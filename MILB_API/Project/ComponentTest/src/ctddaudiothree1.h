/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree1类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE1_H_
#define __CT_DD_AUDIO_THREE1_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_THREE1					(ct_dd_audio_three1_get_type())
#define CT_DD_AUDIO_THREE1(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree1))
#define CT_DD_AUDIO_THREE1_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE1, CtDdAudioThree1Class))
#define CT_IS_DD_AUDIO_THREE1(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE1))
#define CT_IS_DD_AUDIO_THREE1_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE1))
#define CT_DD_AUDIO_THREE1_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE1, CtDdAudioThree1Class))

typedef struct 			_CtDdAudioThree1 CtDdAudioThree1;
typedef struct 			_CtDdAudioThree1Class CtDdAudioThree1Class;
typedef struct 			_CtDdAudioThree1Private CtDdAudioThree1Private;

struct _CtDdAudioThree1
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThree1Class
{
	GObjectClass parentclass;
};


GType			 				ct_dd_audio_three1_get_type(void);
CtDdAudioThree1 	  *ct_dd_audio_three1_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three1_042(CtDdAudioThree1 *self);
void 							ct_dd_audio_three1_043(CtDdAudioThree1 *self);
void 							ct_dd_audio_three1_044(CtDdAudioThree1 *self);
void 							ct_dd_audio_three1_045(CtDdAudioThree1 *self);
void 							ct_dd_audio_three1_046(CtDdAudioThree1 *self);
void 							ct_dd_audio_three1_047(CtDdAudioThree1 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE1_H_ */
