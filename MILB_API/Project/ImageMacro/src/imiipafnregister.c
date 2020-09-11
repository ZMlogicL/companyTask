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


#include "imiipafnregister.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImIipAfnRegister, im_iip_afn_register);
#define IM_IIP_AFN_REGISTER_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipAfnRegisterPrivate, IM_TYPE_IIP_AFN_REGISTER	))


struct _ImIipAfnRegisterPrivate
{
	kint a;
};
/**
 * IMPL
 */
static void im_iip_afn_register_constructor(ImIipAfnRegister *self)
{
//	ImIipAfnRegisterPrivate *priv = IM_IIP_AFN_REGISTER_GET_PRIVATE(self);
}

static void im_iip_afn_register_destructor(ImIipAfnRegister *self)
{
//	ImIipAfnRegisterPrivate *priv = IM_IIP_AFN_REGISTER_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
ImIipAfnRegister* im_iip_afn_register_new(void)
{
	ImIipAfnRegister *self = k_object_new_with_private(IM_TYPE_IIP_AFN_REGISTER, sizeof(ImIipAfnRegisterPrivate));
	return self;
}
