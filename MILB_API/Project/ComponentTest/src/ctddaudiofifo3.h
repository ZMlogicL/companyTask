/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtDdAudioFifo3类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_FIFO3_H_
#define __CT_DD_AUDIO_FIFO3_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_FIFO3					(ct_dd_audio_fifo3_get_type())
#define CT_DD_AUDIO_FIFO3(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioFifo3))
#define CT_DD_AUDIO_FIFO3_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_FIFO3, CtDdAudioFifo3Class))
#define CT_IS_DD_AUDIO_FIFO3(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_FIFO3))
#define CT_IS_DD_AUDIO_FIFO3_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_FIFO3))
#define CT_DD_AUDIO_FIFO3_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_FIFO3, CtDdAudioFifo3Class))

typedef struct 			_CtDdAudioFifo3 CtDdAudioFifo3;
typedef struct 			_CtDdAudioFifo3Class CtDdAudioFifo3Class;
typedef struct 			_CtDdAudioFifo3Private CtDdAudioFifo3Private;

struct _CtDdAudioFifo3
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioFifo3Class
{
	GObjectClass parentclass;
};

GType			 			ct_dd_audio_fifo3_get_type(void);
CtDdAudioFifo3    *ct_dd_audio_fifo3_new(kpointer *temp, kuint8 ch) ;

void 						ct_dd_audio_fifo3_monitor_play0_D2(CtDdAudioFifo3 *self);
void 						ct_dd_audio_fifo3_monitor_play1_D2(CtDdAudioFifo3 *self);
void 						ct_dd_audio_fifo3_monitor_play2_D2(CtDdAudioFifo3 *self);
void 						ct_dd_audio_fifo3_monitor_play3_D2(CtDdAudioFifo3 *self);
void 						ct_dd_audio_fifo3_bit_shift( kuint16 *pcm, kuint32 dataBytes );
void 						ct_dd_audio_fifo3_sync_pdm(void);

G_END_DECLS

#endif /* __CT_DD_AUDIO_FIFO3_H_ */
