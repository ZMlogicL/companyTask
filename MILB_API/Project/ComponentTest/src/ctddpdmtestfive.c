/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmTestfive类
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

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPdmTestfive, ct_dd_pdm_testfive);
#define CT_DD_PDM_TESTFIVE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPdmTestfivePrivate,CT_TYPE_DD_PDM_TESTFIVE))

struct _CtDdPdmTestfivePrivate
{
	kint a;
};

static volatile kuint32 *S_GCt_DD_PDM_DMA_INT_CNT5;

static void ct_dd_pdm_testfive_constructor(CtDdPdmTestfive *self) 
{

}

static void ct_dd_pdm_testfive_destructor(CtDdPdmTestfive *self) 
{

}

/*
 *PUBLIC
 */
void ct_dd_pdm_testfive_set_addr(CtDdPdmTestfive *self,CtDdPdmTestone *testone)
{
	S_GCt_DD_PDM_DMA_INT_CNT5 = &testone->cnt;
}

#ifdef CO_ES3_HARDWARE
void ct_dd_pdm_testfive_dma_int_handler026_0_cb(void)
{
	*S_GCt_DD_PDM_DMA_INT_CNT5++;
	Dd_Pdm_Set_DMA0_Dst_Addr(0, CtDdPdmTestone_WORK_AREA+(0x400 * 4 * (*S_GCt_DD_PDM_DMA_INT_CNT5)));
	Dd_Pdm_Set_EnableDma1Intr(0, D_DD_PDM_ENABLE);
	
	Ddim_Print(( "%s\n", __FUNCTION__ ));
}

void ct_dd_pdm_testfive_dma_int_handler026_1_cb(void)
{
	*S_GCt_DD_PDM_DMA_INT_CNT5++;
	Dd_Pdm_Set_DMA1_Dst_Addr(0, CtDdPdmTestone_WORK_AREA+(0x400 * 4 * (*S_GCt_DD_PDM_DMA_INT_CNT5)));
	Dd_Pdm_Set_EnableDma0Intr(0, D_DD_PDM_ENABLE);
	
	Ddim_Print(( "%s\n", __FUNCTION__ ));
}

void ct_dd_pdm_testfive_026(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;

	// Select PDM_CLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(4);
	
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);
	
	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Ddim_Print(("> pdm(ES3) 020 : PDM0(DMA) Clock:24.576MHz(PDM_CLK) FS:48kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_027(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	
	// Select AUCLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(5);
	
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Dd_Audio_Close_Input(4);
	
	Ddim_Print(("> pdm(ES3) 021 : PDM0(DMA) Clock:24.576MHz(AUCLK) FS:48kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_028(CtDdPdmTestfive *self)
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Ddim_Print(("> pdm(ES3) 022 : PDM0(DMA) Clock:12.288MHz(AUCLK/2) FS:48kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_029(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;
	
	// Select PDM_CLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(4);
	
	Dd_Pdm_Init();
	
	if(Dd_Pdm_Open(ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	Dd_Pdm_Get_Ctrl_Core(ch, &self->pdmCfg);
	self->pdmCfg.mclk_div = 8;
	self->pdmCfg.sinc_rate = 24;
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
	
	Dd_Pdm_Flush_Dma_Fifo(ch);
	
	Dd_Pdm_Set_DMA0_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA);
	Dd_Pdm_Set_DMA1_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	Dd_Pdm_Set_Dma_TransLength(ch, &self->pdmLen);
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Ddim_Print(("> pdm(ES3) 023 : PDM0(DMA) Clock:24.576MHz(PDM_CLK) FS:32kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_030(CtDdPdmTestfive *self)
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Dd_Audio_Close_Input(4);
	
	Ddim_Print(("> pdm(ES3) 024 : PDM0(DMA) Clock:8.192MHz(AUCLK) FS:32kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_031(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;
	
	// Select PDM_CLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(4);
	
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
	
	Dd_Pdm_Flush_Dma_Fifo(ch);
	
	Dd_Pdm_Set_DMA0_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA);
	Dd_Pdm_Set_DMA1_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	Dd_Pdm_Set_Dma_TransLength(ch, &self->pdmLen);
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(0, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Ddim_Print(("> pdm(ES3) 025 : PDM0(DMA) Clock:24.576MHz(PDM_CLK) FS:24kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_032(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	
	// Select AUCLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(5);
	
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Dd_Audio_Close_Input(4);
	
	Ddim_Print(("> pdm(ES3) 026 : PDM0(DMA) Clock:24.576MHz(AUCLK) FS:24kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_033(CtDdPdmTestfive *self)
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Ddim_Print(("> pdm(ES3) 027 : PDM0(DMA) Clock:12.288MHz(AUCLK/2) FS:24kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_034(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;
	
	// Select PDM_CLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(4);
	
	Dd_Pdm_Init();
	
	if(Dd_Pdm_Open(ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	Dd_Pdm_Get_Ctrl_Core(ch, &self->pdmCfg);
	self->pdmCfg.mclk_div = 8;
	self->pdmCfg.sinc_rate = 48;
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
	
	Dd_Pdm_Flush_Dma_Fifo(ch);
	
	Dd_Pdm_Set_DMA0_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA);
	Dd_Pdm_Set_DMA1_Dst_Addr(ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	Dd_Pdm_Set_Dma_TransLength(ch, &self->pdmLen);
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(0, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Ddim_Print(("> pdm(ES3) 028 : PDM0(DMA) Clock:24.576MHz(PDM_CLK) FS:16kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_035(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	
	// Select AUCLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(5);
	
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
	self->pdmCfg.mclk_div = 8;
	self->pdmCfg.sinc_rate = 48;
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Dd_Audio_Close_Input(4);
	
	Ddim_Print(("> pdm(ES3) 029 : PDM0(DMA) Clock:24.576MHz(AUCLK) FS:16kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_036(CtDdPdmTestfive *self)
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
	self->pdmCfg.mclk_div = 4;
	self->pdmCfg.sinc_rate = 48;
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	Dd_Pdm_Stop_Streaming(ch);
	
	Dd_Pdm_Close(ch);
	
	Ddim_Print(("> pdm(ES3) 030 : PDM0(DMA) Clock:12.288MHz(AUCLK/2) FS:16kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

#endif /*CO_ES3_HARDWARE*/

CtDdPdmTestfive* ct_dd_pdm_testfive_new(void) 
{
    CtDdPdmTestfive *self = k_object_new_with_private(CT_TYPE_DD_PDM_TESTFIVE, sizeof(CtDdPdmTestfivePrivate));

    return self;
}
