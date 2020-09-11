/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE2_H_
#define __CT_DD_AUDIO_THREE2_H_

#include <klib.h>

#define CT_TYPE_DD_AUDIO_THREE2					(ct_dd_audio_three2_get_type())
#define CT_DD_AUDIO_THREE2(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree2)) 
#define CT_IS_DD_AUDIO_THREE2(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_AUDIO_THREE2))

typedef struct 			_CtDdAudioThree2 CtDdAudioThree2;
typedef struct 			_CtDdAudioThree2Private CtDdAudioThree2Private;

struct _CtDdAudioThree2
{
	KObject parent;
	kuint8 ch;
};

KConstType 				ct_dd_audio_three2_get_type(void);
CtDdAudioThree2	  *ct_dd_audio_three2_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three2_048(CtDdAudioThree2 *self);
void 							ct_dd_audio_three2_049(CtDdAudioThree2 *self);
void 							ct_dd_audio_three2_050(CtDdAudioThree2 *self);
void 							ct_dd_audio_three2_051(CtDdAudioThree2 *self);
void 							ct_dd_audio_three2_052(CtDdAudioThree2 *self);

#endif /* __CT_DD_AUDIO_THREE2_H_ */
