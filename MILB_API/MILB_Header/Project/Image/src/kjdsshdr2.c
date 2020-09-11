/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-07
 *@author            :郑蛘钊
 *@brief             :kjdsshdr2
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "kjdsshdr2.h"

K_TYPE_DEFINE_WITH_PRIVATE(KJdsshdr2, k_jdsshdr2);
#define K_JDSSHDR2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsshdr2Private, K_TYPE_JDSSHDR2))

struct _KJdsshdr2Private
{

};
/**
 *IMPL
 */
static void k_jdsshdr2_constructor(KJdsshdr2 *self)
{
    //KJdsshdr2Private *priv = K_JDSSHDR2_GET_PRIVATE(self);
}

static void k_jdsshdr2_destructor(KJdsshdr2 *self)
{
    //KJdsshdr2Private *priv = K_JDSSHDR2_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KJdsshdr2* k_jdsshdr2_new(void)
{
    KJdsshdr2* self = k_object_new_with_private(K_TYPE_JDSSHDR2, sizeof(KJdsshdr2Private));
    return self;
}

