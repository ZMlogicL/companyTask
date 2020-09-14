/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree5类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE5_H_
#define __CT_DD_AUDIO_THREE5_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_THREE5					(ct_dd_audio_three5_get_type())
#define CT_DD_AUDIO_THREE5(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree5))
#define CT_DD_AUDIO_THREE5_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE5, CtDdAudioThree5Class))
#define CT_IS_DD_AUDIO_THREE5(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE5))
#define CT_IS_DD_AUDIO_THREE5_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE5))
#define CT_DD_AUDIO_THREE5_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE5, CtDdAudioThree5Class))

typedef struct 			_CtDdAudioThree5 CtDdAudioThree5;
typedef struct 			_CtDdAudioThree5Class CtDdAudioThree5Class;
typedef struct 			_CtDdAudioThree5Private CtDdAudioThree5Private;

struct _CtDdAudioThree5
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThree5Class
{
	GObjectClass parentclass;
};

GType			 				ct_dd_audio_three5_get_type(void);
CtDdAudioThree5	  *ct_dd_audio_three5_new(kpointer *temp, kuint8 ch);
void 							ct_dd_audio_three5_067(CtDdAudioThree5 *self);
void 							ct_dd_audio_three5_068(CtDdAudioThree5 *self);
void 							ct_dd_audio_three5_069(CtDdAudioThree5 *self);
void 							ct_dd_audio_three5_070(CtDdAudioThree5 *self);
void 							ct_dd_audio_three5_071(CtDdAudioThree5 *self);
void 							ct_dd_audio_three5_072(CtDdAudioThree5 *self);
void 							ct_dd_audio_three5_073(CtDdAudioThree5 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE5_H_ */
