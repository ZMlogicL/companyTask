/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseFour类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseFour类
*@version 1.0.0
*
*/

#ifndef __CT_AUDIO_CASE_FOUR_H__
#define __CT_AUDIO_CASE_FOUR_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
#include "absctaudiocase.h"
G_BEGIN_DECLS

#define 	CT_TYPE_AUDIO_CASE_FOUR			   		(ct_audio_case_four_get_type ())
#define 	CT_AUDIO_CASE_FOUR(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_AUDIO_CASE_FOUR, CtAudioCaseFour))
#define 	CT_AUDIO_CASE_FOUR_CLASS(klass)	   	(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_AUDIO_CASE_FOUR, CtAudioCaseFourClass))
#define 	CT_IS_AUDIO_CASE_FOUR(widget)	   		(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_AUDIO_CASE_FOUR))
#define 	CT_IS_AUDIO_CASE_FOUR_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass),\
				CT_TYPE_AUDIO_CASE_FOUR))
#define 	CT_AUDIO_CASE_FOUR_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_AUDIO_CASE_FOUR, CtAudioCaseFourClass))

typedef struct _CtAudioCaseFour         			CtAudioCaseFour;
typedef struct _CtAudioCaseFourClass    		CtAudioCaseFourClass;
typedef struct _CtAudioCaseFourPrivate  		CtAudioCaseFourPrivate;

struct _CtAudioCaseFour
{
	AbsCtAudioCase parent;
};

struct _CtAudioCaseFourClass
{
	AbsCtAudioCaseClass parentclass;
};

GType           				ct_audio_case_four_get_type (void);
CtAudioCaseFour     *ct_audio_case_four_new(void);

G_END_DECLS
#endif /* __K_AUDIO_CASE_FOUR_H__ */

