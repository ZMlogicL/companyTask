/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-07
 *@author            :郑蛘钊
 *@brief             :jdsr2yf2e2
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#include "jdsr2yf2e2.h"


K_TYPE_DEFINE_WITH_PRIVATE(Jdsr2yF2e2, jdsr2y_f2e2);

#define JDSR2Y_F2E2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), Jdsr2yF2e2Private, JDSR2Y_TYPE_F2E2))


struct _Jdsr2yF2e2Private
{

};
/**
 *IMPL
 */
static void jdsr2y_f2e2_constructor(Jdsr2yF2e2 *self)
{
    //Jdsr2yF2e2Private *priv = JDSR2Y_F2E2_GET_PRIVATE(self);
}

static void jdsr2y_f2e2_destructor(Jdsr2yF2e2 *self)
{
    //Jdsr2yF2e2Private *priv = JDSR2Y_F2E2_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
Jdsr2yF2e2* jdsr2y_f2e2_new(void)
{
    Jdsr2yF2e2* self = k_object_new_with_private(JDSR2Y_TYPE_F2E2, sizeof(Jdsr2yF2e2Private));
    return self;
}
