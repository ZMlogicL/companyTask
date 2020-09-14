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

#include <string.h>
#include "audio_if.h"
#include "ddarm.h"
#include "ddtop.h"
#include "ddimusercustom.h"
#include "ddaudio.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudio, dd_audio);
#define DD_AUDIO_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioPrivate, DD_TYPE_AUDIO))


struct _DdAudioPrivate
{
	DdAudioCtrl* audioCtrl;
	DdAudioDma* audioDma;
	DdAudioI2s* audioI2s;
	DdAudioIo* audioIo;
	DdAudioLoopback* audioLoopBack;
	DdAudioReg* audioReg;
	volatile DdAudioRegFunc overFlowCallbackFunc[DdAudio_IF_CH_NUM_MAX];
	volatile DdAudioRegFunc inputCallbackFunc[DdAudio_IF_CH_NUM_MAX];
	volatile DdAudioRegFunc outputCallbackFunc[DdAudio_IF_CH_NUM_MAX];
};


static 	kulong S_DD_AUDIO_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64))) = 0;


static kint32 ddAudioSetSwReset(kuint8 ch);
static kboolean ddAudioGetInFull(kuint8 ch);
static kboolean ddAudioGetOutEmpty(kuint8 ch);
static kboolean ddAudioGetInOverflowFlag(kuint8 ch);
static kboolean ddAudioGetOutUnderflowFlag(kuint8 ch);
static kboolean ddAudioGetEnableInOverflowIntr(kuint8 ch);
static kboolean ddAudioGetEnableOutUnderflowIntr(kuint8 ch);
static kboolean ddAudioGetInUsageFlag(kuint8 ch);
static kboolean ddAudioGetOutUsageFlag(kuint8 ch);


static void dd_audio_constructor(DdAudio *self)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdAudio_IF_CH_NUM_MAX; i++)
	{
		priv->overFlowCallbackFunc[i] = NULL;
		priv->inputCallbackFunc[i] = NULL;
		priv->outputCallbackFunc[i] = NULL;
	}

	priv->audioCtrl = dd_audio_ctrl_new();
	priv->audioDma = dd_audio_dma_new();
	priv->audioI2s = dd_audio_i2s_new();
	priv->audioIo = dd_audio_io_new();
	priv->audioLoopBack = dd_audio_loopback_new();
	priv->audioReg = dd_audio_reg_new();
}

static void dd_audio_destructor(DdAudio *self)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	if(priv->audioCtrl)
	{
		k_object_unref(priv->audioCtrl);
		priv->audioCtrl = NULL;
	}

	if(priv->audioDma)
	{
		k_object_unref(priv->audioDma);
		priv->audioDma = NULL;
	}

	if(priv->audioI2s)
	{
		k_object_unref(priv->audioI2s);
		priv->audioI2s = NULL;
	}

	if(priv->audioIo)
	{
		k_object_unref(priv->audioIo);
		priv->audioIo = NULL;
	}

	if(priv->audioLoopBack)
	{
		k_object_unref(priv->audioLoopBack);
		priv->audioLoopBack = NULL;
	}

	if(priv->audioReg)
	{
		k_object_unref(priv->audioReg);
		priv->audioReg = NULL;
	}
}

/**
 * @brief  Reset Audio Interface.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetSwReset(kuint8 ch)
{
	volatile IoAudioAures aures;
	
	aures.word = ioAudio.audioifCtrl.aures.word;
	
	switch (ch){
		case DdAudio_IF_CH0 :
			aures.bit.auif0Rst = 1;
			break;
		case DdAudio_IF_CH1 :
			aures.bit.auif1Rst = 1;
			break;
		case DdAudio_IF_CH2 :
			aures.bit.auif2Rst = 1;
			break;
		case DdAudio_IF_CH3 :
			aures.bit.auif3Rst = 1;
			break;
		case DdAudio_IF_CH4 :
			aures.bit.auif4Rst = 1;
			break;
		case DdAudio_IF_CH5 :
			aures.bit.auif5Rst = 1;
			break;
		default :
#ifdef CO_PARAM_CHECK
			Ddim_Assertion(("[DD_AUDIO]]AUDIO Reset:input channel error : %d\n", ch));
#endif	// CO_PARAM_CHECK
			return DdAudio_INPUT_PARAM_ERROR;
	}
	
	// bit6 = 0
	aures.word &= 0x3F;
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(S_DD_AUDIO_SPIN_LOCK);
	
	ioAudio.audioifCtrl.aures.word = aures.word;
	ioAudio.audioifCtrl.aures.word = 0;
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(S_DD_AUDIO_SPIN_LOCK);
	
	return D_DDIM_OK;
}

/**
 * @brief  Get register INTI.
 * @param  kuint8 ch
 * @return TRUE/FALSE
 */
static kboolean ddAudioGetInFull(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get INTI:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	if (ioAudio.audioif[ch].aucr.bit.inti == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register INTO.
 * @param  kuint8 ch
 * @return TRUE/FALSE
 */
static kboolean ddAudioGetOutEmpty(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get INTO:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	if (ioAudio.audioif[ch].aucr.bit.into == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register IROF.
 * @param  kuint8 ch
 * @return TRUE/FALSE
 */
static kboolean ddAudioGetInOverflowFlag(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get IROF:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	if (ioAudio.audioif[ch].aust.bit.irof == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register ORUF.
 * @param  kuint8 ch
 * @return TRUE/FALSE
 */
static kboolean ddAudioGetOutUnderflowFlag(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get ORUF:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	if (ioAudio.audioif[ch].aust.bit.oruf == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register OFIE.
 * @param  kuint8 ch
 * @return kboolean TRUE/FALSE
 */
static kboolean ddAudioGetEnableInOverflowIntr(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get OFIE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	if (ioAudio.audioif[ch].aust.bit.ofie == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register UFIE.
 * @param  kuint8 ch
 * @return kboolean TRUE/FALSE
 */
static kboolean ddAudioGetEnableOutUnderflowIntr(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get UFIE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	if (ioAudio.audioif[ch].aust.bit.ufie == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register EINTI.
 * @param  kuint8 ch
 * @return TRUE/FALSE
 */
static kboolean ddAudioGetInUsageFlag(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get EINTI:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	if (ioAudio.audioif[ch].aust.bit.einti == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register EINTO.
 * @param  kuint8 ch
 * @return TRUE/FALSE
 */
static kboolean ddAudioGetOutUsageFlag(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get EINTO:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	if (ioAudio.audioif[ch].aust.bit.einto == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register INTOE.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kboolean dd_audio_get_enable_out_empty_intr(DdAudio* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get INTOE:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aucr.bit.intoe == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register INTIE.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kboolean dd_audio_get_enable_in_full_intr(DdAudio* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get INTIE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aucr.bit.intie == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register eintie.
 * @param  kuint8 ch
 * @return kboolean TRUE/FALSE
 */
kboolean dd_audio_get_enable_in_usage_intr(DdAudio* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get eintie:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aust.bit.eintie == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register eintoe.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kboolean dd_audio_get_enable_out_usage_intr(DdAudio* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get eintoe:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aust.bit.eintoe == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

kboolean dd_audio_get_loopback_flag(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_loopback_flag_get(priv->audioLoopBack, ch);
}

/**
 * @brief  The audio input channel is exclusively controlled.
 * @param  kuint8 ch
 * @param  kint32 tmout
 * @return kint32 D_DDIM_OK/DdAudio_SEM_NG/DdAudio_INPUT_PARAM_ERROR/DdAudio_SEM_TIMEOUT
 */
kint32 dd_audio_open_input(DdAudio* self, kuint8 ch, kint32 tmout)
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_open_input:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (tmout < DdimUserCustom_SEM_WAIT_FEVR){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_open_input:input timeout error : %d\n", tmout));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	// Exclusive check
	if (tmout == DdimUserCustom_SEM_WAIT_POL){
		ercd = DDIM_User_Pol_Sem(SID_DD_AUDIO_IF_IN(ch));							// pol_sem()
	}
	else {
		ercd = DDIM_User_Twai_Sem(SID_DD_AUDIO_IF_IN(ch), (DdimUserCustom_TMO)tmout);	// twai_sem()
	}
	
	switch (ercd){
		case DdimUserCustom_E_OK:
			return D_DDIM_OK;
		case DdimUserCustom_E_TMOUT:
			return DdAudio_SEM_TIMEOUT;
		default:
			return DdAudio_SEM_NG;
	}
}

/**
 * @brief  The audio output channel is exclusively controlled.
 * @param  kuint8 ch
 * @param  kint32 tmout
 * @return kint32 D_DDIM_OK/DdAudio_SEM_NG/DdAudio_INPUT_PARAM_ERROR/DdAudio_SEM_TIMEOUT
 */
kint32 dd_audio_open_output(DdAudio* self, kuint8 ch, kint32 tmout)
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_open_output:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (tmout < DdimUserCustom_SEM_WAIT_FEVR){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_open_output:input timeout error : %d\n", tmout));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	// Exclusive check
	if (tmout == DdimUserCustom_SEM_WAIT_POL){
		ercd = DDIM_User_Pol_Sem(SID_DD_AUDIO_IF_OUT(ch));							// pol_sem()
	}
	else {
		ercd = DDIM_User_Twai_Sem(SID_DD_AUDIO_IF_OUT(ch), (DdimUserCustom_TMO)tmout);	// twai_sem()
	}
	
	switch (ercd){
		case DdimUserCustom_E_OK:
			return D_DDIM_OK;
		case DdimUserCustom_E_TMOUT:
			return DdAudio_SEM_TIMEOUT;
		default:
			return DdAudio_SEM_NG;
	}
}

/**
 * @brief  The exclusive control of control Input Channel it is released.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_SEM_NG/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_close_input(DdAudio* self, kuint8 ch)
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_close_input:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// Exclusive release
	ercd = DDIM_User_Sig_Sem(SID_DD_AUDIO_IF_IN(ch));					// sig_sem()
	if (ercd == DdimUserCustom_E_OK){
		return D_DDIM_OK;
	}
	else {
		return DdAudio_SEM_NG;
	}
}

/**
 * @brief  The exclusive control of control Output Channel it is released.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_SEM_NG/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_close_output(DdAudio* self, kuint8 ch)
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_close_output:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// Exclusive release
	ercd = DDIM_User_Sig_Sem(SID_DD_AUDIO_IF_OUT(ch));					// sig_sem()
	if (ercd == DdimUserCustom_E_OK){
		return D_DDIM_OK;
	}
	else {
		return DdAudio_SEM_NG;
	}
}

/**
 * @brief  AudioI/F interrupt handler
 * @param  kuint8 ch
 */
void dd_audio_int_handler(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);
	DdAudioRegFunc callbackFunc;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_int_handler:input channel error : %d\n", ch));
		return ;
	}
#endif	// CO_PARAM_CHECK
	
	// input interrupt
	if ((dd_audio_get_enable_in_full_intr(self, ch) != FALSE) && (ddAudioGetInFull(ch) != FALSE)){
		
		Ddim_Print(("[DD_AUDIO]Interrupt:InputRegisterFull[%d]\n",ch));
		
		(void)dd_audio_set_enable_in_full_intr(self, ch, DdAudio_DISABLE);
		
		callbackFunc = priv->inputCallbackFunc[ch];
		if (callbackFunc != NULL){
			callbackFunc(priv->audioReg);
		}
	}
	
	if ((dd_audio_get_enable_in_usage_intr(self, ch) != FALSE) && (ddAudioGetInUsageFlag(ch) != FALSE)){
		
		Ddim_Print(("[DD_AUDIO]Interrupt:Write Completion to Input Register[%d]\n",ch));
		
		(void)dd_audio_set_enable_in_usage_intr(self, ch, DdAudio_DISABLE);
		
		callbackFunc = priv->inputCallbackFunc[ch];
		if (callbackFunc != NULL){
			callbackFunc(priv->audioReg);
		}
	}
	
	// input error interrupt
	if ((ddAudioGetEnableInOverflowIntr(ch) != FALSE) && (ddAudioGetInOverflowFlag(ch) != FALSE)){
		
		Ddim_Print(("[DD_AUDIO]Interrupt:OverFlow[%d]\n",ch));
		
		(void)dd_audio_clear_in_overflow_flag(self, ch);
		
		callbackFunc = priv->overFlowCallbackFunc[ch];
		if (callbackFunc != NULL){
			callbackFunc(priv->audioReg);
		}
	}
	
	// output interrupt
	if ((dd_audio_get_enable_out_empty_intr(self, ch) != FALSE) && (ddAudioGetOutEmpty(ch) != FALSE)){
		
		Ddim_Print(("[DD_AUDIO]Interrupt:OutputRegisterEmpty[%d]\n",ch));
		
		(void)dd_audio_set_enable_out_empty_intr(self, ch, DdAudio_DISABLE);
		
		callbackFunc = priv->outputCallbackFunc[ch];
		if (callbackFunc != NULL){
			callbackFunc(priv->audioReg);
		}
	}
	
	if ((dd_audio_get_enable_out_usage_intr(self, ch) != FALSE) && (ddAudioGetOutUsageFlag(ch) != FALSE)){
		
		Ddim_Print(("[DD_AUDIO]Interrupt:Read Completion from Output Register[%d]\n",ch));
		
		(void)dd_audio_set_enable_out_usage_intr(self, ch, DdAudio_DISABLE);
		
		callbackFunc = priv->outputCallbackFunc[ch];
		if (callbackFunc != NULL){
			callbackFunc(priv->audioReg);
		}
	}
	
	// output error interrupt
	if ((ddAudioGetEnableOutUnderflowIntr(ch) != FALSE) && (ddAudioGetOutUnderflowFlag(ch) != FALSE)){
		
		Ddim_Print(("[DD_AUDIO]Interrupt:UnderFlow[%d]\n",ch))
		
		(void)dd_audio_clear_out_underflow_flag(self, ch);
		
		callbackFunc = dd_audio_reg_get_under_flow_func(priv->audioReg, ch);

		if (callbackFunc != NULL){
			callbackFunc(priv->audioReg);
		}
	}
}

/**
 * @brief  Initialized AudioMacro Setting
 */
void dd_audio_init(DdAudio* self)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	// software reset
	(void)dd_audio_reset(self, DdAudio_IF_CH0);
	(void)dd_audio_reset(self, DdAudio_IF_CH1);
	(void)dd_audio_reset(self, DdAudio_IF_CH2);
	(void)dd_audio_reset(self, DdAudio_IF_CH3);
	(void)dd_audio_reset(self, DdAudio_IF_CH4);
	(void)dd_audio_reset(self, DdAudio_IF_CH5);
	
	// Set Audio PLL
	if (Dd_Top_Get_PLLCNT1_PL10AST() == 0){
		Dd_Top_Stop_Pll10A();
		DdAudio_WAIT_USEC(6);			// wait 6us
		
		Dd_Top_Set_CLKSTOP3_PDM0CK(1);
		Dd_Top_Set_CLKSTOP3_PDM1CK(1);
		
		Dd_Top_Start_Pll10A();
	}
	
	dd_audio_i2s_set_master_clock(priv->audioI2s, (AudioMasterClock)0xFF);
}

/**
 * @brief  Reset AudioI/F Macro
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_reset(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reset:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	ret = ddAudioSetSwReset(ch);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_reset:dd_audio_set_sw_reset() = %x\n", ret));
		return DdAudio_SYSTEM_ERROR;
	}
	
	// Initialize Global Data
	dd_audio_ctrl_set_cmmn_fifo_usage(priv->audioCtrl, ch, DdAudioCtrl_FIFO_USAGE_STAGES_8);
	dd_audio_ctrl_set_cmmn_channel(priv->audioCtrl, ch, DdAudioCtrl_CHANNEL_MONO);
	
	dd_audio_ctrl_set_in_format(priv->audioCtrl, ch, DdAudioCtrl_DATA_REG_FRMT_R_JUST);
	dd_audio_ctrl_set_in_fifo_stages(priv->audioCtrl, ch, DdAudioCtrl_FIFO_STAGES_1);
	dd_audio_ctrl_set_in_ahb_format(priv->audioCtrl, ch, DdAudioCtrl_AHB_FRMT_R_JUST);
	dd_audio_ctrl_set_in_bit_shift(priv->audioCtrl, ch, DdAudioCtrl_BIT_SHIFT_0);
	
	dd_audio_ctrl_set_out_format(priv->audioCtrl, ch, DdAudioCtrl_DATA_REG_FRMT_R_JUST);
	dd_audio_ctrl_set_out_fifo_stages(priv->audioCtrl, ch, DdAudioCtrl_FIFO_STAGES_1);
	dd_audio_ctrl_set_out_ahb_format(priv->audioCtrl, ch, DdAudioCtrl_AHB_FRMT_R_JUST);
	dd_audio_ctrl_set_out_lr_copy(priv->audioCtrl, ch, DdAudio_DISABLE);
	dd_audio_ctrl_set_out_mix_play(priv->audioCtrl, ch, DdAudio_DISABLE);
	dd_audio_ctrl_set_out_bit_shift(priv->audioCtrl, ch, DdAudioCtrl_BIT_SHIFT_0);
	
	if (ch != DdAudio_IF_CH1){
		dd_audio_i2s_cmmn_init(priv->audioI2s, ch);
	}
	
	dd_audio_i2s_in_init(priv->audioI2s, ch);

	dd_audio_i2s_out_init(priv->audioI2s, ch);
	
	dd_audio_dma_set_in_2ch(priv->audioDma, ch, DdAudio_DISABLE);
	dd_audio_dma_set_in_trnsf_cnt(priv->audioDma, ch, 0);
	
	dd_audio_dma_set_out_2ch(priv->audioDma, ch, DdAudio_DISABLE);
	dd_audio_dma_set_out_trnsf_cnt(priv->audioDma, ch, 0);
	
	priv->overFlowCallbackFunc[ch] = NULL;
	dd_audio_reg_set_under_flow_func(priv->audioReg, NULL, ch);
	priv->inputCallbackFunc[ch] = NULL;
	priv->outputCallbackFunc[ch] = NULL;
	
	return D_DDIM_OK;
}

kint32 dd_audio_ctrl_common(DdAudio *self, kuint8 ch, AudioCtrlCommon* ctrlInf)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_ctrl_common(priv->audioCtrl, ch, ctrlInf);
}

kint32 dd_audio_get_ctrl_common(DdAudio *self, kuint8 ch, AudioCtrlCommon* ctrlInf)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_get_ctrl_common(priv->audioCtrl, ch, ctrlInf);
}

kint32 dd_audio_ctrl_input(DdAudio *self, kuint8 ch, AudioCtrlIn* ctrlInf)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_ctrl_input(priv->audioCtrl, ch, ctrlInf);
}

kint32 dd_audio_get_ctrl_input(DdAudio *self, kuint8 ch, AudioCtrlIn* ctrlInf)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_get_ctrl_input(priv->audioCtrl, ch, ctrlInf);
}

kint32 dd_audio_ctrl_output(DdAudio *self, kuint8 ch, AudioCtrlOut* ctrlInf)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_ctrl_output(priv->audioCtrl, ch, ctrlInf);
}

kint32 dd_audio_get_ctrl_output(DdAudio *self, kuint8 ch, AudioCtrlOut* ctrlInf)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_get_ctrl_output(priv->audioCtrl, ch, ctrlInf);
}

void dd_audio_set_over_flow_func(DdAudio* self, DdAudioRegFunc overFlowFunc, int index)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	priv->overFlowCallbackFunc[index] = overFlowFunc;
}

void dd_audio_set_input_func(DdAudio* self, DdAudioRegFunc input, int index)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	priv->inputCallbackFunc[index] = input;
}

void dd_audio_set_output_func(DdAudio* self, DdAudioRegFunc output, int index)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	priv->outputCallbackFunc[index] = output;
}

kulong* dd_audio_get_spin_lock_addr(DdAudio* self)
{
	return &S_DD_AUDIO_SPIN_LOCK;
}

AudioFifoUsage dd_audio_get_cmmn_fifo_usage(DdAudio* self, int index)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_get_cmmn_fifo_usage(priv->audioCtrl, index);
}

AudioFifoStages dd_audio_get_in_fifo_stages(DdAudio* self, int index)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_get_in_fifo_stages(priv->audioCtrl, index);
}

AudioFifoStages dd_audio_get_out_fifo_stages(DdAudio* self, int index)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_get_out_fifo_stages(priv->audioCtrl, index);
}

kint32 dd_audio_ctrl_dma_in(DdAudio *self, kuint8 ch, AudioDma* dmaSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_ctrl_dma_in(priv->audioDma, ch, dmaSetting);
}

kint32 dd_audio_get_ctrl_dma_in(DdAudio *self, kuint8 ch, AudioDma* dmaSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_get_ctrl_dma_in(priv->audioDma, ch, dmaSetting);
}

kint32 dd_audio_ctrl_dma_out(DdAudio *self, kuint8 ch, AudioDma* dmaSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_ctrl_dma_out(priv->audioDma, ch, dmaSetting);
}

kint32 dd_audio_get_ctrl_dma_out(DdAudio *self, kuint8 ch, AudioDma* dmaSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_get_ctrl_dma_out(priv->audioDma, ch, dmaSetting);
}

kint32 dd_audio_set_enable_fifo_full_dmain(DdAudio *self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_enable_fifo_full_dmain(priv->audioDma, ch, enable);
}

kint32 dd_audio_set_enable_fifo_empty_dma_out(DdAudio *self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_enable_fifo_empty_dma_out(priv->audioDma, ch, enable);
}

kint32 dd_audio_set_input_dma_request_enable(DdAudio *self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_input_dma_request_enable(priv->audioDma, ch, enable);
}

kint32 dd_audio_set_output_dma_request_enable(DdAudio *self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_output_dma_request_enable(priv->audioDma, ch, enable);
}

UINT16 dd_audio_get_in_dma_sample(DdAudio *self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_get_in_dma_sample(priv->audioDma, ch);
}

UINT16 dd_audio_get_out_dma_sample(DdAudio *self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_get_out_dma_sample(priv->audioDma, ch);
}

kint32 dd_audio_set_swap_byte_auidlr(DdAudio *self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_swapbyte_auidlr(priv->audioDma, ch, enable);
}

kint32 dd_audio_set_swap_hw_auidlr(DdAudio *self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_swap_hw_auidlr(priv->audioDma, ch, enable);
}

kint32 dd_audio_set_swap_byte_auodlr(DdAudio *self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_swap_byte_auodlr(priv->audioDma, ch, enable);
}

kint32 dd_audio_set_swap_hw_auodlr(DdAudio *self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_swap_hw_auodlr(priv->audioDma, ch, enable);
}

AudioClkMode dd_audio_get_cmmn_master_slave(DdAudio *self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_get_cmmn_master_slave(priv->audioI2s, ch);
}

kint32 dd_audio_ctrl_i2s_cmmn(DdAudio *self, kuint8 ch, AudioI2sCmmn* i2sSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_ctrl_i2s_cmmn(priv->audioI2s, ch, i2sSetting);
}

kint32 dd_audio_get_ctrl_i2s_cmmn(DdAudio *self, kuint8 ch, AudioI2sCmmn* i2sSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_get_ctrl_i2s_cmmn(priv->audioI2s, ch, i2sSetting);
}

kint32 dd_audio_ctrl_i2s_in(DdAudio *self, kuint8 ch, AudioI2sIn* i2sSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_ctrl_i2s_in(priv->audioI2s, ch, i2sSetting);
}

kint32 dd_audio_get_ctrl_i2s_in(DdAudio *self, kuint8 ch, AudioI2sIn* i2sSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_get_ctrl_i2s_in(priv->audioI2s, ch, i2sSetting);
}

kint32 dd_audio_ctrl_i2s_out(DdAudio *self, kuint8 ch, AudioI2sOut* i2sSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_ctrl_i2s_out(priv->audioI2s, ch, i2sSetting);
}

kint32 dd_audio_get_ctrl_i2s_out(DdAudio *self, kuint8 ch, AudioI2sOut* i2sSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_get_ctrl_i2s_out(priv->audioI2s, ch, i2sSetting);
}

kint32 dd_audio_start_input(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_io_start_input(priv->audioIo, ch);
}

kint32 dd_audio_stop_input(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_io_stop_input(priv->audioIo, ch);
}

kboolean dd_audio_get_status_input(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_io_get_status_input(priv->audioIo, ch);
}

kint32 dd_audio_start_output(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_io_start_output(priv->audioIo, ch);
}

kint32 dd_audio_stop_output(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_io_stop_output(priv->audioIo, ch);
}

kboolean dd_audio_get_status_output(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_io_get_status_output(priv->audioIo, ch);
}

kint32 dd_audio_start_loop_back(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_loopback_start(priv->audioLoopBack, ch);
}

kint32 dd_audio_stop_loop_back(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_loopback_stop(priv->audioLoopBack, ch);
}

kboolean dd_audio_get_status_loop_back(DdAudio* self, kuchar ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_loopback_get_status(priv->audioLoopBack, ch);
}

kuint32 dd_audio_get_addr_reg_auidlr(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auidlr(priv->audioReg, ch);
}

kuint32 dd_audio_get_addr_reg_auodlr(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auodlr(priv->audioReg, ch);
}

kuint32 dd_audio_get_addr_reg_auidl(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auidl(priv->audioReg, ch);
}

kuint32 dd_audio_get_addr_reg_auidr(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auidr(priv->audioReg, ch);
}

kuint32 dd_audio_get_addr_reg_auodl(DdAudio* self, kuchar ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auodl(priv->audioReg, ch);
}

kuint32 dd_audio_get_addr_reg_auodr(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auodr(priv->audioReg, ch);
}

kuint32 dd_audio_get_addr_reg_auiddmapt(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auiddmapt(priv->audioReg, ch);
}

kuint32 dd_audio_get_addr_reg_auoddmapt(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auoddmapt(priv->audioReg, ch);
}

kint32 dd_audio_set_enable_input_intr(DdAudio* self, kuint8 ch, kuint8 enable, DdAudioRegFunc callback)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_input_intr(priv->audioReg, ch, enable, callback);
}

kint32 dd_audio_set_enable_output_intr(DdAudio* self, kuint8 ch, kuint8 enable, DdAudioRegFunc callback)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_output_intr(priv->audioReg, ch, enable, callback);
}

kint32 dd_audio_set_enable_in_over_flow_intr(DdAudio* self, kuint8 ch, kuint8 enable, DdAudioRegFunc callback)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_in_over_flow_intr(priv->audioReg, ch, enable, callback);
}

kint32 dd_audio_set_enable_out_under_flow_intr(DdAudio* self, kuint8 ch, kuint8 enable, DdAudioRegFunc callback)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_out_under_flow_intr(priv->audioReg, ch, enable, callback);
}

kuint32 dd_audio_get_input_fifo_status(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_input_fifo_status(priv->audioReg, ch);
}

kuint32 dd_audio_get_output_fifo_status(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_output_fifo_status(priv->audioReg, ch);
}

kint32 dd_audio_set_enable_in_full_intr(DdAudio* self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_in_full_intr(priv->audioReg, ch, enable);
}

kint32 dd_audio_set_enable_out_empty_intr(DdAudio* self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_out_empty_intr(priv->audioReg, ch, enable);
}

kboolean dd_audio_get_audio_in_enable_flag(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_audio_in_enable_flag(priv->audioReg, ch);
}

kboolean dd_audio_get_audio_out_enable_flag(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_audio_out_enable_flag(priv->audioReg, ch);
}

kint32 dd_audio_clear_out_underflow_flag(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_clear_out_underflow_flag(priv->audioReg, ch);
}

kint32 dd_audio_set_enable_in_overflow_intr(DdAudio* self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_in_overflow_intr(priv->audioReg, ch, enable);
}

kint32 dd_audio_set_enable_out_underflow_intr(DdAudio* self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_out_underflow_intr(priv->audioReg, ch, enable);
}

kint32 dd_audio_set_enable_in_usage_intr(DdAudio* self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_in_usage_intr(priv->audioReg, ch, enable);
}

kint32 dd_audio_clear_in_overflow_flag(DdAudio* self, kuint8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_clear_in_overflow_flag(priv->audioReg, ch);
}

kint32 dd_audio_set_enable_out_usage_intr(DdAudio* self, kuint8 ch, kuint8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_out_usage_intr(priv->audioReg, ch, enable);
}

DdAudio* dd_audio_get(void)
{
	static DdAudio* self = NULL;

	if(!self)
		self = k_object_new_with_private(DD_TYPE_AUDIO, sizeof(DdAudioPrivate));

	return self;
}

