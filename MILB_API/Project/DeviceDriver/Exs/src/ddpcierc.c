/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 王顺
*@brief : DdPcieRc
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/
/**
 * @file		dd_pcie_rc.c
 * @brief		PCIe RootComplex driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#include "ddpcierc.h"
#include "ddpcierccommon.h"
#include"ddtoptwo.h"
#include"ddtopthree.h"
#include"ddtopfour.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdPcieRc, dd_pcie_rc);

#define DD_PCIE_RC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdPcieRcPrivate, DD_TYPE_PCIE_RC))


struct _DdPcieRcPrivate
{

};

/**
DECLS
*/

/**
IMPL
*/
static void dd_pcie_rc_constructor(DdPcieRc *self)
{
//	DdPcieRcPrivate *priv = DD_PCIE_RC_GET_PRIVATE(self);
}

static void dd_pcie_rc_destructor(DdPcieRc *self)
{
//	DdPcieRcPrivate *priv = DD_PCIE_RC_GET_PRIVATE(self);
}
/**
PUBLIC
*/
/**
 * @brief	Initialize PCIe Root Complex.
 * @param	DdPcieBifurcation	bifurcation
 */
void dd_pcie_rc_init1(DdPcieRc *self, DdPcieBifurcation	bifurcation)
{
	DdTopthree_SET_PERSEL3_PRT0SCK3(0);		// PXRSTX0
	DdTopothree_SET_PERSEL3_PXW0WP12(0);// PXWAKE0
	DdTopothree_SET_PERSEL3_PXC0SCK7(0);	// PXCLKREQ0
	DdToptwo_SET_CLKSTOP2_EXSAX(2);		// AXI bus clock of EXS is supplied

	dd_exs_set_pcie0_bus_clock_stop_ctrl(dd_exs_get(), 0);	// Output PCIE0 BUS CLOCK
	dd_exs_set_ram_pd_ctrl_pcie0(dd_exs_get(), 0);			// Power-down mode is released

//	gddPcieRcBifurcation = bifurcation;
	dd_pcie_rc_common_set_gdd_pcie_rc_bifurcation(dd_pcie_rc_common_get(), bifurcation);
	dd_pcie_rc_common_init(dd_pcie_rc_common_get(), &ioPcie0, &ioPcie0Core, bifurcation);

	if (bifurcation == E_DD_PCIE_BIFURCATION_ENABLE) {
		DdTopothree_SET_PERSEL3_PRT1SOU3(0);		// PXRSTX1
		Dd_Top_Set_PERSEL3_PXW1SOU7(0);		// PXWAKE1
		Dd_Top_Set_PERSEL3_PXC1WP15(0);		// PXCLKREQ1
		Dd_Exs_Set_PCIE1_BUS_CLOCK_Stop_Ctrl(0);	// Output PCIE1 BUS CLOCK
		dd_exs_set_ram_pd_ctrl_pcie1(dd_exs_get(), 0);		// Power-down mode is released
		dd_pcie_rc_common_init(dd_pcie_rc_common_get(), &ioPcie1, &ioPcie1Core, bifurcation);
	}

	gddPcieRcReType = E_DD_PCIE_RE_TYPE_RC;
}

/**
 * @brief	PCIe End.
 */
void dd_pcie_rc_deinit(DdPcieRc *self)
{
	kuchar	ch;

	// Global data reset
	gddPcieRcReType = E_DD_PCIE_RE_TYPE_US;
//	gddPcieRcBifurcation = E_DD_PCIE_BIFURCATION_DISABLE;
	dd_pcie_rc_common_set_gdd_pcie_rc_bifurcation(dd_pcie_rc_common_get(), E_DD_PCIE_BIFURCATION_DISABLE);

	for (ch = 0; ch < C_PCIE_RC_MAX_CH; ch++) {
		gddPcieRcIntDmaCb[ch].wrCb = NULL;
		gddPcieRcIntDmaCb[ch].rdCb = NULL;
		gddPcieRcIntMsiCb[ch] = NULL;
		gddPcieRcIntTrsIcsMsiCb[ch].cfgLinkAutoBwIntCb = NULL;
		gddPcieRcIntTrsIcsMsiCb[ch].cfgBwMgtIntCb = NULL;
		gddPcieRcIntTrsIcsMsiCb[ch].smlhReqRstNotCb = NULL;
		gddPcieRcIntSysErrCb[ch].cfgAerRcErrCb = NULL;
		gddPcieRcIntSysErrCb[ch].cfgSysErrRcCb = NULL;
		gddPcieRcIntEpCb[ch].radmIntxCb = NULL;
		gddPcieRcIntEpCb[ch].radmPmPmeCb = NULL;
		gddPcieRcIntEpCb[ch].radmCorrectableErrCb = NULL;
		gddPcieRcIntEpCb[ch].radmNonfatalErrCb = NULL;
		gddPcieRcIntEpCb[ch].radmFatalErrCb = NULL;
		gddPcieRcIntEpCb[ch].radmMsgLtrCb = NULL;
		gddPcieRcIntEpCb[ch].radmPmToAckCb = NULL;
		gddPcieRcIntEpCb[ch].radmVendorMsgCb = NULL;
		gddPcieRcIntOwnCb[ch].cfgPmeCb = NULL;
		gddPcieRcIntOwnCb[ch].hpCb = NULL;
		gddPcieRcIntOwnCb[ch].rdlhLinkUpCb = NULL;
		gddPcieRcIntOwnCb[ch].wakeCb = NULL;
		gddPcieRcHpDetectCard[ch] = NULL;
		gddPcieRcConfigAdr[ch] = (D_DD_PCIE_0_PIO_ADR >> 16);
	}

	dd_exs_set_ram_pd_ctrl_pcie0(dd_exs_get(), 1);	// PCIE0 power down.
	dd_exs_set_ram_pd_ctrl_pcie1(dd_exs_get(), 1);	// PCIE1 power down.
	DdToptwo_SET_CLKSTOP2_PCISUPPCK(3);	// Sub clock of PCI is stopped.
}

/**
 * @brief	Execute exclusive control for PCIe channel.
 * @param	kint32	tmout
 * @return	kint32	D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/D_DD_PCIE_SEM_TIMEOUT/D_DD_PCIE_SEM_NG
 */
kint32 dd_pcie_rc_open(DdPcieRc *self, kint32 tmout)
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if (tmout < D_DDIM_USER_SEM_WAIT_FEVR) {
		Ddim_Assertion(("PCIE: input param error. tmout = %x\n", tmout));
		return C_PCIE_INPUT_PARAM_ERROR;
	}
#endif

	if (tmout == DdimUserCustom_SEM_WAIT_POL) {
		ercd = ddim_user_custom_pol_sem(NULL, DdimUserCustom_SID_DD_PDM);
	} else {
		ercd = ddim_user_custom_twai_sem(NULL, DdimUserCustom_SID_DD_PDM, (DdimUserCustom_TMO) tmout);
	}

	switch (ercd) {
	case DdimUserCustom_E_OK:
		return D_DDIM_OK;
	case DdimUserCustom_E_TMOUT:
		return D_DD_PCIE_SEM_TIMEOUT;
	default:
		return D_DD_PCIE_SEM_NG;
	}
}

/**
 * @brief	Cancel exclusive control for PCIe channel.
 * @return	kint32	D_DDIM_OK/D_DD_PCIE_SEM_NG
 */
kint32 dd_pcie_rc_close(DdPcieRc *self)
{
	DdimUserCustom_ER ercd;

	ercd = ddim_user_custom_sig_sem(NULL, DdimUserCustom_SID_DD_PDM);	// Exclusive release
	if (DdimUserCustom_E_OK != ercd) {
		return D_DD_PCIE_SEM_NG;
	} else {
		return D_DDIM_OK;
	}
}

/**
 * @brief	Get PCIe link status.
 * @param	DdPcieCh		ch
 * @return	TRUE/FALSE
 */
kboolean dd_pcie_rc_get_link_status(DdPcieRc *self, DdPcieCh ch)
{
	kboolean linkStatus;

	if (ch == E_DD_PCIE_CH0) {
		linkStatus = (kboolean) ioPcie0.LINK_MONITOR.bit.SMLH_LINK_UP;
	} else {	// PCIe ch1
		linkStatus = (kboolean) ioPcie1.LINK_MONITOR.bit.SMLH_LINK_UP;
	}

	return linkStatus;
}

/**
 * @brief	It will be setting up the transfer of config.
 * @param	DdPcieRc const* const self
 * @return	kint32	D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_COMM_ERROR
 */
kint32 dd_pcie_rc_ctrl_config(DdPcieRc const* const self)
{
#ifdef CO_PARAM_CHECK
	if (self == NULL) {
		return C_PCIE_INPUT_PARAM_ERROR;
	}
#endif

	if (dd_pcie_rc_get_link_status(NULL, self->ch) == FALSE) {// Not link up
		return C_PCIE_COMM_ERROR;
	}

	if (self->ch == E_DD_PCIE_CH0) {
		ioPcie0Core.rc.ppl.iv.word = 0x00000000;
		ioPcie0Core.rc.ppl.irc1.word = 0x00000004;// define the type of the region to be CFG0
		ioPcie0Core.rc.ppl.ilba.word = self->baseAdr;// set the Lower Base Address
		gddPcieRcConfigAdr[E_DD_PCIE_CH0] = ioPcie0Core.rc.ppl.ilba.bit.lbr;
		ioPcie0Core.rc.ppl.iuba.word = 0x00000000;// set the Upper Base Address
		ioPcie0Core.rc.ppl.ila.word = self->limitAdr;// set the Limit Address
		ioPcie0Core.rc.ppl.ilta.ob.bit.ltro = 0x00000000;	// set the Lower Target Address
		ioPcie0Core.rc.ppl.iuta.bit.utr = 0x00000000;	// set the Upper Target Address
		ioPcie0Core.rc.ppl.irc2.word = 0x80000000;// enable the region in routing id match mode
	} else {	// PCIe ch1
		ioPcie0Core.rc.ppl.iv.word = 0x00000000;
		ioPcie1Core.rc.ppl.irc1.word = 0x00000004;// define the type of the region to be CFG0
		ioPcie1Core.rc.ppl.ilba.word = self->baseAdr;// set the Lower Base Address
		gddPcieRcConfigAdr[E_DD_PCIE_CH1] = ioPcie1Core.rc.ppl.ilba.bit.lbr;
		ioPcie1Core.rc.ppl.iuba.word = 0x00000000;// set the Upper Base Address
		ioPcie1Core.rc.ppl.ila.word = self->limitAdr;// set the Limit Address
		ioPcie1Core.rc.ppl.ilta.ob.bit.ltro = 0x00000000;	// set the Lower Target Address
		ioPcie1Core.rc.ppl.iuta.bit.utr = 0x00000000;	// set the Upper Target Address
		ioPcie1Core.rc.ppl.irc2.word = 0x80000000;// enable the region in routing id match mode
	}

	return D_DDIM_OK;
}

/**
 * @brief	It will be setting up the dma transfer.
 * @param	DdPcieCtrlDma const* const	pcieCtrlDma
 * @return	kint32	D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_ctrl_dma(DdPcieRc *self, DdPcieCtrlDma const* const pcieCtrlDma)
{
#ifdef CO_PARAM_CHECK
	if (pcieCtrlDma == NULL) {
		return C_PCIE_INPUT_PARAM_ERROR;
	}
#endif

	if (pcieCtrlDma->ch == E_DD_PCIE_CH0) {
		if (DdExs_GET_RAM_PD_CTRL_PCIE0() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		ioPcie0Core.rc.ppl.dwic.bit.wdic = 0xFF;	// Interrupt clear
		ioPcie0Core.rc.ppl.dwic.bit.waic = 0xFF;	// Interrupt clear
		ioPcie0Core.rc.ppl.dric.bit.rdic = 0xFF;	// Interrupt clear
		ioPcie0Core.rc.ppl.dric.bit.raic = 0xFF;	// Interrupt clear

		if (pcieCtrlDma->direction == E_DD_PCIE_DMA_DIR_STOD) {
			ioPcie0Core.rc.ppl.dwee.bit.dwe = 1;	// Write Engine Enable
			ioPcie0Core.rc.ppl.dree.bit.dre = 0;	// Read Engine Disable
			gddPcieRcIntDmaCb[pcieCtrlDma->ch].wrCb = pcieCtrlDma->intDmaCb; // interrupt dma callback function
		} else {
			ioPcie0Core.rc.ppl.dwee.bit.dwe = 0;	// Write Engine Disable
			ioPcie0Core.rc.ppl.dree.bit.dre = 1;	// Read Engine Enable
			gddPcieRcIntDmaCb[pcieCtrlDma->ch].rdCb = pcieCtrlDma->intDmaCb; // interrupt dma callback function
		}

		ioPcie0Core.rc.ppl.dvs.bit.cn = pcieCtrlDma->dmaCh;// Channel Number
		ioPcie0Core.rc.ppl.dvs.bit.cd = ~pcieCtrlDma->direction;// Direction

		if (pcieCtrlDma->mode == E_DD_PCIE_DMA_DEMAND_MODE) {	// dmac mode control
			ioPcie0Core.rc.ppl.dcc1.word = 0x00000008;// Local Interrupt Enable
			ioPcie0Core.rc.ppl.dts.bit.dts = pcieCtrlDma->dmndTransSize;// Transfer Size
			ioPcie0Core.rc.ppl.dsl.bit.sarl = pcieCtrlDma->dmndSrcAddrL;	// Source Address Low
			ioPcie0Core.rc.ppl.dsh.bit.sarh = pcieCtrlDma->dmndSrcAddrH;	// Source Address Hight
			ioPcie0Core.rc.ppl.ddl.bit.darl = pcieCtrlDma->dmndDstAddrL;	// Destination Address Low
			ioPcie0Core.rc.ppl.ddh.bit.darh = pcieCtrlDma->dmndDstAddrH;	// Destination Address Hight
		} else {	// Linked List mode
			if (pcieCtrlDma->direction == E_DD_PCIE_DMA_DIR_STOD) {
				ioPcie0Core.rc.ppl.dwllee.bit.wclllaie = 1;// Write Channel LL Local Abort Interrupt Enable.
				ioPcie0Core.rc.ppl.dwllee.bit.wcllraie = 0;// Read Channel LL Local Abort Interrupt Disable.
			} else {
				ioPcie0Core.rc.ppl.dwllee.bit.wclllaie = 0;// Write Channel LL Local Abort Interrupt Disable.
				ioPcie0Core.rc.ppl.dwllee.bit.wcllraie = 1;// Read Channel LL Local Abort Interrupt Enable.
			}

			// DMA Channel Control 1 register
			// Linked List Enable (LLE) = 1
			// Consumer Cycle State (CCS) = 1
			// Traffic Digest TLP Header Bit(TD) = 1
			ioPcie0Core.rc.ppl.dcc1.word = 0x04000300;
			ioPcie0Core.rc.ppl.dll.bit.ll = pcieCtrlDma->llAddr;// Linked List Pointer Low
		}

		ioPcie0Core.rc.ppl.dwim.bit.wdim = 0;	// Write Done Interrupt Mask Off
		ioPcie0Core.rc.ppl.dwim.bit.waim = 0;	// Write Abort Interrupt Mask Off
		ioPcie0Core.rc.ppl.drim.bit.rdim = 0;	// Read Done Interrupt Mask Off
		ioPcie0Core.rc.ppl.drim.bit.raim = 0;	// Read Abort Interrupt Mask Off
	} else {	// PCIe ch1
		if (DdExs_GET_RAM_PD_CTRL_PCIE1() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		ioPcie1Core.rc.ppl.dwic.bit.wdic = 0xFF;	// Interrupt clear
		ioPcie1Core.rc.ppl.dwic.bit.waic = 0xFF;	// Interrupt clear
		ioPcie1Core.rc.ppl.dric.bit.rdic = 0xFF;	// Interrupt clear
		ioPcie1Core.rc.ppl.dric.bit.raic = 0xFF;	// Interrupt clear

		if (pcieCtrlDma->direction == E_DD_PCIE_DMA_DIR_STOD) {
			ioPcie1Core.rc.ppl.dwee.bit.dwe = 1;	// Write Engine Enable
			ioPcie1Core.rc.ppl.dree.bit.dre = 0;	// Read Engine Disable
			gddPcieRcIntDmaCb[pcieCtrlDma->ch].wrCb = pcieCtrlDma->intDmaCb; // interrupt dma callback function
		} else {
			ioPcie1Core.rc.ppl.dwee.bit.dwe = 0;	// Write Engine Disable
			ioPcie1Core.rc.ppl.dree.bit.dre = 1;	// Read Engine Enable
			gddPcieRcIntDmaCb[pcieCtrlDma->ch].rdCb = pcieCtrlDma->intDmaCb; // interrupt dma callback function
		}

		ioPcie1Core.rc.ppl.dvs.bit.cn = pcieCtrlDma->dmaCh;// Channel Number
		ioPcie1Core.rc.ppl.dvs.bit.cd = ~pcieCtrlDma->direction;// Direction

		if (pcieCtrlDma->mode == E_DD_PCIE_DMA_DEMAND_MODE) {	// dmac mode control
			ioPcie1Core.rc.ppl.dcc1.word = 0x00000008;// Local Interrupt Enable
			ioPcie1Core.rc.ppl.dts.bit.dts = pcieCtrlDma->dmndTransSize;// Transfer Size
			ioPcie1Core.rc.ppl.dsl.bit.sarl = pcieCtrlDma->dmndSrcAddrL;	// Source Address Low
			ioPcie1Core.rc.ppl.dsh.bit.sarh = pcieCtrlDma->dmndSrcAddrH;	// Source Address Hight
			ioPcie1Core.rc.ppl.ddl.bit.darl = pcieCtrlDma->dmndDstAddrL;	// Destination Address Low
			ioPcie1Core.rc.ppl.ddh.bit.darh = pcieCtrlDma->dmndDstAddrH;	// Destination Address Hight
		} else {
			if (pcieCtrlDma->direction == E_DD_PCIE_DMA_DIR_STOD) {
				ioPcie1Core.rc.ppl.dwllee.bit.wclllaie = 1;// Write Channel LL Local Abort Interrupt Enable.
				ioPcie1Core.rc.ppl.dwllee.bit.wcllraie = 0;// Read Channel LL Local Abort Interrupt Disable.
			} else {
				ioPcie1Core.rc.ppl.dwllee.bit.wclllaie = 0;// Write Channel LL Local Abort Interrupt Disable.
				ioPcie1Core.rc.ppl.dwllee.bit.wcllraie = 1;// Read Channel LL Local Abort Interrupt Enable.
			}

			// DMA Channel Control 1 register
			// Linked List Enable (LLE) = 1
			// Consumer Cycle State (CCS) = 1
			// Traffic Digest TLP Header Bit(TD) = 1
			ioPcie1Core.rc.ppl.dcc1.word = 0x04000300;
			ioPcie1Core.rc.ppl.dll.bit.ll = pcieCtrlDma->llAddr;// Linked List Pointer Low
		}

		ioPcie1Core.rc.ppl.dwim.bit.wdim = 0;	// Write Done Interrupt Mask Off
		ioPcie1Core.rc.ppl.dwim.bit.waim = 0;	// Write Abort Interrupt Mask Off
		ioPcie1Core.rc.ppl.drim.bit.rdim = 0;	// Read Done Interrupt Mask Off
		ioPcie1Core.rc.ppl.drim.bit.raim = 0;	// Read Abort Interrupt Mask Off
	}

	return D_DDIM_OK;
}

/**
 * @brief	Start DMA.
 * @param	DdPcieCh		ch
 * @param	DdPcieDmaCh	dmaCh
 * @param	DdPcieDmaDir	dir
 * @return	kint32	D_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_start_dma(DdPcieRc *self, DdPcieCh ch, DdPcieDmaCh dmaCh, DdPcieDmaDir dir)
{
	if (ch == E_DD_PCIE_CH0) {
		if (DdExs_GET_RAM_PD_CTRL_PCIE0() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		if (dir == E_DD_PCIE_DMA_DIR_STOD) {	// source to destination (write)
			ioPcie0Core.rc.ppl.dwd.bit.wdn = dmaCh;
			ioPcie0Core.rc.ppl.dwd.bit.ws = 0;
		} else {								// destination to source (read)
			ioPcie0Core.rc.ppl.drd.bit.rdn = dmaCh;
			ioPcie0Core.rc.ppl.drd.bit.rs = 0;
		}
	} else {	// PCIe ch1
		if (DdExs_GET_RAM_PD_CTRL_PCIE1() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		if (dir == E_DD_PCIE_DMA_DIR_STOD) {	// source to destination (write)
			ioPcie1Core.rc.ppl.dwd.bit.wdn = dmaCh;
			ioPcie1Core.rc.ppl.dwd.bit.ws = 0;
		} else {								// destination to source (read)
			ioPcie1Core.rc.ppl.drd.bit.rdn = dmaCh;
			ioPcie1Core.rc.ppl.drd.bit.rs = 0;
		}
	}

	return D_DDIM_OK;
}

/**
 * @brief	Stop DMA.
 * @param	DdPcieCh		ch
 * @param	DdPcieDmaCh	dmaCh
 * @param	DdPcieDmaDir	dir
 * @return	kint32	D_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_stop_dma(DdPcieRc *self, DdPcieCh ch, DdPcieDmaCh dmaCh, DdPcieDmaDir dir)
{
	if (ch == E_DD_PCIE_CH0) {
		if (DdExs_GET_RAM_PD_CTRL_PCIE0() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		if (dir == E_DD_PCIE_DMA_DIR_STOD) {	// source to destination (write)
			ioPcie0Core.rc.ppl.dwd.bit.wdn = dmaCh;
			ioPcie0Core.rc.ppl.dwd.bit.ws = 1;
			ioPcie0Core.rc.ppl.dwic.bit.wdic = 0xFF;	// Interrupt clear
			ioPcie0Core.rc.ppl.dwic.bit.waic = 0xFF;	// Interrupt clear
		} else {								// destination to source (read)
			ioPcie0Core.rc.ppl.drd.bit.rdn = dmaCh;
			ioPcie0Core.rc.ppl.drd.bit.rs = 1;
			ioPcie0Core.rc.ppl.dric.bit.rdic = 0xFF;	// Interrupt clear
			ioPcie0Core.rc.ppl.dric.bit.raic = 0xFF;	// Interrupt clear
		}
	} else {	// PCIe ch1
		if (DdExs_GET_RAM_PD_CTRL_PCIE1() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		if (dir == E_DD_PCIE_DMA_DIR_STOD) {	// source to destination (write)
			ioPcie1Core.rc.ppl.dwd.bit.wdn = dmaCh;
			ioPcie1Core.rc.ppl.dwd.bit.ws = 1;
			ioPcie1Core.rc.ppl.dwic.bit.wdic = 0xFF;	// Interrupt clear
			ioPcie1Core.rc.ppl.dwic.bit.waic = 0xFF;	// Interrupt clear
		} else {								// destination to source (read)
			ioPcie1Core.rc.ppl.drd.bit.rdn = dmaCh;
			ioPcie1Core.rc.ppl.drd.bit.rs = 1;
			ioPcie1Core.rc.ppl.dric.bit.rdic = 0xFF;	// Interrupt clear
			ioPcie1Core.rc.ppl.dric.bit.raic = 0xFF;	// Interrupt clear
		}
	}

	return D_DDIM_OK;
}

/**
 * @brief	It will be setting up the transfer of memory. CPU transfer.
 * @param	DdPcieCtrlMem const* const pcieCtrlMem
 * @return	kint32 D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_COMM_ERROR
 */
kint32 dd_pcie_rc_ctrl_memory(DdPcieRc *self, DdPcieCtrlMem const* const pcieCtrlMem)
{
#ifdef CO_PARAM_CHECK
	if (pcieCtrlMem == NULL) {
		return C_PCIE_INPUT_PARAM_ERROR;
	}
#endif

	if (dd_pcie_rc_get_link_status(NULL, pcieCtrlMem->ch) == FALSE) {// Not link up
		return C_PCIE_COMM_ERROR;
	}

	if (pcieCtrlMem->ch == E_DD_PCIE_CH0) {
		ioPcie0Core.rc.ppl.iv.word = 0x00000001;
		ioPcie0Core.rc.ppl.ilba.word = pcieCtrlMem->baseAdr;// set the Lower Base Address
		ioPcie0Core.rc.ppl.iuba.word = 0x00000000;// set the Upper Base Address
		ioPcie0Core.rc.ppl.ila.word = pcieCtrlMem->limitAdr;// set the Limit Address
		ioPcie0Core.rc.ppl.ilta.ob.bit.ltro = pcieCtrlMem->lowTargetAdr;// set the Lower Target Address
		ioPcie0Core.rc.ppl.iuta.bit.utr = pcieCtrlMem->uppTargetAdr;// set the Upper Target Address
		ioPcie0Core.rc.ppl.irc1.word = 0x00000000;// define the type of the region to be MEM
		ioPcie0Core.rc.ppl.irc2.word = 0x80000000;// enable the region in address match mode
	} else {	// PCIe ch1
		ioPcie1Core.rc.ppl.iv.word = 0x00000001;
		ioPcie1Core.rc.ppl.ilba.word = pcieCtrlMem->baseAdr;// set the Lower Base Address
		ioPcie1Core.rc.ppl.iuba.word = 0x00000000;// set the Upper Base Address
		ioPcie1Core.rc.ppl.ila.word = pcieCtrlMem->limitAdr;// set the Limit Address
		ioPcie1Core.rc.ppl.ilta.ob.bit.ltro = pcieCtrlMem->lowTargetAdr;// set the Lower Target Address
		ioPcie1Core.rc.ppl.iuta.bit.utr = pcieCtrlMem->uppTargetAdr;// set the Upper Target Address
		ioPcie1Core.rc.ppl.irc1.word = 0x00000000;// define the type of the region to be MEM
		ioPcie1Core.rc.ppl.irc2.word = 0x80000000;// enable the region in address match mode
	}

	return D_DDIM_OK;
}

/**
 * @brief	Interrupt handler for PCIe ch0 own.
 */
void dd_pcie_rc_ch0_int_own_handler(DdPcieRc *self)
{
	VpCallbackPcieFunc callback;

	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] CH0 INT_OWN Occurred.\n"));

	// cfg_pme_int/cfg_pme_msi
	if (ioPcie0Core.rc.pciecr.rsr.bit.pmes == 1) {
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_pme_int/cfg_pme_msi.\n"));
		ioPcie0Core.rc.pciecr.rsr.bit.pmes = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH0].cfgPmeCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie0Core.rc.pciecr.scsr.bit.abp == 1) {
		// hp_mpe/hp_int/hp_msi
		// PCIE_CAP_ATTENTION_BUTTON_PRESSED
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] hp_mpe/hp_int/hp_msi: PCIE_CAP_ATTENTION_BUTTON_PRESSED.\n"));
		dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH0, TRUE);
		ioPcie0Core.rc.pciecr.scr.bit.abp = 0;
		dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH0, FALSE);
		ioPcie0Core.rc.pciecr.scsr.bit.abp = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH0].hpCb;
		if (callback != NULL) {
			(*callback)(DdPcieRc_PCIE_HOT_PLUG_ST_ABP);
		}
	} else if (ioPcie0Core.rc.pciecr.scsr.bit.pfd == 1) {
		// PCIE_CAP_POWER_FAULT_DETECTED
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] hp_mpe/hp_int/hp_msi: PCIE_CAP_POWER_FAULT_DETECTED.\n"));
		dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH0, TRUE);
		ioPcie0Core.rc.pciecr.scr.bit.pcp = 0;
		dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH0, FALSE);
		ioPcie0Core.rc.pciecr.scsr.bit.pfd = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH0].hpCb;
		if (callback != NULL) {
			(*callback)(DdPcieRc_PCIE_HOT_PLUG_ST_PFD);
		}
	} else if (ioPcie0Core.rc.pciecr.scsr.bit.mrlsc == 1) {
		// PCIE_CAP_MRL_SENSOR_CHANGED
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] hp_mpe/hp_int/hp_msi: PCIE_CAP_MRL_SENSOR_CHANGED.\n"));
		ioPcie0Core.rc.pciecr.scsr.bit.mrlsc = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH0].hpCb;
		if (callback != NULL) {
			(*callback)(DdPcieRc_PCIE_HOT_PLUG_ST_MRLSC);
		}
	} else if (ioPcie0Core.rc.pciecr.scsr.bit.pdc == 1) {
		// PCIE_CAP_PRESENCE_DETECTED_CHANGED
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] hp_mpe/hp_int/hp_msi: PCIE_CAP_PRESENCE_DETECTED_CHANGED.\n"));
		ioPcie0Core.rc.pciecr.scsr.bit.pdc = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH0].hpCb;
		if (callback != NULL) {
			(*callback)(DdPcieRc_PCIE_HOT_PLUG_ST_PDC);
		}
	} else if (ioPcie0Core.rc.pciecr.scsr.bit.cc == 1) {
		// PCIE_CAP_CMD_CPLD
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] hp_mpe/hp_int/hp_msi: PCIE_CAP_CMD_CPLD.\n"));
		ioPcie0.emControl.bit.cmdCpledInt = 0;
		ioPcie0Core.rc.pciecr.scsr.bit.cc = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH0].hpCb;
		if (callback != NULL) {
			(*callback)(DdPcieRc_PCIE_HOT_PLUG_ST_CC);
		}
	} else if (ioPcie0Core.rc.pciecr.scsr.bit.dllsc == 1) {
		// PCIE_CAP_DLL_STATE_CHANGED
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] hp_mpe/hp_int/hp_msi: PCIE_CAP_DLL_STATE_CHANGED.\n"));
		ioPcie0Core.rc.pciecr.scsr.bit.dllsc = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH0].hpCb;
		if (callback != NULL) {
			(*callback)(DdPcieRc_PCIE_HOT_PLUG_ST_DLLSC);
		}
	} else if (ioPcie0.intControl2.bit.rdlhLinkUpStt == 1) {
		// rdlh_link_up
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] rdlh_link_up.\n"));
		ioPcie0.intControl2.bit.rdlhLinkUpStt = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH0].rdlhLinkUpCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie0.intControl2.bit.wakeStatus == 1) {
		// wake
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] wake.\n"));
		ioPcie0.intControl2.bit.wakeStatus = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH0].wakeCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	}
}

/**
 * @brief	Interrupt handler for PCIe ch0 endpoint.
 */
void dd_pcie_rc_ch0_int_ep_handler(DdPcieRc *self)
{
	kuint32 intStat;
	VpCallbackPcieFunc callback;

	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] CH0 INT_EP Occurred.\n"));

	// radm_inta/radm_intb/radm_intc/radm_intd/
	if (ioPcie0.intControl1.word & 0xF0000000) {
		intStat = ioPcie0.intControl1.word;
		ioPcie0.intControl1.word &= intStat;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] INTX_Status \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie0.intControl1.word, intStat));

		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmIntxCb;
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] INT_X callback\n"));
			(*callback)(intStat >> 28);// argument: 1(INTA), 2(INTB), 4(INTC), 8(INTD)
		}
	} else if (ioPcie0.intControl3.bit.radmPmPmeStt == 1) {
		// radm_pm_pme
		ioPcie0.intControl3.bit.radmPmPmeStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_pm_pme\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmPmPmeCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie0.intControl3.bit.radmCorErrStt == 1) {
		// radm_correctable_err
		ioPcie0.intControl3.bit.radmCorErrStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_correctable_err\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmCorrectableErrCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie0.intControl3.bit.radmNfErrStt == 1) {
		// radm_nonfatal_err
		ioPcie0.intControl3.bit.radmNfErrStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_nonfatal_err\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmNonfatalErrCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie0.intControl3.bit.radmFErrStt == 1) {
		// radm_fatal_err
		ioPcie0.intControl3.bit.radmFErrStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_fatal_err\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmFatalErrCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie0.intControl3.bit.radmPm2ackStt == 1) {
		// radm_pm_to_ack
		ioPcie0.intControl3.bit.radmPm2ackStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_pm_to_ack\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmPmToAckCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie0.intControl2.bit.vendorMsgStt == 1) {
		// radm_vendor_msg
		ioPcie0.intControl2.bit.vendorMsgStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_vendor_msg\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmVendorMsgCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie0.intControl3.bit.radmMsgLtrStt) {
		// radm_msg_ltr
		// LTR Interrupt Status
		ioPcie0.intControl3.bit.radmMsgLtrStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_msg_ltr\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmMsgLtrCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	}
}

/**
 * @brief	ASPM Control.
 * @param	DdPcieCh	ch
 * @param	DdPcieAspmControl aspmControl
 * @return	kint32	D_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_ctrl_aspm(DdPcieRc *self, DdPcieCh ch, DdPcieAspmControl aspmControl)
{
	DdPcieStLtssm ltssmStatus;

	if (dd_pcie_rc_get_pmst_status(NULL, ch) != E_DD_PCIE_PMST_D0) {
		return C_PCIE_ACCESS_ERR;
	}

	ltssmStatus = dd_pcie_rc_get_st_ltssm_status(NULL, ch);
	if (ltssmStatus < E_DD_PCIE_S_L0 || ltssmStatus > E_DD_PCIE_S_L1_IDLE) {
		return C_PCIE_ACCESS_ERR;
	}

	if (ch == E_DD_PCIE_CH0) {
		ioPcie0Core.rc.pciecr.lcsr.bit.aspmc = aspmControl;
	} else {	// PCIe ch1
		ioPcie1Core.rc.pciecr.lcsr.bit.aspmc = aspmControl;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Power Turn Off Request. (L2 Entry)
 * @param	DdPcieCh	ch
 * @return	kint32	D_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_pm_pw_turn_off_req(DdPcieRc *self, DdPcieCh ch)
{
	if (dd_pcie_rc_get_st_ltssm_status(NULL, ch) != E_DD_PCIE_S_L0) {
		return C_PCIE_ACCESS_ERR;
	}

	if (ch == E_DD_PCIE_CH0) {
		ioPcie0.pmUnlockReq.bit.pmXmtTurnoff = 0;	// deassert
		ioPcie0.pmUnlockReq.bit.pmXmtTurnoff = 1;	// assert
	} else {	// PCIe ch1
		ioPcie1.pmUnlockReq.bit.pmXmtTurnoff = 0;	// deassert
		ioPcie1.pmUnlockReq.bit.pmXmtTurnoff = 1;	// assert
	}

	return D_DDIM_OK;
}

/**
 * @brief	Power L2 Exit. (L0 Entry)
 * @param	DdPcieCh	ch
 * @return	kint32	D_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_pm_pw_l2_exit(DdPcieRc *self, DdPcieCh ch)
{
	kuchar function;

	if (dd_pcie_rc_get_st_ltssm_status(NULL, ch) != E_DD_PCIE_S_L2_IDLE) {
		return C_PCIE_ACCESS_ERR;
	}

	if (ch == E_DD_PCIE_CH0) {
		dd_topfour_get_gpio_function(NULL, DdTop_GPIO_PY0, &function);
		dd_topfour_set_gpio_function(NULL, DdTop_GPIO_PY0, DdToptwo_GPIO_FUNC_HWMODE);
		ioPcie0Core.rc.pmcr.pmcs.bit.ps = 0;	// D0
		ioPcie0.resetControl1.bit.perstNOReg = 0;	// PERST# Assert
		ioPcie0Core.rc.pciecr.scsr.bit.pcc = 0;	// Power ON
		ioPcie0.resetControl1.bit.perstNOReg = 1;	// PERST# Deassert
		dd_topfour_set_gpio_function(NULL, DdTop_GPIO_PY0, function);
	} else {	// PCIe ch1
		dd_topfour_get_gpio_function(NULL, DdTop_GPIO_PY1, &function);
		dd_topfour_set_gpio_function(NULL, DdTop_GPIO_PY1, DdToptwo_GPIO_FUNC_HWMODE);
		ioPcie1Core.rc.pmcr.pmcs.bit.ps = 0;	// D0
		ioPcie1.resetControl1.bit.perstNOReg = 0;	// PERST# Assert
		ioPcie1Core.rc.pciecr.scsr.bit.pcc = 0;	// Power ON
		ioPcie1.resetControl1.bit.perstNOReg = 1;	// PERST# Deassert
		dd_topfour_set_gpio_function(NULL, DdTop_GPIO_PY1, function);
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get PCIe Power status.
 * @param	DdPcieCh	ch
 * @return	DdPciePmst
 */
DdPciePmst dd_pcie_rc_get_pmst_status(DdPcieRc *self, DdPcieCh ch)
{
	if (ch == E_DD_PCIE_CH0) {
		return (DdPciePmst) ioPcie0.pmMonitor1.bit.pmDstate;
	} else {	// PCIe ch1
		return (DdPciePmst) ioPcie1.pmMonitor1.bit.pmDstate;
	}
}

/**
 * @brief	Get PCIe LTSSM status.
 * @param	DdPcieCh	ch
 * @return	DdPcieStLtssm
 */
DdPcieStLtssm dd_pcie_rc_get_st_ltssm_status(DdPcieRc *self, DdPcieCh ch)
{
	if (ch == E_DD_PCIE_CH0) {
		return (DdPcieStLtssm) ioPcie0.pmMonitor1.bit.smlhLtssmState;
	} else {	// PCIe ch1
		return (DdPcieStLtssm) ioPcie1.pmMonitor1.bit.smlhLtssmState;
	}
}

/**
 * @brief	Transfer speed change.
 * @param	DdPcieCh			ch
 * @param	DdPcieLinkSpeed	linkSpeed
 * @return	kint32	D_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_transfer_speed_change(DdPcieRc *self, DdPcieCh ch, DdPcieLinkSpeed linkSpeed)
{
	DdPcieStLtssm ltssmStatus;

	ltssmStatus = dd_pcie_rc_get_st_ltssm_status(NULL, ch);
	if (ltssmStatus < E_DD_PCIE_S_L0 || ltssmStatus > E_DD_PCIE_S_L1_IDLE) {
		return C_PCIE_ACCESS_ERR;
	}

	if (ch == E_DD_PCIE_CH0) {
		if (linkSpeed == E_DD_PCIE_LINK_SPEED_GEN1) {
			ioPcie0Core.rc.pciecr.lc2sr.bit.tls = 0x1;	// 2.5GT/s
		} else {
			ioPcie0Core.rc.pciecr.lc2sr.bit.tls = 0x2;	// 5.0GT/s
		}

		ioPcie0Core.rc.ppl.gen2c.bit.dsc = 0x0;	// Deassert
		ioPcie0Core.rc.ppl.gen2c.bit.dsc = 0x1;	// Assert

		if (ioPcie0Core.rc.pciecr.lcsr.bit.lbmie == 1) {
			ioPcie0Core.rc.pciecr.lcsr.bit.rl = 1;
		}
	} else {	// ch1
		if (linkSpeed == E_DD_PCIE_LINK_SPEED_GEN1) {
			ioPcie1Core.rc.pciecr.lc2sr.bit.tls = 0x1;	// 2.5GT/s
		} else {
			ioPcie1Core.rc.pciecr.lc2sr.bit.tls = 0x2;	// 5.0GT/s
		}

		ioPcie1Core.rc.ppl.gen2c.bit.dsc = 0x0;	// Deassert
		ioPcie1Core.rc.ppl.gen2c.bit.dsc = 0x1;	// Assert

		if (ioPcie1Core.rc.pciecr.lcsr.bit.lbmie == 1) {
			ioPcie1Core.rc.pciecr.lcsr.bit.rl = 1;
		}
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get current link speed.
 * @param	DdPcieCh			ch
 * @param	DdPcieLinkSpeed	currentLinkSpeed
 * @return	kint32	D_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_get_current_link_speed(DdPcieRc *self, DdPcieCh ch, DdPcieLinkSpeed* currentLinkSpeed)
{
	if (ch == E_DD_PCIE_CH0) {
		if (DdExs_GET_RAM_PD_CTRL_PCIE0() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		*currentLinkSpeed = (DdPcieLinkSpeed) ioPcie0Core.rc.pciecr.lcsr.bit.cls;
	} else {	// PCIe ch1
		if (DdExs_GET_RAM_PD_CTRL_PCIE1() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		*currentLinkSpeed = (DdPcieLinkSpeed)ioPcie1Core.rc.pciecr.lcsr.bit.cls;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get ASPM Status.
 * @param	DdPcieCh			ch
 * @param	DdPcieAspmControl	aspmStatus
 * @return	kint32	D_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_get_aspm_status(DdPcieRc *self, DdPcieCh ch, DdPcieAspmControl* aspmStatus)
{
	if (ch == E_DD_PCIE_CH0) {
		if (DdExs_GET_RAM_PD_CTRL_PCIE0() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		*aspmStatus = (DdPcieAspmControl) ioPcie0Core.rc.pciecr.lcsr.bit.aspmc;
	} else {	// PCIe ch1
		if (DdExs_GET_RAM_PD_CTRL_PCIE1() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		*aspmStatus = (DdPcieAspmControl) ioPcie1Core.rc.pciecr.lcsr.bit.aspmc;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Read the config read register.
 * @param	DdPcieCh	ch
 * @param	kuint16			offset
 * @param	kuint32*			data
 * @return	kint32	D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_COMM_ERROR
 */
kint32	dd_pcie_rc_config_read(DdPcieRc *self, DdPcieCh ch, kuint16 offset, kuint32* data)
{
	kint32 ret = D_DDIM_OK;
	kuint32* addr;

	ret = dd_pcie_rc_common_chk_config_rw_par(dd_pcie_rc_common_get(), ch, offset);
	if (ret != D_DDIM_OK) {
		return ret;
	}

	if (ch == E_DD_PCIE_CH0) {
		addr = (kuint32*) ((gddPcieRcConfigAdr[E_DD_PCIE_CH0] << 16) + offset);
	} else {
		addr = (kuint32*) ((gddPcieRcConfigAdr[E_DD_PCIE_CH1] << 16) + offset);
	}

//	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] addr  = 0x%08X\n", addr));
//	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] *addr = 0x%08X\n", *addr));

	*data = *addr;
	return ret;
}

/**
 * @brief	Read the config write register.
 * @param	DdPcieCh	ch
 * @param	kuint16		offset
 * @param	kuint32		data
 * @return	kint32	D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_COMM_ERROR
 */
kint32	dd_pcie_rc_config_write(DdPcieRc *self, DdPcieCh ch, kuint16 offset, kuint32 data)
{
	kint32 ret = D_DDIM_OK;
	kuint32* addr;

	ret = dd_pcie_rc_common_chk_config_rw_par(dd_pcie_rc_common_get(), ch, offset);
	if (ret != D_DDIM_OK) {
		return ret;
	}

	if (ch == E_DD_PCIE_CH0) {
		addr = (kuint32*) ((gddPcieRcConfigAdr[E_DD_PCIE_CH0] << 16) + offset);
	} else {
		addr = (kuint32*) ((gddPcieRcConfigAdr[E_DD_PCIE_CH1] << 16) + offset);
	}

//	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] addr  = 0x%08X\n", addr));
//	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] *addr = 0x%08X\n", *addr));

	*addr = data;
	return ret;
}

/**
 * @brief	It will be setting up Detect Card.
 * @param	DdPcieCh		ch
 * @param	VpCallbackPcieFunc	callback
 * @return	kint32				D_DDIM_OK
 */
kint32 dd_pcie_rc_ctrl_detect_card(DdPcieRc *self, DdPcieCh ch, VpCallbackPcieFunc callback)
{
	if (ch == E_DD_PCIE_CH0) {
		DdTopthree_SET_PERSEL3_PRT0SCK3(0);	// CHIPTOP PERSEL3. Set PXRSTX0.
		dd_exs_set_pcie0_cd_debounce_soft_reset(dd_exs_get(), 0);	// Reset
		dd_exs_set_deben_pcie0_en(dd_exs_get(), 1);			// PCIe0 Debounce ON
		dd_exs_set_deben_pcie0detim(dd_exs_get(), 0);	// PCIe0 Debounce time
		dd_exs_set_pcie0_cd_debounce_soft_reset(dd_exs_get(), 1);// Reset Cancel
		dd_exs_branch_clear_intstat_pcie0_ris(dd_exs_branch_get());
		dd_exs_branch_clear_intstat_pcie0_fis(dd_exs_branch_get());
		dd_exs_set_intmsk_pcie0_rim(dd_exs_get(), 0); // PCIe0 Detect INT Mask(Rising Edge) Off
		dd_exs_set_intmsk_pcie0_fim(dd_exs_get(), 0); // PCIe0 Detect INT Mask(Falling Edge) Off
		gddPcieRcHpDetectCard[E_DD_PCIE_CH0] = callback;
	} else {	// PCIe ch1
		DdTopothree_SET_PERSEL3_PRT1SOU3(0); //CHIPTOP RERSEL3. Set PXRSTX1.
		dd_exs_set_pcie1_cd_debounce_soft_reset(dd_exs_get(), 0); // Reset
		dd_exs_set_deben_pcie1_en(dd_exs_get(), 1); // PCIe0 Debounce ON
		dd_exs_set_deben_pcie1detim(dd_exs_get(), 0);	 // PCIe0 Debounce time
		dd_exs_set_pcie1_cd_debounce_soft_reset(dd_exs_get(), 1);	// Reset Cancel
		dd_exs_branch_clear_intstat_pcie1_ris(dd_exs_branch_get());
		dd_exs_branch_clear_intstat_pcie1_fis(dd_exs_branch_get());
		dd_exs_set_intmsk_pcie1_rim(dd_exs_get(), 0);	// PCIe0 Detect INT Mask(Rising Edge) Off
		dd_exs_set_intmsk_pcie1_fim(dd_exs_get(), 0);	// PCIe0 Detect INT Mask(Falling Edge) Off
		gddPcieRcHpDetectCard[E_DD_PCIE_CH1] = callback;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Set max payload size.
 * @param	DdPcieMps	mps
 * @return	kint32			D_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_set_mps(DdPcieRc *self, DdPcieCh ch, DdPcieMps mps)
{
	if (ch == E_DD_PCIE_CH0) {
		if (DdExs_GET_RAM_PD_CTRL_PCIE0() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		ioPcie0Core.rc.pciecr.dcsr.bit.mps = mps;
	} else {
		if (DdExs_GET_RAM_PD_CTRL_PCIE1() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		ioPcie1Core.rc.pciecr.dcsr.bit.mps = mps;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get max payload size.
 * @param	DdPcieMps*	mps
 * @return	kint32			D_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_get_mps(DdPcieRc *self, DdPcieCh ch, DdPcieMps* mps)
{
	if (ch == E_DD_PCIE_CH0) {
		if (DdExs_GET_RAM_PD_CTRL_PCIE0() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		*mps = ioPcie0Core.rc.pciecr.dcsr.bit.mps;
	} else {
		if (DdExs_GET_RAM_PD_CTRL_PCIE1() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		*mps = ioPcie1Core.rc.pciecr.dcsr.bit.mps;
	}

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
/**
 * @brief	Get EXSTOP PCIe Register
 * @param	DdPcieCh	ch
 * @param	kuint16			offset
 * @param	kuint32*			data
 * @return	kint32	D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR
 */
kint32 dd_pcie_rc_get_exs_reg(DdPcieRc *self, DdPcieCh ch, kuint16 offset, kuint32* data)
{
	kint32 ret = D_DDIM_OK;
	kuint32* addr;

	ret = dd_pcie_rc_common_chk_exs_reg_par(dd_pcie_rc_common_get(), ch, offset);
	if (ret != D_DDIM_OK) {
		return ret;
	}

	if (ch == E_DD_PCIE_CH0) {
		addr = (kuint32*) (C_PCIE_0_EXS_ADR + offset);
	} else {
		addr = (kuint32*) (C_PCIE_1_EXS_ADR + offset);
	}

//	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] addr  = 0x%08X\n", addr));
//	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] *addr = 0x%08X\n", *addr));

	*data = *addr;
	return ret;
}

/**
 * @brief	Set EXSTOP PCIe Register
 * @param	DdPcieCh	ch
 * @param	kuint16			offset
 * @param	kuint32			data
 * @return	kint32	D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR
 */
kint32 dd_pcie_rc_set_exs_reg(DdPcieRc *self, DdPcieCh ch, kuint16 offset, kuint32 data)
{
	kint32 ret = D_DDIM_OK;
	kuint32* addr;

	ret = dd_pcie_rc_common_chk_exs_reg_par(dd_pcie_rc_common_get(), ch, offset);
	if (ret != D_DDIM_OK) {
		return ret;
	}

	if (ch == E_DD_PCIE_CH0) {
		addr = (kuint32*) (C_PCIE_0_EXS_ADR + offset);
	} else {
		addr = (kuint32*) (C_PCIE_1_EXS_ADR + offset);
	}

//	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] addr  = 0x%08X\n", addr));
//	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] *addr = 0x%08X\n", *addr));

	*addr = data;
	return ret;
}

/**
 * @brief	Get DBI AXI Slave Register
 * @param	DdPcieCh	ch
 * @param	kuint16			offset
 * @param	kuint32*			data
 * @return	kint32	D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_get_dbi_reg(DdPcieRc *self, DdPcieCh ch, kuint16 offset, kuint32* data)
{
	kint32	ret = D_DDIM_OK;
	kuint32*	addr;

	ret = dd_pcie_rc_common_chk_dbi_reg_par(dd_pcie_rc_common_get(), ch, offset);
	if (ret != D_DDIM_OK) {
		return ret;
	}

	if (ch == E_DD_PCIE_CH0) {
		addr = (kuint32*) (C_PCIE_0_DBI_ADR + offset);
	} else {
		addr = (kuint32*) (C_PCIE_1_DBI_ADR + offset);
	}

//	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] addr  = 0x%08X\n", addr));
//	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] *addr = 0x%08X\n", *addr));

	*data = *addr;
	return ret;
}

/**
 * @brief	Set DBI AXI Slave Register
 * @param	DdPcieCh	ch
 * @param	kuint16			offset
 * @param	kuint32			data
 * @return	kint32	D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_set_dbi_reg(DdPcieRc *self, DdPcieCh ch, kuint16 offset, kuint32 data)
{
	kint32 ret = D_DDIM_OK;
	kuint32* addr;

	ret = dd_pcie_rc_common_chk_dbi_reg_par(dd_pcie_rc_common_get(), ch, offset);
	if (ret != D_DDIM_OK) {
		return ret;
	}

	if (ch == E_DD_PCIE_CH0) {
		addr = (kuint32*) (C_PCIE_0_DBI_ADR + offset);
	} else {
		addr = (kuint32*) (C_PCIE_1_DBI_ADR + offset);
	}

//	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] addr  = 0x%08X\n", addr));
//	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] *addr = 0x%08X\n", *addr));

	*addr = data;
	return ret;
}

/**
 * @brief	Set write access to DBI read-only register.
 * @param	DdPcieCh	ch
 * @return	kint32			D_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32  dd_pcie_rc_set_wr_acc_to_ro_reg(DdPcieRc *self, DdPcieCh ch, kboolean access)
{
	if (dd_pcie_rc_get_link_status(NULL, ch) == TRUE) {	// Link up
		return C_PCIE_ACCESS_ERR;
	}

	if (ch == E_DD_PCIE_CH0) {
		if (DdExs_GET_RAM_PD_CTRL_PCIE0() != 0) {
			// PCIe power down
			return C_PCIE_ACCESS_ERR;
		}

		ioPcie0Core.rc.ppl.mc1.bit.drwe = access;
	} else {	// PCIe ch1
		if (DdExs_GET_RAM_PD_CTRL_PCIE1() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		ioPcie1Core.rc.ppl.mc1.bit.drwe = access;
	}

	return D_DDIM_OK;
}
#endif

DdPcieRc* dd_pcie_rc_new(void)
{
	DdPcieRc* self = k_object_new_with_private(DD_TYPE_PCIE_RC, sizeof(DdPcieRcPrivate));

	return self;
}
