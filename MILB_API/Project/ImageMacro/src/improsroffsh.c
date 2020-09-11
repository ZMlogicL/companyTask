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
#include"improsroffsh.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSroffsh, impro_sroffsh);
#define IMPRO_SROFFSH_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSroffshPrivate, IMPRO_TYPE_SROFFSH));


/*宏定义区域*/
/* FFSH0			*/
#define	ImproSroffsh_D_IM_SRO1_STATUS_FFSH0		((0x00000000UL)&(1<< 3))
/* FFSH1			*/
#define	ImproSroffsh_D_IM_SRO1_STATUS_FFSH1		((0x00000000UL)&(1<< 4))
/* FFSH0			*/
#define	ImproSroffsh_D_IM_SRO2_STATUS_FFSH0		((0x10000000UL)&(1<< 3))
/* FFSH1			*/
#define	ImproSroffsh_D_IM_SRO2_STATUS_FFSH1		((0x10000000UL)&(1<< 4))
/* Image Pipe1&2 FFSH0	*/
#define	ImproSroffsh_D_IM_SRO_STATUS_FFSH0_BOTH	( ImproSroffsh_D_IM_SRO1_STATUS_FFSH0\
																									| ImproSroffsh_D_IM_SRO2_STATUS_FFSH0	)
/* Image Pipe1&2 FFSH1	*/
#define	ImproSroffsh_D_IM_SRO_STATUS_FFSH1_BOTH	( ImproSroffsh_D_IM_SRO1_STATUS_FFSH1\
																								| ImproSroffsh_D_IM_SRO2_STATUS_FFSH1	)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSroffshPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
static const TimproRdmaFfshAddr S_G_IM_PRO_FFSH_ADDR[E_IM_PRO_UNIT_NUM_MAX][ImproSroffsh_D_IM_PRO_SRO_FFSH_CH_NUM] = {
	{
		{
			0x2840821C,0x28408230,0x28408234,0x28408238,
			0x2840823C,
		},
		{
			0x2840831C,0x28408330,0x28408334,0x28408338,
			0x2840833C,
		},
	},
	{
		{
			0x2850821C,0x28508230,0x28508234,0x28508238,
			0x2850823C,
		},
		{
			0x2850831C,0x28508330,0x28508334,0x28508338,
			0x2850833C,
		},
	},
	{
		{
			0x2860821C,0x28608230,0x28608234,0x28608238,
			0x2860823C,
		},
		{
			0x2860831C,0x28608330,0x28608334,0x28608338,
			0x2860833C,
		},
	},
};
static const UINT32	S_G_IM_PRO_FFSH_STATUS_TBL[E_IM_PRO_UNIT_NUM_MAX][ImproSroffsh_D_IM_PRO_SRO_FFSH_CH_NUM] = {
	// E_IM_PRO_UNIT_NUM_1
	{
		ImproSroffsh_D_IM_SRO1_STATUS_FFSH0,		ImproSroffsh_D_IM_SRO1_STATUS_FFSH1,
	},
	// E_IM_PRO_UNIT_NUM_2
	{
		ImproSroffsh_D_IM_SRO2_STATUS_FFSH0,		ImproSroffsh_D_IM_SRO2_STATUS_FFSH1,
	},
	// E_IM_PRO_BOTH_UNIT
	{
		ImproSroffsh_D_IM_SRO_STATUS_FFSH0_BOTH,	ImproSroffsh_D_IM_SRO_STATUS_FFSH1_BOTH,
	},
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_sroffsh_constructor(ImproSroffsh *self)
{
	ImproSroffshPrivate *priv = IMPRO_SROFFSH_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_sroffsh_destructor(ImproSroffsh *self)
{
	ImproSroffshPrivate *priv = IMPRO_SROFFSH_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
FFSH start
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@retval		D_DDIM_OK					: Processing OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: PRCH not running NG
*/
INT32 impro_sroffsh_start( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshtrg.bit.ffshtrg = D_IM_PRO_TRG_START;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_START_STATUS(S_G_IM_PRO_FFSH_STATUS_TBL[unitNo][ch], 0);

	return D_DDIM_OK;
}

/**
FFSH stop
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Processing OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: PRCH not stopped NG
*/
INT32 impro_sroffsh_stop( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	if(force == 0) {
		// stop
		ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshtrg.bit.ffshtrg = D_IM_PRO_TRG_FRAME_STOP;
	}
	else {
		// force stop
		ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshtrg.bit.ffshtrg = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_STOP_STATUS(S_G_IM_PRO_FFSH_STATUS_TBL[unitNo][ch], 0);

	return D_DDIM_OK;
}

/**
FFSH control setup
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	ffshCtrl : FFSH control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroffsh_ctrl( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, TimproFfshCtrl* ffshCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ffshCtrl == NULL){
		Ddim_Assertion(("I:impro_sroffsh_ctrl error. ffshCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRH_MIN,
			ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRH_MAX, ffshCtrl->hSizeCorrectionCoeff,
			"impro_sroffsh_ctrl : hSizeCorrectionCoeff" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRV_MIN,
			ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRV_MAX, ffshCtrl->vSizeCorrectionCoeff,
			"impro_sroffsh_ctrl : vSizeCorrectionCoeff" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSPH_MIN,
			ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSPH_MAX, ffshCtrl->hPixelUnitInterpolation,
			"impro_sroffsh_ctrl : hPixelUnitInterpolation" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSPV_MIN,
			ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSPV_MAX, ffshCtrl->vPixelUnitInterpolation,
			"impro_sroffsh_ctrl : vPixelUnitInterpolation" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSTH_MIN,
			ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSTH_MAX, ffshCtrl->hStartPosCoeff,
			"impro_sroffsh_ctrl : hStartPosCoeff" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSTV_MIN,
			ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSTV_MAX, ffshCtrl->vStartPosCoeff,
			"impro_sroffsh_ctrl : vStartPosCoeff" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubpr.bit.ffshsubprh	= ffshCtrl->hSizeCorrectionCoeff;
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubpr.bit.ffshsubprv	= ffshCtrl->vSizeCorrectionCoeff;
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubsp.bit.ffshsubsph	= ffshCtrl->hPixelUnitInterpolation;
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubsp.bit.ffshsubspv	= ffshCtrl->vPixelUnitInterpolation;
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubdr.bit.ffshsubdrm	= ffshCtrl->radInverseCoeffInterpolation;
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubdr.bit.ffshsubdre	= ffshCtrl->expRadInverseCoeffInterpolation;
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubst.bit.ffshsubsth	= ffshCtrl->hStartPosCoeff;
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubst.bit.ffshsubstv	= ffshCtrl->vStartPosCoeff;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
A setup of FFSH blend ratio.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	blendCtrl : FFSH blend control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroffsh_set_blend( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, TimproFfshBlendCtrl* blendCtrl )
{
#ifdef CO_PARAM_CHECK
	if (blendCtrl == NULL){
		Ddim_Assertion(("I:impro_sroffsh_set_blend error. blendCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshbc, union io_ffshbc, ffshbc0, blendCtrl->frameCorrectionBlend0 );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshbc, union io_ffshbc, ffshbc1, blendCtrl->frameCorrectionBlend1 );
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
A setup of FFSH effective area
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	ffshArea : FFSH area information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroffsh_set_area( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, TimproFfshArea* ffshArea )
{
#ifdef CO_PARAM_CHECK
	if (ffshArea == NULL){
		Ddim_Assertion(("I:impro_sroffsh_set_area error. ffshArea=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffsh_D_IM_PRO_FFSH_FFSHH_MIN, ImproSroffsh_D_IM_PRO_FFSH_FFSHH_MAX,
			ffshArea->ffshArea.posX, "impro_sroffsh_set_area : posX" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffsh_D_IM_PRO_FFSH_FFSHV_MIN, ImproSroffsh_D_IM_PRO_FFSH_FFSHV_MAX,
			ffshArea->ffshArea.posY, "impro_sroffsh_set_area : posY" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffsh_D_IM_PRO_FFSH_FFSHHW_MIN, ImproSroffsh_D_IM_PRO_FFSH_FFSHHW_MAX,
			ffshArea->ffshArea.width, "impro_sroffsh_set_area : width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffsh_D_IM_PRO_FFSH_FFSHVW_MIN, ImproSroffsh_D_IM_PRO_FFSH_FFSHVW_MAX,
			ffshArea->ffshArea.lines, "impro_sroffsh_set_area : lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshh.bit.ffshh	= ffshArea->ffshArea.posX;
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshv.bit.ffshv	= ffshArea->ffshArea.posY;
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshhw.bit.ffshhw	= ffshArea->ffshArea.width;
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshvw.bit.ffshvw	= ffshArea->ffshArea.lines;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of FFSH.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroffsh_set_paen( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, UCHAR paenTrg )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshpaen.bit.ffshpaen = paenTrg;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
set the request issue interval when reading the coefficients from PRCH/M2P macro.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	reqIntervalClk : RAM access control<br>
			value range :[4~1023]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroffsh_set_coeff_read_line_wait( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, USHORT reqIntervalClk )
{
#ifdef CO_PARAM_CHECK
	if( im_pro_check_val_range( ImproSroffsh_D_IM_PRO_FFSH_FFSHWRIC_MIN, ImproSroffsh_D_IM_PRO_FFSH_FFSHWRIC_MAX,
			reqIntervalClk, "impro_sroffsh_set_coeff_read_line_wait : reqIntervalClk" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( reqIntervalClk >= ((ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshhw.bit.ffshhw - (4*ioPro.imgPipe[unitNo]
	                                                                                                         .sro.ffsh[ch].ffshsubpr.bit.ffshsubprh))-10)/3 ) {
		Ddim_Assertion(("I:impro_sroffsh_set_coeff_read_line_wait. parameter error. Please satisfy following relationship."
				" (reqIntervalClk  < ((FFSHHW-(4*FFSHSUBPRH)) -10)/3) (%u)\n", reqIntervalClk));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshwric.bit.ffshwric	= reqIntervalClk;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Get the top address of the address array of FFSH control.
@param[in]		unitNo : Unit number.
@param[in]		ch : Channel No
@param[out]		addr					: Top address of the address array of FFSH control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 impro_sroffsh_get_rdma_addr_ffsh_cntl( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, const TimproRdmaFfshAddr** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:impro_sroffsh_get_rdma_addr_ffsh_cntl. error. addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &(S_G_IM_PRO_FFSH_ADDR[unitNo][ch]);

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSroffsh类的一个实例
 *
 */
ImproSroffsh* 	impro_sroffsh_new()
{
	ImproSroffsh* self = k_object_new_with_private(IMPRO_TYPE_SROFFSH,sizeof(ImproSroffshPrivate));
	ImproSroffshPrivate* priv = IMPRO_SROFFSH_GET_PRIVATE(self);
	
	e_warning_o(self," impro_sroffsh_new \n");
	return self;
}
