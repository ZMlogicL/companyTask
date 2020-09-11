/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl5类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_CTRL5_H__
#define __CT_DD_AUDIO_CTRL5_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_CTRL5			   			(ct_dd_audio_ctrl5_get_type ())
#define 	CT_DD_AUDIO_CTRL5(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_CTRL5, CtDdAudioCtrl5))
#define 	CT_DD_AUDIO_CTRL5_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_CTRL5, CtDdAudioCtrl5Class))
#define 	CT_IS_DD_AUDIO_CTRL5(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_CTRL5))
#define 	CT_IS_DD_AUDIO_CTRL5_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_CTRL5))
#define 	CT_DD_AUDIO_CTRL5_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_CTRL5, CtDdAudioCtrl5Class))

typedef struct _CtDdAudioCtrl5         			CtDdAudioCtrl5;
typedef struct _CtDdAudioCtrl5Class    		CtDdAudioCtrl5Class;
typedef struct _CtDdAudioCtrl5Private  		CtDdAudioCtrl5Private;

struct _CtDdAudioCtrl5
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioCtrl5Class
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_ctrl5_get_type (void);
CtDdAudioCtrl5  	  *ct_dd_audio_ctrl5_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_ctrl5_i2scmmn_test7( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test8( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test9( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test10( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test11( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test12( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test13( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test14( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test15( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test16( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test17( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test18( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test19( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test20( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test21( CtDdAudioCtrl5 *self );
void 						ct_dd_audio_ctrl5_i2scmmn_test22( CtDdAudioCtrl5 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_CTRL5_H_ */
