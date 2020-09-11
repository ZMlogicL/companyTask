/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-10
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


#include "jdsdispdcoretbl.h"


K_TYPE_DEFINE_WITH_PRIVATE(JdsdispDcoreTbl, jdsdisp_dcore_tbl);
#define JDSDISP_DCORE_TBL_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsdispDcoreTblPrivate, JDSDISP_TYPE_DCORE_TBL))


struct  _JdsdispDcoreTblPrivate
{
	kint a;
};
/**
 IMPL
*/
static void jdsdisp_dcore_tbl_constructor(JdsdispDcoreTbl *self)
{
	JdsdispDcoreTblPrivate *priv = JDSDISP_DCORE_TBL_GET_PRIVATE(self);

	priv->a = 0;
}

static void jdsdisp_dcore_tbl_destructor(JdsdispDcoreTbl *self)
{
	JdsdispDcoreTblPrivate *priv = JDSDISP_DCORE_TBL_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
JdsdispDcoreTbl* jdsdisp_dcore_tbl_new(void)
{
	JdsdispDcoreTbl* self = k_object_new_with_private(JDSDISP_TYPE_DCORE_TBL, sizeof(JdsdispDcoreTblPrivate));

	return self;
}
