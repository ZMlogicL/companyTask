/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-04
 *@author            :郑蛘钊
 *@brief             :kgic
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "kgic.h"

K_TYPE_DEFINE_WITH_PRIVATE(KGic, k_gic);
#define K_GIC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KGicPrivate, K_TYPE_GIC))

struct _KGicPrivate
{

};

volatile IoGicDist ioGicDist __attribute__((section(".GIC_DIST")));
volatile IoGicCpu ioGicCpu __attribute__((section(".GIC_CPU")));
/**
 *IMPL
 */
static void k_gic_constructor(KGic *self)
{
//	KGicPrivate *priv = K_GIC_GET_PRIVATE(self);
}

static void k_gic_destructor(KGic *self)
{
//	KGicPrivate *priv = K_GIC_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KGic* k_gic_new(void)
{
    KGic* self = k_object_new_with_private(K_TYPE_GIC, sizeof(KGicPrivate));
    return self;
}
