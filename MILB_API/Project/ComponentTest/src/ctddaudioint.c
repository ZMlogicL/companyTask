/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioInt类
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

G_DEFINE_TYPE(CtDdAudioInt, ct_dd_audio_int, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_INT_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_INT, CtDdAudioIntPrivate))

struct _CtDdAudioIntPrivate
{
};

/*
 * DECLS
 */
static void ct_dd_audio_int_class_init(CtDdAudioIntClass *klass);
static void ct_dd_audio_int_init(CtDdAudioInt *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
/*
 * IMPL
 */
static void ct_dd_audio_int_class_init(CtDdAudioIntClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioIntPrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_int_init(CtDdAudioInt *self)
{
	// CtDdAudioInt *self = CT_DD_AUDIO_INT(object);
    // CtDdAudioIntPrivate *priv = CT_DD_AUDIO_INT_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_int_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_int_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_int_handler_test1(CtDdAudioInt *self)
{
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));
	const guint8 ch = self->ch;
#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test2(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_24BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	dd_audio_start_input(dd_audio_get(), ch);
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test3(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif
	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test4(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));
#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));
	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

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
	i2sIn.bit_in = E_DD_AUDIO_BIT_24BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(1);

	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test5(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_24BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	dd_audio_start_input(dd_audio_get(), ch);
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test6(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test7(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));
	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

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
	i2sIn.bit_in = E_DD_AUDIO_BIT_24BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	if (ch != 0){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(1);

	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test8(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bit_in = E_DD_AUDIO_BIT_24BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	dd_audio_start_input(dd_audio_get(), ch);
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test9(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test10(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	T_DD_AUDIO_CTRL_IN ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));
	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clk_div_enable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
		i2sIn.bit_in = E_DD_AUDIO_BIT_24BIT;
		dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clk_div_enable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
		i2sIn.bit_in = E_DD_AUDIO_BIT_24BIT;
		dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	}

	dd_audio_start_input(dd_audio_get(), ch);
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test11(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test12(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test13(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));
	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test14(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test15(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test16(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));
	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
//	printf("EINTOE set\n");
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test17(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_OUT i2sOut;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));
#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
	IO_AUDIO.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif
	dd_audio_init(dd_audio_get());
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.lr_copy = 0;
	ctrlInf.mix_play = 0;
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bit_out = E_DD_AUDIO_BIT_24BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_I2S;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;
	dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	dd_audio_start_output(dd_audio_get(), ch);
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUOEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF));
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 1;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test18(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	IO_AUDIO.AUDIOIF[ch].AUODLR = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test19(CtDdAudioInt *self)
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_OUT i2sOut;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
	IO_AUDIO.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	DDIM_User_DisableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch));
	dd_audio_init(dd_audio_get());
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlInf.lr_copy = 0;
	ctrlInf.mix_play = 0;
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

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
	i2sOut.bit_out = E_DD_AUDIO_BIT_24BIT;
	i2sOut.mode_out = E_DD_AUDIO_MODE_I2S;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;
	dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	if (ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUODLR = 1;

		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		IO_AUDIO.AUDIOIF[0].AUODLR = 1;
		IO_AUDIO.AUDIOIF[1].AUODLR = 1;

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(1);

	DriverCommon_DDIM_PRINT(("AUOEF = %d\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF));
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO = 0;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 1;
	IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF = 1;
	dd_audio_int_handler(dd_audio_get(), ch);
	IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE = 0;
	DDIM_User_EnableInt((DDIM_USER_INTID)(E_DD_GIC_INTID_AUDIO_IF_CH0_INT + ch), 14);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

CtDdAudioInt *ct_dd_audio_int_new(gpointer *temp, guint8 ch)
{
    CtDdAudioInt *self = CT_DD_AUDIO_INT(g_object_new(CT_TYPE_DD_AUDIO_INT, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}

