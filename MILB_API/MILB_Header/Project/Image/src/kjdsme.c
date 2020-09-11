/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsme
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


#include "kjdsme.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsme, k_jdsme);
#define K_JDSME_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsmePrivate, K_TYPE_JDSME))


struct  _KJdsmePrivate
{

};


volatile IoJdsme		ioMe			__attribute__((section(".ME")));
/**
 IMPL
*/
static void k_jdsme_constructor(KJdsme *self)
{
//	KJdsmePrivate *priv = K_JDSME_GET_PRIVATE(self);
}

static void k_jdsme_destructor(KJdsme *self)
{
//	KJdsmePrivate *priv = K_JDSME_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdsme* k_jdsme_new(void)
{
	KJdsme* self = k_object_new_with_private(K_TYPE_JDSME, sizeof(KJdsmePrivate));
	return self;
}

