/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseEight类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、CtAudioCaseEight类
*@version 1.0.0
*/

#ifndef __CT_AUDIO_CASE_EIGHT_H__
#define __CT_AUDIO_CASE_EIGHT_H__
#include <klib.h>
#include "absctaudiocase.h"

#define CT_TYPE_AUDIO_CASE_EIGHT   		(ct_audio_case_eight_get_type())
#define CT_IS_AUDIO_CASE_EIGHT(obj)    K_TYPE_CHECK_INSTANCE_TYPE(obj, CtAudioCaseEight)
#define CT_AUDIO_CASE_EIGHT(obj)     		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtAudioCaseEight))


typedef struct 				_CtAudioCaseEight CtAudioCaseEight;
typedef struct 				_CtAudioCaseEightPrivate CtAudioCaseEightPrivate;

struct _CtAudioCaseEight
{
	AbsCtAudioCase parent;
};


KConstType		            		ct_audio_case_eight_get_type(void);
CtAudioCaseEight             *ct_audio_case_eight_new(void);

#endif /* __K_AUDIO_CASE_EIGHT_H__ */

