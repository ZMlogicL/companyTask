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
#include "kpmc.h"


G_DEFINE_TYPE(KPmc, k_pmc, G_TYPE_OBJECT);

#define K_PMC_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o), K_TYPE_PMC, KPmcPrivate));


struct _KPmcPrivate
{
	 gint preserved;
};


volatile IoPmc		ioPmc			__attribute__((section(".PMC")));
/**
 * DECLS
 */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
/**
 * IMPL
 */
static void k_pmc_class_init(KPmcClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(KPmcPrivate));
}

static void k_pmc_init(KPmc *self)
{
	KPmcPrivate *priv = K_PMC_GET_PRIVATE(self);

	priv->preserved = 0;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(k_pmc_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(k_pmc_parent_class)->finalize(object);
}
/**
 * PUBLIC
 */
KPmc *k_pmc_new()
{
	KPmc *self = g_object_new(K_TYPE_PMC, NULL);

	return self;
}
