/**
 * @file		ct_dd_gpv.h
 * @brief		dd_exs Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#ifndef _CT_DD_GIC_H_
#define _CT_DD_GIC_H_

#include "../src/ctddhdmac.h"
#include "../src/ctddhdmacmain.h"

/*
 * 兼容原函数
 */
static inline	VOID	Ct_Dd_GPV_Main(int argc, char** argv)
{
	CtDdGpvMain* gpv = ct_dd_gpv_main_new();
	ct_dd_gpv_main_test(gpv, argc, argv);
	k_object_unref(gpv);
	gpv = NULL;

}

/*#include "ddim_typedef.h"

----------------------------------------------------------------------
 Definition
----------------------------------------------------------------------
 Nothing Special

----------------------------------------------------------------------
 Enumeration
----------------------------------------------------------------------
 Nothing Special

----------------------------------------------------------------------
 Structure
----------------------------------------------------------------------
 Nothing Special

----------------------------------------------------------------------
 Function Prototype Definition
----------------------------------------------------------------------
extern	VOID	Ct_Dd_GPV_Main(int argc, char** argv);*/

#endif
