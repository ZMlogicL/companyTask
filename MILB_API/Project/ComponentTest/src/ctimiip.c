/*
 *
 *@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
 *@date : 2020-09-03
 *@author : maoguangkun
 *@rely : klib.h
 *@function : 按ETK规范抄写索喜源代码
 *@version : 1.0.0 能正常上屏显示图像
 *
 */

/**
 * @file		ct_im_iip.c
 * @brief		IIP ct code
 * @note		None
 * @attention	None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


// CT header
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

// C Standard header
#include <string.h>
#include <stdlib.h>

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#include <stdio.h>
#endif
#endif //CO_CT_IM_IIP_DISABLE

#include "ctimiip.h"

//K_TYPE_DEFINE_WITH_PRIVATE(CtImIip, ct_im_iip)
//#define CT_IM_IIP_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIipPrivate, CT_TYPE_IM_IIP))

struct _CtImIipPrivate
{

};

//static void ct_im_iip_constructor(CtImIip *self)
//{
//	CtImIipPrivate *priv = CT_IM_IIP_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_destructor(CtImIip *self)
//{
//	CtImIipPrivate *priv = CT_IM_IIP_GET_PRIVATE(self);
//}

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/

// Input Image Memory(for Simulator test)
ULONG gct_im_iip_in_addr[2] = { 0x48000000UL, 0x49000000UL, };
// Output Image Memory(for Simulator test)
ULONG gct_im_iip_out_addr[3] = { 0x4A000000UL, 0x4B000000UL, 0x4C000000UL, };

#ifndef CO_CT_IM_IIP_DISABLE

static const T_CT_IM_IIP_UNITID_TBL g_ct_im_iip_unitid_array[] = { { .pldunit = D_IM_IIP_PARAM_PLDUNIT_LD0, .unitid = E_IM_IIP_UNIT_ID_LD0, .unitname = "LD0", .pUNITINFTBL = &IO_IIP.UNITINFTBL_LD0, .unit_param_dump = ct_im_iip_print_1d_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_LD1, .unitid = E_IM_IIP_UNIT_ID_LD1, .unitname = "LD1", .pUNITINFTBL = &IO_IIP.UNITINFTBL_LD1, .unit_param_dump = ct_im_iip_print_1d_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_LD2, .unitid = E_IM_IIP_UNIT_ID_LD2, .unitname = "LD2", .pUNITINFTBL = &IO_IIP.UNITINFTBL_LD2, .unit_param_dump = ct_im_iip_print_1d_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_LD3, .unitid = E_IM_IIP_UNIT_ID_LD3, .unitname = "LD3", .pUNITINFTBL = &IO_IIP.UNITINFTBL_LD3, .unit_param_dump = ct_im_iip_print_1d_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_FLT, .unitid = E_IM_IIP_UNIT_ID_FLT, .unitname = "FLT", .pUNITINFTBL = &IO_IIP.UNITINFTBL_FLT, .unit_param_dump = ct_im_iip_print_flt_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_AFN0, .unitid = E_IM_IIP_UNIT_ID_AFN0, .unitname = "AFN0", .pUNITINFTBL = &IO_IIP.UNITINFTBL_AFN0, .unit_param_dump = ct_im_iip_print_afn_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_AFN1, .unitid = E_IM_IIP_UNIT_ID_AFN1, .unitname = "AFN1", .pUNITINFTBL = &IO_IIP.UNITINFTBL_AFN1, .unit_param_dump = ct_im_iip_print_afn_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_AFN2, .unitid = E_IM_IIP_UNIT_ID_AFN2, .unitname = "AFN2", .pUNITINFTBL = &IO_IIP.UNITINFTBL_AFN2, .unit_param_dump = ct_im_iip_print_afn_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_FRECT0, .unitid = E_IM_IIP_UNIT_ID_FRECT0, .unitname = "FRC0", .pUNITINFTBL = &IO_IIP.UNITINFTBL_FRC0, .unit_param_dump = ct_im_iip_print_frect_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_MON, .unitid = E_IM_IIP_UNIT_ID_MON, .unitname = "MON", .pUNITINFTBL = &IO_IIP.UNITINFTBL_MON, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_SL0, .unitid = E_IM_IIP_UNIT_ID_SL0, .unitname = "SL0", .pUNITINFTBL = &IO_IIP.UNITINFTBL_SL0, .unit_param_dump = ct_im_iip_print_sl_unit_param, .is_sl = 1, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_SL1, .unitid = E_IM_IIP_UNIT_ID_SL1, .unitname = "SL1", .pUNITINFTBL = &IO_IIP.UNITINFTBL_SL1, .unit_param_dump = ct_im_iip_print_sl_unit_param, .is_sl = 1, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_SL2, .unitid = E_IM_IIP_UNIT_ID_SL2, .unitname = "SL2", .pUNITINFTBL = &IO_IIP.UNITINFTBL_SL2, .unit_param_dump = ct_im_iip_print_sl_unit_param, .is_sl = 1, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_SL3, .unitid = E_IM_IIP_UNIT_ID_SL3, .unitname = "SL3", .pUNITINFTBL = &IO_IIP.UNITINFTBL_SL3, .unit_param_dump = ct_im_iip_print_sl_unit_param, .is_sl = 1, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_SL4, .unitid = E_IM_IIP_UNIT_ID_SL4, .unitname = "SL4", .pUNITINFTBL = &IO_IIP.UNITINFTBL_SL4, .unit_param_dump = ct_im_iip_print_sl_unit_param, .is_sl = 1, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_SL5, .unitid = E_IM_IIP_UNIT_ID_SL5, .unitname = "SL5", .pUNITINFTBL = &IO_IIP.UNITINFTBL_SL5, .unit_param_dump = ct_im_iip_print_sl_unit_param, .is_sl = 1, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_CSC0, .unitid = E_IM_IIP_UNIT_ID_CSC0, .unitname = "CSC0", .pUNITINFTBL = &IO_IIP.UNITINFTBL_CSC0, .unit_param_dump = ct_im_iip_print_csc_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_CSC1, .unitid = E_IM_IIP_UNIT_ID_CSC1, .unitname = "CSC1", .pUNITINFTBL = &IO_IIP.UNITINFTBL_CSC1, .unit_param_dump = ct_im_iip_print_csc_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_LUT, .unitid = E_IM_IIP_UNIT_ID_LUT, .unitname = "LUT", .pUNITINFTBL = &IO_IIP.UNITINFTBL_LUT, .unit_param_dump = ct_im_iip_print_lut_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_GPC, .unitid = E_IM_IIP_UNIT_ID_GPC, .unitname = "GPC", .pUNITINFTBL = &IO_IIP.UNITINFTBL_GPC, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_BLEND0, .unitid = E_IM_IIP_UNIT_ID_BLEND0, .unitname = "BLD0", .pUNITINFTBL = &IO_IIP.UNITINFTBL_BLD0, .unit_param_dump = ct_im_iip_print_blend_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_BLEND1, .unitid = E_IM_IIP_UNIT_ID_BLEND1, .unitname = "BLD1", .pUNITINFTBL = &IO_IIP.UNITINFTBL_BLD1, .unit_param_dump = ct_im_iip_print_blend_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_FRECT1, .unitid = E_IM_IIP_UNIT_ID_FRECT1, .unitname = "FRC1", .pUNITINFTBL = &IO_IIP.UNITINFTBL_FRC1, .unit_param_dump = ct_im_iip_print_frect_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_CFL0, .unitid = E_IM_IIP_UNIT_ID_CFL0, .unitname = "CFL0", .pUNITINFTBL = &IO_IIP.UNITINFTBL_CFL0, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_CSC2, .unitid = E_IM_IIP_UNIT_ID_CSC2, .unitname = "CSC2", .pUNITINFTBL = &IO_IIP.UNITINFTBL_CSC2, .unit_param_dump = ct_im_iip_print_csc_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_CSC3, .unitid = E_IM_IIP_UNIT_ID_CSC3, .unitname = "CSC3", .pUNITINFTBL = &IO_IIP.UNITINFTBL_CSC3, .unit_param_dump = ct_im_iip_print_csc_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_SL6, .unitid = E_IM_IIP_UNIT_ID_SL6, .unitname = "SL6", .pUNITINFTBL = &IO_IIP.UNITINFTBL_SL6, .unit_param_dump = ct_im_iip_print_sl_unit_param, .is_sl = 1, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_SL7, .unitid = E_IM_IIP_UNIT_ID_SL7, .unitname = "SL7", .pUNITINFTBL = &IO_IIP.UNITINFTBL_SL7, .unit_param_dump = ct_im_iip_print_sl_unit_param, .is_sl = 1, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_SL8, .unitid = E_IM_IIP_UNIT_ID_SL8, .unitname = "SL8", .pUNITINFTBL = &IO_IIP.UNITINFTBL_SL8, .unit_param_dump = ct_im_iip_print_sl_unit_param, .is_sl = 1, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_LD4, .unitid = E_IM_IIP_UNIT_ID_LD4, .unitname = "LD4", .pUNITINFTBL = &IO_IIP.UNITINFTBL_LD4, .unit_param_dump = ct_im_iip_print_1d_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_LD5, .unitid = E_IM_IIP_UNIT_ID_LD5, .unitname = "LD5", .pUNITINFTBL = &IO_IIP.UNITINFTBL_LD5, .unit_param_dump = ct_im_iip_print_1d_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_LD6, .unitid = E_IM_IIP_UNIT_ID_LD6, .unitname = "LD6", .pUNITINFTBL = &IO_IIP.UNITINFTBL_LD6, .unit_param_dump = ct_im_iip_print_1d_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_LD7, .unitid = E_IM_IIP_UNIT_ID_LD7, .unitname = "LD7", .pUNITINFTBL = &IO_IIP.UNITINFTBL_LD7, .unit_param_dump = ct_im_iip_print_1d_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_AFN3, .unitid = E_IM_IIP_UNIT_ID_AFN3, .unitname = "AFN3", .pUNITINFTBL = &IO_IIP.UNITINFTBL_AFN3, .unit_param_dump = ct_im_iip_print_afn_unit_param, .is_sl = 0, }, { .pldunit = D_IM_IIP_PARAM_PLDUNIT_MFT, .unitid = E_IM_IIP_UNIT_ID_MFT, .unitname = "MFT", .pUNITINFTBL = &IO_IIP.UNITINFTBL_MFT, .unit_param_dump = ct_im_iip_print_mft_unit_param, .is_sl = 0, }, };

T_CT_IM_IIP_AXI_PRINT_TBL g_ct_im_iip_axi_print_tbl[E_IM_IIP_AXI_ID_MAX] = { [E_IM_IIP_AXI_ID_CACHE0] = { "PDCCTL[0]", &IO_IIP.PDCCTL[0].word }, [E_IM_IIP_AXI_ID_CACHE1] = { "PDCCTL[1]", &IO_IIP.PDCCTL[1].word }, [E_IM_IIP_AXI_ID_CACHE2] = { "PDCCTL[2]", &IO_IIP.PDCCTL[2].word }, [E_IM_IIP_AXI_ID_DP] = { "DPAXICTL", &IO_IIP.DPAXICTL.word }, [E_IM_IIP_AXI_ID_AFN0] = { "AFNAXICTL", &IO_IIP.AFNAXICTL.word[0], &IO_IIP.AFNAXICTL.word[1] }, [E_IM_IIP_AXI_ID_AFN1] = { "AFNAXICTL", &IO_IIP.AFNAXICTL.word[0], &IO_IIP.AFNAXICTL.word[1] }, [E_IM_IIP_AXI_ID_AFN2] = { "AFNAXICTL", &IO_IIP.AFNAXICTL.word[0], &IO_IIP.AFNAXICTL.word[1] }, [E_IM_IIP_AXI_ID_AFN3] = { "AFNAXICTL", &IO_IIP.AFNAXICTL.word[0], &IO_IIP.AFNAXICTL.word[1] }, [E_IM_IIP_AXI_ID_FRECT0] = { "FRAXICTL", &IO_IIP.FRAXICTL.word }, [E_IM_IIP_AXI_ID_FRECT1] = { "FRAXICTL", &IO_IIP.FRAXICTL.word }, [E_IM_IIP_AXI_ID_GPC] = { "GPCAXICTL", &IO_IIP.GPCAXICTL.word }, [E_IM_IIP_AXI_ID_SL0] = { "SLAXICTL1", &IO_IIP.SLAXICTL.SLAXICTL1.word }, [E_IM_IIP_AXI_ID_SL1] = { "SLAXICTL1", &IO_IIP.SLAXICTL.SLAXICTL1.word }, [E_IM_IIP_AXI_ID_SL2] = { "SLAXICTL2", &IO_IIP.SLAXICTL.SLAXICTL2.word }, [E_IM_IIP_AXI_ID_SL3] = { "SLAXICTL2", &IO_IIP.SLAXICTL.SLAXICTL2.word }, [E_IM_IIP_AXI_ID_SL4] = { "SLAXICTL3", &IO_IIP.SLAXICTL.SLAXICTL3.word }, [E_IM_IIP_AXI_ID_SL5] = { "SLAXICTL3", &IO_IIP.SLAXICTL.SLAXICTL3.word }, [E_IM_IIP_AXI_ID_SL6] = { "SLAXICTL4", &IO_IIP.SLAXICTL.SLAXICTL4.word }, [E_IM_IIP_AXI_ID_SL7] = { "SLAXICTL4", &IO_IIP.SLAXICTL.SLAXICTL4.word }, [E_IM_IIP_AXI_ID_SL8] = { "SLAXICTL5", &IO_IIP.SLAXICTL.SLAXICTL5.word }, };

const T_IM_IIP_PIXFMTTBL g_ct_im_iip_pixfmttbl_base = { .pix_depth = D_IM_IIP_PDEPTH_8BITS, .alpha = D_IM_IIP_ALPHA_FALSE, .frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR, .pix_format = E_IM_IIP_PFMT_YCC422, .alpha_depth = E_IM_IIP_ADEPTH_8BITS, .chunky_color = { .component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G, .component1 = D_IM_IIP_CHUNKY_COLOR_CB_B, .component2 = D_IM_IIP_CHUNKY_COLOR_CR_R, .component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A, }, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA, .sign_Cb_B = D_IM_IIP_UNSIGNED_DATA, .sign_Cr_R = D_IM_IIP_UNSIGNED_DATA, .sign_D3 = D_IM_IIP_UNSIGNED_DATA, .masterIF_Y_G = D_IM_IIP_MASTER_IF0, .masterIF_Cb_B = D_IM_IIP_MASTER_IF0, .masterIF_Cr_R = D_IM_IIP_MASTER_IF0, .masterIF_Alpha = D_IM_IIP_MASTER_IF0, .alpha_subsampling = D_IM_IIP_ALPHA_NO_SUBSAMP, .pix_outside_img = D_IM_IIP_OUTSIDE_IMG_EDGE, .Y_G_val_outside_img = 0,// dummy
.Cb_B_val_outside_img = 0,				// dummy
.Cr_R_val_outside_img = 0,				// dummy
.Alpha_val_outside_img = 0,				// dummy
.width = D_IM_IIP_VGA_WIDTH, .lines = D_IM_IIP_VGA_LINES,
//	.line_bytes = {
//		.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
//		.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
//		.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
//		.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH,
//	},
//	.addr = {
//		.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y,
//		.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
//		.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
//		.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A,
//	},
};

const T_IM_IIP_PARAM_AFN g_ct_im_iip_param_afn_base = { .header0.bit.BeginningAddress = 0x0000, .header0.bit.WordLength = 29, .header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, .AFNTOPCNF.bit.DATACONF = 0,	// Register default
//	.AFNTOPCNF.bit.WAITCONF,							// set later
.AFNLDCNF.bit.DTHD = E_IM_IIP_PARAM_DTHD_NORMAL, .AFNLDCNF.bit.CBC = E_IM_IIP_PARAM_CBC_DISABLE, .AFNCTL.bit.HSMD = E_IM_IIP_PARAM_HSMD_NORMAL, .AFNCTL.bit.LPLVL = E_IM_IIP_PARAM_LPLVL_H_LEVEL, .AFNCTL.bit.HDBL = E_IM_IIP_PARAM_HDBL_SAME_AS_PICHSZ, .AFNCTL.bit.VDBL = E_IM_IIP_PARAM_VDBL_SAME_AS_PICVSZ, .AFNCTL.bit.GHSZ = E_IM_IIP_PARAM_GHSZ_64PIX,// Needs tuning
.AFNCTL.bit.GVSZ = E_IM_IIP_PARAM_GVSZ_8PIX,		// Needs tuning
.PFCTL.bit.PFEXTMC = 4, .PFCTL.bit.PFEXTADC = 64,							// Needs tuning
.PFCTL.bit.PFSP1 = E_IM_IIP_PARAM_PFSP_16,			// Needs tuning
.PFCTL.bit.PFSP2 = E_IM_IIP_PARAM_PFSP_16,			// Needs tuning
.PFCTL.bit.PFVSP = E_IM_IIP_PARAM_PFVSP_VERTICAL_0,	// Needs tuning
.PFCTL.bit.PFOFF = E_IM_IIP_PARAM_PFOFF_RUN, .PIXIDEF.bit.EXA = E_IM_IIP_PARAM_EXA_NO_ALPHA_TO_NEXT_UNIT, .PIXIDEF.bit.CSEL = E_IM_IIP_PARAM_CSEL_0,// ImgCache
//	.PIXIDEF.bit.IPIXID,								// set later
.OUTSIZE.bit.OUTHSZ = 0, .OUTSIZE.bit.OUTVSZ = 0, .OUTSTARTPOS.bit.STARTX = 0, .OUTSTARTPOS.bit.STARTY = 0, .CALMETHOD.bit.OPCOL = 0, .CALMETHOD.bit.ITMD = E_IM_IIP_PARAM_ITMD_BI_LINEAR, .CALMETHOD.bit.ARA = E_IM_IIP_PARAM_ARA_ITMD, .CALMETHOD.bit.FILMD = 0, .CALMETHOD.bit.DANTI = 1, .CALMETHOD.bit.AANTI = 1, .CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN0, .CALMETHOD.bit.SCUB = E_IM_IIP_PARAM_SCUB_0, .FILVAL0.bit.FILVALYG = 0x0, .FILVAL0.bit.FILVALB = 0x0, .FILVAL1.bit.FILVALR = 0x0, .FILVAL1.bit.FILVALA = 0x0, .OPMD.bit.OPMD0 = E_IM_IIP_PARAM_OPMD_NON, .OPY.bit.OPBY = 0, .OPY.bit.OPAY = 0, .OPB.bit.OPBB = 0, .OPB.bit.OPAB = 0, .OPR.bit.OPBR = 0, .OPR.bit.OPAR = 0, .OPA.bit.OPBA = 0, .OPA.bit.OPAA = 0, .CLIPLVLY.bit.CLIPLVLYH = 0xFFFF, .CLIPLVLY.bit.CLIPLVLYL = 0, .CLIPLVLB.bit.CLIPLVLBH = 0xFFFF, .CLIPLVLB.bit.CLIPLVLBL = 0, .CLIPLVLR.bit.CLIPLVLRH = 0xFFFF, .CLIPLVLR.bit.CLIPLVLRL = 0, .CLIPLVLA.bit.CLIPLVLAH = 0xFFFF, .CLIPLVLA.bit.CLIPLVLAL = 0, .AFNPCNT.bit.AFNPHCNT = 1, .AFNPCNT.bit.AFNPVCNT = 1,
//	.AFNPA.word = (ULONG)afntbl,						// set later
.UPLK_TARGET.bit.UPSU0 = E_IM_IIP_PARAM_UPSU_NONE, .UPLK_TARGET.bit.UPSU1 = E_IM_IIP_PARAM_UPSU_NONE, .UPLK_TARGET.bit.UPSU2 = 0, .DWLK_TARGET.bit.DWSU0 = E_IM_IIP_PARAM_DWSU_NONE, .DWLK_TARGET.bit.DWSU1 = E_IM_IIP_PARAM_DWSU_NONE, .DWLK_TARGET.bit.DWSU2 = 0, .LKNUM.bit.UPNUM = E_IM_IIP_PARAM_UPNUM_NONE, .LKNUM.bit.DWNUM = E_IM_IIP_PARAM_DWNUM_NONE, .RING.bit.URINGSIZE = 0, .RING.bit.UMARGINIYSZ = 0, .RING.bit.DRINGSIZE = 0, };

const T_IM_IIP_PARAM_FRECT g_ct_im_iip_param_frect_base = { .header0.bit.BeginningAddress = 0x0000, .header0.bit.WordLength = 29, .header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, .FRTOPCNF.bit.DATACONF = 0,
//	.FRTOPCNF.bit.WAITCONF,							// set later
.FRLDCNF.bit.DTHD = E_IM_IIP_PARAM_DTHD_NORMAL, .FRCTL.bit.HSMD = E_IM_IIP_PARAM_HSMD_NORMAL, .FRCTL.bit.LPLVL = E_IM_IIP_PARAM_LPLVL_H_LEVEL, .FRCTL.bit.HDBL = E_IM_IIP_PARAM_HDBL_SAME_AS_PICHSZ, .FRCTL.bit.VDBL = E_IM_IIP_PARAM_VDBL_SAME_AS_PICVSZ, .FRCTL.bit.GHSZ = E_IM_IIP_PARAM_GHSZ_64PIX,	// Needs tuning
.FRCTL.bit.GVSZ = E_IM_IIP_PARAM_GVSZ_SAME_AS_VERTICAL_PIX,		// Needs tuning
.PFCTL.bit.PFEXTMC = 4, .PFCTL.bit.PFEXTADC = 16,							// Needs tuning
.PFCTL.bit.PFSP1 = E_IM_IIP_PARAM_PFSP_16,			// Needs tuning
.PFCTL.bit.PFSP2 = E_IM_IIP_PARAM_PFSP_16,			// Needs tuning
.PFCTL.bit.PFVSP = E_IM_IIP_PARAM_PFVSP_VERTICAL_0,	// Needs tuning
.PFCTL.bit.PFOFF = E_IM_IIP_PARAM_PFOFF_RUN, .PIXIDEF.bit.EXA = E_IM_IIP_PARAM_EXA_NO_ALPHA_TO_NEXT_UNIT, .PIXIDEF.bit.CSEL = E_IM_IIP_PARAM_CSEL_0,// ImgCache
//	.PIXIDEF.bit.IPIXID,								// set later
.OUTSIZE.bit.OUTHSZ = 0, .OUTSIZE.bit.OUTVSZ = 0, .OUTSTARTPOS.bit.STARTX = 0, .OUTSTARTPOS.bit.STARTY = 0, .CALMETHOD.bit.OPCOL = 0, .CALMETHOD.bit.ITMD = E_IM_IIP_PARAM_ITMD_BI_LINEAR, .CALMETHOD.bit.ARA = E_IM_IIP_PARAM_ARA_ITMD, .CALMETHOD.bit.FILMD = 0, .CALMETHOD.bit.DANTI = 1, .CALMETHOD.bit.AANTI = 1, .CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN0, .CALMETHOD.bit.SCUB = E_IM_IIP_PARAM_SCUB_0, .FILVAL0.bit.FILVALYG = 0x0, .FILVAL0.bit.FILVALB = 0x0, .FILVAL1.bit.FILVALR = 0x0, .FILVAL1.bit.FILVALA = 0x0, .OPMD.bit.OPMD0 = E_IM_IIP_PARAM_OPMD_NON, .OPY.bit.OPBY = 0, .OPY.bit.OPAY = 0, .OPB.bit.OPBB = 0, .OPB.bit.OPAB = 0, .OPR.bit.OPBR = 0, .OPR.bit.OPAR = 0, .OPA.bit.OPBA = 0, .OPA.bit.OPAA = 0, .CLIPLVLY.bit.CLIPLVLYH = 0xFFFF, .CLIPLVLY.bit.CLIPLVLYL = 0, .CLIPLVLB.bit.CLIPLVLBH = 0xFFFF, .CLIPLVLB.bit.CLIPLVLBL = 0, .CLIPLVLR.bit.CLIPLVLRH = 0xFFFF, .CLIPLVLR.bit.CLIPLVLRL = 0, .CLIPLVLA.bit.CLIPLVLAH = 0xFFFF, .CLIPLVLA.bit.CLIPLVLAL = 0,
//	.FRPCNT.bit.FRPHCNT = 1,							// set later
//	.FRPCNT.bit.FRPVCNT = 1,							// set later
//	.PADRS.word = (ULONG)frecttbl,						// set later
.UPLK_TARGET.bit.UPSU0 = E_IM_IIP_PARAM_UPSU_NONE, .UPLK_TARGET.bit.UPSU1 = E_IM_IIP_PARAM_UPSU_NONE, .UPLK_TARGET.bit.UPSU2 = 0, .DWLK_TARGET.bit.DWSU0 = E_IM_IIP_PARAM_DWSU_NONE, .DWLK_TARGET.bit.DWSU1 = E_IM_IIP_PARAM_DWSU_NONE, .DWLK_TARGET.bit.DWSU2 = 0, .LKNUM.bit.UPNUM = E_IM_IIP_PARAM_UPNUM_NONE, .LKNUM.bit.DWNUM = E_IM_IIP_PARAM_DWNUM_NONE, .RING.bit.URINGSIZE = 0, .RING.bit.UMARGINIYSZ = 0, .RING.bit.DRINGSIZE = 0, };

const T_IM_IIP_PARAM_1DL g_ct_im_iip_param_1dl_base = { .header0.bit.BeginningAddress = 0x0004, .header0.bit.WordLength = 16, .header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET,
//	.LD_TOPCNF0.bit.WAITCONF,							// set later
.LD_TOPCNF1.bit.LINK_UID = 0,
//	.PIXIDDEF.bit.IPIXID,								// set later
.LD_CTL.bit.LD_MODE = E_IM_IIP_PARAM_LD_MODE_NORMAL_LOAD, .LD_CTL.bit.LD_OUT = 0, .LD_CTL.bit.SLOW = E_IM_IIP_PARAM_SLOW_1PIX_CYC, .LD_CTL.bit.SAVERD = 0, .LD_CTL.bit.CSEL = E_IM_IIP_PARAM_CSEL_0, .LD_PREFETCH.bit.PFOFF = E_IM_IIP_PARAM_PFOFF_RUN, .LD_PREFETCH.bit.PF_PDIST = E_IM_IIP_PARAM_PF_PDIST_8PIX, .LD_PREFETCH.bit.PF_1ST = E_IM_IIP_PARAM_PF_1ST_ACCESS_BEFORE_PF, .LD_PREFETCH.bit.PFB_NUM = 0,// Need tuning
.LD_PREFETCH.bit.PF_ADD = 0,						// Need tuning
.LD_HSIZE.bit.HSTART = 0, .LD_HSIZE.bit.HEND = D_IM_IIP_VGA_WIDTH - 1, .LD_VSIZE.bit.VSTART = 0, .LD_VSIZE.bit.VEND = D_IM_IIP_VGA_LINES - 1, .LD_PHSZ.bit.PHSZ1 = 64, .LD_PVSZ.bit.PVSZ1 = 8, .LD_PHSZ.bit.PHSZ0 = 64, .LD_PVSZ.bit.PVSZ0 = 8, .UPLK_TARGET.bit.UPSU0 = E_IM_IIP_PARAM_UPSU_NONE, .UPLK_TARGET.bit.UPSU1 = E_IM_IIP_PARAM_UPSU_NONE, .UPLK_TARGET.bit.UPSU2 = 0, .DWLK_TARGET.bit.DWSU0 = E_IM_IIP_PARAM_DWSU_NONE, .DWLK_TARGET.bit.DWSU1 = E_IM_IIP_PARAM_DWSU_NONE, .DWLK_TARGET.bit.DWSU2 = 0, .LKNUM.bit.UPNUM = E_IM_IIP_PARAM_UPNUM_NONE, .LKNUM.bit.DWNUM = E_IM_IIP_PARAM_DWNUM_NONE, .RING.bit.URINGSIZE = 0, .RING.bit.UMARGINIYSZ = 0, .RING.bit.DRINGSIZE = 0, };

const T_IM_IIP_PARAM_BLEND g_ct_im_iip_param_blend_base = { .header0.bit.BeginningAddress = 0x0000, .header0.bit.WordLength = 4, .header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_LOAD_ONLY,
//	.BLENDTOPCNF0.bit.WAITCONF_0 = ,							// set later
//	.BLENDTOPCNF0.bit.DATACONF_0 = ,							// set later
//	.BLENDTOPCNF1.bit.WAITCONF_1 = ,							// set later
//	.BLENDTOPCNF1.bit.DATACONF_1 = ,							// set later
.BLENDTOPCNF2.bit.DATACONF_2 = E_IM_IIP_PARAM_PORTID_NONE, .header1.bit.BeginningAddress = 0x0080, .header1.bit.WordLength = 24, .header1.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, .BLENDCTL.bit.BLD_MD = E_IM_IIP_PARAM_BLD_MD_ALPHA_BLEND, .BLENDCTL.bit.CLP_MD = E_IM_IIP_PARAM_CLP_MD_NO_CLIP, .BLENDCTL.bit.ALPHA_OUT = E_IM_IIP_PARAM_ALPHA_OUT_NONE, .ALPHACTL0.bit.ALPHA_STEP = E_IM_IIP_PARAM_ALPHA_STEP_8BITS, .ALPHACTL0.bit.ALPHA_SEL = E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL, .ALPHACTL1.bit.ALPHA_VAL0 = 128, .ALPHACTL1.bit.ALPHA_VAL1 = 128, .ALPHACTL2.bit.ALPHA_VAL2 = 128, .ALPHACTL2.bit.ALPHA_VAL3 = 128, .WADDCTL[0].bit.WADD_KA = 0, .WADDCTL[0].bit.WADD_KB = 0, .WADDCTL[1].bit.WADD_KA = 0, .WADDCTL[1].bit.WADD_KB = 0, .WADDCTL[2].bit.WADD_KA = 0, .WADDCTL[2].bit.WADD_KB = 0, .WADDCTL[3].bit.WADD_KA = 0, .WADDCTL[3].bit.WADD_KB = 0, .DIVCTL0.bit.RSFT = 0xF, .MSKCTL0.bit.MSKSEL = 0, .MSKCTL0.bit.DINSEL = 0, .MULCTL[0].bit.ADDVAL_A = 0, .MULCTL[0].bit.ADDVAL_B = 0, .MULCTL[0].bit.ADDVAL_C = 0, .MULCTL[0].bit.SFTSEL = E_IM_IIP_PARAM_SFTSEL_NONE, .MULCTL[1].bit.ADDVAL_A = 0, .MULCTL[1].bit.ADDVAL_B = 0, .MULCTL[1].bit.ADDVAL_C = 0, .MULCTL[1].bit.SFTSEL = E_IM_IIP_PARAM_SFTSEL_NONE, .MULCTL[2].bit.ADDVAL_A = 0, .MULCTL[2].bit.ADDVAL_B = 0, .MULCTL[2].bit.ADDVAL_C = 0, .MULCTL[2].bit.SFTSEL = E_IM_IIP_PARAM_SFTSEL_NONE, .MULCTL[3].bit.ADDVAL_A = 0, .MULCTL[3].bit.ADDVAL_B = 0, .MULCTL[3].bit.ADDVAL_C = 0, .MULCTL[3].bit.SFTSEL = E_IM_IIP_PARAM_SFTSEL_NONE, };

const T_IM_IIP_PARAM_STS g_ct_im_iip_param_sts_base = { .header0.bit.BeginningAddress = 0x0000, .header0.bit.WordLength = 26, .header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_LOAD_ONLY, .BASE = { .SL_TOPCNF0.bit.WAITCONF = E_IM_IIP_PARAM_PORTID_NONE,
//		.SL_TOPCNF0.bit.DATACONF,		// set later
//		.PIXIDDEF.bit.OPIXID,			// set later
.PIXIDDEF.bit.CSEL = E_IM_IIP_PARAM_CSEL_0,	// dummy
.PIXIDDEF.bit.DIV1ST = E_IM_IIP_PARAM_DIV1ST_1ST, .PIXIDDEF.bit.LKDIV = 0,

.PLDUNIT_SL.bit.PLDUNIT_SL_LO = Im_IIP_Get_PLDUNIT_Lo(D_IM_IIP_PARAM_PLDUNIT_NONE), .PLDUNIT_SL.bit.PLDUNIT_SL_HI = Im_IIP_Get_PLDUNIT_Hi(D_IM_IIP_PARAM_PLDUNIT_NONE),

.SL_CTL.bit.SL_MODE = 0, .SL_CTL.bit.LOADMD = 0, .SL_CTL.bit.MASKEN = E_IM_IIP_PARAM_MASKEN_NO_MASK,

.OUTCOL.bit.OUTCOL = 0,

.SL_HSIZE.bit.HSTART = 0, .SL_HSIZE.bit.HEND = D_IM_IIP_VGA_WIDTH - 1, .SL_VSIZE.bit.VSTART = 0, .SL_VSIZE.bit.VEND = D_IM_IIP_VGA_LINES - 1, .SL_PHSZ.bit.PHSZ1 = 64, .SL_PVSZ.bit.PVSZ1 = 8, .SL_PHSZ.bit.PHSZ0 = 64, .SL_PVSZ.bit.PVSZ0 = 8,

.SEL_OPARA.bit.SEL_OPARA = 0,

.OFSET_0.bit.OFSET = 0, .CLPTH_U_0.bit.CLPTH_U = 0x3FFF, .CLPTH_L_0.bit.CLPTH_L = -0x4000, .CLPVAL_U_0.bit.CLPVAL_U = 0x3FFF, .CLPVAL_L_0.bit.CLPVAL_L = -0x4000, .SFT_0.bit.SFTVAL = 0, .SFT_0.bit.SFTM = E_IM_IIP_PARAM_SFTM_ROUNDDOWN, .W14MD_0.bit.W14LSFT = 0, .W14MD_0.bit.W14SAT = 0, },

.header1.bit.BeginningAddress = 0x0200, .header1.bit.WordLength = 2, .header1.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, .FILL_EN.bit.FILL_EN0 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN1 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN2 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN3 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN4 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN5 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN6 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN7 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN8 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN9 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN10 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN11 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN12 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN13 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN14 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN15 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN16 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN17 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN18 = E_IM_IIP_PARAM_FILL_EN_DISABLE, .FILL_EN.bit.FILL_EN19 = E_IM_IIP_PARAM_FILL_EN_DISABLE, };

const T_IM_IIP_PARAM_CSC g_ct_im_iip_param_csc_base = { .header0.bit.BeginningAddress = 0x0000, .header0.bit.WordLength = 25, .header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET,
//	.CSCTOPCNF.bit.WAITCONF = ,		// set later
//	.CSCTOPCNF.bit.DATACONF = ,		// set later
.CSCK = { [0] = { .bit.CSCK_0 = (LONG) (1.0F * 0x1000), .bit.CSCK_1 = 0, .bit.CSCK_2 = 0, .bit.CSCK_3 = 0, }, [1] = { .bit.CSCK_0 = 0, .bit.CSCK_1 = (LONG) (1.0F * 0x1000), .bit.CSCK_2 = 0, .bit.CSCK_3 = 0, }, [2] = { .bit.CSCK_0 = 0, .bit.CSCK_1 = 0, .bit.CSCK_2 = (LONG) (1.0F * 0x1000), .bit.CSCK_3 = 0, }, [3] = { .bit.CSCK_0 = 0, .bit.CSCK_0 = 0, .bit.CSCK_2 = 0, .bit.CSCK_3 = (LONG) (1.0F * 0x1000), }, }, .MDSEL.bit.MDSEL = 1, .ALPSEL.bit.ALPSEL = E_IM_IIP_PARAM_ALPSEL_DIRECT, .ALPSEL.bit.ALOSEL = E_IM_IIP_PARAM_ALOSEL_CALCULATED, .ALPVAL.bit.ALPVAL = 0, .MAXMIN.bit.MAXMIN0 = E_IM_IIP_PARAM_MAXMIN_THROUGH, .MAXMIN.bit.MAXMIN1 = E_IM_IIP_PARAM_MAXMIN_THROUGH, .MAXMIN.bit.MAXMIN2 = E_IM_IIP_PARAM_MAXMIN_THROUGH, .MAXMIN.bit.MAXMIN3 = E_IM_IIP_PARAM_MAXMIN_THROUGH, .OUTCLIP.bit.CLPMAX0 = 0x3fff, .OUTCLIP.bit.CLPMIN0 = 0x4000, .OUTCLIP.bit.CLPMAX1 = 0x3fff, .OUTCLIP.bit.CLPMIN1 = 0x4000, .OUTCLIP.bit.CLPMAX2 = 0x3fff, .OUTCLIP.bit.CLPMIN2 = 0x4000, .OUTCLIP.bit.CLPMAX3 = 0xff, .OUTCLIP.bit.CLPMIN3 = 0x100, };

const T_IM_IIP_PARAM_FLT g_ct_im_iip_param_flt_base = { .header0.bit.BeginningAddress = 0x0000, .header0.bit.WordLength = 145, .header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET,
//	.TDLTOPCNF.bit.WAITCONF_0 = 0,		// set later
.TDLTOPCNF.bit.WAITCONF_1 = E_IM_IIP_PARAM_PORTID_NONE, .TDLTOPCNF.bit.DATACONF = E_IM_IIP_PARAM_PORTID_NONE,
//	.PIXIDDEF.bit.IPIXID0 = ,		// set later
.PIXIDDEF.bit.IPIXID1 = 0, .TDL_CTL.bit.FM = E_IM_IIP_PARAM_FM_3x3, .TDL_CTL.bit.LNUM = E_IM_IIP_PARAM_LNUM_SLOW, .TDL_CTL.bit.SAVERD = 0, .TDL_CTL.bit.INPUT_MODE = E_IM_IIP_PARAM_INPUT_MODE_NORMAL, .TDL_CTL.bit.CSEL = E_IM_IIP_PARAM_CSEL_0, .CALC_MD.bit.CALC_MD = E_IM_IIP_PARAM_CALC_MD_NORMAL, .TDL_HSIZE.bit.HSTART = 0, .TDL_HSIZE.bit.HEND = D_IM_IIP_VGA_WIDTH - 1, .TDL_VSIZE.bit.VSTART = 0, .TDL_VSIZE.bit.VEND = D_IM_IIP_VGA_LINES - 1, .TDL_PHSZ.bit.PHSZ0 = 64, .TDL_PVSZ.bit.PVSZ0 = 8, .TDL_PHSZ.bit.PHSZ1 = 64, .TDL_PVSZ.bit.PVSZ1 = 8, .TDL_PF.bit.PF_ON = E_IM_IIP_PARAM_PF_ON_ACTIVE, .TDL_PF.bit.PF_MD = E_IM_IIP_PARAM_PF_MD_PREFETCH, .TDL_PF.bit.PF_NUM = 16, .TDL_PF.bit.PF_ADJ_NUM = 0xf, .TDL_PF.bit.PF_ADJ_VAL = 0xffff, .UPLK_TARGET.bit.UPSU0 = E_IM_IIP_PARAM_UPSU_NONE, .UPLK_TARGET.bit.UPSU1 = E_IM_IIP_PARAM_UPSU_NONE, .UPLK_TARGET.bit.UPSU2 = 0, .DWLK_TARGET.bit.DWSU0 = E_IM_IIP_PARAM_DWSU_NONE, .DWLK_TARGET.bit.DWSU1 = E_IM_IIP_PARAM_DWSU_NONE, .DWLK_TARGET.bit.DWSU2 = 0, .LKNUM.bit.UPNUM = E_IM_IIP_PARAM_UPNUM_NONE, .LKNUM.bit.DWNUM = E_IM_IIP_PARAM_DWNUM_NONE, .RING.bit.URINGSIZE = 0, .RING.bit.UMARGINIYSZ = 0, .RING.bit.DRINGSIZE = 0, .UNIT_OUT.bit.UNIT_OUT_A_D0 = E_IM_IIP_PARAM_UNIT_OUT_SPF,	// port 0
.UNIT_OUT.bit.UNIT_OUT_A_D1 = E_IM_IIP_PARAM_UNIT_OUT_SPF,		// port 0
.UNIT_OUT.bit.UNIT_OUT_A_D2 = E_IM_IIP_PARAM_UNIT_OUT_SPF,		// port 0
.UNIT_OUT.bit.UNIT_OUT_B_D0 = E_IM_IIP_PARAM_UNIT_OUT_DISABLE,	// port 1
.UNIT_OUT.bit.UNIT_OUT_B_D1 = E_IM_IIP_PARAM_UNIT_OUT_DISABLE,	// port 1
.UNIT_OUT.bit.UNIT_OUT_B_D2 = E_IM_IIP_PARAM_UNIT_OUT_DISABLE,	// port 1
.FIN_CLP_A_D0.bit.FIN_CLVLP_A_D0 = 0x3fff, .FIN_CLP_A_D0.bit.FIN_CLVLM_A_D0 = 0x4000, .FIN_CLP_A_D1.bit.FIN_CLVLP_A_D1 = 0xff, .FIN_CLP_A_D1.bit.FIN_CLVLM_A_D1 = 0x100, .FIN_CLP_A_D2.bit.FIN_CLVLP_A_D2 = 0xff, .FIN_CLP_A_D2.bit.FIN_CLVLM_A_D2 = 0x100, .FIN_CLP_B_D0.bit.FIN_CLVLP_B_D0 = 0x3fff, .FIN_CLP_B_D0.bit.FIN_CLVLM_B_D0 = 0x4000, .FIN_CLP_B_D1.bit.FIN_CLVLP_B_D1 = 0xff, .FIN_CLP_B_D1.bit.FIN_CLVLM_B_D1 = 0x100, .FIN_CLP_B_D2.bit.FIN_CLVLP_B_D2 = 0xff, .FIN_CLP_B_D2.bit.FIN_CLVLM_B_D2 = 0x100, .ISO_MD.bit.ISO_JM = 0, .ISO_MD.bit.ISO_CM = 0, .ISO_TH_D[0].bit.ISO_UTH_D = 0x7fff, .ISO_TH_D[0].bit.ISO_LTH_D = 0x7fff, .ISO_TH_D[1].bit.ISO_UTH_D = 0x7fff, .ISO_TH_D[1].bit.ISO_LTH_D = 0x7fff, .ISO_TH_D[2].bit.ISO_UTH_D = 0x7fff, .ISO_TH_D[2].bit.ISO_LTH_D = 0x7fff, .ISO_TH_D[3].bit.ISO_UTH_D = 0x7fff, .ISO_TH_D[3].bit.ISO_LTH_D = 0x7fff, .ISO_GAIN_D[0].bit.ISO_GA_D = 0x100, .ISO_GAIN_D[0].bit.ISO_GB_D = 0x100, .ISO_GAIN_D[1].bit.ISO_GA_D = 0x100, .ISO_GAIN_D[1].bit.ISO_GB_D = 0x100, .ISO_GAIN_D[2].bit.ISO_GA_D = 0x100, .ISO_GAIN_D[2].bit.ISO_GB_D = 0x100, .ISO_GAIN_D[3].bit.ISO_GA_D = 0x100, .ISO_GAIN_D[3].bit.ISO_GB_D = 0x100, .SPF_MD.bit.SPF_MD = E_IM_IIP_PARAM_SPF_MD_SPF, .SPF_FLTW_D0.bit = {
// 3x3
0x020, 0x020, 0x020,	// 0.1250 0.1250 0.1250
0x020, 0x000, 0x020,	// 0.1250 0.0000 0.1250
0x020, 0x020, 0x020,	// 0.1250 0.1250 0.1250
// dummy(9~16)
0, 0, 0, 0, 0, 0, 0, 0, }, .SPF_FLTW_D1.bit = {
// 3x3
0x020, 0x020, 0x020,	// 0.1250 0.1250 0.1250
0x020, 0x000, 0x020,	// 0.1250 0.0000 0.1250
0x020, 0x020, 0x020,	// 0.1250 0.1250 0.1250
// dummy(9~16)
0, 0, 0, 0, 0, 0, 0, 0, }, .SPF_FLTW_D2.bit = {
// 3x3
0x020, 0x020, 0x020,	// 0.1250 0.1250 0.1250
0x020, 0x000, 0x020,	// 0.1250 0.0000 0.1250
0x020, 0x020, 0x020,	// 0.1250 0.1250 0.1250
// dummy(9~16)
0, 0, 0, 0, 0, 0, 0, 0, }, .SPF_FLTW_D3.bit = {
// 3x3
0x020, 0x020, 0x020,	// 0.1250 0.1250 0.1250
0x020, 0x000, 0x020,	// 0.1250 0.0000 0.1250
0x020, 0x020, 0x020,	// 0.1250 0.1250 0.1250
// dummy(9~16)
0, 0, 0, 0, 0, 0, 0, 0, }, .SPF_VTH_D0.bit.SPF_UTH_D0 = 0x7fff, .SPF_VTH_D0.bit.SPF_LTH_D0 = 0, .SPF_VTH_D1.bit.SPF_UTH_D1 = 0x1ff, .SPF_VTH_D1.bit.SPF_LTH_D1 = 0, .SPF_VTH_D2.bit.SPF_UTH_D2 = 0x1ff, .SPF_VTH_D2.bit.SPF_LTH_D2 = 0, .SPF_CORE_D0.bit.SPF_CTHP_D0 = 0, .SPF_CORE_D0.bit.SPF_CTHM_D0 = 0, .SPF_CORE_D1.bit.SPF_CTHP_D1 = 0, .SPF_CORE_D1.bit.SPF_CTHM_D1 = 0, .SPF_CORE_D2.bit.SPF_CTHP_D2 = 0, .SPF_CORE_D2.bit.SPF_CTHM_D2 = 0, .SPF_CLP_D0.bit.SPF_CLVLP_D0 = 0x3fff, .SPF_CLP_D0.bit.SPF_CLVLM_D0 = 0x4000, .SPF_CLP_D1.bit.SPF_CLVLP_D1 = 0xff, .SPF_CLP_D1.bit.SPF_CLVLM_D1 = 0x100, .SPF_CLP_D2.bit.SPF_CLVLP_D2 = 0xff, .SPF_CLP_D2.bit.SPF_CLVLM_D2 = 0x100, .SPF_EOADD_D0.bit.SPF_EOADD_D0 = 0, .SPF_EOADD_D1.bit.SPF_EOADD_D1 = 0, .SPF_EOADD_D2.bit.SPF_EOADD_D2 = 0, .EP_MD.bit.EP_MD = E_IM_IIP_PARAM_EP_MD_NR_LOW, .EP_GA_D[0].bit.EP_GA_0 = 0x200, .EP_GA_D[0].bit.EP_GA_1 = 0x100, .EP_GA_D[0].bit.EP_GA_2 = 0x080, .EP_GA_D[1].bit.EP_GA_0 = 0x200, .EP_GA_D[1].bit.EP_GA_1 = 0x100, .EP_GA_D[1].bit.EP_GA_2 = 0x080, .EP_GA_D[2].bit.EP_GA_0 = 0x200, .EP_GA_D[2].bit.EP_GA_1 = 0x100, .EP_GA_D[2].bit.EP_GA_2 = 0x080, .EP_GA_D[3].bit.EP_GA_0 = 0x200, .EP_GA_D[3].bit.EP_GA_1 = 0x100, .EP_GA_D[3].bit.EP_GA_2 = 0x080, .EP_OFS_D[0].bit.EP_OFS_0 = 0x000, .EP_OFS_D[0].bit.EP_OFS_1 = 0x020, .EP_OFS_D[0].bit.EP_OFS_2 = 0x040, .EP_OFS_D[1].bit.EP_OFS_0 = 0x000, .EP_OFS_D[1].bit.EP_OFS_1 = 0x020, .EP_OFS_D[1].bit.EP_OFS_2 = 0x040, .EP_OFS_D[2].bit.EP_OFS_0 = 0x000, .EP_OFS_D[2].bit.EP_OFS_1 = 0x020, .EP_OFS_D[2].bit.EP_OFS_2 = 0x040, .EP_OFS_D[3].bit.EP_OFS_0 = 0x000, .EP_OFS_D[3].bit.EP_OFS_1 = 0x020, .EP_OFS_D[3].bit.EP_OFS_2 = 0x040, .EP_BD_D[0].bit.EP_BD_0 = 0x000, .EP_BD_D[0].bit.EP_BD_1 = 0x040, .EP_BD_D[0].bit.EP_BD_2 = 0x080, .EP_BD_D[1].bit.EP_BD_0 = 0x000, .EP_BD_D[1].bit.EP_BD_1 = 0x040, .EP_BD_D[1].bit.EP_BD_2 = 0x080, .EP_BD_D[2].bit.EP_BD_0 = 0x000, .EP_BD_D[2].bit.EP_BD_1 = 0x040, .EP_BD_D[2].bit.EP_BD_2 = 0x080, .EP_BD_D[3].bit.EP_BD_0 = 0x000, .EP_BD_D[3].bit.EP_BD_1 = 0x040, .EP_BD_D[3].bit.EP_BD_2 = 0x080, .ED_FM.bit.ED_FM_0 = E_IM_IIP_PARAM_ED_FM_NEAR4, .ED_FM.bit.ED_FM_1 = E_IM_IIP_PARAM_ED_FM_NEAR4, .ED_FM.bit.ED_FM_2 = E_IM_IIP_PARAM_ED_FM_NEAR4, .ED_FM.bit.ED_FM_3 = E_IM_IIP_PARAM_ED_FM_NEAR4, .ED_OUT.bit.ED_OUT_0 = E_IM_IIP_PARAM_ED_OUT_DIFF_ABS_MIN, .ED_OUT.bit.ED_OUT_1 = E_IM_IIP_PARAM_ED_OUT_DIFF_ABS_MIN, .ED_OUT.bit.ED_OUT_2 = E_IM_IIP_PARAM_ED_OUT_DIFF_ABS_MIN, .ED_OUT.bit.ED_OUT_3 = E_IM_IIP_PARAM_ED_OUT_DIFF_ABS_MIN, .ADAPT_K.bit.ADAPT_K0 = 0x08, .ADAPT_K.bit.ADAPT_K1 = 0x04, .ADAPT_K.bit.ADAPT_K2 = 0x00, .ADAPT_TH.bit.ADAPT_TH = 0, .ADAPT_DIV.bit.ADAPT_DIV = E_IM_IIP_PARAM_ADAPT_DIV_1_DIVBY_2, .BF_MD.bit.BF_FMT = E_IM_IIP_PARAM_BF_FMT_VALID_D0_D1_D2, .BF_MD.bit.BF_PRT = E_IM_IIP_PARAM_BF_PRT_PORT0, };

const T_IM_IIP_PARAM_MON g_ct_im_iip_param_mon_base = { .header0.bit.BeginningAddress = 0x0000, .header0.bit.WordLength = 25, .header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET, .MONCTL.bit.HISTAE = 1, .MONCTL.bit.HISTBE = 1, .MONCTL.bit.HISTCE = 1, .MONCTL.bit.HISTDE = 1, .MONCTL.bit.MAXE = 1, .MONCTL.bit.MINE = 1, .MONCTL.bit.ADDE = 1, .MONDSEL.bit.DSEL = E_IM_IIP_PARAM_DSEL_SL0, .MONDSEL.bit.SGNEN0 = E_IM_IIP_PARAM_SGNEN_UNSIGN, .MONDSEL.bit.SGNEN1 = E_IM_IIP_PARAM_SGNEN_UNSIGN, .MONDSEL.bit.SGNEN2 = E_IM_IIP_PARAM_SGNEN_UNSIGN, .MONDSEL.bit.SGNEN3 = E_IM_IIP_PARAM_SGNEN_UNSIGN, .HISTCTL[0].bit.HISTSEL = 0,// D0
.HISTCTL[0].bit.BITSEL = E_IM_IIP_PARAM_BITSEL_7_0, .HISTCTL[0].bit.HISTSKIP_H = 2, .HISTCTL[0].bit.HISTSKIP_V = 2, .HISTCTL[1].bit.HISTSEL = 1,// D1
.HISTCTL[1].bit.BITSEL = E_IM_IIP_PARAM_BITSEL_7_0, .HISTCTL[1].bit.HISTSKIP_H = 2, .HISTCTL[1].bit.HISTSKIP_V = 2, .HISTCTL[2].bit.HISTSEL = 2,// D2
.HISTCTL[2].bit.BITSEL = E_IM_IIP_PARAM_BITSEL_7_0, .HISTCTL[2].bit.HISTSKIP_H = 2, .HISTCTL[2].bit.HISTSKIP_V = 2, .HISTCTL[3].bit.HISTSEL = 3,// D3
.HISTCTL[3].bit.BITSEL = E_IM_IIP_PARAM_BITSEL_7_0, .HISTCTL[3].bit.HISTSKIP_H = 2, .HISTCTL[3].bit.HISTSKIP_V = 2, .ABSMAX.bit.ABSMAX = 0, .ABSMIN.bit.ABSMIN = 0, .ABSADD.bit.ABSADD = 0, .OVERVALUE[0].bit.OVERVALUE = 0x7FFFFFFF, .OVERVALUE[1].bit.OVERVALUE = 0x7FFFFFFF, .OVERVALUE[2].bit.OVERVALUE = 0x7FFFFFFF, .OVERVALUE[3].bit.OVERVALUE = 0x7FFFFFFF, };

#ifdef __GNUC__
T_IM_IIP_PARAM_AFN g_ct_im_iip_unit_param_afn __attribute__((aligned(8)));			// Needs 8bytes align
T_IM_IIP_PARAM_STS g_ct_im_iip_unit_param_sl0 __attribute__((aligned(8)));// Needs 8bytes align
T_IM_IIP_PARAM_STS g_ct_im_iip_unit_param_sl1 __attribute__((aligned(8)));// Needs 8bytes align
T_IM_IIP_PARAM_STS g_ct_im_iip_unit_param_sl2 __attribute__((aligned(8)));// Needs 8bytes align
T_IM_IIP_PARAM_AFN_OPCOL_0 g_ct_im_iip_afntbl __attribute__((aligned(8)));// Needs 8bytes align
T_IM_IIP_PARAM_FRECT g_ct_im_iip_unit_param_frect0 __attribute__((aligned(8)));// Needs 8bytes align
T_IM_IIP_PARAM_FRECT g_ct_im_iip_unit_param_frect1 __attribute__((aligned(8)));// Needs 8bytes align
T_IM_IIP_PARAM_1DL g_ct_im_iip_unit_param_1dl0 __attribute__((aligned(8)));// Needs 8bytes align
T_IM_IIP_PARAM_1DL g_ct_im_iip_unit_param_1dl1 __attribute__((aligned(8)));// Needs 8bytes align
T_IM_IIP_PARAM_1DL g_ct_im_iip_unit_param_1dl2 __attribute__((aligned(8)));// Needs 8bytes align
T_IM_IIP_PARAM_BLEND g_ct_im_iip_unit_param_blend __attribute__((aligned(8)));// Needs 8bytes align
T_IM_IIP_PARAM_CSC g_ct_im_iip_unit_param_csc __attribute__((aligned(8)));// Needs 8bytes align
T_IM_IIP_PARAM_FLT g_ct_im_iip_unit_param_flt __attribute__((aligned(8)));// Needs 8bytes align
T_IM_IIP_PARAM_MON g_ct_im_iip_unit_param_mon __attribute__((aligned(8)));// Needs 8bytes align
#else
__align(8) T_IM_IIP_PARAM_AFN g_ct_im_iip_unit_param_afn;								// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_STS g_ct_im_iip_unit_param_sl0;// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_STS g_ct_im_iip_unit_param_sl1;// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_STS g_ct_im_iip_unit_param_sl2;// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_AFN_OPCOL_0 g_ct_im_iip_afntbl;// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_FRECT g_ct_im_iip_unit_param_frect0;// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_FRECT g_ct_im_iip_unit_param_frect1;// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_1DL g_ct_im_iip_unit_param_1dl0;// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_1DL g_ct_im_iip_unit_param_1dl1;// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_1DL g_ct_im_iip_unit_param_1dl2;// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_BLEND g_ct_im_iip_unit_param_blend;// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_CSC g_ct_im_iip_unit_param_csc;// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_FLT g_ct_im_iip_unit_param_flt;// Needs 8bytes align
__align(8) T_IM_IIP_PARAM_MON g_ct_im_iip_unit_param_mon;// Needs 8bytes align
#endif

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
ULONG gCtImIIP_Get_Unit_Param[0x3A0 / sizeof(ULONG)];
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

extern VOID Im_IIP_Print_DebugStatus( VOID);
#ifdef CO_IIP_DEBUG
extern VOID Im_IIP_Print_ClockStatus( VOID );
#endif

#ifdef CO_DEBUG_ON_PC
static VOID ct_im_iip_print_hwen_all( VOID )
{
	Im_IIP_On_Pclk();

	ct_im_iip_print_hwen( "LD0", IO_IIP.UNITINFTBL_LD0 );
	ct_im_iip_print_hwen( "LD1", IO_IIP.UNITINFTBL_LD1 );
	ct_im_iip_print_hwen( "LD2", IO_IIP.UNITINFTBL_LD2 );
	ct_im_iip_print_hwen( "LD3", IO_IIP.UNITINFTBL_LD3 );
	ct_im_iip_print_hwen( "LD4", IO_IIP.UNITINFTBL_LD4 );
	ct_im_iip_print_hwen( "LD5", IO_IIP.UNITINFTBL_LD5 );
	ct_im_iip_print_hwen( "LD6", IO_IIP.UNITINFTBL_LD6 );
	ct_im_iip_print_hwen( "LD7", IO_IIP.UNITINFTBL_LD7 );
	ct_im_iip_print_hwen( "SPF", IO_IIP.UNITINFTBL_FLT );
	ct_im_iip_print_hwen( "AFN0", IO_IIP.UNITINFTBL_AFN0 );
	ct_im_iip_print_hwen( "AFN1", IO_IIP.UNITINFTBL_AFN1 );
	ct_im_iip_print_hwen( "AFN2", IO_IIP.UNITINFTBL_AFN2 );
	ct_im_iip_print_hwen( "AFN3", IO_IIP.UNITINFTBL_AFN3 );
	ct_im_iip_print_hwen( "FRCT0", IO_IIP.UNITINFTBL_FRC0 );
	ct_im_iip_print_hwen( "FRCT1", IO_IIP.UNITINFTBL_FRC1 );
	ct_im_iip_print_hwen( "MON", IO_IIP.UNITINFTBL_MON );
	ct_im_iip_print_hwen( "SL0", IO_IIP.UNITINFTBL_SL0 );
	ct_im_iip_print_hwen( "SL1", IO_IIP.UNITINFTBL_SL1 );
	ct_im_iip_print_hwen( "SL2", IO_IIP.UNITINFTBL_SL2 );
	ct_im_iip_print_hwen( "SL3", IO_IIP.UNITINFTBL_SL3 );
	ct_im_iip_print_hwen( "SL4", IO_IIP.UNITINFTBL_SL4 );
	ct_im_iip_print_hwen( "SL5", IO_IIP.UNITINFTBL_SL5 );
	ct_im_iip_print_hwen( "SL6", IO_IIP.UNITINFTBL_SL6 );
	ct_im_iip_print_hwen( "SL7", IO_IIP.UNITINFTBL_SL7 );
	ct_im_iip_print_hwen( "SL8", IO_IIP.UNITINFTBL_SL8 );
	ct_im_iip_print_hwen( "CSC0", IO_IIP.UNITINFTBL_CSC0 );
	ct_im_iip_print_hwen( "CSC1", IO_IIP.UNITINFTBL_CSC1 );
	ct_im_iip_print_hwen( "CSC2", IO_IIP.UNITINFTBL_CSC2 );
	ct_im_iip_print_hwen( "CSC3", IO_IIP.UNITINFTBL_CSC3 );
	ct_im_iip_print_hwen( "LUT", IO_IIP.UNITINFTBL_LUT );
	ct_im_iip_print_hwen( "GPC", IO_IIP.UNITINFTBL_GPC );
	ct_im_iip_print_hwen( "BLD0", IO_IIP.UNITINFTBL_BLD0 );
	ct_im_iip_print_hwen( "BLD1", IO_IIP.UNITINFTBL_BLD1 );
	ct_im_iip_print_hwen( "CFL0", IO_IIP.UNITINFTBL_CFL0 );
	ct_im_iip_print_hwen( "MFT", IO_IIP.UNITINFTBL_MFT );
	Im_IIP_Off_Pclk();
}

static VOID ct_im_iip_set_hwen_auto_all( VOID )
{
	struct io_iip_uinftbl uinftbl;

	memset( &uinftbl, '\0', sizeof(uinftbl) );
	uinftbl.UNITINFTBL0.bit.HWEN = D_IM_IIP_HW_CTRL_AUTO;

	IO_IIP.UNITINFTBL_LD0 = uinftbl;
	IO_IIP.UNITINFTBL_LD1 = uinftbl;
	IO_IIP.UNITINFTBL_LD2 = uinftbl;
	IO_IIP.UNITINFTBL_LD3 = uinftbl;
	IO_IIP.UNITINFTBL_LD4 = uinftbl;
	IO_IIP.UNITINFTBL_LD5 = uinftbl;
	IO_IIP.UNITINFTBL_LD6 = uinftbl;
	IO_IIP.UNITINFTBL_LD7 = uinftbl;
	IO_IIP.UNITINFTBL_FLT = uinftbl;
	IO_IIP.UNITINFTBL_AFN0 = uinftbl;
	IO_IIP.UNITINFTBL_AFN1 = uinftbl;
	IO_IIP.UNITINFTBL_AFN2 = uinftbl;
	IO_IIP.UNITINFTBL_AFN3 = uinftbl;
	IO_IIP.UNITINFTBL_FRC0 = uinftbl;
	IO_IIP.UNITINFTBL_FRC1 = uinftbl;
	IO_IIP.UNITINFTBL_MON = uinftbl;
	IO_IIP.UNITINFTBL_SL0 = uinftbl;
	IO_IIP.UNITINFTBL_SL1 = uinftbl;
	IO_IIP.UNITINFTBL_SL2 = uinftbl;
	IO_IIP.UNITINFTBL_SL3 = uinftbl;
	IO_IIP.UNITINFTBL_SL4 = uinftbl;
	IO_IIP.UNITINFTBL_SL5 = uinftbl;
	IO_IIP.UNITINFTBL_SL6 = uinftbl;
	IO_IIP.UNITINFTBL_SL7 = uinftbl;
	IO_IIP.UNITINFTBL_SL8 = uinftbl;
	IO_IIP.UNITINFTBL_CSC0 = uinftbl;
	IO_IIP.UNITINFTBL_CSC1 = uinftbl;
	IO_IIP.UNITINFTBL_CSC2 = uinftbl;
	IO_IIP.UNITINFTBL_CSC3 = uinftbl;
	IO_IIP.UNITINFTBL_LUT = uinftbl;
	IO_IIP.UNITINFTBL_GPC = uinftbl;
	IO_IIP.UNITINFTBL_BLD0 = uinftbl;
	IO_IIP.UNITINFTBL_BLD1 = uinftbl;
	IO_IIP.UNITINFTBL_CFL0 = uinftbl;
	IO_IIP.UNITINFTBL_MFT = uinftbl;
}
#endif // CO_DEBUG_ON_PC

#endif //CO_CT_IM_IIP_DISABLE

VOID CT_Im_IIP_Print_Pixfmttbl_Detail(const UINT32 pixid)
{
	volatile struct io_iip_pixfmttbl* pPIXFMTTBL;
	static const CHAR* const ftype_name_tbl[8] = { "E_IM_IIP_FTYPE_Y_PACKED_CBCR", "E_IM_IIP_FTYPE_CHUNKY", "E_IM_IIP_FTYPE_PLANE", };
	static const CHAR* const pfmt_name_tbl[16] = { "E_IM_IIP_PFMT_YCC422", "E_IM_IIP_PFMT_YCC444", "E_IM_IIP_PFMT_YCC420", "E_IM_IIP_PFMT_BAYER", "E_IM_IIP_PFMT_CBCR", "E_IM_IIP_PFMT_VIDEO", "E_IM_IIP_PFMT_PLANE", "E_IM_IIP_PFMT_RGB565", "E_IM_IIP_PFMT_RGBA5551", "E_IM_IIP_PFMT_RGBA4444", };
	static const CHAR* const pdepth_name_tbl[8] = { "D_IM_IIP_PDEPTH_8BITS", "D_IM_IIP_PDEPTH_12BITS", "D_IM_IIP_PDEPTH_16BITS", };
	static const CHAR* const adepth_name_tbl[8] = { "E_IM_IIP_ADEPTH_8BITS", "(null)", "(null)", "E_IM_IIP_ADEPTH_4BITS", };
	static const CHAR* const sgX_name_tbl[2] = { "D_IM_IIP_UNSIGNED_DATA", "D_IM_IIP_SIGNED_DATA", };
	static const CHAR* const asubspl_name_tbl[4] = { "D_IM_IIP_ALPHA_NO_SUBSAMP", "D_IM_IIP_ALPHA_H_SUBSAMP", "D_IM_IIP_ALPHA_HV_SUBSAMP", };
	static const CHAR* const oarbhv_name_tbl[2] = { "D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE", "D_IM_IIP_OUTSIDE_IMG_EDGE", };
	static const CHAR* const chkyordr_name_tbl[4] = { "D_IM_IIP_CHUNKY_COLOR_Y0_G", "D_IM_IIP_CHUNKY_COLOR_CB_B", "D_IM_IIP_CHUNKY_COLOR_CR_R", "D_IM_IIP_CHUNKY_COLOR_Y1_A", };

	pPIXFMTTBL = &IO_IIP.PIXFMTTBL[pixid];

	Im_IIP_On_Pclk();

	DDIM_User_Printf("[%u] PIXFMTTBL.FTYPE = %s\n", pixid, ftype_name_tbl[pPIXFMTTBL->PIXFMTTBL_0.bit.FTYPE]);
	DDIM_User_Printf("[%u] PIXFMTTBL.PFMT = %s\n", pixid, pfmt_name_tbl[pPIXFMTTBL->PIXFMTTBL_0.bit.PFMT]);
	DDIM_User_Printf("[%u] PIXFMTTBL.ALPHA = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_0.bit.ALPHA);
	DDIM_User_Printf("[%u] PIXFMTTBL.PDEPTH = %s\n", pixid, pdepth_name_tbl[pPIXFMTTBL->PIXFMTTBL_0.bit.PDEPTH]);
	DDIM_User_Printf("[%u] PIXFMTTBL.ADEPTH = %s\n", pixid, adepth_name_tbl[pPIXFMTTBL->PIXFMTTBL_0.bit.ADEPTH]);
	DDIM_User_Printf("[%u] PIXFMTTBL.CHKYORDR D0=%s D1=%s D2=%s D3=%s\n", pixid, chkyordr_name_tbl[(pPIXFMTTBL->PIXFMTTBL_0.bit.CHKYORDR & 0x03)], chkyordr_name_tbl[(pPIXFMTTBL->PIXFMTTBL_0.bit.CHKYORDR & 0x0c) >> 2], chkyordr_name_tbl[(pPIXFMTTBL->PIXFMTTBL_0.bit.CHKYORDR & 0x30) >> 4], chkyordr_name_tbl[(pPIXFMTTBL->PIXFMTTBL_0.bit.CHKYORDR & 0xc0) >> 6]);
	DDIM_User_Printf("[%u] PIXFMTTBL.SGYG = %s\n", pixid, sgX_name_tbl[pPIXFMTTBL->PIXFMTTBL_1.bit.SGYG]);
	DDIM_User_Printf("[%u] PIXFMTTBL.SGB = %s\n", pixid, sgX_name_tbl[pPIXFMTTBL->PIXFMTTBL_1.bit.SGB]);
	DDIM_User_Printf("[%u] PIXFMTTBL.SGR = %s\n", pixid, sgX_name_tbl[pPIXFMTTBL->PIXFMTTBL_1.bit.SGR]);
	DDIM_User_Printf("[%u] PIXFMTTBL.SGA = %s\n", pixid, sgX_name_tbl[pPIXFMTTBL->PIXFMTTBL_1.bit.SGA]);
	DDIM_User_Printf("[%u] PIXFMTTBL.ASUBSPL = %s\n", pixid, asubspl_name_tbl[pPIXFMTTBL->PIXFMTTBL_1.bit.ASUBSPL]);
	DDIM_User_Printf("[%u] PIXFMTTBL.MTIFYG = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFYG);
	DDIM_User_Printf("[%u] PIXFMTTBL.MTIFB = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFB);
	DDIM_User_Printf("[%u] PIXFMTTBL.MTIFR = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFR);
	DDIM_User_Printf("[%u] PIXFMTTBL.MTIFA = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFA);
	DDIM_User_Printf("[%u] PIXFMTTBL.OARBHV = %s\n", pixid, oarbhv_name_tbl[pPIXFMTTBL->PIXFMTTBL_1.bit.OARBHV]);
	DDIM_User_Printf("[%u] PIXFMTTBL.OARVALYG = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_2.bit.OARVALYG);
	DDIM_User_Printf("[%u] PIXFMTTBL.OARVALB = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_2.bit.OARVALB);
	DDIM_User_Printf("[%u] PIXFMTTBL.OARVALR = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_3.bit.OARVALR);
	DDIM_User_Printf("[%u] PIXFMTTBL.OARVALA = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_3.bit.OARVALA);
	DDIM_User_Printf("[%u] PIXFMTTBL.GHSZYG = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_4.bit.GHSZYG);
	DDIM_User_Printf("[%u] PIXFMTTBL.GHSZB = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_5.bit.GHSZB);
	DDIM_User_Printf("[%u] PIXFMTTBL.GHSZR = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_6.bit.GHSZR);
	DDIM_User_Printf("[%u] PIXFMTTBL.GHSZA = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_7.bit.GHSZA);
	DDIM_User_Printf("[%u] PIXFMTTBL.PICHSZ = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_8.bit.PICHSZ);
	DDIM_User_Printf("[%u] PIXFMTTBL.PICVSZ = %u\n", pixid, pPIXFMTTBL->PIXFMTTBL_8.bit.PICVSZ);
	DDIM_User_Printf("[%u] PIXFMTTBL.ADRSYG = 0x%lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_9.bit.ADRSYG);
	DDIM_User_Printf("[%u] PIXFMTTBL.ADRSB = 0x%lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_10.bit.ADRSB);
	DDIM_User_Printf("[%u] PIXFMTTBL.ADRSR = 0x%lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_11.bit.ADRSR);
	DDIM_User_Printf("[%u] PIXFMTTBL.ADRSA = 0x%lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_12.bit.ADRSA);

	Im_IIP_Off_Pclk();
}

#ifndef CO_CT_IM_IIP_DISABLE

VOID CT_Im_IIP_Print_Pixfmttbl_Byid(const E_IM_IIP_PIXID pixid)
{
	UINT32 loopcnt;

	for (loopcnt = 0; loopcnt < D_IM_IIP_PIXID_MAXNUM; loopcnt++)
	{
		if (pixid == (1 << loopcnt))
		{
//			ct_im_iip_print_pixfmttbl( loopcnt );
			CT_Im_IIP_Print_Pixfmttbl_Detail(loopcnt);
			return;
		}
	}

	DDIM_User_Printf("Unknown PIXID = 0x%x\n", pixid);
}

static VOID ct_im_iip_print_unitcfg(const CHAR* const unit_name, volatile struct io_iip_uinftbl* const pUNITINFTBL, const UCHAR is_sl)
{
	Im_IIP_On_Pclk();

	Ddim_Print(( "%s UNITINFTBL0 = 0x%08lx\n", unit_name, pUNITINFTBL->UNITINFTBL0.word ));
	if (is_sl != 0)
	{
		Ddim_Print(( "%s UNITINFTBL1 = 0x%08lx%08lx\n", unit_name, pUNITINFTBL->UNITINFTBL1.word[0], pUNITINFTBL->UNITINFTBL1.word[1] ));
	}
	Ddim_Print(( "%s UNITINFTBL2 = 0x%08lx\n", unit_name, pUNITINFTBL->UNITINFTBL2.word ));
	Ddim_Print(( "%s UNITSR      = 0x%08lx\n", unit_name, pUNITINFTBL->UNITSR.word ));

	Im_IIP_Off_Pclk();
}

static VOID ct_im_iip_print_unitcfg_detail(const CHAR* const unit_name, volatile struct io_iip_uinftbl* const pUNITINFTBL)
{
	UINT32 loopcnt;
	T_CT_IM_IIP_UNITID_TBL unitid_tbl;

	Im_IIP_On_Pclk();

	if (pUNITINFTBL->UNITINFTBL1.word != 0)
	{
		Ddim_Print(( "%s UNITINFTBL1.PLDUNIT =", unit_name ));
		for (loopcnt = 0; loopcnt < D_CT_IM_IIP_UNIT_ARRAY_MAX; loopcnt++)
		{
			unitid_tbl = g_ct_im_iip_unitid_array[loopcnt];

			if ((unitid_tbl.pldunit & Im_IIP_Get_Reg_PLDUNIT64(pUNITINFTBL->UNITINFTBL1)) != 0)
			{
				Ddim_Print(( " %s", unitid_tbl.unitname ));
			}
		}
		Ddim_Print(( "\n" ));
	}

	Im_IIP_Off_Pclk();
}

VOID ct_im_iip_print_unitcfg_all( VOID)
{
	UINT32 loopcnt;
	T_CT_IM_IIP_UNITID_TBL unitid;

	for (loopcnt = 0; loopcnt < D_CT_IM_IIP_UNIT_ARRAY_MAX; loopcnt++)
	{
		unitid = g_ct_im_iip_unitid_array[loopcnt];

		ct_im_iip_print_unitcfg(unitid.unitname, unitid.pUNITINFTBL, unitid.is_sl);
	}
}

VOID CT_Im_IIP_Print_Unitcfg_Byid(const E_IM_IIP_UNIT_ID unitid)
{
	UINT32 loopcnt;
	T_CT_IM_IIP_UNITID_TBL unitid_tbl;

	for (loopcnt = 0; loopcnt < D_CT_IM_IIP_UNIT_ARRAY_MAX; loopcnt++)
	{
		unitid_tbl = g_ct_im_iip_unitid_array[loopcnt];

		if (unitid_tbl.unitid == unitid)
		{
			ct_im_iip_print_unitcfg(unitid_tbl.unitname, unitid_tbl.pUNITINFTBL, unitid_tbl.is_sl);
			ct_im_iip_print_unitcfg_detail(unitid_tbl.unitname, unitid_tbl.pUNITINFTBL);
			if (unitid_tbl.unit_param_dump)
			{
				unitid_tbl.unit_param_dump(unitid_tbl.pUNITINFTBL, unitid_tbl.unitid);
			}
			break;
		}
	}
}


#if !defined(CO_CT_IM_IIP_2_7_1_DISABLE_HIST) && !defined(CO_CT_IM_IIP_11_1_2_DISABLE_HIST)
VOID CT_Im_IIP_Plot_Hist(const ULONG* buffer_histgram, const UINT32 count, const UCHAR histmax)
{
	CHAR bar_graph_str[112 + 1];
	ULONG loopcnt;
	ULONG loopcnt2;

	for (loopcnt = 0; loopcnt < count; loopcnt++)
	{
		if (buffer_histgram[histmax] != 0)
		{
			for (loopcnt2 = 0; loopcnt2 < (112 * buffer_histgram[loopcnt] / buffer_histgram[histmax]); loopcnt2++)
			{
				bar_graph_str[loopcnt2] = '*';
			}
		}
		else
		{
			loopcnt2 = 0;
		}
		bar_graph_str[loopcnt2] = '\0';
		Ddim_Print(( "[%4lu] 0x%-6lx %s\n", loopcnt, buffer_histgram[loopcnt], bar_graph_str ));
		if ((loopcnt % 10) == 0)
		{
			DDIM_User_Dly_Tsk(100);		// Wait for UART output.
		}
	}
}
#endif



/************/
/* API test */
/************/

INT32 CT_Im_IIP_1_1_11( VOID)
{
	T_IM_IIP_UNIT_CFG unitcfg;
	T_CT_IM_IIP_UNITID_TBL unitid;
	UINT32 loopcnt;
	INT32 ercd;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	memset(&unitcfg, '\0', sizeof(unitcfg));

	for (loopcnt = 0; loopcnt < D_CT_IM_IIP_UNIT_ARRAY_MAX; loopcnt++)
	{
		unitid = g_ct_im_iip_unitid_array[loopcnt];

		Ddim_Print(( "** UNIT: %s\n", unitid.unitname ));
		ercd = Im_IIP_Open_SWTRG(unitid.pldunit, 0, 0, 1000);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		// check result=0x0C000001
		ercd = Im_IIP_Ctrl_SWTRG_Unit(unitid.unitid, NULL);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		// check register max value
		unitcfg.unit_ctrl = 1;
		unitcfg.chain_enable = 1;
		unitcfg.unit_param_addr = 0xFFFFFFFFul;
		unitcfg.load_unit_param_flag = 0xFFFFFFFFFFFFFFFFull;
		ercd = Im_IIP_Ctrl_SWTRG_Unit(unitid.unitid, &unitcfg);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_unitcfg(unitid.unitname, unitid.pUNITINFTBL, unitid.is_sl);

		// check register min value
		unitcfg.unit_ctrl = 0;
		unitcfg.chain_enable = 0;
		unitcfg.unit_param_addr = 0;
		unitcfg.load_unit_param_flag = 0;
		ercd = Im_IIP_Ctrl_SWTRG_Unit(unitid.unitid, &unitcfg);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_unitcfg(unitid.unitname, unitid.pUNITINFTBL, unitid.is_sl);

		ercd = Im_IIP_Close_SWTRG(unitid.pldunit, 0, 0);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	}

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_18( VOID)
{
	INT32 ercd;
	UINT32 loopcnt;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
	T_CT_IM_IIP_UNITID_TBL unitid;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG(unit_bitmask, 0, 0, 1000);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	for (loopcnt = 0; loopcnt < D_CT_IM_IIP_UNIT_ARRAY_MAX; loopcnt++)
	{
		unitid = g_ct_im_iip_unitid_array[loopcnt];

		Ddim_Print(( "** UNIT: %s\n", unitid.unitname ));

		// check register max value
		ercd = Im_IIP_Update_PADRS(unitid.unitid, 0xFFFFFFFF);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_unitcfg(unitid.unitname, unitid.pUNITINFTBL, unitid.is_sl);

		// check register min value
		ercd = Im_IIP_Update_PADRS(unitid.unitid, 0);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_unitcfg(unitid.unitname, unitid.pUNITINFTBL, unitid.is_sl);
	}

	ercd = Im_IIP_Close_SWTRG(unit_bitmask, 0, 0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}


#ifdef CO_CT_IM_IIP_ENABLE_1_1_34
#ifdef CO_DEBUG_ON_PC
INT32 CT_Im_IIP_1_1_34( VOID )
{
	INT32 ercd;
	volatile ULONG* p_iip_debug;
	UINT32 out_bytes;
	UINT32 loopcnt;
	UINT32 loopcnt2;
	T_CT_IM_IIP_UNITID_TBL unitid;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
	static volatile ULONG g_ct_im_iip_get_unitparam_buf[sizeof(IO_IIP.UNITDEBUG) /4];

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	p_iip_debug = IO_IIP.UNITDEBUG;

	for( loopcnt = 0; loopcnt < (65536 / sizeof(ULONG)); loopcnt++ )
	{
		p_iip_debug[loopcnt] = ((65536 / sizeof(ULONG)) -1 - loopcnt)
		| ((65536 / sizeof(ULONG)) -1 - loopcnt) * 0x10000;
	}

	for( loopcnt = 0; loopcnt < D_CT_IM_IIP_UNIT_ARRAY_MAX; loopcnt++ )
	{
		unitid = g_ct_im_iip_unitid_array[loopcnt];

		Ddim_Print(( "** UNIT: %s\n", unitid.unitname ));

		memset( (VOID*)g_ct_im_iip_get_unitparam_buf, '\0', sizeof(g_ct_im_iip_get_unitparam_buf) );
		ercd = Im_IIP_Get_UNIT_PARAM( unitid.unitid, (ULONG*)g_ct_im_iip_get_unitparam_buf, &out_bytes );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x bytes=%u(0x%x)\n", ercd, out_bytes, out_bytes ));

		for( loopcnt2 = 0; loopcnt2 < (out_bytes / sizeof(ULONG) +1); loopcnt2++ )
		{
			Ddim_Print(( "0x%08lx ", g_ct_im_iip_get_unitparam_buf[loopcnt2] ));
			if( (loopcnt2 % 16) == 15 )
			{
				Ddim_Print(( "\n" ));
			}
		}

		Ddim_Print(( "\n" ));
	}

	// check result = 0x0C000001
	ercd = Im_IIP_Get_UNIT_PARAM( E_IM_IIP_UNIT_ID_LD0, NULL, &out_bytes );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	// check result = 0x0C000001
	ercd = Im_IIP_Get_UNIT_PARAM( E_IM_IIP_UNIT_ID_LD0, (ULONG*)g_ct_im_iip_get_unitparam_buf, NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_DEBUG_ON_PC
#endif // CO_CT_IM_IIP_ENABLE_1_1_34

INT32 CT_Im_IIP_1_1_39( VOID)
{
	INT32 ercd;
	UINT32 loopcnt;
	T_CT_IM_IIP_UNITID_TBL unitid;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	for (loopcnt = 0; loopcnt < D_CT_IM_IIP_UNIT_ARRAY_MAX; loopcnt++)
	{
		unitid = g_ct_im_iip_unitid_array[loopcnt];

		Ddim_Print(( "** UNIT: %s\n", unitid.unitname ));

#ifdef CO_DEBUG_ON_PC
		IO_IIP.IZACTL2.bit.ABORT = 3;
#endif //CO_DEBUG_ON_PC
		ercd = Im_IIP_Start_DumpUnitReg(unitid.unitid);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		Ddim_Print(( "ABORT=%u SELRDREG_UNIT=%u DBEN=%u\n", IO_IIP.IZACTL2.bit.ABORT, IO_IIP.IZACTL1.bit.SELRDREG_UNIT, IO_IIP.IZACTL1.bit.DBEN ));
	}

	ercd = Im_IIP_Stop_DumpUnitReg();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

#endif //CO_CT_IM_IIP_DISABLE

CtImIip* ct_im_iip_get(void)
{
	static CtImIip* self = NULL;

	if (!self)
	{
//		self = k_object_new_with_private(CT_TYPE_IM_IIP, sizeof(CtImIipPrivate));
	}

	return self;
}
