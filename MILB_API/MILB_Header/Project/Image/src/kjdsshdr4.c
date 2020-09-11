/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-10
 *@author            :郑蛘钊
 *@brief             :kjdsshdr4
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "kjdsshdr4.h"

K_TYPE_DEFINE_WITH_PRIVATE(KJdsshdr4, k_jdsshdr4);
#define K_JDSSHDR4_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsshdr4Private, K_TYPE_JDSSHDR4))

struct _KJdsshdr4Private
{

};
/**
 *IMPL
 */
static void k_jdsshdr4_constructor(KJdsshdr4 *self)
{
    //KJdsshdr4Private *priv = K_JDSSHDR4_GET_PRIVATE(self);
}

static void k_jdsshdr4_destructor(KJdsshdr4 *self)
{
    //KJdsshdr4Private *priv = K_JDSSHDR4_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KJdsshdr4* k_jdsshdr4_new(void)
{
    KJdsshdr4* self = k_object_new_with_private(K_TYPE_JDSSHDR4, sizeof(KJdsshdr4Private));
    return self;
}

