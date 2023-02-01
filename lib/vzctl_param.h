/*
 *  Copyright (c) 1999-2017, Parallels International GmbH
 * Copyright (c) 2017-2019 Virtuozzo International GmbH. All rights reserved.
 *
 * This file is part of OpenVZ libraries. OpenVZ is free software; you can
 * redistribute it and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation; either version
 * 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/> or write to Free Software Foundation,
 * 51 Franklin Street, Fifth Floor Boston, MA 02110, USA.
 *
 * Our contact details: Virtuozzo International GmbH, Vordergasse 59, 8200
 * Schaffhausen, Switzerland.
 *
 */

#ifndef _VZCTL_PARAM_H_
#define _VZCTL_PARAM_H_

enum {
	VZCTL_PARAM_KMEMSIZE = 0xffff,
	VZCTL_PARAM_LOCKEDPAGES,
	VZCTL_PARAM_PRIVVMPAGES,
	VZCTL_PARAM_SHMPAGES,
	VZCTL_PARAM_NUMPROC,
	VZCTL_PARAM_PHYSPAGES,
	VZCTL_PARAM_VMGUARPAGES,
	VZCTL_PARAM_OOMGUARPAGES,
	VZCTL_PARAM_NUMTCPSOCK,
	VZCTL_PARAM_NUMFLOCK,
	VZCTL_PARAM_NUMPTY,
	VZCTL_PARAM_NUMSIGINFO,
	VZCTL_PARAM_TCPSNDBUF,
	VZCTL_PARAM_TCPRCVBUF,
	VZCTL_PARAM_OTHERSOCKBUF,
	VZCTL_PARAM_DGRAMRCVBUF,
	VZCTL_PARAM_NUMOTHERSOCK,
	VZCTL_PARAM_DCACHESIZE,
	VZCTL_PARAM_NUMFILE,
	VZCTL_PARAM_NUMIPTENT,
	VZCTL_PARAM_SWAPPAGES,
	VZCTL_PARAM_TOTVMPAGES,
	VZCTL_PARAM_IPCSHMPAGES,
	VZCTL_PARAM_ANONSHPAGES,
	VZCTL_PARAM_RSSPAGES,
	VZCTL_PARAM_OOMGUAR,
	VZCTL_PARAM_NUMSOCK,
	VZCTL_PARAM_UNIXSOCKBUF,
	VZCTL_PARAM_SOCKRCVBUF,
	VZCTL_PARAM_NUMUNIXSOCK,
	VZCTL_PARAM_VM_OVERCOMMIT,
	VZCTL_PARAM_IP_ADDRESS,
	VZCTL_PARAM_IPDEL,
	VZCTL_PARAM_HOSTNAME,
	VZCTL_PARAM_SEARCHDOMAIN,
	VZCTL_PARAM_NAMESERVER,
	VZCTL_PARAM_USERPW,
	VZCTL_PARAM_TEMPLATE,
	VZCTL_PARAM_OSTEMPLATE,
	VZCTL_PARAM_DEF_OSTEMPLATE,
	VZCTL_PARAM_BASH,
	VZCTL_PARAM_SAVE,
	VZCTL_PARAM_VE_ROOT,
	VZCTL_PARAM_VE_PRIVATE,
	VZCTL_PARAM_ONBOOT,
	VZCTL_PARAM_IPHOST,
	VZCTL_PARAM_DISKSPACE,
	VZCTL_PARAM_DISKINODES,
	VZCTL_PARAM_QUOTATIME,
	VZCTL_PARAM_QUOTAUGIDLIMIT,
	VZCTL_PARAM_DISK_QUOTA,
	VZCTL_PARAM_CFGVER,
	VZCTL_PARAM_AVNUMPROC,
	VZCTL_PARAM_TEMPLATES,
	VZCTL_PARAM_SKIPQUOTACHECK,
	VZCTL_PARAM_MEMINFO,
	VZCTL_PARAM_CPUWEIGHT,
	VZCTL_PARAM_CPULIMIT,
	VZCTL_PARAM_CPULIMIT_MHZ,
	VZCTL_PARAM_CPUUNITS,
	VZCTL_PARAM_CPUS,
	VZCTL_PARAM_CPUMASK,
	VZCTL_PARAM_NODEMASK,
	VZCTL_PARAM_NOATIME,
	VZCTL_PARAM_SAFE,
	VZCTL_PARAM_CAP,
	VZCTL_PARAM_CONFIG,
	VZCTL_PARAM_SHARED,
	VZCTL_PARAM_FAST,
	VZCTL_PARAM_APPLYCONFIG,
	VZCTL_PARAM_IPTABLES,
	VZCTL_PARAM_NETDEV,
	VZCTL_PARAM_NETDEV_DEL,
	VZCTL_PARAM_DISABLED,
	VZCTL_PARAM_FORCE,
	VZCTL_PARAM_SKIP_VE_SETUP,
	VZCTL_PARAM_CONFIG_SAMPLE,
	VZCTL_PARAM_CONFIG_CUSTOMIZE,
	VZCTL_PARAM_SETMODE,
	VZCTL_PARAM_LOGFILE,
	VZCTL_PARAM_LOGGING,
	VZCTL_PARAM_LOGLEVEL,
	VZCTL_PARAM_LOCKDIR,
	VZCTL_PARAM_DUMPFILE,
	VZCTL_PARAM_CPTCONTEXT,
	VZCTL_PARAM_CPU_FLAGS,
	VZCTL_PARAM_KILL,
	VZCTL_PARAM_RESUME,
	VZCTL_PARAM_DUMP,
	VZCTL_PARAM_SUSPEND,
	VZCTL_PARAM_UNDUMP,
	VZCTL_PARAM_DUMPDIR,
	VZCTL_PARAM_SKIP_ARPDETECT,
	VZCTL_PARAM_RESET_UB,
	VZCTL_PARAM_VEID,
	VZCTL_PARAM_NAME,
	VZCTL_PARAM_DESCRIPTION,
	VZCTL_PARAM_APPLYCONFIG_MAP,
	VZCTL_PARAM_WAIT,
	VZCTL_PARAM_IPV6NET,
	VZCTL_PARAM_VETH_ADD,
	VZCTL_PARAM_FEATURES,
	VZCTL_PARAM_NETIF,
	VZCTL_PARAM_NETIF_ADD,
	VZCTL_PARAM_NETIF_DEL,
	VZCTL_PARAM_NETIF_IFNAME,
	VZCTL_PARAM_NETIF_MAC,
	VZCTL_PARAM_NETIF_HOST_IFNAME,
	VZCTL_PARAM_NETIF_HOST_MAC,
	VZCTL_PARAM_NETIF_GW,
	VZCTL_PARAM_NETIF_GW6,
	VZCTL_PARAM_NETIF_DHCP,
	VZCTL_PARAM_NETIF_DHCP6,
	VZCTL_PARAM_NETIF_MAC_FILTER,
	VZCTL_PARAM_NETIF_CONFIGURE_MODE,
	VZCTL_PARAM_NETIF_NETWORK,
	VZCTL_PARAM_NETIF_IPADD,
	VZCTL_PARAM_NETIF_IPDEL,
	VZCTL_PARAM_DISK,
	VZCTL_PARAM_VERBOSE,
	VZCTL_PARAM_DISTRIBUTION,
	VZCTL_PARAM_TECHNOLOGIES,
	VZCTL_PARAM_DEVICES,
	VZCTL_PARAM_DEVNODES,
	VZCTL_PARAM_IOPRIO,
	VZCTL_PARAM_IOLIMIT,
	VZCTL_PARAM_IOLIMIT_MB,
	VZCTL_PARAM_IOPSLIMIT,
	VZCTL_PARAM_VE_TYPE,
	VZCTL_PARAM_VE_UUID,
	VZCTL_PARAM_APPLY_IPONLY,
	VZCTL_PARAM_HA_ENABLE,
	VZCTL_PARAM_HA_PRIO,
	VZCTL_PARAM_OSRELEASE,
	VZCTL_PARAM_JOURNALED_QUOTA,
	VZCTL_PARAM_USE_NET_RPS,
	VZCTL_PARAM_SKIP_CLUSTER,
	VZCTL_PARAM_RENEW,
	VZCTL_PARAM_REG_START,
	VZCTL_PARAM_KEEP_PAGES,
	VZCTL_PARAM_UNFREEZE,
	VZCTL_PARAM_BINDMOUNT,
	VZCTL_PARAM_VE_ENVIRONMENT,
	VZCTL_PARAM_PCI,
	VZCTL_PARAM_PCI_DEL,
	VZCTL_PARAM_ORIGIN_SAMPLE,
	VZCTL_PARAM_SLMMEMORYLIMIT,
	VZCTL_PARAM_SLMMODE,
	VZCTL_PARAM_STORAGE_LIST,
	VZCTL_PARAM_BURST_CPU_AVG_USAGE,
	VZCTL_PARAM_BURST_CPULIMIT,
	VZCTL_PARAM_TOTALRATE,
	VZCTL_PARAM_RATE,
	VZCTL_PARAM_RATEBOUND,
	VZCTL_PARAM_TRAFFIC_SHAPING,
	VZCTL_PARAM_AUTOCOMPACT,
	VZCTL_PARAM_BOOTORDER,
	VZCTL_PARAM_ROOT_DISK,
	VZCTL_PARAM_SWAP,
	VZCTL_PARAM_MEMORY,
	VZCTL_PARAM_NETIF_IP_FILTER,
	VZCTL_PARAM_BINDMOUNT_DEL,
	VZCTL_PARAM_MEM_GUARANTEE,
	VZCTL_PARAM_NETIF_NETTYPE,
	VZCTL_PARAM_AUTOSTOP,
	VZCTL_PARAM_PAGECACHE_ISOLATION,
	VZCTL_PARAM_NUMMEMORYSUBGROUPS,
	VZCTL_PARAM_NUMNETIF,
	VZCTL_PARAM_NETIF_VPORT_TYPE,
	VZCTL_PARAM_MEM_GUARANTEE_BYTES,
	VZCTL_PARAM_NETIF_IFACEID,
};

#endif
