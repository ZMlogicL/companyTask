/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl2类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_CTRL2_H__
#define __CT_DD_AUDIO_CTRL2_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_CTRL2			   			(ct_dd_audio_ctrl2_get_type ())
#define 	CT_DD_AUDIO_CTRL2(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_CTRL2, CtDdAudioCtrl2))
#define 	CT_DD_AUDIO_CTRL2_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_CTRL2, CtDdAudioCtrl2Class))
#define 	CT_IS_DD_AUDIO_CTRL2(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_CTRL2))
#define 	CT_IS_DD_AUDIO_CTRL2_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_CTRL2))
#define 	CT_DD_AUDIO_CTRL2_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_CTRL2, CtDdAudioCtrl2Class))

typedef struct _CtDdAudioCtrl2         			CtDdAudioCtrl2;
typedef struct _CtDdAudioCtrl2Class    		CtDdAudioCtrl2Class;
typedef struct _CtDdAudioCtrl2Private  		CtDdAudioCtrl2Private;

struct _CtDdAudioCtrl2
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioCtrl2Class
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_ctrl2_get_type (void);
CtDdAudioCtrl2    *ct_dd_audio_ctrl2_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_ctrl2_output_test5( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test6( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test7( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test8( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test9( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test10( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test11( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test12( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test13( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test14( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test15( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test16( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test17( CtDdAudioCtrl2 *self );
void 						ct_dd_audio_ctrl2_output_test18( CtDdAudioCtrl2 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_CTRL2_H_ */
