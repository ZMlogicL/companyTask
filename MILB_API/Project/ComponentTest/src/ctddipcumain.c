/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-03
*@author              	:杨升柄
*@brief               	:CtDdIpcuMain类
*@rely                		:klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/
#include <stdlib.h>
#include <string.h>
#include "driver_common.h"
#include "dd_ipcu.h"
#include "ctddipcu.h"
#include "ctddipcumain.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdIpcuMain, ct_dd_ipcu_main);
#define CT_DD_IPCU_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdIpcuMainPrivate,CT_TYPE_DD_IPCU_MAIN))

struct _CtDdIpcuMainPrivate
{
	CtDdIpcu* iPcu;
};

/*
 * DECLS
 */
static void ctDdIpcuCallbackAck1_cb( kuchar mbNum );
static void ctDdIpcuCallbackReq1_cb( kuchar mbNum );
static void ctDdIpcuPctestWrap_cb(CtDdIpcu* cdIpcu, kchar* cmd, kpointer userData);

static void ct_dd_ipcu_main_constructor(CtDdIpcuMain *self) 
{
	CtDdIpcuMainPrivate *priv = CT_DD_IPCU_MAIN_GET_PRIVATE(self);

	priv->iPcu = ct_dd_ipcu_new();
	self->priv = priv;

	ct_dd_ipcu_set_func(priv->iPcu, ctDdIpcuPctestWrap_cb, self);
}

static void ct_dd_ipcu_main_destructor(CtDdIpcuMain *self) 
{
	CtDdIpcuMainPrivate *priv = CT_DD_IPCU_MAIN_GET_PRIVATE(self);

	if(priv->iPcu)
	{
		k_object_unref(priv->iPcu);
	}
	priv->iPcu = NULL;
	self->priv = NULL;
}

/*
 * IMPL
 *
* Definition
*
* Nothing Special
*
* Enumeration
*
* Nothing Special
*
* Structure
*
* Nothing Special
*
* Global Data
*
* Nothing Special
*
* Local Method Definition
*
* Nothing Special
*
* Local Function
*/
static void ctDdIpcuCallbackAck1_cb( kuchar mbNum )
{
	Ddim_Print(("ctDdIpcuCallbackAck1_cb(mbNum=%u)\n", mbNum ));
}

static void ctDdIpcuCallbackReq1_cb( kuchar mbNum )
{
	Ddim_Print(("ctDdIpcuCallbackReq1_cb(mbNum=%u)\n", mbNum ));
}

static void ctDdIpcuPctestWrap_cb(CtDdIpcu* cdIpcu, kchar* cmd, kpointer userData)
{
	kint32	argc = 0;
	kchar*	argv[32];
	kchar	arg[32][32];
	kint32	pos = 0;
	kint32	len = 0;
	kint32	max = strlen(cmd);
	kint32	i;
	CtDdIpcuMain* iPcuMain = ct_dd_ipcu_main_new();

	printf("CMD> %s\n", cmd);

	// Clear arg buffer
	for(i = 0; i < 32; i++){
		argv[i] = arg[i];
		memset(argv[i], 0, 32);
	}

	// Set arg buffer
	for(i = 0; i < max; i++){
		if(cmd[i] == ' '){
			if(len){
				memcpy(argv[argc], &cmd[pos], len);
				argc++;
				len = 0;
			}
			pos = i + 1;
		}
		else if(i == max - 1){
			memcpy(argv[argc], &cmd[pos], len + 1);
			argc++;
			len = 0;
			pos = i + 1;
		}
		else{
			len++;
		}
	}

	// Execute command
	ct_dd_ipcu_main_test(iPcuMain, argc, argv);
	k_object_unref(iPcuMain);
	iPcuMain = NULL;
}

/*
 * Global Function
 *
 * PUBLIC
 *
 * @brief  Command main function for IPCU test.
 * @param  kint argc	:The number of parameters
 *		   kchar** argv	:The value of parameters
 * @return void
 *
 *		The meaning of parameters
 *		+-------+-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		| P1    | P2    | P3    | P4    | P5    | P6    | P7    | P7    |  Meaning                                 |
 *		+-------+-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		| open  | mbNum|    	|       |       |       |       |       | Open                                     |
 *		+-------+-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		| close | id    |    	|       |       |       |       |       | Close                                    |
 *		+-------+-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		| ctrl  | id 	| src_ch|dstbit |mskbit |mode	|       |       | Control Setting						   |
 *		+-------+-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		| set   | srcr  | id    | src   |       |       |       |       | Source Register                          |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | mr    | id    | md    |       |       |       |       | Mode Register                            |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | sndr  | id    |       |       |       |       |       | Send Register                            |
 *		|       +-------+-------+-------+-------+-----------------------+------------------------------------------+
 *		|       | dsr   | id    | val   |       |       |       |		| Destination Set Register                 |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | dsru  | id    | uni   |       |       |       | 		| Destination Set Register (Unit)          |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | dcr   | id    | val   |       |       |       | 		| Destination Clear Register               |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | dcru  | id    | uni   |       |       |       |		| Destination Clear Register (Unit)        |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | msr   | id    | val   |       |       |       | 		| Mask Set Register                        |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | msru  | id    | uni   |       |       |       |		| Mask Set Register (Unit)                 |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | mcr   | id	| val   |       |       |       | 		| Mask Clear Register                      |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | mcru  | id    | uni   |       |       |       | 		| Mask Clear Register (Unit)               |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | asr   | id    | val   |       |       |       |		| Acknowledge Set Register                 |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | asru  | id    | uni   |       |       |       |		| Acknowledge Set Register (Unit)          |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | acr   | id    | val   |       |       |       |		| Acknowledge Clear Register               |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | acru  | id    | uni   |       |       |       |		| Acknowledge Clear Register (Unit)        |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | dr    | id    | dat   | val   |       |       | 		| Data Register                            |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | ack_cb| id    | func  |       |       |       |       | Ack callback(set:func=1,clear:func=0)    |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | req_cb| unit  | ch    | func  |       |       |       | Req callback(set:func=1,clear:func=0)    |
 *		+-------+-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		| get   | isr   | unit  | ch    | num   |       |       |       | Interrupt Status Register                |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | isr   | unit  | all   |       |       |       |       | Interrupt Status Register (All)          |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | mbar  | unit  | ch    |       |       |       |       | Mailbox Address Register                 |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | mbar  | unit  | all   |       |       |       |       | Mailbox Address Register (All)           |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | srcr  | id    | uni   |       |       |       |		| Source Register                          |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | srcr  | id    | all   |       |       |       |       | Source Register (All)                    |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | mr    | id    |       |       |       |       |       | Mode Register                            |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | mr    | all   |       |       |       |       |       | Mode Register (All)                      |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | sndr  | id    |       |       |       |       | 		| Send Register                            |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | sndr  | all   |       |       |       |       |		| Send Register (All)                      |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | dstsr | id    | uni   |       |       |       | 		| Destination Status Register              |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | dstsr | all   |       |       |       |       |		| Destination Status Register (All)        |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | msr   | id    | uni   |       |       |       |		| Mask Status Register                     |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | msr   | all   |       |       |       |       |		| Mask Status Register (All)               |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | astar | id    | uni   |       |       |       | 		| Acknowledge Status Register              |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | astar | all   |       |       |       |       | 		| Acknowledge Status Register (All)        |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | asrcr | id 	| uni   |       |       |       | 		| Acknowledge Source Register              |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | asrcr | all   |       |       |       |       | 		| Acknowledge Source Register (All)        |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | dr    | id    | dat   |       |       |       | 		| Data Register                            |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | dr    | all   |       |       |       |       | 		| Data Register (All)                      |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | mbsr  | unit  | num   |       |       |       |       | MailBox Status Register                  |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | mbsr  | unit  | all   |       |       |       |       | MailBox Status Register (All)            |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | reqd  | id    | length|       |       |       |       | MailBox Data register                    |
 *		|       +-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 *		|       | ctrl  |       |       |       |       |       |       | Control Setting				           |
 *		+-------+-------+-------+-------+-------+-------+-------+-------+------------------------------------------+
 */
void ct_dd_ipcu_main_test(CtDdIpcuMain* self, kint argc, kchar** argv)
{
	CtDdIpcuMainPrivate* priv = self->priv;
	kuchar mbNum;
	kuchar length;
	kuchar id;
	kint32 ret;
	kint32 num;
	kint32 uni;
	kulong ch;
	kulong unit;
	kulong dat;
	kulong src;
	kulong md;
	kulong val;
	kulong send;
	kulong state;
	kulong ack;
	kulong req;
	kulong mbar;
	kulong dst;
	kulong msk;
//	static kulong data[9] = { 0x1111U, 0x2222U, 0x3333U, 0x4444U, 0x5555U, 0x6666U, 0x7777U, 0x8888U, 0x9999U };
	static kulong data[9] =
	{
			0x0000U, 0x0000U, 0x0000U, 0x0000U,
			0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U
	};
	kulong mbStat;
	static T_DD_IPCU_MNG ipcuMng;

	if(0 == strcmp(argv[1], "open")){
		Ddim_Print(("--- Open process ---\n"));
		// pgr0539
		mbNum = strtol(argv[2], NULL, 0);
		// pgr0539
		ret = Dd_IPCU_Open( mbNum, D_DDIM_WAIT_END_TIME, &id );
		Ddim_Print(("Dd_IPCU_Open:[MB No = %d][id = %d], ret = %d\n", mbNum, id, ret ));
	}else if(0 == strcmp(argv[1], "close")){
		Ddim_Print(("--- Close process ---\n"));
		id = strtol(argv[2], NULL, 0);
		// pgr0539
		ret = Dd_IPCU_Close( id );
		Ddim_Print(("Dd_IPCU_Close:[id = %d], ret = %d\n", id, ret ));
	}else if(0 == strcmp(argv[1], "ctrl")){
		Ddim_Print(("--- Control setting ---\n"));
		id = strtol(argv[2], NULL, 0);
		ipcuMng.src_ch_num = strtol(argv[3], NULL, 10);
		ipcuMng.dst_ch_bit = strtol(argv[4], NULL, 0);
		ipcuMng.mask_ch_bit = strtol(argv[5], NULL, 0);
		ipcuMng.mode = strtol(argv[6], NULL, 16);
		memcpy( &( ipcuMng.send_data ), data, D_DD_IPCU_DATA_LENGTH );
		ipcuMng.data_size = ( D_DD_IPCU_DATA_BLK_MAX * 4 );
		// pgr0539
		ret = Dd_IPCU_Ctrl( id, &ipcuMng );
		Ddim_Print(("Dd_IPCU_Ctrl:[id = %d], ret = %d\n", id, ret ));
	}else if(0 == strcmp(argv[1], "start")){
		Ddim_Print(("--- Start process ---\n"));
		id = strtol(argv[2], NULL, 10);
		// pgr0539
		ret = Dd_IPCU_Start( id );
		Ddim_Print(("Dd_IPCU_Start:[id = %d], ret = %d\n", id, ret ));
	}else if(0 == strcmp(argv[1], "set")){
		if(0 == strcmp(argv[2], "ack_cb")){
			Ddim_Print(("--- Set Acknowledge callback function ---\n"));
			id = strtol(argv[3], NULL, 10);
			if( strtol(argv[4], NULL, 10)){
				// pgr0539
				Dd_IPCU_Set_Ack_CB( id, ctDdIpcuCallbackAck1_cb );
				Ddim_Print(("Dd_IPCU_Set_Ack_CB:[id = %d], func = 1, callback = 0x%x\n", id,
						(kuint32)&ctDdIpcuCallbackAck1_cb ));
			}else
			{
				// pgr0539
				Dd_IPCU_Set_Ack_CB( id, 0 );
				Ddim_Print(("Dd_IPCU_Set_Ack_CB:[id = %d], func = 0, callback = 0\n", id ));
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "req_cb")){
			Ddim_Print(("--- Set Request callback function ---\n"));
			unit = strtol(argv[3], NULL, 10);
			ch = strtol(argv[4], NULL, 10);
			if( strtol(argv[5], NULL, 10)){
				// pgr0539
				Dd_IPCU_Set_Req_CB( unit, ch, ctDdIpcuCallbackReq1_cb );
				Ddim_Print(("Dd_IPCU_Set_Req_CB:[unit = %ld][ch = %ld], func = 1, callback = 0x%x\n", unit, ch,
						(kuint32)&ctDdIpcuCallbackReq1_cb ));
			}else
			{
				// pgr0539
				Dd_IPCU_Set_Req_CB( unit, ch, 0 );
				Ddim_Print(("Dd_IPCU_Set_Req_CB:[unit = %ld][ch = %ld], func = 0, callback = 0\n", unit, ch ));
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "srcr")){
			Ddim_Print(("--- Source Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			src = strtol(argv[4], NULL, 0);
			// pgr0539
			Dd_IPCU_Set_MB_Src( id, src );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "mr")){
			Ddim_Print(("--- Mode Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			md = strtol(argv[4], NULL, 0);
			// pgr0539
			ret = Dd_IPCU_Set_MB_Mode( id, md );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "sndr")){
			Ddim_Print(("--- Send Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			// pgr0539
			Dd_IPCU_Set_MB_Send( id );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "dsr")){
			Ddim_Print(("--- Destination Set Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			dst = strtol(argv[4], NULL, 0);
			// pgr0539, pgr0039
			Dd_IPCU_Set_MB_Dst( id, dst );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "dsru")){
			Ddim_Print(("--- Destination Set Register (Unit) ---\n"));
			id = strtol(argv[3], NULL, 0);
			uni = strtol(argv[4], NULL, 0);
			// pgr0539
			Dd_IPCU_Set_MB_Dst_Unit( id, uni );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "dcr")){
			Ddim_Print(("--- Destination Clear Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			val = strtol(argv[4], NULL, 0);
			// pgr0539
			Dd_IPCU_Clr_MB_Dst(id, val);
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "dcru")){
			Ddim_Print(("--- Destination Clear Register (Unit) ---\n"));
			id = strtol(argv[3], NULL, 0);
			uni = strtol(argv[4], NULL, 0);
			// pgr0539
			Dd_IPCU_Clr_MB_Dst_Unit( id, uni );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "msr")){
			Ddim_Print(("--- Mask Set Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			// pgr0539
			val = strtol(argv[4], NULL, 0);
			// pgr0539
			Dd_IPCU_Set_MB_Msk( id, val );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "msru")){
			Ddim_Print(("--- Mask Set Register (Unit) ---\n"));
			id = strtol(argv[3], NULL, 0);
			uni = strtol(argv[4], NULL, 0);
			// pgr0539
			Dd_IPCU_Set_MB_Msk_Unit( id, uni );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "mcr")){
			Ddim_Print(("--- Mask Clear Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			val = strtol(argv[4], NULL, 0);
			// pgr0539
			Dd_IPCU_Clr_MB_Msk( id, val );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "mcru")){
			Ddim_Print(("--- Mask Clear Register (Unit) ---\n"));
			id = strtol(argv[3], NULL, 0);
			uni = strtol(argv[4], NULL, 0);
			// pgr0539
			Dd_IPCU_Clr_MB_Msk_Unit( id, uni );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "asr")){
			Ddim_Print(("--- Acknowledge Set Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			val = strtol(argv[4], NULL, 0);
			// pgr0539
			Dd_IPCU_Set_MB_Ack( id, val );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "asru")){
			Ddim_Print(("--- Acknowledge Set Register (Unit) ---\n"));
			id = strtol(argv[3], NULL, 0);
			uni = strtol(argv[4], NULL, 0);
			// pgr0539
			Dd_IPCU_Set_MB_Ack_Unit( id, uni );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "acr")){
			Ddim_Print(("--- Acknowledge Clear Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			// pgr0539
			val = strtol(argv[4], NULL, 0);
			// pgr0539
			Dd_IPCU_Clr_MB_Ack( id, val );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "acru")){
			Ddim_Print(("--- Acknowledge Clear Register (Unit) ---\n"));
			id = strtol(argv[3], NULL, 0);
			uni = strtol(argv[4], NULL, 0);
			// pgr0539
			Dd_IPCU_Clr_MB_Ack_Unit( id, uni );
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "dr")){
			Ddim_Print(("--- Data Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			dat = strtol(argv[4], NULL, 0);
			val = strtoul(argv[5], NULL, 0);
			// pgr0539
			Dd_IPCU_Set_MB_Data( id, dat, val );
			Ddim_Print(("---\n"));
		}else{
			Ddim_Print(("please check 2nd parameter!!\n"));
		}
	}else if(0 == strcmp(argv[1], "get")){
		if(0 == strcmp(argv[2], "isr")){
			Ddim_Print(("--- Interrupt Status Register ---\n"));
			unit = strtol(argv[3], NULL, 0);
			ch = strtol(argv[4], NULL, 0);
			for(ch=0; ch<=D_DD_IPCU_INT_MAX; ch++){
				if((0 == strcmp(argv[4], "all"))||(ch == strtol(argv[4], NULL, 16))){
					// pgr0539
					ret = Dd_IPCU_Get_Int_Stat( unit, ch, &state );
					Ddim_Print(("ISR[unit = %ld][ch = %ld][state = %ld], ret = %d\n", unit, ch, state, ret));

					for(num=0; num<=D_DD_IPCU_MB_MAX; num++){
						if((0 == strcmp(argv[4], "all"))||(num == strtol(argv[5], NULL, 16))){
							ret = Dd_IPCU_Get_Int_Stat_MB( unit, ch, num, &state );
							Ddim_Print(("ISR[unit = %ld][ch = %ld][mb = %d][state = %ld], ret = %d\n",
									unit, ch, num, state, ret ));
						}
					}
				}
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "mbar")){
			Ddim_Print(("--- Mailbox Address Register ---\n"));
			unit = strtol(argv[3], NULL, 0);
			ch = strtol(argv[4], NULL, 0);
			for(ch=0; ch<=D_DD_IPCU_INT_MAX; ch++){
				if((0 == strcmp(argv[4], "all"))||(ch == strtol(argv[4], NULL, 16))){
					// pgr0539
					ret = Dd_IPCU_Get_MB_Ack( unit, ch, &ack );
					Ddim_Print(("MBADR[unit = %ld][ch = %ld][ACK = %ld], ret = %d\n", unit, ch, ack, ret));
					ret = Dd_IPCU_Get_MB_Req( unit, ch, &req );
					Ddim_Print(("MBADR[unit = %ld][ch = %ld][REQ = %ld], ret = %d\n", unit, ch, req, ret));
					ret = Dd_IPCU_Get_MB_Adr( unit, ch, &mbar );
					Ddim_Print(("MBADR[unit = %ld][ch = %ld][MBA = 0x%x], ret = %d\n", unit, ch, (kuint32)mbar, ret));
				}
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "srcr")){
			Ddim_Print(("--- Source Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			uni = strtol(argv[4], NULL, 0);
			for(num=0; num<=D_DD_IPCU_MB_MAX; num++){
				if((0 == strcmp(argv[3], "all"))||(num == strtol(argv[4], NULL, 16))){
					// pgr0539
					ret = Dd_IPCU_Get_MB_Src( id, &src );
					Ddim_Print(("MAILBOX[id = %d]SRC = %ld], ret = %d\n", id, src, ret));
					for(uni=0; uni<=D_DD_IPCU_INT_MAX; uni++){
						if((0 == strcmp(argv[4], "all"))||((uni == strtol(argv[4], NULL, 16)))){
							ret = Dd_IPCU_Get_MB_Src_Unit( id, uni, &src );
							Ddim_Print(("MAILBOX[id = %d][ch = %d], ret = %d\n", id, uni, ret));
						}
					}
				}
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "mr")){
			Ddim_Print(("--- Mode Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			for(num=0; num<=D_DD_IPCU_MB_MAX; num++){
				if((0 == strcmp(argv[3], "all"))||(num == id)){
					// pgr0539
					ret = Dd_IPCU_Get_MB_Mode( id, &md );
					Ddim_Print(("MAILBOX[id = %d][MODE = %ld], ret = %d\n", id, md, ret));
				}
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "sndr")){
			Ddim_Print(("--- Send Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			for(num=0; num<=D_DD_IPCU_MB_MAX; num++){
				// pgr0539
				if((0 == strcmp(argv[3], "all"))||(num == id)){
					// pgr0539
					ret = Dd_IPCU_Get_MB_Send( id, &send );
					Ddim_Print(("MAILBOX[id = %d][SEND = %ld], ret = %d\n", id, send, ret));
				}
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "dstsr")){
			Ddim_Print(("--- Destination Status Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			uni = strtol(argv[4], NULL, 0);
			for(num=0; num<=D_DD_IPCU_MB_MAX; num++){
				if((0 == strcmp(argv[3], "all"))||(num == id)){
					// pgr0539
					ret = Dd_IPCU_Get_MB_Dst_Stat( id, &dst );
					Ddim_Print(("MAILBOX[id = %d][DSTSTAT = 0x%x], ret = %d\n", id, (kuint32)dst, ret));
					for(uni=0; uni<=D_DD_IPCU_INT_MAX; uni++){
						if((0 == strcmp(argv[3], "all"))||(uni == strtol(argv[4], NULL, 16))){
							ret = Dd_IPCU_Get_MB_Dst_Stat_Unit( id, uni, &dst );
							Ddim_Print(("MAILBOX[id = %d][ch = %d][DSTSTAT = %ld], ret = %d\n", id, uni, dst, ret));
						}
					}
				}
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "msr")){
			Ddim_Print(("--- Mask Status Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			uni = strtol(argv[4], NULL, 0);
			for(num=0; num<=D_DD_IPCU_MB_MAX; num++){
				if((0 == strcmp(argv[3], "all"))||(num == id)){
					// pgr0539
					ret = Dd_IPCU_Get_MB_Msk_Stat( id, &msk );
					Ddim_Print(("MAILBOX[[id = %d][MASKSTAT = 0x%x], ret = %d\n", id, (kuint32)msk, ret));
					for(uni=0; uni<=D_DD_IPCU_INT_MAX; uni++){
						if((0 == strcmp(argv[3], "all"))||(uni == strtol(argv[4], NULL, 16))){
							ret = Dd_IPCU_Get_MB_Msk_Stat_Unit(num, uni, &msk);
							Ddim_Print(("MAILBOX[id = %d][ch = %d][MASKSTAT = %ld], ret = %d\n", id, uni, msk, ret));
						}
					}
				}
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "astar")){
			Ddim_Print(("--- Acknowledge Status Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			uni = strtol(argv[4], NULL, 0);
			for(num=0; num<=D_DD_IPCU_MB_MAX; num++){
				if((0 == strcmp(argv[3], "all"))||(num == id)){
					// pgr0539
					ret = Dd_IPCU_Get_MB_Ack_Stat( id, &ack );
					Ddim_Print(("MAILBOX[id = %d][ACKSTAT = 0x%x], ret = %d\n", id, (kuint32)ack, ret));
					for(uni=0; uni<=D_DD_IPCU_INT_MAX; uni++){
						if((0 == strcmp(argv[3], "all"))||(uni == strtol(argv[4], NULL, 16))){
							ret = Dd_IPCU_Get_MB_Ack_Stat_Unit(num, uni, &ack);
							Ddim_Print(("MAILBOX[id = %d][ch = %d][ACKSTAT = %ld], ret = %d\n", id, uni, ack, ret));
						}
					}
				}
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "asrcr")){
			Ddim_Print(("--- Acknowledge Source Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			uni = strtol(argv[4], NULL, 0);
			for(num=0; num<=D_DD_IPCU_MB_MAX; num++){
				if((0 == strcmp(argv[3], "all"))||(num == id)){
					// pgr0539
					ret = Dd_IPCU_Get_MB_Ack_Src( id, &ack );
					Ddim_Print(("MAILBOX[id = %d][ACKSRC = 0x%x], ret = %d\n", id, (kuint32)ack, ret));
					for(uni=0; uni<=D_DD_IPCU_INT_MAX; uni++){
						if((0 == strcmp(argv[3], "all"))||(uni == strtol(argv[4], NULL, 16))){
							ret = Dd_IPCU_Get_MB_Ack_Src_Unit( id, uni, &ack);
							Ddim_Print(("MAILBOX[id = %d][ch = %d][ACKSRC = %ld], ret = %d\n", id, uni, ack, ret));
						}
					}
				}
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "dr")){
			Ddim_Print(("--- Data Register ---\n"));
			id = strtol(argv[3], NULL, 0);
			dat = strtol(argv[4], NULL, 0);
			for(num=0; num<=D_DD_IPCU_MB_MAX; num++){
				if((0 == strcmp(argv[3], "all"))||(num == id)){
					for(dat=0; dat<=D_DD_IPCU_MB_DATA_MAX; dat++){
						if((0 == strcmp(argv[3], "all"))||(dat == strtol(argv[4], NULL, 16))){
							// pgr0539
							ret = Dd_IPCU_Get_MB_Data( id, dat, &val );
							Ddim_Print(("MAILBOX[[id = %d][DATA[%ld] = 0x%x], ret = %d\n", id, dat, (kuint32)val, ret));
						}
					}
				}
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "mbsr")){
			Ddim_Print(("--- MailBox Status Register ---\n"));
			unit = strtol(argv[3], NULL, 0);
			mbNum = strtol(argv[3], NULL, 0);
			// pgr0539
			ret = Dd_IPCU_Get_MB_Stat( unit, &mbStat );
			Ddim_Print(("[unit = %ld][MBSTAT = %ld], ret = %d\n", unit, mbStat, ret));
			for(num=0; num<=D_DD_IPCU_MB_MAX; num++){
				if((0 == strcmp(argv[3], "all"))||(num == mbNum)){
					ret = Dd_IPCU_Get_MB_Stat_MB( unit, num, &mbStat );
					Ddim_Print(("[unit = %ld][MBSTAT[%d] = %ld], ret = %d\n", unit, num, mbStat, ret));
				}
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "reqd")){
		Ddim_Print(("--- Get MailBox Data ---\n"));
			kuchar dat_num = 0;
			id = strtol(argv[3], NULL, 0);
			length = strtol(argv[4], NULL, 0);
			// pgr0539
			ret = Dd_IPCU_Get_Req_Data( id, data, length );
			while( length > 0 ) {
				Ddim_Print(("MAILBOX[id = %d][dat_num = %d][data = %ld], ret = %d\n",
						id, dat_num, data[dat_num], ret));
				length = length - 4;
				dat_num++;
			}
			Ddim_Print(("---\n"));
		}else if(0 == strcmp(argv[2], "ctrl")){
			Ddim_Print(("--- Control setting ---\n"));
			id = strtol(argv[3], NULL, 0);
			// pgr0539
			ret = Dd_IPCU_Get_Ctrl( id, &ipcuMng );
			Ddim_Print(("[id = %d][mode = %d] ret = %d\n", id, ipcuMng.mode, ret ));
			Ddim_Print(("[src ch = %ld][dst ch bit = 0x%04lx]\n", ipcuMng.src_ch_num, ipcuMng.dst_ch_bit ));
			Ddim_Print(("[msk ch bit = 0x%04lx]\n", ipcuMng.mask_ch_bit ));
			Ddim_Print(("---\n"));
		}else{
			Ddim_Print(("please check 2nd parameter!!\n"));
		}
	}else if(0 == strcmp(argv[1], "test_2")){
		ct_dd_ipcu_test_all_2(priv->iPcu);
	}else if(0 == strcmp(argv[1], "test_3")){
		ct_dd_ipcu_test_all_3(priv->iPcu);
	}else{
		Ddim_Print(("please check 1st parameter!!\n"));
	}
}

CtDdIpcuMain* ct_dd_ipcu_main_new(void) 
{
    CtDdIpcuMain *self = k_object_new_with_private(CT_TYPE_DD_IPCU_MAIN, sizeof(CtDdIpcuMainPrivate));
    return self;
}
