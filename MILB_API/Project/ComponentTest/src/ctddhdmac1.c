/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-04
*@author             	:杨升柄
*@brief               	:CtDdHdmac1类
*@rely                		:klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/
#include "stdlib.h"
#include "string.h"
#include "dd_hdmac1.h"
#include "ct_dd_hdmac1.h"
#include "dd_gic.h"
#include "ddim_user_custom.h"
#include <string.h>
#include "ctddhdmac1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdHdmac1, ct_dd_hdmac1);
#define CT_DD_HDMAC1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdHdmac1Private,CT_TYPE_DD_HDMAC1))


struct _CtDdHdmac1Private
{
};

/*
 * DECLS
 */
static void ctHdmac1Callback( void );
static kint32 ctHdmac1SetIs(CtDdHdmac1 *self, kuchar ch, kchar* is );
static kint ctHdmac1Process(kuchar num);

static void ct_dd_hdmac1_constructor(CtDdHdmac1 *self) 
{
	self->size = 0;
}

static void ct_dd_hdmac1_destructor(CtDdHdmac1 *self) 
{
}

static void ctHdmac1Callback( void )
{
	Ddim_Print(("HDMAC1 Callback\n"));
}

/*
 * IMPL
 */
static kint32 ctHdmac1SetIs(CtDdHdmac1 *self, kuchar ch, kchar* is )
{
	kint32 ret = D_DDIM_OK;

	// Set IS
	if (strcmp(is, "soft") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_SOFT;
	}else if (strcmp(is, "dreq_h") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_DREQ_H;
	}else if (strcmp(is, "dreq_l") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_DREQ_L;
	}else if (strcmp(is, "idreq_0") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_0;
	}else if (strcmp(is, "idreq_1") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_1;
	}else if (strcmp(is, "idreq_2") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_2;
	}else if (strcmp(is, "idreq_3") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_3;
	}else if (strcmp(is, "idreq_4") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_4;
	}else if (strcmp(is, "idreq_5") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_5;
	}else if (strcmp(is, "idreq_6") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_6;
	}else if (strcmp(is, "idreq_7") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_7;
	}else if (strcmp(is, "idreq_8") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_8;
	}else if (strcmp(is, "idreq_9") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_9;
	}else if (strcmp(is, "idreq_10") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_10;
	}else if (strcmp(is, "idreq_11") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_11;
	}else if (strcmp(is, "idreq_12") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_12;
	}else if (strcmp(is, "idreq_13") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_13;
	}else if (strcmp(is, "idreq_14") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_14;
	}else if (strcmp(is, "idreq_15") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_15;
	}else if (strcmp(is, "idreq_16") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_16;
	}else if (strcmp(is, "idreq_17") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_17;
	}else if (strcmp(is, "idreq_18") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_18;
	}else if (strcmp(is, "idreq_19") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_19;
	}else if (strcmp(is, "idreq_20") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_20;
	}else if (strcmp(is, "idreq_21") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_21;
	}else if (strcmp(is, "idreq_22") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_22;
	}else if (strcmp(is, "idreq_23") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_23;
	}else if (strcmp(is, "idreq_24") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_24;
	}else if (strcmp(is, "idreq_25") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_25;
	}else if (strcmp(is, "idreq_26") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_26;
	}else if (strcmp(is, "idreq_27") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_27;
	}else if (strcmp(is, "idreq_28") == 0) {
		self->gHdmac1CtrlTrns[ch].mode.input_sel = D_DD_HDMAC1_IS_IDREQ_28;
	}else
	{
		Ddim_Print(("Parameter ERR. Input Select \n"));
		ret = D_DDIM_INPUT_PARAM_ERROR;
	}
	return ret;
}

static kint ctHdmac1Process(kuchar num)
{
#if 1
	kint32                 						ret;
	kuint32               				 		waitMode;
	kushort                					status = 0;
	kuchar                						ch;
	kuchar                 					arbType;
	T_DD_HDMAC1_CTRL      		hdmac1Ctrl;
	T_DD_HDMAC1_CTRL_TRNS 	hdmac1CtrlTrns;

	switch (num) {
		// TEST ID 01-01-01
		case 1:
			memset((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, 0x00, CtDdHdmac1_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 0;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC1_CH0_INT,1,D_DD_GIC_PRI30,CtDdHdmac1_CPU_TARGET);
			// rotate
			arbType = D_DD_HDMAC1_ARB_ROTATE;
			waitMode = D_DD_HDMAC1_WAITMODE_CPU;
			// clear
			hdmac1Ctrl.config_a.word = 0;

			hdmac1Ctrl.config_a.bit.is = D_DD_HDMAC1_IS_SOFT;
			hdmac1Ctrl.config_a.bit.bt = D_DD_HDMAC1_BT_NORMAL;
			hdmac1Ctrl.config_a.bit.bc = 0x0F;
			hdmac1Ctrl.config_a.bit.tc = ((CtDdHdmac1_AUTO_TEST_SIZE / 16) - 1);
			// clear
			hdmac1Ctrl.config_b.word = 0;

			hdmac1Ctrl.config_b.bit.ms = D_DD_HDMAC1_MS_BLK;
			hdmac1Ctrl.config_b.bit.tw = D_DD_HDMAC1_TW_BYTE;
			hdmac1Ctrl.config_b.bit.fs = D_DD_HDMAC1_FS_INCR;
			hdmac1Ctrl.config_b.bit.fd = D_DD_HDMAC1_FD_INCR;
			hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_DISABLE;
			hdmac1Ctrl.config_b.bit.rs = D_DD_HDMAC1_RS_DISABLE;
			hdmac1Ctrl.config_b.bit.rd = D_DD_HDMAC1_RD_DISABLE;

			hdmac1Ctrl.src_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
			hdmac1Ctrl.dst_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
			hdmac1Ctrl.int_handler = 0;

			ret = Dd_HDMAC1_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC1 Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC1_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC1_Ctrl_Common(ch, &hdmac1Ctrl);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC1_Start_Sync(ch, &status, waitMode);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Start Sync ERR\n"));
					break;
				}
				break;
			}
			ret = Dd_HDMAC1_Close(ch);
			if (ret != 0) {
				Ddim_Print(("HDMAC1 Close ERR\n"));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, (void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, CtDdHdmac1_AUTO_TEST_SIZE)));
			break;

		// TEST ID 01-01-02
		case 2:
			memset((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, 0x00, CtDdHdmac1_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 1;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC1_CH1_INT,1,D_DD_GIC_PRI30,CtDdHdmac1_CPU_TARGET);
			// fix
			arbType = D_DD_HDMAC1_ARB_FIX;
			waitMode = D_DD_HDMAC1_WAITMODE_EVENT;
			// clear
			hdmac1Ctrl.config_a.word = 0;

			hdmac1Ctrl.config_a.bit.is = D_DD_HDMAC1_IS_SOFT;
			hdmac1Ctrl.config_a.bit.bt = D_DD_HDMAC1_BT_NORMAL;
			hdmac1Ctrl.config_a.bit.bc = 0x0F;
			hdmac1Ctrl.config_a.bit.tc = ((CtDdHdmac1_AUTO_TEST_SIZE / 16 / 2) - 1);
			// clear
			hdmac1Ctrl.config_b.word = 0;

			hdmac1Ctrl.config_b.bit.ms = D_DD_HDMAC1_MS_BURST;
			hdmac1Ctrl.config_b.bit.tw = D_DD_HDMAC1_TW_HWORD;
			hdmac1Ctrl.config_b.bit.fs = D_DD_HDMAC1_FS_INCR;
			hdmac1Ctrl.config_b.bit.fd = D_DD_HDMAC1_FD_INCR;
			hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_DISABLE;
			hdmac1Ctrl.config_b.bit.rs = D_DD_HDMAC1_RS_DISABLE;
			hdmac1Ctrl.config_b.bit.rd = D_DD_HDMAC1_RD_DISABLE;

			hdmac1Ctrl.src_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
			hdmac1Ctrl.dst_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
			hdmac1Ctrl.int_handler = 0;

			ret = Dd_HDMAC1_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC1 Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC1_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC1_Ctrl_Common(ch, &hdmac1Ctrl);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC1_Start_Sync(ch, &status, waitMode);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Start Sync ERR\n"));
					break;
				}
				break;
			}
			ret = Dd_HDMAC1_Close(ch);
			if (ret != 0) {
				Ddim_Print(("HDMAC1 Close ERR\n"));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC,
					(void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, CtDdHdmac1_AUTO_TEST_SIZE)));
			break;

		// TEST ID 01-01-03
		case 3:
			memset((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, 0x00, CtDdHdmac1_AUTO_TEST_SIZE);
			memset((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, 0x00, CtDdHdmac1_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 2;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC1_CH2_INT,1,D_DD_GIC_PRI30,CtDdHdmac1_CPU_TARGET);
			// fix
			arbType = D_DD_HDMAC1_ARB_FIX;
			waitMode = D_DD_HDMAC1_WAITMODE_CPU;

			hdmac1CtrlTrns.mode.input_sel = D_DD_HDMAC1_IS_SOFT;
			hdmac1CtrlTrns.mode.mode_sel = D_DD_HDMAC1_MS_BLK;
			hdmac1CtrlTrns.mode.src_fix = D_DD_HDMAC1_FS_INCR;
			hdmac1CtrlTrns.mode.dst_fix = D_DD_HDMAC1_FD_INCR;
			hdmac1CtrlTrns.mode.beat_type = D_DD_HDMAC1_BT_NORMAL;

			hdmac1CtrlTrns.size.trns_width = D_DD_HDMAC1_TW_WORD;
			hdmac1CtrlTrns.size.trns_size = CtDdHdmac1_AUTO_TEST_SIZE;
			hdmac1CtrlTrns.size.src_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
			hdmac1CtrlTrns.size.dst_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;

			hdmac1CtrlTrns.int_handler = 0;

			ret = Dd_HDMAC1_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC1 Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC1_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC1_Ctrl_Trns(ch, &hdmac1CtrlTrns);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC1_Start_Async(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Start Sync ERR\n"));
					break;
				}
				ret = Dd_HDMAC1_Wait_End(ch, &status, waitMode);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Wait ERR\n"));
					break;
				}
				break;
			}
			ret = Dd_HDMAC1_Close(ch);
			if (ret != 0) {
				Ddim_Print(("HDMAC1 Close ERR\n"));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC,
					(void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, CtDdHdmac1_AUTO_TEST_SIZE)));
			break;

		// TEST ID 01-01-04
		case 4:
			memset((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, 0x00, CtDdHdmac1_AUTO_TEST_SIZE);
			memset((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, 0x00, CtDdHdmac1_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 3;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC1_CH3_INT,1,D_DD_GIC_PRI30,CtDdHdmac1_CPU_TARGET);
			// fix
			arbType = D_DD_HDMAC1_ARB_FIX;
			waitMode = D_DD_HDMAC1_WAITMODE_EVENT;

			hdmac1CtrlTrns.mode.input_sel = D_DD_HDMAC1_IS_SOFT;
			hdmac1CtrlTrns.mode.mode_sel = D_DD_HDMAC1_MS_BURST;
			hdmac1CtrlTrns.mode.src_fix = D_DD_HDMAC1_FS_INCR;
			hdmac1CtrlTrns.mode.dst_fix = D_DD_HDMAC1_FD_INCR;
			hdmac1CtrlTrns.mode.beat_type = D_DD_HDMAC1_BT_NORMAL;

			hdmac1CtrlTrns.size.trns_width = D_DD_HDMAC1_TW_BYTE;
			hdmac1CtrlTrns.size.trns_size = CtDdHdmac1_AUTO_TEST_SIZE;
			hdmac1CtrlTrns.size.src_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
			hdmac1CtrlTrns.size.dst_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;

			hdmac1CtrlTrns.int_handler = 0;

			ret = Dd_HDMAC1_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC1 Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC1_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC1_Ctrl_Trns(ch, &hdmac1CtrlTrns);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC1_Start_Async(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Start Sync ERR\n"));
					break;
				}
				ret = Dd_HDMAC1_Wait_End(ch, &status, waitMode);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Wait ERR\n"));
					break;
				}
				break;
			}
			ret = Dd_HDMAC1_Close(ch);
			if (ret != 0) {
				Ddim_Print(("HDMAC1 Close ERR\n"));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC,
					(void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, CtDdHdmac1_AUTO_TEST_SIZE)));
			break;

		case 5:
			memset((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, 0x00, CtDdHdmac1_AUTO_TEST_SIZE);
			memset((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, 0x00, CtDdHdmac1_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 2;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC1_CH2_INT,1,D_DD_GIC_PRI30,CtDdHdmac1_CPU_TARGET);
			// fix
			arbType = D_DD_HDMAC1_ARB_FIX;
			waitMode = D_DD_HDMAC1_WAITMODE_EVENT;
			// clear
			hdmac1Ctrl.config_a.word = 0;

			hdmac1Ctrl.config_a.bit.is = D_DD_HDMAC1_IS_SOFT;
			hdmac1Ctrl.config_a.bit.bt = D_DD_HDMAC1_BT_NORMAL;
			hdmac1Ctrl.config_a.bit.bc = 0x0F;
			hdmac1Ctrl.config_a.bit.tc = ((CtDdHdmac1_AUTO_TEST_SIZE / 16) - 1);
			// clear
			hdmac1Ctrl.config_b.word = 0;

			hdmac1Ctrl.config_b.bit.ms = D_DD_HDMAC1_MS_BLK;
			hdmac1Ctrl.config_b.bit.tw = D_DD_HDMAC1_TW_BYTE;
			hdmac1Ctrl.config_b.bit.fs = D_DD_HDMAC1_FS_INCR;
			hdmac1Ctrl.config_b.bit.fd = D_DD_HDMAC1_FD_INCR;
			hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_DISABLE;
			hdmac1Ctrl.config_b.bit.rs = D_DD_HDMAC1_RS_DISABLE;
			hdmac1Ctrl.config_b.bit.rd = D_DD_HDMAC1_RD_DISABLE;

			hdmac1Ctrl.src_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
			hdmac1Ctrl.dst_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
			hdmac1Ctrl.int_handler = 0;

			ret = Dd_HDMAC1_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC1 Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC1_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC1_Ctrl_Common(ch, &hdmac1Ctrl);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC1_Start_Async(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Start Async ERR\n"));
					break;
				}
				ret = Dd_HDMAC1_Pause(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Pause ERR\n"));
					break;
				}
				break;
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC,
					(void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, CtDdHdmac1_AUTO_TEST_SIZE)));
			break;

		case 6:
			memset((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, 0x00, CtDdHdmac1_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 0;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC1_CH0_INT,1,D_DD_GIC_PRI30,CtDdHdmac1_CPU_TARGET);
			// rotate
			arbType = D_DD_HDMAC1_ARB_ROTATE;
			waitMode = D_DD_HDMAC1_WAITMODE_EVENT;
			// clear
			hdmac1Ctrl.config_a.word = 0;

			hdmac1Ctrl.config_a.bit.is = D_DD_HDMAC1_IS_SOFT;
			hdmac1Ctrl.config_a.bit.bt = D_DD_HDMAC1_BT_NORMAL;
			hdmac1Ctrl.config_a.bit.bc = (16 / 4) - 1;
			hdmac1Ctrl.config_a.bit.tc = ((CtDdHdmac1_AUTO_TEST_SIZE / 16) - 1);
			// clear
			hdmac1Ctrl.config_b.word = 0;

			hdmac1Ctrl.config_b.bit.ms = D_DD_HDMAC1_MS_BLK;
			hdmac1Ctrl.config_b.bit.tw = D_DD_HDMAC1_TW_WORD;
			hdmac1Ctrl.config_b.bit.fs = D_DD_HDMAC1_FS_INCR;
			hdmac1Ctrl.config_b.bit.fd = D_DD_HDMAC1_FD_INCR;
			hdmac1Ctrl.config_b.bit.rc = D_DD_HDMAC1_RC_DISABLE;
			hdmac1Ctrl.config_b.bit.rs = D_DD_HDMAC1_RS_DISABLE;
			hdmac1Ctrl.config_b.bit.rd = D_DD_HDMAC1_RD_DISABLE;

			hdmac1Ctrl.src_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
			hdmac1Ctrl.dst_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
			hdmac1Ctrl.int_handler = 0;

			ret = Dd_HDMAC1_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC1 Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC1_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC1_Ctrl_Common(ch, &hdmac1Ctrl);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC1_Start_Async(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC1 Start Async ERR\n"));
					break;
				}
				Dd_HDMAC1_Stop_All_Ch();
				break;
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac1_AUTO_TEST_ADR_SRC,
					(void*)CtDdHdmac1_AUTO_TEST_ADR_SRC, CtDdHdmac1_AUTO_TEST_SIZE)));
			break;

		default:
			ret = -1;
			break;
	}
	return ret;
#else
	return 0;
#endif
}

/*
 * PUBLIC
 */
void ct_dd_hdmac1_from_main(CtDdHdmac1 *self, kint argc, kchar** argv)
{
	VP_CALLBACK			intHandler;
	kuchar						num;

	if (strcmp(argv[1], "ctrl_cmm_cfga") == 0) {
		// ch number
		self->ch = atoi(argv[2]);

		self->gHdmac1Ctrl[self->ch].config_a.word = 0;

		// Set IS
		self->ret = ctHdmac1SetIs(self, self->ch, argv[3]);
		if( self->ret != D_DDIM_OK ){
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}

		// Set BT
		if (strcmp(argv[4], "normal") == 0) {
			self->gHdmac1Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC1_BT_NORMAL;
		}else if (strcmp(argv[4], "single") == 0) {
			self->gHdmac1Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC1_BT_SINGLE;
		}else if (strcmp(argv[4], "incr") == 0) {
			self->gHdmac1Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC1_BT_INCR;
		}else if (strcmp(argv[4], "wrap4") == 0) {
			self->gHdmac1Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC1_BT_WRAP4;
		}else if (strcmp(argv[4], "incr4") == 0) {
			self->gHdmac1Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC1_BT_INCR4;
		}else if (strcmp(argv[4], "wrap8") == 0) {
			self->gHdmac1Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC1_BT_WRAP8;
		}else if (strcmp(argv[4], "incr8") == 0) {
			self->gHdmac1Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC1_BT_INCR8;
		}else if (strcmp(argv[4], "wrap16") == 0) {
			self->gHdmac1Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC1_BT_WRAP16;
		}else if (strcmp(argv[4], "incr16") == 0) {
			self->gHdmac1Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC1_BT_INCR16;
		}else
		{
			Ddim_Print(("Parameter ERR. P4 \n"));
			return;
		}

		// Set BC
		self->gHdmac1Ctrl[self->ch].config_a.bit.bc = atoi(argv[5]);

		// Set TC
		self->gHdmac1Ctrl[self->ch].config_a.bit.tc = atoi(argv[6]);
	}else if (strcmp(argv[1], "ctrl_trns_md") == 0) {
		// self->ch number
		self->ch = atoi(argv[2]);

		// Set IS
		self->ret = ctHdmac1SetIs(self, self->ch, argv[3]);
		if( self->ret != D_DDIM_OK ){
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}

		// Set MS
		if (strcmp(argv[4], "blk") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.mode_sel = D_DD_HDMAC1_MS_BLK;
		}else if (strcmp(argv[4], "burst") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.mode_sel = D_DD_HDMAC1_MS_BURST;
		}else if (strcmp(argv[4], "demand") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.mode_sel = D_DD_HDMAC1_MS_DEMAND;
		}else
		{
			Ddim_Print(("Parameter ERR. P4 \n"));
			return;
		}

		// Set FS
		if (strcmp(argv[5], "src_fix") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.src_fix = D_DD_HDMAC1_FS_FIX;
		}else if (strcmp(argv[5], "src_incr") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.src_fix = D_DD_HDMAC1_FS_INCR;
		}else
		{
			Ddim_Print(("Parameter ERR. P5 \n"));
			return;
		}

		// Set FD
		if (strcmp(argv[6], "dst_fix") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.dst_fix = D_DD_HDMAC1_FD_FIX;
		}else if (strcmp(argv[6], "dst_incr") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.dst_fix = D_DD_HDMAC1_FD_INCR;
		}else
		{
			Ddim_Print(("Parameter ERR. P6 \n"));
			return;
		}

		// Set BT
		if (strcmp(argv[7], "normal") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC1_BT_NORMAL;
		}else if (strcmp(argv[7], "single") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC1_BT_SINGLE;
		}else if (strcmp(argv[7], "incr") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC1_BT_INCR;
		}else if (strcmp(argv[7], "wrap4") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC1_BT_WRAP4;
		}else if (strcmp(argv[7], "incr4") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC1_BT_INCR4;
		}else if (strcmp(argv[7], "wrap8") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC1_BT_WRAP8;
		}else if (strcmp(argv[7], "incr8") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC1_BT_INCR8;
		}else if (strcmp(argv[7], "wrap16") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC1_BT_WRAP16;
		}else if (strcmp(argv[7], "incr16") == 0) {
			self->gHdmac1CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC1_BT_INCR16;
		}else
		{
			Ddim_Print(("Parameter ERR. P7 \n"));
			return;
		}
	}else if (strcmp(argv[1], "auto") == 0) {
		// self->ch number
		num = atoi(argv[2]);

		self->ret = ctHdmac1Process(num);
		if (self->ret == 0) {
			Ddim_Print(("ctHdmac1Process OK\n"));
		}else
		{
			Ddim_Print(("ctHdmac1Process ERR. ret=0x%x\n", self->ret));
		}
	}else if (strcmp(argv[1], "ctrl_cmm") == 0) {
		// self->ch number
		self->ch = atoi(argv[2]);

		self->gHdmac1Ctrl[self->ch].int_handler = ctHdmac1Callback;

		self->gHdmac1Ctrl[self->ch].src_addr = strtoul(argv[3], &self->endstr, 16);

		self->gHdmac1Ctrl[self->ch].dst_addr = strtoul(argv[4], &self->endstr, 16);

		self->ret = Dd_HDMAC1_Ctrl_Common(self->ch, &self->gHdmac1Ctrl[self->ch]);
		if (self->ret == 0) {
			Ddim_Print(("HDMAC1 Ctrl_Common OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Ctrl_Common ERR. ret=0x%x\n", self->ret));
		}
	}else if (strcmp(argv[1], "ctrl_trns") == 0) {
		// self->ch number
		self->ch = atoi(argv[2]);

		self->gHdmac1CtrlTrns[self->ch].int_handler = ctHdmac1Callback;

		self->ret = Dd_HDMAC1_Ctrl_Trns(self->ch, &self->gHdmac1CtrlTrns[self->ch]);
		if (self->ret == 0) {
			Ddim_Print(("HDMAC1 Ctrl_Trns OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Ctrl_Trns ERR. ret=0x%x\n", self->ret));
		}
	}else if (strcmp(argv[1], "int_set") == 0) {
		// self->ch number
		self->ch = atoi(argv[2]);

		intHandler = ctHdmac1Callback;

		Dd_HDMAC1_Set_Int_Handler(self->ch, intHandler);
	}else if (strcmp(argv[1], "sdram_async") == 0) {
		// self->ch number
		self->ch = atoi(argv[2]);

		self->srcAddr = strtoul(argv[3], &self->endstr, 16);
		self->dstAddr = strtoul(argv[4], &self->endstr, 16);
		self->size = atoi(argv[5]);
		intHandler = ctHdmac1Callback;

		self->ret = Dd_HDMAC1_Copy_SDRAM_Async(self->ch, self->srcAddr, self->dstAddr, self->size, intHandler);
		if (self->ret == 0) {
			Ddim_Print(("HDMAC1 Util Copy Async. OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Util Copy Async. ERR. ret=0x%x\n", self->ret));
		}
	}else if (strcmp(argv[1], "err") == 0){
		T_DD_HDMAC1_CTRL      		hdmac1Ctrl;
		T_DD_HDMAC1_CTRL_TRNS 	hdmac1CtrlTrns;
		T_DD_HDMAC1_TRNS_SIZE 	hdmac1TrnsSize;
		kushort 									status;

		hdmac1CtrlTrns.mode.input_sel = D_DD_HDMAC1_IS_SOFT;
		hdmac1CtrlTrns.mode.mode_sel = D_DD_HDMAC1_MS_BLK;
		hdmac1CtrlTrns.mode.src_fix = D_DD_HDMAC1_FS_INCR;
		hdmac1CtrlTrns.mode.dst_fix = D_DD_HDMAC1_FD_INCR;
		hdmac1CtrlTrns.mode.beat_type = D_DD_HDMAC1_BT_NORMAL;
		hdmac1CtrlTrns.size.trns_width = D_DD_HDMAC1_TW_WORD;
		hdmac1CtrlTrns.size.trns_size = CtDdHdmac1_AUTO_TEST_SIZE;
		hdmac1CtrlTrns.size.src_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
		hdmac1CtrlTrns.size.dst_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
		hdmac1CtrlTrns.int_handler = 0;

		hdmac1TrnsSize.trns_width = D_DD_HDMAC1_TW_BYTE;
		hdmac1TrnsSize.trns_size = CtDdHdmac1_AUTO_TEST_SIZE;
		hdmac1TrnsSize.src_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;
		hdmac1TrnsSize.dst_addr = CtDdHdmac1_AUTO_TEST_ADR_SRC;

		self->ret = Dd_HDMAC1_Open(D_DD_HDMAC1_CH_NUM_MAX, D_DDIM_USER_SEM_WAIT_POL);
		Ddim_Print(("Dd_HDMAC1_Open(): Channel number is illegal. ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Close(D_DD_HDMAC1_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC1_Close(): Channel number is illegal. ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Ctrl_Common(D_DD_HDMAC1_CH_NUM_MAX, &hdmac1Ctrl);
		Ddim_Print(("Dd_HDMAC1_Ctrl_Common(): Channel number is illegal. ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Ctrl_Common(0, NULL);
		Ddim_Print(("Dd_HDMAC1_Ctrl_Common(): ctrl is NULL. ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Ctrl_Trns(D_DD_HDMAC1_CH_NUM_MAX, &hdmac1CtrlTrns);
		Ddim_Print(("Dd_HDMAC1_Ctrl_Trns(): Channel number is illegal. ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Ctrl_Trns(0, NULL);
		Ddim_Print(("Dd_HDMAC1_Ctrl_Trns(): ctrl is NULL. ret=0x%x\n", self->ret));

		// BC over test (Ctrl_Trns)
		// 65536*4*17
		hdmac1CtrlTrns.size.trns_size = 0x00440000;
		self->ret = Dd_HDMAC1_Ctrl_Trns(0, &hdmac1CtrlTrns);
		Ddim_Print(("Dd_HDMAC1_Ctrl_Trns(): BC is over. ret=0x%x\n", self->ret));

		// BC over test in Demand mode (Ctrl_Trns)
		hdmac1CtrlTrns.mode.mode_sel  = D_DD_HDMAC1_MS_DEMAND;
		// 65536*4*2
		hdmac1CtrlTrns.size.trns_size = 0x00080000;
		self->ret = Dd_HDMAC1_Ctrl_Trns(0, &hdmac1CtrlTrns);
		Ddim_Print(("Dd_HDMAC1_Ctrl_Trns(): demand transfer and BC is not 0. ret=0x%x\n", self->ret));


		self->ret = Dd_HDMAC1_Set_Trns_Size(D_DD_HDMAC1_CH_NUM_MAX, &hdmac1TrnsSize);
		Ddim_Print(("Dd_HDMAC1_Set_Trns_Size(): Channel number is illegal. ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Set_Trns_Size(0, NULL);
		Ddim_Print(("Dd_HDMAC1_Set_Trns_Size(): trns_size is NULL. ret=0x%x\n", self->ret));

		// BC over test (Set_Trns_Size)
		hdmac1CtrlTrns.mode.mode_sel  = D_DD_HDMAC1_MS_BLK;
		// 65536*1*17
		hdmac1CtrlTrns.size.trns_size = 0x00110000;
		self->ret = Dd_HDMAC1_Ctrl_Trns(0, &hdmac1CtrlTrns);
		hdmac1TrnsSize.trns_size = 0x00001000;
		self->ret = Dd_HDMAC1_Set_Trns_Size(0, &hdmac1TrnsSize);
		Ddim_Print(("Dd_HDMAC1_Set_Trns_Size(): BC is over. ret=0x%x\n", self->ret));

		// BC over test in Demand mode (Set_Trns_Size)
		hdmac1CtrlTrns.mode.mode_sel = D_DD_HDMAC1_MS_DEMAND;
		hdmac1CtrlTrns.size.trns_size = 0x00001000;
		self->ret = Dd_HDMAC1_Ctrl_Trns(0, &hdmac1CtrlTrns);
		// 65536*1*2
		hdmac1TrnsSize.trns_size = 0x00020000;
		self->ret = Dd_HDMAC1_Set_Trns_Size(0, &hdmac1TrnsSize);
		Ddim_Print(("Dd_HDMAC1_Set_Trns_Size(): demand transfer and BC is not 0. ret=0x%x\n", self->ret));


		self->ret = Dd_HDMAC1_Start_Sync(D_DD_HDMAC1_CH_NUM_MAX, &status, D_DD_HDMAC1_WAITMODE_CPU);
		Ddim_Print(("Dd_HDMAC1_Start_Sync(): Channel number is illegal. ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Start_Sync(0, NULL, D_DD_HDMAC1_WAITMODE_CPU);
		Ddim_Print(("Dd_HDMAC1_Start_Sync(): status is NULL. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Start_Sync(0, &status, D_DD_HDMAC1_WAITMODE_EVENT+1);
		Ddim_Print(("Dd_HDMAC1_Start_Sync(): wait_mode is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Start_Async(D_DD_HDMAC1_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC1_Start_Async(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Stop(D_DD_HDMAC1_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC1_Stop(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Pause(D_DD_HDMAC1_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC1_Pause(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Resume(D_DD_HDMAC1_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC1_Resume(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Set_Wait_Time(D_DD_HDMAC1_CH_NUM_MAX, D_DDIM_USER_SEM_WAIT_POL);
		Ddim_Print(("Dd_HDMAC1_Set_Wait_Time(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Set_Wait_Time(0, -2);
		Ddim_Print(("Dd_HDMAC1_Set_Wait_Time(): wait_time is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Wait_End(D_DD_HDMAC1_CH_NUM_MAX, &status, D_DD_HDMAC1_WAITMODE_CPU);
		Ddim_Print(("Dd_HDMAC1_Wait_End(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Wait_End(0, NULL, D_DD_HDMAC1_WAITMODE_CPU);
		Ddim_Print(("Dd_HDMAC1_Wait_End(): status is NULL. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Wait_End(0, &status, D_DD_HDMAC1_WAITMODE_EVENT+1);
		Ddim_Print(("Dd_HDMAC1_Wait_End(): wait_mode is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Clear_Status(D_DD_HDMAC1_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC1_Clear_Status(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Get_Status(D_DD_HDMAC1_CH_NUM_MAX, &status);
		Ddim_Print(("Dd_HDMAC1_Get_Status(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Get_Status(0, NULL);
		Ddim_Print(("Dd_HDMAC1_Get_Status(): status is NULL. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Get_Trns_Size(D_DD_HDMAC1_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC1_Get_Trns_Size(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Get_Remain_Trns_Size(D_DD_HDMAC1_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC1_Get_Remain_Trns_Size(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Get_Total_Trns_Size(D_DD_HDMAC1_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC1_Get_Total_Trns_Size(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Get_Src_Addr(D_DD_HDMAC1_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC1_Get_Src_Addr(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Get_Dst_Addr(D_DD_HDMAC1_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC1_Get_Dst_Addr(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Set_Source_Protect(D_DD_HDMAC1_CH_NUM_MAX, 0);
		Ddim_Print(("Dd_HDMAC1_Set_Source_Protect(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Set_Destination_Protect(D_DD_HDMAC1_CH_NUM_MAX, 0);
		Ddim_Print(("Dd_HDMAC1_Set_Destination_Protect(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Set_Arbitration(D_DD_HDMAC1_ARB_ROTATE+1);
		Ddim_Print(("Dd_HDMAC1_Set_Arbitration(): arbitration is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Get_Arbitration(NULL);
		Ddim_Print(("Dd_HDMAC1_Get_Arbitration(): arbitration is NULL. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Copy_SDRAM_Sync(D_DD_HDMAC1_CH_NUM_MAX, 1, 2, 1, D_DD_HDMAC1_WAITMODE_EVENT);
		Ddim_Print(("Dd_HDMAC1_Copy_SDRAM_Sync(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Copy_SDRAM_Sync(0, 0, 2, 1, D_DD_HDMAC1_WAITMODE_EVENT);
		Ddim_Print(("Dd_HDMAC1_Copy_SDRAM_Sync(): src_addr is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Copy_SDRAM_Sync(0, 1, 0, 1, D_DD_HDMAC1_WAITMODE_EVENT);
		Ddim_Print(("Dd_HDMAC1_Copy_SDRAM_Sync(): dst_addr is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Copy_SDRAM_Sync(0, 1, 2, 0, D_DD_HDMAC1_WAITMODE_EVENT);
		Ddim_Print(("Dd_HDMAC1_Copy_SDRAM_Sync(): size is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Copy_SDRAM_Sync(0, 1, 2, 1, D_DD_HDMAC1_WAITMODE_EVENT+1);
		Ddim_Print(("Dd_HDMAC1_Copy_SDRAM_Sync(): wait_mode is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Copy_SDRAM_Async(D_DD_HDMAC1_CH_NUM_MAX, 1, 2, 1, ctHdmac1Callback);
		Ddim_Print(("Dd_HDMAC1_Copy_SDRAM_Async(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Copy_SDRAM_Async(0, 0, 2, 1, ctHdmac1Callback);
		Ddim_Print(("Dd_HDMAC1_Copy_SDRAM_Async(): src_addr is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Copy_SDRAM_Async(0, 1, 0, 1, ctHdmac1Callback);
		Ddim_Print(("Dd_HDMAC1_Copy_SDRAM_Async(): dst_addr is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC1_Copy_SDRAM_Async(0, 1, 2, 0, ctHdmac1Callback);
		Ddim_Print(("Dd_HDMAC1_Copy_SDRAM_Async(): size is illegal. self->ret=0x%x\n", self->ret));
	}
}

CtDdHdmac1* ct_dd_hdmac1_new(void) 
{
    CtDdHdmac1 *self = k_object_new_with_private(CT_TYPE_DD_HDMAC1, sizeof(CtDdHdmac1Private));
    return self;
}
