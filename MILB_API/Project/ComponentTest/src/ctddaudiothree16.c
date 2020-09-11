/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtDdAudioThree16类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
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
#include "ctddaudiothree1.h"
#include "ctddaudiothree2.h"
#include "ctddaudiothree3.h"
#include "ctddaudiothree4.h"
#include "ctddaudiothree5.h"
#include "ctddaudiothree6.h"
#include "ctddaudiothree7.h"
#include "ctddaudiothree8.h"
#include "ctddaudiothree9.h"
#include "ctddaudiothree10.h"
#include "ctddaudiothree11.h"
#include "ctddaudiothree12.h"
#include "ctddaudiothree13.h"
#include "ctddaudiothree14.h"
#include "ctddaudiothree15.h"
#include "ctddaudiothree16.h"
#include "ctddaudiovariable.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdAudioThree16, ct_dd_audio_three16);
#define CT_DD_AUDIO_THREE16_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtDdAudioThree16Private,CT_TYPE_DD_AUDIO_THREE16))

struct _CtDdAudioThree16Private
{
};

/*
*DECLS
*/
static void 	ct_dd_audio_three16_constructor(CtDdAudioThree16 *self);
static void 	ct_dd_audio_three16_destructor(CtDdAudioThree16 *self);
static void	 	ctDdAudioDmaIntHandler130_cb( void );
static void 	ctDdAudioDmaIntHandler131P00_cb( void );
static void 	ctDdAudioDmaIntHandler131P01_cb( void );
static void 	ctDdAudioDmaIntHandler131P10_cb( void );
static void 	ctDdAudioDmaIntHandler131P11_cb( void );
static void 	ctDdAudioDmaIntHandlerHdmi_cb( void );
/*
 * IMPL
 */
static void ct_dd_audio_three16_constructor(CtDdAudioThree16 *self) 
{
}

static void ct_dd_audio_three16_destructor(CtDdAudioThree16 *self) 
{
}

static void ctDdAudioDmaIntHandler130_cb( void )
{
	kuint8 ch = 5;
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);

	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 10) {
		Dd_HDMAC0_Input_Audio_Async( 0,
			 D_DD_HDMAC0_IS_IDREQ_10,
			 Dd_Audio_Get_Addr_Reg_AUIDDMAPT(ch),
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(2400 * 2 * 2 * ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
			 (2400 * 2 * 2),
			 (VP_CALLBACK)ctDdAudioDmaIntHandler130_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler130_cb \n"));
}

static void ctDdAudioDmaIntHandler131P00_cb( void )
{
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);

	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 100) {
		Dd_HDMAC0_Input_Audio_Async( 0,
			 D_DD_HDMAC0_IS_IDREQ_8,
			 Dd_Audio_Get_Addr_Reg_AUIDLR(4),
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(0x4B00 * ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
			 0x4B00,
			 (VP_CALLBACK)ctDdAudioDmaIntHandler131P00_cb);
	}

	Ddim_Print(("%s\n", __FUNCTION__));
}

static void ctDdAudioDmaIntHandler131P01_cb( void )
{
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);

	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 100) {
		Dd_HDMAC0_Input_Audio_Async( 1,
			 D_DD_HDMAC0_IS_IDREQ_20,
			 Dd_Audio_Get_Addr_Reg_AUIDLR(4),
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(0x4B00 * ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
			 0x4B00,
			 (VP_CALLBACK)ctDdAudioDmaIntHandler131P01_cb);
	}

	Ddim_Print(("%s\n", __FUNCTION__));
}

static void ctDdAudioDmaIntHandler131P10_cb( void )
{
	ct_dd_audio_set_dma_int_cnt1(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new()) + 1);

	if(ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new()) < 100) {
		Dd_HDMAC0_Input_Audio_Async( 2,
			 D_DD_HDMAC0_IS_IDREQ_10,
			 Dd_Audio_Get_Addr_Reg_AUIDLR(5),
			 CtDdAudio_CT_DD_Audio_WORK_AREA2+(0x4B00*ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new())),
			 0x4B00,
			 (VP_CALLBACK)ctDdAudioDmaIntHandler131P10_cb);
	}

	Ddim_Print(("%s\n", __FUNCTION__));
}

static void ctDdAudioDmaIntHandler131P11_cb( void )
{
	ct_dd_audio_set_dma_int_cnt1(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new()) + 1);

	if(ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new()) < 100) {
		Dd_HDMAC0_Input_Audio_Async( 3,
			 D_DD_HDMAC0_IS_IDREQ_22,
			 Dd_Audio_Get_Addr_Reg_AUIDLR(5),
			 CtDdAudio_CT_DD_Audio_WORK_AREA2+(0x4B00*ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new())),
			 0x4B00,
			 (VP_CALLBACK)ctDdAudioDmaIntHandler131P11_cb);
	}

	Ddim_Print(("%s\n", __FUNCTION__));
}

static void ctDdAudioDmaIntHandlerHdmi_cb( void )
{
	kuint8 ch = 1;

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 10) {
		Dd_HDMAC0_Output_Audio_Async(2,
			 D_DD_HDMAC0_IS_IDREQ_7,
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(4800 * 2 * ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
			 Dd_Audio_Get_Addr_Reg_AUODLR(ch),
			 (4800 * 2),
			 (VP_CALLBACK)ctDdAudioDmaIntHandlerHdmi_cb);

		if (IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF == 1){
			Ddim_Print(("underflow\n"));
		}
	}

	Ddim_Print(("ctDdAudioDmaIntHandlerHdmi_cb\n"));
}
/*
 * PUBLIC
 */
void ct_dd_audio_3_130(CtDdAudioThree16 *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_DMA	dma;
	T_DD_PDM_CORE_CFG pdm_cfg;
	T_DD_PDM_DMA_CFG pdm_dma_cfg;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	/* Select PDM CLK */
	Dd_Top_Set_CLKSEL7_PDM1SEL(4);
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Dd_Pdm_Init();

	if(Dd_Pdm_Open(1, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}

	Dd_Pdm_Get_Ctrl_Core(1, &pdm_cfg);

	pdm_cfg.mclk_div = 8;
	pdm_cfg.sinc_rate = 16;
	pdm_cfg.pga_r = 0;
	pdm_cfg.pga_l = 0;

	Dd_Pdm_Ctrl_Core(1, &pdm_cfg);

	Dd_Pdm_Get_Ctrl_Dma(1, &pdm_dma_cfg);

	pdm_dma_cfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_STEREO;
	pdm_dma_cfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_24;

	Dd_Pdm_Ctrl_Dma(1, &pdm_dma_cfg);

	Dd_Pdm_Start_Streaming(1);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Input(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);

	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sCmmn(ch, &i2sCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_I2sIn(ch, &i2sIn);

	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	i2sIn.bit_in = E_DD_AUDIO_BIT_24BIT;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sIn(ch, &i2sIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);

	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_STEREO;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(ch, &ctrlCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Input(ch, &ctrlIn);

	ctrlIn.format		= E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifo_stages	= E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format	= E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlIn.bit_shift	= E_DD_AUDIO_BIT_SHIFT_0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Input(ch, &ctrlIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaIn(ch, &dma);

	dma.dma_2ch			= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt	= 0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaIn(ch, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUIDLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Input_Audio_Async(0,
		D_DD_HDMAC0_IS_IDREQ_10,
		Dd_Audio_Get_Addr_Reg_AUIDDMAPT(ch),
		CtDdAudio_CT_DD_Audio_WORK_AREA,
		(2400 * 2 * 2),
		(VP_CALLBACK)ctDdAudioDmaIntHandler130_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Input(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(3000);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Input(ch), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}

	Dd_HDMAC0_Close(0);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(ch), D_DDIM_OK);

	Dd_Pdm_Stop_Streaming(1);
	Dd_Pdm_Close(1);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 130 : Record(1000ms) PDM test");
}

void ct_dd_audio_3_131(CtDdAudioThree16 *self)
{
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_DMA	dma;
	T_DD_PDM_CORE_CFG pdm_cfg;
	T_DD_PDM_DMA_CFG pdm_dma_cfg;

	CtDdAudio *temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	/* Select PDM CLK */
	Dd_Top_Set_CLKSEL7_PDM0SEL(4);
	Dd_Top_Set_CLKSEL7_PDM1SEL(4);
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Dd_Pdm_Init();

	if(Dd_Pdm_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	if(Dd_Pdm_Open(1, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}

	Dd_Pdm_Get_Ctrl_Core(0, &pdm_cfg);

	pdm_cfg.mclk_div = 8;
	pdm_cfg.sinc_rate = 16;
	pdm_cfg.pga_r = 0;
	pdm_cfg.pga_l = 0;

	Dd_Pdm_Ctrl_Core(0, &pdm_cfg);
	Dd_Pdm_Ctrl_Core(1, &pdm_cfg);

	Dd_Pdm_Get_Ctrl_Dma(0, &pdm_dma_cfg);

	pdm_dma_cfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_STEREO;
	pdm_dma_cfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;

	Dd_Pdm_Ctrl_Dma(0, &pdm_dma_cfg);
	Dd_Pdm_Ctrl_Dma(1, &pdm_dma_cfg);

	Dd_Pdm_Start_Streaming(0);
	Dd_Pdm_Start_Streaming(1);

	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	Dd_Audio_Open_Input(5, D_DDIM_USER_SEM_WAIT_FEVR);

	Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR);
	Dd_HDMAC0_Open(1, D_DDIM_USER_SEM_WAIT_FEVR);
	Dd_HDMAC0_Open(2, D_DDIM_USER_SEM_WAIT_FEVR);
	Dd_HDMAC0_Open(3, D_DDIM_USER_SEM_WAIT_FEVR);

	Dd_Audio_Init();

	// sampling rate 48kHz
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);

	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sCmmn(5, &i2sCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_I2sIn(4, &i2sIn);

	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sIn(4, &i2sIn), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sIn(5, &i2sIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Common(4, &ctrlCommon);

	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_STEREO;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(4, &ctrlCommon), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(5, &ctrlCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Input(4, &ctrlIn);

	ctrlIn.format		= E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifo_stages	= E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format	= E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlIn.bit_shift	= E_DD_AUDIO_BIT_SHIFT_0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Input(4, &ctrlIn), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Input(5, &ctrlIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaIn(4, &dma);

	dma.dma_2ch			= D_DD_AUDIO_ENABLE;
	dma.dma_trnsf_cnt	= 0x4800;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaIn(4, &dma), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaIn(5, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUIDLR(4, D_DD_AUDIO_ENABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUIDLR(5, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),1);
	// ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new()) = 1;
	ct_dd_audio_set_dma_int_cnt1(ct_dd_audio_variable_new(),1);

	Dd_HDMAC0_Input_Audio_Async(0,
		D_DD_HDMAC0_IS_IDREQ_8,
		Dd_Audio_Get_Addr_Reg_AUIDLR(4),
		CtDdAudio_CT_DD_Audio_WORK_AREA,
		0x4B00,
		(VP_CALLBACK)ctDdAudioDmaIntHandler131P00_cb);

	Dd_HDMAC0_Input_Audio_Async(1,
		D_DD_HDMAC0_IS_IDREQ_20,
		Dd_Audio_Get_Addr_Reg_AUIDLR(4),
		CtDdAudio_CT_DD_Audio_WORK_AREA+(0x4B00),
		0x4B00,
		(VP_CALLBACK)ctDdAudioDmaIntHandler131P01_cb);

	Dd_HDMAC0_Input_Audio_Async(2,
		D_DD_HDMAC0_IS_IDREQ_10,
		Dd_Audio_Get_Addr_Reg_AUIDLR(5),
		CtDdAudio_CT_DD_Audio_WORK_AREA2,
		0x4B00,
		(VP_CALLBACK)ctDdAudioDmaIntHandler131P10_cb);

	Dd_HDMAC0_Input_Audio_Async(3,
		D_DD_HDMAC0_IS_IDREQ_22,
		Dd_Audio_Get_Addr_Reg_AUIDLR(5),
		CtDdAudio_CT_DD_Audio_WORK_AREA2+(0x4B00),
		0x4B00,
		(VP_CALLBACK)ctDdAudioDmaIntHandler131P11_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_ENABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(5, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Input(D_DD_AUDIO_IF_CH4_CH5), D_DDIM_OK);

	DDIM_User_Dly_Tsk(11000);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Input(D_DD_AUDIO_IF_CH4_CH5), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_DISABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(5, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}

	if(Dd_HDMAC0_Stop(1) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch1)\n"));
	}

	if(Dd_HDMAC0_Stop(2) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch2)\n"));
	}

	if(Dd_HDMAC0_Stop(3) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch3)\n"));
	}

	Dd_HDMAC0_Close(0);
	Dd_HDMAC0_Close(1);
	Dd_HDMAC0_Close(2);
	Dd_HDMAC0_Close(3);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(4), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(5), D_DDIM_OK);

	Dd_Pdm_Stop_Streaming(0);
	Dd_Pdm_Stop_Streaming(1);
	Dd_Pdm_Close(0);
	Dd_Pdm_Close(1);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, 17);
    ct_dd_audio_test_fin(testFin, "> audio 131 : Record(10000ms) PDM0/PDM Sync test");
	printf("> PDM0 Data. Addr: 0x7C000000, Size: 0x1D4C00\n");
	printf("> PDM1 Data. Addr: 0x7D000000, Size: 0x1D4C00\n");
}

void ct_dd_audio_3_hdmi(CtDdAudioThree16 *self)
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

	if(Dd_HDMAC0_Open(2, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch2)\n"));
	}

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);

	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_8;
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

	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_1;
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

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Output_Audio_Async(2,
		D_DD_HDMAC0_IS_IDREQ_7,
		CtDdAudio_CT_DD_Audio_WORK_AREA,
		Dd_Audio_Get_Addr_Reg_AUODLR(ch),
		(4800 * 2),
		(VP_CALLBACK)ctDdAudioDmaIntHandlerHdmi_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Output(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(1200);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(2) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch2)\n"));
	}

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Output(ch), D_DDIM_OK);

	Dd_HDMAC0_Close(2);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio hdmi : Play(1000ms) DMA 1ch mode test");
}

CtDdAudioThree16 *ct_dd_audio_three16_new(kpointer *temp, kuint8 ch)
{
    CtDdAudioThree16 *self = k_object_new_with_private(CT_TYPE_DD_AUDIO_THREE16, sizeof(CtDdAudioThree16Private));
    if(!temp)
    {
         *temp = (kpointer)self;
    }
    self->ch = ch;
    return self;
}
