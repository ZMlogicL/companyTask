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
 * @file		relc.c
 * @brief		Definition RELC Macro I/O register
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include "snsrelc.h"


K_TYPE_DEFINE_WITH_PRIVATE(SnsRelc, sns_relc)
#define SNS_RELC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), SnsRelcPrivate, SNS_TYPE_RELC))


struct _SnsRelcPrivate
{
	int a;
};


/*DECLS*/
volatile IoRelc		ioRelc		__attribute__((section(".RELC")));


/*IMPL*/
static void sns_relc_constructor(SnsRelc *self)
{
//	SnsRelcPrivate *priv = SNS_RELC_GET_PRIVATE(self);
}

static void sns_relc_destructor(SnsRelc *self)
{
//	SnsRelcPrivate *priv = SNS_RELC_GET_PRIVATE(self);
}


/*PUBLIC*/
SnsRelc* sns_relc_new(void)
{
	SnsRelc *self = k_object_new_with_private(SNS_TYPE_RELC, sizeof(SnsRelcPrivate));

	return self;
}

SnsRelc* sns_relc_get(void)
{
	static SnsRelc *self = NULL;

	if (!self) {
		self = k_object_new_with_private(SNS_TYPE_RELC, sizeof(SnsRelcPrivate));
	}

	return self;
}
