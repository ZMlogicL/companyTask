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
 * @file		jmlexs.c
 * @brief		Definition JMLEXS Macro I/O register
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#include "snsjmlexs.h"


K_TYPE_DEFINE_WITH_PRIVATE(SnsJmlexs, sns_jmlexs)
#define SNS_JMLEXS_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), SnsJmlexsPrivate, SNS_TYPE_JMLEXS))


struct _SnsJmlexsPrivate
{
	int a;
};

/*DECLS*/
volatile IoGpv    ioGpv			__attribute__((section(".GPV")));
volatile IoExstop ioExstop	__attribute__((section(".EXSTOP")));


/*IMPL*/
static void sns_jmlexs_constructor(SnsJmlexs *self)
{
//	SnsJmlexsPrivate *priv = SNS_JMLEXS_GET_PRIVATE(self);
}

static void sns_jmlexs_destructor(SnsJmlexs *self)
{
//	SnsJmlexsPrivate *priv = SNS_JMLEXS_GET_PRIVATE(self);
}


/*PUBLIC*/
SnsJmlexs* sns_jmlexs_new(void)
{
	SnsJmlexs *self = k_object_new_with_private(SNS_TYPE_JMLEXS, sizeof(SnsJmlexsPrivate));

	return self;
}

SnsJmlexs* sns_jmlexs_get(void)
{
	static SnsJmlexs	*self = NULL;

	if (!self) {
		self = k_object_new_with_private(SNS_TYPE_JMLEXS, sizeof(SnsJmlexsPrivate));
	}

	return self;
}
