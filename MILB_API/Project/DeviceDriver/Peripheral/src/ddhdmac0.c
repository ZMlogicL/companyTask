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

//#include "dd_top.h"
#include "peripheral.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#include "dd_arm.h"
#include "ddhdmac0.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdHdmac0, dd_hdmac0);
#define DD_HDMAC0_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdHdmac0Private, DD_TYPE_HDMAC0))

#define D_DD_HDMAC0_SYNC			0		/* Sync Processing */
#define D_DD_HDMAC0_ASYNC			1		/* Async Processing */


struct _DdHdmac0Private
{
	DdHdmac0Utility *utility;
	volatile Hdmac0Ctrl gDD_HDMAC0_Ctrl[DdHdmac0_CH_NUM_MAX];
	volatile USHORT gDD_HDMAC0_TC_Second[DdHdmac0_CH_NUM_MAX];
	volatile USHORT gDD_HDMAC0_Stop_Status[DdHdmac0_CH_NUM_MAX];
	volatile INT32 gDD_HDMAC0_Wait_End_Time[DdHdmac0_CH_NUM_MAX];
};


/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
static INT32 waitEnd(DdHdmac0Private *priv, UCHAR ch, USHORT* const status, UINT32 wait_mode);
static INT32 dd_hdmac0_start(DdHdmac0Private *priv, UCHAR ch, USHORT* const status, UINT32 wait_mode, UINT32 sync);


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
static INT32 waitEnd(DdHdmac0Private *priv, UCHAR ch, USHORT* const status, UINT32 wait_mode)
{
	DDIM_USER_FLGPTN flg_ptn;
	DDIM_USER_ER ercd = 0;
	USHORT ss;

	// CPU Polling (no use interrupt)
	if (wait_mode == DdHdmac0_WAITMODE_CPU) {
		while (priv->gDD_HDMAC0_Stop_Status[ch] == 0) {
			ss = IO_HDMAC0.DMAC[ch].DMACB.bit.SS;
			if(ss) {
				priv->gDD_HDMAC0_Stop_Status[ch] = ss;
			}
		}
		
		if (priv->gDD_HDMAC0_Stop_Status[ch] == 0) {
			*status = IO_HDMAC0.DMAC[ch].DMACB.bit.SS;	// To give the user the content of the SS bit of DMACB register
			IO_HDMAC0.DMAC[ch].DMACB.bit.SS = 0x0;		// Stop Status clear
			IO_HDMAC0.DMAC[ch].DMACA.bit.EB = 0;		// HDMAC0 Stop
		}
		else {
			*status = priv->gDD_HDMAC0_Stop_Status[ch];
			priv->gDD_HDMAC0_Stop_Status[ch] = 0;
		}
	}
	// EVENT (use interrupt)
	else {
		switch (ch) {
			case 0:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH0, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC0_Wait_End_Time[ch]);
				break;

			case 1:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH1, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC0_Wait_End_Time[ch]);
				break;

			case 2:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH2, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC0_Wait_End_Time[ch]);
				break;

			case 3:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH3, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC0_Wait_End_Time[ch]);
				break;

			case 4:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH4, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC0_Wait_End_Time[ch]);
				break;

			case 5:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH5, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC0_Wait_End_Time[ch]);
				break;

			case 6:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH6, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC0_Wait_End_Time[ch]);
				break;

			case 7:
				ercd = DDIM_User_Twai_Flg(FID_DD_HDMAC0, DdHdmac0_FLG_CH7, D_DDIM_USER_TWF_ORW, &flg_ptn, priv->gDD_HDMAC0_Wait_End_Time[ch]);
				break;

			default:
				break;
		}

		*status = priv->gDD_HDMAC0_Stop_Status[ch];		// To give the user the content of the SS bit of DMACB register
		priv->gDD_HDMAC0_Stop_Status[ch] = 0;
	}

	if (ercd == D_DDIM_USER_E_TMOUT) {
		Ddim_Print(("HDMAC0 error. timeout!"));
		return DdHdmac0_TIMEOUT_ERR;
	}

	if (ercd != D_DDIM_USER_E_OK) {
		Ddim_Print(("HDMAC0 error. system error!"));
		return DdHdmac0_SYSTEM_ERR;
	}

	return D_DDIM_OK;
}

/**
 * @brief  HDMAC0 start.
 */
static INT32 dd_hdmac0_start(DdHdmac0Private *priv, UCHAR ch, USHORT* const status, UINT32 wait_mode, UINT32 sync)
{
	INT32 ret = D_DDIM_OK;

	// HDMAC0 Enable
	if (IO_HDMAC0.DMACR.bit.DE == 0) {
		IO_HDMAC0.DMACR.bit.DE = 1;							// HDMAC0 all ch enable
	}

	// HDMAC0 Busy Check
	if (IO_HDMAC0.DMAC[ch].DMACA.bit.EB) {
		return DdHdmac0_BUSY_ERR;
	}

	if (wait_mode == DdHdmac0_WAITMODE_EVENT) {
		priv->gDD_HDMAC0_Ctrl[ch].configB.bit.ei = 1;				// Error Interrupt Enable
		priv->gDD_HDMAC0_Ctrl[ch].configB.bit.ci = 1;				// Completion Interrupt Enable
	}

	priv->gDD_HDMAC0_Stop_Status[ch] = 0;
	IO_HDMAC0.DMAC[ch].DMACA.word = priv->gDD_HDMAC0_Ctrl[ch].configA.word;	// HDMAC0 Config A register set
	IO_HDMAC0.DMAC[ch].DMACB.word = priv->gDD_HDMAC0_Ctrl[ch].configB.word;	// HDMAC0 Config B register set
	IO_HDMAC0.DMAC[ch].DMACSA     = priv->gDD_HDMAC0_Ctrl[ch].srcAddr;		// HDMAC0 Source Address register set
	IO_HDMAC0.DMAC[ch].DMACDA     = priv->gDD_HDMAC0_Ctrl[ch].dstAddr;		// HDMAC0 Destination Address register set

	if (wait_mode == DdHdmac0_WAITMODE_EVENT) {
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

	IO_HDMAC0.DMAC[ch].DMACA.bit.EB = 1;			// HDMAC0 Start
	if (priv->gDD_HDMAC0_Ctrl[ch].configA.bit.is == DdHdmac0_IS_SOFT) {
		IO_HDMAC0.DMAC[ch].DMACA.bit.ST = 1;		// Soft trigger
	}
	Dd_ARM_Dsb_Pou();

	// Sync Processing
	if (sync == D_DD_HDMAC0_SYNC) {
		ret = waitEnd(priv, ch, status, wait_mode);
	}

	return ret;
}

/**
 * @brief  Execute exclusive control for designated HDMAC0 channel.
 * @param  UCHAR	ch	Channel number (0 to 7)
 * @return INT32 	D_DDIM_OK / DdHdmac0_EXC_LOCK_NG / DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_open(DdHdmac0 *self, UCHAR ch, INT32 tmout)
{
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	if (D_DDIM_USER_SEM_WAIT_POL == tmout) {
		ercd = DDIM_User_Pol_Sem(SID_DD_HDMAC0(ch));				// pol_sem()
	}
	else {
		ercd = DDIM_User_Twai_Sem(SID_DD_HDMAC0(ch), (DDIM_USER_TMO)tmout);	// twai_sem()
	}

	if (D_DDIM_USER_E_OK != ercd) {
		if (D_DDIM_USER_E_TMOUT == ercd) {
			return DdHdmac0_SEM_TIMEOUT;
		}

		return DdHdmac0_SEM_NG;
	}

	return D_DDIM_OK;
}

/**
 * @brief  Cancel exclusive control for designated HDMAC0 channel.
           When the designated channel is under transferring, stop transfer immediately and cancel lock.
 * @param  UCHAR	ch			Channel number (0 to 7)
 * @return INT32  D_DDIM_OK/DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_close(DdHdmac0 *self, UCHAR ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// Global variable is clear
	priv->gDD_HDMAC0_Ctrl[ch].configA.word = 0;
	priv->gDD_HDMAC0_Ctrl[ch].configB.word = 0;
	priv->gDD_HDMAC0_Ctrl[ch].srcAddr      = 0;
	priv->gDD_HDMAC0_Ctrl[ch].dstAddr      = 0;
	priv->gDD_HDMAC0_Ctrl[ch].intHandler   = NULL;

	ercd = DDIM_User_Sig_Sem(SID_DD_HDMAC0(ch));				// sig_sem()
	if(D_DDIM_USER_E_OK != ercd) {
		return DdHdmac0_SEM_NG;
	}

	return D_DDIM_OK;
}

/**
 * @brief  Set control data to registers related HDMAC0 designated channel.
 * @param  UCHAR	ch	Channel number (0 to 7)
 * @return INT32	D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_ctrl_common(DdHdmac0 *self, UCHAR ch, Hdmac0Ctrl const *const hdmac0_ctrl)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (hdmac0_ctrl == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*hdmac0_ctrl] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// HDMAC0 Busy Check
//	if (IO_HDMAC0.DMAC[ch].CSTR.bit.BUSY) {
//		return DdHdmac0_BUSY_ERR;
//	}

	// The value is set to an external variable
	priv->gDD_HDMAC0_Ctrl[ch].configA.word = (hdmac0_ctrl->configA.word & 0x1FFFFFFF);
	priv->gDD_HDMAC0_Ctrl[ch].configB.word = (hdmac0_ctrl->configB.word & 0xFFFFFF00);
	priv->gDD_HDMAC0_Ctrl[ch].srcAddr      = hdmac0_ctrl->srcAddr;
	priv->gDD_HDMAC0_Ctrl[ch].dstAddr      = hdmac0_ctrl->dstAddr;
	priv->gDD_HDMAC0_Ctrl[ch].intHandler   = hdmac0_ctrl->intHandler;

	priv->gDD_HDMAC0_TC_Second[ch] = 0;
	priv->gDD_HDMAC0_Wait_End_Time[ch] = D_DDIM_WAIT_END_TIME;

	return D_DDIM_OK;
}

/**
 * @brief  Set control data to registers related HDMAC0 designated channel.
 * @param  UCHAR	ch	Channel number (0 to 7)
 * @return INT32	D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_ctrl_trns(DdHdmac0 *self, UCHAR ch, Hdmac0CtrlTrns const *const hdmac0_ctrl_trans)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	UCHAR  tmp_width;
	ULONG  tmp_tc = 0;
	USHORT tmp_bc = 0;
	UCHAR  tmp_bt = 0;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (hdmac0_ctrl_trans == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*hdmac0_ctrl_trans] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// HDMAC0 Busy Check
//	if (IO_HDMAC0.DMAC[ch].CSTR.bit.BUSY) {
//		return DdHdmac0_BUSY_ERR;
//	}

	// Calucurate TC and BC
	tmp_width = 0x01 << hdmac0_ctrl_trans->size.trnsWidth;
	if ((hdmac0_ctrl_trans->size.trnsSize % tmp_width) != 0) {
		Ddim_Print(("HDMAC0: input param error. illegal alignment.\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}

	switch (hdmac0_ctrl_trans->mode.beatType) {
		case DdHdmac0_BT_WRAP4:
		case DdHdmac0_BT_INCR4:
			tmp_bt = 4;
			break;
		case DdHdmac0_BT_WRAP8:
		case DdHdmac0_BT_INCR8:
			tmp_bt = 8;
			break;
		case DdHdmac0_BT_WRAP16:
		case DdHdmac0_BT_INCR16:
		case DdHdmac0_BT_INCR:
			tmp_bt = 16;
			break;
		default:
			tmp_bt = 16;
			break;
	}
	if ((hdmac0_ctrl_trans->mode.modeSel != DdHdmac0_MS_DEMAND) &&
		(hdmac0_ctrl_trans->size.trnsSize > (tmp_width * tmp_bt))) {

		tmp_bc = tmp_bt - 1;
		tmp_tc = (hdmac0_ctrl_trans->size.trnsSize / (tmp_width * tmp_bt)) - 1;

		if ((hdmac0_ctrl_trans->size.trnsSize % (tmp_width * tmp_bt)) != 0) {
			priv->gDD_HDMAC0_TC_Second[ch] = ((hdmac0_ctrl_trans->size.trnsSize % (tmp_width * tmp_bt)) / tmp_width);
		}
		else {
			priv->gDD_HDMAC0_TC_Second[ch] = 0;
		}
	}
	else {
		tmp_bc = 0;
		tmp_tc = (hdmac0_ctrl_trans->size.trnsSize / tmp_width) - 1;
		priv->gDD_HDMAC0_TC_Second[ch] = 0;
	}

	// Check TransferSize
	if ((tmp_tc >= 65536) || ((tmp_tc == 65535) && (priv->gDD_HDMAC0_TC_Second[ch] != 0))) {
		// Max size over
		Ddim_Print(("HDMAC0: input param error. Max size over (Max size=%d).\n", tmp_width * tmp_bt * 65536));
		return DdHdmac0_INPUT_PARAM_ERR;
	}

	// The value is set to an external variable
	priv->gDD_HDMAC0_Ctrl[ch].configA.bit.is = hdmac0_ctrl_trans->mode.inputSel;
	priv->gDD_HDMAC0_Ctrl[ch].configA.bit.bt = hdmac0_ctrl_trans->mode.beatType;

	priv->gDD_HDMAC0_Ctrl[ch].configB.bit.ms = hdmac0_ctrl_trans->mode.modeSel;
	priv->gDD_HDMAC0_Ctrl[ch].configB.bit.fs = hdmac0_ctrl_trans->mode.srcFix;
	priv->gDD_HDMAC0_Ctrl[ch].configB.bit.fd = hdmac0_ctrl_trans->mode.dstFix;

	priv->gDD_HDMAC0_Ctrl[ch].configB.bit.tw = hdmac0_ctrl_trans->size.trnsWidth;

	priv->gDD_HDMAC0_Ctrl[ch].configA.bit.bc = tmp_bc;
	priv->gDD_HDMAC0_Ctrl[ch].configA.bit.tc = (USHORT)tmp_tc;

	priv->gDD_HDMAC0_Ctrl[ch].configB.bit.dp = 0x08;		// HPROT[3] Cachable (Source Protection)
	priv->gDD_HDMAC0_Ctrl[ch].configB.bit.sp = 0x08;		// HPROT[3] Cachable (Destination Protection)

	priv->gDD_HDMAC0_Ctrl[ch].srcAddr        = hdmac0_ctrl_trans->size.srcAddr;
	priv->gDD_HDMAC0_Ctrl[ch].dstAddr        = hdmac0_ctrl_trans->size.dstAddr;
	priv->gDD_HDMAC0_Ctrl[ch].intHandler     = hdmac0_ctrl_trans->intHandler;

	priv->gDD_HDMAC0_Wait_End_Time[ch] = D_DDIM_WAIT_END_TIME;

	return D_DDIM_OK;
}

INT32 dd_hdmac0_set_trns_size(DdHdmac0 *self, UCHAR ch, Hdmac0TrnsSize const *const hdmac0_trns_size)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	UCHAR  tmp_width;
	ULONG  tmp_tc = 0;
	USHORT tmp_bc = 0;
	UCHAR  tmp_bt = 0;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (hdmac0_trns_size == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*hdmac0_trns_size] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// HDMAC0 Busy Check
//	if (IO_HDMAC0.DMAC[ch].CSTR.bit.BUSY) {
//		return DdHdmac0_BUSY_ERR;
//	}

	// Calucurate TC and BC
	tmp_width = 0x01 << hdmac0_trns_size->trnsWidth;
	if ((hdmac0_trns_size->trnsSize % tmp_width) != 0) {
		Ddim_Print(("HDMAC0: input param error. illegal alignment.\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}

	switch (priv->gDD_HDMAC0_Ctrl[ch].configA.bit.bt) {
		case DdHdmac0_BT_WRAP4:
		case DdHdmac0_BT_INCR4:
			tmp_bt = 4;
			break;
		case DdHdmac0_BT_WRAP8:
		case DdHdmac0_BT_INCR8:
			tmp_bt = 8;
			break;
		case DdHdmac0_BT_WRAP16:
		case DdHdmac0_BT_INCR16:
		case DdHdmac0_BT_INCR:
			tmp_bt = 16;
			break;
		default:
			tmp_bt = 16;
			break;
	}
	if ((priv->gDD_HDMAC0_Ctrl[ch].configB.bit.ms != DdHdmac0_MS_DEMAND) &&
		(hdmac0_trns_size->trnsSize > (tmp_width * tmp_bt))) {
		tmp_bc = tmp_bt - 1;
		tmp_tc = (hdmac0_trns_size->trnsSize / (tmp_width * tmp_bt)) - 1;

		if ((hdmac0_trns_size->trnsSize % (tmp_width * tmp_bt)) != 0) {
			priv->gDD_HDMAC0_TC_Second[ch] = ((hdmac0_trns_size->trnsSize % (tmp_width * tmp_bt)) / tmp_width);
		}
		else {
			priv->gDD_HDMAC0_TC_Second[ch] = 0;
		}
	}
	else {
		tmp_bc = 0;
		tmp_tc = (hdmac0_trns_size->trnsSize / tmp_width) - 1;
		priv->gDD_HDMAC0_TC_Second[ch] = 0;
	}

	// Check TransferSize
	if ((tmp_tc >= 65536) || ((tmp_tc == 65535) && (priv->gDD_HDMAC0_TC_Second[ch] != 0))) {
		// Max size over
		Ddim_Print(("HDMAC0: input param error. Max size over (Max size=%d).\n", tmp_width * tmp_bt * 65536));
		return DdHdmac0_INPUT_PARAM_ERR;
	}

	// The value is set to an external variable
	priv->gDD_HDMAC0_Ctrl[ch].configB.bit.tw = hdmac0_trns_size->trnsWidth;

	priv->gDD_HDMAC0_Ctrl[ch].configA.bit.bc = tmp_bc;
	priv->gDD_HDMAC0_Ctrl[ch].configA.bit.tc = (USHORT)tmp_tc;

	priv->gDD_HDMAC0_Ctrl[ch].srcAddr        = hdmac0_trns_size->srcAddr;
	priv->gDD_HDMAC0_Ctrl[ch].dstAddr        = hdmac0_trns_size->dstAddr;

	return D_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC0 of specified ch begins.
 * @param  UCHAR				ch				Channel number (0 to 7)
 *         T_DD_HDMAC0_START*	hdmac0_start	HDMAC0 Start table
 *         USHORT*			status		Channel Status Register pointer
 *         UINT32			wait_mode	HDMAC0 end wait mode
 * @return INT32			D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR / D_DDIM_TIMEOUT / DdHdmac0_SYSTEM_ERR
 */
INT32 dd_hdmac0_start_sync(DdHdmac0 *self, UCHAR ch, USHORT *const status, UINT32 wait_mode)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	INT32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (status == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*status] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if ((wait_mode != DdHdmac0_WAITMODE_CPU) && (wait_mode != DdHdmac0_WAITMODE_EVENT)) {
		Ddim_Assertion(("HDMAC0: input param error. [wait_mode] = %x\n", wait_mode));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	ret = dd_hdmac0_start(priv, ch, status, wait_mode, D_DD_HDMAC0_SYNC);		// HDMAC0 Start

	if ((*status == DdHdmac0_SS_NORMAL_END) && (priv->gDD_HDMAC0_TC_Second[ch] != 0)) {
		// restart
		priv->gDD_HDMAC0_Ctrl[ch].configA.bit.bc = 0;
		priv->gDD_HDMAC0_Ctrl[ch].configA.bit.tc = priv->gDD_HDMAC0_TC_Second[ch] - 1;

		priv->gDD_HDMAC0_Ctrl[ch].srcAddr        = IO_HDMAC0.DMAC[ch].DMACSA;
		priv->gDD_HDMAC0_Ctrl[ch].dstAddr        = IO_HDMAC0.DMAC[ch].DMACDA;

		priv->gDD_HDMAC0_TC_Second[ch] = 0;
		dd_hdmac0_start(priv, ch, status, wait_mode, D_DD_HDMAC0_SYNC);	// HDMAC0 Start
	}

	return ret;
}

/**
 * @brief  The operation of HDMAC0 of specified ch begins.
 * @param  UCHAR				ch				Channel number (0 to 7)
 *         T_DD_HDMAC0_START*	hdmac0_start	HDMAC0 Start table
 * @return INT32			D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_start_async(DdHdmac0 *self, UCHAR ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	USHORT	status;	// dummy

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	dd_hdmac0_start(priv, ch, &status, DdHdmac0_WAITMODE_EVENT, D_DD_HDMAC0_ASYNC);	// HDMAC0 Start
	return D_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC0 of specified ch is stopped.
 * @param  UCHAR	ch			Channel number (0 to 7)
 * @return INT32	D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_stop(DdHdmac0 *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	IO_HDMAC0.DMAC[ch].DMACA.word &= 0x7FFFFFFF;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC0 of specified ch is stopped.
 * @param  UCHAR	ch			Channel number (0 to 7)
 * @return INT32	D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_pause(DdHdmac0 *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	IO_HDMAC0.DMAC[ch].DMACA.bit.PB = 1;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC0 of specified ch is resumed.
 * @param  UCHAR	ch			Channel number (0 to 7)
 * @return INT32	D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_resume(DdHdmac0 *self, UCHAR ch)
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

	IO_HDMAC0.DMAC[ch].DMACA.bit.PB = 0;
	IO_HDMAC0.DMAC[ch].DMACA.bit.EB = 1;			// HDMAC0 Start
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  Wait end time of transfer process of designated channel.
 * @param  UCHAR	ch			Channel number (0 to 7)
 *         INT32	wait_time	Wait end time of transfer process
 * @return INT32				D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_set_wait_time(DdHdmac0 *self, UCHAR ch, INT32 wait_time)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (wait_time < D_DDIM_WAIT_END_FOREVER) {
		Ddim_Assertion(("HDMAC0: input param error. [wait_time] = %d\n", wait_time));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	priv->gDD_HDMAC0_Wait_End_Time[ch] = wait_time;
	return D_DDIM_OK;
}

/**
 * @brief  Wait end of transfer process of designated channel.
 *         The value of the CSTR register is passed by the out parameter.
 * @param  UCHAR	ch			Channel number (0 to 7)
 *         USHORT*	status		Channel Status Register pointer
 * @return INT32	D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR / D_DDIM_TIMEOUT / DdHdmac0_SYSTEM_ERR
 */
INT32 dd_hdmac0_wait_end(DdHdmac0 *self, UCHAR ch, USHORT* const status, UINT32 wait_mode)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	INT32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (status == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*status] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if ((wait_mode != DdHdmac0_WAITMODE_CPU) && (wait_mode != DdHdmac0_WAITMODE_EVENT)) {
		Ddim_Assertion(("HDMAC0: input param error. [wait_mode] = %x\n", wait_mode));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	ret = waitEnd(priv, ch, status, wait_mode);

	if ((*status == DdHdmac0_SS_NORMAL_END) && (priv->gDD_HDMAC0_TC_Second[ch] != 0)) {
		// restart
		priv->gDD_HDMAC0_Ctrl[ch].configA.bit.bc = 0;
		priv->gDD_HDMAC0_Ctrl[ch].configA.bit.tc = priv->gDD_HDMAC0_TC_Second[ch] - 1;

		priv->gDD_HDMAC0_Ctrl[ch].srcAddr        = IO_HDMAC0.DMAC[ch].DMACSA;
		priv->gDD_HDMAC0_Ctrl[ch].dstAddr        = IO_HDMAC0.DMAC[ch].DMACDA;

		priv->gDD_HDMAC0_TC_Second[ch] = 0;
		dd_hdmac0_start(priv, ch, status, DdHdmac0_WAITMODE_EVENT, D_DD_HDMAC0_ASYNC);	// HDMAC0 Start
		ret = waitEnd(priv, ch, status, wait_mode);
	}

	return ret;
}

/**
 * @brief  The status of HDMAC0 of specified ch is cleared.
 * @param  UCHAR	ch			Channel number (0 to 7)
 * @return INT32				D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_clear_status(DdHdmac0 *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	IO_HDMAC0.DMAC[ch].DMACB.bit.SS = 0;

	return D_DDIM_OK;
}

/**
 * @brief  The error status of HDMAC0 of specified ch is cleared.
 * @param  UCHAR	ch			Channel number (0 to 7)
 * @return INT32				D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_get_status(DdHdmac0 *self, UCHAR ch, USHORT *const status)
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

	*status = IO_HDMAC0.DMAC[ch].DMACB.bit.SS;
	return D_DDIM_OK;
}

/**
The value of the transferd size of the specified channel is acquired.
@param [in] ch				Channel number (0 to 7)
@retval size						transferd size of the specified channel
@remarks This API forced cancel exclusive control if process is under executing.
*/
ULONG dd_hdmac0_get_trns_size(DdHdmac0 *self, UCHAR ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	ULONG  total_size;
	ULONG  remain_size;
	USHORT tc;
	UCHAR  bc;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	tc = IO_HDMAC0.DMAC[ch].DMACA.bit.TC;
	bc = IO_HDMAC0.DMAC[ch].DMACA.bit.BC;
	remain_size = (bc + 1) * (tc + 1) * (1 << priv->gDD_HDMAC0_Ctrl[ch].configB.bit.tw);

	if ((tc == 0) && (bc == 0)) {
		if (((IO_HDMAC0.DMAC[ch].DMACB.word & 0x00070000) != 0x00000000) || (priv->gDD_HDMAC0_Stop_Status[ch] != 0)) {
			remain_size = 0;
		}
	}

	if (priv->gDD_HDMAC0_TC_Second[ch] != 0) {
		remain_size += (priv->gDD_HDMAC0_TC_Second[ch]) * (1 << priv->gDD_HDMAC0_Ctrl[ch].configB.bit.tw);
	}

	total_size = (priv->gDD_HDMAC0_Ctrl[ch].configA.bit.bc + 1) * (priv->gDD_HDMAC0_Ctrl[ch].configA.bit.tc + 1) * (1 << priv->gDD_HDMAC0_Ctrl[ch].configB.bit.tw);
	if (priv->gDD_HDMAC0_TC_Second[ch] != 0) {
		total_size += (priv->gDD_HDMAC0_TC_Second[ch]) * (1 << priv->gDD_HDMAC0_Ctrl[ch].configB.bit.tw);
	}

	return (total_size - remain_size);
}

/**
The value of the remainder transfer size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval size						remainder transfer size of the specified channel
@remarks This API forced cancel exclusive control if process is under executing.
*/
ULONG dd_hdmac0_get_remain_trns_size(DdHdmac0 *self, UCHAR ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	ULONG  remain_size;
	USHORT tc;
	UCHAR  bc;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	tc = IO_HDMAC0.DMAC[ch].DMACA.bit.TC;
	bc = IO_HDMAC0.DMAC[ch].DMACA.bit.BC;
	remain_size = (bc + 1) * (tc + 1) * (1 << priv->gDD_HDMAC0_Ctrl[ch].configB.bit.tw);

	if ((tc == 0) && (bc == 0)) {
		if (((IO_HDMAC0.DMAC[ch].DMACB.word & 0x00070000) != 0x00000000) || (priv->gDD_HDMAC0_Stop_Status[ch] != 0)) {
			remain_size = 0;
		}
	}

	if (priv->gDD_HDMAC0_TC_Second[ch] != 0) {
		remain_size += (priv->gDD_HDMAC0_TC_Second[ch]) * (1 << priv->gDD_HDMAC0_Ctrl[ch].configB.bit.tw);
	}

	return remain_size;
}

/**
The value of the total transfer size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval size						total transfer size of the specified channel
*/
ULONG dd_hdmac0_get_total_trns_size(DdHdmac0 *self, UCHAR ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	ULONG total_size;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	total_size = (priv->gDD_HDMAC0_Ctrl[ch].configA.bit.bc + 1) * (priv->gDD_HDMAC0_Ctrl[ch].configA.bit.tc + 1) * (1 << priv->gDD_HDMAC0_Ctrl[ch].configB.bit.tw);
	if (priv->gDD_HDMAC0_TC_Second[ch] != 0) {
		total_size += (priv->gDD_HDMAC0_TC_Second[ch]) * (1 << priv->gDD_HDMAC0_Ctrl[ch].configB.bit.tw);
	}

	return total_size;
}

/**
The value of the source address (DMACSA) of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval srcAddr					source address of the specified channel
*/
ULONG dd_hdmac0_get_src_addr(DdHdmac0 *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	return IO_HDMAC0.DMAC[ch].DMACSA;
}

/**
The value of the destination address (DMACDA) of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval dstAddr					Destination address of the specified channel
*/
ULONG dd_hdmac0_get_dst_addr(DdHdmac0 *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	return IO_HDMAC0.DMAC[ch].DMACDA;
}

/**
Source Protection code is set.

@param [in] ch					Channel number (0 to 7)
@param [in] protect_code		Protection Code
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
*/
INT32 dd_hdmac0_set_source_protect(DdHdmac0 *self, UCHAR ch, UCHAR protect_code)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	IO_HDMAC0.DMAC[ch].DMACB.bit.SP = protect_code;
	return D_DDIM_OK;
}

/**
Destination Protection code is set.

@param [in] ch					Channel number (0 to 7)
@param [in] protect_code		Protection Code
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
*/
INT32 dd_hdmac0_set_destination_protect(DdHdmac0 *self, UCHAR ch, UCHAR protect_code)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	IO_HDMAC0.DMAC[ch].DMACB.bit.DP = protect_code;
	return D_DDIM_OK;
}

/**
 * @brief  Arbitration level and HDMAC0 forwarding control interrupt level of all channels are set.
 * @param  T_DD_HDMAC0_ARBITRATION*	arbitration
 * @return INT32				D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_set_arbitration(DdHdmac0 *self, UCHAR arbitration)
{
#ifdef CO_PARAM_CHECK
	if ((arbitration != DdHdmac0_ARB_FIX) && (arbitration != DdHdmac0_ARB_ROTATE)) {
		Ddim_Assertion(("HDMAC0: input param error. [arbitration] = %x\n", arbitration));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// Arbitration type is set
	IO_HDMAC0.DMACR.bit.PR = arbitration;

	return D_DDIM_OK;
}

/**
 * @brief  Arbitration level and HDMAC0 forwarding control interrupt level of all channels are read.
 * @param  T_DD_HDMAC0_ARBITRATION*	arbitration
 * @return INT32				D_DDIM_OK / DdHdmac0_INPUT_PARAM_ERR
 */
INT32 dd_hdmac0_get_arbitration(DdHdmac0 *self, UCHAR *const arbitration)
{
#ifdef CO_PARAM_CHECK
	if (arbitration == NULL) {
		Ddim_Assertion(("HDMAC0: input param error. [*arbitration] NULL\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// Arbitration type is set
	*arbitration = IO_HDMAC0.DMACR.bit.PR;

	return D_DDIM_OK;
}

/**
 * @brief  Arbitration level and HDMAC0 forwarding control interrupt level of all channels are returned to an initial value.
 * @param  VOID
 * @return VOID
 */
VOID dd_hdmac0_clear_arbitration(DdHdmac0 *self)
{
	// Arbitration type is set
	IO_HDMAC0.DMACR.bit.PR = 0;
}

/**
The operation of All HDMAC0 channel is stopped.
*/
VOID dd_hdmac0_stop_all_ch(DdHdmac0 *self)
{
	// HDMAC0 Halt
	IO_HDMAC0.DMACR.bit.DH = 1;
}

/**
The operation of All HDMAC0 channel is resumed.
*/
VOID dd_hdmac0_resume_all_ch(DdHdmac0 *self)
{
	// HDMAC0 resume
	IO_HDMAC0.DMACR.bit.DH = 0;
}

/**
It is API that returns the value set to the register of TW. 

@param [in] srcAddr			soruce address
@param [in] dstAddr			destination address
@param [in] total_size			total size
@retval TW value set to register of TW
*/
UCHAR dd_hdmac0_get_trns_width(DdHdmac0 *self, ULONG srcAddr, ULONG dstAddr, ULONG total_size)
{
	UCHAR trnsWidth;

	// Check transfer size
	if (((srcAddr & 0x03) == 0) && ((dstAddr & 0x03) == 0) && ((total_size & 0x03) == 0)) {
		trnsWidth = DdHdmac0_TW_WORD;
	}
	else if (((srcAddr & 0x01) == 0) && ((dstAddr & 0x01) == 0) && ((total_size & 0x01) == 0)) {
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
 * @return VOID
 */
VOID dd_hdmac0_set_int_handler(DdHdmac0 *self, UCHAR ch, VOID (*intHandler)(VOID))
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return;
	}
#endif

	priv->gDD_HDMAC0_Ctrl[ch].intHandler = intHandler;
}

/**
 * @brief  Interrupt handler of HDMAC0 channel 0 for transfer process is finished.
 * @param  VOID
 * @return VOID
 */
VOID dd_hdmac0_int_handler(DdHdmac0 *self, UCHAR ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	DDIM_USER_ER ercd;
	USHORT status;
	VP_CALLBACK handler;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return;
	}
#endif

	status = IO_HDMAC0.DMAC[ch].DMACB.bit.SS;		// To give the user the content of the SS of DMACB register
	priv->gDD_HDMAC0_Stop_Status[ch] = status;
	IO_HDMAC0.DMAC[ch].DMACB.bit.SS = 0x0;			// Stop Status clear
	IO_HDMAC0.DMAC[ch].DMACA.bit.EB = 0;				// HDMAC0 Stop
	Dd_ARM_Dsb_Pou();

	if ((status != DdHdmac0_SS_NORMAL_END) || (priv->gDD_HDMAC0_TC_Second[ch] == 0)) {
		handler = priv->gDD_HDMAC0_Ctrl[ch].intHandler;
		
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

		if (ercd != D_DDIM_USER_E_OK) {
			Ddim_Print(("I:DDIM_User_Set_Flg error. ercd = %d\n", ercd));
		}
	}
	else if (priv->gDD_HDMAC0_TC_Second[ch] != 0) {
		// restart
		priv->gDD_HDMAC0_Ctrl[ch].configA.bit.bc = 0;
		priv->gDD_HDMAC0_Ctrl[ch].configA.bit.bt = 0;
		priv->gDD_HDMAC0_Ctrl[ch].configA.bit.tc = priv->gDD_HDMAC0_TC_Second[ch] - 1;

		priv->gDD_HDMAC0_Ctrl[ch].srcAddr        = IO_HDMAC0.DMAC[ch].DMACSA;
		priv->gDD_HDMAC0_Ctrl[ch].dstAddr        = IO_HDMAC0.DMAC[ch].DMACDA;

		priv->gDD_HDMAC0_TC_Second[ch] = 0;
		dd_hdmac0_start(priv, ch, &status, DdHdmac0_WAITMODE_EVENT, D_DD_HDMAC0_ASYNC);	// HDMAC0 Start
	}
}

/**
 * @brief  Interrupt handler of HDMAC0 channel 0 for transfer process is finished.
 * @param  VOID
 * @return VOID
 */
VOID dd_hdmac0_int_handler_2(DdHdmac0 *self, UCHAR ch)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);
	DDIM_USER_ER ercd;
	USHORT status;
	VP_CALLBACK handler;
#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return;
	}
#endif

	
//	printf("[%d]Dd_HDMAC0_Int_Handler %d \n", ch, 1);
//	Dd_Top_Set_Gpio_Status(E_DD_TOP_GPIO_PF2, 1);


	status = IO_HDMAC0.DMAC[ch].DMACB.bit.SS;		// To give the user the content of the SS of DMACB register
	priv->gDD_HDMAC0_Stop_Status[ch] = status;
	IO_HDMAC0.DMAC[ch].DMACB.bit.SS = 0x0;			// Stop Status clear
	IO_HDMAC0.DMAC[ch].DMACA.bit.EB = 0;				// HDMAC0 Stop
	Dd_ARM_Dsb_Pou();

	if ((status != DdHdmac0_SS_NORMAL_END) || (priv->gDD_HDMAC0_TC_Second[ch] == 0)) {
		handler = priv->gDD_HDMAC0_Ctrl[ch].intHandler;
		
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
		if (ercd != D_DDIM_USER_E_OK) {
			Ddim_Print(("I:2_ DDIM_User_Set_Flg error. ercd = %d\n", ercd));
		}
	}
	else if (priv->gDD_HDMAC0_TC_Second[ch] != 0) {
		// restart
		priv->gDD_HDMAC0_Ctrl[ch].configA.bit.bc = 0;
		priv->gDD_HDMAC0_Ctrl[ch].configA.bit.bt = 0;
		priv->gDD_HDMAC0_Ctrl[ch].configA.bit.tc = priv->gDD_HDMAC0_TC_Second[ch] - 1;

		priv->gDD_HDMAC0_Ctrl[ch].srcAddr        = IO_HDMAC0.DMAC[ch].DMACSA;
		priv->gDD_HDMAC0_Ctrl[ch].dstAddr        = IO_HDMAC0.DMAC[ch].DMACDA;

		priv->gDD_HDMAC0_TC_Second[ch] = 0;
		dd_hdmac0_start(priv, ch, &status, DdHdmac0_WAITMODE_EVENT, D_DD_HDMAC0_ASYNC);	// HDMAC0 Start
	}
}

#ifdef CO_DDIM_UTILITY_USE

INT32 dd_hdmac0_copy_sdram_sync(DdHdmac0 *self, UCHAR ch, ULONG srcAddr, ULONG dstAddr, ULONG size, UINT32 wait_mode)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

	return dd_hdmac0_utility_copy_sdram_sync(priv->utility, ch, srcAddr, dstAddr, size, wait_mode);
}

INT32 dd_hdmac0_copy_sdram_async(DdHdmac0 *self, UCHAR ch, ULONG srcAddr, ULONG dstAddr, ULONG size, VP_CALLBACK intHandler)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

	return dd_hdmac0_utility_copy_sdram_async(priv->utility, ch, srcAddr, dstAddr, size, intHandler);
}

INT32 dd_hdmac0_input_audio_async(DdHdmac0 *self, UCHAR ch, UCHAR inputSel, ULONG srcAddr, ULONG dstAddr, ULONG size, VP_CALLBACK intHandler)
{
	DdHdmac0Private *priv = DD_HDMAC0_GET_PRIVATE(self);

	return  dd_hdmac0_utility_input_audio_async(priv->utility, ch, inputSel, srcAddr, dstAddr, size, intHandler);
}

INT32 dd_hdmac0_output_audio_async(DdHdmac0 *self, UCHAR ch, UCHAR inputSel, ULONG srcAddr, ULONG dstAddr, ULONG size, VP_CALLBACK intHandler)
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

