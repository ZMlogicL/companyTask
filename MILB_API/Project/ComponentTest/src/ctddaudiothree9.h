/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree9类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_THREE9_H_
#define __CT_DD_AUDIO_THREE9_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_THREE9					(ct_dd_audio_three9_get_type())
#define CT_DD_AUDIO_THREE9(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree9))
#define CT_DD_AUDIO_THREE9_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE9, CtDdAudioThree9Class))
#define CT_IS_DD_AUDIO_THREE9(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE9))
#define CT_IS_DD_AUDIO_THREE9_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE9))
#define CT_DD_AUDIO_THREE9_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE9, CtDdAudioThree9Class))

typedef struct 			_CtDdAudioThree9 CtDdAudioThree9;
typedef struct 			_CtDdAudioThree9Class CtDdAudioThree9Class;
typedef struct 			_CtDdAudioThree9Private CtDdAudioThree9Private;

struct _CtDdAudioThree9
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThree9Class
{
	GObjectClass parentclass;
};

GType			 				ct_dd_audio_three9_get_type(void);
CtDdAudioThree9    *ct_dd_audio_three9_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three9_094(CtDdAudioThree9 *self);
void 							ct_dd_audio_three9_095(CtDdAudioThree9 *self);
void 							ct_dd_audio_three9_096(CtDdAudioThree9 *self);
void 							ct_dd_audio_three9_097(CtDdAudioThree9 *self);
void 							ct_dd_audio_three9_098(CtDdAudioThree9 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE9_H_ */
