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
#include "../../DeviceDriver/Peripheral/src/ddaudio.h"
#include "../../DeviceDriver/Peripheral/src/ddaudioi2s.h"
#include "../../DeviceDriver/Peripheral/src/ddhdmac0.h"
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
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),0, CtDdPdmTestone_WORK_AREA+(0x400 * 4 * (*S_GCt_DD_PDM_DMA_INT_CNT5)));
	dd_pdm_set_enable_dma1_intr(dd_pdm_get(),0, DdAudio_ENABLE);
	
	Ddim_Print(( "%s\n", __FUNCTION__ ));
}

void ct_dd_pdm_testfive_dma_int_handler026_1_cb(void)
{
	*S_GCt_DD_PDM_DMA_INT_CNT5++;
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),0, CtDdPdmTestone_WORK_AREA+(0x400 * 4 * (*S_GCt_DD_PDM_DMA_INT_CNT5)));
	dd_pdm_set_enable_dma0_intr(0, DdAudio_ENABLE);
	
	Ddim_Print(( "%s\n", __FUNCTION__ ));
}

void ct_dd_pdm_testfive_026(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;

	// Select PDM_CLK
	DdTopone_SET_CLKSEL7_PDM0SEL(4);
	
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);
	
	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 020 : PDM0(DMA) Clock:24.576MHz(PDM_CLK) FS:48kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_027(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;
	AUDIOI2SCMMN	i2sCommon;
	
	// Select AUCLK
	DdTopone_SET_CLKSEL7_PDM0SEL(5);
	
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	Ddim_Print(("> pdm(ES3) 021 : PDM0(DMA) Clock:24.576MHz(AUCLK) FS:48kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_028(CtDdPdmTestfive *self)
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 022 : PDM0(DMA) Clock:12.288MHz(AUCLK/2) FS:48kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_029(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;
	
	// Select PDM_CLK
	DdTopone_SET_CLKSEL7_PDM0SEL(4);
	
	dd_pdm_init(dd_pdm_get());
	
	if(dd_pdm_open(dd_pdm_get(),ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	self->pdmCfg.mclkDiv = 8;
	self->pdmCfg.sincRate = 24;
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
	
	dd_pdm_flush_dma_fifo(dd_pdm_get(),ch);
	
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA);
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	dd_pdm_set_dma_trans_length(dd_pdm_get(),ch, &self->pdmLen);
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 023 : PDM0(DMA) Clock:24.576MHz(PDM_CLK) FS:32kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_030(CtDdPdmTestfive *self)
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	Ddim_Print(("> pdm(ES3) 024 : PDM0(DMA) Clock:8.192MHz(AUCLK) FS:32kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_031(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;
	
	// Select PDM_CLK
	DdTopone_SET_CLKSEL7_PDM0SEL(4);
	
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
	
	dd_pdm_flush_dma_fifo(dd_pdm_get(),ch);
	
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA);
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	dd_pdm_set_dma_trans_length(dd_pdm_get(),ch, &self->pdmLen);
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),0, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 025 : PDM0(DMA) Clock:24.576MHz(PDM_CLK) FS:24kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_032(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;
	AUDIOI2SCMMN	i2sCommon;
	
	// Select AUCLK
	DdTopone_SET_CLKSEL7_PDM0SEL(5);
	
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	Ddim_Print(("> pdm(ES3) 026 : PDM0(DMA) Clock:24.576MHz(AUCLK) FS:24kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_033(CtDdPdmTestfive *self)
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 027 : PDM0(DMA) Clock:12.288MHz(AUCLK/2) FS:24kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_034(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;
	
	// Select PDM_CLK
	DdTopone_SET_CLKSEL7_PDM0SEL(4);
	
	dd_pdm_init(dd_pdm_get());
	
	if(dd_pdm_open(dd_pdm_get(),ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	self->pdmCfg.mclkDiv = 8;
	self->pdmCfg.sincRate = 48;
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
	
	dd_pdm_flush_dma_fifo(dd_pdm_get(),ch);
	
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA);
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),ch, CtDdPdmTestone_WORK_AREA+(0x400 * 4));
	
	self->pdmLen.ttsize =0x400;
	self->pdmLen.tsize =0x10;
	
	dd_pdm_set_dma_trans_length(dd_pdm_get(),ch, &self->pdmLen);
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),0, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 028 : PDM0(DMA) Clock:24.576MHz(PDM_CLK) FS:16kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_035(CtDdPdmTestfive *self)
{
	kuint8 ch = 0;
	AUDIOI2SCMMN	i2sCommon;
	
	// Select AUCLK
	DdTopone_SET_CLKSEL7_PDM0SEL(5);
	
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
	self->pdmCfg.mclkDiv = 8;
	self->pdmCfg.sincRate = 48;
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	Ddim_Print(("> pdm(ES3) 029 : PDM0(DMA) Clock:24.576MHz(AUCLK) FS:16kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

void ct_dd_pdm_testfive_036(CtDdPdmTestfive *self)
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
	self->pdmCfg.mclkDiv = 4;
	self->pdmCfg.sincRate = 48;
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
	
	*S_GCt_DD_PDM_DMA_INT_CNT5 = 1;
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	

	DDIM_User_Dly_Tsk(2000);

	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 030 : PDM0(DMA) Clock:12.288MHz(AUCLK/2) FS:16kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestfive));
}

#endif /*CO_ES3_HARDWARE*/

CtDdPdmTestfive* ct_dd_pdm_testfive_new(void) 
{
    CtDdPdmTestfive *self = k_object_new_with_private(CT_TYPE_DD_PDM_TESTFIVE, sizeof(CtDdPdmTestfivePrivate));

    return self;
}
