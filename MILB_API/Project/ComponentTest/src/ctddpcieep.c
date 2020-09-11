/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdPcieEp类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_pcie_ep.c
 * @brief		ct code for dd_pcie_ep
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include <stdlib.h>
#include <string.h>
#include "ddgic.h"
#include "ddtop.h"
#include "arm.h"
#include "ctddpcieep.h"
#include "ddtimestamp.h"
#include "ddpcieep.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPcieEp, ct_dd_pcie_ep);
#define CT_DD_PCIE_EP_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPcieEpPrivate,CT_TYPE_DD_PCIE_EP))

struct _CtDdPcieEpPrivate {

};

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define	CtDdPcieEp_PCIE_TIMESTAMP_FREQUENCY	(0x2625A00)		// 40MHz (Timestamp frequency)

// coefficient for transfer time
#define CtDdPcieEp_PCIE_TIMESTAMP_K			(0.025)			// 1000000/CtDdPcieEp_PCIE_TIMESTAMP_FREQUENCY

#define CtDdPcieEp_PCIE_DMA_LL_ADDR			(0x55000000)

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
//static T_DD_PCIE_INIT_CONF gctDD_PCIE_Init_Conf = {E_DD_PCIE_BIFURCATION_DISABLE,
//												   0,
//												   0,
//												   E_DD_PCIE_PM_D1_D2_USPT,
//												   E_DD_PCIE_PM_D1_D2_USPT,
//												   0};

static TDdPcieEpIntEpCb			S_GCTDD_PCIE_EP_INT_EP_CD		= {NULL, NULL};
static TDdPcieEpIntOwnCb		S_GCTDD_PCIE_EP_INT_OWN_CD		= {NULL, NULL,NULL,NULL};

/*DECLS*/

static void ctDdPcieEpIntDmaCb(kint32 status);
static void ctDdPcieEpIntEpMsgUnlockCb(kint32 status);
static void ctDdPcieEpIntEpPmTurnofCb(kint32 status);
static void ctDdPcieEpIntOwnLuCb(kint32 status);
static void ctDdPcieEpIntOwnCeCb(kint32 status);
static void ctDdPcieEpIntOwnNfeCb(kint32 status);
static void ctDdPcieEpIntOwnFeCb(kint32 status);
static void ctDdPcieEpLlDma(void);
static void ctDdPcieEpLlDma1(void);
static void ctDdPcieEpErrMsg(kuint32 msg);
static void ctDdPcieEpLtr(void);

static void ct_dd_pcie_ep_constructor(CtDdPcieEp *self) 
{
	// CtDdPcieEpPrivate *priv = CT_DD_PCIE_EP_GET_PRIVATE(self);
}

static void ct_dd_pcie_ep_destructor(CtDdPcieEp *self)
{
	// CtDdPcieEpPrivate *priv = CT_DD_PCIE_EP_GET_PRIVATE(self);
}

/*IMPL*/

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
static void ctDdPcieEpIntDmaCb(kint32 status)
{
	kulonglong	timestampCounter;
	kulong		transferTime;
	DdTimestamp *dtStamp = dd_timestamp_new();

	dd_timestamp_get_counter(dtStamp, &timestampCounter);
//	dd_timestamp_stop();
//	dd_timestamp_close();
	transferTime = (kulong)(timestampCounter * CtDdPcieEp_PCIE_TIMESTAMP_K);
	Ddim_Print(("[DD_PCIe_CT] DMA transfer time=%ld[us]\n", transferTime));

	Ddim_Print(("ctDdPcieEpIntDmaCb called. Status=0x%08X\n", status));
	k_object_unref(dtStamp);
	dtStamp = NULL;
}

static void ctDdPcieEpIntEpMsgUnlockCb(kint32 status)
{
	Ddim_Print(("ctDdPcieEpIntEpMsgUnlockCb called. Status=0x%08X\n", status));
}

static void ctDdPcieEpIntEpPmTurnofCb(kint32 status)
{
	Ddim_Print(("ctDdPcieEpIntEpPmTurnofCb called. Status=0x%08X\n", status));
}

static void ctDdPcieEpIntOwnLuCb(kint32 status)
{
	Ddim_Print(("ctDdPcieEpIntOwnLuCb called. Status=0x%08X\n", status));
}

static void ctDdPcieEpIntOwnCeCb(kint32 status)
{
	Ddim_Print(("ctDdPcieEpIntOwnCeCb called. Status=0x%08X\n", status));
}

static void ctDdPcieEpIntOwnNfeCb(kint32 status)
{
	Ddim_Print(("ctDdPcieEpIntOwnNfeCb called. Status=0x%08X\n", status));
}

static void ctDdPcieEpIntOwnFeCb(kint32 status)
{
	Ddim_Print(("ctDdPcieEpIntOwnFeCb called. Status=0x%08X\n", status));
}

static void ctDdPcieEpLlDma(void)
{
	kuint32 LinkedList[22];
	kuint32 tarnsData[3] = {0x87654321, 0xffedcba9, 0xddccbbaa};

	memcpy((void*)0x58000000, (void*)tarnsData, sizeof(tarnsData));
	ddim_user_custom_l1l2cache_clean_flush_addr(0x58000000, sizeof(tarnsData));

	LinkedList[0]	= 0x00000001;	// Channel Control
	LinkedList[1]	= 0x00000004;	// Transfer Size
	LinkedList[2]	= 0x58000000;	// SAR Low
	LinkedList[3]	= 0x0;			// SAR High
	LinkedList[4]	= 0x5F000000;	// DAR Low
	LinkedList[5]	= 0x0;			// DAR High
	// Element 1
	LinkedList[6]	= 0x00000001;	// Channel Control
	LinkedList[7]	= 0x00000004;	// Transfer Size
	LinkedList[8]	= 0x58000004;	// SAR Low
	LinkedList[9]	= 0x0;			// SAR High
	LinkedList[10]	= 0x5F000004;	// DAR Low
	LinkedList[11]	= 0x0;			// DAR High
	// Element 2
	LinkedList[12]	= 0x00000009;	// Channel Control (Local Interrupt Enable)
	LinkedList[13]	= 0x00000004;	// Transfer Size
	LinkedList[14]	= 0x58000008;	// SAR Low
	LinkedList[15]	= 0x0;			// SAR High
	LinkedList[16]	= 0x5F000008;	// DAR Low
	LinkedList[17]	= 0x0;			// DAR High
	// Element 3
	LinkedList[18]	= 0x00000004;	// Channel Control (Linked List End)
	LinkedList[19]	= 0x0;
	LinkedList[20]	= 0x0;
	LinkedList[21]	= 0x0;

	memcpy((void*)CtDdPcieEp_PCIE_DMA_LL_ADDR, (void*)LinkedList, sizeof(LinkedList));
	ddim_user_custom_l1l2cache_clean_flush_addr(CtDdPcieEp_PCIE_DMA_LL_ADDR, sizeof(LinkedList));
}

static void ctDdPcieEpLlDma1(void)
{
	kuint32 LinkedList[22];

	// Element 0
	LinkedList[0]	= 0x00000001;	// Channel Control
	LinkedList[1]	= 0x00000004;	// Transfer Size
	LinkedList[2]	= 0x5F000000;	// SAR Low
	LinkedList[3]	= 0x0;			// SAR High
	LinkedList[4]	= 0x58000010;	// DAR Low
	LinkedList[5]	= 0x0;			// DAR High
	// Element 1
	LinkedList[6]	= 0x00000001;	// Channel Control
	LinkedList[7]	= 0x00000004;	// Transfer Size
	LinkedList[8]	= 0x5F000004;	// SAR Low
	LinkedList[9]	= 0x0;			// SAR High
	LinkedList[10]	= 0x58000014;	// DAR Low
	LinkedList[11]	= 0x0;			// DAR High
	// Element 2
	LinkedList[12]	= 0x00000009;	// Channel Control (Local Interrupt Enable)
	LinkedList[13]	= 0x00000004;	// Transfer Size
	LinkedList[14]	= 0x5F000008;	// SAR Low
	LinkedList[15]	= 0x0;			// SAR High
	LinkedList[16]	= 0x58000018;	// DAR Low
	LinkedList[17]	= 0x0;			// DAR High
	// Element 3
	LinkedList[18]	= 0x00000004;	// Channel Control (Linked List End)
	LinkedList[19]	= 0x0;
	LinkedList[20]	= 0x0;
	LinkedList[21]	= 0x0;

	memcpy((void*)CtDdPcieEp_PCIE_DMA_LL_ADDR, (void*)LinkedList, sizeof(LinkedList));
	ddim_user_custom_l1l2cache_clean_flush_addr(CtDdPcieEp_PCIE_DMA_LL_ADDR, sizeof(LinkedList));
}

static void ctDdPcieEpErrMsg(kuint32 msg)
{
	DdPcieEp *dpEp = dd_pcie_ep_get();

	dd_pcie_ep_set_dbi_reg(dpEp, 0x0900, 0x00000000);	// BANK : Region 0 outband
	dd_pcie_ep_set_dbi_reg(dpEp, 0x0904, 0x00000010);	// CTRL1: [4:0] TYPE=10_000(MSG)
	dd_pcie_ep_set_dbi_reg(dpEp, 0x090C, 0x19400000);	// Lower Base
	dd_pcie_ep_set_dbi_reg(dpEp, 0x0910, 0x00000000);	// Upper Base
	dd_pcie_ep_set_dbi_reg(dpEp, 0x0914, 0x1940FFFF);	// Base  Limit
	dd_pcie_ep_set_dbi_reg(dpEp, 0x0918, 0x00000000);	// Lower Target
	dd_pcie_ep_set_dbi_reg(dpEp, 0x091C, 0x00000000);	// Upper Target
	switch(msg){
		case 0:
			dd_pcie_ep_set_dbi_reg(dpEp, 0x0908, 0x80000030); // CTRL2: [31] REGION_EN, MSG_CODE=ERR_COR
			break;
		case 1:
			dd_pcie_ep_set_dbi_reg(dpEp, 0x0908, 0x80000031); // CTRL2: [31] REGION_EN, MSG_CODE=ERR_NOFATAL
			break;
		case 2:
			dd_pcie_ep_set_dbi_reg(dpEp, 0x0908, 0x80000033); // CTRL2: [31] REGION_EN, MSG_CODE=ERR_FATAL
			break;
		case 3:
			dd_pcie_ep_set_dbi_reg(dpEp, 0x0908, 0x8000007E); // CTRL2: [31] REGION_EN, MSG_CODE=Vendor defined message
			break;
		default:
			;
	}
	k_object_unref(dpEp);
	dpEp = NULL;

	ioXdmacs.cdacs.word			= 0x10000000;	// XDMAC Enable
	ioXdmacs.ch[0].xdtbc		= 0x00000004;	// Transfer Byte Count Set(4byte)
	ioXdmacs.ch[0].xdssa		= 0x00010000;	// Source Start Address(Reserved area)
	ioXdmacs.ch[0].xddsa		= 0x19400000;	// Destination Start Address(Target area)
	ioXdmacs.ch[0].xdsac.word	= 0x00020300;	// Source Access Configration
	ioXdmacs.ch[0].xddac.word	= 0x00020300;	// Destination Access Configration
	ioXdmacs.ch[0].xddes.word	= 0x11100003;	// Enable Setting
}

// Latency Tolerance Reporting (LTR) Mechanism
static void ctDdPcieEpLtr(void)
{
	ioPcie0.ltrMonitor1.bit.appLtrMsgRst	= 0;	// Reset Cancel
	ioPcie0Core.ep.pciecr.dc2sr.bit.ltrme	= 1;	// LTR Mechanism Enable
	ioPcie0.pmUnlockReq.bit.ltrMsgFuncNum	= 0;
	ioPcie0.ltrMsg.bit.ltrMsgLatency		= 0x1000;
	ioPcie0.pmUnlockReq.bit.ltrMsgReq		= 1;
}

/*PUBLIC*/

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/**
 *	@brief	Command main function for PCIe test.
 *	@param	int argc	:The number of parameters
 *			char** argv	:The value of parameters
 *
 *	The meaning of parameters
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| P1	| P2	| P3 	| P4	| P5	| P6	| P7	| P8	| P9  | P10| P11|Meaning					|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| open	| tout	|		|		|		|		|		|		|	  |	   |    | PCIe open					|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| close	|		|		|		|		|		|		|		|	  |	   |    | PCIe close				|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| init	|		| 		|		|		|		|		|		|	  |	   |	| PCIe initialize			|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| deinit|		| 		|		|		|		|		|		|	  |	   |	| PCIe deinit				|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| lnkst	|		|		|		|		|		|		|		|	  |	   |	| Get link status			|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| ctrl	| dma	| dmd	| dmach	| srcadr| dstadr| size	| dir	| cb  |	   |	| Set demand transfer		|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| ctrl	| mem	| bar	| ladr	| tadr	| 		| 		|		|	  |	   |	| Set memory transfer		|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| ctrl	| aspm	| aspmlv|		| 		| 		|		|		|	  |	   |	| ASPM control				|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| dma	| start	| dmach	| dir	| 		|		|		|		|	  |	   |	| DMA start read/write		|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| dma	| stop	| dmach	| dir	|		|		|		|		|	  |	   |	| DMA stop					|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| rqintx|		|		|		|		|		|		|		|	  |	   |	| Request IINTx send		|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| rqmsi	| mnum	|		|		|		|		|		|		|	  |	   |	| Request MSI Transfer	    |
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| set	| chtrsp| lnksp	| 		|		|		|		|		|	  |	   |	| Set Change Transfer Speed.|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| set	| ixcb	| cb	|		|		|		|		|		|	  |	   |	| Set INT_EP callback		|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| set	| iocb	| cb	|		|		|		|		|		|	  |	   |	| Set INT_OWN callback		|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| get	| pmst	| 		| 		|		|		|		|		|	  |	   |	| Get Power State.			|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| get	| ltssm	| 		| 		|		|		|		|		|	  |	   |	| Get LTSSM State.			|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| get	| cls	| 		| 		|		|		|		|		|	  |	   |	| Get Current Link Speed.	|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| int	| ep	|		| 		|		|		|		|		|	  |	   |	| Interrupt INT_EP.			|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	| int	| own	|		| 		|		|		|		|		|	  |	   |	| Interrupt INT_OWN.		|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-----+----+----+---------------------------+
 *	tout	: 0(Wait by Polling), 1~n(timeout sec)
 *	dmd		: 0(Demand DMA mode), 1(Link List DMA mode)
 *	dmach	: 0,1
 *	srcadr	: Demand dma transfer source address
 *	dstadr	: Demand dma transfer destination address
 *	size	: Demand dma transfer total size
 *	lladr	: Link list dma transfer table address
 *	dir		: 0(destination to source), 1(source to destination)
 *	cb		: 0(callback off), 1(callback on)
 *	ladr	: hex string of limit address
 *	tadr	: hex string of target address
 *	mnum	: MSI number(0~31)
 *	aspmlv	: 0(Disabled), 1(L0s Entry Enabled), 2(L1 Entry Enabled), 3(L0s and L1 Entry Enabled)
 *
 *	@return void
 */

void ct_dd_pcie_ep_main(CtDdPcieEp *self, kint argc, KType* argv)
{
	kint32					ret;
	DdPcieEp *				dpEp = dd_pcie_ep_get();
	DdTimestamp *			dtStamp = dd_timestamp_new();
	
	if(strcmp(argv[1], "open") == 0){
		ret = dd_pcie_ep_open(dpEp, (kint32)atoi(argv[2]));
		Ddim_Print(("dd_pcie_ep_open completed. Return Value=0x%08X\n", ret));
	}
	else if(strcmp(argv[1], "close") == 0){
		ret = dd_pcie_ep_close(dpEp);
		Ddim_Print(("dd_pcie_ep_open completed. Return Value=0x%08X\n", ret));
	}
	else if(strcmp(argv[1], "init") == 0){
		ret = dd_pcie_ep_init(dpEp);
		Ddim_Print(("dd_pcie_ep_init completed. Return Value=0x%08X\n", ret));
	}
	else if(strcmp(argv[1], "deinit") == 0){
		dd_pcie_ep_deinit(dpEp);
		Ddim_Print(("dd_pcie_ep_deinit completed.\n"));
	}
	else if(strcmp(argv[1], "lnkst") == 0){
		kboolean linkStatus;
		linkStatus = dd_pcie_ep_get_link_status(dpEp);
		Ddim_Print(("dd_pcie_ep_get_link_status completed. Link Status=%d\n", linkStatus));
	}
	else if(strcmp(argv[1], "ctrl") == 0){
		if(strcmp(argv[2], "dma") == 0){
			memset(&self->ctrlDma,0,sizeof(self->ctrlDma));
			self->ctrlDma.mode	= (DdPcieDmaTransMode)atoi(argv[3]);
			self->ctrlDma.ch	= DdPcieComm_DD_PCIE_CH0;
			self->ctrlDma.dmaCh	= (DdPcieDmaCh)atoi(argv[4]);
			sscanf(argv[5], "%lx", (kulong*)&self->ctrlDma.dmndSrcAddrL);
			sscanf(argv[6], "%lx", (kulong*)&self->ctrlDma.dmndDstAddrL);//对方没改完
			self->ctrlDma.dmndDstAddrH = 0;
			sscanf(argv[7], "%lx", (kulong*)&self->ctrlDma.dmndTransSize);
			self->ctrlDma.direction	= (DdPcieDmaDir)atoi(argv[8]);
			if(strcmp(argv[9], "0") == 0){
				self->ctrlDma.intDmaCb = NULL;
			}
			else{
				self->ctrlDma.intDmaCb = (VP_CALLBACK_PCIE)ctDdPcieEpIntDmaCb;
			}
			if(self->ctrlDma.mode == DdPcieComm_DD_PCIE_DMA_LL_MODE){
				self->ctrlDma.llAddr = CtDdPcieEp_PCIE_DMA_LL_ADDR;
				if(self->ctrlDma.direction == DdPcieComm_DD_PCIE_DMA_DIR_STOD){	// Write
					ctDdPcieEpLlDma();
				}
				else{	// Read
					ctDdPcieEpLlDma1();
				}
			}
			ret = dd_pcie_ep_ctrl_dma(dpEp, &self->ctrlDma);
			Ddim_Print(("dd_pcie_ep_ctrl_dma completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "mem") == 0){
			memset(&self->ctrlMem,0,sizeof(self->ctrlMem));;
			sscanf(argv[3], "%lx", (kulong*)&self->ctrlMem.baseAdr);
			sscanf(argv[4], "%lx", (kulong*)&self->ctrlMem.limitAdr);
			sscanf(argv[5], "%lx", (kulong*)&self->ctrlMem.lowTargetAdr);
			ret = dd_pcie_ep_ctrl_memory(dpEp, &self->ctrlMem);
			Ddim_Print(("dd_pcie_ep_ctrl_memory completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "aspm") == 0){
			DdPcieAspmControl aspmlv;
			aspmlv = (DdPcieAspmControl)atoi(argv[3]);
			ret = dd_pcie_ep_ctrl_aspm(dpEp, aspmlv);
			Ddim_Print(("dd_pcie_ep_ctrl_aspm completed. Return Value=0x%08X\n", ret));
		}
		else{
			Ddim_Print(("please check parameter!!\n"));
		}
	}
	else if(strcmp(argv[1], "dma") == 0){
		self->dmach		= (DdPcieDmaCh)atoi(argv[3]);
		self->dir		= (DdPcieDmaDir)atoi(argv[4]);
		if(strcmp(argv[2], "start") == 0){
			self->timestampCtrl.hdbg			= 0;			// has no effect
			self->timestampCtrl.counter		= 0;			// Counter
			self->timestampCtrl.frequency	= CtDdPcieEp_PCIE_TIMESTAMP_FREQUENCY;
			dd_timestamp_init(dtStamp);
			if (dd_timestamp_open(dtStamp, DdimUserCustom_SEM_WAIT_POL) != D_DDIM_OK) {
				Ddim_Print(("Dd_TIMESTAMP has already opened.\n"));
				dd_timestamp_stop(dtStamp);
				dd_timestamp_close(dtStamp);
				if (dd_timestamp_open(dtStamp, DdimUserCustom_SEM_WAIT_POL) != D_DDIM_OK) {
					Ddim_Print(("dd_timestamp_open Error.\n"));
				}
			}
			dd_timestamp_ctrl(dtStamp, &self->timestampCtrl);
			dd_timestamp_start(dtStamp);

			ret = dd_pcie_ep_start_dma(dpEp, self->dmach, self->dir);
			Ddim_Print(("dd_pcie_ep_start_dma completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "stop") == 0){
			ret = dd_pcie_ep_stop_dma(dpEp, self->dmach, self->dir);
			Ddim_Print(("dd_pcie_ep_stop_dma completed. Return Value=0x%08X\n", ret));
		}
		else{
			Ddim_Print(("please check parameter!!\n"));
		}
	}
	else if(strcmp(argv[1], "rqintx") == 0){
		kuint32	msfF0Stat;
		msfF0Stat = dd_pcie_ep_req_int_ep(dpEp);
		if(msfF0Stat == 0){
			Ddim_Print(("dd_pcie_ep_req_int_ep completed. INTx Deassert(1->0). Value=0x%08X\n", 
				msfF0Stat));
		}
		else{
			Ddim_Print(("dd_pcie_ep_req_int_ep completed. INTx Assert(0->1). Value=0x%08X\n",
				msfF0Stat));
		}
	}
	else if(strcmp(argv[1], "rqmsi") == 0){
		self->msiNum = (EDdPcieEpMsiNum)atoi(argv[2]);
		ret = dd_pcie_ep_transfer_msi(dpEp, self->msiNum);
		Ddim_Print(("dd_pcie_ep_transfer_msi completed. Return Value=0x%08X\n", ret));
	}
	else if(strcmp(argv[1], "set") == 0){
		if(strcmp(argv[2], "chtrsp") == 0){
			ret = dd_pcie_ep_transfer_speed_change(dpEp, (EDdPcieLinkSpeed)atoi(argv[3]));
			Ddim_Print(("dd_pcie_ep_transfer_speed_change completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "ixcb") == 0){
			if(strcmp(argv[3], "1") == 0){
				S_GCTDD_PCIE_EP_INT_EP_CD.msgUnlockCb	= (VP_CALLBACK_PCIE)ctDdPcieEpIntEpMsgUnlockCb;
				S_GCTDD_PCIE_EP_INT_EP_CD.pmTurnofCb	= (VP_CALLBACK_PCIE)ctDdPcieEpIntEpPmTurnofCb;
			}
			else{
				S_GCTDD_PCIE_EP_INT_EP_CD.msgUnlockCb	= NULL;
				S_GCTDD_PCIE_EP_INT_EP_CD.pmTurnofCb	= NULL;
			}
			ret = dd_pcie_ep_set_int_ep_func(dpEp, &S_GCTDD_PCIE_EP_INT_EP_CD);
			Ddim_Print(("dd_pcie_ep_set_int_ep_func completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "iocb") == 0){
			if(strcmp(argv[3], "1") == 0){
				S_GCTDD_PCIE_EP_INT_OWN_CD.luCb		= (VP_CALLBACK_PCIE)ctDdPcieEpIntOwnLuCb;
				S_GCTDD_PCIE_EP_INT_OWN_CD.ceCb		= (VP_CALLBACK_PCIE)ctDdPcieEpIntOwnCeCb;
				S_GCTDD_PCIE_EP_INT_OWN_CD.nfeCb	= (VP_CALLBACK_PCIE)ctDdPcieEpIntOwnNfeCb;
				S_GCTDD_PCIE_EP_INT_OWN_CD.feCb		= (VP_CALLBACK_PCIE)ctDdPcieEpIntOwnFeCb;
			}
			else{
				S_GCTDD_PCIE_EP_INT_OWN_CD.luCb		= NULL;
				S_GCTDD_PCIE_EP_INT_OWN_CD.ceCb		= NULL;
				S_GCTDD_PCIE_EP_INT_OWN_CD.nfeCb	= NULL;
				S_GCTDD_PCIE_EP_INT_OWN_CD.feCb		= NULL;
			}
			ret = dd_pcie_ep_set_int_own_func(dpEp, &S_GCTDD_PCIE_EP_INT_OWN_CD);
			Ddim_Print(("dd_pcie_ep_set_int_own_func completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "mps") == 0){
			self->mps = (DdPcieMps)atoi(argv[3]);
			ret = dd_pcie_ep_set_mps(dpEp, self->mps);
			Ddim_Print(("dd_pcie_ep_set_mps completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "exsr") == 0){
			sscanf(argv[3], "%lx", (kulong*)&self->offset);
			sscanf(argv[4], "%lx", (kulong*)&self->data);
			ret = dd_pcie_ep_set_exs_reg(dpEp, self->offset, self->data);
			Ddim_Print(("EXSTOP PCIe Register\t0x%04X\t0x%08X\n", self->offset, self->data));
			Ddim_Print(("dd_pcie_ep_set_exs_reg completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "dbir") == 0){
			sscanf(argv[3], "%lx", (kulong*)&self->offset);
			sscanf(argv[4], "%lx", (kulong*)&self->data);
			ret = dd_pcie_ep_set_dbi_reg(dpEp, self->offset, self->data);
			Ddim_Print(("DBI AXI Slave Register\t0x%04X\t0x%08X\n", self->offset, self->data));
			Ddim_Print(("dd_pcie_ep_set_dbi_reg completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "drwe") == 0){	// DBI_RO_WR_EN
			ret = dd_pcie_ep_set_wr_acc_to_ro_reg(dpEp, (kboolean)atoi(argv[3]));
			Ddim_Print(("dd_pcie_ep_set_wr_acc_to_ro_reg completed. Return Value=0x%08X\n", ret));
		}
		else{
			Ddim_Print(("please check parameter!!\n"));
		}
	}
	else if(strcmp(argv[1], "get") == 0){
		if(strcmp(argv[2], "pmst") == 0){
			DdPciePmst pmst = dd_pcie_ep_get_pmst_status(dpEp);
			Ddim_Print(("dd_pcie_ep_get_pmst_status completed. PMST Status=%d\n", pmst));
		}
		else if(strcmp(argv[2], "ltssm") == 0){
			DdPcieStLtssm stLtssm = dd_pcie_ep_get_st_ltssm_status(dpEp);
			Ddim_Print(("dd_pcie_ep_get_st_ltssm_status completed. LTSSM Status=%d\n", stLtssm));
		}
		else if(strcmp(argv[2], "cls") == 0){
			ret = dd_pcie_ep_get_current_link_speed(dpEp, &self->currentLinkSpeed);
			Ddim_Print(("Current Link Speed\t0x%08X\n", self->currentLinkSpeed));
			Ddim_Print(("dd_pcie_ep_get_current_link_speed completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "aspm") == 0){
			ret = dd_pcie_ep_get_aspm_status(dpEp, &self->aspmStatus);
			Ddim_Print(("ASPM status\t0x%08X\n", self->aspmStatus));
			Ddim_Print(("dd_pcie_ep_get_aspm_status completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "mps") == 0){
			self->mps = (DdPcieMps)atoi(argv[3]);
			ret = dd_pcie_ep_get_mps(dpEp, &self->mps);
			if(ret == D_DDIM_OK){
				Ddim_Print(("Max Payload Size = %d\n", self->mps));
			}
			Ddim_Print(("dd_pcie_ep_get_mps completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "exsr") == 0){
			sscanf(argv[3], "%lx", (kulong*)&self->offset);
			ret = dd_pcie_ep_get_exs_reg(dpEp, self->offset, &self->data);
			Ddim_Print(("EXSTOP PCIe Register\t0x%04X\t0x%08X\n", self->offset, self->data));
			Ddim_Print(("dd_pcie_ep_get_exs_reg completed. Return Value=0x%08X\n", ret));
		}
		else if(strcmp(argv[2], "dbir") == 0){
			sscanf(argv[3], "%lx", (kulong*)&self->offset);
			ret = dd_pcie_ep_get_dbi_reg(dpEp, self->offset, &self->data);
			Ddim_Print(("DBI AXI Slave Register\t0x%04X\t0x%08X\n", self->offset, self->data));
			Ddim_Print(("dd_pcie_ep_get_dbi_reg completed. Return Value=0x%08X\n", ret));
		}
		else{
			Ddim_Print(("please check parameter!!\n"));
		}
	}
	else if(strcmp(argv[1], "int") == 0){
		if(strcmp(argv[2], "ep") == 0){
//			DdGic_DIST_SET_ISPENDR(8,0x00200000);	// 277 PCIE0(INT_EP)
			dd_pcie_ep_ch0_int_ep_handler(dpEp);
		}
		else if(strcmp(argv[2], "own") == 0){
			DdGic_DIST_SET_ISPENDR(8,0x00400000);	// 278 PCIE0(INT_OWN)
//			Dd_Pcie_Ep_Ch0_Int_Own_Handler();
		}
		else{
			Ddim_Print(("please check parameter!!\n"));
		}
	}
	else if(strcmp(argv[1], "memcmp") == 0){
		kuint32	addr1,addr2,size;
		sscanf(argv[2], "%lx", (kulong*)&addr1);
		sscanf(argv[3], "%lx", (kulong*)&addr2);
		sscanf(argv[4], "%lx", (kulong*)&size);
		ddim_user_custom_l1l2cache_flush_addr((kuint32)addr1, size);
		ddim_user_custom_l1l2cache_flush_addr((kuint32)addr2, size);
		if(memcmp((void*)addr1, (void*)addr2, size) == 0){
			Ddim_Print(("Memory Compare OK.\n"));
		}
		else{
			Ddim_Print(("Memory Compare NG.\n"));
		}
	}
	else if(strcmp(argv[1], "errmsg") == 0){
		ctDdPcieEpErrMsg(atoi(argv[2]));
	}
	else if(strcmp(argv[1], "ltr") == 0){
		ctDdPcieEpLtr();
	}
	else if(strcmp(argv[1], "err") == 0){
		if(dd_pcie_ep_ctrl_dma(dpEp, &self->ctrlDma) != C_PCIE_ACCESS_ERR){
			Ddim_Print(("dd_pcie_ep_ctrl_dma D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_start_dma(dpEp, 0,0) != C_PCIE_ACCESS_ERR){
			Ddim_Print(("dd_pcie_ep_start_dma D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_stop_dma(dpEp, 0,0) != C_PCIE_ACCESS_ERR){
			Ddim_Print(("dd_pcie_ep_stop_dma D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_ctrl_memory(dpEp, &self->ctrlMem) != C_PCIE_COMM_ERROR){
			Ddim_Print(("dd_pcie_ep_ctrl_memory D_DD_PCIE_COMM_ERROR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_req_int_ep(dpEp) != C_PCIE_ACCESS_ERR){
			Ddim_Print(("dd_pcie_ep_req_int_ep D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_transfer_msi(dpEp, 0) != C_PCIE_ACCESS_ERR){
			Ddim_Print(("dd_pcie_ep_transfer_msi D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_ctrl_aspm(dpEp, 3) != C_PCIE_ACCESS_ERR){
			Ddim_Print(("dd_pcie_ep_ctrl_aspm D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_transfer_speed_change(dpEp, 3) != C_PCIE_ACCESS_ERR){
			Ddim_Print(("dd_pcie_ep_transfer_speed_change D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_get_current_link_speed(dpEp, &self->currentLinkSpeed) != C_PCIE_ACCESS_ERR){
			Ddim_Print(("dd_pcie_ep_get_current_link_speed D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_get_aspm_status(dpEp, &self->aspmStatus) != C_PCIE_ACCESS_ERR){
			Ddim_Print(("dd_pcie_ep_get_aspm_status D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_get_exs_reg(dpEp, 1,&self->data) != C_PCIE_INPUT_PARAM_ERROR){
			Ddim_Print(("dd_pcie_ep_get_exs_reg D_DD_PCIE_INPUT_PARAM_ERROR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_get_exs_reg(dpEp, 0x0288,&self->data) != C_PCIE_INPUT_PARAM_ERROR){
			Ddim_Print(("dd_pcie_ep_get_exs_reg D_DD_PCIE_INPUT_PARAM_ERROR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_get_dbi_reg(dpEp, 1,&self->data) != C_PCIE_INPUT_PARAM_ERROR){
			Ddim_Print(("dd_pcie_ep_get_dbi_reg D_DD_PCIE_INPUT_PARAM_ERROR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_get_dbi_reg(dpEp, 0x0B48,&self->data) != C_PCIE_INPUT_PARAM_ERROR){
			Ddim_Print(("dd_pcie_ep_get_dbi_reg D_DD_PCIE_INPUT_PARAM_ERROR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_get_dbi_reg(dpEp, 0,&self->data) != C_PCIE_ACCESS_ERR){
			Ddim_Print(("dd_pcie_ep_get_dbi_reg D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(dd_pcie_ep_set_wr_acc_to_ro_reg(dpEp, 1) != C_PCIE_ACCESS_ERR){
			Ddim_Print(("dd_pcie_ep_set_wr_acc_to_ro_reg D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		Ddim_Print(("Error Check OK.\n"));
	}
	else{
		Ddim_Print(("please check parameter!!\n"));
	}
	k_object_unref(dpEp);
	dpEp = NULL;
	k_object_unref(dtStamp);
	dtStamp = NULL;
}

CtDdPcieEp *ct_dd_pcie_ep_new(void)
{
    CtDdPcieEp *self = k_object_new_with_private(CT_TYPE_DD_PCIE_EP, sizeof(CtDdPcieEpPrivate));
    return self;
}
