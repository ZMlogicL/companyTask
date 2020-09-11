/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioInt类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_INT_H__
#define __CT_DD_AUDIO_INT_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define 	CT_TYPE_DD_AUDIO_INT			   			(ct_dd_audio_int_get_type ())
#define 	CT_DD_AUDIO_INT(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
				CT_TYPE_DD_AUDIO_INT, CtDdAudioInt))
#define 	CT_DD_AUDIO_INT_CLASS(klass)	   		(G_TYPE_CHECK_CLASS_CAST ((klass), \
				CT_TYPE_DD_AUDIO_INT, CtDdAudioIntClass))
#define 	CT_IS_DD_AUDIO_INT(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), \
				CT_TYPE_DD_AUDIO_INT))
#define 	CT_IS_DD_AUDIO_INT_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), \
				CT_TYPE_DD_AUDIO_INT))
#define 	CT_DD_AUDIO_INT_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), \
				CT_TYPE_DD_AUDIO_INT, CtDdAudioIntClass))

typedef struct _CtDdAudioInt         			CtDdAudioInt;
typedef struct _CtDdAudioIntClass    		CtDdAudioIntClass;
typedef struct _CtDdAudioIntPrivate  	CtDdAudioIntPrivate;

struct _CtDdAudioInt
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioIntClass
{
	GObjectClass parentclass;
};

GType           		ct_dd_audio_int_get_type(void);
CtDdAudioInt   *ct_dd_audio_int_new(gpointer *temp, guint8 ch);

void 					ct_dd_audio_int_handler_test1(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test2(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test3(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test4(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test5(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test6(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test7(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test8(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test9(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test10(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test11(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test12(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test13(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test14(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test15(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test16(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test17(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test18(CtDdAudioInt *self);
void 					ct_dd_audio_int_handler_test19(CtDdAudioInt *self);

G_END_DECLS
#endif /* __CT_DD_AUDIO_INT_H_ */
