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
#include <string.h>
#include <stdlib.h>
#include "audio_if.h"
#include "dd_audio.h"
#include "dd_hdmac0.h"
#include "dd_top.h"
#include "dd_cache.h"
#include "dd_pdm.h"
#include "dd_gic.h"
#include "peripheral.h"
#include "ctddaudiovariable.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdAudioVariable, ct_dd_audio_variable);
#define CT_DD_AUDIO_VARIABLE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtDdAudioVariablePrivate,CT_TYPE_DD_AUDIO_VARIABLE))

struct _CtDdAudioVariablePrivate
{
	kuint8 ddCtAudioDMAIntCnt;
	kuint8 ddCtAudioDMAIntCnt1;
	kuint8 ddCtAudioDMAIntCntIn;
	kuint8 ddCtAudioDMAIntCntOut;
	kuint32 gCtDdAudioFifoMonitor[2048];
};
/*
*DECLS
*/
static void ct_dd_audio_variable_constructor(CtDdAudioVariable *self);
static void ct_dd_audio_variable_destructor(CtDdAudioVariable *self);
/*
 * IMPL
 */
static void ct_dd_audio_variable_constructor(CtDdAudioVariable *self) 
{
}

static void ct_dd_audio_variable_destructor(CtDdAudioVariable *self) 
{
}
/*
 * PUBLIC
 */
//ddCtAudioDMAIntCnt:
void ct_dd_audio_set_dma_int_cnt(CtDdAudioVariable *self, kuint8 ct1 )
{
	CtDdAudioVariablePrivate *priv = CT_DD_AUDIO_VARIABLE_GET_PRIVATE(self);
	priv->ddCtAudioDMAIntCnt = ct1;
}

kuint8 ct_dd_audio_get_dma_int_cnt(CtDdAudioVariable *self)
{
	CtDdAudioVariablePrivate *priv = CT_DD_AUDIO_VARIABLE_GET_PRIVATE(self);
	return priv->ddCtAudioDMAIntCnt;
}

//ddCtAudioDMAIntCnt1:
void ct_dd_audio_set_dma_int_cnt1(CtDdAudioVariable *self, kuint8 ct2)
{
	CtDdAudioVariablePrivate *priv = CT_DD_AUDIO_VARIABLE_GET_PRIVATE(self);
	priv->ddCtAudioDMAIntCnt1 = ct2;
}

kuint8 ct_dd_audio_get_dma_int_cnt1(CtDdAudioVariable *self)
{
	CtDdAudioVariablePrivate *priv = CT_DD_AUDIO_VARIABLE_GET_PRIVATE(self);
	return priv->ddCtAudioDMAIntCnt1;
}

//ddCtAudioDMAIntCntIn:
void ct_dd_audio_set_dma_int_cnt_in(CtDdAudioVariable *self, kuint8 ct3)
{
	CtDdAudioVariablePrivate *priv = CT_DD_AUDIO_VARIABLE_GET_PRIVATE(self);
	priv->ddCtAudioDMAIntCntIn = ct3;
}

kuint8 ct_dd_audio_get_dma_int_cnt_in(CtDdAudioVariable *self)
{
	CtDdAudioVariablePrivate *priv = CT_DD_AUDIO_VARIABLE_GET_PRIVATE(self);
	return priv->ddCtAudioDMAIntCntIn;
}

//ddCtAudioDMAIntCntOut
void ct_dd_audio_set_dma_int_cnt_out(CtDdAudioVariable *self, kuint8 ct4)
{
	CtDdAudioVariablePrivate *priv = CT_DD_AUDIO_VARIABLE_GET_PRIVATE(self);
	priv->ddCtAudioDMAIntCntOut = ct4;
}

kuint8 ct_dd_audio_get_dma_int_cnt_out(CtDdAudioVariable *self)
{
	CtDdAudioVariablePrivate *priv = CT_DD_AUDIO_VARIABLE_GET_PRIVATE(self);
	return priv->ddCtAudioDMAIntCntOut;
}

//gCtDdAudioFifoMonitor[2048]:
void ct_dd_audio_set_gct_dd_audio_fifomonitor(CtDdAudioVariable *self, kint i ,kuint32 ct5)
{
	CtDdAudioVariablePrivate *priv = CT_DD_AUDIO_VARIABLE_GET_PRIVATE(self);
	priv->gCtDdAudioFifoMonitor[i] = ct5;
}

kuint32 ct_dd_audio_get_gct_dd_audio_fifomonitor(CtDdAudioVariable *self, kint j)
{
	CtDdAudioVariablePrivate *priv = CT_DD_AUDIO_VARIABLE_GET_PRIVATE(self);
	return priv->gCtDdAudioFifoMonitor[j];
}

CtDdAudioVariable *ct_dd_audio_variable_new(void)
{
	static CtDdAudioVariable *self = NULL;
	if(!self)
	{
		self = k_object_new(CT_TYPE_DD_AUDIO_VARIABLE);
	}
    return self;
}
