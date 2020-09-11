/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-09-5
*@author              :hubing
*@brief               :snsos
*@rely                :klib
*@function
*采用ETK-C语言抄写代码
*设计的主要功能:
*@version
*1.0.0 2020年06月开始开发
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
#include "palladiumtestinterruptb.h"
#include "example.h"
/**
 * K_DEFINE_*语句
 */
K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestInterruptB, palladium_test_interrupt_b);
/**
 * 以下开始宏定义
 */
#define PALLADIUM_TEST_INTERRUPT_B_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestInterruptBPrivate,PALLADIUM_TYPE_TEST_INTERRUPT_B))
/**
 * 内部结构体或类型定义
 */
struct _PalladiumTestInterruptBPrivate
{
	int a;
};
/***********
 * IMPL
 */
static void palladium_test_interrupt_b_constructor(PalladiumTestInterruptB *self)
{
	PalladiumTestInterruptBPrivate *priv = PALLADIUM_TEST_INTERRUPT_B_GET_PRIVATE(self);
}

static void palladium_test_interrupt_b_destructor(PalladiumTestInterruptB *self)
{
	PalladiumTestInterruptBPrivate *priv = PALLADIUM_TEST_INTERRUPT_B_GET_PRIVATE(self);
}

/*********
 * PUBLIC
 */
// PWM ch8-11
VOID palladium_test_interrupt_b_pt_pwm_ch8_ch11_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Pwm_Ch8_Ch11_Int\n"));
}

// PWM ch12-15
VOID palladium_test_interrupt_b_pt_pwm_ch12_ch15_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Pwm_Ch12_Ch15_Int\n"));
}

// PWM ch0-3 STP
VOID palladium_test_interrupt_b_pt_pwm_ch0_ch3_stp_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Pwm_Ch0_Ch3_Stp_Int\n"));
}

// PWM ch4-7 STP
VOID palladium_test_interrupt_b_pt_pwm_ch4_ch7_stp_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Pwm_Ch4_Ch7_Stp_Int\n"));
}

// PWM ch8-11 STP
VOID palladium_test_interrupt_b_pt_pwm_ch8_ch11_stp_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Pwm_Ch8_Ch11_Stp_Int\n"));
}

// PWM ch12-15 STP
VOID palladium_test_interrupt_b_pt_Pwm_ch12_ch15_stp_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Pwm_Ch12_Ch15_Stp_Int\n"));
}

// Audio I/F ch0
VOID palladium_test_interrupt_b_pt_audio_if_ch0_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Audio_If_Ch0_Int\n"));
}

// Audio I/F ch1
VOID palladium_test_interrupt_b_pt_audio_if_ch1_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Audio_If_Ch1_Int\n"));
}

// Audio I/F ch2
VOID palladium_test_interrupt_b_pt_audio_if_ch2_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Audio_If_Ch2_Int\n"));
}

// Audio I/F ch3
VOID palladium_test_interrupt_b_pt_audio_if_ch3_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Audio_If_Ch3_Int\n"));
}

// Audio I/F ch4
VOID palladium_test_interrupt_b_pt_audio_if_ch4_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Audio_If_Ch4_Int\n"));
}

// Audio I/F ch5
VOID palladium_test_interrupt_b_pt_audio_if_ch5_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Audio_If_Ch5_Int\n"));
}

// Peripheral HDMAC0 ch0
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch0_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac0_Ch0_Int\n"));
}

// Peripheral HDMAC0 ch1
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch1_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac0_Ch1_Int\n"));
}

// Peripheral HDMAC0 ch2
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch2_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac0_Ch2_Int\n"));
}

// Peripheral HDMAC0 ch3
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch3_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac0_Ch3_Int\n"));
}

// Peripheral HDMAC0 ch4
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch4_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac0_Ch4_Int\n"));
}

// Peripheral HDMAC0 ch5
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch5_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac0_Ch5_Int\n"));
}

// Peripheral HDMAC0 ch6
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch6_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac0_Ch6_Int\n"));
}

// Peripheral HDMAC0 ch7
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch7_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac0_Ch7_Int\n"));
}

// Peripheral HDMAC1 ch0
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch0_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac1_Ch0_Int\n"));
}

// Peripheral HDMAC1 ch1
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch1_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac1_Ch1_Int\n"));
}

// Peripheral HDMAC1 ch2
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch2_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac1_Ch2_Int\n"));
}

// Peripheral HDMAC1 ch3
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch3_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac1_Ch3_Int\n"));
}

// Peripheral HDMAC1 ch4
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch4_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac1_Ch4_Int\n"));
}

// Peripheral HDMAC1 ch5
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch5_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac1_Ch5_Int\n"));
}

// Peripheral HDMAC1 ch6
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch6_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac1_Ch6_Int\n"));
}

// Peripheral HDMAC1 ch7
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch7_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Peri_Hdmac1_Ch7_Int\n"));
}

// UART ch0 Reception
VOID palladium_test_interrupt_b_pt_uart_ch0_reception_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch0_Reception_Int\n"));
}

// UART ch1 Reception
VOID palladium_test_interrupt_b_pt_uart_ch1_reception_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch1_Reception_Int\n"));
}


// UART ch2 Reception
VOID palladium_test_interrupt_b_pt_uart_ch2_reception_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch2_Reception_Int\n"));
}

// UART ch3 Reception
VOID palladium_test_interrupt_b_pt_uart_ch3_reception_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch3_Reception_Int\n"));
}

// UART ch4 Reception
VOID palladium_test_interrupt_b_pt_uart_ch4_reception_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch4_Reception_Int\n"));
}

// UART ch5 Reception
VOID palladium_test_interrupt_b_pt_uart_ch5_reception_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch5_Reception_Int\n"));
}

// UART ch6 Reception
VOID palladium_test_interrupt_b_pt_uart_ch6_reception_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch6_Reception_Int\n"));
}

// UART ch7 Reception
VOID palladium_test_interrupt_b_pt_uart_ch7_reception_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch7_Reception_Int\n"));
}

// UART ch0 Transmission
VOID palladium_test_interrupt_b_pt_uart_ch0_transmission_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch0_Transmission_Int\n"));
}

// UART ch1 Transmission
VOID palladium_test_interrupt_b_pt_uart_ch1_transmission_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch1_Transmission_Int\n"));
}

// UART ch2 Transmission
VOID palladium_test_interrupt_b_pt_uart_ch2_transmission_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch2_Transmission_Int\n"));
}

// UART ch3 Transmission
VOID palladium_test_interrupt_b_pt_uart_ch3_transmission_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch3_Transmission_Int\n"));
}

// UART ch4 Transmission
VOID palladium_test_interrupt_b_pt_uart_ch4_transmission_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch4_Transmission_Int\n"));
}

// UART ch5 Transmission
VOID palladium_test_interrupt_b_pt_uart_ch5_transmission_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch5_Transmission_Int\n"));
}

// UART ch6 Transmission
VOID palladium_test_interrupt_b_pt_uart_ch6_transmission_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch6_Transmission_Int\n"));
}

// UART ch7 Transmission
VOID palladium_test_interrupt_b_pt_uart_ch7_transmission_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Uart_Ch7_Transmission_Int\n"));
}

// SPI ch0
VOID palladium_test_interrupt_b_pt_spi_ch0_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SPI_Ch0_Int\n"));
}

// SPI ch1
VOID palladium_test_interrupt_b_pt_spi_ch1_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SPI_Ch1_Int\n"));
}

// SPI ch2
VOID palladium_test_interrupt_b_pt_spi_ch2_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SPI_Ch2_Int\n"));
}

// PDM ch0 DMA0
VOID palladium_test_interrupt_b_pt_pdm_ch0_dma0_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("PDM_Ch0_DMA0_Int\n"));
}

// PDM ch0 DMA1
VOID palladium_test_interrupt_b_pt_pdm_ch0_dma1_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("PDM_Ch0_DMA1_Int\n"));
}

// PDM ch0 Fifo Overflow
VOID palladium_test_interrupt_b_pt_pdm_ch0_fifo_overflow_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("PDM_Ch0_Fifo_Overflow_Int\n"));
}

// PDM ch1 DMA0
VOID palladium_test_interrupt_b_pt_pdm_ch1_dma0_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("PDM_Ch1_DMA0_Int\n"));
}

// PDM ch1 DMA1
VOID palladium_test_interrupt_b_pt_pdm_ch1_dma1_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("PDM_Ch1_DMA1_Int\n"));
}

// PDM ch1 Fifo Overflow
VOID palladium_test_interrupt_b_pt_pdm_ch1_fifo_overflow_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("PDM_Ch1_Fifo_Overflow_Int\n"));
}

// SLIMBUS ch0
VOID palladium_test_interrupt_b_pt_slimbus_ch0_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SLIMBUS_Ch0_Int\n"));
}

// SLIMBUS ch1
VOID palladium_test_interrupt_b_pt_slimbus_ch1_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SLIMBUS_Ch1_Int\n"));
}

// SLIMBUS ch2
VOID palladium_test_interrupt_b_pt_slimbus_ch2_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SLIMBUS_Ch2_Int\n"));
}

// SLIMBUS ch3
VOID palladium_test_interrupt_b_pt_slimbus_ch3_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SLIMBUS_Ch3_Int\n"));
}

// Image SDRAMC0
VOID palladium_test_interrupt_b_pt_sdramc_ch0_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Sdramc_Ch0_Int\n"));
	Im_SDRAMC_Int_Handler( E_IM_SDRAMC_CH_0 );
}

// Image SDRAMC1
VOID palladium_test_interrupt_b_pt_sdramc_ch1_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Sdramc_Ch1_Int\n"));
	Im_SDRAMC_Int_Handler( E_IM_SDRAMC_CH_1 );
}

// Image MXIC Unit0
VOID palladium_test_interrupt_b_pt_mxic_unit0_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Mxic_Unit0_Int\n"));
	Im_MXIC_Int_Handler( E_IM_MXIC_UNIT_0 );
}

// Image MXIC Unit1
VOID palladium_test_interrupt_b_pt_mxic_unit1_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Mxic_Unit1_Int\n"));
	Im_MXIC_Int_Handler( E_IM_MXIC_UNIT_1 );
}

// Image MXIC Unit2
VOID palladium_test_interrupt_b_pt_mxic_unit2_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Mxic_Unit2_Int\n"));
	Im_MXIC_Int_Handler( E_IM_MXIC_UNIT_2 );
}

// Image MXIC Unit3
VOID palladium_test_interrupt_b_pt_mxic_unit3_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Mxic_Unit3_Int\n"));
	Im_MXIC_Int_Handler( E_IM_MXIC_UNIT_3 );
}

// Image MXIC Unit4
VOID palladium_test_interrupt_b_pt_mxic_unit4_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Mxic_Unit4_Int\n"));
	Im_MXIC_Int_Handler( E_IM_MXIC_UNIT_4 );
}

// Image MXIC Unit5
VOID palladium_test_interrupt_b_pt_mxic_unit5_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Mxic_Unit5_Int\n"));
	Im_MXIC_Int_Handler( E_IM_MXIC_UNIT_5 );
}

// Image MXIC Unit6
VOID palladium_test_interrupt_b_pt_mxic_unit6_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Mxic_Unit6_Int\n"));
	Im_MXIC_Int_Handler( E_IM_MXIC_UNIT_6 );
}

// Image SEN
VOID palladium_test_interrupt_b_pt_sen_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SEN_Int\n"));
}

// Image SEN VD
VOID palladium_test_interrupt_b_pt_sen_vd_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SEN_VD_Int\n"));
}

// Image SEN HD
VOID palladium_test_interrupt_b_pt_sen_hd_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SEN_HD_Int\n"));
}

// Image SENSOR IF Macro0
VOID palladium_test_interrupt_b_pt_sensor_if_macro0_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SENSOR_IF_Macro0_Int\n"));
}

// Image SENSOR IF Macro1
VOID palladium_test_interrupt_b_pt_sensor_if_macro1_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SENSOR_IF_Macro1_Int\n"));
}

// Image SENSOR IF Macro2
VOID palladium_test_interrupt_b_pt_sensor_if_macro2_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SENSOR_IF_Macro2_Int\n"));
}

// Image SENSOR IF Macro3
VOID palladium_test_interrupt_b_pt_sensor_if_macro3_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SENSOR_IF_Macro3_Int\n"));
}

// Image SRO Unit1
VOID palladium_test_interrupt_b_pt_sro_unit1_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SRO_Unit1_Int\n"));
}

// Image SRO Unit1 VD
VOID palladium_test_interrupt_b_pt_sro_unit1_vd_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SRO_Unit1_VD_Int\n"));
}

// Image SRO Unit1 HD
VOID palladium_test_interrupt_b_pt_sro_unit1_hd_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SRO_Unit1_HD_Int\n"));
}

// Image SRO Unit2
VOID palladium_test_interrupt_b_pt_sro_unit2_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SRO_Unit2_Int\n"));
}

// Image SRO Unit2 VD
VOID palladium_test_interrupt_b_pt_sro_unit2_vd_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SRO_Unit2_VD_Int\n"));
}

// Image SRO Unit2 HD
VOID palladium_test_interrupt_b_pt_sro_unit2_hd_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("SRO_Unit2_HD_Int\n"));
}

// Image B2B Unit1
VOID palladium_test_interrupt_b_pt_b2b_unit1_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("B2B_Unit1_Int\n"));
}

// Image B2B Unit1 VD
VOID palladium_test_interrupt_b_pt_b2b_unit1_vd_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("B2B_Unit1_VD_Int\n"));
}

// Image B2B Unit1 HD
VOID palladium_test_interrupt_b_pt_b2b_unit1_hd_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("B2B_Unit1_HD_Int\n"));
}

// Image B2B Unit2
VOID palladium_test_interrupt_b_pt_b2b_unit2_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("B2B_Unit2_Int\n"));
}

// Image B2B Unit2 VD
VOID palladium_test_interrupt_b_pt_b2b_unit2_vd_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("B2B_Unit2_VD_Int\n"));
}

// Image B2B Unit2 HD
VOID palladium_test_interrupt_b_pt_b2b_unit2_hd_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("B2B_Unit2_HD_Int\n"));
}

// Image Start
VOID palladium_test_interrupt_b_pt_start_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("Start_Int\n"));
}

// Image PAS Unit2
VOID palladium_test_interrupt_b_pt_pas_unit2_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("PAS_Unit2_Int\n"));
}

// Image PAS Unit2 VD
VOID palladium_test_interrupt_b_pt_pas_unit2_vd_int(PalladiumTestInterruptB* self)
{
	Ddim_Print(("PAS_Unit2_VD_Int\n"));
}

PalladiumTestInterruptB* palladium_test_interrupt_b_new(void)
{
	PalladiumTestInterruptB *self = k_object_new(PALLADIUM_TYPE_TEST_INTERRUPT_B);
	return self;
}
