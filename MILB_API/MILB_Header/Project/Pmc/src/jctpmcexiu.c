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


#include "jctpmcexiu.h"


K_TYPE_DEFINE_WITH_PRIVATE(JctpmcExiu, jctpmc_exiu);
#define JCTPMC_EXIU_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JctpmcExiuPrivate, JCTPMC_TYPE_EXIU))


struct _JctpmcExiuPrivate
{
	kint a;
};
/*
 * IMPL
 */
static void jctpmc_exiu_constructor(JctpmcExiu *self)
{
	JctpmcExiuPrivate *priv = JCTPMC_EXIU_GET_PRIVATE(self);

	priv->a = 0;
}

static void jctpmc_exiu_destructor(JctpmcExiu *self)
{
	JctpmcExiuPrivate *priv = JCTPMC_EXIU_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
JctpmcExiu *jctpmc_exiu_new(void)
{
	JctpmcExiu* self = k_object_new_with_private(JCTPMC_TYPE_EXIU,sizeof(JctpmcExiuPrivate));

	return self;
}
