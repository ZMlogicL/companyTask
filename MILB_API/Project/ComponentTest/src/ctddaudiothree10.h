/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree10类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_THREE10_H_
#define __CT_DD_AUDIO_THREE10_H_

#include <klib.h>

#define CT_TYPE_DD_AUDIO_THREE10				(ct_dd_audio_three10_get_type())
#define CT_DD_AUDIO_THREE10(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree10)) 
#define CT_IS_DD_AUDIO_THREE10(obj)			(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_AUDIO_THREE10))

typedef struct 			_CtDdAudioThree10 CtDdAudioThree10;
typedef struct 			_CtDdAudioThree10Private CtDdAudioThree10Private;

struct _CtDdAudioThree10
{
	KObject parent;
	kuint8 ch;
};

KConstType 				ct_dd_audio_three10_get_type(void);
CtDdAudioThree10  *ct_dd_audio_three10_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three10_099(CtDdAudioThree10 *self);
void 							ct_dd_audio_three10_100(CtDdAudioThree10 *self);
void 							ct_dd_audio_three10_101(CtDdAudioThree10 *self);
void 							ct_dd_audio_three10_102(CtDdAudioThree10 *self);
void 							ct_dd_audio_three10_103(CtDdAudioThree10 *self);

#endif /* __CT_DD_AUDIO_THREE10_H_ */
