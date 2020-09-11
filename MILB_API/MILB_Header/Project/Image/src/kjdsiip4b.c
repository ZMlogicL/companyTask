/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsiip4b
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


#include "kjdsiip4b.h"
#include "jdsiip.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsiip4b, k_jdsiip4b);
#define K_JDSIIP4B_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsiip4bPrivate, K_TYPE_JDSIIP4B))


struct  _KJdsiip4bPrivate
{

};


volatile IoIip		ioIip		__attribute__((section(".IIP")));
volatile IoIipRam	ioIipTbl	__attribute__((section(".IIP_TBL")));
/**
 IMPL
*/
static void k_jdsiip4b_constructor(KJdsiip4b *self)
{
//	KJdsiip4bPrivate *priv = K_JDSIIP4B_GET_PRIVATE(self);
}

static void k_jdsiip4b_destructor(KJdsiip4b *self)
{
//	KJdsiip4bPrivate *priv = K_JDSIIP4B_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdsiip4b* k_jdsiip4b_new(void)
{
	KJdsiip4b* self = k_object_new_with_private(K_TYPE_JDSIIP4B, sizeof(KJdsiip4bPrivate));
	return self;
}

