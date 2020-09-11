/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月3日
 * @author            :冯黎阳
 * @brief             :
 * @rely              :klib
 * @function
 * @version
 *
 */


#include <string.h>
#include "audio_if.h"
#include "dd_arm.h"
#include "ddaudio.h"
#include "ddaudiodma.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudioDma, dd_audio_dma);
#define DD_AUDIO_DMA_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioDmaPrivate, DD_TYPE_AUDIO_DMA))


struct _DdAudioDmaPrivate
{
	volatile AudioDma inData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioDma outData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioDma	*gDd_Audio_Dma_In[DdAudio_IF_CH_NUM_MAX];
	volatile AudioDma	*gDd_Audio_Dma_Out[DdAudio_IF_CH_NUM_MAX];
};


static INT32 dd_audio_set_enable_fifo_full_dma_in(UINT8 ch, UINT8 enable);
static INT32 ddAudioSetEnableFifoEmptyDmaOut(UINT8 ch, UINT8 enable);
static BOOL dd_audio_get_enable_fifo_empty_dma_out(UINT8 ch);
static INT32 ddDudioSetInputDmaRequestEnable(UINT8 ch, UINT8 enable);
static INT32 ddAudioSetOutputDmaRequestEnable(UINT8 ch, UINT8 enable);
static INT32 dd_audio_set_input_byte_swap(UINT8 ch, UINT8 enable);
static INT32 dd_audio_set_input_hw_swap(UINT8 ch, UINT8 enable);
static INT32 dd_audio_set_output_byte_swap(UINT8 ch, UINT8 enable);
static INT32 dd_audio_set_output_hw_swap(UINT8 ch, UINT8 enable);
static INT32 dd_audio_set_enable_in_dma2ch(UINT8 ch, UINT8 enable);
static INT32 dd_audio_set_enable_out_dma2ch(UINT8 ch, UINT8 enable);
static INT32 dd_audio_set_in_dma_sample(UINT8 ch, UINT16 sample);
static INT32 dd_audio_set_out_dma_sample(UINT8 ch, UINT16 sample);
static BOOL dd_audio_get_input_dma_request_enable(UINT8 ch);
static BOOL dd_audio_get_output_dma_request_enable(UINT8 ch);
static BOOL dd_audio_get_enable_fifo_full_dma_in(UINT8 ch);

static void dd_audio_dma_constructor(DdAudioDma *self)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdAudio_IF_CH_NUM_MAX; i++)
	{
		priv->inData[i].dma2Ch = DdAudio_DISABLE;
		priv->inData[i].dmaTrnsfCnt = 0;

		priv->outData[i].dma2Ch = DdAudio_DISABLE;
		priv->outData[i].dmaTrnsfCnt = 0;

		priv->gDd_Audio_Dma_In[i] = &priv->inData[i];
		priv->gDd_Audio_Dma_Out[i] = &priv->outData[i];
	}
}

static void dd_audio_dma_destructor(DdAudioDma *self)
{

}

/**
 * @brief  Set register DMIE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_enable_fifo_full_dma_in(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucr aucr;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set DMIE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set DMIE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucr.word = IO_AUDIO.AUDIOIF[ch].AUCR.word;

	if (aucr.bit.DMIE != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_input_dma_request_enable(ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set DMIE Error:EDMIE = 1\n"));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else {
				aucr.bit.DMIE = enable;
				IO_AUDIO.AUDIOIF[ch].AUCR.word = aucr.word;
			}
		}
		else {
			aucr.bit.DMIE = enable;
			IO_AUDIO.AUDIOIF[ch].AUCR.word = aucr.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register DMOE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 ddAudioSetEnableFifoEmptyDmaOut(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucr aucr;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set DMOE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set DMOE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucr.word = IO_AUDIO.AUDIOIF[ch].AUCR.word;

	if (aucr.bit.DMOE != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_output_dma_request_enable(ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set DMOE Error:EDMOE = 1\n"));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else {
				aucr.bit.DMOE = enable;
				IO_AUDIO.AUDIOIF[ch].AUCR.word = aucr.word;
			}
		}
		else {
			aucr.bit.DMOE = enable;
			IO_AUDIO.AUDIOIF[ch].AUCR.word = aucr.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Get register DMOE.
 * @param  UINT8 ch
 * @return BOOL TRUE/FALSE
 */
static BOOL dd_audio_get_enable_fifo_empty_dma_out(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get DMOE:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUCR.bit.DMOE == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Set register IBYTE_SWP.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_input_byte_swap(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aumd aumd;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set IBYTE_SWP:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set IBYTE_SWP:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aumd.word = IO_AUDIO.AUDIOIF[ch].AUMD.word;

	if (aumd.bit.IBYTE_SWP != enable){								/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set IBYTE_SWP Error:AUIEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.IBYTE_SWP = enable;
			IO_AUDIO.AUDIOIF[ch].AUMD.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register IHW_SWP.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_input_hw_swap(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aumd aumd;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set IHW_SWP:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set IHW_SWP:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aumd.word = IO_AUDIO.AUDIOIF[ch].AUMD.word;

	if (aumd.bit.IHW_SWP != enable){								/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set IHW_SWP Error:AUIEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.IHW_SWP = enable;
			IO_AUDIO.AUDIOIF[ch].AUMD.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register OBYTE_SWP.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_output_byte_swap(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aumd aumd;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set OBYTE_SWP:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set OBYTE_SWP:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aumd.word = IO_AUDIO.AUDIOIF[ch].AUMD.word;

	if (aumd.bit.OBYTE_SWP != enable){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set OBYTE_SWP Error:AUOEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set OBYTE_SWP Error:LBF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.OBYTE_SWP = enable;
			IO_AUDIO.AUDIOIF[ch].AUMD.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register OHW_SWP.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_output_hw_swap(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aumd aumd;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set OHW_SWP:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set OHW_SWP:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aumd.word = IO_AUDIO.AUDIOIF[ch].AUMD.word;

	if (aumd.bit.OHW_SWP != enable){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set OHW_SWP Error:AUOEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set OHW_SWP Error:LBF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.OHW_SWP = enable;
			IO_AUDIO.AUDIOIF[ch].AUMD.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register EDMIE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 ddDudioSetInputDmaRequestEnable(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aust aust;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set EDMIE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set EDMIE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = IO_AUDIO.AUDIOIF[ch].AUST.word;

	if (aust.bit.EDMIE != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_enable_fifo_full_dma_in(ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set EDMIE Error:DMIE = 1\n"));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else {
				aust.bit.EDMIE = enable;
				IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;
			}
		}
		else {
			aust.bit.EDMIE = enable;
			IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register EDMOE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 ddAudioSetOutputDmaRequestEnable(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aust aust;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set EDMOE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set EDMOE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = IO_AUDIO.AUDIOIF[ch].AUST.word;

	if (aust.bit.EDMOE != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_enable_fifo_empty_dma_out(ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set EDMOE Error:DMOE = 1\n"));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else {
				aust.bit.EDMOE = enable;
				IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;
			}
		}
		else {
			aust.bit.EDMOE = enable;
			IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register DMI2CHEN.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_enable_in_dma2ch(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_audma2ctl audma2ctl;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set DMI2CHEN:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set DMI2CHEN:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	audma2ctl.word = IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.word;
	audma2ctl.bit.DMI2CHEN = enable;
	IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.word = audma2ctl.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register DMO2CHEN.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_enable_out_dma2ch(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_audma2ctl audma2ctl;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set DMO2CHEN:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set DMO2CHEN:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	audma2ctl.word = IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.word;
	audma2ctl.bit.DMO2CHEN = enable;
	IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.word = audma2ctl.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register DMISPL.
 * @param  UINT8 ch
 * @param  UINT16 sample
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_in_dma_sample(UINT8 ch, UINT16 sample)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set DMISPL:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	IO_AUDIO.AUDIOIF[ch].AUDMISAMPLE.bit.DMISPL = sample;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register DMOSPL.
 * @param  UINT8 ch
 * @param  UINT16 sample
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_out_dma_sample(UINT8 ch, UINT16 sample)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set DMOSPL : input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	IO_AUDIO.AUDIOIF[ch].AUDMOSAMPLE.bit.DMOSPL = sample;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Get register EDMIE.
 * @param  UINT8 ch
 * @return BOOL TRUE/FALSE
 */
static BOOL dd_audio_get_input_dma_request_enable(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get EDMIE:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUST.bit.EDMIE == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register EDMOE.
 * @param  UINT8 ch
 * @return BOOL TRUE/FALSE
 */
static BOOL dd_audio_get_output_dma_request_enable(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get EDMOE:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUST.bit.EDMOE == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register DMIE.
 * @param  UINT8 ch
 * @return BOOL TRUE/FALSE
 */
static BOOL dd_audio_get_enable_fifo_full_dma_in(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get DMIE:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUCR.bit.DMIE == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Set Audio DMA Information of Input
 * @param  UINT8 ch
 * @param  T_DD_AUDIO_CTRL *ctrl_inf
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_dma_ctrl_dma_in(DdAudioDma *self, UINT8 ch, AudioDma* dma_setting)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);
	INT32 ret;

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_ctrl_dma_in:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (dma_setting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_ctrl_dma_in:dma_setting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	ret = dd_audio_set_enable_in_dma2ch(ch, dma_setting->dma2Ch);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_dma_ctrl_dma_in:dd_audio_set_enable_in_dma2ch() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_Dma_In[ch]->dma2Ch = dma_setting->dma2Ch;
	}

	if (dma_setting->dma2Ch == DdAudio_ENABLE){
		if ((dd_audio_get_enable_fifo_full_dma_in(ch) == FALSE) && (dd_audio_get_input_dma_request_enable(ch) == FALSE)){
			ret = dd_audio_set_in_dma_sample(ch, dma_setting->dmaTrnsfCnt);
			if (ret != D_DDIM_OK){
				Ddim_Print(("[DD_AUDIO]dd_audio_dma_ctrl_dma_in:dd_audio_set_in_dma_sample() = %x\n", ret));
				return ret;
			}
			else {
				priv->gDd_Audio_Dma_In[ch]->dmaTrnsfCnt = dma_setting->dmaTrnsfCnt;
			}
		}
		else {
			Ddim_Print(("[DD_AUDIO]dd_audio_dma_ctrl_dma_in:DMIE=%d, EDMIE=%d\n", dd_audio_get_enable_fifo_full_dma_in(ch), dd_audio_get_input_dma_request_enable(ch)));
			return DdAudio_SYSTEM_ERROR;
		}
	}

	return D_DDIM_OK;
}

/**
 * @brief  Get Audio DMA Information(Input)
 * @param  UINT8 ch
 * @param  T_DD_AUDIO_CTRL *ctrl_inf
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_dma_get_ctrl_dma_in(DdAudioDma *self, UINT8 ch, AudioDma* dma_setting)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_get_ctrl_dma_in:input channel error : %d\n", ch));
		*dma_setting = *priv->gDd_Audio_Dma_In[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (dma_setting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_ctrl_dma_in:dma_setting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*dma_setting = *priv->gDd_Audio_Dma_In[ch];

	return D_DDIM_OK;
}

/**
 * @brief  Set Audio DMA Information(Output)
 * @param  UINT8 ch
 * @param  T_DD_AUDIO_CTRL *ctrl_inf
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_dma_ctrl_dma_out(DdAudioDma *self, UINT8 ch, AudioDma* dma_setting)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);
	INT32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_ctrl_dma_out:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (dma_setting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_ctrl_dma_out:dma_setting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	ret = dd_audio_set_enable_out_dma2ch(ch, dma_setting->dma2Ch);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_dma_ctrl_dma_out:dd_audio_set_enable_out_dma2ch() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_Dma_Out[ch]->dma2Ch = dma_setting->dma2Ch;
	}

	if (dma_setting->dma2Ch == DdAudio_ENABLE){
		if ((dd_audio_get_enable_fifo_empty_dma_out(ch) == FALSE) && (dd_audio_get_output_dma_request_enable(ch) == FALSE)){
			ret = dd_audio_set_out_dma_sample(ch, dma_setting->dmaTrnsfCnt);
			if (ret != D_DDIM_OK){
				Ddim_Print(("[DD_AUDIO]dd_audio_dma_ctrl_dma_out:dd_audio_set_out_dma_sample() = %x\n", ret));
				return ret;
			}
			else {
				priv->gDd_Audio_Dma_Out[ch]->dmaTrnsfCnt = dma_setting->dmaTrnsfCnt;
			}
		}
		else {
			Ddim_Print(("[DD_AUDIO]dd_audio_dma_ctrl_dma_out:DMOE=%d, EDMOE=%d\n", dd_audio_get_enable_fifo_empty_dma_out(ch), dd_audio_get_output_dma_request_enable(ch)));
			return DdAudio_SYSTEM_ERROR;
		}
	}

	return D_DDIM_OK;
}

/**
 * @brief  Get Audio DMA Information(Output)
 * @param  UINT8 ch
 * @param  T_DD_AUDIO_CTRL *ctrl_inf
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_dma_get_ctrl_dma_out(DdAudioDma *self, UINT8 ch, AudioDma* dma_setting)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_get_ctrl_dma_out:input channel error : %d\n", ch));
		*dma_setting = *priv->gDd_Audio_Dma_Out[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (dma_setting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_get_ctrl_dma_out:dma_setting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*dma_setting = *priv->gDd_Audio_Dma_Out[ch];

	return D_DDIM_OK;
}

/**
 * @brief  Set register DMIE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_dma_set_enable_fifo_full_dmain(DdAudioDma *self, UINT8 ch, UINT8 enable)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_set_enable_fifo_full_dmain:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_set_enable_fifo_full_dmain:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return dd_audio_set_enable_fifo_full_dma_in(ch, enable);
}

/**
 * @brief  Set register DMOE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_dma_set_enable_fifo_empty_dma_out(DdAudioDma *self, UINT8 ch, UINT8 enable)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_set_enable_fifo_empty_dma_out:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_set_enable_fifo_empty_dma_out:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return ddAudioSetEnableFifoEmptyDmaOut(ch, enable);
}

/**
 * @brief  Set register EDMIE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_dma_set_input_dma_request_enable(DdAudioDma *self, UINT8 ch, UINT8 enable)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_set_input_dma_request_enable:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_set_input_dma_request_enable:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return ddDudioSetInputDmaRequestEnable(ch, enable);
}

/**
 * @brief  Set register EDMOE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_dma_set_output_dma_request_enable(DdAudioDma *self, UINT8 ch, UINT8 enable)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_set_output_dma_request_enable:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_set_output_dma_request_enable:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return ddAudioSetOutputDmaRequestEnable(ch, enable);
}

/**
 * @brief  Get register AUDMISAMPLE.
 * @param  UINT8 ch
 * @return UINT16 value of register AUDMISAMPLE.DMISPL
 */
UINT16 dd_audio_dma_get_in_dma_sample(DdAudioDma *self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_get_in_dma_sample:input channel error : %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	
	return IO_AUDIO.AUDIOIF[ch].AUDMISAMPLE.bit.DMISPL;
}

/**
 * @brief  Get register AUDMOSAMPLE.
 * @param  UINT8 ch
 * @return UINT16 value of register AUDMOSAMPLE
 */
UINT16 dd_audio_dma_get_out_dma_sample(DdAudioDma *self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_get_out_dma_sample:input channel error : %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	
	return IO_AUDIO.AUDIOIF[ch].AUDMOSAMPLE.bit.DMOSPL;
}

/**
 * @brief  Swap a reading value from AUIDLR by 1Byte unit.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_dma_set_swapbyte_auidlr(DdAudioDma *self, UINT8 ch, UINT8 enable)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_set_swapbyte_auidlr:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	return dd_audio_set_input_byte_swap(ch, enable);
}

/**
 * @brief  Swap a reading value from AUIDLR by 2Byte unit.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_dma_set_swap_hw_auidlr(DdAudioDma *self, UINT8 ch, UINT8 enable)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_set_swap_hw_auidlr:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	return dd_audio_set_input_hw_swap(ch, enable);
}

/**
 * @brief  Swap a writing value to AUIDLR by 1Byte unit.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_dma_set_swap_byte_auodlr(DdAudioDma *self, UINT8 ch, UINT8 enable)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Dd_Audio_SwapByte_AUODLR:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	return dd_audio_set_output_byte_swap(ch, enable);
}

/**
 * @brief  Swap a writing value to AUODLR by 2Byte unit.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_dma_set_swap_hw_auodlr(DdAudioDma *self, UINT8 ch, UINT8 enable)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Dd_Audio_SwapHW_AUODLR:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	return dd_audio_set_output_hw_swap(ch, enable);
}

void dd_audio_dma_set_in_2ch(DdAudioDma *self, UINT8 ch, UINT8 dma2ch)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);

	priv->gDd_Audio_Dma_In[ch]->dma2Ch = dma2ch;
}

void dd_audio_dma_set_in_trnsf_cnt(DdAudioDma *self, UINT8 ch, UINT16 trnsfCnt)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);

	priv->gDd_Audio_Dma_In[ch]->dmaTrnsfCnt = trnsfCnt;
}

void dd_audio_dma_set_out_2ch(DdAudioDma *self, UINT8 ch, UINT8 dma2ch)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);

	priv->gDd_Audio_Dma_Out[ch]->dma2Ch = dma2ch;
}

void dd_audio_dma_set_out_trnsf_cnt(DdAudioDma *self, UINT8 ch, UINT16 trnsfCnt)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);

	priv->gDd_Audio_Dma_Out[ch]->dmaTrnsfCnt = trnsfCnt;
}

DdAudioDma* dd_audio_dma_new(void)
{
	DdAudioDma* self = k_object_new_with_private(DD_TYPE_AUDIO_DMA, sizeof(DdAudioDmaPrivate));

	return self;
}

