/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl3类
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

#include "../../../../MILB_API/Project/DeviceDriver/Peripheral/src/ddaudioctrl.h"
#include "../../../../MILB_API/Project/DeviceDriver/Peripheral/src/ddaudio.h"

G_DEFINE_TYPE(CtDdAudioCtrl3, ct_dd_audio_ctrl3, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_CTRL3_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_CTRL3, CtDdAudioCtrl3Private))

struct _CtDdAudioCtrl3Private
{
};

/*
 * DECLS
 */
static void ct_dd_audio_ctrl3_class_init(CtDdAudioCtrl3Class *klass);
static void ct_dd_audio_ctrl3_init(CtDdAudioCtrl3 *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);

/*
 * IMPL
 */
static void ct_dd_audio_ctrl3_class_init(CtDdAudioCtrl3Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioCtrl3Private));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_ctrl3_init(CtDdAudioCtrl3 *self)
{
	// CtDdAudioCtrl3 *self = CT_DD_AUDIO_CTRL3(object);
    // CtDdAudioCtrl3Private *priv = CT_DD_AUDIO_CTRL3_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl3_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl3_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_ctrl3_output_test19( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	AudioI2sCmmn i2sCommon;
	AudioCtrlCommon ctrlCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	dd_audio_init(dd_audio_get());

	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	}

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.mixPlay = 0;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.mixPlay = 0;
		(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	ioAudio.AUDIOIF[ch].AUMD.bit.STEREO = 1;
	ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.mixPlay = 0;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test20( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	AudioCtrlCommon ctrlCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.STEREO = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.mixPlay = 0;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.mixPlay = 1;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test21( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	AudioCtrlCommon ctrlCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	ioAudio.AUDIOIF[ch].AUMD.bit.STEREO = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.mixPlay = 0;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test22( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	AudioCtrlCommon ctrlCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_MONO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	ioAudio.AUDIOIF[ch].AUMD.bit.STEREO = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.mixPlay = 0;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test23( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	AudioCtrlCommon ctrlCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	dd_audio_init(dd_audio_get());

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	ioAudio.AUDIOIF[ch].AUMD.bit.STEREO = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.mixPlay = 1;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test24( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	dd_audio_init(dd_audio_get());

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bitShift = E_DD_AUDIO_BIT_SHIFT_1;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ioAudio.AUDIOIF[ch].AUDP.bit.AUODS = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test25( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	AudioI2sCmmn i2sCommon;
	AudioCtrlCommon ctrlCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	dd_audio_init(dd_audio_get());

	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	}

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
		(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	ioAudio.AUDIOIF[ch].AUDP.bit.AUODS = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test26( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	dd_audio_init(dd_audio_get());

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ioAudio.AUDIOIF[ch].AUDP.bit.AUODS = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bitShift = E_DD_AUDIO_BIT_SHIFT_1;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test27( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	dd_audio_init(dd_audio_get());

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ioAudio.AUDIOIF[ch].AUDP.bit.AUODS = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bitShift = E_DD_AUDIO_BIT_SHIFT_2;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test28( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	dd_audio_init(dd_audio_get());

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ioAudio.AUDIOIF[ch].AUDP.bit.AUODS = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_3;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test29( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	AudioCtrlCommon ctrlCommon;
	AudioI2sCmmn i2sCommon;
	AudioI2sOut i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	if (ch != 1){
		ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
	}
	else{
		ioAudio.AUDIOIF[0].AUOFST.word = 0xFFFFFFFF;
		ioAudio.AUDIOIF[1].AUOFST.word = 0xFFFFFFFF;
	}
#endif

	dd_audio_init(dd_audio_get());

	if ( ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	}

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bitOut = DdAudioI2s_BIT_16BIT;
	dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_16;
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	if ( ch != 1){
		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_16;
		ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
		(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(0);
#ifdef PC_DEBUG
	if ( ch != 1){
		ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	}
	else {
		ioAudio.AUDIOIF[0].AUCR.bit.AUOEF = 1;
		ioAudio.AUDIOIF[1].AUCR.bit.AUOEF = 1;
	}
#endif

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test30( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlCommon ctrlCommon;
	AudioCtrlIn ctrlInfIn;
	AudioCtrlOut ctrlInfOut;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	if (ch != 1){
		ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
	}
	else{
		ioAudio.AUDIOIF[0].AUOFST.word = 0xFFFFFFFF;
		ioAudio.AUDIOIF[1].AUOFST.word = 0xFFFFFFFF;
	}
#endif

	dd_audio_init(dd_audio_get());

	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	}

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bitIn = DdAudioI2s_BIT_16BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_MONO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInfIn);
	ctrlInfIn.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInfIn.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
	ctrlInfIn.ahbFormat = E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlInfIn.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInfIn);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
		ctrlCommon.channel = DdAudioCtrl_CHANNEL_MONO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInfIn);
		ctrlInfIn.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
		ctrlInfIn.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
		ctrlInfIn.ahbFormat = E_DD_AUDIO_AHB_FRMT_L_JUST;
		ctrlInfIn.bitShift = DdAudioCtrl_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInfIn);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(0);

#ifdef PC_DEBUG
	if ( ch != 1){
		ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
	}
	else {
		ioAudio.AUDIOIF[0].AUCR.bit.AUIEF = 1;
		ioAudio.AUDIOIF[1].AUCR.bit.AUIEF = 1;
	}
#endif

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	ctrlInfOut.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInfOut.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
	ctrlInfOut.ahbFormat = E_DD_AUDIO_AHB_FRMT_L_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	dd_audio_start_loop_back(dd_audio_get(), ch);

	ddim_user_custom_dly_tsk(0);
#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 1;
#endif

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);
	ctrlInfOut.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test31( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlCommon ctrlCommon;
	AudioCtrlOut ctrlInf;
	AudioI2sCmmn i2sCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	if (ch != 1){
		ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
	}
	else{
		ioAudio.AUDIOIF[0].AUOFST.word = 0xFFFFFFFF;
		ioAudio.AUDIOIF[1].AUOFST.word = 0xFFFFFFFF;
	}
#endif

	dd_audio_init(dd_audio_get());

	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	}

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_MONO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
		ctrlCommon.channel = DdAudioCtrl_CHANNEL_MONO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
		(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(0);
#ifdef PC_DEBUG
	if ( ch != 1){
		ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	}
	else {
		ioAudio.AUDIOIF[0].AUCR.bit.AUOEF = 1;
		ioAudio.AUDIOIF[1].AUCR.bit.AUOEF = 1;
	}
#endif

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl3_output_test32( CtDdAudioCtrl3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlCommon ctrlCommon;
	AudioCtrlIn ctrlInfIn;
	AudioCtrlOut ctrlInfOut;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

#ifdef PC_DEBUG
	if (ch != 1){
		ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
	}
	else{
		ioAudio.AUDIOIF[0].AUOFST.word = 0xFFFFFFFF;
		ioAudio.AUDIOIF[1].AUOFST.word = 0xFFFFFFFF;
	}
#endif

	dd_audio_init(dd_audio_get());

	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	}

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bitIn = DdAudioI2s_BIT_16BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_MONO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInfIn);
	ctrlInfIn.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlInfIn.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
	ctrlInfIn.ahbFormat = E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlInfIn.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInfIn);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
		ctrlCommon.channel = DdAudioCtrl_CHANNEL_MONO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_input(dd_audio_get(), 0, &ctrlInfIn);
		ctrlInfIn.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
		ctrlInfIn.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
		ctrlInfIn.ahbFormat = E_DD_AUDIO_AHB_FRMT_L_JUST;
		ctrlInfIn.bitShift = DdAudioCtrl_BIT_SHIFT_0;
		(void)dd_audio_ctrl_input(dd_audio_get(), 0, &ctrlInfIn);

		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(0);

#ifdef PC_DEBUG
	if ( ch != 1){
		ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
	}
	else {
		ioAudio.AUDIOIF[0].AUCR.bit.AUIEF = 1;
		ioAudio.AUDIOIF[1].AUCR.bit.AUIEF = 1;
	}
#endif

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	ctrlInfOut.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlInfOut.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInfOut.ahbFormat = E_DD_AUDIO_AHB_FRMT_L_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	dd_audio_start_loop_back(dd_audio_get(), ch);

	ddim_user_custom_dly_tsk(0);

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 1;
#endif

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);
	ctrlInfOut.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

CtDdAudioCtrl3 *ct_dd_audio_ctrl3_new(gpointer *temp, guint8 ch)
{
    CtDdAudioCtrl3 *self = CT_DD_AUDIO_CTRL3(g_object_new(CT_TYPE_DD_AUDIO_CTRL3, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}
