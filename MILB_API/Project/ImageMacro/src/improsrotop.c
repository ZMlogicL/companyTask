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
#include "improbase.h"
#include"improsrotop.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSrotop, impro_srotop);
#define IMPRO_SROTOP_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSrotopPrivate, IMPRO_TYPE_SROTOP));


/*宏定义区域*/
/* started check	*/
#define ImproSrotop_IM_PRO_SRO_GET_START_STATUS(st, ch)		(((S_G_IM_SRO_START_Status[((st) >> 28) \
																												& 0xf] & (((st) & 0x0fffffff) << (ch))) != 0) ? TRUE : FALSE)
/* started check	*/
#define ImproSrotop_IM_PRO_SRO_GET_STOP_ALL()				(((S_G_IM_SRO_START_Status[0] | S_G_IM_SRO_START_Status[1]\
																											| S_G_IM_SRO_START_Status[2]) != 0) ? FALSE : TRUE)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSrotopPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/


/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_srotop_constructor(ImproSrotop *self)
{
	ImproSrotopPrivate *priv = IMPRO_SROTOP_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_srotop_destructor(ImproSrotop *self)
{
	ImproSrotopPrivate *priv = IMPRO_SROTOP_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/********************************************************/
/*	SRO Top												*/
/********************************************************/
/**
SROTOP Macro initialize
@param[in]	unitNo : Unit number.
@remarks	Please Call at the time of system starting.
*/
VOID impro_srotop_init( E_IM_PRO_UNIT_NUM unitNo )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	// Software release
	ioPro.imgPipe[unitNo].sro.srotop.sr.bit.sr = D_IM_PRO_SR_RELEASE;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
}

/**
SROTOP Macro software reset
@param[in]	unitNo : Unit number.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: All macro not stopped NG
*/
INT32 impro_srotop_sw_reset( E_IM_PRO_UNIT_NUM unitNo )
{
#ifdef CO_PARAM_CHECK
	//not ALL Stopped
	if (ImproSrotop_IM_PRO_SRO_GET_STOP_ALL() == FALSE){
		Ddim_Print(("I:impro_srotop_sw_reset. macro not stopped error. \n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif	/* CO_ACT_PRO_CLOCK */

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	// Software reset
	ioPro.imgPipe[unitNo].sro.srotop.sr.bit.sr = D_IM_PRO_SR_RESET;

	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
SROTOP Macro clock control
@param[in]	unitNo : Unit number.
@param[in]	clkType	: SROTOP Macro clock type
@param[in]	onOff		: 0:clock on 1:clock off
@param[in]	waitSkip	: 0:non wait 1:wait 1ms. for wait PROCLK/CDK 5 cycle.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srotop_control_clock( E_IM_PRO_UNIT_NUM unitNo, EimproSrotopClkType clkType, UCHAR onOff, UCHAR waitSkip )
{
	UINT32 cpuClkHz;
	UINT32 macroClkHz;
	EimproClkBlockType clkBlockType;

#ifdef CO_PARAM_CHECK
	if (onOff > D_IM_PRO_CLOCK_OFF){
		Ddim_Assertion(("I:impro_srotop_control_clock error. onOff value over!! (%d)\n", onOff));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else {
		// DO NOTHING
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	switch( clkType ) {
		case ImproSrotop_E_IM_PRO_SROTOP_CLK_TYPE_SROCLK:
			ioPro.imgPipe[unitNo].sro.srotop.clkstp.bit.pstp1 = ( ( onOff == D_IM_PRO_CLOCK_ON )
					? D_IM_PRO_CLOCK_ON : D_IM_PRO_CLOCK_OFF );
			clkBlockType = ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO;
			break;

		//case E_IM_PRO_SROTOP_CLK_TYPE_SROCLK2:
		default:
			ioPro.imgPipe[unitNo].sro.srotop.clkstp.bit.pstp2 = ( ( onOff == D_IM_PRO_CLOCK_ON )
					? D_IM_PRO_CLOCK_ON : D_IM_PRO_CLOCK_OFF );
			clkBlockType = ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO2;
			break;
	}
	// waiting for 5 cycle
	if( waitSkip == 0 ) {
		im_pro_get_current_clk_hz( unitNo, clkBlockType, &cpuClkHz, &macroClkHz );
		im_pro_common_wait_by_clk_cycle( 5, macroClkHz, cpuClkHz );
#ifndef CO_DEBUG_ON_PC
//			__nop();
#endif
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
SROTOP macro control data setting
@param[in]	unitNo : Unit number.
@param[in]	ctrl : SROTOP macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srotop_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproSrotopCtrl* ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ctrl == NULL){
		Ddim_Assertion(("I:impro_srotop_ctrl error. ctrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.sroisw	= ctrl->inputMode;
	ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.sromd	= ctrl->sroModeSel;
	ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.cagsl	= ctrl->cagTargetSel;
	ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.brpsw0	= ctrl->bayOutPathSel;
	ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.brpsw1	= ctrl->b2bConnectPathSel;
	ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.brpsw2	= ctrl->ltmConnectPathSel;
	ioPro.imgPipe[unitNo].sro.srotop.srotopctl2.bit.org0		= ctrl->firstPixel[0];
	ioPro.imgPipe[unitNo].sro.srotop.srotopctl2.bit.org1		= ctrl->firstPixel[1];
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
WEITGEN macro control data setting
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	weitgenCtrl : WEITGEN macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srotop_weitgen_ctrl( E_IM_PRO_UNIT_NUM unitNo, EimproWeitgenCh ch, TimproSrotopWeitgenCtrl* weitgenCtrl )
{
#ifdef CO_PARAM_CHECK
	if (weitgenCtrl == NULL){
		Ddim_Assertion(("I:impro_srotop_weitgen_ctrl error. weitgenCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrotop_D_IM_PRO_SROTOP_GENV_MIN, ImproSrotop_D_IM_PRO_SROTOP_GENV_MAX,
			weitgenCtrl->vWaitSignalPos, "impro_srotop_weitgen_ctrl : vWaitSignalPos" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrotop_D_IM_PRO_SROTOP_GENH_MIN, ImproSrotop_D_IM_PRO_SROTOP_GENH_MAX,
			weitgenCtrl->hWaitSignalPos, "impro_srotop_weitgen_ctrl : hWaitSignalPos" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	if( ch == ImproSrotop_E_IM_PRO_WEITGEN_CH0 ) {
		ioPro.imgPipe[unitNo].sro.srotop.waitgenv.bit.genv0	= weitgenCtrl->vWaitSignalPos;
		ioPro.imgPipe[unitNo].sro.srotop.waitgenh.bit.genh0	= weitgenCtrl->hWaitSignalPos;
	}
	else  if( ch == ImproSrotop_E_IM_PRO_WEITGEN_CH1 ){
		ioPro.imgPipe[unitNo].sro.srotop.waitgenv.bit.genv1	= weitgenCtrl->vWaitSignalPos;
		ioPro.imgPipe[unitNo].sro.srotop.waitgenh.bit.genh1	= weitgenCtrl->hWaitSignalPos;
	}
	else {
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
setup of enable to WEITGEN macro.
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	enabled : setup of enable to WEITGEN macro.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srotop_weitgen_enable( E_IM_PRO_UNIT_NUM unitNo, EimproWeitgenCh ch, EimproWeitgenEnable enabled )
{
#ifdef CO_PARAM_CHECK
	//not ALL Stopped
	if ( (ImproSrotop_IM_PRO_SRO_GET_STOP_ALL() == FALSE) || (im_pro_common_fig_im_pro_sen_get_stop_all() == FALSE)){
		Ddim_Print(("I:impro_srotop_weitgen_enable. macro not stopped error. \n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	if( ch == ImproSrotop_E_IM_PRO_WEITGEN_CH0 ) {
		ioPro.imgPipe[unitNo].sro.srotop.waitgenen.bit.genen0	= enabled;
	}
	else  if( ch == ImproSrotop_E_IM_PRO_WEITGEN_CH1 ){
		ioPro.imgPipe[unitNo].sro.srotop.waitgenen.bit.genen1	= enabled;
	}
	else {
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSrotop类的一个实例
 *
 */
ImproSrotop* 	impro_srotop_new()
{
	ImproSrotop* self = k_object_new_with_private(IMPRO_TYPE_SROTOP,sizeof(ImproSrotopPrivate));
	ImproSrotopPrivate* priv = IMPRO_SROTOP_GET_PRIVATE(self);
	
	e_warning_o(self," impro_srotop_new \n");
	return self;
}
