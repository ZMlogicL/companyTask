/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl4类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_CTRL4_H__
#define __CT_DD_AUDIO_CTRL4_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_CTRL4			   			(ct_dd_audio_ctrl4_get_type ())
#define 	CT_DD_AUDIO_CTRL4(widget)		  			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_CTRL4, CtDdAudioCtrl4))
#define 	CT_DD_AUDIO_CTRL4_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_CTRL4, CtDdAudioCtrl4Class))
#define 	CT_IS_DD_AUDIO_CTRL4(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_CTRL4))
#define 	CT_IS_DD_AUDIO_CTRL4_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_CTRL4))
#define 	CT_DD_AUDIO_CTRL4_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_CTRL4, CtDdAudioCtrl4Class))

typedef struct _CtDdAudioCtrl4         			CtDdAudioCtrl4;
typedef struct _CtDdAudioCtrl4Class    		CtDdAudioCtrl4Class;
typedef struct _CtDdAudioCtrl4Private  		CtDdAudioCtrl4Private;

struct _CtDdAudioCtrl4
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioCtrl4Class
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_ctrl4_get_type (void);
CtDdAudioCtrl4    *ct_dd_audio_ctrl4_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_ctrl4_output_test33( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_output_test34( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_output_test35( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_output_test36( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_output_test37( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_output_test38( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_output_test39( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_output_test40( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_output_test41( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_output_test42( CtDdAudioCtrl4 *self );
void						ct_dd_audio_ctrl4_output_test43( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_output_test44( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_output_test45( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_i2scmmn_test1( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_i2scmmn_test2( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_i2scmmn_test3( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_i2scmmn_test4( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_i2scmmn_test5( CtDdAudioCtrl4 *self );
void 						ct_dd_audio_ctrl4_i2scmmn_test6( CtDdAudioCtrl4 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_CTRL4_H_ */
