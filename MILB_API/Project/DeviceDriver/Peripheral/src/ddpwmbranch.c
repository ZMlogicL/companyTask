/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :PWM driver(branch)
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

#include "dd_arm.h"
#include "dd_hdmac0.h"

#include "ddpwmbranch.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdPwmBranch, dd_pwm_branch);
#define DD_PWM_BRANCH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdPwmBranchPrivate, DD_TYPE_PWM_BRANCH))

#define DdPwmBranch_DD_PWM_DSB() Dd_ARM_Dsb_Pou()

struct _DdPwmBranchPrivate
{
	// PWM control management table
	volatile DdPwmCtrlMemo gDdPwmCtrl[DdPwmBranch_CH_NUM_MAX];
};

/*
 * DECLS
 */
static volatile union io_pwm_pcn*    ddPwmPcnAddr(DdPwmBranch* self, kuint32 ch);   //TODO

static void dd_pwm_branch_constructor(DdPwmBranch *self)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);

	kint i;

	for(i = 0; i < DdPwmBranch_CH_NUM_MAX; i++){
		priv->gDdPwmCtrl[i].pCallback = NULL;
	}
}

static void dd_pwm_branch_destructor(DdPwmBranch *self)
{

}

/*
 * IMPL
 */
/*
 * @brief  Get PWM control PCNx register Address.
 * @param  kuint32 ch
 * @return union io_pwm_pcn*
 */
static volatile union io_pwm_pcn* ddPwmPcnAddr(DdPwmBranch* self, kuint32 ch)     //TODO
{
	const kuint32 chInBlk = (DdPwmBranch_CH_NUM_IN_BLOCK - 1) & ch;
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;
	volatile union io_pwm_pcn* pcnAddr = NULL;

	switch (chInBlk) {
		case 0:
			pcnAddr = (union io_pwm_pcn*) &IO_PERI.PWM[blk].PCNA;
			break;

		case 1:
			pcnAddr = (union io_pwm_pcn*) &IO_PERI.PWM[blk].PCNB;
			break;

		case 2:
			pcnAddr = (union io_pwm_pcn*) &IO_PERI.PWM[blk].PCNC;
			break;

		case 3:
			pcnAddr = (union io_pwm_pcn*) &IO_PERI.PWM[blk].PCND;
			break;

		default:
			break;
	}
	return pcnAddr;
}

/*
 * PUBLIC
 */
/*
 * @brief  The PWM of a control channel is started.
 * @param  kuint32 ch
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_branch_start(DdPwmBranch* self, kuint32 ch)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
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
#endif

	if(IO_PERI.PWM[blk].GCN2.bit.TMEEN) {
		kushort temp;

		IO_PERI.PWM[blk].GCN2.bit.STP0 = 0;
		temp = IO_PERI.PWM[blk].PINTCT0.word;
		/* clear UIS, FIS, AIS			*/
		IO_PERI.PWM[blk].PINTCT0.word = temp;
		pcnTmp.word = IO_PERI.PWM[blk].PCNE.word;
		/* timer count enable	@PCNH	*/
		pcnTmp.bit.__CNTE	= 1;
		/* interrupt flag (not change)	*/
		pcnTmp.bit.__IRQF	= 1;
		/* interrupt enable		@PCNH	*/
		pcnTmp.bit.__IREN	= priv->gDdPwmCtrl[ch].intEnable;
		IO_PERI.PWM[blk].PCNE.word = pcnTmp.word;
		/* trigger on					*/
		IO_PERI.PWM[blk].GCN2.bit.EN0 = 1;
	}
	else {
		pcnAddr = dd_pwm_branch_get_func_pcn_addr(self, ch);
		pcnTmp.word = pcnAddr->word;
		/* interrupt enable		@PCNH	*/
		pcnTmp.bit.__IREN	= priv->gDdPwmCtrl[ch].intEnable;
		/* interrupt flag (not change)	*/
		pcnTmp.bit.__IRQF	= 1;
		pcnAddr->word = pcnTmp.word;

		/* trigger on					*/
		switch (chInBlk) {
			case 0:
				IO_PERI.PWM[blk].GCN2.bit.EN0 = 1;
				break;

			case 1:
				IO_PERI.PWM[blk].GCN2.bit.EN1 = 1;
				break;

			case 2:
				IO_PERI.PWM[blk].GCN2.bit.EN2 = 1;
				break;

			case 3:
				IO_PERI.PWM[blk].GCN2.bit.EN3 = 1;
				break;

			default:
				break;
		}
	}

	DdPwmBranch_DD_PWM_DSB();

	return D_DDIM_OK;
}

/*
 * @brief  The PWM of a control channel is started.
 * @param  kuint32 chA, kuint32 chB
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_branch_2ch_start(DdPwmBranch* self, kuint32 chA, kuint32 chB)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
	const kuint32 chInBlkA = (DdPwmBranch_CH_NUM_IN_BLOCK - 1) & chA;
	const kuint32 chInBlkB = (DdPwmBranch_CH_NUM_IN_BLOCK - 1) & chB;
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blkA = chA >> 2;
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blkB = chB >> 2;
	volatile union io_pwm_pcn* pcnAddrA;
	volatile union io_pwm_pcn* pcnAddrB;
	union io_pwm_pcn pcnATmp;
	union io_pwm_pcn pcnBTmp;

#ifdef CO_PARAM_CHECK
	if (chA >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. chA[ch] = %d\n", chA));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (chB >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. chB[ch] = %d\n", chB));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif



	if(IO_PERI.PWM[blkA].GCN2.bit.TMEEN) {
		kushort temp;

		IO_PERI.PWM[blkA].GCN2.bit.STP0 = 0;
		temp = IO_PERI.PWM[blkA].PINTCT0.word;
		/* clear UIS, FIS, AIS			*/
		IO_PERI.PWM[blkA].PINTCT0.word = temp;
		pcnATmp.word = IO_PERI.PWM[blkA].PCNE.word;
		/* timer count enable	@PCNH	*/
		pcnATmp.bit.__CNTE	= 1;
		/* interrupt flag (not change)	*/
		pcnATmp.bit.__IRQF	= 1;
		/* interrupt enable		@PCNH	*/
		pcnATmp.bit.__IREN	= priv->gDdPwmCtrl[chA].intEnable;
		IO_PERI.PWM[blkA].PCNE.word = pcnATmp.word;
	}
	else {
		pcnAddrA = dd_pwm_branch_get_func_pcn_addr(self, chA);
		pcnATmp.word = pcnAddrA->word;
		/* interrupt enable		@PCNH	*/
		pcnATmp.bit.__IREN	= priv->gDdPwmCtrl[chA].intEnable;
		/* interrupt flag (not change)	*/
		pcnATmp.bit.__IRQF	= 1;
		pcnAddrA->word = pcnATmp.word;
	}

	if(IO_PERI.PWM[blkB].GCN2.bit.TMEEN) {
		kushort temp;

		IO_PERI.PWM[blkB].GCN2.bit.STP0 = 0;
		temp = IO_PERI.PWM[blkB].PINTCT0.word;
		/* clear UIS, FIS, AIS			*/
		IO_PERI.PWM[blkB].PINTCT0.word = temp;
		pcnBTmp.word = IO_PERI.PWM[blkB].PCNE.word;
		/* timer count enable	@PCNH	*/
		pcnBTmp.bit.__CNTE = 1;
		/* interrupt flag (not change)	*/
		pcnBTmp.bit.__IRQF	= 1;
		/* interrupt enable		@PCNH	*/
		pcnBTmp.bit.__IREN	= priv->gDdPwmCtrl[chB].intEnable;
		IO_PERI.PWM[blkB].PCNE.word = pcnBTmp.word;
	}
	else {
		pcnAddrB = dd_pwm_branch_get_func_pcn_addr(self, chB);
		pcnBTmp.word = pcnAddrB->word;
		/* interrupt enable		@PCNH	*/
		pcnBTmp.bit.__IREN	= priv->gDdPwmCtrl[chB].intEnable;
		/* interrupt flag (not change)	*/
		pcnBTmp.bit.__IRQF	= 1;
		pcnAddrB->word = pcnBTmp.word;
	}

	if((IO_PERI.PWM[blkA].GCN2.bit.TMEEN == 1) && (IO_PERI.PWM[blkB].GCN2.bit.TMEEN == 1)) {
		/* trigger on					*/
		IO_PERI.PWM[blkA].GCN2.bit.EN0 = 1;
		/* trigger on					*/
		IO_PERI.PWM[blkB].GCN2.bit.EN0 = 1;
	}
	else {
		/* trigger on					*/
		switch (chInBlkA) {
			case 0:
				IO_PERI.PWM[blkA].GCN2.bit.EN0 = 1;
				break;

			case 1:
				IO_PERI.PWM[blkA].GCN2.bit.EN1 = 1;
				break;

			case 2:
				IO_PERI.PWM[blkA].GCN2.bit.EN2 = 1;
				break;

			case 3:
				IO_PERI.PWM[blkA].GCN2.bit.EN3 = 1;
				break;

			default:
				break;
		}

		/* trigger on					*/
		switch (chInBlkB) {
			case 0:
				IO_PERI.PWM[blkB].GCN2.bit.EN0 = 1;
				break;

			case 1:
				IO_PERI.PWM[blkB].GCN2.bit.EN1 = 1;
				break;

			case 2:
				IO_PERI.PWM[blkB].GCN2.bit.EN2 = 1;
				break;

			case 3:
				IO_PERI.PWM[blkB].GCN2.bit.EN3 = 1;
				break;

			default:
				break;
		}
	}

	DdPwmBranch_DD_PWM_DSB();

	return D_DDIM_OK;
}

/*
 * @brief  The PWM of a control channel is stopped.
 * @param  kuint32 ch
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_branch_stop(DdPwmBranch* self, kuint32 ch)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
	kint32 ret;
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
#endif

	if(IO_PERI.PWM[blk].GCN2.bit.TMEEN) {
		IO_PERI.PWM[blk].GCN2.bit.STP0 = 1;
		DdPwmBranch_DD_PWM_DSB();

		IO_PERI.PWM[blk].GCN2.bit.EN0 = 0;

		pcnTmp.word = IO_PERI.PWM[blk].PCNE.word;
		/* interrupt enable		@PCNH	*/
		pcnTmp.bit.__IREN = 0;
		/* timer count enable	@PCNH	*/
		pcnTmp.bit.__CNTE = 0;
		/* interrupt flag (not change)	*/
		pcnTmp.bit.__IRQF = 1;
		IO_PERI.PWM[blk].PCNE.word = pcnTmp.word;
		DdPwmBranch_DD_PWM_DSB();

		if (priv->gDdPwmCtrl[ch].dmaEnable){
			ret = Dd_HDMAC0_Stop(priv->gDdPwmCtrl[ch].dmaCh);
			if(ret != D_DDIM_OK){
				Ddim_Print(("Error Dd_HDMAC0_Stop()!! ret = 0x%x\n", ret));
			}
			ret = Dd_HDMAC0_Close(priv->gDdPwmCtrl[ch].dmaCh);
			if(ret != D_DDIM_OK){
				Ddim_Print(("Error Dd_HDMAC0_Close()!! ret = 0x%x\n", ret));
			}
			priv->gDdPwmCtrl[ch].dmaEnable = 0;
		}
	}
	else {
		pcnAddr = dd_pwm_branch_get_func_pcn_addr(self, ch);

		switch (chInBlk) {
			case 0:
				IO_PERI.PWM[blk].GCN2.bit.STP0 = 1;
				DdPwmBranch_DD_PWM_DSB();
				IO_PERI.PWM[blk].GCN2.bit.EN0 = 0;
				break;

			case 1:
				IO_PERI.PWM[blk].GCN2.bit.STP1 = 1;
				DdPwmBranch_DD_PWM_DSB();
				IO_PERI.PWM[blk].GCN2.bit.EN1 = 0;
				break;

			case 2:
				IO_PERI.PWM[blk].GCN2.bit.STP2 = 1;
				DdPwmBranch_DD_PWM_DSB();
				IO_PERI.PWM[blk].GCN2.bit.EN2 = 0;
				break;

			case 3:
				IO_PERI.PWM[blk].GCN2.bit.STP3 = 1;
				DdPwmBranch_DD_PWM_DSB();
				IO_PERI.PWM[blk].GCN2.bit.EN3 = 0;
				break;

			default:
				break;
		}

		pcnTmp.word = pcnAddr->word;
		/* interrupt enable		@PCNH	*/
		pcnTmp.bit.__IREN = 0;
		/* timer count enable	@PCNH	*/
		pcnTmp.bit.__CNTE = 0;
		/* interrupt flag (not change)	*/
		pcnTmp.bit.__IRQF = 1;
		pcnAddr->word = pcnTmp.word;

		DdPwmBranch_DD_PWM_DSB();
	}

	return D_DDIM_OK;
}

kint32 dd_pwm_branch_get_timer(DdPwmBranch* self, kuint32 ch, kushort* timerVal, kushort* timerEVal)
{
	const kuint32 chInBlk = (DdPwmBranch_CH_NUM_IN_BLOCK - 1) & ch;
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	if (0 == timerVal) {
		Ddim_Assertion(("PWM input param error. [timerVal] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	if (0 == timerEVal) {
		Ddim_Assertion(("PWM input param error. [timerEVal] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	switch(chInBlk) {
		case 0:
			*timerVal = IO_PERI.PWM[blk].PTMRA;
			break;

		case 1:
			*timerVal = IO_PERI.PWM[blk].PTMRB;
			break;

		case 2:
			*timerVal = IO_PERI.PWM[blk].PTMRC;
			break;

		case 3:
			*timerVal = IO_PERI.PWM[blk].PTMRD;
			break;

		default:
			break;
	}
	*timerEVal = IO_PERI.PWM[blk].PTMRE;

	return D_DDIM_OK;
}

kint32 dd_pwm_branch_get_pulse_num(DdPwmBranch* self, kuint32 ch, kulong* pulseNum)
{
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	if (0 == pulseNum) {
		Ddim_Assertion(("PWM input param error. [pulseNum] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	*pulseNum = (IO_PERI.PWM[blk].STMRH << 16) | IO_PERI.PWM[blk].STMRL;

	return D_DDIM_OK;
}

kint32 dd_pwm_branch_get_interrupt_flag(DdPwmBranch* self, kuint32 ch,
		kushort* intFlgCtrl0, kushort* intFlgCtrl1)
{
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	if (0 == intFlgCtrl0) {
		Ddim_Assertion(("PWM input param error. [intFlgCtrl0] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	if (0 == intFlgCtrl1) {
		Ddim_Assertion(("PWM input param error. [intFlgCtrl1] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	*intFlgCtrl0 = IO_PERI.PWM[blk].PINTCT0.word;
	*intFlgCtrl1 = IO_PERI.PWM[blk].PINTCT1.word;

	return D_DDIM_OK;
}

kint32 dd_pwm_branch_set_interrupt_flag(DdPwmBranch* self, kuint32 ch,
		kushort intFlgCtrl0, kushort intFlgCtrl1)
{
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	IO_PERI.PWM[blk].PINTCT0.word = intFlgCtrl0;
	IO_PERI.PWM[blk].PINTCT1.word = intFlgCtrl1;
	DdPwmBranch_DD_PWM_DSB();

	return D_DDIM_OK;
}

kint32 dd_pwm_branch_get_channel_assign(DdPwmBranch* self, kuint32 ch, kuchar* chAssign)
{
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	if (0 == chAssign) {
		Ddim_Assertion(("PWM input param error. [chAssign] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	*chAssign = IO_PERI.PWM[blk].GCN2.bit.CHAS;

	return D_DDIM_OK;
}

kint32 dd_pwm_branch_set_channel_assign(DdPwmBranch* self, kuint32 ch, kuchar chAssign)
{
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	if (chAssign > DdPwmBranch_GCN_CHAS_CBAD) {
		Ddim_Assertion(("PWM input param error. [chAssign] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	IO_PERI.PWM[blk].GCN2.bit.CHAS = chAssign;

	return D_DDIM_OK;
}

/*
 * @brief  Get Interrupt Status of PWM. (Not PWM_STP)
 * @param  void
 * @return TRUE:Interrupt request occur. FALSE:No interrupt request
 */
kboolean dd_pwm_branch_get_int_stat(DdPwmBranch* self, kuint32 ch)
{
	volatile union io_pwm_pcn* pcnAddr;
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return FALSE;
	}
#endif

	pcnAddr = dd_pwm_branch_get_func_pcn_addr(self, ch);
	if(pcnAddr == NULL)
	{
		return FALSE;
	}
	if ((pcnAddr->bit.__IREN == 1) && (pcnAddr->bit.__IRQF == 1)){
		return TRUE;
	}

	pcnAddr = (union io_pwm_pcn*) &IO_PERI.PWM[blk].PCNE;
	if ((pcnAddr->bit.__IREN == 1) && (pcnAddr->bit.__IRQF == 1)){
		return TRUE;
	}

	return FALSE;
}

/*
 * @brief  It is Interrupt Handler of PWM.
 * @param  void
 * @return void
 */
void dd_pwm_branch_int_handler(DdPwmBranch* self, kuint32 ch)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
	kuint32 chFlg[4] = {0,0,0,0};
	int i, chMax = DdPwmBranch_CH_NUM_MAX;
	volatile union io_pwm_pcn* pcnAddr;
	union io_pwm_pcn pcnTmp;
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return;
	}
#endif

	if (IO_PERI.PWM[blk].PCNA.bit.__IRQF == 1){
		chMax = ch;
		chFlg[0] = 1;
	}
	if (IO_PERI.PWM[blk].PCNB.bit.__IRQF == 1){
		chMax = ch + 1;
		chFlg[1] = 1;
	}
	if (IO_PERI.PWM[blk].PCNC.bit.__IRQF == 1){
		chMax = ch + 2;
		chFlg[2] = 1;
	}
	if (IO_PERI.PWM[blk].PCND.bit.__IRQF == 1){
		chMax = ch + 3;
		chFlg[3] = 1;
	}
	if (IO_PERI.PWM[blk].PCNE.bit.__IRQF == 1){
		chMax = ch;
		chFlg[0] = 1;
	}

//	printf("Dd_PWM_Int_Handler ch= %d \n", ch);
//
//	if(ch==4){
////		FJ_Gpio_Set_Status(FJ_GPIO_PF2, 1);
//		Dd_Top_Set_Gpio_Status(E_DD_TOP_GPIO_PF2, 1);
//	}

	if(chMax == DdPwmBranch_CH_NUM_MAX) {
		return;
	}
	for (i = 0; i < 4; i++){
		if (chFlg[i] == 1) {
			pcnAddr = dd_pwm_branch_get_func_pcn_addr(self, ch);

			if ((pcnAddr->bit.__IREN == 1) && (pcnAddr->bit.__IRQF == 1)){
				// Clear interrupt flag
				pcnTmp.word = pcnAddr->word;
				pcnTmp.bit.__IRQF = 0;
				pcnAddr->word = pcnTmp.word;
				DdPwmBranch_DD_PWM_DSB();

				if (priv->gDdPwmCtrl[ch].pCallback) {
					// Call Back function
					(*priv->gDdPwmCtrl[ch].pCallback)(ch, pcnAddr->bit.__IRS);
				}
			}
			pcnAddr = (union io_pwm_pcn*) &IO_PERI.PWM[blk].PCNE;
			if ((pcnAddr->bit.__IREN == 1) && (pcnAddr->bit.__IRQF == 1)){
				// Clear interrupt flag
				pcnTmp.word = pcnAddr->word;
				pcnTmp.bit.__IRQF = 0;
				pcnAddr->word = pcnTmp.word;
				DdPwmBranch_DD_PWM_DSB();

				if (priv->gDdPwmCtrl[ch].pCallback) {
					(*priv->gDdPwmCtrl[ch].pCallback)(ch, pcnAddr->bit.__IRS);
				}
			}
		}
		ch++;
		if (ch > chMax) {
			break;
		}
	}

//	if(ch==4){
////		FJ_Gpio_Set_Status(FJ_GPIO_PF2, 0);
//		Dd_Top_Set_Gpio_Status(E_DD_TOP_GPIO_PF2, 0);
//	}
}

/*
 * @brief  It is Interrupt Handler of PWM_STP.
 * @param  void
 * @return void
 */
void dd_pwm_branch_int_handler_stp(DdPwmBranch* self, kuint32 ch)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;
	kushort pintctTemp;
	kint32	ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return;
	}
#endif
	if (IO_PERI.PWM[blk].PINTCT0.word == 0x0000){
		return;
	}

	if (priv->gDdPwmCtrl[ch].dmaEnable){
		ret = Dd_HDMAC0_Stop(priv->gDdPwmCtrl[ch].dmaCh);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Dd_HDMAC0_Stop Error: %d\n", ret));
		}
		ret = Dd_HDMAC0_Close(priv->gDdPwmCtrl[ch].dmaCh);
		if (ret != D_DDIM_OK){
			Ddim_Print(("Dd_HDMAC0_Close Error: %d\n", ret));
		}
		priv->gDdPwmCtrl[ch].dmaEnable = 0;
	}

	if ((IO_PERI.PWM[blk].PINTCT0.bit.__UIE == 1) && (IO_PERI.PWM[blk].PINTCT0.bit.__UIS == 1)){
		if (priv->gDdPwmCtrl[ch].pCallback) {
			(*priv->gDdPwmCtrl[ch].pCallback)(ch, DdPwmBranch_INT_STATUS_UNDER_RUN);
		}
	}
	if ((IO_PERI.PWM[blk].PINTCT0.bit.__FIE == 1) && (IO_PERI.PWM[blk].PINTCT0.bit.__FIS == 1)){
		if (priv->gDdPwmCtrl[ch].pCallback) {
			(*priv->gDdPwmCtrl[ch].pCallback)(ch, DdPwmBranch_INT_STATUS_FORCE_STOP);
		}
	}
	if ((IO_PERI.PWM[blk].PINTCT0.bit.__AIE == 1) && (IO_PERI.PWM[blk].PINTCT0.bit.__AIS == 1)){
		if (priv->gDdPwmCtrl[ch].pCallback) {
			(*priv->gDdPwmCtrl[ch].pCallback)(ch, DdPwmBranch_INT_STATUS_AUTO_STOP);
		}
	}
	// clear UIS, FIS, AIS
	pintctTemp = IO_PERI.PWM[blk].PINTCT0.word;
	IO_PERI.PWM[blk].PINTCT0.word = pintctTemp;
	DdPwmBranch_DD_PWM_DSB();
}

/*
 * @brief  The Mask status is set. Only when the corresponding timer ABCD.
 * @param  kuint32 ch, kushort mask
 * @return kint32 D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_branch_set_stopped_output_mask(DdPwmBranch* self, kuint32 ch, kuchar mask)
{
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	switch ((DdPwmBranch_CH_NUM_IN_BLOCK - 1) & ch) {
		case 0:
			IO_PERI.PWM[blk].GCN2.bit.MSK0 = mask;
			break;

		case 1:
			IO_PERI.PWM[blk].GCN2.bit.MSK1 = mask;
			break;

		case 2:
			IO_PERI.PWM[blk].GCN2.bit.MSK2 = mask;
			break;

		case 3:
			IO_PERI.PWM[blk].GCN2.bit.MSK3 = mask;
			break;

		default:
			return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	DdPwmBranch_DD_PWM_DSB();

	return D_DDIM_OK;
}

/*
 * @brief  Get setting value of the mask. Only when the corresponding timer ABCD.
 * @param  kuint32 ch, kushort mask
 * @return kint32 D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_branch_get_stopped_output_mask(DdPwmBranch* self, kuint32 ch, kuchar* mask)
{
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	if (0 == mask) {
		Ddim_Assertion(("PWM input param error. [mask] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	switch ((DdPwmBranch_CH_NUM_IN_BLOCK - 1) & ch) {
		case 0:
			*mask = IO_PERI.PWM[blk].GCN2.bit.MSK0;
			break;

		case 1:
			*mask = IO_PERI.PWM[blk].GCN2.bit.MSK1;
			break;

		case 2:
			*mask = IO_PERI.PWM[blk].GCN2.bit.MSK2;
			break;

		case 3:
			*mask = IO_PERI.PWM[blk].GCN2.bit.MSK3;
			break;

		default:
			return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}

/*
 * @brief  Get setting value of conter clock of TimerE
 * @param  kuint32 ch, kuchar clock
 * @return kint32 D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_branch_get_clock_sel_timer_e(DdPwmBranch* self, kuint32 ch, kuchar* clock)
{
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	switch ((DdPwmBranch_CH_NUM_IN_BLOCK - 1) & ch) {
		case 0:
			*clock = IO_PERI.PWM[blk].PCNE.bit.__CKS;
			break;

		case 1:
			*clock = IO_PERI.PWM[blk].PCNE.bit.__CKS;
			break;

		case 2:
			*clock = IO_PERI.PWM[blk].PCNE.bit.__CKS;
			break;

		case 3:
			*clock = IO_PERI.PWM[blk].PCNE.bit.__CKS;
			break;

		default:
			return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}

/*
 * @brief  Get the output state of the stopped.
 * @param  kuint32 ch, kulong* chStatus
 * @return kint32 D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_branch_get_stopped_output_status(DdPwmBranch* self, kuint32 ch, kuchar* chStatus)
{
	/* ch / D_DD_PWM_CH_NUM_IN_BLOCK */
	const kuint32 blk = ch >> 2;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	if (0 == chStatus) {
		Ddim_Assertion(("PWM input param error. [chStatus] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	switch (ch & 0x03) {
		case 0:
			*chStatus = IO_PERI.PWM[blk].PCHSET0.bit.OSTA0;
			break;

		case 1:
			*chStatus = IO_PERI.PWM[blk].PCHSET0.bit.OSTA1;
			break;

		case 2:
			*chStatus = IO_PERI.PWM[blk].PCHSET0.bit.OSTA2;
			break;

		case 3:
			*chStatus = IO_PERI.PWM[blk].PCHSET0.bit.OSTA3;
			break;

		default:
			return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}

volatile union io_pwm_pcn* dd_pwm_branch_get_func_pcn_addr(DdPwmBranch* self, kuint32 ch)
{
	return ddPwmPcnAddr(self, ch);
}

DdPwmCtrlMemo dd_pwm_branch_get_ctrl_memo(DdPwmBranch* self, kuint32 ch)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
	return priv->gDdPwmCtrl[ch];
}

void dd_pwm_branch_set_clk_sel(DdPwmBranch* self, kuint32 ch, kuchar clkSel)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
	priv->gDdPwmCtrl[ch].clkSel = clkSel;
}

void dd_pwm_branch_set_int_enable(DdPwmBranch* self, kuint32 ch, kuchar intEnable)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
	priv->gDdPwmCtrl[ch].intEnable = intEnable;
}

void dd_pwm_branch_set_p_callback(DdPwmBranch* self, kuint32 ch, VpCallbackPwm pCallback)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
	priv->gDdPwmCtrl[ch].pCallback = pCallback;
}

void dd_pwm_branch_set_cyc_num(DdPwmBranch* self, kuint32 ch, kushort cycNum)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
	priv->gDdPwmCtrl[ch].cycNum = cycNum;
}

void dd_pwm_branch_set_duty_num(DdPwmBranch* self, kuint32 ch, kushort dutyNum)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
	priv->gDdPwmCtrl[ch].dutyNum = dutyNum;
}

void dd_pwm_branch_set_dma_enable(DdPwmBranch* self, kuint32 ch, kuchar dmaEnable)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
	priv->gDdPwmCtrl[ch].dmaEnable	 = dmaEnable;
}

void dd_pwm_branch_set_dma_ch(DdPwmBranch* self, kuint32 ch, kuchar dmaCh)
{
	DdPwmBranchPrivate *priv = DD_PWM_BRANCH_GET_PRIVATE(self);
	priv->gDdPwmCtrl[ch].dmaCh = dmaCh;
}

DdPwmBranch* dd_pwm_branch_new(void)
{
	DdPwmBranch* self = k_object_new_with_private(DD_TYPE_PWM_BRANCH, sizeof(DdPwmBranchPrivate));
	return self;
}
