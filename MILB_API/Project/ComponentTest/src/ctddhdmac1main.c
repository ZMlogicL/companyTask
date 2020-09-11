/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :杨升柄
*@brief               :CtDdHdmac1Main类
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
#include "dd_hdmac1.h"
#include "ct_dd_hdmac1.h"
#include "dd_gic.h"
#include "ddim_user_custom.h"
#include <string.h>
#include "ctddhdmac1.h"
#include "ctddhdmac1main.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdHdmac1Main, ct_dd_hdmac1_main);
#define CT_DD_HDMAC1_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
	CtDdHdmac1MainPrivate,CT_TYPE_DD_HDMAC1_MAIN))

struct _CtDdHdmac1MainPrivate
{
	CtDdHdmac1 *hdmac1;
};

static void ct_dd_hdmac1_main_constructor(CtDdHdmac1Main *self) 
{
	CtDdHdmac1MainPrivate *priv = CT_DD_HDMAC1_MAIN_GET_PRIVATE(self);

	priv->hdmac1 = ct_dd_hdmac1_new();
}

static void ct_dd_hdmac1_main_destructor(CtDdHdmac1Main *self) 
{
	CtDdHdmac1MainPrivate *priv = CT_DD_HDMAC1_MAIN_GET_PRIVATE(self);

	if(priv->hdmac1)
	{
		k_object_unref(priv->hdmac1);
	}
	priv->hdmac1 = NULL;
}

/**
 * PUBLIC
 *
 * @brief  Command main function for HDMAC1 test.
 * @param  kint32 argc	:The number of parameters
 *		   kchar** argv	:The value of parameters
 *
 *	The meaning of parameters
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| P1              | P2       | P3         | P4       | P5         | P6         | P7       | P8 | P9 | P10 | P11 | Meaning                            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "open"          | priv->hdmac1->ch       | waitTime  |          |            |            |          |    |    |     |     | Dd_HDMAC1_Open()                   |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "close"         | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Close()                  |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_cmm"      | priv->hdmac1->ch       | src_addr   | dst_addr |            |            |          |    |    |     |     | Dd_HDMAC1_Ctrl_Common()            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_cmm_cfga" | priv->hdmac1->ch       | "soft"     | "normal" | bc         | tc         |          |    |    |     |     | Set DMACA                          |
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
 *	| "ctrl_cmm_cfgb" | priv->hdmac1->ch       | "blk"      | "1"      | "src_fix"  | "dst_fix"  | rc       | rs | rd | sp  | dp  | Set DMACB                          |
 *	|                 |          | "burst"    | "2"      | "src_incr" | "dst_incr" |          |    |    |     |     |                                    |
 *	|                 |          | "demand"   | "4"      |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_trns"     | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Ctrl_Trns()              |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_trns_md"  | priv->hdmac1->ch       | "soft"     | "blk"    | "src_fix"  | "dst_fix"  | "normal" |    |    |     |     | Set HDMAC1 transfer mode           |
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
 *	| "ctrl_trns_sz"  | priv->hdmac1->ch       | "1"        | size     | src_addr   | dst_addr   |          |    |    |     |     | Set HDMAC1 transfer size           |
 *	|                 |          | "2"        |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "4"        |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "start_sync"    | priv->hdmac1->ch       | "cpu"      |          |            |            |          |    |    |     |     | Dd_HDMAC1_Start_Sync()             |
 *	|                 |          | "event"    |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "start_async"   | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Start_Async()            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "stop"          | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Stop()                   |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "pause"         | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Pause()                  |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "resume"        | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Resume()                 |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "wait"          | priv->hdmac1->ch       | "cpu"      |          |            |            |          |    |    |     |     | Dd_HDMAC1_Wait_End()               |
 *	|                 |          | "event"    |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "set_wait_time" | priv->hdmac1->ch       | time       |          |            |            |          |    |    |     |     | Dd_HDMAC1_Set_Wait_Time()          |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "status_clear"  | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Clear_Status()           |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "status_read"   | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Get_Status()             |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "trns_size_set" | priv->hdmac1->ch       | "1"        | size     | src_addr   | dst_addr   |          |    |    |     |     | Dd_HDMAC1_Set_Trns_Size()          |
 *	|                 |          | "2"        |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "4"        |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "trns_size_get" | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Get_Trns_Size()          |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "rmn_size_get"  | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Get_Remain_Trns_Size()   |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "total_size_get"| priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Get_Total_Trns_Size()    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "src_addr_get"  | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Get_Src_Addr()           |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "dst_addr_get"  | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Get_Dst_Addr()           |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "src_prot_set"  | priv->hdmac1->ch       | sp         |          |            |            |          |    |    |     |     | Dd_HDMAC1_Set_Source_Protect()     |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "dst_prot_set"  | priv->hdmac1->ch       | dp         |          |            |            |          |    |    |     |     | Dd_HDMAC1_Set_Destination_Protect()|
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "arb_set"       | "rotate" |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Set_Arbitration()        |
 *	|                 | "fix"    |            |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "arb_get"       |          |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Get_Arbitration()        |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "arb_clear"     |          |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Clear_Arbitration()      |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "stop_all"      |          |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Stop_All_Ch()            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "resume_all"    |          |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Resume_All_Ch()          |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "get_width"     | src_addr | dst_addr   | size     |            |            |          |    |    |     |     | Dd_HDMAC1_Get_Trns_Width()         |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "int_set"       | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Set_Int_Handler()        |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "int_handler"   | priv->hdmac1->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC1_Int_Handler()            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "auto"          | num      |            |          |            |            |          |    |    |     |     | Continuous execution               |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "sdram_sync"    | priv->hdmac1->ch       | src_addr   | dst_addr | size       | "cpu"      |          |    |    |     |     | Dd_HDMAC1_Copy_SDRAM_Sync()        |
 *	|                 |          |            |          |            | "event"    |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "sdram_async"   | priv->hdmac1->ch       | src_addr   | dst_addr | size       |            |          |    |    |     |     | Dd_HDMAC1_Copy_SDRAM_Async()       |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *
 *			priv->hdmac1->ch			:	0          - 7
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
void ct_dd_hdmac1_main_test(CtDdHdmac1Main* self, kint argc, kchar** argv)
{
	CtDdHdmac1MainPrivate *	priv = CT_DD_HDMAC1_MAIN_GET_PRIVATE(self);
	kuint32									waitMode = D_DD_HDMAC1_WAITMODE_CPU;
	kulong										totalSize;
	kulong										transWidth = 0;
	kushort									status = 0;
	kuchar										prot;
	kuchar										arbType;
	kint32										waitTime;

	// check number of parameter
	if (argc > 12) {
		Ddim_Print(("The number of input parameters is exceeded!\n"));
		return;
	}

	ct_dd_hdmac1_from_main(priv->hdmac1, argc, argv);

	if (strcmp(argv[1], "open") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);
		waitTime = atoi(argv[3]);

		priv->hdmac1->ret = Dd_HDMAC1_Open(priv->hdmac1->ch, waitTime);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Open OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Open ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "close") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->ret = Dd_HDMAC1_Close(priv->hdmac1->ch);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Close OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Close ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "ctrl_cmm_cfgb") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.word = 0;

		// Set MS
		if (strcmp(argv[3], "blk") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.ms = D_DD_HDMAC1_MS_BLK;
		}else if (strcmp(argv[3], "burst") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.ms = D_DD_HDMAC1_MS_BURST;
		}else if (strcmp(argv[3], "demand") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.ms = D_DD_HDMAC1_MS_DEMAND;
		}else
		{
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}

		// Set TW
		if (strcmp(argv[4], "1") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.tw = D_DD_HDMAC1_TW_BYTE;
		}else if (strcmp(argv[4], "2") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.tw = D_DD_HDMAC1_TW_HWORD;
		}else if (strcmp(argv[4], "4") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.tw = D_DD_HDMAC1_TW_WORD;
		}else
		{
			Ddim_Print(("Parameter ERR. P4 \n"));
			return;
		}

		// Set FS
		if (strcmp(argv[5], "src_fix") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.fs = D_DD_HDMAC1_FS_FIX;
		}else if (strcmp(argv[5], "src_incr") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.fs = D_DD_HDMAC1_FS_INCR;
		}else
		{
			Ddim_Print(("Parameter ERR. P5 \n"));
			return;
		}

		// Set FD
		if (strcmp(argv[6], "dst_fix") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.fs = D_DD_HDMAC1_FD_FIX;
		}else if (strcmp(argv[6], "dst_incr") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.fs = D_DD_HDMAC1_FD_INCR;
		}else
		{
			Ddim_Print(("Parameter ERR. P6 \n"));
			return;
		}

		// Set RC
		if (strcmp(argv[7], "ena") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.rc = D_DD_HDMAC1_RC_ENABLE;
		}else if (strcmp(argv[7], "dis") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.rc = D_DD_HDMAC1_RC_DISABLE;
		}else
		{
			Ddim_Print(("Parameter ERR. P7 \n"));
			return;
		}

		// Set RS
		if (strcmp(argv[8], "ena") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.rs = D_DD_HDMAC1_RS_ENABLE;
		}else if (strcmp(argv[8], "dis") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.rs = D_DD_HDMAC1_RS_DISABLE;
		}else
		{
			Ddim_Print(("Parameter ERR. P8 \n"));
			return;
		}

		// Set RD
		if (strcmp(argv[9], "ena") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.rd = D_DD_HDMAC1_RD_ENABLE;
		}else if (strcmp(argv[9], "dis") == 0) {
			priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.rd = D_DD_HDMAC1_RD_DISABLE;
		}else
		{
			Ddim_Print(("Parameter ERR. P9 \n"));
			return;
		}

		// Set SP
		priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.sp = atoi(argv[10]);

		// Set DP
		priv->hdmac1->gHdmac1Ctrl[priv->hdmac1->ch].config_b.bit.dp = atoi(argv[11]);
	}else if (strcmp(argv[1], "ctrl_trns_sz") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		// Set TW
		if (strcmp(argv[3], "1") == 0) {
			priv->hdmac1->gHdmac1CtrlTrns[priv->hdmac1->ch].size.trns_width = D_DD_HDMAC1_TW_BYTE;
		}else if (strcmp(argv[3], "2") == 0) {
			priv->hdmac1->gHdmac1CtrlTrns[priv->hdmac1->ch].size.trns_width = D_DD_HDMAC1_TW_HWORD;
		}else if (strcmp(argv[3], "4") == 0) {
			priv->hdmac1->gHdmac1CtrlTrns[priv->hdmac1->ch].size.trns_width = D_DD_HDMAC1_TW_WORD;
		}else
		{
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}

		// Set Size
		priv->hdmac1->gHdmac1CtrlTrns[priv->hdmac1->ch].size.trns_size = atoi(argv[4]);

		priv->hdmac1->gHdmac1CtrlTrns[priv->hdmac1->ch].size.src_addr = strtoul(argv[5], &priv->hdmac1->endstr, 16);

		priv->hdmac1->gHdmac1CtrlTrns[priv->hdmac1->ch].size.dst_addr = strtoul(argv[6], &priv->hdmac1->endstr, 16);
	}else if (strcmp(argv[1], "start_sync") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		if (strcmp(argv[3], "cpu") == 0) {
			waitMode = D_DD_HDMAC1_WAITMODE_CPU;
		}else if (strcmp(argv[3], "event") == 0) {
			waitMode = D_DD_HDMAC1_WAITMODE_EVENT;
		}else
		{
			Ddim_Print(("Parameter ERR P3. waitMode=0x%x\n", waitMode));
			return ;
		}

		priv->hdmac1->ret = Dd_HDMAC1_Start_Sync(priv->hdmac1->ch, &status, waitMode);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Start Sync OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Start Sync ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
		Ddim_Print(("status=0x%x\n", status));
	}else if (strcmp(argv[1], "start_async") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->ret = Dd_HDMAC1_Start_Async(priv->hdmac1->ch);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Start Async OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Start Async ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "stop") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->ret = Dd_HDMAC1_Stop(priv->hdmac1->ch);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Stop OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Stop ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "pause") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->ret = Dd_HDMAC1_Pause(priv->hdmac1->ch);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Pause OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Pause ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "resume") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->ret = Dd_HDMAC1_Resume(priv->hdmac1->ch);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Resume OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Resume ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "wait") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		if (strcmp(argv[3], "cpu") == 0 ){
			waitMode = D_DD_HDMAC1_WAITMODE_CPU;
		}else if (strcmp(argv[3], "event") == 0) {
			waitMode = D_DD_HDMAC1_WAITMODE_EVENT;
		}else
		{
			Ddim_Print(("Parameter ERR P3. waitMode=0x%x\n", waitMode));
			return ;
		}

		priv->hdmac1->ret = Dd_HDMAC1_Wait_End(priv->hdmac1->ch, &status, waitMode);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Wait OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Wait ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
		Ddim_Print(("status=0x%x\n", status));
	}else if (strcmp(argv[1], "set_wait_time") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);
		kint32 waitTime = atoi(argv[3]);

		priv->hdmac1->ret = Dd_HDMAC1_Set_Wait_Time(priv->hdmac1->ch, waitTime);
		if ( priv->hdmac1->ret == D_DDIM_OK ) {
			Ddim_Print(("HDMAC1 Set Wait Time OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Set Wait Time ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "status_clear") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->ret = Dd_HDMAC1_Clear_Status(priv->hdmac1->ch);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Status Clear OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Status Clear ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "status_read") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->ret = Dd_HDMAC1_Get_Status(priv->hdmac1->ch, &status);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Get Status OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Get Status ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
		Ddim_Print(("status=0x%x\n", status));
	}else if (strcmp(argv[1], "trns_size_set") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		// Set TW
		if (strcmp(argv[3], "1") == 0) {
			priv->hdmac1->gHdmac1TrnsSize[priv->hdmac1->ch].trns_width = D_DD_HDMAC1_TW_BYTE;
		}else if (strcmp(argv[3], "2") == 0) {
			priv->hdmac1->gHdmac1TrnsSize[priv->hdmac1->ch].trns_width = D_DD_HDMAC1_TW_HWORD;
		}else if (strcmp(argv[3], "4") == 0) {
			priv->hdmac1->gHdmac1TrnsSize[priv->hdmac1->ch].trns_width = D_DD_HDMAC1_TW_WORD;
		}else
		{
			Ddim_Print(("Parameter ERR. P3 \n"));
			return;
		}
		priv->hdmac1->gHdmac1TrnsSize[priv->hdmac1->ch].trns_size = atoi(argv[4]);
		priv->hdmac1->gHdmac1TrnsSize[priv->hdmac1->ch].src_addr = strtoul(argv[5], &priv->hdmac1->endstr, 16);
		priv->hdmac1->gHdmac1TrnsSize[priv->hdmac1->ch].dst_addr = strtoul(argv[6], &priv->hdmac1->endstr, 16);

		priv->hdmac1->ret = Dd_HDMAC1_Set_Trns_Size(priv->hdmac1->ch, &priv->hdmac1->gHdmac1TrnsSize[priv->hdmac1->ch]);
		if ( priv->hdmac1->ret == D_DDIM_OK ) {
			Ddim_Print(("HDMAC1 Set Trans Size OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Set Trans Size ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "trns_size_get") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->size = Dd_HDMAC1_Get_Trns_Size(priv->hdmac1->ch);
		Ddim_Print(("HDMAC1 Trans Size Get OK\n"));
		Ddim_Print(("Size=%d\n", priv->hdmac1->size));
	}else if (strcmp(argv[1], "rmn_size_get") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->size = Dd_HDMAC1_Get_Remain_Trns_Size(priv->hdmac1->ch);
		Ddim_Print(("HDMAC1 Remain Trans Size OK\n"));
		Ddim_Print(("Size=%d\n", priv->hdmac1->size));
	}else if (strcmp(argv[1], "total_size_get") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->size = Dd_HDMAC1_Get_Total_Trns_Size(priv->hdmac1->ch);
		Ddim_Print(("HDMAC1 Total Trans Size OK\n"));
		Ddim_Print(("Size=%d\n", priv->hdmac1->size));
	}else if (strcmp(argv[1], "src_addr_get") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->srcAddr = Dd_HDMAC1_Get_Src_Addr(priv->hdmac1->ch);
		Ddim_Print(("HDMAC1 Source Address OK\n"));
		Ddim_Print(("Src Addr=0x%08lx\n", priv->hdmac1->srcAddr));
	}else if (strcmp(argv[1], "dst_addr_get") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->dstAddr = Dd_HDMAC1_Get_Dst_Addr(priv->hdmac1->ch);
		Ddim_Print(("HDMAC1 Destination Address OK\n"));
		Ddim_Print(("Dst Addr=0x%08lx\n", priv->hdmac1->dstAddr));
	}else if (strcmp(argv[1], "src_prot_set") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);
		prot = atoi(argv[3]);

		priv->hdmac1->ret = Dd_HDMAC1_Set_Source_Protect(priv->hdmac1->ch, prot);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Source Protect Set OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Source Protect Set ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "dst_prot_set") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);
		prot = atoi(argv[3]);

		priv->hdmac1->ret = Dd_HDMAC1_Set_Destination_Protect(priv->hdmac1->ch, prot);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Destination Protect Set OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Destination Protect Set ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "arb_set") == 0) {
		if (strcmp(argv[2], "rotate") == 0) {
			arbType = D_DD_HDMAC1_ARB_ROTATE;
		}else if (strcmp(argv[2], "fix") == 0) {
			arbType = D_DD_HDMAC1_ARB_FIX;
		}else
		{
			Ddim_Print(("Parameter ERR P2. \n"));
			return;
		}

		priv->hdmac1->ret = Dd_HDMAC1_Set_Arbitration(arbType);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Arbitration Set OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Arbitration Set ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "arb_get") == 0) {
		priv->hdmac1->ret = Dd_HDMAC1_Get_Arbitration(&arbType);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Arbitration Read OK\n"));
			Ddim_Print(("arbType=0x%x\n", arbType));
		}else
		{
			Ddim_Print(("HDMAC1 Arbitration Read ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if (strcmp(argv[1], "arb_clear") == 0) {
		Dd_HDMAC1_Clear_Arbitration();
	}else if (strcmp(argv[1], "stop_all") == 0) {
		Dd_HDMAC1_Stop_All_Ch();
	}else if (strcmp(argv[1], "resume_all") == 0) {
		Dd_HDMAC1_Resume_All_Ch();
	}else if (strcmp(argv[1], "get_width") == 0) {
		priv->hdmac1->srcAddr = strtoul(argv[2], &priv->hdmac1->endstr, 16);
		priv->hdmac1->dstAddr = strtoul(argv[3], &priv->hdmac1->endstr, 16);
		totalSize = atoi(argv[4]);
		// pgr0539
		transWidth = Dd_HDMAC1_Get_Trns_Width(priv->hdmac1->srcAddr, priv->hdmac1->dstAddr, totalSize);
		Ddim_Print(("HDMAC1 Trans Width Get OK\n"));
		Ddim_Print(("transWidth=%lu\n", transWidth));
	}else if (strcmp(argv[1], "int_handler") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		Dd_HDMAC1_Int_Handler(priv->hdmac1->ch);
	}else if (strcmp(argv[1], "sdram_sync") == 0) {
		// priv->hdmac1->ch number
		priv->hdmac1->ch = atoi(argv[2]);

		priv->hdmac1->srcAddr = strtoul(argv[3], &priv->hdmac1->endstr, 16);
		priv->hdmac1->dstAddr = strtoul(argv[4], &priv->hdmac1->endstr, 16);
		priv->hdmac1->size = atoi(argv[5]);

		if (strcmp(argv[6], "cpu") == 0 ){
			waitMode = D_DD_HDMAC1_WAITMODE_CPU;
		}else if (strcmp(argv[6], "event") == 0) {
			waitMode = D_DD_HDMAC1_WAITMODE_EVENT;
		}else
		{
			Ddim_Print(("Parameter ERR P6. waitMode=0x%x\n", waitMode));
			return ;
		}
		// pgr0539
		priv->hdmac1->ret = Dd_HDMAC1_Copy_SDRAM_Sync(priv->hdmac1->ch,
				priv->hdmac1->srcAddr, priv->hdmac1->dstAddr, priv->hdmac1->size, waitMode);
		if (priv->hdmac1->ret == 0) {
			Ddim_Print(("HDMAC1 Util Copy Sync. OK\n"));
		}else
		{
			Ddim_Print(("HDMAC1 Util Copy Sync. ERR. priv->hdmac1->ret=0x%x\n", priv->hdmac1->ret));
		}
	}else if(strcmp(argv[1], "cmp") == 0) {
		Ddim_Print(("cmp = %d\n", memcmp((void*)strtoul(argv[2], &priv->hdmac1->endstr, 16),
				(void*)strtoul(argv[3], &priv->hdmac1->endstr, 16), atoi(argv[4]))));
	}else
	{
		Ddim_Print(("please check 1st parameter!!\n"));
	}
	return;
}

CtDdHdmac1Main* ct_dd_hdmac1_main_new(void) 
{
    CtDdHdmac1Main *self = k_object_new_with_private(CT_TYPE_DD_HDMAC1_MAIN, sizeof(CtDdHdmac1MainPrivate));
    return self;
}
