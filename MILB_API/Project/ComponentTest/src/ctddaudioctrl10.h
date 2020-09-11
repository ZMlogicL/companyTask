/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl10类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_CTRL10_H__
#define __CT_DD_AUDIO_CTRL10_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_CTRL10			   			(ct_dd_audio_ctrl10_get_type ())
#define 	CT_DD_AUDIO_CTRL10(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_CTRL10, CtDdAudioCtrl10))
#define 	CT_DD_AUDIO_CTRL10_CLASS(klass)	   	(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_CTRL10, CtDdAudioCtrl10Class))
#define 	CT_IS_DD_AUDIO_CTRL10(widget)	   		(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_CTRL10))
#define 	CT_IS_DD_AUDIO_CTRL10_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_CTRL10))
#define 	CT_DD_AUDIO_CTRL10_GET_CLASS(obj)  	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_CTRL10, CtDdAudioCtrl10Class))

typedef struct _CtDdAudioCtrl10         		CtDdAudioCtrl10;
typedef struct _CtDdAudioCtrl10Class    	CtDdAudioCtrl10Class;
typedef struct _CtDdAudioCtrl10Private  	CtDdAudioCtrl10Private;

struct _CtDdAudioCtrl10
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioCtrl10Class
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_ctrl10_get_type (void);
CtDdAudioCtrl10  *ct_dd_audio_ctrl10_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_ctrl10_i2sout_test40( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_i2sout_test41( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_i2sout_test42( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_i2sout_test43( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_i2sout_test44( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmain_test1( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmain_test2( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmain_test3( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmain_test4( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmain_test5( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmain_test6( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmain_test7( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmaout_test1( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmaout_test2( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmaout_test3( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmaout_test4( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmaout_test5( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmaout_test6( CtDdAudioCtrl10 *self );
void 						ct_dd_audio_ctrl10_dmaout_test7( CtDdAudioCtrl10 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_CTRL10_H_ */
