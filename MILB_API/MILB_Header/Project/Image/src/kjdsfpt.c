/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsfpt
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


#include "kjdsfpt.h"
#include "_jdsfpt.h"
#include "_jdsfpt_ahb.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsfpt, k_jdsfpt);
#define K_JDSFPT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsfptPrivate, K_TYPE_JDSFPT))


struct  _KJdsfptPrivate
{

};


volatile IoJdsfpt ioFpt[2] __attribute__((section(".FPT")));
volatile IoJdsfptAhb ioFptAhb[2] __attribute__((section(".FPT_AHB")));
/**
 IMPL
*/
static void k_jdsfpt_constructor(KJdsfpt *self)
{
//	KJdsfptPrivate *priv = K_JDSFPT_GET_PRIVATE(self);
}

static void k_jdsfpt_destructor(KJdsfpt *self)
{
//	KJdsfptPrivate *priv = K_JDSFPT_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
KJdsfpt* k_jdsfpt_new(void)
{
	KJdsfpt* self = k_object_new_with_private(K_TYPE_JDSFPT, sizeof(KJdsfptPrivate));
	return self;
}

