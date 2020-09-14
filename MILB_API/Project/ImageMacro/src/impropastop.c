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
#include"impropastop.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproPastop, impro_pastop);
#define IMPRO_PASTOP_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproPastopPrivate, IMPRO_TYPE_PASTOP));


/*宏定义区域*/
#define ImproPastop_GET_START_STATUS(st, ch)		(((gIM_PAS_START_Status[((st) >> 28) & 0xf] & (((st) & 0x0fffffff) << (ch))) != 0) ? TRUE : FALSE)		/* started check	*/
#define ImproPastop_GET_STOP_ALL()						((gIM_PAS_START_Status[0] != 0) ? FALSE : TRUE)	/* started check	*/


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproPastopPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/


/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_pastop_constructor(ImproPastop *self)
{
	ImproPastopPrivate *priv = IMPRO_PASTOP_GET_PRIVATE(self);
}

/*内存释放区域*/
static void impro_pastop_destructor(ImproPastop *self)
{
	ImproPastopPrivate *priv = IMPRO_PASTOP_GET_PRIVATE(self);
}



/*IMPL*/


/*PUBLIC*/
/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/* Nothing Special */
/********************************************************/
/*	PAS Top												*/
/********************************************************/
/**
PASTOP Macro initialize
@remarks	Please Call at the time of system starting.
*/
VOID impro_pastop_init( VOID )
{
	// Software release
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	ioPro.pas.pastop.sr.bit.sr = D_IM_PRO_SR_RELEASE;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_PAS );
}

/**
PASTOP Macro software reset
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: All macro not stopped NG
*/
INT32 impro_pastop_sw_reset( VOID )
{
#ifdef CO_ACT_PRO_CLOCK
	//not ALL Stopped
	if (ImproPastop_GET_STOP_ALL() == FALSE){
		Ddim_Print(("I:impro_pastop_sw_reset. macro not stopped error. \n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif	/* CO_ACT_PRO_CLOCK */
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	// Software reset
	ioPro.pas.pastop.sr.bit.sr = D_IM_PRO_SR_RESET;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	return D_DDIM_OK;
}

/**
PASTOP Macro clock control
@param[in]	clkType	: PASTOP Macro clock type
@param[in]	onOff		: 0:clock on 1:clock off
@param[in]	waitSkip	: 0:non wait 1:wait 1ms. for wait PROCLK/CDK 5 cycle.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_pastop_control_clock(EimproPastopClkType clkType, UCHAR onOff, UCHAR waitSkip )
{
	UINT32 cpuClkHz;
	UINT32 macroClkHz;

#ifdef CO_PARAM_CHECK
	if (onOff > D_IM_PRO_CLOCK_OFF){
		Ddim_Assertion(("I:Im_PRO_STATTOP_Control_Clock error. onOff value over!! (%d)\n", onOff));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else {
		// DO NOTHING
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	switch( clkType ) {
		case ImproPastop_E_IM_PRO_PASTOP_CLK_TYPE_PASCLK:
			ioPro.pas.pastop.clkstp.bit.pstp1 = ( ( onOff == D_IM_PRO_CLOCK_ON ) ? D_IM_PRO_CLOCK_ON : D_IM_PRO_CLOCK_OFF );
			break;

		default:
			break;
	}
	// waiting for 5 cycle
	if( waitSkip == 0 ) {
		im_pro_get_current_clk_hz( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_PAS, &cpuClkHz, &macroClkHz );
		im_pro_common_wait_by_clk_cycle( 5, macroClkHz, cpuClkHz );
#ifndef CO_DEBUG_ON_PC
//			__nop();
#endif
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	return D_DDIM_OK;
}

/**
PASTOP macro control data setting
@param[in]	ctrl : PASTOP macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_pastop_ctrl(TimproPastopCtrl* ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ctrl == NULL){
		Ddim_Assertion(("I:impro_pastop_ctrl error. ctrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	ioPro.pas.pastop.pastopctl1.bit.org	= ctrl->org;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	return D_DDIM_OK;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproPastop类的一个实例
 *
 */
ImproPastop* 	impro_pastop_new()
{
	ImproPastop* self = k_object_new_with_private(IMPRO_TYPE_PASTOP,sizeof(ImproPastopPrivate));
	ImproPastopPrivate* priv = IMPRO_PASTOP_GET_PRIVATE(self);
	
	e_warning_o(self," impro_pastop_new \n");
	return self;
}
