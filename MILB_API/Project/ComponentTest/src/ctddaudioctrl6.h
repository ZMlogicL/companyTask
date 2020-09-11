/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl6类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_CTRL6_H__
#define __CT_DD_AUDIO_CTRL6_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_CTRL6			   			(ct_dd_audio_ctrl6_get_type ())
#define 	CT_DD_AUDIO_CTRL6(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_CTRL6, CtDdAudioCtrl6))
#define 	CT_DD_AUDIO_CTRL6_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass),\
				CT_TYPE_DD_AUDIO_CTRL6, CtDdAudioCtrl6Class))
#define 	CT_IS_DD_AUDIO_CTRL6(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_CTRL6))
#define 	CT_IS_DD_AUDIO_CTRL6_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_CTRL6))
#define 	CT_DD_AUDIO_CTRL6_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_CTRL6, CtDdAudioCtrl6Class))

typedef struct _CtDdAudioCtrl6         			CtDdAudioCtrl6;
typedef struct _CtDdAudioCtrl6Class    		CtDdAudioCtrl6Class;
typedef struct _CtDdAudioCtrl6Private  		CtDdAudioCtrl6Private;

struct _CtDdAudioCtrl6
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioCtrl6Class
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_ctrl6_get_type (void);
CtDdAudioCtrl6  	  *ct_dd_audio_ctrl6_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_ctrl6_i2scmmn_test23( CtDdAudioCtrl6 *self );
void 						ct_dd_audio_ctrl6_i2scmmn_test24( CtDdAudioCtrl6 *self );
void 						ct_dd_audio_ctrl6_i2scmmn_test25( CtDdAudioCtrl6 *self );
void 						ct_dd_audio_ctrl6_i2scmmn_test26( CtDdAudioCtrl6 *self );
void 						ct_dd_audio_ctrl6_i2scmmn_test27( CtDdAudioCtrl6 *self );
void 						ct_dd_audio_ctrl6_i2scmmn_test28( CtDdAudioCtrl6 *self );
void 						ct_dd_audio_ctrl6_i2scmmn_test29( CtDdAudioCtrl6 *self );
void 						ct_dd_audio_ctrl6_i2scmmn_test30( CtDdAudioCtrl6 *self );
void 						ct_dd_audio_ctrl6_i2scmmn_test31( CtDdAudioCtrl6 *self );
void 						ct_dd_audio_ctrl6_i2scmmn_test32( CtDdAudioCtrl6 *self );
void 						ct_dd_audio_ctrl6_i2scmmn_test33( CtDdAudioCtrl6 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_CTRL6_H_ */
