/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-08
*@author              :liudong
*@brief               :CtImB2r10类
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
#include "ctimb2r1.h"

#include "ctimb2r10.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImB2r10, ct_im_b2r10);
#define CT_IM_B2R10_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImB2r10Private,CT_TYPE_IM_B2R10))


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define ct_im_b2r_check_target_pipe_no_1(a)		(((a)+1) & (D_IM_B2R_PIPE1+1))
#define ct_im_b2r_check_target_pipe_no_2(a)		(((a)+1) & (D_IM_B2R_PIPE2+1))

struct _CtImB2r10Private
{

};

/*
DECLS
*/


static void ct_im_b2r10_constructor(CtImB2r10 *self) 
{
//	CtImB2r10Private *priv = CT_IM_B2R10_GET_PRIVATE(self);
}

static void ct_im_b2r10_destructor(CtImB2r10 *self) 
{
//	CtImB2r10Private *priv = CT_IM_B2R10_GET_PRIVATE(self);
	self = 	NULL;
}

/*
IMPL//todo
*/

/*
PUBLIC//todo
*/

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r10_2_1: "
kint32 ct_im_b2r10_2_1( CtImB2r10 *self )
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

#ifdef CO_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 2;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 2;
	}
#endif	//CO_DEBUG_ON_PC

	b2r_rect_param.input_size.img_top = 0;
	b2r_rect_param.input_size.img_left = 0;
	b2r_rect_param.input_size.img_width = D_IM_B2R_SRC_IMG_PIXS_WIDTH;
	b2r_rect_param.input_size.img_lines = D_IM_B2R_SRC_IMG_PIXS_LINES;
	b2r_rect_param.output_size.output_global_w = D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U8;

	b2r_in_addr.raw.addr = (void*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP;

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
#ifdef CO_DEBUG_ON_PC
		if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
			IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 3;
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 3;
		}
#endif	//CO_DEBUG_ON_PC

		ercd = Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &gctImB2rCtrlSdramInRaw16bit );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
		Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
#ifdef CO_DEBUG_ON_PC
		if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
			IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 3;
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 3;
		}
#endif	//CO_DEBUG_ON_PC
		Im_B2R_Ctrl_ModeSDRAMInput( self->pipeNo, &gctImB2rCtrlSdramInBase );
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
			ercd = Im_B2R_Get_OutBankIndex( 0, &bank_index );
			Ddim_Print(( D_IM_B2R_FUNC_NAME "%d bank_idx=%u\n", ercd, bank_index ));
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			ercd = Im_B2R_Get_OutBankIndex( 1, &bank_index );
			Ddim_Print(( D_IM_B2R_FUNC_NAME "%d bank_idx=%u\n", ercd, bank_index ));
		}

		ercd = Im_B2R_Stop( self->pipeNo );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#ifdef CO_DEBUG_ON_PC
		if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
			IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 2;
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 2;
		}
#endif	//CO_DEBUG_ON_PC
#else
		Im_B2R_WaitEnd( NULL, flgptn, 60 );
		Im_B2R_Get_OutBankIndex( self->pipeNo, &bank_index );
		Im_B2R_Stop( self->pipeNo );
#ifdef CO_DEBUG_ON_PC
		if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
			IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 2;
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 2;
		}
#endif	//CO_DEBUG_ON_PC
#endif


#ifdef IM_B2R_STATUS_PRINT
		Im_B2R_Print_Status();
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r10_2_2: "
kint32 ct_im_b2r10_2_2( CtImB2r10 *self )
{
	T_IM_B2R_RECT b2r_rect_param;
	T_IM_B2R_INADDR_INFO b2r_in_addr;
	T_IM_B2R_OUTBANK_INFO b2r_out_addr;
	kuint32 loopcnt;
	UCHAR bank_index;
	DDIM_USER_FLGPTN flgptn = 0;
	T_IM_B2R_CTRL_B2B_DIRECT b2r_ctrl_b2b_direct[] = {
		[0] = {	// max
			.even_line_start_timming = 0x3FF,
			.frame_stop = 1,
		},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

#ifdef CO_DEBUG_ON_PC
	if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
		IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 2;
	}
	if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
		IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 2;
	}
#endif	//CO_DEBUG_ON_PC
	b2r_rect_param.input_size.img_top = 0;
	b2r_rect_param.input_size.img_left = 0;
	b2r_rect_param.input_size.img_width = D_IM_B2R_SRC_IMG_PIXS_WIDTH;
	b2r_rect_param.input_size.img_lines = D_IM_B2R_SRC_IMG_PIXS_LINES;
	b2r_rect_param.output_size.output_global_w = D_IM_B2R_DST_IMG_GLOBAL_WIDTH_RGB_U8;

	b2r_in_addr.raw.addr = (void*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP;

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
#ifdef CO_DEBUG_ON_PC
		if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
			IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 3;
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 3;
		}
#endif	//CO_DEBUG_ON_PC

		ercd = Im_B2R_Ctrl_ModeB2BDirect( self->pipeNo, &b2r_ctrl_b2b_direct[0] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#else
		Im_B2R_Start( self->pipeNo, D_IM_B2R_START_WITH_YBW );
#ifdef CO_DEBUG_ON_PC
		if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
			IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 3;
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 3;
		}
#endif	//CO_DEBUG_ON_PC
		Im_B2R_Ctrl_ModeB2BDirect( self->pipeNo, &b2r_ctrl_b2b_direct[0] );
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
			ercd = Im_B2R_Get_OutBankIndex( 0, &bank_index );
			Ddim_Print(( D_IM_B2R_FUNC_NAME "%d bank_idx=%u\n", ercd, bank_index ));
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			ercd = Im_B2R_Get_OutBankIndex( 1, &bank_index );
			Ddim_Print(( D_IM_B2R_FUNC_NAME "%d bank_idx=%u\n", ercd, bank_index ));
		}

		ercd = Im_B2R_Stop( self->pipeNo );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
#ifdef CO_DEBUG_ON_PC
		if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
			IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 2;
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 2;
		}
#endif	//CO_DEBUG_ON_PC
#else
		Im_B2R_WaitEnd( NULL, flgptn, 60 );
		Im_B2R_Get_OutBankIndex( self->pipeNo, &bank_index );
		Im_B2R_Stop( self->pipeNo );
#ifdef CO_DEBUG_ON_PC
		if( ct_im_b2r_check_target_pipe_no_1( self->pipeNo ) ){
			IO_B2R_P1.YBR.YBRTRG.bit.YBRTRG = 2;
		}
		if( ct_im_b2r_check_target_pipe_no_2( self->pipeNo ) ){
			IO_B2R_P2.YBR.YBRTRG.bit.YBRTRG = 2;
		}
#endif	//CO_DEBUG_ON_PC
#endif


#ifdef IM_B2R_STATUS_PRINT
		Im_B2R_Print_Status();
#endif
	}

	return D_DDIM_OK;
}


CtImB2r10* ct_im_b2r10_new(void) 
{
    CtImB2r10 *self = k_object_new_with_private(CT_TYPE_IM_B2R10, sizeof(CtImB2r10Private));
    return self;
}
