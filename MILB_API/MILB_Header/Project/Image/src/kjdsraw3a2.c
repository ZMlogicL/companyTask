/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-11
 *@author            :郑蛘钊
 *@brief             :kjdsraw3a2
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "kjdsraw3a2.h"

K_TYPE_DEFINE_WITH_PRIVATE(KJdsraw3a2, k_jdsraw3a2);
#define K_JDSRAW3A2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsraw3a2Private, K_TYPE_JDSRAW3A2))

struct _KJdsraw3a2Private
{

};
/**
 *IMPL
 */
static void k_jdsraw3a2_constructor(KJdsraw3a2 *self)
{
    //KJdsraw3a2Private *priv = K_JDSRAW3A2_GET_PRIVATE(self);
}

static void k_jdsraw3a2_destructor(KJdsraw3a2 *self)
{
    //KJdsraw3a2Private *priv = K_JDSRAW3A2_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KJdsraw3a2* k_jdsraw3a2_new(void)
{
    KJdsraw3a2* self = k_object_new_with_private(K_TYPE_JDSRAW3A2, sizeof(KJdsraw3a2Private));
    return self;
}

