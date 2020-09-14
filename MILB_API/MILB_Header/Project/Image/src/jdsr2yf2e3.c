/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-11
 *@author            :郑蛘钊
 *@brief             :jdsr2yf2e3
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#include "jdsr2yf2e3.h"


K_TYPE_DEFINE_WITH_PRIVATE(Jdsr2yF2e3, jdsr2y_f2e3);

#define JDSR2Y_F2E3_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), Jdsr2yF2e3Private, JDSR2Y_TYPE_F2E3))


struct _Jdsr2yF2e3Private
{

};
/**
 *IMPL
 */
static void jdsr2y_f2e3_constructor(Jdsr2yF2e3 *self)
{
    //Jdsr2yF2e3Private *priv = JDSR2Y_F2E3_GET_PRIVATE(self);
}

static void jdsr2y_f2e3_destructor(Jdsr2yF2e3 *self)
{
    //Jdsr2yF2e3Private *priv = JDSR2Y_F2E3_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
Jdsr2yF2e3* jdsr2y_f2e3_new(void)
{
    Jdsr2yF2e3* self = k_object_new_with_private(JDSR2Y_TYPE_F2E3, sizeof(Jdsr2yF2e3Private));
    return self;
}
