/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtDdAudioFifo2类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_FIFO2_H_
#define __CT_DD_AUDIO_FIFO2_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_FIFO2					(ct_dd_audio_fifo2_get_type())
#define CT_DD_AUDIO_FIFO2(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioFifo2))
#define CT_DD_AUDIO_FIFO2_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_FIFO2, CtDdAudioFifo2Class))
#define CT_IS_DD_AUDIO_FIFO2(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_FIFO2))
#define CT_IS_DD_AUDIO_FIFO2_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_FIFO2))
#define CT_DD_AUDIO_FIFO2_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_FIFO2, CtDdAudioFifo2Class))

typedef struct 			_CtDdAudioFifo2 CtDdAudioFifo2;
typedef struct 			_CtDdAudioFifo2Class CtDdAudioFifo2Class;
typedef struct 			_CtDdAudioFifo2Private CtDdAudioFifo2Private;

struct _CtDdAudioFifo2
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioFifo2Class
{
	GObjectClass parentclass;
};


GType 						ct_dd_audio_fifo2_get_type(void);
CtDdAudioFifo2    *ct_dd_audio_fifo2_new(kpointer *temp, kuint8 ch);

void 						ct_dd_audio_fifo2_monitor_play1(CtDdAudioFifo2 *self);
void 						ct_dd_audio_fifo2_monitor_play1_slave(CtDdAudioFifo2 *self);
void 						ct_dd_audio_fifo2_monitor_play2_n(CtDdAudioFifo2 *self);
void 						ct_dd_audio_fifo2_monitor_play2(CtDdAudioFifo2 *self);
void 						ct_dd_audio_fifo2_monitor_play2_slave(CtDdAudioFifo2 *self);
void 						ct_dd_audio_fifo2_monitor_play3_n(CtDdAudioFifo2 *self);
void 						ct_dd_audio_fifo2_monitor_play3(CtDdAudioFifo2 *self);
void 						ct_dd_audio_fifo2_monitor_play3_slave(CtDdAudioFifo2 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_FIFO2_H_ */
