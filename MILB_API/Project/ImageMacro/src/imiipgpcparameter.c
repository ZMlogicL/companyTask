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


G_DEFINE_TYPE(ImIipGpcParameter, im_iip_gpc_parameter, G_TYPE_OBJECT);
#define IM_IIP_GPC_PARAMETER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_IIP_GPC_PARAMETER, ImIipGpcParameterPrivate));


struct _ImIipGpcParameterPrivate
{

};
/**
 *DECLS
 */
static void 		dispose_od(GObject *object);
static void 		finalize_od(GObject *object);
/**
 *IMPL
 */
static void 		im_iip_gpc_parameter_class_init(ImIipGpcParameterClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_aim_private(klass, sizeof(ImIipGpcParameterPrivate));
}

static void 		im_iip_gpc_parameter_init(ImIipGpcParameter *self)
{
	ImIipGpcParameterPrivate *priv = IM_IIP_GPC_PARAMETER_GET_PRIVATE(self);
}

static void 		dispose_od(GObject *object)
{
	ImIipGpcParameterPrivate *priv = IM_IIP_GPC_PARAMETER_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_iip_gpc_parameter_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	ImIipGpcParameterPrivate *priv = IM_IIP_GPC_PARAMETER_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_iip_gpc_parameter_parent_class) -> dispose(object);
}

/**
 * PUBLIC
 */
ImIipGpcParameter* 		im_iip_gpc_parameter_new(void)
{
	ImIipGpcParameter *self = g_object_new(IM_TYPE_IIP_GPC_PARAMETER, NULL);
	return self;
}


