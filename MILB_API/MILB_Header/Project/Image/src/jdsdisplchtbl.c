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


#include "jdsdisplchtbl.h"


K_TYPE_DEFINE_WITH_PRIVATE(JdsdispLchTbl, jdsdisp_lch_tbl);
#define JDSDISP_LCH_TBL_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsdispLchTblPrivate, JDSDISP_TYPE_LCH_TBL))


struct  _JdsdispLchTblPrivate
{
	kint a;
};
/**
 IMPL
*/
static void jdsdisp_lch_tbl_constructor(JdsdispLchTbl *self)
{
	JdsdispLchTblPrivate *priv = JDSDISP_LCH_TBL_GET_PRIVATE(self);

	priv->a = 0;
}

static void jdsdisp_lch_tbl_destructor(JdsdispLchTbl *self)
{
	JdsdispLchTblPrivate *priv = JDSDISP_LCH_TBL_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
JdsdispLchTbl* jdsdisp_lch_tbl_new(void)
{
	JdsdispLchTbl* self = k_object_new_with_private(JDSDISP_TYPE_LCH_TBL, sizeof(JdsdispLchTblPrivate));

	return self;
}
