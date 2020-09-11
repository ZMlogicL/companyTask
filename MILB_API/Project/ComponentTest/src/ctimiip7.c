/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIip7
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
#include "ctimiip7.h"


//K_TYPE_DEFINE_WITH_PRIVATE(CtImIip7, ct_im_iip_7)
//#define CT_IM_IIP_7_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIip7Private, CT_TYPE_IM_IIP_7))


struct _CtImIip7Private
{

};


/********
 * IMPL
 */
//static void ct_im_iip_7_constructor(CtImIip7 *self)
//{
//	CtImIip7Private *priv = CT_IM_IIP_7_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_7_destructor(CtImIip7 *self)
//{
//	CtImIip7Private *priv = CT_IM_IIP_7_GET_PRIVATE(self);
//}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_IIP_DISABLE
// Im_IIP_Init 2-1-1
INT32 CT_Im_IIP_2_1_1( VOID)
{
	INT32 ercd;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Init();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x.\n", ercd ));

	return D_DDIM_OK;
}

// Im_IIP_Init_Unit 2-1-2
INT32 CT_Im_IIP_2_1_2( VOID)
{
	INT32 ercd;
	UINT32 loopcnt;
	static const E_IM_IIP_UNIT_ID unit_id[] = { E_IM_IIP_UNIT_ID_LD0, E_IM_IIP_UNIT_ID_LD1, E_IM_IIP_UNIT_ID_LD2, E_IM_IIP_UNIT_ID_LD3, E_IM_IIP_UNIT_ID_FLT, E_IM_IIP_UNIT_ID_AFN0, E_IM_IIP_UNIT_ID_AFN1, E_IM_IIP_UNIT_ID_AFN2, E_IM_IIP_UNIT_ID_FRECT0, E_IM_IIP_UNIT_ID_MON, E_IM_IIP_UNIT_ID_SL0, E_IM_IIP_UNIT_ID_SL1, E_IM_IIP_UNIT_ID_SL2, E_IM_IIP_UNIT_ID_SL3, E_IM_IIP_UNIT_ID_SL4, E_IM_IIP_UNIT_ID_SL5, E_IM_IIP_UNIT_ID_CSC0, E_IM_IIP_UNIT_ID_CSC1, E_IM_IIP_UNIT_ID_LUT, E_IM_IIP_UNIT_ID_GPC, E_IM_IIP_UNIT_ID_BLEND0, E_IM_IIP_UNIT_ID_BLEND1, E_IM_IIP_UNIT_ID_FRECT1, E_IM_IIP_UNIT_ID_CFL0, E_IM_IIP_UNIT_ID_CSC2, E_IM_IIP_UNIT_ID_CSC3, E_IM_IIP_UNIT_ID_SL6, E_IM_IIP_UNIT_ID_SL7, E_IM_IIP_UNIT_ID_SL8, E_IM_IIP_UNIT_ID_LD4, E_IM_IIP_UNIT_ID_LD5, E_IM_IIP_UNIT_ID_LD6, E_IM_IIP_UNIT_ID_LD7, E_IM_IIP_UNIT_ID_AFN3, E_IM_IIP_UNIT_ID_MFT, };

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	for (loopcnt = 0; loopcnt < (sizeof(unit_id) / sizeof(unit_id[0])); loopcnt++)
	{
		Ddim_Print(( D_IM_IIP_FUNC_NAME "** unit_id %u\n", unit_id[loopcnt] ));
		ercd = Im_IIP_Init_Unit(unit_id[loopcnt]);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x.\n", ercd ));
	}

	return D_DDIM_OK;
}

// Im_IIP_Update_PADRS 2-1-3

INT32 CT_Im_IIP_2_1_3( VOID)
{
	INT32 ercd;
	UINT32 loopcnt;
	T_CT_IM_IIP_2_1_3 padrs_tbl[] = { { E_IM_IIP_UNIT_ID_LD0, &IO_IIP.UNITINFTBL_LD0 }, { E_IM_IIP_UNIT_ID_LD1, &IO_IIP.UNITINFTBL_LD1 }, { E_IM_IIP_UNIT_ID_LD2, &IO_IIP.UNITINFTBL_LD2 }, { E_IM_IIP_UNIT_ID_FLT, &IO_IIP.UNITINFTBL_FLT }, { E_IM_IIP_UNIT_ID_AFN0, &IO_IIP.UNITINFTBL_AFN0 }, { E_IM_IIP_UNIT_ID_AFN1, &IO_IIP.UNITINFTBL_AFN1 }, { E_IM_IIP_UNIT_ID_AFN2, &IO_IIP.UNITINFTBL_AFN2 }, { E_IM_IIP_UNIT_ID_FRECT0, &IO_IIP.UNITINFTBL_FRC0 }, { E_IM_IIP_UNIT_ID_MON, &IO_IIP.UNITINFTBL_MON }, { E_IM_IIP_UNIT_ID_SL0, &IO_IIP.UNITINFTBL_SL0 }, { E_IM_IIP_UNIT_ID_SL1, &IO_IIP.UNITINFTBL_SL1 }, { E_IM_IIP_UNIT_ID_SL2, &IO_IIP.UNITINFTBL_SL2 }, { E_IM_IIP_UNIT_ID_SL3, &IO_IIP.UNITINFTBL_SL3 }, { E_IM_IIP_UNIT_ID_SL4, &IO_IIP.UNITINFTBL_SL4 }, { E_IM_IIP_UNIT_ID_SL5, &IO_IIP.UNITINFTBL_SL5 }, { E_IM_IIP_UNIT_ID_CSC0, &IO_IIP.UNITINFTBL_CSC0 }, { E_IM_IIP_UNIT_ID_CSC1, &IO_IIP.UNITINFTBL_CSC1 }, { E_IM_IIP_UNIT_ID_LUT, &IO_IIP.UNITINFTBL_LUT }, { E_IM_IIP_UNIT_ID_GPC, &IO_IIP.UNITINFTBL_GPC }, { E_IM_IIP_UNIT_ID_BLEND0, &IO_IIP.UNITINFTBL_BLD0 }, { E_IM_IIP_UNIT_ID_BLEND1, &IO_IIP.UNITINFTBL_BLD1 }, { E_IM_IIP_UNIT_ID_FRECT1, &IO_IIP.UNITINFTBL_FRC1 }, { E_IM_IIP_UNIT_ID_CFL0, &IO_IIP.UNITINFTBL_CFL0 }, { E_IM_IIP_UNIT_ID_CSC2, &IO_IIP.UNITINFTBL_CSC2 }, { E_IM_IIP_UNIT_ID_CSC3, &IO_IIP.UNITINFTBL_CSC3 }, { E_IM_IIP_UNIT_ID_SL6, &IO_IIP.UNITINFTBL_SL6 }, { E_IM_IIP_UNIT_ID_SL7, &IO_IIP.UNITINFTBL_SL7 }, { E_IM_IIP_UNIT_ID_SL8, &IO_IIP.UNITINFTBL_SL8 }, { E_IM_IIP_UNIT_ID_LD3, &IO_IIP.UNITINFTBL_LD3 }, { E_IM_IIP_UNIT_ID_LD4, &IO_IIP.UNITINFTBL_LD4 }, { E_IM_IIP_UNIT_ID_LD5, &IO_IIP.UNITINFTBL_LD5 }, { E_IM_IIP_UNIT_ID_LD6, &IO_IIP.UNITINFTBL_LD6 }, { E_IM_IIP_UNIT_ID_LD7, &IO_IIP.UNITINFTBL_LD7 }, { E_IM_IIP_UNIT_ID_MFT, &IO_IIP.UNITINFTBL_MFT }, };

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	for (loopcnt = 0; loopcnt < (sizeof(padrs_tbl) / sizeof(T_CT_IM_IIP_2_1_3)); loopcnt++)
	{
		ercd = Im_IIP_Update_PADRS(padrs_tbl[loopcnt].unit_id, loopcnt * 8 + 0x1000);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x.\n", ercd ));

		Im_IIP_On_Pclk();
		if (padrs_tbl[loopcnt].uinftbl->UNITINFTBL2.bit.PADRS != (loopcnt * 8 + 0x1000))
		{
			Ddim_Print(( D_IM_IIP_FUNC_NAME "Error unit_id=%u\n", padrs_tbl[loopcnt].unit_id ));
		}
		Im_IIP_Off_Pclk();
	}

	return D_DDIM_OK;
}

// Im_IIP_Stop 2-2-1
INT32 CT_Im_IIP_2_2_1( VOID)
{
	INT32 ercd;
	T_IM_IIP_PIXFMTTBL pixfmt_tbl_0;		// AFN Unit input
	T_IM_IIP_PIXFMTTBL pixfmt_tbl_1;		// SL Unit output
	T_IM_IIP_UNIT_CFG afn_cfg;
	T_IM_IIP_PARAM_AFN* afn_unit_inf = &g_ct_im_iip_unit_param_afn;
	T_IM_IIP_PARAM_AFN_OPCOL_0* afn_tbl = &g_ct_im_iip_afntbl;
	T_IM_IIP_PARAM_STS* sl_unit_inf = &g_ct_im_iip_unit_param_sl0;
	T_IM_IIP_UNIT_CFG sl_cfg;
	UINT32 wait_factor_result = 0;
	const UINT32 wait_factor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const UINT32 unitid_bitmask = D_IM_IIP_PARAM_PLDUNIT_AFN0 | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const UINT32 pixid_bitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID src_unitid = E_IM_IIP_UNIT_ID_AFN0;
	const E_IM_IIP_UNIT_ID dst_unitid = E_IM_IIP_UNIT_ID_SL2;
	const E_IM_IIP_PARAM_PORTID src_portid = E_IM_IIP_PARAM_PORTID_AFN0;
	const E_IM_IIP_PARAM_PORTID dst_portid = E_IM_IIP_PARAM_PORTID_SL2;
	const UINT32 src_pixid = 4;
	const UINT32 dst_pixid = 5;
	const UINT32 open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG(unitid_bitmask, pixid_bitmask, open_res_bitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
	if (ercd != D_IM_IIP_OK)
	{
		return ercd;
	}

	pixfmt_tbl_0 = g_ct_im_iip_pixfmttbl_base;
	pixfmt_tbl_0.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmt_tbl_0.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_0.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_0.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmt_tbl_0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	pixfmt_tbl_0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmt_tbl_0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmt_tbl_0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A;

	pixfmt_tbl_1 = g_ct_im_iip_pixfmttbl_base;
	pixfmt_tbl_1.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmt_tbl_1.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_1.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_1.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmt_tbl_1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	pixfmt_tbl_1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmt_tbl_1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmt_tbl_1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "afn_tbl = 0x%x 0x%x\n", (UINT32)afn_tbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) ));

	memset(afn_tbl, '\0', sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0));
	afn_tbl->STAXY0.bit.STAX = M_CT_IM_IIP_AFNTBL_CALC_POS(0);
	afn_tbl->STAXY0.bit.STAY = M_CT_IM_IIP_AFNTBL_CALC_POS(0);
	afn_tbl->D_OUT_IN_0.bit.DXX = M_CT_IM_IIP_AFNTBL_CALC_POS(1.0F);	// X increment X=1.0
	afn_tbl->D_OUT_IN_0.bit.DXY = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// X increment Y=0.0
	afn_tbl->D_OUT_IN_0.bit.DYX = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// Y increment X=0.0
	afn_tbl->D_OUT_IN_0.bit.DYY = M_CT_IM_IIP_AFNTBL_CALC_POS(1.0F);	// Y increment Y=1.0
	afn_tbl->SZ.bit.AFNDHSZ = D_IM_IIP_VGA_WIDTH;
	afn_tbl->SZ.bit.AFNDVSZ = D_IM_IIP_VGA_LINES;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "afn_unit_inf = 0x%x 0x%x\n", (UINT32)afn_unit_inf, sizeof(T_IM_IIP_PARAM_AFN) ));
	Ddim_Print(( D_IM_IIP_FUNC_NAME "STAX=0x%x STAY=0x%x\n", (INT32)afn_tbl->STAXY0.bit.STAX, (INT32)afn_tbl->STAXY0.bit.STAY ));

	memset(afn_unit_inf, '\0', sizeof(*afn_unit_inf));
	*afn_unit_inf = g_ct_im_iip_param_afn_base;
	afn_unit_inf->AFNTOPCNF.bit.WAITCONF = dst_portid;
	afn_unit_inf->PIXIDEF.bit.IPIXID = src_pixid;
	afn_unit_inf->AFNPA.word = (ULONG) afn_tbl;

	afn_cfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	afn_cfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	afn_cfg.unit_param_addr = (ULONG) afn_unit_inf;
	afn_cfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "sl_unit_inf = 0x%x 0x%x\n", (UINT32)sl_unit_inf, sizeof(T_IM_IIP_PARAM_STS) ));

	memset(sl_unit_inf, '\0', sizeof(*sl_unit_inf));
	*sl_unit_inf = g_ct_im_iip_param_sts_base;
	sl_unit_inf->BASE.SL_TOPCNF0.bit.DATACONF = src_portid;
	sl_unit_inf->BASE.PIXIDDEF.bit.OPIXID = dst_pixid;

	sl_cfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	sl_cfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	sl_cfg.unit_param_addr = (ULONG) sl_unit_inf;
	sl_cfg.load_unit_param_flag = unitid_bitmask;

	ct_im_iip_clean_l1l2_dcache_addr((ULONG )afn_tbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0));
	ct_im_iip_clean_l1l2_dcache_addr((ULONG )afn_unit_inf, sizeof(T_IM_IIP_PARAM_AFN));
	ct_im_iip_clean_l1l2_dcache_addr((ULONG )sl_unit_inf, sizeof(T_IM_IIP_PARAM_STS));

	ercd = Im_IIP_Ctrl_PIXFMTTBL(src_pixid, &pixfmt_tbl_0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL(dst_pixid, &pixfmt_tbl_1);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(src_unitid, &afn_cfg);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(dst_unitid, &sl_cfg);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt(wait_factor, D_IM_IIP_ENABLE_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	Ddim_Print(( "AFN[0]: PADRS=0x%x HWEN=%u\n", (UINT32)IO_IIP.UNITINFTBL_AFN0.UNITINFTBL2.bit.PADRS, (UINT32)IO_IIP.UNITINFTBL_AFN0.UNITINFTBL0.bit.HWEN ));
	Ddim_Print(( "SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n", (UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS, (UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN, (UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI, (UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO ));
	Im_IIP_Off_Pclk();

	Dd_ARM_Dmb_Pou();

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG(dst_unitid, D_IM_IIP_SWTRG_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG(src_unitid, D_IM_IIP_SWTRG_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Stop( D_IM_IIP_STOP);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End(&wait_factor_result, wait_factor, D_IM_IIP_OR_WAIT, 30);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, wait_factor_result ));

	Im_IIP_On_Pclk();
	if (IO_IIP.IZACTL1.bit.TRG != 2)
	{
		Ddim_Print(( D_IM_IIP_FUNC_NAME "Error\n" ));
	}
	Im_IIP_Off_Pclk();

	if (ercd != D_DDIM_OK)
	{
		Ddim_Print(( D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, wait_factor_result ));
	}

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG(unitid_bitmask, pixid_bitmask, open_res_bitmask);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// Im_IIP_Stop 2-2-2
INT32 CT_Im_IIP_2_2_2( VOID)
{
	INT32 ercd;
	T_IM_IIP_PIXFMTTBL pixfmt_tbl_0;		// AFN Unit input
	T_IM_IIP_PIXFMTTBL pixfmt_tbl_1;		// SL Unit output
	T_IM_IIP_UNIT_CFG afn_cfg;
	T_IM_IIP_PARAM_AFN* afn_unit_inf = &g_ct_im_iip_unit_param_afn;
	T_IM_IIP_PARAM_AFN_OPCOL_0* afn_tbl = &g_ct_im_iip_afntbl;
	T_IM_IIP_PARAM_STS* sl_unit_inf = &g_ct_im_iip_unit_param_sl0;
	T_IM_IIP_UNIT_CFG sl_cfg;
	UINT32 wait_factor_result = 0;
	const UINT32 wait_factor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const UINT32 unitid_bitmask = D_IM_IIP_PARAM_PLDUNIT_AFN0 | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const UINT32 pixid_bitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID src_unitid = E_IM_IIP_UNIT_ID_AFN0;
	const E_IM_IIP_UNIT_ID dst_unitid = E_IM_IIP_UNIT_ID_SL2;
	const E_IM_IIP_PARAM_PORTID src_portid = E_IM_IIP_PARAM_PORTID_AFN0;
	const E_IM_IIP_PARAM_PORTID dst_portid = E_IM_IIP_PARAM_PORTID_SL2;
	const UINT32 src_pixid = 4;
	const UINT32 dst_pixid = 5;
	const UINT32 open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG(unitid_bitmask, pixid_bitmask, open_res_bitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
	if (ercd != D_IM_IIP_OK)
	{
		return ercd;
	}

	pixfmt_tbl_0 = g_ct_im_iip_pixfmttbl_base;
	pixfmt_tbl_0.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmt_tbl_0.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_0.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_0.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmt_tbl_0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	pixfmt_tbl_0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmt_tbl_0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmt_tbl_0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A;

	pixfmt_tbl_1 = g_ct_im_iip_pixfmttbl_base;
	pixfmt_tbl_1.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmt_tbl_1.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_1.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_1.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmt_tbl_1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	pixfmt_tbl_1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmt_tbl_1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmt_tbl_1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "afn_tbl = 0x%x 0x%x\n", (UINT32)afn_tbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) ));

	memset(afn_tbl, '\0', sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0));
	afn_tbl->STAXY0.bit.STAX = M_CT_IM_IIP_AFNTBL_CALC_POS(0);
	afn_tbl->STAXY0.bit.STAY = M_CT_IM_IIP_AFNTBL_CALC_POS(0);
	afn_tbl->D_OUT_IN_0.bit.DXX = M_CT_IM_IIP_AFNTBL_CALC_POS(1.0F);	// X increment X=1.0
	afn_tbl->D_OUT_IN_0.bit.DXY = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// X increment Y=0.0
	afn_tbl->D_OUT_IN_0.bit.DYX = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// Y increment X=0.0
	afn_tbl->D_OUT_IN_0.bit.DYY = M_CT_IM_IIP_AFNTBL_CALC_POS(1.0F);	// Y increment Y=1.0
	afn_tbl->SZ.bit.AFNDHSZ = D_IM_IIP_VGA_WIDTH;
	afn_tbl->SZ.bit.AFNDVSZ = D_IM_IIP_VGA_LINES;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "afn_unit_inf = 0x%x 0x%x\n", (UINT32)afn_unit_inf, sizeof(T_IM_IIP_PARAM_AFN) ));
	Ddim_Print(( D_IM_IIP_FUNC_NAME "STAX=0x%x STAY=0x%x\n", (INT32)afn_tbl->STAXY0.bit.STAX, (INT32)afn_tbl->STAXY0.bit.STAY ));

	memset(afn_unit_inf, '\0', sizeof(*afn_unit_inf));
	*afn_unit_inf = g_ct_im_iip_param_afn_base;
	afn_unit_inf->AFNTOPCNF.bit.WAITCONF = dst_portid;
	afn_unit_inf->PIXIDEF.bit.IPIXID = src_pixid;
	afn_unit_inf->AFNPA.word = (ULONG) afn_tbl;

	afn_cfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	afn_cfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	afn_cfg.unit_param_addr = (ULONG) afn_unit_inf;
	afn_cfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "sl_unit_inf = 0x%x 0x%x\n", (UINT32)sl_unit_inf, sizeof(T_IM_IIP_PARAM_STS) ));

	memset(sl_unit_inf, '\0', sizeof(*sl_unit_inf));
	*sl_unit_inf = g_ct_im_iip_param_sts_base;
	sl_unit_inf->BASE.SL_TOPCNF0.bit.DATACONF = src_portid;
	sl_unit_inf->BASE.PIXIDDEF.bit.OPIXID = dst_pixid;

	sl_cfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	sl_cfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	sl_cfg.unit_param_addr = (ULONG) sl_unit_inf;
	sl_cfg.load_unit_param_flag = unitid_bitmask;

	ct_im_iip_clean_l1l2_dcache_addr((ULONG )afn_tbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0));
	ct_im_iip_clean_l1l2_dcache_addr((ULONG )afn_unit_inf, sizeof(T_IM_IIP_PARAM_AFN));
	ct_im_iip_clean_l1l2_dcache_addr((ULONG )sl_unit_inf, sizeof(T_IM_IIP_PARAM_STS));

	ercd = Im_IIP_Ctrl_PIXFMTTBL(src_pixid, &pixfmt_tbl_0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL(dst_pixid, &pixfmt_tbl_1);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(src_unitid, &afn_cfg);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(dst_unitid, &sl_cfg);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt(wait_factor, D_IM_IIP_ENABLE_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	Ddim_Print(( "AFN[0]: PADRS=0x%x HWEN=%u\n", (UINT32)IO_IIP.UNITINFTBL_AFN0.UNITINFTBL2.bit.PADRS, (UINT32)IO_IIP.UNITINFTBL_AFN0.UNITINFTBL0.bit.HWEN ));
	Ddim_Print(( "SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n", (UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS, (UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN, (UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI, (UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO ));
	Im_IIP_Off_Pclk();

	Dd_ARM_Dmb_Pou();

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG(dst_unitid, D_IM_IIP_SWTRG_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG(src_unitid, D_IM_IIP_SWTRG_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Stop( D_IM_IIP_ABORT);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End(&wait_factor_result, wait_factor, D_IM_IIP_OR_WAIT, 30);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, wait_factor_result ));

	Im_IIP_On_Pclk();
	if (IO_IIP.IZACTL1.bit.TRG != 2)
	{
		Ddim_Print(( D_IM_IIP_FUNC_NAME "Error\n" ));
	}
	Im_IIP_Off_Pclk();

	if (ercd != D_DDIM_OK)
	{
		Ddim_Print(( D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, wait_factor_result ));
	}

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG(unitid_bitmask, pixid_bitmask, open_res_bitmask);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_CT_IM_IIP_DISABLE

CtImIip7* ct_im_iip_7_get(void)
{
	static CtImIip7* self = NULL;

	if (!self) {
//		self = k_object_new_with_private(CT_TYPE_IM_IIP_7, sizeof(CtImIip7Private));
	}

	return self;
}
