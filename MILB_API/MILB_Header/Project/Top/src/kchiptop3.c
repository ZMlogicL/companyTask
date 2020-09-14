/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
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
#include "kchiptop3.h"


G_DEFINE_TYPE(KChiptop3, k_chiptop3, G_TYPE_OBJECT);

#define K_CHIPTOP3_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), K_TYPE_CHIPTOP3, KChiptop3Private));


struct _KChiptop3Private
{
	 gint preserved;
};
/**
 * DECLS
 */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
/**
 * IMPL
 */
static void k_chiptop3_class_init(KChiptop3Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(KChiptop3Private));
}

static void k_chiptop3_init(KChiptop3 *self)
{
	KChiptop3Private *priv = K_CHIPTOP3_GET_PRIVATE(self);

	priv->preserved = 0;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(k_chiptop3_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(k_chiptop3_parent_class)->finalize(object);
}
/**
 * PUBLIC
 */
KChiptop3 *k_chiptop3_new()
{
	KChiptop3 *self = g_object_new(K_TYPE_CHIPTOP3, NULL);

	return self;
}
