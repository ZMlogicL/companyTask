/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月2日
 * @author            :冯黎阳
 * @brief             :
 * @rely              :klib
 * @function
 * @version
 *
 */


#include "audio_if.h"
#include "ddarm.h"
#include "ddaudio.h"
#include "ddaudioreg.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudioReg, dd_audio_reg);
#define DD_AUDIO_REG_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioRegPrivate, DD_TYPE_AUDIO_REG))


struct _DdAudioRegPrivate
{
	volatile DdAudioRegFunc underFlowCallbackFunc[DdAudio_IF_CH_NUM_MAX];
};


static void dd_audio_reg_constructor(DdAudioReg *self)
{
	DdAudioRegPrivate *priv = DD_AUDIO_REG_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdAudio_IF_CH_NUM_MAX; i++)
	{
		priv->underFlowCallbackFunc[i] = NULL;
	}
}

static void dd_audio_reg_destructor(DdAudioReg *self)
{

}

/**
 * @brief  Set register INTIE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_reg_set_enable_in_full_intr(DdAudioReg* self, kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucr aucr;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set INTIE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set INTIE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (enable == DdAudio_ENABLE){
		if (dd_audio_get_enable_in_usage_intr(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set INTIE Error:eintie = 1\n"));
			return DdAudio_SYSTEM_ERROR;
		}
	}

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucr.word = ioAudio.audioif[ch].aucr.word;
	aucr.bit.intie = enable;
	ioAudio.audioif[ch].aucr.word = aucr.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  Set register INTOE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_reg_set_enable_out_empty_intr(DdAudioReg* self, kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucr aucr;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set INTOE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set INTOE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (enable == DdAudio_ENABLE){
		if (dd_audio_get_enable_out_usage_intr(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set INTOE Error:eintoe = 1\n"));
			return DdAudio_SYSTEM_ERROR;
		}
	}

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucr.word = ioAudio.audioif[ch].aucr.word;
	aucr.bit.intoe = enable;
	ioAudio.audioif[ch].aucr.word = aucr.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  Get register AUIEF.
 * @param  kuint8 ch
 * @return TRUE/FALSE
 */
kboolean dd_audio_reg_get_audio_in_enable_flag(DdAudioReg* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get AUIEF:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aucr.bit.auief == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register AUOE.
 * @param  kuint8 ch
 * @return TRUE/FALSE
 */
kboolean dd_audio_reg_get_audio_out_enable_flag(DdAudioReg* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get AUOEF:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aucr.bit.auoef == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Clear register ORUF.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_reg_clear_out_underflow_flag(DdAudioReg* self, kuint8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAust aust;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Clear ORUF:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = ioAudio.audioif[ch].aust.word;
	aust.bit.oruf = 0;
	ioAudio.audioif[ch].aust.word = aust.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  Set register OFIE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_reg_set_enable_in_overflow_intr(DdAudioReg* self, kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAust aust;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set OFIE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set OFIE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = ioAudio.audioif[ch].aust.word;
	aust.bit.ofie = enable;
	ioAudio.audioif[ch].aust.word = aust.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register UFIE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_reg_set_enable_out_underflow_intr(DdAudioReg* self, kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAust aust;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set UFIE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set UFIE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = ioAudio.audioif[ch].aust.word;
	aust.bit.ufie = enable;
	ioAudio.audioif[ch].aust.word = aust.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register eintie.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_reg_set_enable_in_usage_intr(DdAudioReg* self, kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAust aust;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set eintie:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set eintie:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = ioAudio.audioif[ch].aust.word;

	if (aust.bit.eintie != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_enable_in_full_intr(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set eintie Error:INTIE = 1\n"));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else {
				aust.bit.eintie = enable;
				ioAudio.audioif[ch].aust.word = aust.word;
			}
		}
		else {
			aust.bit.eintie = enable;
			ioAudio.audioif[ch].aust.word = aust.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	Dd_ARM_Dsb_Pou();

	return retVal;
}

/**
 * @brief  Clear register IROF.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_reg_clear_in_overflow_flag(DdAudioReg* self, kuint8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAust aust;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Clear IROF:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = ioAudio.audioif[ch].aust.word;
	aust.bit.irof = 0;
	ioAudio.audioif[ch].aust.word = aust.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  Set register eintoe.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_reg_set_enable_out_usage_intr(DdAudioReg* self, kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAust aust;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set eintoe:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set eintoe:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = ioAudio.audioif[ch].aust.word;

	if (aust.bit.eintoe != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_enable_out_empty_intr(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set eintoe Error:INTOE = 1\n"));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else {
				aust.bit.eintoe = enable;
				ioAudio.audioif[ch].aust.word = aust.word;
			}
		}
		else {
			aust.bit.eintoe = enable;
			ioAudio.audioif[ch].aust.word = aust.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	Dd_ARM_Dsb_Pou();

	return retVal;
}

/**
 * @brief  Get address of register AUIDLR.
 * @param  kuint8 ch
 * @return kuint32 address of register AUIDLR
 */
kuint32 dd_audio_reg_get_addr_reg_auidlr(DdAudioReg* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auidlr:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK

	return (kuint32)&ioAudio.audioif[ch].auidlr;
}

/**
 * @brief  Get address of register AUODLR.
 * @param  kuint8 ch
 * @return kuint32 address of register AUODLR
 */
kuint32 dd_audio_reg_get_addr_reg_auodlr(DdAudioReg* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auodlr:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK

	return (kuint32)&ioAudio.audioif[ch].auodlr;
}

/**
 * @brief  Get address of register AUIDL.
 * @param  kuint8 ch
 * @return kuint32 address of register AUIDL
 */
kuint32 dd_audio_reg_get_addr_reg_auidl(DdAudioReg* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auidl:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (kuint32)&ioAudio.audioif[ch].auidl;
}

/**
 * @brief  Get address of register AUIDR.
 * @param  kuint8 ch
 * @return kuint32 address of register AUIDR
 */
kuint32 dd_audio_reg_get_addr_reg_auidr(DdAudioReg* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auidr:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (kuint32)&ioAudio.audioif[ch].auidr;
}

/**
 * @brief  Get address of register AUODL.
 * @param  kuint8 ch
 * @return kuint32 address of register AUODL
 */
kuint32 dd_audio_reg_get_addr_reg_auodl(DdAudioReg* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auodl:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (kuint32)&ioAudio.audioif[ch].auodl;
}

/**
 * @brief  Get address of register AUODR.
 * @param  kuint8 ch
 * @return kuint32 address of register AUODR
 */
kuint32 dd_audio_reg_get_addr_reg_auodr(DdAudioReg* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auodr:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (kuint32)&ioAudio.audioif[ch].auodr;
}

/**
 * @brief  Get address of register AUIDDMAPT.
 * @param  kuint8 ch
 * @return kuint32 address of register AUIDDMAPT
 */
kuint32 dd_audio_reg_get_addr_reg_auiddmapt(DdAudioReg* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auiddmapt:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (kuint32)&ioAudio.audioif[ch].auiddmapt;
}

/**
 * @brief  Get address of register AUODDMAPT.
 * @param  kuint8 ch
 * @return kuint32 address of register AUODDMAPT
 */
kuint32 dd_audio_reg_get_addr_reg_auoddmapt(DdAudioReg* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auoddmapt:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (kuint32)&ioAudio.audioif[ch].auoddmapt;
}

/**
 * @brief  Set register INTIE/eintie.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @param  DdAudioRegFunc callback
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_reg_set_enable_input_intr(DdAudioReg* self, kuint8 ch, kuint8 enable, DdAudioRegFunc callback)
{
	DdAudio* ddAudio = dd_audio_get();
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_set_enable_input_intr:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_set_enable_input_intr:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if ((dd_audio_get_cmmn_fifo_usage(ddAudio, ch) == DdAudioCtrl_FIFO_USAGE_STAGES_16)	||
		(dd_audio_get_in_fifo_stages(ddAudio, ch) == DdAudioCtrl_FIFO_STAGES_1)){

		ret = dd_audio_reg_set_enable_in_full_intr(self, ch, enable);
	}
	else {
		ret = dd_audio_reg_set_enable_in_usage_intr(self, ch, enable);
	}

	if ((ret == D_DDIM_OK) && (enable == DdAudio_ENABLE)){
		dd_audio_set_input_func(ddAudio, callback, ch);
	}
	else {
		dd_audio_set_input_func(ddAudio, NULL, ch);
	}

	return ret;
}

/**
 * @brief  Set register INTOE/eintoe.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_reg_set_enable_output_intr(DdAudioReg* self, kuint8 ch, kuint8 enable, DdAudioRegFunc callback)
{
	DdAudio* ddAudio = dd_audio_get();
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_set_enable_output_intr:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_set_enable_output_intr:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if ((dd_audio_get_cmmn_fifo_usage(ddAudio, ch) == DdAudioCtrl_FIFO_USAGE_STAGES_16)	||
		(dd_audio_get_out_fifo_stages(ddAudio, ch) == DdAudioCtrl_FIFO_STAGES_1)){

		ret = dd_audio_reg_set_enable_out_empty_intr(self, ch, enable);
	}
	else {
		ret = dd_audio_reg_set_enable_out_usage_intr(self, ch, enable);
	}

	if ((ret == D_DDIM_OK) && (enable == DdAudio_ENABLE)){
		dd_audio_set_output_func(ddAudio, callback, ch);
	}
	else {
		dd_audio_set_output_func(ddAudio, NULL, ch);
	}

	return ret;
}

/**
 * @brief  Set register OFIE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_reg_set_enable_in_over_flow_intr(DdAudioReg* self, kuint8 ch, kuint8 enable, DdAudioRegFunc callback)
{
	DdAudio* ddAudio = dd_audio_get();
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_set_enable_in_over_flow_intr:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_set_enable_in_over_flow_intr:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	ret = dd_audio_reg_clear_in_overflow_flag(self, ch);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_reg_set_enable_in_over_flow_intr:dd_audio_clear_in_overflow_flag() = %x\n",
						ret));
	}

	ret = dd_audio_reg_set_enable_in_overflow_intr(self, ch, enable);

	if ((ret == D_DDIM_OK) && (enable == DdAudio_ENABLE)){
		dd_audio_set_over_flow_func(ddAudio, callback, ch);
	}
	else {
		dd_audio_set_over_flow_func(ddAudio, NULL, ch);
	}

	return ret;
}

/**
 * @brief  Set register UFIE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_reg_set_enable_out_under_flow_intr(DdAudioReg* self, kuint8 ch, kuint8 enable, DdAudioRegFunc callback)
{
	DdAudioRegPrivate *priv = DD_AUDIO_REG_GET_PRIVATE(self);
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_set_enable_out_under_flow_intr:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]DDd_Audio_Set_EnableOutUnderFlowIntr:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	ret = dd_audio_reg_clear_out_underflow_flag(self, ch);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_reg_set_enable_out_under_flow_intr:"
				"dd_audio_clear_out_underflow_flag() = %x\n", ret));
	}

	ret = dd_audio_reg_set_enable_out_underflow_intr(self, ch, enable);

	if ((ret == D_DDIM_OK) && (enable == DdAudio_ENABLE)){
		priv->underFlowCallbackFunc[ch] = callback;
	}
	else {
		priv->underFlowCallbackFunc[ch] = NULL;
	}

	return ret;
}

/**
 * @brief  Get register AUIFST.
 * @param  kuint8 ch
 * @return kuint32 value of register AUIFST
 */
kuint32 dd_audio_reg_get_input_fifo_status(DdAudioReg* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_input_fifo_status:input channel error : %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK

	return ioAudio.audioif[ch].auifst.word;
}

/**
 * @brief  Get register AUOFST.
 * @param  kuint8 ch
 * @return kuint32 value of register AUOFST
 */
kuint32 dd_audio_reg_get_output_fifo_status(DdAudioReg* self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_output_fifo_status:input channel error : %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK

	return ioAudio.audioif[ch].auofst.word;
}

void dd_audio_reg_set_under_flow_func(DdAudioReg* self, DdAudioRegFunc underFlowFunc, int index)
{
	DdAudioRegPrivate *priv = DD_AUDIO_REG_GET_PRIVATE(self);

	priv->underFlowCallbackFunc[index] = underFlowFunc;
}

DdAudioRegFunc dd_audio_reg_get_under_flow_func(DdAudioReg* self, int index)
{
	DdAudioRegPrivate *priv = DD_AUDIO_REG_GET_PRIVATE(self);

	return priv->underFlowCallbackFunc[index];
}

DdAudioReg* dd_audio_reg_new(void)
{
	DdAudioReg* self = k_object_new_with_private(DD_TYPE_AUDIO_REG, sizeof(DdAudioRegPrivate));

	return self;
}
