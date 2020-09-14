/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :周洪
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、HDMAC driver
*2、将dd_hdmac.c更名为ddhdmac.c类
*@version
*1.0.0 2020年06月开始开发
*/

#include "peripheral.h"
#include "driver_common.h"
#include "ddimusercustom.h"
#include "ddarm.h"
#include "ddhdmac.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdHdmac, dd_hdmac);
#define DD_HDMAC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), DdHdmacPrivate, DD_TYPE_HDMAC))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
#define D_DD_HDMAC_SYNC			0		/* Sync Processing */
#define D_DD_HDMAC_ASYNC			1		/* Async Processing */

struct _DdHdmacPrivate
{
    volatile TDdHdmacCtrl 	gDdHdmacCtrl[DdHdmac_CH_NUM_MAX];		// HDMAC Register Info
    volatile kushort 				gDdHdmacTcSecond[DdHdmac_CH_NUM_MAX];
    volatile kushort 				gDdHdmacStopStatus[DdHdmac_CH_NUM_MAX];
    volatile kint32 				gDdHdmacWaitEndTime[DdHdmac_CH_NUM_MAX];
    DdimUserCustom			*ddimUserCustom;
   //TODO: ddim_user_custom.c类中
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
//static volatile T_DD_HDMAC_CTRL gDD_HDMAC_Ctrl[D_DD_HDMAC_CH_NUM_MAX];		// HDMAC Register Info
//static volatile kushort gDD_HDMAC_TC_Second[D_DD_HDMAC_CH_NUM_MAX];
//static volatile kushort gDD_HDMAC_Stop_Status[D_DD_HDMAC_CH_NUM_MAX];
//static volatile kint32 gDD_HDMAC_Wait_End_Time[D_DD_HDMAC_CH_NUM_MAX];

/*----------------------------------------------------------------------*/
/* DECLS																		*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
static kint32 ddHdmacWaitEnd(DdHdmac *self, kuchar ch, kushort* const status, kuint32 waitMode);
static kint32 ddHdmacStart(DdHdmac *self, kuchar ch, kushort* const status, kuint32 waitMode, kuint32 sync);

static void dd_hdmac_constructor(DdHdmac *self)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
	priv->ddimUserCustom = ddim_user_custom_get();
}

static void dd_hdmac_destructor(DdHdmac *self)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
    if(priv->ddimUserCustom){
        k_object_unref(priv->ddimUserCustom);
        priv->ddimUserCustom = NULL;
    }
}

/*----------------------------------------------------------------------*/
/* IMPL																		*/
/*----------------------------------------------------------------------*/
/**
 * @brief  HDMAC wait end.
 */
static kint32 ddHdmacWaitEnd(DdHdmac *self, kuchar ch, kushort* const status, kuint32 waitMode)
{
	DdHdmacPrivate 			*priv = DD_HDMAC_GET_PRIVATE(self);
	DdimUserCustom_FLGPTN 	flgPtn;
	DdimUserCustom_ER 			ercd = 0;
	kushort 							ss;

	// CPU Polling (no use interrupt)
	if (waitMode == DdHdmac_WAITMODE_CPU) {
		while (priv->gDdHdmacStopStatus[ch] == 0) {
			ss = ioHdmac.dmac[ch].dmacb.bit.ss;//TODO:IO_HDMAC定义在khdmac.h中,命名方式不符合ETK_C规范这里最好是写成get方法和set方法来读写
			if(ss) {
				priv->gDdHdmacStopStatus[ch] = ss;
			}
		}

		if (priv->gDdHdmacStopStatus[ch] == 0) {
			*status = ioHdmac.dmac[ch].dmacb.bit.ss;	// To give the user the content of the SS bit of dmacb register
			ioHdmac.dmac[ch].dmacb.bit.ss = 0x0;		// Stop Status clear
			ioHdmac.dmac[ch].dmaca.bit.eb = 0;			// HDMAC Stop
		}
		else {
			*status = priv->gDdHdmacStopStatus[ch];
			priv->gDdHdmacStopStatus[ch] = 0;
		}
	}
	// EVENT (use interrupt)
	else {
		switch (ch) {
			case 0:
				ercd = ddim_user_custom_twai_flg(priv->ddimUserCustom, priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC,\
						DdHdmac_FLG_CH0, D_DDIM_USER_TWF_ORW, &flgPtn, priv->gDdHdmacWaitEndTime[ch]);
				break;
//TODO:ddim_user_custom_twai_flg原型:DDIM_User_Twai_Flg
			case 1:
				ercd = ddim_user_custom_twai_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, DdHdmac_FLG_CH1,\
						D_DDIM_USER_TWF_ORW, &flgPtn, priv->gDdHdmacWaitEndTime[ch]);
				break;

			case 2:
				ercd = ddim_user_custom_twai_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, DdHdmac_FLG_CH2,\
						D_DDIM_USER_TWF_ORW, &flgPtn, priv->gDdHdmacWaitEndTime[ch]);
				break;

			case 3:
				ercd = ddim_user_custom_twai_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, DdHdmac_FLG_CH3,\
						D_DDIM_USER_TWF_ORW, &flgPtn, priv->gDdHdmacWaitEndTime[ch]);
				break;

			default:
				break;
		}

		*status = priv->gDdHdmacStopStatus[ch];		// To give the user the content of the SS bit of dmacb register
		priv->gDdHdmacStopStatus[ch] = 0;
	}
//TODO:DdimUserCustom_E_TMOUT原型D_DDIM_USER_E_TMOUT
	if (ercd == DdimUserCustom_E_TMOUT) {
		DriverCommon_DDIM_PRINT(("HDMAC error. timeout!"));
		return DdHdmac_TIMEOUT_ERR;
	}
//TODO:DdimUserCustom_E_OK原型D_DDIM_USER_E_OK
	if (ercd != DdimUserCustom_E_OK) {
		DriverCommon_DDIM_PRINT(("HDMAC error. system error!"));
		return DdHdmac_SYSTEM_ERR;
	}

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  HDMAC start.
 */
static kint32 ddHdmacStart(DdHdmac *self, kuchar ch, kushort* const status, kuint32 waitMode, kuint32 sync)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
	kint32 ret = DriverCommon_DDIM_OK;

	// HDMAC Enable
	if (ioHdmac.dmacr.bit.de == 0) {
		ioHdmac.dmacr.bit.de = 1;							// HDMAC all ch enable
	}

	// HDMAC Busy Check
	if (ioHdmac.dmac[ch].dmaca.bit.eb) {
		return DdHdmac_BUSY_ERR;
	}

	if (waitMode == DdHdmac_WAITMODE_EVENT) {
		priv->gDdHdmacCtrl[ch].configB.bit.eI = 1;				// Error Interrupt Enable
		priv->gDdHdmacCtrl[ch].configB.bit.cI = 1;				// Completion Interrupt Enable
	}

	priv->gDdHdmacStopStatus[ch] = 0;
	ioHdmac.dmac[ch].dmaca.word = priv->gDdHdmacCtrl[ch].configA.word;	// HDMAC Config A register set
	ioHdmac.dmac[ch].dmacb.word = priv->gDdHdmacCtrl[ch].configB.word;	// HDMAC Config B register set
	ioHdmac.dmac[ch].dmacsa = priv->gDdHdmacCtrl[ch].srcAddr;			// HDMAC Source Address register set
	ioHdmac.dmac[ch].dmacda = priv->gDdHdmacCtrl[ch].dstAddr;			// HDMAC Destination Address register set

	if (waitMode == DdHdmac_WAITMODE_EVENT) {
		switch (ch) {
			case 0:
				ddim_user_custom_clr_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, ~DdHdmac_FLG_CH0);
				break;

			case 1:
				ddim_user_custom_clr_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, ~DdHdmac_FLG_CH1);
				break;

			case 2:
				ddim_user_custom_clr_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, ~DdHdmac_FLG_CH2);
				break;

			case 3:
				ddim_user_custom_clr_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, ~DdHdmac_FLG_CH3);
				break;

			default:
				break;
		}
	}

	ioHdmac.dmac[ch].dmaca.bit.eb = 1;			// HDMAC Start
	if (priv->gDdHdmacCtrl[ch].configA.bit.iS == DdHdmac_IS_SOFT) {
		ioHdmac.dmac[ch].dmaca.bit.st = 1;		// Soft trigger
	}
	DD_ARM_DSB_POU();

	// Sync Processing
	if (sync == D_DD_HDMAC_SYNC) {
		ret = ddHdmacWaitEnd(self, ch, status, waitMode);
	}

	return ret;
}

/*----------------------------------------------------------------------*/
/* PUBLIC(公有函数接口实现)														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/**
 * @brief  Execute exclusive control for designated HDMAC channel.
 * @param  kuchar	ch	Channel number (0 to 3)
 * @return kint32 	DriverCommon_DDIM_OK / DdHdmac_EXC_LOCK_NG / DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_open(DdHdmac *self, kuchar ch, kint32 tmout)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
	DdimUserCustom_ER ercd;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	if (DdimUserCustom_SEM_WAIT_POL == tmout) {
		ercd = ddim_user_custom_pol_sem(priv->ddimUserCustom, DdimUserCustom_SID_DD_HDMAC(ch));				// pol_sem()
	}
	else {
		ercd = ddim_user_custom_twai_sem(priv->ddimUserCustom, DdimUserCustom_SID_DD_HDMAC(ch), (DdimUserCustom_TMO)tmout);	// twai_sem()
	}

	if (DdimUserCustom_E_OK != ercd) {
		if (DdimUserCustom_E_TMOUT == ercd) {
			return DdHdmac_SEM_TIMEOUT;
		}

		return DdHdmac_SEM_NG;
	}

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Cancel exclusive control for designated HDMAC channel.
           When the designated channel is under transferring, stop transfer immediately and cancel lock.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32  DriverCommon_DDIM_OK/DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_close(DdHdmac *self, kuchar ch)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
	DdimUserCustom_ER ercd;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	// Global variable is clear
	priv->gDdHdmacCtrl[ch].configA.word = 0;
	priv->gDdHdmacCtrl[ch].configB.word = 0;
	priv->gDdHdmacCtrl[ch].srcAddr = 0;
	priv->gDdHdmacCtrl[ch].dstAddr = 0;
	priv->gDdHdmacCtrl[ch].intHandler = NULL;

	ercd = ddim_user_custom_sig_sem(priv->ddimUserCustom, DdimUserCustom_SID_DD_HDMAC(ch));				// sig_sem()
	if(DdimUserCustom_E_OK != ercd) {
		return DdHdmac_SEM_NG;
	}

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Set control data to registers related HDMAC designated channel.
 * @param  kuchar	ch	Channel number (0 to 3)
 * @return kint32	DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_ctrl_common(DdHdmac *self, kuchar ch, TDdHdmacCtrl const *const hdmacCtrl)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if (hdmacCtrl == NULL) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [*hdmacCtrl] NULL\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	// HDMAC Busy Check
//	if (ioHdmac.dmac[ch].CSTR.bit.BUSY) {
//		return DdHdmac_BUSY_ERR;
//	}

	// The value is set to an external variable
	priv->gDdHdmacCtrl[ch].configA.word = (hdmacCtrl->configA.word & 0x1FFFFFFF);
	priv->gDdHdmacCtrl[ch].configB.word = (hdmacCtrl->configB.word & 0xFFFFFF00);
	priv->gDdHdmacCtrl[ch].srcAddr = hdmacCtrl->srcAddr;
	priv->gDdHdmacCtrl[ch].dstAddr = hdmacCtrl->dstAddr;
	priv->gDdHdmacCtrl[ch].intHandler = hdmacCtrl->intHandler;

	priv->gDdHdmacTcSecond[ch] = 0;
	priv->gDdHdmacWaitEndTime[ch] = DriverCommon_DDIM_WAIT_END_TIME;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Set control data to registers related HDMAC designated channel.
 * @param  kuchar	ch	Channel number (0 to 3)
 * @return kint32	DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_ctrl_trns(DdHdmac *self, kuchar ch, TDdHdmacCtrlTrns const *const hdmacCtrlTrans)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
	kuchar  	tmpWidth;
	kulong  	tmpTc = 0;
	kushort 	tmpBc = 0;
	kuchar  	tmpBt = 0;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if (hdmacCtrlTrans == NULL) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [*hdmac_ctrl_trans] NULL\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	// HDMAC Busy Check
//	if (ioHdmac.dmac[ch].CSTR.bit.BUSY) {
//		return DdHdmac_BUSY_ERR;
//	}

	// Calucurate TC and BC
	tmpWidth = 0x01 << hdmacCtrlTrans->size.trnsWidth;
	if ((hdmacCtrlTrans->size.trnsSize% tmpWidth) != 0) {
		DriverCommon_DDIM_PRINT(("HDMAC: input param error. illegal alignment.\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}

	switch (hdmacCtrlTrans->mode.beatType) {
		case DdHdmac_BT_WRAP4:
		case DdHdmac_BT_INCR4:
			tmpBt = 4;
			break;
		case DdHdmac_BT_WRAP8:
		case DdHdmac_BT_INCR8:
			tmpBt = 8;
			break;
		case DdHdmac_BT_WRAP16:
		case DdHdmac_BT_INCR16:
		case DdHdmac_BT_INCR:
			tmpBt = 16;
			break;
		default:
			tmpBt = 16;
			break;
	}
	if ((hdmacCtrlTrans->mode.modeSel != DdHdmac_MS_DEMAND) &&
		(hdmacCtrlTrans->size.trnsSize> (tmpWidth * tmpBt))) {

		tmpBc = tmpBt - 1;
		tmpTc = (hdmacCtrlTrans->size.trnsSize/ (tmpWidth * tmpBt)) - 1;

		if ((hdmacCtrlTrans->size.trnsSize% (tmpWidth * tmpBt)) != 0) {
			priv->gDdHdmacTcSecond[ch] = ((hdmacCtrlTrans->size.trnsSize% (tmpWidth * tmpBt)) / tmpWidth);
		}
		else {
			priv->gDdHdmacTcSecond[ch] = 0;
		}
	}
	else {
		tmpBc = 0;
		tmpTc = (hdmacCtrlTrans->size.trnsSize/ tmpWidth) - 1;
		priv->gDdHdmacTcSecond[ch] = 0;
	}

	// Check TransferSize
	if ((tmpTc >= 65536) || ((tmpTc == 65535) && (priv->gDdHdmacTcSecond[ch] != 0))) {
		// Max size over
		DriverCommon_DDIM_PRINT(("HDMAC: input param error. Max size over (Max size=%d).\n", tmpWidth * tmpBt * 65536));
		return DdHdmac_INPUT_PARAM_ERR;
	}

	// The value is set to an external variable
	priv->gDdHdmacCtrl[ch].configA.bit.iS = hdmacCtrlTrans->mode.inputSel;
	priv->gDdHdmacCtrl[ch].configA.bit.bT = hdmacCtrlTrans->mode.beatType;

	priv->gDdHdmacCtrl[ch].configB.bit.mS = hdmacCtrlTrans->mode.modeSel;
	priv->gDdHdmacCtrl[ch].configB.bit.fS = hdmacCtrlTrans->mode.srcFix;
	priv->gDdHdmacCtrl[ch].configB.bit.fD = hdmacCtrlTrans->mode.dstFix;

	priv->gDdHdmacCtrl[ch].configB.bit.tW = hdmacCtrlTrans->size.trnsWidth;

	priv->gDdHdmacCtrl[ch].configA.bit.bC = tmpBc;
	priv->gDdHdmacCtrl[ch].configA.bit.tC = (kushort)tmpTc;

	priv->gDdHdmacCtrl[ch].configB.bit.dP = 0x08;		// HPROT[3] Cachable (Source Protection)
	priv->gDdHdmacCtrl[ch].configB.bit.sP = 0x08;		// HPROT[3] Cachable (Destination Protection)

	priv->gDdHdmacCtrl[ch].srcAddr = hdmacCtrlTrans->size.srcAddr;
	priv->gDdHdmacCtrl[ch].dstAddr = hdmacCtrlTrans->size.dstAddr;
	priv->gDdHdmacCtrl[ch].intHandler = hdmacCtrlTrans->intHandler;

	priv->gDdHdmacWaitEndTime[ch] = DriverCommon_DDIM_WAIT_END_TIME;

	return DriverCommon_DDIM_OK;
}

kint32 dd_hdmac_set_trns_size(DdHdmac *self, kuchar ch, TDdHdmacTrnsSize const *const hdmacTrnsSize)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
	kuchar  	tmpWidth;
	kulong  	tmpTc = 0;
	kushort 	tmpBc = 0;
	kuchar  	tmpBt = 0;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if (hdmacTrnsSize == NULL) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [*hdmacTrnsSize] NULL\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	// HDMAC Busy Check
//	if (ioHdmac.dmac[ch].CSTR.bit.BUSY) {
//		return DdHdmac_BUSY_ERR;
//	}

	// Calucurate TC and BC
	tmpWidth = 0x01 << hdmacTrnsSize->trnsWidth;
	if ((hdmacTrnsSize->trnsSize % tmpWidth) != 0) {
		DriverCommon_DDIM_PRINT(("HDMAC: input param error. illegal alignment.\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}

	switch (priv->gDdHdmacCtrl[ch].configA.bit.bT) {
		case DdHdmac_BT_WRAP4:
		case DdHdmac_BT_INCR4:
			tmpBt = 4;
			break;
		case DdHdmac_BT_WRAP8:
		case DdHdmac_BT_INCR8:
			tmpBt = 8;
			break;
		case DdHdmac_BT_WRAP16:
		case DdHdmac_BT_INCR16:
		case DdHdmac_BT_INCR:
			tmpBt = 16;
			break;
		default:
			tmpBt = 16;
			break;
	}
	if ((priv->gDdHdmacCtrl[ch].configB.bit.mS != DdHdmac_MS_DEMAND) &&
		(hdmacTrnsSize->trnsSize > (tmpWidth * tmpBt))) {
		tmpBc = tmpBt - 1;
		tmpTc = (hdmacTrnsSize->trnsSize / (tmpWidth * tmpBt)) - 1;

		if ((hdmacTrnsSize->trnsSize % (tmpWidth * tmpBt)) != 0) {
			priv->gDdHdmacTcSecond[ch] = ((hdmacTrnsSize->trnsSize % (tmpWidth * tmpBt)) / tmpWidth);
		}
		else {
			priv->gDdHdmacTcSecond[ch] = 0;
		}
	}
	else {
		tmpBc = 0;
		tmpTc = (hdmacTrnsSize->trnsSize / tmpWidth) - 1;
		priv->gDdHdmacTcSecond[ch] = 0;
	}

	// Check TransferSize
	if ((tmpTc >= 65536) || ((tmpTc == 65535) && (priv->gDdHdmacTcSecond[ch] != 0))) {
		// Max size over
		DriverCommon_DDIM_PRINT(("HDMAC: input param error. Max size over (Max size=%d).\n", tmpWidth * tmpBt * 65536));
		return DdHdmac_INPUT_PARAM_ERR;
	}

	// The value is set to an external variable
	priv->gDdHdmacCtrl[ch].configB.bit.tW = hdmacTrnsSize->trnsWidth;

	priv->gDdHdmacCtrl[ch].configA.bit.bC = tmpBc;
	priv->gDdHdmacCtrl[ch].configA.bit.tC = (kushort)tmpTc;

	priv->gDdHdmacCtrl[ch].srcAddr = hdmacTrnsSize->srcAddr;
	priv->gDdHdmacCtrl[ch].dstAddr = hdmacTrnsSize->dstAddr;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC of specified ch begins.
 * @param  kuchar				ch				Channel number (0 to 3)
 *         T_DD_HDMAC_START*	hdmac_start		HDMAC Start table
 *         kushort*			status		Channel Status Register pointer
 *         kuint32			waitMode	HDMAC end wait mode
 * @return kint32			DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR / D_DDIM_TIMEOUT / DdHdmac_SYSTEM_ERR
 */
kint32 dd_hdmac_start_sync(DdHdmac *self, kuchar ch, kushort *const status, kuint32 waitMode)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
	kint32 ret;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if (status == NULL) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [*status] NULL\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if ((waitMode != DdHdmac_WAITMODE_CPU) && (waitMode != DdHdmac_WAITMODE_EVENT)) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [waitMode] = %x\n", waitMode));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	ret = ddHdmacStart(self, ch, status, waitMode, D_DD_HDMAC_SYNC);		// HDMAC Start

	if ((*status == DdHdmac_SS_NORMAL_END) && (priv->gDdHdmacTcSecond[ch] != 0)) {
		// restart
		priv->gDdHdmacCtrl[ch].configA.bit.bC = 0;
		priv->gDdHdmacCtrl[ch].configA.bit.tC = priv->gDdHdmacTcSecond[ch] - 1;

		priv->gDdHdmacCtrl[ch].srcAddr = ioHdmac.dmac[ch].dmacsa;
		priv->gDdHdmacCtrl[ch].dstAddr = ioHdmac.dmac[ch].dmacda;

		priv->gDdHdmacTcSecond[ch] = 0;
		ddHdmacStart(self, ch, status, waitMode, D_DD_HDMAC_SYNC);	// HDMAC Start
	}

	return ret;
}

/**
 * @brief  The operation of HDMAC of specified ch begins.
 * @param  kuchar				ch				Channel number (0 to 3)
 *         T_DD_HDMAC_START*	hdmac_start		HDMAC Start table
 * @return kint32			DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_start_async(DdHdmac *self, kuchar ch)
{
	kushort	status;	// dummy

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	ddHdmacStart(self, ch, &status, DdHdmac_WAITMODE_EVENT, D_DD_HDMAC_ASYNC);	// HDMAC Start
	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Wait end time of transfer process of designated channel.
 * @param  kuchar	ch			Channel number (0 to 3)
 *         kint32	waitTime	Wait end time of transfer process
 * @return kint32				DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_set_wait_time(DdHdmac *self, kuchar ch, kint32 waitTime)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if (waitTime < DriverCommon_DDIM_WAIT_END_FOREVER) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [waitTime] = %d\n", waitTime));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	priv->gDdHdmacWaitEndTime[ch] = waitTime;
	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Wait end of transfer process of designated channel.
 *         The value of the CSTR register is passed by the out parameter.
 * @param  kuchar	ch			Channel number (0 to 3)
 *         kushort*	status		Channel Status Register pointer
 * @return kint32	DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR / D_DDIM_TIMEOUT / DdHdmac_SYSTEM_ERR
 */
kint32 dd_hdmac_wait_end(DdHdmac *self, kuchar ch, kushort* const status, kuint32 waitMode)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
	kint32 ret;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if (status == NULL) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [*status] NULL\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if ((waitMode != DdHdmac_WAITMODE_CPU) && (waitMode != DdHdmac_WAITMODE_EVENT)) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [waitMode] = %x\n", waitMode));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	ret = ddHdmacWaitEnd(self, ch, status, waitMode);

	if ((*status == DdHdmac_SS_NORMAL_END) && (priv->gDdHdmacTcSecond[ch] != 0)) {
		// restart
		priv->gDdHdmacCtrl[ch].configA.bit.bC = 0;
		priv->gDdHdmacCtrl[ch].configA.bit.tC = priv->gDdHdmacTcSecond[ch] - 1;

		priv->gDdHdmacCtrl[ch].srcAddr = ioHdmac.dmac[ch].dmacsa;
		priv->gDdHdmacCtrl[ch].dstAddr = ioHdmac.dmac[ch].dmacda;

		priv->gDdHdmacTcSecond[ch] = 0;
		ddHdmacStart(self, ch, status, DdHdmac_WAITMODE_EVENT, D_DD_HDMAC_ASYNC);	// HDMAC Start
		ret = ddHdmacWaitEnd(self, ch, status, waitMode);
	}

	return ret;
}

/**
The value of the transferd size of the specified channel is acquired.
@param [in] ch				Channel number (0 to 3)
@retval size						transferd size of the specified channel
@remarks This API forced cancel exclusive control if process is under executing.
*/
kulong dd_hdmac_get_trns_size(DdHdmac *self, kuchar ch)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
	kulong  	totalSize;
	kulong  	remainSize;
	kushort 	tc;
	kuchar  	bc;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	tc = ioHdmac.dmac[ch].dmaca.bit.tc;
	bc = ioHdmac.dmac[ch].dmaca.bit.bc;
	remainSize = (bc + 1) * (tc + 1) * (1 << priv->gDdHdmacCtrl[ch].configB.bit.tW);

	if ((tc == 0) && (bc == 0)) {
		if (((ioHdmac.dmac[ch].dmacb.word & 0x00070000) != 0x00000000) || (priv->gDdHdmacStopStatus[ch] != 0)) {
			remainSize = 0;
		}
	}

	if (priv->gDdHdmacTcSecond[ch] != 0) {
		remainSize += (priv->gDdHdmacTcSecond[ch]) * (1 << priv->gDdHdmacCtrl[ch].configB.bit.tW);
	}

	totalSize = (priv->gDdHdmacCtrl[ch].configA.bit.bC + 1) * (priv->gDdHdmacCtrl[ch].configA.bit.tC + 1) *\
			(1 << priv->gDdHdmacCtrl[ch].configB.bit.tW);
	if (priv->gDdHdmacTcSecond[ch] != 0) {
		totalSize += (priv->gDdHdmacTcSecond[ch]) * (1 << priv->gDdHdmacCtrl[ch].configB.bit.tW);
	}

	return (totalSize - remainSize);
}

/**
The value of the remainder transfer size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 3)
@retval size						remainder transfer size of the specified channel
@remarks This API forced cancel exclusive control if process is under executing.
*/
kulong dd_hdmac_get_remain_trns_size(DdHdmac *self, kuchar ch)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
	kulong  	remainSize;
	kushort	tc;
	kuchar  	bc;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	tc = ioHdmac.dmac[ch].dmaca.bit.tc;
	bc = ioHdmac.dmac[ch].dmaca.bit.bc;
	remainSize = (bc + 1) * (tc + 1) * (1 << priv->gDdHdmacCtrl[ch].configB.bit.tW);

	if ((tc == 0) && (bc == 0)) {
		if (((ioHdmac.dmac[ch].dmacb.word & 0x00070000) != 0x00000000) || (priv->gDdHdmacStopStatus[ch] != 0)) {
			remainSize = 0;
		}
	}

	if (priv->gDdHdmacTcSecond[ch] != 0) {
		remainSize += (priv->gDdHdmacTcSecond[ch]) * (1 << priv->gDdHdmacCtrl[ch].configB.bit.tW);
	}

	return remainSize;
}

/**
The value of the total transfer size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 3)
@retval size						total transfer size of the specified channel
*/
kulong dd_hdmac_get_total_trns_size(DdHdmac *self, kuchar ch)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
	kulong 	totalSize;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	totalSize = (priv->gDdHdmacCtrl[ch].configA.bit.bC + 1) * (priv->gDdHdmacCtrl[ch].configA.bit.tC + 1) *\
			(1 << priv->gDdHdmacCtrl[ch].configB.bit.tW);
	if (priv->gDdHdmacTcSecond[ch] != 0) {
		totalSize += (priv->gDdHdmacTcSecond[ch]) * (1 << priv->gDdHdmacCtrl[ch].configB.bit.tW);
	}

	return totalSize;
}

/**
 * @brief  Set HDMAC Interrupt Handler
 * @param  HDMAC channel, interrupt handler
 * @return void
 */
void dd_hdmac_set_int_handler(DdHdmac *self, kuchar ch, void (*IntHandlerFunc)(void))
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return;
	}
#endif

	priv->gDdHdmacCtrl[ch].intHandler = IntHandlerFunc;
}

/**
 * @brief  Interrupt handler of HDMAC channel 0 for transfer process is finished.
 * @param  void
 * @return void
 */
void dd_hdmac_int_handler(DdHdmac *self, kuchar ch)
{
	DdHdmacPrivate *priv = DD_HDMAC_GET_PRIVATE(self);
	DdimUserCustom_ER 	ercd;
	kushort 							status;
	VpCallback 					handler;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return;
	}
#endif

	status = ioHdmac.dmac[ch].dmacb.bit.ss;		// To give the user the content of the SS of dmacb register
	priv->gDdHdmacStopStatus[ch] = status;
	ioHdmac.dmac[ch].dmacb.bit.ss = 0x0;			// Stop Status clear
	ioHdmac.dmac[ch].dmaca.bit.eb = 0;				// HDMAC Stop
	DD_ARM_DSB_POU();

	if ((status != DdHdmac_SS_NORMAL_END) || (priv->gDdHdmacTcSecond[ch] == 0)) {
		handler = priv->gDdHdmacCtrl[ch].intHandler;

		if (handler != NULL) {
			(*handler)(ch, &status);
		}

		switch (ch) {
			case 0:
				ercd = ddim_user_custom_set_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, DdHdmac_FLG_CH0);
				break;

			case 1:
				ercd = ddim_user_custom_set_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, DdHdmac_FLG_CH1);
				break;

			case 2:
				ercd = ddim_user_custom_set_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, DdHdmac_FLG_CH2);
				break;

			case 3:
				ercd = ddim_user_custom_set_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, DdHdmac_FLG_CH3);
				break;

			default:
				ercd = -1;
				break;
		}

		if (ercd != DdimUserCustom_E_OK) {
			DriverCommon_DDIM_PRINT(("I:DDIM_User_Set_Flg error. ercd = %d\n", ercd));
		}
	}
	else if (priv->gDdHdmacTcSecond[ch] != 0) {
		// restart
		priv->gDdHdmacCtrl[ch].configA.bit.bC = 0;
		priv->gDdHdmacCtrl[ch].configA.bit.bT = 0;
		priv->gDdHdmacCtrl[ch].configA.bit.tC = priv->gDdHdmacTcSecond[ch] - 1;

		priv->gDdHdmacCtrl[ch].srcAddr = ioHdmac.dmac[ch].dmacsa;
		priv->gDdHdmacCtrl[ch].dstAddr = ioHdmac.dmac[ch].dmacda;

		priv->gDdHdmacTcSecond[ch] = 0;
		ddHdmacStart(self, ch, &status, DdHdmac_WAITMODE_EVENT, D_DD_HDMAC_ASYNC);	// HDMAC Start
	}
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
/**
 * @brief  HDMAC Copy Sync for SDRAM
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  kulong		src_addr		source address
 * @param  kulong		dst_addr		destination address
 * @param  kulong		size			Copy size
 * @param  kint32		waitMode		HDMAC end wait mode
 * @return kint32		DriverCommon_DDIM_OK
 */
kint32 dd_hdmac_copy_sdram_sync(DdHdmac *self, kuchar ch, kulong size, kuint32 waitMode)
{
	DdHdmacPrivate 			*priv = DD_HDMAC_GET_PRIVATE(self);
	kint32                 			ret;
	kushort                			status = 0;
	TDdHdmacCtrlTrns 		hdmacCtrlTrns;
	kuchar 							tmpWidth;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if ((self->srcAddr == 0) || (self->dstAddr == 0)) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [addr] = 0\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if (size == 0) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [size] = 0\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if ((waitMode != DdHdmac_WAITMODE_CPU) && (waitMode != DdHdmac_WAITMODE_EVENT)) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [waitMode] = %x\n", waitMode));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	// Check transfer size
	if (((self->srcAddr & 0x03) == 0) && ((self->dstAddr & 0x03) == 0) && ((size & 0x03) == 0)) {
		hdmacCtrlTrns.size.trnsWidth = DdHdmac_TW_WORD;
	}
	else if (((self->srcAddr & 0x01) == 0) && ((self->dstAddr & 0x01) == 0) && ((size & 0x01) == 0)) {
		hdmacCtrlTrns.size.trnsWidth = DdHdmac_TW_HWORD;
	}
	else {
		hdmacCtrlTrns.size.trnsWidth = DdHdmac_TW_BYTE;
	}

	// Parameter Setting
	hdmacCtrlTrns.mode.inputSel = DdHdmac_IS_SOFT;
	hdmacCtrlTrns.mode.modeSel = DdHdmac_MS_BLK;
	hdmacCtrlTrns.mode.srcFix = DdHdmac_FS_INCR;
	hdmacCtrlTrns.mode.dstFix = DdHdmac_FD_INCR;
	tmpWidth = 0x01 << hdmacCtrlTrns.size.trnsWidth;
	if (size > (tmpWidth * 16)) {
		hdmacCtrlTrns.mode.beatType = DdHdmac_BT_INCR16;
	}
	else {
		hdmacCtrlTrns.mode.beatType = DdHdmac_BT_NORMAL;
	}

	hdmacCtrlTrns.size.trnsSize= size;
	hdmacCtrlTrns.size.srcAddr = self->srcAddr;
	hdmacCtrlTrns.size.dstAddr = self->dstAddr;

	hdmacCtrlTrns.intHandler = NULL;

	ret = dd_hdmac_open(self, ch, DriverCommon_DDIM_WAIT_END_TIME);
	if (ret != DriverCommon_DDIM_OK) {
		DriverCommon_DDIM_PRINT(("HDMAC Util Copy Sync. Open ERR : ret=0x%x\n", ret));
		return ret;
	}
	while (1) {
		ret = dd_hdmac_ctrl_trns(self, ch, &hdmacCtrlTrns);
		if (ret != DriverCommon_DDIM_OK) {
			DriverCommon_DDIM_PRINT(("HDMAC Util Copy Sync. Ctrl ERR : ret=0x%x\n", ret));
			break;
		}
		ret = dd_hdmac_start_sync(self, ch, &status, waitMode);
		if (ret != DriverCommon_DDIM_OK) {
			DriverCommon_DDIM_PRINT(("HDMAC Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
		}
		break;
	}

	ret = dd_hdmac_close(self, ch);
	if (ret != DriverCommon_DDIM_OK) {
		DriverCommon_DDIM_PRINT(("HDMAC Util Copy Sync. Close ERR : ret=0x%x\n", ret));
	}

	return ret;
}

/**
 * @brief  HDMAC Copy Async SDRAM
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  kulong		src_addr		source address
 * @param  kulong		dst_addr		destination address
 * @param  kulong		size			Copy size
 * @param  VpCallback	intHandler		Callback function pointer
 * @return kint32  		DriverCommon_DDIM_OK
 */
kint32 dd_hdmac_copy_sdram_async(DdHdmac *self, kuchar ch, kulong size, VpCallback intHandler)
{
	kint32                 		ret;
	TDdHdmacCtrlTrns 	hdmacCtrlTrns;
	kuchar 						tmpWidth;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if ((self->srcAddr == 0) || (self->dstAddr == 0)) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [addr] = 0\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if (size == 0) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [size] = 0\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	// Check transfer size
	if (((self->srcAddr & 0x03) == 0) && ((self->dstAddr & 0x03) == 0) && ((size & 0x03) == 0)) {
		hdmacCtrlTrns.size.trnsWidth = DdHdmac_TW_WORD;
	}
	else if (((self->srcAddr & 0x01) == 0) && ((self->dstAddr & 0x01) == 0) && ((size & 0x01) == 0)) {
		hdmacCtrlTrns.size.trnsWidth = DdHdmac_TW_HWORD;
	}
	else {
		hdmacCtrlTrns.size.trnsWidth = DdHdmac_TW_BYTE;
	}

	// Parameter Setting
	hdmacCtrlTrns.mode.inputSel = DdHdmac_IS_SOFT;
	hdmacCtrlTrns.mode.modeSel = DdHdmac_MS_BLK;
	hdmacCtrlTrns.mode.srcFix = DdHdmac_FS_INCR;
	hdmacCtrlTrns.mode.dstFix = DdHdmac_FD_INCR;
	tmpWidth = 0x01 << hdmacCtrlTrns.size.trnsWidth;
	if (size > (tmpWidth * 16)) {
		hdmacCtrlTrns.mode.beatType = DdHdmac_BT_INCR16;
	}
	else {
		hdmacCtrlTrns.mode.beatType = DdHdmac_BT_NORMAL;
	}

	hdmacCtrlTrns.size.trnsSize= size;
	hdmacCtrlTrns.size.srcAddr = self->srcAddr;
	hdmacCtrlTrns.size.dstAddr = self->dstAddr;

	hdmacCtrlTrns.intHandler = intHandler;

	ret = dd_hdmac_ctrl_trns(self, ch, &hdmacCtrlTrns);
	if (ret != DriverCommon_DDIM_OK) {
		DriverCommon_DDIM_PRINT(("HDMAC Util Copy Async. Ctrl ERR : ret=0x%x\n", ret));
		return ret;
	}
	ret = dd_hdmac_start_async(self, ch);
	if (ret != DriverCommon_DDIM_OK) {
		DriverCommon_DDIM_PRINT(("HDMAC Util Copy Async. Start ERR : ret=0x%x\n", ret));
		return ret;
	}
	return ret;
}

//---------------------- colabo  section -------------------------------
// Nothing Special
#endif

DdHdmac* dd_hdmac_get(void)
{
	static DdHdmac *ddHdmac = NULL;
	if(!ddHdmac)
	{
		ddHdmac = k_object_new_with_private(DD_TYPE_HDMAC,sizeof(DdHdmacPrivate));
	}
	return ddHdmac;
}
