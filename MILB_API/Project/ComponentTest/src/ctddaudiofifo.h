/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtDdAudioFifo类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_FIFO_H_
#define __CT_DD_AUDIO_FIFO_H_

#include <klib.h>

#define CT_TYPE_DD_AUDIO_FIFO					(ct_dd_audio_fifo_get_type())
#define CT_DD_AUDIO_FIFO(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioFifo)) 
#define CT_IS_DD_AUDIO_FIFO(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_AUDIO_FIFO))

typedef struct 			_CtDdAudioFifo CtDdAudioFifo;
typedef struct 			_CtDdAudioFifoPrivate CtDdAudioFifoPrivate;

struct _CtDdAudioFifo
{
	KObject parent;
	kuint8 ch;
};

KConstType 			ct_dd_audio_fifo_get_type(void);
CtDdAudioFifo      *ct_dd_audio_fifo_new(kpointer *temp, kuint8 ch);

void 						ct_dd_audio_fifo_dma_int_handler_fifo_monitor_rec_cb( void );
void 						ct_dd_audio_fifo_monitor_rec0_n(CtDdAudioFifo *self);
void 						ct_dd_audio_fifo_monitor_rec0(CtDdAudioFifo *self);
void 						ct_dd_audio_fifo_monitor_rec0_slave(CtDdAudioFifo *self);
void 						ct_dd_audio_fifo_monitor_rec1(CtDdAudioFifo *self);
void 						ct_dd_audio_fifo_monitor_rec1_slave(CtDdAudioFifo *self);
void 						ct_dd_audio_fifo_monitor_rec2_n(CtDdAudioFifo *self);
void 						ct_dd_audio_fifo_monitor_rec2(CtDdAudioFifo *self);

#endif /* __CT_DD_AUDIO_FIFO_H_ */
