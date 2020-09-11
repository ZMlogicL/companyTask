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
#include"improsroffc.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSroffc, impro_sroffc);
#define IMPRO_SROFFC_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSroffcPrivate, IMPRO_TYPE_SROFFC));


/*宏定义区域*/
/* FFC				*/
#define	ImproSroffc_D_IM_SRO1_STATUS_FFC		((0x00000000UL)&(1<<12))
/* FFC				*/
#define	ImproSroffc_D_IM_SRO2_STATUS_FFC		((0x10000000UL)&(1<<12))
/* Image Pipe1&2 FFC	*/
#define	ImproSroffc_D_IM_SRO_STATUS_FFC_BOTH	( ImproSroffc_D_IM_SRO1_STATUS_FFC | ImproSroffc_D_IM_SRO2_STATUS_FFC	)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSroffcPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
static const TimproRdmaFfcAddr S_G_IM_PRO_FFC_Addr[E_IM_PRO_UNIT_NUM_MAX] = {
	{
		0x2840971C,0x28409734,0x28409738,0x2840973C,
		0x28409740,
	},
	{
		0x2850971C,0x28509734,0x28509738,0x2850973C,
		0x28509740,
	},
	{
		0x2860971C,0x28609734,0x28609738,0x2860973C,
		0x28609740,
	},
};

static const UINT32	gIM_PRO_FFC_Status_Tbl[E_IM_PRO_UNIT_NUM_MAX] = {
	ImproSroffc_D_IM_SRO1_STATUS_FFC,	ImproSroffc_D_IM_SRO2_STATUS_FFC,	ImproSroffc_D_IM_SRO_STATUS_FFC_BOTH,
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_sroffc_constructor(ImproSroffc *self)
{
	ImproSroffcPrivate *priv = IMPRO_SROFFC_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_sroffc_destructor(ImproSroffc *self)
{
	ImproSroffcPrivate *priv = IMPRO_SROFFC_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
Start FFC
@param[in]	unitNo : Unit number.
@retval		D_DDIM_OK					: Processing OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: PRCH/M2P not running NG
*/
INT32 impro_sroffc_start( E_IM_PRO_UNIT_NUM unitNo )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ffc.fctrg.bit.fctrg = D_IM_PRO_TRG_START;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_START_STATUS(gIM_PRO_FFC_Status_Tbl[unitNo], 0);

	return D_DDIM_OK;
}

/**
Stop FFC
@param[in]	unitNo : Unit number.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Processing OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: PRCH/M2P not stopped NG
*/
INT32 impro_sroffc_stop( E_IM_PRO_UNIT_NUM unitNo, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	if(force == 0) {
		// stop
		ioPro.imgPipe[unitNo].sro.ffc.fctrg.bit.fctrg = D_IM_PRO_TRG_FRAME_STOP;
	}
	else {
		// force stop
		ioPro.imgPipe[unitNo].sro.ffc.fctrg.bit.fctrg = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_STOP_STATUS(gIM_PRO_FFC_Status_Tbl[unitNo], 0);

	return D_DDIM_OK;
}

/**
Set FFC control information
@param[in]	unitNo : Unit number.
@param[in]	ffcCtrl	: FFC control Information.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroffc_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproFfcCtrl* ffcCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ffcCtrl == NULL){
		Ddim_Assertion(("I:impro_sroffc_ctrl error. ffcCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffc_D_IM_PRO_FFC_FCSUBPRH_MIN, ImproSroffc_D_IM_PRO_FFC_FCSUBPRH_MAX,
			ffcCtrl->coefHorizontalSize, "impro_sroffc_ctrl : coefHorizontalSize" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffc_D_IM_PRO_FFC_FCSUBPRV_MIN, ImproSroffc_D_IM_PRO_FFC_FCSUBPRV_MAX,
			ffcCtrl->coefVorizontalSize, "impro_sroffc_ctrl : coefVorizontalSize" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffc_D_IM_PRO_FFC_FCSUBSPH_MIN, ImproSroffc_D_IM_PRO_FFC_FCSUBSPH_MAX,
			ffcCtrl->horizontalPixel, "impro_sroffc_ctrl : horizontalPixel" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffc_D_IM_PRO_FFC_FCSUBSPV_MIN, ImproSroffc_D_IM_PRO_FFC_FCSUBSPV_MAX,
			ffcCtrl->verticalPixel, "impro_sroffc_ctrl : verticalPixel" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffc_D_IM_PRO_FFC_FCSUBSTH_MIN, ImproSroffc_D_IM_PRO_FFC_FCSUBSTH_MAX,
			ffcCtrl->coefPosX, "impro_sroffc_ctrl : coefPosX" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffc_D_IM_PRO_FFC_FCSUBSTV_MIN, ImproSroffc_D_IM_PRO_FFC_FCSUBSTV_MAX,
			ffcCtrl->coefPosY, "impro_sroffc_ctrl : coefPosY" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ffc.fcsubpr.bit.fcsubprh	= ffcCtrl->coefHorizontalSize;
	ioPro.imgPipe[unitNo].sro.ffc.fcsubpr.bit.fcsubprv	= ffcCtrl->coefVorizontalSize;
	ioPro.imgPipe[unitNo].sro.ffc.fcsubsp.bit.fcsubsph	= ffcCtrl->horizontalPixel;
	ioPro.imgPipe[unitNo].sro.ffc.fcsubsp.bit.fcsubspv	= ffcCtrl->verticalPixel;
	ioPro.imgPipe[unitNo].sro.ffc.fcsubdr.bit.fcsubdrm	= ffcCtrl->inverseBase;
	ioPro.imgPipe[unitNo].sro.ffc.fcsubdr.bit.fcsubdre	= ffcCtrl->inverseExponent;
	ioPro.imgPipe[unitNo].sro.ffc.fcsubst.bit.fcsubsth	= ffcCtrl->coefPosX;
	ioPro.imgPipe[unitNo].sro.ffc.fcsubst.bit.fcsubstv	= ffcCtrl->coefPosY;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Set FFC blend control information
@param[in]	unitNo : Unit number.
@param[in]	blendCtrl	: FFC blend control Information.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroffc_set_blend( E_IM_PRO_UNIT_NUM unitNo, TimproFfcBlendCtrl* blendCtrl )
{
#ifdef CO_PARAM_CHECK
	if (blendCtrl == NULL){
		Ddim_Assertion(("I:impro_sroffc_set_blend error. blendCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.ffc.fcbc, union io_ffc_fcbc, fcbc0, blendCtrl->blendRatio0 );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.ffc.fcbc, union io_ffc_fcbc, fcbc1, blendCtrl->blendRatio1 );
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of FFC.
@param[in]	unitNo : Unit number.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroffc_set_paen( E_IM_PRO_UNIT_NUM unitNo, UCHAR paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( ioPro.imgPipe[unitNo].sro.ffc.fctrg.bit.fctrg != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:impro_sroffc_set_paen. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ffc.fcpaen.bit.fcpaen = paenTrg;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Set FFC area
@param[in]	unitNo : Unit number.
@param[in]	ffcArea	: FFC area.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroffc_set_area( E_IM_PRO_UNIT_NUM unitNo, TimproFfcArea* ffcArea )
{
#ifdef CO_PARAM_CHECK
	if (ffcArea == NULL){
		Ddim_Assertion(("I:impro_sroffc_set_area error. ffcArea=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffc_D_IM_PRO_FFC_FCH_MIN, ImproSroffc_D_IM_PRO_FFC_FCH_MAX,
			ffcArea->posX, "impro_sroffc_set_area : posX" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffc_D_IM_PRO_FFC_FCV_MIN, ImproSroffc_D_IM_PRO_FFC_FCV_MAX,
			ffcArea->posY, "impro_sroffc_set_area : posY" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffc_D_IM_PRO_FFC_FCHW_MIN, ImproSroffc_D_IM_PRO_FFC_FCHW_MAX,
			ffcArea->width, "impro_sroffc_set_area : width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroffc_D_IM_PRO_FFC_FCVW_MIN, ImproSroffc_D_IM_PRO_FFC_FCVW_MAX,
			ffcArea->lines, "impro_sroffc_set_area : lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ffc.fch.bit.fch	= ffcArea->posX;
	ioPro.imgPipe[unitNo].sro.ffc.fcv.bit.fcv	= ffcArea->posY;
	ioPro.imgPipe[unitNo].sro.ffc.fchw.bit.fchw	= ffcArea->width;
	ioPro.imgPipe[unitNo].sro.ffc.fcvw.bit.fcvw	= ffcArea->lines;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
set the request issue interval when reading the coefficients from PRCH/M2P macro.
@param[in]	unitNo : Unit number.
@param[in]	reqIntervalClk : RAM access control<br>
			value range :[4~1023]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroffc_set_coeff_read_line_wait( E_IM_PRO_UNIT_NUM unitNo, USHORT reqIntervalClk )
{
#ifdef CO_PARAM_CHECK
	if( im_pro_check_val_range( ImproSroffc_D_IM_PRO_FFC_FCWRIC_MIN, ImproSroffc_D_IM_PRO_FFC_FCWRIC_MAX,
			reqIntervalClk, "impro_sroffc_set_coeff_read_line_wait : reqIntervalClk" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( reqIntervalClk >= ((ioPro.imgPipe[unitNo].sro.ffc.fchw.bit.fchw - (4*ioPro.imgPipe[unitNo].
			sro.ffc.fcsubpr.bit.fcsubprh))-10)/3 ) {
		Ddim_Assertion(("I:impro_sroffc_set_coeff_read_line_wait. parameter error. Please satisfy following relationship."
				" (reqIntervalClk  < ((FCHW-(4*FCSUBPRH)) -10)/3) (%u)\n", reqIntervalClk));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ffc.fcwric.bit.fcwric	= reqIntervalClk;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Get the top address of the address array of FFC control.
@param[in]		unitNo : Unit number.
@param[out]		addr					: Top address of the address array of FFC control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 impro_sroffc_get_rdma_addr_ffc_cntl( E_IM_PRO_UNIT_NUM unitNo, const TimproRdmaFfcAddr** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:impro_sroffc_get_rdma_addr_ffc_cntl. error. addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &(S_G_IM_PRO_FFC_Addr[unitNo]);

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSroffc类的一个实例
 *
 */
ImproSroffc* 	impro_sroffc_new()
{
	ImproSroffc* self = k_object_new_with_private(IMPRO_TYPE_SROFFC,sizeof(ImproSroffcPrivate));
	ImproSroffcPrivate* priv = IMPRO_SROFFC_GET_PRIVATE(self);
	
	e_warning_o(self," impro_sroffc_new \n");
	return self;
}
