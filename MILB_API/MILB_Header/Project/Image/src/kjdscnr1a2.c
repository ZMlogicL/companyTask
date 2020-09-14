/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-14
*@author            :陈倩
*@brief             :kjdscnr1a2
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


#include "kjdscnr1a2.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdscnr1a2, k_jdscnr1a2);
#define K_JDSCNR1A2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdscnr1a2Private, K_TYPE_JDSCNR1A2))


struct  _KJdscnr1a2Private
{

};


/**
 DECLS
*/

/**
 IMPL
*/
static void k_jdscnr1a2_constructor(KJdscnr1a2 *self)
{
//	KJdscnr1a2Private *priv = K_JDSCNR1A2_GET_PRIVATE(self);
}

static void k_jdscnr1a2_destructor(KJdscnr1a2 *self)
{
//	KJdscnr1a2Private *priv = K_JDSCNR1A2_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdscnr1a2* k_jdscnr1a2_new(void)
{
	KJdscnr1a2* self = k_object_new_with_private(K_TYPE_JDSCNR1A2, sizeof(KJdscnr1a2Private));
	return self;
}

