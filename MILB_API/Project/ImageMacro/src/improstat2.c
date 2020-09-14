/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-8-5 (发布日期)
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
#include "im_pro_common.h"
#include "dd_top.h"
#include "improstat2.h"


G_DEFINE_TYPE(ImProStat2, im_pro_stat2, G_TYPE_OBJECT);
#define IM_PRO_STAT2_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_PRO_STAT2, ImProStat2Private));


struct _ImProStat2Private{

};


/*DECLS*/
static void 					dispose_od(GObject *object);
static void 					finalize_od(GObject *object);


/*IMPL*/
static void im_pro_stat2_class_init(ImProStat2Class *klass)
{
	g_type_class_add_private(klass, sizeof(ImProStat2Private));
}

static void im_pro_stat2_init(ImProStat2 *self)
{
	ImProStat2Private *priv = IM_PRO_STAT2_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	ImProStat2Private *self = IM_PRO_STAT2_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	ImProStat2Private *self = IM_PRO_STAT2_GET_PRIVATE(object);
}


/*PUBLIC*/
/**
HIST macro start
@param[in]	ch : Channel No.
@retval		D_DDIM_OK				: Processing OK
@retval		D_IM_PRO_MACRO_BUSY_NG	: PWCH not running NG
*/
INT32 im_pro_stat2_hist_start(ImProStat2 *self, E_IM_PRO_HIST_CH ch )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.HIST[ch].HISTTRG.bit.HISTTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	ImProStat_SET_START_STATUS(ImProStat_STATUS_HIST_0, ch);

	return D_DDIM_OK;
}

/**
HIST macro stop
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: PWCH not stopped NG
*/
INT32 im_pro_stat2_hist_stop(ImProStat2 *self, E_IM_PRO_HIST_CH ch, UCHAR force )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	if(force == 0) {
		IO_PRO.STAT.HIST[ch].HISTTRG.bit.HISTTRG = D_IM_PRO_TRG_FRAME_STOP;	// stop
	}
	else {
		IO_PRO.STAT.HIST[ch].HISTTRG.bit.HISTTRG = D_IM_PRO_TRG_FORCE_STOP;	// force stop
	}
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	ImProStat_SET_STOP_STATUS(ImProStat_STATUS_HIST_0, ch);

	return D_DDIM_OK;
}

/**
HIST detecting information set
@param[in]	ch : Channel No.
@param[in]	histCtrl : HIST Information @ref T_IM_PRO_HIST_CTRL
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_hist_ctrl(ImProStat2 *self, E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_CTRL* histCtrl )
{
#ifdef CO_PARAM_CHECK
	if (histCtrl == NULL){
		Ddim_Assertion(("I:im_pro_stat2_hist_ctrl error. histCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.HIST[ch].HISTCTL.bit.HISTCT		= histCtrl->hist_mode;
	IO_PRO.STAT.HIST[ch].HISTCTL.bit.HISTHCYC	= histCtrl->histCycle;
	IO_PRO.STAT.HIST[ch].HISTCTL.bit.HISTSUMS	= histCtrl->hist_shift_val;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of HIST.
@param[in]	ch : Channel No.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_hist_set_paen(ImProStat2 *self, E_IM_PRO_HIST_CH ch, UCHAR paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( IO_PRO.STAT.HIST[ch].HISTTRG.bit.HISTTRG != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:im_pro_stat2_hist_set_paen. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.HIST[ch].HISTPAEN.bit.PAEN	= paenTrg;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
HIST detecting mode set
@param[in]	ch : Channel No.
@param[in]	histCycle : HIST horizontal subsampling cycle. @ref E_IM_PRO_HIST_CYCLE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_hist_set_h_cycle(ImProStat2 *self, E_IM_PRO_HIST_CH ch, E_IM_PRO_HIST_CYCLE histCycle )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.HIST[ch].HISTCTL.bit.HISTHCYC	= histCycle;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Set HIST Window size
@param[in]	ch : Channel No.
@param[in]	histArea : HIST window information<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_hist_set_area(ImProStat2 *self, E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_AREA* histArea )
{
#ifdef CO_PARAM_CHECK
	if (histArea == NULL){
		Ddim_Assertion(("I:im_pro_stat2_hist_set_area error. histArea=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_HIST_HISTH_MIN,
			D_IM_PRO_HIST_HISTH_MAX, histArea->pos_x, "im_pro_stat2_hist_set_area : pos_x" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_HIST_HISTV_MIN,
			D_IM_PRO_HIST_HISTV_MAX, histArea->pos_y, "im_pro_stat2_hist_set_area : pos_y" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_HIST_HISTHW_MIN,
			D_IM_PRO_HIST_HISTHW_MAX, histArea->width, "im_pro_stat2_hist_set_area : width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_HIST_HISTVW_MIN,
			D_IM_PRO_HIST_HISTVW_MAX, histArea->lines, "im_pro_stat2_hist_set_area : lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.HIST[ch].HISTH.bit.HISTH	= histArea->pos_x;
	IO_PRO.STAT.HIST[ch].HISTV.bit.HISTV	= histArea->pos_y;
	IO_PRO.STAT.HIST[ch].HISTHW.bit.HISTHW	= histArea->width;
	IO_PRO.STAT.HIST[ch].HISTVW.bit.HISTVW	= histArea->lines;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Set HIST Window size
@param[in]	ch : Channel No.
@param[in]	histGain : HIST window information<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_hist_set_gain(ImProStat2 *self, E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_GAIN* histGain )
{
#ifdef CO_PARAM_CHECK
	if (histGain == NULL){
		Ddim_Assertion(("I:im_pro_stat2_hist_set_gain error. histGain=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.HIST[ch].HISTWBGR.bit.HISTWBGR	= histGain->r_gain;
	IO_PRO.STAT.HIST[ch].HISTWBGG.bit.HISTWBGG	= histGain->g_gain;
	IO_PRO.STAT.HIST[ch].HISTWBGB.bit.HISTWBGB	= histGain->b_gain;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
HIST Y coefficient
@param[in]	ch : Channel No.
@param[in]	histyk	:Luminosity generation coefficient Information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_hist_set_histyk(ImProStat2 *self, E_IM_PRO_HIST_CH ch, T_IM_PRO_STAT_YK* histyk )
{
#ifdef CO_PARAM_CHECK
	if (histyk == NULL){
		Ddim_Assertion(("I:im_pro_stat2_hist_set_histyk error. histyk=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	im_pro_set_reg_signed( IO_PRO.STAT.HIST[ch].HISTYKRR, union io_histykrr, HISTYKRR, histyk->ykr );
	im_pro_set_reg_signed( IO_PRO.STAT.HIST[ch].HISTYKGR, union io_histykgr, HISTYKGR, histyk->ykgr );
	im_pro_set_reg_signed( IO_PRO.STAT.HIST[ch].HISTYKGB, union io_histykgb, HISTYKGB, histyk->ykgb );
	im_pro_set_reg_signed( IO_PRO.STAT.HIST[ch].HISTYKBB, union io_histykbb, HISTYKBB, histyk->ykb );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Get HIST result Data
@param[in]	ch : Channel No.
@param[out]	histData :Histgram result value inside the HIST window.
*/
INT32 im_pro_stat2_hist_get_hist_data(ImProStat2 *self, E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_DATA* histData )
{
#ifdef CO_PARAM_CHECK
	if (histData == NULL){
		Ddim_Assertion(("I:im_pro_stat2_hist_get_hist_data error. histData=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_comm_get_hist_result(ch, histData);

	return D_DDIM_OK;
}

INT32 im_pro_stat2_hist_get_hist_ram(ImProStat2 *self, E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_RAM_DATA* histRamData )
{
#ifdef CO_PARAM_CHECK
	if (histRamData == NULL){
		Ddim_Assertion(("I:im_pro_stat2_hist_get_hist_ram error. histRamData=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_comm_get_hist_ram(ch, histRamData);

	return D_DDIM_OK;
}

/**
FLCK macro start
@param[in]	ch : Channel No.
@retval		D_DDIM_OK				: Processing OK
@retval		D_IM_PRO_MACRO_BUSY_NG	: PWCH not running NG
*/
INT32 im_pro_stat2_flck_start(ImProStat2 *self, E_IM_PRO_FLCK_CH ch )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.FLCK[ch].FLTRG.bit.FLTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	ImProStat_SET_START_STATUS(ImProStat_STATUS_FLCK_0, ch);

	return D_DDIM_OK;
}

/**
FLCK macro stop
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: PWCH not stopped NG
*/
INT32 im_pro_stat2_flck_stop(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, UCHAR force )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	if(force == 0) {
		IO_PRO.STAT.FLCK[ch].FLTRG.bit.FLTRG = D_IM_PRO_TRG_FRAME_STOP;	// stop
	}
	else {
		IO_PRO.STAT.FLCK[ch].FLTRG.bit.FLTRG = D_IM_PRO_TRG_FORCE_STOP;	// force stop
	}
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	ImProStat_SET_STOP_STATUS(ImProStat_STATUS_FLCK_0, ch);

	return D_DDIM_OK;
}

/**
FLCK detecting information set
@param[in]	ch : Channel No.
@param[in]	flckCtrl : FLCK Information @ref T_IM_PRO_FLCK_CTRL
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_flck_ctrl(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_CTRL* flckCtrl )
{
#ifdef CO_PARAM_CHECK
	if (flckCtrl == NULL){
		Ddim_Assertion(("I:im_pro_stat2_flck_ctrl error. flckCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FLCK_FLCVW_MIN,
			D_IM_PRO_FLCK_FLCVW_MAX, flckCtrl->flcvw, "im_pro_stat2_flck_ctrl : flcvw" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FLCK_FLBC_MIN,
			D_IM_PRO_FLCK_FLBC_MAX, flckCtrl->bcNum, "im_pro_stat2_flck_ctrl : bcNum" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.FLCK[ch].FLCKCTL.bit.FLWPMD	= flckCtrl->flck_type;
	IO_PRO.STAT.FLCK[ch].FLCKCTL.bit.FLWLMD	= flckCtrl->flckMode;
	IO_PRO.STAT.FLCK[ch].FLVW.bit.FLCVW		= flckCtrl->flcvw;
	IO_PRO.STAT.FLCK[ch].FLBC.bit.FLBC		= flckCtrl->bcNum;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
FLCK detect data format select.
@param[in]	ch : Channel No.
@param[in]	flckFormat : FLCK detect data format @ref E_IM_PRO_FLCK_TYPE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_flck_set_flckdataformat(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, E_IM_PRO_FLCK_TYPE flckFormat )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.FLCK[ch].FLCKCTL.bit.FLWPMD	= flckFormat;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
FLCK detecting mode set
@param[in]	ch : Channel No.
@param[in]	flckMode : FLCK Detecting mode @ref E_IM_PRO_FLCK_MODE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_flck_set_wd_mode(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, E_IM_PRO_FLCK_MODE flckMode )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.FLCK[ch].FLCKCTL.bit.FLWLMD	= flckMode;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Set FLCK Window size
@param[in]	ch : Channel No.
@param[in]	flckArea : flck window information<br>
						value range :[0 - 8190] 2pixel boundary<br>
						target registor :@@FLH<br>
						value range :[0 - 8190] 2pixel boundary<br>
						target registor :@@FLV<br>
						value range :[6 - 8192] 2pixel boundary<br>
						target registor :@@FLHW<br>
						value range :[2 - 1024] 2pixel boundary(FLWLMD=0)<br>
												4pixel boundary(FLWLMD=1)<br>
						target registor :@@FLVW<br>

@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_flck_set_area(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_AREA* flckArea )
{
#ifdef CO_PARAM_CHECK
	if (flckArea == NULL){
		Ddim_Assertion(("I:im_pro_stat2_flck_set_area error. flckArea=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FLCK_FLH_MIN, D_IM_PRO_FLCK_FLH_MAX,
			flckArea->pos_x, "im_pro_stat2_flck_set_area : pos_x" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FLCK_FLV_MIN, D_IM_PRO_FLCK_FLV_MAX,
			flckArea->pos_y, "im_pro_stat2_flck_set_area : pos_y" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FLCK_FLHW_MIN, D_IM_PRO_FLCK_FLHW_MAX,
			flckArea->width, "im_pro_stat2_flck_set_area : width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FLCK_FLVW_MIN, D_IM_PRO_FLCK_FLVW_MAX,
			flckArea->lines, "im_pro_stat2_flck_set_area : lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.FLCK[ch].FLH.bit.FLH	= flckArea->pos_x;
	IO_PRO.STAT.FLCK[ch].FLV.bit.FLV	= flckArea->pos_y;
	IO_PRO.STAT.FLCK[ch].FLHW.bit.FLHW	= flckArea->width;
	IO_PRO.STAT.FLCK[ch].FLVW.bit.FLVW	= flckArea->lines;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Set FLCK Window block number
@param[in]	ch : Channel No.
@param[in]	bcNum :FLCK Window block number<br>
					value range :[1 - 4096]<br>
					target registor :@@FLBC<br>

@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_flck_set_blocks(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, USHORT bcNum )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.FLCK[ch].FLBC.bit.FLBC	= bcNum;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Set calculation permission in FLCK Window block
@param[in]	ch : Channel No.
@param[in]	flcvw : FLCK Addition permission size in a block information<br>
					 value range :[2 - 1024] 2pixel boundary(FLWLMD=0)<br>
											 4pixel boundary(FLWLMD=1)<br>
					 target registor :@@FLCVW<br>

@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_flck_set_cw(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, USHORT flcvw )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.FLCK[ch].FLVW.bit.FLCVW	= flcvw;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
FLCK RGB level gate threshold
@param[in]	ch : Channel No.
@param[in]	lvGate	:	FLCK RGB gate threshold
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_flck_set_lv_gate(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_LV_GATE* lvGate )
{
#ifdef CO_PARAM_CHECK
	if (lvGate == NULL){
		Ddim_Assertion(("I:im_pro_stat2_flck_set_lv_gate error. lvGate=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.FLCK[ch].FLTDY.bit.FLTDUY	= lvGate->fltduy;
	IO_PRO.STAT.FLCK[ch].FLTDR.bit.FLTDUR	= lvGate->fltdur;
	IO_PRO.STAT.FLCK[ch].FLTDG.bit.FLTDUG	= lvGate->fltdug;
	IO_PRO.STAT.FLCK[ch].FLTDB.bit.FLTDUB	= lvGate->fltdub;
	IO_PRO.STAT.FLCK[ch].FLTDY.bit.FLTDLY	= lvGate->fltdly;
	IO_PRO.STAT.FLCK[ch].FLTDR.bit.FLTDLR	= lvGate->fltdlr;
	IO_PRO.STAT.FLCK[ch].FLTDG.bit.FLTDLG	= lvGate->fltdlg;
	IO_PRO.STAT.FLCK[ch].FLTDB.bit.FLTDLB	= lvGate->fltdlb;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
FLCK matrix level gate threshold
@param[in]	ch : Channel No.
@param[in]	mtLvGate	:FLCK Matrix gate
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_flck_set_matrix_lv_gate(ImProStat2 *self, E_IM_PRO_FLCK_CH ch,
		T_IM_PRO_FLCK_MATRIX_LV_GATE* mtLvGate )
{
#ifdef CO_PARAM_CHECK
	if (mtLvGate == NULL){
		Ddim_Assertion(("I:im_pro_stat2_flck_set_matrix_lv_gate error. mtLvGate=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.FLCK[ch].FLMLCY.bit.FLMLUCY		= mtLvGate->flmlucy;
	IO_PRO.STAT.FLCK[ch].FLMLCY.bit.FLMLLCY		= mtLvGate->flmllcy;
	IO_PRO.STAT.FLCK[ch].FLMLCB.bit.FLMLUCB		= mtLvGate->flmlucb;
	IO_PRO.STAT.FLCK[ch].FLMLCB.bit.FLMLLCB		= mtLvGate->flmllcb;
	IO_PRO.STAT.FLCK[ch].FLMLCR.bit.FLMLUCR		= mtLvGate->flmlucr;
	IO_PRO.STAT.FLCK[ch].FLMLCR.bit.FLMLLCR		= mtLvGate->flmllcr;
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLMC.FLMC1, union io_flmc_1, FLMC00, mtLvGate->flmc[0][0] );
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLMC.FLMC1, union io_flmc_1, FLMC01, mtLvGate->flmc[0][1] );
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLMC.FLMC2, union io_flmc_2, FLMC02, mtLvGate->flmc[0][2] );
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLMC.FLMC2, union io_flmc_2, FLMC10, mtLvGate->flmc[1][0] );
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLMC.FLMC3, union io_flmc_3, FLMC11, mtLvGate->flmc[1][1] );
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLMC.FLMC3, union io_flmc_3, FLMC12, mtLvGate->flmc[1][2] );
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLMC.FLMC4, union io_flmc_4, FLMC20, mtLvGate->flmc[2][0] );
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLMC.FLMC4, union io_flmc_4, FLMC21, mtLvGate->flmc[2][1] );
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLMC.FLMC5, union io_flmc_5, FLMC22, mtLvGate->flmc[2][2] );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
FLCK Y coefficient
@param[in]	ch : Channel No.
@param[in]	flckyk	:Luminosity generation coefficient Information

@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat2_flck_set_flyk(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, T_IM_PRO_STAT_YK* flckyk )
{
#ifdef CO_PARAM_CHECK
	if (flckyk == NULL){
		Ddim_Assertion(("I:im_pro_stat2_flck_set_flyk error. flckyk=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLYKRR, union io_flykrr, FLYKRR, flckyk->ykr );
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLYKGR, union io_flykgr, FLYKGR, flckyk->ykgr );
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLYKGB, union io_flykgb, FLYKGB, flckyk->ykgb );
	im_pro_set_reg_signed( IO_PRO.STAT.FLCK[ch].FLYKBB, union io_flykbb, FLYKBB, flckyk->ykb );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Get FLCK Data
@retval		FLCK Data Address	:	FLCK Data Storing Area Address
*/
ULONG im_pro_stat2_flck_get_flckdata(ImProStat2 *self, E_IM_PRO_FLCK_CH ch )
{
	UCHAR	flck_pwch_ch = 0;
	if( ch == E_IM_PRO_FLCK_CH0 ) {
		flck_pwch_ch = ImProStat_FLCK0_PWCH;
	}
	else {
		flck_pwch_ch = ImProStat_FLCK1_PWCH;
	}

	return im_pro_comm_get_stat_cur_data_addr( flck_pwch_ch );
}

/**
Get FLCK Last Data
@param[in]	ch : Channel No.
@retval		FLCK Data Address	:	FLCK Data Storing Area Address(Last address)
*/
ULONG im_pro_stat2_flck_get_lastflckdata(ImProStat2 *self, E_IM_PRO_FLCK_CH ch )
{
	UCHAR	flck_pwch_ch = 0;
	if( ch == E_IM_PRO_FLCK_CH0 ) {
		flck_pwch_ch = ImProStat_FLCK0_PWCH;
	}
	else {
		flck_pwch_ch = ImProStat_FLCK1_PWCH;
	}
	return im_pro_comm_get_stat_last_data_addr( flck_pwch_ch );
}

ImProStat2* im_pro_stat2_new(void)
{
	ImProStat2 *self = g_object_new(IM_TYPE_PRO_STAT2, NULL);
	return self;
}
