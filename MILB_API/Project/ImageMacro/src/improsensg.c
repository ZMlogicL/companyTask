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
#include"improsensg.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSensg, impro_sensg);
#define IMPRO_SENSG_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSensgPrivate, IMPRO_TYPE_SENSG));


/*宏定义区域*/
/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// SG Trigger Force STOP
#define ImproSensg_D_IM_PRO_SG_TRG_FORCE_STOP		(0)
// SG Trigger Frame STOP
#define ImproSensg_D_IM_PRO_SG_TRG_FRAME_STOP		(2)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSensgPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/


/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_sensg_constructor(ImproSensg *self)
{
	ImproSensgPrivate *priv = IMPRO_SENSG_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_sensg_destructor(ImproSensg *self)
{
	ImproSensgPrivate *priv = IMPRO_SENSG_GET_PRIVATE(self);
}



/*IMPL*/

/*PUBLIC*/
/**
The SG operation(Trigger) started.
@param[in]	ch : SG ch number
*/
INT32 impro_sensg_start( EimproSgCh ch )
{
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );	// Dd_Top_Start_Clock
	switch( ch ) {
		case ImproSensg_E_IM_PRO_SG_CH_0:
			if ( ioPro.sen.sentop.clkstp.clkstp1.bit.pstp2 != 0 ) {
				impro_sentop_control_clock( ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK0 , 0, 1 );
			}
			break;

		case ImproSensg_E_IM_PRO_SG_CH_1:
			if ( ioPro.sen.sentop.clkstp.clkstp1.bit.pstp3 != 0 ) {
				impro_sentop_control_clock( ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK1 , 0, 1 );
			}
			break;

		case ImproSensg_E_IM_PRO_SG_CH_2:
			if ( ioPro.sen.sentop.clkstp.clkstp1.bit.pstp4 != 0 ) {
				impro_sentop_control_clock( ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK2 , 0, 1 );
			}
			break;

		case ImproSensg_E_IM_PRO_SG_CH_3:
			if ( ioPro.sen.sentop.clkstp.clkstp2.bit.pstp5 != 0 ) {
				impro_sentop_control_clock( ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK3 , 0, 1 );
			}
			break;

		default:
			// invalid ch value
			Ddim_Assertion(("I:impro_sensg_start ch value error!! (%d)\n", ch));
			return D_IM_PRO_INPUT_PARAM_ERROR;
	}

	// start
	ioPro.sen.sg[ch].sgtrg.bit.sgtrg = D_IM_PRO_TRG_START;

	im_pro_sen_set_start_status(D_IM_SEN_STATUS_SG0, ch);
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
The SG operation(Trigger) stopped(Frame).
@param[in]	ch : SG ch number
@param[in]	force : force stop option
*/
INT32 impro_sensg_stop( EimproSgCh ch, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	if (force == 0){
		// stop
		ioPro.sen.sg[ch].sgtrg.bit.sgtrg = ImproSensg_D_IM_PRO_SG_TRG_FRAME_STOP;
	}
	else{
		// force stop
		ioPro.sen.sg[ch].sgtrg.bit.sgtrg = ImproSensg_D_IM_PRO_SG_TRG_FORCE_STOP;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	im_pro_sen_set_stop_status(D_IM_SEN_STATUS_SG0, ch);
	return D_DDIM_OK;
}

/**
The SG operation condition is set.
@param[in]	ch : SG ch number
@param[in]	sgCtrl : SG Control info
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sensg_ctrl( EimproSgCh ch, TimproSgCtrl* sgCtrl )
{
#ifdef CO_PARAM_CHECK
	if (sgCtrl == NULL){
		Ddim_Assertion(("I:impro_sensg_ctrl error. ch=%u sgCtrl=NULL\n", ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( sgCtrl->vdocyc < ImproSensg_D_IM_PRO_SG_VDOCYC_MIN ) {
		Ddim_Assertion(("I:impro_sensg_ctrl. vdocyc value error!! ch=%u (%lu)\n", ch, sgCtrl->vdocyc));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( sgCtrl->hdocyc > ImproSensg_D_IM_PRO_SG_HDOCYC_MAX ) {
		Ddim_Assertion(("I:impro_sensg_ctrl. hdocyc value error!! ch=%u (%u)\n", ch, sgCtrl->hdocyc));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( sgCtrl->hdocyc2 > ImproSensg_D_IM_PRO_SG_HDOCYC_MAX ) {
		Ddim_Assertion(("I:impro_sensg_ctrl. hdocyc2 value error!! ch=%u (%u)\n", ch, sgCtrl->hdocyc2));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( sgCtrl->hdow > ImproSensg_D_IM_PRO_SG_HDOW_MAX ) {
		Ddim_Assertion(("I:impro_sensg_ctrl. hdow value error!! ch=%u (%u)\n", ch, sgCtrl->hdow));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( sgCtrl->hdow2 > ImproSensg_D_IM_PRO_SG_HDOW_MAX ) {
		Ddim_Assertion(("I:impro_sensg_ctrl. hdow2 value error!! ch=%u (%u)\n", ch, sgCtrl->hdow2));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( sgCtrl->vdow > ImproSensg_D_IM_PRO_SG_VDOW_MAX ) {
		Ddim_Assertion(("I:impro_sensg_ctrl. vdow value error!! ch=%u (%u)\n", ch, sgCtrl->vdow));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( sgCtrl->vdow >= ( sgCtrl->vdocyc - 1 ) ) {
		Ddim_Assertion(("I:impro_sensg_ctrl. vdow value error!! ch=%u (%u)\n", ch, sgCtrl->vdow));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( sgCtrl->hdow >= sgCtrl->hdocyc ) {
		Ddim_Assertion(("I:impro_sensg_ctrl. hdow value error!! Please set as [hdow < hdocyc]."
									"ch=%u (hdow(%u),hdocyc(%u)\n", ch, sgCtrl->hdow, sgCtrl->hdocyc));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( sgCtrl->hdow2 >= sgCtrl->hdocyc2 ) {
		Ddim_Assertion(("I:impro_sensg_ctrl. hdow2 value error!! Please set as [hdow2 < hdocyc2]."
									" ch=%u (hdow2(%u),hdocyc2(%u)\n", ch, sgCtrl->hdow2, sgCtrl->hdocyc2));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( sgCtrl->vddly > ImproSensg_D_IM_PRO_SG_VDDLY_MAX ) {
		Ddim_Assertion(("I:impro_sensg_ctrl. vddly value error!! ch=%u (%u)\n", ch, sgCtrl->vddly));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.sg[ch].sgctl1.bit.vhdo		= sgCtrl->vhdo;
	ioPro.sen.sg[ch].sgctl1.bit.vdot		= sgCtrl->vdot;
	ioPro.sen.sg[ch].sgctl1.bit.vdinv		= sgCtrl->vdinv;
	ioPro.sen.sg[ch].sgctl1.bit.hdinv		= sgCtrl->hdinv;
	ioPro.sen.sg[ch].sgctl2.bit.hdchg		= sgCtrl->hdchg;
	ioPro.sen.sg[ch].sgctl2.bit.vddly		= sgCtrl->vddly;
	ioPro.sen.sg[ch].vdocyc.bit.vdocyc		= sgCtrl->vdocyc;
	ioPro.sen.sg[ch].vdow.bit.vdow			= sgCtrl->vdow;
	ioPro.sen.sg[ch].hdocyc.bit.hdocyc		= sgCtrl->hdocyc;
	ioPro.sen.sg[ch].hdow.bit.hdow			= sgCtrl->hdow;
	ioPro.sen.sg[ch].hdocyc2.bit.hdocyc2	= sgCtrl->hdocyc2;
	ioPro.sen.sg[ch].hdow2.bit.hdow2		= sgCtrl->hdow2;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
The SG operation condition is get.
@param[in]	ch : SG ch number
@param[out]	sgCtrl : SG Control info
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sensg_get_cycle( EimproSgCh ch, TimproSgCtrl* sgCtrl )
{
#ifdef CO_PARAM_CHECK
	if (sgCtrl == NULL){
		Ddim_Assertion(("I:impro_sensg_get_cycle error. ch=%d sgCtrl=NULL\n", ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	sgCtrl->vhdo = 	ioPro.sen.sg[ch].sgctl1.bit.vhdo;
	sgCtrl->vdot = 	ioPro.sen.sg[ch].sgctl1.bit.vdot;
	sgCtrl->vdinv = 	ioPro.sen.sg[ch].sgctl1.bit.vdinv;
	sgCtrl->hdinv = 	ioPro.sen.sg[ch].sgctl1.bit.hdinv;
	sgCtrl->hdchg = 	ioPro.sen.sg[ch].sgctl2.bit.hdchg;
	sgCtrl->vddly = 	ioPro.sen.sg[ch].sgctl2.bit.vddly;
	sgCtrl->vdocyc = 	ioPro.sen.sg[ch].vdocyc.bit.vdocyc;
	sgCtrl->vdow = 	ioPro.sen.sg[ch].vdow.bit.vdow;
	sgCtrl->hdocyc = 	ioPro.sen.sg[ch].hdocyc.bit.hdocyc;
	sgCtrl->hdow = 	ioPro.sen.sg[ch].hdow.bit.hdow;
	sgCtrl->hdocyc2 = 	ioPro.sen.sg[ch].hdocyc2.bit.hdocyc2;
	sgCtrl->hdow2 = 	ioPro.sen.sg[ch].hdow2.bit.hdow2;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
Get monitoring result of the input VD and HD signals.
@param[in]	ch : SG ch number
@param[out]	sgMoniInfo : SG monitor information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sensg_get_monitor_info( EimproSgCh ch, TimproSgMoniInfo* sgMoniInfo )
{
#ifdef CO_PARAM_CHECK
	if (sgMoniInfo == NULL){
		Ddim_Assertion(("I:impro_sensg_get_monitor_info error. ch=%d sgMoniInfo=NULL\n", ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	sgMoniInfo->inputVdSignal	= ioPro.sen.sg[ch].vdhdmon.bit.vdin;
	sgMoniInfo->inputHdSignal	= ioPro.sen.sg[ch].vdhdmon.bit.hdin;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSensg类的一个实例
 *
 */
ImproSensg* 	impro_sensg_new()
{
	ImproSensg* self = k_object_new_with_private(IMPRO_TYPE_SENSG,sizeof(ImproSensgPrivate));
	ImproSensgPrivate* priv = IMPRO_SENSG_GET_PRIVATE(self);
	
	e_warning_o(self," impro_sensg_new \n");
	return self;
}
