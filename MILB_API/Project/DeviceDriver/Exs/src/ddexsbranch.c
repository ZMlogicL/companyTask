/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :周洪
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、Exs driver
*2、将dd_exs.c里将后面的个共有方法放在这里
*@version
*1.0.0 2020年06月开始开发
*/

#include "exstop.h"
#include "driver_common.h"
#include "ddimusercustom.h"
#include "ddexsbranch.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdExsBranch, dd_exs_branch);
#define DD_EXS_BRANCH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), DdExsBranchPrivate, DD_TYPE_EXS_BRANCH))

struct _DdExsBranchPrivate
{
    int a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static kulong S_DD_EXS_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));

static void dd_exs_branch_constructor(DdExsBranch *self)
{
	DdExsBranchPrivate *priv = DD_EXS_BRANCH_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_exs_branch_destructor(DdExsBranch *self)
{

}

/*----------------------------------------------------------------------*/
/* PUBLIC(公有函数接口实现)														*/
/*----------------------------------------------------------------------*/

/**
Set usb2IdpuSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_idpu_sel(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Idvbusctl.bit.usb2IdpuSel = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb2IdSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_id_sel(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Idvbusctl.bit.usb2IdSel = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb2IdVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_id_val(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Idvbusctl.bit.usb2IdVal = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb2VbSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_vb_sel(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Idvbusctl.bit.usb2VbSel = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb2VbVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_vb_val(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Idvbusctl.bit.usb2VbVal = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb2VbdetSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_vbdet_sel(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Idvbusctl.bit.usb2VbdetSel = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb2VbdetVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_vbdet_val(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Idvbusctl.bit.usb2VbdetVal = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set hdmacBc1.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_hdmac1_hdmac_bc1(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Hdmac1.bit.hdmacBc1 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set hdmacBt1.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_hdmac1_hdmac_bt1(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Hdmac1.bit.hdmacBt1 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set hdmacMs1.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_hdmac1_hdmac_ms1(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Hdmac1.bit.hdmacMs1 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set hdmacBc2.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_hdmac2_hdmac_bc2(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Hdmac2.bit.hdmacBc2 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set hdmacBt2.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_hdmac2_hdmac_bt2(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Hdmac2.bit.hdmacBt2 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set hdmacMs2.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_hdmac2_hdmac_ms2(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Hdmac2.bit.hdmacMs2 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set fsmrst1.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_dmafsm1_fsmrst1(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Dmafsm1.bit.fsmrst1 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set fsmrst2.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_dmafsm2_fsmrst2(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Dmafsm2.bit.fsmrst2 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set aclken.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_ckctl_aclken(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Ckctl.bit.aclken = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set sftrst.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_rctl_sftrst(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Rctl.bit.sftrst = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set phyResetN.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_rctl_phy_reset_n(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Rctl.bit.phyResetN = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set acjtLevel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_rcv_sns_acjt_level(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3RcvSns.bit.acjtLevel = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set fsel3.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_fsel_fsel3(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Fsel.bit.fsel3 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set mpllMultiplier.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_fsel_mpll_multiplier(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Fsel.bit.mpllMultiplier = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set sscRefClkSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_fsel_ssc_ref_clk_sel(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Fsel.bit.sscRefClkSel = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set refClkdiv2.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_fsel_ref_clkdiv2(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Fsel.bit.refClkdiv2 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set refSspEn.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_rfc_ctl_ref_ssp_en(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3RfcCtl.bit.refSspEn = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set refUsePad.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_rfc_ctl_ref_use_pad(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3RfcCtl.bit.refUsePad = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set pciImplement.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_ho_if_pci_implement(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3HoIf.bit.pciImplement = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set hostMsiEnable.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_ho_if_host_msi_enable(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3HoIf.bit.hostMsiEnable = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set xhcBme.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_ho_if_xhc_bme(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3HoIf.bit.xhcBme = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set xhcAc64.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_ho_if_xhc_ac64(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3HoIf.bit.xhcAc64 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set fladj30mhzReg.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_jt_adj_fladj_30mhz_reg(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3JtAdj.bit.fladj30mhzReg = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb3OvrcurEn.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_jt_adj_usb3_ovrcur_en(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3JtAdj.bit.usb3OvrcurEn = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb3IdpuVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_idpu_val(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Idvbusctl.bit.usb3IdpuVal = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb3IdSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_id_sel(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Idvbusctl.bit.usb3IdSel = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb3IdVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_id_val(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Idvbusctl.bit.usb3IdVal = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb3VbSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_vb_sel(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Idvbusctl.bit.usb3VbSel = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb3VbVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_vb_val(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Idvbusctl.bit.usb3VbVal = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb3VbdetSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_vbdet_sel(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Idvbusctl.bit.usb3VbdetSel = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb3VbdetVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_vbdet_val(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb3Idvbusctl.bit.usb3VbdetVal = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set dscvInhibit.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_ip_ctl_dscv_inhibit(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfIpCtl.bit.dscvInhibit = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set dscvIgnrCrc.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_ip_ctl_dscv_ignr_crc(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfIpCtl.bit.dscvIgnrCrc = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set bootEn.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_ip_ctl_boot_en(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfIpCtl.bit.bootEn = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set iddqEn.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_ip_ctl_iddq_en(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfIpCtl.bit.iddqEn = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set rbValidTime.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_rb_valid_tm(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfRbValidTm.bit.rbValidTime = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set phyCtrl.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_phy_ctrl_reg(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfPhyCtrlReg.bit.phyCtrl = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set PHY_DQ_TIMENG.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_phy_dq_timing(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfPhyDqTim.bit.phyDqTiming = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set phyDqsTiming.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_phy_dqs_timing(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfPhyDqsTim.bit.phyDqsTiming = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set phyGtLpbkCtl.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_phy_gt_lpbk_ctl(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfPhyGtLpbk.bit.phyGtLpbkCtl = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set phyDllMstCtl.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_phy_dll_mctl(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfPhyDllMctl.bit.phyDllMstCtl = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set phyDllSlvCtl.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_phy_dll_sctl(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfPhyDllSctl.bit.phyDllSlvCtl = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set bootEccSecSiz.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_boot_ecc_ctl_sec_siz(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfBootEccCtl.bit.bootEccSecSiz = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set btEccCorrStr.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_boot_ecc_ctl_corr_str(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfBootEccCtl.bit.btEccCorrStr = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set bootEccEn.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_boot_ecc_ctl_en(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfBootEccCtl.bit.bootEccEn = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set nfwpxCnt.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_nfwpx_cnt(DdExsBranch *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nfNfwpxCnt.bit.nfwpxCnt = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of SD2_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_sd2_ris(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_SD2_RIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of SD2_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_sd2_fis(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_SD2_FIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of SD3_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_sd3_ris(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_SD3_RIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of SD3_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_sd3_fis(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_SD3_FIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of SD4_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_sd4_ris(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_SD4_RIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of SD4_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_sd4_fis(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_SD4_FIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of PCIe0_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_pcie0_ris(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_PCIE0_RIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of PCIe0_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_pcie0_fis(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_PCIE0_FIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of PCIe1_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_pcie1_ris(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_PCIE1_RIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of PCIe1_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_pcie1_fis(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_PCIE1_FIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of USB2VBUS_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb2vbus_ris(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_USB2VBUS_RIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of USB2VBUS_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb2vbus_fis(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_USB2VBUS_FIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of USB2ID_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb2id_ris(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_USB2ID_RIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of USB2ID_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb2id_fis(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_USB2ID_FIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of USB3VBUS_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb3vbus_ris(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_USB3VBUS_RIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of USB3VBUS_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb3vbus_fis(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_USB3VBUS_FIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of USB3ID_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb3id_ris(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_USB3ID_RIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
The status of intstat of USB3ID_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb3id_fis(DdExsBranch *self)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intstat.word = DdExsBranch_USB3ID_FIS_BIT;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
External Strage CD(CARD detector) INT handler.<br>
@param[in]  *val Setting value
					<ul><li> 0-1 bit : SD2(UHS1 Wifi).
						<li> 2-3 bit : SD3(UHS2).
						<li> 4-5 bit : SD4(UHS1 Card).
						<li> 6-7 bit : PCIe0.
						<li> 8-9 bit : PCIe1.
						<li> 10-11 bit : USB2 VBUS.
						<li> 12-13 bit : USB2 ID.
						<li> 14-15 bit : USB3 VBUS.
						<li> 16-17 bit : USB3 ID.
						<li> Even bit of 0 : The interrupt signal by the card detection rising edge detection factor is output.
						<li> Even bit of 1 : The interrupt signal by the card detection rising edge detection factor is mask.
						<li> Odd bit of 0 : The interrupt signal by the card detection falling edge detection factor is output.
						<li> Odd bit of 1 : The interrupt signal by the card detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_branch_int_handler(DdExsBranch *self, kulong *val)
{
	*val = ioExstop.intstat.word;
	ioExstop.intstat.word = *val;	// Int clear
}

DdExsBranch* dd_exs_branch_get(void)
{
	static DdExsBranch *ddExsBranch = NULL;
	if(!ddExsBranch)
	{
		ddExsBranch = k_object_new_with_private(DD_TYPE_EXS_BRANCH,sizeof(DdExsBranchPrivate));
	}
	return ddExsBranch;
}
