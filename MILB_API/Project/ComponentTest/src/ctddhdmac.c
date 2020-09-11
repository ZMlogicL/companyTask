/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :杨升柄
*@brief               :CtDdHdmac类
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
#include "dd_hdmac.h"
#include "ct_dd_hdmac.h"
#include "dd_gic.h"
#include "dd_exs.h"
#include "ddim_user_custom.h"
#include <string.h>
#include "ctddhdmac.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdHdmac, ct_dd_hdmac);
#define CT_DD_HDMAC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdHdmacPrivate,CT_TYPE_DD_HDMAC))

/*
 * DECLS
 */
static void 	ctHdmacCallback( void );
static kint32 	ctHdmacSetIs(CtDdHdmac *self, kuchar ch, kchar* is );
static kint 		ct_hdmac_process(kuchar num);

struct _CtDdHdmacPrivate
{
};

static void ct_dd_hdmac_constructor(CtDdHdmac *self) 
{
	self->size = 0;
}

static void ct_dd_hdmac_destructor(CtDdHdmac *self) 
{
}

/*
 * IMPL
 */
static void ctHdmacCallback( void )
{
	Ddim_Print(("HDMAC Callback\n"));
}

static kint32 ctHdmacSetIs(CtDdHdmac *self, kuchar ch, kchar* is )
{
	kint32 ret = D_DDIM_OK;

	// Set IS
	if (strcmp(is, "soft") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_SOFT;
	}else if (strcmp(is, "dreq_h") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_DREQ_H;
	}else if (strcmp(is, "dreq_l") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_DREQ_L;
	}else if (strcmp(is, "idreq_0") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_0;
	}else if (strcmp(is, "idreq_1") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_1;
	}else if (strcmp(is, "idreq_2") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_2;
	}else if (strcmp(is, "idreq_3") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_3;
	}else if (strcmp(is, "idreq_4") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_4;
	}else if (strcmp(is, "idreq_5") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_5;
	}else if (strcmp(is, "idreq_6") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_6;
	}else if (strcmp(is, "idreq_7") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_7;
	}else if (strcmp(is, "idreq_8") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_8;
	}else if (strcmp(is, "idreq_9") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_9;
	}else if (strcmp(is, "idreq_10") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_10;
	}else if (strcmp(is, "idreq_11") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_11;
	}else if (strcmp(is, "idreq_12") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_12;
	}else if (strcmp(is, "idreq_13") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_13;
	}else if (strcmp(is, "idreq_14") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_14;
	}else if (strcmp(is, "idreq_15") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_15;
	}else if (strcmp(is, "idreq_16") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_16;
	}else if (strcmp(is, "idreq_17") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_17;
	}else if (strcmp(is, "idreq_18") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_18;
	}else if (strcmp(is, "idreq_19") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_19;
	}else if (strcmp(is, "idreq_20") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_20;
	}else if (strcmp(is, "idreq_21") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_21;
	}else if (strcmp(is, "idreq_22") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_22;
	}else if (strcmp(is, "idreq_23") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_23;
	}else if (strcmp(is, "idreq_24") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_24;
	}else if (strcmp(is, "idreq_25") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_25;
	}else if (strcmp(is, "idreq_26") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_26;
	}else if (strcmp(is, "idreq_27") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_27;
	}else if (strcmp(is, "idreq_28") == 0) {
		self->gHdmacCtrlTrns[ch].mode.input_sel = D_DD_HDMAC_IS_IDREQ_28;
	}else {
		Ddim_Print(("Parameter ERR. Input Select \n"));
		ret = D_DDIM_INPUT_PARAM_ERROR;
	}
	return ret;
}

static kint ct_hdmac_process(kuchar num)
{
#if 1
	kint32                 						ret;
	kuint32               						waitMode;
	kushort              						status = 0;
	kuchar                						ch;
	kuchar                						arbType;
	T_DD_HDMAC_CTRL      			hdmacCtrl;
	T_DD_HDMAC_CTRL_TRNS 	hdmacCtrlTrns;

	switch (num) {
		// TEST ID 01-01-01
		case 1:
			memset((void*)CtDdHdmac_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 0;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_EXS_HDMAC_CH0_INT,1,D_DD_GIC_PRI30,CtDdHdmac_CPU_TARGET);
			// rotate
			arbType = D_DD_HDMAC_ARB_ROTATE;
			waitMode = D_DD_HDMAC_WAITMODE_CPU;
			// clear
			hdmacCtrl.config_a.word   = 0;

			hdmacCtrl.config_a.bit.is = D_DD_HDMAC_IS_SOFT;
			hdmacCtrl.config_a.bit.bt = D_DD_HDMAC_BT_NORMAL;
			hdmacCtrl.config_a.bit.bc = 0x0F;
			hdmacCtrl.config_a.bit.tc = ((CtDdHdmac_AUTO_TEST_SIZE / 16) - 1);
			// clear
			hdmacCtrl.config_b.word   = 0;

			hdmacCtrl.config_b.bit.ms = D_DD_HDMAC_MS_BLK;
			hdmacCtrl.config_b.bit.tw = D_DD_HDMAC_TW_BYTE;
			hdmacCtrl.config_b.bit.fs = D_DD_HDMAC_FS_INCR;
			hdmacCtrl.config_b.bit.fd = D_DD_HDMAC_FD_INCR;
			hdmacCtrl.config_b.bit.rc = D_DD_HDMAC_RC_DISABLE;
			hdmacCtrl.config_b.bit.rs = D_DD_HDMAC_RS_DISABLE;
			hdmacCtrl.config_b.bit.rd = D_DD_HDMAC_RD_DISABLE;

			hdmacCtrl.src_addr        = CtDdHdmac_AUTO_TEST_ADR_SRC;
			hdmacCtrl.dst_addr        = CtDdHdmac_AUTO_TEST_ADR_DST;
			hdmacCtrl.int_handler     = 0;

			ret = Dd_HDMAC_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC_Ctrl_Common(ch, &hdmacCtrl);
				if (ret != 0) {
					Ddim_Print(("HDMAC Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC_Start_Sync(ch, &status, waitMode);
				if (ret != 0) {
					Ddim_Print(("HDMAC Start Sync ERR\n"));
					break;
				}
				break;
			}
			ret = Dd_HDMAC_Close(ch);
			if (ret != 0) {
				Ddim_Print(("HDMAC Close ERR\n"));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac_AUTO_TEST_ADR_SRC, (void*)CtDdHdmac_AUTO_TEST_ADR_DST, CtDdHdmac_AUTO_TEST_SIZE)));
			break;

		// TEST ID 01-01-02
		case 2:
			memset((void*)CtDdHdmac_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 1;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_EXS_HDMAC_CH1_INT,1,D_DD_GIC_PRI30,CtDdHdmac_CPU_TARGET);
			// fix
			arbType = D_DD_HDMAC_ARB_FIX;
			waitMode = D_DD_HDMAC_WAITMODE_EVENT;
			// clear
			hdmacCtrl.config_a.word   = 0;

			hdmacCtrl.config_a.bit.is = D_DD_HDMAC_IS_SOFT;
			hdmacCtrl.config_a.bit.bt = D_DD_HDMAC_BT_NORMAL;
			hdmacCtrl.config_a.bit.bc = 0x0F;
			hdmacCtrl.config_a.bit.tc = ((CtDdHdmac_AUTO_TEST_SIZE / 16 / 2) - 1);
			// clear
			hdmacCtrl.config_b.word   = 0;

			hdmacCtrl.config_b.bit.ms = D_DD_HDMAC_MS_BURST;
			hdmacCtrl.config_b.bit.tw = D_DD_HDMAC_TW_HWORD;
			hdmacCtrl.config_b.bit.fs = D_DD_HDMAC_FS_INCR;
			hdmacCtrl.config_b.bit.fd = D_DD_HDMAC_FD_INCR;
			hdmacCtrl.config_b.bit.rc = D_DD_HDMAC_RC_DISABLE;
			hdmacCtrl.config_b.bit.rs = D_DD_HDMAC_RS_DISABLE;
			hdmacCtrl.config_b.bit.rd = D_DD_HDMAC_RD_DISABLE;

			hdmacCtrl.src_addr        = CtDdHdmac_AUTO_TEST_ADR_SRC;
			hdmacCtrl.dst_addr        = CtDdHdmac_AUTO_TEST_ADR_DST;
			hdmacCtrl.int_handler     = 0;

			ret = Dd_HDMAC_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC_Ctrl_Common(ch, &hdmacCtrl);
				if (ret != 0) {
					Ddim_Print(("HDMAC Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC_Start_Sync(ch, &status, waitMode);
				if (ret != 0) {
					Ddim_Print(("HDMAC Start Sync ERR\n"));
					break;
				}
				break;
			}
			ret = Dd_HDMAC_Close(ch);
			if (ret != 0) {
				Ddim_Print(("HDMAC Close ERR\n"));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac_AUTO_TEST_ADR_SRC, (void*)CtDdHdmac_AUTO_TEST_ADR_DST, CtDdHdmac_AUTO_TEST_SIZE)));
			break;

		// TEST ID 01-01-03
		case 3:
			memset((void*)CtDdHdmac_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac_AUTO_TEST_SIZE);
			memset((void*)CtDdHdmac_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 2;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_EXS_HDMAC_CH2_INT,1,D_DD_GIC_PRI30,CtDdHdmac_CPU_TARGET);
			// fix
			arbType = D_DD_HDMAC_ARB_FIX;
			waitMode = D_DD_HDMAC_WAITMODE_CPU;

			hdmacCtrlTrns.mode.input_sel = D_DD_HDMAC_IS_SOFT;
			hdmacCtrlTrns.mode.mode_sel  = D_DD_HDMAC_MS_BLK;
			hdmacCtrlTrns.mode.src_fix   = D_DD_HDMAC_FS_INCR;
			hdmacCtrlTrns.mode.dst_fix   = D_DD_HDMAC_FD_INCR;
			hdmacCtrlTrns.mode.beat_type = D_DD_HDMAC_BT_NORMAL;

			hdmacCtrlTrns.size.trns_width = D_DD_HDMAC_TW_WORD;
			hdmacCtrlTrns.size.trns_size  = CtDdHdmac_AUTO_TEST_SIZE;
			hdmacCtrlTrns.size.src_addr   = CtDdHdmac_AUTO_TEST_ADR_SRC;
			hdmacCtrlTrns.size.dst_addr   = CtDdHdmac_AUTO_TEST_ADR_DST;

			hdmacCtrlTrns.int_handler  = 0;

			ret = Dd_HDMAC_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC_Ctrl_Trns(ch, &hdmacCtrlTrns);
				if (ret != 0) {
					Ddim_Print(("HDMAC Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC_Start_Async(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC Start Sync ERR\n"));
					break;
				}
				ret = Dd_HDMAC_Wait_End(ch, &status, waitMode);
				if (ret != 0) {
					Ddim_Print(("HDMAC Wait ERR\n"));
					break;
				}
				break;
			}
			ret = Dd_HDMAC_Close(ch);
			if (ret != 0) {
				Ddim_Print(("HDMAC Close ERR\n"));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac_AUTO_TEST_ADR_SRC, (void*)CtDdHdmac_AUTO_TEST_ADR_DST, CtDdHdmac_AUTO_TEST_SIZE)));
			break;

		// TEST ID 01-01-04
		case 4:
			memset((void*)CtDdHdmac_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac_AUTO_TEST_SIZE);
			memset((void*)CtDdHdmac_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 3;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_EXS_HDMAC_CH3_INT,1,D_DD_GIC_PRI30,CtDdHdmac_CPU_TARGET);
			// fix
			arbType = D_DD_HDMAC_ARB_FIX;
			waitMode = D_DD_HDMAC_WAITMODE_EVENT;

			hdmacCtrlTrns.mode.input_sel = D_DD_HDMAC_IS_SOFT;
			hdmacCtrlTrns.mode.mode_sel  = D_DD_HDMAC_MS_BURST;
			hdmacCtrlTrns.mode.src_fix   = D_DD_HDMAC_FS_INCR;
			hdmacCtrlTrns.mode.dst_fix   = D_DD_HDMAC_FD_INCR;
			hdmacCtrlTrns.mode.beat_type = D_DD_HDMAC_BT_NORMAL;

			hdmacCtrlTrns.size.trns_width = D_DD_HDMAC_TW_BYTE;
			hdmacCtrlTrns.size.trns_size  = CtDdHdmac_AUTO_TEST_SIZE;
			hdmacCtrlTrns.size.src_addr   = CtDdHdmac_AUTO_TEST_ADR_SRC;
			hdmacCtrlTrns.size.dst_addr   = CtDdHdmac_AUTO_TEST_ADR_DST;

			hdmacCtrlTrns.int_handler = 0;

			ret = Dd_HDMAC_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC_Ctrl_Trns(ch, &hdmacCtrlTrns);
				if (ret != 0) {
					Ddim_Print(("HDMAC Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC_Start_Async(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC Start Sync ERR\n"));
					break;
				}
				ret = Dd_HDMAC_Wait_End(ch, &status, waitMode);
				if (ret != 0) {
					Ddim_Print(("HDMAC Wait ERR\n"));
					break;
				}
				break;
			}
			ret = Dd_HDMAC_Close(ch);
			if (ret != 0) {
				Ddim_Print(("HDMAC Close ERR\n"));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac_AUTO_TEST_ADR_SRC, (void*)CtDdHdmac_AUTO_TEST_ADR_DST, CtDdHdmac_AUTO_TEST_SIZE)));
			break;

		case 5:
			memset((void*)CtDdHdmac_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac_AUTO_TEST_SIZE);
			memset((void*)CtDdHdmac_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 2;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_EXS_HDMAC_CH2_INT,1,D_DD_GIC_PRI30,CtDdHdmac_CPU_TARGET);
			// fix
			arbType = D_DD_HDMAC_ARB_FIX;
			waitMode  = D_DD_HDMAC_WAITMODE_EVENT;
			// clear
			hdmacCtrl.config_a.word   = 0;

			hdmacCtrl.config_a.bit.is = D_DD_HDMAC_IS_SOFT;
			hdmacCtrl.config_a.bit.bt = D_DD_HDMAC_BT_NORMAL;
			hdmacCtrl.config_a.bit.bc = 0x0F;
			hdmacCtrl.config_a.bit.tc = ((CtDdHdmac_AUTO_TEST_SIZE / 16) - 1);
			// clear
			hdmacCtrl.config_b.word = 0;

			hdmacCtrl.config_b.bit.ms = D_DD_HDMAC_MS_BLK;
			hdmacCtrl.config_b.bit.tw = D_DD_HDMAC_TW_BYTE;
			hdmacCtrl.config_b.bit.fs = D_DD_HDMAC_FS_INCR;
			hdmacCtrl.config_b.bit.fd = D_DD_HDMAC_FD_INCR;
			hdmacCtrl.config_b.bit.rc = D_DD_HDMAC_RC_DISABLE;
			hdmacCtrl.config_b.bit.rs = D_DD_HDMAC_RS_DISABLE;
			hdmacCtrl.config_b.bit.rd = D_DD_HDMAC_RD_DISABLE;

			hdmacCtrl.src_addr = CtDdHdmac_AUTO_TEST_ADR_SRC;
			hdmacCtrl.dst_addr = CtDdHdmac_AUTO_TEST_ADR_DST;
			hdmacCtrl.int_handler = 0;

			ret = Dd_HDMAC_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC_Ctrl_Common(ch, &hdmacCtrl);
				if (ret != 0) {
					Ddim_Print(("HDMAC Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC_Start_Async(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC Start Async ERR\n"));
					break;
				}
				ret = Dd_HDMAC_Pause(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC Pause ERR\n"));
					break;
				}
				break;
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac_AUTO_TEST_ADR_SRC, (void*)CtDdHdmac_AUTO_TEST_ADR_DST, CtDdHdmac_AUTO_TEST_SIZE)));
			break;

		case 6:
			memset((void*)CtDdHdmac_AUTO_TEST_ADR_DST, 0x00, CtDdHdmac_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 0;
			Dd_GIC_Ctrl(E_DD_GIC_INTID_EXS_HDMAC_CH0_INT,1,D_DD_GIC_PRI30,CtDdHdmac_CPU_TARGET);
			// rotate
			arbType = D_DD_HDMAC_ARB_ROTATE;
			waitMode = D_DD_HDMAC_WAITMODE_EVENT;
			// clear
			hdmacCtrl.config_a.word   = 0;

			hdmacCtrl.config_a.bit.is = D_DD_HDMAC_IS_SOFT;
			hdmacCtrl.config_a.bit.bt = D_DD_HDMAC_BT_NORMAL;
			hdmacCtrl.config_a.bit.bc = (16 / 4) - 1;
			hdmacCtrl.config_a.bit.tc = ((CtDdHdmac_AUTO_TEST_SIZE / 16) - 1);
			// clear
			hdmacCtrl.config_b.word   = 0;

			hdmacCtrl.config_b.bit.ms = D_DD_HDMAC_MS_BLK;
			hdmacCtrl.config_b.bit.tw = D_DD_HDMAC_TW_WORD;
			hdmacCtrl.config_b.bit.fs = D_DD_HDMAC_FS_INCR;
			hdmacCtrl.config_b.bit.fd = D_DD_HDMAC_FD_INCR;
			hdmacCtrl.config_b.bit.rc = D_DD_HDMAC_RC_DISABLE;
			hdmacCtrl.config_b.bit.rs = D_DD_HDMAC_RS_DISABLE;
			hdmacCtrl.config_b.bit.rd = D_DD_HDMAC_RD_DISABLE;

			hdmacCtrl.src_addr = CtDdHdmac_AUTO_TEST_ADR_SRC;
			hdmacCtrl.dst_addr = CtDdHdmac_AUTO_TEST_ADR_DST;
			hdmacCtrl.int_handler = 0;

			ret = Dd_HDMAC_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
			if (ret != 0) {
				Ddim_Print(("HDMAC Open ERR\n"));
				return ret;
			}
			while (1) {
				ret = Dd_HDMAC_Set_Arbitration(arbType);
				if (ret != 0) {
					Ddim_Print(("HDMAC Open ERR\n"));
					break;
				}

				ret = Dd_HDMAC_Ctrl_Common(ch, &hdmacCtrl);
				if (ret != 0) {
					Ddim_Print(("HDMAC Ctrl ERR\n"));
					break;
				}
				ret = Dd_HDMAC_Start_Async(ch);
				if (ret != 0) {
					Ddim_Print(("HDMAC Start Async ERR\n"));
					break;
				}
				Dd_HDMAC_Stop_All_Ch();
				break;
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdHdmac_AUTO_TEST_ADR_SRC, (void*)CtDdHdmac_AUTO_TEST_ADR_DST, CtDdHdmac_AUTO_TEST_SIZE)));
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
void ct_dd_hdmac_from_main(CtDdHdmac *self, kint argc, kchar** argv)
{
	if (strcmp(argv[1], "ctrl_cmm") == 0) {
		/*
		 * ch number
		 */
		self->ch = atoi(argv[2]);

		self->gHdmacCtrl[self->ch].int_handler = ctHdmacCallback;

		self->gHdmacCtrl[self->ch].src_addr = strtoul(argv[3], &self->endstr, 16);

		self->gHdmacCtrl[self->ch].dst_addr = strtoul(argv[4], &self->endstr, 16);

		self->ret = Dd_HDMAC_Ctrl_Common(self->ch, &self->gHdmacCtrl[self->ch]);
		if (self->ret == 0) {
			Ddim_Print(("HDMAC Ctrl_Common OK\n"));
		}else {
			Ddim_Print(("HDMAC Ctrl_Common ERR. self->ret=0x%x\n", self->ret));
		}
	}else if (strcmp(argv[1], "ctrl_trns") == 0) {
		/*
		 * self->ch number
		 */
		self->ch = atoi(argv[2]);

		self->gHdmacCtrlTrns[self->ch].int_handler = ctHdmacCallback;

		self->ret = Dd_HDMAC_Ctrl_Trns(self->ch, &self->gHdmacCtrlTrns[self->ch]);
		if (self->ret == 0) {
			Ddim_Print(("HDMAC Ctrl_Trns OK\n"));
		}else {
			Ddim_Print(("HDMAC Ctrl_Trns ERR. self->ret=0x%x\n", self->ret));
		}
	}else if (strcmp(argv[1], "int_set") == 0) {
		/*
		 *  self->ch number
		 */
		self->ch = atoi(argv[2]);

		self->intHandler = ctHdmacCallback;

		Dd_HDMAC_Set_Int_Handler(self->ch, self->intHandler);
	}else if (strcmp(argv[1], "sdram_async") == 0){
		/*
		 * self->ch number
		 */
		self->ch = atoi(argv[2]);

		self->srcAddr = strtoul(argv[3], &self->endstr, 16);
		self->dstAddr = strtoul(argv[4], &self->endstr, 16);
		self->size = atoi(argv[5]);
		self->intHandler = ctHdmacCallback;
		/*
		 * pgr0539
		 */
		self->ret = Dd_HDMAC_Copy_SDRAM_Async(self->ch, self->srcAddr, self->dstAddr, self->size, self->intHandler);
		if (self->ret == 0) {
			Ddim_Print(("HDMAC Util Copy Async. OK\n"));
		}else {
			Ddim_Print(("HDMAC Util Copy Async. ERR. self->ret=0x%x\n", self->ret));
		}
	}else if (strcmp(argv[1], "err") == 0){
		T_DD_HDMAC_CTRL      			hdmacCtrl;
		T_DD_HDMAC_CTRL_TRNS 	hdmacCtrlTrns;
		T_DD_HDMAC_TRNS_SIZE 		hdmacTrnsSize;
		kushort 									status;

		hdmacCtrlTrns.mode.input_sel = D_DD_HDMAC_IS_SOFT;
		hdmacCtrlTrns.mode.mode_sel = D_DD_HDMAC_MS_BLK;
		hdmacCtrlTrns.mode.src_fix = D_DD_HDMAC_FS_INCR;
		hdmacCtrlTrns.mode.dst_fix = D_DD_HDMAC_FD_INCR;
		hdmacCtrlTrns.mode.beat_type = D_DD_HDMAC_BT_NORMAL;
		hdmacCtrlTrns.size.trns_width = D_DD_HDMAC_TW_WORD;
		hdmacCtrlTrns.size.trns_size = CtDdHdmac_AUTO_TEST_SIZE;
		hdmacCtrlTrns.size.src_addr = CtDdHdmac_AUTO_TEST_ADR_SRC;
		hdmacCtrlTrns.size.dst_addr = CtDdHdmac_AUTO_TEST_ADR_DST;
		hdmacCtrlTrns.int_handler = 0;

		hdmacTrnsSize.trns_width = D_DD_HDMAC_TW_BYTE;
		hdmacTrnsSize.trns_size = CtDdHdmac_AUTO_TEST_SIZE;
		hdmacTrnsSize.src_addr = CtDdHdmac_AUTO_TEST_ADR_SRC;
		hdmacTrnsSize.dst_addr = CtDdHdmac_AUTO_TEST_ADR_DST;

		self->ret = Dd_HDMAC_Open(D_DD_HDMAC_CH_NUM_MAX, D_DDIM_USER_SEM_WAIT_POL);
		Ddim_Print(("Dd_HDMAC_Open(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Close(D_DD_HDMAC_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC_Close(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Ctrl_Common(D_DD_HDMAC_CH_NUM_MAX, &hdmacCtrl);
		Ddim_Print(("Dd_HDMAC_Ctrl_Common(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Ctrl_Common(0, NULL);
		Ddim_Print(("Dd_HDMAC_Ctrl_Common(): ctrl is NULL. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Ctrl_Trns(D_DD_HDMAC_CH_NUM_MAX, &hdmacCtrlTrns);
		Ddim_Print(("Dd_HDMAC_Ctrl_Trns(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Ctrl_Trns(0, NULL);
		Ddim_Print(("Dd_HDMAC_Ctrl_Trns(): ctrl is NULL. self->ret=0x%x\n", self->ret));

		// BC over test (Ctrl_Trns)     65536*4*17
		hdmacCtrlTrns.size.trns_size  = 0x00440000;
		self->ret = Dd_HDMAC_Ctrl_Trns(0, &hdmacCtrlTrns);
		Ddim_Print(("Dd_HDMAC_Ctrl_Trns(): BC is over. self->ret=0x%x\n", self->ret));

		// BC over test in Demand mode (Ctrl_Trns)
		hdmacCtrlTrns.mode.mode_sel  = D_DD_HDMAC_MS_DEMAND;
		// 65536*4*2
		hdmacCtrlTrns.size.trns_size = 0x00080000;
		self->ret = Dd_HDMAC_Ctrl_Trns(0, &hdmacCtrlTrns);
		Ddim_Print(("Dd_HDMAC_Ctrl_Trns(): demand transfer and BC is not 0. self->ret=0x%x\n", self->ret));


		self->ret = Dd_HDMAC_Set_Trns_Size(D_DD_HDMAC_CH_NUM_MAX, &hdmacTrnsSize);
		Ddim_Print(("Dd_HDMAC_Set_Trns_Size(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Set_Trns_Size(0, NULL);
		Ddim_Print(("Dd_HDMAC_Set_Trns_Size(): trns_size is NULL. self->ret=0x%x\n", self->ret));

		// BC over test (Set_Trns_Size)
		hdmacCtrlTrns.mode.mode_sel  = D_DD_HDMAC_MS_BLK;
		hdmacCtrlTrns.size.trns_size = 0x00001000;
		self->ret = Dd_HDMAC_Ctrl_Trns(0, &hdmacCtrlTrns);
		// 65536*1*17
		hdmacTrnsSize.trns_size = 0x00110000;
		self->ret = Dd_HDMAC_Set_Trns_Size(0, &hdmacTrnsSize);
		Ddim_Print(("Dd_HDMAC_Set_Trns_Size(): BC is over. self->ret=0x%x\n", self->ret));

		// BC over test in Demand mode (Set_Trns_Size)
		hdmacCtrlTrns.mode.mode_sel  = D_DD_HDMAC_MS_DEMAND;
		hdmacCtrlTrns.size.trns_size = 0x00001000;
		self->ret = Dd_HDMAC_Ctrl_Trns(0, &hdmacCtrlTrns);
		// 65536*1*2
		hdmacTrnsSize.trns_size = 0x00020000;
		self->ret = Dd_HDMAC_Set_Trns_Size(0, &hdmacTrnsSize);
		Ddim_Print(("Dd_HDMAC_Set_Trns_Size(): demand transfer and BC is not 0. self->ret=0x%x\n", self->ret));


		self->ret = Dd_HDMAC_Start_Sync(D_DD_HDMAC_CH_NUM_MAX, &status, D_DD_HDMAC_WAITMODE_CPU);
		Ddim_Print(("Dd_HDMAC_Start_Sync(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Start_Sync(0, NULL, D_DD_HDMAC_WAITMODE_CPU);
		Ddim_Print(("Dd_HDMAC_Start_Sync(): status is NULL. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Start_Sync(0, &status, D_DD_HDMAC_WAITMODE_EVENT+1);
		Ddim_Print(("Dd_HDMAC_Start_Sync(): waitMode is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Start_Async(D_DD_HDMAC_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC_Start_Async(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Stop(D_DD_HDMAC_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC_Stop(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Pause(D_DD_HDMAC_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC_Pause(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Resume(D_DD_HDMAC_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC_Resume(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Set_Wait_Time(D_DD_HDMAC_CH_NUM_MAX, D_DDIM_USER_SEM_WAIT_POL);
		Ddim_Print(("Dd_HDMAC_Set_Wait_Time(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Set_Wait_Time(0, -2);
		Ddim_Print(("Dd_HDMAC_Set_Wait_Time(): wait_time is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Wait_End(D_DD_HDMAC_CH_NUM_MAX, &status, D_DD_HDMAC_WAITMODE_CPU);
		Ddim_Print(("Dd_HDMAC_Wait_End(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Wait_End(0, NULL, D_DD_HDMAC_WAITMODE_CPU);
		Ddim_Print(("Dd_HDMAC_Wait_End(): status is NULL. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Wait_End(0, &status, D_DD_HDMAC_WAITMODE_EVENT+1);
		Ddim_Print(("Dd_HDMAC_Wait_End(): waitMode is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Clear_Status(D_DD_HDMAC_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC_Clear_Status(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Get_Status(D_DD_HDMAC_CH_NUM_MAX, &status);
		Ddim_Print(("Dd_HDMAC_Get_Status(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Get_Status(0, NULL);
		Ddim_Print(("Dd_HDMAC_Get_Status(): status is NULL. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Get_Trns_Size(D_DD_HDMAC_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC_Get_Trns_Size(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Get_Remain_Trns_Size(D_DD_HDMAC_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC_Get_Remain_Trns_Size(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Get_Total_Trns_Size(D_DD_HDMAC_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC_Get_Total_Trns_Size(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Get_Src_Addr(D_DD_HDMAC_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC_Get_Src_Addr(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Get_Dst_Addr(D_DD_HDMAC_CH_NUM_MAX);
		Ddim_Print(("Dd_HDMAC_Get_Dst_Addr(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Set_Source_Protect(D_DD_HDMAC_CH_NUM_MAX, 0);
		Ddim_Print(("Dd_HDMAC_Set_Source_Protect(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Set_Destination_Protect(D_DD_HDMAC_CH_NUM_MAX, 0);
		Ddim_Print(("Dd_HDMAC_Set_Destination_Protect(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Set_Arbitration(D_DD_HDMAC_ARB_ROTATE+1);
		Ddim_Print(("Dd_HDMAC_Set_Arbitration(): arbitration is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Get_Arbitration(NULL);
		Ddim_Print(("Dd_HDMAC_Get_Arbitration(): arbitration is NULL. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Copy_SDRAM_Sync(D_DD_HDMAC_CH_NUM_MAX, 1, 2, 1, D_DD_HDMAC_WAITMODE_EVENT);
		Ddim_Print(("Dd_HDMAC_Copy_SDRAM_Sync(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Copy_SDRAM_Sync(0, 0, 2, 1, D_DD_HDMAC_WAITMODE_EVENT);
		Ddim_Print(("Dd_HDMAC_Copy_SDRAM_Sync(): src_addr is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Copy_SDRAM_Sync(0, 1, 0, 1, D_DD_HDMAC_WAITMODE_EVENT);
		Ddim_Print(("Dd_HDMAC_Copy_SDRAM_Sync(): dst_addr is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Copy_SDRAM_Sync(0, 1, 2, 0, D_DD_HDMAC_WAITMODE_EVENT);
		Ddim_Print(("Dd_HDMAC_Copy_SDRAM_Sync(): size is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Copy_SDRAM_Sync(0, 1, 2, 1, D_DD_HDMAC_WAITMODE_EVENT+1);
		Ddim_Print(("Dd_HDMAC_Copy_SDRAM_Sync(): waitMode is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Copy_SDRAM_Async(D_DD_HDMAC_CH_NUM_MAX, 1, 2, 1, ctHdmacCallback);
		Ddim_Print(("Dd_HDMAC_Copy_SDRAM_Async(): Channel number is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Copy_SDRAM_Async(0, 0, 2, 1, ctHdmacCallback);
		Ddim_Print(("Dd_HDMAC_Copy_SDRAM_Async(): src_addr is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Copy_SDRAM_Async(0, 1, 0, 1, ctHdmacCallback);
		Ddim_Print(("Dd_HDMAC_Copy_SDRAM_Async(): dst_addr is illegal. self->ret=0x%x\n", self->ret));

		self->ret = Dd_HDMAC_Copy_SDRAM_Async(0, 1, 2, 0, ctHdmacCallback);
		Ddim_Print(("Dd_HDMAC_Copy_SDRAM_Async(): size is illegal. self->ret=0x%x\n", self->ret));
	}else if (strcmp(argv[1], "ctrl_cmm_cfga") == 0) {
		/*
		 * self->ch number
		 */
		self->ch = atoi(argv[2]);

		self->gHdmacCtrl[self->ch].config_a.word = 0;

		// Set IS
		self->ret = ctHdmacSetIs(self, self->ch, argv[3]);
		if( self->ret != D_DDIM_OK ){
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}

		// Set BT
		if (strcmp(argv[4], "normal") == 0) {
			self->gHdmacCtrl[self->ch].config_a.bit.bt = D_DD_HDMAC_BT_NORMAL;
		}else if (strcmp(argv[4], "single") == 0) {
			self->gHdmacCtrl[self->ch].config_a.bit.bt = D_DD_HDMAC_BT_SINGLE;
		}else if (strcmp(argv[4], "incr") == 0) {
			self->gHdmacCtrl[self->ch].config_a.bit.bt = D_DD_HDMAC_BT_INCR;
		}else if (strcmp(argv[4], "wrap4") == 0) {
			self->gHdmacCtrl[self->ch].config_a.bit.bt = D_DD_HDMAC_BT_WRAP4;
		}else if (strcmp(argv[4], "incr4") == 0) {
			self->gHdmacCtrl[self->ch].config_a.bit.bt = D_DD_HDMAC_BT_INCR4;
		}else if (strcmp(argv[4], "wrap8") == 0) {
			self->gHdmacCtrl[self->ch].config_a.bit.bt = D_DD_HDMAC_BT_WRAP8;
		}else if (strcmp(argv[4], "incr8") == 0) {
			self->gHdmacCtrl[self->ch].config_a.bit.bt = D_DD_HDMAC_BT_INCR8;
		}else if (strcmp(argv[4], "wrap16") == 0) {
			self->gHdmacCtrl[self->ch].config_a.bit.bt = D_DD_HDMAC_BT_WRAP16;
		}else if (strcmp(argv[4], "incr16") == 0) {
			self->gHdmacCtrl[self->ch].config_a.bit.bt = D_DD_HDMAC_BT_INCR16;
		}else {
			Ddim_Print(("Parameter ERR. P4 \n"));
			return;
		}

		// Set BC
		self->gHdmacCtrl[self->ch].config_a.bit.bc = atoi(argv[5]);

		// Set TC
		self->gHdmacCtrl[self->ch].config_a.bit.tc = atoi(argv[6]);
	}else if (strcmp(argv[1], "ctrl_trns_md") == 0) {
		/*
		 * self->ch number
		 */
		self->ch = atoi(argv[2]);

		// Set IS
		self->ret = ctHdmacSetIs(self, self->ch, argv[3]);
		if( self->ret != D_DDIM_OK ){
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}

		// Set MS
		if (strcmp(argv[4], "blk") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.mode_sel = D_DD_HDMAC_MS_BLK;
		}else if (strcmp(argv[4], "burst") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.mode_sel = D_DD_HDMAC_MS_BURST;
		}else if (strcmp(argv[4], "demand") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.mode_sel = D_DD_HDMAC_MS_DEMAND;
		}else {
			Ddim_Print(("Parameter ERR. P4 \n"));
			return;
		}

		// Set FS
		if (strcmp(argv[5], "src_fix") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.src_fix = D_DD_HDMAC_FS_FIX;
		}else if (strcmp(argv[5], "src_incr") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.src_fix = D_DD_HDMAC_FS_INCR;
		}else {
			Ddim_Print(("Parameter ERR. P5 \n"));
			return;
		}

		// Set FD
		if (strcmp(argv[6], "dst_fix") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.dst_fix = D_DD_HDMAC_FD_FIX;
		}else if (strcmp(argv[6], "dst_incr") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.dst_fix = D_DD_HDMAC_FD_INCR;
		}else {
			Ddim_Print(("Parameter ERR. P6 \n"));
			return;
		}

		// Set BT
		if (strcmp(argv[7], "normal") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC_BT_NORMAL;
		}else if (strcmp(argv[7], "single") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC_BT_SINGLE;
		}else if (strcmp(argv[7], "incr") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC_BT_INCR;
		}else if (strcmp(argv[7], "wrap4") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC_BT_WRAP4;
		}else if (strcmp(argv[7], "incr4") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC_BT_INCR4;
		}else if (strcmp(argv[7], "wrap8") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC_BT_WRAP8;
		}else if (strcmp(argv[7], "incr8") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC_BT_INCR8;
		}else if (strcmp(argv[7], "wrap16") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC_BT_WRAP16;
		}else if (strcmp(argv[7], "incr16") == 0) {
			self->gHdmacCtrlTrns[self->ch].mode.beat_type = D_DD_HDMAC_BT_INCR16;
		}else {
			Ddim_Print(("Parameter ERR. P7 \n"));
			return;
		}
	}else if(strcmp(argv[1], "cmp") == 0) {
		Ddim_Print(("cmp = %d\n", memcmp((void*)strtoul(argv[2],
				&self->endstr, 16), (void*)strtoul(argv[3], &self->endstr, 16), atoi(argv[4]))));
	}else if (strcmp(argv[1], "auto") == 0) {
		/*
		 * ch number
		 */
		self->num = atoi(argv[2]);

		self->ret = ct_hdmac_process(self->num);
		if (self->ret == 0) {
			Ddim_Print(("ct_hdmac_process OK\n"));
		}else
		{
			Ddim_Print(("ct_hdmac_process ERR. self->ret=0x%x\n", self->ret));
		}
	}
}

CtDdHdmac* ct_dd_hdmac_new(void) 
{
    CtDdHdmac *self = k_object_new_with_private(CT_TYPE_DD_HDMAC, sizeof(CtDdHdmacPrivate));
    return self;
}
