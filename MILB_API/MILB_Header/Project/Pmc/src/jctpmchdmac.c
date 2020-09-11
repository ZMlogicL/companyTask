/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
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


#include "jctpmchdmac.h"


K_TYPE_DEFINE_WITH_PRIVATE(JctpmcHdmac, jctpmc_hdmac);
#define JCTPMC_HDMAC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JctpmcHdmacPrivate, JCTPMC_TYPE_HDMAC))


struct _JctpmcHdmacPrivate
{
	kint a;
};
/*
 * IMPL
 */
static void jctpmc_hdmac_constructor(JctpmcHdmac *self)
{
	JctpmcHdmacPrivate *priv = JCTPMC_HDMAC_GET_PRIVATE(self);

	priv->a = 0;
}

static void jctpmc_hdmac_destructor(JctpmcHdmac *self)
{
	JctpmcHdmacPrivate *priv = JCTPMC_HDMAC_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
JctpmcHdmac *jctpmc_hdmac_new(void)
{
	JctpmcHdmac* self = k_object_new_with_private(JCTPMC_TYPE_HDMAC,sizeof(JctpmcHdmacPrivate));

	return self;
}
