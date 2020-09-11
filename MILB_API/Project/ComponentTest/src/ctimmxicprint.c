/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :jianghaodong
*@brief               :CtImMxicPrint类
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

#include "ctimmxiccreate.h"
#include "ctimmxicprint.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImMxicPrint, ct_im_mxic_print);
#define CT_IM_MXIC_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImMxicPrintPrivate,CT_TYPE_IM_MXIC_PRINT))

struct _CtImMxicPrintPrivate
{
};

/*
*IMPL
*/
static void ct_im_mxic_print_constructor(CtImMxicPrint *self) 
{
}

static void ct_im_mxic_print_destructor(CtImMxicPrint *self) 
{
}

/*
*PUBLIC
*/
// atoi (Hex)
int ct_im_mxic_print_atoi_hex( kchar* ch)
{
	int ret = 0;
	int temp[20];
	int i = 0, n = 0, j;

	memset(temp, 0, sizeof(temp));
	if (ch[0] == '0' && (ch[1] == 'x' || ch[1] == 'X')) {
		ch += 2;
		// HEX
		while(*ch != 0) {
			switch(*ch) {
				case '0':	// FALL THROUGH
				case '1':	// FALL THROUGH
				case '2':	// FALL THROUGH
				case '3':	// FALL THROUGH
				case '4':	// FALL THROUGH
				case '5':	// FALL THROUGH
				case '6':	// FALL THROUGH
				case '7':	// FALL THROUGH
				case '8':	// FALL THROUGH
				case '9':
					temp[n] = *ch - 0x30;
					break;

				case 'a':	// FALL THROUGH
				case 'A':
					temp[n] = 10;
					break;

				case 'b':	// FALL THROUGH
				case 'B':
					temp[n] = 11;
					break;

				case 'c':	// FALL THROUGH
				case 'C':
					temp[n] = 12;
					break;

				case 'd':	// FALL THROUGH
				case 'D':
					temp[n] = 13;
					break;

				case 'e':	// FALL THROUGH
				case 'E':
					temp[n] = 14;
					break;

				case 'f':	// FALL THROUGH
				case 'F':
					temp[n] = 15;
					break;
			}
			n++;
			ch++;
		}
		for(i = 0; i < n; i++) {
			for(j = 0; j < n - i - 1; j++) {
				temp[i] *= 16;
			}
			ret += temp[i];
		}
	}
	else{
		ret = atoi((const char*)ch);
	}
	return ret;
}

// Print T_IM_MXIC_W_ARBITER_ASSIGN data.
void ct_im_mxic_print_w_arbiter_assign( T_IM_MXIC_W_ARBITER_ASSIGN_PORT const* const wAssign)
{
	kint32 i, j;

	Ddim_Print(("---- T_IM_MXIC_W_ARBITER_ASSIGN ----\n"));
	for (i = E_IM_MXIC_PORT_0; i < E_IM_MXIC_PORT_MAX; i++) {
		for (j = 0; j < D_IM_MXIC_SLOT_SIZE_8; j++) {
			Ddim_Print(("wAssign->port[%d].slot0[%d] = 0x%02X\n", i, j, wAssign->port[i].slot0[j]));
		}
		for (j = 0; j < D_IM_MXIC_SLOT_SIZE_8; j++) {
			Ddim_Print(("wAssign->port[%d].slot1[%d] = 0x%02X\n", i, j, wAssign->port[i].slot1[j]));
		}
		for (j = 0; j < D_IM_MXIC_SLOT_SIZE_8; j++) {
			Ddim_Print(("wAssign->port[%d].slot2[%d] = 0x%02X\n", i, j, wAssign->port[i].slot2[j]));
		}
		for (j = 0; j < D_IM_MXIC_SLOT_SIZE_8; j++) {
			Ddim_Print(("wAssign->port[%d].slot3[%d] = 0x%02X\n", i, j, wAssign->port[i].slot3[j]));
		}
	}
	return;
}

// Print T_IM_MXIC_W_ARBITER_ASSIGN data.
void ct_im_mxic_print_w_arbiter_assign_group( T_IM_MXIC_W_ARBITER_ASSIGN_GR const* const wAssign)
{
	kint32 i;

	Ddim_Print(("---- T_IM_MXIC_W_ARBITER_ASSIGN ----\n"));
	for (i = 0; i < D_IM_MXIC_SLOT_SIZE_8; i++) {
		Ddim_Print(("wAssign->slot[%d] = 0x%02X\n", i, wAssign->slot[i]));
	}
	return;
}

// Print T_IM_MXIC_R_ARBITER_ASSIGN data.
void ct_im_mxic_print_r_arbiter_assign( T_IM_MXIC_R_ARBITER_ASSIGN_PORT const* const rAssign)
{
	kint32 i, j;

	Ddim_Print(("---- T_IM_MXIC_R_ARBITER_ASSIGN ----\n"));
	for (i = E_IM_MXIC_PORT_0; i < E_IM_MXIC_PORT_MAX; i++) {
		for (j = 0; j < D_IM_MXIC_SLOT_SIZE_8; j++) {
			Ddim_Print(("rAssign->port[%d].slot0[%d] = 0x%02X\n", i, j, rAssign->port[i].slot0[j]));
		}
		for (j = 0; j < D_IM_MXIC_SLOT_SIZE_8; j++) {
			Ddim_Print(("rAssign->port[%d].slot1[%d] = 0x%02X\n", i, j, rAssign->port[i].slot1[j]));
		}
		for (j = 0; j < D_IM_MXIC_SLOT_SIZE_8; j++) {
			Ddim_Print(("rAssign->port[%d].slot2[%d] = 0x%02X\n", i, j, rAssign->port[i].slot2[j]));
		}
		for (j = 0; j < D_IM_MXIC_SLOT_SIZE_8; j++) {
			Ddim_Print(("rAssign->port[%d].slot3[%d] = 0x%02X\n", i, j, rAssign->port[i].slot3[j]));
		}
	}
	return;
}

// Print T_IM_MXIC_W_ARBITER_ASSIGN data.
void ct_im_mxic_print_r_arbiter_assign_group( T_IM_MXIC_R_ARBITER_ASSIGN_GR const* const wAssign)
{
	kint32 i;

	Ddim_Print(("---- T_IM_MXIC_W_ARBITER_ASSIGN ----\n"));
	for (i = 0; i < D_IM_MXIC_SLOT_SIZE_8; i++) {
		Ddim_Print(("wAssign->slot[%d] = 0x%02X\n", i, wAssign->slot[i]));
	}
	return;
}

// Print T_IM_MXIC_ALL_ARBITER_ASSIGN data.
void ct_im_mxic_print_all_arbiter_assign( T_IM_MXIC_ALL_ARBITER_ASSIGN const* const allAssign)
{
	kint32 i;

	Ddim_Print(("---- T_IM_MXIC_ALL_ARBITER_ASSIGN ----\n"));
	for (i = E_IM_MXIC_W_ARBITER_W1; i < E_IM_MXIC_W_ARBITER_MAX; i++) {
		Ddim_Print(("[W%d arbiter] Master assign\n", (i + 1)));
		ct_im_mxic_print_w_arbiter_assign( &allAssign->w_arbiter[i]);
	}
	for (i = E_IM_MXIC_R_ARBITER_R1; i < E_IM_MXIC_R_ARBITER_MAX; i++) {
		Ddim_Print(("[R%d arbiter] Master assign\n", (i + 1)));
		ct_im_mxic_print_r_arbiter_assign( &allAssign->r_arbiter[i]);
	}
	return;
}

// Print T_IM_MXIC_ALL_SLOT_PRIORITY_LEVEL data.
void ct_im_mxic_print_all_slot_priority_level( T_IM_MXIC_ALL_SLOT_PRIORITY_LEVEL const* const allArbiterAssign)
{
	kint32 i, j;

	Ddim_Print(("---- T_IM_MXIC_ALL_SLOT_PRIORITY_LEVEL ----\n"));
	// Write Slave
	for (i = E_IM_MXIC_W_ARBITER_W1; i < E_IM_MXIC_W_ARBITER_MAX; i++) {
		Ddim_Print((("---- W%d arbiter ----\n"), i+1));
		for (j = E_IM_MXIC_PORT_0; j < E_IM_MXIC_PORT_MAX; j++) {
			Ddim_Print((("---- port%d ----\n"), j));
			Ddim_Print(("level0 priority_level_type  = %d\n",
					allArbiterAssign->w_level[i].level0[j].priority_level_type));
			Ddim_Print(("level0 upper_priority_level = %d\n",
					allArbiterAssign->w_level[i].level0[j].upper_priority_level));
			Ddim_Print(("level0 lower_priority_level = %d\n",
					allArbiterAssign->w_level[i].level0[j].lower_priority_level));
			Ddim_Print(("level1 priority_level_type  = %d\n",
					allArbiterAssign->w_level[i].level1[j].priority_level_type));
			Ddim_Print(("level1 upper_priority_level = %d\n",
					allArbiterAssign->w_level[i].level1[j].upper_priority_level));
			Ddim_Print(("level1 lower_priority_level = %d\n",
					allArbiterAssign->w_level[i].level1[j].lower_priority_level));
			Ddim_Print(("level2 priority_level_type  = %d\n",
					allArbiterAssign->w_level[i].level2[j].priority_level_type));
			Ddim_Print(("level2 upper_priority_level = %d\n",
					allArbiterAssign->w_level[i].level2[j].upper_priority_level));
			Ddim_Print(("level2 lower_priority_level = %d\n",
					allArbiterAssign->w_level[i].level2[j].lower_priority_level));
		}
	}
	// Read Slave
	for (i = E_IM_MXIC_R_ARBITER_R1; i < E_IM_MXIC_R_ARBITER_MAX; i++) {
		Ddim_Print((("---- R%d arbiter ----\n"), i+1));
		for (j = E_IM_MXIC_PORT_0; j < E_IM_MXIC_PORT_MAX; j++) {
			Ddim_Print((("---- port%d ----\n"), j));
			Ddim_Print(("level0 priority_level_type  = %d\n",
					allArbiterAssign->r_level[i].level0[j].priority_level_type));
			Ddim_Print(("level0 upper_priority_level = %d\n",
					allArbiterAssign->r_level[i].level0[j].upper_priority_level));
			Ddim_Print(("level0 lower_priority_level = %d\n",
					allArbiterAssign->r_level[i].level0[j].lower_priority_level));
			Ddim_Print(("level1 priority_level_type  = %d\n",
					allArbiterAssign->r_level[i].level1[j].priority_level_type));
			Ddim_Print(("level1 upper_priority_level = %d\n",
					allArbiterAssign->r_level[i].level1[j].upper_priority_level));
			Ddim_Print(("level1 lower_priority_level = %d\n",
					allArbiterAssign->r_level[i].level1[j].lower_priority_level));
			Ddim_Print(("level2 priority_level_type  = %d\n",
					allArbiterAssign->r_level[i].level2[j].priority_level_type));
			Ddim_Print(("level2 upper_priority_level = %d\n",
					allArbiterAssign->r_level[i].level2[j].upper_priority_level));
			Ddim_Print(("level2 lower_priority_level = %d\n",
					allArbiterAssign->r_level[i].level2[j].lower_priority_level));
		}
	}

	return;
}

// Print T_IM_MXIC_ALL_SLOT_STATUS_MONITOR data.
void ct_im_mxic_print_all_slot_status_monitor( T_IM_MXIC_ALL_SLOT_STATUS_MONITOR const* const allSlotStatus)
{
	kint32 i;

	Ddim_Print(("---- T_IM_MXIC_ALL_SLOT_STATUS_MONITOR ----\n"));
	for (i = E_IM_MXIC_W_ARBITER_W1; i < E_IM_MXIC_W_ARBITER_MAX; i++) {
		Ddim_Print(("[W%d arbiter] Slot status\n", (i + 1)));
		ct_im_mxic_print_w_arbiter_assign( &allSlotStatus->w_arbiter[i]);
	}
	for (i = E_IM_MXIC_R_ARBITER_R1; i < E_IM_MXIC_R_ARBITER_MAX; i++) {
		Ddim_Print(("[R%d arbiter] Slot status\n", (i + 1)));
		ct_im_mxic_print_r_arbiter_assign( &allSlotStatus->r_arbiter[i]);
	}
	for (i = E_IM_MXIC_W_ARBITER_GR_W0; i < E_IM_MXIC_W_ARBITER_GR_MAX; i++) {
		Ddim_Print(("[Group W%d arbiter] Slot status\n", (i + 1)));
		ct_im_mxic_print_w_arbiter_assign_group( &allSlotStatus->w_arbiter_gr[i]);
	}
	for (i = E_IM_MXIC_R_ARBITER_GR_R0; i < E_IM_MXIC_R_ARBITER_GR_MAX; i++) {
		Ddim_Print(("[Group R%d arbiter] Slot status\n", (i + 1)));
		ct_im_mxic_print_r_arbiter_assign_group( &allSlotStatus->r_arbiter_gr[i]);
	}
	return;
}

// Print T_IM_MXIC_MASTER_STATUS_MONITOR data.
void ct_im_mxic_print_master_status_monitor( T_IM_MXIC_MASTER_STATUS_MONITOR const* const masterStatus)
{
	kint32 i;

	Ddim_Print(("---- T_IM_MXIC_MASTER_STATUS_MONITOR ----\n"));
	for (i = 1; i < D_IM_MXIC_MAX_W_MASTER_NUM; i++) {
		Ddim_Print(("[W%d]\n", i));
		Ddim_Print(("w_master[%d] = %d\n", i, masterStatus->w_master[i]));
	}
	for (i = 1; i < D_IM_MXIC_MAX_R_MASTER_NUM; i++) {
		Ddim_Print(("[R%d]\n", i));
		Ddim_Print(("r_master[%d] = %d\n", i, masterStatus->r_master[i]));
	}
	return;
}

// Print T_IM_MXIC_MONITOR_PARAMETER data.
void ct_im_mxic_print_monitor_parameter( T_IM_MXIC_MONITOR_PARAMETER const* const monParam)
{
	Ddim_Print(("---- T_IM_MXIC_MONITOR_PARAMETER ----\n"));
	Ddim_Print(("start_condition          = %d\n", monParam->start_condition));
	Ddim_Print(("end_condition            = %d\n", monParam->end_condition));
	Ddim_Print(("update_enable            = %d\n", monParam->update_enable));
	Ddim_Print(("update_trigger_interval  = %d\n", monParam->update_trigger_interval));
	Ddim_Print(("update_clear_en          = %d\n", monParam->update_clear_en));
	Ddim_Print(("start_clear_en           = %d\n", monParam->start_clear_en));
	Ddim_Print(("cnt_val                  = %d\n", monParam->cnt_val));
	Ddim_Print(("limit_access_trans       = %d\n", monParam->limit_access_trans));
	Ddim_Print(("limit_detection_target   = %d\n", monParam->limit_detection_target));
	Ddim_Print(("limit                    = %d\n", monParam->limit));
	Ddim_Print(("target[0].monitor_sel    = %d\n", monParam->target[0].monitor_sel));
	Ddim_Print(("target[1].monitor_sel    = %d\n", monParam->target[1].monitor_sel));
	Ddim_Print(("target[2].monitor_sel    = %d\n", monParam->target[2].monitor_sel));
	Ddim_Print(("target[3].monitor_sel    = %d\n", monParam->target[3].monitor_sel));
	Ddim_Print(("target[0].monitor_target = %02X\n", monParam->target[0].monitor_target));
	Ddim_Print(("target[1].monitor_target = %02X\n", monParam->target[1].monitor_target));
	Ddim_Print(("target[2].monitor_target = %02X\n", monParam->target[2].monitor_target));
	Ddim_Print(("target[3].monitor_target = %02X\n", monParam->target[3].monitor_target));
	Ddim_Print(("pCallBack                = %08X\n", (unsigned int)monParam->pCallBack));
	return;
}

// Print T_IM_MXIC_ALL_ACCESS_OR_TRANS_MONITOR data.
void ct_im_mxic_print_all_access_or_trans_monitor( T_IM_MXIC_ALL_ACCESS_OR_TRANS_MONITOR const* const allAccTrans)
{
	kint32 i;

	Ddim_Print(("---- T_IM_MXIC_ALL_ACCESS_OR_TRANS_MONITOR ----\n"));
	for (i = 0; i < D_IM_MXIC_MAX_MONITOR_TARGET_NUM; i++) {
		Ddim_Print(("allAccTrans->count[%d] = %d\n", i, allAccTrans->count[i]));
	}
	return;
}

// Print T_IM_MXIC_OUTPUT_PORT data.
void ct_im_mxic_print_all_port_assign( T_IM_MXIC_OUTPUT_PORT const* const allPortAssign)
{
	Ddim_Print(("---- T_IM_MXIC_OUTPUT_PORT ----\n"));
	Ddim_Print(("(Write master output port)\n"));
	Ddim_Print(("JDSELA Master I/F          = %d\n", allPortAssign->w_out_port.ela));
	Ddim_Print(("JDSXH Master I/F           = %d\n", allPortAssign->w_out_port.xch));
	Ddim_Print(("FPT Master I/F-0           = %d\n", allPortAssign->w_out_port.fpt_0));
	Ddim_Print(("FPT Master I/F-1           = %d\n", allPortAssign->w_out_port.fpt_1));

	Ddim_Print(("\n(Read master output port)\n"));
	Ddim_Print(("JDSELA Master I/F          = %d\n", allPortAssign->r_out_port.ela));
	Ddim_Print(("JDSXH Master I/F           = %d\n", allPortAssign->r_out_port.xch));
	Ddim_Print(("FPT Master I/F-0           = %d\n", allPortAssign->r_out_port.fpt_0));
	Ddim_Print(("FPT Master I/F-1           = %d\n", allPortAssign->r_out_port.fpt_1));

	return;
}

// Print T_IM_MXIC_ALL_ACCEPTANCE_CAPABILITY data.
void ct_im_mxic_print_all_acceptance_capability(T_IM_MXIC_ALL_ACCEPTANCE_CAPABILITY const* const allCapability)
{
	kint32 i, j;

	Ddim_Print(("---- T_IM_MXIC_ALL_ACCEPTANCE_CAPABILITY ----\n"));
	for (i = E_IM_MXIC_W_ARBITER_W1; i < E_IM_MXIC_W_ARBITER_MAX; i++) {
		for (j = E_IM_MXIC_PORT_0; j < E_IM_MXIC_PORT_MAX; j++) {
			Ddim_Print(("allCapability->w_capability[%d][%d] = %d\n", i, j, allCapability->w_capability[i][j]));
		}
	}
	for (i = E_IM_MXIC_R_ARBITER_R1; i < E_IM_MXIC_R_ARBITER_MAX; i++) {
		for (j = E_IM_MXIC_PORT_0; j < E_IM_MXIC_PORT_MAX; j++) {
			Ddim_Print(("allCapability->r_capability[%d][%d] = %d\n", i, j, allCapability->r_capability[i][j]));
		}
	}
	for (i = E_IM_MXIC_W_ARBITER_GR_W0; i < E_IM_MXIC_W_ARBITER_GR_MAX; i++) {
		for (j = E_IM_MXIC_PORT_GR_0; j < E_IM_MXIC_PORT_GR_MAX; j++) {
			Ddim_Print(("allCapability->w_capability_gr[%d][%d] = %d\n", i, j,
					allCapability->w_capability_gr[i][j]));
		}
	}
	for (i = E_IM_MXIC_R_ARBITER_GR_R0; i < E_IM_MXIC_R_ARBITER_GR_MAX; i++) {
		for (j = E_IM_MXIC_PORT_GR_0; j < E_IM_MXIC_PORT_GR_MAX; j++) {
			Ddim_Print(("allCapability->r_capability_gr[%d][%d] = %d\n", i, j,
					allCapability->r_capability_gr[i][j]));
		}
	}
	return;
}

// Print T_IM_MXIC_SLAVE_AREA data.
void ct_im_mxic_print_slave_area(T_IM_MXIC_SLAVE_AREA const* const slaveArea)
{
	Ddim_Print(("---- T_IM_MXIC_SLAVE_AREA ----\n"));
	Ddim_Print(("slaveArea->size    = %d\n", slaveArea->size));
	Ddim_Print(("slaveArea->address = 0x%08X\n", slaveArea->address));
	return;
}

// Print T_IM_MXIC_ALL_SLAVE_AREA data
void ct_im_mxic_print_all_slave_area(T_IM_MXIC_ALL_SLAVE_AREA const* const allSlaveArea)
{
	kint32 i;

	Ddim_Print(("---- T_IM_MXIC_ALL_SLAVE_AREA ----\n"));

	for (i = E_IM_MXIC_SLAVE_NUMBER_1; i < E_IM_MXIC_SLAVE_NUMBER_MAX; i++) {
		Ddim_Print(("[Slave area-%d]\n", (i + 1)));
		ct_im_mxic_print_slave_area(&allSlaveArea->slave_area[i]);
	}
	return;
}

// Print T_IM_MXIC_DEC_ERR_INT data
void ct_im_mxic_print_dec_err_int(T_IM_MXIC_DEC_ERR_INT const* const decErrInt)
{
	Ddim_Print(("---- T_IM_MXIC_DEC_ERR_INT ----\n"));
	Ddim_Print(("decErrInt->w_err_int_en = %d\n", decErrInt->w_err_int_en));
	Ddim_Print(("decErrInt->r_err_int_en = %d\n", decErrInt->r_err_int_en));
	Ddim_Print(("decErrInt->pCallBack    = %08X\n", (unsigned int)decErrInt->pCallBack));
	return;
}

// Print T_IM_MXIC_DEC_ERR data
void ct_im_mxic_print_dec_err(T_IM_MXIC_DEC_ERR const* const decErr)
{
	Ddim_Print(("---- T_IM_MXIC_DEC_ERR ----\n"));
	Ddim_Print(("decErr->w_req_master = %02X\n", decErr->w_req_master));
	Ddim_Print(("decErr->w_req_addr   = %08X\n", decErr->w_req_addr));
	Ddim_Print(("decErr->r_req_master = %02X\n", decErr->r_req_master));
	Ddim_Print(("decErr->r_req_addr   = %08X\n", decErr->r_req_addr));
	return;
}

// Print T_IM_MXIC_HISTORY_MONITOR data
void ct_im_mxic_print_history_monitor(T_IM_MXIC_HISTORY_MONITOR const* const history)
{
	kint32 i;

	Ddim_Print(("---- T_IM_MXIC_HISTORY_MONITOR ----\n"));
	for (i = 0; i < D_IM_MXIC_MAX_MONITOR_HISTORY_NUM; i++) {
		Ddim_Print(("history->history[%d] = %d\n", i, history->history[i]));
	}
	return;
}

// Print T_IM_MXIC_ALL_HISTORY_MONITOR data
void ct_im_mxic_print_all_history_monitor(T_IM_MXIC_ALL_HISTORY_MONITOR const* const allHistory)
{
	kint32 i, j;

	Ddim_Print(("---- T_IM_MXIC_ALL_HISTORY_MONITOR ----\n"));
	for (i = E_IM_MXIC_W_ARBITER_W1; i < E_IM_MXIC_W_ARBITER_MAX; i++) {
		for (j = E_IM_MXIC_PORT_0; j < E_IM_MXIC_PORT_MAX; j++) {
			Ddim_Print(("[W%d arbiter-Port%d]\n", (i + 1), j));
			ct_im_mxic_print_history_monitor(&allHistory->w_arbiter[i][j]);
		}
	}
	for (i = E_IM_MXIC_R_ARBITER_R1; i < E_IM_MXIC_R_ARBITER_MAX; i++) {
		for (j = E_IM_MXIC_PORT_0; j < E_IM_MXIC_PORT_MAX; j++) {
			Ddim_Print(("[R%d arbiter-Port%d]\n", (i + 1), j));
			ct_im_mxic_print_history_monitor(&allHistory->r_arbiter[i][j]);
		}
	}
	return;
}

// Print T_IM_MXIC_MEMORY_ACCESS_SLAVE data
void ct_im_mxic_print_memory_access_param(T_IM_MXIC_MEMORY_ACCESS_SLAVE const* const memaccParam)
{
	kint32 i;

	Ddim_Print(("---- T_IM_MXIC_MEMORY_ACCESS_SLAVE ----\n"));
	for (i = E_IM_MXIC_W_ARBITER_W1; i < E_IM_MXIC_W_ARBITER_MAX; i++) {
		Ddim_Print(("[W%d memory access]\n", (i + 1)));
		Ddim_Print(("memaccParam->slave[%d].start_trigger = %d\n"   , (i + 1), memaccParam->slave[i].start_trigger));
		Ddim_Print(("memaccParam->slave[%d].master47_1 = %llu\n"  , (i + 1), memaccParam->slave[i].master47_1));
		Ddim_Print(("memaccParam->slave[%d].master127_64 = %llu\n" , (i + 1), memaccParam->slave[i].master127_64));
		Ddim_Print(("memaccParam->slave[%d].start_address = %08X\n" , (i + 1), memaccParam->slave[i].start_address));
		Ddim_Print(("memaccParam->slave[%d].end_address = %08X\n" , (i + 1), memaccParam->slave[i].end_address));
		Ddim_Print(("memaccParam->slave[%d].mode = %d\n"            , (i + 1), memaccParam->slave[i].mode));
		Ddim_Print(("memaccParam->slave[%d].detect_master = %d\n" , (i + 1), memaccParam->slave[i].detect_master));
		Ddim_Print(("memaccParam->slave[%d].detect_address = %08X\n", (i + 1),
				memaccParam->slave[i].detect_address));
	}
	return;
}

// Print T_IM_MXIC_ALL_LEVELPORT  data
void ct_im_mxic_print_all_levelport(T_IM_MXIC_ALL_LEVELPORT* const allLevelport)
{
	kint32 i, j;

	Ddim_Print(("---- T_IM_MXIC_ALL_LEVELPORT ----\n"));
	for ( i = E_IM_MXIC_W_ARBITER_W1; i < E_IM_MXIC_W_ARBITER_MAX; i++ ) {

		for ( j = 0; j < D_IM_MXIC_MASTER_NUMBER_MAX-1; j++ ) {

			Ddim_Print(("allLevelport->w_arbiter[ %d ].port[ %d ] = %d\n", i, j,
					allLevelport->w_arbiter[ i ].port[ j ]));
			Ddim_Print(("allLevelport->w_arbiter[ %d ].level[ %d ] = %d\n",i, j,
					allLevelport->w_arbiter[ i ].level[ j ]));
		}
	}

	for ( i = E_IM_MXIC_R_ARBITER_R1; i < E_IM_MXIC_R_ARBITER_MAX; i++ ) {

		for ( j = 0; j < D_IM_MXIC_MASTER_NUMBER_MAX-1; j++ ) {

			Ddim_Print(("allLevelport->r_arbiter[ %d ].port[ %d ] = %d\n", i, j,
					allLevelport->r_arbiter[ i ].port[ j ]));
			Ddim_Print(("allLevelport->r_arbiter[ %d ].level[ %d ] = %d\n",i, j,
					allLevelport->r_arbiter[ i ].level[ j ]));
		}
	}

	return;
}

CtImMxicPrint* ct_im_mxic_print_new(void) 
{
    CtImMxicPrint *self = k_object_new_with_private(CT_TYPE_IM_MXIC_PRINT, sizeof(CtImMxicPrintPrivate));
    return self;
}
