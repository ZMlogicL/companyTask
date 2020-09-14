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
#include"improsencmipi.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSencmipi, impro_sencmipi);
#define IMPRO_SENCMIPI_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSencmipiPrivate, IMPRO_TYPE_SENCMIPI));


/*宏定义区域*/
// C-MIPI wait time(us) for start-up stabilization.
#define ImproSencmipi_D_IM_PRO_CMIPI_WAIT_PHY_STARTUP	(100)

/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSencmipiPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/


/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_sencmipi_constructor(ImproSencmipi *self)
{
	ImproSencmipiPrivate *priv = IMPRO_SENCMIPI_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_sencmipi_destructor(ImproSencmipi *self)
{
	ImproSencmipiPrivate *priv = IMPRO_SENCMIPI_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
MIPI-CPHY initialize
@param[in]	ch : MIPI-CPHY channel
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sencmipi_init( EimproCmipiCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	// Software release
	ioPro.sen.mipic[ch].mpicsr.bit.sr  = D_IM_PRO_SR_RELEASE;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
Software reset of MIPI-CPHY
@param[in]	ch : MIPI-CPHY channel
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sencmipi_sr( EimproCmipiCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	// Software reset
	ioPro.sen.mipic[ch].mpicsr.bit.sr  = D_IM_PRO_SR_RESET;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
MIPI-CPHY macro start.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Macro Start OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: C-MIPI has not stopped NG
*/
INT32 impro_sencmipi_start( EimproCmipiCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	if( ioPro.sen.mipic[ch].mpictrg.bit.mpictrg == D_IM_PRO_TRG_STATUS_RUNNING ) {
		Ddim_Print(( "impro_sencmipi_start C-MIPI macro is not stopped error.\n" ));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
	ioPro.sen.mipic[ch].mpictrg.bit.mpictrg = D_IM_PRO_TRG_START;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	im_pro_common_fig_im_pro_sen_set_start_status(D_IM_SEN_STATUS_CMIPI0, ch);

	return D_DDIM_OK;
}

/**
MIPI-CPHY macro stop.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Macro Stop OK
@retval		D_IM_PRO_NG					: Macro Stop NG
*/
INT32 impro_sencmipi_stop( EimproCmipiCh ch, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	if (force == 0){
		// frame stop
		ioPro.sen.mipic[ch].mpictrg.bit.mpictrg = D_IM_PRO_TRG_FRAME_STOP;
	}
	else{
		// force stop
		ioPro.sen.mipic[ch].mpictrg.bit.mpictrg = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	im_pro_common_fig_im_pro_sen_set_stop_status(D_IM_SEN_STATUS_CMIPI0, ch);

	return D_DDIM_OK;
}

/**
The control parameter of MIPI-CPHY is set.
@param[in]	ch : Channel No.
@param[in]	cmipiCtrl : MIPI-CPHY control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_sencmipi_ctrl( EimproCmipiCh ch, TimproCmipiCtrl* cmipiCtrl )
{
#ifdef CO_PARAM_CHECK
	if (cmipiCtrl == NULL){
		Ddim_Assertion(("I:impro_sencmipi_ctrl error. cmipiCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	//not Stopped
	if (im_pro_common_fig_im_pro_sen_get_start_status( D_IM_SEN_STATUS_CMIPI0, ch ) == TRUE) {
		Ddim_Print(("I:impro_sencmipi_ctrl. macro not stopped error. \n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.mipic[ch].mpiclmode.bit.lane					= cmipiCtrl->laneSel;
	ioPro.sen.mipic[ch].mpiciomd0.bit.dtmd0				= cmipiCtrl->inputDataMode[0];
	ioPro.sen.mipic[ch].mpiciomd0.bit.outmd0				= cmipiCtrl->outputDataMode[0];
	ioPro.sen.mipic[ch].mpiciomd0.bit.vcout0				= cmipiCtrl->vcModeSel[0];
	ioPro.sen.mipic[ch].mpiciomd0.bit.dtcomd0				= cmipiCtrl->outputDtSel[0];
	ioPro.sen.mipic[ch].mpiciomd0.bit.dtco0				= cmipiCtrl->outputDtSetting[0];
	ioPro.sen.mipic[ch].mpiciomd1.bit.dtmd1				= cmipiCtrl->inputDataMode[1];
	ioPro.sen.mipic[ch].mpiciomd1.bit.outmd1				= cmipiCtrl->outputDataMode[1];
	ioPro.sen.mipic[ch].mpiciomd1.bit.vcout1				= cmipiCtrl->vcModeSel[1];
	ioPro.sen.mipic[ch].mpiciomd1.bit.dtcomd1				= cmipiCtrl->outputDtSel[1];
	ioPro.sen.mipic[ch].mpiciomd1.bit.dtco1				= cmipiCtrl->outputDtSetting[1];
	ioPro.sen.mipic[ch].mpichdpdsel.bit.hdpdsel0			= cmipiCtrl->outCycle[0];
	ioPro.sen.mipic[ch].mpichdpdsel.bit.hdpdsel1			= cmipiCtrl->outCycle[1];
	ioPro.sen.mipic[ch].mpiccpi2.bit.cpHsSettlecnt		= cmipiCtrl->phyCtrl.hsSettlecnt;
	ioPro.sen.mipic[ch].mpiccpi2.bit.cpHsStopcnt			= cmipiCtrl->phyCtrl.hsStopcnt;
	ioPro.sen.mipic[ch].mpiccpi2.bit.cpHsSyncmode		= cmipiCtrl->phyCtrl.hsSyncmode;
	ioPro.sen.mipic[ch].mpicprlrlconf.bit.cpRlrLconfig	= cmipiCtrl->phyCtrl.rlrLconfig;
	ioPro.sen.mipic[ch].mpicprlrltpsel.bit.cpRlrTpsel	= cmipiCtrl->phyCtrl.rlrTpsel;
	ioPro.sen.mipic[ch].mpicprlrprbs.bit.cpRlrPrbssp		= cmipiCtrl->phyCtrl.rlrPrbssp;
	ioPro.sen.mipic[ch].mpicpprogseq.bit.cpTgrProgseq	= cmipiCtrl->phyCtrl.tgrProgseq;
	ioPro.sen.mipic[ch].mpicpfrxmode.bit.cpForcerxmode2	= cmipiCtrl->phyCtrl.forcerxmode2;
	ioPro.sen.mipic[ch].mpicpfrxmode.bit.cpForcerxmode1	= cmipiCtrl->phyCtrl.forcerxmode1;
	ioPro.sen.mipic[ch].mpicpfrxmode.bit.cForcerxmode0	= cmipiCtrl->phyCtrl.forcerxmode0;

	ioPro.sen.mipic[ch].mpiccpi1.bit.cpen					= cmipiCtrl->phyCtrl.rxenable;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	im_pro_wait_usec( ImproSencmipi_D_IM_PRO_CMIPI_WAIT_PHY_STARTUP );


	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of MIPI-CPHY.
@param[in]	ch : Channel No.
@param[in]	paen0Trg : RAM0 access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@param[in]	paen1Trg : RAM1 access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sencmipi_set_pean( EimproCmipiCh ch, UCHAR paen0Trg, UCHAR paen1Trg )
{
#ifdef CO_PARAM_CHECK
	if( ( paen0Trg == 0 ) && ( paen1Trg == 0 )
										&& ( ioPro.sen.mipic[ch].mpictrg.bit.mpictrg
										!= D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:impro_sencmipi_set_pean. macro has not stopped error.\n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.mipic[ch].mpicpaen0.bit.paen0 = paen0Trg;
	ioPro.sen.mipic[ch].mpicpaen1.bit.paen1 = paen1Trg;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}


/**
Get MIPI C-PHY status..
@param[in]	ch : Channel No.
@param[out]	status : MIPI-CPHY status information
*/
INT32 impro_sencmipi_get_status( EimproCmipiCh ch, TimproCmipiStatus* status )
{
#ifdef CO_PARAM_CHECK
	if (status == NULL){
		Ddim_Assertion(("I:impro_sencmipi_get_status error. status=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (status == NULL){
		Ddim_Assertion(("I:impro_sencmipi_get_status error. status=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	status->rxstopstateL0	= ioPro.sen.mipic[ch].mpicpvr.bit.ssl0;
	status->rxstopstateL1	= ioPro.sen.mipic[ch].mpicpvr.bit.ssl1;
	status->rxstopstateL2	= ioPro.sen.mipic[ch].mpicpvr.bit.ssl2;
	status->lstatus0		= ioPro.sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus0;
	status->lstatus1		= ioPro.sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus1;
	status->lstatus2		= ioPro.sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus2;
	status->werrcnt0		= ioPro.sen.mipic[ch].mpicprlrwecnt0.bit.cpRlrWerrcnt0;
	status->werrcnt1		= ioPro.sen.mipic[ch].mpicprlrwecnt1.bit.cpRlrWerrcnt1;
	status->werrcnt2		= ioPro.sen.mipic[ch].mpicprlrwecnt2.bit.cpRlrWerrcnt2;
	status->wcnt0			= ioPro.sen.mipic[ch].mpicprlrwcnt0.bit.cpRlrWcnt0;
	status->wcnt1			= ioPro.sen.mipic[ch].mpicprlrwcnt1.bit.cpRlrWcnt1;
	status->wcnt2			= ioPro.sen.mipic[ch].mpicprlrwcnt2.bit.cpRlrWcnt2;
	status->syerrcnt0		= ioPro.sen.mipic[ch].mpicprlrserrcnt0.bit.cpRlrSyerrcnt0;
	status->syerrcnt1		= ioPro.sen.mipic[ch].mpicprlrserrcnt1.bit.cpRlrSyerrcnt1;
	status->syerrcnt2		= ioPro.sen.mipic[ch].mpicprlrserrcnt2.bit.cpRlrSyerrcnt2;
	status->syerrloc0		= ioPro.sen.mipic[ch].mpicprlrserrloc0.bit.cpRlrSyerrloc0;
	status->syerrloc1		= ioPro.sen.mipic[ch].mpicprlrserrloc1.bit.cpRlrSyerrloc1;
	status->syerrloc2		= ioPro.sen.mipic[ch].mpicprlrserrloc2.bit.cpRlrSyerrloc2;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSencmipi类的一个实例
 *
 */
ImproSencmipi* 	impro_sencmipi_new()
{
	ImproSencmipi* self = k_object_new_with_private(IMPRO_TYPE_SENCMIPI,sizeof(ImproSencmipiPrivate));
	ImproSencmipiPrivate* priv = IMPRO_SENCMIPI_GET_PRIVATE(self);
	
	e_warning_o(self," impro_sencmipi_new \n");
	return self;
}
