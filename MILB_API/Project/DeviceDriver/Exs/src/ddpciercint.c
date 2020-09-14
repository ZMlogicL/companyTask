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


#include "ddpciercint.h"
#include "ddpcierccommon.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdPcieRcInt, dd_pcie_rc_int);

#define DD_PCIE_RC_INT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdPcieRcIntPrivate, DD_TYPE_PCIE_RC_INT))


struct _DdPcieRcIntPrivate
{

};

/**
DECLS
*/

/**
IMPL
*/
static void dd_pcie_rc_int_constructor(DdPcieRcInt *self)
{
//	DdPcieRcIntPrivate *priv = DD_PCIE_RC_INT_GET_PRIVATE(self);
}

static void dd_pcie_rc_int_destructor(DdPcieRcInt *self)
{
//	DdPcieRcIntPrivate *priv = DD_PCIE_RC_INT_GET_PRIVATE(self);
}
/**
PUBLIC
*/
/**
 * @brief	It will be setting up the interrupt MSI.
 * @param	DdPcieRcInt const* const self
 * @return	kint32 D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_ctrl_msi(DdPcieRcInt const* const self)
{
#ifdef CO_PARAM_CHECK
	if (self == NULL) {
		return C_PCIE_INPUT_PARAM_ERROR;
	}
#endif

	if (self->ch == E_DD_PCIE_CH0) {
		if (DdExs_GET_RAM_PD_CTRL_PCIE0() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		ioPcie0Core.rc.ppl.mci0s.bit.mci0s = 0xFFFFFFFF;	// interrupt clear
		ioPcie0Core.rc.ppl.mca.bit.mca = self->cmpAdr;
		ioPcie0Core.rc.ppl.mci0e.bit.mci0e = self->intEn;
		gddPcieRcIntMsiCb[self->ch] = self->intMsiCb;
		ioPcie0Core.rc.ppl.mci0m.bit.mci0m = 0;	// Mask off
	} else {	// PCIe ch1
		if (DdExs_GET_RAM_PD_CTRL_PCIE1() != 0) {
			return C_PCIE_ACCESS_ERR;
		}

		ioPcie0Core.rc.ppl.mci0s.bit.mci0s = 0xFFFFFFFF;	// interrupt clear
		ioPcie1Core.rc.ppl.mca.bit.mca = self->cmpAdr;
		ioPcie1Core.rc.ppl.mci0e.bit.mci0e = self->intEn;
		gddPcieRcIntMsiCb[self->ch] = self->intMsiCb;
		ioPcie1Core.rc.ppl.mci0m.bit.mci0m = 0;	// Mask off
	}

	return D_DDIM_OK;
}

/**
 * @brief	Set the function to call back when INT_OWN interrupt occurs.
 * @param	DdPcieCh	ch
 * @param	DdPciRcIntOwnCb	intOwnCb
 * @return	kint32	D_DDIM_OK
 */
kint32 dd_pcie_rc_int_set_int_own_func(DdPcieRcInt *self, DdPcieCh ch, DdPciRcIntOwnCb const* const intOwnCb)
{
	gddPcieRcIntOwnCb[ch] = *intOwnCb;
	DdPcieBifurcation gddPcieRcBifurcation =
			dd_pcie_rc_common_get_gdd_pcie_rc_bifurcation(dd_pcie_rc_common_get());

	if (ch == E_DD_PCIE_CH0) {
		// rdlh_link_up
		if (gddPcieRcIntOwnCb[E_DD_PCIE_CH0].rdlhLinkUpCb != NULL) {
			if (dd_pcie_rc_get_link_status(NULL, ch) == FALSE) {	// Not link up
				ioPcie0.intControl2.bit.rdlhLinkUpStt = 1;// Clear Interrupt
				ioPcie0.intControl2.bit.rdlhLinkUpEn = 1;	// Interrupt Enable
				ioPcie0.intControl2.bit.rdlhLinkUpCen = 1;// Interrupt Clear Enable
				ioPcie0.intControl2.bit.rdlhLinkUpM = 0;	// Mask Off
			}
		} else {
			ioPcie0.intControl2.bit.rdlhLinkUpEn = 0;	// Interrupt Disable
			ioPcie0.intControl2.bit.rdlhLinkUpCen = 0;// Interrupt Clear Disable
		}

		if (gddPcieRcReType == E_DD_PCIE_RE_TYPE_RC) {
			// cfg_pme_int/cfg_pme_msi
			if (gddPcieRcIntOwnCb[E_DD_PCIE_CH0].cfgPmeCb != NULL) {
				ioPcie0Core.rc.pciecr.rsr.bit.pmes = 1;	// Clear Interrupt
				ioPcie0Core.rc.pciecr.rccr.bit.pmeie = 1;	// PME Interrupt Enable
				ioPcie0Core.rc.pmcr.pmcs.bit.pmeen = 1;	// PME Enable
			} else {
				ioPcie0Core.rc.pciecr.rccr.bit.pmeie = 0;	// PME Interrupt Disable
				ioPcie0Core.rc.pmcr.pmcs.bit.pmeen = 0;	// PME Disable
			}

			// hp_mpe/hp_int/hp_msi
			if(gddPcieRcIntOwnCb[E_DD_PCIE_CH0].hpCb != NULL){
				// Clear Interrupt
				ioPcie0Core.rc.pciecr.scsr.bit.abp = 1;	// PCIE_CAP_ATTENTION_BUTTON_PRESSED
				ioPcie0Core.rc.pciecr.scsr.bit.pfd = 1;	// PCIE_CAP_POWER_FAULT_DETECTED
				ioPcie0Core.rc.pciecr.scsr.bit.mrlsc = 1;// PCIE_CAP_MRL_SENSOR_CHANGED
				ioPcie0Core.rc.pciecr.scsr.bit.pdc = 1;	// PCIE_CAP_PRESENCE_DETECT_CHANGE
				ioPcie0Core.rc.pciecr.scsr.bit.cc = 1;	// PCIE_CAP_CMD_CPLD
				ioPcie0Core.rc.pciecr.scsr.bit.dllsc = 1;// PCIE_CAP_DLL_STATE_CHANGED
				// Interrupt Enable
				ioPcie0Core.rc.pciecr.scsr.bit.hpie = 1;// Hot Plug Interrupt Enable
				ioPcie0Core.rc.pciecr.scsr.bit.abpe = 1;// PCIE_CAP_ATTENTION_BUTTON_PRESSED
				ioPcie0Core.rc.pciecr.scsr.bit.pfde = 1;// PCIE_CAP_POWER_FAULT_DETECTED
				ioPcie0Core.rc.pciecr.scsr.bit.mrlsce = 1;// PCIE_CAP_MRL_SENSOR_CHANGED
				ioPcie0Core.rc.pciecr.scsr.bit.pdce = 1;// PCIE_CAP_PRESENCE_DETECT_CHANGE
				ioPcie0Core.rc.pciecr.scsr.bit.ccie = 1;	// PCIE_CAP_CMD_CPLD
				ioPcie0Core.rc.pciecr.scsr.bit.dllsce = 1;// PCIE_CAP_DLL_STATE_CHANGED

				ioPcie0.emSelect.bit.preDetSttSel	= 1;	// Control by relay terminal

				dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH0, TRUE);
				ioPcie0Core.rc.pciecr.scr.bit.abp = 1;
				ioPcie0Core.rc.pciecr.scr.bit.pcp = 1;
				ioPcie0Core.rc.pciecr.scr.bit.mrlsp = 1;
				dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH0, FALSE);
			} else {
				dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH0, TRUE);
				ioPcie0Core.rc.pciecr.scr.bit.abp = 0;
				ioPcie0Core.rc.pciecr.scr.bit.pcp = 0;
				ioPcie0Core.rc.pciecr.scr.bit.mrlsp = 0;
				dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH0, FALSE);

				// Interrupt Disable
				ioPcie0Core.rc.pciecr.scsr.bit.hpie = 0;// Hot Plug Interrupt Enable
				ioPcie0Core.rc.pciecr.scsr.bit.abpe = 0;// PCIE_CAP_ATTENTION_BUTTON_PRESSED
				ioPcie0Core.rc.pciecr.scsr.bit.pfde = 0;// PCIE_CAP_POWER_FAULT_DETECTED
				ioPcie0Core.rc.pciecr.scsr.bit.mrlsce = 0;// PCIE_CAP_MRL_SENSOR_CHANGED
				ioPcie0Core.rc.pciecr.scsr.bit.pdce = 0;// PCIE_CAP_PRESENCE_DETECT_CHANGE
				ioPcie0Core.rc.pciecr.scsr.bit.ccie = 0;	// PCIE_CAP_CMD_CPLD
				ioPcie0Core.rc.pciecr.scsr.bit.dllsce = 0;// PCIE_CAP_DLL_STATE_CHANGED
			}

			// wake
			if (gddPcieRcIntOwnCb[E_DD_PCIE_CH0].wakeCb != NULL) {
				dd_topfour_set_gpio_function(NULL, DdTop_GPIO_PY4, DdToptwo_GPIO_FUNC_HWMODE);
				ioPcie0.pmSelect1.bit.wakeSel = 1;// Control by terminal wake_n_i
				ioPcie0.intControl2.bit.wakeMask = 0;	// Mask Off
				ioPcie0.intControl2.bit.wakeClearEn = 1;// Interrupt Clear Enable
				ioPcie0.intControl2.bit.wakeEn = 1;	// Interrupt Enable
			} else {
				ioPcie0.intControl2.bit.wakeClearEn = 0;// Interrupt Clear Disable
				ioPcie0.intControl2.bit.wakeEn = 0;	// Interrupt Disable
			}
		}
	} else {
		// rdlh_link_up
		if (gddPcieRcIntOwnCb[E_DD_PCIE_CH1].rdlhLinkUpCb != NULL) {
			if (dd_pcie_rc_get_link_status(NULL, ch) == FALSE) {	// Not link up
				ioPcie1.intControl2.bit.rdlhLinkUpStt = 1;// Clear Interrupt
				ioPcie1.intControl2.bit.rdlhLinkUpEn = 1;	// Interrupt Enable
				ioPcie1.intControl2.bit.rdlhLinkUpCen = 1;// Interrupt Clear Enable
				ioPcie1.intControl2.bit.rdlhLinkUpM = 0;	// Mask Off
			}
		} else {
			ioPcie1.intControl2.bit.rdlhLinkUpEn = 0;	// Interrupt Disable
			ioPcie1.intControl2.bit.rdlhLinkUpCen = 0;// Interrupt Clear Disable
		}

		if(gddPcieRcReType == E_DD_PCIE_RE_TYPE_RC && gddPcieRcBifurcation == E_DD_PCIE_BIFURCATION_ENABLE) {
			// cfg_pme_int/cfg_pme_msi
			if (gddPcieRcIntOwnCb[E_DD_PCIE_CH1].cfgPmeCb != NULL) {
				ioPcie1Core.rc.pciecr.rsr.bit.pmes = 1;	// Clear Interrupt
				ioPcie1Core.rc.pciecr.rccr.bit.pmeie = 1;	// PME Interrupt Enable
				ioPcie1Core.rc.pmcr.pmcs.bit.pmeen = 1;	// PME Enable
			} else {
				ioPcie1Core.rc.pciecr.rccr.bit.pmeie = 0;	// PME Interrupt Disable
				ioPcie1Core.rc.pmcr.pmcs.bit.pmeen = 0;	// PME Disable
			}

			// hp_mpe/hp_int/hp_msi
			if(gddPcieRcIntOwnCb[E_DD_PCIE_CH1].hpCb != NULL){
				// Clear Interrupt
				ioPcie1Core.rc.pciecr.scsr.bit.abp = 1;// PCIE_CAP_ATTENTION_BUTTON_PRESSED
				ioPcie1Core.rc.pciecr.scsr.bit.pfd = 1;// PCIE_CAP_POWER_FAULT_DETECTED
				ioPcie1Core.rc.pciecr.scsr.bit.mrlsc = 1;	// PCIE_CAP_MRL_SENSOR_CHANGED
				ioPcie1Core.rc.pciecr.scsr.bit.pdc = 1;// PCIE_CAP_PRESENCE_DETECT_CHANGE
				ioPcie1Core.rc.pciecr.scsr.bit.cc = 1;	// PCIE_CAP_CMD_CPLD
				ioPcie1Core.rc.pciecr.scsr.bit.dllsc = 1;	// PCIE_CAP_DLL_STATE_CHANGED
				// Interrupt Enable
				ioPcie1Core.rc.pciecr.scsr.bit.hpie = 1;// Hot Plug Interrupt Enable
				ioPcie1Core.rc.pciecr.scsr.bit.abpe = 1;// PCIE_CAP_ATTENTION_BUTTON_PRESSED
				ioPcie1Core.rc.pciecr.scsr.bit.pfde = 1;// PCIE_CAP_POWER_FAULT_DETECTED
				ioPcie1Core.rc.pciecr.scsr.bit.mrlsce = 1;// PCIE_CAP_MRL_SENSOR_CHANGED
				ioPcie1Core.rc.pciecr.scsr.bit.pdce = 1;// PCIE_CAP_PRESENCE_DETECT_CHANGE
				ioPcie1Core.rc.pciecr.scsr.bit.ccie = 1;	// PCIE_CAP_CMD_CPLD
				ioPcie1Core.rc.pciecr.scsr.bit.dllsce = 1;// PCIE_CAP_DLL_STATE_CHANGED
				ioPcie1.emSelect.bit.preDetSttSel = 1;	// Control by relay terminal
				dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH1, TRUE);
				ioPcie1Core.rc.pciecr.scr.bit.abp = 1;
				ioPcie1Core.rc.pciecr.scr.bit.pcp = 1;
				ioPcie1Core.rc.pciecr.scr.bit.mrlsp = 1;
				dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH1, FALSE);
			} else {
				dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH1, TRUE);
				ioPcie1Core.rc.pciecr.scr.bit.abp = 0;
				ioPcie1Core.rc.pciecr.scr.bit.pcp = 0;
				ioPcie1Core.rc.pciecr.scr.bit.mrlsp = 0;
				dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH1, FALSE);

				// Interrupt Disable
				ioPcie1Core.rc.pciecr.scsr.bit.hpie = 0;// Hot Plug Interrupt Enable
				ioPcie1Core.rc.pciecr.scsr.bit.abpe = 0;// PCIE_CAP_ATTENTION_BUTTON_PRESSED
				ioPcie1Core.rc.pciecr.scsr.bit.pfde = 0;// PCIE_CAP_POWER_FAULT_DETECTED
				ioPcie1Core.rc.pciecr.scsr.bit.mrlsce = 0;// PCIE_CAP_MRL_SENSOR_CHANGED
				ioPcie1Core.rc.pciecr.scsr.bit.pdce = 0;// PCIE_CAP_PRESENCE_DETECT_CHANGE
				ioPcie1Core.rc.pciecr.scsr.bit.ccie = 0;	// PCIE_CAP_CMD_CPLD
				ioPcie1Core.rc.pciecr.scsr.bit.dllsce = 0;// PCIE_CAP_DLL_STATE_CHANGED
			}

			// wake
			if (gddPcieRcIntOwnCb[E_DD_PCIE_CH1].wakeCb != NULL) {
				dd_topfour_set_gpio_function(NULL, DdTop_GPIO_PY5, DdToptwo_GPIO_FUNC_HWMODE);
				ioPcie1.pmSelect1.bit.wakeSel = 1;// Control by terminal wake_n_i
				ioPcie1.intControl2.bit.wakeMask = 0;	// Mask Off
				ioPcie1.intControl2.bit.wakeClearEn = 1;// Interrupt Clear Enable
				ioPcie1.intControl2.bit.wakeEn = 1;	// Interrupt Enable
			} else {
				ioPcie1.intControl2.bit.wakeClearEn = 0;// Interrupt Clear Disable
				ioPcie1.intControl2.bit.wakeEn = 0;	// Interrupt Disable
			}
		}
	}

	return D_DDIM_OK;
}

/**
 * @brief	Set the function to call back when INT_EP interrupt occurs.
 * @param	DdPcieCh	ch
 * @param	DdPcieRcIntEpCb	intEpCb
 * @return	kint32	D_DDIM_OK
 */
kint32 dd_pcie_rc_int_set_int_ep_func(DdPcieRcInt *self, DdPcieCh ch, DdPcieRcIntEpCb const* const intEpCb)
{
	gddPcieRcIntEpCb[ch] = *intEpCb;
	DdPcieBifurcation gddPcieRcBifurcation =
			dd_pcie_rc_common_get_gdd_pcie_rc_bifurcation(dd_pcie_rc_common_get());

	if (ch == E_DD_PCIE_CH0) {
		// radm_pm_pme
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmPmPmeCb != NULL) {
			ioPcie0.intControl3.bit.radmPmPmeStt = 1;	// interrupt clear
			ioPcie0.intControl3.bit.radmPmPmeEn = 1;	// Interrupt Enable
			ioPcie0.intControl3.bit.radmPmPmeCen = 1;// Interrupt Clear Enable
			ioPcie0.intControl3.bit.radmPmPmeM = 0;	// Mask Off
		} else {
			ioPcie0.intControl3.bit.radmPmPmeEn = 0;	// Interrupt Disable
			ioPcie0.intControl3.bit.radmPmPmeCen = 0;// Interrupt Clear Disable
		}

		// radm_correctable_err
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmCorrectableErrCb != NULL) {
			ioPcie0.intControl3.bit.radmCorErrStt = 1;	// interrupt clear
			ioPcie0.intControl3.bit.radmCorErrEn = 1;	// Interrupt Enable
			ioPcie0.intControl3.bit.radmCorErrCen = 1;// Interrupt Clear Enable
			ioPcie0.intControl3.bit.radmCorErrM = 0;	// Mask Off
		} else {
			ioPcie0.intControl3.bit.radmCorErrEn = 0;	// Interrupt Disable
			ioPcie0.intControl3.bit.radmCorErrCen = 0;// Interrupt Clear Disable
		}

		// radm_nonfatal_err
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmNonfatalErrCb != NULL) {
			ioPcie0.intControl3.bit.radmNfErrStt = 1;	// interrupt clear
			ioPcie0.intControl3.bit.radmNfErrEn = 1;	// Interrupt Enable
			ioPcie0.intControl3.bit.radmNfErrCen = 1;// Interrupt Clear Enable
			ioPcie0.intControl3.bit.radmNfErrM = 0;	// Mask Off
		} else {
			ioPcie0.intControl3.bit.radmNfErrEn = 0;	// Interrupt Disable
			ioPcie0.intControl3.bit.radmNfErrCen = 0;// Interrupt Clear Disable
		}

		// radm_fatal_err
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmFatalErrCb != NULL) {
			ioPcie0.intControl3.bit.radmFErrStt = 1;	// interrupt clear
			ioPcie0.intControl3.bit.radmFErrEn = 1;	// Interrupt Enable
			ioPcie0.intControl3.bit.radmFErrCen = 1;// Interrupt Clear Enable
			ioPcie0.intControl3.bit.radmFErrM = 0;	// Mask Off
		} else {
			ioPcie0.intControl3.bit.radmFErrEn = 0;	// Interrupt Disable
			ioPcie0.intControl3.bit.radmFErrCen = 0;// Interrupt Clear Disable
		}

		// radm_pm_to_ack
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmPmToAckCb != NULL) {
			ioPcie0.intControl3.bit.radmPm2ackStt = 1;	// interrupt clear
			ioPcie0.intControl3.bit.radmPm2ackEn = 1;	// Interrupt Enable
			ioPcie0.intControl3.bit.radmPm2ackCen = 1;	// Interrupt Clear Enable
			ioPcie0.intControl3.bit.radmPm2ackM = 0;	// Mask Off
		} else {
			ioPcie0.intControl3.bit.radmPm2ackEn = 0;	// Interrupt Disable
			ioPcie0.intControl3.bit.radmPm2ackCen = 0;	// Interrupt Clear Disable
		}

		// radm_vendor_msg
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmVendorMsgCb != NULL) {
			ioPcie0.intControl2.bit.vendorMsgStt = 1;	// interrupt clear
			ioPcie0.intControl2.bit.vendorMsgEn = 1;	// Interrupt Enable
			ioPcie0.intControl2.bit.vendorMsgCen = 1;// Interrupt Clear Enable
			ioPcie0.intControl2.bit.vendorMsgM = 0;	// Mask Off
		} else {
			ioPcie0.intControl2.bit.vendorMsgEn = 0;	// Interrupt Disable
			ioPcie0.intControl2.bit.vendorMsgCen = 0;// Interrupt Clear Disable
		}

		// radm_msg_ltr
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmMsgLtrCb != NULL) {
			ioPcie0.intControl3.bit.radmMsgLtrStt = 1;// interrupt clear
			ioPcie0.intControl3.bit.radmMsgLtrEn = 1;	// Interrupt Enable
			ioPcie0.intControl3.bit.radmMsgLtrCen = 1;// Interrupt Clear Enable
			ioPcie0.intControl3.bit.radmMsgLtrM = 0;	// Mask Off
		} else {
			ioPcie0.intControl3.bit.radmMsgLtrEn = 0;	// Interrupt Disable
			ioPcie0.intControl3.bit.radmMsgLtrCen = 0;// Interrupt Clear Disable
		}

		if (gddPcieRcReType == E_DD_PCIE_RE_TYPE_RC) {
			// radm_inta/b/c/d
			if (gddPcieRcIntEpCb[E_DD_PCIE_CH0].radmIntxCb != NULL) {
				ioPcie0.intControl1.word &= 0xF0000000;	// interrupt clear
				ioPcie0Core.rc.ppl.mci0e.bit.mci0e = 0;// MSI interrupt disable
				ioPcie0Core.rc.t1csh.statusCommand.bit.id = 0;// interrupt enable
			}
		}
	} else {
		// radm_pm_pme
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmPmPmeCb != NULL) {
			ioPcie1.intControl3.bit.radmPmPmeStt = 1;	// interrupt clear
			ioPcie1.intControl3.bit.radmPmPmeEn = 1;	// Interrupt Enable
			ioPcie1.intControl3.bit.radmPmPmeCen = 1;	// Interrupt Clear Enable
			ioPcie1.intControl3.bit.radmPmPmeM = 0;	// Mask Off
		} else {
			ioPcie1.intControl3.bit.radmPmPmeEn = 0;	// Interrupt Disable
			ioPcie1.intControl3.bit.radmPmPmeCen = 0;	// Interrupt Clear Disable
		}

		// radm_correctable_err
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmCorrectableErrCb != NULL) {
			ioPcie1.intControl3.bit.radmCorErrStt = 1;// interrupt clear
			ioPcie1.intControl3.bit.radmCorErrEn = 1;	// Interrupt Enable
			ioPcie1.intControl3.bit.radmCorErrCen = 1;// Interrupt Clear Enable
			ioPcie1.intControl3.bit.radmCorErrM = 0;	// Mask Off
		} else {
			ioPcie1.intControl3.bit.radmCorErrEn = 0;	// Interrupt Disable
			ioPcie1.intControl3.bit.radmCorErrCen = 0;// Interrupt Clear Disable
		}

		// radm_nonfatal_err
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmNonfatalErrCb != NULL) {
			ioPcie1.intControl3.bit.radmNfErrStt = 1;	// interrupt clear
			ioPcie1.intControl3.bit.radmNfErrEn = 1;	// Interrupt Enable
			ioPcie1.intControl3.bit.radmNfErrCen = 1;	// Interrupt Clear Enable
			ioPcie1.intControl3.bit.radmNfErrM = 0;	// Mask Off
		} else {
			ioPcie1.intControl3.bit.radmNfErrEn = 0;	// Interrupt Disable
			ioPcie1.intControl3.bit.radmNfErrCen = 0;	// Interrupt Clear Disable
		}

		// radm_fatal_err
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmFatalErrCb != NULL) {
			ioPcie1.intControl3.bit.radmFErrStt = 1;	// interrupt clear
			ioPcie1.intControl3.bit.radmFErrEn = 1;	// Interrupt Enable
			ioPcie1.intControl3.bit.radmFErrCen = 1;// Interrupt Clear Enable
			ioPcie1.intControl3.bit.radmFErrM = 0;	// Mask Off
		} else {
			ioPcie1.intControl3.bit.radmFErrEn = 0;	// Interrupt Disable
			ioPcie1.intControl3.bit.radmFErrCen = 0;// Interrupt Clear Disable
		}

		// radm_pm_to_ack
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmPmToAckCb != NULL) {
			ioPcie1.intControl3.bit.radmPm2ackStt = 1;	// interrupt clear
			ioPcie1.intControl3.bit.radmPm2ackEn = 1;	// Interrupt Enable
			ioPcie1.intControl3.bit.radmPm2ackCen = 1;	// Interrupt Clear Enable
			ioPcie1.intControl3.bit.radmPm2ackM = 0;	// Mask Off
		} else {
			ioPcie1.intControl3.bit.radmPm2ackEn = 0;	// Interrupt Disable
			ioPcie1.intControl3.bit.radmPm2ackCen = 0;	// Interrupt Clear Disable
		}

		// radm_vendor_msg
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmVendorMsgCb != NULL) {
			ioPcie1.intControl2.bit.vendorMsgStt = 1;	// interrupt clear
			ioPcie1.intControl2.bit.vendorMsgEn = 1;	// Interrupt Enable
			ioPcie1.intControl2.bit.vendorMsgCen = 1;// Interrupt Clear Enable
			ioPcie1.intControl2.bit.vendorMsgM = 0;	// Mask Off
		} else {
			ioPcie1.intControl2.bit.vendorMsgEn = 0;	// Interrupt Disable
			ioPcie1.intControl2.bit.vendorMsgCen = 0;// Interrupt Clear Disable
		}

		// radm_msg_ltr
		if (gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmMsgLtrCb != NULL) {
			ioPcie1.intControl3.bit.radmMsgLtrStt = 1;// interrupt clear
			ioPcie1.intControl3.bit.radmMsgLtrEn = 1;	// Interrupt Enable
			ioPcie1.intControl3.bit.radmMsgLtrCen = 1;// Interrupt Clear Enable
			ioPcie1.intControl3.bit.radmMsgLtrM = 0;	// Mask Off
		} else {
			ioPcie1.intControl3.bit.radmMsgLtrEn = 0;	// Interrupt Disable
			ioPcie1.intControl3.bit.radmMsgLtrCen = 0;// Interrupt Clear Disable
		}

		if (gddPcieRcReType == E_DD_PCIE_RE_TYPE_RC && gddPcieRcBifurcation == E_DD_PCIE_BIFURCATION_ENABLE){
			// radm_inta/b/c/d
			if (gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmIntxCb != NULL) {
				ioPcie1.intControl1.word &= 0xF0000000;	// interrupt clear
				ioPcie1Core.rc.ppl.mci0e.bit.mci0e = 0;// MSI interrupt disable
				ioPcie1Core.rc.t1csh.statusCommand.bit.id = 0;// interrupt enable
			}
		}
	}

	return D_DDIM_OK;
}

/**
 * @brief	Set the function to call back when INT_SYS_ERR interrupt occurs.
 * @param	DdPcieCh	ch
 * @param	DdPcieRcIntSysErrCb	int_sysErrCb
 * @return	kint32	D_DDIM_OK
 */
kint32 dd_pcie_rc_int_set_int_sys_err_func(DdPcieRcInt *self, DdPcieCh ch, DdPcieRcIntSysErrCb const* const int_sysErrCb)
{
	gddPcieRcIntSysErrCb[ch] = *int_sysErrCb;
	DdPcieBifurcation gddPcieRcBifurcation =
			dd_pcie_rc_common_get_gdd_pcie_rc_bifurcation(dd_pcie_rc_common_get());

	if (ch == E_DD_PCIE_CH0) {
		if (gddPcieRcReType == E_DD_PCIE_RE_TYPE_RC) {
			// cfg_sys_err_rc
			if (gddPcieRcIntSysErrCb[E_DD_PCIE_CH0].cfgSysErrRcCb != NULL) {
				ioPcie0.intControl2.bit.sysErrRcStt = 1;	// interrupt clear
				ioPcie0.intControl2.bit.sysErrRcEn = 1;	// Interrupt Enable
				ioPcie0.intControl2.bit.sysErrRcCen = 1;// Interrupt Clear Enable
				ioPcie0.intControl2.bit.sysErrRcM = 0;	// Mask Off
			} else {
				ioPcie0.intControl2.bit.sysErrRcEn = 0;	// Interrupt Disable
				ioPcie0.intControl2.bit.sysErrRcCen = 0;// Interrupt Clear Disable
			}

			// cfg_aer_rc_err_int/cfg_aer_rc_err_msi
			if (gddPcieRcIntSysErrCb[E_DD_PCIE_CH0].cfgAerRcErrCb != NULL) {
				ioPcie0Core.rc.aerc.resr.word &= 0x0000007F;// interrupt clear
				ioPcie0Core.rc.aerc.recr.bit.cere = 1;// Correctable Error Reporting Enable
				ioPcie0Core.rc.aerc.recr.bit.nfere = 1;// Non-Fatal Error Reporting Enable
				ioPcie0Core.rc.aerc.recr.bit.fere = 1;// Fatal Error Reporting Enable
			} else {
				ioPcie0Core.rc.aerc.recr.bit.cere = 0;// Correctable Error Reporting Disable
				ioPcie0Core.rc.aerc.recr.bit.nfere = 0;// Non-Fatal Error Reporting Disable
				ioPcie0Core.rc.aerc.recr.bit.fere = 0;// Fatal Error Reporting Disable
			}

			if (gddPcieRcIntSysErrCb[E_DD_PCIE_CH0].cfgSysErrRcCb != NULL
					|| gddPcieRcIntSysErrCb[E_DD_PCIE_CH0].cfgAerRcErrCb != NULL) {
				ioPcie0Core.rc.pciecr.rccr.bit.secee = 1;
				ioPcie0Core.rc.pciecr.rccr.bit.senfee = 1;
				ioPcie0Core.rc.pciecr.rccr.bit.sefee = 1;
				ioPcie0Core.rc.t1csh.statusCommand.bit.serre = 1;
				ioPcie0Core.rc.t1csh.bridgeCtrlIntPinIntLine.bit.serre = 1;
				ioPcie0Core.rc.pciecr.dcsr.bit.cere = 1;
				ioPcie0Core.rc.pciecr.dcsr.bit.nfere = 1;
				ioPcie0Core.rc.pciecr.dcsr.bit.fere = 1;
			} else {
				ioPcie0Core.rc.pciecr.rccr.bit.secee = 0;
				ioPcie0Core.rc.pciecr.rccr.bit.senfee = 0;
				ioPcie0Core.rc.pciecr.rccr.bit.sefee = 0;
				ioPcie0Core.rc.t1csh.statusCommand.bit.serre = 0;
				ioPcie0Core.rc.t1csh.bridgeCtrlIntPinIntLine.bit.serre = 0;
				ioPcie0Core.rc.pciecr.dcsr.bit.cere = 0;
				ioPcie0Core.rc.pciecr.dcsr.bit.nfere = 0;
				ioPcie0Core.rc.pciecr.dcsr.bit.fere = 0;
			}
		}
	} else {
		if (gddPcieRcReType == E_DD_PCIE_RE_TYPE_RC && gddPcieRcBifurcation == E_DD_PCIE_BIFURCATION_ENABLE) {
			// cfg_sys_err_rc
			if (gddPcieRcIntSysErrCb[E_DD_PCIE_CH1].cfgSysErrRcCb != NULL) {
				ioPcie1.intControl2.bit.sysErrRcStt = 1;	// interrupt clear
				ioPcie1.intControl2.bit.sysErrRcEn = 1;	// Interrupt Enable
				ioPcie1.intControl2.bit.sysErrRcCen = 1;// Interrupt Clear Enable
				ioPcie1.intControl2.bit.sysErrRcM = 0;	// Mask Off
			} else {
				ioPcie1.intControl2.bit.sysErrRcEn = 0;	// Interrupt Disable
				ioPcie1.intControl2.bit.sysErrRcCen = 0;// Interrupt Clear Disable
			}

			// cfg_aer_rc_err_int/cfg_aer_rc_err_msi
			if (gddPcieRcIntSysErrCb[E_DD_PCIE_CH1].cfgAerRcErrCb != NULL) {
				ioPcie1Core.rc.aerc.resr.word &= 0x0000007F;// interrupt clear
				ioPcie1Core.rc.aerc.recr.bit.cere = 1;// Correctable Error Reporting Enable
				ioPcie1Core.rc.aerc.recr.bit.nfere = 1;	// Non-Fatal Error Reporting Enable
				ioPcie1Core.rc.aerc.recr.bit.fere = 1;// Fatal Error Reporting Enable
			} else {
				ioPcie1Core.rc.aerc.recr.bit.cere = 0;// Correctable Error Reporting Disable
				ioPcie1Core.rc.aerc.recr.bit.nfere = 0;	// Non-Fatal Error Reporting Disable
				ioPcie1Core.rc.aerc.recr.bit.fere = 0;// Fatal Error Reporting Disable
			}

			if (gddPcieRcIntSysErrCb[E_DD_PCIE_CH1].cfgSysErrRcCb != NULL
					|| gddPcieRcIntSysErrCb[E_DD_PCIE_CH1].cfgAerRcErrCb != NULL) {
				ioPcie1Core.rc.pciecr.rccr.bit.secee = 1;
				ioPcie1Core.rc.pciecr.rccr.bit.senfee = 1;
				ioPcie1Core.rc.pciecr.rccr.bit.sefee = 1;
				ioPcie1Core.rc.t1csh.statusCommand.bit.serre = 1;
				ioPcie1Core.rc.t1csh.bridgeCtrlIntPinIntLine.bit.serre = 1;
				ioPcie1Core.rc.pciecr.dcsr.bit.cere = 1;
				ioPcie1Core.rc.pciecr.dcsr.bit.nfere = 1;
				ioPcie1Core.rc.pciecr.dcsr.bit.fere = 1;
			} else {
				ioPcie1Core.rc.pciecr.rccr.bit.secee = 0;
				ioPcie1Core.rc.pciecr.rccr.bit.senfee = 0;
				ioPcie1Core.rc.pciecr.rccr.bit.sefee = 0;
				ioPcie1Core.rc.t1csh.statusCommand.bit.serre = 0;
				ioPcie1Core.rc.t1csh.bridgeCtrlIntPinIntLine.bit.serre = 0;
				ioPcie1Core.rc.pciecr.dcsr.bit.cere = 0;
				ioPcie1Core.rc.pciecr.dcsr.bit.nfere = 0;
				ioPcie1Core.rc.pciecr.dcsr.bit.fere = 0;
			}
		}
	}

	return D_DDIM_OK;
}

/**
 * @brief	Set the function to call back when INT_TRS_ICS_MSI interrupt occurs.
 * @param	DdPcieCh	ch
 * @param	DdPcieRcInt	intTrsIcsMsiCb
 * @return	kint32	D_DDIM_OK
 */
kint32	dd_pcie_rc_int_set_int_trs_ics_msi_func(DdPcieRcInt *self, DdPcieCh ch,
		DdPcieRcIntTrsIcsMsiCb const* const intTrsIcsMsiCb)
{
	gddPcieRcIntTrsIcsMsiCb[ch] = *intTrsIcsMsiCb;
	DdPcieBifurcation gddPcieRcBifurcation =
			dd_pcie_rc_common_get_gdd_pcie_rc_bifurcation(dd_pcie_rc_common_get());

	if (ch == E_DD_PCIE_CH0) {
		// smlh_req_rst_not
		if (gddPcieRcIntTrsIcsMsiCb[E_DD_PCIE_CH0].smlhReqRstNotCb != NULL) {
			ioPcie0.intControl2.bit.smlhReqRstStt = 1; // interrupt clear
			ioPcie0.intControl2.bit.smlhReqRstEn = 1; // Interrupt Enable
			ioPcie0.intControl2.bit.smlhReqRstCen = 1; // Interrupt Clear Enable
			ioPcie0.intControl2.bit.smlhReqRstM = 0; // Mask Off
		} else {
			ioPcie0.intControl2.bit.smlhReqRstEn = 0; // Interrupt Disable
			ioPcie0.intControl2.bit.smlhReqRstCen = 0; // Interrupt Clear Disable
		}

		if (gddPcieRcReType == E_DD_PCIE_RE_TYPE_RC) {
			// cfg_link_auto_bw_int
			if (gddPcieRcIntTrsIcsMsiCb[E_DD_PCIE_CH0].cfgLinkAutoBwIntCb != NULL) {
				ioPcie0Core.rc.pciecr.lcsr.bit.labs = 1;	// interrupt clear
				ioPcie0Core.rc.pciecr.lcsr.bit.labie = 1;	// PCIE_CAP_LINK_AUTO_BW_INT_EN Enable
			} else {
				ioPcie0Core.rc.pciecr.lcsr.bit.labie = 0;	// PCIE_CAP_LINK_AUTO_BW_INT_EN Disable
			}

			// cfg_bw_mgt_int
			if (gddPcieRcIntTrsIcsMsiCb[E_DD_PCIE_CH0].cfgBwMgtIntCb != NULL) {
				ioPcie0Core.rc.pciecr.lcsr.bit.lbms = 1;	// interrupt clear
				ioPcie0Core.rc.pciecr.lcsr.bit.lbmie = 1;// PCIE_CAP_LINK_BW_MAN_INT_EN Enable
			} else {
				ioPcie0Core.rc.pciecr.lcsr.bit.lbmie = 0;// PCIE_CAP_LINK_BW_MAN_INT_EN Disable
			}
		}


	} else {
		// smlh_req_rst_not
		if (gddPcieRcIntTrsIcsMsiCb[E_DD_PCIE_CH1].smlhReqRstNotCb != NULL) {
			ioPcie1.intControl2.bit.smlhReqRstStt = 1;	// interrupt clear
			ioPcie1.intControl2.bit.smlhReqRstEn = 1;	// Interrupt Enable
			ioPcie1.intControl2.bit.smlhReqRstCen = 1;// Interrupt Clear Enable
			ioPcie1.intControl2.bit.smlhReqRstM = 0;	// Mask Off
		} else {
			ioPcie1.intControl2.bit.smlhReqRstEn = 0;	// Interrupt Disable
			ioPcie1.intControl2.bit.smlhReqRstCen = 0;// Interrupt Clear Disable
		}

		if (gddPcieRcReType == E_DD_PCIE_RE_TYPE_RC && gddPcieRcBifurcation == E_DD_PCIE_BIFURCATION_ENABLE) {
			// cfg_link_auto_bw_int
			if (gddPcieRcIntTrsIcsMsiCb[E_DD_PCIE_CH1].cfgLinkAutoBwIntCb != NULL) {
				ioPcie1Core.rc.pciecr.lcsr.bit.labs = 1;	// interrupt clear
				ioPcie1Core.rc.pciecr.lcsr.bit.labie = 1;	// PCIE_CAP_LINK_AUTO_BW_INT_EN Enable
			} else {
				ioPcie1Core.rc.pciecr.lcsr.bit.labie = 0;	// PCIE_CAP_LINK_AUTO_BW_INT_EN Disable
			}

			// cfg_bw_mgt_int
			if (gddPcieRcIntTrsIcsMsiCb[E_DD_PCIE_CH1].cfgBwMgtIntCb != NULL) {
				ioPcie1Core.rc.pciecr.lcsr.bit.lbms = 1;	// interrupt clear
				ioPcie1Core.rc.pciecr.lcsr.bit.lbmie = 1;	// PCIE_CAP_LINK_BW_MAN_INT_EN Enable
			} else {
				ioPcie1Core.rc.pciecr.lcsr.bit.lbmie = 0;	// PCIE_CAP_LINK_BW_MAN_INT_EN Disable
			}
		}
	}

	return D_DDIM_OK;
}

/**
 * @brief	Interrupt handler for detect card of PCIe ch0.
 * @param	intst	Card edge detection
 */
void dd_pcie_rc_int_ch0_int_exs_handler(DdPcieRcInt *self, kulong intst)
{
	VpCallbackPcieFunc callback;

	if ((intst & DdExsBranch_PCIe0_RIS_BIT) != 0) {
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] dd_pcie_rc_int_ch0_int_exs_handler : Rising Interrupt.\n"));
	} else if ((intst & DdExsBranch_PCIe0_FIS_BIT) != 0) {
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] dd_pcie_rc_int_ch0_int_exs_handler : Falling Interrupt.\n"));

		// Hot-Plug flow (Card Detect)
		if ((gddPcieRcIntOwnCb[E_DD_PCIE_CH0].hpCb != NULL) && ioPcie0Core.rc.pciecr.scsr.bit.pdce) {
			ioPcie0.emControl.bit.preDetChged = 1;
		}
	}

	callback = gddPcieRcHpDetectCard[E_DD_PCIE_CH0];
	if (callback != NULL) {
		(*callback)((kuint32) DdExsBranch_GET_SIGMON_PCIE0_CD());
	}
}

/**
 * @brief	Interrupt handler for detect card of PCIe ch1.
 * @param	intst	Card edge detection
 */
void dd_pcie_rc_int_ch1_int_exs_handler(DdPcieRcInt *self, kulong intst)
{
	VpCallbackPcieFunc callback;

	if ((intst & DdExsBranch_PCIe1_RIS_BIT) != 0) {
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] dd_pcie_rc_int_ch1_int_exs_handler : Rising Interrupt.\n"));
	} else if ((intst & DdExsBranch_PCIe1_FIS_BIT) != 0) {
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] dd_pcie_rc_int_ch1_int_exs_handler : Falling Interrupt.\n"));

		// Hot-Plug flow (Card Detect)
		if ((gddPcieRcIntOwnCb[E_DD_PCIE_CH1].hpCb != NULL) && ioPcie1Core.rc.pciecr.scsr.bit.pdce) {
			ioPcie1.emControl.bit.preDetChged = 1;
		}
	}

	callback = gddPcieRcHpDetectCard[E_DD_PCIE_CH1];
	if (callback != NULL) {
		(*callback)((kuint32) DdExsBranch_GET_SIGMON_PCIE1_CD());
	}
}

/**
 * @brief	Interrupt handler for PCIe ch0 system error.
 */
void dd_pcie_rc_int_ch0_int_sys_err_handler(void)
{
	kuint32 intStat;
	VpCallbackPcieFunc callback;

	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] CH0 INT_SYS_ERR Occurred.\n"));

	// cfg_aer_rc_err_int/cfg_aer_rc_err_msi
	if ((ioPcie0Core.rc.aerc.resr.word & 0x0000007F) != 0) {
		intStat = ioPcie0Core.rc.aerc.resr.word;
		ioPcie0Core.rc.aerc.resr.word &= 0x0000007F;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_aer_rc_err \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie0Core.rc.aerc.resr.word, intStat));

		callback = gddPcieRcIntSysErrCb[E_DD_PCIE_CH0].cfgAerRcErrCb;
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_aer_rc_err callback\n"));
			(*callback)(intStat & 0x0000007F);
		}
	} else if (ioPcie0.intControl2.bit.sysErrRcStt != 0) {// cfg_sys_err_rc
		ioPcie0.intControl2.bit.sysErrRcStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_sys_err_rc\n"));

		callback = gddPcieRcIntSysErrCb[E_DD_PCIE_CH0].cfgSysErrRcCb;
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_sys_err_rc callback\n"));
			(*callback)(0);
		}
	}
}

/**
 * @brief	Interrupt handler for PCIe ch0 dma.
 */
void dd_pcie_rc_int_ch0_int_dma_handler(DdPcieRcInt *self)
{
	kuint32 status;
	VpCallbackPcieFunc callback;

	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] CH0 INT_DMA Occurred.\n"));

	if (ioPcie0Core.rc.ppl.dwis.word) {// DMA Write Interupt Status (Done and Abort)
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] DMA Write Interrupt Status \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie0Core.rc.ppl.dwis.word, (kuint32)ioPcie0Core.rc.ppl.dwis.word));

		// ioPcie0Core.rc.ppl.dwis.word
		// 0x00000001  Done Interrupt status(DMA ch0)
		// 0x00000002  Done Interrupt status(DMA ch1)
		// 0x00010000  Abort Interrupt status(DMA ch0)
		// 0x00020000  Abort Interrupt status(DMA ch1)
		status = ioPcie0Core.rc.ppl.dwis.word;
		ioPcie0Core.rc.ppl.dwic.word = ioPcie0Core.rc.ppl.dwis.word;// Interrupt clear
		callback = gddPcieRcIntDmaCb[E_DD_PCIE_CH0].wrCb;
		if (callback) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] INT_DMA write callback\n"));
			(*callback)(status);
		}
	} else if (ioPcie0Core.rc.ppl.dris.word) {// DMA Read Interupt Status (Done and Abort)
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] DMA Read Interrupt Status \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie0Core.rc.ppl.dris.word, (kuint32)ioPcie0Core.rc.ppl.dris.word));

		// ioPcie0Core.rc.ppl.dris.word
		// 0x00000001  Done Interrupt status(DMA ch0)
		// 0x00000002  Done Interrupt status(DMA ch1)
		// 0x00010000  Abort Interrupt status(DMA ch0)
		// 0x00020000  Abort Interrupt status(DMA ch1)
		status = ioPcie0Core.rc.ppl.dris.word;
		ioPcie0Core.rc.ppl.dric.word = ioPcie0Core.rc.ppl.dris.word;// Interrupt clear
		callback = gddPcieRcIntDmaCb[E_DD_PCIE_CH0].rdCb;
		if (callback) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] INT_DMA read callback\n"));
			(*callback)(status);
		}
	}
}

/**
 * @brief	Interrupt handler for PCIe ch0 Trs_Ics_Msi.
 */
void dd_pcie_rc_int_ch0_int_trs_ics_msi_handler(void)
{
	kuint32 intStat;
	VpCallbackPcieFunc callback;

	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] CH0 INT_TRS_ICS_MSI Occurred.\n"));

	// msi_ctrl_int (MSI interrupt)
	if (ioPcie0Core.rc.ppl.mci0s.bit.mci0s != 0) {
		intStat = ioPcie0Core.rc.ppl.mci0s.bit.mci0s;
		ioPcie0Core.rc.ppl.mci0s.bit.mci0s = intStat;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] msi_ctrl_int \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie0Core.rc.ppl.mci0s.word, intStat));

		callback = gddPcieRcIntMsiCb[E_DD_PCIE_CH0];
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] msi_ctrl_int callback\n"));
			(*callback)(intStat);
		}
	} else if (ioPcie0Core.rc.pciecr.lcsr.bit.labs != 0) {// cfg_link_auto_bw_int
		intStat = ioPcie0Core.rc.pciecr.lcsr.word;
		ioPcie0Core.rc.pciecr.lcsr.bit.labs = 1;		// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_link_auto_bw_int \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie0Core.rc.pciecr.lcsr.word, intStat));

		callback = gddPcieRcIntTrsIcsMsiCb[E_DD_PCIE_CH0].cfgLinkAutoBwIntCb;
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_link_auto_bw_int callback\n"));
			(*callback)(0);
		}
	} else if (ioPcie0Core.rc.pciecr.lcsr.bit.lbms != 0) {// cfg_bw_mgt_int
		intStat = ioPcie0Core.rc.pciecr.lcsr.word;
		ioPcie0Core.rc.pciecr.lcsr.bit.lbms = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_bw_mgt_int \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie0Core.rc.pciecr.lcsr.word, intStat));

		callback = gddPcieRcIntTrsIcsMsiCb[E_DD_PCIE_CH0].cfgBwMgtIntCb;
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_bw_mgt_int callback\n"));
			(*callback)(0);
		}
	} else if (ioPcie0.intControl2.bit.smlhReqRstStt != 0) {// smlh_req_rst_not
		intStat = ioPcie0.intControl2.word;
		ioPcie0.intControl2.bit.smlhReqRstStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] smlh_req_rst_not \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie0.intControl2.word, intStat));

		callback = gddPcieRcIntTrsIcsMsiCb[E_DD_PCIE_CH0].smlhReqRstNotCb;
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] smlh_req_rst_not callback\n"));
			(*callback)(0);
		}
	}
}

/**
 * @brief	Interrupt handler for PCIe ch1 own.
 */
void dd_pcie_rc_int_ch1_int_own_handler(void)
{
	VpCallbackPcieFunc callback;

	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] CH1 INT_OWN Occurred.\n"));

	// cfg_pme_int/cfg_pme_msi
	if (ioPcie1Core.rc.pciecr.rsr.bit.pmes == 1) {
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_pme_int/cfg_pme_msi.\n"));
		ioPcie1Core.rc.pciecr.rsr.bit.pmes = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH1].cfgPmeCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie1Core.rc.pciecr.scsr.bit.abp == 1) {
		// hp_mpe/hp_int/hp_msi // PCIE_CAP_ATTENTION_BUTTON_PRESSED
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] hp_mpe/hp_int/hp_msi: PCIE_CAP_ATTENTION_BUTTON_PRESSED.\n"));
		dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH1, TRUE);
		ioPcie1Core.rc.pciecr.scr.bit.abp = 0;
		dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH1, FALSE);
		ioPcie1Core.rc.pciecr.scsr.bit.abp = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH1].hpCb;
		if (callback != NULL) {
			(*callback)(DdPcieRc_PCIE_HOT_PLUG_ST_ABP);
		}
	} else if (ioPcie1Core.rc.pciecr.scsr.bit.pfd == 1) {
		// PCIE_CAP_POWER_FAULT_DETECTED
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] hp_mpe/hp_int/hp_msi: PCIE_CAP_POWER_FAULT_DETECTED.\n"));
		dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH1, TRUE);
		ioPcie1Core.rc.pciecr.scr.bit.pcp = 0;
		dd_pcie_rc_set_wr_acc_to_ro_reg(NULL, E_DD_PCIE_CH1, FALSE);
		ioPcie1Core.rc.pciecr.scsr.bit.pfd = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH1].hpCb;
		if (callback != NULL) {
			(*callback)(DdPcieRc_PCIE_HOT_PLUG_ST_PFD);
		}
	} else if (ioPcie1Core.rc.pciecr.scsr.bit.mrlsc == 1) {
		// PCIE_CAP_MRL_SENSOR_CHANGED
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] hp_mpe/hp_int/hp_msi: PCIE_CAP_MRL_SENSOR_CHANGED.\n"));
		ioPcie1Core.rc.pciecr.scsr.bit.mrlsc = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH1].hpCb;
		if (callback != NULL) {
			(*callback)(DdPcieRc_PCIE_HOT_PLUG_ST_MRLSC);
		}
	} else if (ioPcie1Core.rc.pciecr.scsr.bit.pdc == 1) {
		// PCIE_CAP_PRESENCE_DETECTED_CHANGED
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] hp_mpe/hp_int/hp_msi: PCIE_CAP_PRESENCE_DETECTED_CHANGED.\n"));
		ioPcie1Core.rc.pciecr.scsr.bit.pdc = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH1].hpCb;
		if (callback != NULL) {
			(*callback)(DdPcieRc_PCIE_HOT_PLUG_ST_PDC);
		}
	} else if (ioPcie1Core.rc.pciecr.scsr.bit.cc == 1) {
		// PCIE_CAP_CMD_CPLD
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] hp_mpe/hp_int/hp_msi: PCIE_CAP_CMD_CPLD.\n"));
		ioPcie1.emControl.bit.cmdCpledInt = 0;
		ioPcie1Core.rc.pciecr.scsr.bit.cc = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH1].hpCb;
		if (callback != NULL) {
			(*callback)(DdPcieRc_PCIE_HOT_PLUG_ST_CC);
		}
	} else if (ioPcie1Core.rc.pciecr.scsr.bit.dllsc == 1) {
		// PCIE_CAP_DLL_STATE_CHANGED
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] hp_mpe/hp_int/hp_msi: PCIE_CAP_DLL_STATE_CHANGED.\n"));
		ioPcie1Core.rc.pciecr.scsr.bit.dllsc = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH1].hpCb;
		if (callback != NULL) {
			(*callback)(DdPcieRc_PCIE_HOT_PLUG_ST_DLLSC);
		}
	} else if (ioPcie1.intControl2.bit.rdlhLinkUpStt == 1) {
		// rdlh_link_up
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] rdlh_link_up.\n"));
		ioPcie1.intControl2.bit.rdlhLinkUpStt = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH1].rdlhLinkUpCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie1.intControl2.bit.wakeStatus == 1) {
		// wake
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] wake.\n"));
		ioPcie1.intControl2.bit.wakeStatus = 1;	// Clear Interrupt
		callback = gddPcieRcIntOwnCb[E_DD_PCIE_CH1].wakeCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	}
}

/**
 * @brief	Interrupt handler for PCIe ch1 endpoint.
 */
void dd_pcie_rc_int_ch1_int_ep_handler(void)
{
	kuint32 intStat;
	VpCallbackPcieFunc callback;

	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] CH1 INT_EP Occurred.\n"));

	// radm_inta/b/c/d
	if (ioPcie1.intControl1.word & 0xF0000000) {
		intStat = ioPcie1.intControl1.word;
		ioPcie1.intControl1.word &= intStat;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] INTX_Status \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie1.intControl1.word, intStat));

		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmIntxCb;
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] INT_X callback\n"));
			(*callback)(intStat >> 28);// argument: 1(INTA), 2(INTB), 4(INTC), 8(INTD)
		}
	} else if (ioPcie1.intControl3.bit.radmPmPmeStt == 1) {
		// radm_pm_pme
		ioPcie1.intControl3.bit.radmPmPmeStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_pm_pme\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmPmPmeCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie1.intControl3.bit.radmCorErrStt == 1) {
		// radm_correctable_err
		ioPcie1.intControl3.bit.radmCorErrStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_correctable_err\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmCorrectableErrCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie1.intControl3.bit.radmNfErrStt == 1) {
		// radm_nonfatal_err
		ioPcie1.intControl3.bit.radmNfErrStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_nonfatal_err\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmNonfatalErrCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie1.intControl3.bit.radmFErrStt == 1) {
		// radm_fatal_err
		ioPcie1.intControl3.bit.radmFErrStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_fatal_err\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmFatalErrCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie1.intControl3.bit.radmPm2ackStt == 1) {
		// radm_pm_to_ack
		ioPcie1.intControl3.bit.radmPm2ackStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_pm_to_ack\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmPmToAckCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie1.intControl2.bit.vendorMsgStt == 1) {
		// radm_vendor_msg
		ioPcie1.intControl2.bit.vendorMsgStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_vendor_msg\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmVendorMsgCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	} else if (ioPcie1.intControl3.bit.radmMsgLtrStt) {
		// radm_msg_ltr
		// LTR Interrupt Status
		ioPcie1.intControl3.bit.radmMsgLtrStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] radm_msg_ltr\n"));
		callback = gddPcieRcIntEpCb[E_DD_PCIE_CH1].radmMsgLtrCb;
		if (callback != NULL) {
			(*callback)(0);
		}
	}
}

/**
 * @brief	Interrupt handler for PCIe ch1 system error.
 */
void dd_pcie_rc_int_ch1_int_sys_err_handler(void)
{
	kuint32 intStat;
	VpCallbackPcieFunc callback;

	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] CH1 INT_SYS_ERR Occurred.\n"));

	// cfg_aer_rc_err_int/cfg_aer_rc_err_msi
	if ((ioPcie1Core.rc.aerc.resr.word & 0x0000007F) != 0) {
		intStat = ioPcie1Core.rc.aerc.resr.word;
		ioPcie1Core.rc.aerc.resr.word &= 0x0000007F;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_aer_rc_err \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie1Core.rc.aerc.resr.word, intStat));

		callback = gddPcieRcIntSysErrCb[E_DD_PCIE_CH1].cfgAerRcErrCb;
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_aer_rc_err callback\n"));
			(*callback)(intStat & 0x0000007F);
		}
	} else if (ioPcie1.intControl2.bit.sysErrRcStt != 0) {
		// cfg_sys_err_rc
		ioPcie1.intControl2.bit.sysErrRcStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_sys_err_rc\n"));
		callback = gddPcieRcIntSysErrCb[E_DD_PCIE_CH1].cfgSysErrRcCb;
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_sys_err_rc callback\n"));
			(*callback)(0);
		}
	}
}

/**
 * @brief	Interrupt handler for PCIe ch1 dma.
 */
void dd_pcie_rc_int_ch1_int_dma_handler(void)
{
	kuint32 status;
	VpCallbackPcieFunc callback;

	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] CH1 INT_DMA Occurred.\n"));

	if (ioPcie1Core.rc.ppl.dwis.word) {// DMA Write Interupt Status (Done and Abort)
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] DMA Write Interrupt Status \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie1Core.rc.ppl.dwis.word, (kuint32)ioPcie1Core.rc.ppl.dwis.word));

		// ioPcie1Core.rc.ppl.dwis.word
		// 0x00000001  Done Interrupt status(DMA ch0)
		// 0x00000002  Done Interrupt status(DMA ch1)
		// 0x00010000  Abort Interrupt status(DMA ch0)
		// 0x00020000  Abort Interrupt status(DMA ch1)
		status = ioPcie1Core.rc.ppl.dwis.word;
		ioPcie1Core.rc.ppl.dwic.word = ioPcie1Core.rc.ppl.dwis.word;// Interrupt clear
		callback = gddPcieRcIntDmaCb[E_DD_PCIE_CH1].wrCb;
		if (callback) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] INT_DMA write callback\n"));
			(*callback)(status);
		}
	} else if (ioPcie1Core.rc.ppl.dris.word) {// DMA Read Interupt Status (Done and Abort)
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] DMA Read Interrupt Status \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie1Core.rc.ppl.dris.word, (kuint32)ioPcie1Core.rc.ppl.dris.word));

		// ioPcie1Core.rc.ppl.dris.word
		// 0x00000001  Done Interrupt status(DMA ch0)
		// 0x00000002  Done Interrupt status(DMA ch1)
		// 0x00010000  Abort Interrupt status(DMA ch0)
		// 0x00020000  Abort Interrupt status(DMA ch1)
		status = ioPcie1Core.rc.ppl.dris.word;
		ioPcie1Core.rc.ppl.dric.word = ioPcie1Core.rc.ppl.dris.word;// Interrupt clear
		callback = gddPcieRcIntDmaCb[E_DD_PCIE_CH1].rdCb;
		if (callback) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] INT_DMA read callback\n"));
			(*callback)(status);
		}
	}
}

/**
 * @brief	Interrupt handler for PCIe ch1 Trs_Ics_Msi.
 */
void dd_pcie_rc_int_ch1_int_trs_ics_msi_handler(void)
{
	kuint32 intStat;
	VpCallbackPcieFunc callback;

	DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] CH1 INT_TRS_ICS_MSI Occurred.\n"));

	// msi_ctrl_int (MSI interrupt)
	if (ioPcie1Core.rc.ppl.mci0s.bit.mci0s != 0) {
		intStat = ioPcie1Core.rc.ppl.mci0s.bit.mci0s;
		ioPcie1Core.rc.ppl.mci0s.bit.mci0s = intStat;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] msi_ctrl_int \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie1Core.rc.ppl.mci0s.word, intStat));

		callback = gddPcieRcIntMsiCb[E_DD_PCIE_CH1];
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] msi_ctrl_int callback\n"));
			(*callback)(intStat);
		}
	} else if (ioPcie1Core.rc.pciecr.lcsr.bit.labs != 0) {
		// cfg_link_auto_bw_int
		intStat = ioPcie1Core.rc.pciecr.lcsr.word;
		ioPcie1Core.rc.pciecr.lcsr.bit.labs = 1;		// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_link_auto_bw_int \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie1Core.rc.pciecr.lcsr.word, intStat));

		callback = gddPcieRcIntTrsIcsMsiCb[E_DD_PCIE_CH1].cfgLinkAutoBwIntCb;
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_link_auto_bw_int callback\n"));
			(*callback)(0);
		}
	} else if (ioPcie1Core.rc.pciecr.lcsr.bit.lbms != 0) {
		// cfg_bw_mgt_int
		intStat = ioPcie1Core.rc.pciecr.lcsr.word;
		ioPcie1Core.rc.pciecr.lcsr.bit.lbms = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_bw_mgt_int \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie1Core.rc.pciecr.lcsr.word, intStat));

		callback = gddPcieRcIntTrsIcsMsiCb[E_DD_PCIE_CH1].cfgBwMgtIntCb;
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] cfg_bw_mgt_int callback\n"));
			(*callback)(0);
		}
	} else if (ioPcie1.intControl2.bit.smlhReqRstStt != 0) {
		// smlh_req_rst_not
		intStat = ioPcie1.intControl2.word;
		ioPcie1.intControl2.bit.smlhReqRstStt = 1;	// interrupt clear
		DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] smlh_req_rst_not \t0x%08X\t0x%08X\n",
						(kuint32)&ioPcie1.intControl2.word, intStat));

		callback = gddPcieRcIntTrsIcsMsiCb[E_DD_PCIE_CH1].smlhReqRstNotCb;
		if (callback != NULL) {
			DdPcieRcCommon_DEBUG_PRINT(("[DD_PCIE_RC] smlh_req_rst_not callback\n"));
			(*callback)(0);
		}
	}
}

DdPcieRcInt* dd_pcie_rc_int_new(void)
{
	DdPcieRcInt* self = k_object_new_with_private(DD_TYPE_PCIE_RC_INT, sizeof(DdPcieRcIntPrivate));

	return self;
}
