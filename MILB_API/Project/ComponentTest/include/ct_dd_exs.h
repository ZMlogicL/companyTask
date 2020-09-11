/**
 * @file		ct_dd_exs.h
 * @brief		dd_exs Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#ifndef _CT_DD_GIC_H_
#define _CT_DD_GIC_H_

#include "../src/ctddexsmain.h"

/*
 * 兼容原函数
 */
extern	VOID	Ct_Dd_EXS_Main(int argc, char** argv)
{
	CtDdExsMain *exsMain = ct_dd_exs_main_new();
	ct_dd_exs_main_test(exsMain, argc, argv);
	k_object_unref(exsMain);
	exsMain = NULL;
}

/*
#include "ddim_typedef.h"

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
extern	VOID	Ct_Dd_EXS_Main(int argc, char** argv);
*/

#endif
