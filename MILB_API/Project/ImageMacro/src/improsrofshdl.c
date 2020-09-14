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
#include"improsrofshdl.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSrofshdl, impro_srofshdl);
#define IMPRO_SROFSHDL_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSrofshdlPrivate, IMPRO_TYPE_SROFSHDL));


/*宏定义区域*/
/* FSHDL0			*/
#define	ImproSrofshdl_D_IM_SRO1_STATUS_FSHDL0		((0x00000000UL)&(1<<10))
/* FSHDL1			*/
#define	ImproSrofshdl_D_IM_SRO1_STATUS_FSHDL1		((0x00000000UL)&(1<<11))
/* FSHDL0			*/
#define	ImproSrofshdl_D_IM_SRO2_STATUS_FSHDL0		((0x10000000UL)&(1<<10))
/* FSHDL1			*/
#define	ImproSrofshdl_D_IM_SRO2_STATUS_FSHDL1		((0x10000000UL)&(1<<11))
/* Image Pipe1&2 FSHDL0	*/
#define	ImproSrofshdl_D_IM_SRO_STATUS_FSHDL0_BOTH	( ImproSrofshdl_D_IM_SRO1_STATUS_FSHDL0\
																									| ImproSrofshdl_D_IM_SRO2_STATUS_FSHDL0	)
/* Image Pipe1&2 FSHDL1	*/
#define	ImproSrofshdl_D_IM_SRO_STATUS_FSHDL1_BOTH	( ImproSrofshdl_D_IM_SRO1_STATUS_FSHDL1\
																									| ImproSrofshdl_D_IM_SRO2_STATUS_FSHDL1	)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSrofshdlPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
static const TimproRdmaFshdlAddr S_G_IM_PRO_FSHDL_ADDR[ImproBase_E_IM_PRO_UNIT_NUM_MAX]
                                                       	   	   	   [ImproSrofshdl_D_IM_PRO_SRO_FSHDL_CH_NUM] = {
	{
		{
			0x2840931C,0x28409320,0x28409324,0x28409328,
			0x28409330,0x28409334,0x28409338,0x2840933C,
			0x28409340,0x28409344,0x28409350,0x28409354,
			0x28409358,
		},
		{
			0x28409A1C,0x28409A20,0x28409A24,0x28409A28,
			0x28409A30,0x28409A34,0x28409A38,0x28409A3C,
			0x28409A40,0x28409A44,0x28409A50,0x28409A54,
			0x28409A58,
		},
	},
	{
		{
			0x2850931C,0x28509320,0x28509324,0x28509328,
			0x28509330,0x28509334,0x28509338,0x2850933C,
			0x28509340,0x28509344,0x28509350,0x28509354,
			0x28509358,
		},
		{
			0x28509A1C,0x28509A20,0x28509A24,0x28509A28,
			0x28509A30,0x28509A34,0x28509A38,0x28509A3C,
			0x28509A40,0x28509A44,0x28509A50,0x28509A54,
			0x28509A58,
		},
	},
	{
		{
			0x2860931C,0x28609320,0x28609324,0x28609328,
			0x28609330,0x28609334,0x28609338,0x2860933C,
			0x28609340,0x28609344,0x28609350,0x28609354,
			0x28609358,
		},
		{
			0x28609A1C,0x28609A20,0x28609A24,0x28609A28,
			0x28609A30,0x28609A34,0x28609A38,0x28609A3C,
			0x28609A40,0x28609A44,0x28609A50,0x28609A54,
			0x28609A58,
		},
	},
};
static const T_IM_PRO_SRO_FSHDL_INFO	S_G_IM_PRO_FSHDL_STATUS_TBL[ImproBase_E_IM_PRO_UNIT_NUM_MAX]
                                    	                            		[ImproSrofshdl_D_IM_PRO_SRO_FSHDL_CH_NUM] = {
	// ImproBase_E_IM_PRO_UNIT_NUM_1
	{
		{ &ioPro.imgPipe[0].sro.fshdl0,	ImproSrofshdl_D_IM_SRO1_STATUS_FSHDL0	},
		{ &ioPro.imgPipe[0].sro.fshdl1,	ImproSrofshdl_D_IM_SRO1_STATUS_FSHDL1	},
	},
	// ImproBase_E_IM_PRO_UNIT_NUM_2
	{
		{ &ioPro.imgPipe[1].sro.fshdl0,	ImproSrofshdl_D_IM_SRO2_STATUS_FSHDL0	},
		{ &ioPro.imgPipe[1].sro.fshdl1,	ImproSrofshdl_D_IM_SRO2_STATUS_FSHDL1	},
	},
	// ImproBase_E_IM_PRO_BOTH_UNIT
	{
		{ &ioPro.imgPipe[2].sro.fshdl0,	ImproSrofshdl_D_IM_SRO_STATUS_FSHDL0_BOTH	},
		{ &ioPro.imgPipe[2].sro.fshdl1,	ImproSrofshdl_D_IM_SRO_STATUS_FSHDL1_BOTH	},
	},
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_srofshdl_constructor(ImproSrofshdl *self)
{
	ImproSrofshdlPrivate *priv = IMPRO_SROFSHDL_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_srofshdl_destructor(ImproSrofshdl *self)
{
	ImproSrofshdlPrivate *priv = IMPRO_SROFSHDL_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
VOID impro_srofshdl_comm_get_fshdl_reg_info( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch,
			const T_IM_PRO_SRO_FSHDL_INFO** fshdlInfo )
{
	*fshdlInfo = &S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch];
}

/**
Flat Shading Start
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK				: Setting OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG	: PRCH/M2P not running NG
@remarks	Flat Shading Compensation function is started(enable).
*/
// Dd_Top_Start_Clock
INT32 impro_srofshdl_start( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch )
{
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshtrg.bit.ffshtrg = D_IM_PRO_TRG_START;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_START_STATUS(S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].status, 0);

	return D_DDIM_OK;
}

/**
Flat Shading Stop
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK				: Setting OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG	: PRCH/M2P not stopped NG
@remarks	Flat Shading Compensation function is stopped(disable).
*/
INT32 impro_srofshdl_stop( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	if(force == 0) {
		// stop
		S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshtrg.bit.ffshtrg = D_IM_PRO_TRG_FRAME_STOP;
	}
	else {
		// force stop
		S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshtrg.bit.ffshtrg = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_STOP_STATUS(S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].status, 0);

	return D_DDIM_OK;
}

/**
Flat Shading Control
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	fshdlCtrl : Shading Control information
@retval		D_DDIM_OK						: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
INT32 impro_srofshdl_ctrl( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch, TimproFshdlCommonCtrl* fshdlCtrl )
{
#ifdef CO_PARAM_CHECK
	if (fshdlCtrl == NULL){
		Ddim_Assertion(("I:impro_srofshdl_ctrl error. fshdlCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULRR_MIN,
			ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULRR_MAX, fshdlCtrl->clipR, "impro_srofshdl_ctrl : clipR" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULGR_MIN,
			ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULGR_MAX, fshdlCtrl->clipGr, "impro_srofshdl_ctrl : clipGr" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULGB_MIN,
			ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULGB_MAX, fshdlCtrl->clipGb, "impro_srofshdl_ctrl : clipGb" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULBB_MIN,
			ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULBB_MAX, fshdlCtrl->clipB, "impro_srofshdl_ctrl : clipB" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshctl.bit.ffshptmd		= fshdlCtrl->montageMode;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->FFSHUL1.bit.FFSHULRR		= fshdlCtrl->clipR;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->FFSHUL1.bit.FFSHULGR		= fshdlCtrl->clipGr;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->FFSHUL2.bit.FFSHULGB		= fshdlCtrl->clipGb;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->FFSHUL2.bit.FFSHULBB		= fshdlCtrl->clipB;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}


/**
Flat Shading Blend ratio Control
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	fshdlCtrl : Shading Control information
@retval		D_DDIM_OK						: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
INT32 impro_srofshdl_set_blend( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch, TimproFshdlBlendCtrl* blendCtrl )
{
#ifdef CO_PARAM_CHECK
	if (blendCtrl == NULL){
		Ddim_Assertion(("I:impro_srofshdl_set_blend error. blendCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	im_pro_set_reg_signed( S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->FFSHBC,
			union io_fshdlbc, FFSHBC0, blendCtrl->shadingBlend0 );
	im_pro_set_reg_signed( S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->FFSHBC,
			union io_fshdlbc, FFSHBC1, blendCtrl->shadingBlend1 );
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of FSHDL.
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srofshdl_set_paen( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch, UCHAR paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->FFSHTRG.bit.ffshtrg
														!= D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:impro_srofshdl_set_paen. macro has not stopped error.\n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->FFSHPAEN.bit.FFSHPAEN	= paenTrg;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
A Setup is Flat Shading Area
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	fshdlArea : Area for Shading compensation See @ref TimproAreaInfo<br>
 												value range  :posX[0 - 4095]<br>
 												target registor  :@@FFSHH<br>
 												value range  :posY[2 - 8960] 2line boundary<br>
 												target registor  :@@FFSHV<br>
 												value range  :width[4 - 2496] 4pixel boundary<br>
 												target registor  :@@FFSHHW<br>
 												value range  :lines[4 - 8960] 4pixel boundary<br>
 												target registor  :@@FFSHVW
@retval		D_DDIM_OK						: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
INT32 impro_srofshdl_set_area( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch, TimproAreaInfo* fshdlArea )
{
#ifdef CO_PARAM_CHECK
	if (fshdlArea == NULL){
		Ddim_Assertion(("I:impro_srofshdl_set_area error. fshdlArea=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHH_MIN, ImproSrofshdl_D_IM_PRO_FSHDL_FFSHH_MAX,
			fshdlArea->posX, "impro_srofshdl_set_area : posX" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHV_MIN, ImproSrofshdl_D_IM_PRO_FSHDL_FFSHV_MAX,
			fshdlArea->posY, "impro_srofshdl_set_area : posY" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHHW_MIN, ImproSrofshdl_D_IM_PRO_FSHDL_FFSHHW_MAX,
			fshdlArea->width, "impro_srofshdl_set_area : width" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHVW_MIN, ImproSrofshdl_D_IM_PRO_FSHDL_FFSHVW_MAX,
			fshdlArea->lines, "impro_srofshdl_set_area : lines" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshv.bit.ffshv			= fshdlArea->posY;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshh.bit.ffshh			= fshdlArea->posX;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshvw.bit.ffshvw		= fshdlArea->lines;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshhw.bit.ffshhw		= fshdlArea->width;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Flat Shading (Frame Correction) Control
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	FSHDL_ctrl : Frame Correction Control information
@retval		D_DDIM_OK						: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
INT32 impro_srofshdl_set_frame( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch, TimproFshdlFrameCtrl* fshdlCtrl )
{
#ifdef CO_PARAM_CHECK
	if (fshdlCtrl == NULL){
		Ddim_Assertion(("I:impro_srofshdl_set_frame error. FSHDL_ctrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRH_MIN,
			ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRH_MAX, fshdlCtrl->frameHorizontalSize,
			"impro_srofshdl_set_frame : frameHorizontalSize" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRV_MIN,
			ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRV_MAX, fshdlCtrl->frameVorizontalSize,
			"impro_srofshdl_set_frame : frameVorizontalSize" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSPH_MIN,
			ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSPH_MAX, fshdlCtrl->horizontalPixel,
			"impro_srofshdl_set_frame : horizontalPixel" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSPV_MIN,
			ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSPV_MAX, fshdlCtrl->verticalPixel,
			"impro_srofshdl_set_frame : verticalPixel" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSTH_MIN,
			ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSTH_MAX, fshdlCtrl->startPosH,
			"impro_srofshdl_set_frame : startPosH" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSTV_MIN,
			ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSTV_MAX, fshdlCtrl->startPosV,
"impro_srofshdl_set_frame : startPosV" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHHWPH_MIN,
			ImproSrofshdl_D_IM_PRO_FSHDL_FFSHHWPH_MAX, fshdlCtrl->montagePosH,
			"impro_srofshdl_set_frame : montagePosH" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshgfmt.bit.ffshgfmt	= fshdlCtrl->selectFormat;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshsubpr.bit.ffshsubprh	= fshdlCtrl->frameHorizontalSize;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshsubpr.bit.ffshsubprv	= fshdlCtrl->frameVorizontalSize;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshsubsp.bit.ffshsubsph	= fshdlCtrl->horizontalPixel;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshsubsp.bit.ffshsubspv	= fshdlCtrl->verticalPixel;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshsubdr.bit.ffshsubdrm	= fshdlCtrl->InverseBase;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshsubdr.bit.ffshsubdre	= fshdlCtrl->InverseExponent;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshsubst.bit.ffshsubsth	= fshdlCtrl->startPosH;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshsubst.bit.ffshsubstv	= fshdlCtrl->startPosV;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshhwph.bit.ffshhwph	= fshdlCtrl->montagePosH;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshcctl.bit.ffshcen		= fshdlCtrl->satCorrectionEnabled;
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshlp1.bit.ffshlprr		= fshdlCtrl->satSlopeGain[0];
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshlp1.bit.ffshlpgr		= fshdlCtrl->satSlopeGain[1];
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshlp2.bit.ffshlpgb		= fshdlCtrl->satSlopeGain[2];
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshlp2.bit.ffshlpbb		= fshdlCtrl->satSlopeGain[3];
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
set the request issue interval when reading the coefficients from PRCH/M2P macro.
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	reqIntervalClk : RAM access control<br>
			value range :[4~1023]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srofshdl_set_coeff_read_line_wait( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch, USHORT reqIntervalClk )
{
#ifdef CO_PARAM_CHECK
	if( im_pro_check_val_range( ImproSrofshdl_D_IM_PRO_FSHDL_FFSHWRIC_MIN, ImproSrofshdl_D_IM_PRO_FSHDL_FFSHWRIC_MAX, reqIntervalClk, "impro_srofshdl_set_coeff_read_line_wait : reqIntervalClk" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( reqIntervalClk >= ((S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshhw.bit.ffshhw
			- (4*S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshsubpr.bit.ffshsubprh))-10)/3 ) {
		Ddim_Assertion(("I:impro_srofshdl_set_coeff_read_line_wait. parameter error. Please satisfy following"
				" relationship. (reqIntervalClk  < ((FFSHHW-(4*FFSHSUBPRH)) -10)/3) (%u)\n", reqIntervalClk));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	S_G_IM_PRO_FSHDL_STATUS_TBL[unitNo][ch].regPtr->ffshwric.bit.ffshwric	= reqIntervalClk;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Get the top address of the address array of FSHDL control.
@param[in]		unitNo : Unit number.
@param[in]		ch : Channel No
@param[out]		addr					: Top address of the address array of FSHDL control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 impro_srofshdl_get_rdma_addr_fshdl_cntl( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch,
				const TimproRdmaFshdlAddr** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:impro_srofshdl_get_rdma_addr_fshdl_cntl. error. addr=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &(S_G_IM_PRO_FSHDL_ADDR[unitNo][ch]);

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSrofshdl类的一个实例
 *
 */
ImproSrofshdl* 	impro_srofshdl_new()
{
	ImproSrofshdl* self = k_object_new_with_private(IMPRO_TYPE_SROFSHDL,sizeof(ImproSrofshdlPrivate));
	ImproSrofshdlPrivate* priv = IMPRO_SROFSHDL_GET_PRIVATE(self);
	
	e_warning_o(self," impro_srofshdl_new \n");
	return self;
}
