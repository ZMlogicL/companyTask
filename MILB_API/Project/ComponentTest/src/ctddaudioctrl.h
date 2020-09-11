/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author            :luhongyin
*@brief               :CtDdAudioCtrl类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_CTRL_H__
#define __CT_DD_AUDIO_CTRL_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_CTRL			   				(ct_dd_audio_ctrl_get_type ())
#define 	CT_DD_AUDIO_CTRL(widget)		   				(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_CTRL, CtDdAudioCtrl))
#define 	CT_DD_AUDIO_CTRL_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_CTRL, CtDdAudioCtrlClass))
#define 	CT_IS_DD_AUDIO_CTRL(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_CTRL))
#define 	CT_IS_DD_AUDIO_CTRL_CLASS(klass)  		(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_CTRL))
#define 	CT_DD_AUDIO_CTRL_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_CTRL, CtDdAudioCtrlClass))

typedef struct _CtDdAudioCtrl         		CtDdAudioCtrl;
typedef struct _CtDdAudioCtrlClass    	CtDdAudioCtrlClass;
typedef struct _CtDdAudioCtrlPrivate  	CtDdAudioCtrlPrivate;

struct _CtDdAudioCtrl
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioCtrlClass
{
	GObjectClass parentclass;
};

GType           		ct_dd_audio_ctrl_get_type (void);
CtDdAudioCtrl  *ct_dd_audio_ctrl_new(gpointer *temp, guint8 ch);

void 					ct_dd_audio_ctrl_common_test1( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_common_test2( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_common_test3( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_common_test4( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_common_test5( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_common_test6( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_common_test7( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_common_test8( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_common_test9( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_common_test10( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_common_test11( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_input_test1( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_input_test2( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_input_test3( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_input_test4( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_input_test5( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_input_test6( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_input_test7( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_input_test8( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_input_test9( CtDdAudioCtrl *self );
void 					ct_dd_audio_ctrl_input_test10( CtDdAudioCtrl *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_CTRL_H_ */
