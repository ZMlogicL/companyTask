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

#include "ddarm.h"
#include "arm.h"
#include "ddxdmasnap.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdXdmasnap, dd_xdmasnap);
#define DD_XDMASNAP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdXdmasnapPrivate, DD_TYPE_XDMASNAP))

// Sync Processing
#define D_DD_XDMASNAP_SYNC			(0)
// Async Processing
#define D_DD_XDMASNAP_ASYNC			(1)

struct _DdXdmasnapPrivate
{
	// DMA Register Info
	volatile TDdXdmasnapCtrl snapCtrl[DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX];
	volatile kushort 		 snapStopStatus[DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX];
	volatile kint32 		 waitEndTime[DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX];
	DdimUserCustom 			 *ddimUserCustom;
};

// Spin Lock
static kulong S_XDMASNAP_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64))) = 0;

static void dd_xdmasnap_constructor(DdXdmasnap *self)
{
	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);
	priv->ddimUserCustom = ddim_user_custom_new();
}

static void dd_xdmasnap_destructor(DdXdmasnap *self)
{
	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);
	if(priv->ddimUserCustom){
		k_object_unref(priv->ddimUserCustom);
		priv->ddimUserCustom = NULL;
	}
}

/**
 * @brief  DMA wait end.
 */
static kint32 ddXdmasnapWaitEnd(DdXdmasnap *self, kuchar ch, kushort *const status, kuint32 waitMode)
{
	DdimUserFlgptn flgPtn;
	DdimUserEr ercd = 0;

	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);
	// CPU Polling (no use interrupt)
	if( waitMode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU ){
		while(( ioXdmacs.ch[ch].xddsd.bit.ts == DdXdmasnap_D_DD_XDMASNAP_XDDSD_TS_RUNNING ) && ( priv->snapStopStatus[ch] == 0 )){
			;	// It waits until completing it
		}
		
		if( priv->snapStopStatus[ch] == 0 ){
			*status = ioXdmacs.ch[ch].xddsd.bit.is;
			// Stop Status clear
			ioXdmacs.ch[ch].xddsd.bit.is = 0x0;
			// DMA Stop
			ioXdmacs.ch[ch].xddes.bit.ce = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
		}
		else{
			*status = priv->snapStopStatus[ch];
			priv->snapStopStatus[ch] = 0;
		}
	}
	// EVENT (use interrupt)
	else{
		switch(ch){
			case 0:
				ercd = ddim_user_custom_twai_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH0, DdimUserCustom_TWF_ORW, &flgPtn, priv->waitEndTime[ch]);
				break;
			case 1:
				ercd = ddim_user_custom_twai_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH1, DdimUserCustom_TWF_ORW, &flgPtn, priv->waitEndTime[ch]);
				break;
			case 2:
				ercd = ddim_user_custom_twai_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH2, DdimUserCustom_TWF_ORW, &flgPtn, priv->waitEndTime[ch]);
				break;
			case 3:
				ercd = ddim_user_custom_twai_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH3, DdimUserCustom_TWF_ORW, &flgPtn, priv->waitEndTime[ch]);
				break;
			default:
				break;
		}
		
		*status = priv->snapStopStatus[ch];
		priv->snapStopStatus[ch] = 0;
	}
	
	if( ercd == DdimUserCustom_E_TMOUT ){
		Ddim_Print(("DMA error. timeout!\n"));
		return DdXdmasnap_D_DD_XDMASNAP_TIMEOUT_ERR;
	}
	
	if( ercd != DdimUserCustom_E_OK ){
		Ddim_Print(("DMA error. system error!\n"));
		return DdXdmasnap_D_DD_XDMASNAP_SYSTEM_ERR;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  DMA start.
 */
static kint32 ddXdmasnapStart(DdXdmasnap *self, kuchar ch, kushort* const status, kuint32 waitMode, kuint32 sync)
{
	kint32 ret = D_DDIM_OK;
	IoXdmacXdsac xdsac;
	IoXdmacXddac xddac;
	IoXdmacXddes xddes;

	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);
	// DMA Enable
	if( ioXdmacs.xdacs.bit.xe == DdXdmasnap_D_DD_XDMASNAP_XDACS_XS_NOTACTIVE ){
		return DdXdmasnap_D_DD_XDMASNAP_SYSTEM_ERR;
	}
	
	if( waitMode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT ){
		// Error Interrupt Enable
		priv->snapCtrl[ch].config1.bit.eI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_ENABLE;
		// Completion Interrupt Enable
		priv->snapCtrl[ch].config1.bit.tI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_ENABLE;
	}
	
	priv->snapStopStatus[ch] = 0;
	
	// xdsac
	xdsac.word = ioXdmacs.ch[ch].xdsac.word;
	xdsac.bit.srl = priv->snapCtrl[ch].config1.bit.sRL;
	xdsac.bit.saf = priv->snapCtrl[ch].config1.bit.sAF;
	xdsac.bit.sbl = priv->snapCtrl[ch].config1.bit.sBL;
	xdsac.bit.sbs = priv->snapCtrl[ch].config1.bit.sBS;
	ioXdmacs.ch[ch].xdsac.word = xdsac.word;
	
	// xddac
	xddac.word = ioXdmacs.ch[ch].xddac.word;
	xddac.bit.drl = priv->snapCtrl[ch].config1.bit.dRL;
	xddac.bit.daf = priv->snapCtrl[ch].config1.bit.dAF;
	xddac.bit.dbl = priv->snapCtrl[ch].config1.bit.dBL;
	xddac.bit.dbs = priv->snapCtrl[ch].config1.bit.dBS;
	ioXdmacs.ch[ch].xddac.word = xddac.word;
	
	// xddes
	xddes.word = ioXdmacs.ch[ch].xddes.word;
	xddes.bit.ti = priv->snapCtrl[ch].config1.bit.tI;
	xddes.bit.ei = priv->snapCtrl[ch].config1.bit.eI;
	xddes.bit.at = priv->snapCtrl[ch].config1.bit.aT;
	xddes.bit.br = priv->snapCtrl[ch].config1.bit.bR;
	xddes.bit.bt = priv->snapCtrl[ch].config1.bit.bT;
	xddes.bit.sa = priv->snapCtrl[ch].config1.bit.sA;
	xddes.bit.tf = priv->snapCtrl[ch].config1.bit.tF;
	xddes.bit.se = priv->snapCtrl[ch].config1.bit.sE;
	ioXdmacs.ch[ch].xddes.word = xddes.word;
	
	ioXdmacs.ch[ch].xddcc = priv->snapCtrl[ch].config2.word;
	
	ioXdmacs.ch[ch].xdtbc = priv->snapCtrl[ch].trnsSize - 1;
	// DMA Source Address register set
	ioXdmacs.ch[ch].xdssa = priv->snapCtrl[ch].srcAddr;
	// DMA Destination Address register set
	ioXdmacs.ch[ch].xddsa = priv->snapCtrl[ch].dstAddr;
	
	if( waitMode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT ){
		switch(ch){
			case 0:
				ddim_user_custom_clr_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_XDMASNAP, ~DdXdmasnap_D_DD_XDMASNAP_FLG_CH0);
				break;
			case 1:
				ddim_user_custom_clr_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_XDMASNAP, ~DdXdmasnap_D_DD_XDMASNAP_FLG_CH1);
				break;
			case 2:
				ddim_user_custom_clr_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_XDMASNAP, ~DdXdmasnap_D_DD_XDMASNAP_FLG_CH2);
				break;
			case 3:
				ddim_user_custom_clr_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_XDMASNAP, ~DdXdmasnap_D_DD_XDMASNAP_FLG_CH3);
				break;
			default:
				break;
		}
	}
	
	ioXdmacs.ch[ch].xddes.bit.ce = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_ENABLE;
	DD_ARM_DSB_POU();
	
	// Sync Processing
	if( sync == D_DD_XDMASNAP_SYNC ){
		ret = ddXdmasnapWaitEnd(self, ch, status, waitMode);
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
	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
	if( tmout < DdimUserCustom_SEM_WAIT_FEVR ){
		Ddim_Assertion(("Dd_XDMASNAP_Open: input param error. tmout = %d\n", tmout));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	DdimUserEr ercd = 0;
	
	if( DdimUserCustom_SEM_WAIT_POL == tmout ){
		// pol_sem()
		ercd = ddim_user_custom_pol_sem(priv->ddimUserCustom, SID_DD_XDMASNAP(ch));
	}else{
		// twai_sem()
		ercd = ddim_user_custom_twai_sem(priv->ddimUserCustom, SID_DD_XDMASNAP(ch), (DdimUserTmo)tmout);
	}
	
	if( DdimUserCustom_E_OK != ercd ){
		if( DdimUserCustom_E_TMOUT == ercd ){
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
	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR;
	}
#endif
	DdimUserEr ercd = 0;
	
	// Global variable is clear
	priv->snapCtrl[ch].config1.word = 0;
	priv->snapCtrl[ch].config2.word = 0;
	priv->snapCtrl[ch].srcAddr      = 0;
	priv->snapCtrl[ch].dstAddr      = 0;
	priv->snapCtrl[ch].trnsSize     = 0;
	priv->snapCtrl[ch].intHandler   = NULL;
	// sig_sem()
	ercd = ddim_user_custom_sig_sem(priv->ddimUserCustom, SID_DD_XDMASNAP(ch));
	if( DdimUserCustom_E_OK != ercd ){
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
	DD_ARM_CRITICAL_SECTION_START(S_XDMASNAP_SPIN_LOCK);
	
	// The value is set to an external variable
	ioXdmacs.xdacs.bit.cp = dmaCommon->commonConfig.bit.cP;
	ioXdmacs.xdacs.bit.xe = dmaCommon->commonConfig.bit.xE;
	
	// SpinUnLock
	DD_ARM_CRITICAL_SECTION_END(S_XDMASNAP_SPIN_LOCK);
	
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
	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);

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
	priv->snapCtrl[ch].config1.word = dmaCtrlTrans->config1.word;
	priv->snapCtrl[ch].config2.word = 0;
	priv->snapCtrl[ch].config2.bit.dCA = dmaCtrlTrans->config2.bit.dCA;
	priv->snapCtrl[ch].config2.bit.dCN = dmaCtrlTrans->config2.bit.dCN;
	
	priv->snapCtrl[ch].trnsSize       = dmaCtrlTrans->trnsSize;
	priv->snapCtrl[ch].srcAddr        = dmaCtrlTrans->srcAddr;
	priv->snapCtrl[ch].dstAddr        = dmaCtrlTrans->dstAddr;
	priv->snapCtrl[ch].intHandler     = dmaCtrlTrans->intHandler;
	
	priv->waitEndTime[ch] = D_DDIM_WAIT_END_TIME;
	
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
	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);

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
	priv->snapCtrl[ch].trnsSize = dmaTrnsSize->trnsSize;
	priv->snapCtrl[ch].srcAddr  = dmaTrnsSize->srcAddr;
	priv->snapCtrl[ch].dstAddr  = dmaTrnsSize->dstAddr;
	ioXdmacs.ch[ch].xdssa = priv->snapCtrl[ch].srcAddr;
	ioXdmacs.ch[ch].xddsa = priv->snapCtrl[ch].dstAddr;
	
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
	ret = ddXdmasnapStart(self, ch, status, waitMode, D_DD_XDMASNAP_SYNC);
	
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
	ddXdmasnapStart(self, ch, &status, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT, D_DD_XDMASNAP_ASYNC);
	
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
	ioXdmacs.ch[ch].xddes.bit.ce = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
	DD_ARM_DSB_POU();
	
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
	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);

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
	priv->waitEndTime[ch] = waitTime;
	
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
	ret = ddXdmasnapWaitEnd(self, ch, status, waitMode);
	
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
	ioXdmacs.ch[ch].xddsd.bit.is = DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_NONE;
	
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
	*xdmacStatus = ioXdmacs.xdacs.bit.xs;
	*transferStatus = ioXdmacs.ch[ch].xddsd.bit.ts;
	*interruptStatus = ioXdmacs.ch[ch].xddsd.bit.is;
	
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
	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif
	return priv->snapCtrl[ch].trnsSize - (ioXdmacs.ch[ch].xdtbc + 1);
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
	return ioXdmacs.ch[ch].xdssa;
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
	return ioXdmacs.ch[ch].xddsa;
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
	DD_ARM_CRITICAL_SECTION_START(S_XDMASNAP_SPIN_LOCK);
	
	ioXdmacs.xdacs.bit.lp = lowPower;
	
	// SpinUnLock
	DD_ARM_CRITICAL_SECTION_END(S_XDMASNAP_SPIN_LOCK);
	
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
	ioXdmacs.ch[ch].xddpc.bit.sp = protectCode;
	
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
	ioXdmacs.ch[ch].xddpc.bit.dp = protectCode;
	
	return D_DDIM_OK;
}

/**
 * @brief  The operation of All DMA channel is stopped.
 */
void	dd_xdmasnap_stop_all_ch(DdXdmasnap *self)
{
	ioXdmacs.ch[0].xddes.bit.ce = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
	ioXdmacs.ch[1].xddes.bit.ce = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
	ioXdmacs.ch[2].xddes.bit.ce = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
	ioXdmacs.ch[3].xddes.bit.ce = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
	
	return;
}

/**
 * @brief  Set DMA Interrupt Handler.
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  void			intHandler		Interrupt handler
 * @return void
 */
void  dd_xdmasnap_set_int_handler(DdXdmasnap *self, kuchar ch, void (*intHandler)(void))
{
	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return;
	}
#endif
	priv->snapCtrl[ch].intHandler = intHandler;
}

/**
 * @brief  Interrupt handler of DMA channel 0 for transfer process is finished.
 * @param  kuchar		ch				Channel number (0 to 3)
 * @return void
 */
void  dd_xdmasnap_int_handler(DdXdmasnap *self, kuchar ch)
{
	DdimUserEr ercd;
	kushort status;
	VpCallbackFunc handler;

	DdXdmasnapPrivate *priv = DD_XDMASNAP_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if( ch >= DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX ){
		Ddim_Assertion(("XDMASNAP: input param error. [ch] = %x\n", ch));
		return;
	}
#endif
	// To give the user the content of the IS of xddsd register
	status = ioXdmacs.ch[ch].xddsd.bit.is;
	priv->snapStopStatus[ch] = status;
	// Stop Status clear
	ioXdmacs.ch[ch].xddsd.bit.is = DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_NONE;
	// DMA Stop
	ioXdmacs.ch[ch].xddes.bit.ce = DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE;
	DD_ARM_DSB_POU();
	
	handler = priv->snapCtrl[ch].intHandler;
	
	if (handler != NULL) {
		(*handler)(ch, &status);
	}

	if( status != DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_NONE ){
		switch(ch){
			case 0:
				ercd = DDIM_User_Set_Flg(DdimUserCustom_FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH0);
				break;
			case 1:
				ercd = DDIM_User_Set_Flg(DdimUserCustom_FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH1);
				break;
			case 2:
				ercd = DDIM_User_Set_Flg(DdimUserCustom_FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH2);
				break;
			case 3:
				ercd = DDIM_User_Set_Flg(DdimUserCustom_FID_DD_XDMASNAP, DdXdmasnap_D_DD_XDMASNAP_FLG_CH3);
				break;
			default:
				ercd = -1;
				break;
		}
	}else{
		ercd = DdimUserCustom_E_OK;
	}
	
	if( ercd != DdimUserCustom_E_OK ){
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
	}else if(( (srcAddr & 0x03) == 0 ) && ( (dstAddr & 0x03) == 0 ) && ( (size & 0x03) == 0 )){
		dmaCtrlTrns.config1.bit.sBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_WORD;
		dmaCtrlTrns.config1.bit.dBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_WORD;
	}else if(( (srcAddr & 0x01) == 0 ) && ( (dstAddr & 0x01) == 0 ) && ( (size & 0x01) == 0 )){
		dmaCtrlTrns.config1.bit.sBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_HALFWORD;
		dmaCtrlTrns.config1.bit.dBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_HALFWORD;
	}else{
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
 * @param  VpCallbackFunc	intHandler		Callback function pointer
 * @return kint32  		D_DDIM_OK
 */
kint32 dd_xdmasnap_copy_sdram_async(DdXdmasnap *self, kuchar ch, kulong srcAddr, kulong dstAddr, kulong size, VpCallbackFunc intHandler)
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
	}else if(( (srcAddr & 0x03) == 0 ) && ( (dstAddr & 0x03) == 0 ) && ( (size & 0x03) == 0 )){
		dmaCtrlTrns.config1.bit.sBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_WORD;
		dmaCtrlTrns.config1.bit.dBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_WORD;
	}else if(( (srcAddr & 0x01) == 0 ) && ( (dstAddr & 0x01) == 0 ) && ( (size & 0x01) == 0 )){
		dmaCtrlTrns.config1.bit.sBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_HALFWORD;
		dmaCtrlTrns.config1.bit.dBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_HALFWORD;
	}else{
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
