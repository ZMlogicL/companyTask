/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-04
 *@author            :郑蛘钊
 *@brief             :Definition MCC (Multi-Core Controller) I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "kmcc.h"

K_TYPE_DEFINE_WITH_PRIVATE(KMcc, k_mcc);
#define K_MCC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KMccPrivate, K_TYPE_MCC))

struct _KMccPrivate
{

};

volatile IoMcc ioMcc __attribute__((section(".MCC")));
/**
 *IMPL
 */
static void k_mcc_constructor(KMcc *self)
{
//	KMccPrivate *priv = K_MCC_GET_PRIVATE(self);
}

static void k_mcc_destructor(KMcc *self)
{
//	KMccPrivate *priv = K_MCC_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KMcc* k_mcc_new(void)
{
    KMcc* self = k_object_new_with_private(K_TYPE_MCC, sizeof(KMccPrivate));
    return self;
}
