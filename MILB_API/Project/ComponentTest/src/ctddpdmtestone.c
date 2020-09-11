/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmTestone类
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

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPdmTestone, ct_dd_pdm_testone);
#define CT_DD_PDM_TESTONE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPdmTestonePrivate,CT_TYPE_DD_PDM_TESTONE))

struct _CtDdPdmTestonePrivate
{
	kint a;
};

static volatile kuint32 *S_GCt_DD_PDM_DMA_INT_CNT1;

/*
 *DECLS
 */
#ifdef CO_ES1_HARDWARE
static void 		ctDdPdmDmaIntHandler001(void);
static void 		ctDdPdmDmaIntHandler002(void);
static void 		ctDdPdmDmaIntHandler003(void);
static void 		ctDdPdmDmaIntHandler004(void);
static void 		ctDdPdmDmaIntHandler005(void);
#endif 

static void ct_dd_pdm_testone_constructor(CtDdPdmTestone *self) 
{
	S_GCt_DD_PDM_DMA_INT_CNT1 = &(self->cnt);
}

static void ct_dd_pdm_testone_destructor(CtDdPdmTestone *self) 
{

}

/*
 *IMPL
 */
#ifdef CO_ES1_HARDWARE
static void ctDdPdmDmaIntHandler001( void )
{
	*S_GCt_DD_PDM_DMA_INT_CNT1++;
	
	if ((*S_GCt_DD_PDM_DMA_INT_CNT1 % 2) == 0){
		Dd_Top_Set_Gpio_Status(E_DD_TOP_GPIO_P72, D_DD_TOP_GPIO_STATUS_HIGH);
	}else {
		Dd_Top_Set_Gpio_Status(E_DD_TOP_GPIO_P72, D_DD_TOP_GPIO_STATUS_LOW);
	}
	
	if(*S_GCt_DD_PDM_DMA_INT_CNT1 < 10) {
		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_8,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(4),
									 CtDdPdmTestone_WORK_AREA+(9600*2*2*(*S_GCt_DD_PDM_DMA_INT_CNT1)),
									 (9600*2*2),
									 (VP_CALLBACK)ctDdPdmDmaIntHandler001);
	}
	
	Ddim_Print(("ctDdPdmDmaIntHandler001 \n"));
}

static void ctDdPdmDmaIntHandler002( void )
{
	*S_GCt_DD_PDM_DMA_INT_CNT1++;
	
	if(*S_GCt_DD_PDM_DMA_INT_CNT1 < 10) {
		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_8,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(4),
									 CtDdPdmTestone_WORK_AREA+(4800*2*2*(*S_GCt_DD_PDM_DMA_INT_CNT1)),
									 (4800*2*2),
									 (VP_CALLBACK)ctDdPdmDmaIntHandler002);
	}
	
	Ddim_Print(("ctDdPdmDmaIntHandler002 \n"));
}

static void ctDdPdmDmaIntHandler003( void )
{
	*S_GCt_DD_PDM_DMA_INT_CNT1++;
	
	if(*S_GCt_DD_PDM_DMA_INT_CNT1 < 10) {
		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_8,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(4),
									 CtDdPdmTestone_WORK_AREA+(3200*2*2*(*S_GCt_DD_PDM_DMA_INT_CNT1)),
									 (3200*2*2),
									 (VP_CALLBACK)ctDdPdmDmaIntHandler003);
	}
	
	Ddim_Print(("ctDdPdmDmaIntHandler003 \n"));
}

static void ctDdPdmDmaIntHandler004( void )
{
	*S_GCt_DD_PDM_DMA_INT_CNT1++;
	
	if(*S_GCt_DD_PDM_DMA_INT_CNT1 < 10) {
		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_10,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(5),
									 CtDdPdmTestone_WORK_AREA+(9600*2*2*(*S_GCt_DD_PDM_DMA_INT_CNT1)),
									 (9600*2*2),
									 (VP_CALLBACK)ctDdPdmDmaIntHandler004);
	}
	
	Ddim_Print(("ctDdPdmDmaIntHandler004 \n"));
}

static void ctDdPdmDmaIntHandler005( void )
{
	*S_GCt_DD_PDM_DMA_INT_CNT1++;
	
	if(*S_GCt_DD_PDM_DMA_INT_CNT1 < 10) {
		Dd_HDMAC0_Input_Audio_Async( 0,
									 D_DD_HDMAC0_IS_IDREQ_10,
									 Dd_Audio_Get_Addr_Reg_AUIDLR(5),
									 CtDdPdmTestone_WORK_AREA+(4800*2*2*(*S_GCt_DD_PDM_DMA_INT_CNT1)),
									 (4800*2*2),
									 (VP_CALLBACK)ctDdPdmDmaIntHandler005);
	}
	
	Ddim_Print(("ctDdPdmDmaIntHandler005 \n"));
}
#endif 

/*
 *PUBLIC
 */
void ct_dd_pdm_testone_reg_rw(void)
{
	kuint8 ch;
	
	for (ch = 0; ch <= 1; ch++){
		
		//CORE_CFG
		IO_PDM[ch].CORE_CFG.word = 0xA5A5A5A5;
		if (IO_PDM[ch].CORE_CFG.word == 0xA5A5A5A5){
			Ddim_Print(("CORE_CFG%d Check OK\n", ch));
		}else {
			Ddim_Print(("CORE_CFG%d Check NG[A5]: 0x%08x\n", ch, (kuint)IO_PDM[ch].CORE_CFG.word));
		}

		IO_PDM[ch].CORE_CFG.word = 0x5A5A5A5A;
		if (IO_PDM[ch].CORE_CFG.word == 0x5A5A5A5A){
			Ddim_Print(("CORE_CFG%d Check OK\n", ch));
		}else {
			Ddim_Print(("CORE_CFG%d Check NG[5A]: 0x%08x\n", ch, (kuint)IO_PDM[ch].CORE_CFG.word));
		}
		
		// DMAC_CFG
		IO_PDM[ch].DMA_CFG.word = 0x3F00B4FF;
		if (IO_PDM[ch].DMA_CFG.word == 0x3F00B4FF){
			Ddim_Print(("DMA_CFG%d Check OK\n", ch));
		}else {
			Ddim_Print(("DMA_CFG%d Check NG[A5]: 0x%08x\n", ch, (kuint)IO_PDM[ch].DMA_CFG.word));
		}
		
		IO_PDM[ch].DMA_LEN.word = 0x7FFFFF00;
		if (IO_PDM[ch].DMA_LEN.word == 0x7FFFFF00){
			Ddim_Print(("DMA_LEN%d Check OK\n", ch));
		}else {
			Ddim_Print(("DMA_LEN%d Check NG[5A]: 0x%08x\n", ch, (kuint)IO_PDM[ch].DMA_LEN.word));
		}

		IO_PDM[ch].DMA0_DST_ADDR.word = 0xFFFFFFFC;
		if (IO_PDM[ch].DMA0_DST_ADDR.word == 0xFFFFFFFC){
			Ddim_Print(("DMA0_DST_ADDR%d Check OK\n", ch));
		}else {
			Ddim_Print(("DMA0_DST_ADDR%d Check NG[5A]: 0x%08x\n", ch, (kuint)IO_PDM[ch].DMA0_DST_ADDR.word));
		}
		
		IO_PDM[ch].DMA1_DST_ADDR.word = 0xFFFFFFFC;
		if (IO_PDM[ch].DMA1_DST_ADDR.word == 0xFFFFFFFC){
			Ddim_Print(("DMA1_DST_ADDR%d Check OK\n", ch));
		}else {
			Ddim_Print(("DMA1_DST_ADDR%d Check NG[5A]: 0x%08x\n", ch, (kuint)IO_PDM[ch].DMA1_DST_ADDR.word));
		}

	}
}

#ifdef CO_ES1_HARDWARE
void ct_dd_pdm_testone_001(CtDdPdmTestone * self)
{
	kuint8 ch = 0;
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

	self->self->pdmCfg.mclk_div = 8;
	self->self->pdmCfg.self->pdmCfg.sinc_rate = 8;
	self->self->pdmCfg.self->pdmCfg.pga_r = 0;
	self->self->pdmCfg.self->pdmCfg.pga_l = 0;
	
	Dd_Pdm_Ctrl_Core(ch, &self->pdmCfg);
	
	Dd_Pdm_Get_Ctrl_Dma(ch, &self->pdmDmaCfg);
	self->self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_STEREO;
	self->self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}
	
	Dd_Audio_Init();
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
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
	
	Dd_Audio_Get_Ctrl_Common(4, &ctrlCommon);
	
	ctrlCommon.fifo_usage = E_DD_AUDIO_FIFO_USAGE_STAGES_1;
	ctrlCommon.channel = E_DD_AUDIO_CHANNEL_STEREO;
	
	Dd_Audio_Ctrl_Common(4, &ctrlCommon);
	
	Dd_Audio_Get_Ctrl_Input(4, &ctrlIn);
	
	ctrlIn.format = E_DD_AUDIO_DATA_REG_FRMT_L_JUST;
	ctrlIn.fifo_stages	= E_DD_AUDIO_FIFO_STAGES_16;
	ctrlIn.ahb_format = E_DD_AUDIO_AHB_FRMT_L_JUST;
	ctrlIn.bit_shift = E_DD_AUDIO_BIT_SHIFT_0;
	
	Dd_Audio_Ctrl_Input(4, &ctrlIn);
	
	Dd_Audio_Get_Ctrl_DmaIn(4, &dma);
	
	dma.dma_2ch = D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt = 0;
	
	Dd_Audio_Ctrl_DmaIn(4, &dma);
	
	Dd_Audio_Set_SwapHW_AUIDLR(4, D_DD_AUDIO_ENABLE);
	
	self->cnt = 0;
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_8,
								Dd_Audio_Get_Addr_Reg_AUIDLR(4),
								CtDdPdmTestone_WORK_AREA,
								(9600*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler001);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_ENABLE);
	
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
	
	Ddim_Print(("> pdm 001 : Record PDM0 96kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestone));
}

void ct_dd_pdm_testone_002(CtDdPdmTestone * self)
{
	kuint8 ch = 0;
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
	self->self->pdmCfg.mclk_div = 8;
	self->self->pdmCfg.sinc_rate = 16;
	self->self->pdmCfg.pga_r = 0;
	self->self->pdmCfg.pga_l = 0;
	
	Dd_Pdm_Ctrl_Core(ch, &self->pdmCfg);
	
	Dd_Pdm_Get_Ctrl_Dma(ch, &self->pdmDmaCfg);
	self->self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_STEREO;
	self->self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Pdm_Start_Streaming(ch);
	
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
	
	dma.dma_2ch = D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt = 0;
	
	Dd_Audio_Ctrl_DmaIn(4, &dma);
	
	Dd_Audio_Set_SwapHW_AUIDLR(4, D_DD_AUDIO_ENABLE);
	
	self->cnt = 0;
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_8,
								Dd_Audio_Get_Addr_Reg_AUIDLR(4),
								CtDdPdmTestone_WORK_AREA,
								(4800*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler002);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_ENABLE);
	
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
	
	Ddim_Print(("> pdm 002 : Record PDM0 48kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestone));
}

void ct_dd_pdm_testone_003(CtDdPdmTestone * self)
{
	kuint8 ch = 0;
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
	
	Dd_Pdm_Ctrl_Core(ch, &self->pdmCfg);
	
	Dd_Pdm_Get_Ctrl_Dma(ch, &self->pdmDmaCfg);
	self->pdmDmaCfg.pcm_chset = E_DD_PDM_DMA_PCM_CH_STEREO;
	self->pdmDmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_16;
	Dd_Pdm_Ctrl_Dma(ch, &self->pdmDmaCfg);
	
	Dd_Pdm_Start_Streaming(ch);
	
	Dd_Audio_Open_Input(4, D_DDIM_USER_SEM_WAIT_FEVR);
	
	if(Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Open Error(ch0)\n"));
	}
	
	Dd_Audio_Init();
	
	Dd_Audio_Get_Ctrl_I2sCmmn(4, &i2sCommon);
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_8_192;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_1;
	i2sCommon.div_auclk = E_DD_AUDIO_AUCLK_DIV_4;
	i2sCommon.div_lrclk = E_DD_AUDIO_AULR_DIV_64;
	i2sCommon.clk_div_enable = D_DD_AUDIO_ENABLE;
	i2sCommon.master_slave = E_DD_AUDIO_CLK_MASTER;
	
	Dd_Audio_Ctrl_I2sCmmn(4, &i2sCommon);
	
	Dd_Audio_Get_Ctrl_I2sIn(4, &i2sIn);
	
	i2sIn.mode_in = E_DD_AUDIO_MODE_I2S;
	i2sIn.bit_in = E_DD_AUDIO_BIT_16BIT;
	
	Dd_Audio_Ctrl_I2sIn(4, &i2sIn);
	
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
	
	dma.dma_2ch = D_DD_AUDIO_DISABLE;
	dma.dma_trnsf_cnt = 0;
	
	Dd_Audio_Ctrl_DmaIn(4, &dma);
	
	Dd_Audio_Set_SwapHW_AUIDLR(4, D_DD_AUDIO_ENABLE);
	
	self->cnt = 0;
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_8,
								Dd_Audio_Get_Addr_Reg_AUIDLR(4),
								CtDdPdmTestone_WORK_AREA,
								(3200*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler003);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_ENABLE);
	
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
	
	Dd_Audio_Start_Input(4);
	
	DDIM_User_Dly_Tsk(3000);
	
	Dd_Audio_Stop_Input(4);
	
	Dd_Audio_Set_InputDMARequestEnable(4, D_DD_AUDIO_DISABLE);
	
	if(Dd_HDMAC0_Stop(0) != D_DDIM_OK) {
		Ddim_Print(("Dd_HDMAC0_Stop Error(ch0)\n"));
	}
	
	Dd_HDMAC0_Close(0);
	
	Dd_Audio_Close_Input(4);
	
	Dd_Pdm_Stop_Streaming(ch);
	Dd_Pdm_Close(ch);
	
	Ddim_Print(("> pdm 003 : Record PDM0 32kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestone));
}

void ct_dd_pdm_testone_004(CtDdPdmTestone * self)
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
	self->pdmCfg.sinc_rate = 8;
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
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_1;
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
	
	self->cnt = 0;
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_10,
								Dd_Audio_Get_Addr_Reg_AUIDLR(5),
								CtDdPdmTestone_WORK_AREA,
								(9600*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler004);
	
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
	
	Ddim_Print(("> pdm 004 : Record PDM1 96kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestone));
}

void ct_dd_pdm_testone_005(CtDdPdmTestone * self)
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
	self->pdmCfg.sinc_rate = 16;
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
	
	i2sCommon.aumclki = E_DD_AUDIO_MASTER_CLOCK_24_576;
	i2sCommon.div_aumclko =  E_DD_AUDIO_AUMCLKO_DIV_2;
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
	
	self->cnt = 0;
	Dd_HDMAC0_Input_Audio_Async(0,
								D_DD_HDMAC0_IS_IDREQ_10,
								Dd_Audio_Get_Addr_Reg_AUIDLR(5),
								CtDdPdmTestone_WORK_AREA,
								(4800*2*2),
								(VP_CALLBACK)ctDdPdmDmaIntHandler005);
	
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
	
	Ddim_Print(("> pdm 005 : Record PDM1 48kHz test\n"));
	memset(self,0,sizeof(CtDdPdmTestone));
}
#endif /*CO_ES1_HARDWARE*/

CtDdPdmTestone* ct_dd_pdm_testone_new(void) 
{
    CtDdPdmTestone *self = k_object_new_with_private(CT_TYPE_DD_PDM_TESTONE, sizeof(CtDdPdmTestonePrivate));

    return self;
}
