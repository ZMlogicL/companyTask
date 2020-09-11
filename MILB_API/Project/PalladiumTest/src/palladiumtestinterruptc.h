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
#ifndef __PALLADIUM_TEST_INTERRUPT_C_H_
#define __PALLADIUM_TEST_INTERRUPT_C_H_
/**
 * 以下开始include语句
 */
#include "ddim_typedef.h"
#include <klib.h>
/*******
 * 以下开始宏声明
 */
#define PALLADIUM_TYPE_TEST_INTERRUPT_C	(palladium_test_interrupt_c_get_type())
#define PALLADIUM_TEST_INTERRUPT_CER(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestInterruptC)
#define PALLADIUM_IS_TEST_INTERRUPT_C(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_INTERRUPT_C)
/**
 * 以下开始类结构体声明
 */
typedef struct _PalladiumTestInterruptC  PalladiumTestInterruptC;
typedef struct _PalladiumTestInterruptCPrivate		PalladiumTestInterruptCPrivate;

struct _PalladiumTestInterruptC{
	KObject parent;
};

KConstType 		palladium_test_interrupt_c_get_type(void);
#ifdef __cplusplus
extern "C" {
#endif
/**
* 此为公有函数第一个。
 * @arg1	-- 此参数没有意义
 * @str		-- 字符串参数
 * @obj		-- 内部会进行ref操作,外部可以释放
 * @usrData	-- 内部不进行任何修改和复制，要保证在执行过程中访问合法
 * @return:
 * 		TRUE表示成功；否则为失败。
 */
VOID palladium_test_interrupt_c_pt_pas_unit2_hd_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_b2r_unit1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_b2r_unit2_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_ltm_unit1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_ltm_unit2_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_r2y_unit1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_r2y_unit2_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_cnr_unit1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_cnr_unit2_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_iip_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_shdr_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_shdr_line_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_me_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_graphics_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_jpeg_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_raw_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_ipu_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_ela_unit_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_xch_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_fpt_unit0_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_fpt_unit1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_disp_lcd_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_disp_hdmi_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_disp_mipi_dsi_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_mipi_dsi_tx_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_disp_dwch_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_rdma_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_hdmi_master_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_hdmi_cec_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_bmh_unit0_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_bmh_unit1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_ribery_rbr_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_ribery_rwdt_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_interprocessor0_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_interprocessor1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_interprocessor2_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_interprocessor3_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_dsp_peripheral_unit_ipcu0_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_dsp_peripheral_unit_ipcu1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_dsp_peripheral_unit_ipcu2_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_dsp_peripheral_unit_ipcu3_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_dsp_debug_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_nand_flash_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pcie_ch0_msi_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pcie_ch0_system_error_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pcie_ch0_intx_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pcie_ch0_core_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pcie_ch0_dma_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pcie_ch1_msi_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pcie_ch1_system_error_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pcie_ch1_intx_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pcie_ch1_core_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pcie_ch1_dma_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_exs_xdmac_ch0_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_exs_xdmac_ch1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_exs_xdmac_ch2_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_exs_xdmac_ch3_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_exs_hdmac_ch0_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_exs_hdmac_ch1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_exs_hdmac_ch2_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_exs_hdmac_ch3_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_usb20_hdc_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_usb20_host_ehci_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_usb20_host_ohci_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_usb30_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_output_signal1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_output_signal2_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pme_sd_card1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pme_f_sdh30_uhs1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_output_signal3_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_f_sdh30_uhs1_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_f_sdh40_uhs2_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pme_f_sdh40_uhs2_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_output_signal4_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_output_signal5_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_pme_sd_card2_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_output_signal6_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_wakeup_signal_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_relc_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_netsec_a_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_netsec_b_int(PalladiumTestInterruptC* self);
VOID palladium_test_interrupt_c_pt_output_signal7_int(PalladiumTestInterruptC* self);
#ifdef __cplusplus
}
#endif
/**
 * New方法创建对象，应该放在声明的最后
 * @return:
 * 		新创建的对象，极少概率返回NULL(失败)
 */
PalladiumTestInterruptC* 	palladium_test_interrupt_c_new(void);
#endif /* __PALLADIUM_TEST_INTERRUPT_C_H_ */

