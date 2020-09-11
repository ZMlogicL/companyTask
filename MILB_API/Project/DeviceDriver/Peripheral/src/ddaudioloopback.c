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
#include "ddaudioloopback.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudioLoopback, dd_audio_loopback);
#define DD_AUDIO_LOOPBACK_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioLoopbackPrivate, DD_TYPE_AUDIO_LOOPBACK))


struct _DdAudioLoopbackPrivate
{
};


static INT32 dd_audio_set_enable_loopback(DdAudioLoopback* self, UINT8 ch, UINT8 enable);

/**
 * @brief  Set register LB.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_enable_loopback(DdAudioLoopback* self, UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aulbe aulbe;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set AULBE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (ch == DdAudio_IF_CH0_CH1){
		if (enable == DdAudio_ENABLE){
			if (dd_audio_loopback_flag_get(self, DdAudio_IF_CH0) != FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AULBE:already start loopback(0)\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_loopback_flag_get(self, DdAudio_IF_CH1) != FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AULBE:already start loopback(1)\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_audio_in_enable_flag(ddAudio, DdAudio_IF_CH0) == FALSE){
				Ddim_Print(("[DD_AUDIO]Set AULBE: AUIEF(0) = 0\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_audio_in_enable_flag(ddAudio, DdAudio_IF_CH1) == FALSE){
				Ddim_Print(("[DD_AUDIO]Set AULBE: AUIEF(1) = 0\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_audio_out_enable_flag(ddAudio, DdAudio_IF_CH0) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set AULBE:AUOEF(0) = 1\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_audio_out_enable_flag(ddAudio, DdAudio_IF_CH1) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set AULBE:AUOEF(1) = 1\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
		else {
			if (dd_audio_loopback_flag_get(self, DdAudio_IF_CH0) == FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AULBE:already stop loopback\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_loopback_flag_get(self, DdAudio_IF_CH1) == FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AULBE:already stop loopback\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
	}
	else {
		if (enable == DdAudio_ENABLE){
			if (dd_audio_loopback_flag_get(self, ch) != FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AULBE:already start loopback\n"));
				return DdAudio_SYSTEM_ERROR;
			}
			if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) == FALSE){
				Ddim_Print(("[DD_AUDIO]Set AULBE Error: AUIEF = 0\n"));
				return DdAudio_SYSTEM_ERROR;
			}
			if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set AULBE:AUOEF = 1\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
		else {
			if (dd_audio_loopback_flag_get(self, ch) == FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AULBE:already stop loopback\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
	}

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aulbe.word = IO_AUDIO.AUDIOIF_CTRL.AULBE.word;

	switch (ch){
		case DdAudio_IF_CH0 :
			if (enable == DdAudio_ENABLE){
				aulbe.bit.AULBE0 = 1;
			}
			else {
				aulbe.bit.AULBE0 = 2;
			}
			break;
		case DdAudio_IF_CH1 :
			if (enable == DdAudio_ENABLE){
				aulbe.bit.AULBE1 = 1;
			}
			else {
				aulbe.bit.AULBE1 = 2;
			}
			break;
		case DdAudio_IF_CH2 :
			if (enable == DdAudio_ENABLE){
				aulbe.bit.AULBE2 = 1;
			}
			else {
				aulbe.bit.AULBE2 = 2;
			}
			break;
		case DdAudio_IF_CH3 :
			if (enable == DdAudio_ENABLE){
				aulbe.bit.AULBE3 = 1;
			}
			else {
				aulbe.bit.AULBE3 = 2;
			}
			break;
		case DdAudio_IF_CH4 :
			if (enable == DdAudio_ENABLE){
				aulbe.bit.AULBE4 = 1;
			}
			else {
				aulbe.bit.AULBE4 = 2;
			}
			break;
		case DdAudio_IF_CH5 :
			if (enable == DdAudio_ENABLE){
				aulbe.bit.AULBE5 = 1;
			}
			else {
				aulbe.bit.AULBE5 = 2;
			}
			break;
		case DdAudio_IF_CH0_CH1 :
			if (enable == DdAudio_ENABLE){
				aulbe.bit.AULBE0 = 1;
				aulbe.bit.AULBE1 = 1;
			}
			else {
				aulbe.bit.AULBE0 = 2;
				aulbe.bit.AULBE1 = 2;
			}
			break;
		default :
			Ddim_Print(("[DD_AUDIO]Set AULBE:input channel error : %d\n", ch));
			ret_val = DdAudio_INPUT_PARAM_ERROR;
			break;
	}

	if (ret_val == D_DDIM_OK){
		IO_AUDIO.AUDIOIF_CTRL.AULBE.word = aulbe.word;
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

static void dd_audio_loopback_constructor(DdAudioLoopback *self)
{
}

static void dd_audio_loopback_destructor(DdAudioLoopback *self)
{

}

/**
 * @brief  Get register LB.
 * @param  UINT8 ch
 * @return TRUE/FALSE
 */
BOOL dd_audio_loopback_flag_get(DdAudioLoopback* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get LBF:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Start LoopBack Operation.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_loopback_start(DdAudioLoopback* self, UINT8 ch)
{
	DdAudio* ddAudio = dd_audio_get();

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_LB_CH_NUM_MAX) && (ch != DdAudio_IF_CH0_CH1)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_loopback_start:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	if (ch == DdAudio_IF_CH0_CH1){
		if (dd_audio_get_audio_in_enable_flag(ddAudio, DdAudio_IF_CH0) == FALSE){
			Ddim_Print(("[DD_AUDIO]dd_audio_loopback_start:input operation is not performed \n"));
			return DdAudio_SYSTEM_ERROR;
		}
		
		if (dd_audio_get_audio_in_enable_flag(ddAudio, DdAudio_IF_CH1) == FALSE){
			Ddim_Print(("[DD_AUDIO]dd_audio_loopback_start:input operation is not performed \n"));
			return DdAudio_SYSTEM_ERROR;
		}
	}
	else {
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) == FALSE){
			Ddim_Print(("[DD_AUDIO]dd_audio_loopback_start:input operation is not performed \n"));
			return DdAudio_SYSTEM_ERROR;
		}
	}
	
	return dd_audio_set_enable_loopback(self, ch, DdAudio_ENABLE);
}

/**
 * @brief  Stop LoopBack Operation.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_loopback_stop(DdAudioLoopback* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_LB_CH_NUM_MAX) && (ch != DdAudio_IF_CH0_CH1)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_loopback_stop:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	return dd_audio_set_enable_loopback(self, ch, DdAudio_DISABLE);
}

/**
 * @brief  Get Status of LoopBack Operation.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
BOOL dd_audio_loopback_get_status(DdAudioLoopback* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECKa
	if (ch >= DdAudio_IF_LB_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_loopback_get_status:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	return dd_audio_loopback_flag_get(self, ch);
}

DdAudioLoopback* dd_audio_loopback_new(void)
{
	DdAudioLoopback* self = k_object_new_with_private(DD_TYPE_AUDIO_LOOPBACK, sizeof(DdAudioLoopbackPrivate));

	return self;
}

