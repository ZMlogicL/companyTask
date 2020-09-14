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

#ifndef __DD_AUDIO_CTRL_H__
#define __DD_AUDIO_CTRL_H__

#include "klib.h"
#include "driver_common.h"


#define DD_TYPE_AUDIO_CTRL				(dd_audio_ctrl_get_type())
#define DD_AUDIO_CTRL(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdAudioCtrl))
#define DD_IS_AUDIO_CTRL(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_AUDIO_CTRL))

/** Data Output/Input Register Format */
typedef enum {
	DdAudioCtrl_DATA_REG_FRMT_R_JUST	= 0,								/**< Left justified */
	DdAudioCtrl_DATA_REG_FRMT_L_JUST										/**< Right justified */
} AudioDataRegFrmt;

/** FIFO Stages */
typedef enum {
	DdAudioCtrl_FIFO_STAGES_1	= 0,									/**< FIFO Stages 1 */
	DdAudioCtrl_FIFO_STAGES_16											/**< FIFO Stages 16 */
} AudioFifoStages;

/** AHB Bus Format */
typedef enum {
	DdAudioCtrl_AHB_FRMT_R_JUST	= 0,									/**< Right justified */
	DdAudioCtrl_AHB_FRMT_L_JUST											/**< Left justified */
} AudioAhbFrmt;

/** Data Shift */
typedef enum {
	DdAudioCtrl_BIT_SHIFT_0	= 0,										/**< Left shift of 0 bit */
	DdAudioCtrl_BIT_SHIFT_1,												/**< Left shift of 1 bit */
	DdAudioCtrl_BIT_SHIFT_2,												/**< Left shift of 2 bit */
	DdAudioCtrl_BIT_SHIFT_3												/**< Left shift of 3 bit */
} AudioBitShift;

/** FIFO Usage */
typedef enum {
	DdAudioCtrl_FIFO_USAGE_STAGES_1	= 0,								/**< FIFO Usages Status 1 stage */
	DdAudioCtrl_FIFO_USAGE_STAGES_12,									/**< FIFO Usages Status 12 stages */
	DdAudioCtrl_FIFO_USAGE_STAGES_8,										/**< FIFO Usages Status 8 stages */
	DdAudioCtrl_FIFO_USAGE_STAGES_4,										/**< FIFO Usages Status 4 stages */
	DdAudioCtrl_FIFO_USAGE_STAGES_16										/**< FIFO Usages Status 16 stages */
} AudioFifoUsage;

/** Audio Channel */
typedef enum {
	DdAudioCtrl_CHANNEL_MONO		= 0,									/**< Mono */
	DdAudioCtrl_CHANNEL_STEREO	= 1										/**< Stereo */
} AudioChannel;

typedef struct _AudioCtrlCommon AudioCtrlCommon;
typedef struct _AudioCtrlIn 	AudioCtrlIn;
typedef struct _AudioCtrlOut 	AudioCtrlOut;

/** Audio Control(Common) */
struct _AudioCtrlCommon {
	AudioFifoUsage		fifoUsage;									/**< FIFO Usage<BR><BR>
																 	 Default value : DdAudioCtrl_FIFO_USAGE_STAGES_8 */
	AudioChannel		channel;									/**< channel<BR><BR>
																	 Default value : DdAudioCtrl_CHANNEL_MONO */
};

/** Audio Control(Input) */
struct _AudioCtrlIn {
	AudioDataRegFrmt	format;										/**< Data Input Register Format<BR><BR>
																				 Default value : DdAudioCtrl_DATA_REG_FRMT_R_JUST */
	AudioFifoStages		fifoStages;								/**< input FIFO Stages of output register<BR><BR>
																				 Default value : DdAudioCtrl_FIFO_STAGES_1 */
	AudioAhbFrmt		ahbFormat;									/**< Input Data AHB Bus Format<BR><BR>
																				 Default value : DdAudioCtrl_AHB_FRMT_R_JUST */
	AudioBitShift		bitShift;									/**< Audio Input Data Shift<BR><BR>
																				 Default value : DdAudioCtrl_BIT_SHIFT_0 */
};

/** Audio Control(Output) */
struct _AudioCtrlOut {
	AudioDataRegFrmt	format;										/**< Data Output Register Format<BR><BR>
																				 Default value : DdAudioCtrl_DATA_REG_FRMT_R_JUST */
	AudioFifoStages		fifoStages;								/**< Output FIFO Stages of output register<BR><BR>
																				 Default value : DdAudioCtrl_FIFO_STAGES_1 */
	AudioAhbFrmt		ahbFormat;									/**< Output Data AHB Bus Format<BR><BR>
																	 Default value : DdAudioCtrl_AHB_FRMT_R_JUST */
	kuint8				lrCopy;									/**< Lch Data Rch Copy Enable <BR><BR>
																	 Value Range:DdAudio_DISABLE / DdAudio_ENABLE<BR>
																	 In the case of a audio interface slave mode, It is prohibited to set DdAudio_ENABLE. <BR><BR>
																	 Default value : DdAudio_DISABLE */
	kuint8				mixPlay;									/**< Mix Output Enable <BR><BR>
																	DdAudio_ENABLE: The data mixed Lch / Rch is output.<BR>
																	DdAudio_DISABLE: The normal data is output.<BR>
																	Value Range:DdAudio_DISABLE / DdAudio_ENABLE<BR>
																	Default value : DdAudio_DISABLE */
	AudioBitShift		bitShift;									/**< Audio Output Data Shift<BR><BR>
																				 Default value : DdAudioCtrl_BIT_SHIFT_0 */
};


typedef struct _DdAudioCtrl 		DdAudioCtrl;
typedef struct _DdAudioCtrlPrivate 	DdAudioCtrlPrivate;

struct  _DdAudioCtrl {
	KObject parent;
};

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
#ifdef __cplusplus
extern "C" {
#endif


KConstType 		dd_audio_ctrl_get_type(void);
DdAudioCtrl* 	dd_audio_ctrl_new(void);

/**
Set audio data control information(Common Setting)<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[in]	ctrlInf audio data control information. See @ref AudioCtrlCommon
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
kint32			dd_audio_ctrl_ctrl_common(DdAudioCtrl *self, kuint8 ch, AudioCtrlCommon* ctrlInf);

/**
Get audio data control information(Common Setting)<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[out]	ctrlInf audio data control information. See @ref AudioCtrlCommon
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 			dd_audio_ctrl_get_ctrl_common(DdAudioCtrl *self, kuint8 ch, AudioCtrlCommon* ctrlInf);

/**
Set audio input data control information<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[in]	ctrlInf audio data control information. See @ref AudioCtrlIn
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
kint32			dd_audio_ctrl_ctrl_input(DdAudioCtrl *self, kuint8 ch, AudioCtrlIn* ctrlInf);

/**
Get audio input data control information<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[out]	ctrlInf audio data control information. See @ref AudioCtrlIn
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 			dd_audio_ctrl_get_ctrl_input(DdAudioCtrl *self, kuint8 ch, AudioCtrlIn* ctrlInf);

/**
Set audio output data control information<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[in]	ctrlInf audio data control information. See @ref AudioCtrlOut
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
kint32			dd_audio_ctrl_ctrl_output(DdAudioCtrl *self, kuint8 ch, AudioCtrlOut* ctrlInf);

/**
Get audio output data control information<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[out]	ctrlInf audio data control information. See @ref AudioCtrlOut
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 			dd_audio_ctrl_get_ctrl_output(DdAudioCtrl *self, kuint8 ch, AudioCtrlOut* ctrlInf);

void 			dd_audio_ctrl_set_cmmn_fifo_usage(DdAudioCtrl *self, int index, AudioFifoUsage fifoUsage);
void 			dd_audio_ctrl_set_cmmn_channel(DdAudioCtrl *self, int index, AudioChannel channel);
AudioFifoUsage 	dd_audio_ctrl_get_cmmn_fifo_usage(DdAudioCtrl *self, int index);
AudioChannel 	dd_audio_ctrl_get_cmmn_channel(DdAudioCtrl *self, int index);

void 			dd_audio_ctrl_set_in_format(DdAudioCtrl *self, int index, AudioDataRegFrmt format);
void 			dd_audio_ctrl_set_in_fifo_stages(DdAudioCtrl *self, int index, AudioFifoStages fifoStages);
void 			dd_audio_ctrl_set_in_ahb_format(DdAudioCtrl *self, int index, AudioAhbFrmt ahbFormat);
void 			dd_audio_ctrl_set_in_bit_shift(DdAudioCtrl *self, int index, AudioBitShift bitShift);
AudioFifoStages dd_audio_ctrl_get_in_fifo_stages(DdAudioCtrl *self, int index);

void 			dd_audio_ctrl_set_out_format(DdAudioCtrl *self, int index, AudioDataRegFrmt format);
void 			dd_audio_ctrl_set_out_fifo_stages(DdAudioCtrl *self, int index, AudioFifoStages fifoStages);
void 			dd_audio_ctrl_set_out_ahb_format(DdAudioCtrl *self, int index, AudioAhbFrmt ahbFormat);
void 			dd_audio_ctrl_set_out_lr_copy(DdAudioCtrl *self, int index, kuint8 lrCopy);
void 			dd_audio_ctrl_set_out_mix_play(DdAudioCtrl *self, int index, kuint8 mixPlay);
void 			dd_audio_ctrl_set_out_bit_shift(DdAudioCtrl *self, int index, AudioBitShift bitShift);
AudioFifoStages dd_audio_ctrl_get_out_fifo_stages(DdAudioCtrl *self, int index);


#ifdef __cplusplus
}
#endif

#endif	// __DD_AUDIO_CTRL_H__


