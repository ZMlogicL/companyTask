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


#include "jdsdispdbg.h"


K_TYPE_DEFINE_WITH_PRIVATE(JdsdispDbg, jdsdisp_dbg);
#define JDSDISP_DBG_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsdispDbgPrivate, JDSDISP_TYPE_DBG))


struct  _JdsdispDbgPrivate
{
	kint a;
};
/**
 IMPL
*/
static void jdsdisp_dbg_constructor(JdsdispDbg *self)
{
	JdsdispDbgPrivate *priv = JDSDISP_DBG_GET_PRIVATE(self);

	priv->a = 0;
}

static void jdsdisp_dbg_destructor(JdsdispDbg *self)
{
	JdsdispDbgPrivate *priv = JDSDISP_DBG_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
JdsdispDbg* jdsdisp_dbg_new(void)
{
	JdsdispDbg* self = k_object_new_with_private(JDSDISP_TYPE_DBG, sizeof(JdsdispDbgPrivate));

	return self;
}
