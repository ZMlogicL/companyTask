/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition JDSSPR5C Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#include "kjdsrdma.h"


K_TYPE_DEFINE_WITH_PRIVATE(KJdsrdma, k_jdsrdma);

#define K_JDSRDMA_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsrdmaPrivate, K_TYPE_JDSRDMA))


struct _KJdsrdmaPrivate
{

};


volatile IoRdma ioRdma __attribute__((section(".RDMA")));
/**
 *IMPL
 */
static void k_jdsrdma_constructor(KJdsrdma *self)
{
    //KJdsrdmaPrivate *priv = K_JDSRDMA_GET_PRIVATE(self);
}

static void k_jdsrdma_destructor(KJdsrdma *self)
{
    //KJdsrdmaPrivate *priv = K_JDSRDMA_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KJdsrdma* k_jdsrdma_new(void)
{
    KJdsrdma* self = k_object_new_with_private(K_TYPE_JDSRDMA, sizeof(KJdsrdmaPrivate));
    return self;
}
