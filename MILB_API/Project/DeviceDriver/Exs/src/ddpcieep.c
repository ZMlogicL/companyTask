/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :周洪
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、PCIe driver for Endpoint mode
*2、将dd_pcie_ep.c更名为ddpcieep.c类
*@version
*1.0.0 2020年06月开始开发
*/

#include "ddimusercustom.h"
#include "chiptop.h"
#include "ddtoptwo.h"
#include "ddtopthree.h"
#include "ddexs.h"
#include "ddexsbranch.h"
#include <string.h>
#include "ddpcieep.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdPcieEp, dd_pcie_ep);
#define DD_PCIE_EP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), DdPcieEpPrivate, DD_TYPE_PCIE_EP))

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#ifndef D_DEBUG_PRINT_INFO_ON
#define DD_PCIE_DEBUG_PRINT(arg)
#else
#define DD_PCIE_DEBUG_PRINT(arg)		{ddim_user_custom_printf arg;}
#endif	// D_DEBUG_PRINT_INFO_ON

struct _DdPcieEpPrivate
{
    volatile TDdPcieEpIntEpCb		gDdPcieEpIntEpCb;
    volatile TDdPcieEpIntOwnCb	gDdPcieEpIntOwnCb;
    volatile DdPcieIntDmaCb			gDdPcieEpIntDmaCb;
    /** PCIe IP mode */
    volatile kuchar							gDdPcieEpReType;	/**< Type Undettled */
    //在interrupt中声明和用到,这里需要写一个get方法
    DdExs  											*ddExs;
    DdTop 											*ddTop;
    DdimUserCustom 						*ddimUserCustom;
};

/*----------------------------------------------------------------------*/
/* DECLS																		*/
/*----------------------------------------------------------------------*/
static kint32 dd_pcie_ep_chk_exs_reg_par(DdPcieEp *self, kushort offset);
static kint32 dd_pcie_ep_chk_dbi_reg_par(DdPcieEp *self, kushort offset);

static void dd_pcie_ep_constructor(DdPcieEp *self)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
    priv->gDdPcieEpIntEpCb.msgUnlockCb = NULL;
    priv->gDdPcieEpIntEpCb.pmTurnofCb = NULL;
    priv->gDdPcieEpIntOwnCb.ceCb = NULL;
    priv->gDdPcieEpIntOwnCb.feCb = NULL;
    priv->gDdPcieEpIntOwnCb.luCb = NULL;
    priv->gDdPcieEpIntOwnCb.nfeCb = NULL;
    priv->gDdPcieEpIntDmaCb.rdCb = NULL;
    priv->gDdPcieEpIntDmaCb.wrCb = NULL;
    priv->gDdPcieEpReType = E_DD_PCIE_RE_TYPE_US;
    priv->ddExs = dd_exs_get();
    priv->ddTop = dd_top_get();
    priv->ddimUserCustom = ddim_user_custom_get();
}

static void dd_pcie_ep_destructor(DdPcieEp *self)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
    if(priv->ddExs)
    {
        k_object_unref(priv->ddExs);
        priv->ddExs = NULL;
    }
    if(priv->ddTop)
    {
        k_object_unref(priv->ddTop);
        priv->ddTop = NULL;
    }
    if(priv->ddimUserCustom)
     {
         k_object_unref(priv->ddimUserCustom);
         priv->ddimUserCustom = NULL;
     }
}

/*----------------------------------------------------------------------*/
/* IMPL																			*/
/*----------------------------------------------------------------------*/
/**
 * @brief	Check EXSTOP PCIe register access parameter.
 * @param	kushort	offset
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_ACCESS_ERR
 */
static kint32 dd_pcie_ep_chk_exs_reg_par(DdPcieEp *self, kushort offset)
{
	// Word boundary check.
	if((offset % 4) != 0){
		return C_PCIE_INPUT_PARAM_ERROR;
	}

	// Check on reserved address.
	if((offset >= 0x0060 && offset <= 0x00FF) ||
	   (offset >= 0x0118 && offset <= 0x01D7) ||
	   (offset == 0x0204) ||
	   (offset == 0x0214) ||
	   (offset == 0x0234) ||
	   (offset >= 0x0288)){
		return C_PCIE_INPUT_PARAM_ERROR;//这里
	}

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	Check DBI AXI slave register access parameter.
 * @param	kushort	offset
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_ACCESS_ERR
 */
static kint32 dd_pcie_ep_chk_dbi_reg_par(DdPcieEp *self, kushort offset)
{
	// Word boundary check.
	if((offset % 4) != 0){
		return C_PCIE_INPUT_PARAM_ERROR;
	}

	// Check on reserved address. Access Type = DBI(Normal Register Access).
	if((offset >= 0x0038 && offset <= 0x003B) ||
	   (offset >= 0x0048 && offset <= 0x004F) ||
	   (offset >= 0x0068 && offset <= 0x006F) ||
	   (offset >= 0x00A4 && offset <= 0x00AF) ||
	   (offset >= 0x00B0 && offset <= 0x00FF) ||
	   (offset >= 0x0160 && offset <= 0x06FF) ||
	   (offset >= 0x0754 && offset <= 0x080B) ||
	   (offset >= 0x0818 && offset <= 0x081F) ||
	   (offset >= 0x0834 && offset <= 0x0887) ||
	   (offset >= 0x088C && offset <= 0x08B7) ||
	   (offset >= 0x08C8 && offset <= 0x08CB) ||
	   (offset >= 0x08DC && offset <= 0x08DF) ||
	   (offset >= 0x08EC && offset <= 0x08EF) ||
	   (offset >= 0x08F8 && offset <= 0x08FF) ||
	   (offset >= 0x0920 && offset <= 0x096F) ||
	   (offset >= 0x0974 && offset <= 0x0977) ||
	   (offset >= 0x0984 && offset <= 0x0987) ||
	   (offset >= 0x0990 && offset <= 0x099B) ||
	   (offset >= 0x09A4 && offset <= 0x09A7) ||
	   (offset >= 0x09B0 && offset <= 0x09BB) ||
	   (offset >= 0x09C0 && offset <= 0x09C3) ||
	   (offset >= 0x09F0 && offset <= 0x09FF) ||
	   (offset >= 0x0A04 && offset <= 0x0A0F) ||
	   (offset >= 0x0A14 && offset <= 0x0A17) ||
	   (offset >= 0x0A20 && offset <= 0x0A23) ||
	   (offset >= 0x0A2C && offset <= 0x0A33) ||
	   (offset >= 0x0A38 && offset <= 0x0A3B) ||
	   (offset >= 0x0A5C && offset <= 0x0A6B) ||
	   (offset >= 0x0A74 && offset <= 0x0A77) ||
	   (offset >= 0x0A94 && offset <= 0x0B2F) ||
	   (offset >= 0x0B34 && offset <= 0x0B3F) ||
	   (offset >= 0x0B48 && offset <= 0x0FFF)){
		return C_PCIE_INPUT_PARAM_ERROR;
	}

	if(DdExs_GET_RAM_PD_CTRL_PCIE0() != 0){
		// PCIe power down
		return C_PCIE_ACCESS_ERR;
	}

	return DriverCommon_DDIM_OK;
}

/*----------------------------------------------------------------------*/
/* PUBLIC(公有函数接口实现)														*/
/*----------------------------------------------------------------------*/
/**
 * @brief	Initialize PCIe Endpoint.
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_TIMEOUT
 */
kint32 dd_pcie_ep_init(DdPcieEp *self)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
	kuchar					function;
	kuchar					direction;
	kuchar					perst=0;
	kuint32					waitCounter;
	DdimUserCustom_ER		ercd;

	DdTopthree_SET_PERSEL3_PRT0SCK3(1);	    	 // bit23 FPSCK4		System reset input when used as Endpoint.
	DdTopthree_SET_PERSEL3_PXW0WP12(1);		// bit12 WPPG12_1	Wakeup request signal from EP to RC.
	DdTopthree_SET_PERSEL3_PXC0SCK7(1);			// bit14 FPSCK8		Reference clock control signal when L1 sub state.

	DdToptwo_SET_CLKSTOP2_EXSAX(2);				// AXI bus clock of EXS is supplied

	dd_exs_set_pcie0_bus_clock_stop_ctrl(priv->ddExs, 0);	// Output PCIE0 BUS CLOCK
	dd_exs_set_ram_pd_ctrl_pcie0(priv->ddExs, 0);			// Power-down mode is released

	// 1 Assert all PHY / LINK resets
	ioPcie0.resetControl1.word = 0x00000000;
	ioPcie0.resetControl2.word = 0x00000000;
	ioPcie0.resetSelect1.word = 0x31111000;
	ioPcie0.resetSelect2.word = 0x00000111;

	// 2 Set P<n>_app_ltssm_enable='0' for reprogramming before linkup.
	// 3 Set device_type (EP)
	ioPcie0.coreControl.bit.deviceType = 0;	// PCI Express Endpoint

	// 4 pipe_port_sel=2'b01 (Disable)
	ioPcie0.phyConfigCom6.bit.pipePortSel = 1;

	// 5 Supply Reference (It has executed)
	// 6 Wait for 10usec (Reference Clocks is stable)
	DD_ARM_WAIT_NS(10000);

	// 7 Wait for de asserting of PERST#
	dd_top_get_gpio_function(priv->ddTop, DdTop_GPIO_PY0, &function);
	dd_top_get_gpio_direction(priv->ddTop, DdTop_GPIO_PY0, &direction);
	dd_top_set_gpio_function(priv->ddTop, DdTop_GPIO_PY0, DdToptwo_GPIO_FUNC_GPIO);
	dd_top_set_gpio_direction(priv->ddTop, DdTop_GPIO_PY0, DdToptwo_GPIO_DIR_IN);

	ioPcie0.resetSelect1.bit.perstSel = 1;

	waitCounter = 0;
	dd_top_get_gpio_status(priv->ddTop, DdTop_GPIO_PY0, &perst);
	while(perst == DdToptwo_GPIO_STATUS_LOW){	// PERSR#==1
		ercd = ddim_user_custom_dly_tsk(priv->ddimUserCustom, 0);
		if (ercd != DdimUserCustom_E_OK){
			DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP]dd_pcie_ep_init: dly_tsk error. ercd = %d\n", ercd));
		}

		if(waitCounter > 100){	// 100ms wait
			DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP]dd_pcie_ep_init: Timeout waitCounter=%d.\n", waitCounter));
			dd_top_set_gpio_function(priv->ddTop, DdTop_GPIO_PY0, function);
			dd_top_set_gpio_direction(priv->ddTop, DdTop_GPIO_PY0, direction);
			return C_PCIE_TIMEOUT;
		}
		waitCounter++;

		dd_top_get_gpio_status(priv->ddTop, DdTop_GPIO_PY0, &perst);
	}
	DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP]dd_pcie_ep_init: PERSR#==1 waitCounter=%d.\n", waitCounter));
	dd_top_set_gpio_function(priv->ddTop, DdTop_GPIO_PY0, function);
	dd_top_set_gpio_direction(priv->ddTop, DdTop_GPIO_PY0, direction);

	// 8 Assert sysAuxPwrDet
	ioPcie0.pmControl2.bit.sysAuxPwrDet = 1;

	// 9 Supply following clocks
	ioPcie0.axiClkStop.word = 0x00000222;
	DdToptwo_SET_CLKSTOP2_PCISUPPCK(2);	// Sub clock of PCI is supplied.

	// 10 De assert PHY reset
	// 11 De assert LINK's PMC reset
	ioPcie0.resetControl1.word = 0x00000033;

	// 12 PHY auto
	// 13 Wrapper auto
	// 14-17 PHY auto
	// 18 Wrapper auto

	// 20 Set P<n>_app_ltssm_enable='1'
	ioPcie0.coreControl.bit.appLtssmEnable = 1;

	priv->gDdPcieEpReType = E_DD_PCIE_RE_TYPE_EP;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	PCIe End.
 */
void dd_pcie_ep_deinit(DdPcieEp *self)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
	// Global data reset
	priv->gDdPcieEpReType = E_DD_PCIE_RE_TYPE_US;
	priv->gDdPcieEpIntEpCb.msgUnlockCb = NULL;
	priv->gDdPcieEpIntEpCb.pmTurnofCb = NULL;
	priv->gDdPcieEpIntOwnCb.luCb = NULL;
	priv->gDdPcieEpIntOwnCb.ceCb = NULL;
	priv->gDdPcieEpIntOwnCb.nfeCb = NULL;
	priv->gDdPcieEpIntOwnCb.feCb = NULL;
	priv->gDdPcieEpIntDmaCb.wrCb = NULL;
	priv->gDdPcieEpIntDmaCb.rdCb = NULL;

	dd_exs_set_ram_pd_ctrl_pcie0(priv->ddExs, 1);	// PCIE0 power down.
	DdToptwo_SET_CLKSTOP2_PCISUPPCK(3);	// Sub clock of PCI is stopped.
}

/**
 * @brief	Execute exclusive control for PCIe channel.
 * @param	kint32	tmout
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_SEM_TIMEOUT/C_PCIE_SEM_NG
 */
kint32 dd_pcie_ep_open(DdPcieEp *self, kint32 tmout)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
	DdimUserCustom_ER	ercd;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (tmout < D_DDIM_USER_SEM_WAIT_FEVR) {
		DriverCommon_DDIM_ASSERTION(("PCIE: input param error. tmout = %x\n", tmout));
		return C_PCIE_INPUT_PARAM_ERROR;
	}
#endif

	if(tmout == DdimUserCustom_SEM_WAIT_POL){
		ercd = ddim_user_custom_pol_sem(priv->ddimUserCustom, DdimUserCustom_SID_DD_PDM);
	}
	else{
		ercd = ddim_user_custom_twai_sem(priv->ddimUserCustom, DdimUserCustom_SID_DD_PDM, (DdimUserCustom_TMO)tmout);
	}

	switch (ercd){
		case DdimUserCustom_E_OK:
			return DriverCommon_DDIM_OK;
		case DdimUserCustom_E_TMOUT:
			return C_PCIE_SEM_TIMEOUT;
		default:
			return C_PCIE_SEM_NG;
	}
}

/**
 * @brief	Cancel exclusive control for PCIe channel.
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_SEM_NG
 */
kint32 dd_pcie_ep_close(DdPcieEp *self)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
	DdimUserCustom_ER	ercd;
	ercd = ddim_user_custom_sig_sem(priv->ddimUserCustom, DdimUserCustom_SID_DD_PDM);	// Exclusive release
	if(DdimUserCustom_E_OK != ercd){
		return C_PCIE_SEM_NG;
	}
	else{
		return DriverCommon_DDIM_OK;
	}
}

/**
 * @brief	Get PCIe link status.
 * @param	E_DD_PCIE_CH	ch
 * @return	BOOL			TRUE/FALSE
 */
BOOL dd_pcie_ep_get_link_status(DdPcieEp *self)
{
	return (BOOL)ioPcie0.linkMonitor.bit.smlhLinkUp;
}

/**
 * @brief	It will be setting up the dma transfer.
 * @param	DdPcieCtrlDma const* const	pcieCtrlDma
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_ep_ctrl_dma(DdPcieEp *self, DdPcieCtrlDma const* const pcieCtrlDma)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
#ifdef DriverCommon_CO_PARAM_CHECK
	if(pcieCtrlDma == NULL){
		return C_PCIE_INPUT_PARAM_ERROR;
	}
#endif

	if(DdExs_GET_RAM_PD_CTRL_PCIE0() != 0){	// PCIe power down
		return C_PCIE_ACCESS_ERR;
	}

	// Interrupt Clear
	ioPcie0Core.ep.ppl.dwic.bit.wdic = 0xFF;
	ioPcie0Core.ep.ppl.dwic.bit.waic = 0xFF;
	ioPcie0Core.ep.ppl.dric.bit.rdic = 0xFF;
	ioPcie0Core.ep.ppl.dric.bit.raic = 0xFF;

	if(pcieCtrlDma->direction == E_DD_PCIE_DMA_DIR_STOD){
		ioPcie0Core.ep.ppl.dwee.bit.dwe = 1;						// Write Engine Enable
		priv->gDdPcieEpIntDmaCb.wrCb = pcieCtrlDma->intDmaCb;	// interrupt dma callback function
	}
	else{
		ioPcie0Core.ep.ppl.dree.bit.dre = 1;						// Read Engine Enable
		priv->gDdPcieEpIntDmaCb.rdCb = pcieCtrlDma->intDmaCb;	// interrupt dma callback function
	}

	ioPcie0Core.ep.ppl.dvs.bit.cn = pcieCtrlDma->dmaCh;		// Channel Number
	ioPcie0Core.ep.ppl.dvs.bit.cd = ~pcieCtrlDma->direction;	// Direction

	if(pcieCtrlDma->mode == E_DD_PCIE_DMA_DEMAND_MODE){	// dmac mode control
		ioPcie0Core.ep.ppl.dcc1.word = 0x00000008;		// Local Interrupt Enable

		ioPcie0Core.ep.ppl.dts.bit.dts = pcieCtrlDma->dmndTransSize;	// Transfer Size
		ioPcie0Core.ep.ppl.dsl.bit.sarl = pcieCtrlDma->dmndSrcAddrL;	// Source Address Low
		ioPcie0Core.ep.ppl.dsh.bit.sarh = pcieCtrlDma->dmndSrcAddrH;	// Source Address Hight
		ioPcie0Core.ep.ppl.ddl.bit.darl = pcieCtrlDma->dmndDstAddrL;	// Destination Address Low
		ioPcie0Core.ep.ppl.ddh.bit.darh = pcieCtrlDma->dmndDstAddrH;	// Destination Address Hight
	}
	else{	// Linked List mode
		if(pcieCtrlDma->direction == E_DD_PCIE_DMA_DIR_STOD){
			ioPcie0Core.ep.ppl.dwllee.bit.wclllaie = 1;	// Write Channel LL Local Abort Interrupt Enable.
			ioPcie0Core.ep.ppl.dwllee.bit.wcllraie = 0;	// Read Channel LL Local Abort Interrupt Disable.
		}
		else{
			ioPcie0Core.ep.ppl.dwllee.bit.wclllaie = 0;	// Write Channel LL Local Abort Interrupt Disable.
			ioPcie0Core.ep.ppl.dwllee.bit.wcllraie = 1;	// Read Channel LL Local Abort Interrupt Enable.
		}

		// DMA Channel Control 1 register
		// Linked List Enable (LLE) = 1
		// Consumer Cycle State (CCS) = 1
		// Traffic Digest TLP Header Bit(TD) = 1
		ioPcie0Core.ep.ppl.dcc1.word = 0x04000300;

		ioPcie0Core.ep.ppl.dll.bit.ll = pcieCtrlDma->llAddr;	// Linked List Pointer Low
	}

	ioPcie0Core.ep.ppl.dwim.bit.wdim &= 0;	// Write Done Interrupt Mask Off
	ioPcie0Core.ep.ppl.dwim.bit.waim &= 0;	// Write Abort Interrupt Mask Off
	ioPcie0Core.ep.ppl.drim.bit.rdim &= 0;	// Read Done Interrupt Mask Off
	ioPcie0Core.ep.ppl.drim.bit.raim &= 0;	// Read Abort Interrupt Mask Off

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	Start DMA.
 * @param	DdPcieDmaCh	dmaCh
 * @param	DdPcieDmaDir	dir
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_ep_start_dma(DdPcieEp *self, DdPcieDmaCh dmaCh, DdPcieDmaDir dir)
{
	if(DdExs_GET_RAM_PD_CTRL_PCIE0() != 0){	// PCIe power down
		return C_PCIE_ACCESS_ERR;
	}

	if(dir == E_DD_PCIE_DMA_DIR_STOD){	// source to destination (write)
		ioPcie0Core.ep.ppl.dwd.bit.wdn = dmaCh;
		ioPcie0Core.ep.ppl.dwd.bit.ws = 0;
	}
	else{								// destination to source (read)
		ioPcie0Core.ep.ppl.drd.bit.rdn = dmaCh;
		ioPcie0Core.ep.ppl.drd.bit.rs = 0;
	}

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	Stop DMA.
 * @param	DdPcieDmaCh	dmaCh
 * @param	DdPcieDmaDir	dir
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_ep_stop_dma(DdPcieEp *self, DdPcieDmaCh dmaCh, DdPcieDmaDir dir)
{
	if(DdExs_GET_RAM_PD_CTRL_PCIE0() != 0){	// PCIe power down
		return C_PCIE_ACCESS_ERR;
	}

	if(dir == E_DD_PCIE_DMA_DIR_STOD){	// source to destination (write)
		ioPcie0Core.ep.ppl.dwd.bit.wdn = dmaCh;
		ioPcie0Core.ep.ppl.dwd.bit.ws = 1;
	}
	else{								// destination to source (read)
		ioPcie0Core.ep.ppl.drd.bit.rdn = dmaCh;
		ioPcie0Core.ep.ppl.drd.bit.rs = 1;
	}

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	It will be setting up the transfer of memory. CPU transfer.
 * @param	DdPcieCtrlMem const* const pcieCtrlMem
 * @return	kint32 DriverCommon_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_COMM_ERROR
 */
kint32 dd_pcie_ep_ctrl_memory(DdPcieEp *self, DdPcieCtrlMem const* const pcieCtrlMem)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(pcieCtrlMem == NULL){
		return C_PCIE_INPUT_PARAM_ERROR;
	}
#endif

	if(dd_pcie_ep_get_link_status(self) == FALSE){	// Not link up
		return C_PCIE_COMM_ERROR;
	}

	ioPcie0Core.ep.ppl.iv.word = 0x00000001;
	ioPcie0Core.ep.ppl.ilba.word = pcieCtrlMem->baseAdr;			// set the Lower Base Address
	ioPcie0Core.ep.ppl.iuba.word = 0x00000000;						// set the Upper Base Address
	ioPcie0Core.ep.ppl.ila.word = pcieCtrlMem->limitAdr;			// set the Limit Address
	ioPcie0Core.ep.ppl.ilta.ob.bit.ltro = pcieCtrlMem->lowTargetAdr;	// set the Lower Target Address
	ioPcie0Core.ep.ppl.iuta.bit.utr = pcieCtrlMem->uppTargetAdr;	// set the Upper Target Address
	ioPcie0Core.ep.ppl.irc1.word = 0x00000000;						// define the type of the region to be MEM
	ioPcie0Core.ep.ppl.irc2.word = 0x80000000;						// enable the region in address match mode

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	It will be controll the INTx send request.
 * @return	kuint32				SYS_INT Status/C_PCIE_ACCESS_ERR
 */
kuint32 dd_pcie_ep_req_int_ep(DdPcieEp *self)
{
	kuint32	sysIntStat = 0;
	kuchar	msie;

	if(DdExs_GET_RAM_PD_CTRL_PCIE0() != 0){
		// PCIe power down
		return C_PCIE_ACCESS_ERR;
	}

	msie = ioPcie0Core.ep.msicr.msiCapIdNextCtrl.bit.msie;
	if(msie == 1){	// MSI Enable
		ioPcie0Core.ep.msicr.msiCapIdNextCtrl.bit.msie = 0;	// Set MSI Disable
	}

	if(dd_pcie_ep_get_st_ltssm_status(self) == E_DD_PCIE_S_L1_IDLE){
		ioPcie0.pmControl2.bit.appReqExitL1 = 1;
	}

	sysIntStat = (~(ioPcie0.intControl1.bit.sysInt) & 1);
	ioPcie0.intControl1.bit.sysInt = sysIntStat;

	ioPcie0Core.ep.msicr.msiCapIdNextCtrl.bit.msie = msie;
	ioPcie0.pmControl2.bit.appReqExitL1 = 0;

	return sysIntStat;
}

/**
 * @brief	It will be controll the MSI transfer request.
 * @param	E_DD_PCIE_MSI_NUM	msi_num
 * @return	kint32				DriverCommon_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kuint32 dd_pcie_ep_transfer_msi(DdPcieEp *self, EDdPcieEpMsiNum msiNum)
{
	kuchar bme;
	kuchar msie;
	kuchar mme;

	if(DdExs_GET_RAM_PD_CTRL_PCIE0() != 0){
		// PCIe power down
		return C_PCIE_ACCESS_ERR;
	}

	bme = ioPcie0Core.ep.t0csh.statusCommand.bit.bme;
	if(bme == 0){	// Bus Master Disable
		ioPcie0Core.ep.t0csh.statusCommand.bit.bme = 1;			// Set Bus Master Enable
	}

	msie = ioPcie0Core.ep.msicr.msiCapIdNextCtrl.bit.msie;
	if(msie == 0){	// MSI Disable
		ioPcie0Core.ep.msicr.msiCapIdNextCtrl.bit.msie = 1;	// Set MSI Enable
	}

	mme = ioPcie0Core.ep.msicr.msiCapIdNextCtrl.bit.mme;
	if(mme != 5){
		ioPcie0Core.ep.msicr.msiCapIdNextCtrl.bit.mme = 5;	// Multiple Message Enable 32 kinds
	}

	if(dd_pcie_ep_get_st_ltssm_status(self) == E_DD_PCIE_S_L1_IDLE){
		ioPcie0.pmControl2.bit.appReqExitL1 = 1;
	}

	ioPcie0.msiRequest1.bit.localInterrupt = (kuint32)1 << msiNum;	// MSI Transfer

	ioPcie0Core.ep.t0csh.statusCommand.bit.bme = bme;
	ioPcie0Core.ep.msicr.msiCapIdNextCtrl.bit.msie = msie;
	ioPcie0Core.ep.msicr.msiCapIdNextCtrl.bit.mme = mme;
	ioPcie0.pmControl2.bit.appReqExitL1 = 0;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	Interrupt handler for PCIe ch0 INTx.
 */
void dd_pcie_ep_ch0_int_ep_handler(DdPcieEp *self)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
	VpCallbackPcieFunc callback;

	DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] CH0 INT_EP Occurred.\n"));
	DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] INT_CONTROL_3_Status \t0x%08X\t0x%08X\n", \
			(kuint32)&ioPcie0.intControl3.word, (kuint32)ioPcie0.intControl3.word));

	// Unlock Message
	if(ioPcie0.intControl3.bit.radmMsgUlStt){
		ioPcie0.intControl3.bit.radmMsgUlStt = 1;	// Interrupt clear
		callback = priv->gDdPcieEpIntEpCb.msgUnlockCb;
		if(callback){
			DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] INT_EP msg_unlock callback\n"));
			(*callback)(0);
		}
	}

	// PME Turn Off
	if(ioPcie0.intControl3.bit.radmPmToffStt){
		ioPcie0.intControl3.bit.radmPmToffStt = 1;	// Interrupt clear
		callback = priv->gDdPcieEpIntEpCb.pmTurnofCb;
		if(callback){
			DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] INT_EP pme turn off callback\n"));
			(*callback)(0);
		}
	}
}

/**
 * @brief	Interrupt handler for PCIe ch0 own.
 */
void dd_pcie_ep_ch0_int_own_handler(DdPcieEp *self)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
	VpCallbackPcieFunc callback;

	DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] CH0 INT_OWN Occurred.\n"));
	DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] INT_CONTROL_2_Status \t0x%08X\t0x%08X\n",\
			(kuint32)&ioPcie0.intControl2.word, (kuint32)ioPcie0.intControl2.word));

	// Link Up
	if(ioPcie0.intControl2.bit.rdlhLinkUpStt){
		ioPcie0.intControl2.bit.rdlhLinkUpStt = 1;	// Interrupt clear
		callback = priv->gDdPcieEpIntOwnCb.luCb;
		if(callback){
			DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] INT_OWN Link Up callback\n"));
			(*callback)(0);
		}
	}

	// Correctable Error
	if(ioPcie0.intControl2.bit.sendCorErrStt){
		ioPcie0.intControl2.bit.sendCorErrStt = 1;	// Interrupt clear
		callback = priv->gDdPcieEpIntOwnCb.ceCb;
		if(callback){
			DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] INT_OWN Correctable Error callback\n"));
			(*callback)(0);
		}
	}

	// Non-Fatal Error
	if(ioPcie0.intControl2.bit.sendNfErrStt){
		ioPcie0.intControl2.bit.sendNfErrStt = 1;	// Interrupt clear
		callback = priv->gDdPcieEpIntOwnCb.nfeCb;
		if(callback){
			DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] INT_OWN Non-Fatal Error callback\n"));
			(*callback)(0);
		}
	}

	// Fatal Error
	if(ioPcie0.intControl2.bit.sendFErrStt){
		ioPcie0.intControl2.bit.sendFErrStt = 1;	// Interrupt clear
		callback = priv->gDdPcieEpIntOwnCb.feCb;
		if(callback){
			DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] INT_OWN Fatal Error callback\n"));
			(*callback)(0);
		}
	}
}

/**
 * @brief	Interrupt handler for PCIe ch0 dma.
 */
void dd_pcie_ep_ch0_int_dma_handler(DdPcieEp *self)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
	kuint32 					status;
	VpCallbackPcieFunc 			callback;

	DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] CH0 INT_DMA Occurred.\n"));

	if(ioPcie0Core.ep.ppl.dwis.word){				// DMA Write Interupt Status (Done and Abort)
		// DMA Write Interrupt Status
		DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] DMA Write Interrupt Status \t0x%08X\t0x%08X\n",\
				(kuint32)&ioPcie0Core.ep.ppl.dwis.word, (kuint32)ioPcie0Core.ep.ppl.dwis.word));

		// ioPcie0Core.ep.ppl.dwis.word
		// 0x00000001  Done Interrupt status(DMA ch0)
		// 0x00010000  Abort Interrupt status(DMA ch0)
		status = ioPcie0Core.ep.ppl.dwis.word;

		ioPcie0Core.ep.ppl.dwic.word = ioPcie0Core.ep.ppl.dwis.word;	// Interrupt clear

		callback = priv->gDdPcieEpIntDmaCb.wrCb;
		if(callback){
			DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] INT_DMA write callback\n"));
			(*callback)(status);
		}
	}
	else if(ioPcie0Core.ep.ppl.dris.word){		// DMA Read Interupt Status (Done and Abort)
		DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] DMA Read Interrupt Status \t0x%08X\t0x%08X\n",\
				(kuint32)&ioPcie0Core.ep.ppl.dris.word, (kuint32)ioPcie0Core.ep.ppl.dris.word));

		// ioPcie0Core.ep.ppl.dris.word
		// 0x00000001  Done Interrupt status(DMA ch0)
		// 0x00010000  Abort Interrupt status(DMA ch0)
		status = ioPcie0Core.ep.ppl.dris.word;

		ioPcie0Core.ep.ppl.dric.word = ioPcie0Core.ep.ppl.dris.word;	// Interrupt clear

		callback = priv->gDdPcieEpIntDmaCb.rdCb;
		if(callback){
			DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] INT_DMA read callback\n"));
			(*callback)(status);
		}
	}
}

/**
 * @brief	Set the function to call back when INT_EP interrupt occurs.
 * @param	T_DD_PCIE_EP_INT_EP_CB	INT_EP callback
 * @return	kint32	DriverCommon_DDIM_OK
 */
kint32 dd_pcie_ep_set_int_ep_func(DdPcieEp *self, TDdPcieEpIntEpCb const* const intEpCb)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
	priv->gDdPcieEpIntEpCb = *intEpCb;

	// Unlock Message
	if(intEpCb->msgUnlockCb != NULL){
		ioPcie0.intControl3.bit.radmMsgUlEn = 1;	// Interrupt Enable
		ioPcie0.intControl3.bit.radmMsgUlCen = 1;	// Interrupt Clear Enable
		ioPcie0.intControl3.bit.radmMsgUlM = 0;	// Mask Off
	}
	else{
		ioPcie0.intControl3.bit.radmMsgUlEn = 0;	// Interrupt Disable
		ioPcie0.intControl3.bit.radmMsgUlCen = 0;	// Interrupt Clear Disable
	}

	// PME Turn Off
	if(intEpCb->pmTurnofCb != NULL){
		ioPcie0.intControl3.bit.radmPmToffEn = 1;	// Interrupt Enable
		ioPcie0.intControl3.bit.radmPmToffCen = 1;	// Interrupt Clear Enable
		ioPcie0.intControl3.bit.radmPmToffM = 0;	// Mask Off
	}
	else{
		ioPcie0.intControl3.bit.radmPmToffEn = 0;	// Interrupt Disable
		ioPcie0.intControl3.bit.radmPmToffCen = 0;	// Interrupt Clear Disable
	}

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	Set the function to call back when INT_TRS_ICS_MSI interrupt occurs.
 * @param	T_DD_PCIE_EP_INT_OWN_CB	INT_OWN callback
 * @return	kint32	DriverCommon_DDIM_OK
 */
kint32 dd_pcie_ep_set_int_own_func(DdPcieEp *self, TDdPcieEpIntOwnCb const* const intOwnCb)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
	priv->gDdPcieEpIntOwnCb = *intOwnCb;

	// Link Up
	if(intOwnCb->luCb != NULL){
		if(dd_pcie_ep_get_link_status(self) == FALSE){	// Not link up
			ioPcie0.intControl2.bit.rdlhLinkUpEn = 1;	// Interrupt Enable
			ioPcie0.intControl2.bit.rdlhLinkUpCen = 1;	// Interrupt Clear Enable
			ioPcie0.intControl2.bit.rdlhLinkUpM = 0;	// Mask Off
		}
	}
	else{
		ioPcie0.intControl2.bit.rdlhLinkUpEn = 0;	// Interrupt Disable
		ioPcie0.intControl2.bit.rdlhLinkUpCen = 0;	// Interrupt Clear Disable
	}

	// Correctable Error
	if(intOwnCb->ceCb != NULL){
		ioPcie0.intControl2.bit.sendCorErrEn = 1;	// Interrupt Enable
		ioPcie0.intControl2.bit.sendCorErrCen = 1;	// Interrupt Clear Enable
		ioPcie0.intControl2.bit.sendCorErrM = 0;	// Mask Off
	}
	else{
		ioPcie0.intControl2.bit.sendCorErrEn = 0;	// Interrupt Disable
		ioPcie0.intControl2.bit.sendCorErrCen = 0;	// Interrupt Clear Disable
	}

	// Non-Fatal Error
	if(intOwnCb->nfeCb != NULL){
		ioPcie0.intControl2.bit.sendNfErrEn = 1;	// Interrupt Enable
		ioPcie0.intControl2.bit.sendNfErrCen = 1;	// Interrupt Clear Enable
		ioPcie0.intControl2.bit.sendNfErrM = 0;	// Mask Off
	}
	else{
		ioPcie0.intControl2.bit.sendNfErrEn = 0;	// Interrupt Disable
		ioPcie0.intControl2.bit.sendNfErrCen = 0;	// Interrupt Clear Disable
	}

	// Fatal Error
	if(intOwnCb->feCb != NULL){
		ioPcie0.intControl2.bit.sendFErrEn = 1;	// Interrupt Enable
		ioPcie0.intControl2.bit.sendFErrCen = 1;	// Interrupt Clear Enable
		ioPcie0.intControl2.bit.sendFErrM = 0;	// Mask Off
	}
	else{
		ioPcie0.intControl2.bit.sendFErrEn = 0;	// Interrupt Disable
		ioPcie0.intControl2.bit.sendFErrCen = 0;	// Interrupt Clear Disable
	}

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	ASPM Control.
 * @param	DdPcieAspmControl aspmControl
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_ep_ctrl_aspm(DdPcieEp *self, DdPcieAspmControl aspmControl)
{
	DdPcieStLtssm	ltssmStatus;

	ltssmStatus = dd_pcie_ep_get_st_ltssm_status(self);
	if(ltssmStatus < E_DD_PCIE_S_L0 || ltssmStatus > E_DD_PCIE_S_L1_IDLE){
		return C_PCIE_ACCESS_ERR;
	}

	ioPcie0Core.ep.pciecr.lcsr.bit.aspmc = aspmControl;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	Get PCIe Power status.
 * @return	DdPciePmst
 */
DdPciePmst dd_pcie_ep_get_pmst_status(DdPcieEp *self)
{
	return (DdPciePmst)ioPcie0.pmMonitor1.bit.pmDstate;
}

/**
 * @brief	Get PCIe LTSSM status.
 * @return	DdPcieStLtssm
 */
DdPcieStLtssm dd_pcie_ep_get_st_ltssm_status(DdPcieEp *self)
{
	return (DdPcieStLtssm)ioPcie0.pmMonitor1.bit.smlhLtssmState;
}

/**
 * @brief	Transfer speed change.
 * @param	DdPcieLinkSpeed	link_speed
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_ep_transfer_speed_change(DdPcieEp *self, DdPcieLinkSpeed linkSpeed)
{
	DdPcieStLtssm	ltssmStatus;

	ltssmStatus = dd_pcie_ep_get_st_ltssm_status(self);
	if(ltssmStatus < E_DD_PCIE_S_L0 || ltssmStatus > E_DD_PCIE_S_L1_IDLE){
		return C_PCIE_ACCESS_ERR;
	}

	if(linkSpeed == E_DD_PCIE_LINK_SPEED_GEN1){
		ioPcie0Core.ep.pciecr.lc2sr.bit.tls = 0x1;	// 2.5GT/s
	}
	else{
		ioPcie0Core.ep.pciecr.lc2sr.bit.tls = 0x2;	// 5.0GT/s
	}

	ioPcie0Core.ep.ppl.gen2c.bit.dsc = 0x0;	// Assert
	ioPcie0Core.ep.ppl.gen2c.bit.dsc = 0x1;	// Deassert

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	Get current link speed.
 * @param	DdPcieLinkSpeed	current_link_speed
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_ep_get_current_link_speed(DdPcieEp *self, DdPcieLinkSpeed* currentLinkSpeed)
{
	if(DdExs_GET_RAM_PD_CTRL_PCIE0() != 0){
		// PCIe power down
		return C_PCIE_ACCESS_ERR;
	}

	*currentLinkSpeed = (DdPcieLinkSpeed)ioPcie0Core.ep.pciecr.lcsr.bit.cls;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	Get ASPM Status.
 * @param	E_DD_PCIE_CH			ch
 * @param	DdPcieAspmControl	aspm_status
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_ep_get_aspm_status(DdPcieEp *self, DdPcieAspmControl* aspmStatus)
{
	if(DdExs_GET_RAM_PD_CTRL_PCIE0() != 0){
		return C_PCIE_ACCESS_ERR;
	}

	*aspmStatus = (DdPcieAspmControl)ioPcie0Core.ep.pciecr.lcsr.bit.aspmc;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	Set max payload size.
 * @param	DdPcieMps	mps
 * @return	kint32			DriverCommon_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_ep_set_mps(DdPcieMps mps)
{
	if(DdExs_GET_RAM_PD_CTRL_PCIE0() != 0){
		return C_PCIE_ACCESS_ERR;
	}

	ioPcie0Core.ep.pciecr.dcsr.bit.mps = mps;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	Get max payload size.
 * @param	DdPcieMps*	mps
 * @return	kint32			DriverCommon_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_ep_get_mps(DdPcieMps* mps)
{
	if(DdExs_GET_RAM_PD_CTRL_PCIE0() != 0){
		return C_PCIE_ACCESS_ERR;
	}

	*mps = ioPcie0Core.ep.pciecr.dcsr.bit.mps;

	return DriverCommon_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
/**
 * @brief	Get EXSTOP PCIe Register
 * @param	kushort			offset
 * @param	kuint32*			data
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR
 */
kint32 dd_pcie_ep_get_exs_reg(DdPcieEp *self, kushort offset, kuint32* data)
{
	kint32	ret = DriverCommon_DDIM_OK;
	kuint32*	addr;

	ret = dd_pcie_ep_chk_exs_reg_par(self, self, offset);
	if(ret != DriverCommon_DDIM_OK){
		return ret;
	}

	addr = (kuint32*)(C_PCIE_0_EXS_ADR + offset);

//	DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] addr = 0x%08X\n", addr));
//	DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] *addr = 0x%08X\n", *addr));

	*data = *addr;

	return ret;
}

/**
 * @brief	Set EXSTOP PCIe Register
 * @param	kushort			offset
 * @param	kuint32			data
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR
 */
kint32 dd_pcie_ep_set_exs_reg(DdPcieEp *self, kushort offset, kuint32 data)
{
	kint32	ret = DriverCommon_DDIM_OK;
	kuint32*	addr;

	ret = dd_pcie_ep_chk_exs_reg_par(self, offset);
	if(ret != DriverCommon_DDIM_OK){
		return ret;
	}

	addr = (kuint32*)(C_PCIE_0_EXS_ADR + offset);

	*addr = data;

	return ret;
}

/**
 * @brief	Get DBI AXI Slave Register
 * @param	kushort			offset
 * @param	kuint32*			data
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_ep_get_dbi_reg(DdPcieEp *self, kushort offset, kuint32* data)
{
	kint32	ret = DriverCommon_DDIM_OK;
	kuint32*	addr;

	ret = dd_pcie_ep_chk_dbi_reg_par(self, offset);
	if(ret != DriverCommon_DDIM_OK){
		return ret;
	}

	addr = (kuint32*)(C_PCIE_0_DBI_ADR + offset);

//	DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] addr = 0x%08X\n", addr));
//	DD_PCIE_DEBUG_PRINT(("[DD_PCIE_EP] *addr = 0x%08X\n", *addr));

	*data = *addr;

	return ret;
}

/**
 * @brief	Set DBI AXI Slave Register
 * @param	kushort			offset
 * @param	kuint32			data
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_ep_set_dbi_reg(DdPcieEp *self, kushort offset, kuint32 data)
{
	kint32	ret = DriverCommon_DDIM_OK;
	kuint32*	addr;

	ret = dd_pcie_ep_chk_dbi_reg_par(self, offset);
	if(ret != DriverCommon_DDIM_OK){
		return ret;
	}

	addr = (kuint32*)(C_PCIE_0_DBI_ADR + offset);

	*addr = data;

	return ret;
}

/**
 * @brief	Set write access to DBI read-only register.
 * @return	kint32	DriverCommon_DDIM_OK/C_PCIE_ACCESS_ERR
 */
kint32  dd_pcie_ep_set_wr_acc_to_ro_reg(DdPcieEp *self, BOOL access)
{
	if(DdExs_GET_RAM_PD_CTRL_PCIE0() != 0){
		// PCIe power down
		return C_PCIE_ACCESS_ERR;
	}

	ioPcie0Core.ep.ppl.mc1.bit.drwe = access;

	return DriverCommon_DDIM_OK;
}
#endif

kint32 dd_pcie_ep_get_gddpcieepretype(DdPcieEp *self)
{
	DdPcieEpPrivate *priv = DD_PCIE_EP_GET_PRIVATE(self);
	return priv->gDdPcieEpReType;
}

DdPcieEp* dd_pcie_ep_get(void)
{
	static DdPcieEp *ddPcieEp = NULL;
	if(!ddPcieEp)
	{
		ddPcieEp = k_object_new_with_private(DD_TYPE_PCIE_EP,sizeof(DdPcieEpPrivate));
	}
    return ddPcieEp;
}
