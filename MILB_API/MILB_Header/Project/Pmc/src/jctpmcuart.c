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


#include "jctpmcuart.h"


K_TYPE_DEFINE_WITH_PRIVATE(JctpmcUart, jctpmc_uart);
#define JCTPMC_UART_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JctpmcUartPrivate, JCTPMC_TYPE_UART))


struct _JctpmcUartPrivate
{
	kint a;
};
/*
 * IMPL
 */
static void jctpmc_uart_constructor(JctpmcUart *self)
{
	JctpmcUartPrivate *priv = JCTPMC_UART_GET_PRIVATE(self);

	priv->a = 0;
}

static void jctpmc_uart_destructor(JctpmcUart *self)
{
	JctpmcUartPrivate *priv = JCTPMC_UART_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
JctpmcUart *jctpmc_uart_new(void)
{
	JctpmcUart* self = k_object_new_with_private(JCTPMC_TYPE_UART,sizeof(JctpmcUartPrivate));

	return self;
}
