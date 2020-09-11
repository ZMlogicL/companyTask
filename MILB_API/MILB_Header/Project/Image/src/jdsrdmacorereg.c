/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-08
 *@author            :郑蛘钊
 *@brief             :jdsrdmacorereg
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "jdsrdmacorereg.h"

K_TYPE_DEFINE_WITH_PRIVATE(JdsrdmaCoreReg, jdsrdma_core_reg);
#define JDSRDMA_CORE_REG_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsrdmaCoreRegPrivate, JDSRDMA_TYPE_CORE_REG))

struct _JdsrdmaCoreRegPrivate
{

};
/**
 *IMPL
 */
static void jdsrdma_core_reg_constructor(JdsrdmaCoreReg *self)
{
    //JdsrdmaCoreRegPrivate *priv = JDSRDMA_CORE_REG_GET_PRIVATE(self);
}

static void jdsrdma_core_reg_destructor(JdsrdmaCoreReg *self)
{
    //JdsrdmaCoreRegPrivate *priv = JDSRDMA_CORE_REG_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
JdsrdmaCoreReg* jdsrdma_core_reg_new(void)
{
    JdsrdmaCoreReg* self = k_object_new_with_private(JDSRDMA_TYPE_CORE_REG, sizeof(JdsrdmaCoreRegPrivate));
    return self;
}

