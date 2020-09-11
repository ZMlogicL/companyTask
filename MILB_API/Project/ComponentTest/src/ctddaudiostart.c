/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioStart类
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

G_DEFINE_TYPE(CtDdAudioStart, ct_dd_audio_start, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_START_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_START, CtDdAudioStartPrivate))

struct _CtDdAudioStartPrivate
{
};

/*
 * DECLS
 */
static void ct_dd_audio_start_class_init(CtDdAudioStartClass *klass);
static void ct_dd_audio_start_init(CtDdAudioStart *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
/*
 * IMPL
 */
static void ct_dd_audio_start_class_init(CtDdAudioStartClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioStartPrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_start_init(CtDdAudioStart *self)
{
	// CtDdAudioStart *self = CT_DD_AUDIO_START(object);
    // CtDdAudioStartPrivate *priv = CT_DD_AUDIO_START_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_start_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_start_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_start_input_test1( CtDdAudioStart *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	if (ch != DdAudio_IF_CH1){
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
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_start_input(dd_audio_get(), ch);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
#endif

	DriverCommon_DDIM_PRINT(("AUST.IROF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF));
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUCR.AUIEF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_start_input_test2( CtDdAudioStart *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_start_input(dd_audio_get(), ch);

	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUCR.AUIEF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));
	DriverCommon_DDIM_PRINT(("AUST.IROF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_start_input_test_multi01( CtDdAudioStart *self )
{
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, 1);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), 0, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), 0, &i2sIn);

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), 1, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), 1, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

	dd_audio_get_ctrl_common(dd_audio_get(), 1, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), 1, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInf);
	(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInf);
	dd_audio_get_ctrl_input(dd_audio_get(), 1, &ctrlInf);
	(void)dd_audio_ctrl_input(dd_audio_get(), 1, &ctrlInf);

	result = dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[0].AUCR.bit.AUIEF = 1;
	IO_AUDIO.AUDIOIF[1].AUCR.bit.AUIEF = 1;
#endif

	DriverCommon_DDIM_PRINT(("AUST0.IROF=0x%x\n", IO_AUDIO.AUDIOIF[0].AUST.bit.IROF));
	DriverCommon_DDIM_PRINT(("AUST1.IROF=0x%x\n", IO_AUDIO.AUDIOIF[1].AUST.bit.IROF));
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUCR0.AUIEF=0x%x\n", IO_AUDIO.AUDIOIF[0].AUCR.bit.AUIEF));
	DriverCommon_DDIM_PRINT(("AUCR1.AUIEF=0x%x\n", IO_AUDIO.AUDIOIF[1].AUCR.bit.AUIEF));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x\n", __FUNCTION__, result));
}

void ct_dd_audio_start_input_test_multi45( CtDdAudioStart *self )
{
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, 4);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	regInit = ct_dd_audio_new(NULL, 5);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);


	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 4, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 4, &i2sCommon);
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 5, &i2sCommon);

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), 4, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), 4, &i2sIn);
	dd_audio_ctrl_i2s_in(dd_audio_get(), 5, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), 4, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), 4, &ctrlCommon);
	dd_audio_ctrl_common(dd_audio_get(), 5, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), 4, &ctrlInf);
	(void)dd_audio_ctrl_input(dd_audio_get(), 4, &ctrlInf);
	(void)dd_audio_ctrl_input(dd_audio_get(), 5, &ctrlInf);

	result = dd_audio_start_input(dd_audio_get(), D_DD_AUDIO_IF_CH4_CH5);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[4].AUCR.bit.AUIEF = 1;
	IO_AUDIO.AUDIOIF[5].AUCR.bit.AUIEF = 1;
#endif

	DriverCommon_DDIM_PRINT(("AUST4.IROF=0x%x\n", IO_AUDIO.AUDIOIF[4].AUST.bit.IROF));
	DriverCommon_DDIM_PRINT(("AUST5.IROF=0x%x\n", IO_AUDIO.AUDIOIF[5].AUST.bit.IROF));
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUCR4.AUIEF=0x%x\n", IO_AUDIO.AUDIOIF[4].AUCR.bit.AUIEF));
	DriverCommon_DDIM_PRINT(("AUCR5.AUIEF=0x%x\n", IO_AUDIO.AUDIOIF[5].AUCR.bit.AUIEF));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x\n", __FUNCTION__, result));
}

void ct_dd_audio_start_output_test1( CtDdAudioStart *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_OUT i2sOut;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
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

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;
	dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	result = dd_audio_start_output(dd_audio_get(), ch);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
#endif

	DriverCommon_DDIM_PRINT(("AUST.ORUF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF));
	DriverCommon_DDIM_PRINT(("AUCR.AUOEF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF));
	DriverCommon_DDIM_PRINT(("AUOE.AUOE=0x%x\n", (unsigned int)IO_AUDIO.AUDIOIF_CTRL.AUIOE.word));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_start_output_test2( CtDdAudioStart *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_start_output(dd_audio_get(), ch);

	if (ch != DdAudio_IF_CH0_CH1){
		DriverCommon_DDIM_PRINT(("AUST.ORUF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF));
		DriverCommon_DDIM_PRINT(("AUCR.AUOEF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF));
	}
	else {
		DriverCommon_DDIM_PRINT(("AUST0.ORUF=0x%x\n", IO_AUDIO.AUDIOIF[0].AUST.bit.ORUF));
		DriverCommon_DDIM_PRINT(("AUCR0.AUOEF=0x%x\n", IO_AUDIO.AUDIOIF[0].AUCR.bit.AUOEF));

		DriverCommon_DDIM_PRINT(("AUST1.ORUF=0x%x\n", IO_AUDIO.AUDIOIF[1].AUST.bit.ORUF));
		DriverCommon_DDIM_PRINT(("AUCR1.AUOEF=0x%x\n", IO_AUDIO.AUDIOIF[1].AUCR.bit.AUOEF));
	}

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_start_output_test_multi( CtDdAudioStart *self )
{
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_OUT i2sOut;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, 1);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);


	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), 0, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;
	dd_audio_ctrl_i2s_out(dd_audio_get(), 0, &i2sOut);

	dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

	dd_audio_get_ctrl_common(dd_audio_get(), 1, &ctrlCommon);
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), 1, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

	dd_audio_get_ctrl_output(dd_audio_get(), 1, &ctrlInf);
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_output(dd_audio_get(), 1, &ctrlInf);

	result = dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[0].AUCR.bit.AUOEF = 1;
	IO_AUDIO.AUDIOIF[1].AUCR.bit.AUOEF = 1;
#endif

	DriverCommon_DDIM_PRINT(("AUST.ORUF0=0x%x\n", IO_AUDIO.AUDIOIF[0].AUST.bit.ORUF));
	DriverCommon_DDIM_PRINT(("AUST.ORUF1=0x%x\n", IO_AUDIO.AUDIOIF[1].AUST.bit.ORUF));
	DriverCommon_DDIM_PRINT(("AUCR.AUOEF0=0x%x\n", IO_AUDIO.AUDIOIF[0].AUCR.bit.AUOEF));
	DriverCommon_DDIM_PRINT(("AUCR.AUOEF1=0x%x\n", IO_AUDIO.AUDIOIF[1].AUCR.bit.AUOEF));
	DriverCommon_DDIM_PRINT(("AUOE.AUOE=0x%x\n", (unsigned int)IO_AUDIO.AUDIOIF_CTRL.AUIOE.word));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x\n", __FUNCTION__, result));
}

void ct_dd_audio_start_loop_back_test1( CtDdAudioStart *self )
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

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInfIn);
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInfIn);

	dd_audio_start_input(dd_audio_get(), ch);

//	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;		// for PC-Sim
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
	dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	ddim_user_custom_dly_tsk(0);

	result = dd_audio_start_loop_back(dd_audio_get(), ch);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 1;
#endif

	ddim_user_custom_dly_tsk(0);

	DriverCommon_DDIM_PRINT(("AUMD.LBF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_start_loop_back_test2( CtDdAudioStart *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_start_loop_back(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_start_loop_back_test3( CtDdAudioStart *self )
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

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInfIn);
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInfIn);

	dd_audio_start_input(dd_audio_get(), ch);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;		// for PC-Sim
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
	dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	dd_audio_start_output(dd_audio_get(), ch);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 1;		// for PC-Sim
#else
	ddim_user_custom_dly_tsk(1);
#endif

	result = dd_audio_start_loop_back(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_start_loop_back_test_multi( CtDdAudioStart *self )
{
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInfIn;
	T_DD_AUDIO_CTRL_OUT ctrlInfOut;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, 1);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), 0, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), 0, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

	dd_audio_get_ctrl_common(dd_audio_get(), 1, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), 1, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInfIn);
	(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInfIn);

	dd_audio_get_ctrl_input(dd_audio_get(), 1, &ctrlInfIn);
	(void)dd_audio_ctrl_input(dd_audio_get(), 1, &ctrlInfIn);

	dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[0].AUCR.bit.AUIEF = 1;		// for PC-Sim
	IO_AUDIO.AUDIOIF[1].AUCR.bit.AUIEF = 1;		// for PC-Sim
#endif

	ddim_user_custom_dly_tsk(0);

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), 0, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;
	dd_audio_ctrl_i2s_out(dd_audio_get(), 0, &i2sOut);

	dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInfOut);
	ctrlInfOut.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlInfOut.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInfOut.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInfOut);

	dd_audio_get_ctrl_output(dd_audio_get(), 1, &ctrlInfOut);
	ctrlInfOut.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlInfOut.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInfOut.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	dd_audio_ctrl_output(dd_audio_get(), 1, &ctrlInfOut);

	result = dd_audio_start_loop_back(dd_audio_get(), DdAudio_IF_CH0_CH1);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[0].AUMD.bit.LBF = 1;
	IO_AUDIO.AUDIOIF[1].AUMD.bit.LBF = 1;
#endif

	ddim_user_custom_dly_tsk(0);

	DriverCommon_DDIM_PRINT(("AUMD0.LBF=0x%x\n", IO_AUDIO.AUDIOIF[0].AUMD.bit.LBF));
	DriverCommon_DDIM_PRINT(("AUMD1.LBF=0x%x\n", IO_AUDIO.AUDIOIF[1].AUMD.bit.LBF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x\n", __FUNCTION__, result));
}

void ct_dd_audio_start_loop_back_test_multi2( CtDdAudioStart *self )
{
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_IN ctrlInfIn;
	T_DD_AUDIO_CTRL_OUT ctrlInfOut;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), 0, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), 0, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

	dd_audio_get_ctrl_common(dd_audio_get(), 1, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), 1, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInfIn);
	(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInfIn);

	dd_audio_get_ctrl_input(dd_audio_get(), 1, &ctrlInfIn);
	(void)dd_audio_ctrl_input(dd_audio_get(), 1, &ctrlInfIn);

	dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[0].AUCR.bit.AUIEF = 1;		// for PC-Sim
	IO_AUDIO.AUDIOIF[1].AUCR.bit.AUIEF = 1;		// for PC-Sim
#endif

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), 0, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;
	dd_audio_ctrl_i2s_out(dd_audio_get(), 0, &i2sOut);

	dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInfOut);
	ctrlInfOut.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlInfOut.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInfOut.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInfOut);

	dd_audio_get_ctrl_output(dd_audio_get(), 1, &ctrlInfOut);
	ctrlInfOut.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlInfOut.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInfOut.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	dd_audio_ctrl_output(dd_audio_get(), 1, &ctrlInfOut);

	result = dd_audio_start_loop_back(dd_audio_get(), DdAudio_IF_CH0_CH1);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[0].AUMD.bit.LBF = 1;
	IO_AUDIO.AUDIOIF[1].AUMD.bit.LBF = 1;
#endif

	DriverCommon_DDIM_PRINT(("AUMD0.LBF=0x%x\n", IO_AUDIO.AUDIOIF[0].AUMD.bit.LBF));
	DriverCommon_DDIM_PRINT(("AUMD1.LBF=0x%x\n", IO_AUDIO.AUDIOIF[1].AUMD.bit.LBF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x\n", __FUNCTION__, result));
}

CtDdAudioStart* ct_dd_audio_start_set_ch(CtDdAudioStart *self, guint8 ch)
{
	self->ch = ch;
	return self;
}

CtDdAudioStart *ct_dd_audio_start_new(gpointer *temp, guint8 ch)
{
    CtDdAudioStart *self = CT_DD_AUDIO_START(g_object_new(CT_TYPE_DD_AUDIO_START, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}

