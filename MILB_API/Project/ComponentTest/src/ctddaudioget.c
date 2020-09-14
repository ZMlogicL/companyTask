/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :luhongyin
*@brief               :CtDdAudioGet类
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

#include "../../../../MILB_API/Project/DeviceDriver/Peripheral/src/ddaudioctrl.h"
#include "../../../../MILB_API/Project/DeviceDriver/Peripheral/src/ddaudio.h"

G_DEFINE_TYPE(CtDdAudioGet, ct_dd_audio_get, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_GET_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO_GET, CtDdAudioGetPrivate))

struct _CtDdAudioGetPrivate
{
};

/*
 * DECLS
 */
static void ct_dd_audio_get_class_init(CtDdAudioGetClass *klass);
static void ct_dd_audio_get_init(CtDdAudioGet *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
/*
 * IMPL
 */
static void ct_dd_audio_get_class_init(CtDdAudioGetClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioGetPrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_get_init(CtDdAudioGet *self)
{
	// CtDdAudioGet *self = CT_DD_AUDIO_GET(object);
    // CtDdAudioGetPrivate *priv = CT_DD_AUDIO_GET_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_get_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_get_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
void ct_dd_audio_get_ctrl_common_test1( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	gint32 result;
	AudioCtrlCommon ctrlInf;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	result = dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("fifoUsage=0x%x\n", ctrlInf.fifoUsage));
	DriverCommon_DDIM_PRINT(("channel=0x%x\n", ctrlInf.channel));
	DriverCommon_DDIM_PRINT(("<%s> End. result= 0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_common_test2( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_get_ctrl_common(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result= 0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_input_test1( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	AudioCtrlIn ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	result = dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("format=0x%x\n", ctrlInf.format));
	DriverCommon_DDIM_PRINT(("fifoStages=0x%x\n", ctrlInf.fifoStages));
	DriverCommon_DDIM_PRINT(("ahbFormat=0x%x\n", ctrlInf.ahbFormat));
	DriverCommon_DDIM_PRINT(("bitShift=0x%x\n", ctrlInf.bitShift));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_input_test2( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_get_ctrl_input(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_output_test1( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	AudioCtrlOut ctrlInf;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	result = dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlInf);

	DriverCommon_DDIM_PRINT(("format=0x%x\n", ctrlInf.format));
	DriverCommon_DDIM_PRINT(("fifoStages=0x%x\n", ctrlInf.fifoStages));
	DriverCommon_DDIM_PRINT(("ahbFormat=0x%x\n", ctrlInf.ahbFormat));
	DriverCommon_DDIM_PRINT(("lrCopy=0x%x\n", ctrlInf.lrCopy));
	DriverCommon_DDIM_PRINT(("mixPlay=0x%x\n", ctrlInf.mixPlay));
	DriverCommon_DDIM_PRINT(("bitShift=0x%x\n", ctrlInf.bitShift));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_output_test2( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_get_ctrl_output(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_i2scmmn_test1( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	AudioI2sCmmn i2sCommon;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	result = dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("aumclki=0x%x\n", i2sCommon.aumclki));
	DriverCommon_DDIM_PRINT(("divAumclko=0x%x\n", i2sCommon.divAumclko));
	DriverCommon_DDIM_PRINT(("divAuclk=0x%x\n", i2sCommon.divAuclk));
	DriverCommon_DDIM_PRINT(("divLrclk=0x%x\n", i2sCommon.divLrclk));
	DriverCommon_DDIM_PRINT(("clkDivEnable=0x%x\n", i2sCommon.clkDivEnable));
	DriverCommon_DDIM_PRINT(("masterSlave=0x%x\n", i2sCommon.masterSlave));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_i2scmmn_test2( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_i2sin_test1( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	AudioI2sIn i2sIn;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	result = dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

	DriverCommon_DDIM_PRINT(("modeIn=0x%x\n", i2sIn.modeIn));
	DriverCommon_DDIM_PRINT(("bitIn=0x%x\n", i2sIn.bitIn));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_i2sin_test2( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_i2sout_test1( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	AudioI2sOut i2sOut;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	result = dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

	DriverCommon_DDIM_PRINT(("modeOut=0x%x\n", i2sOut.modeOut));
	DriverCommon_DDIM_PRINT(("bitOut=0x%x\n", i2sOut.bitOut));
	DriverCommon_DDIM_PRINT(("fs=0x%x\n", i2sOut.fs));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_i2sout_test2( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_dmain_test1( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	AudioDma dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	result = dd_audio_get_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("dma2Ch=0x%x\n", dmaSetting.dma2Ch));
	DriverCommon_DDIM_PRINT(("dmaTrnsfCnt=0x%x\n", dmaSetting.dmaTrnsfCnt));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_dmain_test2( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_get_ctrl_dma_in(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_dmaout_test1( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	AudioDma dmaSetting;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	CtDdAudio* regInit = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_reg_init(regInit);
    k_object_unref(regInit);

	dd_audio_init(dd_audio_get());

	result = dd_audio_get_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

	DriverCommon_DDIM_PRINT(("dma2Ch=0x%x\n", dmaSetting.dma2Ch));
	DriverCommon_DDIM_PRINT(("dmaTrnsfCnt=0x%x\n", dmaSetting.dmaTrnsfCnt));

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_ctrl_dmaout_test2( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	gint32 result;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_get_ctrl_dma_out(dd_audio_get(), ch, NULL);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_get_status_input_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("dd_audio_get_status_input(dd_audio_get(), %d) = %d\n", 
		ch, (int)dd_audio_get_status_input(dd_audio_get(), ch)));
	DriverCommon_DDIM_PRINT(("<%s> End.\n", __FUNCTION__));
}

void ct_dd_audio_get_status_output_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("dd_audio_get_status_output(dd_audio_get(), %d) = %d\n", 
		ch, (int)dd_audio_get_status_output(dd_audio_get(), ch)));
	DriverCommon_DDIM_PRINT(("<%s> End.\n", __FUNCTION__));
}

void ct_dd_audio_get_status_loop_back_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_reset(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("dd_audio_get_status_loop_back(dd_audio_get(), (%d) = %d\n", 
		ch, (int)dd_audio_get_status_loop_back(dd_audio_get(), (ch)));
	DriverCommon_DDIM_PRINT(("<%s> End.\n", __FUNCTION__));
}

void ct_dd_audio_get_in_dmasample_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	ioAudio.AUDIOIF[ch].AUDMISAMPLE.word = 0;		// for PC-Sim
	dd_audio_reset(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(( "DMISPL=0x%x\n", dd_audio_get_in_dma_sample(dd_audio_get(), ch)));

	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_get_out_dmasample_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	ioAudio.AUDIOIF[ch].AUDMOSAMPLE.word = 0;		// for PC-Sim

	dd_audio_reset(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(( "DMOSPL=0x%x\n", dd_audio_get_out_dma_sample(dd_audio_get(), (ch)));

	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_get_addr_reg_auidlr_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DriverCommon_DDIM_PRINT(("AUIDLR%d addr=0x%lx\n", 
		ch, (long unsigned int)dd_audio_get_addr_reg_auidlr(dd_audio_get(), ch)));

	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_get_addr_reg_auodlr_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DriverCommon_DDIM_PRINT(("AUODLR %d addr=0x%lx\n", 
		ch, (long unsigned int)dd_audio_get_addr_reg_auodlr(dd_audio_get(), ch)));

	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_get_addr_reg_auidl_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DriverCommon_DDIM_PRINT(("AUIDL%d addr=0x%lx\n", 
		ch, (long unsigned int)dd_audio_get_addr_reg_auidl(dd_audio_get(), ch)));

	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_get_addr_reg_auidr_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DriverCommon_DDIM_PRINT(("AUIDR %d addr=0x%lx\n", 
		ch, (long unsigned int)dd_audio_get_addr_reg_auidlr(dd_audio_get(), ch)));

	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_get_addr_reg_auodl_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DriverCommon_DDIM_PRINT(("AUODL %d addr=0x%lx\n", 
		ch, (long unsigned int)dd_audio_get_addr_reg_auodl(dd_audio_get(), ch)));

	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_get_addr_reg_auodr_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DriverCommon_DDIM_PRINT(("AUODR %d addr=0x%lx\n",
		ch, (long unsigned int)dd_audio_get_addr_reg_auodr(dd_audio_get(), ch)));

	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_get_addr_reg_auiddmapt_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DriverCommon_DDIM_PRINT(("AUIDDMAPT%d addr=0x%lx\n", 
		ch, (long unsigned int)dd_audio_get_addr_reg_auiddmapt(dd_audio_get(), ch)));

	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_get_addr_reg_auoddmapt_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DriverCommon_DDIM_PRINT(("AUODDMAPT %d addr=0x%lx\n", 
		ch, (long unsigned int)dd_audio_get_addr_reg_auoddmapt(dd_audio_get(), ch)));

	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_get_input_fifo_status_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DriverCommon_DDIM_PRINT(("AUIFST%d = 0x%lx\n", 
		ch, (long unsigned int)dd_audio_get_input_fifo_status(dd_audio_get(), ch)));

	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

void ct_dd_audio_get_output_fifo_status_test( CtDdAudioGet *self )
{
	guint8 ch = self->ch;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	DriverCommon_DDIM_PRINT(("AUOFST%d = 0x%lx\n", 
		ch, (long unsigned int)dd_audio_get_output_fifo_status(dd_audio_get(), ch)));

	DriverCommon_DDIM_PRINT(("<%s> End. ch=%d\n", __FUNCTION__, ch));
}

CtDdAudioGet *ct_dd_audio_get_new(gpointer *temp, guint8 ch)
{
    CtDdAudioGet *self = CT_DD_AUDIO_GET(g_object_new(CT_TYPE_DD_AUDIO_GET, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}
