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
#include "dd_arm.h"
#include "dd_top.h"
#include "ddim_user_custom.h"
#include "ddpdm.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdPdm, dd_pdm);
#define DD_PDM_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdPdmPrivate, DD_TYPE_PDM))

#define dd_pdm_wait_usec(usec)	Dd_ARM_Wait_ns((usec * 1000))


struct _DdPdmPrivate
{
	volatile DdPdmFunc gDd_Pdm_Dma0_Callback_Func[DdPdm_CH_NUM_MAX];
	volatile DdPdmFunc gDd_Pdm_Dma1_Callback_Func[DdPdm_CH_NUM_MAX];
	volatile DdPdmFunc gDd_Pdm_OverFlow_Callback_Func[DdPdm_CH_NUM_MAX];
};

// Spin Lock
static ULONG gDd_Pdm_Spin_Lock __attribute__((section(".LOCK_SECTION"), aligned(64))) = 0;


static VOID dd_pdm_set_pdmxck(UINT8 ch, UINT8 val);
static INT32 dd_pdm_set_pcm_clk(VOID);


static void dd_pdm_constructor(DdPdm *self)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdPdm_CH_NUM_MAX; i++)
	{
		priv->gDd_Pdm_Dma0_Callback_Func[i] = NULL;
		priv->gDd_Pdm_Dma1_Callback_Func[i] = NULL;
		priv->gDd_Pdm_OverFlow_Callback_Func[i] = NULL;
	}
}

static void dd_pdm_destructor(DdPdm *self)
{

}

/**
 * @brief  Set register PDMxCK.
 * @param  UINT8 ch
 * @param  UINT8 val[1:stop/0:supply]
 */
static VOID dd_pdm_set_pdmxck(UINT8 ch, UINT8 val)
{
	// SpinLock
	Dd_ARM_Critical_Section_Start(gDd_Pdm_Spin_Lock);
	
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
	Dd_ARM_Critical_Section_End(gDd_Pdm_Spin_Lock);
}

/**
 * @brief  Set PDM_CLK.
 * @param  AudioMasterClock mclk
 * @return INT32 D_DDIM_OK/DdPdm_SYSTEM_ERROR
 */
static INT32 dd_pdm_set_pcm_clk(VOID)
{
	if (Dd_Top_Get_PLLCNT1_PL10ST() == 0){
		Ddim_Print(("[DD_PDM]dd_pdm_set_masterclock:PLL10 is not started. \n"));
		return DdPdm_SYSTEM_ERROR;
	}
	
	if (Dd_Top_Get_PLLCNT1_PL10AST() == 0){
		Dd_Top_Stop_Pll10A();
		dd_pdm_wait_usec(6);			// wait 6us
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
 * @param  UINT8 ch
 * @param  INT32 tmout
 * @return INT32 D_DDIM_OK/DdPdm_SEM_NG/DdPdm_INPUT_PARAM_ERROR/DdPdm_SEM_TIMEOUT
 */
INT32 dd_pdm_open(DdPdm *self, UINT8 ch, INT32 tmout)
{
	DDIM_USER_ER ercd;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Open:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (tmout < D_DDIM_USER_SEM_WAIT_FEVR){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Open:input timeout error : %d\n", tmout));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	// Exclusive check
	if (tmout == D_DDIM_USER_SEM_WAIT_POL){
		ercd = DDIM_User_Pol_Sem(SID_DD_PDM(ch));							// pol_sem()
	}
	else {
		ercd = DDIM_User_Twai_Sem(SID_DD_PDM(ch), (DDIM_USER_TMO)tmout);	// twai_sem()
	}
	
	switch (ercd){
		case D_DDIM_USER_E_OK:
			return D_DDIM_OK;
		case D_DDIM_USER_E_TMOUT:
			return DdPdm_SEM_TIMEOUT;
		default:
			return DdPdm_SEM_NG;
	}
}

/**
 * @brief  The exclusive control of control Input Channel it is released.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdPdm_SEM_NG/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_close(DdPdm *self, UINT8 ch)
{
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Close:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// Exclusive release
	ercd = DDIM_User_Sig_Sem(SID_DD_PDM(ch));					// sig_sem()
	if (ercd == D_DDIM_USER_E_OK){
		return D_DDIM_OK;
	}
	else {
		return DdPdm_SEM_NG;
	}
}

/**
 * @brief  PDM DMA0 interrupt handler
 * @param  UINT8 ch
 */
VOID dd_pdm_dma0_int_handler(DdPdm *self, UINT8 ch)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Dma0_Int_Handler:input channel error : %d\n", ch));
		return ;
	}
#endif	// CO_PARAM_CHECK
	
	IO_PDM[ch].DMA_CFG.bit.CLR_IRQ_DMA0 = 0;
	Dd_ARM_Dsb_Pou();
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(gDd_Pdm_Spin_Lock);
	
	if (priv->gDd_Pdm_Dma0_Callback_Func[ch] != NULL){
		priv->gDd_Pdm_Dma0_Callback_Func[ch](self);
	}
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(gDd_Pdm_Spin_Lock);
	
	IO_PDM[ch].DMA_CFG.bit.CLR_IRQ_DMA0 = 1;
}

/**
 * @brief  PDM DMA1 interrupt handler
 * @param  UINT8 ch
 */
VOID dd_pdm_dma1_int_handler(DdPdm *self, UINT8 ch)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Dma1_Int_Handler:input channel error : %d\n", ch));
		return ;
	}
#endif	// CO_PARAM_CHECK
	
	IO_PDM[ch].DMA_CFG.bit.CLR_IRQ_DMA1 = 0;
	Dd_ARM_Dsb_Pou();
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(gDd_Pdm_Spin_Lock);
	
	if (priv->gDd_Pdm_Dma1_Callback_Func[ch] != NULL){
		priv->gDd_Pdm_Dma1_Callback_Func[ch](self);
	}
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(gDd_Pdm_Spin_Lock);
	
	IO_PDM[ch].DMA_CFG.bit.CLR_IRQ_DMA1 = 1;
}

/**
 * @brief  OverFlow interrupt handler
 * @param  UINT8 ch
 */
VOID dd_pdm_overflow_int_handler(DdPdm *self, UINT8 ch)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_OverFlow_Int_Handler:input channel error : %d\n", ch));
		return ;
	}
#endif	// CO_PARAM_CHECK
	
	IO_PDM[ch].DMA_CFG.bit.CLR_IRQ_FFOVF = 0;
	Dd_ARM_Dsb_Pou();
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(gDd_Pdm_Spin_Lock);
	
	if (priv->gDd_Pdm_OverFlow_Callback_Func[ch] != NULL){
		priv->gDd_Pdm_OverFlow_Callback_Func[ch](self);
	}
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(gDd_Pdm_Spin_Lock);
	
	IO_PDM[ch].DMA_CFG.bit.CLR_IRQ_FFOVF = 1;
}

/**
 * @brief  Initialized PDM Macro Setting
 */
INT32 dd_pdm_init(DdPdm *self)
{
	INT32 ret;
	volatile union io_pdm_dmacfg pdmdmacfg;
	
	dd_pdm_set_pdmxck(DdPdm_CH0, 1);
	dd_pdm_set_pdmxck(DdPdm_CH1, 1);
	Dd_ARM_Dsb_Pou();
	
	// Init Register.
	IO_PDM[DdPdm_CH0].CORE_CFG.bit.PDMCORE_EN = DdPdm_DISABLE;
	IO_PDM[DdPdm_CH1].CORE_CFG.bit.PDMCORE_EN = DdPdm_DISABLE;
	
	pdmdmacfg.word = IO_PDM[DdPdm_CH0].DMA_CFG.word;
	pdmdmacfg.bit.DMA_EN = DdPdm_DISABLE;
	pdmdmacfg.bit.CLR_IRQ_FFOVF	= 0;
	pdmdmacfg.bit.CLR_IRQ_DMA1	= 0;
	pdmdmacfg.bit.CLR_IRQ_DMA0	= 0;
	pdmdmacfg.bit.PCM_CHSET		= 3;
	IO_PDM[DdPdm_CH0].DMA_CFG.word = pdmdmacfg.word;
	
	pdmdmacfg.word = IO_PDM[DdPdm_CH1].DMA_CFG.word;
	pdmdmacfg.bit.DMA_EN = DdPdm_DISABLE;
	pdmdmacfg.bit.CLR_IRQ_FFOVF	= 0;
	pdmdmacfg.bit.CLR_IRQ_DMA1	= 0;
	pdmdmacfg.bit.CLR_IRQ_DMA0	= 0;
	pdmdmacfg.bit.PCM_CHSET		= 3;
	IO_PDM[DdPdm_CH1].DMA_CFG.word = pdmdmacfg.word;
	Dd_ARM_Dsb_Pou();
	
	ret = dd_pdm_set_pcm_clk();
	if (ret != D_DDIM_OK){
		return ret;
	}
	
	dd_pdm_set_pdmxck(DdPdm_CH0, 0);
	dd_pdm_set_pdmxck(DdPdm_CH1, 0);
	
	(VOID)dd_pdm_clear_status(self, DdPdm_CH0, DdPdm_INT_TYPE_DMA0);
	(VOID)dd_pdm_clear_status(self, DdPdm_CH1, DdPdm_INT_TYPE_DMA0);
	(VOID)dd_pdm_clear_status(self, DdPdm_CH0, DdPdm_INT_TYPE_DMA1);
	(VOID)dd_pdm_clear_status(self, DdPdm_CH1, DdPdm_INT_TYPE_DMA1);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set Core Control Information
 * @param  UINT8 ch
 * @param  DdPdmCoreCfg *core_cfg
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_ctrl_core(DdPdm *self, UINT8 ch, DdPdmCoreCfg* core_cfg)
{
	volatile union io_pdm_corecfg pdmcorecfg;
	INT32 ret = D_DDIM_OK;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Ctrl_Core:input channel error : %d\n", ch));
		
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (core_cfg == NULL){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Ctrl_Core:ctrl_inf = NULL\n"));
		
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	pdmcorecfg.word = IO_PDM[ch].CORE_CFG.word;
	
	// LRSWAP
	if (core_cfg->swap <= DdPdm_CORE_LR_SWAP_SWAP){
		pdmcorecfg.bit.LRSWAP = (ULONG)core_cfg->swap;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:LRSWAP is out of range. swap = %d\n", (int)core_cfg->swap));
	}
	
	// PGA_R
	if (core_cfg->pgaR <= DdPdm_CORE_PGA_M_1_5_DB){
		pdmcorecfg.bit.PGA_R = (ULONG)core_cfg->pgaR;
		
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:PGA_R is out of range. pgaR = %d\n", (int)core_cfg->pgaR));
	}
	
	// PGA_L
	if (core_cfg->pgaL <= DdPdm_CORE_PGA_M_1_5_DB){
		pdmcorecfg.bit.PGA_L = (ULONG)core_cfg->pgaL;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:PGA_L out of range. pgaL = %d\n", (int)core_cfg->pgaL));
	}
	
	// MCLKDIV
	if ((1 < core_cfg->mclkDiv)	&&
		(core_cfg->mclkDiv <= 12)	){
		pdmcorecfg.bit.MCLKDIV = (ULONG)core_cfg->mclkDiv;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:MCLKDIV is out of range. mclkDiv = %d\n", (int)core_cfg->mclkDiv));
	}
	
	// SINC_RATE
	if ((16 <= core_cfg->sincRate)	&&
		(core_cfg->sincRate < 64)	){
		pdmcorecfg.bit.SINC_RATE = (ULONG)core_cfg->sincRate;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:SINC_RATE is out of range. sincRate = %d\n", (int)core_cfg->sincRate));
	}
	
	// ADCHPD
	if (core_cfg->adcHpd == DdPdm_ENABLE){
		pdmcorecfg.bit.ADCHPD = 0;
	}
	else if (core_cfg->adcHpd == DdPdm_DISABLE){
		//pdmcorecfg.bit.ADCHPD = 1;
		pdmcorecfg.bit.ADCHPD = 0; // from other project, always enable to avoid Audio Pop Up Noise.
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:ADCHPD is out of range. adcHpd = %d\n", (int)core_cfg->adcHpd));
	}
	
	// HPCUTOFF
	pdmcorecfg.bit.HPCUTOFF = core_cfg->hpCutoff;
	
	// S_CYCLES
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	if (core_cfg->sCycle <= DdPdm_CORE_S_CYCLE_1333US){
		pdmcorecfg.bit.S_CYCLES = (ULONG)core_cfg->sCycle;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:S_CYCLES is out of range. sCycle = %d\n", (int)core_cfg->sCycle));
	}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	if (core_cfg->sCycle <= DdPdm_CORE_S_CYCLE_7){
		pdmcorecfg.bit.S_CYCLES = (ULONG)core_cfg->sCycle;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:S_CYCLES is out of range. sCycle = %d\n", (int)core_cfg->sCycle));
	}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	
	// SOFT_MUTE
	if (core_cfg->softMute <= DdPdm_ENABLE){
		pdmcorecfg.bit.SOFT_MUTE = (ULONG)core_cfg->softMute;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Core:SOFT_MUTE is out of range. softMute = %d\n", (int)core_cfg->softMute));
	}
	
	IO_PDM[ch].CORE_CFG.word = pdmcorecfg.word;
	
	return ret;
}

/**
 * @brief  Get Core Control Information
 * @param  UINT8 ch
 * @param  DdPdmCoreCfg *core_cfg
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_get_ctrl_core(DdPdm *self, UINT8 ch, DdPdmCoreCfg* core_cfg)
{
	volatile union io_pdm_corecfg pdmcorecfg;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Get_Ctrl_Core:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (core_cfg == NULL){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Get_Ctrl_Core:ctrl_inf = NULL\n"));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	pdmcorecfg.word = IO_PDM[ch].CORE_CFG.word;
	
	core_cfg->swap		= (PdmCoreLrSwap)pdmcorecfg.bit.LRSWAP;			/* pgr0872 */
	core_cfg->pgaR		= (PdmCorePga)pdmcorecfg.bit.PGA_R;				/* pgr0872 */
	core_cfg->pgaL		= (PdmCorePga)pdmcorecfg.bit.PGA_L;				/* pgr0872 */
	core_cfg->mclkDiv	= pdmcorecfg.bit.MCLKDIV;								/* pgr0872 */
	core_cfg->sincRate	= pdmcorecfg.bit.SINC_RATE;								/* pgr0872 */
	
	// ADCHPD
	if (pdmcorecfg.bit.ADCHPD == 0){											/* pgr0872 */
		core_cfg->adcHpd = DdPdm_ENABLE;
	}
	else {
		core_cfg->adcHpd = DdPdm_DISABLE;
	}
	
	core_cfg->hpCutoff	= pdmcorecfg.bit.HPCUTOFF;								/* pgr0872 */
	core_cfg->sCycle	= (PdmCoreSCycle)pdmcorecfg.bit.S_CYCLES;		/* pgr0872 */
	core_cfg->softMute	= pdmcorecfg.bit.SOFT_MUTE;								/* pgr0872 */
	
	return D_DDIM_OK;
}

/**
 * @brief  Start Data Streaming
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_start_streaming(DdPdm *self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Start_Streaming:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	IO_PDM[ch].CORE_CFG.bit.PDMCORE_EN = DdPdm_ENABLE;
	
	return D_DDIM_OK;
}

/**
 * @brief  Stop Data Streaming
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_stop_streaming(DdPdm *self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Start_Streaming:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	IO_PDM[ch].CORE_CFG.bit.PDMCORE_EN = DdPdm_DISABLE;
	
	return D_DDIM_OK;
}

/**
 * @brief  Set DMA Control Information
 * @param  UINT8 ch
 * @param  DdPdmDmaCfg *dma_cfg
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_ctrl_dma(DdPdm *self, UINT8 ch, DdPdmDmaCfg* dma_cfg)
{
	volatile union io_pdm_dmacfg pdmdmacfg;
	INT32 ret = D_DDIM_OK;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Ctrl_Dma:input channel error : %d\n", ch));
		
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (dma_cfg == NULL){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Ctrl_Dma:dma_cfg = NULL\n"));
		
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	pdmdmacfg.word = IO_PDM[ch].DMA_CFG.word;
	
	// DMICK_DLY
	if (dma_cfg->dmickDly <= 3){
		pdmdmacfg.bit.DMICK_DLY = dma_cfg->dmickDly;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Dma:DMICK_DLY is out of range. dmickDly = %d\n", (int)dma_cfg->dmickDly));
	}
	
	// DMA_BURSTLEN
	if (dma_cfg->dmaBurstlen <= DdPdm_DMA_BURST_LEN_16){
		pdmdmacfg.bit.DMA_BURSTLEN = (ULONG)dma_cfg->dmaBurstlen;
		
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Dma:DMA_BURSTLEN is out of range. dmaBurstlen = %d\n", (int)dma_cfg->dmaBurstlen));
	}
	
	// PCM_CHSET
	if (dma_cfg->pcmChset <= DdPdm_DMA_PCM_CH_STEREO){
		pdmdmacfg.bit.PCM_CHSET = (ULONG)dma_cfg->pcmChset;
		
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Dma:PCM_CHSET is out of range. pcmChset = %d\n", (int)dma_cfg->pcmChset));
	}
	
	// PCM_WDLEN
	if (dma_cfg->pcmWdlen <= DdPdm_DMA_PCM_WD_24){
		pdmdmacfg.bit.PCM_WDLEN = (ULONG)dma_cfg->pcmWdlen;
		
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Dma:PCM_WDLEN is out of range. pcmWdlen = %d\n", (int)dma_cfg->pcmWdlen));
	}
	
	// DMA_EN
	if (dma_cfg->dmaEn <= DdPdm_ENABLE){
		pdmdmacfg.bit.DMA_EN = dma_cfg->dmaEn;
	}
	else {
		ret = DdPdm_INPUT_PARAM_ERROR;
		
		Ddim_Print(("[DD_PDM]Dd_Pdm_Ctrl_Dma:DMA_EN is out of range. dmaEn = %d\n", (int)dma_cfg->dmaEn));
	}
	
	IO_PDM[ch].DMA_CFG.word = pdmdmacfg.word;
	
	return ret;
}

/**
 * @brief  Get DMA Control Information
 * @param  UINT8 ch
 * @param  DdPdmDmaCfg *dma_cfg
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_get_ctrl_dma(DdPdm *self, UINT8 ch, DdPdmDmaCfg* dma_cfg)
{
	volatile union io_pdm_dmacfg pdmdmacfg;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Get_Ctrl_Dma:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (dma_cfg == NULL){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Get_Ctrl_Dma:dma_cfg = NULL\n"));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	pdmdmacfg.word = IO_PDM[ch].DMA_CFG.word;
	
	dma_cfg->dmickDly		= pdmdmacfg.bit.DMICK_DLY;									/* pgr0872 */
	dma_cfg->dmaBurstlen	= (PdmDmaBurstLen)pdmdmacfg.bit.DMA_BURSTLEN;		/* pgr0872 */
	dma_cfg->pcmChset		= (PdmDmaPcmCh)pdmdmacfg.bit.PCM_CHSET;				/* pgr0872 */
	dma_cfg->pcmWdlen		= (PdmDmaPcmWd)pdmdmacfg.bit.PCM_WDLEN;				/* pgr0872 */
	dma_cfg->dmaEn			= pdmdmacfg.bit.DMA_EN;										/* pgr0872 */

	return D_DDIM_OK;
}

/**
 * @brief  Set callback function of Dma0 Interrupt
 * @param  UINT8 ch
 * @param  DdPdmFunc callback
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_set_callback_dma0_intr(DdPdm *self, UINT8 ch, DdPdmFunc callback)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_CallbackDma0Intr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(gDd_Pdm_Spin_Lock);
	
	priv->gDd_Pdm_Dma0_Callback_Func[ch] = callback;
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(gDd_Pdm_Spin_Lock);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set enable/disable Dma0 Interrupt
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_set_enable_dma0_intr(DdPdm *self, UINT8 ch, UINT8 enable)
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
		IO_PDM[ch].DMA_CFG.bit.CLR_IRQ_DMA0 = 0;
	}
	else {
		IO_PDM[ch].DMA_CFG.bit.CLR_IRQ_DMA0 = 1;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Set callback function of Dma1 Interrupt
 * @param  UINT8 ch
 * @param  DdPdmFunc callback
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_set_callback_dma1_intr(DdPdm *self, UINT8 ch, DdPdmFunc callback)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_CallbackDma1Intr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(gDd_Pdm_Spin_Lock);
	
	priv->gDd_Pdm_Dma1_Callback_Func[ch] = callback;
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(gDd_Pdm_Spin_Lock);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set enable/disable Dma1 Interrupt
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_set_enable_dma1_intr(DdPdm *self, UINT8 ch, UINT8 enable)
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
		IO_PDM[ch].DMA_CFG.bit.CLR_IRQ_DMA1 = 0;
	}
	else {
		IO_PDM[ch].DMA_CFG.bit.CLR_IRQ_DMA1 = 1;
		priv->gDd_Pdm_Dma1_Callback_Func[ch] = NULL;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Set callback function of OverFlow Interrupt
 * @param  UINT8 ch
 * @param  DdPdmFunc callback
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_set_callback_over_flow_intr(DdPdm *self, UINT8 ch, DdPdmFunc callback)
{
	DdPdmPrivate *priv = DD_PDM_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_CallbackOverFlowIntr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(gDd_Pdm_Spin_Lock);
	
	priv->gDd_Pdm_OverFlow_Callback_Func[ch] = callback;
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(gDd_Pdm_Spin_Lock);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set enable/disable OverFlow Interrupt
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_set_enable_over_flow_intr(DdPdm *self, UINT8 ch, UINT8 enable)
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
		IO_PDM[ch].DMA_CFG.bit.CLR_IRQ_FFOVF = 0;
	}
	else {
		IO_PDM[ch].DMA_CFG.bit.CLR_IRQ_FFOVF = 1;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Set DMA0 distination address
 * @param  UINT8 ch
 * @param  UINT32 addr
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_set_dma0_dst_addr(DdPdm *self, UINT8 ch, UINT32 addr)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_DMA0_Dst_Addr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	IO_PDM[ch].DMA0_DST_ADDR.word = (addr & 0xFFFFFFFC);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set DMA1 distination address
 * @param  UINT8 ch
 * @param  UINT32 addr
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_set_dma1_dst_addr(DdPdm *self, UINT8 ch, UINT32 addr)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_DMA1_Dst_Addr:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif
	
	IO_PDM[ch].DMA1_DST_ADDR.word = (addr & 0xFFFFFFFC);
	
	return D_DDIM_OK;
}

/**
 * @brief  Set DMA Transfer Length
 * @param  UINT8 ch
 * @param  DdPdmDmaLen* dma_len
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_set_dma_trans_length(DdPdm *self, UINT8 ch, DdPdmDmaLen* dma_len)
{
	volatile union io_pdm_dmalen pdmdmalen;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_Dma_TransLength:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (dma_len == NULL){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_Dma_TransLength:dma_len = NULL\n"));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (dma_len->ttsize > 0x7FFF){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_Dma_TransLength:ttsize is out of range : %d\n", dma_len->ttsize));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (dma_len->ttsize == 0x00){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_Dma_TransLength:ttsize is out of range : %d\n", dma_len->ttsize));
		return DdPdm_INPUT_PARAM_ERROR;
	}
	
	if (dma_len->tsize == 0x00){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Set_Dma_TransLength:tsize is out of range : %d\n", dma_len->tsize));
		return DdPdm_INPUT_PARAM_ERROR;
	}

#endif	// CO_PARAM_CHECK
	
	pdmdmalen.bit.DMA_TTSIZE = dma_len->ttsize;
	pdmdmalen.bit.DMA_TSIZE = dma_len->tsize;
	
	IO_PDM[ch].DMA_LEN.word = pdmdmalen.word;				/* pgr0872 */
	
	return D_DDIM_OK;
}

/**
 * @brief  Start Dma Transfer
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */

INT32 dd_pdm_flush_dma_fifo(DdPdm *self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Flush_Dma_Fifo:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	// FIFO Flush
	IO_PDM[ch].DMA_CFG.bit.DMA_FLUSH = 1;
	Dd_ARM_Dsb_Pou();
	IO_PDM[ch].DMA_CFG.bit.DMA_FLUSH = 0;
	Dd_ARM_Dsb_Pou();
	
	return D_DDIM_OK;
}

/**
 * @brief  Get log of interrupt
 * @param  UINT8 ch
 * @param  DdPdmIntType type
 * @param  UINT8* status
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_get_status(DdPdm *self, UINT8 ch, DdPdmIntType type, UINT8* status)
{
	volatile union io_pdm_status pdmstatus;
	
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
	
	pdmstatus.word = IO_PDM[ch].STATUS.word;
	
	switch (type) {
		case DdPdm_INT_TYPE_FFOVF:
			*status = pdmstatus.bit.FFOVF_INT_REG;				/* pgr0872 */
			break;
		case DdPdm_INT_TYPE_DMA0:
			*status = pdmstatus.bit.DMA0_INT_REG;				/* pgr0872 */
			break;
		case DdPdm_INT_TYPE_DMA1:
			*status = pdmstatus.bit.DMA1_INT_REG;				/* pgr0872 */
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
 * @param  UINT8 ch
 * @param  DdPdmIntType type
 * @return INT32 D_DDIM_OK/DdPdm_INPUT_PARAM_ERROR
 */
INT32 dd_pdm_clear_status(DdPdm *self, UINT8 ch, DdPdmIntType type)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPdm_CH_NUM_MAX){
		Ddim_Assertion(("[DD_PDM]Dd_Pdm_Clear_Status:input channel error : %d\n", ch));
		return DdPdm_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	switch (type) {
		case DdPdm_INT_TYPE_FFOVF:
			IO_PDM[ch].STATUS.bit.FFOVF_INT_REG = 1;
			break;
		case DdPdm_INT_TYPE_DMA0:
			IO_PDM[ch].STATUS.bit.DMA0_INT_REG = 1;
			break;
		case DdPdm_INT_TYPE_DMA1:
			IO_PDM[ch].STATUS.bit.DMA1_INT_REG = 1;
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


