/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree14类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE14_H_
#define __CT_DD_AUDIO_THREE14_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_THREE14					(ct_dd_audio_three14_get_type())
#define CT_DD_AUDIO_THREE14(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree14))
#define CT_DD_AUDIO_THREE14_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE14, CtDdAudioThree14Class))
#define CT_IS_DD_AUDIO_THREE14(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE14))
#define CT_IS_DD_AUDIO_THREE14_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE14))
#define CT_DD_AUDIO_THREE14_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE14, CtDdAudioThree14Class))

typedef struct 			_CtDdAudioThree14 CtDdAudioThree14;
typedef struct 			_CtDdAudioThree14Class CtDdAudioThree14Class;
typedef struct 			_CtDdAudioThree14Private CtDdAudioThree14Private;

struct _CtDdAudioThree14
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThree14Class
{
	GObjectClass parentclass;
};

GType			 				ct_dd_audio_three14_get_type(void);
CtDdAudioThree14  *ct_dd_audio_three14_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three14_121(CtDdAudioThree14 *self);
void 							ct_dd_audio_three14_122(CtDdAudioThree14 *self);
void 							ct_dd_audio_three14_123(CtDdAudioThree14 *self);
void 							ct_dd_audio_three14_124(CtDdAudioThree14 *self);
void 							ct_dd_audio_three14_125(CtDdAudioThree14 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE14_H_ */
