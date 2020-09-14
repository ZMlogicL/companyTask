/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmMain类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#include <string.h>
#include <stdlib.h>
#include "pdm.h"
#include "dd_pdm.h"
#include "ct_dd_pdm.h"
// #include "dd_top.h"
// #include "dd_cache.h"
// #include "dd_gic.h"
// #include "dd_audio.h"
// #include "dd_hdmac0.h"
#include "../../DeviceDriver/Peripheral/src/ddpdm.h"
#include "../../DeviceDriver/LSITop/src/ddtopone.h"
#include "../../DeviceDriver/ARM/src/ddcacheasm.h"
#include "../../DeviceDriver/ARM/src/ddgic.h"
#include "../../DeviceDriver/Peripheral/src/ddaudio.h"
#include "../../DeviceDriver/Peripheral/src/ddhdmac0.h"
#include "../../../MILB_Header/Project/Top/src/kchiptop1.h"
#include "peripheral.h"
#include "ctddpdmcoretest.h"
#include "ctddpdmdmatest.h"
#include "ctddpdmothertest.h"
#include "ctddpdmstatustest.h"
#include "ctddpdmtestone.h"
#include "ctddpdmtesttwo.h"
#include "ctddpdmtestthree.h"
#include "ctddpdmtestfour.h"
#include "ctddpdmtestfive.h"
#include "ctddpdmtestsix.h"
#include "ctddpdmmain.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPdmMain, ct_dd_pdm_main);
#define CT_DD_PDM_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPdmMainPrivate,CT_TYPE_DD_PDM_MAIN))

struct _CtDdPdmMainPrivate
{
    CtDdPdmOthertest* test;
};

static void ct_dd_pdm_main_constructor(CtDdPdmMain *self) 
{
	CtDdPdmMainPrivate *priv = CT_DD_PDM_MAIN_GET_PRIVATE(self);

	priv->test = ct_dd_pdm_othertest_new();
}

static void ct_dd_pdm_main_destructor(CtDdPdmMain *self) 
{
	CtDdPdmMainPrivate *priv = CT_DD_PDM_MAIN_GET_PRIVATE(self);

	if(priv->test){
		k_object_unref(priv->test);
		priv->test = NULL;
	}
}

/*
 *PUBLIC
 */
void ct_dd_pdm_main_reg_init(void)
{
#ifdef PC_DEBUG
	ioChiptop.IoChiptopPllcnt1.bit.pl10st = 1;
	IO_PDM[0].CORE_CFG.word = 0x00084365;
	IO_PDM[1].CORE_CFG.word = 0x00084365;
	IO_PDM[0].DMA_CFG.word = 0x00000069;
	IO_PDM[1].DMA_CFG.word = 0x00000069;
#endif
}

void ct_dd_pdm_main_init_test(CtDdPdmMain *self)
{
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	ct_dd_pdm_main_reg_init();
	
	dd_pdm_init(dd_pdm_get());
	
	Ddim_Print(("PDM0.PDMCORE_EN=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH0].CORE_CFG.bit.PDMCORE_EN));
	Ddim_Print(("PDM1.PDMCORE_EN=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH1].CORE_CFG.bit.PDMCORE_EN));
	
	Ddim_Print(("PDM0.DMA_EN=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH0].DMA_CFG.bit.DMA_EN));
	Ddim_Print(("PDM1.DMA_EN=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH1].DMA_CFG.bit.DMA_EN));
	
	Ddim_Print(("PDM0.CLR_IRQ_FFOVF=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH0].DMA_CFG.bit.CLR_IRQ_FFOVF));
	Ddim_Print(("PDM1.CLR_IRQ_FFOVF=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH1].DMA_CFG.bit.CLR_IRQ_FFOVF));
	
	Ddim_Print(("PDM0.CLR_IRQ_DMA1=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH0].DMA_CFG.bit.CLR_IRQ_DMA1));
	Ddim_Print(("PDM1.CLR_IRQ_DMA1=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH1].DMA_CFG.bit.CLR_IRQ_DMA1));
	
	Ddim_Print(("PDM0.CLR_IRQ_DMA0=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH0].DMA_CFG.bit.CLR_IRQ_DMA0));
	Ddim_Print(("PDM1.CLR_IRQ_DMA0=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH1].DMA_CFG.bit.CLR_IRQ_DMA0));
	
	Ddim_Print(("PDM0.DMA0_INT_REG=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH0].STATUS.bit.DMA0_INT_REG));
	Ddim_Print(("PDM1.DMA0_INT_REG=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH1].STATUS.bit.DMA0_INT_REG));
	
	Ddim_Print(("PDM0.DMA1_INT_REG=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH0].STATUS.bit.DMA1_INT_REG));
	Ddim_Print(("PDM1.DMA1_INT_REG=0x%x\n", IO_PDM[AudioPdm_D_AUDIO_PDM_CH1].STATUS.bit.DMA1_INT_REG));
	
	Ddim_Print(("<%s> End.\n", __FUNCTION__));
}

/**
 * @brief		Command processing of dd_pdm_if.h
 * @param[in]	kint32 argc
 * @param[in]	kchar** argv
 * @return		None
 * @note		Command processing of MBch.
 * @attention	None
 */
void ct_dd_pdm_main(CtDdPdmMain *self,kint argc, kchar** argv)
{
	CtDdPdmMainPrivate *priv = CT_DD_PDM_MAIN_GET_PRIVATE(self);
	CtDdPdmOthertest *test = priv->test;
	CtDdPdmStatustest *st = ct_dd_pdm_statustest_new();
	CtDdPdmCoretest *ct = ct_dd_pdm_coretest_new();
	CtDdPdmDmatest *dt = ct_dd_pdm_dmatest_new();

	ct_dd_pdm_statustest_set_test(st,priv->test);
	ct_dd_pdm_coretest_set_test(ct, priv->test);
	ct_dd_pdm_dmatest_set_test(dt,priv->test);

	Dd_CACHE_L1_Clean_Flush_Dcache_All();
	Dd_CACHE_L2_Clean_Flush_Dcache_All();
	
	if(atoi(argv[1]) == 1) {
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	/* Select PDM CLK */
	DdTopone_SET_CLKSEL7_PDM0SEL(4);
	DdTopone_SET_CLKSEL7_PDM1SEL(4);
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		switch (atoi(argv[2])) {
			case 1:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_opentest1(test);
				break;
			case 2:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_opentest2(test);
				break;
			case 3:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_opentest3(test);
				break;
			case 4:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_othertest_opentest1(test);
				break;
			case 5:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_othertest_opentest2(test);
				break;
			case 6:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_othertest_opentest3(test);
				break;
			case 7:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_closetest(test);
				break;
			case 8:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_othertest_closetest(test);
				break;
			case 9:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_dma0_int_handler_test(test);
				break;
			case 10:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_othertest_dma0_int_handler_test(test);
				break;
			case 11:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_dma1_int_handler_test(test);
				break;
			case 12:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_othertest_dma1_int_handler_test(test);
				break;
			case 13:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_overflow_int_handler_test(test);
				break;
			case 14:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_othertest_overflow_int_handler_test(test);
				break;
			case 15:
				ct_dd_pdm_main_init_test(self);
				break;
			case 16:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_coretest_ctrl(ct);
				break;
			case 17:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_coretest_ctrl(ct);
				break;
			case 18:
				dd_pdm_init(dd_pdm_get());
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_coretest_get_ctrl(ct);
				break;
			case 19:
				dd_pdm_init(dd_pdm_get());
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_coretest_get_ctrl(ct);
				break;
			case 20:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_start_streaming_test(test);
				break;
			case 21:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_othertest_start_streaming_test(test);
				break;
			case 22:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_stop_streaming_test(test);
				break;
			case 23:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_othertest_stop_streaming_test(test);
				break;
			case 24:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_ctrl(dt);
				break;
			case 25:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_dmatest_ctrl(dt);
				break;
			case 26:
				dd_pdm_init(dd_pdm_get());
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_get_ctrl(dt);
				break;
			case 27:
				dd_pdm_init(dd_pdm_get());
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_dmatest_get_ctrl(dt);
				break;
			case 28:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_callback_dma0_intr_test(dt);
				break;
			case 29:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_dmatest_set_callback_dma0_intr_test(dt);
				break;
			case 30:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_callback_dma1_intr_test(dt);
				break;
			case 31:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_dmatest_set_callback_dma1_intr_test(dt);
				break;
			case 32:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_set_callback_overflow_intr_test(test);
				break;
			case 33:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_othertest_set_callback_overflow_intr_test(test);
				break;
			case 34:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_enable_dma0_intr_test1(dt);
				break;
			case 35:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_dmatest_set_enable_dma0_intr_test2(dt);
				break;
			case 36:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_enable_dma1_intr_test1(dt);
				break;
			case 37:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_dmatest_set_enable_dma1_intr_test2(dt);
				break;
			case 38:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_set_enable_overflow_intr_test1(test);
				break;
			case 39:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_othertest_set_enable_overflow_intr_test2(test);
				break;
			case 40:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_dma0_dst_addr_test(dt);
				break;
			case 41:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_dmatest_set_dma0_dst_addr_test(dt);
				break;
			case 42:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_dma1_dst_addr_test(dt);
				break;
			case 43:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_dmatest_set_dma1_dst_addr_test(dt);
				break;
			case 44:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_dma_trans_length_test(dt);
				break;
			case 45:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_dmatest_set_dma_trans_length_test(dt);
				break;
			case 46:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_flush_dma_fifo_test(dt);
				break;
			case 47:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_dmatest_flush_dma_fifo_test(dt);
				break;
			case 48:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_statustest_get(st);
				break;
			case 49:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_statustest_get2(st);
				break;
			case 50:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_statustest_get3(st);
				break;
			case 51:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_statustest_get(st);
				break;
			case 52:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_statustest_get2(st);
				break;
			case 53:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_statustest_get3(st);
				break;
			case 54:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_statustest_clear1(st);
				break;
			case 55:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_statustest_clear2(st);
				break;
			case 56:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_statustest_clear3(st);
				break;
			case 57:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_statustest_clear1(st);
				break;
			case 58:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_statustest_clear2(st);
				break;
			case 59:
				ct_dd_pdm_othertest_set_ch(test,1);
				ct_dd_pdm_statustest_clear3(st);
				break;
			default :
				Ddim_Print(("ddpdm : ERROR command line\n"));
				break;
		}
	}
	else if(atoi(argv[1]) == 2) {
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	/* Select PDM CLK */
	DdTopone_SET_CLKSEL7_PDM0SEL(4);
	DdTopone_SET_CLKSEL7_PDM1SEL(4);
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

		switch (atoi(argv[2])) {
			case 1:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_othertest_opentest1(test);
				break;
			case 2:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_opentest_e1(test);
				break;
			case 3:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_opentest_e2(test);
				break;
			case 4:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_othertest_closetest(test);
				break;
			case 5:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_othertest_dma0_int_handler_test(test);
				break;
			case 6:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_othertest_dma1_int_handler_test(test);
				break;
			case 7:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_othertest_overflow_int_handler_test(test);
				break;
			case 8:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_coretest_ctrl(ct);
				break;
			case 9:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_coretest_ctrl_e1(ct);
				break;
			case 10:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_coretest_ctrl_e2(ct);
				break;
			case 11:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_coretest_ctrl_e3(ct);
				break;
			case 12:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_coretest_ctrl_e4(ct);
				break;
			case 13:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_coretest_ctrl_e5(ct);
				break;
			case 14:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_coretest_ctrl_e6(ct);
				break;
			case 15:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_coretest_ctrl_e7(ct);
				break;
			case 16:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_coretest_ctrl_e8(ct);
				break;
			case 17:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_coretest_ctrl_e9(ct);
				break;
			case 18:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_coretest_get_ctrl(ct);
				break;
			case 19:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_coretest_get_ctrl_e1(ct);
				break;
			case 20:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_othertest_start_streaming_test(test);
				break;
			case 21:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_othertest_stop_streaming_test(test);
				break;
			case 22:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_dmatest_ctrl(dt);
				break;
			case 23:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_ctrl_e1(dt);
				break;
			case 24:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_ctrl_e2(dt);
				break;
			case 25:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_ctrl_e3(dt);
				break;
			case 26:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_ctrl_e4(dt);
				break;
			case 27:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_ctrl_e5(dt);
				break;
			case 28:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_ctrl_e6(dt);
				break;
			case 29:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_dmatest_get_ctrl(dt);
				break;
			case 30:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_get_ctrl_e1(dt);
				break;
			case 31:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_dmatest_set_callback_dma0_intr_test(dt);
				break;
			case 32:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_dmatest_set_callback_dma1_intr_test(dt);
				break;
			case 33:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_othertest_set_callback_overflow_intr_test(test);
				break;
			case 34:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_dmatest_set_enable_dma0_intr_test1(dt);
				break;
			case 35:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_enable_dma0_intr_test_e1(dt);
				break;
			case 36:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_dmatest_set_enable_dma1_intr_test1(dt);
				break;
			case 37:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_enable_dma1_intr_test_e1(dt);
				break;
			case 38:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_othertest_set_enable_overflow_intr_test1(test);
				break;
			case 39:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_othertest_set_enable_overflow_intr_test_e1(test);
				break;
			case 40:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_dmatest_set_dma0_dst_addr_test(dt);
				break;
			case 41:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_dmatest_set_dma1_dst_addr_test(dt);
				break;
			case 42:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_dmatest_set_dma_trans_length_test(dt);
				break;
			case 43:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_dma_trans_length_test_e1(dt);
				break;
			case 44:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_dma_trans_length_test_e2(dt);
				break;
			case 45:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_dma_trans_length_test_e3(dt);
				break;
			case 46:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_dmatest_set_dma_trans_length_test_e4(dt);
				break;
			case 47:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_dmatest_flush_dma_fifo_test(dt);
				break;
			case 48:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_statustest_get(st);
				break;
			case 49:
				ct_dd_pdm_othertest_set_ch(test,0);
				ct_dd_pdm_statustest_get_get_e1(st);
				break;
			case 50:
				ct_dd_pdm_othertest_set_ch(test,2);
				ct_dd_pdm_statustest_clear1(st);
				break;
			default :
				Ddim_Print(("ddpdm : ERROR command line\n"));
				break;
		}
	}
	else if(atoi(argv[1]) == 3) {
		CtDdPdmTestone *test1 = ct_dd_pdm_testone_new();
		CtDdPdmTesttwo *test2 = ct_dd_pdm_testtwo_new();
		CtDdPdmTestthree *test3 = ct_dd_pdm_testthree_new();
		CtDdPdmTestfour *test4 = ct_dd_pdm_testfour_new();
		CtDdPdmTestfive *test5 = ct_dd_pdm_testfive_new();
		CtDdPdmTestsix *test6 = ct_dd_pdm_testsix_new();
		
		ct_dd_pdm_testtwo_set_addr(test2,test1);
		ct_dd_pdm_testthree_set_addr(test3,test1);
		ct_dd_pdm_testfour_set_addr(test4,test1);
		ct_dd_pdm_testfive_set_addr(test5,test1);
		ct_dd_pdm_testsix_set_addr(test6,test1);
		
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		DDIM_User_EnableInt((DDIM_USER_INTID)(DdGic_INTID_PDM_CH0_DMA0_INT), (DDIM_USER_INTID)C_PRI08);
		DDIM_User_EnableInt((DDIM_USER_INTID)(DdGic_INTID_PDM_CH0_DMA1_INT), (DDIM_USER_INTID)C_PRI08);
		DDIM_User_EnableInt((DDIM_USER_INTID)(DdGic_INTID_PDM_CH0_FIFO_OVERFLOW_INT), (DDIM_USER_INTID)C_PRI08);
		DDIM_User_EnableInt((DDIM_USER_INTID)(DdGic_INTID_PDM_CH1_DMA0_INT), (DDIM_USER_INTID)C_PRI08);
		DDIM_User_EnableInt((DDIM_USER_INTID)(DdGic_INTID_PDM_CH1_DMA1_INT), (DDIM_USER_INTID)C_PRI08);
		DDIM_User_EnableInt((DDIM_USER_INTID)(DdGic_INTID_PDM_CH1_FIFO_OVERFLOW_INT), (DDIM_USER_INTID)C_PRI08);
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		
		switch (atoi(argv[2])) {
			case 0:
				ct_dd_pdm_testone_reg_rw();
				break;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
			case 1:
				ct_dd_pdm_testone_001(test1);
				break;
			case 2:
				ct_dd_pdm_testone_002(test1);
				break;
			case 3:
				ct_dd_pdm_testone_003(test1);
				break;
			case 4:
				ct_dd_pdm_testone_004(test1);
				break;
			case 5:
				ct_dd_pdm_testone_005(test1);
				break;
			case 6:
				ct_dd_pdm_testtwo_006(test2);
				break;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
			case 7:
				ct_dd_pdm_testtwo_007(test2);
				break;
			case 8:
				ct_dd_pdm_testtwo_008(test2);
				break;
			case 9:
				ct_dd_pdm_testtwo_009(test2);
				break;
			case 10:
				ct_dd_pdm_testtwo_010(test2);
				break;
			case 11:
				ct_dd_pdm_testtwo_011(test2);
				break;
			case 12:
				ct_dd_pdm_testthree_012(test3);
				break;
			case 13:
				ct_dd_pdm_testthree_013(test3);
				break;
			case 14:
				ct_dd_pdm_testthree_014(test3);
				break;
			case 15:
				ct_dd_pdm_testthree_015(test3);
				break;
			case 16:
				ct_dd_pdm_testthree_016(test3);
				break;
			case 17:
				ct_dd_pdm_testthree_017(test3);
				break;
			case 18:
				ct_dd_pdm_testthree_018(test3);
				break;
			case 19:
				ct_dd_pdm_testfour_019(test4);
				break;
			case 20:
				ct_dd_pdm_testfour_020(test4);
				break;
			case 21:
				ct_dd_pdm_testfour_021(test4);
				break;
			case 22:
				ct_dd_pdm_testfour_022(test4);
				break;
			case 23:
				ct_dd_pdm_testfour_023(test4);
				break;
			case 24:
				ct_dd_pdm_testfour_024(test4);
				break;
			case 25:
				ct_dd_pdm_testfour_025(test4);
				break;
			case 26:
				ct_dd_pdm_testfive_026(test5);
				break;
			case 27:
				ct_dd_pdm_testfive_027(test5);
				break;
			case 28:
				ct_dd_pdm_testfive_028(test5);
				break;
			case 29:
				ct_dd_pdm_testfive_029(test5);
				break;
			case 30:
				ct_dd_pdm_testfive_030(test5);
				break;
			case 31:
				ct_dd_pdm_testfive_031(test5);
				break;
			case 32:
				ct_dd_pdm_testfive_032(test5);
				break;
			case 33:
				ct_dd_pdm_testfive_033(test5);
				break;
			case 34:
				ct_dd_pdm_testfive_034(test5);
				break;
			case 35:
				ct_dd_pdm_testfive_035(test5);
				break;
			case 36:
				ct_dd_pdm_testfive_036(test5);
				break;
			case 37:
				ct_dd_pdm_testsix_037(test6);
				break;
			case 38:
				ct_dd_pdm_testsix_038(test6);
				break;
			case 39:
				ct_dd_pdm_testsix_039(test6);
				break;
			case 40:
				ct_dd_pdm_testsix_040(test6);
				break;
			case 41:
				ct_dd_pdm_testsix_041(test6);
				break;
			case 42:
				ct_dd_pdm_testsix_042(test6);
				break;
			case 43:
				ct_dd_pdm_testsix_043(test6);
				break;
			case 44:
				ct_dd_pdm_testsix_044(test6);
				break;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
			default :
				Ddim_Print(("ddpdm : ERROR command line\n"));
				break;
		}

	k_object_unref(test1);
	k_object_unref(test2);
	k_object_unref(test3);
	k_object_unref(test4);
	k_object_unref(test5);
	k_object_unref(test6);

	}

	else {
		Ddim_Print(("ddpdm : ERROR command line\n"));
	}

	k_object_unref(st);
	k_object_unref(ct);
	k_object_unref(dt);

	Dd_CACHE_L1_Clean_Flush_Dcache_All();
	Dd_CACHE_L2_Clean_Flush_Dcache_All();
}

CtDdPdmMain* ct_dd_pdm_main_new(void) 
{
    CtDdPdmMain *self = k_object_new_with_private(CT_TYPE_DD_PDM_MAIN, sizeof(CtDdPdmMainPrivate));

    return self;
}
