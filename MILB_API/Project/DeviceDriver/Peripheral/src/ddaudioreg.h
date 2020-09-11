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

#ifndef __DD_AUDIO_REG__
#define __DD_AUDIO_REG__

#include "klib.h"
#include "driver_common.h"


#define DD_TYPE_AUDIO_REG				(dd_audio_reg_get_type())
#define DD_AUDIO_REG(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdAudioReg))
#define DD_IS_AUDIO_REG(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_AUDIO_REG))


typedef struct _DdAudioReg 			DdAudioReg;
typedef struct _DdAudioRegPrivate 	DdAudioRegPrivate;
typedef VOID (*DdAudioRegFunc)(DdAudioReg *audioReg);	/**< Callback function pointer	*/

struct  _DdAudioReg {
	KObject parent;
};


#ifdef __cplusplus
extern "C" {
#endif


KConstType 		dd_audio_reg_get_type(void);
DdAudioReg* 	dd_audio_reg_new(void);

INT32 			dd_audio_reg_set_enable_in_full_intr(DdAudioReg* self, UINT8 ch, UINT8 enable);
INT32 			dd_audio_reg_set_enable_out_empty_intr(DdAudioReg* self, UINT8 ch, UINT8 enable);
BOOL 			dd_audio_reg_get_audio_in_enable_flag(DdAudioReg* self, UINT8 ch);
BOOL 			dd_audio_reg_get_audio_out_enable_flag(DdAudioReg* self, UINT8 ch);
INT32 			dd_audio_reg_clear_out_underflow_flag(DdAudioReg* self, UINT8 ch);
INT32 			dd_audio_reg_set_enable_in_overflow_intr(DdAudioReg* self, UINT8 ch, UINT8 enable);
INT32 			dd_audio_reg_set_enable_out_underflow_intr(DdAudioReg* self, UINT8 ch, UINT8 enable);
INT32 			dd_audio_reg_set_enable_in_usage_intr(DdAudioReg* self, UINT8 ch, UINT8 enable);
INT32 			dd_audio_reg_clear_in_overflow_flag(DdAudioReg* self, UINT8 ch);
INT32 			dd_audio_reg_set_enable_out_usage_intr(DdAudioReg* self, UINT8 ch, UINT8 enable);

/**
Get address of register AUIDLR<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@retval Adress of register AUIDLR
*/
UINT32			dd_audio_reg_get_addr_reg_auidlr(DdAudioReg* self, UINT8 ch);

/**
Get address of register AUODLR<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@retval Adress of register AUODLR
*/
UINT32			dd_audio_reg_get_addr_reg_auodlr(DdAudioReg* self, UINT8 ch);

/**
Get address of register AUIDL<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@retval Adress of register AUIDL
*/
UINT32			dd_audio_reg_get_addr_reg_auidl(DdAudioReg* self, UINT8 ch);

/**
Get address of register AUIDR<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@retval Adress of register AUIDR
*/
UINT32			dd_audio_reg_get_addr_reg_auidr(DdAudioReg* self, UINT8 ch);

/**
Get address of register AUODL<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@retval Adress of register AUODL
*/
UINT32			dd_audio_reg_get_addr_reg_auodl(DdAudioReg* self, UCHAR ch);

/**
Get address of register AUODR<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@retval Adress of register AUODR
*/
UINT32			dd_audio_reg_get_addr_reg_auodr(DdAudioReg* self, UINT8 ch);

/**
Get address of register AUIDDMAPT<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@retval Adress of register AUIDDMAPT
*/
UINT32			dd_audio_reg_get_addr_reg_auiddmapt(DdAudioReg* self, UINT8 ch);

/**
Get address of register AUODDMAPT<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@retval Adress of register AUODDMAPT
*/
UINT32			dd_audio_reg_get_addr_reg_auoddmapt(DdAudioReg* self, UINT8 ch);

/**
Set enable the interrupt request caused by input register full<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[in]	enable	[1:enable interrupt request, 0:disable interrupt request]
@param[in]	callback	Callback function pointer
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32 			dd_audio_reg_set_enable_input_intr(DdAudioReg* self, UINT8 ch, UINT8 enable, DdAudioRegFunc callback);

/**
Set enable the interrupt request caused by output register empty<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[in]	enable	[1:enable interrupt request, 0:disable interrupt request]
@param[in]	callback	Callback function pointer
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32 			dd_audio_reg_set_enable_output_intr(DdAudioReg* self, UINT8 ch, UINT8 enable, DdAudioRegFunc callback);

/**
Set enable the interrupt request caused by data input register overflow<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[in]	enable	[1:enable interrupt request, 0:disable interrupt request]
@param[in]	callback	Callback function pointer
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32			dd_audio_reg_set_enable_in_over_flow_intr(DdAudioReg* self, UINT8 ch,
						UINT8 enable, DdAudioRegFunc callback);

/**
Set enable the interrupt request caused by data output register underflow<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[in]	enable	[1:enable interrupt request, 0:disable interrupt request]
@param[in]	callback	Callback function pointer
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32			dd_audio_reg_set_enable_out_under_flow_intr(DdAudioReg* self, UINT8 ch,
						UINT8 enable, DdAudioRegFunc callback);

/**
Get the operation status of FIFO stages 15-0 of input register<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@retval Value of register AUIFST
*/
UINT32			dd_audio_reg_get_input_fifo_status(DdAudioReg* self, UINT8 ch);

/**
Get the operation status of FIFO stages 15-0 of output register<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@retval Value of register AUOFST
*/
UINT32 			dd_audio_reg_get_output_fifo_status(DdAudioReg* self, UINT8 ch);

void 			dd_audio_reg_set_under_flow_func(DdAudioReg* self, DdAudioRegFunc underFlowFunc, int index);
DdAudioRegFunc 	dd_audio_reg_get_under_flow_func(DdAudioReg* self, int index);

#ifdef __cplusplus
}
#endif

#endif	// __DD_AUDIO_REG__

