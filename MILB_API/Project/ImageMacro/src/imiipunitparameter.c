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


G_DEFINE_TYPE(ImIipUnitParameter, im_iip_unit_parameter, G_TYPE_OBJECT);
#define IM_IIP_UNIT_PARAMETER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_IIP_UNIT_PARAMETER, ImIipUnitParameterPrivate));


struct _ImIipUnitParameterPrivate
{
	gint a;
};


/**
 *DECLS
 */
static void 		dispose_od(GObject *object);
static void 		finalize_od(GObject *object);
/**
 *IMPL
 */
static void 		im_iip_unit_parameter_class_init(ImIipUnitParameterClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_aim_private(klass, sizeof(ImIipUnitParameterPrivate));
}

static void 		im_iip_unit_parameter_init(ImIipUnitParameter *self)
{
	ImIipUnitParameterPrivate *priv = IM_IIP_UNIT_PARAMETER_GET_PRIVATE(self);
}

static void 		dispose_od(GObject *object)
{
	ImIipUnitParameterPrivate *priv = IM_IIP_UNIT_PARAMETER_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_iip_unit_parameter_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	ImIipUnitParameterPrivate *priv = IM_IIP_UNIT_PARAMETER_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_iip_unit_parameter_parent_class) -> dispose(object);
}
/**
 * PUBLIC
 */
ImIipUnitParameter* 		im_iip_unit_parameter_new(void)
{
	ImIipUnitParameter *self = g_object_new(IM_TYPE_IIP_UNIT_PARAMETER, NULL);
	return self;
}


