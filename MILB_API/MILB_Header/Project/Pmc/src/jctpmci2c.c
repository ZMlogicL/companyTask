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


#include "jctpmci2c.h"


K_TYPE_DEFINE_WITH_PRIVATE(JctpmcI2c, jctpmc_i2c);
#define JCTPMC_I2C_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JctpmcI2cPrivate, JCTPMC_TYPE_I2C))


struct _JctpmcI2cPrivate
{
	kint a;
};
/*
 * IMPL
 */
static void jctpmc_i2c_constructor(JctpmcI2c *self)
{
	JctpmcI2cPrivate *priv = JCTPMC_I2C_GET_PRIVATE(self);

	priv->a = 0;
}

static void jctpmc_i2c_destructor(JctpmcI2c *self)
{
	JctpmcI2cPrivate *priv = JCTPMC_I2C_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
JctpmcI2c *jctpmc_i2c_new(void)
{
	JctpmcI2c* self = k_object_new_with_private(JCTPMC_TYPE_I2C,sizeof(JctpmcI2cPrivate));

	return self;
}
