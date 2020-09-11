/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-04
*@author            :陈倩
*@brief             :khdmac
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*3、
*4、
*5、
*@version
*
*/


#include "khdmac.h"


K_TYPE_DEFINE_WITH_PRIVATE(KHdmac, k_hdmac);
#define K_HDMAC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KHdmacPrivate, K_TYPE_HDMAC))


struct  _KHdmacPrivate
{

};


volatile IoHdmac    ioHdmac    __attribute__((section(".HDMAC")));		/* External Storage */
volatile IoHdmac    ioHdmac0   __attribute__((section(".HDMAC0")));	/* Peripheral */
volatile IoHdmac    ioHdmac1   __attribute__((section(".HDMAC1")));	/* Peripheral */
/**
 IMPL
*/
static void k_hdmac_constructor(KHdmac *self)
{
//	KHdmacPrivate *priv = K_HDMAC_GET_PRIVATE(self);
}

static void k_hdmac_destructor(KHdmac *self)
{
//	KHdmacPrivate *priv = K_HDMAC_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KHdmac* k_hdmac_new(void)
{
	KHdmac* self = k_object_new_with_private(K_TYPE_HDMAC, sizeof(KHdmacPrivate));
	return self;
}

