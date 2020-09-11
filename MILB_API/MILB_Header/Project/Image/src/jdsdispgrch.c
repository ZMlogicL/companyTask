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


#include "jdsdispgrch.h"


K_TYPE_DEFINE_WITH_PRIVATE(JdsdispGrch, jdsdisp_grch);
#define JDSDISP_GRCH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsdispGrchPrivate, JDSDISP_TYPE_GRCH))


struct  _JdsdispGrchPrivate
{
	kint a;
};
/**
 IMPL
*/
static void jdsdisp_grch_constructor(JdsdispGrch *self)
{
	JdsdispGrchPrivate *priv = JDSDISP_GRCH_GET_PRIVATE(self);

	priv->a = 0;
}

static void jdsdisp_grch_destructor(JdsdispGrch *self)
{
	JdsdispGrchPrivate *priv = JDSDISP_GRCH_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
JdsdispGrch* jdsdisp_grch_new(void)
{
	JdsdispGrch* self = k_object_new_with_private(JDSDISP_TYPE_GRCH, sizeof(JdsdispGrchPrivate));

	return self;
}
