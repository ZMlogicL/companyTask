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


#ifndef __DD_AUDIO_IO_H__
#define __DD_AUDIO_IO_H__

#include "klib.h"
#include "driver_common.h"


#define DD_TYPE_AUDIO_IO			(dd_audio_io_get_type())
#define DD_AUDIO_IO(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, DdAudioIo))
#define DD_IS_AUDIO_IO(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_AUDIO_IO))


typedef struct _DdAudioIo 			DdAudioIo;
typedef struct _DdAudioIoPrivate 	DdAudioIoPrivate;

struct  _DdAudioIo {
	KObject parent;
};


#ifdef __cplusplus
extern "C" {
#endif


KConstType 	dd_audio_io_get_type(void);
DdAudioIo* 	dd_audio_io_new(void);

/**
Start input operation<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5
							<li>@ref DdAudio_IF_CH0_CH1</ul>
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
INT32		dd_audio_io_start_input(DdAudioIo* self, UINT8 ch);

/**
Stop input operation<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5
							<li>@ref DdAudio_IF_CH0_CH1</ul>
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
@remarks This API uses DDIM_User_Dly_Tsk().
*/
INT32		dd_audio_io_stop_input(DdAudioIo* self, UINT8 ch);

/**
Get status of input operation of audio interface<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@retval	TRUE:input operation is performed.
@retval	FALSE:input operation is not performed.
*/
BOOL		dd_audio_io_get_status_input(DdAudioIo* self, UINT8 ch);

/**
Start output operation<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3
							<li>@ref DdAudio_IF_CH0_CH1</ul>
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
INT32		dd_audio_io_start_output(DdAudioIo* self, UINT8 ch);

/**
Stop output operation<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3
							<li>@ref DdAudio_IF_CH0_CH1</ul>
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
@remarks This API uses DDIM_User_Dly_Tsk().
*/
INT32		dd_audio_io_stop_output(DdAudioIo* self, UINT8 ch);

/**
Get status of output operation of audio interface<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@retval	TRUE:output operation is performed.
@retval	FALSE:output is fixed to "0".
*/
BOOL		dd_audio_io_get_status_output(DdAudioIo* self, UINT8 ch);


#ifdef __cplusplus
}
#endif

#endif	// __DD_AUDIO_IO_H__

