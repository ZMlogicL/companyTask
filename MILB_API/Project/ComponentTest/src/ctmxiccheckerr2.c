/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtMxicCheckErr2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "im_mxic.h"
//#include "ct_im_mxic.h"
#include <string.h>
#include <stdlib.h>

#include "dd_top.h"

#include "ddim_user_custom.h"

#include "ctmxiccheckerr2.h"


G_DEFINE_TYPE(CtMxicCheckErr2, ct_mxic_check_err2, G_TYPE_OBJECT);
#define CT_MXIC_CHECK_ERR2_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_MXIC_CHECK_ERR2, CtMxicCheckErr2Private))

struct _CtMxicCheckErr2Private
{

};


/*
*DECLS
*/
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
/*
*IMPL
*/

static void ct_mxic_check_err2_class_init(CtMxicCheckErr2Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtMxicCheckErr2Private));
}

static void ct_mxic_check_err2_init(CtMxicCheckErr2 *self)
{
//	CtMxicCheckErr2Private *priv = CT_MXIC_CHECK_ERR2_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
//	CtMxicCheckErr2 *self = (CtMxicCheckErr2*)object;
//	CtMxicCheckErr2Private *priv = CT_MXIC_CHECK_ERR2_GET_PRIVATE(self);
}

static void finalize_od(GObject *object)
{
//	CtMxicCheckErr2 *self = (CtMxicCheckErr2*)object;
//	CtMxicCheckErr2Private *priv = CT_MXIC_CHECK_ERR2_GET_PRIVATE(self);
}


/*
*PUBLIC
*/
// Error test of Im_MXIC_Set_Slot_Priority_All_Arbiter and Im_MXIC_Get_Slot_Priority_All_Arbiter function.
void ct_mxic_check_err2_slot_priority_all_arbiter(void)
{
	gint32								result;
	T_IM_MXIC_ALL_SLOT_PRIORITY_LEVEL	allLevelCtrl;

	// --- Im_MXIC_Set_Slot_Priority_All_Arbiter ---
	// all_priority unit check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Priority_All_Arbiter(): all_priority unit check]----\n"));
	result = Im_MXIC_Set_Slot_Priority_All_Arbiter((E_IM_MXIC_UNIT)7, &allLevelCtrl);
	Ddim_Print(("result=%d\n", result));

	// all_priority NULL check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Priority_All_Arbiter(): all_priority NULL check]----\n"));
	result = Im_MXIC_Set_Slot_Priority_All_Arbiter((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Slot_Priority_All_Arbiter ---
	// all_priority unit check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Priority_All_Arbiter(): all_priority unit check]----\n"));
	result = Im_MXIC_Get_Slot_Priority_All_Arbiter((E_IM_MXIC_UNIT)7, &allLevelCtrl);
	Ddim_Print(("result=%d\n", result));
#if 1
	// all_priority NULL check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Priority_All_Arbiter(): all_priority NULL check]----\n"));
	result = Im_MXIC_Get_Slot_Priority_All_Arbiter((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));
#endif
	return;
}

// Error test of Im_MXIC_Set_Master_Priority and Im_MXIC_Get_Master_Priority function.
void ct_mxic_check_err2_master_priority(void)
{
	gint32	result;
	guchar	masterPriority;

	// --- Im_MXIC_Set_Master_Priority ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_Priority(): unit range error check]----\n"));
	result = Im_MXIC_Set_Master_Priority((E_IM_MXIC_UNIT)7, D_IM_MXIC_0_W_SEN_0, D_IM_MXIC_MASTER_MOVE_15);
	Ddim_Print(("result=%d\n", result));

	// priority range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_Priority(): priority range error check]----\n"));
	result = Im_MXIC_Set_Master_Priority((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0, (D_IM_MXIC_MASTER_MOVE_15 + 1));
	Ddim_Print(("result=%d\n", result));

	// priority unit check
	Ddim_Print(("----[Im_MXIC_Get_Master_Priority(): unit range error check]----\n"));
	result = Im_MXIC_Get_Master_Priority((E_IM_MXIC_UNIT)7, D_IM_MXIC_0_W_SEN_0, &masterPriority);
	Ddim_Print(("result=%d\n", result));

	// priority NULL check
	Ddim_Print(("----[Im_MXIC_Get_Master_Priority(): priority range error check]----\n"));
	result = Im_MXIC_Get_Master_Priority((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Slot_Mask and Im_MXIC_Get_Slot_Mask function.
void ct_mxic_check_err2_slot_mask(void)
{
	gint32 result;
	guchar maskEnable;

	// --- Im_MXIC_Set_Slot_Mask ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Mask(): unit range error check]----\n"));
	result = Im_MXIC_Set_Slot_Mask((E_IM_MXIC_UNIT)7, E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_1,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_0, D_IM_MXIC_ON);
	Ddim_Print(("result=%d\n", result));

	// write or read arbiter range error check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Mask(): wr_arbiter range error check]----\n"));
	result = Im_MXIC_Set_Slot_Mask((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_MAX, E_IM_MXIC_SPEC_ARBITER_1,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_0, D_IM_MXIC_ON);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Mask(): arbiter range error check]----\n"));
	result = Im_MXIC_Set_Slot_Mask((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_MAX,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_0, D_IM_MXIC_ON);
	Ddim_Print(("result=%d\n", result));

	// slot range error check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Mask(): port range error check]----\n"));
	result = Im_MXIC_Set_Slot_Mask((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_2,
			E_IM_MXIC_PORT_MAX, E_IM_MXIC_SLOT_0, D_IM_MXIC_ON);
	Ddim_Print(("result=%d\n", result));

	// slot range error check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Mask(): slot range error check]----\n"));
	result = Im_MXIC_Set_Slot_Mask((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_2,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_MAX, D_IM_MXIC_ON);
	Ddim_Print(("result=%d\n", result));

	// maskEnable range error check
	Ddim_Print(("----[Im_MXIC_Set_Slot_Mask(): maskEnable range error check]----\n"));
	result = Im_MXIC_Set_Slot_Mask((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_2,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_3, 2);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Slot_Mask ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Mask(): unit range error check]----\n"));
	result = Im_MXIC_Get_Slot_Mask((E_IM_MXIC_UNIT)7, E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_1,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_0, &maskEnable);
	Ddim_Print(("result=%d\n", result));

	// write or read arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Mask(): wr_arbiter range error check]----\n"));
	result = Im_MXIC_Get_Slot_Mask((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_MAX, E_IM_MXIC_SPEC_ARBITER_1,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_0, &maskEnable);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Mask(): arbiter range error check]----\n"));
	result = Im_MXIC_Get_Slot_Mask((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_MAX,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_0, &maskEnable);
	Ddim_Print(("result=%d\n", result));

	// port range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Mask(): port range error check]----\n"));
	result = Im_MXIC_Get_Slot_Mask((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_2,
			E_IM_MXIC_PORT_MAX, E_IM_MXIC_SLOT_0, &maskEnable);
	Ddim_Print(("result=%d\n", result));

	// slot range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Mask(): slot range error check]----\n"));
	result = Im_MXIC_Get_Slot_Mask((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_R, E_IM_MXIC_SPEC_ARBITER_2,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_MAX, &maskEnable);
	Ddim_Print(("result=%d\n", result));

	// maskEnable NULL check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Mask(): maskEnable NULL check]----\n"));
	result = Im_MXIC_Get_Slot_Mask((E_IM_MXIC_UNIT)0, E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_2,
			E_IM_MXIC_PORT_0, E_IM_MXIC_SLOT_3, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Master_Mask and Im_MXIC_Get_Master_Mask function.
void ct_mxic_check_err2_master_mask(void)
{
	gint32					result;
	T_IM_MXIC_MASTER_MASK	masterMask;

	// --- Im_MXIC_Set_Master_Mask ---
	// mask unit check
	Ddim_Print(("----[Im_MXIC_Set_Master_Mask(): mask unit check]----\n"));
	result = Im_MXIC_Set_Master_Mask((E_IM_MXIC_UNIT)7, D_IM_MXIC_0_W_SEN_0, &masterMask);
	Ddim_Print(("result=%d\n", result));

	// mask NULL check
	Ddim_Print(("----[Im_MXIC_Set_Master_Mask(): mask NULL check]----\n"));
	result = Im_MXIC_Set_Master_Mask((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0, NULL);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Master_Mask ---
	// mask unit check
	Ddim_Print(("----[Im_MXIC_Get_Master_Mask(): mask unit check]----\n"));
	result = Im_MXIC_Get_Master_Mask((E_IM_MXIC_UNIT)7, D_IM_MXIC_0_W_SEN_0, &masterMask);
	Ddim_Print(("result=%d\n", result));

	// mask NULL check
	Ddim_Print(("----[Im_MXIC_Get_Master_Mask(): mask NULL check]----\n"));
	result = Im_MXIC_Get_Master_Mask((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Master_Mask_Factor and Im_MXIC_Get_Master_Mask_Factor function.
void ct_mxic_check_err2_master_mask_factor(void)
{
	gint32 result;
	guchar enable;

	// --- Im_MXIC_Set_Master_Mask_Factor ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_Mask_Factor(): unit range error check]----\n"));
	result = Im_MXIC_Set_Master_Mask_Factor((E_IM_MXIC_UNIT)7, D_IM_MXIC_0_W_SEN_0, E_IM_MXIC_MASK_GROUP_B,
			D_IM_MXIC_ON);
	Ddim_Print(("result=%d\n", result));

	// group range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_Mask_Factor(): group range error check]----\n"));
	result = Im_MXIC_Set_Master_Mask_Factor((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0, E_IM_MXIC_MASK_GROUP_MAX,
			D_IM_MXIC_ON);
	Ddim_Print(("result=%d\n", result));

	// enable range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_Mask_Factor(): enable range error check]----\n"));
	result = Im_MXIC_Set_Master_Mask_Factor((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0, E_IM_MXIC_MASK_GROUP_B, 2);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Master_Mask_Factor ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Get_Master_Mask_Factor(): unit range error check]----\n"));
	result = Im_MXIC_Get_Master_Mask_Factor((E_IM_MXIC_UNIT)7, D_IM_MXIC_0_W_SEN_0,
			E_IM_MXIC_MASK_GROUP_B, &enable);
	Ddim_Print(("result=%d\n", result));

	// group range error check
	Ddim_Print(("----[Im_MXIC_Get_Master_Mask_Factor(): group range error check]----\n"));
	result = Im_MXIC_Get_Master_Mask_Factor((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0,
			E_IM_MXIC_MASK_GROUP_MAX, &enable);
	Ddim_Print(("result=%d\n", result));

	// enable range error check
	Ddim_Print(("----[Im_MXIC_Get_Master_Mask_Factor(): enable range error check]----\n"));
	result = Im_MXIC_Get_Master_Mask_Factor((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0,
			E_IM_MXIC_MASK_GROUP_B, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Master_Mask_Target and Im_MXIC_Get_Master_Mask_Target function.
void ct_mxic_check_err2_master_mask_target(void)
{
	gint32 result;
	guchar enable;

	// --- Im_MXIC_Set_Master_Mask_Target ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_Mask_Target(): unit range error check]----\n"));
	result = Im_MXIC_Set_Master_Mask_Target((E_IM_MXIC_UNIT)7, D_IM_MXIC_0_W_SEN_0, E_IM_MXIC_MASK_GROUP_B,
			D_IM_MXIC_ON);
	Ddim_Print(("result=%d\n", result));

	// group range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_Mask_Target(): group range error check]----\n"));
	result = Im_MXIC_Set_Master_Mask_Target((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0, E_IM_MXIC_MASK_GROUP_MAX,
			D_IM_MXIC_ON);
	Ddim_Print(("result=%d\n", result));

	// enable range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_Mask_Target(): enable range error check]----\n"));
	result = Im_MXIC_Set_Master_Mask_Target((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0, E_IM_MXIC_MASK_GROUP_B, 2);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Master_Mask_Target ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Get_Master_Mask_Target(): unit range error check]----\n"));
	result = Im_MXIC_Get_Master_Mask_Target((E_IM_MXIC_UNIT)7, D_IM_MXIC_0_W_SEN_0,
			E_IM_MXIC_MASK_GROUP_B, &enable);
	Ddim_Print(("result=%d\n", result));

	// group range error check
	Ddim_Print(("----[Im_MXIC_Get_Master_Mask_Target(): group range error check]----\n"));
	result = Im_MXIC_Get_Master_Mask_Target((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0,
			E_IM_MXIC_MASK_GROUP_MAX, &enable);
	Ddim_Print(("result=%d\n", result));

	// enable range error check
	Ddim_Print(("----[Im_MXIC_Get_Master_Mask_Target(): enable range error check]----\n"));
	result = Im_MXIC_Get_Master_Mask_Target((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0,
			E_IM_MXIC_MASK_GROUP_B, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Master_Mask_Select and Im_MXIC_Get_Master_Mask_Select function.
void ct_mxic_check_err2_master_mask_select(void)
{
	gint32	result;
	guchar	maskSelect;

	// --- Im_MXIC_Set_Master_Mask_Select ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_Mask_Select(): unit range error check]----\n"));
	result = Im_MXIC_Set_Master_Mask_Select((E_IM_MXIC_UNIT)7, D_IM_MXIC_0_W_SEN_0, 1);
	Ddim_Print(("result=%d\n", result));

	// select range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_Mask_Select(): select range error check]----\n"));
	result = Im_MXIC_Set_Master_Mask_Select((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0, 2);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Master_Mask_Select ---
	// select unit check
	Ddim_Print(("----[Im_MXIC_Get_Master_Mask_Select(): select unit check]----\n"));
	result = Im_MXIC_Get_Master_Mask_Select((E_IM_MXIC_UNIT)7, D_IM_MXIC_0_W_SEN_0, &maskSelect);
	Ddim_Print(("result=%d\n", result));

	// select NULL check
	Ddim_Print(("----[Im_MXIC_Get_Master_Mask_Select(): select NULL check]----\n"));
	result = Im_MXIC_Get_Master_Mask_Select((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Master_Transaction and Im_MXIC_Get_Master_Transaction function.
void ct_mxic_check_err2_master_transaction(void)
{
	gint32	result;
	guchar	transaction;

	// --- Im_MXIC_Set_Master_Transaction ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_Mask(): unit range error check]----\n"));
	result = Im_MXIC_Set_Master_Transaction((E_IM_MXIC_UNIT)7, D_IM_MXIC_0_W_SEN_0, 63);
	Ddim_Print(("result=%d\n", result));

	// transaction range error check
	Ddim_Print(("----[Im_MXIC_Set_Master_Mask(): transaction range error check]----\n"));
	result = Im_MXIC_Set_Master_Transaction((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0, 64);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_Master_Transaction ---
	// transaction unit check
	Ddim_Print(("----[Im_MXIC_Get_Master_Mask(): mask unit check]----\n"));
	result = Im_MXIC_Get_Master_Transaction((E_IM_MXIC_UNIT)7, D_IM_MXIC_0_W_SEN_0, &transaction);
	Ddim_Print(("result=%d\n", result));

	// transaction NULL check
	Ddim_Print(("----[Im_MXIC_Get_Master_Mask(): mask NULL check]----\n"));
	result = Im_MXIC_Get_Master_Transaction((E_IM_MXIC_UNIT)0, D_IM_MXIC_0_W_SEN_0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_History_Monitor_Stop_Enable and Im_MXIC_Get_History_Monitor_Stop_Enable function.
void ct_mxic_check_err2_history_monitor_stop_enable(void)
{
	gint32 result;

	// --- Im_MXIC_Set_History_Monitor_Stop_Enable ---
	// enable range error check
	Ddim_Print(("----[Im_MXIC_Set_History_Monitor_Stop_Enable(): enable range error check]----\n"));
	result = Im_MXIC_Set_History_Monitor_Stop_Enable(2);
	Ddim_Print(("result=%d\n", result));

	// --- Im_MXIC_Get_History_Monitor_Stop_Enable ---
	// enable NULL check
	Ddim_Print(("----[Im_MXIC_Get_History_Monitor_Stop_Enable(): enable NULL check]----\n"));
	result = Im_MXIC_Get_History_Monitor_Stop_Enable(NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_History_Monitor function.
void ct_mxic_check_err2_history_monitor(void)
{
	gint32 result;
	T_IM_MXIC_HISTORY_MONITOR history;

	// --- Im_MXIC_Get_History_Monitor ---
	// write or read arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_History_Monitor(): wr_arbiter range error check]----\n"));
	result = Im_MXIC_Get_History_Monitor(E_IM_MXIC_WR_ARBITER_MAX, E_IM_MXIC_SPEC_ARBITER_1,
			E_IM_MXIC_PORT_0, &history);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_History_Monitor(): arbiter range error check]----\n"));
	result = Im_MXIC_Get_History_Monitor(E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_MAX,
			E_IM_MXIC_PORT_0, &history);
	Ddim_Print(("result=%d\n", result));

	// port range error check
	Ddim_Print(("----[Im_MXIC_Get_History_Monitor(): port range error check]----\n"));
	result = Im_MXIC_Get_History_Monitor(E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_1,
			E_IM_MXIC_PORT_MAX, &history);
	Ddim_Print(("result=%d\n", result));

	// history NULL check
	Ddim_Print(("----[Im_MXIC_Get_History_Monitor(): history NULL check]----\n"));
	result = Im_MXIC_Get_History_Monitor(E_IM_MXIC_WR_ARBITER_W, E_IM_MXIC_SPEC_ARBITER_1,
			E_IM_MXIC_PORT_1, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_History_Monitor_All_Port function.
void ct_mxic_check_err2_history_monitor_all_port(void)
{
	gint32 result;

	// --- Im_MXIC_Get_History_Monitor_All_Port ---
	// all_history NULL check
	Ddim_Print(("----[Im_MXIC_Get_History_Monitor_All_Port(): all_history NULL check]----\n"));
	result = Im_MXIC_Get_History_Monitor_All_Port(NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter function.
void ct_mxic_check_err2_slot_status_monitor_all_arbiter(void)
{
	gint32								result;
	T_IM_MXIC_ALL_SLOT_STATUS_MONITOR	allSlotStatus;

	// --- Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter ---
	// all_status unit check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter(): all_status unit check]----\n"));
	result = Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter((E_IM_MXIC_UNIT)7, &allSlotStatus);
	Ddim_Print(("result=%d\n", result));

	// all_status NULL check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter(): all_status NULL check]----\n"));
	result = Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter function.
void ct_mxic_check_err2_slot_status_monitor_w_arbiter(void)
{
	gint32 result;
	T_IM_MXIC_W_ARBITER_ASSIGN_PORT status;

	// --- Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter(): unit range error check]----\n"));
	result = Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter((E_IM_MXIC_UNIT)7, E_IM_MXIC_W_ARBITER_W2, &status);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter(): arbiter range error check]----\n"));
	result = Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_W_ARBITER_MAX, &status);
	Ddim_Print(("result=%d\n", result));

	// status NULL check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter(): status NULL check]----\n"));
	result = Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_W_ARBITER_W2, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter function.
void ct_mxic_check_err2_slot_status_monitor_r_arbiter(void)
{
	gint32 result;
	T_IM_MXIC_R_ARBITER_ASSIGN_PORT status;

	// --- Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter ---
	// unit range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter(): unit range error check]----\n"));
	result = Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter((E_IM_MXIC_UNIT)7, E_IM_MXIC_R_ARBITER_R2, &status);
	Ddim_Print(("result=%d\n", result));

	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter(): arbiter range error check]----\n"));
	result = Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_R_ARBITER_MAX, &status);
	Ddim_Print(("result=%d\n", result));

	// status NULL check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter(): status NULL check]----\n"));
	result = Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter((E_IM_MXIC_UNIT)0, E_IM_MXIC_R_ARBITER_R2, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter_Group function.
void ct_mxic_check_err2_slot_status_monitor_w_arbiter_group(void)
{
	gint32 result;
	T_IM_MXIC_W_ARBITER_ASSIGN_GR status;

	// --- Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter_Group ---
	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter_Group(): arbiter range error check]----\n"));
	result = Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter_Group(E_IM_MXIC_W_ARBITER_GR_MAX, &status);
	Ddim_Print(("result=%d\n", result));

	// status NULL check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter_Group(): status NULL check]----\n"));
	result = Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter_Group(E_IM_MXIC_W_ARBITER_GR_W1, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter_Group function.
void ct_mxic_check_err2_slot_status_monitor_r_arbiter_group(void)
{
	gint32 result;
	T_IM_MXIC_R_ARBITER_ASSIGN_GR status;

	// --- Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter_Group ---
	// arbiter range error check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter_Group(): arbiter range error check]----\n"));
	result = Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter_Group(E_IM_MXIC_R_ARBITER_GR_MAX, &status);
	Ddim_Print(("result=%d\n", result));

	// status NULL check
	Ddim_Print(("----[Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter_Group(): status NULL check]----\n"));
	result = Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter_Group(E_IM_MXIC_R_ARBITER_GR_R1, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_Master_Status_Monitor function.
void ct_mxic_check_err2_master_status_monitor(void)
{
	gint32							result;
	T_IM_MXIC_MASTER_STATUS_MONITOR	masterStatus;

	// --- Im_MXIC_Get_Master_Status_Monitor ---
	// status unit check
	Ddim_Print(("----[Im_MXIC_Get_Master_Status_Monitor(): status unit check]----\n"));
	result = Im_MXIC_Get_Master_Status_Monitor((E_IM_MXIC_UNIT)7, &masterStatus);
	Ddim_Print(("result=%d\n", result));

	// status NULL check
	Ddim_Print(("----[Im_MXIC_Get_Master_Status_Monitor(): status NULL check]----\n"));
	result = Im_MXIC_Get_Master_Status_Monitor((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter function.
void ct_mxic_check_err2_set_access_or_trans_monitor_parameter(void)
{
	gint32 result;
	T_IM_MXIC_MONITOR_PARAMETER param;

	// Initialize
	param.start_condition          = D_IM_MXIC_MONITOR_START_TRG;
	param.end_condition            = D_IM_MXIC_MONITOR_END_LIMIT;
	param.update_enable            = D_IM_MXIC_OFF;
	param.update_trigger_interval  = D_IM_MXIC_MONITOR_UPDATE_1;
	param.update_clear_en          = D_IM_MXIC_OFF;
	param.start_clear_en           = D_IM_MXIC_OFF;
	param.cnt_val                  = D_IM_MXIC_TRANS_COUNT_VALUE;
	param.limit_access_trans       = D_IM_MXIC_MONITOR_TRANSFER;
	param.limit_detection_target   = D_IM_MXIC_SLAVE_W1_PORT0;
	param.limit                    = 0xFFFFFFFF;
	param.target[0].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
	param.target[0].monitor_target = D_IM_MXIC_SLAVE_W1_PORT0;
	param.target[1].monitor_sel    = D_IM_MXIC_MONITOR_ACCESS;
	param.target[1].monitor_target = D_IM_MXIC_SLAVE_W2_PORT1;
	param.target[2].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
	param.target[2].monitor_target = D_IM_MXIC_SLAVE_R1_PORT0;
	param.target[3].monitor_sel    = D_IM_MXIC_MONITOR_ACCESS;
	param.target[3].monitor_target = D_IM_MXIC_SLAVE_R2_PORT1;
	param.pCallBack                = NULL;

	// --- Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter ---
	// param NULL check
	Ddim_Print(("----[Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter(): param NULL check]----\n"));
	result = Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter(NULL);
	Ddim_Print(("result=%d\n", result));

	// monitor_target range error check
	Ddim_Print(("----[Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter(): monitor_target range error check]----\n"));
	param.target[3].monitor_target = 0x100;
	result = Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter(&param);
	param.target[3].monitor_target = D_IM_MXIC_SLAVE_R2_PORT1;
	Ddim_Print(("result=%d\n", result));

	// limit_detection_target range error check
	Ddim_Print(("----[Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter(): "
			"limit_detection_target range error check]----\n"));
	param.limit_detection_target = 0x180;
	result = Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter(&param);
	param.limit_detection_target = D_IM_MXIC_SLAVE_W1_PORT0;
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_Access_Or_Trans_Monitor_Parameter function.
void ct_mxic_check_err2_get_access_or_trans_monitor_parameter(void)
{
	gint32 result;

	// --- Im_MXIC_Get_Access_Or_Trans_Monitor_Parameter ---
	// param NULL check
	Ddim_Print(("----[Im_MXIC_Get_Access_Or_Trans_Monitor_Parameter(): param NULL check]----\n"));
	result = Im_MXIC_Get_Access_Or_Trans_Monitor_Parameter(NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_Access_Or_Trans_Monitor function.
void ct_mxic_check_err2_access_or_trans_monitor(void)
{
	gint32 result;
	guint32 monitorResult;

	// --- Im_MXIC_Get_Access_Or_Trans_Monitor ---
	// entry range error check
	Ddim_Print(("----[Im_MXIC_Get_Access_Or_Trans_Monitor(): entry range error check]----\n"));
	result = Im_MXIC_Get_Access_Or_Trans_Monitor(4, &monitorResult);
	Ddim_Print(("result=%d\n", result));

	// result NULL check
	Ddim_Print(("----[Im_MXIC_Get_Access_Or_Trans_Monitor(): result NULL check]----\n"));
	result = Im_MXIC_Get_Access_Or_Trans_Monitor(0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_Access_Or_Trans_Monitor_All_Entry function.
void ct_mxic_check_err2_access_or_trans_monitor_all_entry(void)
{
	gint32 result;

	// --- Im_MXIC_Get_Access_Or_Trans_Monitor_All_Entry ---
	// all_result NULL check
	Ddim_Print(("----[Im_MXIC_Get_Access_Or_Trans_Monitor_All_Entry(): all_result NULL check]----\n"));
	result = Im_MXIC_Get_Access_Or_Trans_Monitor_All_Entry(NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_Access_Or_Trans_Monitor_Limit_End_State function.
void ct_mxic_check_err2_sccess_or_trans_monitor_limit_end_state(void)
{
	gint32 result;

	// --- Im_MXIC_Get_Access_Or_Trans_Monitor_Limit_End_State ---
	// mon_state NULL check
	Ddim_Print(("----[Im_MXIC_Get_Access_Or_Trans_Monitor_Limit_End_State(): mon_state NULL check]----\n"));
	result = Im_MXIC_Get_Access_Or_Trans_Monitor_Limit_End_State(NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Start_Memory_Access_Detect function.
void ct_mxic_check_err2_memory_access_start(void)
{
	gint32							result;
	T_IM_MXIC_MEMORY_ACCESS_SLAVE	memoryAccess;

	// --- Im_MXIC_Start_Memory_Access_Detect ---
	// param unit check
	Ddim_Print(("----[Im_MXIC_Start_Memory_Access_Detect(): param unit check]----\n"));
	result = Im_MXIC_Start_Memory_Access_Detect((E_IM_MXIC_UNIT)7, &memoryAccess);
	Ddim_Print(("result=%d\n", result));

	// param NULL check
	Ddim_Print(("----[Im_MXIC_Start_Memory_Access_Detect(): param NULL check]----\n"));
	result = Im_MXIC_Start_Memory_Access_Detect((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Set_Memory_Access_Detect function.
void ct_mxic_check_err2_memory_access_set(void)
{
	gint32							result;
	T_IM_MXIC_MEMORY_ACCESS_SLAVE	memoryAccess;

	// --- Im_MXIC_Set_Memory_Access_Detect ---
	// param unit check
	Ddim_Print(("----[Im_MXIC_Set_Memory_Access_Detect(): param unit check]----\n"));
	result = Im_MXIC_Set_Memory_Access_Detect((E_IM_MXIC_UNIT)7, &memoryAccess);
	Ddim_Print(("result=%d\n", result));

	// param NULL check
	Ddim_Print(("----[Im_MXIC_Set_Memory_Access_Detect(): param NULL check]----\n"));
	result = Im_MXIC_Set_Memory_Access_Detect((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

// Error test of Im_MXIC_Get_Memory_Access_Detect function.
void ct_mxic_check_err2_memory_access_get(void)
{
	gint32							result;
	T_IM_MXIC_MEMORY_ACCESS_SLAVE	memoryAccess;

	// --- Im_MXIC_Get_Memory_Access_Detect ---
	// param unit check
	Ddim_Print(("----[Im_MXIC_Get_Memory_Access_Detect(): param unit check]----\n"));
	result = Im_MXIC_Get_Memory_Access_Detect((E_IM_MXIC_UNIT)7, &memoryAccess);
	Ddim_Print(("result=%d\n", result));

	// param NULL check
	Ddim_Print(("----[Im_MXIC_Get_Memory_Access_Detect(): param NULL check]----\n"));
	result = Im_MXIC_Get_Memory_Access_Detect((E_IM_MXIC_UNIT)0, NULL);
	Ddim_Print(("result=%d\n", result));

	return;
}

CtMxicCheckErr2 *ct_mxic_check_err2_new(void) 
{
    CtMxicCheckErr2 *self = g_object_new(CT_TYPE_MXIC_CHECK_ERR2, NULL);
    return self;
}
