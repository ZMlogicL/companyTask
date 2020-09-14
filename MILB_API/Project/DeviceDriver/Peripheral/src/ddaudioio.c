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
#include "ddimusercustom.h"
#include "ddaudio.h"
#include "ddaudioio.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudioIo, dd_audio_io);
#define DD_AUDIO_IO_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioIoPrivate, DD_TYPE_AUDIO_IO))

#define D_DD_AUDIO_STOP_WAIT_LOOP	(5)


struct _DdAudioIoPrivate
{
};


static kint32 ddAudioSetEnableAudioIn(kuint8 ch, kuint8 enable);
static kint32 ddAudioSetEnableAudioOut(kuint8 ch, kuint8 enable);
static kboolean ddAudioGetEnableInData24bit(kuint8 ch);
static kint32 ddAudioDisableInputIntr(kuint8 ch);
static kint32 ddAudioDisableOutputIntr(kuint8 ch);
static void ddAudioWaitEmptyInputFifo(kuint8 ch);
static void ddAudioWaitEmptyOutputFifo(kuint8 ch);
static void ddAudioWaitStoreOutputFifo(kuint8 ch);


static void dd_audio_io_constructor(DdAudioIo *self)
{
}

static void dd_audio_io_destructor(DdAudioIo *self)
{

}

/**
 * @brief  Set register AUIOE(AUIE).
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetEnableAudioIn(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAuioe auioe;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set AUIE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (ch == DdAudio_IF_CH0_CH1){
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_audio_in_enable_flag(ddAudio, DdAudio_IF_CH0) != FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUIE:already start input(0)\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_audio_in_enable_flag(ddAudio, DdAudio_IF_CH1) != FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUIE:already start input(1)\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
		else {
			if (dd_audio_get_audio_in_enable_flag(ddAudio, DdAudio_IF_CH0) == FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUIE:already stop input(0)\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_audio_in_enable_flag(ddAudio, DdAudio_IF_CH1) == FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUIE:already stop input(1)\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
	}
	else if (ch == DdAudio_IF_CH4_CH5){
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_audio_in_enable_flag(ddAudio, DdAudio_IF_CH4) != FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUIE:already start input(4)\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_audio_in_enable_flag(ddAudio, DdAudio_IF_CH5) != FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUIE:already start input(5)\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
		else {
			if (dd_audio_get_audio_in_enable_flag(ddAudio, DdAudio_IF_CH4) == FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUIE:already stop input(4)\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_audio_in_enable_flag(ddAudio, DdAudio_IF_CH5) == FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUIE:already stop input(5)\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
	}
	else {
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUIE:already start input\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
		else {
			if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) == FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUIE:already stop input\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
	}

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	auioe.word = ioAudio.audioifCtrl.auioe.word;

	switch (ch){
		case DdAudio_IF_CH0 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auie0 = 1;
			}
			else {
				auioe.bit.auie0 = 2;
			}
			break;
		case DdAudio_IF_CH1 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auie1 = 1;
			}
			else {
				auioe.bit.auie1 = 2;
			}
			break;
		case DdAudio_IF_CH2 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auie2 = 1;
			}
			else {
				auioe.bit.auie2 = 2;
			}
			break;
		case DdAudio_IF_CH3 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auie3 = 1;
			}
			else {
				auioe.bit.auie3 = 2;
			}
			break;
		case DdAudio_IF_CH4 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auie4 = 1;
			}
			else {
				auioe.bit.auie4 = 2;
			}
			break;
		case DdAudio_IF_CH5 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auie5 = 1;
			}
			else {
				auioe.bit.auie5 = 2;
			}
			break;
		case DdAudio_IF_CH0_CH1 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auie0 = 1;
				auioe.bit.auie1 = 1;
			}
			else {
				auioe.bit.auie0 = 2;
				auioe.bit.auie1 = 2;
			}
			break;
		case DdAudio_IF_CH4_CH5 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auie4 = 1;
				auioe.bit.auie5 = 1;
			}
			else {
				auioe.bit.auie4 = 2;
				auioe.bit.auie5 = 2;
			}
			break;
		default :
			Ddim_Print(("[DD_AUDIO]Set AUIE:input channel error : %d\n", ch));
			retVal = DdAudio_INPUT_PARAM_ERROR;
			break;
	}

	if (retVal == D_DDIM_OK){
		ioAudio.audioifCtrl.auioe.word = auioe.word;
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register AUIOE(AUOE).
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetEnableAudioOut(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAuioe auioe;
	kint32 retVal = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set AUOE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (ch == DdAudio_IF_CH0_CH1){
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_audio_out_enable_flag(ddAudio, DdAudio_IF_CH0) != FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUOE:already start output(0)\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_audio_out_enable_flag(ddAudio, DdAudio_IF_CH1) != FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUOE:already start output(1)\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_loopback_flag(ddAudio, DdAudio_IF_CH0) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set AUOE:LBF(0) = 1\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_loopback_flag(ddAudio, DdAudio_IF_CH1) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set AUOE:LBF(1) = 1\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
		else {
			if (dd_audio_get_audio_out_enable_flag(ddAudio, DdAudio_IF_CH0) == FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUOE:already stop output(0)\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_audio_out_enable_flag(ddAudio, DdAudio_IF_CH1) == FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUOE:already stop output(1)\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
	}
	else {
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUOE:already start output\n"));
				return DdAudio_SYSTEM_ERROR;
			}

			if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set AUOE:LBF = 1\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
		else {
			if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) == FALSE){
				Ddim_Assertion(("[DD_AUDIO]Set AUOE:already stop output\n"));
				return DdAudio_SYSTEM_ERROR;
			}
		}
	}

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	auioe.word = ioAudio.audioifCtrl.auioe.word;

	switch (ch){
		case DdAudio_IF_CH0 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auoe0 = 1;
			}
			else {
				auioe.bit.auoe0 = 2;
			}
			break;
		case DdAudio_IF_CH1 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auoe1 = 1;
			}
			else {
				auioe.bit.auoe1 = 2;
			}
			break;
		case DdAudio_IF_CH2 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auoe2 = 1;
			}
			else {
				auioe.bit.auoe2 = 2;
			}
			break;
		case DdAudio_IF_CH3 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auoe3 = 1;
			}
			else {
				auioe.bit.auoe3 = 2;
			}
			break;
		case DdAudio_IF_CH4 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auoe4 = 1;
			}
			else {
				auioe.bit.auoe4 = 2;
			}
			break;
		case DdAudio_IF_CH5 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auoe5 = 1;
			}
			else {
				auioe.bit.auoe5 = 2;
			}
			break;
		case DdAudio_IF_CH0_CH1 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.auoe0 = 1;
				auioe.bit.auoe1 = 1;
			}
			else {
				auioe.bit.auoe0 = 2;
				auioe.bit.auoe1 = 2;
			}
			break;
		default :
			Ddim_Print(("[DD_AUDIO]Set AUOE:input channel error : %d\n", ch));
			retVal = DdAudio_INPUT_PARAM_ERROR;
			break;
	}

	if (retVal == D_DDIM_OK){
		ioAudio.audioifCtrl.auioe.word = auioe.word;
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Get register AUIDSEL.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kboolean ddAudioGetEnableInData24bit(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUIDSEL:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aucr.bit.auidsel == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Disable Input Interrupt.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_SYSTEM_ERROR
 */
static kint32 ddAudioDisableInputIntr(kuint8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	kint32 ret;

	if (dd_audio_get_cmmn_fifo_usage(ddAudio, ch) == DdAudioCtrl_FIFO_USAGE_STAGES_16){
		ret = dd_audio_set_enable_in_full_intr(ddAudio, ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_disable_input_intr:dd_audio_set_enable_in_full_intr() = %x\n", ret));
			return DdAudio_SYSTEM_ERROR;
		}
	}
	else {
		ret = dd_audio_set_enable_in_usage_intr(ddAudio, ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_disable_input_intr:dd_audio_set_enable_in_usage_intr() = %x\n", ret));
			return DdAudio_SYSTEM_ERROR;
		}
	}

	return D_DDIM_OK;
}

/**
 * @brief  Disable Output Interrupt.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_SYSTEM_ERROR
 */
static kint32 ddAudioDisableOutputIntr(kuint8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	kint32 ret;

	if (dd_audio_get_cmmn_fifo_usage(ddAudio, ch) == DdAudioCtrl_FIFO_USAGE_STAGES_16){
		ret = dd_audio_set_enable_out_empty_intr(ddAudio, ch, DdAudio_DISABLE);
	}
	else {
		ret = dd_audio_set_enable_out_usage_intr(ddAudio, ch, DdAudio_DISABLE);
	}

	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_disable_output_intr:Set INTOE/eintoe = %x\n", ret));
		return DdAudio_SYSTEM_ERROR;
	}

	return D_DDIM_OK;
}

/**
 * @brief  wait for empty state of fifo.
 * @param  kuint8 ch
 */
static void ddAudioWaitEmptyInputFifo(kuint8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	volatile kuint8 waitCounter;
	DdimUserCustom_ER ercd;
	volatile kuint32 dummyRead = 0;

	waitCounter = 0;
	while (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
		ercd = DDIM_User_Dly_Tsk(0);

		if (ercd != DdimUserCustom_E_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_wait_empty_input_fifo:dly_tsk error. ercd = %d\n", ercd));
			break;
		}

		if (waitCounter > D_DD_AUDIO_STOP_WAIT_LOOP){
			Ddim_Print(("[DD_AUDIO]dd_audio_wait_empty_input_fifo:TimeOut \n"));
			waitCounter = 0;
			if (ddAudioGetEnableInData24bit(ch) != FALSE){
				while (waitCounter < 15){
					dummyRead = ioAudio.audioif[ch].auidl;
					dummyRead = ioAudio.audioif[ch].auidr;
					waitCounter++;
				}
			}
			else {
				while (waitCounter < 15){
					dummyRead = ioAudio.audioif[ch].auidlr;
					waitCounter++;
				}
			}

			break;				// time out
		}

		waitCounter++;
	}

	// remove the warnning of the compiler
	if (dummyRead == 0){
		; // Nothing
	}
}

/**
 * @brief  wait for empty state of fifo.
 * @param  kuint8 ch
 */
static void ddAudioWaitEmptyOutputFifo(kuint8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	volatile kuint8 waitCounter;
	DdimUserCustom_ER ercd;

	waitCounter = 0;
	while (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
		ercd = DDIM_User_Dly_Tsk(0);

		if (ercd != DdimUserCustom_E_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_wait_empty_output_fifo:dly_tsk error. ercd = %d\n", ercd));
			break;
		}

		if (waitCounter > D_DD_AUDIO_STOP_WAIT_LOOP){
			Ddim_Print(("[DD_AUDIO]dd_audio_wait_empty_output_fifo:TimeOut \n"));
			break;				// time out
		}

		waitCounter++;
	}
}

/**
 * @brief  wait for store data to fifo.
 * @param  kuint8 ch
 */
static void ddAudioWaitStoreOutputFifo(kuint8 ch)
{
	volatile kuint8 waitCounter;

	waitCounter = 0;
	while (dd_audio_get_output_fifo_status(dd_audio_get(), ch) == 0){
		waitCounter++;

		// fail safe
		if (waitCounter > 100){
			Ddim_Print(("[DD_AUDIO]dd_audio_wait_store_output_fifo:TimeOut. ch=%d\n", ch));
			break;
		}
	}
}

/**
 * @brief  Start Audio Input
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_io_start_input(DdAudioIo* self, kuint8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	kint32 ret;
	
#ifdef CO_PARAM_CHECK
	if (((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)) &&
		 (ch != DdAudio_IF_CH0_CH1)									   &&
		 (ch != DdAudio_IF_CH4_CH5)										){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_io_start_input:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	// Clear OverFlow Flag
	if (ch == DdAudio_IF_CH0_CH1){
		// CH0
		ret = dd_audio_clear_in_overflow_flag(ddAudio, DdAudio_IF_CH0);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_clear_in_overflow_flag() = %x\n", ret));
		}
		// CH1
		ret = dd_audio_clear_in_overflow_flag(ddAudio, DdAudio_IF_CH1);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_clear_in_overflow_flag() = %x\n", ret));
		}
	}
	else if (ch == DdAudio_IF_CH4_CH5){
		// CH0
		ret = dd_audio_clear_in_overflow_flag(ddAudio, DdAudio_IF_CH4);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_clear_in_overflow_flag() = %x\n", ret));
		}
		// CH1
		ret = dd_audio_clear_in_overflow_flag(ddAudio, DdAudio_IF_CH5);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_clear_in_overflow_flag() = %x\n", ret));
		}
	}
	else {
		ret = dd_audio_clear_in_overflow_flag(ddAudio, ch);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_clear_in_overflow_flag() = %x\n", ret));
		}
	}
	
	ret = ddAudioSetEnableAudioIn(ch, DdAudio_ENABLE);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_set_enable_audio_in() = %x\n", ret));
		return ret;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Stop Audio Input
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_io_stop_input(DdAudioIo* self, kuint8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	kint32 ret;
	
#ifdef CO_PARAM_CHECK
	if (((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)) &&
		 (ch != DdAudio_IF_CH0_CH1)									   &&
		 (ch != DdAudio_IF_CH4_CH5)										){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_io_stop_input:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	if (ch == DdAudio_IF_CH0_CH1){
		// Disable Interrupt
		ret = dd_audio_set_enable_in_overflow_intr(ddAudio, DdAudio_IF_CH0, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_set_enable_in_overflow_intr() = %x\n", ret));
		}
		
		ret = dd_audio_set_enable_in_overflow_intr(ddAudio, DdAudio_IF_CH1, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_set_enable_in_overflow_intr() = %x\n", ret));
		}
		
		// CH0
		ret = ddAudioDisableInputIntr(DdAudio_IF_CH0);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_disable_input_intr() = %x\n", ret));
		}
		
		// CH1
		ret = ddAudioDisableInputIntr(DdAudio_IF_CH1);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_disable_input_intr() = %x\n", ret));
		}
		
		//stop input
		ret = ddAudioSetEnableAudioIn(ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_input:dd_audio_set_enable_audio_in() = %x\n", ret));
			return ret;
		}
		
		Dd_ARM_Dsb_Pou();
		
		// CH0
		ddAudioWaitEmptyInputFifo(DdAudio_IF_CH0);
		
		// CH1
		ddAudioWaitEmptyInputFifo(DdAudio_IF_CH1);
	}
	else if (ch == DdAudio_IF_CH4_CH5){
		// Disable Interrupt
		ret = dd_audio_set_enable_in_overflow_intr(ddAudio, DdAudio_IF_CH4, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_set_enable_in_overflow_intr() = %x\n", ret));
		}
		
		ret = dd_audio_set_enable_in_overflow_intr(ddAudio, DdAudio_IF_CH5, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_set_enable_in_overflow_intr() = %x\n", ret));
		}
		
		// CH0
		ret = ddAudioDisableInputIntr(DdAudio_IF_CH4);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_disable_input_intr() = %x\n", ret));
		}
		
		// CH1
		ret = ddAudioDisableInputIntr(DdAudio_IF_CH5);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_disable_input_intr() = %x\n", ret));
		}
		
		//stop input
		ret = ddAudioSetEnableAudioIn(ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_input:dd_audio_set_enable_audio_in() = %x\n", ret));
			return ret;
		}
		
		Dd_ARM_Dsb_Pou();
		
		// CH0
		ddAudioWaitEmptyInputFifo(DdAudio_IF_CH4);
		
		// CH1
		ddAudioWaitEmptyInputFifo(DdAudio_IF_CH5);
	}
	else {
		// Disable Interrupt
		ret = dd_audio_set_enable_in_overflow_intr(ddAudio, ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_set_enable_in_overflow_intr() = %x\n", ret));
		}
		
		ret = ddAudioDisableInputIntr(ch);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_disable_input_intr() = %x\n", ret));
		}
		
		//stop input
		ret = ddAudioSetEnableAudioIn(ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_input:dd_audio_set_enable_audio_in() = %x\n", ret));
			return ret;
		}
		
		Dd_ARM_Dsb_Pou();
		
		ddAudioWaitEmptyInputFifo(ch);
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get Status of Input Operation
 * @param  kuint8 ch
 * @return TRUE/FALSE
 */
kboolean dd_audio_io_get_status_input(DdAudioIo* self, kuint8 ch)
{
	DdAudio* ddAudio = dd_audio_get();

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_io_get_status_input:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	return dd_audio_get_audio_in_enable_flag(ddAudio, ch);
}

/**
 * @brief  Start Audio Output
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_io_start_output(DdAudioIo* self, kuint8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	kint32 ret;
	
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_OUT_CH_NUM_MAX) && (ch != DdAudio_IF_CH0_CH1)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_io_start_output:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	if (ch == DdAudio_IF_CH0_CH1){
		// CH0
		ret = dd_audio_clear_out_underflow_flag(ddAudio, DdAudio_IF_CH0);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_output:dd_audio_clear_out_underflow_flag() = %x\n", ret));
		}
		
		// CH1
		ret = dd_audio_clear_out_underflow_flag(ddAudio, DdAudio_IF_CH1);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_output:dd_audio_clear_out_underflow_flag() = %x\n", ret));
		}
		
		// CH0
		ddAudioWaitStoreOutputFifo(DdAudio_IF_CH0);
		
		// CH1
		ddAudioWaitStoreOutputFifo(DdAudio_IF_CH1);
	}
	else {
		ret = dd_audio_clear_out_underflow_flag(ddAudio, ch);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_output:dd_audio_clear_out_underflow_flag() = %x\n", ret));
		}
		
		ddAudioWaitStoreOutputFifo(ch);
	}
	
	ret = ddAudioSetEnableAudioOut(ch, DdAudio_ENABLE);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_io_start_output:dd_audio_set_enable_audio_out() = %x\n", ret));
		return ret;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Stop Audio Ouput
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_io_stop_output(DdAudioIo* self, kuint8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	kint32 ret;
	
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_OUT_CH_NUM_MAX) && (ch != DdAudio_IF_CH0_CH1)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_io_stop_output:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	if (ch == DdAudio_IF_CH0_CH1){
		// Disable Interrupt
		// CH0
		ret = dd_audio_set_enable_out_underflow_intr(ddAudio, DdAudio_IF_CH0, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:dd_audio_set_enable_out_underflow_intr = %x\n", ret));
		}
		
		// CH1
		ret = dd_audio_set_enable_out_underflow_intr(ddAudio, DdAudio_IF_CH1, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:dd_audio_set_enable_out_underflow_intr = %x\n", ret));
		}
		
		// CH0
		ret = ddAudioDisableOutputIntr(DdAudio_IF_CH0);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:Set INTOE/eintoe = %x\n", ret));
		}
		
		// CH1
		ret = ddAudioDisableOutputIntr(DdAudio_IF_CH1);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:Set INTOE/eintoe = %x\n", ret));
		}
		
		//stop output
		ret = ddAudioSetEnableAudioOut(ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:dd_audio_set_enable_audio_out() = %x\n", ret));
			return ret;
		}
		
		ddAudioWaitEmptyOutputFifo(DdAudio_IF_CH0);
		ddAudioWaitEmptyOutputFifo(DdAudio_IF_CH1);
	}
	else {
		// Disable Interrupt
		ret = dd_audio_set_enable_out_underflow_intr(ddAudio, ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:dd_audio_set_enable_out_underflow_intr = %x\n", ret));
		}
		
		ret = ddAudioDisableOutputIntr(ch);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:Set INTOE/eintoe = %x\n", ret));
		}
		
		//stop output
		ret = ddAudioSetEnableAudioOut(ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:dd_audio_set_enable_audio_out() = %x\n", ret));
			return ret;
		}
		
		ddAudioWaitEmptyOutputFifo(ch);
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get Status of Output Operation
 * @param  kuint8 ch
 * @return TRUE/FALSE
 */
kboolean dd_audio_io_get_status_output(DdAudioIo* self, kuint8 ch)
{
	DdAudio* ddAudio = dd_audio_get();

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_io_get_status_output:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	return dd_audio_get_audio_out_enable_flag(ddAudio, ch);
}

DdAudioIo* dd_audio_io_new(void)
{
	DdAudioIo* self = k_object_new_with_private(DD_TYPE_AUDIO_IO, sizeof(DdAudioIoPrivate));

	return self;
}


