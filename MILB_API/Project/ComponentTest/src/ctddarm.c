/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :jianghaodong
*@brief               :CtDdArm类
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
#include "dd_arm.h"
#include "dd_timestamp.h"

#include "ctddarm.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdArm, ct_dd_arm);
#define CT_DD_ARM_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdArmPrivate,CT_TYPE_DD_ARM))

struct _CtDdArmPrivate
{
};


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
static kulong S_GCT_ARM_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));

/*
*IMPL
*/
static void ct_dd_arm_constructor(CtDdArm *self) 
{
}

static void ct_dd_arm_destructor(CtDdArm *self) 
{
}

/*
*PUBLIC
*/
/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
/**
 * @brief  Command main function for ARM test.
 * @param  int argc	:The number of parameters
 *		   char** argv	:The value of parameters
 * @return void
 *
 *			The meaning of parameters
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| P1              | P2   | P3   |Meaning                                                    |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| eidi            |      |      |IRQ enable & disable.                                      |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| spinlock        |      |      |Spin lock & unlock.                                        |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| critical        |      |      |Spin lock & unlock / IRQ enable & disable.                 |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| cpuid           |      |      |Get CPU ID.                                                |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| ttb             |      |      |Get TTB.                                                   |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| vector          |      |      |Change Vector address.                                     |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1prefetch      |      |      |L1 Prefetch enable & disable.                              |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| eifdif          |      |      |IRQ/FIQ enable & disable.                                  |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| mmu             |      |      |MMU enable & disable.                                      |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| waitns          |      |      |Wait nsec.                                                 |
 *		+-----------------+------+------+-----------------------------------------------------------+
 */
void ct_dd_arm_main_main(CtDdArm* self, kint argc, kchar** argv)
{
	kint32 ret;
	kuint32 sr1;
	kuint32 sr2;
	kuint32 r0=0;
	kuint32 r1=0;

	if( argc < 2 ) {
		Ddim_Print(("please check 1st parameter!!\n"));
	}
	else if( 0 == strcmp( argv[1], "eidi" ) ) {
		Ddim_Print(("interrupt disable start\n"));
		sr1 = Dd_ARM_DI();
		sr2 = Dd_ARM_DI();
		Ddim_Print(("interrupt disable sr1:0x%08x\n", sr1));
		Ddim_Print(("interrupt disable sr2:0x%08x\n", sr2));
		Ddim_Print(("interrupt disable end\n"));
		Ddim_Print(("interrupt enable start\n"));
		Dd_ARM_EI(sr2);
#ifndef CO_DEBUG_ON_PC
		__asm__ __volatile__(
			"MRS     %0, cpsr;"
			:"=r"(r0)
		);
#endif
		Dd_ARM_EI(sr1);
#ifndef CO_DEBUG_ON_PC
		__asm__ __volatile__(
			"MRS     %0, cpsr;"
			:"=r"(r1)
		);
#endif
		Ddim_Print(("interrupt enable r0:0x%08x\n", r0));
		Ddim_Print(("interrupt enable r1:0x%08x\n", r1));
		Ddim_Print(("interrupt enable end\n"));
	}
	else if( 0 == strcmp( argv[1], "spinlock" ) ) {
		Ddim_Print(("Dd_ARM_Spin_Lock start\n"));
		Dd_ARM_Spin_Lock(&S_GCT_ARM_SPIN_LOCK);
		Ddim_Print(("Dd_ARM_Spin_Lock val:%lu\n", S_GCT_ARM_SPIN_LOCK));
		Ddim_Print(("Dd_ARM_Spin_Lock end\n"));
		Ddim_Print(("Dd_ARM_Spin_Unlock start\n"));
		Dd_ARM_Spin_Unlock(&S_GCT_ARM_SPIN_LOCK);
		Ddim_Print(("Dd_ARM_Spin_Unlock val:%lu\n", S_GCT_ARM_SPIN_LOCK));
		Ddim_Print(("Dd_ARM_Spin_Unlock end\n"));
	}
	else if( 0 == strcmp( argv[1], "critical" ) ) {
		Ddim_Print(("Dd_ARM_Critical_Section_Start start\n"));
		Dd_ARM_Critical_Section_Start(S_GCT_ARM_SPIN_LOCK);
		Ddim_Print(("Dd_ARM_Critical_Section_Start val:%lu\n", S_GCT_ARM_SPIN_LOCK));
		Ddim_Print(("Dd_ARM_Critical_Section_Start end\n"));
		Ddim_Print(("Dd_ARM_Critical_Section_End start\n"));
		Dd_ARM_Critical_Section_End(S_GCT_ARM_SPIN_LOCK);
		Ddim_Print(("Dd_ARM_Critical_Section_End val:%lu\n", S_GCT_ARM_SPIN_LOCK));
		Ddim_Print(("Dd_ARM_Critical_Section_End end\n"));
	}
	else if( 0 == strcmp( argv[1], "cpuid" ) ) {
		Ddim_Print(("Dd_ARM_Get_CPU_ID start\n"));
		ret = Dd_ARM_Get_CPU_ID();
		Ddim_Print(("Dd_ARM_Get_CPU_ID CPU ID:%d\n", ret));
		Ddim_Print(("Dd_ARM_Get_CPU_ID end\n"));
	}
	else if( 0 == strcmp( argv[1], "ttb" ) ) {
		Ddim_Print(("Dd_ARM_Get_TTB start\n"));
		ret = Dd_ARM_Get_TTB();
		Ddim_Print(("Dd_ARM_Get_TTB TTB:0x%08x\n", ret));
		Ddim_Print(("Dd_ARM_Get_TTB end\n"));
	}
	else if( 0 == strcmp( argv[1], "vector" ) ) {
		Ddim_Print(("Dd_ARM_Change_Vector_Table start\n"));
		Dd_ARM_Change_Vector_Table(0xa0000000);
#ifndef CO_DEBUG_ON_PC
		__asm__ __volatile__(
			"MRC     p15, 0, %0, c12, c0, 0;"
			:"=r"(r0)
		);
#endif
		Ddim_Print(("Dd_ARM_Change_Vector_Table Vector:0x%08x\n", r0));
		Ddim_Print(("Dd_ARM_Change_Vector_Table end\n"));
	}
	else if( 0 == strcmp( argv[1], "l1prefetch" ) ) {
		Ddim_Print(("Dd_ARM_L1_Prefetch_Enable start\n"));
		Dd_ARM_L1_Prefetch_Enable();
#ifndef CO_DEBUG_ON_PC
		__asm__ __volatile__(
			"MRC		p15, 0, %0, c1, c0, 1;"
			:"=r"(r0)
		);
#endif
		Ddim_Print(("Dd_ARM_L1_Prefetch_Enable val:%d\n", r0));
		Ddim_Print(("Dd_ARM_L1_Prefetch_Enable end\n"));
		Ddim_Print(("Dd_ARM_L1_Prefetch_Disable start\n"));
		Dd_ARM_L1_Prefetch_Disable();
#ifndef CO_DEBUG_ON_PC
		__asm__ __volatile__(
			"MRC		p15, 0, %0, c1, c0, 1;"
			:"=r"(r0)
		);
#endif
		Ddim_Print(("Dd_ARM_L1_Prefetch_Disable val:%d\n", r0));
		Ddim_Print(("Dd_ARM_L1_Prefetch_Disable end\n"));
	}
	else if( 0 == strcmp( argv[1], "eifdif" ) ) {
		Ddim_Print(("interrupt disable start\n"));
		sr1 = Dd_ARM_DIF();
		sr2 = Dd_ARM_DIF();
		Ddim_Print(("interrupt disable sr1:0x%08x\n", sr1));
		Ddim_Print(("interrupt disable sr2:0x%08x\n", sr2));
		Ddim_Print(("interrupt disable end\n"));
		Ddim_Print(("interrupt enable start\n"));
		Dd_ARM_EIF(sr2);
#ifndef CO_DEBUG_ON_PC
		__asm__ __volatile__(
			"MRS     %0, cpsr;"
			:"=r"(r0)
		);
#endif
		Dd_ARM_EIF(sr1);
#ifndef CO_DEBUG_ON_PC
		__asm__ __volatile__(
			"MRS     %0, cpsr;"
			:"=r"(r1)
		);
#endif
		Ddim_Print(("interrupt enable r0:0x%08x\n", r0));
		Ddim_Print(("interrupt enable r1:0x%08x\n", r1));
		Ddim_Print(("interrupt enable end\n"));
	}
	else if( 0 == strcmp( argv[1], "mmu" ) ) {
//		Ddim_Print(("Dd_ARM_MMU_Disable start\n"));
		Dd_ARM_MMU_Disable();
#ifndef CO_DEBUG_ON_PC
		__asm__ __volatile__(
			"MRC		p15, 0, %0, c1, c0, 0;"
			:"=r"(r0)
		);
#endif
//		Ddim_Print(("Dd_ARM_MMU_Disable val:%d\n", r0));
//		Ddim_Print(("Dd_ARM_MMU_Disable end\n"));
//		Ddim_Print(("Dd_ARM_MMU_Enable start\n"));
		Dd_ARM_MMU_Enable();
#ifndef CO_DEBUG_ON_PC
		__asm__ __volatile__(
			"MRC		p15, 0, %0, c1, c0, 0;"
			:"=r"(r0)
		);
#endif
		Ddim_Print(("Dd_ARM_MMU_Enable val:%d\n", r0));
//		Ddim_Print(("Dd_ARM_MMU_Enable end\n"));
	}
	else if( 0 == strcmp( argv[1], "waitns" ) ) {
		UINT64 timestamp_counter_1;
		UINT64 timestamp_counter_2;
		kulong timestamp;

		Ddim_Print(("Dd_ARM_Wait_ns start\n"));

		Dd_TIMESTAMP_Get_Counter( &timestamp_counter_1 );
	    timestamp_counter_1 = (timestamp_counter_1 / 40) * 1000;  // 40MHz

		Dd_ARM_Wait_ns(1000);
		Dd_TIMESTAMP_Get_Counter( &timestamp_counter_2 );
	    timestamp_counter_2 = (timestamp_counter_2 / 40) * 1000;  // 40MHz
	    timestamp = (kulong)(timestamp_counter_2 - timestamp_counter_1);
	    Ddim_Print(("timestamp_counter %ld ns\n", timestamp));

	    Dd_ARM_Wait_ns(10000);
	    Dd_TIMESTAMP_Get_Counter( &timestamp_counter_1 );
	    timestamp_counter_1 = (timestamp_counter_1 / 40) * 1000;  // 40MHz
	    timestamp = (kulong)(timestamp_counter_1 - timestamp_counter_2);
	    Ddim_Print(("timestamp_counter %ld ns\n", timestamp));

		Dd_ARM_Wait_ns(100000);
	    Dd_TIMESTAMP_Get_Counter( &timestamp_counter_2 );
	    timestamp_counter_2 = (timestamp_counter_2 / 40) * 1000;  // 40MHz
	    timestamp = (kulong)(timestamp_counter_2 - timestamp_counter_1);
	    Ddim_Print(("timestamp_counter %ld ns\n", timestamp));

		Dd_ARM_Wait_ns(200000);
	    Dd_TIMESTAMP_Get_Counter( &timestamp_counter_1 );
	    timestamp_counter_1 = (timestamp_counter_1 / 40) * 1000;  // 40MHz
	    timestamp = (kulong)(timestamp_counter_1 - timestamp_counter_2);
	    Ddim_Print(("timestamp_counter %ld ns\n", timestamp));

		Ddim_Print(("Dd_ARM_Wait_ns end\n"));
	}
	else
	{
		Ddim_Print(("please check 1st parameter!!\n"));
	}
}

CtDdArm* ct_dd_arm_new(void) 
{
    CtDdArm *self = k_object_new_with_private(CT_TYPE_DD_ARM, sizeof(CtDdArmPrivate));
    return self;
}
