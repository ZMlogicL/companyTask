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
*2、将dd_pcie_ep.h更名为ddpcieep.h类
*@version
*1.0.0 2020年06月开始开发
*/
/**
@weakgroup dd_pcie_ep
@{

<hr>

- @ref PCIe_EP_Sequence_Initialize
- @ref PCIe_EP_Sequence_Speed_change
- @ref PCIe_EP_Sequence_Memory_access
- @ref PCIe_EP_Sequence_DMA_transfer
- @ref PCIe_EP_Sequence_MSI_transfer
- @ref PCIe_EP_Sequence_INTx_message
- @ref PCIe_EP_Sequence_end
@section dd_pcie_ep_sample Sample Code
- @ref PCIe_EP_Sample_Initialize
- @ref PCIe_EP_Sample_Speed_Change
- @ref PCIe_EP_Sample_Memory_Access
- @ref PCIe_EP_Sample_Demand_DMA_Transfer
- @ref PCIe_EP_Sample_LL_DMA_Transfer
- @ref PCIe_EP_Sample_ASPM
- @ref PCIe_EP_Sample_Interrupt
- @ref PCIe_EP_Sample_End

@section PCIe_EP_Sequence_Initialize					Initial setting.
@image html dd_pcie_ep_Initialize.png

@section PCIe_EP_Sequence_Speed_change					Change of transfer speed.
@image html dd_pcie_ep_transfer_speed_change.png

@section PCIe_EP_Sequence_Memory_access					Access to the memory of Root Complex side.
@image html dd_pcie_ep_memory.png

@section PCIe_EP_Sequence_DMA_transfer					Data transfer by DMA.
@image html dd_pcie_ep_dma_transfer.png

@section PCIe_EP_Sequence_MSI_transfer					MSI transfer.
@image html dd_pcie_ep_MSI_transfer.png

@section PCIe_EP_Sequence_INTx_message					INTx message send.
@image html dd_pcie_ep_INTx_message.png

@section PCIe_EP_Sequence_end							PCIe end.
@image html dd_pcie_ep_end.png

@}
*/

/**
@addtogroup dd_pcie_ep
@{

*/

#ifndef __DD_PCIE_EP_H__
#define __DD_PCIE_EP_H__

#include <klib.h>
#include "driver_common.h"
#include "exstop.h"
#include "ddpciecomm.h"

#define DD_TYPE_PCIE_EP     (dd_pcie_ep_get_type())
#define DD_PCIE_EP(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, DdPcieEp))
#define DD_IS_PCIE_EP(obj)  (K_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_PCIE_EP))

typedef struct _TDdPcieEpIntEpCb 		TDdPcieEpIntEpCb;
typedef struct _TDdPcieEpIntOwnCb 	TDdPcieEpIntOwnCb;

typedef struct _DdPcieEp                			DdPcieEp;
typedef struct _DdPcieEpPrivate 			DdPcieEpPrivate;

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/** MSI Number */
typedef enum {
	ddpcieep_00 = 0,			/**< msi number 0	*/
	ddpcieep_01,				/**< msi number 1	*/
	ddpcieep_02,				/**< msi number 2	*/
	ddpcieep_03,				/**< msi number 3	*/
	ddpcieep_04,				/**< msi number 4	*/
	ddpcieep_05,				/**< msi number 5	*/
	ddpcieep_06,				/**< msi number 6	*/
	ddpcieep_07,				/**< msi number 7	*/
	ddpcieep_08,				/**< msi number 8	*/
	ddpcieep_09,				/**< msi number 9	*/
	ddpcieep_10,				/**< msi number 10	*/
	ddpcieep_11,				/**< msi number 11	*/
	ddpcieep_12,				/**< msi number 12	*/
	ddpcieep_13,				/**< msi number 13	*/
	ddpcieep_14,				/**< msi number 14	*/
	ddpcieep_15,				/**< msi number 15	*/
	ddpcieep_16,				/**< msi number 16	*/
	ddpcieep_17,				/**< msi number 17	*/
	ddpcieep_18,				/**< msi number 18	*/
	ddpcieep_19,				/**< msi number 19	*/
	ddpcieep_20,				/**< msi number 20	*/
	ddpcieep_21,				/**< msi number 21	*/
	ddpcieep_22,				/**< msi number 22	*/
	ddpcieep_23,				/**< msi number 23	*/
	ddpcieep_24,				/**< msi number 24	*/
	ddpcieep_25,				/**< msi number 25	*/
	ddpcieep_26,				/**< msi number 26	*/
	ddpcieep_27,				/**< msi number 27	*/
	ddpcieep_28,				/**< msi number 28	*/
	ddpcieep_29,				/**< msi number 29	*/
	ddpcieep_30,				/**< msi number 30	*/
	ddpcieep_31					/**< msi number 31	*/
} EDdPcieEpMsiNum;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/** PCIe interrupt x callback. */
struct _TDdPcieEpIntEpCb
{
	VpCallbackPcieFunc	msgUnlockCb;	/**< radm_msg_unlock callback	*/
	VpCallbackPcieFunc	pmTurnofCb;	/**< radm_pm_turnof callback	*/
};

/** PCIe interrupt own callback. */
struct _TDdPcieEpIntOwnCb
{
	VpCallbackPcieFunc	luCb;	/**< Link Up callback			*/
	VpCallbackPcieFunc	ceCb;	/**< Correctable Error callback	*/
	VpCallbackPcieFunc	nfeCb;	/**< Non-Fatal Error callback	*/
	VpCallbackPcieFunc	feCb;	/**< Fatal Error callback		*/
};

struct _DdPcieEp
{
	KObject parent;
};

KConstType 	dd_pcie_ep_get_type(void);
DdPcieEp* 	dd_pcie_ep_get(void);

/*----------------------------------------------------------------------*/
/* Function 															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/**
Initialize PCIe Endpoint.<br>
@retval DriverCommon_DDIM_OK			OK
@retval C_PCIE_TIMEOUT	Initialize timeout NG.
@remarks This API uses DDIM_User_Dly_Tsk().
*/
kint32	dd_pcie_ep_init(DdPcieEp *self);

/**
PCIe end.<br>
*/
void		dd_pcie_ep_deinit(DdPcieEp *self);

/**
Execute exclusive control for PCIe channel.<br>
@param [in]	tmout	Time of timeout<br>
						<ul><li>Positive Value(Time of timeout)
							<li>@ref DdimUserCustom_SEM_WAIT_POL
							<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
@retval DriverCommon_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Input parameter error.
@retval C_PCIE_SEM_TIMEOUT		Semaphore acquisition Time Out.
@retval C_PCIE_SEM_NG			Semaphore acquisition NG.
@remarks This API uses ddim_user_custom_pol_sem(priv->ddimUserCustom,) when waitTime is set to 0. <br>
		 This API uses ddim_user_custom_twai_sem(priv->ddimUserCustom,) when waitTime is set to the value except for 0.
*/
kint32	dd_pcie_ep_open(DdPcieEp *self, kint32 tmout);

/**
Cancel exclusive control for PCIe channel.<br>
@retval DriverCommon_DDIM_OK			OK
@retval D_DD_AUDIO_SEM_NG	Semaphore release NG.
@remarks This API uses ddim_user_custom_sig_sem(priv->ddimUserCustom,).
*/
kint32	dd_pcie_ep_close(DdPcieEp *self);

/**
Get PCIe link status.<br>
@retval TRUE	link up
@retval FALSE	link down
*/
BOOL	dd_pcie_ep_get_link_status(DdPcieEp *self);

/**
It will be setting up the dma transfer.<br>
@param[in]	pcieCtrlDma		dma control table.	See @ref DdPcieCtrlDma.
@retval DriverCommon_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Input parameter error.
@retval C_PCIE_ACCESS_ERR		PCIe power down.(dd_pcie_ep_init unexecution)
@remarks
	- With the function for the opposing device to make the memory light a trigger and to generate interrupt, DMA Remote Interrupt can be used.
*/
kint32	dd_pcie_ep_ctrl_dma(DdPcieEp *self, DdPcieCtrlDma const* const pcieCtrlDma);

/**
Start DMA.<br>
@param[in]	dmaCh	Dma channel	See @ref DdPcieDmaCh.
@param[in]	dir		Direction	See @ref DdPcieDmaDir.
@retval DriverCommon_DDIM_OK				OK
@retval C_PCIE_ACCESS_ERR	PCIe power down.(dd_pcie_ep_init unexecution)
*/
kint32	dd_pcie_ep_start_dma(DdPcieEp *self, DdPcieDmaCh dmaCh, DdPcieDmaDir dir);

/**
Stop DMA.<br>
@param[in]	dmaCh	Dma channel	See @ref DdPcieDmaCh.
@param[in]	dir		Direction	See @ref DdPcieDmaDir.
@retval DriverCommon_DDIM_OK				OK
@retval C_PCIE_ACCESS_ERR	PCIe power down.(dd_pcie_ep_init unexecution)
*/
kint32	dd_pcie_ep_stop_dma(DdPcieEp *self, DdPcieDmaCh dmaCh, DdPcieDmaDir dir);

/**
It will be setting up the transfer of memory. CPU transfer.<br>
@param[in]	pcieCtrlMem		memory control data. See @ref DdPcieCtrlMem.
@retval DriverCommon_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Input parameter error.
@retval C_PCIE_COMM_ERROR		Communication error. (Not link up)
@remarks
			- Please use by Link Up state.
*/
kint32	dd_pcie_ep_ctrl_memory(DdPcieEp *self, DdPcieCtrlMem const* const pcieCtrlMem);

/**
It will be controll the INTx send request.<br>
@retval	SYS_INT Status value. (0:Assert_INTx message was send / 1:Deassert_INTx message was send)
@retval C_PCIE_ACCESS_ERR	PCIe power down. (dd_pcie_ep_init unexecution)
@remarks
			- This API is reverse the SYS_INT value, and return the SYS_INT value after reverved.
			- If the SYS_INT is 0 to 1, send the Assert_INTx message.
			- If the SYS_INT is 1 to 0, send the Deassert_INTx message.
*/
kuint32	dd_pcie_ep_req_int_ep(DdPcieEp *self);

/**
It will be controll the MSI transfer request.
@param[in]	msi_num		MSI number. See @ref E_DD_PCIE_EP_MSI_NUM.
@retval DriverCommon_DDIM_OK					OK
@retval C_PCIE_ACCESS_ERR		PCIe power down. (dd_pcie_ep_init unexecution)
*/
kuint32	dd_pcie_ep_transfer_msi(DdPcieEp *self, EDdPcieEpMsiNum msiNum);

/**
Interrupt handler for PCIe ch0 ep.<br>
*/
void		dd_pcie_ep_ch0_int_ep_handler(DdPcieEp *self);

/**
Interrupt handler for PCIe ch0 own.<br>
*/
void		dd_pcie_ep_ch0_int_own_handler(DdPcieEp *self);

/**
Interrupt handler for PCIe ch0 dma.<br>
*/
void		dd_pcie_ep_ch0_int_dma_handler(DdPcieEp *self);

/**
Set the function to call back when INT_EP interrupt occurs.
@param [in] intEpCb	callback function table. See @ref T_DD_PCIE_EP_INT_EP_CB.
@retval DriverCommon_DDIM_OK	OK
*/
kint32	dd_pcie_ep_set_int_ep_func(DdPcieEp *self, TDdPcieEpIntEpCb const* const intEpCb);

/**
Set the function to call back when INT_OWN interrupt occurs.
@param [in] intOwnCb	callback function table. See @ref T_DD_PCIE_EP_INT_OWN_CB.
@retval DriverCommon_DDIM_OK	OK
@remarks
			- The luCb setting in Link up is invalid.
*/
kint32	dd_pcie_ep_set_int_own_func(DdPcieEp *self, TDdPcieEpIntOwnCb const* const intOwnCb);

/**
ASPM control.
@param[in]	aspmControl	ASPM control.	See @ref DdPcieAspmControl.
@retval DriverCommon_DDIM_OK					OK
@retval C_PCIE_ACCESS_ERR		Power status not D0.<br>
									Link status is not L0/L0s/L1.
*/
kint32	dd_pcie_ep_ctrl_aspm(DdPcieEp *self, DdPcieAspmControl aspmControl);

/**
Get PCIe Power status.
@retval See @ref DdPciePmst.
*/
DdPciePmst	dd_pcie_ep_get_pmst_status(DdPcieEp *self);

/**
Get PCIe LTSSM status.
@retval See @ref DdPcieStLtssm.
*/
DdPcieStLtssm	dd_pcie_ep_get_st_ltssm_status(DdPcieEp *self);

/**
Transfer speed change.
@param[in]	link_speed	Link Speed. See @ref DdPcieLinkSpeed.
@retval DriverCommon_DDIM_OK				OK
@retval C_PCIE_ACCESS_ERR	Link status is not L0/L0s/L1.
@remarks
		- It opposite device is 5.0GT/s support.<br>
*/
kint32	dd_pcie_ep_transfer_speed_change(DdPcieEp *self, DdPcieLinkSpeed linkSpeed);

/**
Get current link speed.
@param[in]	current_link_speed	Current link speed. See @ref DdPcieLinkSpeed.
@retval DriverCommon_DDIM_OK				OK
@retval C_PCIE_ACCESS_ERR	PCIe power down. (dd_pcie_ep_init unexecution)
*/
kint32	dd_pcie_ep_get_current_link_speed(DdPcieEp *self, DdPcieLinkSpeed* currentLinkSpeed);

/**
Get ASPM status.
@param[in]	aspm_status	ASPM status. See @ref DdPcieAspmControl.
@retval DriverCommon_DDIM_OK				OK
@retval C_PCIE_ACCESS_ERR	PCIe power down. (dd_pcie_ep_init unexecution)
*/
kint32	dd_pcie_ep_get_aspm_status(DdPcieEp *self, DdPcieAspmControl* aspmStatus);

/**
Set max payload size.
@param[in]	mps		Max Payload Size. See @ref DdPcieMps.
@retval DriverCommon_DDIM_OK				OK
@retval C_PCIE_ACCESS_ERR	PCIe power down. (dd_pcie_ep_init unexecution)
*/
kint32 dd_pcie_ep_set_mps(DdPcieEp *self, DdPcieMps mps);

/**
Get max payload size.
@param[out]	mps		Max Payload Size. See @ref DdPcieMps.
@retval DriverCommon_DDIM_OK				OK
@retval C_PCIE_ACCESS_ERR	PCIe power down. (dd_pcie_ep_init unexecution)
*/
kint32 dd_pcie_ep_get_mps(DdPcieEp *self, DdPcieMps* mps);

#ifdef CO_DDIM_UTILITY_USE
/** @name Utility Functions
@{*/
//---------------------- utility section -------------------------------
/**
Get EXSTOP PCIe register.
@param[in]	offset	Offset of EXSTOP PCIe register.
@param[out]	data	Get data.
@retval DriverCommon_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Violation of word boundary or reservation register.
@retval C_PCIE_ACCESS_ERR		PCIe power down. (dd_pcie_ep_init unexecution)
*/
kint32 dd_pcie_ep_get_exs_reg(DdPcieEp *self, kushort offset, kuint32* data);

/**
Set EXSTOP PCIe register.
@param[in]	offset	Offset of EXSTOP PCIe register.
@param[in]	data	Set data.
@retval DriverCommon_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Violation of word boundary or reservation register.
@retval C_PCIE_ACCESS_ERR		PCIe power down. (dd_pcie_ep_init unexecution)
*/
kint32 dd_pcie_ep_set_exs_reg(DdPcieEp *self, kushort offset, kuint32 data);

/**
Get DBI AXI Slave register.
@param[in]	offset	Offset of DBI AXI Slave register.
@param[out]	data	Get data.
@retval DriverCommon_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Violation of word boundary or reservation register.
@retval C_PCIE_ACCESS_ERR		PCIe power down. (dd_pcie_ep_init unexecution)
*/
kint32 dd_pcie_ep_get_dbi_reg(DdPcieEp *self, kushort offset, kuint32* data);

/**
Set DBI AXI Slave register.
@param[in]	offset	Offset of DBI AXI Slave register.
@param[in]	data	Set data.
@retval DriverCommon_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Violation of word boundary or reservation register.
@retval C_PCIE_ACCESS_ERR		PCIe power down. (dd_pcie_ep_init unexecution)
*/
kint32 dd_pcie_ep_set_dbi_reg(DdPcieEp *self, kushort offset, kuint32 data);

/**
Set write access to DBI read-only register.
@param[in]	access	DBI Read only register access mode. (TRUE:access, FALSE:not access)
@retval DriverCommon_DDIM_OK	OK
@retval C_PCIE_ACCESS_ERR	PCIe power down.(dd_pcie_ep_init unexecution)
*/
kint32	dd_pcie_ep_set_wr_acc_to_ro_reg(DdPcieEp *self, BOOL access);

//---------------------- colabo  section -------------------------------
// Nothing Special
/*  @}*/
#endif

kint32 dd_pcie_ep_get_gddpcieepretype(DdPcieEp *self);

#ifdef __cplusplus
"C" {
#endif	// __cplusplus

#endif /* __DD_PCIE_EP_H__ */

/*@}*/

/**
@weakgroup dd_pcie_ep
@{

	<br>
	<br>
	The example of PCIe is as follows.<br>
	Sample code, use the PCIE to the opposing device.
	<hr>
	@section PCIe_EP_Sample_Initialize	Sample of Initialize.
	@code
	static void pcie_ep_lu_cb(kint32 status)
	{
		DriverCommon_DDIM_PRINT(("Link Up.\n"));
	}

	void PCIe_EP_Sample_Initialize(DdPcieEp *self)
	{
		kint32 ret;
		TDdPcieEpIntOwnCb intOwnCb

		memset(&intOwnCb, 0, sizeof(intOwnCb));
		intOwnCb.luCb = (VpCallbackPcieFunc)pcie_ep_lu_cb;
		dd_pcie_ep_set_int_own_func(&intOwnCb);

		ret = dd_pcie_ep_init();
		if(ret != DriverCommon_DDIM_OK){
			DriverCommon_DDIM_PRINT(("dd_pcie_ep_init Error. ret=0x%08x\n", ret));
			return;
		}

		ret = Dd_Pcie_EP_Open(DdimUserCustom_SEM_WAIT_POL);
		if(ret != DriverCommon_DDIM_OK){
			DriverCommon_DDIM_PRINT(("dd_pcie_ep_open Error. ret=0x%08x\n", ret));
			return;
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_EP_Sample_Speed_Change	Sample of transfer speed change.
	@code
	void PCIe_EP_Sample_Speed_Change(DdPcieEp *self)
	{
		kint32 ret;

		if(dd_pcie_ep_get_link_status() == TRUE){
			ret = dd_pcie_ep_transfer_speed_change(E_DD_PCIE_LINK_SPEED_GEN2);	// GEN1(2.5GT/s) -> GEN2(5.0GT/s)
			if(ret == DriverCommon_DDIM_OK){
				DriverCommon_DDIM_PRINT(("Current Link Speed. %d\n", dd_pcie_ep_get_current_link_speed()));
			}
			else{
				DriverCommon_DDIM_PRINT(("dd_pcie_ep_transfer_speed_change Error. ret=0x%08x\n", ret));
			}
		}
		else{
			DriverCommon_DDIM_PRINT(("Transfer speed change is not available.\n"));
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_EP_Sample_Memory_Access	Sample of memory access.
	@code
	void PCIe_EP_Sample_Memory_Access(DdPcieEp *self)
	{
		kint32 ret;
		DdPcieCtrlMem pcieCtrlMem;

		if(dd_pcie_ep_get_link_status() == TRUE){
			memset(&pcieCtrlMem, 0, sizeof(pcieCtrlMem));
			pcieCtrlMem.ch	 = E_DD_PCIE_CH0;
			pcieCtrlMem.base_adr = 0x19400000;
			pcieCtrlMem.limit_adr = 0x1940ffff;
			pcieCtrlMem.low_target_adr = 0x58000000;
			ret = dd_pcie_ep_ctrl_memory(&pcieCtrlMem);
			if(ret == DriverCommon_DDIM_OK){
				memcpy((void*)0x19400000, "PCIe Start 1", 12);	// RC write 0x19400000
				DDIM_User_L1l2cache_Clean_Flush_Addr(0x19400000, 12);
			}
			else{
				DriverCommon_DDIM_PRINT(("dd_pcie_ep_ctrl_memory Error. ret=0x%08x\n", ret));
			}
		}
		else{
			DriverCommon_DDIM_PRINT(("Memory access is not available.\n"));
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_EP_Sample_Demand_DMA_Transfer	Sample of Demand mode DMA transfer.
	@code
	static void pcie_ep_int_dma_cb(kint32 status)
	{
		// status
		// 0x00000001  Done Interrupt status(DMA ch0)
		// 0x00000002  Done Interrupt status(DMA ch1)
		// 0x00010000  Abort Interrupt status(DMA ch0)
		// 0x00020000  Abort Interrupt status(DMA ch1)
	}

	void PCIe_EP_Sample_Demand_DMA_Transfer(DdPcieEp *self)
	{
		kint32 ret;
		DdPcieCtrlDma pcieCtrlDma;

		memset(&pcieCtrlDma, 0, sizeof(pcieCtrlDma));
		pcieCtrlDma.mode	 = E_DD_PCIE_DMA_DEMAND;
		pcieCtrlDma.ch	 = E_DD_PCIE_CH0;
		pcieCtrlDma.dmaCh = E_DD_PCIE_DMA_CH0;
		pcieCtrlDma.dmnd_src_addr = 0x58000000;
		pcieCtrlDma.dmndDstAddrL = 0x5F000000;
		pcieCtrlDma.dmndTransSize = 0x3FC000;
		pcieCtrlDma.direction = E_DD_PCIE_DMA_DIR_STOD;
		pcieCtrlDma.int_dma_callback = (VpCallbackPcieFunc)pcie_ep_int_dma_cb;
		ret = dd_pcie_ep_ctrl_dma(&pcieCtrlDma);
		if(ret == DriverCommon_DDIM_OK){
			dd_pcie_ep_start_dma(pcieCtrlDma.ch, pcieCtrlDma.direction);
		}
		else{
			DriverCommon_DDIM_PRINT(("dd_pcie_ep_ctrl_dma Error. ret=0x%08x\n", ret));
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_EP_Sample_LL_DMA_Transfer	Sample of Linked List mode DMA Transfer.
	@code

	#define PCIE_DMA_LL_ADDR	(0x55000000)

	static void pcie_ep_ll_dma(DdPcieEp *self)
	{
		kuint32 Linked_list[22];

		Linked_list[0] = 0x00000001;	// Channel Control
		Linked_list[1] = 0x00000004;	// Transfer Size
		Linked_list[2] = 0x58000000;	// SAR Low
		Linked_list[3] = 0x0;			// SAR High
		Linked_list[4] = 0x5F000000;	// DAR Low
		Linked_list[5] = 0x0;			// DAR High
		// Element 1
		Linked_list[6] = 0x00000001;	// Channel Control
		Linked_list[7] = 0x00000004;	// Transfer Size
		Linked_list[8] = 0x58000004;	// SAR Low
		Linked_list[9] = 0x0;			// SAR High
		Linked_list[10] = 0x5F000004;	// DAR Low
		Linked_list[11] = 0x0;			// DAR High
		// Element 2
		Linked_list[12] = 0x00000009;	// Channel Control (Local Interrupt Enable)
		Linked_list[13] = 0x00000004;	// Transfer Size
		Linked_list[14] = 0x58000008;	// SAR Low
		Linked_list[15] = 0x0;			// SAR High
		Linked_list[16] = 0x5F000008;	// DAR Low
		Linked_list[17] = 0x0;			// DAR High
		// Element 3
		Linked_list[18] = 0x00000004;	// Channel Control (Linked List End)
		Linked_list[19] = 0x0;
		Linked_list[20] = 0x0;
		Linked_list[21] = 0x0;

		memcpy((void*)PCIE_DMA_LL_ADDR, (void*)Linked_list, sizeof(Linked_list));
		DDIM_User_L1l2cache_Clean_Flush_Addr(PCIE_DMA_LL_ADDR, sizeof(Linked_list));
	}

	void PCIe_EP_Sample_LL_DMA_Transfer(DdPcieEp *self)
	{
		kint32 ret;
		DdPcieCtrlDma pcieCtrlDma;

		pcie_ep_ll_dma();
		memset(&pcieCtrlDma, 0, sizeof(pcieCtrlDma));
		pcieCtrlDma.mode	 = E_DD_PCIE_DMA_LL_MODE;
		pcieCtrlDma.ch	 = E_DD_PCIE_CH0;
		pcieCtrlDma.dmaCh = E_DD_PCIE_DMA_CH0;
		pcieCtrlDma.llAddr = PCIE_DMA_LL_ADDR;
		pcieCtrlDma.direction = E_DD_PCIE_DMA_DIR_STOD;
		pcieCtrlDma.int_dma_callback = (VpCallbackPcieFunc)pcie_ep_int_dma_cb;
		ret = dd_pcie_ep_ctrl_dma(&pcieCtrlDma);
		if(ret == DriverCommon_DDIM_OK){
			dd_pcie_ep_start_dma(pcieCtrlDma.ch, pcieCtrlDma.direction);
		}
		else{
			DriverCommon_DDIM_PRINT(("dd_pcie_ep_ctrl_dma Error. ret=0x%08x\n", ret));
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_EP_Sample_ASPM	Sample of ASPM.
	@code
	void PCIe_EP_Sample_ASPM(DdPcieEp *self)
	{
		kint32 ret;

		if(dd_pcie_ep_get_link_status() == TRUE){
			ret = dd_pcie_ep_ctrl_aspm(DdPcieComm_L0S_L1);
			if(ret == DriverCommon_DDIM_OK){
				DriverCommon_DDIM_PRINT(("dd_pcie_ep_ctrl_aspm OK.\n"));
			}
			else{
				DriverCommon_DDIM_PRINT(("dd_pcie_ep_ctrl_aspm Error. ret=0x%08x\n", ret));
			}
		}
		else{
			DriverCommon_DDIM_PRINT(("ASPM is not available.\n"));
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_EP_Sample_Message		Sample of Message transfer.
	@code
	// Message transfer. -------------------------------------------------------
	// MSI transfer-------------------------------------------------------------
	void PCIe_EP_Sample_Transfer_MSI(DdPcieEp *self)
	{
		kint32  ret;

		if(dd_pcie_ep_get_link_status() == TRUE){
			ret =dd_pcie_ep_transfer_msi(E_DD_PCIE_EP_MSI_NUM_00);
			if(ret == DriverCommon_DDIM_OK){
			}
			else{
				DriverCommon_DDIM_PRINT(("dd_pcie_ep_transfer_msi Error. ret=0x%08x\n", ret));
			}
		}
		else{
			DriverCommon_DDIM_PRINT(("Configuration is not available.\n"));
		}
	}

	// INTx message ------------------------------------------------------------

	void PCIe_EP_Sample_INTx_message(DdPcieEp *self)
	{
		kint32 ret;
		kuint32 msg_f0_status;

		if(dd_pcie_ep_get_link_status() == TRUE){
			msg_f0_status = dd_pcie_ep_req_int_ep();
			if(msg_f0_status == 0){
				DriverCommon_DDIM_PRINT(("dd_pcie_ep_req_int_ep INTx Deassert\n"));
			}
			else{
				DriverCommon_DDIM_PRINT(("dd_pcie_ep_req_int_ep INTx Assert\n"));
			}
		}
		else{
			DriverCommon_DDIM_PRINT(("Configuration is not available.\n"));
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_EP_Sample_Interrupt	Sample of Interrupt.
	@code
	// Interrupt of INT_EP. -----------------------------------------------
	static void pcie_ep_int_ep_msg_unlock_cb(kint32 status)
	{
		// status = 0 (none)
	}

	static void pcie_ep_int_ep_pm_turnof_cb(kint32 status)
	{
		// status = 0 (none)
	}

	void PCIe_EP_Sample_INT_EP(DdPcieEp *self)
	{
		TDdPcieEpIntEpCb intEpCb;

		intEpCb.msg_unlock_cb = (VpCallbackPcieFunc)pcie_ep_int_ep_msg_unlock_cb;
		intEpCb.pmTurnofCb = (VpCallbackPcieFunc)pcie_ep_int_ep_pm_turnof_cb;
		dd_pcie_ep_set_int_ep_func(&intEpCb);
	}

	// Interrupt of INT_OWN.  ------------------------------------------
	static void pcie_ep_int_own_lu_cb(kint32 status)
	{
		// status = 0 (none)
	}
	static void pcie_ep_int_own_ce_cb(kint32 status)
	{
		// status = 0 (none)
	}
	static void pcie_ep_int_own_nfe_cb(kint32 status)
	{
		// status = 0 (none)
	}
	static void pcie_ep_int_own_fe_cb(kint32 status)
	{
		// status = 0 (none)
	}

	void PCIe_EP_Sample_INT_OWN(DdPcieEp *self)
	{
		TDdPcieEpIntOwnCb intOwnCb;

		intOwnCb.luCb = pcie_ep_int_own_lu_cb;
		intOwnCb.ceCb = pcie_ep_int_own_ce_cb;
		intOwnCb.nfeCb = pcie_ep_int_own_nfe_cb;
		intOwnCb.feCb = pcie_ep_int_own_fe_cb;
		dd_pcie_ep_set_int_own_func(&intOwnCb);
	}
	@endcode

	<br>
	<br>
	@section PCIe_EP_Sample_End		Sample of PCIe End.
	@code
	void PCIe_EP_Sample_End(DdPcieEp *self)
	{
		dd_pcie_ep_close();
		dd_pcie_ep_deinit();
	}
	@endcode

@}*/

