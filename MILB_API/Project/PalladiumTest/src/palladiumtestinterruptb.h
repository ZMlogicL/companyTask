/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-09-4
*@author              :hubing
*@brief               :snsos
*@rely                :klib
*@function
*采用ETK-C语言抄写代码
*设计的主要功能:
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __PALLADIUM_TEST_INTERRUPT_B_H_
#define __PALLADIUM_TEST_INTERRUPT_B_H_
/**
 * 以下开始include语句
 */
#include "ddim_typedef.h"
#include <klib.h>
/*******
 * 以下开始宏声明
 */
#define PALLADIUM_TYPE_TEST_INTERRUPT_B	(palladium_test_interrupt_b_get_type())
#define PALLADIUM_TEST_INTERRUPT_BER(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestInterruptB)
#define PALLADIUM_IS_TEST_INTERRUPT_B(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_INTERRUPT_B)
/**
 * 以下开始类结构体声明
 */
typedef struct _PalladiumTestInterruptB    PalladiumTestInterruptB;
typedef struct _PalladiumTestInterruptBPrivate		PalladiumTestInterruptBPrivate;

struct _PalladiumTestInterruptB
{
	KObject parent;
};

KConstType 		palladium_test_interrupt_b_get_type(void);
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
VOID palladium_test_interrupt_b_pt_pwm_ch8_ch11_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_pwm_ch12_ch15_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_pwm_ch0_ch3_stp_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_pwm_ch4_ch7_stp_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_pwm_ch8_ch11_stp_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_Pwm_ch12_ch15_stp_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_audio_if_ch0_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_audio_if_ch1_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_audio_if_ch2_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_audio_if_ch3_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_audio_if_ch4_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_audio_if_ch5_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch0_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch1_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch2_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch3_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch4_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch5_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch6_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac0_ch7_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch0_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch1_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch2_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch3_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch4_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch5_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch6_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_peri_hdmac1_ch7_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch0_reception_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch1_reception_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch2_reception_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch3_reception_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch4_reception_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch5_reception_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch6_reception_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch7_reception_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch0_transmission_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch1_transmission_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch2_transmission_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch3_transmission_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch4_transmission_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch5_transmission_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch6_transmission_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_uart_ch7_transmission_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_spi_ch0_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_spi_ch1_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_spi_ch2_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_pdm_ch0_dma0_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_pdm_ch0_dma1_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_pdm_ch0_fifo_overflow_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_pdm_ch1_dma0_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_pdm_ch1_dma1_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_pdm_ch1_fifo_overflow_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_slimbus_ch0_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_slimbus_ch1_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_slimbus_ch2_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_slimbus_ch3_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sdramc_ch0_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sdramc_ch1_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_mxic_unit0_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_mxic_unit1_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_mxic_unit2_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_mxic_unit3_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_mxic_unit4_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_mxic_unit5_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_mxic_unit6_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sen_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sen_vd_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sen_hd_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sensor_if_macro0_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sensor_if_macro1_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sensor_if_macro2_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sensor_if_macro3_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sro_unit1_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sro_unit1_vd_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sro_unit1_hd_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sro_unit2_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sro_unit2_vd_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_sro_unit2_hd_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_b2b_unit1_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_b2b_unit1_vd_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_b2b_unit1_hd_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_b2b_unit2_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_b2b_unit2_vd_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_b2b_unit2_hd_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_start_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_pas_unit2_int(PalladiumTestInterruptB* self);
VOID palladium_test_interrupt_b_pt_pas_unit2_vd_int(PalladiumTestInterruptB* self);
#ifdef __cplusplus
}
#endif
/**
 * New方法创建对象，应该放在声明的最后
 * @return:
 * 		新创建的对象，极少概率返回NULL(失败)
 */
PalladiumTestInterruptB* 	palladium_test_interrupt_b_new(void);
#endif /* __PALLADIUM_TEST_INTERRUPT_B_H_ */

