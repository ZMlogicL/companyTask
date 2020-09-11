/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-05
*@author              :jianghaodong
*@brief               :CtDdGic类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include <stdlib.h>
#include <string.h>
#include "driver_common.h"
#include "dd_gic.h"

#include "ctddgic.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdGic, ct_dd_gic);
#define CT_DD_GIC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdGicPrivate,CT_TYPE_DD_GIC))

struct _CtDdGicPrivate
{
};

/*
*IMPL
*/
static void ct_dd_gic_constructor(CtDdGic *self) 
{
}

static void ct_dd_gic_destructor(CtDdGic *self) 
{
}


/*
*PUBLIC
*/
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
/**
 * @brief  Command main function for GIC test.
 * @param  int argc	:The number of parameters
 *		   char** argv	:The value of parameters
 * @return void
 *
 *		The meaning of parameters
 *		+-----+--------+------------+------------+------------+-----------------------------------------------------+
 *		| P1  | P2     | P3         | P4         | P5         |Meaning                                              |
 *		+-----+--------+------------+------------+------------+-----------------------------------------------------+
 *		| 1   | -      | -          | -          | -          |Initialize Generic Interrupt Controller.             |
 *		+-----+--------+------------+------------+------------+-----------------------------------------------------+
 *		| 2   | int id | enable     | priority   | cpu target |Control Generic Interrupt Controller to set resource.|
 *		+-----+--------+------------+------------+------------+-----------------------------------------------------+
 *		| 3   | -      | -          | -          | -          |End Generic Interrupt Controller.                    |
 *		+-----+--------+------------+------------+------------+-----------------------------------------------------+
 *		| 4   | int id | cpu filter | cpu target | -          |SGI Interrupt.                                       |
 *		+-----+--------+------------+------------+------------+-----------------------------------------------------+
 *		| 5   | -      | -          | -          | -          |Macro Check.                                         |
 *		+-----+--------+------------+------------+------------+-----------------------------------------------------+
 *		| 6   | -      | -          | -          | -          |Parameter Error Check.                               |
 *		+-----+--------+------------+------------+------------+-----------------------------------------------------+
 */
void ct_dd_gic_main_main(CtDdGic* self, kint argc, kchar** argv)
{
	kint32  dat;
	kuint32 regNum;

	kuint32 sho;
	kuint32 intid;
	kuint32 setEnable;
	kint32  intrptPri;
	kint32  cpuTarget;
	kuint32 targetFilter;

	switch ( strtol(argv[1], NULL, 16) ) {
		case 1:		// Init
			Ddim_Print(("Dd_GIC_Init Test Start\n"));
			Dd_GIC_Init();

			// GICD_ICENABLER
			dat = Dd_GIC_DIST_Get_ICEnabler(0);
			Ddim_Print(("GICD_ICENABLER[0] = 0x%08x (set 0x0000FFFF:SGI Enable)\n", dat));

			for(regNum=1; regNum<(D_DD_GIC_INTID_MAX/32); regNum++){
				dat = Dd_GIC_DIST_Get_ICEnabler(regNum);
				Ddim_Print(("GICD_ICENABLER[%d] = 0x%08x (set 0x00000000)\n", regNum, dat));
			}

			// GICD_ICPENDR
			dat = Dd_GIC_DIST_Get_ICPendr(0);
			Ddim_Print(("GICD_ICPENDR[0] = 0x%08x (set 0x00000000:SGI and PPI Pending)\n", dat));

			for(regNum=0; regNum<(D_DD_GIC_INTID_MAX/32); regNum++){
				dat = Dd_GIC_DIST_Get_ICPendr(regNum);
				Ddim_Print(("GICD_ICPENDR[%d] = 0x%08x (set 0x00000000)\n", regNum, dat));
			}

			// GICD_IPRIORITYR
			for(regNum=0; regNum<D_DD_GIC_INTID_MAX; regNum++){
				dat = Dd_GIC_DIST_Get_IPriorityr(regNum);
				Ddim_Print(("GICD_IPRIORITYR[%d] = 0x%02x (set 0x00)\n", regNum, dat));
			}

			// GICD_ITARGETSR
			for(regNum=32; regNum<D_DD_GIC_INTID_MAX; regNum++){
				dat = Dd_GIC_DIST_Get_ITargetsr(regNum);
				Ddim_Print(("GICD_ITARGETSR[%d] = %d (set 0)\n", regNum, dat));
			}

			// GICD_ICFGR
			dat = Dd_GIC_DIST_Get_ICfgr(0);
			Ddim_Print(("ICDICFR[0] = 0x%08x (set 0xaaaaaaaa)\n", dat));

			dat = Dd_GIC_DIST_Get_ICfgr(1);
			Ddim_Print(("ICDICFR[1] = 0x%08x (set 0x7dc00000)\n", dat));

			for(regNum=2; regNum<(D_DD_GIC_INTID_MAX/16); regNum++){
				dat = Dd_GIC_DIST_Get_ICfgr(regNum);
				Ddim_Print(("ICDICFR[%d] = 0x%08x (set 0x55555555)\n", regNum, dat));
			}

			// GICC_PMR
			dat = Dd_GIC_CPU_Get_Pmr_Priority;
			Ddim_Print(("GICC_PMR = 0x%02x (set 0xF8)\n", dat));

			// GICC_BPR
			dat = Dd_GIC_CPU_Get_Bpr_BinaryPoint;
			Ddim_Print(("GICC_BPR = %d (set 2)\n", dat));

			// GICC_IAR
			dat = Dd_GIC_CPU_Get_Iar;
			Ddim_Print(("GICC_IAR = 0x%08x (set 0x00000000)\n", dat));

			// GICD_CTLR
			dat = Dd_GIC_DIST_Get_Ctlr_EnableGrp0;
			Ddim_Print(("GICD_CTLR EnableGrp0 = %d (set 1)\n", dat));
			dat = Dd_GIC_DIST_Get_Ctlr_EnableGrp1;
			Ddim_Print(("GICD_CTLR EnableGrp1 = %d (set 0)\n", dat));

			// GICC_CTLR
			dat = Dd_GIC_CPU_Get_Ctlr_EnableGrp0;
			Ddim_Print(("GICC_CTLR EnableGrp0 = %d (set 1)\n", dat));
			dat = Dd_GIC_CPU_Get_Ctlr_EnableGrp1;
			Ddim_Print(("GICC_CTLR EnableGrp1 = %d (set 0)\n", dat));

			Ddim_Print(("Dd_GIC_Init Test End\n"));
			break;

		case 2:		// Ctrl
			Ddim_Print(("Dd_GIC_Ctrl Test Start\n"));
			intid = strtoul(argv[2], NULL, 16);
			setEnable = strtoul(argv[3], NULL, 16);
			intrptPri = strtol(argv[4], NULL, 16);
			cpuTarget = strtol(argv[5], NULL, 16);

			if( intid <= 0 ){
				intid = 0;
			}
			if( setEnable <= 0 ){
				setEnable = 0;
			}
			if( intrptPri >= 0x7FFFFFFF ){
				intrptPri = -1;
			}
			if( cpuTarget >= 0x7FFFFFFF ){
				cpuTarget = -1;
			}
			if( Dd_GIC_Ctrl( (E_DD_GIC_INTID)intid, setEnable, intrptPri, cpuTarget ) == D_DDIM_OK ){
				dat = Dd_GIC_DIST_Get_IPriorityr(intid);
				Ddim_Print(("GICD_IPRIORITYR[%u] = 0x%02x\n", intid, dat));
				dat = Dd_GIC_DIST_Get_ITargetsr(intid);
				Ddim_Print(("GICD_ITARGETSR[%u] = %d\n", intid, dat));
				sho = intid / 32;
				dat = Dd_GIC_DIST_Get_ISEnabler(sho);
				Ddim_Print(("GICD_ISENABLER[%u] = 0x%08x\n", sho, dat));
			}
			else{
				Ddim_Print(("please check parameter!!\n"));
			}

			Ddim_Print(("Dd_GIC_Ctrl Test End\n"));
			break;

		case 3:		// End
			Ddim_Print(("Dd_GIC_End Test Start\n"));
			Dd_GIC_End();

			// GICD_CTLR
			dat = Dd_GIC_DIST_Get_Ctlr_EnableGrp0;
			Ddim_Print(("GICD_CTLR EnableGrp0 = %d (set 0)\n", dat));
			dat = Dd_GIC_DIST_Get_Ctlr_EnableGrp1;
			Ddim_Print(("GICD_CTLR EnableGrp1 = %d (set 0)\n", dat));

			// GICC_CTLR
			dat = Dd_GIC_CPU_Get_Ctlr_EnableGrp0;
			Ddim_Print(("GICC_CTLR EnableGrp0 = %d (set 0)\n", dat));
			dat = Dd_GIC_CPU_Get_Ctlr_EnableGrp1;
			Ddim_Print(("GICC_CTLR EnableGrp1 = %d (set 0)\n", dat));

			Ddim_Print(("Dd_GIC_End Test End\n"));
			break;

		case 4:		// SGI Test
			Ddim_Print(("SGI Test Start\n"));
			intid         = strtoul(argv[2], NULL, 16);
			targetFilter = strtoul(argv[3], NULL, 16);
			cpuTarget    = strtoul(argv[4], NULL, 16);

			if( intid <= 0 ){
				intid = 0;
			}
			if( targetFilter <= 0 ){
				targetFilter = 0;
			}
			if( cpuTarget < 0 ){
				cpuTarget = 0;
			}
			dat = Dd_GIC_Send_Sgi( (E_DD_GIC_INTID)intid, targetFilter, cpuTarget);

			Ddim_Print(("SGI Test End\n"));
			break;

		case 5:		// DIST & CPU
			Ddim_Print(("--------DIST-------\n"));

			// GICD_TYPER
			dat = Dd_GIC_DIST_Get_Typer_ItLinesNumber;
			Ddim_Print(("GICD_TYPER Get ITLINESNUMBER = %d\n", dat));
			dat = Dd_GIC_DIST_Get_Typer_CpuNumber;
			Ddim_Print(("GICD_TYPER Get CPUNUMBER = %d\n", dat));
			dat = Dd_GIC_DIST_Get_Typer_SecurityExtn;
			Ddim_Print(("GICD_TYPER Get SECURITY_EXTN = %d\n", dat));
			dat = Dd_GIC_DIST_Get_Typer_Lspi;
			Ddim_Print(("GICD_TYPER Get LSPI = %d\n", dat));

			// GICD_IIDR
			dat = Dd_GIC_DIST_Get_IIdr_Implementer;
			Ddim_Print(("GICD_IIDR Get IMPLEMENTER = %d\n", dat));
			dat = Dd_GIC_DIST_Get_IIdr_Revision;
			Ddim_Print(("GICD_IIDR Get REVISION = %d\n", dat));
			dat = Dd_GIC_DIST_Get_IIdr_Variant;
			Ddim_Print(("GICD_IIDR Get VARIANT = %d\n", dat));
			dat = Dd_GIC_DIST_Get_IIdr_ProductId;
			Ddim_Print(("GICD_IIDR Get PRODUCTID = %d\n", dat));

			// GICD_IGROUPR
			dat = Dd_GIC_DIST_Get_IGroupr(1);
			Ddim_Print(("GICD_IGROUPR Get = %d\n", dat));

			// GICD_ISPENDR
			// GICD_ICPENDR
			Dd_GIC_DIST_Set_ISPendr(1, 1);
			dat = Dd_GIC_DIST_Get_ISPendr(1);
			Ddim_Print(("GICD_ISPENDR Get = 0x%08x\n", dat));
			Dd_GIC_DIST_Set_ICPendr(1, 1);
			dat = Dd_GIC_DIST_Get_ICPendr(1);
			Ddim_Print(("GICD_ICPENDR Get = 0x%08x\n", dat));

			// GICD_ISACTIVER
			// GICD_ICACTIVER
			Dd_GIC_DIST_Set_ISActiver(2, 0x80000000);
			dat = Dd_GIC_DIST_Get_ISActiver(2);
			Ddim_Print(("GICD_ISACTIVER Get = 0x%08x\n", dat));
			Dd_GIC_DIST_Set_ICActiver(2, 0x80000000);
			dat = Dd_GIC_DIST_Get_ICActiver(2);
			Ddim_Print(("GICD_ICACTIVER Get = 0x%08x\n", dat));

			// GICD_PPISR
			dat =  Dd_GIC_DIST_Get_Spisr(1);
			Ddim_Print(("GICD_SPISR Get = 0x%08x\n", dat));

			// GICD_SPISR
			dat =  Dd_GIC_DIST_Get_Ppisr;
			Ddim_Print(("GICD_PPISR Get = 0x%08x\n", dat));

			// GICD_SPENDSGIR
			// GICD_CPENDSGIR
			Dd_GIC_DIST_Set_SPendSgir(0, 1);
			dat = Dd_GIC_DIST_Get_SPendSgir(0);
			Ddim_Print(("GICD_SPENDSGIR Get = 0x%08x\n", dat));
			Dd_GIC_DIST_Set_CPendSgir(0, 1);
			dat = Dd_GIC_DIST_Get_CPendSgir(0);
			Ddim_Print(("GICD_CPENDSGIR Get = 0x%08x\n", dat));

			Ddim_Print(("-------------------\n"));

			Ddim_Print(("--------CPU--------\n"));

			// GICC_CTLR
			Dd_GIC_CPU_Set_Ctlr_Ackctl(1);
			dat = Dd_GIC_CPU_Get_Ctlr_Ackctl;
			Ddim_Print(("GICC_CTLR Get ACKCTL = %d\n", dat));
			//Dd_GIC_CPU_Set_Ctlr_Fiqen(1);
			//dat = Dd_GIC_CPU_Get_Ctlr_Fiqen;
			//dim_Print(("GICC_CTLR Get FIQEN = %d\n", dat));
			Dd_GIC_CPU_Set_Ctlr_Sbpr(1);
			dat = Dd_GIC_CPU_Get_Ctlr_Sbpr;
			Ddim_Print(("GICC_CTLR Get CBPR = %d\n", dat));
			Dd_GIC_CPU_Set_Ctlr_FiqByDisGrp0(1);
			dat = Dd_GIC_CPU_Get_Ctlr_FiqByDisGrp0;
			Ddim_Print(("GICC_CTLR Get FIQBYPDISGRP0 = %d\n", dat));
			Dd_GIC_CPU_Set_Ctlr_IrqByDisGrp0(1);
			dat = Dd_GIC_CPU_Get_Ctlr_IrqByDisGrp0;
			Ddim_Print(("GICC_CTLR Get IRQBYPDISGRP0 = %d\n", dat));
			Dd_GIC_CPU_Set_Ctlr_FiqByDisGrp1(1);
			dat = Dd_GIC_CPU_Get_Ctlr_FiqByDisGrp1;
			Ddim_Print(("GICC_CTLR Get FIQBYPDISGRP1 = %d\n", dat));
			Dd_GIC_CPU_Set_Ctlr_IrqByDisGrp1(1);
			dat = Dd_GIC_CPU_Get_Ctlr_IrqByDisGrp1;
			Ddim_Print(("GICC_CTLR Get IRQBYPDISGRP1 = %d\n", dat));
			Dd_GIC_CPU_Set_Ctlr_EoiModeS(1);
			dat = Dd_GIC_CPU_Get_Ctlr_EoiModeS;
			Ddim_Print(("GICC_CTLR Get EOIMODES = %d\n", dat));
			Dd_GIC_CPU_Set_Ctlr_EoiModeNS(1);
			dat = Dd_GIC_CPU_Get_Ctlr_EoiModeNS;
			Ddim_Print(("GICC_CTLR Get EOIMODENS = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_IAR
			dat = Dd_GIC_CPU_Get_Iar;
			Ddim_Print(("GICC_IAR Get %d\n", dat));
			dat = Dd_GIC_CPU_Get_Iar_AckIntId;
			Ddim_Print(("GICC_IAR Get ACKINTID = %d\n", dat));
			dat = Dd_GIC_CPU_Get_Iar_CpuId;
			Ddim_Print(("GICC_IAR Get CPUID = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_EOIR
			Dd_GIC_CPU_Set_Eoir(0x00000401);
			Ddim_Print(("GICC_EOIR Set = 0x00000401\n"));
			Dd_GIC_CPU_Set_Eoir_EoiIntId(1);
			Ddim_Print(("GICC_EOIR Set EOIINTID = 1\n"));
			Dd_GIC_CPU_Set_Eoir_CpuId(1);
			Ddim_Print(("GICC_EOIR Set CPUID = 1\n"));

			Ddim_Print(("-------------------\n"));

			// GICC_RPR
			dat = Dd_GIC_CPU_Get_Rpr_Priority;
			Ddim_Print(("GICC_RPR Get PRIORITY = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_HPPIR
			dat = Dd_GIC_CPU_Get_Hppir_PendIntId;
			Ddim_Print(("GICC_HPPIR Get PENDINTID = %d\n", dat));
			dat = Dd_GIC_CPU_Get_Hppir_CpuId;
			Ddim_Print(("GICC_HPPIR Get CPUID = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_ABPR
			Dd_GIC_CPU_Set_ABpr_BinaryPoint(4);
			dat = Dd_GIC_CPU_Get_ABpr_BinaryPoint;
			Ddim_Print(("GICC_ABPR Get BINARYPOINT = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_AIAR
			dat = Dd_GIC_CPU_Get_AIar;
			Ddim_Print(("GICC_AIAR Get %d\n", dat));
			dat = Dd_GIC_CPU_Get_AIar_AckIntId;
			Ddim_Print(("GICC_AIAR Get ACKINTID = %d\n", dat));
			dat = Dd_GIC_CPU_Get_AIar_CpuId;
			Ddim_Print(("GICC_AIAR Get CPUID = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_AEOIR
			Dd_GIC_CPU_Set_AEoir(0x00000401);
			Ddim_Print(("GICC_AEOIR Set = 0x00000401\n"));
			Dd_GIC_CPU_Set_AEoir_EoiIntId(1);
			Ddim_Print(("GICC_AEOIR Set EOIINTID = 1\n"));
			Dd_GIC_CPU_Set_AEoir_CpuId(1);
			Ddim_Print(("GICC_AEOIR Set CPUID = 1\n"));

			Ddim_Print(("-------------------\n"));

			// GICC_AHPPIR
			dat = Dd_GIC_CPU_Get_AHppir_PendIntId;
			Ddim_Print(("GICC_AHPPIR Get PENDINTID = %d\n", dat));
			dat = Dd_GIC_CPU_Get_AHppir_CpuId;
			Ddim_Print(("GICC_AHPPIR Get CPUID = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_APR0
			Dd_GIC_CPU_Set_Apr0(1);
			dat = Dd_GIC_CPU_Get_Apr0;
			Ddim_Print(("GICC_APR0 Get = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_NSAPR0
			Dd_GIC_CPU_Set_NsApr0(1);
			dat = Dd_GIC_CPU_Get_NsApr0;
			Ddim_Print(("GICC_NSAPR0 Get = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_IIDR
			dat = Dd_GIC_CPU_Get_IIdr_Implementer;
			Ddim_Print(("GICC_IIDR Get IMPLEMENTER = %d\n", dat));
			dat = Dd_GIC_CPU_Get_IIdr_Revision;
			Ddim_Print(("GICC_IIDR Get REVISION = %d\n", dat));
			dat = Dd_GIC_CPU_Get_IIdr_Version;
			Ddim_Print(("GICC_IIDR Get VERSION = %d\n", dat));
			dat = Dd_GIC_CPU_Get_IIdr_ProductId;
			Ddim_Print(("GICC_IIDR Get PRODUCTID = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_DIR
			Dd_GIC_CPU_Set_Dir(1);
			Ddim_Print(("GICC_DIR Set = 1\n"));

			Ddim_Print(("-------------------\n"));
			break;

		case 6:		// Error Test
			Ddim_Print(("Dd_GIC_Ctrl Error Test\n"));
			dat = Dd_GIC_Ctrl((E_DD_GIC_INTID)(D_DD_GIC_INTID_SPI_MAX + 1), 1, D_DD_GIC_PRI31, 3);
			Ddim_Print(("Arg1 Test = 0x%08x\n", dat));
			dat = Dd_GIC_Ctrl((E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, 2, D_DD_GIC_PRI31, 3);
			Ddim_Print(("Arg2 Test = 0x%08x\n", dat));
			dat = Dd_GIC_Ctrl((E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, 1, (D_DD_GIC_PRI31 + 1), 3);
			Ddim_Print(("Arg3_Max Test = 0x%08x\n", dat));
			dat = Dd_GIC_Ctrl((E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, 1, -2, 3);
			Ddim_Print(("Arg3_Min Test = 0x%08x\n", dat));
			dat = Dd_GIC_Ctrl((E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, 1, D_DD_GIC_PRI31, 16);
			Ddim_Print(("Arg4_Max Test = 0x%08x\n", dat));
			dat = Dd_GIC_Ctrl((E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, 1, D_DD_GIC_PRI31, -2);
			Ddim_Print(("Arg4_Min Test = 0x%08x\n", dat));

			Ddim_Print(("Dd_GIC_Set_Priority Error Test\n"));
			dat = Dd_GIC_Set_Priority((E_DD_GIC_INTID)(D_DD_GIC_INTID_SPI_MAX + 1), D_DD_GIC_PRI31);
			Ddim_Print(("Arg1 Test = 0x%08x\n", dat));
			dat = Dd_GIC_Set_Priority((E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, (D_DD_GIC_PRI31 + 1));
			Ddim_Print(("Arg2_Max Test = 0x%08x\n", dat));
			dat = Dd_GIC_Set_Priority((E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, -2);
			Ddim_Print(("Arg2_Min Test = 0x%08x\n", dat));

			Ddim_Print(("Dd_GIC_Set_Target_Cpu Error Test\n"));
			dat = Dd_GIC_Set_Target_Cpu((E_DD_GIC_INTID)(D_DD_GIC_INTID_SPI_MAX + 1), D_DD_GIC_PRI31);
			Ddim_Print(("Arg1 Test = 0x%08x\n", dat));
			dat = Dd_GIC_Set_Target_Cpu((E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, 16);
			Ddim_Print(("Arg2_Max Test = 0x%08x\n", dat));
			dat = Dd_GIC_Set_Target_Cpu((E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, -2);
			Ddim_Print(("Arg2_Min Test = 0x%08x\n", dat));

			Ddim_Print(("Dd_GIC_Send_Sgi Error Test\n"));
			dat = Dd_GIC_Send_Sgi((E_DD_GIC_INTID)(D_DD_GIC_INTID_SGI_MAX + 1), 2, 3);
			Ddim_Print(("Arg1 Test = 0x%08x\n", dat));
			dat = Dd_GIC_Send_Sgi((E_DD_GIC_INTID)D_DD_GIC_INTID_SGI_MAX, 3, 3);
			Ddim_Print(("Arg2 Test = 0x%08x\n", dat));
			dat = Dd_GIC_Send_Sgi((E_DD_GIC_INTID)D_DD_GIC_INTID_SGI_MAX, 2, 16);
			Ddim_Print(("Arg3 Test = 0x%08x\n", dat));
			break;

		default :
			Ddim_Print(("please check 1st parameter!!\n"));
	}
}

CtDdGic* ct_dd_gic_new(void) 
{
    CtDdGic *self = k_object_new_with_private(CT_TYPE_DD_GIC, sizeof(CtDdGicPrivate));
    return self;
}
