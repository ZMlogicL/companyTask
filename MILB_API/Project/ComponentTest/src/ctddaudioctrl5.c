/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl5类
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

G_DEFINE_TYPE(CtDdAudioCtrl5, ct_dd_audio_ctrl5, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_CTRL5_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_CTRL5, CtDdAudioCtrl5Private))

struct _CtDdAudioCtrl5Private
{
};

/*
 * DECLS
 */
static void ct_dd_audio_ctrl5_class_init(CtDdAudioCtrl5Class *klass);
static void ct_dd_audio_ctrl5_init(CtDdAudioCtrl5 *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);

/*
 * IMPL
 */
static void ct_dd_audio_ctrl5_class_init(CtDdAudioCtrl5Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioCtrl5Private));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_ctrl5_init(CtDdAudioCtrl5 *self)
{
	// CtDdAudioCtrl5 *self = CT_DD_AUDIO_CTRL5(object);
    // CtDdAudioCtrl5Private *priv = CT_DD_AUDIO_CTRL5_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl5_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl5_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_ctrl5_i2scmmn_test7( CtDdAudioCtrl5 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;

#ifdef PC_DEBUG
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_16;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
#endif

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_32;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_32;
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

void ct_dd_audio_ctrl5_i2scmmn_test8( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = DdAudio_DISABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_16;
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

void ct_dd_audio_ctrl5_i2scmmn_test9( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
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

void ct_dd_audio_ctrl5_i2scmmn_test10( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
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

void ct_dd_audio_ctrl5_i2scmmn_test11( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
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

void ct_dd_audio_ctrl5_i2scmmn_test12( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
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

void ct_dd_audio_ctrl5_i2scmmn_test13( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
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

void ct_dd_audio_ctrl5_i2scmmn_test14( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
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

void ct_dd_audio_ctrl5_i2scmmn_test15( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
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

void ct_dd_audio_ctrl5_i2scmmn_test16( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
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

void ct_dd_audio_ctrl5_i2scmmn_test17( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
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

void ct_dd_audio_ctrl5_i2scmmn_test18( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
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

void ct_dd_audio_ctrl5_i2scmmn_test19( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
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

void ct_dd_audio_ctrl5_i2scmmn_test20( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
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

void ct_dd_audio_ctrl5_i2scmmn_test21( CtDdAudioCtrl5 *self )
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
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
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

void ct_dd_audio_ctrl5_i2scmmn_test22( CtDdAudioCtrl5 *self )
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

CtDdAudioCtrl5* ct_dd_audio_ctrl5_new(gpointer *temp, guint8 ch)
{
    CtDdAudioCtrl5 *self = CT_DD_AUDIO_CTRL5(g_object_new(CT_TYPE_DD_AUDIO_CTRL5, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}

