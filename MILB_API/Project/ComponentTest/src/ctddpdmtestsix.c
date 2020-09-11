/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmTestsix类
*@rely                :klib
*@function
*1.0.0 2020年09月开始开发
*设计的主要功能:
*1、
*@version
*
*/

#include <string.h>
#include <stdlib.h>
#include "pdm.h"
#include "dd_pdm.h"
#include "ct_dd_pdm.h"
#include "dd_top.h"
#include "dd_cache.h"
#include "dd_gic.h"
#include "dd_audio.h"
#include "dd_hdmac0.h"
#include "peripheral.h"
#include "ctddpdmtestone.h"
#include "ctddpdmtestfive.h"
#include "ctddpdmtestsix.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPdmTestsix, ct_dd_pdm_testsix);
#define CT_DD_PDM_TESTCASE6_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPdmTestsixPrivate,CT_TYPE_DD_PDM_TESTCASE6))

struct _CtDdPdmTestsixPrivate
{
	kint a;
};

static volatile kuint32 *S_GCT_DD_PDM_DMA_INT_CNT6;

static void ct_dd_pdm_testsix_constructor(CtDdPdmTestsix *self) 
{

}

static void ct_dd_pdm_testsix_destructor(CtDdPdmTestsix *self) 
{

}

/*
 *PUBLIC
 */
void ct_dd_pdm_testsix_set_addr(CtDdPdmTestsix *self,CtDdPdmTestone *testone)
{
	S_GCT_DD_PDM_DMA_INT_CNT6 = &testone->cnt;
}

#ifdef CO_ES3_HARDWARE
void ct_dd_pdm_testsix_037(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	
	// Select AUCLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(5);
	
	Dd_Audio_Init();
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);

	Dd_Pdm_Init();
	
	if(Dd_Pdm_Open(ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	Dd_Pdm_Get_Ctrl_Core(ch, &self->pdmCfg);
	self->pdmCfg.mclk_div = 4;
	self->pdmCfg.sinc_rate = 32;
	self->pdmCfg.pga_r = 0;
	self->pdmCfg.pga_l = 0;
	
	Dd_Pdm_Ctrl_Core(ch, &self->pdmCfg);
	
	Dd_Pdm_Get_Ctrl_Dma(ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Pdm_Set_CallbackDma0Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	Dd_Pdm_Set_EnableDma0Intr(ch, D_DD_PDM_ENABLE);
	Dd_Pdm_Set_CallbackDma1Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	Dd_Pdm_Set_EnableDma1Intr(ch, D_DD_PDM_ENABLE);
	
	Dd_Pdm_Flush_Dma_Fifo(0);
	
	Dd_Pdm_Set_DMA0_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA);
	Dd_Pdm_Set_DMA1_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	Dd_Pdm_Set_Dma_TransLength(ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Dd_Audio_Close_Input(4);
	
	Ddim_Print(("> pdm(ES3) 031 : PDM0(DMA) Clock:8.192MHz(AUCLK) FS:16kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_038(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	
	// Select AUCLK/2
	Dd_Top_Set_CLKSEL7_PDM0SEL(6);
	
	Dd_Audio_Init();
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);
	
	Dd_Pdm_Init();
	
	if(Dd_Pdm_Open(ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	Dd_Pdm_Get_Ctrl_Core(ch, &self->pdmCfg);
	self->pdmCfg.mclk_div = 12;
	self->pdmCfg.sinc_rate = 32;
	self->pdmCfg.pga_r = 0;
	self->pdmCfg.pga_l = 0;
	
	Dd_Pdm_Ctrl_Core(ch, &self->pdmCfg);
	
	Dd_Pdm_Get_Ctrl_Dma(ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Pdm_Set_CallbackDma0Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	Dd_Pdm_Set_EnableDma0Intr(ch, D_DD_PDM_ENABLE);
	Dd_Pdm_Set_CallbackDma1Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	Dd_Pdm_Set_EnableDma1Intr(ch, D_DD_PDM_ENABLE);
	
	Dd_Pdm_Flush_Dma_Fifo(0);
	
	Dd_Pdm_Set_DMA0_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA);
	Dd_Pdm_Set_DMA1_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	Dd_Pdm_Set_Dma_TransLength(ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Ddim_Print(("> pdm(ES3) 032 : PDM0(DMA) Clock:12.288MHz(AUCLK/2) FS:8kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_039(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	
	// Select AUCLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(5);
	
	Dd_Audio_Init();
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);

	Dd_Pdm_Init();
	
	if(Dd_Pdm_Open(ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	Dd_Pdm_Get_Ctrl_Core(ch, &self->pdmCfg);
	self->pdmCfg.mclk_div = 8;
	self->pdmCfg.sinc_rate = 32;
	self->pdmCfg.pga_r = 0;
	self->pdmCfg.pga_l = 0;
	
	Dd_Pdm_Ctrl_Core(ch, &self->pdmCfg);
	
	Dd_Pdm_Get_Ctrl_Dma(ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Pdm_Set_CallbackDma0Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	Dd_Pdm_Set_EnableDma0Intr(ch, D_DD_PDM_ENABLE);
	Dd_Pdm_Set_CallbackDma1Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	Dd_Pdm_Set_EnableDma1Intr(ch, D_DD_PDM_ENABLE);
	
	Dd_Pdm_Flush_Dma_Fifo(0);
	
	Dd_Pdm_Set_DMA0_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA);
	Dd_Pdm_Set_DMA1_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	Dd_Pdm_Set_Dma_TransLength(ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Dd_Audio_Close_Input(4);
	
	Ddim_Print(("> pdm(ES3) 033 : PDM0(DMA) Clock:8.192MHz(AUCLK) FS:8kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_040(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	
	// Select AUCLK/2
	Dd_Top_Set_CLKSEL7_PDM0SEL(6);
	
	Dd_Audio_Init();
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);

	Dd_Pdm_Init();
	
	if(Dd_Pdm_Open(ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	Dd_Pdm_Get_Ctrl_Core(ch, &self->pdmCfg);
	self->pdmCfg.mclk_div = 4;
	self->pdmCfg.sinc_rate = 32;
	self->pdmCfg.pga_r = 0;
	self->pdmCfg.pga_l = 0;
	
	Dd_Pdm_Ctrl_Core(ch, &self->pdmCfg);
	
	Dd_Pdm_Get_Ctrl_Dma(ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Pdm_Set_CallbackDma0Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	Dd_Pdm_Set_EnableDma0Intr(ch, D_DD_PDM_ENABLE);
	Dd_Pdm_Set_CallbackDma1Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	Dd_Pdm_Set_EnableDma1Intr(ch, D_DD_PDM_ENABLE);
	
	Dd_Pdm_Flush_Dma_Fifo(0);
	
	Dd_Pdm_Set_DMA0_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA);
	Dd_Pdm_Set_DMA1_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize = 0x400;
	self->pdmLen.tsize = 0x10;
	
	Dd_Pdm_Set_Dma_TransLength(ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Dd_Audio_Close_Input(4);
	
	Ddim_Print(("> pdm(ES3) 034 : PDM0(DMA) Clock:4.096MHz(AUCLK) FS:8kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_041(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	
	// Select AUCLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(5);
	
	Dd_Audio_Init();
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_22_5792;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);

	Dd_Pdm_Init();
	
	if(Dd_Pdm_Open(ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	Dd_Pdm_Get_Ctrl_Core(ch, &self->pdmCfg);
	self->pdmCfg.mclk_div = 8;
	self->pdmCfg.sinc_rate = 16;
	self->pdmCfg.pga_r = 0;
	self->pdmCfg.pga_l = 0;
	
	Dd_Pdm_Ctrl_Core(ch, &self->pdmCfg);
	
	Dd_Pdm_Get_Ctrl_Dma(ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Pdm_Set_CallbackDma0Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	Dd_Pdm_Set_EnableDma0Intr(ch, D_DD_PDM_ENABLE);
	Dd_Pdm_Set_CallbackDma1Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	Dd_Pdm_Set_EnableDma1Intr(ch, D_DD_PDM_ENABLE);
	
	Dd_Pdm_Flush_Dma_Fifo(0);
	
	Dd_Pdm_Set_DMA0_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA);
	Dd_Pdm_Set_DMA1_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	Dd_Pdm_Set_Dma_TransLength(ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Dd_Audio_Close_Input(4);
	
	Ddim_Print(("> pdm(ES3) 035 : PDM0(DMA) Clock:22.5792MHz(AUCLK) FS:44.1kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_042(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	
	// Select AUCLK/2
	Dd_Top_Set_CLKSEL7_PDM0SEL(6);
	
	Dd_Audio_Init();
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_22_5792;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);
	
	Dd_Pdm_Init();
	
	if(Dd_Pdm_Open(ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	Dd_Pdm_Get_Ctrl_Core(ch, &self->pdmCfg);
	self->pdmCfg.mclk_div = 4;
	self->pdmCfg.sinc_rate = 16;
	self->pdmCfg.pga_r = 0;
	self->pdmCfg.pga_l = 0;
	
	Dd_Pdm_Ctrl_Core(ch, &self->pdmCfg);
	
	Dd_Pdm_Get_Ctrl_Dma(ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Pdm_Set_CallbackDma0Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	Dd_Pdm_Set_EnableDma0Intr(ch, D_DD_PDM_ENABLE);
	Dd_Pdm_Set_CallbackDma1Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	Dd_Pdm_Set_EnableDma1Intr(ch, D_DD_PDM_ENABLE);
	
	Dd_Pdm_Flush_Dma_Fifo(0);
	
	Dd_Pdm_Set_DMA0_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA);
	Dd_Pdm_Set_DMA1_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	Dd_Pdm_Set_Dma_TransLength(ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Ddim_Print(("> pdm(ES3) 036 : PDM0(DMA) Clock:11.2896MHz(AUCLK/2) FS:44.1kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_043(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	
	// Select AUCLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(5);
	
	Dd_Audio_Init();
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_22_5792;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);

	Dd_Pdm_Init();
	
	if(Dd_Pdm_Open(ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	Dd_Pdm_Get_Ctrl_Core(ch, &self->pdmCfg);
	self->pdmCfg.mclk_div = 8;
	self->pdmCfg.sinc_rate = 32;
	self->pdmCfg.pga_r = 0;
	self->pdmCfg.pga_l = 0;
	
	Dd_Pdm_Ctrl_Core(ch, &self->pdmCfg);
	
	Dd_Pdm_Get_Ctrl_Dma(ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Pdm_Set_CallbackDma0Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	Dd_Pdm_Set_EnableDma0Intr(ch, D_DD_PDM_ENABLE);
	Dd_Pdm_Set_CallbackDma1Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	Dd_Pdm_Set_EnableDma1Intr(ch, D_DD_PDM_ENABLE);
	
	Dd_Pdm_Flush_Dma_Fifo(0);
	
	Dd_Pdm_Set_DMA0_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA);
	Dd_Pdm_Set_DMA1_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	Dd_Pdm_Set_Dma_TransLength(ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Dd_Audio_Close_Input(4);
	
	Ddim_Print(("> pdm(ES3) 037 : PDM0(DMA) Clock:22.5792MHz(AUCLK) FS:22.05kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_044(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	
	// Select AUCLK/2
	Dd_Top_Set_CLKSEL7_PDM0SEL(6);
	
	Dd_Audio_Init();
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_22_5792;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);
	
	Dd_Pdm_Init();
	
	if(Dd_Pdm_Open(ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	Dd_Pdm_Get_Ctrl_Core(ch, &self->pdmCfg);
	self->pdmCfg.mclk_div = 4;
	self->pdmCfg.sinc_rate = 32;
	self->pdmCfg.pga_r = 0;
	self->pdmCfg.pga_l = 0;
	
	Dd_Pdm_Ctrl_Core(ch, &self->pdmCfg);
	
	Dd_Pdm_Get_Ctrl_Dma(ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Pdm_Set_CallbackDma0Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	Dd_Pdm_Set_EnableDma0Intr(ch, D_DD_PDM_ENABLE);
	Dd_Pdm_Set_CallbackDma1Intr(ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	Dd_Pdm_Set_EnableDma1Intr(ch, D_DD_PDM_ENABLE);
	
	Dd_Pdm_Flush_Dma_Fifo(0);
	
	Dd_Pdm_Set_DMA0_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA);
	Dd_Pdm_Set_DMA1_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize = 0x400;
	self->pdmLen.tsize = 0x10;
	
	Dd_Pdm_Set_Dma_TransLength(ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);
	
	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Ddim_Print(("> pdm(ES3) 038 : PDM0(DMA) Clock:11.2896MHz(AUCLK/2) FS:22.05kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

#endif /*CO_ES3_HARDWARE*/

CtDdPdmTestsix* ct_dd_pdm_testsix_new(void) 
{
    CtDdPdmTestsix *self = k_object_new_with_private(CT_TYPE_DD_PDM_TESTCASE6, sizeof(CtDdPdmTestsixPrivate));

    return self;
}
