/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
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


#include "jctpmcpmu.h"


K_TYPE_DEFINE_WITH_PRIVATE(JctpmcPmu, jctpmc_pmu);
#define JCTPMC_PMU_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JctpmcPmuPrivate, JCTPMC_TYPE_PMU))


struct _JctpmcPmuPrivate
{
	kint a;
};
/*
 * IMPL
 */
static void jctpmc_pmu_constructor(JctpmcPmu *self)
{
	JctpmcPmuPrivate *priv = JCTPMC_PMU_GET_PRIVATE(self);

	priv->a = 0;
}

static void jctpmc_pmu_destructor(JctpmcPmu *self)
{
	JctpmcPmuPrivate *priv = JCTPMC_PMU_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
JctpmcPmu *jctpmc_pmu_new(void)
{
	JctpmcPmu* self = k_object_new_with_private(JCTPMC_TYPE_PMU,sizeof(JctpmcPmuPrivate));

	return self;
}
