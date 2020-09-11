/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r3类
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

#include "ctimb2r3.h"
#include "ctimb2r1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImB2r3, ct_im_b2r3);
#define CT_IM_B2R3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImB2r3Private,CT_TYPE_IM_B2R3))


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define ct_im_b2r_check_target_pipe_no_1(a)		(((a)+1) & (D_IM_B2R_PIPE1+1))
#define ct_im_b2r_check_target_pipe_no_2(a)		(((a)+1) & (D_IM_B2R_PIPE2+1))


struct _CtImB2r3Private
{

};

/*
DECLS
*/


static void ct_im_b2r3_constructor(CtImB2r3 *self) 
{
//	CtImB2r3Private *priv = CT_IM_B2R3_GET_PRIVATE(self);
}

static void ct_im_b2r3_destructor(CtImB2r3 *self) 
{
//	CtImB2r3Private *priv = CT_IM_B2R3_GET_PRIVATE(self);
	self = NULL;
}

/*
IMPL//todo
*/

/*
PUBLIC//todo
*/

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_23: "
kint32 ct_im_b2r3_1_23( CtImB2r3 *self )
{
	T_IM_B2R_OUTBANK_INFO b2r_addr;
	kuint32 loopcnt;
	kuint32 ybw_bank_no;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	if( self->pipeNo == D_IM_B2R_PIPE12 ){
		return D_DDIM_OK;
	}

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < 3; loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));


		switch( loopcnt ) {
			case 0:	// max
				b2r_addr.bank_initial_position = D_IM_B2R_YBW_BANK_3;
				b2r_addr.use_bank_num = D_IM_B2R_YBW_BANK_3;
				for( ybw_bank_no = D_IM_B2R_YBW_BANK_0; ybw_bank_no < D_IM_B2R_YBW_BANK_MAX; ybw_bank_no++ ) {
					b2r_addr.output_addr[ybw_bank_no].rgb.addr_R = (void*)0xFFFFFFFF;
					b2r_addr.output_addr[ybw_bank_no].rgb.addr_G = (void*)0xFFFFFFFF;
					b2r_addr.output_addr[ybw_bank_no].rgb.addr_B = (void*)0xFFFFFFFF;
				}
				break;
			case 1:	// min
				b2r_addr.bank_initial_position = D_IM_B2R_YBW_BANK_0;
				b2r_addr.use_bank_num = D_IM_B2R_YBW_BANK_0;
				for( ybw_bank_no = D_IM_B2R_YBW_BANK_0; ybw_bank_no < D_IM_B2R_YBW_BANK_MAX; ybw_bank_no++ ) {
					b2r_addr.output_addr[ybw_bank_no].rgb.addr_R = (void*)0;
					b2r_addr.output_addr[ybw_bank_no].rgb.addr_G = (void*)0;
					b2r_addr.output_addr[ybw_bank_no].rgb.addr_B = (void*)0;
				}
				break;
			default:
//			case 2:	// indivisual
				b2r_addr.bank_initial_position = D_IM_B2R_YBW_BANK_1;
				b2r_addr.use_bank_num = D_IM_B2R_YBW_BANK_2;
				for( ybw_bank_no = D_IM_B2R_YBW_BANK_0; ybw_bank_no < D_IM_B2R_YBW_BANK_MAX; ybw_bank_no++ ) {
					b2r_addr.output_addr[ybw_bank_no].rgb.addr_R = (void*)0x1FFFFFF0;
					b2r_addr.output_addr[ybw_bank_no].rgb.addr_G = (void*)0x2FFFFFF0;
					b2r_addr.output_addr[ybw_bank_no].rgb.addr_B = (void*)0x3FFFFFF0;
				}
				break;
		}

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Ctrl( self->pipeNo, &gctImB2rCtrlBase );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));

		ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &gctImB2rCtrlSdramInBase );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));

		ercd = Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_addr );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
		Im_B2R_Ctrl( self->pipeNo, &gctImB2rCtrlBase );
		Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &gctImB2rCtrlSdramInBase );
		Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_addr );
#endif

		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( "IO_B2R_P1.YBW.YBWCTL.bit.USEBANK = %u\n",   (kuint32)IO_B2R_P1.YBW.YBWCTL.bit.USEBANK ));
		Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_0_0  = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_0_0 ));
		Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_1_0  = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_1_0 ));
		Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_2_0  = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_2_0 ));
		Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_0_1  = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_0_1 ));
		Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_1_1  = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_1_1 ));
		Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_2_1  = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_2_1 ));
		Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_0_2  = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_0_2 ));
		Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_1_2  = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_1_2 ));
		Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_2_2  = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_2_2 ));
		Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_0_3  = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_0_3 ));
		Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_1_3  = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_1_3 ));
		Ddim_Print(( "IO_B2R_P1.YBW.YBWA.bit.YBWA_2_3  = 0x%x\n", (kuint32)IO_B2R_P1.YBW.YBWA.bit.YBWA_2_3 ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWCTL.bit.USEBANK = %u\n",   (kuint32)IO_B2R_P2.YBW.YBWCTL.bit.USEBANK ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_0_0  = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_0_0 ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_1_0  = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_1_0 ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_2_0  = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_2_0 ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_0_1  = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_0_1 ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_1_1  = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_1_1 ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_2_1  = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_2_1 ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_0_2  = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_0_2 ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_1_2  = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_1_2 ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_2_2  = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_2_2 ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_0_3  = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_0_3 ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_1_3  = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_1_3 ));
		Ddim_Print(( "IO_B2R_P2.YBW.YBWA.bit.YBWA_2_3  = 0x%x\n", (kuint32)IO_B2R_P2.YBW.YBWA.bit.YBWA_2_3 ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );


#ifdef IM_B2R_STATUS_PRINT
		Im_B2R_Print_Status();
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_24: "
kint32 ct_im_b2r3_1_24( CtImB2r3 *self )
{
	T_IM_B2R_RECT b2r_rect_param;
	T_IM_B2R_INADDR_INFO b2r_in_addr;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	kuint32 loopcnt;
	UCHAR bank_index;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	if( self->pipeNo == D_IM_B2R_PIPE12 ){
		return D_DDIM_OK;
	}

	b2r_rect_param.input_size.img_top = 0;
	b2r_rect_param.input_size.img_left = 0;
	b2r_rect_param.input_size.img_width = D_IM_B2R_SRC_IMG_PIXS_WIDTH;
	b2r_rect_param.input_size.img_lines = D_IM_B2R_SRC_IMG_PIXS_LINES;
	b2r_rect_param.output_size.output_global_w = D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U8;

	b2r_in_addr.raw.addr = (void*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP;

	memset( &b2r_out_addr, '\x0', sizeof(b2r_out_addr) );
	b2r_out_addr.bank_initial_position = D_IM_B2R_YBW_BANK_3;
	b2r_out_addr.use_bank_num = D_IM_B2R_YBW_BANK_3;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_R = (void*)(D_IM_B2R_IMG_MEM_OUT_RGB_U8_R_ADDR_TOP + 0x0);
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_G = (void*)(D_IM_B2R_IMG_MEM_OUT_RGB_U8_G_ADDR_TOP + 0x0);
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_B = (void*)(D_IM_B2R_IMG_MEM_OUT_RGB_U8_B_ADDR_TOP + 0x0);
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_1].rgb.addr_R = (void*)(D_IM_B2R_IMG_MEM_OUT_RGB_U8_R_ADDR_TOP + 0x4);
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_1].rgb.addr_G = (void*)(D_IM_B2R_IMG_MEM_OUT_RGB_U8_G_ADDR_TOP + 0x4);
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_1].rgb.addr_B = (void*)(D_IM_B2R_IMG_MEM_OUT_RGB_U8_B_ADDR_TOP + 0x4);
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_2].rgb.addr_R = (void*)(D_IM_B2R_IMG_MEM_OUT_RGB_U8_R_ADDR_TOP + 0x8);
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_2].rgb.addr_G = (void*)(D_IM_B2R_IMG_MEM_OUT_RGB_U8_G_ADDR_TOP + 0x8);
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_2].rgb.addr_B = (void*)(D_IM_B2R_IMG_MEM_OUT_RGB_U8_B_ADDR_TOP + 0x8);
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_3].rgb.addr_R = (void*)(D_IM_B2R_IMG_MEM_OUT_RGB_U8_R_ADDR_TOP + 0xC);
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_3].rgb.addr_G = (void*)(D_IM_B2R_IMG_MEM_OUT_RGB_U8_G_ADDR_TOP + 0xC);
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_3].rgb.addr_B = (void*)(D_IM_B2R_IMG_MEM_OUT_RGB_U8_B_ADDR_TOP + 0xC);

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &gctImB2rCtrlBase );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &gctImB2rCtrlSdramInBase );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Ctrl( self->pipeNo, &gctImB2rCtrlBase );
	Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &gctImB2rCtrlSdramInBase );
	Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
#endif

	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", 0 ));

#ifdef IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "Status\n" ));
	Im_B2R_Print_Status();
#endif

	for( loopcnt = 0; loopcnt < D_IM_B2R_YBW_BANK_MAX; loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

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
		Ddim_Print(( D_IM_B2R_FUNC_NAME "loopcnt = %u\n", loopcnt ));
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
		ercd = Im_B2R_WaitEnd( NULL, flgptn, 60 );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

		ercd = Im_B2R_Get_OutBankIndex( self->pipeNo, &bank_index );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d bank_idx=%u\n", ercd, bank_index ));

		ercd = Im_B2R_Stop( self->pipeNo );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
		Im_B2R_WaitEnd( NULL, flgptn, 60 );
		Im_B2R_Get_OutBankIndex( self->pipeNo, &bank_index );
		Im_B2R_Stop( self->pipeNo );
#endif


#ifdef IM_B2R_STATUS_PRINT
		Im_B2R_Print_Status();
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_25: "
kint32 ct_im_b2r3_1_25( CtImB2r3 *self )
{
	kuint32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

#ifdef CO_MSG_PRINT_ON
	for( loopcnt = D_IM_B2R_YBW_BANK_0; loopcnt < D_IM_B2R_YBW_BANK_MAX; loopcnt++ ) {
		Ddim_Print(( D_IM_B2R_FUNC_NAME "##loop %u\n", loopcnt ));
		ercd = Im_B2R_Set_OutBankIndex( self->pipeNo, loopcnt );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.YBW.YBWBANK.bit.BANKST = %u\n", IO_B2R_P1.YBW.YBWBANK.bit.BANKST ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.YBW.YBWBANK.bit.BANKPS = %u\n", IO_B2R_P1.YBW.YBWBANK.bit.BANKPS ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.YBW.YBWBANK.bit.BANKST = %u\n", IO_B2R_P2.YBW.YBWBANK.bit.BANKST ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.YBW.YBWBANK.bit.BANKPS = %u\n", IO_B2R_P2.YBW.YBWBANK.bit.BANKPS ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
	}
#endif
	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_26: "
kint32 ct_im_b2r3_1_26( CtImB2r3 *self )
{
	kuint32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;

	memset( &b2r_out_addr, '\x0', sizeof(b2r_out_addr) );
	b2r_out_addr.bank_initial_position = D_IM_B2R_YBW_BANK_3;
	b2r_out_addr.use_bank_num = D_IM_B2R_YBW_BANK_3;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_R = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_U8_R_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_G = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_U8_G_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_B = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_U8_B_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_1].rgb.addr_R = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_U8_R_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_1].rgb.addr_G = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_U8_G_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_1].rgb.addr_B = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_U8_B_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_2].rgb.addr_R = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_U8_R_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_2].rgb.addr_G = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_U8_G_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_2].rgb.addr_B = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_U8_B_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_3].rgb.addr_R = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_U8_R_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_3].rgb.addr_G = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_U8_G_ADDR_TOP;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_3].rgb.addr_B = (void*)D_IM_B2R_IMG_MEM_OUT_RGB_U8_B_ADDR_TOP;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	for( loopcnt = D_IM_B2R_YBW_BANK_0; loopcnt < D_IM_B2R_YBW_BANK_MAX; loopcnt++ ) {
		Ddim_Print(( D_IM_B2R_FUNC_NAME "##loop %u\n", loopcnt ));

#ifdef CO_DEBUG_ON_PC
		if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
			IO_B2R_P1.YBW.YBWBANK.bit.BANKSTS = loopcnt;
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			IO_B2R_P2.YBW.YBWBANK.bit.BANKSTS = loopcnt;
		}
#endif //CO_DEBUG_ON_PC

		ercd = Im_B2R_Inc_OutBankIndex( self->pipeNo );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.YBW.YBWBANK.bit.BANKPS = %u\n", IO_B2R_P1.YBW.YBWBANK.bit.BANKPS ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.YBW.YBWBANK.bit.BANKST = %u\n", IO_B2R_P1.YBW.YBWBANK.bit.BANKST ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.YBW.YBWBANK.bit.BANKPS = %u\n", IO_B2R_P2.YBW.YBWBANK.bit.BANKPS ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.YBW.YBWBANK.bit.BANKST = %u\n", IO_B2R_P2.YBW.YBWBANK.bit.BANKST ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
	}
#endif


	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_27: "
kint32 ct_im_b2r3_1_27( CtImB2r3 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlBase;
	T_IM_B2R_CTRL_SDRAM_INPUT b2r_ctrl_sdram_in = gctImB2rCtrlSdramInBase;
	T_IM_B2R_RECT b2r_rect_param;
	T_IM_B2R_INADDR_INFO b2r_in_addr = {
		.raw.addr = (void*)0x10000000,		// RAW
	};
	const UCHAR input_dtype[4] = {
		D_IM_B2R_STL_DTYP_PACK8,
		D_IM_B2R_STL_DTYP_PACK10,
		D_IM_B2R_STL_DTYP_PACK12,
		D_IM_B2R_STL_DTYP_PACK16
	};

#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));




	for( loopcnt = 0; loopcnt < 4; loopcnt++ ) {
		Ddim_Print(( "## %u\n", loopcnt ));

		b2r_ctrl_sdram_in.input_dtype = input_dtype[loopcnt];

		b2r_rect_param.input_size.img_top = 180;
		b2r_rect_param.input_size.img_left = 320;
		b2r_rect_param.input_size.img_width = 1920 - b2r_rect_param.input_size.img_left *2;
		b2r_rect_param.input_size.img_lines = 1080 - b2r_rect_param.input_size.img_top *2;
		b2r_rect_param.output_size.output_global_w = 0x1000;

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));

		ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));

		ercd = Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));

		ercd = Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
#else
		Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
		Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &b2r_ctrl_sdram_in );
		Im_B2R_Set_Rect( self->pipeNo, &gctImB2rCtrlSdramInBase );
		Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
#endif

		ct_im_b2r1_print_b2r_ctrl_modesdraminput_reg();
		ct_im_b2r1_print_rect_reg();

#ifdef IM_B2R_STATUS_PRINT
		Im_B2R_Print_Status();
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_28: "
kint32 ct_im_b2r3_1_28( CtImB2r3 *self )
{
	T_IM_B2R_RECT b2r_rect_param;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	if( self->pipeNo == D_IM_B2R_PIPE12 ){
		return D_DDIM_OK;
	}

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	ercd = ct_im_b2r3_1_27( self );
	if( ercd != D_DDIM_OK ) {
		return ercd;
	}

#ifdef CO_MSG_PRINT_ON
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		ercd = Im_B2R_Get_Rect_Param( 0, &b2r_rect_param );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));

		Ddim_Print(( "###self->pipeNo      = %u\n", 0 ));
		Ddim_Print(( "img_top         = %u\n", b2r_rect_param.input_size.img_top ));
		Ddim_Print(( "img_left        = %u\n", b2r_rect_param.input_size.img_left ));
		Ddim_Print(( "img_width       = %u\n", b2r_rect_param.input_size.img_width ));
		Ddim_Print(( "img_lines       = %u\n", b2r_rect_param.input_size.img_lines ));
		Ddim_Print(( "output_global_w = %u\n", b2r_rect_param.output_size.output_global_w ));
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		ercd = Im_B2R_Get_Rect_Param( 1, &b2r_rect_param );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));

		Ddim_Print(( "###self->pipeNo      = %u\n", 1 ));
		Ddim_Print(( "img_top         = %u\n", b2r_rect_param.input_size.img_top ));
		Ddim_Print(( "img_left        = %u\n", b2r_rect_param.input_size.img_left ));
		Ddim_Print(( "img_width       = %u\n", b2r_rect_param.input_size.img_width ));
		Ddim_Print(( "img_lines       = %u\n", b2r_rect_param.input_size.img_lines ));
		Ddim_Print(( "output_global_w = %u\n", b2r_rect_param.output_size.output_global_w ));
	}
#else
	Im_B2R_Get_Rect_Param( self->pipeNo, &b2r_rect_param );
#endif

#ifdef IM_B2R_STATUS_PRINT
	Im_B2R_Print_Status();
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_29: "
kint32 ct_im_b2r3_1_29( CtImB2r3 *self )
{
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlBase;
	T_IM_B2R_RECT b2r_rect_param;
	T_IM_B2R_INADDR_INFO b2r_in_addr;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	T_IM_B2R_OUTADDR_INFO out_addr_info;
	kuint32 loopcnt;
	UCHAR bank_index;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
	const char dumpmsg[] = "%d idx=%u addr y=0x%05lx cb=0x%05lx cr=0x%05lx\n";
#endif

	b2r_rect_param.input_size.img_top = 0;
	b2r_rect_param.input_size.img_left = 0;
	b2r_rect_param.input_size.img_width = D_IM_B2R_SRC_IMG_PIXS_WIDTH;
	b2r_rect_param.input_size.img_lines = D_IM_B2R_SRC_IMG_PIXS_LINES;
	b2r_rect_param.output_size.output_global_w = D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U8;

	b2r_in_addr.raw.addr = (void*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP;

	memset( &b2r_out_addr, '\x0', sizeof(b2r_out_addr) );
	b2r_out_addr.bank_initial_position = D_IM_B2R_YBW_BANK_3;
	b2r_out_addr.use_bank_num = D_IM_B2R_YBW_BANK_3;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_R = (void*)0x100;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_G = (void*)0x200;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_B = (void*)0x300;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_1].rgb.addr_R = (void*)0x400;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_1].rgb.addr_G = (void*)0x500;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_1].rgb.addr_B = (void*)0x600;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_2].rgb.addr_R = (void*)0x700;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_2].rgb.addr_G = (void*)0x800;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_2].rgb.addr_B = (void*)0x900;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_3].rgb.addr_R = (void*)0xa00;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_3].rgb.addr_G = (void*)0xb00;
	b2r_out_addr.output_addr[D_IM_B2R_YBW_BANK_3].rgb.addr_B = (void*)0xc00;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &gctImB2rCtrlSdramInBase );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
	Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &gctImB2rCtrlSdramInBase );
	Im_B2R_Set_Rect( self->pipeNo, &b2r_rect_param );
	Im_B2R_Set_InAddr_Info( self->pipeNo, &b2r_in_addr );
	Im_B2R_Set_OutBankInfo( self->pipeNo, &b2r_out_addr );
#endif

	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", 0 ));

#ifdef IM_B2R_STATUS_PRINT
	Ddim_Print(( D_IM_B2R_FUNC_NAME "Status\n" ));
	Im_B2R_Print_Status();
#endif

	for( loopcnt = 0; loopcnt < D_IM_B2R_YBW_BANK_MAX; loopcnt++ ) {
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
		Ddim_Print(( D_IM_B2R_FUNC_NAME "loopcnt = %u\n", loopcnt ));
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
		ercd = Im_B2R_WaitEnd( NULL, flgptn, 60 );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

		if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
			ercd = Im_B2R_Get_Latest_OutAddr( 0, &bank_index, &out_addr_info );
			Ddim_Print(( dumpmsg,
						ercd,
						bank_index,
						(ULONG)out_addr_info.rgb.addr_R,
						(ULONG)out_addr_info.rgb.addr_G,
						(ULONG)out_addr_info.rgb.addr_B
						));
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			ercd = Im_B2R_Get_Latest_OutAddr( 1, &bank_index, &out_addr_info );
			Ddim_Print(( dumpmsg,
						ercd,
						bank_index,
						(ULONG)out_addr_info.rgb.addr_R,
						(ULONG)out_addr_info.rgb.addr_G,
						(ULONG)out_addr_info.rgb.addr_B
						));
		}

		ercd = Im_B2R_Stop( self->pipeNo );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
		Im_B2R_WaitEnd( NULL, flgptn, 60 );
		Im_B2R_Get_OutBankIndex( self->pipeNo, &bank_index );
		Im_B2R_Stop( self->pipeNo );
#endif


#ifdef IM_B2R_STATUS_PRINT
//		Im_B2R_Print_Status();
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_30: "
kint32 ct_im_b2r3_1_30( CtImB2r3 *self )
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Set_FrameStop( self->pipeNo, 1 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.YBR.DINCTL.bit.FRMSTP = %u\n", IO_B2R_P1.YBR.DINCTL.bit.FRMSTP ));
	Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.YBR.DINCTL.bit.FRMSTP = %u\n", IO_B2R_P2.YBR.DINCTL.bit.FRMSTP ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
	ercd = Im_B2R_Set_FrameStop( self->pipeNo, 0 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.YBR.DINCTL.bit.FRMSTP = %u\n", IO_B2R_P1.YBR.DINCTL.bit.FRMSTP ));
	Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.YBR.DINCTL.bit.FRMSTP = %u\n", IO_B2R_P2.YBR.DINCTL.bit.FRMSTP ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
#endif


	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_31: "
kint32 ct_im_b2r3_1_31( CtImB2r3 *self )
{
#ifdef CO_MSG_PRINT_ON
	BOOL busy_state;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 3;
		Im_B2R_Get_YbrBusy( self->pipeNo, &busy_state );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "pipe1:busy = %u\n", busy_state ));
		IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 2;
		Im_B2R_Get_YbrBusy( self->pipeNo, &busy_state );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "pipe1:busy = %u\n", busy_state ));
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 3;
		Im_B2R_Get_YbrBusy( self->pipeNo, &busy_state );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "pipe2:busy = %u\n", busy_state ));
		IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 2;
		Im_B2R_Get_YbrBusy( self->pipeNo, &busy_state );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "pipe2:busy = %u\n", busy_state ));
	}
#endif


	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_32: "
kint32 ct_im_b2r3_1_32( CtImB2r3 *self )
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
	USHORT ring_pixs;
#endif
	T_IM_B2R_CTRL b2r_ctrl = gctImB2rCtrlBase;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

	b2r_ctrl.cia_bypass = 0;
	b2r_ctrl.cia_padding = 0;

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Ctrl( self->pipeNo, &b2r_ctrl );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "%d\n", ercd ));
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		ercd = Im_B2R_Get_HRingPixs( 0, &ring_pixs );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "ring = %u %d\n", ring_pixs, ercd ));
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		ercd = Im_B2R_Get_HRingPixs( 1, &ring_pixs );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "ring = %u %d\n", ring_pixs, ercd ));
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_33: "
kint32 ct_im_b2r3_1_33( CtImB2r3 *self )
{
#ifdef CO_MSG_PRINT_ON
	kuint32 err_factor;
	kint32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		IO_B2R_P1.YBR.DINERR.bit.TRMER = 1;
		IO_B2R_P1.YBR.DINERR.bit.HPDDER = 1;
		IO_B2R_P1.YBR.DINERR.bit.WAITER = 1;
		ercd = Im_B2R_Get_YBR_Error_Factor( 0, &err_factor );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "error factor = %x %d\n", err_factor, ercd ));
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		IO_B2R_P2.YBR.DINERR.bit.TRMER = 1;
		IO_B2R_P2.YBR.DINERR.bit.HPDDER = 1;
		IO_B2R_P2.YBR.DINERR.bit.WAITER = 1;
		ercd = Im_B2R_Get_YBR_Error_Factor( 1, &err_factor );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "error factor = %x %d\n", err_factor, ercd ));
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_34: "
kint32 ct_im_b2r3_1_34( CtImB2r3 *self )
{
	T_IM_B2R_CTRL_TRIMMING b2r_ctrl_trimming[] = {
		[0] = {	// max
			.trimming_enable = 1,
			.start_x = 0x1FFF,
			.width = 0x1FFF,
			.start_y = 0x3FFF,
			.lines = 0x3FFF,
		},
		[1] = {	// min
			.trimming_enable = 0,
			.start_x = 0,
			.width = 0,
			.start_y = 0,
			.lines = 0,
		},
	};
	kuint32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


#ifdef CO_MSG_PRINT_ON
	for( loopcnt = 0; loopcnt < (sizeof(b2r_ctrl_trimming) / sizeof(b2r_ctrl_trimming[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));
		ercd = Im_B2R_Ctrl_Trimming( self->pipeNo, &b2r_ctrl_trimming[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.YBW.YBWMD.bit.TRMEN     = %u\n", IO_B2R_P1.YBW.YBWMD.bit.TRMEN ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.YBW.YBWTRMH.bit.TRMHSTA = %u\n", IO_B2R_P1.YBW.YBWTRMH.bit.TRMHSTA ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.YBW.YBWTRMH.bit.TRMHSIZ = %u\n", IO_B2R_P1.YBW.YBWTRMH.bit.TRMHSIZ ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.YBW.YBWTRMV.bit.TRMVSTA = %u\n", IO_B2R_P1.YBW.YBWTRMV.bit.TRMVSTA ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.YBW.YBWTRMV.bit.TRMVSIZ = %u\n", IO_B2R_P1.YBW.YBWTRMV.bit.TRMVSIZ ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.YBW.YBWMD.bit.TRMEN     = %u\n", IO_B2R_P2.YBW.YBWMD.bit.TRMEN ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.YBW.YBWTRMH.bit.TRMHSTA = %u\n", IO_B2R_P2.YBW.YBWTRMH.bit.TRMHSTA ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.YBW.YBWTRMH.bit.TRMHSIZ = %u\n", IO_B2R_P2.YBW.YBWTRMH.bit.TRMHSIZ ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.YBW.YBWTRMV.bit.TRMVSTA = %u\n", IO_B2R_P2.YBW.YBWTRMV.bit.TRMVSTA ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.YBW.YBWTRMV.bit.TRMVSIZ = %u\n", IO_B2R_P2.YBW.YBWTRMV.bit.TRMVSIZ ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_35: "
kint32 ct_im_b2r3_1_35( CtImB2r3 *self )
{
#ifdef CO_DEBUG_ON_PC
	struct t_ct_im_b2r_1_35 {
		USHORT src_tbl[D_IM_B2R_TABLE_MAX_BAYER_DEKNEE];
	};
	struct t_ct_im_b2r_1_35 tbl_body;
	struct t_ct_im_b2r_1_35* tbl = &tbl_body;
#else //!CO_DEBUG_ON_PC
	struct t_ct_im_b2r_1_35 {
		USHORT src_tbl[D_IM_B2R_TABLE_MAX_BAYER_DEKNEE];
	}* tbl = (struct t_ct_im_b2r_1_35*)D_IM_B2R_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	kuint32			loopcnt;
	kuint32			loopcnt2;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	const char errmsg[] = "%u unmatch\n";

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < 3; loopcnt++ ) {
		switch( loopcnt ) {
			default:	// max
//			case 0:
				for( loopcnt2 = 0; loopcnt2 < D_IM_B2R_TABLE_MAX_BAYER_DEKNEE; loopcnt2++ ) {
					tbl->src_tbl[loopcnt2] = 0xFFF;
				}
				break;
			case 1:	// min
				for( loopcnt2 = 0; loopcnt2 < D_IM_B2R_TABLE_MAX_BAYER_DEKNEE; loopcnt2++ ) {
					tbl->src_tbl[loopcnt2] = 0;
				}
				break;
			case 2:	// indvisual
				for( loopcnt2 = 0; loopcnt2 < D_IM_B2R_TABLE_MAX_BAYER_DEKNEE; loopcnt2++ ) {
					tbl->src_tbl[loopcnt2] = 0xFFF - loopcnt2;
				}
				break;
		}


#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Set_Deknee_Table( self->pipeNo, tbl->src_tbl );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Hclk( self->pipeNo );
		Im_B2R_Set_DekneeAccessEnable( self->pipeNo, D_IM_B2R_ENABLE_ON, D_IM_B2R_WAIT_ON );
		if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
			for( loopcnt2 = 0; loopcnt2 < D_IM_B2R_TABLE_MAX_BAYER_DEKNEE; loopcnt2++ ) {
				if( IO_B2R_TBL_P1.DKNTBL.hword[loopcnt2] != tbl->src_tbl[loopcnt2] ) {
					Ddim_Print(( errmsg, loopcnt2 ));
				}
			}
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			for( loopcnt2 = 0; loopcnt2 < D_IM_B2R_TABLE_MAX_BAYER_DEKNEE; loopcnt2++ ) {
				if( IO_B2R_TBL_P2.DKNTBL.hword[loopcnt2] != tbl->src_tbl[loopcnt2] ) {
					Ddim_Print(( errmsg, loopcnt2 ));
				}
			}
		}
		Im_B2R_Set_DekneeAccessEnable( self->pipeNo, D_IM_B2R_ENABLE_OFF, D_IM_B2R_WAIT_OFF );
		Im_B2R_Off_Hclk( self->pipeNo );
#else
		Im_B2R_Set_Deknee_Table( self->pipeNo, tbl->src_tbl );
#endif
	}


	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_36: "
kint32 ct_im_b2r3_1_36( CtImB2r3 *self )
{
	UCHAR access_enable[] = {
		[0] = 1,	// max
		[1] = 0,	// min
	};
	kuint32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	Im_B2R_Init( D_IM_B2R_PIPE12 );
	Ddim_Print(( "Initial value\n" ));
	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	Ddim_Print(( "IO_B2R_P1.B2R_CMN.RAMAEN.word                  = 0x%lx\n", IO_B2R_P1.B2R_CMN.RAMAEN.word ));
	Ddim_Print(( "IO_B2R_P1.B2R_CMN.RAMAEN.bit.RAMAEN_BAY_DEKNEE = %u\n",    IO_B2R_P1.B2R_CMN.RAMAEN.bit.RAMAEN_BAY_DEKNEE ));
	Ddim_Print(( "IO_B2R_P2.B2R_CMN.RAMAEN.word                  = 0x%lx\n", IO_B2R_P2.B2R_CMN.RAMAEN.word ));
	Ddim_Print(( "IO_B2R_P2.B2R_CMN.RAMAEN.bit.RAMAEN_BAY_DEKNEE = %u\n",    IO_B2R_P2.B2R_CMN.RAMAEN.bit.RAMAEN_BAY_DEKNEE ));
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
#endif

	for( loopcnt = 0; loopcnt < (sizeof(access_enable) / sizeof(access_enable[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Set_DekneeAccessEnable( self->pipeNo, access_enable[loopcnt], D_IM_B2R_WAIT_ON );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
		Ddim_Print(( "IO_B2R_P1.B2R_CMN.RAMAEN.word                  = 0x%lx\n", IO_B2R_P1.B2R_CMN.RAMAEN.word ));
		Ddim_Print(( "IO_B2R_P1.B2R_CMN.RAMAEN.bit.RAMAEN_BAY_DEKNEE = %u\n",    IO_B2R_P1.B2R_CMN.RAMAEN.bit.RAMAEN_BAY_DEKNEE ));
		Ddim_Print(( "IO_B2R_P2.B2R_CMN.RAMAEN.word                  = 0x%lx\n", IO_B2R_P2.B2R_CMN.RAMAEN.word ));
		Ddim_Print(( "IO_B2R_P2.B2R_CMN.RAMAEN.bit.RAMAEN_BAY_DEKNEE = %u\n",    IO_B2R_P2.B2R_CMN.RAMAEN.bit.RAMAEN_BAY_DEKNEE ));
		Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
#endif
	}


	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r3_1_37: "
kint32 ct_im_b2r3_1_37( CtImB2r3 *self )
{
#ifdef CO_DEBUG_ON_PC
	struct t_ct_im_b2r_1_37 {
		UCHAR src_tbl[D_IM_B2R_TABLE_MAX_RGB_KNEE];
	};
	struct t_ct_im_b2r_1_37 tbl_body;
	struct t_ct_im_b2r_1_37* tbl = &tbl_body;
#else //!CO_DEBUG_ON_PC
	struct t_ct_im_b2r_1_37 {
		UCHAR src_tbl[D_IM_B2R_TABLE_MAX_RGB_KNEE];
	}* tbl = (struct t_ct_im_b2r_1_37*)D_IM_B2R_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	kuint32			loopcnt;
	E_B2R_RGBTBL	loopcnt2;
	kuint32			loopcnt3;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	const char errmsg[] = "%u[%u] unmatch\n";

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < 3; loopcnt++ ) {
		switch( loopcnt ) {
			default:	// max
//			case 0:
				for( loopcnt3 = 0; loopcnt3 < D_IM_B2R_TABLE_MAX_RGB_KNEE; loopcnt3++ ) {
					tbl->src_tbl[loopcnt3] = 0xFF;
				}
				break;
			case 1:	// min
				for( loopcnt3 = 0; loopcnt3 < D_IM_B2R_TABLE_MAX_RGB_KNEE; loopcnt3++ ) {
					tbl->src_tbl[loopcnt3] = 0;
				}
				break;
			case 2:	// indvisual
				for( loopcnt3 = 0; loopcnt3 < D_IM_B2R_TABLE_MAX_RGB_KNEE; loopcnt3++ ) {
					tbl->src_tbl[loopcnt3] = 0xFF - loopcnt3;
				}
				break;
		}

		for( loopcnt2 = (E_B2R_RGBTBL)0; loopcnt2 < E_B2R_RGBTBL_MAX; loopcnt2++ ) {
			Ddim_Print(( "** %u - %u\n", loopcnt, loopcnt2 ));


#ifdef CO_MSG_PRINT_ON
			ercd = Im_B2R_Set_Knee_Table( self->pipeNo, loopcnt2, tbl->src_tbl );
			Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
			Im_B2R_On_Hclk( self->pipeNo );
			Im_B2R_Set_RGB_KneeAccessEnable( self->pipeNo, D_IM_B2R_ENABLE_ON, D_IM_B2R_WAIT_ON );
			switch( loopcnt2 ) {
				default:
//				case E_B2R_RGBTBL_R:
					if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_B2R_TABLE_MAX_RGB_KNEE; loopcnt3++ ) {
							if( IO_B2R_TBL_P1.KNETBLR.byte[loopcnt3] != tbl->src_tbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_B2R_TABLE_MAX_RGB_KNEE; loopcnt3++ ) {
							if( IO_B2R_TBL_P2.KNETBLR.byte[loopcnt3] != tbl->src_tbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					break;
				case E_B2R_RGBTBL_G:
					if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_B2R_TABLE_MAX_RGB_KNEE; loopcnt3++ ) {
							if( IO_B2R_TBL_P1.KNETBLG.byte[loopcnt3] != tbl->src_tbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_B2R_TABLE_MAX_RGB_KNEE; loopcnt3++ ) {
							if( IO_B2R_TBL_P2.KNETBLG.byte[loopcnt3] != tbl->src_tbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					break;
				case E_B2R_RGBTBL_B:
					if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_B2R_TABLE_MAX_RGB_KNEE; loopcnt3++ ) {
							if( IO_B2R_TBL_P1.KNETBLB.byte[loopcnt3] != tbl->src_tbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_B2R_TABLE_MAX_RGB_KNEE; loopcnt3++ ) {
							if( IO_B2R_TBL_P2.KNETBLB.byte[loopcnt3] != tbl->src_tbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					break;
			}
			Im_B2R_Set_RGB_KneeAccessEnable( self->pipeNo, D_IM_B2R_ENABLE_OFF, D_IM_B2R_WAIT_OFF );
			Im_B2R_Off_Hclk( self->pipeNo );
#else
			Im_B2R_Set_Knee_Table( self->pipeNo, loopcnt2, tbl->src_tbl );
#endif
		}
	}


	return D_DDIM_OK;
}


CtImB2r3* ct_im_b2r3_new(void) 
{
    CtImB2r3 *self = k_object_new_with_private(CT_TYPE_IM_B2R3, sizeof(CtImB2r3Private));
    return self;
}
