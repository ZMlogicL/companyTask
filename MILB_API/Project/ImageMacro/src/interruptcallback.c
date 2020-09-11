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

#include "interruptcallback.h"
#include "interruptfactor.h"

#include "jdspro.h"
#include "im_pro.h"
#include "im_pro_common.h"
#include "dd_top.h"

K_TYPE_DEFINE_WITH_PRIVATE(InterruptCallback, interrupt_callback);
#define INTERRUPT_CALLBACK_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), InterruptCallbackPrivate, INTERRUPT_TYPE_CALLBACK))

struct _InterruptCallbackPrivate
{
	int a;
};


static void interrupt_callback_constructor(InterruptCallback *self)
{
	InterruptCallbackPrivate *priv = INTERRUPT_CALLBACK_GET_PRIVATE(self);
	priv->a=0;
}

static void interrupt_callback_destructor(InterruptCallback *self)
{
	InterruptCallbackPrivate *priv = INTERRUPT_CALLBACK_GET_PRIVATE(self);
	priv->a=0;
}

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
typedef struct {
	ULONG	pwchIntf[D_IM_PRO_SRO_PWCH_CH_NUM];
	ULONG	prchIntf[D_IM_PRO_SRO_PRCH_CH_NUM];
	ULONG	sdcIntf[D_IM_PRO_SRO_SDC_CH_NUM];
	ULONG	moniIntf;
} TinterruptcallbackSroIntFactor;

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static	volatile	TimproCallbackInfo	S_GIM_PRO_AEAWB_CALLBACK_FUNC[D_IM_PRO_STAT_AEAWB_CH_NUM]								= {{0}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_AF_CALLBACK_FUNC[D_IM_PRO_STAT_AF_CH_NUM]									= {{0}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_HIST_CALLBACK_FUNC[D_IM_PRO_STAT_HIST_CH_NUM]								= {{0}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_PAS_VD_CALLBACK_FUNC														= {0};
static	volatile	TimproCallbackInfo	S_GIM_PRO_PAS_HD_CALLBACK_FUNC														= {0};
static	volatile	TimproCallbackInfo	S_GIM_PRO_SDC_CALLBACK_FUNC[D_IM_PRO_PIPE_NUM][D_IM_PRO_SRO_SDC_CH_NUM]								= {{{0}}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_MONI_CALLBACK_FUNC[D_IM_PRO_PIPE_NUM][E_IM_PRO_BLOCK_TYPE_MAX][D_IM_PRO_SEN_MONI_CH_NUM]	= {{{{0}}}};//等着


static const TimproIntflgTbl S_GIM_PRO_INTTBL_STAT_AEAWB_INT[1] = {
	{ D_IM_PRO_LINEINTFLG_LINEF,	D_IM_PRO_LINEINTENB_LINEE,	D_IM_PRO_LINEINTFLG_LINEF },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_STAT_AF_INT[1] = {
	{ D_IM_PRO_AFINTFLG_AFF,		D_IM_PRO_AFINTENB_AFE,		D_IM_PRO_AFINTFLG_AFF },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_STAT_HIST_INT[1] = {
	{ D_IM_PRO_HISTINTFLG_HISTF,	D_IM_PRO_HISTINTENB_HISTE,	D_IM_PRO_HISTINTFLG_HISTF },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_PAS_VD[2] = {
	{ D_IM_PRO_PASTOP_INT_VDF0,	D_IM_PRO_PASTOP_INT_VDE0,		D_IM_PRO_PASTOP_INT_VDF0 },
	{ D_IM_PRO_PASTOP_INT_VDF1,	D_IM_PRO_PASTOP_INT_VDE1,		D_IM_PRO_PASTOP_INT_VDF1 },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_PAS_HD[2] = {
	{ D_IM_PRO_PASTOP_INT_HDF0,	D_IM_PRO_PASTOP_INT_HDE0,		D_IM_PRO_PASTOP_INT_HDF0 },
	{ D_IM_PRO_PASTOP_INT_HDF1,	D_IM_PRO_PASTOP_INT_HDE1,		D_IM_PRO_PASTOP_INT_HDF1 },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SRO_SDC_INT[1] = {
	{ D_IM_PRO_SDCINTFLG_SDCF,	D_IM_PRO_SDCINTENB_SDCE,		D_IM_PRO_SDCINTFLG_SDCF },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_MONI_INT[5] = {
	{ D_IM_PRO_MONIINTFLG_MONIHDF,		D_IM_PRO_MONIINTENB_MONIHDE,		D_IM_PRO_MONIINTFLG_MONIHDF		 },
	{ D_IM_PRO_MONIINTFLG_MONIEPFF,		D_IM_PRO_MONIINTENB_MONIEPFE,		D_IM_PRO_MONIINTFLG_MONIEPFF	 },
	{ D_IM_PRO_MONIINTFLG_MONIEPLF,		D_IM_PRO_MONIINTENB_MONIEPLE,		D_IM_PRO_MONIINTFLG_MONIEPLF	 },
	{ D_IM_PRO_MONIINTFLG_MONIBLLMINF,	D_IM_PRO_MONIINTENB_MONIBLLMINE,	D_IM_PRO_MONIINTFLG_MONIBLLMINF	 },
	{ D_IM_PRO_MONIINTFLG_MONIBLLMAXF,	D_IM_PRO_MONIINTENB_MONIBLLMAXE,	D_IM_PRO_MONIINTFLG_MONIBLLMAXF	 },
};               //等着

/*----------------------------------------------------------------------*/
/*DECLS   																       */
/*----------------------------------------------------------------------*/
static VOID imProCallbackSroInt( E_IM_PRO_UNIT_NUM unitNo, TinterruptcallbackSroIntFactor* intFactor );
static VOID imProClearSroIntFactorPrint( E_IM_PRO_UNIT_NUM unitNo, UCHAR status );
static VOID imProClearSroIntFactor( E_IM_PRO_UNIT_NUM unitNo, TinterruptcallbackSroIntFactor* intFactor );
static VOID imProStatIntHandlerPrint( UCHAR status );
static VOID imProPastopVdIntHandlerPrint( UCHAR status );
static VOID imProPastopHdIntHandlerPrint( UCHAR status );

/*----------------------------------------------------------------------*/
/* IMPL														                   */
/*----------------------------------------------------------------------*/
static VOID imProCallbackSroInt( E_IM_PRO_UNIT_NUM unitNo, TinterruptcallbackSroIntFactor* intFactor )
{
	UINT32	loopcnt;
	UINT32	chLoopcnt;
	ULONG	callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= 0,
		.block_type	= 0,
		.channel	= 0,
	};

	/***************/
	/* MONI        */
	/***************/
	callbackResult = 0;
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_MONI_INT) / sizeof(S_GIM_PRO_INTTBL_MONI_INT[0])); loopcnt++ ) {
		if( (intFactor->moniIntf & S_GIM_PRO_INTTBL_MONI_INT[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_MONI_INT[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_MONI_CALLBACK_FUNC[unitNo][E_IM_PRO_BLOCK_TYPE_SRO][E_IM_PRO_MONI_CH_0].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= unitNo,
		cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SRO,
		cbId.channel		= 0,
		S_GIM_PRO_MONI_CALLBACK_FUNC[unitNo][E_IM_PRO_BLOCK_TYPE_SRO][E_IM_PRO_MONI_CH_0].pCallback( &cbId, callbackResult, S_GIM_PRO_MONI_CALLBACK_FUNC[unitNo][E_IM_PRO_BLOCK_TYPE_SRO][E_IM_PRO_MONI_CH_0].userParam );
	}

	/***************/
	/* SDC         */
	/***************/
	for( chLoopcnt = 0; chLoopcnt < D_IM_PRO_SRO_SDC_CH_NUM; chLoopcnt++ ) {
		callbackResult = 0;
		for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SRO_SDC_INT) / sizeof(S_GIM_PRO_INTTBL_SRO_SDC_INT[0])); loopcnt++ ) {
			if( (intFactor->moniIntf & S_GIM_PRO_INTTBL_SRO_SDC_INT[loopcnt].flgBitmask) != 0 ) {
				callbackResult	|= S_GIM_PRO_INTTBL_SRO_SDC_INT[loopcnt].intFact;
			}
		}
		// Callback
		if (( S_GIM_PRO_SDC_CALLBACK_FUNC[unitNo][chLoopcnt].pCallback != NULL ) && ( callbackResult != 0 )){
			cbId.unit_no		= unitNo,
			cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SRO,
			cbId.channel		= chLoopcnt,
			S_GIM_PRO_SDC_CALLBACK_FUNC[unitNo][chLoopcnt].pCallback( &cbId, callbackResult, S_GIM_PRO_SDC_CALLBACK_FUNC[unitNo][chLoopcnt].userParam );
		}
	}

	/***************/
	/* PWCH        */
	/***************/
	for( chLoopcnt = 0; chLoopcnt < D_IM_PRO_SRO_PWCH_CH_NUM; chLoopcnt++ ) {
		interrupt_factor_pwch_callback_int_factor( interrupt_factor_new(),unitNo, E_IM_PRO_BLOCK_TYPE_SRO, (E_IM_PRO_PWCH)chLoopcnt, intFactor->pwchIntf );
	}

	/***************/
	/* PRCH        */
	/***************/
	for( chLoopcnt = 0; chLoopcnt < D_IM_PRO_SRO_PRCH_CH_NUM; chLoopcnt++ ) {
		interrupt_factor_prch_callback_int_factor( interrupt_factor_new(),unitNo, E_IM_PRO_BLOCK_TYPE_SRO, (E_IM_PRO_PRCH)chLoopcnt, intFactor->prchIntf );
	}
}

static VOID imProClearSroIntFactorPrint( E_IM_PRO_UNIT_NUM unitNo, UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "imProClearSroIntFactorPrint(%u) MONI MONIINTFLG(0x%08x) MONIINTENB(0x%08x) (status:%u)\n", unitNo, IO_PRO.IMG_PIPE[unitNo].SRO.MONI0.MONIINTFLG.word, IO_PRO.IMG_PIPE[unitNo].SRO.MONI0.MONIINTENB.word, status ));

	for(UCHAR i = 0; i < D_IM_PRO_SRO_SDC_CH_NUM; i++) {
		Ddim_Print(( "imProClearSroIntFactorPrint(%u) SDC%u SDCINTFLG(0x%08x) SDCINTENB(0x%08x) (status:%u)\n", unitNo, i, IO_PRO.IMG_PIPE[unitNo].SRO.SDC[i].SDCINTFLG.word, IO_PRO.IMG_PIPE[unitNo].SRO.SDC[i].SDCINTENB.word, status ));
	}

	for(UCHAR i = 0; i < D_IM_PRO_SRO_PWCH_CH_NUM; i++) {
		Ddim_Print(( "imProClearSroIntFactorPrint(%u) PWCH%u PWCHINTFLG(0x%08x) PWCHINTENB(0x%08x) (status:%u)\n", unitNo, i, IO_PRO.IMG_PIPE[unitNo].SRO.PWCH[i].PWCHINTFLG.word, IO_PRO.IMG_PIPE[unitNo].SRO.PWCH[i].PWCHINTENB.word, status ));
	}

	for(UCHAR i = 0; i < D_IM_PRO_SRO_PRCH_CH_NUM; i++) {
		Ddim_Print(( "imProClearSroIntFactorPrint(%u) PRCH%u PRCHINTFLG(0x%08x) PRCHINTENB(0x%08x) (status:%u)\n", unitNo, i, IO_PRO.IMG_PIPE[unitNo].SRO.PRCH[i].PRCHINTFLG.word, IO_PRO.IMG_PIPE[unitNo].SRO.PRCH[i].PRCHINTENB.word, status ));
	}
#endif
}

static VOID imProClearSroIntFactor( E_IM_PRO_UNIT_NUM unitNo, TinterruptcallbackSroIntFactor* intFactor )
{
	TimproPwchIntInfo pwchInfo = {0};
	TimproPichIntInfo prchInfo = {0};

	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	Im_Pro_Dsb();
	imProClearSroIntFactorPrint( unitNo, 0 );

	//************* MONI *************//
	// Get interrupt flag
	intFactor->moniIntf	= IO_PRO.IMG_PIPE[unitNo].SRO.MONI0.MONIINTFLG.word & IO_PRO.IMG_PIPE[unitNo].SRO.MONI0.MONIINTENB.word;
	// Clear interrupt flag
	IO_PRO.IMG_PIPE[unitNo].SRO.MONI0.MONIINTFLG.word = intFactor->moniIntf;

	if( intFactor->moniIntf != 0 ) {
		im_pro_comm_update_moni_result( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_MONI_CH_0 );
	}

	//************* SDC *************//
	// Get interrupt flag
	intFactor->sdcIntf[0]	= IO_PRO.IMG_PIPE[unitNo].SRO.SDC[0].SDCINTFLG.word & IO_PRO.IMG_PIPE[unitNo].SRO.SDC[0].SDCINTENB.word;
	intFactor->sdcIntf[1]	= IO_PRO.IMG_PIPE[unitNo].SRO.SDC[1].SDCINTFLG.word & IO_PRO.IMG_PIPE[unitNo].SRO.SDC[1].SDCINTENB.word;
	// Clear interrupt flag
	IO_PRO.IMG_PIPE[unitNo].SRO.SDC[0].SDCINTFLG.word = intFactor->sdcIntf[0];
	IO_PRO.IMG_PIPE[unitNo].SRO.SDC[1].SDCINTFLG.word = intFactor->sdcIntf[1];

	//************* PWCH *************//
	pwchInfo.unitNo		= unitNo;
	pwchInfo.blockType	= E_IM_PRO_BLOCK_TYPE_B2B;
	pwchInfo.regPtr		= IO_PRO.IMG_PIPE[unitNo].SRO.PWCH;
	interrupt_factor_pwch_clear_int_factor( interrupt_factor_new(),&pwchInfo, intFactor->pwchIntf, D_IM_PRO_SRO_PWCH_CH_NUM );

	//************* PRCH *************//
	prchInfo.unitNo		= unitNo;
	prchInfo.blockType	= E_IM_PRO_BLOCK_TYPE_B2B;
	prchInfo.regPtr		= IO_PRO.IMG_PIPE[unitNo].SRO.PRCH;
	interrupt_factor_prch_clear_int_factor( interrupt_factor_new(),&prchInfo, intFactor->prchIntf, D_IM_PRO_SRO_PRCH_CH_NUM );

	Im_Pro_Dsb();
	imProClearSroIntFactorPrint( unitNo, 1 );
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
}

static VOID imProStatIntHandlerPrint( UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	for(UCHAR i = 0; i < D_IM_PRO_STAT_PWCH_CH_NUM; i++) {
		Ddim_Print(( "imProStatIntHandlerPrint() PWCH%u PWCHINTFLG(0x%08x) PWCHINTENB(0x%08x) (status:%u)\n", i, IO_PRO.SEN.PWCH[i].PWCHINTFLG.word, IO_PRO.SEN.PWCH[i].PWCHINTENB.word, status ));
	}
	for(UCHAR i = 0; i < D_IM_PRO_STAT_AEAWB_CH_NUM; i++) {
		Ddim_Print(( "imProStatIntHandlerPrint() AEAWB%u LINEINTFLG(0x%08x) LINEINTENB(0x%08x) (status:%u)\n", i, IO_PRO.STAT.AEAWB[i].LINEINTFLG.word, IO_PRO.STAT.AEAWB[i].LINEINTENB.word, status ));
	}
	for(UCHAR i = 0; i < D_IM_PRO_STAT_AF_CH_NUM; i++) {
		Ddim_Print(( "imProStatIntHandlerPrint() AF%u AFINTFLG(0x%08x) AFINTENB(0x%08x) (status:%u)\n", i, IO_PRO.STAT.AF[i].AFGBAL.AFINTFLG.word, IO_PRO.STAT.AF[i].AFGBAL.AFINTENB.word, status ));
	}
	for(UCHAR i = 0; i < D_IM_PRO_STAT_HIST_CH_NUM; i++) {
		Ddim_Print(( "imProStatIntHandlerPrint() HIST%u HISTINTFLG(0x%08x) HISTINTENB(0x%08x) (status:%u)\n", i, IO_PRO.STAT.HIST[i].HISTINTFLG.word, IO_PRO.STAT.HIST[i].HISTINTENB.word, status ));
	}
#endif
}

static VOID imProPastopVdIntHandlerPrint( UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "im_pro_sen_vd_int_handler_print() VHDINTFLG(0x%08x) VHDINTENB(0x%08x) (status:%u)\n", IO_PRO.PAS.PASTOP.VHDINTFLG.word, IO_PRO.PAS.PASTOP.VHDINTENB.word, status ));
#endif
}

static VOID imProPastopHdIntHandlerPrint( UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "imProPastopHdIntHandlerPrint() VHDINTFLG(0x%08x) VHDINTENB(0x%08x) (status:%u)\n", IO_PRO.PAS.PASTOP.VHDINTFLG.word, IO_PRO.PAS.PASTOP.VHDINTENB.word, status ));
#endif
}


/*----------------------------------------------------------------------*/
/* PUBLIC                           											   */
/*----------------------------------------------------------------------*/
VOID interrupt_callback_monifunc( InterruptCallback*self,
		UINT32	loopcnt,TimproSencoreIntFactor* intFactor,ULONG	callbackResult,T_CALLBACK_ID	*cbId,UCHAR sencoreCh)
{
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_MONI_INT) / sizeof(S_GIM_PRO_INTTBL_MONI_INT[0])); loopcnt++ ) {
		if( (intFactor->moniIntf & S_GIM_PRO_INTTBL_MONI_INT[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_MONI_INT[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_MONI_CALLBACK_FUNC[0][E_IM_PRO_BLOCK_TYPE_SEN][sencoreCh].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId->unit_no		= E_IM_PRO_UNIT_NUM_1,
		cbId->block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
		cbId->channel		= sencoreCh,
		S_GIM_PRO_MONI_CALLBACK_FUNC[0][E_IM_PRO_BLOCK_TYPE_SEN][sencoreCh].pCallback( cbId, callbackResult, S_GIM_PRO_MONI_CALLBACK_FUNC[0][E_IM_PRO_BLOCK_TYPE_SEN][sencoreCh].userParam );
	}
}

/**
STAT Macro Int handler.
*/
VOID interrupt_callback_stat_int_handler( VOID )
{
	UINT32	loopcnt = 0;
	UINT32	loopcntCh = 0;
	ULONG	aeawbIntf[D_IM_PRO_STAT_AEAWB_CH_NUM] = {0};
	ULONG	afIntf[D_IM_PRO_STAT_AF_CH_NUM] = {0};
	ULONG	histIntf[D_IM_PRO_STAT_HIST_CH_NUM] = {0};
	ULONG	callbackResult = 0;
	ULONG	pwchIntf[D_IM_PRO_STAT_PWCH_CH_NUM] = {0};
	TimproPwchIntInfo	pwchInfo = {0};
	T_CALLBACK_ID	cbId = {
		.unit_no	= 0,
		.block_type	= 0,
		.channel	= 0,
	};

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_callback_stat_int_handler begin\n" ));
#endif
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );
	Im_Pro_Dsb();
	imProStatIntHandlerPrint( 0 );

	/***********/
	/* PWCH    */
	/***********/
	// Get & clear interrupt flag
	pwchInfo.unitNo		= E_IM_PRO_UNIT_NUM_1;
	pwchInfo.blockType	= E_IM_PRO_BLOCK_TYPE_STAT;
	pwchInfo.regPtr		= IO_PRO.STAT.PWCH;
	interrupt_factor_pwch_clear_int_factor( interrupt_factor_new(),&pwchInfo, pwchIntf, D_IM_PRO_STAT_PWCH_CH_NUM );

	/***********/
	/* AEAWB   */
	/***********/
	// Get & clear interrupt flag
	for( loopcnt = 0; loopcnt < D_IM_PRO_STAT_AEAWB_CH_NUM; loopcnt++ ) {
		aeawbIntf[loopcnt]	= IO_PRO.STAT.AEAWB[loopcnt].LINEINTFLG.word & IO_PRO.STAT.AEAWB[loopcnt].LINEINTENB.word;
		IO_PRO.STAT.AEAWB[loopcnt].LINEINTFLG.word = aeawbIntf[loopcnt];
	}

	/***********/
	/* AF      */
	/***********/
	// Get & clear interrupt flag
	for( loopcnt = 0; loopcnt < D_IM_PRO_STAT_AF_CH_NUM; loopcnt++ ) {
		afIntf[loopcnt]	= IO_PRO.STAT.AF[loopcnt].AFGBAL.AFINTFLG.word & IO_PRO.STAT.AF[loopcnt].AFGBAL.AFINTENB.word;
		IO_PRO.STAT.AF[loopcnt].AFGBAL.AFINTFLG.word = afIntf[loopcnt];

		if( afIntf[loopcnt] & D_IM_PRO_AFINTFLG_AFF ) {
			im_pro_comm_update_af_result( loopcnt );
		}
	}

	/***********/
	/* HIST    */
	/***********/
	// Get & clear interrupt flag
	for( loopcnt = 0; loopcnt < D_IM_PRO_STAT_HIST_CH_NUM; loopcnt++ ) {
		histIntf[loopcnt]	= IO_PRO.STAT.HIST[loopcnt].HISTINTFLG.word & IO_PRO.STAT.HIST[loopcnt].HISTINTENB.word;
		IO_PRO.STAT.HIST[loopcnt].HISTINTFLG.word = histIntf[loopcnt];
		if( histIntf[loopcnt] & D_IM_PRO_HISTINTFLG_HISTF ) {
			im_pro_comm_update_hist_result( loopcnt );
		}
	}

	Im_Pro_Dsb();
	imProStatIntHandlerPrint( 1 );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );


	/***********/
	/* PWCH    */
	/***********/
	for( loopcntCh = 0; loopcntCh < D_IM_PRO_STAT_PWCH_CH_NUM; loopcntCh++ ) {
		interrupt_factor_pwch_callback_int_factor( interrupt_factor_new(),0, E_IM_PRO_BLOCK_TYPE_STAT, (E_IM_PRO_PWCH)loopcntCh, pwchIntf );
	}

	/***********/
	/* AEAWB   */
	/***********/
	for( loopcntCh = 0; loopcntCh < D_IM_PRO_STAT_AEAWB_CH_NUM; loopcntCh++ ) {
		callbackResult = 0;
		for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_STAT_AEAWB_INT) / sizeof(S_GIM_PRO_INTTBL_STAT_AEAWB_INT[0])); loopcnt++ ) {
			if( (aeawbIntf[loopcntCh] & S_GIM_PRO_INTTBL_STAT_AEAWB_INT[loopcnt].flgBitmask) != 0 ) {
				callbackResult	|= S_GIM_PRO_INTTBL_STAT_AEAWB_INT[loopcnt].intFact;
			}
		}
		// Callback
		if (( S_GIM_PRO_AEAWB_CALLBACK_FUNC[loopcntCh].pCallback != NULL ) && ( callbackResult != 0 )){
			cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
			cbId.block_type	= E_IM_PRO_BLOCK_TYPE_STAT,
			cbId.channel		= loopcntCh,
			S_GIM_PRO_AEAWB_CALLBACK_FUNC[loopcntCh].pCallback( &cbId, callbackResult, S_GIM_PRO_AEAWB_CALLBACK_FUNC[loopcntCh].userParam );
		}
	}
	Im_Pro_Dsb();

	/***********/
	/* AF      */
	/***********/
	for( loopcntCh = 0; loopcntCh < D_IM_PRO_STAT_AF_CH_NUM; loopcntCh++ ) {
		callbackResult = 0;
		for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_STAT_AF_INT) / sizeof(S_GIM_PRO_INTTBL_STAT_AF_INT[0])); loopcnt++ ) {
			if( (afIntf[loopcntCh] & S_GIM_PRO_INTTBL_STAT_AF_INT[loopcnt].flgBitmask) != 0 ) {
				callbackResult	|= S_GIM_PRO_INTTBL_STAT_AF_INT[loopcnt].intFact;
			}
		}
		// Callback
		if (( S_GIM_PRO_AF_CALLBACK_FUNC[loopcntCh].pCallback != NULL ) && ( callbackResult != 0 )){
			cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
			cbId.block_type	= E_IM_PRO_BLOCK_TYPE_STAT,
			cbId.channel		= loopcntCh,
			S_GIM_PRO_AF_CALLBACK_FUNC[loopcntCh].pCallback( &cbId, callbackResult, S_GIM_PRO_AF_CALLBACK_FUNC[loopcntCh].userParam );
		}
	}
	Im_Pro_Dsb();

	/***********/
	/* HIST    */
	/***********/
	for( loopcntCh = 0; loopcntCh < D_IM_PRO_STAT_AF_CH_NUM; loopcntCh++ ) {
		callbackResult = 0;
		for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_STAT_HIST_INT) / sizeof(S_GIM_PRO_INTTBL_STAT_HIST_INT[0])); loopcnt++ ) {
			if( (histIntf[loopcntCh] & S_GIM_PRO_INTTBL_STAT_HIST_INT[loopcnt].flgBitmask) != 0 ) {
				callbackResult	|= S_GIM_PRO_INTTBL_STAT_HIST_INT[loopcnt].intFact;
			}
		}
		// Callback
		if (( S_GIM_PRO_HIST_CALLBACK_FUNC[loopcntCh].pCallback != NULL ) && ( callbackResult != 0 )){
			cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
			cbId.block_type	= E_IM_PRO_BLOCK_TYPE_STAT,
			cbId.channel		= loopcntCh,
			S_GIM_PRO_HIST_CALLBACK_FUNC[loopcntCh].pCallback( &cbId, callbackResult, S_GIM_PRO_HIST_CALLBACK_FUNC[loopcntCh].userParam );
		}
	}
	Im_Pro_Dsb();
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_callback_stat_int_handler end\n" ));
#endif
}

/**
CallBackFunction which Call to the interruption timing of AEAWB is registered
@param[in]	ch : channel
@param[in]	inthandler : AEAWB Interrupt callback function address
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_callback_aeawb_set_int_handler( InterruptCallback*self,E_IM_PRO_AEAWB_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_AEAWB_CALLBACK_FUNC[ch].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_AEAWB_CALLBACK_FUNC[ch].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
CallBackFunction which Call to the interruption timing of AF is registered
@param[in]	ch : channel
@param[in]	inthandler : AF Interrupt callback function address
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_callback_af_set_int_handler( InterruptCallback*self,E_IM_PRO_AF_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_AF_CALLBACK_FUNC[ch].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_AF_CALLBACK_FUNC[ch].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
CallBackFunction which Call to the interruption timing of HIST is registered
@param[in]	ch : channel
@param[in]	inthandler : HIST Interrupt callback function address
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_callback_hist_set_int_handler( InterruptCallback*self, E_IM_PRO_HIST_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_HIST_CALLBACK_FUNC[ch].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_HIST_CALLBACK_FUNC[ch].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
PAS block VD Int handler setting.
@param[in]	inthandler : Interrupt handler address pointer
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_callback_pastop_set_vd_int_handler( InterruptCallback*self,T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_PAS_VD_CALLBACK_FUNC.pCallback = callbackCfg->inthandler;
	S_GIM_PRO_PAS_VD_CALLBACK_FUNC.userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
PAS Macro VD Int handler.
*/
VOID interrupt_callback_pastop_vd_int_handler( VOID )
{
	UINT32			loopcnt;
	ULONG			vdIntf;
	ULONG callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= E_IM_PRO_UNIT_NUM_1,
		.block_type	= E_IM_PRO_BLOCK_TYPE_PAS,
		.channel	= 0,
	};

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_callback_pastop_vd_int_handler begin\n" ));
#endif
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	Im_Pro_Dsb();
	imProPastopVdIntHandlerPrint( 0 );

	// Get interrupt flag
	vdIntf	= IO_PRO.PAS.PASTOP.VHDINTFLG.word & IO_PRO.PAS.PASTOP.VHDINTENB.word & D_IM_PRO_PASTOP_INT_VD_ALL;

	// Clear interrupt flag
	IO_PRO.PAS.PASTOP.VHDINTFLG.word	= vdIntf;

	Im_Pro_Dsb();
	imProPastopVdIntHandlerPrint( 1 );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	/***********/
	/* VD Edge */
	/***********/
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_PAS_VD) / sizeof(S_GIM_PRO_INTTBL_PAS_VD[0])); loopcnt++ ) {
		if( (vdIntf & S_GIM_PRO_INTTBL_PAS_VD[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_PAS_VD[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_PAS_VD_CALLBACK_FUNC.pCallback != NULL ) && ( callbackResult != 0 )){
		S_GIM_PRO_PAS_VD_CALLBACK_FUNC.pCallback( &cbId, callbackResult, S_GIM_PRO_PAS_VD_CALLBACK_FUNC.userParam );
	}
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_callback_pastop_vd_int_handler end\n" ));
#endif
}

/**
PAS block HD Int handler setting.
@param[in]	inthandler : Interrupt handler address pointer
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_callback_pastop_set_hd_int_handler( InterruptCallback*self, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_PAS_HD_CALLBACK_FUNC.pCallback = callbackCfg->inthandler;
	S_GIM_PRO_PAS_HD_CALLBACK_FUNC.userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
PAS Macro HD Int handler.
*/
VOID interrupt_callback_pastop_hd_int_handler( VOID )
{
	UINT32			loopcnt;
	ULONG			hdIntf;
	ULONG			callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= E_IM_PRO_UNIT_NUM_1,
		.block_type	= E_IM_PRO_BLOCK_TYPE_PAS,
		.channel	= 0,
	};

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_callback_pastop_hd_int_handler begin\n" ));
#endif
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	Im_Pro_Dsb();
	imProPastopHdIntHandlerPrint( 0 );

	// Get interrupt flag
	hdIntf		= IO_PRO.PAS.PASTOP.VHDINTFLG.word & IO_PRO.PAS.PASTOP.VHDINTENB.word & D_IM_PRO_PASTOP_INT_HD_ALL;

	// Clear interrupt flag
	IO_PRO.PAS.PASTOP.VHDINTFLG.word	= hdIntf;

	Im_Pro_Dsb();
	imProPastopHdIntHandlerPrint( 1 );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	/***********/
	/* HD Edge */
	/***********/
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_PAS_HD) / sizeof(S_GIM_PRO_INTTBL_PAS_HD[0])); loopcnt++ ) {
		if( (hdIntf & S_GIM_PRO_INTTBL_PAS_HD[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_PAS_HD[loopcnt].intFact;

		}
	}
	// Callback
	if (( S_GIM_PRO_PAS_HD_CALLBACK_FUNC.pCallback != NULL ) && ( callbackResult != 0 )){
		S_GIM_PRO_PAS_HD_CALLBACK_FUNC.pCallback( &cbId, callbackResult, S_GIM_PRO_PAS_HD_CALLBACK_FUNC.userParam );
	}
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_callback_pastop_hd_int_handler end\n" ));
#endif
}

/**
CallBackFunction which Call to the interruption timing of SDC is registered
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel<br>
	 			 value range:[0 - 1]<br>
@param[in]	inthandler : SDC Interrupt callback function address
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NCH_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_callback_sdc_set_int_handler( InterruptCallback*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_SDC_CALLBACK_FUNC[unitNo][ch].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_SDC_CALLBACK_FUNC[unitNo][ch].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
CallBackFunction which Call to the interruption timing of MONI is registered
@param[in]	ch : Channel No.
@param[in]	inthandler : MONI Interrupt callback function address
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_callback_moni_set_int_handler( InterruptCallback*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_MONI_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_MONI_CALLBACK_FUNC[unitNo][blockType][ch].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_MONI_CALLBACK_FUNC[unitNo][blockType][ch].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
SRO Macro Pipe1 Int handler.
*/
VOID interrupt_callback_srotop_pipe1_int_handler( VOID )
{
	TinterruptcallbackSroIntFactor intFactor;

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_callback_srotop_pipe1_int_handler begin\n" ));
#endif
	imProClearSroIntFactor( E_IM_PRO_UNIT_NUM_1, &intFactor );
	imProCallbackSroInt( E_IM_PRO_UNIT_NUM_1, &intFactor );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_callback_srotop_pipe1_int_handler end\n" ));
#endif
}

/**
SRO Macro Pipe2 Int handler.
*/
VOID interrupt_callback_srotop_pipe2_int_handler( VOID )
{
	TinterruptcallbackSroIntFactor intFactor;

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_callback_srotop_pipe2_int_handler begin\n" ));
#endif
	imProClearSroIntFactor( E_IM_PRO_UNIT_NUM_2, &intFactor );
	imProCallbackSroInt( E_IM_PRO_UNIT_NUM_2, &intFactor );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_callback_srotop_pipe2_int_handler end\n" ));
#endif
}

InterruptCallback *interrupt_callback_new(void)
{
	InterruptCallback* self = k_object_new_with_private(INTERRUPT_TYPE_CALLBACK,sizeof(InterruptCallbackPrivate));
	return self;
}
