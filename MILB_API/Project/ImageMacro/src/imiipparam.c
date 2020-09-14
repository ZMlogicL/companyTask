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


G_DEFINE_TYPE(ImIipParam, im_iip_param, G_TYPE_OBJECT);
#define IM_IIP_PARAM_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_IIP_PARAM, ImIipParamPrivate));


struct _ImIipParamPrivate
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
static void 		im_iip_param_class_init(ImIipParamClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_aim_private(klass, sizeof(ImIipParamPrivate));
}

static void 		im_iip_param_init(ImIipParam *self)
{
	ImIipParamPrivate *priv = IM_IIP_PARAM_GET_PRIVATE(self);
}

static void 		dispose_od(GObject *object)
{
	ImIipParamPrivate *priv = IM_IIP_PARAM_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_iip_param_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	ImIipParamPrivate *priv = IM_IIP_PARAM_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_iip_param_parent_class) -> dispose(object);
}
/**
 * PUBLIC
 */
ImIipParam* 		im_iip_param_new(void)
{
	ImIipParam *self = g_object_new(IM_TYPE_IIP_PARAM, NULL);
	return self;
}
