/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-03
*@author              	:杨升柄
*@brief               	:CtDdPcieMain类
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
#include "ctddpciemain.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPcieMain, ct_dd_pcie_main);
#define CT_DD_PCIE_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPcieMainPrivate,CT_TYPE_DD_PCIE_MAIN))

struct _CtDdPcieMainPrivate
{
	CtDdPcieRc* pcieRc;
};

/*
 * Enumeration
 *
 * Nothing Special
 *
 * Structure
 *
 * Nothing Special
 *
 * Global Data
 */
static T_DD_PCIE_RC_INT_TRS_ICS_MSI_CB S_GCTDD_PCIE_INT_TIM_CB[2] =
{
		{NULL, NULL, NULL},
		{NULL, NULL, NULL}
};
static T_DD_PCIE_RC_INT_SYS_ERR_CB S_GCTDD_PCIE_INT_SYS_ERR_CB[2] =
{
		{NULL, NULL},
		{NULL, NULL}
};
static T_DD_PCIE_RC_INT_EP_CB S_GCTDD_PCIE_INT_EP_CB[2] =
{
		{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
		{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
};
static T_DD_PCIE_RC_INT_OWN_CB S_GCTDD_PCIE_INT_OWN_CB[2] =
{
		{NULL, NULL, NULL, NULL},
		{NULL, NULL, NULL, NULL}
};

/*
 * DECLS
 */
static void ctDdPcieRcIntOwnCfgPme_cb(kint32 status);
static void ctDdPcieRcIntOwnHp_cb(kint32 status);
static void ctDdPcieRcIntOwnRdlhLinkUp_cb(kint32 status);
static void ctDdPcieRcIntOwnWake_cb(kint32 status);
static void ctDdPcieRcIntEpRix_cb(kint32 status);
static void ctDdPcieRcIntEpRpp_cb(kint32 status);
static void ctDdPcieRcIntEpRce_cb(kint32 status);
static void ctDdPcieRcIntEpRne_cb(kint32 status);
static void ctDdPcieRcIntEpRfe_cb(kint32 status);
static void ctDdPcieRcIntEpRml_cb(kint32 status);
static void ctDdPcieRcIntEpRpta_cb(kint32 status);
static void ctDdPcieRcIntEpRvm_cb(kint32 status);
static void ctDdPcieRcIntSysErrCare_cb(kint32 status);
static void ctDdPcieRcIntSysErrCser_cb(kint32 status);
static void ctDdPcieRcIntTimClab_cb(kint32 status);
static void ctDdPcieRcIntTimCbmi_cb(kint32 status);
static void ctDdPcieRcIntTimSrrn_cb(kint32 status);
static void ctDdPcieRcLtr( E_DD_PCIE_CH ch );

static void ct_dd_pcie_main_constructor(CtDdPcieMain *self)
{
	CtDdPcieMainPrivate *priv = CT_DD_PCIE_MAIN_GET_PRIVATE(self);

	priv->pcieRc = ct_dd_pcie_rc_new();
	self->priv = priv;
}

static void ct_dd_pcie_main_destructor(CtDdPcieMain *self)
{
	CtDdPcieMainPrivate *priv = CT_DD_PCIE_MAIN_GET_PRIVATE(self);

	if(priv->pcieRc)
	{
		k_object_unref(priv->pcieRc);
	}
	priv->pcieRc = NULL;

}

/*
 * IMPL
 *
 * Macro
 *
 * Nothing Special *
 *
 * Local Method Definition
 *
 * Nothing Special
 *
 * Local Function
 */
static void ctDdPcieRcIntOwnCfgPme_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntOwnCfgPme_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntOwnHp_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntOwnHp_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntOwnRdlhLinkUp_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntOwnRdlhLinkUp_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntOwnWake_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntOwnWake_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntEpRix_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntEpRix_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntEpRpp_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntEpRpp_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntEpRce_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntEpRce_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntEpRne_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntEpRne_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntEpRfe_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntEpRfe_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntEpRml_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntEpRml_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntEpRpta_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntEpRpta_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntEpRvm_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntEpRvm_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntSysErrCare_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntSysErrCare_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntSysErrCser_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntSysErrCser_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntTimClab_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntTimClab_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntTimCbmi_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntTimCbmi_cb called. Status=0x%08X\n", status));
}

static void ctDdPcieRcIntTimSrrn_cb(kint32 status)
{
	Ddim_Print(("ctDdPcieRcIntTimSrrn_cb called. Status=0x%08X\n", status));
}

// Latency Tolerance Reporting (LTR) Mechanism
static void ctDdPcieRcLtr( E_DD_PCIE_CH ch )
{
	if(ch == E_DD_PCIE_CH0){
		// LTR Mechanism Enable
		IO_PCIE0_CORE.RC.PCIECR.DC2SR.bit.LTRME = 1;
	}
	else{
		// LTR Mechanism Enable
		IO_PCIE1_CORE.RC.PCIECR.DC2SR.bit.LTRME = 1;
	}
}

/*
 * Global Function
 * PUBLIC
 **
 *	@brief	Command main function for PCIe test.
 *	@param	kint argc	:The number of parameters
 *			kchar** argv	:The value of parameters
 *
 *	The meaning of parameters
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| P1	| P2	| P3 	| P4	| P5	| P6	| P7	| P8	| P9	| P10	| P11	| Meaning										|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| open	| tout	|		|		|		|		|		|		|		|		|		| PCIe open										|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| close	|		|		|		|		|		|		|		|		|		|		| PCIe close									|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| init	| bif	| 		|		|		|		|		|		|		|		|		| PCIe initialize								|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| deinit|		| 		|		|		|		|		|		|		|		|		| PCIe deinit									|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| lnkst	| ch	|		|		|		|		|		|		|		|		|		| Get link status								|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| ctrl	| conf	| ch	| bar	| lar	|		|		|		|		|		|		| Set config transfer							|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| ctrl	| dma	| ch	|dmd	| dmach	| srcadr| dstadr| size	| dir	|  cb	|		| Set dma transfer 								|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| ctrl	| mem	| ch	| bar	| ladr	| tadr	|		|		|		|		|		| Set memory transfer							|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| ctrl	| msi	| ch	| ie	| ca	| cb	|		|		|		|		|		| Set MSI										|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| ctrl	| aspm	| ch	| aspmlv| 		| 		|		|		|		|		|		| ASPM control									|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| dma	| start	| ch	| dmach	| dir	|		|		|		|		|		|		| DMA start										|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| dma	| stop	| ch	| dmach	| dir	|		|		|		|		|		|		| DMA stop										|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| chtrsp| ch	| lnksp	|		|		|		|		|		|		|		| Set Change Transfer Speed.					|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| vid	| hwdat	|		|		|		|		|		|		|		|		| Set vender id									|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| did	| hwdat	|		|		|		|		|		|		|		|		| Set device id									|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| d1s	| spt	|		|		|		|		|		|		|		|		| Set D1 support								|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| d2s	| spt	|		|		|		|		|		|		|		|		| Set D2 support								|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| iowcb	| ch	| pme	| cb	|		|		|		|		|		|		| Set INT_OWN PME CB							|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| iowcb	| ch	| hp	| cb	|		|		|		|		|		|		| Set INT_OWN Hot-Plug callback					|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| iowcb	| ch	| lu	| cb	|		|		|		|		|		|		| Set INT_OWN Link Up callback					|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| iowcb	| ch	| wake	| cb	|		|		|		|		|		|		| Set INT_OWN Wake callback						|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| iepcb	| ch	| type	|		|		|		|		|		|		|		| Set INT_EP callback							|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| isecb	| ch	| care	| cb	|		|		|		|		|		|		| Set INT_SYS_ERR cfg_aer_rc_err_int/msi callback	|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| isecb	| ch	| cser	| cb	|		|		|		|		|		|		| Set INT_SYS_ERR cfg_sys_err_rc callback		|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| iticb	| ch	| clab	| cb	|		|		|		|		|		|		| Set INT_TRS_ICS_MSI cfg_link_auto_bw_int callback	|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| iticb	| ch	| cbmi	| cb	|		|		|		|		|		|		| Set INT_TRS_ICS_MSI cfg_bw_mgt_int_cb callback	|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| iticb	| ch	| srrn	| cb	|		|		|		|		|		|		| Set INT_TRS_ICS_MSI smlh_req_rst_not_cb callback	|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| pw	| ch	| L2	|		|		|		|		|		|		|		| Set Power Turn Off Request. (L2 Entry)		|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| set	| pw	| ch	| L0	|		|		|		|		|		|		|		| Set Power L2 Exit. (L0 Entry)					|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| get	| pmst	| ch	| 		|		|		|		|		|		|		|		| Get Power State.								|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| get	| ltssm	| ch	| 		|		|		|		|		|		|		|		| Get LTSSM State.								|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| get	| cls	| ch	| 		|		|		|		|		|		|		|		| Get Current Link Speed.						|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| get	| aspm	| ch	| 		|		|		|		|		|		|		|		| Get ASPM status.								|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| kint	| own	| ch	| 		|		|		|		|		|		|		|		| Interrupt INT_OWN.							|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| kint	| se	| ch	| 		|		|		|		|		|		|		|		| Interrupt INT_SYS_ERR.						|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| kint	| tim	| ch	| 		|		|		|		|		|		|		|		| Interrupt INT_TRS_ICS_MSI.					|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	| kint	| ep	| ch	| 		|		|		|		|		|		|		|		| Interrupt INT_EP.								|
 *	+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------------------------------------------+
 *	tout	: 0(Wait by Polling), 1~n(timeout sec)
 *	bif		: 0(bifurcation disable), 1(bifurcation enable)
 *	ch		: 0(PCIE0), 1(PCIE1)
 *	bar		: hex string of base address (32bit)
 *	lar		: hex string of limit address (32bit)
 *	tar		: hex string of target address (32bit)
 *	dmd		: 0(Demand DMA transfer), 1(Linked List DMA transfer)
 *	dmach	: 0,1
 *	srcadr	: Demand dma transfer source address
 *	dadrl	: Demand dma transfer destination lower address
 *	size	: Demand dma transfer total size
 *	tbladr	: Descriptor dma transfer table address (4Byte)
 *	dir		: 0(destination to source), 1(source to destination)
 *	mrr		: 0(4multiple request occur),1(Single request occur),2(2multiple request occur),3(3multiple request occur)
 *	cb		: 0(callback off), 1(callback on)
 *	ladr	: hex string of limit address
 *	tadr	: hex string of target address
 *	rw		: 0(read), 1(write)
 *	hwdat	: hex string of harf word data
 *	sn		: hex string of lower serial number (32bit)
 *	spt		: 0(unsupport), 1(support)
 *	type	: 0(INTX), 1(MSI)
 *	ie		: hex string of Interrupt enable
 *	ca		: hex string of compare address
 *	aspmlv	: 0(Disabled), 1(L0s Entry Enabled), 2(L1 Entry Enabled), 3(L0s and L1 Entry Enabled)
 *	lnksp	: 1(GEN1), 2(GEN2)
 *
 *	@return void
 */
void ct_dd_pcie_main_test(CtDdPcieMain* self, kint argc, kchar** argv)
{
	CtDdPcieMainPrivate* 		priv = self->priv;
	kushort								offset;
	kuint32								data;
	E_DD_PCIE_MPS					mps;

	 ct_dd_pcie_rc_from_main(self->priv->pcieRc, argc, argv);

	if(strcmp(argv[1], "set") == 0){
		if(strcmp(argv[2], "chtrsp") == 0){
			priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			priv->pcieRc->ret = Dd_Pcie_Rc_Transfer_Speed_Change(priv->pcieRc->ch,
					(E_DD_PCIE_LINK_SPEED)atoi(argv[4]));
			Ddim_Print(("Dd_Pcie_Rc_Transfer_Speed_Change completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "iowcb") == 0){
			priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			if(strcmp(argv[4], "pme") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_OWN_CB[priv->pcieRc->ch].cfg_pme_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntOwnCfgPme_cb;
				}else
				{
					S_GCTDD_PCIE_INT_OWN_CB[priv->pcieRc->ch].cfg_pme_cb = NULL;
				}
			}else if(strcmp(argv[4], "hp") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_OWN_CB[priv->pcieRc->ch].hp_cb = (VP_CALLBACK_PCIE)ctDdPcieRcIntOwnHp_cb;
				}else
				{
					S_GCTDD_PCIE_INT_OWN_CB[priv->pcieRc->ch].hp_cb = NULL;
				}
			}else if(strcmp(argv[4], "lu") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_OWN_CB[priv->pcieRc->ch].rdlh_link_up_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntOwnRdlhLinkUp_cb;
				}else
				{
					S_GCTDD_PCIE_INT_OWN_CB[priv->pcieRc->ch].rdlh_link_up_cb = NULL;
				}
			}else if(strcmp(argv[4], "wake") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_OWN_CB[priv->pcieRc->ch].wake_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntOwnWake_cb;
				}else
				{
					S_GCTDD_PCIE_INT_OWN_CB[priv->pcieRc->ch].wake_cb = NULL;
				}
			}else
			{
				Ddim_Print(("please check parameter!!\n"));
				return;
			}
			priv->pcieRc->ret = Dd_Pcie_Rc_Set_Int_Own_Func(priv->pcieRc->ch,
					&S_GCTDD_PCIE_INT_OWN_CB[priv->pcieRc->ch]);
			Ddim_Print(("Dd_Pcie_Rc_Set_Int_Own_Func completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "iepcb") == 0){
			priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			if(strcmp(argv[4], "rix") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_intx_cb = (VP_CALLBACK_PCIE)ctDdPcieRcIntEpRix_cb;
				}else
				{
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_intx_cb = NULL;
				}
			}else if(strcmp(argv[4], "rpp") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_pm_pme_cb = (VP_CALLBACK_PCIE)ctDdPcieRcIntEpRpp_cb;
				}else
				{
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_pm_pme_cb = NULL;
				}
			}else if(strcmp(argv[4], "rce") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_correctable_err_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntEpRce_cb;
				}else
				{
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_correctable_err_cb = NULL;
				}
			}else if(strcmp(argv[4], "rne") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_nonfatal_err_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntEpRne_cb;
				}else
				{
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_nonfatal_err_cb = NULL;
				}
			}else if(strcmp(argv[4], "rfe") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_fatal_err_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntEpRfe_cb;
				}else
				{
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_fatal_err_cb = NULL;
				}
			}else if(strcmp(argv[4], "rml") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_msg_ltr_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntEpRml_cb;
					// Latency Tolerance Reporting (LTR) Mechanism
					ctDdPcieRcLtr(priv->pcieRc->ch);
				}else
				{
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_msg_ltr_cb = NULL;
				}
			}else if(strcmp(argv[4], "rpta") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_pm_to_ack_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntEpRpta_cb;
				}else
				{
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_pm_to_ack_cb = NULL;
				}
			}else if(strcmp(argv[4], "rvm") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_vendor_msg_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntEpRvm_cb;
				}else
				{
					S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch].radm_vendor_msg_cb = NULL;
				}
			}else
			{
				Ddim_Print(("please check parameter!!\n"));
				return;
			}

			priv->pcieRc->ret = Dd_Pcie_Rc_Set_Int_Ep_Func(priv->pcieRc->ch,
					&S_GCTDD_PCIE_INT_EP_CB[priv->pcieRc->ch]);
			Ddim_Print(("Dd_Pcie_Rc_Set_Int_Ep_Func completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "isecb") == 0){
			priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			if(strcmp(argv[4], "care") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_SYS_ERR_CB[priv->pcieRc->ch].cfg_aer_rc_err_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntSysErrCare_cb;
				}else
				{
					S_GCTDD_PCIE_INT_SYS_ERR_CB[priv->pcieRc->ch].cfg_aer_rc_err_cb = NULL;
				}
			}else if(strcmp(argv[4], "cser") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_SYS_ERR_CB[priv->pcieRc->ch].cfg_sys_err_rc_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntSysErrCser_cb;
				}else
				{
					S_GCTDD_PCIE_INT_SYS_ERR_CB[priv->pcieRc->ch].cfg_sys_err_rc_cb = NULL;
				}
			}else
			{
				Ddim_Print(("please check parameter!!\n"));
				return;
			}
			priv->pcieRc->ret = Dd_Pcie_Rc_Set_Int_Sys_Err_Func(priv->pcieRc->ch,
					&S_GCTDD_PCIE_INT_SYS_ERR_CB[priv->pcieRc->ch]);
			Ddim_Print(("Dd_Pcie_Rc_Set_Int_Sys_Err_Func completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "iticb") == 0){
			priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			if(strcmp(argv[4], "clab") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_TIM_CB[priv->pcieRc->ch].cfg_link_auto_bw_int_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntTimClab_cb;
				}else
				{
					S_GCTDD_PCIE_INT_TIM_CB[priv->pcieRc->ch].cfg_link_auto_bw_int_cb = NULL;
				}
			}else if(strcmp(argv[4], "cbmi") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_TIM_CB[priv->pcieRc->ch].cfg_bw_mgt_int_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntTimCbmi_cb;
				}else
				{
					S_GCTDD_PCIE_INT_TIM_CB[priv->pcieRc->ch].cfg_bw_mgt_int_cb = NULL;
				}
			}else if(strcmp(argv[4], "srrn") == 0){
				if(strcmp(argv[5], "1") == 0){
					S_GCTDD_PCIE_INT_TIM_CB[priv->pcieRc->ch].smlh_req_rst_not_cb =
							(VP_CALLBACK_PCIE)ctDdPcieRcIntTimSrrn_cb;
				}else
				{
					S_GCTDD_PCIE_INT_TIM_CB[priv->pcieRc->ch].smlh_req_rst_not_cb = NULL;
				}
			}
			priv->pcieRc->ret = Dd_Pcie_Rc_Set_Int_Trs_Ics_Msi_Func(priv->pcieRc->ch,
					&S_GCTDD_PCIE_INT_TIM_CB[priv->pcieRc->ch]);
			Ddim_Print(("Dd_Pcie_Rc_Set_Int_Trs_Ics_Msi_Func completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "pw") == 0){
			priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			if(strcmp(argv[4], "l2") == 0 || strcmp(argv[4], "L2") == 0){
				priv->pcieRc->ret = Dd_Pcie_Rc_Pm_Pw_Turn_Off_Req(priv->pcieRc->ch);
				Ddim_Print(("Dd_Pcie_Rc_Pm_Pw_Turn_Off_Req completed. Return Value=0x%08X\n", priv->pcieRc->ret));
			}else if(strcmp(argv[4], "l0") == 0 || strcmp(argv[4], "L0") == 0){
				priv->pcieRc->ret = Dd_Pcie_Rc_Pm_Pw_L2_Exit(priv->pcieRc->ch);
				Ddim_Print(("Dd_Pcie_Rc_Pm_Pw_L2_Exit completed. Return Value=0x%08X\n", priv->pcieRc->ret));
			}else
			{
				Ddim_Print(("please check parameter!!\n"));
			}
		}else if(strcmp(argv[2], "mps") == 0){
			priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			mps = (E_DD_PCIE_MPS)atoi(argv[4]);
			priv->pcieRc->ret = Dd_Pcie_Rc_Set_Mps(priv->pcieRc->ch, mps);
			Ddim_Print(("Dd_Pcie_Rc_Set_Mps completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "conf") == 0){
			priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			sscanf(argv[4], "%lx", (kulong*)&offset);
			sscanf(argv[5], "%lx", (kulong*)&data);
			priv->pcieRc->ret = Dd_Pcie_Rc_Config_Write(priv->pcieRc->ch, offset, data);
			Ddim_Print(("Config Register\t0x%04X\t0x%08X\n", offset, data));
			Ddim_Print(("Dd_Pcie_Rc_Config_Write completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "exsr") == 0){
			priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			sscanf(argv[4], "%lx", (kulong*)&offset);
			sscanf(argv[5], "%lx", (kulong*)&data);
			priv->pcieRc->ret = Dd_Pcie_Rc_Set_Exs_Reg(priv->pcieRc->ch, offset, data);
			Ddim_Print(("EXSTOP PCIe Register\t0x%04X\t0x%08X\n", offset, data));
			Ddim_Print(("Dd_Pcie_Rc_Set_Exs_Reg completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "dbir") == 0){
			priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			sscanf(argv[4], "%lx", (kulong*)&offset);
			sscanf(argv[5], "%lx", (kulong*)&data);
			priv->pcieRc->ret = Dd_Pcie_Rc_Set_Dbi_Reg(priv->pcieRc->ch, offset, data);
			Ddim_Print(("DBI AXI Slave Register\t0x%04X\t0x%08X\n", offset, data));
			Ddim_Print(("Dd_Pcie_Rc_Set_Dbi_Reg completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		// DBI_RO_WR_EN
		}else if(strcmp(argv[2], "drwe") == 0){
			priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			priv->pcieRc->ret = Dd_Pcie_Rc_Set_Wr_Acc_To_Ro_Reg(priv->pcieRc->ch, (BOOL)atoi(argv[4]));
			Ddim_Print(("Dd_Pcie_Rc_Set_Wr_Acc_To_Ro_Reg completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}
		else{
			Ddim_Print(("please check parameter!!\n"));
		}
	}
	else if(strcmp(argv[1], "get") == 0){
		priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
		if(strcmp(argv[2], "pmst") == 0){
			E_DD_PCIE_PMST pmst = Dd_Pcie_Rc_Get_PMST_Status(priv->pcieRc->ch);
			Ddim_Print(("Dd_Pcie_Rc_Get_PMST_Status completed. PMST Status=%d\n", pmst));
		}else if(strcmp(argv[2], "ltssm") == 0){
			E_DD_PCIE_ST_LTSSM st_ltssm = Dd_Pcie_Rc_Get_ST_LTSSM_Status(priv->pcieRc->ch);
			Ddim_Print(("Dd_Pcie_Rc_Get_ST_LTSSM_Status completed. LTSSM Status=%d\n", st_ltssm));
		}else if(strcmp(argv[2], "cls") == 0){
			E_DD_PCIE_LINK_SPEED current_link_speed;
			priv->pcieRc->ret = Dd_Pcie_Rc_Get_Current_Link_Speed(priv->pcieRc->ch, &current_link_speed);
			Ddim_Print(("Current Link Speed\t0x%08X\n", current_link_speed));
			Ddim_Print(("Dd_Pcie_Rc_Get_Current_Link_Speed completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "aspm") == 0){
			E_DD_PCIE_ASPM_CONTROL aspm_status;
			priv->pcieRc->ret = Dd_Pcie_Rc_Get_Aspm_Status(priv->pcieRc->ch, &aspm_status);
			Ddim_Print(("ASPM status\t0x%08X\n", aspm_status));
			Ddim_Print(("Dd_Pcie_Rc_Get_Aspm_Status completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "mps") == 0){
			priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
			priv->pcieRc->ret = Dd_Pcie_Rc_Get_Mps(priv->pcieRc->ch, &mps);
			if(priv->pcieRc->ret == D_DDIM_OK){
				Ddim_Print(("Max Payload Size = %d\n", mps));
			}
			Ddim_Print(("Dd_Pcie_Rc_Set_Mps completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "conf") == 0){
			sscanf(argv[4], "%lx", (kulong*)&offset);
			priv->pcieRc->ret = Dd_Pcie_Rc_Config_Read(priv->pcieRc->ch, offset, &data);
			Ddim_Print(("Config Register\t0x%04X\t0x%08X\n", offset, data));
			Ddim_Print(("Dd_Pcie_Rc_Config_Read completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "exsr") == 0){
			sscanf(argv[4], "%lx", (kulong*)&offset);
			priv->pcieRc->ret = Dd_Pcie_Rc_Get_Exs_Reg(priv->pcieRc->ch, offset, &data);
			Ddim_Print(("EXSTOP PCIe Register\t0x%04X\t0x%08X\n", offset, data));
			Ddim_Print(("Dd_Pcie_Rc_Get_Exs_Reg completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}else if(strcmp(argv[2], "dbir") == 0){
			sscanf(argv[4], "%lx", (kulong*)&offset);
			priv->pcieRc->ret = Dd_Pcie_Rc_Get_Dbi_Reg(priv->pcieRc->ch, offset, &data);
			Ddim_Print(("DBI AXI Slave Register\t0x%04X\t0x%08X\n", offset, data));
			Ddim_Print(("Dd_Pcie_Rc_Get_Dbi_Reg completed. Return Value=0x%08X\n", priv->pcieRc->ret));
		}
		else{
			Ddim_Print(("please check parameter!!\n"));
		}
	}
	else if(strcmp(argv[1], "kint") == 0){
		priv->pcieRc->ch = (E_DD_PCIE_CH)atoi(argv[3]);
		if(strcmp(argv[2], "tim") == 0){
			if(priv->pcieRc->ch == 0){
				//Dd_GIC_DIST_Set_ISPendr(8,0x00080000);	// 275 PCIE0(INT_TRS_ICS_MSI)
				Dd_Pcie_Rc_Ch0_Int_Trs_Ics_Msi_Handler();
			}else
			{
				//Dd_GIC_DIST_Set_ISPendr(8,0x01000000);	// 280 PCIE1(INT_TRS_ICS_MSI)
				Dd_Pcie_Rc_Ch1_Int_Trs_Ics_Msi_Handler();
			}
		}else if(strcmp(argv[2], "se") == 0){
			if(priv->pcieRc->ch == 0){
				//Dd_GIC_DIST_Set_ISPendr(8,0x00100000);	// 276 PCIE0(INT_SYS_ERR)
				Dd_Pcie_Rc_Ch0_Int_Sys_Err_Handler();
			}else
			{
				//Dd_GIC_DIST_Set_ISPendr(8,0x02000000);	// 281 PCIE1(INT_SYS_ERR)
				Dd_Pcie_Rc_Ch1_Int_Sys_Err_Handler();
			}
		}else if(strcmp(argv[2], "ep") == 0){
			if(priv->pcieRc->ch == 0){
				//Dd_GIC_DIST_Set_ISPendr(8,0x00200000);	// 277 PCIE0(INT_EP)
				Dd_Pcie_Rc_Ch0_Int_Ep_Handler();
			}else
			{
				//Dd_GIC_DIST_Set_ISPendr(8,0x04000000);	// 282 PCIE1(INT_EP)
				Dd_Pcie_Rc_Ch1_Int_Ep_Handler();
			}
		}else if(strcmp(argv[2], "own") == 0){
			if(priv->pcieRc->ch == 0){
				//Dd_GIC_DIST_Set_ISPendr(8,0x00400000);	// 278 PCIE0(INT_OWN)
				Dd_Pcie_Rc_Ch0_Int_Own_Handler();
			}else
			{
				//Dd_GIC_DIST_Set_ISPendr(8,0x08000000);	// 283 PCIE1(INT_OWN)
				Dd_Pcie_Rc_Ch1_Int_Own_Handler();
			}
		}
		else{
			Ddim_Print(("please check parameter!!\n"));
		}
	}
	else if( strcmp(argv[1], "memcmp") == 0 ){
		kuint32	addr1,addr2,size;
		sscanf(argv[2], "%lx", (kulong*)&addr1);
		sscanf(argv[3], "%lx", (kulong*)&addr2);
		sscanf(argv[4], "%lx", (kulong*)&size);
		DDIM_User_L1l2cache_Flush_Addr((kuint32)addr1, size);
		DDIM_User_L1l2cache_Flush_Addr((kuint32)addr2, size);
		if(memcmp((void*)addr1, (void*)addr2, size) == 0){
			Ddim_Print(("Memory Compare OK.\n"));
		}
		else{
			Ddim_Print(("Memory Compare NG.\n"));
		}
	}
	else if(strcmp(argv[1], "flash") == 0){
		kuint32 address, size;
		sscanf(argv[2], "%lx", (kulong*)&address);
		sscanf(argv[3], "%lx", (kulong*)&size);
		Ddim_Print(("address = 0x%08X, size = 0x%08X\n", address, size));
		DDIM_User_L1l2cache_Flush_Addr(address, size);
	}
	else if(strcmp(argv[1], "err") == 0){
		if(Dd_Pcie_Rc_Ctrl_Config(&priv->pcieRc->pcieCtrlCfg) != D_DD_PCIE_COMM_ERROR){
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Config D_DD_PCIE_COMM_ERROR Check NG.\n"));
			return;
		}

		priv->pcieRc->ctrlDma.ch = E_DD_PCIE_CH0;
		if(Dd_Pcie_Rc_Ctrl_Dma(&priv->pcieRc->ctrlDma) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Dma ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		priv->pcieRc->ctrlDma.ch = E_DD_PCIE_CH1;
		if(Dd_Pcie_Rc_Ctrl_Dma(&priv->pcieRc->ctrlDma) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Dma ch1 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Start_Dma(0,0,0) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Start_Dma ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(Dd_Pcie_Rc_Start_Dma(1,0,0) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Start_Dma ch1 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Stop_Dma(0,0,0) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Stop_Dma ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(Dd_Pcie_Rc_Stop_Dma(1,0,0) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Stop_Dma ch1 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Ctrl_Memory(&priv->pcieRc->ctrlMem) != D_DD_PCIE_COMM_ERROR){
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Memory D_DD_PCIE_COMM_ERROR Check NG.\n"));
			return;
		}

		priv->pcieRc->pcieCtrlMsi.ch = E_DD_PCIE_CH0;
		if(Dd_Pcie_Rc_Ctrl_Msi(&priv->pcieRc->pcieCtrlMsi) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Msi ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		priv->pcieRc->pcieCtrlMsi.ch = E_DD_PCIE_CH1;
		if(Dd_Pcie_Rc_Ctrl_Msi(&priv->pcieRc->pcieCtrlMsi) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Msi ch1 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Ctrl_Aspm(0,1) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Aspm ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Pm_Pw_Turn_Off_Req(0) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Pm_Pw_Turn_Off_Req ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Pm_Pw_L2_Exit(0) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Pm_Pw_L2_Exit ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Transfer_Speed_Change(0,1) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Transfer_Speed_Change ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Get_Current_Link_Speed(0,0) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Get_Current_Link_Speed ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(Dd_Pcie_Rc_Get_Current_Link_Speed(1,0) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Get_Current_Link_Speed ch1 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Get_Aspm_Status(0,0) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Get_Aspm_Status ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(Dd_Pcie_Rc_Get_Aspm_Status(1,0) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Get_Aspm_Status ch1 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Config_Read(0,1,&data) != D_DD_PCIE_INPUT_PARAM_ERROR){
			Ddim_Print(("Dd_Pcie_Rc_Config_Read ch0 D_DD_PCIE_INPUT_PARAM_ERROR Check NG.\n"));
			return;
		}
		if(Dd_Pcie_Rc_Config_Read(0,0,&data) != D_DD_PCIE_COMM_ERROR){
			Ddim_Print(("Dd_Pcie_Rc_Config_Read ch0 D_DD_PCIE_COMM_ERROR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Get_Exs_Reg(0,1,&data) != D_DD_PCIE_INPUT_PARAM_ERROR){
			Ddim_Print(("Dd_Pcie_Rc_Get_Exs_Reg ch0 D_DD_PCIE_INPUT_PARAM_ERROR Check NG.\n"));
			return;
		}
		if(Dd_Pcie_Rc_Get_Exs_Reg(0,0x0288,&data) != D_DD_PCIE_INPUT_PARAM_ERROR){
			Ddim_Print(("Dd_Pcie_Rc_Get_Exs_Reg ch0 D_DD_PCIE_INPUT_PARAM_ERROR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Get_Dbi_Reg(0,1,&data) != D_DD_PCIE_INPUT_PARAM_ERROR){
			Ddim_Print(("Dd_Pcie_Rc_Get_Dbi_Reg ch0 D_DD_PCIE_INPUT_PARAM_ERROR Check NG.\n"));
			return;
		}
		if(Dd_Pcie_Rc_Get_Dbi_Reg(0,0x0B48,&data) != D_DD_PCIE_INPUT_PARAM_ERROR){
			Ddim_Print(("Dd_Pcie_Rc_Get_Dbi_Reg ch0 D_DD_PCIE_INPUT_PARAM_ERROR Check NG.\n"));
			return;
		}
		if(Dd_Pcie_Rc_Get_Dbi_Reg(0,0,&data) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Get_Dbi_Reg ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(Dd_Pcie_Rc_Get_Dbi_Reg(1,0,&data) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Get_Dbi_Reg ch1 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		if(Dd_Pcie_Rc_Set_Wr_Acc_To_Ro_Reg(0,0) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Set_Wr_Acc_To_Ro_Reg ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}
		if(Dd_Pcie_Rc_Set_Wr_Acc_To_Ro_Reg(1,0) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Set_Wr_Acc_To_Ro_Reg ch1 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		Dd_Pcie_Rc_Init(E_DD_PCIE_BIFURCATION_DISABLE);

		if(Dd_Pcie_Rc_Ctrl_Aspm(0,1) != D_DD_PCIE_ACCESS_ERR){
			Ddim_Print(("Dd_Pcie_Rc_Ctrl_Aspm ch0 D_DD_PCIE_ACCESS_ERR Check NG.\n"));
			return;
		}

		Ddim_Print(("Error Check OK.\n"));
	}
	else{
		Ddim_Print(("please check parameter!!\n" ));
	}
}

CtDdPcieMain* ct_dd_pcie_main_new(void) 
{
    CtDdPcieMain *self = k_object_new_with_private(CT_TYPE_DD_PCIE_MAIN, sizeof(CtDdPcieMainPrivate));
    return self;
}
