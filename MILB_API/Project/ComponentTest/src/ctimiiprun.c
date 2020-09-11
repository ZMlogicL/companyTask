/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIipRun
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


// CT header
// C Standard header
#include <string.h>
#include <stdlib.h>

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#include <stdio.h>
#endif
#endif //CO_CT_IM_IIP_DISABLE

#include "ct_im_iip.h"
#include "ct_im_iip_b2y_frect_afn.h"
#include "ct_im_iip_afn.h"
//#include "ct_im_iip_frect.h"
#include "ctimiipfrect.h"
#include "ct_im_iip_lut.h"
#include "ct_im_iip_blend.h"
#include "ct_im_iip_csc.h"
#include "ct_im_iip_ld.h"
#include "ct_im_iip_flt.h"
#include "ct_im_iip_sl.h"
#include "ct_im_iip_mon.h"
#include "ct_im_iip_cfl.h"
#include "ct_im_iip_gpc.h"
#include "ct_im_iip_utility.h"
#include "ct_im_iip_mft.h"
// im_iip header
#include "im_iip.h"

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#include "palladium_test_common.h"
#endif
// ### REMOVE_RELEASE END

// Driver common header
#include "driver_common.h"
#include "ddim_user_custom.h"

// Clock Control
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif

// Memory barrier
#include "dd_arm.h"
// MILB register header
#include "jdsiip.h"
#include "ctimiip.h"
#include "ctimiiprun.h"


//K_TYPE_DEFINE_WITH_PRIVATE(CtImIipRun, ct_im_iip_run)
//#define CT_IM_IIP_RUN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIipRunPrivate, CT_TYPE_IM_IIP_RUN))


struct _CtImIipRunPrivate
{

};


/*
*DECLS
*/
#ifndef CO_CT_IM_IIP_DISABLE
extern INT32 CT_Im_IIP_Run_4_1( const UINT32 ct_no_3rd );
#endif //CO_CT_IM_IIP_DISABLE

#ifndef CO_CT_IM_IIP_DISABLE
static INT32 CT_Im_IIP_Run_1_1(const UINT32 ct_no_3rd);
static INT32 CT_Im_IIP_Run_2_1(const UINT32 ct_no_3rd);
static INT32 CT_Im_IIP_Run_2_2(const UINT32 ct_no_3rd);
static INT32 CT_Im_IIP_Run_2_4(const UINT32 ct_no_3rd);
static INT32 CT_Im_IIP_Run_2_6(const UINT32 ct_no_3rd);
static INT32 CT_Im_IIP_Run_2_7(const UINT32 ct_no_3rd);
#endif //CO_CT_IM_IIP_DISABLE


/**
 * IMPL
 */
//static void ct_im_iip_run_constructor(CtImIipRun *self)
//{
//	CtImIipRunPrivate *priv = CT_IM_IIP_RUN_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_run_destructor(CtImIipRun *self)
//{
//	CtImIipRunPrivate *priv = CT_IM_IIP_RUN_GET_PRIVATE(self);
//}

#ifndef CO_CT_IM_IIP_DISABLE
static INT32 CT_Im_IIP_Run_1_1(const UINT32 ct_no_3rd)
{
	switch (ct_no_3rd)
	{
	// Test-1-1-2
	case 2:
		return CT_Im_IIP_1_1_2();

		// Test-1-1-3
	case 3:
		return CT_Im_IIP_1_1_3();

		// Test-1-1-4
	case 4:
		return CT_Im_IIP_1_1_4();

		// Test-1-1-5
	case 5:
		return CT_Im_IIP_1_1_5();

		// Test-1-1-6
	case 6:
		return CT_Im_IIP_1_1_6();

		// Test-1-1-7
	case 7:
		return CT_Im_IIP_1_1_7();

		// Test-1-1-8
	case 8:
		return CT_Im_IIP_1_1_8();

		// Test-1-1-9
	case 9:
		return CT_Im_IIP_1_1_9();

		// Test-1-1-10
	case 10:
		return CT_Im_IIP_1_1_10();

		// Test-1-1-11
	case 11:
		return CT_Im_IIP_1_1_11();

		// Test-1-1-12
	case 12:
		return CT_Im_IIP_1_1_12();

		// Test-1-1-13
	case 13:
		return CT_Im_IIP_1_1_13();

		// Test-1-1-14
	case 14:
		return CT_Im_IIP_1_1_14();

		// Test-1-1-15
	case 15:
		return CT_Im_IIP_1_1_15();

		// Test-1-1-16
	case 16:
		return CT_Im_IIP_1_1_16();

		// Test-1-1-17
	case 17:
		return CT_Im_IIP_1_1_17();

		// Test-1-1-18
	case 18:
		return CT_Im_IIP_1_1_18();

		// Test-1-1-19
	case 19:
		return CT_Im_IIP_1_1_19();

		// Test-1-1-20
	case 20:
		return CT_Im_IIP_1_1_20();

		// Test-1-1-21
	case 21:
		return CT_Im_IIP_1_1_21();

		// Test-1-1-22
	case 22:
		return CT_Im_IIP_1_1_22();

		// Test-1-1-23
	case 23:
		return CT_Im_IIP_1_1_23();

		// Test-1-1-24
	case 24:
		return CT_Im_IIP_1_1_24();

		// Test-1-1-25
	case 25:
		return CT_Im_IIP_1_1_25();

#ifdef CO_CT_IM_IIP_ENABLE_1_1_26
		// Test-1-1-26
		case 26:
		return CT_Im_IIP_1_1_26();
#endif

#ifdef CO_DEBUG_ON_PC
		// Test-1-1-27
		case 27:
		return CT_Im_IIP_1_1_27();
#endif

#ifdef CO_DEBUG_ON_PC
		// Test-1-1-28
		case 28:
		return CT_Im_IIP_1_1_28();
#endif

#ifdef CO_DEBUG_ON_PC
		// Test-1-1-29
		case 29:
		return CT_Im_IIP_1_1_29();
#endif

#ifdef CO_DEBUG_ON_PC
		// Test-1-1-30
		case 30:
		return CT_Im_IIP_1_1_30();
#endif

#ifdef CO_DEBUG_ON_PC
		// Test-1-1-31
		case 31:
		return CT_Im_IIP_1_1_31();
#endif

#ifdef CO_DEBUG_ON_PC
		// Test-1-1-32
		case 32:
		return CT_Im_IIP_1_1_32();
#endif

#ifdef CO_DEBUG_ON_PC
		// Test-1-1-33
		case 33:
		return CT_Im_IIP_1_1_33();
#endif

#ifdef CO_CT_IM_IIP_ENABLE_1_1_34
		// Test-1-1-34
		case 34:
		return CT_Im_IIP_1_1_34();
#endif

		// Test-1-1-35
	case 35:
		return CT_Im_IIP_1_1_35();

		// Test-1-1-36
	case 36:
		return CT_Im_IIP_1_1_36();

#ifdef CO_DEBUG_ON_PC
		// Test-1-1-37
		case 37:
		return CT_Im_IIP_1_1_37();
#endif

#ifdef CO_DEBUG_ON_PC
		// Test-1-1-38
		case 38:
		return CT_Im_IIP_1_1_38();
#endif

		// Test-1-1-39
	case 39:
		return CT_Im_IIP_1_1_39();

		// Test-1-1-40
	case 40:
		return CT_Im_IIP_1_1_40();

		// Test-1-1-41
	case 41:
		return CT_Im_IIP_1_1_41();

		// Test-1-1-42
	case 42:
		return CT_Im_IIP_1_1_42();

		// Test-1-1-43
	case 43:
		return CT_Im_IIP_1_1_43();

		// Test-1-1-44
	case 44:
		return CT_Im_IIP_1_1_44();

		// Test-1-1-45
	case 45:
		return CT_Im_IIP_1_1_45();

	default:
		Ddim_Print(("Error: Unknown command.\n"))
		;
		break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

// Im_IIP_Init, Im_IIP_Update_PADRS 2-1-X
static INT32 CT_Im_IIP_Run_2_1(const UINT32 ct_no_3rd)
{
	switch (ct_no_3rd)
	{
	// Test-2-1-1
	case 1:
		return CT_Im_IIP_2_1_1();

		// Test-2-1-2
	case 2:
		return CT_Im_IIP_2_1_2();

		// Test-2-1-3
	case 3:
		return CT_Im_IIP_2_1_3();

	default:
		Ddim_Print(("Error: Unknown command.\n"))
		;
		break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

// Im_IIP_Stop 2-2-X
static INT32 CT_Im_IIP_Run_2_2(const UINT32 ct_no_3rd)
{
	switch (ct_no_3rd)
	{
	// Test-2-2-1
	case 1:
		return CT_Im_IIP_2_2_1();

		// Test-2-2-2
	case 2:
		return CT_Im_IIP_2_2_2();

	default:
		Ddim_Print(("Error: Unknown command.\n"))
		;
		break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

// Im_IIP_Stop 2-4-X
static INT32 CT_Im_IIP_Run_2_4(const UINT32 ct_no_3rd)
{
	switch (ct_no_3rd)
	{
	// Test-2-4-1
	case 1:
		return CT_Im_IIP_2_4_1();

	default:
		Ddim_Print(("Error: Unknown command.\n"))
		;
		break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

// UNIT register dump 2-6-x
static INT32 CT_Im_IIP_Run_2_6(const UINT32 ct_no_3rd)
{
	switch (ct_no_3rd)
	{
	// Test-2-6-1
	case 1:
		return CT_Im_IIP_2_6_1();

	default:
		Ddim_Print(("Error: Unknown command.\n"))
		;
		break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

// Im_IIP_Clear_HISTGRAM 2-7-x
static INT32 CT_Im_IIP_Run_2_7(const UINT32 ct_no_3rd)
{
	switch (ct_no_3rd)
	{
	// Test-2-7-1
	case 1:
		return CT_Im_IIP_2_7_1();

	default:
		Ddim_Print(("Error: Unknown command.\n"))
		;
		break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}
#endif //CO_CT_IM_IIP_DISABLE

#ifndef CO_CT_IM_IIP_DISABLE
VOID CT_Im_IIP_Run(const UINT32 ct_idx_1st, const UINT32 ct_idx_2nd, const UINT32 ct_idx_3rd)
{
#ifdef CO_MSG_PRINT_ON
	INT32 result = D_DDIM_INPUT_PARAM_ERROR;
#endif
	static BOOL is_init = 0;
	T_IM_IIP_LUT lut;
	ULONG hist[4];
	INT32 ercd;

	Ddim_Print(( "CT_Im_IIP_Run( %u, %u, %u ) Begin\n", ct_idx_1st, ct_idx_2nd, ct_idx_3rd ));

	if (is_init == 0)
	{
#ifdef CO_DEBUG_ON_PC
		memset( (VOID*)&IO_IIP, '\0', sizeof(IO_IIP) );
		IO_IIP.IZACTL1.bit.TRG = 2;
		IO_IIP.IZACTL2.bit.ABORT = 2;
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
		Dd_Top_Set_CLKSTOP3_IIPAP( 1 );
		Dd_Top_Set_CLKSTOP3_IIPAH( 1 );
		Dd_Top_Set_CLKSTOP3_IIPAX( 1 );
		Dd_Top_Set_CLKSTOP3_IIPCK( 1 );
#endif
#endif // CO_DEBUG_ON_PC

		if (!((ct_idx_1st == 1) && (ct_idx_2nd == 1) && (ct_idx_3rd == 1)))
		{
			Ddim_Print(( "Im_IIP_Init() Begin\n" ));
			ercd = Im_IIP_Init();
			if (ercd != D_DDIM_USER_E_OK)
			{
				Ddim_Print(( "Im_IIP_Init() Error ercd=0x%x\n", ercd ));
			}
			else
			{
				is_init = 1;
			}
			Ddim_Print(( "Im_IIP_Init() End\n" ));
		}
	}

#ifdef CO_IIP_DEBUG
	Im_IIP_Print_ClockStatus();
#endif

	switch (ct_idx_1st)
	{
	case 0:
		switch (ct_idx_2nd)
		{
		case 0:
			CT_Im_IIP_Print_Pixfmttbl_Detail(ct_idx_3rd);
			break;

#ifdef CO_IM_IIP_UTIL_DEBUG
			case 1:
			{
				extern VOID IM_IIP_Utility_PrintParamBufferBytes( VOID );
				IM_IIP_Utility_PrintParamBufferBytes();
			}
			break;
#endif //CO_IM_IIP_UTIL_DEBUG

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 1:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_1_1(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 2:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_2_1(ct_idx_3rd));
			break;

		case 2:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_2_2(ct_idx_3rd));
			break;

		case 4:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_2_4(ct_idx_3rd));
			break;

#if 0
			case 5:
			D_IM_IIP_RESULT( CT_Im_IIP_Run_2_5( ct_idx_3rd ) );
			break;
#endif

		case 6:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_2_6(ct_idx_3rd));
			break;

		case 7:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_2_7(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 3:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_3_1(ct_idx_3rd));
			break;

		case 2:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_3_2(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;
	case 4:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_4_1(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 5:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_5_1(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 6:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_6_1(ct_idx_3rd));
			break;

		case 2:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_6_2(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 7:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_7_1(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 8:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_8_1(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 9:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_9_1(ct_idx_3rd));
			break;

		case 2:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_9_2(ct_idx_3rd));
			break;

		case 3:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_9_3(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 10:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_10_1(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 11:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_11_1(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 12:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_12_1(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 13:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_13_1(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 14:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_14_1(ct_idx_3rd));
			break;

		case 2:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_14_2(ct_idx_3rd));
			break;

		case 3:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_14_3(ct_idx_3rd));
			break;

		case 4:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_14_4(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	case 15:
		switch (ct_idx_2nd)
		{
		case 1:
			D_IM_IIP_RESULT(CT_Im_IIP_Run_15_1(ct_idx_3rd));
			break;

		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

		// for Jpeg isse workaround.
	case 99:
		switch (ct_idx_2nd)
		{
		case 1:
			Im_IIP_Ctrl_LUT(&lut);
			break;
		case 2:
			Im_IIP_Clear_HISTGRAM(0, 0, 0, 0);
			break;
		case 3:
			Im_IIP_Get_HISTGRAM(&hist[0], &hist[1], &hist[2], &hist[3]);
			break;
		default:
			Ddim_Print(( "Error: Unknown command.\n" ))
			;
			break;
		}
		break;

	default:
		Ddim_Print(( "Error: Unknown command.\n" ))
		;
		break;
	}

#ifdef CO_MSG_PRINT_ON
	Ddim_Print(( "result = 0x%x\n", result ));
#endif

#ifdef CO_IIP_DEBUG
	Im_IIP_Print_ClockStatus();
#endif

	Ddim_Print(( "CT_Im_IIP_Run( %u, %u, %u ) End\n", ct_idx_1st, ct_idx_2nd, ct_idx_3rd ));

	return;
}

#else //CO_CT_IM_IIP_DISABLE
VOID CT_Im_IIP_Run( const UINT32 ct_idx_1st, const UINT32 ct_idx_2nd, const UINT32 ct_idx_3rd )
{

	switch( ct_idx_1st )
	{
		case 0:
		switch( ct_idx_2nd )
		{
			case 0:
			CT_Im_IIP_Print_Pixfmttbl_Detail( ct_idx_3rd );
			break;

			default:
			Ddim_Print(( "Error: Unknown command.\n" ));
			break;
		}
		break;

		default:
		Ddim_Print(( "Error: Unknown command.\n" ));
		break;
	}

	return;
}
#endif //CO_CT_IM_IIP_DISABLE

CtImIipRun* ct_im_iip_run_get(void)
{
	static CtImIipRun* self = NULL;

	if (!self) {
//		self = k_object_new_with_private(CT_TYPE_IM_IIP_RUN, sizeof(CtImIipRunPrivate));
	}

	return self;
}
