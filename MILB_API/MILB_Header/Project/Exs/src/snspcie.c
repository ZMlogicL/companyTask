/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
*@author              :于孟孟
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		pcie.c
 * @brief		Definition JMLEXS_PCIE Macro I/O register
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#include "snspcie.h"


K_TYPE_DEFINE_WITH_PRIVATE(SnsPcie, sns_pcie)
#define SNS_PCIE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), SnsPciePrivate, SNS_TYPE_PCIE))


struct _SnsPciePrivate
{
	int a;
};


/*DECLS*/
volatile IoPcie			ioPcie0			__attribute__((section(".PCIE0")));
volatile IoPcie			ioPcie1			__attribute__((section(".PCIE1")));
volatile IoPcieCore	ioPcie0Core	__attribute__((section(".PCIE0_CORE")));
volatile IoPcieCore	ioPcie1Core	__attribute__((section(".PCIE1_CORE")));


/*IMPL*/
static void sns_pcie_constructor(SnsPcie *self)
{
//	SnsPciePrivate *priv = SNS_PCIE_GET_PRIVATE(self);
}

static void sns_pcie_destructor(SnsPcie *self)
{
//	SnsPciePrivate *priv = SNS_PCIE_GET_PRIVATE(self);
}


/*PUBLIC*/
SnsPcie* sns_pcie_new(void)
{
	SnsPcie *self = k_object_new_with_private(SNS_TYPE_PCIE, sizeof(SnsPciePrivate));

	return self;
}

SnsPcie* sns_pcie_get(void)
{
	static SnsPcie *self = NULL;

	if (!self) {
		self = k_object_new_with_private(SNS_TYPE_PCIE, sizeof(SnsPciePrivate));
	}

	return self;
}
