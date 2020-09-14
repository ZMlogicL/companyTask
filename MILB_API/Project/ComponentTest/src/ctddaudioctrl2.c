/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioCtrl2类
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

#include "../../../../MILB_API/Project/DeviceDriver/Peripheral/src/ddaudioctrl.h"
#include "../../../../MILB_API/Project/DeviceDriver/Peripheral/src/ddaudio.h"

G_DEFINE_TYPE(CtDdAudioCtrl2, ct_dd_audio_ctrl2, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_CTRL2_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_CTRL2, CtDdAudioCtrl2Private))

struct _CtDdAudioCtrl2Private
{
};

/*
 * DECLS
 */
static void ct_dd_audio_ctrl2_class_init(CtDdAudioCtrl2Class *klass);
static void ct_dd_audio_ctrl2_init(CtDdAudioCtrl2 *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);

/*
 * IMPL
 */
static void ct_dd_audio_ctrl2_class_init(CtDdAudioCtrl2Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioCtrl2Private));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_ctrl2_init(CtDdAudioCtrl2 *self)
{
	// CtDdAudioCtrl2 *self = CT_DD_AUDIO_CTRL2(object);
    // CtDdAudioCtrl2Private *priv = CT_DD_AUDIO_CTRL2_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl2_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_ctrl2_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_ctrl2_output_test5( CtDdAudioCtrl2 *self )
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
	ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16 = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
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

void ct_dd_audio_ctrl2_output_test6( CtDdAudioCtrl2 *self )
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

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16 = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
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

void ct_dd_audio_ctrl2_output_test7( CtDdAudioCtrl2 *self )
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

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF = 1;
#endif
	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	ctrlInfOut.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlInfOut.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInfOut.ahbFormat = E_DD_AUDIO_AHB_FRMT_L_JUST;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	dd_audio_start_loop_back(dd_audio_get(), ch);

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 1;
	ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16 = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);
	ctrlInfOut.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInfOut);

	DriverCommon_DDIM_PRINT(("AUCR.AUORF=%d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUORF));
	DriverCommon_DDIM_PRINT(("AUMD.OSTG16=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16));
	DriverCommon_DDIM_PRINT(("AUMD.STEREO=%d\n", ioAudio.AUDIOIF[ch].AUMD.bit.STEREO));
	DriverCommon_DDIM_PRINT(("AUDP.AUODS=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODS));
	DriverCommon_DDIM_PRINT(("AUDP.AUODF=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AUODF));
	DriverCommon_DDIM_PRINT(("AUDP.AULRCP=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP));
	DriverCommon_DDIM_PRINT(("AUDP.MIXPLAY=%d\n", ioAudio.AUDIOIF[ch].AUDP.bit.MIXPLAY));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_ctrl2_output_test8( CtDdAudioCtrl2 *self )
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
	ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.OSTG16 = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
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

void ct_dd_audio_ctrl2_output_test9( CtDdAudioCtrl2 *self )
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
	ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 0;
	ioAudio.AUDIOIF[ch].AUDP.bit.AUODF = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
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

void ct_dd_audio_ctrl2_output_test10( CtDdAudioCtrl2 *self )
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
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
		(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 0;
	ioAudio.AUDIOIF[ch].AUDP.bit.AUODF = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
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

void ct_dd_audio_ctrl2_output_test11( CtDdAudioCtrl2 *self )
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
	ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 0;
	ioAudio.AUDIOIF[ch].AUDP.bit.AUODF = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.ahbFormat = E_DD_AUDIO_AHB_FRMT_L_JUST;
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

void ct_dd_audio_ctrl2_output_test12( CtDdAudioCtrl2 *self )
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

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.STEREO = 1;
	ioAudio.AUDIOIF[ch].AUCC.bit.AUCKOE = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.lrCopy = 1;
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

void ct_dd_audio_ctrl2_output_test13( CtDdAudioCtrl2 *self )
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

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.STEREO = 1;
	ioAudio.AUDIOIF[ch].AUCC.bit.AUCKOE = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.lrCopy = 0;
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

void ct_dd_audio_ctrl2_output_test14( CtDdAudioCtrl2 *self )
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
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_SLAVE;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_SLAVE;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
	}

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.STEREO = 1;
	ioAudio.AUDIOIF[ch].AUCC.bit.AUCKOE = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.lrCopy = 0;
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

void ct_dd_audio_ctrl2_output_test15( CtDdAudioCtrl2 *self )
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

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.STEREO = 1;
	ioAudio.AUDIOIF[ch].AUCC.bit.AUCKOE = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.lrCopy = 1;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.lrCopy = 0;
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

void ct_dd_audio_ctrl2_output_test16( CtDdAudioCtrl2 *self )
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
	ctrlInf.lrCopy = 0;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	if (ch != 1){
		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		dd_audio_get_ctrl_common(dd_audio_get(), 0, &ctrlCommon);
		ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
		dd_audio_ctrl_common(dd_audio_get(), 0, &ctrlCommon);

		dd_audio_get_ctrl_output(dd_audio_get(), 0, &ctrlInf);
		ctrlInf.lrCopy = 0;
		(void)dd_audio_ctrl_output(dd_audio_get(), 0, &ctrlInf);

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 1;
	ioAudio.AUDIOIF[ch].AUMD.bit.STEREO = 1;
	ioAudio.AUDIOIF[ch].AUCC.bit.AUCKOE = 1;
	ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.lrCopy = 0;
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

void ct_dd_audio_ctrl2_output_test17( CtDdAudioCtrl2 *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	AudioCtrlCommon ctrlCommon;
	AudioI2sCmmn i2sCommon;
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

	ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	ioAudio.AUDIOIF[ch].AUMD.bit.STEREO = 1;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.lrCopy = 0;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ioAudio.AUDIOIF[ch].AUDP.bit.AULRCP = 0;

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.lrCopy = 1;
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

void ct_dd_audio_ctrl2_output_test18( CtDdAudioCtrl2 *self )
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

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.mixPlay = 1;
	result = dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ioAudio.AUDIOIF[ch].AUDP.bit.MIXPLAY = 1;

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

CtDdAudioCtrl2 *ct_dd_audio_ctrl2_new(gpointer *temp, guint8 ch)
{
    CtDdAudioCtrl2 *self = CT_DD_AUDIO_CTRL2(g_object_new(CT_TYPE_DD_AUDIO_CTRL2, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}
