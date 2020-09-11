/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl1类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_CTRL1_H__
#define __CT_DD_AUDIO_CTRL1_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_CTRL1			   			(ct_dd_audio_ctrl1_get_type ())
#define 	CT_DD_AUDIO_CTRL1(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_CTRL1, CtDdAudioCtrl1))
#define 	CT_DD_AUDIO_CTRL1_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_CTRL1, CtDdAudioCtrl1Class))
#define 	CT_IS_DD_AUDIO_CTRL1(widget)	  			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_CTRL1))
#define 	CT_IS_DD_AUDIO_CTRL1_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_CTRL1))
#define 	CT_DD_AUDIO_CTRL1_GET_CLASS(obj)  	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_CTRL1, CtDdAudioCtrl1Class))

typedef struct _CtDdAudioCtrl1         			CtDdAudioCtrl1;
typedef struct _CtDdAudioCtrl1Class    		CtDdAudioCtrl1Class;
typedef struct _CtDdAudioCtrl1Private  		CtDdAudioCtrl1Private;

struct _CtDdAudioCtrl1
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioCtrl1Class
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_ctrl1_get_type (void);
CtDdAudioCtrl1    *ct_dd_audio_ctrl1_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_ctrl1_input_test11( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_input_test12( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_input_test13( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_input_test14( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_input_test15( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_input_test16( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_input_test17( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_input_test18( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_input_test19( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_input_test20( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_input_test21( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_input_test22( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_input_test23( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_output_test1( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_output_test2( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_output_test3( CtDdAudioCtrl1 *self );
void 						ct_dd_audio_ctrl1_output_test4( CtDdAudioCtrl1 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_CTRL1_H_ */
