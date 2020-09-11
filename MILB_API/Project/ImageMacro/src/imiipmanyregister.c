/*
 *
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-09
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/


#include "imiipmanyregister.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImIipManyRegister, im_iip_many_register);
#define IM_IIP_MANY_REGISTER_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipManyRegisterPrivate, IM_TYPE_IIP_MANY_REGISTER))


struct _ImIipManyRegisterPrivate
{
	kint a;
};
/**
 * IMPL
 */
static void im_iip_many_register_constructor(ImIipManyRegister *self)
{
//	ImIipManyRegisterPrivate *priv = IM_IIP_MANY_REGISTER_GET_PRIVATE(self);
}

static void im_iip_many_register_destructor(ImIipManyRegister *self)
{
//	ImIipManyRegisterPrivate *priv = IM_IIP_MANY_REGISTER_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
ImIipManyRegister* im_iip_many_register_new(void)
{
	ImIipManyRegister *self = k_object_new_with_private(IM_TYPE_IIP_MANY_REGISTER, sizeof(ImIipManyRegisterPrivate));
	return self;
}
