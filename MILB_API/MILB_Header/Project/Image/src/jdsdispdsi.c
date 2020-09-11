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


#include "jdsdispdsi.h"


K_TYPE_DEFINE_WITH_PRIVATE(JdsdispDsi, jdsdisp_dsi);
#define JDSDISP_DSI_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsdispDsiPrivate, JDSDISP_TYPE_DSI))


struct  _JdsdispDsiPrivate
{
	kint a;
};
/**
 IMPL
*/
static void jdsdisp_dsi_constructor(JdsdispDsi *self)
{
	JdsdispDsiPrivate *priv = JDSDISP_DSI_GET_PRIVATE(self);

	priv->a = 0;
}

static void jdsdisp_dsi_destructor(JdsdispDsi *self)
{
	JdsdispDsiPrivate *priv = JDSDISP_DSI_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
JdsdispDsi* jdsdisp_dsi_new(void)
{
	JdsdispDsi* self = k_object_new_with_private(JDSDISP_TYPE_DSI, sizeof(JdsdispDsiPrivate));

	return self;
}
