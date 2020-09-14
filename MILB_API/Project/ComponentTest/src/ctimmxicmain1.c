/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImMxicMain1类
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
#include "ctimmxicfunc1.h"
#include "ctimmxicfunc2.h"
#include "ctmxiccheckerr1.h"
#include "ctmxiccheckerr2.h"

#include "ctimmxicmain2.h"
#include "ctimmxicmain.h"

#include "ctimmxicmain1.h"


G_DEFINE_TYPE(CtImMxicMain1, ct_im_mxic_main1, G_TYPE_OBJECT);
#define CT_IM_MXIC_MAIN1_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_MXIC_MAIN1, CtImMxicMain1Private))

struct _CtImMxicMain1Private
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

static void ct_im_mxic_main1_class_init(CtImMxicMain1Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImMxicMain1Private));
}

static void ct_im_mxic_main1_init(CtImMxicMain1 *self)
{
//	CtImMxicMain1Private *priv = CT_IM_MXIC_MAIN1_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
//	CtImMxicMain1 *self = (CtImMxicMain1*)object;
//	CtImMxicMain1Private *priv = CT_IM_MXIC_MAIN1_GET_PRIVATE(self);
}

static void finalize_od(GObject *object)
{
//	CtImMxicMain1 *self = (CtImMxicMain1*)object;
//	CtImMxicMain1Private *priv = CT_IM_MXIC_MAIN1_GET_PRIVATE(self);
}


/*
*PUBLIC
*/
void ct_im_mxic_main1(CtImMxicMain1 *self,gint32 argc, gchar** argv)
{
	guint32	i, j;
	guint32	workvalue;
	guchar	capability;
	guchar*	addr;

	T_IM_MXIC_CONFIG_ARBITER				config;
	T_IM_MXIC_CLOCK							clockCtrl;
	T_IM_MXIC_ALL_ACCEPTANCE_CAPABILITY		allCapability;
	T_IM_MXIC_SLAVE_AREA					slaveArea;
	T_IM_MXIC_ALL_SLAVE_AREA				allSlaveArea;
	T_IM_MXIC_DEC_ERR_INT					decErrInt;
	T_IM_MXIC_DEC_ERR						decErr;
	T_IM_MXIC_ALL_ARBITER_ASSIGN			allArbiterAssign;

	if (strcmp((const char *)argv[1], "reset") == 0) {
		// MXIC reset
		// [command] immxic reset P1
		//           P1 : Target self->unit number. (0-6)
		self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[2]);
		Im_MXIC_Reset( self->unit );
		Ddim_Print(("Im_MXIC_Reset(self->unit=%d) OK.\n", self->unit));
	}
	else if (strcmp((const char *)argv[1], "init") == 0) {
		// MXIC initialize
		// [command] immxic init P1
		//           P1 : Target self->unit number. (0-6)
		self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[2]);
		self->result = Im_MXIC_Init( self->unit );
		if (self->result == DriverCommon_D_DDIM_OK) {
			Ddim_Print(("Im_MXIC_Init OK(self->unit=%d).\n", self->unit));
		}
		else {
			Ddim_Print(("E:Im_MXIC_Init NG(self->unit=%d). self->result=0x%X\n", self->result, self->unit));
		}
	}
	else if (strcmp((const char *)argv[1], "start") == 0) {
		// Configration start
		// [command] immxic start P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19
		//	P20 P21 P22 P23 P24 P25
		//           P1 : Target self->unit number. (0-6)
		//           P2 : Configration enable of Slave W1 arbiter. (0:Disable, 1:Enable)
		//           P3 : Configration enable of Slave W2 arbiter. (0:Disable, 1:Enable)
		//           P4 : Configration enable of Slave W3 arbiter. (0:Disable, 1:Enable)
		//           P5 : Configration enable of Slave W4 arbiter. (0:Disable, 1:Enable)
		//           P6 : Configration enable of Slave R1 arbiter. (0:Disable, 1:Enable)
		//           P7 : Configration enable of Slave R2 arbiter. (0:Disable, 1:Enable)
		//           P8 : Configration enable of Slave R3 arbiter. (0:Disable, 1:Enable)
		//           P9 : Configration enable of Slave R4 arbiter. (0:Disable, 1:Enable)
		//           P10: Configration enable of Group W1 arbiter. (0:Disable, 1:Enable)
		//           P11: Configration enable of Group W2 arbiter. (0:Disable, 1:Enable)
		//           P12: Configration enable of Group W3 arbiter. (0:Disable, 1:Enable)
		//           P13: Configration enable of Group W4 arbiter. (0:Disable, 1:Enable)
		//           P14: Configration enable of Group W5 arbiter. (0:Disable, 1:Enable)
		//           P15: Configration enable of Group W6 arbiter. (0:Disable, 1:Enable)
		//           P16: Configration enable of Group W7 arbiter. (0:Disable, 1:Enable)
		//           P17: Configration enable of Group W8 arbiter. (0:Disable, 1:Enable)
		//           P18: Configration enable of Group R1 arbiter. (0:Disable, 1:Enable)
		//           P19: Configration enable of Group R2 arbiter. (0:Disable, 1:Enable)
		//           P20: Configration enable of Group R3 arbiter. (0:Disable, 1:Enable)
		//           P21: Configration enable of Group R4 arbiter. (0:Disable, 1:Enable)
		//           P22: Configration enable of Group R5 arbiter. (0:Disable, 1:Enable)
		//           P23: Configration enable of Group R6 arbiter. (0:Disable, 1:Enable)
		//           P24: Configration enable of Group R7 arbiter. (0:Disable, 1:Enable)
		//           P25: Configration enable of Group R8 arbiter. (0:Disable, 1:Enable)

		if(argc >= 25) {
			self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[2]);
			config.sl_w1_config_on_flg = atoi((const char *)argv[3]);
			config.sl_w2_config_on_flg = atoi((const char *)argv[4]);
			config.sl_w3_config_on_flg = atoi((const char *)argv[5]);
			config.sl_w4_config_on_flg = atoi((const char *)argv[6]);
			config.sl_r1_config_on_flg = atoi((const char *)argv[7]);
			config.sl_r2_config_on_flg = atoi((const char *)argv[8]);
			config.sl_r3_config_on_flg = atoi((const char *)argv[9]);
			config.sl_r4_config_on_flg = atoi((const char *)argv[10]);
			config.gr_w0_config_on_flg = atoi((const char *)argv[11]);
			config.gr_w1_config_on_flg = atoi((const char *)argv[12]);
			config.gr_w2_config_on_flg = atoi((const char *)argv[13]);
			config.gr_w3_config_on_flg = atoi((const char *)argv[14]);
			config.gr_w4_config_on_flg = atoi((const char *)argv[15]);
			config.gr_w5_config_on_flg = atoi((const char *)argv[16]);
			config.gr_w6_config_on_flg = atoi((const char *)argv[17]);
			config.gr_w7_config_on_flg = atoi((const char *)argv[18]);
			config.gr_r0_config_on_flg = atoi((const char *)argv[19]);
			config.gr_r1_config_on_flg = atoi((const char *)argv[20]);
			config.gr_r2_config_on_flg = atoi((const char *)argv[21]);
			config.gr_r3_config_on_flg = atoi((const char *)argv[22]);
			config.gr_r4_config_on_flg = atoi((const char *)argv[23]);
			config.gr_r5_config_on_flg = atoi((const char *)argv[24]);
			config.gr_r6_config_on_flg = atoi((const char *)argv[25]);
			config.gr_r7_config_on_flg = atoi((const char *)argv[26]);

			self->result = Im_MXIC_Start_Config( self->unit, &config );
			if (self->result == DriverCommon_D_DDIM_OK) {
				Ddim_Print(("Im_MXIC_Start_Config OK(self->unit=%d).\n", self->unit));
			}
			else {
				Ddim_Print(("E:Im_MXIC_Start_Config NG(self->unit=%d). self->result=0x%X\n", self->unit,
						self->result));
			}
		}
		else {
			Ddim_Print(("E:Parameter nums must be 25\n"));
		}
	}
	else if (strcmp((const char *)argv[1], "clock") == 0) {
		if (strcmp((const char *)argv[2], "set") == 0) {
			// Set clock
			// [command] immxic clock set P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19
			//	P20 P21 P22 P23 P24 P25 P26 P27
			//           P1 : Target self->unit number. (0-6)
			//           P2 : Clock enable of Slave-1_0 arbiter.        (0:Disable, 1:Enable)
			//           P3 : Clock enable of Slave-1_1 arbiter.        (0:Disable, 1:Enable)
			//           P4 : Clock enable of Slave-1_2 arbiter.        (0:Disable, 1:Enable)
			//           P5 : Clock enable of Slave-1_3 arbiter.        (0:Disable, 1:Enable)
			//           P6 : Clock enable of Slave-2_0 arbiter.        (0:Disable, 1:Enable)
			//           P7 : Clock enable of Slave-2_1 arbiter.        (0:Disable, 1:Enable)
			//           P8 : Clock enable of Slave-2_2 arbiter.        (0:Disable, 1:Enable)
			//           P9 : Clock enable of Slave-2_3 arbiter.        (0:Disable, 1:Enable)
			//           P10: Clock enable of Slave-3_0 arbiter.        (0:Disable, 1:Enable)
			//           P11: Clock enable of Slave-3_1 arbiter.        (0:Disable, 1:Enable)
			//           P12: Clock enable of Slave-3_2 arbiter.        (0:Disable, 1:Enable)
			//           P13: Clock enable of Slave-3_3 arbiter.        (0:Disable, 1:Enable)
			//           P14: Clock enable of Slave-4_0 arbiter.        (0:Disable, 1:Enable)
			//           P15: Clock enable of Slave-4_1 arbiter.        (0:Disable, 1:Enable)
			//           P16: Clock enable of Slave-4_2 arbiter.        (0:Disable, 1:Enable)
			//           P17: Clock enable of Slave-4_3 arbiter.        (0:Disable, 1:Enable)
			//           P18: Clock enable of Group-1 arbiter.          (0:Disable, 1:Enable)
			//           P19: Clock enable of Group-2 arbiter.          (0:Disable, 1:Enable)
			//           P20: Clock enable of Group-3 arbiter.          (0:Disable, 1:Enable)
			//           P21: Clock enable of Group-4 arbiter.          (0:Disable, 1:Enable)
			//           P22: Clock enable of Group-5 arbiter.          (0:Disable, 1:Enable)
			//           P23: Clock enable of Group-6 arbiter.          (0:Disable, 1:Enable)
			//           P24: Clock enable of Group-7 arbiter.          (0:Disable, 1:Enable)
			//           P25: Clock enable of Group-8 arbiter.          (0:Disable, 1:Enable)
			//           P26: Clock enable of decode error block.       (0:Disable, 1:Enable)
			//           P27: Clock enable of monitor function block.   (0:Disable, 1:Enable)
			if(argc >= 27) {
				self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[3]);
				clockCtrl.clk_en_slave_1_0 = atoi((const char *)argv[4]);
				clockCtrl.clk_en_slave_1_1 = atoi((const char *)argv[5]);
				clockCtrl.clk_en_slave_1_2 = atoi((const char *)argv[6]);
				clockCtrl.clk_en_slave_1_3 = atoi((const char *)argv[7]);
				clockCtrl.clk_en_slave_2_0 = atoi((const char *)argv[8]);
				clockCtrl.clk_en_slave_2_1 = atoi((const char *)argv[9]);
				clockCtrl.clk_en_slave_2_2 = atoi((const char *)argv[10]);
				clockCtrl.clk_en_slave_2_3 = atoi((const char *)argv[11]);
				clockCtrl.clk_en_slave_3_0 = atoi((const char *)argv[12]);
				clockCtrl.clk_en_slave_3_1 = atoi((const char *)argv[13]);
				clockCtrl.clk_en_slave_3_2 = atoi((const char *)argv[14]);
				clockCtrl.clk_en_slave_3_3 = atoi((const char *)argv[15]);
				clockCtrl.clk_en_slave_4_0 = atoi((const char *)argv[16]);
				clockCtrl.clk_en_slave_4_1 = atoi((const char *)argv[17]);
				clockCtrl.clk_en_slave_4_2 = atoi((const char *)argv[18]);
				clockCtrl.clk_en_slave_4_3 = atoi((const char *)argv[19]);
				clockCtrl.clk_en_group_0   = atoi((const char *)argv[20]);
				clockCtrl.clk_en_group_1   = atoi((const char *)argv[21]);
				clockCtrl.clk_en_group_2   = atoi((const char *)argv[22]);
				clockCtrl.clk_en_group_3   = atoi((const char *)argv[23]);
				clockCtrl.clk_en_group_4   = atoi((const char *)argv[24]);
				clockCtrl.clk_en_group_5   = atoi((const char *)argv[25]);
				clockCtrl.clk_en_group_6   = atoi((const char *)argv[26]);
				clockCtrl.clk_en_group_7   = atoi((const char *)argv[27]);
				clockCtrl.clk_en_dec_err   = atoi((const char *)argv[28]);
				clockCtrl.clk_en_monitor   = atoi((const char *)argv[29]);

				self->result = Im_MXIC_Set_Clock_Enable(self->unit, &clockCtrl);
				if (self->result == DriverCommon_D_DDIM_OK) {
					Ddim_Print(("Im_MXIC_Set_Clock_Enable OK(self->unit=%d).\n",self->unit));
				}
				else {
					Ddim_Print(("E:Im_MXIC_Set_Clock_Enable NG(self->unit=%d). self->result=0x%X\n", self->unit,
							self->result));
				}
			}
			else {
				Ddim_Print(("E:Parameter nums must be 27\n"));
			}
		}
		else if (strcmp((const char *)argv[2], "get") == 0) {
			// Get clock
			// [command] immxic clock get P1
			//           P1 : Target self->unit number. (0-6)
			if(argc >= 4) {
				self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[3]);
				self->result = Im_MXIC_Get_Clock_Enable(self->unit, &clockCtrl);
				if (self->result == DriverCommon_D_DDIM_OK) {
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
					Ddim_Print(("E:Im_MXIC_Get_Clock_Enable NG(self->unit=%d). self->result=0x%X\n", self->unit,
							self->result));
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
	else if (strcmp((const char *)argv[1], "acc_capa") == 0) {
		if (strcmp((const char *)argv[2], "slave") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				// [command] immxic acc_capa slave set P1 P2 P3 P4 P5
				//           P1: Target self->unit number. (0-6)
				//           P2: Write Or Read (0:Write, 1:Raed)
				//           P3: Arbiter (0:Slave-1, 1:Slave-2, 2:Slave-3, 3:Slave-4)
				//           P4: Port (0~3)
				//           P5: Acceptance capability (1~8)
				if(argc >= 9) {
					self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
					self->result = Im_MXIC_Set_Acceptance_Capability(self->unit,
															  (E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[5]),
															  (E_IM_MXIC_SPEC_ARBITER)atoi((const char *)argv[6]),
															  (E_IM_MXIC_PORT)atoi((const char *)argv[7]),
															  (guchar)atoi((const char *)argv[8]));
					if (self->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("Im_MXIC_Set_Acceptance_Capability OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_Acceptance_Capability NG. self->result=0x%X\n", self->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 5\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic acc_capa slave get P1 P2 P3 P4
				//           P1: Target self->unit number. (0-6)
				//           P2: Write Or Read (0:Write, 1:Raed)
				//           P3: Arbiter (0:Slave-1, 1:Slave-2, 2:Slave-3, 3:Slave-4)
				//           P4: Port (0~3)
				if(argc >= 8) {
					self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
					self->result = Im_MXIC_Get_Acceptance_Capability(self->unit,
															  (E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[5]),
															  (E_IM_MXIC_SPEC_ARBITER)atoi((const char *)argv[6]),
															  (E_IM_MXIC_PORT)atoi((const char *)argv[7]),
															  &capability);
					if (self->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("capability = %d\n", capability));
						Ddim_Print(("Im_MXIC_Get_Acceptance_Capability OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_Acceptance_Capability NG. self->result=0x%X\n", self->result));
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
		else if (strcmp((const char *)argv[2], "group") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				// [command] immxic acc_capa group set P1 P2 P3 P4
				//           P1: Write Or Read (0:Write, 1:Raed)
				//           P2: Arbiter (0:Group-0, 1:Group-1, 2:Group-2, 3:Group-3, 4:Group-4,
				//			  5:Group-5, 6:Group-6, 7:Group-7)
				//           P3: Port (0~1)
				//           P4: Acceptance capability (1~8)
				if(argc >= 8) {
					self->result = Im_MXIC_Set_Acceptance_Capability_Group(
														 (E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[4]),
														 (E_IM_MXIC_SPEC_ARBITER_GR)atoi((const char *)argv[5]),
														 (E_IM_MXIC_PORT_GR)atoi((const char *)argv[6]),
														 (guchar)atoi((const char *)argv[7]));
					if (self->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("Im_MXIC_Set_Acceptance_Capability_Group OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_Acceptance_Capability_Group NG. self->result=0x%X\n",
								self->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 4\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic acc_capa group get P1 P2 P3
				//           P1: Write Or Read (0:Write, 1:Raed)
				//           P2: Arbiter (0:Group-0, 1:Group-1, 2:Group-2, 3:Group-3, 4:Group-4,
				//			  5:Group-5, 6:Group-6, 7:Group-7)
				//           P3: Port (0~1)
				if(argc >= 7) {
					self->result = Im_MXIC_Get_Acceptance_Capability_Group(
															(E_IM_MXIC_WR_ARBITER)atoi((const char *)argv[4]),
															(E_IM_MXIC_SPEC_ARBITER_GR)atoi((const char *)argv[5]),
															(E_IM_MXIC_PORT_GR)atoi((const char *)argv[6]),
															&capability);
					if (self->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("capability = %d\n", capability));
						Ddim_Print(("Im_MXIC_Get_Acceptance_Capability_Group OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_Acceptance_Capability_Group NG. self->result=0x%X\n",
								self->result));
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
		else if (strcmp((const char *)argv[2], "all") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				// [command] immxic acc_capa all set P1 P2
				//           P1: Target self->unit number. (0-6)
				//           P2: acceptance capability pattern
				//               1: acceptance capability ALL 1
				//               2: acceptance capability ALL 8
				if(argc >= 6) {
					self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
					if (strcmp((const char *)argv[5], "1") == 0) {
						workvalue = 1;
					}
					else if (strcmp((const char *)argv[5], "2") == 0) {
						workvalue = 8;
					}
					else {
						Ddim_Print(("E:Parameter error P1=%d\n", atoi((const char *)argv[5])));
						return;
					}

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

					self->result = Im_MXIC_Set_Acceptance_Capability_All_Port(self->unit, &allCapability);
					if (self->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("Im_MXIC_Set_Acceptance_Capability_All_Port OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_Acceptance_Capability_All_Port NG. self->result=0x%X\n",
								self->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 2\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic acc_capa all get P1
				//           P1: Target self->unit number. (0-6)
				if(argc >= 5) {
					self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
					self->result = Im_MXIC_Get_Acceptance_Capability_All_Port(self->unit, &allCapability);
					if (self->result == DriverCommon_D_DDIM_OK) {
						ct_im_mxic_print_all_acceptance_capability(&allCapability);
						Ddim_Print(("Im_MXIC_Get_Acceptance_Capability_All_Port OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_Acceptance_Capability_All_Port NG. self->result=0x%X\n",
								self->result));
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
		else {
			Ddim_Print(("E:Unknown command.\n"));
		}
	}
	else if (strcmp((const char *)argv[1], "slaveArea") == 0) {
		if (strcmp((const char *)argv[2], "one") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				if(argc >= 8) {
					// [command] immxic slaveArea one set P1 P2 P3 P4
					//           P1: Target self->unit number. (0-6)
					//           P2: Slave area number (0:Slave number-1, 1:Slave number-2,
					// 			  2:Slave number-3, 3:Slave number-4)
					//           P3: Size of slave area (Hex value)
					//           P4: Start address of slave area (Hex value)
					self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
					slaveArea.size    = (guint32)ct_im_mxic_print_atoi_hex(argv[6]);
					slaveArea.address = (guint32)ct_im_mxic_print_atoi_hex(argv[7]);

					self->result = Im_MXIC_Set_Slave_Area(self->unit,
							(E_IM_MXIC_SLAVE_NUMBER)atoi((const char *)argv[5]), &slaveArea);
					if (self->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("Im_MXIC_Set_Slave_Area OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_Slave_Area NG. self->result=0x%X\n", self->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 8\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic slaveArea one get P1 P2
				//           P1: Target self->unit number. (0-6)
				//           P2: Slave area number (0:Slave number-1, 1:Slave number-2,
				//           2:Slave number-3, 3:Slave number-4)
				if(argc >= 6) {
					self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
					self->result = Im_MXIC_Get_Slave_Area(self->unit,
							(E_IM_MXIC_SLAVE_NUMBER)atoi((const char *)argv[5]), &slaveArea);
					if (self->result == DriverCommon_D_DDIM_OK) {
						ct_im_mxic_print_slave_area(&slaveArea);
						Ddim_Print(("Im_MXIC_Get_Slave_Area OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_Slave_Area NG. self->result=0x%X\n", self->result));
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
		else if (strcmp((const char *)argv[2], "all") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				if(argc >= 13) {
					// [command] immxic slaveArea all set P1 P2 P3 P4 P5 P6 P7 P8 P9
					//           P1: Target self->unit number. (0-6)
					//           P2: Slave number-1: Size of slave area (Hex value)
					//           P3: Slave number-1: Start address of slave area (Hex value)
					//           P4: Slave number-2: Size of slave area (Hex value)
					//           P5: Slave number-2: Start address of slave area (Hex value)
					//           P6: Slave number-3: Size of slave area (Hex value)
					//           P7: Slave number-3: Start address of slave area (Hex value)
					//           P8: Slave number-4: Size of slave area (Hex value)
					//           P9: Slave number-4: Start address of slave area (Hex value)
					self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
					allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_1].size    =
							(guint32)ct_im_mxic_print_atoi_hex(argv[5]);
					allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_1].address =
							(guint32)ct_im_mxic_print_atoi_hex(argv[6]);
					allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_2].size    =
							(guint32)ct_im_mxic_print_atoi_hex(argv[7]);
					allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_2].address =
							(guint32)ct_im_mxic_print_atoi_hex(argv[8]);
					allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_3].size    =
							(guint32)ct_im_mxic_print_atoi_hex(argv[9]);
					allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_3].address =
							(guint32)ct_im_mxic_print_atoi_hex(argv[10]);
					allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_4].size    =
							(guint32)ct_im_mxic_print_atoi_hex(argv[11]);
					allSlaveArea.slave_area[E_IM_MXIC_SLAVE_NUMBER_4].address =
							(guint32)ct_im_mxic_print_atoi_hex(argv[12]);

					self->result = Im_MXIC_Set_Slave_Area_All(self->unit, &allSlaveArea);
					if (self->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("Im_MXIC_Set_Slave_Area_All OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_Slave_Area_All NG. self->result=0x%X\n", self->result));
					}
				}
				else {
					Ddim_Print(("E:Parameter nums must be 13\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic slaveArea all get P1
				//           P1: Target self->unit number. (0-6)
				if(argc >= 5) {
					self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
					self->result = Im_MXIC_Get_Slave_Area_All(self->unit, &allSlaveArea);
					if (self->result == DriverCommon_D_DDIM_OK) {
						ct_im_mxic_print_all_slave_area(&allSlaveArea);
						Ddim_Print(("Im_MXIC_Get_Slave_Area_All OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Get_Slave_Area_All NG. self->result=0x%X\n", self->result));
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
		else {
			Ddim_Print(("E:Unknown command.\n"));
		}
	}
	else if (strcmp((const char *)argv[1], "decErr") == 0) {
		if (strcmp((const char *)argv[2], "set_int") == 0) {
			// [command] immxic decErr set_int P1 P2 P3 P4
			//           P1: Target self->unit number. (0-6)
			//           P2: Interrupt enable of W channel decode error (0:Disable, 1:Enable)
			//           P3: Interrupt enable of R channel decode error (0:Disable, 1:Enable)
			//           P4: Callback function (0:NULL, 1:ct_im_mxic_create_dec_err_cb)
			if(argc >= 7) {
				self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[3]);
				decErrInt.w_err_int_en = (guchar)atoi((const char *)argv[4]);
				decErrInt.r_err_int_en = (guchar)atoi((const char *)argv[5]);

				if (atoi((const char *)argv[6]) == 0) {
					decErrInt.pCallBack = NULL;
				}
				else {
					decErrInt.pCallBack = ct_im_mxic_create_dec_err_cb;
				}

				self->result = Im_MXIC_Set_Decode_Error_Int(self->unit, &decErrInt);
				if (self->result == DriverCommon_D_DDIM_OK) {
					Ddim_Print(("Im_MXIC_Set_Decode_Error_Int OK.\n"));
				}
				else {
					Ddim_Print(("E:Im_MXIC_Set_Decode_Error_Int NG. self->result=0x%X\n", self->result));
				}
			}
			else {
				Ddim_Print(("E:Parameter nums must be 4\n"));
			}
		}
		else if (strcmp((const char *)argv[2], "get_int") == 0) {
			// [command] immxic decErr get_int P1
			//           P1: Target self->unit number. (0-6)
			if(argc >= 4) {
				self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[3]);
				self->result = Im_MXIC_Get_Decode_Error_Int(self->unit, &decErrInt);
				if (self->result == DriverCommon_D_DDIM_OK) {
					ct_im_mxic_print_dec_err_int(&decErrInt);
					Ddim_Print(("Im_MXIC_Get_Decode_Error_Int OK.\n"));
				}
				else {
					Ddim_Print(("E:Im_MXIC_Get_Decode_Error_Int NG. self->result=0x%X\n", self->result));
				}
			}
			else {
				Ddim_Print(("E:Parameter nums must be 1\n"));
			}
		}
		else if (strcmp((const char *)argv[2], "get") == 0) {
			// [command] immxic decErr get P1
			//           P1: Target self->unit number. (0-6)
			if(argc >= 4) {
				self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[3]);
				self->result = Im_MXIC_Get_Decode_Error(self->unit, &decErr);
				if (self->result == DriverCommon_D_DDIM_OK) {
					ct_im_mxic_print_dec_err(&decErr);
					Ddim_Print(("Im_MXIC_Get_Decode_Error OK.\n"));
				}
				else {
					Ddim_Print(("E:Im_MXIC_Get_Decode_Error NG. self->result=0x%X\n", self->result));
				}
			}
			else {
				Ddim_Print(("E:Parameter nums must be 1\n"));
			}
		}
		else if (strcmp((const char *)argv[2], "access") == 0) {
			// [command] immxic decErr access P1
			//           P1: Access target address
			addr = (guchar*)ct_im_mxic_print_atoi_hex(argv[3]);
			Ddim_Print(("Read address 0x%08X = %d\n", *addr, *addr));
	//			Ddim_Print(("Write address 0x%08X\n"));
			*addr = 0;
		}
		else {
			Ddim_Print(("E:Unknown command.\n"));
		}
	}
	else if (strcmp((const char *)argv[1], "master") == 0) {
		if (strcmp((const char *)argv[2], "w") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				// [command] immxic master w set P1 P2
				//           P1: Target self->unit number. (0-6)
				//           P2: W arbiter (0:W1, 1:W2, 2:W3, 3:W4)
				self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
				// Get parameter for Im_MXIC_Set_Master_W_Arbiter function.
				self->result = ct_im_mxic_create_master_w_arbiter_param( self->unit, &self->wSlotStatus );
				if ( self->result == DriverCommon_D_DDIM_OK ) {
					// Execute function.
					self->result = Im_MXIC_Set_Master_W_Arbiter( self->unit,
							(E_IM_MXIC_W_ARBITER)atoi((const char *)argv[5]), &self->wSlotStatus );
					if (self->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("Im_MXIC_Set_Master_W_Arbiter OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_Master_W_Arbiter NG. self->result=0x%X\n", self->result));
					}
				}
				else {
					Ddim_Print(("E:Command parameter error.\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic master w get P1
				//           P1: Target self->unit number. (0-6)
				//           P2: W arbiter (0:W1, 1:W2, 2:W3, 3:W4)
				self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
				self->result = Im_MXIC_Get_Master_W_Arbiter( self->unit,
						(E_IM_MXIC_W_ARBITER)atoi((const char *)argv[5]), &self->wSlotStatus );
				if ( self->result == DriverCommon_D_DDIM_OK ) {
					ct_im_mxic_print_w_arbiter_assign(  &self->wSlotStatus );
					Ddim_Print(("Im_MXIC_Get_Master_W_Arbiter OK.\n"));
				}
				else {
					Ddim_Print(("E:Im_MXIC_Get_Master_W_Arbiter NG. self->result=0x%X\n", self->result));
				}
			}
			else {
				Ddim_Print(("E:Unknown command.\n"));
			}
		}
		else if (strcmp((const char *)argv[2], "r") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				// [command] immxic master r set P1 P2
				//           P1: Target self->unit number. (0-6)
				//           P2: R arbiter (0:R1, 1:R2, 2:R3, 3:R4)
				self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
				// Get parameter for Im_MXIC_Set_Master_R_Arbiter function.
				self->result = ct_im_mxic_create_master_r_arbiter_param( self->unit, &self->rSlotStatus );
				if ( self->result == DriverCommon_D_DDIM_OK ) {
					// Execute function.
					self->result = Im_MXIC_Set_Master_R_Arbiter( self->unit,
							(E_IM_MXIC_R_ARBITER)atoi((const char *)argv[5]), &self->rSlotStatus );
					if ( self->result == DriverCommon_D_DDIM_OK ) {
						Ddim_Print(("Im_MXIC_Set_Master_R_Arbiter OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_Master_R_Arbiter NG. self->result=0x%X\n", self->result));
					}
				}
				else {
					Ddim_Print(("E:Command parameter error.\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic master r get P1 P2
				//           P1: Target self->unit number. (0-6)
				//           P2: R arbiter (0:R1, 1:R2, 2:R3, 3:R4)
				self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
				self->result = Im_MXIC_Get_Master_R_Arbiter( self->unit,
						(E_IM_MXIC_R_ARBITER)atoi((const char *)argv[5]), &self->rSlotStatus );
				if ( self->result == DriverCommon_D_DDIM_OK ) {
					ct_im_mxic_print_r_arbiter_assign( &self->rSlotStatus);
					Ddim_Print(("Im_MXIC_Get_Master_R_Arbiter OK.\n"));
				}
				else {
					Ddim_Print(("E:Im_MXIC_Get_Master_R_Arbiter NG. self->result=0x%X\n", self->result));
				}
			}
			else {
				Ddim_Print(("E:Unknown command.\n"));
			}
		}
		else if (strcmp((const char *)argv[2], "all") == 0) {
			if (strcmp((const char *)argv[3], "set") == 0) {
				// [command] immxic master all set P1
				//           P1: Target self->unit number. (0-6)
				self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
				// Get parameter for Im_MXIC_Set_Master_All_Arbiter function.
				self->result = ct_im_mxic_create_master_all_arbiter_param( self->unit, &allArbiterAssign );
				if ( self->result == DriverCommon_D_DDIM_OK ) {
					// Execute function.
					self->result = Im_MXIC_Set_Master_All_Arbiter( self->unit, &allArbiterAssign );
					if (self->result == DriverCommon_D_DDIM_OK) {
						Ddim_Print(("Im_MXIC_Set_Master_All_Arbiter OK.\n"));
					}
					else {
						Ddim_Print(("E:Im_MXIC_Set_Master_All_Arbiter NG. self->result=0x%X\n", self->result));
					}
				}
				else {
					Ddim_Print(("E:Command parameter error.\n"));
				}
			}
			else if (strcmp((const char *)argv[3], "get") == 0) {
				// [command] immxic master all get P1
				//           P1: Target self->unit number. (0-6)
				self->unit = (E_IM_MXIC_UNIT)atoi((const char *)argv[4]);
				self->result = Im_MXIC_Get_Master_All_Arbiter( self->unit, &allArbiterAssign );
				if ( self->result == DriverCommon_D_DDIM_OK ) {
					ct_im_mxic_print_all_arbiter_assign(  &allArbiterAssign );
					Ddim_Print(("Im_MXIC_Get_Master_All_Arbiter OK.\n"));
				}
				else {
					Ddim_Print(("E:Im_MXIC_Get_Master_All_Arbiter NG. self->result=0x%X\n", self->result));
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

CtImMxicMain1 *ct_im_mxic_main1_new(void) 
{
    CtImMxicMain1 *self = g_object_new(CT_TYPE_IM_MXIC_MAIN1, NULL);
    return self;
}
