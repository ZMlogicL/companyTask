/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :王睿
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#include "interruptfactor.h"

#include "jdspro.h"
#include "im_pro.h"
#include "im_pro_common.h"
#include "dd_top.h"

K_TYPE_DEFINE_WITH_PRIVATE(InterruptFactor, interrupt_factor);
#define INTERRUPT_FACTOR_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), InterruptFactorPrivate, INTERRUPT_TYPE_FACTOR))

struct _InterruptFactorPrivate
{
	int a;
};


static void interrupt_factor_constructor(InterruptFactor *self)
{
	InterruptFactorPrivate *priv = INTERRUPT_FACTOR_GET_PRIVATE(self);
	priv->a=0;
}

static void interrupt_factor_destructor(InterruptFactor *self)
{
	InterruptFactorPrivate *priv = INTERRUPT_FACTOR_GET_PRIVATE(self);
	priv->a=0;
}

typedef struct {
	ULONG	pwchIntf[D_IM_PRO_B2B_PWCH_CH_NUM];
	ULONG	prchIntf[D_IM_PRO_B2B_PRCH_CH_NUM];
} TimproB2bIntFactor;

static	volatile	TimproCallbackInfo	S_GIM_PRO_PWCH_CALLBACK_FUNC[D_IM_PRO_PIPE_NUM][E_IM_PRO_BLOCK_TYPE_MAX][E_IM_PRO_PWCH_MAX]			= {{{{0}}}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_PRCH_CALLBACK_FUNC[D_IM_PRO_PIPE_NUM][E_IM_PRO_BLOCK_TYPE_MAX][E_IM_PRO_PRCH_MAX]			= {{{{0}}}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_SENTOP_HD_CALLBACK_FUNC														= {0};
static	volatile	TimproCallbackInfo	S_GIM_PRO_SG_HD_CALLBACK_FUNC															= {0};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_PWCH_INT[3] = {
	{ D_IM_PRO_PWCHINTFLG_PWF,	D_IM_PRO_PWCHINTENB_PWE,		D_IM_PRO_PWCHINTFLG_PWF  },
	{ D_IM_PRO_PWCHINTFLG_PWEF,	D_IM_PRO_PWCHINTENB_PWEE,		D_IM_PRO_PWCHINTFLG_PWEF },
	{ D_IM_PRO_PWCHINTFLG_PWXF,	D_IM_PRO_PWCHINTENB_PWXE,		D_IM_PRO_PWCHINTFLG_PWXF },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_PRCH_INT[3] = {
	{ D_IM_PRO_PRCHINTENB_PRE,	D_IM_PRO_PRCHINTFLG_PRF,		D_IM_PRO_PRCHINTENB_PRE  },
	{ D_IM_PRO_PRCHINTENB_PREE,	D_IM_PRO_PRCHINTFLG_PREF,		D_IM_PRO_PRCHINTENB_PREE },
	{ D_IM_PRO_PRCHINTENB_PRXE,	D_IM_PRO_PRCHINTFLG_PRXF,		D_IM_PRO_PRCHINTENB_PRXE },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_HD[8] = {
	{ D_IM_PRO_INT_HDF00,	D_IM_PRO_INT_HDE00,	D_IM_PRO_INT_HDF00 },
	{ D_IM_PRO_INT_HDF01,	D_IM_PRO_INT_HDE01,	D_IM_PRO_INT_HDF01 },
	{ D_IM_PRO_INT_HDF10,	D_IM_PRO_INT_HDE10,	D_IM_PRO_INT_HDF10 },
	{ D_IM_PRO_INT_HDF11,	D_IM_PRO_INT_HDE11,	D_IM_PRO_INT_HDF11 },
	{ D_IM_PRO_INT_HDF20,	D_IM_PRO_INT_HDE20,	D_IM_PRO_INT_HDF20 },
	{ D_IM_PRO_INT_HDF21,	D_IM_PRO_INT_HDE21,	D_IM_PRO_INT_HDF21 },
	{ D_IM_PRO_INT_HDF30,	D_IM_PRO_INT_HDE30,	D_IM_PRO_INT_HDF30 },
	{ D_IM_PRO_INT_HDF31,	D_IM_PRO_INT_HDE31,	D_IM_PRO_INT_HDF31 },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_SG_HD[4] = {
	{ D_IM_PRO_INT_SGHDF0,	D_IM_PRO_INT_SGHDE0,	D_IM_PRO_INT_SGHDF0 },
	{ D_IM_PRO_INT_SGHDF1,	D_IM_PRO_INT_SGHDE1,	D_IM_PRO_INT_SGHDF1 },
	{ D_IM_PRO_INT_SGHDF2,	D_IM_PRO_INT_SGHDE2,	D_IM_PRO_INT_SGHDF2 },
	{ D_IM_PRO_INT_SGHDF3,	D_IM_PRO_INT_SGHDE3,	D_IM_PRO_INT_SGHDF3 },
};
/*----------------------------------------------------------------------*/
/*DECLS   																       */
/*----------------------------------------------------------------------*/
static VOID imProClearB2bIntFactorPrint( E_IM_PRO_UNIT_NUM unitNo, UCHAR status );
static VOID imProClearB2bIntFactor( E_IM_PRO_UNIT_NUM unitNo, TimproB2bIntFactor* intFactor );
static VOID imProCallbackB2bInt( E_IM_PRO_UNIT_NUM unitNo, TimproB2bIntFactor* intFactor );
static VOID imProPastopIntHandlerPrint( UCHAR status );
static VOID imProSenHdIntHandlerPrint( UCHAR status );
//static VOID interrupt_factor_pwch_clear_int_factor( TimproPwchIntInfo* pwch_info, ULONG* int_factor, UCHAR ch_cnt );
//static VOID interrupt_factor_prch_clear_int_factor( TimproPichIntInfo* pwch_info, ULONG* int_factor, UCHAR ch_cnt );

/*----------------------------------------------------------------------*/
/* IMPL														                   */
/*----------------------------------------------------------------------*/
static VOID imProClearB2bIntFactorPrint( E_IM_PRO_UNIT_NUM unitNo, UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	for(UCHAR i = 0; i < D_IM_PRO_B2B_PWCH_CH_NUM; i++) {
		Ddim_Print(( "imProClearB2bIntFactorPrint(%u) PWCH%u PWCHINTFLG(0x%08x) PWCHINTENB(0x%08x) (status:%u)\n", unitNo, i, IO_PRO.IMG_PIPE[unitNo].B2B.PWCH[i].PWCHINTFLG.word, IO_PRO.IMG_PIPE[unitNo].B2B.PWCH[i].PWCHINTENB.word, status ));
	}

	for(UCHAR i = 0; i < D_IM_PRO_B2B_PRCH_CH_NUM; i++) {
		Ddim_Print(( "imProClearB2bIntFactorPrint(%u) PRCH%u PRCHINTFLG(0x%08x) PRCHINTENB(0x%08x) (status:%u)\n", unitNo, i, IO_PRO.IMG_PIPE[unitNo].B2B.PRCH[i].PRCHINTFLG.word, IO_PRO.IMG_PIPE[unitNo].B2B.PRCH[i].PRCHINTENB.word, status ));
	}
#endif
}

static VOID imProClearB2bIntFactor( E_IM_PRO_UNIT_NUM unitNo, TimproB2bIntFactor* intFactor )
{
	TimproPwchIntInfo pwchInfo = {0};
	TimproPichIntInfo prchInfo = {0};

	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_B2B );
	Im_Pro_Dsb();
	imProClearB2bIntFactorPrint( unitNo, 0 );

	//************* PWCH *************//
	pwchInfo.unitNo		= unitNo;
	pwchInfo.blockType	= E_IM_PRO_BLOCK_TYPE_B2B;
	pwchInfo.regPtr		= IO_PRO.IMG_PIPE[unitNo].B2B.PWCH;
	interrupt_factor_pwch_clear_int_factor( interrupt_factor_new(),&pwchInfo, intFactor->pwchIntf, D_IM_PRO_B2B_PWCH_CH_NUM );

	//************* PRCH *************//
	prchInfo.unitNo		= unitNo;
	prchInfo.blockType	= E_IM_PRO_BLOCK_TYPE_B2B;
	prchInfo.regPtr		= IO_PRO.IMG_PIPE[unitNo].B2B.PRCH;
	interrupt_factor_prch_clear_int_factor( interrupt_factor_new(),&prchInfo, intFactor->prchIntf, D_IM_PRO_B2B_PRCH_CH_NUM );

	Im_Pro_Dsb();
	imProClearB2bIntFactorPrint( unitNo, 1 );
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_B2B );
}

static VOID imProCallbackB2bInt( E_IM_PRO_UNIT_NUM unitNo, TimproB2bIntFactor* intFactor )
{
	UINT32	chLoopcnt;

	/***************/
	/* PWCH        */
	/***************/
	for( chLoopcnt = 0; chLoopcnt < D_IM_PRO_B2B_PWCH_CH_NUM; chLoopcnt++ ) {
		interrupt_factor_pwch_callback_int_factor( interrupt_factor_new(),unitNo, E_IM_PRO_BLOCK_TYPE_B2B, (E_IM_PRO_PWCH)chLoopcnt, intFactor->pwchIntf );
	}

	/***************/
	/* PRCH        */
	/***************/
	for( chLoopcnt = 0; chLoopcnt < D_IM_PRO_B2B_PRCH_CH_NUM; chLoopcnt++ ) {
		interrupt_factor_prch_callback_int_factor( interrupt_factor_new(),unitNo, E_IM_PRO_BLOCK_TYPE_B2B, (E_IM_PRO_PRCH)chLoopcnt, intFactor->prchIntf );
	}
}

static VOID imProPastopIntHandlerPrint( UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "imProPastopIntHandlerPrint() PWCH PWCHINTFLG(0x%08x) PWCHINTENB(0x%08x) (status:%u)\n", IO_PRO.PAS.PWCH0.PWCHINTFLG.word, IO_PRO.PAS.PWCH0.PWCHINTENB.word, status ));
	Ddim_Print(( "imProPastopIntHandlerPrint() PWCH PWCHINTFLG(0x%08x) PWCHINTENB(0x%08x) (status:%u)\n", IO_PRO.PAS.PRCH0.PRCHINTFLG.word, IO_PRO.PAS.PRCH0.PRCHINTENB.word, status ));
#endif
}

static VOID imProSenHdIntHandlerPrint( UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "imProSenHdIntHandlerPrint() VHDINTFLG2 (0x%08x) VHDINTENB2 (0x%08x) (status:%u)\n", IO_PRO.SEN.SENTOP.VHDINTFLG.VHDINTFLG2.word, IO_PRO.SEN.SENTOP.VHDINTENB.VHDINTENB2.word, status ));
	Ddim_Print(( "imProSenHdIntHandlerPrint() SGVHDINTFLG(0x%08x) SGVHDINTENB(0x%08x) (status:%u)\n", IO_PRO.SEN.SENTOP.SGVHDINTFLG.word, IO_PRO.SEN.SENTOP.SGVHDINTENB.word, status ));
#endif
}
/*----------------------------------------------------------------------*/
/* PUBLIC                           											   */
/*----------------------------------------------------------------------*/
VOID interrupt_factor_pwch_clear_int_factor( InterruptFactor*self,TimproPwchIntInfo* pwchInfo, ULONG* intFactor, UCHAR chCnt ) //私有变公有
{
	UINT32	chLoopcnt;

	for( chLoopcnt = 0; chLoopcnt < chCnt; chLoopcnt++ ) {
		// Get interrupt flag
		intFactor[chLoopcnt]	= pwchInfo->regPtr[chLoopcnt].PWCHINTFLG.word & pwchInfo->regPtr[chLoopcnt].PWCHINTENB.word;
		// Clear interrupt flag
		pwchInfo->regPtr[chLoopcnt].PWCHINTFLG.word = intFactor[chLoopcnt];

		if( ( intFactor[chLoopcnt] & D_IM_PRO_PWCHINTFLG_PWF ) != 0 ) {
			switch( pwchInfo->blockType ) {
				case E_IM_PRO_BLOCK_TYPE_SRO:
					// for AFPB buffer update
					if( ( chLoopcnt == E_IM_PRO_PWCH_2 ) ||
						( chLoopcnt == E_IM_PRO_PWCH_3 ) ||
						( chLoopcnt == E_IM_PRO_PWCH_4 ) ||
						( chLoopcnt == E_IM_PRO_PWCH_5 ) ) {
						im_pro_comm_update_afpb_pwch_index(pwchInfo->blockType, ( chLoopcnt - E_IM_PRO_PWCH_2 ));
					}
					break;

				case E_IM_PRO_BLOCK_TYPE_STAT:
					// for AEAWB / FLCK buffer update
					im_pro_comm_update_stat_pwch_index(chLoopcnt);
					break;

				default:
					break;
			}
		}

		if( (intFactor[chLoopcnt] & D_IM_PRO_PWCHINTFLG_PWXF) != 0 ) {
			im_pro_comm_set_pwch_axi_response( pwchInfo->unitNo, pwchInfo->blockType, chLoopcnt, pwchInfo->regPtr[chLoopcnt].PWCHBRESP.bit.PWCHBRESP );
		}
	}
}

VOID interrupt_factor_pwch_callback_int_factor( InterruptFactor*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_PWCH ch, ULONG* intFactor )//私变公
{
	UINT32	loopcnt;
	ULONG	callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= 0,
		.block_type	= 0,
		.channel	= 0,
	};

	/*******************/
	/* PWCH Callback   */
	/*******************/
	callbackResult = 0;
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_PWCH_INT) / sizeof(S_GIM_PRO_INTTBL_PWCH_INT[0])); loopcnt++ ) {
		if( (intFactor[ch] & S_GIM_PRO_INTTBL_PWCH_INT[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_PWCH_INT[loopcnt].intFact;
		}
	}
	if (( S_GIM_PRO_PWCH_CALLBACK_FUNC[unitNo][blockType][ch].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= unitNo,
		cbId.block_type	= blockType,
		cbId.channel		= ch,
		S_GIM_PRO_PWCH_CALLBACK_FUNC[unitNo][blockType][ch].pCallback( &cbId, callbackResult, S_GIM_PRO_PWCH_CALLBACK_FUNC[unitNo][blockType][ch].userParam );
	}
	Im_Pro_Dsb();
}

VOID interrupt_factor_prch_callback_int_factor( InterruptFactor*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_PRCH ch, ULONG* intFactor )//私变公
{
	UINT32	loopcnt;
	ULONG	callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= 0,
		.block_type	= 0,
		.channel	= 0,
	};

	/*******************/
	/* PRCH Callback   */
	/*******************/
	callbackResult = 0;
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_PRCH_INT) / sizeof(S_GIM_PRO_INTTBL_PRCH_INT[0])); loopcnt++ ) {
		if( (intFactor[ch] & S_GIM_PRO_INTTBL_PRCH_INT[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_PRCH_INT[loopcnt].intFact;
		}
	}
	if (( S_GIM_PRO_PRCH_CALLBACK_FUNC[unitNo][blockType][ch].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= unitNo,
		cbId.block_type	= blockType,
		cbId.channel		= ch,
		S_GIM_PRO_PRCH_CALLBACK_FUNC[unitNo][blockType][ch].pCallback( &cbId, callbackResult, S_GIM_PRO_PRCH_CALLBACK_FUNC[unitNo][blockType][ch].userParam );
	}
	Im_Pro_Dsb();
}

VOID interrupt_factor_prch_clear_int_factor( InterruptFactor*self,TimproPichIntInfo* prchInfo, ULONG* intFactor, UCHAR chCnt )//私变公
{
	UINT32	chLoopcnt;

	for( chLoopcnt = 0; chLoopcnt < chCnt; chLoopcnt++ ) {
		// Get interrupt flag
		intFactor[chLoopcnt]	= prchInfo->regPtr[chLoopcnt].PRCHINTFLG.word & prchInfo->regPtr[chLoopcnt].PRCHINTENB.word;
		// Clear interrupt flag
		prchInfo->regPtr[chLoopcnt].PRCHINTFLG.word = intFactor[chLoopcnt];

		if( (intFactor[chLoopcnt] & D_IM_PRO_PRCHINTFLG_PRXF) != 0 ) {
			im_pro_comm_set_prch_axi_response( prchInfo->unitNo, prchInfo->blockType, chLoopcnt, prchInfo->regPtr[chLoopcnt].PRCHBRESP.bit.PRCHBRESP );
		}
	}
}

/**
CallBackFunction which Call to the interruption timing of PRch is registered
@param[in]	unitNo : Unit number.
@param[in]	blockType	 : PRO block type
@param[in]	ch : PRch channel
@param[in]	inthandler : PRch Interrupt callback function address
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_prch_set_int_handler( InterruptFactor*self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_PRCH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_PRCH_CALLBACK_FUNC[unitNo][blockType][ch].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_PRCH_CALLBACK_FUNC[unitNo][blockType][ch].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
CallBackFunction which Call to the interruption timing of PWch is registered
@param[in]	unitNo : Unit number.
@param[in]	blockType	 : PRO block type
@param[in]	ch			: PWch number
@param[in]	inthandler	: PWch Interrupt callback function address
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_pwch_set_int_handler( InterruptFactor*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_PWCH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_PWCH_CALLBACK_FUNC[unitNo][blockType][ch].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_PWCH_CALLBACK_FUNC[unitNo][blockType][ch].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
B2B Macro Pipe1 Int handler.
*/
VOID interrupt_factor_b2btop_pipe1_int_handler( VOID )
{
	TimproB2bIntFactor intFactor;

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_factor_b2btop_pipe1_int_handler begin\n" ));
#endif
	imProClearB2bIntFactor( E_IM_PRO_UNIT_NUM_1, &intFactor );
	imProCallbackB2bInt( E_IM_PRO_UNIT_NUM_1, &intFactor );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_factor_b2btop_pipe1_int_handler end\n" ));
#endif
}

/**
B2B Macro Pipe2 Int handler.
*/

VOID interrupt_factor_b2btop_pipe2_int_handler( VOID )
{
	TimproB2bIntFactor intFactor;

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_factor_b2btop_pipe2_int_handler begin\n" ));
#endif
	imProClearB2bIntFactor( E_IM_PRO_UNIT_NUM_2, &intFactor );
	imProCallbackB2bInt( E_IM_PRO_UNIT_NUM_2, &intFactor );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_factor_b2btop_pipe2_int_handler end\n" ));
#endif
}

/**
PAS Macro Int handler.
*/
VOID interrupt_factor_pastop_int_handler( VOID )
{
	ULONG			pwchIntf = 0;
	ULONG			prchIntf = 0;
	TimproPwchIntInfo pwchInfo = {0};
	TimproPichIntInfo prchInfo = {0};

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_factor_pastop_int_handler begin\n" ));
#endif
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	Im_Pro_Dsb();
	imProPastopIntHandlerPrint( 0 );

	/***********/
	/* PWCH    */
	/***********/
	// Get & clear interrupt flag
	pwchInfo.unitNo		= E_IM_PRO_UNIT_NUM_1;
	pwchInfo.blockType	= E_IM_PRO_BLOCK_TYPE_PAS;
	pwchInfo.regPtr		= &IO_PRO.PAS.PWCH0;
	interrupt_factor_pwch_clear_int_factor( interrupt_factor_new(),&pwchInfo, &pwchIntf, 1 );

	/***********/
	/* PRCH    */
	/***********/
	// Get & clear interrupt flag
	prchInfo.unitNo		= E_IM_PRO_UNIT_NUM_1;
	prchInfo.blockType	= E_IM_PRO_BLOCK_TYPE_PAS;
	prchInfo.regPtr		= &IO_PRO.PAS.PRCH0;
	interrupt_factor_prch_clear_int_factor( interrupt_factor_new(),&prchInfo, &prchIntf, 1 );

	Im_Pro_Dsb();
	imProPastopIntHandlerPrint( 1 );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	/*******************/
	/* PWCH Callback   */
	/*******************/
	interrupt_factor_pwch_callback_int_factor( interrupt_factor_new(),0, E_IM_PRO_BLOCK_TYPE_PAS, E_IM_PRO_PWCH_0, &pwchIntf );

	/*******************/
	/* PRCH Callback   */
	/*******************/
	interrupt_factor_prch_callback_int_factor( interrupt_factor_new(),0, E_IM_PRO_BLOCK_TYPE_PAS, E_IM_PRO_PRCH_0, &prchIntf );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_factor_pastop_int_handler end\n" ));
#endif
}

/**
SENTOP macro interrupt delay setting
@param[in]	blockNum : SENCORE block number(0:SENCORE0, 1:SENCORE1, 2:SENCORE2, 3:SENCORE3)
@param[in]	ch : interrupt ch(0-1)
@param[in]	delayCtrl : delay setting
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_sentop_set_vhd_delay( InterruptFactor*self,UCHAR blockNum, UCHAR ch, T_IM_PRO_INT_VHD_DELAY_CTRL* delayCtrl )
{
#ifdef CO_PARAM_CHECK
	if (blockNum >= D_IM_PRO_SEN_SENCORE_NUM){
		Ddim_Assertion(("I:interrupt_factor_sentop_set_vhd_delay. blockNum value error!! (blockNum:%d ch:%d)\n", blockNum, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (ch >= D_IM_PRO_SENTOP_VHD_CH_NUM){
		Ddim_Assertion(("I:interrupt_factor_sentop_set_vhd_delay. ch value error!! (blockNum:%d ch:%d)\n", blockNum, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl == NULL){
		Ddim_Assertion(("I:interrupt_factor_sentop_set_vhd_delay error. delayCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->hd_delay > D_IM_PRO_HMIHADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_sentop_set_vhd_delay hd_delay value error. delayCtrl->hd_delay=%u\n",delayCtrl->hd_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->vd_h_delay > D_IM_PRO_VMIHADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_sentop_set_vhd_delay vd_h_delay value error. delayCtrl->vd_h_delay=%u\n",delayCtrl->vd_h_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->vd_v_delay > D_IM_PRO_VMIVADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_sentop_set_vhd_delay vd_v_delay value error. delayCtrl->vd_v_delay=%u\n",delayCtrl->vd_v_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	switch( blockNum ) {
		case 0:
			if( ch == 0 ) {
				IO_PRO.SEN.SENTOP.HMIHADR.HMIHADR1.bit.HMIHADR00	= delayCtrl->hd_delay;
				IO_PRO.SEN.SENTOP.VMIHADR.VMIHADR1.bit.VMIHADR00	= delayCtrl->vd_h_delay;
				IO_PRO.SEN.SENTOP.VMIVADR.VMIVADR1.bit.VMIVADR00	= delayCtrl->vd_v_delay;
				IO_PRO.SEN.SENTOP.VHSET0.VHSET0_1.bit.VHSET00		= D_IM_PRO_FUNC_EN;
			}
			else {
				IO_PRO.SEN.SENTOP.HMIHADR.HMIHADR1.bit.HMIHADR01	= delayCtrl->hd_delay;
				IO_PRO.SEN.SENTOP.VMIHADR.VMIHADR1.bit.VMIHADR01	= delayCtrl->vd_h_delay;
				IO_PRO.SEN.SENTOP.VMIVADR.VMIVADR1.bit.VMIVADR01	= delayCtrl->vd_v_delay;
				IO_PRO.SEN.SENTOP.VHSET0.VHSET0_2.bit.VHSET01		= D_IM_PRO_FUNC_EN;
			}
			break;

		case 1:
			if( ch == 0 ) {
				IO_PRO.SEN.SENTOP.HMIHADR.HMIHADR2.bit.HMIHADR10	= delayCtrl->hd_delay;
				IO_PRO.SEN.SENTOP.VMIHADR.VMIHADR2.bit.VMIHADR10	= delayCtrl->vd_h_delay;
				IO_PRO.SEN.SENTOP.VMIVADR.VMIVADR2.bit.VMIVADR10	= delayCtrl->vd_v_delay;
				IO_PRO.SEN.SENTOP.VHSET1.VHSET1_1.bit.VHSET10		= D_IM_PRO_FUNC_EN;
			}
			else {
				IO_PRO.SEN.SENTOP.HMIHADR.HMIHADR2.bit.HMIHADR11	= delayCtrl->hd_delay;
				IO_PRO.SEN.SENTOP.VMIHADR.VMIHADR2.bit.VMIHADR11	= delayCtrl->vd_h_delay;
				IO_PRO.SEN.SENTOP.VMIVADR.VMIVADR2.bit.VMIVADR11	= delayCtrl->vd_v_delay;
				IO_PRO.SEN.SENTOP.VHSET1.VHSET1_2.bit.VHSET11		= D_IM_PRO_FUNC_EN;
			}
			break;

		case 2:
			if( ch == 0 ) {
				IO_PRO.SEN.SENTOP.HMIHADR.HMIHADR3.bit.HMIHADR20	= delayCtrl->hd_delay;
				IO_PRO.SEN.SENTOP.VMIHADR.VMIHADR3.bit.VMIHADR20	= delayCtrl->vd_h_delay;
				IO_PRO.SEN.SENTOP.VMIVADR.VMIVADR3.bit.VMIVADR20	= delayCtrl->vd_v_delay;
				IO_PRO.SEN.SENTOP.VHSET2.VHSET2_1.bit.VHSET20		= D_IM_PRO_FUNC_EN;
			}
			else {
				IO_PRO.SEN.SENTOP.HMIHADR.HMIHADR3.bit.HMIHADR21	= delayCtrl->hd_delay;
				IO_PRO.SEN.SENTOP.VMIHADR.VMIHADR3.bit.VMIHADR21	= delayCtrl->vd_h_delay;
				IO_PRO.SEN.SENTOP.VMIVADR.VMIVADR3.bit.VMIVADR21	= delayCtrl->vd_v_delay;
				IO_PRO.SEN.SENTOP.VHSET2.VHSET2_2.bit.VHSET21		= D_IM_PRO_FUNC_EN;
			}
			break;

		//case 3:
		default:
			if( ch == 0 ) {
				IO_PRO.SEN.SENTOP.HMIHADR.HMIHADR4.bit.HMIHADR30	= delayCtrl->hd_delay;
				IO_PRO.SEN.SENTOP.VMIHADR.VMIHADR4.bit.VMIHADR30	= delayCtrl->vd_h_delay;
				IO_PRO.SEN.SENTOP.VMIVADR.VMIVADR4.bit.VMIVADR30	= delayCtrl->vd_v_delay;
				IO_PRO.SEN.SENTOP.VHSET3.VHSET3_1.bit.VHSET30		= D_IM_PRO_FUNC_EN;
			}
			else {
				IO_PRO.SEN.SENTOP.HMIHADR.HMIHADR4.bit.HMIHADR31	= delayCtrl->hd_delay;
				IO_PRO.SEN.SENTOP.VMIHADR.VMIHADR4.bit.VMIHADR31	= delayCtrl->vd_h_delay;
				IO_PRO.SEN.SENTOP.VMIVADR.VMIVADR4.bit.VMIVADR31	= delayCtrl->vd_v_delay;
				IO_PRO.SEN.SENTOP.VHSET3.VHSET3_2.bit.VHSET31		= D_IM_PRO_FUNC_EN;
			}
			break;
	}
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
SENTOP macro GYRO interrupt delay setting
@param[in]	blockNum : SENCORE block number(0:SENCORE0, 1:SENCORE1, 2:SENCORE2, 3:SENCORE3)
@param[in]	ch : channel(0:HD/VD0, 1:HD/VD1, 2:HD/VD2, 3:HD/VD3)
@param[in]	delayCtrl : delay setting
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_sentop_set_gyro_int_delay( InterruptFactor*self,UCHAR blockNum, T_IM_PRO_INT_VHD_DELAY_CTRL* delayCtrl )
{
#ifdef CO_PARAM_CHECK
	if (blockNum >= D_IM_PRO_SEN_SENCORE_NUM){
		Ddim_Assertion(("I:interrupt_factor_sentop_set_gyro_int_delay. blockNum value error!! (blockNum:%d)\n", blockNum));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl == NULL){
		Ddim_Assertion(("I:interrupt_factor_sentop_set_gyro_int_delay error. delayCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->hd_delay > D_IM_PRO_HMIHADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_sentop_set_gyro_int_delay hd_delay value error. delayCtrl->hd_delay=%u\n",delayCtrl->hd_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->vd_h_delay > D_IM_PRO_VMIHADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_sentop_set_gyro_int_delay vd_h_delay value error. delayCtrl->vd_h_delay=%u\n",delayCtrl->vd_h_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->vd_v_delay > D_IM_PRO_VMIVADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_sentop_set_gyro_int_delay vd_v_delay value error. delayCtrl->vd_v_delay=%u\n",delayCtrl->vd_v_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	switch( blockNum ) {
		case 0:
			IO_PRO.SEN.SENTOP.GHADR.GHADR1.bit.GHADR0	= delayCtrl->hd_delay;
			IO_PRO.SEN.SENTOP.GVADR.GVADR1.bit.GVADR0	= delayCtrl->vd_v_delay;
			IO_PRO.SEN.SENTOP.GSET0.bit.GSET0			= D_IM_PRO_FUNC_EN;
			break;

		case 1:
			IO_PRO.SEN.SENTOP.GHADR.GHADR1.bit.GHADR1	= delayCtrl->hd_delay;
			IO_PRO.SEN.SENTOP.GVADR.GVADR1.bit.GVADR1	= delayCtrl->vd_v_delay;
			IO_PRO.SEN.SENTOP.GSET1.bit.GSET1			= D_IM_PRO_FUNC_EN;
			break;

		case 2:
			IO_PRO.SEN.SENTOP.GHADR.GHADR2.bit.GHADR2	= delayCtrl->hd_delay;
			IO_PRO.SEN.SENTOP.GVADR.GVADR2.bit.GVADR2	= delayCtrl->vd_v_delay;
			IO_PRO.SEN.SENTOP.GSET2.bit.GSET2			= D_IM_PRO_FUNC_EN;
			break;

		//case 3:
		default:
			IO_PRO.SEN.SENTOP.GHADR.GHADR2.bit.GHADR3	= delayCtrl->hd_delay;
			IO_PRO.SEN.SENTOP.GVADR.GVADR2.bit.GVADR3	= delayCtrl->vd_v_delay;
			IO_PRO.SEN.SENTOP.GSET3.bit.GSET3			= D_IM_PRO_FUNC_EN;
			break;
	}
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
SROTOP macro interrupt delay setting
@param[in]	unitNo : Unit number.
@param[in]	ch : channel(0:HD/VD0, 1:HD/VD1)
@param[in]	delayCtrl : delay setting
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_srotop_set_vhd_delay( InterruptFactor*self,
		E_IM_PRO_UNIT_NUM unitNo, UCHAR ch, T_IM_PRO_INT_VHD_DELAY_CTRL* delayCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_PRO_SROTOP_VHD_CH_NUM){
		Ddim_Assertion(("I:interrupt_factor_srotop_set_vhd_delay. ch value error!! (unitNo:%d ch:%d)\n", unitNo, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl == NULL){
		Ddim_Assertion(("I:interrupt_factor_srotop_set_vhd_delay error. delayCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->hd_delay > D_IM_PRO_HMIHADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_srotop_set_vhd_delay hd_delay value error. delayCtrl->hd_delay=%u\n",delayCtrl->hd_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->vd_h_delay > D_IM_PRO_VMIHADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_srotop_set_vhd_delay vd_h_delay value error. delayCtrl->vd_h_delay=%u\n",delayCtrl->vd_h_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->vd_v_delay > D_IM_PRO_VMIVADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_srotop_set_vhd_delay vd_v_delay value error. delayCtrl->vd_v_delay=%u\n",delayCtrl->vd_v_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	if( ch == 0 ) {
		IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.HMIHADR.bit.HMIHADR0	= delayCtrl->hd_delay;
		IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VMIHADR.bit.VMIHADR0	= delayCtrl->vd_h_delay;
		IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VMIVADR.bit.VMIVADR0	= delayCtrl->vd_v_delay;
		IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHSET.bit.VHSET0		= D_IM_PRO_FUNC_EN;
	}
	else {
		IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.HMIHADR.bit.HMIHADR1	= delayCtrl->hd_delay;
		IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VMIHADR.bit.VMIHADR1	= delayCtrl->vd_h_delay;
		IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VMIVADR.bit.VMIVADR1	= delayCtrl->vd_v_delay;
		IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHSET.bit.VHSET1		= D_IM_PRO_FUNC_EN;
	}
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
STATTOP Interrupt setting
@param[in]	intCtrl : STATTOP interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_factor_stattop_interrupt_ctrl( InterruptFactor*self,T_IM_PRO_INT_STATTOP_CTRL* intCtrl )
{
#ifdef CO_PARAM_CHECK
	if (intCtrl == NULL){
		Ddim_Assertion(("I:interrupt_factor_stattop_interrupt_ctrl error. intCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );
	IO_PRO.STAT.STATTOP.INTCTL.bit.INTMD	= intCtrl->int_mode;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );

	return D_DDIM_OK;
}

/**
B2BTOP macro interrupt delay setting
@param[in]	unitNo : Unit number.
@param[in]	ch : channel(0:HD/VD0, 1:HD/VD1)
@param[in]	delayCtrl : delay setting
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_b2btop_set_vhd_delay( InterruptFactor*self,
		E_IM_PRO_UNIT_NUM unitNo, UCHAR ch, T_IM_PRO_INT_VHD_DELAY_CTRL* delayCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_PRO_B2BTOP_VHD_CH_NUM){
		Ddim_Assertion(("I:interrupt_factor_b2btop_set_vhd_delay. ch value error!! (unitNo:%d ch:%d)\n", unitNo, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl == NULL){
		Ddim_Assertion(("I:interrupt_factor_b2btop_set_vhd_delay error. delayCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->hd_delay > D_IM_PRO_HMIHADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_b2btop_set_vhd_delay hd_delay value error. delayCtrl->hd_delay=%u\n",delayCtrl->hd_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->vd_h_delay > D_IM_PRO_VMIHADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_b2btop_set_vhd_delay vd_h_delay value error. delayCtrl->vd_h_delay=%u\n",delayCtrl->vd_h_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->vd_v_delay > D_IM_PRO_VMIVADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_b2btop_set_vhd_delay vd_v_delay value error. delayCtrl->vd_v_delay=%u\n",delayCtrl->vd_v_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_B2B );
	if( ch == 0 ) {
		IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.HMIHADR.bit.HMIHADR0	= delayCtrl->hd_delay;
		IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VMIHADR.bit.VMIHADR0	= delayCtrl->vd_h_delay;
		IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VMIVADR.bit.VMIVADR0	= delayCtrl->vd_v_delay;
		IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHSET.bit.VHSET0		= D_IM_PRO_FUNC_EN;
	}
	else {
		IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.HMIHADR.bit.HMIHADR1	= delayCtrl->hd_delay;
		IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VMIHADR.bit.VMIHADR1	= delayCtrl->vd_h_delay;
		IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VMIVADR.bit.VMIVADR1	= delayCtrl->vd_v_delay;
		IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHSET.bit.VHSET1		= D_IM_PRO_FUNC_EN;
	}
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_B2B );

	return D_DDIM_OK;
}

/**
PASTOP macro interrupt delay setting
@param[in]	ch : channel(0:HD/VD0, 1:HD/VD1)
@param[in]	delayCtrl : delay setting
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_pastop_set_vhd_delay( InterruptFactor*self,UCHAR ch, T_IM_PRO_INT_VHD_DELAY_CTRL* delayCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_PRO_PASTOP_VHD_CH_NUM){
		Ddim_Assertion(("I:interrupt_factor_pastop_set_vhd_delay. ch value error!! (ch:%d)\n", ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl == NULL){
		Ddim_Assertion(("I:interrupt_factor_pastop_set_vhd_delay error. delayCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->hd_delay > D_IM_PRO_HMIHADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_pastop_set_vhd_delay hd_delay value error. delayCtrl->hd_delay=%u\n",delayCtrl->hd_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->vd_h_delay > D_IM_PRO_VMIHADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_pastop_set_vhd_delay vd_h_delay value error. delayCtrl->vd_h_delay=%u\n",delayCtrl->vd_h_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (delayCtrl->vd_v_delay > D_IM_PRO_VMIVADR_MAX){
		Ddim_Assertion(("I:interrupt_factor_pastop_set_vhd_delay vd_v_delay value error. delayCtrl->vd_v_delay=%u\n",delayCtrl->vd_v_delay));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	if( ch == 0 ) {
		IO_PRO.PAS.PASTOP.HMIHADR.bit.HMIHADR0	= delayCtrl->hd_delay;
		IO_PRO.PAS.PASTOP.VMIHADR.bit.VMIHADR0	= delayCtrl->vd_h_delay;
		IO_PRO.PAS.PASTOP.VMIVADR.bit.VMIVADR0	= delayCtrl->vd_v_delay;
		IO_PRO.PAS.PASTOP.VHSET.bit.VHSET0		= D_IM_PRO_FUNC_EN;
	}
	else {
		IO_PRO.PAS.PASTOP.HMIHADR.bit.HMIHADR1	= delayCtrl->hd_delay;
		IO_PRO.PAS.PASTOP.VMIHADR.bit.VMIHADR1	= delayCtrl->vd_h_delay;
		IO_PRO.PAS.PASTOP.VMIVADR.bit.VMIVADR1	= delayCtrl->vd_v_delay;
		IO_PRO.PAS.PASTOP.VHSET.bit.VHSET1		= D_IM_PRO_FUNC_EN;
	}
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	return D_DDIM_OK;
}


/**
SEN block HD Int handler.
*/
VOID interrupt_factor_hd_int_handler( VOID )
{
	UINT32			loopcnt;
	ULONG			hdIntf;
	ULONG			sgHdIntf;
	ULONG			callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= E_IM_PRO_UNIT_NUM_1,
		.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
		.channel	= 0,
	};

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_factor_hd_int_handler begin\n" ));
#endif
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	Im_Pro_Dsb();
	imProSenHdIntHandlerPrint( 0 );

	// Get interrupt flag
	hdIntf		= IO_PRO.SEN.SENTOP.VHDINTFLG.VHDINTFLG2.word & IO_PRO.SEN.SENTOP.VHDINTENB.VHDINTENB2.word;
	sgHdIntf	= IO_PRO.SEN.SENTOP.SGVHDINTFLG.word & IO_PRO.SEN.SENTOP.SGVHDINTENB.word & D_IM_PRO_INT_SGHD_ALL;

	// Clear interrupt flag
	IO_PRO.SEN.SENTOP.VHDINTFLG.VHDINTFLG1.word	= hdIntf;
	IO_PRO.SEN.SENTOP.SGVHDINTFLG.word			= sgHdIntf;

	Im_Pro_Dsb();
	imProSenHdIntHandlerPrint( 1 );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	/***********/
	/* HD Edge */
	/***********/
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_HD) / sizeof(S_GIM_PRO_INTTBL_SEN_HD[0])); loopcnt++ ) {
		if( (hdIntf & S_GIM_PRO_INTTBL_SEN_HD[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_SEN_HD[loopcnt].intFact;

		}
	}
	// Callback
	if (( S_GIM_PRO_SENTOP_HD_CALLBACK_FUNC.pCallback != NULL ) && ( callbackResult != 0 )){
		S_GIM_PRO_SENTOP_HD_CALLBACK_FUNC.pCallback( &cbId, callbackResult, S_GIM_PRO_SENTOP_HD_CALLBACK_FUNC.userParam );
	}

	/***********/
	/* SG HD Edge */
	/***********/
	callbackResult = 0;
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_SG_HD) / sizeof(S_GIM_PRO_INTTBL_SEN_SG_HD[0])); loopcnt++ ) {
		if( (sgHdIntf & S_GIM_PRO_INTTBL_SEN_SG_HD[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_SEN_SG_HD[loopcnt].intFact;

		}
	}
	// Callback
	if (( S_GIM_PRO_SG_HD_CALLBACK_FUNC.pCallback != NULL ) && ( callbackResult != 0 )){
		S_GIM_PRO_SG_HD_CALLBACK_FUNC.pCallback( &cbId, callbackResult, S_GIM_PRO_SG_HD_CALLBACK_FUNC.userParam );
	}
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_factor_hd_int_handler end\n" ));
#endif
}

/**
SEN block HD Int handler setting.
@param[in]	inthandler : Interrupt handler address pointer
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_set_hd_int_handler( InterruptFactor*self,T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_SENTOP_HD_CALLBACK_FUNC.pCallback = callbackCfg->inthandler;
	S_GIM_PRO_SENTOP_HD_CALLBACK_FUNC.userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
SEN block SG HD Int handler setting.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_set_sg_hd_int_handler( InterruptFactor*self,T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_SG_HD_CALLBACK_FUNC.pCallback = callbackCfg->inthandler;
	S_GIM_PRO_SG_HD_CALLBACK_FUNC.userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

InterruptFactor *interrupt_factor_new(void)
{
	InterruptFactor* self = k_object_new_with_private(INTERRUPT_TYPE_FACTOR,sizeof(InterruptFactorPrivate));
	return self;
}
