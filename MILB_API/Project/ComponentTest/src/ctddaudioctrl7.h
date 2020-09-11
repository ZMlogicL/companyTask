/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl7类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_CTRL7_H__
#define __CT_DD_AUDIO_CTRL7_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_CTRL7			   			(ct_dd_audio_ctrl7_get_type ())
#define 	CT_DD_AUDIO_CTRL7(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_CTRL7, CtDdAudioCtrl7))
#define 	CT_DD_AUDIO_CTRL7_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_CTRL7, CtDdAudioCtrl7Class))
#define 	CT_IS_DD_AUDIO_CTRL7(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_CTRL7))
#define 	CT_IS_DD_AUDIO_CTRL7_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_CTRL7))
#define 	CT_DD_AUDIO_CTRL7_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_CTRL7, CtDdAudioCtrl7Class))

typedef struct _CtDdAudioCtrl7         		CtDdAudioCtrl7;
typedef struct _CtDdAudioCtrl7Class    	CtDdAudioCtrl7Class;
typedef struct _CtDdAudioCtrl7Private  	CtDdAudioCtrl7Private;

struct _CtDdAudioCtrl7
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioCtrl7Class
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_ctrl7_get_type (void);
CtDdAudioCtrl7    *ct_dd_audio_ctrl7_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_ctrl7_i2scmmn_test34( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test35( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test36( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test37( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test38( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test39( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test40( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test41( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test42( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test43( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test44( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test45( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test46( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test47( CtDdAudioCtrl7 *self );
void 						ct_dd_audio_ctrl7_i2scmmn_test48( CtDdAudioCtrl7 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_CTRL7_H_ */
