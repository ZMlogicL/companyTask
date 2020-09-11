/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioSet3类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_SET3_H__
#define __CT_DD_AUDIO_SET3_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_SET3			   				(ct_dd_audio_set3_get_type ())
#define 	CT_DD_AUDIO_SET3(widget)		  		 		(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_SET3, CtDdAudioSet3))
#define 	CT_DD_AUDIO_SET3_CLASS(klass)	   			(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_SET3, CtDdAudioSet3Class))
#define 	CT_IS_DD_AUDIO_SET3(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_SET3))
#define 	CT_IS_DD_AUDIO_SET3_CLASS(klass)  		(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_SET3))
#define 	CT_DD_AUDIO_SET3_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_SET3, CtDdAudioSet3Class))

typedef struct _CtDdAudioSet3         			CtDdAudioSet3;
typedef struct _CtDdAudioSet3Class    		CtDdAudioSet3Class;
typedef struct _CtDdAudioSet3Private  		CtDdAudioSet3Private;

struct _CtDdAudioSet3
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioSet3Class
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_set3_get_type (void);
CtDdAudioSet3     *ct_dd_audio_set3_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_set3_enable_output_intr_test10( CtDdAudioSet3 *self );
void 						ct_dd_audio_set3_enable_output_intr_test11( CtDdAudioSet3 *self );
void 						ct_dd_audio_set3_enable_output_intr_test12( CtDdAudioSet3 *self );
void 						ct_dd_audio_set3_enable_in_over_flow_intr_test1( CtDdAudioSet3 *self );
void 						ct_dd_audio_set3_enable_in_over_flow_intr_test2( CtDdAudioSet3 *self );
void 						ct_dd_audio_set3_enable_in_over_flow_intr_test3( CtDdAudioSet3 *self );
void 						ct_dd_audio_set3_enable_in_over_flow_intr_test4( CtDdAudioSet3 *self );
void 						ct_dd_audio_set3_enable_out_under_flow_intr_test1( CtDdAudioSet3 *self );
void 						ct_dd_audio_set3_enable_out_under_flow_intr_test2( CtDdAudioSet3 *self );
void 						ct_dd_audio_set3_enable_out_under_flow_intr_test3( CtDdAudioSet3 *self );
void 						ct_dd_audio_set3_enable_out_under_flow_intr_test4( CtDdAudioSet3 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_SET3_H_ */
