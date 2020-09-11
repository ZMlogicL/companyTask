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
	const guint8 ch = self->ch;
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
	if (ch != 1){
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUOEF = 0;
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.AUIEF = 0;
		IO_AUDIO.AUDIOIF[ch].AUMD.bit.LBF = 0;
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.DMIE = 0;
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.DMOE = 0;
		IO_AUDIO.AUDIOIF[ch].AUST.bit.EDMOE = 0;
		IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE = 0;
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE = 0;
		IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE = 0;
		IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE = 0;
	}
	else{
		IO_AUDIO.AUDIOIF[0].AUCR.bit.AUOEF = 0;
		IO_AUDIO.AUDIOIF[0].AUCR.bit.AUIEF = 0;
		IO_AUDIO.AUDIOIF[0].AUMD.bit.LBF = 0;
		IO_AUDIO.AUDIOIF[0].AUCR.bit.DMIE = 0;
		IO_AUDIO.AUDIOIF[0].AUST.bit.EDMIE = 0;
		IO_AUDIO.AUDIOIF[0].AUCR.bit.DMOE = 0;
		IO_AUDIO.AUDIOIF[0].AUST.bit.EDMOE = 0;
		IO_AUDIO.AUDIOIF[0].AUST.bit.EINTIE = 0;
		IO_AUDIO.AUDIOIF[0].AUCR.bit.INTIE = 0;
		IO_AUDIO.AUDIOIF[0].AUST.bit.EINTOE = 0;
		IO_AUDIO.AUDIOIF[0].AUCR.bit.INTOE = 0;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.AUOEF = 0;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.AUIEF = 0;
		IO_AUDIO.AUDIOIF[1].AUMD.bit.LBF = 0;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.DMIE = 0;
		IO_AUDIO.AUDIOIF[1].AUST.bit.EDMIE = 0;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.DMOE = 0;
		IO_AUDIO.AUDIOIF[1].AUST.bit.EDMOE = 0;
		IO_AUDIO.AUDIOIF[1].AUST.bit.EINTIE = 0;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.INTIE = 0;
		IO_AUDIO.AUDIOIF[1].AUST.bit.EINTOE = 0;
		IO_AUDIO.AUDIOIF[1].AUCR.bit.INTOE = 0;
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

	IO_CHIPTOP.PERSEL.bit.AU2PXSEL = 0;	// Select AudioIF ch2
	IO_CHIPTOP.PERSEL2.bit.AU0DOC = 0;	// Select AU0DO
	IO_CHIPTOP.PERSEL2.bit.AU0MCC = 0;	// Select AUM0CLKO


	IO_CHIPTOP.EPCR.bit.P30 = 1;	// AU0CLK
	IO_CHIPTOP.EPCR.bit.P31 = 1;	// AU0LR
	IO_CHIPTOP.DDR.bit.P32  = 0;	// AU0DI
	IO_CHIPTOP.EPCR.bit.P33 = 1;	// AU0DO
	IO_CHIPTOP.EPCR.bit.P34 = 1;	// AU1CLK
	IO_CHIPTOP.EPCR.bit.P35 = 1;	// AU1LR
	IO_CHIPTOP.EPCR.bit.P36 = 1;	// AUM1CLKO
	IO_CHIPTOP.EPCR.bit.P37 = 1;	// AU1DO

	IO_CHIPTOP.DDR.bit.P41  = 0;	// AU2DI

	IO_CHIPTOP.DDR.bit.PA6  = 0;	// AUMCLKI
	IO_CHIPTOP.EPCR.bit.PA7 = 1;	// AUM0CLKO

	IO_CHIPTOP.EPCR.bit.PU0 = 1;	// AU2CLK
	IO_CHIPTOP.EPCR.bit.PU1 = 1;	// AU2LR
	IO_CHIPTOP.EPCR.bit.PU2 = 1;	// AU2DO
	IO_CHIPTOP.EPCR.bit.PU3 = 1;	// AUM2CLKO
#endif

#if 0
	Dd_GIC_Ctrl(E_DD_GIC_INTID_AUDIO_IF_CH0_INT,1,D_DD_GIC_PRI30,0);
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
	const guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_input(dd_audio_get(), ch, D_DDIM_USER_SEM_WAIT_POL);
	dd_audio_close_input(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_input_open_test2( CtDdAudio *self )
{
	const guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));
	
	result = dd_audio_open_input(dd_audio_get(), ch, 3000);
	dd_audio_close_input(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_input_open_test3( CtDdAudio *self )
{
	const guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_input(dd_audio_get(), ch, D_DDIM_USER_SEM_WAIT_FEVR);
	dd_audio_close_input(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_input_open_test4( CtDdAudio *self )
{
	const guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_input(dd_audio_get(), ch, -2);
	dd_audio_close_input(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_input_open_test5( CtDdAudio *self )
{
	const guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_open_input(dd_audio_get(), ch, D_DDIM_USER_SEM_WAIT_POL);
	result = dd_audio_open_input(dd_audio_get(), ch, D_DDIM_USER_SEM_WAIT_POL);
	dd_audio_close_input(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_output_open_test1( CtDdAudio *self )
{
	const guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_output(dd_audio_get(), ch, D_DDIM_USER_SEM_WAIT_POL);
	dd_audio_close_output(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_output_open_test2( CtDdAudio *self )
{
	const guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_output(dd_audio_get(), ch, 3000);
	dd_audio_close_output(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_output_open_test3( CtDdAudio *self )
{
	const guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_output(dd_audio_get(), ch, D_DDIM_USER_SEM_WAIT_FEVR);
	dd_audio_close_output(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_output_open_test4( CtDdAudio *self )
{
	const guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	result = dd_audio_open_output(dd_audio_get(), ch, -2);
	dd_audio_close_output(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_output_open_test5( CtDdAudio *self )
{
	const guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_open_output(dd_audio_get(), ch, D_DDIM_USER_SEM_WAIT_POL);
	result = dd_audio_open_output(dd_audio_get(), ch, D_DDIM_USER_SEM_WAIT_POL);
	dd_audio_close_output(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_input_close_test( CtDdAudio *self )
{
	const guint8 ch = self->ch;
	gint32 result;
	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

	dd_audio_open_input(dd_audio_get(), ch, D_DDIM_USER_SEM_WAIT_POL);
	result = dd_audio_close_input(dd_audio_get(), ch);

	DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
}

void ct_dd_audio_output_close_test( CtDdAudio *self )
{
	const guint8 ch = self->ch;
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
	IO_CHIPTOP.PLLCNT1.bit.PL10ST = 1;
#endif

	dd_audio_init(dd_audio_get());

	DriverCommon_DDIM_PRINT(("<%s> End.\n", __FUNCTION__));
}

void ct_dd_audio_reset_test( CtDdAudio *self )
{
	const guint8 ch = self->ch;
	gint32 result;
	T_DD_AUDIO_CTRL_COMMON ctrlCommon;
	T_DD_AUDIO_CTRL_OUT ctrlOut;
	T_DD_AUDIO_CTRL_IN ctrlIn;
	T_DD_AUDIO_I2S_CMMN i2sCommon;
	T_DD_AUDIO_I2S_IN i2sIn;
	T_DD_AUDIO_I2S_OUT i2sOut;
	T_DD_AUDIO_DMA dmaSetting;

	DriverCommon_DDIM_PRINT(( "<%s> Start\n", __FUNCTION__ ));

    ct_dd_audio_reg_init(self);

	result = dd_audio_reset(dd_audio_get(), ch);

	if (result != D_DDIM_OK){
		DriverCommon_DDIM_PRINT(("<%s> End. result=0x%x, ch=%d\n", __FUNCTION__, result, ch));
		return;
	}

	dd_audio_get_ctrl_common(dd_audio_get(), ch, &ctrlCommon);
	DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_Common----\n"));
	DriverCommon_DDIM_PRINT(("fifo_usage=0x%x\n", ctrlCommon.fifo_usage));
	DriverCommon_DDIM_PRINT(("channel=0x%x\n", ctrlCommon.channel));

	if (ch != 3){
		dd_audio_get_ctrl_input(dd_audio_get(), ch, &ctrlIn);

		DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_Input----\n"));
		DriverCommon_DDIM_PRINT(("format=0x%x\n", ctrlIn.format));
		DriverCommon_DDIM_PRINT(("fifo_stages=0x%x\n", ctrlIn.fifo_stages));
		DriverCommon_DDIM_PRINT(("ahb_format=0x%x\n", ctrlIn.ahb_format));
		DriverCommon_DDIM_PRINT(("bit_shift=0x%x\n", ctrlIn.bit_shift));
	}

	if (ch < 4){
		dd_audio_get_ctrl_output(dd_audio_get(), ch, &ctrlOut);

		DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_Output----\n"));
		DriverCommon_DDIM_PRINT(("format=0x%x\n", ctrlOut.format));
		DriverCommon_DDIM_PRINT(("fifo_stages=0x%x\n", ctrlOut.fifo_stages));
		DriverCommon_DDIM_PRINT(("ahb_format=0x%x\n", ctrlOut.ahb_format));
		DriverCommon_DDIM_PRINT(("lr_copy=0x%x\n", ctrlOut.lr_copy));
		DriverCommon_DDIM_PRINT(("mix_play=0x%x\n", ctrlOut.mix_play));
		DriverCommon_DDIM_PRINT(("bit_shift=0x%x\n", ctrlOut.bit_shift));
	}

	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(), ch, &i2sCommon);

	DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_I2sCmmn----\n"));
	DriverCommon_DDIM_PRINT(("aumclki=0x%x\n", i2sCommon.aumclki));
	DriverCommon_DDIM_PRINT(("div_aumclko=0x%x\n", i2sCommon.div_aumclko));
	DriverCommon_DDIM_PRINT(("div_auclk=0x%x\n", i2sCommon.div_auclk));
	DriverCommon_DDIM_PRINT(("div_lrclk=0x%x\n", i2sCommon.div_lrclk));
	DriverCommon_DDIM_PRINT(("clk_div_enable=0x%x\n", i2sCommon.clk_div_enable));
	DriverCommon_DDIM_PRINT(("master_slave=0x%x\n", i2sCommon.master_slave));

	if (ch != 3){
		dd_audio_get_ctrl_i2s_in(dd_audio_get(), ch, &i2sIn);

		DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_I2sIn----\n"));
		DriverCommon_DDIM_PRINT(("mode_in=0x%x\n", i2sIn.mode_in));
		DriverCommon_DDIM_PRINT(("bit_in=0x%x\n", i2sIn.bit_in));
	}

	if (ch < 4){
		dd_audio_get_ctrl_i2s_out(dd_audio_get(), ch, &i2sOut);

		DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_I2sOut----\n"));
		DriverCommon_DDIM_PRINT(("mode_out=0x%x\n", i2sOut.mode_out));
		DriverCommon_DDIM_PRINT(("bit_out=0x%x\n", i2sOut.bit_out));
		DriverCommon_DDIM_PRINT(("fs=0x%x\n", i2sOut.fs));
	}

	if (ch != 3){
		dd_audio_get_ctrl_dma_in(dd_audio_get(), ch, &dmaSetting);

		DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_DmaIn----\n"));
		DriverCommon_DDIM_PRINT(("dma_2ch=0x%x\n", dmaSetting.dma_2ch));
		DriverCommon_DDIM_PRINT(("dma_trnsf_cnt=0x%x\n", dmaSetting.dma_trnsf_cnt));
	}

	if (ch < 4){
		dd_audio_get_ctrl_dma_out(dd_audio_get(), ch, &dmaSetting);

		DriverCommon_DDIM_PRINT(("----Dd_Audio_Get_Ctrl_DmaOut----\n"));
		DriverCommon_DDIM_PRINT(("dma_2ch=0x%x\n", dmaSetting.dma_2ch));
		DriverCommon_DDIM_PRINT(("dma_trnsf_cnt=0x%x\n", dmaSetting.dma_trnsf_cnt));
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
