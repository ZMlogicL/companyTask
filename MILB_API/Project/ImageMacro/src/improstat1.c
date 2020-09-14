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
#include "improcommon.h"
#include "ddtop.h"
#include "impro.h"
#include "improstat1.h"


G_DEFINE_TYPE(ImProStat1, im_pro_stat1, G_TYPE_OBJECT);
#define IM_PRO_STAT1_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_PRO_STAT1, ImProStat1Private));


struct _ImProStat1Private{

};


/*DECLS*/
static void 					dispose_od(GObject *object);
static void 					finalize_od(GObject *object);


/*IMPL*/
static void im_pro_stat1_class_init(ImProStat1Class *klass)
{
	g_type_class_add_private(klass, sizeof(ImProStat1Private));
}

static void im_pro_stat1_init(ImProStat1 *self)
{
	ImProStat1Private *priv = IM_PRO_STAT1_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	ImProStat1Private *self = IM_PRO_STAT1_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	ImProStat1Private *self = IM_PRO_STAT1_GET_PRIVATE(object);
}


/*PUBLIC*/
/**
A setup of enable access to the built-in RAM of AF.
@param[in]	paenTrg : RAM access control<br>
			value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat1_af_set_paen(ImProStat1 *self, E_IM_PRO_AF_CH ch, kuchar paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( IO_PRO.STAT.AF[ch].AFGBAL.AFTRG.bit.AFTRG != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:im_pro_stat1_af_set_paen. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AF[ch].AFGBAL.AFPAEN.bit.AFPAEN	= paenTrg;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock
	return D_DDIM_OK;
}

/**
Set AF Global Window
@param[in]	globalWin :AF global area information<br>
							value range :pos_x[0 - 8190](Multiples of 2)<br>
							target registor :@@AFGH<br>
							value range :pos_y[0 - 8190](Multiples of 2)<br>
							target registor :@@AFGV<br>
							value range :width[2 - 4480] 2pixel boundary<br>
							target registor :@@AFGHW<br>
							value range :lines[2 - 8192] 2pixel boundary<br>
							target registor :@@AFGVW<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@attention	None
*/
INT32 im_pro_stat1_af_set_global_area(ImProStat1 *self, E_IM_PRO_AF_CH ch, T_IM_PRO_AREA_INFO* globalWin )
{
#ifdef CO_PARAM_CHECK
	if (globalWin == NULL){
		Ddim_Assertion(("I:im_pro_stat1_af_set_global_area error. globalWin=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AF_AFGH_MIN, D_IM_PRO_AF_AFGH_MAX,
			globalWin->pos_x, "im_pro_stat1_af_set_global_area : pos_x" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AF_AFGV_MIN, D_IM_PRO_AF_AFGV_MAX,
			globalWin->pos_y, "im_pro_stat1_af_set_global_area : pos_y" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AF_AFGHW_MIN, D_IM_PRO_AF_AFGHW_MAX,
			globalWin->width, "im_pro_stat1_af_set_global_area : width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AF_AFGVW_MIN, D_IM_PRO_AF_AFGVW_MAX,
			globalWin->lines, "im_pro_stat1_af_set_global_area : lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AF[ch].AFGBAL.AFGH.bit.AFGH		= globalWin->pos_x;
	IO_PRO.STAT.AF[ch].AFGBAL.AFGV.bit.AFGV		= globalWin->pos_y;
	IO_PRO.STAT.AF[ch].AFGBAL.AFGHW.bit.AFGHW	= globalWin->width;
	IO_PRO.STAT.AF[ch].AFGBAL.AFGVW.bit.AFGVW	= globalWin->lines;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock
	return D_DDIM_OK;
}

/**
AF Surface color Information
@param[in]	unitNo	:				Evaluated value calculation unit number. See @ref E_IM_PRO_AF_EVAL_CALC_UNIT<br>
@param[in]	afEvalCalcCtrl	:	Evaluated value calculation unit Information. See @ref T_IM_PRO_AF_EVAL_CALC_CTRL<br>
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_AF_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat1_af_ctrl_eval_calc(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_EVAL_CALC_UNIT unitNo,
		T_IM_PRO_AF_EVAL_CALC_CTRL* afEvalCalcCtrl )
{
#ifdef CO_PARAM_CHECK
	if (afEvalCalcCtrl == NULL){
		Ddim_Assertion(("I:im_pro_stat1_af_ctrl_eval_calc error. afEvalCalcCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFMTRXRR,
			union io_afmtrxrr, AFMTRXRR, afEvalCalcCtrl->r );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFMTRXGR,
			union io_afmtrxgr, AFMTRXGR, afEvalCalcCtrl->gr );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFMTRXGB,
			union io_afmtrxgb, AFMTRXGB, afEvalCalcCtrl->gb );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFMTRXBB,
			union io_afmtrxbb, AFMTRXBB, afEvalCalcCtrl->b );
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFMDEN.bit.AFMDEN				= afEvalCalcCtrl->median_enable;
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNEN.bit.AFKNEN				= afEvalCalcCtrl->knee_enable;
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNB.AFKNB1.bit.AFKNB_1			= afEvalCalcCtrl->knee_boundary[0];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNB.AFKNB1.bit.AFKNB_2			= afEvalCalcCtrl->knee_boundary[1];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNB.AFKNB2.bit.AFKNB_3			= afEvalCalcCtrl->knee_boundary[2];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNB.AFKNB2.bit.AFKNB_4			= afEvalCalcCtrl->knee_boundary[3];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNB.AFKNB3.bit.AFKNB_5			= afEvalCalcCtrl->knee_boundary[4];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNB.AFKNB3.bit.AFKNB_6			= afEvalCalcCtrl->knee_boundary[5];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNB.AFKNB4.bit.AFKNB_7			= afEvalCalcCtrl->knee_boundary[6];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNINC.AFKNINC1.bit.AFKNINC_0	= afEvalCalcCtrl->knee_slope[0];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNINC.AFKNINC1.bit.AFKNINC_1	= afEvalCalcCtrl->knee_slope[1];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNINC.AFKNINC2.bit.AFKNINC_2	= afEvalCalcCtrl->knee_slope[2];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNINC.AFKNINC2.bit.AFKNINC_3	= afEvalCalcCtrl->knee_slope[3];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNINC.AFKNINC3.bit.AFKNINC_4	= afEvalCalcCtrl->knee_slope[4];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNINC.AFKNINC3.bit.AFKNINC_5	= afEvalCalcCtrl->knee_slope[5];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNINC.AFKNINC4.bit.AFKNINC_6	= afEvalCalcCtrl->knee_slope[6];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNINC.AFKNINC4.bit.AFKNINC_7	= afEvalCalcCtrl->knee_slope[7];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNOFS.AFKNOFS1.bit.AFKNOFS_0	= afEvalCalcCtrl->knee_offset[0];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNOFS.AFKNOFS1.bit.AFKNOFS_1	= afEvalCalcCtrl->knee_offset[1];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNOFS.AFKNOFS2.bit.AFKNOFS_2	= afEvalCalcCtrl->knee_offset[2];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNOFS.AFKNOFS2.bit.AFKNOFS_3	= afEvalCalcCtrl->knee_offset[3];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNOFS.AFKNOFS3.bit.AFKNOFS_4	= afEvalCalcCtrl->knee_offset[4];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNOFS.AFKNOFS3.bit.AFKNOFS_5	= afEvalCalcCtrl->knee_offset[5];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNOFS.AFKNOFS4.bit.AFKNOFS_6	= afEvalCalcCtrl->knee_offset[6];
	IO_PRO.STAT.AF[ch].AFMAIN[unitNo].AFKNOFS.AFKNOFS4.bit.AFKNOFS_7	= afEvalCalcCtrl->knee_offset[7];
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
AF Vertical detection Information
@param[in]	afVerticalCtrl	:	Vertical detection Information See @ref T_IM_PRO_AF_VERTICAL_CTRL<br>
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_AF_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat1_af_ctrl_vertical(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		T_IM_PRO_AF_VERTICAL_CTRL* afVerticalCtrl )
{
#ifdef CO_PARAM_CHECK
	if (afVerticalCtrl == NULL){
		Ddim_Assertion(("I:im_pro_stat1_af_ctrl_vertical error. afVerticalCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AF_AFVSH_MIN,
			D_IM_PRO_AF_AFVSH_MAX, afVerticalCtrl->start_addr,
			"im_pro_stat1_af_ctrl_vertical : start_addr" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AF_AFVSHW_MIN,
			D_IM_PRO_AF_AFVSHW_MAX, afVerticalCtrl->horizon_size,
			"im_pro_stat1_af_ctrl_vertical : horizon_size" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AF[ch].AFVS.AFVSCTL.bit.AFVSCYC				= afVerticalCtrl->update_cycle;
	IO_PRO.STAT.AF[ch].AFVS.AFVSCTL.bit.AFSLV				= afVerticalCtrl->eval_cal_unit;
	IO_PRO.STAT.AF[ch].AFVS.AFVSH.bit.AFVSH					= afVerticalCtrl->start_addr;
	IO_PRO.STAT.AF[ch].AFVS.AFVSHW.bit.AFVSHW				= afVerticalCtrl->horizon_size;
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFVS.AFIIRVB.AFIIRVB1,
			union io_afiirvb_1, AFIIRVK, afVerticalCtrl->iir_k );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFVS.AFIIRVB.AFIIRVB1,
			union io_afiirvb_1, AFIIRVA0, afVerticalCtrl->iir_a0 );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFVS.AFIIRVB.AFIIRVB1,
			union io_afiirvb_1, AFIIRVA1, afVerticalCtrl->iir_a1 );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFVS.AFIIRVB.AFIIRVB2,
			union io_afiirvb_2, AFIIRVA2, afVerticalCtrl->iir_a2 );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFVS.AFIIRVB.AFIIRVB2,
			union io_afiirvb_2, AFIIRVB1, afVerticalCtrl->iir_b1 );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFVS.AFIIRVB.AFIIRVB3,
			union io_afiirvb_3, AFIIRVB2, afVerticalCtrl->iir_b2 );
	IO_PRO.STAT.AF[ch].AFVS.AFCOR2V.bit.AFCOR2LVV			= afVerticalCtrl->cor_threshold;
	IO_PRO.STAT.AF[ch].AFVS.AFCOR2V.bit.AFCOR2V				= afVerticalCtrl->cor_level;
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFVS.AFFIRVB,
			union io_affirvb, AFFIRVB1, afVerticalCtrl->fir_filter[0] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFVS.AFFIRVB,
			union io_affirvb, AFFIRVB2, afVerticalCtrl->fir_filter[1] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFVS.AFFIRVB,
			union io_affirvb, AFFIRVB3, afVerticalCtrl->fir_filter[2] );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
AF Horizontal detection Information
@param[in]	tapNo	:			Horizontal detection TAP number See @ref E_IM_PRO_AF_TAP<br>
@param[in]	afHorizonCtrl	:	Horizontal detection Information See @ref T_IM_PRO_AF_HORIZON_CTRL<br>
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_AF_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 im_pro_stat1_af_ctrl_horizon(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_TAP tapNo,
		T_IM_PRO_AF_HORIZON_CTRL* afHorizonCtrl )
{
#ifdef CO_PARAM_CHECK
	if (afHorizonCtrl == NULL){
		Ddim_Assertion(("I:im_pro_stat1_af_ctrl_horizon error. afHorizonCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFHSCTLA.bit.AFIHA						= afHorizonCtrl->group_a.iir_enable;
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFHSCTLA.bit.AFFHA						= afHorizonCtrl->group_a.fir_enable;
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFHSCTLA.bit.AFSLHA						= afHorizonCtrl->group_a.input_select;
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFFIRHBA.AFFIRHBA1,
			union io_affirhba_1, AFFIRHBA_1, afHorizonCtrl->group_a.fir_coefficient[0] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFFIRHBA.AFFIRHBA1,
			union io_affirhba_1, AFFIRHBA_2, afHorizonCtrl->group_a.fir_coefficient[1] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFFIRHBA.AFFIRHBA1,
			union io_affirhba_1, AFFIRHBA_3, afHorizonCtrl->group_a.fir_coefficient[2] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFFIRHBA.AFFIRHBA1,
			union io_affirhba_1, AFFIRHBA_4, afHorizonCtrl->group_a.fir_coefficient[3] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFFIRHBA.AFFIRHBA2,
			union io_affirhba_2, AFFIRHBA_5, afHorizonCtrl->group_a.fir_coefficient[4] );
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCOR1HA.bit.AFCOR1HA					= afHorizonCtrl->group_a.fir_level;
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFGAINHA.bit.AFGAINHA					= afHorizonCtrl->group_a.gain;
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFIIRHBA.AFIIRHBA1,
			union io_afiirhba_1, AFIIRHKA,  afHorizonCtrl->group_a.iir_k );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFIIRHBA.AFIIRHBA1,
			union io_afiirhba_1, AFIIRHA0A, afHorizonCtrl->group_a.iir_a0 );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFIIRHBA.AFIIRHBA1,
			union io_afiirhba_1, AFIIRHA1A, afHorizonCtrl->group_a.iir_a1 );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFIIRHBA.AFIIRHBA2,
			union io_afiirhba_2, AFIIRHA2A, afHorizonCtrl->group_a.iir_a2 );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFIIRHBA.AFIIRHBA2,
			union io_afiirhba_2, AFIIRHB1A, afHorizonCtrl->group_a.iir_b1 );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFIIRHBA.AFIIRHBA3,
			union io_afiirhba_3, AFIIRHB2A, afHorizonCtrl->group_a.iir_b2 );
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORBHA.AFCORBHA1.bit.AFCORBHA_1	= afHorizonCtrl->group_a.coring_bounder[0];
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORBHA.AFCORBHA1.bit.AFCORBHA_2	= afHorizonCtrl->group_a.coring_bounder[1];
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORBHA.AFCORBHA2.bit.AFCORBHA_3	= afHorizonCtrl->group_a.coring_bounder[2];
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORINCHA.AFCORINCHA1,
			union io_afcorincha_1, AFCORINCHA_0,  afHorizonCtrl->group_a.coring_slope[0] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORINCHA.AFCORINCHA1,
			union io_afcorincha_1, AFCORINCHA_1,  afHorizonCtrl->group_a.coring_slope[1] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORINCHA.AFCORINCHA2,
			union io_afcorincha_2, AFCORINCHA_2,  afHorizonCtrl->group_a.coring_slope[2] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORINCHA.AFCORINCHA2,
			union io_afcorincha_2, AFCORINCHA_3,  afHorizonCtrl->group_a.coring_slope[3] );
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCOROFSHA.AFCOROFSHA1.bit.AFCOROFSHA_0	= afHorizonCtrl->group_a.coring_offset[0];
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCOROFSHA.AFCOROFSHA1.bit.AFCOROFSHA_1	= afHorizonCtrl->group_a.coring_offset[1];
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCOROFSHA.AFCOROFSHA2.bit.AFCOROFSHA_2	= afHorizonCtrl->group_a.coring_offset[2];
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCOROFSHA.AFCOROFSHA2.bit.AFCOROFSHA_3	= afHorizonCtrl->group_a.coring_offset[3];

	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFHSCTLB.bit.AFIHB						= afHorizonCtrl->group_b.iir_enable;
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFHSCTLB.bit.AFFHB						= afHorizonCtrl->group_b.fir_enable;
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFHSCTLB.bit.AFSLHB						= afHorizonCtrl->group_b.input_select;
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFFIRHBB.AFFIRHBB1,
			union io_affirhbb_1, AFFIRHBB_1, afHorizonCtrl->group_b.fir_coefficient[0] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFFIRHBB.AFFIRHBB1,
			union io_affirhbb_1, AFFIRHBB_2, afHorizonCtrl->group_b.fir_coefficient[1] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFFIRHBB.AFFIRHBB1,
			union io_affirhbb_1, AFFIRHBB_3, afHorizonCtrl->group_b.fir_coefficient[2] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFFIRHBB.AFFIRHBB1,
			union io_affirhbb_1, AFFIRHBB_4, afHorizonCtrl->group_b.fir_coefficient[3] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFFIRHBB.AFFIRHBB2,
			union io_affirhbb_2, AFFIRHBB_5, afHorizonCtrl->group_b.fir_coefficient[4] );
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCOR1HB.bit.AFCOR1HB					= afHorizonCtrl->group_b.fir_level;
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFGAINHB.bit.AFGAINHB					= afHorizonCtrl->group_b.gain;
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFIIRHBB.AFIIRHBB1,
			union io_afiirhbb_1, AFIIRHKB,   afHorizonCtrl->group_b.iir_k );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFIIRHBB.AFIIRHBB1,
			union io_afiirhbb_1, AFIIRHA0B,  afHorizonCtrl->group_b.iir_a0 );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFIIRHBB.AFIIRHBB1,
			union io_afiirhbb_1, AFIIRHA1B,  afHorizonCtrl->group_b.iir_a1 );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFIIRHBB.AFIIRHBB2,
			union io_afiirhbb_2, AFIIRHA2B,  afHorizonCtrl->group_b.iir_a2 );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFIIRHBB.AFIIRHBB2,
			union io_afiirhbb_2, AFIIRHB1B,  afHorizonCtrl->group_b.iir_b1 );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFIIRHBB.AFIIRHBB3,
			union io_afiirhbb_3, AFIIRHB2B,  afHorizonCtrl->group_b.iir_b2 );
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORBHB.AFCORBHB1.bit.AFCORBHB_1	= afHorizonCtrl->group_b.coring_bounder[0];
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORBHB.AFCORBHB1.bit.AFCORBHB_2	= afHorizonCtrl->group_b.coring_bounder[1];
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORBHB.AFCORBHB2.bit.AFCORBHB_3	= afHorizonCtrl->group_b.coring_bounder[2];
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORINCHB.AFCORINCHB1,
			union io_afcorinchb_1, AFCORINCHB_0,  afHorizonCtrl->group_b.coring_slope[0] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORINCHB.AFCORINCHB1,
			union io_afcorinchb_1, AFCORINCHB_1,  afHorizonCtrl->group_b.coring_slope[1] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORINCHB.AFCORINCHB2,
			union io_afcorinchb_2, AFCORINCHB_2,  afHorizonCtrl->group_b.coring_slope[2] );
	im_pro_set_reg_signed( IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCORINCHB.AFCORINCHB2,
			union io_afcorinchb_2, AFCORINCHB_3,  afHorizonCtrl->group_b.coring_slope[3] );
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCOROFSHB.AFCOROFSHB1.bit.AFCOROFSHB_0	= afHorizonCtrl->group_b.coring_offset[0];
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCOROFSHB.AFCOROFSHB1.bit.AFCOROFSHB_1	= afHorizonCtrl->group_b.coring_offset[1];
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCOROFSHB.AFCOROFSHB2.bit.AFCOROFSHB_2	= afHorizonCtrl->group_b.coring_offset[2];
	IO_PRO.STAT.AF[ch].AFHS[tapNo].AFCOROFSHB.AFCOROFSHB2.bit.AFCOROFSHB_3	= afHorizonCtrl->group_b.coring_offset[3];
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
AF Window Information Setting
@param[in]	winNo		:	Window No. See @ref E_IM_PRO_AF_WINDOW_NO
@param[in]	afWinCtrl	:	Window Information See @ref T_IM_PRO_AF_WIN_CTRL<br>
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_AF_INPUT_PARAM_ERROR	: Setting NG
@code
// sample code
	//---- Set AF Window Information ----
	T_IM_PRO_AF_WIN_CTRL afWinCtrl;

	afWinCtrl.h_sel0           = E_IM_PRO_AF_WIN_H0_A;
	afWinCtrl.h_sel1           = E_IM_PRO_AF_WIN_H0_A;
	afWinCtrl.eval_cal_unit    = E_IM_PRO_AF_WIN_C0;
	afWinCtrl.bright_threshold = 0xFFFF;
	afWinCtrl.dark_threshold   = 0x0000;
	afWinCtrl.start_pos_x      = 64;
	afWinCtrl.start_pos_y      = 128;
	afWinCtrl.width            = 50;
	afWinCtrl.height           = 50;

	im_pro_stat1_af_ctrl_win(E_IM_PRO_AF_WINDOW_1, &af_ctrl);
@endcode
*/
INT32 im_pro_stat1_af_ctrl_win(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo,
		T_IM_PRO_AF_WIN_CTRL* afWinCtrl )
{
#ifdef CO_PARAM_CHECK
	if (afWinCtrl == NULL){
		Ddim_Assertion(("I:im_pro_stat1_af_ctrl_win error. afWinCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AF_AFH_MIN, D_IM_PRO_AF_AFH_MAX,
			afWinCtrl->start_pos_x, "Im_PRO_AF_Set_Area : start_pos_x" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AF_AFV_MIN, D_IM_PRO_AF_AFV_MAX,
			afWinCtrl->start_pos_y, "Im_PRO_AF_Set_Area : start_pos_y" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AF_AFHW_MIN, D_IM_PRO_AF_AFHW_MAX,
			afWinCtrl->width, "Im_PRO_AF_Set_Area : width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_AF_AFVW_MIN, D_IM_PRO_AF_AFVW_MAX,
			afWinCtrl->height, "Im_PRO_AF_Set_Area : height" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.AF[ch].AFWIN[winNo].AFWINCTL.bit.AFSLWH0	= afWinCtrl->h_sel0;
	IO_PRO.STAT.AF[ch].AFWIN[winNo].AFWINCTL.bit.AFSLWH1	= afWinCtrl->h_sel1;
	IO_PRO.STAT.AF[ch].AFWIN[winNo].AFWINCTL.bit.AFSLWH2	= afWinCtrl->h_sel2;
	IO_PRO.STAT.AF[ch].AFWIN[winNo].AFWINCTL.bit.AFSLWC	= afWinCtrl->eval_cal_unit;
	IO_PRO.STAT.AF[ch].AFWIN[winNo].AFCLVGE.bit.AFCLVGE	= afWinCtrl->bright_threshold;
	IO_PRO.STAT.AF[ch].AFWIN[winNo].AFCLVL.bit.AFCLVL		= afWinCtrl->dark_threshold;
	IO_PRO.STAT.AF[ch].AFWIN[winNo].AFH.bit.AFH			= afWinCtrl->start_pos_x;
	IO_PRO.STAT.AF[ch].AFWIN[winNo].AFV.bit.AFV			= afWinCtrl->start_pos_y;
	IO_PRO.STAT.AF[ch].AFWIN[winNo].AFHW.bit.AFHW			= afWinCtrl->width;
	IO_PRO.STAT.AF[ch].AFWIN[winNo].AFVW.bit.AFVW			= afWinCtrl->height;
	IO_PRO.STAT.AF[ch].AFWIN[winNo].AFSLWM.bit.AFSLWM		= afWinCtrl->max_mix_select;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

/**
Get AF Surface Data
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The brightness data is acquired.
@code
// SAMPLE CODE //
	kulong* win1_ydata;

	win1_ydata = im_pro_stat1_af_get_eval_calc_data(E_IM_PRO_AF_WINDOW_1);	// Window 1 Ydata Top Address Get
@endcode
*/
kulong im_pro_stat1_af_get_eval_calc_data(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVAL_CALC, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get AF Surface Bright block Data
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The brightness data is acquired.
@code
// SAMPLE CODE //
	kulong* win1_ydata;

	win1_ydata = im_pro_stat1_af_get_bright_data(E_IM_PRO_AF_WINDOW_1);	// Window 1 Ydata Top Address Get
@endcode
*/
kulong im_pro_stat1_af_get_bright_data(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVAL_BRIGHT, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get AF Surface Dark block Data
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The brightness data is acquired.
*/
kulong im_pro_stat1_af_get_dark_data(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVAL_DARK, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get AF Horizontal 0 Data
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The AF Horizontal 0 data is acquired.
*/
kulong im_pro_stat1_af_get_horizontal0_data(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL0, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get AF Horizontal 1 Data
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The AF Horizontal 1 data is acquired.
*/
kulong im_pro_stat1_af_get_horizontal1_data(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL1, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get AF Horizontal 2 Data
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The AF Horizontal 2 data is acquired.
*/
kulong im_pro_stat1_af_get_horizontal2_data(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL2, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get AF Vertical Data
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The AF Vertical data is acquired.
*/
kulong im_pro_stat1_af_get_vertical_data(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_VERTICAL, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get As a result maximum evaluated calculation value AF detection window
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The maximum color value is acquired.
*/
kulong im_pro_stat1_af_get_max_eval_calc_value(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVALUATED_VALUE_MAX, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get As a result minimum evaluated calculation value AF detection window
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The minimum color value is acquired.
*/
kulong im_pro_stat1_af_get_min_eval_calc_value(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVALUATED_VALUE_MIN, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get As a result maximum assessment value AF detection window
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The maximum assessment value is acquired.
*/
kulong im_pro_stat1_af_get_max_assess_value(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVALUATION_VALUE_MAX, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get As a result minimum assessment value AF detection window
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The minimum assessment value is acquired.
*/
kulong im_pro_stat1_af_get_min_assess_value(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVALUATION_VALUE_MIN, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get AF Detection Window Horizontal0 Detection Each Line Maximum Value Accumulation result.
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The maximum assessment value is acquired.
*/
kulong im_pro_stat1_af_get_horizontal0_line_accum_max_value(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL_0_EACH_LINE_MAX, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get AF Detection Window Horizontal1 Detection Each Line Maximum Value Accumulation result.
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The maximum assessment value is acquired.
*/
kulong im_pro_stat1_af_get_horizontal1_line_accum_max_value(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL_1_EACH_LINE_MAX, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get AF Detection Window Horizontal2 Detection Each Line Maximum Value Accumulation result.
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The maximum assessment value is acquired.
*/
kulong im_pro_stat1_af_get_horizontal2_line_accum_max_value(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL_2_EACH_LINE_MAX, E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT );
}

/**
Get AF evaluated calculation Data for AFE long exposure
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The brightness data is acquired.
@code
// SAMPLE CODE //
	kulong* win1_ydata;

	win1_ydata = im_pro_stat1_af_get_eval_calc_lastdata(E_IM_PRO_AF_WINDOW_1);	// Window 1 Ydata Top Address Get
@endcode
*/
kulong im_pro_stat1_af_get_eval_calc_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVAL_CALC, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get AF evaluated calculation Bright block Data for AFE long exposure
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The brightness data is acquired.
@code
// SAMPLE CODE //
	kulong* win1_ydata;

	win1_ydata = im_pro_stat1_af_get_bright_lastdata(E_IM_PRO_AF_WINDOW_1);	// Window 1 Ydata Top Address Get
@endcode
*/
kulong im_pro_stat1_af_get_bright_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVAL_BRIGHT, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get AF evaluated calculation Dark block Data for AFE long exposure
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The brightness data is acquired.
@code
// SAMPLE CODE //
	kulong* win1_ydata;

	win1_ydata = im_pro_stat1_af_get_dark_lastdata(E_IM_PRO_AF_WINDOW_1);	// Window 1 Ydata Top Address Get
@endcode
*/
kulong im_pro_stat1_af_get_dark_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVAL_DARK, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get AF Horizontal 0 Data for AFE long exposure
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The brightness data is acquired.
@code
// SAMPLE CODE //
	kulong* win1_ydata;

	win1_ydata = im_pro_stat1_af_get_horizontal0_lastdata(E_IM_PRO_AF_WINDOW_1);	// Window 1 Ydata Top Address Get
@endcode
*/
kulong im_pro_stat1_af_get_horizontal0_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL0, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get AF Horizontal 1 Data for AFE long exposure
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The brightness data is acquired.
@code
// SAMPLE CODE //
	kulong* win1_ydata;

	win1_ydata = im_pro_stat1_af_get_horizontal1_lastdata(E_IM_PRO_AF_WINDOW_1);	// Window 1 Ydata Top Address Get
@endcode
*/
kulong im_pro_stat1_af_get_horizontal1_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL1, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get AF Horizontal 2 Data for AFE long exposure
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The brightness data is acquired.
@code
// SAMPLE CODE //
	kulong* win1_ydata;

	win1_ydata = im_pro_stat1_af_get_horizontal2_lastdata(E_IM_PRO_AF_WINDOW_1);	// Window 1 Ydata Top Address Get
@endcode
*/
kulong im_pro_stat1_af_get_horizontal2_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL2, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get AF Vertical Data for AFE long exposure
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* brightness data address pointer
@remarks	The brightness data is acquired.
@code
// SAMPLE CODE //
	kulong* win1_ydata;

	win1_ydata = im_pro_stat1_af_get_vertical_lastdata(E_IM_PRO_AF_WINDOW_1);	// Window 1 Ydata Top Address Get
@endcode
*/
kulong im_pro_stat1_af_get_vertical_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_VERTICAL, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get As a result maximum evaluated calculation value AF detection window for AFE long exposure
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The maximum color value is acquired.
*/
kulong im_pro_stat1_af_get_max_eval_calc_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVALUATED_VALUE_MAX, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get As a result minimum evaluated calculation value AF detection window for AFE long exposure
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The minimum color value is acquired.
*/
kulong im_pro_stat1_af_get_min_eval_calc_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVALUATED_VALUE_MIN, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get As a result maximum assessment value AF detection window for AFE long exposure
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The maximum assessment value is acquired.
*/
kulong im_pro_stat1_af_get_max_assess_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVALUATION_VALUE_MAX, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get As a result minimum assessment value AF detection window for AFE long exposure
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The minimum assessment value is acquired.
*/
kulong im_pro_stat1_af_get_min_assess_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_EVALUATION_VALUE_MIN, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get AF Detection Window Horizontal0 Detection Each Line Maximum Value Accumulation result for AFE long exposure.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The maximum assessment value is acquired.
*/
kulong im_pro_stat1_af_get_horizontal0_line_accum_max_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL_0_EACH_LINE_MAX, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get AF Detection Window Horizontal1 Detection Each Line Maximum Value Accumulation result for AFE long exposure.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The maximum assessment value is acquired.
*/
kulong im_pro_stat1_af_get_horizontal1_line_accum_max_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL_1_EACH_LINE_MAX, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

/**
Get AF Detection Window Horizontal2 Detection Each Line Maximum Value Accumulation result for AFE long exposure.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		kulong* data address pointer
@remarks	The maximum assessment value is acquired.
*/
kulong im_pro_stat1_af_get_horizontal2_line_accum_max_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo )
{
	return im_pro_comm_get_af_data( ch, winNo,
			E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL_2_EACH_LINE_MAX, E_IM_PRO_AF_RESULT_DATA_TYPE_LAST );
}

ImProStat1* im_pro_stat1_new(void)
{
	ImProStat1 *self = g_object_new(IM_TYPE_PRO_STAT1, NULL);
	return self;
}
