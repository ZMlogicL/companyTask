/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseSeven类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseSeven类
*@version 1.0.0
*
*/

#ifndef __CT_AUDIO_CASE_SEVEN_H__
#define __CT_AUDIO_CASE_SEVEN_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
#include "absctaudiocase.h"
G_BEGIN_DECLS

#define 	CT_TYPE_AUDIO_CASE_SEVEN			   			(ct_audio_case_seven_get_type ())
#define 	CT_AUDIO_CASE_SEVEN(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_AUDIO_CASE_SEVEN, CtAudioCaseSeven))
#define 	CT_AUDIO_CASE_SEVEN_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_AUDIO_CASE_SEVEN, CtAudioCaseSevenClass))
#define 	CT_IS_AUDIO_CASE_SEVEN(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_AUDIO_CASE_SEVEN))
#define 	CT_IS_AUDIO_CASE_SEVEN_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_AUDIO_CASE_SEVEN))
#define 	CT_AUDIO_CASE_SEVEN_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_AUDIO_CASE_SEVEN, CtAudioCaseSevenClass))

typedef struct _CtAudioCaseSeven         			CtAudioCaseSeven;
typedef struct _CtAudioCaseSevenClass    			CtAudioCaseSevenClass;
typedef struct _CtAudioCaseSevenPrivate  		CtAudioCaseSevenPrivate;

struct _CtAudioCaseSeven
{
	AbsCtAudioCase parent;
};

struct _CtAudioCaseSevenClass
{
	AbsCtAudioCaseClass parentclass;
};

GType           				ct_audio_case_seven_get_type (void);
CtAudioCaseSeven   *ct_audio_case_seven_new(void);

G_END_DECLS
#endif /* __K_AUDIO_CASE_SEVEN_H__ */

