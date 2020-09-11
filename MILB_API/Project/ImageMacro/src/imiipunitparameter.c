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


#include "imiipunitparameter.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImIipUnitParameter, im_iip_unit_parameter);
#define IM_IIP_UNIT_PARAMETER_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipUnitParameterPrivate, IM_TYPE_IIP_UNIT_PARAMETER))


struct _ImIipUnitParameterPrivate
{
	kint a;
};


/**
 * IMPL
 */
static void im_iip_unit_parameter_constructor(ImIipUnitParameter *self)
{
//	ImIipUnitParameterPrivate *priv = IM_IIP_UNIT_PARAMETER_GET_PRIVATE(self);
}

static void im_iip_unit_parameter_destructor(ImIipUnitParameter *self)
{
//	ImIipUnitParameterPrivate *priv = IM_IIP_UNIT_PARAMETER_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
ImIipUnitParameter* im_iip_unit_parameter_new(void)
{
	ImIipUnitParameter *self = k_object_new_with_private(IM_TYPE_IIP_UNIT_PARAMETER, sizeof(ImIipUnitParameterPrivate));
	return self;
}
