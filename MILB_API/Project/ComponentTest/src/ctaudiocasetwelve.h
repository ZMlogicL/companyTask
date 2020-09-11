/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseTwelve类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、CtAudioCaseTwelve类
*@version 1.0.0
*/

#ifndef __CT_AUDIO_CASE_TWELVE_H__
#define __CT_AUDIO_CASE_TWELVE_H__
#include <klib.h>
#include "absctaudiocase.h"

#define CT_TYPE_AUDIO_CASE_TWELVE   		(ct_audio_case_twelve_get_type())
#define CT_IS_AUDIO_CASE_TWELVE(obj)    	K_TYPE_CHECK_INSTANCE_TYPE(obj, CtAudioCaseTwelve)
#define CT_AUDIO_CASE_TWELVE(obj)     		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtAudioCaseTwelve))


typedef struct 				_CtAudioCaseTwelve CtAudioCaseTwelve;
typedef struct 				_CtAudioCaseTwelvePrivate CtAudioCaseTwelvePrivate;

struct _CtAudioCaseTwelve
{
	AbsCtAudioCase parent;
};


KConstType		            ct_audio_case_twelve_get_type(void);
CtAudioCaseTwelve  *ct_audio_case_twelve_new(void);

#endif /* __K_AUDIO_CASE_TWELVE_H__ */


