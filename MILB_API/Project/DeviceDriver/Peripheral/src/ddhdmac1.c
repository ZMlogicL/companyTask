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


#include "peripheral.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#include "dd_arm.h"
#include "ddhdmac1.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdHdmac1, dd_hdmac1);
#define DD_HDMAC1_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdHdmac1Private, DD_TYPE_HDMAC1))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
#define DdHdmac1_SYNC			0		/* Sync Processing */
#define DdHdmac1_ASYNC			1		/* Async Processing */


struct _DdHdmac1Private
{
	DdHdmac1Utility* utility;
	volatile Hdmac1Ctrl gDD_HDMAC1_Ctrl[DdHdmac1_CH_NUM_MAX];		// HDMAC1 Register Info
	volatile USHORT gDD_HDMAC1_TC_Second[DdHdmac1_CH_NUM_MAX];
	volatile USHORT gDD_HDMAC1_Stop_Status[DdHdmac1_CH_NUM_MAX];
	volatile INT32 gDD_HDMAC1_Wait_End_Time[DdHdmac1_CH_NUM_MAX];
};


/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
static INT32 waitEnd(DdHdmac1Private *priv, UCHAR ch, USHORT* const status, UINT32 wait_mode);
static INT32 dd_hdmac1_start(DdHdmac1Private *priv, UCHAR ch, USHORT* const status, UINT32 wait_mode, UINT32 sync);


static void dd_hdmac1_constructor(DdHdmac1 *self)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);

	priv->utility = dd_hdmac1_utility_new();
}

static void dd_hdmac1_destructor(DdHdmac1 *self)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);

	if(priv->utility)
	{
		k_object_unref(priv->utility);
		priv->utility = NULL;
	}
}

/**
 * @brief  HDMAC1 wait end.
 */
static INT32 waitEnd(DdHdmac1Private *priv, UCHAR ch, USHORT* const status, UINT32 wait_mode)
{
	DDIM_USER_FLGPTN flg_ptn;
	DDIM_USER_ER ercd = 0;
	USHORT ss;

	// CPU Polling (no use interrupt)
	if (wait_mode == DdHdmac1_WAITMODE_CPU) {
		while (priv->gDD_HDMAC1_Stop_Status[ch] == 0) {
			ss = IO_HDMAC1.DMAC[ch].DMACB.bit.SS;
			if(ss) {
				priv->gDD_HDMAC1_Stop_Status[ch] = ss;
			}
		}
		
		if (priv->gDD_HDMAC1_Stop_Status[ch] == 0) {
			*status = IO_HDMAC1.DMAC[ch].DMACB.bit.SS;	// To give the user the content of the SS bit of DMACB register
			IO_HDMAC1.DMAC[ch].DMACB.bit.SS = 0x0;		// Stop Status clear
			IO_HDMAC1.DMAC[ch].DMACA.bit.EB = 0;		// HDMAC1 Stop
		}
		else {
			*status = priv->gDD_HDMAC1_Stop_Status[ch];
			priv->gDD_HDMAC1_Stop_Status[ch] = 0;
		}
	}
	// EVENT (use interrupt)
	else {
		switch (ch) {
			case 0:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH0, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC1_Wait_End_Time[ch]);
				break;

			case 1:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH1, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC1_Wait_End_Time[ch]);
				break;

			case 2:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH2, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC1_Wait_End_Time[ch]);
				break;

			case 3:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH3, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC1_Wait_End_Time[ch]);
				break;

			case 4:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH4, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC1_Wait_End_Time[ch]);
				break;

			case 5:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH5, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC1_Wait_End_Time[ch]);
				break;

			case 6:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH6, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC1_Wait_End_Time[ch]);
				break;

			case 7:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH7, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC1_Wait_End_Time[ch]);
				break;

			default:
				break;
		}

		*status = priv->gDD_HDMAC1_Stop_Status[ch];		// To give the user the content of the SS bit of DMACB register
		priv->gDD_HDMAC1_Stop_Status[ch] = 0;
	}

	if (ercd == D_DDIM_USER_E_TMOUT) {
		Ddim_Print(("HDMAC1 error. timeout!"));
		return DdHdmac1_TIMEOUT_ERR;
	}

	if (ercd != D_DDIM_USER_E_OK) {
		Ddim_Print(("HDMAC1 error. system error!"));
		return DdHdmac1_SYSTEM_ERR;
	}

	return D_DDIM_OK;
}

/**
 * @brief  HDMAC1 start.
 */
static INT32 dd_hdmac1_start(DdHdmac1Private *priv, UCHAR ch, USHORT* const status, UINT32 wait_mode, UINT32 sync)
{
	INT32 ret = D_DDIM_OK;

	// HDMAC1 Enable
	if (IO_HDMAC1.DMACR.bit.DE == 0) {
		IO_HDMAC1.DMACR.bit.DE = 1;							// HDMAC1 all ch enable
	}

	// HDMAC1 Busy Check
	if (IO_HDMAC1.DMAC[ch].DMACA.bit.EB) {
		return DdHdmac1_BUSY_ERR;
	}

	if (wait_mode == DdHdmac1_WAITMODE_EVENT) {
		priv->gDD_HDMAC1_Ctrl[ch].configB.bit.ei = 1;				// Error Interrupt Enable
		priv->gDD_HDMAC1_Ctrl[ch].configB.bit.ci = 1;				// Completion Interrupt Enable
	}

	priv->gDD_HDMAC1_Stop_Status[ch] = 0;
	IO_HDMAC1.DMAC[ch].DMACA.word = priv->gDD_HDMAC1_Ctrl[ch].configA.word;	// HDMAC1 Config A register set
	IO_HDMAC1.DMAC[ch].DMACB.word = priv->gDD_HDMAC1_Ctrl[ch].configB.word;	// HDMAC1 Config B register set
	IO_HDMAC1.DMAC[ch].DMACSA     = priv->gDD_HDMAC1_Ctrl[ch].srcAddr;		// HDMAC1 Source Address register set
	IO_HDMAC1.DMAC[ch].DMACDA     = priv->gDD_HDMAC1_Ctrl[ch].dstAddr;		// HDMAC1 Destination Address register set

	if (wait_mode == DdHdmac1_WAITMODE_EVENT) {
		switch (ch) {
			case 0:
				DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH0);
				break;

			case 1:
				DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH1);
				break;

			case 2:
				DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH2);
				break;

			case 3:
				DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH3);
				break;

			case 4:
				DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH4);
				break;

			case 5:
				DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH5);
				break;

			case 6:
				DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH6);
				break;

			case 7:
				DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH7);
				break;

			default:
				break;
		}
	}

	IO_HDMAC1.DMAC[ch].DMACA.bit.EB = 1;			// HDMAC1 Start
	if (priv->gDD_HDMAC1_Ctrl[ch].configA.bit.is == DdHdmac1_IS_SOFT) {
		IO_HDMAC1.DMAC[ch].DMACA.bit.ST = 1;		// Soft trigger
	}
	Dd_ARM_Dsb_Pou();

	// Sync Processing
	if (sync == DdHdmac1_SYNC) {
		ret = waitEnd(priv, ch, status, wait_mode);
	}

	return ret;
}

/**
 * @brief  Execute exclusive control for designated HDMAC1 channel.
 * @param  UCHAR	ch	Channel number (0 to 7)
 * @return INT32 	D_DDIM_OK / DdHdmac1_EXC_LOCK_NG / DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_open(DdHdmac1 *self, UCHAR ch, INT32 tmout)
{
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	if (D_DDIM_USER_SEM_WAIT_POL == tmout) {
		ercd = DDIM_User_Pol_Sem(SID_DD_HDMAC1(ch));				// pol_sem()
	}
	else {
		ercd = DDIM_User_Twai_Sem(SID_DD_HDMAC1(ch), (DDIM_USER_TMO)tmout);	// twai_sem()
	}

	if (D_DDIM_USER_E_OK != ercd) {
		if (D_DDIM_USER_E_TMOUT == ercd) {
			return DdHdmac1_SEM_TIMEOUT;
		}

		return DdHdmac1_SEM_NG;
	}

	return D_DDIM_OK;
}

/**
 * @brief  Cancel exclusive control for designated HDMAC1 channel.
           When the designated channel is under transferring, stop transfer immediately and cancel lock.
 * @param  UCHAR	ch			Channel number (0 to 7)
 * @return INT32  D_DDIM_OK/DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_close(DdHdmac1 *self, UCHAR ch)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	// Global variable is clear
	priv->gDD_HDMAC1_Ctrl[ch].configA.word = 0;
	priv->gDD_HDMAC1_Ctrl[ch].configB.word = 0;
	priv->gDD_HDMAC1_Ctrl[ch].srcAddr      = 0;
	priv->gDD_HDMAC1_Ctrl[ch].dstAddr      = 0;
	priv->gDD_HDMAC1_Ctrl[ch].intHandler   = NULL;

	ercd = DDIM_User_Sig_Sem(SID_DD_HDMAC1(ch));				// sig_sem()
	if(D_DDIM_USER_E_OK != ercd) {
		return DdHdmac1_SEM_NG;
	}

	return D_DDIM_OK;
}

/**
 * @brief  Set control data to registers related HDMAC1 designated channel.
 * @param  UCHAR	ch	Channel number (0 to 7)
 * @return INT32	D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_ctrl_common(DdHdmac1 *self, UCHAR ch, Hdmac1Ctrl const *const hdmac1_ctrl)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if (hdmac1_ctrl == NULL) {
		Ddim_Assertion(("HDMAC1: input param error. [*hdmac1_ctrl] NULL\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	// HDMAC1 Busy Check
//	if (IO_HDMAC1.DMAC[ch].CSTR.bit.BUSY) {
//		return DdHdmac1_BUSY_ERR;
//	}

	// The value is set to an external variable
	priv->gDD_HDMAC1_Ctrl[ch].configA.word = (hdmac1_ctrl->configA.word & 0x1FFFFFFF);
	priv->gDD_HDMAC1_Ctrl[ch].configB.word = (hdmac1_ctrl->configB.word & 0xFFFFFF00);
	priv->gDD_HDMAC1_Ctrl[ch].srcAddr      = hdmac1_ctrl->srcAddr;
	priv->gDD_HDMAC1_Ctrl[ch].dstAddr      = hdmac1_ctrl->dstAddr;
	priv->gDD_HDMAC1_Ctrl[ch].intHandler   = hdmac1_ctrl->intHandler;

	priv->gDD_HDMAC1_TC_Second[ch] = 0;
	priv->gDD_HDMAC1_Wait_End_Time[ch] = D_DDIM_WAIT_END_TIME;

	return D_DDIM_OK;
}

/**
 * @brief  Set control data to registers related HDMAC1 designated channel.
 * @param  UCHAR	ch	Channel number (0 to 7)
 * @return INT32	D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_ctrl_trns(DdHdmac1 *self, UCHAR ch, Hdmac1CtrlTrns const *const hdmac1_ctrl_trans)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);
	UCHAR  tmp_width;
	ULONG  tmp_tc = 0;
	USHORT tmp_bc = 0;
	UCHAR  tmp_bt = 0;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if (hdmac1_ctrl_trans == NULL) {
		Ddim_Assertion(("HDMAC1: input param error. [*hdmac1_ctrl_trans] NULL\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	// HDMAC1 Busy Check
//	if (IO_HDMAC1.DMAC[ch].CSTR.bit.BUSY) {
//		return DdHdmac1_BUSY_ERR;
//	}

	// Calucurate TC and BC
	tmp_width = 0x01 << hdmac1_ctrl_trans->size.trnsWidth;
	if ((hdmac1_ctrl_trans->size.trnsSize % tmp_width) != 0) {
		Ddim_Print(("HDMAC1: input param error. illegal alignment.\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}

	switch (hdmac1_ctrl_trans->mode.beatType) {
		case DdHdmac1_BT_WRAP4:
		case DdHdmac1_BT_INCR4:
			tmp_bt = 4;
			break;
		case DdHdmac1_BT_WRAP8:
		case DdHdmac1_BT_INCR8:
			tmp_bt = 8;
			break;
		case DdHdmac1_BT_WRAP16:
		case DdHdmac1_BT_INCR16:
		case DdHdmac1_BT_INCR:
			tmp_bt = 16;
			break;
		default:
			tmp_bt = 16;
			break;
	}
	if ((hdmac1_ctrl_trans->mode.modeSel != DdHdmac1_MS_DEMAND) &&
		(hdmac1_ctrl_trans->size.trnsSize > (tmp_width * tmp_bt))) {

		tmp_bc = tmp_bt - 1;
		tmp_tc = (hdmac1_ctrl_trans->size.trnsSize / (tmp_width * tmp_bt)) - 1;

		if ((hdmac1_ctrl_trans->size.trnsSize % (tmp_width * tmp_bt)) != 0) {
			priv->gDD_HDMAC1_TC_Second[ch] = ((hdmac1_ctrl_trans->size.trnsSize % (tmp_width * tmp_bt)) / tmp_width);
		}
		else {
			priv->gDD_HDMAC1_TC_Second[ch] = 0;
		}
	}
	else {
		tmp_bc = 0;
		tmp_tc = (hdmac1_ctrl_trans->size.trnsSize / tmp_width) - 1;
		priv->gDD_HDMAC1_TC_Second[ch] = 0;
	}

	// Check TransferSize
	if ((tmp_tc >= 65536) || ((tmp_tc == 65535) && (priv->gDD_HDMAC1_TC_Second[ch] != 0))) {
		// Max size over
		Ddim_Print(("HDMAC1: input param error. Max size over (Max size=%d).\n", tmp_width * tmp_bt * 65536));
		return DdHdmac1_INPUT_PARAM_ERR;
	}

	// The value is set to an external variable
	priv->gDD_HDMAC1_Ctrl[ch].configA.bit.is = hdmac1_ctrl_trans->mode.inputSel;
	priv->gDD_HDMAC1_Ctrl[ch].configA.bit.bt = hdmac1_ctrl_trans->mode.beatType;

	priv->gDD_HDMAC1_Ctrl[ch].configB.bit.ms = hdmac1_ctrl_trans->mode.modeSel;
	priv->gDD_HDMAC1_Ctrl[ch].configB.bit.fs = hdmac1_ctrl_trans->mode.srcFix;
	priv->gDD_HDMAC1_Ctrl[ch].configB.bit.fd = hdmac1_ctrl_trans->mode.dstFix;

	priv->gDD_HDMAC1_Ctrl[ch].configB.bit.tw = hdmac1_ctrl_trans->size.trnsWidth;

	priv->gDD_HDMAC1_Ctrl[ch].configA.bit.bc = tmp_bc;
	priv->gDD_HDMAC1_Ctrl[ch].configA.bit.tc = (USHORT)tmp_tc;

	priv->gDD_HDMAC1_Ctrl[ch].configB.bit.dp = 0x08;		// HPROT[3] Cachable (Source Protection)
	priv->gDD_HDMAC1_Ctrl[ch].configB.bit.sp = 0x08;		// HPROT[3] Cachable (Destination Protection)

	priv->gDD_HDMAC1_Ctrl[ch].srcAddr        = hdmac1_ctrl_trans->size.srcAddr;
	priv->gDD_HDMAC1_Ctrl[ch].dstAddr        = hdmac1_ctrl_trans->size.dstAddr;
	priv->gDD_HDMAC1_Ctrl[ch].intHandler     = hdmac1_ctrl_trans->intHandler;

	priv->gDD_HDMAC1_Wait_End_Time[ch] = D_DDIM_WAIT_END_TIME;

	return D_DDIM_OK;
}

INT32 dd_hdmac1_set_trns_size(DdHdmac1 *self, UCHAR ch, Hdmac1TrnsSize const *const hdmac1_trns_size)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);
	UCHAR  tmp_width;
	ULONG  tmp_tc = 0;
	USHORT tmp_bc = 0;
	UCHAR  tmp_bt = 0;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if (hdmac1_trns_size == NULL) {
		Ddim_Assertion(("HDMAC1: input param error. [*hdmac1_trns_size] NULL\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	// HDMAC1 Busy Check
//	if (IO_HDMAC1.DMAC[ch].CSTR.bit.BUSY) {
//		return DdHdmac1_BUSY_ERR;
//	}

	// Calucurate TC and BC
	tmp_width = 0x01 << hdmac1_trns_size->trnsWidth;
	if ((hdmac1_trns_size->trnsSize % tmp_width) != 0) {
		Ddim_Print(("HDMAC1: input param error. illegal alignment.\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}

	switch (priv->gDD_HDMAC1_Ctrl[ch].configA.bit.bt) {
		case DdHdmac1_BT_WRAP4:
		case DdHdmac1_BT_INCR4:
			tmp_bt = 4;
			break;
		case DdHdmac1_BT_WRAP8:
		case DdHdmac1_BT_INCR8:
			tmp_bt = 8;
			break;
		case DdHdmac1_BT_WRAP16:
		case DdHdmac1_BT_INCR16:
		case DdHdmac1_BT_INCR:
			tmp_bt = 16;
			break;
		default:
			tmp_bt = 16;
			break;
	}
	if ((priv->gDD_HDMAC1_Ctrl[ch].configB.bit.ms != DdHdmac1_MS_DEMAND) &&
		(hdmac1_trns_size->trnsSize > (tmp_width * tmp_bt))) {
		tmp_bc = tmp_bt - 1;
		tmp_tc = (hdmac1_trns_size->trnsSize / (tmp_width * tmp_bt)) - 1;

		if ((hdmac1_trns_size->trnsSize % (tmp_width * tmp_bt)) != 0) {
			priv->gDD_HDMAC1_TC_Second[ch] = ((hdmac1_trns_size->trnsSize % (tmp_width * tmp_bt)) / tmp_width);
		}
		else {
			priv->gDD_HDMAC1_TC_Second[ch] = 0;
		}
	}
	else {
		tmp_bc = 0;
		tmp_tc = (hdmac1_trns_size->trnsSize / tmp_width) - 1;
		priv->gDD_HDMAC1_TC_Second[ch] = 0;
	}

	// Check TransferSize
	if ((tmp_tc >= 65536) || ((tmp_tc == 65535) && (priv->gDD_HDMAC1_TC_Second[ch] != 0))) {
		// Max size over
		Ddim_Print(("HDMAC1: input param error. Max size over (Max size=%d).\n", tmp_width * tmp_bt * 65536));
		return DdHdmac1_INPUT_PARAM_ERR;
	}

	// The value is set to an external variable
	priv->gDD_HDMAC1_Ctrl[ch].configB.bit.tw = hdmac1_trns_size->trnsWidth;

	priv->gDD_HDMAC1_Ctrl[ch].configA.bit.bc = tmp_bc;
	priv->gDD_HDMAC1_Ctrl[ch].configA.bit.tc = (USHORT)tmp_tc;

	priv->gDD_HDMAC1_Ctrl[ch].srcAddr        = hdmac1_trns_size->srcAddr;
	priv->gDD_HDMAC1_Ctrl[ch].dstAddr        = hdmac1_trns_size->dstAddr;

	return D_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC1 of specified ch begins.
 * @param  UCHAR				ch				Channel number (0 to 7)
 *         T_DD_HDMAC1_START*	hdmac1_start	HDMAC1 Start table
 *         USHORT*			status		Channel Status Register pointer
 *         UINT32			wait_mode	HDMAC1 end wait mode
 * @return INT32			D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR / D_DDIM_TIMEOUT / DdHdmac1_SYSTEM_ERR
 */
INT32 dd_hdmac1_start_sync(DdHdmac1 *self, UCHAR ch, USHORT *const status, UINT32 wait_mode)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);
	INT32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if (status == NULL) {
		Ddim_Assertion(("HDMAC1: input param error. [*status] NULL\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if ((wait_mode != DdHdmac1_WAITMODE_CPU) && (wait_mode != DdHdmac1_WAITMODE_EVENT)) {
		Ddim_Assertion(("HDMAC1: input param error. [wait_mode] = %x\n", wait_mode));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	ret = dd_hdmac1_start(priv, ch, status, wait_mode, DdHdmac1_SYNC);		// HDMAC1 Start

	if ((*status == DdHdmac1_SS_NORMAL_END) && (priv->gDD_HDMAC1_TC_Second[ch] != 0)) {
		// restart
		priv->gDD_HDMAC1_Ctrl[ch].configA.bit.bc = 0;
		priv->gDD_HDMAC1_Ctrl[ch].configA.bit.tc = priv->gDD_HDMAC1_TC_Second[ch] - 1;

		priv->gDD_HDMAC1_Ctrl[ch].srcAddr        = IO_HDMAC1.DMAC[ch].DMACSA;
		priv->gDD_HDMAC1_Ctrl[ch].dstAddr        = IO_HDMAC1.DMAC[ch].DMACDA;

		priv->gDD_HDMAC1_TC_Second[ch] = 0;
		dd_hdmac1_start(priv, ch, status, wait_mode, DdHdmac1_SYNC);	// HDMAC1 Start
	}

	return ret;
}

/**
 * @brief  The operation of HDMAC1 of specified ch begins.
 * @param  UCHAR				ch				Channel number (0 to 7)
 *         T_DD_HDMAC1_START*	hdmac1_start	HDMAC1 Start table
 * @return INT32			D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_start_async(DdHdmac1 *self, UCHAR ch)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);
	USHORT	status;	// dummy

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	dd_hdmac1_start(priv, ch, &status, DdHdmac1_WAITMODE_EVENT, DdHdmac1_ASYNC);	// HDMAC1 Start
	return D_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC1 of specified ch is stopped.
 * @param  UCHAR	ch			Channel number (0 to 7)
 * @return INT32	D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_stop(DdHdmac1 *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	IO_HDMAC1.DMAC[ch].DMACA.word &= 0x7FFFFFFF;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC1 of specified ch is stopped.
 * @param  UCHAR	ch			Channel number (0 to 7)
 * @return INT32	D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_pause(DdHdmac1 *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	IO_HDMAC1.DMAC[ch].DMACA.bit.PB = 1;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC1 of specified ch is resumed.
 * @param  UCHAR	ch			Channel number (0 to 7)
 * @return INT32	D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_resume(DdHdmac1 *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	switch (ch) {
		case 0:
			DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH0);
			break;

		case 1:
			DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH1);
			break;

		case 2:
			DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH2);
			break;

		case 3:
			DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH3);
			break;

		case 4:
			DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH4);
			break;

		case 5:
			DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH5);
			break;

		case 6:
			DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH6);
			break;

		case 7:
			DDIM_User_Clr_Flg(FID_DD_HDMAC1, ~DdHdmac1_FLG_CH7);
			break;

		default:
			break;
	}

	IO_HDMAC1.DMAC[ch].DMACA.bit.PB = 0;
	IO_HDMAC1.DMAC[ch].DMACA.bit.EB = 1;			// HDMAC1 Start
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  Wait end time of transfer process of designated channel.
 * @param  UCHAR	ch			Channel number (0 to 7)
 *         INT32	wait_time	Wait end time of transfer process
 * @return INT32				D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_set_wait_time(DdHdmac1 *self, UCHAR ch, INT32 wait_time)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if (wait_time < D_DDIM_WAIT_END_FOREVER) {
		Ddim_Assertion(("HDMAC1: input param error. [wait_time] = %d\n", wait_time));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	priv->gDD_HDMAC1_Wait_End_Time[ch] = wait_time;
	return D_DDIM_OK;
}

/**
 * @brief  Wait end of transfer process of designated channel.
 *         The value of the CSTR register is passed by the out parameter.
 * @param  UCHAR	ch			Channel number (0 to 7)
 *         USHORT*	status		Channel Status Register pointer
 * @return INT32	D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR / D_DDIM_TIMEOUT / DdHdmac1_SYSTEM_ERR
 */
INT32 dd_hdmac1_wait_end(DdHdmac1 *self, UCHAR ch, USHORT* const status, UINT32 wait_mode)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);
	INT32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if (status == NULL) {
		Ddim_Assertion(("HDMAC1: input param error. [*status] NULL\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if ((wait_mode != DdHdmac1_WAITMODE_CPU) && (wait_mode != DdHdmac1_WAITMODE_EVENT)) {
		Ddim_Assertion(("HDMAC1: input param error. [wait_mode] = %x\n", wait_mode));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

#ifdef CO_DEBUG_ON_PC
	ret = D_DDIM_OK;
	*status = DdHdmac1_SS_NORMAL_END;
#else
	ret = waitEnd(priv, ch, status, wait_mode);
#endif

	if ((*status == DdHdmac1_SS_NORMAL_END) && (priv->gDD_HDMAC1_TC_Second[ch] != 0)) {
		// restart
		priv->gDD_HDMAC1_Ctrl[ch].configA.bit.bc = 0;
		priv->gDD_HDMAC1_Ctrl[ch].configA.bit.tc = priv->gDD_HDMAC1_TC_Second[ch] - 1;

		priv->gDD_HDMAC1_Ctrl[ch].srcAddr        = IO_HDMAC1.DMAC[ch].DMACSA;
		priv->gDD_HDMAC1_Ctrl[ch].dstAddr        = IO_HDMAC1.DMAC[ch].DMACDA;

		priv->gDD_HDMAC1_TC_Second[ch] = 0;
		dd_hdmac1_start(priv, ch, status, DdHdmac1_WAITMODE_EVENT, DdHdmac1_ASYNC);	// HDMAC1 Start
		ret = waitEnd(priv, ch, status, wait_mode);
	}

	return ret;
}

/**
 * @brief  The status of HDMAC1 of specified ch is cleared.
 * @param  UCHAR	ch			Channel number (0 to 7)
 * @return INT32				D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_clear_status(DdHdmac1 *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	IO_HDMAC1.DMAC[ch].DMACB.bit.SS = 0;

	return D_DDIM_OK;
}

/**
 * @brief  The error status of HDMAC1 of specified ch is cleared.
 * @param  UCHAR	ch			Channel number (0 to 7)
 * @return INT32				D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_get_status(DdHdmac1 *self, UCHAR ch, USHORT *const status)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if (status == NULL) {
		Ddim_Assertion(("HDMAC1: input param error. [*status] NULL\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	*status = IO_HDMAC1.DMAC[ch].DMACB.bit.SS;
	return D_DDIM_OK;
}

/**
The value of the transferd size of the specified channel is acquired.
@param [in] ch				Channel number (0 to 7)
@retval size						transferd size of the specified channel
@remarks This API forced cancel exclusive control if process is under executing.
*/
ULONG dd_hdmac1_get_trns_size(DdHdmac1 *self, UCHAR ch)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);
	ULONG  total_size;
	ULONG  remain_size;
	USHORT tc;
	UCHAR  bc;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	tc = IO_HDMAC1.DMAC[ch].DMACA.bit.TC;
	bc = IO_HDMAC1.DMAC[ch].DMACA.bit.BC;
	remain_size = (bc + 1) * (tc + 1) * (1 << priv->gDD_HDMAC1_Ctrl[ch].configB.bit.tw);

	if ((tc == 0) && (bc == 0)) {
		if (((IO_HDMAC1.DMAC[ch].DMACB.word & 0x00070000) != 0x00000000) || (priv->gDD_HDMAC1_Stop_Status[ch] != 0)) {
			remain_size = 0;
		}
	}

	if (priv->gDD_HDMAC1_TC_Second[ch] != 0) {
		remain_size += (priv->gDD_HDMAC1_TC_Second[ch]) * (1 << priv->gDD_HDMAC1_Ctrl[ch].configB.bit.tw);
	}

	total_size = (priv->gDD_HDMAC1_Ctrl[ch].configA.bit.bc + 1) * (priv->gDD_HDMAC1_Ctrl[ch].configA.bit.tc + 1) * (1 << priv->gDD_HDMAC1_Ctrl[ch].configB.bit.tw);
	if (priv->gDD_HDMAC1_TC_Second[ch] != 0) {
		total_size += (priv->gDD_HDMAC1_TC_Second[ch]) * (1 << priv->gDD_HDMAC1_Ctrl[ch].configB.bit.tw);
	}

	return (total_size - remain_size);
}

/**
The value of the remainder transfer size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval size						remainder transfer size of the specified channel
@remarks This API forced cancel exclusive control if process is under executing.
*/
ULONG dd_hdmac1_get_remain_trns_size(DdHdmac1 *self, UCHAR ch)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);
	ULONG  remain_size;
	USHORT tc;
	UCHAR  bc;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	tc = IO_HDMAC1.DMAC[ch].DMACA.bit.TC;
	bc = IO_HDMAC1.DMAC[ch].DMACA.bit.BC;
	remain_size = (bc + 1) * (tc + 1) * (1 << priv->gDD_HDMAC1_Ctrl[ch].configB.bit.tw);

	if ((tc == 0) && (bc == 0)) {
		if (((IO_HDMAC1.DMAC[ch].DMACB.word & 0x00070000) != 0x00000000) || (priv->gDD_HDMAC1_Stop_Status[ch] != 0)) {
			remain_size = 0;
		}
	}

	if (priv->gDD_HDMAC1_TC_Second[ch] != 0) {
		remain_size += (priv->gDD_HDMAC1_TC_Second[ch]) * (1 << priv->gDD_HDMAC1_Ctrl[ch].configB.bit.tw);
	}

	return remain_size;
}

/**
The value of the total transfer size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval size						total transfer size of the specified channel
*/
ULONG dd_hdmac1_get_total_trns_size(DdHdmac1 *self, UCHAR ch)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);
	ULONG total_size;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	total_size = (priv->gDD_HDMAC1_Ctrl[ch].configA.bit.bc + 1) * (priv->gDD_HDMAC1_Ctrl[ch].configA.bit.tc + 1) * (1 << priv->gDD_HDMAC1_Ctrl[ch].configB.bit.tw);
	if (priv->gDD_HDMAC1_TC_Second[ch] != 0) {
		total_size += (priv->gDD_HDMAC1_TC_Second[ch]) * (1 << priv->gDD_HDMAC1_Ctrl[ch].configB.bit.tw);
	}

	return total_size;
}

/**
The value of the source address (DMACSA) of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval srcAddr					Source address of the specified channel
*/
ULONG dd_hdmac1_get_src_addr(DdHdmac1 *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	return IO_HDMAC1.DMAC[ch].DMACSA;
}

/**
The value of the destination address (DMACDA) of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval dstAddr					Destination address of the specified channel
*/
ULONG dd_hdmac1_get_dst_addr(DdHdmac1 *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	return IO_HDMAC1.DMAC[ch].DMACDA;
}

/**
The value of the taransfer count (TC) of the specified channel is get.

@param [in] ch				Channel number (0 to 7)
@param [out] trans_count	Transfer Count (0 to 65535)
@retval D_DDIM_OK					OK
@retval DdHdmac1_INPUT_PARAM_ERR	Input Parameter Error
*/
INT32 dd_hdmac1_get_trans_count(DdHdmac1 *self, UCHAR ch, ULONG* const trans_count)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	*trans_count = IO_HDMAC1.DMAC[ch].DMACA.bit.TC;

	return D_DDIM_OK;
}

/**
Source Protection code is set.

@param [in] ch					Channel number (0 to 7)
@param [in] protect_code		Protection Code
@retval D_DDIM_OK					OK
@retval DdHdmac1_INPUT_PARAM_ERR	Input Parameter Error
*/
INT32 dd_hdmac1_set_source_protect(DdHdmac1 *self, UCHAR ch, UCHAR protect_code)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	IO_HDMAC1.DMAC[ch].DMACB.bit.SP = protect_code;
	return D_DDIM_OK;
}

/**
Destination Protection code is set.

@param [in] ch					Channel number (0 to 7)
@param [in] protect_code		Protection Code
@retval D_DDIM_OK					OK
@retval DdHdmac1_INPUT_PARAM_ERR	Input Parameter Error
*/
INT32 dd_hdmac1_set_destination_protect(DdHdmac1 *self, UCHAR ch, UCHAR protect_code)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	IO_HDMAC1.DMAC[ch].DMACB.bit.DP = protect_code;
	return D_DDIM_OK;
}

/**
 * @brief  Arbitration level and HDMAC1 forwarding control interrupt level of all channels are set.
 * @param  T_DD_HDMAC1_ARBITRATION*	arbitration
 * @return INT32				D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_set_arbitration(DdHdmac1 *self, UCHAR arbitration)
{
#ifdef CO_PARAM_CHECK
	if ((arbitration != DdHdmac1_ARB_FIX) && (arbitration != DdHdmac1_ARB_ROTATE)) {
		Ddim_Assertion(("HDMAC1: input param error. [arbitration] = %x\n", arbitration));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	// Arbitration type is set
	IO_HDMAC1.DMACR.bit.PR = arbitration;

	return D_DDIM_OK;
}

/**
 * @brief  Arbitration level and HDMAC1 forwarding control interrupt level of all channels are read.
 * @param  T_DD_HDMAC1_ARBITRATION*	arbitration
 * @return INT32				D_DDIM_OK / DdHdmac1_INPUT_PARAM_ERR
 */
INT32 dd_hdmac1_get_arbitration(DdHdmac1 *self, UCHAR *const arbitration)
{
#ifdef CO_PARAM_CHECK
	if (arbitration == NULL) {
		Ddim_Assertion(("HDMAC1: input param error. [*arbitration] NULL\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	// Arbitration type is set
	*arbitration = IO_HDMAC1.DMACR.bit.PR;

	return D_DDIM_OK;
}

/**
 * @brief  Arbitration level and HDMAC1 forwarding control interrupt level of all channels are returned to an initial value.
 * @param  VOID
 * @return VOID
 */
VOID dd_hdmac1_clear_arbitration(DdHdmac1 *self)
{
	// Arbitration type is set
	IO_HDMAC1.DMACR.bit.PR = 0;
}

/**
The operation of All HDMAC1 channel is stopped.
*/
VOID dd_hdmac1_stop_all_ch(DdHdmac1 *self)
{
	// HDMAC1 Halt
	IO_HDMAC1.DMACR.bit.DH = 1;
}

/**
The operation of All HDMAC1 channel is resumed.
*/
VOID dd_hdmac1_resume_all_ch(DdHdmac1 *self)
{
	// HDMAC1 resume
	IO_HDMAC1.DMACR.bit.DH = 0;
}

/**
It is API that returns the value set to the register of TW. 

@param [in] srcAddr			soruce address
@param [in] dstAddr			destination address
@param [in] total_size			total size
@retval TW value set to register of TW
*/
UCHAR dd_hdmac1_get_trns_width(DdHdmac1 *self, ULONG srcAddr, ULONG dstAddr, ULONG total_size)
{
	UCHAR trnsWidth;

	// Check transfer size
	if (((srcAddr & 0x03) == 0) && ((dstAddr & 0x03) == 0) && ((total_size & 0x03) == 0)) {
		trnsWidth = DdHdmac1_TW_WORD;
	}
	else if (((srcAddr & 0x01) == 0) && ((dstAddr & 0x01) == 0) && ((total_size & 0x01) == 0)) {
		trnsWidth = DdHdmac1_TW_HWORD;
	}
	else {
		trnsWidth = DdHdmac1_TW_BYTE;
	}

	return trnsWidth;
}

/**
 * @brief  Set HDMAC1 Interrupt Handler
 * @param  HDMAC1 channel, interrupt handler
 * @return VOID
 */
VOID dd_hdmac1_set_int_handler(DdHdmac1 *self, UCHAR ch, VOID (*intHandler)(VOID))
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return;
	}
#endif

	priv->gDD_HDMAC1_Ctrl[ch].intHandler = intHandler;
}

/**
 * @brief  Interrupt handler of HDMAC1 channel 0 for transfer process is finished.
 * @param  VOID
 * @return VOID
 */
VOID dd_hdmac1_int_handler(DdHdmac1 *self, UCHAR ch)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);
	DDIM_USER_ER ercd;
	USHORT status;
	VP_CALLBACK handler;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return;
	}
#endif

	status = IO_HDMAC1.DMAC[ch].DMACB.bit.SS;		// To give the user the content of the SS of DMACB register
	priv->gDD_HDMAC1_Stop_Status[ch] = status;
	IO_HDMAC1.DMAC[ch].DMACB.bit.SS = 0x0;			// Stop Status clear
	IO_HDMAC1.DMAC[ch].DMACA.bit.EB = 0;				// HDMAC1 Stop
	Dd_ARM_Dsb_Pou();

	if ((status != DdHdmac1_SS_NORMAL_END) || (priv->gDD_HDMAC1_TC_Second[ch] == 0)) {
		handler = priv->gDD_HDMAC1_Ctrl[ch].intHandler;
		
		if (handler != NULL) {
			(*handler)(ch, &status);
		}

		switch (ch) {
			case 0:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH0);
				break;

			case 1:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH1);
				break;

			case 2:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH2);
				break;

			case 3:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH3);
				break;

			case 4:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH4);
				break;

			case 5:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH5);
				break;

			case 6:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH6);
				break;

			case 7:
				ercd = DDIM_User_Set_Flg(FID_DD_HDMAC1, DdHdmac1_FLG_CH7);
				break;

			default:
				ercd = -1;
				break;
		}

		if (ercd != D_DDIM_USER_E_OK) {
			Ddim_Print(("I:DDIM_User_Set_Flg error. ercd = %d\n", ercd));
		}
	}
	else if (priv->gDD_HDMAC1_TC_Second[ch] != 0) {
		// restart
		priv->gDD_HDMAC1_Ctrl[ch].configA.bit.bc = 0;
		priv->gDD_HDMAC1_Ctrl[ch].configA.bit.bt = 0;
		priv->gDD_HDMAC1_Ctrl[ch].configA.bit.tc = priv->gDD_HDMAC1_TC_Second[ch] - 1;

		priv->gDD_HDMAC1_Ctrl[ch].srcAddr        = IO_HDMAC1.DMAC[ch].DMACSA;
		priv->gDD_HDMAC1_Ctrl[ch].dstAddr        = IO_HDMAC1.DMAC[ch].DMACDA;

		priv->gDD_HDMAC1_TC_Second[ch] = 0;
		dd_hdmac1_start(priv, ch, &status, DdHdmac1_WAITMODE_EVENT, DdHdmac1_ASYNC);	// HDMAC1 Start
	}
}

#ifdef CO_DDIM_UTILITY_USE

INT32 dd_hdmac1_copy_sdram_sync(DdHdmac1 *self, UCHAR ch, ULONG srcAddr, ULONG dstAddr, ULONG size, UINT32 wait_mode)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);

	return dd_hdmac1_utility_copy_sdram_sync(priv->utility, ch, srcAddr, dstAddr, size, wait_mode);
}

INT32 dd_hdmac1_copy_sdram_async(DdHdmac1 *self, UCHAR ch, ULONG srcAddr, ULONG dstAddr,
		ULONG size, VP_CALLBACK intHandler)
{
	DdHdmac1Private *priv = DD_HDMAC1_GET_PRIVATE(self);

	return dd_hdmac1_utility_copy_sdram_async(priv->utility, ch, srcAddr, dstAddr, size, intHandler);
}

#endif

DdHdmac1* dd_hdmac1_get(void)
{
	static DdHdmac1* self = NULL;

	if(!self)
		self = k_object_new_with_private(DD_TYPE_HDMAC1, sizeof(DdHdmac1Private));

	return self;
}
