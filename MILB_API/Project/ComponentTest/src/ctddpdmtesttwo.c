/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmTesttwo类
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
#include "ctddpdmtesttwo.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPdmTesttwo, ct_dd_pdm_testtwo);
#define CT_DD_PDM_TESTTWO_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPdmTesttwoPrivate,CT_TYPE_DD_PDM_TESTTWO))

struct _CtDdPdmTesttwoPrivate
{
	kint a;
};

static volatile kuint32 *S_GCt_DD_PDM_DMA_INT_CNT2;

/*
 *DECLS
 */
#ifdef CO_ES1_HARDWARE
static void 		ctDdPdmDmaIntHandler006( void );
#endif /*CO_ES1_HARDWARE*/
#ifdef CO_ES3_HARDWARE
static void 		ctDdPdmDmaIntHandler007( void );
static void 		ctDdPdmDmaIntHandler010( void );
#endif /*CO_ES3_HARDWARE*/

static void ct_dd_pdm_testtwo_constructor(CtDdPdmTesttwo *self) 
{

}

static void ct_dd_pdm_testtwo_destructor(CtDdPdmTesttwo *self) 
{

}

/*
 *IMPL
 */
#ifdef CO_ES1_HARDWARE
static void ctDdPdmDmaIntHandler006( void )
{
	*S_GCt_DD_PDM_DMA_INT_CNT2++;
	
	if(*S_GCt_DD_PDM_DMA_INT_CNT2 < 10) {
		dd_hdmac0_input_audio_async(dd_hdmac0_get(), 0,
									 D_DD_HDMAC0_IS_IDREQ_10,
									 dd_audio_get_addr_reg_auidlr(dd_audio_get(),5),
									 CtDdPdmTestone_WORK_AREA+(3200*2*2*(*S_GCt_DD_PDM_DMA_INT_CNT2)),
									 (3200*2*2),
									 (VP_CALLBACK)ctDdPdmDmaIntHandler006);
	}
	
	Ddim_Print(("ctDdPdmDmaIntHandler006 \n"));
}
#endif 

#ifdef CO_ES3_HARDWARE
static void ctDdPdmDmaIntHandler007( void )
{
	*S_GCt_DD_PDM_DMA_INT_CNT2++;
	
	if(*S_GCt_DD_PDM_DMA_INT_CNT2 < 10) {
		dd_hdmac0_input_audio_async(dd_hdmac0_get(), 0,
									 DdHdmac0_IS_IDREQ_8,
									 dd_audio_get_addr_reg_auidlr(dd_audio_get(),4),
									 CtDdPdmTestone_WORK_AREA+(4800*2*2*(*S_GCt_DD_PDM_DMA_INT_CNT2)),
									 (4800*2*2),
									 (VP_CALLBACK)ctDdPdmDmaIntHandler007);
	}
	
	Ddim_Print(( "%s\n", __FUNCTION__ ));

}

static void ctDdPdmDmaIntHandler010( void )
{
	*S_GCt_DD_PDM_DMA_INT_CNT2++;
	
	if(*S_GCt_DD_PDM_DMA_INT_CNT2 < 10) {
		dd_hdmac0_input_audio_async(dd_hdmac0_get(), 0,
									 DdHdmac0_IS_IDREQ_8,
									 dd_audio_get_addr_reg_auidlr(dd_audio_get(),4),
									 CtDdPdmTestone_WORK_AREA+(3200*2*2*(*S_GCt_DD_PDM_DMA_INT_CNT2)),
									 (3200*2*2),
									 (VP_CALLBACK)ctDdPdmDmaIntHandler010);
	}
	
	Ddim_Print(( "%s\n", __FUNCTION__ ));
}
#endif 


/*
 *PUBLIC
 */
void ct_dd_pdm_testtwo_set_addr(CtDdPdmTesttwo *self,CtDdPdmTestone *testone)
{
	S_GCt_DD_PDM_DMA_INT_CNT2 = &testone->cnt;
}

#ifdef CO_ES1_HARDWARE
void ct_dd_pdm_testtwo_006(CtDdPdmTesttwo *self)
{
	kuint8 ch = 1;
	AUDIOCTRLCOMMON	ctrlCommon;
	AUDIOCTRLIN	ctrlIn;
	AUDIOI2SCMMN	i2sCommon;
	AUDIOI2SIN	i2sIn;
	AUDIODMA	dma;

	dd_pdm_init(dd_pdm_get());
	
	if(dd_pdm_open(dd_pdm_get(),ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	self->pdmCfg.mclkDiv = 8;
	self->pdmCfg.sincRate = 24;
	self->pdmCfg.pgaR = 0;
	self->pdmCfg.pgaL = 0;
	self->pdmCfg.swap = DdPdm_CORE_LR_SWAP_SWAP;
	
	dd_pdm_ctrl_core(dd_pdm_get(),ch, &self->pdmCfg);
	
	dd_pdm_get_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_audio_open_input(dd_audio_get(),5, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(dd_hdmac0_open(dd_hdmac0_get(),0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("dd_hdmac0_open Error(ch0)\n"));
	}
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),5, &i2sCommon);
	
	i2sCommon.aumclki = DdAudioI2s_MASTER_CLOCK_8_192;
	i2sCommon.divaumclko = DdAudioI2s_AUMCLKO_DIV_1;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),5, &i2sCommon);
	
	dd_audio_get_ctrl_i2s_in(dd_audio_get(),5, &i2sIn);
	
	i2sIn.modeIn = DdAudioI2s_MODE_I2S;
	i2sIn.bitIn = DdAudioI2s_BIT_16BIT;
	
	dd_audio_ctrl_i2s_in(dd_audio_get(),5, &i2sIn);
	
	dd_audio_get_ctrl_common(dd_audio_get(),5, &ctrlCommon);
	
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	
	dd_audio_ctrl_common(dd_audio_get(),5, &ctrlCommon);
	
	dd_audio_get_ctrl_input(dd_audio_get(),5, &ctrlIn);
	
	ctrlIn.format = DdAudioCtrl_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
	ctrlIn.ahbFormat = DdAudioCtrl_AHB_FRMT_L_JUST;
	ctrlIn.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	
	dd_audio_ctrl_input(dd_audio_get(),5, &ctrlIn);
	
	dd_audio_get_ctrl_dma_in(dd_audio_get(),5, &dma);
	
	dma.dma2Ch	= DdAudio_DISABLE;
	dma.dmaTrnsfCnt = 0;
	
	dd_audio_ctrl_dma_in(dd_audio_get(),5, &dma);
	
	dd_audio_set_swap_hw_auidlr(dd_audio_get(),5, DdAudio_ENABLE);
	
	*S_GCt_DD_PDM_DMA_INT_CNT2 = 0;
	dd_hdmac0_input_audio_async(dd_hdmac0_get(),0,
								D_DD_HDMAC0_IS_IDREQ_10,
								dd_audio_get_addr_reg_auidlr(dd_audio_get(),5),
								CtDdPdmTestone_WORK_AREA,
								(3200*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler006);
	
	dd_audio_set_input_dma_request_enable(dd_audio_get(),5, DdAudio_ENABLE);
	
#if 0
	dd_pdm_flush_dma_fifo(dd_pdm_get(),0);
	
	dd_pdm_set_dma0_dst_addr(dd_pdm_get(),0, CtDdPdmTestone_WORK_AREA);
	dd_pdm_set_dma1_dst_addr(dd_pdm_get(),0, CtDdPdmTestone_WORK_AREA+0x400);
	
	DdPdmDmaLen pdmLen;
	pdmLen.ttsize =0x400;
	pdmLen.tsize =0x10;
	
	dd_pdm_set_dma_trans_length(dd_pdm_get(),0, &pdmLen);
	
	self->pdmDmaCfg.dmaEn = DdAudio_ENABLE;
	dd_pdm_ctrl_dma(dd_pdm_get(),0, &self->pdmDmaCfg);
#endif
	
	dd_audio_start_input(dd_audio_get(),5);
	
	DDIM_User_Dly_Tsk(2000);
	
	dd_audio_stop_input(dd_audio_get(),5);
	
	dd_audio_set_input_dma_request_enable(dd_audio_get(),5, DdAudio_DISABLE);
	
	if(dd_hdmac0_stop(dd_hdmac0_get(),0) != D_DDIM_OK) {
		Ddim_Print(("dd_hdmac0_stop Error(ch0)\n"));
	}
	
	dd_hdmac0_close(dd_hdmac0_get(),0);
	
	dd_audio_close_input(dd_audio_get(),5);
	
	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm 006 : Record PDM1 32kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTesttwo));
}
#endif /*CO_ES1_HARDWARE*/

#ifdef CO_ES3_HARDWARE
void ct_dd_pdm_testtwo_007(CtDdPdmTesttwo *self)
{
	/*
	 * Clock:24.576MHz(PDM CLK)
	 * FS:48kHz
	 * */
	kuint8 ch = 0;
	AUDIOCTRLCOMMON	ctrlCommon;
	AUDIOCTRLIN	ctrlIn;
	AUDIOI2SCMMN	i2sCommon;
	AUDIOI2SIN	i2sIn;
	AUDIODMA	dma;
	
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
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(dd_hdmac0_open(dd_hdmac0_get(),0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("dd_hdmac0_open Error(ch0)\n"));
	}
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DDAUDIOI2S_MASTER_CLOCK_24_576;
	i2sCommon.divaumclko = DdAudioI2s_AUMCLKO_DIV_2;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	dd_audio_get_ctrl_i2s_in(dd_audio_get(),4, &i2sIn);
	
	i2sIn.modeIn = DdAudioI2s_MODE_I2S;
	i2sIn.bitIn = DdAudioI2s_BIT_16BIT;
	
	dd_audio_ctrl_i2s_in(dd_audio_get(),4, &i2sIn);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_audio_get_ctrl_common(dd_audio_get(),4, &ctrlCommon);
	
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	
	dd_audio_ctrl_common(dd_audio_get(),4, &ctrlCommon);
	
	dd_audio_get_ctrl_input(dd_audio_get(),4, &ctrlIn);
	
	ctrlIn.format = DdAudioCtrl_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
	ctrlIn.ahbFormat = DdAudioCtrl_AHB_FRMT_L_JUST;
	ctrlIn.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	
	dd_audio_ctrl_input(dd_audio_get(),4, &ctrlIn);
	
	dd_audio_get_ctrl_dma_in(dd_audio_get(),4, &dma);
	
	dma.dma2Ch	= DdAudio_DISABLE;
	dma.dmaTrnsfCnt = 0;
	
	dd_audio_ctrl_dma_in(dd_audio_get(),4, &dma);
	
	dd_audio_set_swap_hw_auidlr(dd_audio_get(),4, DdAudio_ENABLE);
	
	*S_GCt_DD_PDM_DMA_INT_CNT2 = 0;
	dd_hdmac0_input_audio_async(dd_hdmac0_get(),0,
								DdHdmac0_IS_IDREQ_8,
								dd_audio_get_addr_reg_auidlr(dd_audio_get(),4),
								CtDdPdmTestone_WORK_AREA,
								(4800*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler007);
	
	dd_audio_set_input_dma_request_enable(dd_audio_get(),4, DdAudio_ENABLE);
	
	dd_audio_start_input(dd_audio_get(),4);
	
	DDIM_User_Dly_Tsk(2000);
	
	dd_audio_stop_input(dd_audio_get(),4);
	
	dd_audio_set_input_dma_request_enable(dd_audio_get(),4, DdAudio_DISABLE);
	
	if(dd_hdmac0_stop(dd_hdmac0_get(),0) != D_DDIM_OK) {
		Ddim_Print(("dd_hdmac0_stop Error(ch0)\n"));
	}
	
	dd_hdmac0_close(dd_hdmac0_get(),0);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 001 : Record PDM0 Clock:24.576MHz(PDM_CLK) FS:48kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTesttwo));
}

void ct_dd_pdm_testtwo_008(CtDdPdmTesttwo *self)
{
	/*
	 * Clock:24.576MHz(PDM CLK)
	 * FS:48kHz
	 * */
	kuint8 ch = 0;
	AUDIOCTRLCOMMON	ctrlCommon;
	AUDIOCTRLIN	ctrlIn;
	AUDIOI2SCMMN	i2sCommon;
	AUDIOI2SIN	i2sIn;
	AUDIODMA	dma;
	
	// Select AUCLK
	DdTopone_SET_CLKSEL7_PDM0SEL(5);
	
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
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(dd_hdmac0_open(dd_hdmac0_get(),0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("dd_hdmac0_open Error(ch0)\n"));
	}
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DDAUDIOI2S_MASTER_CLOCK_24_576;
	i2sCommon.divaumclko =  DdAudioI2s_AUMCLKO_DIV_2;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	dd_audio_get_ctrl_i2s_in(dd_audio_get(),4, &i2sIn);
	
	i2sIn.modeIn = DdAudioI2s_MODE_I2S;
	i2sIn.bitIn = DdAudioI2s_BIT_16BIT;
	
	dd_audio_ctrl_i2s_in(dd_audio_get(),4, &i2sIn);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_audio_get_ctrl_common(dd_audio_get(),4, &ctrlCommon);
	
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	
	dd_audio_ctrl_common(dd_audio_get(),4, &ctrlCommon);
	
	dd_audio_get_ctrl_input(dd_audio_get(),4, &ctrlIn);
	
	ctrlIn.format = DdAudioCtrl_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
	ctrlIn.ahbFormat = DdAudioCtrl_AHB_FRMT_L_JUST;
	ctrlIn.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	
	dd_audio_ctrl_input(dd_audio_get(),4, &ctrlIn);
	
	dd_audio_get_ctrl_dma_in(dd_audio_get(),4, &dma);
	
	dma.dma2Ch	= DdAudio_DISABLE;
	dma.dmaTrnsfCnt = 0;
	
	dd_audio_ctrl_dma_in(dd_audio_get(),4, &dma);
	
	dd_audio_set_swap_hw_auidlr(dd_audio_get(),4, DdAudio_ENABLE);
	
	*S_GCt_DD_PDM_DMA_INT_CNT2 = 0;
	dd_hdmac0_input_audio_async(dd_hdmac0_get(),0,
								DdHdmac0_IS_IDREQ_8,
								dd_audio_get_addr_reg_auidlr(dd_audio_get(),4),
								CtDdPdmTestone_WORK_AREA,
								(4800*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler007);
	
	dd_audio_set_input_dma_request_enable(dd_audio_get(),4, DdAudio_ENABLE);
	
	dd_audio_start_input(dd_audio_get(),4);
	
	DDIM_User_Dly_Tsk(2000);
	
	dd_audio_stop_input(dd_audio_get(),4);
	
	dd_audio_set_input_dma_request_enable(dd_audio_get(),4, DdAudio_DISABLE);
	
	if(dd_hdmac0_stop(dd_hdmac0_get(),0) != D_DDIM_OK) {
		Ddim_Print(("dd_hdmac0_stop Error(ch0)\n"));
	}
	
	dd_hdmac0_close(dd_hdmac0_get(),0);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 002 : Record PDM0 Clock:24.576MHz(AUCLK) FS=48kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTesttwo));
}

void ct_dd_pdm_testtwo_009(CtDdPdmTesttwo *self)
{
	/*
	 * Clock:12.288MHz(AUCLK/2)
	 * FS:48kHz
	 * */
	kuint8 ch = 0;
	AUDIOCTRLCOMMON	ctrlCommon;
	AUDIOCTRLIN	ctrlIn;
	AUDIOI2SCMMN	i2sCommon;
	AUDIOI2SIN	i2sIn;
	AUDIODMA	dma;
	
	// Select AUCLK/2
	DdTopone_SET_CLKSEL7_PDM0SEL(6);
	
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
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(dd_hdmac0_open(dd_hdmac0_get(),0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("dd_hdmac0_open Error(ch0)\n"));
	}
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DDAUDIOI2S_MASTER_CLOCK_24_576;
	i2sCommon.divaumclko =  DdAudioI2s_AUMCLKO_DIV_2;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	dd_audio_get_ctrl_i2s_in(dd_audio_get(),4, &i2sIn);
	
	i2sIn.modeIn = DdAudioI2s_MODE_I2S;
	i2sIn.bitIn = DdAudioI2s_BIT_16BIT;
	
	dd_audio_ctrl_i2s_in(dd_audio_get(),4, &i2sIn);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_audio_get_ctrl_common(dd_audio_get(),4, &ctrlCommon);
	
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	
	dd_audio_ctrl_common(dd_audio_get(),4, &ctrlCommon);
	
	dd_audio_get_ctrl_input(dd_audio_get(),4, &ctrlIn);
	
	ctrlIn.format = DdAudioCtrl_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
	ctrlIn.ahbFormat = DdAudioCtrl_AHB_FRMT_L_JUST;
	ctrlIn.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	
	dd_audio_ctrl_input(dd_audio_get(),4, &ctrlIn);
	
	dd_audio_get_ctrl_dma_in(dd_audio_get(),4, &dma);
	
	dma.dma2Ch	= DdAudio_DISABLE;
	dma.dmaTrnsfCnt = 0;
	
	dd_audio_ctrl_dma_in(dd_audio_get(),4, &dma);
	
	dd_audio_set_swap_hw_auidlr(dd_audio_get(),4, DdAudio_ENABLE);
	
	*S_GCt_DD_PDM_DMA_INT_CNT2 = 0;
	dd_hdmac0_input_audio_async(dd_hdmac0_get(),0,
								DdHdmac0_IS_IDREQ_8,
								dd_audio_get_addr_reg_auidlr(dd_audio_get(),4),
								CtDdPdmTestone_WORK_AREA,
								(4800*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler007);
	
	dd_audio_set_input_dma_request_enable(dd_audio_get(),4, DdAudio_ENABLE);
	
	dd_audio_start_input(dd_audio_get(),4);
	
	DDIM_User_Dly_Tsk(2000);
	
	dd_audio_stop_input(dd_audio_get(),4);
	
	dd_audio_set_input_dma_request_enable(dd_audio_get(),4, DdAudio_DISABLE);
	
	if(dd_hdmac0_stop(dd_hdmac0_get(),0) != D_DDIM_OK) {
		Ddim_Print(("dd_hdmac0_stop Error(ch0)\n"));
	}
	
	dd_hdmac0_close(dd_hdmac0_get(),0);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 003 : Record PDM0 Clock:12.288MHz(AUCLK/2) FS=48kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTesttwo));
}

void ct_dd_pdm_testtwo_010(CtDdPdmTesttwo *self)
{
	/*
	 * Clock:24.576MHz(PDM CLK)
	 * FS:32kHz
	 * */
	kuint8 ch = 0;
	AUDIOCTRLCOMMON	ctrlCommon;
	AUDIOCTRLIN	ctrlIn;
	AUDIOI2SCMMN	i2sCommon;
	AUDIOI2SIN	i2sIn;
	AUDIODMA	dma;
	
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
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(dd_hdmac0_open(dd_hdmac0_get(),0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("dd_hdmac0_open Error(ch0)\n"));
	}
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DdAudioI2s_MASTER_CLOCK_8_192;
	i2sCommon.divaumclko = DdAudioI2s_AUMCLKO_DIV_1;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	dd_audio_get_ctrl_i2s_in(dd_audio_get(),4, &i2sIn);
	
	i2sIn.modeIn = DdAudioI2s_MODE_I2S;
	i2sIn.bitIn = DdAudioI2s_BIT_16BIT;
	
	dd_audio_ctrl_i2s_in(dd_audio_get(),4, &i2sIn);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_audio_get_ctrl_common(dd_audio_get(),4, &ctrlCommon);
	
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	
	dd_audio_ctrl_common(dd_audio_get(),4, &ctrlCommon);
	
	dd_audio_get_ctrl_input(dd_audio_get(),4, &ctrlIn);
	
	ctrlIn.format = DdAudioCtrl_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
	ctrlIn.ahbFormat = DdAudioCtrl_AHB_FRMT_L_JUST;
	ctrlIn.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	
	dd_audio_ctrl_input(dd_audio_get(),4, &ctrlIn);
	
	dd_audio_get_ctrl_dma_in(dd_audio_get(),4, &dma);
	
	dma.dma2Ch	= DdAudio_DISABLE;
	dma.dmaTrnsfCnt = 0;
	
	dd_audio_ctrl_dma_in(dd_audio_get(),4, &dma);
	
	dd_audio_set_swap_hw_auidlr(dd_audio_get(),4, DdAudio_ENABLE);
	
	*S_GCt_DD_PDM_DMA_INT_CNT2 = 0;
	dd_hdmac0_input_audio_async(dd_hdmac0_get(),0,
								DdHdmac0_IS_IDREQ_8,
								dd_audio_get_addr_reg_auidlr(dd_audio_get(),4),
								CtDdPdmTestone_WORK_AREA,
								(3200*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler010);
	
	dd_audio_set_input_dma_request_enable(dd_audio_get(),4, DdAudio_ENABLE);
	
	dd_audio_start_input(dd_audio_get(),4);
	
	DDIM_User_Dly_Tsk(2000);
	
	dd_audio_stop_input(dd_audio_get(),4);
	
	dd_audio_set_input_dma_request_enable(dd_audio_get(),4, DdAudio_DISABLE);
	
	if(dd_hdmac0_stop(dd_hdmac0_get(),0) != D_DDIM_OK) {
		Ddim_Print(("dd_hdmac0_stop Error(ch0)\n"));
	}
	
	dd_hdmac0_close(dd_hdmac0_get(),0);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 004 : Record PDM0 Clock:24.576MHz(PDM_CLK) FS:32kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTesttwo));
}

void ct_dd_pdm_testtwo_011(CtDdPdmTesttwo *self)
{
	/*
	 * Clock:8.192MHz(AUCLK)
	 * FS:32kHz
	 * */
	kuint8 ch = 0;
	AUDIOCTRLCOMMON	ctrlCommon;
	AUDIOCTRLIN	ctrlIn;
	AUDIOI2SCMMN	i2sCommon;
	AUDIOI2SIN	i2sIn;
	AUDIODMA	dma;
	
	// Select AUCLK
	DdTopone_SET_CLKSEL7_PDM0SEL(5);
	
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
	self->pdmDmaCfg.pcmChset = DdPdm_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcmWdlen = DdPdm_DMA_PCM_WD_16;
	dd_pdm_ctrl_dma(dd_pdm_get(),ch, &self->pdmDmaCfg);
	
	dd_audio_open_input(dd_audio_get(),4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(dd_hdmac0_open(dd_hdmac0_get(),0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("dd_hdmac0_open Error(ch0)\n"));
	}
	
	dd_audio_init(dd_audio_get());
	
	dd_audio_get_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	i2sCommon.aumclki = DdAudioI2s_MASTER_CLOCK_8_192;
	i2sCommon.divaumclko = DdAudioI2s_AUMCLKO_DIV_1;
	i2sCommon.divAuclk = DdAudioI2s_AUCLK_DIV_4;
	i2sCommon.divLrclk = DdAudioI2s_AULR_DIV_64;
	i2sCommon.clkDivEnable = DdAudio_ENABLE;
	i2sCommon.masterSlave = DdAudioI2s_CLK_MASTER;
	
	dd_audio_ctrl_i2s_cmmn(dd_audio_get(),4, &i2sCommon);
	
	dd_audio_get_ctrl_i2s_in(dd_audio_get(),4, &i2sIn);
	
	i2sIn.modeIn = DdAudioI2s_MODE_I2S;
	i2sIn.bitIn = DdAudioI2s_BIT_16BIT;
	
	dd_audio_ctrl_i2s_in(dd_audio_get(),4, &i2sIn);
	
	dd_pdm_start_streaming(dd_pdm_get(),ch);
	
	dd_audio_get_ctrl_common(dd_audio_get(),4, &ctrlCommon);
	
	ctrlCommon.fifoUsage = DdAudioCtrl_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = DdAudioCtrl_CHANNEL_STEREO;
	
	dd_audio_ctrl_common(dd_audio_get(),4, &ctrlCommon);
	
	dd_audio_get_ctrl_input(dd_audio_get(),4, &ctrlIn);
	
	ctrlIn.format = DdAudioCtrl_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifoStages = DdAudioCtrl_FIFO_STAGES_16;
	ctrlIn.ahbFormat = DdAudioCtrl_AHB_FRMT_L_JUST;
	ctrlIn.bitShift = DdAudioCtrl_BIT_SHIFT_0;
	
	dd_audio_ctrl_input(dd_audio_get(),4, &ctrlIn);
	
	dd_audio_get_ctrl_dma_in(dd_audio_get(),4, &dma);
	
	dma.dma2Ch	= DdAudio_DISABLE;
	dma.dmaTrnsfCnt = 0;
	
	dd_audio_ctrl_dma_in(dd_audio_get(),4, &dma);
	
	dd_audio_set_swap_hw_auidlr(dd_audio_get(),4, DdAudio_ENABLE);
	
	*S_GCt_DD_PDM_DMA_INT_CNT2 = 0;
	dd_hdmac0_input_audio_async(dd_hdmac0_get(),0,
								DdHdmac0_IS_IDREQ_8,
								dd_audio_get_addr_reg_auidlr(dd_audio_get(),4),
								CtDdPdmTestone_WORK_AREA,
								(3200*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler010);
	
	dd_audio_set_input_dma_request_enable(dd_audio_get(),4, DdAudio_ENABLE);
	
	dd_audio_start_input(dd_audio_get(),4);
	
	DDIM_User_Dly_Tsk(2000);
	
	dd_audio_stop_input(dd_audio_get(),4);
	
	dd_audio_set_input_dma_request_enable(dd_audio_get(),4, DdAudio_DISABLE);
	
	if(dd_hdmac0_stop(dd_hdmac0_get(),0) != D_DDIM_OK) {
		Ddim_Print(("dd_hdmac0_stop Error(ch0)\n"));
	}
	
	dd_hdmac0_close(dd_hdmac0_get(),0);
	
	dd_audio_close_input(dd_audio_get(),4);
	
	dd_pdm_stop_streaming(dd_pdm_get(),ch);
	dd_pdm_close(dd_pdm_get(),ch);
	
	Ddim_Print(("> pdm(ES3) 005 : Record PDM0 Clock:8.192MHz(AUCLK) FS=32kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTesttwo));
}

#endif /*CO_ES3_HARDWARE*/

CtDdPdmTesttwo* ct_dd_pdm_testtwo_new(void) 
{
    CtDdPdmTesttwo *self = k_object_new_with_private(CT_TYPE_DD_PDM_TESTTWO, sizeof(CtDdPdmTesttwoPrivate));
    return self;
}
