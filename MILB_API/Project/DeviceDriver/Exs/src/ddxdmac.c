/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :周洪
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、XDMA driver
*2、将dd_xdmac.c更名为ddxdmac.c类
*@version
*1.0.0 2020年06月开始开发
*/

#include "ddarm.h"
#include "arm.h"
//#include "dd_exs.h"
#include "ddexs.h"
#include "ddexsbranch.h"
#include "kxdmac.h"
#include "ddxdmac.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdXdmac, dd_xdmac);
#define DD_XDMAC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), DdXdmacPrivate, DD_TYPE_XDMAC))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define C_DD_XDMAC_SYNC				(0)		/* Sync Processing */
#define C_DD_XDMAC_ASYNC			(1)		/* Async Processing */

struct _DdXdmacPrivate
{
    int 											a;
	volatile TDdXdmacCtrl 		gDdXdmacCtrl[DdXdmac_CH_NUM_MAX];
	volatile kushort 					gDdXdmacStopStatus[DdXdmac_CH_NUM_MAX];
	volatile kint32 					gDdXdmacWaitEndTime[DdXdmac_CH_NUM_MAX];
	DdExs    									*ddExs;
    DdimUserCustom				*ddimUserCustom;
   //TODO: ddim_user_custom.c类中

	#ifdef CO_ACT_CLOCK
	volatile kuchar 					gDdXdmacClkCtrlCnt;
	#endif	// CO_ACT_CLOCK

};

///*----------------------------------------------------------------------*/
///* Global Data															*/
///*----------------------------------------------------------------------*/
//static volatile TDdXdmacCtrl gDD_XDMAC_Ctrl[DdXdmac_CH_NUM_MAX];		// DMA Register Info
//static volatile kushort gDD_XDMAC_Stop_Status[DdXdmac_CH_NUM_MAX];
//static volatile kint32 gDD_XDMAC_Wait_End_Time[DdXdmac_CH_NUM_MAX];

// Spin Lock
static kulong S_DD_XDMAC_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64))) = 0;

/*----------------------------------------------------------------------*/
/* DECLS																		*/
/*----------------------------------------------------------------------*/
#ifdef CO_ACT_CLOCK
static void ddXdmacStartClock(DdXdmac *self);
static void ddXdmacStopClock(DdXdmac *self);
#endif			// CO_ACT_CLOCK
static kint32 ddXdmacWaitEnd(DdXdmac *self, kuchar ch, kushort* const status, kuint32 waitMode);
static kint32 ddXdmacStart(DdXdmac *self, kuchar ch, kushort* const status, kuint32 waitMode, kuint32 sync);

static void dd_xdmac_constructor(DdXdmac *self)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
    priv->a = 0;
    priv->ddExs = dd_exs_get();
    priv->ddimUserCustom = ddim_user_custom_get();
#ifdef CO_ACT_CLOCK
    priv->gDdXdmacClkCtrlCnt = 0;
	#endif	// CO_ACT_CLOCK
}

static void dd_xdmac_destructor(DdXdmac *self)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
    if(priv->ddExs)
    {
        k_object_unref(priv->ddExs);
        priv->ddExs = NULL;
    }
    if(priv->ddimUserCustom)
     {
         k_object_unref(priv->ddimUserCustom);
         priv->ddimUserCustom = NULL;
     }
}

/*----------------------------------------------------------------------*/
/* IMPL																		*/
/*----------------------------------------------------------------------*/
#ifdef CO_ACT_CLOCK
/**
Control Clock Stop to start clock.<br>
*/
static void ddXdmacStartClock(DdXdmac *self)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
	DD_ARM_CRITICAL_SECTION_START(S_DD_XDMAC_SPIN_LOCK);

	priv->gDdXdmacClkCtrlCnt++;
	if (priv->gDdXdmacClkCtrlCnt == 1){
		if ((DdExsBranch_GET_XDMAC_LOWPOWER_CTL_CACTIVE() == 0)	&&
			(DdExsBranch_GET_XDMAC_LOWPOWER_CTL_CSYSACK() == 0)	){

			dd_exs_set_xdmac_bus_clock_stop_ctrl(priv->ddExs, 0);
			DD_ARM_DSB_POU();

			dd_exs_set_xdmac_lowpower_ctl_csysreq(priv->ddExs, 1);
			DD_ARM_DSB_POU();

			if (DdExsBranch_GET_XDMAC_LOWPOWER_CTL_CACTIVE() != 1){
				DriverCommon_DDIM_PRINT(("[XDMAC]CLK ON Error. cActive=0\n"));
			}

			if (DdExsBranch_GET_XDMAC_LOWPOWER_CTL_CSYSACK() != 1){
				DriverCommon_DDIM_PRINT(("[XDMAC]CLK ON Error. csysAck=0\n"));
			}

			ioXdmac.xdacs.bit.lp = DdXdmac_XDACS_LP_DISABLE;
		}
	}

	DD_ARM_CRITICAL_SECTION_END(S_DD_XDMAC_SPIN_LOCK);
}

/**
Control Clock Stop to stop clock.
*/
static void ddXdmacStopClock(DdXdmac *self)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
	DD_ARM_CRITICAL_SECTION_START(S_DD_XDMAC_SPIN_LOCK);

	if (0 < priv->gDdXdmacClkCtrlCnt){
		priv->gDdXdmacClkCtrlCnt--;
	}
	if (0 == priv->gDdXdmacClkCtrlCnt){
		if ((DdExsBranch_GET_XDMAC_LOWPOWER_CTL_CACTIVE() == 1)	&&
			(DdExsBranch_GET_XDMAC_LOWPOWER_CTL_CSYSACK() == 1)	){

			ioXdmac.xdacs.bit.lp = DdXdmac_XDACS_LP_ENABLE;
			DD_ARM_DSB_POU();

			dd_exs_set_xdmac_lowpower_ctl_csysreq(priv->ddExs, 0);
			DD_ARM_DSB_POU();

			if (DdExsBranch_GET_XDMAC_LOWPOWER_CTL_CACTIVE() != 0){
				DriverCommon_DDIM_PRINT(("[XDMAC]CLK OFF Error. cActive=1\n"));
			}

			if (DdExsBranch_GET_XDMAC_LOWPOWER_CTL_CSYSACK() != 0){
				DriverCommon_DDIM_PRINT(("[XDMAC]CLK OFF Error. csysAck=1\n"));
			}

			dd_exs_set_xdmac_bus_clock_stop_ctrl(priv->ddExs, 1);
		}
	}

	DD_ARM_CRITICAL_SECTION_END(S_DD_XDMAC_SPIN_LOCK);
}
#endif	// CO_ACT_CLOCK

/**
 * @brief  DMA wait end.
 */
static kint32 ddXdmacWaitEnd(DdXdmac *self, kuchar ch, kushort* const status, kuint32 waitMode)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
	DdimUserCustom_FLGPTN flgPtn;
	DdimUserCustom_ER ercd = 0;

	// CPU Polling (no use interrupt)
	if(waitMode == DdXdmac_WAITMODE_CPU){
		while((ioXdmac.ch[ch].xddsd.bit.ts == DdXdmac_XDDSD_TS_RUNNING) && (priv->gDdXdmacStopStatus[ch] == 0)){
			;	// It waits until completing it
		}

		if(priv->gDdXdmacStopStatus[ch] == 0){
			*status = ioXdmac.ch[ch].xddsd.bit.is;
			ioXdmac.ch[ch].xddsd.bit.is = 0x0;		// Stop Status clear
			ioXdmac.ch[ch].xddes.bit.ce = DdXdmac_XDDES_CE_DISABLE;			// DMA Stop
		}
		else{
			*status = priv->gDdXdmacStopStatus[ch];
			priv->gDdXdmacStopStatus[ch] = 0;
		}
	}
	// EVENT (use interrupt)
	else{
		switch(ch){
			case 0:
				ercd = ddim_user_custom_twai_flg(priv->ddimUserCustom, FID_DD_XDMAC, DdXdmac_FLG_CH0,\
						D_DDIM_USER_TWF_ORW, &flgPtn, priv->gDdXdmacWaitEndTime[ch]);
				break;
			case 1:
				ercd = ddim_user_custom_twai_flg(priv->ddimUserCustom, FID_DD_XDMAC, DdXdmac_FLG_CH1,\
						D_DDIM_USER_TWF_ORW, &flgPtn, priv->gDdXdmacWaitEndTime[ch]);
				break;
			case 2:
				ercd = ddim_user_custom_twai_flg(priv->ddimUserCustom, FID_DD_XDMAC, DdXdmac_FLG_CH2,\
						D_DDIM_USER_TWF_ORW, &flgPtn, priv->gDdXdmacWaitEndTime[ch]);
				break;
			case 3:
				ercd = ddim_user_custom_twai_flg(priv->ddimUserCustom, FID_DD_XDMAC, DdXdmac_FLG_CH3,\
						D_DDIM_USER_TWF_ORW, &flgPtn, priv->gDdXdmacWaitEndTime[ch]);
				break;
			default:
				break;
		}

		*status = priv->gDdXdmacStopStatus[ch];
		priv->gDdXdmacStopStatus[ch] = 0;
	}

	if(ercd == DdimUserCustom_E_TMOUT){
		DriverCommon_DDIM_PRINT(("DMA error. timeout!\n"));
		return DdXdmac_TIMEOUT_ERR;
	}

	if(ercd != DdimUserCustom_E_OK){
		DriverCommon_DDIM_PRINT(("DMA error. system error!\n"));
		return DdXdmac_CH_SYSTEM_ERR;
	}

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  DMA start.
 */
static kint32 ddXdmacStart(DdXdmac *self, kuchar ch, kushort* const status, kuint32 waitMode, kuint32 sync)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
	kint32 ret = DriverCommon_DDIM_OK;
	IoXdmacXdsac xdsac;
	IoXdmacXddac xddac;
	IoXdmacXddes xddes;

	// DMA Enable
	if(ioXdmac.xdacs.bit.xe == DdXdmac_XDACS_XS_NOTACTIVE){
		return DdXdmac_CH_SYSTEM_ERR;
	}

	if(waitMode == DdXdmac_WAITMODE_EVENT){
		priv->gDdXdmacCtrl[ch].configOne.bit.eI = DdXdmac_XDDES_EI_ENABLE;				// Error Interrupt Enable
		priv->gDdXdmacCtrl[ch].configOne.bit.tI = DdXdmac_XDDES_TI_ENABLE;				// Completion Interrupt Enable
	}

	priv->gDdXdmacStopStatus[ch] = 0;

	// XDSAC
	xdsac.word = ioXdmac.ch[ch].xdsac.word;
	xdsac.bit.srl = priv->gDdXdmacCtrl[ch].configOne.bit.sRL;
	xdsac.bit.saf = priv->gDdXdmacCtrl[ch].configOne.bit.sAF;
	xdsac.bit.sbl = priv->gDdXdmacCtrl[ch].configOne.bit.sBL;
	xdsac.bit.sbs = priv->gDdXdmacCtrl[ch].configOne.bit.sBS;
	ioXdmac.ch[ch].xdsac.word = xdsac.word;

	// XDDAC
	xddac.word = ioXdmac.ch[ch].xddac.word;
	xddac.bit.drl = priv->gDdXdmacCtrl[ch].configOne.bit.dRL;
	xddac.bit.daf = priv->gDdXdmacCtrl[ch].configOne.bit.dAF;
	xddac.bit.dbl = priv->gDdXdmacCtrl[ch].configOne.bit.dBL;
	xddac.bit.dbs = priv->gDdXdmacCtrl[ch].configOne.bit.dBS;
	ioXdmac.ch[ch].xddac.word = xddac.word;

	// XDDES
	xddes.word = ioXdmac.ch[ch].xddes.word;
	xddes.bit.ti = priv->gDdXdmacCtrl[ch].configOne.bit.tI;
	xddes.bit.ei = priv->gDdXdmacCtrl[ch].configOne.bit.eI;
	xddes.bit.at = priv->gDdXdmacCtrl[ch].configOne.bit.aT;
	xddes.bit.br = priv->gDdXdmacCtrl[ch].configOne.bit.bR;
	xddes.bit.bt = priv->gDdXdmacCtrl[ch].configOne.bit.bT;
	xddes.bit.sa = priv->gDdXdmacCtrl[ch].configOne.bit.sA;
	xddes.bit.tf = priv->gDdXdmacCtrl[ch].configOne.bit.tF;
	xddes.bit.se = priv->gDdXdmacCtrl[ch].configOne.bit.sE;
	ioXdmac.ch[ch].xddes.word = xddes.word;

	ioXdmac.ch[ch].xddcc = priv->gDdXdmacCtrl[ch].configTwo.word;

	ioXdmac.ch[ch].xdtbc = priv->gDdXdmacCtrl[ch].trnsSize - 1;

	ioXdmac.ch[ch].xdssa = priv->gDdXdmacCtrl[ch].srcAddr;		// DMA Source Address register set
	ioXdmac.ch[ch].xddsa = priv->gDdXdmacCtrl[ch].dstAddr;		// DMA Destination Address register set

	if(waitMode == DdXdmac_WAITMODE_EVENT){
		switch(ch){
			case 0:
				ddim_user_custom_clr_flg(priv->ddimUserCustom, FID_DD_XDMAC, ~DdXdmac_FLG_CH0);
				break;
			case 1:
				ddim_user_custom_clr_flg(priv->ddimUserCustom, FID_DD_XDMAC, ~DdXdmac_FLG_CH1);
				break;
			case 2:
				ddim_user_custom_clr_flg(priv->ddimUserCustom, FID_DD_XDMAC, ~DdXdmac_FLG_CH2);
				break;
			case 3:
				ddim_user_custom_clr_flg(priv->ddimUserCustom, FID_DD_XDMAC, ~DdXdmac_FLG_CH3);
				break;
			default:
				break;
		}
	}

	ioXdmac.ch[ch].xddes.bit.ce = DdXdmac_XDDES_CE_ENABLE;
	DD_ARM_DSB_POU();

	// Sync Processing
	if(sync == C_DD_XDMAC_SYNC){
		ret = ddXdmacWaitEnd(self, ch, status, waitMode);
	}

	return ret;
}

/*----------------------------------------------------------------------*/
/* PUBLIC(公有函数接口实现)														*/
/*----------------------------------------------------------------------*/
/**
 * @brief  Execute exclusive control for designated DMA channel.
 * @param  kint32	tmout
 * @param  kuchar	ch	Channel number (0 to 3)
 * @return kint32 	DriverCommon_DDIM_OK / DdXdmac_EXC_LOCK_NG / DdXdmac_INPUT_PARAM_ERR / DdXdmac_SEM_TIMEOUT / DdXdmac_SEM_NG
 */
kint32 dd_xdmac_open(DdXdmac *self, kuchar ch, kint32 tmout)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(tmout < D_DDIM_USER_SEM_WAIT_FEVR){
		DriverCommon_DDIM_ASSERTION(("Dd_XDMAC_Open: input param error. tmout = %d\n", tmout));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif
	DdimUserCustom_ER ercd = 0;

	if(DdimUserCustom_SEM_WAIT_POL == tmout){
		ercd = ddim_user_custom_pol_sem(priv->ddimUserCustom, SID_DD_XDMAC(ch));				// pol_sem()
	}
	else{
		ercd = ddim_user_custom_twai_sem(priv->ddimUserCustom, SID_DD_XDMAC(ch), (DdimUserCustom_TMO)tmout);	// twai_sem()
	}

	if(DdimUserCustom_E_OK != ercd){
		if(DdimUserCustom_E_TMOUT == ercd){
			return DdXdmac_SEM_TIMEOUT;
		}

		return DdXdmac_SEM_NG;
	}


#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Cancel exclusive control for designated DMA channel.
           When the designated channel is under transferring, stop transfer immediately and cancel lock.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32  DriverCommon_DDIM_OK/DdXdmac_INPUT_PARAM_ERR / DdXdmac_SEM_NG
 */
kint32 dd_xdmac_close(DdXdmac *self, kuchar ch)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif
	DdimUserCustom_ER ercd = 0;

	// Global variable is clear
	priv->gDdXdmacCtrl[ch].configOne.word = 0;
	priv->gDdXdmacCtrl[ch].configTwo.word = 0;
	priv->gDdXdmacCtrl[ch].srcAddr = 0;
	priv->gDdXdmacCtrl[ch].dstAddr = 0;
	priv->gDdXdmacCtrl[ch].trnsSize = 0;
	priv->gDdXdmacCtrl[ch].intHandler = NULL;

	ercd = ddim_user_custom_sig_sem(priv->ddimUserCustom, SID_DD_XDMAC(ch));				// sig_sem()
	if(DdimUserCustom_E_OK != ercd){
		return DdXdmac_SEM_NG;
	}

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Set control data to registers related DMA designated channel.
 * @return kint32	DriverCommon_DDIM_OK / DdXdmac_INPUT_PARAM_ERR
 */
kint32 dd_xdmac_ctrl_common(DdXdmac *self, TDdXdmacCommon const *const dmaCommon)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(dmaCommon == NULL){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [*dma_ctrl] NULL\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	// SpinLock
	DD_ARM_CRITICAL_SECTION_START(S_DD_XDMAC_SPIN_LOCK);

	// The value is set to an external variable
	ioXdmac.xdacs.bit.cp = dmaCommon->commonConfig.bit.cP;
	ioXdmac.xdacs.bit.xe = dmaCommon->commonConfig.bit.xE;

	// SpinUnLock
	DD_ARM_CRITICAL_SECTION_END(S_DD_XDMAC_SPIN_LOCK);

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Set control data to registers related DMA designated channel.
 * @param  kuchar	ch	Channel number (0 to 3)
 * @param  kuchar	dma_ctrl_trans	DMA Transfer setting
 * @return kint32	DriverCommon_DDIM_OK / DdXdmac_INPUT_PARAM_ERR
 */
kint32	dd_xdmac_ctrl_trns(DdXdmac *self, kuchar ch, TDdXdmacCtrl const *const dma_ctrl_trans)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(dma_ctrl_trans == NULL){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [*dma_ctrl_trans] NULL\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(dma_ctrl_trans->trnsSize == 0){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [dma_ctrl_trans->trns_size] Zero\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif
	// The value is set to an external variable
	priv->gDdXdmacCtrl[ch].configOne.word = dma_ctrl_trans->configOne.word;
	priv->gDdXdmacCtrl[ch].configTwo.word = 0;
	priv->gDdXdmacCtrl[ch].configTwo.bit.dCA = dma_ctrl_trans->configTwo.bit.dCA;
	priv->gDdXdmacCtrl[ch].configTwo.bit.dCN = dma_ctrl_trans->configTwo.bit.dCN;

	priv->gDdXdmacCtrl[ch].trnsSize = dma_ctrl_trans->trnsSize;
	priv->gDdXdmacCtrl[ch].srcAddr = dma_ctrl_trans->srcAddr;
	priv->gDdXdmacCtrl[ch].dstAddr = dma_ctrl_trans->dstAddr;
	priv->gDdXdmacCtrl[ch].intHandler = dma_ctrl_trans->intHandler;

	priv->gDdXdmacWaitEndTime[ch] = DriverCommon_DDIM_WAIT_END_TIME;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Set translation size to registers related DMA designated channel.
 * @param  kuchar	ch	Channel number (0 to 3)
 * @param  kuchar	dma_trns_size	DMA Transfer size
 * @return kint32	DriverCommon_DDIM_OK / DdXdmac_INPUT_PARAM_ERR
 */
kint32	dd_xdmac_set_trns_size(DdXdmac *self, kuchar ch, TDdXdmacTrnsSize const *const dma_trns_size)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(dma_trns_size == NULL){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [*dma_trns_size] NULL\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(dma_trns_size->trnsSize == 0){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [dma_trns_size->trns_size] Zero\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	priv->gDdXdmacCtrl[ch].trnsSize = dma_trns_size->trnsSize;
	priv->gDdXdmacCtrl[ch].srcAddr = dma_trns_size->srcAddr;
	priv->gDdXdmacCtrl[ch].dstAddr = dma_trns_size->dstAddr;
	ioXdmac.ch[ch].xdssa = priv->gDdXdmacCtrl[ch].srcAddr;
	ioXdmac.ch[ch].xddsa = priv->gDdXdmacCtrl[ch].dstAddr;

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  The operation of DMA of specified ch begins.
 * @param  kuchar			ch			Channel number (0 to 3)
 *         kushort*			status		Channel Status Register pointer
 *         kuint32			waitMode	DMA end wait mode
 * @return kint32			DriverCommon_DDIM_OK / DdXdmac_INPUT_PARAM_ERR / D_DDIM_TIMEOUT / DdXdmac_CH_SYSTEM_ERR
 */
kint32	dd_xdmac_start_sync(DdXdmac *self, kuchar ch, kushort *const status, kuint32 waitMode)
{
	kint32 ret;

#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(status == NULL){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [*status] NULL\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if((waitMode != DdXdmac_WAITMODE_CPU) && (waitMode != DdXdmac_WAITMODE_EVENT)){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [waitMode] = %x\n", waitMode));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	ret = ddXdmacStart(self, ch, status, waitMode, C_DD_XDMAC_SYNC);		// DMA Start

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return ret;
}

/**
 * @brief  The operation of DMA of specified ch begins.
 * @param  kuchar			ch			Channel number (0 to 3)
 * @return kint32			DriverCommon_DDIM_OK / DdXdmac_INPUT_PARAM_ERR
 */
kint32	dd_xdmac_start_async(DdXdmac *self, kuchar ch)
{
	kushort	status;		// dummy

#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	ddXdmacStart(self, ch, &status, DdXdmac_WAITMODE_EVENT, C_DD_XDMAC_ASYNC);	// DMA Start

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  The operation of DMA of specified ch is stopped.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32	DriverCommon_DDIM_OK / DdXdmac_INPUT_PARAM_ERR
 */
kint32	dd_xdmac_stop(DdXdmac *self, kuchar ch)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	ioXdmac.ch[ch].xddes.bit.ce = DdXdmac_XDDES_CE_DISABLE;
	DD_ARM_DSB_POU();

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Wait end time of transfer process of designated channel.
 * @param  kuchar	ch			Channel number (0 to 3)
 *         kint32	waitTime	Wait end time of transfer process
 * @return kint32				DriverCommon_DDIM_OK / DdXdmac_INPUT_PARAM_ERR
 */
kint32 dd_xdmac_set_wait_time(DdXdmac *self, kuchar ch, kint32 waitTime)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(waitTime < DriverCommon_DDIM_WAIT_END_FOREVER){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [waitTime] = %d\n", waitTime));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif
	priv->gDdXdmacWaitEndTime[ch] = waitTime;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Wait end of transfer process of designated channel.
 *         The value of the CSTR register is passed by the out parameter.
 * @param  kuchar	ch			Channel number (0 to 3)
 *         kushort*	status		Channel Status Register pointer
 * @return kint32	DriverCommon_DDIM_OK / DdXdmac_INPUT_PARAM_ERR / D_DDIM_TIMEOUT / DdXdmac_CH_SYSTEM_ERR
 */
kint32 dd_xdmac_wait_end(DdXdmac *self, kuchar ch, kushort* const status, kuint32 waitMode)
{
	kint32 ret;

#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(status == NULL){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [*status] NULL\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if((waitMode != DdXdmac_WAITMODE_CPU) && (waitMode != DdXdmac_WAITMODE_EVENT)){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [waitMode] = %x\n", waitMode));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	ret = ddXdmacWaitEnd(self, ch, status, waitMode);

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return ret;
}

/**
 * @brief  The status of DMA of specified ch is cleared.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32				DriverCommon_DDIM_OK / DdXdmac_INPUT_PARAM_ERR
 */
kint32	dd_xdmac_clear_status(DdXdmac *self, kuchar ch)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	ioXdmac.ch[ch].xddsd.bit.is = DdXdmac_XDDSD_IS_NONE;

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  The error status of DMA of specified ch is collected.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32				DriverCommon_DDIM_OK / DdXdmac_INPUT_PARAM_ERR
 */
kint32	dd_xdmac_get_status(DdXdmac *self, kuchar ch, kushort *const xdmacStatus,\
		kushort *const transferStatus, kushort *const interruptStatus)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(xdmacStatus == NULL){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [*status] NULL\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(transferStatus == NULL){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [*transferStatus] NULL\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(interruptStatus == NULL){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [*interruptStatus] NULL\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	*xdmacStatus = ioXdmac.xdacs.bit.xs;
	*transferStatus = ioXdmac.ch[ch].xddsd.bit.ts;
	*interruptStatus = ioXdmac.ch[ch].xddsd.bit.is;

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return DriverCommon_DDIM_OK;
}

/**
 * @brief   The value of the transferd size of the specified channel is acquired.
 * @param   kuchar		ch		Channel number (0 to 3)
 * @return  kulong				Transferd size of the specified channel
 * @remarks This API forced cancel exclusive control if process is under executing.
 */
kulong	dd_xdmac_get_trns_size(DdXdmac *self, kuchar ch)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
	kulong size;

#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	size = priv->gDdXdmacCtrl[ch].trnsSize - (ioXdmac.ch[ch].xdtbc + 1);

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return size;
}

/**
 * @brief  The value of the source address (dmacsa) of the specified channel is acquired.
 * @param  kuchar		ch		Channel number (0 to 3)
 * @return kulong				Source address of the specified channel
 */
kulong	dd_xdmac_get_src_addr(DdXdmac *self, kuchar ch)
{
	kulong addr;

#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	addr = ioXdmac.ch[ch].xdssa;

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return addr;
}

/**
 * @brief  The value of the destination address (dmacda) of the specified channel is acquired.
 * @param  kuchar		ch		Channel number (0 to 3)
 * @return kulong				Destination address of the specified channel
 */
kulong	dd_xdmac_get_dst_addr(DdXdmac *self, kuchar ch)
{
	kulong addr;

#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	addr = ioXdmac.ch[ch].xddsa;

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return addr;
}

/**
 * @brief  Low Power is set is set.
 * @param  kuchar		lowpower	Low Power
 * @return kint32					D_DDIM_OK / D_DD_XDMAC_INPUT_PARAM_ERR
 */
kint32	dd_xdmac_set_low_power(DdXdmac *self, kuchar lowpower)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (lowpower > DdXdmac_XDACS_LP_ENABLE) {
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [lowpower] = %d\n", lowpower));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	// SpinLock
	DD_ARM_CRITICAL_SECTION_START(S_DD_XDMAC_SPIN_LOCK);

	ioXdmac.xdacs.bit.lp = lowpower;

	// SpinUnLock
	DD_ARM_CRITICAL_SECTION_END(S_DD_XDMAC_SPIN_LOCK);

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Source Protection code is set.
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  kuchar		protect_code	Protection Code
 * @return kint32						DriverCommon_DDIM_OK / DdXdmac_INPUT_PARAM_ERR
 */
kint32	dd_xdmac_set_source_protect(DdXdmac *self, kuchar ch, kuchar protect_code)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(protect_code > DdXdmac_XDDPC_SP_PRIVILEGED_SECURE){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [protect_code] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	ioXdmac.ch[ch].xddpc.bit.sp = protect_code;

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Destination Protection code is set.
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  kuchar		protect_code	Protection Code
 * @return kint32						DriverCommon_DDIM_OK / DdXdmac_INPUT_PARAM_ERR
 */
kint32	dd_xdmac_set_destination_protect(DdXdmac *self, kuchar ch, kuchar protect_code)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(protect_code > DdXdmac_XDDPC_DP_PRIVILEGED_SECURE){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [protect_code] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	ioXdmac.ch[ch].xddpc.bit.dp = protect_code;

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  The operation of All DMA channel is stopped.
 */
void	dd_xdmac_stop_all_ch(DdXdmac *self)
{
#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	ioXdmac.ch[0].xddes.bit.ce = DdXdmac_XDDES_CE_DISABLE;
	ioXdmac.ch[1].xddes.bit.ce = DdXdmac_XDDES_CE_DISABLE;
	ioXdmac.ch[2].xddes.bit.ce = DdXdmac_XDDES_CE_DISABLE;
	ioXdmac.ch[3].xddes.bit.ce = DdXdmac_XDDES_CE_DISABLE;

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK

	return;
}

/**
 * @brief  Set DMA Interrupt Handler.
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  void			IntHandlerFunc		Interrupt handler
 * @return void
 */
void  dd_xdmac_set_int_handler(DdXdmac *self, kuchar ch, void (*IntHandlerFunc)(void))
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return;
	}
#endif
	priv->gDdXdmacCtrl[ch].intHandler = IntHandlerFunc;
}

/**
 * @brief  Interrupt handler of DMA channel 0 for transfer process is finished.
 * @param  kuchar		ch				Channel number (0 to 3)
 * @return void
 */
void dd_xdmac_int_handler(DdXdmac *self, kuchar ch)
{
	DdXdmacPrivate *priv = DD_XDMAC_GET_PRIVATE(self);
	DdimUserCustom_ER ercd;
	kushort status;
	VpCallback handler;//TODO:VpCallback定义在ddim_typedef.h中,原型为typedef void				(*VP_CALLBACK)();	/**< Type is defined to Callback function pointer */

#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return;
	}
#endif

#ifdef CO_ACT_CLOCK
	ddXdmacStartClock(self);
#endif //CO_ACT_CLOCK

	status = ioXdmac.ch[ch].xddsd.bit.is;								// To give the user the content of the IS of XDDSD register
	priv->gDdXdmacStopStatus[ch] = status;
	ioXdmac.ch[ch].xddsd.bit.is = DdXdmac_XDDSD_IS_NONE;		// Stop Status clear
	ioXdmac.ch[ch].xddes.bit.ce = DdXdmac_XDDES_CE_DISABLE;		// DMA Stop
	DD_ARM_DSB_POU();

	handler = priv->gDdXdmacCtrl[ch].intHandler;

	if (handler != NULL) {
		(*handler)(ch, &status);
	}

	if(status != DdXdmac_XDDSD_IS_NONE){
		switch(ch){
			case 0:
				ercd = ddim_user_custom_set_flg(priv->ddimUserCustom, FID_DD_XDMAC, DdXdmac_FLG_CH0);
				break;
			case 1:
				ercd = ddim_user_custom_set_flg(priv->ddimUserCustom, FID_DD_XDMAC, DdXdmac_FLG_CH1);
				break;
			case 2:
				ercd = ddim_user_custom_set_flg(priv->ddimUserCustom, FID_DD_XDMAC, DdXdmac_FLG_CH2);
				break;
			case 3:
				ercd = ddim_user_custom_set_flg(priv->ddimUserCustom, FID_DD_XDMAC, DdXdmac_FLG_CH3);
				break;
			default:
				ercd = -1;
				break;
		}
	}
	else{
		ercd = DdimUserCustom_E_OK;
	}

	if(ercd != DdimUserCustom_E_OK){
		DriverCommon_DDIM_PRINT(("I:DDIM_User_Set_Flg error. ercd = %d\n", ercd));
	}

#ifdef CO_ACT_CLOCK
	ddXdmacStopClock(self);
#endif //CO_ACT_CLOCK
}

DdXdmac* dd_xdmac_get(void)
{
	static DdXdmac *ddXdmac = NULL;
	if(!ddXdmac)
	{
		ddXdmac = k_object_new_with_private(DD_TYPE_XDMAC,sizeof(DdXdmacPrivate));
	}
    return ddXdmac;
}
