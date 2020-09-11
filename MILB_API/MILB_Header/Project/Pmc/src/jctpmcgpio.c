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


#include "jctpmcgpio.h"


K_TYPE_DEFINE_WITH_PRIVATE(JctpmcGpio, jctpmc_gpio);
#define JCTPMC_GPIO_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JctpmcGpioPrivate, JCTPMC_TYPE_GPIO))


struct _JctpmcGpioPrivate
{
	kint a;
};
/*
 * IMPL
 */
static void jctpmc_gpio_constructor(JctpmcGpio *self)
{
	JctpmcGpioPrivate *priv = JCTPMC_GPIO_GET_PRIVATE(self);

	priv->a = 0;
}

static void jctpmc_gpio_destructor(JctpmcGpio *self)
{
	JctpmcGpioPrivate *priv = JCTPMC_GPIO_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
JctpmcGpio *jctpmc_gpio_new(void)
{
	JctpmcGpio* self = k_object_new_with_private(JCTPMC_TYPE_GPIO,sizeof(JctpmcGpioPrivate));

	return self;
}
