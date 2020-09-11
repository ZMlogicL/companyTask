/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree8类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE8_H_
#define __CT_DD_AUDIO_THREE8_H_

#include <klib.h>

#define CT_TYPE_DD_AUDIO_THREE8					(ct_dd_audio_three8_get_type())
#define CT_DD_AUDIO_THREE8(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree8)) 
#define CT_IS_DD_AUDIO_THREE8(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_AUDIO_THREE8))

typedef struct 			_CtDdAudioThree8 CtDdAudioThree8;
typedef struct 			_CtDdAudioThree8Private CtDdAudioThree8Private;

struct _CtDdAudioThree8
{
	KObject parent;
	kuint8 ch;
};

KConstType 				ct_dd_audio_three8_get_type(void);
CtDdAudioThree8	  *ct_dd_audio_three8_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three8_088(CtDdAudioThree8 *self);
void 							ct_dd_audio_three8_089(CtDdAudioThree8 *self);
void 							ct_dd_audio_three8_089_1(CtDdAudioThree8 *self);
void 							ct_dd_audio_three8_090(CtDdAudioThree8 *self);
void 							ct_dd_audio_three8_091(CtDdAudioThree8 *self);
void 							ct_dd_audio_three8_092(CtDdAudioThree8 *self);
void 							ct_dd_audio_three8_093(CtDdAudioThree8 *self);

#endif /* __CT_DD_AUDIO_THREE8_H_ */
