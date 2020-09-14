/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseNine类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseNine类
*@version 1.0.0
*/

#ifndef __CT_AUDIO_CASE_NINE_H__
#define __CT_AUDIO_CASE_NINE_H__
#include <glib-object.h>
#include "absctaudiocase.h"

G_BEGIN_DECLS

#define CT_TYPE_AUDIO_CASE_NINE					(ct_audio_case_nine_get_type())
#define CT_AUDIO_CASE_NINE(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtAudioCaseNine))
#define CT_AUDIO_CASE_NINE_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_AUDIO_CASE_NINE, CtAudioCaseNineClass))
#define CT_IS_AUDIO_CASE_NINE(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_AUDIO_CASE_NINE))
#define CT_IS_AUDIO_CASE_NINE_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_AUDIO_CASE_NINE))
#define CT_AUDIO_CASE_NINE_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_AUDIO_CASE_NINE, CtAudioCaseNineClass))

typedef struct 			_CtAudioCaseNine CtAudioCaseNine;
typedef struct 			_CtAudioCaseNineClass CtAudioCaseNineClass;
typedef struct 			_CtAudioCaseNinePrivate CtAudioCaseNinePrivate;

struct _CtAudioCaseNine
{
	AbsCtAudioCase parent;
};

struct _CtAudioCaseNineClass
{
	AbsCtAudioCaseClass parentclass;
};

GType		            			ct_audio_case_nine_get_type(void);
CtAudioCaseNine    	  *ct_audio_case_nine_new(void);

G_END_DECLS

#endif /* __K_AUDIO_CASE_NINE_H__ */

