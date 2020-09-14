/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree12类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE12_H_
#define __CT_DD_AUDIO_THREE12_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_THREE12					(ct_dd_audio_three12_get_type())
#define CT_DD_AUDIO_THREE12(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree12))
#define CT_DD_AUDIO_THREE12_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE12, CtDdAudioThree12Class))
#define CT_IS_DD_AUDIO_THREE12(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE12))
#define CT_IS_DD_AUDIO_THREE12_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE12))
#define CT_DD_AUDIO_THREE12_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE12, CtDdAudioThree12Class))

typedef struct 			_CtDdAudioThree12 CtDdAudioThree12;
typedef struct 			_CtDdAudioThree12Class CtDdAudioThree12Class;
typedef struct 			_CtDdAudioThree12Private CtDdAudioThree12Private;

struct _CtDdAudioThree12
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThree12Class
{
	GObjectClass parentclass;
};

GType			 				ct_dd_audio_three12_get_type(void);
CtDdAudioThree12  *ct_dd_audio_three12_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three12_109(CtDdAudioThree12 *self);
void 							ct_dd_audio_three12_110(CtDdAudioThree12 *self);
void 							ct_dd_audio_three12_111(CtDdAudioThree12 *self);
void 							ct_dd_audio_three12_112(CtDdAudioThree12 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE12_H_ */
