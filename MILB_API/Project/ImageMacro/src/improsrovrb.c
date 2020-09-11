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
#include"improsrovrb.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSrovrb, impro_srovrb);
#define IMPRO_SROVRB_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSrovrbPrivate, IMPRO_TYPE_SROVRB));


/*宏定义区域*/
/* VRB				*/
#define	ImproSrovrb_D_IM_SRO1_STATUS_VRB		((0x00000000UL)&(1<<14))
/* VRB				*/
#define	ImproSrovrb_D_IM_SRO2_STATUS_VRB		((0x10000000UL)&(1<<14))
/* Image Pipe1&2 VRB	*/
#define	ImproSrovrb_D_IM_SRO_STATUS_VRB_BOTH	( ImproSrovrb_D_IM_SRO1_STATUS_VRB\
																								| ImproSrovrb_D_IM_SRO2_STATUS_VRB	)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSrovrbPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
static const UINT32	S_G_IM_PRO_VRB_STATUS_TBL[E_IM_PRO_UNIT_NUM_MAX] = {
	ImproSrovrb_D_IM_SRO1_STATUS_VRB,	ImproSrovrb_D_IM_SRO2_STATUS_VRB,	ImproSrovrb_D_IM_SRO_STATUS_VRB_BOTH,
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_srovrb_constructor(ImproSrovrb *self)
{
	ImproSrovrbPrivate *priv = IMPRO_SROVRB_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_srovrb_destructor(ImproSrovrb *self)
{
	ImproSrovrbPrivate *priv = IMPRO_SROVRB_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
Start VRB
@param[in]	unitNo : Unit number.
*/
VOID impro_srovrb_start( E_IM_PRO_UNIT_NUM unitNo )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.vrb.vrbtrg.bit.vrbtrg = D_IM_PRO_TRG_START;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_START_STATUS(S_G_IM_PRO_VRB_STATUS_TBL[unitNo], 0);
}

/**
Stop VRB
@param[in]	unitNo : Unit number.
@param[in]	force : force stop option
*/
VOID impro_srovrb_stop( E_IM_PRO_UNIT_NUM unitNo, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	if(force == 0) {
		// stop
		ioPro.imgPipe[unitNo].sro.vrb.vrbtrg.bit.vrbtrg = D_IM_PRO_TRG_FRAME_STOP;
	}
	else {
		// force stop
		ioPro.imgPipe[unitNo].sro.vrb.vrbtrg.bit.vrbtrg = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_STOP_STATUS(S_G_IM_PRO_VRB_STATUS_TBL[unitNo], 0);
}

/**
VRB control data setting
@param[in]	unitNo : Unit number.
@param[in]	vrb_ctrl : VRB control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srovrb_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproVrbCtrl* vrb_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (vrb_ctrl == NULL){
		Ddim_Assertion(("I:impro_srovrb_ctrl error. vrb_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrovrb_D_IM_PRO_VRB_VRBH_MIN, ImproSrovrb_D_IM_PRO_VRB_VRBH_MAX,
			vrb_ctrl->inPosX, "impro_srovrb_ctrl : inPosX" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrovrb_D_IM_PRO_VRB_VRBV_MIN, ImproSrovrb_D_IM_PRO_VRB_VRBV_MAX,
			vrb_ctrl->inPosY, "impro_srovrb_ctrl : inPosY" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrovrb_D_IM_PRO_VRB_VRBHW_MIN, ImproSrovrb_D_IM_PRO_VRB_VRBHW_MAX,
			vrb_ctrl->inWidth, "impro_srovrb_ctrl : inWidth" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrovrb_D_IM_PRO_VRB_VRBVW_MIN, ImproSrovrb_D_IM_PRO_VRB_VRBVW_MAX,
			vrb_ctrl->inLines, "impro_srovrb_ctrl : inLines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrovrb_D_IM_PRO_VRB_VRBSCYC_MIN, ImproSrovrb_D_IM_PRO_VRB_VRBSCYC_MAX,
			vrb_ctrl->cycle, "impro_srovrb_ctrl : cycle" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.vrb.vrbh.bit.vrbh				= vrb_ctrl->inPosX;
	ioPro.imgPipe[unitNo].sro.vrb.vrbv.bit.vrbv				= vrb_ctrl->inPosY;
	ioPro.imgPipe[unitNo].sro.vrb.vrbhw.bit.vrbhw			= vrb_ctrl->inWidth;
	ioPro.imgPipe[unitNo].sro.vrb.vrbvw.bit.vrbvw			= vrb_ctrl->inLines;
	ioPro.imgPipe[unitNo].sro.vrb.vrbscyc.bit.vrbscyc		= vrb_ctrl->cycle;

	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k1.bit.vrb0k00		= vrb_ctrl->coefficient0[0][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k1.bit.vrb0k01		= vrb_ctrl->coefficient0[0][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k2.bit.vrb0k02		= vrb_ctrl->coefficient0[0][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k2.bit.vrb0k10		= vrb_ctrl->coefficient0[1][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k3.bit.vrb0k11		= vrb_ctrl->coefficient0[1][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k3.bit.vrb0k12		= vrb_ctrl->coefficient0[1][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k4.bit.vrb0k20		= vrb_ctrl->coefficient0[2][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k4.bit.vrb0k21		= vrb_ctrl->coefficient0[2][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k5.bit.vrb0k22		= vrb_ctrl->coefficient0[2][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k5.bit.vrb0k30		= vrb_ctrl->coefficient0[3][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k6.bit.vrb0k31		= vrb_ctrl->coefficient0[3][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k6.bit.vrb0k32		= vrb_ctrl->coefficient0[3][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k7.bit.vrb0k40		= vrb_ctrl->coefficient0[4][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k7.bit.vrb0k41		= vrb_ctrl->coefficient0[4][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k8.bit.vrb0k42		= vrb_ctrl->coefficient0[4][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k8.bit.vrb0k50		= vrb_ctrl->coefficient0[5][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k9.bit.vrb0k51		= vrb_ctrl->coefficient0[5][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k9.bit.vrb0k52		= vrb_ctrl->coefficient0[5][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k10.bit.vrb0k60	= vrb_ctrl->coefficient0[6][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k10.bit.vrb0k61	= vrb_ctrl->coefficient0[6][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k11.bit.vrb0k62	= vrb_ctrl->coefficient0[6][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k11.bit.vrb0k70	= vrb_ctrl->coefficient0[7][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k12.bit.vrb0k71	= vrb_ctrl->coefficient0[7][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k12.bit.vrb0k72	= vrb_ctrl->coefficient0[7][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k13.bit.vrb0k80	= vrb_ctrl->coefficient0[8][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k13.bit.vrb0k81	= vrb_ctrl->coefficient0[8][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k14.bit.vrb0k82	= vrb_ctrl->coefficient0[8][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k14.bit.vrb0k90	= vrb_ctrl->coefficient0[9][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k15.bit.vrb0k91	= vrb_ctrl->coefficient0[9][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k15.bit.vrb0k92	= vrb_ctrl->coefficient0[9][2];

	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k1.bit.vrb1k00		= vrb_ctrl->coefficient1[0][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k1.bit.vrb1k01		= vrb_ctrl->coefficient1[0][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k2.bit.vrb1k02		= vrb_ctrl->coefficient1[0][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k2.bit.vrb1k10		= vrb_ctrl->coefficient1[1][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k3.bit.vrb1k11		= vrb_ctrl->coefficient1[1][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k3.bit.vrb1k12		= vrb_ctrl->coefficient1[1][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k4.bit.vrb1k20		= vrb_ctrl->coefficient1[2][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k4.bit.vrb1k21		= vrb_ctrl->coefficient1[2][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k5.bit.vrb1k22		= vrb_ctrl->coefficient1[2][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k5.bit.vrb1k30		= vrb_ctrl->coefficient1[3][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k6.bit.vrb1k31		= vrb_ctrl->coefficient1[3][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k6.bit.vrb1k32		= vrb_ctrl->coefficient1[3][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k7.bit.vrb1k40		= vrb_ctrl->coefficient1[4][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k7.bit.vrb1k41		= vrb_ctrl->coefficient1[4][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k8.bit.vrb1k42		= vrb_ctrl->coefficient1[4][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k8.bit.vrb1k50		= vrb_ctrl->coefficient1[5][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k9.bit.vrb1k51		= vrb_ctrl->coefficient1[5][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k9.bit.vrb1k52		= vrb_ctrl->coefficient1[5][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k10.bit.vrb1k60	= vrb_ctrl->coefficient1[6][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k10.bit.vrb1k61	= vrb_ctrl->coefficient1[6][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k11.bit.vrb1k62	= vrb_ctrl->coefficient1[6][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k11.bit.vrb1k70	= vrb_ctrl->coefficient1[7][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k12.bit.vrb1k71	= vrb_ctrl->coefficient1[7][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k12.bit.vrb1k72	= vrb_ctrl->coefficient1[7][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k13.bit.vrb1k80	= vrb_ctrl->coefficient1[8][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k13.bit.vrb1k81	= vrb_ctrl->coefficient1[8][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k14.bit.vrb1k82	= vrb_ctrl->coefficient1[8][2];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k14.bit.vrb1k90	= vrb_ctrl->coefficient1[9][0];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k15.bit.vrb1k91	= vrb_ctrl->coefficient1[9][1];
	ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k15.bit.vrb1k92	= vrb_ctrl->coefficient1[9][2];
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of vrb.
@param[in]	unitNo : Unit number.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srovrb_set_paen( E_IM_PRO_UNIT_NUM unitNo, UCHAR paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( ioPro.imgPipe[unitNo].sro.vrb.vrbtrg.bit.vrbtrg != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:impro_srovrb_set_paen. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.vrb.vrbpaen.bit.paen = paenTrg;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSrovrb类的一个实例
 *
 */
ImproSrovrb* 	impro_srovrb_new()
{
	ImproSrovrb* self = k_object_new_with_private(IMPRO_TYPE_SROVRB,sizeof(ImproSrovrbPrivate));
	ImproSrovrbPrivate* priv = IMPRO_SROVRB_GET_PRIVATE(self);
	
	e_warning_o(self," impro_srovrb_new \n");
	return self;
}
