/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :jianghaodong
*@brief               :CtImMxicCreate类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "ct_im_mxic.h"
#include <string.h>
#include <stdlib.h>

#include "dd_top.h"

#include "ddim_user_custom.h"

#include "ctimmxicprint.h"
#include "ctimmxiccreate.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImMxicCreate, ct_im_mxic_create);
#define CT_IM_MXIC_CREATE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImMxicCreatePrivate,CT_TYPE_IM_MXIC_CREATE))

struct _CtImMxicCreatePrivate
{

};

/*
*DECLS
*/
static void 			ctImMxicAccMonitor_cb(void);

/*
*IMPL
*/
static void ct_im_mxic_create_constructor(CtImMxicCreate *self)
{
}

static void ct_im_mxic_create_destructor(CtImMxicCreate *self)
{
}

// Callback function for slave area decode error.
void ct_im_mxic_create_dec_err_cb( kuchar chType)
{
	kint32 result;
	T_IM_MXIC_DEC_ERR decErr;

	switch (chType) {
		case D_IM_MXIC_DEC_ERR_CH_W:
			Ddim_Print(("E:Decode error interrupt. chType = D_IM_MXIC_DEC_ERR_CH_W\n"));
			break;

		case D_IM_MXIC_DEC_ERR_CH_R:
			Ddim_Print(("E:Decode error interrupt. chType = D_IM_MXIC_DEC_ERR_CH_R\n"));
			break;

		case D_IM_MXIC_DEC_ERR_CH_RW:
			Ddim_Print(("E:Decode error interrupt. chType = D_IM_MXIC_DEC_ERR_CH_RW\n"));
			break;

		default:
			Ddim_Print(("E:Decode error interrupt. chType = UNKNOWN\n"));
			break;
	}

	// Get error information.
	result = Im_MXIC_Get_Decode_Error((E_IM_MXIC_UNIT)0, &decErr);
	if (result == D_DDIM_OK) {
		ct_im_mxic_print_dec_err(&decErr);
	}
	else {
		Ddim_Print(("E:Im_MXIC_Get_Decode_Error NG. result=0x%X\n", result));
	}
	return;
}

// Callback function for monitor end.
static void ctImMxicAccMonitor_cb(void)
{
	Ddim_Print(("The monitor end interrupt was generated.\n"));
}

/*
*PUBLIC
*/
// Create parameter for Im_MXIC_Set_Slot_Priority_All_Arbiter function test.
kint32 ct_im_mxic_create_slot_priority_all_arbiter_param(
		T_IM_MXIC_ALL_SLOT_PRIORITY_LEVEL* const allLevelCtrl)
{
	kint32 i, j;

	// Write Slave
	for (i = E_IM_MXIC_W_ARBITER_W1; i < E_IM_MXIC_W_ARBITER_MAX; i++) {
		for (j = E_IM_MXIC_PORT_0; j < E_IM_MXIC_PORT_MAX; j++) {
			allLevelCtrl->w_level[i].level0[j].priority_level_type  = D_IM_MXIC_SLOT_PRIORITY_UPPER_ONLY;
			allLevelCtrl->w_level[i].level0[j].upper_priority_level = 0;
			allLevelCtrl->w_level[i].level0[j].lower_priority_level = 63;
			allLevelCtrl->w_level[i].level1[j].priority_level_type  = D_IM_MXIC_SLOT_PRIORITY_UPPER;
			allLevelCtrl->w_level[i].level1[j].upper_priority_level = 32;
			allLevelCtrl->w_level[i].level1[j].lower_priority_level = 1;
			allLevelCtrl->w_level[i].level2[j].priority_level_type  = D_IM_MXIC_SLOT_PRIORITY_LOWWER;
			allLevelCtrl->w_level[i].level2[j].upper_priority_level = 63;
			allLevelCtrl->w_level[i].level2[j].lower_priority_level = 0;
		}
	}
	// Read Slave
	for (i = E_IM_MXIC_R_ARBITER_R1; i < E_IM_MXIC_R_ARBITER_MAX; i++) {
		for (j = E_IM_MXIC_PORT_0; j < E_IM_MXIC_PORT_MAX; j++) {
			allLevelCtrl->r_level[i].level0[j].priority_level_type  = D_IM_MXIC_SLOT_PRIORITY_LOWWER_ONLY;
			allLevelCtrl->r_level[i].level0[j].upper_priority_level = 63;
			allLevelCtrl->r_level[i].level0[j].lower_priority_level = 0;
			allLevelCtrl->r_level[i].level1[j].priority_level_type  = D_IM_MXIC_SLOT_PRIORITY_LOWWER;
			allLevelCtrl->r_level[i].level1[j].upper_priority_level = 0;
			allLevelCtrl->r_level[i].level1[j].lower_priority_level = 63;
			allLevelCtrl->r_level[i].level2[j].priority_level_type  = D_IM_MXIC_SLOT_PRIORITY_UPPER;
			allLevelCtrl->r_level[i].level2[j].upper_priority_level = 1;
			allLevelCtrl->r_level[i].level2[j].lower_priority_level = 32;
		}
	}

	return D_DDIM_OK;
}

kint32 ct_im_mxic_create_all_levelport_param( T_IM_MXIC_ALL_LEVELPORT* const allLevelport)
{
	kint32 i, j;

	for ( i = E_IM_MXIC_W_ARBITER_W1; i < E_IM_MXIC_W_ARBITER_MAX; i++ ) {

		for ( j = 0; j < D_IM_MXIC_MASTER_NUMBER_MAX-1; j++ ) {

			allLevelport->w_arbiter[ i ].port[ j ]		= E_IM_MXIC_PORT_1;
			allLevelport->w_arbiter[ i ].level[ j ]	= E_IM_MXIC_LEVEL_1;
		}
	}

	for ( i = E_IM_MXIC_R_ARBITER_R1; i < E_IM_MXIC_R_ARBITER_MAX; i++ ) {

		for ( j = 0; j < D_IM_MXIC_MASTER_NUMBER_MAX-1; j++ ) {

			allLevelport->r_arbiter[ i ].port[ j ]		= E_IM_MXIC_PORT_2;
			allLevelport->r_arbiter[ i ].level[ j ]	= E_IM_MXIC_LEVEL_2;
		}
	}

	return D_DDIM_OK;
}

// Create parameter for Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter function test.
kint32 ct_im_mxic_create_access_or_trans_monitor_param( kuchar paramKind,
		T_IM_MXIC_MONITOR_PARAMETER* const monParam)
{
	kint32 result;

	result = D_DDIM_OK;

	switch (paramKind) {
		case 0:
			// Monitor mode register. (TMMD)
			monParam->start_condition          = D_IM_MXIC_MONITOR_START_ON;
			monParam->end_condition            = D_IM_MXIC_MONITOR_ENDLESS;
			monParam->update_enable            = D_IM_MXIC_OFF;
			monParam->update_trigger_interval  = D_IM_MXIC_MONITOR_UPDATE_1;
			monParam->update_clear_en          = D_IM_MXIC_OFF;
			monParam->start_clear_en           = D_IM_MXIC_OFF;
			monParam->cnt_val                  = D_IM_MXIC_VALUE_WHEN_UPDATE_TRG;

			// Limit judgment conditions.
			monParam->limit_access_trans       = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->limit_detection_target   = D_IM_MXIC_W_RESERVE;
			monParam->limit                    = 0x00000001;

			// Monitor target and kind(Access or Transfer).
			monParam->target[0].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[1].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[2].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[3].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[0].monitor_target = D_IM_MXIC_4_R_DISP_A;
			monParam->target[1].monitor_target = D_IM_MXIC_TARGET_NOTHING;
			monParam->target[2].monitor_target = D_IM_MXIC_TARGET_NOTHING;
			monParam->target[3].monitor_target = D_IM_MXIC_TARGET_NOTHING;

			// Callback for TMF interrupt.
			monParam->pCallBack = ctImMxicAccMonitor_cb;
			break;

		case 1:
			// Monitor mode register. (TMMD)
			monParam->start_condition          = D_IM_MXIC_MONITOR_START_TRG;
			monParam->end_condition            = D_IM_MXIC_MONITOR_END_LIMIT;
			monParam->update_enable            = D_IM_MXIC_OFF;
			monParam->update_trigger_interval  = D_IM_MXIC_MONITOR_UPDATE_512;
			monParam->update_clear_en          = D_IM_MXIC_OFF;
			monParam->start_clear_en           = D_IM_MXIC_ON;
			monParam->cnt_val                  = D_IM_MXIC_TRANS_COUNT_VALUE;

			// Limit judgment conditions.
			monParam->limit_access_trans       = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->limit_detection_target   = D_IM_MXIC_SLAVE_R1_PORT0;
			monParam->limit                    = 0x08000000;

			// Monitor target and kind(Access or Transfer).
			monParam->target[0].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[1].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[2].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[3].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[0].monitor_target = D_IM_MXIC_SLAVE_W1_PORT0;
			monParam->target[1].monitor_target = D_IM_MXIC_SLAVE_W1_PORT1;
			monParam->target[2].monitor_target = D_IM_MXIC_SLAVE_R1_PORT0;
			monParam->target[3].monitor_target = D_IM_MXIC_SLAVE_R1_PORT1;

			// Callback for TMF interrupt.
			monParam->pCallBack = ctImMxicAccMonitor_cb;
			break;

		case 2:
			// Monitor mode register. (TMMD)
			monParam->start_condition          = D_IM_MXIC_MONITOR_START_TRG;
			monParam->end_condition            = D_IM_MXIC_MONITOR_END_ASSERT;
			monParam->update_enable            = D_IM_MXIC_OFF;
			monParam->update_trigger_interval  = D_IM_MXIC_MONITOR_UPDATE_32;
			monParam->update_clear_en          = D_IM_MXIC_OFF;
			monParam->start_clear_en           = D_IM_MXIC_ON;
			monParam->cnt_val                  = D_IM_MXIC_TRANS_COUNT_VALUE;

			// Limit judgment conditions.
			monParam->limit_access_trans       = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->limit_detection_target   = D_IM_MXIC_R_RESERVE;
			monParam->limit                    = 0x00000001;

			// Monitor target and kind(Access or Transfer).
			monParam->target[0].monitor_sel    = D_IM_MXIC_MONITOR_ACCESS;
			monParam->target[1].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[2].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[3].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[0].monitor_target = D_IM_MXIC_4_R_DISP_A;
			monParam->target[1].monitor_target = D_IM_MXIC_SLAVE_W1_PORT0;
			monParam->target[2].monitor_target = D_IM_MXIC_SLAVE_R1_PORT0;
			monParam->target[3].monitor_target = D_IM_MXIC_TARGET_NOTHING;

			// Callback for TMF interrupt.
			monParam->pCallBack = ctImMxicAccMonitor_cb;
			break;

		case 3:
			// Monitor mode register. (TMMD)
			monParam->start_condition          = D_IM_MXIC_MONITOR_START_ON;
			monParam->end_condition            = D_IM_MXIC_MONITOR_ENDLESS;
			monParam->update_enable            = D_IM_MXIC_OFF;
			monParam->update_trigger_interval  = D_IM_MXIC_MONITOR_UPDATE_1;
			monParam->update_clear_en          = D_IM_MXIC_OFF;
			monParam->start_clear_en           = D_IM_MXIC_OFF;
			monParam->cnt_val                  = D_IM_MXIC_VALUE_WHEN_UPDATE_TRG;

			// Limit judgment conditions.
			monParam->limit_access_trans       = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->limit_detection_target   = D_IM_MXIC_W_RESERVE;
			monParam->limit                    = 0x00000001;

			// Monitor target and kind(Access or Transfer).
			monParam->target[0].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[1].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[2].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[3].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[0].monitor_target = D_IM_MXIC_3_R_IIP_A;
			monParam->target[1].monitor_target = D_IM_MXIC_TARGET_NOTHING;
			monParam->target[2].monitor_target = D_IM_MXIC_TARGET_NOTHING;
			monParam->target[3].monitor_target = D_IM_MXIC_TARGET_NOTHING;

			// Callback for TMF interrupt.
			monParam->pCallBack = ctImMxicAccMonitor_cb;
			break;

		case 4:
			// Monitor mode register. (TMMD)
			monParam->start_condition          = D_IM_MXIC_MONITOR_START_TRG;
			monParam->end_condition            = D_IM_MXIC_MONITOR_END_LIMIT;
			monParam->update_enable            = D_IM_MXIC_OFF;
			monParam->update_trigger_interval  = D_IM_MXIC_MONITOR_UPDATE_512;
			monParam->update_clear_en          = D_IM_MXIC_OFF;
			monParam->start_clear_en           = D_IM_MXIC_ON;
			monParam->cnt_val                  = D_IM_MXIC_TRANS_COUNT_VALUE;

			// Limit judgment conditions.
			monParam->limit_access_trans       = D_IM_MXIC_MONITOR_ACCESS;
			monParam->limit_detection_target   = D_IM_MXIC_SLAVE_R1_PORT0;
			monParam->limit                    = 0x00100000;

			// Monitor target and kind(Access or Transfer).
			monParam->target[0].monitor_sel    = D_IM_MXIC_MONITOR_ACCESS;
			monParam->target[1].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[2].monitor_sel    = D_IM_MXIC_MONITOR_ACCESS;
			monParam->target[3].monitor_sel    = D_IM_MXIC_MONITOR_TRANSFER;
			monParam->target[0].monitor_target = D_IM_MXIC_SLAVE_W1_PORT0;
			monParam->target[1].monitor_target = D_IM_MXIC_SLAVE_W1_PORT1;
			monParam->target[2].monitor_target = D_IM_MXIC_SLAVE_R1_PORT0;
			monParam->target[3].monitor_target = D_IM_MXIC_SLAVE_R1_PORT1;
			break;

		default:
			// Unknown parameter kind.
			result = D_IM_MXIC_INPUT_PARAM_ERROR;
			break;
	}
	return result;
}

// Create parameter for Im_MXIC_Set_Master_W_Arbiter function test.
kint32 ct_im_mxic_create_master_w_arbiter_param( E_IM_MXIC_UNIT unit,
		T_IM_MXIC_W_ARBITER_ASSIGN_PORT* const wArbiterAssign )
{
	kuint32 i, j;

	for ( i = E_IM_MXIC_PORT_0; i < E_IM_MXIC_PORT_MAX ; i++ ) {
		for ( j = 0; j < D_IM_MXIC_SLOT_SIZE_8 ; j++ ) {
			wArbiterAssign->port[ i ].slot0[ j ] = D_IM_MXIC_W_RESERVE;
			wArbiterAssign->port[ i ].slot1[ j ] = D_IM_MXIC_W_RESERVE;
			wArbiterAssign->port[ i ].slot2[ j ] = D_IM_MXIC_W_RESERVE;
			wArbiterAssign->port[ i ].slot3[ j ] = D_IM_MXIC_W_RESERVE;
		}
	}

	switch ( unit ) {
		case E_IM_MXIC_UNIT_0:
			break;
		case E_IM_MXIC_UNIT_1:
			break;
		case E_IM_MXIC_UNIT_2:
			break;
		case E_IM_MXIC_UNIT_3:
			break;
		case E_IM_MXIC_UNIT_4:
			break;
		case E_IM_MXIC_UNIT_5:
			break;
		case E_IM_MXIC_UNIT_6:
			break;
		default:
			break;
	}

	return D_DDIM_OK;
}

// Create parameter for Im_MXIC_Set_Master_R_Arbiter function test.
kint32 ct_im_mxic_create_master_r_arbiter_param(E_IM_MXIC_UNIT unit,
		T_IM_MXIC_R_ARBITER_ASSIGN_PORT* const rArbiterAssign )
{
	kuint32 i, j;

	for ( i = E_IM_MXIC_PORT_0; i < E_IM_MXIC_PORT_MAX; i++ ) {
		for ( j = 0; j < D_IM_MXIC_SLOT_SIZE_8 ; j++ ) {
			rArbiterAssign->port[ i ].slot0[ j ] = D_IM_MXIC_R_RESERVE;
			rArbiterAssign->port[ i ].slot1[ j ] = D_IM_MXIC_R_RESERVE;
			rArbiterAssign->port[ i ].slot2[ j ] = D_IM_MXIC_R_RESERVE;
			rArbiterAssign->port[ i ].slot3[ j ] = D_IM_MXIC_R_RESERVE;
		}
	}

	switch ( unit ) {
		case E_IM_MXIC_UNIT_0:
			break;
		case E_IM_MXIC_UNIT_1:
			break;
		case E_IM_MXIC_UNIT_2:
			break;
		case E_IM_MXIC_UNIT_3:
			break;
		case E_IM_MXIC_UNIT_4:
			break;
		case E_IM_MXIC_UNIT_5:
			break;
		case E_IM_MXIC_UNIT_6:
			break;
		default:
			break;
	}

	return D_DDIM_OK;
}

// Create parameter for Im_MXIC_Set_Master_All_Arbiter function test.
kint32 ct_im_mxic_create_master_all_arbiter_param( E_IM_MXIC_UNIT unit,
		T_IM_MXIC_ALL_ARBITER_ASSIGN* const allArbiterAssign )
{
	kuint32 i;

	for ( i = E_IM_MXIC_W_ARBITER_W1; i < E_IM_MXIC_W_ARBITER_MAX; i++ ) {
		ct_im_mxic_create_master_w_arbiter_param( unit, &allArbiterAssign->w_arbiter[ i ] );
	}

	for (i=E_IM_MXIC_R_ARBITER_R1; i<E_IM_MXIC_R_ARBITER_MAX; i++) {
		ct_im_mxic_create_master_r_arbiter_param( unit, &allArbiterAssign->r_arbiter[ i ] );
	}

	return D_DDIM_OK;
}

// Create start_trigger for Im_MXIC_Start_Memory_Access_Detect function test.
kint32 ct_im_mxic_create_memory_access_start_trigger( kuint32 startParam,
		T_IM_MXIC_MEMORY_ACCESS_SLAVE* const memacc_start)
{
	kint32 result;

	result = D_DDIM_OK;

	memacc_start->slave[0].start_trigger = D_IM_MXIC_OFF;
	memacc_start->slave[1].start_trigger = D_IM_MXIC_OFF;
	memacc_start->slave[2].start_trigger = D_IM_MXIC_OFF;
	memacc_start->slave[3].start_trigger = D_IM_MXIC_OFF;
	switch (startParam) {
		case 0:
			memacc_start->slave[0].start_trigger = D_IM_MXIC_ON;
			break;
		case 1:
			memacc_start->slave[1].start_trigger = D_IM_MXIC_ON;
			break;
		case 2:
			memacc_start->slave[2].start_trigger = D_IM_MXIC_ON;
			break;
		case 3:
			memacc_start->slave[3].start_trigger = D_IM_MXIC_ON;
			break;
		case 9:
			memacc_start->slave[0].start_trigger = D_IM_MXIC_ON;
			memacc_start->slave[1].start_trigger = D_IM_MXIC_ON;
			memacc_start->slave[2].start_trigger = D_IM_MXIC_ON;
			memacc_start->slave[3].start_trigger = D_IM_MXIC_ON;
			break;
		default:
			// Unknown parameter kind.
			result = D_IM_MXIC_INPUT_PARAM_ERROR;
			break;
	}

	return result;
}

// Create param for Im_MXIC_Set_Memory_Access_Detect function test.
kint32 ct_im_mxic_create_memory_access_param( kuint32 startParam,
		kuint32 paramPattern, T_IM_MXIC_MEMORY_ACCESS_SLAVE* const memaccParam)
{
	kint32 result;

	result = D_DDIM_OK;

	result = ct_im_mxic_create_memory_access_start_trigger( startParam, memaccParam);
	if (result == D_DDIM_OK) {
		switch (paramPattern) {
			case 0:
				memaccParam->slave[0].master47_1		= 0x00001000001E7BFE;
				memaccParam->slave[0].master127_64		= 0x10000000000F032F;
				memaccParam->slave[0].start_address	= 0x40000000;
				memaccParam->slave[0].end_address		= 0x80000000;
				memaccParam->slave[0].mode				= D_IM_MXIC_ON;
				memaccParam->slave[1].master47_1		= 0x00002000001E7BFE;
				memaccParam->slave[1].master127_64		= 0x20000000000F032F;
				memaccParam->slave[1].start_address	= 0x40000000;
				memaccParam->slave[1].end_address		= 0x80000000;
				memaccParam->slave[1].mode				= D_IM_MXIC_ON;
				memaccParam->slave[2].master47_1		= 0x00003000001E7BFE;
				memaccParam->slave[2].master127_64		= 0x30000000000F032F;
				memaccParam->slave[2].start_address	= 0x40000000;
				memaccParam->slave[2].end_address		= 0x80000000;
				memaccParam->slave[2].mode				= D_IM_MXIC_ON;
				memaccParam->slave[3].master47_1		= 0x00008000001E7BFE;
				memaccParam->slave[3].master127_64		= 0x80000000000F032F;
				memaccParam->slave[3].start_address	= 0x40000000;
				memaccParam->slave[3].end_address		= 0x80000000;
				memaccParam->slave[3].mode				= D_IM_MXIC_ON;
				break;
			case 1:
				memaccParam->slave[0].master47_1 = 0x00000000001E7BFE;
				memaccParam->slave[0].master127_64 = 0x00000000000F032F;
				memaccParam->slave[0].start_address = 0x40000000;
				memaccParam->slave[0].end_address = 0x80000000;
				memaccParam->slave[0].mode = D_IM_MXIC_OFF;
				memaccParam->slave[1].master47_1 = 0x00000000001E7BFE;
				memaccParam->slave[1].master127_64 = 0x00000000000F032F;
				memaccParam->slave[1].start_address = 0x40000000;
				memaccParam->slave[1].end_address = 0x80000000;
				memaccParam->slave[1].mode = D_IM_MXIC_OFF;
				memaccParam->slave[2].master47_1 = 0x00000000001E7BFE;
				memaccParam->slave[2].master127_64 = 0x00000000000F032F;
				memaccParam->slave[2].start_address = 0x40000000;
				memaccParam->slave[2].end_address = 0x80000000;
				memaccParam->slave[2].mode = D_IM_MXIC_OFF;
				memaccParam->slave[3].master47_1 = 0x00000000001E7BFE;
				memaccParam->slave[3].master127_64 = 0x00000000000F032F;
				memaccParam->slave[3].start_address = 0x40000000;
				memaccParam->slave[3].end_address = 0x80000000;
				memaccParam->slave[3].mode = D_IM_MXIC_OFF;
				break;
			default:
				// Unknown parameter kind.
				result = D_IM_MXIC_INPUT_PARAM_ERROR;
				break;
		}
	}
	return result;
}

// Error test of Im_MXIC_Get_Access_Or_Trans_Monitor_All_Entry function.
kint32 ct_im_mxic_create_all_port_set( kuint32 set_ptn,
		T_IM_MXIC_OUTPUT_PORT* const allPortAssign)
{
	kint32 result;

	result = D_DDIM_OK;

	if(set_ptn == 0){
		memset((T_IM_MXIC_OUTPUT_PORT*)allPortAssign, 0, sizeof(T_IM_MXIC_OUTPUT_PORT));
	}
	else if(set_ptn == 1){
		memset((T_IM_MXIC_OUTPUT_PORT*)allPortAssign, 1, sizeof(T_IM_MXIC_OUTPUT_PORT));
	}
	else if(set_ptn == 2){
		// TPORTMW_127_64
		allPortAssign->w_out_port.ela			= E_IM_MXIC_PORT_GR_0;
		allPortAssign->w_out_port.xch			= E_IM_MXIC_PORT_GR_1;
		allPortAssign->w_out_port.fpt_0		= E_IM_MXIC_PORT_GR_0;
		allPortAssign->w_out_port.fpt_1		= E_IM_MXIC_PORT_GR_1;

		// TPORTMR_127_64
		allPortAssign->r_out_port.ela			= E_IM_MXIC_PORT_GR_0;
		allPortAssign->r_out_port.xch			= E_IM_MXIC_PORT_GR_1;
		allPortAssign->r_out_port.fpt_0		= E_IM_MXIC_PORT_GR_0;
		allPortAssign->r_out_port.fpt_1		= E_IM_MXIC_PORT_GR_1;
	}
	else if(set_ptn == 3){
		// TPORTMW_127_64
		allPortAssign->w_out_port.ela			= E_IM_MXIC_PORT_GR_0;
		allPortAssign->w_out_port.xch			= E_IM_MXIC_PORT_GR_1;
		allPortAssign->w_out_port.fpt_0		= E_IM_MXIC_PORT_GR_0;
		allPortAssign->w_out_port.fpt_1		= E_IM_MXIC_PORT_GR_1;

		// TPORTMR_127_64
		allPortAssign->r_out_port.ela			= E_IM_MXIC_PORT_GR_0;
		allPortAssign->r_out_port.xch			= E_IM_MXIC_PORT_GR_1;
		allPortAssign->r_out_port.fpt_0		= E_IM_MXIC_PORT_GR_0;
		allPortAssign->r_out_port.fpt_1		= E_IM_MXIC_PORT_GR_1;
	}
	else {
		result = D_IM_MXIC_INPUT_PARAM_ERROR;
	}
	return result;
}

CtImMxicCreate* ct_im_mxic_create_new(void) 
{
    CtImMxicCreate *self = k_object_new_with_private(CT_TYPE_IM_MXIC_CREATE, sizeof(CtImMxicCreatePrivate));
    return self;
}
