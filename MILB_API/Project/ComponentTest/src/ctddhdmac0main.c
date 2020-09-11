/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :杨升柄
*@brief               :CtDdHdmac0Main类
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
#include "ctddhdmac0main.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdHdmac0Main, ct_dd_hdmac0_main);
#define CT_DD_HDMAC0_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtDdHdmac0MainPrivate,CT_TYPE_DD_HDMAC0_MAIN))

struct _CtDdHdmac0MainPrivate
{
	CtDdHdmac0 *hdma0;
};

static void ct_dd_hdmac0_main_constructor(CtDdHdmac0Main *self) 
{
	CtDdHdmac0MainPrivate *priv = CT_DD_HDMAC0_MAIN_GET_PRIVATE(self);
	priv->hdma0 = ct_dd_hdmac0_new();
}

static void ct_dd_hdmac0_main_destructor(CtDdHdmac0Main *self) 
{
	CtDdHdmac0MainPrivate *priv = CT_DD_HDMAC0_MAIN_GET_PRIVATE(self);
	if(priv->hdma0)
	{
		k_object_unref(priv->hdma0);
	}
	priv->hdma0 = NULL;
}

/**
 * PUBLIC
 *
 * @brief  Command main function for HDMAC0 test.
 * @param  kint32 argc	:The number of parameters
 *		   kchar** argv	:The value of parameters#include "dd_hdmac.h"
 *
 *	The meaning of parameters
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| P1              | P2       | P3         | P4       | P5         | P6         | P7       | P8 | P9 | P10 | P11 | Meaning                            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "open"          | priv->hdma0->ch       | wait_time  |          |            |            |          |    |    |     |     | Dd_HDMAC0_Open()                   |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "close"         | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Close()                  |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_cmm"      | priv->hdma0->ch       | src_addr   | dst_addr |            |            |          |    |    |     |     | Dd_HDMAC0_Ctrl_Common()            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_cmm_cfga" | priv->hdma0->ch       | "soft"     | "normal" | bc         | tc         |          |    |    |     |     | Set DMACA                          |
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
 *	| "ctrl_cmm_cfgb" | priv->hdma0->ch       | "blk"      | "1"      | "src_fix"  | "dst_fix"  | rc       | rs | rd | sp  | dp  | Set DMACB                          |
 *	|                 |          | "burst"    | "2"      | "src_incr" | "dst_incr" |          |    |    |     |     |                                    |
 *	|                 |          | "demand"   | "4"      |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_trns"     | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Ctrl_Trns()              |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "ctrl_trns_md"  | priv->hdma0->ch       | "soft"     | "blk"    | "src_fix"  | "dst_fix"  | "normal" |    |    |     |     | Set HDMAC0 transfer mode           |
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
 *	| "ctrl_trns_sz"  | priv->hdma0->ch       | "1"        | size     | src_addr   | dst_addr   |          |    |    |     |     | Set HDMAC0 transfer size           |
 *	|                 |          | "2"        |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "4"        |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "start_sync"    | priv->hdma0->ch       | "cpu"      |          |            |            |          |    |    |     |     | Dd_HDMAC0_Start_Sync()             |
 *	|                 |          | "event"    |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "start_async"   | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Start_Async()            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "stop"          | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Stop()                   |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "pause"         | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Pause()                  |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "resume"        | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Resume()                 |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "wait"          | priv->hdma0->ch       | "cpu"      |          |            |            |          |    |    |     |     | Dd_HDMAC0_Wait_End()               |
 *	|                 |          | "event"    |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "set_wait_time" | priv->hdma0->ch       | time       |          |            |            |          |    |    |     |     | Dd_HDMAC0_Set_Wait_Time()          |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "status_clear"  | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Clear_Status()           |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "status_read"   | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Get_Status()             |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "trns_size_set" | priv->hdma0->ch       | "1"        | size     | src_addr   | dst_addr   |          |    |    |     |     | Dd_HDMAC0_Set_Trns_Size()          |
 *	|                 |          | "2"        |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "4"        |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "trns_size_get" | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Get_Trns_Size()          |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "rmn_size_get"  | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Get_Remain_Trns_Size()   |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "total_size_get"| priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Get_Total_Trns_Size()    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "src_addr_get"  | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Get_Src_Addr()           |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "dst_addr_get"  | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Get_Dst_Addr()           |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "src_prot_set"  | priv->hdma0->ch       | sp         |          |            |            |          |    |    |     |     | Dd_HDMAC0_Set_Source_Protect()     |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "dst_prot_set"  | priv->hdma0->ch       | dp         |          |            |            |          |    |    |     |     | Dd_HDMAC0_Set_Destination_Protect()|
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "arb_set"       | "rotate" |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Set_Arbitration()        |
 *	|                 | "fix"    |            |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "arb_get"       |          |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Get_Arbitration()        |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "arb_clear"     |          |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Clear_Arbitration()      |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "stop_all"      |          |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Stop_All_Ch()            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "resume_all"    |          |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Resume_All_Ch()          |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "get_width"     | src_addr | dst_addr   | size     |            |            |          |    |    |     |     | Dd_HDMAC0_Get_Trns_Width()         |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "int_set"       | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Set_Int_Handler()        |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "int_handler"   | priv->hdma0->ch       |            |          |            |            |          |    |    |     |     | Dd_HDMAC0_Int_Handler()            |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "auto"          | num      |            |          |            |            |          |    |    |     |     | Continuous execution               |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "sdram_sync"    | priv->hdma0->ch       | src_addr   | dst_addr | size       | "cpu"      |          |    |    |     |     | Dd_HDMAC0_Copy_SDRAM_Sync()        |
 *	|                 |          |            |          |            | "event"    |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "sdram_async"   | priv->hdma0->ch       | src_addr   | dst_addr | size       |            |          |    |    |     |     | Dd_HDMAC0_Copy_SDRAM_Async()       |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *	| "in_audio"      | priv->hdma0->ch       | "soft"     | src_addr | dst_addr   | size       |          |    |    |     |     | Dd_HDMAC0_Input_Audio_Async()      |
 *	|                 |          | "dreq_h"   |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "dreq_l"   |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_0"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_1"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_2"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_3"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_4"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_5"  |          |            |            |          |    |    |     |     |                                    |
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
 *	| "out_audio"     | priv->hdma0->ch       | "soft"     | src_addr | dst_addr   | size       |          |    |    |     |     | Dd_HDMAC0_Output_Audio_Async()     |
 *	|                 |          | "dreq_h"   |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "dreq_l"   |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_0"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_1"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_2"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_3"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_4"  |          |            |            |          |    |    |     |     |                                    |
 *	|                 |          | "idreq_5"  |          |            |            |          |    |    |     |     |                                    |
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
 *	| "err"           |          |            |          |            |            |          |    |    |     |     |                                    |
 *	+-----------------+----------+------------+----------+------------+------------+----------+----+----+-----+-----+------------------------------------+
 *
 *			priv->hdma0->ch			:	0          - 7
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
void ct_dd_hdmac0_main_test(CtDdHdmac0Main* self, kint argc, kchar** argv)
 {
	CtDdHdmac0MainPrivate *priv = CT_DD_HDMAC0_MAIN_GET_PRIVATE(self);

 	kuint32								waitMode = D_DD_HDMAC0_WAITMODE_CPU;
 	kulong									totalSize;
 	kulong									transWidth = 0;
 	kushort								status = 0;
 	kuchar									prot;
 	kuchar									arbType;


 	// check number of parameter
 	if (argc > 12) {
 		Ddim_Print(("The number of input parameters is exceeded!\n"));
 		return;
 	}

 	//main函数拆分出去的
 	ct_dd_hdmac0_from_main(priv->hdma0, argc, argv);

    if (strcmp(argv[1], "ctrl_trns") == 0) {
 		/* priv->hdma0->ch number */
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->gHdmac0CtrlTrns[priv->hdma0->ch].int_handler = ct_hdmac0_callback;

 		priv->hdma0->ret = Dd_HDMAC0_Ctrl_Trns(priv->hdma0->ch, &priv->hdma0->gHdmac0CtrlTrns[priv->hdma0->ch]);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Ctrl_Trns OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Ctrl_Trns ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "ctrl_trns_sz") == 0) {
 		/* priv->hdma0->ch number */
 		priv->hdma0->ch = atoi(argv[2]);

 		// Set TW
 		if (strcmp(argv[3], "1") == 0) {
 			priv->hdma0->gHdmac0CtrlTrns[priv->hdma0->ch].size.trns_width = D_DD_HDMAC0_TW_BYTE;
 		}
 		else if (strcmp(argv[3], "2") == 0) {
 			priv->hdma0->gHdmac0CtrlTrns[priv->hdma0->ch].size.trns_width = D_DD_HDMAC0_TW_HWORD;
 		}
 		else if (strcmp(argv[3], "4") == 0) {
 			priv->hdma0->gHdmac0CtrlTrns[priv->hdma0->ch].size.trns_width = D_DD_HDMAC0_TW_WORD;
 		}else
 		{
 			Ddim_Print(("Parameter ERR. P3 \n"));
 			return;
 		}

 		// Set Size
 		priv->hdma0->gHdmac0CtrlTrns[priv->hdma0->ch].size.trns_size = atoi(argv[4]);

 		priv->hdma0->gHdmac0CtrlTrns[priv->hdma0->ch].size.src_addr = strtoul(argv[5], &priv->hdma0->endstr, 16);

 		priv->hdma0->gHdmac0CtrlTrns[priv->hdma0->ch].size.dst_addr = strtoul(argv[6], &priv->hdma0->endstr, 16);
 	}else if (strcmp(argv[1], "start_sync") == 0) {
 		/* priv->hdma0->ch number */
 		priv->hdma0->ch = atoi(argv[2]);

 		if (strcmp(argv[3], "cpu") == 0) {
 			waitMode = D_DD_HDMAC0_WAITMODE_CPU;
 		}
 		else if (strcmp(argv[3], "event") == 0) {
 			waitMode = D_DD_HDMAC0_WAITMODE_EVENT;
 		}else
 		{
 			Ddim_Print(("Parameter ERR P3. waitMode=0x%x\n", waitMode));
 			return ;
 		}

 		priv->hdma0->ret = Dd_HDMAC0_Start_Sync(priv->hdma0->ch, &status, waitMode);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Start Sync OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Start Sync ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 		Ddim_Print(("status=0x%x\n", status));
 	}else if (strcmp(argv[1], "start_async") == 0) {
 		/* priv->hdma0->ch number */
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->ret = Dd_HDMAC0_Start_Async(priv->hdma0->ch);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Start Async OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Start Async ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "stop") == 0) {
 		/* priv->hdma0->ch number */
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->ret = Dd_HDMAC0_Stop(priv->hdma0->ch);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Stop OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Stop ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "pause") == 0) {
 		/* priv->hdma0->ch number */
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->ret = Dd_HDMAC0_Pause(priv->hdma0->ch);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Pause OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Pause ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "resume") == 0) {
 		/* priv->hdma0->ch number */
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->ret = Dd_HDMAC0_Resume(priv->hdma0->ch);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Resume OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Resume ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "wait") == 0) {
 		/* priv->hdma0->ch number */
 		priv->hdma0->ch = atoi(argv[2]);

 		if (strcmp(argv[3], "cpu") == 0 ){
 			waitMode = D_DD_HDMAC0_WAITMODE_CPU;
 		}
 		else if (strcmp(argv[3], "event") == 0) {
 			waitMode = D_DD_HDMAC0_WAITMODE_EVENT;
 		}else
 		{
 			Ddim_Print(("Parameter ERR P3. waitMode=0x%x\n", waitMode));
 			return ;
 		}

 		priv->hdma0->ret = Dd_HDMAC0_Wait_End(priv->hdma0->ch, &status, waitMode);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Wait OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Wait ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 		Ddim_Print(("status=0x%x\n", status));
 	}else if (strcmp(argv[1], "set_wait_time") == 0) {
 		/* priv->hdma0->ch number */
 		priv->hdma0->ch = atoi(argv[2]);
 		kint32 wait_time = atoi(argv[3]);

 		priv->hdma0->ret = Dd_HDMAC0_Set_Wait_Time(priv->hdma0->ch, wait_time);
 		if ( priv->hdma0->ret == D_DDIM_OK ) {
 			Ddim_Print(("HDMAC0 Set Wait Time OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Set Wait Time ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "status_clear") == 0) {
 		/* priv->hdma0->ch number */
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->ret = Dd_HDMAC0_Clear_Status(priv->hdma0->ch);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Status Clear OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Status Clear ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "status_read") == 0) {
 		/* priv->hdma0->ch number */
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->ret = Dd_HDMAC0_Get_Status(priv->hdma0->ch, &status);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Get Status OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Get Status ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 		Ddim_Print(("status=0x%x\n", status));
 	}else if (strcmp(argv[1], "trns_size_set") == 0) {
 		/* priv->hdma0->ch number */
 		priv->hdma0->ch = atoi(argv[2]);

 		// Set TW
 		if (strcmp(argv[3], "1") == 0) {
 			priv->hdma0->gHdmac0TrnsSize[priv->hdma0->ch].trns_width = D_DD_HDMAC0_TW_BYTE;
 		}
 		else if (strcmp(argv[3], "2") == 0) {
 			priv->hdma0->gHdmac0TrnsSize[priv->hdma0->ch].trns_width = D_DD_HDMAC0_TW_HWORD;
 		}
 		else if (strcmp(argv[3], "4") == 0) {
 			priv->hdma0->gHdmac0TrnsSize[priv->hdma0->ch].trns_width = D_DD_HDMAC0_TW_WORD;
 		}else
 		{
 			Ddim_Print(("Parameter ERR. P3 \n"));
 			return;
 		}
 		priv->hdma0->gHdmac0TrnsSize[priv->hdma0->ch].trns_size = atoi(argv[4]);
 		priv->hdma0->gHdmac0TrnsSize[priv->hdma0->ch].src_addr = strtoul(argv[5], &priv->hdma0->endstr, 16);
 		priv->hdma0->gHdmac0TrnsSize[priv->hdma0->ch].dst_addr = strtoul(argv[6], &priv->hdma0->endstr, 16);

 		priv->hdma0->ret = Dd_HDMAC0_Set_Trns_Size(priv->hdma0->ch, &priv->hdma0->gHdmac0TrnsSize[priv->hdma0->ch]);
 		if ( priv->hdma0->ret == D_DDIM_OK ) {
 			Ddim_Print(("HDMAC0 Set Trans Size OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Set Trans Size ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "trns_size_get") == 0) {
 		// priv->hdma0->ch number
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->size = Dd_HDMAC0_Get_Trns_Size(priv->hdma0->ch);
 		Ddim_Print(("HDMAC0 Trans Size Get OK\n"));
 		Ddim_Print(("Size=%d\n", priv->hdma0->size));
 	}else if (strcmp(argv[1], "rmn_size_get") == 0) {
 		//priv->hdma0->ch number
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->size = Dd_HDMAC0_Get_Remain_Trns_Size(priv->hdma0->ch);
 		Ddim_Print(("HDMAC0 Remain Trans Size OK\n"));
 		Ddim_Print(("Size=%d\n", priv->hdma0->size));
 	}else if (strcmp(argv[1], "total_size_get") == 0) {
 		// priv->hdma0->ch number
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->size = Dd_HDMAC0_Get_Total_Trns_Size(priv->hdma0->ch);
 		Ddim_Print(("HDMAC0 Total Trans Size OK\n"));
 		Ddim_Print(("Size=%d\n", priv->hdma0->size));
 	}else if (strcmp(argv[1], "src_addr_get") == 0) {
 		// priv->hdma0->ch number
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->srcAddr = Dd_HDMAC0_Get_Src_Addr(priv->hdma0->ch);
 		Ddim_Print(("HDMAC0 Source Address OK\n"));
 		Ddim_Print(("Src Addr=0x%08lx\n", priv->hdma0->srcAddr));
 	}else if (strcmp(argv[1], "dst_addr_get") == 0) {
 		// priv->hdma0->ch number
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->dstAddr = Dd_HDMAC0_Get_Dst_Addr(priv->hdma0->ch);
 		Ddim_Print(("HDMAC0 Destination Address OK\n"));
 		Ddim_Print(("Dst Addr=0x%08lx\n", priv->hdma0->dstAddr));
 	}else if (strcmp(argv[1], "src_prot_set") == 0) {
 		// priv->hdma0->ch number
 		priv->hdma0->ch = atoi(argv[2]);
 		prot = atoi(argv[3]);

 		priv->hdma0->ret = Dd_HDMAC0_Set_Source_Protect(priv->hdma0->ch, prot);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Source Protect Set OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Source Protect Set ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "dst_prot_set") == 0) {
 		// priv->hdma0->ch number
 		priv->hdma0->ch = atoi(argv[2]);
 		prot = atoi(argv[3]);

 		priv->hdma0->ret = Dd_HDMAC0_Set_Destination_Protect(priv->hdma0->ch, prot);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Destination Protect Set OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Destination Protect Set ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "arb_set") == 0) {
 		if (strcmp(argv[2], "rotate") == 0) {
 			arbType = D_DD_HDMAC0_ARB_ROTATE;
 		}
 		else if (strcmp(argv[2], "fix") == 0) {
 			arbType = D_DD_HDMAC0_ARB_FIX;
 		}else
 		{
 			Ddim_Print(("Parameter ERR P2. \n"));
 			return;
 		}

 		priv->hdma0->ret = Dd_HDMAC0_Set_Arbitration(arbType);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Arbitration Set OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Arbitration Set ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "arb_get") == 0) {
 		priv->hdma0->ret = Dd_HDMAC0_Get_Arbitration(&arbType);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Arbitration Read OK\n"));
 			Ddim_Print(("arbType=0x%x\n", arbType));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Arbitration Read ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "arb_clear") == 0) {
 		Dd_HDMAC0_Clear_Arbitration();
 	}else if (strcmp(argv[1], "stop_all") == 0) {
 		Dd_HDMAC0_Stop_All_Ch();
 	}else if (strcmp(argv[1], "resume_all") == 0) {
 		Dd_HDMAC0_Resume_All_Ch();
 	}else if (strcmp(argv[1], "get_width") == 0) {
 		priv->hdma0->srcAddr = strtoul(argv[2], &priv->hdma0->endstr, 16);
 		priv->hdma0->dstAddr = strtoul(argv[3], &priv->hdma0->endstr, 16);
 		totalSize = atoi(argv[4]);

 		transWidth = Dd_HDMAC0_Get_Trns_Width(priv->hdma0->srcAddr, priv->hdma0->dstAddr, totalSize);	/* pgr0539 */
 		Ddim_Print(("HDMAC0 Trans Width Get OK\n"));
 		Ddim_Print(("transWidth=%lu\n", transWidth));
 	}else if (strcmp(argv[1], "int_set") == 0) {
 		// priv->hdma0->ch number
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->intHandler = ct_hdmac0_callback;

 		Dd_HDMAC0_Set_Int_Handler(priv->hdma0->ch, priv->hdma0->intHandler);
 	}else if (strcmp(argv[1], "int_handler") == 0) {
 		// priv->hdma0->ch number
 		priv->hdma0->ch = atoi(argv[2]);

 		Dd_HDMAC0_Int_Handler(priv->hdma0->ch);
 	}else if (strcmp(argv[1], "sdram_sync") == 0) {
 		// priv->hdma0->ch number
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->srcAddr = strtoul(argv[3], &priv->hdma0->endstr, 16);
 		priv->hdma0->dstAddr = strtoul(argv[4], &priv->hdma0->endstr, 16);
 		priv->hdma0->size = atoi(argv[5]);

 		if (strcmp(argv[6], "cpu") == 0 ){
 			waitMode = D_DD_HDMAC0_WAITMODE_CPU;
 		}
 		else if (strcmp(argv[6], "event") == 0) {
 			waitMode = D_DD_HDMAC0_WAITMODE_EVENT;
 		}else
 		{
 			Ddim_Print(("Parameter ERR P6. waitMode=0x%x\n", waitMode));
 			return ;
 		}
 		// pgr0539
 		priv->hdma0->ret = Dd_HDMAC0_Copy_SDRAM_Sync(priv->hdma0->ch, priv->hdma0->srcAddr,
 				priv->hdma0->dstAddr, priv->hdma0->size, waitMode);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Util Copy Sync. OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Util Copy Sync. ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if (strcmp(argv[1], "sdram_async") == 0) {
 		// priv->hdma0->ch number
 		priv->hdma0->ch = atoi(argv[2]);

 		priv->hdma0->srcAddr = strtoul(argv[3], &priv->hdma0->endstr, 16);
 		priv->hdma0->dstAddr = strtoul(argv[4], &priv->hdma0->endstr, 16);
 		priv->hdma0->size = atoi(argv[5]);
 		priv->hdma0->intHandler = ct_hdmac0_callback;
 		// pgr0539
 		priv->hdma0->ret = Dd_HDMAC0_Copy_SDRAM_Async(priv->hdma0->ch,
 				priv->hdma0->srcAddr, priv->hdma0->dstAddr, priv->hdma0->size, priv->hdma0->intHandler);
 		if (priv->hdma0->ret == 0) {
 			Ddim_Print(("HDMAC0 Util Copy Async. OK\n"));
 		}else
 		{
 			Ddim_Print(("HDMAC0 Util Copy Async. ERR. ret=0x%x\n", priv->hdma0->ret));
 		}
 	}else if(strcmp(argv[1], "cmp") == 0) {
 		Ddim_Print(("cmp = %d\n", memcmp((void*)strtoul(argv[2], &priv->hdma0->endstr, 16),
 				(void*)strtoul(argv[3], &priv->hdma0->endstr, 16), atoi(argv[4]))));
 	}else if (strcmp(argv[1], "err") == 0){
 		T_DD_HDMAC0_CTRL      		hdmac0Ctrl;
 		T_DD_HDMAC0_CTRL_TRNS	hdmac0CtrlTrns;
 		T_DD_HDMAC0_TRNS_SIZE 	hdmac0TrnsSize;
 		kushort 									status;

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

 		hdmac0TrnsSize.trns_width = D_DD_HDMAC0_TW_BYTE;
 		hdmac0TrnsSize.trns_size = CtDdHdmac0_AUTO_TEST_SIZE;
 		hdmac0TrnsSize.src_addr  = CtDdHdmac0_AUTO_TEST_ADR_SRC;
 		hdmac0TrnsSize.dst_addr  = CtDdHdmac0_AUTO_TEST_ADR_DST;

 		priv->hdma0->ret = Dd_HDMAC0_Open(D_DD_HDMAC0_CH_NUM_MAX, D_DDIM_USER_SEM_WAIT_POL);
 		Ddim_Print(("Dd_HDMAC0_Open(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Close(D_DD_HDMAC0_CH_NUM_MAX);
 		Ddim_Print(("Dd_HDMAC0_Close(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Ctrl_Common(D_DD_HDMAC0_CH_NUM_MAX, &hdmac0Ctrl);
 		Ddim_Print(("Dd_HDMAC0_Ctrl_Common(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Ctrl_Common(0, NULL);
 		Ddim_Print(("Dd_HDMAC0_Ctrl_Common(): ctrl is NULL. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Ctrl_Trns(D_DD_HDMAC0_CH_NUM_MAX, &hdmac0CtrlTrns);
 		Ddim_Print(("Dd_HDMAC0_Ctrl_Trns(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Ctrl_Trns(0, NULL);
 		Ddim_Print(("Dd_HDMAC0_Ctrl_Trns(): ctrl is NULL. ret=0x%x\n", priv->hdma0->ret));

 		// BC over test (Ctrl_Trns)
 		// 65536*4*17
 		hdmac0CtrlTrns.size.trns_size = 0x00440000;
 		priv->hdma0->ret = Dd_HDMAC0_Ctrl_Trns(0, &hdmac0CtrlTrns);
 		Ddim_Print(("Dd_HDMAC0_Ctrl_Trns(): BC is over. ret=0x%x\n", priv->hdma0->ret));

 		// BC over test in Demand mode (Ctrl_Trns)
 		hdmac0CtrlTrns.mode.mode_sel = D_DD_HDMAC0_MS_DEMAND;
 		// 65536*4*2
 		hdmac0CtrlTrns.size.trns_size = 0x00080000;
 		priv->hdma0->ret = Dd_HDMAC0_Ctrl_Trns(0, &hdmac0CtrlTrns);
 		Ddim_Print(("Dd_HDMAC0_Ctrl_Trns(): demand transfer and BC is not 0. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Set_Trns_Size(D_DD_HDMAC0_CH_NUM_MAX, &hdmac0TrnsSize);
 		Ddim_Print(("Dd_HDMAC0_Set_Trns_Size(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Set_Trns_Size(0, NULL);
 		Ddim_Print(("Dd_HDMAC0_Set_Trns_Size(): trns_size is NULL. ret=0x%x\n", priv->hdma0->ret));

 		// BC over test (Set_Trns_Size)
 		hdmac0CtrlTrns.mode.mode_sel = D_DD_HDMAC0_MS_BLK;
 		hdmac0CtrlTrns.size.trns_size = 0x00001000;
 		priv->hdma0->ret = Dd_HDMAC0_Ctrl_Trns(0, &hdmac0CtrlTrns);
 		// 65536*1*17
 		hdmac0TrnsSize.trns_size = 0x00110000;
 		priv->hdma0->ret = Dd_HDMAC0_Set_Trns_Size(0, &hdmac0TrnsSize);
 		Ddim_Print(("Dd_HDMAC0_Set_Trns_Size(): BC is over. ret=0x%x\n", priv->hdma0->ret));

 		// BC over test in Demand mode (Set_Trns_Size)
 		hdmac0CtrlTrns.mode.mode_sel = D_DD_HDMAC0_MS_DEMAND;
 		hdmac0CtrlTrns.size.trns_size = 0x00001000;
 		priv->hdma0->ret = Dd_HDMAC0_Ctrl_Trns(0, &hdmac0CtrlTrns);
 		// 65536*1*2
 		hdmac0TrnsSize.trns_size = 0x00020000;
 		priv->hdma0->ret = Dd_HDMAC0_Set_Trns_Size(0, &hdmac0TrnsSize);
 		Ddim_Print(("Dd_HDMAC0_Set_Trns_Size(): demand transfer and BC is not 0. ret=0x%x\n", priv->hdma0->ret));


 		priv->hdma0->ret = Dd_HDMAC0_Start_Sync(D_DD_HDMAC0_CH_NUM_MAX, &status, D_DD_HDMAC0_WAITMODE_CPU);
 		Ddim_Print(("Dd_HDMAC0_Start_Sync(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Start_Sync(0, NULL, D_DD_HDMAC0_WAITMODE_CPU);
 		Ddim_Print(("Dd_HDMAC0_Start_Sync(): status is NULL. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Start_Sync(0, &status, D_DD_HDMAC0_WAITMODE_EVENT+1);
 		Ddim_Print(("Dd_HDMAC0_Start_Sync(): waitMode is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Start_Async(D_DD_HDMAC0_CH_NUM_MAX);
 		Ddim_Print(("Dd_HDMAC0_Start_Async(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Stop(D_DD_HDMAC0_CH_NUM_MAX);
 		Ddim_Print(("Dd_HDMAC0_Stop(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Pause(D_DD_HDMAC0_CH_NUM_MAX);
 		Ddim_Print(("Dd_HDMAC0_Pause(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Resume(D_DD_HDMAC0_CH_NUM_MAX);
 		Ddim_Print(("Dd_HDMAC0_Resume(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Set_Wait_Time(D_DD_HDMAC0_CH_NUM_MAX, D_DDIM_USER_SEM_WAIT_POL);
 		Ddim_Print(("Dd_HDMAC0_Set_Wait_Time(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Set_Wait_Time(0, -2);
 		Ddim_Print(("Dd_HDMAC0_Set_Wait_Time(): wait_time is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Wait_End(D_DD_HDMAC0_CH_NUM_MAX, &status, D_DD_HDMAC0_WAITMODE_CPU);
 		Ddim_Print(("Dd_HDMAC0_Wait_End(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Wait_End(0, NULL, D_DD_HDMAC0_WAITMODE_CPU);
 		Ddim_Print(("Dd_HDMAC0_Wait_End(): status is NULL. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Wait_End(0, &status, D_DD_HDMAC0_WAITMODE_EVENT+1);
 		Ddim_Print(("Dd_HDMAC0_Wait_End(): waitMode is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Clear_Status(D_DD_HDMAC0_CH_NUM_MAX);
 		Ddim_Print(("Dd_HDMAC0_Clear_Status(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Get_Status(D_DD_HDMAC0_CH_NUM_MAX, &status);
 		Ddim_Print(("Dd_HDMAC0_Get_Status(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Get_Status(0, NULL);
 		Ddim_Print(("Dd_HDMAC0_Get_Status(): status is NULL. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Get_Trns_Size(D_DD_HDMAC0_CH_NUM_MAX);
 		Ddim_Print(("Dd_HDMAC0_Get_Trns_Size(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Get_Remain_Trns_Size(D_DD_HDMAC0_CH_NUM_MAX);
 		Ddim_Print(("Dd_HDMAC0_Get_Remain_Trns_Size(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Get_Total_Trns_Size(D_DD_HDMAC0_CH_NUM_MAX);
 		Ddim_Print(("Dd_HDMAC0_Get_Total_Trns_Size(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Get_Src_Addr(D_DD_HDMAC0_CH_NUM_MAX);
 		Ddim_Print(("Dd_HDMAC0_Get_Src_Addr(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Get_Dst_Addr(D_DD_HDMAC0_CH_NUM_MAX);
 		Ddim_Print(("Dd_HDMAC0_Get_Dst_Addr(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Set_Source_Protect(D_DD_HDMAC0_CH_NUM_MAX, 0);
 		Ddim_Print(("Dd_HDMAC0_Set_Source_Protect(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Set_Destination_Protect(D_DD_HDMAC0_CH_NUM_MAX, 0);
 		Ddim_Print(("Dd_HDMAC0_Set_Destination_Protect(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Set_Arbitration(D_DD_HDMAC0_ARB_ROTATE+1);
 		Ddim_Print(("Dd_HDMAC0_Set_Arbitration(): arbitration is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Get_Arbitration(NULL);
 		Ddim_Print(("Dd_HDMAC0_Get_Arbitration(): arbitration is NULL. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Copy_SDRAM_Sync(D_DD_HDMAC0_CH_NUM_MAX, 1, 2, 1,
 				D_DD_HDMAC0_WAITMODE_EVENT);
 		Ddim_Print(("Dd_HDMAC0_Copy_SDRAM_Sync(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Copy_SDRAM_Sync(0, 0, 2, 1, D_DD_HDMAC0_WAITMODE_EVENT);
 		Ddim_Print(("Dd_HDMAC0_Copy_SDRAM_Sync(): src_addr is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Copy_SDRAM_Sync(0, 1, 0, 1, D_DD_HDMAC0_WAITMODE_EVENT);
 		Ddim_Print(("Dd_HDMAC0_Copy_SDRAM_Sync(): dst_addr is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Copy_SDRAM_Sync(0, 1, 2, 0, D_DD_HDMAC0_WAITMODE_EVENT);
 		Ddim_Print(("Dd_HDMAC0_Copy_SDRAM_Sync(): size is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Copy_SDRAM_Sync(0, 1, 2, 1, D_DD_HDMAC0_WAITMODE_EVENT+1);
 		Ddim_Print(("Dd_HDMAC0_Copy_SDRAM_Sync(): waitMode is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Copy_SDRAM_Async(D_DD_HDMAC0_CH_NUM_MAX, 1, 2, 1, ct_hdmac0_callback);
 		Ddim_Print(("Dd_HDMAC0_Copy_SDRAM_Async(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Copy_SDRAM_Async(0, 0, 2, 1, ct_hdmac0_callback);
 		Ddim_Print(("Dd_HDMAC0_Copy_SDRAM_Async(): src_addr is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Copy_SDRAM_Async(0, 1, 0, 1, ct_hdmac0_callback);
 		Ddim_Print(("Dd_HDMAC0_Copy_SDRAM_Async(): dst_addr is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Copy_SDRAM_Async(0, 1, 2, 0, ct_hdmac0_callback);
 		Ddim_Print(("Dd_HDMAC0_Copy_SDRAM_Async(): size is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Input_Audio_Async(D_DD_HDMAC0_CH_NUM_MAX,
 				D_DD_HDMAC0_IS_SOFT, 1, 2, 1, ct_hdmac0_callback);
 		Ddim_Print(("Dd_HDMAC0_Input_Audio_Async(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Input_Audio_Async(0, D_DD_HDMAC0_IS_SOFT, 0, 2, 1, ct_hdmac0_callback);
 		Ddim_Print(("Dd_HDMAC0_Input_Audio_Async(): src_addr is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Input_Audio_Async(0, D_DD_HDMAC0_IS_SOFT, 1, 0, 1, ct_hdmac0_callback);
 		Ddim_Print(("Dd_HDMAC0_Input_Audio_Async(): dst_addr is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Input_Audio_Async(0, D_DD_HDMAC0_IS_SOFT, 1, 2, 0, ct_hdmac0_callback);
 		Ddim_Print(("Dd_HDMAC0_Input_Audio_Async(): size is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Output_Audio_Async(D_DD_HDMAC0_CH_NUM_MAX,
 				D_DD_HDMAC0_IS_SOFT, 1, 2, 1, ct_hdmac0_callback);
 		Ddim_Print(("Dd_HDMAC0_Output_Audio_Async(): Channel number is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Output_Audio_Async(0, D_DD_HDMAC0_IS_SOFT, 0, 2, 1, ct_hdmac0_callback);
 		Ddim_Print(("Dd_HDMAC0_Output_Audio_Async(): src_addr is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Output_Audio_Async(0, D_DD_HDMAC0_IS_SOFT, 1, 0, 1, ct_hdmac0_callback);
 		Ddim_Print(("Dd_HDMAC0_Output_Audio_Async(): dst_addr is illegal. ret=0x%x\n", priv->hdma0->ret));

 		priv->hdma0->ret = Dd_HDMAC0_Output_Audio_Async(0, D_DD_HDMAC0_IS_SOFT, 1, 2, 0, ct_hdmac0_callback);
 		Ddim_Print(("Dd_HDMAC0_Output_Audio_Async(): size is illegal. ret=0x%x\n", priv->hdma0->ret));
 	}else
 	{
 		Ddim_Print(("please check 1st parameter!!\n"));
 	}
 	return;
 }

CtDdHdmac0Main* ct_dd_hdmac0_main_new(void) 
{
    CtDdHdmac0Main *self = k_object_new_with_private(CT_TYPE_DD_HDMAC0_MAIN, sizeof(CtDdHdmac0MainPrivate));
    return self;
}
