/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition XDMAC Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "kxdmac.h"

K_TYPE_DEFINE_WITH_PRIVATE(KXdmac, k_xdmac);
#define K_XDMAC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KXdmacPrivate, K_TYPE_XDMAC))

struct _KXdmacPrivate
{

};

volatile IoXdmac ioXdmac __attribute__((section(".XDMAC")));
volatile IoXdmac ioXdmacs __attribute__((section(".XDMACS")));
/**
 *IMPL
 */
static void k_xdmac_constructor(KXdmac *self)
{
//	KXdmacPrivate *priv = K_XDMAC_GET_PRIVATE(self);
}

static void k_xdmac_destructor(KXdmac *self)
{
//	KXdmacPrivate *priv = K_XDMAC_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KXdmac* k_xdmac_new(void)
{
    KXdmac* self = k_object_new_with_private(K_TYPE_XDMAC, sizeof(KXdmacPrivate));
    return self;
}

