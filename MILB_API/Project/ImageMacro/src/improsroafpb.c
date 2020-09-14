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
#include"improsroafpb.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSroafpb, impro_sroafpb);
#define IMPRO_SROAFPB_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSroafpbPrivate, IMPRO_TYPE_SROAFPB));


/*宏定义区域*/
/* AFPB A			*/
#define	ImproSroafpb_D_IM_SRO1_STATUS_AFPB_A		((0x00000000UL)&(1<< 8))
/* AFPB G			*/
#define	ImproSroafpb_D_IM_SRO1_STATUS_AFPB_G		((0x00000000UL)&(1<< 9))
/* AFPB A			*/
#define	ImproSroafpb_D_IM_SRO2_STATUS_AFPB_A		((0x10000000UL)&(1<< 8))
/* AFPB G			*/
#define	ImproSroafpb_D_IM_SRO2_STATUS_AFPB_G		((0x10000000UL)&(1<< 9))
/* Image Pipe1&2 AFPB_A	*/
#define	ImproSroafpb_D_IM_SRO_STATUS_AFPB_A_BOTH	( ImproSroafpb_D_IM_SRO1_STATUS_AFPB_A	\
																									| ImproSroafpb_D_IM_SRO2_STATUS_AFPB_A	)
/* Image Pipe1&2 AFPB_G	*/
#define	ImproSroafpb_D_IM_SRO_STATUS_AFPB_G_BOTH	( ImproSroafpb_D_IM_SRO1_STATUS_AFPB_G	\
																									| ImproSroafpb_D_IM_SRO2_STATUS_AFPB_G	)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSroafpbPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
static const UINT32	gIM_PRO_AFPB_Status_Tbl[ImproBase_E_IM_PRO_UNIT_NUM_MAX][ImproSroafpb_D_IM_PRO_SRO_AFPB_CH_NUM] = {
	// ImproBase_E_IM_PRO_UNIT_NUM_1
	{
		ImproSroafpb_D_IM_SRO1_STATUS_AFPB_A,		ImproSroafpb_D_IM_SRO1_STATUS_AFPB_G,
	},
	// ImproBase_E_IM_PRO_UNIT_NUM_2
	{
		ImproSroafpb_D_IM_SRO2_STATUS_AFPB_A,		ImproSroafpb_D_IM_SRO2_STATUS_AFPB_G,
	},
	// ImproBase_E_IM_PRO_BOTH_UNIT
	{
		ImproSroafpb_D_IM_SRO_STATUS_AFPB_A_BOTH,	ImproSroafpb_D_IM_SRO_STATUS_AFPB_G_BOTH,
	},
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_sroafpb_constructor(ImproSroafpb *self)
{
	ImproSroafpbPrivate *priv = IMPRO_SROAFPB_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_sroafpb_destructor(ImproSroafpb *self)
{
	ImproSroafpbPrivate *priv = IMPRO_SROAFPB_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
Start AFPB
@param[in]	unitNo : Unit number.
*/
VOID impro_sroafpb_start( E_IM_PRO_UNIT_NUM unitNo, EimproAfpbCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.afpb[ch].afpbtrg.bit.afpbtrg = D_IM_PRO_TRG_START;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_START_STATUS(gIM_PRO_AFPB_Status_Tbl[unitNo][ch], 0);
}

/**
Stop AFPB
@param[in]	unitNo : Unit number.
@param[in]	force : force stop option
*/
VOID impro_sroafpb_stop( E_IM_PRO_UNIT_NUM unitNo, EimproAfpbCh ch, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	if(force == 0) {
		// stop
		ioPro.imgPipe[unitNo].sro.afpb[ch].afpbtrg.bit.afpbtrg = D_IM_PRO_TRG_FRAME_STOP;
	}
	else {
		// force stop
		ioPro.imgPipe[unitNo].sro.afpb[ch].afpbtrg.bit.afpbtrg = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_STOP_STATUS(gIM_PRO_AFPB_Status_Tbl[unitNo][ch], 0);
}

/**
Set AFPB control information
@param[in]	unitNo : Unit number.
@param[in]	afpbCtrl	: AFPB control Information.
*/
INT32 impro_sroafpb_ctrl( E_IM_PRO_UNIT_NUM unitNo, EimproAfpbCh ch, TimproAfpbCtrl* afpbCtrl )
{
#ifdef CO_PARAM_CHECK
	if (afpbCtrl == NULL){
		Ddim_Assertion(("I:impro_sroafpb_ctrl error. afpbCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroafpb_D_IM_PRO_AFPB_AFPBH_MIN, ImproSroafpb_D_IM_PRO_AFPB_AFPBH_MAX,
				afpbCtrl->afpbArea.posX, "impro_sroafpb_ctrl : posX" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroafpb_D_IM_PRO_AFPB_AFPBV_MIN, ImproSroafpb_D_IM_PRO_AFPB_AFPBV_MAX,
				afpbCtrl->afpbArea.posY, "impro_sroafpb_ctrl : posY" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroafpb_D_IM_PRO_AFPB_AFPBHW_MIN, ImproSroafpb_D_IM_PRO_AFPB_AFPBHW_MAX,
				afpbCtrl->afpbArea.width, "impro_sroafpb_ctrl : width" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroafpb_D_IM_PRO_AFPB_AFPBVW_MIN, ImproSroafpb_D_IM_PRO_AFPB_AFPBVW_MAX,
				afpbCtrl->afpbArea.lines, "impro_sroafpb_ctrl : lines" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.afpb[ch].afpbh.bit.afpbh	= afpbCtrl->afpbArea.posX;
	ioPro.imgPipe[unitNo].sro.afpb[ch].afpbv.bit.afpbv	= afpbCtrl->afpbArea.posY;
	ioPro.imgPipe[unitNo].sro.afpb[ch].afpbhw.bit.afpbhw	= afpbCtrl->afpbArea.width;
	ioPro.imgPipe[unitNo].sro.afpb[ch].afpbvw.bit.afpbvw	= afpbCtrl->afpbArea.lines;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}



/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSroafpb类的一个实例
 *
 */
ImproSroafpb* 	impro_sroafpb_new()
{
	ImproSroafpb* self = k_object_new_with_private(IMPRO_TYPE_SROAFPB,sizeof(ImproSroafpbPrivate));
	ImproSroafpbPrivate* priv = IMPRO_SROAFPB_GET_PRIVATE(self);
	
	e_warning_o(self," impro_sroafpb_new \n");
	return self;
}
