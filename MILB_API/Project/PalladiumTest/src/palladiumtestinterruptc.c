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
#include "palladiumtestinterruptc.h"
/**
 * K_DEFINE_*语句
 */
K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestInterruptC, palladium_test_interrupt_c);
/**
 * 以下开始宏定义
 */
#define PALLADIUM_TEST_INTERRUPT_C_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestInterruptCPrivate,PALLADIUM_TYPE_TEST_INTERRUPT_C))
/**
 * 内部结构体或类型定义
 */
struct _PalladiumTestInterruptCPrivate
{
	int a;
};

/***********
 * IMPL
 */
static void palladium_test_interrupt_c_constructor(PalladiumTestInterruptC *self)
{
	PalladiumTestInterruptCPrivate *priv = PALLADIUM_TEST_INTERRUPT_C_GET_PRIVATE(self);
}

static void palladium_test_interrupt_c_destructor(PalladiumTestInterruptC *self)
{
	PalladiumTestInterruptCPrivate *priv = PALLADIUM_TEST_INTERRUPT_C_GET_PRIVATE(self);
}

/*********
 * PUBLIC
 */
// Image PAS Unit2 HD
VOID palladium_test_interrupt_c_pt_pas_unit2_hd_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("PAS_Unit2_HD_Int\n"));
}

// Image B2R Unit1
VOID palladium_test_interrupt_c_pt_b2r_unit1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("B2R_Unit1_Int\n"));
	Im_B2R_Int_Handler( D_IM_B2R_PIPE1 );
}

// Image B2R Unit2
VOID palladium_test_interrupt_c_pt_b2r_unit2_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("B2R_Unit2_Int\n"));
	Im_B2R_Int_Handler( D_IM_B2R_PIPE2 );
}

// Image LTM Unit1
VOID palladium_test_interrupt_c_pt_ltm_unit1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("LTM_Unit1_Int\n"));
	Im_LTM_Int_Handler( D_IM_LTM_PIPE1 );
}

// Image LTM Unit2
VOID palladium_test_interrupt_c_pt_ltm_unit2_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("LTM_Unit2_Int\n"));
	Im_LTM_Int_Handler( D_IM_LTM_PIPE2 );
}

// Image R2Y Unit1
VOID palladium_test_interrupt_c_pt_r2y_unit1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("R2Y_Unit1_Int\n"));
	Im_R2Y_Int_Handler( D_IM_R2Y_PIPE1 );
}

// Image R2Y Unit2
VOID palladium_test_interrupt_c_pt_r2y_unit2_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("R2Y_Unit2_Int\n"));
	Im_R2Y_Int_Handler( D_IM_R2Y_PIPE2 );
}

// Image CNR Unit1
VOID palladium_test_interrupt_c_pt_cnr_unit1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("CNR_Unit1_Int\n"));
	Im_CNR0_Int_Handler();
}

// Image CNR Unit2
VOID palladium_test_interrupt_c_pt_cnr_unit2_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("CNR_Unit2_Int\n"));
	Im_CNR1_Int_Handler();
}

// Image IIP
VOID palladium_test_interrupt_c_pt_iip_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("IIP_Int\n"));
	Im_IIP_Int_Handler();
}

// Image SHDR
VOID palladium_test_interrupt_c_pt_shdr_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("SHDR_Int\n"));
	Im_SHDR_Int_Handler();
}

// Image SHDR Line
VOID palladium_test_interrupt_c_pt_shdr_line_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("SHDR_Line_Int\n"));
}

// Image ME
VOID palladium_test_interrupt_c_pt_me_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("ME_Int\n"));
	Im_ME_Int_Handler();
}

// Image Graphics
VOID palladium_test_interrupt_c_pt_graphics_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Graphics_Int\n"));
}

// Image JPEG
VOID palladium_test_interrupt_c_pt_jpeg_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Jpeg_Int start\n"));
	Im_JPEG_Int_Handler();
	Ddim_Print(("Jpeg_Int end\n"));
}

// Image RAW
VOID palladium_test_interrupt_c_pt_raw_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("RAW_Int\n"));
	Im_RAW_Int_Handler();
}

// Image IPU
VOID palladium_test_interrupt_c_pt_ipu_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("IPU_Int\n"));
}

// Image ELA Unit
VOID palladium_test_interrupt_c_pt_ela_unit_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Ela_Unit_Int\n"));
	Im_ELA_Int_Handler();
}

// Image Xch
VOID palladium_test_interrupt_c_pt_xch_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Xch_Int\n"));
	Im_Xch_Int_Handler();
}

// Image FPT Unit0
VOID palladium_test_interrupt_c_pt_fpt_unit0_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("FPT_Unit0_Int\n"));
	Im_FPT_Int_Handler( 0 );
}

// Image FPT Unit1
VOID palladium_test_interrupt_c_pt_fpt_unit1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("FPT_Unit1_Int\n"));
	Im_FPT_Int_Handler( 1 );
}

// Image DISP LCD
VOID palladium_test_interrupt_c_pt_disp_lcd_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("DISP_LCD_Int\n"));
}

// Image DISP HDMI
VOID palladium_test_interrupt_c_pt_disp_hdmi_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("DISP_HDMI_Int\n"));
}

// Image DISP MIPI DSI
VOID palladium_test_interrupt_c_pt_disp_mipi_dsi_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("DISP_MIPI_DSI_Int\n"));
}

// Image MIPI DSI Tx
VOID palladium_test_interrupt_c_pt_mipi_dsi_tx_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("MIPI_DSI_Tx_Int\n"));
}

// Image DISP DWCH
VOID palladium_test_interrupt_c_pt_disp_dwch_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("DISP_Dwch_Int\n"));
}

// Image RDMA
VOID palladium_test_interrupt_c_pt_rdma_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("RDMA_Int\n"));
}

// HDMI Master
VOID palladium_test_interrupt_c_pt_hdmi_master_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("HDMI_Master_Int\n"));
}

// HDMI Cec
VOID palladium_test_interrupt_c_pt_hdmi_cec_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("HDMI_Cec_Int\n"));
}

// BMH Unit0
VOID palladium_test_interrupt_c_pt_bmh_unit0_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("BMH_Unit0_Int\n"));
	Im_BMH_Int_Handler( 0 );
}

// BMH Unit1
VOID palladium_test_interrupt_c_pt_bmh_unit1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("BMH_Unit1_Int\n"));
	Im_BMH_Int_Handler( 1 );
}

// RIBERY RBR
VOID palladium_test_interrupt_c_pt_ribery_rbr_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Ribery_Rbr_Int\n"));
}

// RIBERY RWDT
VOID palladium_test_interrupt_c_pt_ribery_rwdt_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Ribery_RWDT_Int\n"));
}

// INTERPROCESSOR0
VOID palladium_test_interrupt_c_pt_interprocessor0_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("INTERPROCESSOR0_Int\n"));
}

// INTERPROCESSOR1
VOID palladium_test_interrupt_c_pt_interprocessor1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("INTERPROCESSOR1_Int\n"));
}

// INTERPROCESSOR2
VOID palladium_test_interrupt_c_pt_interprocessor2_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("INTERPROCESSOR2_Int\n"));
}

// INTERPROCESSOR3
VOID palladium_test_interrupt_c_pt_interprocessor3_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("INTERPROCESSOR3_Int\n"));
}

// DSP Peripheral Unit Ipcu0
VOID palladium_test_interrupt_c_pt_dsp_peripheral_unit_ipcu0_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("DSP_Peripheral_Unit_Ipcu0_Int\n"));
}

// DSP Peripheral Unit Ipcu1
VOID palladium_test_interrupt_c_pt_dsp_peripheral_unit_ipcu1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("DSP_Peripheral_Unit_Ipcu1_Int\n"));
}

// DSP Peripheral Unit Ipcu2
VOID palladium_test_interrupt_c_pt_dsp_peripheral_unit_ipcu2_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("DSP_Peripheral_Unit_Ipcu2_Int\n"));
}

// DSP Peripheral Unit Ipcu3
VOID palladium_test_interrupt_c_pt_dsp_peripheral_unit_ipcu3_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("DSP_Peripheral_Unit_Ipcu3_Int\n"));
}

// DSP Debug
VOID palladium_test_interrupt_c_pt_dsp_debug_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Dsp_Debug_Int\n"));
}

// NandFlash
VOID palladium_test_interrupt_c_pt_nand_flash_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Nand_Flash_Int\n"));
}

// PCIE ch0 Msi
VOID palladium_test_interrupt_c_pt_pcie_ch0_msi_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Pcie_Ch0_Msi_Int\n"));
}

// PCIE ch0 System Error
VOID palladium_test_interrupt_c_pt_pcie_ch0_system_error_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Pcie_Ch0_System_Error_Int\n"));
}

// PCIE ch0 Intx
VOID palladium_test_interrupt_c_pt_pcie_ch0_intx_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Pcie_Ch0_Intx_Int\n"));
}

// PCIE ch0 Core
VOID palladium_test_interrupt_c_pt_pcie_ch0_core_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Pcie_Ch0_Core_Int\n"));
}

// PCIE ch0 DMA
VOID palladium_test_interrupt_c_pt_pcie_ch0_dma_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Pcie_Ch0_DMA_Int\n"));
}

// PCIE ch1 Msi
VOID palladium_test_interrupt_c_pt_pcie_ch1_msi_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Pcie_Ch1_Msi_Int\n"));
}

// PCIE ch1 System Error
VOID palladium_test_interrupt_c_pt_pcie_ch1_system_error_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Pcie_Ch1_System_Error_Int\n"));
}

// PCIE ch1 Intx
VOID palladium_test_interrupt_c_pt_pcie_ch1_intx_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Pcie_Ch1_Intx_Int\n"));
}

// PCIE ch1 Core
VOID palladium_test_interrupt_c_pt_pcie_ch1_core_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Pcie_Ch1_Core_Int\n"));
}

// PCIE ch1 DMA
VOID palladium_test_interrupt_c_pt_pcie_ch1_dma_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Pcie_Ch1_DMA_Int\n"));
}

// External Storage XDMAC ch0
VOID palladium_test_interrupt_c_pt_exs_xdmac_ch0_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Exs_XDMAC_Ch0_Int\n"));
}

// External Storage XDMAC ch1
VOID palladium_test_interrupt_c_pt_exs_xdmac_ch1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Exs_XDMAC_Ch1_Int\n"));
}

// External Storage XDMAC ch2
VOID palladium_test_interrupt_c_pt_exs_xdmac_ch2_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Exs_XDMAC_Ch2_Int\n"));
}

// External Storage XDMAC ch3
VOID palladium_test_interrupt_c_pt_exs_xdmac_ch3_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Exs_XDMAC_Ch3_Int\n"));
}

// External Storage HDMAC ch0
VOID palladium_test_interrupt_c_pt_exs_hdmac_ch0_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Exs_HDMAC_Ch0_Int\n"));
}

// External Storage HDMAC ch1
VOID palladium_test_interrupt_c_pt_exs_hdmac_ch1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Exs_HDMAC_Ch1_Int\n"));
}

// External Storage HDMAC ch2
VOID palladium_test_interrupt_c_pt_exs_hdmac_ch2_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Exs_HDMAC_Ch2_Int\n"));
}

// External Storage HDMAC ch3
VOID palladium_test_interrupt_c_pt_exs_hdmac_ch3_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Exs_HDMAC_Ch3_Int\n"));
}

// USB20 Hdc
VOID palladium_test_interrupt_c_pt_usb20_hdc_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("USB20_Hdc_Int\n"));
}

// USB20 Host EHCI
VOID palladium_test_interrupt_c_pt_usb20_host_ehci_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("USB20_Host_Ehci_Int\n"));
}

// USB20 Host OHCI
VOID palladium_test_interrupt_c_pt_usb20_host_ohci_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("USB20_Host_Ohci_Int\n"));
}

// USB30
VOID palladium_test_interrupt_c_pt_usb30_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("USB30_Int\n"));
}

// Output Signal1
VOID palladium_test_interrupt_c_pt_output_signal1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Output_Signal1_Int\n"));
}

// Output Signal2
VOID palladium_test_interrupt_c_pt_output_signal2_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Output_Signal2_Int\n"));
}

// PME SD card1
VOID palladium_test_interrupt_c_pt_pme_sd_card1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("PME_SD_Card1_Int\n"));
}

// PME F SDH30 UHS1
VOID palladium_test_interrupt_c_pt_pme_f_sdh30_uhs1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("PME_F_SDH30_Uhs1_Int\n"));
}

// Output Signal3
VOID palladium_test_interrupt_c_pt_output_signal3_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Output_Signal3_Int\n"));
}

// F SDH30 UHS1
VOID palladium_test_interrupt_c_pt_f_sdh30_uhs1_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("F_SDH30_Uhs1_Int\n"));
}

// F SDH40 UHS2
VOID palladium_test_interrupt_c_pt_f_sdh40_uhs2_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("F_SDH40_Uhs2_Int\n"));
}

// PME F SDH40 UHS2
VOID palladium_test_interrupt_c_pt_pme_f_sdh40_uhs2_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("PME_F_SDH40_Uhs2_Int\n"));
}

// Output Signal4
VOID palladium_test_interrupt_c_pt_output_signal4_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Output_Signal4_Int\n"));
}

// Output Signal5
VOID palladium_test_interrupt_c_pt_output_signal5_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Output_Signal5_Int\n"));
}

// PME SD card2
VOID palladium_test_interrupt_c_pt_pme_sd_card2_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("PME_SD_Card2_Int\n"));
}

// Output Signal6
VOID palladium_test_interrupt_c_pt_output_signal6_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Output_Signal6_Int\n"));
}

// Wakeup Signal
VOID palladium_test_interrupt_c_pt_wakeup_signal_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Wakeup_Signal_Int\n"));
}

// RELC
VOID palladium_test_interrupt_c_pt_relc_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Relc_Int\n"));
}

// NETSEC A
VOID palladium_test_interrupt_c_pt_netsec_a_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Netsec_A_Int\n"));
}

// NETSEC B
VOID palladium_test_interrupt_c_pt_netsec_b_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Netsec_B_Int\n"));
}

// Output Signal7
VOID palladium_test_interrupt_c_pt_output_signal7_int(PalladiumTestInterruptC* self)
{
	Ddim_Print(("Output_Signal7_Int\n"));
}

PalladiumTestInterruptC* palladium_test_interrupt_c_new(void)
{
	PalladiumTestInterruptC *self = k_object_new(PALLADIUM_TYPE_TEST_INTERRUPT_C);
	return self;
}
