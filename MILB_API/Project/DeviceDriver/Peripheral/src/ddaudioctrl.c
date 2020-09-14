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
#include "ddaudio.h"
#include "ddarm.h"
#include "ddaudioctrl.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudioCtrl, dd_audio_ctrl);
#define DD_AUDIO_CTRL_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioCtrlPrivate, DD_TYPE_AUDIO_CTRL))


struct _DdAudioCtrlPrivate
{
	volatile AudioCtrlCommon cmmnData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioCtrlIn inData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioCtrlOut outData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioCtrlCommon *cmmn[DdAudio_IF_CH_NUM_MAX];
	volatile AudioCtrlIn *in[DdAudio_IF_CH_NUM_MAX];
	volatile AudioCtrlOut *out[DdAudio_IF_CH_NUM_MAX];
};


static kint32 ddAudioSetInputRegisterFormat(kuint8 ch, kuint8 format);
static kint32 ddAudioSetOutputRegisterFormat(kuint8 ch, kuint8 format);
static kint32 ddAudioSetInFifo(kuint8 ch, kuint8 stage);
static kint32 ddAudioSetOutFifo(kuint8 ch, kuint8 stage);
static kint32 ddAudioSetStereo(kuint8 ch, kuint8 stereo);
static kboolean ddAudioGetStereo(kuint8 ch);
static kint32 ddAudioSetRegisterUsage(kuint8 ch, kuint8 control);
static kint32 ddAudioSetMixPlay(kuint8 ch, kuint8 control);
static kint32 ddAudioSetLrDataCopy(kuint8 ch, kuint8 copy);
static kint32 ddAudioSetInAhbFormat(kuint8 ch, kuint8 format);
static kint32 ddAudioSetOutAhbFormat(kuint8 ch, kuint8 format);
static kint32 ddAudioSetOutDataShift(kuint8 ch, kuint8 shift);
static kint32 ddAudioSetInDataShift(kuint8 ch, kuint8 shift);


static void dd_audio_ctrl_constructor(DdAudioCtrl *self)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdAudio_IF_CH_NUM_MAX; i++)
	{
		priv->cmmnData[i].fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
		priv->cmmnData[i].channel = DdAudioCtrl_CHANNEL_MONO;

		priv->inData[i].format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
		priv->inData[i].fifoStages = DdAudioCtrl_FIFO_STAGES_1;
		priv->inData[i].ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
		priv->inData[i].bitShift = DdAudioCtrl_BIT_SHIFT_0;

		priv->outData[i].format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
		priv->outData[i].fifoStages = DdAudioCtrl_FIFO_STAGES_1;
		priv->outData[i].ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
		priv->outData[i].lrCopy = DdAudio_DISABLE;
		priv->outData[i].mixPlay = DdAudio_DISABLE;
		priv->outData[i].bitShift = DdAudioCtrl_BIT_SHIFT_0;

		priv->cmmn[i] = &priv->cmmnData[i];
		priv->in[i] = &priv->inData[i];
		priv->out[i] = &priv->outData[i];
	}

}

static void dd_audio_ctrl_destructor(DdAudioCtrl *self)
{

}

/**
 * @brief  Set register AUIRF.
 * @param  kuint8 ch
 * @param  kuint8 format
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetInputRegisterFormat(kuint8 ch, kuint8 format)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucr aucr;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUIRF:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (format > 1){
		Ddim_Assertion(("[DD_AUDIO]Set AUIRF:input format error : %d\n", format));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucr.word = ioAudio.audioif[ch].aucr.word;

	if (aucr.bit.auirf != format){					/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUIRF Error: AUIEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			aucr.bit.auirf = format;
			ioAudio.audioif[ch].aucr.word = aucr.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register AUORF.
 * @param  kuint8 ch
 * @param  kuint8 format
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetOutputRegisterFormat(kuint8 ch, kuint8 format)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucr aucr;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUORF:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (format > 1){
		Ddim_Assertion(("[DD_AUDIO]Set AUORF:input format error : %d\n", format));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucr.word = ioAudio.audioif[ch].aucr.word;

	if (aucr.bit.auorf != format){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUORF Error:AUOEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUORF Error:LBF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			aucr.bit.auorf = format;
			ioAudio.audioif[ch].aucr.word = aucr.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register ISTG16.
 * @param  kuint8 ch
 * @param  kuint8 stage
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetInFifo(kuint8 ch, kuint8 stage)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAumd aumd;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set ISTG16:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (stage > 1){
		Ddim_Assertion(("[DD_AUDIO]Set ISTG16:input stage error : %d\n", stage));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aumd.word = ioAudio.audioif[ch].aumd.word;

	if (aumd.bit.istg16 != stage){							/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set ISTG16 Error:AUIEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.istg16 = stage;
			ioAudio.audioif[ch].aumd.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register OSTG16.
 * @param  kuint8 ch
 * @param  kuint8 stage
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetOutFifo(kuint8 ch, kuint8 stage)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAumd aumd;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set OSTG16:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (stage > 1){
		Ddim_Assertion(("[DD_AUDIO]Set OSTG16:input stage error : %d\n", stage));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aumd.word = ioAudio.audioif[ch].aumd.word;

	if (aumd.bit.ostg16 != stage){							/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set OSTG16 Error:AUOEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set OSTG16 Error:LBF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.ostg16 = stage;
			ioAudio.audioif[ch].aumd.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register STEREO.
 * @param  kuint8 ch
 * @param  kuint8 stereo
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetStereo(kuint8 ch, kuint8 stereo)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAumd aumd;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set STEREO:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (stereo > 1){
		Ddim_Assertion(("[DD_AUDIO]Set STEREO:input stereo error : %d\n", stereo));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aumd.word = ioAudio.audioif[ch].aumd.word;

	if (aumd.bit.stereo != stereo){								/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set STEREO Error:AUIEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set STEREO Error:AUOEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set STEREO Error:LBF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.stereo = stereo;
			ioAudio.audioif[ch].aumd.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Get register STEREO.
 * @param  kuint8 ch
 * @return TRUE/FALSE
 */
static kboolean ddAudioGetStereo(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get STEREO:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aumd.bit.stereo == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Set register ESTG.
 * @param  kuint8 ch
 * @param  kuint8 control
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetRegisterUsage(kuint8 ch, kuint8 control)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAust aust;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set ESTG:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (control > 3){
		Ddim_Assertion(("[DD_AUDIO]Set ESTG:input control error : %d\n", control));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aust.word = ioAudio.audioif[ch].aust.word;
	aust.bit.estg = control;
	ioAudio.audioif[ch].aust.word = aust.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register MIXPLAY.
 * @param  kuint8 ch
 * @param  kuint8 copy
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetMixPlay(kuint8 ch, kuint8 control)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAudp audp;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set MIXPLAY:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (control > 1){
		Ddim_Assertion(("[DD_AUDIO]Set MIXPLAY:input control error : %d\n", control));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	audp.word = ioAudio.audioif[ch].audp.word;

	if (audp.bit.mixplay != control){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set MIXPLAY Error:AUOEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else if (control == 1){
			if(ddAudioGetStereo(ch) == FALSE){
				Ddim_Print(("[DD_AUDIO]Set MIXPLAY Error. MIXPLAY = 1, STEREO = 0, ch = %d\n",ch));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else {
				audp.bit.mixplay = control;
				ioAudio.audioif[ch].audp.word = audp.word;
			}
		}
		else {
			audp.bit.mixplay = control;
			ioAudio.audioif[ch].audp.word = audp.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register AULRCP.
 * @param  kuint8 ch
 * @param  kuint8 copy
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetLrDataCopy(kuint8 ch, kuint8 copy)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAudp audp;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AULRCP:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (copy > 1){
		Ddim_Assertion(("[DD_AUDIO]Set AULRCP:input copy error : %d\n", copy));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	audp.word = ioAudio.audioif[ch].audp.word;

	if (audp.bit.aulrcp != copy){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AULRCP Error:AUOEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else if (copy == DdAudio_ENABLE){
			if (ioAudio.audioif[ch].aucc.bit.auckoe == 0){
				Ddim_Print(("[DD_AUDIO]Set AULRCP = 1, AUCKOE = 0, ch = %d\n",ch));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else {
				audp.bit.aulrcp = copy;
				ioAudio.audioif[ch].audp.word = audp.word;
			}
		}
		else {
			audp.bit.aulrcp = copy;
			ioAudio.audioif[ch].audp.word = audp.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register AUIDF.
 * @param  kuint8 ch
 * @param  kuint8 shift
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetInAhbFormat(kuint8 ch, kuint8 format)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAudp audp;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUIDF:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (format > 1){
		Ddim_Assertion(("[DD_AUDIO]Set AUIDF:input format error : %d\n", format));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	audp.word = ioAudio.audioif[ch].audp.word;

	if (audp.bit.auidf != format){								/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUIDF Error:AUIEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			audp.bit.auidf = format;
			ioAudio.audioif[ch].audp.word = audp.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register AUODF.
 * @param  kuint8 ch
 * @param  kuint8 shift
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetOutAhbFormat(kuint8 ch, kuint8 format)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAudp audp;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUODF:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (format > 1){
		Ddim_Assertion(("[DD_AUDIO]Set AUODF:input format error : %d\n", format));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	audp.word = ioAudio.audioif[ch].audp.word;

	if (audp.bit.auodf != format){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUODF Error:AUOEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			audp.bit.auodf = format;
			ioAudio.audioif[ch].audp.word = audp.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register AUODS.
 * @param  kuint8 ch
 * @param  kuint8 shift
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetOutDataShift(kuint8 ch, kuint8 shift)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAudp audp;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUODS:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (shift > 3){
		Ddim_Assertion(("[DD_AUDIO]Set AUODS:input shift error : %d\n", shift));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	audp.word = ioAudio.audioif[ch].audp.word;

	if (audp.bit.auods != shift){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUODS Error:AUOEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			audp.bit.auods = shift;
			ioAudio.audioif[ch].audp.word = audp.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register AUIDS.
 * @param  kuint8 ch
 * @param  kuint8 shift
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetInDataShift(kuint8 ch, kuint8 shift)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAudp audp;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUIDS : input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (shift > 3){
		Ddim_Assertion(("[DD_AUDIO]Set AUIDS : input shift error : %d\n", shift));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	audp.word = ioAudio.audioif[ch].audp.word;

	if (audp.bit.auids != shift){								/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUIDS Error:AUIEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			audp.bit.auids = shift;
			ioAudio.audioif[ch].audp.word = audp.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set Audio Control Information(common)
 * @param  kuint8 ch
 * @param  T_DD_AUDIO_CTRL *ctrl_inf
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_ctrl_ctrl_common(DdAudioCtrl *self, kuint8 ch, AudioCtrlCommon* ctrl_inf)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);
	kint32 ret;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_ctrl_common:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (ctrl_inf == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_ctrl_common:ctrl_inf = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	if (ctrl_inf->fifoUsage < DdAudioCtrl_FIFO_USAGE_STAGES_16){
		ret = ddAudioSetRegisterUsage(ch, ctrl_inf->fifoUsage);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_common:dd_audio_set_register_usage() = %x\n", ret));
			return ret;
		}
	}
	else if (ctrl_inf->fifoUsage == DdAudioCtrl_FIFO_USAGE_STAGES_16){
		;		// Do Nothing.
	}
	else {
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_ctrl_common:input fifoUsage error : %d\n", ctrl_inf->fifoUsage));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	priv->cmmn[ch]->fifoUsage = ctrl_inf->fifoUsage;
	
	if (ctrl_inf->channel <= DdAudioCtrl_CHANNEL_STEREO){
		ret = ddAudioSetStereo(ch, ctrl_inf->channel);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_common:dd_audio_set_stereo() = %x\n", ret));
			return ret;
		}
		else {
			priv->cmmn[ch]->channel = ctrl_inf->channel;
		}
	}
	else {
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_ctrl_common:input audio channel error : %d\n", ctrl_inf->channel));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get Audio Control Information(common)
 * @param  kuint8 ch
 * @param  AudioCtrlCommon* ctrl_inf
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_ctrl_get_ctrl_common(DdAudioCtrl *self, kuint8 ch, AudioCtrlCommon* ctrl_inf)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_get_ctrl_common:input channel error : %d\n", ch));
		*ctrl_inf = *priv->cmmn[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (ctrl_inf == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_get_ctrl_common:ctrl_inf = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	*ctrl_inf = *priv->cmmn[ch];
	
	return D_DDIM_OK;
}

/**
 * @brief  Set Audio Control Information(input)
 * @param  kuint8 ch
 * @param  AudioCtrlIn *ctrl_inf
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_ctrl_ctrl_input(DdAudioCtrl *self, kuint8 ch, AudioCtrlIn* ctrl_inf)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);
	kint32 ret;
	
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_ctrl_input:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (ctrl_inf == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_ctrl_input:ctrl_inf = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	ret = ddAudioSetInputRegisterFormat(ch, ctrl_inf->format);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_input:dd_audio_set_input_register_format() = %x\n", ret));
		return ret;
	}
	else {
		priv->in[ch]->format = ctrl_inf->format;
	}
	
	ret = ddAudioSetInFifo(ch, ctrl_inf->fifoStages);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_input:dd_audio_set_in_fifo() = %x\n", ret));
		return ret;
	}
	else {
		priv->in[ch]->fifoStages = ctrl_inf->fifoStages;
	}
	
	ret = ddAudioSetInAhbFormat(ch, ctrl_inf->ahbFormat);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_input:dd_audio_set_in_ahb_format() = %x\n", ret));
		return ret;
	}
	else {
		priv->in[ch]->ahbFormat = ctrl_inf->ahbFormat;
	}

	ret = ddAudioSetInDataShift(ch, ctrl_inf->bitShift);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_input:dd_audio_set_in_data_shift() = %x\n", ret));
		return ret;
	}
	else {
		priv->in[ch]->bitShift = ctrl_inf->bitShift;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get Audio Control Information(input)
 * @param  kuint8 ch
 * @param  AudioCtrlIn *ctrl_inf
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_ctrl_get_ctrl_input(DdAudioCtrl *self, kuint8 ch, AudioCtrlIn* ctrl_inf)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_get_ctrl_input:input channel error : %d\n", ch));
		*ctrl_inf = *priv->in[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (ctrl_inf == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_get_ctrl_input:ctrl_inf = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	*ctrl_inf = *priv->in[ch];
	return D_DDIM_OK;
}

/**
 * @brief  Set Audio Control Information(output)
 * @param  kuint8 ch
 * @param  AudioCtrlOut *ctrl_inf
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_ctrl_ctrl_output(DdAudioCtrl *self, kuint8 ch, AudioCtrlOut* ctrl_inf)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);
	DdAudio* ddAudio = dd_audio_get();
	kint32 ret;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (ctrl_inf == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:ctrl_inf = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	ret = ddAudioSetOutputRegisterFormat(ch, ctrl_inf->format);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:dd_audio_set_output_register_format() = %x\n", ret));
		return ret;
	}
	else {
		priv->out[ch]->format = ctrl_inf->format;
	}
	
	ret = ddAudioSetOutFifo(ch, ctrl_inf->fifoStages);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:dd_audio_set_out_fifo() = %x\n", ret));
		return ret;
	}
	else {
		priv->out[ch]->fifoStages = ctrl_inf->fifoStages;
	}
	
	ret = ddAudioSetOutAhbFormat(ch, ctrl_inf->ahbFormat);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:dd_audio_set_out_ahb_format() = %x\n", ret));
		return ret;
	}
	else {
		priv->out[ch]->ahbFormat = ctrl_inf->ahbFormat;
	}
	
	if ((ctrl_inf->lrCopy == DdAudio_ENABLE) && (dd_audio_get_cmmn_master_slave(ddAudio, ch) == DdAudioI2s_CLK_SLAVE)){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output: [SlaveMode] LR Copy Enable\n"));
		return DdAudio_SYSTEM_ERROR;
	}
	
	ret = ddAudioSetLrDataCopy(ch, ctrl_inf->lrCopy);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:dd_audio_set_lr_data_copy() = %x\n", ret));
		return ret;
	}
	else {
		priv->out[ch]->lrCopy = ctrl_inf->lrCopy;
	}
	
	ret = ddAudioSetMixPlay(ch, ctrl_inf->mixPlay);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:dd_audio_set_mix_play() = %x\n", ret));
		return ret;
	}
	else {
		priv->out[ch]->mixPlay = ctrl_inf->mixPlay;
	}
	
	ret = ddAudioSetOutDataShift(ch, ctrl_inf->bitShift);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:dd_audio_set_out_data_shift() = %x\n", ret));
		return ret;
	}
	else {
		priv->out[ch]->bitShift = ctrl_inf->bitShift;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get Audio Control Information(output)
 * @param  kuint8 ch
 * @param  AudioCtrlOut *ctrl_inf
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_ctrl_get_ctrl_output(DdAudioCtrl *self, kuint8 ch, AudioCtrlOut* ctrl_inf)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_get_ctrl_output:input channel error : %d\n", ch));
		*ctrl_inf = *priv->out[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (ctrl_inf == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_get_ctrl_output:ctrl_inf = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	*ctrl_inf = *priv->out[ch];
	
	return D_DDIM_OK;
}

void dd_audio_ctrl_set_cmmn_fifo_usage(DdAudioCtrl *self, int index, AudioFifoUsage fifoUsage)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->cmmn[index]->fifoUsage = fifoUsage;
}

void dd_audio_ctrl_set_cmmn_channel(DdAudioCtrl *self, int index, AudioChannel channel)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->cmmn[index]->channel = channel;
}

AudioFifoUsage dd_audio_ctrl_get_cmmn_fifo_usage(DdAudioCtrl *self, int index)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	return priv->cmmn[index]->fifoUsage;
}

AudioChannel dd_audio_ctrl_get_cmmn_channel(DdAudioCtrl *self, int index)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	return priv->cmmn[index]->channel;
}

void dd_audio_ctrl_set_in_format(DdAudioCtrl *self, int index, AudioDataRegFrmt format)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->in[index]->format = format;
}

void dd_audio_ctrl_set_in_fifo_stages(DdAudioCtrl *self, int index, AudioFifoStages fifoStages)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->in[index]->fifoStages = fifoStages;
}

void dd_audio_ctrl_set_in_ahb_format(DdAudioCtrl *self, int index, AudioAhbFrmt ahbFormat)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->in[index]->ahbFormat = ahbFormat;
}

void dd_audio_ctrl_set_in_bit_shift(DdAudioCtrl *self, int index, AudioBitShift bitShift)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->in[index]->bitShift = bitShift;
}

AudioFifoStages dd_audio_ctrl_get_in_fifo_stages(DdAudioCtrl *self, int index)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	return priv->in[index]->fifoStages;
}

void dd_audio_ctrl_set_out_format(DdAudioCtrl *self, int index, AudioDataRegFrmt format)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->out[index]->format = format;
}

void dd_audio_ctrl_set_out_fifo_stages(DdAudioCtrl *self, int index, AudioFifoStages fifoStages)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->out[index]->fifoStages = fifoStages;
}

void dd_audio_ctrl_set_out_ahb_format(DdAudioCtrl *self, int index, AudioAhbFrmt ahbFormat)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->out[index]->ahbFormat = ahbFormat;
}

void dd_audio_ctrl_set_out_lr_copy(DdAudioCtrl *self, int index, kuint8 lrCopy)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->out[index]->lrCopy = lrCopy;
}

void dd_audio_ctrl_set_out_mix_play(DdAudioCtrl *self, int index, kuint8 mixPlay)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->out[index]->mixPlay = mixPlay;
}

void dd_audio_ctrl_set_out_bit_shift(DdAudioCtrl *self, int index, AudioBitShift bitShift)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->out[index]->bitShift = bitShift;
}

AudioFifoStages dd_audio_ctrl_get_out_fifo_stages(DdAudioCtrl *self, int index)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	return priv->out[index]->fifoStages;
}

DdAudioCtrl* dd_audio_ctrl_new(void)
{
	DdAudioCtrl* self = k_object_new_with_private(DD_TYPE_AUDIO_CTRL, sizeof(DdAudioCtrlPrivate));

	return self;
}

