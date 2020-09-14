/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition JDSRAW3A Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#include "kjdsraw3a.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsraw3a, k_jdsraw3a);

#define K_JDSRAW3A_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsraw3aPrivate, K_TYPE_JDSRAW3A))


struct _KJdsraw3aPrivate
{

};


volatile IoJdsraw ioRaw __attribute__((section(".RAW")));
/**
 *IMPL
 */
static void k_jdsraw3a_constructor(KJdsraw3a *self)
{
    //KJdsraw3aPrivate *priv = K_JDSRAW3A_GET_PRIVATE(self);
}

static void k_jdsraw3a_destructor(KJdsraw3a *self)
{
    //KJdsraw3aPrivate *priv = K_JDSRAW3A_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KJdsraw3a* k_jdsraw3a_new(void)
{
    KJdsraw3a* self = k_object_new_with_private(K_TYPE_JDSRAW3A, sizeof(KJdsraw3aPrivate));
    return self;
}
