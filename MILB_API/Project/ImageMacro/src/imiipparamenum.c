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


G_DEFINE_TYPE(ImIipParamEnum, im_iip_param_enum, G_TYPE_OBJECT);
#define IM_IIP_PARAM_ENUM_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_IIP_PARAM_ENUM, ImIipParamEnumPrivate));


struct _ImIipParamEnumPrivate
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
static void 		im_iip_param_enum_class_init(ImIipParamEnumClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_aim_private(klass, sizeof(ImIipParamEnumPrivate));
}

static void 		im_iip_param_enum_init(ImIipParamEnum *self)
{
	ImIipParamEnumPrivate *priv = IM_IIP_PARAM_ENUM_GET_PRIVATE(self);
}

static void 		dispose_od(GObject *object)
{
	ImIipParamEnumPrivate *priv = IM_IIP_PARAM_ENUM_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_iip_param_enum_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	ImIipParamEnumPrivate *priv = IM_IIP_PARAM_ENUM_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_iip_param_enum_parent_class) -> dispose(object);
}
/**
 * PUBLIC
 */
ImIipParamEnum* 		im_iip_param_enum_new(void)
{
	ImIipParamEnum *self = g_object_new(IM_TYPE_IIP_PARAM_ENUM, NULL);
	return self;
}
