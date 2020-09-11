/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :PWM driver(colabo  section)
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

#include "dd_hdmac0.h"

#include "ddpwmcolabo.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdPwmColabo, dd_pwm_colabo);
#define DD_PWM_COLABO_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdPwmColaboPrivate, DD_TYPE_PWM_COLABO))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#ifdef CO_DDIM_UTILITY_USE
#define D_DD_PWM_DMACA_IS_BASE		(D_DD_HDMAC0_IS_IDREQ_25)
#endif	/* CO_DDIM_UTILITY_USE */

typedef struct _DmaSetParam DmaSetParam;

struct _DmaSetParam
{
	kuint32 pwmCh;
	kuchar dmaCh;
	kuchar stepRemainder;
	kulong srcAddr;
	kulong dstAddr;
};

struct _DdPwmColaboPrivate
{
    kint a;
};

/*
 * DECLS
 */
#ifdef CO_DDIM_UTILITY_USE
static kint32 ddPwmDmaSet(DdPwmColabo* self, DmaSetParam dmaSetParam);
#endif	/* CO_DDIM_UTILITY_USE */

static void dd_pwm_colabo_constructor(DdPwmColabo *self)
{
	DdPwmColaboPrivate *priv = DD_PWM_COLABO_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_pwm_colabo_destructor(DdPwmColabo *self)
{

}

/*
 * IMPL
 */
#ifdef CO_DDIM_UTILITY_USE
static kint32 ddPwmDmaSet(DdPwmColabo* self, DmaSetParam dmaSetParam)
{
	kint32 ret;
	T_DD_HDMAC0_CTRL dmaCtrl;

	// Channel open
	ret = Dd_HDMAC0_Open(dmaSetParam.dmaCh, D_DDIM_USER_SEM_WAIT_POL);
	if(ret != D_DDIM_OK){
		Ddim_Print(("Dd_HDMAC0_Open() error. ret=0x%x\n", ret));
		return ret;
	}

	dmaCtrl.config_a.word	 = 0;
	dmaCtrl.config_a.bit.is = D_DD_PWM_DMACA_IS_BASE + (dmaSetParam.pwmCh >> 2);
	dmaCtrl.config_a.bit.bt = D_DD_HDMAC0_BT_NORMAL;
	// cycle, duty, pulse
	dmaCtrl.config_a.bit.bc = 3 - 1;
	dmaCtrl.config_a.bit.tc = dmaSetParam.stepRemainder - 1;

	dmaCtrl.config_b.word	 = 0;
	dmaCtrl.config_b.bit.ms = D_DD_HDMAC0_MS_BLK;
	dmaCtrl.config_b.bit.tw = D_DD_HDMAC0_TW_HWORD;
	dmaCtrl.config_b.bit.fs = D_DD_HDMAC0_FS_INCR;
	dmaCtrl.config_b.bit.fd = D_DD_HDMAC0_FD_FIX;
	dmaCtrl.config_b.bit.rc = D_DD_HDMAC0_RC_DISABLE;
	dmaCtrl.config_b.bit.rs = D_DD_HDMAC0_RS_ENABLE;
	dmaCtrl.config_b.bit.rd = D_DD_HDMAC0_RD_DISABLE;

	dmaCtrl.src_addr = dmaSetParam.srcAddr;
	dmaCtrl.dst_addr = dmaSetParam.dstAddr;
	dmaCtrl.int_handler = NULL;

	ret = Dd_HDMAC0_Ctrl_Common(dmaSetParam.dmaCh, &dmaCtrl);
	if(ret != D_DDIM_OK){
		Dd_HDMAC0_Close(dmaSetParam.dmaCh);
		Ddim_Print(("Dd_HDMAC0_Ctrl_Common() error. ret=0x%x\n", ret));
		return ret;
	}

	ret = Dd_HDMAC0_Start_Async(dmaSetParam.dmaCh);
	if(ret != D_DDIM_OK){
		Dd_HDMAC0_Close(dmaSetParam.dmaCh);
		Ddim_Print(("Dd_HDMAC0_Start_Async() error. ret=0x%x\n", ret));
		return ret;
	}
	return ret;
}
#endif	/* CO_DDIM_UTILITY_USE */

/*
 * PUBLIC
 */
#ifdef CO_DDIM_UTILITY_USE
/*
 * The PWM Timer E and DMA is set for stepping motor.
 */
kint32 dd_pwm_colabo_write_step(DdPwmColabo* self, kuint32 pwmCh, kuint32 dmaCh,
		TDdPwmStep const* const pwmStep)
{
	DmaSetParam dmaSetParam;
	kint32 ret;
	kuchar chInBlk;
	kuchar step;
	kuchar index;
	kuchar stepRemainder;
	DdPwmCtrlCmn ctrlCmn;
	PwmCtrlTimerE ctrlE;
	PwmTimerEstepsData* wStepData;
	PwmTimerEstepsData* wUnderRunData;

#ifdef CO_PARAM_CHECK
	if ((pwmCh != 0) && (pwmCh != 4) && (pwmCh != 8) && (pwmCh != 12)) {
		Ddim_Assertion(("PWM input param error. [pwmCh] = %d\n", pwmCh));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if(dmaCh >= D_DD_HDMAC0_CH_NUM_MAX){
		Ddim_Assertion(("PWM input param error. [dmaCh] = %x\n", dmaCh));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (0 == pwmStep) {
		Ddim_Assertion(("PWM input param error. [pwmStep] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	wStepData = pwmStep->stepData;
	wUnderRunData = pwmStep->underRunData;

//	ch_in_blk = (D_DD_PWM_CH_NUM_IN_BLOCK - 1) & pwmCh;
	chInBlk = DdPwmBranch_GCN_TSEL_TIM0;

	// Set PWM Control Common Data
	// clock select
	ctrlCmn.clkSel = pwmStep->clkSel;
	// output polarity
	ctrlCmn.polarity = pwmStep->polarity;
	// channel assignment
	ctrlCmn.chAssign = pwmStep->chAssign;
	// trigger input factor
	ctrlCmn.inTrigger = chInBlk;
	// PWM or One-Shot operation
	ctrlCmn.drvMode = DdPwmBranch_PCNHL_MDSE_PWM;
	// edge enable select
	ctrlCmn.edge = DdPwmBranch_PCNHL_EGS_RISE;
	// restart enable
	ctrlCmn.restartTrig = pwmStep->restartTrig;
	// output level mask
	ctrlCmn.outMask	 = DdPwmBranch_PCNHL_PGMS_L;
	// interrupt enable
	ctrlCmn.intEnable = DdPwmBranch_PCNHL_IREN_OFF;
	// interrupt factor (don't care)
	ctrlCmn.trigger = DdPwmBranch_PCNHL_IRS_TRG;
	// Timer E disable
	ctrlCmn.timEEnable = 1;
	// callback function pointer
	ctrlCmn.pCallback = pwmStep->pCallback;

	// Set PWM Control Timer E Data
	for(index = 0; index < DdPwmBranch_CH_NUM_IN_BLOCK; index++) {
		// hold setting at stop
		ctrlE.hold[index] = pwmStep->hold[index];

		if(pwmStep->force[index] != DdPwmColabo_STEP_FORCE_DISABLE){
			// force enable
			ctrlE.force[index] = 1;
			// force value
			ctrlE.forceVal[index] = pwmStep->force[index];
		}
		else{
			// force disable
			ctrlE.force[index] = 0;
			// force value
			ctrlE.forceVal[index] = 0;
		}
	}

	// interrupt enable under run error
	ctrlE.undrRunIntErrEnable = DdPwmBranch_PINTCT_UIE_ON;
	// interrupt enable for force stop
	ctrlE.forceStopIntEnable = DdPwmBranch_PINTCT_FIE_ON;
	// interrupt enable for auto stop
	ctrlE.autoStopIntEnable = DdPwmBranch_PINTCT_AIE_ON;
	// Inerrupt request timing for DMA
//	ctrlE.emptyDmaReq = D_DD_PWM_PCHSET_RQTIM_4;
	// Inerrupt request timing for DMA
//	ctrlE.emptyDmaReq = D_DD_PWM_PCHSET_RQTIM_6;
	// Inerrupt request timing for DMA
	ctrlE.emptyDmaReq = DdPwmBranch_PCHSET_RQTIM_2;

	// Set PWM Step Data
	for(step = 0; step < DdPwmBranch_TIMER_E_STEPS; step++) {
		if(step < pwmStep->stepDataNum){
			ctrlE.stepsData[step].cycNum = wStepData->cycNum;
			ctrlE.stepsData[step].dutyNum = wStepData->dutyNum;
			ctrlE.stepsData[step].pulseLink.hword = wStepData->pulseLink.hword;
		}
		else{
			ctrlE.stepsData[step].cycNum = 0;
			ctrlE.stepsData[step].dutyNum = 0x0003;
			ctrlE.stepsData[step].pulseLink.hword = 0;
		}
		wStepData++;
	}

	// Set PWM Under run Step Data
	if(pwmStep->undrRunDataNum > 0){
		// speed down setting under run error enable
		ctrlE.undrRunEnable = 1;
		for(step = 0; step < DdPwmBranch_TIMER_E_STEPS_UNDER_RUN; step++) {
			if(step < pwmStep->undrRunDataNum){
				ctrlE.underRunData[step].cycNum = wUnderRunData->cycNum;
				ctrlE.underRunData[step].dutyNum = wUnderRunData->dutyNum;
				ctrlE.underRunData[step].pulseLink.hword = wUnderRunData->pulseLink.hword;
			}
			else{
				ctrlE.underRunData[step].cycNum = 0;
				ctrlE.underRunData[step].dutyNum = 0x0003;
				ctrlE.underRunData[step].pulseLink.hword = 0;
			}
			wUnderRunData++;
		}
	}
	else{
		// speed down setting under run error disable
		ctrlE.undrRunEnable = 0;
	}

	if(pwmStep->stepDataNum > DdPwmBranch_TIMER_E_STEPS){
		// interrupt enable for dma
		ctrlE.dmaIntEnable = DdPwmBranch_PINTCT_DRQE_ON;
		dd_pwm_set_branch_dma_enable(dd_pwm_get(), pwmCh, 1);
		dd_pwm_set_branch_dma_ch(dd_pwm_get(), pwmCh, dmaCh);
		stepRemainder = pwmStep->stepDataNum - DdPwmBranch_TIMER_E_STEPS;

		// cache clean
		DDIM_User_L1l2cache_Clean_Addr((kuint32)wStepData, sizeof(PwmTimerEstepsData) * stepRemainder);

		// Set DMA Transfer
		dmaSetParam.pwmCh = pwmCh;
		dmaSetParam.dmaCh = dmaCh;
		dmaSetParam.stepRemainder = stepRemainder;
		dmaSetParam.srcAddr = (kulong)wStepData;
		dmaSetParam.dstAddr = (kulong)(&(IO_PWMDMA[pwmCh >> 2].BFDTPT));
		ret= ddPwmDmaSet(self, dmaSetParam);
	}
	else{
		// interrupt disable for dma
		ctrlE.dmaIntEnable = DdPwmBranch_PINTCT_DRQE_OFF;
		dd_pwm_set_branch_dma_enable(dd_pwm_get(), pwmCh, 0);
	}

	// Set PWM Control(Common Setting)
	ret = dd_pwm_ctrl_common(dd_pwm_get(), pwmCh, &ctrlCmn);
	if (ret != D_DDIM_OK){
		Ddim_Print(("PWM: common setting error. result = 0x%x\n", ret))
		return ret;
	}

	// Set PWM Control(Timer E Setting)
	ret = dd_pwm_ctrl_timer_e(dd_pwm_get(), pwmCh, &ctrlE);
	if (ret != D_DDIM_OK){
		Ddim_Print(("PWM: timer e setting error. result = 0x%x\n", ret))
		return ret;
	}

	return D_DDIM_OK;
}

/*
 * The PWM Timer E and DMA is set for stepping motor.
 */
kint32 dd_pwm_colabo_write_step_only_buf_data_window(DdPwmColabo* self, kuint32 pwmCh,
		kuint32 dmaCh, PwmTimerEstepsData const* const pwmStep, kuchar dataNum)
{
	DmaSetParam dmaSetParam;
	kint32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((pwmCh != 0) && (pwmCh != 4) && (pwmCh != 8) && (pwmCh != 12)) {
		Ddim_Assertion(("PWM input param error. [pwmCh] = %d\n", pwmCh));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if(dmaCh >= D_DD_HDMAC0_CH_NUM_MAX){
		Ddim_Assertion(("PWM input param error. [dmaCh] = %x\n", dmaCh));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	dd_pwm_set_branch_dma_enable(dd_pwm_get(), pwmCh, 1);
	dd_pwm_set_branch_dma_ch(dd_pwm_get(), pwmCh, dmaCh);

	// cache clean
	DDIM_User_L1l2cache_Clean_Addr((kuint32)pwmStep, sizeof(PwmTimerEstepsData) * dataNum);


	ret = Dd_HDMAC0_Close(dmaCh);

	// Set DMA Transfer
	dmaSetParam.pwmCh = pwmCh;
	dmaSetParam.dmaCh = dmaCh;
	dmaSetParam.stepRemainder = dataNum;
	dmaSetParam.srcAddr = (kulong)pwmStep;
	dmaSetParam.dstAddr = (kulong)(&(IO_PWMDMA[pwmCh >> 2].BFDTPT));
	ret |= ddPwmDmaSet(self, dmaSetParam);

	return ret;
}

#endif	/* CO_DDIM_UTILITY_USE */

DdPwmColabo* dd_pwm_colabo_get(void)
{
	DdPwmColabo *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_PWM_COLABO, sizeof(DdPwmColaboPrivate));
	}

	return self;
}
