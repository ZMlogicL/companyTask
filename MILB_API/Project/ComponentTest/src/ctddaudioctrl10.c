/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl10类
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

G_DEFINE_TYPE(CtDdAudioCtrl10, ct_dd_audio_ctrl10, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_CTRL10_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_CTRL10, CtDdAudioCtrl10Private))

struct _CtDdAudioCtrl10Private
{
};

/*
 * DECLS
 */
static void ct_dd_audio_ctrl10_class_init(CtDdAudioCtrl10Class *klass);
static void ct_dd_audio_ctrl10_init(CtDdAudioCtrl10 *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
/*
 * IMPL
 */
static void ct_dd_audio_ctrl10_class_init(CtDdAudioCtrl10Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioCtrl10Private));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_ctrl10_init(CtDdAudioCtrl10 *self)
{
	// CtDdAudioCtrl10 *self = CT_DD_AUDIO_CTRL10(object);
    // CtDdAudioCtrl10Private *priv = CT_DD_AUDIO_CTRL10_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl10_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl10_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_ctrl10_i2sout_test40( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInfIn;
	T_DD_AUDIO_CTRL_OUT ctrlInfOut;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clk_div_enable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clk_div_enable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	}

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_MONO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInfIn);
	ctrlInfIn.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlInfIn.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlInfIn.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlInfIn.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInfIn);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
		ctrlCommon.channel = E_DD_AUDIO_CHANNEL_MONO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInfIn);
		ctrlInfIn.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
		ctrlInfIn.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
		ctrlInfIn.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
		ctrlInfIn.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInfIn);
		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
#else
	ddim_user_custom_dly_tsk(1);
#endif

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;
	dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	ctrlInfOut.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlInfOut.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInfOut.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	dd_audio_start_loop_back(dd_audio_get(), ch);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 1;
#else
	ddim_user_custom_dly_tsk(1);
#endif

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_R_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;
	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_i2sout_test41( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = (E_DD_AUDIO_BIT)3;
	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_i2sout_test42( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.mode_out = (E_DD_AUDIO_MODE)3;
	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_i2sout_test43( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.fs = (E_DD_AUDIO_FS)4;
	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_i2sout_test44( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmain_test1( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_DMA dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

	dmaSetting.dma_2ch = DdAudio_DISABLE;
	dmaSetting.dma_trnsf_cnt = 0;

	result = dd_audio_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("AUDMA2CTL.DMI2CHEN=%x\n", IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.bit.DMI2CHEN));
	DriverCommon_DDIM_PRINT(("AUDMISAMPLE.DMISPL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUDMISAMPLE.bit.DMISPL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmain_test2( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_DMA dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

	dmaSetting.dma_2ch = DdAudio_ENABLE;
	dmaSetting.dma_trnsf_cnt = 1024;

	result = dd_audio_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("AUDMA2CTL.DMI2CHEN=%x\n", IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.bit.DMI2CHEN));
	DriverCommon_DDIM_PRINT(("AUDMISAMPLE.DMISPL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUDMISAMPLE.bit.DMISPL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmain_test3( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_DMA dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));


	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.DMIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EDMIE = 1;

	dd_audio_get_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

	dmaSetting.dma_2ch = DdAudio_ENABLE;
	dmaSetting.dma_trnsf_cnt = 1024;

	result = dd_audio_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("AUDMA2CTL.DMI2CHEN=%x\n", IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.bit.DMI2CHEN));
	DriverCommon_DDIM_PRINT(("AUDMISAMPLE.DMISPL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUDMISAMPLE.bit.DMISPL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmain_test4( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_DMA dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.DMIE = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EDMIE = 0;

	dd_audio_get_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

	dmaSetting.dma_2ch = DdAudio_ENABLE;
	dmaSetting.dma_trnsf_cnt = 1024;

	result = dd_audio_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("AUDMA2CTL.DMI2CHEN=%x\n", IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.bit.DMI2CHEN));
	DriverCommon_DDIM_PRINT(("AUDMISAMPLE.DMISPL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUDMISAMPLE.bit.DMISPL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmain_test5( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_DMA dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.DMIE = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EDMIE = 1;

	dd_audio_get_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

	dmaSetting.dma_2ch = DdAudio_ENABLE;
	dmaSetting.dma_trnsf_cnt = 1024;

	result = dd_audio_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("AUDMA2CTL.DMI2CHEN=%x\n", IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.bit.DMI2CHEN));
	DriverCommon_DDIM_PRINT(("AUDMISAMPLE.DMISPL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUDMISAMPLE.bit.DMISPL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmain_test6( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_DMA dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dmaSetting.dma_2ch = 2;
	dmaSetting.dma_trnsf_cnt = 1024;

	result = dd_audio_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmain_test7( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_ctrl_dma_in(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmaout_test1( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_DMA dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.DMOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EDMOE = 0;

	dd_audio_get_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

	dmaSetting.dma_2ch = DdAudio_DISABLE;
	dmaSetting.dma_trnsf_cnt = 0;

	result = dd_audio_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("AUDMA2CTL.DMO2CHEN=%x\n", IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.bit.DMO2CHEN));
	DriverCommon_DDIM_PRINT(("AUDMISAMPLE.DMOSPL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUDMOSAMPLE.bit.DMOSPL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmaout_test2( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_DMA dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.DMOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EDMOE = 0;

	dd_audio_get_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

	dmaSetting.dma_2ch = DdAudio_ENABLE;
	dmaSetting.dma_trnsf_cnt = 1024;

	result = dd_audio_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("AUDMA2CTL.DMO2CHEN=%x\n", IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.bit.DMO2CHEN));
	DriverCommon_DDIM_PRINT(("AUDMISAMPLE.DMOSPL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUDMOSAMPLE.bit.DMOSPL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmaout_test3( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_DMA dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.DMOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EDMOE = 1;

	dd_audio_get_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

	dmaSetting.dma_2ch = DdAudio_ENABLE;
	dmaSetting.dma_trnsf_cnt = 1024;

	result = dd_audio_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("AUDMA2CTL.DMO2CHEN=%x\n", IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.bit.DMO2CHEN));
	DriverCommon_DDIM_PRINT(("AUDMISAMPLE.DMOSPL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUDMOSAMPLE.bit.DMOSPL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmaout_test4( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_DMA dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.DMOE = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EDMOE = 0;

	dd_audio_get_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

	dmaSetting.dma_2ch = DdAudio_ENABLE;
	dmaSetting.dma_trnsf_cnt = 1024;

	result = dd_audio_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("AUDMA2CTL.DMO2CHEN=%x\n", IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.bit.DMO2CHEN));
	DriverCommon_DDIM_PRINT(("AUDMISAMPLE.DMOSPL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUDMOSAMPLE.bit.DMOSPL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmaout_test5( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_DMA dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.DMOE = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EDMOE = 1;

	dd_audio_get_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

	dmaSetting.dma_2ch = DdAudio_ENABLE;
	dmaSetting.dma_trnsf_cnt = 1024;

	result = dd_audio_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("AUDMA2CTL.DMO2CHEN=%x\n", IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.bit.DMO2CHEN));
	DriverCommon_DDIM_PRINT(("AUDMISAMPLE.DMOSPL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUDMOSAMPLE.bit.DMOSPL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmaout_test6( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_DMA dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dmaSetting.dma_2ch = 2;
	dmaSetting.dma_trnsf_cnt = 1024;

	result = dd_audio_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("AUDMA2CTL.DMO2CHEN=%x\n", IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.bit.DMO2CHEN));
	DriverCommon_DDIM_PRINT(("AUDMISAMPLE.DMOSPL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUDMOSAMPLE.bit.DMOSPL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl10_dmaout_test7( CtDdAudioCtrl10 *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_ctrl_dma_out(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}


CtDdAudioCtrl10 *ct_dd_audio_ctrl10_new(gpointer *temp, guint8 ch)
{
    CtDdAudioCtrl10 *self = CT_DD_AUDIO_CTRL10(g_object_new(CT_TYPE_DD_AUDIO_CTRL10, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}
