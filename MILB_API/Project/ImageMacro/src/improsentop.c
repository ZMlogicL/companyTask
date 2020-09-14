/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-01
*@author              :杨金波
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


#include<stdint.h>
#include<string.h>
#include<math.h>
#include <klib.h>
#include"improbase.h"
#include"improsentop.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSentop, impro_sentop);
#define IMPRO_SENTOP_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSentopPrivate, IMPRO_TYPE_SENTOP));


/*宏定义区域*/


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSentopPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/


/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_sentop_constructor(ImproSentop *self)
{
	ImproSentopPrivate *priv = IMPRO_SENTOP_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_sentop_destructor(ImproSentop *self)
{
	ImproSentopPrivate *priv = IMPRO_SENTOP_GET_PRIVATE(self);
}

/*IMPL*/


/*PUBLIC*/
/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
VOID impro_sentop_set_cphy_common_ctrl( UCHAR phyNo, TimproSentopCphyCommonModeCtrl* cphyCommon )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	switch( phyNo ) {
		case 0:
			ioPro.sen.sentop.phy0mdctl.bit.phy0Bitwidthsel			= cphyCommon->bitwidthsel;
			ioPro.sen.sentop.phy0mdctl.bit.phy0Rxmode					= cphyCommon->rxmode;
			ioPro.sen.sentop.phy0ifctl.phy0ifctl1.bit.phy0D0setsel	= cphyCommon->d0setsel;
			ioPro.sen.sentop.phy0ifctl.phy0ifctl1.bit.phy0D1setsel	= cphyCommon->d1setsel;
			ioPro.sen.sentop.phy0ifctl.phy0ifctl1.bit.phy0D2setsel	= cphyCommon->d2setsel;
			ioPro.sen.sentop.phy0ifctl.phy0ifctl2.bit.phy0D3setsel	= cphyCommon->d3setsel;
			break;

		case 1:
			ioPro.sen.sentop.phy1mdctl.bit.phy1Bitwidthsel			= cphyCommon->bitwidthsel;
			ioPro.sen.sentop.phy1mdctl.bit.phy1Rxmode					= cphyCommon->rxmode;
			ioPro.sen.sentop.phy1ifctl.phy1ifctl1.bit.phy1D0setsel	= cphyCommon->d0setsel;
			ioPro.sen.sentop.phy1ifctl.phy1ifctl1.bit.phy1D1setsel	= cphyCommon->d1setsel;
			ioPro.sen.sentop.phy1ifctl.phy1ifctl1.bit.phy1D2setsel	= cphyCommon->d2setsel;
			ioPro.sen.sentop.phy1ifctl.phy1ifctl2.bit.phy1D3setsel	= cphyCommon->d3setsel;
			break;

		case 2:
			ioPro.sen.sentop.phy2mdctl.bit.phy2Bitwidthsel			= cphyCommon->bitwidthsel;
			ioPro.sen.sentop.phy2mdctl.bit.phy2Rxmode					= cphyCommon->rxmode;
			ioPro.sen.sentop.phy2ifctl.phy2ifctl1.bit.phy2D0setsel	= cphyCommon->d0setsel;
			ioPro.sen.sentop.phy2ifctl.phy2ifctl1.bit.phy2D1setsel	= cphyCommon->d1setsel;
			ioPro.sen.sentop.phy2ifctl.phy2ifctl1.bit.phy2D2setsel	= cphyCommon->d2setsel;
			ioPro.sen.sentop.phy2ifctl.phy2ifctl2.bit.phy2D3setsel	= cphyCommon->d3setsel;
			break;

		//case 3:
		default:
			ioPro.sen.sentop.phy3mdctl.bit.phy3Bitwidthsel			= cphyCommon->bitwidthsel;
			ioPro.sen.sentop.phy3mdctl.bit.phy3Rxmode	D0setsel	= cphyCommon->d0setsel;
			ioPro.sen.sentop.phy3ifctl.phy3ifctl1.bit.phy3D1setsel	= cphyCommon->d1setsel;
			ioPro.sen.sentop.phy3ifctl.phy3ifctl1.bit.phy3D2setsel	= cphyCommon->d2setsel;
			ioPro.sen.sentop.phy3ifctl.phy3ifctl2.bit.phy3D3setsel	= cphyCommon->d3setsel;
			break;
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
}

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/********************************************************/
/*	SEN Top												*/
/********************************************************/
/**
SENTOP Macro initialize
@remarks	Please Call at the time of system starting.
*/
VOID impro_sentop_init( VOID )
{
	// Software release
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.sr.bit.sr  = D_IM_PRO_SR_RELEASE;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
}

/**
SENTOP Macro software reset
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: All macro not stopped NG
*/
INT32 impro_sentop_sw_reset( VOID )
{
#ifdef CO_ACT_PRO_CLOCK
	//not ALL Stopped
	if (im_pro_common_fig_im_pro_sen_get_stop_all() == FALSE){
		Ddim_Print(("I:impro_sentop_sw_reset. macro not stopped error. \n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif	/* CO_ACT_PRO_CLOCK */

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	// Software reset
	ioPro.sen.sentop.sr.bit.sr  = D_IM_PRO_SR_RESET;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
SENTOP Macro clock control
@param[in]	clkType	: SENTOP Macro clock type
@param[in]	onOff		: 0:clock on 1:clock off
@param[in]	waitSkip	: 0:non wait 1:wait 1ms. for wait PROCLK/CDK 5 cycle.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sentop_control_clock( EimproSentopClkType clkType, UCHAR onOff, UCHAR waitSkip )
{
	UINT32 cpuClkHz;
	UINT32 macroClkHz;

#ifdef CO_PARAM_CHECK
	if (onOff > D_IM_PRO_CLOCK_OFF){
		Ddim_Assertion(("I:impro_sentop_control_clock error. onOff value over!! (%d)\n", onOff));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else {
		// DO NOTHING
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	switch( clkType ) {
		case ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_SENSORCLK:
			ioPro.sen.sentop.clkstp.clkstp1.bit.pstp1 = ( ( onOff == D_IM_PRO_CLOCK_ON )
					? D_IM_PRO_CLOCK_ON : D_IM_PRO_CLOCK_OFF );
			break;

		case ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK0:
			ioPro.sen.sentop.clkstp.clkstp1.bit.pstp2 = ( ( onOff == D_IM_PRO_CLOCK_ON )
					? D_IM_PRO_CLOCK_ON : D_IM_PRO_CLOCK_OFF );
			break;

		case ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK1:
			ioPro.sen.sentop.clkstp.clkstp1.bit.pstp3 = ( ( onOff == D_IM_PRO_CLOCK_ON )
					? D_IM_PRO_CLOCK_ON : D_IM_PRO_CLOCK_OFF );
			break;

		case ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK2:
			ioPro.sen.sentop.clkstp.clkstp1.bit.pstp4 = ( ( onOff == D_IM_PRO_CLOCK_ON )
					? D_IM_PRO_CLOCK_ON : D_IM_PRO_CLOCK_OFF );
			break;

		//case E_IM_PRO_SENTOP_CLK_TYPE_APCLK3:
		default:
			ioPro.sen.sentop.clkstp.clkstp2.bit.pstp5 = ( ( onOff == D_IM_PRO_CLOCK_ON )
					? D_IM_PRO_CLOCK_ON : D_IM_PRO_CLOCK_OFF );
			break;
	}
	// waiting for 5 cycle
	if( waitSkip == 0 ) {
		im_pro_get_current_clk_hz( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN, &cpuClkHz, &macroClkHz );
		im_pro_common_wait_by_clk_cycle( 5, macroClkHz, cpuClkHz );
#ifndef CO_DEBUG_ON_PC
//			__nop();
#endif
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
SENTOP macro control data setting
@param[in]	ctrl : SENTOP macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sentop_ctrl( TimproSentopCtrl* ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ctrl == NULL){
		Ddim_Assertion(("I:impro_sentop_ctrl error. ctrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (im_pro_common_fig_im_pro_sen_get_stop_all() == FALSE){	//not ALL Stopped
		Ddim_Print(("I:impro_sentop_ctrl. macro not stopped error. \n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
	if( ctrl->sencoreHmaxSizeCtrl > ImproSentop_E_IM_PRO_SENTOP_SENCORE_MAX_HSIZE_CTRL_2 ) {
		Ddim_Print(("I:impro_sentop_ctrl. sencoreHmaxSizeCtrl error.(%u) \n", ctrl->sencoreHmaxSizeCtrl));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
	if( ctrl->ldivHmaxSizeCtrl > ImproSentop_E_IM_PRO_SENTOP_LDIV_MAX_HSIZE_CTRL_2 ) {
		Ddim_Print(("I:impro_sentop_ctrl. ldivHmaxSizeCtrl error.(%u) \n", ctrl->ldivHmaxSizeCtrl));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.sentopctl1.sentopctl11.bit.senin0		= ctrl->senConnectTypeSel[0];
	ioPro.sen.sentop.sentopctl1.sentopctl11.bit.senin1		= ctrl->senConnectTypeSel[1];
	ioPro.sen.sentop.sentopctl1.sentopctl11.bit.senin2		= ctrl->senConnectTypeSel[2];
	ioPro.sen.sentop.sentopctl1.sentopctl11.bit.senin3		= ctrl->senConnectTypeSel[3];
	ioPro.sen.sentop.sentopctl1.sentopctl11.bit.blobset0	= ctrl->blobInputSel[0];
	ioPro.sen.sentop.sentopctl1.sentopctl11.bit.blobset1	= ctrl->blobInputSel[1];
	ioPro.sen.sentop.sentopctl1.sentopctl12.bit.blobset2	= ctrl->blobInputSel[2];
	ioPro.sen.sentop.sentopctl1.sentopctl12.bit.blobset3	= ctrl->blobInputSel[3];
	ioPro.sen.sentop.sentopctl1.sentopctl12.bit.pwsw0		= ctrl->sdramOutputType[0];
	ioPro.sen.sentop.sentopctl1.sentopctl12.bit.pwsw1		= ctrl->sdramOutputType[1];
	ioPro.sen.sentop.sentopctl1.sentopctl13.bit.pwsw2		= ctrl->sdramOutputType[2];
	ioPro.sen.sentop.sentopctl1.sentopctl13.bit.pwsw3		= ctrl->sdramOutputType[3];
	ioPro.sen.sentop.sentopctl1.sentopctl13.bit.pipe2s		= ctrl->outputSelSro2;
	ioPro.sen.sentop.sentopctl1.sentopctl13.bit.senramsw	= ctrl->sencoreHmaxSizeCtrl;
	ioPro.sen.sentop.sentopctl1.sentopctl13.bit.ldivramsw	= ctrl->ldivHmaxSizeCtrl;
	ioPro.sen.sentop.sentopctl1.sentopctl13.bit.ldivmch	= ctrl->ldivMultiChInputCtrl;


	ioPro.sen.sentop.sentopctl2.sentopctl2_1.bit.org00		= ctrl->firstPixel[0][0];
	ioPro.sen.sentop.sentopctl2.sentopctl2_1.bit.org01		= ctrl->firstPixel[0][1];
	ioPro.sen.sentop.sentopctl2.sentopctl2_1.bit.org10		= ctrl->firstPixel[1][0];
	ioPro.sen.sentop.sentopctl2.sentopctl2_1.bit.org11		= ctrl->firstPixel[1][1];
	ioPro.sen.sentop.sentopctl2.sentopctl2_2.bit.org20		= ctrl->firstPixel[2][0];
	ioPro.sen.sentop.sentopctl2.sentopctl2_2.bit.org21		= ctrl->firstPixel[2][1];
	ioPro.sen.sentop.sentopctl2.sentopctl2_2.bit.org30		= ctrl->firstPixel[3][0];
	ioPro.sen.sentop.sentopctl2.sentopctl2_2.bit.org31		= ctrl->firstPixel[3][1];
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
SENTOP BitShift macro control data setting
@param[in]	ctrl : SENTOP BitShift macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sentop_bs_ctrl( TimproSentopBsCtrl* ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ctrl == NULL){
		Ddim_Assertion(("I:impro_sentop_bs_ctrl error. ctrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	//not ALL Stopped
	if (im_pro_common_fig_im_pro_sen_get_stop_all() == FALSE){
		Ddim_Print(("I:impro_sentop_bs_ctrl. macro not stopped error. \n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.bsctl.bsctl1.bit.bsamnt0	= ctrl->shiftValue[0];
	ioPro.sen.sentop.bsctl.bsctl1.bit.bsamnt1	= ctrl->shiftValue[1];
	ioPro.sen.sentop.bsctl.bsctl1.bit.bsamnt2	= ctrl->shiftValue[2];
	ioPro.sen.sentop.bsctl.bsctl1.bit.bsamnt3	= ctrl->shiftValue[3];
	ioPro.sen.sentop.bsctl.bsctl1.bit.bslmd0	= ctrl->satCompensation[0];
	ioPro.sen.sentop.bsctl.bsctl1.bit.bslmd1	= ctrl->satCompensation[1];
	ioPro.sen.sentop.bsctl.bsctl1.bit.bslmd2	= ctrl->satCompensation[2];
	ioPro.sen.sentop.bsctl.bsctl1.bit.bslmd3	= ctrl->satCompensation[3];
	ioPro.sen.sentop.bsctl.bsctl2.bit.bslr0	= ctrl->shiftDir[0];
	ioPro.sen.sentop.bsctl.bsctl2.bit.bslr1	= ctrl->shiftDir[1];
	ioPro.sen.sentop.bsctl.bsctl2.bit.bslr2	= ctrl->shiftDir[2];
	ioPro.sen.sentop.bsctl.bsctl2.bit.bslr3	= ctrl->shiftDir[3];
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}


/**
SENTOP OBT macro setting
@param[in]	ctrl : SENTOP BitShift macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sentop_obt_ctrl( TimproSentopObtCtrl* ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ctrl == NULL){
		Ddim_Assertion(("I:impro_sentop_obt_ctrl error. ctrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.obtcdcctl1.bit.obtcpat	= ctrl->obtCommPerttern;
	ioPro.sen.sentop.obtcdcset.bit.obtcdcset	= 1;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	// waiting for 5 cycle
	im_pro_common_wait_by_clk_cycle( 5, 100*1000*1000, 660*1000*1000 );
#ifndef CO_DEBUG_ON_PC
//	__nop();
#endif

	return D_DDIM_OK;
}


/**
SENTOP OBT macro weight coefficient setting
@param[in]	coeff : SENTOP OBT macro weight coefficient information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sentop_obt_set_weight_coeff( TimproSentopObtWeightCoeff* coeff )
{
#ifdef CO_PARAM_CHECK
	if (coeff == NULL){
		Ddim_Assertion(("I:impro_sentop_obt_set_weight_coeff error. coeff=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( E_IM_PRO_UNIT_NUM1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.obtcdcctl2.obtcdcctl21.bit.obtdwc00	= coeff->coeff[0][0];
	ioPro.sen.sentop.obtcdcctl2.obtcdcctl21.bit.obtdwc01	= coeff->coeff[0][1];
	ioPro.sen.sentop.obtcdcctl2.obtcdcctl21.bit.obtdwc10	= coeff->coeff[1][0];
	ioPro.sen.sentop.obtcdcctl2.obtcdcctl21.bit.obtdwc11	= coeff->coeff[1][1];
	ioPro.sen.sentop.obtcdcctl2.obtcdcctl22.bit.obtdwc20	= coeff->coeff[2][0];
	ioPro.sen.sentop.obtcdcctl2.obtcdcctl22.bit.obtdwc21	= coeff->coeff[2][1];
	ioPro.sen.sentop.obtcdcctl2.obtcdcctl22.bit.obtdwc30	= coeff->coeff[3][0];
	ioPro.sen.sentop.obtcdcctl2.obtcdcctl22.bit.obtdwc31	= coeff->coeff[3][1];
	ioPro.sen.sentop.OBTCDCSET.bit.OBTCDCSET	= 1;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	// waiting for 5 cycle
	im_pro_common_wait_by_clk_cycle( 5, 100*1000*1000, 660*1000*1000 );
#ifndef CO_DEBUG_ON_PC
//	__nop();
#endif

	return D_DDIM_OK;
}

/**
SENTOP LVDS macro setting
@param[in]	ctrl : SENTOP LVDS macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sentop_lvds_ctrl( TimproSentopLvdsCtrl* ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ctrl == NULL){
		Ddim_Assertion(("I:impro_sentop_lvds_ctrl error. ctrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.lvdsctl.bit.lvdsckpd	= ctrl->clockLanePowerdown;
	ioPro.sen.sentop.lvdsctl.bit.lvdsdlpd	= ctrl->dataLanePowerdown;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}


/**
SENTOP SLVS macro setting
@param[in]	ctrl : SENTOP SLVS macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sentop_slvs_ctrl( TimproSentopSlvsCtrl* ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ctrl == NULL){
		Ddim_Assertion(("I:impro_sentop_slvs_ctrl error. ctrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.slvsecctl.bit.slvsecsel		= ctrl->linkMode;
	ioPro.sen.sentop.slvsecctl.bit.phy0Rxpdck		= ctrl->phy0Rxpdck;
	ioPro.sen.sentop.slvsecctl.bit.phy1Rxpdck		= ctrl->phy1Rxpdck;
	ioPro.sen.sentop.slvsecctl.bit.phy2Rxpdck		= ctrl->phy2Rxpdck;
	ioPro.sen.sentop.slvsecctl.bit.phy3Rxpdck		= ctrl->phy3Rxpdck;
	if( ctrl->clkCtrlEnabled == TRUE ) {
		ioPro.sen.sentop.slvsecctl.bit.phy0Rxpclk2aen	= ctrl->phy0Rxpclk2aen;
		ioPro.sen.sentop.slvsecctl.bit.phy1Rxpclk2aen	= ctrl->phy1Rxpclk2aen;
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}


/**
SENTOP SG macro setting
@param[in]	ctrl : SG macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sentop_sgCtrl( TimproSentopSgCtrl* ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ctrl == NULL){
		Ddim_Assertion(("I:impro_sentop_sgCtrl error. ctrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.sgoutctl.bit.sgsel0	= ctrl->sgIfOutputSel[0];
	ioPro.sen.sentop.sgoutctl.bit.sgsel1	= ctrl->sgIfOutputSel[1];
	ioPro.sen.sentop.sgoutctl.bit.sgsel2	= ctrl->sgIfOutputSel[2];
	ioPro.sen.sentop.sgoutctl.bit.sgsel3	= ctrl->sgIfOutputSel[3];
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}


/**
SENTOP CombpPHY macro setting
@param[in]	cphyCtrl : CombpPHY control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sentop_cphy_ctrl( TimproSentopCphyCtrl* cphyCtrl )
{
#ifdef CO_PARAM_CHECK
	if (cphyCtrl == NULL){
		Ddim_Assertion(("I:impro_sentop_cphy_ctrl error. cphyCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.phycifctl.phycifctl1.bit.phyPregcnt			= cphyCtrl->commonIfCtrl.pregcnt;
	ioPro.sen.sentop.phycifctl.phycifctl1.bit.phyFreqcnt			= cphyCtrl->commonIfCtrl.freqcnt;
	ioPro.sen.sentop.phycifctl.phycifctl1.bit.phyPdccnt			= cphyCtrl->commonIfCtrl.pdccnt;
	ioPro.sen.sentop.phycifctl.phycifctl1.bit.phySetdf			= cphyCtrl->commonIfCtrl.setdf;
	ioPro.sen.sentop.phycifctl.phycifctl1.bit.phyPicodetst		= cphyCtrl->commonIfCtrl.picodetst;
	ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyPmonsel			= cphyCtrl->commonIfCtrl.pmonsel;
	ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyDmonsel			= cphyCtrl->commonIfCtrl.dmonsel;
	ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyCntsel			= cphyCtrl->commonIfCtrl.cntsel;
	ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyMulgainf			= cphyCtrl->commonIfCtrl.mulgainf;
	ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyMulgainp			= cphyCtrl->commonIfCtrl.mulgainp;
	ioPro.sen.sentop.phycifctl.phycifctl3.bit.phyCdrfunc			= cphyCtrl->commonIfCtrl.cdrfunc;

	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop3uicp0	= cphyCtrl->cpmodeCtrl[0].zerop3uicp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop4uicp0	= cphyCtrl->cpmodeCtrl[0].zerop4uicp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop5uicp0	= cphyCtrl->cpmodeCtrl[0].zerop5uicp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop6uicp0	= cphyCtrl->cpmodeCtrl[0].zerop6uicp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0DetcntCp0	= cphyCtrl->cpmodeCtrl[0].detcntCp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0EqEnCp0	= cphyCtrl->cpmodeCtrl[0].eqEnCp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0EqSetCp0	= cphyCtrl->cpmodeCtrl[0].eqSetCp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop3uicp1	= cphyCtrl->cpmodeCtrl[0].zerop3uicp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop4uicp1	= cphyCtrl->cpmodeCtrl[0].zerop4uicp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop5uicp1	= cphyCtrl->cpmodeCtrl[0].zerop5uicp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop6uicp1	= cphyCtrl->cpmodeCtrl[0].zerop6uicp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0DetcntCp1	= cphyCtrl->cpmodeCtrl[0].detcntCp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0EqEnCp1	= cphyCtrl->cpmodeCtrl[0].eqEnCp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0EqSetCp1	= cphyCtrl->cpmodeCtrl[0].eqSetCp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop3uicp2	= cphyCtrl->cpmodeCtrl[0].zerop3uicp2;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop4uicp2	= cphyCtrl->cpmodeCtrl[0].zerop4uicp2;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop5uicp2	= cphyCtrl->cpmodeCtrl[0].zerop5uicp2;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop6uicp2	= cphyCtrl->cpmodeCtrl[0].zerop6uicp2;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0DetcntCp2	= cphyCtrl->cpmodeCtrl[0].detcntCp2;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0EqEnCp2	= cphyCtrl->cpmodeCtrl[0].eqEnCp2;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0EqSetCp2	= cphyCtrl->cpmodeCtrl[0].eqSetCp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop3uicp0	= cphyCtrl->cpmodeCtrl[1].zerop3uicp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop4uicp0	= cphyCtrl->cpmodeCtrl[1].zerop4uicp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop5uicp0	= cphyCtrl->cpmodeCtrl[1].zerop5uicp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop6uicp0	= cphyCtrl->cpmodeCtrl[1].zerop6uicp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1DetcntCp0	= cphyCtrl->cpmodeCtrl[1].detcntCp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1EqEnCp0	= cphyCtrl->cpmodeCtrl[1].eqEnCp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1EqSetCp0	= cphyCtrl->cpmodeCtrl[1].eqSetCp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop3uicp1	= cphyCtrl->cpmodeCtrl[1].zerop3uicp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop4uicp1	= cphyCtrl->cpmodeCtrl[1].zerop4uicp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop5uicp1	= cphyCtrl->cpmodeCtrl[1].zerop5uicp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop6uicp1	= cphyCtrl->cpmodeCtrl[1].zerop6uicp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1DetcntCp1	= cphyCtrl->cpmodeCtrl[1].detcntCp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1EqEnCp1	= cphyCtrl->cpmodeCtrl[1].eqEnCp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1EqSetCp1	= cphyCtrl->cpmodeCtrl[1].eqSetCp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop3uicp2	= cphyCtrl->cpmodeCtrl[1].zerop3uicp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop4uicp2	= cphyCtrl->cpmodeCtrl[1].zerop4uicp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop5uicp2	= cphyCtrl->cpmodeCtrl[1].zerop5uicp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop6uicp2	= cphyCtrl->cpmodeCtrl[1].zerop6uicp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1DetcntCp2	= cphyCtrl->cpmodeCtrl[1].detcntCp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1EqEnCp2	= cphyCtrl->cpmodeCtrl[1].eqEnCp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop3uicp0	= cphyCtrl->cpmodeCtrl[2].zerop3uicp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop4uicp0	= cphyCtrl->cpmodeCtrl[2].zerop4uicp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop5uicp0	= cphyCtrl->cpmodeCtrl[2].zerop5uicp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop6uicp0	= cphyCtrl->cpmodeCtrl[2].zerop6uicp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2DetcntCp0	= cphyCtrl->cpmodeCtrl[2].detcntCp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2EqEnCp0	= cphyCtrl->cpmodeCtrl[2].eqEnCp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2EqSetCp0	= cphyCtrl->cpmodeCtrl[2].eqSetCp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop3uicp1	= cphyCtrl->cpmodeCtrl[2].zerop3uicp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop4uicp1	= cphyCtrl->cpmodeCtrl[2].zerop4uicp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop5uicp1	= cphyCtrl->cpmodeCtrl[2].zerop5uicp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop6uicp1	= cphyCtrl->cpmodeCtrl[2].zerop6uicp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2DetcntCp1	= cphyCtrl->cpmodeCtrl[2].detcntCp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2EqEnCp1	= cphyCtrl->cpmodeCtrl[2].eqEnCp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2EqSetCp1	= cphyCtrl->cpmodeCtrl[2].eqSetCp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop3uicp2	= cphyCtrl->cpmodeCtrl[2].zerop3uicp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop4uicp2	= cphyCtrl->cpmodeCtrl[2].zerop4uicp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop5uicp2	= cphyCtrl->cpmodeCtrl[2].zerop5uicp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop6uicp2	= cphyCtrl->cpmodeCtrl[2].zerop6uicp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2DetcntCp2	= cphyCtrl->cpmodeCtrl[2].detcntCp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2EqEnCp2	= cphyCtrl->cpmodeCtrl[2].eqEnCp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2EqSetCp2	= cphyCtrl->cpmodeCtrl[2].eqSetCp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop3uicp0	= cphyCtrl->cpmodeCtrl[3].zerop3uicp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop4uicp0	= cphyCtrl->cpmodeCtrl[3].zerop4uicp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop5uicp0	= cphyCtrl->cpmodeCtrl[3].zerop5uicp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop6uicp0	= cphyCtrl->cpmodeCtrl[3].zerop6uicp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3DetcntCp0	= cphyCtrl->cpmodeCtrl[3].detcntCp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3EqEnCp0	= cphyCtrl->cpmodeCtrl[3].eqEnCp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3EqSetCp0	= cphyCtrl->cpmodeCtrl[3].eqSetCp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop3uicp1	= cphyCtrl->cpmodeCtrl[3].zerop3uicp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop4uicp1	= cphyCtrl->cpmodeCtrl[3].zerop4uicp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop5uicp1	= cphyCtrl->cpmodeCtrl[3].zerop5uicp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop6uicp1	= cphyCtrl->cpmodeCtrl[3].zerop6uicp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3DetcnCp1	= cphyCtrl->cpmodeCtrl[3].detcntCp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3EqEnCp1	= cphyCtrl->cpmodeCtrl[3].eqEnCp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3EqSetCp1	= cphyCtrl->cpmodeCtrl[3].eqSetCp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop3uicp2	= cphyCtrl->cpmodeCtrl[3].zerop3uicp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop4uicp2	= cphyCtrl->cpmodeCtrl[3].zerop4uicp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop5uicp2	= cphyCtrl->cpmodeCtrl[3].zerop5uicp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop6uicp2	= cphyCtrl->cpmodeCtrl[3].zerop6uicp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3DetcntCp2	= cphyCtrl->cpmodeCtrl[3].detcntCp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3EqEnCp2	= cphyCtrl->cpmodeCtrl[3].eqEnCp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3EqSetCp2	= cphyCtrl->cpmodeCtrl[3].eqSetCp2;

	ioPro.sen.sentop.phy0dlctl.bit.phy0D0rxspeed					= cphyCtrl->delayCtrl[0].d0rxspeed;
	ioPro.sen.sentop.phy0dlctl.bit.phy0D1rxspeed					= cphyCtrl->delayCtrl[0].d1rxspeed;
	ioPro.sen.sentop.phy0dlctl.bit.phy0D2rxspeed					= cphyCtrl->delayCtrl[0].d2rxspeed;
	ioPro.sen.sentop.phy0dlctl.bit.phy0D3rxspeed					= cphyCtrl->delayCtrl[0].d3rxspeed;
	ioPro.sen.sentop.phy0dlctl.bit.phy0SkwselCp0					= cphyCtrl->delayCtrl[0].skwselCp0;
	ioPro.sen.sentop.phy0dlctl.bit.phy0SkwselCp1					= cphyCtrl->delayCtrl[0].skwselCp1;
	ioPro.sen.sentop.phy0dlctl.bit.phy0SkwselCp2					= cphyCtrl->delayCtrl[0].skwselCp2;
	ioPro.sen.sentop.phy1dlctl.bit.phy1D0rxspeed					= cphyCtrl->delayCtrl[1].d0rxspeed;
	ioPro.sen.sentop.phy1dlctl.bit.phy1D1rxspeed					= cphyCtrl->delayCtrl[1].d1rxspeed;
	ioPro.sen.sentop.phy1dlctl.bit.phy1D2rxspeed					= cphyCtrl->delayCtrl[1].d2rxspeed;
	ioPro.sen.sentop.phy1dlctl.bit.phy1D3rxspeed					= cphyCtrl->delayCtrl[1].d3rxspeed;
	ioPro.sen.sentop.phy1dlctl.bit.phy1SkwselCp0					= cphyCtrl->delayCtrl[1].skwselCp0;
	ioPro.sen.sentop.phy1dlctl.bit.phy1SkwselCp1					= cphyCtrl->delayCtrl[1].skwselCp1;
	ioPro.sen.sentop.phy1dlctl.bit.phy1SkwselCp2					= cphyCtrl->delayCtrl[1].skwselCp2;
	ioPro.sen.sentop.phy2dlctl.bit.phy2D0rxspeed					= cphyCtrl->delayCtrl[2].d0rxspeed;
	ioPro.sen.sentop.phy2dlctl.bit.phy2D1rxspeed					= cphyCtrl->delayCtrl[2].d1rxspeed;
	ioPro.sen.sentop.phy2dlctl.bit.phy2D2rxspeed					= cphyCtrl->delayCtrl[2].d2rxspeed;
	ioPro.sen.sentop.phy2dlctl.bit.phy2D3rxspeed					= cphyCtrl->delayCtrl[2].d3rxspeed;
	ioPro.sen.sentop.phy2dlctl.bit.phy2SkwselCp0					= cphyCtrl->delayCtrl[2].skwselCp0;
	ioPro.sen.sentop.phy2dlctl.bit.phy2SkwselCp1					= cphyCtrl->delayCtrl[2].skwselCp1;
	ioPro.sen.sentop.phy2dlctl.bit.phy2SkwselCp2					= cphyCtrl->delayCtrl[2].skwselCp2;
	ioPro.sen.sentop.phy3dlctl.bit.phy3D0rxspeed					= cphyCtrl->delayCtrl[3].d0rxspeed;
	ioPro.sen.sentop.phy3dlctl.bit.phy3D1rxspeed					= cphyCtrl->delayCtrl[3].d1rxspeed;
	ioPro.sen.sentop.phy3dlctl.bit.phy3D2rxspeed					= cphyCtrl->delayCtrl[3].d2rxspeed;
	ioPro.sen.sentop.phy3dlctl.bit.phy3D3rxspeed					= cphyCtrl->delayCtrl[3].d3rxspeed;
	ioPro.sen.sentop.phy3dlctl.bit.phy3SkwselCp0					= cphyCtrl->delayCtrl[3].skwselCp0;
	ioPro.sen.sentop.phy3dlctl.bit.phy3SkwselCp1					= cphyCtrl->delayCtrl[3].skwselCp1;
	ioPro.sen.sentop.phy3dlctl.bit.phy3SkwselCp2					= cphyCtrl->delayCtrl[3].skwselCp2;

	ioPro.sen.sentop.phy0dskctl.bit.phy0Rxspden					= cphyCtrl->desknewCtrl[0].rxspden;
	ioPro.sen.sentop.phy0dskctl.bit.phy0Dcntnum 					= cphyCtrl->desknewCtrl[0].dcntnum;
	ioPro.sen.sentop.phy0dskctl.bit.phy0Grdwidth					= cphyCtrl->desknewCtrl[0].grdwidth;
	ioPro.sen.sentop.phy0dskctl.bit.phy0Rdwait					= cphyCtrl->desknewCtrl[0].rdwait;
	ioPro.sen.sentop.phy0dskctl.bit.phy0Vldprd					= cphyCtrl->desknewCtrl[0].vldprd;
	ioPro.sen.sentop.phy1dskctl.bit.phy1Rxspden					= cphyCtrl->desknewCtrl[1].rxspden;
	ioPro.sen.sentop.phy1dskctl.bit.phy1Dcntnum 					= cphyCtrl->desknewCtrl[1].dcntnum;
	ioPro.sen.sentop.phy1dskctl.bit.phy1Grdwidth					= cphyCtrl->desknewCtrl[1].grdwidth;
	ioPro.sen.sentop.phy1dskctl.bit.phy1Rdwait					= cphyCtrl->desknewCtrl[1].rdwait;
	ioPro.sen.sentop.phy1dskctl.bit.phy1Vldprd					= cphyCtrl->desknewCtrl[1].vldprd;
	ioPro.sen.sentop.phy2dskctl.bit.phy2Rxspden					= cphyCtrl->desknewCtrl[2].rxspden;
	ioPro.sen.sentop.phy2dskctl.bit.phy2Dcntnum 					= cphyCtrl->desknewCtrl[2].dcntnum;
	ioPro.sen.sentop.phy2dskctl.bit.phy2Grdwidth					= cphyCtrl->desknewCtrl[2].grdwidth;
	ioPro.sen.sentop.phy2dskctl.bit.phy2Rdwait					= cphyCtrl->desknewCtrl[2].rdwait;
	ioPro.sen.sentop.phy2dskctl.bit.phy2Vldprd					= cphyCtrl->desknewCtrl[2].vldprd;
	ioPro.sen.sentop.phy3dskctl.bit.phy3Rxspden					= cphyCtrl->desknewCtrl[3].rxspden;
	ioPro.sen.sentop.phy3dskctl.bit.phy3Dcntnum 					= cphyCtrl->desknewCtrl[3].dcntnum;
	ioPro.sen.sentop.phy3dskctl.bit.phy3Grdwidth					= cphyCtrl->desknewCtrl[3].grdwidth;
	ioPro.sen.sentop.phy3dskctl.bit.phy3Rdwait					= cphyCtrl->desknewCtrl[3].rdwait;
	ioPro.sen.sentop.phy3dskctl.bit.phy3Vldprd					= cphyCtrl->desknewCtrl[3].vldprd;

	ioPro.sen.sentop.pll0ctl.bit.pll0Ibcnt						= cphyCtrl->pll0Ctrl.ibcnt;
	ioPro.sen.sentop.pll0ctl.bit.pll0Ilfsel						= cphyCtrl->pll0Ctrl.ilfsel;
	ioPro.sen.sentop.pll0ctl.bit.pll0Ioclken						= cphyCtrl->pll0Ctrl.ioclken;
	ioPro.sen.sentop.pll0ctl.bit.pll0Itxpclk2aen					= cphyCtrl->pll0Ctrl.itxpclk2aen;

	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

INT32 impro_sentop_cphy_clk_ctrl( TimproSentopCphyClkCtrl* clkCtrl )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.phy0clkctl.bit.phy0Clklanesel	= clkCtrl[0].clklanesel;
	ioPro.sen.sentop.phy0clkctl.bit.phy0Clkmodesel	= clkCtrl[0].clkmodesel;
	ioPro.sen.sentop.phy0clkctl.bit.phy0Clkoutren		= clkCtrl[0].clkoutren;
	ioPro.sen.sentop.phy0clkctl.bit.phy0Clkoutlen		= clkCtrl[0].clkoutlen;
	ioPro.sen.sentop.phy1clkctl.bit.phy1Clklanesel	= clkCtrl[1].clklanesel;
	ioPro.sen.sentop.phy1clkctl.bit.phy1Clkmodesel	= clkCtrl[1].clkmodesel;
	ioPro.sen.sentop.phy1clkctl.bit.phy1Clkoutren		= clkCtrl[1].clkoutren;
	ioPro.sen.sentop.phy1clkctl.bit.phy1Clkoutlen		= clkCtrl[1].clkoutlen;
	ioPro.sen.sentop.phy2clkctl.bit.phy2Clklanesel	= clkCtrl[2].clklanesel;
	ioPro.sen.sentop.phy2clkctl.bit.phy2Clkmodesel	= clkCtrl[2].clkmodesel;
	ioPro.sen.sentop.phy2clkctl.bit.phy2Clkoutren		= clkCtrl[2].clkoutren;
	ioPro.sen.sentop.phy2clkctl.bit.phy2Clkoutlen		= clkCtrl[2].clkoutlen;
	ioPro.sen.sentop.phy3clkctl.bit.phy3Clklanesel	= clkCtrl[3].clklanesel;
	ioPro.sen.sentop.phy3clkctl.bit.phy3Clkmodesel	= clkCtrl[3].clkmodesel;
	ioPro.sen.sentop.phy3clkctl.bit.phy3Clkoutren		= clkCtrl[3].clkoutren;
	ioPro.sen.sentop.phy3clkctl.bit.phy3Clkoutlen		= clkCtrl[3].clkoutlen;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

INT32 impro_sentop_cphy_bias_ctrl( TimproSentopCphyBiasCtrl* biasCtrl )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.biasctl.bit.phy0Xbgrpd	= biasCtrl->phy0Xbgrpd;
	ioPro.sen.sentop.biasctl.bit.phy1Xbgrpd	= biasCtrl->phy1Xbgrpd;
	ioPro.sen.sentop.biasctl.bit.phy2Xbgrpd	= biasCtrl->phy2Xbgrpd;
	ioPro.sen.sentop.biasctl.bit.phy3Xbgrpd	= biasCtrl->phy3Xbgrpd;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

INT32 impro_sentop_cphy_slvs_mode_ctrl( TimproSentopCphySlvsModeCtrl* modeCtrl )
{
	impro_sentop_set_cphy_common_ctrl( 0, &modeCtrl[0].commonCtrl );
	impro_sentop_set_cphy_common_ctrl( 1, &modeCtrl[1].commonCtrl );
	impro_sentop_set_cphy_common_ctrl( 2, &modeCtrl[2].commonCtrl );
	impro_sentop_set_cphy_common_ctrl( 3, &modeCtrl[3].commonCtrl );

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.phy0mdctl.bit.phy0Pimode	= modeCtrl[0].pimode;
	ioPro.sen.sentop.phy0mdctl.bit.phy0Picnt	= modeCtrl[0].picnt;
	ioPro.sen.sentop.phy1mdctl.bit.phy1Pimode	= modeCtrl[1].pimode;
	ioPro.sen.sentop.phy1mdctl.bit.phy1Picnt	= modeCtrl[1].picnt;
	ioPro.sen.sentop.phy2mdctl.bit.phy2Pimode	= modeCtrl[2].pimode;
	ioPro.sen.sentop.phy2mdctl.bit.phy2Picnt	= modeCtrl[2].picnt;
	ioPro.sen.sentop.phy3mdctl.bit.phy3Pimode	= modeCtrl[3].pimode;
	ioPro.sen.sentop.phy3mdctl.bit.phy3Picnt	= modeCtrl[3].picnt;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}


INT32 impro_sentop_cphy_lvds_mode_ctrl( TimproSentopCphyLvdsModeCtrl* modeCtrl )
{
	impro_sentop_set_cphy_common_ctrl( 0, &modeCtrl[0].commonCtrl );
	impro_sentop_set_cphy_common_ctrl( 1, &modeCtrl[1].commonCtrl );
	impro_sentop_set_cphy_common_ctrl( 2, &modeCtrl[2].commonCtrl );
	impro_sentop_set_cphy_common_ctrl( 3, &modeCtrl[3].commonCtrl );

	return D_DDIM_OK;
}


INT32 impro_sentop_cphy_dmipi_mode_ctrl( TimproSentopCphyDmipiModeCtrl* modeCtrl )
{
	impro_sentop_set_cphy_common_ctrl( 0, &modeCtrl[0].commonCtrl );
	impro_sentop_set_cphy_common_ctrl( 1, &modeCtrl[1].commonCtrl );
	impro_sentop_set_cphy_common_ctrl( 2, &modeCtrl[2].commonCtrl );
	impro_sentop_set_cphy_common_ctrl( 3, &modeCtrl[3].commonCtrl );

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.phy0dskctl.bit.phy0Rxspden	= modeCtrl[0].rxspden;
	ioPro.sen.sentop.phy0dskctl.bit.phy0Dcntnum 	= modeCtrl[0].dcntnum;
	ioPro.sen.sentop.phy0dskctl.bit.phy0Grdwidth	= modeCtrl[0].grdwidth;
	ioPro.sen.sentop.phy0dskctl.bit.phy0Rdwait	= modeCtrl[0].rdwait;
	ioPro.sen.sentop.phy0dskctl.bit.phy0Vldprd	= modeCtrl[0].vldprd;
	ioPro.sen.sentop.phy1dskctl.bit.phy1Rxspden	= modeCtrl[1].rxspden;
	ioPro.sen.sentop.phy1dskctl.bit.phy1Dcntnum 	= modeCtrl[1].dcntnum;
	ioPro.sen.sentop.phy1dskctl.bit.phy1Grdwidth	= modeCtrl[1].grdwidth;
	ioPro.sen.sentop.phy1dskctl.bit.phy1Rdwait	= modeCtrl[1].rdwait;
	ioPro.sen.sentop.phy1dskctl.bit.phy1Vldprd	= modeCtrl[1].vldprd;
	ioPro.sen.sentop.phy2dskctl.bit.phy2Rxspden	= modeCtrl[2].rxspden;
	ioPro.sen.sentop.phy2dskctl.bit.phy2Dcntnum 	= modeCtrl[2].dcntnum;
	ioPro.sen.sentop.phy2dskctl.bit.phy2Grdwidth	= modeCtrl[2].grdwidth;
	ioPro.sen.sentop.phy2dskctl.bit.phy2Rdwait	= modeCtrl[2].rdwait;
	ioPro.sen.sentop.phy2dskctl.bit.phy2Vldprd	= modeCtrl[2].vldprd;
	ioPro.sen.sentop.phy3dskctl.bit.phy3Rxspden	= modeCtrl[3].rxspden;
	ioPro.sen.sentop.phy3dskctl.bit.phy3Dcntnum 	= modeCtrl[3].dcntnum;
	ioPro.sen.sentop.phy3dskctl.bit.phy3Grdwidth	= modeCtrl[3].grdwidth;
	ioPro.sen.sentop.phy3dskctl.bit.phy3Rdwait	= modeCtrl[3].rdwait;
	ioPro.sen.sentop.phy3dskctl.bit.phy3Vldprd	= modeCtrl[3].vldprd;

	ioPro.sen.sentop.phy0ifctl.phy0ifctl4.bit.phy0Funcseld0	= modeCtrl[0].funcseld0;
	ioPro.sen.sentop.phy0ifctl.phy0ifctl5.bit.phy0Funcseld1	= modeCtrl[0].funcseld0;
	ioPro.sen.sentop.phy0ifctl.phy0ifctl6.bit.phy0Funcseld2	= modeCtrl[0].funcseld0;
	ioPro.sen.sentop.phy0ifctl.phy0ifctl7.bit.phy0Funcseld3	= modeCtrl[0].funcseld0;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl4.bit.phy1Funcseld0	= modeCtrl[1].funcseld0;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl5.bit.phy1Funcseld1	= modeCtrl[1].funcseld0;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl6.bit.phy1Funcseld2	= modeCtrl[1].funcseld0;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl7.bit.phy1Funcseld3	= modeCtrl[1].funcseld0;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl4.bit.phy2Funcseld0	= modeCtrl[2].funcseld0;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl5.bit.phy2Funcseld1	= modeCtrl[2].funcseld0;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl6.bit.phy2Funcseld2	= modeCtrl[2].funcseld0;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl7.bit.phy2Funcseld3	= modeCtrl[2].funcseld0;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl4.bit.phy3Funcseld0	= modeCtrl[3].funcseld0;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl5.bit.phy3Funcseld1	= modeCtrl[3].funcseld0;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl6.bit.phy3Funcseld2	= modeCtrl[3].funcseld0;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl7.bit.phy3Funcseld3	= modeCtrl[3].funcseld0;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

INT32 impro_sentop_cphy_cmipi_mode_ctrl( TimproSentopCphyCmipiModeCtrl* modeCtrl )
{
	impro_sentop_set_cphy_common_ctrl( 0, &modeCtrl[0].commonCtrl );
	impro_sentop_set_cphy_common_ctrl( 1, &modeCtrl[1].commonCtrl );
	impro_sentop_set_cphy_common_ctrl( 2, &modeCtrl[2].commonCtrl );
	impro_sentop_set_cphy_common_ctrl( 3, &modeCtrl[3].commonCtrl );

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop3uicp0	= modeCtrl[0].zerop3uicp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop4uicp0	= modeCtrl[0].zerop4uicp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop5uicp0	= modeCtrl[0].zerop5uicp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop6uicp0	= modeCtrl[0].zerop6uicp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0DetcntCp0	= modeCtrl[0].detcntCp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0EqEnCp0	= modeCtrl[0].eqEnCp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0EqSetCp0	= modeCtrl[0].eqSetCp0;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop3uicp1	= modeCtrl[0].zerop3uicp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop4uicp1	= modeCtrl[0].zerop4uicp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop5uicp1	= modeCtrl[0].zerop5uicp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop6uicp1	= modeCtrl[0].zerop6uicp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0DetcntCp1	= modeCtrl[0].detcntCp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0EqEnCp1	= modeCtrl[0].eqEnCp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0EqSetCp1	= modeCtrl[0].eqSetCp1;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop3uicp2	= modeCtrl[0].zerop3uicp2;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop4uicp2	= modeCtrl[0].zerop4uicp2;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop5uicp2	= modeCtrl[0].zerop5uicp2;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop6uicp2	= modeCtrl[0].zerop6uicp2;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0DetcntCp2	= modeCtrl[0].detcntCp2;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0EqEnCp2	= modeCtrl[0].eqEnCp2;
	ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0EqSetCp2	= modeCtrl[0].eqSetCp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop3uicp0	= modeCtrl[1].zerop3uicp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop4uicp0	= modeCtrl[1].zerop4uicp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop5uicp0	= modeCtrl[1].zerop5uicp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop6uicp0	= modeCtrl[1].zerop6uicp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1DetcntCp0	= modeCtrl[1].detcntCp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1EqEnCp0	= modeCtrl[1].eqEnCp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1EqSetCp0	= modeCtrl[1].eqSetCp0;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop3uicp1	= modeCtrl[1].zerop3uicp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop4uicp1	= modeCtrl[1].zerop4uicp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop5uicp1	= modeCtrl[1].zerop5uicp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop6uicp1	= modeCtrl[1].zerop6uicp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1DetcntCp1	= modeCtrl[1].detcntCp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1EqEnCp1	= modeCtrl[1].eqEnCp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1EqSetCp1	= modeCtrl[1].eqSetCp1;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop3uicp2	= modeCtrl[1].zerop3uicp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop4uicp2	= modeCtrl[1].zerop4uicp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop5uicp2	= modeCtrl[1].zerop5uicp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop6uicp2	= modeCtrl[1].zerop6uicp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1DetcntCp2	= modeCtrl[1].detcntCp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1EqSetCp2	= modeCtrl[1].eqSetCp2;
	ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1EqEnCp2	= modeCtrl[1].eqEnCp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop3uicp0	= modeCtrl[2].zerop3uicp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop4uicp0	= modeCtrl[2].zerop4uicp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop5uicp0	= modeCtrl[2].zerop5uicp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop6uicp0	= modeCtrl[2].zerop6uicp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2DetcntCp0	= modeCtrl[2].detcntCp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2EqEnCp0	= modeCtrl[2].eqEnCp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2EqSetCp0	= modeCtrl[2].eqSetCp0;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop3uicp1	= modeCtrl[2].zerop3uicp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop4uicp1	= modeCtrl[2].zerop4uicp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop5uicp1	= modeCtrl[2].zerop5uicp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop6uicp1	= modeCtrl[2].zerop6uicp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2DetcntCp1	= modeCtrl[2].detcntCp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2EqEnCp1	= modeCtrl[2].eqEnCp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2EqSetCp1	= modeCtrl[2].eqSetCp1;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop3uicp2	= modeCtrl[2].zerop3uicp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop4uicp2	= modeCtrl[2].zerop4uicp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop5uicp2	= modeCtrl[2].zerop5uicp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop6uicp2	= modeCtrl[2].zerop6uicp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2DetcntCp2	= modeCtrl[2].detcntCp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2EqEnCp2	= modeCtrl[2].eqEnCp2;
	ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2EqSetCp2	= modeCtrl[2].eqSetCp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop3uicp0	= modeCtrl[3].zerop3uicp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop4uicp0	= modeCtrl[3].zerop4uicp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop5uicp0	= modeCtrl[3].zerop5uicp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop6uicp0	= modeCtrl[3].zerop6uicp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3DetcntCp0	= modeCtrl[3].detcntCp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3EqEnCp0	= modeCtrl[3].eqEnCp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3EqSetCp0	= modeCtrl[3].eqSetCp0;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop3uicp1	= modeCtrl[3].zerop3uicp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop4uicp1	= modeCtrl[3].zerop4uicp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop5uicp1	= modeCtrl[3].zerop5uicp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop6uicp1	= modeCtrl[3].zerop6uicp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3DetcntCp1	= modeCtrl[3].detcntCp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3EqEnCp1	= modeCtrl[3].eqEnCp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3EqSetCp1	= modeCtrl[3].eqSetCp1;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop3uicp2	= modeCtrl[3].zerop3uicp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop4uicp2	= modeCtrl[3].zerop4uicp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop5uicp2	= modeCtrl[3].zerop5uicp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop6uicp2	= modeCtrl[3].zerop6uicp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3DetcntCp2	= modeCtrl[3].detcntCp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3EqEnCp2	= modeCtrl[3].eqEnCp2;
	ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3EqSetCp2	= modeCtrl[3].eqSetCp2;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

INT32 impro_sentop_cphy_ext_signal_ctrl( TimproSentopCphyIfExtSignalCtrl* extSignal )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.phy0ifctl.phy0ifctl1.bit.phy0Clksetsel	= extSignal[0].clksetsel;
	ioPro.sen.sentop.phy0ifctl.phy0ifctl2.bit.phy0CphysetCp0	= extSignal[0].cphysetCp0;
	ioPro.sen.sentop.phy0ifctl.phy0ifctl2.bit.phy0CphysetCp1	= extSignal[0].cphysetCp1;
	ioPro.sen.sentop.phy0ifctl.phy0ifctl2.bit.phy0CphysetCp2	= extSignal[0].cphysetCp2;
	ioPro.sen.sentop.phy0ifctl.phy0ifctl3.bit.phy0Funcselck	= extSignal[0].funcselck;
	ioPro.sen.sentop.phy0ifctl.phy0ifctl4.bit.phy0Funcseld0	= extSignal[0].funcseld0;
	ioPro.sen.sentop.phy0ifctl.phy0ifctl5.bit.phy0Funcseld1	= extSignal[0].funcseld1;
	ioPro.sen.sentop.phy0ifctl.phy0ifctl6.bit.phy0Funcseld2	= extSignal[0].funcseld2;
	ioPro.sen.sentop.phy0ifctl.phy0ifctl7.bit.phy0Funcseld3	= extSignal[0].funcseld3;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl1.bit.phy1Clksetsel	= extSignal[1].clksetsel;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl2.bit.phy1CphysetCp0	= extSignal[1].cphysetCp0;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl2.bit.phy1CphysetCp1	= extSignal[1].cphysetCp1;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl2.bit.phy1CphysetCp2	= extSignal[1].cphysetCp2;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl3.bit.phy1Funcselck	= extSignal[1].funcselck;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl4.bit.phy1Funcseld0	= extSignal[1].funcseld0;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl5.bit.phy1Funcseld1	= extSignal[1].funcseld1;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl6.bit.phy1Funcseld2	= extSignal[1].funcseld2;
	ioPro.sen.sentop.phy1ifctl.phy1ifctl7.bit.phy1Funcseld3	= extSignal[1].funcseld3;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl1.bit.phy2Clksetsel	= extSignal[2].clksetsel;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl2.bit.phy2CphysetCp0	= extSignal[2].cphysetCp0;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl2.bit.phy2CphysetCp1	= extSignal[2].cphysetCp1;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl2.bit.phy2CphysetCp2	= extSignal[2].cphysetCp2;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl3.bit.phy2Funcselck	= extSignal[2].funcselck;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl4.bit.phy2Funcseld0	= extSignal[2].funcseld0;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl5.bit.phy2Funcseld1	= extSignal[2].funcseld1;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl6.bit.phy2Funcseld2	= extSignal[2].funcseld2;
	ioPro.sen.sentop.phy2ifctl.phy2ifctl7.bit.phy2Funcseld3	= extSignal[2].funcseld3;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl1.bit.phy3Clksetsel	= extSignal[3].clksetsel;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl2.bit.phy3CphysetCp0	= extSignal[3].cphysetCp0;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl2.bit.phy3CphysetCp1	= extSignal[3].cphysetCp1;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl2.bit.phy3CphysetCp2	= extSignal[3].cphysetCp2;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl3.bit.phy3Funcselck	= extSignal[3].funcselck;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl4.bit.phy3Funcseld0	= extSignal[3].funcseld0;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl5.bit.phy3Funcseld1	= extSignal[3].funcseld1;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl6.bit.phy3Funcseld2	= extSignal[3].funcseld2;
	ioPro.sen.sentop.phy3ifctl.phy3ifctl7.bit.phy3Funcseld3	= extSignal[3].funcseld3;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

INT32 impro_sentop_cphy_get_des_knew_ctrl( TimproSentopCphyDesknewMonitor* cphyMoni )
{
#ifdef CO_PARAM_CHECK
	if (cphyMoni == NULL){
		Ddim_Assertion(("I:impro_sentop_cphy_get_des_knew_ctrl error. cphyMoni=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	cphyMoni->desknew_moni[0].dtypemon0	= ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon0;
	cphyMoni->desknew_moni[0].dtypemon1	= ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon1;
	cphyMoni->desknew_moni[0].dtypemon2	= ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon2;
	cphyMoni->desknew_moni[0].dtypemon3	= ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon3;
	cphyMoni->desknew_moni[0].vldwindow0	= ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Vldwindow0;
	cphyMoni->desknew_moni[0].vldwindow1	= ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Vldwindow1;
	cphyMoni->desknew_moni[0].vldwindow2	= ioPro.sen.sentop.phy0dskmoni.phy0dskmoni2.bit.phy0Vldwindow2;
	cphyMoni->desknew_moni[0].vldwindow3	= ioPro.sen.sentop.phy0dskmoni.phy0dskmoni2.bit.phy0Vldwindow3;
	cphyMoni->desknew_moni[1].dtypemon0	= ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon0;
	cphyMoni->desknew_moni[1].dtypemon1	= ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon1;
	cphyMoni->desknew_moni[1].dtypemon2	= ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon2;
	cphyMoni->desknew_moni[1].dtypemon3	= ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon3;
	cphyMoni->desknew_moni[1].vldwindow0	= ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Vldwindow0;
	cphyMoni->desknew_moni[1].vldwindow1	= ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Vldwindow1;
	cphyMoni->desknew_moni[1].vldwindow2	= ioPro.sen.sentop.phy1dskmoni.phy1dskmoni2.bit.phy1Vldwindow2;
	cphyMoni->desknew_moni[1].vldwindow3	= ioPro.sen.sentop.phy1dskmoni.phy1dskmoni2.bit.phy1Vldwindow3;
	cphyMoni->desknew_moni[2].dtypemon0	= ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon0;
	cphyMoni->desknew_moni[2].dtypemon1	= ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon1;
	cphyMoni->desknew_moni[2].dtypemon2	= ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon2;
	cphyMoni->desknew_moni[2].dtypemon3	= ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon3;
	cphyMoni->desknew_moni[2].vldwindow0	= ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Vldwindow0;
	cphyMoni->desknew_moni[2].vldwindow1	= ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Vldwindow1;
	cphyMoni->desknew_moni[2].vldwindow2	= ioPro.sen.sentop.phy2dskmoni.phy2dskmoni2.bit.phy2Vldwindow2;
	cphyMoni->desknew_moni[2].vldwindow3	= ioPro.sen.sentop.phy2dskmoni.phy2dskmoni2.bit.phy2Vldwindow3;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

INT32 impro_sentop_cphy_get_delay_line_monitor( TimproSentopCphyDelaylineMonitor* cphyMoni )
{
#ifdef CO_PARAM_CHECK
	if (cphyMoni == NULL){
		Ddim_Assertion(("I:impro_sentop_cphy_get_delay_line_monitor error. cphyMoni=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	cphyMoni->delayline_moni[0].phy_code_cp0	= ioPro.sen.sentop.phy0dlmoni.phy0dlmoni1.bit.phy0CodeCp0;
	cphyMoni->delayline_moni[0].phy_code_cp1	= ioPro.sen.sentop.phy0dlmoni.phy0dlmoni2.bit.phy0CodeCp1;
	cphyMoni->delayline_moni[0].phy_code_cp2	= ioPro.sen.sentop.phy0dlmoni.phy0dlmoni3.bit.phy0CodeCp2;
	cphyMoni->delayline_moni[1].phy_code_cp0	= ioPro.sen.sentop.phy1dlmoni.phy1dlmoni1.bit.phy1CodeCp0;
	cphyMoni->delayline_moni[1].phy_code_cp1	= ioPro.sen.sentop.phy1dlmoni.phy1dlmoni2.bit.phy1CodeCp1;
	cphyMoni->delayline_moni[1].phy_code_cp2	= ioPro.sen.sentop.phy1dlmoni.phy1dlmoni3.bit.phy1CodeCp2;
	cphyMoni->delayline_moni[2].phy_code_cp0	= ioPro.sen.sentop.phy2dlmoni.phy2dlmoni1.bit.phy2CodeCp0;
	cphyMoni->delayline_moni[2].phy_code_cp1	= ioPro.sen.sentop.phy2dlmoni.phy2dlmoni2.bit.phy2CodeCp1;
	cphyMoni->delayline_moni[2].phy_code_cp2	= ioPro.sen.sentop.phy2dlmoni.phy2dlmoni3.bit.phy2CodeCp2;
	cphyMoni->delayline_moni[3].phy_code_cp0	= ioPro.sen.sentop.phy3dlmoni.phy3dlmoni1.bit.phy3CodeCp0;
	cphyMoni->delayline_moni[3].phy_code_cp1	= ioPro.sen.sentop.phy3dlmoni.phy3dlmoni2.bit.phy3CodeCp1;
	cphyMoni->delayline_moni[3].phy_code_cp2	= ioPro.sen.sentop.phy3dlmoni.phy3dlmoni3.bit.phy3CodeCp2;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

INT32 impro_sentop_cphy_get_common_if_monitor( TimproSentopCphyCommonIfMonitor* cphyMoni )
{
#ifdef CO_PARAM_CHECK
	if (cphyMoni == NULL){
		Ddim_Assertion(("I:impro_sentop_cphy_get_delay_line_monitor error. cphyMoni=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	cphyMoni->phy0Cdrmon	= ioPro.sen.sentop.phycmoni.phycmoni1.bit.phy0Cdrmon;
	cphyMoni->phy1Cdrmon	= ioPro.sen.sentop.phycmoni.phycmoni2.bit.phy1Cdrmon;
	cphyMoni->phy2Cdrmon	= ioPro.sen.sentop.phycmoni.phycmoni3.bit.phy2Cdrmon;
	cphyMoni->phy3Cdrmon	= ioPro.sen.sentop.phycmoni.phycmoni4.bit.phy3Cdrmon;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

INT32 impro_sentop_pseudo_vd_issue( VOID )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sentop.pseudeVd.word = 1;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}


ImproSentop* 	impro_sentop_new()
{
	ImproSentop* self = k_object_new_with_private(IMPRO_TYPE_SENTOP,sizeof(ImproSentopPrivate));
	ImproSentopPrivate* priv = IMPRO_SENTOP_GET_PRIVATE(self);
	
	e_warning_o(self," impro_sentop_new \n");
	return self;
}
