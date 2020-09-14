/*
 *imdisp1group.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-08
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
#include <stdlib.h>
#include <string.h>
#include "ctimdisp.h"//already define CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
#include "ctimdisp1.h"
#include "ctimdisp1a.h"
#include "ctimdisp1b.h"
#include "ctimdisp1c.h"
#include "ctimdisp1d.h"
#include "ctimdisp1e.h"

#include "imdisp1group.h"


/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (ImDisp1Group, im_disp1_group, G_TYPE_OBJECT);

/*
 * 以下开始宏定义
 * */
#define IM_DISP1_GROUP_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
		IM_TYPE_DISP1_GROUP, ImDisp1GroupPrivate))

/*
 * 内部结构体或类型定义
 * */
struct _ImDisp1GroupPrivate
{
	gpointer qwertyu;
	ImDisp1Parent *pcTestInstance;
	GObject *wrapObject;
	guchar *pImDispPclkCounter;
};

/*
 * 文件级全局变量定义
 * */

/*
 * DECLS
 * */
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
static void initAllCtImDisp1(ImDisp1Group *self);

/*
 * IMPL
 * */
static void im_disp1_group_class_init(ImDisp1GroupClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(ImDisp1GroupPrivate));
}

static void im_disp1_group_init(ImDisp1Group *self)
{
	ImDisp1GroupPrivate *priv = IM_DISP1_GROUP_GET_PRIVATE(self);
	self->privImDisp1Group = priv;
	priv->pcTestInstance = NULL;
}

static void dispose_od(GObject *object)
{
//	ImDisp1Group *self = IM_DISP1_GROUP(object);
//	ImDisp1GroupPrivate *priv = IM_DISP1_GROUP_GET_PRIVATE(self);
	/*释放创建的对象1*/
//	if (priv->objectMine) {
//		g_object_unref(priv->objectMine);
//		priv->objectMine = NULL;
//	}
	G_OBJECT_CLASS (im_disp1_group_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	ImDisp1Group *self = IM_DISP1_GROUP(object);
//	ImDisp1GroupPrivate *priv = IM_DISP1_GROUP_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (im_disp1_group_parent_class)->finalize(object);
}

static void initAllCtImDisp1(ImDisp1Group *self)
{
	ImDisp1GroupPrivate *priv = self->privImDisp1Group;
	ImDisp1Parent *ctImDisp1 = (ImDisp1Parent *)ct_im_disp1_new();
	ImDisp1Parent *ctImDisp1a = (ImDisp1Parent *)ct_im_disp1a_new();
	ImDisp1Parent *ctImDisp1b = (ImDisp1Parent *)ct_im_disp1b_new();
	ImDisp1Parent *ctImDisp1c = (ImDisp1Parent *)ct_im_disp1c_new();
	ImDisp1Parent *ctImDisp1d = (ImDisp1Parent *)ct_im_disp1d_new();
	ImDisp1Parent *ctImDisp1e= (ImDisp1Parent *)ct_im_disp1e_new();

	im_disp1_parent_add_next(ctImDisp1, ctImDisp1a);
	im_disp1_parent_add_next(ctImDisp1a, ctImDisp1b);
	im_disp1_parent_add_next(ctImDisp1b, ctImDisp1c);
	im_disp1_parent_add_next(ctImDisp1c, ctImDisp1d);
	im_disp1_parent_add_next(ctImDisp1d, ctImDisp1e);

	im_disp1_parent_set_group(ctImDisp1, (GObject *)self);
	im_disp1_parent_set_group(ctImDisp1a, (GObject *)self);
	im_disp1_parent_set_group(ctImDisp1b, (GObject *)self);
	im_disp1_parent_set_group(ctImDisp1c, (GObject *)self);
	im_disp1_parent_set_group(ctImDisp1d, (GObject *)self);

	g_object_unref(ctImDisp1a);
	g_object_unref(ctImDisp1b);
	g_object_unref(ctImDisp1c);
	g_object_unref(ctImDisp1d);
	g_object_unref(ctImDisp1e);

	priv->pcTestInstance = ctImDisp1;
}

/*
 * PUBLIC
 * */

ImDisp1Parent *	im_disp1_group_get_pctest_instance(ImDisp1Group *self)
{
	if(self && IM_IS_DISP1_GROUP(self))
	{
		ImDisp1GroupPrivate *priv = self->privImDisp1Group;
		return priv->pcTestInstance;
	}
	return NULL;
}

guchar *im_disp1_group_get_pclk_counter(ImDisp1Group *self)
{
	if (IM_IS_DISP1_GROUP(self))
	{
		ImDisp1GroupPrivate *priv = self->privImDisp1Group;
		return priv->pImDispPclkCounter;
	}
	return NULL;
}

void im_disp1_group_ct_im_disp3_pclk_counter_on(ImDisp1Group *self)
{
#ifdef CO_ACT_PCLOCK
	ImDisp1GroupPrivate *priv = self->privImDisp1Group;
	Dd_Top_Start_Clock(&priv->pImDispPclkCounter,
			&Dd_Top_Get_CLKSTOP3(), D_IM_DISP_CLKSTOP3_DISPAP_ON);
#endif	// CO_ACT_PCLOCK
}

void im_disp1_group_ct_im_disp3_pclk_counter_off(ImDisp1Group *self)
{
#ifdef CO_ACT_PCLOCK
	ImDisp1GroupPrivate *priv = self->privImDisp1Group;
	Dd_Top_Stop_Clock(&priv->pImDispPclkCounter,
			&Dd_Top_Get_CLKSTOP3(), D_IM_DISP_CLKSTOP3_DISPAP_OFF);
#endif	// CO_ACT_PCLOCK
}

ImDisp1Group *im_disp1_group_new(guchar *pclkCounter, guchar *hclkCounter)
{
	ImDisp1Group *self = (ImDisp1Group *)
		g_object_new(IM_TYPE_DISP1_GROUP, NULL);
	ImDisp1GroupPrivate *priv = self->privImDisp1Group;
	priv->pImDispPclkCounter = pclkCounter;

	initAllCtImDisp1(self);
	return self;
}
