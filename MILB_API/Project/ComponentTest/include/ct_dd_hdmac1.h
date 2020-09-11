/**
 * @file		ct_dd_hdmac1.h
 * @brief		This is ct header for dd_hdmac1.c
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef _CT_DD_HDMAC1_H_
#define _CT_DD_HDMAC1_H_

#include "../src/ctddhdmac1.h"
#include "../src/ctddhdmac1main.h"

/*
 * 兼容原文件
 */
#define D_HDMAC1_AUTO_TEST_SIZE					CtDdHdmac1_AUTO_TEST_SIZE
#define D_HDMAC1_SDRAM_BASE						CtDdHdmac1_SDRAM_BASE
#define D_HDMAC1_AUTO_TEST_ADR_SRC			CtDdHdmac1_AUTO_TEST_ADR_SRC
#define D_HDMAC1_AUTO_TEST_ADR_DST			CtDdHdmac1_AUTO_TEST_ADR_DST
#define D_HDMAC1_CPU_TARGET						CtDdHdmac1_CPU_TARGET

static inline	VOID Ct_Dd_HDMAC1_Main(int argc, char** argv)
{
	CtDdHdmac1Main* self = ct_dd_hdmac1_main_new();
	ct_dd_hdmac1_main_test(self, argc, argv);
	k_object_unref(self);
	self = NULL;
}


/*
#include "driver_common.h"
----------------------------------------------------------------------
 Definition
----------------------------------------------------------------------
**********************************
 Size definition
**********************************
#define D_HDMAC1_AUTO_TEST_SIZE			(0x96000)

**********************************
 Address definition
**********************************
#define D_HDMAC1_SDRAM_BASE				(0x7A000000)

#define D_HDMAC1_AUTO_TEST_ADR_SRC		(D_HDMAC1_SDRAM_BASE)
#define D_HDMAC1_AUTO_TEST_ADR_DST		(D_HDMAC1_SDRAM_BASE + D_HDMAC1_AUTO_TEST_SIZE)

#define D_HDMAC1_CPU_TARGET				(2)	// CPU1


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
extern	VOID Ct_Dd_HDMAC1_Main(int argc, char** argv);*/

#endif
