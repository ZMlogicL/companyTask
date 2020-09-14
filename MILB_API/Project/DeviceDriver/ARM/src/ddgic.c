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
 * @file		dd_gic.c
 * @brief		GIC (Generic Interrupt Controller) driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#include "ddgic.h"
#include "ddarm.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdGic, dd_gic);

#define DD_GIC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdGicPrivate, DD_TYPE_GIC))


struct _DdGicPrivate
{

};

/**
DECLS
*/
/**
IMPL
*/
static void dd_gic_constructor(DdGic *self)
{
//	DdGicPrivate *priv = DD_GIC_GET_PRIVATE(self);
}

static void dd_gic_destructor(DdGic *self)
{
//	DdGicPrivate *priv = DD_GIC_GET_PRIVATE(self);
}
/**
PUBLIC
*/
/**
 * @brief	Initialize Generic Interrupt Controller.
 */
void dd_gic_init1(DdGic *self)
{
	kuint16 i;
	
	//----------------------------------------------------------------------
	// Distributor side Disable
	// Distributor Control Register (GICD_CTLR)
	//----------------------------------------------------------------------
	DdGic_DIST_DIST_SET_CTLR_ENABLEGRP0(0x0);
	DdGic_DIST_SET_CTLR_ENABLEGRP1(0x0);
	
	//----------------------------------------------------------------------
	// Distributor Bank Register Initialize
	//----------------------------------------------------------------------
	dd_gic_dist_bank_init(NULL);
	
	//----------------------------------------------------------------------
	// Disable Interrupt
	// Interrupt Clear-Enable Register (GICD_ICENABLER)
	//----------------------------------------------------------------------
	// SGIs are always enabled.
	for (i = 1; i < (C_INTID_MAX / 32); i++) {
		DdGic_DIST_SET_ICENABLER(i, 0xFFFFFFFF);
	}
	
	//----------------------------------------------------------------------
	// Clear Interrupt Pending
	// Interrupt Clear-Pending Register (GICD_ICPENDR)
	//----------------------------------------------------------------------
	// SGIs are always enabled.
	for (i = 1; i < (C_INTID_MAX / 32); i++) {
		DdGic_DIST_SET_ICPENDR(i, 0xFFFFFFFF);
	}
	
	//----------------------------------------------------------------------
	// Clear Interupt Priority
	// Interrupt Priority Register (GICD_IPRIORITYR)
	//----------------------------------------------------------------------
	for (i = 32; i < C_INTID_MAX; i++) {
		DdGic_DIST_SET_IPRIORITYR(i, 0x0);
	}
	
	//----------------------------------------------------------------------
	// Clear Target CPU
	// Interrupt Processor Targets Register (GICD_ITARGETSR)
	//----------------------------------------------------------------------
	// The Distributor does not provide registers for INTIDs < 32.(SGI and PPI)
	for (i = 32; i < C_INTID_MAX; i++) {
		DdGic_DIST_SET_ITARGETSR(i, 0x0);
	}
	
	//----------------------------------------------------------------------
	// "Level-sensitive" or "Edge-triggered"
	// Interrupt Configuration Register (GICD_ICFGR)
	//----------------------------------------------------------------------
	// SGIs are always pulse-sensitive
	// PPIs are configured during the GIC configuration process
	for (i = 1; i < (C_INTID_MAX / 16); i++) {
		DdGic_DIST_SET_ICFGR(i, 0x55555555);
	}
	
	//----------------------------------------------------------------------
	// CPU Interface Control Register Initialize
	//----------------------------------------------------------------------
	dd_gic_cpu_init(NULL);
	
	//----------------------------------------------------------------------
	// Distributor side Enable
	// Distributor Control Register (GICD_CTLR)
	//----------------------------------------------------------------------
	DdGic_DIST_DIST_SET_CTLR_ENABLEGRP0(0x1);
	DdGic_DIST_SET_CTLR_ENABLEGRP1(0x0);

	DD_ARM_DSB_POU();
}

/**
 * @brief	Initialize Distributor Bank Register.
 */
void dd_gic_dist_bank_init(DdGic *self)
{
	kuint16 i;
	
	//----------------------------------------------------------------------
	// Disable Interrupt
	// Interrupt Clear-Enable Register (GICD_ICENABLER)
	//----------------------------------------------------------------------
	// SGIs are always enabled.
	DdGic_DIST_SET_ICENABLER(0, 0xFFFFFFFF);
	
	//----------------------------------------------------------------------
	// Clear Interrupt Pending
	// Interrupt Clear-Pending Register (GICD_ICPENDR)
	//----------------------------------------------------------------------
	// SGIs are always enabled.
	DdGic_DIST_SET_ICPENDR(0, 0xFFFFFFFF);
	
	//----------------------------------------------------------------------
	// Clear Interrupt Priority
	// Interrupt Priority Register (GICD_IPRIORITYR)
	//----------------------------------------------------------------------
	for (i = 0; i < 32; i++) {
		DdGic_DIST_SET_IPRIORITYR(i, 0x0);
	}
	
	DD_ARM_DSB_POU();
}

/**
 * @brief	Initialize CPU Interface Control Register.
 */
void dd_gic_cpu_init(DdGic *self)
{
	//----------------------------------------------------------------------
	// CPU I/F side Disable
	// CPU Interface Control Register (GICC_CTLR)
	//----------------------------------------------------------------------
	DdGic_CPU_SET_CTLR_ENABLEGRP0(0x0);
	DdGic_CPU_SET_CTLR_ENABLEGRP1(0x0);
	
	//----------------------------------------------------------------------
	// Set Priority Mask
	// Interrupt Priority Mask Register (GICC_PMR)
	//----------------------------------------------------------------------
	DdGic_CPU_SET_PMR_PRIORITY(0xF8);
	
	//----------------------------------------------------------------------
	// Set Binary point
	// Binary Point Register (GICC_BPR)
	//----------------------------------------------------------------------
	DdGic_CPU_SET_BPR_BINARYPOINT(0x2);
	
	//----------------------------------------------------------------------
	// When Exist Interrupt Acknowledge Register
	// Set End of Interrupt Register
	//----------------------------------------------------------------------
	do {
		kuint32 temp;

		temp = DdGic_CPU_GET_IAR;
		if ((temp & C_INTERRUPT_MASK) == C_SPURIOUS_INTERRUPT) {
			break;
		}
		DdGic_CPU_SET_AEOIR(temp);
	} while (1);
	
	//----------------------------------------------------------------------
	// CPU I/F side Enable
	// CPU Interface Control Register (GICC_CTLR)
	//----------------------------------------------------------------------
	DdGic_CPU_SET_CTLR_ENABLEGRP0(0x1);
	DdGic_CPU_SET_CTLR_ENABLEGRP1(0x0);

	DD_ARM_DSB_POU();
}

/**
 * @brief	End Generic Interrupt Controller.
 */
void dd_gic_end(DdGic *self)
{
	//----------------------------------------------------------------------
	// CPU I/F side
	// CPU Interface Control Register (GICC_CTLR)
	//----------------------------------------------------------------------
	DdGic_CPU_SET_CTLR_ENABLEGRP0(0x0);
	DdGic_CPU_SET_CTLR_ENABLEGRP1(0x0);

	//----------------------------------------------------------------------
	// Distributor side
	// Distributor Control Register (GICD_CTLR)
	//----------------------------------------------------------------------
	DdGic_DIST_DIST_SET_CTLR_ENABLEGRP0(0x0);
	DdGic_DIST_SET_CTLR_ENABLEGRP1(0x0);
	DD_ARM_DSB_POU();
}

/**
 * @brief	Control Generic Interrupt Controller to set resource.
 * @param	DdGicIntid	intid
			kulong			setEnable
			kint64			intrptPri
			kint64			cpuTarget
 */
kint32 dd_gic_ctrl(DdGic *self, DdGicIntid intid, kulong setEnable, kint64 intrptPri, kint64 cpuTarget)
{
	kulong num;
	kint32 sho;
	
#ifdef CO_PARAM_CHECK
	kuint16 flg;
	
	if (intid > C_INTID_SPI_MAX) {
		Ddim_Assertion(("GIC: input param error. [intid] = %x\n", (kuint32)intid));
		return C_GIC_INPUT_PARAM_ERR;
	}
	if (setEnable > 1) {
		Ddim_Assertion(("GIC: input param error. [setEnable] = %x\n", (kuint32)setEnable));
		return C_GIC_INPUT_PARAM_ERR;
	}
	flg = 0;
	num = 0;
	while (num <= 248 && intrptPri >= 0) {
		if (intrptPri == num) {
			flg = 1;
			break;
		}
		if (intrptPri < num) {
			break;
		}
		num += 8;
	}
	if (intrptPri != -1 && flg == 0) {
		Ddim_Assertion(("GIC: input param error. [intrptPri] = %x\n", (kint32)intrptPri));
		return C_GIC_INPUT_PARAM_ERR;
	}
	if (cpuTarget < -1 || cpuTarget > 15) {
		Ddim_Assertion(("GIC: input param error. [cpuTarget] = %x\n", (kint32)cpuTarget));
		return C_GIC_INPUT_PARAM_ERR;
	}
#endif
	//----------------------------------------------------------------------
	// Disable Interrupt
	// Interrupt Clear-Enable Register (GICD_ICENABLER)
	//----------------------------------------------------------------------
	// SGIs are always enabled.
	if (intid > C_INTID_SGI_MAX && intid <= C_INTID_SPI_MAX) {
		sho = intid / 32;
		num = 1 << (intid - sho * 32);
		DdGic_DIST_SET_ICENABLER(sho, num);
	}
	
	//----------------------------------------------------------------------
	// Set Interupt Priority
	// Interrupt Priority Register (GICD_IPRIORITYR)
	//----------------------------------------------------------------------
	dd_gic_set_priority(NULL, intid, intrptPri);
	
	//----------------------------------------------------------------------
	// Set Target CPU
	// Interrupt Processor Targets Register (GICD_ITARGETSR)
	//----------------------------------------------------------------------
	dd_gic_set_target_cpu(NULL, intid, cpuTarget);
	
	//----------------------------------------------------------------------
	// Enable Interrupt
	// Interrupt Set-Enable Registers (GICD_ISENABLER)
	//----------------------------------------------------------------------
	// SGIs are always enabled.
	if (setEnable) {
		if (intid > C_INTID_SGI_MAX && intid <= C_INTID_SPI_MAX) {
			sho = intid / 32;
			num = setEnable << (intid - sho * 32);
			DdGic_DIST_SET_ISENABLER(sho, num);
		}
	}
	
	DD_ARM_DSB_POU();

	return D_DDIM_OK;
}

/**
 * @brief	Set Interrupt Priority Registers.
 * @param	kulong	intid
			kint64	intrptPri
 */
kint32 dd_gic_set_priority(DdGic *self, DdGicIntid intid, kint64 intrptPri)
{
#ifdef CO_PARAM_CHECK
	kuint16 flg;
	kulong num;
	
	if (intid > C_INTID_SPI_MAX) {
		Ddim_Assertion(("GIC: input param error. [intid] = %x\n", (kuint32)intid));
		return C_GIC_INPUT_PARAM_ERR;
	}
	flg = 0;
	num = 0;
	while (num <= 248 && intrptPri >= 0) {
		if (intrptPri == num) {
			flg = 1;
			break;
		}
		if (intrptPri < num) {
			break;
		}
		num += 8;
	}
	if (intrptPri != -1 && flg == 0) {
		Ddim_Assertion(("GIC: input param error. [intrptPri] = %x\n", (kint32)intrptPri));
		return C_GIC_INPUT_PARAM_ERR;
	}
#endif
	//----------------------------------------------------------------------
	// Set Interupt Priority
	// Interrupt Priority Register (GICD_IPRIORITYR)
	//----------------------------------------------------------------------
	if (intrptPri != -1) {
		if (intid <= C_INTID_SPI_MAX) {
			DdGic_DIST_SET_IPRIORITYR(intid, intrptPri);
		}
	}
	
	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Set Interrupt Processor Targets Registers.
 * @param	kulong	intid
			kint64	cpuTarget
 */
kint32 dd_gic_set_target_cpu(DdGic *self, DdGicIntid intid, kint64 cpuTarget)
{
#ifdef CO_PARAM_CHECK
	if (intid > C_INTID_SPI_MAX) {
		Ddim_Assertion(("GIC: input param error. [intid] = %x\n", (kuint32)intid));
		return C_GIC_INPUT_PARAM_ERR;
	}
	if (cpuTarget < -1 || cpuTarget > 15) {
		Ddim_Assertion(("GIC: input param error. [cpuTarget] = %x\n", (kint32)cpuTarget));
		return C_GIC_INPUT_PARAM_ERR;
	}
#endif
	//----------------------------------------------------------------------
	// Target CPU
	// Interrupt Processor Targets Register (GICD_ITARGETSR)
	//----------------------------------------------------------------------
	if (cpuTarget != -1) {
		if (intid <= C_INTID_SPI_MAX) {
			DdGic_DIST_SET_ITARGETSR(intid, cpuTarget);
		}
	}
	
	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Set Software Generated Interrupt Registers.
 * @param	kulong	intid
			kulong	targetFilter
			kulong	cpuTarget
 */
kint32 dd_gic_send_sgi(DdGic *self, DdGicIntid intid, kulong targetFilter, kulong cpuTarget)
{
#ifdef CO_PARAM_CHECK
	if (intid > C_INTID_SGI_MAX) {
		Ddim_Assertion(("GIC: input param error. [intid] = %x\n", (kuint32)intid));
		return C_GIC_INPUT_PARAM_ERR;
	}
	if (targetFilter > 2) {
		Ddim_Assertion(("GIC: input param error. [targetFilter] = %x\n", (kint32)targetFilter));
		return C_GIC_INPUT_PARAM_ERR;
	}
	if (cpuTarget > 15) {
		Ddim_Assertion(("GIC: input param error. [cpuTarget] = %x\n", (kint32)cpuTarget));
		return C_GIC_INPUT_PARAM_ERR;
	}
#endif
	kulong sgiSet;
	
	// Select SATT bit value always secure.
	sgiSet = (kulong) intid + (targetFilter << 24) + (cpuTarget << 16);
	DdGic_DIST_SET_SGIR(sgiSet);
	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

DdGic* dd_gic_new(void)
{
	DdGic* self = k_object_new_with_private(DD_TYPE_GIC, sizeof(DdGicPrivate));

	return self;
}
