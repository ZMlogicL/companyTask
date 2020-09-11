/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIip6
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
#include "ctimiip6.h"


//K_TYPE_DEFINE_WITH_PRIVATE(CtImIip6, ct_im_iip_6)
//#define CT_IM_IIP_6_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIip6Private, CT_TYPE_IM_IIP_6))


struct _CtImIip6Private
{

};


/********
 * IMPL
 */
//static void ct_im_iip_6_constructor(CtImIip6 *self)
//{
//	CtImIip6Private *priv = CT_IM_IIP_6_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_6_destructor(CtImIip6 *self)
//{
//	CtImIip6Private *priv = CT_IM_IIP_6_GET_PRIVATE(self);
//}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_IIP_DISABLE
INT32 CT_Im_IIP_1_1_40( VOID)
{
	INT32 ercd;
	UINT32 loopcnt;
	static CHAR* unit_name[] = { "ld0", "ld1", "ld2", "ld3", "flt", "afn0", "afn1", "afn2", "frect0", "mon", "sl0", "sl1", "sl2", "sl3", "sl4", "sl5", "csc0", "csc1", "lut", "gpc", "blend0", "blend1", "frect1", "cfl0", "csc2", "csc3", "sl6", "sl7", "sl8", "ld4", "ld5", "ld6", "ld7", "afn3", "mft", };

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	for (loopcnt = 0; loopcnt < (sizeof(unit_name) / sizeof(unit_name[0])); loopcnt++)
	{ /* pgr0834 */
		Ddim_Print(( "** UNIT: %s\n", unit_name[loopcnt] ));

#ifdef CO_DEBUG_ON_PC
		IO_IIP.IZACTL2.bit.ABORT = 3;
#endif //CO_DEBUG_ON_PC
		ercd = Im_IIP_Start_DumpUnitReg_ByName(unit_name[loopcnt]);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		Ddim_Print(( "ABORT=%u SELRDREG_UNIT=%u DBEN=%u\n", IO_IIP.IZACTL2.bit.ABORT, IO_IIP.IZACTL1.bit.SELRDREG_UNIT, IO_IIP.IZACTL1.bit.DBEN ));
	}

	ercd = Im_IIP_Stop_DumpUnitReg();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_41( VOID)
{
	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	return CT_Im_IIP_1_1_39();
}

INT32 CT_Im_IIP_1_1_42( VOID)
{
	T_IM_IIP_UTIL_RR iip_util_rr_0 = {
//		.afn_unitid = E_IM_IIP_UNIT_ID_AFN0,	// UNITID of AFN
//		.sl_unitid = D_SAMPLE_SL_UNITID,		// UNITID of SL
//		.src_pixid = E_IM_IIP_PIXID_0,			// Source image PIXID
//		.dst_pixid = E_IM_IIP_PIXID_1,			// Destination image PIXID
	.src = {								// Source image info.
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 1280,							// Width
	.lines = 720,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 1280,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 720,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 1280, .Cb_B = 1280, .Cr_R = 1280, .Alpha = 1280,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x20000000, .Cb_B = 0x21000000, .Cr_R = 0x22000000, .Alpha = 0x20000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, .dst = {								// Destination image info.
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 640,							// Width
	.lines = 360,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 640,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 360,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 640, .Cb_B = 640, .Cr_R = 640, .Alpha = 640,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x23000000, .Cb_B = 0x24000000, .Cr_R = 0x25000000, .Alpha = 0x23000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF1,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF1,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF1,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF1,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, .afn_cache_select = E_IM_IIP_PARAM_CSEL_0,	// AFN cache select.
	.pix_depth = D_IM_IIP_PDEPTH_8BITS,			// PIXFMTTBL.PDEPTH[2:0] <br><br> Depth of pixel.
	.rotation = E_IM_IIP_UTIL_ROTATE_000,		// Angle of rotation
	.resize_mode = E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR,		// Resize mode
	};
	T_IM_IIP_UTIL_RR iip_util_rr_1 = {
//		.afn_unitid = E_IM_IIP_UNIT_ID_AFN0,	// UNITID of AFN
//		.sl_unitid = D_SAMPLE_SL_UNITID,		// UNITID of SL
//		.src_pixid = E_IM_IIP_PIXID_0,			// Source image PIXID
//		.dst_pixid = E_IM_IIP_PIXID_1,			// Destination image PIXID
	.src = {								// Source image info.
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 1440,							// Width
	.lines = 1080,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_PLANE,			// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC420,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 1440,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 1080,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 1440, .Cb_B = 1440 / 2, .Cr_R = 1440 / 2, .Alpha = 1440,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x20000000, .Cb_B = 0x21000000, .Cr_R = 0x22000000, .Alpha = 0x20000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, .dst = {								// Destination image info.
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 960,							// Width
	.lines = 720,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_PLANE,			// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC420,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 960,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 720,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 960, .Cb_B = 960 / 2, .Cr_R = 960 / 2, .Alpha = 960,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x23000000, .Cb_B = 0x24000000, .Cr_R = 0x25000000, .Alpha = 0x23000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF1,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF1,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF1,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF1,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, .afn_cache_select = E_IM_IIP_PARAM_CSEL_0,	// AFN cache select.
	.pix_depth = D_IM_IIP_PDEPTH_8BITS,			// PIXFMTTBL.PDEPTH[2:0] <br><br> Depth of pixel.
	.rotation = E_IM_IIP_UTIL_ROTATE_000,		// Angle of rotation
	.resize_mode = E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR,		// Resize mode
	};
	UCHAR param_master_IF = D_IM_IIP_MASTER_IF0;
	UCHAR param_buffer[D_IM_IIP_UTIL_RR_BUF_BYTES * 2 + 8];
	ULONG param_buffer_addr = (((ULONG) param_buffer) + 7UL) & 0xFFFFFFF8UL;	// Convet 8bytes align
	INT32 wait_time = 100;
	INT32 ercd;
	UINT32 loopcnt;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	for (loopcnt = 0;; loopcnt++)
	{
		switch (loopcnt)
		{
		default:
			return D_DDIM_OK;
		case 0:
			iip_util_rr_0.afn_unitid = E_IM_IIP_UNIT_ID_AFN0;
			iip_util_rr_0.sl_unitid = E_IM_IIP_UNIT_ID_SL2;
			iip_util_rr_0.src_pixid = E_IM_IIP_PIXID_0;
			iip_util_rr_0.dst_pixid = E_IM_IIP_PIXID_1;
			iip_util_rr_0.resize_mode = E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR;
			iip_util_rr_1.afn_unitid = E_IM_IIP_UNIT_ID_AFN1;
			iip_util_rr_1.sl_unitid = E_IM_IIP_UNIT_ID_SL3;
			iip_util_rr_1.src_pixid = E_IM_IIP_PIXID_2;
			iip_util_rr_1.dst_pixid = E_IM_IIP_PIXID_3;
			iip_util_rr_1.resize_mode = E_IM_IIP_UTIL_RESIZE_MODE_NEAREST;
			break;
		case 1:
			iip_util_rr_0.afn_unitid = E_IM_IIP_UNIT_ID_AFN2;
			iip_util_rr_0.sl_unitid = E_IM_IIP_UNIT_ID_SL4;
			iip_util_rr_0.src_pixid = E_IM_IIP_PIXID_4;
			iip_util_rr_0.dst_pixid = E_IM_IIP_PIXID_5;
			iip_util_rr_0.resize_mode = E_IM_IIP_UTIL_RESIZE_MODE_BICUBIC;
			iip_util_rr_1.afn_unitid = E_IM_IIP_UNIT_ID_AFN0;
			iip_util_rr_1.sl_unitid = E_IM_IIP_UNIT_ID_SL5;
			iip_util_rr_1.src_pixid = E_IM_IIP_PIXID_6;
			iip_util_rr_1.dst_pixid = E_IM_IIP_PIXID_7;
			iip_util_rr_1.resize_mode = E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR;
			break;
		case 2:
			iip_util_rr_0.afn_unitid = E_IM_IIP_UNIT_ID_AFN2;
			iip_util_rr_0.sl_unitid = E_IM_IIP_UNIT_ID_SL6;
			iip_util_rr_0.src_pixid = E_IM_IIP_PIXID_8;
			iip_util_rr_0.dst_pixid = E_IM_IIP_PIXID_9;
			iip_util_rr_0.resize_mode = E_IM_IIP_UTIL_RESIZE_MODE_BICUBIC;
			iip_util_rr_1.afn_unitid = E_IM_IIP_UNIT_ID_AFN0;
			iip_util_rr_1.sl_unitid = E_IM_IIP_UNIT_ID_SL5;
			iip_util_rr_1.src_pixid = E_IM_IIP_PIXID_10;
			iip_util_rr_1.dst_pixid = E_IM_IIP_PIXID_11;
			iip_util_rr_1.resize_mode = E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR;
			break;
		}

		Ddim_Print(( "** %u\n", loopcnt ));
		ercd = IM_IIP_Utility_ResizeRotate(&iip_util_rr_0, &iip_util_rr_1, param_master_IF, param_buffer_addr, wait_time);
		printf("IM_IIP_Utility_ResizeRotate result = 0x%x.\n", ercd);

		switch (ercd)
		{
		case D_IM_IIP_OK:	// FALLTHROUGH
		case D_IM_IIP_TIMEOUT_ERR:
			CT_Im_IIP_Print_Unitcfg_Byid(iip_util_rr_0.afn_unitid);
			CT_Im_IIP_Print_Unitcfg_Byid(iip_util_rr_0.sl_unitid);
			CT_Im_IIP_Print_Pixfmttbl_Byid(iip_util_rr_0.src_pixid);
			CT_Im_IIP_Print_Pixfmttbl_Byid(iip_util_rr_0.dst_pixid);

			CT_Im_IIP_Print_Unitcfg_Byid(iip_util_rr_1.afn_unitid);
			CT_Im_IIP_Print_Unitcfg_Byid(iip_util_rr_1.sl_unitid);
			CT_Im_IIP_Print_Pixfmttbl_Byid(iip_util_rr_1.src_pixid);
			CT_Im_IIP_Print_Pixfmttbl_Byid(iip_util_rr_1.dst_pixid);
			break;
		default:
			// do nothing
			break;
		}
	}
}

INT32 CT_Im_IIP_1_1_43( VOID)
{
	T_IM_IIP_UTIL_CSC iip_util_csc_0 = {
//		.ld_unitid = 0,
//		.csc_unitid = 0,
//		.sl_unitid = 0,
//		.src_pixid = 0,
//		.dst_pixid = 0,
	.src = {								// Source image info.
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 1280,							// Width
	.lines = 720,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 1280,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 720,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 1280, .Cb_B = 1280, .Cr_R = 1280, .Alpha = 1280,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x20000000, .Cb_B = 0x21000000, .Cr_R = 0x22000000, .Alpha = 0x20000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, .dst = {								// Destination image info.
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 640,							// Width
	.lines = 360,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 640,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 360,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 640, .Cb_B = 640, .Cr_R = 640, .Alpha = 640,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x23000000, .Cb_B = 0x24000000, .Cr_R = 0x25000000, .Alpha = 0x23000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF1,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF1,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF1,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF1,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, .ld_cache_select = E_IM_IIP_PARAM_CSEL_1, .pix_depth = D_IM_IIP_PDEPTH_8BITS, .alpha_depth = E_IM_IIP_ADEPTH_8BITS, .alpha_subsampling = D_IM_IIP_ALPHA_NO_SUBSAMP, .csck = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 8, 9, 10, 11 }, }, .csck_mode_sel = 0, .alpha_in_sel = E_IM_IIP_PARAM_ALPSEL_DIRECT, .alpha_out_sel = E_IM_IIP_PARAM_ALOSEL_CALCULATED, .alpha_val = 0, .sl_sftval = 0, };
	T_IM_IIP_UTIL_CSC iip_util_csc_1 = {
//		.ld_unitid = 0,
//		.csc_unitid = 0,
//		.sl_unitid = 0,
//		.src_pixid = 0,
//		.dst_pixid = 0,
	.src = {								// Source image info.
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 1440,							// Width
	.lines = 1080,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_PLANE,			// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC420,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 1440,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 1080,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 1440, .Cb_B = 1440 / 2, .Cr_R = 1440 / 2, .Alpha = 1440,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x20000000, .Cb_B = 0x21000000, .Cr_R = 0x22000000, .Alpha = 0x20000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, .dst = {								// Destination image info.
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 960,							// Width
	.lines = 720,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_PLANE,			// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC420,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 960,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 720,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 960, .Cb_B = 960 / 2, .Cr_R = 960 / 2, .Alpha = 960,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x23000000, .Cb_B = 0x24000000, .Cr_R = 0x25000000, .Alpha = 0x23000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF1,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF1,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF1,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF1,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, .ld_cache_select = E_IM_IIP_PARAM_CSEL_0, .pix_depth = D_IM_IIP_PDEPTH_8BITS, .alpha_depth = E_IM_IIP_ADEPTH_8BITS, .alpha_subsampling = D_IM_IIP_ALPHA_NO_SUBSAMP, .csck = { { 12, 13, 14, 15 }, { 16, 17, 18, 19 }, { 20, 21, 22, 23 }, { 24, 25, 26, 27 }, }, .csck_mode_sel = 0, .alpha_in_sel = E_IM_IIP_PARAM_ALPSEL_DIRECT, .alpha_out_sel = E_IM_IIP_PARAM_ALOSEL_CALCULATED, .alpha_val = 0, .sl_sftval = 0, };
	UCHAR param_master_IF = D_IM_IIP_MASTER_IF0;
	UCHAR param_buffer[D_IM_IIP_UTIL_CSC_BUF_BYTES * 2 + 8];
	ULONG param_buffer_addr = (((ULONG) param_buffer) + 7UL) & 0xFFFFFFF8UL;	// Convet 8bytes align
	INT32 wait_time = 100;
	INT32 ercd;
	UINT32 loopcnt;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	for (loopcnt = 0;; loopcnt++)
	{
		switch (loopcnt)
		{
		default:
			return D_DDIM_OK;
		case 0:
			iip_util_csc_0.ld_unitid = E_IM_IIP_UNIT_ID_LD0;
			iip_util_csc_0.csc_unitid = E_IM_IIP_UNIT_ID_CSC0;
			iip_util_csc_0.sl_unitid = E_IM_IIP_UNIT_ID_SL2;
			iip_util_csc_0.src_pixid = E_IM_IIP_PIXID_0;
			iip_util_csc_0.dst_pixid = E_IM_IIP_PIXID_1;
			iip_util_csc_1.ld_unitid = E_IM_IIP_UNIT_ID_LD1;
			iip_util_csc_1.csc_unitid = E_IM_IIP_UNIT_ID_CSC1;
			iip_util_csc_1.sl_unitid = E_IM_IIP_UNIT_ID_SL3;
			iip_util_csc_1.src_pixid = E_IM_IIP_PIXID_2;
			iip_util_csc_1.dst_pixid = E_IM_IIP_PIXID_3;
			break;
		case 1:
			iip_util_csc_0.ld_unitid = E_IM_IIP_UNIT_ID_LD2;
			iip_util_csc_0.csc_unitid = E_IM_IIP_UNIT_ID_CSC2;
			iip_util_csc_0.sl_unitid = E_IM_IIP_UNIT_ID_SL4;
			iip_util_csc_0.src_pixid = E_IM_IIP_PIXID_4;
			iip_util_csc_0.dst_pixid = E_IM_IIP_PIXID_5;
			iip_util_csc_1.ld_unitid = E_IM_IIP_UNIT_ID_LD1;
			iip_util_csc_1.csc_unitid = E_IM_IIP_UNIT_ID_CSC3;
			iip_util_csc_1.sl_unitid = E_IM_IIP_UNIT_ID_SL5;
			iip_util_csc_1.src_pixid = E_IM_IIP_PIXID_6;
			iip_util_csc_1.dst_pixid = E_IM_IIP_PIXID_7;
			break;
		case 2:
			iip_util_csc_0.ld_unitid = E_IM_IIP_UNIT_ID_LD2;
			iip_util_csc_0.csc_unitid = E_IM_IIP_UNIT_ID_CSC3;
			iip_util_csc_0.sl_unitid = E_IM_IIP_UNIT_ID_SL6;
			iip_util_csc_0.src_pixid = E_IM_IIP_PIXID_8;
			iip_util_csc_0.dst_pixid = E_IM_IIP_PIXID_9;
			iip_util_csc_1.ld_unitid = E_IM_IIP_UNIT_ID_LD1;
			iip_util_csc_1.csc_unitid = E_IM_IIP_UNIT_ID_CSC2;
			iip_util_csc_1.sl_unitid = E_IM_IIP_UNIT_ID_SL5;
			iip_util_csc_1.src_pixid = E_IM_IIP_PIXID_10;
			iip_util_csc_1.dst_pixid = E_IM_IIP_PIXID_11;
			break;
		}

		Ddim_Print(( "** %u\n", loopcnt ));
		ercd = IM_IIP_Utility_CSC(&iip_util_csc_0, &iip_util_csc_1, param_master_IF, param_buffer_addr, wait_time);
		printf("IM_IIP_Utility_CSC result = 0x%x.\n", ercd);

		switch (ercd)
		{
		case D_IM_IIP_OK:	// FALLTHROUGH
		case D_IM_IIP_TIMEOUT_ERR:
			CT_Im_IIP_Print_Unitcfg_Byid(iip_util_csc_0.ld_unitid);
			CT_Im_IIP_Print_Unitcfg_Byid(iip_util_csc_0.csc_unitid);
			CT_Im_IIP_Print_Unitcfg_Byid(iip_util_csc_0.sl_unitid);
			CT_Im_IIP_Print_Pixfmttbl_Byid(iip_util_csc_0.src_pixid);
			CT_Im_IIP_Print_Pixfmttbl_Byid(iip_util_csc_0.dst_pixid);

			CT_Im_IIP_Print_Unitcfg_Byid(iip_util_csc_1.ld_unitid);
			CT_Im_IIP_Print_Unitcfg_Byid(iip_util_csc_1.csc_unitid);
			CT_Im_IIP_Print_Unitcfg_Byid(iip_util_csc_1.sl_unitid);
			CT_Im_IIP_Print_Pixfmttbl_Byid(iip_util_csc_1.src_pixid);
			CT_Im_IIP_Print_Pixfmttbl_Byid(iip_util_csc_1.dst_pixid);
			break;
		default:
			// do nothing
			break;
		}
	}
}

INT32 CT_Im_IIP_1_1_44( VOID)
{
	USHORT lutram_a[D_IM_IIP_LUT_MAXNUM];
	USHORT lutram_b[D_IM_IIP_LUT_MAXNUM];
	USHORT lutram_c[D_IM_IIP_LUT_MAXNUM];
	USHORT lutram_d[D_IM_IIP_LUT_MAXNUM];
	T_IM_IIP_UTIL_LUT cfg = {
//		.ld_unitid = 0,
//		.lut_unitid = 0,
//		.sl_unitid = 0,
//		.src_pixid = 0,
//		.dst_pixid = 0,
	.src = {								// Source image info.
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 1280,							// Width
	.lines = 720,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 1280,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 720,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 1280, .Cb_B = 1280, .Cr_R = 1280, .Alpha = 1280,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x20000000, .Cb_B = 0x21000000, .Cr_R = 0x22000000, .Alpha = 0x20000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, .dst = {								// Destination image info.
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 640,							// Width
	.lines = 360,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 640,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 360,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 640, .Cb_B = 640, .Cr_R = 640, .Alpha = 640,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x23000000, .Cb_B = 0x24000000, .Cr_R = 0x25000000, .Alpha = 0x23000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF1,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF1,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF1,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF1,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, .ld_cache_select = E_IM_IIP_PARAM_CSEL_1, .pix_depth = D_IM_IIP_PDEPTH_8BITS, .alpha_depth = E_IM_IIP_ADEPTH_8BITS, .alpha_subsampling = D_IM_IIP_ALPHA_NO_SUBSAMP, .lut_pix_depth = { 0, 1, 2, 3 }, .splbit = { 4, 5, 6, 7, }, .lutram = { .buffer_bytes = { sizeof(lutram_a), sizeof(lutram_b), sizeof(lutram_c), sizeof(lutram_d), 0, 0, }, .buffer_addr = { lutram_a, lutram_b, lutram_c, lutram_d, 0, 0, }, }, };
	UCHAR param_master_IF = D_IM_IIP_MASTER_IF0;
	UCHAR param_buffer[D_IM_IIP_UTIL_LUT_BUF_BYTES + 8];
	ULONG param_buffer_addr = (((ULONG) param_buffer) + 7UL) & 0xFFFFFFF8UL;	// Convet 8bytes align
	INT32 wait_time = 100;
	INT32 ercd;
	UINT32 loopcnt;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	for (loopcnt = 0; loopcnt < D_IM_IIP_LUT_MAXNUM; loopcnt++)
	{
		lutram_a[loopcnt] = 0x0000 + loopcnt;
		lutram_b[loopcnt] = 0x1000 + loopcnt;
		lutram_c[loopcnt] = 0x2000 + loopcnt;
		lutram_d[loopcnt] = 0x3000 + loopcnt;
	}

	for (loopcnt = 0;; loopcnt++)
	{
		switch (loopcnt)
		{
		default:
			return D_DDIM_OK;
		case 0:
			cfg.ld_unitid = E_IM_IIP_UNIT_ID_LD0;
			cfg.lut_unitid = E_IM_IIP_UNIT_ID_LUT;
			cfg.sl_unitid = E_IM_IIP_UNIT_ID_SL2;
			cfg.src_pixid = E_IM_IIP_PIXID_0;
			cfg.dst_pixid = E_IM_IIP_PIXID_1;
			break;
		case 1:
			cfg.ld_unitid = E_IM_IIP_UNIT_ID_LD1;
			cfg.lut_unitid = E_IM_IIP_UNIT_ID_LUT;
			cfg.sl_unitid = E_IM_IIP_UNIT_ID_SL3;
			cfg.src_pixid = E_IM_IIP_PIXID_2;
			cfg.dst_pixid = E_IM_IIP_PIXID_3;
			break;
		case 2:
			cfg.ld_unitid = E_IM_IIP_UNIT_ID_LD2;
			cfg.lut_unitid = E_IM_IIP_UNIT_ID_LUT;
			cfg.sl_unitid = E_IM_IIP_UNIT_ID_SL4;
			cfg.src_pixid = E_IM_IIP_PIXID_4;
			cfg.dst_pixid = E_IM_IIP_PIXID_5;
			break;
		case 3:
			cfg.ld_unitid = E_IM_IIP_UNIT_ID_LD2;
			cfg.lut_unitid = E_IM_IIP_UNIT_ID_LUT;
			cfg.sl_unitid = E_IM_IIP_UNIT_ID_SL5;
			cfg.src_pixid = E_IM_IIP_PIXID_6;
			cfg.dst_pixid = E_IM_IIP_PIXID_7;
			break;
		case 4:
			cfg.ld_unitid = E_IM_IIP_UNIT_ID_LD2;
			cfg.lut_unitid = E_IM_IIP_UNIT_ID_LUT;
			cfg.sl_unitid = E_IM_IIP_UNIT_ID_SL6;
			cfg.src_pixid = E_IM_IIP_PIXID_8;
			cfg.dst_pixid = E_IM_IIP_PIXID_9;
			break;
		case 5:
			cfg.ld_unitid = E_IM_IIP_UNIT_ID_LD2;
			cfg.lut_unitid = E_IM_IIP_UNIT_ID_LUT;
			cfg.sl_unitid = E_IM_IIP_UNIT_ID_SL6;
			cfg.src_pixid = E_IM_IIP_PIXID_10;
			cfg.dst_pixid = E_IM_IIP_PIXID_11;
			break;
		}

		Ddim_Print(( "** %u\n", loopcnt ));
		ercd = IM_IIP_Utility_LUT(&cfg, param_master_IF, param_buffer_addr, wait_time);
		printf("IM_IIP_Utility_LUT result = 0x%x.\n", ercd);

		switch (ercd)
		{
		case D_IM_IIP_OK:	// FALLTHROUGH
		case D_IM_IIP_TIMEOUT_ERR:
			CT_Im_IIP_Print_Unitcfg_Byid(cfg.ld_unitid);
			CT_Im_IIP_Print_Unitcfg_Byid(cfg.lut_unitid);
			CT_Im_IIP_Print_Unitcfg_Byid(cfg.sl_unitid);
			CT_Im_IIP_Print_Pixfmttbl_Byid(cfg.src_pixid);
			CT_Im_IIP_Print_Pixfmttbl_Byid(cfg.dst_pixid);
			break;
		default:
			// do nothing
			break;
		}
	}
}

INT32 CT_Im_IIP_1_1_45( VOID)
{
	T_IM_IIP_UTIL_ALPHABLEND cfg = {
//		.ld_unitid = {
//			0, 0,
//		},
//		.blend_unitid = 0,
//		.sl_unitid = 0,
//		.src_pixid = {
//			0, 0,
//		},
//		.dst_pixid = 0,
	.src = { [0] = {									// Source image info[0].
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 1920,							// Width
	.lines = 1080,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 1920,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 1080,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 1920, .Cb_B = 1920, .Cr_R = 1920, .Alpha = 1920,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x20000000, .Cb_B = 0x21000000, .Cr_R = 0x22000000, .Alpha = 0x20000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, [1] = {									// Source image info[1].
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 1280,							// Width
	.lines = 720,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 1280,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 720,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 1280, .Cb_B = 1280, .Cr_R = 1280, .Alpha = 1280,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x23000000, .Cb_B = 0x24000000, .Cr_R = 0x25000000, .Alpha = 0x23000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF0,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, }, .dst = {								// Destination image info.
	.rect = {								// Rectangle info. (Source image area)
	.top = 0.0,								// Vertical position of top-left pixel
	.left = 0.0,							// Horizontal position of top-left pixel
	.width = 640,							// Width
	.lines = 360,							// Lines
	}, .gbl = {								// Global image info.
	.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
	.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
	.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
	.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
	.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,	// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
	.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,	// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
	.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,	// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
	.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,	// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
	}, .sign_Y_G = D_IM_IIP_UNSIGNED_DATA,			// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
	.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
	.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,		// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
	.sign_D3 = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
	.width = 640,						// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
	.lines = 360,							// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
	.line_bytes = {								// The size of byte of Global image 1 line.
	.Y_G = 640, .Cb_B = 640, .Cr_R = 640, .Alpha = 640,			// dummy
	}, .addr = {									// Beginning address of Global image.
	.Y_G = 0x26000000, .Cb_B = 0x27000000, .Cr_R = 0x28000000, .Alpha = 0x26000000,	// dummy
	}, .masterIF_Y_G = D_IM_IIP_MASTER_IF1,	// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
	.masterIF_Cb_B = D_IM_IIP_MASTER_IF1,// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
	.masterIF_Cr_R = D_IM_IIP_MASTER_IF1,// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
	.masterIF_Alpha = D_IM_IIP_MASTER_IF1,	// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
	}, }, .ld_cache_select = { E_IM_IIP_PARAM_CSEL_0, E_IM_IIP_PARAM_CSEL_1, }, .pix_depth = D_IM_IIP_PDEPTH_8BITS, .alpha_depth = E_IM_IIP_ADEPTH_8BITS, .alpha_subsampling = D_IM_IIP_ALPHA_NO_SUBSAMP, .alpha = { .step = E_IM_IIP_PARAM_ALPHA_STEP_8BITS, .sel = E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL, .out = E_IM_IIP_PARAM_ALPHA_OUT_NONE, .ALPHA_VAL = { 1, 2, 3, 4, }, }, };
	UCHAR param_master_IF = D_IM_IIP_MASTER_IF0;
	UCHAR param_buffer[D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES + 8];
	ULONG param_buffer_addr = (((ULONG) param_buffer) + 7UL) & 0xFFFFFFF8UL;	// Convet 8bytes align
	INT32 wait_time = 100;
	INT32 ercd;
	UINT32 loopcnt;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	for (loopcnt = 0;; loopcnt++)
	{
		switch (loopcnt)
		{
		default:
			return D_DDIM_OK;
		case 0:
			cfg.ld_unitid[0] = E_IM_IIP_UNIT_ID_LD0;
			cfg.ld_unitid[1] = E_IM_IIP_UNIT_ID_LD1;
			cfg.blend_unitid = E_IM_IIP_UNIT_ID_BLEND0;
			cfg.sl_unitid = E_IM_IIP_UNIT_ID_SL2;
			cfg.src_pixid[0] = E_IM_IIP_PIXID_0;
			cfg.src_pixid[1] = E_IM_IIP_PIXID_1;
			cfg.dst_pixid = E_IM_IIP_PIXID_2;
			break;
		case 1:
			cfg.ld_unitid[0] = E_IM_IIP_UNIT_ID_LD1;
			cfg.ld_unitid[1] = E_IM_IIP_UNIT_ID_LD2;
			cfg.blend_unitid = E_IM_IIP_UNIT_ID_BLEND0;
			cfg.sl_unitid = E_IM_IIP_UNIT_ID_SL3;
			cfg.src_pixid[0] = E_IM_IIP_PIXID_3;
			cfg.src_pixid[1] = E_IM_IIP_PIXID_4;
			cfg.dst_pixid = E_IM_IIP_PIXID_5;
			break;
		case 2:
			cfg.ld_unitid[0] = E_IM_IIP_UNIT_ID_LD0;
			cfg.ld_unitid[1] = E_IM_IIP_UNIT_ID_LD1;
			cfg.blend_unitid = E_IM_IIP_UNIT_ID_BLEND0;
			cfg.sl_unitid = E_IM_IIP_UNIT_ID_SL4;
			cfg.src_pixid[0] = E_IM_IIP_PIXID_6;
			cfg.src_pixid[1] = E_IM_IIP_PIXID_7;
			cfg.dst_pixid = E_IM_IIP_PIXID_8;
			break;
		case 3:
			cfg.ld_unitid[0] = E_IM_IIP_UNIT_ID_LD0;
			cfg.ld_unitid[1] = E_IM_IIP_UNIT_ID_LD1;
			cfg.blend_unitid = E_IM_IIP_UNIT_ID_BLEND0;
			cfg.sl_unitid = E_IM_IIP_UNIT_ID_SL5;
			cfg.src_pixid[0] = E_IM_IIP_PIXID_9;
			cfg.src_pixid[1] = E_IM_IIP_PIXID_10;
			cfg.dst_pixid = E_IM_IIP_PIXID_11;
			break;
		}

		Ddim_Print(( "** %u\n", loopcnt ));
		ercd = IM_IIP_Utility_AlphaBlend(&cfg, param_master_IF, param_buffer_addr, wait_time);
		printf("IM_IIP_Utility_AlphaBlend result = 0x%x.\n", ercd);

		switch (ercd)
		{
		case D_IM_IIP_OK:	// FALLTHROUGH
		case D_IM_IIP_TIMEOUT_ERR:
			CT_Im_IIP_Print_Unitcfg_Byid(cfg.ld_unitid[0]);
			CT_Im_IIP_Print_Unitcfg_Byid(cfg.ld_unitid[1]);
			CT_Im_IIP_Print_Unitcfg_Byid(cfg.blend_unitid);
			CT_Im_IIP_Print_Unitcfg_Byid(cfg.sl_unitid);
			CT_Im_IIP_Print_Pixfmttbl_Byid(cfg.src_pixid[0]);
			CT_Im_IIP_Print_Pixfmttbl_Byid(cfg.src_pixid[1]);
			CT_Im_IIP_Print_Pixfmttbl_Byid(cfg.dst_pixid);
			break;
		default:
			// do nothing
			break;
		}
	}
}
#endif //CO_CT_IM_IIP_DISABLE

CtImIip6* ct_im_iip_6_get(void)
{
	static CtImIip6* self = NULL;

	if (!self) {
//		self = k_object_new_with_private(CT_TYPE_IM_IIP_6, sizeof(CtImIip6Private));
	}

	return self;
}
