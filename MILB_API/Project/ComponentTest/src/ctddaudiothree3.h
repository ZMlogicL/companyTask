/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree3类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE3_H_
#define __CT_DD_AUDIO_THREE3_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_THREE3					(ct_dd_audio_three3_get_type())
#define CT_DD_AUDIO_THREE3(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree3))
#define CT_DD_AUDIO_THREE3_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE3, CtDdAudioThree3Class))
#define CT_IS_DD_AUDIO_THREE3(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE3))
#define CT_IS_DD_AUDIO_THREE3_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE3))
#define CT_DD_AUDIO_THREE3_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE3, CtDdAudioThree3Class))

typedef struct 			_CtDdAudioThree3 CtDdAudioThree3;
typedef struct 			_CtDdAudioThree3Class CtDdAudioThree3Class;
typedef struct 			_CtDdAudioThree3Private CtDdAudioThree3Private;

struct _CtDdAudioThree3
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThree3Class
{
	GObjectClass parentclass;
};

GType			 				ct_dd_audio_three3_get_type(void);
CtDdAudioThree3	  *ct_dd_audio_three3_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three3_053(CtDdAudioThree3 *self);
void 							ct_dd_audio_three3_054(CtDdAudioThree3 *self);
void 							ct_dd_audio_three3_055(CtDdAudioThree3 *self);
void 							ct_dd_audio_three3_056(CtDdAudioThree3 *self);
void 							ct_dd_audio_trhee3_057(CtDdAudioThree3 *self);
void 							ct_dd_audio_three3_058(CtDdAudioThree3 *self);
void 							ct_dd_audio_three3_059(CtDdAudioThree3 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE3_H_ */
