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
#include "dd_arm.h"
#include "ddaudioctrl.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudioCtrl, dd_audio_ctrl);
#define DD_AUDIO_CTRL_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioCtrlPrivate, DD_TYPE_AUDIO_CTRL))


struct _DdAudioCtrlPrivate
{
	volatile AudioCtrlCommon	cmmnData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioCtrlIn	inData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioCtrlOut outData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioCtrlCommon	*gDd_Audio_Ctrl_Cmmn[DdAudio_IF_CH_NUM_MAX];
	volatile AudioCtrlIn *gDd_Audio_Ctrl_In[DdAudio_IF_CH_NUM_MAX];
	volatile AudioCtrlOut *gDd_Audio_Ctrl_Out[DdAudio_IF_CH_NUM_MAX];
};


static INT32 dd_audio_set_input_register_format(UINT8 ch, UINT8 format);
static INT32 dd_audio_set_output_register_format(UINT8 ch, UINT8 format);
static INT32 dd_audio_set_in_fifo(UINT8 ch, UINT8 stage);
static INT32 dd_audio_set_out_fifo(UINT8 ch, UINT8 stage);
static INT32 dd_audio_set_stereo(UINT8 ch, UINT8 stereo);
static BOOL dd_audio_get_stereo(UINT8 ch);
static INT32 dd_audio_set_register_usage(UINT8 ch, UINT8 control);
static INT32 dd_audio_set_mix_play(UINT8 ch, UINT8 control);
static INT32 dd_audio_set_lr_data_copy(UINT8 ch, UINT8 copy);
static INT32 dd_audio_set_in_ahb_format(UINT8 ch, UINT8 format);
static INT32 dd_audio_set_out_ahb_format(UINT8 ch, UINT8 format);
static INT32 dd_audio_set_out_data_shift(UINT8 ch, UINT8 shift);
static INT32 dd_audio_set_in_data_shift(UINT8 ch, UINT8 shift);


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

		priv->gDd_Audio_Ctrl_Cmmn[i] = &priv->cmmnData[i];
		priv->gDd_Audio_Ctrl_In[i] = &priv->inData[i];
		priv->gDd_Audio_Ctrl_Out[i] = &priv->outData[i];
	}

}

static void dd_audio_ctrl_destructor(DdAudioCtrl *self)
{

}

/**
 * @brief  Set register AUIRF.
 * @param  UINT8 ch
 * @param  UINT8 format
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_input_register_format(UINT8 ch, UINT8 format)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucr aucr;
	INT32 ret_val = D_DDIM_OK;

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

	aucr.word = IO_AUDIO.AUDIOIF[ch].AUCR.word;

	if (aucr.bit.AUIRF != format){					/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUIRF Error: AUIEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			aucr.bit.AUIRF = format;
			IO_AUDIO.AUDIOIF[ch].AUCR.word = aucr.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register AUORF.
 * @param  UINT8 ch
 * @param  UINT8 format
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_output_register_format(UINT8 ch, UINT8 format)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucr aucr;
	INT32 ret_val = D_DDIM_OK;

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

	aucr.word = IO_AUDIO.AUDIOIF[ch].AUCR.word;

	if (aucr.bit.AUORF != format){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUORF Error:AUOEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUORF Error:LBF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			aucr.bit.AUORF = format;
			IO_AUDIO.AUDIOIF[ch].AUCR.word = aucr.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register ISTG16.
 * @param  UINT8 ch
 * @param  UINT8 stage
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_in_fifo(UINT8 ch, UINT8 stage)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aumd aumd;
	INT32 ret_val = D_DDIM_OK;

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

	aumd.word = IO_AUDIO.AUDIOIF[ch].AUMD.word;

	if (aumd.bit.ISTG16 != stage){							/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set ISTG16 Error:AUIEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.ISTG16 = stage;
			IO_AUDIO.AUDIOIF[ch].AUMD.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register OSTG16.
 * @param  UINT8 ch
 * @param  UINT8 stage
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_out_fifo(UINT8 ch, UINT8 stage)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aumd aumd;
	INT32 ret_val = D_DDIM_OK;

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

	aumd.word = IO_AUDIO.AUDIOIF[ch].AUMD.word;

	if (aumd.bit.OSTG16 != stage){							/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set OSTG16 Error:AUOEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set OSTG16 Error:LBF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.OSTG16 = stage;
			IO_AUDIO.AUDIOIF[ch].AUMD.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register STEREO.
 * @param  UINT8 ch
 * @param  UINT8 stereo
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_stereo(UINT8 ch, UINT8 stereo)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aumd aumd;
	INT32 ret_val = D_DDIM_OK;

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

	aumd.word = IO_AUDIO.AUDIOIF[ch].AUMD.word;

	if (aumd.bit.STEREO != stereo){								/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set STEREO Error:AUIEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set STEREO Error:AUOEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set STEREO Error:LBF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			aumd.bit.STEREO = stereo;
			IO_AUDIO.AUDIOIF[ch].AUMD.word = aumd.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Get register STEREO.
 * @param  UINT8 ch
 * @return TRUE/FALSE
 */
static BOOL dd_audio_get_stereo(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get STEREO:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Set register ESTG.
 * @param  UINT8 ch
 * @param  UINT8 control
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_register_usage(UINT8 ch, UINT8 control)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aust aust;

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

	aust.word = IO_AUDIO.AUDIOIF[ch].AUST.word;
	aust.bit.ESTG = control;
	IO_AUDIO.AUDIOIF[ch].AUST.word = aust.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register MIXPLAY.
 * @param  UINT8 ch
 * @param  UINT8 copy
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_mix_play(UINT8 ch, UINT8 control)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_audp audp;
	INT32 ret_val = D_DDIM_OK;

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

	audp.word = IO_AUDIO.AUDIOIF[ch].AUDP.word;

	if (audp.bit.MIXPLAY != control){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set MIXPLAY Error:AUOEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else if (control == 1){
			if(dd_audio_get_stereo(ch) == FALSE){
				Ddim_Print(("[DD_AUDIO]Set MIXPLAY Error. MIXPLAY = 1, STEREO = 0, ch = %d\n",ch));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else {
				audp.bit.MIXPLAY = control;
				IO_AUDIO.AUDIOIF[ch].AUDP.word = audp.word;
			}
		}
		else {
			audp.bit.MIXPLAY = control;
			IO_AUDIO.AUDIOIF[ch].AUDP.word = audp.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register AULRCP.
 * @param  UINT8 ch
 * @param  UINT8 copy
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_lr_data_copy(UINT8 ch, UINT8 copy)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_audp audp;
	INT32 ret_val = D_DDIM_OK;

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

	audp.word = IO_AUDIO.AUDIOIF[ch].AUDP.word;

	if (audp.bit.AULRCP != copy){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AULRCP Error:AUOEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else if (copy == DdAudio_ENABLE){
			if (IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE == 0){
				Ddim_Print(("[DD_AUDIO]Set AULRCP = 1, AUCKOE = 0, ch = %d\n",ch));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else {
				audp.bit.AULRCP = copy;
				IO_AUDIO.AUDIOIF[ch].AUDP.word = audp.word;
			}
		}
		else {
			audp.bit.AULRCP = copy;
			IO_AUDIO.AUDIOIF[ch].AUDP.word = audp.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register AUIDF.
 * @param  UINT8 ch
 * @param  UINT8 shift
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_in_ahb_format(UINT8 ch, UINT8 format)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_audp audp;
	INT32 ret_val = D_DDIM_OK;

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

	audp.word = IO_AUDIO.AUDIOIF[ch].AUDP.word;

	if (audp.bit.AUIDF != format){								/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUIDF Error:AUIEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			audp.bit.AUIDF = format;
			IO_AUDIO.AUDIOIF[ch].AUDP.word = audp.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register AUODF.
 * @param  UINT8 ch
 * @param  UINT8 shift
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_out_ahb_format(UINT8 ch, UINT8 format)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_audp audp;
	INT32 ret_val = D_DDIM_OK;

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

	audp.word = IO_AUDIO.AUDIOIF[ch].AUDP.word;

	if (audp.bit.AUODF != format){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUODF Error:AUOEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			audp.bit.AUODF = format;
			IO_AUDIO.AUDIOIF[ch].AUDP.word = audp.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register AUODS.
 * @param  UINT8 ch
 * @param  UINT8 shift
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_out_data_shift(UINT8 ch, UINT8 shift)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_audp audp;
	INT32 ret_val = D_DDIM_OK;

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

	audp.word = IO_AUDIO.AUDIOIF[ch].AUDP.word;

	if (audp.bit.AUODS != shift){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUODS Error:AUOEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			audp.bit.AUODS = shift;
			IO_AUDIO.AUDIOIF[ch].AUDP.word = audp.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register AUIDS.
 * @param  UINT8 ch
 * @param  UINT8 shift
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_in_data_shift(UINT8 ch, UINT8 shift)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_audp audp;
	INT32 ret_val = D_DDIM_OK;

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

	audp.word = IO_AUDIO.AUDIOIF[ch].AUDP.word;

	if (audp.bit.AUIDS != shift){								/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUIDS Error:AUIEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			audp.bit.AUIDS = shift;
			IO_AUDIO.AUDIOIF[ch].AUDP.word = audp.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set Audio Control Information(common)
 * @param  UINT8 ch
 * @param  T_DD_AUDIO_CTRL *ctrl_inf
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_ctrl_ctrl_common(DdAudioCtrl *self, UINT8 ch, AudioCtrlCommon* ctrl_inf)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);
	INT32 ret;
	
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
		ret = dd_audio_set_register_usage(ch, ctrl_inf->fifoUsage);
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
	
	priv->gDd_Audio_Ctrl_Cmmn[ch]->fifoUsage = ctrl_inf->fifoUsage;
	
	if (ctrl_inf->channel <= DdAudioCtrl_CHANNEL_STEREO){
		ret = dd_audio_set_stereo(ch, ctrl_inf->channel);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_common:dd_audio_set_stereo() = %x\n", ret));
			return ret;
		}
		else {
			priv->gDd_Audio_Ctrl_Cmmn[ch]->channel = ctrl_inf->channel;
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
 * @param  UINT8 ch
 * @param  AudioCtrlCommon* ctrl_inf
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_ctrl_get_ctrl_common(DdAudioCtrl *self, UINT8 ch, AudioCtrlCommon* ctrl_inf)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_get_ctrl_common:input channel error : %d\n", ch));
		*ctrl_inf = *priv->gDd_Audio_Ctrl_Cmmn[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (ctrl_inf == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_get_ctrl_common:ctrl_inf = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	*ctrl_inf = *priv->gDd_Audio_Ctrl_Cmmn[ch];
	
	return D_DDIM_OK;
}

/**
 * @brief  Set Audio Control Information(input)
 * @param  UINT8 ch
 * @param  AudioCtrlIn *ctrl_inf
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_ctrl_ctrl_input(DdAudioCtrl *self, UINT8 ch, AudioCtrlIn* ctrl_inf)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);
	INT32 ret;
	
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
	
	ret = dd_audio_set_input_register_format(ch, ctrl_inf->format);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_input:dd_audio_set_input_register_format() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_Ctrl_In[ch]->format = ctrl_inf->format;
	}
	
	ret = dd_audio_set_in_fifo(ch, ctrl_inf->fifoStages);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_input:dd_audio_set_in_fifo() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_Ctrl_In[ch]->fifoStages = ctrl_inf->fifoStages;
	}
	
	ret = dd_audio_set_in_ahb_format(ch, ctrl_inf->ahbFormat);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_input:dd_audio_set_in_ahb_format() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_Ctrl_In[ch]->ahbFormat = ctrl_inf->ahbFormat;
	}

	ret = dd_audio_set_in_data_shift(ch, ctrl_inf->bitShift);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_input:dd_audio_set_in_data_shift() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_Ctrl_In[ch]->bitShift = ctrl_inf->bitShift;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get Audio Control Information(input)
 * @param  UINT8 ch
 * @param  AudioCtrlIn *ctrl_inf
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_ctrl_get_ctrl_input(DdAudioCtrl *self, UINT8 ch, AudioCtrlIn* ctrl_inf)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_get_ctrl_input:input channel error : %d\n", ch));
		*ctrl_inf = *priv->gDd_Audio_Ctrl_In[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (ctrl_inf == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_get_ctrl_input:ctrl_inf = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	*ctrl_inf = *priv->gDd_Audio_Ctrl_In[ch];
	return D_DDIM_OK;
}

/**
 * @brief  Set Audio Control Information(output)
 * @param  UINT8 ch
 * @param  AudioCtrlOut *ctrl_inf
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_ctrl_ctrl_output(DdAudioCtrl *self, UINT8 ch, AudioCtrlOut* ctrl_inf)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);
	DdAudio* ddAudio = dd_audio_get();
	INT32 ret;
	
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

	ret = dd_audio_set_output_register_format(ch, ctrl_inf->format);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:dd_audio_set_output_register_format() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_Ctrl_Out[ch]->format = ctrl_inf->format;
	}
	
	ret = dd_audio_set_out_fifo(ch, ctrl_inf->fifoStages);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:dd_audio_set_out_fifo() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_Ctrl_Out[ch]->fifoStages = ctrl_inf->fifoStages;
	}
	
	ret = dd_audio_set_out_ahb_format(ch, ctrl_inf->ahbFormat);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:dd_audio_set_out_ahb_format() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_Ctrl_Out[ch]->ahbFormat = ctrl_inf->ahbFormat;
	}
	
	if ((ctrl_inf->lrCopy == DdAudio_ENABLE) && (dd_audio_get_cmmn_master_slave(ddAudio, ch) == DdAudioI2s_CLK_SLAVE)){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output: [SlaveMode] LR Copy Enable\n"));
		return DdAudio_SYSTEM_ERROR;
	}
	
	ret = dd_audio_set_lr_data_copy(ch, ctrl_inf->lrCopy);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:dd_audio_set_lr_data_copy() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_Ctrl_Out[ch]->lrCopy = ctrl_inf->lrCopy;
	}
	
	ret = dd_audio_set_mix_play(ch, ctrl_inf->mixPlay);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:dd_audio_set_mix_play() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_Ctrl_Out[ch]->mixPlay = ctrl_inf->mixPlay;
	}
	
	ret = dd_audio_set_out_data_shift(ch, ctrl_inf->bitShift);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_ctrl_ctrl_output:dd_audio_set_out_data_shift() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_Ctrl_Out[ch]->bitShift = ctrl_inf->bitShift;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get Audio Control Information(output)
 * @param  UINT8 ch
 * @param  AudioCtrlOut *ctrl_inf
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_ctrl_get_ctrl_output(DdAudioCtrl *self, UINT8 ch, AudioCtrlOut* ctrl_inf)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_get_ctrl_output:input channel error : %d\n", ch));
		*ctrl_inf = *priv->gDd_Audio_Ctrl_Out[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (ctrl_inf == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_ctrl_get_ctrl_output:ctrl_inf = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	*ctrl_inf = *priv->gDd_Audio_Ctrl_Out[ch];
	
	return D_DDIM_OK;
}

void dd_audio_ctrl_set_cmmn_fifo_usage(DdAudioCtrl *self, int index, AudioFifoUsage fifoUsage)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->gDd_Audio_Ctrl_Cmmn[index]->fifoUsage = fifoUsage;
}

void dd_audio_ctrl_set_cmmn_channel(DdAudioCtrl *self, int index, AudioChannel channel)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->gDd_Audio_Ctrl_Cmmn[index]->channel = channel;
}

AudioFifoUsage dd_audio_ctrl_get_cmmn_fifo_usage(DdAudioCtrl *self, int index)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	return priv->gDd_Audio_Ctrl_Cmmn[index]->fifoUsage;
}

AudioChannel dd_audio_ctrl_get_cmmn_channel(DdAudioCtrl *self, int index)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	return priv->gDd_Audio_Ctrl_Cmmn[index]->channel;
}

void dd_audio_ctrl_set_in_format(DdAudioCtrl *self, int index, AudioDataRegFrmt format)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->gDd_Audio_Ctrl_In[index]->format = format;
}

void dd_audio_ctrl_set_in_fifo_stages(DdAudioCtrl *self, int index, AudioFifoStages fifoStages)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->gDd_Audio_Ctrl_In[index]->fifoStages = fifoStages;
}

void dd_audio_ctrl_set_in_ahb_format(DdAudioCtrl *self, int index, AudioAhbFrmt ahbFormat)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->gDd_Audio_Ctrl_In[index]->ahbFormat = ahbFormat;
}

void dd_audio_ctrl_set_in_bit_shift(DdAudioCtrl *self, int index, AudioBitShift bitShift)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->gDd_Audio_Ctrl_In[index]->bitShift = bitShift;
}

AudioFifoStages dd_audio_ctrl_get_in_fifo_stages(DdAudioCtrl *self, int index)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	return priv->gDd_Audio_Ctrl_In[index]->fifoStages;
}

void dd_audio_ctrl_set_out_format(DdAudioCtrl *self, int index, AudioDataRegFrmt format)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->gDd_Audio_Ctrl_Out[index]->format = format;
}

void dd_audio_ctrl_set_out_fifo_stages(DdAudioCtrl *self, int index, AudioFifoStages fifoStages)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->gDd_Audio_Ctrl_Out[index]->fifoStages = fifoStages;
}

void dd_audio_ctrl_set_out_ahb_format(DdAudioCtrl *self, int index, AudioAhbFrmt ahbFormat)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->gDd_Audio_Ctrl_Out[index]->ahbFormat = ahbFormat;
}

void dd_audio_ctrl_set_out_lr_copy(DdAudioCtrl *self, int index, UINT8 lrCopy)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->gDd_Audio_Ctrl_Out[index]->lrCopy = lrCopy;
}

void dd_audio_ctrl_set_out_mix_play(DdAudioCtrl *self, int index, UINT8 mixPlay)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->gDd_Audio_Ctrl_Out[index]->mixPlay = mixPlay;
}

void dd_audio_ctrl_set_out_bit_shift(DdAudioCtrl *self, int index, AudioBitShift bitShift)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	priv->gDd_Audio_Ctrl_Out[index]->bitShift = bitShift;
}

AudioFifoStages dd_audio_ctrl_get_out_fifo_stages(DdAudioCtrl *self, int index)
{
	DdAudioCtrlPrivate *priv = DD_AUDIO_CTRL_GET_PRIVATE(self);

	return priv->gDd_Audio_Ctrl_Out[index]->fifoStages;
}

DdAudioCtrl* dd_audio_ctrl_new(void)
{
	DdAudioCtrl* self = k_object_new_with_private(DD_TYPE_AUDIO_CTRL, sizeof(DdAudioCtrlPrivate));

	return self;
}
