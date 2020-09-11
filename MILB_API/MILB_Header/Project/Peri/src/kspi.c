/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-05
*@author            :陈倩
*@brief             :kspi
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


#include "kspi.h"


K_TYPE_DEFINE_WITH_PRIVATE(KSpi, k_spi);
#define K_SPI_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KSpiPrivate, K_TYPE_SPI))


struct  _KSpiPrivate
{

};


volatile IoSpi		ioSpi[3]	__attribute__((section(".SPI")));
/**
 IMPL
*/
static void k_spi_constructor(KSpi *self)
{
//	KSpiPrivate *priv = K_SPI_GET_PRIVATE(self);
}

static void k_spi_destructor(KSpi *self)
{
//	KSpiPrivate *priv = K_SPI_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KSpi* k_spi_new(void)
{
	KSpi* self = k_object_new_with_private(K_TYPE_SPI, sizeof(KSpiPrivate));
	return self;
}

