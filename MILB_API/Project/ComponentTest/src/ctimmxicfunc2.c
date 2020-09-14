/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImMxicFunc2类
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
#include "ctimmxicfunc2.h"


G_DEFINE_TYPE(CtImMxicFunc2, ct_im_mxic_func2, G_TYPE_OBJECT);
#define CT_IM_MXIC_FUNC2_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_MXIC_FUNC2, CtImMxicFunc2Private))

struct _CtImMxicFunc2Private
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

static void ct_im_mxic_func2_class_init(CtImMxicFunc2Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImMxicFunc2Private));
}

static void ct_im_mxic_func2_init(CtImMxicFunc2 *self)
{
//	CtImMxicFunc2Private *priv = CT_IM_MXIC_FUNC2_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
//	CtImMxicFunc2 *self = (CtImMxicFunc2*)object;
//	CtImMxicFunc2Private *priv = CT_IM_MXIC_FUNC2_GET_PRIVATE(self);
}

static void finalize_od(GObject *object)
{
//	CtImMxicFunc2 *self = (CtImMxicFunc2*)object;
//	CtImMxicFunc2Private *priv = CT_IM_MXIC_FUNC2_GET_PRIVATE(self);
}


/*
*PUBLIC
*/
void ct_im_mxic_func2_12(CtImMxicFunc2* self)
{
	gint32	result;
	guchar	transaction;

	Ddim_Print(("ct_im_mxic_func2_12(self->unit=%d)\n", self->unit));

	result = Im_MXIC_Set_Master_Transaction( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x81,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Transaction OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Transaction NG. result=0x%X\n", result));
	}

	transaction = 0;

	result = Im_MXIC_Get_Master_Transaction( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x81,
											 &transaction );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("transaction = %d\n", transaction));
		Ddim_Print(("Im_MXIC_Get_Master_Transaction OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Master_Transaction NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));

}

void ct_im_mxic_func2_13(CtImMxicFunc2* self)
{
	gint32					result;
	T_IM_MXIC_ALL_LEVELPORT	allLevelport;
	E_IM_MXIC_PORT			port;
	E_IM_MXIC_LEVEL			level;

	Ddim_Print(("ct_im_mxic_func2_13(self->unit=%d)\n", self->unit));

	result = ct_im_mxic_create_all_levelport_param( &allLevelport );
	if (result == DriverCommon_D_DDIM_OK) {
		// Execute function.
		result = Im_MXIC_Set_LevelPort_All( (E_IM_MXIC_UNIT)self->unit, &allLevelport );
		if ( result == DriverCommon_D_DDIM_OK ) {
			Ddim_Print(("Im_MXIC_Set_LevelPort_All OK.\n"));
		}
		else {
			Ddim_Print(("E:Im_MXIC_Set_LevelPort_All NG. result=0x%X\n", result));
		}
	}

	memset( &allLevelport, 0, sizeof(T_IM_MXIC_ALL_LEVELPORT) );

	result = Im_MXIC_Get_LevelPort_All( (E_IM_MXIC_UNIT)self->unit, &allLevelport );
	if ( result == DriverCommon_D_DDIM_OK ) {
		ct_im_mxic_print_all_levelport( &allLevelport );
		Ddim_Print(("Im_MXIC_Get_LevelPort_All OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_LevelPort_All NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_LevelPort_Port( (E_IM_MXIC_UNIT)self->unit,
										 (E_IM_MXIC_WR_ARBITER)0,
										 (E_IM_MXIC_SPEC_ARBITER)0,
										 (guchar)0x00,
										 (E_IM_MXIC_PORT)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_LevelPort_Port OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_LevelPort_Port NG. result=0x%X\n", result));
	}

	port = (E_IM_MXIC_PORT)0;

	result = Im_MXIC_Get_LevelPort_Port( (E_IM_MXIC_UNIT)self->unit,
										 (E_IM_MXIC_WR_ARBITER)0,
										 (E_IM_MXIC_SPEC_ARBITER)0,
										 (guchar)0x00,
										 &port );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Target port = %d\n", port));
		Ddim_Print(("Im_MXIC_Get_LevelPort_Port OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_LevelPort_Port NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_LevelPort_Level( (E_IM_MXIC_UNIT)self->unit,
										  (E_IM_MXIC_WR_ARBITER)0,
										  (E_IM_MXIC_SPEC_ARBITER)0,
										  (guchar)0x00,
										  (E_IM_MXIC_LEVEL)2 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_LevelPort_Level OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_LevelPort_Level NG. result=0x%X\n", result));
	}

	level = (E_IM_MXIC_LEVEL)0;

	result = Im_MXIC_Get_LevelPort_Level( (E_IM_MXIC_UNIT)self->unit,
										  (E_IM_MXIC_WR_ARBITER)0,
										  (E_IM_MXIC_SPEC_ARBITER)0,
										  (guchar)0x00,
										  &level );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Target level = %d\n", level));
		Ddim_Print(("Im_MXIC_Get_LevelPort_Level OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_LevelPort_Level NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func2_14(CtImMxicFunc2* self)
{
	gint32					result;
	T_IM_MXIC_OUTPUT_PORT	allPortAssign;
	E_IM_MXIC_PORT_GR		portAssign;

	Ddim_Print(("ct_im_mxic_func2_14(self->unit=%d)\n", self->unit));

	result = ct_im_mxic_create_all_port_set( 1, &allPortAssign );
	if ( result == DriverCommon_D_DDIM_OK ) {
		result = Im_MXIC_Set_Output_Port_All( &allPortAssign );
		if (result == DriverCommon_D_DDIM_OK) {
			Ddim_Print(("Im_MXIC_Set_Output_Port_All OK.\n"));
		}
		else {
			Ddim_Print(("E:Im_MXIC_Set_Output_Port_All NG. result=0x%X\n", result));
		}
	}
	else {
		Ddim_Print(("E:Command parameter error.\n"));
	}

	memset( &allPortAssign, 0, sizeof(T_IM_MXIC_OUTPUT_PORT) );

	result = Im_MXIC_Get_Output_Port_All( &allPortAssign );
	if ( result == DriverCommon_D_DDIM_OK ) {
		ct_im_mxic_print_all_port_assign(  &allPortAssign );
		Ddim_Print(("Im_MXIC_Get_Output_Port_All OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Output_Port_All NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Output_Port( (guchar)0x40,
									  E_IM_MXIC_PORT_GR_1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Output_Port OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Output_Port NG. result=0x%X\n", result));
	}

	portAssign = E_IM_MXIC_PORT_GR_0;

	result = Im_MXIC_Get_Output_Port((guchar)0x40, &portAssign );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("portAssign = %d\n", portAssign));
		Ddim_Print(("Im_MXIC_Get_Output_Port OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Output_Port NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func2_15(CtImMxicFunc2* self)
{
	gint32									result;
	T_IM_MXIC_MONITOR_PARAMETER				monParam;
	guchar									thstopEnable;
	T_IM_MXIC_ALL_HISTORY_MONITOR			allHistory;
	T_IM_MXIC_HISTORY_MONITOR				history;
	T_IM_MXIC_ALL_SLOT_STATUS_MONITOR		allSlotStatus;
	T_IM_MXIC_W_ARBITER_ASSIGN_PORT			wSlotStatus;
	T_IM_MXIC_R_ARBITER_ASSIGN_PORT			rSlotStatus;
	T_IM_MXIC_W_ARBITER_ASSIGN_GR			wGrSlotStatus;
	T_IM_MXIC_R_ARBITER_ASSIGN_GR			rGrSlotStatus;
	T_IM_MXIC_MASTER_STATUS_MONITOR			masterStatus;
	T_IM_MXIC_ALL_ACCESS_OR_TRANS_MONITOR	allAccTrans;
	guint32									monResult;
	guchar									monState;

	Ddim_Print(("ct_im_mxic_func2_15(self->unit=%d)\n", self->unit));

	result = ct_im_mxic_create_access_or_trans_monitor_param( 0, &monParam );
	if ( result == DriverCommon_D_DDIM_OK ) {
		// Execute function.
		result = Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter( &monParam );
		if (result == DriverCommon_D_DDIM_OK) {
			Ddim_Print(("Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter OK.\n"));
		}
		else {
			Ddim_Print(("E:Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter NG. result=0x%X\n", result));
		}
	}
	else {
		Ddim_Print(("E:Command parameter error.\n"));
	}

	memset( &monParam, 0, sizeof(T_IM_MXIC_MONITOR_PARAMETER) );

	result = Im_MXIC_Get_Access_Or_Trans_Monitor_Parameter( &monParam );
	if ( result == DriverCommon_D_DDIM_OK ) {
		ct_im_mxic_print_monitor_parameter(  &monParam );
		Ddim_Print(("Im_MXIC_Get_Access_Or_Trans_Monitor_Parameter OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Access_Or_Trans_Monitor_Parameter NG. result=0x%X\n", result));
	}

	Im_MXIC_Start_Monitor();
	Ddim_Print(("Im_MXIC_Start_Monitor OK.\n"));

	Im_MXIC_Stop_Monitor();
	Ddim_Print(("Im_MXIC_Stop_Monitor OK.\n"));

	result = Im_MXIC_Set_History_Monitor_Stop_Enable( (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_History_Monitor_Stop_Enable OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_History_Monitor_Stop_Enable NG. result=0x%X\n", result));
	}

	thstopEnable = 0;

	result = Im_MXIC_Get_History_Monitor_Stop_Enable( &thstopEnable );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("thstopEnable = %d\n", thstopEnable));
		Ddim_Print(("Im_MXIC_Get_History_Monitor_Stop_Enable OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_History_Monitor_Stop_Enable NG. result=0x%X\n", result));
	}

	memset( &allHistory, 0, sizeof(T_IM_MXIC_ALL_HISTORY_MONITOR) );

	result = Im_MXIC_Get_History_Monitor_All_Port( &allHistory );
	if ( result == DriverCommon_D_DDIM_OK ) {
		ct_im_mxic_print_all_history_monitor( &allHistory );
		Ddim_Print(("Im_MXIC_Get_History_Monitor_All_Port OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_History_Monitor_All_Port NG. result=0x%X\n", result));
	}

	memset( &history, 0, sizeof(T_IM_MXIC_HISTORY_MONITOR) );

	result = Im_MXIC_Get_History_Monitor( (E_IM_MXIC_WR_ARBITER)0,
										  (E_IM_MXIC_SPEC_ARBITER)0,
										  (E_IM_MXIC_PORT)0,
										  &history );
	if (result == DriverCommon_D_DDIM_OK) {
		ct_im_mxic_print_history_monitor( &history );
		Ddim_Print(("Im_MXIC_Get_History_Monitor OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_History_Monitor NG. result=0x%X\n", result));
	}

	memset( &allSlotStatus, 0, sizeof(T_IM_MXIC_ALL_SLOT_STATUS_MONITOR) );

	result = Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter( (E_IM_MXIC_UNIT)self->unit, &allSlotStatus );
	if ( result == DriverCommon_D_DDIM_OK ) {
		ct_im_mxic_print_all_slot_status_monitor(  &allSlotStatus );
		Ddim_Print(("Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter NG. result=0x%X\n", result));
	}

	memset( &wSlotStatus, 0, sizeof(T_IM_MXIC_W_ARBITER_ASSIGN_PORT) );

	result = Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter( (E_IM_MXIC_UNIT)self->unit,
			(E_IM_MXIC_W_ARBITER)0, &wSlotStatus );
	if (result == DriverCommon_D_DDIM_OK) {
		ct_im_mxic_print_w_arbiter_assign( &wSlotStatus);
		Ddim_Print(("Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter NG. result=0x%X\n", result));
	}

	memset( &rSlotStatus, 0, sizeof(T_IM_MXIC_R_ARBITER_ASSIGN_PORT) );

	result = Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter( (E_IM_MXIC_UNIT)self->unit,
			(E_IM_MXIC_R_ARBITER)0, &rSlotStatus );
	if (result == DriverCommon_D_DDIM_OK) {
		ct_im_mxic_print_r_arbiter_assign( &rSlotStatus);
		Ddim_Print(("Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter NG. result=0x%X\n", result));
	}

	memset( &wGrSlotStatus, 0, sizeof(T_IM_MXIC_W_ARBITER_ASSIGN_GR) );

	result = Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter_Group( (E_IM_MXIC_W_ARBITER_GR)0, &wGrSlotStatus );
	if ( result == DriverCommon_D_DDIM_OK ) {
		ct_im_mxic_print_w_arbiter_assign_group(  &wGrSlotStatus );
		Ddim_Print(("Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter_Group OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter_Group NG. result=0x%X\n", result));
	}

	memset( &rGrSlotStatus, 0, sizeof(T_IM_MXIC_R_ARBITER_ASSIGN_GR) );

	result = Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter_Group( (E_IM_MXIC_R_ARBITER_GR)0, &rGrSlotStatus );
	if ( result == DriverCommon_D_DDIM_OK ) {
		ct_im_mxic_print_r_arbiter_assign_group(  &rGrSlotStatus );
		Ddim_Print(("Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter_Group OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter_Group NG. result=0x%X\n", result));
	}

	memset( &masterStatus, 0, sizeof(T_IM_MXIC_MASTER_STATUS_MONITOR) );

	result = Im_MXIC_Get_Master_Status_Monitor( (E_IM_MXIC_UNIT)self->unit, &masterStatus );
	if ( result == DriverCommon_D_DDIM_OK ) {
		ct_im_mxic_print_master_status_monitor(  &masterStatus );
		Ddim_Print(("Im_MXIC_Get_Master_Status_Monitor OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Master_Status_Monitor NG. result=0x%X\n", result));
	}

	memset( &allAccTrans, 0, sizeof(T_IM_MXIC_ALL_ACCESS_OR_TRANS_MONITOR) );

	result = Im_MXIC_Get_Access_Or_Trans_Monitor_All_Entry( &allAccTrans );
	if (result == DriverCommon_D_DDIM_OK) {
		ct_im_mxic_print_all_access_or_trans_monitor(  &allAccTrans );
		Ddim_Print(("Im_MXIC_Get_Access_Or_Trans_Monitor_All_Entry OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Access_Or_Trans_Monitor_All_Entry NG. result=0x%X\n", result));
	}

	monResult = 0;

	result = Im_MXIC_Get_Access_Or_Trans_Monitor( 0, &monResult );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("monResult = %d\n", monResult));
		Ddim_Print(("Im_MXIC_Get_Access_Or_Trans_Monitor OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Access_Or_Trans_Monitor NG. result=0x%X\n", result));
	}

	monState = 0;

	result = Im_MXIC_Get_Access_Or_Trans_Monitor_Limit_End_State( &monState );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("monState = %d\n", monState));
		Ddim_Print(("Im_MXIC_Get_Access_Or_Trans_Monitor_Limit_End_State OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Access_Or_Trans_Monitor_Limit_End_State NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func2_16(CtImMxicFunc2* self)
{
	gint32							result;
	T_IM_MXIC_MEMORY_ACCESS_SLAVE	memoryAccess;

	Ddim_Print(("ct_im_mxic_func2_16(self->unit=%d)\n", self->unit));

	result = ct_im_mxic_create_memory_access_param( 9, 0, &memoryAccess );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Im_MXIC_Set_Memory_Access_Detect( (E_IM_MXIC_UNIT)self->unit, &memoryAccess );
		if ( result == DriverCommon_D_DDIM_OK ) {
			Ddim_Print(("Im_MXIC_Set_Memory_Access_Detect OK.\n"));
		}
		else {
			Ddim_Print(("E:Im_MXIC_Set_Memory_Access_Detect NG. result=0x%X\n", result));
		}
	}
	else {
		Ddim_Print(("E:Command parameter error.\n"));
	}

	memset( &memoryAccess, 0, sizeof(T_IM_MXIC_MEMORY_ACCESS_SLAVE) );

	result = ct_im_mxic_create_memory_access_start_trigger( 9, &memoryAccess );
	if ( result == DriverCommon_D_DDIM_OK ) {
		result = Im_MXIC_Start_Memory_Access_Detect( (E_IM_MXIC_UNIT)self->unit, &memoryAccess );
		if ( result == DriverCommon_D_DDIM_OK ) {
			Ddim_Print(("Im_MXIC_Start_Memory_Access_Detect OK.\n"));
		}
		else {
			Ddim_Print(("E:Im_MXIC_Start_Memory_Access_Detect NG. result=0x%X\n", result));
		}
	}
	else {
		Ddim_Print(("E:Command parameter error.\n"));
	}

	memset( &memoryAccess, 0, sizeof(T_IM_MXIC_MEMORY_ACCESS_SLAVE) );

	result = Im_MXIC_Get_Memory_Access_Detect( (E_IM_MXIC_UNIT)self->unit, &memoryAccess );
	if ( result == DriverCommon_D_DDIM_OK ) {
		ct_im_mxic_print_memory_access_param( &memoryAccess );
		Ddim_Print(("Im_MXIC_Get_Memory_Access_Detect OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Memory_Access_Detect NG. result=0x%X\n", result));
	}

	Im_MXIC_Stop_Memory_Access_Detect( (E_IM_MXIC_UNIT)self->unit );
	Ddim_Print(("Im_MXIC_Stop_Memory_Access_Detect OK.\n"));

	Ddim_Print(("\n"));
}

void ct_im_mxic_func2_17(CtImMxicFunc2* self)
{
	gint32					result;
	T_IM_MXIC_DEC_ERR_INT	decErrInt;
	T_IM_MXIC_DEC_ERR		decErr;

	Ddim_Print(("ct_im_mxic_func2_17(self->unit=%d)\n", self->unit));

	memset( &decErrInt, 0, sizeof(T_IM_MXIC_DEC_ERR_INT) );

	decErrInt.pCallBack = ct_im_mxic_create_dec_err_cb;

	result = Im_MXIC_Set_Decode_Error_Int( (E_IM_MXIC_UNIT)self->unit, &decErrInt );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Decode_Error_Int OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Decode_Error_Int NG. result=0x%X\n", result));
	}

	memset( &decErrInt, 0, sizeof(T_IM_MXIC_DEC_ERR_INT) );

	result = Im_MXIC_Get_Decode_Error_Int( (E_IM_MXIC_UNIT)self->unit, &decErrInt );
	if ( result == DriverCommon_D_DDIM_OK ) {
		ct_im_mxic_print_dec_err_int( &decErrInt );
		Ddim_Print(("Im_MXIC_Get_Decode_Error_Int OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Decode_Error_Int NG. result=0x%X\n", result));
	}

	memset( &decErr, 0, sizeof(T_IM_MXIC_DEC_ERR) );

	result = Im_MXIC_Get_Decode_Error( (E_IM_MXIC_UNIT)self->unit, &decErr );
	if ( result == DriverCommon_D_DDIM_OK ) {
		ct_im_mxic_print_dec_err( &decErr );
		Ddim_Print(("Im_MXIC_Get_Decode_Error OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Decode_Error NG. result=0x%X\n", result));
	}

	Ddim_Print(("\n"));
}

void ct_im_mxic_func2_19(CtImMxicFunc2* self)
{
	gint32					result;

	Ddim_Print(("ct_im_mxic_func2_19(self->unit=%d)\n", self->unit));

	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x01,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor 1-1 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor 1-1 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x41,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor 1-2 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor 1-2 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x1F,
											 (E_IM_MXIC_MASK_GROUP)1,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor 1-3 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor 1-3 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x62,
											 (E_IM_MXIC_MASK_GROUP)1,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor 1-4 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor 1-4 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x01,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target 2-1 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target 2-1 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x41,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target 2-2 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target 2-2 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x1F,
											 (E_IM_MXIC_MASK_GROUP)1,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target 2-3 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target 2-3 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x62,
											 (E_IM_MXIC_MASK_GROUP)1,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target 2-4 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target 2-4 NG. result=0x%X\n", result));
	}

#if 1
	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x01,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (guchar)0 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor 3 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor 3 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x41,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (guchar)0 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor 3 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor 3 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x1F,
											 (E_IM_MXIC_MASK_GROUP)1,
											 (guchar)0 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor 3 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor 3 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x62,
											 (E_IM_MXIC_MASK_GROUP)1,
											 (guchar)0 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor 3 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor 3 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x01,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target 4 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target 4 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x41,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target 4 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target 4 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x1F,
											 (E_IM_MXIC_MASK_GROUP)1,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target 4 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target 4 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x62,
											 (E_IM_MXIC_MASK_GROUP)1,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target 4 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target 4 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x01,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor 5 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor 5 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x41,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor 5 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor 5 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x1F,
											 (E_IM_MXIC_MASK_GROUP)1,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor 5 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor 5 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Factor( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x62,
											 (E_IM_MXIC_MASK_GROUP)1,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor 5 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor 5 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x01,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (guchar)0 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target 6 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target 6 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x41,
											 (E_IM_MXIC_MASK_GROUP)0,
											 (guchar)0 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target 6 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target 6 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x1F,
											 (E_IM_MXIC_MASK_GROUP)1,
											 (guchar)0 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target 6 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target 6 NG. result=0x%X\n", result));
	}

	result = Im_MXIC_Set_Master_Mask_Target( (E_IM_MXIC_UNIT)self->unit,
											 (guchar)0x62,
											 (E_IM_MXIC_MASK_GROUP)1,
											 (guchar)1 );
	if ( result == DriverCommon_D_DDIM_OK ) {
		Ddim_Print(("Im_MXIC_Set_Master_Mask_Target 6 OK.\n"));
	}
	else {
		Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target 6 NG. result=0x%X\n", result));
	}
#endif

	Ddim_Print(("\n"));
}

CtImMxicFunc2 *ct_im_mxic_func2_new(void) 
{
    CtImMxicFunc2 *self = g_object_new(CT_TYPE_IM_MXIC_FUNC2, NULL);
    return self;
}
