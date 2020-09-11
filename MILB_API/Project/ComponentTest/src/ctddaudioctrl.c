/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author            :luhongyin
*@brief               :CtDdAudioCtrl类
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

G_DEFINE_TYPE(CtDdAudioCtrl, ct_dd_audio_ctrl, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_CTRL_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_CTRL, CtDdAudioCtrlPrivate))

struct _CtDdAudioCtrlPrivate
{
};

/*
*DECLS
*/
static void ct_dd_audio_ctrl_class_init(CtDdAudioCtrlClass *klass);
static void ct_dd_audio_ctrl_init(CtDdAudioCtrl *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
/*
 * IMPL
 */
static void ct_dd_audio_ctrl_class_init(CtDdAudioCtrlClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioCtrlPrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_ctrl_init(CtDdAudioCtrl *self)
{
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl_parent_class)->finalize(object);
}
/*
*PUBLIC
*/
void ct_dd_audio_ctrl_common_test1( CtDdAudioCtrl *self )
{
	gint32 result;
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlInf;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	ctrlInf.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_1;
	ctrlInf.channel = E_DD_AUDIO_CHANNEL_MONO;

	result = dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUST.ESTG=%d\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.ESTG));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_common_test2( CtDdAudioCtrl *self )
{
	gint32 result;
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlInf;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	ctrlInf.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_12;
	ctrlInf.channel = E_DD_AUDIO_CHANNEL_STEREO;

	result = dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUST.ESTG=%d\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.ESTG));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_common_test3( CtDdAudioCtrl *self )
{
	gint32 result;
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlInf;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	ctrlInf.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlInf.channel = E_DD_AUDIO_CHANNEL_MONO;

	result = dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUST.ESTG=%d\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.ESTG));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_common_test4( CtDdAudioCtrl *self )
{
	gint32 result;
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlInf;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	ctrlInf.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_4;
	ctrlInf.channel = E_DD_AUDIO_CHANNEL_STEREO;

	result = dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUST.ESTG=%d\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.ESTG));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_common_test5( CtDdAudioCtrl *self )
{
	gint32 result;
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlInf;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	ctrlInf.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	ctrlInf.channel = E_DD_AUDIO_CHANNEL_MONO;

	DriverCommon_DDIM_PRINT(("AUST.ESTG=%d\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.ESTG));

	result = dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUST.ESTG=%d\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.ESTG));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_common_test6( CtDdAudioCtrl *self )
{
	gint32 result;
	const guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_ctrl_common(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_common_test7( CtDdAudioCtrl *self )
{
	gint32 result;
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlInf;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_usage = (E_DD_AUDIO_FIFO_USAGE)5;
	result = dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_common_test8( CtDdAudioCtrl *self )
{
	gint32 result;
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlInf;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.channel = (E_DD_AUDIO_CHANNEL)2;
	result = dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_common_test9( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
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
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
		ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
		ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
		ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
		ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(0);

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_MONO;
	result = dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_common_test10( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	if ( ch != 1){
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

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	if ( ch != 1){
		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
		ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
		(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(0);

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_MONO;
	result = dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_common_test11( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInfIn;
	T_DD_AUDIO_CTRL_OUT ctrlInfOut;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
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
	ctrlInfIn.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
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
		ctrlInfIn.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
		ctrlInfIn.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
		ctrlInfIn.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
		ctrlInfIn.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInfIn);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	ctrlInfOut.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInfOut.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlInfOut.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	dd_audio_start_loop_back(dd_audio_get(), ch);

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 1;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	result = dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_input_test1( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF = 1;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_input_test2( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
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
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
		ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
		ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
		ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_input_test3( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_input_test4( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16 = 1;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_input_test5( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
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
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
		ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
		ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
		ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));

	IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16 = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_input_test6( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16 = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_input_test7( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF = 1;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_input_test8( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
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
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_8;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
		ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
		ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
		ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));

	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_input_test9( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl_input_test10( CtDdAudioCtrl *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS = 1;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

CtDdAudioCtrl *ct_dd_audio_ctrl_new(gpointer *temp, guint8 ch)
{
    CtDdAudioCtrl *self = CT_DD_AUDIO_CTRL(g_object_new(CT_TYPE_DD_AUDIO_CTRL, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}

