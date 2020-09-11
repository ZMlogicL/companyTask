/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE1_H_
#define __CT_DD_AUDIO_THREE1_H_

#include <klib.h>

#define CT_TYPE_DD_AUDIO_THREE1					(ct_dd_audio_three1_get_type())
#define CT_DD_AUDIO_THREE1(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree1)) 
#define CT_IS_DD_AUDIO_THREE1(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_AUDIO_THREE1))

typedef struct 			_CtDdAudioThree1 CtDdAudioThree1;
typedef struct 			_CtDdAudioThree1Private CtDdAudioThree1Private;

struct _CtDdAudioThree1
{
	KObject parent;
	kuint8 ch;
};

KConstType 				ct_dd_audio_three1_get_type(void);
CtDdAudioThree1 	  *ct_dd_audio_three1_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three1_042(CtDdAudioThree1 *self);
void 							ct_dd_audio_three1_043(CtDdAudioThree1 *self);
void 							ct_dd_audio_three1_044(CtDdAudioThree1 *self);
void 							ct_dd_audio_three1_045(CtDdAudioThree1 *self);
void 							ct_dd_audio_three1_046(CtDdAudioThree1 *self);
void 							ct_dd_audio_three1_047(CtDdAudioThree1 *self);

#endif /* __CT_DD_AUDIO_THREE1_H_ */
