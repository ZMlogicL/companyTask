/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-09
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


#include "jdsdisplch.h"


K_TYPE_DEFINE_WITH_PRIVATE(JdsdispLch, jdsdisp_lch);
#define JDSDISP_LCH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsdispLchPrivate, JDSDISP_TYPE_LCH))


struct  _JdsdispLchPrivate
{
	kint a;
};
/**
 IMPL
*/
static void jdsdisp_lch_constructor(JdsdispLch *self)
{
	JdsdispLchPrivate *priv = JDSDISP_LCH_GET_PRIVATE(self);

	priv->a = 0;
}

static void jdsdisp_lch_destructor(JdsdispLch *self)
{
	JdsdispLchPrivate *priv = JDSDISP_LCH_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
JdsdispLch* jdsdisp_lch_new(void)
{
	JdsdispLch* self = k_object_new_with_private(JDSDISP_TYPE_LCH, sizeof(JdsdispLchPrivate));

	return self;
}
