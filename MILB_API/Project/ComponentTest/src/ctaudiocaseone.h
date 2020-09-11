/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseOne类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseOne类
*@version 1.0.0
*
*/

#ifndef __CT_AUDIO_CASE_ONE_H__
#define __CT_AUDIO_CASE_ONE_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
#include "absctaudiocase.h"
G_BEGIN_DECLS

#define 	CT_TYPE_AUDIO_CASE_ONE			   			(ct_audio_case_one_get_type ())
#define 	CT_AUDIO_CASE_ONE(widget)		  			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_AUDIO_CASE_ONE, CtAudioCaseOne))
#define 	CT_AUDIO_CASE_ONE_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_AUDIO_CASE_ONE, CtAudioCaseOneClass))
#define 	CT_IS_AUDIO_CASE_ONE(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_AUDIO_CASE_ONE))
#define 	CT_IS_AUDIO_CASE_ONE_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_AUDIO_CASE_ONE))
#define 	CT_AUDIO_CASE_ONE_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_AUDIO_CASE_ONE, CtAudioCaseOneClass))

typedef struct _CtAudioCaseOne         		CtAudioCaseOne;
typedef struct _CtAudioCaseOneClass    	CtAudioCaseOneClass;
typedef struct _CtAudioCaseOnePrivate  	CtAudioCaseOnePrivate;

struct _CtAudioCaseOne
{
	AbsCtAudioCase parent;
};

struct _CtAudioCaseOneClass
{
	AbsCtAudioCaseClass parentclass;
};

GType           				ct_audio_case_one_get_type (void);
CtAudioCaseOne 	  *ct_audio_case_one_new(void);

void 							ct_dd_audio_one_if_main(gint argc, kchar** argv);

G_END_DECLS
#endif /* __K_AUDIO_CASE_ONE_H__ */

