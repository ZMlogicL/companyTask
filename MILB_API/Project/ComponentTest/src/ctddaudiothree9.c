/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree9类
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
#include "ctddaudiovariable.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdAudioThree9, ct_dd_audio_three9);
#define CT_DD_AUDIO_THREE9_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtDdAudioThree9Private,CT_TYPE_DD_AUDIO_THREE9))

struct _CtDdAudioThree9Private
{
};

/*
*DECLS
*/
static void 	ct_dd_audio_three9_constructor(CtDdAudioThree9 *self);
static void 	ct_dd_audio_three9_destructor(CtDdAudioThree9 *self);
static void 	ctDdAudioDmaIntHandler094_cb(void);
static void 	ctDdAudioDmaIntHandler095_cb(void);
static void 	ctDdAudioDmaIntHandler096In_cb( void );
static void 	ctDdAudioDmaIntHandler096Out_cb( void );
static void 	ctDdAudioDmaIntHandler097In_cb( void );
static void 	ctDdAudioDmaIntHandler097Out_cb( void );
static void 	ctDdAudioDmaIntHandler098In_cb( void );
static void 	ctDdAudioDmaIntHandler098Out_cb( void );
/*
 * IMPL
 */
static void ct_dd_audio_three9_constructor(CtDdAudioThree9 *self) 
{
}

static void ct_dd_audio_three9_destructor(CtDdAudioThree9 *self) 
{
}

static void ctDdAudioDmaIntHandler094_cb(void)
{
	kuint8 ch = 0;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableInOverFlowIntr(ch, D_DD_AUDIO_DISABLE, NULL), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Input(ch), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_InputDMARequestEnable(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(ch), D_DDIM_OK);
	Ddim_Print(("ctDdAudioDmaIntHandler094_cb\n"));
}

static void ctDdAudioDmaIntHandler095_cb(void)
{
	kuint8 ch = 0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableOutUnderFlowIntr(ch, D_DD_AUDIO_DISABLE, NULL), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Output(ch), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);
	Ddim_Print(("ctDdAudioDmaIntHandler095_cb\n"));
}

static void ctDdAudioDmaIntHandler096In_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt_in(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt_in(ct_dd_audio_variable_new()) + 1);
	if(ct_dd_audio_get_dma_int_cnt_in(ct_dd_audio_variable_new()) < 10) {
		Dd_HDMAC0_Input_Audio_Async( 0,
			 D_DD_HDMAC0_IS_IDREQ_0,
			 Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
			 CtDdAudio_CT_DD_Audio_WORK_AREA2+(800 * 2 * ct_dd_audio_get_dma_int_cnt_in(ct_dd_audio_variable_new())),
			 (800 * 2),
			 (VP_CALLBACK)ctDdAudioDmaIntHandler096In_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler096In_cb\n"));
}

static void ctDdAudioDmaIntHandler096Out_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt_out(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt_out(ct_dd_audio_variable_new()) + 1);
	if(ct_dd_audio_get_dma_int_cnt_out(ct_dd_audio_variable_new()) < 10) {
		Dd_HDMAC0_Output_Audio_Async(2,
			 D_DD_HDMAC0_IS_IDREQ_1,
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(800 * 2 * ct_dd_audio_get_dma_int_cnt_out(ct_dd_audio_variable_new())),
			 Dd_Audio_Get_Addr_Reg_AUODLR(ch),
			 (800 * 2),
			 (VP_CALLBACK)ctDdAudioDmaIntHandler096Out_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler096Out_cb\n"));
}

static void ctDdAudioDmaIntHandler097In_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt_in(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt_in(ct_dd_audio_variable_new()) + 1);
	if(ct_dd_audio_get_dma_int_cnt_in(ct_dd_audio_variable_new()) < 10) {
		Dd_HDMAC0_Input_Audio_Async( 0,
			 D_DD_HDMAC0_IS_IDREQ_0,
			 Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
			 CtDdAudio_CT_DD_Audio_WORK_AREA2+(800 * 2 * ct_dd_audio_get_dma_int_cnt_in(ct_dd_audio_variable_new())),
			 (800 * 2),
			 (VP_CALLBACK)ctDdAudioDmaIntHandler097In_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler097In_cb\n"));
}

static void ctDdAudioDmaIntHandler097Out_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt_out(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt_out(ct_dd_audio_variable_new()) + 1);
	if(ct_dd_audio_get_dma_int_cnt_out(ct_dd_audio_variable_new()) < 10) {
		Dd_HDMAC0_Output_Audio_Async(2,
			 D_DD_HDMAC0_IS_IDREQ_1,
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(800 * 2 * ct_dd_audio_get_dma_int_cnt_out(ct_dd_audio_variable_new())),
			 Dd_Audio_Get_Addr_Reg_AUODLR(ch),
			 (800 * 2),
			 (VP_CALLBACK)ctDdAudioDmaIntHandler097Out_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler097Out_cb\n"));
}

static void ctDdAudioDmaIntHandler098In_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt_in(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt_in(ct_dd_audio_variable_new()) + 1);
	if(ct_dd_audio_get_dma_int_cnt_in(ct_dd_audio_variable_new()) < 10) {
		Dd_HDMAC0_Input_Audio_Async( 0,
			 D_DD_HDMAC0_IS_IDREQ_0,
			 Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
			 CtDdAudio_CT_DD_Audio_WORK_AREA2+(800 * 2 * ct_dd_audio_get_dma_int_cnt_in(ct_dd_audio_variable_new())),
			 (800 * 2),
			 (VP_CALLBACK)ctDdAudioDmaIntHandler098In_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler098In_cb\n"));
}

static void ctDdAudioDmaIntHandler098Out_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt_out(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt_out(ct_dd_audio_variable_new()) + 1);
	if(ct_dd_audio_get_dma_int_cnt_out(ct_dd_audio_variable_new()) < 10) {
		Dd_HDMAC0_Output_Audio_Async(2,
			 D_DD_HDMAC0_IS_IDREQ_1,
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(800 * 2 * ct_dd_audio_get_dma_int_cnt_out(ct_dd_audio_variable_new())),
			 Dd_Audio_Get_Addr_Reg_AUODLR(ch),
			 (800 * 2),
			 (VP_CALLBACK)ctDdAudioDmaIntHandler098Out_cb);
	}

	Ddim_Print(("ctDdAudioDmaIntHandler098Out_cb\n"));
}
/*
 * PUBLIC
 */
void ct_dd_audio_three9_094(CtDdAudioThree9 *self)
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

	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_16;
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

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoFullDmaIn(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableInOverFlowIntr(ch,D_DD_AUDIO_ENABLE,
			(T_DD_AUDIO_CALLBACK)ctDdAudioDmaIntHandler094_cb), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Input(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(100);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 94 : [Interrupt Test]OverFlow");
}

void ct_dd_audio_three9_095(CtDdAudioThree9 *self)
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

	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_16;
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_STEREO;

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

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoEmptyDmaOut(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableOutUnderFlowIntr(ch,D_DD_AUDIO_ENABLE,
			(T_DD_AUDIO_CALLBACK)ctDdAudioDmaIntHandler095_cb), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Output(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(100);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 95 : [Interrupt Test]UnderFlow");
}

void ct_dd_audio_three9_096(CtDdAudioThree9 *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_CTRL_OUT	ctrlOut;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_I2S_OUT	i2sOut;
	T_DD_AUDIO_DMA	dma;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Input(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Output(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}

	if(Dd_HDMAC0_Open(2, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch2)\n"));
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

	Dd_Audio_Get_Ctrl_I2sOut(ch, &i2sOut);

	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.fs = E_DD_AUDIO_FS_32FS;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sOut(ch, &i2sOut), D_DDIM_OK);

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

	Dd_Audio_Get_Ctrl_Output(ch, &ctrlOut);

	ctrlOut.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlOut.fifo_stages =  E_DD_AUDIO_FIFO_STAGES_16;
	ctrlOut.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlOut.lr_copy = D_DD_AUDIO_DISABLE;
	ctrlOut.mix_play = D_DD_AUDIO_DISABLE;
	ctrlOut.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Output(ch, &ctrlOut), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaIn(ch, &dma);

	dma.dma_2ch			= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt	= 0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaIn(ch, &dma), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaOut(ch, &dma);

	dma.dma_2ch			= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt	= 0;

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaOut(ch, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUIDLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUODLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	ct_dd_audio_set_dma_int_cnt_in(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Input_Audio_Async(0,
		D_DD_HDMAC0_IS_IDREQ_0,
		Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
		CtDdAudio_CT_DD_Audio_WORK_AREA2,
		(800 * 2),
		(VP_CALLBACK)ctDdAudioDmaIntHandler096In_cb);

	ct_dd_audio_set_dma_int_cnt_out(ct_dd_audio_variable_new(), 0);
	Dd_HDMAC0_Output_Audio_Async(2,
		D_DD_HDMAC0_IS_IDREQ_1,
		CtDdAudio_CT_DD_Audio_WORK_AREA,
		Dd_Audio_Get_Addr_Reg_AUODLR(ch),
		(800 * 2),
		(VP_CALLBACK)ctDdAudioDmaIntHandler096Out_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoFullDmaIn(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoEmptyDmaOut(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Output(ch), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Input(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(1200);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Input(ch), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoFullDmaIn(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoEmptyDmaOut(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}

	if(Dd_HDMAC0_Stop(2) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch2)\n"));
	}

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Output(ch), D_DDIM_OK);

	Dd_HDMAC0_Close(0);

	Dd_HDMAC0_Close(2);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(ch), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 96 : Record 0bit shift test");
}

void ct_dd_audio_three9_097(CtDdAudioThree9 *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_CTRL_OUT	ctrlOut;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_I2S_OUT	i2sOut;
	T_DD_AUDIO_DMA	dma;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Input(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Output(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}

	if(Dd_HDMAC0_Open(2, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch2)\n"));
	}

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_4;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_8;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_32;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sCmmn(ch, &i2sCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_I2sIn(ch, &i2sIn);
	i2sIn.mode_in = E_DD_AUDIO_MODE_L_JUST;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sIn(ch, &i2sIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_I2sOut(ch, &i2sOut);
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.fs = E_DD_AUDIO_FS_32FS;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sOut(ch, &i2sOut), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);
	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_MONO;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(ch, &ctrlCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Input(ch, &ctrlIn);
	ctrlIn.format		= E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlIn.fifo_stages	= E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format	= E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlIn.bit_shift	= E_DD_AUDIO_BIT_SHIFT_1;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Input(ch, &ctrlIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Output(ch, &ctrlOut);
	ctrlOut.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlOut.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlOut.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlOut.lr_copy = D_DD_AUDIO_DISABLE;
	ctrlOut.mix_play = D_DD_AUDIO_DISABLE;
	ctrlOut.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Output(ch, &ctrlOut), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaIn(ch, &dma);
	dma.dma_2ch			= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt	= 0;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaIn(ch, &dma), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaOut(ch, &dma);
	dma.dma_2ch			= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt	= 0;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaOut(ch, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUIDLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUODLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	ct_dd_audio_set_dma_int_cnt_in(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Input_Audio_Async(0,
		D_DD_HDMAC0_IS_IDREQ_0,
		Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
		CtDdAudio_CT_DD_Audio_WORK_AREA2,
		(800 * 2),
		(VP_CALLBACK)ctDdAudioDmaIntHandler097In_cb);

	ct_dd_audio_set_dma_int_cnt_out(ct_dd_audio_variable_new(), 0);
	Dd_HDMAC0_Output_Audio_Async(2,
		D_DD_HDMAC0_IS_IDREQ_1,
		CtDdAudio_CT_DD_Audio_WORK_AREA,
		Dd_Audio_Get_Addr_Reg_AUODLR(ch),
		(800 * 2),
		(VP_CALLBACK)ctDdAudioDmaIntHandler097Out_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoFullDmaIn(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoEmptyDmaOut(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Output(ch), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Input(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(1200);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Input(ch), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoFullDmaIn(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoEmptyDmaOut(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}

	if(Dd_HDMAC0_Stop(2) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch2)\n"));
	}

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Output(ch), D_DDIM_OK);

	Dd_HDMAC0_Close(0);
	Dd_HDMAC0_Close(2);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(ch), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 97 : Record 1bit shift test");
}

void ct_dd_audio_three9_098(CtDdAudioThree9 *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_CTRL_OUT	ctrlOut;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_I2S_OUT	i2sOut;
	T_DD_AUDIO_DMA	dma;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Input(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Output(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}

	if(Dd_HDMAC0_Open(2, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch2)\n"));
	}

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_4;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_8;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_32;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sCmmn(ch, &i2sCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_I2sIn(ch, &i2sIn);
	i2sIn.mode_in = E_DD_AUDIO_MODE_L_JUST;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sIn(ch, &i2sIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_I2sOut(ch, &i2sOut);
	i2sOut.mode_out = E_DD_AUDIO_MODE_L_JUST;
	i2sOut.bit_out = E_DD_AUDIO_BIT_16BIT;
	i2sOut.fs = E_DD_AUDIO_FS_32FS;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_I2sOut(ch, &i2sOut), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Common(ch, &ctrlCommon);
	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_MONO;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Common(ch, &ctrlCommon), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Input(ch, &ctrlIn);
	ctrlIn.format		= E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlIn.fifo_stages	= E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format	= E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlIn.bit_shift	= E_DD_AUDIO_BIT_SHIFT_2;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Input(ch, &ctrlIn), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_Output(ch, &ctrlOut);
	ctrlOut.format = E_DD_AUDIO_DATA_REG_FRMT_R_JUST;
	ctrlOut.fifo_stages =  E_DD_AUDIO_FIFO_STAGES_16;
	ctrlOut.ahb_format = E_DD_AUDIO_AHB_FRMT_R_JUST;
	ctrlOut.lr_copy = D_DD_AUDIO_DISABLE;
	ctrlOut.mix_play = D_DD_AUDIO_DISABLE;
	ctrlOut.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_Output(ch, &ctrlOut), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaIn(ch, &dma);
	dma.dma_2ch			= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt	= 0;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaIn(ch, &dma), D_DDIM_OK);

	Dd_Audio_Get_Ctrl_DmaOut(ch, &dma);
	dma.dma_2ch			= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt	= 0;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaOut(ch, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUIDLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUODLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	ct_dd_audio_set_dma_int_cnt_in(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Input_Audio_Async(0,
		D_DD_HDMAC0_IS_IDREQ_0,
		Dd_Audio_Get_Addr_Reg_AUIDLR(ch),
		CtDdAudio_CT_DD_Audio_WORK_AREA2,
		(800 * 2),
		(VP_CALLBACK)ctDdAudioDmaIntHandler098In_cb);

	ct_dd_audio_set_dma_int_cnt_out(ct_dd_audio_variable_new(), 0);
	Dd_HDMAC0_Output_Audio_Async(2,
		D_DD_HDMAC0_IS_IDREQ_1,
		CtDdAudio_CT_DD_Audio_WORK_AREA,
		Dd_Audio_Get_Addr_Reg_AUODLR(ch),
		(800 * 2),
		(VP_CALLBACK)ctDdAudioDmaIntHandler098Out_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoFullDmaIn(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoEmptyDmaOut(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Output(ch), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Input(ch), D_DDIM_OK);

	DDIM_User_Dly_Tsk(1200);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Input(ch), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoFullDmaIn(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_EnableFifoEmptyDmaOut(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}

	if(Dd_HDMAC0_Stop(2) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch2)\n"));
	}

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Output(ch), D_DDIM_OK);

	Dd_HDMAC0_Close(0);
	Dd_HDMAC0_Close(2);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Input(ch), D_DDIM_OK);
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio 98 : Record 2bit shift test");
}

CtDdAudioThree9 *ct_dd_audio_three9_new(kpointer *temp, kuint8 ch)
{
    CtDdAudioThree9 *self = k_object_new_with_private(CT_TYPE_DD_AUDIO_THREE9, sizeof(CtDdAudioThree9Private));
    if(!temp)
    {
         *temp = (kpointer)self;
    }
    self->ch = ch;
    return self;
}
