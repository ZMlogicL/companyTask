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


#include "jdsdisphdmi.h"


K_TYPE_DEFINE_WITH_PRIVATE(JdsdispHdmi, jdsdisp_hdmi);
#define JDSDISP_HDMI_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsdispHdmiPrivate, JDSDISP_TYPE_HDMI))


struct  _JdsdispHdmiPrivate
{
	kint a;
};
/**
 IMPL
*/
static void jdsdisp_hdmi_constructor(JdsdispHdmi *self)
{
	JdsdispHdmiPrivate *priv = JDSDISP_HDMI_GET_PRIVATE(self);

	priv->a = 0;
}

static void jdsdisp_hdmi_destructor(JdsdispHdmi *self)
{
	JdsdispHdmiPrivate *priv = JDSDISP_HDMI_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
JdsdispHdmi* jdsdisp_hdmi_new(void)
{
	JdsdispHdmi* self = k_object_new_with_private(JDSDISP_TYPE_HDMI, sizeof(JdsdispHdmiPrivate));

	return self;
}
