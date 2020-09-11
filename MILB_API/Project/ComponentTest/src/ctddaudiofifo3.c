/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtDdAudioFifo3类
*@rely                :klib
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
#include "dd_audio.h"
#include "dd_hdmac0.h"
#include "dd_top.h"
#include "dd_cache.h"
#include "dd_pdm.h"
#include "dd_gic.h"
#include "peripheral.h"
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
#include "ctddaudiofifo.h"
#include "ctddaudiofifo1.h"
#include "ctddaudiofifo2.h"
#include "ctddaudiofifo3.h"
#include "ctddaudiovariable.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdAudioFifo3, ct_dd_audio_fifo3);
#define CT_DD_AUDIO_FIFO3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdAudioFifo3Private,CT_TYPE_DD_AUDIO_FIFO3))

struct _CtDdAudioFifo3Private
{
};

//变量:
static kuint32 S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[2048];
static kuint32 S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[2048];
static kuint32 S_DD_CT_AUDIO_PDM_DMA_INT_CNT0;
static kuint32 S_DD_CT_AUDIO_PDM_DMA_INT_CNT1;
/*
 * DECLS
 */
static void 	ct_dd_audio_fifo3_constructor(CtDdAudioFifo3 *self);
static void 	ct_dd_audio_fifo3_destructor(CtDdAudioFifo3 *self);
static void 	ctDdAudioDmaIntHandlerFifoMonitorPlay0_cb( void );
static void 	ctDdAudioDmaIntHandlerFifoMonitorPlay1_cb( void );
static void 	ctDdAudioDmaIntHandlerFifoMonitorPlay01_cb( void );
static void 	ctDdAudioDmaIntHandlerFifoMonitorPlay11_cb( void );
static void 	ctDdAudioDmaIntHandlerPdm00_cb( void );
static void 	ctDdAudioDmaIntHandlerPdm01_cb( void );
static void 	ctDdAudioDmaIntHandlerPdm10_cb( void );
static void 	ctDdAudioDmaIntHandlerPdm11_cb( void );

/*
 * IMPL
 */
static void ct_dd_audio_fifo3_constructor(CtDdAudioFifo3 *self) 
{
}

static void ct_dd_audio_fifo3_destructor(CtDdAudioFifo3 *self) 
{
}

//回调方法
static void ctDdAudioDmaIntHandlerFifoMonitorPlay0_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 5) {

		Dd_HDMAC0_Output_Audio_Async(2,
			 D_DD_HDMAC0_IS_IDREQ_1,
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(256*4*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
			 Dd_Audio_Get_Addr_Reg_AUODLR(ch),
			 (256 * 4),
			 (VP_CALLBACK)ctDdAudioDmaIntHandlerFifoMonitorPlay0_cb);

		if (IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF == 1){
			Ddim_Print(("underflow\n"));
		}
	}

	Ddim_Print(("ctDdAudioDmaIntHandlerFifoMonitorPlay0_cb\n"));
}
//回调方法
static void ctDdAudioDmaIntHandlerFifoMonitorPlay1_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 5) {

		Dd_HDMAC0_Output_Audio_Async(3,
			 D_DD_HDMAC0_IS_IDREQ_13,
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(256 * 4 * ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
			 Dd_Audio_Get_Addr_Reg_AUODLR(ch),
			 (256 * 4),
			 (VP_CALLBACK)ctDdAudioDmaIntHandlerFifoMonitorPlay1_cb);

		if (IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF == 1){
			Ddim_Print(("underflow\n"));
		}
	}

	Ddim_Print(("ctDdAudioDmaIntHandlerFifoMonitorPlay1_cb\n"));
}
//回调方法
static void ctDdAudioDmaIntHandlerFifoMonitorPlay01_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 5) {

		Dd_HDMAC0_Output_Audio_Async(2,
			 D_DD_HDMAC0_IS_IDREQ_1,
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(240 * 4 * ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
			 Dd_Audio_Get_Addr_Reg_AUODLR(ch),
			 (240 * 4),
			 (VP_CALLBACK)ctDdAudioDmaIntHandlerFifoMonitorPlay01_cb);

		if (IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF == 1){
			Ddim_Print(("underflow\n"));
		}
	}

	Ddim_Print(("ctDdAudioDmaIntHandlerFifoMonitorPlay0_cb\n"));
}
//回调方法
static void ctDdAudioDmaIntHandlerFifoMonitorPlay11_cb( void )
{
	kuint8 ch = 0;

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),
			ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) +1);
	if(ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new()) < 5) {

		Dd_HDMAC0_Output_Audio_Async(3,
			 D_DD_HDMAC0_IS_IDREQ_13,
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(240 * 4 * ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
			 Dd_Audio_Get_Addr_Reg_AUODLR(ch),
			 (240 * 4),
			 (VP_CALLBACK)ctDdAudioDmaIntHandlerFifoMonitorPlay11_cb);

		if (IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF == 1){
			Ddim_Print(("underflow\n"));
		}
	}

	Ddim_Print(("ctDdAudioDmaIntHandlerFifoMonitorPlay1_cb\n"));
}
//回调方法
static void ctDdAudioDmaIntHandlerPdm00_cb( void )
{
	S_DD_CT_AUDIO_PDM_DMA_INT_CNT0++;

	if(S_DD_CT_AUDIO_PDM_DMA_INT_CNT0 < 100) {
		Dd_HDMAC0_Input_Audio_Async( 0,
			 D_DD_HDMAC0_IS_IDREQ_8,
			 Dd_Audio_Get_Addr_Reg_AUIDLR(4),
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(0x4B00 * S_DD_CT_AUDIO_PDM_DMA_INT_CNT0),
			 0x4B00,
			 (VP_CALLBACK)ctDdAudioDmaIntHandlerPdm00_cb);
	}

//	Ddim_Print(("%s\n", __FUNCTION__));
}
//回调方法
static void ctDdAudioDmaIntHandlerPdm01_cb( void )
{
	S_DD_CT_AUDIO_PDM_DMA_INT_CNT0++;

	if(S_DD_CT_AUDIO_PDM_DMA_INT_CNT0 < 100) {
		Dd_HDMAC0_Input_Audio_Async( 1,
			 D_DD_HDMAC0_IS_IDREQ_20,
			 Dd_Audio_Get_Addr_Reg_AUIDLR(4),
			 CtDdAudio_CT_DD_Audio_WORK_AREA+(0x4B00 * S_DD_CT_AUDIO_PDM_DMA_INT_CNT0),
			 0x4B00,
			 (VP_CALLBACK)ctDdAudioDmaIntHandlerPdm01_cb);
	}

//	Ddim_Print(("%s\n", __FUNCTION__));
}
//回调方法
static void ctDdAudioDmaIntHandlerPdm10_cb( void )
{
	S_DD_CT_AUDIO_PDM_DMA_INT_CNT1++;

	if(S_DD_CT_AUDIO_PDM_DMA_INT_CNT1 < 100) {
		Dd_HDMAC0_Input_Audio_Async( 2,
			 D_DD_HDMAC0_IS_IDREQ_10,
			 Dd_Audio_Get_Addr_Reg_AUIDLR(5),
			 CtDdAudio_CT_DD_Audio_WORK_AREA2+(0x4B00*S_DD_CT_AUDIO_PDM_DMA_INT_CNT1),
			 0x4B00,
			 (VP_CALLBACK)ctDdAudioDmaIntHandlerPdm10_cb);
	}

//	Ddim_Print(("%s\n", __FUNCTION__));
}
//回调方法
static void ctDdAudioDmaIntHandlerPdm11_cb( void )
{
	S_DD_CT_AUDIO_PDM_DMA_INT_CNT1++;

	if(S_DD_CT_AUDIO_PDM_DMA_INT_CNT1 < 100) {
		Dd_HDMAC0_Input_Audio_Async( 3,
			 D_DD_HDMAC0_IS_IDREQ_22,
			 Dd_Audio_Get_Addr_Reg_AUIDLR(5),
			 CtDdAudio_CT_DD_Audio_WORK_AREA2+(0x4B00*S_DD_CT_AUDIO_PDM_DMA_INT_CNT1),
			 0x4B00,
			 (VP_CALLBACK)ctDdAudioDmaIntHandlerPdm11_cb);
	}

//	Ddim_Print(("%s\n", __FUNCTION__));
}
/*
 * PUBLIC
 */
void ct_dd_audio_fifo3_monitor_play0_D2(CtDdAudioFifo3 *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_OUT	ctrlOut;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_OUT	i2sOut;
	T_DD_AUDIO_DMA	dma;
	ULONG count;

	CtDdAudio *temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Output(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	if(Dd_HDMAC0_Open(2, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch2)\n"));
	}

	if(Dd_HDMAC0_Open(3, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch3)\n"));
	}

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_32;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_32;
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
	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_1;
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
	dma.dma_2ch			= D_DD_AUDIO_ENABLE;
	dma.dma_trnsf_cnt	= 256;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaOut(ch, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUODLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Output_Audio_Async(2,
		D_DD_HDMAC0_IS_IDREQ_1,
		CtDdAudio_CT_DD_Audio_WORK_AREA,
		Dd_Audio_Get_Addr_Reg_AUODLR(ch),
		(256 * 4),
		(VP_CALLBACK)ctDdAudioDmaIntHandlerFifoMonitorPlay0_cb);

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),1);
	Dd_HDMAC0_Output_Audio_Async(3,
		D_DD_HDMAC0_IS_IDREQ_13,
		CtDdAudio_CT_DD_Audio_WORK_AREA+(256*4*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
		Dd_Audio_Get_Addr_Reg_AUODLR(ch),
		(256 * 4),
		(VP_CALLBACK)ctDdAudioDmaIntHandlerFifoMonitorPlay1_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Output(ch), D_DDIM_OK);

	for (count = 0; count < 2048; count++){
		DDIM_User_Dly_Tsk(0);
		ct_dd_audio_set_gct_dd_audio_fifomonitor(ct_dd_audio_variable_new(),count,IO_AUDIO.AUDIOIF[ch].AUOFST.word);
		S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[count] = IO_HDMAC0.DMAC[2].DMACA.bit.TC;
		S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[count] = IO_HDMAC0.DMAC[3].DMACA.bit.TC;
	}

	DDIM_User_Dly_Tsk(5000);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(2) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch2)\n"));
	}

	if(Dd_HDMAC0_Stop(3) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch2)\n"));
	}

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Output(ch), D_DDIM_OK);

	Dd_HDMAC0_Close(2);
	Dd_HDMAC0_Close(3);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);

	CtDdAudio *testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio play:DMA2ch Fifo Monitor ESTG = 0\n");
	Ddim_Print(("ct_dd_audio_get_gct_dd_audio_fifomonitor(ct_dd_audio_variable_new(), 0)= %lx\n",
			(kulong)ct_dd_audio_get_gct_dd_audio_fifomonitor(ct_dd_audio_variable_new(), 0)));
	Ddim_Print(("S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[0]= %lx\n",
			(kulong)S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[0]));
	Ddim_Print(("S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[0]= %lx\n",
			(kulong)S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[0]));
}

void ct_dd_audio_fifo3_monitor_play1_D2(CtDdAudioFifo3 *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_OUT	ctrlOut;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_OUT	i2sOut;
	T_DD_AUDIO_DMA	dma;
	ULONG count;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Output(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	if(Dd_HDMAC0_Open(2, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch2)\n"));
	}

	if(Dd_HDMAC0_Open(3, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch2)\n"));
	}

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_32;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_32;
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
	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_12;
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
	dma.dma_2ch			= D_DD_AUDIO_ENABLE;
	dma.dma_trnsf_cnt	= 240;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaOut(ch, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUODLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Output_Audio_Async(2,
		D_DD_HDMAC0_IS_IDREQ_1,
		CtDdAudio_CT_DD_Audio_WORK_AREA,
		Dd_Audio_Get_Addr_Reg_AUODLR(ch),
		(240 * 4),
		(VP_CALLBACK)ctDdAudioDmaIntHandlerFifoMonitorPlay01_cb);

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),1);
	Dd_HDMAC0_Output_Audio_Async(3,
		D_DD_HDMAC0_IS_IDREQ_14,
		CtDdAudio_CT_DD_Audio_WORK_AREA+(240*4*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
		Dd_Audio_Get_Addr_Reg_AUODLR(ch),
		(240 * 4),
		(VP_CALLBACK)ctDdAudioDmaIntHandlerFifoMonitorPlay11_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Output(ch), D_DDIM_OK);

	for (count = 0; count < 2048; count++){
		DDIM_User_Dly_Tsk(0);
		ct_dd_audio_set_gct_dd_audio_fifomonitor(ct_dd_audio_variable_new(), count, IO_AUDIO.AUDIOIF[ch].AUOFST.word);
		S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[count] = IO_HDMAC0.DMAC[2].DMACA.bit.TC;
		S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[count] = IO_HDMAC0.DMAC[3].DMACA.bit.TC;
	}

	DDIM_User_Dly_Tsk(9000);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(2) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch2)\n"));
	}

	if(Dd_HDMAC0_Stop(3) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch2)\n"));
	}

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Output(ch), D_DDIM_OK);

	Dd_HDMAC0_Close(2);
	Dd_HDMAC0_Close(3);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio Play:DMA2ch Fifo Monitor ESTG = 1\n");
	Ddim_Print(("ct_dd_audio_get_gct_dd_audio_fifomonitor(ct_dd_audio_variable_new(), 0)= %lx\n",
			(kulong)ct_dd_audio_get_gct_dd_audio_fifomonitor(ct_dd_audio_variable_new(), 0)));
	Ddim_Print(("S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[0]= %lx\n",
			(kulong)S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[0]));
	Ddim_Print(("S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[0]= %lx\n",
			(kulong)S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[0]));
}

void ct_dd_audio_fifo3_monitor_play2_D2(CtDdAudioFifo3 *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_OUT	ctrlOut;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_OUT	i2sOut;
	T_DD_AUDIO_DMA	dma;
	ULONG count;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Output(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	if(Dd_HDMAC0_Open(2, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch2)\n"));
	}

	if(Dd_HDMAC0_Open(3, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch2)\n"));
	}

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_32;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_32;
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
	dma.dma_2ch			= D_DD_AUDIO_ENABLE;
	dma.dma_trnsf_cnt	= 256;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaOut(ch, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUODLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	// ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Output_Audio_Async(2,
		D_DD_HDMAC0_IS_IDREQ_1,
		CtDdAudio_CT_DD_Audio_WORK_AREA,
		Dd_Audio_Get_Addr_Reg_AUODLR(ch),
		(256 * 4),
		(VP_CALLBACK)ctDdAudioDmaIntHandlerFifoMonitorPlay0_cb);

	// ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),1);
	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),1);
	Dd_HDMAC0_Output_Audio_Async(3,
		D_DD_HDMAC0_IS_IDREQ_11,
		CtDdAudio_CT_DD_Audio_WORK_AREA+(256*4*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
		Dd_Audio_Get_Addr_Reg_AUODLR(ch),
		(256 * 4),
		(VP_CALLBACK)ctDdAudioDmaIntHandlerFifoMonitorPlay1_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Output(ch), D_DDIM_OK);

	for (count = 0; count < 2048; count++){
		DDIM_User_Dly_Tsk(0);
		ct_dd_audio_set_gct_dd_audio_fifomonitor(ct_dd_audio_variable_new(), count, IO_AUDIO.AUDIOIF[ch].AUOFST.word);
		S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[count] = IO_HDMAC0.DMAC[2].DMACA.bit.TC;
		S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[count] = IO_HDMAC0.DMAC[3].DMACA.bit.TC;
	}

	DDIM_User_Dly_Tsk(5000);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(2) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch2)\n"));
	}
	if(Dd_HDMAC0_Stop(3) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch2)\n"));
	}

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Output(ch), D_DDIM_OK);

	Dd_HDMAC0_Close(2);
	Dd_HDMAC0_Close(3);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);

	CtDdAudio *testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio Play:DMA2ch Fifo Monitor ESTG = 2\n");
	Ddim_Print(("ct_dd_audio_get_gct_dd_audio_fifomonitor(ct_dd_audio_variable_new(), 0)= %lx\n",
			(kulong)ct_dd_audio_get_gct_dd_audio_fifomonitor(ct_dd_audio_variable_new(), 0)));
	Ddim_Print(("S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[0]= %lx\n",
			(kulong)S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[0]));
	Ddim_Print(("S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[0]= %lx\n",
			(kulong)S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[0]));
}

void ct_dd_audio_fifo3_monitor_play3_D2(CtDdAudioFifo3 *self)
{
	kuint8 ch = self->ch;
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_OUT	ctrlOut;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_OUT	i2sOut;
	T_DD_AUDIO_DMA	dma;
	ULONG count;

	CtDdAudio*temp = ct_dd_audio_new(NULL, 0);
    ct_dd_audio_test_init(temp);
    k_object_unref(temp);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Open_Output(ch, D_DDIM_USER_SEM_WAIT_FEVR), D_DDIM_OK);

	if(Dd_HDMAC0_Open(2, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch2)\n"));
	}

	if(Dd_HDMAC0_Open(3, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch2)\n"));
	}

	Dd_Audio_Init();

	Dd_Audio_Get_Ctrl_I2sCmmn(ch, &i2sCommon);
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_32;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_32;
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
	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_4;
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
	dma.dma_2ch			= D_DD_AUDIO_ENABLE;
	dma.dma_trnsf_cnt	= 256;
	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Ctrl_DmaOut(ch, &dma), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_SwapHW_AUODLR(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),0);
	Dd_HDMAC0_Output_Audio_Async(2,
		D_DD_HDMAC0_IS_IDREQ_1,
		CtDdAudio_CT_DD_Audio_WORK_AREA,
		Dd_Audio_Get_Addr_Reg_AUODLR(ch),
		(256 * 4),
		(VP_CALLBACK)ctDdAudioDmaIntHandlerFifoMonitorPlay0_cb);

	ct_dd_audio_set_dma_int_cnt(ct_dd_audio_variable_new(),1);
	Dd_HDMAC0_Output_Audio_Async(3,
		D_DD_HDMAC0_IS_IDREQ_11,
		CtDdAudio_CT_DD_Audio_WORK_AREA+(256*4*ct_dd_audio_get_dma_int_cnt(ct_dd_audio_variable_new())),
		Dd_Audio_Get_Addr_Reg_AUODLR(ch),
		(256 * 4),
		(VP_CALLBACK)ctDdAudioDmaIntHandlerFifoMonitorPlay1_cb);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_ENABLE), D_DDIM_OK);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Start_Output(ch), D_DDIM_OK);

	for (count = 0; count < 2048; count++){
		DDIM_User_Dly_Tsk(0);
		ct_dd_audio_set_gct_dd_audio_fifomonitor(ct_dd_audio_variable_new(), count, IO_AUDIO.AUDIOIF[ch].AUOFST.word);
		S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[count] = IO_HDMAC0.DMAC[2].DMACA.bit.TC;
		S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[count] = IO_HDMAC0.DMAC[3].DMACA.bit.TC;
	}

	DDIM_User_Dly_Tsk(5000);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Set_OutputDMARequestEnable(ch, D_DD_AUDIO_DISABLE), D_DDIM_OK);

	if(Dd_HDMAC0_Stop(2) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch2)\n"));
	}

	if(Dd_HDMAC0_Stop(3) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch3)\n"));
	}

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Stop_Output(ch), D_DDIM_OK);

	Dd_HDMAC0_Close(2);
	Dd_HDMAC0_Close(3);

	CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(Dd_Audio_Close_Output(ch), D_DDIM_OK);

	CtDdAudio* testFin = ct_dd_audio_new(NULL, ch);
    ct_dd_audio_test_fin(testFin, "> audio Play:DMA2ch Fifo Monitor ESTG = 3\n");
	Ddim_Print(("ct_dd_audio_get_gct_dd_audio_fifomonitor(ct_dd_audio_variable_new(), 0)= %lx\n",
			(kulong)ct_dd_audio_get_gct_dd_audio_fifomonitor(ct_dd_audio_variable_new(), 0)));
	Ddim_Print(("S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[0]= %lx\n",
			(kulong)S_GCT_DD_AUDIO_FIFO_MONITOR_TC0[0]));
	Ddim_Print(("S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[0]= %lx\n",
			(kulong)S_GCT_DD_AUDIO_FIFO_MONITOR_TC1[0]));
}

void ct_dd_audio_fifo3_bit_shift( kuint16* pcm, kuint32 dataBytes )
{
	kuint32 loop;

	for (loop = 0; loop < (dataBytes / 2); loop++){
		*pcm = (*pcm) << 1;
		pcm++;
	}
}

void ct_dd_audio_fifo3_sync_pdm(void)
{
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
	Dd_Top_Set_CLKSEL7_PDM0SEL(4);
	Dd_Top_Set_CLKSEL7_PDM1SEL(4);
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Dd_Pdm_Init();

	Dd_Pdm_Open(0, D_DDIM_USER_SEM_WAIT_FEVR);
	Dd_Pdm_Open(1, D_DDIM_USER_SEM_WAIT_FEVR);

	pdm_cfg.soft_mute = D_DD_PDM_DISABLE;
	pdm_cfg.s_cycle = (E_DD_PDM_CORE_S_CYCLE)1;
	pdm_cfg.hp_cutoff = 0xB;
	pdm_cfg.adc_hpd = D_DD_PDM_DISABLE;
	pdm_cfg.mclk_div = 8;
	pdm_cfg.sinc_rate = 16;
	pdm_cfg.pga_r = 0;
	pdm_cfg.pga_l = 0;
	pdm_cfg.swap = E_DD_PDM_CORE_LR_SWAP_NO_SWAP;

	Dd_Pdm_Ctrl_Core(0, &pdm_cfg);
	Dd_Pdm_Ctrl_Core(1, &pdm_cfg);

	pdm_dma_cfg.dma_en = D_DD_PDM_DISABLE;
	pdm_dma_cfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_STEREO;
	pdm_dma_cfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	pdm_dma_cfg.dma_burstlen = E_DD_PDM_DMA_BURST_LEN_4;
	pdm_dma_cfg.dmick_dly = 0;

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
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;

	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);
	Dd_Audio_Ctrl_I2sCmmn(5, &i2sCommon);

	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;

	Dd_Audio_Ctrl_I2sIn(4, &i2sIn);
	Dd_Audio_Ctrl_I2sIn(5, &i2sIn);

	Dd_Audio_Get_Ctrl_Common(4, &ctrlCommon);

	ctrlCommon.fifo_usage	= E_DD_AUDIO_FIFO_USAGE_STAGES_8;
	ctrlCommon.channel		= E_DD_AUDIO_CHANNEL_STEREO;

	Dd_Audio_Ctrl_Common(4, &ctrlCommon);
	Dd_Audio_Ctrl_Common(5, &ctrlCommon);

	ctrlIn.format		= E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifo_stages	= E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format	= E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlIn.bit_shift	= E_DD_AUDIO_BIT_SHIFT_0;

	Dd_Audio_Ctrl_Input(4, &ctrlIn);
	Dd_Audio_Ctrl_Input(5, &ctrlIn);

	dma.dma_2ch			= D_DD_AUDIO_ENABLE;
	dma.dma_trnsf_cnt	= 0x4800;

	Dd_Audio_Ctrl_DmaIn(4, &dma);
	Dd_Audio_Ctrl_DmaIn(5, &dma);

	Dd_Audio_Set_SwapHW_AUIDLR(4, D_DD_AUDIO_ENABLE);
	Dd_Audio_Set_SwapHW_AUIDLR(5, D_DD_AUDIO_ENABLE);

	S_DD_CT_AUDIO_PDM_DMA_INT_CNT0 = 1;
	S_DD_CT_AUDIO_PDM_DMA_INT_CNT1 = 1;

	Dd_HDMAC0_Input_Audio_Async(0,
		D_DD_HDMAC0_IS_IDREQ_8,
		Dd_Audio_Get_Addr_Reg_AUIDLR(4),
		CtDdAudio_CT_DD_Audio_WORK_AREA,
		0x4B00,
		(VP_CALLBACK)ctDdAudioDmaIntHandlerPdm00_cb);

	Dd_HDMAC0_Input_Audio_Async(1,
		D_DD_HDMAC0_IS_IDREQ_20,
		Dd_Audio_Get_Addr_Reg_AUIDLR(4),
		CtDdAudio_CT_DD_Audio_WORK_AREA+(0x4B00),
		0x4B00,
		(VP_CALLBACK)ctDdAudioDmaIntHandlerPdm01_cb);

	Dd_HDMAC0_Input_Audio_Async(2,
		D_DD_HDMAC0_IS_IDREQ_10,
		Dd_Audio_Get_Addr_Reg_AUIDLR(5),
		CtDdAudio_CT_DD_Audio_WORK_AREA2,
		0x4B00,
		(VP_CALLBACK)ctDdAudioDmaIntHandlerPdm10_cb);

	Dd_HDMAC0_Input_Audio_Async(3,
		D_DD_HDMAC0_IS_IDREQ_22,
		Dd_Audio_Get_Addr_Reg_AUIDLR(5),
		CtDdAudio_CT_DD_Audio_WORK_AREA2+(0x4B00),
		0x4B00,
		(VP_CALLBACK)ctDdAudioDmaIntHandlerPdm11_cb);

	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_ENABLE);
	Dd_Audio_Set_InputDMARequestEnable(5, D_DD_AUDIO_ENABLE);

	IO_AUDIO.AUDIOIF_CTRL.AUIOE.word = 0x00000500;

	DDIM_User_Dly_Tsk(11000);

	IO_AUDIO.AUDIOIF_CTRL.AUIOE.word = 0x00000A00;

	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_DISABLE);
	Dd_Audio_Set_InputDMARequestEnable(5, D_DD_AUDIO_DISABLE);

	Dd_HDMAC0_Stop(0);
	Dd_HDMAC0_Stop(1);
	Dd_HDMAC0_Stop(2);
	Dd_HDMAC0_Stop(3);

	Dd_HDMAC0_Close(0);
	Dd_HDMAC0_Close(1);
	Dd_HDMAC0_Close(2);
	Dd_HDMAC0_Close(3);

	Dd_Audio_Close_Input(4);
	Dd_Audio_Close_Input(5);

	Dd_Pdm_Stop_Streaming(0);
	Dd_Pdm_Stop_Streaming(1);
	Dd_Pdm_Close(0);
	Dd_Pdm_Close(1);

	printf("> Audio Pdm : PDM0/PDM1 Sync test\n");
	printf("> PDM0 Data. Addr: 0x7C000000, Size: 0x1D4C00\n");
	printf("> PDM1 Data. Addr: 0x7D000000, Size: 0x1D4C00\n");
}

CtDdAudioFifo3 *ct_dd_audio_fifo3_new(kpointer *temp, kuint8 ch)
{
    CtDdAudioFifo3 *self = k_object_new_with_private(CT_TYPE_DD_AUDIO_FIFO3, sizeof(CtDdAudioFifo3Private));
    if(!temp)
    {
         *temp = (kpointer)self;
    }
    self->ch = ch;
	return self;
}
