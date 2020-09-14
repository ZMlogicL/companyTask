/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date               :2020-09-03
*@author            :luhongyin
*@brief               :CtDdAudio类
*@rely                 :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include <string.h>
#include <stdlib.h>
#include "audio_if.h"
// #include "dd_audio.h"
#include "dd_hdmac0.h"
#include "dd_top.h"
#include "dd_cache.h"
#include "dd_pdm.h"
#include "dd_gic.h"
#include "peripheral.h"

#include "../../../../MILB_API/Project/DeviceDriver/Peripheral/src/ddaudioctrl.h"
#include "../../../../MILB_API/Project/DeviceDriver/Peripheral/src/ddaudio.h"
#include "../../../../milb_api_usercustom/src/ddimusercustom.h"
#include "ctddaudio.h"

G_DEFINE_TYPE(CtDdAudio, ct_dd_audio, G_TYPE_OBJECT);
#define 	CT_DD_AUDIO_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_DD_AUDIO, CtDdAudioPrivate))

struct _CtDdAudioPrivate
{
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static kuint32 S_GCT_DD_AUDIO_NG_COUNTER;
static kuint32 S_GCT_DD_AUDIO_OK_COUNTER;

/*
 * DECLS
 */
static void ct_dd_audio_class_init(CtDdAudioClass *klass);
static void ct_dd_audio_init(CtDdAudio *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);

/*
 * IMPL
 */
static void ct_dd_audio_class_init(CtDdAudioClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtDdAudioPrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_dd_audio_init(CtDdAudio *self)
{
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_dd_audio_parent_class)->finalize(object);
}

/*
*PUBLIC
*/
/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/

void ct_dd_audio_test_init(CtDdAudio *self)
{
	S_GCT_DD_AUDIO_NG_COUNTER = 0;
	S_GCT_DD_AUDIO_OK_COUNTER = 0;
}

void ct_dd_audio_test_fin(CtDdAudio *self, const kchar *testName)
{
    DriverCommon_DDIM_PRINT(("## %s ## \n",testName));
    DriverCommon_DDIM_PRINT(("ch%d \n",self->ch));
    DriverCommon_DDIM_PRINT((".....NG (%d tests)\n",S_GCT_DD_AUDIO_NG_COUNTER));
    DriverCommon_DDIM_PRINT((".....OK (%d tests)\n\n\n",S_GCT_DD_AUDIO_OK_COUNTER));
	k_object_unref(self);
}

void ct_dd_audio_do_test_ng_countup(CtDdAudio *self)
{
    S_GCT_DD_AUDIO_NG_COUNTER++;
}

void ct_dd_audio_do_test_ok_countup(CtDdAudio *self)
{
    S_GCT_DD_AUDIO_OK_COUNTER++;
}

void ct_dd_audio_reg_init(CtDdAudio *self)
{
#ifdef PC_DEBUG
	guint8 ch = self->ch;
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
	if (ch != 1){
		ioAudio.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
		ioAudio.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
		ioAudio.AUDIOIF[ch].AUMD.bit.LBF = 0;
		ioAudio.AUDIOIF[ch].AUCR.bit.DMIE = 0;
		ioAudio.AUDIOIF[ch].AUCR.bit.DMOE = 0;
		ioAudio.AUDIOIF[ch].AUST.bit.EDMOE = 0;
		ioAudio.AUDIOIF[ch].AUST.bit.EINTIE = 0;
		ioAudio.AUDIOIF[ch].AUCR.bit.INTIE = 0;
		ioAudio.AUDIOIF[ch].AUST.bit.EINTOE = 0;
		ioAudio.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	}
	else{
		ioAudio.AUDIOIF[0].AUCR.bit.AUOEF = 0;
		ioAudio.AUDIOIF[0].AUCR.bit.AUIEF = 0;
		ioAudio.AUDIOIF[0].AUMD.bit.LBF = 0;
		ioAudio.AUDIOIF[0].AUCR.bit.DMIE = 0;
		ioAudio.AUDIOIF[0].AUST.bit.EDMIE = 0;
		ioAudio.AUDIOIF[0].AUCR.bit.DMOE = 0;
		ioAudio.AUDIOIF[0].AUST.bit.EDMOE = 0;
		ioAudio.AUDIOIF[0].AUST.bit.EINTIE = 0;
		ioAudio.AUDIOIF[0].AUCR.bit.INTIE = 0;
		ioAudio.AUDIOIF[0].AUST.bit.EINTOE = 0;
		ioAudio.AUDIOIF[0].AUCR.bit.INTOE = 0;
		ioAudio.AUDIOIF[1].AUCR.bit.AUOEF = 0;
		ioAudio.AUDIOIF[1].AUCR.bit.AUIEF = 0;
		ioAudio.AUDIOIF[1].AUMD.bit.LBF = 0;
		ioAudio.AUDIOIF[1].AUCR.bit.DMIE = 0;
		ioAudio.AUDIOIF[1].AUST.bit.EDMIE = 0;
		ioAudio.AUDIOIF[1].AUCR.bit.DMOE = 0;
		ioAudio.AUDIOIF[1].AUST.bit.EDMOE = 0;
		ioAudio.AUDIOIF[1].AUST.bit.EINTIE = 0;
		ioAudio.AUDIOIF[1].AUCR.bit.INTIE = 0;
		ioAudio.AUDIOIF[1].AUST.bit.EINTOE = 0;
		ioAudio.AUDIOIF[1].AUCR.bit.INTOE = 0;
	}
#endif
}


/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/

void ct_dd_audio_set_gpio( CtDdAudio *self )
{
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#if 0
	Dd_Top_Set_CLKSTOP_GPIOAP(0);

	ioChiptop.PERSEL.bit.AU2PXSEL = 0;	// Select AudioIF ch2
	ioChiptop.PERSEL2.bit.AU0DOC = 0;	// Select AU0DO
	ioChiptop.PERSEL2.bit.AU0MCC = 0;	// Select AUM0CLKO


	ioChiptop.EPCR.bit.P30 = 1;	// AU0CLK
	ioChiptop.EPCR.bit.P31 = 1;	// AU0LR
	ioChiptop.DDR.bit.P32  = 0;	// AU0DI
	ioChiptop.EPCR.bit.P33 = 1;	// AU0DO
	ioChiptop.EPCR.bit.P34 = 1;	// AU1CLK
	ioChiptop.EPCR.bit.P35 = 1;	// AU1LR
	ioChiptop.EPCR.bit.P36 = 1;	// AUM1CLKO
	ioChiptop.EPCR.bit.P37 = 1;	// AU1DO

	ioChiptop.DDR.bit.P41  = 0;	// AU2DI

	ioChiptop.DDR.bit.PA6  = 0;	// AUMCLKI
	ioChiptop.EPCR.bit.PA7 = 1;	// AUM0CLKO

	ioChiptop.EPCR.bit.PU0 = 1;	// AU2CLK
	ioChiptop.EPCR.bit.PU1 = 1;	// AU2LR
	ioChiptop.EPCR.bit.PU2 = 1;	// AU2DO
	ioChiptop.EPCR.bit.PU3 = 1;	// AUM2CLKO
#endif

#if 0
	Dd_GIC_Ctrl(DdGic_INTID_AUDIO_IF_CH0_INT,1,D_DD_GIC_PRI30,0);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_AUDIO_IF_CH1_INT,1,D_DD_GIC_PRI30,0);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_AUDIO_IF_CH2_INT,1,D_DD_GIC_PRI30,0);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_AUDIO_IF_CH3_INT,1,D_DD_GIC_PRI30,0);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_AUDIO_IF_CH4_INT,1,D_DD_GIC_PRI30,0);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_AUDIO_IF_CH5_INT,1,D_DD_GIC_PRI30,0);

	Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH0_INT,1,D_DD_GIC_PRI30,0);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH1_INT,1,D_DD_GIC_PRI30,0);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH2_INT,1,D_DD_GIC_PRI30,0);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH3_INT,1,D_DD_GIC_PRI30,0);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH4_INT,1,D_DD_GIC_PRI30,0);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH5_INT,1,D_DD_GIC_PRI30,0);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH6_INT,1,D_DD_GIC_PRI30,0);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH7_INT,1,D_DD_GIC_PRI30,0);
#endif

	DriverCommon_DDIM_PRINT(("<%s> End.\n", __FUNCTION__));
}

void ct_dd_audio_input_open_test1( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_input(dd_audio_get(), ch, DdimUserCustom_SEM_WAIT_POL);
	dd_audio_close_input(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_input_open_test2( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));
	
	result = dd_audio_open_input(dd_audio_get(), ch, 3000);
	dd_audio_close_input(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_input_open_test3( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_input(dd_audio_get(), ch, DdimUserCustom_SEM_WAIT_FEVR);
	dd_audio_close_input(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_input_open_test4( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_input(dd_audio_get(), ch, -2);
	dd_audio_close_input(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_input_open_test5( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_open_input(dd_audio_get(), ch, DdimUserCustom_SEM_WAIT_POL);
	result = dd_audio_open_input(dd_audio_get(), ch, DdimUserCustom_SEM_WAIT_POL);
	dd_audio_close_input(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_output_open_test1( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_output(dd_audio_get(), ch, DdimUserCustom_SEM_WAIT_POL);
	dd_audio_close_output(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_output_open_test2( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_output(dd_audio_get(), ch, 3000);
	dd_audio_close_output(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_output_open_test3( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_output(dd_audio_get(), ch, DdimUserCustom_SEM_WAIT_FEVR);
	dd_audio_close_output(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_output_open_test4( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_output(dd_audio_get(), ch, -2);
	dd_audio_close_output(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_output_open_test5( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_open_output(dd_audio_get(), ch, DdimUserCustom_SEM_WAIT_POL);
	result = dd_audio_open_output(dd_audio_get(), ch, DdimUserCustom_SEM_WAIT_POL);
	dd_audio_close_output(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_input_close_test( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_open_input(dd_audio_get(), ch, DdimUserCustom_SEM_WAIT_POL);
	result = dd_audio_close_input(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_output_close_test( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_open_output(dd_audio_get(), ch, 3000);
	result = dd_audio_close_output(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_init_test( CtDdAudio *self )
{
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

#ifdef PC_DEBUG
	ioChiptop.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());

	DriverCommon_DDIM_PRINT(("<%s> End.\n", __FUNCTION__));
}

void ct_dd_audio_reset_test( CtDdAudio *self )
{
	guint8 ch = self->ch;
	gint32 result;
	AudioCtrlCommon ctrlCommon;
	AudioCtrlOut ctrlOut;
	AudioCtrlIn ctrlIn;
	AudioI2sCmmn i2sCommon;
	AudioI2sIn i2sIn;
	AudioI2sOut i2sOut;
	AudioDma dmaSetting;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

    ct_dd_audio_reg_init(self);

	result = dd_audio_reset(dd_audio_get(), ch);

	if (result != D_DDIM_OK){
		DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
		return;
	}

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_Common----\n"));
	DriverCommon_DDIM_PRINT(("fifoUsage=0x%x\n", ctrlCommon.fifoUsage));
	DriverCommon_DDIM_PRINT(("channel=0x%x\n", ctrlCommon.channel));

	if (ch != 3){
		dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlIn);

		DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_Input----\n"));
		DriverCommon_DDIM_PRINT(("format=0x%x\n", ctrlIn.format));
		DriverCommon_DDIM_PRINT(("fifoStages=0x%x\n", ctrlIn.fifoStages));
		DriverCommon_DDIM_PRINT(("ahbFormat=0x%x\n", ctrlIn.ahbFormat));
		DriverCommon_DDIM_PRINT(("bitShift=0x%x\n", ctrlIn.bitShift));
	}

	if (ch < 4){
		dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlOut);

		DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_Output----\n"));
		DriverCommon_DDIM_PRINT(("format=0x%x\n", ctrlOut.format));
		DriverCommon_DDIM_PRINT(("fifoStages=0x%x\n", ctrlOut.fifoStages));
		DriverCommon_DDIM_PRINT(("ahbFormat=0x%x\n", ctrlOut.ahbFormat));
		DriverCommon_DDIM_PRINT(("lrCopy=0x%x\n", ctrlOut.lrCopy));
		DriverCommon_DDIM_PRINT(("mixPlay=0x%x\n", ctrlOut.mixPlay));
		DriverCommon_DDIM_PRINT(("bitShift=0x%x\n", ctrlOut.bitShift));
	}

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_I2sCmmn----\n"));
	DriverCommon_DDIM_PRINT(("aumclki=0x%x\n", i2sCommon.aumclki));
	DriverCommon_DDIM_PRINT(("divAumclko=0x%x\n", i2sCommon.divAumclko));
	DriverCommon_DDIM_PRINT(("divAuclk=0x%x\n", i2sCommon.divAuclk));
	DriverCommon_DDIM_PRINT(("divLrclk=0x%x\n", i2sCommon.divLrclk));
	DriverCommon_DDIM_PRINT(("clkDivEnable=0x%x\n", i2sCommon.clkDivEnable));
	DriverCommon_DDIM_PRINT(("masterSlave=0x%x\n", i2sCommon.masterSlave));

	if (ch != 3){
		dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

		DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_I2sIn----\n"));
		DriverCommon_DDIM_PRINT(("modeIn=0x%x\n", i2sIn.modeIn));
		DriverCommon_DDIM_PRINT(("bitIn=0x%x\n", i2sIn.bitIn));
	}

	if (ch < 4){
		dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

		DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_I2sOut----\n"));
		DriverCommon_DDIM_PRINT(("modeOut=0x%x\n", i2sOut.modeOut));
		DriverCommon_DDIM_PRINT(("bitOut=0x%x\n", i2sOut.bitOut));
		DriverCommon_DDIM_PRINT(("fs=0x%x\n", i2sOut.fs));
	}

	if (ch != 3){
		dd_audio_get_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

		DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_DmaIn----\n"));
		DriverCommon_DDIM_PRINT(("dma2Ch=0x%x\n", dmaSetting.dma2Ch));
		DriverCommon_DDIM_PRINT(("dmaTrnsfCnt=0x%x\n", dmaSetting.dmaTrnsfCnt));
	}

	if (ch < 4){
		dd_audio_get_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

		DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_DmaOut----\n"));
		DriverCommon_DDIM_PRINT(("dma2Ch=0x%x\n", dmaSetting.dma2Ch));
		DriverCommon_DDIM_PRINT(("dmaTrnsfCnt=0x%x\n", dmaSetting.dmaTrnsfCnt));
	}

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

CtDdAudio* ct_dd_audio_new(gpointer *temp, guint8 ch)
{
    CtDdAudio *self = CT_DD_AUDIO(g_object_new(CT_TYPE_DD_AUDIO, NULL));
	if(*temp)
	{
		 *temp = (gpointer)self;
	}
    self->ch = ch;
    return self;
}
