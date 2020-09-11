/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsltm1a
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*3、
*4、
*5、
*@version
*
*/


#include "kjdsltm1a.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsltm1a, k_jdsltm1a);
#define K_JDSLTM1A_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsltm1aPrivate, K_TYPE_JDSLTM1A))


struct  _KJdsltm1aPrivate
{

};


volatile IoLtmTop		ioLtmP1		__attribute__((section(".LTM_P1")));;
volatile IoLtmTop		ioLtmP2		__attribute__((section(".LTM_P2")));;
volatile IoLtmTop		ioLtmP3		__attribute__((section(".LTM_P3")));;
volatile struct LoLtmSram		ioLtmTblP1	__attribute__((section(".LTM_TBL_P1")));
volatile struct LoLtmSram		ioLtmTblP2	__attribute__((section(".LTM_TBL_P2")));
volatile struct LoLtmSram		ioLtmTblP3	__attribute__((section(".LTM_TBL_P3")));
/**
 IMPL
*/
static void k_jdsltm1a_constructor(KJdsltm1a *self)
{
//	KJdsltm1aPrivate *priv = K_JDSLTM1A_GET_PRIVATE(self);
}

static void k_jdsltm1a_destructor(KJdsltm1a *self)
{
//	KJdsltm1aPrivate *priv = K_JDSLTM1A_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdsltm1a* k_jdsltm1a_new(void)
{
	KJdsltm1a* self = k_object_new_with_private(K_TYPE_JDSLTM1A, sizeof(KJdsltm1aPrivate));
	return self;
}

