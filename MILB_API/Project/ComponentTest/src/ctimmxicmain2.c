/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImMxicMain2类
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

#include "ctimmxicprint.h"
#include "ctimmxiccreate.h"
#include "ctimmxicfunc1.h"
#include "ctimmxicfunc2.h"
#include "ctmxiccheckerr1.h"
#include "ctmxiccheckerr2.h"
#include "ctimmxicmain.h"
#include "ctimmxicmain2.h"


G_DEFINE_TYPE(CtImMxicMain2, ct_im_mxic_main2, G_TYPE_OBJECT);
#define CT_IM_MXIC_MAIN2_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_MXIC_MAIN2, CtImMxicMain2Private))

struct _CtImMxicMain2Private
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

static void ct_im_mxic_main2_class_init(CtImMxicMain2Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImMxicMain2Private));
}

static void ct_im_mxic_main2_init(CtImMxicMain2 *self)
{
//	CtImMxicMain2Private *priv = CT_IM_MXIC_MAIN2_GET_PRIVATE(self);
	self->ctImMxicMain1 = ct_im_mxic_main1_new();
}

static void dispose_od(GObject *object)
{
	CtImMxicMain2 *self = (CtImMxicMain2*)object;
//	CtImMxicMain2Private *priv = CT_IM_MXIC_MAIN2_GET_PRIVATE(self);
	if(self->ctImMxicMain1){
		g_object_unref(self->ctImMxicMain1);
		self->ctImMxicMain1=NULL;
	}
}

static void finalize_od(GObject *object)
{
//	CtImMxicMain2 *self = (CtImMxicMain2*)object;
//	CtImMxicMain2Private *priv = CT_IM_MXIC_MAIN2_GET_PRIVATE(self);
}


/*
*PUBLIC
*/
void ct_im_mxic_main2(CtImMxicMain2 *self, gint32 argc, gchar** argv)
{
	guchar	transaction;
	guchar	master_priority;
	guchar	mask_enable;
	guchar	mask_select;
	E_IM_MXIC_PORT							port;
	E_IM_MXIC_PORT_GR						portAssign;
	E_IM_MXIC_LEVEL							level;
	T_IM_MXIC_SLOT_PRIORITY_LEVEL			levelCtrl;
	T_IM_MXIC_ALL_SLOT_PRIORITY_LEVEL		allLevelCtrl;
	T_IM_MXIC_MASTER_MASK					masterMask;
	T_IM_MXIC_OUTPUT_PORT					allPortAssign;
	T_IM_MXIC_ALL_LEVELPORT 				allLevelport;

//	CtImMxicMain2Private *self = CT_IM_MXIC_MAIN2_GET_PRIVATE(self);

	if (strcmp((const char *)argv[1], "pri") == 0) {
		if (strcmp((const char *)argv[2], "slot") == 0) {
			if (strcmp((const char *)argv[3], "one") == 0) {
				if (strcmp((const char *)argv[4], "set") == 0) {
					// [command] immxic pri slot one set P1 P2 P3 P4 P5 P6 P7 P8
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					//           P2: Write Or Read (0:Write, 1:Raed)
					//           P3: Arbiter (0:Slave-1, 1:Slave-2, 2:Slave-3, 3:Slave-4)
					//           P4: Port (0:port0, 1:port1, 2:port2, 3:port3)
					//           P5: Level control block (0:Level0, 1:Level1, 2:Level2)
					//           P6: Priority level type (0:Upper, 1:Lower, 2:Upper fixed, 3:Lower fixed)
					//           P7: Upper priority ratio (0~63. 0 means 64)
					//           P8: Lower priority ratio (0~63. 0 means 64)
					if( argc >= 13 ) {
						levelCtrl.priority_level_type  = (guchar)atoi((const char *)argv[10]);
						levelCtrl.upper_priority_level = (guchar)atoi((const char *)argv[11]);
						levelCtrl.lower_priority_level = (guchar)atoi((const char *)argv[12]);

						self->ctImMxicMain1->result = Im_MXIC_Set_Slot_Priority(
															(E_IM_MXIC_UNIT)atoi((const char *)argv[5]),
															(E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[6]),
															(E_IM_MXIC_SPEC_ARBITER)atoi((const char *)argv[7]),
															(E_IM_MXIC_PORT)atoi((const char *)argv[8]),
															(E_IM_MXIC_SLOT_LEVEL_CTRL)atoi((const char *)argv[9]),
															&levelCtrl);
						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							Ddim_Print(("Im_MXIC_Set_Slot_Priority OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Set_Slot_Priority NG. result=0x%X\n",
									self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 13\n"));
					}
				}
				else if (strcmp((const char *)argv[4], "get") == 0) {
					// [command] immxic pri slot one get P1 P2 P3 P4 P5
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					//           P2: Write Or Read (0:Write, 1:Raed)
					//           P3: Arbiter (0:Slave-1, 1:Slave-2, 2:Slave-3, 3:Slave-4)
					//           P4: Port (0:port0, 1:port1, 2:port2, 3:port3)
					//           P5: Level control block (0:Level0, 1:Level1, 2:Level2)
					if(argc >= 10) {
						self->ctImMxicMain1->result = Im_MXIC_Get_Slot_Priority(
															(E_IM_MXIC_UNIT)atoi((const char *)argv[5]),
															(E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[6]),
															(E_IM_MXIC_SPEC_ARBITER)atoi((const char *)argv[7]),
															(E_IM_MXIC_PORT)atoi((const char *)argv[8]),
															(E_IM_MXIC_SLOT_LEVEL_CTRL)atoi((const char *)argv[9]),
															&levelCtrl);

						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							Ddim_Print(("priority_level_type  = %d\n", levelCtrl.priority_level_type));
							Ddim_Print(("upper_priority_level = %d\n", levelCtrl.upper_priority_level));
							Ddim_Print(("lower_priority_level = %d\n", levelCtrl.lower_priority_level));
							Ddim_Print(("Im_MXIC_Get_Slot_Priority OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Get_Slot_Priority NG. result=0x%X\n",
									self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 5\n"));
					}
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "all") == 0) {
				if (strcmp((const char *)argv[4], "set") == 0) {
					// [command] immxic pri slot all set P1
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					// Get parameter for Im_MXIC_Set_Slot_Priority_All_Arbiter function.
					self->ctImMxicMain1->result = ct_im_mxic_create_slot_priority_all_arbiter_param(
							&allLevelCtrl);
					if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
						// Execute function.
						self->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[5]);
						self->ctImMxicMain1->result = Im_MXIC_Set_Slot_Priority_All_Arbiter(
								self->ctImMxicMain1->unit,&allLevelCtrl);
						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							Ddim_Print(("Im_MXIC_Set_Slot_Priority_All_Arbiter OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Set_Slot_Priority_All_Arbiter NG. result=0x%X\n",
									self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Command parameter error.\n"));
					}
				}
				else if (strcmp((const char *)argv[4], "get") == 0) {
					// [command] immxic pri slot all get P1
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					self->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[5]);
					self->ctImMxicMain1->result =
							Im_MXIC_Get_Slot_Priority_All_Arbiter(self->ctImMxicMain1->unit, &allLevelCtrl);
					if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
						ct_im_mxic_print_all_slot_priority_level( &allLevelCtrl);
						Ddim_Print(("Im_MXIC_Get_Slot_Priority_All_Arbiter OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_Slot_Priority_All_Arbiter NG. result=0x%X\n",
								self->ctImMxicMain1->result));
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
		else if (strcmp((const char *)argv[2], "master") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				// [command] immxic pri master set P1 P2 P3
				//           P1: Target self->ctImMxicMain1->unit number. (0-6)
				//           P2: Master number (Hex value)
				//           P3: Master priority (0~15)
				if(argc >= 7) {
					self->ctImMxicMain1->result = Im_MXIC_Set_Master_Priority(
														  (E_IM_MXIC_UNIT)atoi((const char *)argv[4]),
														  (guchar)ct_im_mxic_print_atoi_hex(argv[5]),
														  (guchar)atoi((const char *)argv[6]));
					if ( self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK ) {
						Ddim_Print(("Im_MXIC_Set_Master_Priority OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_Master_Priority NG. result=0x%X\n",
								self->ctImMxicMain1->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 3\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic pri master get P1 P2
				//           P1: Target self->ctImMxicMain1->unit number. (0-6)
				//           P2: Master number (Hex value)
				if(argc >= 6) {
					self->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
					self->ctImMxicMain1->result = Im_MXIC_Get_Master_Priority( self->ctImMxicMain1->unit,
							(guchar)ct_im_mxic_print_atoi_hex(argv[5]), &master_priority );
					if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("master_priority = %d\n", master_priority));
						Ddim_Print(("Im_MXIC_Get_Master_Priority OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_Master_Priority NG. result=0x%X\n",
								self->ctImMxicMain1->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 2\n"));
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
	else if (strcmp((const char *)argv[1], "mask") == 0) {
		if (strcmp((const char *)argv[2], "slot") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				// [command] immxic mask slot set P1 P2 P3 P4 P5 P6
				//           P1: Target self->ctImMxicMain1->unit number. (0-6)
				//           P2: Write Or Read (0:Write, 1:Raed)
				//           P3: Arbiter (0:Slave-1, 1:Slave-2, 2:Slave-3, 3:Slave-4)
				//           P4: Port (0~3)
				//           P5: Slot (0~3)
				//           P6: Mask enable (0:Disable, 1:Enable)
				if(argc >= 10) {
					self->ctImMxicMain1->result = Im_MXIC_Set_Slot_Mask(
													(E_IM_MXIC_UNIT)atoi((const char *)argv[4]),
													(E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[5]),
													(E_IM_MXIC_SPEC_ARBITER)atoi((const char *)argv[6]),
													(E_IM_MXIC_PORT)atoi((const char *)argv[7]),
													(E_IM_MXIC_SLOT)atoi((const char *)argv[8]),
													(guchar)atoi((const char *)argv[9]));
					if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("Im_MXIC_Set_Slot_Mask OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_Slot_Mask NG. result=0x%X\n", self->ctImMxicMain1->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 6\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic mask slot get P1 P2 P3 P4 P5
				//           P1: Target self->ctImMxicMain1->unit number. (0-6)
				//           P2: Write Or Read (0:Write, 1:Raed)
				//           P3: Arbiter (0:Slave-1, 1:Slave-2, 2:Slave-3, 3:Slave-4)
				//           P4: Port (0~3)
				//           P5: Slot (0~3)
				if(argc >= 9) {
					self->ctImMxicMain1->result = Im_MXIC_Get_Slot_Mask(
													(E_IM_MXIC_UNIT)atoi((const char *)argv[4]),
													(E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[5]),
													(E_IM_MXIC_SPEC_ARBITER)atoi((const char *)argv[6]),
													(E_IM_MXIC_PORT)atoi((const char *)argv[7]),
													(E_IM_MXIC_SLOT)atoi((const char *)argv[8]),
													&mask_enable);
					if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("mask_enable = %d\n", mask_enable));
						Ddim_Print(("Im_MXIC_Get_Slot_Mask OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_Slot_Mask NG. result=0x%X\n", self->ctImMxicMain1->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 5\n"));
				}
			}
			else {
				Ddim_Print(("E:Unknown command.\n"));
			}
		}
		else if (strcmp((const char *)argv[2], "master") == 0) {
			if (strcmp((const char *)argv[3], "enable") == 0) {
				if (strcmp((const char *)argv[4], "set") == 0) {
					// [command] immxic mask master enable set P1 P2 P3 P4
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					//           P2: Master number (Hex value)
					//           P3: Mask type (0:Mask OFF, 1:Mask ON, 2:Mask ON during specified period)
					//           P4: Mask period (4~4096. 0 means 4096.)
					if(argc >= 9) {
						self->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[5]);
						masterMask.mask_type   = (guchar)atoi((const char *)argv[7]);
						masterMask.mask_period = (USHORT)atoi((const char *)argv[8]);

						self->ctImMxicMain1->result = Im_MXIC_Set_Master_Mask(self->ctImMxicMain1->unit,
								(guchar)ct_im_mxic_print_atoi_hex(argv[6]), &masterMask);
						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							Ddim_Print(("Im_MXIC_Set_Master_Mask OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Set_Master_Mask NG. result=0x%X\n",self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 4\n"));
					}
				}
				else if (strcmp((const char *)argv[4], "get") == 0) {
					// [command] immxic mask master enable get P1 P2
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					//           P2: Master number (Hex value)
					if(argc >= 7) {
						self->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[5]);
						self->ctImMxicMain1->result = Im_MXIC_Get_Master_Mask(self->ctImMxicMain1->unit,
								(guchar)ct_im_mxic_print_atoi_hex(argv[6]), &masterMask);
						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							Ddim_Print(("masterMask.mask_type   = %d\n", masterMask.mask_type));
							Ddim_Print(("masterMask.mask_period = %d\n", masterMask.mask_period));
							Ddim_Print(("Im_MXIC_Get_Master_Mask OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Get_Master_Mask NG. result=0x%X\n",
									self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 2\n"));
					}
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "factor") == 0) {
				if (strcmp((const char *)argv[4], "set") == 0) {
					// [command] immxic mask master factor set P1 P2 P3 P4
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					//           P2: Master number (Hex value)
					//           P3: Mask group (0:Group-A, 1:Group-B)
					//           P4: Mask enable (0:Disable, 1:Enable)
					if(argc >= 9) {
						self->ctImMxicMain1->result = Im_MXIC_Set_Master_Mask_Factor(
																 (E_IM_MXIC_UNIT)atoi((const char *)argv[5]),
																 (guchar)ct_im_mxic_print_atoi_hex(argv[6]),
																 (E_IM_MXIC_MASK_GROUP)atoi((const char *)argv[7]),
																 (guchar)atoi((const char *)argv[8]));
						if ( self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK ) {
							Ddim_Print(("Im_MXIC_Set_Master_Mask_Factor OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Factor NG. result=0x%X\n",
									self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 4\n"));
					}
				}
				else if (strcmp((const char *)argv[4], "get") == 0) {
					// [command] immxic mask master factor get P1 P2 P3
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					//           P2: Master number (Hex value)
					//           P3: Mask group (0:Group-A, 1:Group-B)
					if(argc >= 8) {
						self->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[5]);
						self->ctImMxicMain1->result = Im_MXIC_Get_Master_Mask_Factor(self->ctImMxicMain1->unit,
															   (guchar)ct_im_mxic_print_atoi_hex(argv[6]),
															   (E_IM_MXIC_MASK_GROUP)atoi((const char *)argv[7]),
															   &mask_enable);
						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							Ddim_Print(("mask_enable = %d\n", mask_enable));
							Ddim_Print(("Im_MXIC_Get_Master_Mask_Factor OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Get_Master_Mask_Factor NG. result=0x%X\n",
									self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 3\n"));
					}
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "target") == 0) {
				if (strcmp((const char *)argv[4], "set") == 0) {
					// [command] immxic mask master target set P1 P2 P3 P4
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					//           P2: Master number (Hex value)
					//           P3: Mask group (0:Group-A, 1:Group-B)
					//           P4: Mask enable (0:Disable, 1:Enable)
					if(argc >= 9) {
						self->ctImMxicMain1->result = Im_MXIC_Set_Master_Mask_Target(
																 (E_IM_MXIC_UNIT)atoi((const char *)argv[5]),
																 (guchar)ct_im_mxic_print_atoi_hex(argv[6]),
																 (E_IM_MXIC_MASK_GROUP)atoi((const char *)argv[7]),
																 (guchar)atoi((const char *)argv[8]));
						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							Ddim_Print(("Im_MXIC_Set_Master_Mask_Target OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Target NG. result=0x%X\n",
									self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 4\n"));
					}
				}
				else if (strcmp((const char *)argv[4], "get") == 0) {
					// [command] immxic mask master target get P1 P2 P3
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					//           P2: Master number (Hex value)
					//           P3: Mask group (0:Group-A, 1:Group-B)
					if(argc >= 8) {
						self->ctImMxicMain1->result = Im_MXIC_Get_Master_Mask_Target(
																 (E_IM_MXIC_UNIT)atoi((const char *)argv[5]),
																 (guchar)ct_im_mxic_print_atoi_hex(argv[6]),
																 (E_IM_MXIC_MASK_GROUP)atoi((const char *)argv[7]),
																 &mask_enable);
						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							Ddim_Print(("mask_enable = %d\n", mask_enable));
							Ddim_Print(("Im_MXIC_Get_Master_Mask_Target OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Get_Master_Mask_Target NG. result=0x%X\n",
									self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 3\n"));
					}
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "select") == 0) {
				if (strcmp((const char *)argv[4], "set") == 0) {
					// [command] immxic mask master select set P1 P2 P3
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					//           P2: Master number (Hex value)
					//           P3: Mask select (0:Off, 1:On)
					if(argc >= 8) {
						self->ctImMxicMain1->result = Im_MXIC_Set_Master_Mask_Select(
																 (E_IM_MXIC_UNIT)atoi((const char *)argv[5]),
																 (guchar)ct_im_mxic_print_atoi_hex(argv[6]),
																 (guchar)atoi((const char *)argv[7]));
						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							Ddim_Print(("Im_MXIC_Set_Master_Mask_Select OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Set_Master_Mask_Select NG. result=0x%X\n",
									self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 3\n"));
					}
				}
				else if (strcmp((const char *)argv[4], "get") == 0) {
					// [command] immxic mask master select get P1 P2
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					//           P2: Master number (Hex value)
					if(argc >= 7) {
						self->ctImMxicMain1->result = Im_MXIC_Get_Master_Mask_Select(
																 (E_IM_MXIC_UNIT)atoi((const char *)argv[5]),
																 (guchar)ct_im_mxic_print_atoi_hex(argv[6]),
																 &mask_select);
						if ( self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK ) {
							Ddim_Print(("mask_select = %d\n", mask_select));
							Ddim_Print(("Im_MXIC_Get_Master_Mask_Select OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Get_Master_Mask_Select NG. result=0x%X\n",
									self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 2\n"));
					}
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "trn") == 0) {
				if (strcmp((const char *)argv[4], "set") == 0) {
					// [command] immxic mask master trn set P1 P2 P3
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					//           P2: Master number (Hex value)
					//           P3: Master transaction (0~63)
					if(argc >= 8) {
						self->ctImMxicMain1->result = Im_MXIC_Set_Master_Transaction(
																 (E_IM_MXIC_UNIT)atoi((const char *)argv[5]),
																 (guchar)ct_im_mxic_print_atoi_hex(argv[6]),
																 (guchar)atoi((const char *)argv[7]));
						if ( self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK ) {
							Ddim_Print(("Im_MXIC_Set_Master_Transaction OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Set_Master_Transaction NG. result=0x%X\n",
									self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 3\n"));
					}
				}
				else if (strcmp((const char *)argv[4], "get") == 0) {
					// [command] immxic mask master trn get P1 P2
					//           P1: Target self->ctImMxicMain1->unit number. (0-6)
					//           P2: Master number (Hex value)
					if(argc >= 7) {
						self->ctImMxicMain1->result = Im_MXIC_Get_Master_Transaction(
																 (E_IM_MXIC_UNIT)atoi((const char *)argv[5]),
																 (guchar)ct_im_mxic_print_atoi_hex(argv[6]),
																 &transaction);
						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							Ddim_Print(("transaction = %d\n", transaction));
							Ddim_Print(("Im_MXIC_Get_Master_Transaction OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Get_Master_Transaction NG. result=0x%X\n",
									self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 2\n"));
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
		else {
			Ddim_Print(("E:Unknown command.\n"));
		}
	}
	else if (strcmp((const char *)argv[1], "levelport") == 0) {
		if (strcmp((const char *)argv[2], "port") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				// [command] immxic levelport port set P1 P2 P3 P4 P5
				//           P1: Target self->ctImMxicMain1->unit number. (0-6)
				//           P2: Target write or read Arbiter (0:Write, 1:Read).
				//           P3: Target arbiter (0:Slave-1, 1:Slave-2, 2:Slave-3, 3:Slave-4).
				//           P4: Master number (Hex value).
				//           P5: Target Port (0-3).
				if(argc >= 9) {
					self->ctImMxicMain1->result = Im_MXIC_Set_LevelPort_Port(
														 (E_IM_MXIC_UNIT)atoi((const char *)argv[4]),
														 (E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[5]),
														 (E_IM_MXIC_SPEC_ARBITER)atoi((const char *)argv[6]),
														 (guchar)ct_im_mxic_print_atoi_hex(argv[7]),
														 (E_IM_MXIC_PORT)atoi((const char *)argv[8]) );
					if ( self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK ) {
						Ddim_Print(("Im_MXIC_Set_LevelPort_Port OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_LevelPort_Port NG. result=0x%X\n", self->ctImMxicMain1->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 5\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic levelport port get P1 P2 P3 P4
				//           P1: Target self->ctImMxicMain1->unit number. (0-6)
				//           P2: Target write or read Arbiter (0:Write, 1:Read).
				//           P3: Target arbiter (0:Slave-1, 1:Slave-2, 2:Slave-3, 3:Slave-4).
				//           P4: Master number (Hex value).
				if(argc >= 8) {
					self->ctImMxicMain1->result = Im_MXIC_Get_LevelPort_Port(
														 (E_IM_MXIC_UNIT)atoi((const char *)argv[4]),
														 (E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[5]),
														 (E_IM_MXIC_SPEC_ARBITER)atoi((const char *)argv[6]),
														 (guchar)ct_im_mxic_print_atoi_hex(argv[7]),
														 &port );
					if ( self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK ) {
						Ddim_Print(("Target port = %d\n", port));
						Ddim_Print(("Im_MXIC_Get_LevelPort_Port OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_LevelPort_Port NG. result=0x%X\n", self->ctImMxicMain1->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 4\n"));
				}
			}
			else {
				Ddim_Print(("E:Unknown command.\n"));
			}
		}
		else if (strcmp((const char *)argv[2], "level") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				// [command] immxic levelport level set P1 P2 P3 P4 P5
				//           P1: Target self->ctImMxicMain1->unit number. (0-6)
				//           P2: Target write or read Arbiter (0:Write, 1:Read).
				//           P3: Target arbiter (0:Slave-1, 1:Slave-2, 2:Slave-3, 3:Slave-4).
				//           P4: Master number (Hex value).
				//           P5: Target level (0-3).
				if(argc >= 9) {
					self->ctImMxicMain1->result = Im_MXIC_Set_LevelPort_Level(
														 (E_IM_MXIC_UNIT)atoi((const char *)argv[4]),
														 (E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[5]),
														 (E_IM_MXIC_SPEC_ARBITER)atoi((const char *)argv[6]),
														 (guchar)ct_im_mxic_print_atoi_hex(argv[7]),
														 (E_IM_MXIC_LEVEL)atoi((const char *)argv[8]) );
					if ( self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK ) {
						Ddim_Print(("Im_MXIC_Set_LevelPort_Level OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_LevelPort_Level NG.result=0x%X\n", self->ctImMxicMain1->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 5\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic levelport level get P1 P2 P3 P4
				//           P1: Target self->ctImMxicMain1->unit number. (0-6)
				//           P2: Target write or read Arbiter (0:Write, 1:Read).
				//           P3: Target arbiter (0:Slave-1, 1:Slave-2, 2:Slave-3, 3:Slave-4).
				//           P4: Master number (Hex value).
				if(argc >= 8) {
					self->ctImMxicMain1->result = Im_MXIC_Get_LevelPort_Level(
														 (E_IM_MXIC_UNIT)atoi((const char *)argv[4]),
														 (E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[5]),
														 (E_IM_MXIC_SPEC_ARBITER)atoi((const char *)argv[6]),
														 (guchar)ct_im_mxic_print_atoi_hex(argv[7]),
														 &level );
					if ( self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK ) {
						Ddim_Print(("Target level = %d\n", level));
						Ddim_Print(("Im_MXIC_Get_LevelPort_Level OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_LevelPort_Level NG.result=0x%X\n", self->ctImMxicMain1->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 4\n"));
				}
			}
			else {
				Ddim_Print(("E:Unknown command.\n"));
			}
		}
		else if (strcmp((const char *)argv[2], "all") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				// [command] immxic levelport all set P1
				//           P1: Target self->ctImMxicMain1->unit number. (0-6)
				self->ctImMxicMain1->result = ct_im_mxic_create_all_levelport_param( &allLevelport);
				if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
					// Execute function.
					self->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
					self->ctImMxicMain1->result = Im_MXIC_Set_LevelPort_All(self->ctImMxicMain1->unit,
							&allLevelport);
					if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("Im_MXIC_Set_LevelPort_All OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_LevelPort_All NG. result=0x%X\n",
								self->ctImMxicMain1->result));
					}
				}
				else {
					Ddim_Print(("E:Command parameter error.\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic levelport all get P1
				//           P1: Target self->ctImMxicMain1->unit number. (0-6)
				// Execute function.
				self->ctImMxicMain1->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
				self->ctImMxicMain1->result = Im_MXIC_Get_LevelPort_All(self->ctImMxicMain1->unit, &allLevelport);
				if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
					ct_im_mxic_print_all_levelport(&allLevelport);
					Ddim_Print(("Im_MXIC_Get_LevelPort_All OK.\n"));
				}
				else {
					Ddim_Print(("E:Im_MXIC_Get_LevelPort_All NG. result=0x%X\n", self->ctImMxicMain1->result));
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
	else if (strcmp((const char *)argv[1], "port") == 0) {
		if (strcmp((const char *)argv[2], "assign") == 0) {
			if (strcmp((const char *)argv[3], "one") == 0) {
				if (strcmp((const char *)argv[4], "set") == 0) {
					// [command] immxic port assign one set P1 P2
					//           P1: master number group (Hex value)
					//           P2: port (0:port0, 1:port1)
					if(argc >= 7) {
						self->ctImMxicMain1->result = Im_MXIC_Set_Output_Port(
														(guchar)ct_im_mxic_print_atoi_hex(argv[5]),
														(E_IM_MXIC_PORT_GR)atoi((const char *)argv[6]));
						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							Ddim_Print(("Im_MXIC_Set_Output_Port OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Set_Output_Port NG. result=0x%X\n", self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 7\n"));
					}
				}
				else if (strcmp((const char *)argv[4], "get") == 0) {
					// [command] immxic port assign one get P1
					//           P1: master number group (Hex value)
					if(argc >= 6) {
						self->ctImMxicMain1->result = Im_MXIC_Get_Output_Port(
								(guchar)ct_im_mxic_print_atoi_hex(argv[5]), &portAssign);
						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							Ddim_Print(("portAssign = %d\n", portAssign));
							Ddim_Print(("Im_MXIC_Get_Output_Port OK.\n"));
						}
						else {
							Ddim_Print(("E:Im_MXIC_Get_Output_Port NG.result=0x%X\n", self->ctImMxicMain1->result));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 6\n"));
					}
				}
				else {
					Ddim_Print(("E:Unknown command.\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "all") == 0) {
				if (strcmp((const char *)argv[4], "set") == 0) {
					// [command] immxic port assign all set PP
					//           PP: Port set pattern.
					//               0 : All 0
					//               1 : All 1
					//               2 : Random pattern 1
					//               3 : Random pattern 2
					if(argc >= 6) {
						self->ctImMxicMain1->result = ct_im_mxic_create_all_port_set( atoi((const char *)argv[5]),
								&allPortAssign);
						if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
							self->ctImMxicMain1->result = Im_MXIC_Set_Output_Port_All(&allPortAssign);
							if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
								Ddim_Print(("Im_MXIC_Set_Output_Port_All OK.\n"));
							}
							else {
								Ddim_Print(("E:Im_MXIC_Set_Output_Port_All NG.result=0x%X\n",
										self->ctImMxicMain1->result));
							}
						}
						else {
							Ddim_Print(("E:Command parameter error.\n"));
						}
					}
					else {
						Ddim_Print(("E:Parameter nums must be 6\n"));
					}
				}
				else if (strcmp((const char *)argv[4], "get") == 0) {
					// [command] immxic port assign all get
					self->ctImMxicMain1->result = Im_MXIC_Get_Output_Port_All(&allPortAssign);
					if (self->ctImMxicMain1->result == DriverCommon_D_DDIM_OK) {
						ct_im_mxic_print_all_port_assign( &allPortAssign);
						Ddim_Print(("Im_MXIC_Get_Output_Port_All OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_Output_Port_All NG. result=0x%X\n", self->ctImMxicMain1->result));
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
		else {
			Ddim_Print(("E:Unknown command.\n"));
		}
	}
}

CtImMxicMain2 *ct_im_mxic_main2_new(void) 
{
    CtImMxicMain2 *self = g_object_new(CT_TYPE_IM_MXIC_MAIN2, NULL);
    return self;
}
