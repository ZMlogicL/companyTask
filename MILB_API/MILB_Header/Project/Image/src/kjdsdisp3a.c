/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#include <stdio.h>
#include <stdlib.h>
#include "kjdsdisp3a.h"


G_DEFINE_TYPE(KJdsdisp3a, k_jdsdisp3a, G_TYPE_OBJECT);

#define K_JDSDISP3A_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), K_TYPE_JDSDISP3A, KJdsdisp3aPrivate));


struct _KJdsdisp3aPrivate
{
	 gint preserved;
};


volatile  IoJdsdispTop	ioDisp				__attribute__((section(".DISP")));
volatile  IoJdsdispTbl	ioDispTbl			__attribute__((section(".DISP_TBL")));
/**
 * DECLS
 */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
/**
 * IMPL
 */
static void k_jdsdisp3a_class_init(KJdsdisp3aClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(KJdsdisp3aPrivate));
}

static void k_jdsdisp3a_init(KJdsdisp3a *self)
{
	KJdsdisp3aPrivate *priv = K_JDSDISP3A_GET_PRIVATE(self);

	priv->preserved = 0;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(k_jdsdisp3a_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(k_jdsdisp3a_parent_class)->finalize(object);
}
/**
 * PUBLIC
 */
KJdsdisp3a *k_jdsdisp3a_new()
{
	KJdsdisp3a *self = g_object_new(K_TYPE_JDSDISP3A, NULL);

	return self;
}
