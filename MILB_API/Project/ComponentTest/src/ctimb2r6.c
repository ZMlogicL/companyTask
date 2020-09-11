/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r6类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "ct_im_b2r.h"

#include "im_b2r.h"
#include "im_pro.h"
#include "im_pro_common.h"

#include "driver_common.h"
#include "ddim_user_custom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif

#include "jdsb2r.h"

#include <stdlib.h>
#include <string.h>

#include "ctimb2r.h"

#include "ctimb2r6.h"
#include "ctimb2r1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImB2r6, ct_im_b2r6);
#define CT_IM_B2R6_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImB2r6Private,CT_TYPE_IM_B2R6))


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define ct_im_b2r_check_target_pipe_no_1(a)		(((a)+1) & (D_IM_B2R_PIPE1+1))
#define ct_im_b2r_check_target_pipe_no_2(a)		(((a)+1) & (D_IM_B2R_PIPE2+1))


struct _CtImB2r6Private
{

};

/*
DECLS
*/

static void ct_im_b2r6_constructor(CtImB2r6 *self) 
{
//	CtImB2r6Private *priv = CT_IM_B2R6_GET_PRIVATE(self);
}

static void ct_im_b2r6_destructor(CtImB2r6 *self) 
{
//	CtImB2r6Private *priv = CT_IM_B2R6_GET_PRIVATE(self);
	self = NULL;
}

/*
IMPL//todo
*/

/*
PUBLIC//todo
*/

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r6_3_1: "
kint32 ct_im_b2r6_3_1( CtImB2r6 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw16bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbU8;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

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

#ifdef IM_B2R_STATUS_PRINT
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
	ercd = Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
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
		flgptn |= D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= D_IM_B2R2_INT_FLG_YBW_END;
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


#ifdef IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R End Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

	return D_DDIM_OK;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r6_3_2: "
kint32 ct_im_b2r6_3_2( CtImB2r6 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw16bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbP12;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_ctrl.ybw.output_dtype = D_IM_B2R_STL_DTYP_PACK12;
	b2r_ctrl.ybw.knee_enable = 0;

	memset( &b2r_out_addr, '\x00', sizeof(b2r_out_addr) );
	b2r_out_addr = gctImB2rOutAddrRgb;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_R = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_P12_R_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_G = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_P12_G_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_B = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_P12_B_ADDR_TOP;

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

#ifdef IM_B2R_STATUS_PRINT
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
	ercd = Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
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
		flgptn |= D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= D_IM_B2R2_INT_FLG_YBW_END;
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


#ifdef IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R End Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

	return D_DDIM_OK;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r6_3_3: "
kint32 ct_im_b2r6_3_3( CtImB2r6 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw12bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbU8;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

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

#ifdef IM_B2R_STATUS_PRINT
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
	ercd = Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
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
		flgptn |= D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= D_IM_B2R2_INT_FLG_YBW_END;
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


#ifdef IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R End Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

	return D_DDIM_OK;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r6_3_4: "
kint32 ct_im_b2r6_3_4( CtImB2r6 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw12bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbP12;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_ctrl.ybw.output_dtype = D_IM_B2R_STL_DTYP_PACK12;
	b2r_ctrl.ybw.knee_enable = 0;

	memset( &b2r_out_addr, '\x00', sizeof(b2r_out_addr) );
	b2r_out_addr = gctImB2rOutAddrRgb;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_R = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_P12_R_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_G = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_P12_G_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_B = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_P12_B_ADDR_TOP;

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

#ifdef IM_B2R_STATUS_PRINT
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
	ercd = Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
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
		flgptn |= D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= D_IM_B2R2_INT_FLG_YBW_END;
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


#ifdef IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R End Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

	return D_DDIM_OK;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r6_3_5: "
kint32 ct_im_b2r6_3_5( CtImB2r6 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw10bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbU8;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

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

#ifdef IM_B2R_STATUS_PRINT
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
	ercd = Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
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
		flgptn |= D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= D_IM_B2R2_INT_FLG_YBW_END;
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


#ifdef IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R End Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

	return D_DDIM_OK;
}


#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r6_3_6: "
kint32 ct_im_b2r6_3_6( CtImB2r6 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlRaw;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInRaw10bit;
	T_IM_B2R_RECT b2r_rect_param = gctImB2rRectParamOutRgbP12;
	T_IM_B2R_INADDR_INFO b2r_in_addr = gctImB2rInAddrRaw;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_ctrl.ybw.output_dtype = D_IM_B2R_STL_DTYP_PACK12;
	b2r_ctrl.ybw.knee_enable = 0;

	memset( &b2r_out_addr, '\x00', sizeof(b2r_out_addr) );
	b2r_out_addr = gctImB2rOutAddrRgb;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_R = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_P12_R_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_G = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_P12_G_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_B = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_P12_B_ADDR_TOP;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_Left_Shift( self->pipeNo, 2, 1 );
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
	Im_B2R_Ctrl_Left_Shift( self->pipeNo, 2, 1 );
	Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
#endif

	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", 0 ));

#ifdef IM_B2R_STATUS_PRINT
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
	ercd = Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
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
		flgptn |= D_IM_B2R1_INT_FLG_YBW_END;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		flgptn |= D_IM_B2R2_INT_FLG_YBW_END;
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


#ifdef IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "B2R End Status\n" ));
	Im_B2R_Print_Status();
	Im_B2R_Print_ClockStatus();
	Im_B2R_Print_AccEnStatus();
#endif

	return D_DDIM_OK;
}


CtImB2r6* ct_im_b2r6_new(void) 
{
    CtImB2r6 *self = k_object_new_with_private(CT_TYPE_IM_B2R6, sizeof(CtImB2r6Private));
    return self;
}
