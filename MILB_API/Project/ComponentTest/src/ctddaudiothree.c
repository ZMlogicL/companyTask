/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree类
*@rely                :klib
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
#include "ctddaudiothree.h"
#include "ctddaudiovariable.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdAudioThree, ct_dd_audio_three);
#define CT_DD_AUDIO_THREE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdAudioThreePrivate,CT_TYPE_DD_AUDIO_THREE))

#define CtDdAudioThree_CT_DD_AUDIO_PRINT(arg)      if(S_GCT_DD_AUDIO_DISPLAY_FLAG) {Ddim_Print(arg);}

struct _CtDdAudioThreePrivate
{
};

//变量
static kint32 S_GCT_DD_AUDIO_DISPLAY_FLAG = 1;

/*
 * DECLS
 */
static void 	ct_dd_audio_three_constructor(CtDdAudioThree *self);
static void 	ct_dd_audio_three_destructor(CtDdAudioThree *self);
static void 	ctDdAudioDmaIntHandler041_cb( void );

/*
 * IMPL
 */
static void ct_dd_audio_three_constructor(CtDdAudioThree *self) 
{
}

static void ct_dd_audio_three_destructor(CtDdAudioThree *self) 
{
}

//回调方法:
static void ctDdAudioDmaIntHandler041_cb( void )
{
	kuint8 ch = 0;

	// ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 10) {
		Dd_HDMAC0_Input_Audio_Async( 0,
			 D_DD_HDMAC0_IS_IDREQ_0,
			 Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(800 * 2 * ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
			 (800 * 2),
			 (VP_CALLBACK)ctDdAudioDmaIntHandler041_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler041_cb\n"));
}
/*
 * PUBLIC
 */
void ct_dd_audio_three_reg_rw(CtDdAudioThree *self)
{
	kuint8 ch = self->ch;

	// AURES
	IO_AUDIO.AUDIOIF_CTRL.AURES.word = 0x0000003F;
	if (IO_AUDIO.AUDIOIF_CTRL.AURES.word == 0x0000003F){
		CtDdAudioThree_CT_DD_AUDIO_PRINT(("AURES Check OK\n"));
	}
	else {
		CtDdAudioThree_CT_DD_AUDIO_PRINT(("AURES Check NG: 0x%08x\n", 
		(kuint)IO_AUDIO.AUDIOIF_CTRL.AURES.word));
	}
	IO_AUDIO.AUDIOIF_CTRL.AURES.word = 0x00000000;

	for (ch = 0; ch <= 5; ch++){
		// AUODLR
		IO_AUDIO.AUDIOIF[ch].AUODLR = 0xA5A5A5A5;
		if (IO_AUDIO.AUDIOIF[ch].AUODLR == 0xA5A5A5A5){
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUODLR%d Check OK\n", ch));
		}
		else {
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUODLR%d Check NG: 0x%08x\n", ch, 
			(kuint)IO_AUDIO.AUDIOIF[ch].AUODLR));
		}

		// AUCR
		IO_AUDIO.AUDIOIF[ch].AUCR.word = 0xED8ECC03;
		// AUORF = 1
		// AUOF = 110 1101b
		// AUIRF = 1
		// AUIF = 1110b
		// DMOE = 1
		// DMIE = 1
		// AUOEF = R
		// AUIEF = R
		// INTOE = 1
		// INTIE = 1
		// INTO = R
		// INTI = R
		// AUODSEL = 1
		// AUIDSEL = 1
		if ((IO_AUDIO.AUDIOIF[ch].AUCR.word & 0xED8ECC03)== 0xED8ECC03){
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUCR%d Check1 OK\n", ch));
		}
		else {
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUCR%d Check1 NG: 0x%08x\n", ch, 
			(kuint)IO_AUDIO.AUDIOIF[ch].AUCR.word));
		}

		IO_AUDIO.AUDIOIF[ch].AUCR.word = 0x02020000;
		if ((IO_AUDIO.AUDIOIF[ch].AUCR.word & 0x02020000) == 0x02020000){
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUCR%d Check2 OK\n", ch));
		}
		else {
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUCR%d Check2 NG: 0x%08x\n", ch, 
			(kuint)IO_AUDIO.AUDIOIF[ch].AUCR.word));
		}

		// AUMD
		// LBF = R
		// STEREO = 1
		// (bit26) = 1
		// OSTG16 = 1
		// ISTG16 = 1
		// OHWSWP = 1
		// OBYTESWP = 1
		// IHWSWP = 1
		// IBYTESWP = 1
		IO_AUDIO.AUDIOIF[ch].AUMD.word = 0x0F0F0000;
		if ((IO_AUDIO.AUDIOIF[ch].AUMD.word & 0x0F0F0000) == 0x0F0F0000){
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUMD%d Check OK\n", ch));
		}
		else {
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUMD%d Check NG: 0x%08x\n", ch, 
			(kuint)IO_AUDIO.AUDIOIF[ch].AUMD.word));
		}
		IO_AUDIO.AUDIOIF[ch].AUMD.word = 0x04800000;

		// AUST
		// ESTG = 01b
		// EDMOE = 1
		// EDMIE = 1
		// EITOE = 1
		// EINTIE = 1
		// EINTO = R
		// EINTI = R
		// UFIE = 1
		// OFIE = 1
		// ORUF = x
		// IROF = x
		IO_AUDIO.AUDIOIF[ch].AUST.word = 0x7C0C0000;
		if ((IO_AUDIO.AUDIOIF[ch].AUST.word & 0x7C0C0000) == 0x7C0C0000){
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUST%d Check OK\n", ch));
		}
		else {
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUST%d Check NG: 0x%08x\n", ch, 
			(kuint)IO_AUDIO.AUDIOIF[ch].AUST.word));
		}

		// AUCC
		// AUCKOE = 1
		// DIVE = 1
		// DIVMCK = 11111b
		// DIVCK = 100b
		// DIVLR = 10b

		IO_AUDIO.AUDIOIF[ch].AUCC.word = 0xDF120000;
		if (IO_AUDIO.AUDIOIF[ch].AUCC.word == 0xDF120000){
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUCC%d Check OK\n", ch));
		}
		else {
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUCC%d Check NG: 0x%08x\n", ch, 
			(kuint)IO_AUDIO.AUDIOIF[ch].AUCC.word));
		}

		// AUDP
		// AUIDS = 11b
		// AUODS = 11b
		// AUODF = 1
		// AUIDF = 1
		// AULRCP = 1
		// MIXPLAY = 1
		IO_AUDIO.AUDIOIF[ch].AUDP.word = 0x33030101;
		if (IO_AUDIO.AUDIOIF[ch].AUDP.word == 0x33030101){
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUDP%d Check OK\n", ch));
		}
		else {
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUDP%d Check NG: 0x%08x\n", ch, 
			(kuint)IO_AUDIO.AUDIOIF[ch].AUDP.word));
		}


#if 0
		// AUODL
		IO_AUDIO.AUDIOIF[ch].AUODL = 0xA5A5A5A5;
		if (IO_AUDIO.AUDIOIF[ch].AUODL == 0x00A5A5A5){
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUODL%d Check OK\n", ch));
		}
		else {
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUODL%d Check NG: 0x%08x\n", ch, 
			(kuint)IO_AUDIO.AUDIOIF[ch].AUODL));
		}

		// AUODR
		IO_AUDIO.AUDIOIF[ch].AUODR = 0xA5A5A5A5;
		if (IO_AUDIO.AUDIOIF[ch].AUODR == 0x00A5A5A5){
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUODR%d Check OK\n", ch));
		}
		else {
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUODR%d Check NG: 0x%08x\n", ch, 
			(kuint)IO_AUDIO.AUDIOIF[ch].AUODR));
		}
#endif

		// AUDMA2CTL
		// DMO2CHEN = 1
		// DMI2CHEN = 1
		IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.word = 0x00000101;
		if (IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.word == 0x00000101){
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUDMA2CTL%d Check OK\n", ch));
		}
		else {
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUDMA2CTL%d Check NG: 0x%08x\n", ch, 
			(kuint)IO_AUDIO.AUDIOIF[ch].AUDMA2CTL.word));
		}

		// AUDMISAMPLE
		IO_AUDIO.AUDIOIF[ch].AUDMISAMPLE.word = 0x0000FFFF;
		if (IO_AUDIO.AUDIOIF[ch].AUDMISAMPLE.word == 0x00000000){
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUDMISAMPLE%d Check OK\n", ch));
		}
		else {
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUDMISAMPLE%d Check NG: 0x%08x\n", ch, 
			(kuint)IO_AUDIO.AUDIOIF[ch].AUDMISAMPLE.word));
		}

		// AUDMOSAMPLE
		IO_AUDIO.AUDIOIF[ch].AUDMOSAMPLE.word = 0x0000FFFF;
		if (IO_AUDIO.AUDIOIF[ch].AUDMOSAMPLE.word == 0x00000000){
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUDMOSAMPLE%d Check OK\n", ch));
		}
		else {
			CtDdAudioThree_CT_DD_AUDIO_PRINT(("AUDMOSAMPLE%d Check NG: 0x%08x\n", ch, 
			(kuint)IO_AUDIO.AUDIOIF[ch].AUDMOSAMPLE.word));
		}
	}
}

void ct_dd_audio_three_input_open_close(CtDdAudioThree *self)
{
	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Input(self->ch,D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(self->ch), D_DDIM_OK);
	CtDdAudio* testFin = ct_dd_audio_new(NULL, self->ch);
    ct_dd_audio_test_fin(testFin, "> audio 1 : Input open/close test");
}

void ct_dd_audio_three_output_open_close(CtDdAudioThree *self)
{
	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Output(self->ch,D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(self->ch), D_DDIM_OK);
	CtDdAudio* testFin = ct_dd_audio_new(NULL, self->ch);
    ct_dd_audio_test_fin(testFin, "> audio 2 : Output open/close test");
}

void ct_dd_audio_three_init(CtDdAudioThree *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_OUT	ctrlOut;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_I2S_OUT	i2sOut;
	T_DD_AUDIO_DMA	dma;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	if (ch != 3){
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Input(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);
	}

	if (ch <= 3){
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Output(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);
	}

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlCommon.fifo_usage, E_DD_AUDIO_FIFO_USAGE_STAGES_8);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlCommon.channel, E_DD_AUDIO_CHANNEL_MONO);

	if (ch != 3){
		Dd_Audio_Get_Ctrl_Input(ch, &ctrlIn);

		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlIn.format, E_DD_AUDIO_DATA_REG_FRMT_R_JUST);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlIn.fifo_stages, E_DD_AUDIO_FIFO_STAGES_1);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlIn.ahb_format, E_DD_AUDIO_AHB_FRMT_R_JUST);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlIn.bit_shift, E_DD_AUDIO_BIT_SHIFT_0);
	}

	if (ch <= 3){
		Dd_Audio_Get_Ctrl_Output(ch, &ctrlOut);

		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.format, E_DD_AUDIO_DATA_REG_FRMT_R_JUST);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.fifo_stages, E_DD_AUDIO_FIFO_STAGES_1);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.ahb_format, E_DD_AUDIO_AHB_FRMT_R_JUST);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.lr_copy, D_DD_AUDIO_DISABLE);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.mix_play, D_DD_AUDIO_DISABLE);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.bit_shift, E_DD_AUDIO_BIT_SHIFT_0);
	}

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.aumclki, E_DD_AUDIO_MASTER_CLOCK_8_192);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.div_aumclko, E_DD_AUDIO_AUMCLKO_DIV_2);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.div_auclk, E_DD_AUDIO_AUCLK_DIV_16);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.div_lrclk, E_DD_AUDIO_AULR_DIV_32);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.clk_div_enable, D_DD_AUDIO_DISABLE);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.master_slave, E_DD_AUDIO_CLK_SLAVE);

	if (ch != 3){
		Dd_Audio_Get_Ctrl_I2sIn(ch, &i2sIn);

		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sIn.mode_in, E_DD_AUDIO_MODE_L_JUST);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sIn.bit_in, E_DD_AUDIO_BIT_8BIT);
	}

	if (ch <= 3){
		Dd_Audio_Get_Ctrl_I2sOut(ch, &i2sOut);

		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sOut.mode_out, E_DD_AUDIO_MODE_L_JUST);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sOut.bit_out, E_DD_AUDIO_BIT_8BIT);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sOut.fs, E_DD_AUDIO_FS_32FS);
	}

	if (ch != 3){
		Dd_Audio_Get_Ctrl_DmaIn(ch, &dma);

		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(dma.dma_2ch, D_DD_AUDIO_DISABLE);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(dma.dma_trnsf_cnt, 0);
	}

	if (ch <= 3){
		Dd_Audio_Get_Ctrl_DmaOut(ch, &dma);

		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(dma.dma_2ch, D_DD_AUDIO_DISABLE);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(dma.dma_trnsf_cnt, 0);
	}

	if (ch != 3){
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(ch), D_DDIM_OK);
	}

	if (ch <= 3){
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);
	}

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 3 : default setting test");
}

void ct_dd_audio_three_update_input_setting(CtDdAudioThree *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_DMA	dma;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Input(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);
	Dd_Audio_Get_Ctrl_Input(ch, &ctrlIn);
	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);
	Dd_Audio_Get_Ctrl_I2sIn(ch, &i2sIn);
	Dd_Audio_Get_Ctrl_DmaIn(ch, &dma);

	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_22_5792;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_4;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_8;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sCmmn(ch, &i2sCommon), D_DDIM_OK);

	i2sIn.mode_in = E_DD_AUDIO_MODE_R_JUST;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sIn(ch, &i2sIn), D_DDIM_OK);

	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_4;
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(ch, &ctrlCommon), D_DDIM_OK);

	ctrlIn.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlIn.bit_shift = E_DD_AUDIO_BIT_SHIFT_1;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Input(ch, &ctrlIn), D_DDIM_OK);

	dma.dma_2ch = D_DD_AUDIO_ENABLE;
	dma.dma_trnsf_cnt = 1024;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaIn(ch, &dma), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);
	Dd_Audio_Get_Ctrl_Input(ch, &ctrlIn);
	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);
	Dd_Audio_Get_Ctrl_I2sIn(ch, &i2sIn);
	Dd_Audio_Get_Ctrl_DmaIn(ch, &dma);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlCommon.fifo_usage, E_DD_AUDIO_FIFO_USAGE_STAGES_4);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlCommon.channel, E_DD_AUDIO_CHANNEL_STEREO);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlIn.format, E_DD_AUDIO_DATA_REG_FRMT_L_JUST);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlIn.fifo_stages, E_DD_AUDIO_FIFO_STAGES_16);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlIn.ahb_format, E_DD_AUDIO_AHB_FRMT_L_JUST);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlIn.bit_shift, E_DD_AUDIO_BIT_SHIFT_1);

	if (ch != 1){
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.aumclki, E_DD_AUDIO_MASTER_CLOCK_22_5792);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.div_aumclko, E_DD_AUDIO_AUMCLKO_DIV_4);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.div_auclk, E_DD_AUDIO_AUCLK_DIV_8);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.div_lrclk, E_DD_AUDIO_AULR_DIV_64);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.clk_div_enable, D_DD_AUDIO_ENABLE);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.master_slave, E_DD_AUDIO_CLK_MASTER);
	}

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sIn.mode_in, E_DD_AUDIO_MODE_R_JUST);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sIn.bit_in, E_DD_AUDIO_BIT_16BIT);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(dma.dma_2ch, D_DD_AUDIO_ENABLE);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(dma.dma_trnsf_cnt, 1024);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 4 : updates input setting. test");
}

void ct_dd_audio_three_update_output_setting(CtDdAudioThree *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_OUT	ctrlOut;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_OUT	i2sOut;
	T_DD_AUDIO_DMA	dma;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Output(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);
	Dd_Audio_Get_Ctrl_Output(ch, &ctrlOut);
	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);
	Dd_Audio_Get_Ctrl_I2sOut(ch, &i2sOut);
	Dd_Audio_Get_Ctrl_DmaOut(ch, &dma);

	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_22_5792;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_4;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_8;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sCmmn(ch, &i2sCommon), D_DDIM_OK);

	i2sOut.mode_out = E_DD_AUDIO_MODE_R_JUST;
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sOut(ch, &i2sOut), D_DDIM_OK);

	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_4;
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(ch, &ctrlCommon), D_DDIM_OK);

	ctrlOut.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlOut.fifo_stages =  E_DD_AUDIO_FIFO_STAGES_16;
	ctrlOut.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;

	if (ch != 1){
		ctrlOut.lr_copy = D_DD_AUDIO_ENABLE;
	}
	else {
		ctrlOut.lr_copy = D_DD_AUDIO_DISABLE;
	}

	ctrlOut.mix_play = D_DD_AUDIO_ENABLE;
	ctrlOut.bit_shift = E_DD_AUDIO_BIT_SHIFT_3;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Output(ch, &ctrlOut), D_DDIM_OK);

	dma.dma_2ch = D_DD_AUDIO_ENABLE;
	dma.dma_trnsf_cnt = 1024;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaOut(ch, &dma), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);
	Dd_Audio_Get_Ctrl_Output(ch, &ctrlOut);
	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);
	Dd_Audio_Get_Ctrl_I2sOut(ch, &i2sOut);
	Dd_Audio_Get_Ctrl_DmaOut(ch, &dma);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlCommon.fifo_usage, E_DD_AUDIO_FIFO_USAGE_STAGES_4);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlCommon.channel, E_DD_AUDIO_CHANNEL_STEREO);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.format, E_DD_AUDIO_DATA_REG_FRMT_L_JUST);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.fifo_stages,  E_DD_AUDIO_FIFO_STAGES_16);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.ahb_format, E_DD_AUDIO_AHB_FRMT_L_JUST);

	if (ch != 1){
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.lr_copy, D_DD_AUDIO_ENABLE);
	}
	else {
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.lr_copy, D_DD_AUDIO_DISABLE);
	}

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.mix_play, D_DD_AUDIO_ENABLE);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(ctrlOut.bit_shift, E_DD_AUDIO_BIT_SHIFT_3);

	if (ch != 1){
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.aumclki, E_DD_AUDIO_MASTER_CLOCK_22_5792);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.div_aumclko, E_DD_AUDIO_AUMCLKO_DIV_4);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.div_auclk, E_DD_AUDIO_AUCLK_DIV_8);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.div_lrclk, E_DD_AUDIO_AULR_DIV_64);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.clk_div_enable, D_DD_AUDIO_ENABLE);
		CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sCommon.master_slave, E_DD_AUDIO_CLK_MASTER);
	}

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sOut.mode_out, E_DD_AUDIO_MODE_R_JUST);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sOut.bit_out, E_DD_AUDIO_BIT_16BIT);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(i2sOut.fs, E_DD_AUDIO_FS_64FS);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(dma.dma_2ch, D_DD_AUDIO_ENABLE);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(dma.dma_trnsf_cnt, 1024);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 5 : updates output setting test");
}

void ct_dd_audio_three_reset_input_status(CtDdAudioThree *self)
{
	kuint8 ch = self->ch;
	CtDdAudio *temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Input(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Reset(ch), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Get_Status_Input(ch), FALSE);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 6 : Reset Input Status test");
}

void ct_dd_audio_three_reset_output_status(CtDdAudioThree *self)
{
	kuint8 ch = self->ch;
	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Output(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Reset(ch), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Get_Status_Output(ch), FALSE);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 7 : Reset Output Status test");
}

void ct_dd_audio_three_start_stop_input(CtDdAudioThree *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_DMA	dma;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Input(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);

	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_32;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sCmmn(ch, &i2sCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_I2sIn(ch, &i2sIn);

	i2sIn.mode_in = E_DD_AUDIO_MODE_L_JUST;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sIn(ch, &i2sIn), D_DDIM_OK);


	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);

	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_MONO;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(ch, &ctrlCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Input(ch, &ctrlIn);

	ctrlIn.format		= E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlIn.fifo_stages	= E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format	= E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlIn.bit_shift	= E_DD_AUDIO_BIT_SHIFT_0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Input(ch, &ctrlIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaIn(ch, &dma);

	dma.dma_2ch			= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt	= 0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaIn(ch, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Input(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(1);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Get_Status_Input(ch), TRUE);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Input(ch), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Get_Status_Input(ch), FALSE);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 7 : Input start/stop test");
}

void ct_dd_audio_three_start_stop_output(CtDdAudioThree *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_OUT	ctrlOut;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_OUT	i2sOut;
	T_DD_AUDIO_DMA	dma;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Output(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);

	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_16;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_32;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sCmmn(ch, &i2sCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_I2sOut(ch, &i2sOut);

	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.fs = E_DD_AUDIO_FS_32FS;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sOut(ch, &i2sOut), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);

	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_MONO;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(ch, &ctrlCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Output(ch, &ctrlOut);

	ctrlOut.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlOut.fifo_stages =  E_DD_AUDIO_FIFO_STAGES_16;
	ctrlOut.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlOut.lr_copy = D_DD_AUDIO_DISABLE;
	ctrlOut.mix_play = D_DD_AUDIO_DISABLE;
	ctrlOut.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Output(ch, &ctrlOut), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaOut(ch, &dma);

	dma.dma_2ch			= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt	= 0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaOut(ch, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Output(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(1);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Get_Status_Output(ch), TRUE);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Output(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(1);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Get_Status_Output(ch), FALSE);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 8 : output start/stop test");
}

void ct_dd_audio_three_041(CtDdAudioThree *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_DMA	dma;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Input(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);

	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_4;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sCmmn(ch, &i2sCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_I2sIn(ch, &i2sIn);

	i2sIn.mode_in = E_DD_AUDIO_MODE_L_JUST;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sIn(ch, &i2sIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);

	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_MONO;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(ch, &ctrlCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Input(ch, &ctrlIn);

	ctrlIn.format		= E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlIn.fifo_stages	= E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format	= E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlIn.bit_shift	= E_DD_AUDIO_BIT_SHIFT_0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Input(ch, &ctrlIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaIn(ch, &dma);

	dma.dma_2ch			= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt	= 0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaIn(ch, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUIDLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	// ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Input_Audio_Async(0,
		D_DD_HDMAC0_IS_IDREQ_0,
		Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
		CtDdAudio_CT_DD_Audio_WORK_AREA,
		(800 * 2),
		(VP_CALLBACK)ctDdAudioDmaIntHandler041_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Input(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(1200);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Input(ch), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}

	Dd_HDMAC0_Close(0);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(ch), D_DDIM_OK);

	CtDdAudio *testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 41 : Record(1000ms) DMA 1ch mode test");
}

CtDdAudioThree *ct_dd_audio_three_new(kpointer *temp, kuint8 ch)
{
    CtDdAudioThree *self = k_object_new_with_private(CT_TYPE_DD_AUDIO_THREE, sizeof(CtDdAudioThreePrivate));
    if(!temp)
    {
         *temp = (kpointer)self;
    }
    self->ch = ch;
    return self;
}
