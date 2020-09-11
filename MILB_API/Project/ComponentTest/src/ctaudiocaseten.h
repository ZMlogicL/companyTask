/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseTen类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、CtAudioCaseTen类
*@version 1.0.0
*/

#ifndef __CT_AUDIO_CASE_TEN_H__
#define __CT_AUDIO_CASE_TEN_H__
#include <klib.h>
#include "absctaudiocase.h"

#define CT_TYPE_AUDIO_CASE_TEN   		(ct_audio_case_ten_get_type())
#define CT_IS_AUDIO_CASE_TEN(obj)    K_TYPE_CHECK_INSTANCE_TYPE(obj, CtAudioCaseTen)
#define CT_AUDIO_CASE_TEN(obj)     		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtAudioCaseTen))


typedef struct 				_CtAudioCaseTen CtAudioCaseTen;
typedef struct 				_CtAudioCaseTenPrivate CtAudioCaseTenPrivate;

struct _CtAudioCaseTen
{
	AbsCtAudioCase parent;
};


KConstType		            ct_audio_case_ten_get_type(void);
CtAudioCaseTen       *ct_audio_case_ten_new(void);

#endif /* __K_AUDIO_CASE_TEN_H__ */

