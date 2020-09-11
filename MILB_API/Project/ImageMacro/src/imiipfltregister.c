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


#include "imiipfltregister.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImIipFltRegister, im_iip_flt_register);
#define IM_IIP_FLT_REGISTER_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipFltRegisterPrivate, IM_TYPE_IIP_FLT_REGISTER))


struct _ImIipFltRegisterPrivate
{
	kint a;
};
/**
 * IMPL
 */
static void im_iip_flt_register_constructor(ImIipFltRegister *self)
{
//	ImIipFltRegisterPrivate *priv = IM_IIP_FLT_REGISTER_GET_PRIVATE(self);
}

static void im_iip_flt_register_destructor(ImIipFltRegister *self)
{
//	ImIipFltRegisterPrivate *priv = IM_IIP_FLT_REGISTER_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
ImIipFltRegister* im_iip_flt_register_new(void)
{
	ImIipFltRegister *self = k_object_new_with_private(IM_TYPE_IIP_FLT_REGISTER, sizeof(ImIipFltRegisterPrivate));
	return self;
}
