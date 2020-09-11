/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-05
*@author            :陈倩
*@brief             :kjdscnr1a
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


#include "kjdscnr1a.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdscnr1a, k_jdscnr1a);
#define K_JDSCNR1A_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdscnr1aPrivate, K_TYPE_JDSCNR1A))


struct  _KJdscnr1aPrivate
{

};


volatile  IoCnrReg		ioCnr1		__attribute__((section(".CNR_1")));
volatile  IoCnrReg		ioCnr2		__attribute__((section(".CNR_2")));
volatile  IoCnrReg		ioCnr3		__attribute__((section(".CNR_3")));
/**
 IMPL
*/
static void k_jdscnr1a_constructor(KJdscnr1a *self)
{
//	KJdscnr1aPrivate *priv = K_JDSCNR1A_GET_PRIVATE(self);
}

static void k_jdscnr1a_destructor(KJdscnr1a *self)
{
//	KJdscnr1aPrivate *priv = K_JDSCNR1A_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdscnr1a* k_jdscnr1a_new(void)
{
	KJdscnr1a* self = k_object_new_with_private(K_TYPE_JDSCNR1A, sizeof(KJdscnr1aPrivate));
	return self;
}

