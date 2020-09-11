/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree9类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_THREE9_H_
#define __CT_DD_AUDIO_THREE9_H_

#include <klib.h>

#define CT_TYPE_DD_AUDIO_THREE9					(ct_dd_audio_three9_get_type())
#define CT_DD_AUDIO_THREE9(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree9)) 
#define CT_IS_DD_AUDIO_THREE9(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_AUDIO_THREE9))

typedef struct 			_CtDdAudioThree9 CtDdAudioThree9;
typedef struct 			_CtDdAudioThree9Private CtDdAudioThree9Private;

struct _CtDdAudioThree9
{
	KObject parent;
	kuint8 ch;
};

KConstType 				ct_dd_audio_three9_get_type(void);
CtDdAudioThree9    *ct_dd_audio_three9_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three9_094(CtDdAudioThree9 *self);
void 							ct_dd_audio_three9_095(CtDdAudioThree9 *self);
void 							ct_dd_audio_three9_096(CtDdAudioThree9 *self);
void 							ct_dd_audio_three9_097(CtDdAudioThree9 *self);
void 							ct_dd_audio_three9_098(CtDdAudioThree9 *self);

#endif /* __CT_DD_AUDIO_THREE9_H_ */
