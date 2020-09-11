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


#include "imiipgpcparameter.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImIipGpcParameter, im_iip_gpc_parameter);
#define IM_IIP_GPC_PARAMETER_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipGpcParameterPrivate, IM_TYPE_IIP_GPC_PARAMETER))


struct _ImIipGpcParameterPrivate
{

};
/**
 * IMPL
 */
static void im_iip_gpc_parameter_constructor(ImIipGpcParameter *self)
{
//	ImIipGpcParameterPrivate *priv = IM_IIP_GPC_PARAMETER_GET_PRIVATE(self);
}

static void im_iip_gpc_parameter_destructor(ImIipGpcParameter *self)
{
//	ImIipGpcParameterPrivate *priv = IM_IIP_GPC_PARAMETER_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
ImIipGpcParameter* im_iip_gpc_parameter_new(void)
{
	ImIipGpcParameter *self = k_object_new_with_private(IM_TYPE_IIP_GPC_PARAMETER, sizeof(ImIipGpcParameterPrivate));
	return self;
}

