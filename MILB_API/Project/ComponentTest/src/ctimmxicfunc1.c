/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :jianghaodong
*@brief               :CtImMxicFunc1类
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

#include "ctimmxicprint.h"
#include "ctimmxiccreate.h"
#include "ctimmxicfunc1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImMxicFunc1, ct_im_mxic_func1);
#define CT_IM_MXIC_FUNC1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImMxicFunc1Private,CT_TYPE_IM_MXIC_FUNC1))

struct _CtImMxicFunc1Private
{

};

/*
*IMPL
*/
static void ct_im_mxic_func1_constructor(CtImMxicFunc1 *self) 
{
}

static void ct_im_mxic_func1_destructor(CtImMxicFunc1 *self) 
{
}

/*
*PUBLIC
*/
/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
void ct_im_mxic_func1_01(CtImMxicFunc1* self)
{
	kint32								result;
	T_IM_MXIC_ALL_ARBITER_ASSIGN		allArbiterAssign;
	T_IM_MXIC_ALL_SLOT_PRIORITY_LEVEL	allLevelCtrl;
	T_IM_MXIC_ALL_LEVELPORT 			allLevelport;

	Ddim_Print(("ct_im_mxic_func1_01(self->unit=%d)\n", self->unit));

	result = Im_MXIC_Init( (E_IM_MXIC_UNIT)self->unit );
	if (result == D_DDIM_OK) {
		Ddim_Print(("Im_MXIC_Init OK(self->unit=%d).\n", self->unit));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Init NG(self->unit=%d). result=0x%X\n", result, self->unit));
	}

	result = Im_MXIC_Get_Master_All_Arbiter( (E_IM_MXIC_UNIT)self->unit, &allArbiterAssign );
	if ( result == D_DDIM_OK ) {
		ct_im_mxic_print_all_arbiter_assign(  &allArbiterAssign );
		Ddim_Print(("Im_MXIC_Get_Master_All_Arbiter OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Master_All_Arbiter NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Get_Slot_Priority_All_Arbiter( (E_IM_MXIC_UNIT)self->unit, &allLevelCtrl );
	if (result == D_DDIM_OK) {
		ct_im_mxic_print_all_slot_priority_level(  &allLevelCtrl );
		Ddim_Print(("Im_MXIC_Get_Slot_Priority_All_Arbiter OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Slot_Priority_All_Arbiter NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Get_LevelPort_All( (E_IM_MXIC_UNIT)self->unit, &allLevelport );
	if (result == D_DDIM_OK) {
		ct_im_mxic_print_all_levelport( &allLevelport );
		Ddim_Print(("Im_MXIC_Get_LevelPort_All OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_LevelPort_All NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func1_02(CtImMxicFunc1* self)
{
	kint32						result;
	T_IM_MXIC_CONFIG_ARBITER	config;

	Ddim_Print(("ct_im_mxic_func1_02(self->unit=%d)\n", self->unit));

	config.sl_w1_config_on_flg = D_IM_MXIC_ON;
	config.sl_w2_config_on_flg = D_IM_MXIC_ON;
	config.sl_w3_config_on_flg = D_IM_MXIC_ON;
	config.sl_w4_config_on_flg = D_IM_MXIC_ON;
	config.sl_r1_config_on_flg = D_IM_MXIC_ON;
	config.sl_r2_config_on_flg = D_IM_MXIC_ON;
	config.sl_r3_config_on_flg = D_IM_MXIC_ON;
	config.sl_r4_config_on_flg = D_IM_MXIC_ON;
	config.gr_w0_config_on_flg = D_IM_MXIC_ON;
	config.gr_w1_config_on_flg = D_IM_MXIC_ON;
	config.gr_w2_config_on_flg = D_IM_MXIC_ON;
	config.gr_w3_config_on_flg = D_IM_MXIC_ON;
	config.gr_w4_config_on_flg = D_IM_MXIC_ON;
	config.gr_w5_config_on_flg = D_IM_MXIC_ON;
	config.gr_w6_config_on_flg = D_IM_MXIC_ON;
	config.gr_w7_config_on_flg = D_IM_MXIC_ON;
	config.gr_r0_config_on_flg = D_IM_MXIC_ON;
	config.gr_r1_config_on_flg = D_IM_MXIC_ON;
	config.gr_r2_config_on_flg = D_IM_MXIC_ON;
	config.gr_r3_config_on_flg = D_IM_MXIC_ON;
	config.gr_r4_config_on_flg = D_IM_MXIC_ON;
	config.gr_r5_config_on_flg = D_IM_MXIC_ON;
	config.gr_r6_config_on_flg = D_IM_MXIC_ON;
	config.gr_r7_config_on_flg = D_IM_MXIC_ON;

	result = Im_MXIC_Start_Config( (E_IM_MXIC_UNIT)self->unit, &config );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Start_Config OK(self->unit=%d).\n", self->unit));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Start_Config NG(self->unit=%d). result=0x%X\n", self->unit, result));
	}

	config.sl_w1_config_on_flg = D_IM_MXIC_OFF;
	config.sl_w2_config_on_flg = D_IM_MXIC_OFF;
	config.sl_w3_config_on_flg = D_IM_MXIC_OFF;
	config.sl_w4_config_on_flg = D_IM_MXIC_OFF;
	config.sl_r1_config_on_flg = D_IM_MXIC_OFF;
	config.sl_r2_config_on_flg = D_IM_MXIC_OFF;
	config.sl_r3_config_on_flg = D_IM_MXIC_OFF;
	config.sl_r4_config_on_flg = D_IM_MXIC_OFF;
	config.gr_w0_config_on_flg = D_IM_MXIC_OFF;
	config.gr_w1_config_on_flg = D_IM_MXIC_OFF;
	config.gr_w2_config_on_flg = D_IM_MXIC_OFF;
	config.gr_w3_config_on_flg = D_IM_MXIC_OFF;
	config.gr_w4_config_on_flg = D_IM_MXIC_OFF;
	config.gr_w5_config_on_flg = D_IM_MXIC_OFF;
	config.gr_w6_config_on_flg = D_IM_MXIC_OFF;
	config.gr_w7_config_on_flg = D_IM_MXIC_OFF;
	config.gr_r0_config_on_flg = D_IM_MXIC_OFF;
	config.gr_r1_config_on_flg = D_IM_MXIC_OFF;
	config.gr_r2_config_on_flg = D_IM_MXIC_OFF;
	config.gr_r3_config_on_flg = D_IM_MXIC_OFF;
	config.gr_r4_config_on_flg = D_IM_MXIC_OFF;
	config.gr_r5_config_on_flg = D_IM_MXIC_OFF;
	config.gr_r6_config_on_flg = D_IM_MXIC_OFF;
	config.gr_r7_config_on_flg = D_IM_MXIC_OFF;

	result = Im_MXIC_Start_Config( (E_IM_MXIC_UNIT)self->unit, &config );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Start_Config OK(self->unit=%d).\n", self->unit));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Start_Config NG(self->unit=%d). result=0x%X\n", self->unit, result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func1_03(CtImMxicFunc1* self)
{
	kint32			result;
	T_IM_MXIC_CLOCK	clockCtrl;

	Ddim_Print(("ct_im_mxic_func1_03(self->unit=%d)\n", self->unit));

	clockCtrl.clk_en_slave_1_0 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_1_1 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_1_2 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_1_3 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_2_0 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_2_1 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_2_2 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_2_3 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_3_0 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_3_1 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_3_2 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_3_3 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_4_0 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_4_1 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_4_2 = D_IM_MXIC_ON;
	clockCtrl.clk_en_slave_4_3 = D_IM_MXIC_ON;
	clockCtrl.clk_en_group_0   = D_IM_MXIC_ON;
	clockCtrl.clk_en_group_1   = D_IM_MXIC_ON;
	clockCtrl.clk_en_group_2   = D_IM_MXIC_ON;
	clockCtrl.clk_en_group_3   = D_IM_MXIC_ON;
	clockCtrl.clk_en_group_4   = D_IM_MXIC_ON;
	clockCtrl.clk_en_group_5   = D_IM_MXIC_ON;
	clockCtrl.clk_en_group_6   = D_IM_MXIC_ON;
	clockCtrl.clk_en_group_7   = D_IM_MXIC_ON;
	clockCtrl.clk_en_dec_err   = D_IM_MXIC_ON;
	clockCtrl.clk_en_monitor   = D_IM_MXIC_ON;

	result = Im_MXIC_Set_Clock_Enable( (E_IM_MXIC_UNIT)self->unit, &clockCtrl );
	if (result == D_DDIM_OK) {
		Ddim_Print(("Im_MXIC_Set_Clock_Enable OK(self->unit=%d).\n",self->unit));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Clock_Enable NG(self->unit=%d). result=0x%X\n", self->unit, result));
	}

	memset( &clockCtrl, 0, sizeof(T_IM_MXIC_CLOCK) );

	result = Im_MXIC_Get_Clock_Enable( (E_IM_MXIC_UNIT)self->unit, &clockCtrl );
	if (result == D_DDIM_OK) {
		Ddim_Print(("clockCtrl.clk_en_slave_1_0=%d\n", clockCtrl.clk_en_slave_1_0));
		Ddim_Print(("clockCtrl.clk_en_slave_1_1=%d\n", clockCtrl.clk_en_slave_1_1));
		Ddim_Print(("clockCtrl.clk_en_slave_1_2=%d\n", clockCtrl.clk_en_slave_1_2));
		Ddim_Print(("clockCtrl.clk_en_slave_1_3=%d\n", clockCtrl.clk_en_slave_1_3));
		Ddim_Print(("clockCtrl.clk_en_slave_2_0=%d\n", clockCtrl.clk_en_slave_2_0));
		Ddim_Print(("clockCtrl.clk_en_slave_2_1=%d\n", clockCtrl.clk_en_slave_2_1));
		Ddim_Print(("clockCtrl.clk_en_slave_2_2=%d\n", clockCtrl.clk_en_slave_2_2));
		Ddim_Print(("clockCtrl.clk_en_slave_2_3=%d\n", clockCtrl.clk_en_slave_2_3));
		Ddim_Print(("clockCtrl.clk_en_slave_3_0=%d\n", clockCtrl.clk_en_slave_3_0));
		Ddim_Print(("clockCtrl.clk_en_slave_3_1=%d\n", clockCtrl.clk_en_slave_3_1));
		Ddim_Print(("clockCtrl.clk_en_slave_3_2=%d\n", clockCtrl.clk_en_slave_3_2));
		Ddim_Print(("clockCtrl.clk_en_slave_3_3=%d\n", clockCtrl.clk_en_slave_3_3));
		Ddim_Print(("clockCtrl.clk_en_slave_4_0=%d\n", clockCtrl.clk_en_slave_4_0));
		Ddim_Print(("clockCtrl.clk_en_slave_4_1=%d\n", clockCtrl.clk_en_slave_4_1));
		Ddim_Print(("clockCtrl.clk_en_slave_4_2=%d\n", clockCtrl.clk_en_slave_4_2));
		Ddim_Print(("clockCtrl.clk_en_slave_4_3=%d\n", clockCtrl.clk_en_slave_4_3));
		Ddim_Print(("clockCtrl.clk_en_group_0=%d\n", clockCtrl.clk_en_group_0));
		Ddim_Print(("clockCtrl.clk_en_group_1=%d\n", clockCtrl.clk_en_group_1));
		Ddim_Print(("clockCtrl.clk_en_group_2=%d\n", clockCtrl.clk_en_group_2));
		Ddim_Print(("clockCtrl.clk_en_group_3=%d\n", clockCtrl.clk_en_group_3));
		Ddim_Print(("clockCtrl.clk_en_group_4=%d\n", clockCtrl.clk_en_group_4));
		Ddim_Print(("clockCtrl.clk_en_group_5=%d\n", clockCtrl.clk_en_group_5));
		Ddim_Print(("clockCtrl.clk_en_group_6=%d\n", clockCtrl.clk_en_group_6));
		Ddim_Print(("clockCtrl.clk_en_group_7=%d\n", clockCtrl.clk_en_group_7));
		Ddim_Print(("clockCtrl.clk_en_dec_err=%d\n", clockCtrl.clk_en_dec_err));
		Ddim_Print(("clockCtrl.clk_en_monitor=%d\n", clockCtrl.clk_en_monitor));
		Ddim_Print(("Im_MXIC_Get_Clock_Enable OK(self->unit=%d).\n", self->unit));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Clock_Enable NG(self->unit=%d). result=0x%X\n", self->unit, result));
	}

	clockCtrl.clk_en_slave_1_0 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_1_1 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_1_2 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_1_3 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_2_0 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_2_1 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_2_2 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_2_3 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_3_0 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_3_1 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_3_2 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_3_3 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_4_0 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_4_1 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_4_2 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_slave_4_3 = D_IM_MXIC_OFF;
	clockCtrl.clk_en_group_0   = D_IM_MXIC_OFF;
	clockCtrl.clk_en_group_1   = D_IM_MXIC_OFF;
	clockCtrl.clk_en_group_2   = D_IM_MXIC_OFF;
	clockCtrl.clk_en_group_3   = D_IM_MXIC_OFF;
	clockCtrl.clk_en_group_4   = D_IM_MXIC_OFF;
	clockCtrl.clk_en_group_5   = D_IM_MXIC_OFF;
	clockCtrl.clk_en_group_6   = D_IM_MXIC_OFF;
	clockCtrl.clk_en_group_7   = D_IM_MXIC_OFF;
	clockCtrl.clk_en_dec_err   = D_IM_MXIC_OFF;
	clockCtrl.clk_en_monitor   = D_IM_MXIC_OFF;

	result = Im_MXIC_Set_Clock_Enable( (E_IM_MXIC_UNIT)self->unit, &clockCtrl );
	if (result == D_DDIM_OK) {
		Ddim_Print(("Im_MXIC_Set_Clock_Enable OK(self->unit=%d).\n",self->unit));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Clock_Enable NG(self->unit=%d). result=0x%X\n", self->unit, result));
	}

	memset( &clockCtrl, 0, sizeof(T_IM_MXIC_CLOCK) );

	result = Im_MXIC_Get_Clock_Enable( (E_IM_MXIC_UNIT)self->unit, &clockCtrl );
	if (result == D_DDIM_OK) {
		Ddim_Print(("clockCtrl.clk_en_slave_1_0=%d\n", clockCtrl.clk_en_slave_1_0));
		Ddim_Print(("clockCtrl.clk_en_slave_1_1=%d\n", clockCtrl.clk_en_slave_1_1));
		Ddim_Print(("clockCtrl.clk_en_slave_1_2=%d\n", clockCtrl.clk_en_slave_1_2));
		Ddim_Print(("clockCtrl.clk_en_slave_1_3=%d\n", clockCtrl.clk_en_slave_1_3));
		Ddim_Print(("clockCtrl.clk_en_slave_2_0=%d\n", clockCtrl.clk_en_slave_2_0));
		Ddim_Print(("clockCtrl.clk_en_slave_2_1=%d\n", clockCtrl.clk_en_slave_2_1));
		Ddim_Print(("clockCtrl.clk_en_slave_2_2=%d\n", clockCtrl.clk_en_slave_2_2));
		Ddim_Print(("clockCtrl.clk_en_slave_2_3=%d\n", clockCtrl.clk_en_slave_2_3));
		Ddim_Print(("clockCtrl.clk_en_slave_3_0=%d\n", clockCtrl.clk_en_slave_3_0));
		Ddim_Print(("clockCtrl.clk_en_slave_3_1=%d\n", clockCtrl.clk_en_slave_3_1));
		Ddim_Print(("clockCtrl.clk_en_slave_3_2=%d\n", clockCtrl.clk_en_slave_3_2));
		Ddim_Print(("clockCtrl.clk_en_slave_3_3=%d\n", clockCtrl.clk_en_slave_3_3));
		Ddim_Print(("clockCtrl.clk_en_slave_4_0=%d\n", clockCtrl.clk_en_slave_4_0));
		Ddim_Print(("clockCtrl.clk_en_slave_4_1=%d\n", clockCtrl.clk_en_slave_4_1));
		Ddim_Print(("clockCtrl.clk_en_slave_4_2=%d\n", clockCtrl.clk_en_slave_4_2));
		Ddim_Print(("clockCtrl.clk_en_slave_4_3=%d\n", clockCtrl.clk_en_slave_4_3));
		Ddim_Print(("clockCtrl.clk_en_group_0=%d\n", clockCtrl.clk_en_group_0));
		Ddim_Print(("clockCtrl.clk_en_group_1=%d\n", clockCtrl.clk_en_group_1));
		Ddim_Print(("clockCtrl.clk_en_group_2=%d\n", clockCtrl.clk_en_group_2));
		Ddim_Print(("clockCtrl.clk_en_group_3=%d\n", clockCtrl.clk_en_group_3));
		Ddim_Print(("clockCtrl.clk_en_group_4=%d\n", clockCtrl.clk_en_group_4));
		Ddim_Print(("clockCtrl.clk_en_group_5=%d\n", clockCtrl.clk_en_group_5));
		Ddim_Print(("clockCtrl.clk_en_group_6=%d\n", clockCtrl.clk_en_group_6));
		Ddim_Print(("clockCtrl.clk_en_group_7=%d\n", clockCtrl.clk_en_group_7));
		Ddim_Print(("clockCtrl.clk_en_dec_err=%d\n", clockCtrl.clk_en_dec_err));
		Ddim_Print(("clockCtrl.clk_en_monitor=%d\n", clockCtrl.clk_en_monitor));
		Ddim_Print(("Im_MXIC_Get_Clock_Enable OK(self->unit=%d).\n", self->unit));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Clock_Enable NG(self->unit=%d). result=0x%X\n", self->unit, result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func1_04(CtImMxicFunc1* self)
{
	kint32								result;
	kuint32								workvalue;
	kuint32								i, j;
	kuchar								capability = 0;
	T_IM_MXIC_ALL_ACCEPTANCE_CAPABILITY	allCapability;

	Ddim_Print(("ct_im_mxic_func1_04(self->unit=%d)\n", self->unit));

	workvalue = 1;

	for (i=E_IM_MXIC_W_ARBITER_W1; i<E_IM_MXIC_W_ARBITER_MAX; i++) {
		for (j=E_IM_MXIC_PORT_0; j<E_IM_MXIC_PORT_MAX; j++) {
			allCapability.w_capability[i][j] = workvalue;
		}
	}
	for (i=E_IM_MXIC_R_ARBITER_R1; i<E_IM_MXIC_R_ARBITER_MAX; i++) {
		for (j=E_IM_MXIC_PORT_0; j<E_IM_MXIC_PORT_MAX; j++) {
			allCapability.r_capability[i][j] = workvalue;
		}
	}
	for (i=E_IM_MXIC_W_ARBITER_GR_W0; i<E_IM_MXIC_W_ARBITER_GR_MAX; i++) {
		for (j=E_IM_MXIC_PORT_GR_0; j<E_IM_MXIC_PORT_GR_MAX; j++) {
			allCapability.w_capability_gr[i][j] = workvalue;
		}
	}
	for (i=E_IM_MXIC_R_ARBITER_GR_R0; i<E_IM_MXIC_R_ARBITER_GR_MAX; i++) {
		for (j=E_IM_MXIC_PORT_GR_0; j<E_IM_MXIC_PORT_GR_MAX; j++) {
			allCapability.r_capability_gr[i][j] = workvalue;
		}
	}

	result = Im_MXIC_Set_Acceptance_Capability_All_Port( (E_IM_MXIC_UNIT)self->unit, &allCapability );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Acceptance_Capability_All_Port OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Acceptance_Capability_All_Port NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Get_Acceptance_Capability_All_Port( (E_IM_MXIC_UNIT)self->unit, &allCapability );
	if (result == D_DDIM_OK) {
		ct_im_mxic_print_all_acceptance_capability(&allCapability);
		Ddim_Print(("Im_MXIC_Get_Acceptance_Capability_All_Port OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Acceptance_Capability_All_Port NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Acceptance_Capability( (E_IM_MXIC_UNIT)self->unit,
												(E_IM_MXIC_WR_ARBITER)0,
												(E_IM_MXIC_SPEC_ARBITER)0,
												(E_IM_MXIC_PORT)0,
												(kuchar)8);
	if (result == D_DDIM_OK) {
		Ddim_Print(("Im_MXIC_Set_Acceptance_Capability OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Acceptance_Capability NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Get_Acceptance_Capability( (E_IM_MXIC_UNIT)self->unit,
												(E_IM_MXIC_WR_ARBITER)0,
												(E_IM_MXIC_SPEC_ARBITER)0,
												(E_IM_MXIC_PORT)0,
												&capability);
	if (result == D_DDIM_OK) {
		Ddim_Print(("capability = %d\n", capability));
		Ddim_Print(("Im_MXIC_Get_Acceptance_Capability OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Acceptance_Capability NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Acceptance_Capability_Group( (E_IM_MXIC_WR_ARBITER)0,
													  (E_IM_MXIC_SPEC_ARBITER_GR)0,
													  (E_IM_MXIC_PORT_GR)0,
													  (kuchar)1 );
	if (result == D_DDIM_OK) {
		Ddim_Print(("Im_MXIC_Set_Acceptance_Capability_Group OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Acceptance_Capability_Group NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Get_Acceptance_Capability_Group( (E_IM_MXIC_WR_ARBITER)0,
													  (E_IM_MXIC_SPEC_ARBITER_GR)0,
													  (E_IM_MXIC_PORT_GR)0,
													  &capability );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("capability = %d\n", capability));
		Ddim_Print(("Im_MXIC_Get_Acceptance_Capability_Group OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Acceptance_Capability_Group NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func1_05(CtImMxicFunc1* self)
{
	kint32						result;
	T_IM_MXIC_ALL_SLAVE_AREA	allSlaveArea;
	T_IM_MXIC_SLAVE_AREA		slaveArea;

	Ddim_Print(("ct_im_mxic_func1_05(self->unit=%d)\n", self->unit));

	allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_1].size    = (kuint32)0x20000000;
	allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_1].address = (kuint32)0x40000000;
	allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_2].size    = (kuint32)0x20000000;
	allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_2].address = (kuint32)0x60000000;
	allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_3].size    = (kuint32)0x20000000;
	allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_3].address = (kuint32)0x80000000;
	allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_4].size    = (kuint32)0x20000000;
	allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_4].address = (kuint32)0xA0000000;

	result = Im_MXIC_Set_Slave_Area_All( (E_IM_MXIC_UNIT)self->unit, &allSlaveArea );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Slave_Area_All OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Slave_Area_All NG. result=0x%X\n", result));
	}

	memset( &allSlaveArea, 0, sizeof(T_IM_MXIC_ALL_SLAVE_AREA) );

	result = Im_MXIC_Get_Slave_Area_All( (E_IM_MXIC_UNIT)self->unit, &allSlaveArea );
	if ( result == D_DDIM_OK ) {
		ct_im_mxic_print_all_slave_area( &allSlaveArea );
		Ddim_Print(("Im_MXIC_Get_Slave_Area_All OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Slave_Area_All NG. result=0x%X\n", result));
	}

	slaveArea.size    = (kuint32)0x40000000;
	slaveArea.address = (kuint32)0x40000000;

	result = Im_MXIC_Set_Slave_Area( (E_IM_MXIC_UNIT)self->unit, (E_IM_MXIC_SLAVE_NUMBER)0, &slaveArea );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Slave_Area OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Slave_Area NG. result=0x%X\n", result));
	}

	memset( &slaveArea, 0, sizeof(T_IM_MXIC_SLAVE_AREA) );

	result = Im_MXIC_Get_Slave_Area( (E_IM_MXIC_UNIT)self->unit, (E_IM_MXIC_SLAVE_NUMBER)0, &slaveArea );
	if ( result == D_DDIM_OK ) {
		ct_im_mxic_print_slave_area( &slaveArea );
		Ddim_Print(("Im_MXIC_Get_Slave_Area OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Slave_Area NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func1_06(CtImMxicFunc1* self)
{
	kint32							result;
	T_IM_MXIC_ALL_ARBITER_ASSIGN		allArbiterAssign;
	T_IM_MXIC_W_ARBITER_ASSIGN_PORT	wSlotStatus;
	T_IM_MXIC_R_ARBITER_ASSIGN_PORT	rSlotStatus;

	Ddim_Print(("ct_im_mxic_func1_06(self->unit=%d)\n", self->unit));

	result = ct_im_mxic_create_master_all_arbiter_param( (E_IM_MXIC_UNIT)self->unit, &allArbiterAssign );
	if ( result == D_DDIM_OK ) {
		// Execute function.
		result = Im_MXIC_Set_Master_All_Arbiter( (E_IM_MXIC_UNIT)self->unit, &allArbiterAssign );
		if ( result == D_DDIM_OK ) {
			Ddim_Print(("Im_MXIC_Set_Master_All_Arbiter OK.\n"));
		}
		else {
			Ddim_Print(("E:Im_MXIC_Set_Master_All_Arbiter NG. result=0x%X\n", result));
		}
	}

	memset( &allArbiterAssign, 0, sizeof(T_IM_MXIC_ALL_ARBITER_ASSIGN) );

	result = Im_MXIC_Get_Master_All_Arbiter( (E_IM_MXIC_UNIT)self->unit, &allArbiterAssign );
	if ( result == D_DDIM_OK ) {
		ct_im_mxic_print_all_arbiter_assign(  &allArbiterAssign );
		Ddim_Print(("Im_MXIC_Get_Master_All_Arbiter OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Master_All_Arbiter NG. result=0x%X\n", result));
	}

	result = ct_im_mxic_create_master_w_arbiter_param( (E_IM_MXIC_UNIT)self->unit, &wSlotStatus );
	if ( result == D_DDIM_OK ) {
		// Execute function.
		result = Im_MXIC_Set_Master_W_Arbiter( (E_IM_MXIC_UNIT)self->unit, (E_IM_MXIC_W_ARBITER)0, &wSlotStatus );
		if (result == D_DDIM_OK) {
			Ddim_Print(("Im_MXIC_Set_Master_W_Arbiter OK.\n"));
		}
		else {
			Ddim_Print(("E:Im_MXIC_Set_Master_W_Arbiter NG. result=0x%X\n", result));
		}
	}

	memset( &wSlotStatus, 0, sizeof(T_IM_MXIC_W_ARBITER_ASSIGN_PORT) );

	result = Im_MXIC_Get_Master_W_Arbiter( (E_IM_MXIC_UNIT)self->unit, (E_IM_MXIC_W_ARBITER)0, &wSlotStatus );
	if ( result == D_DDIM_OK ) {
		ct_im_mxic_print_w_arbiter_assign(  &wSlotStatus );
		Ddim_Print(("Im_MXIC_Get_Master_W_Arbiter OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Master_W_Arbiter NG. result=0x%X\n", result));
	}

	result = ct_im_mxic_create_master_r_arbiter_param( (E_IM_MXIC_UNIT)self->unit, &rSlotStatus );
	if ( result == D_DDIM_OK ) {
		// Execute function.
		result = Im_MXIC_Set_Master_R_Arbiter( (E_IM_MXIC_UNIT)self->unit, (E_IM_MXIC_R_ARBITER)0, &rSlotStatus );
		if ( result == D_DDIM_OK ) {
			Ddim_Print(("Im_MXIC_Set_Master_R_Arbiter OK.\n"));
		}
		else {
			Ddim_Print(("E:Im_MXIC_Set_Master_R_Arbiter NG. result=0x%X\n", result));
		}
	}

	memset( &rSlotStatus, 0, sizeof(T_IM_MXIC_R_ARBITER_ASSIGN_PORT) );

	result = Im_MXIC_Get_Master_R_Arbiter( (E_IM_MXIC_UNIT)self->unit, (E_IM_MXIC_R_ARBITER)0, &rSlotStatus );
	if ( result == D_DDIM_OK ) {
		ct_im_mxic_print_r_arbiter_assign(  &rSlotStatus );
		Ddim_Print(("Im_MXIC_Get_Master_R_Arbiter OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Master_R_Arbiter NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func1_07(CtImMxicFunc1* self)
{
	kint32								result;
	T_IM_MXIC_ALL_SLOT_PRIORITY_LEVEL	allLevelCtrl;
	T_IM_MXIC_SLOT_PRIORITY_LEVEL		levelCtrl;

	Ddim_Print(("ct_im_mxic_func1_07(self->unit=%d)\n", self->unit));

	result = ct_im_mxic_create_slot_priority_all_arbiter_param( &allLevelCtrl );
	if ( result == D_DDIM_OK ) {
		// Execute function.
		result = Im_MXIC_Set_Slot_Priority_All_Arbiter( (E_IM_MXIC_UNIT)self->unit, &allLevelCtrl);
		if (result == D_DDIM_OK) {
			Ddim_Print(("Im_MXIC_Set_Slot_Priority_All_Arbiter OK.\n"));
		}
		else {
			Ddim_Print(("E:Im_MXIC_Set_Slot_Priority_All_Arbiter NG. result=0x%X\n", result));
		}
	}

	result = Im_MXIC_Get_Slot_Priority_All_Arbiter( (E_IM_MXIC_UNIT)self->unit, &allLevelCtrl );
	if ( result == D_DDIM_OK ) {
		ct_im_mxic_print_all_slot_priority_level(  &allLevelCtrl );
		Ddim_Print(("Im_MXIC_Get_Slot_Priority_All_Arbiter OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Slot_Priority_All_Arbiter NG. result=0x%X\n", result));
	}

	levelCtrl.priority_level_type  = (kuchar)1;
	levelCtrl.upper_priority_level = (kuchar)0;
	levelCtrl.lower_priority_level = (kuchar)63;

	result = Im_MXIC_Set_Slot_Priority( (E_IM_MXIC_UNIT)self->unit,
										(E_IM_MXIC_WR_ARBITER)0,
										(E_IM_MXIC_SPEC_ARBITER)0,
										(E_IM_MXIC_PORT)0,
										(E_IM_MXIC_SLOT_LEVEL_CTRL)0,
										&levelCtrl);
	if (result == D_DDIM_OK) {
		Ddim_Print(("Im_MXIC_Set_Slot_Priority OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Slot_Priority NG. result=0x%X\n", result));
	}

	memset( &levelCtrl, 0, sizeof(T_IM_MXIC_SLOT_PRIORITY_LEVEL) );

	result = Im_MXIC_Get_Slot_Priority( (E_IM_MXIC_UNIT)self->unit,
										(E_IM_MXIC_WR_ARBITER)0,
										(E_IM_MXIC_SPEC_ARBITER)0,
										(E_IM_MXIC_PORT)0,
										(E_IM_MXIC_SLOT_LEVEL_CTRL)0,
										&levelCtrl);
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("priority_level_type  = %d\n", levelCtrl.priority_level_type));
		Ddim_Print(("upper_priority_level = %d\n", levelCtrl.upper_priority_level));
		Ddim_Print(("lower_priority_level = %d\n", levelCtrl.lower_priority_level));
		Ddim_Print(("Im_MXIC_Get_Slot_Priority OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Slot_Priority NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func1_08(CtImMxicFunc1* self)
{
	kint32	result;
	kuchar	masterPriority;

	Ddim_Print(("ct_im_mxic_func1_08(self->unit=%d)\n", self->unit));

	result = Im_MXIC_Set_Master_Priority( (E_IM_MXIC_UNIT)self->unit,
										  (kuchar)0x81,
										  (kuchar)3 );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Priority OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Priority NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Get_Master_Priority( (E_IM_MXIC_UNIT)self->unit, (kuchar)0x81, &masterPriority );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("masterPriority = %d\n", masterPriority));
		Ddim_Print(("Im_MXIC_Get_Master_Priority OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Master_Priority NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func1_09(CtImMxicFunc1* self)
{
	kint32	result;
	kuchar	maskEnable;

	Ddim_Print(("ct_im_mxic_func1_09(self->unit=%d)\n", self->unit));

	result = Im_MXIC_Set_Slot_Mask( (E_IM_MXIC_UNIT)self->unit,
									(E_IM_MXIC_WR_ARBITER)1,
									(E_IM_MXIC_SPEC_ARBITER)0,
									(E_IM_MXIC_PORT)0,
									(E_IM_MXIC_SLOT)0,
									(kuchar)1 );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Slot_Mask OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Slot_Mask NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Get_Slot_Mask( (E_IM_MXIC_UNIT)self->unit,
									(E_IM_MXIC_WR_ARBITER)1,
									(E_IM_MXIC_SPEC_ARBITER)0,
									(E_IM_MXIC_PORT)0,
									(E_IM_MXIC_SLOT)0,
									&maskEnable);
	if (result == D_DDIM_OK) {
		Ddim_Print(("maskEnable = %d\n", maskEnable));
		Ddim_Print(("Im_MXIC_Get_Slot_Mask OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Slot_Mask NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func1_10(CtImMxicFunc1* self)
{
	kint32					result;
	T_IM_MXIC_MASTER_MASK	master_mask;

	Ddim_Print(("ct_im_mxic_func1_10(self->unit=%d)\n", self->unit));

	master_mask.mask_type   = (kuchar)2;
	master_mask.mask_period = (USHORT)4;

	result = Im_MXIC_Set_Master_Mask( (E_IM_MXIC_UNIT)self->unit, (kuchar)0x81, &master_mask );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask NG. result=0x%X\n", result));
	}

	memset( &master_mask, 0, sizeof(T_IM_MXIC_MASTER_MASK) );

	result = Im_MXIC_Get_Master_Mask( (E_IM_MXIC_UNIT)self->unit, (kuchar)0x81, &master_mask );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("master_mask.mask_type   = %d\n", master_mask.mask_type));
		Ddim_Print(("master_mask.mask_period = %d\n", master_mask.mask_period));
		Ddim_Print(("Im_MXIC_Get_Master_Mask OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Master_Mask NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}


void ct_im_mxic_func1_11(CtImMxicFunc1* self)
{
	kint32	result;
	kuchar	maskEnable;
	kuchar	maskSelect;

	Ddim_Print(("ct_im_mxic_func1_11(self->unit=%d)\n", self->unit));

	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (kuchar)0x81,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (kuchar)1 );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor NG. result=0x%X\n", result));
	}

	maskEnable = 0;

	result = Im_MXIC_Get_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (kuchar)0x81,
											 (E_IM_MXIC_MASK_GROUP)0,
											 &maskEnable );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("maskEnable = %d\n", maskEnable));
		Ddim_Print(("Im_MXIC_Get_Master_Mask_Factor OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Master_Mask_Factor NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (kuchar)0x82,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (kuchar)1 );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target NG. result=0x%X\n", result));
	}

	maskEnable = 0;

	result = Im_MXIC_Get_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (kuchar)0x82,
											 (E_IM_MXIC_MASK_GROUP)0,
											 &maskEnable );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("maskEnable = %d\n", maskEnable));
		Ddim_Print(("Im_MXIC_Get_Master_Mask_Target OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Master_Mask_Target NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Select( (E_IM_MXIC_UNIT)self->unit,
											 (kuchar)0x81,
											 (kuchar)1 );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Select OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Select NG. result=0x%X\n", result));
	}

	maskSelect = 0;

	result = Im_MXIC_Get_Master_Mask_Select( (E_IM_MXIC_UNIT)self->unit,
											 (kuchar)0x81,
											 &maskSelect );
	if ( result == D_DDIM_OK ) {
		Ddim_Print(("maskSelect = %d\n", maskSelect));
		Ddim_Print(("Im_MXIC_Get_Master_Mask_Select OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Master_Mask_Select NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}

CtImMxicFunc1* ct_im_mxic_func1_new(void) 
{
    CtImMxicFunc1 *self = k_object_new_with_private(CT_TYPE_IM_MXIC_FUNC1, sizeof(CtImMxicFunc1Private));
    return self;
}
