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

#include"improsenslvs.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSenslvs, impro_senslvs);
#define IMPRO_SENSLVS_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSenslvsPrivate, IMPRO_TYPE_SENSLVS));


/*宏定义区域*/
// SLVS-ECG Trigger Force STOP
#define ImproSenslvs_D_IM_PRO_SLVS_TRG_FORCE_STOP	(0)
// SLVS-ECG Trigger Frame STOP
#define ImproSenslvs_D_IM_PRO_SLVS_TRG_FRAME_STOP	(2)
// SLVS-EC Software reset
#define ImproSenslvs_D_IM_PRO_SLVS_SW_RESET			(1)
// SLVS-EC Software reset release
#define ImproSenslvs_D_IM_PRO_SLVS_SW_RESET_RELEASE	(0)
// SLVS-EC Configuration update
#define ImproSenslvs_D_IM_PRO_SLVS_CFG_UPDATE		(1)
// SLVS-EC PMA macro optional initialization disabled.
#define ImproSenslvs_D_IM_PRO_SLVS_PMA_OPT_INIT_DIS	(0)
#define ImproSenslvs_D_IM_PRO_SLVS_INIT_WAIT_PD		(5)

/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSenslvsPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/


/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_senslvs_constructor(ImproSenslvs *self)
{
	ImproSenslvsPrivate *priv = IMPRO_SENSLVS_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_senslvs_destructor(ImproSenslvs *self)
{
	ImproSenslvsPrivate *priv = IMPRO_SENSLVS_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
Software reset of SLVS-EC RX macro(excluding PMA, termination resistor adjustment circuit and CNT block).
@param[in]	streamType : stream type of SLVS
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_senslvs_sr( E_IM_PRO_SLVS_STREAM_TYPE streamType )
{
#ifdef CO_PARAM_CHECK
	if( streamType > E_IM_PRO_SLVS_STREAM_TYPE_BOTH ) {
		Ddim_Assertion(("I:impro_senslvs_sr stream type illegal. streamType=%d\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	switch( streamType ) {
		case E_IM_PRO_SLVS_STREAM_TYPE_A:
			ioPro.sen.slvsec.common.sr.bit.inita	= ImproSenslvs_D_IM_PRO_SLVS_SW_RESET;
			break;

		case E_IM_PRO_SLVS_STREAM_TYPE_B:
			ioPro.sen.slvsec.common.sr.bit.initb	= ImproSenslvs_D_IM_PRO_SLVS_SW_RESET;
			break;

		//case E_IM_PRO_SLVS_STREAM_TYPE_BOTH:
		default:
			ioPro.sen.slvsec.common.sr.bit.inita	= ImproSenslvs_D_IM_PRO_SLVS_SW_RESET;
			ioPro.sen.slvsec.common.sr.bit.initb	= ImproSenslvs_D_IM_PRO_SLVS_SW_RESET;
			break;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}

/**
Update of the SLVS-EC configuration parameters.
@param[in]	streamType : stream type of SLVS
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_senslvs_update_cfg( E_IM_PRO_SLVS_STREAM_TYPE streamType )
{
#ifdef CO_PARAM_CHECK
	if( streamType > E_IM_PRO_SLVS_STREAM_TYPE_BOTH ) {
		Ddim_Assertion(("I:Im_PRO_SLVS_SR_Rls_And_Update_Cfg stream type illegal. streamType=%d\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	switch( streamType ) {
		case E_IM_PRO_SLVS_STREAM_TYPE_A:
			ioPro.sen.slvsec.common.sr.bit.upda	= ImproSenslvs_D_IM_PRO_SLVS_CFG_UPDATE;
			break;

		case E_IM_PRO_SLVS_STREAM_TYPE_B:
			ioPro.sen.slvsec.common.sr.bit.updb	= ImproSenslvs_D_IM_PRO_SLVS_CFG_UPDATE;
			break;

		//case E_IM_PRO_SLVS_STREAM_TYPE_BOTH:
		default:
			ioPro.sen.slvsec.common.sr.bit.upda	= ImproSenslvs_D_IM_PRO_SLVS_CFG_UPDATE;
			ioPro.sen.slvsec.common.sr.bit.updb	= ImproSenslvs_D_IM_PRO_SLVS_CFG_UPDATE;
			break;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}

/**
Software reset release of SLVS-EC.
@param[in]	streamType : stream type of SLVS
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_senslvs_sr_rlease( E_IM_PRO_SLVS_STREAM_TYPE streamType )
{
#ifdef CO_PARAM_CHECK
	if( streamType > E_IM_PRO_SLVS_STREAM_TYPE_BOTH ) {
		Ddim_Assertion(("I:Im_PRO_SLVS_SR_Rls_And_Update_Cfg stream type illegal. streamType=%d\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	switch( streamType ) {
		case E_IM_PRO_SLVS_STREAM_TYPE_A:
			ioPro.sen.slvsec.common.sr.bit.inita	= ImproSenslvs_D_IM_PRO_SLVS_SW_RESET_RELEASE;
			break;

		case E_IM_PRO_SLVS_STREAM_TYPE_B:
			ioPro.sen.slvsec.common.sr.bit.initb	= ImproSenslvs_D_IM_PRO_SLVS_SW_RESET_RELEASE;
			break;

		//case E_IM_PRO_SLVS_STREAM_TYPE_BOTH:
		default:
			ioPro.sen.slvsec.common.sr.bit.inita	= ImproSenslvs_D_IM_PRO_SLVS_SW_RESET_RELEASE;
			ioPro.sen.slvsec.common.sr.bit.initb	= ImproSenslvs_D_IM_PRO_SLVS_SW_RESET_RELEASE;
			break;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}


/**
Physical Media Attachment initialization.
@param[in]	pmaInit : PMA initialization parameters.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
INT32 impro_senslvs_pma_init( TimproSlvsPmaInit* pmaInit )
{
#ifdef CO_PARAM_CHECK
	if (pmaInit == NULL){
		Ddim_Assertion(("I:impro_senslvs_pma_init error. pmaInit=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.slvsec.common.phycr2.bit.pdx			= ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_NORMAL;
	im_pro_wait_usec( ImproSenslvs_D_IM_PRO_SLVS_INIT_WAIT_PD );

	ioPro.sen.slvsec.common.phycr1.bit.invdata		= ( pmaInit->invertSel.lane0 << 0 |
														pmaInit->invertSel.lane1 << 1 |
														pmaInit->invertSel.lane2 << 2 |
														pmaInit->invertSel.lane3 << 3 |
														pmaInit->invertSel.lane4 << 4 |
														pmaInit->invertSel.lane5 << 5 |
														pmaInit->invertSel.lane6 << 6 |
														pmaInit->invertSel.lane7 << 7 );
	ioPro.sen.slvsec.common.phycr1.bit.ifvdcnt		= pmaInit->multiplicationFactor;

	if( pmaInit->optInitParam.enabled != ImproSenslvs_D_IM_PRO_SLVS_PMA_OPT_INIT_DIS ) {
		ioPro.sen.slvsec.common.phycr0.bit.refsel	= pmaInit->optInitParam.refsel;
		ioPro.sen.slvsec.common.phycr0.bit.icpcode	= pmaInit->optInitParam.icpcode;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}


/**
Physical Media Attachment Power Down control.
@param[in]	pmaPd : PMA Power Down control parameters.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
INT32 impro_senslvs_pma_power_down( TimproSlvsPmaPd* pmaPd )
{
#ifdef CO_PARAM_CHECK
	if (pmaPd == NULL){
		Ddim_Assertion(("I:impro_senslvs_pma_power_down error. pmaPd=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.slvsec.common.phycr2.bit.irxpdx0		= pmaPd->lane0PdState;
	ioPro.sen.slvsec.common.phycr2.bit.irxpdx1		= pmaPd->lane1PdState;
	ioPro.sen.slvsec.common.phycr2.bit.irxpdx2		= pmaPd->lane2PdState;
	ioPro.sen.slvsec.common.phycr2.bit.irxpdx3		= pmaPd->lane3PdState;
	ioPro.sen.slvsec.common.phycr2.bit.irxpdx4		= pmaPd->lane4PdState;
	ioPro.sen.slvsec.common.phycr2.bit.irxpdx5		= pmaPd->lane5PdState;
	ioPro.sen.slvsec.common.phycr2.bit.irxpdx6		= pmaPd->lane6PdState;
	ioPro.sen.slvsec.common.phycr2.bit.irxpdx7		= pmaPd->lane7PdState;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}

/**
Physical Media Attachment PLL Power Down control.
@param[in]	pdState : PMA PLL Power Down control parameters.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
INT32 impro_senslvs_pma_pll_power_down( EimproSlvsPdState pdState )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.slvsec.common.phycr2.bit.ipdpllx	= pdState;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}

/**
SLVS-EC Common Configuration.
@param[in]	commonCfg : Common configuration parameters.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
INT32 impro_senslvs_common_cfg( TimproSlvsCommonCfg* commonCfg )
{
#ifdef CO_PARAM_CHECK
	if (commonCfg == NULL){
		Ddim_Assertion(("I:impro_senslvs_common_cfg error. commonCfg=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.slvsec.common.attr1.bit.StandbyLength		= commonCfg->StandbyLength;
	ioPro.sen.slvsec.common.attr1.bit.StandbySymbolType	= commonCfg->StandbySymbolType;
	ioPro.sen.slvsec.common.attr1.bit.StandbySymbol		= commonCfg->StandbySymbol;
	ioPro.sen.slvsec.common.attr2.bit.DeskewInterval		= commonCfg->DeskewInterval;
	ioPro.sen.slvsec.common.attr2.bit.DeskewLength			= commonCfg->DeskewLength;
	ioPro.sen.slvsec.common.attr2.bit.DeskewSymbolType		= commonCfg->DeskewSymbolType;
	ioPro.sen.slvsec.common.attr2.bit.DeskewSymbol			= commonCfg->DeskewSymbol;
	ioPro.sen.slvsec.common.attr3.bit.IdleSymbolType1		= commonCfg->IdleSymbolType1;
	ioPro.sen.slvsec.common.attr3.bit.IdleSymbol1			= commonCfg->IdleSymbol1;
	ioPro.sen.slvsec.common.attr3.bit.IdleSymbolType0		= commonCfg->IdleSymbolType0;
	ioPro.sen.slvsec.common.attr3.bit.IdleSymbol0			= commonCfg->IdleSymbol0;
	ioPro.sen.slvsec.common.attr4.bit.IdleSymbolType3		= commonCfg->IdleSymbolType3;
	ioPro.sen.slvsec.common.attr4.bit.IdleSymbol3			= commonCfg->IdleSymbol3;
	ioPro.sen.slvsec.common.attr4.bit.IdleSymbolType2		= commonCfg->IdleSymbolType2;
	ioPro.sen.slvsec.common.attr4.bit.IdleSymbol2			= commonCfg->IdleSymbol2;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}


/**
SLVS-EC Configuration.
@param[in]	streamType : stream type of SLVS
@param[in]	slvsCtrl : configuration parameters for each stream.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
INT32 impro_senslvs_ctrl( E_IM_PRO_SLVS_STREAM_TYPE streamType, TimproSlvsCtrl* slvsCtrl )
{
#ifdef CO_PARAM_CHECK
	if (slvsCtrl == NULL){
		Ddim_Assertion(("I:impro_senslvs_ctrl error. streamType=%d slvsCtrl=NULL\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( streamType > E_IM_PRO_SLVS_STREAM_TYPE_B ) {
		Ddim_Assertion(("I:impro_senslvs_ctrl stream type illegal. streamType=%d\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.slvsec.stream[streamType].rampd.bit.rampd		= slvsCtrl->ramPdState;
	ioPro.sen.slvsec.stream[streamType].trgr.bit.vden			= slvsCtrl->vdoutCtrl;
	ioPro.sen.slvsec.stream[streamType].cfgr0.bit.ecccrc		= slvsctrl->ecccrcopt;
	iopro.sen.slvsec.stream[streamtype].mmode.bit.lnmaxclp	= slvsCtrl->expectVal;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}


/**
SLVS-EC Mode Configuration.
@param[in]	streamType : stream type of SLVS
@param[in]	modeCtrl : mode configuration parameters for each stream.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
INT32 impro_senslvs_mode_cfg( E_IM_PRO_SLVS_STREAM_TYPE streamType, TimproSlvsModeCfg* modeCtrl )
{
#ifdef CO_PARAM_CHECK
	if (modeCtrl == NULL){
		Ddim_Assertion(("I:impro_senslvs_mode_cfg error. streamType=%d modeCtrl=NULL\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( streamType > E_IM_PRO_SLVS_STREAM_TYPE_B ) {
		Ddim_Assertion(("I:impro_senslvs_mode_cfg stream type illegal. streamType=%d\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.slvsec.stream[streamType].cfgr0.bit.PixelBit	= modeCtrl->pixelbit;
	ioPro.sen.slvsec.stream[streamType].cfgr0.bit.LaneNum		= modeCtrl->lanenum;
	ioPro.sen.slvsec.stream[streamType].cfgr1.bit.LineLength	= modeCtrl->linelength;
	ioPro.sen.slvsec.stream[streamType].outmd.bit.outmd		= modeCtrl->outputFormat;
	ioPro.sen.slvsec.stream[streamType].lswap.bit.l0out		= modeCtrl->swapLane[0];
	ioPro.sen.slvsec.stream[streamType].lswap.bit.l1out		= modeCtrl->swapLane[1];
	ioPro.sen.slvsec.stream[streamType].lswap.bit.l2out		= modeCtrl->swapLane[2];
	ioPro.sen.slvsec.stream[streamType].lswap.bit.l3out		= modeCtrl->swapLane[3];
	ioPro.sen.slvsec.stream[streamType].lswap.bit.l4out		= modeCtrl->swapLane[4];
	ioPro.sen.slvsec.stream[streamType].lswap.bit.l5out		= modeCtrl->swapLane[5];
	ioPro.sen.slvsec.stream[streamType].lswap.bit.l6out		= modeCtrl->swapLane[6];
	ioPro.sen.slvsec.stream[streamType].lswap.bit.l7out		= modeCtrl->swapLane[7];
	ioPro.sen.slvsec.stream[streamType].vlane.bit.lane0		= modeCtrl->valid_lane.lane0;
	ioPro.sen.slvsec.stream[streamType].vlane.bit.lane1		= modeCtrl->valid_lane.lane1;
	ioPro.sen.slvsec.stream[streamType].vlane.bit.lane2		= modeCtrl->valid_lane.lane2;
	ioPro.sen.slvsec.stream[streamType].vlane.bit.lane3		= modeCtrl->valid_lane.lane3;
	ioPro.sen.slvsec.stream[streamType].vlane.bit.lane4		= modeCtrl->valid_lane.lane4;
	ioPro.sen.slvsec.stream[streamType].vlane.bit.lane5		= modeCtrl->valid_lane.lane5;
	ioPro.sen.slvsec.stream[streamType].vlane.bit.lane6		= modeCtrl->valid_lane.lane6;
	ioPro.sen.slvsec.stream[streamType].vlane.bit.lane7		= modeCtrl->valid_lane.lane7;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}


/**
SLVS-EC Trimming Configuration.
@param[in]	streamType : stream type of SLVS
@param[in]	trimCtrl : trimming configuration parameters for each stream.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
INT32 impro_senslvs_trim_cfg( E_IM_PRO_SLVS_STREAM_TYPE streamType, TimproSlvsTrimCfg* trimCtrl )
{
#ifdef CO_PARAM_CHECK
	if (trimCtrl == NULL){
		Ddim_Assertion(("I:impro_senslvs_trim_cfg error. streamType=%d trimCtrl=NULL\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( streamType > E_IM_PRO_SLVS_STREAM_TYPE_B ) {
		Ddim_Assertion(("I:impro_senslvs_trim_cfg stream type illegal. streamType=%d\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.slvsec.stream[streamType].outmd.bit.trmg	= trimCtrl->enabled;
	ioPro.sen.slvsec.stream[streamType].hsadd.bit.hsadd	= trimCtrl->startX;
	ioPro.sen.slvsec.stream[streamType].hsize.bit.hsize	= trimCtrl->width;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}



/**
Get SLVS-EC status.
@param[out]	status : status parameter pointer.
*/
INT32 impro_senslvs_get_status( E_IM_PRO_SLVS_STREAM_TYPE streamType, TimproSlvsStatus* status )
{
#ifdef CO_PARAM_CHECK
	if (status == NULL){
		Ddim_Assertion(("I:impro_senslvs_get_status error. streamType=%d status=NULL\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( streamType > E_IM_PRO_SLVS_STREAM_TYPE_B ) {
		Ddim_Assertion(("I:impro_senslvs_get_status stream type illegal. streamType=%d\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	status->embeddedDataDetect		= (EimproSlvsStatusEbd)ioPro.sen.slvsec.stream[streamType].ebdst.bit.ebd;
	status->ebdStoredLineNum			= ioPro.sen.slvsec.stream[streamType].ebdst.bit.lnum;
	status->expectValueDiscontinuity	= ioPro.sen.slvsec.stream[streamType].lnest.bit.expln;
	status->lineNumDiscontinuity		= ioPro.sen.slvsec.stream[streamType].lnest.bit.detln;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}


/**
SLVS-EC macro start.
*/
INT32 impro_senslvs_status( E_IM_PRO_SLVS_STREAM_TYPE streamType )
{
#ifdef CO_PARAM_CHECK
	if( streamType > E_IM_PRO_SLVS_STREAM_TYPE_BOTH ) {
		Ddim_Assertion(("I:impro_senslvs_status stream type illegal. streamType=%d\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	if( streamType == E_IM_PRO_SLVS_STREAM_TYPE_BOTH ) {
		ioPro.sen.slvsec.stream[E_IM_PRO_SLVS_STREAM_TYPE_A].trgr.bit.trg	= D_IM_PRO_TRG_START;
		ioPro.sen.slvsec.stream[E_IM_PRO_SLVS_STREAM_TYPE_B].trgr.bit.trg	= D_IM_PRO_TRG_START;
	}
	else {
		ioPro.sen.slvsec.stream[streamType].trgr.bit.trg	= D_IM_PRO_TRG_START;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	if( streamType == E_IM_PRO_SLVS_STREAM_TYPE_BOTH ) {
		im_pro_sen_set_start_status(D_IM_SEN_STATUS_SLVSEC0, 0);
		im_pro_sen_set_start_status(D_IM_SEN_STATUS_SLVSEC1, 0);
	}
	else {
		im_pro_sen_set_start_status(D_IM_SEN_STATUS_SLVSEC0, streamType);
	}

	return D_DDIM_OK;
}


/**
Stop SLVS-EC information
@param[in]	force : force stop option
*/
INT32 impro_senslvs_stop( E_IM_PRO_SLVS_STREAM_TYPE streamType, UCHAR force )
{
	UCHAR stop_type = ImproSenslvs_D_IM_PRO_SLVS_TRG_FRAME_STOP;

#ifdef CO_PARAM_CHECK
	if( streamType > E_IM_PRO_SLVS_STREAM_TYPE_BOTH ) {
		Ddim_Assertion(("I:impro_senslvs_stop stream type illegal. streamType=%d\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	if (force == 0){
		// frame stop
		stop_type = ImproSenslvs_D_IM_PRO_SLVS_TRG_FRAME_STOP;
	}
	else{
		// force stop
		stop_type = ImproSenslvs_D_IM_PRO_SLVS_TRG_FORCE_STOP;
	}

	if( streamType == E_IM_PRO_SLVS_STREAM_TYPE_BOTH ) {
		ioPro.sen.slvsec.stream[E_IM_PRO_SLVS_STREAM_TYPE_A].trgr.bit.trg = stop_type;
		ioPro.sen.slvsec.stream[E_IM_PRO_SLVS_STREAM_TYPE_B].trgr.bit.trg = stop_type;
	}
	else {
		ioPro.sen.slvsec.stream[streamType].trgr.bit.trg = stop_type;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	if( streamType == E_IM_PRO_SLVS_STREAM_TYPE_BOTH ) {
		im_pro_sen_set_stop_status(D_IM_SEN_STATUS_SLVSEC0, 0);
		im_pro_sen_set_stop_status(D_IM_SEN_STATUS_SLVSEC1, 0);
	}
	else {
		im_pro_sen_set_stop_status(D_IM_SEN_STATUS_SLVSEC0, streamType);
	}

	return D_DDIM_OK;
}

/**
wait end of SLVS-EC macro.
@param[in]		waiptn   : waiting end cause. (bit field)
						<ul><li>@ref D_IM_PRO_SLVS_INTST_FSI_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_INTST_FSO_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_INTST_FEI_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_INTST_FEO_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_INTST_RDY_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_INTST_STBY_WAITEND_FLG</ul>
@param[in]		tmout    : timeout.
@param[out]		p_flgptn : end cause. (bit field)
						<ul><li>@ref D_IM_PRO_SLVS_INTST_FSI_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_INTST_FSO_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_INTST_FEI_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_INTST_FEO_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_INTST_RDY_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_INTST_STBY_WAITEND_FLG</ul>
@retval			D_DDIM_OK                  : SLVS-EC normal end. and set end cause to p_flgptn.
@retval			D_IM_PRO_INPUT_PARAM_ERROR : parameter error.
@retval			ImproSenslvs_D_IM_PRO_TIMEOUT     : wait timeout.
*/
INT32 impro_senslvs_wait_end( DDIM_USER_FLGPTN* const p_flgptn,
				const DDIM_USER_FLGPTN waiptn, const DDIM_USER_TMO tmout )
{
	DDIM_USER_FLGPTN	flgptn;
	DDIM_USER_ER		ercd;

#ifdef CO_PARAM_CHECK
	if( (waiptn & ImproSenslvs_D_IM_PRO_SLVS_INTST_ALL_WAITEND_FLG) != waiptn ) {
		// Parameter setting error
		Ddim_Assertion(("I:impro_senslvs_wait_end error. waiptn\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	Im_Pro_Dsb();

	switch( DDIM_User_Twai_Flg( FID_IM_SEN, waiptn, D_DDIM_USER_TWF_ORW, &flgptn, tmout ) ) {
		case D_DDIM_USER_E_OK:
			flgptn = waiptn & flgptn;
			ercd = DDIM_User_Clr_Flg( FID_IM_SEN, ~flgptn );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "impro_senslvs_wait_end: invalid FID.\n" ));
				return ImproSenslvs_D_IM_PRO_SYSTEM_ERROR;
			}
			if( p_flgptn != NULL ) {
				*p_flgptn = flgptn;
			}
			return D_DDIM_OK;
		case D_DDIM_USER_E_TMOUT:
			Ddim_Print(( "impro_senslvs_wait_end twai_flg TimeOut return\n" ));
			return ImproSenslvs_D_IM_PRO_TIMEOUT;
		default:
			Ddim_Print(( "impro_senslvs_wait_end twai_flg NG return\n" ));
			return D_IM_PRO_INPUT_PARAM_ERROR;
	}
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSenslvs类的一个实例
 *
 */
ImproSenslvs* 	impro_senslvs_new()
{
	ImproSenslvs* self = k_object_new_with_private(IMPRO_TYPE_SENSLVS,sizeof(ImproSenslvsPrivate));
	ImproSenslvsPrivate* priv = IMPRO_SENSLVS_GET_PRIVATE(self);
	
	e_warning_o(self," impro_senslvs_new \n");
	return self;
}
