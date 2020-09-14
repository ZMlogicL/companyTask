/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r9类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "ctimb2r.h"

// #include "im_b2r.h"
#include "../../ImageMacro/src/imb2r.h"
#include "im_pro.h"
// #include "im_pro_common.h"
#include "../../ImageMacro/src/improcommon.h"

#include "driver_common.h"
// #include "ddim_user_custom.h"
#include "../../../../milb_api_usercustom/src/ddimusercustom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
// #include "dd_top.h"
#include "../../DeviceDriver/LSITop/src/ddtop.h"
#endif

#include "jdsb2r.h"

#include <stdlib.h>
#include <string.h>

#include "ctimb2r.h"

#include "ctimb2r9.h"
#include "ctimb2r1.h"
#include "ctimb2r6.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImB2r9, ct_im_b2r9);
#define CT_IM_B2R9_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImB2r9Private,CT_TYPE_IM_B2R9))


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define ct_im_b2r_check_target_pipe_no_1(a)		(((a)+1) & (ImB2r_D_IM_B2R_PIPE1+1))
#define ct_im_b2r_check_target_pipe_no_2(a)		(((a)+1) & (ImB2r_D_IM_B2R_PIPE2+1))


struct _CtImB2r9Private
{

};


// T_IM_B2R_RECT table for RGB U16
static T_IM_B2R_RECT S_GCT_IM_B2R_RECT_PARAM_OUT_RGB_U16 = {
	.input_size.img_left = 0,
	.input_size.img_top = 0,
	.input_size.img_width = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH,
	.input_size.img_lines = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES,
	.output_size = {
		.output_global_w = CtImB2r_D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U16,
	},
};


// Deknee table.
static const USHORT S_GCT_IM_B2R_DEKNEE_TBL[ImB2r_D_IM_B2R_TABLE_MAX_BAYER_DEKNEE] = {
	     0,    16,    32,    48,    64,    80,    96,   112,   128,   144,   160,   176,   192,   208,   224,   240,
	   256,   273,   289,   305,   321,   337,   353,   369,   385,   401,   417,   433,   449,   465,   481,   497,
	   513,   529,   546,   562,   578,   594,   610,   626,   642,   658,   674,   690,   706,   722,   738,   754,
	   770,   786,   802,   819,   835,   851,   867,   883,   899,   915,   931,   947,   963,   979,   995,  1011,
	  1027,  1043,  1059,  1075,  1092,  1108,  1124,  1140,  1156,  1172,  1188,  1204,  1220,  1236,  1252,  1268,
	  1284,  1300,  1316,  1332,  1348,  1365,  1381,  1397,  1413,  1429,  1445,  1461,  1477,  1493,  1509,  1525,
	  1541,  1557,  1573,  1589,  1605,  1621,  1638,  1654,  1670,  1686,  1702,  1718,  1734,  1750,  1766,  1782,
	  1798,  1814,  1830,  1846,  1862,  1878,  1894,  1911,  1927,  1943,  1959,  1975,  1991,  2007,  2023,  2039,
	  2055,  2071,  2087,  2103,  2119,  2135,  2151,  2167,  2184,  2200,  2216,  2232,  2248,  2264,  2280,  2296,
	  2312,  2328,  2344,  2360,  2376,  2392,  2408,  2424,  2440,  2457,  2473,  2489,  2505,  2521,  2537,  2553,
	  2569,  2585,  2601,  2617,  2633,  2649,  2665,  2681,  2697,  2713,  2730,  2746,  2762,  2778,  2794,  2810,
	  2826,  2842,  2858,  2874,  2890,  2906,  2922,  2938,  2954,  2970,  2986,  3003,  3019,  3035,  3051,  3067,
	  3083,  3099,  3115,  3131,  3147,  3163,  3179,  3195,  3211,  3227,  3243,  3259,  3276,  3292,  3308,  3324,
	  3340,  3356,  3372,  3388,  3404,  3420,  3436,  3452,  3468,  3484,  3500,  3516,  3532,  3549,  3565,  3581,
	  3597,  3613,  3629,  3645,  3661,  3677,  3693,  3709,  3725,  3741,  3757,  3773,  3789,  3805,  3822,  3838,
	  3854,  3870,  3886,  3902,  3918,  3934,  3950,  3966,  3982,  3998,  4014,  4030,  4046,  4062,  4078,  4095,
};

/*
DECLS
*/


static void ct_im_b2r9_constructor(CtImB2r9 *self) 
{
//	CtImB2r9Private *priv = CT_IM_B2R9_GET_PRIVATE(self);
}

static void ct_im_b2r9_destructor(CtImB2r9 *self) 
{
//	CtImB2r9Private *priv = CT_IM_B2R9_GET_PRIVATE(self);
	self = NULL;
}

/*
IMPL//todo
*/

/*
PUBLIC//todo
*/

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r9_3_28: "
kint32 ct_im_b2r9_3_28( CtImB2r9 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbP12;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DdimUserCustom_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_ctrl.ybw.output_dtype = ImB2r_D_IM_B2R_STL_DTYP_PACK12;
	b2r_ctrl.ybw.knee_enable = 0;
	b2r_ctrl.deknee_enable = 1;

	memset( &b2r_out_addr, '\x00', sizeof(b2r_out_addr) );
	b2r_out_addr = gctImB2rOutAddrRgb;
	b2r_out_addr.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_R = (void*)CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_P12_R_ADDR_TOP;
	b2r_out_addr.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_G = (void*)CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_P12_G_ADDR_TOP;
	b2r_out_addr.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_B = (void*)CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_P12_B_ADDR_TOP;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &gctImB2rCtrlSdramInRaw8bit );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Deknee_Table( self->pipeNo, S_GCT_IM_B2R_DEKNEE_TBL );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	CtImB2r1* ctImB2r1 = ct_im_b2r1_new();
	ctImB2r1->pipeNo = self->pipeNo;
	ct_im_b2r1_set_wb_gain( ctImB2r1 );
	k_object_unref(ctImB2r1);
#else
	Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Im_B2R_Set_Deknee_Table( self->pipeNo, S_GCT_IM_B2R_DEKNEE_TBL );
	Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
#endif

	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", 0 ));

#ifdef ImB2r_IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R Start Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

#ifdef D_IM_B2R_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[0] = 1;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[1] = 1;
	}
#endif
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R Start\n" ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Start( self->pipeNo, ImB2r_D_IM_B2R_START_WITH_YBW );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Start( self->pipeNo, ImB2r_D_IM_B2R_START_WITH_YBW );
#endif

#ifdef D_IM_B2R_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[0] = 0;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[1] = 0;
	}
#endif

	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R2_INT_FLG_YBW_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_WaitEnd( NULL, flgptn, 60 * 10 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Stop( self->pipeNo );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_WaitEnd( NULL, flgptn, 60 * 10 );
	Im_B2R_Stop( self->pipeNo );
#endif

	ct_im_b2r1_print_b2r_common_reg();
	ct_im_b2r1_print_b2r_ybr_reg();
	ct_im_b2r1_print_b2r_ybw_reg();
	ct_im_b2r1_print_b2r_ctrl_reg();
	ct_im_b2r1_print_b2r_ctrl_modesdraminput_reg();
	ct_im_b2r1_print_b2r_ctrl_modeb2bdirect_reg();
	ct_im_b2r1_print_rect_reg();
	ct_im_b2r1_print_trimming_reg();
	ct_im_b2r1_print_other_reg();
	ct_im_b2r1_print_fb2r_ctrl_reg();
	ct_im_b2r1_print_axi_reg();


#ifdef ImB2r_IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R End Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

	return D_DDIM_OK;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r9_3_29: "
kint32 ct_im_b2r9_3_29( CtImB2r9 *self )
{
	kint32 ret;
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	CtImB2r6* ctImB2r6 = ct_im_b2r6_new();
	ctImB2r6->pipeNo = self->pipeNo;
	ret = ct_im_b2r6_3_1( ctImB2r6 );
	k_object_unref(ctImB2r6);
	return ret;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r9_3_30: "
kint32 ct_im_b2r9_3_30( CtImB2r9 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw16bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbU8;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DdimUserCustom_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_ctrl.cia_bypass = 1;
	b2r_ctrl.cia_padding = 0;

	memset( &b2r_out_addr, '\x00', sizeof(b2r_out_addr) );
	b2r_out_addr = gctImB2rOutAddrRgb;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_R, gctImB2rKneeTbl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_G, gctImB2rKneeTbl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_B, gctImB2rKneeTbl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	CtImB2r1* ctImB2r1 = ct_im_b2r1_new();
	ctImB2r1->pipeNo = self->pipeNo;
	ct_im_b2r1_set_wb_gain( ctImB2r1 );
	k_object_unref(ctImB2r1);
#else
	Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_R, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_G, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_B, gctImB2rKneeTbl );
	Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
#endif

	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", 0 ));

#ifdef ImB2r_IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R Start Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

#ifdef D_IM_B2R_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[0] = 1;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[1] = 1;
	}
#endif
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R Start\n" ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Start( self->pipeNo, ImB2r_D_IM_B2R_START_WITH_YBW );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Start( self->pipeNo, ImB2r_D_IM_B2R_START_WITH_YBW );
#endif

#ifdef D_IM_B2R_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[0] = 0;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[1] = 0;
	}
#endif

	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R2_INT_FLG_YBW_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_WaitEnd( NULL, flgptn, 60 * 10 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Stop( self->pipeNo );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_WaitEnd( NULL, flgptn, 60 * 10 );
	Im_B2R_Stop( self->pipeNo );
#endif

	ct_im_b2r1_print_b2r_common_reg();
	ct_im_b2r1_print_b2r_ybr_reg();
	ct_im_b2r1_print_b2r_ybw_reg();
	ct_im_b2r1_print_b2r_ctrl_reg();
	ct_im_b2r1_print_b2r_ctrl_modesdraminput_reg();
	ct_im_b2r1_print_b2r_ctrl_modeb2bdirect_reg();
	ct_im_b2r1_print_rect_reg();
	ct_im_b2r1_print_trimming_reg();
	ct_im_b2r1_print_other_reg();
	ct_im_b2r1_print_fb2r_ctrl_reg();
	ct_im_b2r1_print_axi_reg();


#ifdef ImB2r_IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R End Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

	return D_DDIM_OK;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r9_3_31: "
kint32 ct_im_b2r9_3_31( CtImB2r9 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw16bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbU8;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DdimUserCustom_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_ctrl.cia_padding = 0;

	memset( &b2r_out_addr, '\x00', sizeof(b2r_out_addr) );
	b2r_out_addr = gctImB2rOutAddrRgb;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_R, gctImB2rKneeTbl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_G, gctImB2rKneeTbl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_B, gctImB2rKneeTbl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	CtImB2r1* ctImB2r1 = ct_im_b2r1_new();
	ctImB2r1->pipeNo = self->pipeNo;
	ct_im_b2r1_set_wb_gain( ctImB2r1 );
	k_object_unref(ctImB2r1);
#else
	Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_R, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_G, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_B, gctImB2rKneeTbl );
	Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
#endif

	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", 0 ));

#ifdef ImB2r_IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R Start Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

#ifdef D_IM_B2R_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[0] = 1;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[1] = 1;
	}
#endif
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R Start\n" ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Start( self->pipeNo, ImB2r_D_IM_B2R_START_WITH_YBW );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Start( self->pipeNo, ImB2r_D_IM_B2R_START_WITH_YBW );
#endif

#ifdef D_IM_B2R_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[0] = 0;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[1] = 0;
	}
#endif

	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R2_INT_FLG_YBW_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_WaitEnd( NULL, flgptn, 60 * 10 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Stop( self->pipeNo );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_WaitEnd( NULL, flgptn, 60 * 10 );
	Im_B2R_Stop( self->pipeNo );
#endif

	ct_im_b2r1_print_b2r_common_reg();
	ct_im_b2r1_print_b2r_ybr_reg();
	ct_im_b2r1_print_b2r_ybw_reg();
	ct_im_b2r1_print_b2r_ctrl_reg();
	ct_im_b2r1_print_b2r_ctrl_modesdraminput_reg();
	ct_im_b2r1_print_b2r_ctrl_modeb2bdirect_reg();
	ct_im_b2r1_print_rect_reg();
	ct_im_b2r1_print_trimming_reg();
	ct_im_b2r1_print_other_reg();
	ct_im_b2r1_print_fb2r_ctrl_reg();
	ct_im_b2r1_print_axi_reg();


#ifdef ImB2r_IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R End Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

	return D_DDIM_OK;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r9_3_32: "
kint32 ct_im_b2r9_3_32( CtImB2r9 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw16bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbU8;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_CTRL_TRIMMING b2r_ctrl_trimming;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DdimUserCustom_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_ctrl_trimming.trimming_enable = ImB2r_D_IM_B2R_ENABLE_ON;
	b2r_ctrl_trimming.start_x = CtImB2r_D_IM_B2R_DST_IMG_PIXS_WIDTH / 4;
	b2r_ctrl_trimming.start_y = CtImB2r_D_IM_B2R_DST_IMG_PIXS_LINES / 4;
	b2r_ctrl_trimming.width = CtImB2r_D_IM_B2R_DST_IMG_PIXS_WIDTH / 2;
	b2r_ctrl_trimming.lines = CtImB2r_D_IM_B2R_DST_IMG_PIXS_LINES / 2;

	memset( &b2r_out_addr, '\x00', sizeof(b2r_out_addr) );
	b2r_out_addr = gctImB2rOutAddrRgb;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_R, gctImB2rKneeTbl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_G, gctImB2rKneeTbl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_B, gctImB2rKneeTbl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_Trimming( self->pipeNo, &b2r_ctrl_trimming );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	CtImB2r1* ctImB2r1 = ct_im_b2r1_new();
	ctImB2r1->pipeNo = self->pipeNo;
	ct_im_b2r1_set_wb_gain( ctImB2r1 );
	k_object_unref(ctImB2r1);
#else
	Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_R, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_G, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_B, gctImB2rKneeTbl );
	Im_B2R_Ctrl_Trimming( self->pipeNo, &b2r_ctrl_trimming );
	Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
#endif

	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", 0 ));

#ifdef ImB2r_IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "Status\n" ));
	Im_B2R_Print_Status();
#endif

#ifdef D_IM_B2R_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[0] = 1;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[1] = 1;
	}
#endif
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R Start\n" ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Start( self->pipeNo, ImB2r_D_IM_B2R_START_WITH_YBW );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Start( self->pipeNo, ImB2r_D_IM_B2R_START_WITH_YBW );
#endif

#ifdef D_IM_B2R_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[0] = 0;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[1] = 0;
	}
#endif

	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R2_INT_FLG_YBW_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_WaitEnd( NULL, flgptn, 60 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Stop( self->pipeNo );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_WaitEnd( NULL, flgptn, 60 );
	Im_B2R_Stop( self->pipeNo );
#endif

	ct_im_b2r1_print_b2r_ctrl_reg();
	ct_im_b2r1_print_b2r_ctrl_modesdraminput_reg();
	ct_im_b2r1_print_rect_reg();
	ct_im_b2r1_print_other_reg();

#ifdef ImB2r_IM_B2R_STATUS_PRINT
	Im_B2R_Print_Status();
#endif

	return D_DDIM_OK;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r9_3_33: "
kint32 ct_im_b2r9_3_33( CtImB2r9 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw16bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbU8;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DdimUserCustom_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	memset( &b2r_out_addr, '\x00', sizeof(b2r_out_addr) );
	b2r_out_addr = gctImB2rOutAddrRgb;

	// 180 degree rotation.
	b2r_out_addr.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_R = (void*)(((ULONG)b2r_out_addr.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_R)
															  + (b2r_rect_param.output_size.output_global_w
															  * (b2r_rect_param.input_size.img_lines -1)));
	b2r_out_addr.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_G = (void*)(((ULONG)b2r_out_addr.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_G)
															  + (b2r_rect_param.output_size.output_global_w
															  * (b2r_rect_param.input_size.img_lines -1)));
	b2r_out_addr.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_B = (void*)(((ULONG)b2r_out_addr.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_B)
															  + (b2r_rect_param.output_size.output_global_w
															  * (b2r_rect_param.input_size.img_lines -1)));

	b2r_rect_param.output_size.output_global_w = -b2r_rect_param.output_size.output_global_w;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_R, gctImB2rKneeTbl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_G, gctImB2rKneeTbl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_B, gctImB2rKneeTbl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_R, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_G, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_B, gctImB2rKneeTbl );
	Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
#endif

	CtImB2r1* ctImB2r1 = ct_im_b2r1_new();
	ctImB2r1->pipeNo = self->pipeNo;
	ct_im_b2r1_set_wb_gain( ctImB2r1 );
	k_object_unref(ctImB2r1);

	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", 0 ));

#ifdef ImB2r_IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "Status\n" ));
	Im_B2R_Print_Status();
#endif

#ifdef D_IM_B2R_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[0] = 1;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[1] = 1;
	}
#endif
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R Start\n" ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Start( self->pipeNo, ImB2r_D_IM_B2R_START_WITH_YBW );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Start( self->pipeNo, ImB2r_D_IM_B2R_START_WITH_YBW );
#endif

#ifdef D_IM_B2R_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[0] = 0;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[1] = 0;
	}
#endif

	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R2_INT_FLG_YBW_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_WaitEnd( NULL, flgptn, 60 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Stop( self->pipeNo );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_WaitEnd( NULL, flgptn, 60 );
	Im_B2R_Stop( self->pipeNo );
#endif

	ct_im_b2r1_print_b2r_common_reg();
	ct_im_b2r1_print_b2r_ybr_reg();
	ct_im_b2r1_print_b2r_ybw_reg();
	ct_im_b2r1_print_b2r_ctrl_reg();
	ct_im_b2r1_print_b2r_ctrl_modesdraminput_reg();
	ct_im_b2r1_print_rect_reg();
	ct_im_b2r1_print_fb2r_ctrl_reg();

#ifdef ImB2r_IM_B2R_STATUS_PRINT
	Im_B2R_Print_Status();
#endif

	return D_DDIM_OK;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r9_3_34: "
kint32 ct_im_b2r9_3_34( CtImB2r9 *self )
{
	kint32 ret;
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	CtImB2r6* ctImB2r6 = ct_im_b2r6_new();
	ctImB2r6->pipeNo = self->pipeNo;
	ret = ct_im_b2r6_3_1( ctImB2r6 );
	k_object_unref(ctImB2r6);
	return ret;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r9_3_35: "
kint32 ct_im_b2r9_3_35( CtImB2r9 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw16bit;
	T_IM_B2R_RECT b2r_rect_param = S_GCT_IM_B2R_RECT_PARAM_OUT_RGB_U16;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DdimUserCustom_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_ctrl.ybw.output_dtype = ImB2r_D_IM_B2R_STL_DTYP_PACK16;
	b2r_ctrl.ybw.knee_enable = 0;

	memset( &b2r_out_addr, '\x00', sizeof(b2r_out_addr) );
	b2r_out_addr = gctImB2rOutAddrRgb;
	b2r_out_addr.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_R = (void*)CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U16_R_ADDR_TOP;
	b2r_out_addr.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_G = (void*)CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U16_G_ADDR_TOP;
	b2r_out_addr.output_addr[ImB2r_D_IM_B2R_YBW_BANK_0].rgb.addr_B = (void*)CtImB2r_D_IM_B2R_IMG_MEM_OUT_RGB_U16_B_ADDR_TOP;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	CtImB2r1* ctImB2r1 = ct_im_b2r1_new();
	ctImB2r1->pipeNo = self->pipeNo;
	ct_im_b2r1_set_wb_gain( ctImB2r1 );
	k_object_unref(ctImB2r1);
#else
	Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
#endif

	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", 0 ));

#ifdef ImB2r_IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R Start Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

#ifdef D_IM_B2R_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[0] = 1;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[1] = 1;
	}
#endif
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R Start\n" ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Start( self->pipeNo, ImB2r_D_IM_B2R_START_WITH_YBW );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Start( self->pipeNo, ImB2r_D_IM_B2R_START_WITH_YBW );
#endif

#ifdef D_IM_B2R_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[0] = 0;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		gIM_B2R_macro_fake_finish[1] = 0;
	}
#endif

	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R2_INT_FLG_YBW_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_WaitEnd( NULL, flgptn, 60 * 10 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Stop( self->pipeNo );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_WaitEnd( NULL, flgptn, 60 * 10 );
	Im_B2R_Stop( self->pipeNo );
#endif

	ct_im_b2r1_print_b2r_common_reg();
	ct_im_b2r1_print_b2r_ybr_reg();
	ct_im_b2r1_print_b2r_ybw_reg();
	ct_im_b2r1_print_b2r_ctrl_reg();
	ct_im_b2r1_print_b2r_ctrl_modesdraminput_reg();
	ct_im_b2r1_print_b2r_ctrl_modeb2bdirect_reg();
	ct_im_b2r1_print_rect_reg();
	ct_im_b2r1_print_trimming_reg();
	ct_im_b2r1_print_other_reg();
	ct_im_b2r1_print_fb2r_ctrl_reg();
	ct_im_b2r1_print_axi_reg();


#ifdef ImB2r_IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R End Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

	return D_DDIM_OK;
}


CtImB2r9* ct_im_b2r9_new(void) 
{
    CtImB2r9 *self = k_object_new_with_private(CT_TYPE_IM_B2R9, sizeof(CtImB2r9Private));
    return self;
}
