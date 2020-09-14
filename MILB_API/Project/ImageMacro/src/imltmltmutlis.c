/*
*@Copyright (C) 2010-2020贵阳高新网用软件有限公司
*@date                :2020-9-2
*@author           :sunhongyu
*@brief                :imltmmapevent类
*@rely                  :
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "im_ltm.h"
#include <string.h>
#include "ddarm.h"
#include "jdsltm.h"
#include "imltmltmutlis.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImLtmLtmUtlis, im_ltm_ltm_utlis);
#define IM_LTM_LTM_UTLIS_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImLtmLtmUtlisPrivate, IM_TYPE_LTM_LTM_UTLIS))

struct _ImLtmLtmUtlisPrivate
{
	int a;
};

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

static volatile struct io_ltm_ltm_sram* S_GIM_IO_LTM_LTM_TBL_PTR[D_IM_LTM_PIPE_MAX] = { &(IO_LTM_TBL_P1.LTM_SRAM), &(IO_LTM_TBL_P2.LTM_SRAM), &(IO_LTM_TBL_P3.LTM_SRAM) };

static const TImLtmLtmIntflgTbl S_GIM_LTM_LTM_INTTBL[ImLtmLtmUtlis_D_IM_LTM_PIPE_COUNT][6] = {
	{
		{ 0x00000001, 0x00000001, D_IM_LTM_LTM1_INT_STATE_LTM_END,   D_IM_LTM_LTM1_INT_FLG_LTM_END  },	// FINEN
		{ 0x00000010, 0x00000010, D_IM_LTM_LTM1_INT_STATE_EXIP_END,  ImLtmLtmUtlis_D_IM_LTM_LTM1_INT_FLG_EXIP_END },	// EXIPEN
		{ 0x00001000, 0x00001000, D_IM_LTM_LTM1_INT_STATE_LINE_END,  ImLtmLtmUtlis_D_IM_LTM_LTM1_INT_FLG_LINE_END },	// LCNTEN
		{ 0x00100000, 0x00100000, D_IM_LTM_LTM1_INT_STATE_AXR_ERR,   ImLtmLtmUtlis_D_IM_LTM_LTM1_INT_FLG_AXR_ERR  },	// AXREEN
		{ 0x00200000, 0x00200000, D_IM_LTM_LTM1_INT_STATE_AXW_ERR,   ImLtmLtmUtlis_D_IM_LTM_LTM1_INT_FLG_AXW_ERR  },	// AXWEEN
		{ 0x02000000, 0x02000000, D_IM_LTM_LTM1_INT_STATE_YLOG_ERR,  ImLtmLtmUtlis_D_IM_LTM_LTM1_INT_FLG_YLOG_ERR },	// RAMEEN
	},
	{
		{ 0x00000001, 0x00000001, D_IM_LTM_LTM2_INT_STATE_LTM_END,   D_IM_LTM_LTM2_INT_FLG_LTM_END  },	// FINEN
		{ 0x00000010, 0x00000010, D_IM_LTM_LTM2_INT_STATE_EXIP_END,  ImLtmLtmUtlis_D_IM_LTM_LTM2_INT_FLG_EXIP_END },	// EXIPEN
		{ 0x00001000, 0x00001000, D_IM_LTM_LTM2_INT_STATE_LINE_END,  ImLtmLtmUtlis_D_IM_LTM_LTM2_INT_FLG_LINE_END },	// LCNTEN
		{ 0x00100000, 0x00100000, D_IM_LTM_LTM2_INT_STATE_AXR_ERR,   ImLtmLtmUtlis_D_IM_LTM_LTM2_INT_FLG_AXR_ERR  },	// AXREEN
		{ 0x00200000, 0x00200000, D_IM_LTM_LTM2_INT_STATE_AXW_ERR,   ImLtmLtmUtlis_D_IM_LTM_LTM2_INT_FLG_AXW_ERR  },	// AXWEEN
		{ 0x02000000, 0x02000000, D_IM_LTM_LTM2_INT_STATE_YLOG_ERR,  ImLtmLtmUtlis_D_IM_LTM_LTM2_INT_FLG_YLOG_ERR },	// RAMEEN
	},
};

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

//---------------------- driver  section -------------------------------
#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

static void im_ltm_ltm_utlis_constructor(ImLtmLtmUtlis *self)
{
//	ImLtmLtmUtlisPrivate *priv = IM_LTM_LTM_UTLIS_GET_PRIVATE(self);
}

static void im_ltm_ltm_utlis_destructor(ImLtmLtmUtlis *self)
{
//	ImLtmLtmUtlisPrivate *priv = IM_LTM_LTM_UTLIS_GET_PRIVATE(self);
}

/*
 PUBLIC
*/
 VOID im_ltm_ltm_utlis_im_ltm_ltm_get_loop_val(ImLtmLtmUtlis*self,UCHAR pipe_no, UCHAR* loop_sta, UCHAR* loop_end )
{
	switch( pipe_no ){
		case D_IM_LTM_PIPE1:
			*loop_sta = 0;
			*loop_end = 0;
			break;
		case D_IM_LTM_PIPE2:
			*loop_sta = 1;
			*loop_end = 1;
			break;
//		case D_IM_LTM_PIPE12:
		default:
			*loop_sta = 0;
			*loop_end = 1;
			break;
	}
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

INT32 Im_LTM_LTM_Set_MapImage_Resize_Pitch( UCHAR pipe_no, const T_IM_LTM_LTM_MAP_RESIZE_PITCH* const resize_pitch )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	if( resize_pitch == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Set_MapImage_Resize_Pitch error. ltm_ctrl_b2r_direct = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Set_MapImage_Resize_Pitch error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no) ->LHSTA, union io_ltm_ch_ltm_lhsta, HSTA, resize_pitch->hsta );
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LHPIT.bit.HPIT = resize_pitch->hpit;
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LVSTA, union io_ltm_ch_ltm_lvsta, VSTA, resize_pitch->vsta );
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LVPIT.bit.VPIT = resize_pitch->vpit;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* Set Frame stop
 */
INT32 Im_LTM_LTM_Set_FrameStop( UCHAR pipe_no, UCHAR onoff )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Set_FrameStop error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LFRSTP.bit.FRSTP = onoff;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* Set LTM parameter hold
*/
INT32 Im_LTM_LTM_Set_ParamHold( UCHAR pipe_no, const UCHAR hold_enable )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Set_ParamHold error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LPARMSK.bit.PARMSK = hold_enable;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* Get LTM busy status.
 */
INT32 Im_LTM_LTM_Get_LtmBusy( UCHAR pipe_no, BOOL* const busy_status )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	ULONG ltmtrg;

#ifdef CO_PARAM_CHECK
	if( busy_status == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Get_LtmBusy error. busy_status = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Get_LtmBusy error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	ltmtrg = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LTRG.bit.TRG;

	Im_LTM_Off_Pclk( pipe_no );

	if( ltmtrg == ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_BUSY ) {
		*busy_status = TRUE;
	}
	else {
		*busy_status = FALSE;
	}
	return D_DDIM_OK;
}

/* Restart LTM process.
 */
INT32 Im_LTM_LTM_ContStart( UCHAR pipe_no )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_ContStart error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// P-clock control
#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_ContStart on pclk\n" ));
#endif
	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSRAMEN.word = ImLtmLtmUtlis_D_IM_LTM_LTM_LSRAMEN_ENABLE;

	ImLtmLtmUtlis_IM_LTM_LTM_WAIT_USEC( ImLtmLtmUtlis_D_IM_LTM_LTM_SRAM_WAIT_USEC );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LTRG.bit.TRG = ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_ON;

#ifdef CO_DEBUG_ON_PC
	if( ImLtmLtmUtlis_IM_LTM_LTM_CHECK_TARGET_PIPE_NO_1(pipe_no) ){
		gIM_Io_Ltm_Ltm_Reg_Ptr[D_IM_LTM_PIPE1]->LTRG.bit.TRG = ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_BUSY;
	}
	if( ImLtmLtmUtlis_IM_LTM_LTM_CHECK_TARGET_PIPE_NO_2(pipe_no) ){
		gIM_Io_Ltm_Ltm_Reg_Ptr[D_IM_LTM_PIPE2]->LTRG.bit.TRG = ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_BUSY;
	}
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_ContStart off pclk\n" ));
#endif
	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* Start LTM process.
 */
INT32 Im_LTM_LTM_Start( UCHAR pipe_no )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	DDIM_USER_ER		ercd;
	INT32				retcd;
	UCHAR				loop_cnt, loop_sta, loop_end;
	DDIM_USER_FLGPTN	flgptn = 0;

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Start error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_Start begin\n" ));
#endif

	// P-clock control
#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_Start on pclk\n" ));
#endif

	im_ltm_ltm_utlis_im_ltm_ltm_get_loop_val(NULL,pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );

	while( 1 ) {	// Pclk enable section
		// Clear of All Interrupt enable & Interrupt status
#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
		Ddim_Print(( "Im_LTM_LTM_Start begin initialize\n" ));
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
		Ddim_Print(( "Im_LTM_LTM_Start initialize interrupt\n" ));
#endif
		// Initialized Interrupt
		im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LINT1.word = ImLtmLtmUtlis_D_IM_LTM_LTM_LINT1_ALL_CLR;

		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,loop_cnt).intStatus = 0;
		}

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
		Ddim_Print(( "Im_LTM_LTM_Start enable interrupt\n" ));
#endif
		im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LINT0.word = ImLtmLtmUtlis_D_IM_LTM_LTM_LINT0_ENABLE;

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
		Ddim_Print(( "Im_LTM_LTM_Start on clk\n" ));
#endif
		Im_LTM_On_Hclk( pipe_no );
		Im_LTM_On_Aclk( pipe_no );
		Im_LTM_On_Clk( pipe_no );

		ImLtmLtmUtlis_IM_LTM_LTM_WAIT_USEC( ImLtmLtmUtlis_D_IM_LTM_LTM_SRAM_WAIT_USEC );

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
		Ddim_Print(( "Im_LTM_LTM_Start clear event flag\n" ));
#endif

		// Clear of Event Flag
		if( ImLtmLtmUtlis_IM_LTM_LTM_CHECK_TARGET_PIPE_NO_1( pipe_no ) ){
			flgptn |= ImLtmLtmUtlis_D_IM_LTM_LTM1_INT_FLG_ALL;
		}
		if( ImLtmLtmUtlis_IM_LTM_LTM_CHECK_TARGET_PIPE_NO_2( pipe_no ) ){
			flgptn |= ImLtmLtmUtlis_D_IM_LTM_LTM2_INT_FLG_ALL;
		}

		ercd = DDIM_User_Clr_Flg( FID_IM_LTM_LTM, ~flgptn );
		if( ercd != D_DDIM_USER_E_OK ) {
			Ddim_Print(( "Im_LTM_LTM_Start: invalid FID\n" ));
			retcd = D_IM_LTM_SYSTEM_ERROR;
			break;
		}

		im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSRAMEN.word = ImLtmLtmUtlis_D_IM_LTM_LTM_LSRAMEN_ENABLE;

		ImLtmLtmUtlis_IM_LTM_LTM_WAIT_USEC( ImLtmLtmUtlis_D_IM_LTM_LTM_SRAM_WAIT_USEC );

		im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LTRG.bit.TRG = ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_ON;
#ifdef CO_DEBUG_ON_PC
		for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
			im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,loop_cnt) ->LTRG.bit.TRG = ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_BUSY;
		}
#endif
		retcd = D_DDIM_OK;
		break;
	}

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_Start off pclk\n" ));
#endif
	Im_LTM_Off_Pclk( pipe_no );

#ifdef D_IM_LTM_LTM_DEBUG_ON_PC
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,loop_cnt) ->LINT1.word = 0;
		im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,loop_cnt) ->LINT1.bit.__FINFL = 1;
		if( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,loop_cnt) ->LLINTLV.bit.LINTLV != 0 ){
			im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,loop_cnt) ->LINT1.bit.__LCNTFL = 1;
		}
		Im_LTM_LTM_Int_Handler( loop_cnt );
		im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,loop_cnt) ->LINT1.word = 0;
	}
#endif

	ImLtmLtmUtlis_IM_LTM_DSB();

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_Start end\n" ));
#endif

	return retcd;
}

/* Stop LTM LTM process
 */
INT32 Im_LTM_LTM_Stop( UCHAR pipe_no )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	UCHAR loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Stop error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_ltm_ltm_utlis_im_ltm_ltm_get_loop_val(NULL,pipe_no, &loop_sta, &loop_end );

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LTRG.bit.TRG = ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_OFF;

	ImLtmLtmUtlis_IM_LTM_DSB();
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		while( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,loop_cnt) ->LTRG.bit.TRG != ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_IDLE ) {
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(( "Im_LTM_LTM_Stop wait loop. %u\n", im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,loop_cnt) ->LTRG.bit.TRG ));
			im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,loop_cnt) ->LTRG.bit.TRG = ImLtmLtmUtlis_D_IM_LTM_LTM_TRG_IDLE;
#endif
			;	// DO NOTHING
		}
	}

	// Clear of All Interrupt disable
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LINT0.word = ImLtmLtmUtlis_D_IM_LTM_LTM_LINT0_DISABLE;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LINT1.word = ImLtmLtmUtlis_D_IM_LTM_LTM_LINT1_ALL_CLR;

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSRAMEN.word = ImLtmLtmUtlis_D_IM_LTM_LTM_LSRAMEN_DISABLE;

	Im_LTM_Off_Clk( pipe_no );
	Im_LTM_Off_Aclk( pipe_no );
	Im_LTM_Off_Hclk( pipe_no );
	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* Wait end of LTM LTM macro.
 */
INT32 Im_LTM_LTM_WaitEnd( DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout )
{
	DDIM_USER_FLGPTN	flgptn;
	DDIM_USER_ER		ercd;

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_WaitEnd begin\n" ));
#endif

#ifdef CO_PARAM_CHECK
	if( (waiptn & ImLtmLtmUtlis_D_IM_LTM_LTM_INT_FLG_ALL) != waiptn ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_WaitEnd error. waiptn\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif
	ImLtmLtmUtlis_IM_LTM_DSB();

	switch( DDIM_User_Twai_Flg( FID_IM_LTM_LTM, waiptn, D_DDIM_USER_TWF_ORW, &flgptn, tmout ) ) {
		case D_DDIM_USER_E_OK:
#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
		Ddim_Print(( "Im_LTM_LTM_WaitEnd twai_flg OK return\n" ));
#endif
			flgptn = waiptn & flgptn;
			ercd = DDIM_User_Clr_Flg( FID_IM_LTM_LTM, ~flgptn );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "Im_LTM_LTM_WaitEnd: invalid FID.\n" ));
				return D_IM_LTM_PARAM_ERROR;
			}
			if( p_flgptn != NULL ) {
				*p_flgptn = flgptn;
			}
			return D_DDIM_OK;
		case D_DDIM_USER_E_TMOUT:
#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
		Ddim_Print(( "Im_LTM_LTM_WaitEnd twai_flg TimeOut return\n" ));
#endif
			return D_IM_LTM_TIMEOUT;
		default:
#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
		Ddim_Print(( "Im_LTM_LTM_WaitEnd twai_flg NG return\n" ));
#endif
			return D_IM_LTM_PARAM_ERROR;
	}
}

/* LTM_LTM Interrupt Handler
 */
VOID Im_LTM_LTM_Int_Handler( UCHAR pipe_no )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	UINT32			loopcnt;
	DDIM_USER_ER	ercd;
	ULONG			lint0;
	ULONG			lint1;
	ULONG			lint1_clr;

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Int_Handler error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_Int_Handler begin\n" ));
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_Int_Handler on pclk\n" ));
#endif
	Im_LTM_On_Pclk( pipe_no );

	lint0 = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LINT0.word;
	lint1 = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no) ->LINT1.word;
	lint1_clr = 0;

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_Int_Handler lint0=0x%lx, lint1=0x%lx\n", lint0, lint1 ));
#endif

	// Call of Callback API for interrupt status

	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_LTM_LTM_INTTBL[0]) / sizeof(S_GIM_LTM_LTM_INTTBL[0][0])); loopcnt++ ) {
		if( ((lint1 & S_GIM_LTM_LTM_INTTBL[pipe_no][loopcnt].flgBitmask) != 0)
		 && ((lint0 & S_GIM_LTM_LTM_INTTBL[pipe_no][loopcnt].enaBitmask) != 0) ) {

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
			Ddim_Print(( "Im_LTM_LTM_Int_Handler begin 0x%x\n", S_GIM_LTM_LTM_INTTBL[pipe_no][loopcnt].flgBitmask ));
#endif

			im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).intStatus = S_GIM_LTM_LTM_INTTBL[pipe_no][loopcnt].intStatus;

			lint1_clr |= S_GIM_LTM_LTM_INTTBL[pipe_no][loopcnt].flgBitmask;

			ercd = DDIM_User_Set_Flg( FID_IM_LTM_LTM, S_GIM_LTM_LTM_INTTBL[pipe_no][loopcnt].waitflg );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "Im_LTM_LTM_Int_Handler: invalid FID. 0x%lx\n", S_GIM_LTM_LTM_INTTBL[pipe_no][loopcnt].waitflg ));
			}

			if (im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).ltmUserHandler) {
				im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).ltmUserHandler( (UINT32*)&im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).intStatus, im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis,pipe_no).userParam );
			}
		}
	}

	// Clear interrupt
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LINT1.word = lint1_clr;

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_Int_Handler lint1=0x%lx\n", im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LINT1.word ));
#endif

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_Int_Handler off pclk\n" ));
#endif
	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

#ifdef CO_DEBUG_PRINT_IM_LTM_LTM
	Ddim_Print(( "Im_LTM_LTM_Int_Handler end\n" ));
#endif
}

/* Set LTM High frequency strength
*/
INT32 Im_LTM_LTM_Set_High_Frequency_Strength( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_HF_STRENGTH* hf_ctrl )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	if( hf_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Set_High_Frequency_Strength error. hf_ctrl = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Set_High_Frequency_Strength error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->NLVTHOF7.bit.NLVTHOF_7 = hf_ctrl->strength;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->PLVTHOF7.bit.PLVTHOF_7 = hf_ctrl->strength;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* Set internal parameter
 */
INT32 Im_LTM_LTM_Set_Internal_Param( UCHAR pipe_no, T_IM_LTM_INTERNAL_PARAM* const param )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	if( param == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Set_Internal_Param error. param = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Set_Internal_Param error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LYSHADOW.bit.YSHADOW       = param->yshadow;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LYHIGHLIGHT.bit.YHIGHLIGHT = param->yhighlight;

	Im_LTM_Off_Pclk( pipe_no );
	return D_DDIM_OK;
}

/* LTM Blend control
*/
INT32 Im_LTM_LTM_Ctrl_Blend( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_BLEND* blend_ctrl )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	if( blend_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Ctrl_Blend error. blend_ctrl = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Ctrl_Blend error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDYRT.bit.BLDYRT        = blend_ctrl->ratio;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDOF.BLDOF1.bit.BLDOF_0 = blend_ctrl->offset[0];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDOF.BLDOF1.bit.BLDOF_1 = blend_ctrl->offset[1];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDOF.BLDOF2.bit.BLDOF_2 = blend_ctrl->offset[2];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDOF.BLDOF2.bit.BLDOF_3 = blend_ctrl->offset[3];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDOF.BLDOF3.bit.BLDOF_4 = blend_ctrl->offset[4];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDOF.BLDOF3.bit.BLDOF_5 = blend_ctrl->offset[5];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDOF.BLDOF4.bit.BLDOF_6 = blend_ctrl->offset[6];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDOF.BLDOF4.bit.BLDOF_7 = blend_ctrl->offset[7];

	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDGA.BLDGA1, union io_ltm_ch_ltm_bldga_1, BLDGA_0, blend_ctrl->gain[0] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDGA.BLDGA1, union io_ltm_ch_ltm_bldga_1, BLDGA_1, blend_ctrl->gain[1] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDGA.BLDGA2, union io_ltm_ch_ltm_bldga_2, BLDGA_2, blend_ctrl->gain[2] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDGA.BLDGA2, union io_ltm_ch_ltm_bldga_2, BLDGA_3, blend_ctrl->gain[3] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDGA.BLDGA3, union io_ltm_ch_ltm_bldga_3, BLDGA_4, blend_ctrl->gain[4] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDGA.BLDGA3, union io_ltm_ch_ltm_bldga_3, BLDGA_5, blend_ctrl->gain[5] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDGA.BLDGA4, union io_ltm_ch_ltm_bldga_4, BLDGA_6, blend_ctrl->gain[6] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDGA.BLDGA4, union io_ltm_ch_ltm_bldga_4, BLDGA_7, blend_ctrl->gain[7] );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDBD.BLDBD1.bit.BLDBD_0 = blend_ctrl->border[0];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDBD.BLDBD1.bit.BLDBD_1 = blend_ctrl->border[1];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDBD.BLDBD2.bit.BLDBD_2 = blend_ctrl->border[2];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDBD.BLDBD2.bit.BLDBD_3 = blend_ctrl->border[3];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDBD.BLDBD3.bit.BLDBD_4 = blend_ctrl->border[4];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDBD.BLDBD3.bit.BLDBD_5 = blend_ctrl->border[5];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDBD.BLDBD4.bit.BLDBD_6 = blend_ctrl->border[6];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->BLDBD.BLDBD4.bit.BLDBD_7 = blend_ctrl->border[7];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LTMMD.bit.LTMMD          = blend_ctrl->mode;

	if( blend_ctrl->mode == 1 ){
		im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->RCGMD.bit.YSHMD = 1;
		im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->RCGMD.bit.RCGMD = 0;
	}
	else{
		im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->RCGMD.bit.YSHMD = 0;
		im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->RCGMD.bit.RCGMD = 1;
	}
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->RCGMD.bit.RCGAMD = 0;

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* LTM RCG table control
*/
INT32 Im_LTM_LTM_Set_RCG_Table( UCHAR pipe_no, const USHORT* const src_tbl )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	UINT32 loop_cnt;

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if(src_tbl == NULL) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Set_RCG_Table error. src_tbl = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Set_RCG_Table error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif

	Im_LTM_On_Pclk( pipe_no );

	for( loop_cnt = 0; loop_cnt < ImLtmLtmUtlis_D_IM_LTM_TABLE_MAX_RCG; loop_cnt++ ) {
		im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->RCGTBL.hword[loop_cnt] = src_tbl[loop_cnt];
	}

	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

/* LTM chroma correction strength control
*/
INT32 Im_LTM_LTM_Ctrl_Chroma_Correction_Strength( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_CHROMA* chroma_ctrl )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	if( chroma_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Ctrl_Chroma_Correction_Strength error. chroma_ctrl = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Ctrl_Chroma_Correction_Strength error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGOF.CGOF1.bit.CGOF_0 = chroma_ctrl->offset[0];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGOF.CGOF1.bit.CGOF_1 = chroma_ctrl->offset[1];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGOF.CGOF2.bit.CGOF_2 = chroma_ctrl->offset[2];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGOF.CGOF2.bit.CGOF_3 = chroma_ctrl->offset[3];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGOF.CGOF3.bit.CGOF_4 = chroma_ctrl->offset[4];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGOF.CGOF3.bit.CGOF_5 = chroma_ctrl->offset[5];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGOF.CGOF4.bit.CGOF_6 = chroma_ctrl->offset[6];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGOF.CGOF4.bit.CGOF_7 = chroma_ctrl->offset[7];

	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGGA.CGGA1, union io_ltm_ch_ltm_cgga_1, CGGA_0, chroma_ctrl->gain[0] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGGA.CGGA1, union io_ltm_ch_ltm_cgga_1, CGGA_1, chroma_ctrl->gain[1] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGGA.CGGA2, union io_ltm_ch_ltm_cgga_2, CGGA_2, chroma_ctrl->gain[2] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGGA.CGGA2, union io_ltm_ch_ltm_cgga_2, CGGA_3, chroma_ctrl->gain[3] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGGA.CGGA3, union io_ltm_ch_ltm_cgga_3, CGGA_4, chroma_ctrl->gain[4] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGGA.CGGA3, union io_ltm_ch_ltm_cgga_3, CGGA_5, chroma_ctrl->gain[5] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGGA.CGGA4, union io_ltm_ch_ltm_cgga_4, CGGA_6, chroma_ctrl->gain[6] );
	ImLtmLtmUtlis_IM_LTM_LTM_SET_REG_SIGNED( im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGGA.CGGA4, union io_ltm_ch_ltm_cgga_4, CGGA_7, chroma_ctrl->gain[7] );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGBD.CGBD1.bit.CGBD_1 = chroma_ctrl->border[0];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGBD.CGBD2.bit.CGBD_2 = chroma_ctrl->border[1];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGBD.CGBD2.bit.CGBD_3 = chroma_ctrl->border[2];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGBD.CGBD3.bit.CGBD_4 = chroma_ctrl->border[3];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGBD.CGBD3.bit.CGBD_5 = chroma_ctrl->border[4];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGBD.CGBD4.bit.CGBD_6 = chroma_ctrl->border[5];
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->CGBD.CGBD4.bit.CGBD_7 = chroma_ctrl->border[6];

	Im_LTM_Off_Pclk( pipe_no );
	ImLtmLtmUtlis_IM_LTM_DSB();

	return D_DDIM_OK;
}

/* YLOG table control
 */
INT32 Im_LTM_LTM_Ctrl_Ylog_Tbl( UCHAR pipe_no, const T_IM_LTM_CTRL_YLOG* const ylog_ctrl )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	if( ylog_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Ctrl_Ylog_Tbl error. ylog_ctrl = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Ctrl_Ylog_Tbl error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LYLCTL.bit.YLOGSL      = ylog_ctrl->use_tbl;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LYLOG0EP0.bit.YLOG0EP0 = ylog_ctrl->end_point0_tbl0;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LYLOG0EP1.bit.YLOG0EP1 = ylog_ctrl->end_point1_tbl0;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LYLOG1EP0.bit.YLOG1EP0 = ylog_ctrl->end_point0_tbl1;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LYLOG1EP1.bit.YLOG1EP1 = ylog_ctrl->end_point1_tbl1;

	Im_LTM_Off_Pclk( pipe_no );
	return D_DDIM_OK;
}

/* Get active YLOG table No.
 */
INT32 Im_LTM_LTM_Get_Active_Ylog_Tbl_No( UCHAR pipe_no, UCHAR* const tbl_no )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

#ifdef CO_PARAM_CHECK
	if( tbl_no == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Get_Active_Ylog_Tbl_No error. tbl_no = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Get_Active_Ylog_Tbl_No error. pipe_no>=D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	Im_LTM_On_Pclk( pipe_no );

	*tbl_no = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LYLCTL.bit.YLOGSTA;

	Im_LTM_Off_Pclk( pipe_no );
	return D_DDIM_OK;
}

/* Set YLOG table.
 */
INT32 Im_LTM_LTM_Set_YLOG_Table( UCHAR pipe_no, UCHAR tbl_sel, const USHORT* const src_tbl )
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	UINT32 sram_en;
#ifndef CO_LTM_RDMA_ON
	UINT32 loop_cnt;
	volatile USHORT* dst_tbl;
#endif	// CO_LTM_RDMA_ON

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if(src_tbl == NULL) {
		// Parameter setting error
		Ddim_Assertion(("Im_LTM_LTM_Set_YLOG_Table error. src_tbl = NULL\n"));
		return D_IM_LTM_PARAM_ERROR;
	}
	if( pipe_no > D_IM_LTM_PIPE12 ){
		Ddim_Assertion(( "Im_LTM_LTM_Set_YLOG_Table error. pipe_no>D_IM_LTM_PIPE12\n" ));
		return D_IM_LTM_PARAM_ERROR;
	}
#endif

	Im_LTM_On_Pclk( pipe_no );

	sram_en = im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSRAMEN.word;
	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSRAMEN.word = ImLtmLtmUtlis_D_IM_LTM_LTM_LSRAMEN_ENABLE;

#ifdef CO_LTM_RDMA_ON
	im_ltm_ltm_set_rdma_val_ylog_table( pipe_no, src_tbl );
#else	// CO_LTM_RDMA_ON
	Im_LTM_On_Hclk( pipe_no );

	switch( tbl_sel ){
		case D_LTM_YLOG_TBL_00:
			dst_tbl = S_GIM_IO_LTM_LTM_TBL_PTR[pipe_no]->LYLOG0TBL0.hword;
			break;
		case D_LTM_YLOG_TBL_10:
			dst_tbl = S_GIM_IO_LTM_LTM_TBL_PTR[pipe_no]->LYLOG1TBL0.hword;
			break;
		case D_LTM_YLOG_TBL_01:
			dst_tbl = S_GIM_IO_LTM_LTM_TBL_PTR[pipe_no]->LYLOG0TBL1.hword;
			break;
		case D_LTM_YLOG_TBL_11:
			dst_tbl = S_GIM_IO_LTM_LTM_TBL_PTR[pipe_no]->LYLOG1TBL1.hword;
			break;
		default:
			return D_IM_LTM_PARAM_ERROR;
	}

	for( loop_cnt = 0; loop_cnt < D_IM_LTM_TABLE_MAX_YLOG; loop_cnt++ ) {
		dst_tbl[loop_cnt] = src_tbl[loop_cnt];
	}

	Im_LTM_Off_Hclk( pipe_no );
#endif	// CO_LTM_RDMA_ON

	im_ltm_ltm_utlis_get_gIM_Io_Ltm_Ltm_Reg_Ptr(imLtmLtmUtlis,pipe_no)->LSRAMEN.word = sram_en;

	Im_LTM_Off_Pclk( pipe_no );

	return D_DDIM_OK;
}

#ifdef IM_LTM_LTM_STATUS_PRINT
im_ltm_ltm_utlis_im_ltm_ltm_print_status(ImLtmLtmUtlis*self)
{
	ImLtmLtmUtlis*imLtmLtmUtlis=im_ltm_ltm_utlis_get( );

	UINT32 loopcnt;

	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "PIPE%u:\n", loopcnt ));
		Ddim_Print(( "\tinput_size_rgb\n" ));
		Ddim_Print(( "\t\timg_left            = 0x%x\n", im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis, loopcnt).inputSizeRgb.img_left ));
		Ddim_Print(( "\t\timg_top             = 0x%x\n", im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis, loopcnt).inputSizeRgb.img_top ));
		Ddim_Print(( "\t\timg_width           = 0x%x\n", im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis, loopcnt).inputSizeRgb.img_width ));
		Ddim_Print(( "\t\timg_lines           = 0x%x\n",  im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis, loopcnt).inputSizeRgb.img_lines ));
		Ddim_Print(( "\tinput_size_y\n" ));
		Ddim_Print(( "\t\timg_left            = 0x%x\n",  im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis, loopcnt).inputSizeY.img_left ));
		Ddim_Print(( "\t\timg_top             = 0x%x\n",  im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis, loopcnt).inputSizeY.img_top ));
		Ddim_Print(( "\t\timg_width           = 0x%x\n",  im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis, loopcnt).inputSizeY.img_width ));
		Ddim_Print(( "\t\timg_lines           = 0x%x\n",  im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis, loopcnt).inputSizeY.img_lines ));
		Ddim_Print(( "\tint_status            = 0x%x\n",  im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis, loopcnt).intStatus ));
		Ddim_Print(( "\tltm_user_handler      = 0x%x\n", (UINT32) im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis, loopcnt).ltmUserHandler ));
		Ddim_Print(( "\tuser_param            = 0x%x\n", (UINT32) im_ltm_ltm_utlis_get_gIM_LTM_LTM_Mng(imLtmLtmUtlis, loopcnt).userParam ));
	}
}

VOID im_ltm_ltm_utlis_im_ltm_ltm_print_accenstatus(ImLtmLtmUtlis*self)
{
	UINT32 loopcnt;

	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "SRAMAEN  = 0x%x\n", gIM_Io_Ltm_Ltm_Reg_Ptr[loopcnt]->LSRAMEN.bit.SRAMAEN ));
		Ddim_Print(( "RMAENRGB = 0x%x\n", gIM_Io_Ltm_Ltm_Reg_Ptr[loopcnt]->LSRAMEN.bit.RMAENEGB ));
		Ddim_Print(( "RMAENYN  = 0x%x\n", gIM_Io_Ltm_Ltm_Reg_Ptr[loopcnt]->LSRAMEN.bit.RMAENYN ));
	}
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
}
#endif

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#endif	// CO_DDIM_UTILITY_USE

ImLtmLtmUtlis*im_ltm_ltm_utlis_get(void)
{
	 static ImLtmLtmUtlis* self = NULL;
	 if(!self){
		 self = k_object_new(IM_TYPE_LTM_LTM_UTLIS);
		 self->gIMIoLtmLtmRegPtr[D_IM_LTM_PIPE_MAX-2]=&(IO_LTM_P1.LTM);
		 self->gIMIoLtmLtmRegPtr[D_IM_LTM_PIPE_MAX-1]=&(IO_LTM_P2.LTM);
		 self->gIMIoLtmLtmRegPtr[D_IM_LTM_PIPE_MAX-D_IM_LTM_PIPE_MAX]=&(IO_LTM_P3.LTM) ;
	 }
//	 else{
//		 k_object_ref(self);
//	 }
	return self;
}
