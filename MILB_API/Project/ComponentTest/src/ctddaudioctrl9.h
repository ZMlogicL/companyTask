/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl9类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_CTRL9_H__
#define __CT_DD_AUDIO_CTRL9_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_CTRL9			   				(ct_dd_audio_ctrl9_get_type ())
#define 	CT_DD_AUDIO_CTRL9(widget)		   				(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_CTRL9, CtDdAudioCtrl9))
#define 	CT_DD_AUDIO_CTRL9_CLASS(klass)	   			(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_CTRL9, CtDdAudioCtrl9Class))
#define 	CT_IS_DD_AUDIO_CTRL9(widget)	   				(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_CTRL9))
#define 	CT_IS_DD_AUDIO_CTRL9_CLASS(klass)  		(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_CTRL9))
#define 	CT_DD_AUDIO_CTRL9_GET_CLASS(obj)   		(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_CTRL9, CtDdAudioCtrl9Class))

typedef struct _CtDdAudioCtrl9         			CtDdAudioCtrl9;
typedef struct _CtDdAudioCtrl9Class    		CtDdAudioCtrl9Class;
typedef struct _CtDdAudioCtrl9Private  		CtDdAudioCtrl9Private;

struct _CtDdAudioCtrl9
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioCtrl9Class
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_ctrl9_get_type (void);
CtDdAudioCtrl9 	  *ct_dd_audio_ctrl9_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_ctrl9_i2sout_test16( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test17( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test18( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test19( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test20( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test21( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test22( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test23( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test24( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test25( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test26( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test27( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test28( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test29( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test30( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test31( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test32( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test33( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test34( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test35( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test36( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test37( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test38( CtDdAudioCtrl9 *self );
void 						ct_dd_audio_ctrl9_i2sout_test39( CtDdAudioCtrl9 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_CTRL9_H_ */
