/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-03
*@author              	:杨升柄
*@brief               	:CtDdPcieRc类
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
#include "ddim_user_custom.h"
#include "dd_pcie_rc.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "dd_timestamp.h"
#include "ctddpcierc.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPcieRc, ct_dd_pcie_rc);
#define CT_DD_PCIE_RC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPcieRcPrivate,CT_TYPE_DD_PCIE_RC))

/*
 * Definition
 * 40MHz (Timestamp frequency)
 */
#define	CtDdPcieRc_PCIE_TIMESTAMP_FREQUENCY		(0x2625A00)

// coefficient for transfer time
// 1000000/CtDdPcieRc_PCIE_TIMESTAMP_FREQUENCY
#define CtDdPcieRc_PCIE_TIMESTAMP_K						(0.025)
#define CtDdPcieRc_PCIE_DMA_LL_ADDR						(0x55000000)

struct _CtDdPcieRcPrivate
{
};

/*
 * DECLS
 */
static void ctDdPcieRcIntDma_cb(kint32 status);
static void ctDdPcieRcIntMsi_cb(kint32 status);
static void ctDdPcieRcIntDc_cb(kint32 status);
static void ctDdPcieRcLlDma( void );
static void ctDdPcieRcLlDma2( void );

static void ct_dd_pcie_rc_constructor(CtDdPcieRc *self) 
{
	self->ret = 0;
}

static void ct_dd_pcie_rc_destructor(CtDdPcieRc *self) 
{
}

/*
 * IMPL
 */
static void ctDdPcieRcIntDma_cb(kint32 status)
{
	UINT64	timestampCounter;
	kulong		transferTime;

	Dd_TIMESTAMP_Get_Counter(&timestampCounter);
//	Dd_TIMESTAMP_Stop();
//	Dd_TIMESTAMP_Close();
	transferTime = (kulong)(timestampCounter * CtDdPcieRc_PCIE_TIMESTAMP_K);
	Ddim_Print(("[DD_PCIe_CT] DMA transfer time=%ld[us]\n", transferTime));

	Ddim_Print(("ctDdPcieRcIntDma_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntMsi_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntMsi_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntDc_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntDc_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcLlDma( void )
{
	kuint32 LinkedList[22];
	kuint32 tarnsData[3] = {0x87654321, 0xffedcba9, 0xddccbbaa};

	memcpy((void*)0x58000000, (void*)tarnsData, sizeof(tarnsData));
	DDIM_User_L1l2cache_Clean_Flush_Addr(0x58000000, sizeof(tarnsData));
	// Channel Control
	LinkedList[0]	= 0x00000001;
	// Transfer Size
	LinkedList[1]	= 0x00000004;
	// SAR Low
	LinkedList[2]	= 0x58000000;
	// SAR High
	LinkedList[3]	= 0x0;
	// DAR Low
	LinkedList[4]	= 0x5F000000;
	// DAR High
	LinkedList[5]	= 0x0;

	// Element 1
	// Channel Control
	LinkedList[6]	= 0x00000001;
	// Transfer Size
	LinkedList[7]	= 0x00000004;
	// SAR Low
	LinkedList[8]	= 0x58000004;
	// SAR High
	LinkedList[9]	= 0x0;
	// DAR Low
	LinkedList[10]	= 0x5F000004;
	// DAR High
	LinkedList[11]	= 0x0;

	// Element 2
	// Channel Control (Local Interrupt Enable)
	LinkedList[12]	= 0x00000009;
	// Transfer Size
	LinkedList[13]	= 0x00000004;
	// SAR Low
	LinkedList[14]	= 0x58000008;
	// SAR High
	LinkedList[15]	= 0x0;
	// DAR Low
	LinkedList[16]	= 0x5F000008;
	// DAR High
	LinkedList[17]	= 0x0;

	// Element 3
	// Channel Control (Linked List End)
	LinkedList[18]	= 0x00000004;
	LinkedList[19]	= 0x0;
	LinkedList[20]	= 0x0;
	LinkedList[21]	= 0x0;

	memcpy((void*)CtDdPcieRc_PCIE_DMA_LL_ADDR, (void*)LinkedList, sizeof(LinkedList));
	DDIM_User_L1l2cache_Clean_Flush_Addr(CtDdPcieRc_PCIE_DMA_LL_ADDR, sizeof(LinkedList));
}

static void ctDdPcieRcLlDma2( void )
{
	kuint32 LinkedList[22];

	// Element 0
	// Channel Control
	LinkedList[0]	= 0x00000001;
	// Transfer Size
	LinkedList[1]	= 0x00000004;
	// SAR Low
	LinkedList[2]	= 0x5F000000;
	// SAR High
	LinkedList[3]	= 0x0;
	// DAR Low
	LinkedList[4]	= 0x58000010;
	// DAR High
	LinkedList[5]	= 0x0;

	// Element 1
	// Channel Control
	LinkedList[6]	= 0x00000001;
	// Transfer Size
	LinkedList[7]	= 0x00000004;
	// SAR Low
	LinkedList[8]	= 0x5F000004;
	// SAR High
	LinkedList[9]	= 0x0;
	// DAR Low
	LinkedList[10]	= 0x58000014;
	// DAR High
	LinkedList[11]	= 0x0;

	// Element 2
	// Channel Control (Local Interrupt Enable)
	LinkedList[12]	= 0x00000009;
	// Transfer Size
	LinkedList[13]	= 0x00000004;
	// SAR Low
	LinkedList[14]	= 0x5F000008;
	// SAR High
	LinkedList[15]	= 0x0;
	// DAR Low
	LinkedList[16]	= 0x58000018;
	// DAR High
	LinkedList[17]	= 0x0;

	// Element 3
	// Channel Control (Linked List End)
	LinkedList[18]	= 0x00000004;
	LinkedList[19]	= 0x0;
	LinkedList[20]	= 0x0;
	LinkedList[21]	= 0x0;

	memcpy((void*)CtDdPcieRc_PCIE_DMA_LL_ADDR, (void*)LinkedList, sizeof(LinkedList));
	DDIM_User_L1l2cache_Clean_Flush_Addr(CtDdPcieRc_PCIE_DMA_LL_ADDR, sizeof(LinkedList));
}

/*
 * PUBLIC
 */
void ct_dd_pcie_rc_from_main(CtDdPcieRc* self, kint argc, kchar** argv)
{
	E_DD_PCIE_DMA_CH			dmach;
	E_DD_PCIE_DMA_DIR			dir;
	E_DD_PCIE_BIFURCATION	bifurcation;
	T_DD_TIMESTAMP_CTRL	timestampCtrl;

	 if(strcmp(argv[1], "open") == 0){
		self->ret = Dd_Pcie_Rc_Open((kint32)atoi(argv[2]));
		Ddim_Print(("Dd_Pcie_Rc_Open completed. Return Value=0x%08X\n", self->ret));
	}else if(strcmp(argv[1], "close") == 0){
		self->ret = Dd_Pcie_Rc_Close();
		Ddim_Print(("Dd_Pcie_Rc_Close completed. Return Value=0x%08X\n", self->ret));
	}else if(strcmp(argv[1], "init") == 0){
		bifurcation = (E_DD_PCIE_BIFURCATION)atoi(argv[2]);
		Dd_Pcie_Rc_Init(bifurcation);
		Ddim_Print(("Dd_Pcie_Rc_Init completed.\n"));
	}else if(strcmp(argv[1], "deinit") == 0){
		Dd_Pcie_Rc_Deinit();
		Ddim_Print(("Dd_Pcie_Rc_Deinit completed.\n"));
	}else if(strcmp(argv[1], "lnkst") == 0){
		BOOL link_status;
		self->ch = (E_DD_PCIE_CH)atoi(argv[2]);
		link_status = Dd_Pcie_Rc_Get_Link_Status(self->ch);
		Ddim_Print(("Dd_Pcie_Rc_Get_Link_Status completed. Link Status=%d\n", link_status));
	}else if(strcmp(argv[1], "ctrl") == 0){
		if(strcmp(argv[2], "conf") == 0){
			self->pcieCtrlCfg.ch = (E_DD_PCIE_CH)atoi(argv[3]);
			sscanf(argv[4], "%lx", (kulong*)&self->pcieCtrlCfg.base_adr);
			sscanf(argv[5], "%lx", (kulong*)&self->pcieCtrlCfg.limit_adr);
			self->ret = Dd_Pcie_Rc_Ctrl_Config(&self->pcieCtrlCfg);
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Config completed. Return Value=0x%08X\n", self->ret));
		}else if(strcmp(argv[2], "dma") == 0){
			memset(&self->ctrlDma,0,sizeof(self->ctrlDma));
			self->ctrlDma.ch		= (E_DD_PCIE_CH)atoi(argv[3]);
			self->ctrlDma.mode	= (E_DD_PCIE_DMA_TRANS_MODE)atoi(argv[4]);
			self->ctrlDma.dma_ch	= (E_DD_PCIE_DMA_CH)atoi(argv[5]);
			sscanf(argv[6], "%lx", (kulong*)&self->ctrlDma.dmnd_src_addr_l);
			sscanf(argv[7], "%lx", (kulong*)&self->ctrlDma.dmnd_dst_addr_l);
			self->ctrlDma.dmnd_dst_addr_h = 0;
			sscanf(argv[8], "%lx", (kulong*)&self->ctrlDma.dmnd_trans_size);
			self->ctrlDma.direction	= (E_DD_PCIE_DMA_DIR)atoi(argv[9]);
			if(strcmp(argv[10], "0") == 0){
				self->ctrlDma.int_dma_cb = NULL;
			}else
			{
				self->ctrlDma.int_dma_cb = (VP_CALLBACK_PCIE)ctDdPcieRcIntDma_cb;
			}
			if(self->ctrlDma.mode == E_DD_PCIE_DMA_LL_MODE){
				self->ctrlDma.ll_addr = CtDdPcieRc_PCIE_DMA_LL_ADDR;
				// Write
				if(self->ctrlDma.direction == E_DD_PCIE_DMA_DIR_STOD){
					ctDdPcieRcLlDma();
				// Read
				}else
				{
					ctDdPcieRcLlDma2();
				}
			}
			self->ret = Dd_Pcie_Rc_Ctrl_Dma(&self->ctrlDma);
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Dma completed. Return Value=0x%08X\n", self->ret));
		}else if(strcmp(argv[2], "mem") == 0){
			memset(&self->ctrlMem,0,sizeof(self->ctrlMem));;
			self->ctrlMem.ch = (E_DD_PCIE_CH)atoi(argv[3]);
			sscanf(argv[4], "%lx", (kulong*)&self->ctrlMem.base_adr);
			sscanf(argv[5], "%lx", (kulong*)&self->ctrlMem.limit_adr);
			sscanf(argv[6], "%lx", (kulong*)&self->ctrlMem.low_target_adr);
			self->ret = Dd_Pcie_Rc_Ctrl_Memory(&self->ctrlMem);
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Memory completed. Return Value=0x%08X\n", self->ret));
		}else if(strcmp(argv[2], "msi") == 0){
			memset(&self->pcieCtrlMsi,0,sizeof(self->pcieCtrlMsi));
			self->pcieCtrlMsi.ch = (E_DD_PCIE_CH)atoi(argv[3]);
			sscanf(argv[4], "%lx", (kulong*)&self->pcieCtrlMsi.int_en);
			sscanf(argv[5], "%lx", (kulong*)&self->pcieCtrlMsi.cmp_adr);
			if(strcmp(argv[6], "1") == 0){
				self->pcieCtrlMsi.int_msi_cb = (VP_CALLBACK_PCIE)ctDdPcieRcIntMsi_cb;
			}
			self->ret = Dd_Pcie_Rc_Ctrl_Msi(&self->pcieCtrlMsi);
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Msi completed. Return Value=0x%08X\n", self->ret));
		}else if(strcmp(argv[2], "aspm") == 0){
			E_DD_PCIE_ASPM_CONTROL aspmlv;
			self->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			aspmlv = (E_DD_PCIE_ASPM_CONTROL)atoi(argv[4]);
			self->ret = Dd_Pcie_Rc_Ctrl_Aspm(self->ch, aspmlv);
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Aspm completed. Return Value=0x%08X\n", self->ret));
		}else if(strcmp(argv[2], "hdc") == 0){
			self->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			if(strcmp(argv[4], "1") == 0){
				self->ret = Dd_Pcie_Rc_Ctrl_Detect_Card(self->ch, (VP_CALLBACK_PCIE)ctDdPcieRcIntDc_cb);
			}else
			{
				self->ret = Dd_Pcie_Rc_Ctrl_Detect_Card(self->ch, NULL);
			}
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Detect_Card completed. Return Value=0x%08X\n", self->ret));
		}else
		{
			Ddim_Print(("please check parameter!!\n"));
		}
	}else if(strcmp(argv[1], "dma") == 0){
		self->ch		= (E_DD_PCIE_CH)atoi(argv[3]);
		dmach	= (E_DD_PCIE_DMA_CH)atoi(argv[4]);
		dir		= (E_DD_PCIE_DMA_DIR)atoi(argv[5]);
		if(strcmp(argv[2], "start") == 0){
			// has no effect
			timestampCtrl.hdbg			= 0;
			// Counter
			timestampCtrl.counter		= 0;
			timestampCtrl.frequency	= CtDdPcieRc_PCIE_TIMESTAMP_FREQUENCY;
			Dd_TIMESTAMP_Init();
			if (Dd_TIMESTAMP_Open(D_DDIM_USER_SEM_WAIT_POL) != D_DDIM_OK) {
				Ddim_Print(("Dd_TIMESTAMP has already opened.\n"));
				Dd_TIMESTAMP_Stop();
				Dd_TIMESTAMP_Close();
				if (Dd_TIMESTAMP_Open(D_DDIM_USER_SEM_WAIT_POL) != D_DDIM_OK) {
					Ddim_Print(("Dd_TIMESTAMP_Open Error.\n"));
				}
			}
			Dd_TIMESTAMP_Ctrl(&timestampCtrl);
			Dd_TIMESTAMP_Start();

			self->ret = Dd_Pcie_Rc_Start_Dma(self->ch, dmach, dir);
			Ddim_Print(("Dd_Pcie_Rc_start_Dma completed. Return Value=0x%08X\n", self->ret));
		}else if(strcmp(argv[2], "stop") == 0){
			self->ret = Dd_Pcie_Rc_Stop_Dma(self->ch, dmach, dir);
			Ddim_Print(("Dd_Pcie_Rc_Stop_Dma completed. Return Value=0x%08X\n", self->ret));
		}else
		{
			Ddim_Print(("please check parameter!!\n"));
		}
	}
}

CtDdPcieRc* ct_dd_pcie_rc_new(void) 
{
    CtDdPcieRc *self = k_object_new_with_private(CT_TYPE_DD_PCIE_RC, sizeof(CtDdPcieRcPrivate));
    return self;
}
