/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIip8
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
#include "ctimiip8.h"


//K_TYPE_DEFINE_WITH_PRIVATE(CtImIip8, ct_im_iip_8)
//#define CT_IM_IIP_8_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIip8Private, CT_TYPE_IM_IIP_8))


struct _CtImIip8Private
{

};


/********
 * IMPL
 */
//static void ct_im_iip_8_constructor(CtImIip8 *self)
//{
//	CtImIip8Private *priv = CT_IM_IIP_8_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_8_destructor(CtImIip8 *self)
//{
//	CtImIip8Private *priv = CT_IM_IIP_8_GET_PRIVATE(self);
//}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_IIP_DISABLE
// Im_IIP_Start_SWTRG 2-4-1
INT32 CT_Im_IIP_2_4_1( VOID)
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
	const UINT32 wait_factor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL5END;
	const UINT32 unitid_bitmask = D_IM_IIP_PARAM_PLDUNIT_AFN2 | D_IM_IIP_PARAM_PLDUNIT_SL5;
	const UINT32 pixid_bitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID src_unitid = E_IM_IIP_UNIT_ID_AFN2;
	const E_IM_IIP_UNIT_ID dst_unitid = E_IM_IIP_UNIT_ID_SL5;
	const E_IM_IIP_PARAM_PORTID src_portid = E_IM_IIP_PARAM_PORTID_AFN2;
	const E_IM_IIP_PARAM_PORTID dst_portid = E_IM_IIP_PARAM_PORTID_SL5;
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

	Ddim_Print(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End(&wait_factor_result, wait_factor, D_IM_IIP_OR_WAIT, 30);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, wait_factor_result ));
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

// UNIT register dump 2-6-1
INT32 CT_Im_IIP_2_6_1( VOID)
{
	ULONG* unitdebug;
	ULONG* sdram;
#ifndef CO_DEBUG_ON_PC
	UINT32 loopcnt;
#endif
	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	Im_IIP_Start_DumpUnitReg_ByName("afn0");

	unitdebug = (ULONG*) &IO_IIP.UNITDEBUG;
	sdram = (ULONG*) D_IM_IIP_IMG_MEM_ADDR_1_TOP;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "unitdebug = 0x%lx\n", (ULONG)unitdebug ));
	Ddim_Print(( D_IM_IIP_FUNC_NAME "sdram = 0x%lx\n", (ULONG)sdram ));

	Im_IIP_On_Pclk();
#ifndef CO_DEBUG_ON_PC
	for (loopcnt = 0; loopcnt < (65536 / sizeof(*sdram)); loopcnt++)
	{
		sdram[loopcnt] = unitdebug[loopcnt];
	}
#endif
	Im_IIP_Off_Pclk();

	ct_im_iip_clean_l1l2_dcache_addr((ULONG )sdram, 65536);

	return D_DDIM_OK;
}

// Im_IIP_Clear_HISTGRAM 2-7-1
INT32 CT_Im_IIP_2_7_1( VOID)
{
	INT32 ercd;
	T_IM_IIP_PIXFMTTBL pixfmt_tbl_0;		// 1DL Unit input
	T_IM_IIP_PIXFMTTBL pixfmt_tbl_1;		// SL Unit output
	T_IM_IIP_UNIT_CFG oned_cfg;
	T_IM_IIP_PARAM_1DL* oned_unit_inf = &g_ct_im_iip_unit_param_1dl0;
	T_IM_IIP_PARAM_STS* sl_unit_inf = &g_ct_im_iip_unit_param_sl0;
	T_IM_IIP_UNIT_CFG sl_cfg;
	T_IM_IIP_PARAM_MON* mon_unit_inf = &g_ct_im_iip_unit_param_mon;
	T_IM_IIP_UNIT_CFG mon_cfg;
	UINT32 wait_factor_result = 0;
	const UINT32 wait_factor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL4END;
	const UINT32 unitid_bitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_SL4 | D_IM_IIP_PARAM_PLDUNIT_MON;
	const UINT32 pixid_bitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID src_unitid = E_IM_IIP_UNIT_ID_LD1;
	const E_IM_IIP_UNIT_ID dst_unitid = E_IM_IIP_UNIT_ID_SL4;
	const E_IM_IIP_UNIT_ID mon_unitid = E_IM_IIP_UNIT_ID_MON;
	const E_IM_IIP_PARAM_PORTID src_portid = E_IM_IIP_PARAM_PORTID_LD1;
	const E_IM_IIP_PARAM_PORTID dst_portid = E_IM_IIP_PARAM_PORTID_SL4;
	const UINT32 src_pixid = 4;
	const UINT32 dst_pixid = 5;
	const UINT32 open_res_bitmask = E_IM_IIP_OPEN_RES_CACHE0 | E_IM_IIP_OPEN_RES_HIST_0 | E_IM_IIP_OPEN_RES_HIST_1 | E_IM_IIP_OPEN_RES_HIST_2;
	T_IM_IIP_MAXMON maxmon;
	T_IM_IIP_MINMON minmon;
	T_IM_IIP_ADDMON addmon;
	UINT32 loopcnt;
#ifndef CO_CT_IM_IIP_2_7_1_DISABLE_HIST
	static ULONG buffer_histgram[D_IM_IIP_HIST_MAXBYTES / sizeof(ULONG)] = { 0ul };
	UCHAR histmax;
#endif

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
	pixfmt_tbl_0.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR;

	pixfmt_tbl_1 = g_ct_im_iip_pixfmttbl_base;
	pixfmt_tbl_1.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmt_tbl_1.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_1.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_1.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmt_tbl_1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	pixfmt_tbl_1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmt_tbl_1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmt_tbl_1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;
	pixfmt_tbl_1.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "oned_unit_inf = 0x%x 0x%x\n", (UINT32)oned_unit_inf, sizeof(T_IM_IIP_PARAM_1DL) ));

	memset(oned_unit_inf, '\0', sizeof(*oned_unit_inf));
	*oned_unit_inf = g_ct_im_iip_param_1dl_base;
	oned_unit_inf->LD_TOPCNF0.bit.WAITCONF = dst_portid;
	oned_unit_inf->PIXIDDEF.bit.IPIXID = src_pixid;

	oned_cfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	oned_cfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	oned_cfg.unit_param_addr = (ULONG) oned_unit_inf;
	oned_cfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "sl_unit_inf = 0x%x 0x%x\n", (UINT32)sl_unit_inf, sizeof(T_IM_IIP_PARAM_STS) ));

	memset(sl_unit_inf, '\0', sizeof(*sl_unit_inf));
	*sl_unit_inf = g_ct_im_iip_param_sts_base;
	sl_unit_inf->BASE.SL_TOPCNF0.bit.DATACONF = src_portid;
	sl_unit_inf->BASE.PIXIDDEF.bit.OPIXID = dst_pixid;

	sl_cfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	sl_cfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	sl_cfg.unit_param_addr = (ULONG) sl_unit_inf;
	sl_cfg.load_unit_param_flag = unitid_bitmask;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "mon_unit_inf = 0x%x 0x%x\n", (UINT32)mon_unit_inf, sizeof(T_IM_IIP_PARAM_MON) ));

	memset(mon_unit_inf, '\0', sizeof(*mon_unit_inf));
	*mon_unit_inf = g_ct_im_iip_param_mon_base;
	mon_unit_inf->MONDSEL.bit.DSEL = E_IM_IIP_PARAM_DSEL_SL4;
	mon_unit_inf->HISTCTL[0].bit.BITSEL = E_IM_IIP_PARAM_BITSEL_7_0;
	mon_unit_inf->HISTCTL[1].bit.BITSEL = E_IM_IIP_PARAM_BITSEL_7_0;
	mon_unit_inf->HISTCTL[2].bit.BITSEL = E_IM_IIP_PARAM_BITSEL_7_0;
	mon_unit_inf->HISTCTL[3].bit.BITSEL = E_IM_IIP_PARAM_BITSEL_7_0;

	mon_cfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	mon_cfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	mon_cfg.unit_param_addr = (ULONG) mon_unit_inf;
	mon_cfg.load_unit_param_flag = 0;

	ct_im_iip_clean_l1l2_dcache_addr((ULONG )oned_unit_inf, sizeof(T_IM_IIP_PARAM_1DL));
	ct_im_iip_clean_l1l2_dcache_addr((ULONG )sl_unit_inf, sizeof(T_IM_IIP_PARAM_STS));
	ct_im_iip_clean_l1l2_dcache_addr((ULONG )mon_unit_inf, sizeof(T_IM_IIP_PARAM_MON));

	ercd = Im_IIP_Ctrl_PIXFMTTBL(src_pixid, &pixfmt_tbl_0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL(dst_pixid, &pixfmt_tbl_1);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(src_unitid, &oned_cfg);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(mon_unitid, &mon_cfg);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(dst_unitid, &sl_cfg);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt(wait_factor, D_IM_IIP_ENABLE_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Clear_HISTGRAM(1, 1, 1, 1);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	Ddim_Print(( "ONED[1]: PADRS=0x%x HWEN=%u\n", (UINT32)IO_IIP.UNITINFTBL_LD1.UNITINFTBL2.bit.PADRS, (UINT32)IO_IIP.UNITINFTBL_LD1.UNITINFTBL0.bit.HWEN ));
	Ddim_Print(( "SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n", (UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS, (UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN, (UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI, (UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO ));
	Im_IIP_Off_Pclk();

	Dd_ARM_Dmb_Pou();

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG(dst_unitid, D_IM_IIP_SWTRG_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG(mon_unitid, D_IM_IIP_SWTRG_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start3\n" ));
	ercd = Im_IIP_Start_SWTRG(src_unitid, D_IM_IIP_SWTRG_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End(&wait_factor_result, wait_factor, D_IM_IIP_OR_WAIT, 30);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, wait_factor_result ));
	if (ercd != D_DDIM_OK)
	{
		Ddim_Print(( D_IM_IIP_FUNC_NAME "Abort\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, wait_factor_result ));
	}

	ercd = Im_IIP_Clear_HISTGRAM(1, 1, 1, 1);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

#ifndef CO_CT_IM_IIP_2_7_1_DISABLE_HIST
	Ddim_Print(( D_IM_IIP_FUNC_NAME "** hist_a\n" ));
	ercd = Im_IIP_Get_HISTGRAM(buffer_histgram, NULL, NULL, NULL);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Get_HISTMAX(&histmax, NULL, NULL, NULL);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)buffer_histgram, D_IM_IIP_HIST_MAXBYTES );
	Palladium_Set_Out_Localstack( (ULONG)buffer_histgram, D_IM_IIP_HIST_MAXBYTES );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax ));
#else
// ### REMOVE_RELEASE END
	CT_Im_IIP_Plot_Hist(buffer_histgram, (D_IM_IIP_HIST_MAXBYTES / sizeof(ULONG)), histmax);
	DDIM_User_Dly_Tsk(500);		// Wait for UART output.
// ### REMOVE_RELEASE BEGIN
#endif
// ### REMOVE_RELEASE END

	Ddim_Print(( D_IM_IIP_FUNC_NAME "** hist_b\n" ));
	ercd = Im_IIP_Get_HISTGRAM( NULL, buffer_histgram, NULL, NULL);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Get_HISTMAX( NULL, &histmax, NULL, NULL);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)buffer_histgram, D_IM_IIP_HIST_MAXBYTES );
	Palladium_Set_Out_Localstack( (ULONG)buffer_histgram, D_IM_IIP_HIST_MAXBYTES );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax ));
#else
// ### REMOVE_RELEASE END
	CT_Im_IIP_Plot_Hist(buffer_histgram, (D_IM_IIP_HIST_MAXBYTES / sizeof(ULONG)), histmax);
	DDIM_User_Dly_Tsk(500);		// Wait for UART output.
// ### REMOVE_RELEASE BEGIN
#endif
// ### REMOVE_RELEASE END

	Ddim_Print(( D_IM_IIP_FUNC_NAME "** hist_c\n" ));
	ercd = Im_IIP_Get_HISTGRAM( NULL, NULL, buffer_histgram, NULL);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Get_HISTMAX( NULL, NULL, &histmax, NULL);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)buffer_histgram, D_IM_IIP_HIST_MAXBYTES );
	Palladium_Set_Out_Localstack( (ULONG)buffer_histgram, D_IM_IIP_HIST_MAXBYTES );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax ));
#else
// ### REMOVE_RELEASE END
	CT_Im_IIP_Plot_Hist(buffer_histgram, (D_IM_IIP_HIST_MAXBYTES / sizeof(ULONG)), histmax);
	DDIM_User_Dly_Tsk(500);		// Wait for UART output.
// ### REMOVE_RELEASE BEGIN
#endif
// ### REMOVE_RELEASE END

	Ddim_Print(( D_IM_IIP_FUNC_NAME "** hist_d\n" ));
	ercd = Im_IIP_Get_HISTGRAM( NULL, NULL, NULL, buffer_histgram);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Get_HISTMAX( NULL, NULL, NULL, &histmax);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)buffer_histgram, D_IM_IIP_HIST_MAXBYTES );
	Palladium_Set_Out_Localstack( (ULONG)buffer_histgram, D_IM_IIP_HIST_MAXBYTES );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax ));
#else
// ### REMOVE_RELEASE END
	CT_Im_IIP_Plot_Hist(buffer_histgram, (D_IM_IIP_HIST_MAXBYTES / sizeof(ULONG)), histmax);
// ### REMOVE_RELEASE BEGIN
#endif
// ### REMOVE_RELEASE END
#endif

	ercd = Im_IIP_Get_MAXMON(&maxmon);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Get_MINMON(&minmon);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Get_ADDMON(&addmon);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	for (loopcnt = 0; loopcnt < 4; loopcnt++)
	{
		Ddim_Print(( D_IM_IIP_FUNC_NAME "max_mon[%u]:x=%u y=%u V=%d\n", loopcnt, maxmon.max[loopcnt].pos_x, maxmon.max[loopcnt].pos_y, maxmon.max[loopcnt].value ));
		Ddim_Print(( D_IM_IIP_FUNC_NAME "min_mon[%u]:x=%u y=%u V=%d\n", loopcnt, minmon.min[loopcnt].pos_x, minmon.min[loopcnt].pos_y, minmon.min[loopcnt].value ));
		Ddim_Print(( D_IM_IIP_FUNC_NAME "add_mon[%u]:x=%u y=%u V=%d\n", loopcnt, addmon.add[loopcnt].pos_x, addmon.add[loopcnt].pos_y, addmon.add[loopcnt].value ));
	}

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG(unitid_bitmask, pixid_bitmask, open_res_bitmask);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// for Debug console interface
VOID CT_Im_IIP_Main(INT32 argc, CHAR** argv)
{
	if (argc < 4)
	{
		Ddim_Print(( "Ct_Im_IIP_Main: parameter error.\n" ));
		return;
	}

	CT_Im_IIP_Run((UINT32) atoi((const CHAR*) argv[1]), (UINT32) atoi((const CHAR*) argv[2]), (UINT32) atoi((const CHAR*) argv[3]));
}

#else //CO_CT_IM_IIP_DISABLE
VOID CT_Im_IIP_Main( INT32 argc, CHAR** argv )
{
}
#endif //CO_CT_IM_IIP_DISABLE

CtImIip8* ct_im_iip_8_get(void)
{
	static CtImIip8* self = NULL;

	if (!self) {
//		self = k_object_new_with_private(CT_TYPE_IM_IIP_8, sizeof(CtImIip8Private));
	}

	return self;
}
