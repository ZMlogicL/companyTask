/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-05
*@author            :陈倩
*@brief             :kperipheral
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


#include "kperipheral.h"


K_TYPE_DEFINE_WITH_PRIVATE(KPeripheral, k_peripheral);
#define K_PERIPHERAL_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KPeripheralPrivate, K_TYPE_PERIPHERAL))


struct  _KPeripheralPrivate
{

};


volatile IoPeri     ioPeri         __attribute__((section(".PERI")));
volatile IoPwmdma   ioPwmdma[4]    __attribute__((section(".PWMDMA")));
/**
 IMPL
*/
static void k_peripheral_constructor(KPeripheral *self)
{
//	KPeripheralPrivate *priv = K_PERIPHERAL_GET_PRIVATE(self);
}

static void k_peripheral_destructor(KPeripheral *self)
{
//	KPeripheralPrivate *priv = K_PERIPHERAL_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KPeripheral* k_peripheral_new(void)
{
	KPeripheral* self = k_object_new_with_private(K_TYPE_PERIPHERAL, sizeof(KPeripheralPrivate));
	return self;
}

