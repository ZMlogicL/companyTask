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

#ifndef __DD_AUDIO_DMA_H__
#define __DD_AUDIO_DMA_H__

#include "klib.h"
#include "driver_common.h"


#define DD_TYPE_AUDIO_DMA				(dd_audio_dma_get_type())
#define DD_AUDIO_DMA(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdAudioDma))
#define DD_IS_AUDIO_DMA(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_AUDIO_DMA))


typedef struct _AudioDma AudioDma;

/** Audio DMA Control */
struct _AudioDma {
	UINT8	dma2Ch;									/**< DMA 2ch Transfer Enable<BR><BR>
													 Value Range:DdAudio_DISABLE / DdAudio_ENABLE<BR>
													 Default value : DdAudio_DISABLE */
	UINT16	dmaTrnsfCnt;							/**< DMA Transfer Sample Count<BR><BR>
													 Value Range:[0x0010 - 0xFFFE]<BR>
													 Default value : 0x0000 */
};


typedef struct _DdAudioDma 			DdAudioDma;
typedef struct _DdAudioDmaPrivate 	DdAudioDmaPrivate;

struct  _DdAudioDma {
	KObject parent;
};


#ifdef __cplusplus
extern "C" {
#endif

KConstType 	dd_audio_dma_get_type(void);
DdAudioDma* dd_audio_dma_new(void);

/**
Set DMA control information of input<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[in]	dmaSetting	DMA control information. See @ref AudioDma
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
INT32		dd_audio_dma_ctrl_dma_in(DdAudioDma *self, UINT8 ch, AudioDma* dmaSetting);

/**
Get DMA control information of input<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[out]	dmaSetting	DMA control information. See @ref AudioDma
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32		dd_audio_dma_get_ctrl_dma_in(DdAudioDma *self, UINT8 ch, AudioDma* dmaSetting);

/**
Set DMA control information of output<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[in]	dmaSetting	DMA control information. See @ref AudioDma
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
INT32		dd_audio_dma_ctrl_dma_out(DdAudioDma *self, UINT8 ch, AudioDma* dmaSetting);

/**
Set DMA control information of output<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[out]	dmaSetting	DMA control information. See @ref AudioDma
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
INT32		dd_audio_dma_get_ctrl_dma_out(DdAudioDma *self, UINT8 ch, AudioDma* dmaSetting);

/**
Set enable DMA start request when the input register is full<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[in]	enable	[1:enable DMA start request, 0:disable DMA start request]
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32		dd_audio_dma_set_enable_fifo_full_dmain(DdAudioDma *self, UINT8 ch, UINT8 enable);

/**
Set enable DMA start request when the output register is empty<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[in]	enable	[1:enable DMA start request, 0:disable DMA start request]
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32		dd_audio_dma_set_enable_fifo_empty_dma_out(DdAudioDma *self, UINT8 ch, UINT8 enable);

/**
Set enable DMA start request(input operation) according to FIFO Usage(See @ref AudioCtrlCommon)<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[in]	enable	[1:enable DMA start request, 0:disable DMA start request]
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32		dd_audio_dma_set_input_dma_request_enable(DdAudioDma *self, UINT8 ch, UINT8 enable);

/**
Set enable DMA start request(output operation) according to FIFO Usage(See @ref AudioCtrlCommon)<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[in]	enable	[1:enable DMA start request, 0:disable DMA start request]
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32		dd_audio_dma_set_output_dma_request_enable(DdAudioDma *self, UINT8 ch, UINT8 enable);

/**
Get input data DMA transfer sample count<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@retval sample count
*/
UINT16		dd_audio_dma_get_in_dma_sample(DdAudioDma *self, UINT8 ch);

/**
Get output data DMA transfer sample count<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@retval sample count
*/
UINT16		dd_audio_dma_get_out_dma_sample(DdAudioDma *self, UINT8 ch);

/**
Replace the write value to the input register(AUIDLR) by 1Byte unit<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[in]	enable  [1:Enable replacement, 0:Disable replacement]
@retval D_DDIM_OK					OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32		dd_audio_dma_set_swapbyte_auidlr(DdAudioDma *self, UINT8 ch, UINT8 enable);

/**
Replace the write value to the input register(AUIDLR) by 2Byte unit<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[in]	enable  [1:Enable replacement, 0:Disable replacement]
@retval D_DDIM_OK					OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32		dd_audio_dma_set_swap_hw_auidlr(DdAudioDma *self, UINT8 ch, UINT8 enable);

/**
Replace the write value to the input register(AUODLR) by 1Byte unit<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[in]	enable  [1:Enable replacement, 0:Disable replacement]
@retval D_DDIM_OK					OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32		dd_audio_dma_set_swap_byte_auodlr(DdAudioDma *self, UINT8 ch, UINT8 enable);

/**
Replace the write value to the input register(AUODLR) by 2Byte unit<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[in]	enable  [1:Enable replacement, 0:Disable replacement]
@retval D_DDIM_OK					OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
INT32		dd_audio_dma_set_swap_hw_auodlr(DdAudioDma *self, UINT8 ch, UINT8 enable);

void 		dd_audio_dma_set_in_2ch(DdAudioDma *self, UINT8 ch, UINT8 dma2ch);
void 		dd_audio_dma_set_in_trnsf_cnt(DdAudioDma *self, UINT8 ch, UINT16 trnsfCnt);
void 		dd_audio_dma_set_out_2ch(DdAudioDma *self, UINT8 ch, UINT8 dma2ch);
void 		dd_audio_dma_set_out_trnsf_cnt(DdAudioDma *self, UINT8 ch, UINT16 trnsfCnt);


#ifdef __cplusplus
}
#endif

#endif	// __DD_AUDIO_DMA_H__

