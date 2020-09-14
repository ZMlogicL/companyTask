/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :唐萍萍
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/

#include <string.h>
//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
//#endif
#include "dd_arm.h"

#include "jdsb2r.h"
//#include "imrdma.h"
#include"imb2r.h"
#include"imb2r1.h"
#include "imb2r2.h"
#include"imb2r3.h"
#include "imb2r4.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImB2r2, im_b2r2);
#define IM_B2R2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImB2r2Private, IM_TYPE_B2R2))

struct _ImB2r2Private
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/

#ifdef D_IM_B2R_DEBUG_ON_PC
volatile UCHAR  gImB2rMacroFakeFinish[ImB2r1_D_IM_B2R_PIPE_COUNT] = {0,0};
#endif

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
static UCHAR imB2rIsActFb2r( UCHAR pipe_no );

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/

static void im_b2r2_constructor(ImB2r2 *self)
{
	//ImB2r2Private *priv = IM_B2R2_GET_PRIVATE(self);
}

static void im_b2r2_destructor(ImB2r2 *self)
{
	//ImB2r2Private *priv = IM_B2R2_GET_PRIVATE(self);
}

/* Is F_B2R active
 */
static UCHAR imB2rIsActFb2r( UCHAR pipe_no )
{
	UCHAR t_b2r_enable;
	ImB2r2*	imB2r2=im_b2r2_get();

	if( pipe_no >= ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Print(( "imB2rIsActFb2r:pipe_no err\n" ));
		return 0;
	}

	Im_B2R_On_Pclk(pipe_no);
	t_b2r_enable = (im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.CNTL.bit.TRG != ImB2r1_D_IM_B2R_FB2RTRG_IDLE)?(ImB2r_D_IM_B2R_ENABLE_ON):(ImB2r_D_IM_B2R_ENABLE_OFF);
	Im_B2R_Off_Pclk(pipe_no);

	return t_b2r_enable;
}

/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------

/* B2R Control (SDRAM input mode control)
 */
INT32 Im_B2R_Ctrl_ModeSDRAMInput( UCHAR pipe_no, const T_IM_B2R_CTRL_SDRAM_INPUT* const b2r_ctrl_sdram_input )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( b2r_ctrl_sdram_input == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Ctrl_ModeSDRAMInput error. b2r_ctrl_sdram_input = NULL\n"));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Ctrl_ModeSDRAMInput error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_b2r_get_loop_val( pipe_no, &loop_sta, &loop_end );

	Im_B2R_On_Pclk( pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBR.YBRTRG.bit.YBRTRG != ImB2r1_D_IM_B2R_YBRTRG_IDLE ){
#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
			Ddim_Print(( "Im_B2R_Ctrl_ModeSDRAMInput error. PIPE%d YBR busy\n", loop_cnt ));
#endif
			Im_B2R_Off_Pclk( pipe_no );
			return ImB2r_D_IM_B2R_MACRO_BUSY;
		}
	}

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).inputDtype      = b2r_ctrl_sdram_input->input_dtype;
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).topOffset       = b2r_ctrl_sdram_input->top_offset;
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).inputGlobal     = b2r_ctrl_sdram_input->input_global;
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).videoPhotoMode = ImB2r1_D_IM_B2R_MODE_SDRAM_INPUT;
	}

	// YBCH
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBRAXMD.bit.YBRBL       = b2r_ctrl_sdram_input->burst_length;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBRREQMSK.bit.YBRREQMSK = b2r_ctrl_sdram_input->read_request_mask;

	// B2R_CMN
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.DINSEL.bit.B2BDIN = ImB2r1_D_IM_B2R_MODE_SDRAM_INPUT;

	// YBR
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRCTL.bit.YBRDTYP    = b2r_ctrl_sdram_input->input_dtype;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRDEF.bit.YBRDEF     = b2r_ctrl_sdram_input->input_global;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRHBLNK.bit.YBRHBLNK = b2r_ctrl_sdram_input->line_space;

	Im_B2R_Off_Pclk( pipe_no );
	ImB2r1_IM_B2R_DSB();

	return D_DDIM_OK;
}

/* B2R Control (B2B direct connection mode control)
 */
INT32 Im_B2R_Ctrl_ModeB2BDirect( UCHAR pipe_no, const T_IM_B2R_CTRL_B2B_DIRECT* const b2r_ctrl_b2b_direct )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( b2r_ctrl_b2b_direct == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Ctrl_ModePRODirect error. b2r_ctrl_b2b_direct = NULL\n"));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Ctrl_ModeB2BDirect error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_b2r_get_loop_val( pipe_no, &loop_sta, &loop_end );

	Im_B2R_On_Pclk( pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBR.YBRTRG.bit.YBRTRG != ImB2r1_D_IM_B2R_YBRTRG_IDLE ){
#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
			Ddim_Print(( "Im_B2R_Ctrl_ModeB2BDirect error. PIPE%d YBR busy\n", loop_cnt ));
#endif
			Im_B2R_Off_Pclk( pipe_no );
			return ImB2r_D_IM_B2R_MACRO_BUSY;
		}
	}

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.DINELS.bit.DINELS     = b2r_ctrl_b2b_direct->even_line_start_timming;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.DINCTL.bit.FRMSTP     = b2r_ctrl_b2b_direct->frame_stop;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.DINSEL.bit.B2BDIN = ImB2r1_D_IM_B2R_MODE_B2B_DIRECT;
	Im_B2R_Off_Pclk( pipe_no );
	ImB2r1_IM_B2R_DSB();

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).videoPhotoMode = ImB2r1_D_IM_B2R_MODE_B2B_DIRECT;
	}

	return D_DDIM_OK;
}

/* Get Horizontal ring pixel padding number
 */
INT32 Im_B2R_Get_HRingPixs( UCHAR pipe_no, USHORT* const ring_pixs )
{
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( ring_pixs == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Get_HRingPixs error. ring_pixs = NULL\n"));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no >= ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_HRingPixs error. pipe_no>=ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*ring_pixs = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).ringPixsInfo.ringPixs;

	return D_DDIM_OK;
}

/* Restart B2R process when ybw_continue_start_enable equal ImB2r_D_IM_B2R_ENABLE_OFF.
 */
INT32 Im_B2R_ContStart( UCHAR pipe_no )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_ContStart error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_b2r_get_loop_val( pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).wasStarted == ImB2r1_D_IM_B2R_FALSE ) {
			return D_DDIM_OK;
		}
	}

	// P-clock control
#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_ContStart on pclk\n" ));
#endif
	Im_B2R_On_Pclk( pipe_no );

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWTRG.bit.YBWTRG = ImB2r1_D_IM_B2R_YBWTRG_ON;

#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_ContStart off pclk\n" ));
#endif
	Im_B2R_Off_Pclk( pipe_no );
	ImB2r1_IM_B2R_DSB();

	return D_DDIM_OK;
}

/* Start B2R process.
 */
INT32 Im_B2R_Start( UCHAR pipe_no, UCHAR start_type )
{
	DDIM_USER_ER		ercd;
	INT32				retcd;
	UCHAR				loop_cnt, loop_sta, loop_end;
	DDIM_USER_FLGPTN	flgptn = 0;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Start error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_Start begin\n" ));
#endif


	// P-clock control
#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_Start on pclk\n" ));
#endif

	im_b2r_get_loop_val( pipe_no, &loop_sta, &loop_end );

	Im_B2R_On_Pclk( pipe_no );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBR.YBRTRG.bit.YBRTRG != ImB2r1_D_IM_B2R_YBRTRG_IDLE ){
			Ddim_Print(( "Im_B2R_Start error. YBR busy\n" ));
			return ImB2r_D_IM_B2R_MACRO_BUSY;
		}
		if( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWTRG.bit.YBWTRG != ImB2r1_D_IM_B2R_YBWTRG_IDLE ){
			Ddim_Print(( "Im_B2R_Start error. YBW busy\n" ));
			return ImB2r_D_IM_B2R_MACRO_BUSY;
		}
		if( imB2rIsActFb2r(loop_cnt) != ImB2r_D_IM_B2R_ENABLE_OFF ){
			Ddim_Print(( "Im_B2R_Start error. F_B2R busy\n" ));
			return ImB2r_D_IM_B2R_MACRO_BUSY;
		}
	}

	while( 1 ) {	// Pclk enable section
		// Clear of All Interrupt enable & Interrupt status
#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
		Ddim_Print(( "Im_B2R_Start begin initialize\n" ));
#endif

#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
		Ddim_Print(( "Im_B2R_Start initialize interrupt\n" ));
#endif
		// Initialized Interrupt
		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.YBINTE.word = ImB2r1_D_IM_B2R_YBINTE_DISABLE;
		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.YBINTF.word = ImB2r1_D_IM_B2R_YBINTF_ALL_CLR;

		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.B2RINTE.word = ImB2r1_D_IM_B2R_B2RINTE_DISABLE;
		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.B2RINTF.word = ImB2r1_D_IM_B2R_B2RINTF_CLR;

		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).intStatus = 0;
		}

#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
		Ddim_Print(( "Im_B2R_Start enable interrupt\n" ));
#endif
		if( start_type != ImB2r_D_IM_B2R_START_EXTERNAL_IF_ONLY ){
			im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.YBINTE.word = ImB2r1_D_IM_B2R_YBINTE_ALL_ENABLE;
		}
		else{
			im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.YBINTE.word = ImB2r1_D_IM_B2R_YBINTE_EXT_ONLY_ENABLE;
		}

		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.B2RINTE.word = ImB2r1_D_IM_B2R_B2RINTE_ENABLE;


#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
		Ddim_Print(( "Im_B2R_Start on clk\n" ));
#endif
		Im_B2R_On_Iclk( pipe_no );
		Im_B2R_On_Clk( pipe_no );


		// Set access enable

		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			// Bayer Deknee
			if( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBR.YBRCTL.bit.DKNEN != 0 ) {
				Im_B2R_Set_DekneeAccessEnable( loop_cnt, ImB2r_D_IM_B2R_ENABLE_ON, ImB2r_D_IM_B2R_WAIT_OFF );
			}

			// RGB Knee
			if( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWMD.bit.KNEEN != 0 ) {
				Im_B2R_Set_RGB_KneeAccessEnable( loop_cnt, ImB2r_D_IM_B2R_ENABLE_ON, ImB2r_D_IM_B2R_WAIT_OFF );
			}
		}


		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.RAMAEN.bit.RAMAEN_YBR = 1;
		if( start_type != ImB2r_D_IM_B2R_START_EXTERNAL_IF_ONLY ){
			im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.RAMAEN.bit.RAMAEN_YBW = 1;
		}

		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.FLTAEN.bit.CIAEN = 1;

		ImB2r1_IM_B2R_WAIT_USEC( ImB2r1_D_IM_B2R_SRAM_WAIT_USEC );


#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
		Ddim_Print(( "Im_B2R_Start clear event flag\n" ));
#endif

		// Clear of Event Flag
		if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
			flgptn |= ImB2r_D_IM_B2R1_INT_FLG_ALL;
		}
		if( ImB2r1_IM_B2R_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
			flgptn |= ImB2r_D_IM_B2R2_INT_FLG_ALL;
		}

		ercd = DDIM_User_Clr_Flg( FID_IM_B2R, ~flgptn );
		if( ercd != D_DDIM_USER_E_OK ) {
			Ddim_Print(( "Im_B2R_Start: invalid FID\n" ));
			retcd = ImB2r_D_IM_B2R_SYSTEM_ERROR;
			break;
		}

		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).wasStarted = ImB2r1_D_IM_B2R_TRUE;

#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
			Ddim_Print(( "Im_B2R_Start check macro busy state\n" ));
#endif
#ifndef D_IM_B2R_DEBUG_ON_PC
			ImB2r1_IM_B2R_DSB();
			while( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBR.YBRTRG.bit.YBRTRG == ImB2r1_D_IM_B2R_YBRTRG_BUSY ) {
				;	// DO NOTHING
			}

			while( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWTRG.bit.YBWTRG == ImB2r1_D_IM_B2R_YBWTRG_BUSY ) {
				;	// DO NOTHING
			}
#endif

			if( start_type != ImB2r_D_IM_B2R_START_EXTERNAL_IF_ONLY ){
				im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).busyState |= ImB2r1_D_IM_B2R_STATE_BUSY_YBW;
			}
			im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).busyState |= ImB2r1_D_IM_B2R_STATE_BUSY_F_B2R;
			im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).busyState |= ImB2r1_D_IM_B2R_STATE_BUSY_YBR;
		}

		if( start_type != ImB2r_D_IM_B2R_START_EXTERNAL_IF_ONLY ){
#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
		Ddim_Print(( "Im_B2R_Start enable YBW\n" ));
#endif
			im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWTRG.bit.YBWTRG = ImB2r1_D_IM_B2R_YBWTRG_ON;
		}

#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
		Ddim_Print(( "Im_B2R_Start enable F_B2R\n" ));
#endif
		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.CNTL.bit.TRG = ImB2r1_D_IM_B2R_FB2RTRG_ON;
#ifdef CO_DEBUG_ON_PC
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->F_B2R.CNTL.CNTL.bit.TRG = ImB2r1_D_IM_B2R_FB2RTRG_BUSY;
		}
#endif

#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
		Ddim_Print(( "Im_B2R_Start enable YBR\n" ));
#endif
		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRTRG.bit.YBRTRG = ImB2r1_D_IM_B2R_YBRTRG_ON;

		retcd = D_DDIM_OK;
		break;
	}

#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_Start off pclk\n" ));
#endif
	Im_B2R_Off_Pclk( pipe_no );

#ifdef D_IM_B2R_DEBUG_ON_PC
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( gImB2rMacroFakeFinish[loop_cnt] != 0 ) {
			im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->B2R_CMN.YBINTF.word = 0;
			im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->F_B2R.CNTL.B2RINTF.word = 0;
			im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->B2R_CMN.YBINTF.bit.__YBREF = 1;
			if( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->B2R_CMN.ELNLV.bit.ELNLV != 0 ){
				im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->B2R_CMN.YBINTF.bit.__ELNEF = 1;
			}
			if( start_type != ImB2r_D_IM_B2R_START_EXTERNAL_IF_ONLY ){
				im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->B2R_CMN.YBINTF.bit.__YBWEF = 1;
				if( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWBANK.bit.BANKST != 0 ) {
					im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWBANK.bit.BANKST = 0;
					im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWBANK.bit.BANKSTS = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWBANK.bit.BANKPS;
				}
			}
			Im_B2R_Int_Handler( loop_cnt );
			im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->B2R_CMN.YBINTF.word = 0;
			if( start_type != ImB2r_D_IM_B2R_START_EXTERNAL_IF_ONLY ){
				im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWBANK.bit.BANKSTS = ImB2r1_IM_B2R_INC_BANK_INDEX( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWBANK.bit.BANKSTS, im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWCTL.bit.USEBANK +1 );
			}
		}
	}
#endif

	ImB2r1_IM_B2R_DSB();

#ifdef ImB2r_CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_Start end\n" ));
#endif

	return retcd;
}

/* Stop B2R process
 */
INT32 Im_B2R_Stop( UCHAR pipe_no )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Stop error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_b2r_get_loop_val( pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).wasStarted = ImB2r1_D_IM_B2R_FALSE;
	}

	Im_B2R_On_Pclk( pipe_no );
	Im_B2R_On_Iclk( pipe_no );
	Im_B2R_On_Clk( pipe_no );	// ImB2r1_D_IM_B2R_FB2RTRG_OFF control accompanies the B2R reset.

	//
	// Stop YBW
	//
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).busyState &= ~(ImB2r1_D_IM_B2R_STATE_BUSY_YBW);
	}
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWTRG.bit.YBWTRG = ImB2r1_D_IM_B2R_YBWTRG_OFF;

	ImB2r1_IM_B2R_DSB();
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		while( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWTRG.bit.YBWTRG != ImB2r1_D_IM_B2R_YBWTRG_IDLE ) {
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(( "Im_B2R_Stop YBW wait loop. %u\n", im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWTRG.bit.YBWTRG ));
			im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWTRG.bit.YBWTRG = ImB2r1_D_IM_B2R_YBWTRG_IDLE;
#endif
			;	// DO NOTHING
		}
	}

	//
	// Stop F_B2R
	//
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).busyState &= ~(ImB2r1_D_IM_B2R_STATE_BUSY_F_B2R);
	}
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.CNTL.bit.TRG = ImB2r1_D_IM_B2R_FB2RTRG_OFF;
#ifdef CO_DEBUG_ON_PC
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->F_B2R.CNTL.CNTL.bit.TRG = ImB2r1_D_IM_B2R_FB2RTRG_IDLE;
	}
#endif

	//
	// Stop YBR
	//
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).busyState &= ~(ImB2r1_D_IM_B2R_STATE_BUSY_YBR);
	}
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRTRG.bit.YBRTRG = ImB2r1_D_IM_B2R_YBRTRG_OFF;

	ImB2r1_IM_B2R_DSB();
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		while( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBR.YBRTRG.bit.YBRTRG != ImB2r1_D_IM_B2R_YBRTRG_IDLE ) {
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(( "Im_B2R_Stop YBR wait loop. %u\n", im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBR.YBRTRG.bit.YBRTRG ));
			im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBR.YBRTRG.bit.YBRTRG = ImB2r1_D_IM_B2R_YBRTRG_IDLE;
#endif
			;	// DO NOTHING
		}
	}

	// Clear of All Interrupt disable
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.YBINTE.word = ImB2r1_D_IM_B2R_YBINTE_DISABLE;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.YBINTF.word = ImB2r1_D_IM_B2R_YBINTF_ALL_CLR;

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.B2RINTE.word = ImB2r1_D_IM_B2R_B2RINTE_DISABLE;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.B2RINTF.word = ImB2r1_D_IM_B2R_B2RINTF_CLR;

	// Bayer Deknee
	Im_B2R_Set_DekneeAccessEnable( pipe_no, ImB2r_D_IM_B2R_ENABLE_OFF, ImB2r_D_IM_B2R_WAIT_OFF );

	// RGB Knee
	Im_B2R_Set_RGB_KneeAccessEnable( pipe_no, ImB2r_D_IM_B2R_ENABLE_OFF, ImB2r_D_IM_B2R_WAIT_OFF );

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.RAMAEN.bit.RAMAEN_YBR = 0;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.RAMAEN.bit.RAMAEN_YBW = 0;

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.FLTAEN.bit.CIAEN = 0;

	Im_B2R_Force_Off_Clk( pipe_no );
	Im_B2R_Force_Off_Iclk( pipe_no );
	Im_B2R_Force_Off_Pclk( pipe_no );
	ImB2r1_IM_B2R_DSB();

	return D_DDIM_OK;
}




//为了平衡代码量，私有转公有
/* Calculate input(YBR) width and lines when SDRAM input mode.
 */
VOID im_b2r_calc_in_rect_sdram_input( UCHAR pipe_no )
{
	USHORT img_width;
	USHORT img_lines;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no >= ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "im_b2r_set_ybr_address_sdram_input error. pipe_no>=ImB2r_D_IM_B2R_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk(pipe_no);

	// YBRHSIZ (2pixels alignment & Advancing)
	img_width = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputSize.img_width;
	img_width = ImB2r1_IM_B2R_MIN( img_width, (USHORT)ImB2r1_D_IM_B2R_YBRHSIZ_MAX );
	img_width = ImB2r1_IM_B2R_MAX( img_width, (USHORT)(ImB2r1_D_IM_B2R_YBRHSIZ_MIN + im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).ringPixsInfo.refPixs) );

	// YBRVSIZ
	img_lines = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputSize.img_lines;
	img_lines = ImB2r1_IM_B2R_MIN( img_lines, (USHORT)ImB2r1_D_IM_B2R_YBRVSIZ_MAX );
	img_lines = ImB2r1_IM_B2R_MAX( img_lines, (USHORT)(ImB2r1_D_IM_B2R_YBRVSIZ_MIN + im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).ringPixsInfo.refPixs) );

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRHSIZ.word = img_width;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRVSIZ.word = img_lines;

	Im_B2R_Off_Pclk(pipe_no);
}

//为了平衡代码量，私有转公有
/* Calculate input(YBR) width and lines when B2B direct input mode.
 */
VOID im_b2r_calc_in_rect_b2b_direct( UCHAR pipe_no )
{
	USHORT img_top;
	USHORT img_left;
	USHORT img_width;
	USHORT img_lines;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no >= ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "im_b2r_calc_in_rect_b2b_direct error. pipe_no>=ImB2r_D_IM_B2R_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk(pipe_no);

	// DINVSTA
	img_top = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputSize.img_top;
	img_top = ImB2r1_IM_B2R_MIN( img_top, (USHORT)ImB2r1_D_IM_B2R_DINVSTA_MAX );
	img_top = ImB2r1_IM_B2R_MAX( img_top, (USHORT)ImB2r1_D_IM_B2R_DINVSTA_MIN );

	// DINHSTA
	img_left = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputSize.img_left;
	img_left = ImB2r1_IM_B2R_MIN( img_left, (USHORT)ImB2r1_D_IM_B2R_DINHSTA_MAX );
	img_left = ImB2r1_IM_B2R_MAX( img_left, (USHORT)ImB2r1_D_IM_B2R_DINHSTA_MIN );

	// DINVSIZ
	img_lines = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputSize.img_lines;
	img_lines = ImB2r1_IM_B2R_MIN( img_lines, (USHORT)ImB2r1_D_IM_B2R_DINVSIZ_MAX );
	img_lines = ImB2r1_IM_B2R_MAX( img_lines, (USHORT)(ImB2r1_D_IM_B2R_DINVSIZ_MIN + im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).ringPixsInfo.refPixs) );

	// DINHSIZ (2pixels alignment & Advancing)
	img_width = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputSize.img_width;
	img_width = ImB2r1_IM_B2R_MIN( img_width, (USHORT)ImB2r1_D_IM_B2R_DINHSIZ_MAX );
	img_width = ImB2r1_IM_B2R_MAX( img_width, (USHORT)(ImB2r1_D_IM_B2R_DINHSIZ_MIN + im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).ringPixsInfo.refPixs) );

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.DINVSTA.word = img_top;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.DINHSTA.word = img_left;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.DINVSIZ.word = img_lines;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.DINHSIZ.word = img_width;

	Im_B2R_Off_Pclk(pipe_no);
}

//为了平衡代码量，私有转公有
/* Calculate bayer left-top pixel color.
 */
VOID im_b2r_calc_top_color_sdram_input( UCHAR pipe_no )
{
	ImB2r2 *imB2r2=im_b2r2_get();

	static const UCHAR t_top_pix_of_trim[4][2][2] = {	// top_color, trim_v_odd, trim_h_odd
			// H even				 H odd
		{	// R
			{ ImB2r_D_IM_B2R_TOP_PIXEL_R,  ImB2r_D_IM_B2R_TOP_PIXEL_GR },	// V even
			{ ImB2r_D_IM_B2R_TOP_PIXEL_GB, ImB2r_D_IM_B2R_TOP_PIXEL_B }		// V odd
		},
		{	// B
			{ ImB2r_D_IM_B2R_TOP_PIXEL_B,  ImB2r_D_IM_B2R_TOP_PIXEL_GB }, 	// V even
			{ ImB2r_D_IM_B2R_TOP_PIXEL_GR, ImB2r_D_IM_B2R_TOP_PIXEL_R }		// V odd
		},
		{	// GR
			{ ImB2r_D_IM_B2R_TOP_PIXEL_GR, ImB2r_D_IM_B2R_TOP_PIXEL_R },	// V even
			{ ImB2r_D_IM_B2R_TOP_PIXEL_B,  ImB2r_D_IM_B2R_TOP_PIXEL_GB }	// V odd
		},
		{	// GB
			{ ImB2r_D_IM_B2R_TOP_PIXEL_GB, ImB2r_D_IM_B2R_TOP_PIXEL_B },	// V even
			{ ImB2r_D_IM_B2R_TOP_PIXEL_R,  ImB2r_D_IM_B2R_TOP_PIXEL_GR }	// V odd
		}
	};
	USHORT trim_v_odd;
	USHORT trim_h_odd;

#ifdef CO_PARAM_CHECK
	if( pipe_no >= ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "im_b2r_calc_top_color_sdram_input error. pipe_no>=ImB2r_D_IM_B2R_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );

	trim_v_odd = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputSize.img_top % 2;
	trim_h_odd = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputSize.img_left % 2;

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRCTL.bit.PIXEL
			 = t_top_pix_of_trim[im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).bayerTopPixel][trim_v_odd][trim_h_odd];

	Im_B2R_Off_Pclk( pipe_no );
}



ImB2r2 *im_b2r2_get()
{
	static ImB2r2 *imB2r2 = NULL;
	if(!imB2r2)
		imB2r2 = k_object_new_with_private(IM_TYPE_B2R2,sizeof(ImB2r2Private));
	   imB2r2->gImIoB2rRegPtr[0]=&IO_B2R_P1;
		imB2r2->gImIoB2rRegPtr[1]=&IO_B2R_P2;
		imB2r2->gImIoB2rRegPtr[2]=&IO_B2R_P3;
	return imB2r2;
}

