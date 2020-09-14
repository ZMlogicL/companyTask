/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree4类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE4_H_
#define __CT_DD_AUDIO_THREE4_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_THREE4					(ct_dd_audio_three4_get_type())
#define CT_DD_AUDIO_THREE4(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree4))
#define CT_DD_AUDIO_THREE4_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE4, CtDdAudioThree4Class))
#define CT_IS_DD_AUDIO_THREE4(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE4))
#define CT_IS_DD_AUDIO_THREE4_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE4))
#define CT_DD_AUDIO_THREE4_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE4, CtDdAudioThree4Class))

typedef struct 			_CtDdAudioThree4 CtDdAudioThree4;
typedef struct 			_CtDdAudioThree4Class CtDdAudioThree4Class;
typedef struct 			_CtDdAudioThree4Private CtDdAudioThree4Private;

struct _CtDdAudioThree4
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThree4Class
{
	GObjectClass parentclass;
};

GType			 				ct_dd_audio_three4_get_type(void);
CtDdAudioThree4	  *ct_dd_audio_three4_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three4_060(CtDdAudioThree4 *self);
void 							ct_dd_audio_three4_061(CtDdAudioThree4 *self);
void						 	ct_dd_audio_three4_062(CtDdAudioThree4 *self);
void 							ct_dd_audio_three4_063(CtDdAudioThree4 *self);
void 							ct_dd_audio_three4_064(CtDdAudioThree4 *self);
void 							ct_dd_audio_three4_065(CtDdAudioThree4 *self);
void 							ct_dd_audio_three4_066(CtDdAudioThree4 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE4_H_ */
