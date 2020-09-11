/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree1类
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
#include "ctddaudiothree1.h"
#include "ctddaudiovariable.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdAudioThree1, ct_dd_audio_three1);
#define CT_DD_AUDIO_THREE1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdAudioThree1Private,CT_TYPE_DD_AUDIO_THREE1))

struct _CtDdAudioThree1Private
{
};

//变量
static kuint32 S_CT_TEST_LOG[100] = {0};
static kuint32 S_CT_TEST_POS = 0;
/*
*DECLS
*/
static void 	ct_dd_audio_three1_constructor(CtDdAudioThree1 *self);
static void 	ct_dd_audio_three1_destructor(CtDdAudioThree1 *self);
static void 	ctDdAudioDmaIntHandler0420_cb( void );
static void 	ctDdAudioDmaIntHandler0421_cb( void );
static void 	ctDdAudioDmaIntHandler0430_cb( void );
static void 	ctDdAudioDmaIntHandler0431_cb( void );
static void 	ctDdAudioDmaIntHandler0432_cb( void );
static void 	ctDdAudioDmaIntHandler0433_cb( void );
static void 	ctDdAudioDmaIntHandler044_cb( void );
static void 	ctDdAudioDmaIntHandler045_cb( void );
static void 	ctDdAudioDmaIntHandler046_cb( void );
static void 	ctDdAudioDmaIntHandler047_cb( void );
/*
 * IMPL
 */
static void ct_dd_audio_three1_constructor(CtDdAudioThree1 *self) 
{
}

static void ct_dd_audio_three1_destructor(CtDdAudioThree1 *self) 
{
}
//回调方法
static void ctDdAudioDmaIntHandler0420_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 10) {

		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_0,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
									 CtDdAudio_CT_DD_Audio_WORK_AREA+(800*2*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
									 (800*2),
									 (VP_CALLBACK)ctDdAudioDmaIntHandler0420_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler0420_cb\n"));
}

static void ctDdAudioDmaIntHandler0421_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 10) {

		Dd_HDMAC0_Input_Audio_Async( 1,
									 D_DD_HDMAC0_IS_IDREQ_12,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
									 CtDdAudio_CT_DD_Audio_WORK_AREA+(800*2*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
									 (800*2),
									 (VP_CALLBACK)ctDdAudioDmaIntHandler0421_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler0421_cb\n"));
}

static void ctDdAudioDmaIntHandler0430_cb( void )
{
	kuint8 ch = 0;

	// ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 10) {

		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_0,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
									 CtDdAudio_CT_DD_Audio_WORK_AREA+(4800*2*2*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
									 (4800*2*2),
									 (VP_CALLBACK)ctDdAudioDmaIntHandler0430_cb);
	}

//	Ddim_Print(("ctDdAudioDmaIntHandler0430_cb\n"));

	S_CT_TEST_LOG[S_CT_TEST_POS] = 1;
	S_CT_TEST_POS++;
}

static void ctDdAudioDmaIntHandler0431_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 10) {

		Dd_HDMAC0_Input_Audio_Async( 1,
									 D_DD_HDMAC0_IS_IDREQ_12,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
									 CtDdAudio_CT_DD_Audio_WORK_AREA+(4800*2*2*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
									 (4800*2*2),
									 (VP_CALLBACK)ctDdAudioDmaIntHandler0431_cb);
	}

//	Ddim_Print(("ctDdAudioDmaIntHandler0431_cb\n"));

	S_CT_TEST_LOG[S_CT_TEST_POS] = 2;
	S_CT_TEST_POS++;

}

static void ctDdAudioDmaIntHandler0432_cb( void )
{
	kuint8 ch = 1;

	ct_dd_audio_set_dma_int_cnt1(ct_dd_audio_variable_new(),ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new()) + 1);
	if(ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new()) < 10) {

		Dd_HDMAC0_Input_Audio_Async( 2,
									 D_DD_HDMAC0_IS_IDREQ_2,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
									 CtDdAudio_CT_DD_Audio_WORK_AREA2+(4800*2*2*ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new())),
									 (4800*2*2),
									 (VP_CALLBACK)ctDdAudioDmaIntHandler0432_cb);
	}

//	Ddim_Print(("ctDdAudioDmaIntHandler0432_cb\n"));

	S_CT_TEST_LOG[S_CT_TEST_POS] = 3;
	S_CT_TEST_POS++;

}

static void ctDdAudioDmaIntHandler0433_cb( void )
{
	kuint8 ch = 1;

	ct_dd_audio_set_dma_int_cnt1(ct_dd_audio_variable_new(),ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new()) + 1);
	if(ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new()) < 10) {

		Dd_HDMAC0_Input_Audio_Async( 3,
									 D_DD_HDMAC0_IS_IDREQ_14,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
									 CtDdAudio_CT_DD_Audio_WORK_AREA2+(4800*2*2*ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new())),
									 (4800*2*2),
									 (VP_CALLBACK)ctDdAudioDmaIntHandler0433_cb);
	}

//	Ddim_Print(("ctDdAudioDmaIntHandler0433_cb\n"));

	S_CT_TEST_LOG[S_CT_TEST_POS] = 4;
	S_CT_TEST_POS++;

}

static void ctDdAudioDmaIntHandler044_cb( void )
{
	kuint8 ch = 0;

	// ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 10) {
		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_0,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
									 CtDdAudio_CT_DD_Audio_WORK_AREA+(800*2*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
									 (800*2),
									 (VP_CALLBACK)ctDdAudioDmaIntHandler044_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler044_cb\n"));
}

static void ctDdAudioDmaIntHandler045_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 40) {
		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_0,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
									 CtDdAudio_CT_DD_Audio_WORK_AREA+(800*2*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
									 (800*2),
									 (VP_CALLBACK)ctDdAudioDmaIntHandler045_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler045_cb\n"));
}

static void ctDdAudioDmaIntHandler046_cb( void )
{
	kuint8 ch = 0;

	// ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 20) {
		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_0,
									 Dd_Audio_Get_Addr_Reg_AUIDDMAPT(ch),
									 CtDdAudio_CT_DD_Audio_WORK_AREA+(800*4*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
									 (800*4),
									 (VP_CALLBACK)ctDdAudioDmaIntHandler046_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler046_cb\n"));
}

static void ctDdAudioDmaIntHandler047_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 10) {

		Dd_HDMAC0_Output_Audio_Async(0,
									 D_DD_HDMAC0_IS_IDREQ_1,
									 CtDdAudio_CT_DD_Audio_WORK_AREA+(800*2*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
									 Dd_Audio_Get_Addr_Reg_AUODLR(ch),
									 (800*2),
									 (VP_CALLBACK)ctDdAudioDmaIntHandler047_cb);

		if (IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF == 1){
			Ddim_Print(("underflow\n"));
		}
	}

	Ddim_Print(("ctDdAudioDmaIntHandler047_cb\n"));
}
/*
 * PUBLIC
 */
void ct_dd_audio_three1_042(CtDdAudioThree1 *self)
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

	if(Dd_HDMAC0_Open(1, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch1)\n"));
	}

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);

	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_4;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_8;
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

	dma.dma_2ch			= D_DD_AUDIO_ENABLE;
	dma.dma_trnsf_cnt	= 400;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaIn(ch, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUIDLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	// ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_0,
								Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
								CtDdAudio_CT_DD_Audio_WORK_AREA,
								(800*2),
								(VP_CALLBACK)ctDdAudioDmaIntHandler0420_cb);
	// ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	Dd_HDMAC0_Input_Audio_Async(1,
								D_DD_HDMAC0_IS_IDREQ_12,
								Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
								CtDdAudio_CT_DD_Audio_WORK_AREA + (800*2*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
								(800*2),
								(VP_CALLBACK)ctDdAudioDmaIntHandler0421_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Input(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(1200);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Input(ch), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}

	if(Dd_HDMAC0_Stop(1) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch1)\n"));
	}

	Dd_HDMAC0_Close(0);
	Dd_HDMAC0_Close(1);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 42 : Record(1000ms) DMA 2ch mode test");
}

void ct_dd_audio_three1_043(CtDdAudioThree1 *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_DMA	dma;

	S_CT_TEST_POS = 0;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Input(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Input(1, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}

	if(Dd_HDMAC0_Open(1, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch1)\n"));
	}

	if(Dd_HDMAC0_Open(2, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch2)\n"));
	}

	if(Dd_HDMAC0_Open(3, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch3)\n"));
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

	i2sIn.mode_in = E_DD_AUDIO_MODE_L_JUST;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sIn(ch, &i2sIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_I2sIn(1, &i2sIn);

	i2sIn.mode_in = E_DD_AUDIO_MODE_L_JUST;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sIn(1, &i2sIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);

	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_STEREO;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(ch, &ctrlCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Common(1, &ctrlCommon);

	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_STEREO;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(1, &ctrlCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Input(ch, &ctrlIn);

	ctrlIn.format		= E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlIn.fifo_stages	= E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format	= E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlIn.bit_shift	= E_DD_AUDIO_BIT_SHIFT_0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Input(ch, &ctrlIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Input(1, &ctrlIn);

	ctrlIn.format		= E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlIn.fifo_stages	= E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format	= E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlIn.bit_shift	= E_DD_AUDIO_BIT_SHIFT_0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Input(1, &ctrlIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaIn(ch, &dma);

	dma.dma_2ch			= D_DD_AUDIO_ENABLE;
	dma.dma_trnsf_cnt	= 4800;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaIn(ch, &dma), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaIn(1, &dma);

	dma.dma_2ch			= D_DD_AUDIO_ENABLE;
	dma.dma_trnsf_cnt	= 4800;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaIn(1, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUIDLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUIDLR(1, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	// ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	// ct_dd_audio_set_dma_int_cnt1(ct_dd_audio_variable_new(),0);
	ct_dd_audio_set_dma_int_cnt1(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_0,
								Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
								CtDdAudio_CT_DD_Audio_WORK_AREA,
								(4800*2*2),
								(VP_CALLBACK)ctDdAudioDmaIntHandler0430_cb);
	// ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(), ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	Dd_HDMAC0_Input_Audio_Async(1,
								D_DD_HDMAC0_IS_IDREQ_12,
								Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
								CtDdAudio_CT_DD_Audio_WORK_AREA + (4800*2*2*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
								(4800*2*2),
								(VP_CALLBACK)ctDdAudioDmaIntHandler0431_cb);

	Dd_HDMAC0_Input_Audio_Async(2,
								D_DD_HDMAC0_IS_IDREQ_2,
								Dd_Audio_Get_Addr_Reg_AUIDLR(1),
								CtDdAudio_CT_DD_Audio_WORK_AREA2,
								(4800*2*2),
								(VP_CALLBACK)ctDdAudioDmaIntHandler0432_cb);
	ct_dd_audio_set_dma_int_cnt1(ct_dd_audio_variable_new(),ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new()) + 1);
	Dd_HDMAC0_Input_Audio_Async(3,
								D_DD_HDMAC0_IS_IDREQ_14,
								Dd_Audio_Get_Addr_Reg_AUIDLR(1),
								CtDdAudio_CT_DD_Audio_WORK_AREA2 + (4800*2*2*ct_dd_audio_get_dma_int_cnt1(ct_dd_audio_variable_new())),
								(4800*2*2),
								(VP_CALLBACK)ctDdAudioDmaIntHandler0433_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(1, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Input(D_DD_AUDIO_IF_CH0_CH1), D_DDIM_OK);

	DDIM_User_Dly_Tsk(1200);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Input(D_DD_AUDIO_IF_CH0_CH1), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(1, D_DD_AUDIO_DISABLE), D_DDIM_OK);

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

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(ch), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(1), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 43 : Record(1000ms) DMA 4ch mode test");
}

void ct_dd_audio_three1_044(CtDdAudioThree1 *self)
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
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_8;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_32;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sCmmn(ch, &i2sCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_I2sIn(ch, &i2sIn);

	i2sIn.mode_in = E_DD_AUDIO_MODE_L_JUST;
	i2sIn.bit_in = E_DD_AUDIO_BIT_8BIT;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sIn(ch, &i2sIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);

	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_MONO;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(ch, &ctrlCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Input(ch, &ctrlIn);

	ctrlIn.format		= E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
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
								(800*2),
								(VP_CALLBACK)ctDdAudioDmaIntHandler044_cb);

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

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 44 : Record(1000ms) 8bit/sample test");
}

void ct_dd_audio_three1_045(CtDdAudioThree1 *self)
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

	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_2;
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
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_STEREO;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(ch, &ctrlCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Input(ch, &ctrlIn);

	ctrlIn.format		= E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
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
								(800*2),
								(VP_CALLBACK)ctDdAudioDmaIntHandler045_cb);

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

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 45 : Record(1000ms) 16bit/sample test");
}

void ct_dd_audio_three1_046(CtDdAudioThree1 *self)
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

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_0,
								Dd_Audio_Get_Addr_Reg_AUIDDMAPT(ch),
								CtDdAudio_CT_DD_Audio_WORK_AREA,
								(800*4),
								(VP_CALLBACK)ctDdAudioDmaIntHandler046_cb);

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

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 46 : Record(1000ms) 24bit/sample test");
}

void ct_dd_audio_three1_047(CtDdAudioThree1 *self)
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

	Dd_Audio_Get_Ctrl_I2sOut(ch, &i2sOut);

	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.fs = E_DD_AUDIO_FS_64FS;

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

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUODLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Output_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_1,
								CtDdAudio_CT_DD_Audio_WORK_AREA,
								Dd_Audio_Get_Addr_Reg_AUODLR(ch),
								(800*2),
								(VP_CALLBACK)ctDdAudioDmaIntHandler047_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Output(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(1200);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Output(ch), D_DDIM_OK);

	Dd_HDMAC0_Close(0);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 47 : Play(1000ms) DMA 1ch mode test");
}

CtDdAudioThree1* ct_dd_audio_three1_new(kpointer *temp, kuint8 ch) 
{
    CtDdAudioThree1 *self = k_object_new_with_private(CT_TYPE_DD_AUDIO_THREE1, sizeof(CtDdAudioThree1Private));
    if(!temp)
    {
         *temp = (kpointer)self;
    }
    self->ch = ch;
    return self;
}
