/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition JDSSHDR Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "kjdsshdr.h"

K_TYPE_DEFINE_WITH_PRIVATE(KJdsshdr, k_jdsshdr);
#define K_JDSSHDR_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KJdsshdrPrivate, K_TYPE_JDSSHDR))

struct _KJdsshdrPrivate
{

};

volatile IoJdsshdr ioShdr __attribute__((section(".SHDR")));
volatile IoJdsshdrTbl ioShdrTbl __attribute__((section(".SHDR_TBL")));
/**
 *IMPL
 */
static void k_jdsshdr_constructor(KJdsshdr *self)
{
    //KJdsshdrPrivate *priv = K_JDSSHDR_GET_PRIVATE(self);
}

static void k_jdsshdr_destructor(KJdsshdr *self)
{
    //KJdsshdrPrivate *priv = K_JDSSHDR_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KJdsshdr* k_jdsshdr_new(void)
{
    KJdsshdr* self = k_object_new_with_private(K_TYPE_JDSSHDR, sizeof(KJdsshdrPrivate));
    return self;
}

