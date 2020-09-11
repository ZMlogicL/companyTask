/**
 * @file		ct_dd_ipcu.h
 * @brief		dd_ipcu Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#ifndef _CT_DD_IPCU_H_
#define _CT_DD_IPCU_H_

#include "../src/ctddipcu.h"
#include "../src/ctddipcumain.h"

/*
 * 兼容原函数
 */
VOID	Ct_Dd_IPCU_Main(int argc, char** argv)
{
	CtDdIpcuMain* iPcuMain = ct_dd_ipcu_main_new();
	ct_dd_ipcu_main_test(iPcuMain, argc, argv);
	k_object_unref(iPcuMain);
	iPcuMain = NULL;
}

/*

#include "typedef.h"

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
extern	VOID	Ct_Dd_IPCU_Main(int argc, char** argv);

*/

#endif
