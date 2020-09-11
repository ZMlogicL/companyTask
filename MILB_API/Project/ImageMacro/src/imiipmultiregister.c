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


#include "imiipmultiregister.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImIipMultiRegister, im_iip_multi_register);
#define IM_IIP_MULTI_REGISTER_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipMultiRegisterPrivate, IM_TYPE_IIP_MULTI_REGISTER))


struct _ImIipMultiRegisterPrivate
{
	kint a;
};
/**
 * IMPL
 */
static void im_iip_multi_register_constructor(ImIipMultiRegister *self)
{
//	ImIipMultiRegisterPrivate *priv = IM_IIP_MULTI_REGISTER_GET_PRIVATE(self);
}

static void im_iip_multi_register_destructor(ImIipMultiRegister *self)
{
//	ImIipMultiRegisterPrivate *priv = IM_IIP_MULTI_REGISTER_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
ImIipMultiRegister* im_iip_multi_register_new(void)
{
	ImIipMultiRegister *self = k_object_new_with_private(IM_TYPE_IIP_MULTI_REGISTER, sizeof(ImIipMultiRegisterPrivate));
	return self;
}

