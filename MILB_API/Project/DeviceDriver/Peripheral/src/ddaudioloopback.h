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


#ifndef __DD_AUDIO_LOOPBACK_H__
#define __DD_AUDIO_LOOPBACK_H__

#include "klib.h"
#include "driver_common.h"


#define DD_TYPE_AUDIO_LOOPBACK				(dd_audio_loopback_get_type())
#define DD_AUDIO_LOOPBACK(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdAudioLoopback))
#define DD_IS_AUDIO_LOOPBACK(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_AUDIO_LOOPBACK))


typedef struct _DdAudioLoopback 		DdAudioLoopback;
typedef struct _DdAudioLoopbackPrivate 	DdAudioLoopbackPrivate;

struct  _DdAudioLoopback {
	KObject parent;
};


#ifdef __cplusplus
extern "C" {
#endif


KConstType 			dd_audio_loopback_get_type(void);
DdAudioLoopback* 	dd_audio_loopback_new(void);

BOOL 				dd_audio_loopback_flag_get(DdAudioLoopback* self, UINT8 ch);

/**
Start loopback operation<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH0_CH1</ul>
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
INT32				dd_audio_loopback_start(DdAudioLoopback* self, UINT8 ch);

/**
Stop loopBack operation<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH0_CH1</ul>
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
INT32				dd_audio_loopback_stop(DdAudioLoopback* self, UINT8 ch);

/**
Get status of loopback operation<br>
@param[in]	ch channel[0 - 2]
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2</ul>
@retval	TRUE:loopback operation is performed.
@retval	FALSE:loopback operation is not performed.
*/
BOOL				dd_audio_loopback_get_status(DdAudioLoopback* self, UCHAR ch);


#ifdef __cplusplus
}
#endif

#endif	// __DD_AUDIO_LOOPBACK_H__

