/*
 *imdisp2parent.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

/*
 * 以下开始include语句
 * */
#include "imdisp2parent.h"

/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (ImDisp2Parent, im_disp2_parent, G_TYPE_OBJECT);

/*
 * 以下开始宏定义
 * */
#define IM_DISP2_PARENT_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
		IM_TYPE_DISP2_PARENT, ImDisp2ParentPrivate))

/*
 * 内部结构体或类型定义
 * */
struct _ImDisp2ParentPrivate
{
	GObject *imDisp2Group;
};

/*
 * 文件级全局变量定义
 * */

/*
 * DECLS
 * */
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);

/*
 * IMPL
 * */
static void im_disp2_parent_class_init(ImDisp2ParentClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(ImDisp2ParentPrivate));
}

static void im_disp2_parent_init(ImDisp2Parent *self)
{
	ImDisp2ParentPrivate *priv = IM_DISP2_PARENT_GET_PRIVATE(self);
	self->privImDisp2Parent = priv;
	self->doMainFunc = NULL;
	priv->imDisp2Group = NULL;
}

static void dispose_od(GObject *object)
{
	ImDisp2Parent *self = IM_DISP2_PARENT(object);
	ImDisp2ParentPrivate *priv = self->privImDisp2Parent;
	if (priv->imDisp2Group)
	{/*释放创建的对象1*/
		g_object_unref(priv->imDisp2Group);
		priv->imDisp2Group = NULL;
	}
	G_OBJECT_CLASS (im_disp2_parent_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	ImDisp2Parent *self = IM_DISP2_PARENT(object);
//	ImDisp2ParentPrivate *priv = IM_DISP2_PARENT_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (im_disp2_parent_parent_class)->finalize(object);
}

/*
 * PUBLIC
 * */
void im_disp2_parent_do_main(ImDisp2Parent *self, gint32 argc, char **argv)
{
	if(self->doMainFunc){
		self->doMainFunc(self, argc, argv);
	}
}

void im_disp2_parent_set_group(ImDisp2Parent *self, GObject *group)
{
	if (self && group && IM_IS_DISP2_PARENT(self))
	{
		ImDisp2ParentPrivate *priv = self->privImDisp2Parent;
		priv->imDisp2Group = g_object_ref(group);
	}
}

GObject *im_disp2_parent_get_group(ImDisp2Parent *self)
{
	if (self && IM_IS_DISP2_PARENT(self))
	{
		ImDisp2ParentPrivate *priv = self->privImDisp2Parent;
		return priv->imDisp2Group;
	}else{
//		Ddim_Print(("!! ImDisp2Parent:%p  group NULL: %s (%d)", self->parent.string, __FILE__, __LINE__));
		return NULL;
	}
}
