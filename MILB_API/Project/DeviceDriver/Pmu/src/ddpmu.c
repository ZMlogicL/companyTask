/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月5日
 * @author            :冯黎阳
 * @brief             :
 * @rely              :klib
 * @function
 * @version
 *
 */

#include <string.h>
#include "pmc.h"
#include "ddpmu.h"
#include "dd_arm.h"
#include "ddim_user_custom.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdPmu, dd_pmu);
#define DD_PMU_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdPmuPrivate, DD_TYPE_PMU))


struct _DdPmuPrivate
{
};

static ULONG gDD_PMU_Spin_Lock __attribute__((section(".LOCK_SECTION"), aligned(64)));

static void dd_pmu_constructor(DdPmu *self)
{
}

static void dd_pmu_destructor(DdPmu *self)
{

}

/**
 * @brief  Get status of PMU PD function.
*/
INT32 dd_pmu_get_status(DdPmu *self, DdPmuPdType pd_type, ULONG* value)
{
	if (value == NULL) {
		return DdPmu_INPUT_PARAM_ERR;
	}
	*value = 0x0;
	if (pd_type == DdPmu_PD_TYPE_RESERVED || pd_type >= DdPmu_PD_TYPE_MAX) {
		return DdPmu_INPUT_PARAM_ERR;
	}
	
	// Get Power status.
	Dd_ARM_Critical_Section_Start(gDD_PMU_Spin_Lock);
	*value = IO_PMC.PMU.PWR_STR & (1 << pd_type);		// PD#0~6
	Dd_ARM_Critical_Section_End(gDD_PMU_Spin_Lock);
	*value = (*value >> pd_type) & 0x1;
	
	return D_DDIM_OK;
}

/**
 * @brief  PMU PD Off function.
*/
INT32 dd_pmu_pd_off(DdPmu *self, DdPmuPdType pd_type)
{
	int iDelayCount;
	ULONG pmuStatus = 0;
	
	if (pd_type == DdPmu_PD_TYPE_RESERVED || pd_type >= DdPmu_PD_TYPE_MAX) {
		return DdPmu_INPUT_PARAM_ERR;
	}
	
	Dd_ARM_Critical_Section_Start(gDD_PMU_Spin_Lock);
	// Get Power status.
	pmuStatus = IO_PMC.PMU.PWR_STR & 0x0000007F;		// PD#0~6
	
	// To make sure that the operation of the PD target macro has been completed.
	
	// On chip PG Power off.
	if (pmuStatus != 0) {
//		pmuStatus = ~pmuStatus;		// PD#0~6
//		pmuStatus &= (0xffffffff - (1 << pd_type));
		pmuStatus = (1 << pd_type);
		
		// Set the Power OFF request.
//		IO_PMC.PMU.PWR_DN_EN |= pmuStatus;
		IO_PMC.PMU.PWR_DN_EN = pmuStatus;
		
		// Power-switch-down done Interrupt Clear.
		IO_PMC.PMU.PMU_INT_CLR.bit.PDNIC = 1;
		
		// Power-switch-down done Interrupt Enalbe.
		IO_PMC.PMU.PMU_INT_EN.bit.PDNIE = 1;
		
		// Power Down SET.
		IO_PMC.PMU.PMU_CTL.word |= 0x0000AA02;
		
		for (iDelayCount = 0; iDelayCount < 100; iDelayCount++) {
			// Check Power-switch-down done Interrupt.
			if (IO_PMC.PMU.PMU_INT_ST.bit.PDNI == 1) {
				break;
			}
			// 1ms wait.
			DDIM_User_Dly_Tsk(1);
		}
		
		// Power-switch-down done Interrupt Clear.
		IO_PMC.PMU.PMU_INT_CLR.bit.PDNIC = 1;
	}
	Dd_ARM_Critical_Section_End(gDD_PMU_Spin_Lock);
	DDIM_User_Dly_Tsk(0);
	
	return D_DDIM_OK;
}

/**
 * @brief  PMU PD on function.
*/
INT32 dd_pmu_pd_on(DdPmu *self, DdPmuPdType pd_type)
{
	int iDelayCount;
	ULONG pmuStatus = 0;
	
	if (pd_type == DdPmu_PD_TYPE_RESERVED || pd_type >= DdPmu_PD_TYPE_MAX) {
		return DdPmu_INPUT_PARAM_ERR;
	}
	
	Dd_ARM_Critical_Section_Start(gDD_PMU_Spin_Lock);
	// Get Power status.
	pmuStatus = IO_PMC.PMU.PWR_STR & 0x0000007F;		// PD#0~6
	
	// On chip PG Power on.
	if ((pmuStatus & (1 << pd_type)) == 0) {
//		pmuStatus &= (0xffffffff - (1 << pd_type));
		pmuStatus = (1 << pd_type);
		
//		IO_PMC.PMU.PWR_ON_EN0 |= pmuStatus;
		IO_PMC.PMU.PWR_ON_EN0 = pmuStatus;
		
		// Power-switch-ON done Interrupt Clear.
		IO_PMC.PMU.PMU_INT_CLR.bit.PONIC = 1;
		
		// Power-switch-ON done Interrupt Enalbe.
		IO_PMC.PMU.PMU_INT_EN.bit.PONIE = 1;
		
		// Power Up SET.
		IO_PMC.PMU.PMU_CTL.word |= 0x0000AA01;
		
		for (iDelayCount = 0; iDelayCount < 100; iDelayCount++) {
			// Check Power-switch-ON done Interrupt.
			if (IO_PMC.PMU.PMU_INT_ST.bit.PONI == 1) {
				break;
			}
			// 1ms wait.
			DDIM_User_Dly_Tsk(1);
		}
		
		// Power-switch-ON done Interrupt Clear.
		IO_PMC.PMU.PMU_INT_CLR.bit.PONIC = 1;
	}
	Dd_ARM_Critical_Section_End(gDD_PMU_Spin_Lock);
	DDIM_User_Dly_Tsk(0);
	
	return D_DDIM_OK;
}

DdPmu* dd_pmu_get(void)
{
	static DdPmu* self = NULL;

	if(!self)
		self = k_object_new_with_private(DD_TYPE_PMU, sizeof(DdPmuPrivate));

	return self;
}

