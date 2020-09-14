/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdPmu类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、PMU driver Component Test
*@version
*1.0.0 2020年06月开始开发
*/

#include <stdlib.h>
#include <string.h>
#include "driver_common.h"
#include "ddpmu.h"
#include "pmc.h"
#include "ctddpmu.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPmu, ct_dd_pmu);
#define CT_DD_PMU_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPmuPrivate,CT_TYPE_DD_PMU))

struct _CtDdPmuPrivate {
    kint i;
};

static void ct_dd_pmu_constructor(CtDdPmu *self) 
{
// CtDdPmuPrivate *priv = CT_DD_PMU_GET_PRIVATE(self);
}

static void ct_dd_pmu_destructor(CtDdPmu *self)
{
// CtDdPmuPrivate *priv = CT_DD_PMU_GET_PRIVATE(self);
}
/*
 *PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/**
 * @brief  Command main function for PMU test.
 * @param  int argc	:The number of parameters
 *		   char** argv	:The value of parameters
 * @return void
 */
void ct_dd_pmu_main(CtDdPmu *self, kint argc, KType* argv)
{
	kint32	ret;
	DdPmu *	ddPmu = dd_pmu_get();

	if(strcmp(argv[1], "pd") == 0){
		// get 2nd paramter.
		if(strcmp(argv[2], "get") == 0){
			// get 3rd paramter.
			if(argc > 3){
				self->param2 = atoi(argv[3]);

				ret = dd_pmu_get_status(ddPmu, self->param2, &self->value);
				Ddim_Print(("--- PMU Power status ---\n"));
				Ddim_Print(("Status : %d=0x%08lx ret=0x%08x\n", self->param2, self->value, ret));
			}
			else {
				Ddim_Print(("--- PMU Power status ---\n"));
				for (self->param2 = 0; self->param2 < DdPmu_PD_TYPE_MAX; self->param2 ++) {
					if (self->param2 == DdPmu_PD_TYPE_RESERVED) {
						continue;
					}
					ret = dd_pmu_get_status(ddPmu, self->param2, &self->value);
					Ddim_Print(("Status : %d=0x%08lx ret=0x%08x\n", self->param2, self->value, ret));
				}
			}
		}
		else if(strcmp(argv[2], "off") == 0){
			if(argc > 3){
				// get 3rd paramter.
				self->param2 = atoi(argv[3]);

				ret = dd_pmu_pd_off(ddPmu, self->param2);
				Ddim_Print(("--- PMU status ---\n"));
				Ddim_Print(("Stauts : %d ret=0x%08x\n", self->param2, ret));
			}
			else {
				Ddim_Print(("--- PMU status ---\n"));
				for (self->param2 = 0; self->param2 < DdPmu_PD_TYPE_MAX; self->param2 ++) {
					if (self->param2 == DdPmu_PD_TYPE_RESERVED) {
						continue;
					}
					ret = dd_pmu_pd_off(ddPmu, self->param2);
					Ddim_Print(("Status : %d ret=0x%08x\n", self->param2, ret));
				}
			}
		}
		else if(strcmp(argv[2], "on") == 0){
			if(argc > 3){
				// get 3rd paramter.
				self->param2 = atoi(argv[3]);

				ret = dd_pmu_pd_on(ddPmu, self->param2);
				Ddim_Print(("--- PMU status ---\n"));
				Ddim_Print(("Status : %d ret=0x%08x\n", self->param2, ret));
			}
			else {
				Ddim_Print(("--- PMU status ---\n"));
				for (self->param2 = 0; self->param2 < DdPmu_PD_TYPE_MAX; self->param2++) {
					if (self->param2 == DdPmu_PD_TYPE_RESERVED) {
						continue;
					}
					ret = dd_pmu_pd_on(ddPmu, self->param2);
					Ddim_Print(("Status : %d ret=0x%08x\n", self->param2, ret));
				}
			}
		}
		else if(strcmp(argv[2], "onoff") == 0){
			if(argc > 3){
				// get 3rd paramter.
				self->param2 = atoi(argv[3]);

				ret = dd_pmu_get_status(ddPmu, self->param2, &self->value);
				Ddim_Print(("Status : %d=0x%08lx ret=0x%08x\n", self->param2, self->value, ret));
				ret = dd_pmu_pd_on(ddPmu, self->param2);
				ret = dd_pmu_get_status(ddPmu, self->param2, &self->value);
				Ddim_Print(("Status : %d=0x%08lx ret=0x%08x\n", self->param2, self->value, ret));

				ret = dd_pmu_get_status(ddPmu, self->param2, &self->value);
				Ddim_Print(("Status : %d=0x%08lx ret=0x%08x\n", self->param2, self->value, ret));
				ret = dd_pmu_pd_off(ddPmu, self->param2);
				ret = dd_pmu_get_status(ddPmu, self->param2, &self->value);
				Ddim_Print(("Status : %d=0x%08lx ret=0x%08x\n", self->param2, self->value, ret));

				Ddim_Print(("--- PMU status ---\n"));
				Ddim_Print(("Status : %d ret=0x%08x\n", self->param2, ret));
			}
			else {
				Ddim_Print(("--- PMU status ---\n"));
				for (self->param2 = 0; self->param2 < DdPmu_PD_TYPE_MAX; self->param2 ++) {
					if (self->param2 == DdPmu_PD_TYPE_RESERVED) {
						continue;
					}
					ret = dd_pmu_get_status(ddPmu, self->param2, &self->value);
					Ddim_Print(("Status : %d=0x%08lx ret=0x%08x\n", self->param2, self->value, ret));

					ret = dd_pmu_pd_on(ddPmu, self->param2);
					Ddim_Print(("Status : %d ret=0x%08x\n", self->param2, ret));

					ret = dd_pmu_get_status(ddPmu, self->param2, &self->value);
					Ddim_Print(("Status : %d=0x%08lx ret=0x%08x\n", self->param2, self->value, ret));

					ret = dd_pmu_pd_off(ddPmu, self->param2);
					Ddim_Print(("Status : %d ret=0x%08x\n", self->param2, ret));

					ret = dd_pmu_get_status(ddPmu, self->param2, &self->value);
					Ddim_Print(("Status : %d=0x%08lx ret=0x%08x\n\n", self->param2, self->value, ret));
				}
			}
		}
		else{
			Ddim_Print(("please check 2nd parameter!!\n"));
		}
	}
	else{
		Ddim_Print(("please check 1st parameter!!\n"));
	}
	k_object_unref(ddPmu);
	ddPmu = NULL; 
}

CtDdPmu *ct_dd_pmu_new(void)
{
    CtDdPmu *self = k_object_new_with_private(CT_TYPE_DD_PMU, sizeof(CtDdPmuPrivate));
    return self;
}
