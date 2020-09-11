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


#include "jctpmccalendar.h"


K_TYPE_DEFINE_WITH_PRIVATE(JctpmcCalendar, jctpmc_calendar);
#define JCTPMC_CALENDAR_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JctpmcCalendarPrivate, JCTPMC_TYPE_CALENDAR))


struct _JctpmcCalendarPrivate
{
	kint a;
};
/*
 * IMPL
 */
static void jctpmc_calendar_constructor(JctpmcCalendar *self)
{
	JctpmcCalendarPrivate *priv = JCTPMC_CALENDAR_GET_PRIVATE(self);

	priv->a = 0;
}

static void jctpmc_calendar_destructor(JctpmcCalendar *self)
{
	JctpmcCalendarPrivate *priv = JCTPMC_CALENDAR_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
JctpmcCalendar *jctpmc_calendar_new(void)
{
	JctpmcCalendar* self = k_object_new_with_private(JCTPMC_TYPE_CALENDAR,sizeof(JctpmcCalendarPrivate));

	return self;
}
