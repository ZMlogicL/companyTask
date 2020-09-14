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

#ifndef _DD_AUDIO_H_
#define _DD_AUDIO_H_

#include "klib.h"
#include "driver_common.h"
#include "ddaudioctrl.h"
#include "ddaudioi2s.h"
#include "ddaudioio.h"
#include "ddaudioloopback.h"
#include "ddaudiodma.h"
#include "ddaudioreg.h"


#define DD_TYPE_AUDIO				(dd_audio_get_type())
#define DD_AUDIO(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdAudio))
#define DD_IS_AUDIO(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_AUDIO))

/* Return Value */
#define DdAudio_INPUT_PARAM_ERROR	(D_DD_AUDIO | D_DDIM_INPUT_PARAM_ERROR)	/**< Input Parameter Error */
#define DdAudio_MACRO_BUSY_NG		(D_DD_AUDIO | D_DDIM_MACRO_BUSY_NG)		/**< Macro busy */
#define DdAudio_SEM_TIMEOUT			(D_DD_AUDIO | D_DDIM_SEM_TIMEOUT)		/**< Semaphore acquisition Time Out */
#define DdAudio_SEM_NG				(D_DD_AUDIO | D_DDIM_SEM_NG)			/**< Semaphore acquisition NG */
#define DdAudio_SYSTEM_ERROR		(D_DD_AUDIO | D_DDIM_SYSTEM_ERROR)		/**< System error */

#define DdAudio_IF_CH0				(0x00)									/**< Audio IF Channel 0  */
#define DdAudio_IF_CH1				(0x01)									/**< Audio IF Channel 1 */
#define DdAudio_IF_CH2				(0x02)									/**< Audio IF Channel 2 */
#define DdAudio_IF_CH3				(0x03)									/**< Audio IF Channel 3 */
#define DdAudio_IF_CH4				(0x04)									/**< Audio IF Channel 4 */
#define DdAudio_IF_CH5				(0x05)									/**< Audio IF Channel 5 */
#define DdAudio_IF_CH0_CH1			(0x10)									/**< Audio IF Channel 0 & 1<br>
																					 This define is available only in following functions.<br>
																					 - dd_audio_io_start_input()<br>
																					 - dd_audio_io_stop_input()<br>
																					 - dd_audio_io_start_output()<br>
																					 - dd_audio_io_stop_output()<br>
																					 - dd_audio_loopback_start()<br>
																					 - dd_audio_loopback_stop() */
#define DdAudio_IF_CH4_CH5			(0x11)									/**< Audio IF Channel 4 & 5<br>
																					 This define is available only in following functions.<br>
																					 - dd_audio_io_start_input()<br>
																					 - dd_audio_io_stop_input() */

#define DdAudio_IF_CH_NUM_MAX		(0x06)									/**< Channel Max Number */
#define DdAudio_IF_IN_CH_NUM_MAX	(DdAudio_IF_CH_NUM_MAX)			/**< Input Channel Max Number */
#define DdAudio_IF_OUT_CH_NUM_MAX	(0x04)									/**< Output Channel Max Number */
#define DdAudio_IF_LB_CH_NUM_MAX	(0x03)									/**< LoopBack Channel Max Number */

/* Function Enable */
#define	DdAudio_DISABLE				(0)									/**< Disable	*/
#define	DdAudio_ENABLE				(1)									/**< Enable		*/

#define DdAudio_WAIT_USEC(usec)		DD_ARM_WAIT_NS((usec * 1000))


typedef struct _DdAudio 		DdAudio;
typedef struct _DdAudioPrivate 	DdAudioPrivate;

struct  _DdAudio {
	KObject parent;
};


/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
#ifdef __cplusplus
"C" {
#endif


KConstType 		dd_audio_get_type(void);
DdAudio* 		dd_audio_get(void);

kboolean 		dd_audio_get_enable_out_empty_intr(DdAudio* self, kuint8 ch);
kboolean 		dd_audio_get_enable_in_full_intr(DdAudio* self, kuint8 ch);
kboolean 		dd_audio_get_enable_in_usage_intr(DdAudio* self, kuint8 ch);
kboolean 		dd_audio_get_enable_out_usage_intr(DdAudio* self, kuint8 ch);
kboolean 		dd_audio_get_loopback_flag(DdAudio* self, kuint8 ch);

/**
Execute exclusive control for AudioI/F macro(Input)<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[in]	tmout	Time of timeout<br>
						<ul><li>Positive Value(Time of timeout)
							<li>@ref DdimUserCustom_SEM_WAIT_POL
							<li>@ref DdimUserCustom_SEM_WAIT_FEVR</ul>
@retval D_DDIM_OK					OK
@retval D_DD_AUDIO_INPUT_PARAM_ERR	Input Parameter Error
@retval DdAudio_SEM_NG			Semaphore acquisition NG
@retval DdAudio_SEM_TIMEOUT		Semaphore acquisition Time Out
@remarks This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
		 This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
kint32			dd_audio_open_input(DdAudio* self, kuint8 ch, kint32 tmout);

/**
Execute exclusive control for AudioI/F macro(Output)<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[in]	tmout	Time of timeout<br>
						<ul><li>Positive Value(Time of timeout)
							<li>@ref DdimUserCustom_SEM_WAIT_POL
							<li>@ref DdimUserCustom_SEM_WAIT_FEVR</ul>
@retval D_DDIM_OK					OK
@retval D_DD_AUDIO_INPUT_PARAM_ERR	Input Parameter Error
@retval DdAudio_SEM_NG			Semaphore acquisition NG
@retval DdAudio_SEM_TIMEOUT		Semaphore acquisition Time Out
@remarks This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
		 This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
kint32			dd_audio_open_output(DdAudio* self, kuint8 ch, kint32 tmout);

/**
Cancel exclusive control for AudioI/F macro(Input)<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@retval D_DDIM_OK					OK
@retval DdAudio_SEM_NG			Semaphore release NG
@remarks This API uses DDIM_User_Sig_Sem().
*/
kint32			dd_audio_close_input(DdAudio* self, kuint8 ch);

/**
Cancel exclusive control for AudioI/F macro(Output)<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@retval D_DDIM_OK					OK
@retval DdAudio_SEM_NG			Semaphore release NG
@remarks This API uses DDIM_User_Sig_Sem().
*/
kint32			dd_audio_close_output(DdAudio* self, kuint8 ch);

/**
Interrupt handler for AudioI/F macro<br><br>
Interrupt Cause<br>
- Input register full<br>
- Input FIFO stage sotred<br>
- Input register overflow<br>
- Output register empty<br>
- Output FIFO stage empty<br>
- Output register underflow<br><br>

@param[in]	ch	channel<br>
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
*/
void			dd_audio_int_handler(DdAudio* self, kuint8 ch);

/**
Initialize AudioI/F macro<br>
Reset all channel of AudioI/F macro<br>
Start Clock(PLL10A)<br>
*/
void			dd_audio_init(DdAudio* self);

/**
Reset Audio macro<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
kint32 			dd_audio_reset(DdAudio* self, kuint8 ch);

kint32			dd_audio_ctrl_common(DdAudio *self, kuint8 ch, AudioCtrlCommon* ctrlInf);
kint32 			dd_audio_get_ctrl_common(DdAudio *self, kuint8 ch, AudioCtrlCommon* ctrlInf);
kint32			dd_audio_ctrl_input(DdAudio *self, kuint8 ch, AudioCtrlIn* ctrlInf);
kint32 			dd_audio_get_ctrl_input(DdAudio *self, kuint8 ch, AudioCtrlIn* ctrlInf);
kint32			dd_audio_ctrl_output(DdAudio *self, kuint8 ch, AudioCtrlOut* ctrlInf);
kint32 			dd_audio_get_ctrl_output(DdAudio *self, kuint8 ch, AudioCtrlOut* ctrlInf);

void 			dd_audio_set_over_flow_func(DdAudio* self, DdAudioRegFunc overFlowFunc, int index);
void 			dd_audio_set_input_func(DdAudio* self, DdAudioRegFunc input, int index);
void 			dd_audio_set_output_func(DdAudio* self, DdAudioRegFunc output, int index);
kulong* 			dd_audio_get_spin_lock_addr(DdAudio* self);
AudioFifoUsage 	dd_audio_get_cmmn_fifo_usage(DdAudio* self, int index);
AudioFifoStages dd_audio_get_in_fifo_stages(DdAudio* self, int index);
AudioFifoStages dd_audio_get_out_fifo_stages(DdAudio* self, int index);

kint32			dd_audio_ctrl_dma_in(DdAudio *self, kuint8 ch, AudioDma* dmaSetting);
kint32			dd_audio_get_ctrl_dma_in(DdAudio *self, kuint8 ch, AudioDma* dmaSetting);
kint32			dd_audio_ctrl_dma_out(DdAudio *self, kuint8 ch, AudioDma* dmaSetting);
kint32			dd_audio_get_ctrl_dma_out(DdAudio *self, kuint8 ch, AudioDma* dmaSetting);
kint32			dd_audio_set_enable_fifo_full_dmain(DdAudio *self, kuint8 ch, kuint8 enable);
kint32			dd_audio_set_enable_fifo_empty_dma_out(DdAudio *self, kuint8 ch, kuint8 enable);
kint32			dd_audio_set_input_dma_request_enable(DdAudio *self, kuint8 ch, kuint8 enable);
kint32			dd_audio_set_output_dma_request_enable(DdAudio *self, kuint8 ch, kuint8 enable);
UINT16			dd_audio_get_in_dma_sample(DdAudio *self, kuint8 ch);
UINT16			dd_audio_get_out_dma_sample(DdAudio *self, kuint8 ch);
kint32			dd_audio_set_swap_byte_auidlr(DdAudio *self, kuint8 ch, kuint8 enable);
kint32			dd_audio_set_swap_hw_auidlr(DdAudio *self, kuint8 ch, kuint8 enable);
kint32			dd_audio_set_swap_byte_auodlr(DdAudio *self, kuint8 ch, kuint8 enable);
kint32			dd_audio_set_swap_hw_auodlr(DdAudio *self, kuint8 ch, kuint8 enable);

AudioClkMode 	dd_audio_get_cmmn_master_slave(DdAudio *self, kuint8 ch);

kint32			dd_audio_ctrl_i2s_cmmn(DdAudio *self, kuint8 ch, AudioI2sCmmn* i2sSetting);
kint32 			dd_audio_get_ctrl_i2s_cmmn(DdAudio *self, kuint8 ch, AudioI2sCmmn* i2sSetting);
kint32			dd_audio_ctrl_i2s_in(DdAudio *self, kuint8 ch, AudioI2sIn* i2sSetting);
kint32 			dd_audio_get_ctrl_i2s_in(DdAudio *self, kuint8 ch, AudioI2sIn* i2sSetting);
kint32			dd_audio_ctrl_i2s_out(DdAudio *self, kuint8 ch, AudioI2sOut* i2sSetting);
kint32 			dd_audio_get_ctrl_i2s_out(DdAudio *self, kuint8 ch, AudioI2sOut* i2sSetting);

kint32			dd_audio_start_input(DdAudio* self, kuint8 ch);
kint32			dd_audio_stop_input(DdAudio* self, kuint8 ch);
kboolean		dd_audio_get_status_input(DdAudio* self, kuint8 ch);
kint32			dd_audio_start_output(DdAudio* self, kuint8 ch);
kint32			dd_audio_stop_output(DdAudio* self, kuint8 ch);
kboolean		dd_audio_get_status_output(DdAudio* self, kuint8 ch);

kint32			dd_audio_start_loop_back(DdAudio* self, kuint8 ch);
kint32			dd_audio_stop_loop_back(DdAudio* self, kuint8 ch);
kboolean		dd_audio_get_status_loop_back(DdAudio* self, kuchar ch);

kuint32			dd_audio_get_addr_reg_auidlr(DdAudio* self, kuint8 ch);
kuint32			dd_audio_get_addr_reg_auodlr(DdAudio* self, kuint8 ch);
kuint32			dd_audio_get_addr_reg_auidl(DdAudio* self, kuint8 ch);
kuint32			dd_audio_get_addr_reg_auidr(DdAudio* self, kuint8 ch);
kuint32			dd_audio_get_addr_reg_auodl(DdAudio* self, kuchar ch);
kuint32			dd_audio_get_addr_reg_auodr(DdAudio* self, kuint8 ch);
kuint32			dd_audio_get_addr_reg_auiddmapt(DdAudio* self, kuint8 ch);
kuint32			dd_audio_get_addr_reg_auoddmapt(DdAudio* self, kuint8 ch);
kint32 			dd_audio_set_enable_input_intr(DdAudio* self, kuint8 ch, kuint8 enable,
					DdAudioRegFunc callback);
kint32 			dd_audio_set_enable_output_intr(DdAudio* self, kuint8 ch, kuint8 enable,
					DdAudioRegFunc callback);
kint32			dd_audio_set_enable_in_over_flow_intr(DdAudio* self, kuint8 ch, kuint8 enable,
					DdAudioRegFunc callback);
kint32			dd_audio_set_enable_out_under_flow_intr(DdAudio* self, kuint8 ch, kuint8 enable,
					DdAudioRegFunc callback);
kuint32			dd_audio_get_input_fifo_status(DdAudio* self, kuint8 ch);
kuint32 		dd_audio_get_output_fifo_status(DdAudio* self, kuint8 ch);

kint32 			dd_audio_set_enable_in_full_intr(DdAudio* self, kuint8 ch, kuint8 enable);
kint32 			dd_audio_set_enable_out_empty_intr(DdAudio* self, kuint8 ch, kuint8 enable);
kboolean 		dd_audio_get_audio_in_enable_flag(DdAudio* self, kuint8 ch);
kboolean 		dd_audio_get_audio_out_enable_flag(DdAudio* self, kuint8 ch);
kint32 			dd_audio_clear_out_underflow_flag(DdAudio* self, kuint8 ch);
kint32 			dd_audio_set_enable_in_overflow_intr(DdAudio* self, kuint8 ch, kuint8 enable);
kint32 			dd_audio_set_enable_out_underflow_intr(DdAudio* self, kuint8 ch, kuint8 enable);
kint32 			dd_audio_set_enable_in_usage_intr(DdAudio* self, kuint8 ch, kuint8 enable);
kint32 			dd_audio_clear_in_overflow_flag(DdAudio* self, kuint8 ch);
kint32 			dd_audio_set_enable_out_usage_intr(DdAudio* self, kuint8 ch, kuint8 enable);

#ifdef __cplusplus
}
#endif

#endif	// _DD_AUDIO_H_


