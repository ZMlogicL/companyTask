/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree11类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE11_H_
#define __CT_DD_AUDIO_THREE11_H_

#include <glib-object.h>

#define CT_TYPE_DD_AUDIO_THREE11					(ct_dd_audio_three11_get_type())
#define CT_DD_AUDIO_THREE11(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree11))
#define CT_DD_AUDIO_THREE11_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE11, CtDdAudioThree11Class))
#define CT_IS_DD_AUDIO_THREE11(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE11))
#define CT_IS_DD_AUDIO_THREE11_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE11))
#define CT_DD_AUDIO_THREE11_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE11, CtDdAudioThree11Class))

typedef struct 			_CtDdAudioThree11 CtDdAudioThree11;
typedef struct 			_CtDdAudioThree11Class CtDdAudioThree11Class;
typedef struct 			_CtDdAudioThree11Private CtDdAudioThree11Private;

struct _CtDdAudioThree11
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThree11Class
{
	GObjectClass parentclass;
};


GType			 				ct_dd_audio_three11_get_type(void);
CtDdAudioThree11  *ct_dd_audio_three11_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three11_104(CtDdAudioThree11 *self);
void 							ct_dd_audio_three11_105(CtDdAudioThree11 *self);
void 							ct_dd_audio_three11_106(CtDdAudioThree11 *self);
void 							ct_dd_audio_three11_107(CtDdAudioThree11 *self);
void 							ct_dd_audio_three11_108(CtDdAudioThree11 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE11_H_ */
