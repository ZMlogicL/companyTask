/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-9-2 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/


#include "jdspro.h"
#include "im_pro.h"
#include "improcommon.h"
#include "ddtop.h"
#include "improstat.h"


G_DEFINE_TYPE(ImProStat, im_pro_stat, G_TYPE_OBJECT);
#define IM_PRO_STAT_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_PRO_STAT, ImProStatPrivate));

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define	ImProStat_STATUS_NONE					(0x00000000UL)				/* All stopped	*/
#define	ImProStat_STATUS_AEAWB_0				((0x00000000UL)&(1<< 0))	/* AEAWB0		*/
#define	ImProStat_STATUS_AEAWB_1				((0x00000000UL)&(1<< 1))	/* AEAWB1		*/
#define	ImProStat_STATUS_AEAWB_2				((0x00000000UL)&(1<< 2))	/* AEAWB2		*/
#define	ImProStat_STATUS_AEAWB_3				((0x00000000UL)&(1<< 3))	/* AEAWB3		*/
#define	ImProStat_STATUS_HIST_0					((0x00000000UL)&(1<< 4))	/* HIST0		*/
#define	ImProStat_STATUS_HIST_1					((0x00000000UL)&(1<< 5))	/* HIST1		*/
#define	ImProStat_STATUS_HIST_2					((0x00000000UL)&(1<< 6))	/* HIST2		*/
#define	ImProStat_STATUS_HIST_3					((0x00000000UL)&(1<< 7))	/* HIST3		*/
#define	ImProStat_STATUS_AF_0					((0x00000000UL)&(1<< 8))	/* AF0			*/
#define	ImProStat_STATUS_AF_1					((0x00000000UL)&(1<< 9))	/* AF1			*/
#define	ImProStat_STATUS_FLCK_0					((0x00000000UL)&(1<<10))	/* FLCK0		*/
#define	ImProStat_STATUS_FLCK_1					((0x00000000UL)&(1<<11))	/* FLCK1		*/

#define	ImProStat_AEAEB_AE_BLK_SIZE				(4)			/* AE block data size		*/
#define	ImProStat_AEAEB_AWB_BLK_SIZE				(16)		/* AWB block data size		*/
#define	ImProStat_AEAEB_IAWB_BLK_SIZE			(128)		/* IAWB block data size		*/
#define	ImProStat_AEAEB_DUMMY_DATA_SIZE			(4)			/* Dummy block data size	*/

#define ImProStat_FLCK0_PWCH			(E_IM_PRO_PWCH_4)
#define ImProStat_FLCK1_PWCH			(E_IM_PRO_PWCH_5)


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
// PRO Channel/Macro start/stop status
#define ImProStat_SET_START_STATUS(st, ch) 	(S_IM_PRO_STAT_START_STATUS[((st) >> 28) & 0xf] |=  (((st) & 0x0fffffff) << (ch)))								/* SEN clock status ON	*/
#define ImProStat_SET_STOP_STATUS(st, ch)		(S_IM_PRO_STAT_START_STATUS[((st) >> 28) & 0xf] &= ~(((st) & 0x0fffffff) << (ch)))								/* SEN clock status OFF	*/
#define ImProStat_GET_START_STATUS(st, ch)	(((S_IM_PRO_STAT_START_STATUS[((st) >> 28) & 0xf] & (((st) & 0x0fffffff) << (ch))) != 0) ? TRUE : FALSE)			/* started check	*/

#define ImProStat_GET_STOP_ALL()				((S_IM_PRO_STAT_START_STATUS[0] != 0) ? FALSE : TRUE)	/* started check	*/

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// clock control status
static	volatile	kulong	 S_IM_PRO_STAT_START_STATUS[1] = {0x00000000};

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/


struct _ImProStatPrivate{

};


/*DECLS*/
static void 					dispose_od(GObject *object);
static void 					finalize_od(GObject *object);


/*IMPL*/
static void im_pro_stat_class_init(ImProStatClass *klass)
{
	g_type_class_add_private(klass, sizeof(ImProStatPrivate));
}

static void im_pro_stat_init(ImProStat *self)
{
	ImProStatPrivate *priv = IM_PRO_STAT_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	ImProStatPrivate *self = IM_PRO_STAT_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	ImProStatPrivate *self = IM_PRO_GET_PRIVATE(object);
}


/*PUBLIC*/
/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/********************************************************/
/*	STAT Top												*/
/********************************************************/
/**
STATTOP Macro initialize
@remarks	Please Call at the time of system starting.
*/
void im_pro_stat_stattop_init( ImProStat *self )
{
	// Software release
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.STATTOP.SR.bit.SR = D_IM_PRO_SR_RELEASE;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock
}

/**
STATTOP Macro software reset
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: All macro not stopped NG
*/
INT32 im_pro_stat_stattop_sw_reset( ImProStat *self )
{
#ifdef CO_ACT_PRO_CLOCK
	if (ImProStat_GET_STOP_ALL() == FALSE){	//not ALL Stopped
		Ddim_Print(("I:im_pro_stat_stattop_sw_reset. macro not stopped error. \n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif	/* CO_ACT_PRO_CLOCK */

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock

	// Software reset
	IO_PRO.STAT.STATTOP.SR.bit.SR = D_IM_PRO_SR_RESET;

	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
STATTOP Macro clock control
@param[in]	clkType	: STATTOP Macro clock type
@param[in]	onOff		: 0:clock on 1:clock off
@param[in]	waitSkip	: 0:non wait 1:wait 1ms. for wait PROCLK/CDK 5 cycle.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_stattop_control_clock(ImProStat *self, E_IM_PRO_STATTOP_CLK_TYPE clkType,
		kuchar onOff, kuchar waitSkip )
{
	UINT32 cpu_clk_hz;
	UINT32 macro_clk_hz;
#ifdef CO_PARAM_CHECK
	if (onOff > D_IM_PRO_CLOCK_OFF){
		Ddim_Assertion(("I:im_pro_stat_stattop_control_clock error. onOff value over!! (%d)\n", onOff));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else {
		// DO NOTHING
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock

	switch( clkType ) {
		case E_IM_PRO_STATTOP_CLK_TYPE_STATCLK:
			IO_PRO.STAT.STATTOP.CLKSTP.bit.PSTP1 = ( ( onOff == D_IM_PRO_CLOCK_ON ) ? D_IM_PRO_CLOCK_ON : D_IM_PRO_CLOCK_OFF );
			break;

		default:
			break;
	}
	// waiting for 5 cycle
	if( waitSkip == 0 ) {
		im_pro_get_current_clk_hz( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT, &cpu_clk_hz, &macro_clk_hz );
		im_pro_common_wait_by_clk_cycle( 5, macro_clk_hz, cpu_clk_hz );
#ifndef CO_DEBUG_ON_PC
//			__nop();
#endif
	}

	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
STATTOP macro control data setting
@param[in]	ctrl : STATTOP macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_stattop_ctrl(ImProStat *self, T_IM_PRO_STATTOP_CTRL* ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ctrl == NULL){
		Ddim_Assertion(("I:im_pro_stat_stattop_ctrl error. ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_stat_stattop_control_clock( E_IM_PRO_STATTOP_CLK_TYPE_STATCLK, D_IM_PRO_CLOCK_OFF, 0 );

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.STATTOP.STATTOPCTL1.bit.AFSW0	= ctrl->af_input_sel[0];
	IO_PRO.STAT.STATTOP.STATTOPCTL1.bit.AFSW1	= ctrl->af_input_sel[1];
	IO_PRO.STAT.STATTOP.STATTOPCTL1.bit.FLSW0	= ctrl->flck_input_sel[0];
	IO_PRO.STAT.STATTOP.STATTOPCTL1.bit.FLSW1	= ctrl->flck_input_sel[1];
	IO_PRO.STAT.STATTOP.STATTOPCTL1.bit.AESW0	= ctrl->aeawb_input_sel[0];
	IO_PRO.STAT.STATTOP.STATTOPCTL1.bit.AESW1	= ctrl->aeawb_input_sel[1];
	IO_PRO.STAT.STATTOP.STATTOPCTL1.bit.AESW2	= ctrl->aeawb_input_sel[2];
	IO_PRO.STAT.STATTOP.STATTOPCTL1.bit.AESW3	= ctrl->aeawb_input_sel[3];
	IO_PRO.STAT.STATTOP.STATTOPCTL1.bit.HISW0	= ctrl->hist_input_sel[0];
	IO_PRO.STAT.STATTOP.STATTOPCTL1.bit.HISW1	= ctrl->hist_input_sel[1];
	IO_PRO.STAT.STATTOP.STATTOPCTL1.bit.HISW2	= ctrl->hist_input_sel[2];
	IO_PRO.STAT.STATTOP.STATTOPCTL1.bit.HISW3	= ctrl->hist_input_sel[3];
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	im_pro_stat_stattop_control_clock( E_IM_PRO_STATTOP_CLK_TYPE_STATCLK, D_IM_PRO_CLOCK_ON, 0 );

	return D_DDIM_OK;
}

/**
AEAWB macro start
@retval		D_DDIM_OK				: Processing OK
@retval		D_IM_PRO_MACRO_BUSY_NG	: PWCH not running NG
*/
INT32 im_pro_stat_aeawb_start(ImProStat *self, E_IM_PRO_AEAWB_CH ch )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AEAWB[ch].AETRG.bit.AETRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	ImProStat_SET_START_STATUS(ImProStat_STATUS_AEAWB_0, ch);

	return D_DDIM_OK;
}

/**
AEAWB macro stop
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: PWCH not stopped NG
*/
INT32 im_pro_stat_aeawb_stop(ImProStat *self, E_IM_PRO_AEAWB_CH ch, kuchar force )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	if(force == 0) {
		IO_PRO.STAT.AEAWB[ch].AETRG.bit.AETRG = D_IM_PRO_TRG_FRAME_STOP;	// stop
	}
	else {
		IO_PRO.STAT.AEAWB[ch].AETRG.bit.AETRG = D_IM_PRO_TRG_FORCE_STOP;	// force stop
	}
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	ImProStat_SET_STOP_STATUS(ImProStat_STATUS_AEAWB_0, ch);

	return D_DDIM_OK;
}

/**
AE/AWB data SDRAM write enable set
@param[in]	aeawbCtrl : AEAWB Information @ref T_IM_PRO_AEAWB_CTRL
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_aeawbCtrl(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_CTRL* aeawbCtrl )
{
#ifdef CO_PARAM_CHECK
	if (aeawbCtrl == NULL){
		Ddim_Assertion(("I:im_pro_stat_aeawbCtrl error. aeawbCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AEAWB_AEHBC_MIN,
			D_IM_PRO_AEAWB_AEHBC_MAX, aeawbCtrl->h_bc_num, "im_pro_stat_aeawbCtrl : h_bc_num" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AEAWB_AEVBC_MIN,
			D_IM_PRO_AEAWB_AEVBC_MAX, aeawbCtrl->v_bc_num, "im_pro_stat_aeawbCtrl : v_bc_num" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	if( im_pro_stat_aeawb_set_wd_mode( ch, aeawbCtrl->aeawb_mode ) != D_DDIM_OK ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}

	if( im_pro_stat_aeawb_set_awbdataformat( ch, aeawbCtrl->awb_mode ) != D_DDIM_OK ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}

	if( im_pro_stat_aeawb_set_wd_window_mode( ch, aeawbCtrl->awb_wd_window_mode ) != D_DDIM_OK ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}

	if( im_pro_stat_aeawb_set_area( ch, &aeawbCtrl->awb_area ) != D_DDIM_OK ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}

	if( im_pro_stat_aeawb_set_blocks( ch, aeawbCtrl->h_bc_num, aeawbCtrl->v_bc_num ) != D_DDIM_OK ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of AEAWB.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_aeawb_set_paen(ImProStat *self, E_IM_PRO_AEAWB_CH ch, kuchar paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( IO_PRO.STAT.AEAWB[ch].AETRG.bit.AETRG != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:im_pro_stat_aeawb_set_paen. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AEAWB[ch].AEAWBPAEN.bit.PAEN = paenTrg;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
AWB detect data format select.
@param[in]	awbFormat : AWB detect data format @ref E_IM_PRO_AWB_MODE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_aeawb_set_awbdataformat(ImProStat *self, E_IM_PRO_AEAWB_CH ch,
		E_IM_PRO_AWB_MODE awbFormat )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AEAWB[ch].AEAWBCTL.bit.AWBGMD	= awbFormat;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
AE/AWB detecting mode set
@param[in]	wbMode : AEAWB Detecting mode @ref E_IM_PRO_AEAWB_MODE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_aeawb_set_wd_mode(ImProStat *self, E_IM_PRO_AEAWB_CH ch,
		E_IM_PRO_AEAWB_MODE wbMode )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AEAWB[ch].AEAWBCTL.bit.AEAWBWMD	= wbMode;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
AE/AWB detecting window mode set
@param[in]	wbWinMode : AEAWB Detecting window mode @ref E_IM_PRO_AEAWB_WD_WINDOW_MODE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_aeawb_set_wd_window_mode(ImProStat *self, ImProStat *self, E_IM_PRO_AEAWB_CH ch,
		E_IM_PRO_AEAWB_WD_WINDOW_MODE wbWinMode )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AEAWB[ch].AEAWBCTL.bit.AEEWMD	= wbWinMode;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Set AE/AWB Window size
* @param[in]	aeawbArea :aeawb window information.

@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_aeawb_set_area(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_AREA* aeawbArea )
{
#ifdef CO_PARAM_CHECK
	if (aeawbArea == NULL){
		Ddim_Assertion(("I:im_pro_stat_aeawb_set_area error. aeawbArea=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AEAWB_AEH_MIN,
			D_IM_PRO_AEAWB_AEH_MAX, aeawbArea->pos_x, "im_pro_stat_aeawb_set_area : pos_x" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AEAWB_AEV_MIN, D_IM_PRO_AEAWB_AEV_MAX,
			aeawbArea->pos_y, "im_pro_stat_aeawb_set_area : pos_y" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AEAWB_AEHW_MIN, D_IM_PRO_AEAWB_AEHW_MAX,
			aeawbArea->width, "im_pro_stat_aeawb_set_area : width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AEAWB_AEVW_MIN, D_IM_PRO_AEAWB_AEVW_MAX,
			aeawbArea->lines, "im_pro_stat_aeawb_set_area : lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AEAWB_AETW_MIN, D_IM_PRO_AEAWB_AETW_MAX,
			aeawbArea->top_lines, "im_pro_stat_aeawb_set_area : top_lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AEAWB_AEBW_MIN, D_IM_PRO_AEAWB_AEBW_MAX,
			aeawbArea->bottom_lines, "im_pro_stat_aeawb_set_area : bottom_lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AEAWB_AELW_MIN, D_IM_PRO_AEAWB_AELW_MAX,
			aeawbArea->left_width, "im_pro_stat_aeawb_set_area : left_width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AEAWB_AERW_MIN, D_IM_PRO_AEAWB_AERW_MAX,
			aeawbArea->right_width, "im_pro_stat_aeawb_set_area : right_width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AEAWB[ch].AEH.bit.AEH	= aeawbArea->pos_x;
	IO_PRO.STAT.AEAWB[ch].AEV.bit.AEV	= aeawbArea->pos_y;
	IO_PRO.STAT.AEAWB[ch].AEHW.bit.AEHW	= aeawbArea->width;
	IO_PRO.STAT.AEAWB[ch].AEVW.bit.AEVW	= aeawbArea->lines;
	IO_PRO.STAT.AEAWB[ch].AETW.bit.AETW	= aeawbArea->top_lines;
	IO_PRO.STAT.AEAWB[ch].AEBW.bit.AEBW	= aeawbArea->bottom_lines;
	IO_PRO.STAT.AEAWB[ch].AELW.bit.AELW	= aeawbArea->left_width;
	IO_PRO.STAT.AEAWB[ch].AERW.bit.AERW	= aeawbArea->right_width;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Set AE/AWB Window block number
@param[in]	hBcNum :horizontal AEAWB Window block number<br>
						value range  :[1 - 64]<br>
						target registor  :@@AEHBC<br>
						Note that if level WB is enabled (aeawbMode=E_IM_PRO_AEAWB_MODE_LWB~E_IM_PRO_AEAWB_MODE_AE_AWB_LWB),
						the upper limit of this register is 32.

@param[in]	vBcNum :vertical AEAWB Window block number<br>
					  value range  :[1 - 64]<br>
					  target registor  :@@AEVBC
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32	im_pro_stat_aeawb_set_blocks(ImProStat *self, E_IM_PRO_AEAWB_CH ch, kuint16 hBcNum, kuint16 vBcNum )
{
#ifdef CO_PARAM_CHECK
	if( im_pro_check_val_range( D_IM_PRO_AEAWB_AEHBC_MIN, D_IM_PRO_AEAWB_AEHBC_MAX,
			hBcNum, "im_pro_stat_aeawb_set_blocks : hBcNum" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AEAWB_AEVBC_MIN, D_IM_PRO_AEAWB_AEVBC_MAX,
			vBcNum, "im_pro_stat_aeawb_set_blocks : vBcNum" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AEAWB[ch].AEVBC.bit.AEVBC	= vBcNum;
	IO_PRO.STAT.AEAWB[ch].AEHBC.bit.AEHBC	= hBcNum;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock
	return D_DDIM_OK;
}

/**
Set calculation permission in AE/AWB Window block.
* @param[in]	aeawbCw :AE/AWB Addition permission size in a block information<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_aeawb_set_cw(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_CW* aeawbCw )
{
#ifdef CO_PARAM_CHECK
	if (aeawbCw == NULL){
		Ddim_Assertion(("I:im_pro_stat_aeawb_set_cw error. aeawbCw=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AEAWB[ch].AECW1.bit.AECVW	= aeawbCw->aecvw;
	IO_PRO.STAT.AEAWB[ch].AECW1.bit.AECHW	= aeawbCw->aechw;
	IO_PRO.STAT.AEAWB[ch].AECW2.bit.AECTW	= aeawbCw->aectw;
	IO_PRO.STAT.AEAWB[ch].AECW3.bit.AECBW	= aeawbCw->aecbw;
	IO_PRO.STAT.AEAWB[ch].AECW2.bit.AECLW	= aeawbCw->aeclw;
	IO_PRO.STAT.AEAWB[ch].AECW3.bit.AECRW	= aeawbCw->aecrw;
	IO_PRO.STAT.AEAWB[ch].AWBCW1.bit.AWBCVW	= aeawbCw->awcvw;
	IO_PRO.STAT.AEAWB[ch].AWBCW1.bit.AWBCHW	= aeawbCw->awchw;
	IO_PRO.STAT.AEAWB[ch].AWBCW2.bit.AWBCTW	= aeawbCw->awctw;
	IO_PRO.STAT.AEAWB[ch].AWBCW3.bit.AWBCBW	= aeawbCw->awcbw;
	IO_PRO.STAT.AEAWB[ch].AWBCW2.bit.AWBCLW	= aeawbCw->awclw;
	IO_PRO.STAT.AEAWB[ch].AWBCW3.bit.AWBCRW	= aeawbCw->awcrw;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock
	return D_DDIM_OK;
}

/**
AWB RGB level gate threshold
@param[in]	lvGate	:	AWB RGB gate threshold
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_aeawb_set_lv_gate(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_LV_GATE* lvGate )
{
#ifdef CO_PARAM_CHECK
	if (lvGate == NULL){
		Ddim_Assertion(("I:im_pro_stat_aeawb_set_lv_gate error. lvGate=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AEAWB[ch].AWTDY.bit.AWTDUY	= lvGate->awtduy;
	IO_PRO.STAT.AEAWB[ch].AWTDR.bit.AWTDUR	= lvGate->awtdur;
	IO_PRO.STAT.AEAWB[ch].AWTDG.bit.AWTDUG	= lvGate->awtdug;
	IO_PRO.STAT.AEAWB[ch].AWTDB.bit.AWTDUB	= lvGate->awtdub;
	IO_PRO.STAT.AEAWB[ch].AWTDY.bit.AWTDLY	= lvGate->awtdly;
	IO_PRO.STAT.AEAWB[ch].AWTDR.bit.AWTDLR	= lvGate->awtdlr;
	IO_PRO.STAT.AEAWB[ch].AWTDG.bit.AWTDLG	= lvGate->awtdlg;
	IO_PRO.STAT.AEAWB[ch].AWTDB.bit.AWTDLB	= lvGate->awtdlb;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
AWB matrix level gate threshold
@param[in]	mtLvGate	:AWB Matrix gate
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_aeawb_set_matrix_lv_gate(ImProStat *self, E_IM_PRO_AEAWB_CH ch,
		T_IM_PRO_AEAWB_MATRIX_LV_GATE* mtLvGate )
{
#ifdef CO_PARAM_CHECK
	if (mtLvGate == NULL){
		Ddim_Assertion(("I:im_pro_stat_aeawb_set_matrix_lv_gate error. mtLvGate=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AEAWB[ch].AWMLCY.bit.AWMLUCY	= mtLvGate->awmlucy;
	IO_PRO.STAT.AEAWB[ch].AWMLCY.bit.AWMLLCY	= mtLvGate->awmllcy;
	IO_PRO.STAT.AEAWB[ch].AWMLCB.bit.AWMLUCB	= mtLvGate->awmlucb;
	IO_PRO.STAT.AEAWB[ch].AWMLCB.bit.AWMLLCB	= mtLvGate->awmllcb;
	IO_PRO.STAT.AEAWB[ch].AWMLCR.bit.AWMLUCR	= mtLvGate->awmlucr;
	IO_PRO.STAT.AEAWB[ch].AWMLCR.bit.AWMLLCR	= mtLvGate->awmllcr;
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AWMC.AWMC1, union io_awmc_1, AWMC00, mtLvGate->awmc[0][0] );
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AWMC.AWMC1, union io_awmc_1, AWMC01, mtLvGate->awmc[0][1] );
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AWMC.AWMC2, union io_awmc_2, AWMC02, mtLvGate->awmc[0][2] );
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AWMC.AWMC2, union io_awmc_2, AWMC10, mtLvGate->awmc[1][0] );
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AWMC.AWMC3, union io_awmc_3, AWMC11, mtLvGate->awmc[1][1] );
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AWMC.AWMC3, union io_awmc_3, AWMC12, mtLvGate->awmc[1][2] );
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AWMC.AWMC4, union io_awmc_4, AWMC20, mtLvGate->awmc[2][0] );
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AWMC.AWMC4, union io_awmc_4, AWMC21, mtLvGate->awmc[2][1] );
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AWMC.AWMC5, union io_awmc_5, AWMC22, mtLvGate->awmc[2][2] );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
AE Y coefficient
@param[in]	ch : Channel No.
@param[in]	aeyk	:Luminosity generation coefficient Information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_aeawb_set_aeyk(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_STAT_YK* aeyk )
{
#ifdef CO_PARAM_CHECK
	if (aeyk == NULL){
		Ddim_Assertion(("I:im_pro_stat_aeawb_set_aeyk error. aeyk=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AEYKRR, union io_aeykrr, AEYKRR, aeyk->ykr );
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AEYKGR, union io_aeykgr, AEYKGR, aeyk->ykgr );
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AEYKGB, union io_aeykgb, AEYKGB, aeyk->ykgb );
	im_pro_set_reg_signed( IO_PRO.STAT.AEAWB[ch].AEYKBB, union io_aeykbb, AEYKBB, aeyk->ykb );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Get Luminance generation coefficient.
@param[in]	ch : Channel No.
@param[out]	aeyk	:Luminosity generation coefficient Information
@retval		Luminance generation coefficient.
*/
INT32 im_pro_stat_aeawb_get_aeyk(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_STAT_YK* aeyk )
{
#ifdef CO_PARAM_CHECK
	if (aeyk == NULL){
		Ddim_Assertion(("I:im_pro_stat_aeawb_get_aeyk error. aeyk=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	im_pro_get_reg_signed( aeyk->ykr, IO_PRO.STAT.AEAWB[ch].AEYKRR, union io_aeykrr, AEYKRR );
	im_pro_get_reg_signed( aeyk->ykgr, IO_PRO.STAT.AEAWB[ch].AEYKGR, union io_aeykgr, AEYKGR );
	im_pro_get_reg_signed( aeyk->ykgb, IO_PRO.STAT.AEAWB[ch].AEYKGB, union io_aeykgb, AEYKGB );
	im_pro_get_reg_signed( aeyk->ykb, IO_PRO.STAT.AEAWB[ch].AEYKBB, union io_aeykbb, AEYKBB );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Luminosity is integrated from the specified line in the AEAWB detection Window
@param[in]	lineInfo
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_aeawb_set_lineData_position(ImProStat *self, E_IM_PRO_AEAWB_CH ch,
		T_IM_PRO_AEAWB_LINE_INFO* lineInfo )
{
#ifdef CO_PARAM_CHECK
	if (lineInfo == NULL){
		Ddim_Assertion(("I:im_pro_stat_aeawb_set_lineData_position error. lineInfo=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AEAWB[ch].LINEV.LINEV1.bit.LINEV_0	= lineInfo->start_line[0];
	IO_PRO.STAT.AEAWB[ch].LINEV.LINEV1.bit.LINEV_1	= lineInfo->start_line[1];
	IO_PRO.STAT.AEAWB[ch].LINEV.LINEV2.bit.LINEV_2	= lineInfo->start_line[2];
	IO_PRO.STAT.AEAWB[ch].LINEV.LINEV2.bit.LINEV_3	= lineInfo->start_line[3];
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Get flicker result line data. Result is kulong [4] address.
@retval		line data Result address.
*/
INT32 im_pro_stat_aeawb_get_lineData(ImProStat *self, E_IM_PRO_AEAWB_CH ch, kulong* lineData )
{
#ifdef CO_PARAM_CHECK
	if (lineData == NULL){
		Ddim_Assertion(("I:im_pro_stat_aeawb_get_lineData error. lineData=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	lineData[0]	= IO_PRO.STAT.AEAWB[ch].LINEDATA.LINEDATA1.bit.LINEDATA_0;
	lineData[1]	= IO_PRO.STAT.AEAWB[ch].LINEDATA.LINEDATA2.bit.LINEDATA_1;
	lineData[2]	= IO_PRO.STAT.AEAWB[ch].LINEDATA.LINEDATA3.bit.LINEDATA_2;
	lineData[3]	= IO_PRO.STAT.AEAWB[ch].LINEDATA.LINEDATA4.bit.LINEDATA_3;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Get AE Data
@retval		AE Data Address	:	AE Data Storing Area Address
*/
kulong im_pro_stat_aeawb_get_aeawbdata(ImProStat *self, E_IM_PRO_AEAWB_CH ch )
{
	return im_pro_comm_get_stat_cur_data_addr( ch );
}

/**
Get AE Data last VD for AFE long exposure
@retval		kulong AE Data Storing Area Address for AFE long exposure
*/
kulong im_pro_stat_aeawb_get_lastaeawbdata(ImProStat *self, E_IM_PRO_AEAWB_CH ch )
{
	return im_pro_comm_get_stat_last_data_addr( ch );
}

/**
Get Wave Detection Data information
@param[in/out]	wdInfo : Wave Detection Data information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat_aeawb_get_wdInfo(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_WD_INFO* wdInfo )
{
	kulong data_addr = 0;
	kuchar detect_mode = 0;
	kuchar bit1_num = 0;
	kuchar bit2_num = 0;
	kuchar bit3_num = 0;
	kuchar dummy_size = 0;

#ifdef CO_PARAM_CHECK
	if (wdInfo == NULL){
		Ddim_Assertion(("I:im_pro_stat_aeawb_get_wdInfo error. wdInfo=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// For the representation of the mode with the bit( bit1 => ON )
	// IAWB  AWB  AE
	//   0    0    1  = 1d
	//   0    1    0  = 2d
	//   0    1    1  = 3d
	//   1    0    0  = 4d
	//   1    0    1  = 5d
	//   1    1    0  = 6d
	//   1    1    1  = 7d
	detect_mode = wdInfo->mode + 1;

	bit1_num = ( detect_mode & 0x1 );		// AE
	bit2_num = ( detect_mode & 0x2 ) >> 1;	// AWB
	bit3_num = ( detect_mode & 0x4 ) >> 2;	// IAWB

	dummy_size = ( ( wdInfo->aehbc % 2) * ImProStat_AEAEB_DUMMY_DATA_SIZE );

	// Calc Global data width
	*wdInfo->global_data_width = ( bit1_num * wdInfo->aehbc * ImProStat_AEAEB_AE_BLK_SIZE )
								  + ( bit2_num * wdInfo->aehbc * ImProStat_AEAEB_AWB_BLK_SIZE )
								  + ( bit3_num * wdInfo->aehbc * ImProStat_AEAEB_IAWB_BLK_SIZE )
								  + dummy_size;

	// Calc Address
	data_addr = im_pro_comm_get_stat_cur_data_addr( ch );

	switch( wdInfo->type ) {
		case E_IM_PRO_AEAWB_TYPE_AWB:
			{
				data_addr = data_addr + ( bit1_num * wdInfo->aehbc * ImProStat_AEAEB_AE_BLK_SIZE )
									  +   dummy_size;
			}
			break;

		case E_IM_PRO_AEAWB_TYPE_LAWB:
			{
				data_addr = data_addr + ( bit1_num * wdInfo->aehbc * ImProStat_AEAEB_AE_BLK_SIZE )
									  + ( bit2_num * wdInfo->aehbc * ImProStat_AEAEB_AWB_BLK_SIZE )
									  +   dummy_size;
			}
			break;

		case E_IM_PRO_AEAWB_TYPE_AE:
		default:
			{
				// to do nothing
			}
			break;
	}
	*wdInfo->address = data_addr;

	return D_DDIM_OK;
}

/**
AF macro start
*/
void im_pro_stat_af_start(ImProStat *self, E_IM_PRO_AF_CH ch )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AF[ch].AFGBAL.AFTRG.bit.AFTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	ImProStat_SET_START_STATUS(ImProStat_STATUS_AF_0, ch);
}

/**
AF macro stop
@param[in]	force : force stop option
*/
void im_pro_stat_af_stop(ImProStat *self, E_IM_PRO_AF_CH ch, kuchar force )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	if(force == 0) {
		IO_PRO.STAT.AF[ch].AFGBAL.AFTRG.bit.AFTRG = D_IM_PRO_TRG_FRAME_STOP;	// stop
	}
	else {
		IO_PRO.STAT.AF[ch].AFGBAL.AFTRG.bit.AFTRG = D_IM_PRO_TRG_FORCE_STOP;	// force stop
	}
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	ImProStat_SET_STOP_STATUS(ImProStat_STATUS_AF_0, ch);
}

/**
AF Information Setting
@param[in]	afCtrl	:	Window Information See @ref T_IM_PRO_AF_CTRL<br>
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_AF_INPUT_PARAM_ERROR	: Setting NG
@code
// sample code
	int i;
	//---- Set AF Information ----
	T_IM_PRO_AF_CTRL afCtrl;

	afCtrl.eval_calc0_enable = E_IM_PRO_AF_ENABLE_EN;
	afCtrl.eval_calc1_enable = E_IM_PRO_AF_ENABLE_EN;
	afCtrl.eval_calc2_enable = E_IM_PRO_AF_ENABLE_EN;
	afCtrl.vertical_enable   = E_IM_PRO_AF_ENABLE_EN;
	afCtrl.horizon0_enable   = E_IM_PRO_AF_ENABLE_EN;
	afCtrl.horizon1_enable   = E_IM_PRO_AF_ENABLE_EN;
	afCtrl.horizon2_enable   = E_IM_PRO_AF_ENABLE_EN;
	for (i = E_IM_PRO_AF_WINDOW_1; i < E_IM_PRO_AF_WINDOW_MAX; i ++){
		afCtrl.enable[i] = E_IM_PRO_AF_ENABLE_EN;
	}

	im_pro_stat_afctrl(&afCtrl);
@endcode
*/
INT32 im_pro_stat_afctrl(ImProStat *self, E_IM_PRO_AF_CH ch, T_IM_PRO_AF_CTRL* afCtrl )
{
#ifdef CO_PARAM_CHECK
	if (afCtrl == NULL){
		Ddim_Assertion(("I:im_pro_stat_afctrl error. afCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (afCtrl->eval_calc0_enable == 0){
		Ddim_Assertion(("I:im_pro_stat_afctrl error. setting 0 to eval_calc0_enable is inhibition.\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (afCtrl->horizon0_enable == 0){
		Ddim_Assertion(("I:im_pro_stat_afctrl error. setting 0 to horizon0_enable is inhibition.\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( ( IO_PRO.STAT.STATTOP.CLKSTP.bit.PSTP1 == D_IM_PRO_CLOCK_OFF ) || ( IO_PRO.STAT.AF[ch].AFGBAL.AFTRG.bit.AFTRG != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:im_pro_stat_afctrl error. macro has not stopped or clock stopped.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENM0	= afCtrl->eval_calc0_enable;
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENM1	= afCtrl->eval_calc1_enable;
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENM2	= afCtrl->eval_calc2_enable;
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENV0	= afCtrl->vertical_enable;
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENH0	= afCtrl->horizon0_enable;
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENH1	= afCtrl->horizon1_enable;
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENH2	= afCtrl->horizon2_enable;
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW0	= afCtrl->enable[0];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW1	= afCtrl->enable[1];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW2	= afCtrl->enable[2];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW3	= afCtrl->enable[3];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW4	= afCtrl->enable[4];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW5	= afCtrl->enable[5];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW6	= afCtrl->enable[6];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW7	= afCtrl->enable[7];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW8	= afCtrl->enable[8];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW9	= afCtrl->enable[9];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW10	= afCtrl->enable[10];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW11	= afCtrl->enable[11];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW12	= afCtrl->enable[12];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW13	= afCtrl->enable[13];
	IO_PRO.STAT.AF[ch].AFGBAL.AFEBEN.bit.ENW14	= afCtrl->enable[14];
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

ImProStat* im_pro_stat_new(void)
{
	ImProStat *self = g_object_new(IM_TYPE_PRO_STAT, NULL);
	return self;
}
