/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-04
 *@author            :郑蛘钊
 *@brief             :kexiu
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "kexiu.h"

K_TYPE_DEFINE_WITH_PRIVATE(KExiu, k_exiu);

#define K_EXIU_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KExiuPrivate, K_TYPE_EXIU))


struct _KExiuPrivate
{

};

volatile IoExiu ioExiu __attribute__((section(".EXIU")));
/**
 *IMPL
 */
static void k_exiu_constructor(KExiu *self)
{
//	KExiuPrivate *priv = K_EXIU_GET_PRIVATE(self);
}

static void k_exiu_destructor(KExiu *self)
{
//	KExiuPrivate *priv = K_EXIU_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KExiu* k_exiu_new(void)
{
    KExiu* self = k_object_new_with_private(K_TYPE_EXIU, sizeof(KExiuPrivate));
    return self;
}
