/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_THREE_H_
#define __CT_DD_AUDIO_THREE_H_

#include <klib.h>

#define CT_TYPE_DD_AUDIO_THREE					(ct_dd_audio_three_get_type())
#define CT_DD_AUDIO_THREE(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree))
#define CT_IS_DD_AUDIO_THREE(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_AUDIO_THREE))

typedef struct 			_CtDdAudioThree CtDdAudioThree;
typedef struct 			_CtDdAudioThreePrivate CtDdAudioThreePrivate;

struct _CtDdAudioThree
{
	KObject parent;
	kuint8 ch;
};

KConstType 			ct_dd_audio_three_get_type(void);
CtDdAudioThree  *ct_dd_audio_three_new(kpointer *temp, kuint8 ch);

void 						ct_dd_audio_three_reg_rw(CtDdAudioThree *self);
void 						ct_dd_audio_three_input_open_close(CtDdAudioThree *self);
void 						ct_dd_audio_three_output_open_close(CtDdAudioThree *self);
void 						ct_dd_audio_three_init(CtDdAudioThree *self);
void 						ct_dd_audio_three_update_input_setting(CtDdAudioThree *self);
void 						ct_dd_audio_three_update_output_setting(CtDdAudioThree *self);
void 						ct_dd_audio_three_reset_input_status(CtDdAudioThree *self);
void 						ct_dd_audio_three_reset_output_status(CtDdAudioThree *self);
void 						ct_dd_audio_three_start_stop_input(CtDdAudioThree *self);
void 						ct_dd_audio_three_start_stop_output(CtDdAudioThree *self);
void 						ct_dd_audio_three_041(CtDdAudioThree *self);

#endif /* __CT_DD_AUDIO_THREE_H_ */
