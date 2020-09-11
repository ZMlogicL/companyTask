/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImIipParam
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
#include "ctimiipparam.h"


//K_TYPE_DEFINE_WITH_PRIVATE(CtImIipParam, ct_im_iip_param)
//#define CT_IM_IIP_PARAM_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIipParamPrivate, CT_TYPE_IM_IIP_PARAM))


struct _CtImIipParamPrivate
{

};


/*
*DECLS
*/
#ifndef CO_CT_IM_IIP_DISABLE
static const CHAR*			ct_im_iip_conv_portid_to_name( const E_IM_IIP_PARAM_PORTID portid );
static const CHAR*			ct_im_iip_get_cubsel_name( const ULONG cubsel );
static VOID 						ct_im_iip_get_upsu_name( const UINT32 idx, const ULONG upsu );
static VOID 						ct_im_iip_get_dwsu_name( const UINT32 idx, const ULONG dwsu );
static VOID 						ct_im_iip_print_afn_tbl( const ULONG addr );
#endif //CO_CT_IM_IIP_DISABLE


/********
 * IMPL
 */
//static void ct_im_iip_param_constructor(CtImIipParam *self)
//{
//	CtImIipParamPrivate *priv = CT_IM_IIP_PARAM_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_param_destructor(CtImIipParam *self)
//{
//	CtImIipParamPrivate *priv = CT_IM_IIP_PARAM_GET_PRIVATE(self);
//}

#ifndef CO_CT_IM_IIP_DISABLE
static const CHAR* ct_im_iip_conv_portid_to_name( const E_IM_IIP_PARAM_PORTID portid )
{
	switch( portid ) {
		case E_IM_IIP_PARAM_PORTID_LD0:
			return "E_IM_IIP_PARAM_PORTID_LD0";
		case E_IM_IIP_PARAM_PORTID_LD1:
			return "E_IM_IIP_PARAM_PORTID_LD1";
		case E_IM_IIP_PARAM_PORTID_LD2:
			return "E_IM_IIP_PARAM_PORTID_LD2";
		case E_IM_IIP_PARAM_PORTID_FLT_P0:
			return "E_IM_IIP_PARAM_PORTID_FLT_P0";	// Only port0
		case E_IM_IIP_PARAM_PORTID_AFN0:
			return "E_IM_IIP_PARAM_PORTID_AFN0";
		case E_IM_IIP_PARAM_PORTID_AFN1:
			return "E_IM_IIP_PARAM_PORTID_AFN1";
		case E_IM_IIP_PARAM_PORTID_AFN2:
			return "E_IM_IIP_PARAM_PORTID_AFN2";
		case E_IM_IIP_PARAM_PORTID_AFN3:
			return "E_IM_IIP_PARAM_PORTID_AFN3";
		case E_IM_IIP_PARAM_PORTID_FRECT0:
			return "E_IM_IIP_PARAM_PORTID_FRECT0";
		case E_IM_IIP_PARAM_PORTID_NONE:
			return "E_IM_IIP_PARAM_PORTID_NONE";		// Port not found
		case E_IM_IIP_PARAM_PORTID_SL0:
			return "E_IM_IIP_PARAM_PORTID_SL0";
		case E_IM_IIP_PARAM_PORTID_SL1:
			return "E_IM_IIP_PARAM_PORTID_SL1";
		case E_IM_IIP_PARAM_PORTID_SL2:
			return "E_IM_IIP_PARAM_PORTID_SL2";
		case E_IM_IIP_PARAM_PORTID_SL3:
			return "E_IM_IIP_PARAM_PORTID_SL3";
		case E_IM_IIP_PARAM_PORTID_SL4:
			return "E_IM_IIP_PARAM_PORTID_SL4";
		case E_IM_IIP_PARAM_PORTID_SL5:
			return "E_IM_IIP_PARAM_PORTID_SL5";
		case E_IM_IIP_PARAM_PORTID_CSC0:
			return "E_IM_IIP_PARAM_PORTID_CSC0";
		case E_IM_IIP_PARAM_PORTID_CSC1:
			return "E_IM_IIP_PARAM_PORTID_CSC1";
		case E_IM_IIP_PARAM_PORTID_LUT_P0:
			return "E_IM_IIP_PARAM_PORTID_LUT_P0";	// Only port0
		case E_IM_IIP_PARAM_PORTID_GPC_P0:
			return "E_IM_IIP_PARAM_PORTID_GPC_P0";	// Only port0
		case E_IM_IIP_PARAM_PORTID_BLEND0_P0:
			return "E_IM_IIP_PARAM_PORTID_BLEND0_P0";
		case E_IM_IIP_PARAM_PORTID_BLEND0_P1:
			return "E_IM_IIP_PARAM_PORTID_BLEND0_P1";
		case E_IM_IIP_PARAM_PORTID_BLEND0_P2:
			return "E_IM_IIP_PARAM_PORTID_BLEND0_P2";
		case E_IM_IIP_PARAM_PORTID_BLEND1_P0:
			return "E_IM_IIP_PARAM_PORTID_BLEND1_P0";
		case E_IM_IIP_PARAM_PORTID_BLEND1_P1:
			return "E_IM_IIP_PARAM_PORTID_BLEND2_P1";
		case E_IM_IIP_PARAM_PORTID_BLEND1_P2:
			return "E_IM_IIP_PARAM_PORTID_BLEND1_P2";
		case E_IM_IIP_PARAM_PORTID_FRECT1:
			return "E_IM_IIP_PARAM_PORTID_FRECT1";
		case E_IM_IIP_PARAM_PORTID_CFL0_P0:
			return "E_IM_IIP_PARAM_PORTID_CFL0_P0";	// Only port0
		case E_IM_IIP_PARAM_PORTID_CSC2:
			return "E_IM_IIP_PARAM_PORTID_CSC2";
		case E_IM_IIP_PARAM_PORTID_CSC3:
			return "E_IM_IIP_PARAM_PORTID_CSC3";
		case E_IM_IIP_PARAM_PORTID_SL6:
			return "E_IM_IIP_PARAM_PORTID_SL6";
		case E_IM_IIP_PARAM_PORTID_SL7:
			return "E_IM_IIP_PARAM_PORTID_SL7";
		case E_IM_IIP_PARAM_PORTID_SL8:
			return "E_IM_IIP_PARAM_PORTID_SL8";
		case E_IM_IIP_PARAM_PORTID_LD3:
			return "E_IM_IIP_PARAM_PORTID_LD3";
		case E_IM_IIP_PARAM_PORTID_LD4:
			return "E_IM_IIP_PARAM_PORTID_LD4";
		case E_IM_IIP_PARAM_PORTID_LD5:
			return "E_IM_IIP_PARAM_PORTID_LD5";
		case E_IM_IIP_PARAM_PORTID_LD6:
			return "E_IM_IIP_PARAM_PORTID_LD6";
		case E_IM_IIP_PARAM_PORTID_LD7:
			return "E_IM_IIP_PARAM_PORTID_LD7";
		case E_IM_IIP_PARAM_PORTID_MFT:
			return "E_IM_IIP_PARAM_PORTID_MFT";
		default:
			return "(null)";	// Invalid parameter
	}
}

static const CHAR* ct_im_iip_get_cubsel_name( const ULONG cubsel )
{
	static const CHAR* const cubsel_name_tbl[8] = {
		[E_IM_IIP_PARAM_CUBSEL_AFN0] = "E_IM_IIP_PARAM_CUBSEL_AFN0",
		[E_IM_IIP_PARAM_CUBSEL_AFN1] = "E_IM_IIP_PARAM_CUBSEL_AFN1",
		[E_IM_IIP_PARAM_CUBSEL_AFN2] = "E_IM_IIP_PARAM_CUBSEL_AFN2",
		[E_IM_IIP_PARAM_CUBSEL_AFN3] = "E_IM_IIP_PARAM_CUBSEL_AFN3",
		[E_IM_IIP_PARAM_CUBSEL_FRECT0] = "E_IM_IIP_PARAM_CUBSEL_FRECT0",
		[E_IM_IIP_PARAM_CUBSEL_FRECT1] = "E_IM_IIP_PARAM_CUBSEL_FRECT1",
	};

	if( cubsel_name_tbl[cubsel] == NULL ) {
		return "(UNKNOWN)";
	}
	else {
		return cubsel_name_tbl[cubsel];
	}
}

static VOID ct_im_iip_get_upsu_name( const UINT32 idx, const ULONG upsu )
{
	static const CHAR* const upsu_name_tbl[16] = {
		[E_IM_IIP_PARAM_UPSU_NONE] = "E_IM_IIP_PARAM_UPSU_NONE",
		[E_IM_IIP_PARAM_UPSU_B2Y] = "E_IM_IIP_PARAM_UPSU_B2Y",
		[E_IM_IIP_PARAM_UPSU_AFN0] = "E_IM_IIP_PARAM_UPSU_AFN0",
		[E_IM_IIP_PARAM_UPSU_AFN1] = "E_IM_IIP_PARAM_UPSU_AFN1",
		[E_IM_IIP_PARAM_UPSU_AFN2] = "E_IM_IIP_PARAM_UPSU_AFN2",
		[E_IM_IIP_PARAM_UPSU_AFN3] = "E_IM_IIP_PARAM_UPSU_AFN3",
		[E_IM_IIP_PARAM_UPSU_FRECT0] = "E_IM_IIP_PARAM_UPSU_FRECT0",
		[E_IM_IIP_PARAM_UPSU_FRECT1] = "E_IM_IIP_PARAM_UPSU_FRECT1",
		[E_IM_IIP_PARAM_UPSU_FLT] = "E_IM_IIP_PARAM_UPSU_FLT",
		[E_IM_IIP_PARAM_UPSU_LD0] = "E_IM_IIP_PARAM_UPSU_LD0",
		[E_IM_IIP_PARAM_UPSU_LD1] = "E_IM_IIP_PARAM_UPSU_LD1",
		[E_IM_IIP_PARAM_UPSU_LD2] = "E_IM_IIP_PARAM_UPSU_LD2",
		[E_IM_IIP_PARAM_UPSU_LD3] = "E_IM_IIP_PARAM_UPSU_LD3",
		[E_IM_IIP_PARAM_UPSU_LD4] = "E_IM_IIP_PARAM_UPSU_LD4",
		[E_IM_IIP_PARAM_UPSU_LD5] = "E_IM_IIP_PARAM_UPSU_LD5",
		[E_IM_IIP_PARAM_UPSU_LD6] = "E_IM_IIP_PARAM_UPSU_LD6",
	};

	Ddim_Print(( "UPLK_TARGET.UPSU%u = %s\n", idx, upsu_name_tbl[upsu] ));
}

static VOID ct_im_iip_get_dwsu_name( const UINT32 idx, const ULONG dwsu )
{
	static const CHAR* const dwsu_name_tbl[16] = {
		[E_IM_IIP_PARAM_DWSU_NONE] = "E_IM_IIP_PARAM_DWSU_NONE",
		[E_IM_IIP_PARAM_DWSU_AFN0] = "E_IM_IIP_PARAM_DWSU_AFN0",
		[E_IM_IIP_PARAM_DWSU_AFN1] = "E_IM_IIP_PARAM_DWSU_AFN1",
		[E_IM_IIP_PARAM_DWSU_AFN2] = "E_IM_IIP_PARAM_DWSU_AFN2",
		[E_IM_IIP_PARAM_DWSU_AFN3] = "E_IM_IIP_PARAM_DWSU_AFN3",
		[E_IM_IIP_PARAM_DWSU_FLT] = "E_IM_IIP_PARAM_DWSU_FLT",
		[E_IM_IIP_PARAM_DWSU_LD0] = "E_IM_IIP_PARAM_DWSU_LD0",
		[E_IM_IIP_PARAM_DWSU_LD1] = "E_IM_IIP_PARAM_DWSU_LD1",
		[E_IM_IIP_PARAM_DWSU_LD2] = "E_IM_IIP_PARAM_DWSU_LD2",
		[E_IM_IIP_PARAM_DWSU_LD3] = "E_IM_IIP_PARAM_DWSU_LD3",
		[E_IM_IIP_PARAM_DWSU_LD4] = "E_IM_IIP_PARAM_DWSU_LD4",
		[E_IM_IIP_PARAM_DWSU_LD5] = "E_IM_IIP_PARAM_DWSU_LD5",
		[E_IM_IIP_PARAM_DWSU_LD6] = "E_IM_IIP_PARAM_DWSU_LD6",
	};
	const CHAR* name;

	if( dwsu_name_tbl[dwsu] == NULL ) {
		name = "(UNKNOWN)";
	}
	else {
		name = dwsu_name_tbl[dwsu];
	}

	Ddim_Print(( "DWLK_TARGET.DWSU%u = %s\n", idx, name ));
}

static VOID ct_im_iip_print_afn_tbl( const ULONG addr )
{
	const T_IM_IIP_PARAM_AFN_OPCOL_0* afntbl = (T_IM_IIP_PARAM_AFN_OPCOL_0*)addr;

	if( afntbl == NULL ) {
		return;
	}

	Ddim_Print(( "STAX = 0x%x %f\n", afntbl->STAXY0.bit.STAX, ct_im_iip_conv_afntbl_float(afntbl->STAXY0.bit.STAX) ));
	Ddim_Print(( "STAY = 0x%x %f\n", afntbl->STAXY0.bit.STAY, ct_im_iip_conv_afntbl_float(afntbl->STAXY0.bit.STAY) ));
	Ddim_Print(( "DXX = 0x%x %f\n", afntbl->D_OUT_IN_0.bit.DXX, ct_im_iip_conv_afntbl_float(afntbl->D_OUT_IN_0.bit.DXX) ));
	Ddim_Print(( "DXY = 0x%x %f\n", afntbl->D_OUT_IN_0.bit.DXY, ct_im_iip_conv_afntbl_float(afntbl->D_OUT_IN_0.bit.DXY) ));
	Ddim_Print(( "DYX = 0x%x %f\n", afntbl->D_OUT_IN_0.bit.DYX, ct_im_iip_conv_afntbl_float(afntbl->D_OUT_IN_0.bit.DYX) ));
	Ddim_Print(( "DYY = 0x%x %f\n", afntbl->D_OUT_IN_0.bit.DYY, ct_im_iip_conv_afntbl_float(afntbl->D_OUT_IN_0.bit.DYY) ));
	Ddim_Print(( "AFNDHSZ = %u\n", afntbl->SZ.bit.AFNDHSZ ));
	Ddim_Print(( "AFNDVSZ = %u\n", afntbl->SZ.bit.AFNDVSZ ));
}


/**********
 * PUBLIC
 */
VOID ct_im_iip_print_lutram( const E_IM_IIP_LUTRAM_TYPE lutram_type )
{
	UINT32 loopcnt;
	UINT32 lutram_type_idx;

	switch( lutram_type ) {
		case E_IM_IIP_LUTRAM_TYPE_A:
			lutram_type_idx = 0;
			break;
		case E_IM_IIP_LUTRAM_TYPE_B:
			lutram_type_idx = 2;
			break;
		case E_IM_IIP_LUTRAM_TYPE_C:
			lutram_type_idx = 4;
			break;
		case E_IM_IIP_LUTRAM_TYPE_D:
			lutram_type_idx = 1;
			break;
		case E_IM_IIP_LUTRAM_TYPE_E:
			lutram_type_idx = 3;
			break;
		case E_IM_IIP_LUTRAM_TYPE_F:
			lutram_type_idx = 5;
			break;
		default:
			return;
	}

	Im_IIP_On_Pclk();
	Im_IIP_On_Hclk();

	for( loopcnt = 0; loopcnt < 1024; loopcnt++ ) {
		Ddim_Print(( "[%4u]=0x%04lx ", loopcnt, IO_IIP_TBL.LUTRAM.LUTRAM.word[lutram_type_idx][loopcnt] ));
		if( (loopcnt % 8) == 7 ) {
			Ddim_Print(( "\n" ));
		}
	}

	Im_IIP_Off_Hclk();
	Im_IIP_Off_Pclk();
}

VOID ct_im_iip_print_afn_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid )
{
	static const CHAR* const itmd_name_tbl[4] = {
		"E_IM_IIP_PARAM_ITMD_BI_LINEAR",
		"E_IM_IIP_PARAM_ITMD_NEAREST",
		"E_IM_IIP_PARAM_ITMD_BI_CUBIC",
	};
	static const CHAR* const ghsz_name_tbl[2] = {
		"E_IM_IIP_PARAM_GHSZ_64PIX",
		"E_IM_IIP_PARAM_GHSZ_32PIX",
	};
	static const CHAR* const gvsz_name_tbl[16] = {
		"E_IM_IIP_PARAM_GVSZ_SAME_AS_VERTICAL_PIX",
		"E_IM_IIP_PARAM_GVSZ_2PIX",
		"E_IM_IIP_PARAM_GVSZ_4PIX",
		"E_IM_IIP_PARAM_GVSZ_8PIX",
		"E_IM_IIP_PARAM_GVSZ_16PIX",
		"E_IM_IIP_PARAM_GVSZ_32PIX",
		"E_IM_IIP_PARAM_GVSZ_64PIX",
		"E_IM_IIP_PARAM_GVSZ_128PIX",
		"E_IM_IIP_PARAM_GVSZ_256PIX",
	};
	const T_IM_IIP_PARAM_AFN* afn = (T_IM_IIP_PARAM_AFN*)pUNITINFTBL->UNITINFTBL2.word;

	if( afn == NULL ) {
		return;
	}

	Ddim_Print(( "AFNTOPCNF.WAITCONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)afn->AFNTOPCNF.bit.WAITCONF) ));
	Ddim_Print(( "AFNCTL.GHSZ = %s\n", ghsz_name_tbl[afn->AFNCTL.bit.GHSZ] ));
	Ddim_Print(( "AFNCTL.GVSZ = %s\n", gvsz_name_tbl[afn->AFNCTL.bit.GVSZ] ));
	Ddim_Print(( "AFNCTL.HSMD = %u\n", afn->AFNCTL.bit.HSMD ));
	Ddim_Print(( "PFCTL.PFSP1 = %u\n", afn->PFCTL.bit.PFSP1 ));
	Ddim_Print(( "PFCTL.PFSP2 = %u\n", afn->PFCTL.bit.PFSP2 ));
	Ddim_Print(( "PIXIDEF.IPIXID = %u\n", afn->PIXIDEF.bit.IPIXID ));
	Ddim_Print(( "CALMETHOD.ITMD = %s\n", itmd_name_tbl[afn->CALMETHOD.bit.ITMD] ));
	Ddim_Print(( "CALMETHOD.DANTI = %u\n", afn->CALMETHOD.bit.DANTI ));
	Ddim_Print(( "CALMETHOD.AANTI = %u\n", afn->CALMETHOD.bit.AANTI ));
	Ddim_Print(( "CALMETHOD.CUBSEL = %s\n", ct_im_iip_get_cubsel_name( afn->CALMETHOD.bit.CUBSEL ) ));
	Ddim_Print(( "CLIPLVLY.CLIPLVLYH = %u\n", afn->CLIPLVLY.bit.CLIPLVLYH ));
	Ddim_Print(( "CLIPLVLY.CLIPLVLYL = %u\n", afn->CLIPLVLY.bit.CLIPLVLYL ));
	Ddim_Print(( "CLIPLVLB.CLIPLVLBH = %u\n", afn->CLIPLVLB.bit.CLIPLVLBH ));
	Ddim_Print(( "CLIPLVLB.CLIPLVLBL = %u\n", afn->CLIPLVLB.bit.CLIPLVLBL ));
	Ddim_Print(( "CLIPLVLR.CLIPLVLRH = %u\n", afn->CLIPLVLR.bit.CLIPLVLRH ));
	Ddim_Print(( "CLIPLVLR.CLIPLVLRL = %u\n", afn->CLIPLVLR.bit.CLIPLVLRL ));
	Ddim_Print(( "CLIPLVLA.CLIPLVLAH = %u\n", afn->CLIPLVLA.bit.CLIPLVLAH ));
	Ddim_Print(( "CLIPLVLA.CLIPLVLAL = %u\n", afn->CLIPLVLA.bit.CLIPLVLAL ));
	Ddim_Print(( "OUTSIZE.OUTHSZ = %u\n", afn->OUTSIZE.bit.OUTHSZ ));
	Ddim_Print(( "OUTSIZE.OUTVSZ = %u\n", afn->OUTSIZE.bit.OUTVSZ ));
	Ddim_Print(( "OUTSTARTPOS.STARTX = %u\n", afn->OUTSTARTPOS.bit.STARTX ));
	Ddim_Print(( "OUTSTARTPOS.STARTY = %u\n", afn->OUTSTARTPOS.bit.STARTY ));
	ct_im_iip_get_upsu_name( 0, afn->UPLK_TARGET.bit.UPSU0 );
	ct_im_iip_get_upsu_name( 1, afn->UPLK_TARGET.bit.UPSU1 );
	ct_im_iip_get_upsu_name( 2, afn->UPLK_TARGET.bit.UPSU2 );
	Ddim_Print(( "LKNUM.UPNUM = %u\n", afn->LKNUM.bit.UPNUM ));
	Ddim_Print(( "RING.URINGSIZE = %u\n", afn->RING.bit.URINGSIZE ));
	Ddim_Print(( "RING.UMARGINIYSZ = %u\n", afn->RING.bit.UMARGINIYSZ ));
	ct_im_iip_get_dwsu_name( 0, afn->DWLK_TARGET.bit.DWSU0 );
	ct_im_iip_get_dwsu_name( 1, afn->DWLK_TARGET.bit.DWSU1 );
	ct_im_iip_get_dwsu_name( 2, afn->DWLK_TARGET.bit.DWSU2 );
	Ddim_Print(( "LKNUM.DWNUM = %u\n", afn->LKNUM.bit.DWNUM ));
	Ddim_Print(( "RING.DRINGSIZE = %u\n", afn->RING.bit.DRINGSIZE ));
	Ddim_Print(( "AFNPA = 0x%lx\n", afn->AFNPA.word ));

	ct_im_iip_print_afn_tbl( afn->AFNPA.word );
}

VOID ct_im_iip_print_frect_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid )
{
	static const CHAR* const itmd_name_tbl[4] = {
		"E_IM_IIP_PARAM_ITMD_BI_LINEAR",
		"E_IM_IIP_PARAM_ITMD_NEAREST",
		"E_IM_IIP_PARAM_ITMD_BI_CUBIC",
	};
	static const CHAR* const ghsz_name_tbl[2] = {
		"E_IM_IIP_PARAM_GHSZ_64PIX",
		"E_IM_IIP_PARAM_GHSZ_32PIX",
	};
	static const CHAR* const gvsz_name_tbl[16] = {
		"E_IM_IIP_PARAM_GVSZ_SAME_AS_VERTICAL_PIX",
		"E_IM_IIP_PARAM_GVSZ_2PIX",
		"E_IM_IIP_PARAM_GVSZ_4PIX",
		"E_IM_IIP_PARAM_GVSZ_8PIX",
		"E_IM_IIP_PARAM_GVSZ_16PIX",
		"E_IM_IIP_PARAM_GVSZ_32PIX",
		"E_IM_IIP_PARAM_GVSZ_64PIX",
		"E_IM_IIP_PARAM_GVSZ_128PIX",
		"E_IM_IIP_PARAM_GVSZ_256PIX",
	};
	const T_IM_IIP_PARAM_FRECT* fr = (T_IM_IIP_PARAM_FRECT*)pUNITINFTBL->UNITINFTBL2.word;

	if( fr == NULL ) {
		return;
	}

	Ddim_Print(( "FRTOPCNF.WAITCONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)fr->FRTOPCNF.bit.WAITCONF) ));
	Ddim_Print(( "FRCTL.GHSZ = %s\n", ghsz_name_tbl[fr->FRCTL.bit.GHSZ] ));
	Ddim_Print(( "FRCTL.GVSZ = %s\n", gvsz_name_tbl[fr->FRCTL.bit.GVSZ] ));
	Ddim_Print(( "FRCTL.HSMD = %u\n", fr->FRCTL.bit.HSMD ));
	Ddim_Print(( "PFCTL.PFSP1 = %u\n", fr->PFCTL.bit.PFSP1 ));
	Ddim_Print(( "PFCTL.PFSP2 = %u\n", fr->PFCTL.bit.PFSP2 ));
	Ddim_Print(( "PIXIDEF.IPIXID = %u\n", fr->PIXIDEF.bit.IPIXID ));
	Ddim_Print(( "CALMETHOD.ITMD = %s\n", itmd_name_tbl[fr->CALMETHOD.bit.ITMD] ));
	Ddim_Print(( "CALMETHOD.DANTI = %u\n", fr->CALMETHOD.bit.DANTI ));
	Ddim_Print(( "CALMETHOD.AANTI = %u\n", fr->CALMETHOD.bit.AANTI ));
	Ddim_Print(( "CALMETHOD.CUBSEL = %s\n", ct_im_iip_get_cubsel_name( fr->CALMETHOD.bit.CUBSEL ) ));
	Ddim_Print(( "CLIPLVLY.CLIPLVLYH = %u\n", fr->CLIPLVLY.bit.CLIPLVLYH ));
	Ddim_Print(( "CLIPLVLY.CLIPLVLYL = %u\n", fr->CLIPLVLY.bit.CLIPLVLYL ));
	Ddim_Print(( "CLIPLVLB.CLIPLVLBH = %u\n", fr->CLIPLVLB.bit.CLIPLVLBH ));
	Ddim_Print(( "CLIPLVLB.CLIPLVLBL = %u\n", fr->CLIPLVLB.bit.CLIPLVLBL ));
	Ddim_Print(( "CLIPLVLR.CLIPLVLRH = %u\n", fr->CLIPLVLR.bit.CLIPLVLRH ));
	Ddim_Print(( "CLIPLVLR.CLIPLVLRL = %u\n", fr->CLIPLVLR.bit.CLIPLVLRL ));
	Ddim_Print(( "CLIPLVLA.CLIPLVLAH = %u\n", fr->CLIPLVLA.bit.CLIPLVLAH ));
	Ddim_Print(( "CLIPLVLA.CLIPLVLAL = %u\n", fr->CLIPLVLA.bit.CLIPLVLAL ));
	Ddim_Print(( "OUTSIZE.OUTHSZ = %u\n", fr->OUTSIZE.bit.OUTHSZ ));
	Ddim_Print(( "OUTSIZE.OUTVSZ = %u\n", fr->OUTSIZE.bit.OUTVSZ ));
	Ddim_Print(( "OUTSTARTPOS.STARTX = %u\n", fr->OUTSTARTPOS.bit.STARTX ));
	Ddim_Print(( "OUTSTARTPOS.STARTY = %u\n", fr->OUTSTARTPOS.bit.STARTY ));
	ct_im_iip_get_upsu_name( 0, fr->UPLK_TARGET.bit.UPSU0 );
	ct_im_iip_get_upsu_name( 1, fr->UPLK_TARGET.bit.UPSU1 );
	ct_im_iip_get_upsu_name( 2, fr->UPLK_TARGET.bit.UPSU2 );
	Ddim_Print(( "LKNUM.UPNUM = %u\n", fr->LKNUM.bit.UPNUM ));
	Ddim_Print(( "RING.URINGSIZE = %u\n", fr->RING.bit.URINGSIZE ));
	Ddim_Print(( "RING.UMARGINIYSZ = %u\n", fr->RING.bit.UMARGINIYSZ ));
	ct_im_iip_get_dwsu_name( 0, fr->DWLK_TARGET.bit.DWSU0 );
	ct_im_iip_get_dwsu_name( 1, fr->DWLK_TARGET.bit.DWSU1 );
	ct_im_iip_get_dwsu_name( 2, fr->DWLK_TARGET.bit.DWSU2 );
	Ddim_Print(( "LKNUM.DWNUM = %u\n", fr->LKNUM.bit.DWNUM ));
	Ddim_Print(( "RING.DRINGSIZE = %u\n", fr->RING.bit.DRINGSIZE ));
	Ddim_Print(( "PADRS = 0x%lx\n", fr->PADRS.word ));
}

VOID ct_im_iip_print_sl_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid )
{
	const T_IM_IIP_PARAM_STS*			sl = (T_IM_IIP_PARAM_STS*)pUNITINFTBL->UNITINFTBL2.word;
	volatile struct io_iip_pixfmttbl*	pPIXFMTTBL;
	UINT32								pixid;
	UINT32								mif_no_y;
	UINT32								mif_no_cb;
	UINT32								mif_no_cr;
	UINT32								mif_no_a;
	static const UINT32					mif_tbl_sl2[2] = { 2, 1 };
	static const UINT32					mif_tbl_sl5[2] = { 2, 0 };

	if( sl == NULL ) {
		return;
	}

	Ddim_Print(( "SL_TOPCNF0.DATACONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)sl->BASE.SL_TOPCNF0.bit.DATACONF) ));
	Ddim_Print(( "SL_TOPCNF0.WAITCONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)sl->BASE.SL_TOPCNF0.bit.WAITCONF) ));
	Ddim_Print(( "PIXIDDEF.bit.OPIXID = %u\n", sl->BASE.PIXIDDEF.bit.OPIXID ));
	Ddim_Print(( "SL_HSIZE.HSTART = %u\n", sl->BASE.SL_HSIZE.bit.HSTART ));
	Ddim_Print(( "SL_HSIZE.HEND = %u\n", sl->BASE.SL_HSIZE.bit.HEND ));
	Ddim_Print(( "SL_VSIZE.VSTART = %u\n", sl->BASE.SL_VSIZE.bit.VSTART ));
	Ddim_Print(( "SL_VSIZE.VEND = %u\n", sl->BASE.SL_VSIZE.bit.VEND ));
	Ddim_Print(( "SL_PHSZ.PHSZ0 = %u\n", sl->BASE.SL_PHSZ.bit.PHSZ0 ));
	Ddim_Print(( "SL_PHSZ.PHSZ1 = %u\n", sl->BASE.SL_PHSZ.bit.PHSZ1 ));
	Ddim_Print(( "SL_PVSZ.PVSZ0 = %u\n", sl->BASE.SL_PVSZ.bit.PVSZ0 ));
	Ddim_Print(( "SL_PVSZ.PVSZ1 = %u\n", sl->BASE.SL_PVSZ.bit.PVSZ1 ));
	Ddim_Print(( "CLPTH_U_0.CLPTH_U = %u\n", sl->BASE.CLPTH_U_0.bit.CLPTH_U ));
	Ddim_Print(( "CLPTH_L_0.CLPTH_L = %u\n", sl->BASE.CLPTH_L_0.bit.CLPTH_L ));

	pixid = sl->BASE.PIXIDDEF.bit.OPIXID;
	pPIXFMTTBL = &IO_IIP.PIXFMTTBL[pixid];

	switch( unitid ) {
		case E_IM_IIP_UNIT_ID_SL0:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL3:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL6:
			mif_no_y = 0;
			mif_no_cb = 0;
			mif_no_cr = 0;
			mif_no_a = 0;
			break;
		case E_IM_IIP_UNIT_ID_SL1:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL4:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL7:
			mif_no_y = 1;
			mif_no_cb = 1;
			mif_no_cr = 1;
			mif_no_a = 1;
			break;
		case E_IM_IIP_UNIT_ID_SL8:
			mif_no_y = 2;
			mif_no_cb = 2;
			mif_no_cr = 2;
			mif_no_a = 2;
			break;
		case E_IM_IIP_UNIT_ID_SL2:
			mif_no_y = mif_tbl_sl2[pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFYG];
			mif_no_cb = mif_tbl_sl2[pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFB];
			mif_no_cr = mif_tbl_sl2[pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFR];
			mif_no_a = mif_tbl_sl2[pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFA];
			break;
		case E_IM_IIP_UNIT_ID_SL5:
			mif_no_y = mif_tbl_sl5[pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFYG];
			mif_no_cb = mif_tbl_sl5[pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFB];
			mif_no_cr = mif_tbl_sl5[pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFR];
			mif_no_a = mif_tbl_sl5[pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFA];
			break;
		default:
			mif_no_y = 0xFF;
			mif_no_cb = 0xFF;
			mif_no_cr = 0xFF;
			mif_no_a = 0xFF;
			break;
	}

	DDIM_User_Printf( "MasterIF Y=%u(%u) Cb=%u(%u) Cr=%u(%u) A=%u(%u)\n",
			mif_no_y, pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFYG,
			mif_no_cb, pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFB,
			mif_no_cr, pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFR,
			mif_no_a, pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFA );
}

VOID ct_im_iip_print_1d_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid )
{
	const T_IM_IIP_PARAM_1DL* pLD = (T_IM_IIP_PARAM_1DL*)pUNITINFTBL->UNITINFTBL2.word;

	if( pLD == NULL ) {
		return;
	}

	Ddim_Print(( "LD_TOPCNF0.WAITCONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)pLD->LD_TOPCNF0.bit.WAITCONF) ));
	Ddim_Print(( "PIXIDDEF.IPIXID  = %u\n", pLD->PIXIDDEF.bit.IPIXID ));
	Ddim_Print(( "LD_PREFETCH.PF_PDIST = %u\n", pLD->LD_PREFETCH.bit.PF_PDIST ));
	Ddim_Print(( "LD_HSIZE.HSTART = %u\n", pLD->LD_HSIZE.bit.HSTART ));
	Ddim_Print(( "LD_HSIZE.HEND = %u\n", pLD->LD_HSIZE.bit.HEND ));
	Ddim_Print(( "LD_VSIZE.VSTART = %u\n", pLD->LD_VSIZE.bit.VSTART ));
	Ddim_Print(( "LD_VSIZE.VEND = %u\n", pLD->LD_VSIZE.bit.VEND ));
	Ddim_Print(( "LD_PHSZ.PHSZ0 = %u\n", pLD->LD_PHSZ.bit.PHSZ0 ));
	Ddim_Print(( "LD_PHSZ.PHSZ1 = %u\n", pLD->LD_PHSZ.bit.PHSZ1 ));
	Ddim_Print(( "LD_PVSZ.PVSZ0 = %u\n", pLD->LD_PVSZ.bit.PVSZ0 ));
	Ddim_Print(( "LD_PVSZ.PVSZ1 = %u\n", pLD->LD_PVSZ.bit.PVSZ1 ));
	ct_im_iip_get_upsu_name( 0, pLD->UPLK_TARGET.bit.UPSU0 );
	ct_im_iip_get_upsu_name( 1, pLD->UPLK_TARGET.bit.UPSU1 );
	ct_im_iip_get_upsu_name( 2, pLD->UPLK_TARGET.bit.UPSU2 );
	Ddim_Print(( "LKNUM.UPNUM = %u\n", pLD->LKNUM.bit.UPNUM ));
	Ddim_Print(( "RING.URINGSIZE = %u\n", pLD->RING.bit.URINGSIZE ));
	Ddim_Print(( "RING.UMARGINIYSZ = %u\n", pLD->RING.bit.UMARGINIYSZ ));
	ct_im_iip_get_dwsu_name( 0, pLD->DWLK_TARGET.bit.DWSU0 );
	ct_im_iip_get_dwsu_name( 1, pLD->DWLK_TARGET.bit.DWSU1 );
	ct_im_iip_get_dwsu_name( 2, pLD->DWLK_TARGET.bit.DWSU2 );
	Ddim_Print(( "LKNUM.DWNUM = %u\n", pLD->LKNUM.bit.DWNUM ));
	Ddim_Print(( "RING.DRINGSIZE = %u\n", pLD->RING.bit.DRINGSIZE ));
}

VOID ct_im_iip_print_csc_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid )
{
	const T_IM_IIP_PARAM_CSC* csc = (T_IM_IIP_PARAM_CSC*)pUNITINFTBL->UNITINFTBL2.word;
	UINT32 loopcnt;

	if( csc == NULL ) {
		return;
	}

	Ddim_Print(( "CSCTOPCNF.DATACONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)csc->CSCTOPCNF.bit.DATACONF) ));
	Ddim_Print(( "CSCTOPCNF.WAITCONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)csc->CSCTOPCNF.bit.WAITCONF) ));
	Ddim_Print(( "CSCK\n" ));
	for( loopcnt = 0; loopcnt < 4; loopcnt++ ) {
		Ddim_Print(( " %u %u %u %u\n",
					csc->CSCK[loopcnt].bit.CSCK_0,
					csc->CSCK[loopcnt].bit.CSCK_1,
					csc->CSCK[loopcnt].bit.CSCK_2,
					csc->CSCK[loopcnt].bit.CSCK_3
					));
	}
	Ddim_Print(( "MDSEL.MDSEL = 0x%x\n", csc->MDSEL.bit.MDSEL ));
	Ddim_Print(( "ALPSEL.ALPSEL = 0x%x\n", csc->ALPSEL.bit.ALPSEL ));
	Ddim_Print(( "ALPSEL.ALOSEL = 0x%x\n", csc->ALPSEL.bit.ALOSEL ));
	Ddim_Print(( "ALPVAL.ALPVAL = 0x%x\n", csc->ALPVAL.bit.ALPVAL ));
}

VOID ct_im_iip_print_lut_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid )
{
	const T_IM_IIP_PARAM_LUT* lut = (T_IM_IIP_PARAM_LUT*)pUNITINFTBL->UNITINFTBL2.word;
	static const CHAR* sgX_name_tbl[2] = {
		"D_IM_IIP_UNSIGNED_DATA",
		"D_IM_IIP_SIGNED_DATA",
	};

	if( lut == NULL ) {
		return;
	}

	Ddim_Print(( "LUTTOPCNF[0].DATACONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)lut->LUTTOPCNF[0].bit.DATACONF) ));
	Ddim_Print(( "LUTTOPCNF[0].WAITCONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)lut->LUTTOPCNF[0].bit.WAITCONF) ));
	Ddim_Print(( "LUTUNITCTL.PORTEN = %u\n", lut->LUTUNITCTL.bit.PORTEN ));
	Ddim_Print(( "LUTCTL_A.LUTBIT = %u\n", lut->LUTCTL_A.bit.LUTBIT ));
	Ddim_Print(( "LUTCTL_A.USE = %u\n", lut->LUTCTL_A.bit.USE ));
	Ddim_Print(( "LUTCTL_A.SGN = %s\n", sgX_name_tbl[lut->LUTCTL_A.bit.SGN] ));
	Ddim_Print(( "LUTCTL_A.SPLBIT = %u\n", lut->LUTCTL_A.bit.SPLBIT ));
	Ddim_Print(( "LUTPRECAL_A.OFSET = %u\n", lut->LUTPRECAL_A.bit.OFSET ));
	Ddim_Print(( "LUTPRECAL_A.CLPMAX = %u\n", lut->LUTPRECAL_A.bit.CLPMAX ));
	Ddim_Print(( "LUTPRECAL_A.THMAX = %u\n", lut->LUTPRECAL_A.bit.THMAX ));
	Ddim_Print(( "LUTPRECAL_A.CLPMIN = %u\n", lut->LUTPRECAL_A.bit.CLPMIN ));
	Ddim_Print(( "LUTPRECAL_A.THMIN = %u\n", lut->LUTPRECAL_A.bit.THMIN ));
	Ddim_Print(( "LUTPRECAL_A.ABS = %u\n", lut->LUTPRECAL_A.bit.ABS ));
	Ddim_Print(( "LUTCTL_B.LUTBIT = %u\n", lut->LUTCTL_B.bit.LUTBIT ));
	Ddim_Print(( "LUTCTL_B.USE = %u\n", lut->LUTCTL_B.bit.USE ));
	Ddim_Print(( "LUTCTL_B.SGN = %s\n", sgX_name_tbl[lut->LUTCTL_B.bit.SGN] ));
	Ddim_Print(( "LUTCTL_B.SPLBIT = %u\n", lut->LUTCTL_B.bit.SPLBIT ));
	Ddim_Print(( "LUTPRECAL_B.OFSET = %u\n", lut->LUTPRECAL_B.bit.OFSET ));
	Ddim_Print(( "LUTPRECAL_B.CLPMAX = %u\n", lut->LUTPRECAL_B.bit.CLPMAX ));
	Ddim_Print(( "LUTPRECAL_B.THMAX = %u\n", lut->LUTPRECAL_B.bit.THMAX ));
	Ddim_Print(( "LUTPRECAL_B.CLPMIN = %u\n", lut->LUTPRECAL_B.bit.CLPMIN ));
	Ddim_Print(( "LUTPRECAL_B.THMIN = %u\n", lut->LUTPRECAL_B.bit.THMIN ));
	Ddim_Print(( "LUTPRECAL_B.ABS = %u\n", lut->LUTPRECAL_B.bit.ABS ));
	Ddim_Print(( "LUTCTL_C.LUTBIT = %u\n", lut->LUTCTL_C.bit.LUTBIT ));
	Ddim_Print(( "LUTCTL_C.USE = %u\n", lut->LUTCTL_C.bit.USE ));
	Ddim_Print(( "LUTCTL_C.SGN = %s\n", sgX_name_tbl[lut->LUTCTL_C.bit.SGN] ));
	Ddim_Print(( "LUTCTL_C.SPLBIT = %u\n", lut->LUTCTL_C.bit.SPLBIT ));
	Ddim_Print(( "LUTPRECAL_C.OFSET = %u\n", lut->LUTPRECAL_C.bit.OFSET ));
	Ddim_Print(( "LUTPRECAL_C.CLPMAX = %u\n", lut->LUTPRECAL_C.bit.CLPMAX ));
	Ddim_Print(( "LUTPRECAL_C.THMAX = %u\n", lut->LUTPRECAL_C.bit.THMAX ));
	Ddim_Print(( "LUTPRECAL_C.CLPMIN = %u\n", lut->LUTPRECAL_C.bit.CLPMIN ));
	Ddim_Print(( "LUTPRECAL_C.THMIN = %u\n", lut->LUTPRECAL_C.bit.THMIN ));
	Ddim_Print(( "LUTPRECAL_C.ABS = %u\n", lut->LUTPRECAL_C.bit.ABS ));
	Ddim_Print(( "LUTCTL_D.LUTBIT = %u\n", lut->LUTCTL_D.bit.LUTBIT ));
	Ddim_Print(( "LUTCTL_D.USE = %u\n", lut->LUTCTL_D.bit.USE ));
	Ddim_Print(( "LUTCTL_D.SGN = %s\n", sgX_name_tbl[lut->LUTCTL_D.bit.SGN] ));
	Ddim_Print(( "LUTCTL_D.SPLBIT = %u\n", lut->LUTCTL_D.bit.SPLBIT ));
	Ddim_Print(( "LUTPRECAL_D.OFSET = %u\n", lut->LUTPRECAL_D.bit.OFSET ));
	Ddim_Print(( "LUTPRECAL_D.CLPMAX = %u\n", lut->LUTPRECAL_D.bit.CLPMAX ));
	Ddim_Print(( "LUTPRECAL_D.THMAX = %u\n", lut->LUTPRECAL_D.bit.THMAX ));
	Ddim_Print(( "LUTPRECAL_D.CLPMIN = %u\n", lut->LUTPRECAL_D.bit.CLPMIN ));
	Ddim_Print(( "LUTPRECAL_D.THMIN = %u\n", lut->LUTPRECAL_D.bit.THMIN ));
	Ddim_Print(( "LUTPRECAL_D.ABS = %u\n", lut->LUTPRECAL_D.bit.ABS ));

	Ddim_Print(( "LUTRAM A:\n" ));
	ct_im_iip_print_lutram( E_IM_IIP_LUTRAM_TYPE_A );
	Ddim_Print(( "LUTRAM B:\n" ));
	ct_im_iip_print_lutram( E_IM_IIP_LUTRAM_TYPE_B );
	Ddim_Print(( "LUTRAM C:\n" ));
	ct_im_iip_print_lutram( E_IM_IIP_LUTRAM_TYPE_C );
	Ddim_Print(( "LUTRAM D:\n" ));
	ct_im_iip_print_lutram( E_IM_IIP_LUTRAM_TYPE_D );
	Ddim_Print(( "LUTRAM E:\n" ));
	ct_im_iip_print_lutram( E_IM_IIP_LUTRAM_TYPE_E );
	Ddim_Print(( "LUTRAM F:\n" ));
	ct_im_iip_print_lutram( E_IM_IIP_LUTRAM_TYPE_F );
}

VOID ct_im_iip_print_blend_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid )
{
	const T_IM_IIP_PARAM_BLEND* alp = (T_IM_IIP_PARAM_BLEND*)pUNITINFTBL->UNITINFTBL2.word;
	static const CHAR* const alpha_out_name_tbl[4] = {
		"E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA",
		"E_IM_IIP_PARAM_ALPHA_OUT_P1_ALPHA",
		"E_IM_IIP_PARAM_ALPHA_OUT_FIXED_VAL",
		"E_IM_IIP_PARAM_ALPHA_OUT_NONE",
	};
	static const CHAR* const alpha_step_name_tbl[4] = {
		"E_IM_IIP_PARAM_ALPHA_STEP_8BITS",
		"(null)",
		"(null)",
		"E_IM_IIP_PARAM_ALPHA_STEP_4BITS",
	};
	static const CHAR* const alpha_sel_name_tbl[8] = {
		"E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA",
		"E_IM_IIP_PARAM_ALPHA_SEL_P1_ALPHA",
		"E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL",
		"E_IM_IIP_PARAM_ALPHA_SEL_P2_D0_D1_D2_ALPHA",
		"E_IM_IIP_PARAM_ALPHA_SEL_P2_D0_ALPHA",
		"(null)",
		"(null)",
		"(null)",
	};

	if( alp == NULL ) {
		return;
	}

	Ddim_Print(( "BLENDTOPCNF0.DATACONF_0 = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)alp->BLENDTOPCNF0.bit.DATACONF_0) ));
	Ddim_Print(( "BLENDTOPCNF1.DATACONF_1 = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)alp->BLENDTOPCNF1.bit.DATACONF_1) ));
	Ddim_Print(( "BLENDTOPCNF0.WAITCONF_0 = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)alp->BLENDTOPCNF0.bit.WAITCONF_0) ));
	Ddim_Print(( "BLENDCTL.ALPHA_OUT = %s\n", alpha_out_name_tbl[alp->BLENDCTL.bit.ALPHA_OUT] ));
	Ddim_Print(( "ALPHACTL0.ALPHA_STEP = %s\n", alpha_step_name_tbl[alp->ALPHACTL0.bit.ALPHA_STEP] ));
	Ddim_Print(( "ALPHACTL0.ALPHA_SEL = 0x%s\n", alpha_sel_name_tbl[alp->ALPHACTL0.bit.ALPHA_SEL] ));
	Ddim_Print(( "ALPHACTL1.ALPHA_VAL0 = 0x%x\n", alp->ALPHACTL1.bit.ALPHA_VAL0 ));
	Ddim_Print(( "ALPHACTL1.ALPHA_VAL1 = 0x%x\n", alp->ALPHACTL1.bit.ALPHA_VAL1 ));
	Ddim_Print(( "ALPHACTL2.ALPHA_VAL2 = 0x%x\n", alp->ALPHACTL2.bit.ALPHA_VAL2 ));
	Ddim_Print(( "ALPHACTL2.ALPHA_VAL3 = 0x%x\n", alp->ALPHACTL2.bit.ALPHA_VAL3 ));
}

VOID ct_im_iip_print_mft_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid )
{
	const T_IM_IIP_PARAM_MFT* mft = (T_IM_IIP_PARAM_MFT*)pUNITINFTBL->UNITINFTBL2.word;
	static const CHAR* const mftmd_name_tbl[2] = {
		"E_IM_IIP_PARAM_MFTMD_MIN",
		"E_IM_IIP_PARAM_MFTMD_MAX",
	};
	static const CHAR* const fix_name_tbl[2] = {
		"E_IM_IIP_PARAM_DNFIX_FILTER",
		"E_IM_IIP_PARAM_DNFIX_FIXVAL",
	};
	UINT32 loopcnt;

	if( mft == NULL ) {
		return;
	}

	Ddim_Print(( "FTTOPCONF.DATACONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)mft->FTTOPCONF.bit.DATACONF) ));
	Ddim_Print(( "FTTOPCONF.WAITCONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)mft->FTTOPCONF.bit.WAITCONF) ));
	Ddim_Print(( "MFTMD.MFTMD = %s\n", mftmd_name_tbl[mft->MFTMD.bit.MFTMD] ));
	Ddim_Print(( "FLTTPSZ.FLTTPSZ = %u\n", mft->FLTTPSZ.bit.FLTTPSZ ));
	Ddim_Print(( "FLTOUTHSZ.FLTOUTHSZ = %u\n", mft->FLTOUTHSZ.bit.FLTOUTHSZ ));
	for( loopcnt = 0; loopcnt < 4; loopcnt++ ) {
		Ddim_Print(( "MFTCTLD[%u].FIX = %s\n", loopcnt, fix_name_tbl[mft->MFTCTLD[loopcnt].bit.FIX] ));
		Ddim_Print(( "MFTCTLD[%u].VAL = 0x%x\n", loopcnt, mft->MFTCTLD[loopcnt].bit.VAL ));
	}
}

VOID ct_im_iip_print_flt_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid )
{
	const T_IM_IIP_PARAM_FLT* flt = (T_IM_IIP_PARAM_FLT*)pUNITINFTBL->UNITINFTBL2.word;

	if( flt == NULL ) {
		return;
	}

	Im_IIP_On_Pclk();
	Ddim_Print(( "FLT_TDLTOPCNF.DATACONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)flt->TDLTOPCNF.bit.WAITCONF_0) ));
	Ddim_Print(( "FLT_TDLTOPCNF.WAITCONF = %s\n", ct_im_iip_conv_portid_to_name((E_IM_IIP_PARAM_PORTID)flt->TDLTOPCNF.bit.DATACONF) ));
	Ddim_Print(( "PIXIDDEF.IPIXID0 = %u\n", flt->PIXIDDEF.bit.IPIXID0 ));
	Ddim_Print(( "TDL_CTL.FM = %u\n", flt->TDL_CTL.bit.FM ));
	Ddim_Print(( "TDL_CTL.LNUM = %u\n", flt->TDL_CTL.bit.LNUM ));
	Ddim_Print(( "TDL_CTL.SAVERD = %u\n", flt->TDL_CTL.bit.SAVERD ));
	Ddim_Print(( "TDL_CTL.INPUT_MODE = %u\n", flt->TDL_CTL.bit.INPUT_MODE ));
	Ddim_Print(( "TDL_CTL.CSEL = %u\n", flt->TDL_CTL.bit.CSEL ));
	Ddim_Print(( "CALC_MD.CALC_MD = %u\n", flt->CALC_MD.bit.CALC_MD ));

	Ddim_Print(( "TDL_HSIZE.HSTART = %u\n", flt->TDL_HSIZE.bit.HSTART ));
	Ddim_Print(( "TDL_HSIZE.HEND = %u\n", flt->TDL_HSIZE.bit.HEND ));
	Ddim_Print(( "TDL_VSIZE.VSTART = %u\n", flt->TDL_VSIZE.bit.VSTART ));
	Ddim_Print(( "TDL_VSIZE.VEND = %u\n", flt->TDL_VSIZE.bit.VEND ));

	Ddim_Print(( "TDL_PHSZ.PHSZ1 = %u\n", flt->TDL_PHSZ.bit.PHSZ1 ));
	Ddim_Print(( "TDL_PVSZ.PVSZ1 = %u\n", flt->TDL_PVSZ.bit.PVSZ1 ));
	Ddim_Print(( "TDL_PHSZ.PHSZ0 = %u\n", flt->TDL_PHSZ.bit.PHSZ0 ));
	Ddim_Print(( "TDL_PVSZ.PVSZ0 = %u\n", flt->TDL_PVSZ.bit.PVSZ0 ));

	Ddim_Print(( "TDL_PF.PF_ON = %u\n", flt->TDL_PF.bit.PF_ON ));
	Ddim_Print(( "TDL_PF.PF_MD = %u\n", flt->TDL_PF.bit.PF_MD ));
	Ddim_Print(( "TDL_PF.PF_NUM = %u\n", flt->TDL_PF.bit.PF_NUM ));
	Ddim_Print(( "TDL_PF.PF_ADJ_NUM = %u\n", flt->TDL_PF.bit.PF_ADJ_NUM ));
	Ddim_Print(( "TDL_PF.PF_ADJ_VAL = 0x%x\n", flt->TDL_PF.bit.PF_ADJ_VAL ));

	ct_im_iip_get_upsu_name( 0, flt->UPLK_TARGET.bit.UPSU0 );
	ct_im_iip_get_upsu_name( 1, flt->UPLK_TARGET.bit.UPSU1 );
	ct_im_iip_get_upsu_name( 2, flt->UPLK_TARGET.bit.UPSU2 );
	Ddim_Print(( "LKNUM.UPNUM = %u\n", flt->LKNUM.bit.UPNUM ));
	Ddim_Print(( "RING.URINGSIZE = %u\n", flt->RING.bit.URINGSIZE ));
	Ddim_Print(( "RING.UMARGINIYSZ = %u\n", flt->RING.bit.UMARGINIYSZ ));
	ct_im_iip_get_dwsu_name( 0, flt->DWLK_TARGET.bit.DWSU0 );
	ct_im_iip_get_dwsu_name( 1, flt->DWLK_TARGET.bit.DWSU1 );
	ct_im_iip_get_dwsu_name( 2, flt->DWLK_TARGET.bit.DWSU2 );
	Ddim_Print(( "LKNUM.DWNUM = %u\n", flt->LKNUM.bit.DWNUM ));

	Ddim_Print(( "UNIT_OUT.UNIT_OUT_A_D0 = %u\n", flt->UNIT_OUT.bit.UNIT_OUT_A_D0 ));
	Ddim_Print(( "UNIT_OUT.UNIT_OUT_A_D1 = %u\n", flt->UNIT_OUT.bit.UNIT_OUT_A_D1 ));
	Ddim_Print(( "UNIT_OUT.UNIT_OUT_A_D2 = %u\n", flt->UNIT_OUT.bit.UNIT_OUT_A_D2 ));
	Ddim_Print(( "UNIT_OUT.UNIT_OUT_B_D0 = %u\n", flt->UNIT_OUT.bit.UNIT_OUT_B_D0 ));
	Ddim_Print(( "UNIT_OUT.UNIT_OUT_B_D1 = %u\n", flt->UNIT_OUT.bit.UNIT_OUT_B_D1 ));
	Ddim_Print(( "UNIT_OUT.UNIT_OUT_B_D2 = %u\n", flt->UNIT_OUT.bit.UNIT_OUT_B_D2 ));

	Ddim_Print(( "FIN_CLP_A_D0.FIN_CLVLP_A_D0 = 0x%x\n", flt->FIN_CLP_A_D0.bit.FIN_CLVLP_A_D0 ));
	Ddim_Print(( "FIN_CLP_A_D0.FIN_CLVLM_A_D0 = 0x%x\n", flt->FIN_CLP_A_D0.bit.FIN_CLVLM_A_D0 ));
	Ddim_Print(( "FIN_CLP_A_D1.FIN_CLVLP_A_D1 = 0x%x\n", flt->FIN_CLP_A_D1.bit.FIN_CLVLP_A_D1 ));
	Ddim_Print(( "FIN_CLP_A_D1.FIN_CLVLM_A_D1 = 0x%x\n", flt->FIN_CLP_A_D1.bit.FIN_CLVLM_A_D1 ));
	Ddim_Print(( "FIN_CLP_A_D2.FIN_CLVLP_A_D2 = 0x%x\n", flt->FIN_CLP_A_D2.bit.FIN_CLVLP_A_D2 ));
	Ddim_Print(( "FIN_CLP_A_D2.FIN_CLVLM_A_D2 = 0x%x\n", flt->FIN_CLP_A_D2.bit.FIN_CLVLM_A_D2 ));
	Ddim_Print(( "FIN_CLP_B_D0.FIN_CLVLP_B_D0 = 0x%x\n", flt->FIN_CLP_B_D0.bit.FIN_CLVLP_B_D0 ));
	Ddim_Print(( "FIN_CLP_B_D0.FIN_CLVLM_B_D0 = 0x%x\n", flt->FIN_CLP_B_D0.bit.FIN_CLVLM_B_D0 ));
	Ddim_Print(( "FIN_CLP_B_D1.FIN_CLVLP_B_D1 = 0x%x\n", flt->FIN_CLP_B_D1.bit.FIN_CLVLP_B_D1 ));
	Ddim_Print(( "FIN_CLP_B_D1.FIN_CLVLM_B_D1 = 0x%x\n", flt->FIN_CLP_B_D1.bit.FIN_CLVLM_B_D1 ));
	Ddim_Print(( "FIN_CLP_B_D2.FIN_CLVLP_B_D2 = 0x%x\n", flt->FIN_CLP_B_D2.bit.FIN_CLVLP_B_D2 ));
	Ddim_Print(( "FIN_CLP_B_D2.FIN_CLVLM_B_D2 = 0x%x\n", flt->FIN_CLP_B_D2.bit.FIN_CLVLM_B_D2 ));

	Ddim_Print(( "ISO_MD.ISO_JM = 0x%x\n", flt->ISO_MD.bit.ISO_JM ));
	Ddim_Print(( "ISO_MD.ISO_CM = 0x%x\n", flt->ISO_MD.bit.ISO_CM ));
	Ddim_Print(( "ISO_TH_D[0].ISO_UTH_D = 0x%x\n", flt->ISO_TH_D[0].bit.ISO_UTH_D ));
	Ddim_Print(( "ISO_TH_D[0].ISO_LTH_D = 0x%x\n", flt->ISO_TH_D[0].bit.ISO_LTH_D ));
	Ddim_Print(( "ISO_TH_D[1].ISO_UTH_D = 0x%x\n", flt->ISO_TH_D[1].bit.ISO_UTH_D ));
	Ddim_Print(( "ISO_TH_D[1].ISO_LTH_D = 0x%x\n", flt->ISO_TH_D[1].bit.ISO_LTH_D ));
	Ddim_Print(( "ISO_TH_D[2].ISO_UTH_D = 0x%x\n", flt->ISO_TH_D[2].bit.ISO_UTH_D ));
	Ddim_Print(( "ISO_TH_D[2].ISO_LTH_D = 0x%x\n", flt->ISO_TH_D[2].bit.ISO_LTH_D ));
	Ddim_Print(( "ISO_TH_D[3].ISO_UTH_D = 0x%x\n", flt->ISO_TH_D[3].bit.ISO_UTH_D ));
	Ddim_Print(( "ISO_TH_D[3].ISO_LTH_D = 0x%x\n", flt->ISO_TH_D[3].bit.ISO_LTH_D ));
	Ddim_Print(( "ISO_GAIN_D[0].ISO_GA_D = 0x%x\n", flt->ISO_GAIN_D[0].bit.ISO_GA_D ));
	Ddim_Print(( "ISO_GAIN_D[0].ISO_GB_D = 0x%x\n", flt->ISO_GAIN_D[0].bit.ISO_GB_D ));
	Ddim_Print(( "ISO_GAIN_D[1].ISO_GA_D = 0x%x\n", flt->ISO_GAIN_D[1].bit.ISO_GA_D ));
	Ddim_Print(( "ISO_GAIN_D[1].ISO_GB_D = 0x%x\n", flt->ISO_GAIN_D[1].bit.ISO_GB_D ));
	Ddim_Print(( "ISO_GAIN_D[2].ISO_GA_D = 0x%x\n", flt->ISO_GAIN_D[2].bit.ISO_GA_D ));
	Ddim_Print(( "ISO_GAIN_D[2].ISO_GB_D = 0x%x\n", flt->ISO_GAIN_D[2].bit.ISO_GB_D ));
	Ddim_Print(( "ISO_GAIN_D[3].ISO_GA_D = 0x%x\n", flt->ISO_GAIN_D[3].bit.ISO_GA_D ));
	Ddim_Print(( "ISO_GAIN_D[3].ISO_GB_D = 0x%x\n", flt->ISO_GAIN_D[3].bit.ISO_GB_D ));

	Ddim_Print(( "SPF_MD.SPF_MD = 0x%x\n", flt->SPF_MD.bit.SPF_MD ));

	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_0  = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_0  ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_1  = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_1  ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_2  = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_2  ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_3  = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_3  ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_4  = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_4  ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_5  = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_5  ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_6  = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_6  ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_7  = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_7  ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_8  = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_8  ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_9  = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_9  ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_10 = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_10 ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_11 = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_11 ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_12 = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_12 ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_13 = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_13 ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_14 = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_14 ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_15 = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_15 ));
	Ddim_Print(( "SPF_FLTW_D0.SPF_FLTW_16 = 0x%x\n", flt->SPF_FLTW_D0.bit.SPF_FLTW_16 ));

	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_0  = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_0  ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_1  = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_1  ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_2  = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_2  ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_3  = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_3  ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_4  = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_4  ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_5  = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_5  ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_6  = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_6  ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_7  = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_7  ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_8  = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_8  ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_9  = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_9  ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_10 = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_10 ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_11 = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_11 ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_12 = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_12 ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_13 = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_13 ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_14 = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_14 ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_15 = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_15 ));
	Ddim_Print(( "SPF_FLTW_D1.SPF_FLTW_16 = 0x%x\n", flt->SPF_FLTW_D1.bit.SPF_FLTW_16 ));

	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_0  = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_0  ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_1  = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_1  ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_2  = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_2  ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_3  = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_3  ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_4  = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_4  ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_5  = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_5  ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_6  = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_6  ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_7  = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_7  ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_8  = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_8  ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_9  = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_9  ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_10 = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_10 ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_11 = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_11 ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_12 = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_12 ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_13 = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_13 ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_14 = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_14 ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_15 = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_15 ));
	Ddim_Print(( "SPF_FLTW_D2.SPF_FLTW_16 = 0x%x\n", flt->SPF_FLTW_D2.bit.SPF_FLTW_16 ));

	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_0  = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_0  ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_1  = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_1  ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_2  = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_2  ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_3  = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_3  ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_4  = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_4  ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_5  = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_5  ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_6  = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_6  ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_7  = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_7  ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_8  = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_8  ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_9  = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_9  ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_10 = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_10 ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_11 = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_11 ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_12 = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_12 ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_13 = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_13 ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_14 = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_14 ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_15 = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_15 ));
	Ddim_Print(( "SPF_FLTW_D3.SPF_FLTW_16 = 0x%x\n", flt->SPF_FLTW_D3.bit.SPF_FLTW_16 ));

	Ddim_Print(( "SPF_VTH_D0.SPF_UTH_D0 = 0x%x\n", flt->SPF_VTH_D0.bit.SPF_UTH_D0 ));
	Ddim_Print(( "SPF_VTH_D0.SPF_LTH_D0 = 0x%x\n", flt->SPF_VTH_D0.bit.SPF_LTH_D0 ));

	Ddim_Print(( "SPF_VTH_D1.SPF_UTH_D1 = 0x%x\n", flt->SPF_VTH_D1.bit.SPF_UTH_D1 ));
	Ddim_Print(( "SPF_VTH_D1.SPF_LTH_D1 = 0x%x\n", flt->SPF_VTH_D1.bit.SPF_LTH_D1 ));

	Ddim_Print(( "SPF_VTH_D2.SPF_UTH_D2 = 0x%x\n", flt->SPF_VTH_D2.bit.SPF_UTH_D2 ));
	Ddim_Print(( "SPF_VTH_D2.SPF_LTH_D2 = 0x%x\n", flt->SPF_VTH_D2.bit.SPF_LTH_D2 ));

	Ddim_Print(( "SPF_CORE_D0.SPF_CTHP_D0 = 0x%x\n", flt->SPF_CORE_D0.bit.SPF_CTHP_D0 ));
	Ddim_Print(( "SPF_CORE_D0.SPF_CTHM_D0 = 0x%x\n", flt->SPF_CORE_D0.bit.SPF_CTHM_D0 ));

	Ddim_Print(( "SPF_CORE_D1.SPF_CTHP_D1 = 0x%x\n", flt->SPF_CORE_D1.bit.SPF_CTHP_D1 ));
	Ddim_Print(( "SPF_CORE_D1.SPF_CTHM_D1 = 0x%x\n", flt->SPF_CORE_D1.bit.SPF_CTHM_D1 ));

	Ddim_Print(( "SPF_CORE_D2.SPF_CTHP_D2 = 0x%x\n", flt->SPF_CORE_D2.bit.SPF_CTHP_D2 ));
	Ddim_Print(( "SPF_CORE_D2.SPF_CTHM_D2 = 0x%x\n", flt->SPF_CORE_D2.bit.SPF_CTHM_D2 ));

	Ddim_Print(( "SPF_CLP_D0.SPF_CLVLP_D0 = 0x%x\n", flt->SPF_CLP_D0.bit.SPF_CLVLP_D0 ));
	Ddim_Print(( "SPF_CLP_D0.SPF_CLVLM_D0 = 0x%x\n", flt->SPF_CLP_D0.bit.SPF_CLVLM_D0 ));

	Ddim_Print(( "SPF_CLP_D1.SPF_CLVLP_D1 = 0x%x\n", flt->SPF_CLP_D1.bit.SPF_CLVLP_D1 ));
	Ddim_Print(( "SPF_CLP_D1.SPF_CLVLM_D1 = 0x%x\n", flt->SPF_CLP_D1.bit.SPF_CLVLM_D1 ));

	Ddim_Print(( "SPF_CLP_D2.SPF_CLVLP_D2 = 0x%x\n", flt->SPF_CLP_D2.bit.SPF_CLVLP_D2 ));
	Ddim_Print(( "SPF_CLP_D2.SPF_CLVLM_D2 = 0x%x\n", flt->SPF_CLP_D2.bit.SPF_CLVLM_D2 ));

	Ddim_Print(( "SPF_EOADD_D0.SPF_EOADD_D0 = 0x%x\n", flt->SPF_EOADD_D0.bit.SPF_EOADD_D0 ));
	Ddim_Print(( "SPF_EOADD_D1.SPF_EOADD_D1 = 0x%x\n", flt->SPF_EOADD_D1.bit.SPF_EOADD_D1 ));
	Ddim_Print(( "SPF_EOADD_D2.SPF_EOADD_D2 = 0x%x\n", flt->SPF_EOADD_D2.bit.SPF_EOADD_D2 ));

	Ddim_Print(( "EP_MD.EP_MD = 0x%x\n", flt->EP_MD.bit.EP_MD ));
	Ddim_Print(( "EP_GA_D[0].EP_GA_0 = 0x%x\n", flt->EP_GA_D[0].bit.EP_GA_0 ));
	Ddim_Print(( "EP_GA_D[0].EP_GA_1 = 0x%x\n", flt->EP_GA_D[0].bit.EP_GA_1 ));
	Ddim_Print(( "EP_GA_D[0].EP_GA_2 = 0x%x\n", flt->EP_GA_D[0].bit.EP_GA_2 ));
	Ddim_Print(( "EP_GA_D[1].EP_GA_0 = 0x%x\n", flt->EP_GA_D[1].bit.EP_GA_0 ));
	Ddim_Print(( "EP_GA_D[1].EP_GA_1 = 0x%x\n", flt->EP_GA_D[1].bit.EP_GA_1 ));
	Ddim_Print(( "EP_GA_D[1].EP_GA_2 = 0x%x\n", flt->EP_GA_D[1].bit.EP_GA_2 ));
	Ddim_Print(( "EP_GA_D[2].EP_GA_0 = 0x%x\n", flt->EP_GA_D[2].bit.EP_GA_0 ));
	Ddim_Print(( "EP_GA_D[2].EP_GA_1 = 0x%x\n", flt->EP_GA_D[2].bit.EP_GA_1 ));
	Ddim_Print(( "EP_GA_D[2].EP_GA_2 = 0x%x\n", flt->EP_GA_D[2].bit.EP_GA_2 ));
	Ddim_Print(( "EP_GA_D[3].EP_GA_0 = 0x%x\n", flt->EP_GA_D[3].bit.EP_GA_0 ));
	Ddim_Print(( "EP_GA_D[3].EP_GA_1 = 0x%x\n", flt->EP_GA_D[3].bit.EP_GA_1 ));
	Ddim_Print(( "EP_GA_D[3].EP_GA_2 = 0x%x\n", flt->EP_GA_D[3].bit.EP_GA_2 ));
	Ddim_Print(( "EP_OFS_D[0].EP_OFS_0 = 0x%x\n", flt->EP_OFS_D[0].bit.EP_OFS_0 ));
	Ddim_Print(( "EP_OFS_D[0].EP_OFS_1 = 0x%x\n", flt->EP_OFS_D[0].bit.EP_OFS_1 ));
	Ddim_Print(( "EP_OFS_D[0].EP_OFS_2 = 0x%x\n", flt->EP_OFS_D[0].bit.EP_OFS_2 ));
	Ddim_Print(( "EP_OFS_D[1].EP_OFS_0 = 0x%x\n", flt->EP_OFS_D[1].bit.EP_OFS_0 ));
	Ddim_Print(( "EP_OFS_D[1].EP_OFS_1 = 0x%x\n", flt->EP_OFS_D[1].bit.EP_OFS_1 ));
	Ddim_Print(( "EP_OFS_D[1].EP_OFS_2 = 0x%x\n", flt->EP_OFS_D[1].bit.EP_OFS_2 ));
	Ddim_Print(( "EP_OFS_D[2].EP_OFS_0 = 0x%x\n", flt->EP_OFS_D[2].bit.EP_OFS_0 ));
	Ddim_Print(( "EP_OFS_D[2].EP_OFS_1 = 0x%x\n", flt->EP_OFS_D[2].bit.EP_OFS_1 ));
	Ddim_Print(( "EP_OFS_D[2].EP_OFS_2 = 0x%x\n", flt->EP_OFS_D[2].bit.EP_OFS_2 ));
	Ddim_Print(( "EP_OFS_D[3].EP_OFS_0 = 0x%x\n", flt->EP_OFS_D[3].bit.EP_OFS_0 ));
	Ddim_Print(( "EP_OFS_D[3].EP_OFS_1 = 0x%x\n", flt->EP_OFS_D[3].bit.EP_OFS_1 ));
	Ddim_Print(( "EP_OFS_D[3].EP_OFS_2 = 0x%x\n", flt->EP_OFS_D[3].bit.EP_OFS_2 ));
	Ddim_Print(( "EP_BD_D[0].EP_BD_0 = 0x%x\n", flt->EP_BD_D[0].bit.EP_BD_0 ));
	Ddim_Print(( "EP_BD_D[0].EP_BD_1 = 0x%x\n", flt->EP_BD_D[0].bit.EP_BD_1 ));
	Ddim_Print(( "EP_BD_D[0].EP_BD_2 = 0x%x\n", flt->EP_BD_D[0].bit.EP_BD_2 ));
	Ddim_Print(( "EP_BD_D[1].EP_BD_0 = 0x%x\n", flt->EP_BD_D[1].bit.EP_BD_0 ));
	Ddim_Print(( "EP_BD_D[1].EP_BD_1 = 0x%x\n", flt->EP_BD_D[1].bit.EP_BD_1 ));
	Ddim_Print(( "EP_BD_D[1].EP_BD_2 = 0x%x\n", flt->EP_BD_D[1].bit.EP_BD_2 ));
	Ddim_Print(( "EP_BD_D[2].EP_BD_0 = 0x%x\n", flt->EP_BD_D[2].bit.EP_BD_0 ));
	Ddim_Print(( "EP_BD_D[2].EP_BD_1 = 0x%x\n", flt->EP_BD_D[2].bit.EP_BD_1 ));
	Ddim_Print(( "EP_BD_D[2].EP_BD_2 = 0x%x\n", flt->EP_BD_D[2].bit.EP_BD_2 ));
	Ddim_Print(( "EP_BD_D[3].EP_BD_0 = 0x%x\n", flt->EP_BD_D[3].bit.EP_BD_0 ));
	Ddim_Print(( "EP_BD_D[3].EP_BD_1 = 0x%x\n", flt->EP_BD_D[3].bit.EP_BD_1 ));
	Ddim_Print(( "EP_BD_D[3].EP_BD_2 = 0x%x\n", flt->EP_BD_D[3].bit.EP_BD_2 ));

	Ddim_Print(( "ED_FM = 0x%lx\n", flt->ED_FM.word ));
	Ddim_Print(( "ED_OUT = 0x%lx\n", flt->ED_OUT.word ));

	Ddim_Print(( "ADAPT_K.ADAPT_K0 = 0x%x\n", flt->ADAPT_K.bit.ADAPT_K0 ));
	Ddim_Print(( "ADAPT_K.ADAPT_K1 = 0x%x\n", flt->ADAPT_K.bit.ADAPT_K1 ));
	Ddim_Print(( "ADAPT_K.ADAPT_K2 = 0x%x\n", flt->ADAPT_K.bit.ADAPT_K2 ));
	Ddim_Print(( "ADAPT_TH.ADAPT_TH = 0x%x\n", flt->ADAPT_TH.bit.ADAPT_TH ));
	Ddim_Print(( "ADAPT_DIV.ADAPT_DIV = 0x%x\n", flt->ADAPT_DIV.bit.ADAPT_DIV ));

	Ddim_Print(( "BF_MD = 0x%lx\n", flt->BF_MD.word ));

	Im_IIP_Off_Pclk();

}
#endif //CO_CT_IM_IIP_DISABLE

CtImIipParam* ct_im_iip_param_get(void)
{
	static CtImIipParam* self = NULL;

	if (!self) {
//		self = k_object_new_with_private(CT_TYPE_IM_IIP_PARAM, sizeof(CtImIipParamPrivate));
	}

	return self;
}
