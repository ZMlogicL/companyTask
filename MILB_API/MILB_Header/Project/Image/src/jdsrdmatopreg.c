/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-08
 *@author            :郑蛘钊
 *@brief             :jdsrdmatopreg
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#include "jdsrdmatopreg.h"


K_TYPE_DEFINE_WITH_PRIVATE(JdsrdmaTopReg, jdsrdma_top_reg);

#define JDSRDMA_TOP_REG_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsrdmaTopRegPrivate, JDSRDMA_TYPE_TOP_REG))


struct _JdsrdmaTopRegPrivate
{

};
/**
 *IMPL
 */
static void jdsrdma_top_reg_constructor(JdsrdmaTopReg *self)
{
    //JdsrdmaTopRegPrivate *priv = JDSRDMA_TOP_REG_GET_PRIVATE(self);
}

static void jdsrdma_top_reg_destructor(JdsrdmaTopReg *self)
{
    //JdsrdmaTopRegPrivate *priv = JDSRDMA_TOP_REG_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
JdsrdmaTopReg* jdsrdma_top_reg_new(void)
{
    JdsrdmaTopReg* self = k_object_new_with_private(JDSRDMA_TYPE_TOP_REG, sizeof(JdsrdmaTopRegPrivate));
    return self;
}
