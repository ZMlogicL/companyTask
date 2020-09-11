/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioSet2类
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
#include "ctddaudioset1.h"
#include "ctddaudioset2.h"

G_DEFINE_TYPE(CtDdAudioSet2, ct_dd_audio_set2, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_SET2_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_SET2, CtDdAudioSet2Private))

struct _CtDdAudioSet2Private
{
};

/*
 * DECLS
 */
static void ct_dd_audio_set2_class_init(CtDdAudioSet2Class *klass);
static void ct_dd_audio_set2_init(CtDdAudioSet2 *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
/*
 * IMPL
 */
static void ct_dd_audio_set2_class_init(CtDdAudioSet2Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioSet2Private));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_set2_init(CtDdAudioSet2 *self)
{
	// CtDdAudioSet2 *self = CT_DD_AUDIO_SET2(object);
    // CtDdAudioSet2Private *priv = CT_DD_AUDIO_SET2_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_set2_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_set2_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_set2_swapbyte_auodlr_test6( CtDdAudioSet2 *self )
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
	if (ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
	}
	else {
		IO_AUDIO.AUDIOIF[0].AUCR.bit.AUIEF = 1;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.AUIEF = 1;
	}
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

	dd_audio_set_swap_byte_auodlr(dd_audio_get(), ch, DdAudio_DISABLE);

	dd_audio_start_loop_back(dd_audio_get(), ch);

#ifdef PC_DEBUG
	if (ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 1;
	}
	else {
		IO_AUDIO.AUDIOIF[0].AUMD.bit.LBF = 1;
		IO_AUDIO.AUDIOIF[1].AUMD.bit.LBF = 1;
	}
#else
	ddim_user_custom_dly_tsk(1);
#endif

	result = dd_audio_set_swap_byte_auodlr(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("AUMD.OBYTE_SWP=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.OBYTE_SWP));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_swapbyte_auodlr_test7( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_swap_byte_auodlr(dd_audio_get(), ch, DdAudio_ENABLE);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_swapbyte_auodlr_test8( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_swap_byte_auodlr(dd_audio_get(), ch, 2);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_input_intr_test1( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_input_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE));
	DriverCommon_DDIM_PRINT(("AUST.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_input_intr_test2( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_input_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE));
	DriverCommon_DDIM_PRINT(("AUST.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_input_intr_test3( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_input_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE));
	DriverCommon_DDIM_PRINT(("AUST.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_input_intr_test4( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_input_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE));
	DriverCommon_DDIM_PRINT(("AUST.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_input_intr_test5( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 1;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_input_intr(dd_audio_get(), ch, DdAudio_DISABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE));
	DriverCommon_DDIM_PRINT(("AUST.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_input_intr_test6( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 1;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_input_intr(dd_audio_get(), ch, DdAudio_DISABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE));
	DriverCommon_DDIM_PRINT(("AUST.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_input_intr_test7( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 1;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_input_intr(dd_audio_get(), ch, DdAudio_DISABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE));
	DriverCommon_DDIM_PRINT(("AUST.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_input_intr_test8( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_input_intr(dd_audio_get(), ch, DdAudio_DISABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE));
	DriverCommon_DDIM_PRINT(("AUST.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_input_intr_test9( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 1;

	result = dd_audio_set_enable_input_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE));
	DriverCommon_DDIM_PRINT(("AUST.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_input_intr_test10( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 1;

	result = dd_audio_set_enable_input_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE));
	DriverCommon_DDIM_PRINT(("AUST.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_input_intr_test11( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_enable_input_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_input_intr_test12( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_enable_input_intr(dd_audio_get(), ch, 2, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_output_intr_test1( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_output_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE));
	DriverCommon_DDIM_PRINT(("AUST.EINTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE));

	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_output_intr_test2( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_output_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE));
	DriverCommon_DDIM_PRINT(("AUST.EINTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE));

	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_output_intr_test3( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_output_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE));
	DriverCommon_DDIM_PRINT(("AUST.EINTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE));

	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_output_intr_test4( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_output_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE));
	DriverCommon_DDIM_PRINT(("AUST.EINTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE));

	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_output_intr_test5( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 1;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_output_intr(dd_audio_get(), ch, DdAudio_DISABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE));
	DriverCommon_DDIM_PRINT(("AUST.EINTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE));

	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_output_intr_test6( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));

	CtDdAudio *regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 1;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_output_intr(dd_audio_get(), ch, DdAudio_DISABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE));
	DriverCommon_DDIM_PRINT(("AUST.EINTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE));

	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_output_intr_test7( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 1;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_output_intr(dd_audio_get(), ch, DdAudio_DISABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE));
	DriverCommon_DDIM_PRINT(("AUST.EINTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE));

	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_output_intr_test8( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_set_enable_output_intr(dd_audio_get(), ch, DdAudio_DISABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE));
	DriverCommon_DDIM_PRINT(("AUST.EINTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE));

	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set2_enable_output_intr_test9( CtDdAudioSet2 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 1;

	result = dd_audio_set_enable_output_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE));
	DriverCommon_DDIM_PRINT(("AUST.EINTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE));

	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

CtDdAudioSet2 *ct_dd_audio_set2_new(gpointer *temp, guint8 ch)
{
    CtDdAudioSet2 *self = CT_DD_AUDIO_SET2(g_object_new(CT_TYPE_DD_AUDIO_SET2, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}

