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


#include "jdspropwch.h"


K_TYPE_DEFINE_WITH_PRIVATE(JdsproPwch, jdspro_pwch);
#define JDSPRO_PWCH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsproPwchPrivate, JDSPRO_TYPE_PWCH))


struct  _JdsproPwchPrivate
{
	kint a;
};
/**
 IMPL
*/
static void jdspro_pwch_constructor(JdsproPwch *self)
{
	JdsproPwchPrivate *priv = JDSPRO_PWCH_GET_PRIVATE(self);

	priv->a = 0;
}

static void jdspro_pwch_destructor(JdsproPwch *self)
{
	JdsproPwchPrivate *priv = JDSPRO_PWCH_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
JdsproPwch* jdspro_pwch_new(void)
{
	JdsproPwch* self = k_object_new_with_private(JDSPRO_TYPE_PWCH, sizeof(JdsproPwchPrivate));

	return self;
}
