/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :jianghaodong
*@brief               :CtImMxicMain类
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
#include "ctimmxicfunc2.h"
#include "ctmxiccheckerr1.h"
#include "ctmxiccheckerr2.h"

#include "ctimmxicmain1.h"
#include "ctimmxicmain2.h"
#include "ctimmxicmain.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImMxicMain, ct_im_mxic_main);
#define CT_IM_MXIC_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImMxicMainPrivate,CT_TYPE_IM_MXIC_MAIN))

struct _CtImMxicMainPrivate
{
	CtImMxicMain2* ctImMxicMain2;
};


/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
#ifdef CO_ACT_MXIC_HCLOCK
extern volatile kuchar gIM_MXIC_Hclk_Ctrl_Cnt;
#endif // CO_ACT_MXIC_HCLOCK
#ifdef CO_ACT_MXIC_PCLOCK
extern volatile kuchar gIM_MXIC_Pclk_Ctrl_Cnt;
#endif // CO_ACT_MXIC_PCLOCK

/*
*IMPL
*/
static void ct_im_mxic_main_constructor(CtImMxicMain *self) 
{
	CtImMxicMainPrivate *priv = CT_IM_MXIC_MAIN_GET_PRIVATE(self);
	priv->ctImMxicMain2 = ct_im_mxic_main2_new();

}

static void ct_im_mxic_main_destructor(CtImMxicMain *self) 
{
	CtImMxicMainPrivate *priv = CT_IM_MXIC_MAIN_GET_PRIVATE(self);
	if(priv->ctImMxicMain2){
		k_object_unref(priv->ctImMxicMain2);
	}
	priv->ctImMxicMain2=NULL;
}

/*
*PUBLIC
*/
void Ct_Im_MXIC_Main(kint32 argc, kchar** argv)
{
	kuchar	thstopEnable;
	kuchar	monState;
	kuint32	monResult;

	T_IM_MXIC_HISTORY_MONITOR				history;
	T_IM_MXIC_ALL_HISTORY_MONITOR			allHistory;
	T_IM_MXIC_ALL_SLOT_STATUS_MONITOR		allSlotStatus;
	T_IM_MXIC_W_ARBITER_ASSIGN_GR			wGrSlotStatus;
	T_IM_MXIC_R_ARBITER_ASSIGN_GR			rGrSlotStatus;
	T_IM_MXIC_MASTER_STATUS_MONITOR			masterStatus;
	T_IM_MXIC_ALL_ACCESS_OR_TRANS_MONITOR	allAccTrans;
	T_IM_MXIC_MONITOR_PARAMETER				monParam;
	T_IM_MXIC_MEMORY_ACCESS_SLAVE			memoryAccess;

	CtImMxicMain *self = ct_im_mxic_main_new();
	CtImMxicMainPrivate *priv = CT_IM_MXIC_MAIN_GET_PRIVATE(self);

	ct_im_mxic_main1(priv->ctImMxicMain2->ctImMxicMain1,argc, argv);
	ct_im_mxic_main2(priv->ctImMxicMain2,argc, argv);

	if (strcmp((const char *)argv[1], "monitor") == 0) {
			if (strcmp((const char *)argv[2], "start") == 0) {
				// [command] immxic monitor start
				Im_MXIC_Start_Monitor();
				Ddim_Print(("Im_MXIC_Start_Monitor OK.\n"));
			}
			else if (strcmp((const char *)argv[2], "stop") == 0) {
				// [command] immxic monitor stop
				Im_MXIC_Stop_Monitor();
				Ddim_Print(("Im_MXIC_Stop_Monitor OK.\n"));
			}
			else if (strcmp((const char *)argv[2], "hist") == 0) {
				if (strcmp((const char *)argv[3], "thstop") == 0) {
					if (strcmp((const char *)argv[4], "set") == 0) {
						// [command] immxic monitor hist thstop set P1
						//           P1: THSTOP enable (0:Disable, 1:Enable)
						if(argc >= 6) {
							priv->ctImMxicMain2->ctImMxicMain1->result =
									Im_MXIC_Set_History_Monitor_Stop_Enable((kuchar)atoi((const char *)argv[5]));
							if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
								Ddim_Print(("Im_MXIC_Set_History_Monitor_Stop_Enable OK.\n"));
							}
							else {
								Ddim_Print(("E:Im_MXIC_Set_History_Monitor_Stop_Enable NG. result=0x%X\n",
										priv->ctImMxicMain2->ctImMxicMain1->result));
							}
						}
						else {
							Ddim_Print(("E:Parameter nums must be 1\n"));
						}
					}
					else if (strcmp((const char *)argv[4], "get") == 0) {
						// [command] immxic monitor hist thstop get
						priv->ctImMxicMain2->ctImMxicMain1->result =
								Im_MXIC_Get_History_Monitor_Stop_Enable(&thstopEnable);
						if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
							Ddim_Print(("thstopEnable = %d\n", thstopEnable));
							Ddim_Print(("Im_MXIC_Get_History_Monitor_Stop_Enable OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Get_History_Monitor_Stop_Enable NG. result=0x%X\n",
									priv->ctImMxicMain2->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Unknown command.\n"));
					}
				}
				else if (strcmp((const char *)argv[3], "one") == 0) {
					// [command] immxic monitor hist one P1 P2 P3
					//           P1: Write Or Read (0:Write, 1:Raed)
					//           P2: Arbiter (0:Slave-1, 1:Slave-2, 2:Slave-3, 3:Slave-4)
					//           P3: Port (0:port0, 1:port1, 2:port2, 3:port3)
					if(argc >= 7) {
						priv->ctImMxicMain2->ctImMxicMain1->result =
								Im_MXIC_Get_History_Monitor((E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[4]),
															(E_IM_MXIC_SPEC_ARBITER)atoi((const char *)argv[5]),
															(E_IM_MXIC_PORT)atoi((const char *)argv[6]),
															&history);
						if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
							ct_im_mxic_print_history_monitor(&history);
							Ddim_Print(("Im_MXIC_Get_History_Monitor OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Get_History_Monitor NG. result=0x%X\n",
									priv->ctImMxicMain2->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 3\n"));
					}
				}
				else if (strcmp((const char *)argv[3], "all") == 0) {
					// [command] immxic monitor hist all
					priv->ctImMxicMain2->ctImMxicMain1->result = Im_MXIC_Get_History_Monitor_All_Port(&allHistory);
					if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
						ct_im_mxic_print_all_history_monitor(&allHistory);
						Ddim_Print(("Im_MXIC_Get_History_Monitor_All_Port OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_History_Monitor_All_Port NG. result=0x%X\n",
								priv->ctImMxicMain2->ctImMxicMain1->result));
					}
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[2], "status") == 0) {
				if (strcmp((const char *)argv[3], "slot") == 0) {
					if (strcmp((const char *)argv[4], "all") == 0) {
						// [command] immxic monitor status slot all P1
						//           P1: Target priv->ctImMxicMain2->ctImMxicMain1->unit number. (0-6)
						priv->ctImMxicMain2->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[5]);
						priv->ctImMxicMain2->ctImMxicMain1->result =
								Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter(priv->ctImMxicMain2->ctImMxicMain1->unit,
										&allSlotStatus);
						if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
							ct_im_mxic_print_all_slot_status_monitor( &allSlotStatus);
							Ddim_Print(("Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter NG. result=0x%X\n",
									priv->ctImMxicMain2->ctImMxicMain1->result));
						}
					}
					else if (strcmp((const char *)argv[4], "w") == 0) {
						// [command] immxic monitor status slot w P1 P2
						//           P1: Target priv->ctImMxicMain2->ctImMxicMain1->unit number. (0-6)
						//           P2: W arbiter (0:W1, 1:W2, 2:W3, 3:W4)
						if(argc >= 7) {
							priv->ctImMxicMain2->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[5]);
							priv->ctImMxicMain2->ctImMxicMain1->result =
									Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter(priv->ctImMxicMain2->ctImMxicMain1->unit,
											(E_IM_MXIC_W_ARBITER)atoi((const char *)argv[6]),
											&priv->ctImMxicMain2->ctImMxicMain1->wSlotStatus);
							if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
								ct_im_mxic_print_w_arbiter_assign(
										&priv->ctImMxicMain2->ctImMxicMain1->wSlotStatus);
								Ddim_Print(("Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter OK.\n"));
							}
							else {
								Ddim_Print(("E:Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter NG. result=0x%X\n",
										priv->ctImMxicMain2->ctImMxicMain1->result));
							}
						}
						else {
							Ddim_Print(("E:Parameter nums must be 2\n"));
						}
					}
					else if (strcmp((const char *)argv[4], "r") == 0) {
						// [command] immxic monitor status slot r P1 P2
						//           P1: Target priv->ctImMxicMain2->ctImMxicMain1->unit number. (0-6)
						//           P2: R arbiter (0:R1, 1:R2, 2:R3, 3:R4)
						if(argc >= 7) {
							priv->ctImMxicMain2->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[5]);
							priv->ctImMxicMain2->ctImMxicMain1->result =
									Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter(priv->ctImMxicMain2->ctImMxicMain1->unit,
											(E_IM_MXIC_R_ARBITER)atoi((const char *)argv[6]),
											&priv->ctImMxicMain2->ctImMxicMain1->rSlotStatus);
							if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
								ct_im_mxic_print_r_arbiter_assign(
										&priv->ctImMxicMain2->ctImMxicMain1->rSlotStatus);
								Ddim_Print(("Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter OK.\n"));
							}
							else {
								Ddim_Print(("E:Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter NG. result=0x%X\n",
										priv->ctImMxicMain2->ctImMxicMain1->result));
							}
						}
						else {
							Ddim_Print(("E:Parameter nums must be 2\n"));
						}
					}
					else if (strcmp((const char *)argv[4], "wgr") == 0) {
						// [command] immxic monitor status slot wgr P1
						//           P1: Group W arbiter (0:W1, 1:W2, 2:W3, 3:W4, 4:W5, 5:W6, 6:W7)
						if(argc >= 6) {
							priv->ctImMxicMain2->ctImMxicMain1->result =
									Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter_Group(
											(E_IM_MXIC_W_ARBITER_GR)atoi((const char *)argv[5]), &wGrSlotStatus);
							if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
								ct_im_mxic_print_w_arbiter_assign_group( &wGrSlotStatus);
								Ddim_Print(("Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter_Group OK.\n"));
							}
							else {
								Ddim_Print(("E:Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter_Group NG. result=0x%X\n",
										priv->ctImMxicMain2->ctImMxicMain1->result));
							}
						}
						else {
							Ddim_Print(("E:Parameter nums must be 1\n"));
						}
					}
					else if (strcmp((const char *)argv[4], "rgr") == 0) {
						// [command] immxic monitor status slot rgr P1
						//           P1: Group R arbiter (0:R1, 1:R2, 2:R3, 3:R4, 4:R5, 5:R6, 6:R7)
						if(argc >= 6) {
							priv->ctImMxicMain2->ctImMxicMain1->result =
									Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter_Group(
											(E_IM_MXIC_R_ARBITER_GR)atoi((const char *)argv[5]), &rGrSlotStatus);
							if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
								ct_im_mxic_print_r_arbiter_assign_group( &rGrSlotStatus);
								Ddim_Print(("Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter_Group OK.\n"));
							}
							else {
								Ddim_Print(("E:Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter_Group NG. result=0x%X\n",
										priv->ctImMxicMain2->ctImMxicMain1->result));
							}
						}
						else {
							Ddim_Print(("E:Parameter nums must be 1\n"));
						}
					}
					else {
						Ddim_Print(("E:Unknown command.\n"));
					}
				}
				else if (strcmp((const char *)argv[3], "master") == 0) {
					// [command] immxic monitor status master P1
					//           P1: Target priv->ctImMxicMain2->ctImMxicMain1->unit number. (0-6)
					priv->ctImMxicMain2->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
					priv->ctImMxicMain2->ctImMxicMain1->result =
						Im_MXIC_Get_Master_Status_Monitor(priv->ctImMxicMain2->ctImMxicMain1->unit, &masterStatus);
					if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
						ct_im_mxic_print_master_status_monitor( &masterStatus);
						Ddim_Print(("Im_MXIC_Get_Master_Status_Monitor OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_Master_Status_Monitor NG. result=0x%X\n",
								priv->ctImMxicMain2->ctImMxicMain1->result));
					}
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[2], "acc") == 0) {
				if (strcmp((const char *)argv[3], "param") == 0) {
					if (strcmp((const char *)argv[4], "set") == 0) {
						// [command] immxic monitor acc param set PP
						//           PP: Port set pattern. (0~4)
						if(argc >= 6) {
							// Get parameter for Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter function.
							priv->ctImMxicMain2->ctImMxicMain1->result =
									ct_im_mxic_create_access_or_trans_monitor_param(
											(kuchar)atoi((const char *)argv[5]), &monParam);
							if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
								// Execute function.
								priv->ctImMxicMain2->ctImMxicMain1->result =
										Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter(&monParam);
								if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
									Ddim_Print(("Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter OK.\n"));
								}
								else {
									Ddim_Print(("E:Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter NG. result=0x%X\n",
											priv->ctImMxicMain2->ctImMxicMain1->result));
								}
							}
							else {
								Ddim_Print(("E:Command parameter error.\n"));
							}
						}
						else {
							Ddim_Print(("E:Parameter nums must be 1\n"));
						}
					}
					else if (strcmp((const char *)argv[4], "get") == 0) {
						// [command] immxic monitor acc param get
						priv->ctImMxicMain2->ctImMxicMain1->result =
								Im_MXIC_Get_Access_Or_Trans_Monitor_Parameter(&monParam);
						if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
							ct_im_mxic_print_monitor_parameter( &monParam);
							Ddim_Print(("Im_MXIC_Get_Access_Or_Trans_Monitor_Parameter OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Get_Access_Or_Trans_Monitor_Parameter NG. result=0x%X\n",
									priv->ctImMxicMain2->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Unknown command.\n"));
					}
				}
				else if (strcmp((const char *)argv[3], "priv->ctImMxicMain2->ctImMxicMain1->result") == 0) {
					if (strcmp((const char *)argv[4], "all") == 0) {
						// [command] immxic monitor acc priv->ctImMxicMain2->ctImMxicMain1->result all
						priv->ctImMxicMain2->ctImMxicMain1->result =
								Im_MXIC_Get_Access_Or_Trans_Monitor_All_Entry(&allAccTrans);
						if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
							ct_im_mxic_print_all_access_or_trans_monitor( &allAccTrans);
							Ddim_Print(("Im_MXIC_Get_Access_Or_Trans_Monitor_All_Entry OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Get_Access_Or_Trans_Monitor_All_Entry NG. result=0x%X\n",
									priv->ctImMxicMain2->ctImMxicMain1->result));
						}
					}
					else if (strcmp((const char *)argv[4], "one") == 0) {
						// [command] immxic monitor acc priv->ctImMxicMain2->ctImMxicMain1->result one P1
						//           P1: Monitor number (0~3)
						if(argc >= 6) {
							priv->ctImMxicMain2->ctImMxicMain1->result =
								Im_MXIC_Get_Access_Or_Trans_Monitor((kuchar)atoi((const char *)argv[5]), &monResult);
							if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
								Ddim_Print(("monResult = %d\n", monResult));
								Ddim_Print(("Im_MXIC_Get_Access_Or_Trans_Monitor OK.\n"));
							}
							else {
								Ddim_Print(("E:Im_MXIC_Get_Access_Or_Trans_Monitor NG. result=0x%X\n",
										priv->ctImMxicMain2->ctImMxicMain1->result));
							}
						}
						else {
							Ddim_Print(("E:Parameter nums must be 1\n"));
						}
					}
					else {
						Ddim_Print(("E:Unknown command.\n"));
					}
				}
				else if (strcmp((const char *)argv[3], "state") == 0) {
					// [command] immxic monitor acc state
					priv->ctImMxicMain2->ctImMxicMain1->result =
							Im_MXIC_Get_Access_Or_Trans_Monitor_Limit_End_State(&monState);
					if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
						Ddim_Print(("monState = %d\n", monState));
						Ddim_Print(("Im_MXIC_Get_Access_Or_Trans_Monitor_Limit_End_State OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_Access_Or_Trans_Monitor_Limit_End_State NG. result=0x%X\n",
								priv->ctImMxicMain2->ctImMxicMain1->result));
					}
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else {
				Ddim_Print(("E:Unknown command.\n"));
			}
		}
		else if (strcmp((const char *)argv[1], "memacc") == 0) {
			if (strcmp((const char *)argv[2], "start") == 0) {
				// [command] immxic memacc start P1 P2
				//           P1: Target priv->ctImMxicMain2->ctImMxicMain1->unit number. (0-6)
				//           P2: W arbiter (0:W1, 1:W2, 2:W3, 3:W4 9:ALL)
				if (argc >= 5) {
					priv->ctImMxicMain2->ctImMxicMain1->result =
						ct_im_mxic_create_memory_access_start_trigger( atoi((const char *)argv[4]), &memoryAccess);
					if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
						priv->ctImMxicMain2->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[3]);
						priv->ctImMxicMain2->ctImMxicMain1->result =
								Im_MXIC_Start_Memory_Access_Detect(priv->ctImMxicMain2->ctImMxicMain1->unit,
										&memoryAccess);
						if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
							Ddim_Print(("Im_MXIC_Start_Memory_Access_Detect OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Start_Memory_Access_Detect NG. result=0x%X\n",
									priv->ctImMxicMain2->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Command parameter error.\n"));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 2\n"));
				}
			}
			else if (strcmp((const char *)argv[2], "stop") == 0) {
				// [command] immxic memacc stop
				//           P1: Target priv->ctImMxicMain2->ctImMxicMain1->unit number. (0-6)
				priv->ctImMxicMain2->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[3]);
				Im_MXIC_Stop_Memory_Access_Detect(priv->ctImMxicMain2->ctImMxicMain1->unit);
				Ddim_Print(("Im_MXIC_Stop_Memory_Access_Detect OK.\n"));
			}
			else if (strcmp((const char *)argv[2], "set") == 0) {
				// [command] immxic memacc set P1 P2 P3
				//           P1: Target priv->ctImMxicMain2->ctImMxicMain1->unit number. (0-6)
				//           P2: W arbiter (0:W1, 1:W2, 2:W3, 3:W4 9:ALL)
				//           P3: Parameter Pattern (0~1)
				if(argc >= 6) {
					priv->ctImMxicMain2->ctImMxicMain1->result =
							ct_im_mxic_create_memory_access_param(
									atoi((const char *)argv[4]), atoi((const char *)argv[5]), &memoryAccess);
					if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
						priv->ctImMxicMain2->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[3]);
						Im_MXIC_Set_Memory_Access_Detect(priv->ctImMxicMain2->ctImMxicMain1->unit, &memoryAccess);
						if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
							Ddim_Print(("Im_MXIC_Set_Memory_Access_Detect OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Set_Memory_Access_Detect NG. result=0x%X\n",
									priv->ctImMxicMain2->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Command parameter error.\n"));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 3\n"));
				}
			}
			else if (strcmp((const char *)argv[2], "get") == 0) {
				// [command] immxic memacc get P1
				//           P1: Target priv->ctImMxicMain2->ctImMxicMain1->unit number. (0-6)
				priv->ctImMxicMain2->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[3]);
				priv->ctImMxicMain2->ctImMxicMain1->result =
						Im_MXIC_Get_Memory_Access_Detect(priv->ctImMxicMain2->ctImMxicMain1->unit, &memoryAccess);
				if (priv->ctImMxicMain2->ctImMxicMain1->result == D_DDIM_OK) {
					ct_im_mxic_print_memory_access_param(&memoryAccess);
					Ddim_Print(("Im_MXIC_Get_Memory_Access_Detect OK.\n"));
				}
				else {
					Ddim_Print(("E:Im_MXIC_Get_Memory_Access_Detect NG. result=0x%X\n",
							priv->ctImMxicMain2->ctImMxicMain1->result));
				}
			}
		}
		else if (strcmp((const char *)argv[1], "err") == 0) {
			// Test command for processing of parameter check
			if (strcmp((const char *)argv[2], "start") == 0) {
				// Im_MXIC_Start_Config
				// [command] immxic err start
				ct_mxic_check_err1_start_config();
			}
			else if (strcmp((const char *)argv[2], "clock") == 0) {
				// Im_MXIC_Set_Clock_Enable
				// Im_MXIC_Get_Clock_Enable
				// [command] immxic err clock
				ct_mxic_check_err1_clock_enable();
			}
			else if (strcmp((const char *)argv[2], "acc_capa") == 0) {
				if (strcmp((const char *)argv[3], "slave") == 0) {
					// Im_MXIC_Set_Acceptance_Capability
					// Im_MXIC_Get_Acceptance_Capability
					// [command] immxic err acc_capa slave
					ct_mxic_check_err1_acceptance_capability();
				}
				else if (strcmp((const char *)argv[3], "group") == 0) {
					// Im_MXIC_Set_Acceptance_Capability_Group
					// Im_MXIC_Get_Acceptance_Capability_Group
					// [command] immxic err acc_capa group
					ct_mxic_check_err1_acceptance_capability_group();
				}
				else if (strcmp((const char *)argv[3], "all") == 0) {
					// Im_MXIC_Set_Acceptance_Capability_All_Port
					// Im_MXIC_Get_Acceptance_Capability_All_Port
					// [command] immxic err acc_capa all
					ct_mxic_check_err1_acceptance_capability_all_port();
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[2], "slave_area") == 0) {
				if (strcmp((const char *)argv[3], "one") == 0) {
					// Im_MXIC_Set_Slave_Area
					// Im_MXIC_Get_Slave_Area
					// [command] immxic err slave_area one
					ct_mxic_check_err1_slave_area();
				}
				else if (strcmp((const char *)argv[3], "all") == 0) {
					// Im_MXIC_Set_Slave_Area_All
					// Im_MXIC_Get_Slave_Area_All
					// [command] immxic err slave_area all
					ct_mxic_check_err1_slave_area_all();
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[2], "dec_err") == 0) {
				// Im_MXIC_Set_Decode_Error_Int
				// Im_MXIC_Get_Decode_Error_Int
				// Im_MXIC_Get_Decode_Error
				// [command] immxic err dec_err
				ct_mxic_check_err1_decode_error();
			}
			else if (strcmp((const char *)argv[2], "levelport") == 0) {
				if (strcmp((const char *)argv[3], "level") == 0) {
					// Im_MXIC_Set_LevelPort_Level
					// Im_MXIC_Get_LevelPort_Level
					// [command] immxic err levelport level
					ct_mxic_check_err1_levelport_level();
				}
				else if (strcmp((const char *)argv[3], "port") == 0) {
					// Im_MXIC_Set_LevelPort_Port
					// Im_MXIC_Get_LevelPort_Port
					// [command] immxic err levelport port
					ct_mxic_check_err1_levelport_port();
				}
				else if (strcmp((const char *)argv[3], "all") == 0) {
					// Im_MXIC_Set_LevelPort_All
					// Im_MXIC_Get_LevelPort_All
					// [command] immxic err levelport all
					ct_mxic_check_err1_levelport_all();
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[2], "port_assign") == 0) {
				if (strcmp((const char *)argv[3], "one") == 0) {
					// Im_MXIC_Set_Output_Port
					// Im_MXIC_Get_Output_Port
					// [command] immxic err port_assign one
					ct_mxic_check_err1_port_assign();
				}
				else if (strcmp((const char *)argv[3], "all") == 0) {
					// Im_MXIC_Set_Output_Port_All
					// Im_MXIC_Get_Output_Port_All
					// [command] immxic err port_assign all
					ct_mxic_check_err1_port_assign_all();
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[2], "master") == 0) {
				if (strcmp((const char *)argv[3], "w") == 0) {
					// Im_MXIC_Set_Master_W_Arbiter
					// Im_MXIC_Get_Master_W_Arbiter
					// [command] immxic err master w
					ct_mxic_check_err1_master_w_arbiter();
				}
				else if (strcmp((const char *)argv[3], "r") == 0) {
					// Im_MXIC_Set_Master_R_Arbiter
					// Im_MXIC_Get_Master_R_Arbiter
					// [command] immxic err master r
					ct_mxic_check_err1_master_r_arbiter();
				}
				else if (strcmp((const char *)argv[3], "all") == 0) {
					// Im_MXIC_Set_Master_All_Arbiter
					// Im_MXIC_Get_Master_All_Arbiter
					// [command] immxic err master all
					ct_mxic_check_err1_master_all_arbiter();
				}
				else if (strcmp((const char *)argv[3], "overlap") == 0) {
					// Im_MXIC_Set_Master_R_Arbiter
					// Im_MXIC_Set_Master_W_Arbiter
					ct_mxic_check_err1_master_overlap();
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[2], "pri") == 0) {
				if (strcmp((const char *)argv[3], "slot") == 0) {
					if (strcmp((const char *)argv[4], "one") == 0) {
						// Im_MXIC_Set_Slot_Priority
						// Im_MXIC_Get_Slot_Priority
						// [command] immxic err pri slot one
						ct_mxic_check_err1_slot_priority();
					}
					else if (strcmp((const char *)argv[4], "all") == 0) {
						// Im_MXIC_Set_Slot_Priority_All_Arbiter
						// Im_MXIC_Get_Slot_Priority_All_Arbiter
						// [command] immxic err pri slot all
						ct_mxic_check_err2_slot_priority_all_arbiter();
					}
					else {
						Ddim_Print(("E:Unknown command.\n"));
					}
				}
				else if (strcmp((const char *)argv[3], "master") == 0) {
					// Im_MXIC_Set_Master_Priority
					// Im_MXIC_Get_Master_Priority
					// [command] immxic err pri master
					ct_mxic_check_err2_master_priority();
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[2], "mask") == 0) {
				if (strcmp((const char *)argv[3], "slot") == 0) {
					// Im_MXIC_Set_Slot_Mask
					// Im_MXIC_Get_Slot_Mask
					// [command] immxic err mask slot
					ct_mxic_check_err2_slot_mask();
				}
				else if (strcmp((const char *)argv[3], "master") == 0) {
					if (strcmp((const char *)argv[4], "enable") == 0) {
						// Im_MXIC_Set_Master_Mask
						// Im_MXIC_Get_Master_Mask
						// [command] immxic err mask master enable
						ct_mxic_check_err2_master_mask();
					}
					else if (strcmp((const char *)argv[4], "factor") == 0) {
						// Im_MXIC_Set_Master_Mask_Factor
						// Im_MXIC_Get_Master_Mask_Factor
						// [command] immxic err mask master factor
						ct_mxic_check_err2_master_mask_factor();
					}
					else if (strcmp((const char *)argv[4], "target") == 0) {
						// Im_MXIC_Set_Master_Mask_Target
						// Im_MXIC_Get_Master_Mask_Target
						// [command] immxic err mask master target
						ct_mxic_check_err2_master_mask_target();
					}
					else if (strcmp((const char *)argv[4], "select") == 0) {
						// Im_MXIC_Set_Master_Mask_Select
						// Im_MXIC_Get_Master_Mask_Select
						// [command] immxic err mask master select
						ct_mxic_check_err2_master_mask_select();
					}
					else if (strcmp((const char *)argv[4], "trn") == 0) {
						// Im_MXIC_Set_Master_Transaction
						// Im_MXIC_Get_Master_Transaction
						// [command] immxic err master transaction
						ct_mxic_check_err2_master_transaction();
					}
					else {
						Ddim_Print(("E:Unknown command.\n"));
					}
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[2], "monitor") == 0) {
				if (strcmp((const char *)argv[3], "hist") == 0) {
					if (strcmp((const char *)argv[4], "thstop") == 0) {
						// Im_MXIC_Set_History_Monitor_Stop_Enable
						// Im_MXIC_Get_History_Monitor_Stop_Enable
						// [command] immxic err monitor hist thstop
						ct_mxic_check_err2_history_monitor_stop_enable();
					}
					else if (strcmp((const char *)argv[4], "one") == 0) {
						// Im_MXIC_Get_History_Monitor
						// [command] immxic err monitor hist one
						ct_mxic_check_err2_history_monitor();
					}
					else if (strcmp((const char *)argv[4], "all") == 0) {
						// Im_MXIC_Get_History_Monitor_All_Port
						// [command] immxic err monitor hist all
						ct_mxic_check_err2_history_monitor_all_port();
					}
					else {
						Ddim_Print(("E:Unknown command.\n"));
					}
				}
				else if (strcmp((const char *)argv[3], "status") == 0) {
					if (strcmp((const char *)argv[4], "slot") == 0) {
						if (strcmp((const char *)argv[5], "all") == 0) {
							// Im_MXIC_Get_Slot_Status_Monitor_All_Arbiter
							// [command] immxic err monitor status slot all
							ct_mxic_check_err2_slot_status_monitor_all_arbiter();
						}
						else if (strcmp((const char *)argv[5], "slave") == 0) {
							if (strcmp((const char *)argv[6], "w") == 0) {
								// Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter
								// [command] immxic err monitor status slot w
								ct_mxic_check_err2_slot_status_monitor_w_arbiter();
							}
							else if(strcmp((const char *)argv[6], "r") == 0) {
								// Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter
								// [command] immxic err monitor status slot r
								ct_mxic_check_err2_slot_status_monitor_r_arbiter();
							}
							else {
								Ddim_Print(("E:Unknown command.\n"));
							}
						}
						else if (strcmp((const char *)argv[5], "group") == 0) {
							if (strcmp((const char *)argv[6], "w") == 0) {
								// Im_MXIC_Get_Slot_Status_Monitor_W_Arbiter
								// [command] immxic err monitor status slot w
								ct_mxic_check_err2_slot_status_monitor_w_arbiter_group();
							}
							else if(strcmp((const char *)argv[6], "r") == 0) {
								// Im_MXIC_Get_Slot_Status_Monitor_R_Arbiter
								// [command] immxic err monitor status slot r
								ct_mxic_check_err2_slot_status_monitor_r_arbiter_group();
							}
							else {
								Ddim_Print(("E:Unknown command.\n"));
							}
						}
						else {
							Ddim_Print(("E:Unknown command.\n"));
						}
					}
					else if (strcmp((const char *)argv[4], "master") == 0) {
						// Im_MXIC_Get_Master_Status_Monitor
						// [command] immxic err monitor status master
						ct_mxic_check_err2_master_status_monitor();
					}
					else {
						Ddim_Print(("E:Unknown command.\n"));
					}
				}
				else if (strcmp((const char *)argv[3], "acc") == 0) {
					if (strcmp((const char *)argv[4], "param") == 0) {
						if (strcmp((const char *)argv[5], "set") == 0) {
							// Im_MXIC_Set_Access_Or_Trans_Monitor_Parameter
							// [command] immxic err monitor acc param set
							ct_mxic_check_err2_set_access_or_trans_monitor_parameter();
						}
						else if (strcmp((const char *)argv[5], "get") == 0) {
							// Im_MXIC_Get_Access_Or_Trans_Monitor_Parameter
							// [command] immxic err monitor acc param get
							ct_mxic_check_err2_get_access_or_trans_monitor_parameter();
						}
						else {
							Ddim_Print(("E:Unknown command.\n"));
						}
					}
					else if (strcmp((const char *)argv[4], "priv->ctImMxicMain2->ctImMxicMain1->result") == 0) {
						if (strcmp((const char *)argv[5], "one") == 0) {
							// Im_MXIC_Get_Access_Or_Trans_Monitor
							// [command] immxic err monitor acc priv->ctImMxicMain2->ctImMxicMain1->result one
							ct_mxic_check_err2_access_or_trans_monitor();
						}
						else if (strcmp((const char *)argv[5], "all") == 0) {
							// Im_MXIC_Get_Access_Or_Trans_Monitor_All_Entry
							// [command] immxic err monitor acc priv->ctImMxicMain2->ctImMxicMain1->result all
							ct_mxic_check_err2_access_or_trans_monitor_all_entry();
						}
						else {
							Ddim_Print(("E:Unknown command.\n"));
						}
					}
					else if (strcmp((const char *)argv[4], "state") == 0) {
						// Im_MXIC_Get_Access_Or_Trans_Monitor_Limit_End_State
						// [command] immxic err monitor acc state
						ct_mxic_check_err2_sccess_or_trans_monitor_limit_end_state();
					}
					else {
						Ddim_Print(("E:Unknown command.\n"));
					}
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[2], "memacc") == 0) {
				if (strcmp((const char *)argv[3], "start") == 0) {
					// Im_MXIC_Start_Memory_Access_Detect
					// [command] immxic err memacc start
					ct_mxic_check_err2_memory_access_start();
				}
				else if (strcmp((const char *)argv[3], "set") == 0) {
					// Im_MXIC_Set_Memory_Access_Detect
					// [command] immxic err memacc set
					ct_mxic_check_err2_memory_access_set();
				}
				else if (strcmp((const char *)argv[3], "get") == 0) {
					// Im_MXIC_Get_Memory_Access_Detect
					// [command] immxic err memacc get
					ct_mxic_check_err2_memory_access_get();
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else {
				Ddim_Print(("E:Unknown command.\n"));
			}
		}
		else {
			Ddim_Print(("E:Unknown command.\n"));
		}
	#ifdef CO_ACT_MXIC_HCLOCK
		if(gIM_MXIC_Hclk_Ctrl_Cnt != 0){
			Ddim_Print(("E:Hclk NG : gIM_MXIC_Hclk_Ctrl_Cnt=%d.\n", gIM_MXIC_Hclk_Ctrl_Cnt));
		}
	#endif // CO_ACT_MXIC_HCLOCK
	#ifdef CO_ACT_MXIC_PCLOCK
		if(gIM_MXIC_Pclk_Ctrl_Cnt != 0){
			Ddim_Print(("E:Pclk NG : gIM_MXIC_Pclk_Ctrl_Cnt=%d.\n", gIM_MXIC_Pclk_Ctrl_Cnt));
		}
	#endif // CO_ACT_MXIC_PCLOCK

		k_object_unref(self);
		self=NULL;

		return;
}

CtImMxicMain* ct_im_mxic_main_new(void) 
{
    CtImMxicMain *self = k_object_new_with_private(CT_TYPE_IM_MXIC_MAIN, sizeof(CtImMxicMainPrivate));
    return self;
}
