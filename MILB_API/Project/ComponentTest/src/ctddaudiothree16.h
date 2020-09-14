/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtDdAudioThree16类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE16_H_
#define __CT_DD_AUDIO_THREE16_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_THREE16					(ct_dd_audio_three16_get_type())
#define CT_DD_AUDIO_THREE16(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree16))
#define CT_DD_AUDIO_THREE16_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE16, CtDdAudioThree16Class))
#define CT_IS_DD_AUDIO_THREE16(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE16))
#define CT_IS_DD_AUDIO_THREE16_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE16))
#define CT_DD_AUDIO_THREE16_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE16, CtDdAudioThree16Class))

typedef struct 			_CtDdAudioThree16 CtDdAudioThree16;
typedef struct 			_CtDdAudioThree16Class CtDdAudioThree16Class;
typedef struct 			_CtDdAudioThree16Private CtDdAudioThree16Private;

struct _CtDdAudioThree16
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThree16Class
{
	GObjectClass parentclass;
};

GType			 				ct_dd_audio_three16_get_type(void);
CtDdAudioThree16  *ct_dd_audio_three16_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_3_130(CtDdAudioThree16 *self);
void 							ct_dd_audio_3_131(CtDdAudioThree16 *self);
void 							ct_dd_audio_3_hdmi(CtDdAudioThree16 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE16_H_ */
