/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、XDMA driver
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#include "dd_arm.h"
#include "arm.h"
#include "ddxdmasnap.h"
#include "lytest.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdXdmasnap, dd_xdmasnap);
#define DD_XDMASNAP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdXdmasnapPrivate, DD_TYPE_XDMASNAP))

// Sync Processing
#define D_DD_XDMASNAP_SYNC			(0)
// Async Processing
#define D_DD_XDMASNAP_ASYNC			(1)

struct _DdXdmasnapPrivate
{
	int a;
};

// DMA Register Info
static volatile TDdXdmasnapCtrl S_CTRL[DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX];
static volatile kushort 			S_STOP_STATUS[DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX];
static volatile kint32 			S_WAIT_END_TIME[DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX];

// Spin Lock
static kulong S_XDMASNAP_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64))) = 0;

static void dd_xdmasnap_constructor(DdXdmasnap *self)
{
	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);
}

static void dd_xdmasnap_destructor(DdXdmasnap *self)
{
	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);
}

/**
 * @brief  DMA wait end.
 */
static kint32 ddXdmasnapWaitEnd(kuchar ch, kushort *const status, kuint32 waitMode)
{
	DDIM_USER_FLGPTN flgPtn;
	DDIM_USER_ER ercd = 0;
	
	// CPU Polling (no use interrupt)
	if( waitMode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU ){
		while(( IO_XDMACS.CH[ch].XDDSD.bit.TS == DdXdmasnap_D_DD_XDMASNAP_XDDSD_TS_RUNNING ) && ( S_STOP_STATUS[ch] == 0 )){
			;	// It waits until completing it
		}
		
		if( S_STOP_STATUS[ch] == 0 ){
			*status = IO_XDMACS.CH[ch].XDDSD.bit.IS;
			// Stop Status clear
			IO_XDMACS.CH[ch].XDDSD.bit.IS = 0x0;
			// DMA Stop
			IO_XDMACS.CH[ch].XDDES.bit.CE = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
		}
		else{
			*status = S_STOP_STATUS[ch];
			S_STOP_STATUS[ch] = 0;
		}
	}
	// EVENT (use interrupt)
	else{
		switch(ch){
			case 0:
				ercd = DDIM_User_Twai_Flg(FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH0, D_DDIM_USER_TWF_ORW, &flgPtn, S_WAIT_END_TIME[ch]);
				break;
			case 1:
				ercd = DDIM_User_Twai_Flg(FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH1, D_DDIM_USER_TWF_ORW, &flgPtn, S_WAIT_END_TIME[ch]);
				break;
			case 2:
				ercd = DDIM_User_Twai_Flg(FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH2, D_DDIM_USER_TWF_ORW, &flgPtn, S_WAIT_END_TIME[ch]);
				break;
			case 3:
				ercd = DDIM_User_Twai_Flg(FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH3, D_DDIM_USER_TWF_ORW, &flgPtn, S_WAIT_END_TIME[ch]);
				break;
			default:
				break;
		}
		
		*status = S_STOP_STATUS[ch];
		S_STOP_STATUS[ch] = 0;
	}
	
	if( ercd == D_DDIM_USER_E_TMOUT ){
		Ddim_Print(("DMA error. timeout!\n"));
		return DdXdmasnap_D_DD_XDMASNAP_TIMEOUT_ERR;
	}
	
	if( ercd != D_DDIM_USER_E_OK ){
		Ddim_Print(("DMA error. system error!\n"));
		return DdXdmasnap_D_DD_XDMASNAP_SYSTEM_ERR;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  DMA start.
 */
static kint32 ddXdmasnapStart(kuchar ch, kushort* const status, kuint32 waitMode, kuint32 sync)
{
	kint32 ret = D_DDIM_OK;
	union io_xdmac_xdsac xdsac;
	union io_xdmac_xddac xddac;
	union io_xdmac_xddes xddes;
	
	// DMA Enable
	if( IO_XDMACS.XDACS.bit.xE == DdXdmasnap_D_DD_XDMASNAP_XDACS_XS_NOTACTIVE ){
		return DdXdmasnap_D_DD_XDMASNAP_SYSTEM_ERR;
	}
	
	if( waitMode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT ){
		// Error Interrupt Enable
		S_CTRL[ch].config1.bit.eI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_ENABLE;
		// Completion Interrupt Enable
		S_CTRL[ch].config1.bit.tI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_ENABLE;
	}
	
	S_STOP_STATUS[ch] = 0;
	
	// XDSAC
	xdsac.word = IO_XDMACS.CH[ch].XDSAC.word;
	xdsac.bit.sRL = S_CTRL[ch].config1.bit.sRL;
	xdsac.bit.sAF = S_CTRL[ch].config1.bit.sAF;
	xdsac.bit.sBL = S_CTRL[ch].config1.bit.sBL;
	xdsac.bit.sBS = S_CTRL[ch].config1.bit.sBS;
	IO_XDMACS.CH[ch].XDSAC.word = xdsac.word;
	
	// XDDAC
	xddac.word = IO_XDMACS.CH[ch].XDDAC.word;
	xddac.bit.dRL = S_CTRL[ch].config1.bit.dRL;
	xddac.bit.dAF = S_CTRL[ch].config1.bit.dAF;
	xddac.bit.dBL = S_CTRL[ch].config1.bit.dBL;
	xddac.bit.dBS = S_CTRL[ch].config1.bit.dBS;
	IO_XDMACS.CH[ch].XDDAC.word = xddac.word;
	
	// XDDES
	xddes.word = IO_XDMACS.CH[ch].XDDES.word;
	xddes.bit.tI = S_CTRL[ch].config1.bit.tI;
	xddes.bit.eI = S_CTRL[ch].config1.bit.eI;
	xddes.bit.aT = S_CTRL[ch].config1.bit.aT;
	xddes.bit.bR = S_CTRL[ch].config1.bit.bR;
	xddes.bit.bT = S_CTRL[ch].config1.bit.bT;
	xddes.bit.sA = S_CTRL[ch].config1.bit.sA;
	xddes.bit.tF = S_CTRL[ch].config1.bit.tF;
	xddes.bit.sE = S_CTRL[ch].config1.bit.sE;
	IO_XDMACS.CH[ch].XDDES.word = xddes.word;
	
	IO_XDMACS.CH[ch].XDDCC = S_CTRL[ch].config2.word;
	
	IO_XDMACS.CH[ch].XDTBC = S_CTRL[ch].trnsSize - 1;
	// DMA Source Address register set
	IO_XDMACS.CH[ch].XDSSA = S_CTRL[ch].srcAddr;
	// DMA Destination Address register set
	IO_XDMACS.CH[ch].XDDSA = S_CTRL[ch].dstAddr;
	
	if( waitMode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT ){
		switch(ch){
			case 0:
				DDIM_User_Clr_Flg(FID_DD_XDMASNAP, ~DdXdmasnap_D_DD_XDMASNAP_FLG_CH0);
				break;
			case 1:
				DDIM_User_Clr_Flg(FID_DD_XDMASNAP, ~DdXdmasnap_D_DD_XDMASNAP_FLG_CH1);
				break;
			case 2:
				DDIM_User_Clr_Flg(FID_DD_XDMASNAP, ~DdXdmasnap_D_DD_XDMASNAP_FLG_CH2);
				break;
			case 3:
				DDIM_User_Clr_Flg(FID_DD_XDMASNAP, ~DdXdmasnap_D_DD_XDMASNAP_FLG_CH3);
				break;
			default:
				break;
		}
	}
	
	IO_XDMACS.CH[ch].XDDES.bit.CE = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_ENABLE;
	Dd_ARM_Dsb_Pou();
	
	// Sync Processing
	if( sync == D_DD_XDMASNAP_SYNC ){
		ret = ddXdmasnapWaitEnd(ch, status, waitMode);
	}
	
	return ret;
}

/**
 * @brief  Execute exclusive control for designated DMA channel.
 * @param  kint32	tmout
 * @param  kuchar	ch	Channel number (0 to 3)
 * @return kint32 	D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_EXC_LOCK_NG / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR / DdXdmasnap_D_DD_XDMASNAP_SEM_TIMEOUT / DdXdmasnap_D_DD_XDMASNAP_SEM_NG
 */
kint32 dd_xdmasnap_open(DdXdmasnap *self, kuchar ch, kint32 tmout)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( tmout < D_DDIM_USER_SEM_WAIT_FEVR ){
		Ddim_Assertion(("Dd_XDMASNAP_Open: input param error. tmout = %d\n", tmout));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	DDIM_USER_ER ercd = 0;
	
	if( D_DDIM_USER_SEM_WAIT_POL == tmout ){
		// pol_sem()
		ercd = DDIM_User_Pol_Sem(SID_DD_XDMASNAP(ch));
	}
	else{
		// twai_sem()
		ercd = DDIM_User_Twai_Sem(SID_DD_XDMASNAP(ch), (DDIM_USER_TMO)tmout);
	}
	
	if( D_DDIM_USER_E_OK != ercd ){
		if( D_DDIM_USER_E_TMOUT == ercd ){
			return DdXdmasnap_D_DD_XDMASNAP_SEM_TIMEOUT;
		}
		
		return DdXdmasnap_D_DD_XDMASNAP_SEM_NG;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Cancel exclusive control for designated DMA channel.
           When the designated channel is under transferring, stop transfer immediately and cancel lock.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32  D_DDIM_OK/DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR / DdXdmasnap_D_DD_XDMASNAP_SEM_NG
 */
kint32 dd_xdmasnap_close(DdXdmasnap *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	DDIM_USER_ER ercd = 0;
	
	// Global variable is clear
	S_CTRL[ch].config1.word = 0;
	S_CTRL[ch].config2.word = 0;
	S_CTRL[ch].srcAddr      = 0;
	S_CTRL[ch].dstAddr      = 0;
	S_CTRL[ch].trnsSize     = 0;
	S_CTRL[ch].intHandler   = NULL;
	// sig_sem()
	ercd = DDIM_User_Sig_Sem(SID_DD_XDMASNAP(ch));
	if( D_DDIM_USER_E_OK != ercd ){
		return DdXdmasnap_D_DD_XDMASNAP_SEM_NG;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Set control data to registers related DMA designated channel.
 * @return kint32	D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR
 */
kint32 dd_xdmasnap_ctrl_common(DdXdmasnap *self, TDdXdmasnapCommon const *const dmaCommon)
{
#ifdef CO_PARAM_CHECK
	if( dmaCommon == NULL ){
		Ddim_Assertion(("XDMASNAP: input param error. [*dma_ctrl] NULL\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(S_XDMASNAP_SPIN_LOCK);
	
	// The value is set to an external variable
	IO_XDMACS.XDACS.bit.cP = dmaCommon->commonConfig.bit.cP;
	IO_XDMACS.XDACS.bit.xE = dmaCommon->commonConfig.bit.xE;
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(S_XDMASNAP_SPIN_LOCK);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set control data to registers related DMA designated channel.
 * @param  kuchar	ch	Channel number (0 to 3)
 * @param  kuchar	dmaCtrlTrans	DMA Transfer setting
 * @return kint32	D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR
 */
kint32	dd_xdmasnap_ctrl_trns(DdXdmasnap *self, kuchar ch, TDdXdmasnapCtrl const *const dmaCtrlTrans)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( dmaCtrlTrans == NULL ){
		Ddim_Assertion(("XDMASNAP: input param error. [*dmaCtrlTrans] NULL\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( dmaCtrlTrans->trnsSize == 0 ){
		Ddim_Assertion(("XDMASNAP: input param error. [dmaCtrlTrans->trnsSize] Zero\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	// The value is set to an external variable
	S_CTRL[ch].config1.word = dmaCtrlTrans->config1.word;
	S_CTRL[ch].config2.word = 0;
	S_CTRL[ch].config2.bit.dCA = dmaCtrlTrans->config2.bit.dCA;
	S_CTRL[ch].config2.bit.dCN = dmaCtrlTrans->config2.bit.dCN;
	
	S_CTRL[ch].trnsSize       = dmaCtrlTrans->trnsSize;
	S_CTRL[ch].srcAddr        = dmaCtrlTrans->srcAddr;
	S_CTRL[ch].dstAddr        = dmaCtrlTrans->dstAddr;
	S_CTRL[ch].intHandler     = dmaCtrlTrans->intHandler;
	
	S_WAIT_END_TIME[ch] = D_DDIM_WAIT_END_TIME;
	
	return D_DDIM_OK;
}

/**
 * @brief  Set translation size to registers related DMA designated channel.
 * @param  kuchar	ch	Channel number (0 to 3)
 * @param  kuchar	dmaTrnsSize	DMA Transfer size
 * @return kint32	D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR
 */
kint32	dd_xdmasnap_set_trns_size(DdXdmasnap *self, kuchar ch, DdXdmasnapTrnsSize const *const dmaTrnsSize)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( dmaTrnsSize == NULL ){
		Ddim_Assertion(("XDMASNAP: input param error. [*dmaTrnsSize] NULL\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( dmaTrnsSize->trnsSize == 0 ){
		Ddim_Assertion(("XDMASNAP: input param error. [dmaTrnsSize->trnsSize] Zero\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	S_CTRL[ch].trnsSize = dmaTrnsSize->trnsSize;
	S_CTRL[ch].srcAddr  = dmaTrnsSize->srcAddr;
	S_CTRL[ch].dstAddr  = dmaTrnsSize->dstAddr;
	IO_XDMACS.CH[ch].XDSSA = S_CTRL[ch].srcAddr;
	IO_XDMACS.CH[ch].XDDSA = S_CTRL[ch].dstAddr;
	
	return D_DDIM_OK;
}

/**
 * @brief  The operation of DMA of specified ch begins.
 * @param  kuchar			ch			Channel number (0 to 3)
 *         kushort*			status		Channel Status Register pointer
 *         kuint32			waitMode	DMA end wait mode
 * @return kint32			D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR / D_DDIM_TIMEOUT / DdXdmasnap_D_DD_XDMASNAP_SYSTEM_ERR
 */
kint32	dd_xdmasnap_start_sync(DdXdmasnap *self, kuchar ch, kushort *const status, kuint32 waitMode)
{
	kint32 ret;
	
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( status == NULL ){
		Ddim_Assertion(("XDMASNAP: input param error. [*status] NULL\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if(( waitMode != DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU ) && ( waitMode != DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT )){
		Ddim_Assertion(("XDMASNAP: input param error. [waitMode] = %x\n", waitMode));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	// DMA Start
	ret = ddXdmasnapStart(ch, status, waitMode, D_DD_XDMASNAP_SYNC);
	
	return ret;
}

/**
 * @brief  The operation of DMA of specified ch begins.
 * @param  kuchar			ch			Channel number (0 to 3)
 * @return kint32			D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR
 */
kint32	dd_xdmasnap_start_async(DdXdmasnap *self, kuchar ch)
{
	// dummy
	kushort	status;
	
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	// DMA Start
	ddXdmasnapStart(ch, &status, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT, D_DD_XDMASNAP_ASYNC);
	
	return D_DDIM_OK;
}

/**
 * @brief  The operation of DMA of specified ch is stopped.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32	D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR
 */
kint32	dd_xdmasnap_stop(DdXdmasnap *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	IO_XDMACS.CH[ch].XDDES.bit.CE = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
	Dd_ARM_Dsb_Pou();
	
	return D_DDIM_OK;
}

/**
 * @brief  Wait end time of transfer process of designated channel.
 * @param  kuchar	ch			Channel number (0 to 3)
 *         kint32	waitTime	Wait end time of transfer process
 * @return kint32				D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR
 */
kint32 dd_xdmasnap_set_wait_time(DdXdmasnap *self, kuchar ch, kint32 waitTime)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( waitTime < D_DDIM_WAIT_END_FOREVER ){
		Ddim_Assertion(("XDMASNAP: input param error. [waitTime] = %d\n", waitTime));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	S_WAIT_END_TIME[ch] = waitTime;
	
	return D_DDIM_OK;
}

/**
 * @brief  Wait end of transfer process of designated channel.
 *         The value of the CSTR register is passed by the out parameter.
 * @param  kuchar	ch			Channel number (0 to 3)
 *         kushort*	status		Channel Status Register pointer
 * @return kint32	D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR / D_DDIM_TIMEOUT / DdXdmasnap_D_DD_XDMASNAP_SYSTEM_ERR
 */
kint32 dd_xdmasnap_wait_end(DdXdmasnap *self, kuchar ch, kushort* const status, kuint32 waitMode)
{
	kint32 ret;
	
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( status == NULL ){
		Ddim_Assertion(("XDMASNAP: input param error. [*status] NULL\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if(( waitMode != DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU ) && ( waitMode != DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT )){
		Ddim_Assertion(("XDMASNAP: input param error. [waitMode] = %x\n", waitMode));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	ret = ddXdmasnapWaitEnd(ch, status, waitMode);
	
	return ret;
}

/**
 * @brief  The status of DMA of specified ch is cleared.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32				D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR
 */
kint32	dd_xdmasnap_clear_status(DdXdmasnap *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	IO_XDMACS.CH[ch].XDDSD.bit.IS = DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_NONE;
	
	return D_DDIM_OK;
}

/**
 * @brief  The error status of DMA of specified ch is collected.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32				D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR
 */
kint32	dd_xdmasnap_get_status(DdXdmasnap *self, kuchar ch, kushort *const xdmacStatus, kushort *const transferStatus, kushort *const interruptStatus)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( xdmacStatus == NULL ){
		Ddim_Assertion(("XDMASNAP: input param error. [*status] NULL\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( transferStatus == NULL ){
		Ddim_Assertion(("XDMASNAP: input param error. [*transferStatus] NULL\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( interruptStatus == NULL ){
		Ddim_Assertion(("XDMASNAP: input param error. [*interruptStatus] NULL\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	*xdmacStatus = IO_XDMACS.XDACS.bit.XS;
	*transferStatus = IO_XDMACS.CH[ch].XDDSD.bit.TS;
	*interruptStatus = IO_XDMACS.CH[ch].XDDSD.bit.IS;
	
	return D_DDIM_OK;
}

/**
 * @brief   The value of the transferd size of the specified channel is acquired.
 * @param   kuchar		ch		Channel number (0 to 3)
 * @return  kulong				Transferd size of the specified channel
 * @remarks This API forced cancel exclusive control if process is under executing.
 */
kulong	dd_xdmasnap_get_trns_size(DdXdmasnap *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif
	return S_CTRL[ch].trnsSize - (IO_XDMACS.CH[ch].XDTBC + 1);
}

/**
 * @brief  The value of the source address (DMACSA) of the specified channel is acquired.
 * @param  kuchar		ch		Channel number (0 to 3)
 * @return kulong				Source address of the specified channel
 */
kulong	dd_xdmasnap_get_src_addr(DdXdmasnap *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif
	return IO_XDMACS.CH[ch].XDSSA;
}

/**
 * @brief  The value of the destination address (DMACDA) of the specified channel is acquired.
 * @param  kuchar		ch		Channel number (0 to 3)
 * @return kulong				Destination address of the specified channel
 */
kulong	dd_xdmasnap_get_dst_addr(DdXdmasnap *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif
	return IO_XDMACS.CH[ch].XDDSA;
}

/**
 * @brief  Low Power is set is set.
 * @param  kuchar		lowPower	Low Power
 * @return kint32					D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR
 */
kint32	dd_xdmasnap_set_low_power(DdXdmasnap *self, kuchar lowPower)
{
#ifdef CO_PARAM_CHECK
	if (lowPower > DdXdmasnap_D_DD_XDMASNAP_XDACS_LP_ENABLE) {
		Ddim_Assertion(("XDMASNAP: input param error. [lowPower] = %d\n", lowPower));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(S_XDMASNAP_SPIN_LOCK);
	
	IO_XDMACS.XDACS.bit.LP = lowPower;
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(S_XDMASNAP_SPIN_LOCK);
	
	return D_DDIM_OK;
}

/**
 * @brief  Source Protection code is set.
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  kuchar		protectCode	Protection Code
 * @return kint32						D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR
 */
kint32	dd_xdmasnap_set_source_protect(DdXdmasnap *self, kuchar ch, kuchar protectCode)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( protectCode > DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_SECURE ){
		Ddim_Assertion(("XDMASNAP: input param error. [protectCode] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	IO_XDMACS.CH[ch].XDDPC.bit.SP = protectCode;
	
	return D_DDIM_OK;
}

/**
 * @brief  Destination Protection code is set.
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  kuchar		protectCode	Protection Code
 * @return kint32						D_DDIM_OK / DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR
 */
kint32	dd_xdmasnap_set_destination_protect(DdXdmasnap *self, kuchar ch, kuchar protectCode)
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( protectCode > DdXdmasnap_D_DD_XDMASNAP_XDDPC_DP_PRIVILEGED_SECURE ){
		Ddim_Assertion(("XDMASNAP: input param error. [protectCode] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	IO_XDMACS.CH[ch].XDDPC.bit.DP = protectCode;
	
	return D_DDIM_OK;
}

/**
 * @brief  The operation of All DMA channel is stopped.
 */
VOID	dd_xdmasnap_stop_all_ch(DdXdmasnap *self)
{
	IO_XDMACS.CH[0].XDDES.bit.CE = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
	IO_XDMACS.CH[1].XDDES.bit.CE = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
	IO_XDMACS.CH[2].XDDES.bit.CE = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
	IO_XDMACS.CH[3].XDDES.bit.CE = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
	
	return;
}

/**
 * @brief  Set DMA Interrupt Handler.
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  VOID			intHandler		Interrupt handler
 * @return VOID
 */
VOID  dd_xdmasnap_set_int_handler(DdXdmasnap *self, kuchar ch, VOID (*intHandler)(VOID))
{
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return;
	}
#endif
	S_CTRL[ch].intHandler = intHandler;
}

/**
 * @brief  Interrupt handler of DMA channel 0 for transfer process is finished.
 * @param  kuchar		ch				Channel number (0 to 3)
 * @return VOID
 */
VOID  dd_xdmasnap_int_handler(DdXdmasnap *self, kuchar ch)
{
	DDIM_USER_ER ercd;
	kushort status;
	VP_CALLBACK handler;

#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return;
	}
#endif
	// To give the user the content of the IS of XDDSD register
	status = IO_XDMACS.CH[ch].XDDSD.bit.IS;
	S_STOP_STATUS[ch] = status;
	// Stop Status clear
	IO_XDMACS.CH[ch].XDDSD.bit.IS = DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_NONE;
	// DMA Stop
	IO_XDMACS.CH[ch].XDDES.bit.CE = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
	Dd_ARM_Dsb_Pou();
	
	handler = S_CTRL[ch].intHandler;
	
	if (handler != NULL) {
		(*handler)(ch, &status);
	}

	if( status != DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_NONE ){
		switch(ch){
			case 0:
				ercd = DDIM_User_Set_Flg(FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH0);
				break;
			case 1:
				ercd = DDIM_User_Set_Flg(FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH1);
				break;
			case 2:
				ercd = DDIM_User_Set_Flg(FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH2);
				break;
			case 3:
				ercd = DDIM_User_Set_Flg(FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH3);
				break;
			default:
				ercd = -1;
				break;
		}
	}
	else{
		ercd = D_DDIM_USER_E_OK;
	}
	
	if( ercd != D_DDIM_USER_E_OK ){
		Ddim_Print(("I:DDIM_User_Set_Flg error. ercd = %d\n", ercd));
	}
}

// CO_DDIM_UTILITY_USE
#ifdef CO_DDIM_UTILITY_USE
/**
 * @brief  DMA Copy Sync for SDRAM
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  kulong		srcAddr		source address
 * @param  kulong		dstAddr		destination address
 * @param  kulong		size			Copy size
 * @param  kint32		waitMode		DMA end wait mode
 * @return kint32		D_DDIM_OK
 */
kint32 dd_xdmasnap_copy_sdram_sync(DdXdmasnap *self, kuchar ch, kulong srcAddr, kulong dstAddr, kulong size, kuint32 waitMode)
{
	kint32              ret;
	kushort             status = 0;
	TDdXdmasnapCtrl dmaCtrlTrns;
	TDdXdmasnapCommon dmaCommon;
	
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if(( srcAddr == 0 ) || ( dstAddr == 0 )){
		Ddim_Assertion(("XDMASNAP: input param error. [addr] = 0\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( size == 0 ){
		Ddim_Assertion(("XDMASNAP: input param error. [size] = 0\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if(( waitMode != DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU ) && ( waitMode != DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT )){
		Ddim_Assertion(("XDMASNAP: input param error. [waitMode] = %x\n", waitMode));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	// Check transfer size
	if((( srcAddr & 0x07) == 0 ) && ((dstAddr & 0x07) == 0 ) && ( (size & 0x07) == 0) ){
		dmaCtrlTrns.config1.bit.sBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_DOUBLEWORD;
		dmaCtrlTrns.config1.bit.dBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_DOUBLEWORD;
	}
	else if(( (srcAddr & 0x03) == 0 ) && ( (dstAddr & 0x03) == 0 ) && ( (size & 0x03) == 0 )){
		dmaCtrlTrns.config1.bit.sBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_WORD;
		dmaCtrlTrns.config1.bit.dBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_WORD;
	}
	else if(( (srcAddr & 0x01) == 0 ) && ( (dstAddr & 0x01) == 0 ) && ( (size & 0x01) == 0 )){
		dmaCtrlTrns.config1.bit.sBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_HALFWORD;
		dmaCtrlTrns.config1.bit.dBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_HALFWORD;
	}
	else{
		dmaCtrlTrns.config1.bit.sBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_BYTE;
		dmaCtrlTrns.config1.bit.dBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_BYTE;
	}
	
	// Parameter Setting
	dmaCtrlTrns.trnsSize       = size;
	dmaCtrlTrns.srcAddr        = srcAddr;
	dmaCtrlTrns.dstAddr        = dstAddr;
	dmaCtrlTrns.intHandler     = NULL;
	
	dmaCtrlTrns.config1.bit.sRL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
	dmaCtrlTrns.config1.bit.sAF = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
	dmaCtrlTrns.config1.bit.sBL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
	dmaCtrlTrns.config1.bit.dRL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
	dmaCtrlTrns.config1.bit.dAF = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
	dmaCtrlTrns.config1.bit.dBL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
	
	if( waitMode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT ){
		dmaCtrlTrns.config1.bit.tI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_ENABLE;
		dmaCtrlTrns.config1.bit.eI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_ENABLE;
	}
	else{
		dmaCtrlTrns.config1.bit.tI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_DISABLE;
		dmaCtrlTrns.config1.bit.eI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_DISABLE;
	}
	
	dmaCtrlTrns.config1.bit.aT = DdXdmasnap_D_DD_XDMASNAP_XDDES_AT_SOURCE;
	dmaCtrlTrns.config1.bit.bR = DdXdmasnap_D_DD_XDMASNAP_XDDES_BR_DISABLE;
	dmaCtrlTrns.config1.bit.bT = DdXdmasnap_D_DD_XDMASNAP_XDDES_BT_ENABLE;
	dmaCtrlTrns.config1.bit.sA = DdXdmasnap_D_DD_XDMASNAP_XDDES_SA_ENABLE;
	dmaCtrlTrns.config1.bit.tF = DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_SOFT;
	dmaCtrlTrns.config1.bit.sE = DdXdmasnap_D_DD_XDMASNAP_XDDES_SE_ENABLE;
	dmaCtrlTrns.config2.bit.dCN = DdXdmasnap_D_DD_XDMASNAP_XDDCC_DCN_INVALID;
	dmaCtrlTrns.config2.bit.dCA = 0;
	
	dmaCommon.commonConfig.bit.xE = DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_ENABLE;
	dmaCommon.commonConfig.bit.cP = DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_FIXED;
	
	ret = dd_xdmasnap_open(self, ch,D_DDIM_WAIT_END_TIME);
	if( ret != D_DDIM_OK ){
		Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
		return ret;
	}
	
	ret = dd_xdmasnap_ctrl_common(self, &dmaCommon);
	if( ret != D_DDIM_OK ){
		Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
		return ret;
	}
	
	while(1){
		ret = dd_xdmasnap_ctrl_trns(self, ch, &dmaCtrlTrns);
		if( ret != D_DDIM_OK ){
			Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
			break;
		}
		ret = dd_xdmasnap_start_sync(self, ch, &status, waitMode);
		if( ret != D_DDIM_OK ){
			Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
		}
		break;
	}
	
	ret = dd_xdmasnap_close(self, ch);
	if( ret != D_DDIM_OK ){
		Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
	}
	
	return ret;
}

/**
 * @brief  DMA Copy Async SDRAM
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  kulong		srcAddr		source address
 * @param  kulong		dstAddr		destination address
 * @param  kulong		size			Copy size
 * @param  VP_CALLBACK	intHandler		Callback function pointer
 * @return kint32  		D_DDIM_OK
 */
kint32 dd_xdmasnap_copy_sdram_async(DdXdmasnap *self, kuchar ch, kulong srcAddr, kulong dstAddr, kulong size, VP_CALLBACK intHandler)
{
	kint32              ret;
	TDdXdmasnapCtrl dmaCtrlTrns;
	TDdXdmasnapCommon dmaCommon;
	
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if(( srcAddr == 0 ) || ( dstAddr == 0 )){
		Ddim_Assertion(("XDMASNAP: input param error. [addr] = 0\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( size == 0 ){
		Ddim_Assertion(("XDMASNAP: input param error. [size] = 0\n"));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	// Check transfer size
	if(( (srcAddr & 0x07) == 0 ) && ( (dstAddr & 0x07) == 0 ) && ( (size & 0x07) == 0) ){
		dmaCtrlTrns.config1.bit.sBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_DOUBLEWORD;
		dmaCtrlTrns.config1.bit.dBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_DOUBLEWORD;
	}
	else if(( (srcAddr & 0x03) == 0 ) && ( (dstAddr & 0x03) == 0 ) && ( (size & 0x03) == 0 )){
		dmaCtrlTrns.config1.bit.sBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_WORD;
		dmaCtrlTrns.config1.bit.dBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_WORD;
	}
	else if(( (srcAddr & 0x01) == 0 ) && ( (dstAddr & 0x01) == 0 ) && ( (size & 0x01) == 0 )){
		dmaCtrlTrns.config1.bit.sBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_HALFWORD;
		dmaCtrlTrns.config1.bit.dBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_HALFWORD;
	}
	else{
		dmaCtrlTrns.config1.bit.sBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_BYTE;
		dmaCtrlTrns.config1.bit.dBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_BYTE;
	}
	
	// Parameter Setting
	dmaCtrlTrns.trnsSize       = size;
	dmaCtrlTrns.srcAddr        = srcAddr;
	dmaCtrlTrns.dstAddr        = dstAddr;
	dmaCtrlTrns.intHandler     = intHandler;
	
	dmaCtrlTrns.config1.bit.sRL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
	dmaCtrlTrns.config1.bit.sAF = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
	dmaCtrlTrns.config1.bit.sBL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
	dmaCtrlTrns.config1.bit.dRL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
	dmaCtrlTrns.config1.bit.dAF = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
	dmaCtrlTrns.config1.bit.dBL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
	
	dmaCtrlTrns.config1.bit.tI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_ENABLE;
	dmaCtrlTrns.config1.bit.eI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_ENABLE;
	
	dmaCtrlTrns.config1.bit.aT = DdXdmasnap_D_DD_XDMASNAP_XDDES_AT_SOURCE;
	dmaCtrlTrns.config1.bit.bR = DdXdmasnap_D_DD_XDMASNAP_XDDES_BR_DISABLE;
	dmaCtrlTrns.config1.bit.bT = DdXdmasnap_D_DD_XDMASNAP_XDDES_BT_ENABLE;
	dmaCtrlTrns.config1.bit.sA = DdXdmasnap_D_DD_XDMASNAP_XDDES_SA_ENABLE;
	dmaCtrlTrns.config1.bit.tF = DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_SOFT;
	dmaCtrlTrns.config1.bit.sE = DdXdmasnap_D_DD_XDMASNAP_XDDES_SE_ENABLE;
	dmaCtrlTrns.config2.bit.dCN = DdXdmasnap_D_DD_XDMASNAP_XDDCC_DCN_INVALID;
	dmaCtrlTrns.config2.bit.dCA = 0;
	
	dmaCommon.commonConfig.bit.xE = DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_ENABLE;
	dmaCommon.commonConfig.bit.cP = DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_FIXED;
	
	ret = dd_xdmasnap_ctrl_common(self, &dmaCommon);
	if( ret != D_DDIM_OK ){
		Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
		return ret;
	}
	
	ret = dd_xdmasnap_ctrl_trns(self, ch, &dmaCtrlTrns);
	if( ret != D_DDIM_OK ){
		Ddim_Print(("DMA Util Copy Async. Ctrl ERR : ret=0x%x\n", ret));
		return ret;
	}
	
	ret = dd_xdmasnap_start_async(self, ch);
	if( ret != D_DDIM_OK ){
		Ddim_Print(("DMA Util Copy Async. Start ERR : ret=0x%x\n", ret));
		return ret;
	}
	
	return ret;
}
#endif

DdXdmasnap *dd_xdmasnap_new(void)
{
	DdXdmasnap* self = k_object_new_with_private(DD_TYPE_XDMASNAP,sizeof(DdXdmasnapPrivate));
	return self;
}
