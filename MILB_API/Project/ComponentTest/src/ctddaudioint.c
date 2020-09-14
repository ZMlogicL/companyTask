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

#include "../../../../MILB_API/Project/DeviceDriver/Peripheral/src/ddaudioctrl.h"
#include "../../../../MILB_API/Project/DeviceDriver/Peripheral/src/ddaudio.h"
#include "../../../../milb_api_usercustom/src/ddimusercustom.h"

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
	guint8 ch = self->ch;
#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test2(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	AudioCtrlIn ctrlInf;
	AudioCtrlCommon ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bitIn = DdAudioI2s_BIT_24BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	dd_audio_start_input(dd_audio_get(), ch);
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF));
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test3(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif
	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test4(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	AudioCtrlIn ctrlInf;
	AudioCtrlCommon ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));
#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	DdimUserCustom* userCustom = ddim_user_custom_new();
	DDIM_User_DisableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch));
	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

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
	i2sIn.bitIn = DdAudioI2s_BIT_24BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	if (ch != 1){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(1);

	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF));
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DDIM_User_EnableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch), 14);
	g_object_unref(userCustom);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test5(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	AudioCtrlIn ctrlInf;
	AudioCtrlCommon ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bitIn = DdAudioI2s_BIT_24BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	dd_audio_start_input(dd_audio_get(), ch);
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF));
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test6(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test7(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	AudioCtrlIn ctrlInf;
	AudioCtrlCommon ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	DdimUserCustom* userCustom = ddim_user_custom_new();
	DDIM_User_DisableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch));
	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);

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
	i2sIn.bitIn = DdAudioI2s_BIT_24BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	if (ch != 0){
		dd_audio_start_input(dd_audio_get(), ch);
	}
	else {
		dd_audio_start_input(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(1);

	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF));
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DDIM_User_EnableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch), 14);
	g_object_unref(userCustom);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test8(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	AudioCtrlIn ctrlInf;
	AudioCtrlCommon ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	i2sIn.bitIn = DdAudioI2s_BIT_24BIT;
	dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	dd_audio_start_input(dd_audio_get(), ch);
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF));
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test9(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test10(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	AudioCtrlIn ctrlInf;
	AudioCtrlCommon ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif
	DdimUserCustom* userCustom = ddim_user_custom_new();
	DDIM_User_DisableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch));
	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_input(dd_audio_get(), ch, &ctrlInf);
	if (ch != 1){
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
		dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
		i2sIn.bitIn = DdAudioI2s_BIT_24BIT;
		dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
	}
	else {
		dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
		i2sCommon.clkDivEnable = DdAudio_ENABLE;
		dd_audio_ctrl_i2s_cmmn(dd_audio_get(), 0, &i2sCommon);
		dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);
		i2sIn.bitIn = DdAudioI2s_BIT_24BIT;
		dd_audio_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	}

	dd_audio_start_input(dd_audio_get(), ch);
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUIEF = %d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF));
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	DDIM_User_EnableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch), 14);
	g_object_unref(userCustom);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test11(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test12(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test13(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	DdimUserCustom* userCustom = ddim_user_custom_new();
	DDIM_User_DisableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch));
	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DDIM_User_EnableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch), 14);
	g_object_unref(userCustom);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test14(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test15(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test16(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	DdimUserCustom* userCustom = ddim_user_custom_new();
	DDIM_User_DisableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch));
	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
//	printf("EINTOE set\n");
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DDIM_User_EnableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch), 14);
	g_object_unref(userCustom);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test17(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	AudioI2sCmmn i2sCommon;
	AudioI2sOut i2sOut;
	AudioCtrlOut ctrlInf;
	AudioCtrlCommon ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));
#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
	ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif
	dd_audio_init(dd_audio_get());
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	ctrlInf.lrCopy = 0;
	ctrlInf.mixPlay = 0;
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	i2sCommon.masterSlave = E_DD_AUDIO_CLK_MASTER;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);
	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bitOut = DdAudioI2s_BIT_24BIT;
	i2sOut.modeOut = E_DD_AUDIO_MODE_I2S;
	i2sOut.fs = DdAudioI2s_FS_64FS;
	dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	dd_audio_start_output(dd_audio_get(), ch);
	ddim_user_custom_dly_tsk(1);
	DriverCommon_DDIM_PRINT(("AUOEF = %d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF));
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 1;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test18(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());
	ioAudio.AUDIOIF[ch].AUODLR = 1;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 0;
	dd_audio_int_handler(dd_audio_get(), ch);
	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_int_handler_test19(CtDdAudioInt *self)
{
	guint8 ch = self->ch;
	AudioI2sCmmn i2sCommon;
	AudioI2sOut i2sOut;
	AudioCtrlOut ctrlInf;
	AudioCtrlCommon ctrlCommon;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
	ioAudio.AUDIOIF[ch].AUOFST.word = 0xFFFFFFFF;
#endif

	DdimUserCustom* userCustom = ddim_user_custom_new();
	DDIM_User_DisableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch));
	dd_audio_init(dd_audio_get());
	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_16;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.format = DdAudioCtrl_DATA_REG_FRMT_R_JUST;
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_1;
	ctrlInf.ahbFormat = DdAudioCtrl_AHB_FRMT_R_JUST;
	ctrlInf.lrCopy = 0;
	ctrlInf.mixPlay = 0;
	ctrlInf.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

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

	dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);
	i2sOut.bitOut = DdAudioI2s_BIT_24BIT;
	i2sOut.modeOut = E_DD_AUDIO_MODE_I2S;
	i2sOut.fs = DdAudioI2s_FS_64FS;
	dd_audio_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	if (ch != 1){
		ioAudio.AUDIOIF[ch].AUODLR = 1;

		dd_audio_start_output(dd_audio_get(), ch);
	}
	else {
		ioAudio.AUDIOIF[0].AUODLR = 1;
		ioAudio.AUDIOIF[1].AUODLR = 1;

		dd_audio_start_output(dd_audio_get(), DdAudio_IF_CH0_CH1);
	}

	ddim_user_custom_dly_tsk(1);

	DriverCommon_DDIM_PRINT(("AUOEF = %d\n", ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF));
	ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTI = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.IROF = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.EINTO = 0;
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 1;
	ioAudio.AUDIOIF[ch].AUST.bit.ORUF = 1;
	dd_audio_int_handler(dd_audio_get(), ch);
	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;
	DDIM_User_EnableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch), 14);
	g_object_unref(userCustom);
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

