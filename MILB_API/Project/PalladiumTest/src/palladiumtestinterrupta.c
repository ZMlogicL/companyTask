/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-09-3
*@author              :hubing
*@brief               :snsos
*@rely                :klib
*@function
*采用ETK-C语言抄写代码
*设计的主要功能:
*@version
*1.0.0 2020年06月开始开发
*1.0.0
*/
/**
 * 以下开始include语句
 */
#include "palladium_test_interrupt.h"
#include "palladium_test.h"
#include "driver_common.h"
#include "dd_tmr32.h"
#include "im_b2r.h"
#include "im_bmh.h"
#include "im_cnr.h"
#include "im_ela.h"
#include "im_fpt.h"
#include "im_iip.h"
#include "im_ltm.h"
#include "im_mxic.h"
#include "im_r2y.h"
#include "im_raw.h"
#include "im_sdramc.h"
#include "im_shdr.h"
#include "im_xch.h"
#include "im_jpeg.h"
#include "im_me.h"
#include "palladiumtestinterrupta.h"

/**
 * K_DEFINE_*语句
 */
K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestInterruptA, palladium_test_interrupt_a);
/*******
 * 以下开始宏声明
 */
#define PALLADIUM_TEST_INTERRUPT_A_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestInterruptAPrivate,PALLADIUM_TYPE_TEST_INTERRUPT_A))

struct _PalladiumTestInterruptAPrivate
{
	int a;
};

/***********
 * IMPL
 */
static void palladium_test_interrupt_a_constructor(PalladiumTestInterruptA *self)
{
	PalladiumTestInterruptAPrivate *priv = PALLADIUM_TEST_INTERRUPT_A_GET_PRIVATE(self);
}

static void palladium_test_interrupt_a_destructor(PalladiumTestInterruptA *self)
{
	PalladiumTestInterruptAPrivate *priv = PALLADIUM_TEST_INTERRUPT_A_GET_PRIVATE(self);
}

/*********
 * PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
// SGI Interrupt0
VOID palladium_test_interrupt_a_pt_sgi_interrupt0(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt0\n"));
}

// SGI Interrupt1
VOID palladium_test_interrupt_a_pt_sgi_interrupt1(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt1\n"));
}

// SGI Interrupt2
VOID palladium_test_interrupt_a_pt_sgi_interrupt2(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt2\n"));
}

// SGI Interrupt3
VOID palladium_test_interrupt_a_pt_sgi_interrupt3(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt3\n"));
}

// SGI Interrupt4
VOID palladium_test_interrupt_a_pt_sgi_interrupt4(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt4\n"));
}

// SGI Interrupt5
VOID palladium_test_interrupt_a_pt_sgi_interrupt5(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt5\n"));
}

// SGI Interrupt6
VOID palladium_test_interrupt_a_pt_sgi_interrupt6(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt6\n"));
}

// SGI Interrupt7
VOID palladium_test_interrupt_a_pt_sgi_interrupt7(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt7\n"));
}

// SGI Interrupt8
VOID palladium_test_interrupt_a_pt_sgi_interrupt8(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt8\n"));
}

// SGI Interrupt9
VOID palladium_test_interrupt_a_pt_sgi_interrupt9(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt9\n"));
}

// SGI Interrupt10
VOID palladium_test_interrupt_a_pt_sgi_interrupt10(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt10\n"));
}

// SGI Interrupt11
VOID palladium_test_interrupt_a_pt_sgi_interrupt11(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt11\n"));
}

// SGI Interrupt12
VOID palladium_test_interrupt_a_pt_sgi_interrupt12(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt12\n"));
}

// SGI Interrupt13
VOID palladium_test_interrupt_a_pt_sgi_interrupt13(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt13\n"));
}

// SGI Interrupt14
VOID palladium_test_interrupt_a_pt_sgi_interrupt14(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt14\n"));
}

// SGI Interrupt15
VOID palladium_test_interrupt_a_pt_sgi_interrupt15(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SGI_Interrupt15\n"));
}

// PPI Interrupt0
VOID palladium_test_interrupt_a_pt_ppi_interrupt0(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt0\n"));
}

// PPI Interrupt1
VOID palladium_test_interrupt_a_pt_ppi_interrupt1(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt1\n"));
}

// PPI Interrupt2
VOID palladium_test_interrupt_a_pt_ppi_interrupt2(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt2\n"));
}

// PPI Interrupt3
VOID palladium_test_interrupt_a_pt_ppi_interrupt3(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt3\n"));
}

// PPI Interrupt4
VOID palladium_test_interrupt_a_pt_ppi_interrupt4(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt4\n"));
}

// PPI Interrupt5
VOID palladium_test_interrupt_a_pt_ppi_interrupt5(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt5\n"));
}

// PPI Interrupt6
VOID palladium_test_interrupt_a_pt_ppi_interrupt6(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt6\n"));
}

// PPI Interrupt7
VOID palladium_test_interrupt_a_pt_ppi_interrupt7(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt7\n"));
}

// PPI Interrupt8
VOID palladium_test_interrupt_a_pt_ppi_interrupt8(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt8\n"));
}

// PPI Interrupt9
VOID palladium_test_interrupt_a_pt_ppi_interrupt9(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt9\n"));
}

// PPI Interrupt10
VOID palladium_test_interrupt_a_pt_ppi_interrupt10(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt10\n"));
}

// PPI Interrupt11
VOID palladium_test_interrupt_a_pt_ppi_interrupt11(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt11\n"));
}

// PPI Interrupt12
VOID palladium_test_interrupt_a_pt_ppi_interrupt12(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt12\n"));
}

// PPI Interrupt13
VOID palladium_test_interrupt_a_pt_ppi_interrupt13(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt13\n"));
}

// PPI Interrupt14
VOID palladium_test_interrupt_a_pt_ppi_interrupt14(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt14\n"));
}

// PPI Interrupt15
VOID palladium_test_interrupt_a_pt_ppi_interrupt15(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PPI_Interrupt15\n"));
}

// Cortex-A7 CPU0 Communication Receive
VOID palladium_test_interrupt_a_pt_cortexa7_cpu0_communication_ch_receive_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu0_Communication_Ch_Receive_Int\n"));
}

// Cortex-A7 CPU0 Communication Trnsmit
VOID palladium_test_interrupt_a_pt_cortexa7_cpu0_communication_ch_trnsmit_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu0_Communication_Ch_Trnsmit_Int\n"));
}

// Cortex-A7 CPU1 Communication Receive
VOID palladium_test_interrupt_a_pt_cortexa7_cpu1_communication_ch_receive_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu1_Communication_Ch_Receive_Int\n"));
}

// Cortex-A7 CPU1 Communication Trnsmit
VOID palladium_test_interrupt_a_pt_cortexa7_cpu1_communication_ch_trnsmit_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu1_Communication_Ch_Trnsmit_Int\n"));
}

// Cortex-A7 CPU2 Communication Receive
VOID palladium_test_interrupt_a_pt_cortexa7_cpu2_communication_ch_receive_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu2_Communication_Ch_Receive_Int\n"));
}

// Cortex-A7 CPU2 Communication Trnsmit
VOID palladium_test_interrupt_a_pt_cortexa7_cpu2_communication_ch_trnsmit_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu2_Communication_Ch_Trnsmit_Int\n"));
}

// Cortex-A7 CPU3 Communication Receive
VOID palladium_test_interrupt_a_pt_cortexa7_cpu3_communication_ch_receive_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu3_Communication_Ch_Receive_Int\n"));
}

// Cortex-A7 CPU3 Communication Trnsmit
VOID palladium_test_interrupt_a_Pt_cortexa7_cpu3_communication_ch_trnsmit_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu3_Communication_Ch_Trnsmit_Int\n"));
}

// Cortex-A7 CPU0 Crosstrigger
VOID palladium_test_interrupt_a_pt_cortexa7_cpu0_crosstrigger_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu0_Crosstrigger_Int\n"));
}

// Cortex-A7 CPU1 Crosstrigger
VOID palladium_test_interrupt_a_pt_cortexa7_cpu1_crosstrigger_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu1_Crosstrigger_Int\n"));
}

// Cortex-A7 CPU2 Crosstrigger
VOID palladium_test_interrupt_a_pt_cortexa7_cpu2_crosstrigger_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu2_Crosstrigger_Int\n"));
}

// Cortex-A7 CPU3 Crosstrigger
VOID palladium_test_interrupt_a_pt_cortexa7_cpu3_crosstrigger_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu3_Crosstrigger_Int\n"));
}

// Cortex-A7 CPU0 System Metrics
VOID palladium_test_interrupt_a_pt_cortexa7_cpu0_system_metrics_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu0_System_Metrics_Int\n"));
}

// Cortex-A7 CPU1 System Metrics
VOID palladium_test_interrupt_a_pt_cortexa7_cpu1_system_metrics_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu1_System_Metrics_Int\n"));
}

// Cortex-A7 CPU2 System Metrics
VOID palladium_test_interrupt_a_pt_cortexa7_cpu2_system_metrics_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu2_System_Metrics_Int\n"));
}

// Cortex-A7 CPU3 System Metrics
VOID palladium_test_interrupt_a_pt_cortexa7_cpu3_system_metrics_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("CortexA7_Cpu3_System_Metrics_Int\n"));
}

// AXI Transaction Error
VOID palladium_test_interrupt_a_pt_axi_transaction_error_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("AXI_Transaction_Error_Int\n"));
}

// SNAP Peri XDMAC ch0
VOID palladium_test_interrupt_a_pt_snap_peri_xdmac_ch0_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SNAP_Peri_Xdmac_Ch0_Int\n"));
}

// SNAP Peri XDMAC ch1
VOID palladium_test_interrupt_a_pt_snap_peri_xdmac_ch1_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SNAP_Peri_Xdmac_Ch1_Int\n"));
}

// SNAP Peri XDMAC ch2
VOID palladium_test_interrupt_a_pt_snap_peri_xdmac_ch2_Int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SNAP_Peri_Xdmac_Ch2_Int\n"));
}

// SNAP Peri XDMAC ch3
VOID palladium_test_interrupt_a_pt_snap_peri_xdmac_ch3_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("SNAP_Peri_Xdmac_Ch3_Int\n"));
}

// Watchdog Timer
VOID palladium_test_interrupt_a_pt_watchdog_timer_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Watchdog_Timer_Int\n"));
}

// IPCU0 interrupt ch0
VOID palladium_test_interrupt_a_pt_ipcu0_ch0_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch0_Int\n"));
}

// IPCU0 interrupt ch1
VOID palladium_test_interrupt_a_pt_ipcu0_ch1_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch1_Int\n"));
}

// IPCU0 interrupt ch2
VOID palladium_test_interrupt_a_pt_ipcu0_ch2_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch2_Int\n"));
}

// IPCU0 interrupt ch3
VOID palladium_test_interrupt_a_pt_ipcu0_ch3_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch3_Int\n"));
}

// IPCU0 interrupt ch4
VOID palladium_test_interrupt_a_pt_ipcu0_ch4_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch4_Int\n"));
}

// IPCU0 interrupt ch5
VOID palladium_test_interrupt_a_pt_ipcu0_ch5_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch5_Int\n"));
}

// IPCU0 interrupt ch6
VOID palladium_test_interrupt_a_pt_ipcu0_ch6_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch6_Int\n"));
}

// IPCU0 interrupt ch7
VOID palladium_test_interrupt_a_pt_ipcu0_ch7_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch7_Int\n"));
}

// IPCU0 interrupt ch8
VOID palladium_test_interrupt_a_pt_ipcu0_ch8_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch8_Int\n"));
}

// IPCU0 interrupt ch9
VOID palladium_test_interrupt_a_pt_ipcu0_ch9_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch9_Int\n"));
}

// IPCU0 interrupt ch10
VOID palladium_test_interrupt_a_pt_ipcu0_ch10_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch10_Int\n"));
}

// IPCU0 interrupt ch11
VOID palladium_test_interrupt_a_pt_ipcu0_ch11_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch11_Int\n"));
}

// IPCU0 interrupt ch12
VOID palladium_test_interrupt_a_pt_ipcu0_ch12_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch12_Int\n"));
}

// IPCU0 interrupt ch13
VOID palladium_test_interrupt_a_pt_ipcu0_ch13_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch13_Int\n"));
}

// IPCU0 interrupt ch14
VOID palladium_test_interrupt_a_pt_ipcu0_ch14_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch14_Int\n"));
}

// IPCU0 interrupt ch15
VOID palladium_test_interrupt_a_pt_ipcu0_ch15_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu0_Ch15_Int\n"));
}

// IPCU1 interrupt ch0
VOID palladium_test_interrupt_a_pt_ipcu1_ch0_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch0_Int\n"));
}

// IPCU1 interrupt ch1
VOID palladium_test_interrupt_a_pt_ipcu1_ch1_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch1_Int\n"));
}

// IPCU1 interrupt ch2
VOID palladium_test_interrupt_a_pt_ipcu1_ch2_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch2_Int\n"));
}

// IPCU1 interrupt ch3
VOID palladium_test_interrupt_a_pt_ipcu1_ch3_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch3_Int\n"));
}

// IPCU1 interrupt ch4
VOID palladium_test_interrupt_a_pt_ipcu1_ch4_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch4_Int\n"));
}

// IPCU1 interrupt ch5
VOID palladium_test_interrupt_a_pt_ipcu1_ch5_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch5_Int\n"));
}

// IPCU1 interrupt ch6
VOID palladium_test_interrupt_a_pt_ipcu1_ch6_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch6_Int\n"));
}

// IPCU1 interrupt ch7
VOID palladium_test_interrupt_a_pt_ipcu1_ch7_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch7_Int\n"));
}

// IPCU1 interrupt ch8
VOID palladium_test_interrupt_a_pt_ipcu1_ch8_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch8_Int\n"));
}

// IPCU1 interrupt ch9
VOID palladium_test_interrupt_a_pt_ipcu1_ch9_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch9_Int\n"));
}

// IPCU1 interrupt ch10
VOID palladium_test_interrupt_a_pt_ipcu1_ch10_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch10_Int\n"));
}

// IPCU1 interrupt ch11
VOID palladium_test_interrupt_a_pt_ipcu1_ch11_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch11_Int\n"));
}

// IPCU1 interrupt ch12
VOID palladium_test_interrupt_a_pt_ipcu1_ch12_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch12_Int\n"));
}

// IPCU1 interrupt ch13
VOID palladium_test_interrupt_a_pt_ipcu1_ch13_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch13_Int\n"));
}

// IPCU1 interrupt ch14
VOID palladium_test_interrupt_a_pt_ipcu1_ch14_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch14_Int\n"));
}

// IPCU1 interrupt ch15
VOID palladium_test_interrupt_a_pt_ipcu1_ch15_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Ipcu1_Ch15_Int\n"));
}

// External Interrupt ch16
VOID palladium_test_interrupt_a_pt_external_ch16_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch16_Int\n"));
}

// External Interrupt ch17
VOID palladium_test_interrupt_a_pt_external_ch17_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch17_Int\n"));
}

// External Interrupt ch18
VOID palladium_test_interrupt_a_pt_external_ch18_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch18_Int\n"));
}

// External Interrupt ch19
VOID palladium_test_interrupt_a_pt_external_ch19_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch19_Int\n"));
}

// External Interrupt ch20
VOID palladium_test_interrupt_a_pt_external_ch20_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch20_Int\n"));
}

// External Interrupt ch21
VOID palladium_test_interrupt_a_pt_external_ch21_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch21_Int\n"));
}

// External Interrupt ch22
VOID palladium_test_interrupt_a_pt_external_ch22_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch22_Int\n"));
}

// External Interrupt ch23
VOID palladium_test_interrupt_a_pt_external_ch23_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch23_Int\n"));
}

// External Interrupt ch24
VOID palladium_test_interrupt_a_pt_external_ch24_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch24_Int\n"));
}

// External Interrupt ch25
VOID palladium_test_interrupt_a_pt_external_ch25_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch25_Int\n"));
}

// External Interrupt ch26
VOID palladium_test_interrupt_a_pt_external_ch26_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch26_Int\n"));
}

// External Interrupt ch27
VOID palladium_test_interrupt_a_pt_external_ch27_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch27_Int\n"));
}

// External Interrupt ch28
VOID palladium_test_interrupt_a_pt_external_ch28_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch28_Int\n"));
}

// External Interrupt ch29
VOID palladium_test_interrupt_a_pt_external_ch29_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch29_Int\n"));
}

// External Interrupt ch30
VOID palladium_test_interrupt_a_pt_external_ch30_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch30_Int\n"));
}

// External Interrupt ch31
VOID palladium_test_interrupt_a_pt_external_ch31_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("External_Ch31_Int\n"));
}

// PMC DMAC ADC.
VOID palladium_test_interrupt_a_pt_pmc_dmac_adc_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PMC_DMAC_ADC_Int\n"));
}

// PMC DMAC Receive.
VOID palladium_test_interrupt_a_pt_pmc_dmac_receive_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PMC_DMAC_Receive_Int\n"));
}

// PMC UART Transmission Data.
VOID palladium_test_interrupt_a_pt_pmc_uart_transmission_data_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PMC_UART_Transmission_Data_Int\n"));
}

// PMC DMAC QSPI Transmission.
VOID palladium_test_interrupt_a_pt_pmc_dmac_qspi_transmission_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PMC_DMAC_QSPI_Transmission_Int\n"));
}

// PMC DMAC QSPI Receive.
VOID palladium_test_interrupt_a_pt_pmc_dmac_qspi_receive_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PMC_DMAC_QSPI_Receive_Int\n"));
}

// PMC UART Receive Relation.
VOID palladium_test_interrupt_a_pt_pmc_uart_receive_relation_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PMC_UART_Receive_Relation_Int\n"));
}

// PMC UART Transmission Relation.
VOID palladium_test_interrupt_a_pt_pmc_uart_transmission_relation_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Pmc_Uart_Transmission_Relation_Int\n"));
}

// PMC QSPI.
VOID palladium_test_interrupt_a_pt_pmc_qspi_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PMC_Qspi_Int\n"));
}

// CALENDAR Alarm.
VOID palladium_test_interrupt_a_pt_calendar_alarm_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Calendar_Alarm_Int\n"));
}

// PMC 32bit Timer Under Flow.
VOID palladium_test_interrupt_a_pt_pmc_32bit_timer_under_flow_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PMC_32bit_Timer_Under_Floe_Int\n"));
}

// ADC.
VOID palladium_test_interrupt_a_pt_adc_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("ADC_Int\n"));
}

// PMC I2C.
VOID palladium_test_interrupt_a_pt_pmc_i2c_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PMC_I2c_Int\n"));
}

// PMC Watchdog.
VOID palladium_test_interrupt_a_pt_pmc_watchdog_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PMC_Watchdog_Int\n"));
}

// Temperature.
VOID palladium_test_interrupt_a_pt_temperature_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Temperature_Int\n"));
}

// PMU.
VOID palladium_test_interrupt_a_pt_pmu_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PMU_Int\n"));
}

// PMC Gpio.
VOID palladium_test_interrupt_a_pt_pmc_gpio_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("PMC_Gpio_Int\n"));
}

// Timer ch0
VOID palladium_test_interrupt_a_pt_timer_ch0_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch0_Int\n"));
	Dd_TMR32_Int_Handler(0);
}

// Timer ch1
VOID palladium_test_interrupt_a_pt_timer_ch1_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch1_Int\n"));
	Dd_TMR32_Int_Handler(1);
}

// Timer ch2
VOID palladium_test_interrupt_a_pt_timer_ch2_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch2_Int\n"));
	Dd_TMR32_Int_Handler(2);
}

// Timer ch3
VOID palladium_test_interrupt_a_pt_timer_ch3_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch3_Int\n"));
	Dd_TMR32_Int_Handler(3);
}

// Timer ch4
VOID palladium_test_interrupt_a_pt_timer_ch4_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch4_Int\n"));
	Dd_TMR32_Int_Handler(4);
}

// Timer ch5
VOID palladium_test_interrupt_a_pt_timer_ch5_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch5_Int\n"));
	Dd_TMR32_Int_Handler(5);
}

// Timer ch6
VOID palladium_test_interrupt_a_pt_timer_ch6_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch6_Int\n"));
	Dd_TMR32_Int_Handler(6);
}

// Timer ch7
VOID palladium_test_interrupt_a_pt_timer_ch7_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch7_Int\n"));
	Dd_TMR32_Int_Handler(7);
}

// Timer ch8
VOID palladium_test_interrupt_a_pt_timer_ch8_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch8_Int\n"));
	Dd_TMR32_Int_Handler(8);
}

// Timer ch9
VOID palladium_test_interrupt_a_pt_timer_ch9_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch9_Int\n"));
	Dd_TMR32_Int_Handler(9);
}

// Timer ch10
VOID palladium_test_interrupt_a_pt_timer_ch10_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch10_Int\n"));
	Dd_TMR32_Int_Handler(10);
}

// Timer ch11
VOID palladium_test_interrupt_a_pt_timer_ch11_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch11_Int\n"));
	Dd_TMR32_Int_Handler(11);
}

// Timer ch12
VOID palladium_test_interrupt_a_pt_timer_ch12_Int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch12_Int\n"));
	Dd_TMR32_Int_Handler(12);
}

// Timer ch13
VOID palladium_test_interrupt_a_pt_timer_ch13_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Timer_Ch13_Int\n"));
	Dd_TMR32_Int_Handler(13);
}

// I2C ch0
VOID palladium_test_interrupt_a_pt_i2c_ch0_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("I2c_Ch0_Int\n"));
}

// I2C ch1
VOID palladium_test_interrupt_a_pt_i2c_ch1_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("I2c_Ch1_Int\n"));
}

// I2C ch2
VOID palladium_test_interrupt_a_pt_i2c_ch2_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("I2c_Ch2_Int\n"));
}

// Up/Down Counter ch0
VOID palladium_test_interrupt_a_pt_updown_counter_ch0_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Updown_Counter_Ch0_Int\n"));
}

// Up/Down Counter ch1
VOID palladium_test_interrupt_a_pt_updown_counter_ch1_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Updown_Counter_Ch1_Int\n"));
}

// Up/Down Counter ch2
VOID palladium_test_interrupt_a_pt_updown_counter_ch2_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Updown_Counter_Ch2_Int\n"));
}

// Up/Down Counter ch3
VOID palladium_test_interrupt_a_pt_updown_counter_ch3_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Updown_Counter_Ch3_Int\n"));
}

// Up/Down Counter ch4
VOID palladium_test_interrupt_a_pt_updown_counter_ch4_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Updown_Counter_Ch4_Int\n"));
}

// Up/Down Counter ch5
VOID palladium_test_interrupt_a_pt_updown_counter_ch5_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Updown_Counter_Ch5_Int\n"));
}

// PWM ch0-3
VOID palladium_test_interrupt_a_pt_pwm_ch0_ch3_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Pwm_Ch0_Ch3_Int\n"));
}

// PWM ch4-7
VOID palladium_test_interrupt_a_pt_pwm_ch4_ch7_int(PalladiumTestInterruptA* self)
{
	Ddim_Print(("Pwm_Ch4_Ch7_Int\n"));
}

PalladiumTestInterruptA* palladium_test_interrupt_a_new(void)
{
	PalladiumTestInterruptA *self = k_object_new(PALLADIUM_TYPE_TEST_INTERRUPT_A);
	return self;
}
