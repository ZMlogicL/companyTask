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
#include "ddarm.h"
#include "ddaudio.h"
#include "ddaudiodma.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudioDma, dd_audio_dma);
#define DD_AUDIO_DMA_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioDmaPrivate, DD_TYPE_AUDIO_DMA))


struct _DdAudioDmaPrivate
{
	volatile AudioDma inData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioDma outData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioDma	*in[DdAudio_IF_CH_NUM_MAX];
	volatile AudioDma	*out[DdAudio_IF_CH_NUM_MAX];
};


static kint32 ddAudioSetEnableFifoFullDmaIn(kuint8 ch, kuint8 enable);
static kint32 ddAudioSetEnableFifoEmptyDmaOut(kuint8 ch, kuint8 enable);
static kboolean ddAudioGetEnableFifoEmptyDmaOut(kuint8 ch);
static kint32 ddDudioSetInputDmaRequestEnable(kuint8 ch, kuint8 enable);
static kint32 ddAudioSetOutputDmaRequestEnable(kuint8 ch, kuint8 enable);
static kint32 ddAudioSetInputByteSwap(kuint8 ch, kuint8 enable);
static kint32 ddAudioSetInputHwSwap(kuint8 ch, kuint8 enable);
static kint32 ddAudioSetOutputByteSwap(kuint8 ch, kuint8 enable);
static kint32 ddAudioSetOutputHwSwap(kuint8 ch, kuint8 enable);
static kint32 ddAudioSetEnableInDma2ch(kuint8 ch, kuint8 enable);
static kint32 ddAudioSetEnableOutDma2ch(kuint8 ch, kuint8 enable);
static kint32 ddAudioSetInDmaSample(kuint8 ch, UINT16 sample);
static kint32 ddAudioSetOutDmaSample(kuint8 ch, UINT16 sample);
static kboolean ddAudioGetInputDmaRequestEnable(kuint8 ch);
static kboolean ddAudioGetOutputDmaRequestEnable(kuint8 ch);
static kboolean ddAudioGetEnableFifoFullDmaIn(kuint8 ch);

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

		priv->in[i] = &priv->inData[i];
		priv->out[i] = &priv->outData[i];
	}
}

static void dd_audio_dma_destructor(DdAudioDma *self)
{

}

/**
 * @brief  Set register DMIE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetEnableFifoFullDmaIn(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucr aucr;
	kint32 retVal = D_DDIM_OK;

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

	aucr.word = ioAudio.audioif[ch].aucr.word;

	if (aucr.bit.dmie != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (ddAudioGetInputDmaRequestEnable(ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set DMIE Error:EDMIE = 1\n"));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else {
				aucr.bit.dmie = enable;
				ioAudio.audioif[ch].aucr.word = aucr.word;
			}
		}
		else {
			aucr.bit.dmie = enable;
			ioAudio.audioif[ch].aucr.word = aucr.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register DMOE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetEnableFifoEmptyDmaOut(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucr aucr;
	kint32 retVal = D_DDIM_OK;

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

	aucr.word = ioAudio.audioif[ch].aucr.word;

	if (aucr.bit.dmoe != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (ddAudioGetOutputDmaRequestEnable(ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set DMOE Error:EDMOE = 1\n"));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else {
				aucr.bit.dmoe = enable;
				ioAudio.audioif[ch].aucr.word = aucr.word;
			}
		}
		else {
			aucr.bit.dmoe = enable;
			ioAudio.audioif[ch].aucr.word = aucr.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Get register DMOE.
 * @param  kuint8 ch
 * @return kboolean TRUE/FALSE
 */
static kboolean ddAudioGetEnableFifoEmptyDmaOut(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get DMOE:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aucr.bit.dmoe == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Set register IBYTE_SWP.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetInputByteSwap(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAumd aumd;
	kint32 retVal = D_DDIM_OK;

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

	aumd.word = ioAudio.audioif[ch].aumd.word;

	if (aumd.bit.ibyteSwp != enable){								/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set IBYTE_SWP Error:AUIEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.ibyteSwp = enable;
			ioAudio.audioif[ch].aumd.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register IHW_SWP.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetInputHwSwap(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAumd aumd;
	kint32 retVal = D_DDIM_OK;

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

	aumd.word = ioAudio.audioif[ch].aumd.word;

	if (aumd.bit.ihwSwp != enable){								/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set IHW_SWP Error:AUIEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.ihwSwp = enable;
			ioAudio.audioif[ch].aumd.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register OBYTE_SWP.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetOutputByteSwap(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAumd aumd;
	kint32 retVal = D_DDIM_OK;

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

	aumd.word = ioAudio.audioif[ch].aumd.word;

	if (aumd.bit.obyteSwp != enable){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set OBYTE_SWP Error:AUOEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set OBYTE_SWP Error:LBF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.obyteSwp = enable;
			ioAudio.audioif[ch].aumd.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register OHW_SWP.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetOutputHwSwap(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAumd aumd;
	kint32 retVal = D_DDIM_OK;

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

	aumd.word = ioAudio.audioif[ch].aumd.word;

	if (aumd.bit.ohwSwp != enable){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set OHW_SWP Error:AUOEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set OHW_SWP Error:LBF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.ohwSwp = enable;
			ioAudio.audioif[ch].aumd.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register EDMIE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddDudioSetInputDmaRequestEnable(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAust aust;
	kint32 retVal = D_DDIM_OK;

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

	aust.word = ioAudio.audioif[ch].aust.word;

	if (aust.bit.edmie != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (ddAudioGetEnableFifoFullDmaIn(ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set EDMIE Error:DMIE = 1\n"));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else {
				aust.bit.edmie = enable;
				ioAudio.audioif[ch].aust.word = aust.word;
			}
		}
		else {
			aust.bit.edmie = enable;
			ioAudio.audioif[ch].aust.word = aust.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register EDMOE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetOutputDmaRequestEnable(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAust aust;
	kint32 retVal = D_DDIM_OK;

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

	aust.word = ioAudio.audioif[ch].aust.word;

	if (aust.bit.edmoe != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (ddAudioGetEnableFifoEmptyDmaOut(ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set EDMOE Error:DMOE = 1\n"));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else {
				aust.bit.edmoe = enable;
				ioAudio.audioif[ch].aust.word = aust.word;
			}
		}
		else {
			aust.bit.edmoe = enable;
			ioAudio.audioif[ch].aust.word = aust.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register DMI2CHEN.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetEnableInDma2ch(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAudma2ctl audma2ctl;

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

	audma2ctl.word = ioAudio.audioif[ch].audma2ctl.word;
	audma2ctl.bit.dmi2chen = enable;
	ioAudio.audioif[ch].audma2ctl.word = audma2ctl.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register DMO2CHEN.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetEnableOutDma2ch(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAudma2ctl audma2ctl;

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

	audma2ctl.word = ioAudio.audioif[ch].audma2ctl.word;
	audma2ctl.bit.dmo2chen = enable;
	ioAudio.audioif[ch].audma2ctl.word = audma2ctl.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register DMISPL.
 * @param  kuint8 ch
 * @param  UINT16 sample
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetInDmaSample(kuint8 ch, UINT16 sample)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set DMISPL:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	ioAudio.audioif[ch].audmisample.bit.dmispl = sample;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register DMOSPL.
 * @param  kuint8 ch
 * @param  UINT16 sample
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetOutDmaSample(kuint8 ch, UINT16 sample)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set DMOSPL : input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	ioAudio.audioif[ch].audmosample.bit.dmospl = sample;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Get register EDMIE.
 * @param  kuint8 ch
 * @return kboolean TRUE/FALSE
 */
static kboolean ddAudioGetInputDmaRequestEnable(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get EDMIE:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aust.bit.edmie == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register EDMOE.
 * @param  kuint8 ch
 * @return kboolean TRUE/FALSE
 */
static kboolean ddAudioGetOutputDmaRequestEnable(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get EDMOE:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aust.bit.edmoe == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register DMIE.
 * @param  kuint8 ch
 * @return kboolean TRUE/FALSE
 */
static kboolean ddAudioGetEnableFifoFullDmaIn(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get DMIE:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aucr.bit.dmie == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Set Audio DMA Information of Input
 * @param  kuint8 ch
 * @param  T_DD_AUDIO_CTRL *ctrl_inf
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_dma_ctrl_dma_in(DdAudioDma *self, kuint8 ch, AudioDma* dma_setting)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);
	kint32 ret;

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

	ret = ddAudioSetEnableInDma2ch(ch, dma_setting->dma2Ch);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_dma_ctrl_dma_in:dd_audio_set_enable_in_dma2ch() = %x\n", ret));
		return ret;
	}
	else {
		priv->in[ch]->dma2Ch = dma_setting->dma2Ch;
	}

	if (dma_setting->dma2Ch == DdAudio_ENABLE){
		if ((ddAudioGetEnableFifoFullDmaIn(ch) == FALSE) && (ddAudioGetInputDmaRequestEnable(ch) == FALSE)){
			ret = ddAudioSetInDmaSample(ch, dma_setting->dmaTrnsfCnt);
			if (ret != D_DDIM_OK){
				Ddim_Print(("[DD_AUDIO]dd_audio_dma_ctrl_dma_in:dd_audio_set_in_dma_sample() = %x\n", ret));
				return ret;
			}
			else {
				priv->in[ch]->dmaTrnsfCnt = dma_setting->dmaTrnsfCnt;
			}
		}
		else {
			Ddim_Print(("[DD_AUDIO]dd_audio_dma_ctrl_dma_in:DMIE=%d, EDMIE=%d\n", ddAudioGetEnableFifoFullDmaIn(ch), ddAudioGetInputDmaRequestEnable(ch)));
			return DdAudio_SYSTEM_ERROR;
		}
	}

	return D_DDIM_OK;
}

/**
 * @brief  Get Audio DMA Information(Input)
 * @param  kuint8 ch
 * @param  T_DD_AUDIO_CTRL *ctrl_inf
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_dma_get_ctrl_dma_in(DdAudioDma *self, kuint8 ch, AudioDma* dma_setting)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_get_ctrl_dma_in:input channel error : %d\n", ch));
		*dma_setting = *priv->in[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (dma_setting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_ctrl_dma_in:dma_setting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*dma_setting = *priv->in[ch];

	return D_DDIM_OK;
}

/**
 * @brief  Set Audio DMA Information(Output)
 * @param  kuint8 ch
 * @param  T_DD_AUDIO_CTRL *ctrl_inf
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_dma_ctrl_dma_out(DdAudioDma *self, kuint8 ch, AudioDma* dma_setting)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);
	kint32 ret;

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

	ret = ddAudioSetEnableOutDma2ch(ch, dma_setting->dma2Ch);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_dma_ctrl_dma_out:dd_audio_set_enable_out_dma2ch() = %x\n", ret));
		return ret;
	}
	else {
		priv->out[ch]->dma2Ch = dma_setting->dma2Ch;
	}

	if (dma_setting->dma2Ch == DdAudio_ENABLE){
		if ((ddAudioGetEnableFifoEmptyDmaOut(ch) == FALSE) && (ddAudioGetOutputDmaRequestEnable(ch) == FALSE)){
			ret = ddAudioSetOutDmaSample(ch, dma_setting->dmaTrnsfCnt);
			if (ret != D_DDIM_OK){
				Ddim_Print(("[DD_AUDIO]dd_audio_dma_ctrl_dma_out:dd_audio_set_out_dma_sample() = %x\n", ret));
				return ret;
			}
			else {
				priv->out[ch]->dmaTrnsfCnt = dma_setting->dmaTrnsfCnt;
			}
		}
		else {
			Ddim_Print(("[DD_AUDIO]dd_audio_dma_ctrl_dma_out:DMOE=%d, EDMOE=%d\n", ddAudioGetEnableFifoEmptyDmaOut(ch), ddAudioGetOutputDmaRequestEnable(ch)));
			return DdAudio_SYSTEM_ERROR;
		}
	}

	return D_DDIM_OK;
}

/**
 * @brief  Get Audio DMA Information(Output)
 * @param  kuint8 ch
 * @param  T_DD_AUDIO_CTRL *ctrl_inf
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_dma_get_ctrl_dma_out(DdAudioDma *self, kuint8 ch, AudioDma* dma_setting)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_get_ctrl_dma_out:input channel error : %d\n", ch));
		*dma_setting = *priv->out[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (dma_setting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_get_ctrl_dma_out:dma_setting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*dma_setting = *priv->out[ch];

	return D_DDIM_OK;
}

/**
 * @brief  Set register DMIE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_dma_set_enable_fifo_full_dmain(DdAudioDma *self, kuint8 ch, kuint8 enable)
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

	return ddAudioSetEnableFifoFullDmaIn(ch, enable);
}

/**
 * @brief  Set register DMOE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_dma_set_enable_fifo_empty_dma_out(DdAudioDma *self, kuint8 ch, kuint8 enable)
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
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_dma_set_input_dma_request_enable(DdAudioDma *self, kuint8 ch, kuint8 enable)
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
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_dma_set_output_dma_request_enable(DdAudioDma *self, kuint8 ch, kuint8 enable)
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
 * @param  kuint8 ch
 * @return UINT16 value of register AUDMISAMPLE.dmispl
 */
UINT16 dd_audio_dma_get_in_dma_sample(DdAudioDma *self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_get_in_dma_sample:input channel error : %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	
	return ioAudio.audioif[ch].audmisample.bit.dmispl;
}

/**
 * @brief  Get register AUDMOSAMPLE.
 * @param  kuint8 ch
 * @return UINT16 value of register AUDMOSAMPLE
 */
UINT16 dd_audio_dma_get_out_dma_sample(DdAudioDma *self, kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_get_out_dma_sample:input channel error : %d\n", ch));
		return 0;
	}
#endif	// CO_PARAM_CHECK
	
	return ioAudio.audioif[ch].audmosample.bit.dmospl;
}

/**
 * @brief  Swap a reading value from AUIDLR by 1Byte unit.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_dma_set_swapbyte_auidlr(DdAudioDma *self, kuint8 ch, kuint8 enable)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_set_swapbyte_auidlr:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	return ddAudioSetInputByteSwap(ch, enable);
}

/**
 * @brief  Swap a reading value from AUIDLR by 2Byte unit.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_dma_set_swap_hw_auidlr(DdAudioDma *self, kuint8 ch, kuint8 enable)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_dma_set_swap_hw_auidlr:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	return ddAudioSetInputHwSwap(ch, enable);
}

/**
 * @brief  Swap a writing value to AUIDLR by 1Byte unit.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_dma_set_swap_byte_auodlr(DdAudioDma *self, kuint8 ch, kuint8 enable)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Dd_Audio_SwapByte_AUODLR:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	return ddAudioSetOutputByteSwap(ch, enable);
}

/**
 * @brief  Swap a writing value to AUODLR by 2Byte unit.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_dma_set_swap_hw_auodlr(DdAudioDma *self, kuint8 ch, kuint8 enable)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Dd_Audio_SwapHW_AUODLR:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	return ddAudioSetOutputHwSwap(ch, enable);
}

void dd_audio_dma_set_in_2ch(DdAudioDma *self, kuint8 ch, kuint8 dma2ch)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);

	priv->in[ch]->dma2Ch = dma2ch;
}

void dd_audio_dma_set_in_trnsf_cnt(DdAudioDma *self, kuint8 ch, UINT16 trnsfCnt)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);

	priv->in[ch]->dmaTrnsfCnt = trnsfCnt;
}

void dd_audio_dma_set_out_2ch(DdAudioDma *self, kuint8 ch, kuint8 dma2ch)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);

	priv->out[ch]->dma2Ch = dma2ch;
}

void dd_audio_dma_set_out_trnsf_cnt(DdAudioDma *self, kuint8 ch, UINT16 trnsfCnt)
{
	DdAudioDmaPrivate *priv = DD_AUDIO_DMA_GET_PRIVATE(self);

	priv->out[ch]->dmaTrnsfCnt = trnsfCnt;
}

DdAudioDma* dd_audio_dma_new(void)
{
	DdAudioDma* self = k_object_new_with_private(DD_TYPE_AUDIO_DMA, sizeof(DdAudioDmaPrivate));

	return self;
}

