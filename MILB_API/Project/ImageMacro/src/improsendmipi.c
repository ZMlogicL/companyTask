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
#include"improsendmipi.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSendmipi, impro_sendmipi);
#define IMPRO_SENDMIPI_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSendmipiPrivate, IMPRO_TYPE_SENDMIPI));


/*宏定义区域*/
// D-MIPI wait time(us) for start-up stabilization.
#define ImproSendmipi_D_IM_PRO_DMIPI_WAIT_PHY_STARTUP	(100)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSendmipiPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/


/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_sendmipi_constructor(ImproSendmipi *self)
{
	ImproSendmipiPrivate *priv = IMPRO_SENDMIPI_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_sendmipi_destructor(ImproSendmipi *self)
{
	ImproSendmipiPrivate *priv = IMPRO_SENDMIPI_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
MIPI-DPHY initialize
@param[in]	ch : MIPI-DPHY channel
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sendmipi_init( EimproDmipiCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	// Software release
	ioPro.sen.mipid[ch].mpisr.bit.sr  = D_IM_PRO_SR_RELEASE;
	// Dd_Top_Start_Clock

	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}

/**
Software reset of MIPI-DPHY
@param[in]	ch : MIPI-DPHY channel
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sendmipi_sr( EimproDmipiCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	// Software reset
	ioPro.sen.mipid[ch].mpisr.bit.sr  = D_IM_PRO_SR_RESET;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	return D_DDIM_OK;
}

/**
MIPI-DPHY macro start.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Macro Start OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: D-MIPI has not stopped NG
*/
INT32 impro_sendmipi_start( EimproDmipiCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	if( ioPro.sen.mipid[ch].mpitrg.bit.mpitrg == D_IM_PRO_TRG_STATUS_RUNNING ) {
		Ddim_Print(( "impro_sendmipi_start D-MIPI macro is not stopped error.\n" ));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
	ioPro.sen.mipid[ch].mpitrg.bit.mpitrg = D_IM_PRO_TRG_START;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	im_pro_common_fig_im_pro_sen_set_start_status(D_IM_SEN_STATUS_DMIPI0, ch);

	return D_DDIM_OK;
}

/**
MIPI-DPHY macro stop.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Macro Stop OK
@retval		D_IM_PRO_NG					: Macro Stop NG
*/
INT32 impro_sendmipi_stop( EimproDmipiCh ch, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	if (force == 0){
		// frame stop
		ioPro.sen.mipid[ch].mpitrg.bit.mpitrg = 2;
	}
	else{
		// force stop
		ioPro.sen.mipid[ch].mpitrg.bit.mpitrg = 0;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	im_pro_common_fig_im_pro_sen_set_stop_status(D_IM_SEN_STATUS_DMIPI0, ch);

	return D_DDIM_OK;
}

/**
The control parameter of MIPI-DPHY is set.
@param[in]	ch : Channel No.
@param[in]	dmipiCtrl : MIPI-DPHY control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_sendmipi_ctrl( EimproDmipiCh ch, TimproDmipiCtrl* dmipiCtrl )
{
#ifdef CO_PARAM_CHECK
	if (dmipiCtrl == NULL){
		Ddim_Assertion(("I:impro_sendmipi_ctrl error. dmipiCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	//not Stopped
	if (im_pro_common_fig_im_pro_sen_get_start_status( D_IM_SEN_STATUS_DMIPI0, ch ) == TRUE) {
		Ddim_Print(("I:impro_sendmipi_ctrl. macro not stopped error. \n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.mipid[ch].MPILMODE.bit.lane			= dmipiCtrl->laneSel;

	ioPro.sen.mipid[ch].mpiiomd0.bit.dtmd0			= dmipiCtrl->inputDataMode[0];
	ioPro.sen.mipid[ch].mpiiomd0.bit.outmd0		= dmipiCtrl->outputDataMode[0];
	ioPro.sen.mipid[ch].mpiiomd0.bit.vcout0		= dmipiCtrl->vcModeSel[0];
	ioPro.sen.mipid[ch].mpiiomd0.bit.dtcomd0		= dmipiCtrl->outputDtSel[0];
	ioPro.sen.mipid[ch].mpiiomd0.bit.dtco0			= dmipiCtrl->outputDtSetting[0];

	ioPro.sen.mipid[ch].mpiiomd1.bit.dtmd1			= dmipiCtrl->inputDataMode[1];
	ioPro.sen.mipid[ch].mpiiomd1.bit.outmd1		= dmipiCtrl->outputDataMode[1];
	ioPro.sen.mipid[ch].mpiiomd1.bit.vcout1		= dmipiCtrl->vcModeSel[1];
	ioPro.sen.mipid[ch].mpiiomd1.bit.dtcomd1		= dmipiCtrl->outputDtSel[1];
	ioPro.sen.mipid[ch].mpiiomd1.bit.dtco1			= dmipiCtrl->outputDtSetting[1];

	ioPro.sen.mipid[ch].mpidpi.bit.dpsmtc			= dmipiCtrl->phyCtrl.rxsmtCVal;
	ioPro.sen.mipid[ch].mpidpi.bit.dpsmtd			= dmipiCtrl->phyCtrl.rxsmtDVal;
	ioPro.sen.mipid[ch].mpidpi.bit.dpsm			= dmipiCtrl->phyCtrl.rxsyncmode;

	ioPro.sen.mipid[ch].mpihdpdsel.bit.hdpdsel0 = dmipiCtrl->outCycle[0];
	ioPro.sen.mipid[ch].mpihdpdsel.bit.hdpdsel1	= dmipiCtrl->outCycle[1];

	// start D-PHY
	ioPro.sen.mipid[ch].mpidpi.bit.dpen			= dmipiCtrl->phyCtrl.rxenable;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	im_pro_wait_usec( ImproSendmipi_D_IM_PRO_DMIPI_WAIT_PHY_STARTUP );

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of MIPI-DPHY.
@param[in]	ch : Channel No.
@param[in]	paen0Trg : RAM0 access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@param[in]	paen1Trg : RAM1 access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sendmipi_set_paen( EimproDmipiCh ch, UCHAR paen0Trg, UCHAR paen1Trg )
{
#ifdef CO_PARAM_CHECK
	if( ( paen0Trg == 0 ) && ( paen1Trg == 0 ) && ( ioPro.sen.mipid[ch].mpitrg.bit.mpitrg
										!= D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:impro_sendmipi_set_paen. macro has not stopped error.\n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.mipid[ch].mpipaen0.bit.paen0 = paen0Trg;
	ioPro.sen.mipid[ch].mpipaen1.bit.paen1 = paen1Trg;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
Get MIPI D-PHY status..
@param[in]	ch : Channel No.
@param[out]	status : MIPI-DPHY status information
@retval		D_DDIM_OK					: Getting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Getting NG
*/
INT32 impro_sendmipi_get_status( EimproDmipiCh ch, TimproDmipiStatus* status )
{
#ifdef CO_PARAM_CHECK
	if (status == NULL){
		Ddim_Assertion(("I:impro_sendmipi_get_status error. status=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	status->inputSignalStatus		= ioPro.sen.mipid[ch].mpidpvr.word;
	status->skewCalibrationStatus	= ioPro.sen.mipid[ch].mpiscs.word;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSendmipi类的一个实例
 *
 */
ImproSendmipi* 	impro_sendmipi_new()
{
	ImproSendmipi* self = k_object_new_with_private(IMPRO_TYPE_SENDMIPI,sizeof(ImproSendmipiPrivate));
	ImproSendmipiPrivate* priv = IMPRO_SENDMIPI_GET_PRIVATE(self);
	
	e_warning_o(self," impro_sendmipi_new \n");
	return self;
}
