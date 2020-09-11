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


#include "jctpmccrg11.h"


K_TYPE_DEFINE_WITH_PRIVATE(JctpmcCrg11, jctpmc_crg11);
#define JCTPMC_CRG11_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JctpmcCrg11Private, JCTPMC_TYPE_CRG11))


struct _JctpmcCrg11Private
{
	kint a;
};
/*
 * IMPL
 */
static void jctpmc_crg11_constructor(JctpmcCrg11 *self)
{
	JctpmcCrg11Private *priv = JCTPMC_CRG11_GET_PRIVATE(self);

	priv->a = 0;
}

static void jctpmc_crg11_destructor(JctpmcCrg11 *self)
{
	JctpmcCrg11Private *priv = JCTPMC_CRG11_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
JctpmcCrg11 *jctpmc_crg11_new(void)
{
	JctpmcCrg11* self = k_object_new_with_private(JCTPMC_TYPE_CRG11,sizeof(JctpmcCrg11Private));

	return self;
}
