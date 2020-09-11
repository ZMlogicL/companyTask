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


#include "fhdmitx2p0lp2.h"


K_TYPE_DEFINE_WITH_PRIVATE(FHdmitx2p0Lp2, f_hdmitx2p0_lp2);
#define F_HDMITX2P0_LP2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), FHdmitx2p0Lp2Private, F_TYPE_HDMITX2P0_LP2))


struct  _FHdmitx2p0Lp2Private
{
	kint a;
};
/**
 IMPL
*/
static void f_hdmitx2p0_lp2_constructor(FHdmitx2p0Lp2 *self)
{
	FHdmitx2p0Lp2Private *priv = F_HDMITX2P0_LP2_GET_PRIVATE(self);

	priv->a = 0;
}

static void f_hdmitx2p0_lp2_destructor(FHdmitx2p0Lp2 *self)
{
	FHdmitx2p0Lp2Private *priv = F_HDMITX2P0_LP2_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
FHdmitx2p0Lp2* f_hdmitx2p0_lp2_new(void)
{
	FHdmitx2p0Lp2* self = k_object_new_with_private(F_TYPE_HDMITX2P0_LP2, sizeof(FHdmitx2p0Lp2Private));

	return self;
}
