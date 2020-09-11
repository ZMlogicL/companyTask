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

#ifndef __DD_EXS_PART_H__
#define __DD_EXS_PART_H__

#include <klib.h>
#include "ddimtypedef.h"
#include "driver_common.h"
#include "ddarm.h"
#include "exstop.h"

#define DD_TYPE_EXS_PART     (dd_exs_part_get_type())
#define DD_EXS_PART(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, DdExsPart))
#define DD_IS_EXS_PART(obj)  (K_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_EXS_PART))

typedef struct _DdExsPart                DdExsPart;
typedef struct _DdExsPartPrivate DdExsPartPrivate;

struct _DdExsPart
{
	KObject parent;
};

KConstType dd_exs_part_get_type(void);
DdExsPart* dd_exs_part_new(void);

/**
Set PCIE1 macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_part_set_ram_pd_ctrl_pcie1(DdExsPart *self, kulong val);

/**
Set eMMC macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_part_set_ram_pd_ctrl_emmc(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the Nand Flash BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output Nand Flash BUS CLOCK.
						<li> 1:Stop Nand Flash BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_nf_bus_clock_stop_ctrl(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the PCIE0 BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output PCIE0 BUS CLOCK.
						<li> 1:Stop PCIE0 BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_pcie0_bus_clock_stop_ctrl(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the PCIE1 BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output PCIE1 BUS CLOCK.
						<li> 1:Stop PCIE1 BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_pcie1_bus_clock_stop_ctrl(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the XDMAC BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output XDMAC BUS CLOCK.
						<li> 1:Stop XDMAC BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_xdmac_bus_clock_stop_ctrl(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the HDMAC BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output HDMAC BUS CLOCK.
						<li> 1:Stop HDMAC BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_hdmac_bus_clock_stop_ctrl(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the eMMC BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output eMMC BUS CLOCK.
						<li> 1:Stop eMMC BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_emmc_bus_clock_stop_ctrl(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the SD2 (Wifi) BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output SD2 (Wifi) BUS CLOCK.
						<li> 1:Stop SD2 (Wifi) BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_sd2_bus_clock_stop_ctrl(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the SD3 (UHS2) BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output SD3 (UHS2) BUS CLOCK.
						<li> 1:Stop SD3 (UHS2) BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_sd3_bus_clock_stop_ctrl(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the SD4 (UHS1 Card) BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output SD4 (UHS1 Card) BUS CLOCK.
						<li> 1:Stop SD4 (UHS1 Card) BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_sd4_bus_clock_stop_ctrl(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the NETSEC BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output NETSEC BUS CLOCK.
						<li> 1:Stop NETSEC BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_netsec_bus_clock_stop_ctrl(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the RELC BUS CLOCK macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output RELC BUS CLOCK.
						<li> 1:Stop RELC BUS CLOCK.</ul>
@retval	None.
*/
void dd_exs_part_set_relc_bus_clock_stop_ctrl(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the PTP_CLK NETSEC macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output PTP_CLK.
						<li> 1:Stop PTP_CLK.</ul>
@retval	None.
*/
void dd_exs_part_set_netsec_ptpclk_stop_ctrl_netsec_ptpstp(DdExsPart *self, kulong val);

/**
Set the output a signal to stop control of the MMC_BCLK_I.<br>
@param[in]  *val Setting value
					<ul><li> 0:Output MMC_BCLK_I.
						<li> 1:Stop MMC_BCLK_I.</ul>
@retval	None.
*/
void dd_exs_part_set_emmc_ckstp_emclkstp(DdExsPart *self, kulong val);

/**
Set pvDtimec.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_em_pv_dtimec(DdExsPart *self, kulong val);

/**
Set pvAmpbl.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_em_pv_ampbl(DdExsPart *self, kulong val);

/**
Set crSlottype.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_em_cr_slottype(DdExsPart *self, kulong val);

/**
Set crBclkfreq.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_em_cr_bclkfreq(DdExsPart *self, kulong val);

/**
Set emcd.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_em_cddet_emcd(DdExsPart *self, kulong val);

/**
Set hdcHclken.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_ckctl_hdc_hclken(DdExsPart *self, kulong val);

/**
Set hoHclken.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_ckctl_ho_hclken(DdExsPart *self, kulong val);

/**
Set hdcSrst.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_rctl_hdc_srst(DdExsPart *self, kulong val);

/**
Set hoSrst.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_rctl_ho_srst(DdExsPart *self, kulong val);

/**
Set anpd.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_anpd_anpd(DdExsPart *self, kulong val);

/**
Set hfSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_hfsel_hf_sel(DdExsPart *self, kulong val);

/**
Set fsel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_fsel_fsel(DdExsPart *self, kulong val);

/**
Set pllbtune.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_fsel_pllbtune(DdExsPart *self, kulong val);

/**
Set ssFadjHostI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_ehci_strap_ss_fadj_host_i(DdExsPart *self, kulong val);

/**
Set ssFladjValI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_ehci_strap_ss_fladj_val_i(DdExsPart *self, kulong val);

/**
Set ssFladjValI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_ohci_if_ohci_clksel_i(DdExsPart *self, kulong val);

/**
Set ssEnaIncr4I.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_lmodset_ss_ena_incr4_i(DdExsPart *self, kulong val);

/**
Set ssEnaIncr8I.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_lmodset_ss_ena_incr8_i(DdExsPart *self, kulong val);

/**
Set ssEnaIncr16I.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_lmodset_ss_ena_incr16_i(DdExsPart *self, kulong val);

/**
Set ssEnaIncAlI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_lmodset_ss_ena_inc_al_i(DdExsPart *self, kulong val);

/**
Set ssEhci64bEnI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_lmodset_ss_ehci64b_en_i(DdExsPart *self, kulong val);

/**
Set rpdpenI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_pmodset_rpdpen_i(DdExsPart *self, kulong val);

/**
Set rpdmenI.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_pmodset_rpdmen_i(DdExsPart *self, kulong val);

/**
Set usb2Ehpt.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_hpt_ctl_usb2_ehpt(DdExsPart *self, kulong val);

/**
Set usb2Ohpt.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_hpt_ctl_usb2_ohpt(DdExsPart *self, kulong val);

/**
Set usb2IdpuVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_part_set_usb2_idvbusctl_usb2_idpu_val(DdExsPart *self, kulong val);

#endif /* __DD_EXS_PART_H__ */
