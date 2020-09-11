/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 王顺
*@brief : DdCache
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/
/**
 * @file		dd_arm.h
 * @brief		ARM driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

/**
@addtogroup dd_arm
@{
	- @ref dd_arm_sample_section1
	- @ref dd_arm_sample_section2
*/


#ifndef _DD_ARM_H_
#define _DD_ARM_H_


#include "driver_common.h"
#include "ddtop.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DD_ARM_CRITICAL_SECTION_START(s)		{volatile unsigned r=Dd_ARM_Spin_Lock_Composite((kulong*)&s)
/**< Critical Section Start */
#define DD_ARM_CRITICAL_SECTION_END(s)		Dd_ARM_Spin_Unlock((kulong*)&s);Dd_ARM_EI(r);}
/**< Critical Section End */
#ifndef CO_DEBUG_ON_PC
#define DD_ARM_WAIT_NS(ns)								Dd_ARM_Wait_Count(1+((ns) * \
																						((DdTopone_UCLK40I*33/2)/100000)/10000/4))
/**< Wait nsec */
#define DD_ARM_DMB_POU()									__asm__ __volatile__ ("DMB 0xF")
/**< Data Memory Barrier */
#define DD_ARM_DSB_POU()									__asm__ __volatile__ ("DSB 0xF")
/**< Data Synchronization Barrier */
#define DD_ARM_ISB_POU()									__asm__ __volatile__ ("ISB 0xF")
/**< Instruction Synchronization Barrier */
#define DD_ARM_DMB_POC()									__asm__ __volatile__ ("DMB 0xF")
/**< Data Memory Barrier */
#define DD_ARM_DSB_POC()									__asm__ __volatile__ ("DSB 0xF")
/**< Data Synchronization Barrier */
#define DD_ARM_ISB_POC()									__asm__ __volatile__ ("ISB 0xF")
/**< Instruction Synchronization Barrier */
#else
// for PCSim
#define DD_ARM_WAIT_NS(ns)								Dd_ARM_Wait_Count(ns)	/**< Wait nsec */
#define DD_ARM_DMB_POU()
#define DD_ARM_DSB_POU()
#define DD_ARM_ISB_POU()
#define DD_ARM_DMB_POC()
#define DD_ARM_DSB_POC()
#define DD_ARM_ISB_POC()
#endif

#define D_DD_ARM_NUM_OF_CORES						(4)	/**< CPU core number. */


/**
 Wait by machine cycle count.
 @param[in]	count	: wait count
 */
void Dd_ARM_Wait_Count(kuint32 count);

/**
 Enable IRQ and Set program status included IRQ mask bit
 @param[in]	sr		: program status included IRQ mask bit
 */
void Dd_ARM_EI(unsigned sr);

/**
 Disable IRQ and Get program status included IRQ mask bit
 @return		program status included IRQ mask bit
 */
unsigned Dd_ARM_DI(void);

/**
 Spin Lock function.<br>
 @param[in]	spin_id	: pointer of spin lock address
 */
void Dd_ARM_Spin_Lock(kulong* spin_id);

/**
 Spin Lock function.<br>
 @param[in]	spin_id	: pointer of spin lock address
 @retval		lock return (0:OK 1:NG)
 */
kulong Dd_ARM_Spin_Lock_Ret(kulong* spin_id);

/**
 Spin Lock function.<br>
 @param[in]	spin_id	: pointer of spin lock address
 @return		program status
 @remarks	When enable interrupt, It can accept interrupt.
 After this, interrupt is disable.
 */
unsigned Dd_ARM_Spin_Lock_Composite(kulong* spin_id);

/**
 Spin Unlock function.<br>
 @param[in]	spin_id	: pointer of spin lock address
 */
void Dd_ARM_Spin_Unlock(kulong* spin_id);

/**
 Get CPU core ID.
 @retval	0			: CPU0
 @retval	1			: CPU1
 @retval	2			: CPU2
 @retval	3			: CPU3
 */
kulong Dd_ARM_Get_CPU_ID(void);

/**
 Get tranlation table base.
 @retval	tranlation table base register0
 */
kulong Dd_ARM_Get_TTB(void);

/**
 Change vector table base.
 @param[in]	address	: base address
 */
void Dd_ARM_Change_Vector_Table(kuint32 address);

/**
 L1 Prefetch Disable.
 */
void Dd_ARM_L1_Prefetch_Disable(void);

/**
 L1 Prefetch Enable.
 */
void Dd_ARM_L1_Prefetch_Enable(void);

/**
 Enable IRQ & FIQ and Set program status included IRQ & FIQ mask bit.
 @param[in]	sr			: program status included IRQ & FIQ mask bit
 */
void Dd_ARM_EIF(kulong sr);

/**
 Disable IRQ & FIQ and Get program status included IRQ & FIQ mask bit.
 @retval	program status included IRQ & FIQ mask bit
 */
kulong Dd_ARM_DIF(void);

/**
 MMU Disable.
 */
void Dd_ARM_MMU_Disable(void);

/**
 MMU Enable.
 */
void Dd_ARM_MMU_Enable(void);

/*@}*/

/**
 @weakgroup dd_arm
 @{
 @section dd_arm_sample_section1		Sample of 'Interrupt Enable/Disable Control'
 using DD_ARM_CRITICAL_SECTION_START and DD_ARM_CRITICAL_SECTION_END functions.
 @code
 static kulong xxxx_Spin_Lock1 __attribute__((section(".XXXXXXXX"), aligned(64)));
 void XXXX_function(void)
 {
 DD_ARM_CRITICAL_SECTION_START(xxxx_Spin_Lock);
 //
 // critical setion.
 // disable interrupt area.
 //
 DD_ARM_CRITICAL_SECTION_END(xxxx_Spin_Lock);
 }
 @endcode
 <br>
 @section dd_arm_sample_section2		Sample of 'Spin Lock Control' using Dd_ARM_Spin_Lock and
 Dd_ARM_Spin_Unlock functions.
 @code
 static kulong xxxx_Spin_Lock2 __attribute__((section(".XXXXXXXX"), aligned(64)));
 void XXXX_function(void)
 {
 Dd_ARM_Spin_Lock(&xxxx_Spin_Lock2);

 // macro settings, etc.

 Dd_ARM_Spin_Unlock(&xxxx_Spin_Lock2);
 }
 @endcode
 @}*/

#ifdef __cplusplus
}
#endif

#endif	// _DD_ARM_H_
