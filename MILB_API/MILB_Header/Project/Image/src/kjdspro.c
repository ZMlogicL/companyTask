/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdspro
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


#include "kjdspro.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdspro, k_jdspro);
#define K_JDSPRO_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsproPrivate, K_TYPE_JDSPRO))


struct  _KJdsproPrivate
{

};


volatile IoPro		ioPro		__attribute__((section(".PRO")));
volatile IoProTbl	ioProTbl	__attribute__((section(".PRO_TBL")));
/**
 IMPL
*/
static void k_jdspro_constructor(KJdspro *self)
{
//	KJdsproPrivate *priv = K_JDSPRO_GET_PRIVATE(self);
}

static void k_jdspro_destructor(KJdspro *self)
{
//	KJdsproPrivate *priv = K_JDSPRO_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdspro* k_jdspro_new(void)
{
	KJdspro* self = k_object_new_with_private(K_TYPE_JDSPRO, sizeof(KJdsproPrivate));
	return self;
}

