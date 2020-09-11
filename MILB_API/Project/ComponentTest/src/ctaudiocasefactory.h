/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :luhongyin
*@brief               :CtAudioCaseFactory类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseFactory类
*@version 1.0.0
*
*/

#ifndef __CT_AUDIO_CASE_FACTORY_H__
#define __CT_AUDIO_CASE_FACTORY_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
#include "absctaudiocase.h"
G_BEGIN_DECLS

#define CT_TYPE_AUDIO_CASE_FACTORY			   (ct_audio_case_factory_get_type ())
#define CT_AUDIO_CASE_FACTORY(widget)		   (G_TYPE_CHECK_INSTANCE_CAST ((widget), CT_TYPE_AUDIO_CASE_FACTORY, CtAudioCaseFactory))
#define CT_AUDIO_CASE_FACTORY_CLASS(klass)	   (G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_AUDIO_CASE_FACTORY, CtAudioCaseFactoryClass))
#define CT_IS_AUDIO_CASE_FACTORY(widget)	   (G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_AUDIO_CASE_FACTORY))
#define CT_IS_AUDIO_CASE_FACTORY_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_AUDIO_CASE_FACTORY))
#define CT_AUDIO_CASE_FACTORY_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_AUDIO_CASE_FACTORY, CtAudioCaseFactoryClass))

typedef struct _CtAudioCaseFactory         CtAudioCaseFactory;
typedef struct _CtAudioCaseFactoryClass    CtAudioCaseFactoryClass;
typedef struct _CtAudioCaseFactoryPrivate  CtAudioCaseFactoryPrivate;

struct _CtAudioCaseFactory
{
	GObject parent;
};

struct _CtAudioCaseFactoryClass
{
	GObjectClass parentclass;
};

GType           						ct_audio_case_factory_get_type (void);
CtAudioCaseFactory         *ct_audio_case_factory_new(void);

AbsCtAudioCase  			  *ct_audio_case_factory_create_case(CtAudioCaseFactory *self, AbsCtAudioCaseType type);

G_END_DECLS
#endif /* __K_AUDIO_CASE_FACTORY_H__ */

