/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r8类
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

#include "ctimb2r8.h"
#include "ctimb2r1.h"
#include "ctimb2r7.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImB2r8, ct_im_b2r8);
#define CT_IM_B2R8_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImB2r8Private,CT_TYPE_IM_B2R8))


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define ct_im_b2r_check_target_pipe_no_1(a)		(((a)+1) & (ImB2r_D_IM_B2R_PIPE1+1))
#define ct_im_b2r_check_target_pipe_no_2(a)		(((a)+1) & (ImB2r_D_IM_B2R_PIPE2+1))


struct _CtImB2r8Private
{

};

/*
DECLS
*/

static void ct_im_b2r8_constructor(CtImB2r8 *self) 
{
//	CtImB2r8Private *priv = CT_IM_B2R8_GET_PRIVATE(self);
}

static void ct_im_b2r8_destructor(CtImB2r8 *self) 
{
//	CtImB2r8Private *priv = CT_IM_B2R8_GET_PRIVATE(self);
	self = NULL;
}

/*
IMPL//todo
*/

/*
PUBLIC//todo
*/

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r8_3_17: "
kint32 ct_im_b2r8_3_17( CtImB2r8 *self )
{
	kint32 ret;
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	CtImB2r7* ctImB2r7 = ct_im_b2r7_new();
	ctImB2r7->pipeNo = self->pipeNo;

	ret = ct_im_b2r7_3_11( ctImB2r7 );
	k_object_unref(ctImB2r7);
	return ret;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r8_3_18: "
kint32 ct_im_b2r8_3_18( CtImB2r8 *self )
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

	b2r_rect_param.input_size.img_top = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES / 4 - 1;
	b2r_rect_param.input_size.img_left = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH / 4 - 1;
	b2r_rect_param.input_size.img_width = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH / 2;
	b2r_rect_param.input_size.img_lines = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES / 2;

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
#define D_IM_B2R_FUNC_NAME "ct_im_b2r8_3_19: "
kint32 ct_im_b2r8_3_19( CtImB2r8 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	return ct_im_b2r8_3_18( self );
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r8_3_20: "
kint32 ct_im_b2r8_3_20( CtImB2r8 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	return ct_im_b2r8_3_18( self );
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r8_3_21: "
kint32 ct_im_b2r8_3_21( CtImB2r8 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw12bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbU8;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DdimUserCustom_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_rect_param.input_size.img_top = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES / 4;
	b2r_rect_param.input_size.img_left = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH / 4 - 1;
	b2r_rect_param.input_size.img_width = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH / 2;
	b2r_rect_param.input_size.img_lines = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES / 2;

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
#define D_IM_B2R_FUNC_NAME "ct_im_b2r8_3_22: "
kint32 ct_im_b2r8_3_22( CtImB2r8 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	return ct_im_b2r8_3_21( self );
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r8_3_23: "
kint32 ct_im_b2r8_3_23( CtImB2r8 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw10bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbU8;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DdimUserCustom_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_rect_param.input_size.img_top = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES / 4 - 1;
	b2r_rect_param.input_size.img_left = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH / 4;
	b2r_rect_param.input_size.img_width = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH / 2;
	b2r_rect_param.input_size.img_lines = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES / 2;

	memset( &b2r_out_addr, '\x00', sizeof(b2r_out_addr) );
	b2r_out_addr = gctImB2rOutAddrRgb;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_Left_Shift( self->pipeNo, 2, 1 );
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
	Im_B2R_Ctrl_Left_Shift( self->pipeNo, 2, 1 );
	Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_R, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_G, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_B, gctImB2rKneeTbl );
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
#define D_IM_B2R_FUNC_NAME "ct_im_b2r8_3_24: "
kint32 ct_im_b2r8_3_24( CtImB2r8 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	return ct_im_b2r8_3_23( self );
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r8_3_25: "
kint32 ct_im_b2r8_3_25( CtImB2r8 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw8bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbU8;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DdimUserCustom_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_rect_param.input_size.img_top = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES / 4 - 1;
	b2r_rect_param.input_size.img_left = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH / 4 - 1;
	b2r_rect_param.input_size.img_width = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH / 2;
	b2r_rect_param.input_size.img_lines = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES / 2;

	memset( &b2r_out_addr, '\x00', sizeof(b2r_out_addr) );
	b2r_out_addr = gctImB2rOutAddrRgb;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_Left_Shift( self->pipeNo, 3, 1 );
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
	Im_B2R_Ctrl_Left_Shift( self->pipeNo, 3, 1 );
	Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_R, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_G, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_B, gctImB2rKneeTbl );
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
#define D_IM_B2R_FUNC_NAME "ct_im_b2r8_3_26: "
kint32 ct_im_b2r8_3_26( CtImB2r8 *self )
{
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	return ct_im_b2r8_3_25( self );
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r8_3_27: "
kint32 ct_im_b2r8_3_27( CtImB2r8 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_B2B_DIRECT b2r_ctrl_b2b_direct = gctImB2rCtrlB2bDirect;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbU8;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DdimUserCustom_FLGPTN flgptn = 0;
	USHORT ring_pixs;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_ctrl.bayer_top_pixel = ImB2r_D_IM_B2R_TOP_PIXEL_GR;

	Im_B2R_Get_HRingPixs( 0, &ring_pixs );
	b2r_ctrl_b2b_direct.even_line_start_timming -= ring_pixs / 2;

	b2r_rect_param.input_size.img_top = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES / 4;
	b2r_rect_param.input_size.img_left = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH / 4 - 1;
	b2r_rect_param.input_size.img_width = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_WIDTH / 2;
	b2r_rect_param.input_size.img_lines = CtImB2r_D_IM_B2R_SRC_IMG_PIXS_LINES / 2;

	memset( &b2r_out_addr, '\x00', sizeof(b2r_out_addr) );
	b2r_out_addr = gctImB2rOutAddrRgb;

	ct_im_b2r1_set_b2b( (E_IM_PRO_UNIT_NUM)self->pipeNo );

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	// Set clock to B2B-B2R direct input mode.
	Dd_Top_Set_CLKSTOP10_B2R1CK( 1 );	// ★B2R1 Clock Stop
	Dd_Top_Set_CLKSEL4_B2R1CLK( 24 );	// ★B2R1 Clock select(SRO1CLK_2)
	Dd_Top_Set_CLKSTOP10_B2R1CK( 0 );	// ★B2R1 Clock Start
	Dd_Top_Set_CLKSTOP12_B2R2CK( 1 );	// ★B2R2 Clock Stop
	Dd_Top_Set_CLKSEL6_B2R2CLK( 24 );	// ★B2R2 Clock select(SRO2CLK_2)
	Dd_Top_Set_CLKSTOP12_B2R2CK( 0 );	// ★B2R2 Clock Start
#endif

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_ModeB2BDirect( self->pipeNo, &b2r_ctrl_b2b_direct );
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

	ercd = Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Im_B2R_Ctrl_ModeB2BDirect( self->pipeNo, &b2r_ctrl_b2b_direct );
	Im_B2R_Ctrl_Left_Shift( self->pipeNo, 0, 0 );
	Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_R, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_G, gctImB2rKneeTbl );
	Im_B2R_Set_Knee_Table( self->pipeNo, E_B2R_RGBTBL_B, gctImB2rKneeTbl );
	Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
#endif

	CtImB2r1* ctImB2r1 = ct_im_b2r1_new();
	ctImB2r1->pipeNo = self->pipeNo;
	ct_im_b2r1_set_wb_gain( ctImB2r1 );
	k_object_unref(ctImB2r1);

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

	ct_im_b2r1_start_b2b( (E_IM_PRO_UNIT_NUM)self->pipeNo );
	ct_im_b2r1_waitend_stop_b2b( (E_IM_PRO_UNIT_NUM)self->pipeNo );

	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= ImB2r_D_IM_B2R2_INT_FLG_YBW_END;
	}
#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_WaitEnd( NULL, flgptn, 30 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Stop( self->pipeNo );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_WaitEnd( NULL, flgptn, 30 );
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


CtImB2r8* ct_im_b2r8_new(void) 
{
    CtImB2r8 *self = k_object_new_with_private(CT_TYPE_IM_B2R8, sizeof(CtImB2r8Private));
    return self;
}
