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
 * @file		ddpcierc.h
 * @brief		PCIe RootComplex driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
/**
@weakgroup dd_pcie_rc
@{

<hr>

@section dd_pcie_rc_sequence Sequence Chart
- @ref PCIe_RC_Sequence_Initialize
- @ref PCIe_RC_Sequence_Configuration
- @ref PCIe_RC_Sequence_Speed_Change
- @ref PCIe_RC_Sequence_Memory_Access
- @ref PCIe_RC_Sequence_DMA_Transfer
- @ref PCIe_RC_Sequence_MSI_Transfer
- @ref PCIe_RC_Sequence_ASPM
- @ref PCIe_RC_Sequence_PM_D1D2
- @ref PCIe_RC_Sequence_end
@section dd_pcie_rc_sample Sample Code
- @ref PCIe_RC_Sample_Initialize
- @ref PCIe_RC_Sample_Configuration
- @ref PCIe_RC_Sample_Speed_Change
- @ref PCIe_RC_Sample_Memory_Access
- @ref PCIe_RC_Sample_Demand_DMA_Transfer
- @ref PCIe_RC_Sample_LL_DMA_Transfer
- @ref PCIe_RC_Sample_ASPM
- @ref PCIe_RC_Sample_Interrupt
- @ref PCIe_RC_Sample_End
- @ref PCIe_RC_Sample_L2_Exit
- @ref PCIe_RC_Sample_Detect_Card

@section PCIe_RC_Sequence_Initialize	Initial setting.
@image html dd_pcie_rc_Initialize.png

@section PCIe_RC_Sequence_Configuration	Configuration access.
@image html dd_pcie_rc_configuration.png

@section PCIe_RC_Sequence_Speed_Change	Change of transfer speed.
@image html dd_pcie_rc_transfer_speed_change.png

@section PCIe_RC_Sequence_Memory_Access	Access to the memory of Endpoint side.
@image html dd_pcie_rc_memory.png

@section PCIe_RC_Sequence_DMA_Transfer	Data transfer by DMA.
@image html dd_pcie_rc_dma_transfer.png

@section PCIe_RC_Sequence_MSI_Transfer	MSI transfer.
@image html dd_pcie_rc_MSI_transfer.png

@section PCIe_RC_Sequence_ASPM			Control the power management by ASPM(Active State Power Management).
@image html dd_pcie_rc_ASPM.png

@section PCIe_RC_Sequence_PM_D1D2		Control the power management by software.
@image html dd_pcie_rc_PM_D1D2_by_SW.png

@section PCIe_RC_Sequence_end			PCIe end.
@image html dd_pcie_rc_end.png

@}
*/

/**
@addtogroup dd_pcie_rc
@{

*/


#ifndef __DD_PCIE_RC_H__
#define __DD_PCIE_RC_H__


#include <klib.h>
#include "driver_common.h"
#include "exstop.h"
#include "ddpciecomm.h"
#include "ddpciercint.h"

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

#define DD_TYPE_PCIE_RC                  (dd_pcie_rc_get_type())
#define DD_PCIE_RC(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdPcieRc))
#define DD_IS_PCIE_RC(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DD_TYPE_PCIE_RC))

#define C_PCIE_RC_MAX_CH		(2)		/**< The maximum number of channels */


typedef enum _DdPcieHotPlugSt DdPcieHotPlugSt;

/** Hot-Plug Status */
enum _DdPcieHotPlugSt
{
	DdPcieRc_PCIE_HOT_PLUG_ST_ABP = 0, /**< Attention Button Pressed		*/
	DdPcieRc_PCIE_HOT_PLUG_ST_PFD, /**< Power Fault Detected			*/
	DdPcieRc_PCIE_HOT_PLUG_ST_MRLSC, /**< MRL Sensor Changed				*/
	DdPcieRc_PCIE_HOT_PLUG_ST_PDC, /**< Presence Detect Changed		*/
	DdPcieRc_PCIE_HOT_PLUG_ST_CC, /**< Command Completed				*/
	DdPcieRc_PCIE_HOT_PLUG_ST_DLLSC /**< Data Link Layer State Change	*/
};


typedef struct _DdPcieRc DdPcieRc;
typedef struct _DdPcieRcPrivate DdPcieRcPrivate;

//T_DD_PCIE_RC_CTRL_CFG修改为DdPcieRcCtrlCfg，将此结构体放入类结构体中
struct _DdPcieRc
{
	KObject parent;
	DdPcieCh ch; /**< PCIe channel			*/
	kuint32 baseAdr; /**< Lower base address		*/
	kuint32 limitAdr; /**< limit address			*/
};


KConstType		dd_pcie_rc_get_type(void);
DdPcieRc*		dd_pcie_rc_new(void);
/**
Initialize PCIe Root Complex.<br>
@param[in]	bifurcation		See @ref DdPcieBifurcation.
*/
void				dd_pcie_rc_init1(DdPcieRc *self, DdPcieBifurcation bifurcation);

/**
PCIe end.<br>
*/
void				dd_pcie_rc_deinit(DdPcieRc *self);

/**
Execute exclusive control for PCIe channel.<br>
@param [in]	tmout	Time of timeout<br>
						<ul><li>Positive Value(Time of timeout)
							<li>@ref D_DDIM_USER_SEM_WAIT_POL
							<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
@retval D_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Input parameter error.
@retval D_DD_PCIE_SEM_TIMEOUT		Semaphore acquisition Time Out.
@retval D_DD_PCIE_SEM_NG			Semaphore acquisition NG.
@remarks This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
		 This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
kint32				dd_pcie_rc_open(DdPcieRc *self, kint32 tmout);

/**
Cancel exclusive control for PCIe channel.<br>
@retval D_DDIM_OK			OK
@retval D_DD_PCIE_SEM_NG	Semaphore release NG.
@remarks This API uses DDIM_User_Sig_Sem().
*/
kint32				dd_pcie_rc_close(DdPcieRc *self);

/**
Get PCIe link status.<br>
@param[in]	ch	Pcie channel.	See @ref DdPcieCh.
@retval TRUE	link up
@retval FALSE	link down
@remarks In the case of bifurcation disable, ch1 can not be used.
*/
kboolean				dd_pcie_rc_get_link_status(DdPcieRc *self, DdPcieCh ch);

/**
It will be setting up the transfer of config.<br>
@param[in]	self			config control data. See @ref DdPcieRc.
@retval D_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Input parameter error.
@retval C_PCIE_COMM_ERROR		Communication error. (Not link up)
@remarks In the case of bifurcation disable, ch1 can not be used.
*/
kint32				dd_pcie_rc_ctrl_config(DdPcieRc const* const self);

/**
It will be setting up the dma transfer.<br>
@param[in]	pcieCtrlDma	dma control data.	See @ref DdPcieCtrlDma.
@retval D_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Input parameter error.
@retval C_PCIE_ACCESS_ERR		PCIe power down.(dd_pcie_rc_init1 unexecution)
@remarks
	- With the function for the opposing device to make the memory light a trigger and
	to generate interrupt, DMA Remote Interrupt can be used. <br>
	- In the case of bifurcation disable, ch1 can not be used.
*/
kint32				dd_pcie_rc_ctrl_dma(DdPcieRc *self, DdPcieCtrlDma const* const pcieCtrlDma);

/**
Start DMA.<br>
@param[in]	ch		Pcie channel.	See @ref DdPcieCh.
@param[in]	dmaCh	Dma channel.	See @ref DdPcieDmaCh.
@param[in]	dir		Direction.		See @ref DdPcieDmaDir.
@retval D_DDIM_OK					OK
@retval C_PCIE_ACCESS_ERR		PCIe power down.(dd_pcie_rc_init1 unexecution)
@remarks In the case of bifurcation disable, ch1 can not be used.
*/
kint32				dd_pcie_rc_start_dma(DdPcieRc *self, DdPcieCh ch, DdPcieDmaCh dmaCh,
							DdPcieDmaDir dir);

/**
Stop DMA.<br>
@param[in]	ch		Pcie channel.	See @ref DdPcieCh.
@param[in]	dmaCh	Dma channel.	See @ref DdPcieDmaCh.
@param[in]	dir		Direction.		See @ref DdPcieDmaDir.
@retval D_DDIM_OK					OK
@retval C_PCIE_ACCESS_ERR		PCIe power down.(dd_pcie_rc_init1 unexecution)
@remarks In the case of bifurcation disable, ch1 can not be used.
*/
kint32				dd_pcie_rc_stop_dma(DdPcieRc *self, DdPcieCh ch, DdPcieDmaCh dmaCh,
							DdPcieDmaDir dir);

/**
It will be setting up the transfer of memory. CPU transfer.<br>
@param[in]	pcieCtrlMem			memory control data. See @ref DdPcieCtrlMem.
@retval D_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Input parameter error.
@retval C_PCIE_COMM_ERROR		Communication error. (Not link up)
@remarks 
			- Please use by Link Up state.
			- In the case of bifurcation disable, ch1 can not be used.
*/
kint32				dd_pcie_rc_ctrl_memory(DdPcieRc *self, DdPcieCtrlMem const* const pcieCtrlMem);

/**
Interrupt handler for PCIe ch0 own.<br>
*/
void				dd_pcie_rc_ch0_int_own_handler(DdPcieRc *self);

/**
Interrupt handler for PCIe ch0 endpoint.<br>
*/
void				dd_pcie_rc_ch0_int_ep_handler(DdPcieRc *self);

/**
ASPM control.
@param[in]	ch				Pcie channel.	See @ref DdPcieCh.
@param[in]	aspmControl	ASPM control.	See @ref DdPcieAspmControl.
@retval D_DDIM_OK					OK
@retval C_PCIE_ACCESS_ERR		Power status not D0.<br>
									Link status not L0/L0s/L1.
@remarks In the case of bifurcation disable, ch1 can not be used.
*/
kint32				dd_pcie_rc_ctrl_aspm(DdPcieRc *self, DdPcieCh ch, DdPcieAspmControl aspmControl);

/**
Power Turn Off Request. (L2 Entry)
@param[in]	ch	Pcie channel. See @ref DdPcieCh.
@retval D_DDIM_OK					OK
@retval C_PCIE_ACCESS_ERR		Link status is not L0.
@remarks In the case of bifurcation disable, ch1 can not be used.
*/
kint32				dd_pcie_rc_pm_pw_turn_off_req(DdPcieRc *self, DdPcieCh ch);

/**
Power L2 Exit. (L0 Entry)
@param[in]	ch	Pcie channel. See @ref DdPcieCh.
@retval D_DDIM_OK					OK
@retval C_PCIE_ACCESS_ERR		Link status is not L2.
@remarks In the case of bifurcation disable, ch1 can not be used.
*/
kint32				dd_pcie_rc_pm_pw_l2_exit(DdPcieRc *self, DdPcieCh ch);

/**
Get PCIe Power status.
@param[in]	ch	Pcie channel. See @ref DdPcieCh.
@retval See @ref DdPciePmst.
@remarks In the case of bifurcation disable, ch1 can not be used.
*/
DdPciePmst	dd_pcie_rc_get_pmst_status(DdPcieRc *self, DdPcieCh ch);

/**
Get PCIe LTSSM status.
@param[in]	ch	Pcie channel. See @ref DdPcieCh.
@retval See @ref DdPcieStLtssm.
@remarks In the case of bifurcation disable, ch1 can not be used.
*/
DdPcieStLtssm	dd_pcie_rc_get_st_ltssm_status(DdPcieRc *self, DdPcieCh ch);

/**
Transfer speed change.
@param[in]	ch	Pcie channel. See @ref DdPcieCh.
@param[in]	linkSpeed	Link Speed. See @ref DdPcieLinkSpeed.
@retval D_DDIM_OK					OK
@retval C_PCIE_ACCESS_ERR		Link status not L0/L0s/L1.
@remarks
		- If the opposing device supports  5.0GT/s, function can use.<br>
*/
kint32				dd_pcie_rc_transfer_speed_change(DdPcieRc *self, DdPcieCh ch, DdPcieLinkSpeed linkSpeed);

/**
Get current link speed.
@param[in]	ch	Pcie channel. See @ref DdPcieCh.
@param[in]	currentLinkSpeed	Current link speed. See @ref DdPcieLinkSpeed.
@retval D_DDIM_OK				OK
@retval C_PCIE_ACCESS_ERR	PCIe power down. (dd_pcie_rc_init1 unexecution)
*/
kint32				dd_pcie_rc_get_current_link_speed(DdPcieRc *self, DdPcieCh ch,
							DdPcieLinkSpeed* currentLinkSpeed);

/**
Get ASPM status.
@param[in]	ch			Pcie channel. See @ref DdPcieCh.
@param[in]	aspmStatus	ASPM status. See @ref DdPcieAspmControl.
@retval D_DDIM_OK				OK
@retval C_PCIE_ACCESS_ERR	PCIe power down. (dd_pcie_rc_init1 unexecution)
*/
kint32				dd_pcie_rc_get_aspm_status(DdPcieRc *self, DdPcieCh ch, DdPcieAspmControl* aspmStatus);

/**
Read the config read register.
@param[in]	ch		Pcie channel. See @ref DdPcieCh.
@param[in]	offset	Offset of the read config register.
@param[in]	data	Read data.
@retval D_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	address word boundary violation.
@retval C_PCIE_COMM_ERROR		Communication error. (Not link up)
*/
kint32				dd_pcie_rc_config_read(DdPcieRc *self, DdPcieCh ch, kuint16 offset, kuint32* data);

/**
Write the config read register.
@param[in]	ch		Pcie channel. See @ref DdPcieCh.
@param[in]	offset	Offset of the write config register.
@param[in]	data	Write data.
@retval D_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	address word boundary violation.
@retval C_PCIE_COMM_ERROR		Communication error. (Not link up)
*/
kint32				dd_pcie_rc_config_write(DdPcieRc *self, DdPcieCh ch, kuint16 offset, kuint32 data);

/**
It will be setting up Detect Card.
@param[in]	ch			Pcie channel. See @ref DdPcieCh.
@param[in]	callback	callback function.
@retval D_DDIM_OK		OK
@remarks
			- Value of callback argument. 0:Insert , 1:Eject
*/
kint32				dd_pcie_rc_ctrl_detect_card(DdPcieRc *self, DdPcieCh ch, vpCallbackPcieFunc callback);

/**
Set max payload size.
@param[in]	ch		Pcie channel. See @ref DdPcieCh.
@param[in]	mps		Max Payload Size. See @ref DdPcieMps.
@retval D_DDIM_OK				OK
@retval C_PCIE_ACCESS_ERR	PCIe power down. (dd_pcie_rc_init1 unexecution)
*/
kint32				dd_pcie_rc_set_mps(DdPcieRc *self, DdPcieCh ch, DdPcieMps mps);

/**
Get max payload size.
@param[in]	ch		Pcie channel. See @ref DdPcieCh.
@param[out]	mps		Max Payload Size. See @ref DdPcieMps.
@retval D_DDIM_OK				OK
@retval C_PCIE_ACCESS_ERR	PCIe power down. (dd_pcie_rc_init1 unexecution)
*/
kint32				dd_pcie_rc_get_mps(DdPcieRc *self, DdPcieCh ch, DdPcieMps* mps);

#ifdef CO_DDIM_UTILITY_USE
/** @name Utility Functions
@{*/
//---------------------- utility section -------------------------------
/**
Get EXSTOP PCIe register.
@param[in]	ch		Pcie channel. See @ref DdPcieCh.
@param[in]	offset	Offset of EXSTOP PCIe register.
@param[out]	data	Get data.
@retval D_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Violation of word boundary or reservation register.
@retval C_PCIE_ACCESS_ERR		PCIe power down. (dd_pcie_rc_init1 unexecution)
*/
kint32				dd_pcie_rc_get_exs_reg(DdPcieRc *self, DdPcieCh ch, kuint16 offset, kuint32* data);

/**
Set EXSTOP PCIe register.
@param[in]	ch		Pcie channel. See @ref DdPcieCh.
@param[in]	offset	Offset of EXSTOP PCIe register.
@param[in]	data	Set data.
@retval D_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Violation of word boundary or reservation register.
@retval C_PCIE_ACCESS_ERR		PCIe power down. (dd_pcie_rc_init1 unexecution)
*/
kint32				dd_pcie_rc_set_exs_reg(DdPcieRc *self, DdPcieCh ch, kuint16 offset, kuint32 data);

/**
Get DBI AXI Slave register.
@param[in]	ch		Pcie channel. See @ref DdPcieCh.
@param[in]	offset	Offset of DBI AXI Slave register.
@param[out]	data	Get data.
@retval D_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Violation of word boundary or reservation register.
@retval C_PCIE_ACCESS_ERR		PCIe power down. (dd_pcie_rc_init1 unexecution)
*/
kint32				dd_pcie_rc_get_dbi_reg(DdPcieRc *self, DdPcieCh ch, kuint16 offset, kuint32* data);

/**
Set DBI AXI Slave register.
@param[in]	ch		Pcie channel. See @ref DdPcieCh.
@param[in]	offset	Offset of DBI AXI Slave register.
@param[out]	data	Set data.
@retval D_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Violation of word boundary or reservation register.
@retval C_PCIE_ACCESS_ERR		PCIe power down. (dd_pcie_rc_init1 unexecution)
*/
kint32				dd_pcie_rc_set_dbi_reg(DdPcieRc *self, DdPcieCh ch, kuint16 offset, kuint32 data);

/**
Set write access to DBI read-only register.
@param[in]	ch	Pcie channel. See @ref DdPcieCh.
@param[in]	access	DBI Read only register access mode. (TRUE:access, FALSE:not access)
@retval D_DDIM_OK				OK
@retval C_PCIE_ACCESS_ERR	PCIe power down.(dd_pcie_rc_init1 unexecution)<br>
								It is not possible to access it because of Link up.
*/
kint32				dd_pcie_rc_set_wr_acc_to_ro_reg(DdPcieRc *self, DdPcieCh ch, kboolean access);

//---------------------- colabo  section -------------------------------
// Nothing Special
/*  @}*/
#endif

/*@}*/

/**
@weakgroup dd_pcie_rc
@{

	<br>
	<br>
	The example of PCIe is as follows.<br>
	Sample code, use the PCIE to the opposing device.
	<hr>
	@section PCIe_RC_Sample_Initialize	Sample of Initialize. (Bifurcation Disable)
	@code
	static void pcie_rc_link_up_cb(kint32 status)
	{
		Ddim_Print(("Link Up.\n"));
	}

	void PCIe_RC_Sample_Initialize(void)
	{
		kint32 ret;
		T_DD_PCIE_INIT_CONF pcie_init_conf;
		DdPciRcIntOwnCb int_own_cb

		memset(&int_own_cb, 0, sizeof(int_own_cb));
		int_own_cb.rdlhLinkUpCb = (vpCallbackPcieFunc)pcie_rc_link_up_cb;
		dd_pcie_rc_int_set_int_own_func(NULL, E_DD_PCIE_CH0, &int_own_cb);

		ret = dd_pcie_rc_init1(NULL, E_DD_PCIE_BIFURCATION_DISABLE);
		if(ret != D_DDIM_OK){
			Ddim_Print(("dd_pcie_rc_init1 Error. ret=0x%08x\n", ret));
			return;
		}

		ret = dd_pcie_rc_open(NULL, D_DDIM_USER_SEM_WAIT_POL);
		if(ret != D_DDIM_OK){
			Ddim_Print(("dd_pcie_rc_open Error. ret=0x%08x\n", ret));
			return;
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_RC_Sample_Configuration	Sample of Configuration.
	@code
	void PCIe_RC_Sample_Configuration(void)
	{
		kint32 ret;
		DdPcieRc self;

		if(dd_pcie_rc_get_link_status(NULL, E_DD_PCIE_CH0) == TRUE){
			memset(&self, 0, sizeof(self));
			self.ch				= E_DD_PCIE_CH0;
			self.baseAdr			= 0x19400000;
			self.limitAdr			= 0x1940ffff;
			ret = dd_pcie_rc_ctrl_config(&self);	// ch0 configration
			if(ret == D_DDIM_OK){
				Ddim_Print(("Configuration success.\n"));
			}
			else{
				Ddim_Print(("dd_pcie_rc_ctrl_config Error. ret=0x%08x\n", ret));
			}
		}
		else{
			Ddim_Print(("Configuration is not available.\n"));
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_RC_Sample_Speed_Change	Sample of transfer speed change.
	@code
	void PCIe_RC_Sample_Speed_Change(void)
	{
		kint32 ret;
		DdPcieLinkSpeed tran_speed_stat;

		if(dd_pcie_rc_get_link_status(NULL, E_DD_PCIE_CH0) == TRUE){
			ret = dd_pcie_rc_transfer_speed_change(NULL, E_DD_PCIE_CH0, E_DD_PCIE_LINK_SPEED_GEN2);	// GEN1(2.5GT/s) -> GEN2(5.0GT/s)
			if(ret == D_DDIM_OK){
				Ddim_Print(("Current Link Speed. %d\n", dd_pcie_rc_get_current_link_speed(NULL, E_DD_PCIE_CH0)));
			}
			else{
				Ddim_Print(("dd_pcie_rc_transfer_speed_change Error. ret=0x%08x\n", ret));
			}
		}
		else{
			Ddim_Print(("Transfer speed change is not available.\n"));
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_RC_Sample_Memory_Access	Sample of memory access.
	@code
	void PCIe_RC_Sample_Memory_Access(void)
	{
		kint32 ret;
		DdPcieCtrlMem pcieCtrlMem;

		if(dd_pcie_rc_get_link_status(NULL, E_DD_PCIE_CH0) == TRUE){
			memset(&pcieCtrlMem, 0, sizeof(pcieCtrlMem));
			pcieCtrlMem.ch				= E_DD_PCIE_CH0;
			pcieCtrlMem.baseAdr			= 0x19600000;
			pcieCtrlMem.limitAdr			= 0x1960ffff;
			pcieCtrlMem.lowTargetAdr	= 0x58000000;
			ret = dd_pcie_rc_ctrl_memory(NULL, &pcieCtrlMem);
			if(ret == D_DDIM_OK){
				memcpy((void*)0x0x19600000, "PCIe Start 1", 12);
				DDIM_User_L1l2cache_Clean_Flush_Addr(0x0x19600000, 12);
			}
			else{
				Ddim_Print(("dd_pcie_rc_ctrl_memory Error. ret=0x%08x\n", ret));
			}
		}
		else{
			Ddim_Print(("Memory access is not available.\n"));
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_RC_Sample_Demand_DMA_Transfer	Sample of Demand mode DMA transfer.
	@code
	static void pcie_rc_int_dma_cb(kint32 status)
	{
		// status
		// 0x00000001  Done Interrupt status(DMA ch0)
		// 0x00000002  Done Interrupt status(DMA ch1)
		// 0x00010000  Abort Interrupt status(DMA ch0)
		// 0x00020000  Abort Interrupt status(DMA ch1)
	}

	void PCIe_RC_Sample_Demand_DMA_Transfer(void)
	{
		kint32 ret;
		DdPcieCtrlDma pcieCtrlDma;

		memset(&pcieCtrlDma, 0, sizeof(pcieCtrlDma));
		pcieCtrlDma.mode				= E_DD_PCIE_DMA_DEMAND;
		pcieCtrlDma.ch				= E_DD_PCIE_CH0;
		pcieCtrlDma.dmaCh			= E_DD_PCIE_DMA_CH0;
		pcieCtrlDma.dmnd_src_addr		= 0x58000000;
		pcieCtrlDma.dmndDstAddrL	= 0x5F000000;
		pcieCtrlDma.dmnd_trans_size	= 0x3FC000;
		pcieCtrlDma.direction			= E_DD_PCIE_DMA_DIR_STOD;
		pcieCtrlDma.int_dma_callback	= (vpCallbackPcieFunc)pcie_rc_int_dma_cb;
		ret = dd_pcie_rc_ctrl_dma(NULL, &pcieCtrlDma);
		if(ret == D_DDIM_OK){
			dd_pcie_rc_start_dma(NULL, pcieCtrlDma.ch, pcieCtrlDma.direction);
		}
		else{
			Ddim_Print(("dd_pcie_rc_ctrl_dma Error. ret=0x%08x\n", ret));
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_RC_Sample_LL_DMA_Transfer	Sample of Linked List mode DMA Transfer.
	@code

	#define PCIE_DMA_LL_ADDR	(0x55000000)

	static void pcie_rc_ll_dma(void)
	{
		kuint32 Linked_list[22];

		Linked_list[0]	= 0x00000001;	// Channel Control
		Linked_list[1]	= 0x00000004;	// Transfer Size
		Linked_list[2]	= 0x58000000;	// SAR Low
		Linked_list[3]	= 0x0;			// SAR High
		Linked_list[4]	= 0x5F000000;	// DAR Low
		Linked_list[5]	= 0x0;			// DAR High
		// Element 1
		Linked_list[6]	= 0x00000001;	// Channel Control
		Linked_list[7]	= 0x00000004;	// Transfer Size
		Linked_list[8]	= 0x58000004;	// SAR Low
		Linked_list[9]	= 0x0;			// SAR High
		Linked_list[10]	= 0x5F000004;	// DAR Low
		Linked_list[11]	= 0x0;			// DAR High
		// Element 2
		Linked_list[12]	= 0x00000009;	// Channel Control (Local Interrupt Enable)
		Linked_list[13]	= 0x00000004;	// Transfer Size
		Linked_list[14]	= 0x58000008;	// SAR Low
		Linked_list[15]	= 0x0;			// SAR High
		Linked_list[16]	= 0x5F000008;	// DAR Low
		Linked_list[17]	= 0x0;			// DAR High
		// Element 3
		Linked_list[18]	= 0x00000004;	// Channel Control (Linked List End)
		Linked_list[19]	= 0x0;
		Linked_list[20]	= 0x0;
		Linked_list[21]	= 0x0;

		memcpy((void*)PCIE_DMA_LL_ADDR, (void*)Linked_list, sizeof(Linked_list));
		DDIM_User_L1l2cache_Clean_Flush_Addr(PCIE_DMA_LL_ADDR, sizeof(Linked_list));
	}

	void PCIe_RC_Sample_LL_DMA_Transfer(void)
	{
		kint32 ret;
		DdPcieCtrlDma pcieCtrlDma;

		pcie_rc_ll_dma();
		memset(&pcieCtrlDma, 0, sizeof(pcieCtrlDma));
		pcieCtrlDma.mode				= E_DD_PCIE_DMA_LL_MODE;
		pcieCtrlDma.ch				= E_DD_PCIE_CH0;
		pcieCtrlDma.dmaCh			= E_DD_PCIE_DMA_CH0;
		pcieCtrlDma.llAddr			= PCIE_DMA_LL_ADDR;
		pcieCtrlDma.direction			= E_DD_PCIE_DMA_DIR_STOD;
		pcieCtrlDma.int_dma_callback	= (vpCallbackPcieFunc)pcie_rc_int_dma_cb;
		ret = dd_pcie_rc_ctrl_dma(NULL, &pcieCtrlDma);
		if(ret == D_DDIM_OK){
			dd_pcie_rc_start_dma(NULL, pcieCtrlDma.ch, pcieCtrlDma.direction);
		}
		else{
			Ddim_Print(("dd_pcie_rc_ctrl_dma Error. ret=0x%08x\n", ret));
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_RC_Sample_ASPM	Sample of ASPM.
	@code
	void PCIe_RC_Sample_ASPM(void)
	{
		kint32 ret;
		DdPcieStLtssm st_ltssm;

		if(dd_pcie_rc_get_link_status(NULL, E_DD_PCIE_CH0) == TRUE){
			ret = dd_pcie_rc_ctrl_aspm(NULL, E_DD_PCIE_CH0, E_DD_PCIE_ASPM_CONTROL_L0S_L1);
			if(ret == D_DDIM_OK){
				Ddim_Print(("dd_pcie_rc_ctrl_aspm OK.\n"));
			}
			else{
				Ddim_Print(("dd_pcie_rc_ctrl_aspm Error. ret=0x%08x\n", ret));
			}
		}
		else{
			Ddim_Print(("ASPM is not available.\n"));
		}
	}
	@endcode

	<br>
	<br>
	@section PCIe_RC_Sample_Interrupt	Sample of Interrupt.
	@code
	// Interrupt of INT_OWN. ---------------------------------------------------
	static void pcie_rc_int_own_pme_cb(kint32 status)
	{
		// status = 0 (none)
	}

	static void pcie_rc_int_own_hp_cb(kint32 status)
	{
		// status
		//	DdPcieRc_PCIE_HOT_PLUG_ST_ABP		Attention Button Pressed
		//	DdPcieRc_PCIE_HOT_PLUG_ST_PFD		Power Fault Detected
		//	DdPcieRc_PCIE_HOT_PLUG_ST_MRLSC		MRL Sensor Changed
		//	DdPcieRc_PCIE_HOT_PLUG_ST_CC		Command Completed
		//	DdPcieRc_PCIE_HOT_PLUG_ST_DLLSC		Data Link Layer State Change
	}

	static void pcie_rc_int_own_link_up_cb(kint32 status)
	{
		// status = 0 (none)
	}

	static void pcie_rc_int_own_wake_cb(kint32 status)
	{
		// status = 0 (none)
	}

	void PCIe_RC_Sample_INT_OWN(void)
	{
		DdPciRcIntOwnCb int_own_cb;

		int_own_cb.cfgPmeCb		= (vpCallbackPcieFunc)pcie_rc_int_own_pme_cb;
		int_own_cb.hpCb			= (vpCallbackPcieFunc)pcie_rc_int_own_hp_cb;
		int_own_cb.rdlhLinkUpCb	= (vpCallbackPcieFunc)pcie_rc_int_own_link_up_cb;
		int_own_cb.wakeCb			= (vpCallbackPcieFunc)pcie_rc_int_own_wake_cb;
		dd_pcie_rc_int_set_int_own_func(NULL, E_DD_PCIE_CH0, &int_own_cb);
	}

	// Interrupt of INT_EP. ----------------------------------------------------
	static void pcie_rc_int_ep_intx_cb(kint32 status)
	{
		// status = 0
		//	1  INTA
		//	2  INTB
		//	4  INTC
		//	8  INTD
	}

	static void pcie_rc_int_ep_pm_pme_cb(kint32 status)
	{
		// status = 0 (none)
	}

	static void pcie_rc_int_ep_correctable_err_cb(kint32 status)
	{
		// status = 0 (none)
	}

	static void pcie_rc_int_ep_nonfatal_err_cb(kint32 status)
	{
		// status = 0 (none)
	}

	static void pcie_rc_int_ep_fatal_err_cb(kint32 status)
	{
		// status = 0 (none)
	}

	static void pcie_rc_int_ep_msg_ltr_cb(kint32 status)
	{
		// status = 0 (none)
	}

	static void pcie_rc_int_ep_pm_to_ack_cb(kint32 status)
	{
		// status = 0 (none)
	}

	static void pcie_rc_int_ep_vendor_msg_cb(kint32 status)
	{
		// status = 0 (none)
	}

	void PCIe_RC_Sample_INT_EP(void)
	{
		DdPcieRcIntEpCb int_own_cb;

		int_ep_cb.radmIntxCb				= (vpCallbackPcieFunc)pcie_rc_int_ep_intx_cb;
		int_ep_cb.radmPmPmeCb			= (vpCallbackPcieFunc)pcie_rc_int_ep_pm_pme_cb;
		int_ep_cb.radmCorrectableErrCb	= (vpCallbackPcieFunc)pcie_rc_int_ep_correctable_err_cb;
		int_ep_cb.radmNonfatalErrCb		= (vpCallbackPcieFunc)pcie_rc_int_ep_nonfatal_err_cb;
		int_ep_cb.radmFatalErrCb			= (vpCallbackPcieFunc)pcie_rc_int_ep_fatal_err_cb;
		int_ep_cb.radmMsgLtrCb			= (vpCallbackPcieFunc)pcie_rc_int_ep_msg_ltr_cb;
		int_ep_cb.radmPmToAckCb			= (vpCallbackPcieFunc)pcie_rc_int_ep_pm_to_ack_cb;
		int_ep_cb.radmVendorMsgCb		= (vpCallbackPcieFunc)pcie_rc_int_ep_vendor_msg_cb;
		dd_pcie_rc_int_set_int_ep_func(NULL, E_DD_PCIE_CH0, &int_ep_cb);
	}

	// Interrupt of INT_SYS_ERR. -----------------------------------------------
	static void pcie_rc_int_aer_rc_err_cb(kint32 status)
	{
		// status = 0 (none)
		//	0x01	Correctable Error Received
		//	0x02	Multiple Correctable Errors Received
		//	0x04	Fatal or Non-Fatal Error Received
		//	0x08	Multiple Fatal or Non-Fatal Errors Received
		//	0x10	First Uncorrectable Error is Fatal
		//	0x20	One or more Non-Fatal Error Messages Received
		//	0x40	One or more Fatal Error Messages Received
	}

	static void pcie_rc_int_sys_err_rc_cb(kint32 status)
	{
		// status = 0 (none)
	}

	void PCIe_RC_Sample_INT_SYS_ERR(void)
	{
		DdPcieRcIntSysErrCb sys_err_cb;

		sys_err_cb.cfgAerRcErrCb	= (vpCallbackPcieFunc)pcie_rc_int_aer_rc_err_cb;
		sys_err_cb.cfgSysErrRcCb	= (vpCallbackPcieFunc)pcie_rc_int_sys_err_rc_cb;
		dd_pcie_rc_int_set_int_sys_err_func(NULL, E_DD_PCIE_CH0, &sys_err_cb);
	}

	// Interrupt of INT_TRS_ICS_MSI. -------------------------------------------
	static void pcie_rc_int_cfg_link_auto_bw_int_cb(kint32 status)
	{
		// status = 0 (none)
	}

	static void pcie_rc_int_cfg_bw_mgt_int_cb(kint32 status)
	{
		// status = 0 (none)
	}

	static void pcie_rc_int_smlh_req_rst_not_cb(kint32 status)
	{
		// status = 0 (none)
	}

	void PCIe_RC_Sample_INT_TRS_ICS_MSI(void)
	{
		DdPcieRcIntTrsIcsMsiCb int_trs_ics_msi_cb;

		int_trs_ics_msi_cb.cfgLinkAutoBwIntCb	= (vpCallbackPcieFunc)pcie_rc_int_cfg_link_auto_bw_int_cb;
		int_trs_ics_msi_cb.cfgBwMgtIntCb		= (vpCallbackPcieFunc)pcie_rc_int_cfg_bw_mgt_int_cb;
		int_trs_ics_msi_cb.smlhReqRstNotCb		= (vpCallbackPcieFunc)pcie_rc_int_smlh_req_rst_not_cb;
		dd_pcie_rc_int_set_int_sys_err_func(NULL, E_DD_PCIE_CH0, &int_trs_ics_msi_cb);
	}

	@endcode

	<br>
	<br>
	@section PCIe_RC_Sample_End		Sample of PCIe End.
	@code
	void PCIe_RC_Sample_End(void)
	{
		dd_pcie_rc_close(NULL);
		dd_pcie_rc_deinit();
	}
	@endcode

	<br>
	<br>
	@section PCIe_RC_Sample_L2_Exit		Sample of L2 Exit.
	@code
	void PCIe_RC_Sample_End(void)
	{
		dd_pcie_rc_pm_pw_l2_exit(NULL, E_DD_PCIE_CH0);
		dd_pcie_rc_close(NULL);
		dd_pcie_rc_deinit(NULL);
	}
	@endcode

	<br>
	<br>
	@section PCIe_RC_Sample_Detect_Card		Sample of Detect Card.
	@code
	static void pcie_rc_detect_card_cb(kint32 status)
	{
		// status
		// 0  Insert
		// 1  Eject
	}

	void PCIe_RC_Sample_Detect_Card(void)
	{
		Dd_Pcie_Rc_Ctrl_Hp_Detect_Card(E_DD_PCIE_CH0, (vpCallbackPcieFunc)pcie_rc_detect_card_cb);
	}
	@endcode

@}*/

#ifdef __cplusplus
}
#endif

#endif /* __DD_PCIE_RC_H__ */
