/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseFive类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseFive类
*@version 1.0.0
*
*/

#ifndef __CT_AUDIO_CASE_FIVE_H__
#define __CT_AUDIO_CASE_FIVE_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
#include "absctaudiocase.h"
G_BEGIN_DECLS

#define 	CT_TYPE_AUDIO_CASE_FIVE			   			(ct_audio_case_five_get_type ())
#define 	CT_AUDIO_CASE_FIVE(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_AUDIO_CASE_FIVE, CtAudioCaseFive))
#define 	CT_AUDIO_CASE_FIVE_CLASS(klass)	  		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_AUDIO_CASE_FIVE, CtAudioCaseFiveClass))
#define 	CT_IS_AUDIO_CASE_FIVE(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_AUDIO_CASE_FIVE))
#define 	CT_IS_AUDIO_CASE_FIVE_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_AUDIO_CASE_FIVE))
#define 	CT_AUDIO_CASE_FIVE_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_AUDIO_CASE_FIVE, CtAudioCaseFiveClass))

typedef struct _CtAudioCaseFive         		CtAudioCaseFive;
typedef struct _CtAudioCaseFiveClass    	CtAudioCaseFiveClass;
typedef struct _CtAudioCaseFivePrivate  	CtAudioCaseFivePrivate;

struct _CtAudioCaseFive
{
	AbsCtAudioCase parent;
};

struct _CtAudioCaseFiveClass
{
	AbsCtAudioCaseClass parentclass;
};

GType           				ct_audio_case_five_get_type (void);
CtAudioCaseFive      *ct_audio_case_five_new(void);

G_END_DECLS
#endif /* __K_AUDIO_CASE_FIVE_H__ */

