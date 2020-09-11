/*
* @上海网用软件有限公司
*
* Date        : 2020-9-11
*
* Author    : zhou hong
*
* Version   :0.0.0
*
* Description :功能描述
*/

#include "exstop.h"
#include "driver_common.h"
#include "ddimusercustom.h"
#include "ddexspart.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdExsPart, dd_exs_part);
#define DD_EXS_PART_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), DdExsPartPrivate, DD_TYPE_EXS_PART))

struct _DdExsPartPrivate
{
    int a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static kulong S_DD_EXS_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));

static void dd_exs_part_constructor(DdExsPart *self)
{
	DdExsPartPrivate *priv = DD_EXS_PART_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_exs_part_destructor(DdExsPart *self)
{

}

/*----------------------------------------------------------------------*/
/* PUBLIC(公有函数接口实现)														*/
/*----------------------------------------------------------------------*/

/**
Set PCIE1 macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_part_set_ram_pd_ctrl_pcie1(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.ramPd.bit.rampdPcie1 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set eMMC macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_part_set_ram_pd_ctrl_emmc(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.ramPd.bit.rampdEmmc = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the Nand Flash BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output Nand Flash BUS CLOCK.
						<li> 1:Stop Nand Flash BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_nf_bus_clock_stop_ctrl(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.busckstp.bit.nfCkStp = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the PCIE0 BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output PCIE0 BUS CLOCK.
						<li> 1:Stop PCIE0 BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_pcie0_bus_clock_stop_ctrl(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.busckstp.bit.pcie0CkStp = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the PCIE1 BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output PCIE1 BUS CLOCK.
						<li> 1:Stop PCIE1 BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_pcie1_bus_clock_stop_ctrl(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.busckstp.bit.pcie1CkStp = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the XDMAC BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output XDMAC BUS CLOCK.
						<li> 1:Stop XDMAC BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_xdmac_bus_clock_stop_ctrl(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.busckstp.bit.xdmacCkStp = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the HDMAC BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output HDMAC BUS CLOCK.
						<li> 1:Stop HDMAC BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_hdmac_bus_clock_stop_ctrl(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.busckstp.bit.hdmacCkStp = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the eMMC BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output eMMC BUS CLOCK.
						<li> 1:Stop eMMC BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_emmc_bus_clock_stop_ctrl(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.busckstp.bit.emmcCkStp = val;//TODO:	emmcCkStp的命名有问题,有一个名为IoExstopEmmcckstp					emmcCkstp
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the SD2 (Wifi) BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output SD2 (Wifi) BUS CLOCK.
						<li> 1:Stop SD2 (Wifi) BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_sd2_bus_clock_stop_ctrl(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.busckstp.bit.sd2CkStp = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the SD3 (UHS2) BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output SD3 (UHS2) BUS CLOCK.
						<li> 1:Stop SD3 (UHS2) BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_sd3_bus_clock_stop_ctrl(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.busckstp.bit.sd3CkStp = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the SD4 (UHS1 Card) BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output SD4 (UHS1 Card) BUS CLOCK.
						<li> 1:Stop SD4 (UHS1 Card) BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_sd4_bus_clock_stop_ctrl(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.busckstp.bit.sd4CkStp = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the NETSEC BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output NETSEC BUS CLOCK.
						<li> 1:Stop NETSEC BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_netsec_bus_clock_stop_ctrl(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.busckstp.bit.netsecCkStp = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the RELC BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output RELC BUS CLOCK.
						<li> 1:Stop RELC BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_relc_bus_clock_stop_ctrl(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.busckstp.bit.relcCkStp = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the PTP_CLK NETSEC macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output PTP_CLK.
						<li> 1:Stop PTP_CLK.</ul>
@retval	None.
*/
void dd_exs_part_set_netsec_ptpclk_stop_ctrl_netsec_ptpstp(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.nsecCkstp.bit.netsecPtpStp = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the output a signal to stop control of the MMC_BCLK_I.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output MMC_BCLK_I.
						<li> 1:Stop MMC_BCLK_I.</ul>
@retval	None.
*/
void dd_exs_part_set_emmc_ckstp_emclkstp(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.emmcCkStp.bit.emClkStp = val;//emmcCkStp应该是emmcCkstp比较合理
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set pvDtimec.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_em_pv_dtimec(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.emPvDtimec.bit.pvDtimec = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set pvAmpbl.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_em_pv_ampbl(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.emPvAmpbl.bit.pvAmpbl = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set crSlottype.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_em_cr_slottype(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.emCrSlottype.bit.crSlottype = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set crBclkfreq.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_em_cr_bclkfreq(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.emCrBclkfreq.bit.crBclkfreq = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set emcd.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_em_cddet_emcd(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.emCddet.bit.emcd = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set hdcHclken.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_ckctl_hdc_hclken(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Ckctl.bit.hdcHclken = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set hoHclken.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_ckctl_ho_hclken(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Ckctl.bit.hoHclken = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set hdcSrst.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_rctl_hdc_srst(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Rctl.bit.hdcSrst = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set hoSrst.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_rctl_ho_srst(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Rctl.bit.hoSrst = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set anpd.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_anpd_anpd(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Anpd.bit.anpd = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set hfSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_hfsel_hf_sel(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Hfsel.bit.hfSel = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set fsel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_fsel_fsel(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Fsel.bit.fsel = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set pllbtune.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_fsel_pllbtune(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Fsel.bit.pllbtune = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set ssFadjHostI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_ehci_strap_ss_fadj_host_i(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2EhciStrap.bit.ssFadjHostI = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set ssFladjValI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_ehci_strap_ss_fladj_val_i(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2EhciStrap.bit.ssFladjValI = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set ssFladjValI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_ohci_if_ohci_clksel_i(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2OhciIf.bit.ohciClkselI = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set ssEnaIncr4I.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_lmodset_ss_ena_incr4_i(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Lmodset.bit.ssEnaIncr4I = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set ssEnaIncr8I.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_lmodset_ss_ena_incr8_i(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Lmodset.bit.ssEnaIncr8I = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set ssEnaIncr16I.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_lmodset_ss_ena_incr16_i(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Lmodset.bit.ssEnaIncr16I = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set ssEnaIncAlI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_lmodset_ss_ena_inc_al_i(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Lmodset.bit.ssEnaIncAlI = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set ssEhci64bEnI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_lmodset_ss_ehci64b_en_i(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Lmodset.bit.ssEhci64bEnI = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set rpdpenI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_pmodset_rpdpen_i(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Pmodset.bit.rpdpenI = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set rpdmenI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_pmodset_rpdmen_i(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Pmodset.bit.rpdmenI = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb2Ehpt.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_hpt_ctl_usb2_ehpt(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2HptCtl.bit.usb2Ehpt = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb2Ohpt.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_hpt_ctl_usb2_ohpt(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2HptCtl.bit.usb2Ohpt = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set usb2IdpuVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_idvbusctl_usb2_idpu_val(DdExsPart *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.usb2Idvbusctl.bit.usb2IdpuVal = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

DdExsPart* dd_exs_part_new(void)
{
	DdExsPart* self = k_object_new_with_private(DD_TYPE_EXS_PART, sizeof(DdExsPartPrivate));
	return self;
}
