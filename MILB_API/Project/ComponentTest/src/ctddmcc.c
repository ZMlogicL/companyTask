/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdMcc类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_mcc.c
 * @brief		dd_mcc Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include <string.h>
#include "driver_common.h"
#include "ddmcc.h"
#include "ctddmcc.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdMcc, ct_dd_mcc);
#define CT_DD_MCC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdMccPrivate,CT_TYPE_DD_MCC))

struct _CtDdMccPrivate {
    kint a;
};

static void ct_dd_mcc_constructor(CtDdMcc *self) 
{
	// CtDdMccPrivate *priv = CT_DD_MCC_GET_PRIVATE(self);
}

static void ct_dd_mcc_destructor(CtDdMcc *self)
{
	// CtDdMccPrivate *priv = CT_DD_MCC_GET_PRIVATE(self);
}
/*
 *PUBLIC
 */

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/**
 * @brief		Command main function for MCC test.
 * @param[in]	INT32 argc	:The number of parameters
 * @param[in]   CHAR** argv	:The value of parameters
 * @return 		None
 * @note		None
 * @attention   None
 *
 *			The meaning of parameters
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| P1          | P2 | P3     | P4	  | P5  |Meaning                             |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| display     | -  | -      | -       | -   |Display all registers in MCC.       |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 */
void ct_dd_mcc_main(CtDdMcc *self, kint argc, KType* argv)
{
	if(0 == strcmp(argv[1], "display")) {
		self->dat = DD_MCC_GET_CA70_WFI();
		Ddim_Print(("CA70_WFI=%d\n", self->dat));
		self->dat = DD_MCC_GET_CA71_WFI();
		Ddim_Print(("CA71_WFI=%d\n", self->dat));
		self->dat = DD_MCC_GET_CA72_WFI();
		Ddim_Print(("CA72_WFI=%d\n", self->dat));
		self->dat = DD_MCC_GET_CA73_WFI();
		Ddim_Print(("CA73_WFI=%d\n", self->dat));
		self->dat = DD_MCC_GET_CA70_WFE();
		Ddim_Print(("CA70_WFE=%d\n", self->dat));
		self->dat = DD_MCC_GET_CA71_WFE();
		Ddim_Print(("CA71_WFE=%d\n", self->dat));
		self->dat = DD_MCC_GET_CA72_WFE();
		Ddim_Print(("CA72_WFE=%d\n", self->dat));
		self->dat = DD_MCC_GET_CA73_WFE();
		Ddim_Print(("CA73_WFE=%d\n", self->dat));
	}
}

CtDdMcc *ct_dd_mcc_new(void)
{
    CtDdMcc *self = k_object_new_with_private(CT_TYPE_DD_MCC, sizeof(CtDdMccPrivate));
    return self;
}
