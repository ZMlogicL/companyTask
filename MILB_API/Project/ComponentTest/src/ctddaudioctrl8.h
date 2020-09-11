/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl8类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_CTRL8_H__
#define __CT_DD_AUDIO_CTRL8_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_CTRL8			  	 		(ct_dd_audio_ctrl8_get_type ())
#define 	CT_DD_AUDIO_CTRL8(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_CTRL8, CtDdAudioCtrl8))
#define 	CT_DD_AUDIO_CTRL8_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_CTRL8, CtDdAudioCtrl8Class))
#define 	CT_IS_DD_AUDIO_CTRL8(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_CTRL8))
#define 	CT_IS_DD_AUDIO_CTRL8_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_CTRL8))
#define 	CT_DD_AUDIO_CTRL8_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_CTRL8, CtDdAudioCtrl8Class))

typedef struct _CtDdAudioCtrl8         			CtDdAudioCtrl8;
typedef struct _CtDdAudioCtrl8Class    		CtDdAudioCtrl8Class;
typedef struct _CtDdAudioCtrl8Private  		CtDdAudioCtrl8Private;

struct _CtDdAudioCtrl8
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioCtrl8Class
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_ctrl8_get_type (void);
CtDdAudioCtrl8    *ct_dd_audio_ctrl8_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_ctrl8_i2sin_test1( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test2( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test3( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test4( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test5( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test6( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test7( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test8( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test9( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test10( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test11( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test12( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test13( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sin_test14( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test1( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test2( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test3( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test4( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test5( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test6( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test7( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test8( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test9( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test10( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test11( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test12( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test13( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test14( CtDdAudioCtrl8 *self );
void 						ct_dd_audio_ctrl8_i2sout_test15( CtDdAudioCtrl8 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_CTRL8_H_ */
