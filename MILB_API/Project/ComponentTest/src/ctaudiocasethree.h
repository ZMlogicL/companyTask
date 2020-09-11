/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseThree类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseThree类
*@version 1.0.0
*
*/

#ifndef __CT_AUDIO_CASE_THREE_H__
#define __CT_AUDIO_CASE_THREE_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
#include "absctaudiocase.h"
G_BEGIN_DECLS

#define 	CT_TYPE_AUDIO_CASE_THREE			  		(ct_audio_case_three_get_type ())
#define 	CT_AUDIO_CASE_THREE(widget)		   		(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_AUDIO_CASE_THREE, CtAudioCaseThree))
#define 	CT_AUDIO_CASE_THREE_CLASS(klass)	   	(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_AUDIO_CASE_THREE, CtAudioCaseThreeClass))
#define 	CT_IS_AUDIO_CASE_THREE(widget)	   		(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_AUDIO_CASE_THREE))
#define 	CT_IS_AUDIO_CASE_THREE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_AUDIO_CASE_THREE))
#define 	CT_AUDIO_CASE_THREE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_AUDIO_CASE_THREE, CtAudioCaseThreeClass))

typedef struct _CtAudioCaseThree         			CtAudioCaseThree;
typedef struct _CtAudioCaseThreeClass    		CtAudioCaseThreeClass;
typedef struct _CtAudioCaseThreePrivate  	CtAudioCaseThreePrivate;

struct _CtAudioCaseThree
{
	AbsCtAudioCase parent;
};

struct _CtAudioCaseThreeClass
{
	AbsCtAudioCaseClass parentclass;
};

GType           				ct_audio_case_three_get_type (void);
CtAudioCaseThree   *ct_audio_case_three_new(void);

G_END_DECLS
#endif /* __K_AUDIO_CASE_THREE_H__ */

