/**
 * @file		ct_dd_hdmac.h
 * @brief		This is ct header for dd_hdmac.c
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef _CT_DD_HDMAC_H_
#define _CT_DD_HDMAC_H_

#include "../src/ctddhdmac.h"
#include "../src/ctddhdmacmain.h"
/*
 * 兼容原文件
 */
#define D_HDMAC_AUTO_TEST_SIZE				CtDdHdmac_AUTO_TEST_SIZE
#define D_HDMAC_SDRAM_BASE					CtDdHdmac_SDRAM_BASE
#define D_HDMAC_AUTO_TEST_ADR_SRC		CtDdHdmac_AUTO_TEST_ADR_SRC
#define D_HDMAC_AUTO_TEST_ADR_DST		CtDdHdmac_AUTO_TEST_ADR_DST
#define D_HDMAC_CPU_TARGET						CtDdHdmac_CPU_TARGET

static inline	VOID Ct_Dd_HDMAC_Main(int argc, char** argv)
{
	CtDdHdmacMain* self = ct_dd_hdmac_main_new();
	ct_dd_hdmac_main_test(self, argc, argv);
	k_object_unref(self);
	self = NULL;
}

/*#include "driver_common.h"

----------------------------------------------------------------------
 Definition
----------------------------------------------------------------------
**********************************
 Size definition
**********************************
#define D_HDMAC_AUTO_TEST_SIZE			(0x96000)

**********************************
 Address definition
**********************************
#define D_HDMAC_SDRAM_BASE				(0x7A000000)

#define D_HDMAC_AUTO_TEST_ADR_SRC		(D_HDMAC_SDRAM_BASE)
#define D_HDMAC_AUTO_TEST_ADR_DST		(D_HDMAC_SDRAM_BASE + D_HDMAC_AUTO_TEST_SIZE)

#define D_HDMAC_CPU_TARGET				(2)	// CPU1

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
extern	VOID Ct_Dd_HDMAC_Main(int argc, char** argv);*/

#endif
