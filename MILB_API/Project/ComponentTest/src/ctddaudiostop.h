/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioStop类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_STOP_H__
#define __CT_DD_AUDIO_STOP_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_STOP			   			(ct_dd_audio_stop_get_type ())
#define 	CT_DD_AUDIO_STOP(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_STOP, CtDdAudioStop))
#define 	CT_DD_AUDIO_STOP_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_STOP, CtDdAudioStopClass))
#define 	CT_IS_DD_AUDIO_STOP(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_STOP))
#define 	CT_IS_DD_AUDIO_STOP_CLASS(klass)  		(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_STOP))
#define 	CT_DD_AUDIO_STOP_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_STOP, CtDdAudioStopClass))

typedef struct _CtDdAudioStop         			CtDdAudioStop;
typedef struct _CtDdAudioStopClass    		CtDdAudioStopClass;
typedef struct _CtDdAudioStopPrivate  		CtDdAudioStopPrivate;

struct _CtDdAudioStop
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioStopClass
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_stop_get_type (void);
CtDdAudioStop    *ct_dd_audio_stop_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_stop_input_test( CtDdAudioStop *self );
void 						ct_dd_audio_stop_output_test( CtDdAudioStop *self );
void 						ct_dd_audio_stop_loop_back_test( CtDdAudioStop *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_STOP_H_ */
