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


#include "imiipfltregister.h"


G_DEFINE_TYPE(ImIipFltRegister, im_iip_flt_register, G_TYPE_OBJECT);
#define IM_IIP_FLT_REGISTER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_IIP_FLT_REGISTER, ImIipFltRegisterPrivate));


struct _ImIipFltRegisterPrivate
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
static void 		im_iip_flt_register_class_init(ImIipFltRegisterClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_aim_private(klass, sizeof(ImIipFltRegisterPrivate));
}

static void 		im_iip_flt_register_init(ImIipFltRegister *self)
{
	ImIipFltRegisterPrivate *priv = IM_IIP_FLT_REGISTER_GET_PRIVATE(self);
}

static void 		dispose_od(GObject *object)
{
	ImIipFltRegisterPrivate *priv = IM_IIP_FLT_REGISTER_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_iip_flt_register_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	ImIipFltRegisterPrivate *priv = IM_IIP_FLT_REGISTER_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_iip_flt_register_parent_class) -> dispose(object);
}

/**
 * PUBLIC
 */
ImIipFltRegister* 		im_iip_flt_register_new(void)
{
	ImIipFltRegister *self = g_object_new(IM_TYPE_IIP_FLT_REGISTER, NULL);
	return self;
}
