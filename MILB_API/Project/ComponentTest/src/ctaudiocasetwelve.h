/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseTwelve类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseTwelve类
*@version 1.0.0
*/

#ifndef __CT_AUDIO_CASE_TWELVE_H__
#define __CT_AUDIO_CASE_TWELVE_H__
#include <glib-object.h>
#include "absctaudiocase.h"

G_BEGIN_DECLS

#define CT_TYPE_AUDIO_CASE_TWELVE					(ct_audio_case_twelve_get_type())
#define CT_AUDIO_CASE_TWELVE(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtAudioCaseTwelve))
#define CT_AUDIO_CASE_TWELVE_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_AUDIO_CASE_TWELVE, CtAudioCaseTwelveClass))
#define CT_IS_AUDIO_CASE_TWELVE(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_AUDIO_CASE_TWELVE))
#define CT_IS_AUDIO_CASE_TWELVE_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_AUDIO_CASE_TWELVE))
#define CT_AUDIO_CASE_TWELVE_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_AUDIO_CASE_TWELVE, CtAudioCaseTwelveClass))

typedef struct 			_CtAudioCaseTwelve CtAudioCaseTwelve;
typedef struct 			_CtAudioCaseTwelveClass CtAudioCaseTwelveClass;
typedef struct 			_CtAudioCaseTwelvePrivate CtAudioCaseTwelvePrivate;

struct _CtAudioCaseTwelve
{
	AbsCtAudioCase parent;
};

struct _CtAudioCaseTwelveClass
{
	AbsCtAudioCaseClass parentclass;
};

GType				            ct_audio_case_twelve_get_type(void);
CtAudioCaseTwelve  *ct_audio_case_twelve_new(void);

G_END_DECLS

#endif /* __K_AUDIO_CASE_TWELVE_H__ */


