/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-05
*@author            :陈倩
*@brief             :kslimbus
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


#include "kslimbus.h"


K_TYPE_DEFINE_WITH_PRIVATE(KSlimbus, k_slimbus);
#define K_SLIMBUS_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KSlimbusPrivate, K_TYPE_SLIMBUS))


struct  _KSlimbusPrivate
{

};


volatile IoSlimbus  ioSlimbus0     __attribute__((section(".SLIMBUS0")));
volatile IoSlimbus  ioSlimbus1     __attribute__((section(".SLIMBUS1")));
volatile IoSlimbus  ioSlimbus2     __attribute__((section(".SLIMBUS2")));
volatile IoSlimbus  ioSlimbus3     __attribute__((section(".SLIMBUS3")));
/**
 IMPL
*/
static void k_slimbus_constructor(KSlimbus *self)
{
//	KSlimbusPrivate *priv = K_SLIMBUS_GET_PRIVATE(self);
}

static void k_slimbus_destructor(KSlimbus *self)
{
//	KSlimbusPrivate *priv = K_SLIMBUS_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KSlimbus* k_slimbus_new(void)
{
	KSlimbus* self = k_object_new_with_private(K_TYPE_SLIMBUS, sizeof(KSlimbusPrivate));
	return self;
}

