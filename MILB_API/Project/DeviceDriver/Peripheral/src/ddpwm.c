/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :PWM driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

#include "dd_top.h"
#include "dd_arm.h"
#include "dd_hdmac0.h"
#include "ddim_user_custom.h"

#include "ddpwm.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdPwm, dd_pwm);
#define DD_PWM_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdPwmPrivate, DD_TYPE_PWM))

struct _DdPwmPrivate
{
    DdPwmBranch *ddPwmBranch;
};

static void dd_pwm_constructor(DdPwm *self)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
    priv->ddPwmBranch = dd_pwm_branch_new();
}

static void dd_pwm_destructor(DdPwm *self)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	if(priv->ddPwmBranch){
		k_object_unref(priv->ddPwmBranch);
		priv->ddPwmBranch = NULL;
	}
}

/*
 * PUBLIC
 */
/*
 * @brief  The PWM control register (all channels) is initialized.
 * @param  void
 * @return void
 */
void dd_pwm_init(DdPwm* self)
{
	kint32 blckn;

//	Dd_Top_Set_CLKSEL_RCLK(0);

	for(blckn = 0; blckn < DdPwmBranch_BLOCK_NUM; blckn++) {
		//0x5000
		IO_PERI.PWM[blckn].GCN2.word = 0xF000;

		IO_PERI.PWM[blckn].PCNA.word = 0x0010;
		IO_PERI.PWM[blckn].PCNB.word = 0x0010;
		IO_PERI.PWM[blckn].PCNC.word = 0x0010;
		IO_PERI.PWM[blckn].PCND.word = 0x0010;
		IO_PERI.PWM[blckn].PCNE.word = 0x0010;

		IO_PERI.PWM[blckn].GCN2.bit.TMEEN = 0;
	}
}

/*
 * @brief  The PWM channel is exclusively controlled.
 * @param  kuint32 ch
 * @param  kint32  tmout
 * @return kint32  D_DDIM_OK/DdPwmBranch_SEM_TIMEOUT/
 * DdPwmBranch_SEM_NG/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_open(DdPwm* self, kuint32 ch, kint32 tmout)
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (tmout < D_DDIM_USER_SEM_WAIT_FEVR) {
		Ddim_Assertion(("PWM: input param error. tmout = %x\n", tmout));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	if(tmout == D_DDIM_USER_SEM_WAIT_POL) {
		ercd = DDIM_User_Pol_Sem(SID_DD_PWM(ch));
	}
	else{
		ercd = DDIM_User_Twai_Sem(SID_DD_PWM(ch), (DDIM_USER_TMO)tmout);
	}

	if(ercd != D_DDIM_USER_E_OK) {
		if(D_DDIM_USER_E_TMOUT == ercd) {
			return DdPwmBranch_SEM_TIMEOUT;
		}
		return DdPwmBranch_SEM_NG;
	}
	return D_DDIM_OK;
}

/*
 * @brief  The exclusive control of control Channel it is released.
 * @param  kuint32 ch
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_close(DdPwm* self, kuint32 ch)
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	ercd = DDIM_User_Sig_Sem(SID_DD_PWM(ch));

	if(D_DDIM_USER_E_OK != ercd) {
		return DdPwmBranch_SEM_NG;
	}
	return D_DDIM_OK;
}

/*
 * @brief  The PWM channel is exclusively controlled for Timer E.
 * @param  kuint32 ch
 * @param  kint32  tmout
 * @return kint32  D_DDIM_OK/DdPwmBranch_SEM_TIMEOUT/
 * DdPwmBranch_SEM_NG/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_open_timer_e(DdPwm* self, kuint32 ch, kint32 tmout)
{
	kuint32 chStep, releaseCh;
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if ((ch != 0) && (ch != 4) && (ch != 8) && (ch != 12)) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (tmout < D_DDIM_USER_SEM_WAIT_FEVR) {
		Ddim_Assertion(("PWM: input param error. tmout = %x\n", tmout));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	for(chStep = ch; chStep < ch + DdPwmBranch_CH_NUM_IN_BLOCK; chStep++){
		if(D_DDIM_USER_SEM_WAIT_POL == tmout) {
			ercd = DDIM_User_Pol_Sem(SID_DD_PWM(chStep));
		}
		else{
			ercd = DDIM_User_Twai_Sem(SID_DD_PWM(chStep), (DDIM_USER_TMO)tmout);
		}

		if(D_DDIM_USER_E_OK != ercd) {
			for (releaseCh = ch; releaseCh < chStep; releaseCh++){
				if(DDIM_User_Sig_Sem(SID_DD_PWM(releaseCh)) != D_DDIM_USER_E_OK){
					return DdPwmBranch_SEM_NG;
				}
			}
			if(D_DDIM_USER_E_TMOUT == ercd) {
				return DdPwmBranch_SEM_TIMEOUT;
			}
			return DdPwmBranch_SEM_NG;
		}
	}

	return D_DDIM_OK;
}

/*
 * @brief  The exclusive control of control Channel it is released for Timer E.
 * @param  kuint32 ch
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_close_timer_e(DdPwm* self, kuint32 ch)
{
	kuint32 chStep;
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if ((ch != 0) && (ch != 4) && (ch != 8) && (ch != 12)) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	for(chStep = ch; chStep < ch + DdPwmBranch_CH_NUM_IN_BLOCK; chStep++){
		ercd = DDIM_User_Sig_Sem(SID_DD_PWM(chStep));
		if(D_DDIM_USER_E_OK != ercd) {
			return DdPwmBranch_SEM_NG;
		}
	}
	return D_DDIM_OK;
}

/*
 * @brief  The PWM operational condition of a control channel is set.
 * @param  kuint32 ch, DdPwmCtrlCmn* pwmCtrlCmn
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_ctrl_common(DdPwm* self, kuint32 ch, DdPwmCtrlCmn const* const pwmCtrlCmn)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	const kuint32 chInBlk = (DdPwmBranch_CH_NUM_IN_BLOCK - 1) & ch;
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;
	volatile union io_pwm_pcn* pcnAddr;
	union io_pwm_pcn pcnTmp;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (0 == pwmCtrlCmn) {
		Ddim_Assertion(("PWM input param error. [pwmCtrlCmn] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	dd_pwm_branch_set_clk_sel(priv->ddPwmBranch, ch, pwmCtrlCmn->clkSel);
	dd_pwm_branch_set_int_enable(priv->ddPwmBranch, ch, pwmCtrlCmn->intEnable);
	dd_pwm_branch_set_p_callback(priv->ddPwmBranch, ch, pwmCtrlCmn->pCallback);

	if (pwmCtrlCmn->timEEnable) {
		pcnAddr = (union io_pwm_pcn*)&IO_PERI.PWM[blk].PCNE;
	}
	else {
		pcnAddr = dd_pwm_branch_get_func_pcn_addr(priv->ddPwmBranch, ch);
	}

	pcnTmp.word = pcnAddr->word;
	/* timer count enable	@PCNH	*/
	pcnTmp.bit.__CNTE = 0;
	/* PWM or One-Shot 		@PCNH	*/
	pcnTmp.bit.__MDSE = pwmCtrlCmn->drvMode;
	/* restart enable		@PCNH	*/
	pcnTmp.bit.__RTRG = pwmCtrlCmn->restartTrig;
	/* clock select			@PCNH	*/
	pcnTmp.bit.__CKS	= pwmCtrlCmn->clkSel;
	/* output level mask	@PCNH	*/
	pcnTmp.bit.__PGMS	= pwmCtrlCmn->outMask;
	/* edge enable select	@PCNH	*/
	pcnTmp.bit.__EGS	= pwmCtrlCmn->edge;
	/* interrupt enable		@PCNH	*/
	pcnTmp.bit.__IREN = 0;
	/* interrupt flag		@PCNH	*/
	pcnTmp.bit.__IRQF = 0;
	/* interrupt factor		@PCNH	*/
	pcnTmp.bit.__IRS = pwmCtrlCmn->trigger;
	/* output polarity		@PCNH	*/
	pcnTmp.bit.__OSEL = pwmCtrlCmn->polarity;
	pcnAddr->word = pcnTmp.word;

	/* timer E enable		@GCN2	*/
	IO_PERI.PWM[blk].GCN2.bit.TMEEN = pwmCtrlCmn->timEEnable;
	/* channel assignment	@GCN2	*/
	IO_PERI.PWM[blk].GCN2.bit.CHAS	 = pwmCtrlCmn->chAssign;

	switch (chInBlk) {
		case 0:
			/* switch factor			*/
			IO_PERI.PWM[blk].TSEL.bit.SEL0 = 0;
			 /* trigger input factor	*/
			IO_PERI.PWM[blk].GCN1.bit.TSEL0 = pwmCtrlCmn->inTrigger;
			/* reverse register*/
			IO_PERI.PWM[blk].PREV.bit.PREVE0 = 0;
			break;

		case 1:
			/* switch factor			*/
			IO_PERI.PWM[blk].TSEL.bit.SEL1 = 0;
			/* trigger input factor*/
			IO_PERI.PWM[blk].GCN1.bit.TSEL1 = pwmCtrlCmn->inTrigger;
			/* reverse register*/
			IO_PERI.PWM[blk].PREV.bit.PREVE1 = 0;
			break;

		case 2:
			/* switch factor	*/
			IO_PERI.PWM[blk].TSEL.bit.SEL2 = 0;
			/* trigger input factor*/
			IO_PERI.PWM[blk].GCN1.bit.TSEL2 = pwmCtrlCmn->inTrigger;
			/* reverse register*/
			IO_PERI.PWM[blk].PREV.bit.PREVE2 = 0;
			break;

		case 3:
			/* switch factor	*/
			IO_PERI.PWM[blk].TSEL.bit.SEL3 = 0;
			/* trigger input factor*/
			IO_PERI.PWM[blk].GCN1.bit.TSEL3 = pwmCtrlCmn->inTrigger;
			/* reverse register*/
			IO_PERI.PWM[blk].PREV.bit.PREVE3 = 0;
			break;

		default:
			break;
	}

	return D_DDIM_OK;
}

/*
 * @brief  The PWM operational condition of a control channel is set.
 * @param  kuint32 ch, DdPwmCtrlCmn* pwmCtrlCmn, kuchar prevEn
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_ctrl_common2(DdPwm* self, kuint32 ch, DdPwmCtrlCmn const* const pwmCtrlCmn, kuchar prevEn)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	const kuint32 chInBlk = (DdPwmBranch_CH_NUM_IN_BLOCK - 1) & ch;
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;
	volatile union io_pwm_pcn* pcnAddr;
	union io_pwm_pcn pcnTmp;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (0 == pwmCtrlCmn) {
		Ddim_Assertion(("PWM input param error. [pwmCtrlCmn] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (prevEn > DdPwmBranch_PREV_ON) {
		Ddim_Assertion(("PWM input param error. [prevEn] = %d\n", prevEn));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	dd_pwm_branch_set_clk_sel(priv->ddPwmBranch, ch, pwmCtrlCmn->clkSel);
	dd_pwm_branch_set_int_enable(priv->ddPwmBranch, ch, pwmCtrlCmn->intEnable);
	dd_pwm_branch_set_p_callback(priv->ddPwmBranch, ch, pwmCtrlCmn->pCallback);

	if (pwmCtrlCmn->timEEnable) {
		pcnAddr = (union io_pwm_pcn*)&IO_PERI.PWM[blk].PCNE;
	}
	else {
		pcnAddr = dd_pwm_branch_get_func_pcn_addr(priv->ddPwmBranch, ch);
	}

	pcnTmp.word = pcnAddr->word;
	/* timer count enable	@PCNH	*/
	pcnTmp.bit.__CNTE = 0;
	/* PWM or One-Shot 		@PCNH	*/
	pcnTmp.bit.__MDSE = pwmCtrlCmn->drvMode;
	/* restart enable		@PCNH	*/
	pcnTmp.bit.__RTRG = pwmCtrlCmn->restartTrig;
	/* clock select			@PCNH	*/
	pcnTmp.bit.__CKS	= pwmCtrlCmn->clkSel;
	/* output level mask	@PCNH	*/
	pcnTmp.bit.__PGMS	= pwmCtrlCmn->outMask;
	/* edge enable select	@PCNH	*/
	pcnTmp.bit.__EGS	= pwmCtrlCmn->edge;
	/* interrupt enable		@PCNH	*/
	pcnTmp.bit.__IREN = 0;
	/* interrupt flag		@PCNH	*/
	pcnTmp.bit.__IRQF = 0;
	/* interrupt factor		@PCNH	*/
	pcnTmp.bit.__IRS = pwmCtrlCmn->trigger;
	/* output polarity		@PCNH	*/
	pcnTmp.bit.__OSEL = pwmCtrlCmn->polarity;
	pcnAddr->word = pcnTmp.word;

	/* timer E enable		@GCN2	*/
	IO_PERI.PWM[blk].GCN2.bit.TMEEN = pwmCtrlCmn->timEEnable;
	/* channel assignment	@GCN2	*/
	IO_PERI.PWM[blk].GCN2.bit.CHAS = pwmCtrlCmn->chAssign;

	switch (chInBlk) {
		case 0:
			IO_PERI.PWM[blk].TSEL.bit.SEL0 = 0;
			/* switch factor	*/
//			IO_PERI.PWM[blk].TSEL.bit.SEL0 = 1;
			/* trigger input factor*/
			IO_PERI.PWM[blk].GCN1.bit.TSEL0 = pwmCtrlCmn->inTrigger;

			if(prevEn == DdPwmBranch_PREV_ON){
				/* reverse register*/
				IO_PERI.PWM[blk].PREV.bit.PREVE0 = 1;
			}
			else{
				/* reverse register*/
				IO_PERI.PWM[blk].PREV.bit.PREVE0 = 0;
			}
			break;

		case 1:
			IO_PERI.PWM[blk].TSEL.bit.SEL1 = 0;
			/* switch factor	*/
//			IO_PERI.PWM[blk].TSEL.bit.SEL1 = 1;
			/* trigger input factor*/
			IO_PERI.PWM[blk].GCN1.bit.TSEL1 = pwmCtrlCmn->inTrigger;
			if(prevEn == DdPwmBranch_PREV_ON){
				/* reverse register*/
				IO_PERI.PWM[blk].PREV.bit.PREVE1 = 1;
			}
			else{
				/* reverse register*/
				IO_PERI.PWM[blk].PREV.bit.PREVE1 = 0;
			}
			break;

		case 2:
			IO_PERI.PWM[blk].TSEL.bit.SEL2 = 0;
			/* switch factor			*/
//			IO_PERI.PWM[blk].TSEL.bit.SEL2 = 1;
			 /* trigger input factor*/
			IO_PERI.PWM[blk].GCN1.bit.TSEL2 = pwmCtrlCmn->inTrigger;
			if(prevEn == DdPwmBranch_PREV_ON){
				/* reverse register*/
				IO_PERI.PWM[blk].PREV.bit.PREVE2 = 1;
			}
			else{
				/* reverse register*/
				IO_PERI.PWM[blk].PREV.bit.PREVE2 = 0;
			}
			break;

		case 3:
			IO_PERI.PWM[blk].TSEL.bit.SEL3 = 0;
			/* switch factor*/
//			IO_PERI.PWM[blk].TSEL.bit.SEL3 = 1;
			/* trigger input factor*/
			IO_PERI.PWM[blk].GCN1.bit.TSEL3 = pwmCtrlCmn->inTrigger;
			if(prevEn == DdPwmBranch_PREV_ON){
				/* reverse register*/
				IO_PERI.PWM[blk].PREV.bit.PREVE3 = 1;
			}
			else{
				/* reverse register*/
				IO_PERI.PWM[blk].PREV.bit.PREVE3 = 0;
			}
			break;

		default:
			break;
	}

	return D_DDIM_OK;
}

/*
 * @brief  The PWM operational condition of a control channel is get.
 * @param  kuint32 ch, DdPwmCtrlCmn* pwmCtrlCmn
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_get_ctrl_common(DdPwm* self, kuint32 ch, DdPwmCtrlCmn* const pwmCtrlCmn)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	const kuint32 chInBlk = (DdPwmBranch_CH_NUM_IN_BLOCK - 1) & ch;
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;
	volatile union io_pwm_pcn* pcnAddr;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (0 == pwmCtrlCmn) {
		Ddim_Assertion(("PWM input param error. [pwmCtrlCmn] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	if (pwmCtrlCmn->timEEnable) {
		pcnAddr = (union io_pwm_pcn*)&IO_PERI.PWM[blk].PCNE;
	}
	else {
		pcnAddr = dd_pwm_branch_get_func_pcn_addr(priv->ddPwmBranch, ch);
	}

	pwmCtrlCmn->drvMode = pcnAddr->bit.__MDSE;
	pwmCtrlCmn->restartTrig = pcnAddr->bit.__RTRG;
	pwmCtrlCmn->clkSel = pcnAddr->bit.__CKS;
	pwmCtrlCmn->outMask	 = pcnAddr->bit.__PGMS;
	pwmCtrlCmn->edge	= pcnAddr->bit.__EGS;
	pwmCtrlCmn->intEnable = dd_pwm_branch_get_ctrl_memo(priv->ddPwmBranch, ch).intEnable;
	pwmCtrlCmn->trigger = pcnAddr->bit.__IRS;
	pwmCtrlCmn->polarity = pcnAddr->bit.__OSEL;
	switch (chInBlk) {
		case 0:
			pwmCtrlCmn->inTrigger = IO_PERI.PWM[blk].GCN1.bit.TSEL0;
			break;
		case 1:
			pwmCtrlCmn->inTrigger = IO_PERI.PWM[blk].GCN1.bit.TSEL1;
			break;
		case 2:
			pwmCtrlCmn->inTrigger = IO_PERI.PWM[blk].GCN1.bit.TSEL2;
			break;
		case 3:
			pwmCtrlCmn->inTrigger = IO_PERI.PWM[blk].GCN1.bit.TSEL3;
			break;
		default:
			break;
	}
	pwmCtrlCmn->timEEnable = IO_PERI.PWM[blk].GCN2.bit.TMEEN;
	pwmCtrlCmn->chAssign = IO_PERI.PWM[blk].GCN2.bit.CHAS;
	pwmCtrlCmn->pCallback = dd_pwm_branch_get_ctrl_memo(priv->ddPwmBranch, ch).pCallback;

	return D_DDIM_OK;
}

/*
 * @brief  The PWM Timer ABCD operational condition of a control channel is set.
 * @param  kuint32 ch, DdpwmCtrlTimerAbcd* pwmCtrlTimerAbcd
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_ctrl_timer_abcd(DdPwm* self, kuint32 ch, DdpwmCtrlTimerAbcd const* const pwmCtrlTimerAbcd)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	const kuint32 chInBlk = (DdPwmBranch_CH_NUM_IN_BLOCK - 1) & ch;
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;
	volatile union io_pwm_pcn* pcnAddr;
	union io_pwm_pcn pcnTmp;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (0 == pwmCtrlTimerAbcd) {
		Ddim_Assertion(("PWM input param error. [pwmCtrlTimerAbcd] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	pcnAddr = dd_pwm_branch_get_func_pcn_addr(priv->ddPwmBranch, ch);

	dd_pwm_branch_set_cyc_num(priv->ddPwmBranch, ch, pwmCtrlTimerAbcd->cycNum);
	dd_pwm_branch_set_duty_num(priv->ddPwmBranch, ch, pwmCtrlTimerAbcd->dutyNum);

	switch (chInBlk) {
		case 0:
			/* number of cycle*/
			IO_PERI.PWM[blk].PCSRA = pwmCtrlTimerAbcd->cycNum;
			/* number of duty*/
			IO_PERI.PWM[blk].PDUTA = pwmCtrlTimerAbcd->dutyNum;
			IO_PERI.PWM[blk].GCN2.bit.STP0 = 0;
			break;

		case 1:
			/* number of cycle*/
			IO_PERI.PWM[blk].PCSRB = pwmCtrlTimerAbcd->cycNum;
			/* number of duty*/
			IO_PERI.PWM[blk].PDUTB = pwmCtrlTimerAbcd->dutyNum;
			IO_PERI.PWM[blk].GCN2.bit.STP1 = 0;
			break;

		case 2:
			/* number of cycle*/
			IO_PERI.PWM[blk].PCSRC = pwmCtrlTimerAbcd->cycNum;
			/* number of duty*/
			IO_PERI.PWM[blk].PDUTC = pwmCtrlTimerAbcd->dutyNum;
			IO_PERI.PWM[blk].GCN2.bit.STP2 = 0;
			break;

		case 3:
			/* number of cycle	*/
			IO_PERI.PWM[blk].PCSRD = pwmCtrlTimerAbcd->cycNum;
			/* number of duty*/
			IO_PERI.PWM[blk].PDUTD = pwmCtrlTimerAbcd->dutyNum;
			IO_PERI.PWM[blk].GCN2.bit.STP3 = 0;
			break;

		default:
			break;
	}

	pcnTmp.word = pcnAddr->word;
	/* timer count enable	@PCNH	*/
	pcnTmp.bit.__CNTE = 1;
	/* interrupt flag (not change)	*/
	pcnTmp.bit.__IRQF = 1;
	pcnAddr->word = pcnTmp.word;

	return D_DDIM_OK;
}

/*
 * @brief  The PWM Timer ABCD operational condition of a control channel is set.
 * @param  kuint32 ch, DdpwmCtrlTimerAbcd2ch* pwmCtrlTimerAbcd2ch
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_ctrl_timer_abcd_2ch(DdPwm* self, kuint32 ch,
		DdpwmCtrlTimerAbcd2ch const* const pwmCtrlTimerAbcd2ch)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	const kuint32 chInBlk = (DdPwmBranch_CH_NUM_IN_BLOCK - 1) & ch;
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;
	volatile union io_pwm_pcn* pcnAddr;
	union io_pwm_pcn pcnTmp;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (0 == pwmCtrlTimerAbcd2ch) {
		Ddim_Assertion(("PWM input param error. [pwmCtrlTimerAbcd] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	pcnAddr = dd_pwm_branch_get_func_pcn_addr(priv->ddPwmBranch, ch);

	dd_pwm_branch_set_cyc_num(priv->ddPwmBranch, ch, pwmCtrlTimerAbcd2ch->cycNum[0]);
	dd_pwm_branch_set_duty_num(priv->ddPwmBranch, ch, pwmCtrlTimerAbcd2ch->dutyNum[0]);

	switch (chInBlk) {
		case 0:
			/* number of cycle			*/
			IO_PERI.PWM[blk].PCSRA = pwmCtrlTimerAbcd2ch->cycNum[0];
			/* number of duty			*/
			IO_PERI.PWM[blk].PDUTA = pwmCtrlTimerAbcd2ch->dutyNum[0];
			/* number of cycle			*/
			IO_PERI.PWM[blk].PCSRRA = pwmCtrlTimerAbcd2ch->cycNum[1];
			/* number of duty			*/
			IO_PERI.PWM[blk].PDUTRA = pwmCtrlTimerAbcd2ch->dutyNum[1];
			IO_PERI.PWM[blk].GCN2.bit.STP0 = 0;
			/* Output L in STOP state	*/
			IO_PERI.PWM[blk].PCHSET0.bit.FRCVAL0 = 0;
			IO_PERI.PWM[blk].PCHSET0.bit.FRCEN0 = 1;
			break;

		case 1:
			/* number of cycle			*/
			IO_PERI.PWM[blk].PCSRB = pwmCtrlTimerAbcd2ch->cycNum[0];
			/* number of duty			*/
			IO_PERI.PWM[blk].PDUTB = pwmCtrlTimerAbcd2ch->dutyNum[0];
			/* number of cycle			*/
			IO_PERI.PWM[blk].PCSRRB = pwmCtrlTimerAbcd2ch->cycNum[1];
			/* number of duty			*/
			IO_PERI.PWM[blk].PDUTRB = pwmCtrlTimerAbcd2ch->dutyNum[1];
			IO_PERI.PWM[blk].GCN2.bit.STP1 = 0;
			/* Output L in STOP state	*/
			IO_PERI.PWM[blk].PCHSET0.bit.FRCVAL1 = 0;
			IO_PERI.PWM[blk].PCHSET0.bit.FRCEN1 = 1;
			break;

		case 2:
			/* number of cycle			*/
			IO_PERI.PWM[blk].PCSRC = pwmCtrlTimerAbcd2ch->cycNum[0];
			/* number of duty			*/
			IO_PERI.PWM[blk].PDUTC = pwmCtrlTimerAbcd2ch->dutyNum[0];
			/* number of cycle			*/
			IO_PERI.PWM[blk].PCSRRC = pwmCtrlTimerAbcd2ch->cycNum[1];
			/* number of duty			*/
			IO_PERI.PWM[blk].PDUTRC = pwmCtrlTimerAbcd2ch->dutyNum[1];
			IO_PERI.PWM[blk].GCN2.bit.STP2 = 0;
			/* Output L in STOP state	*/
			IO_PERI.PWM[blk].PCHSET0.bit.FRCVAL2 = 0;
			IO_PERI.PWM[blk].PCHSET0.bit.FRCEN2 = 1;
			break;

		case 3:
			/* number of cycle			*/
			IO_PERI.PWM[blk].PCSRD = pwmCtrlTimerAbcd2ch->cycNum[0];
			/* number of duty			*/
			IO_PERI.PWM[blk].PDUTD = pwmCtrlTimerAbcd2ch->dutyNum[0];
			/* number of cycle			*/
			IO_PERI.PWM[blk].PCSRRD = pwmCtrlTimerAbcd2ch->cycNum[1];
			/* number of duty			*/
			IO_PERI.PWM[blk].PDUTRD = pwmCtrlTimerAbcd2ch->dutyNum[1];
			IO_PERI.PWM[blk].GCN2.bit.STP3 = 0;
			/* Output L in STOP state	*/
			IO_PERI.PWM[blk].PCHSET0.bit.FRCVAL3 = 0;
			IO_PERI.PWM[blk].PCHSET0.bit.FRCEN3 = 1;
			break;

		default:
			break;
	}

	pcnTmp.word = pcnAddr->word;
	/* timer count enable	@PCNH	*/
	pcnTmp.bit.__CNTE = 1;
	/* interrupt flag (not change)	*/
	pcnTmp.bit.__IRQF = 1;
	pcnAddr->word = pcnTmp.word;

	return D_DDIM_OK;
}

/*
 * @brief  The PWM Timer E operational condition of a control channel is set.
 * @param  kuint32 ch, PwmCtrlTimerE* pwmCtrlTimerE
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_ctrl_timer_e(DdPwm* self, kuint32 ch, PwmCtrlTimerE const* const pwmCtrlTimerE)
{
	union io_pwm_pintct0 pintct0Tmp;    //TODO

	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (0 == pwmCtrlTimerE) {
		Ddim_Assertion(("PWM input param error. [pwmCtrlTimerE] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	IO_PERI.PWM[blk].PCHSET0.bit.HLD0 = pwmCtrlTimerE->hold[0];
	IO_PERI.PWM[blk].PCHSET0.bit.HLD1 = pwmCtrlTimerE->hold[1];
	IO_PERI.PWM[blk].PCHSET0.bit.HLD2 = pwmCtrlTimerE->hold[2];
	IO_PERI.PWM[blk].PCHSET0.bit.HLD3 = pwmCtrlTimerE->hold[3];

	IO_PERI.PWM[blk].PCHSET0.bit.FRCVAL0 = pwmCtrlTimerE->forceVal[0];
	IO_PERI.PWM[blk].PCHSET0.bit.FRCVAL1 = pwmCtrlTimerE->forceVal[1];
	IO_PERI.PWM[blk].PCHSET0.bit.FRCVAL2 = pwmCtrlTimerE->forceVal[2];
	IO_PERI.PWM[blk].PCHSET0.bit.FRCVAL3 = pwmCtrlTimerE->forceVal[3];

	IO_PERI.PWM[blk].PCHSET0.bit.FRCEN0 = pwmCtrlTimerE->force[0];
	IO_PERI.PWM[blk].PCHSET0.bit.FRCEN1 = pwmCtrlTimerE->force[1];
	IO_PERI.PWM[blk].PCHSET0.bit.FRCEN2 = pwmCtrlTimerE->force[2];
	IO_PERI.PWM[blk].PCHSET0.bit.FRCEN3 = pwmCtrlTimerE->force[3];

	IO_PERI.PWM[blk].PCSRE0 = pwmCtrlTimerE->stepsData[0].cycNum;
	IO_PERI.PWM[blk].PCSRE1 = pwmCtrlTimerE->stepsData[1].cycNum;
	IO_PERI.PWM[blk].PCSRE2 = pwmCtrlTimerE->stepsData[2].cycNum;
	IO_PERI.PWM[blk].PCSRE3 = pwmCtrlTimerE->stepsData[3].cycNum;
	IO_PERI.PWM[blk].PCSRE4 = pwmCtrlTimerE->stepsData[4].cycNum;
	IO_PERI.PWM[blk].PCSRE5 = pwmCtrlTimerE->stepsData[5].cycNum;
	IO_PERI.PWM[blk].PCSRE6 = pwmCtrlTimerE->stepsData[6].cycNum;
	IO_PERI.PWM[blk].PCSRE7 = pwmCtrlTimerE->stepsData[7].cycNum;

	IO_PERI.PWM[blk].PDUTE0 = pwmCtrlTimerE->stepsData[0].dutyNum;
	IO_PERI.PWM[blk].PDUTE1 = pwmCtrlTimerE->stepsData[1].dutyNum;
	IO_PERI.PWM[blk].PDUTE2 = pwmCtrlTimerE->stepsData[2].dutyNum;
	IO_PERI.PWM[blk].PDUTE3 = pwmCtrlTimerE->stepsData[3].dutyNum;
	IO_PERI.PWM[blk].PDUTE4 = pwmCtrlTimerE->stepsData[4].dutyNum;
	IO_PERI.PWM[blk].PDUTE5 = pwmCtrlTimerE->stepsData[5].dutyNum;
	IO_PERI.PWM[blk].PDUTE6 = pwmCtrlTimerE->stepsData[6].dutyNum;
	IO_PERI.PWM[blk].PDUTE7 = pwmCtrlTimerE->stepsData[7].dutyNum;

	IO_PERI.PWM[blk].PPALE0.bit.PPALE = pwmCtrlTimerE->stepsData[0].pulseLink.bit.pulseNum;
	IO_PERI.PWM[blk].PPALE1.bit.PPALE = pwmCtrlTimerE->stepsData[1].pulseLink.bit.pulseNum;
	IO_PERI.PWM[blk].PPALE2.bit.PPALE = pwmCtrlTimerE->stepsData[2].pulseLink.bit.pulseNum;
	IO_PERI.PWM[blk].PPALE3.bit.PPALE = pwmCtrlTimerE->stepsData[3].pulseLink.bit.pulseNum;
	IO_PERI.PWM[blk].PPALE4.bit.PPALE = pwmCtrlTimerE->stepsData[4].pulseLink.bit.pulseNum;
	IO_PERI.PWM[blk].PPALE5.bit.PPALE = pwmCtrlTimerE->stepsData[5].pulseLink.bit.pulseNum;
	IO_PERI.PWM[blk].PPALE6.bit.PPALE = pwmCtrlTimerE->stepsData[6].pulseLink.bit.pulseNum;
	IO_PERI.PWM[blk].PPALE7.bit.PPALE = pwmCtrlTimerE->stepsData[7].pulseLink.bit.pulseNum;

	IO_PERI.PWM[blk].PPALE0.bit.LINK = pwmCtrlTimerE->stepsData[0].pulseLink.bit.link;
	IO_PERI.PWM[blk].PPALE1.bit.LINK = pwmCtrlTimerE->stepsData[1].pulseLink.bit.link;
	IO_PERI.PWM[blk].PPALE2.bit.LINK = pwmCtrlTimerE->stepsData[2].pulseLink.bit.link;
	IO_PERI.PWM[blk].PPALE3.bit.LINK = pwmCtrlTimerE->stepsData[3].pulseLink.bit.link;
	IO_PERI.PWM[blk].PPALE4.bit.LINK = pwmCtrlTimerE->stepsData[4].pulseLink.bit.link;
	IO_PERI.PWM[blk].PPALE5.bit.LINK = pwmCtrlTimerE->stepsData[5].pulseLink.bit.link;
	IO_PERI.PWM[blk].PPALE6.bit.LINK = pwmCtrlTimerE->stepsData[6].pulseLink.bit.link;
	IO_PERI.PWM[blk].PPALE7.bit.LINK = pwmCtrlTimerE->stepsData[7].pulseLink.bit.link;

	IO_PERI.PWM[blk].PCSRU0 = pwmCtrlTimerE->underRunData[0].cycNum;
	IO_PERI.PWM[blk].PCSRU1 = pwmCtrlTimerE->underRunData[1].cycNum;
	IO_PERI.PWM[blk].PCSRU2 = pwmCtrlTimerE->underRunData[2].cycNum;
	IO_PERI.PWM[blk].PCSRU3 = pwmCtrlTimerE->underRunData[3].cycNum;

	IO_PERI.PWM[blk].PDUTU0 = pwmCtrlTimerE->underRunData[0].dutyNum;
	IO_PERI.PWM[blk].PDUTU1 = pwmCtrlTimerE->underRunData[1].dutyNum;
	IO_PERI.PWM[blk].PDUTU2 = pwmCtrlTimerE->underRunData[2].dutyNum;
	IO_PERI.PWM[blk].PDUTU3 = pwmCtrlTimerE->underRunData[3].dutyNum;

	IO_PERI.PWM[blk].PPALU0.bit.PPALU = pwmCtrlTimerE->underRunData[0].pulseLink.bit.pulseNum;
	IO_PERI.PWM[blk].PPALU1.bit.PPALU = pwmCtrlTimerE->underRunData[1].pulseLink.bit.pulseNum;
	IO_PERI.PWM[blk].PPALU2.bit.PPALU = pwmCtrlTimerE->underRunData[2].pulseLink.bit.pulseNum;
	IO_PERI.PWM[blk].PPALU3.bit.PPALU = pwmCtrlTimerE->underRunData[3].pulseLink.bit.pulseNum;

	IO_PERI.PWM[blk].PPALU0.bit.LINK = pwmCtrlTimerE->underRunData[0].pulseLink.bit.link;
	IO_PERI.PWM[blk].PPALU1.bit.LINK = pwmCtrlTimerE->underRunData[1].pulseLink.bit.link;
	IO_PERI.PWM[blk].PPALU2.bit.LINK = pwmCtrlTimerE->underRunData[2].pulseLink.bit.link;
	IO_PERI.PWM[blk].PPALU3.bit.LINK = pwmCtrlTimerE->underRunData[3].pulseLink.bit.link;

	IO_PERI.PWM[blk].PCHSET1.word = (((kushort)pwmCtrlTimerE->emptyDmaReq) << 8)
										| ((kushort)pwmCtrlTimerE->undrRunEnable);
	pintct0Tmp.word = IO_PERI.PWM[blk].PINTCT0.word;
	pintct0Tmp.bit.__UIE	= pwmCtrlTimerE->undrRunIntErrEnable;
	pintct0Tmp.bit.__FIE	= pwmCtrlTimerE->forceStopIntEnable;
	pintct0Tmp.bit.__AIE	= pwmCtrlTimerE->autoStopIntEnable;
	/* underrun error (not change)	*/
	pintct0Tmp.bit.__UIS	= 0;
	/* Force stop (not change)		*/
	pintct0Tmp.bit.__FIS	= 0;
	/* Automatic stop (not change)	*/
	pintct0Tmp.bit.__AIS	= 0;
	IO_PERI.PWM[blk].PINTCT0.word = pintct0Tmp.word;
	IO_PERI.PWM[blk].PINTCT1.bit.DRQE = pwmCtrlTimerE->dmaIntEnable;

	return D_DDIM_OK;
}

kint32 dd_pwm_start(DdPwm* self, kuint32 ch)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_start(priv->ddPwmBranch, ch);
}

kint32 dd_pwm_2ch_start(DdPwm* self, kuint32 chA, kuint32 chB)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_2ch_start(priv->ddPwmBranch, chA, chB);
}

kint32 dd_pwm_stop(DdPwm* self, kuint32 ch)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_stop(priv->ddPwmBranch, ch);
}

kint32 dd_pwm_get_timer(DdPwm* self, kuint32 ch, kushort* timerVal, kushort* timerEVal)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_get_timer(priv->ddPwmBranch, ch, timerVal, timerEVal);
}

kint32 dd_pwm_get_pulse_num(DdPwm* self, kuint32 ch, kulong* pulseNum)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_get_pulse_num(priv->ddPwmBranch, ch, pulseNum);
}

kint32 dd_pwm_get_interrupt_flag(DdPwm* self,
		           kuint32 ch, kushort* intFlgCtrl0, kushort* intFlgCtrl1)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_get_interrupt_flag(priv->ddPwmBranch, ch, intFlgCtrl0, intFlgCtrl1);
}

kint32 dd_pwm_set_interrupt_flag(DdPwm* self, kuint32 ch,
		           kushort intFlgCtrl0, kushort intFlgCtrl1)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_set_interrupt_flag(priv->ddPwmBranch, ch, intFlgCtrl0, intFlgCtrl1);
}

kint32 dd_pwm_get_channel_assign(DdPwm* self, kuint32 ch, kuchar* chAssign)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_get_channel_assign(priv->ddPwmBranch, ch, chAssign);
}

kint32 dd_pwm_set_channel_assign(DdPwm* self, kuint32 ch, kuchar chAssign)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_set_channel_assign(priv->ddPwmBranch, ch, chAssign);
}

kboolean dd_pwm_get_int_stat(DdPwm* self, kuint32 ch)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_get_int_stat(priv->ddPwmBranch, ch);
}

void dd_pwm_int_handler(DdPwm* self, kuint32 ch)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	dd_pwm_branch_int_handler(priv->ddPwmBranch, ch);
}

void dd_pwm_int_handler_stp(DdPwm* self, kuint32 ch)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	dd_pwm_branch_int_handler_stp(priv->ddPwmBranch, ch);
}

kint32 dd_pwm_set_stopped_output_mask(DdPwm* self, kuint32 ch, kuchar mask)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_set_stopped_output_mask(priv->ddPwmBranch, ch, mask);
}

kint32 dd_pwm_get_stopped_output_mask(DdPwm* self, kuint32 ch, kuchar* mask)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_get_stopped_output_mask(priv->ddPwmBranch, ch, mask);
}

kint32 dd_pwm_get_clock_sel_timer_e(DdPwm* self, kuint32 ch, kuchar* clock)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_get_clock_sel_timer_e(priv->ddPwmBranch, ch, clock);
}

kint32 dd_pwm_get_stopped_output_status(DdPwm* self, kuint32 ch, kuchar* chStatus)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_get_stopped_output_status(priv->ddPwmBranch, ch, chStatus);
}

volatile union io_pwm_pcn* dd_pwm_get_branch_func_pcn_addr(DdPwm* self, kuint32 ch)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_get_func_pcn_addr(priv->ddPwmBranch, ch);
}

DdPwmCtrlMemo dd_pwm_get_branch_ctrl_memo(DdPwm* self, kuint32 ch)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	return dd_pwm_branch_get_ctrl_memo(priv->ddPwmBranch, ch);
}

void dd_pwm_set_branch_dma_enable(DdPwm* self, kuint32 ch, kuchar dmaEnable)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	dd_pwm_branch_set_dma_enable(priv->ddPwmBranch, ch, dmaEnable);
}

void dd_pwm_set_branch_dma_ch(DdPwm* self, kuint32 ch, kuchar dmaCh)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	dd_pwm_branch_set_dma_ch(priv->ddPwmBranch, ch, dmaCh);
}

void dd_pwm_set_branch_cyc_num(DdPwm* self, kuint32 ch, kushort cycNum)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	dd_pwm_branch_set_cyc_num(priv->ddPwmBranch, ch, cycNum);
}

void dd_pwm_set_branch_duty_num(DdPwm* self, kuint32 ch, kushort dutyNum)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	dd_pwm_branch_set_duty_num(priv->ddPwmBranch, ch, dutyNum);
}

void dd_pwm_set_branch_clk_sel(DdPwm* self, kuint32 ch, kuchar clkSel)
{
	DdPwmPrivate *priv = DD_PWM_GET_PRIVATE(self);
	dd_pwm_branch_set_clk_sel(priv->ddPwmBranch, ch, clkSel);
}

DdPwm* dd_pwm_get(void)
{
	DdPwm *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_PWM, sizeof(DdPwmPrivate));
	}

	return self;
}
