/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtDdAudioVariable类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_VARIABLE_H_
#define __CT_DD_AUDIO_VARIABLE_H_

#include <klib.h>

#define CT_TYPE_DD_AUDIO_VARIABLE					(ct_dd_audio_variable_get_type())
#define CT_DD_AUDIO_VARIABLE(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioVariable)) 
#define CT_IS_DD_AUDIO_VARIABLE(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_AUDIO_VARIABLE))

typedef struct 			_CtDdAudioVariable CtDdAudioVariable;
typedef struct 			_CtDdAudioVariablePrivate CtDdAudioVariablePrivate;

struct _CtDdAudioVariable
{
	KObject parent;
	CtDdAudioVariablePrivate *priv;
};

KConstType 				ct_dd_audio_variable_get_type(void);
CtDdAudioVariable  *ct_dd_audio_variable_new(void);

void 							ct_dd_audio_set_dma_int_cnt(CtDdAudioVariable *self, kuint8 ct1 );
kuint8 							ct_dd_audio_get_dma_int_cnt(CtDdAudioVariable *self);
void 							ct_dd_audio_set_dma_int_cnt1(CtDdAudioVariable *self, kuint8 ct2);
kuint8 							ct_dd_audio_get_dma_int_cnt1(CtDdAudioVariable *self);
void 							ct_dd_audio_set_dma_int_cnt_in(CtDdAudioVariable *self, kuint8 ct3);
kuint8 							ct_dd_audio_get_dma_int_cnt_in(CtDdAudioVariable *self);
void 							ct_dd_audio_set_dma_int_cnt_out(CtDdAudioVariable *self, kuint8 ct4);
kuint8 							ct_dd_audio_get_dma_int_cnt_out(CtDdAudioVariable *self);
void 							ct_dd_audio_set_gct_dd_audio_fifomonitor(CtDdAudioVariable *self, kint i ,kuint32 ct5);
kuint32 						ct_dd_audio_get_gct_dd_audio_fifomonitor(CtDdAudioVariable *self, kint j);

#endif /* __CT_DD_AUDIO_VARIABLE_H_ */
