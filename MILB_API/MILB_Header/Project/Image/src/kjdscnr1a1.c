/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-14
*@author            :陈倩
*@brief             :kjdscnr1a1
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


#include "kjdscnr1a1.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdscnr1a1, k_jdscnr1a1);
#define K_JDSCNR1A1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdscnr1a1Private, K_TYPE_JDSCNR1A1))


struct  _KJdscnr1a1Private
{

};


/**
 DECLS
*/

/**
 IMPL
*/
static void k_jdscnr1a1_constructor(KJdscnr1a1 *self)
{
//	KJdscnr1a1Private *priv = K_JDSCNR1A1_GET_PRIVATE(self);
}

static void k_jdscnr1a1_destructor(KJdscnr1a1 *self)
{
//	KJdscnr1a1Private *priv = K_JDSCNR1A1_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdscnr1a1* k_jdscnr1a1_new(void)
{
	KJdscnr1a1* self = k_object_new_with_private(K_TYPE_JDSCNR1A1, sizeof(KJdscnr1a1Private));
	return self;
}

