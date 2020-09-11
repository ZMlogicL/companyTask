/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-08
 *@author            :郑蛘钊
 *@brief             :jdsproprch
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "jdsproprch.h"

K_TYPE_DEFINE_WITH_PRIVATE(JdsproPrch, jdspro_prch);
#define JDSPRO_PRCH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsproPrchPrivate, JDSPRO_TYPE_PRCH))

struct _JdsproPrchPrivate
{

};
/**
 *IMPL
 */
static void jdspro_prch_constructor(JdsproPrch *self)
{
    //JdsproPrchPrivate *priv = JDSPRO_PRCH_GET_PRIVATE(self);
}

static void jdspro_prch_destructor(JdsproPrch *self)
{
    //JdsproPrchPrivate *priv = JDSPRO_PRCH_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
JdsproPrch* jdspro_prch_new(void)
{
    JdsproPrch* self = k_object_new_with_private(JDSPRO_TYPE_PRCH, sizeof(JdsproPrchPrivate));
    return self;
}

