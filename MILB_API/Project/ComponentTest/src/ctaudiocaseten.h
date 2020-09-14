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
#include <glib-object.h>
#include "absctaudiocase.h"

G_BEGIN_DECLS

#define CT_TYPE_AUDIO_CASE_TEN					(ct_audio_case_ten_get_type())
#define CT_AUDIO_CASE_TEN(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtAudioCaseTen))
#define CT_AUDIO_CASE_TEN_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_AUDIO_CASE_TEN, CtAudioCaseTenClass))
#define CT_IS_AUDIO_CASE_TEN(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_AUDIO_CASE_TEN))
#define CT_IS_AUDIO_CASE_TEN_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_AUDIO_CASE_TEN))
#define CT_AUDIO_CASE_TEN_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_AUDIO_CASE_TEN, CtAudioCaseTenClass))

typedef struct 			_CtAudioCaseTen CtAudioCaseTen;
typedef struct 			_CtAudioCaseTenClass CtAudioCaseTenClass;
typedef struct 			_CtAudioCaseTenPrivate CtAudioCaseTenPrivate;

struct _CtAudioCaseTen
{
	AbsCtAudioCase parent;
};

struct _CtAudioCaseTenClass
{
	AbsCtAudioCaseClass parentclass;
};

GType				            ct_audio_case_ten_get_type(void);
CtAudioCaseTen       *ct_audio_case_ten_new(void);

G_END_DECLS

#endif /* __K_AUDIO_CASE_TEN_H__ */

