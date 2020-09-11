/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtDdAudioThree15类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE15_H_
#define __CT_DD_AUDIO_THREE15_H_

#include <klib.h>

#define CT_TYPE_DD_AUDIO_THREE15					(ct_dd_audio_three15_get_type())
#define CT_DD_AUDIO_THREE15(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree15))
#define CT_IS_DD_AUDIO_THREE15(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_AUDIO_THREE15))

typedef struct 			_CtDdAudioThree15 CtDdAudioThree15;
typedef struct 			_CtDdAudioThree15Private CtDdAudioThree15Private;

struct _CtDdAudioThree15
{
	KObject parent;
	kuint8 ch;
};

KConstType 				ct_dd_audio_three15_get_type(void);
CtDdAudioThree15  *ct_dd_audio_three15_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three15_126(CtDdAudioThree15 *self);
void 							ct_dd_audio_three15_127(CtDdAudioThree15 *self);
void 							ct_dd_audio_three15_128(CtDdAudioThree15 *self);
void 							ct_dd_audio_three15_129(CtDdAudioThree15 *self);

#endif /* __CT_DD_AUDIO_THREE15_H_ */
