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


#include "jdsdispdcore.h"


K_TYPE_DEFINE_WITH_PRIVATE(JdsdispDcore, jdsdisp_dcore);
#define JDSDISP_DCORE_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsdispDcorePrivate, JDSDISP_TYPE_DCORE))


struct  _JdsdispDcorePrivate
{
	kint a;
};
/**
 IMPL
*/
static void jdsdisp_dcore_constructor(JdsdispDcore *self)
{
	JdsdispDcorePrivate *priv = JDSDISP_DCORE_GET_PRIVATE(self);

	priv->a = 0;
}

static void jdsdisp_dcore_destructor(JdsdispDcore *self)
{
	JdsdispDcorePrivate *priv = JDSDISP_DCORE_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
JdsdispDcore* jdsdisp_dcore_new(void)
{
	JdsdispDcore* self = k_object_new_with_private(JDSDISP_TYPE_DCORE, sizeof(JdsdispDcorePrivate));

	return self;
}

