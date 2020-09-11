/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl8类
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

G_DEFINE_TYPE(CtDdAudioCtrl8, ct_dd_audio_ctrl8, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_CTRL8_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_CTRL8, CtDdAudioCtrl8Private))

struct _CtDdAudioCtrl8Private
{
};
/*
 * DECLS
 */
static void ct_dd_audio_ctrl8_class_init(CtDdAudioCtrl8Class *klass);
static void ct_dd_audio_ctrl8_init(CtDdAudioCtrl8 *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);

/*
 * IMPL
 */
static void ct_dd_audio_ctrl8_class_init(CtDdAudioCtrl8Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioCtrl8Private));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_ctrl8_init(CtDdAudioCtrl8 *self)
{
	// CtDdAudioCtrl8 *self = CT_DD_AUDIO_CTRL8(object);
    // CtDdAudioCtrl8Private *priv = CT_DD_AUDIO_CTRL8_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl8_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl8_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_ctrl8_i2sin_test1( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_8BIT;
	i2sIn.mode_in = E_DD_AUDIO_MODE_L_JUST;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("AUCR.AUIF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIF));
	DriverCommon_DDIM_PRINT(("AUCR.AUIDSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIDSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test2( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_8BIT;
	i2sIn.mode_in = E_DD_AUDIO_MODE_R_JUST;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("AUCR.AUIF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIF));
	DriverCommon_DDIM_PRINT(("AUCR.AUIDSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIDSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test3( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_8BIT;
	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("AUCR.AUIF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIF));
	DriverCommon_DDIM_PRINT(("AUCR.AUIDSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIDSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test4( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	i2sIn.mode_in = E_DD_AUDIO_MODE_L_JUST;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("AUCR.AUIF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIF));
	DriverCommon_DDIM_PRINT(("AUCR.AUIDSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIDSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test5( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	i2sIn.mode_in = E_DD_AUDIO_MODE_R_JUST;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("AUCR.AUIF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIF));
	DriverCommon_DDIM_PRINT(("AUCR.AUIDSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIDSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test6( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("AUCR.AUIF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIF));
	DriverCommon_DDIM_PRINT(("AUCR.AUIDSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIDSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test7( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_24BIT;
	i2sIn.mode_in = E_DD_AUDIO_MODE_L_JUST;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("AUCR.AUIF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIF));
	DriverCommon_DDIM_PRINT(("AUCR.AUIDSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIDSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test8( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_24BIT;
	i2sIn.mode_in = E_DD_AUDIO_MODE_R_JUST;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("AUCR.AUIF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIF));
	DriverCommon_DDIM_PRINT(("AUCR.AUIDSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIDSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test9( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_24BIT;
	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("AUCR.AUIF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIF));
	DriverCommon_DDIM_PRINT(("AUCR.AUIDSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIDSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test10( CtDdAudioCtrl8 *self )
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
		i2sCommon.master_slave = E_DD_AUDIO_CLK_SLAVE;
		i2sCommon.clk_div_enable = DdAudio_DISABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.master_slave = E_DD_AUDIO_CLK_SLAVE;
		i2sCommon.clk_div_enable = DdAudio_DISABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);

	}

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	i2sIn.mode_in = E_DD_AUDIO_MODE_R_JUST;
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
		dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
		ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
		ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
		ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	i2sIn.mode_in = E_DD_AUDIO_MODE_R_JUST;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("AUCR.AUIF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIF));
	DriverCommon_DDIM_PRINT(("AUCR.AUIDSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIDSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test11( CtDdAudioCtrl8 *self )
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
	i2sIn.mode_in = E_DD_AUDIO_MODE_R_JUST;
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
		dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
		ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
		ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
		ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}


#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
#else
	ddim_user_custom_dly_tsk(1);
#endif

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_8BIT;
	i2sIn.mode_in = E_DD_AUDIO_MODE_L_JUST;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("AUCR.AUIF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIF));
	DriverCommon_DDIM_PRINT(("AUCR.AUIDSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIDSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test12( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = (E_DD_AUDIO_BIT)3;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test13( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_IN i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.mode_in = (E_DD_AUDIO_MODE)3;
	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sin_test14( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_ctrl_i2s_in(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test1( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_8BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_32FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test2( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_8BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_48FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test3( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_8BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test4( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_8BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_128FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test5( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_8BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_R_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_32FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test6( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_8BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_R_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_48FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test7( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_8BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_R_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test8( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_8BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_R_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_128FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test9( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_8BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_I2S;
	i2sOut.fs = E_DD_AUDIO_FS_32FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test10( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_8BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_I2S;
	i2sOut.fs = E_DD_AUDIO_FS_48FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test11( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_8BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_I2S;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test12( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_8BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_I2S;
	i2sOut.fs = E_DD_AUDIO_FS_128FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test13( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_32FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test14( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_48FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl8_i2sout_test15( CtDdAudioCtrl8 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_OUT i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;

	result = dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUOF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOF));
	DriverCommon_DDIM_PRINT(("AUCR.AUODSEL=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUODSEL));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

CtDdAudioCtrl8 *ct_dd_audio_ctrl8_new(gpointer *temp, guint8 ch)
{
    CtDdAudioCtrl8 *self = CT_DD_AUDIO_CTRL8(g_object_new(CT_TYPE_DD_AUDIO_CTRL8, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}

