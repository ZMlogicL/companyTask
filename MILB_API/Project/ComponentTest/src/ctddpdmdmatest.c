/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmDmatest类
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
#include "ctddpdmothertest.h"
#include "ctddpdmmain.h"
#include "ctddpdmdmatest.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPdmDmatest, ct_dd_pdm_dmatest);
#define CT_DD_PDM_DMATEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPdmDmatestPrivate,CT_TYPE_DD_PDM_DMATEST))

struct _CtDdPdmDmatestPrivate
{
	kint a;
};

static void ct_dd_pdm_dmatest_constructor(CtDdPdmDmatest *self) 
{
	self->test = NULL;
}

static void ct_dd_pdm_dmatest_destructor(CtDdPdmDmatest *self) 
{
	self->test = NULL;
}

/*
 *PUBLIC
 */
void ct_dd_pdm_dmatest_set_test(CtDdPdmDmatest *self,CtDdPdmOthertest *test)
{
	self->test = test;
}

void ct_dd_pdm_dmatest_ctrl(CtDdPdmDmatest *self)
{
	kint32 result;
	T_DD_PDM_DMA_CFG dmaCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	dmaCfg.dmick_dly	= 1;
	dmaCfg.dma_burstlen = E_DD_PDM_DMA_BURST_LEN_1;
	dmaCfg.pcm_chset	 = E_DD_PDM_DMA_PCM_CH_STEREO;
	dmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_24;
	dmaCfg.dma_en	 = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMICK_DLY=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMICK_DLY));
		Ddim_Print(("DMA_BURSTLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_BURSTLEN));
		Ddim_Print(("PCM_CHSET=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_CHSET));
		Ddim_Print(("PCM_WDLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_WDLEN));
		Ddim_Print(("DMA_EN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_EN));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_ctrl_e1(CtDdPdmDmatest *self)
{
	kint32 result;
	T_DD_PDM_DMA_CFG dmaCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	dmaCfg.dmick_dly	= 4;
	dmaCfg.dma_burstlen = E_DD_PDM_DMA_BURST_LEN_1;
	dmaCfg.pcm_chset	 = E_DD_PDM_DMA_PCM_CH_STEREO;
	dmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_24;
	dmaCfg.dma_en	 = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMICK_DLY=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMICK_DLY));
		Ddim_Print(("DMA_BURSTLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_BURSTLEN));
		Ddim_Print(("PCM_CHSET=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_CHSET));
		Ddim_Print(("PCM_WDLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_WDLEN));
		Ddim_Print(("DMA_EN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_EN));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_ctrl_e2(CtDdPdmDmatest *self)
{
	kint32 result;
	T_DD_PDM_DMA_CFG dmaCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	dmaCfg.dmick_dly = 1;
	dmaCfg.dma_burstlen = (E_DD_PDM_DMA_BURST_LEN)4;
	dmaCfg.pcm_chset	 = E_DD_PDM_DMA_PCM_CH_STEREO;
	dmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_24;
	dmaCfg.dma_en = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMICK_DLY=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMICK_DLY));
		Ddim_Print(("DMA_BURSTLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_BURSTLEN));
		Ddim_Print(("PCM_CHSET=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_CHSET));
		Ddim_Print(("PCM_WDLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_WDLEN));
		Ddim_Print(("DMA_EN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_EN));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_ctrl_e3(CtDdPdmDmatest *self)
{
	kint32 result;
	T_DD_PDM_DMA_CFG dmaCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	dmaCfg.dmick_dly = 1;
	dmaCfg.dma_burstlen = E_DD_PDM_DMA_BURST_LEN_1;
	dmaCfg.pcm_chset	 = (E_DD_PDM_DMA_PCM_CH)4;
	dmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_24;
	dmaCfg.dma_en = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMICK_DLY=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMICK_DLY));
		Ddim_Print(("DMA_BURSTLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_BURSTLEN));
		Ddim_Print(("PCM_CHSET=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_CHSET));
		Ddim_Print(("PCM_WDLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_WDLEN));
		Ddim_Print(("DMA_EN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_EN));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_ctrl_e4(CtDdPdmDmatest *self)
{
	kint32 result;
	T_DD_PDM_DMA_CFG dmaCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	dmaCfg.dmick_dly = 1;
	dmaCfg.dma_burstlen = E_DD_PDM_DMA_BURST_LEN_1;
	dmaCfg.pcm_chset	 = E_DD_PDM_DMA_PCM_CH_STEREO;
	dmaCfg.pcm_wdlen = (E_DD_PDM_DMA_PCM_WD)4;
	dmaCfg.dma_en = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMICK_DLY=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMICK_DLY));
		Ddim_Print(("DMA_BURSTLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_BURSTLEN));
		Ddim_Print(("PCM_CHSET=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_CHSET));
		Ddim_Print(("PCM_WDLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_WDLEN));
		Ddim_Print(("DMA_EN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_EN));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_ctrl_e5(CtDdPdmDmatest *self)
{
	kint32 result;
	T_DD_PDM_DMA_CFG dmaCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	dmaCfg.dmick_dly = 1;
	dmaCfg.dma_burstlen = E_DD_PDM_DMA_BURST_LEN_1;
	dmaCfg.pcm_chset	 = E_DD_PDM_DMA_PCM_CH_STEREO;
	dmaCfg.pcm_wdlen = E_DD_PDM_DMA_PCM_WD_24;
	dmaCfg.dma_en = 2;
	
	result = Dd_Pdm_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMICK_DLY=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMICK_DLY));
		Ddim_Print(("DMA_BURSTLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_BURSTLEN));
		Ddim_Print(("PCM_CHSET=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_CHSET));
		Ddim_Print(("PCM_WDLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_WDLEN));
		Ddim_Print(("DMA_EN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_EN));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_ctrl_e6(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Ctrl_Dma(self->test->ch, NULL);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMICK_DLY=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMICK_DLY));
		Ddim_Print(("DMA_BURSTLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_BURSTLEN));
		Ddim_Print(("PCM_CHSET=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_CHSET));
		Ddim_Print(("PCM_WDLEN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.PCM_WDLEN));
		Ddim_Print(("DMA_EN=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.DMA_EN));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_get_ctrl(CtDdPdmDmatest *self)
{
	kint32 result;
	T_DD_PDM_DMA_CFG dmaCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	result = Dd_Pdm_Get_Ctrl_Dma(self->test->ch, &dmaCfg);
	
	Ddim_Print(("dmick_dly=0x%x\n", dmaCfg.dmick_dly));
	Ddim_Print(("dma_burstlen=0x%x\n", dmaCfg.dma_burstlen));
	Ddim_Print(("pcm_chset=0x%x\n", dmaCfg.pcm_chset));
	Ddim_Print(("pcm_wdlen=0x%x\n", dmaCfg.pcm_wdlen));
	Ddim_Print(("dma_en=0x%x\n", dmaCfg.dma_en));
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_get_ctrl_e1(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Get_Ctrl_Dma(self->test->ch, NULL);
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_callback_dma0_intr_test(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Set_CallbackDma0Intr(self->test->ch, NULL);
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_callback_dma1_intr_test(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Set_CallbackDma1Intr(self->test->ch, NULL);
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_enable_dma0_intr_test1(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Set_EnableDma0Intr(self->test->ch, D_DD_PDM_ENABLE);
	
	if (self->test->ch <= 1){
		Ddim_Print(("CLR_IRQ_DMA0=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.CLR_IRQ_DMA0));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_enable_dma0_intr_test2(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Set_EnableDma0Intr(self->test->ch, D_DD_PDM_DISABLE);
	
	if (self->test->ch <= 1){
		Ddim_Print(("CLR_IRQ_DMA0=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.CLR_IRQ_DMA0));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_enable_dma0_intr_test_e1(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Set_EnableDma0Intr(self->test->ch, 2);
	
	if (self->test->ch <= 1){
		Ddim_Print(("CLR_IRQ_DMA0=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.CLR_IRQ_DMA0));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_enable_dma1_intr_test1(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Set_EnableDma1Intr(self->test->ch, D_DD_PDM_ENABLE);
	
	if (self->test->ch <= 1){
		Ddim_Print(("CLR_IRQ_DMA1=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.CLR_IRQ_DMA1));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_enable_dma1_intr_test2(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Set_EnableDma1Intr(self->test->ch, D_DD_PDM_DISABLE);
	
	if (self->test->ch <= 1){
		Ddim_Print(("CLR_IRQ_DMA1=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.CLR_IRQ_DMA1));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_enable_dma1_intr_test_e1(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	Dd_Pdm_Init();
	
	result = Dd_Pdm_Set_EnableDma1Intr(self->test->ch, 2);
	
	if (self->test->ch <= 1){
		Ddim_Print(("CLR_IRQ_DMA1=%d\n", IO_PDM[self->test->ch].DMA_CFG.bit.CLR_IRQ_DMA1));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_dma0_dst_addr_test(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Set_DMA0_Dst_Addr(self->test->ch, 0x70000000);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMA0_DST_ADDR=0x%x\n", (kuint)IO_PDM[self->test->ch].DMA0_DST_ADDR.word));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_dma1_dst_addr_test(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Set_DMA1_Dst_Addr(self->test->ch, 0x71000000);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMA1_DST_ADDR=0x%x\n", (kuint)IO_PDM[self->test->ch].DMA1_DST_ADDR.word));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_dma_trans_length_test(CtDdPdmDmatest *self)
{
	kint32 result;
	T_DD_PDM_DMA_LEN dmaLen;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dmaLen.ttsize = 0x20;
	dmaLen.tsize = 0x10;
	
	result = Dd_Pdm_Set_Dma_TransLength(self->test->ch, &dmaLen);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMA_TTSIZE=0x%x\n", IO_PDM[self->test->ch].DMA_LEN.bit.DMA_TTSIZE));
		Ddim_Print(("DMA_TSIZE=0x%x\n", IO_PDM[self->test->ch].DMA_LEN.bit.DMA_TSIZE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_dma_trans_length_test_e1(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Set_Dma_TransLength(self->test->ch, NULL);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMA_TTSIZE=0x%x\n", IO_PDM[self->test->ch].DMA_LEN.bit.DMA_TTSIZE));
		Ddim_Print(("DMA_TSIZE=0x%x\n", IO_PDM[self->test->ch].DMA_LEN.bit.DMA_TSIZE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_dma_trans_length_test_e2(CtDdPdmDmatest *self)
{
	kint32 result;
	T_DD_PDM_DMA_LEN dmaLen;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dmaLen.ttsize = 0;
	dmaLen.tsize = 0x10;
	
	result = Dd_Pdm_Set_Dma_TransLength(self->test->ch, &dmaLen);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMA_TTSIZE=0x%x\n", IO_PDM[self->test->ch].DMA_LEN.bit.DMA_TTSIZE));
		Ddim_Print(("DMA_TSIZE=0x%x\n", IO_PDM[self->test->ch].DMA_LEN.bit.DMA_TSIZE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_dma_trans_length_test_e3(CtDdPdmDmatest *self)
{
	kint32 result;
	T_DD_PDM_DMA_LEN dmaLen;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dmaLen.ttsize = 0x8000;
	dmaLen.tsize = 0x10;
	
	result = Dd_Pdm_Set_Dma_TransLength(self->test->ch, &dmaLen);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMA_TTSIZE=0x%x\n", IO_PDM[self->test->ch].DMA_LEN.bit.DMA_TTSIZE));
		Ddim_Print(("DMA_TSIZE=0x%x\n", IO_PDM[self->test->ch].DMA_LEN.bit.DMA_TSIZE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_set_dma_trans_length_test_e4(CtDdPdmDmatest *self)
{
	kint32 result;
	T_DD_PDM_DMA_LEN dmaLen;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dmaLen.ttsize = 0x20;
	dmaLen.tsize = 0;
	
	result = Dd_Pdm_Set_Dma_TransLength(self->test->ch, &dmaLen);
	
	if (self->test->ch <= 1){
		Ddim_Print(("DMA_TTSIZE=0x%x\n", IO_PDM[self->test->ch].DMA_LEN.bit.DMA_TTSIZE));
		Ddim_Print(("DMA_TSIZE=0x%x\n", IO_PDM[self->test->ch].DMA_LEN.bit.DMA_TSIZE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_dmatest_flush_dma_fifo_test(CtDdPdmDmatest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	result = Dd_Pdm_Flush_Dma_Fifo(self->test->ch);
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

CtDdPdmDmatest* ct_dd_pdm_dmatest_new(void) 
{
    CtDdPdmDmatest *self = k_object_new_with_private(CT_TYPE_DD_PDM_DMATEST, sizeof(CtDdPdmDmatestPrivate));
    return self;
}
