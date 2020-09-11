/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsimg
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


#include "kjdsimg.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsimg, k_jdsimg);
#define K_JDSIMG_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsimgPrivate, K_TYPE_JDSIMG))


struct  _KJdsimgPrivate
{

};


volatile IoImg		ioImg		__attribute__((section(".IMG")));
/**
 IMPL
*/
static void k_jdsimg_constructor(KJdsimg *self)
{
//	KJdsimgPrivate *priv = K_JDSIMG_GET_PRIVATE(self);
}

static void k_jdsimg_destructor(KJdsimg *self)
{
//	KJdsimgPrivate *priv = K_JDSIMG_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdsimg* k_jdsimg_new(void)
{
	KJdsimg* self = k_object_new_with_private(K_TYPE_JDSIMG, sizeof(KJdsimgPrivate));
	return self;
}

