/**************************************************************************
 * Copyright 2010-2011, Freescale Semiconductor, Inc. All rights reserved.
 ***************************************************************************/
/*
 * File:	gplcode.h
 * Description: IPv4 Options handling related function definations.
 * Authors:	Venkataraman Subhashini <B22166@freescale.com>
 *
 */
/* History
 *  Version	Date		Author		Change Description
 *
*/
/****************************************************************************/


#ifndef __ASF_GPL_CODE_H
#define __ASF_GPL_CODE_H
#include "asf.h"

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 32)
#define asfAllocPerCpu(size)	__alloc_percpu(size, 4)
#define asfFreePerCpu(ptr)	free_percpu(ptr)
#define asfPerCpuPtr(ptr, cpu)	per_cpu_ptr(ptr, cpu)

#if (ASF_FEATURE_OPTION > ASF_MINIMUM)
#define asfDevHardXmit(dev, skb)	(dev->netdev_ops->ndo_start_xmit(skb, dev))
#else
extern int gfar_fast_xmit(struct sk_buff *skb, struct net_device *dev);
#define asfDevHardXmit(dev, skb)	(gfar_fast_xmit(skb, dev))
#endif

#else

#define asfAllocPerCpu(size)	percpu_alloc(size, GFP_KERNEL)
#define asfFreePerCpu(ptr)	percpu_free(ptr)
#define asfPerCpuPtr(ptr, cpu)	percpu_ptr(ptr, cpu)
#define asfDevHardXmit(dev, skb)	(dev->hard_start_xmit(skb, dev))
#endif



void asf_ip_options_fragment(struct sk_buff  *skb);
int asf_ip_options_compile(struct net *net, struct ip_options  *opt, struct sk_buff  *skb, struct iphdr *ipheader);

#endif
