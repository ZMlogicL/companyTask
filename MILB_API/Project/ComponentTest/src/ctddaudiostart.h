/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioStart类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_START_H__
#define __CT_DD_AUDIO_START_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_START			   			(ct_dd_audio_start_get_type ())
#define 	CT_DD_AUDIO_START(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_START, CtDdAudioStart))
#define 	CT_DD_AUDIO_START_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_START, CtDdAudioStartClass))
#define 	CT_IS_DD_AUDIO_START(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_START))
#define 	CT_IS_DD_AUDIO_START_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_START))
#define 	CT_DD_AUDIO_START_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_START, CtDdAudioStartClass))

typedef struct _CtDdAudioStart         		CtDdAudioStart;
typedef struct _CtDdAudioStartClass    	CtDdAudioStartClass;
typedef struct _CtDdAudioStartPrivate  	CtDdAudioStartPrivate;

struct _CtDdAudioStart
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioStartClass
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_start_get_type (void);
CtDdAudioStart    *ct_dd_audio_start_new(gpointer *temp, guint8 ch);

CtDdAudioStart    *ct_dd_audio_start_set_ch(CtDdAudioStart *self, guint8 ch);
void 						ct_dd_audio_start_input_test1( CtDdAudioStart *self );
void 						ct_dd_audio_start_input_test2( CtDdAudioStart *self );
void 						ct_dd_audio_start_input_test_multi01( CtDdAudioStart *self );
void 						ct_dd_audio_start_input_test_multi45( CtDdAudioStart *self );
void 						ct_dd_audio_start_output_test1( CtDdAudioStart *self );
void 						ct_dd_audio_start_output_test2( CtDdAudioStart *self );
void 						ct_dd_audio_start_output_test_multi( CtDdAudioStart *self );
void 						ct_dd_audio_start_loop_back_test1( CtDdAudioStart *self );
void 						ct_dd_audio_start_loop_back_test2( CtDdAudioStart *self );
void 						ct_dd_audio_start_loop_back_test3( CtDdAudioStart *self );
void 						ct_dd_audio_start_loop_back_test_multi( CtDdAudioStart *self );
void 						ct_dd_audio_start_loop_back_test_multi2( CtDdAudioStart *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_START_H_ */
