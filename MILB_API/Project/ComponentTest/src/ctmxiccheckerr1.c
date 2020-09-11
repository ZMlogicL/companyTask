/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :jianghaodong
*@brief               :CtMxicCheckErr1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "im_mxic.h"
#include "ct_im_mxic.h"
#include <string.h>
#include <stdlib.h>

#include "dd_top.h"

#include "ddim_user_custom.h"

#include "ctimmxiccreate.h"
#include "ctmxiccheckerr1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtMxicCheckErr1, ct_mxic_check_err1);
#define CT_MXIC_CHECK_ERR1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtMxicCheckErr1Private,CT_TYPE_MXIC_CHECK_ERR1))

struct _CtMxicCheckErr1Private
{

};

/*
*IMPL
*/
static void ct_mxic_check_err1_constructor(CtMxicCheckErr1 *self) 
{
}

static void ct_mxic_check_err1_destructor(CtMxicCheckErr1 *self) 
{
}

/*
*PUBLIC
*/
// Error test of Im_MXIC_Start_Config function.
void ct_mxic_check_err1_start_config(void)
{
	kint32						result;
	T_IM_MXIC_CONFIG_ARBITER	config;

	// unit check
	Ddim_Print(("----[Im_MXIC_Start_Config(): unit check]----\n"));
	result = Im_MXIC_Start_Config( (E_IM_MXIC_UNIT)7, &config );
	Ddim_Print(("result=%d\n", result));

	// NULL check
	Ddim_Print(("----[Im_MXIC_Start_Config(): NULL check]----\n"));
	result = Im_MXIC_Start_Config( (E_IM_MXIC_UNIT)0, NULL );
	Ddim_Print(("result=%d\n", result));
	return;
}

// Error test of Im_MXIC_Set_Clock_Enable and Im_MXIC_Get_Clock_Enable function.
void ct_mxic_check_err1_clock_enable(void)
{
	kint32			result;
	T_IM_MXIC_CLOCK	clockCtrl;

	// unit check
	Ddim_Print(("----[Im_MXIC_Set_Clock_Enable(): unit check]----\n"));
	result = Im_MXIC_Set_Clock_Enable( (E_IM_MXIC_UNIT)7, &clockCtrl );
	Ddim_Print(("result=%d\n", result));

	// unit check
	Ddim_Print(("----[Im_MXIC_Get_Clock_Enable(): unit check]----\n"));
	result = Im_MXIC_Get_Clock_Enable( (E_IM_MXIC_UNIT)7, &clockCtrl );
	Ddim_Print(("result=%d\n", result));

	// NULL check
	Ddim_Print(("----[Im_MXIC_Set_Clock_Enable(): NULL check]----\n"));
	result = Im_MXIC_Set_Clock_Enable( (E_IM_MXIC_UNIT)0, NULL );
	Ddim_Print(("result=%d\n", result));

	// NULL check
	Ddim_Print(("----[Im_MXIC_Get_Clock_Enable(): NULL check]----\n"));
	result = Im_MXIC_Get_Clock_Enable( (E_IM_MXIC_UNIT)0, NULL );
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Acceptance_Capability and Im_MXIC_Get_Acceptance_Capability function.
void ct_mxic_check_err1_acceptance_capability(void)
{
	kint32 result;
	kuchar capability;

	// --- Im_MXIC_Set_Acceptance_Capability ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability(): unit range error check]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability((E_IM_MXIC_UNIT)7, E_IM_MXIC_WR_ARBITER_W,
			E_IM_MXIC_SPEC_ARBITER_1, E_IM_MXIC_PORT_0, 8);
	Ddim_Print(("result=%d\n", result));

	// write or read arbiter range error check
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability(): wr_arbiter range error check]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_MAX,
			E_IM_MXIC_SPEC_ARBITER_1, E_IM_MXIC_PORT_0, 8);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability(): arbiter range error check]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_W,
			E_IM_MXIC_SPEC_ARBITER_MAX, E_IM_MXIC_PORT_0, 8);
	Ddim_Print(("result=%d\n", result));

	// port range error check
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability(): port range error check]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_W,
			E_IM_MXIC_SPEC_ARBITER_2, E_IM_MXIC_PORT_MAX, 1);
	Ddim_Print(("result=%d\n", result));

	// capability range error check(Min)
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability(): capability range error check(Min)]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_R,
			E_IM_MXIC_SPEC_ARBITER_3, E_IM_MXIC_PORT_1, 0);
	Ddim_Print(("result=%d\n", result));

	// capability range error check(Max)
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability(): capability range error check(Max)]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_R,
			E_IM_MXIC_SPEC_ARBITER_4, E_IM_MXIC_PORT_1, 9);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Acceptance_Capability ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Get_Acceptance_Capability(): unit range error check]----\n"));
	result = Im_MXIC_Get_Acceptance_Capability((E_IM_MXIC_UNIT)7, E_IM_MXIC_WR_ARBITER_W,
			E_IM_MXIC_SPEC_ARBITER_1, E_IM_MXIC_PORT_0, &capability);
	Ddim_Print(("result=%d\n", result));

	// write or read arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Acceptance_Capability(): wr_arbiter range error check]----\n"));
	result = Im_MXIC_Get_Acceptance_Capability((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_MAX,
			E_IM_MXIC_SPEC_ARBITER_1, E_IM_MXIC_PORT_0, &capability);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Acceptance_Capability(): arbiter range error check]----\n"));
	result = Im_MXIC_Get_Acceptance_Capability((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_W,
			E_IM_MXIC_SPEC_ARBITER_MAX, E_IM_MXIC_PORT_0, &capability);
	Ddim_Print(("result=%d\n", result));

	// port range error check
	Ddim_Print(("----[Im_MXIC_Get_Acceptance_Capability(): port range error check]----\n"));
	result = Im_MXIC_Get_Acceptance_Capability((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_W,
			E_IM_MXIC_SPEC_ARBITER_2, E_IM_MXIC_PORT_MAX, &capability);
	Ddim_Print(("result=%d\n", result));

	// capability NULL check
	Ddim_Print(("----[Im_MXIC_Get_Acceptance_Capability(): capability NULL check]----\n"));
	result = Im_MXIC_Get_Acceptance_Capability((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_R,
			E_IM_MXIC_SPEC_ARBITER_3, E_IM_MXIC_PORT_1, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Acceptance_Capability_Group and Im_MXIC_Get_Acceptance_Capability_Group function.
void ct_mxic_check_err1_acceptance_capability_group(void)
{
	kint32 result;
	kuchar capability;

	// --- Im_MXIC_Set_Acceptance_Capability ---
	// write or read arbiter range error check
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability_Group(): wr_arbiter range error check]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability_Group(E_IM_MXIC_WR_ARBITER_MAX, E_IM_MXIC_SPEC_ARBITER_GR_0,
			E_IM_MXIC_PORT_GR_0, 8);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability_Group(): arbiter range error check]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability_Group(E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_GR_MAX,
			E_IM_MXIC_PORT_GR_0, 8);
	Ddim_Print(("result=%d\n", result));

	// port range error check
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability_Group(): port range error check]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability_Group(E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_GR_1,
			E_IM_MXIC_PORT_GR_MAX, 1);
	Ddim_Print(("result=%d\n", result));

	// capability range error check(Min)
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability_Group(): capability range error check(Min)]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability_Group(E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_GR_1,
			E_IM_MXIC_PORT_GR_1, 0);
	Ddim_Print(("result=%d\n", result));

	// capability range error check(Max)
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability_Group(): capability range error check(Max)]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability_Group(E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_GR_2,
			E_IM_MXIC_PORT_GR_1, 9);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Acceptance_Capability ---
	// write or read arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Acceptance_Capability_Group(): wr_arbiter range error check]----\n"));
	result = Im_MXIC_Get_Acceptance_Capability_Group(E_IM_MXIC_WR_ARBITER_MAX, E_IM_MXIC_SPEC_ARBITER_GR_0,
			E_IM_MXIC_PORT_GR_0, &capability);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Acceptance_Capability_Group(): arbiter range error check]----\n"));
	result = Im_MXIC_Get_Acceptance_Capability_Group(E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_GR_MAX,
			E_IM_MXIC_PORT_GR_0, &capability);
	Ddim_Print(("result=%d\n", result));

	// port range error check
	Ddim_Print(("----[Im_MXIC_Get_Acceptance_Capability_Group(): port range error check]----\n"));
	result = Im_MXIC_Get_Acceptance_Capability_Group(E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_GR_0,
			E_IM_MXIC_PORT_GR_MAX, &capability);
	Ddim_Print(("result=%d\n", result));

	// capability NULL check
	Ddim_Print(("----[Im_MXIC_Get_Acceptance_Capability(): capability NULL check]----\n"));
	result = Im_MXIC_Get_Acceptance_Capability_Group(E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_GR_1,
			E_IM_MXIC_PORT_GR_1, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Acceptance_Capability_All_Port and Im_MXIC_Get_Acceptance_Capability_All_Port function.
void ct_mxic_check_err1_acceptance_capability_all_port(void)
{
	kint32								result;
	T_IM_MXIC_ALL_ACCEPTANCE_CAPABILITY	allCapability;

	// --- Im_MXIC_Set_Acceptance_Capability_All_Port ---
	// unit check
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability_All_Port(): unit check]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability_All_Port((E_IM_MXIC_UNIT)7, &allCapability);
	Ddim_Print(("result=%d\n", result));

	// NULL check
	Ddim_Print(("----[Im_MXIC_Set_Acceptance_Capability_All_Port(): NULL check]----\n"));
	result = Im_MXIC_Set_Acceptance_Capability_All_Port((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Acceptance_Capability_All_Port ---
	// unit check
	Ddim_Print(("----[Im_MXIC_Get_Acceptance_Capability_All_Port(): unit check]----\n"));
	result = Im_MXIC_Get_Acceptance_Capability_All_Port((E_IM_MXIC_UNIT)7, &allCapability);
	Ddim_Print(("result=%d\n", result));

	// NULL check
	Ddim_Print(("----[Im_MXIC_Get_Acceptance_Capability_All_Port(): NULL check]----\n"));
	result = Im_MXIC_Get_Acceptance_Capability_All_Port((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Slave_Area and Im_MXIC_Get_Slave_Area function.
void ct_mxic_check_err1_slave_area(void)
{
	kint32 result;
	T_IM_MXIC_SLAVE_AREA slaveArea;

	// --- Im_MXIC_Set_Slave_Area ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Set_Slave_Area(): unit range error check]----\n"));
	result = Im_MXIC_Set_Slave_Area((E_IM_MXIC_UNIT)7, E_IM_MXIC_SLAVE_NUMBER_2, &slaveArea);
	Ddim_Print(("result=%d\n", result));

	// slave_number range error check
	Ddim_Print(("----[Im_MXIC_Set_Slave_Area(): slave_number range error check]----\n"));
	result = Im_MXIC_Set_Slave_Area((E_IM_MXIC_UNIT)0, E_IM_MXIC_SLAVE_NUMBER_MAX, &slaveArea);
	Ddim_Print(("result=%d\n", result));

	// slaveArea NULL check
	Ddim_Print(("----[Im_MXIC_Set_Slave_Area(): slaveArea NULL check]----\n"));
	result = Im_MXIC_Set_Slave_Area((E_IM_MXIC_UNIT)0, E_IM_MXIC_SLAVE_NUMBER_2, NULL);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Slave_Area ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Get_Slave_Area(): unit range error check]----\n"));
	result = Im_MXIC_Get_Slave_Area((E_IM_MXIC_UNIT)7, E_IM_MXIC_SLAVE_NUMBER_2, &slaveArea);
	Ddim_Print(("result=%d\n", result));

	// slave_number range error check
	Ddim_Print(("----[Im_MXIC_Get_Slave_Area(): slave_number range error check]----\n"));
	result = Im_MXIC_Get_Slave_Area((E_IM_MXIC_UNIT)0, E_IM_MXIC_SLAVE_NUMBER_MAX, &slaveArea);
	Ddim_Print(("result=%d\n", result));

	// slaveArea NULL check
	Ddim_Print(("----[Im_MXIC_Get_Slave_Area(): slaveArea NULL check]----\n"));
	result = Im_MXIC_Get_Slave_Area((E_IM_MXIC_UNIT)0, E_IM_MXIC_SLAVE_NUMBER_2, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Slave_Area_All and Im_MXIC_Get_Slave_Area_All function.
void ct_mxic_check_err1_slave_area_all(void)
{
	kint32						result;
	T_IM_MXIC_ALL_SLAVE_AREA	allSlaveArea;

	// --- Im_MXIC_Set_Slave_Area_All ---
	// NULL check
	Ddim_Print(("----[Im_MXIC_Set_Slave_Area_All(): unit check]----\n"));
	result = Im_MXIC_Set_Slave_Area_All((E_IM_MXIC_UNIT)7, &allSlaveArea);
	Ddim_Print(("result=%d\n", result));

	// NULL check
	Ddim_Print(("----[Im_MXIC_Set_Slave_Area_All(): NULL check]----\n"));
	result = Im_MXIC_Set_Slave_Area_All((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Slave_Area_All ---
	// unit check
	Ddim_Print(("----[Im_MXIC_Get_Slave_Area_All(): unit check]----\n"));
	result = Im_MXIC_Get_Slave_Area_All((E_IM_MXIC_UNIT)7, &allSlaveArea);
	Ddim_Print(("result=%d\n", result));

	// NULL check
	Ddim_Print(("----[Im_MXIC_Get_Slave_Area_All(): NULL check]----\n"));
	result = Im_MXIC_Get_Slave_Area_All((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Decode_Error_Int and Im_MXIC_Get_Decode_Error_Int and Im_MXIC_Get_Decode_Error function.
void ct_mxic_check_err1_decode_error(void)
{
	kint32					result;
	T_IM_MXIC_DEC_ERR_INT	decErrInt;
	T_IM_MXIC_DEC_ERR		decErr;

	// --- Im_MXIC_Set_Decode_Error_Int ---
	// unit check
	Ddim_Print(("----[Im_MXIC_Set_Decode_Error_Int(): unit check]----\n"));
	result = Im_MXIC_Set_Decode_Error_Int((E_IM_MXIC_UNIT)7, &decErrInt);
	Ddim_Print(("result=%d\n", result));

	// NULL check
	Ddim_Print(("----[Im_MXIC_Set_Decode_Error_Int(): NULL check]----\n"));
	result = Im_MXIC_Set_Decode_Error_Int((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Decode_Error_Int ---
	// unit check
	Ddim_Print(("----[Im_MXIC_Get_Decode_Error_Int(): unit check]----\n"));
	result = Im_MXIC_Get_Decode_Error_Int((E_IM_MXIC_UNIT)7, &decErrInt);
	Ddim_Print(("result=%d\n", result));

	// NULL check
	Ddim_Print(("----[Im_MXIC_Get_Decode_Error_Int(): NULL check]----\n"));
	result = Im_MXIC_Get_Decode_Error_Int((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Decode_Error ---
	// unit check
	Ddim_Print(("----[Im_MXIC_Get_Decode_Error(): unit check]----\n"));
	result = Im_MXIC_Get_Decode_Error((E_IM_MXIC_UNIT)7, &decErr);
	Ddim_Print(("result=%d\n", result));

	// NULL check
	Ddim_Print(("----[Im_MXIC_Get_Decode_Error(): NULL check]----\n"));
	result = Im_MXIC_Get_Decode_Error((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_LevelPort_Level and Im_MXIC_Get_LevelPort_Level function.
void ct_mxic_check_err1_levelport_level(void)
{
	kint32 result;
	E_IM_MXIC_LEVEL level;

	// --- Im_MXIC_Set_LevelPort_Level ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Set_LevelPort_Level(): unit range error check]----\n"));
	result = Im_MXIC_Set_LevelPort_Level( (E_IM_MXIC_UNIT)7, (E_IM_MXIC_WR_ARBITER)0, (E_IM_MXIC_SPEC_ARBITER)0,
			0x00, (E_IM_MXIC_LEVEL)0 );
	Ddim_Print(("result=%d\n", result));

	// Target write or read range error check
	Ddim_Print(("----[Im_MXIC_Set_LevelPort_Level(): Target write or read range error check]----\n"));
	result = Im_MXIC_Set_LevelPort_Level( (E_IM_MXIC_UNIT)0, (E_IM_MXIC_WR_ARBITER)2, (E_IM_MXIC_SPEC_ARBITER)0,
			0x00, (E_IM_MXIC_LEVEL)0 );
	Ddim_Print(("result=%d\n", result));

	// Target arbiter range error check
	Ddim_Print(("----[Im_MXIC_Set_LevelPort_Level(): Target arbiter range error check]----\n"));
	result = Im_MXIC_Set_LevelPort_Level( (E_IM_MXIC_UNIT)0, (E_IM_MXIC_WR_ARBITER)0, (E_IM_MXIC_SPEC_ARBITER)4,
			0x00, (E_IM_MXIC_LEVEL)0 );
	Ddim_Print(("result=%d\n", result));

	// Target level range error check
	Ddim_Print(("----[Im_MXIC_Set_LevelPort_Level(): Target level range error check]----\n"));
	result = Im_MXIC_Set_LevelPort_Level( (E_IM_MXIC_UNIT)0, (E_IM_MXIC_WR_ARBITER)0, (E_IM_MXIC_SPEC_ARBITER)0,
			0x00, (E_IM_MXIC_LEVEL)4 );
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_LevelPort_Level ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Get_LevelPort_Level(): unit range error check]----\n"));
	result = Im_MXIC_Get_LevelPort_Level( (E_IM_MXIC_UNIT)7, (E_IM_MXIC_WR_ARBITER)0, (E_IM_MXIC_SPEC_ARBITER)0,
			0x00, &level );
	Ddim_Print(("result=%d\n", result));

	// Target write or read range error check
	Ddim_Print(("----[Im_MXIC_Get_LevelPort_Level(): Target write or read range error check]----\n"));
	result = Im_MXIC_Get_LevelPort_Level( (E_IM_MXIC_UNIT)0, (E_IM_MXIC_WR_ARBITER)2, (E_IM_MXIC_SPEC_ARBITER)0,
			0x00, &level );
	Ddim_Print(("result=%d\n", result));

	// Target arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_LevelPort_Level(): Target arbiter range error check]----\n"));
	result = Im_MXIC_Get_LevelPort_Level( (E_IM_MXIC_UNIT)0, (E_IM_MXIC_WR_ARBITER)0, (E_IM_MXIC_SPEC_ARBITER)4,
			0x00, &level );
	Ddim_Print(("result=%d\n", result));

	// Level null error check
	Ddim_Print(("----[Im_MXIC_Get_LevelPort_Level(): Level null error check]----\n"));
	result = Im_MXIC_Get_LevelPort_Level( (E_IM_MXIC_UNIT)0, (E_IM_MXIC_WR_ARBITER)0, (E_IM_MXIC_SPEC_ARBITER)0,
			0x00, NULL );
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_LevelPort_Port and Im_MXIC_Get_LevelPort_Port function.
void ct_mxic_check_err1_levelport_port(void)
{
	kint32 result;
	E_IM_MXIC_PORT port;

	// --- Im_MXIC_Set_LevelPort_Port ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Set_LevelPort_Port(): unit range error check]----\n"));
	result = Im_MXIC_Set_LevelPort_Port( (E_IM_MXIC_UNIT)7, (E_IM_MXIC_WR_ARBITER)0, (E_IM_MXIC_SPEC_ARBITER)0,
			0x00, (E_IM_MXIC_PORT)0 );
	Ddim_Print(("result=%d\n", result));

	// Target write or read range error check
	Ddim_Print(("----[Im_MXIC_Set_LevelPort_Port(): Target write or read range error check]----\n"));
	result = Im_MXIC_Set_LevelPort_Port( (E_IM_MXIC_UNIT)0, (E_IM_MXIC_WR_ARBITER)2, (E_IM_MXIC_SPEC_ARBITER)0,
			0x00, (E_IM_MXIC_PORT)0 );
	Ddim_Print(("result=%d\n", result));

	// Target arbiter range error check
	Ddim_Print(("----[Im_MXIC_Set_LevelPort_Port(): Target arbiter range error check]----\n"));
	result = Im_MXIC_Set_LevelPort_Port( (E_IM_MXIC_UNIT)0, (E_IM_MXIC_WR_ARBITER)0, (E_IM_MXIC_SPEC_ARBITER)4,
			0x00, (E_IM_MXIC_PORT)0 );
	Ddim_Print(("result=%d\n", result));

	// Target port range error check
	Ddim_Print(("----[Im_MXIC_Set_LevelPort_Port(): Target port range error check]----\n"));
	result = Im_MXIC_Set_LevelPort_Port( (E_IM_MXIC_UNIT)0, (E_IM_MXIC_WR_ARBITER)0, (E_IM_MXIC_SPEC_ARBITER)0,
			0x00, (E_IM_MXIC_PORT)4 );
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_LevelPort_Port ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Get_LevelPort_Port(): unit range error check]----\n"));
	result = Im_MXIC_Get_LevelPort_Port( (E_IM_MXIC_UNIT)7, (E_IM_MXIC_WR_ARBITER)0, (E_IM_MXIC_SPEC_ARBITER)0,
			0x00, &port );
	Ddim_Print(("result=%d\n", result));

	// Target write or read range error check
	Ddim_Print(("----[Im_MXIC_Get_LevelPort_Port(): Target write or read range error check]----\n"));
	result = Im_MXIC_Get_LevelPort_Port( (E_IM_MXIC_UNIT)0, (E_IM_MXIC_WR_ARBITER)2, (E_IM_MXIC_SPEC_ARBITER)0,
			0x00, &port );
	Ddim_Print(("result=%d\n", result));

	// Target arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_LevelPort_Port(): Target arbiter range error check]----\n"));
	result = Im_MXIC_Get_LevelPort_Port( (E_IM_MXIC_UNIT)0, (E_IM_MXIC_WR_ARBITER)0, (E_IM_MXIC_SPEC_ARBITER)4,
			0x00, &port );
	Ddim_Print(("result=%d\n", result));

	// Port null error check
	Ddim_Print(("----[Im_MXIC_Get_LevelPort_Port(): Port null error check]----\n"));
	result = Im_MXIC_Get_LevelPort_Port( (E_IM_MXIC_UNIT)0, (E_IM_MXIC_WR_ARBITER)0, (E_IM_MXIC_SPEC_ARBITER)0,
			0x00, NULL );
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_LevelPort_All and Im_MXIC_Get_LevelPort_All function.
void ct_mxic_check_err1_levelport_all(void)
{
	kint32					result;
	T_IM_MXIC_ALL_LEVELPORT	allLevelport;

	// --- Im_MXIC_Set_LevelPort_All ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Set_LevelPort_All(): unit range error check]----\n"));
	result = Im_MXIC_Set_LevelPort_All( (E_IM_MXIC_UNIT)7, &allLevelport );
	Ddim_Print(("result=%d\n", result));

	// allLevelport NULL error check
	Ddim_Print(("----[Im_MXIC_Set_LevelPort_All(): allLevelport NULL error check]----\n"));
	result = Im_MXIC_Set_LevelPort_All( (E_IM_MXIC_UNIT)0, NULL );
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_LevelPort_All ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Get_LevelPort_All(): unit range error check]----\n"));
	result = Im_MXIC_Get_LevelPort_All( (E_IM_MXIC_UNIT)7, &allLevelport );
	Ddim_Print(("result=%d\n", result));

	// allLevelport NULL error check
	Ddim_Print(("----[Im_MXIC_Get_LevelPort_All(): allLevelport NULL error check]----\n"));
	result = Im_MXIC_Get_LevelPort_All( (E_IM_MXIC_UNIT)0, NULL );
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Output_Port and Im_MXIC_Get_Output_Port function.
void ct_mxic_check_err1_port_assign(void)
{
	kint32 result;

	// --- Im_MXIC_Set_Output_Port ---
	// assign range error check
	Ddim_Print(("----[Im_MXIC_Set_Output_Port(): assign range error check]----\n"));
	result = Im_MXIC_Set_Output_Port(D_IM_MXIC_3_W_ELA, E_IM_MXIC_PORT_GR_MAX);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Output_Port ---
	// assign NULL check
	Ddim_Print(("----[Im_MXIC_Get_Output_Port(): assign NULL check]----\n"));
	result = Im_MXIC_Get_Output_Port(D_IM_MXIC_3_W_ELA, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Output_Port_All and Im_MXIC_Get_Output_Port_All function.
void ct_mxic_check_err1_port_assign_all(void)
{
	kint32 result;

	// --- Im_MXIC_Set_Output_Port_All ---
	// all_assign NULL check
	Ddim_Print(("----[Im_MXIC_Set_Output_Port_All(): all_assign NULL check]----\n"));
	result = Im_MXIC_Set_Output_Port_All(NULL);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Output_Port_All ---
	// all_assign NULL check
	Ddim_Print(("----[Im_MXIC_Get_Output_Port_All(): all_assign NULL check]----\n"));
	result = Im_MXIC_Get_Output_Port_All(NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Master_W_Arbiter and Im_MXIC_Get_Master_W_Arbiter function.
void ct_mxic_check_err1_master_w_arbiter(void)
{
	kint32 result;
	kint32 i;
	T_IM_MXIC_W_ARBITER_ASSIGN_PORT wAssign;

	// Initialize
	for (i = 0; i < D_IM_MXIC_SLOT_SIZE_8; i++) {
		wAssign.port[0].slot0[i] = D_IM_MXIC_W_RESERVE;
		wAssign.port[0].slot2[i] = D_IM_MXIC_W_RESERVE;
		wAssign.port[0].slot3[i] = D_IM_MXIC_W_RESERVE;
	}
	for (i = 0; i < D_IM_MXIC_SLOT_SIZE_8; i++) {
		wAssign.port[0].slot1[i] = D_IM_MXIC_W_RESERVE;
	}

	// --- Im_MXIC_Set_Master_W_Arbiter ---
	// unit error check
	Ddim_Print(("----[Im_MXIC_Set_Master_W_Arbiter(): unit range error check]----\n"));
	result = Im_MXIC_Set_Master_W_Arbiter((E_IM_MXIC_UNIT)7, E_IM_MXIC_W_ARBITER_W1, &wAssign);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_W_Arbiter(): arbiter range error check]----\n"));
	result = Im_MXIC_Set_Master_W_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_W_ARBITER_MAX, &wAssign);
	Ddim_Print(("result=%d\n", result));

	// assign.port[0].slot0[7] range error check(W max)
	Ddim_Print(("----[Im_MXIC_Set_Master_W_Arbiter(): assign.port[0].slot0[7] range error check(W max)]----\n"));
	wAssign.port[0].slot0[7] = D_IM_MXIC_MAX_W_MASTER_NUM;
	result = Im_MXIC_Set_Master_W_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_W_ARBITER_W1, &wAssign);
	wAssign.port[0].slot0[7] = D_IM_MXIC_W_RESERVE;
	Ddim_Print(("result=%d\n", result));

	// assign.port[0].slot1[7] range error check(RW type)
	Ddim_Print(("----[Im_MXIC_Set_Master_W_Arbiter(): assign.port[0].slot1[7] range error check(RW type)]----\n"));
	wAssign.port[0].slot1[7] = D_IM_MXIC_1_R_SRO;
	result = Im_MXIC_Set_Master_W_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_W_ARBITER_W2, &wAssign);
	wAssign.port[0].slot1[7] = D_IM_MXIC_W_RESERVE;
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Master_W_Arbiter ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Get_Master_W_Arbiter(): unit range error check]----\n"));
	result = Im_MXIC_Get_Master_W_Arbiter((E_IM_MXIC_UNIT)7, E_IM_MXIC_W_ARBITER_W2, &wAssign);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Master_W_Arbiter(): arbiter range error check]----\n"));
	result = Im_MXIC_Get_Master_W_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_W_ARBITER_MAX, &wAssign);
	Ddim_Print(("result=%d\n", result));

	// assign NULL check
	Ddim_Print(("----[Im_MXIC_Get_Master_W_Arbiter(): assign NULL check]----\n"));
	result = Im_MXIC_Get_Master_W_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_W_ARBITER_W2, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Master_R_Arbiter and Im_MXIC_Get_Master_R_Arbiter function.
void ct_mxic_check_err1_master_r_arbiter(void)
{
	kint32 result;
	kint32 i;
	T_IM_MXIC_R_ARBITER_ASSIGN_PORT rAssign;

	// Initialize
	for (i = 0; i < D_IM_MXIC_SLOT_SIZE_8; i++) {
		rAssign.port[0].slot0[i] = D_IM_MXIC_R_RESERVE;
		rAssign.port[0].slot2[i] = D_IM_MXIC_R_RESERVE;
		rAssign.port[0].slot3[i] = D_IM_MXIC_R_RESERVE;
	}
	for (i = 0; i < D_IM_MXIC_SLOT_SIZE_8; i++) {
		rAssign.port[0].slot1[i] = D_IM_MXIC_R_RESERVE;
	}

	// --- Im_MXIC_Set_Master_R_Arbiter ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_R_Arbiter(): unit range error check]----\n"));
	result = Im_MXIC_Set_Master_R_Arbiter((E_IM_MXIC_UNIT)7, E_IM_MXIC_R_ARBITER_R2, &rAssign);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_R_Arbiter(): arbiter range error check]----\n"));
	result = Im_MXIC_Set_Master_R_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_R_ARBITER_MAX, &rAssign);
	Ddim_Print(("result=%d\n", result));

	// assign.slot1[7].slot1[7] range error check(RW type)
	Ddim_Print(("----[Im_MXIC_Set_Master_R_Arbiter(): assign.port[0].slot1[7] range error check(RW type)]----\n"));
	rAssign.port[0].slot1[7] = D_IM_MXIC_0_W_SEN_0;
	result = Im_MXIC_Set_Master_R_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_R_ARBITER_R2, &rAssign);
	rAssign.port[0].slot1[7] = D_IM_MXIC_R_RESERVE;
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Master_R_Arbiter ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Get_Master_R_Arbiter(): unit range error check]----\n"));
	result = Im_MXIC_Get_Master_R_Arbiter((E_IM_MXIC_UNIT)7, E_IM_MXIC_R_ARBITER_R2, &rAssign);
	Ddim_Print(("result=%d\n", result));

	// 	arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Master_R_Arbiter(): arbiter range error check]----\n"));
	result = Im_MXIC_Get_Master_R_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_R_ARBITER_MAX, &rAssign);
	Ddim_Print(("result=%d\n", result));

	// assign NULL check
	Ddim_Print(("----[Im_MXIC_Get_Master_R_Arbiter(): assign NULL check]----\n"));
	result = Im_MXIC_Get_Master_R_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_R_ARBITER_R2, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Master_All_Arbiter and Im_MXIC_Get_Master_All_Arbiter function.
void ct_mxic_check_err1_master_all_arbiter(void)
{
	kint32							result;
	T_IM_MXIC_ALL_ARBITER_ASSIGN	allArbiterAssign;

	// --- Im_MXIC_Set_Master_All_Arbiter ---
	// all_assign unit check
	Ddim_Print(("----[Im_MXIC_Set_Master_All_Arbiter(): all_assign unit check]----\n"));
	result = Im_MXIC_Set_Master_All_Arbiter((E_IM_MXIC_UNIT)7, &allArbiterAssign);
	Ddim_Print(("result=%d\n", result));

	// all_assign NULL check
	Ddim_Print(("----[Im_MXIC_Set_Master_All_Arbiter(): all_assign NULL check]----\n"));
	result = Im_MXIC_Set_Master_All_Arbiter((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Master_All_Arbiter ---
	// all_assign unit check
	Ddim_Print(("----[Im_MXIC_Get_Master_All_Arbiter(): all_assign unit check]----\n"));
	result = Im_MXIC_Get_Master_All_Arbiter((E_IM_MXIC_UNIT)7, &allArbiterAssign);
	Ddim_Print(("result=%d\n", result));

	// all_assign NULL check
	Ddim_Print(("----[Im_MXIC_Get_Master_All_Arbiter(): all_assign NULL check]----\n"));
	result = Im_MXIC_Get_Master_All_Arbiter((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

void ct_mxic_check_err1_master_overlap( void )
{
	kint32 result;
	T_IM_MXIC_W_ARBITER_ASSIGN_PORT wArbiterAssign;
	T_IM_MXIC_R_ARBITER_ASSIGN_PORT rArbiterAssign;

	Ddim_Print(("----[Im_MXIC_Set_Master_W_Arbiter(): assign error check]----\n"));
	ct_im_mxic_create_master_w_arbiter_param( (E_IM_MXIC_UNIT)0, &wArbiterAssign );
	wArbiterAssign.port[0].slot1[7] = D_IM_MXIC_0_W_SEN_0;
	wArbiterAssign.port[0].slot0[7] = D_IM_MXIC_0_W_SEN_0;
	result = Im_MXIC_Set_Master_W_Arbiter( (E_IM_MXIC_UNIT)0, E_IM_MXIC_W_ARBITER_W1, &wArbiterAssign );
	Ddim_Print(("result=%d\n", result));

	Ddim_Print(("----[Im_MXIC_Set_Master_R_Arbiter(): assign error check]----\n"));
	ct_im_mxic_create_master_r_arbiter_param( (E_IM_MXIC_UNIT)0, &rArbiterAssign );
	rArbiterAssign.port[0].slot2[6] = D_IM_MXIC_1_R_SRO;
	rArbiterAssign.port[0].slot1[7] = D_IM_MXIC_1_R_SRO;
	result = Im_MXIC_Set_Master_R_Arbiter( (E_IM_MXIC_UNIT)0, E_IM_MXIC_R_ARBITER_R1, &rArbiterAssign );
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Slot_Priority and Im_MXIC_Get_Slot_Priority function.
void ct_mxic_check_err1_slot_priority(void)
{
	kint32 result;
	T_IM_MXIC_SLOT_PRIORITY_LEVEL priority;

	// Initialize
	priority.priority_level_type  = D_IM_MXIC_SLOT_PRIORITY_LOWWER;
	priority.upper_priority_level = 0;
	priority.lower_priority_level = 63;

	// --- Im_MXIC_Set_Slot_Priority ---
	// priority unit check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Priority(): priority unit check]----\n"));
	result = Im_MXIC_Set_Slot_Priority((E_IM_MXIC_UNIT)7, E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_2,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_LEVEL_CTRL_2, &priority);
	Ddim_Print(("result=%d\n", result));

	// priority NULL check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Priority(): priority NULL check]----\n"));
	result = Im_MXIC_Set_Slot_Priority((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_2,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_LEVEL_CTRL_2, NULL);
	Ddim_Print(("result=%d\n", result));

	// write or read arbiter range error check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Priority(): wr_arbiter range error check]----\n"));
	result = Im_MXIC_Set_Slot_Priority((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_MAX, E_IM_MXIC_SPEC_ARBITER_2,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_LEVEL_CTRL_2, &priority);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Priority(): arbiter range error check]----\n"));
	result = Im_MXIC_Set_Slot_Priority((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_MAX,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_LEVEL_CTRL_2, &priority);
	Ddim_Print(("result=%d\n", result));

	// port range error check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Priority(): port range error check]----\n"));
	result = Im_MXIC_Set_Slot_Priority((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_1,
			E_IM_MXIC_PORT_MAX, E_IM_MXIC_SLOT_LEVEL_CTRL_1, &priority);
	Ddim_Print(("result=%d\n", result));

	// level_number range error check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Priority(): level_number range error check]----\n"));
	result = Im_MXIC_Set_Slot_Priority((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_1,
			E_IM_MXIC_PORT_1, E_IM_MXIC_SLOT_LEVEL_CTRL_MAX, &priority);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Slot_Priority ---
	// priority unit check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Priority(): priority unit check]----\n"));
	result = Im_MXIC_Get_Slot_Priority((E_IM_MXIC_UNIT)7, E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_2,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_LEVEL_CTRL_2, &priority);
	Ddim_Print(("result=%d\n", result));

	// priority NULL check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Priority(): priority NULL check]----\n"));
	result = Im_MXIC_Get_Slot_Priority((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_2,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_LEVEL_CTRL_2, NULL);
	Ddim_Print(("result=%d\n", result));

	// write or read arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Priority(): wr_arbiter range error check]----\n"));
	result = Im_MXIC_Get_Slot_Priority((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_MAX, E_IM_MXIC_SPEC_ARBITER_2,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_LEVEL_CTRL_2, &priority);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Priority(): arbiter range error check]----\n"));
	result = Im_MXIC_Get_Slot_Priority((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_MAX,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_LEVEL_CTRL_2, &priority);
	Ddim_Print(("result=%d\n", result));

	// port range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Priority(): port range error check]----\n"));
	result = Im_MXIC_Get_Slot_Priority((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_1,
			E_IM_MXIC_PORT_MAX, E_IM_MXIC_SLOT_LEVEL_CTRL_1, &priority);
	Ddim_Print(("result=%d\n", result));

	// level_number range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Priority(): level_number range error check]----\n"));
	result = Im_MXIC_Get_Slot_Priority((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_1,
			E_IM_MXIC_PORT_1, E_IM_MXIC_SLOT_LEVEL_CTRL_MAX, &priority);
	Ddim_Print(("result=%d\n", result));

	return;
}

CtMxicCheckErr1* ct_mxic_check_err1_new(void) 
{
    CtMxicCheckErr1 *self = k_object_new_with_private(CT_TYPE_MXIC_CHECK_ERR1, sizeof(CtMxicCheckErr1Private));
    return self;
}
