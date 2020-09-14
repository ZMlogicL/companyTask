/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月5日
 * @author            :冯黎阳
 * @brief             :
 * @rely              :klib
 * @function
 * @version
 *
 */

#include <string.h>
#include "pdm.h"
#include "ddarm.h"
#include "ddtop.h"
#include "ddimusercustom.h"
#include "ddpdm.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdPdm, dd_pdm);
#define DD_PDM_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdPdmPrivate, DD_TYPE_PDM))

#define DdPdm_WAIT_USEC(usec)	Dd_ARM_Wait_ns((usec * 1000))


struct _DdPdmPrivate
{
	volatile DdPdmFunc dma0CallbackFunc[DdPdm_CH_NUM_MAX];
	volatile DdPdmFunc dma1CallbackFunc[DdPdm_CH_NUM_MAX];
	volatile DdPdmFunc overFlowCallbackFunc[DdPdm_CH_NUM_MAX];
};

// Spin Lock
static kulong S_DD_PDM_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64))) = 0;


static void ddPdmSetPdmxck(kuint8 ch, kuint8 val);
static kint32 ddPdmSetPcmClk(void);


static void dd_pdm_constructor(DdPdm *self)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdPdm_CH_NUM_MAX; i++)
	{
		priv->dma0CallbackFunc[i] = NULL;
		priv->dma1CallbackFunc[i] = NULL;
		priv->overFlowCallbackFunc[i] = NULL;
	}
}

static void dd_pdm_destructor(DdPdm *self)
{

}

/**
 * @brief  Set register PDMxCK.
 * @param  kuint8 ch
 * @param  kuint8 val[1:stop/0:supply]
 */
static void ddPdmSetPdmxck(kuint8 ch, kuint8 val)
{
	// SpinLock
	Dd_ARM_Critical_Section_Start(S_DD_PDM_SPIN_LOCK);
	
	switch (ch){
		case DdPdm_CH0 :
			Dd_Top_Set_CLKSTOP3_PDM0CK(val);
			break;
		case DdPdm_CH1 :
			Dd_Top_Set_CLKSTOP3_PDM1CK(val);
			break;
		default :
			break;
	}
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(S_DD_PDM_SPIN_LOCK);
}

/**
 * @brief  Set PDM_CLK.
 * @param  AudioMasterClock mclk
 * @return kint32 D_DDIM_OK/DdPdm_SYSTEM_ERROR
 */
static kint32 ddPdmSetPcmClk(void)
{
	if (Dd_Top_Get_PLLCNT1_PL10ST() == 0){
		Ddim_Print(("[DD_PDM]dd_pdm_set_masterclock:PLL10 is not started. \n"));
		return DdPdm_SYSTEM_ERROR;
	}
	
	if (Dd_Top_Get_PLLCNT1_PL10AST() == 0){
		Dd_Top_Stop_Pll10A();
		DdPdm_WAIT_USEC(6);			// wait 6us
		Dd_Top_Set_PLLCNT9_P10APLLDIV(0);
		Dd_Top_Start_Pll10A();
	}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	else {
		if (Dd_Top_Get_PLLCNT9_P10APLLDIV() != 0){
			Ddim_Print(("[DD_PDM]dd_pdm_set_masterclock:P10APLLDIV != 0. \n"));
			return DdPdm_SYSTEM_ERROR;
		}
	}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	
	return D_DDIM_OK;
}

/**
 * @brief  The input channel is exclusively controlled.
 * @param  kuint8 ch
 * @param  kint32 tmout
 * @return kint32 D_DDIM_OK/DdPdm_SEM_NG/DdPdm_INPUT_PARAM_ERROR/DdPdm_SEM_TIMEOUT
 */
kint32 dd_pdm_open(DdPdm *self, kuint8 ch, kint32 tmout)
{
	DdimUserCustom_ER ercd;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Open:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (tmout < DdimUserCustom_SEM_WAIT_FEVR){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Open:input timeout error : %d\n", tmout));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	// Exclusive check
	if (tmout == DdimUserCustom_SEM_WAIT_POL){
		ercd = DDIM_User_Pol_Sem(SID_DD_PDM(ch));							// pol_sem()
	}
	else {
		ercd = DDIM_User_Twai_Sem(SID_DD_PDM(ch), (DdimUserCustom_TMO)tmout);	// twai_sem()
	}
	
	switch (ercd){
		case DdimUserCustom_E_OK:
			return D_DDIM_OK;
		case DdimUserCustom_E_TMOUT:
			return DdPdm_SEM_TIMEOUT;
		default:
			return DdPdm_SEM_NG;
	}
}

/**
 * @brief  The exclusive control of control Input Channel it is released.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdPdm_SEM_NG/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_close(DdPdm *self, kuint8 ch)
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Close:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// Exclusive release
	ercd = DDIM_User_Sig_Sem(SID_DD_PDM(ch));					// sig_sem()
	if (ercd == DdimUserCustom_E_OK){
		return D_DDIM_OK;
	}
	else {
		return DdPdm_SEM_NG;
	}
}

/**
 * @brief  PDM DMA0 interrupt handler
 * @param  kuint8 ch
 */
void dd_pdm_dma0_int_handler(DdPdm *self, kuint8 ch)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Dma0_Int_Handler:input channel error : %d\n", ch));
		return ;
	}
#endif	// CO_PARAM_CHECK
	
	ioPdm[ch].dmaCfg.bit.clrIrqDma0 = 0;
	Dd_ARM_Dsb_Pou();
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(S_DD_PDM_SPIN_LOCK);
	
	if (priv->dma0CallbackFunc[ch] != NULL){
		priv->dma0CallbackFunc[ch](self);
	}
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(S_DD_PDM_SPIN_LOCK);
	
	ioPdm[ch].dmaCfg.bit.clrIrqDma0 = 1;
}

/**
 * @brief  PDM DMA1 interrupt handler
 * @param  kuint8 ch
 */
void dd_pdm_dma1_int_handler(DdPdm *self, kuint8 ch)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Dma1_Int_Handler:input channel error : %d\n", ch));
		return ;
	}
#endif	// CO_PARAM_CHECK
	
	ioPdm[ch].dmaCfg.bit.clrIrqDma1 = 0;
	Dd_ARM_Dsb_Pou();
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(S_DD_PDM_SPIN_LOCK);
	
	if (priv->dma1CallbackFunc[ch] != NULL){
		priv->dma1CallbackFunc[ch](self);
	}
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(S_DD_PDM_SPIN_LOCK);
	
	ioPdm[ch].dmaCfg.bit.clrIrqDma1 = 1;
}

/**
 * @brief  OverFlow interrupt handler
 * @param  kuint8 ch
 */
void dd_pdm_overflow_int_handler(DdPdm *self, kuint8 ch)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_OverFlow_Int_Handler:input channel error : %d\n", ch));
		return ;
	}
#endif	// CO_PARAM_CHECK
	
	ioPdm[ch].dmaCfg.bit.clrIrqFfovf = 0;
	Dd_ARM_Dsb_Pou();
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(S_DD_PDM_SPIN_LOCK);
	
	if (priv->overFlowCallbackFunc[ch] != NULL){
		priv->overFlowCallbackFunc[ch](self);
	}
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(S_DD_PDM_SPIN_LOCK);
	
	ioPdm[ch].dmaCfg.bit.clrIrqFfovf = 1;
}

/**
 * @brief  Initialized PDM Macro Setting
 */
kint32 dd_pdm_init(DdPdm *self)
{
	kint32 ret;
	volatile IoPdmDmacfg pdmdmacfg;
	
	ddPdmSetPdmxck(DdPdm_CH0, 1);
	ddPdmSetPdmxck(DdPdm_CH1, 1);
	Dd_ARM_Dsb_Pou();
	
	// Init Register.
	ioPdm[DdPdm_CH0].coreCfg.bit.pdmcoreEn = DdPdm_DISABLE;
	ioPdm[DdPdm_CH1].coreCfg.bit.pdmcoreEn = DdPdm_DISABLE;
	
	pdmdmacfg.word = ioPdm[DdPdm_CH0].dmaCfg.word;
	pdmdmacfg.bit.dmaEn = DdPdm_DISABLE;
	pdmdmacfg.bit.clrIrqFfovf = 0;
	pdmdmacfg.bit.clrIrqDma1 = 0;
	pdmdmacfg.bit.clrIrqDma0 = 0;
	pdmdmacfg.bit.pcmChset = 3;
	ioPdm[DdPdm_CH0].dmaCfg.word = pdmdmacfg.word;
	
	pdmdmacfg.word = ioPdm[DdPdm_CH1].dmaCfg.word;
	pdmdmacfg.bit.dmaEn = DdPdm_DISABLE;
	pdmdmacfg.bit.clrIrqFfovf = 0;
	pdmdmacfg.bit.clrIrqDma1 = 0;
	pdmdmacfg.bit.clrIrqDma0 = 0;
	pdmdmacfg.bit.pcmChset = 3;
	ioPdm[DdPdm_CH1].dmaCfg.word = pdmdmacfg.word;
	Dd_ARM_Dsb_Pou();
	
	ret = ddPdmSetPcmClk();
	if (ret != D_DDIM_OK){
		return ret;
	}
	
	ddPdmSetPdmxck(DdPdm_CH0, 0);
	ddPdmSetPdmxck(DdPdm_CH1, 0);
	
	(void)dd_pdm_clear_status(self, DdPdm_CH0, DdPdm_INT_TYPE_DMA0);
	(void)dd_pdm_clear_status(self, DdPdm_CH1, DdPdm_INT_TYPE_DMA0);
	(void)dd_pdm_clear_status(self, DdPdm_CH0, DdPdm_INT_TYPE_DMA1);
	(void)dd_pdm_clear_status(self, DdPdm_CH1, DdPdm_INT_TYPE_DMA1);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set Core Control Information
 * @param  kuint8 ch
 * @param  DdPdmCoreCfg *coreCfg
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_ctrl_core(DdPdm *self, kuint8 ch, DdPdmCoreCfg* coreCfg)
{
	volatile IoPdmCorecfg pdmcorecfg;
	kint32 ret = D_DDIM_OK;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Ctrl_Core:input channel error : %d\n", ch));
		
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (coreCfg == NULL){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Ctrl_Core:ctrl_inf = NULL\n"));
		
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	pdmcorecfg.word = ioPdm[ch].coreCfg.word;
	
	// LRSWAP
	if (coreCfg->swap <= DdPdm_CORE_LR_SWAP_SWAP){
		pdmcorecfg.bit.lrswap = (kulong)coreCfg->swap;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:LRSWAP is out of range. swap = %d\n", (int)coreCfg->swap));
	}
	
	// PGA_R
	if (coreCfg->pgaR <= DdPdm_CORE_PGA_M_1_5_DB){
		pdmcorecfg.bit.pgaR = (kulong)coreCfg->pgaR;
		
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:PGA_R is out of range. pgaR = %d\n", (int)coreCfg->pgaR));
	}
	
	// PGA_L
	if (coreCfg->pgaL <= DdPdm_CORE_PGA_M_1_5_DB){
		pdmcorecfg.bit.pgaL = (kulong)coreCfg->pgaL;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:PGA_L out of range. pgaL = %d\n", (int)coreCfg->pgaL));
	}
	
	// MCLKDIV
	if ((1 < coreCfg->mclkDiv)	&&
		(coreCfg->mclkDiv <= 12)	){
		pdmcorecfg.bit.mclkdiv = (kulong)coreCfg->mclkDiv;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:MCLKDIV is out of range. mclkDiv = %d\n", (int)coreCfg->mclkDiv));
	}
	
	// sincRate
	if ((16 <= coreCfg->sincRate)	&&
		(coreCfg->sincRate < 64)	){
		pdmcorecfg.bit.sincRate = (kulong)coreCfg->sincRate;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:sincRate is out of range. sincRate = %d\n", (int)coreCfg->sincRate));
	}
	
	// adchpd
	if (coreCfg->adcHpd == DdPdm_ENABLE){
		pdmcorecfg.bit.adchpd = 0;
	}
	else if (coreCfg->adcHpd == DdPdm_DISABLE){
		//pdmcorecfg.bit.adchpd = 1;
		pdmcorecfg.bit.adchpd = 0; // from other project, always enable to avoid Audio Pop Up Noise.
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:adchpd is out of range. adcHpd = %d\n", (int)coreCfg->adcHpd));
	}
	
	// hpcutoff
	pdmcorecfg.bit.hpcutoff = coreCfg->hpCutoff;
	
	// sCycles
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	if (coreCfg->sCycle <= DdPdm_CORE_S_CYCLE_1333US){
		pdmcorecfg.bit.sCycles = (kulong)coreCfg->sCycle;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:sCycles is out of range. sCycle = %d\n", (int)coreCfg->sCycle));
	}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	if (coreCfg->sCycle <= DdPdm_CORE_S_CYCLE_7){
		pdmcorecfg.bit.sCycles = (kulong)coreCfg->sCycle;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:sCycles is out of range. sCycle = %d\n", (int)coreCfg->sCycle));
	}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	
	// SOFT_MUTE
	if (coreCfg->softMute <= DdPdm_ENABLE){
		pdmcorecfg.bit.softMute = (kulong)coreCfg->softMute;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:SOFT_MUTE is out of range. softMute = %d\n", (int)coreCfg->softMute));
	}
	
	ioPdm[ch].coreCfg.word = pdmcorecfg.word;
	
	return ret;
}

/**
 * @brief  Get Core Control Information
 * @param  kuint8 ch
 * @param  DdPdmCoreCfg *coreCfg
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_get_ctrl_core(DdPdm *self, kuint8 ch, DdPdmCoreCfg* coreCfg)
{
	volatile IoPdmCorecfg pdmcorecfg;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Get_Ctrl_Core:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (coreCfg == NULL){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Get_Ctrl_Core:ctrl_inf = NULL\n"));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	pdmcorecfg.word = ioPdm[ch].coreCfg.word;
	
	coreCfg->swap = (PdmCoreLrSwap)pdmcorecfg.bit.lrswap;			/* pgr0872 */
	coreCfg->pgaR = (PdmCorePga)pdmcorecfg.bit.pgaR;				/* pgr0872 */
	coreCfg->pgaL = (PdmCorePga)pdmcorecfg.bit.pgaL;				/* pgr0872 */
	coreCfg->mclkDiv = pdmcorecfg.bit.mclkdiv;								/* pgr0872 */
	coreCfg->sincRate = pdmcorecfg.bit.sincRate;								/* pgr0872 */
	
	// adchpd
	if (pdmcorecfg.bit.adchpd == 0){											/* pgr0872 */
		coreCfg->adcHpd = DdPdm_ENABLE;
	}
	else {
		coreCfg->adcHpd = DdPdm_DISABLE;
	}
	
	coreCfg->hpCutoff = pdmcorecfg.bit.hpcutoff;								/* pgr0872 */
	coreCfg->sCycle = (PdmCoreSCycle)pdmcorecfg.bit.sCycles;		/* pgr0872 */
	coreCfg->softMute = pdmcorecfg.bit.softMute;								/* pgr0872 */
	
	return D_DDIM_OK;
}

/**
 * @brief  Start Data Streaming
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_start_streaming(DdPdm *self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Start_Streaming:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	ioPdm[ch].coreCfg.bit.pdmcoreEn = DdPdm_ENABLE;
	
	return D_DDIM_OK;
}

/**
 * @brief  Stop Data Streaming
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_stop_streaming(DdPdm *self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Start_Streaming:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	ioPdm[ch].coreCfg.bit.pdmcoreEn = DdPdm_DISABLE;
	
	return D_DDIM_OK;
}

/**
 * @brief  Set DMA Control Information
 * @param  kuint8 ch
 * @param  DdPdmDmaCfg *dmaCfg
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_ctrl_dma(DdPdm *self, kuint8 ch, DdPdmDmaCfg* dmaCfg)
{
	volatile IoPdmDmacfg pdmdmacfg;
	kint32 ret = D_DDIM_OK;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Ctrl_Dma:input channel error : %d\n", ch));
		
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (dmaCfg == NULL){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Ctrl_Dma:dmaCfg = NULL\n"));
		
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	pdmdmacfg.word = ioPdm[ch].dmaCfg.word;
	
	// dmickDly
	if (dmaCfg->dmickDly <= 3){
		pdmdmacfg.bit.dmickDly = dmaCfg->dmickDly;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Dma:dmickDly is out of range. dmickDly = %d\n", (int)dmaCfg->dmickDly));
	}
	
	// dmaBurstlen
	if (dmaCfg->dmaBurstlen <= DdPdm_DMA_BURST_LEN_16){
		pdmdmacfg.bit.dmaBurstlen = (kulong)dmaCfg->dmaBurstlen;
		
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Dma:dmaBurstlen is out of range. dmaBurstlen = %d\n",
				(int)dmaCfg->dmaBurstlen));
	}
	
	// pcmChset
	if (dmaCfg->pcmChset <= DdPdm_DMA_PCM_CH_STEREO){
		pdmdmacfg.bit.pcmChset = (kulong)dmaCfg->pcmChset;
		
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Dma:pcmChset is out of range. pcmChset = %d\n", (int)dmaCfg->pcmChset));
	}
	
	// pcmWdlen
	if (dmaCfg->pcmWdlen <= DdPdm_DMA_PCM_WD_24){
		pdmdmacfg.bit.pcmWdlen = (kulong)dmaCfg->pcmWdlen;
		
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Dma:pcmWdlen is out of range. pcmWdlen = %d\n", (int)dmaCfg->pcmWdlen));
	}
	
	// DMA_EN
	if (dmaCfg->dmaEn <= DdPdm_ENABLE){
		pdmdmacfg.bit.dmaEn = dmaCfg->dmaEn;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Dma:DMA_EN is out of range. dmaEn = %d\n", (int)dmaCfg->dmaEn));
	}
	
	ioPdm[ch].dmaCfg.word = pdmdmacfg.word;
	
	return ret;
}

/**
 * @brief  Get DMA Control Information
 * @param  kuint8 ch
 * @param  DdPdmDmaCfg *dmaCfg
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_get_ctrl_dma(DdPdm *self, kuint8 ch, DdPdmDmaCfg* dmaCfg)
{
	volatile IoPdmDmacfg pdmdmacfg;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Get_Ctrl_Dma:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (dmaCfg == NULL){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Get_Ctrl_Dma:dmaCfg = NULL\n"));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	pdmdmacfg.word = ioPdm[ch].dmaCfg.word;
	
	dmaCfg->dmickDly = pdmdmacfg.bit.dmickDly;									/* pgr0872 */
	dmaCfg->dmaBurstlen = (PdmDmaBurstLen)pdmdmacfg.bit.dmaBurstlen;		/* pgr0872 */
	dmaCfg->pcmChset = (PdmDmaPcmCh)pdmdmacfg.bit.pcmChset;				/* pgr0872 */
	dmaCfg->pcmWdlen = (PdmDmaPcmWd)pdmdmacfg.bit.pcmWdlen;				/* pgr0872 */
	dmaCfg->dmaEn = pdmdmacfg.bit.dmaEn;										/* pgr0872 */

	return D_DDIM_OK;
}

/**
 * @brief  Set callback function of Dma0 Interrupt
 * @param  kuint8 ch
 * @param  DdPdmFunc callback
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_set_callback_dma0_intr(DdPdm *self, kuint8 ch, DdPdmFunc callback)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_CallbackDma0Intr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(S_DD_PDM_SPIN_LOCK);
	
	priv->dma0CallbackFunc[ch] = callback;
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(S_DD_PDM_SPIN_LOCK);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set enable/disable Dma0 Interrupt
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_set_enable_dma0_intr(DdPdm *self, kuint8 ch, kuint8 enable)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_EnableDma0Intr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (enable > DdPdm_ENABLE){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_EnableDma0Intr:input enable error : %d\n", enable));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	if (enable == DdPdm_ENABLE){
		ioPdm[ch].dmaCfg.bit.clrIrqDma0 = 0;
	}
	else {
		ioPdm[ch].dmaCfg.bit.clrIrqDma0 = 1;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Set callback function of Dma1 Interrupt
 * @param  kuint8 ch
 * @param  DdPdmFunc callback
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_set_callback_dma1_intr(DdPdm *self, kuint8 ch, DdPdmFunc callback)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_CallbackDma1Intr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(S_DD_PDM_SPIN_LOCK);
	
	priv->dma1CallbackFunc[ch] = callback;
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(S_DD_PDM_SPIN_LOCK);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set enable/disable Dma1 Interrupt
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_set_enable_dma1_intr(DdPdm *self, kuint8 ch, kuint8 enable)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_EanbleDma1Intr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (enable > DdPdm_ENABLE){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_EanbleDma1Intr:input enable error : %d\n", enable));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	if (enable == DdPdm_ENABLE){
		ioPdm[ch].dmaCfg.bit.clrIrqDma1 = 0;
	}
	else {
		ioPdm[ch].dmaCfg.bit.clrIrqDma1 = 1;
		priv->dma1CallbackFunc[ch] = NULL;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Set callback function of OverFlow Interrupt
 * @param  kuint8 ch
 * @param  DdPdmFunc callback
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_set_callback_over_flow_intr(DdPdm *self, kuint8 ch, DdPdmFunc callback)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_CallbackOverFlowIntr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(S_DD_PDM_SPIN_LOCK);
	
	priv->overFlowCallbackFunc[ch] = callback;
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(S_DD_PDM_SPIN_LOCK);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set enable/disable OverFlow Interrupt
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_set_enable_over_flow_intr(DdPdm *self, kuint8 ch, kuint8 enable)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_EnableOverFlowIntr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (enable > DdPdm_ENABLE){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_EnableOverFlowIntr:input enable error : %d\n", enable));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	if (enable == DdPdm_ENABLE){
		ioPdm[ch].dmaCfg.bit.clrIrqFfovf = 0;
	}
	else {
		ioPdm[ch].dmaCfg.bit.clrIrqFfovf = 1;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Set DMA0 distination address
 * @param  kuint8 ch
 * @param  kuint32 addr
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_set_dma0_dst_addr(DdPdm *self, kuint8 ch, kuint32 addr)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_DMA0_Dst_Addr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	ioPdm[ch].dma0DstAddr.word = (addr & 0xFFFFFFFC);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set DMA1 distination address
 * @param  kuint8 ch
 * @param  kuint32 addr
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_set_dma1_dst_addr(DdPdm *self, kuint8 ch, kuint32 addr)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_DMA1_Dst_Addr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	ioPdm[ch].dma1DstAddr.word = (addr & 0xFFFFFFFC);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set DMA Transfer Length
 * @param  kuint8 ch
 * @param  DdPdmDmaLen* dmaLen
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_set_dma_trans_length(DdPdm *self, kuint8 ch, DdPdmDmaLen* dmaLen)
{
	volatile IoPdmDmalen pdmdmalen;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_Dma_TransLength:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (dmaLen == NULL){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_Dma_TransLength:dmaLen = NULL\n"));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (dmaLen->ttsize > 0x7FFF){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_Dma_TransLength:ttsize is out of range : %d\n", dmaLen->ttsize));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (dmaLen->ttsize == 0x00){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_Dma_TransLength:ttsize is out of range : %d\n", dmaLen->ttsize));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (dmaLen->tsize == 0x00){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_Dma_TransLength:tsize is out of range : %d\n", dmaLen->tsize));
		return DdPdm_INPUT_PARAM_ERROR;
	}

#endif	// CO_PARAM_CHECK
	
	pdmdmalen.bit.dmaTtsize = dmaLen->ttsize;
	pdmdmalen.bit.dmaTsize = dmaLen->tsize;
	
	ioPdm[ch].dmaLen.word = pdmdmalen.word;				/* pgr0872 */
	
	return D_DDIM_OK;
}

/**
 * @brief  Start Dma Transfer
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */

kint32 dd_pdm_flush_dma_fifo(DdPdm *self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Flush_Dma_Fifo:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	// FIFO Flush
	ioPdm[ch].dmaCfg.bit.dmaFlush = 1;
	Dd_ARM_Dsb_Pou();
	ioPdm[ch].dmaCfg.bit.dmaFlush = 0;
	Dd_ARM_Dsb_Pou();
	
	return D_DDIM_OK;
}

/**
 * @brief  Get log of interrupt
 * @param  kuint8 ch
 * @param  DdPdmIntType type
 * @param  kuint8* status
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_get_status(DdPdm *self, kuint8 ch, DdPdmIntType type, kuint8* status)
{
	volatile IoPdmStatus pdmstatus;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Get_Status:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (status == NULL){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Get_Status:input status is NULL\n"));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	pdmstatus.word = ioPdm[ch].status.word;
	
	switch (type) {
		case DdPdm_INT_TYPE_FFOVF:
			*status = pdmstatus.bit.ffovfIntReg;				/* pgr0872 */
			break;
		case DdPdm_INT_TYPE_DMA0:
			*status = pdmstatus.bit.dma0IntReg;				/* pgr0872 */
			break;
		case DdPdm_INT_TYPE_DMA1:
			*status = pdmstatus.bit.dma1IntReg;				/* pgr0872 */
			break;
		default:
#ifdef CO_PARAM_CHECK
			Ddim_Assertion(("[DD_PDM]Dd_Pdm_Get_Status:input type error : %d\n", type));
			return DdPdm_INPUT_PARAM_ERROR;
#endif
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Clear log of interrupt
 * @param  kuint8 ch
 * @param  DdPdmIntType type
 * @return kint32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
kint32 dd_pdm_clear_status(DdPdm *self, kuint8 ch, DdPdmIntType type)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Clear_Status:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	switch (type) {
		case DdPdm_INT_TYPE_FFOVF:
			ioPdm[ch].status.bit.ffovfIntReg = 1;
			break;
		case DdPdm_INT_TYPE_DMA0:
			ioPdm[ch].status.bit.dma0IntReg = 1;
			break;
		case DdPdm_INT_TYPE_DMA1:
			ioPdm[ch].status.bit.dma1IntReg = 1;
			break;
		default:
#ifdef CO_PARAM_CHECK
			Ddim_Assertion(("[DD_PDM]Dd_Pdm_Clear_Status:input type error : %d\n", type));
			return DdPdm_INPUT_PARAM_ERROR;
#endif
	}
	
	return D_DDIM_OK;
}

DdPdm* dd_pdm_get(void)
{
	static DdPdm* self = NULL;

	if(!self)
		self = k_object_new_with_private(DD_TYPE_PDM, sizeof(DdPdmPrivate));

	return self;
}


