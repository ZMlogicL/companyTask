/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImIip1
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
#include "ct_im_iip_frect.h"
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
#include "ctimiip1.h"


//K_TYPE_DEFINE_WITH_PRIVATE(CtImIip1, ct_im_iip_1)
//#define CT_IM_IIP_1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIip1Private, CT_TYPE_IM_IIP_1))


struct _CtImIip1Private
{

};


#ifndef CO_CT_IM_IIP_DISABLE
extern VOID Im_IIP_Print_DebugStatus( VOID );
#endif //CO_CT_IM_IIP_DISABLE

#ifndef CO_CT_IM_IIP_DISABLE
extern VOID ct_im_iip_print_unitcfg_all( VOID );
#endif //CO_CT_IM_IIP_DISABLE


/********
 * IMPL
 */
//static void ct_im_iip_1_constructor(CtImIip1 *self)
//{
//	CtImIip1Private *priv = CT_IM_IIP_1_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_1_destructor(CtImIip1 *self)
//{
//	CtImIip1Private *priv = CT_IM_IIP_1_GET_PRIVATE(self);
//}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_IIP_DISABLE
INT32 CT_Im_IIP_1_1_2( VOID )
{
	INT32 ercd;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

#ifdef CO_DEBUG_ON_PC
	IO_IIP.IZACTL1.bit.TRG = 2;
#endif // CO_DEBUG_ON_PC

	// check: result = 0x0
	ercd = Im_IIP_Init();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

#ifdef CO_DEBUG_ON_PC
	// check: result = 0x0C000100
	IO_IIP.IZACTL1.bit.TRG = 3;
	ercd = Im_IIP_Init();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	IO_IIP.IZACTL1.bit.TRG = 2;
#endif // CO_DEBUG_ON_PC

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_3( VOID )
{
#ifdef CO_DEBUG_ON_PC
	INT32 ercd;
	const struct {
		volatile struct io_iip_uinftbl* uinftbl;
		E_IM_IIP_UNIT_ID unit_id;
	} ct_param[] = {
		[0] = {
			.unit_id = E_IM_IIP_UNIT_ID_MFT,	// max
			.uinftbl = &IO_IIP.UNITINFTBL_MFT,
		},
		[1] = {
			.unit_id = E_IM_IIP_UNIT_ID_LD0,	// min
			.uinftbl = &IO_IIP.UNITINFTBL_LD0,
		},
	};
	UINT32 loopcnt;
#endif

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

#ifdef CO_DEBUG_ON_PC
	for( loopcnt = 0; loopcnt < (sizeof(ct_param) / sizeof(ct_param[0])); loopcnt++ ) {
		// check: result = 0x0
		ct_param[loopcnt].uinftbl->UNITINFTBL0.bit.SWTRG = 2;
		ercd = Im_IIP_Init_Unit( ct_param[loopcnt].unit_id );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		// check: result = 0x0C000100
		ct_param[loopcnt].uinftbl->UNITINFTBL0.bit.SWTRG = 3;
		ercd = Im_IIP_Init_Unit( ct_param[loopcnt].unit_id );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_param[loopcnt].uinftbl->UNITINFTBL0.bit.SWTRG = 2;
	}
#endif // CO_DEBUG_ON_PC

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_8( VOID )
{
	USHORT lut_tbl[1024];
	T_IM_IIP_LUT ctrl_lut = {
		.buffer_bytes = 1024 * sizeof(USHORT),
		.buffer_addr = lut_tbl,
		.lutram_type = E_IM_IIP_LUTRAM_TYPE_A,
	};
	UINT32 loopcnt;
	E_IM_IIP_LUTRAM_TYPE lutram_type;
	INT32 ercd;
	E_IM_IIP_OPEN_RES accen_param[E_IM_IIP_LUTRAM_TYPE_MAX] = {
		E_IM_IIP_OPEN_RES_LUT_A,
		E_IM_IIP_OPEN_RES_LUT_B,
		E_IM_IIP_OPEN_RES_LUT_C,
		E_IM_IIP_OPEN_RES_LUT_D,
		E_IM_IIP_OPEN_RES_LUT_E,
		E_IM_IIP_OPEN_RES_LUT_F,
	};

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	// check: result = 0x0
	ercd = Im_IIP_Open( 100 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	// check: Assertion
	ercd = Im_IIP_Ctrl_LUT( NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	for( lutram_type = E_IM_IIP_LUTRAM_TYPE_A; lutram_type < E_IM_IIP_LUTRAM_TYPE_MAX; lutram_type++ ) {
		ctrl_lut.lutram_type = lutram_type;

		Ddim_Print(( D_IM_IIP_FUNC_NAME "** LUTRAM %u\n", lutram_type ));

		// check result = 0x0
		ercd = Im_IIP_Set_AccessEnable( accen_param[lutram_type], 1 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		// check: All valid bit is '1'
		for( loopcnt = 0; loopcnt < 1024; loopcnt++ ) {
			lut_tbl[loopcnt] = 0x3fff;
		}
		ercd = Im_IIP_Ctrl_LUT( &ctrl_lut );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_lutram( lutram_type );

		// check: All valid bit is '0'
		for( loopcnt = 0; loopcnt < 1024; loopcnt++ ) {
			lut_tbl[loopcnt] = 0;
		}
		ercd = Im_IIP_Ctrl_LUT( &ctrl_lut );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_lutram( lutram_type );

		// check: Countup 0~1023
		for( loopcnt = 0; loopcnt < 1024; loopcnt++ ) {
			lut_tbl[loopcnt] = loopcnt;
		}
		ercd = Im_IIP_Ctrl_LUT( &ctrl_lut );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_lutram( lutram_type );

		// check: Access denied (result = 0xc000100)
#ifdef CO_DEBUG_ON_PC
		switch( lutram_type ) {
			case E_IM_IIP_LUTRAM_TYPE_A:
				IO_IIP.AHBSTS.bit.LUTAST = 1;
				break;
			case E_IM_IIP_LUTRAM_TYPE_B:
				IO_IIP.AHBSTS.bit.LUTBST = 1;
				break;
			case E_IM_IIP_LUTRAM_TYPE_C:
				IO_IIP.AHBSTS.bit.LUTCST = 1;
				break;
			case E_IM_IIP_LUTRAM_TYPE_D:
				IO_IIP.AHBSTS.bit.LUTDST = 1;
				break;
			case E_IM_IIP_LUTRAM_TYPE_E:
				IO_IIP.AHBSTS.bit.LUTEST = 1;
				break;
			case E_IM_IIP_LUTRAM_TYPE_F:
				IO_IIP.AHBSTS.bit.LUTFST = 1;
				break;
			default:
				break;
		}
		for( loopcnt = 0; loopcnt < 1024; loopcnt++ ) {
			lut_tbl[loopcnt] = 0x10;
		}
		ercd = Im_IIP_Ctrl_LUT( &ctrl_lut );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "denied test result = 0x%x\n", ercd ));
		ct_im_iip_print_lutram( lutram_type );
		switch( lutram_type ) {
			case E_IM_IIP_LUTRAM_TYPE_A:
				IO_IIP.AHBSTS.bit.LUTAST = 0;
				break;
			case E_IM_IIP_LUTRAM_TYPE_B:
				IO_IIP.AHBSTS.bit.LUTBST = 0;
				break;
			case E_IM_IIP_LUTRAM_TYPE_C:
				IO_IIP.AHBSTS.bit.LUTCST = 0;
				break;
			case E_IM_IIP_LUTRAM_TYPE_D:
				IO_IIP.AHBSTS.bit.LUTDST = 0;
				break;
			case E_IM_IIP_LUTRAM_TYPE_E:
				IO_IIP.AHBSTS.bit.LUTEST = 0;
				break;
			case E_IM_IIP_LUTRAM_TYPE_F:
				IO_IIP.AHBSTS.bit.LUTFST = 0;
				break;
			default:
				break;
		}
#endif // CO_DEBUG_ON_PC

		// check result = 0x0
		ercd = Im_IIP_Set_AccessEnable( accen_param[lutram_type], 0 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	}

	// check: result = 0x0
	ercd = Im_IIP_Close();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_9( VOID )
{
	UINT32 loopcnt;
	INT32 ercd;
	ULLONG all_units_mask = 0
		| D_IM_IIP_PARAM_PLDUNIT_LD0
		| D_IM_IIP_PARAM_PLDUNIT_LD1
		| D_IM_IIP_PARAM_PLDUNIT_LD2
		| D_IM_IIP_PARAM_PLDUNIT_LD3
		| D_IM_IIP_PARAM_PLDUNIT_FLT
		| D_IM_IIP_PARAM_PLDUNIT_AFN0
		| D_IM_IIP_PARAM_PLDUNIT_AFN1
		| D_IM_IIP_PARAM_PLDUNIT_AFN2
		| D_IM_IIP_PARAM_PLDUNIT_FRECT0
		| D_IM_IIP_PARAM_PLDUNIT_MON
		| D_IM_IIP_PARAM_PLDUNIT_SL0
		| D_IM_IIP_PARAM_PLDUNIT_SL1
		| D_IM_IIP_PARAM_PLDUNIT_SL2
		| D_IM_IIP_PARAM_PLDUNIT_SL3
		| D_IM_IIP_PARAM_PLDUNIT_SL4
		| D_IM_IIP_PARAM_PLDUNIT_SL5
		| D_IM_IIP_PARAM_PLDUNIT_CSC0
		| D_IM_IIP_PARAM_PLDUNIT_CSC1
		| D_IM_IIP_PARAM_PLDUNIT_LUT
		| D_IM_IIP_PARAM_PLDUNIT_GPC
		| D_IM_IIP_PARAM_PLDUNIT_BLEND0
		| D_IM_IIP_PARAM_PLDUNIT_BLEND1
		| D_IM_IIP_PARAM_PLDUNIT_FRECT1
		| D_IM_IIP_PARAM_PLDUNIT_CFL0
		| D_IM_IIP_PARAM_PLDUNIT_CSC2
		| D_IM_IIP_PARAM_PLDUNIT_CSC3
		| D_IM_IIP_PARAM_PLDUNIT_SL6
		| D_IM_IIP_PARAM_PLDUNIT_SL7
		| D_IM_IIP_PARAM_PLDUNIT_SL8
		| D_IM_IIP_PARAM_PLDUNIT_LD4
		| D_IM_IIP_PARAM_PLDUNIT_LD5
		| D_IM_IIP_PARAM_PLDUNIT_LD6
		| D_IM_IIP_PARAM_PLDUNIT_LD7
		| D_IM_IIP_PARAM_PLDUNIT_AFN3
		| D_IM_IIP_PARAM_PLDUNIT_MFT
		;
	UINT32 all_pixid_mask = 0
		| E_IM_IIP_PIXID_0
		| E_IM_IIP_PIXID_1
		| E_IM_IIP_PIXID_2
		| E_IM_IIP_PIXID_3
		| E_IM_IIP_PIXID_4
		| E_IM_IIP_PIXID_5
		| E_IM_IIP_PIXID_6
		| E_IM_IIP_PIXID_7
		| E_IM_IIP_PIXID_8
		| E_IM_IIP_PIXID_9
		| E_IM_IIP_PIXID_10
		| E_IM_IIP_PIXID_11
		;
	UINT32 all_openres_mask = 0
		| E_IM_IIP_OPEN_RES_LUT_A
		| E_IM_IIP_OPEN_RES_LUT_B
		| E_IM_IIP_OPEN_RES_LUT_C
		| E_IM_IIP_OPEN_RES_LUT_D
		| E_IM_IIP_OPEN_RES_LUT_E
		| E_IM_IIP_OPEN_RES_LUT_F
		| E_IM_IIP_OPEN_RES_HIST_0
		| E_IM_IIP_OPEN_RES_HIST_1
		| E_IM_IIP_OPEN_RES_HIST_2
		| E_IM_IIP_OPEN_RES_HIST_3
		| E_IM_IIP_OPEN_RES_CACHE0
		| E_IM_IIP_OPEN_RES_CACHE1
		| E_IM_IIP_OPEN_RES_CACHE2
		| E_IM_IIP_OPEN_RES_BICUBIC0
		| E_IM_IIP_OPEN_RES_BICUBIC1
		;
	ULONG all_int_factor = 0
		| D_IM_IIP_INT_FACTOR_IZAEND
		| D_IM_IIP_INT_FACTOR_AXIERR
		| D_IM_IIP_INT_FACTOR_SL0END
		| D_IM_IIP_INT_FACTOR_SL1END
		| D_IM_IIP_INT_FACTOR_SL2END
		| D_IM_IIP_INT_FACTOR_SL3END
		| D_IM_IIP_INT_FACTOR_SL4END
		| D_IM_IIP_INT_FACTOR_SL5END
		| D_IM_IIP_INT_FACTOR_SL6END
		| D_IM_IIP_INT_FACTOR_SL7END
		| D_IM_IIP_INT_FACTOR_SL8END
		| D_IM_IIP_INT_FACTOR_SL0_LINEEND
		| D_IM_IIP_INT_FACTOR_SL1_LINEEND
		| D_IM_IIP_INT_FACTOR_SL2_LINEEND
		| D_IM_IIP_INT_FACTOR_SL3_LINEEND
		| D_IM_IIP_INT_FACTOR_SL4_LINEEND
		| D_IM_IIP_INT_FACTOR_SL5_LINEEND
		| D_IM_IIP_INT_FACTOR_SL6_LINEEND
		| D_IM_IIP_INT_FACTOR_SL7_LINEEND
		| D_IM_IIP_INT_FACTOR_SL8_LINEEND
#if 0	// INTIZ2/INTEN2 delete
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN0
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN1
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN2
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN3
		| D_IM_IIP_INT_FACTOR_RINGFULL_FRECT0
		| D_IM_IIP_INT_FACTOR_RINGFULL_FRECT1
		| D_IM_IIP_INT_FACTOR_RINGFULL_FLT
#endif	// INTIZ2/INTEN2 delete
		;
	ULLONG units_bitmask_array[] = {
		D_IM_IIP_PARAM_PLDUNIT_LD0,
		D_IM_IIP_PARAM_PLDUNIT_LD1,
		D_IM_IIP_PARAM_PLDUNIT_LD2,
		D_IM_IIP_PARAM_PLDUNIT_LD3,
		D_IM_IIP_PARAM_PLDUNIT_FLT,
		D_IM_IIP_PARAM_PLDUNIT_AFN0,
		D_IM_IIP_PARAM_PLDUNIT_AFN1,
		D_IM_IIP_PARAM_PLDUNIT_AFN2,
		D_IM_IIP_PARAM_PLDUNIT_FRECT0,
		D_IM_IIP_PARAM_PLDUNIT_MON,
		D_IM_IIP_PARAM_PLDUNIT_SL0,
		D_IM_IIP_PARAM_PLDUNIT_SL1,
		D_IM_IIP_PARAM_PLDUNIT_SL2,
		D_IM_IIP_PARAM_PLDUNIT_SL3,
		D_IM_IIP_PARAM_PLDUNIT_SL4,
		D_IM_IIP_PARAM_PLDUNIT_SL5,
		D_IM_IIP_PARAM_PLDUNIT_CSC0,
		D_IM_IIP_PARAM_PLDUNIT_CSC1,
		D_IM_IIP_PARAM_PLDUNIT_LUT,
		D_IM_IIP_PARAM_PLDUNIT_GPC,
		D_IM_IIP_PARAM_PLDUNIT_BLEND0,
		D_IM_IIP_PARAM_PLDUNIT_BLEND1,
		D_IM_IIP_PARAM_PLDUNIT_FRECT1,
		D_IM_IIP_PARAM_PLDUNIT_CFL0,
		D_IM_IIP_PARAM_PLDUNIT_CSC2,
		D_IM_IIP_PARAM_PLDUNIT_CSC3,
		D_IM_IIP_PARAM_PLDUNIT_SL6,
		D_IM_IIP_PARAM_PLDUNIT_SL7,
		D_IM_IIP_PARAM_PLDUNIT_SL8,
		D_IM_IIP_PARAM_PLDUNIT_LD4,
		D_IM_IIP_PARAM_PLDUNIT_LD5,
		D_IM_IIP_PARAM_PLDUNIT_LD6,
		D_IM_IIP_PARAM_PLDUNIT_LD7,
		D_IM_IIP_PARAM_PLDUNIT_AFN3,
		D_IM_IIP_PARAM_PLDUNIT_MFT,
	};
	UINT32 pixid_bitmask_array[] = {
		E_IM_IIP_PIXID_0,
		E_IM_IIP_PIXID_1,
		E_IM_IIP_PIXID_2,
		E_IM_IIP_PIXID_3,
		E_IM_IIP_PIXID_4,
		E_IM_IIP_PIXID_5,
		E_IM_IIP_PIXID_6,
		E_IM_IIP_PIXID_7,
		E_IM_IIP_PIXID_8,
		E_IM_IIP_PIXID_9,
		E_IM_IIP_PIXID_10,
		E_IM_IIP_PIXID_11,
	};
	UINT32 open_res_bitmask_array[] = {
		E_IM_IIP_OPEN_RES_LUT_A,
		E_IM_IIP_OPEN_RES_LUT_B,
		E_IM_IIP_OPEN_RES_LUT_C,
		E_IM_IIP_OPEN_RES_LUT_D,
		E_IM_IIP_OPEN_RES_LUT_E,
		E_IM_IIP_OPEN_RES_LUT_F,
		E_IM_IIP_OPEN_RES_HIST_0,
		E_IM_IIP_OPEN_RES_HIST_1,
		E_IM_IIP_OPEN_RES_HIST_2,
		E_IM_IIP_OPEN_RES_HIST_3,
		E_IM_IIP_OPEN_RES_CACHE0,
		E_IM_IIP_OPEN_RES_CACHE1,
		E_IM_IIP_OPEN_RES_CACHE2,
		E_IM_IIP_OPEN_RES_BICUBIC0,
		E_IM_IIP_OPEN_RES_BICUBIC1,
	};
	ULLONG unit_bitmask;
	UINT32 pixid_bitmask;
	UINT32 open_res_bitmask;


	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

#if 1
	// check all open.
	Ddim_Print(( D_IM_IIP_FUNC_NAME "** All device open:\n" ));
	ercd = Im_IIP_Open_SWTRG( all_units_mask, all_pixid_mask, all_openres_mask, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	Im_IIP_Print_DebugStatus();
#endif

#if 1
	Ddim_Print(( D_IM_IIP_FUNC_NAME "** Indivisual device open error:\n" ));
	// check unit open error.
	for( loopcnt = 0; loopcnt < (sizeof(units_bitmask_array) / sizeof(units_bitmask_array[0])); loopcnt++ ) {
		ercd = Im_IIP_Open_SWTRG( units_bitmask_array[loopcnt], 0, 0, 200 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx result = 0x%x\n", units_bitmask_array[loopcnt], ercd ));
		if( ercd == D_IM_IIP_OK ) {
			ercd = Im_IIP_Close_SWTRG( units_bitmask_array[loopcnt], 0, 0 );
			Ddim_Print(( D_IM_IIP_FUNC_NAME "close unitmask=0x%llx result = 0x%x\n", units_bitmask_array[loopcnt], ercd ));
		}
	}
	// check pixfmttbl open error.
	for( loopcnt = 0; loopcnt < (sizeof(pixid_bitmask_array) / sizeof(pixid_bitmask_array[0])); loopcnt++ ) {
		ercd = Im_IIP_Open_SWTRG( 0, pixid_bitmask_array[loopcnt], 0, 200 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "open pixidmask=0x%x result = 0x%x\n", pixid_bitmask_array[loopcnt], ercd ));
		if( ercd == D_IM_IIP_OK ) {
			ercd = Im_IIP_Close_SWTRG( 0, pixid_bitmask_array[loopcnt], 0 );
			Ddim_Print(( D_IM_IIP_FUNC_NAME "close pixidmask=0x%x result = 0x%x\n", pixid_bitmask_array[loopcnt], ercd ));
		}
	}
	// check res open error.
	for( loopcnt = 0; loopcnt < (sizeof(open_res_bitmask_array) / sizeof(open_res_bitmask_array[0])); loopcnt++ ) {
		ercd = Im_IIP_Open_SWTRG( 0, 0, open_res_bitmask_array[loopcnt], 200 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "open resmask=0x%x result = 0x%x\n", open_res_bitmask_array[loopcnt], ercd ));
		// check: E_IM_IIP_OPEN_RES_CACHE0 and E_IM_IIP_OPEN_RES_CACHE1 successfull always.
		if( ercd == D_IM_IIP_OK ) {
			ercd = Im_IIP_Close_SWTRG( 0, 0, open_res_bitmask_array[loopcnt] );
			Ddim_Print(( D_IM_IIP_FUNC_NAME "close resmask=0x%x result = 0x%x\n", open_res_bitmask_array[loopcnt], ercd ));
		}
	}
	Im_IIP_Print_DebugStatus();
#endif

#if 1
	Ddim_Print(( D_IM_IIP_FUNC_NAME "** Indiviaual device close & open:\n" ));
	// check close successful and open successful.
	for( loopcnt = 0; loopcnt < (sizeof(units_bitmask_array) / sizeof(units_bitmask_array[0])); loopcnt++ ) {
		ercd = Im_IIP_Close_SWTRG( units_bitmask_array[loopcnt], 0, 0 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "close unitmask=0x%llx result = 0x%x\n", units_bitmask_array[loopcnt], ercd ));
		ercd = Im_IIP_Open_SWTRG( units_bitmask_array[loopcnt], 0, 0, 200 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx result = 0x%x\n", units_bitmask_array[loopcnt], ercd ));
	}
	// check close successful and open successful.
	for( loopcnt = 0; loopcnt < (sizeof(pixid_bitmask_array) / sizeof(pixid_bitmask_array[0])); loopcnt++ ) {
		ercd = Im_IIP_Close_SWTRG( 0, pixid_bitmask_array[loopcnt], 0 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "close pixidmask=0x%x result = 0x%x\n", pixid_bitmask_array[loopcnt], ercd ));
		ercd = Im_IIP_Open_SWTRG( 0, pixid_bitmask_array[loopcnt], 0, 200 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "open pixidmask=0x%x result = 0x%x\n", pixid_bitmask_array[loopcnt], ercd ));
	}
	// check close successful and open successful.
	for( loopcnt = 0; loopcnt < (sizeof(open_res_bitmask_array) / sizeof(open_res_bitmask_array[0])); loopcnt++ ) {
		ercd = Im_IIP_Close_SWTRG( 0, 0, open_res_bitmask_array[loopcnt] );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "close resmask=0x%x result = 0x%x\n", open_res_bitmask_array[loopcnt], ercd ));
		ercd = Im_IIP_Open_SWTRG( 0, 0, open_res_bitmask_array[loopcnt], 200 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "open resmask=0x%x result = 0x%x\n", open_res_bitmask_array[loopcnt], ercd ));
	}
	Im_IIP_Print_DebugStatus();

	Ddim_Print(( D_IM_IIP_FUNC_NAME "** All device close:\n" ));
	// check all close.
	ercd = Im_IIP_Close_SWTRG( all_units_mask, all_pixid_mask, all_openres_mask );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	Im_IIP_Print_DebugStatus();
#endif

#if 1
	// check Unit competition open.
	Ddim_Print(( D_IM_IIP_FUNC_NAME "** Unit competition open:\n" ));
	// user 'A' open - successful.
	unit_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD0;
	pixid_bitmask = 0;
	open_res_bitmask = 0;
	ercd = Im_IIP_Open_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask, 200 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));
	// user 'B' open - error.
	unit_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD0 | D_IM_IIP_PARAM_PLDUNIT_SL4;
	pixid_bitmask = E_IM_IIP_PIXID_2 | E_IM_IIP_PIXID_4;
	open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE1;
	ercd = Im_IIP_Open_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask, 200 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));
	// user 'A' close - successful.
	unit_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD0;
	pixid_bitmask = 0;
	open_res_bitmask = 0;
	ercd = Im_IIP_Close_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "close unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));
	// user 'B' open - successful.
	unit_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD0 | D_IM_IIP_PARAM_PLDUNIT_SL4;
	pixid_bitmask = E_IM_IIP_PIXID_2 | E_IM_IIP_PIXID_4;
	open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE1;
	ercd = Im_IIP_Open_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask, 200 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));



	// check Pixid competition open.
	Ddim_Print(( D_IM_IIP_FUNC_NAME "** Pixid competition open:\n" ));
	// user 'A' open - successful.
	unit_bitmask = 0;
	pixid_bitmask = E_IM_IIP_PIXID_5;
	open_res_bitmask = 0;
	ercd = Im_IIP_Open_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask, 200 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));
	// user 'B' open - error.
	unit_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_SL5;
	pixid_bitmask = E_IM_IIP_PIXID_3 | E_IM_IIP_PIXID_5;
	open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE1;
	ercd = Im_IIP_Open_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask, 200 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));
	// user 'A' close - successful.
	unit_bitmask = 0;
	pixid_bitmask = E_IM_IIP_PIXID_5;
	open_res_bitmask = 0;
	ercd = Im_IIP_Close_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "close unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));
	// user 'B' open - successful.
	unit_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_SL5;
	pixid_bitmask = E_IM_IIP_PIXID_3 | E_IM_IIP_PIXID_5;
	open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE1;
	ercd = Im_IIP_Open_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask, 200 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));



	// check res competition open.
	Ddim_Print(( D_IM_IIP_FUNC_NAME "** Res competition open:\n" ));
	// user 'A' open - successful.
	unit_bitmask = 0;
	pixid_bitmask = 0;
	open_res_bitmask = E_IM_IIP_OPEN_RES_LUT_B;
	ercd = Im_IIP_Open_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask, 500 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));
	// user 'B' open - error.
	unit_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD2 | D_IM_IIP_PARAM_PLDUNIT_SL6;
	pixid_bitmask = E_IM_IIP_PIXID_1 | E_IM_IIP_PIXID_6;
	open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE1 | E_IM_IIP_OPEN_RES_LUT_B;
	ercd = Im_IIP_Open_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask, 500 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));
	// user 'A' close - successful.
	unit_bitmask = 0;
	pixid_bitmask = 0;
	open_res_bitmask = E_IM_IIP_OPEN_RES_LUT_B;
	ercd = Im_IIP_Close_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "close unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));
	// user 'B' open - successful.
	unit_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD2 | D_IM_IIP_PARAM_PLDUNIT_SL6;
	pixid_bitmask = E_IM_IIP_PIXID_1 | E_IM_IIP_PIXID_6;
	open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE1 | E_IM_IIP_OPEN_RES_LUT_B;
	ercd = Im_IIP_Open_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask, 500 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));



	// close of 'Unit competition open'.
	unit_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD0 | D_IM_IIP_PARAM_PLDUNIT_SL4;
	pixid_bitmask = E_IM_IIP_PIXID_2 | E_IM_IIP_PIXID_4;
	open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE1;
	ercd = Im_IIP_Close_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "close unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));



	// close of 'Pixid competition open'.
	unit_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_SL5;
	pixid_bitmask = E_IM_IIP_PIXID_3 | E_IM_IIP_PIXID_5;
	open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE1;
	ercd = Im_IIP_Close_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "close unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));



	// close of 'res competition open'.
	unit_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD2 | D_IM_IIP_PARAM_PLDUNIT_SL6;
	pixid_bitmask = E_IM_IIP_PIXID_1 | E_IM_IIP_PIXID_6;
	open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE1 | E_IM_IIP_OPEN_RES_LUT_B;
	ercd = Im_IIP_Close_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "close unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));
	Im_IIP_Print_DebugStatus();
#endif

#if 1
	// check parameter error.
	unit_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD2 | D_IM_IIP_PARAM_PLDUNIT_SL6;
	pixid_bitmask = E_IM_IIP_PIXID_1 | E_IM_IIP_PIXID_6;
	open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE1 | E_IM_IIP_OPEN_RES_LUT_B;
	ercd = Im_IIP_Open_SWTRG( unit_bitmask, pixid_bitmask, open_res_bitmask, -3 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx pixidmask=0x%x resmask=0x%x result=0x%x\n", unit_bitmask, pixid_bitmask, open_res_bitmask, ercd ));
	Im_IIP_Print_DebugStatus();
#endif

#if 1
	Ddim_Print(( D_IM_IIP_FUNC_NAME "** check interrupt enable bit unset:\n" ));
	ercd = Im_IIP_Open_SWTRG( all_units_mask, 0, 0, 200 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "open unitmask=0x%llx result = 0x%x\n", all_units_mask, ercd ));

	ercd = Im_IIP_Set_Interrupt( all_int_factor, 1 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	ct_im_iip_print_base();

	for( loopcnt = 0; loopcnt < (sizeof(units_bitmask_array) / sizeof(units_bitmask_array[0])); loopcnt++ ) {
		ercd = Im_IIP_Close_SWTRG( units_bitmask_array[loopcnt], 0, 0 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "close unitmask=0x%llx result = 0x%x\n", units_bitmask_array[loopcnt], ercd ));
		ct_im_iip_print_base();
	}

#endif

	return D_DDIM_OK;
}
#endif //CO_CT_IM_IIP_DISABLE

#ifndef CO_CT_IM_IIP_DISABLE
VOID ct_im_iip_print_base( VOID )
{
	Im_IIP_On_Pclk();

	Ddim_Print(( "IZACTL1: 0x%lx\n", IO_IIP.IZACTL1.word ));
	Ddim_Print(( "INTEN0: 0x%lx\n", IO_IIP.INTEN0.word ));
	Ddim_Print(( "INTEN1: 0x%lx\n", IO_IIP.INTEN1.word ));
	Ddim_Print(( "INTEN2: 0x%lx\n", IO_IIP.INTEN2.word ));
	Ddim_Print(( "LINE_VAL_INT_SL0: 0x%lx\n", IO_IIP.LINE_VAL_INT_SL0.word ));
	Ddim_Print(( "LINE_VAL_INT_SL1: 0x%lx\n", IO_IIP.LINE_VAL_INT_SL1.word ));
	Ddim_Print(( "LINE_VAL_INT_SL2: 0x%lx\n", IO_IIP.LINE_VAL_INT_SL2.word ));
	Ddim_Print(( "LINE_VAL_INT_SL3: 0x%lx\n", IO_IIP.LINE_VAL_INT_SL3.word ));
	Ddim_Print(( "LINE_VAL_INT_SL4: 0x%lx\n", IO_IIP.LINE_VAL_INT_SL4.word ));
	Ddim_Print(( "LINE_VAL_INT_SL5: 0x%lx\n", IO_IIP.LINE_VAL_INT_SL5.word ));
	Ddim_Print(( "LINE_VAL_INT_SL6: 0x%lx\n", IO_IIP.LINE_VAL_INT_SL6.word ));
	Ddim_Print(( "LINE_VAL_INT_SL7: 0x%lx\n", IO_IIP.LINE_VAL_INT_SL7.word ));
	Ddim_Print(( "LINE_VAL_INT_SL8: 0x%lx\n", IO_IIP.LINE_VAL_INT_SL8.word ));
	Ddim_Print(( "PDCCTL[0]: 0x%lx\n", IO_IIP.PDCCTL[0].word ));
	Ddim_Print(( "PDCCTL[1]: 0x%lx\n", IO_IIP.PDCCTL[1].word ));
	Ddim_Print(( "PDCCTL[2]: 0x%lx\n", IO_IIP.PDCCTL[2].word ));

	Im_IIP_Off_Pclk();
}
#endif //CO_CT_IM_IIP_DISABLE

CtImIip1* ct_im_iip_1_get(void)
{
	static CtImIip1* self = NULL;

	if (!self) {
//		self = k_object_new_with_private(CT_TYPE_IM_IIP_1, sizeof(CtImIip1Private));
	}

	return self;
}
