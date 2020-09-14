/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition JDSR2Y_F2E Macro I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#include "jdsr2yf2e.h"


K_TYPE_DEFINE_WITH_PRIVATE(Jdsr2yF2e, jdsr2y_f2e);

#define JDSR2Y_F2E_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), Jdsr2yF2ePrivate, JDSR2Y_TYPE_F2E))


struct _Jdsr2yF2ePrivate
{

};


volatile IoR2y ioR2yP1 __attribute__((section(".R2Y_P1")));
volatile IoR2y ioR2yP2 __attribute__((section(".R2Y_P2")));
volatile IoR2y ioR2yP3 __attribute__((section(".R2Y_P3")));
volatile IoR2ySram ioR2yTblP1 __attribute__((section(".R2Y_TBL_P1")));
volatile IoR2ySram ioR2yTblP2 __attribute__((section(".R2Y_TBL_P2")));
volatile IoR2ySram ioR2yTblP3 __attribute__((section(".R2Y_TBL_P3")));
/**
 *IMPL
 */
static void jdsr2y_f2e_constructor(Jdsr2yF2e *self)
{
    //Jdsr2yF2ePrivate *priv = JDSR2Y_F2E_GET_PRIVATE(self);
}

static void jdsr2y_f2e_destructor(Jdsr2yF2e *self)
{
    //Jdsr2yF2ePrivate *priv = JDSR2Y_F2E_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
Jdsr2yF2e* jdsr2y_f2e_new(void)
{
    Jdsr2yF2e* self = k_object_new_with_private(JDSR2Y_TYPE_F2E, sizeof(Jdsr2yF2ePrivate));
    return self;
}
