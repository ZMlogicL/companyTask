/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseEleven类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、CtAudioCaseEleven类
*@version 1.0.0
*/

#ifndef __CT_AUDIO_CASE_ELEVEN_H__
#define __CT_AUDIO_CASE_ELEVEN_H__
#include <klib.h>
#include "absctaudiocase.h"

#define CT_TYPE_AUDIO_CASE_ELEVEN   		(ct_audio_case_eleven_get_type())
#define CT_IS_AUDIO_CASE_ELEVEN(obj)    	K_TYPE_CHECK_INSTANCE_TYPE(obj, CtAudioCaseEleven)
#define CT_AUDIO_CASE_ELEVEN(obj)     		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtAudioCaseEleven))


typedef struct 				_CtAudioCaseEleven CtAudioCaseEleven;
typedef struct 				_CtAudioCaseElevenPrivate CtAudioCaseElevenPrivate;

struct _CtAudioCaseEleven
{
	AbsCtAudioCase parent;
};


KConstType		            			ct_audio_case_eleven_get_type(void);
CtAudioCaseEleven              *ct_audio_case_eleven_new(void);

#endif /* __K_AUDIO_CASE_ELEVEN_H__ */

