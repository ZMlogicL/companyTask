/**
 * @file		ct_dd_csio.h
 * @brief		This is ct header for ct_dd_csio.c.
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef _CT_DD_CSIO_H_
#define _CT_DD_CSIO_H_

#include "../src/ctddcsio.h"
#include "../src/ctddcsiomain.h"

/*兼容原函数*/
static inline	VOID	Ct_Dd_CSIO_Main(int argc, char** argv)
{
	CtDdCsioMain* csMain =  ct_dd_csio_main_new();
	ct_dd_csio_main_test(csMain,argc, argv );
	k_object_unref(csMain);
	csMain = NULL;
}

static inline	VOID	Ct_Dd_CSIO_PCSim_Test(VOID)
{
	CtDdCsio *csio = ct_dd_csio_new();
	ct_dd_csio_pcsim_test(csio);
	k_object_unref(csio);
	csio = NULL;
}

/*#include "driver_common.h"

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
extern	VOID	Ct_Dd_CSIO_Main(int argc, char** argv);
extern	VOID	Ct_Dd_CSIO_PCSim_Test(VOID);*/

#endif	// _CT_DD_CSIO_H_
