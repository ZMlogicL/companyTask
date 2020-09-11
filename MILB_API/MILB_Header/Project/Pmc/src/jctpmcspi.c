/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#include "jctpmcspi.h"


K_TYPE_DEFINE_WITH_PRIVATE(JctpmcSpi, jctpmc_spi);
#define JCTPMC_SPI_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JctpmcSpiPrivate, JCTPMC_TYPE_SPI))


struct _JctpmcSpiPrivate
{
	kint a;
};
/*
 * IMPL
 */
static void jctpmc_spi_constructor(JctpmcSpi *self)
{
	JctpmcSpiPrivate *priv = JCTPMC_SPI_GET_PRIVATE(self);

	priv->a = 0;
}

static void jctpmc_spi_destructor(JctpmcSpi *self)
{
	JctpmcSpiPrivate *priv = JCTPMC_SPI_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
JctpmcSpi *jctpmc_spi_new(void)
{
	JctpmcSpi* self = k_object_new_with_private(JCTPMC_TYPE_SPI,sizeof(JctpmcSpiPrivate));

	return self;
}
