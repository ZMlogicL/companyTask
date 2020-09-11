/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseSix类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseSix类
*@version 1.0.0
*
*/

#ifndef __CT_AUDIO_CASE_SIX_H__
#define __CT_AUDIO_CASE_SIX_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
#include "absctaudiocase.h"
G_BEGIN_DECLS

#define 	CT_TYPE_AUDIO_CASE_SIX			   			(ct_audio_case_six_get_type ())
#define 	CT_AUDIO_CASE_SIX(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_AUDIO_CASE_SIX, CtAudioCaseSix))
#define 	CT_AUDIO_CASE_SIX_CLASS(klass)	   	(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_AUDIO_CASE_SIX, CtAudioCaseSixClass))
#define 	CT_IS_AUDIO_CASE_SIX(widget)	   		(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_AUDIO_CASE_SIX))
#define 	CT_IS_AUDIO_CASE_SIX_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_AUDIO_CASE_SIX))
#define 	CT_AUDIO_CASE_SIX_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_AUDIO_CASE_SIX, CtAudioCaseSixClass))

typedef struct _CtAudioCaseSix         		CtAudioCaseSix;
typedef struct _CtAudioCaseSixClass    	CtAudioCaseSixClass;
typedef struct _CtAudioCaseSixPrivate  	CtAudioCaseSixPrivate;

struct _CtAudioCaseSix
{
	AbsCtAudioCase parent;
};

struct _CtAudioCaseSixClass
{
	AbsCtAudioCaseClass parentclass;
};

GType           				ct_audio_case_six_get_type (void);
CtAudioCaseSix        *ct_audio_case_six_new(void);

G_END_DECLS
#endif /* __K_AUDIO_CASE_SIX_H__ */

