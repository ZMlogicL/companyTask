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


#include "kjdsdisp3a.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsdisp3a, k_jdsdisp3a);
#define K_JDSDISP3A_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsdisp3aPrivate, K_TYPE_JDSDISP3A))


struct  _KJdsdisp3aPrivate
{
	kint a;
};


volatile  IoJdsdispTop	ioDisp				__attribute__((section(".DISP")));
volatile  IoJdsdispTbl	ioDispTbl			__attribute__((section(".DISP_TBL")));
/**
 IMPL
*/
static void k_jdsdisp3a_constructor(KJdsdisp3a *self)
{
	KJdsdisp3aPrivate *priv = K_JDSDISP3A_GET_PRIVATE(self);

	priv->a = 0;
}

static void k_jdsdisp3a_destructor(KJdsdisp3a *self)
{
	KJdsdisp3aPrivate *priv = K_JDSDISP3A_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 PUBLIC
*/
KJdsdisp3a* k_jdsdisp3a_new(void)
{
	KJdsdisp3a* self = k_object_new_with_private(K_TYPE_JDSDISP3A, sizeof(KJdsdisp3aPrivate));

	return self;
}
