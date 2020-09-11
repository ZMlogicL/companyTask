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


#include "jctpmcwatchdog.h"


K_TYPE_DEFINE_WITH_PRIVATE(JctpmcWatchdog, jctpmc_watchdog);
#define JCTPMC_WATCHDOG_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JctpmcWatchdogPrivate, JCTPMC_TYPE_WATCHDOG))


struct _JctpmcWatchdogPrivate
{
	kint a;
};
/*
 * IMPL
 */
static void jctpmc_watchdog_constructor(JctpmcWatchdog *self)
{
	JctpmcWatchdogPrivate *priv = JCTPMC_WATCHDOG_GET_PRIVATE(self);

	priv->a = 0;
}

static void jctpmc_watchdog_destructor(JctpmcWatchdog *self)
{
	JctpmcWatchdogPrivate *priv = JCTPMC_WATCHDOG_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
JctpmcWatchdog *jctpmc_watchdog_new(void)
{
	JctpmcWatchdog* self = k_object_new_with_private(JCTPMC_TYPE_WATCHDOG,sizeof(JctpmcWatchdogPrivate));

	return self;
}
