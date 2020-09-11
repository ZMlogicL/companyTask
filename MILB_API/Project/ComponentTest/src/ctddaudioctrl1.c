/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author            :luhongyin
*@brief                :CtDdAudioCtrl1类
*@rely                  :glib
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

G_DEFINE_TYPE(CtDdAudioCtrl1, ct_dd_audio_ctrl1, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_CTRL1_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_CTRL1, CtDdAudioCtrl1Private))

struct _CtDdAudioCtrl1Private
{
};

/*
 * DECLS
 */
static void ct_dd_audio_ctrl1_class_init(CtDdAudioCtrl1Class *klass);
static void ct_dd_audio_ctrl1_init(CtDdAudioCtrl1 *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);

/*
 * IMPL
 */
static void ct_dd_audio_ctrl1_class_init(CtDdAudioCtrl1Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioCtrl1Private));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_ctrl1_init(CtDdAudioCtrl1 *self)
{
	// CtDdAudioCtrl1 *self = CT_DD_AUDIO_CTRL1(object);
    // CtDdAudioCtrl1Private *priv = CT_DD_AUDIO_CTRL1_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl1_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl1_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_ctrl1_input_test11( CtDdAudioCtrl1 *self )
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

	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_input_test12( CtDdAudioCtrl1 *self )
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
	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_1;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_input_test13( CtDdAudioCtrl1 *self )
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
	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_2;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_input_test14( CtDdAudioCtrl1 *self )
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
	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_3;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUIRF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF));
	DriverCommon_DDIM_PRINT(("AUMD.ISTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS));
	DriverCommon_DDIM_PRINT(("AUDP.AUIDF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF));
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_input_test15( CtDdAudioCtrl1 *self )
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

	ddim_user_custom_dly_tsk(0);
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIRF = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_input_test16( CtDdAudioCtrl1 *self )
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

	ddim_user_custom_dly_tsk(0);
#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
#endif
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));

	IO_AUDIO.AUDIOIF[ch].AUMD.bit.ISTG16 = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_input_test17( CtDdAudioCtrl1 *self )
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

	ddim_user_custom_dly_tsk(0);
#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
#endif

	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));

	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDF = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_input_test18( CtDdAudioCtrl1 *self )
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

	ddim_user_custom_dly_tsk(0);
#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
#endif

	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));

	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUIDS = 0;

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_1;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_input_test19( CtDdAudioCtrl1 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = (E_DD_AUDIO_DATA_REG_FRMT)2;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_input_test20( CtDdAudioCtrl1 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = (E_DD_AUDIO_FIFO_STAGES)2;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_input_test21( CtDdAudioCtrl1 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.ahb_format = (E_DD_AUDIO_AHB_FRMT)2;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_input_test22( CtDdAudioCtrl1 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bit_shift = (E_DD_AUDIO_BIT_SHIFT)4;
	result = dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_input_test23( CtDdAudioCtrl1 *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_ctrl_input(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_output_test1( CtDdAudioCtrl1 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUORF = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_output_test2( CtDdAudioCtrl1 *self )
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

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

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

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUORF = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_output_test3( CtDdAudioCtrl1 *self )
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

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

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

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
#endif

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	ctrlInfOut.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInfOut.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlInfOut.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	dd_audio_start_loop_back(dd_audio_get(), ch);

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUORF = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);
	ctrlInfOut.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl1_output_test4( CtDdAudioCtrl1 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUORF = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", IO_AUDIO.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

CtDdAudioCtrl1 *ct_dd_audio_ctrl1_new(gpointer *temp, guint8 ch)
{
    CtDdAudioCtrl1 *self = CT_DD_AUDIO_CTRL1(g_object_new(CT_TYPE_DD_AUDIO_CTRL1, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}
