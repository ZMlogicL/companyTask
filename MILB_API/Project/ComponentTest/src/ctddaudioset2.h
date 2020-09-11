/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioSet2类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_SET2_H__
#define __CT_DD_AUDIO_SET2_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_SET2			  	 		(ct_dd_audio_set2_get_type ())
#define 	CT_DD_AUDIO_SET2(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_SET2, CtDdAudioSet2))
#define 	CT_DD_AUDIO_SET2_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_SET2, CtDdAudioSet2Class))
#define 	CT_IS_DD_AUDIO_SET2(widget)	   		(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_SET2))
#define 	CT_IS_DD_AUDIO_SET2_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_SET2))
#define 	CT_DD_AUDIO_SET2_GET_CLASS(obj)  	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_SET2, CtDdAudioSet2Class))

typedef struct _CtDdAudioSet2         			CtDdAudioSet2;
typedef struct _CtDdAudioSet2Class    		CtDdAudioSet2Class;
typedef struct _CtDdAudioSet2Private  		CtDdAudioSet2Private;

struct _CtDdAudioSet2
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioSet2Class
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_set2_get_type (void);
CtDdAudioSet2  	  *ct_dd_audio_set2_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_set2_swapbyte_auodlr_test6( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_swapbyte_auodlr_test7( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_swapbyte_auodlr_test8( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_input_intr_test1( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_input_intr_test2( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_input_intr_test3( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_input_intr_test4( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_input_intr_test5( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_input_intr_test6( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_input_intr_test7( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_input_intr_test8( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_input_intr_test9( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_input_intr_test10( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_input_intr_test11( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_input_intr_test12( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_output_intr_test1( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_output_intr_test2( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_output_intr_test3( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_output_intr_test4( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_output_intr_test5( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_output_intr_test6( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_output_intr_test7( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_output_intr_test8( CtDdAudioSet2 *self );
void 						ct_dd_audio_set2_enable_output_intr_test9( CtDdAudioSet2 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_SET2_H_ */
