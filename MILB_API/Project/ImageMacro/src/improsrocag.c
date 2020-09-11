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
#include"improsrocag.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSrocag, impro_srocag);
#define IMPRO_SROCAG_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSrocagPrivate, IMPRO_TYPE_SROCAG));


/*宏定义区域*/
/* CAG				*/
#define	ImproSrocag_D_IM_SRO1_STATUS_CAG		((0x00000000UL)&(1<<13))
/* CAG				*/
#define	ImproSrocag_D_IM_SRO2_STATUS_CAG		((0x10000000UL)&(1<<13))
/* Image Pipe1&2 CAG	*/
#define	ImproSrocag_D_IM_SRO_STATUS_CAG_BOTH	( ImproSrocag_D_IM_SRO1_STATUS_CAG	| ImproSrocag_D_IM_SRO2_STATUS_CAG)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSrocagPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
static const TimproRdmaCagAddr gIM_PRO_CAG_Addr[E_IM_PRO_UNIT_NUM_MAX] = {
	{
		0x28409818,0x2840981C,0x28409820,0x28409824,
		0x28409828,0x2840982C,0x28409830,0x28409834,
		0x28409838,0x2840983C,0x28409840,0x28409844,
		0x28409848,0x2840984C,0x28409850,0x28409854,
		0x28409858,0x2840985C,0x28409860,0x28409864,
		0x28409868,0x2840986C,0x28409870,0x28409874,
		0x28409878,0x2840987C,0x28409880,0x28409884,
		0x28409888,0x2840988C,0x28409890,0x28409894,
		0x28409898,0x2840989C,0x284098A0,0x284098A4,
		0x284098A8,0x284098AC,0x284098B0,0x284098B4,
		0x284098B8,0x284098BC,0x284098C0,0x284098C4,
		0x284098C8,0x284098CC,0x284098D0,0x284098D4,
		0x284098D8
	},
	{
		0x28509818,0x2850981C,0x28509820,0x28509824,
		0x28509828,0x2850982C,0x28509830,0x28509834,
		0x28509838,0x2850983C,0x28509840,0x28509844,
		0x28509848,0x2850984C,0x28509850,0x28509854,
		0x28509858,0x2850985C,0x28509860,0x28509864,
		0x28509868,0x2850986C,0x28509870,0x28509874,
		0x28509878,0x2850987C,0x28509880,0x28509884,
		0x28509888,0x2850988C,0x28509890,0x28509894,
		0x28509898,0x2850989C,0x285098A0,0x285098A4,
		0x285098A8,0x285098AC,0x285098B0,0x285098B4,
		0x285098B8,0x285098BC,0x285098C0,0x285098C4,
		0x285098C8,0x285098CC,0x285098D0,0x285098D4,
		0x285098D8
	},
	{
		0x28609818,0x2860981C,0x28609820,0x28609824,
		0x28609828,0x2860982C,0x28609830,0x28609834,
		0x28609838,0x2860983C,0x28609840,0x28609844,
		0x28609848,0x2860984C,0x28609850,0x28609854,
		0x28609858,0x2860985C,0x28609860,0x28609864,
		0x28609868,0x2860986C,0x28609870,0x28609874,
		0x28609878,0x2860987C,0x28609880,0x28609884,
		0x28609888,0x2860988C,0x28609890,0x28609894,
		0x28609898,0x2860989C,0x286098A0,0x286098A4,
		0x286098A8,0x286098AC,0x286098B0,0x286098B4,
		0x286098B8,0x286098BC,0x286098C0,0x286098C4,
		0x286098C8,0x286098CC,0x286098D0,0x286098D4,
		0x286098D8
	},
};
static const UINT32	gIM_PRO_CAG_Status_Tbl[E_IM_PRO_UNIT_NUM_MAX] = {
	ImproSrocag_D_IM_SRO1_STATUS_CAG,	ImproSrocag_D_IM_SRO2_STATUS_CAG,	ImproSrocag_D_IM_SRO_STATUS_CAG_BOTH,
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_srocag_constructor(ImproSrocag *self)
{
	ImproSrocagPrivate *priv = IMPRO_SROCAG_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_srocag_destructor(ImproSrocag *self)
{
	ImproSrocagPrivate *priv = IMPRO_SROCAG_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
Start CAG
@param[in]	unitNo : Unit number.
*/
VOID impro_srocag_start( E_IM_PRO_UNIT_NUM unitNo )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.cag.CAGTRG.bit.CAGTRG = D_IM_PRO_TRG_START;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_START_STATUS(gIM_PRO_CAG_Status_Tbl[unitNo], 0);
}

/**
Stop CAG
@param[in]	unitNo : Unit number.
@param[in]	force : force stop option
*/
VOID impro_srocag_stop( E_IM_PRO_UNIT_NUM unitNo, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	if(force == 0) {
		// stop
		ioPro.imgPipe[unitNo].sro.cag.CAGTRG.bit.CAGTRG = D_IM_PRO_TRG_FRAME_STOP;
	}
	else {
		// force stop
		ioPro.imgPipe[unitNo].sro.cag.CAGTRG.bit.CAGTRG = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_STOP_STATUS(gIM_PRO_CAG_Status_Tbl[unitNo], 0);
}


/**
Set CAG control information
@param[in]	unitNo : Unit number.
@param[in]	cagCtrl	: CAG control Information.
*/
INT32 impro_srocag_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproCagCtrl* cagCtrl )
{
#ifdef CO_PARAM_CHECK
	if (cagCtrl == NULL){
		Ddim_Assertion(("I:impro_srocag_ctrl error. cagCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.cag.rbr.bit.rbrv			= cagCtrl->vBinningRatioReciprocalNum;
	ioPro.imgPipe[unitNo].sro.cag.rbr.bit.rbrh			= cagCtrl->hBinningRatioReciprocalNum;
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.aboarh, union IoAboarh,
			aboarh, cagCtrl->optCenterPosH[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.aboagh, union IoAboagh,
			aboagh, cagCtrl->optCenterPosH[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.aboabh, union IoAboabh,
			aboabh, cagCtrl->optCenterPosH[2] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.aboarv, union IoAboarv,
			aboarv, cagCtrl->optCenterPosV[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.aboagv, union IoAboagv,
			aboagv, cagCtrl->optCenterPosV[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.aboabv, union IoAboabv,
			aboabv, cagCtrl->optCenterPosV[2] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.abgar, union IoAbgar,
			abgar,	 cagCtrl->gain[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABGAG, union IoAbgag,
			abgag,	 cagCtrl->gain[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABGAB, union IoAbgab,
			abgab,	 cagCtrl->gain[2] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABLRH, union IoAblrh,
			ablrhu,	 cagCtrl->transferULimitH[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABLGH, union IoAblgh,
			ablghu,	 cagCtrl->transferULimitH[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABLBH, union IoAblbh,
			ablbhu,	 cagCtrl->transferULimitH[2] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABLRH, union IoAblrh,
			ablrhl,	 cagCtrl->transferLLimitH[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABLGH, union IoAblgh,
			ablghl,	 cagCtrl->transferLLimitH[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABLBH, union IoAblbh,
			ablbhl,	 cagCtrl->transferLLimitH[2] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABLRV, union IoAblrv,
			ablrvu,	 cagCtrl->transferULimitV[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABLGV, union IoAblgv,
			ablgvu,	 cagCtrl->transferULimitV[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABLBV, union IoAblbv,
			ablbvu,	 cagCtrl->transferULimitV[2] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABLRV, union IoAblrv,
			ablrvl,	 cagCtrl->transferLLimitV[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABLGV, union IoAblgv,
			ablgvl,	 cagCtrl->transferLLimitV[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABLBV, union IoAblbv,
			ablbvl,	 cagCtrl->transferLLimitV[2] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABOFSRH, union IoAbofsrh,
			abofsrh, cagCtrl->transferOffsetH[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABOFSGH, union IoAbofsgh,
			abofsgh, cagCtrl->transferOffsetH[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABOFSBH, union IoAbofsbh,
			abofsbh, cagCtrl->transferOffsetH[2] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABOFSRV, union IoAbofsrv,
			abofsrv, cagCtrl->transferOffsetV[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABOFSGV, union IoAbofsgv,
			abofsgv, cagCtrl->transferOffsetV[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABOFSBV, union IoAbofsbv,
			abofsbv, cagCtrl->transferOffsetV[2] );
	ioPro.imgPipe[unitNo].sro.cag.ABNLTHR1.bit.ABNLTHR1	= cagCtrl->cornerThresh1[0];
	ioPro.imgPipe[unitNo].sro.cag.ABNLTHG1.bit.ABNLTHG1	= cagCtrl->cornerThresh1[1];
	ioPro.imgPipe[unitNo].sro.cag.ABNLTHB1.bit.ABNLTHB1	= cagCtrl->cornerThresh1[2];
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABNLGAR1, union IoAbnlgar1,
			abnlgar1, cagCtrl->cornerGain1[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABNLGAG1, union IoAbnlgag1,
			abnlgag1, cagCtrl->cornerGain1[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABNLGAB1, union IoAbnlgab1,
			abnlgab1, cagCtrl->cornerGain1[2] );
	ioPro.imgPipe[unitNo].sro.cag.ABNLTHR2.bit.ABNLTHR2	= cagCtrl->cornerThresh2[0];
	ioPro.imgPipe[unitNo].sro.cag.ABNLTHG2.bit.ABNLTHG2	= cagCtrl->cornerThresh2[1];
	ioPro.imgPipe[unitNo].sro.cag.ABNLTHB2.bit.ABNLTHB2	= cagCtrl->cornerThresh2[2];
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABNLGAR2, union IoAbnlgar2,
			abnlgar2, cagCtrl->cornerGain2[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABNLGAG2, union IoAbnlgag2,
			abnlgag2, cagCtrl->cornerGain2[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABNLGAB2, union IoAbnlgab2,
			abnlgab2, cagCtrl->cornerGain2[2] );
	ioPro.imgPipe[unitNo].sro.cag.ABNLTHR3.bit.ABNLTHR3	= cagCtrl->cornerThresh3[0];
	ioPro.imgPipe[unitNo].sro.cag.ABNLTHG3.bit.ABNLTHG3	= cagCtrl->cornerThresh3[1];
	ioPro.imgPipe[unitNo].sro.cag.ABNLTHB3.bit.ABNLTHB3	= cagCtrl->cornerThresh3[2];
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABNLGAR3, union IoAbnlgar3,
			abnlgar3, cagCtrl->cornerGain3[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABNLGAG3, union IoAbnlgag3,
			abnlgag3, cagCtrl->cornerGain3[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABNLGAB3, union IoAbnlgab3,
			abnlgab3, cagCtrl->cornerGain3[2] );
	ioPro.imgPipe[unitNo].sro.cag.ABNLTHR4.bit.ABNLTHR4	= cagCtrl->cornerThresh4[0];
	ioPro.imgPipe[unitNo].sro.cag.ABNLTHG4.bit.ABNLTHG4	= cagCtrl->cornerThresh4[1];
	ioPro.imgPipe[unitNo].sro.cag.ABNLTHB4.bit.ABNLTHB4	= cagCtrl->cornerThresh4[2];
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABNLGAR4, union IoAbnlgar4,
			abnlgar4, cagCtrl->cornerGain4[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABNLGAG4, union IoAbnlgag4,
			abnlgag4, cagCtrl->cornerGain4[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.ABNLGAB4, union IoAbnlgab4,
			abnlgab4, cagCtrl->cornerGain4[2] );
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of CAG.
@param[in]	unitNo : Unit number.
@param[in]	paenTrg :  control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srocag_set_paen( E_IM_PRO_UNIT_NUM unitNo, UCHAR paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( ioPro.imgPipe[unitNo].sro.cag.CAGTRG.bit.CAGTRG != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:Im_PRO_FSHD_Set_PAEN. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.cag.cagpaen.bit.cpaen = paenTrg;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Set CAG area
@param[in]	unitNo : Unit number.
@param[in]	cagArea	: CAG area.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srocag_set_area( E_IM_PRO_UNIT_NUM unitNo, TimproCagArea* cagArea )
{
#ifdef CO_PARAM_CHECK
	if (cagArea == NULL){
		Ddim_Assertion(("I:impro_srocag_set_area error. cagArea=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrocag_D_IM_PRO_CAG_CAGGH_MIN, ImproSrocag_D_IM_PRO_CAG_CAGGH_MAX,
			cagArea->gPosX, "impro_srocag_set_area : gPosX" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrocag_D_IM_PRO_CAG_CAGGV_MIN, ImproSrocag_D_IM_PRO_CAG_CAGGV_MAX,
			cagArea->gPosY, "impro_srocag_set_area : gPosY" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrocag_D_IM_PRO_CAG_CAGGHW_MIN, ImproSrocag_D_IM_PRO_CAG_CAGGHW_MAX,
			cagArea->gWidth, "impro_srocag_set_area : gWidth" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrocag_D_IM_PRO_CAG_CAGGVW_MIN, ImproSrocag_D_IM_PRO_CAG_CAGGVW_MAX,
			cagArea->gLines, "impro_srocag_set_area : gLines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrocag_D_IM_PRO_CAG_CAGH_MIN, ImproSrocag_D_IM_PRO_CAG_CAGH_MAX,
			cagArea->posX, "impro_srocag_set_area : posX" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrocag_D_IM_PRO_CAG_CAGV_MIN, ImproSrocag_D_IM_PRO_CAG_CAGV_MAX,
			cagArea->posY, "impro_srocag_set_area : posY" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrocag_D_IM_PRO_CAG_CAGHW_MIN, ImproSrocag_D_IM_PRO_CAG_CAGHW_MAX,
			cagArea->width, "impro_srocag_set_area : width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrocag_D_IM_PRO_CAG_CAGVW_MIN, ImproSrocag_D_IM_PRO_CAG_CAGVW_MAX,
			cagArea->lines, "impro_srocag_set_area : lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.cag.caggwp.bit.caggh		= cagArea->gPosX;
	ioPro.imgPipe[unitNo].sro.cag.caggwp.bit.caggv		= cagArea->gPosY;
	ioPro.imgPipe[unitNo].sro.cag.caggws.bit.cagghw		= cagArea->gWidth;
	ioPro.imgPipe[unitNo].sro.cag.caggws.bit.caggvw		= cagArea->gLines;
	ioPro.imgPipe[unitNo].sro.cag.cagwp.bit.cagh			= cagArea->posX;
	ioPro.imgPipe[unitNo].sro.cag.cagwp.bit.cagv			= cagArea->posY;
	ioPro.imgPipe[unitNo].sro.cag.cagws.bit.caghw		= cagArea->width;
	ioPro.imgPipe[unitNo].sro.cag.cagws.bit.cagvw		= cagArea->lines;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Set CAG optCenterPosH  control
@param[in]	unitNo : Unit number.
@param[in]	optCenterPosH	: CAG control Information.
*/
INT32 impro_srocag_opt_center_pos_h_ctrl( E_IM_PRO_UNIT_NUM unitNo, SHORT optCenterPosH [3] )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.aboarh, union IoAboarh, aboarh, optCenterPosH[0] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.aboagh, union IoAboagh, aboagh, optCenterPosH[1] );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.cag.aboabh, union IoAboabh, aboabh, optCenterPosH[2] );
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Set CAG G level difference information
@param[in]	unitNo : Unit number.
@param[in]	cagCtrlGlevelDiff	: CAG G level difference Information.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srocag_ctrl_glv_diff( E_IM_PRO_UNIT_NUM unitNo, TimproCagCtrlGlevelDiff* cagCtrlGlevelDiff )
{
#ifdef CO_PARAM_CHECK
	if (cagCtrlGlevelDiff == NULL){
		Ddim_Assertion(("I:impro_srocag_ctrl_glv_diff error. cagCtrlGlevelDiff=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.cag.cagmd.bit.clpsel		= cagCtrlGlevelDiff->clipMode;
	ioPro.imgPipe[unitNo].sro.cag.cagmd.bit.gcamd		= cagCtrlGlevelDiff->gGapCorMode;
	ioPro.imgPipe[unitNo].sro.cag.cagmd.bit.cagpdd		= cagCtrlGlevelDiff->gGapPadMode;
	ioPro.imgPipe[unitNo].sro.cag.cagmd.bit.camd			= cagCtrlGlevelDiff->gGapMode;
	ioPro.imgPipe[unitNo].sro.cag.bfglmt.bit.bfglmth		= cagCtrlGlevelDiff->gradientULimit;
	ioPro.imgPipe[unitNo].sro.cag.bfglmt.bit.bfglmtl		= cagCtrlGlevelDiff->gradientLLimit;
	ioPro.imgPipe[unitNo].sro.cag.bfgth.bit.bfgtha		= cagCtrlGlevelDiff->gradientThreshold;
	ioPro.imgPipe[unitNo].sro.cag.bfgth.bit.bfgthk		= cagCtrlGlevelDiff->gradientThresholdGain;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Get the top address of the address array of CAG control.
@param[in]		unitNo : Unit number.
@param[out]		addr					: Top address of the address array of CAG control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 impro_srocag_get_rdma_addr_cag_cntl( E_IM_PRO_UNIT_NUM unitNo, const TimproRdmaCagAddr** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:impro_srocag_get_rdma_addr_cag_cntl. error. addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &(gIM_PRO_CAG_Addr[unitNo]);

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSrocag类的一个实例
 *
 */
ImproSrocag* 	impro_srocag_new()
{
	ImproSrocag* self = k_object_new_with_private(IMPRO_TYPE_SROCAG,sizeof(ImproSrocagPrivate));
	ImproSrocagPrivate* priv = IMPRO_SROCAG_GET_PRIVATE(self);
	
	e_warning_o(self," impro_srocag_new \n");
	return self;
}
