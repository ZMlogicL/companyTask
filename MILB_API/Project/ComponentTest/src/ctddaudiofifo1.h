/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtDdAudioFifo1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_FIFO1_H_
#define __CT_DD_AUDIO_FIFO1_H_

#include <klib.h>

#define CT_TYPE_DD_AUDIO_FIFO1					(ct_dd_audio_fifo1_get_type())
#define CT_DD_AUDIO_FIFO1(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioFifo1))
#define CT_IS_DD_AUDIO_FIFO1(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_AUDIO_FIFO1)) 

typedef struct 			_CtDdAudioFifo1 CtDdAudioFifo1;
typedef struct 			_CtDdAudioFifo1Private CtDdAudioFifo1Private;

struct _CtDdAudioFifo1
{
	KObject parent;
	kuint8 ch;
};

KConstType 			ct_dd_audio_fifo1_get_type(void);
CtDdAudioFifo1    *ct_dd_audio_fifo1_new(kpointer *temp, kuint8 ch);

void 						ct_dd_audio_fifo1_monitor_rec2_slave(CtDdAudioFifo1 *self);
void 						ct_dd_audio_fifo1_monitor_rec3_n(CtDdAudioFifo1 *self);
void 						ct_dd_audio_fifo1_monitor_rec3(CtDdAudioFifo1 *self);
void 						ct_dd_audio_fifo1_monitor_rec3_slave(CtDdAudioFifo1 *self);
void 						ct_dd_audio_fifo1_dma_int_handler_fifo_monitor_play_cb( void );
void 						ct_dd_audio_fifo1_monitor_play0_n(CtDdAudioFifo1 *self);
void 						ct_dd_audio_fifo1_monitor_play0(CtDdAudioFifo1 *self);
void 						ct_dd_audio_fifo1_monitor_play0_slave(CtDdAudioFifo1 *self);

#endif /* __CT_DD_AUDIO_FIFO1_H_ */
