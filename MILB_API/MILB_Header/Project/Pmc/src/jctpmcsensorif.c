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


#include "jctpmcsensorif.h"


K_TYPE_DEFINE_WITH_PRIVATE(JctpmcSensorIf, jctpmc_sensor_if);
#define JCTPMC_SENSOR_IF_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JctpmcSensorIfPrivate, JCTPMC_TYPE_SENSOR_IF))


struct _JctpmcSensorIfPrivate
{
	kint a;
};
/*
 * IMPL
 */
static void jctpmc_sensor_if_constructor(JctpmcSensorIf *self)
{
	JctpmcSensorIfPrivate *priv = JCTPMC_SENSOR_IF_GET_PRIVATE(self);

	priv->a = 0;
}

static void jctpmc_sensor_if_destructor(JctpmcSensorIf *self)
{
	JctpmcSensorIfPrivate *priv = JCTPMC_SENSOR_IF_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
JctpmcSensorIf *jctpmc_sensor_if_new(void)
{
	JctpmcSensorIf* self = k_object_new_with_private(JCTPMC_TYPE_SENSOR_IF,sizeof(JctpmcSensorIfPrivate));

	return self;
}
