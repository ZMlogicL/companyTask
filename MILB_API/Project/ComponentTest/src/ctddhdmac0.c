/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :杨升柄
*@brief               :CtDdHdmac0类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/
#include "stdlib.h"
#include "string.h"
#include "dd_hdmac0.h"
#include "ct_dd_hdmac0.h"
#include "dd_gic.h"
#include "ddim_user_custom.h"
#include <string.h>
#include "ctddhdmac0.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdHdmac0, ct_dd_hdmac0);
#define CT_DD_HDMAC0_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdHdmac0Private,CT_TYPE_DD_HDMAC0))

struct _CtDdHdmac0Private
{
};

/*
 * DECLS
 */
static kint32 	ctHdmac0SetIs(CtDdHdmac0 *self, kuchar ch, kchar* is );
static kint 		ctHdmac0Process(kuchar num);

static void ct_dd_hdmac0_constructor(CtDdHdmac0 *self) 
{
	self->size = 0;
}

static void ct_dd_hdmac0_destructor(CtDdHdmac0 *self) 
{
}

/*
 * IMPL
 */
static kint32 ctHdmac0SetIs(CtDdHdmac0 *self, kuchar ch, kchar* is )
{
	kint32 ret = D_DDIM_OK;

	// Set IS
	if (strcmp(is, "soft") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_SOFT;
	}else if (strcmp(is, "dreq_h") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_DREQ_H;
	}else if (strcmp(is, "dreq_l") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_DREQ_L;
	}else if (strcmp(is, "idreq_0") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_0;
	}else if (strcmp(is, "idreq_1") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_1;
	}else if (strcmp(is, "idreq_2") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_2;
	}else if (strcmp(is, "idreq_3") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_3;
	}else if (strcmp(is, "idreq_4") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_4;
	}else if (strcmp(is, "idreq_5") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_5;
	}else if (strcmp(is, "idreq_6") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_6;
	}else if (strcmp(is, "idreq_7") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_7;
	}else if (strcmp(is, "idreq_8") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_8;
	}else if (strcmp(is, "idreq_9") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_9;
	}else if (strcmp(is, "idreq_10") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_10;
	}else if (strcmp(is, "idreq_11") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_11;
	}else if (strcmp(is, "idreq_12") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_12;
	}else if (strcmp(is, "idreq_13") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_13;
	}else if (strcmp(is, "idreq_14") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_14;
	}else if (strcmp(is, "idreq_15") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_15;
	}else if (strcmp(is, "idreq_16") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_16;
	}else if (strcmp(is, "idreq_17") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_17;
	}else if (strcmp(is, "idreq_18") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_18;
	}else if (strcmp(is, "idreq_19") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_19;
	}else if (strcmp(is, "idreq_20") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_20;
	}else if (strcmp(is, "idreq_21") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_21;
	}else if (strcmp(is, "idreq_22") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_22;
	}else if (strcmp(is, "idreq_23") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_23;
	}else if (strcmp(is, "idreq_24") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_24;
	}else if (strcmp(is, "idreq_25") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_25;
	}else if (strcmp(is, "idreq_26") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_26;
	}else if (strcmp(is, "idreq_27") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_27;
	}else if (strcmp(is, "idreq_28") == 0) {
		self->gHdmac0CtrlTrns[ch].mode.input_sel = D_DD_HDMAC0_IS_IDREQ_28;
	}else
	{
		Ddim_Print(("Parameter ERR. Input Select \n"));
		ret = D_DDIM_INPUT_PARAM_ERROR;
	}
	return ret;
}

static kint ctHdmac0Process(kuchar num)
{
#if 1
	kint32                 						ret;
	kuint32               				 		waitMode;
	kushort              			  			status = 0;
	kuchar                 					ch;
	kuchar                 					arbType;
	T_DD_HDMAC0_CTRL     		hdmac0Ctrl;
	T_DD_HDMAC0_CTRL_TRNS 	hdmac0CtrlTrns;

	switch (num) {
		// TEST ID 01-01-01
		case 1:
			memset((void*)CtDdHdmac0_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac0_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 0;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH0_INT,1,D_DD_GIC_PRI30,CtDdHdmac0_CPU_TARGET);
			// rotate
			arbType = D_DD_HDMAC0_ARB_ROTATE;
			waitMode = D_DD_HDMAC0_WAITMODE_CPU;
			// clear
			hdmac0Ctrl.config_a.word = 0;

			hdmac0Ctrl.config_a.bit.is = D_DD_HDMAC0_IS_SOFT;
			hdmac0Ctrl.config_a.bit.bt = D_DD_HDMAC0_BT_NORMAL;
			hdmac0Ctrl.config_a.bit.bc = 0x0F;
			hdmac0Ctrl.config_a.bit.tc = ((CtDdHdmac0_AUTO_TEST_SIZE / 16) - 1);
			// clear
			hdmac0Ctrl.config_b.word = 0;

			hdmac0Ctrl.config_b.bit.ms = D_DD_HDMAC0_MS_BLK;
			hdmac0Ctrl.config_b.bit.tw = D_DD_HDMAC0_TW_BYTE;
			hdmac0Ctrl.config_b.bit.fs = D_DD_HDMAC0_FS_INCR;
			hdmac0Ctrl.config_b.bit.fd = D_DD_HDMAC0_FD_INCR;
			hdmac0Ctrl.config_b.bit.rc = D_DD_HDMAC0_RC_DISABLE;
			hdmac0Ctrl.config_b.bit.rs = D_DD_HDMAC0_RS_DISABLE;
			hdmac0Ctrl.config_b.bit.rd = D_DD_HDMAC0_RD_DISABLE;

			hdmac0Ctrl.src_addr = CtDdHdmac0_AUTO_TEST_ADR_SRC;
			hdmac0Ctrl.dst_addr = CtDdHdmac0_AUTO_TEST_ADR_DST;
			hdmac0Ctrl.int_handler = 0;

			ret = Dd_HDMAC0_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC0 Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC0_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC0_Ctrl_Common(ch, &hdmac0Ctrl);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC0_Start_Sync(ch, &status, waitMode);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Start Sync ERR\n"));
					break;
				}
				break;
			}
			ret = Dd_HDMAC0_Close(ch);
			if (ret != 0) {
				Ddim_Print(("HDMAC0 Close ERR\n"));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac0_AUTO_TEST_ADR_SRC,
					(void*)CtDdHdmac0_AUTO_TEST_ADR_DST, CtDdHdmac0_AUTO_TEST_SIZE)));
			break;

		// TEST ID 01-01-02
		case 2:
			memset((void*)CtDdHdmac0_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac0_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 1;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH1_INT,1,D_DD_GIC_PRI30,CtDdHdmac0_CPU_TARGET);
			// fix
			arbType = D_DD_HDMAC0_ARB_FIX;
			waitMode = D_DD_HDMAC0_WAITMODE_EVENT;
			// clear
			hdmac0Ctrl.config_a.word = 0;

			hdmac0Ctrl.config_a.bit.is = D_DD_HDMAC0_IS_SOFT;
			hdmac0Ctrl.config_a.bit.bt = D_DD_HDMAC0_BT_NORMAL;
			hdmac0Ctrl.config_a.bit.bc = 0x0F;
			hdmac0Ctrl.config_a.bit.tc = ((CtDdHdmac0_AUTO_TEST_SIZE / 16 / 2) - 1);
			// clear
			hdmac0Ctrl.config_b.word = 0;

			hdmac0Ctrl.config_b.bit.ms = D_DD_HDMAC0_MS_BURST;
			hdmac0Ctrl.config_b.bit.tw = D_DD_HDMAC0_TW_HWORD;
			hdmac0Ctrl.config_b.bit.fs = D_DD_HDMAC0_FS_INCR;
			hdmac0Ctrl.config_b.bit.fd = D_DD_HDMAC0_FD_INCR;
			hdmac0Ctrl.config_b.bit.rc = D_DD_HDMAC0_RC_DISABLE;
			hdmac0Ctrl.config_b.bit.rs = D_DD_HDMAC0_RS_DISABLE;
			hdmac0Ctrl.config_b.bit.rd = D_DD_HDMAC0_RD_DISABLE;

			hdmac0Ctrl.src_addr = CtDdHdmac0_AUTO_TEST_ADR_SRC;
			hdmac0Ctrl.dst_addr = CtDdHdmac0_AUTO_TEST_ADR_DST;
			hdmac0Ctrl.int_handler = 0;

			ret = Dd_HDMAC0_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC0 Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC0_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC0_Ctrl_Common(ch, &hdmac0Ctrl);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC0_Start_Sync(ch, &status, waitMode);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Start Sync ERR\n"));
					break;
				}
				break;
			}
			ret = Dd_HDMAC0_Close(ch);
			if (ret != 0) {
				Ddim_Print(("HDMAC0 Close ERR\n"));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac0_AUTO_TEST_ADR_SRC,
					(void*)CtDdHdmac0_AUTO_TEST_ADR_DST, CtDdHdmac0_AUTO_TEST_SIZE)));
			break;

		// TEST ID 01-01-03
		case 3:
			memset((void*)CtDdHdmac0_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac0_AUTO_TEST_SIZE);
			memset((void*)CtDdHdmac0_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac0_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 2;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH2_INT,1,D_DD_GIC_PRI30,CtDdHdmac0_CPU_TARGET);
			// fix
			arbType = D_DD_HDMAC0_ARB_FIX;
			waitMode = D_DD_HDMAC0_WAITMODE_CPU;

			hdmac0CtrlTrns.mode.input_sel = D_DD_HDMAC0_IS_SOFT;
			hdmac0CtrlTrns.mode.mode_sel = D_DD_HDMAC0_MS_BLK;
			hdmac0CtrlTrns.mode.src_fix = D_DD_HDMAC0_FS_INCR;
			hdmac0CtrlTrns.mode.dst_fix = D_DD_HDMAC0_FD_INCR;
			hdmac0CtrlTrns.mode.beat_type = D_DD_HDMAC0_BT_NORMAL;

			hdmac0CtrlTrns.size.trns_width = D_DD_HDMAC0_TW_WORD;
			hdmac0CtrlTrns.size.trns_size = CtDdHdmac0_AUTO_TEST_SIZE;
			hdmac0CtrlTrns.size.src_addr = CtDdHdmac0_AUTO_TEST_ADR_SRC;
			hdmac0CtrlTrns.size.dst_addr = CtDdHdmac0_AUTO_TEST_ADR_DST;

			hdmac0CtrlTrns.int_handler = 0;

			ret = Dd_HDMAC0_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC0 Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC0_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC0_Ctrl_Trns(ch, &hdmac0CtrlTrns);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC0_Start_Async(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Start Sync ERR\n"));
					break;
				}
				ret = Dd_HDMAC0_Wait_End(ch, &status, waitMode);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Wait ERR\n"));
					break;
				}
				break;
			}
			ret = Dd_HDMAC0_Close(ch);
			if (ret != 0) {
				Ddim_Print(("HDMAC0 Close ERR\n"));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac0_AUTO_TEST_ADR_SRC,
					(void*)CtDdHdmac0_AUTO_TEST_ADR_DST, CtDdHdmac0_AUTO_TEST_SIZE)));
			break;

		// TEST ID 01-01-04
		case 4:
			memset((void*)CtDdHdmac0_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac0_AUTO_TEST_SIZE);
			memset((void*)CtDdHdmac0_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac0_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 3;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH3_INT,1,D_DD_GIC_PRI30,CtDdHdmac0_CPU_TARGET);
			// fix
			arbType = D_DD_HDMAC0_ARB_FIX;
			waitMode = D_DD_HDMAC0_WAITMODE_EVENT;

			hdmac0CtrlTrns.mode.input_sel = D_DD_HDMAC0_IS_SOFT;
			hdmac0CtrlTrns.mode.mode_sel = D_DD_HDMAC0_MS_BURST;
			hdmac0CtrlTrns.mode.src_fix = D_DD_HDMAC0_FS_INCR;
			hdmac0CtrlTrns.mode.dst_fix = D_DD_HDMAC0_FD_INCR;
			hdmac0CtrlTrns.mode.beat_type = D_DD_HDMAC0_BT_NORMAL;

			hdmac0CtrlTrns.size.trns_width = D_DD_HDMAC0_TW_BYTE;
			hdmac0CtrlTrns.size.trns_size = CtDdHdmac0_AUTO_TEST_SIZE;
			hdmac0CtrlTrns.size.src_addr = CtDdHdmac0_AUTO_TEST_ADR_SRC;
			hdmac0CtrlTrns.size.dst_addr = CtDdHdmac0_AUTO_TEST_ADR_DST;

			hdmac0CtrlTrns.int_handler = 0;

			ret = Dd_HDMAC0_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC0 Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC0_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC0_Ctrl_Trns(ch, &hdmac0CtrlTrns);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC0_Start_Async(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Start Sync ERR\n"));
					break;
				}
				ret = Dd_HDMAC0_Wait_End(ch, &status, waitMode);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Wait ERR\n"));
					break;
				}
				break;
			}
			ret = Dd_HDMAC0_Close(ch);
			if (ret != 0) {
				Ddim_Print(("HDMAC0 Close ERR\n"));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac0_AUTO_TEST_ADR_SRC,
					(void*)CtDdHdmac0_AUTO_TEST_ADR_DST, CtDdHdmac0_AUTO_TEST_SIZE)));
			break;

		case 5:
			memset((void*)CtDdHdmac0_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac0_AUTO_TEST_SIZE);
			memset((void*)CtDdHdmac0_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac0_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 2;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH2_INT,1,D_DD_GIC_PRI30,CtDdHdmac0_CPU_TARGET);
			// fix
			arbType = D_DD_HDMAC0_ARB_FIX;
			waitMode = D_DD_HDMAC0_WAITMODE_EVENT;
			// clear
			hdmac0Ctrl.config_a.word = 0;

			hdmac0Ctrl.config_a.bit.is = D_DD_HDMAC0_IS_SOFT;
			hdmac0Ctrl.config_a.bit.bt = D_DD_HDMAC0_BT_NORMAL;
			hdmac0Ctrl.config_a.bit.bc = 0x0F;
			hdmac0Ctrl.config_a.bit.tc = ((CtDdHdmac0_AUTO_TEST_SIZE / 16) - 1);
			// clear
			hdmac0Ctrl.config_b.word = 0;

			hdmac0Ctrl.config_b.bit.ms = D_DD_HDMAC0_MS_BLK;
			hdmac0Ctrl.config_b.bit.tw = D_DD_HDMAC0_TW_BYTE;
			hdmac0Ctrl.config_b.bit.fs = D_DD_HDMAC0_FS_INCR;
			hdmac0Ctrl.config_b.bit.fd = D_DD_HDMAC0_FD_INCR;
			hdmac0Ctrl.config_b.bit.rc = D_DD_HDMAC0_RC_DISABLE;
			hdmac0Ctrl.config_b.bit.rs = D_DD_HDMAC0_RS_DISABLE;
			hdmac0Ctrl.config_b.bit.rd = D_DD_HDMAC0_RD_DISABLE;

			hdmac0Ctrl.src_addr = CtDdHdmac0_AUTO_TEST_ADR_SRC;
			hdmac0Ctrl.dst_addr = CtDdHdmac0_AUTO_TEST_ADR_DST;
			hdmac0Ctrl.int_handler = 0;

			ret = Dd_HDMAC0_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC0 Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC0_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC0_Ctrl_Common(ch, &hdmac0Ctrl);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC0_Start_Async(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Start Async ERR\n"));
					break;
				}
				ret = Dd_HDMAC0_Pause(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Pause ERR\n"));
					break;
				}
				break;
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac0_AUTO_TEST_ADR_SRC,
					(void*)CtDdHdmac0_AUTO_TEST_ADR_DST, CtDdHdmac0_AUTO_TEST_SIZE)));
			break;

		case 6:
			memset((void*)CtDdHdmac0_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac0_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 0;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH0_INT,1,D_DD_GIC_PRI30,CtDdHdmac0_CPU_TARGET);
			// rotate
			arbType = D_DD_HDMAC0_ARB_ROTATE;
			waitMode = D_DD_HDMAC0_WAITMODE_EVENT;
			// clear
			hdmac0Ctrl.config_a.word = 0;

			hdmac0Ctrl.config_a.bit.is = D_DD_HDMAC0_IS_SOFT;
			hdmac0Ctrl.config_a.bit.bt = D_DD_HDMAC0_BT_NORMAL;
			hdmac0Ctrl.config_a.bit.bc = (16 / 4) - 1;
			hdmac0Ctrl.config_a.bit.tc = ((CtDdHdmac0_AUTO_TEST_SIZE / 16) - 1);
			// clear
			hdmac0Ctrl.config_b.word = 0;

			hdmac0Ctrl.config_b.bit.ms = D_DD_HDMAC0_MS_BLK;
			hdmac0Ctrl.config_b.bit.tw = D_DD_HDMAC0_TW_WORD;
			hdmac0Ctrl.config_b.bit.fs = D_DD_HDMAC0_FS_INCR;
			hdmac0Ctrl.config_b.bit.fd = D_DD_HDMAC0_FD_INCR;
			hdmac0Ctrl.config_b.bit.rc = D_DD_HDMAC0_RC_DISABLE;
			hdmac0Ctrl.config_b.bit.rs = D_DD_HDMAC0_RS_DISABLE;
			hdmac0Ctrl.config_b.bit.rd = D_DD_HDMAC0_RD_DISABLE;

			hdmac0Ctrl.src_addr = CtDdHdmac0_AUTO_TEST_ADR_SRC;
			hdmac0Ctrl.dst_addr = CtDdHdmac0_AUTO_TEST_ADR_DST;
			hdmac0Ctrl.int_handler = 0;

			ret = Dd_HDMAC0_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC0 Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC0_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC0_Ctrl_Common(ch, &hdmac0Ctrl);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC0_Start_Async(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC0 Start Async ERR\n"));
					break;
				}
				Dd_HDMAC0_Stop_All_Ch();
				break;
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac0_AUTO_TEST_ADR_SRC,
					(void*)CtDdHdmac0_AUTO_TEST_ADR_DST, CtDdHdmac0_AUTO_TEST_SIZE)));
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
void ct_hdmac0_callback( void )
{
	Ddim_Print(("HDMAC0 Callback\n"));
}

void ct_dd_hdmac0_from_main(CtDdHdmac0* self, kint argc, kchar** argv)
{
	if (strcmp(argv[1], "ctrl_cmm_cfga") == 0) {
		/* ch number */
		self->ch = atoi(argv[2]);

		self->gHdmac0Ctrl[self->ch].config_a.word = 0;

		// Set IS
		self->ret = ctHdmac0SetIs(self, self->ch, argv[3]);
		if( self->ret != D_DDIM_OK ){
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}

		// Set BT
		if (strcmp(argv[4], "normal") == 0) {
			self->gHdmac0Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC0_BT_NORMAL;
		}else if (strcmp(argv[4], "single") == 0) {
			self->gHdmac0Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC0_BT_SINGLE;
		}else if (strcmp(argv[4], "incr") == 0) {
			self->gHdmac0Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC0_BT_INCR;
		}else if (strcmp(argv[4], "wrap4") == 0) {
			self->gHdmac0Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC0_BT_WRAP4;
		}else if (strcmp(argv[4], "incr4") == 0) {
			self->gHdmac0Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC0_BT_INCR4;
		}else if (strcmp(argv[4], "wrap8") == 0) {
			self->gHdmac0Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC0_BT_WRAP8;
		}else if (strcmp(argv[4], "incr8") == 0) {
			self->gHdmac0Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC0_BT_INCR8;
		}else if (strcmp(argv[4], "wrap16") == 0) {
			self->gHdmac0Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC0_BT_WRAP16;
		}else if (strcmp(argv[4], "incr16") == 0) {
			self->gHdmac0Ctrl[self->ch].config_a.bit.bt = D_DD_HDMAC0_BT_INCR16;
		}
		else {
			Ddim_Print(("Parameter ERR. P4 \n"));
			return;
		}

		// Set BC
		self->gHdmac0Ctrl[self->ch].config_a.bit.bc = atoi(argv[5]);

		// Set TC
		self->gHdmac0Ctrl[self->ch].config_a.bit.tc = atoi(argv[6]);
	}
	else if (strcmp(argv[1], "ctrl_trns_md") == 0) {
		/* self->ch number */
		self->ch = atoi(argv[2]);

		// Set IS
		self->ret = ctHdmac0SetIs(self, self->ch, argv[3]);
		if( self->ret != D_DDIM_OK ){
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}

		// Set MS
		if (strcmp(argv[4], "blk") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.mode_sel = D_DD_HDMAC0_MS_BLK;
		}else if (strcmp(argv[4], "burst") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.mode_sel = D_DD_HDMAC0_MS_BURST;
		}else if (strcmp(argv[4], "demand") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.mode_sel = D_DD_HDMAC0_MS_DEMAND;
		}
		else {
			Ddim_Print(("Parameter ERR. P4 \n"));
			return;
		}

		// Set FS
		if (strcmp(argv[5], "src_fix") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.src_fix = D_DD_HDMAC0_FS_FIX;
		}else if (strcmp(argv[5], "src_incr") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.src_fix = D_DD_HDMAC0_FS_INCR;
		}
		else {
			Ddim_Print(("Parameter ERR. P5 \n"));
			return;
		}

		// Set FD
		if (strcmp(argv[6], "dst_fix") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.dst_fix = D_DD_HDMAC0_FD_FIX;
		}else if (strcmp(argv[6], "dst_incr") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.dst_fix = D_DD_HDMAC0_FD_INCR;
		}
		else {
			Ddim_Print(("Parameter ERR. P6 \n"));
			return;
		}

		// Set BT
		if (strcmp(argv[7], "normal") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC0_BT_NORMAL;
		}else if (strcmp(argv[7], "single") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC0_BT_SINGLE;
		}else if (strcmp(argv[7], "incr") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC0_BT_INCR;
		}else if (strcmp(argv[7], "wrap4") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC0_BT_WRAP4;
		}else if (strcmp(argv[7], "incr4") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC0_BT_INCR4;
		}else if (strcmp(argv[7], "wrap8") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC0_BT_WRAP8;
		}else if (strcmp(argv[7], "incr8") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC0_BT_INCR8;
		}else if (strcmp(argv[7], "wrap16") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC0_BT_WRAP16;
		}else if (strcmp(argv[7], "incr16") == 0) {
			self->gHdmac0CtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC0_BT_INCR16;
		}
		else {
			Ddim_Print(("Parameter ERR. P7 \n"));
			return;
		}
	}
	else if (strcmp(argv[1], "auto") == 0) {
		/* self->ch number */
		self->num = atoi(argv[2]);

		self->ret = ctHdmac0Process(self->num);
		if (self->ret == 0) {
			Ddim_Print(("ctHdmac0Process OK\n"));
		}
		else {
			Ddim_Print(("ctHdmac0Process ERR. ret=0x%x\n", self->ret));
		}
	}
	else if (strcmp(argv[1], "in_audio") == 0) {
		/* self->ch number */
		self->ch = atoi(argv[2]);

		// Set IS
		self->ret = ctHdmac0SetIs(self, self->ch, argv[3]);
		if( self->ret != D_DDIM_OK ){
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}
		self->inputSel = self->gHdmac0CtrlTrns[self->ch].mode.input_sel;

		self->srcAddr = strtoul(argv[4], &self->endstr, 16);
		self->dstAddr = strtoul(argv[5], &self->endstr, 16);
		self->size = atoi(argv[6]);

		self->intHandler = ct_hdmac0_callback;
		/* pgr0539 */
		self->ret = Dd_HDMAC0_Input_Audio_Async(self->ch, self->inputSel,
				self->srcAddr, self->dstAddr, self->size, self->intHandler);
		if (self->ret == 0) {
			Ddim_Print(("HDMAC0 Util Input Audio Async. OK\n"));
		}
		else {
			Ddim_Print(("HDMAC0 Util Input Audio Async. ERR. ret=0x%x\n", self->ret));
		}
	}
	else if (strcmp(argv[1], "out_audio") == 0) {
		/* self->ch number */
		self->ch = atoi(argv[2]);

		// Set IS
		self->ret = ctHdmac0SetIs(self, self->ch, argv[3]);
		if( self->ret != D_DDIM_OK ){
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}
		self->inputSel = self->gHdmac0CtrlTrns[self->ch].mode.input_sel;

		self->srcAddr = strtoul(argv[4], &self->endstr, 16);
		self->dstAddr = strtoul(argv[5], &self->endstr, 16);
		self->size = atoi(argv[6]);

		self->intHandler = ct_hdmac0_callback;
		/* pgr0539 */
		self->ret = Dd_HDMAC0_Output_Audio_Async(self->ch, self->inputSel,
				self->srcAddr, self->dstAddr, self->size, self->intHandler);
		if (self->ret == 0) {
			Ddim_Print(("HDMAC0 Util Output Audio Async. OK\n"));
		}
		else {
			Ddim_Print(("HDMAC0 Util Input Audio Async. ERR. ret=0x%x\n", self->ret));
		}
	}
	if (strcmp(argv[1], "open") == 0) {
		/* self->ch number */
		self->ch = atoi(argv[2]);
		self->waitTime = atoi(argv[3]);

		self->ret = Dd_HDMAC0_Open(self->ch, self->waitTime);
		if (self->ret == 0) {
			Ddim_Print(("HDMAC0 Open OK\n"));
		}
		else {
			Ddim_Print(("HDMAC0 Open ERR. ret=0x%x\n", self->ret));
		}
	}
	else if (strcmp(argv[1], "close") == 0) {
		/* self->ch number */
		self->ch = atoi(argv[2]);

		self->ret = Dd_HDMAC0_Close(self->ch);
		if (self->ret == 0) {
			Ddim_Print(("HDMAC0 Close OK\n"));
		}
		else {
			Ddim_Print(("HDMAC0 Close ERR. ret=0x%x\n", self->ret));
		}
	}
	else if (strcmp(argv[1], "ctrl_cmm") == 0) {
		/* self->ch number */
		self->ch = atoi(argv[2]);

		self->gHdmac0Ctrl[self->ch].int_handler = ct_hdmac0_callback;

		self->gHdmac0Ctrl[self->ch].src_addr = strtoul(argv[3], &self->endstr, 16);

		self->gHdmac0Ctrl[self->ch].dst_addr = strtoul(argv[4], &self->endstr, 16);

		self->ret = Dd_HDMAC0_Ctrl_Common(self->ch, &self->gHdmac0Ctrl[self->ch]);
		if (self->ret == 0) {
			Ddim_Print(("HDMAC0 Ctrl_Common OK\n"));
		}
		else {
			Ddim_Print(("HDMAC0 Ctrl_Common ERR. ret=0x%x\n", self->ret));
		}
	}
	else if (strcmp(argv[1], "ctrl_cmm_cfgb") == 0) {
		/* self->ch number */
		self->ch = atoi(argv[2]);

		self->gHdmac0Ctrl[self->ch].config_b.word = 0;

		// Set MS
		if (strcmp(argv[3], "blk") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.ms = D_DD_HDMAC0_MS_BLK;
		}else if (strcmp(argv[3], "burst") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.ms = D_DD_HDMAC0_MS_BURST;
		}else if (strcmp(argv[3], "demand") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.ms = D_DD_HDMAC0_MS_DEMAND;
		}
		else {
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}

		// Set TW
		if (strcmp(argv[4], "1") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.tw = D_DD_HDMAC0_TW_BYTE;
		}else if (strcmp(argv[4], "2") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.tw = D_DD_HDMAC0_TW_HWORD;
		}else if (strcmp(argv[4], "4") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.tw = D_DD_HDMAC0_TW_WORD;
		}
		else {
			Ddim_Print(("Parameter ERR. P4 \n"));
			return;
		}

		// Set FS
		if (strcmp(argv[5], "src_fix") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.fs = D_DD_HDMAC0_FS_FIX;
		}else if (strcmp(argv[5], "src_incr") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.fs = D_DD_HDMAC0_FS_INCR;
		}
		else {
			Ddim_Print(("Parameter ERR. P5 \n"));
			return;
		}

		// Set FD
		if (strcmp(argv[6], "dst_fix") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.fs = D_DD_HDMAC0_FD_FIX;
		}else if (strcmp(argv[6], "dst_incr") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.fs = D_DD_HDMAC0_FD_INCR;
		}
		else {
			Ddim_Print(("Parameter ERR. P6 \n"));
			return;
		}

		// Set RC
		if (strcmp(argv[7], "ena") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.rc = D_DD_HDMAC0_RC_ENABLE;
		}else if (strcmp(argv[7], "dis") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.rc = D_DD_HDMAC0_RC_DISABLE;
		}
		else {
			Ddim_Print(("Parameter ERR. P7 \n"));
			return;
		}

		// Set RS
		if (strcmp(argv[8], "ena") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.rs = D_DD_HDMAC0_RS_ENABLE;
		}else if (strcmp(argv[8], "dis") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.rs = D_DD_HDMAC0_RS_DISABLE;
		}
		else {
			Ddim_Print(("Parameter ERR. P8 \n"));
			return;
		}

		// Set RD
		if (strcmp(argv[9], "ena") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.rd = D_DD_HDMAC0_RD_ENABLE;
		}else if (strcmp(argv[9], "dis") == 0) {
			self->gHdmac0Ctrl[self->ch].config_b.bit.rd = D_DD_HDMAC0_RD_DISABLE;
		}
		else {
			Ddim_Print(("Parameter ERR. P9 \n"));
			return;
		}

		// Set SP
		self->gHdmac0Ctrl[self->ch].config_b.bit.sp = atoi(argv[10]);

		// Set DP
		self->gHdmac0Ctrl[self->ch].config_b.bit.dp = atoi(argv[11]);
	}
}

CtDdHdmac0* ct_dd_hdmac0_new(void) 
{
    CtDdHdmac0 *self = k_object_new_with_private(CT_TYPE_DD_HDMAC0, sizeof(CtDdHdmac0Private));
    return self;
}
