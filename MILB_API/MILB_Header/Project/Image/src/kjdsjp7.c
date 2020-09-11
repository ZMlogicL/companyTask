/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsjp7
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


#include "kjdsjp7.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsjp7, k_jdsjp7);
#define K_JDSJP7_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsjp7Private, K_TYPE_JDSJP7))


struct  _KJdsjp7Private
{

};


volatile IoFJpg7cWrap		ioJpg7		__attribute__((section(".JPG7")));
/**
 IMPL
*/
static void k_jdsjp7_constructor(KJdsjp7 *self)
{
//	KJdsjp7Private *priv = K_JDSJP7_GET_PRIVATE(self);
}

static void k_jdsjp7_destructor(KJdsjp7 *self)
{
//	KJdsjp7Private *priv = K_JDSJP7_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdsjp7* k_jdsjp7_new(void)
{
	KJdsjp7* self = k_object_new_with_private(K_TYPE_JDSJP7, sizeof(KJdsjp7Private));
	return self;
}

