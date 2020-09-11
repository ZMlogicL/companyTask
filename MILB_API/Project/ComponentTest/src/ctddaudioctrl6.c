/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl6类
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

G_DEFINE_TYPE(CtDdAudioCtrl6, ct_dd_audio_ctrl6, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_CTRL6_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_CTRL6, CtDdAudioCtrl6Private))

struct _CtDdAudioCtrl6Private
{
};

/*
 * DECLS
 */
static void ct_dd_audio_ctrl6_class_init(CtDdAudioCtrl6Class *klass);
static void ct_dd_audio_ctrl6_init(CtDdAudioCtrl6 *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);

/*
 * IMPL
 */
static void ct_dd_audio_ctrl6_class_init(CtDdAudioCtrl6Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioCtrl6Private));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_ctrl6_init(CtDdAudioCtrl6 *self)
{
	// CtDdAudioCtrl6 *self = CT_DD_AUDIO_CTRL6(object);
    // CtDdAudioCtrl6Private *priv = CT_DD_AUDIO_CTRL6_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl6_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl6_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_ctrl6_i2scmmn_test23( CtDdAudioCtrl6 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_32;
	i2sCommon.clk_div_enable = DdAudio_DISABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_32;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = DdAudio_DISABLE;
	result = dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("AUCC.DIVMCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVMCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVLR = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVLR));
	DriverCommon_DDIM_PRINT(("AUCC.AUCKOE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE));
	DriverCommon_DDIM_PRINT(("AUCC.DIVE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE));

	if (ch == 0){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU0SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU0SEL()));
	}
	else if (ch == 2){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU2SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU2SEL()));
	}
	else if (ch == 3){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU3SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU3SEL()));
	}
	else {
		;
	}

	DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AUCLK = 0x%x\n",Dd_Top_Get_CLKSEL8_AUCLK()));
	DriverCommon_DDIM_PRINT(("CHIPTOP.PLLCNT9.P10APLLDIV = 0x%x\n",IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl6_i2scmmn_test24( CtDdAudioCtrl6 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_32;
	i2sCommon.clk_div_enable = DdAudio_DISABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_32;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_32;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_32;
	i2sCommon.clk_div_enable = DdAudio_DISABLE;
	result = dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("AUCC.DIVMCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVMCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVLR = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVLR));
	DriverCommon_DDIM_PRINT(("AUCC.AUCKOE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE));
	DriverCommon_DDIM_PRINT(("AUCC.DIVE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE));

	if (ch == 0){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU0SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU0SEL()));
	}
	else if (ch == 2){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU2SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU2SEL()));
	}
	else if (ch == 3){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU3SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU3SEL()));
	}
	else {
		;
	}

	DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AUCLK = 0x%x\n",Dd_Top_Get_CLKSEL8_AUCLK()));
	DriverCommon_DDIM_PRINT(("CHIPTOP.PLLCNT9.P10APLLDIV = 0x%x\n",IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl6_i2scmmn_test25( CtDdAudioCtrl6 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_32;
	i2sCommon.clk_div_enable = DdAudio_DISABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_32;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_32;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = DdAudio_DISABLE;
	result = dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("AUCC.DIVMCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVMCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVLR = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVLR));
	DriverCommon_DDIM_PRINT(("AUCC.AUCKOE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE));
	DriverCommon_DDIM_PRINT(("AUCC.DIVE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE));

	if (ch == 0){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU0SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU0SEL()));
	}
	else if (ch == 2){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU2SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU2SEL()));
	}
	else if (ch == 3){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU3SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU3SEL()));
	}
	else {
		;
	}

	DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AUCLK = 0x%x\n",Dd_Top_Get_CLKSEL8_AUCLK()));
	DriverCommon_DDIM_PRINT(("CHIPTOP.PLLCNT9.P10APLLDIV = 0x%x\n",IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl6_i2scmmn_test26( CtDdAudioCtrl6 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_SLAVE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	result = dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("AUCC.DIVMCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVMCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVLR = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVLR));
	DriverCommon_DDIM_PRINT(("AUCC.AUCKOE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE));
	DriverCommon_DDIM_PRINT(("AUCC.DIVE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE));

	if (ch == 0){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU0SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU0SEL()));
	}
	else if (ch == 2){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU2SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU2SEL()));
	}
	else if (ch == 3){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU3SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU3SEL()));
	}
	else {
		;
	}

	DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AUCLK = 0x%x\n",Dd_Top_Get_CLKSEL8_AUCLK()));
	DriverCommon_DDIM_PRINT(("CHIPTOP.PLLCNT9.P10APLLDIV = 0x%x\n",IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl6_i2scmmn_test27( CtDdAudioCtrl6 *self )
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

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;
#endif

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	result = dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("AUCC.DIVMCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVMCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVLR = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVLR));
	DriverCommon_DDIM_PRINT(("AUCC.AUCKOE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE));
	DriverCommon_DDIM_PRINT(("AUCC.DIVE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE));

	if (ch == 0){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU0SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU0SEL()));
	}
	else if (ch == 2){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU2SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU2SEL()));
	}
	else if (ch == 3){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU3SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU3SEL()));
	}
	else {
		;
	}

	DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AUCLK = 0x%x\n",Dd_Top_Get_CLKSEL8_AUCLK()));
	DriverCommon_DDIM_PRINT(("CHIPTOP.PLLCNT9.P10APLLDIV = 0x%x\n",IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl6_i2scmmn_test28( CtDdAudioCtrl6 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
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

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
		(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;
#endif

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	result = dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("AUCC.DIVMCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVMCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVLR = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVLR));
	DriverCommon_DDIM_PRINT(("AUCC.AUCKOE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE));
	DriverCommon_DDIM_PRINT(("AUCC.DIVE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE));

	if (ch == 0){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU0SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU0SEL()));
	}
	else if (ch == 2){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU2SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU2SEL()));
	}
	else if (ch == 3){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU3SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU3SEL()));
	}
	else {
		;
	}

	DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AUCLK = 0x%x\n",Dd_Top_Get_CLKSEL8_AUCLK()));
	DriverCommon_DDIM_PRINT(("CHIPTOP.PLLCNT9.P10APLLDIV = 0x%x\n",IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl6_i2scmmn_test29( CtDdAudioCtrl6 *self )
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
#endif

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	ctrlInfOut.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlInfOut.fifo_stages = E_DD_AUDIO_FIFO_STAGES_1;
	ctrlInfOut.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	dd_audio_start_loop_back(dd_audio_get(), ch);

#ifdef PC_DEBUG
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 1;
#endif

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	result = dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("AUCC.DIVMCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVMCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVLR = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVLR));
	DriverCommon_DDIM_PRINT(("AUCC.AUCKOE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE));
	DriverCommon_DDIM_PRINT(("AUCC.DIVE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE));

	if (ch == 0){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU0SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU0SEL()));
	}
	else if (ch == 2){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU2SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU2SEL()));
	}
	else if (ch == 3){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU3SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU3SEL()));
	}
	else {
		;
	}

	DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AUCLK = 0x%x\n",Dd_Top_Get_CLKSEL8_AUCLK()));
	DriverCommon_DDIM_PRINT(("CHIPTOP.PLLCNT9.P10APLLDIV = 0x%x\n",IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl6_i2scmmn_test30( CtDdAudioCtrl6 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.master_slave = E_DD_AUDIO_CLK_SLAVE;
	result = dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("AUCC.DIVMCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVMCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVLR = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVLR));
	DriverCommon_DDIM_PRINT(("AUCC.AUCKOE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE));
	DriverCommon_DDIM_PRINT(("AUCC.DIVE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE));

	if (ch == 0){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU0SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU0SEL()));
	}
	else if (ch == 2){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU2SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU2SEL()));
	}
	else if (ch == 3){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU3SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU3SEL()));
	}
	else {
		;
	}

	DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AUCLK = 0x%x\n",Dd_Top_Get_CLKSEL8_AUCLK()));
	DriverCommon_DDIM_PRINT(("CHIPTOP.PLLCNT9.P10APLLDIV = 0x%x\n",IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl6_i2scmmn_test31( CtDdAudioCtrl6 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.clk_div_enable = DdAudio_DISABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	result = dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("AUCC.DIVMCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVMCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVLR = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVLR));
	DriverCommon_DDIM_PRINT(("AUCC.AUCKOE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE));
	DriverCommon_DDIM_PRINT(("AUCC.DIVE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE));

	if (ch == 0){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU0SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU0SEL()));
	}
	else if (ch == 2){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU2SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU2SEL()));
	}
	else if (ch == 3){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU3SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU3SEL()));
	}
	else {
		;
	}

	DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AUCLK = 0x%x\n",Dd_Top_Get_CLKSEL8_AUCLK()));
	DriverCommon_DDIM_PRINT(("CHIPTOP.PLLCNT9.P10APLLDIV = 0x%x\n",IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl6_i2scmmn_test32( CtDdAudioCtrl6 *self )
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
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	result = dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("AUCC.DIVMCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVMCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVLR = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVLR));
	DriverCommon_DDIM_PRINT(("AUCC.AUCKOE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE));
	DriverCommon_DDIM_PRINT(("AUCC.DIVE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE));

	if (ch == 0){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU0SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU0SEL()));
	}
	else if (ch == 2){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU2SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU2SEL()));
	}
	else if (ch == 3){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU3SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU3SEL()));
	}
	else {
		;
	}

	DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AUCLK = 0x%x\n",Dd_Top_Get_CLKSEL8_AUCLK()));
	DriverCommon_DDIM_PRINT(("CHIPTOP.PLLCNT9.P10APLLDIV = 0x%x\n",IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl6_i2scmmn_test33( CtDdAudioCtrl6 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
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

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
		(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.clk_div_enable = DdAudio_ENABLE;
	result = dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("AUCC.DIVMCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVMCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVCK = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVCK));
	DriverCommon_DDIM_PRINT(("AUCC.DIVLR = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVLR));
	DriverCommon_DDIM_PRINT(("AUCC.AUCKOE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE));
	DriverCommon_DDIM_PRINT(("AUCC.DIVE = 0x%x\n",IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE));

	if (ch == 0){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU0SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU0SEL()));
	}
	else if (ch == 2){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU2SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU2SEL()));
	}
	else if (ch == 3){
		DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AU3SEL = 0x%x\n",Dd_Top_Get_CLKSEL8_AU3SEL()));
	}
	else {
		;
	}

	DriverCommon_DDIM_PRINT(("CHIPTOP.CLKSEL8.AUCLK = 0x%x\n",Dd_Top_Get_CLKSEL8_AUCLK()));
	DriverCommon_DDIM_PRINT(("CHIPTOP.PLLCNT9.P10APLLDIV = 0x%x\n",IO_CHIPTOP.PLLCNT9.bit.P10APLLDIV));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

CtDdAudioCtrl6 *ct_dd_audio_ctrl6_new(gpointer *temp, guint8 ch)
{
    CtDdAudioCtrl6 *self = CT_DD_AUDIO_CTRL6(g_object_new(CT_TYPE_DD_AUDIO_CTRL6, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}

