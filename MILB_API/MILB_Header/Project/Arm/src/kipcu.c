/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-04
 *@author            :郑蛘钊
 *@brief             :Definition IPCU (Inter-Processor Communications Unit) I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#include "kipcu.h"


K_TYPE_DEFINE_WITH_PRIVATE(KIpcu, k_ipcu);

#define K_IPCU_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KIpcuPrivate, K_TYPE_IPCU))


struct _KIpcuPrivate
{

};


volatile IoIpcu ioIpcu0 __attribute__((section(".IPCU0")));
volatile IoIpcu ioIpcu1 __attribute__((section(".IPCU1")));
/**
 *IMPL
 */
static void k_ipcu_constructor(KIpcu *self)
{
//	KIpcuPrivate *priv = K_IPCU_GET_PRIVATE(self);
}

static void k_ipcu_destructor(KIpcu *self)
{
//	KIpcuPrivate *priv = K_IPCU_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KIpcu* k_ipcu_new(void)
{
    KIpcu* self = k_object_new_with_private(K_TYPE_IPCU, sizeof(KIpcuPrivate));
    return self;
}
