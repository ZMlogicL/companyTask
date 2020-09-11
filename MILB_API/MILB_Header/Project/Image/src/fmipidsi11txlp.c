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


#include "fmipidsi11txlp.h"


K_TYPE_DEFINE_WITH_PRIVATE(FMipidsi11txLp, f_mipidsi11tx_lp);
#define F_MIPIDSI11TX_LP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), FMipidsi11txLpPrivate, F_TYPE_MIPIDSI11TX_LP))


struct  _FMipidsi11txLpPrivate
{
	kint a;
};
/**
 IMPL
*/
static void f_mipidsi11tx_lp_constructor(FMipidsi11txLp *self)
{
	FMipidsi11txLpPrivate *priv = F_MIPIDSI11TX_LP_GET_PRIVATE(self);

	priv->a = 0;
}

static void f_mipidsi11tx_lp_destructor(FMipidsi11txLp *self)
{
	FMipidsi11txLpPrivate *priv = F_MIPIDSI11TX_LP_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
FMipidsi11txLp* f_mipidsi11tx_lp_new(void)
{
	FMipidsi11txLp* self = k_object_new_with_private(F_TYPE_MIPIDSI11TX_LP, sizeof(FMipidsi11txLpPrivate));

	return self;
}
