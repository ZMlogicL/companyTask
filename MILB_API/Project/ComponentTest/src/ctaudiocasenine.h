/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseNine类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、CtAudioCaseNine类
*@version 1.0.0
*/

#ifndef __CT_AUDIO_CASE_NINE_H__
#define __CT_AUDIO_CASE_NINE_H__
#include <klib.h>
#include "absctaudiocase.h"

#define CT_TYPE_AUDIO_CASE_NINE   		(ct_audio_case_nine_get_type())
#define CT_IS_AUDIO_CASE_NINE(obj)    	K_TYPE_CHECK_INSTANCE_TYPE(obj, CtAudioCaseNine)
#define CT_AUDIO_CASE_NINE(obj)     		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtAudioCaseNine))


typedef struct 				_CtAudioCaseNine CtAudioCaseNine;
typedef struct 				_CtAudioCaseNinePrivate CtAudioCaseNinePrivate;

struct _CtAudioCaseNine
{
	AbsCtAudioCase parent;
};


KConstType		            	ct_audio_case_nine_get_type(void);
CtAudioCaseNine    	  *ct_audio_case_nine_new(void);

#endif /* __K_AUDIO_CASE_NINE_H__ */

