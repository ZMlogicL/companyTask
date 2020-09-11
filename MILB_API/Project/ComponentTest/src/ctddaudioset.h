/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioSet类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_SET_H__
#define __CT_DD_AUDIO_SET_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_SET			   			(ct_dd_audio_set_get_type ())
#define 	CT_DD_AUDIO_SET(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_SET, CtDdAudioSet))
#define 	CT_DD_AUDIO_SET_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_SET, CtDdAudioSetClass))
#define 	CT_IS_DD_AUDIO_SET(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_SET))
#define 	CT_IS_DD_AUDIO_SET_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_SET))
#define 	CT_DD_AUDIO_SET_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_SET, CtDdAudioSetClass))

typedef struct _CtDdAudioSet         		CtDdAudioSet;
typedef struct _CtDdAudioSetClass    		CtDdAudioSetClass;
typedef struct _CtDdAudioSetPrivate  	CtDdAudioSetPrivate;

struct _CtDdAudioSet
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioSetClass
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_set_get_type (void);
CtDdAudioSet    	  *ct_dd_audio_set_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_set_enable_fifo_full_dmain_test1( CtDdAudioSet *self );
void 						ct_dd_audio_set_enable_fifo_full_dmain_test2( CtDdAudioSet *self );
void 						ct_dd_audio_set_enable_fifo_full_dmain_test3( CtDdAudioSet *self );
void 						ct_dd_audio_set_enable_fifo_full_dmain_test4( CtDdAudioSet *self );
void 						ct_dd_audio_set_enable_fifo_full_dmain_test5( CtDdAudioSet *self );
void 						ct_dd_audio_set_enable_fifo_empty_dma_out_test1( CtDdAudioSet *self );
void 						ct_dd_audio_set_enable_fifo_empty_dma_out_test2( CtDdAudioSet *self );
void 						ct_dd_audio_set_enable_fifo_empty_dma_out_test3( CtDdAudioSet *self );
void 						ct_dd_audio_set_enable_fifo_empty_dma_out_test4( CtDdAudioSet *self );
void 						ct_dd_audio_set_enable_fifo_empty_dma_out_test5( CtDdAudioSet *self );
void 						ct_dd_audio_set_input_dmarequest_enable_test1( CtDdAudioSet *self );
void 						ct_dd_audio_set_input_dmarequest_enable_test2( CtDdAudioSet *self );
void 						ct_dd_audio_set_input_dmarequest_enable_test3( CtDdAudioSet *self );
void 						ct_dd_audio_set_input_dmarequest_enable_test4( CtDdAudioSet *self );
void 						ct_dd_audio_set_input_dmarequest_enable_test5( CtDdAudioSet *self );
void 						ct_dd_audio_set_output_dmarequest_enable_test1( CtDdAudioSet *self );
void 						ct_dd_audio_set_output_dmarequest_enable_test2( CtDdAudioSet *self );
void 						ct_dd_audio_set_output_dmarequest_enable_test3( CtDdAudioSet *self );
void 						ct_dd_audio_set_output_dmarequest_enable_test4( CtDdAudioSet *self );
void 						ct_dd_audio_set_output_dmarequest_enable_test5( CtDdAudioSet *self );
void 						ct_dd_audio_set_swaphw_auidlr_test1( CtDdAudioSet *self );
void 						ct_dd_audio_set_swaphw_auidlr_test2( CtDdAudioSet *self );
void 						ct_dd_audio_set_swaphw_auidlr_test3( CtDdAudioSet *self );
void 						ct_dd_audio_set_swaphw_auidlr_test4( CtDdAudioSet *self );
void 						ct_dd_audio_set_swaphw_auidlr_test5( CtDdAudioSet *self );
void 						ct_dd_audio_set_swaphw_auidlr_test6( CtDdAudioSet *self );
void 						ct_dd_audio_set_swapbyte_auidlr_test1( CtDdAudioSet *self );
void 						ct_dd_audio_set_swapbyte_auidlr_test2( CtDdAudioSet *self );
void 						ct_dd_audio_set_swapbyte_auidlr_test3( CtDdAudioSet *self );
void 						ct_dd_audio_set_swapbyte_auidlr_test4( CtDdAudioSet *self );
void 						ct_dd_audio_set_swapbyte_auidlr_test5( CtDdAudioSet *self );
void 						ct_dd_audio_set_swapbyte_auidlr_test6( CtDdAudioSet *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_SET_H_ */
