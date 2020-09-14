/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseEleven类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseEleven类
*@version 1.0.0
*/

#ifndef __CT_AUDIO_CASE_ELEVEN_H__
#define __CT_AUDIO_CASE_ELEVEN_H__

#include <glib-object.h>
#include "absctaudiocase.h"

G_BEGIN_DECLS

#define CT_TYPE_AUDIO_CASE_ELEVEN						(ct_audio_case_eleven_get_type())
#define CT_AUDIO_CASE_ELEVEN(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtAudioCaseEleven))
#define CT_AUDIO_CASE_ELEVEN_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_AUDIO_CASE_ELEVEN, CtAudioCaseElevenClass))
#define CT_IS_AUDIO_CASE_ELEVEN(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_AUDIO_CASE_ELEVEN))
#define CT_IS_AUDIO_CASE_ELEVEN_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_AUDIO_CASE_ELEVEN))
#define CT_AUDIO_CASE_ELEVEN_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_AUDIO_CASE_ELEVEN, CtAudioCaseElevenClass))

typedef struct 			_CtAudioCaseEleven CtAudioCaseEleven;
typedef struct 			_CtAudioCaseElevenClass CtAudioCaseElevenClass;
typedef struct 			_CtAudioCaseElevenPrivate CtAudioCaseElevenPrivate;

struct _CtAudioCaseEleven
{
	AbsCtAudioCase parent;
};

struct _CtAudioCaseElevenClass
{
	AbsCtAudioCaseClass parentclass;
};

GType		            					ct_audio_case_eleven_get_type(void);
CtAudioCaseEleven              *ct_audio_case_eleven_new(void);

G_END_DECLS

#endif /* __K_AUDIO_CASE_ELEVEN_H__ */

