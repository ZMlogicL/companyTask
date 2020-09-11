/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-11
 *@author            :郑蛘钊
 *@brief             :ksdramc2
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "ksdramc2.h"

K_TYPE_DEFINE_WITH_PRIVATE(KSdramc2, k_sdramc2);
#define K_SDRAMC2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KSdramc2Private, K_TYPE_SDRAMC2))

struct _KSdramc2Private
{

};
/**
 *IMPL
 */
static void k_sdramc2_constructor(KSdramc2 *self)
{
    //KSdramc2Private *priv = K_SDRAMC2_GET_PRIVATE(self);
}

static void k_sdramc2_destructor(KSdramc2 *self)
{
    //KSdramc2Private *priv = K_SDRAMC2_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KSdramc2* k_sdramc2_new(void)
{
    KSdramc2* self = k_object_new_with_private(K_TYPE_SDRAMC2, sizeof(KSdramc2Private));
    return self;
}

