/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition Network InterConnect I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "knic.h"

K_TYPE_DEFINE_WITH_PRIVATE(KNic, k_nic);
#define K_NIC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KNicPrivate, K_TYPE_NIC))

struct _KNicPrivate
{

};

volatile IoAddrctrl ioNicAddrctrl __attribute__((section(".NIC_ADDRCTRL")));
volatile IoAsib ioNicAsib[7] __attribute__((section(".NIC_ASIB")));

/**
 *IMPL
 */
static void k_nic_constructor(KNic *self)
{
//	KNicPrivate *priv = K_NIC_GET_PRIVATE(self);
}

static void k_nic_destructor(KNic *self)
{
//	KNicPrivate *priv = K_NIC_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KNic* k_nic_new(void)
{
    KNic* self = k_object_new_with_private(K_TYPE_NIC, sizeof(KNicPrivate));
    return self;
}
