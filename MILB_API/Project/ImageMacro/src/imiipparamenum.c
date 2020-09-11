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


#include "imiipparamenum.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImIipParamEnum, im_iip_param_enum);
#define IM_IIP_PARAM_ENUM_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipParamEnumPrivate, IM_TYPE_IIP_PARAM_ENUM	))


struct _ImIipParamEnumPrivate
{
	kint a;
};
/**
 * IMPL
 */
static void im_iip_param_enum_constructor(ImIipParamEnum *self)
{
//	ImIipParamEnumPrivate *priv = IM_IIP_PARAM_ENUM_GET_PRIVATE(self);
}

static void im_iip_param_enum_destructor(ImIipParamEnum *self)
{
//	ImIipParamEnumPrivate *priv = IM_IIP_PARAM_ENUM_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
ImIipParamEnum* im_iip_param_enum_new(void)
{
	ImIipParamEnum *self = k_object_new_with_private(IM_TYPE_IIP_PARAM_ENUM, sizeof(ImIipParamEnumPrivate));
	return self;
}
