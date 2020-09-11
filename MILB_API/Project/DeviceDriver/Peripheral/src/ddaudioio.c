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
#include "ddaudioio.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudioIo, dd_audio_io);
#define DD_AUDIO_IO_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioIoPrivate, DD_TYPE_AUDIO_IO))

#define D_DD_AUDIO_STOP_WAIT_LOOP	(5)


struct _DdAudioIoPrivate
{
};


static INT32 dd_audio_set_enable_audio_in(UINT8 ch, UINT8 enable);
static INT32 dd_audio_set_enable_audio_out(UINT8 ch, UINT8 enable);
static BOOL dd_audio_get_enable_in_data24bit(UINT8 ch);
static INT32 dd_audio_disable_input_intr(UINT8 ch);
static INT32 dd_audio_disable_output_intr(UINT8 ch);
static VOID dd_audio_wait_empty_input_fifo(UINT8 ch);
static VOID dd_audio_wait_empty_output_fifo(UINT8 ch);
static VOID dd_audio_wait_store_output_fifo(UINT8 ch);


static void dd_audio_io_constructor(DdAudioIo *self)
{
}

static void dd_audio_io_destructor(DdAudioIo *self)
{

}

/**
 * @brief  Set register AUIOE(AUIE).
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_enable_audio_in(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_auioe auioe;
	INT32 ret_val = D_DDIM_OK;

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

	auioe.word = IO_AUDIO.AUDIOIF_CTRL.AUIOE.word;

	switch (ch){
		case DdAudio_IF_CH0 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUIE0 = 1;
			}
			else {
				auioe.bit.AUIE0 = 2;
			}
			break;
		case DdAudio_IF_CH1 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUIE1 = 1;
			}
			else {
				auioe.bit.AUIE1 = 2;
			}
			break;
		case DdAudio_IF_CH2 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUIE2 = 1;
			}
			else {
				auioe.bit.AUIE2 = 2;
			}
			break;
		case DdAudio_IF_CH3 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUIE3 = 1;
			}
			else {
				auioe.bit.AUIE3 = 2;
			}
			break;
		case DdAudio_IF_CH4 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUIE4 = 1;
			}
			else {
				auioe.bit.AUIE4 = 2;
			}
			break;
		case DdAudio_IF_CH5 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUIE5 = 1;
			}
			else {
				auioe.bit.AUIE5 = 2;
			}
			break;
		case DdAudio_IF_CH0_CH1 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUIE0 = 1;
				auioe.bit.AUIE1 = 1;
			}
			else {
				auioe.bit.AUIE0 = 2;
				auioe.bit.AUIE1 = 2;
			}
			break;
		case DdAudio_IF_CH4_CH5 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUIE4 = 1;
				auioe.bit.AUIE5 = 1;
			}
			else {
				auioe.bit.AUIE4 = 2;
				auioe.bit.AUIE5 = 2;
			}
			break;
		default :
			Ddim_Print(("[DD_AUDIO]Set AUIE:input channel error : %d\n", ch));
			ret_val = DdAudio_INPUT_PARAM_ERROR;
			break;
	}

	if (ret_val == D_DDIM_OK){
		IO_AUDIO.AUDIOIF_CTRL.AUIOE.word = auioe.word;
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register AUIOE(AUOE).
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_enable_audio_out(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_auioe auioe;
	INT32 ret_val = D_DDIM_OK;

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

	auioe.word = IO_AUDIO.AUDIOIF_CTRL.AUIOE.word;

	switch (ch){
		case DdAudio_IF_CH0 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUOE0 = 1;
			}
			else {
				auioe.bit.AUOE0 = 2;
			}
			break;
		case DdAudio_IF_CH1 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUOE1 = 1;
			}
			else {
				auioe.bit.AUOE1 = 2;
			}
			break;
		case DdAudio_IF_CH2 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUOE2 = 1;
			}
			else {
				auioe.bit.AUOE2 = 2;
			}
			break;
		case DdAudio_IF_CH3 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUOE3 = 1;
			}
			else {
				auioe.bit.AUOE3 = 2;
			}
			break;
		case DdAudio_IF_CH4 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUOE4 = 1;
			}
			else {
				auioe.bit.AUOE4 = 2;
			}
			break;
		case DdAudio_IF_CH5 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUOE5 = 1;
			}
			else {
				auioe.bit.AUOE5 = 2;
			}
			break;
		case DdAudio_IF_CH0_CH1 :
			if (enable == DdAudio_ENABLE){
				auioe.bit.AUOE0 = 1;
				auioe.bit.AUOE1 = 1;
			}
			else {
				auioe.bit.AUOE0 = 2;
				auioe.bit.AUOE1 = 2;
			}
			break;
		default :
			Ddim_Print(("[DD_AUDIO]Set AUOE:input channel error : %d\n", ch));
			ret_val = DdAudio_INPUT_PARAM_ERROR;
			break;
	}

	if (ret_val == D_DDIM_OK){
		IO_AUDIO.AUDIOIF_CTRL.AUIOE.word = auioe.word;
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Get register AUIDSEL.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static BOOL dd_audio_get_enable_in_data24bit(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUIDSEL:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIDSEL == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Disable Input Interrupt.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_SYSTEM_ERROR
 */
static INT32 dd_audio_disable_input_intr(UINT8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	INT32 ret;

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
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_SYSTEM_ERROR
 */
static INT32 dd_audio_disable_output_intr(UINT8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	INT32 ret;

	if (dd_audio_get_cmmn_fifo_usage(ddAudio, ch) == DdAudioCtrl_FIFO_USAGE_STAGES_16){
		ret = dd_audio_set_enable_out_empty_intr(ddAudio, ch, DdAudio_DISABLE);
	}
	else {
		ret = dd_audio_set_enable_out_usage_intr(ddAudio, ch, DdAudio_DISABLE);
	}

	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_disable_output_intr:Set INTOE/EINTOE = %x\n", ret));
		return DdAudio_SYSTEM_ERROR;
	}

	return D_DDIM_OK;
}

/**
 * @brief  wait for empty state of fifo.
 * @param  UINT8 ch
 */
static VOID dd_audio_wait_empty_input_fifo(UINT8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	volatile UINT8 wait_counter;
	DDIM_USER_ER ercd;
	volatile UINT32 dummy_read = 0;

	wait_counter = 0;
	while (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
		ercd = DDIM_User_Dly_Tsk(0);

		if (ercd != D_DDIM_USER_E_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_wait_empty_input_fifo:dly_tsk error. ercd = %d\n", ercd));
			break;
		}

		if (wait_counter > D_DD_AUDIO_STOP_WAIT_LOOP){
			Ddim_Print(("[DD_AUDIO]dd_audio_wait_empty_input_fifo:TimeOut \n"));
			wait_counter = 0;
			if (dd_audio_get_enable_in_data24bit(ch) != FALSE){
				while (wait_counter < 15){
					dummy_read = IO_AUDIO.AUDIOIF[ch].AUIDL;
					dummy_read = IO_AUDIO.AUDIOIF[ch].AUIDR;
					wait_counter++;
				}
			}
			else {
				while (wait_counter < 15){
					dummy_read = IO_AUDIO.AUDIOIF[ch].AUIDLR;
					wait_counter++;
				}
			}

			break;				// time out
		}

		wait_counter++;
	}

	// remove the warnning of the compiler
	if (dummy_read == 0){
		; // Nothing
	}
}

/**
 * @brief  wait for empty state of fifo.
 * @param  UINT8 ch
 */
static VOID dd_audio_wait_empty_output_fifo(UINT8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	volatile UINT8 wait_counter;
	DDIM_USER_ER ercd;

	wait_counter = 0;
	while (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
		ercd = DDIM_User_Dly_Tsk(0);

		if (ercd != D_DDIM_USER_E_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_wait_empty_output_fifo:dly_tsk error. ercd = %d\n", ercd));
			break;
		}

		if (wait_counter > D_DD_AUDIO_STOP_WAIT_LOOP){
			Ddim_Print(("[DD_AUDIO]dd_audio_wait_empty_output_fifo:TimeOut \n"));
			break;				// time out
		}

		wait_counter++;
	}
}

/**
 * @brief  wait for store data to fifo.
 * @param  UINT8 ch
 */
static VOID dd_audio_wait_store_output_fifo(UINT8 ch)
{
	volatile UINT8 wait_counter;

	wait_counter = 0;
	while (dd_audio_get_output_fifo_status(dd_audio_get(), ch) == 0){
		wait_counter++;

		// fail safe
		if (wait_counter > 100){
			Ddim_Print(("[DD_AUDIO]dd_audio_wait_store_output_fifo:TimeOut. ch=%d\n", ch));
			break;
		}
	}
}

/**
 * @brief  Start Audio Input
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_io_start_input(DdAudioIo* self, UINT8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	INT32 ret;
	
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
	
	ret = dd_audio_set_enable_audio_in(ch, DdAudio_ENABLE);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_set_enable_audio_in() = %x\n", ret));
		return ret;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Stop Audio Input
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32	dd_audio_io_stop_input(DdAudioIo* self, UINT8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	INT32 ret;
	
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
		ret = dd_audio_disable_input_intr(DdAudio_IF_CH0);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_disable_input_intr() = %x\n", ret));
		}
		
		// CH1
		ret = dd_audio_disable_input_intr(DdAudio_IF_CH1);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_disable_input_intr() = %x\n", ret));
		}
		
		//stop input
		ret = dd_audio_set_enable_audio_in(ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_input:dd_audio_set_enable_audio_in() = %x\n", ret));
			return ret;
		}
		
		Dd_ARM_Dsb_Pou();
		
		// CH0
		dd_audio_wait_empty_input_fifo(DdAudio_IF_CH0);
		
		// CH1
		dd_audio_wait_empty_input_fifo(DdAudio_IF_CH1);
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
		ret = dd_audio_disable_input_intr(DdAudio_IF_CH4);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_disable_input_intr() = %x\n", ret));
		}
		
		// CH1
		ret = dd_audio_disable_input_intr(DdAudio_IF_CH5);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_disable_input_intr() = %x\n", ret));
		}
		
		//stop input
		ret = dd_audio_set_enable_audio_in(ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_input:dd_audio_set_enable_audio_in() = %x\n", ret));
			return ret;
		}
		
		Dd_ARM_Dsb_Pou();
		
		// CH0
		dd_audio_wait_empty_input_fifo(DdAudio_IF_CH4);
		
		// CH1
		dd_audio_wait_empty_input_fifo(DdAudio_IF_CH5);
	}
	else {
		// Disable Interrupt
		ret = dd_audio_set_enable_in_overflow_intr(ddAudio, ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_set_enable_in_overflow_intr() = %x\n", ret));
		}
		
		ret = dd_audio_disable_input_intr(ch);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_input:dd_audio_disable_input_intr() = %x\n", ret));
		}
		
		//stop input
		ret = dd_audio_set_enable_audio_in(ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_input:dd_audio_set_enable_audio_in() = %x\n", ret));
			return ret;
		}
		
		Dd_ARM_Dsb_Pou();
		
		dd_audio_wait_empty_input_fifo(ch);
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get Status of Input Operation
 * @param  UINT8 ch
 * @return TRUE/FALSE
 */
BOOL dd_audio_io_get_status_input(DdAudioIo* self, UINT8 ch)
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
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_io_start_output(DdAudioIo* self, UINT8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	INT32 ret;
	
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
		dd_audio_wait_store_output_fifo(DdAudio_IF_CH0);
		
		// CH1
		dd_audio_wait_store_output_fifo(DdAudio_IF_CH1);
	}
	else {
		ret = dd_audio_clear_out_underflow_flag(ddAudio, ch);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_start_output:dd_audio_clear_out_underflow_flag() = %x\n", ret));
		}
		
		dd_audio_wait_store_output_fifo(ch);
	}
	
	ret = dd_audio_set_enable_audio_out(ch, DdAudio_ENABLE);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_io_start_output:dd_audio_set_enable_audio_out() = %x\n", ret));
		return ret;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Stop Audio Ouput
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_io_stop_output(DdAudioIo* self, UINT8 ch)
{
	DdAudio* ddAudio = dd_audio_get();
	INT32 ret;
	
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
		ret = dd_audio_disable_output_intr(DdAudio_IF_CH0);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:Set INTOE/EINTOE = %x\n", ret));
		}
		
		// CH1
		ret = dd_audio_disable_output_intr(DdAudio_IF_CH1);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:Set INTOE/EINTOE = %x\n", ret));
		}
		
		//stop output
		ret = dd_audio_set_enable_audio_out(ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:dd_audio_set_enable_audio_out() = %x\n", ret));
			return ret;
		}
		
		dd_audio_wait_empty_output_fifo(DdAudio_IF_CH0);
		dd_audio_wait_empty_output_fifo(DdAudio_IF_CH1);
	}
	else {
		// Disable Interrupt
		ret = dd_audio_set_enable_out_underflow_intr(ddAudio, ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:dd_audio_set_enable_out_underflow_intr = %x\n", ret));
		}
		
		ret = dd_audio_disable_output_intr(ch);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:Set INTOE/EINTOE = %x\n", ret));
		}
		
		//stop output
		ret = dd_audio_set_enable_audio_out(ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_io_stop_output:dd_audio_set_enable_audio_out() = %x\n", ret));
			return ret;
		}
		
		dd_audio_wait_empty_output_fifo(ch);
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get Status of Output Operation
 * @param  UINT8 ch
 * @return TRUE/FALSE
 */
BOOL dd_audio_io_get_status_output(DdAudioIo* self, UINT8 ch)
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


