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


#include "jctpmcadc.h"


K_TYPE_DEFINE_WITH_PRIVATE(JctpmcAdc, jctpmc_adc);
#define JCTPMC_ADC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JctpmcAdcPrivate, JCTPMC_TYPE_ADC))


struct _JctpmcAdcPrivate
{
	kint a;
};
/*
 * IMPL
 */
static void jctpmc_adc_constructor(JctpmcAdc *self)
{
	JctpmcAdcPrivate *priv = JCTPMC_ADC_GET_PRIVATE(self);

	priv->a = 0;
}

static void jctpmc_adc_destructor(JctpmcAdc *self)
{
	JctpmcAdcPrivate *priv = JCTPMC_ADC_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
JctpmcAdc *jctpmc_adc_new(void)
{
	JctpmcAdc* self = k_object_new_with_private(JCTPMC_TYPE_ADC,sizeof(JctpmcAdcPrivate));

	return self;
}
