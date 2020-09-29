#!/bin/bash
# Copyright (c) 1999-2017, Parallels International GmbH
# Copyright (c) 2017-2019 Virtuozzo International GmbH. All rights reserved.
#
# This file is part of OpenVZ libraries. OpenVZ is free software; you can
# redistribute it and/or modify it under the terms of the GNU Lesser General
# Public License as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.
#
# Our contact details: Virtuozzo International GmbH, Vordergasse 59, 8200
# Schaffhausen, Switzerland.
#
# This script configure IP alias(es) inside VPS for Debian like distros.
#
# Parameters are passed in environment variables.
# Required parameters:
#   IP_ADDR       - IP address(es) to add
#                   (several addresses should be divided by space)
# Optional parameters:
#   VE_STATE      - state of VPS; could be one of:
#                     starting | stopping | running | stopped
#   IPDELALL      - delete all ip addresses
#
VENET_DEV=venet0
CFGFILE=/etc/network/interfaces
HOSTFILE=/etc/hosts
USE_INET6=yes

function fix_networking_conf()
{
	local cfg=/etc/init/networking.conf

	[ ! -f ${cfg} ] && return 0

	if grep -q "udevtrigger" ${cfg} 2>/dev/null; then
		grep -v udevtrigger ${cfg} | \
			sed "s,(local-filesystems,local-filesystems,g" > ${cfg}.tmp && \
			mv -f ${cfg}.tmp ${cfg}
	fi
}

function setup_network()
{
	echo -e "# This configuration file is auto-generated.
# WARNING: Do not edit this file, otherwise your changes will be lost.
# Please edit template $CFGFILE.template instead.
" > ${CFGFILE}

	if [ -f ${CFGFILE}.template ]; then
		cat ${CFGFILE}.template >> ${CFGFILE}
	fi
	if ! grep -qw lo ${CFGFILE}; then
		echo "auto lo
iface lo inet loopback" >> ${CFGFILE}
	fi
	# Set up /etc/hosts
	if [ ! -f $HOSTFILE ]; then
		echo "127.0.0.1 localhost.localdomain localhost" > $HOSTFILE
	fi
	[ -z "${IP_ADDR}" ] && return
	echo -e "
# Auto generated venet0 interfaces
auto ${VENET_DEV}
iface ${VENET_DEV} inet static
	address 127.0.0.1
	netmask 255.255.255.255
	broadcast 0.0.0.0" >> ${CFGFILE}
	if [ "x${VE_STATE}" = "xstarting" -o "$(is_default_route_configured)" = "no" ]; then
		echo -e "\tup route add default dev ${VENET_DEV}" >> ${CFGFILE}
	fi

	fix_networking_conf
}

function add_ip()
{
	local dev=$1
	local ip=$2
	local mask=$3
	local cfg=

	if ! grep -qe "auto $dev$" ${CFGFILE} 2>/dev/null; then
		cfg="auto ${dev}"
	fi
	cfg="$cfg
iface ${dev} inet static
	address ${ip}"
	if [ -z "${mask}" ]; then
		mask=255.255.255.255
	fi
	cfg="${cfg}
	netmask ${mask}"
	echo -e "${cfg}\n" >> ${CFGFILE}
}

function add_ip6_alias()
{
	local ip=$1

	awk '
		BEGIN {found = 0}
		NF == 0 {next}
		!found && $1 == "iface" && $2 ~/'${VENET_DEV}'$/ && $3 == "inet6" {
			found = 1;
			print;
			next;
		}
		found == 1 && !/^\t/{
			print "\tup ip addr add '$ip' dev venet0";
			found++;
		}
		{print}
		END {
			if (found == 1) {
				print "\tup ip addr add '$ip' dev venet0";
			}
		}
	' < ${CFGFILE} > ${CFGFILE}.$$ && mv -f ${CFGFILE}.$$ ${CFGFILE}
	rm -f ${CFGFILE}.$$ 2>/dev/null
	if_restart=yes
}

function get_all_aliasid()
{
	IFNUM=-1
	IFNUMLIST=`grep -e "^auto ${VENET_DEV}:.*$" ${CFGFILE} 2>/dev/null | sed 's/^auto '${VENET_DEV}'://'`
}

function get_free_aliasid()
{
	# no main iface
	grep -qe "^iface ${VENET_DEV} inet " ${CFGFILE} >/dev/null || return 0

	[ -z "${IFNUMLIST}" ] && get_all_aliasid
	while true; do
		let IFNUM=IFNUM+1
		echo "${IFNUMLIST}" | grep -q -E "^${IFNUM}$" 2>/dev/null || break
	done
	return 1
}

function setup()
{
	local ipm ip mask
	local found
	local dev=$VENET_DEV

	# IPv6 is not supported for ubuntu-8.04
	if grep -q "lenny" /etc/debian_version 2>/dev/null; then
		USE_INET6=no
	fi
	if [ "${VE_STATE}" = "starting" ]; then
		setup_network
	elif ! grep -q "^auto ${VENET_DEV}\$" ${CFGFILE} 2>/dev/null; then
		setup_network
	fi
	if [ "${IPDELALL}" = "yes" ]; then
		ifdown ${VENET_DEV} >/dev/null 2>&1
		remove_debian_interface "${VENET_DEV}:[0-9]*" ${CFGFILE}
		setup_network
	fi
	for ipm in ${IP_ADDR}; do
		ip=${ipm%%/*}
		[ -z "${ip}" ] && continue
		mask=
		if echo "${ipm}" | grep -q '/'; then
			mask=${ipm##*/}
		fi

		if grep -qw -e "^[[:space:]]*address $ip" -e "^[[:space:]]*up ip addr add $ip" ${CFGFILE} 2>/dev/null; then
			continue
		fi

		if is_ipv6 "${ip}"; then
			[ -z "$mask" ] && mask=128
			if grep -q "iface ${dev} inet6" ${CFGFILE} 2>/dev/null; then
				add_ip6_alias "${ip}/${mask}"
			else
				add_debian_ip6 "${ip}/${mask}"
			fi
		else
			get_free_aliasid
			if [ $? -ne 0 ]; then
				add_ip "${dev}:${IFNUM}" "${ip}" "${mask}"
			else
				add_ip "${dev}" "${ip}" "${mask}"
			fi
		fi
	done
	if [ "x${VE_STATE}" = "xrunning" ]; then
		[ -n "${if_restart}" ] && /sbin/ifdown venet0 2>/dev/null
		/sbin/ifup -a --force 2>/dev/null
	fi
}

setup
exit 0
