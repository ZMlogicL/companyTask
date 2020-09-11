/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition JMLBMH2A Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "kjmlbmh2a.h"

K_TYPE_DEFINE_WITH_PRIVATE(KJmlbmh2a, k_jmlbmh2a);
#define K_JMLBMH2A_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJmlbmh2aPrivate, K_TYPE_JMLBMH2A))

struct _KJmlbmh2aPrivate
{

};

volatile IoBmh ioBmh[2] __attribute__((section(".BMH")));
/**
 *IMPL
 */
static void k_jmlbmh2a_constructor(KJmlbmh2a *self)
{
    //KJmlbmh2aPrivate *priv = K_JMLBMH2A_GET_PRIVATE(self);
}

static void k_jmlbmh2a_destructor(KJmlbmh2a *self)
{
    //KJmlbmh2aPrivate *priv = K_JMLBMH2A_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KJmlbmh2a* k_jmlbmh2a_new(void)
{
    KJmlbmh2a* self = k_object_new_with_private(K_TYPE_JMLBMH2A, sizeof(KJmlbmh2aPrivate));
    return self;
}

