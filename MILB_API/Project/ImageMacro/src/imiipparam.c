/*
 *
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-08
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/


#include "imiipparam.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImIipParam, im_iip_param);
#define IM_IIP_PARAM_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipParamPrivate, IM_TYPE_IIP_PARAM	))


struct _ImIipParamPrivate
{
	kint a;
};
/**
 * IMPL
 */
static void im_iip_param_constructor(ImIipParam *self)
{
//	ImIipParamPrivate *priv = IM_IIP_PARAM_GET_PRIVATE(self);
}

static void im_iip_param_destructor(ImIipParam *self)
{
//	ImIipParamPrivate *priv = IM_IIP_PARAM_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
ImIipParam* im_iip_param_new(void)
{
	ImIipParam *self = k_object_new_with_private(IM_TYPE_IIP_PARAM, sizeof(ImIipParamPrivate));
	return self;
}
