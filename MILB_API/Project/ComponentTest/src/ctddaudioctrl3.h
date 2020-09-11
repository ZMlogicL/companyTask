/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl3类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_CTRL3_H__
#define __CT_DD_AUDIO_CTRL3_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_CTRL3			   			(ct_dd_audio_ctrl3_get_type ())
#define 	CT_DD_AUDIO_CTRL3(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_CTRL3, CtDdAudioCtrl3))
#define 	CT_DD_AUDIO_CTRL3_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_CTRL3, CtDdAudioCtrl3Class))
#define 	CT_IS_DD_AUDIO_CTRL3(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_CTRL3))
#define 	CT_IS_DD_AUDIO_CTRL3_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_CTRL3))
#define 	CT_DD_AUDIO_CTRL3_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_CTRL3, CtDdAudioCtrl3Class))

typedef struct _CtDdAudioCtrl3         			CtDdAudioCtrl3;
typedef struct _CtDdAudioCtrl3Class    		CtDdAudioCtrl3Class;
typedef struct _CtDdAudioCtrl3Private  		CtDdAudioCtrl3Private;

struct _CtDdAudioCtrl3
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioCtrl3Class
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_ctrl3_get_type (void);
CtDdAudioCtrl3 	  *ct_dd_audio_ctrl3_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_ctrl3_output_test19( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test20( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test21( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test22( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test23( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test24( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test25( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test26( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test27( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test28( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test29( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test30( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test31( CtDdAudioCtrl3 *self );
void 						ct_dd_audio_ctrl3_output_test32( CtDdAudioCtrl3 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_CTRL3_H_ */
