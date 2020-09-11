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


#include "imiipfrectregister.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImIipFrectRegister, im_iip_frect_register);
#define IM_IIP_FRECT_REGISTER_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipFrectRegisterPrivate, IM_TYPE_IIP_FRECT_REGISTER))


struct _ImIipFrectRegisterPrivate
{
	kint a;
};
/**
 * IMPL
 */
static void im_iip_frect_register_constructor(ImIipFrectRegister *self)
{
//	ImIipFrectRegisterPrivate *priv = IM_IIP_FRECT_REGISTER_GET_PRIVATE(self);
}

static void im_iip_frect_register_destructor(ImIipFrectRegister *self)
{
//	ImIipFrectRegisterPrivate *priv = IM_IIP_FRECT_REGISTER_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
ImIipFrectRegister* im_iip_frect_register_new(void)
{
	ImIipFrectRegister *self = k_object_new_with_private(IM_TYPE_IIP_FRECT_REGISTER, sizeof(ImIipFrectRegisterPrivate));
	return self;
}

