/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-04
*@author            :陈倩
*@brief             :kjmiluart
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


#include "kjmiluart.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJmiluart, k_jmiluart);
#define K_JMILUART_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJmiluartPrivate, K_TYPE_JMILUART))


struct  _KJmiluartPrivate
{

};


volatile IoUsio          ioUsio     __attribute__((section(".USIO")));
/**
 IMPL
*/
static void k_jmiluart_constructor(KJmiluart *self)
{
//	KJmiluartPrivate *priv = K_JMILUART_GET_PRIVATE(self);
}

static void k_jmiluart_destructor(KJmiluart *self)
{
//	KJmiluartPrivate *priv = K_JMILUART_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJmiluart* k_jmiluart_new(void)
{
	KJmiluart* self = k_object_new_with_private(K_TYPE_JMILUART, sizeof(KJmiluartPrivate));
	return self;
}

