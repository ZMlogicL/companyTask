/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月4日
 * @author            :冯黎阳
 * @brief             :
 * @rely              :klib
 * @function
 * @version
 *
 */

//#include "ddtop.h"
#include "peripheral.h"
#include "driver_common.h"
#include "ddimusercustom.h"
#include "ddarm.h"
#include "ddhdmac0.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdHdmac0, dd_hdmac0);
#define DD_HDMAC0_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdHdmac0Private, DD_TYPE_HDMAC0))

#define DdHdmac0_SYNC			0		/* Sync Processing */
#define DdHdmac0_ASYNC			1		/* Async Processing */


struct _DdHdmac0Private
{
	DdHdmac0Utility *utility;
	volatile Hdmac0Ctrl hdmac0Ctrl[DdHdmac0_CH_NUM_MAX];
	volatile kushort tcSecond[DdHdmac0_CH_NUM_MAX];
	volatile kushort stopStatus[DdHdmac0_CH_NUM_MAX];
	volatile kint32 waitEndTime[DdHdmac0_CH_NUM_MAX];
};


//---------------------- driver  section -------------------------------
static kint32 waitEnd(DdHdmac0Private *priv, kuchar ch, kushort* const status, kuint32 waitMode);
static kint32 ddHdmac0Start(DdHdmac0Private *priv, kuchar ch, kushort* const status, kuint32 waitMode, kuint32 sync);


static void dd_hdmac0_constructor(DdHdmac0 *self)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

	priv->utility = dd_hdmac0_utility_new();
}

static void dd_hdmac0_destructor(DdHdmac0 *self)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

	if(priv->utility)
	{
		k_object_unref(priv->utility);
	}
}

/**
 * @brief  HDMAC0 wait end.
 */
static kint32 waitEnd(DdHdmac0Private *priv, kuchar ch, kushort* const status, kuint32 waitMode)
{
	DdimUserCustom_FLGPTN flgPtn;
	DdimUserCustom_ER ercd = 0;
	kushort ss;

	// CPU Polling (no use interrupt)
	if (waitMode == DdHdmac0_WAITMODE_CPU) {
		while (priv->stopStatus[ch] == 0) {
			ss = ioHdmac0.dmac[ch].dmacb.bit.ss;
			if(ss) {
				priv->stopStatus[ch] = ss;
			}
		}
		
		if (priv->stopStatus[ch] == 0) {
			*status = ioHdmac0.dmac[ch].dmacb.bit.ss;	// To give the user the content of the SS bit of DMACB register
			ioHdmac0.dmac[ch].dmacb.bit.ss = 0x0;		// Stop Status clear
			ioHdmac0.dmac[ch].dmaca.bit.eb = 0;		// HDMAC0 Stop
		}
		else {
			*status = priv->stopStatus[ch];
			priv->stopStatus[ch] = 0;
		}
	}
	// EVENT (use interrupt)
	else {
		switch (ch) {
			case 0:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH0, DdimUserCustom_TWF_ORW, &flgPtn,
						priv->waitEndTime[ch]);
				break;

			case 1:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH1, DdimUserCustom_TWF_ORW, &flgPtn,
						priv->waitEndTime[ch]);
				break;

			case 2:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH2, DdimUserCustom_TWF_ORW, &flgPtn,
						priv->waitEndTime[ch]);
				break;

			case 3:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH3, DdimUserCustom_TWF_ORW, &flgPtn,
						priv->waitEndTime[ch]);
				break;

			case 4:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH4, DdimUserCustom_TWF_ORW, &flgPtn,
						priv->waitEndTime[ch]);
				break;

			case 5:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH5, DdimUserCustom_TWF_ORW, &flgPtn,
						priv->waitEndTime[ch]);
				break;

			case 6:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH6, DdimUserCustom_TWF_ORW, &flgPtn,
						priv->waitEndTime[ch]);
				break;

			case 7:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH7, DdimUserCustom_TWF_ORW, &flgPtn,
						priv->waitEndTime[ch]);
				break;

			default:
				break;
		}

		*status = priv->stopStatus[ch];		// To give the user the content of the SS bit of DMACB register
		priv->stopStatus[ch] = 0;
	}

	if (ercd == DdimUserCustom_E_TMOUT) {
		Ddim_Print(("HDMAC0 error. timeout!"));
		return DdHdmac0_TIMEOUT_ERR;
	}

	if (ercd != DdimUserCustom_E_OK) {
		Ddim_Print(("HDMAC0 error. system error!"));
		return DdHdmac0_SYSTEM_ERR;
	}

	return D_DDIM_OK;
}

/**
 * @brief  HDMAC0 start.
 */
static kint32 ddHdmac0Start(DdHdmac0Private *priv, kuchar ch, kushort* const status, kuint32 waitMode, kuint32 sync)
{
	kint32 ret = D_DDIM_OK;

	// HDMAC0 Enable
	if (ioHdmac0.dmacr.bit.de == 0) {
		ioHdmac0.dmacr.bit.de = 1;							// HDMAC0 all ch enable
	}

	// HDMAC0 Busy Check
	if (ioHdmac0.dmac[ch].dmaca.bit.eb) {
		return DdHdmac0_BUSY_ERR;
	}

	if (waitMode == DdHdmac0_WAITMODE_EVENT) {
		priv->hdmac0Ctrl[ch].configB.bit.ei = 1;				// Error Interrupt Enable
		priv->hdmac0Ctrl[ch].configB.bit.ci = 1;				// Completion Interrupt Enable
	}

	priv->stopStatus[ch] = 0;
	ioHdmac0.dmac[ch].dmaca.word = priv->hdmac0Ctrl[ch].configA.word;	// HDMAC0 Config A register set
	ioHdmac0.dmac[ch].dmacb.word = priv->hdmac0Ctrl[ch].configB.word;	// HDMAC0 Config B register set
	ioHdmac0.dmac[ch].dmacsa = priv->hdmac0Ctrl[ch].srcAddr;		// HDMAC0 Source Address register set
	ioHdmac0.dmac[ch].dmacda = priv->hdmac0Ctrl[ch].dstAddr;		// HDMAC0 Destination Address register set

	if (waitMode == DdHdmac0_WAITMODE_EVENT) {
		switch (ch) {
			case 0:
				DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH0);
				break;

			case 1:
				DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH1);
				break;

			case 2:
				DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH2);
				break;

			case 3:
				DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH3);
				break;

			case 4:
				DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH4);
				break;

			case 5:
				DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH5);
				break;

			case 6:
				DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH6);
				break;

			case 7:
				DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH7);
				break;

			default:
				break;
		}
	}

	ioHdmac0.dmac[ch].dmaca.bit.eb = 1;			// HDMAC0 Start
	if (priv->hdmac0Ctrl[ch].configA.bit.is == DdHdmac0_IS_SOFT) {
		ioHdmac0.dmac[ch].dmaca.bit.st = 1;		// Soft trigger
	}
	Dd_ARM_Dsb_Pou();

	// Sync Processing
	if (sync == DdHdmac0_SYNC) {
		ret = waitEnd(priv, ch, status, waitMode);
	}

	return ret;
}

/**
 * @brief  Execute exclusive control for designated HDMAC0 channel.
 * @param  kuchar	ch	Channel number (0 to 7)
 * @return kint32 	D_DDIM_OK / DdHdmac0_EXC_LOCK_NG / DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_open(DdHdmac0 *self, kuchar ch, kint32 tmout)
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	if (DdimUserCustom_SEM_WAIT_POL == tmout) {
		ercd = DDIM_User_Pol_Sem(SID_DD_HDMAC0(ch));				// pol_sem()
	}
	else {
		ercd = DDIM_User_Twai_Sem(SID_DD_HDMAC0(ch), (DdimUserCustom_TMO)tmout);	// twai_sem()
	}

	if (DdimUserCustom_E_OK != ercd) {
		if (DdimUserCustom_E_TMOUT == ercd) {
			return DdHdmac0_SEM_TIMEOUT;
		}

		return DdHdmac0_SEM_NG;
	}

	return D_DDIM_OK;
}

/**
 * @brief  Cancel exclusive control for designated HDMAC0 channel.
           When the designated channel is under transferring, stop transfer immediately and cancel lock.
 * @param  kuchar	ch			Channel number (0 to 7)
 * @return kint32  D_DDIM_OK/DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_close(DdHdmac0 *self, kuchar ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// Global variable is clear
	priv->hdmac0Ctrl[ch].configA.word = 0;
	priv->hdmac0Ctrl[ch].configB.word = 0;
	priv->hdmac0Ctrl[ch].srcAddr = 0;
	priv->hdmac0Ctrl[ch].dstAddr = 0;
	priv->hdmac0Ctrl[ch].intHandler = NULL;

	ercd = DDIM_User_Sig_Sem(SID_DD_HDMAC0(ch));				// sig_sem()
	if(DdimUserCustom_E_OK != ercd) {
		return DdHdmac0_SEM_NG;
	}

	return D_DDIM_OK;
}

/**
 * @brief  Set control data to registers related HDMAC0 designated channel.
 * @param  kuchar	ch	Channel number (0 to 7)
 * @return kint32	D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_ctrl_common(DdHdmac0 *self, kuchar ch, Hdmac0Ctrl const *const hdmac0Ctrl)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (hdmac0Ctrl == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*hdmac0Ctrl] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// HDMAC0 Busy Check
//	if (ioHdmac0.dmac[ch].CSTR.bit.BUSY) {
//		return DdHdmac0_BUSY_ERR;
//	}

	// The value is set to an external variable
	priv->hdmac0Ctrl[ch].configA.word = (hdmac0Ctrl->configA.word & 0x1FFFFFFF);
	priv->hdmac0Ctrl[ch].configB.word = (hdmac0Ctrl->configB.word & 0xFFFFFF00);
	priv->hdmac0Ctrl[ch].srcAddr = hdmac0Ctrl->srcAddr;
	priv->hdmac0Ctrl[ch].dstAddr = hdmac0Ctrl->dstAddr;
	priv->hdmac0Ctrl[ch].intHandler = hdmac0Ctrl->intHandler;

	priv->tcSecond[ch] = 0;
	priv->waitEndTime[ch] = D_DDIM_WAIT_END_TIME;

	return D_DDIM_OK;
}

/**
 * @brief  Set control data to registers related HDMAC0 designated channel.
 * @param  kuchar	ch	Channel number (0 to 7)
 * @return kint32	D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_ctrl_trns(DdHdmac0 *self, kuchar ch, Hdmac0CtrlTrns const *const hdmac0CtrlTrans)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	kuchar  tmpWidth;
	kulong  tmpTc = 0;
	kushort tmpBc = 0;
	kuchar  tmpBt = 0;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (hdmac0CtrlTrans == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*hdmac0CtrlTrans] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// HDMAC0 Busy Check
//	if (ioHdmac0.dmac[ch].CSTR.bit.BUSY) {
//		return DdHdmac0_BUSY_ERR;
//	}

	// Calucurate TC and BC
	tmpWidth = 0x01 << hdmac0CtrlTrans->size.trnsWidth;
	if ((hdmac0CtrlTrans->size.trnsSize % tmpWidth) != 0) {
		Ddim_Print(("HDMAC0: input param error. illegal alignment.\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}

	switch (hdmac0CtrlTrans->mode.beatType) {
		case DdHdmac0_BT_WRAP4:
		case DdHdmac0_BT_INCR4:
			tmpBt = 4;
			break;
		case DdHdmac0_BT_WRAP8:
		case DdHdmac0_BT_INCR8:
			tmpBt = 8;
			break;
		case DdHdmac0_BT_WRAP16:
		case DdHdmac0_BT_INCR16:
		case DdHdmac0_BT_INCR:
			tmpBt = 16;
			break;
		default:
			tmpBt = 16;
			break;
	}
	if ((hdmac0CtrlTrans->mode.modeSel != DdHdmac0_MS_DEMAND) &&
		(hdmac0CtrlTrans->size.trnsSize > (tmpWidth * tmpBt))) {

		tmpBc = tmpBt - 1;
		tmpTc = (hdmac0CtrlTrans->size.trnsSize / (tmpWidth * tmpBt)) - 1;

		if ((hdmac0CtrlTrans->size.trnsSize % (tmpWidth * tmpBt)) != 0) {
			priv->tcSecond[ch] = ((hdmac0CtrlTrans->size.trnsSize % (tmpWidth * tmpBt)) / tmpWidth);
		}
		else {
			priv->tcSecond[ch] = 0;
		}
	}
	else {
		tmpBc = 0;
		tmpTc = (hdmac0CtrlTrans->size.trnsSize / tmpWidth) - 1;
		priv->tcSecond[ch] = 0;
	}

	// Check TransferSize
	if ((tmpTc >= 65536) || ((tmpTc == 65535) && (priv->tcSecond[ch] != 0))) {
		// Max size over
		Ddim_Print(("HDMAC0: input param error. Max size over (Max size=%d).\n", tmpWidth * tmpBt * 65536));
		return DdHdmac0_INPUT_PARAM_ERR;
	}

	// The value is set to an external variable
	priv->hdmac0Ctrl[ch].configA.bit.is = hdmac0CtrlTrans->mode.inputSel;
	priv->hdmac0Ctrl[ch].configA.bit.bt = hdmac0CtrlTrans->mode.beatType;

	priv->hdmac0Ctrl[ch].configB.bit.ms = hdmac0CtrlTrans->mode.modeSel;
	priv->hdmac0Ctrl[ch].configB.bit.fs = hdmac0CtrlTrans->mode.srcFix;
	priv->hdmac0Ctrl[ch].configB.bit.fd = hdmac0CtrlTrans->mode.dstFix;

	priv->hdmac0Ctrl[ch].configB.bit.tw = hdmac0CtrlTrans->size.trnsWidth;

	priv->hdmac0Ctrl[ch].configA.bit.bc = tmpBc;
	priv->hdmac0Ctrl[ch].configA.bit.tc = (kushort)tmpTc;

	priv->hdmac0Ctrl[ch].configB.bit.dp = 0x08;		// HPROT[3] Cachable (Source Protection)
	priv->hdmac0Ctrl[ch].configB.bit.sp = 0x08;		// HPROT[3] Cachable (Destination Protection)

	priv->hdmac0Ctrl[ch].srcAddr = hdmac0CtrlTrans->size.srcAddr;
	priv->hdmac0Ctrl[ch].dstAddr = hdmac0CtrlTrans->size.dstAddr;
	priv->hdmac0Ctrl[ch].intHandler = hdmac0CtrlTrans->intHandler;

	priv->waitEndTime[ch] = D_DDIM_WAIT_END_TIME;

	return D_DDIM_OK;
}

kint32 dd_hdmac0_set_trns_size(DdHdmac0 *self, kuchar ch, Hdmac0TrnsSize const *const hdmac0TrnsSize)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	kuchar  tmpWidth;
	kulong  tmpTc = 0;
	kushort tmpBc = 0;
	kuchar  tmpBt = 0;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (hdmac0TrnsSize == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*hdmac0TrnsSize] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// HDMAC0 Busy Check
//	if (ioHdmac0.dmac[ch].CSTR.bit.BUSY) {
//		return DdHdmac0_BUSY_ERR;
//	}

	// Calucurate TC and BC
	tmpWidth = 0x01 << hdmac0TrnsSize->trnsWidth;
	if ((hdmac0TrnsSize->trnsSize % tmpWidth) != 0) {
		Ddim_Print(("HDMAC0: input param error. illegal alignment.\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}

	switch (priv->hdmac0Ctrl[ch].configA.bit.bt) {
		case DdHdmac0_BT_WRAP4:
		case DdHdmac0_BT_INCR4:
			tmpBt = 4;
			break;
		case DdHdmac0_BT_WRAP8:
		case DdHdmac0_BT_INCR8:
			tmpBt = 8;
			break;
		case DdHdmac0_BT_WRAP16:
		case DdHdmac0_BT_INCR16:
		case DdHdmac0_BT_INCR:
			tmpBt = 16;
			break;
		default:
			tmpBt = 16;
			break;
	}
	if ((priv->hdmac0Ctrl[ch].configB.bit.ms != DdHdmac0_MS_DEMAND) &&
		(hdmac0TrnsSize->trnsSize > (tmpWidth * tmpBt))) {
		tmpBc = tmpBt - 1;
		tmpTc = (hdmac0TrnsSize->trnsSize / (tmpWidth * tmpBt)) - 1;

		if ((hdmac0TrnsSize->trnsSize % (tmpWidth * tmpBt)) != 0) {
			priv->tcSecond[ch] = ((hdmac0TrnsSize->trnsSize % (tmpWidth * tmpBt)) / tmpWidth);
		}
		else {
			priv->tcSecond[ch] = 0;
		}
	}
	else {
		tmpBc = 0;
		tmpTc = (hdmac0TrnsSize->trnsSize / tmpWidth) - 1;
		priv->tcSecond[ch] = 0;
	}

	// Check TransferSize
	if ((tmpTc >= 65536) || ((tmpTc == 65535) && (priv->tcSecond[ch] != 0))) {
		// Max size over
		Ddim_Print(("HDMAC0: input param error. Max size over (Max size=%d).\n", tmpWidth * tmpBt * 65536));
		return DdHdmac0_INPUT_PARAM_ERR;
	}

	// The value is set to an external variable
	priv->hdmac0Ctrl[ch].configB.bit.tw = hdmac0TrnsSize->trnsWidth;

	priv->hdmac0Ctrl[ch].configA.bit.bc = tmpBc;
	priv->hdmac0Ctrl[ch].configA.bit.tc = (kushort)tmpTc;

	priv->hdmac0Ctrl[ch].srcAddr = hdmac0TrnsSize->srcAddr;
	priv->hdmac0Ctrl[ch].dstAddr = hdmac0TrnsSize->dstAddr;

	return D_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC0 of specified ch begins.
 * @param  kuchar				ch				Channel number (0 to 7)
 *         T_DD_HDMAC0_START*	hdmac0_start	HDMAC0 Start table
 *         kushort*			status		Channel Status Register pointer
 *         kuint32			waitMode	HDMAC0 end wait mode
 * @return kint32			D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR / D_DDIM_TIMEOUT / DdHdmac0_SYSTEM_ERR
 */
kint32 dd_hdmac0_start_sync(DdHdmac0 *self, kuchar ch, kushort *const status, kuint32 waitMode)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (status == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*status] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if ((waitMode != DdHdmac0_WAITMODE_CPU) && (waitMode != DdHdmac0_WAITMODE_EVENT)) {
		Ddim_Assertion(("HDMAC0: input param error. [waitMode] = %x\n", waitMode));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	ret = ddHdmac0Start(priv, ch, status, waitMode, DdHdmac0_SYNC);		// HDMAC0 Start

	if ((*status == DdHdmac0_SS_NORMAL_END) && (priv->tcSecond[ch] != 0)) {
		// restart
		priv->hdmac0Ctrl[ch].configA.bit.bc = 0;
		priv->hdmac0Ctrl[ch].configA.bit.tc = priv->tcSecond[ch] - 1;

		priv->hdmac0Ctrl[ch].srcAddr = ioHdmac0.dmac[ch].dmacsa;
		priv->hdmac0Ctrl[ch].dstAddr = ioHdmac0.dmac[ch].dmacda;

		priv->tcSecond[ch] = 0;
		ddHdmac0Start(priv, ch, status, waitMode, DdHdmac0_SYNC);	// HDMAC0 Start
	}

	return ret;
}

/**
 * @brief  The operation of HDMAC0 of specified ch begins.
 * @param  kuchar				ch				Channel number (0 to 7)
 *         T_DD_HDMAC0_START*	hdmac0_start	HDMAC0 Start table
 * @return kint32			D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_start_async(DdHdmac0 *self, kuchar ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	kushort status;	// dummy

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	ddHdmac0Start(priv, ch, &status, DdHdmac0_WAITMODE_EVENT, DdHdmac0_ASYNC);	// HDMAC0 Start
	return D_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC0 of specified ch is stopped.
 * @param  kuchar	ch			Channel number (0 to 7)
 * @return kint32	D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_stop(DdHdmac0 *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	ioHdmac0.dmac[ch].dmaca.word &= 0x7FFFFFFF;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC0 of specified ch is stopped.
 * @param  kuchar	ch			Channel number (0 to 7)
 * @return kint32	D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_pause(DdHdmac0 *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	ioHdmac0.dmac[ch].dmaca.bit.pb = 1;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC0 of specified ch is resumed.
 * @param  kuchar	ch			Channel number (0 to 7)
 * @return kint32	D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_resume(DdHdmac0 *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	switch (ch) {
		case 0:
			DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH0);
			break;

		case 1:
			DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH1);
			break;

		case 2:
			DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH2);
			break;

		case 3:
			DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH3);
			break;

		case 4:
			DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH4);
			break;

		case 5:
			DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH5);
			break;

		case 6:
			DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH6);
			break;

		case 7:
			DDIM_User_Clr_Flg(FID_DD_HDMAC0, ~DdHdmac0_FLG_CH7);
			break;

		default:
			break;
	}

	ioHdmac0.dmac[ch].dmaca.bit.pb = 0;
	ioHdmac0.dmac[ch].dmaca.bit.eb = 1;			// HDMAC0 Start
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  Wait end time of transfer process of designated channel.
 * @param  kuchar	ch			Channel number (0 to 7)
 *         kint32	waitTime	Wait end time of transfer process
 * @return kint32				D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_set_wait_time(DdHdmac0 *self, kuchar ch, kint32 waitTime)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (waitTime < D_DDIM_WAIT_END_FOREVER) {
		Ddim_Assertion(("HDMAC0: input param error. [waitTime] = %d\n", waitTime));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	priv->waitEndTime[ch] = waitTime;
	return D_DDIM_OK;
}

/**
 * @brief  Wait end of transfer process of designated channel.
 *         The value of the CSTR register is passed by the out parameter.
 * @param  kuchar	ch			Channel number (0 to 7)
 *         kushort*	status		Channel Status Register pointer
 * @return kint32	D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR / D_DDIM_TIMEOUT / DdHdmac0_SYSTEM_ERR
 */
kint32 dd_hdmac0_wait_end(DdHdmac0 *self, kuchar ch, kushort* const status, kuint32 waitMode)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (status == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*status] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if ((waitMode != DdHdmac0_WAITMODE_CPU) && (waitMode != DdHdmac0_WAITMODE_EVENT)) {
		Ddim_Assertion(("HDMAC0: input param error. [waitMode] = %x\n", waitMode));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	ret = waitEnd(priv, ch, status, waitMode);

	if ((*status == DdHdmac0_SS_NORMAL_END) && (priv->tcSecond[ch] != 0)) {
		// restart
		priv->hdmac0Ctrl[ch].configA.bit.bc = 0;
		priv->hdmac0Ctrl[ch].configA.bit.tc = priv->tcSecond[ch] - 1;

		priv->hdmac0Ctrl[ch].srcAddr = ioHdmac0.dmac[ch].dmacsa;
		priv->hdmac0Ctrl[ch].dstAddr = ioHdmac0.dmac[ch].dmacda;

		priv->tcSecond[ch] = 0;
		ddHdmac0Start(priv, ch, status, DdHdmac0_WAITMODE_EVENT, DdHdmac0_ASYNC);	// HDMAC0 Start
		ret = waitEnd(priv, ch, status, waitMode);
	}

	return ret;
}

/**
 * @brief  The status of HDMAC0 of specified ch is cleared.
 * @param  kuchar	ch			Channel number (0 to 7)
 * @return kint32				D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_clear_status(DdHdmac0 *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	ioHdmac0.dmac[ch].dmacb.bit.ss = 0;

	return D_DDIM_OK;
}

/**
 * @brief  The error status of HDMAC0 of specified ch is cleared.
 * @param  kuchar	ch			Channel number (0 to 7)
 * @return kint32				D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_get_status(DdHdmac0 *self, kuchar ch, kushort *const status)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (status == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*status] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	*status = ioHdmac0.dmac[ch].dmacb.bit.ss;
	return D_DDIM_OK;
}

/**
The value of the transferd size of the specified channel is acquired.
@param [in] ch				Channel number (0 to 7)
@retval size						transferd size of the specified channel
@remarks This API forced cancel exclusive control if process is under executing.
*/
kulong dd_hdmac0_get_trns_size(DdHdmac0 *self, kuchar ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	kulong  totalSize;
	kulong  remainSize;
	kushort tc;
	kuchar  bc;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	tc = ioHdmac0.dmac[ch].dmaca.bit.tc;
	bc = ioHdmac0.dmac[ch].dmaca.bit.bc;
	remainSize = (bc + 1) * (tc + 1) * (1 << priv->hdmac0Ctrl[ch].configB.bit.tw);

	if ((tc == 0) && (bc == 0)) {
		if (((ioHdmac0.dmac[ch].dmacb.word & 0x00070000) != 0x00000000) || (priv->stopStatus[ch] != 0)) {
			remainSize = 0;
		}
	}

	if (priv->tcSecond[ch] != 0) {
		remainSize += (priv->tcSecond[ch]) * (1 << priv->hdmac0Ctrl[ch].configB.bit.tw);
	}

	totalSize = (priv->hdmac0Ctrl[ch].configA.bit.bc + 1) * (priv->hdmac0Ctrl[ch].configA.bit.tc + 1)
			* (1 << priv->hdmac0Ctrl[ch].configB.bit.tw);
	if (priv->tcSecond[ch] != 0) {
		totalSize += (priv->tcSecond[ch]) * (1 << priv->hdmac0Ctrl[ch].configB.bit.tw);
	}

	return (totalSize - remainSize);
}

/**
The value of the remainder transfer size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval size						remainder transfer size of the specified channel
@remarks This API forced cancel exclusive control if process is under executing.
*/
kulong dd_hdmac0_get_remain_trns_size(DdHdmac0 *self, kuchar ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	kulong  remainSize;
	kushort tc;
	kuchar  bc;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	tc = ioHdmac0.dmac[ch].dmaca.bit.tc;
	bc = ioHdmac0.dmac[ch].dmaca.bit.bc;
	remainSize = (bc + 1) * (tc + 1) * (1 << priv->hdmac0Ctrl[ch].configB.bit.tw);

	if ((tc == 0) && (bc == 0)) {
		if (((ioHdmac0.dmac[ch].dmacb.word & 0x00070000) != 0x00000000) || (priv->stopStatus[ch] != 0)) {
			remainSize = 0;
		}
	}

	if (priv->tcSecond[ch] != 0) {
		remainSize += (priv->tcSecond[ch]) * (1 << priv->hdmac0Ctrl[ch].configB.bit.tw);
	}

	return remainSize;
}

/**
The value of the total transfer size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval size						total transfer size of the specified channel
*/
kulong dd_hdmac0_get_total_trns_size(DdHdmac0 *self, kuchar ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	kulong totalSize;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	totalSize = (priv->hdmac0Ctrl[ch].configA.bit.bc + 1) * (priv->hdmac0Ctrl[ch].configA.bit.tc + 1)
			* (1 << priv->hdmac0Ctrl[ch].configB.bit.tw);
	if (priv->tcSecond[ch] != 0) {
		totalSize += (priv->tcSecond[ch]) * (1 << priv->hdmac0Ctrl[ch].configB.bit.tw);
	}

	return totalSize;
}

/**
The value of the source address (DMACSA) of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval srcAddr					source address of the specified channel
*/
kulong dd_hdmac0_get_src_addr(DdHdmac0 *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	return ioHdmac0.dmac[ch].dmacsa;
}

/**
The value of the destination address (DMACDA) of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval dstAddr					Destination address of the specified channel
*/
kulong dd_hdmac0_get_dst_addr(DdHdmac0 *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	return ioHdmac0.dmac[ch].dmacda;
}

/**
Source Protection code is set.

@param [in] ch					Channel number (0 to 7)
@param [in] protectCode		Protection Code
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32 dd_hdmac0_set_source_protect(DdHdmac0 *self, kuchar ch, kuchar protectCode)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	ioHdmac0.dmac[ch].dmacb.bit.sp = protectCode;
	return D_DDIM_OK;
}

/**
Destination Protection code is set.

@param [in] ch					Channel number (0 to 7)
@param [in] protectCode		Protection Code
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32 dd_hdmac0_set_destination_protect(DdHdmac0 *self, kuchar ch, kuchar protectCode)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	ioHdmac0.dmac[ch].dmacb.bit.dp = protectCode;
	return D_DDIM_OK;
}

/**
 * @brief  Arbitration level and HDMAC0 forwarding control interrupt level of all channels are set.
 * @param  T_DD_HDMAC0_ARBITRATION*	arbitration
 * @return kint32				D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_set_arbitration(DdHdmac0 *self, kuchar arbitration)
{
#ifdef CO_PARAM_CHECK
	if ((arbitration != DdHdmac0_ARB_FIX) && (arbitration != DdHdmac0_ARB_ROTATE)) {
		Ddim_Assertion(("HDMAC0: input param error. [arbitration] = %x\n", arbitration));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// Arbitration type is set
	ioHdmac0.dmacr.bit.pr = arbitration;

	return D_DDIM_OK;
}

/**
 * @brief  Arbitration level and HDMAC0 forwarding control interrupt level of all channels are read.
 * @param  T_DD_HDMAC0_ARBITRATION*	arbitration
 * @return kint32				D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
kint32 dd_hdmac0_get_arbitration(DdHdmac0 *self, kuchar *const arbitration)
{
#ifdef CO_PARAM_CHECK
	if (arbitration == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*arbitration] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// Arbitration type is set
	*arbitration = ioHdmac0.dmacr.bit.pr;

	return D_DDIM_OK;
}

/**
 * @brief  Arbitration level and HDMAC0 forwarding control interrupt level of all channels are returned to an initial value.
 * @param  void
 * @return void
 */
void dd_hdmac0_clear_arbitration(DdHdmac0 *self)
{
	// Arbitration type is set
	ioHdmac0.dmacr.bit.pr = 0;
}

/**
The operation of All HDMAC0 channel is stopped.
*/
void dd_hdmac0_stop_all_ch(DdHdmac0 *self)
{
	// HDMAC0 Halt
	ioHdmac0.dmacr.bit.dh = 1;
}

/**
The operation of All HDMAC0 channel is resumed.
*/
void dd_hdmac0_resume_all_ch(DdHdmac0 *self)
{
	// HDMAC0 resume
	ioHdmac0.dmacr.bit.dh = 0;
}

/**
It is API that returns the value set to the register of TW. 

@param [in] srcAddr			soruce address
@param [in] dstAddr			destination address
@param [in] totalSize			total size
@retval TW value set to register of TW
*/
kuchar dd_hdmac0_get_trns_width(DdHdmac0 *self, kulong srcAddr, kulong dstAddr, kulong totalSize)
{
	kuchar trnsWidth;

	// Check transfer size
	if (((srcAddr & 0x03) == 0) && ((dstAddr & 0x03) == 0) && ((totalSize & 0x03) == 0)) {
		trnsWidth = DdHdmac0_TW_WORD;
	}
	else if (((srcAddr & 0x01) == 0) && ((dstAddr & 0x01) == 0) && ((totalSize & 0x01) == 0)) {
		trnsWidth = DdHdmac0_TW_HWORD;
	}
	else {
		trnsWidth = DdHdmac0_TW_BYTE;
	}

	return trnsWidth;
}

/**
 * @brief  Set HDMAC0 Interrupt Handler
 * @param  HDMAC0 channel, interrupt handler
 * @return void
 */
void dd_hdmac0_set_int_handler(DdHdmac0 *self, kuchar ch, void (*intHandler)(void))
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return;
	}
#endif

	priv->hdmac0Ctrl[ch].intHandler = intHandler;
}

/**
 * @brief  Interrupt handler of HDMAC0 channel 0 for transfer process is finished.
 * @param  void
 * @return void
 */
void dd_hdmac0_int_handler(DdHdmac0 *self, kuchar ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	DdimUserCustom_ER ercd;
	kushort status;
	VpCallbackFunc handler;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return;
	}
#endif

	status = ioHdmac0.dmac[ch].dmacb.bit.ss;		// To give the user the content of the SS of DMACB register
	priv->stopStatus[ch] = status;
	ioHdmac0.dmac[ch].dmacb.bit.ss = 0x0;			// Stop Status clear
	ioHdmac0.dmac[ch].dmaca.bit.eb = 0;				// HDMAC0 Stop
	Dd_ARM_Dsb_Pou();

	if ((status != DdHdmac0_SS_NORMAL_END) || (priv->tcSecond[ch] == 0)) {
		handler = priv->hdmac0Ctrl[ch].intHandler;
		
		if (handler != NULL) {
			(*handler)(ch, &status);
		}
		
		switch (ch) {
			case 0:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH0);
				break;

			case 1:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH1);
				break;

			case 2:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH2);
				break;

			case 3:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH3);
				break;

			case 4:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH4);
				break;

			case 5:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH5);
				break;

			case 6:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH6);
				break;

			case 7:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH7);
				break;

			default:
				ercd = -1;
				break;
		}

		if (ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("I:DDIM_User_Set_Flg error. ercd = %d\n", ercd));
		}
	}
	else if (priv->tcSecond[ch] != 0) {
		// restart
		priv->hdmac0Ctrl[ch].configA.bit.bc = 0;
		priv->hdmac0Ctrl[ch].configA.bit.bt = 0;
		priv->hdmac0Ctrl[ch].configA.bit.tc = priv->tcSecond[ch] - 1;

		priv->hdmac0Ctrl[ch].srcAddr = ioHdmac0.dmac[ch].dmacsa;
		priv->hdmac0Ctrl[ch].dstAddr = ioHdmac0.dmac[ch].dmacda;

		priv->tcSecond[ch] = 0;
		ddHdmac0Start(priv, ch, &status, DdHdmac0_WAITMODE_EVENT, DdHdmac0_ASYNC);	// HDMAC0 Start
	}
}

/**
 * @brief  Interrupt handler of HDMAC0 channel 0 for transfer process is finished.
 * @param  void
 * @return void
 */
void dd_hdmac0_int_handler_2(DdHdmac0 *self, kuchar ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	DdimUserCustom_ER ercd;
	kushort status;
	VpCallbackFunc handler;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return;
	}
#endif
	
//	printf("[%d]Dd_HDMAC0_Int_Handler %d \n", ch, 1);
//	Dd_Top_Set_Gpio_Status(E_DD_TOP_GPIO_PF2, 1);

	status = ioHdmac0.dmac[ch].dmacb.bit.ss;		// To give the user the content of the SS of DMACB register
	priv->stopStatus[ch] = status;
	ioHdmac0.dmac[ch].dmacb.bit.ss = 0x0;			// Stop Status clear
	ioHdmac0.dmac[ch].dmaca.bit.eb = 0;				// HDMAC0 Stop
	Dd_ARM_Dsb_Pou();

	if ((status != DdHdmac0_SS_NORMAL_END) || (priv->tcSecond[ch] == 0)) {
		handler = priv->hdmac0Ctrl[ch].intHandler;
		
		if (handler != NULL) {
			(*handler)(ch, &status);
		}
		
		// for PWM TimerE
		switch (ch) {
			case 5:
//				Dd_Top_Set_Gpio_Status(E_DD_TOP_GPIO_PF3, 0);
				ercd = DDIM_User_Set_Flg(FID_DD_MOTOR_CALC_0, DdHdmac0_MOTOR_FINISHED_DMA_TRANS_CH4);
				break;
			case 6:
//				Dd_Top_Set_Gpio_Status(E_DD_TOP_GPIO_PF3, 1);
				ercd = DDIM_User_Set_Flg(FID_DD_MOTOR_CALC_1, DdHdmac0_MOTOR_FINISHED_DMA_TRANS_CH8);
				break;
			default:
				ercd = -1;
				break;
		}
		if (ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("I:2_ DDIM_User_Set_Flg error. ercd = %d\n", ercd));
		}
	}
	else if (priv->tcSecond[ch] != 0) {
		// restart
		priv->hdmac0Ctrl[ch].configA.bit.bc = 0;
		priv->hdmac0Ctrl[ch].configA.bit.bt = 0;
		priv->hdmac0Ctrl[ch].configA.bit.tc = priv->tcSecond[ch] - 1;

		priv->hdmac0Ctrl[ch].srcAddr = ioHdmac0.dmac[ch].dmacsa;
		priv->hdmac0Ctrl[ch].dstAddr = ioHdmac0.dmac[ch].dmacda;

		priv->tcSecond[ch] = 0;
		ddHdmac0Start(priv, ch, &status, DdHdmac0_WAITMODE_EVENT, DdHdmac0_ASYNC);	// HDMAC0 Start
	}
}

#ifdef CO_DDIM_UTILITY_USE

kint32 dd_hdmac0_copy_sdram_sync(DdHdmac0 *self, kuchar ch, kulong srcAddr,
		kulong dstAddr, kulong size, kuint32 waitMode)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

	return dd_hdmac0_utility_copy_sdram_sync(priv->utility, ch, srcAddr, dstAddr, size, waitMode);
}

kint32 dd_hdmac0_copy_sdram_async(DdHdmac0 *self, kuchar ch, kulong srcAddr,
		kulong dstAddr, kulong size, VpCallbackFunc intHandler)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

	return dd_hdmac0_utility_copy_sdram_async(priv->utility, ch, srcAddr, dstAddr, size, intHandler);
}

kint32 dd_hdmac0_input_audio_async(DdHdmac0 *self, kuchar ch, kuchar inputSel, kulong srcAddr,
		kulong dstAddr, kulong size, VpCallbackFunc intHandler)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

	return  dd_hdmac0_utility_input_audio_async(priv->utility, ch, inputSel, srcAddr, dstAddr, size, intHandler);
}

kint32 dd_hdmac0_output_audio_async(DdHdmac0 *self, kuchar ch, kuchar inputSel, kulong srcAddr,
		kulong dstAddr, kulong size, VpCallbackFunc intHandler)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

	return  dd_hdmac0_utility_output_audio_async(priv->utility, ch, inputSel, srcAddr, dstAddr, size, intHandler);
}


#endif

DdHdmac0* dd_hdmac0_get(void)
{
	static DdHdmac0* self = NULL;

	if(!self)
		self = k_object_new_with_private(DD_TYPE_HDMAC0, sizeof(DdHdmac0Private));

	return self;
}

