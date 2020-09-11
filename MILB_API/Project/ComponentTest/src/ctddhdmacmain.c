/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :杨升柄
*@brief               :CtDdHdmacMain类
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
#include "ctddhdmacmain.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdHdmacMain, ct_dd_hdmac_main);
#define CT_DD_HDMAC_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdHdmacMainPrivate,CT_TYPE_DD_HDMAC_MAIN))

struct _CtDdHdmacMainPrivate
{
	CtDdHdmac *cdHdmac;
};

static void ct_dd_hdmac_main_constructor(CtDdHdmacMain *self) 
{
	CtDdHdmacMainPrivate *priv = CT_DD_HDMAC_MAIN_GET_PRIVATE(self);

	priv->cdHdmac = ct_dd_hdmac_new();
}

static void ct_dd_hdmac_main_destructor(CtDdHdmacMain *self) 
{
	CtDdHdmacMainPrivate *priv = CT_DD_HDMAC_MAIN_GET_PRIVATE(self);

	if(priv->cdHdmac)
	{
		k_object_unref(priv->cdHdmac);
	}
	priv->cdHdmac = NULL;
}

/**
 *PUBLIC
 ***********************
 * @brief  Command main function for HDMAC test.
 * @param  kint32 argc	:The number of parameters
 *		   kchar** argv	:The value of parameters
 *
 *	The meaning of parameters
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| P1              | P2       | P3         | P4       | P5         | P6         | P7       | P8 | P9 | P10 | P11 | Meaning                            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "open"          | priv->cdHdmac->ch       | waitTime  |          |            |            |          |    |    |     |     | Dd_HDMAC_Open()                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "close"         | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Close()                   |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_cmm"      | priv->cdHdmac->ch       | src_addr   | dst_addr |            |            |          |    |    |     |     | Dd_HDMAC_Ctrl_Common()             |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_cmm_cfga" | priv->cdHdmac->ch       | "soft"     | "normal" | bc         | tc         |          |    |    |     |     | Set DMACA                          |
 *	|                 |          | "dreq_h"   | "single" |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "dreq_l"   | "incr"   |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_0"  | "wrap4"  |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_1"  | "incr4"  |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_2"  | "wrap8"  |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_3"  | "incr8"  |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_4"  | "wrap16" |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_5"  | "incr16" |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_6"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_7"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_8"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_9"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_10" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_11" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_12" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_13" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_14" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_15" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_16" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_17" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_18" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_19" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_20" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_21" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_22" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_23" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_24" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_25" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_26" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_27" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_28" |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_cmm_cfgb" | priv->cdHdmac->ch       | "blk"      | "1"      | "src_fix"  | "dst_fix"  | rc       | rs | rd | sp  | dp  | Set DMACB                          |
 *	|                 |          | "burst"    | "2"      | "src_incr" | "dst_incr" |          |    |    |     |     |                                    |
 *	|                 |          | "demand"   | "4"      |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_trns"     | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Ctrl_Trns()               |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_trns_md"  | priv->cdHdmac->ch       | "soft"     | "blk"    | "src_fix"  | "dst_fix"  | "normal" |    |    |     |     | Set HDMAC transfer mode            |
 *	|                 |          | "dreq_h"   | "burst"  | "src_incr" | "dst_incr" | "single" |    |    |     |     |                                    |
 *	|                 |          | "dreq_l"   | "demand" |            |            | "incr"   |    |    |     |     |                                    |
 *	|                 |          | "idreq_0"  |          |            |            | "wrap4"  |    |    |     |     |                                    |
 *	|                 |          | "idreq_1"  |          |            |            | "incr4"  |    |    |     |     |                                    |
 *	|                 |          | "idreq_2"  |          |            |            | "wrap8"  |    |    |     |     |                                    |
 *	|                 |          | "idreq_3"  |          |            |            | "incr8"  |    |    |     |     |                                    |
 *	|                 |          | "idreq_4"  |          |            |            | "wrap16" |    |    |     |     |                                    |
 *	|                 |          | "idreq_5"  |          |            |            | "incr16" |    |    |     |     |                                    |
 *	|                 |          | "idreq_6"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_7"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_8"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_9"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_10" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_11" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_12" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_13" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_14" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_15" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_16" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_17" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_18" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_19" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_20" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_21" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_22" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_23" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_24" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_25" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_26" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_27" |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_28" |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_trns_sz"  | priv->cdHdmac->ch       | "1"        | size     | src_addr   | dst_addr   |          |    |    |     |     | Set HDMAC transfer size            |
 *	|                 |          | "2"        |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "4"        |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "start_sync"    | priv->cdHdmac->ch       | "cpu"      |          |            |            |          |    |    |     |     | Dd_HDMAC_Start_Sync()              |
 *	|                 |          | "event"    |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "start_async"   | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Start_Async()             |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "stop"          | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Stop()                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "pause"         | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Pause()                   |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "resume"        | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Resume()                  |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "wait"          | priv->cdHdmac->ch       | "cpu"      |          |            |            |          |    |    |     |     | Dd_HDMAC_Wait_End()                |
 *	|                 |          | "event"    |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "set_wait_time" | priv->cdHdmac->ch       | time       |          |            |            |          |    |    |     |     | Dd_HDMAC_Set_Wait_Time()           |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "status_clear"  | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Clear_Status()            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "status_read"   | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Get_Status()              |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "trns_size_set" | priv->cdHdmac->ch       | "1"        | size     | src_addr   | dst_addr   |          |    |    |     |     | Dd_HDMAC_Set_Trns_Size()           |
 *	|                 |          | "2"        |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "4"        |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "trns_size_get" | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Get_Trns_Size()           |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "rmn_size_get"  | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Get_Remain_Trns_Size()    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "total_size_get"| priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Get_Total_Trns_Size()     |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "src_addr_get"  | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Get_Src_Addr()            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "dst_addr_get"  | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Get_Dst_Addr()            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "src_prot_set"  | priv->cdHdmac->ch       | sp         |          |            |            |          |    |    |     |     | Dd_HDMAC_Set_Source_Protect()      |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "dst_prot_set"  | priv->cdHdmac->ch       | dp         |          |            |            |          |    |    |     |     | Dd_HDMAC_Set_Destination_Protect() |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "arb_set"       | "rotate" |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Set_Arbitration()         |
 *	|                 | "fix"    |            |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "arb_get"       |          |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Get_Arbitration()         |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "arb_clear"     |          |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Clear_Arbitration()       |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "stop_all"      |          |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Stop_All_Ch()             |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "resume_all"    |          |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Resume_All_Ch()           |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "get_width"     | src_addr | dst_addr   | size     |            |            |          |    |    |     |     | Dd_HDMAC_Get_Trns_Width()          |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "int_set"       | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Set_Int_Handler()         |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "int_handler"   | priv->cdHdmac->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC_Int_Handler()             |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "auto"          | num      |            |          |            |            |          |    |    |     |     | Continuous execution               |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "sdram_sync"    | priv->cdHdmac->ch       | src_addr   | dst_addr | size       | "cpu"      |          |    |    |     |     | Dd_HDMAC_Copy_SDRAM_Sync()         |
 *	|                 |          |            |          |            | "event"    |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "sdram_async"   | priv->cdHdmac->ch       | src_addr   | dst_addr | size       |            |          |    |    |     |     | Dd_HDMAC_Copy_SDRAM_Async()        |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "err"           |          |            |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *
 *			priv->cdHdmac->ch			:	0          - 7
 *			rc			:	ena / dis
 *			rs			:	ena / dis
 *			rd			:	ena / dis
 *			sp			:	0          - 15
 *			dp			:	0          - 15
 *			size		:	0          - 0xFFFFFFFF
 *			src_addr	:	0          - 0xFFFFFFFF
 *			dst_addr	:	0          - 0xFFFFFFFF
 *			IntHandler  :	Callback Function Pointer
 *			num			:	Test ID
 *
 * @return void
 */
void ct_dd_hdmac_main_test(CtDdHdmacMain *self, kint argc, kchar** argv)
{
	CtDdHdmacMainPrivate* 	priv = CT_DD_HDMAC_MAIN_GET_PRIVATE(self);
	kuint32								waitMode = D_DD_HDMAC_WAITMODE_CPU;
	kulong									totalSize;
	kulong									transWidth = 0;
	kushort								status = 0;
	kuchar									prot;
	kuchar									arbType;
	kint32									waitTime;

	// check number of parameter
	if (argc > 12) {
		Ddim_Print(("The number of input parameters is exceeded!\n"));
		return;
	}

	//	Dd_Top_Set_CLKSTOP_HDMEAH(0);
	Dd_Exs_Set_HDMAC_BUS_CLOCK_Stop_Ctrl(0);

	ct_dd_hdmac_from_main(priv->cdHdmac, argc, argv);

	if (strcmp(argv[1], "open") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);
		waitTime = atoi(argv[3]);

		priv->cdHdmac->ret = Dd_HDMAC_Open(priv->cdHdmac->ch, waitTime);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Open OK\n"));
		}else {
			Ddim_Print(("HDMAC Open ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "close") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->ret = Dd_HDMAC_Close(priv->cdHdmac->ch);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Close OK\n"));
		}else {
			Ddim_Print(("HDMAC Close ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "ctrl_cmm_cfgb") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.word = 0;

		// Set MS
		if (strcmp(argv[3], "blk") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.ms = D_DD_HDMAC_MS_BLK;
		}else if (strcmp(argv[3], "burst") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.ms = D_DD_HDMAC_MS_BURST;
		}else if (strcmp(argv[3], "demand") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.ms = D_DD_HDMAC_MS_DEMAND;
		}else {
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}

		// Set TW
		if (strcmp(argv[4], "1") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.tw = D_DD_HDMAC_TW_BYTE;
		}else if (strcmp(argv[4], "2") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.tw = D_DD_HDMAC_TW_HWORD;
		}else if (strcmp(argv[4], "4") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.tw = D_DD_HDMAC_TW_WORD;
		}else {
			Ddim_Print(("Parameter ERR. P4 \n"));
			return;
		}

		// Set FS
		if (strcmp(argv[5], "src_fix") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.fs = D_DD_HDMAC_FS_FIX;
		}else if (strcmp(argv[5], "src_incr") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.fs = D_DD_HDMAC_FS_INCR;
		}else {
			Ddim_Print(("Parameter ERR. P5 \n"));
			return;
		}

		// Set FD
		if (strcmp(argv[6], "dst_fix") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.fs = D_DD_HDMAC_FD_FIX;
		}else if (strcmp(argv[6], "dst_incr") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.fs = D_DD_HDMAC_FD_INCR;
		}else {
			Ddim_Print(("Parameter ERR. P6 \n"));
			return;
		}

		// Set RC
		if (strcmp(argv[7], "ena") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.rc = D_DD_HDMAC_RC_ENABLE;
		}else if (strcmp(argv[7], "dis") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.rc = D_DD_HDMAC_RC_DISABLE;
		}else {
			Ddim_Print(("Parameter ERR. P7 \n"));
			return;
		}

		// Set RS
		if (strcmp(argv[8], "ena") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.rs = D_DD_HDMAC_RS_ENABLE;
		}else if (strcmp(argv[8], "dis") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.rs = D_DD_HDMAC_RS_DISABLE;
		}else {
			Ddim_Print(("Parameter ERR. P8 \n"));
			return;
		}

		// Set RD
		if (strcmp(argv[9], "ena") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.rd = D_DD_HDMAC_RD_ENABLE;
		}else if (strcmp(argv[9], "dis") == 0) {
			priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.rd = D_DD_HDMAC_RD_DISABLE;
		}else {
			Ddim_Print(("Parameter ERR. P9 \n"));
			return;
		}

		// Set SP
		priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.sp = atoi(argv[10]);

		// Set DP
		priv->cdHdmac->gHdmacCtrl[priv->cdHdmac->ch].config_b.bit.dp = atoi(argv[11]);
	}else if (strcmp(argv[1], "ctrl_trns_sz") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		// Set TW
		if (strcmp(argv[3], "1") == 0) {
			priv->cdHdmac->gHdmacCtrlTrns[priv->cdHdmac->ch].size.trns_width = D_DD_HDMAC_TW_BYTE;
		}else if (strcmp(argv[3], "2") == 0) {
			priv->cdHdmac->gHdmacCtrlTrns[priv->cdHdmac->ch].size.trns_width = D_DD_HDMAC_TW_HWORD;
		}else if (strcmp(argv[3], "4") == 0) {
			priv->cdHdmac->gHdmacCtrlTrns[priv->cdHdmac->ch].size.trns_width = D_DD_HDMAC_TW_WORD;
		}else {
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}

		// Set Size
		priv->cdHdmac->gHdmacCtrlTrns[priv->cdHdmac->ch].size.trns_size = atoi(argv[4]);

		priv->cdHdmac->gHdmacCtrlTrns[priv->cdHdmac->ch].size.src_addr = strtoul(argv[5], &priv->cdHdmac->endstr, 16);

		priv->cdHdmac->gHdmacCtrlTrns[priv->cdHdmac->ch].size.dst_addr = strtoul(argv[6], &priv->cdHdmac->endstr, 16);
	}else if (strcmp(argv[1], "start_sync") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		if (strcmp(argv[3], "cpu") == 0) {
			waitMode = D_DD_HDMAC_WAITMODE_CPU;
		}else if (strcmp(argv[3], "event") == 0) {
			waitMode = D_DD_HDMAC_WAITMODE_EVENT;
		}else {
			Ddim_Print(("Parameter ERR P3. waitMode=0x%x\n", waitMode));
			return ;
		}

		priv->cdHdmac->ret = Dd_HDMAC_Start_Sync(priv->cdHdmac->ch, &status, waitMode);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Start Sync OK\n"));
		}else {
			Ddim_Print(("HDMAC Start Sync ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
		Ddim_Print(("status=0x%x\n", status));
	}else if (strcmp(argv[1], "start_async") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->ret = Dd_HDMAC_Start_Async(priv->cdHdmac->ch);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Start Async OK\n"));
		}else {
			Ddim_Print(("HDMAC Start Async ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "stop") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->ret = Dd_HDMAC_Stop(priv->cdHdmac->ch);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Stop OK\n"));
		}else {
			Ddim_Print(("HDMAC Stop ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "pause") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->ret = Dd_HDMAC_Pause(priv->cdHdmac->ch);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Pause OK\n"));
		}else {
			Ddim_Print(("HDMAC Pause ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "resume") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->ret = Dd_HDMAC_Resume(priv->cdHdmac->ch);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Resume OK\n"));
		}else {
			Ddim_Print(("HDMAC Resume ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "wait") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		if (strcmp(argv[3], "cpu") == 0 ){
			waitMode = D_DD_HDMAC_WAITMODE_CPU;
		}else if (strcmp(argv[3], "event") == 0) {
			waitMode = D_DD_HDMAC_WAITMODE_EVENT;
		}else {
			Ddim_Print(("Parameter ERR P3. waitMode=0x%x\n", waitMode));
			return ;
		}

		priv->cdHdmac->ret = Dd_HDMAC_Wait_End(priv->cdHdmac->ch, &status, waitMode);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Wait OK\n"));
		}else {
			Ddim_Print(("HDMAC Wait ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
		Ddim_Print(("status=0x%x\n", status));
	}else if (strcmp(argv[1], "set_wait_time") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);
		kint32 waitTime = atoi(argv[3]);

		priv->cdHdmac->ret = Dd_HDMAC_Set_Wait_Time(priv->cdHdmac->ch, waitTime);
		if ( priv->cdHdmac->ret == D_DDIM_OK ) {
			Ddim_Print(("HDMAC Set Wait Time OK\n"));
		}else {
			Ddim_Print(("HDMAC Set Wait Time ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "status_clear") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->ret = Dd_HDMAC_Clear_Status(priv->cdHdmac->ch);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Status Clear OK\n"));
		}else {
			Ddim_Print(("HDMAC Status Clear ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "status_read") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->ret = Dd_HDMAC_Get_Status(priv->cdHdmac->ch, &status);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Get Status OK\n"));
		}else {
			Ddim_Print(("HDMAC Get Status ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
		Ddim_Print(("status=0x%x\n", status));
	}else if (strcmp(argv[1], "trns_size_set") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		// Set TW
		if (strcmp(argv[3], "1") == 0) {
			priv->cdHdmac->gHdmacTrnsSize[priv->cdHdmac->ch].trns_width = D_DD_HDMAC_TW_BYTE;
		}else if (strcmp(argv[3], "2") == 0) {
			priv->cdHdmac->gHdmacTrnsSize[priv->cdHdmac->ch].trns_width = D_DD_HDMAC_TW_HWORD;
		}else if (strcmp(argv[3], "4") == 0) {
			priv->cdHdmac->gHdmacTrnsSize[priv->cdHdmac->ch].trns_width = D_DD_HDMAC_TW_WORD;
		}else {
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}
		priv->cdHdmac->gHdmacTrnsSize[priv->cdHdmac->ch].trns_size = atoi(argv[4]);
		priv->cdHdmac->gHdmacTrnsSize[priv->cdHdmac->ch].src_addr = strtoul(argv[5], &priv->cdHdmac->endstr, 16);
		priv->cdHdmac->gHdmacTrnsSize[priv->cdHdmac->ch].dst_addr = strtoul(argv[6], &priv->cdHdmac->endstr, 16);

		priv->cdHdmac->ret = Dd_HDMAC_Set_Trns_Size(priv->cdHdmac->ch,
				&priv->cdHdmac->gHdmacTrnsSize[priv->cdHdmac->ch]);
		if ( priv->cdHdmac->ret == D_DDIM_OK ) {
			Ddim_Print(("HDMAC Set Trans Size OK\n"));
		}else {
			Ddim_Print(("HDMAC Set Trans Size ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "trns_size_get") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->size = Dd_HDMAC_Get_Trns_Size(priv->cdHdmac->ch);
		Ddim_Print(("HDMAC Trans Size Get OK\n"));
		Ddim_Print(("Size=%d\n", priv->cdHdmac->size));
	}else if (strcmp(argv[1], "rmn_size_get") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->size = Dd_HDMAC_Get_Remain_Trns_Size(priv->cdHdmac->ch);
		Ddim_Print(("HDMAC Remain Trans Size OK\n"));
		Ddim_Print(("Size=%d\n", priv->cdHdmac->size));
	}else if (strcmp(argv[1], "total_size_get") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->size = Dd_HDMAC_Get_Total_Trns_Size(priv->cdHdmac->ch);
		Ddim_Print(("HDMAC Total Trans Size OK\n"));
		Ddim_Print(("Size=%d\n", priv->cdHdmac->size));
	}else if (strcmp(argv[1], "src_addr_get") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->srcAddr = Dd_HDMAC_Get_Src_Addr(priv->cdHdmac->ch);
		Ddim_Print(("HDMAC Source Address OK\n"));
		Ddim_Print(("Src Addr=0x%08lx\n", priv->cdHdmac->srcAddr));
	}else if (strcmp(argv[1], "dst_addr_get") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->dstAddr = Dd_HDMAC_Get_Dst_Addr(priv->cdHdmac->ch);
		Ddim_Print(("HDMAC Destination Address OK\n"));
		Ddim_Print(("Dst Addr=0x%08lx\n", priv->cdHdmac->dstAddr));
	}else if (strcmp(argv[1], "src_prot_set") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);
		prot = atoi(argv[3]);

		priv->cdHdmac->ret = Dd_HDMAC_Set_Source_Protect(priv->cdHdmac->ch, prot);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Source Protect Set OK\n"));
		}else {
			Ddim_Print(("HDMAC Source Protect Set ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "dst_prot_set") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);
		prot = atoi(argv[3]);

		priv->cdHdmac->ret = Dd_HDMAC_Set_Destination_Protect(priv->cdHdmac->ch, prot);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Destination Protect Set OK\n"));
		}else {
			Ddim_Print(("HDMAC Destination Protect Set ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "arb_set") == 0) {
		if (strcmp(argv[2], "rotate") == 0) {
			arbType = D_DD_HDMAC_ARB_ROTATE;
		}else if (strcmp(argv[2], "fix") == 0) {
			arbType = D_DD_HDMAC_ARB_FIX;
		}else {
			Ddim_Print(("Parameter ERR P2. \n"));
			return;
		}

		priv->cdHdmac->ret = Dd_HDMAC_Set_Arbitration(arbType);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Arbitration Set OK\n"));
		}else {
			Ddim_Print(("HDMAC Arbitration Set ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "arb_get") == 0) {
		priv->cdHdmac->ret = Dd_HDMAC_Get_Arbitration(&arbType);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Arbitration Read OK\n"));
			Ddim_Print(("arbType=0x%x\n", arbType));
		}else {
			Ddim_Print(("HDMAC Arbitration Read ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else if (strcmp(argv[1], "arb_clear") == 0) {
		Dd_HDMAC_Clear_Arbitration();
	}else if (strcmp(argv[1], "stop_all") == 0) {
		Dd_HDMAC_Stop_All_Ch();
	}else if (strcmp(argv[1], "resume_all") == 0) {
		Dd_HDMAC_Resume_All_Ch();
	}else if (strcmp(argv[1], "get_width") == 0) {
		priv->cdHdmac->srcAddr = strtoul(argv[2], &priv->cdHdmac->endstr, 16);
		priv->cdHdmac->dstAddr = strtoul(argv[3], &priv->cdHdmac->endstr, 16);
		totalSize = atoi(argv[4]);
		// pgr0539
		transWidth = Dd_HDMAC_Get_Trns_Width(priv->cdHdmac->srcAddr, priv->cdHdmac->dstAddr, totalSize);
		Ddim_Print(("HDMAC Trans Width Get OK\n"));
		Ddim_Print(("transWidth=%lu\n", transWidth));
	}else if (strcmp(argv[1], "int_handler") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		Dd_HDMAC_Int_Handler(priv->cdHdmac->ch);
	}else if (strcmp(argv[1], "sdram_sync") == 0) {
		/*
		 * priv->cdHdmac->ch number
		 */
		priv->cdHdmac->ch = atoi(argv[2]);

		priv->cdHdmac->srcAddr = strtoul(argv[3], &priv->cdHdmac->endstr, 16);
		priv->cdHdmac->dstAddr = strtoul(argv[4], &priv->cdHdmac->endstr, 16);
		priv->cdHdmac->size = atoi(argv[5]);

		if (strcmp(argv[6], "cpu") == 0 ){
			waitMode = D_DD_HDMAC_WAITMODE_CPU;
		}else if (strcmp(argv[6], "event") == 0) {
			waitMode = D_DD_HDMAC_WAITMODE_EVENT;
		}else {
			Ddim_Print(("Parameter ERR P6. waitMode=0x%x\n", waitMode));
			return ;
		}
		// pgr0539
		priv->cdHdmac->ret = Dd_HDMAC_Copy_SDRAM_Sync(priv->cdHdmac->ch,
				priv->cdHdmac->srcAddr, priv->cdHdmac->dstAddr, priv->cdHdmac->size, waitMode);
		if (priv->cdHdmac->ret == 0) {
			Ddim_Print(("HDMAC Util Copy Sync. OK\n"));
		}else {
			Ddim_Print(("HDMAC Util Copy Sync. ERR. ret=0x%x\n", priv->cdHdmac->ret));
		}
	}else {
		Ddim_Print(("please check 1st parameter!!\n"));
	}
	return;
}

CtDdHdmacMain* ct_dd_hdmac_main_new(void) 
{
    CtDdHdmacMain *self = k_object_new_with_private(CT_TYPE_DD_HDMAC_MAIN, sizeof(CtDdHdmacMainPrivate));
    return self;
}
