/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioGet类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_GET_H__
#define __CT_DD_AUDIO_GET_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_GET			   			(ct_dd_audio_get_get_type ())
#define 	CT_DD_AUDIO_GET(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_GET, CtDdAudioGet))
#define 	CT_DD_AUDIO_GET_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_GET, CtDdAudioGetClass))
#define 	CT_IS_DD_AUDIO_GET(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget),\
				CT_TYPE_DD_AUDIO_GET))
#define 	CT_IS_DD_AUDIO_GET_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_GET))
#define 	CT_DD_AUDIO_GET_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_GET, CtDdAudioGetClass))

typedef struct _CtDdAudioGet         		CtDdAudioGet;
typedef struct _CtDdAudioGetClass    	CtDdAudioGetClass;
typedef struct _CtDdAudioGetPrivate  	CtDdAudioGetPrivate;

struct _CtDdAudioGet
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioGetClass
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_get_get_type (void);
CtDdAudioGet      *ct_dd_audio_get_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_get_ctrl_common_test1( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_common_test2( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_input_test1( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_input_test2( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_output_test1( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_output_test2( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_i2scmmn_test1( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_i2scmmn_test2( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_i2sin_test1( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_i2sin_test2( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_i2sout_test1( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_i2sout_test2( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_dmain_test1( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_dmain_test2( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_dmaout_test1( CtDdAudioGet *self );
void 						ct_dd_audio_get_ctrl_dmaout_test2( CtDdAudioGet *self );
void 						ct_dd_audio_get_status_input_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_status_output_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_status_loop_back_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_in_dmasample_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_out_dmasample_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_addr_reg_auidlr_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_addr_reg_auodlr_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_addr_reg_auidl_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_addr_reg_auidr_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_addr_reg_auodl_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_addr_reg_auodr_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_addr_reg_auiddmapt_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_addr_reg_auoddmapt_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_input_fifo_status_test( CtDdAudioGet *self );
void 						ct_dd_audio_get_output_fifo_status_test( CtDdAudioGet *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_GET_H_ */
