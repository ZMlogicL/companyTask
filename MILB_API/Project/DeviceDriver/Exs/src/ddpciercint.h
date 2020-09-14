/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 王顺
*@brief : DdPcieRcInt
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __DD_PCIE_RC_INT_H__
#define __DD_PCIE_RC_INT_H__


#include <klib.h>
#include "ddpcierc.h"

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

#define DD_TYPE_PCIE_RC_INT                  (dd_pcie_rc_int_get_type())
#define DD_PCIE_RC_INT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdPcieRcInt))
#define DD_IS_PCIE_RC_INT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DD_TYPE_PCIE_RC_INT))


typedef struct _DdPcieRcInt DdPcieRcInt;
typedef struct _DdPcieRcIntEpCb  DdPcieRcIntEpCb;
typedef struct _DdPcieRcIntSysErrCb  DdPcieRcIntSysErrCb;
typedef struct _DdPciRcIntOwnCb  DdPciRcIntOwnCb;
typedef struct _DdPcieRcIntTrsIcsMsiCb DdPcieRcIntTrsIcsMsiCb;

/** PCIe interrupt EP callback */
struct _DdPcieRcIntEpCb
{
	VpCallbackPcieFunc radmIntxCb; /**< Callback of radm_inta/b/c/d port interrupt			*/
	VpCallbackPcieFunc radmPmPmeCb; /**< Callback of radm_pm_pme port interrupt				*/
	VpCallbackPcieFunc radmCorrectableErrCb; /**< Callback of radm_correctable_err port interrupt	*/
	VpCallbackPcieFunc radmNonfatalErrCb; /**< Callback of radm_nonfatal_err port interrupt		*/
	VpCallbackPcieFunc radmFatalErrCb; /**< Callback of radm_fatal_err port interrupt			*/
	VpCallbackPcieFunc radmMsgLtrCb; /**< Callback of radm_msg_ltr port interrupt			*/
	VpCallbackPcieFunc radmPmToAckCb; /**< Callback of radm_pm_to_ack port interrupt			*/
	VpCallbackPcieFunc radmVendorMsgCb; /**< Callback of radm_vendor_msg port interrupt			*/
};

/** PCIe interrupt system error callback. */
struct _DdPcieRcIntSysErrCb
{
	VpCallbackPcieFunc cfgAerRcErrCb; /**< Callback of cfg_aer_rc_err_int/msi port interrupt	*/
	VpCallbackPcieFunc cfgSysErrRcCb; /**< Callback of cfg_sys_err_rc port interrupt			*/
};

/** PCIe interrupt own callback. */
struct _DdPciRcIntOwnCb
{
	VpCallbackPcieFunc cfgPmeCb; /**< Callback of cfg_pme_int/msi port interrupt		*/
	VpCallbackPcieFunc hpCb; /**< Callback of hp_pme/int/msi port interrupt		*/
	VpCallbackPcieFunc rdlhLinkUpCb; /**< Callback of rdlh_link_up port interrupt		*/
	VpCallbackPcieFunc wakeCb; /**< Callback of wake port interrupt				*/
};

/** PCIe interrupt trs_ics_msi callback */
struct _DdPcieRcIntTrsIcsMsiCb
{
	VpCallbackPcieFunc cfgLinkAutoBwIntCb; /**< Callback of cfg_link_auto_bw_int port interrupt	*/
	VpCallbackPcieFunc cfgBwMgtIntCb; /**< Callback of cfg_bw_mgt_int port interrupt			*/
	VpCallbackPcieFunc smlhReqRstNotCb; /**< Callback of smlh_req_rst_not port interrupt		*/
};


typedef struct _DdPcieRcInt DdPcieRcInt;
typedef struct _DdPcieRcIntPrivate DdPcieRcIntPrivate;

//T_DD_PCIE_RC_CTRL_MSI修改为DdPcieRcCtrlMsi，将此结构体放入类结构体中
struct _DdPcieRcInt
{
	KObject parent;
	DdPcieCh ch; /**< PCIe channel			*/
	kuint32 intEn; /**< Interrupt enable		*/
	kuint32 cmpAdr; /**< compare address	*/
	VpCallbackPcieFunc intMsiCb; /**< MSI callback	*/
};


KConstType		dd_pcie_rc_int_get_type(void);
DdPcieRcInt*	dd_pcie_rc_int_new(void);
/**
It will be setting up the interrupt MSI.<br>
@param[in]	pcieCtrlMsi	msi control data. See @ref DdPcieRcInt.
@retval D_DDIM_OK					OK
@retval C_PCIE_INPUT_PARAM_ERROR	Input parameter error.
@retval C_PCIE_ACCESS_ERR		PCIe power down.(dd_pcie_rc_init1 unexecution)
@remarks
			- Please use by Link Up state.
			- In the case of bifurcation disable, ch1 can not be used.
*/
kint32				dd_pcie_rc_ctrl_msi(DdPcieRcInt const* const self);
/**
Set the function to call back when INT_OWN interrupt occurs.
@param[in]	ch			Pcie channel. See @ref DdPcieCh.
@param [in] intOwnCb	callback function table. See @ref DdPciRcIntOwnCb.
@retval D_DDIM_OK	OK
@remarks
			- The lu_cb setting in Link up is invalid.
			- When dd_pcie_rc_init1 is unexecution, fg_pme_cb/hpCb/wake is not set.
*/
kint32				dd_pcie_rc_int_set_int_own_func(DdPcieRcInt *self, DdPcieCh ch,
							DdPciRcIntOwnCb const* const intOwnCb);

/**
Set the function to call back when INT_EP interrupt occurs.
@param[in]	ch			Pcie channel. See @ref DdPcieCh.
@param [in] intEpCb	callback function table. See @ref DdPcieRcIntEpCb.
@retval D_DDIM_OK	OK
@remarks
			- When dd_pcie_rc_init1 is unexecution, radmIntxCb is not set.
*/
kint32				dd_pcie_rc_int_set_int_ep_func(DdPcieRcInt *self, DdPcieCh ch,
							DdPcieRcIntEpCb const* const intEpCb);

/**
Set the function to call back when INT_SY_SERR interrupt occurs.
@param[in]	ch			Pcie channel. See @ref DdPcieCh.
@param [in] sysErrCb	callback function table. See @ref DdPcieRcIntSysErrCb.
@retval D_DDIM_OK	OK
@remarks
			- When dd_pcie_rc_init1 is unexecution, cfgAerRcErrCb is not set.
*/
kint32				dd_pcie_rc_int_set_int_sys_err_func(DdPcieRcInt *self, DdPcieCh ch,
							DdPcieRcIntSysErrCb const* const sysErrCb);

/**
Set the function to call back when INT_TRS_ICS_MSI interrupt occurs.
@param[in]	ch					Pcie channel. See @ref DdPcieCh.
@param [in] intTrsIcsMsiCb	callback function table. See @ref DdPcieRcInt.
@retval D_DDIM_OK				OK
@remarks
			- When dd_pcie_rc_init1 is unexecution, cfgLinkAutoBwIntCb/cfgBwMgtIntCb is not set.
*/
kint32				dd_pcie_rc_int_set_int_trs_ics_msi_func(DdPcieRcInt *self, DdPcieCh ch,
							DdPcieRcIntTrsIcsMsiCb const* const intTrsIcsMsiCb);

/**
Interrupt handler for detect card of PCIe ch1.<br>
@param[in]	intst	Card edge detection. 8-9 bit.
*/
 void				dd_pcie_rc_int_ch1_int_exs_handler(DdPcieRcInt *self, kulong intst);
/**
Interrupt handler for detect card of PCIe ch0.<br>
@param[in]	intst	Card edge detection. 6-7 bit.
*/
void				dd_pcie_rc_int_ch0_int_exs_handler(DdPcieRcInt *self, kulong intst);
/**
Interrupt handler for PCIe ch0 system error.<br>
*/
//暂时不加参数
void				dd_pcie_rc_int_ch0_int_sys_err_handler(void);

/**
Interrupt handler for PCIe ch0 dma.<br>
*/
void				dd_pcie_rc_int_ch0_int_dma_handler(DdPcieRcInt *self);

/**
Interrupt handler for PCIe ch0 Trs_Ics_Msi.<br>
*/
//在DEF_INT_HANDLER_1 中作为参数，加参数会出错，暂时不加参数
void				dd_pcie_rc_int_ch0_int_trs_ics_msi_handler(void);

/**
Interrupt handler for PCIe ch1 own.<br>
*/
//在DEF_INT_HANDLER_1 中作为参数，加参数会出错，暂时不加参数
void				dd_pcie_rc_int_ch1_int_own_handler(void);

/**
Interrupt handler for PCIe ch1 endpoint.<br>
*/
//在DEF_INT_HANDLER_1 中作为参数，加参数会出错，暂时不加参数
void				dd_pcie_rc_int_ch1_int_ep_handler(void);

/**
Interrupt handler for PCIe ch1 system error.<br>
*/
//在DEF_INT_HANDLER_1 中作为参数，加参数会出错，暂时不加参数
void				dd_pcie_rc_int_ch1_int_sys_err_handler(void);

/**
Interrupt handler for PCIe ch1 dma.<br>
*/
//在DEF_INT_HANDLER_1 中作为参数，加参数会出错，暂时不加参数
void				dd_pcie_rc_int_ch1_int_dma_handler(void);

/**
Interrupt handler for PCIe ch1 Trs_Ics_Msi.<br>
*/
//在DEF_INT_HANDLER_1 中作为参数，加参数会出错，暂时不加参数
void				dd_pcie_rc_int_ch1_int_trs_ics_msi_handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __DD_PCIE_RC_INT_H__ */
