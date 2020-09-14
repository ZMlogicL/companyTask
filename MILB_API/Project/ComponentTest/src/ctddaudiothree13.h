/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree13类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE13_H_
#define __CT_DD_AUDIO_THREE13_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_THREE13					(ct_dd_audio_three13_get_type())
#define CT_DD_AUDIO_THREE13(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree13))
#define CT_DD_AUDIO_THREE13_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE13, CtDdAudioThree13Class))
#define CT_IS_DD_AUDIO_THREE13(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE13))
#define CT_IS_DD_AUDIO_THREE13_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE13))
#define CT_DD_AUDIO_THREE13_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE13, CtDdAudioThree13Class))

typedef struct 			_CtDdAudioThree13 CtDdAudioThree13;
typedef struct 			_CtDdAudioThree13Class CtDdAudioThree13Class;
typedef struct 			_CtDdAudioThree13Private CtDdAudioThree13Private;

struct _CtDdAudioThree13
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThree13Class
{
	GObjectClass parentclass;
};

GType			 				ct_dd_audio_three13_get_type(void);
CtDdAudioThree13  *ct_dd_audio_three13_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three13_113(CtDdAudioThree13 *self);
void 							ct_dd_audio_three13_114(CtDdAudioThree13 *self);
void 							ct_dd_audio_three13_115(CtDdAudioThree13 *self);
void 							ct_dd_audio_three13_116(CtDdAudioThree13 *self);
void 							ct_dd_audio_three13_117(CtDdAudioThree13 *self);
void 							ct_dd_audio_three13_118(CtDdAudioThree13 *self);
void 							ct_dd_audio_three13_119(CtDdAudioThree13 *self);
void 							ct_dd_audio_three13_120(CtDdAudioThree13 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE13_H_ */
