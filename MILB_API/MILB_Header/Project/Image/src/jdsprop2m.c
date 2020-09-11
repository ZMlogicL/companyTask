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


#include "jdsprop2m.h"


K_TYPE_DEFINE_WITH_PRIVATE(JdsproP2m, jdspro_p2m);
#define JDSPRO_P2M_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsproP2mPrivate, JDSPRO_TYPE_P2M))


struct  _JdsproP2mPrivate
{
	kint a;
};
/**
 IMPL
*/
static void jdspro_p2m_constructor(JdsproP2m *self)
{
	JdsproP2mPrivate *priv = JDSPRO_P2M_GET_PRIVATE(self);

	priv->a = 0;
}

static void jdspro_p2m_destructor(JdsproP2m *self)
{
	JdsproP2mPrivate *priv = JDSPRO_P2M_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
JdsproP2m* jdspro_p2m_new(void)
{
	JdsproP2m* self = k_object_new_with_private(JDSPRO_TYPE_P2M, sizeof(JdsproP2mPrivate));

	return self;
}
