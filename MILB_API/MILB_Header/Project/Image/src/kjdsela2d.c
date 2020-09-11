/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsela2d
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


#include "kjdsela2d.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsela2d, k_jdsela2d);
#define K_JDSELA2D_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsela2dPrivate, K_TYPE_JDSELA2D))


struct  _KJdsela2dPrivate
{

};


volatile IoEla	ioEla __attribute__((section(".ELA")));
/**
 IMPL
*/
static void k_jdsela2d_constructor(KJdsela2d *self)
{
//	KJdsela2dPrivate *priv = K_JDSELA2D_GET_PRIVATE(self);
}

static void k_jdsela2d_destructor(KJdsela2d *self)
{
//	KJdsela2dPrivate *priv = K_JDSELA2D_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdsela2d* k_jdsela2d_new(void)
{
	KJdsela2d* self = k_object_new_with_private(K_TYPE_JDSELA2D, sizeof(KJdsela2dPrivate));
	return self;
}

