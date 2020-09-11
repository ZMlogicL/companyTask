/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree12类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE12_H_
#define __CT_DD_AUDIO_THREE12_H_

#include <klib.h>

#define CT_TYPE_DD_AUDIO_THREE12					(ct_dd_audio_three12_get_type())
#define CT_DD_AUDIO_THREE12(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree12))
#define CT_IS_DD_AUDIO_THREE12(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_AUDIO_THREE12))

typedef struct 			_CtDdAudioThree12 CtDdAudioThree12;
typedef struct 			_CtDdAudioThree12Private CtDdAudioThree12Private;

struct _CtDdAudioThree12
{
	KObject parent;
	kuint8 ch;
};

KConstType 				ct_dd_audio_three12_get_type(void);
CtDdAudioThree12  *ct_dd_audio_three12_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three12_109(CtDdAudioThree12 *self);
void 							ct_dd_audio_three12_110(CtDdAudioThree12 *self);
void 							ct_dd_audio_three12_111(CtDdAudioThree12 *self);
void 							ct_dd_audio_three12_112(CtDdAudioThree12 *self);

#endif /* __CT_DD_AUDIO_THREE12_H_ */
