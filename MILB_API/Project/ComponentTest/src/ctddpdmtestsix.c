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
// #include "dd_pdm.h"
#include "ct_dd_pdm.h"
// #include "dd_top.h"
// #include "dd_cache.h"
// #include "dd_gic.h"
// #include "dd_audio.h"
// #include "dd_hdmac0.h"
#include "../../DeviceDriver/Peripheral/src/ddpdm.h"
#include "../../DeviceDriver/LSITop/src/ddtopone.h"
#include "../../DeviceDriver/Peripheral/src/ddaudioctrl.h"
#include "../../DeviceDriver/Peripheral/src/ddaudiodma.h"
#include "../../DeviceDriver/Peripheral/src/ddaudioi2s.h"
#include "../../DeviceDriver/Peripheral/src/ddaudio.h"
#include "../../DeviceDriver/Peripheral/src/ddhdmac0.h"
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
	AUDIOI2SCMMN	i2sCommon;
	
	// Select AUCLK
	DdTopone_SET_CLKSEL7_PDM0SEL(5);
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DdAudioI2s_MASTER_CLOCK_8_192;
	i2sCommon.divaumclko = DdAudioI2s_AUMCLKO_DIV_1;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);

	dd_pdm_init(dd_pdm_get());
	
	if(dd_pdm_open(dd_pdm_get(),ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	self->pdmCfg.mclkDiv = 4;
	self->pdmCfg.sincRate = 32;
	self->pdmCfg.pgaR = 0;
	self->pdmCfg.pgaL = 0;
	
	dd_pdm_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	
	dd_pdm_get_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_pdm_set_callback_dma0_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	dd_pdm_set_enable_dma0_intr(ch, DdAudio_ENABLE);
	dd_pdm_set_callback_dma1_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	dd_pdm_set_enable_dma1_intr(dd_pdm_get(),ch, DdAudio_ENABLE);
	
	dd_pdm_flush_dma_fifo(dd_pdm_get(),0);
	
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA);
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	dd_pdm_set_dma_trans_length(dd_pdm_get(),ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	Ddim_Print(("> pdm(ES3) 031 : PDM0(DMA) Clock:8.192MHz(AUCLK) FS:16kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_038(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	AUDIOI2SCMMN	i2sCommon;
	
	// Select AUCLK/2
	DdTopone_SET_CLKSEL7_PDM0SEL(6);
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DDAUDIOI2S_MASTER_CLOCK_24_576;
	i2sCommon.divaumclko = DdAudioI2s_AUMCLKO_DIV_2;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	dd_pdm_init(dd_pdm_get());
	
	if(dd_pdm_open(dd_pdm_get(),ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	self->pdmCfg.mclkDiv = 12;
	self->pdmCfg.sincRate = 32;
	self->pdmCfg.pgaR = 0;
	self->pdmCfg.pgaL = 0;
	
	dd_pdm_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	
	dd_pdm_get_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_pdm_set_callback_dma0_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	dd_pdm_set_enable_dma0_intr(ch, DdAudio_ENABLE);
	dd_pdm_set_callback_dma1_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	dd_pdm_set_enable_dma1_intr(dd_pdm_get(),ch, DdAudio_ENABLE);
	
	dd_pdm_flush_dma_fifo(dd_pdm_get(),0);
	
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA);
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	dd_pdm_set_dma_trans_length(dd_pdm_get(),ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 032 : PDM0(DMA) Clock:12.288MHz(AUCLK/2) FS:8kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_039(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	AUDIOI2SCMMN	i2sCommon;
	
	// Select AUCLK
	DdTopone_SET_CLKSEL7_PDM0SEL(5);
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DdAudioI2s_MASTER_CLOCK_8_192;
	i2sCommon.divaumclko = DdAudioI2s_AUMCLKO_DIV_1;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);

	dd_pdm_init(dd_pdm_get());
	
	if(dd_pdm_open(dd_pdm_get(),ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	self->pdmCfg.mclkDiv = 8;
	self->pdmCfg.sincRate = 32;
	self->pdmCfg.pgaR = 0;
	self->pdmCfg.pgaL = 0;
	
	dd_pdm_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	
	dd_pdm_get_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_pdm_set_callback_dma0_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	dd_pdm_set_enable_dma0_intr(ch, DdAudio_ENABLE);
	dd_pdm_set_callback_dma1_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	dd_pdm_set_enable_dma1_intr(dd_pdm_get(),ch, DdAudio_ENABLE);
	
	dd_pdm_flush_dma_fifo(dd_pdm_get(),0);
	
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA);
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	dd_pdm_set_dma_trans_length(dd_pdm_get(),ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	Ddim_Print(("> pdm(ES3) 033 : PDM0(DMA) Clock:8.192MHz(AUCLK) FS:8kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_040(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	AUDIOI2SCMMN	i2sCommon;
	
	// Select AUCLK/2
	DdTopone_SET_CLKSEL7_PDM0SEL(6);
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DdAudioI2s_MASTER_CLOCK_8_192;
	i2sCommon.divaumclko = DdAudioI2s_AUMCLKO_DIV_1;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);

	dd_pdm_init(dd_pdm_get());
	
	if(dd_pdm_open(dd_pdm_get(),ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	self->pdmCfg.mclkDiv = 4;
	self->pdmCfg.sincRate = 32;
	self->pdmCfg.pgaR = 0;
	self->pdmCfg.pgaL = 0;
	
	dd_pdm_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	
	dd_pdm_get_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_pdm_set_callback_dma0_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	dd_pdm_set_enable_dma0_intr(ch, DdAudio_ENABLE);
	dd_pdm_set_callback_dma1_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	dd_pdm_set_enable_dma1_intr(dd_pdm_get(),ch, DdAudio_ENABLE);
	
	dd_pdm_flush_dma_fifo(dd_pdm_get(),0);
	
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA);
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize = 0x400;
	self->pdmLen.tsize = 0x10;
	
	dd_pdm_set_dma_trans_length(dd_pdm_get(),ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	Ddim_Print(("> pdm(ES3) 034 : PDM0(DMA) Clock:4.096MHz(AUCLK) FS:8kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_041(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	AUDIOI2SCMMN	i2sCommon;
	
	// Select AUCLK
	DdTopone_SET_CLKSEL7_PDM0SEL(5);
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DdAudioI2s_MASTER_CLOCK_22_5792;
	i2sCommon.divaumclko = DdAudioI2s_AUMCLKO_DIV_1;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);

	dd_pdm_init(dd_pdm_get());
	
	if(dd_pdm_open(dd_pdm_get(),ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	self->pdmCfg.mclkDiv = 8;
	self->pdmCfg.sincRate = 16;
	self->pdmCfg.pgaR = 0;
	self->pdmCfg.pgaL = 0;
	
	dd_pdm_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	
	dd_pdm_get_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_pdm_set_callback_dma0_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	dd_pdm_set_enable_dma0_intr(ch, DdAudio_ENABLE);
	dd_pdm_set_callback_dma1_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	dd_pdm_set_enable_dma1_intr(dd_pdm_get(),ch, DdAudio_ENABLE);
	
	dd_pdm_flush_dma_fifo(dd_pdm_get(),0);
	
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA);
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	dd_pdm_set_dma_trans_length(dd_pdm_get(),ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	Ddim_Print(("> pdm(ES3) 035 : PDM0(DMA) Clock:22.5792MHz(AUCLK) FS:44.1kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_042(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	AUDIOI2SCMMN	i2sCommon;
	
	// Select AUCLK/2
	DdTopone_SET_CLKSEL7_PDM0SEL(6);
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DdAudioI2s_MASTER_CLOCK_22_5792;
	i2sCommon.divaumclko = DdAudioI2s_AUMCLKO_DIV_2;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	dd_pdm_init(dd_pdm_get());
	
	if(dd_pdm_open(dd_pdm_get(),ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	self->pdmCfg.mclkDiv = 4;
	self->pdmCfg.sincRate = 16;
	self->pdmCfg.pgaR = 0;
	self->pdmCfg.pgaL = 0;
	
	dd_pdm_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	
	dd_pdm_get_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_pdm_set_callback_dma0_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	dd_pdm_set_enable_dma0_intr(ch, DdAudio_ENABLE);
	dd_pdm_set_callback_dma1_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	dd_pdm_set_enable_dma1_intr(dd_pdm_get(),ch, DdAudio_ENABLE);
	
	dd_pdm_flush_dma_fifo(dd_pdm_get(),0);
	
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA);
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	dd_pdm_set_dma_trans_length(dd_pdm_get(),ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 036 : PDM0(DMA) Clock:11.2896MHz(AUCLK/2) FS:44.1kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_043(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	AUDIOI2SCMMN	i2sCommon;
	
	// Select AUCLK
	DdTopone_SET_CLKSEL7_PDM0SEL(5);
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DdAudioI2s_MASTER_CLOCK_22_5792;
	i2sCommon.divaumclko = DdAudioI2s_AUMCLKO_DIV_1;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);

	dd_pdm_init(dd_pdm_get());
	
	if(dd_pdm_open(dd_pdm_get(),ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	self->pdmCfg.mclkDiv = 8;
	self->pdmCfg.sincRate = 32;
	self->pdmCfg.pgaR = 0;
	self->pdmCfg.pgaL = 0;
	
	dd_pdm_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	
	dd_pdm_get_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_pdm_set_callback_dma0_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	dd_pdm_set_enable_dma0_intr(ch, DdAudio_ENABLE);
	dd_pdm_set_callback_dma1_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	dd_pdm_set_enable_dma1_intr(dd_pdm_get(),ch, DdAudio_ENABLE);
	
	dd_pdm_flush_dma_fifo(dd_pdm_get(),0);
	
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA);
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	dd_pdm_set_dma_trans_length(dd_pdm_get(),ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	Ddim_Print(("> pdm(ES3) 037 : PDM0(DMA) Clock:22.5792MHz(AUCLK) FS:22.05kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

void ct_dd_pdm_testsix_044(CtDdPdmTestsix *self)
{
	kuint8 ch = 0;
	AUDIOI2SCMMN	i2sCommon;
	
	// Select AUCLK/2
	DdTopone_SET_CLKSEL7_PDM0SEL(6);
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DdAudioI2s_MASTER_CLOCK_22_5792;
	i2sCommon.divaumclko = DdAudioI2s_AUMCLKO_DIV_2;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	dd_pdm_init(dd_pdm_get());
	
	if(dd_pdm_open(dd_pdm_get(),ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	self->pdmCfg.mclkDiv = 4;
	self->pdmCfg.sincRate = 32;
	self->pdmCfg.pgaR = 0;
	self->pdmCfg.pgaL = 0;
	
	dd_pdm_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	
	dd_pdm_get_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_LEFT;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_pdm_set_callback_dma0_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_0_cb);
	dd_pdm_set_enable_dma0_intr(ch, DdAudio_ENABLE);
	dd_pdm_set_callback_dma1_intr(dd_pdm_get(),ch, (T_DD_PDM_CALLBACK)ct_dd_pdm_testfive_dma_int_handler026_1_cb);
	dd_pdm_set_enable_dma1_intr(dd_pdm_get(),ch, DdAudio_ENABLE);
	
	dd_pdm_flush_dma_fifo(dd_pdm_get(),0);
	
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA);
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize = 0x400;
	self->pdmLen.tsize = 0x10;
	
	dd_pdm_set_dma_trans_length(dd_pdm_get(),ch, &self->pdmLen);
	
	*S_GCT_DD_PDM_DMA_INT_CNT6 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);
	
	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 038 : PDM0(DMA) Clock:11.2896MHz(AUCLK/2) FS:22.05kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestsix));
}

#endif /*CO_ES3_HARDWARE*/

CtDdPdmTestsix* ct_dd_pdm_testsix_new(void) 
{
    CtDdPdmTestsix *self = k_object_new_with_private(CT_TYPE_DD_PDM_TESTCASE6, sizeof(CtDdPdmTestsixPrivate));

    return self;
}
