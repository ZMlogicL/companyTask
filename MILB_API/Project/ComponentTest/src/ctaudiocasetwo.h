/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseTwo类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseTwo类
*@version 1.0.0
*
*/

#ifndef __CT_AUDIO_CASE_TWO_H__
#define __CT_AUDIO_CASE_TWO_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
#include "absctaudiocase.h"
G_BEGIN_DECLS

#define 	CT_TYPE_AUDIO_CASE_TWO			   			(ct_audio_case_two_get_type ())
#define 	CT_AUDIO_CASE_TWO(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_AUDIO_CASE_TWO, CtAudioCaseTwo))
#define 	CT_AUDIO_CASE_TWO_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_AUDIO_CASE_TWO, CtAudioCaseTwoClass))
#define 	CT_IS_AUDIO_CASE_TWO(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_AUDIO_CASE_TWO))
#define 	CT_IS_AUDIO_CASE_TWO_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_AUDIO_CASE_TWO))
#define 	CT_AUDIO_CASE_TWO_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_AUDIO_CASE_TWO, CtAudioCaseTwoClass))

typedef struct _CtAudioCaseTwo         CtAudioCaseTwo;
typedef struct _CtAudioCaseTwoClass    CtAudioCaseTwoClass;
typedef struct _CtAudioCaseTwoPrivate  CtAudioCaseTwoPrivate;

struct _CtAudioCaseTwo
{
	AbsCtAudioCase parent;
};

struct _CtAudioCaseTwoClass
{
	AbsCtAudioCaseClass parentclass;
};

GType           				ct_audio_case_two_get_type (void);
CtAudioCaseTwo      *ct_audio_case_two_new(void);

G_END_DECLS
#endif /* __K_AUDIO_CASE_TWO_H__ */

