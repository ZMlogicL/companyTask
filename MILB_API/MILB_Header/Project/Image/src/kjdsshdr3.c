/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-07
 *@author            :郑蛘钊
 *@brief             :kjdsshdr3
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#include "kjdsshdr3.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsshdr3, k_jdsshdr3);

#define K_JDSSHDR3_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsshdr3Private, K_TYPE_JDSSHDR3))


struct _KJdsshdr3Private
{

};
/**
 *IMPL
 */
static void k_jdsshdr3_constructor(KJdsshdr3 *self)
{
    //KJdsshdr3Private *priv = K_JDSSHDR3_GET_PRIVATE(self);
}

static void k_jdsshdr3_destructor(KJdsshdr3 *self)
{
    //KJdsshdr3Private *priv = K_JDSSHDR3_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KJdsshdr3* k_jdsshdr3_new(void)
{
    KJdsshdr3* self = k_object_new_with_private(K_TYPE_JDSSHDR3, sizeof(KJdsshdr3Private));
    return self;
}
