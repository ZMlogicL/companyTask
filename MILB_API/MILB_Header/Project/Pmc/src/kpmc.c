/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#include "kpmc.h"


K_TYPE_DEFINE_WITH_PRIVATE(KPmc, k_pmc);
#define K_PMC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KPmcPrivate, K_TYPE_PMC))


struct _KPmcPrivate
{
	kint a;
};


volatile IoPmc		ioPmc			__attribute__((section(".PMC")));
/*
 * IMPL
 */
static void k_pmc_constructor(KPmc *self)
{
	KPmcPrivate *priv = K_PMC_GET_PRIVATE(self);

	priv->a = 0;
}

static void k_pmc_destructor(KPmc *self)
{
	KPmcPrivate *priv = K_PMC_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
KPmc *k_pmc_new(void)
{
	KPmc* self = k_object_new_with_private(K_TYPE_PMC,sizeof(KPmcPrivate));

	return self;
}
