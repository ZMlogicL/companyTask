/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree7类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_THREE7_H_
#define __CT_DD_AUDIO_THREE7_H_

#include <klib.h>

#define CT_TYPE_DD_AUDIO_THREE7					(ct_dd_audio_three7_get_type())
#define CT_DD_AUDIO_THREE7(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree7)) 
#define CT_IS_DD_AUDIO_THREE7(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_AUDIO_THREE7))

typedef struct 			_CtDdAudioThree7 CtDdAudioThree7;
typedef struct 			_CtDdAudioThree7Private CtDdAudioThree7Private;

struct _CtDdAudioThree7
{
	KObject parent;
	kuint8 ch;
};

KConstType 				ct_dd_audio_three7_get_type(void);
CtDdAudioThree7    *ct_dd_audio_three7_new(kpointer *temp, kuint8 ch);

void 						 	ct_dd_audio_three7_081(CtDdAudioThree7 *self);
void 							ct_dd_audio_three7_082(CtDdAudioThree7 *self);
void 							ct_dd_audio_three7_083(CtDdAudioThree7 *self);
void 							ct_dd_audio_three7_084(CtDdAudioThree7 *self);
void 							ct_dd_audio_three7_085(CtDdAudioThree7 *self);
void 							ct_dd_audio_three7_086(CtDdAudioThree7 *self);
void 							ct_dd_audio_three7_087(CtDdAudioThree7 *self);

#endif /* __CT_DD_AUDIO_THREE7_H_ */
