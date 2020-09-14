/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioSet类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/
#include "audio_if.h"
#include "dd_audio.h"
#include "dd_hdmac0.h"
#include "dd_top.h"
#include "dd_cache.h"
#include "dd_pdm.h"
#include "dd_gic.h"
#include "peripheral.h"
#include <string.h>
#include <stdlib.h>
#include "ctddaudio.h"
#include "ctddaudioint.h"
#include "ctddaudioctrl.h"
#include "ctddaudioctrl1.h"
#include "ctddaudioctrl2.h"
#include "ctddaudioctrl3.h"
#include "ctddaudioctrl4.h"
#include "ctddaudioctrl5.h"
#include "ctddaudioctrl6.h"
#include "ctddaudioctrl7.h"
#include "ctddaudioctrl8.h"
#include "ctddaudioctrl9.h"
#include "ctddaudioctrl10.h"
#include "ctddaudioget.h"
#include "ctddaudiostart.h"
#include "ctddaudiostop.h"
#include "ctddaudioset.h"

G_DEFINE_TYPE(CtDdAudioSet, ct_dd_audio_set, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_SET_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_SET, CtDdAudioSetPrivate))

struct _CtDdAudioSetPrivate
{
};

/*
 * DECLS
 */
static void ct_dd_audio_set_class_init(CtDdAudioSetClass *klass);
static void ct_dd_audio_set_init(CtDdAudioSet *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);

/*
 * IMPL
 */
static void ct_dd_audio_set_class_init(CtDdAudioSetClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioSetPrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_set_init(CtDdAudioSet *self)
{
	// CtDdAudioSet *self = CT_DD_AUDIO_SET(object);
    // CtDdAudioSetPrivate *priv = CT_DD_AUDIO_SET_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_set_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_set_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_set_enable_fifo_full_dmain_test1( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	ioAudio.AUDIOIF[ch].AUST.bit.EDMIE = 0;

	result = dd_audio_set_enable_fifo_full_dmain(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUCR.DMIE=0x%x\n", ioAudio.AUDIOIF[ch].AUCR.bit.DMIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_enable_fifo_full_dmain_test2( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	result = dd_audio_set_enable_fifo_full_dmain(dd_audio_get(), ch, DdAudio_DISABLE);

	DriverCommon_DDIM_PRINT(("AUCR.DMIE=0x%x\n", ioAudio.AUDIOIF[ch].AUCR.bit.DMIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_enable_fifo_full_dmain_test3( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	ioAudio.AUDIOIF[ch].AUST.bit.EDMIE = 1;

	result = dd_audio_set_enable_fifo_full_dmain(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUCR.DMIE=0x%x\n", ioAudio.AUDIOIF[ch].AUCR.bit.DMIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_enable_fifo_full_dmain_test4( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_enable_fifo_full_dmain(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_enable_fifo_full_dmain_test5( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_enable_fifo_full_dmain(dd_audio_get(), ch, 2);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_enable_fifo_empty_dma_out_test1( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	ioAudio.AUDIOIF[ch].AUST.bit.EDMOE = 0;

	result = dd_audio_set_enable_fifo_empty_dma_out(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUCR.DMOE=0x%x\n", ioAudio.AUDIOIF[ch].AUCR.bit.DMOE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_enable_fifo_empty_dma_out_test2( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	result = dd_audio_set_enable_fifo_empty_dma_out(dd_audio_get(), ch, DdAudio_DISABLE);

	DriverCommon_DDIM_PRINT(("AUCR.DMOE=0x%x\n", ioAudio.AUDIOIF[ch].AUCR.bit.DMOE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_enable_fifo_empty_dma_out_test3( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	ioAudio.AUDIOIF[ch].AUST.bit.EDMOE = 1;

	result = dd_audio_set_enable_fifo_empty_dma_out(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUCR.DMOE=0x%x\n", ioAudio.AUDIOIF[ch].AUCR.bit.DMOE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_enable_fifo_empty_dma_out_test4( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_enable_fifo_empty_dma_out(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_enable_fifo_empty_dma_out_test5( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_enable_fifo_empty_dma_out(dd_audio_get(), ch, 2);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_input_dmarequest_enable_test1( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	ioAudio.AUDIOIF[ch].AUCR.bit.DMIE = 0;

	result = dd_audio_set_input_dma_request_enable(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUST.EDMIE=0x%x\n", ioAudio.AUDIOIF[ch].AUST.bit.EDMIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_input_dmarequest_enable_test2( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	result = dd_audio_set_input_dma_request_enable(dd_audio_get(), ch, DdAudio_DISABLE);

	DriverCommon_DDIM_PRINT(("AUST.EDMIE=0x%x\n", ioAudio.AUDIOIF[ch].AUST.bit.EDMIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_input_dmarequest_enable_test3( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	ioAudio.AUDIOIF[ch].AUCR.bit.DMIE = 1;

	result = dd_audio_set_input_dma_request_enable(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUST.EDMIE=0x%x\n", ioAudio.AUDIOIF[ch].AUST.bit.EDMIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_input_dmarequest_enable_test4( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_input_dma_request_enable(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_input_dmarequest_enable_test5( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_input_dma_request_enable(dd_audio_get(), ch, 2);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_output_dmarequest_enable_test1( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	ioAudio.AUDIOIF[ch].AUCR.bit.DMOE = 0;

	result = dd_audio_set_output_dma_request_enable(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUST.EDMOE=0x%x\n", ioAudio.AUDIOIF[ch].AUST.bit.EDMOE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_output_dmarequest_enable_test2( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	result = dd_audio_set_output_dma_request_enable(dd_audio_get(), ch, DdAudio_DISABLE);

	DriverCommon_DDIM_PRINT(("AUST.EDMOE=0x%x\n", ioAudio.AUDIOIF[ch].AUST.bit.EDMOE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_output_dmarequest_enable_test3( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	ioAudio.AUDIOIF[ch].AUCR.bit.DMOE = 1;

	result = dd_audio_set_output_dma_request_enable(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUST.EDMOE=0x%x\n", ioAudio.AUDIOIF[ch].AUST.bit.EDMOE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_output_dmarequest_enable_test4( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_output_dma_request_enable(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_output_dmarequest_enable_test5( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_output_dma_request_enable(dd_audio_get(), ch, 2);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_swaphw_auidlr_test1( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_set_swap_hw_auidlr(dd_audio_get(), ch, DdAudio_DISABLE);

	result = dd_audio_set_swap_hw_auidlr(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUMD.IHW_SWP=0x%x\n", ioAudio.AUDIOIF[ch].AUMD.bit.IHW_SWP));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_swaphw_auidlr_test2( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_set_swap_hw_auidlr(dd_audio_get(), ch, DdAudio_ENABLE);

	result = dd_audio_set_swap_hw_auidlr(dd_audio_get(), ch, DdAudio_DISABLE);

	DriverCommon_DDIM_PRINT(("AUMD.IHW_SWP=0x%x\n", ioAudio.AUDIOIF[ch].AUMD.bit.IHW_SWP));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_swaphw_auidlr_test3( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	AudioCtrlIn ctrlInf;
	AudioCtrlCommon ctrlCommon;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_SLAVE;
		i2sCommon.clkDivEnable = DdAudio_DISABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_SLAVE;
		i2sCommon.clkDivEnable = DdAudio_DISABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);

	}

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bitIn = DdAudioI2s_BIT_16BIT;
	i2sIn.modeIn = E_DD_AUDIO_MODE_R_JUST;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	dd_audio_set_swap_hw_auidlr(dd_audio_get(), ch, DdAudio_ENABLE);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
		ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
		ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
		ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

#ifdef PC_DEBUG
	if (ch != 1){
		ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
	}
	else {
		ioAudio.AUDIOIF[0].AUCR.bit.AUIEF = 1;
		ioAudio.AUDIOIF[1].AUCR.bit.AUIEF = 1;
	}
#endif

	result = dd_audio_set_swap_hw_auidlr(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUMD.IHW_SWP=0x%x\n", ioAudio.AUDIOIF[ch].AUMD.bit.IHW_SWP));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_swaphw_auidlr_test4( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	AudioCtrlIn ctrlInf;
	AudioCtrlCommon ctrlCommon;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);

	}

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bitIn = DdAudioI2s_BIT_16BIT;
	i2sIn.modeIn = E_DD_AUDIO_MODE_R_JUST;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	dd_audio_set_swap_hw_auidlr(dd_audio_get(), ch, DdAudio_DISABLE);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
		ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
		ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
		ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

#ifdef PC_DEBUG
	if (ch != 1){
		ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
	}
	else {
		ioAudio.AUDIOIF[0].AUCR.bit.AUIEF = 1;
		ioAudio.AUDIOIF[1].AUCR.bit.AUIEF = 1;
	}
#else
	ddim_user_custom_dly_tsk(1);
#endif

	result = dd_audio_set_swap_hw_auidlr(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUMD.IHW_SWP=0x%x\n", ioAudio.AUDIOIF[ch].AUMD.bit.IHW_SWP));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_swaphw_auidlr_test5( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_swap_hw_auidlr(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_swaphw_auidlr_test6( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_swap_hw_auidlr(dd_audio_get(), ch, 2);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_swapbyte_auidlr_test1( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF = 0;

	dd_audio_set_swap_byte_auidlr(dd_audio_get(), ch, DdAudio_DISABLE);

	result = dd_audio_set_swap_byte_auidlr(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUMD.IBYTE_SWP=0x%x\n", ioAudio.AUDIOIF[ch].AUMD.bit.IBYTE_SWP));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_swapbyte_auidlr_test2( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF = 0;

	dd_audio_set_swap_byte_auidlr(dd_audio_get(), ch, DdAudio_ENABLE);

	result = dd_audio_set_swap_byte_auidlr(dd_audio_get(), ch, DdAudio_DISABLE);

	DriverCommon_DDIM_PRINT(("AUMD.IBYTE_SWP=0x%x\n", ioAudio.AUDIOIF[ch].AUMD.bit.IBYTE_SWP));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_swapbyte_auidlr_test3( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	AudioCtrlIn ctrlInf;
	AudioCtrlCommon ctrlCommon;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_SLAVE;
		i2sCommon.clkDivEnable = DdAudio_DISABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_SLAVE;
		i2sCommon.clkDivEnable = DdAudio_DISABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);

	}

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bitIn = DdAudioI2s_BIT_16BIT;
	i2sIn.modeIn = E_DD_AUDIO_MODE_R_JUST;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	dd_audio_set_swap_byte_auidlr(dd_audio_get(), ch, DdAudio_ENABLE);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
		ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
		ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
		ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

#ifdef PC_DEBUG
	if (ch != 1){
		ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
	}
	else {
		ioAudio.AUDIOIF[0].AUCR.bit.AUIEF = 1;
		ioAudio.AUDIOIF[1].AUCR.bit.AUIEF = 1;
	}
#endif

	result = dd_audio_set_swap_byte_auidlr(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUMD.IBYTE_SWP=0x%x\n", ioAudio.AUDIOIF[ch].AUMD.bit.IBYTE_SWP));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_swapbyte_auidlr_test4( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	AudioCtrlIn ctrlInf;
	AudioCtrlCommon ctrlCommon;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	}

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bitIn = DdAudioI2s_BIT_16BIT;
	i2sIn.modeIn = E_DD_AUDIO_MODE_R_JUST;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	dd_audio_set_swap_byte_auidlr(dd_audio_get(), ch, DdAudio_DISABLE);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
		ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
		ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
		ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

#ifdef PC_DEBUG
	if (ch != 1){
		ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
	}
	else {
		ioAudio.AUDIOIF[0].AUCR.bit.AUIEF = 1;
		ioAudio.AUDIOIF[1].AUCR.bit.AUIEF = 1;
	}
#else
	ddim_user_custom_dly_tsk(1);
#endif

	result = dd_audio_set_swap_byte_auidlr(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUMD.IBYTE_SWP=0x%x\n", ioAudio.AUDIOIF[ch].AUMD.bit.IBYTE_SWP));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_swapbyte_auidlr_test5( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_swap_byte_auidlr(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set_swapbyte_auidlr_test6( CtDdAudioSet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_swap_byte_auidlr(dd_audio_get(), ch, 2);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

CtDdAudioSet *ct_dd_audio_set_new(gpointer *temp, guint8 ch)
{
    CtDdAudioSet *self = CT_DD_AUDIO_SET(g_object_new(CT_TYPE_DD_AUDIO_SET, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}

