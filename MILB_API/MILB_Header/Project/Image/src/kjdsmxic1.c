/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-11
*@author            :陈倩
*@brief             :kjdsmxic1
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


#include "kjdsmxic1.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsmxic1, k_jdsmxic1);
#define K_JDSMXIC1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsmxic1Private, K_TYPE_JDSMXIC1))


struct  _KJdsmxic1Private
{

};
/**
 IMPL
*/
static void k_jdsmxic1_constructor(KJdsmxic1 *self)
{
//	KJdsmxic1Private *priv = K_JDSMXIC1_GET_PRIVATE(self);
}

static void k_jdsmxic1_destructor(KJdsmxic1 *self)
{
//	KJdsmxic1Private *priv = K_JDSMXIC1_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdsmxic1* k_jdsmxic1_new(void)
{
	KJdsmxic1* self = k_object_new_with_private(K_TYPE_JDSMXIC1, sizeof(KJdsmxic1Private));
	return self;
}

