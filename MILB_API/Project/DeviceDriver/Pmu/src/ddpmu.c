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
#include "ddarm.h"
#include "ddimusercustom.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdPmu, dd_pmu);
#define DD_PMU_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdPmuPrivate, DD_TYPE_PMU))


struct _DdPmuPrivate
{
};

static kulong S_DD_PMU_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));

static void dd_pmu_constructor(DdPmu *self)
{
}

static void dd_pmu_destructor(DdPmu *self)
{

}

/**
 * @brief  Get status of PMU PD function.
*/
INT32 dd_pmu_get_status(DdPmu *self, DdPmuPdType pdType, kulong* value)
{
	if (value == NULL) {
		return DdPmu_INPUT_PARAM_ERR;
	}
	*value = 0x0;
	if (pdType == DdPmu_PD_TYPE_RESERVED || pdType >= DdPmu_PD_TYPE_MAX) {
		return DdPmu_INPUT_PARAM_ERR;
	}
	
	// Get Power status.
	Dd_ARM_Critical_Section_Start(S_DD_PMU_SPIN_LOCK);
	*value = ioPmc.pmu.pwrStr & (1 << pdType);		// PD#0~6
	Dd_ARM_Critical_Section_End(S_DD_PMU_SPIN_LOCK);
	*value = (*value >> pdType) & 0x1;
	
	return D_DDIM_OK;
}

/**
 * @brief  PMU PD Off function.
*/
INT32 dd_pmu_pd_off(DdPmu *self, DdPmuPdType pdType)
{
	int iDelayCount;
	kulong pmuStatus = 0;
	
	if (pdType == DdPmu_PD_TYPE_RESERVED || pdType >= DdPmu_PD_TYPE_MAX) {
		return DdPmu_INPUT_PARAM_ERR;
	}
	
	Dd_ARM_Critical_Section_Start(S_DD_PMU_SPIN_LOCK);
	// Get Power status.
	pmuStatus = ioPmc.pmu.pwrStr & 0x0000007F;		// PD#0~6
	
	// To make sure that the operation of the PD target macro has been completed.
	
	// On chip PG Power off.
	if (pmuStatus != 0) {
//		pmuStatus = ~pmuStatus;		// PD#0~6
//		pmuStatus &= (0xffffffff - (1 << pdType));
		pmuStatus = (1 << pdType);
		
		// Set the Power OFF request.
//		ioPmc.pmu.pwrDnEn |= pmuStatus;
		ioPmc.pmu.pwrDnEn = pmuStatus;
		
		// Power-switch-down done Interrupt Clear.
		ioPmc.pmu.pmuIntClr.bit.pdnic = 1;
		
		// Power-switch-down done Interrupt Enalbe.
		ioPmc.pmu.pmuIntEn.bit.pdnie = 1;
		
		// Power Down SET.
		ioPmc.pmu.pmuCtl.word |= 0x0000AA02;
		
		for (iDelayCount = 0; iDelayCount < 100; iDelayCount++) {
			// Check Power-switch-down done Interrupt.
			if (ioPmc.pmu.pmuIntSt.bit.pdni == 1) {
				break;
			}
			// 1ms wait.
			DDIM_User_Dly_Tsk(1);
		}
		
		// Power-switch-down done Interrupt Clear.
		ioPmc.pmu.pmuIntClr.bit.pdnic = 1;
	}
	Dd_ARM_Critical_Section_End(S_DD_PMU_SPIN_LOCK);
	DDIM_User_Dly_Tsk(0);
	
	return D_DDIM_OK;
}

/**
 * @brief  PMU PD on function.
*/
INT32 dd_pmu_pd_on(DdPmu *self, DdPmuPdType pdType)
{
	int iDelayCount;
	kulong pmuStatus = 0;
	
	if (pdType == DdPmu_PD_TYPE_RESERVED || pdType >= DdPmu_PD_TYPE_MAX) {
		return DdPmu_INPUT_PARAM_ERR;
	}
	
	Dd_ARM_Critical_Section_Start(S_DD_PMU_SPIN_LOCK);
	// Get Power status.
	pmuStatus = ioPmc.pmu.pwrStr & 0x0000007F;		// PD#0~6
	
	// On chip PG Power on.
	if ((pmuStatus & (1 << pdType)) == 0) {
//		pmuStatus &= (0xffffffff - (1 << pdType));
		pmuStatus = (1 << pdType);
		
//		ioPmc.pmu.pwrOnEn0 |= pmuStatus;
		ioPmc.pmu.pwrOnEn0 = pmuStatus;
		
		// Power-switch-ON done Interrupt Clear.
		ioPmc.pmu.pmuIntClr.bit.ponic = 1;
		
		// Power-switch-ON done Interrupt Enalbe.
		ioPmc.pmu.pmuIntEn.bit.ponie = 1;
		
		// Power Up SET.
		ioPmc.pmu.pmuCtl.word |= 0x0000AA01;
		
		for (iDelayCount = 0; iDelayCount < 100; iDelayCount++) {
			// Check Power-switch-ON done Interrupt.
			if (ioPmc.pmu.pmuIntSt.bit.poni == 1) {
				break;
			}
			// 1ms wait.
			DDIM_User_Dly_Tsk(1);
		}
		
		// Power-switch-ON done Interrupt Clear.
		ioPmc.pmu.pmuIntClr.bit.ponic = 1;
	}
	Dd_ARM_Critical_Section_End(S_DD_PMU_SPIN_LOCK);
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

