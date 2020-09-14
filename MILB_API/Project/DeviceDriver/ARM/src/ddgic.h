/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 王顺
*@brief : DdGic
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/
/**
 * @file		ddgic.h
 * @brief		GIC (Generic Interrupt Controller) driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

/**
@addtogroup dd_gic
@{
	- @ref dd_gic_sample_section1
	- @ref dd_gic_sample_section2
	- @ref dd_gic_sample_section3
	- @ref dd_gic_sample_section4
*/


#ifndef _DD_GIC_H_
#define _DD_GIC_H_


#include <klib.h>
#include "driver_common.h"
#include "arm.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DD_TYPE_GIC                  (dd_gic_get_type())
#define DD_GIC(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdGic))
#define DD_IS_GIC(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DD_TYPE_GIC))

// Return value of GIC processing result
#define	C_GIC_INPUT_PARAM_ERR		(D_DD_GIC | D_DDIM_INPUT_PARAM_ERROR)	/**< Input Parameter Error */

/** Interrupt ID and Mask */
#define	C_INTID_MAX							(320)					/**< Interrupt ID MAX */
#define	C_INTID_SGI_MAX					(15)						/**< Interrupt ID SGI(Software Generated Interrupt) MAX */
#define	C_INTID_PPI_MAX					(31)						/**< Interrupt ID PPI(Private Peripheral Interrupt) MAX */
#define	C_INTID_SPI_MAX					(319)					/**< Interrupt ID SPI(Shared Peripheral Interrupt) MAX */
#define	C_SPURIOUS_INTERRUPT		(1023)					/**< Spurious Interrupt ID */
#define C_INTERRUPT_MASK				(0x000003FF)		/**< Interrupt Acknowledge Register MASK */

/** Interrupt Priority Value */
#define	C_PRI00									(0x00)					/**< Interrupt Priority 00:(0x00) */
#define	C_PRI01									(0x08)					/**< Interrupt Priority 01:(0x08) */
#define	C_PRI02									(0x10)					/**< Interrupt Priority 02:(0x10) */
#define	C_PRI03									(0x18)					/**< Interrupt Priority 03:(0x18) */
#define	C_PRI04									(0x20)					/**< Interrupt Priority 04:(0x20) */
#define	C_PRI05									(0x28)					/**< Interrupt Priority 05:(0x28) */
#define	C_PRI06									(0x30)					/**< Interrupt Priority 06:(0x30) */
#define	C_PRI07									(0x38)					/**< Interrupt Priority 07:(0x38) */
#define	C_PRI08									(0x40)					/**< Interrupt Priority 08:(0x40) */
#define	C_PRI09									(0x48)					/**< Interrupt Priority 09:(0x48) */
#define	C_PRI10									(0x50)					/**< Interrupt Priority 10:(0x50) */
#define	C_PRI11									(0x58)					/**< Interrupt Priority 11:(0x58) */
#define	C_PRI12									(0x60)					/**< Interrupt Priority 12:(0x60) */
#define	C_PRI13									(0x68)					/**< Interrupt Priority 13:(0x68) */
#define	C_PRI14									(0x70)					/**< Interrupt Priority 14:(0x70) */
#define	C_PRI15									(0x78)					/**< Interrupt Priority 15:(0x78) */
#define	C_PRI16									(0x80)					/**< Interrupt Priority 16:(0x80) */
#define	C_PRI17									(0x88)					/**< Interrupt Priority 17:(0x88) */
#define	C_PRI18									(0x90)					/**< Interrupt Priority 18:(0x90) */
#define	C_PRI19									(0x98)					/**< Interrupt Priority 19:(0x98) */
#define	C_PRI20									(0xA0)					/**< Interrupt Priority 20:(0xA0) */
#define	C_PRI21									(0xA8)					/**< Interrupt Priority 21:(0xA8) */
#define	C_PRI22									(0xB0)					/**< Interrupt Priority 22:(0xB0) */
#define	C_PRI23									(0xB8)					/**< Interrupt Priority 23:(0xB8) */
#define	C_PRI24									(0xC0)					/**< Interrupt Priority 24:(0xC0) */
#define	C_PRI25									(0xC8)					/**< Interrupt Priority 25:(0xC8) */
#define	C_PRI26									(0xD0)					/**< Interrupt Priority 26:(0xD0) */
#define	C_PRI27									(0xD8)					/**< Interrupt Priority 27:(0xD8) */
#define	C_PRI28									(0xE0)					/**< Interrupt Priority 28:(0xE0) */
#define	C_PRI29									(0xE8)					/**< Interrupt Priority 29:(0xE8) */
#define	C_PRI30									(0xF0)					/**< Interrupt Priority 30:(0xF0) */
#define	C_PRI31									(0xF8)					/**< Interrupt Priority 31:(0xF8) */

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
/* Distributor Register */
// Distributor Control Register(GICD_CTLR)
#define DdGic_DIST_GET_CTLR_ENABLEGRP0					(IO_GIC_DIST.GICD_CTLR.bit.ENABLEGR0)
/**< Get GICD_CTLR EnableGrp0(0:Disable, 1:Enable) */
#define DdGic_DIST_DIST_SET_CTLR_ENABLEGRP0(val)	{IO_GIC_DIST.GICD_CTLR.bit.ENABLEGR0 = (val);}
/**< Set GICD_CTLR EnableGrp0(0:Disable, 1:Enable) */
#define DdGic_DIST_GET_CTLR_ENABLEGRP1					(IO_GIC_DIST.GICD_CTLR.bit.ENABLEGR1)
/**< Get GICD_CTLR EnableGrp1(0:Disable, 1:Enable) */
#define DdGic_DIST_SET_CTLR_ENABLEGRP1(val)				{IO_GIC_DIST.GICD_CTLR.bit.ENABLEGR1 = (val);}
/**< Set GICD_CTLR EnableGrp1(0:Disable, 1:Enable) */

// Interrupt Controller Type Register(GICD_TYPER)
#define DdGic_DIST_GET_TYPER_ITLINESNUMBER			(IO_GIC_DIST.GICD_TYPER.bit.ITLINESNUMBER)
/**< Get GICD_TYPER Number of Interrupts<br>
 0b00000 : Up to 32 interruptsa, no external interrupt lines<br>
 0b00001 : Up to 64 interrupts, 32 external interrupt lines<br>
 0b00010 : Up to 96 interrupts, 64 external interrupt lines<br>
 .<br>
 .<br>
 0b01111 Up to 512 interrupts, 480 external interrupt lines<br>
 */
#define DdGic_DIST_GET_TYPER_CPUNUMBER					(IO_GIC_DIST.GICD_TYPER.bit.CPUNUMBER)
/**< Get GICD_TYPER Number of Implemented Processors(1:Two CPUs)<br>
 0b000 : One processor<br>
 0b001 : Two processor<br>
 0b010 : Three processor<br>
 0b011 : Four processors<br>
 */
#define DdGic_DIST_GET_TYPER_SECURITYEXTN				(IO_GIC_DIST.GICD_TYPER.bit.SECURITY_EXTN)
/**< Get GICD_TYPER Security Extensions<br>
 1 : Security Extensions<br>
 */
#define DdGic_DIST_GET_TYPER_LSPI								(IO_GIC_DIST.GICD_TYPER.bit.LSPI)
/**< Get GICD_TYPER Lockable Shared Peripheral Interrupts<br>
 0b11111 : 31 LSPIs<br>
 */

// Distributor Implementer Identification Register(GICD_IIDR)
#define DdGic_DIST_GET_IIDR_IMPLEMENTER					(IO_GIC_DIST.GICD_IIDR.bit.IMPLEMENTER)
/**< Get GICD_IIDR Implementer(0x43B:ARM implementation) */
#define DdGic_DIST_GET_IIDR_REVISION							(IO_GIC_DIST.GICD_IIDR.bit.REVISION)
/**< Get GICD_IIDR Minor Revision Number(0x1:Revision number) */
#define DdGic_DIST_GET_IIDR_VARIANT							(IO_GIC_DIST.GICD_IIDR.bit.VARIANT)
/**< Get GICD_IIDR Major Revision Number(0x0:Variant number) */
#define DdGic_DIST_GET_IIDR_PRODUCTID						(IO_GIC_DIST.GICD_IIDR.bit.PRODUCTID)
/**< Get GICD_IIDR ProductID(0x01:Cortex-A7) */

// Interrupt Group Register(GICD_IGROUPR)
#define DdGic_DIST_GET_IGROUPR(uni)							(IO_GIC_DIST.GICD_IGROUPR[uni])
/**< Get GICD_IGROUPR Group Status bit(uni:0 to 31)<br>
 Bit Field Value<br>
 0 : Group0<br>
 1 : Group1<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */
#define DdGic_DIST_SET_IGROUPR(uni,val)						{IO_GIC_DIST.GICD_IGROUPR[uni] = (val);}
/**< Set GICD_IGROUPR Group Status bit(uni:0 to 31)<br>
 Bit Field Value<br>
 0 : Group0<br>
 1 : Group1<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */

// Interrupt Set-Enable Register(GICD_ISENABLER)
#define DdGic_DIST_GET_ISENABLER(uni)						(IO_GIC_DIST.GICD_ISENABLER[uni])
/**< Get GICD_ISENABLER Set Enable bit(uni:0 to 31)<br>
 Bit Field Value<br>
 0 : Interrupt Disable<br>
 1 : Interrupt Enaable<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */
#define DdGic_DIST_SET_ISENABLER(uni,val)				{IO_GIC_DIST.GICD_ISENABLER[uni] = (val);}
/**< Set GICD_ISENABLER Set Enable bit(uni:0 to 31)<br>
 Bit Field Value(val)<br>
 0 : Has no effect<br>
 1 : Interrupt Enaable<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */

// Interrupt Clear-Enable Register(GICD_ICENABLER)
#define DdGic_DIST_GET_ICENABLER(uni)						(IO_GIC_DIST.GICD_ICENABLER[uni])
/**< Get GICD_ICENABLER Clear Enable bit(uni:0 to 31)<br>
 Bit Field Value<br>
 0 : Interrupt Disable<br>
 1 : Interrupt Enaable<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */
#define DdGic_DIST_SET_ICENABLER(uni,val)				{IO_GIC_DIST.GICD_ICENABLER[uni] = (val);}
/**< Set GICD_ICENABLER Clear Enable bit(uni:0 to 31)<br>
 Bit Field Value<br>
 0 : Has no effect<br>
 1 : Interrupt Disable<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */

// Interrupt Set-Pending Register(GICD_ISPENDR)
#define DdGic_DIST_GET_ISPENDR(uni)							(IO_GIC_DIST.GICD_ISPENDR[uni])
/**< Get GICD_ISPENDR Set-Pending bit(uni:0 to 31)<br>
 Bit Field Value<br>
 0 : Not pending<br>
 1 : SGI and PPI, Pending on this processor<br>
 PPI, Pending on at least one processer<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */
#define DdGic_DIST_SET_ISPENDR(uni,val)					{IO_GIC_DIST.GICD_ISPENDR[uni] = (val);}
/**< Set GICD_ISPENDR Set-Pending bit(uni:0 to 31)<br>
 Bit Field Value<br>
 0 : Has no effect<br>
 1 : Interrupt is pending<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */

// Interrupt Clear-Pending Register(GICD_ICPENDR)
#define DdGic_DIST_GET_ICPENDR(uni)							(IO_GIC_DIST.GICD_ICPENDR[uni])
/**< Get GICD_ICPENDR Clear-Pending bit(uni:0 to 31)<br>
 Bit Field Value<br>
 0 : Not pending<br>
 1 : SGI and PPI, Pending on this processor<br>
 PPI, Pending on at least one processer<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */
#define DdGic_DIST_SET_ICPENDR(uni,val)					{IO_GIC_DIST.GICD_ICPENDR[uni] = (val);}
/**< Set GICD_ICPENDR Clear-Pending bit(uni:0 to 7)<br>
 Bit Field Value<br>
 0 : Has no effect<br>
 1 : Interrupt is not pending<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */

// Interrupt Set-Active Register(GICD_ISACTIVER)
#define DdGic_DIST_GET_ISACTIVER(uni)						(IO_GIC_DIST.GICD_ISACTIVER[uni])
/**< Get GICD_ISACTIVER Set-Active bit(uni:0 to 31)<br>
 Bit Field Value<br>
 0 : Interrupt is not active<br>
 1 : Interrupt is active<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */
#define DdGic_DIST_SET_ISACTIVER(uni,val)					{IO_GIC_DIST.GICD_ISACTIVER[uni] = (val);}
/**< Set GICD_ISACTIVER Set-Active bit(uni:0 to 31)<br>
 Bit Field Value<br>
 0 : Has no effect<br>
 1 : Activates the interrupt<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */

// Interrupt Clear-Active Register(GICD_ICACTIVER)
#define DdGic_DIST_GET_ICACTIVER(uni)						(IO_GIC_DIST.GICD_ICACTIVER[uni])
/**< Get GICD_ICACTIVER Clear-Active bit(uni:0 to 31)<br>
 Bit Field Value<br>
 0 : Interrupt is not active<br>
 1 : Interrupt is active<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */
#define DdGic_DIST_SET_ICACTIVER(uni,val)					{IO_GIC_DIST.GICD_ICACTIVER[uni] = (val);}
/**< Set GICD_ICACTIVER Clear-Active bit(uni:0 to 31)<br>
 Bit Field Value<br>
 0 : Has no effect<br>
 1 : Deactivates the interrupt<br>
 INTID<br>
 INTID = ((uni*32) + Bit position)<br>
 */

// Interrupt Priority Register(GICD_IPRIORITYR)
#define DdGic_DIST_GET_IPRIORITYR(uni)						(IO_GIC_DIST.GICD_IPRIORITYR[uni])
/**< Get GICD_IPRIORITYR Priority byte(uni:0 to 511)<br>
 Byte Field Value<br>
 Range of priority mask<br>
 32 supported levels : 0x00 to 0xF8<br>
 INTID<br>
 INTID = uni<br>
 */
#define DdGic_DIST_SET_IPRIORITYR(uni,val)					{IO_GIC_DIST.GICD_IPRIORITYR[uni] = (val);}
/**< Set GICD_IPRIORITYR Priority byte(uni:0 to 511)<br>
 Byte Field Value<br>
 Range of priority mask<br>
 32 supported levels : 0x00 to 0xF8<br>
 INTID<br>
 INTID = uni<br>
 */

// Interrupt Processor Targets Register(GICD_ITARGETSR)
#define DdGic_DIST_GET_ITARGETSR(uni)							(IO_GIC_DIST.GICD_ITARGETSR[uni])
/**< Get GICD_ITARGETSR CPU target byte(uni:0 to 511)<br>
 Byte Field Value<br>
 0bxxxxxxx1 : CPU interface 0<br>
 0bxxxxxx1x : CPU interface 1<br>
 0bxxxxx1xx : CPU interface 2<br>
 .<br>
 .<br>
 0b1xxxxxxx : CPU interface 7<br>
 INTID<br>
 INTID = uni<br>
 */
#define DdGic_DIST_SET_ITARGETSR(uni,val)					{IO_GIC_DIST.GICD_ITARGETSR[uni] = (val);}
/**< Set GICD_ITARGETSR CPU target byte(uni:0 to 511)<br>
 Byte Field Value<br>
 0bxxxxxxx1 : CPU interface 0<br>
 0bxxxxxx1x : CPU interface 1<br>
 0bxxxxx1xx : CPU interface 2<br>
 .<br>
 .<br>
 0b1xxxxxxx : CPU interface 7<br>
 INTID<br>
 INTID = uni<br>
 */

// Interrupt Configuration Register(GICD_ICFGR)
#define DdGic_DIST_GET_ICFGR(uni)							(IO_GIC_DIST.GICD_ICFGR[uni])
/**< Get GICD_ICFGR Interrupt Config field(uni:0 to 31)<br>
 Field Value<br>
 [2F]     : Reserved<br>
 [2F+1] 0 : Level-Sensitive<br>
 1 : Edge-Triggered<br>
 INTID<br>
 INTID = ((uni*16) + Field offset)<br>
 */
#define DdGic_DIST_SET_ICFGR(uni,val)						{IO_GIC_DIST.GICD_ICFGR[uni] = (val);}
/**< Set GICD_ICFGR Interrupt Config field(uni: 0 to 31)<br>
 Field Value<br>
 [2F]     : Reserved<br>
 [2F+1] 0 : Level-Sensitive<br>
 1 : Edge-Triggered<br>
 INTID<br>
 INTID = ((uni*16) + Field offset)<br>
 */

// Private Peripheral Interrupt Status Register(GICD_PPISR)
#define DdGic_DIST_GET_PPISR									(IO_GIC_DIST.GICD_PPISR.word)
/**< Get GICD_PPISR PPI status<br>
 PPI Status Value<br>
 [9]  : Virtual Maintenance Interrupt<br>
 [10] : Hypervisor timer event<br>
 [11] : Virtual timer event<br>
 [12] : nIRQ<br>
 [13] : Non-secure physical timer event<br>
 [14] : Secure physical timer event<br>
 [15] : nFIQ<br>
 */

// Shared Peripheral Interrupt Status Register(GICD_SPISR)
#define DdGic_DIST_GET_SPISR(uni)						(IO_GIC_DIST.GICD_SPISR[uni])
/**< Get GICD_SPISR SPI status(uni:0 to 14)<br>
 SPI Status Value<br>
 0 : IRQS is LOW<br>
 1 : IRQS is HIGH<br>
 INTID<br>
 INTID = ((uni*32) + (bit position + 32))<br>
 */


// Software Generated Interrupt Register(GICD_SGIR)
#define DdGic_DIST_SET_SGIR(val)						{IO_GIC_DIST.GICD_SGIR.word = (val);}
/**< Set GICD_SGIR SGIR bit<br>
 SGIR Bit Field Value<br>
 [25:24] : Process the requested SGI<br>
 0 : Specified in TargetList<br>
 1 : All CPU except the processor requested<br>
 2 : Only CPU of processor requested<br>
 3 : Reserved<br>
 [23:16] : TargetList Filter<br>
 0bxxxxxxx1 : CPU interface 0<br>
 0bxxxxxx1x : CPU interface 1<br>
 0bxxxxx1xx : CPU interface 2<br>
 .<br>
 .<br>
 0b1xxxxxxx : CPU interface 7<br>
 [15]    : NSATT<br>
 0 : Group0<br>
 1 : Group1<br>
 [3:0]   : Interrupt ID(0 to 15)<br>
 */
// SGI Clear-Pending Register(GICD_CPENDSGIR)
#define DdGic_DIST_GET_CPENDSGIR(uni)					(IO_GIC_DIST.GICD_CPENDSGIR[uni])
/**< Get GICD_CPENDSGIR SGI Clear-Pending bit(uni:0 to 3)<br>
 Bit Field Value<br>
 0 : Not pending<br>
 1 : Pending<br>
 INTID<br>
 INTID = ((uni*4) + Field offset)<br>
 */
#define DdGic_DIST_SET_CPENDSGIR(uni,val)				{IO_GIC_DIST.GICD_CPENDSGIR[uni] = (val);}
/**< Set GICD_CPENDSGIR SGI Clear-Pending bit(uni:0 to 3)<br>
 Bit Field Value<br>
 0 : Has no effect<br>
 1 : Removes the pending<br>
 INTID<br>
 INTID = ((uni*4) + Field offset)<br>
 */

// SGI Set-Pending Register(GICD_SPENDSGIR)
#define DdGic_DIST_GET_SPENDSGIR(uni)					(IO_GIC_DIST.GICD_SPENDSGIR[uni])
/**< Get GICD_SPENDSGIR SGI Set-Pending bit(uni:0 to 3)<br>
 Bit Field Value<br>
 0 : Not pending<br>
 1 : Pending<br>
 INTID<br>
 INTID = ((uni*4) + Field offset)<br>
 */
#define DdGic_DIST_SET_SPENDSGIR(uni,val)				{IO_GIC_DIST.GICD_SPENDSGIR[uni] = (val);}
/**< Set GICD_SPENDSGIR SGI Set-Pending bit(uni:0 to 3)<br>
 Bit Field Value<br>
 0 : Has no effect<br>
 1 : Adds the pending<br>
 INTID<br>
 INTID = ((uni*4) + Field offset)<br>
 */

/* CPU Interface Control Register */

// CPU Interface Control Register(GICC_CTLR)
#define DdGic_CPU_GET_CTLR_ENABLEGRP0					(IO_GIC_CPU.GICC_CTLR.bit.ENABLEGRP0)
/**< Get GICC_CTLR Group0 interrupts(0:Disable, 1:Enable) */
#define DdGic_CPU_SET_CTLR_ENABLEGRP0(val)				{IO_GIC_CPU.GICC_CTLR.bit.ENABLEGRP0 = (val);}
/**< Set GICC_CTLR Group0 interrupts(0:Disable, 1:Enable) */
#define DdGic_CPU_GET_CTLR_ENABLEGRP1					(IO_GIC_CPU.GICC_CTLR.bit.ENABLEGRP1)
/**< Get GICC_CTLR Group1 interrupts(0:Disable, 1:Enable) */
#define DdGic_CPU_SET_CTLR_ENABLEGRP1(val)				{IO_GIC_CPU.GICC_CTLR.bit.ENABLEGRP1 = (val);}
/**< Set GICC_CTLR Group1 interrupts(0:Disable, 1:Enable) */
#define DdGic_CPU_GET_CTLR_ACKCTL								(IO_GIC_CPU.GICC_CTLR.bit.ACKCTL)
/**< Get GICC_CTLR Acknowledged of GICC_IAR(0:Not Acknowledged, 1:Acknowledges) */
#define DdGic_CPU_SET_CTLR_ACKCTL(val)						{IO_GIC_CPU.GICC_CTLR.bit.ACKCTL = (val);}
/**< Set GICC_CTLR Acknowledged of GICC_IAR(0:Not Acknowledged, 1:Acknowledges) */
#define DdGic_CPU_GET_CTLR_FIQEN								(IO_GIC_CPU.GICC_CTLR.bit.FIQEN)
/**< Get GICC_CTLR Use of FIQ or IRQ(0:IRQ, 1:FIQ) */
#define DdGic_CPU_SET_CTLR_FIQEN(val)							{IO_GIC_CPU.GICC_CTLR.bit.FIQEN = (val);}
/**< Set GICC_CTLR Use of FIQ or IRQ(0:IRQ, 1:FIQ) */
#define DdGic_CPU_GET_CTLR_SBPR									(IO_GIC_CPU.GICC_CTLR.bit.CBPR)
/**< Get GICC_CTLR Control of GICC_BPR(0:Group0, 1:Both Group0 and Group1) */
#define DdGic_CPU_SET_CTLR_SBPR(val)							{IO_GIC_CPU.GICC_CTLR.bit.CBPR = (val);}
/**< Set GICC_CTLR Control of GICC_BPR(0:Group0, 1:Both Group0 and Group1) */
#define DdGic_CPU_GET_CTLR_FIQBYDISGRP0					(IO_GIC_CPU.GICC_CTLR.bit.FIQBYPDISGRP0)
/**< Get GICC_CTLR Control of Group0 FIQ Signal(0:Signal, 1:Not Signal) */
#define DdGic_CPU_SET_CTLR_FIQBYDISGRP0(val)			{IO_GIC_CPU.GICC_CTLR.bit.FIQBYPDISGRP0 = (val);}
/**< Set GICC_CTLR Control of Group0 FIQ Signal(0:Signal, 1:Not Signal) */
#define DdGic_CPU_GET_CTLR_IRQBYDISGRP0					(IO_GIC_CPU.GICC_CTLR.bit.IRQBYPDISGRP0)
/**< Get GICC_CTLR Control of Group0 IRQ Signal(0:Signal, 1:Not Signal) */
#define DdGic_CPU_SET_CTLR_IRQBYDISGRP0(val)			{IO_GIC_CPU.GICC_CTLR.bit.IRQBYPDISGRP0 = (val);}
/**< Set GICC_CTLR Control of Group0 IRQ Signal(0:Signal, 1:Not Signal) */
#define DdGic_CPU_GET_CTLR_FIQBYDISGRP1					(IO_GIC_CPU.GICC_CTLR.bit.FIQBYPDISGRP1)
/**< Get GICC_CTLR Control of Group1 FIQ Signal(0:Signal, 1:Not Signal) */
#define DdGic_CPU_SET_CTLR_FIQBYDISGRP1(val)			{IO_GIC_CPU.GICC_CTLR.bit.FIQBYPDISGRP1 = (val);}
/**< Set GICC_CTLR Control of Group1 FIQ Signal(0:Signal, 1:Not Signal) */
#define DdGic_CPU_GET_CTLR_IRQBYDISGRP1					(IO_GIC_CPU.GICC_CTLR.bit.IRQBYPDISGRP1)
/**< Get GICC_CTLR Control of Group1 IRQ Signal(0:Signal, 1:Not Signal) */
#define DdGic_CPU_SET_CTLR_IRQBYDISGRP1(val)			{IO_GIC_CPU.GICC_CTLR.bit.IRQBYPDISGRP1 = (val);}
/**< Set GICC_CTLR Control of Group1 IRQ Signal(0:Signal, 1:Not Signal) */
#define DdGic_CPU_GET_CTLR_EOIMODES						(IO_GIC_CPU.GICC_CTLR.bit.EOIMODES)
/**< Get GICC_CTLR Control of GICC_EOIR and GICC_DIR<br>
 0 : GICC_EOIR has both priority drop and deactivate interrupt functionality.
 Accesses to the GICC_DIR are UNPREDICTABLE.
 1 : GICC_EOIR has priority drop functionality only.
 GICC_DIR has deactivate interrupt functionality.
 */
#define DdGic_CPU_SET_CTLR_EOIMODES(val)					{IO_GIC_CPU.GICC_CTLR.bit.EOIMODES = (val);}
/**< Set GICC_CTLR Control of GICC_EOIR and GICC_DIR<br>
 0 : GICC_EOIR has both priority drop and deactivate interrupt functionality.
 Accesses to the GICC_DIR are UNPREDICTABLE.
 1 : GICC_EOIR has priority drop functionality only.
 GICC_DIR has deactivate interrupt functionality.
 */
#define DdGic_CPU_GET_CTLR_EOIMODENS						(IO_GIC_CPU.GICC_CTLR.bit.EOIMODENS)
/**< Get GICC_CTLR Control of GICC_EOIR and GICC_DIR<br>
 0 : GICC_EOIR has both priority drop and deactivate interrupt functionality.
 Accesses to the GICC_DIR are UNPREDICTABLE.
 1 : GICC_EOIR has priority drop functionality only.
 GICC_DIR has deactivate interrupt functionality.
 */
#define DdGic_CPU_SET_CTLR_EOIMODENS(val)				{IO_GIC_CPU.GICC_CTLR.bit.EOIMODENS = (val);}
/**< Set GICC_CTLR Control of GICC_EOIR and GICC_DIR<br>
 0 : GICC_EOIR has both priority drop and deactivate interrupt functionality.
 Accesses to the GICC_DIR are UNPREDICTABLE.
 1 : GICC_EOIR has priority drop functionality only.
 GICC_DIR has deactivate interrupt functionality.
 */

// Interrupt Priority Mask Register(GICC_PMR)
#define DdGic_CPU_GET_PMR_PRIORITY							(IO_GIC_CPU.GICC_PMR.bit.PRIORITY)
/**< Get GICC_PMR Priority bit<br>
 Bit Field Value<br>
 0xFF : 256 supported levels<br>
 0xFE : 128 supported levels<br>
 0xFC :  64 supported levels<br>
 0xF8 :  32 supported levels<br>
 0xF0 :  16 supported levels<br>
 */
#define DdGic_CPU_SET_PMR_PRIORITY(val)						{IO_GIC_CPU.GICC_PMR.bit.PRIORITY = (val);}
/**< Set GICC_PMR Priority bit<br>
 Bit Field Value<br>
 0xFF : 256 supported levels<br>
 0xFE : 128 supported levels<br>
 0xFC :  64 supported levels<br>
 0xF8 :  32 supported levels<br>
 0xF0 :  16 supported levels<br>
 */

// Binary Point Register(GICC_BPR)
#define DdGic_CPU_GET_BPR_BINARYPOINT					(IO_GIC_CPU.GICC_BPR.bit.BINARYPOINT)
/**< Get GICC_BPR BinaryPoint bit<br>
 Bit Field Value<br>
 0 to 7 : Interrupt preemption<br>
 */
#define DdGic_CPU_SET_BPR_BINARYPOINT(val)				{IO_GIC_CPU.GICC_BPR.bit.BINARYPOINT = (val);}
/**< Set GICC_BPR BinaryPoint bit<br>
 Bit Field Value<br>
 <table>
 <tr><th>val</th><th>Group priority field</th><th>Subpriority field</th><th>Field with binary point</th></tr>
 <tr><td>0</td><td>[7:1]</td><td>[0]</td><td>ggggggg.s</td></tr>
 <tr><td>1</td><td>[7:2]</td><td>[1:0]</td><td>gggggg.ss</td></tr>
 <tr><td>2</td><td>[7:3]</td><td>[2:0]</td><td>ggggg.sss</td></tr>
 <tr><td>3</td><td>[7:4]</td><td>[3:0]</td><td>gggg.ssss</td></tr>
 <tr><td>4</td><td>[7:5]</td><td>[4:0]</td><td>ggg.sssss</td></tr>
 <tr><td>5</td><td>[7:6]</td><td>[5:0]</td><td>gg.ssssss</td></tr>
 <tr><td>6</td><td>[7]</td><td>[6:0]</td><td>g.sssssss</td></tr>
 <tr><td>7</td><td>No preemption</td><td>[7:0]</td><td>.ssssssss</td></tr>
 </table>
 */

// Interrupt Acknowledge Register(GICC_IAR)
#define DdGic_CPU_GET_IAR										(IO_GIC_CPU.GICC_IAR.word)
/**< Get GICC_IAR Acknowledge Register */
#define DdGic_CPU_GET_IAR_ACKINTID						(IO_GIC_CPU.GICC_IAR.bit.ACKINTID)
/**< Get GICC_IAR AckIntId bit */
#define DdGic_CPU_GET_IAR_CPUID							(IO_GIC_CPU.GICC_IAR.bit.CPUID)
/**< Get GICC_IAR CpuId bit */

// End of Interrupt Register(GICC_EOIR)
#define DdGic_CPU_SET_EOIR(val)								{IO_GIC_CPU.GICC_EOIR.word = (val);}
/**< Set GICC_EOIR End of Interrupt Register */
#define DdGic_CPU_SET_EOIR_EOIINTID(val)			{IO_GIC_CPU.GICC_EOIR.bit.EOIINTID = (val);}
/**< Set GICC_EOIR EoiIntId bit */
#define DdGic_CPU_SET_EOIR_CPUID(val)					{IO_GIC_CPU.GICC_EOIR.bit.CPUID = (val);}
/**< Set GICC_EOIR CpuId bit */

// Running Priority Register(GICC_RPR)
#define DdGic_CPU_GET_RPR_PRIORITY					(IO_GIC_CPU.GICC_RPR.bit.PRIORITY)
/**< Get GICC_RPR Priority bit */

// Highest Priority Pending Interrupt Register(GICC_HPPIR)
#define DdGic_CPU_GET_HPPIR_PENDINTID				(IO_GIC_CPU.GICC_HPPIR.bit.PENDINTID)
/**< Get GICC_HPPIR PendIntId */
#define DdGic_CPU_GET_HPPIR_CPUID						(IO_GIC_CPU.GICC_HPPIR.bit.CPUID)
/**< Get GICC_HPPIR CpuId */

// Aliased Binary Point Register(GICC_ABPR)
#define DdGic_CPU_GET_ABPR_BINARYPOINT			(IO_GIC_CPU.GICC_ABPR.bit.BINARYPOINT)
/**< Get BINARYPOINT BinaryPoint bit<br>
 Bit Field Value<br>
 0 to 7 : Interrupt preemption<br>
 */

#define DdGic_CPU_SET_ABPR_BINARYPOINT(val)	{IO_GIC_CPU.GICC_ABPR.bit.BINARYPOINT = (val);}
/**< Set BINARYPOINT BinaryPoint bit <br>
 Bit Field Value<br>
 <table>
 <tr><th>val</th><th>Group priority field</th><th>Subpriority field</th><th>Field with binary point</th></tr>
 <tr><td>0</td><td>[7:1]</td><td>[0]</td><td>ggggggg.s</td></tr>
 <tr><td>1</td><td>[7:2]</td><td>[1:0]</td><td>gggggg.ss</td></tr>
 <tr><td>2</td><td>[7:3]</td><td>[2:0]</td><td>ggggg.sss</td></tr>
 <tr><td>3</td><td>[7:4]</td><td>[3:0]</td><td>gggg.ssss</td></tr>
 <tr><td>4</td><td>[7:5]</td><td>[4:0]</td><td>ggg.sssss</td></tr>
 <tr><td>5</td><td>[7:6]</td><td>[5:0]</td><td>gg.ssssss</td></tr>
 <tr><td>6</td><td>[7]</td><td>[6:0]</td><td>g.sssssss</td></tr>
 <tr><td>7</td><td>No preemption</td><td>[7:0]</td><td>.ssssssss</td></tr>
 </table>
 */

// Aliased Interrupt Acknowledge Register(GICC_AIAR)
#define DdGic_CPU_GET_AIAR											(IO_GIC_CPU.GICC_AIAR.word)
/**< Get GICC_AIAR Acknowledge Register */
#define DdGic_CPU_GET_AIAR_ACKINTID						(IO_GIC_CPU.GICC_AIAR.bit.ACKINTID)
/**< Get GICC_AIAR AckIntId bit */
#define DdGic_CPU_GET_AIAR_CPUID							(IO_GIC_CPU.GICC_AIAR.bit.CPUID)
/**< Get GICC_AIAR CpuId bit */

// Aliased End of Interrupt Register(GICC_AEOIR)
#define DdGic_CPU_SET_AEOIR(val)								{IO_GIC_CPU.GICC_AEOIR.word = (val);}
/**< Set GICC_AEOIR End of Interrupt Register */
#define DdGic_CPU_SET_AEOIR_EOIINTID(val)				{IO_GIC_CPU.GICC_AEOIR.bit.EOIINTID = (val);}
/**< Set GICC_AEOIR EoiIntId bit */
#define DdGic_CPU_SET_AEOIR_CPUID(val)					{IO_GIC_CPU.GICC_AEOIR.bit.CPUID = (val);}
/**< Set GICC_AEOIR CpuId bit */

// Aliased Highest Priority Pending Interrupt Register(GICC_AHPPIR)
#define DdGic_CPU_GET_AHPPIR_PENDINTID				(IO_GIC_CPU.GICC_AHPPIR.bit.PENDINTID)
/**< Get GICC_AHPPIR PendIntId */
#define DdGic_CPU_GET_AHPPIR_CPUID						(IO_GIC_CPU.GICC_AHPPIR.bit.CPUID)
/**< Get GICC_AHPPIR CpuId */

// Active Priorities Register(GICC_APR0)
#define DdGic_CPU_GET_APR0										(IO_GIC_CPU.GICC_APR0)
/**< Get GICC_APR0 Active Priorities Register */
#define DdGic_CPU_SET_APR0(val)									{IO_GIC_CPU.GICC_APR0 = (val);}
/**< Set GICC_APR0 Active Priorities Register */

// Non-secure Active Priorities Register(GICC_NSAPR0)
#define DdGic_CPU_GET_NSAPR0									(IO_GIC_CPU.GICC_NSAPR0)
/**< Get GICC_NSAPR0 Non-secure Active Priorities Register */
#define DdGic_CPU_SET_NSAPR0(val)							{IO_GIC_CPU.GICC_NSAPR0 = (val);}
/**< Set GICC_NSAPR0 Non-secure Active Priorities Register */

// CPU Interface Identification Register(GICC_IIDR)
#define DdGic_CPU_GET_IIDR_IMPLEMENTER				(IO_GIC_CPU.GICC_IIDR.bit.IMPLEMENTER)
/**< Get GICC_IIDR Implementer(0x43B:ARM implementation)<br>
 [11:8] : 0x4 The JEP106 continuation code of the implementer<br>
 [7]    : Always 0<br>
 [6:0]  : 0x3B The JEP106 identity code of the implementer<br>
 */
#define DdGic_CPU_GET_IIDR_REVISION						(IO_GIC_CPU.GICC_IIDR.bit.REVISION)
/**< Get GICC_IIDR Revision(0x1:Revision r0p1) */
#define DdGic_CPU_GET_IIDR_VERSION						(IO_GIC_CPU.GICC_IIDR.bit.VERSION)
/**< Get GICC_IIDR Architecture version(0x2:Version 2.0) */
#define DdGic_CPU_GET_IIDR_PRODUCTID					(IO_GIC_CPU.GICC_IIDR.bit.PRODUCTID)
/**< Get GICC_IIDR ProductID(0x010:Cortex-A7 MPCore product ID) */

// Deactivate Interrupt Register(GICC_DIR)
#define DdGic_CPU_SET_DIR(val)									{IO_GIC_CPU.GICC_DIR.word = (val);}
/**< Set GICC_DIR Deactivate Interrupt Register<br>
 Bit Field Value<br>
 0 to 9   : Interrupt ID<br>
 10 to 12 : CPU ID<br>
 */


typedef enum _DdGicIntid DdGicIntid;

/** Interrupt ID */
enum _DdGicIntid
{
	DdGic_INTID_SGI_INTERRUPT0	 = 0,								/**< 000 */
	DdGic_INTID_SGI_INTERRUPT1,									/**< 001 */
	DdGic_INTID_SGI_INTERRUPT2,									/**< 002 */
	DdGic_INTID_SGI_INTERRUPT3,									/**< 003 */
	DdGic_INTID_SGI_INTERRUPT4,									/**< 004 */
	DdGic_INTID_SGI_INTERRUPT5,									/**< 005 */
	DdGic_INTID_SGI_INTERRUPT6,									/**< 006 */
	DdGic_INTID_SGI_INTERRUPT7,									/**< 007 */
	DdGic_INTID_SGI_INTERRUPT8,									/**< 008 */
	DdGic_INTID_SGI_INTERRUPT9,									/**< 009 */
	DdGic_INTID_SGI_INTERRUPT10,									/**< 010 */
	DdGic_INTID_SGI_INTERRUPT11,									/**< 011 */
	DdGic_INTID_SGI_INTERRUPT12,									/**< 012 */
	DdGic_INTID_SGI_INTERRUPT13,									/**< 013 */
	DdGic_INTID_SGI_INTERRUPT14,									/**< 014 */
	DdGic_INTID_SGI_INTERRUPT15,									/**< 015 */
	DdGic_INTID_PPI_INTERRUPT0,									/**< 016 */
	DdGic_INTID_PPI_INTERRUPT1,									/**< 017 */
	DdGic_INTID_PPI_INTERRUPT2,									/**< 018 */
	DdGic_INTID_PPI_INTERRUPT3,									/**< 019 */
	DdGic_INTID_PPI_INTERRUPT4,									/**< 020 */
	DdGic_INTID_PPI_INTERRUPT5,									/**< 021 */
	DdGic_INTID_PPI_INTERRUPT6,									/**< 022 */
	DdGic_INTID_PPI_INTERRUPT7,									/**< 023 */
	DdGic_INTID_PPI_INTERRUPT8,									/**< 024 */
	DdGic_INTID_PPI_INTERRUPT9,									/**< 025 */
	DdGic_INTID_PPI_INTERRUPT10,									/**< 026 */
	DdGic_INTID_PPI_INTERRUPT11,									/**< 027 */
	DdGic_INTID_PPI_INTERRUPT12,									/**< 028 */
	DdGic_INTID_PPI_INTERRUPT13,									/**< 029 */
	DdGic_INTID_PPI_INTERRUPT14,									/**< 030 */
	DdGic_INTID_PPI_INTERRUPT15,									/**< 031 */
	DdGic_INTID_CORTEXA7_CPU0_COMMUNICATION_CH_RECEIVE_INT,		/**< 032 */
	DdGic_INTID_CORTEXA7_CPU0_COMMUNICATION_TRNSMIT_CH_INT,		/**< 033 */
	DdGic_INTID_CORTEXA7_CPU1_COMMUNICATION_CH_RECEIVE_INT,		/**< 034 */
	DdGic_INTID_CORTEXA7_CPU1_COMMUNICATION_TRNSMIT_CH_INT,		/**< 035 */
	DdGic_INTID_CORTEXA7_CPU2_COMMUNICATION_CH_RECEIVE_INT,		/**< 036 */
	DdGic_INTID_CORTEXA7_CPU2_COMMUNICATION_TRNSMIT_CH_INT,		/**< 037 */
	DdGic_INTID_CORTEXA7_CPU3_COMMUNICATION_CH_RECEIVE_INT,		/**< 038 */
	DdGic_INTID_CORTEXA7_CPU3_COMMUNICATION_TRNSMIT_CH_INT,		/**< 039 */
	DdGic_INTID_CORTEXA7_CPU0_CROSSTRIGGER_INT,				/**< 040 */
	DdGic_INTID_CORTEXA7_CPU1_CROSSTRIGGER_INT,				/**< 041 */
	DdGic_INTID_CORTEXA7_CPU2_CROSSTRIGGER_INT,				/**< 042 */
	DdGic_INTID_CORTEXA7_CPU3_CROSSTRIGGER_INT,				/**< 043 */
	DdGic_INTID_CORTEXA7_CPU0_SYSTEM_MATRICS_INT,			/**< 044 */
	DdGic_INTID_CORTEXA7_CPU1_SYSTEM_MATRICS_INT,			/**< 045 */
	DdGic_INTID_CORTEXA7_CPU2_SYSTEM_MATRICS_INT,			/**< 046 */
	DdGic_INTID_CORTEXA7_CPU3_SYSTEM_MATRICS_INT,			/**< 047 */
	DdGic_INTID_AXI_TRANSACTION_ERROR_INT,						/**< 048 */
	DdGic_INTID_SNAP_PERI_XDMAC_CH0_INT,							/**< 049 */
	DdGic_INTID_SNAP_PERI_XDMAC_CH1_INT,							/**< 050 */
	DdGic_INTID_SNAP_PERI_XDMAC_CH2_INT,							/**< 051 */
	DdGic_INTID_SNAP_PERI_XDMAC_CH3_INT,							/**< 052 */
	DdGic_INTID_WATCHDOG_TIMER_INT,						/**< 053 */
	DdGic_INTID_IPCU0_CH0_INT,									/**< 054 */
	DdGic_INTID_IPCU0_CH1_INT,									/**< 055 */
	DdGic_INTID_IPCU0_CH2_INT,									/**< 056 */
	DdGic_INTID_IPCU0_CH3_INT,									/**< 057 */
	DdGic_INTID_IPCU0_CH4_INT,									/**< 058 */
	DdGic_INTID_IPCU0_CH5_INT,									/**< 059 */
	DdGic_INTID_IPCU0_CH6_INT,									/**< 060 */
	DdGic_INTID_IPCU0_CH7_INT,									/**< 061 */
	DdGic_INTID_IPCU0_CH8_INT,									/**< 062 */
	DdGic_INTID_IPCU0_CH9_INT,									/**< 063 */
	DdGic_INTID_IPCU0_CH10_INT,								/**< 064 */
	DdGic_INTID_IPCU0_CH11_INT,								/**< 065 */
	DdGic_INTID_IPCU0_CH12_INT,								/**< 066 */
	DdGic_INTID_IPCU0_CH13_INT,								/**< 067 */
	DdGic_INTID_IPCU0_CH14_INT,								/**< 068 */
	DdGic_INTID_IPCU0_CH15_INT,								/**< 069 */
	DdGic_INTID_IPCU1_CH0_INT,									/**< 070 */
	DdGic_INTID_IPCU1_CH1_INT,									/**< 071 */
	DdGic_INTID_IPCU1_CH2_INT,									/**< 072 */
	DdGic_INTID_IPCU1_CH3_INT,									/**< 073 */
	DdGic_INTID_IPCU1_CH4_INT,									/**< 074 */
	DdGic_INTID_IPCU1_CH5_INT,									/**< 075 */
	DdGic_INTID_IPCU1_CH6_INT,									/**< 076 */
	DdGic_INTID_IPCU1_CH7_INT,									/**< 077 */
	DdGic_INTID_IPCU1_CH8_INT,									/**< 078 */
	DdGic_INTID_IPCU1_CH9_INT,									/**< 079 */
	DdGic_INTID_IPCU1_CH10_INT,								/**< 080 */
	DdGic_INTID_IPCU1_CH11_INT,								/**< 081 */
	DdGic_INTID_IPCU1_CH12_INT,								/**< 082 */
	DdGic_INTID_IPCU1_CH13_INT,								/**< 083 */
	DdGic_INTID_IPCU1_CH14_INT,								/**< 084 */
	DdGic_INTID_IPCU1_CH15_INT,								/**< 085 */
	DdGic_INTID_EXTERNAL_CH16_INT,							/**< 086 */
	DdGic_INTID_EXTERNAL_CH17_INT,							/**< 087 */
	DdGic_INTID_EXTERNAL_CH18_INT,							/**< 088 */
	DdGic_INTID_EXTERNAL_CH19_INT,							/**< 089 */
	DdGic_INTID_EXTERNAL_CH20_INT,							/**< 090 */
	DdGic_INTID_EXTERNAL_CH21_INT,							/**< 091 */
	DdGic_INTID_EXTERNAL_CH22_INT,							/**< 092 */
	DdGic_INTID_EXTERNAL_CH23_INT,							/**< 093 */
	DdGic_INTID_EXTERNAL_CH24_INT,							/**< 094 */
	DdGic_INTID_EXTERNAL_CH25_INT,							/**< 095 */
	DdGic_INTID_EXTERNAL_CH26_INT,							/**< 096 */
	DdGic_INTID_EXTERNAL_CH27_INT,							/**< 097 */
	DdGic_INTID_EXTERNAL_CH28_INT,							/**< 098 */
	DdGic_INTID_EXTERNAL_CH29_INT,							/**< 099 */
	DdGic_INTID_EXTERNAL_CH30_INT,							/**< 100 */
	DdGic_INTID_EXTERNAL_CH31_INT,							/**< 101 */
	DdGic_INTID_PMC_DMAC_ADC_INT,							/**< 102 */
	DdGic_INTID_PMC_DMAC_RECEIVE_INT,					/**< 103 */
	DdGic_INTID_PMC_UART_TRANSMISSION_DATA_INT,			/**< 104 */
	DdGic_INTID_PMC_DMAC_QSPI_TRANSMISSION_INT,			/**< 105 */
	DdGic_INTID_PMC_DMAC_QSPI_RECEIVE_INT,						/**< 106 */
	DdGic_INTID_PMC_UART_RECEIVE_RELATION_INT,					/**< 107 */
	DdGic_INTID_PMC_UART_TRANSMISSION_RELATION_INT,	/**< 108 */
	DdGic_INTID_PMC_QSPI_INT,													/**< 109 */
	DdGic_INTID_CALENDER_ALARM_INT,										/**< 110 */
	DdGic_INTID_PMC_32BIT_TIMER_UNDER_FLOW_INT,				/**< 111 */
	DdGic_INTID_ADC_INT,												/**< 112 */
	DdGic_INTID_PMC_I2C_INT,										/**< 113 */
	DdGic_INTID_PMC_WATCHDOG_INT,						/**< 114 */
	DdGic_INTID_TEMPERATURE_INT,							/**< 115 */
	DdGic_INTID_PMU_INT,												/**< 116 */
	DdGic_INTID_PMC_GPIO_INT,									/**< 117 */
	DdGic_INTID_TIMER_CH0_INT,									/**< 118 */
	DdGic_INTID_TIMER_CH1_INT,									/**< 119 */
	DdGic_INTID_TIMER_CH2_INT,									/**< 120 */
	DdGic_INTID_TIMER_CH3_INT,									/**< 121 */
	DdGic_INTID_TIMER_CH4_INT,									/**< 122 */
	DdGic_INTID_TIMER_CH5_INT,									/**< 123 */
	DdGic_INTID_TIMER_CH6_INT,									/**< 124 */
	DdGic_INTID_TIMER_CH7_INT,									/**< 125 */
	DdGic_INTID_TIMER_CH8_INT,									/**< 126 */
	DdGic_INTID_TIMER_CH9_INT,									/**< 127 */
	DdGic_INTID_TIMER_CH10_INT,								/**< 128 */
	DdGic_INTID_TIMER_CH11_INT,								/**< 129 */
	DdGic_INTID_TIMER_CH12_INT,								/**< 130 */
	DdGic_INTID_TIMER_CH13_INT,								/**< 131 */
	DdGic_INTID_NULL132,												/**< 132 */
	DdGic_INTID_I2C_CH0_INT,										/**< 133 */
	DdGic_INTID_I2C_CH1_INT,										/**< 134 */
	DdGic_INTID_I2C_CH2_INT,										/**< 135 */
	DdGic_INTID_UPDOWN_COUNTER_CH0_INT,			/**< 136 */
	DdGic_INTID_UPDOWN_COUNTER_CH1_INT,			/**< 137 */
	DdGic_INTID_UPDOWN_COUNTER_CH2_INT,			/**< 138 */
	DdGic_INTID_UPDOWN_COUNTER_CH3_INT,			/**< 139 */
	DdGic_INTID_UPDOWN_COUNTER_CH4_INT,			/**< 140 */
	DdGic_INTID_UPDOWN_COUNTER_CH5_INT,			/**< 141 */
	DdGic_INTID_PWM_CH0_CH3_INT,							/**< 142 */
	DdGic_INTID_PWM_CH4_CH7_INT,							/**< 143 */
	DdGic_INTID_PWM_CH8_CH11_INT,							/**< 144 */
	DdGic_INTID_PWM_CH12_CH15_INT,						/**< 145 */
	DdGic_INTID_PWM_CH0_CH3_STP_INT,					/**< 146 */
	DdGic_INTID_PWM_CH4_CH7_STP_INT,					/**< 147 */
	DdGic_INTID_PWM_CH8_CH11_STP_INT,					/**< 148 */
	DdGic_INTID_PWM_CH12_CH15_STP_INT,				/**< 149 */
	DdGic_INTID_AUDIO_IF_CH0_INT,							/**< 150 */
	DdGic_INTID_AUDIO_IF_CH1_INT,							/**< 151 */
	DdGic_INTID_AUDIO_IF_CH2_INT,							/**< 152 */
	DdGic_INTID_AUDIO_IF_CH3_INT,							/**< 153 */
	DdGic_INTID_AUDIO_IF_CH4_INT,							/**< 154 */
	DdGic_INTID_AUDIO_IF_CH5_INT,							/**< 155 */
	DdGic_INTID_HDMAC0_CH0_INT,								/**< 156 */
	DdGic_INTID_HDMAC0_CH1_INT,								/**< 157 */
	DdGic_INTID_HDMAC0_CH2_INT,								/**< 158 */
	DdGic_INTID_HDMAC0_CH3_INT,								/**< 159 */
	DdGic_INTID_HDMAC0_CH4_INT,								/**< 160 */
	DdGic_INTID_HDMAC0_CH5_INT,								/**< 161 */
	DdGic_INTID_HDMAC0_CH6_INT,								/**< 162 */
	DdGic_INTID_HDMAC0_CH7_INT,								/**< 163 */
	DdGic_INTID_HDMAC1_CH0_INT,								/**< 164 */
	DdGic_INTID_HDMAC1_CH1_INT,								/**< 165 */
	DdGic_INTID_HDMAC1_CH2_INT,								/**< 166 */
	DdGic_INTID_HDMAC1_CH3_INT,								/**< 167 */
	DdGic_INTID_HDMAC1_CH4_INT,								/**< 168 */
	DdGic_INTID_HDMAC1_CH5_INT,								/**< 169 */
	DdGic_INTID_HDMAC1_CH6_INT,								/**< 170 */
	DdGic_INTID_HDMAC1_CH7_INT,								/**< 171 */
	DdGic_INTID_UART_CH0_RECEPTION_INT,				/**< 172 */
	DdGic_INTID_UART_CH1_RECEPTION_INT,				/**< 173 */
	DdGic_INTID_UART_CH2_RECEPTION_INT,				/**< 174 */
	DdGic_INTID_UART_CH3_RECEPTION_INT,				/**< 175 */
	DdGic_INTID_UART_CH4_RECEPTION_INT,				/**< 176 */
	DdGic_INTID_UART_CH5_RECEPTION_INT,				/**< 177 */
	DdGic_INTID_UART_CH6_RECEPTION_INT,				/**< 178 */
	DdGic_INTID_UART_CH7_RECEPTION_INT,				/**< 179 */
	DdGic_INTID_UART_CH0_TRANSMISSION_INT,		/**< 180 */
	DdGic_INTID_UART_CH1_TRANSMISSION_INT,		/**< 181 */
	DdGic_INTID_UART_CH2_TRANSMISSION_INT,		/**< 182 */
	DdGic_INTID_UART_CH3_TRANSMISSION_INT,		/**< 183 */
	DdGic_INTID_UART_CH4_TRANSMISSION_INT,		/**< 184 */
	DdGic_INTID_UART_CH5_TRANSMISSION_INT,		/**< 185 */
	DdGic_INTID_UART_CH6_TRANSMISSION_INT,		/**< 186 */
	DdGic_INTID_UART_CH7_TRANSMISSION_INT,		/**< 187 */
	DdGic_INTID_SPI_CH0_INT,										/**< 188 */
	DdGic_INTID_SPI_CH1_INT,										/**< 189 */
	DdGic_INTID_SPI_CH2_INT,										/**< 190 */
	DdGic_INTID_PDM_CH0_DMA0_INT,							/**< 191 */
	DdGic_INTID_PDM_CH0_DMA1_INT,							/**< 192 */
	DdGic_INTID_PDM_CH0_FIFO_OVERFLOW_INT,		/**< 193 */
	DdGic_INTID_PDM_CH1_DMA0_INT,							/**< 194 */
	DdGic_INTID_PDM_CH1_DMA1_INT,							/**< 195 */
	DdGic_INTID_PDM_CH1_FIFO_OVERFLOW_INT,		/**< 196 */
	DdGic_INTID_SLIMBUS_CH0_INT,								/**< 197 */
	DdGic_INTID_SLIMBUS_CH1_INT,								/**< 198 */
	DdGic_INTID_SLIMBUS_CH2_INT,								/**< 199 */
	DdGic_INTID_SLIMBUS_CH3_INT,								/**< 200 */
	DdGic_INTID_SDRAMC_CH0_INT,								/**< 201 */
	DdGic_INTID_SDRAMC_CH1_INT,								/**< 202 */
	DdGic_INTID_MXIC_UNIT0_INT,								/**< 203 */
	DdGic_INTID_MXIC_UNIT1_INT,								/**< 204 */
	DdGic_INTID_MXIC_UNIT2_INT,								/**< 205 */
	DdGic_INTID_MXIC_UNIT3_INT,								/**< 206 */
	DdGic_INTID_MXIC_UNIT4_INT,								/**< 207 */
	DdGic_INTID_MXIC_UNIT5_INT,								/**< 208 */
	DdGic_INTID_MXIC_UNIT6_INT,								/**< 209 */
	DdGic_INTID_SEN_INT,												/**< 210 */
	DdGic_INTID_SEN_VD_INT,										/**< 211 */
	DdGic_INTID_SEN_HD_INT,										/**< 212 */
	DdGic_INTID_SENSOR_IF_MACRO0_INT,					/**< 213 */
	DdGic_INTID_SENSOR_IF_MACRO1_INT,					/**< 214 */
	DdGic_INTID_SENSOR_IF_MACRO2_INT,					/**< 215 */
	DdGic_INTID_SENSOR_IF_MACRO3_INT,					/**< 216 */
	DdGic_INTID_SRO_UNIT1_INT,									/**< 217 */
	DdGic_INTID_SRO_UNIT1_VD_INT,							/**< 218 */
	DdGic_INTID_SRO_UNIT1_HD_INT,							/**< 219 */
	DdGic_INTID_SRO_UNIT2_INT,									/**< 220 */
	DdGic_INTID_SRO_UNIT2_VD_INT,							/**< 221 */
	DdGic_INTID_SRO_UNIT2_HD_INT,							/**< 222 */
	DdGic_INTID_B2B_UNIT1_INT,									/**< 223 */
	DdGic_INTID_B2B_UNIT1_VD_INT,							/**< 224 */
	DdGic_INTID_B2B_UNIT1_HD_INT,							/**< 225 */
	DdGic_INTID_B2B_UNIT2_INT,									/**< 226 */
	DdGic_INTID_B2B_UNIT2_VD_INT,							/**< 227 */
	DdGic_INTID_B2B_UNIT2_HD_INT,							/**< 228 */
	DdGic_INTID_START_INT,											/**< 229 */
	DdGic_INTID_PAS_UNIT2_INT,									/**< 230 */
	DdGic_INTID_PAS_UNIT2_VD_INT,							/**< 231 */
	DdGic_INTID_PAS_UNIT2_HD_INT,							/**< 232 */
	DdGic_INTID_B2R_UNIT1_INT,									/**< 233 */
	DdGic_INTID_B2R_UNIT2_INT,									/**< 234 */
	DdGic_INTID_LTM_UNIT1_INT,									/**< 235 */
	DdGic_INTID_LTM_UNIT2_INT,									/**< 236 */
	DdGic_INTID_R2Y_UNIT1_INT,									/**< 237 */
	DdGic_INTID_R2Y_UNIT2_INT,									/**< 238 */
	DdGic_INTID_CNR_UNIT1_INT,									/**< 239 */
	DdGic_INTID_CNR_UNIT2_INT,									/**< 240 */
	DdGic_INTID_IIP_INT,												/**< 241 */
	DdGic_INTID_SHDR_INT,											/**< 242 */
	DdGic_INTID_SHDR_LINE_INT,									/**< 243 */
	DdGic_INTID_ME_INT,												/**< 244 */
	DdGic_INTID_GRAPHICS_INT,									/**< 245 */
	DdGic_INTID_JPEG_INT,												/**< 246 */
	DdGic_INTID_RAW_INT,												/**< 247 */
	DdGic_INTID_IPU_INT,												/**< 248 */
	DdGic_INTID_ELA_UNIT_INT,									/**< 249 */
	DdGic_INTID_XCH_INT,												/**< 250 */
	DdGic_INTID_FPT_UNIT0_INT,									/**< 251 */
	DdGic_INTID_FPT_UNIT1_INT,									/**< 252 */
	DdGic_INTID_DISP_LCD_INT,									/**< 253 */
	DdGic_INTID_DISP_HDMI_INT,									/**< 254 */
	DdGic_INTID_DISP_MIPI_DSI_INT,							/**< 255 */
	DdGic_INTID_MIPI_DSI_Tx_INT,								/**< 256 */
	DdGic_INTID_DISP_DWCH_INT,								/**< 257 */
	DdGic_INTID_RDMA_INT,											/**< 258 */
	DdGic_INTID_HDMI_MASTER_INT,							/**< 259 */
	DdGic_INTID_HDMI_CEC_INT,									/**< 260 */
	DdGic_INTID_BMH_UNIT0_INT,								/**< 261 */
	DdGic_INTID_BMH_UNIT1_INT,								/**< 262 */
	DdGic_INTID_RIBERY_RBR_INT,								/**< 263 */
	DdGic_INTID_RIBERY_RWDT_INT,								/**< 264 */
	DdGic_INTID_INTERPROCESSOR0_INT,					/**< 265 */
	DdGic_INTID_INTERPROCESSOR1_INT,					/**< 266 */
	DdGic_INTID_INTERPROCESSOR2_INT,					/**< 267 */
	DdGic_INTID_INTERPROCESSOR3_INT,					/**< 268 */
	DdGic_INTID_DSP_PERIPHERAL_UNIT_IPCU0_INT,	/**< 269 */
	DdGic_INTID_DSP_PERIPHERAL_UNIT_IPCU1_INT,	/**< 270 */
	DdGic_INTID_DSP_PERIPHERAL_UNIT_IPCU2_INT,	/**< 271 */
	DdGic_INTID_DSP_PERIPHERAL_UNIT_IPCU3_INT,	/**< 272 */
	DdGic_INTID_DSP_DEBUG_INT,								/**< 273 */
	DdGic_INTID_NANDFLASH_INT,								/**< 274 */
	DdGic_INTID_PCIE_CH0_MSI_INT,								/**< 275 */
	DdGic_INTID_PCIE_CH0_SYSTEM_ERROR_INT,			/**< 276 */
	DdGic_INTID_PCIE_CH0_INTX_INT,							/**< 277 */
	DdGic_INTID_PCIE_CH0_CORE_INT,							/**< 278 */
	DdGic_INTID_PCIE_CH0_DMA_INT,							/**< 279 */
	DdGic_INTID_PCIE_CH1_MSI_INT,								/**< 280 */
	DdGic_INTID_PCIE_CH1_SYSTEM_ERROR_INT,			/**< 281 */
	DdGic_INTID_PCIE_CH1_INTX_INT,							/**< 282 */
	DdGic_INTID_PCIE_CH1_CORE_INT,							/**< 283 */
	DdGic_INTID_PCIE_CH1_DMA_INT,							/**< 284 */
	DdGic_INTID_EXS_XDMAC_CH0_INT,						/**< 285 */
	DdGic_INTID_EXS_XDMAC_CH1_INT,						/**< 286 */
	DdGic_INTID_EXS_XDMAC_CH2_INT,						/**< 287 */
	DdGic_INTID_EXS_XDMAC_CH3_INT,						/**< 288 */
	DdGic_INTID_EXS_HDMAC_CH0_INT,						/**< 289 */
	DdGic_INTID_EXS_HDMAC_CH1_INT,						/**< 290 */
	DdGic_INTID_EXS_HDMAC_CH2_INT,						/**< 291 */
	DdGic_INTID_EXS_HDMAC_CH3_INT,						/**< 292 */
	DdGic_INTID_USB20_HDC_INT,									/**< 293 */
	DdGic_INTID_USB20_HOST_EHCI_INT,						/**< 294 */
	DdGic_INTID_USB20_HOST_OHCI_INT,					/**< 295 */
	DdGic_INTID_USB30_INT,											/**< 296 */
	DdGic_INTID_SD_CH3_INT,										/**< 297 */
	DdGic_INTID_SD_CH3_SDIO_INT,								/**< 298 */
	DdGic_INTID_SD_CH3_WAKEUP_INT,						/**< 299 */
	DdGic_INTID_SD_CH2_UHS1_INT,								/**< 300 */
	DdGic_INTID_SD_CH2_SDIO_INT,								/**< 301 */
	DdGic_INTID_SD_CH2_UHS1_WAKEUP_INT,				/**< 302 */
	DdGic_INTID_SD_CH2_UHS2_INT,								/**< 303 */
	DdGic_INTID_SD_CH2_UHS2_WAKEUP_INT,				/**< 304 */
	DdGic_INTID_SD_CH1_INT,										/**< 305 */
	DdGic_INTID_SD_CH1_SDIO_INT,								/**< 306 */
	DdGic_INTID_SD_CH1_WAKEUP_INT,						/**< 307 */
	DdGic_INTID_EMMC_INT,											/**< 308 */
	DdGic_INTID_EMMC_WAKEUP_INT,							/**< 309 */
	DdGic_INTID_RELC_INT,											/**< 310 */
	DdGic_INTID_NETSEC_A_INT,									/**< 311 */
	DdGic_INTID_NETSEC_B_INT,									/**< 312 */
	DdGic_INTID_SD_PCIE_DETECT_INT,						/**< 313 */
	DdGic_INTID_NULL314,												/**< 314 */
	DdGic_INTID_NULL315,												/**< 315 */
	DdGic_INTID_NULL316,												/**< 316 */
	DdGic_INTID_NULL317,												/**< 317 */
	DdGic_INTID_NULL318,												/**< 318 */
	DdGic_INTID_NULL319												/**< 319 */
};


typedef struct _DdGic DdGic;
typedef struct _DdGicPrivate DdGicPrivate;

struct _DdGic
{
	KObject parent;
};


KConstType	dd_gic_get_type(void);
DdGic*		dd_gic_new(void);
/**
Initialize Generic Interrupt Controller.
*/
void			dd_gic_init1(DdGic *self);

/**
Initialize Distributor Bank Register.
*/
void			dd_gic_dist_bank_init(DdGic *self);

/**
Initialize CPU Interface Control Register.
*/
void			dd_gic_cpu_init(DdGic *self);

/**
 End Generic Interrupt Controller.
 */
void			dd_gic_end(DdGic *self);

/**
 Control Generic Interrupt Controller to set resource.
 @param [in]	intid					: Interrupt ID (0 to @ref C_INTID_SPI_MAX).
 @param [in]	setEnable				: Interrupt Set-Enable Value.
 <ul>
 <li>0:disable
 <li>1:enable
 </ul>
 @param [in]	intrptPri				: Interrupt Priority Value (-1 to 248).
 <ul>
 <li>0, 8, 16, 24, ..., 248 (in steps of 8):priority
 <li>-1:Not set
 </ul>
 @param [in]	cpuTarget				: Interrupt Processor Target (-1 to 15).
 <ul>
 <li>bit0:CPU0
 <li>bit1:CPU1
 <li>bit2:CPU2
 <li>bit3:CPU3
 <li>-1:No target
 </ul>
 @retval	D_DDIM_OK					: Normal end
 @retval	C_GIC_INPUT_PARAM_ERR	: Input Parameter Error
 @remarks	Disable interrupt is set after this function. If start, dd_gic_init1(NULL) should be used.
 */
kint32			dd_gic_ctrl(DdGic *self, DdGicIntid intid, kulong setEnable, kint64 intrptPri, kint64 cpuTarget);

/**
 Control Set Interrupt Priority Registers.
 @param [in]	intid					: Interrupt ID (0 to @ref C_INTID_SPI_MAX).
 @param [in]	intrptPri				: Interrupt Priority Value (-1 to 248).
 <ul>
 <li>0, 8, 16, 24, ..., 248 (in steps of 8):priority
 <li>-1:Not set
 </ul>
 @retval	D_DDIM_OK					: Normal end
 @retval	C_GIC_INPUT_PARAM_ERR	: Input Parameter Error
 @remarks	Disable interrupt is set after this function. If start, dd_gic_init1(NULL) should be used.
 */
kint32			dd_gic_set_priority(DdGic *self, DdGicIntid intid, kint64 intrptPri);

/**
 Control Set Interrupt Processor Targets Registers.
 @param [in]	intid					: Interrupt ID (0 to @ref C_INTID_SPI_MAX).
 @param [in]	cpuTarget				: Interrupt Processor Target (-1 to 15).
 <ul>
 <li>bit0:CPU0
 <li>bit1:CPU1
 <li>bit2:CPU2
 <li>bit3:CPU3
 <li>-1:No target
 </ul>
 @retval	D_DDIM_OK					: Normal end
 @retval	C_GIC_INPUT_PARAM_ERR	: Input Parameter Error
 @remarks	Disable interrupt is set after this function. If start, dd_gic_init1(NULL) should be used.
 */
kint32			dd_gic_set_target_cpu(DdGic *self, DdGicIntid intid, kint64 cpuTarget);

/**
 SGI(Software Generated Interrupt) send to target CPU.<br>
 Set Interrupt Software Generated Interrupt Register(ICDSGIR).
 @param [in]	intid					: Software Generated Interrupt ID (0 to @ref C_INTID_SGI_MAX).
 @param [in]	targetFilter			: Target List Filter (0 to 2).
 <ul>
 <li>0:Send the interrupt to the CPU interfaces specified in the CPUTargetList(cpuTarget value).
 <li>1:Send the interrupt to all CPU interfaces except the CPU interface that requested the interrupt.
 <li>2:Send the interrupt only to the CPU interface that requested the interrupt.
 </ul>
 @param [in]	cpuTarget				: CPU Target (0 to 15).
 <ul>
 <li>0:No target (targetFilter value 1 or 2)
 <li>1:CPU0 ([0]bit ON)
 <li>2:CPU1 ([1]bit ON)
 <li>4:CPU2 ([2]bit ON)
 <li>8:CPU3 ([3]bit ON)
 <li>15:All CPU
 </ul>
 @retval	D_DDIM_OK					: Normal end
 @retval	C_GIC_INPUT_PARAM_ERR	: Input Parameter Error
 @remarks	When this API call, send the interrupt to target CPU.
 */
kint32			dd_gic_send_sgi(DdGic *self, DdGicIntid intid, kulong targetFilter, kulong cpuTarget);

/*@}*/

/**
 @weakgroup dd_gic
 @{
 @section dd_gic_sample_section1		Sample of "operating procedure for generic interrupt start
 (CPU0)" using dd_gic_init1 function.
 @code
 __align(64) kulong gic_spin_lock;		// Necessarily 64 Byte Align & Cachable Area

 Dd_ARM_Spin_Lock(&gic_spin_lock);

 dd_gic_init1(NULL);							// Initialize(All GIC Register)

 Dd_ARM_Spin_Unlock(&gic_spin_lock);
 @endcode
 <br>
 @section dd_gic_sample_section2		Sample of "operating procedure for generic interrupt
 start(CPU1)" using dd_gic_dist_bank_init function.
 @code
 __align(64) kulong gic_spin_lock;		// Necessarily 64 Byte Align & Cachable Area

 Dd_ARM_Spin_Lock(&gic_spin_lock);

 dd_gic_dist_bank_init(NULL);				// Initialize(Bank Register only)

 Dd_ARM_Spin_Unlock(&gic_spin_lock);
 @endcode
 <br>
 @section dd_gic_sample_section3		Sample of "operating procedure for generic interrupt
  Control" using dd_gic_ctrl function.
 @code
 __align(64) kulong gic_spin_lock;		// Necessarily 64 Byte Align & Cachable Area

 Dd_ARM_Spin_Lock(&gic_spin_lock);

 dd_gic_ctrl(NULL, intid, setEnable, intrptPri, 0);

 Dd_ARM_Spin_Unlock(&gic_spin_lock);
 @endcode
 <br>
 @section dd_gic_sample_section4		Sample of "operating procedure for generic interrupt Stop" using
 dd_gic_end function.
 @code
 __align(64) kulong gic_spin_lock;		// Necessarily 64 Byte Align & Cachable Area

 Dd_ARM_Spin_Lock(&gic_spin_lock);

 dd_gic_end(NULL);

 Dd_ARM_Spin_Unlock(&gic_spin_lock);
 @endcode
 @}*/

#ifdef __cplusplus
}
#endif

#endif /* __DD_GIC_H__ */
