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
#include "dd_arm.h"
#include "ddaudio.h"
#include "ddaudioreg.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudioReg, dd_audio_reg);
#define DD_AUDIO_REG_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioRegPrivate, DD_TYPE_AUDIO_REG))


struct _DdAudioRegPrivate
{
	volatile DdAudioRegFunc gDd_Audio_UnderFlow_Callback_Func[DdAudio_IF_CH_NUM_MAX];
};


static void dd_audio_reg_constructor(DdAudioReg *self)
{
	DdAudioRegPrivate *priv = DD_AUDIO_REG_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdAudio_IF_CH_NUM_MAX; i++)
	{
		priv->gDd_Audio_UnderFlow_Callback_Func[i] = NULL;
	}
}

static void dd_audio_reg_destructor(DdAudioReg *self)
{

}

/**
 * @brief  Set register INTIE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_reg_set_enable_in_full_intr(DdAudioReg* self, UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucr aucr;

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
			Ddim_Print(("[DD_AUDIO]Set INTIE Error:EINTIE = 1\n"));
			return DdAudio_SYSTEM_ERROR;
		}
	}

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucr.word = IO_AUDIO.AUDIOIF[ch].AUCR.word;
	aucr.bit.INTIE = enable;
	IO_AUDIO.AUDIOIF[ch].AUCR.word = aucr.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  Set register INTOE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_reg_set_enable_out_empty_intr(DdAudioReg* self, UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucr aucr;

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
			Ddim_Print(("[DD_AUDIO]Set INTOE Error:EINTOE = 1\n"));
			return DdAudio_SYSTEM_ERROR;
		}
	}

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucr.word = IO_AUDIO.AUDIOIF[ch].AUCR.word;
	aucr.bit.INTOE = enable;
	IO_AUDIO.AUDIOIF[ch].AUCR.word = aucr.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  Get register AUIEF.
 * @param  UINT8 ch
 * @return TRUE/FALSE
 */
BOOL dd_audio_reg_get_audio_in_enable_flag(DdAudioReg* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get AUIEF:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register AUOE.
 * @param  UINT8 ch
 * @return TRUE/FALSE
 */
BOOL dd_audio_reg_get_audio_out_enable_flag(DdAudioReg* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get AUOEF:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Clear register ORUF.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_reg_clear_out_underflow_flag(DdAudioReg* self, UINT8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aust aust;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Clear ORUF:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = IO_AUDIO.AUDIOIF[ch].AUST.word;
	aust.bit.ORUF = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  Set register OFIE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_reg_set_enable_in_overflow_intr(DdAudioReg* self, UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aust aust;

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

	aust.word = IO_AUDIO.AUDIOIF[ch].AUST.word;
	aust.bit.OFIE = enable;
	IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register UFIE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_reg_set_enable_out_underflow_intr(DdAudioReg* self, UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aust aust;

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

	aust.word = IO_AUDIO.AUDIOIF[ch].AUST.word;
	aust.bit.UFIE = enable;
	IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register EINTIE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_reg_set_enable_in_usage_intr(DdAudioReg* self, UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aust aust;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set EINTIE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set EINTIE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = IO_AUDIO.AUDIOIF[ch].AUST.word;

	if (aust.bit.EINTIE != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_enable_in_full_intr(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set EINTIE Error:INTIE = 1\n"));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else {
				aust.bit.EINTIE = enable;
				IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;
			}
		}
		else {
			aust.bit.EINTIE = enable;
			IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	Dd_ARM_Dsb_Pou();

	return ret_val;
}

/**
 * @brief  Clear register IROF.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_reg_clear_in_overflow_flag(DdAudioReg* self, UINT8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aust aust;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Clear IROF:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = IO_AUDIO.AUDIOIF[ch].AUST.word;
	aust.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/**
 * @brief  Set register EINTOE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_reg_set_enable_out_usage_intr(DdAudioReg* self, UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aust aust;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set EINTOE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set EINTOE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = IO_AUDIO.AUDIOIF[ch].AUST.word;

	if (aust.bit.EINTOE != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_enable_out_empty_intr(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set EINTOE Error:INTOE = 1\n"));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else {
				aust.bit.EINTOE = enable;
				IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;
			}
		}
		else {
			aust.bit.EINTOE = enable;
			IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	Dd_ARM_Dsb_Pou();

	return ret_val;
}

/**
 * @brief  Get address of register AUIDLR.
 * @param  UINT8 ch
 * @return UINT32 address of register AUIDLR
 */
UINT32 dd_audio_reg_get_addr_reg_auidlr(DdAudioReg* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auidlr:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK

	return (UINT32)&IO_AUDIO.AUDIOIF[ch].AUIDLR;
}

/**
 * @brief  Get address of register AUODLR.
 * @param  UINT8 ch
 * @return UINT32 address of register AUODLR
 */
UINT32 dd_audio_reg_get_addr_reg_auodlr(DdAudioReg* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auodlr:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK

	return (UINT32)&IO_AUDIO.AUDIOIF[ch].AUODLR;
}

/**
 * @brief  Get address of register AUIDL.
 * @param  UINT8 ch
 * @return UINT32 address of register AUIDL
 */
UINT32 dd_audio_reg_get_addr_reg_auidl(DdAudioReg* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auidl:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (UINT32)&IO_AUDIO.AUDIOIF[ch].AUIDL;
}

/**
 * @brief  Get address of register AUIDR.
 * @param  UINT8 ch
 * @return UINT32 address of register AUIDR
 */
UINT32 dd_audio_reg_get_addr_reg_auidr(DdAudioReg* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auidr:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (UINT32)&IO_AUDIO.AUDIOIF[ch].AUIDR;
}

/**
 * @brief  Get address of register AUODL.
 * @param  UINT8 ch
 * @return UINT32 address of register AUODL
 */
UINT32 dd_audio_reg_get_addr_reg_auodl(DdAudioReg* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auodl:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (UINT32)&IO_AUDIO.AUDIOIF[ch].AUODL;
}

/**
 * @brief  Get address of register AUODR.
 * @param  UINT8 ch
 * @return UINT32 address of register AUODR
 */
UINT32 dd_audio_reg_get_addr_reg_auodr(DdAudioReg* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auodr:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (UINT32)&IO_AUDIO.AUDIOIF[ch].AUODR;
}

/**
 * @brief  Get address of register AUIDDMAPT.
 * @param  UINT8 ch
 * @return UINT32 address of register AUIDDMAPT
 */
UINT32 dd_audio_reg_get_addr_reg_auiddmapt(DdAudioReg* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auiddmapt:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (UINT32)&IO_AUDIO.AUDIOIF[ch].AUIDDMAPT;
}

/**
 * @brief  Get address of register AUODDMAPT.
 * @param  UINT8 ch
 * @return UINT32 address of register AUODDMAPT
 */
UINT32 dd_audio_reg_get_addr_reg_auoddmapt(DdAudioReg* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_addr_reg_auoddmapt:input channel error: %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	return (UINT32)&IO_AUDIO.AUDIOIF[ch].AUODDMAPT;
}

/**
 * @brief  Set register INTIE/EINTIE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @param  DdAudioRegFunc callback
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_reg_set_enable_input_intr(DdAudioReg* self, UINT8 ch, UINT8 enable, DdAudioRegFunc callback)
{
	DdAudio* ddAudio = dd_audio_get();
	INT32 ret;

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
		(dd_audio_get_in_fifo_stages(ddAudio, ch) == DdAudioCtrl_FIFO_STAGES_1)			){

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
 * @brief  Set register INTOE/EINTOE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_reg_set_enable_output_intr(DdAudioReg* self, UINT8 ch, UINT8 enable, DdAudioRegFunc callback)
{
	DdAudio* ddAudio = dd_audio_get();
	INT32 ret;

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
		(dd_audio_get_out_fifo_stages(ddAudio, ch) == DdAudioCtrl_FIFO_STAGES_1)			){

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
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_reg_set_enable_in_over_flow_intr(DdAudioReg* self, UINT8 ch, UINT8 enable, DdAudioRegFunc callback)
{
	DdAudio* ddAudio = dd_audio_get();
	INT32 ret;

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
		Ddim_Print(("[DD_AUDIO]dd_audio_reg_set_enable_in_over_flow_intr:dd_audio_clear_in_overflow_flag() = %x\n", ret));
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
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_reg_set_enable_out_under_flow_intr(DdAudioReg* self, UINT8 ch, UINT8 enable, DdAudioRegFunc callback)
{
	DdAudioRegPrivate *priv = DD_AUDIO_REG_GET_PRIVATE(self);
	INT32 ret;

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
		Ddim_Print(("[DD_AUDIO]dd_audio_reg_set_enable_out_under_flow_intr:dd_audio_clear_out_underflow_flag() = %x\n", ret));
	}

	ret = dd_audio_reg_set_enable_out_underflow_intr(self, ch, enable);

	if ((ret == D_DDIM_OK) && (enable == DdAudio_ENABLE)){
		priv->gDd_Audio_UnderFlow_Callback_Func[ch] = callback;
	}
	else {
		priv->gDd_Audio_UnderFlow_Callback_Func[ch] = NULL;
	}

	return ret;
}

/**
 * @brief  Get register AUIFST.
 * @param  UINT8 ch
 * @return UINT32 value of register AUIFST
 */
UINT32 dd_audio_reg_get_input_fifo_status(DdAudioReg* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_input_fifo_status:input channel error : %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK

	return IO_AUDIO.AUDIOIF[ch].AUIFST.word;
}

/**
 * @brief  Get register AUOFST.
 * @param  UINT8 ch
 * @return UINT32 value of register AUOFST
 */
UINT32 dd_audio_reg_get_output_fifo_status(DdAudioReg* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reg_get_output_fifo_status:input channel error : %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK

	return IO_AUDIO.AUDIOIF[ch].AUOFST.word;
}

void dd_audio_reg_set_under_flow_func(DdAudioReg* self, DdAudioRegFunc underFlowFunc, int index)
{
	DdAudioRegPrivate *priv = DD_AUDIO_REG_GET_PRIVATE(self);

	priv->gDd_Audio_UnderFlow_Callback_Func[index] = underFlowFunc;
}

DdAudioRegFunc dd_audio_reg_get_under_flow_func(DdAudioReg* self, int index)
{
	DdAudioRegPrivate *priv = DD_AUDIO_REG_GET_PRIVATE(self);

	return priv->gDd_Audio_UnderFlow_Callback_Func[index];
}

DdAudioReg* dd_audio_reg_new(void)
{
	DdAudioReg* self = k_object_new_with_private(DD_TYPE_AUDIO_REG, sizeof(DdAudioRegPrivate));

	return self;
}
