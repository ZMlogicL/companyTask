/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition JDSXH2D Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#include "kjdsxch.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsxch, k_jdsxch);

#define K_JDSXCH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsxchPrivate, K_TYPE_JDSXCH))


struct _KJdsxchPrivate
{

};


volatile IoJdsxch ioXch __attribute__((section(".Xch")));
/**
 *IMPL
 */
static void k_jdsxch_constructor(KJdsxch *self)
{
    //KJdsxchPrivate *priv = K_JDSXCH_GET_PRIVATE(self);
}

static void k_jdsxch_destructor(KJdsxch *self)
{
    //KJdsxchPrivate *priv = K_JDSXCH_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KJdsxch* k_jdsxch_new(void)
{
    KJdsxch* self = k_object_new_with_private(K_TYPE_JDSXCH, sizeof(KJdsxchPrivate));
    return self;
}
