/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition SDRAMC Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "ksdramc.h"

K_TYPE_DEFINE_WITH_PRIVATE(KSdramc, k_sdramc);
#define K_SDRAMC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KSdramcPrivate, K_TYPE_SDRAMC))

struct _KSdramcPrivate
{

};

volatile IoSdramc ioSdramc[2] __attribute__((section(".UMC")));
/**
 *IMPL
 */
static void k_sdramc_constructor(KSdramc *self)
{
    //KSdramcPrivate *priv = K_SDRAMC_GET_PRIVATE(self);
}

static void k_sdramc_destructor(KSdramc *self)
{
    //KSdramcPrivate *priv = K_SDRAMC_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KSdramc* k_sdramc_new(void)
{
    KSdramc* self = k_object_new_with_private(K_TYPE_SDRAMC, sizeof(KSdramcPrivate));
    return self;
}

