/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl4类
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
#include "ctddaudioctrl4.h"

G_DEFINE_TYPE(CtDdAudioCtrl4, ct_dd_audio_ctrl4, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_CTRL4_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_CTRL4, CtDdAudioCtrl4Private))

struct _CtDdAudioCtrl4Private
{
};

/*
 * DECLS
 */
static void ct_dd_audio_ctrl4_class_init(CtDdAudioCtrl4Class *klass);
static void ct_dd_audio_ctrl4_init(CtDdAudioCtrl4 *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);

/*
 * IMPL
 */
static void ct_dd_audio_ctrl4_class_init(CtDdAudioCtrl4Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioCtrl4Private));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_ctrl4_init(CtDdAudioCtrl4 *self)
{
	// CtDdAudioCtrl4 *self = CT_DD_AUDIO_CTRL4(object);
    // CtDdAudioCtrl4Private *priv = CT_DD_AUDIO_CTRL4_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl4_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl4_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_ctrl4_output_test33( CtDdAudioCtrl4 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	if (ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
	}
	else{
		IO_AUDIO.AUDIOIF[0].AUOFST.word = 0xFFFFFFFF;
		IO_AUDIO.AUDIOIF[1].AUOFST.word = 0xFFFFFFFF;
	}
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

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
		(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(0);
#ifdef PC_DEBUG
	if ( ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	}
	else {
		IO_AUDIO.AUDIOIF[0].AUCR.bit.AUOEF = 1;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.AUOEF = 1;
	}
#endif

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_output_test34( CtDdAudioCtrl4 *self )
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

#ifdef PC_DEBUG
	if (ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
	}
	else{
		IO_AUDIO.AUDIOIF[0].AUOFST.word = 0xFFFFFFFF;
		IO_AUDIO.AUDIOIF[1].AUOFST.word = 0xFFFFFFFF;
	}
#endif

	dd_audio_init(dd_audio_get());

	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.master_slave = E_DD_AUDIO_CLK_SLAVE;
		i2sCommon.clk_div_enable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.master_slave = E_DD_AUDIO_CLK_SLAVE;
		i2sCommon.clk_div_enable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	}

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO = 1;
	IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE = 0;
	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AULRCP = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.lr_copy = 1;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_output_test35( CtDdAudioCtrl4 *self )
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

#ifdef PC_DEBUG
	if (ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
	}
	else{
		IO_AUDIO.AUDIOIF[0].AUOFST.word = 0xFFFFFFFF;
		IO_AUDIO.AUDIOIF[1].AUOFST.word = 0xFFFFFFFF;
	}
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

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.lr_copy = 0;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.lr_copy = 0;
		(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(0);

#ifdef PC_DEBUG
	if ( ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	}
	else {
		IO_AUDIO.AUDIOIF[0].AUCR.bit.AUOEF = 1;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.AUOEF = 1;
	}
#endif

	IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO = 1;
	IO_AUDIO.AUDIOIF[ch].AUCC.bit.AUCKOE = 1;
	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AULRCP = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.lr_copy = 0;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_output_test36( CtDdAudioCtrl4 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	if (ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
	}
	else{
		IO_AUDIO.AUDIOIF[0].AUOFST.word = 0xFFFFFFFF;
		IO_AUDIO.AUDIOIF[1].AUOFST.word = 0xFFFFFFFF;
	}
#endif

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
	ctrlInf.mix_play = 0;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.mix_play = 0;
		(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(0);

#ifdef PC_DEBUG
	if ( ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	}
	else {
		IO_AUDIO.AUDIOIF[0].AUCR.bit.AUOEF = 1;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.AUOEF = 1;
	}
#endif

	IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO = 1;
	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AULRCP = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.mix_play = 1;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_output_test37( CtDdAudioCtrl4 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	if (ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
	}
	else{
		IO_AUDIO.AUDIOIF[0].AUOFST.word = 0xFFFFFFFF;
		IO_AUDIO.AUDIOIF[1].AUOFST.word = 0xFFFFFFFF;
	}
#endif

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_MONO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	IO_AUDIO.AUDIOIF[ch].AUMD.bit.STEREO = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.mix_play = 1;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_output_test38( CtDdAudioCtrl4 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	if (ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
	}
	else{
		IO_AUDIO.AUDIOIF[0].AUOFST.word = 0xFFFFFFFF;
		IO_AUDIO.AUDIOIF[1].AUOFST.word = 0xFFFFFFFF;
	}
#endif

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

	ddim_user_custom_dly_tsk(0);

#ifdef PC_DEBUG
	if ( ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	}
	else {
		IO_AUDIO.AUDIOIF[0].AUCR.bit.AUOEF = 1;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.AUOEF = 1;
	}
#endif

	IO_AUDIO.AUDIOIF[ch].AUDP.bit.AUODS = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bit_shift = E_DD_AUDIO_BIT_SHIFT_1;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_output_test39( CtDdAudioCtrl4 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = (E_DD_AUDIO_DATA_REG_FRMT)2;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_output_test40( CtDdAudioCtrl4 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifo_stages = (E_DD_AUDIO_FIFO_STAGES)2;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_output_test41( CtDdAudioCtrl4 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.ahb_format = (E_DD_AUDIO_AHB_FRMT)2;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_output_test42( CtDdAudioCtrl4 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.lr_copy = 2;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_output_test43( CtDdAudioCtrl4 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.mix_play = 2;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_output_test44( CtDdAudioCtrl4 *self )
{
	const guint8 ch = self->ch;
	T_DD_AUDIO_CTRL_OUT ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bit_shift = (E_DD_AUDIO_BIT_SHIFT)4;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_output_test45( CtDdAudioCtrl4 *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_ctrl_output(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl4_i2scmmn_test1( CtDdAudioCtrl4 *self )
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
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_AUMCLKI;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_AUMCLKI;
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

void ct_dd_audio_ctrl4_i2scmmn_test2( CtDdAudioCtrl4 *self )
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

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_AUMCLKI;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
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

void ct_dd_audio_ctrl4_i2scmmn_test3( CtDdAudioCtrl4 *self )
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

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_22_5792;
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

void ct_dd_audio_ctrl4_i2scmmn_test4( CtDdAudioCtrl4 *self )
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

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
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

void ct_dd_audio_ctrl4_i2scmmn_test5( CtDdAudioCtrl4 *self )
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

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_36_864;
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

void ct_dd_audio_ctrl4_i2scmmn_test6( CtDdAudioCtrl4 *self )
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

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_AUMCLKI;
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

CtDdAudioCtrl4* ct_dd_audio_ctrl4_new(gpointer *temp, guint8 ch)
{
    CtDdAudioCtrl4 *self = CT_DD_AUDIO_CTRL4(g_object_new(CT_TYPE_DD_AUDIO_CTRL4, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}

