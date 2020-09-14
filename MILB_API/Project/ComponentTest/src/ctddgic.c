/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
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
#include "ddgic.h"

#include "ctddgic.h"


G_DEFINE_TYPE(CtDdGic, ct_dd_gic, G_TYPE_OBJECT);
#define CT_DD_GIC_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_DD_GIC, CtDdGicPrivate))

struct _CtDdGicPrivate
{
	DdGic *ddGic;
};


/*
*DECLS
*/
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
/*
*IMPL
*/

static void ct_dd_gic_class_init(CtDdGicClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtDdGicPrivate));
}

static void ct_dd_gic_init(CtDdGic *self)
{
	CtDdGicPrivate *priv = CT_DD_GIC_GET_PRIVATE(self);
	priv->ddGic=dd_gic_new();
}

static void dispose_od(GObject *object)
{
	CtDdGic *self = (CtDdGic*)object;
	CtDdGicPrivate *priv = CT_DD_GIC_GET_PRIVATE(self);
	if(priv->ddGic){
		g_object_unref(priv->ddGic);
		priv->ddGic=NULL;
	}
	G_OBJECT_CLASS(ct_dd_gic_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtDdGic *self = (CtDdGic*)object;
//	CtDdGicPrivate *priv = CT_DD_GIC_GET_PRIVATE(self);
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
void ct_dd_gic_main_main(CtDdGic* self, gint argc, gchar** argv)
{
	gint32  dat;
	guint32 regNum;

	guint32 sho;
	guint32 intid;
	guint32 setEnable;
	gint32  intrptPri;
	gint32  cpuTarget;
	guint32 targetFilter;

	switch ( strtol(argv[1], NULL, 16) ) {
		case 1:		// Init
			Ddim_Print(("Dd_GIC_Init Test Start\n"));
			Dd_GIC_Init();

			// GICD_ICENABLER
			dat = DdGic_DIST_GET_ICENABLER(0);
			Ddim_Print(("GICD_ICENABLER[0] = 0x%08x (set 0x0000FFFF:SGI Enable)\n", dat));

			for(regNum=1; regNum<(C_INTID_MAX/32); regNum++){
				dat = DdGic_DIST_GET_ICENABLER(regNum);
				Ddim_Print(("GICD_ICENABLER[%d] = 0x%08x (set 0x00000000)\n", regNum, dat));
			}

			// GICD_ICPENDR
			dat = DdGic_DIST_GET_ICPENDR(0);
			Ddim_Print(("GICD_ICPENDR[0] = 0x%08x (set 0x00000000:SGI and PPI Pending)\n", dat));

			for(regNum=0; regNum<(C_INTID_MAX/32); regNum++){
				dat = DdGic_DIST_GET_ICPENDR(regNum);
				Ddim_Print(("GICD_ICPENDR[%d] = 0x%08x (set 0x00000000)\n", regNum, dat));
			}

			// GICD_IPRIORITYR
			for(regNum=0; regNum<C_INTID_MAX; regNum++){
				dat = DdGic_DIST_GET_IPRIORITYR(regNum);
				Ddim_Print(("GICD_IPRIORITYR[%d] = 0x%02x (set 0x00)\n", regNum, dat));
			}

			// GICD_ITARGETSR
			for(regNum=32; regNum<C_INTID_MAX; regNum++){
				dat = DdGic_DIST_GET_ITARGETSR(regNum);
				Ddim_Print(("GICD_ITARGETSR[%d] = %d (set 0)\n", regNum, dat));
			}

			// GICD_ICFGR
			dat = DdGic_DIST_GET_ICFGR(0);
			Ddim_Print(("ICDICFR[0] = 0x%08x (set 0xaaaaaaaa)\n", dat));

			dat = DdGic_DIST_GET_ICFGR(1);
			Ddim_Print(("ICDICFR[1] = 0x%08x (set 0x7dc00000)\n", dat));

			for(regNum=2; regNum<(C_INTID_MAX/16); regNum++){
				dat = DdGic_DIST_GET_ICFGR(regNum);
				Ddim_Print(("ICDICFR[%d] = 0x%08x (set 0x55555555)\n", regNum, dat));
			}

			// GICC_PMR
			dat = DdGic_CPU_GET_PMR_PRIORITY;
			Ddim_Print(("GICC_PMR = 0x%02x (set 0xF8)\n", dat));

			// GICC_BPR
			dat = DdGic_CPU_GET_BPR_BINARYPOINT;
			Ddim_Print(("GICC_BPR = %d (set 2)\n", dat));

			// GICC_IAR
			dat = DdGic_CPU_GET_IAR;
			Ddim_Print(("GICC_IAR = 0x%08x (set 0x00000000)\n", dat));

			// GICD_CTLR
			dat = DdGic_DIST_GET_CTLR_ENABLEGRP0;
			Ddim_Print(("GICD_CTLR EnableGrp0 = %d (set 1)\n", dat));
			dat = DdGic_DIST_GET_CTLR_ENABLEGRP1;
			Ddim_Print(("GICD_CTLR EnableGrp1 = %d (set 0)\n", dat));

			// GICC_CTLR
			dat = DdGic_CPU_GET_CTLR_ENABLEGRP0;
			Ddim_Print(("GICC_CTLR EnableGrp0 = %d (set 1)\n", dat));
			dat = DdGic_CPU_GET_CTLR_ENABLEGRP1;
			Ddim_Print(("GICC_CTLR EnableGrp1 = %d (set 0)\n", dat));

			Ddim_Print(("Dd_GIC_Init Test End\n"));
			break;

		case 2:		// Ctrl
			Ddim_Print(("dd_gic_ctrl Test Start\n"));
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
			if( dd_gic_ctrl(priv->ddGic, (E_DD_GIC_INTID)intid, setEnable,
					intrptPri, cpuTarget ) == DriverCommon_D_DDIM_OK ){
				dat = DdGic_DIST_GET_IPRIORITYR(intid);
				Ddim_Print(("GICD_IPRIORITYR[%u] = 0x%02x\n", intid, dat));
				dat = DdGic_DIST_GET_ITARGETSR(intid);
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
			dat = DdGic_DIST_GET_CTLR_ENABLEGRP0;
			Ddim_Print(("GICD_CTLR EnableGrp0 = %d (set 0)\n", dat));
			dat = DdGic_DIST_GET_CTLR_ENABLEGRP1;
			Ddim_Print(("GICD_CTLR EnableGrp1 = %d (set 0)\n", dat));

			// GICC_CTLR
			dat = DdGic_CPU_GET_CTLR_ENABLEGRP0;
			Ddim_Print(("GICC_CTLR EnableGrp0 = %d (set 0)\n", dat));
			dat = DdGic_CPU_GET_CTLR_ENABLEGRP1;
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
			dat = dd_gic_send_sgi(priv->ddGic, (E_DD_GIC_INTID)intid, targetFilter, cpuTarget);

			Ddim_Print(("SGI Test End\n"));
			break;

		case 5:		// DIST & CPU
			Ddim_Print(("--------DIST-------\n"));

			// GICD_TYPER
			dat = DdGic_DIST_GET_TYPER_ITLINESNUMBER;
			Ddim_Print(("GICD_TYPER Get ITLINESNUMBER = %d\n", dat));
			dat = DdGic_DIST_GET_TYPER_CPUNUMBER;
			Ddim_Print(("GICD_TYPER Get CPUNUMBER = %d\n", dat));
			dat = DdGic_DIST_GET_TYPER_SECURITYEXTN;
			Ddim_Print(("GICD_TYPER Get SECURITY_EXTN = %d\n", dat));
			dat = DdGic_DIST_GET_TYPER_LSPI;
			Ddim_Print(("GICD_TYPER Get LSPI = %d\n", dat));

			// GICD_IIDR
			dat = DdGic_DIST_GET_IIDR_IMPLEMENTER;
			Ddim_Print(("GICD_IIDR Get IMPLEMENTER = %d\n", dat));
			dat = DdGic_DIST_GET_IIDR_REVISION;
			Ddim_Print(("GICD_IIDR Get REVISION = %d\n", dat));
			dat = DdGic_DIST_GET_IIDR_VARIANT;
			Ddim_Print(("GICD_IIDR Get VARIANT = %d\n", dat));
			dat = DdGic_DIST_GET_IIDR_PRODUCTID;
			Ddim_Print(("GICD_IIDR Get PRODUCTID = %d\n", dat));

			// GICD_IGROUPR
			dat = DdGic_DIST_GET_IGROUPR(1);
			Ddim_Print(("GICD_IGROUPR Get = %d\n", dat));

			// GICD_ISPENDR
			// GICD_ICPENDR
			DdGic_DIST_SET_ISPENDR(1, 1);
			dat = DdGic_DIST_GET_ISPENDR(1);
			Ddim_Print(("GICD_ISPENDR Get = 0x%08x\n", dat));
			DdGic_DIST_SET_ICPENDR(1, 1);
			dat = DdGic_DIST_GET_ICPENDR(1);
			Ddim_Print(("GICD_ICPENDR Get = 0x%08x\n", dat));

			// GICD_ISACTIVER
			// GICD_ICACTIVER
			DdGic_DIST_SET_ISACTIVER(2, 0x80000000);
			dat = DdGic_DIST_GET_ISACTIVER(2);
			Ddim_Print(("GICD_ISACTIVER Get = 0x%08x\n", dat));
			DdGic_DIST_SET_ICACTIVER(2, 0x80000000);
			dat = DdGic_DIST_GET_ICACTIVER(2);
			Ddim_Print(("GICD_ICACTIVER Get = 0x%08x\n", dat));

			// GICD_PPISR
			dat =  DdGic_DIST_GET_SPISR(1);
			Ddim_Print(("GICD_SPISR Get = 0x%08x\n", dat));

			// GICD_SPISR
			dat =  DdGic_DIST_GET_PPISR;
			Ddim_Print(("GICD_PPISR Get = 0x%08x\n", dat));

			// GICD_SPENDSGIR
			// GICD_CPENDSGIR
			DdGic_DIST_SET_SPENDSGIR(0, 1);
			dat = DdGic_DIST_GET_SPENDSGIR(0);
			Ddim_Print(("GICD_SPENDSGIR Get = 0x%08x\n", dat));
			DdGic_DIST_SET_CPENDSGIR(0, 1);
			dat = DdGic_DIST_GET_CPENDSGIR(0);
			Ddim_Print(("GICD_CPENDSGIR Get = 0x%08x\n", dat));

			Ddim_Print(("-------------------\n"));

			Ddim_Print(("--------CPU--------\n"));

			// GICC_CTLR
			DdGic_CPU_SET_CTLR_ACKCTL(1);
			dat = DdGic_CPU_GET_CTLR_ACKCTL;
			Ddim_Print(("GICC_CTLR Get ACKCTL = %d\n", dat));
			//Dd_GIC_CPU_Set_Ctlr_Fiqen(1);
			//dat = Dd_GIC_CPU_Get_Ctlr_Fiqen;
			//dim_Print(("GICC_CTLR Get FIQEN = %d\n", dat));
			DdGic_CPU_SET_CTLR_SBPR(1);
			dat = DdGic_CPU_GET_CTLR_SBPR;
			Ddim_Print(("GICC_CTLR Get CBPR = %d\n", dat));
			DdGic_CPU_SET_CTLR_FIQBYDISGRP0(1);
			dat = DdGic_CPU_GET_CTLR_FIQBYDISGRP0;
			Ddim_Print(("GICC_CTLR Get FIQBYPDISGRP0 = %d\n", dat));
			DdGic_CPU_SET_CTLR_IRQBYDISGRP0(1);
			dat = DdGic_CPU_GET_CTLR_IRQBYDISGRP0;
			Ddim_Print(("GICC_CTLR Get IRQBYPDISGRP0 = %d\n", dat));
			DdGic_CPU_SET_CTLR_FIQBYDISGRP1(1);
			dat = DdGic_CPU_GET_CTLR_FIQBYDISGRP1;
			Ddim_Print(("GICC_CTLR Get FIQBYPDISGRP1 = %d\n", dat));
			DdGic_CPU_SET_CTLR_IRQBYDISGRP1(1);
			dat = DdGic_CPU_GET_CTLR_IRQBYDISGRP1;
			Ddim_Print(("GICC_CTLR Get IRQBYPDISGRP1 = %d\n", dat));
			DdGic_CPU_SET_CTLR_EOIMODES(1);
			dat = DdGic_CPU_GET_CTLR_EOIMODES;
			Ddim_Print(("GICC_CTLR Get EOIMODES = %d\n", dat));
			DdGic_CPU_SET_CTLR_EOIMODENS(1);
			dat = DdGic_CPU_GET_CTLR_EOIMODENS;
			Ddim_Print(("GICC_CTLR Get EOIMODENS = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_IAR
			dat = DdGic_CPU_GET_IAR;
			Ddim_Print(("GICC_IAR Get %d\n", dat));
			dat = DdGic_CPU_GET_IAR_ACKINTID;
			Ddim_Print(("GICC_IAR Get ACKINTID = %d\n", dat));
			dat = DdGic_CPU_GET_IAR_CPUID;
			Ddim_Print(("GICC_IAR Get CPUID = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_EOIR
			DdGic_CPU_SET_EOIR(0x00000401);
			Ddim_Print(("GICC_EOIR Set = 0x00000401\n"));
			DdGic_CPU_SET_EOIR_EOIINTID(1);
			Ddim_Print(("GICC_EOIR Set EOIINTID = 1\n"));
			DdGic_CPU_SET_EOIR_CPUID(1);
			Ddim_Print(("GICC_EOIR Set CPUID = 1\n"));

			Ddim_Print(("-------------------\n"));

			// GICC_RPR
			dat = DdGic_CPU_GET_RPR_PRIORITY;
			Ddim_Print(("GICC_RPR Get PRIORITY = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_HPPIR
			dat = DdGic_CPU_GET_HPPIR_PENDINTID;
			Ddim_Print(("GICC_HPPIR Get PENDINTID = %d\n", dat));
			dat = DdGic_CPU_GET_HPPIR_CPUID;
			Ddim_Print(("GICC_HPPIR Get CPUID = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_ABPR
			DdGic_CPU_SET_ABPR_BINARYPOINT(4);
			dat = DdGic_CPU_GET_ABPR_BINARYPOINT;
			Ddim_Print(("GICC_ABPR Get BINARYPOINT = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_AIAR
			dat = DdGic_CPU_GET_AIAR;
			Ddim_Print(("GICC_AIAR Get %d\n", dat));
			dat = DdGic_CPU_GET_AIAR_ACKINTID;
			Ddim_Print(("GICC_AIAR Get ACKINTID = %d\n", dat));
			dat = DdGic_CPU_GET_AIAR_CPUID;
			Ddim_Print(("GICC_AIAR Get CPUID = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_AEOIR
			DdGic_CPU_SET_AEOIR(0x00000401);
			Ddim_Print(("GICC_AEOIR Set = 0x00000401\n"));
			DdGic_CPU_SET_AEOIR_EOIINTID(1);
			Ddim_Print(("GICC_AEOIR Set EOIINTID = 1\n"));
			DdGic_CPU_SET_AEOIR_CPUID(1);
			Ddim_Print(("GICC_AEOIR Set CPUID = 1\n"));

			Ddim_Print(("-------------------\n"));

			// GICC_AHPPIR
			dat = DdGic_CPU_GET_AHPPIR_PENDINTID;
			Ddim_Print(("GICC_AHPPIR Get PENDINTID = %d\n", dat));
			dat = DdGic_CPU_GET_AHPPIR_CPUID;
			Ddim_Print(("GICC_AHPPIR Get CPUID = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_APR0
			DdGic_CPU_SET_APR0(1);
			dat = DdGic_CPU_GET_APR0;
			Ddim_Print(("GICC_APR0 Get = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_NSAPR0
			DdGic_CPU_SET_NSAPR0(1);
			dat = DdGic_CPU_GET_NSAPR0;
			Ddim_Print(("GICC_NSAPR0 Get = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_IIDR
			dat = DdGic_CPU_GET_IIDR_IMPLEMENTER;
			Ddim_Print(("GICC_IIDR Get IMPLEMENTER = %d\n", dat));
			dat = DdGic_CPU_GET_IIDR_REVISION;
			Ddim_Print(("GICC_IIDR Get REVISION = %d\n", dat));
			dat = DdGic_CPU_GET_IIDR_VERSION;
			Ddim_Print(("GICC_IIDR Get VERSION = %d\n", dat));
			dat = DdGic_CPU_GET_IIDR_PRODUCTID;
			Ddim_Print(("GICC_IIDR Get PRODUCTID = %d\n", dat));

			Ddim_Print(("-------------------\n"));

			// GICC_DIR
			DdGic_CPU_SET_DIR(1);
			Ddim_Print(("GICC_DIR Set = 1\n"));

			Ddim_Print(("-------------------\n"));
			break;

		case 6:		// Error Test
			Ddim_Print(("Dd_GIC_Ctrl Error Test\n"));
			dat = dd_gic_ctrl(priv->ddGic, (E_DD_GIC_INTID)(D_DD_GIC_INTID_SPI_MAX + 1), 1, D_DD_GIC_PRI31, 3);
			Ddim_Print(("Arg1 Test = 0x%08x\n", dat));
			dat = dd_gic_ctrl(priv->ddGic, (E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, 2, D_DD_GIC_PRI31, 3);
			Ddim_Print(("Arg2 Test = 0x%08x\n", dat));
			dat = dd_gic_ctrl(priv->ddGic, (E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, 1, (D_DD_GIC_PRI31 + 1), 3);
			Ddim_Print(("Arg3_Max Test = 0x%08x\n", dat));
			dat = dd_gic_ctrl(priv->ddGic, (E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, 1, -2, 3);
			Ddim_Print(("Arg3_Min Test = 0x%08x\n", dat));
			dat = dd_gic_ctrl(priv->ddGic, (E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, 1, D_DD_GIC_PRI31, 16);
			Ddim_Print(("Arg4_Max Test = 0x%08x\n", dat));
			dat = dd_gic_ctrl(priv->ddGic, (E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, 1, D_DD_GIC_PRI31, -2);
			Ddim_Print(("Arg4_Min Test = 0x%08x\n", dat));

			Ddim_Print(("Dd_GIC_Set_Priority Error Test\n"));
			dat = dd_gic_set_priority(priv->ddGic, (E_DD_GIC_INTID)(D_DD_GIC_INTID_SPI_MAX + 1), D_DD_GIC_PRI31);
			Ddim_Print(("Arg1 Test = 0x%08x\n", dat));
			dat = dd_gic_set_priority(priv->ddGic, (E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, (D_DD_GIC_PRI31 + 1));
			Ddim_Print(("Arg2_Max Test = 0x%08x\n", dat));
			dat = dd_gic_set_priority(priv->ddGic, (E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, -2);
			Ddim_Print(("Arg2_Min Test = 0x%08x\n", dat));

			Ddim_Print(("Dd_GIC_Set_Target_Cpu Error Test\n"));
			dat = dd_gic_set_target_cpu(priv->ddGic, (E_DD_GIC_INTID)(D_DD_GIC_INTID_SPI_MAX + 1), D_DD_GIC_PRI31);
			Ddim_Print(("Arg1 Test = 0x%08x\n", dat));
			dat = dd_gic_set_target_cpu(priv->ddGic, (E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, 16);
			Ddim_Print(("Arg2_Max Test = 0x%08x\n", dat));
			dat = dd_gic_set_target_cpu(priv->ddGic, (E_DD_GIC_INTID)D_DD_GIC_INTID_SPI_MAX, -2);
			Ddim_Print(("Arg2_Min Test = 0x%08x\n", dat));

			Ddim_Print(("Dd_GIC_Send_Sgi Error Test\n"));
			dat = dd_gic_send_sgi(priv->ddGic, (E_DD_GIC_INTID)(D_DD_GIC_INTID_SGI_MAX + 1), 2, 3);
			Ddim_Print(("Arg1 Test = 0x%08x\n", dat));
			dat = dd_gic_send_sgi(priv->ddGic, (E_DD_GIC_INTID)D_DD_GIC_INTID_SGI_MAX, 3, 3);
			Ddim_Print(("Arg2 Test = 0x%08x\n", dat));
			dat = dd_gic_send_sgi(priv->ddGic, (E_DD_GIC_INTID)D_DD_GIC_INTID_SGI_MAX, 2, 16);
			Ddim_Print(("Arg3 Test = 0x%08x\n", dat));
			break;

		default :
			Ddim_Print(("please check 1st parameter!!\n"));
	}
}

CtDdGic *ct_dd_gic_new(void) 
{
    CtDdGic *self = g_object_new(CT_TYPE_DD_GIC, NULL);
    return self;
}
