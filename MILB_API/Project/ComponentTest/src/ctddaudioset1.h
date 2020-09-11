/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioSet1类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_SET1_H__
#define __CT_DD_AUDIO_SET1_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_SET1			   				(ct_dd_audio_set1_get_type ())
#define 	CT_DD_AUDIO_SET1(widget)		  		 		(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_SET1, CtDdAudioSet1))
#define 	CT_DD_AUDIO_SET1_CLASS(klass)	   			(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_SET1, CtDdAudioSet1Class))
#define 	CT_IS_DD_AUDIO_SET1(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_SET1))
#define 	CT_IS_DD_AUDIO_SET1_CLASS(klass)  		(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_SET1))
#define 	CT_DD_AUDIO_SET1_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_SET1, CtDdAudioSet1Class))

typedef struct _CtDdAudioSet1         			CtDdAudioSet1;
typedef struct _CtDdAudioSet1Class    		CtDdAudioSet1Class;
typedef struct _CtDdAudioSet1Private  		CtDdAudioSet1Private;

struct _CtDdAudioSet1
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioSet1Class
{
	GObjectClass parentclass;
};

GType           				ct_dd_audio_set1_get_type (void);
CtDdAudioSet1		  *ct_dd_audio_set1_new(gpointer *temp, guint8 ch);

void 							ct_dd_audio_set1_swaphw_auodlr_test1( CtDdAudioSet1 *self );
void 							ct_dd_audio_set1_swaphw_auodlr_test2( CtDdAudioSet1 *self );
void 							ct_dd_audio_set1_swaphw_auodlr_test3( CtDdAudioSet1 *self );
void 							ct_dd_audio_set1_swaphw_auodlr_test4( CtDdAudioSet1 *self );
void 							ct_dd_audio_set1_swaphw_auodlr_test5( CtDdAudioSet1 *self );
void 							ct_dd_audio_set1_swaphw_auodlr_test6( CtDdAudioSet1 *self );
void 							ct_dd_audio_set1_swaphw_auodlr_test7( CtDdAudioSet1 *self );
void 							ct_dd_audio_set1_swaphw_auodlr_test8( CtDdAudioSet1 *self );
void 							ct_dd_audio_set1_swapbyte_auodlr_test1( CtDdAudioSet1 *self );
void 							ct_dd_audio_set1_swapbyte_auodlr_test2( CtDdAudioSet1 *self );
void 							ct_dd_audio_set1_swapbyte_auodlr_test3( CtDdAudioSet1 *self );
void 							ct_dd_audio_set1_swapbyte_auodlr_test4( CtDdAudioSet1 *self );
void 							ct_dd_audio_set1_swapbyte_auodlr_test5( CtDdAudioSet1 *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_SET1_H_ */
