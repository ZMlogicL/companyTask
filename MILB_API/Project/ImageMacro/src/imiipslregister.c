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


#include "imiipslregister.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImIipSlRegister, im_iip_sl_register);
#define IM_IIP_SL_REGISTER_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipSlRegisterPrivate, IM_TYPE_IIP_SL_REGISTER))


struct _ImIipSlRegisterPrivate
{
	kint a;
};


/**
 * IMPL
 */
static void im_iip_sl_register_constructor(ImIipSlRegister *self)
{
//	ImIipSlRegisterPrivate *priv = IM_IIP_SL_REGISTER_GET_PRIVATE(self);
}

static void im_iip_sl_register_destructor(ImIipSlRegister *self)
{
//	ImIipSlRegisterPrivate *priv = IM_IIP_SL_REGISTER_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
ImIipSlRegister* im_iip_sl_register_new(void)
{
	ImIipSlRegister *self = k_object_new_with_private(IM_TYPE_IIP_SL_REGISTER, sizeof(ImIipSlRegisterPrivate));
	return self;
}
