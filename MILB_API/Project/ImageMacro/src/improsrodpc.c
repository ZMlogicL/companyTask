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
#include"improsrodpc.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSrodpc, impro_srodpc);
#define IMPRO_SRODPC_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSrodpcPrivate, IMPRO_TYPE_SRODPC));


/*宏定义区域*/
/* DPC				*/
#define	ImproSrodpc_D_IM_SRO1_STATUS_DPC		((0x00000000UL)&(1<< 7))
/* DPC				*/
#define	ImproSrodpc_D_IM_SRO2_STATUS_DPC		((0x10000000UL)&(1<< 7))
/* Image Pipe1&2 DPC	*/
#define	ImproSrodpc_D_IM_SRO_STATUS_DPC_BOTH	( ImproSrodpc_D_IM_SRO1_STATUS_DPC	|ImproSrodpc_D_IM_SRO2_STATUS_DPC)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSrodpcPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
static const TimproRdmaDpcAddr S_G_IM_PRO_DPC_Addr[ImproBase_E_IM_PRO_UNIT_NUM_MAX] = {
	{
		0x28409118,0x2840911C,0x28409120,0x28409124,
		0x28409130,0x28409134,0x28409138,0x28409140,
		0x28409144,0x28409148,0x28409150,0x28409154,
		0x28409158,0x28409160,0x28409164,0x28409168,
		0x28409170,0x28409178,0x2840917C,0x28409180,
		0x28409184,0x28409188,0x2840918C,0x28409190,
		0x28409194,0x28409198,0x2840919C,0x284091A0,
		0x284091A4,0x284091A8,0x284091AC,0x284091B0,
		0x284091B4,0x284091B8,0x284091BC,0x284091C0,
		0x284091C4,
	},
	{
		0x28509118,0x2850911C,0x28509120,0x28509124,
		0x28509130,0x28509134,0x28509138,0x28509140,
		0x28509144,0x28509148,0x28509150,0x28509154,
		0x28509158,0x28509160,0x28509164,0x28509168,
		0x28509170,0x28509178,0x2850917C,0x28509180,
		0x28509184,0x28509188,0x2850918C,0x28509190,
		0x28509194,0x28509198,0x2850919C,0x285091A0,
		0x285091A4,0x285091A8,0x285091AC,0x285091B0,
		0x285091B4,0x285091B8,0x285091BC,0x285091C0,
		0x285091C4,
	},
	{
		0x28609118,0x2860911C,0x28609120,0x28609124,
		0x28609130,0x28609134,0x28609138,0x28609140,
		0x28609144,0x28609148,0x28609150,0x28609154,
		0x28609158,0x28609160,0x28609164,0x28609168,
		0x28609170,0x28609178,0x2860917C,0x28609180,
		0x28609184,0x28609188,0x2860918C,0x28609190,
		0x28609194,0x28609198,0x2860919C,0x286091A0,
		0x286091A4,0x286091A8,0x286091AC,0x286091B0,
		0x286091B4,0x286091B8,0x286091BC,0x286091C0,
		0x286091C4,
	},
};
static const UINT32	gIM_PRO_DPC_Status_Tbl[ImproBase_E_IM_PRO_UNIT_NUM_MAX] = {
	ImproSrodpc_D_IM_SRO1_STATUS_DPC,	ImproSrodpc_D_IM_SRO2_STATUS_DPC,	ImproSrodpc_D_IM_SRO_STATUS_DPC_BOTH,
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_srodpc_constructor(ImproSrodpc *self)
{
	ImproSrodpcPrivate *priv = IMPRO_SRODPC_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_srodpc_destructor(ImproSrodpc *self)
{
	ImproSrodpcPrivate *priv = IMPRO_SRODPC_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
Compensation mode start
@param[in]	unitNo : Unit number.
@retval		D_DDIM_OK					: Processing OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_srodpc_start( E_IM_PRO_UNIT_NUM unitNo )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.dpc.dpctrg.bit.dpctrg = D_IM_PRO_TRG_START;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_START_STATUS(gIM_PRO_DPC_Status_Tbl[unitNo], 0);

	return D_DDIM_OK;
}

/**
Compensation mode stop
@param[in]	unitNo : Unit number.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Processing OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_srodpc_stop( E_IM_PRO_UNIT_NUM unitNo, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	if(force == 0) {
		// stop
		ioPro.imgPipe[unitNo].sro.dpc.dpctrg.bit.dpctrg = D_IM_PRO_TRG_FRAME_STOP;
	}
	else {
		// force stop
		ioPro.imgPipe[unitNo].sro.dpc.dpctrg.bit.dpctrg = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_STOP_STATUS(gIM_PRO_DPC_Status_Tbl[unitNo], 0);

	return D_DDIM_OK;
}

/**
DPC control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcCtrl : DPC control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srodpc_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcCtrl* dpcCtrl )
{
#ifdef CO_PARAM_CHECK
	if (dpcCtrl == NULL){
		Ddim_Assertion(("I:impro_srodpc_ctrl error. dpcCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.dpc.dpcmd.bit.dpcmd			= dpcCtrl->dpcMode;
	ioPro.imgPipe[unitNo].sro.dpc.dpcmd.bit.dpcrtz			= dpcCtrl->threConv0;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of AEAWB.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srodpc_set_paen( E_IM_PRO_UNIT_NUM unitNo, UCHAR paenTrg )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.dpc.dpcpaen.bit.dpaen = paenTrg;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
DPC control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcArea : DPC control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srodpc_set_area( E_IM_PRO_UNIT_NUM unitNo, TimproDpcArea* dpcArea )
{
#ifdef CO_PARAM_CHECK
	if (dpcArea == NULL){
		Ddim_Assertion(("I:impro_srodpc_set_area error. dpcArea=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrodpc_D_IM_PRO_DPC_DPCGH_MIN, ImproSrodpc_D_IM_PRO_DPC_DPCGH_MAX,
			dpcArea->gPosX, "impro_srodpc_set_area : gPosX" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrodpc_D_IM_PRO_DPC_DPCGV_MIN, ImproSrodpc_D_IM_PRO_DPC_DPCGV_MAX,
			dpcArea->gPosY, "impro_srodpc_set_area : gPosY" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrodpc_D_IM_PRO_DPC_DPCGHW_MIN, ImproSrodpc_D_IM_PRO_DPC_DPCGHW_MAX,
			dpcArea->gWidth, "impro_srodpc_set_area : gWidth" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrodpc_D_IM_PRO_DPC_DPCGVW_MIN, ImproSrodpc_D_IM_PRO_DPC_DPCGVW_MAX,
			dpcArea->gLines, "impro_srodpc_set_area : gLines" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrodpc_D_IM_PRO_DPC_DPCH_MIN, ImproSrodpc_D_IM_PRO_DPC_DPCH_MAX,
			dpcArea->posX, "impro_srodpc_set_area : posX" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrodpc_D_IM_PRO_DPC_DPCV_MIN, ImproSrodpc_D_IM_PRO_DPC_DPCV_MAX,
			dpcArea->posY, "impro_srodpc_set_area : posY" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrodpc_D_IM_PRO_DPC_DPCHW_MIN, ImproSrodpc_D_IM_PRO_DPC_DPCHW_MAX,
			dpcArea->width, "impro_srodpc_set_area : width" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrodpc_D_IM_PRO_DPC_DPCVW_MIN, ImproSrodpc_D_IM_PRO_DPC_DPCVW_MAX,
			dpcArea->lines, "impro_srodpc_set_area : lines" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.dpc.dpcgwp.bit.dpcgh			= dpcArea->gPosX;
	ioPro.imgPipe[unitNo].sro.dpc.dpcgwp.bit.dpcgv			= dpcArea->gPosY;
	ioPro.imgPipe[unitNo].sro.dpc.dpcgws.bit.dpcghw			= dpcArea->gWidth;
	ioPro.imgPipe[unitNo].sro.dpc.dpcgws.bit.dpcgvw			= dpcArea->gLines;
	ioPro.imgPipe[unitNo].sro.dpc.dpcwp.bit.dpch				= dpcArea->posX;
	ioPro.imgPipe[unitNo].sro.dpc.dpcwp.bit.dpcv				= dpcArea->posY;
	ioPro.imgPipe[unitNo].sro.dpc.dpcws.bit.dpchw			= dpcArea->width;
	ioPro.imgPipe[unitNo].sro.dpc.dpcws.bit.dpcvw			= dpcArea->lines;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Alpha blend control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcAbCtrl : Alpha blend Control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srodpc_alpha_blend_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcAbCtrl* dpcAbCtrl )
{
#ifdef CO_PARAM_CHECK
	if (dpcAbCtrl == NULL){
		Ddim_Assertion(("I:impro_srodpc_alpha_blend_ctrl error. dpcAbCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrodpc_D_IM_PRO_DPC_DPCBLW_MIN, ImproSrodpc_D_IM_PRO_DPC_DPCBLW_MAX,
			dpcAbCtrl->alphaBlendTransitionWidthP, "impro_srodpc_alpha_blend_ctrl : alphaBlendTransitionWidthP" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrodpc_D_IM_PRO_DPC_DPCBLW_MIN, ImproSrodpc_D_IM_PRO_DPC_DPCBLW_MAX,
			dpcAbCtrl->alphaBlendTransitionWidthM, "impro_srodpc_alpha_blend_ctrl : alphaBlendTransitionWidthM" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.dpc.dpcblp.bit.dpcblwp			= dpcAbCtrl->alphaBlendTransitionWidthP;
	ioPro.imgPipe[unitNo].sro.dpc.dpcblp.bit.dpcblsp			= dpcAbCtrl->alphaBlendStartPosP;
	ioPro.imgPipe[unitNo].sro.dpc.dpcblm.bit.dpcblwm			= dpcAbCtrl->alphaBlendTransitionWidthM;
	ioPro.imgPipe[unitNo].sro.dpc.dpcblm.bit.dpcblsm			= dpcAbCtrl->alphaBlendStartPosM;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Defect Dynamic Detection control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcDddCtrl : Defect Dynamic Detection Control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srodpc_dynamic_detect_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcDddCtrl* dpcDddCtrl )
{
#ifdef CO_PARAM_CHECK
	if (dpcDddCtrl == NULL){
		Ddim_Assertion(("I:impro_srodpc_dynamic_detect_ctrl error. dpcDddCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.dpc.dfctl.bit.dfgrgb			= dpcDddCtrl->grgbIndependentSetting;
	ioPro.imgPipe[unitNo].sro.dpc.dfctl.bit.dfmdg			= dpcDddCtrl->gMode;
	ioPro.imgPipe[unitNo].sro.dpc.dfctl.bit.dfmdrb			= dpcDddCtrl->rbMode;
	ioPro.imgPipe[unitNo].sro.dpc.dfctl.bit.dfdcnt			= dpcDddCtrl->upperLimitLocalRegistration;
	ioPro.imgPipe[unitNo].sro.dpc.dfctl.bit.dfrbug			= dpcDddCtrl->useMdd;
	ioPro.imgPipe[unitNo].sro.dpc.dfctl.bit.dfagnd			= dpcDddCtrl->support2concecutiveDefect;
	ioPro.imgPipe[unitNo].sro.dpc.dfs.dfs1.bit.dfsrp			= dpcDddCtrl->pThresholdStartPos[0];
	ioPro.imgPipe[unitNo].sro.dpc.dfs.dfs2.bit.dfsgp			= dpcDddCtrl->pThresholdStartPos[1];
	ioPro.imgPipe[unitNo].sro.dpc.dfs.dfs3.bit.dfsbp			= dpcDddCtrl->pThresholdStartPos[2];
	ioPro.imgPipe[unitNo].sro.dpc.dfs.dfs1.bit.dfsrm			= dpcDddCtrl->mThresholdStartPos[0];
	ioPro.imgPipe[unitNo].sro.dpc.dfs.dfs2.bit.dfsgm			= dpcDddCtrl->mThresholdStartPos[1];
	ioPro.imgPipe[unitNo].sro.dpc.dfs.dfs3.bit.dfsbm			= dpcDddCtrl->mThresholdStartPos[2];
	ioPro.imgPipe[unitNo].sro.dpc.dfo.dfo1.bit.dforp			= dpcDddCtrl->pThresholdStartOffset[0];
	ioPro.imgPipe[unitNo].sro.dpc.dfo.dfo2.bit.dfogp			= dpcDddCtrl->pThresholdStartOffset[1];
	ioPro.imgPipe[unitNo].sro.dpc.dfo.dfo3.bit.dfobp			= dpcDddCtrl->pThresholdStartOffset[2];
	ioPro.imgPipe[unitNo].sro.dpc.dfo.dfo1.bit.dform			= dpcDddCtrl->mThresholdStartOffset[0];
	ioPro.imgPipe[unitNo].sro.dpc.dfo.dfo2.bit.dfogm			= dpcDddCtrl->mThresholdStartOffset[1];
	ioPro.imgPipe[unitNo].sro.dpc.dfo.dfo3.bit.dfobm			= dpcDddCtrl->mThresholdStartOffset[2];
	ioPro.imgPipe[unitNo].sro.dpc.dfk.dfk1.bit.dfkrp			= dpcDddCtrl->pThresholdGain[0];
	ioPro.imgPipe[unitNo].sro.dpc.dfk.dfk2.bit.dfkgp			= dpcDddCtrl->pThresholdGain[1];
	ioPro.imgPipe[unitNo].sro.dpc.dfk.dfk3.bit.dfkbp			= dpcDddCtrl->pThresholdGain[2];
	ioPro.imgPipe[unitNo].sro.dpc.dfk.dfk1.bit.dfkrm			= dpcDddCtrl->mThresholdGain[0];
	ioPro.imgPipe[unitNo].sro.dpc.dfk.dfk2.bit.dfkgm			= dpcDddCtrl->mThresholdGain[1];
	ioPro.imgPipe[unitNo].sro.dpc.dfk.dfk3.bit.dfkbm			= dpcDddCtrl->mThresholdGain[2];
	ioPro.imgPipe[unitNo].sro.dpc.dfh.dfh1.bit.dfhrp			= dpcDddCtrl->pThresholdUpperLimit[0];
	ioPro.imgPipe[unitNo].sro.dpc.dfh.dfh2.bit.dfhgp			= dpcDddCtrl->pThresholdUpperLimit[1];
	ioPro.imgPipe[unitNo].sro.dpc.dfh.dfh3.bit.dfhbp			= dpcDddCtrl->pThresholdUpperLimit[2];
	ioPro.imgPipe[unitNo].sro.dpc.dfh.dfh1.bit.dfhrm			= dpcDddCtrl->mThresholdUpperLimit[0];
	ioPro.imgPipe[unitNo].sro.dpc.dfh.dfh2.bit.dfhgm			= dpcDddCtrl->mThresholdUpperLimit[1];
	ioPro.imgPipe[unitNo].sro.dpc.dfh.dfh3.bit.dfhbm			= dpcDddCtrl->mThresholdUpperLimit[2];
	ioPro.imgPipe[unitNo].sro.dpc.dfcsr.bit.dfcsrp			= dpcDddCtrl->pthreshold2consecutive;
	ioPro.imgPipe[unitNo].sro.dpc.dfcsr.bit.dfcsrm			= dpcDddCtrl->mthreshold2consecutive;
	ioPro.imgPipe[unitNo].sro.dpc.dflsth.dflsth1.bit.dflsthr	= dpcDddCtrl->threshold2consecutiveBrightPix[0];
	ioPro.imgPipe[unitNo].sro.dpc.dflsth.dflsth1.bit.dflsthg	= dpcDddCtrl->threshold2consecutiveBrightPix[1];
	ioPro.imgPipe[unitNo].sro.dpc.dflsth.dflsth2.bit.dflsthb	= dpcDddCtrl->threshold2consecutiveBrightPix[2];
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Calculation of mis-determination degree control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcMddCtrl : Calculation of mis-determination degree for correction Control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srodpc_mis_determination_calc_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcMddCtrl* dpcMddCtrl )
{
#ifdef CO_PARAM_CHECK
	if (dpcMddCtrl == NULL){
		Ddim_Assertion(("I:impro_srodpc_mis_determination_calc_ctrl error. dpcMddCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.dpc.dfagef.bit.dfagefp			= dpcMddCtrl->pMddEffect;
	ioPro.imgPipe[unitNo].sro.dpc.dfagef.bit.dfagefm			= dpcMddCtrl->mMddEffect;
	ioPro.imgPipe[unitNo].sro.dpc.dfagef2.bit.dfagefp2		= dpcMddCtrl->pMddEffect2;
	ioPro.imgPipe[unitNo].sro.dpc.dfagef2.bit.dfagefm2		= dpcMddCtrl->mMddEffect2;
	ioPro.imgPipe[unitNo].sro.dpc.dfagth.bit.dfagthp			= dpcMddCtrl->pThresholdOffset;
	ioPro.imgPipe[unitNo].sro.dpc.dfagth.bit.dfagthm			= dpcMddCtrl->mThresholdOffset;
	ioPro.imgPipe[unitNo].sro.dpc.dfagthk.bit.dfagthkp		= dpcMddCtrl->pThresholdGain;
	ioPro.imgPipe[unitNo].sro.dpc.dfagthk.bit.dfagthkm		= dpcMddCtrl->mThresholdGain;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Pixel value magnitude defect correction control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcMdcCtrl : Pixel value magnitude defect correction control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srodpc_magnitude_defect_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcMdcCtrl* dpcMdcCtrl )
{
#ifdef CO_PARAM_CHECK
	if (dpcMdcCtrl == NULL){
		Ddim_Assertion(("I:impro_srodpc_magnitude_defect_ctrl error. dpcMdcCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.dpc.dmctl.bit.dmgug			= dpcMdcCtrl->useOcd;
	ioPro.imgPipe[unitNo].sro.dpc.dmwks.bit.dmwksp			= dpcMdcCtrl->pManualAdjValSingle;
	ioPro.imgPipe[unitNo].sro.dpc.dmwks.bit.dmwksm			= dpcMdcCtrl->mManualAdjValSingle;
	ioPro.imgPipe[unitNo].sro.dpc.dmwkd.bit.dmwkdp			= dpcMdcCtrl->pManualAdjVal2consecutive;
	ioPro.imgPipe[unitNo].sro.dpc.dmwkd.bit.dmwkdm			= dpcMdcCtrl->mManualAdjVal2consecutive;
	ioPro.imgPipe[unitNo].sro.dpc.dmagk.bit.dmagkp			= dpcMdcCtrl->pCorrectionLevelOnOcd;
	ioPro.imgPipe[unitNo].sro.dpc.dmagk.bit.dmagkm			= dpcMdcCtrl->mCorrectionLevelOnOcd;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Edge storage defect correction control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcEsdcCtrl : Edge storage defect correction Control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srodpc_edge_storage_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcEsdcCtrl* dpcEsdcCtrl )
{
#ifdef CO_PARAM_CHECK
	if (dpcEsdcCtrl == NULL){
		Ddim_Assertion(("I:impro_srodpc_edge_storage_ctrl error. dpcEsdcCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.dpc.dectl.bit.degrgb			= dpcEsdcCtrl->esdMode;
	ioPro.imgPipe[unitNo].sro.dpc.dectl.bit.derbug			= dpcEsdcCtrl->useRbJdge;
	ioPro.imgPipe[unitNo].sro.dpc.dectl.bit.degug			= dpcEsdcCtrl->useOcd;
	ioPro.imgPipe[unitNo].sro.dpc.denss.bit.denss			= dpcEsdcCtrl->thresholdStartPos;
	ioPro.imgPipe[unitNo].sro.dpc.denso.bit.denso			= dpcEsdcCtrl->thresholdOffset;
	ioPro.imgPipe[unitNo].sro.dpc.densk.bit.densk			= dpcEsdcCtrl->thresholdGain;
	ioPro.imgPipe[unitNo].sro.dpc.densh.bit.densh			= dpcEsdcCtrl->thresholdUpperLimit;
	ioPro.imgPipe[unitNo].sro.dpc.densmgn.bit.densmgn		= dpcEsdcCtrl->noiseTolerance;
	ioPro.imgPipe[unitNo].sro.dpc.dendcth.bit.dendcth		= dpcEsdcCtrl->thresholdCalculation;
	ioPro.imgPipe[unitNo].sro.dpc.deagk.bit.deagkp			= dpcEsdcCtrl->pCorrectionLevelOnOcd;
	ioPro.imgPipe[unitNo].sro.dpc.deagk.bit.deagkm			= dpcEsdcCtrl->mCorrectionLevelOnOcd;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Calculation of over-correction degree for correction control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcOcdCtrl : Calculation of over-correction degree for correction control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srodpc_over_correction_detect_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcOcdCtrl* dpcOcdCtrl )
{
#ifdef CO_PARAM_CHECK
	if (dpcOcdCtrl == NULL){
		Ddim_Assertion(("I:impro_srodpc_over_correction_detect_ctrl error. dpcOcdCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.dpc.dcagef.bit.dcagefp			= dpcOcdCtrl->pOcdEffect;
	ioPro.imgPipe[unitNo].sro.dpc.dcagef.bit.dcagefm			= dpcOcdCtrl->mOcdEffect;
	ioPro.imgPipe[unitNo].sro.dpc.dcagth.bit.dcagthp			= dpcOcdCtrl->pThreshold;
	ioPro.imgPipe[unitNo].sro.dpc.dcagth.bit.dcagthm			= dpcOcdCtrl->mThreshold;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Get the top address of the address array of DPC control.
@param[in]		unitNo : Unit number.
@param[out]		addr					: Top address of the address array of SDC control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 impro_srodpc_get_rdma_addr_dpc_cntl( E_IM_PRO_UNIT_NUM unitNo, const TimproRdmaDpcAddr** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:impro_srodpc_get_rdma_addr_dpc_cntl. error. addr=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &(S_G_IM_PRO_DPC_Addr[unitNo]);

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSrodpc类的一个实例
 *
 */
ImproSrodpc* 	impro_srodpc_new()
{
	ImproSrodpc* self = k_object_new_with_private(IMPRO_TYPE_SRODPC,sizeof(ImproSrodpcPrivate));
	ImproSrodpcPrivate* priv = IMPRO_SRODPC_GET_PRIVATE(self);
	
	e_warning_o(self," impro_srodpc_new \n");
	return self;
}
