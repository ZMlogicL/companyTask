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
#include"improsenlvds.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSenlvds, impro_senlvds);
#define IMPRO_SENLVDS_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSenlvdsPrivate, IMPRO_TYPE_SENLVDS));


/*宏定义区域*/


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSenlvdsPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static const USHORT S_GIM_PRO_MAXIMUM_SIZE_LVDS[ImproSentop_E_IM_PRO_SENTOP_SENCORE_MAX_HSIZE_CTRL_3 + 1]
                                         [ImproBase_E_IM_PRO_LVDS_CH_3 + 1] = {
	{2960,	2960,	2960,	2960},
	{5920,	5920,	0,		1024},
	{11840,	0,		0,		1024},
	{0,		0,		0,		0	},
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_senlvds_constructor(ImproSenlvds *self)
{
	ImproSenlvdsPrivate *priv = IMPRO_SENLVDS_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_senlvds_destructor(ImproSenlvds *self)
{
	ImproSenlvdsPrivate *priv = IMPRO_SENLVDS_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
LVDS macro start.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Macro Start OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: LVDS has not stopped NG
*/
INT32 impro_senlvds_start( EimproLvdsCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.lvds[ch].lvdstrg.bit.lvdstrg = D_IM_PRO_TRG_START;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	im_pro_common_fig_im_pro_sen_set_start_status(D_IM_SEN_STATUS_LVDS0, ch);

	return D_DDIM_OK;
}

/**
LVDS macro stop.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Macro Stop OK
@retval		D_IM_PRO_NG					: Macro Stop NG
*/
INT32 impro_senlvds_stop( EimproLvdsCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	// frame stop
	ioPro.sen.lvds[ch].lvdstrg.bit.lvdstrg = D_IM_PRO_TRG_FRAME_STOP;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	im_pro_common_fig_im_pro_sen_set_stop_status(D_IM_SEN_STATUS_LVDS0, ch);

	return D_DDIM_OK;
}

/**
The control parameter of LVDS is set.
@param[in]	ch : Channel No.
@param[in]	lvdsCtrl : LVDS control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_senlvds_ctrl( EimproLvdsCh ch, TimproLvdsCtrl* lvdsCtrl )
{
#ifdef CO_PARAM_CHECK
	if (lvdsCtrl == NULL){
		Ddim_Assertion(("I:impro_senlvds_ctrl error. lvdsCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( lvdsCtrl->outputChNo > ImproSenlvds_E_IM_PRO_LVDS_OUT_1CH ) {
		Ddim_Print(("I:impro_senlvds_ctrl. outputChNo error.(%u) \n", lvdsCtrl->outputChNo));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.lvds[ch].lvdsctl1.bit.lmd	= lvdsCtrl->transMode;
	ioPro.sen.lvds[ch].lvdsctl1.bit.lch	= lvdsCtrl->outputChNo;
	ioPro.sen.lvds[ch].lvdsctl1.bit.lane	= lvdsCtrl->lane;
	ioPro.sen.lvds[ch].lvdsctl1.bit.ldw	= lvdsCtrl->dataBitWidth;
	ioPro.sen.lvds[ch].lvdsctl1.bit.lsft	= lvdsCtrl->lsft;
	ioPro.sen.lvds[ch].lvdsctl1.bit.synt	= lvdsCtrl->syncType;
	ioPro.sen.lvds[ch].lvdsctl1.bit.szen	= lvdsCtrl->dataInputType;
	ioPro.sen.lvds[ch].lvdsctl1.bit.syn16	= lvdsCtrl->syncBitFix;

	ioPro.sen.lvds[ch].lvdsctl2.bit.divot	= lvdsCtrl->divideOutput;
	ioPro.sen.lvds[ch].lvdsctl2.bit.lmir	= lvdsCtrl->invertedOutput;
	ioPro.sen.lvds[ch].lvdsctl2.bit.dolmd	= lvdsCtrl->outputMode;
	ioPro.sen.lvds[ch].lvdsctl2.bit.lmsk	= lvdsCtrl->laneMask;

	ioPro.sen.lvds[ch].LVDSCLKS.bit.clks0	= lvdsCtrl->clockSelectSp0;
	ioPro.sen.lvds[ch].LVDSCLKS.bit.clks1	= lvdsCtrl->clockSelectSp1;
	ioPro.sen.lvds[ch].LVDSCLKS.bit.clks2	= lvdsCtrl->clockSelectSp2;
	ioPro.sen.lvds[ch].LVDSCLKS.bit.clks3	= lvdsCtrl->clockSelectSp3;
	ioPro.sen.lvds[ch].LVDSCLKS.bit.clks4	= lvdsCtrl->clockSelectSp4;
	ioPro.sen.lvds[ch].LVDSCLKS.bit.clks5	= lvdsCtrl->clockSelectSp5;
	ioPro.sen.lvds[ch].LVDSCLKS.bit.clks6	= lvdsCtrl->clockSelectSp6;
	ioPro.sen.lvds[ch].LVDSCLKS.bit.clks7	= lvdsCtrl->clockSelectSp7;

	ioPro.sen.lvds[ch].LVDSDATS.bit.dats00	= lvdsCtrl->clockSelectSp00;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats01	= lvdsCtrl->clockSelectSp01;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats10	= lvdsCtrl->clockSelectSp10;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats11	= lvdsCtrl->clockSelectSp11;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats20	= lvdsCtrl->clockSelectSp20;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats21	= lvdsCtrl->clockSelectSp21;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats30	= lvdsCtrl->clockSelectSp30;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats31	= lvdsCtrl->clockSelectSp31;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats40	= lvdsCtrl->clockSelectSp40;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats41	= lvdsCtrl->clockSelectSp41;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats50	= lvdsCtrl->clockSelectSp50;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats51	= lvdsCtrl->clockSelectSp51;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats60	= lvdsCtrl->clockSelectSp60;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats61	= lvdsCtrl->clockSelectSp61;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats71	= lvdsCtrl->clockSelectSp70;
	ioPro.sen.lvds[ch].LVDSDATS.bit.dats70	= lvdsCtrl->clockSelectSp71;
	ioPro.sen.lvds[ch].SYNCSEL.bit.syncsel	= lvdsCtrl->laneSelect;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
LVDS Input starting position setup .
@param[in]	ch : Channel No.
@param[in]	input_pos	: LVDS input position<br>
						 value range:[0 - 12288pixel](Multiples of 4)<br>
						 target registor:@@LHSADD
@param[in]	inputSize : LVDS input size<br>
						 value range:[4 - ](Multiples of 4)<br>
						 maximum size that can be set by each SENCORE block set by SENTOP.SENRAMSW.<br>
						 target registor:@@LHSIZE
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
@remarks	Only in the case of @@SZEN = 1 (see impro_senlvds_ctrl), the value set up by this API is effective.
*/
INT32 impro_senlvds_set_area( EimproLvdsCh ch, USHORT input_pos, USHORT inputSize )
{
#ifdef CO_PARAM_CHECK
	if( inputSize < ImproSenlvds_D_IM_PRO_LVDS_LHSIZE_MIN ) {
		Ddim_Assertion(("I:impro_senlvds_set_area. input param:[inputSize] value over!! >= %d (%d)\n",
									ImproSenlvds_D_IM_PRO_LVDS_LHSIZE_MIN ,inputSize ));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( inputSize > S_GIM_PRO_MAXIMUM_SIZE_LVDS
			[ioPro.sen.sentop.sentopctl1.sentopctl13.bit.SENRAMSW][ch] ) {
		Ddim_Assertion(("I:impro_senlvds_set_area. input param:[inputSize] value over!! <= %d (%d)\n",
				S_GIM_PRO_MAXIMUM_SIZE_LVDS[ioPro.sen.sentop.sentopctl1
				  .sentopctl13.bit.SENRAMSW][ch] ,inputSize ));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else {
		// DO NOTHING
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.lvds[ch].lhsadd.bit.lhsadd	= input_pos;
	ioPro.sen.lvds[ch].lhsize.bit.lhsize	= inputSize;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
LVDS output data rearrangement setup.
@param[in]	ch : Channel No.
@param[in]	lvdsOrder : LVDS pixel order information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_senlvds_set_pixel_order( EimproLvdsCh ch, TimproLvdsPixelOrder* lvdsOrder )
{
#ifdef CO_PARAM_CHECK
	if (lvdsOrder == NULL){
		Ddim_Assertion(("I:impro_senlvds_set_pixel_order error. lvdsOrder=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.lvds[ch].lpdchg.bit.sela	= lvdsOrder->ptnA;
	ioPro.sen.lvds[ch].lpdchg.bit.selb	= lvdsOrder->ptnB;
	ioPro.sen.lvds[ch].lpdchg.bit.selc	= lvdsOrder->ptnC;
	ioPro.sen.lvds[ch].lpdchg.bit.seld	= lvdsOrder->ptnD;
	ioPro.sen.lvds[ch].lpdchg.bit.sele	= lvdsOrder->ptnE;
	ioPro.sen.lvds[ch].lpdchg.bit.self	= lvdsOrder->ptnF;
	ioPro.sen.lvds[ch].lpdchg.bit.selg	= lvdsOrder->ptnG;
	ioPro.sen.lvds[ch].lpdchg.bit.selh	= lvdsOrder->ptnH;
	ioPro.sen.lvds[ch].lpdchg.bit.seli	= lvdsOrder->ptnI;
	ioPro.sen.lvds[ch].lpdchg.bit.selj	= lvdsOrder->ptnJ;
	ioPro.sen.lvds[ch].lpdchg.bit.selk	= lvdsOrder->ptnK;
	ioPro.sen.lvds[ch].lpdchg.bit.sell	= lvdsOrder->ptnP;
	ioPro.sen.lvds[ch].lpdchg.bit.selm	= lvdsOrder->ptnM;
	ioPro.sen.lvds[ch].lpdchg.bit.seln	= lvdsOrder->ptnN;
	ioPro.sen.lvds[ch].lpdchg.bit.selo	= lvdsOrder->ptnO;
	ioPro.sen.lvds[ch].lpdchg.bit.selp	= lvdsOrder->ptnP;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
The sync code parameter of LVDS is set.
@param[in]	ch : Channel No.
@param[in]	syncCode : LVDS sync code information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_senlvds_set_sync_code( EimproLvdsCh ch, TimproLvdsSyncCodeCtrl* syncCode )
{
#ifdef CO_PARAM_CHECK
	if (syncCode == NULL){
		Ddim_Assertion(("I:Im_PRO_Set_SyncCode. syncCode=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.lvds[ch].sav0.sav01.bit.sav00 = syncCode->syncCode[0].sav[0];
	ioPro.sen.lvds[ch].sav0.sav01.bit.sav01 = syncCode->syncCode[0].sav[1];
	ioPro.sen.lvds[ch].sav0.sav02.bit.sav02 = syncCode->syncCode[0].sav[2];
	ioPro.sen.lvds[ch].sav0.sav02.bit.sav03 = syncCode->syncCode[0].sav[3];

	ioPro.sen.lvds[ch].eav0.eav01.bit.eav00 = syncCode->syncCode[0].eav[0];
	ioPro.sen.lvds[ch].eav0.eav01.bit.eav01 = syncCode->syncCode[0].eav[1];
	ioPro.sen.lvds[ch].eav0.eav02.bit.eav02 = syncCode->syncCode[0].eav[2];
	ioPro.sen.lvds[ch].eav0.eav02.bit.eav03 = syncCode->syncCode[0].eav[3];

	ioPro.sen.lvds[ch].sab0.sab01.bit.sab00 = syncCode->syncCode[0].sab[0];
	ioPro.sen.lvds[ch].sab0.sab01.bit.sab01 = syncCode->syncCode[0].sab[1];
	ioPro.sen.lvds[ch].sab0.sab02.bit.sab02 = syncCode->syncCode[0].sab[2];
	ioPro.sen.lvds[ch].sab0.sab02.bit.sab03 = syncCode->syncCode[0].sab[3];

	ioPro.sen.lvds[ch].eab0.eab01.bit.eab00 = syncCode->syncCode[0].eab[0];
	ioPro.sen.lvds[ch].eab0.eab01.bit.eab01 = syncCode->syncCode[0].eab[1];
	ioPro.sen.lvds[ch].eab0.eab02.bit.eab02 = syncCode->syncCode[0].eab[2];
	ioPro.sen.lvds[ch].eab0.eab02.bit.eab03 = syncCode->syncCode[0].eab[3];


	ioPro.sen.lvds[ch].sav1.sav11.bit.sav10 = syncCode->syncCode[1].sav[0];
	ioPro.sen.lvds[ch].sav1.sav11.bit.sav11 = syncCode->syncCode[1].sav[1];
	ioPro.sen.lvds[ch].sav1.sav12.bit.sav12 = syncCode->syncCode[1].sav[2];
	ioPro.sen.lvds[ch].sav1.sav12.bit.sav13 = syncCode->syncCode[1].sav[3];

	ioPro.sen.lvds[ch].eav1.eav11.bit.eav10 = syncCode->syncCode[1].eav[0];
	ioPro.sen.lvds[ch].eav1.eav11.bit.eav11 = syncCode->syncCode[1].eav[1];
	ioPro.sen.lvds[ch].eav1.eav12.bit.eav12 = syncCode->syncCode[1].eav[2];
	ioPro.sen.lvds[ch].eav1.eav12.bit.eav13 = syncCode->syncCode[1].eav[3];

	ioPro.sen.lvds[ch].sab1.sab11.bit.sab10 = syncCode->syncCode[1].sab[0];
	ioPro.sen.lvds[ch].sab1.sab11.bit.sab11 = syncCode->syncCode[1].sab[1];
	ioPro.sen.lvds[ch].sab1.sab12.bit.sab12 = syncCode->syncCode[1].sab[2];
	ioPro.sen.lvds[ch].sab1.sab12.bit.sab13 = syncCode->syncCode[1].sab[3];

	ioPro.sen.lvds[ch].eab1.eab11.bit.eab10 = syncCode->syncCode[1].eab[0];
	ioPro.sen.lvds[ch].eab1.eab11.bit.eab11 = syncCode->syncCode[1].eab[1];
	ioPro.sen.lvds[ch].eab1.eab12.bit.eab12 = syncCode->syncCode[1].eab[2];
	ioPro.sen.lvds[ch].eab1.eab12.bit.eab13 = syncCode->syncCode[1].eab[3];

	ioPro.sen.lvds[ch].sav2.sav21.bit.sav20 = syncCode->syncCode[2].sav[0];
	ioPro.sen.lvds[ch].sav2.sav21.bit.sav21 = syncCode->syncCode[2].sav[1];
	ioPro.sen.lvds[ch].sav2.sav22.bit.sav22 = syncCode->syncCode[2].sav[2];
	ioPro.sen.lvds[ch].sav2.sav22.bit.sav23 = syncCode->syncCode[2].sav[3];

	ioPro.sen.lvds[ch].eav2.eav21.bit.eav20 = syncCode->syncCode[2].eav[0];
	ioPro.sen.lvds[ch].eav2.eav21.bit.eav21 = syncCode->syncCode[2].eav[1];
	ioPro.sen.lvds[ch].eav2.eav22.bit.eav22 = syncCode->syncCode[2].eav[2];
	ioPro.sen.lvds[ch].eav2.eav22.bit.eav23 = syncCode->syncCode[2].eav[3];

	ioPro.sen.lvds[ch].sab2.sab21.bit.sab20 = syncCode->syncCode[2].sab[0];
	ioPro.sen.lvds[ch].sab2.sab21.bit.sab21 = syncCode->syncCode[2].sab[1];
	ioPro.sen.lvds[ch].sab2.sab22.bit.sab22 = syncCode->syncCode[2].sab[2];
	ioPro.sen.lvds[ch].sab2.sab22.bit.sab23 = syncCode->syncCode[2].sab[3];

	ioPro.sen.lvds[ch].eab2.eab21.bit.eab20 = syncCode->syncCode[2].eab[0];
	ioPro.sen.lvds[ch].eab2.eab21.bit.eab21 = syncCode->syncCode[2].eab[1];
	ioPro.sen.lvds[ch].eab2.eab22.bit.eab22 = syncCode->syncCode[2].eab[2];
	ioPro.sen.lvds[ch].eab2.eab22.bit.eab23 = syncCode->syncCode[2].eab[3];
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
LVDS sync code Mask setup.
@param[in]	ch : Channel No.
@param[in]	syncMask : LVDS sync mask information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_senlvds_set_sync_mask( EimproLvdsCh ch, TimproLvdsSyncMaskCtrl* syncMask )
{
#ifdef CO_PARAM_CHECK
	if (syncMask == NULL){
		Ddim_Assertion(("I:Im_PRO_Set_SyncMask. syncMask=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.lvds[ch].msav0.msav01.bit.msav00 = syncMask->syncMask[0].msav[0];
	ioPro.sen.lvds[ch].msav0.msav01.bit.msav01 = syncMask->syncMask[0].msav[1];
	ioPro.sen.lvds[ch].msav0.msav02.bit.msav02 = syncMask->syncMask[0].msav[2];
	ioPro.sen.lvds[ch].msav0.msav02.bit.msav03 = syncMask->syncMask[0].msav[3];

	ioPro.sen.lvds[ch].meav0.meav01.bit.meav00 = syncMask->syncMask[0].meav[0];
	ioPro.sen.lvds[ch].meav0.meav01.bit.meav01 = syncMask->syncMask[0].meav[1];
	ioPro.sen.lvds[ch].meav0.meav02.bit.meav02 = syncMask->syncMask[0].meav[2];
	ioPro.sen.lvds[ch].meav0.meav02.bit.meav03 = syncMask->syncMask[0].meav[3];

	ioPro.sen.lvds[ch].msab0.msab01.bit.msab00 = syncMask->syncMask[0].msab[0];
	ioPro.sen.lvds[ch].msab0.msab01.bit.msab01 = syncMask->syncMask[0].msab[1];
	ioPro.sen.lvds[ch].msab0.msab02.bit.msab02 = syncMask->syncMask[0].msab[2];
	ioPro.sen.lvds[ch].msab0.msab02.bit.msab03 = syncMask->syncMask[0].msab[3];

	ioPro.sen.lvds[ch].meab0.meab01.bit.meab00 = syncMask->syncMask[0].meab[0];
	ioPro.sen.lvds[ch].meab0.meab01.bit.meab01 = syncMask->syncMask[0].meab[1];
	ioPro.sen.lvds[ch].meab0.meab02.bit.meab02 = syncMask->syncMask[0].meab[2];
	ioPro.sen.lvds[ch].meab0.meab02.bit.meab03 = syncMask->syncMask[0].meab[3];

	ioPro.sen.lvds[ch].msav1.msav11.bit.msav10 = syncMask->syncMask[1].msav[0];
	ioPro.sen.lvds[ch].msav1.msav11.bit.msav11 = syncMask->syncMask[1].msav[1];
	ioPro.sen.lvds[ch].msav1.msav12.bit.msav12 = syncMask->syncMask[1].msav[2];
	ioPro.sen.lvds[ch].msav1.msav12.bit.msav13 = syncMask->syncMask[1].msav[3];

	ioPro.sen.lvds[ch].meav1.meav11.bit.meav10 = syncMask->syncMask[1].meav[0];
	ioPro.sen.lvds[ch].meav1.meav11.bit.meav11 = syncMask->syncMask[1].meav[1];
	ioPro.sen.lvds[ch].meav1.meav12.bit.meav12 = syncMask->syncMask[1].meav[2];
	ioPro.sen.lvds[ch].meav1.meav12.bit.meav13 = syncMask->syncMask[1].meav[3];

	ioPro.sen.lvds[ch].msab1.msab11.bit.msab10 = syncMask->syncMask[1].msab[0];
	ioPro.sen.lvds[ch].msab1.msab11.bit.msab11 = syncMask->syncMask[1].msab[1];
	ioPro.sen.lvds[ch].msab1.msab12.bit.msab12 = syncMask->syncMask[1].msab[2];
	ioPro.sen.lvds[ch].msab1.msab12.bit.msab13 = syncMask->syncMask[1].msab[3];

	ioPro.sen.lvds[ch].meab1.meab11.bit.meab10 = syncMask->syncMask[1].meab[0];
	ioPro.sen.lvds[ch].meab1.meab11.bit.meab11 = syncMask->syncMask[1].meab[1];
	ioPro.sen.lvds[ch].meab1.meab12.bit.meab12 = syncMask->syncMask[1].meab[2];
	ioPro.sen.lvds[ch].meab1.meab12.bit.meab13 = syncMask->syncMask[1].meab[3];

	ioPro.sen.lvds[ch].msav2.msav21.bit.msav20 = syncMask->syncMask[2].msav[0];
	ioPro.sen.lvds[ch].msav2.msav21.bit.msav21 = syncMask->syncMask[2].msav[1];
	ioPro.sen.lvds[ch].msav2.msav22.bit.msav22 = syncMask->syncMask[2].msav[2];
	ioPro.sen.lvds[ch].msav2.msav22.bit.msav23 = syncMask->syncMask[2].msav[3];

	ioPro.sen.lvds[ch].meav2.meav21.bit.meav20 = syncMask->syncMask[2].meav[0];
	ioPro.sen.lvds[ch].meav2.meav21.bit.meav21 = syncMask->syncMask[2].meav[1];
	ioPro.sen.lvds[ch].meav2.meav22.bit.meav22 = syncMask->syncMask[2].meav[2];
	ioPro.sen.lvds[ch].meav2.meav22.bit.meav23 = syncMask->syncMask[2].meav[3];

	ioPro.sen.lvds[ch].msab2.msab21.bit.msab20 = syncMask->syncMask[2].msab[0];
	ioPro.sen.lvds[ch].msab2.msab21.bit.msab21 = syncMask->syncMask[2].msab[1];
	ioPro.sen.lvds[ch].msab2.msab22.bit.msab22 = syncMask->syncMask[2].msab[2];
	ioPro.sen.lvds[ch].msab2.msab22.bit.msab23 = syncMask->syncMask[2].msab[3];

	ioPro.sen.lvds[ch].meab2.meab21.bit.meab20 = syncMask->syncMask[2].meab[0];
	ioPro.sen.lvds[ch].meab2.meab21.bit.meab21 = syncMask->syncMask[2].meab[1];
	ioPro.sen.lvds[ch].meab2.meab22.bit.meab22 = syncMask->syncMask[2].meab[2];
	ioPro.sen.lvds[ch].meab2.meab22.bit.meab23 = syncMask->syncMask[2].meab[3];
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
LVDS Input starting position setup .
@param[in]	ch : Channel No.
@param[in]	intAddr	: SOL/EOL interrupt address information.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_senlvds_set_int_adr( EimproLvdsCh ch, TimproLvdsIntAddrCtrl* intAddr )
{
#ifdef CO_PARAM_CHECK
	if (intAddr == NULL){
		Ddim_Assertion(("I:impro_senlvds_set_int_adr. intAddr=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	for( UCHAR loopcnt = 0; loopcnt <= ioPro.sen.lvds[ch].lvdsctl2.bit.dolmd; loopcnt++ ) {
		if( intAddr->intAddr[loopcnt].solAddr > ImproSenlvds_D_IM_PRO_LVDS_LVDSINTADR_MAX ) {
			Ddim_Assertion(("I:impro_senlvds_set_int_adr. input param:[solAddr%d] value over!! <= %d (%d)\n",
					loopcnt, ImproSenlvds_D_IM_PRO_LVDS_LVDSINTADR_MAX, intAddr->intAddr[loopcnt].solAddr ));
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
		if( intAddr->intAddr[loopcnt].eolAddr > ImproSenlvds_D_IM_PRO_LVDS_LVDSINTADR_MAX ) {
			Ddim_Assertion(("I:impro_senlvds_set_int_adr. input param:[eolAddr%d] value over!! <= %d (%d)\n",
					loopcnt, ImproSenlvds_D_IM_PRO_LVDS_LVDSINTADR_MAX, intAddr->intAddr[loopcnt].eolAddr ));
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.lvds[ch].lvdsintadr0.bit.solvadr0	= intAddr->intAddr[0].solAddr;
	ioPro.sen.lvds[ch].lvdsintadr0.bit.eolvadr0	= intAddr->intAddr[0].eolAddr;
	ioPro.sen.lvds[ch].lvdsintadr1.bit.solvadr1	= intAddr->intAddr[1].solAddr;
	ioPro.sen.lvds[ch].lvdsintadr1.bit.eolvadr1	= intAddr->intAddr[1].eolAddr;
	ioPro.sen.lvds[ch].lvdsintadr2.bit.solvadr2	= intAddr->intAddr[2].solAddr;
	ioPro.sen.lvds[ch].lvdsintadr2.bit.eolvadr2	= intAddr->intAddr[2].eolAddr;
	ioPro.sen.lvds[ch].LVDSINTSET0.word = 1;
	ioPro.sen.lvds[ch].LVDSINTSET1.word = 1;
	ioPro.sen.lvds[ch].LVDSINTSET2.word = 1;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of LVDS.
@param[in]	ch : Channel No.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_senlvds_set_paen( EimproLvdsCh ch, UCHAR paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( ioPro.sen.lvds[ch].lvdstrg.bit.lvdstrg != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:impro_senlvds_set_paen. macro has not stopped error.\n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.lvds[ch].lvdspaen.bit.paen	= paenTrg;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSenlvds类的一个实例
 *
 */
ImproSenlvds* 	impro_senlvds_new()
{
	ImproSenlvds* self = k_object_new_with_private(IMPRO_TYPE_SENLVDS,sizeof(ImproSenlvdsPrivate));
	ImproSenlvdsPrivate* priv = IMPRO_SENLVDS_GET_PRIVATE(self);
	
	e_warning_o(self," impro_senlvds_new \n");
	return self;
}
