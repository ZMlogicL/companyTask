/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioSet3类
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
#include "ctddaudiostop.h"
#include "ctddaudioset.h"
#include "ctddaudioset1.h"
#include "ctddaudioset2.h"
#include "ctddaudioset3.h"

#include "../../../../MILB_API/Project/DeviceDriver/Peripheral/src/ddaudioctrl.h"
#include "../../../../MILB_API/Project/DeviceDriver/Peripheral/src/ddaudio.h"
#include "../../../../milb_api_usercustom/src/ddimusercustom.h"

G_DEFINE_TYPE(CtDdAudioSet3, ct_dd_audio_set3, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_SET3_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_SET3, CtDdAudioSet3Private))

struct _CtDdAudioSet3Private
{
};

/*
 * DECLS
 */
static void ct_dd_audio_set3_class_init(CtDdAudioSet3Class *klass);
static void ct_dd_audio_set3_init(CtDdAudioSet3 *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
/*
 * IMPL
 */
static void ct_dd_audio_set3_class_init(CtDdAudioSet3Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioSet3Private));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_set3_init(CtDdAudioSet3 *self)
{
	// CtDdAudioSet3 *self = CT_DD_AUDIO_SET3(object);
    // CtDdAudioSet3Private *priv = CT_DD_AUDIO_SET3_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_set3_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_set3_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_set3_enable_output_intr_test10( CtDdAudioSet3 *self )
{
	guint8 ch = self->ch;
	AudioCtrlCommon ctrlCommon;
	AudioCtrlOut ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));
	DdimUserCustom* userCustom = ddim_user_custom_new();
	DDIM_User_DisableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_8;
	dd_audio_ctrl_common(dd_audio_get(), ch, &ctrlCommon);

	dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);
	ctrlInf.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
	(void)dd_audio_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 1;

	result = dd_audio_set_enable_output_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUCR.INTOE=0x%x\n", ioAudio.AUDIOIF[ch].AUCR.bit.INTOE));
	DriverCommon_DDIM_PRINT(("AUST.EINTOE=0x%x\n", ioAudio.AUDIOIF[ch].AUST.bit.EINTOE));

	DDIM_User_EnableInt(userCustom, (DdimUserCustom_INTID)(DdGic_INTID_AUDIO_IF_CH0_INT + ch), 14);
	g_object_unref(userCustom);
	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set3_enable_output_intr_test11( CtDdAudioSet3 *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_enable_output_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set3_enable_output_intr_test12( CtDdAudioSet3 *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_enable_output_intr(dd_audio_get(), ch, 2, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set3_enable_in_over_flow_intr_test1( CtDdAudioSet3 *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	ioAudio.AUDIOIF[ch].AUST.word = 0;		// for PC-Sim

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 0;

	result = dd_audio_set_enable_in_over_flow_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUST%d.OFIE=0x%x\n", ch, ioAudio.AUDIOIF[ch].AUST.bit.OFIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set3_enable_in_over_flow_intr_test2( CtDdAudioSet3 *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUST.word = 0;		// for PC-Sim
#endif

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	ioAudio.AUDIOIF[ch].AUST.bit.OFIE = 1;

	result = dd_audio_set_enable_in_over_flow_intr(dd_audio_get(), ch, DdAudio_DISABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUST%d.OFIE=0x%x\n", ch, ioAudio.AUDIOIF[ch].AUST.bit.OFIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set3_enable_in_over_flow_intr_test3( CtDdAudioSet3 *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_enable_in_over_flow_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set3_enable_in_over_flow_intr_test4( CtDdAudioSet3 *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_enable_in_over_flow_intr(dd_audio_get(), ch, 2, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set3_enable_out_under_flow_intr_test1( CtDdAudioSet3 *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUST.word = 0;		// for PC-Sim
#endif

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 0;

	result = dd_audio_set_enable_out_under_flow_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUST%d.UFIE=0x%x\n", ch, ioAudio.AUDIOIF[ch].AUST.bit.UFIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set3_enable_out_under_flow_intr_test2( CtDdAudioSet3 *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioAudio.AUDIOIF[ch].AUST.word = 0;		// for PC-Sim
#endif

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	ioAudio.AUDIOIF[ch].AUST.bit.UFIE = 1;

	result = dd_audio_set_enable_out_under_flow_intr(dd_audio_get(), ch, DdAudio_DISABLE, NULL);

	DriverCommon_DDIM_PRINT(("AUST%d.UFIE=0x%x\n", ch, ioAudio.AUDIOIF[ch].AUST.bit.UFIE));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set3_enable_out_under_flow_intr_test3( CtDdAudioSet3 *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_enable_out_under_flow_intr(dd_audio_get(), ch, DdAudio_ENABLE, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_set3_enable_out_under_flow_intr_test4( CtDdAudioSet3 *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_set_enable_out_under_flow_intr(dd_audio_get(), ch, 2, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}


CtDdAudioSet3 *ct_dd_audio_set3_new(gpointer *temp, guint8 ch)
{
    CtDdAudioSet3 *self = CT_DD_AUDIO_SET3(g_object_new(CT_TYPE_DD_AUDIO_SET3, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}
