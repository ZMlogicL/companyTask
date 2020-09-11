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


#include "fhdmitx2p0lp3.h"


K_TYPE_DEFINE_WITH_PRIVATE(FHdmitx2p0Lp3, f_hdmitx2p0_lp3);
#define F_HDMITX2P0_LP3_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), FHdmitx2p0Lp3Private, F_TYPE_HDMITX2P0_LP3))


struct  _FHdmitx2p0Lp3Private
{
	kint a;
};
/**
 IMPL
*/
static void f_hdmitx2p0_lp3_constructor(FHdmitx2p0Lp3 *self)
{
	FHdmitx2p0Lp3Private *priv = F_HDMITX2P0_LP3_GET_PRIVATE(self);

	priv->a = 0;
}

static void f_hdmitx2p0_lp3_destructor(FHdmitx2p0Lp3 *self)
{
	FHdmitx2p0Lp3Private *priv = F_HDMITX2P0_LP3_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
FHdmitx2p0Lp3* f_hdmitx2p0_lp3_new(void)
{
	FHdmitx2p0Lp3* self = k_object_new_with_private(F_TYPE_HDMITX2P0_LP3, sizeof(FHdmitx2p0Lp3Private));

	return self;
}
