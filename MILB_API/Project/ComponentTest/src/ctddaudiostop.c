/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioStop类
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

G_DEFINE_TYPE(CtDdAudioStop, ct_dd_audio_stop, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_STOP_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_STOP, CtDdAudioStopPrivate))

struct _CtDdAudioStopPrivate
{
};

/*
 * DECLS
 */
static void ct_dd_audio_stop_class_init(CtDdAudioStopClass *klass);
static void ct_dd_audio_stop_init(CtDdAudioStop *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
/*
 * IMPL
 */
static void ct_dd_audio_stop_class_init(CtDdAudioStopClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioStopPrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_stop_init(CtDdAudioStop *self)
{
	// CtDdAudioStop *self = CT_DD_AUDIO_STOP(object);
    // CtDdAudioStopPrivate *priv = CT_DD_AUDIO_STOP_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_stop_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_stop_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_stop_input_test( CtDdAudioStop *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_stop_input(dd_audio_get(), ch);

#ifdef PC_DEBUG
	if ( ch == DdAudio_IF_CH0_CH1){
		IO_AUDIO.AUDIOIF[0].AUCR.bit.AUIEF = 0;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.AUIEF = 0;
	}
	else if ( ch == D_DD_AUDIO_IF_CH4_CH5){
		IO_AUDIO.AUDIOIF[4].AUCR.bit.AUIEF = 0;
		IO_AUDIO.AUDIOIF[5].AUCR.bit.AUIEF = 0;
	}
	else {
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
	}
#endif

	if ( ch == DdAudio_IF_CH0_CH1){
		DriverCommon_DDIM_PRINT(("AUCR0.AUIEF=0x%x\n", IO_AUDIO.AUDIOIF[0].AUCR.bit.AUIEF));
		DriverCommon_DDIM_PRINT(("AUCR0.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[0].AUCR.bit.INTIE));
		DriverCommon_DDIM_PRINT(("AUST0.IROF=0x%x\n", IO_AUDIO.AUDIOIF[0].AUST.bit.OFIE));
		DriverCommon_DDIM_PRINT(("AUST0.OFIE=0x%x\n", IO_AUDIO.AUDIOIF[0].AUST.bit.OFIE));
		DriverCommon_DDIM_PRINT(("AUST0.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[0].AUST.bit.EINTIE));

		DriverCommon_DDIM_PRINT(("AUCR1.AUIEF=0x%x\n", IO_AUDIO.AUDIOIF[1].AUCR.bit.AUIEF));
		DriverCommon_DDIM_PRINT(("AUCR1.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[1].AUCR.bit.INTIE));
		DriverCommon_DDIM_PRINT(("AUST1.IROF=0x%x\n", IO_AUDIO.AUDIOIF[1].AUST.bit.OFIE));
		DriverCommon_DDIM_PRINT(("AUST1.OFIE=0x%x\n", IO_AUDIO.AUDIOIF[1].AUST.bit.OFIE));
		DriverCommon_DDIM_PRINT(("AUST1.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[1].AUST.bit.EINTIE));
	}
	else if ( ch == D_DD_AUDIO_IF_CH4_CH5){
		DriverCommon_DDIM_PRINT(("AUCR4.AUIEF=0x%x\n", IO_AUDIO.AUDIOIF[4].AUCR.bit.AUIEF));
		DriverCommon_DDIM_PRINT(("AUCR4.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[4].AUCR.bit.INTIE));
		DriverCommon_DDIM_PRINT(("AUST4.IROF=0x%x\n", IO_AUDIO.AUDIOIF[4].AUST.bit.OFIE));
		DriverCommon_DDIM_PRINT(("AUST4.OFIE=0x%x\n", IO_AUDIO.AUDIOIF[4].AUST.bit.OFIE));
		DriverCommon_DDIM_PRINT(("AUST4.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[4].AUST.bit.EINTIE));

		DriverCommon_DDIM_PRINT(("AUCR5.AUIEF=0x%x\n", IO_AUDIO.AUDIOIF[5].AUCR.bit.AUIEF));
		DriverCommon_DDIM_PRINT(("AUCR5.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[5].AUCR.bit.INTIE));
		DriverCommon_DDIM_PRINT(("AUST5.IROF=0x%x\n", IO_AUDIO.AUDIOIF[5].AUST.bit.OFIE));
		DriverCommon_DDIM_PRINT(("AUST5.OFIE=0x%x\n", IO_AUDIO.AUDIOIF[5].AUST.bit.OFIE));
		DriverCommon_DDIM_PRINT(("AUST5.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[5].AUST.bit.EINTIE));
	}
	else {
		DriverCommon_DDIM_PRINT(("AUCR.AUIEF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF));
		DriverCommon_DDIM_PRINT(("AUCR.INTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE));
		DriverCommon_DDIM_PRINT(("AUST.IROF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE));
		DriverCommon_DDIM_PRINT(("AUST.OFIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE));
		DriverCommon_DDIM_PRINT(("AUST.EINTIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE));
	}

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_stop_output_test( CtDdAudioStop *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_stop_output(dd_audio_get(), ch);

#ifdef PC_DEBUG
	if ( ch == DdAudio_IF_CH0_CH1){
		IO_AUDIO.AUDIOIF[0].AUCR.bit.AUOEF = 0;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.AUOEF = 0;
	}
	else {
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
	}
#endif

	if ( ch == DdAudio_IF_CH0_CH1){
		DriverCommon_DDIM_PRINT(("AUCR0.AUOEF=0x%x\n", IO_AUDIO.AUDIOIF[0].AUCR.bit.AUOEF));
		DriverCommon_DDIM_PRINT(("AUCR0.INTOE=0x%x\n", IO_AUDIO.AUDIOIF[0].AUCR.bit.INTOE));
		DriverCommon_DDIM_PRINT(("AUST0.EINTOE=0x%x\n", IO_AUDIO.AUDIOIF[0].AUST.bit.EINTOE));
		DriverCommon_DDIM_PRINT(("AUST0.UFIE=0x%x\n", IO_AUDIO.AUDIOIF[0].AUST.bit.UFIE));

		DriverCommon_DDIM_PRINT(("AUCR1.AUOEF=0x%x\n", IO_AUDIO.AUDIOIF[1].AUCR.bit.AUOEF));
		DriverCommon_DDIM_PRINT(("AUCR1.INTOE=0x%x\n", IO_AUDIO.AUDIOIF[1].AUCR.bit.INTOE));
		DriverCommon_DDIM_PRINT(("AUST1.EINTOE=0x%x\n", IO_AUDIO.AUDIOIF[1].AUST.bit.EINTOE));
		DriverCommon_DDIM_PRINT(("AUST1.UFIE=0x%x\n", IO_AUDIO.AUDIOIF[1].AUST.bit.UFIE));
	}
	else {
		DriverCommon_DDIM_PRINT(("AUCR.AUOEF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF));
		DriverCommon_DDIM_PRINT(("AUCR.INTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE));
		DriverCommon_DDIM_PRINT(("AUST.EINTOE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE));
		DriverCommon_DDIM_PRINT(("AUST.UFIE=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE));
	}

	DriverCommon_DDIM_PRINT(("AUOE.AUOE=0x%x\n", (unsigned int)IO_AUDIO.AUDIOIF_CTRL.AUIOE.word));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_stop_loop_back_test( CtDdAudioStop *self )
{
	const guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_stop_loop_back(dd_audio_get(), ch);

	ddim_user_custom_dly_tsk(0);

	if (ch == DdAudio_IF_CH0_CH1){

#ifdef PC_DEBUG
		IO_AUDIO.AUDIOIF[0].AUMD.bit.LBF = 0;
		IO_AUDIO.AUDIOIF[1].AUMD.bit.LBF = 0;
#endif
		DriverCommon_DDIM_PRINT(("AUMD0.LBF=0x%x\n", IO_AUDIO.AUDIOIF[0].AUMD.bit.LBF));
		DriverCommon_DDIM_PRINT(("AUMD1.LBF=0x%x\n", IO_AUDIO.AUDIOIF[1].AUMD.bit.LBF));
	}
	else {

#ifdef PC_DEBUG
		IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;
#endif
		DriverCommon_DDIM_PRINT(("AUMD.LBF=0x%x\n", IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF));
	}

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}


CtDdAudioStop *ct_dd_audio_stop_new(gpointer *temp, guint8 ch)
{
    CtDdAudioStop *self = CT_DD_AUDIO_STOP(g_object_new(CT_TYPE_DD_AUDIO_STOP, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}

