/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-11
*@author            :陈倩
*@brief             :kjdsiip4b1
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


#include "kjdsiip4b1.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsiip4b1, k_jdsiip4b1);
#define K_JDSIIP4B1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsiip4b1Private, K_TYPE_JDSIIP4B1))


struct  _KJdsiip4b1Private
{

};
/**
 IMPL
*/
static void k_jdsiip4b1_constructor(KJdsiip4b1 *self)
{
//	KJdsiip4b1Private *priv = K_JDSIIP4B1_GET_PRIVATE(self);
}

static void k_jdsiip4b1_destructor(KJdsiip4b1 *self)
{
//	KJdsiip4b1Private *priv = K_JDSIIP4B1_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdsiip4b1* k_jdsiip4b1_new(void)
{
	KJdsiip4b1* self = k_object_new_with_private(K_TYPE_JDSIIP4B1, sizeof(KJdsiip4b1Private));
	return self;
}

