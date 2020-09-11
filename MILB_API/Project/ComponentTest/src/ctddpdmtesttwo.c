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
#include "dd_pdm.h"
#include "ct_dd_pdm.h"
#include "dd_top.h"
#include "dd_cache.h"
#include "dd_gic.h"
#include "dd_audio.h"
#include "dd_hdmac0.h"
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
		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_10,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(5),
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
		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_8,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(4),
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
		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_8,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(4),
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
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_DMA	dma;

	Dd_Pdm_Init();
	
	if(Dd_Pdm_Open(ch, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_Pdm_Open Error(ch0)\n"));
	}
	
	Dd_Pdm_Get_Ctrl_Core(ch, &self->pdmCfg);
	self->pdmCfg.mclk_div = 8;
	self->pdmCfg.sinc_rate = 24;
	self->pdmCfg.pga_r = 0;
	self->pdmCfg.pga_l = 0;
	self->pdmCfg.swap = E_DD_PDM_CORE_LR_SWAP_SWAP;
	
	Dd_Pdm_Ctrl_Core(ch, &self->pdmCfg);
	
	Dd_Pdm_Get_Ctrl_Dma(ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Audio_Open_Input(5, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}
	
	Dd_Audio_Init();
	
	Dd_Audio_Get_Ctrl_I2sCmmn(5, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(5, &i2sCommon);
	
	Dd_Audio_Get_Ctrl_I2sIn(5, &i2sIn);
	
	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	
	Dd_Audio_Ctrl_I2sIn(5, &i2sIn);
	
	Dd_Audio_Get_Ctrl_Common(5, &ctrlCommon);
	
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	
	Dd_Audio_Ctrl_Common(5, &ctrlCommon);
	
	Dd_Audio_Get_Ctrl_Input(5, &ctrlIn);
	
	ctrlIn.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlIn.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	
	Dd_Audio_Ctrl_Input(5, &ctrlIn);
	
	Dd_Audio_Get_Ctrl_DmaIn(5, &dma);
	
	dma.dma_2ch	= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt = 0;
	
	Dd_Audio_Ctrl_DmaIn(5, &dma);
	
	Dd_Audio_Set_SwapHW_AUIDLR(5, D_DD_AUDIO_ENABLE);
	
	*S_GCt_DD_PDM_DMA_INT_CNT2 = 0;
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_10,
								Dd_Audio_Get_Addr_Reg_AUIDLR(5),
								CtDdPdmTestone_WORK_AREA,
								(3200*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler006);
	
	Dd_Audio_Set_InputDMARequestEnable(5, D_DD_AUDIO_ENABLE);
	
#if 0
	Dd_Pdm_Flush_Dma_Fifo(0);
	
	Dd_Pdm_Set_DMA0_Dst_Addr(0, CtDdPdmTestone_WORK_AREA);
	Dd_Pdm_Set_DMA1_Dst_Addr(0, CtDdPdmTestone_WORK_AREA+0x400);
	
	T_DD_PDM_DMA_LEN pdmLen;
	pdmLen.ttsize =0x400;
	pdmLen.tsize =0x10;
	
	Dd_Pdm_Set_Dma_TransLength(0, &pdmLen);
	
	self->pdmDmaCfg.dma_en = D_DD_PDM_ENABLE;
	Dd_Pdm_Ctrl_Dma(0, &self->pdmDmaCfg);
#endif
	
	Dd_Audio_Start_Input(5);
	
	DDIM_User_Dly_Tsk(2000);
	
	Dd_Audio_Stop_Input(5);
	
	Dd_Audio_Set_InputDMARequestEnable(5, D_DD_AUDIO_DISABLE);
	
	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}
	
	Dd_HDMAC0_Close(0);
	
	Dd_Audio_Close_Input(5);
	
	Dd_Pdm_Stop_Streaming(ch);
	Dd_Pdm_Close(ch);
	
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
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_DMA	dma;
	
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
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}
	
	Dd_Audio_Init();
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);
	
	Dd_Audio_Get_Ctrl_I2sIn(4, &i2sIn);
	
	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	
	Dd_Audio_Ctrl_I2sIn(4, &i2sIn);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Audio_Get_Ctrl_Common(4, &ctrlCommon);
	
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	
	Dd_Audio_Ctrl_Common(4, &ctrlCommon);
	
	Dd_Audio_Get_Ctrl_Input(4, &ctrlIn);
	
	ctrlIn.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlIn.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	
	Dd_Audio_Ctrl_Input(4, &ctrlIn);
	
	Dd_Audio_Get_Ctrl_DmaIn(4, &dma);
	
	dma.dma_2ch	= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt = 0;
	
	Dd_Audio_Ctrl_DmaIn(4, &dma);
	
	Dd_Audio_Set_SwapHW_AUIDLR(4, D_DD_AUDIO_ENABLE);
	
	*S_GCt_DD_PDM_DMA_INT_CNT2 = 0;
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_8,
								Dd_Audio_Get_Addr_Reg_AUIDLR(4),
								CtDdPdmTestone_WORK_AREA,
								(4800*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler007);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_ENABLE);
	
	Dd_Audio_Start_Input(4);
	
	DDIM_User_Dly_Tsk(2000);
	
	Dd_Audio_Stop_Input(4);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_DISABLE);
	
	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}
	
	Dd_HDMAC0_Close(0);
	
	Dd_Audio_Close_Input(4);
	
	Dd_Pdm_Stop_Streaming(ch);
	Dd_Pdm_Close(ch);
	
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
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_DMA	dma;
	
	// Select AUCLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(5);
	
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
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}
	
	Dd_Audio_Init();
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);
	
	Dd_Audio_Get_Ctrl_I2sIn(4, &i2sIn);
	
	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	
	Dd_Audio_Ctrl_I2sIn(4, &i2sIn);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Audio_Get_Ctrl_Common(4, &ctrlCommon);
	
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	
	Dd_Audio_Ctrl_Common(4, &ctrlCommon);
	
	Dd_Audio_Get_Ctrl_Input(4, &ctrlIn);
	
	ctrlIn.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlIn.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	
	Dd_Audio_Ctrl_Input(4, &ctrlIn);
	
	Dd_Audio_Get_Ctrl_DmaIn(4, &dma);
	
	dma.dma_2ch	= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt = 0;
	
	Dd_Audio_Ctrl_DmaIn(4, &dma);
	
	Dd_Audio_Set_SwapHW_AUIDLR(4, D_DD_AUDIO_ENABLE);
	
	*S_GCt_DD_PDM_DMA_INT_CNT2 = 0;
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_8,
								Dd_Audio_Get_Addr_Reg_AUIDLR(4),
								CtDdPdmTestone_WORK_AREA,
								(4800*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler007);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_ENABLE);
	
	Dd_Audio_Start_Input(4);
	
	DDIM_User_Dly_Tsk(2000);
	
	Dd_Audio_Stop_Input(4);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_DISABLE);
	
	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}
	
	Dd_HDMAC0_Close(0);
	
	Dd_Audio_Close_Input(4);
	
	Dd_Pdm_Stop_Streaming(ch);
	Dd_Pdm_Close(ch);
	
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
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_DMA	dma;
	
	// Select AUCLK/2
	Dd_Top_Set_CLKSEL7_PDM0SEL(6);
	
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
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}
	
	Dd_Audio_Init();
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_2;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);
	
	Dd_Audio_Get_Ctrl_I2sIn(4, &i2sIn);
	
	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	
	Dd_Audio_Ctrl_I2sIn(4, &i2sIn);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Audio_Get_Ctrl_Common(4, &ctrlCommon);
	
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	
	Dd_Audio_Ctrl_Common(4, &ctrlCommon);
	
	Dd_Audio_Get_Ctrl_Input(4, &ctrlIn);
	
	ctrlIn.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlIn.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	
	Dd_Audio_Ctrl_Input(4, &ctrlIn);
	
	Dd_Audio_Get_Ctrl_DmaIn(4, &dma);
	
	dma.dma_2ch	= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt = 0;
	
	Dd_Audio_Ctrl_DmaIn(4, &dma);
	
	Dd_Audio_Set_SwapHW_AUIDLR(4, D_DD_AUDIO_ENABLE);
	
	*S_GCt_DD_PDM_DMA_INT_CNT2 = 0;
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_8,
								Dd_Audio_Get_Addr_Reg_AUIDLR(4),
								CtDdPdmTestone_WORK_AREA,
								(4800*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler007);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_ENABLE);
	
	Dd_Audio_Start_Input(4);
	
	DDIM_User_Dly_Tsk(2000);
	
	Dd_Audio_Stop_Input(4);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_DISABLE);
	
	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}
	
	Dd_HDMAC0_Close(0);
	
	Dd_Audio_Close_Input(4);
	
	Dd_Pdm_Stop_Streaming(ch);
	Dd_Pdm_Close(ch);
	
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
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_DMA	dma;
	
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
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}
	
	Dd_Audio_Init();
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);
	
	Dd_Audio_Get_Ctrl_I2sIn(4, &i2sIn);
	
	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	
	Dd_Audio_Ctrl_I2sIn(4, &i2sIn);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Audio_Get_Ctrl_Common(4, &ctrlCommon);
	
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	
	Dd_Audio_Ctrl_Common(4, &ctrlCommon);
	
	Dd_Audio_Get_Ctrl_Input(4, &ctrlIn);
	
	ctrlIn.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlIn.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	
	Dd_Audio_Ctrl_Input(4, &ctrlIn);
	
	Dd_Audio_Get_Ctrl_DmaIn(4, &dma);
	
	dma.dma_2ch	= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt = 0;
	
	Dd_Audio_Ctrl_DmaIn(4, &dma);
	
	Dd_Audio_Set_SwapHW_AUIDLR(4, D_DD_AUDIO_ENABLE);
	
	*S_GCt_DD_PDM_DMA_INT_CNT2 = 0;
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_8,
								Dd_Audio_Get_Addr_Reg_AUIDLR(4),
								CtDdPdmTestone_WORK_AREA,
								(3200*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler010);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_ENABLE);
	
	Dd_Audio_Start_Input(4);
	
	DDIM_User_Dly_Tsk(2000);
	
	Dd_Audio_Stop_Input(4);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_DISABLE);
	
	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}
	
	Dd_HDMAC0_Close(0);
	
	Dd_Audio_Close_Input(4);
	
	Dd_Pdm_Stop_Streaming(ch);
	Dd_Pdm_Close(ch);
	
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
	T_DD_AUDIO_CTRL_COMMON	ctrlCommon;
	T_DD_AUDIO_CTRL_IN	ctrlIn;
	T_DD_AUDIO_I2S_CMMN	i2sCommon;
	T_DD_AUDIO_I2S_IN	i2sIn;
	T_DD_AUDIO_DMA	dma;
	
	// Select AUCLK
	Dd_Top_Set_CLKSEL7_PDM0SEL(5);
	
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
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}
	
	Dd_Audio_Init();
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko = E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);
	
	Dd_Audio_Get_Ctrl_I2sIn(4, &i2sIn);
	
	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	
	Dd_Audio_Ctrl_I2sIn(4, &i2sIn);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Audio_Get_Ctrl_Common(4, &ctrlCommon);
	
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	
	Dd_Audio_Ctrl_Common(4, &ctrlCommon);
	
	Dd_Audio_Get_Ctrl_Input(4, &ctrlIn);
	
	ctrlIn.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifo_stages = E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlIn.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	
	Dd_Audio_Ctrl_Input(4, &ctrlIn);
	
	Dd_Audio_Get_Ctrl_DmaIn(4, &dma);
	
	dma.dma_2ch	= D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt = 0;
	
	Dd_Audio_Ctrl_DmaIn(4, &dma);
	
	Dd_Audio_Set_SwapHW_AUIDLR(4, D_DD_AUDIO_ENABLE);
	
	*S_GCt_DD_PDM_DMA_INT_CNT2 = 0;
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_8,
								Dd_Audio_Get_Addr_Reg_AUIDLR(4),
								CtDdPdmTestone_WORK_AREA,
								(3200*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler010);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_ENABLE);
	
	Dd_Audio_Start_Input(4);
	
	DDIM_User_Dly_Tsk(2000);
	
	Dd_Audio_Stop_Input(4);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_DISABLE);
	
	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}
	
	Dd_HDMAC0_Close(0);
	
	Dd_Audio_Close_Input(4);
	
	Dd_Pdm_Stop_Streaming(ch);
	Dd_Pdm_Close(ch);
	
	Ddim_Print(("> pdm(ES3) 005 : Record PDM0 Clock:8.192MHz(AUCLK) FS=32kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTesttwo));
}

#endif /*CO_ES3_HARDWARE*/

CtDdPdmTesttwo* ct_dd_pdm_testtwo_new(void) 
{
    CtDdPdmTesttwo *self = k_object_new_with_private(CT_TYPE_DD_PDM_TESTTWO, sizeof(CtDdPdmTesttwoPrivate));
    return self;
}
