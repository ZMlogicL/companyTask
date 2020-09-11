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
*2、将dd_exs.h里将前面的77个共有方法放在这里,这里的宏均在别的文件里用
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __DD_EXS_H__
#define __DD_EXS_H__

#include <klib.h>
#include "ddimtypedef.h"
#include "driver_common.h"
#include "ddarm.h"
#include "exstop.h"

#define DD_TYPE_EXS     (dd_exs_get_type())
#define DD_EXS(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, DdExs))
#define DD_IS_EXS(obj)  (K_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_EXS))

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
// ramPd
#define DdExs_GET_RAM_PD_CTRL_SD2()				(ioExstop.ramPd.bit.rampdSd2)						/**< Get SD2(UHS1 Wifi) macro PD signal output of RAMCELL with PD<br>
																													Values:
																													<ul><li>0:Power-down mode is released
																													<li>1:Enters Power-down mode</ul> */
#define DdExs_GET_RAM_PD_CTRL_SD3()				(ioExstop.ramPd.bit.rampdSd3)						/**< Get SD3(UHS2) macro PD signal output of RAMCELL with PD<br>
																													Values:
																													<ul><li>0:Power-down mode is released
																													<li>1:Enters Power-down mode</ul> */
#define DdExs_GET_RAM_PD_CTRL_SD4()				(ioExstop.ramPd.bit.rampdSd4)						/**< Get SD4(UHS1 Card) macro PD signal output of RAMCELL with PD<br>
																													Values:
																													<ul><li>0:Power-down mode is released
																													<li>1:Enters Power-down mode</ul> */
#define DdExs_GET_RAM_PD_CTRL_NF()				(ioExstop.ramPd.bit.rampdNf)							/**< Get Nand Flash macro PD signal output of RAMCELL with PD<br>
																													Values:
																													<ul><li>0:Power-down mode is released
																													<li>1:Enters Power-down mode</ul> */
#define DdExs_GET_RAM_PD_CTRL_RELC()			(ioExstop.ramPd.bit.rampdRelc)						/**< Get RELC macro PD signal output of RAMCELL with PD<br>
																													Values:
																													<ul><li>0:Power-down mode is released
																													<li>1:Enters Power-down mode</ul> */
#define DdExs_GET_RAM_PD_CTRL_NETSEC()		(ioExstop.ramPd.bit.rampdNetsec)						/**< Get NETSEC macro PD signal output of RAMCELL with PD<br>
																													Values:
																													<ul><li>0:Power-down mode is released
																													<li>1:Enters Power-down mode</ul> */
#define DdExs_GET_RAM_PD_CTRL_USB2()			(ioExstop.ramPd.bit.rampdUsb2)						/**< Get USB2 macro PD signal output of RAMCELL with PD<br>
																													Values:
																													<ul><li>0:Power-down mode is released
																													<li>1:Enters Power-down mode</ul> */
#define DdExs_GET_RAM_PD_CTRL_USB3()			(ioExstop.ramPd.bit.rampdUsb3)						/**< Get USB3 macro PD signal output of RAMCELL with PD<br>
																													Values:
																													<ul><li>0:Power-down mode is released
																													<li>1:Enters Power-down mode</ul> */
#define DdExs_GET_RAM_PD_CTRL_PCIE0()			(ioExstop.ramPd.bit.rampdPcie0)						/**< Get PCIE0 macro PD signal output of RAMCELL with PD<br>
																													Values:
																													<ul><li>0:Power-down mode is released
																													<li>1:Enters Power-down mode</ul> */
#define DdExs_GET_RAM_PD_CTRL_PCIE1()			(ioExstop.ramPd.bit.rampdPcie1)						/**< Get PCIE1 macro PD signal output of RAMCELL with PD<br>
																													Values:
																													<ul><li>0:Power-down mode is released
																													<li>1:Enters Power-down mode</ul> */
#define DdExs_GET_RAM_PD_CTRL_EMMC()			(ioExstop.ramPd.bit.rampdEmmc)						/**< Get eMMC macro PD signal output of RAMCELL with PD<br>
																													Values:
																													<ul><li>0:Power-down mode is released
																													<li>1:Enters Power-down mode</ul> */
// busckstp
#define DdExs_GET_NF_BUS_CLOCK_STOP_CTRL()				(ioExstop.busckstp.bit.nfCkStp)						/**< Get the output a signal to stop control of the Nand Flash BUS CLOCK macro<br>
																													Values:
																													<ul><li>0:Output Nand Flash BUS CLOCK
																													<li>1:Stop Nand Flash BUS CLOCK</ul> */
#define DdExs_GET_PCIE0_BUS_CLOCK_STOP_CTRL()			(ioExstop.busckstp.bit.pcie0CkStp)					/**< Get the output a signal to stop control of the PCIE0 BUS CLOCK macro<br>
																													Values:
																													<ul><li>0:Output PCIE0 BUS CLOCK
																													<li>1:Stop PCIE0 BUS CLOCK</ul> */
#define DdExs_GET_PCIE1_BUS_CLOCK_STOP_CTRL()			(ioExstop.busckstp.bit.pcie1CkStp)					/**< Get the output a signal to stop control of the PCIE1 BUS CLOCK macro<br>
																													Values:
																													<ul><li>0:Output PCIE1 BUS CLOCK
																													<li>1:Stop PCIE1 BUS CLOCK</ul> */
#define DdExs_GET_XDMAC_BUS_CLOCK_STOP_CTRL()		(ioExstop.busckstp.bit.xdmacCkStp)					/**< Get the output a signal to stop control of the XDMAC BUS CLOCK macro<br>
																													Values:
																													<ul><li>0:Output XDMAC BUS CLOCK
																													<li>1:Stop XDMAC BUS CLOCK</ul> */
#define DdExs_GET_HDMAC_BUS_CLOCK_STOP_CTRL()		(ioExstop.busckstp.bit.hdmacCkStp)					/**< Get the output a signal to stop control of the HDMAC BUS CLOCK macro<br>
																													Values:
																													<ul><li>0:Output HDMAC BUS CLOCK
																													<li>1:Stop HDMAC BUS CLOCK</ul> */
#define DdExs_GET_EMMC_BUS_CLOCK_STOP_CTRL()			(ioExstop.busckstp.bit.emmcCkStp)						/**< Get the output a signal to stop control of the eMMC BUS CLOCK macro<br>
																													Values:
																													<ul><li>0:Output eMMC BUS CLOCK
																													<li>1:Stop eMMC BUS CLOCK</ul> */
#define DdExs_GET_SD2_BUS_CLOCK_STOP_CTRL()				(ioExstop.busckstp.bit.sd2CkStp)						/**< Get the output a signal to stop control of the SD2 (Wifi) BUS CLOCK macro<br>
																													Values:
																													<ul><li>0:Output SD2 (Wifi) BUS CLOCK
																													<li>1:Stop SD2 (Wifi) BUS CLOCK</ul> */
#define DdExs_GET_SD3_BUS_CLOCK_STOP_CTRL()				(ioExstop.busckstp.bit.sd3CkStp)						/**< Get the output a signal to stop control of the SD3 (UHS2) BUS CLOCK macro<br>
																													Values:
																													<ul><li>0:Output SD3 (UHS2) BUS CLOCK
																													<li>1:Stop SD3 (UHS2) BUS CLOCK</ul> */
#define DdExs_GET_SD4_BUS_CLOCK_STOP_CTRL()				(ioExstop.busckstp.bit.sd4CkStp)						/**< Get the output a signal to stop control of the SD4 (UHS1 Card) BUS CLOCK macro<br>
																													Values:
																													<ul><li>0:Output SD4 (UHS1 Card) BUS CLOCK
																													<li>1:Stop SD4 (UHS1 Card) BUS CLOCK</ul> */
#define DdExs_GET_NETSEC_BUS_CLOCK_STOP_CTRL()		(ioExstop.busckstp.bit.netsecCkStp)					/**< Get the output a signal to stop control of the NETSEC BUS CLOCK macro<br>
																													Values:
																													<ul><li>0:Output NETSEC BUS CLOCK
																													<li>1:Stop NETSEC BUS CLOCK</ul> */
#define DdExs_GET_RELC_BUS_CLOCK_STOP_CTRL()			(ioExstop.busckstp.bit.relcCkStp)						/**< Get the output a signal to stop control of the RELC BUS CLOCK macro<br>
																													Values:
																													<ul><li>0:Output RELC BUS CLOCK
																													<li>1:Stop RELC BUS CLOCK</ul> */
// nsecCkstp
#define DdExs_GET_NETSEC_PTPCLK_STOP_CTRL_NETSEC_PTPSTP()	(ioExstop.nsecCkstp.bit.netsecPtpStp)					/**< Get the output a signal to stop control of the PTP_CLK NETSEC macro<br>
																													Values:
																													<ul><li>0:Output PTP_CLK
																													<li>1:Stop PTP_CLK</ul> */
// emmcCkstp
#define DdExs_GET_EMMC_CKSTP_EMCLKSTP()				(ioExstop.emmcCkstp.bit.emClkStp)						/**< Get the output a signal to stop control of the MMC_BCLK_I<br>
																													Values:
																													<ul><li>0:Output MMC_BCLK_I
																													<li>1:Stop MMC_BCLK_I</ul> */
//TODO:emClkStp和emmcCkstp的命名雷同
// emDrvstr
#define DdExs_GET_EM_DRVSTR()						(ioExstop.emDrvstr.bit.emDsel)						/**< Get emDsel */
// emPvDtimec
#define DdExs_GET_EM_PV_DTIMEC()					(ioExstop.emPvDtimec.bit.pvDtimec)					/**< Get pvDtimec */
// emPvAmpbl
#define DdExs_GET_EM_PV_AMPBL()					(ioExstop.emPvAmpbl.bit.pvAmpbl)					/**< Get pvAmpbl */
// emCrSlottype
#define DdExs_GET_EM_CR_SLOTTYPE()				(ioExstop.emCrSlottype.bit.crSlottype)				/**< Get crSlottype */
// emCrBclkfreq
#define DdExs_GET_EM_CR_BCLKFREQ()			(ioExstop.emCrBclkfreq.bit.crBclkfreq)				/**< Get crBclkfreq */
// emCddet
#define DdExs_GET_EM_CDDET_EMCD()			(ioExstop.emCddet.bit.emcd)							/**< Get emcd */
#define DdExs_GET_EM_CDDET_EMPHYLK()		(ioExstop.emCddet.bit.emphylk)						/**< Get emphylk */
// usb2Ckctl
#define DdExs_GET_USB2_CKCTL_HDC_HCLKEN()			(ioExstop.usb2Ckctl.bit.hdcHclken)					/**< Get the state of USB2.0 core(IP) Device clock<br>
																													Values:
																													<ul><li>0:clock stop
																													<li>1:clock run</ul> */
#define DdExs_GET_USB2_CKCTL_HO_HCLKEN()				(ioExstop.usb2Ckctl.bit.hoHclken)					/**< Get the state of USB2.0 core(IP) Host clock<br>
																													Values:
																													<ul><li>0:clock stop
																													<li>1:clock run</ul> */
// usb2Rctl
#define DdExs_GET_USB2_RCTL_HDC_SRST()						(ioExstop.usb2Rctl.bit.hdcSrst)						/**< Get the reset state of USB2.0 core(IP) Device clock<br>
																													Values:
																													<ul><li>0:reset is set.
																													<li>1:reset is released.</ul> */
#define DdExs_GET_USB2_RCTL_HO_SRST()						(ioExstop.usb2Rctl.bit.hoSrst)						/**< Get hoSrst */
// usb2Anpd
#define DdExs_GET_USB2_ANPD_ANPD()							(ioExstop.usb2Anpd.bit.anpd)							/**< Get anpd */
// usb2Hfsel
#define DdExs_GET_USB2_HFSEL_HF_SEL()						(ioExstop.usb2Hfsel.bit.hfSel)						/**< Get hfSel */
// usb2Fsel
#define DdExs_GET_USB2_FSEL_FSEL()								(ioExstop.usb2Fsel.bit.fsel)							/**< Get fsel */
#define DdExs_GET_USB2_FSEL_PLLBTUNE()					(ioExstop.usb2Fsel.bit.pllbtune)						/**< Get pllbtune */

// usb2EhciSb
#define DdExs_GET_USB2_EHCI_SB_EHCI_XFER_CNT_O()				(ioExstop.usb2EhciSb.bit.ehciXferCntO)			/**< Get ehciXferCntO */
#define DdExs_GET_USB2_EHCI_SB_EHCI_XFER_PRDC_O()				(ioExstop.usb2EhciSb.bit.ehciXferPrdcO)			/**< Get ehciXferPrdcO */
#define DdExs_GET_USB2_EHCI_SB_EHCI_EHCI_BUFACC_O()			(ioExstop.usb2EhciSb.bit.ehciBufaccO)				/**< Get ehciBufaccO */
#define DdExs_GET_USB2_EHCI_SB_EHCI_MCU_INC_FRDX_O()		(ioExstop.usb2EhciSb.bit.mcuIncFrdxO)				/**< Get mcuIncFrdxO */
#define DdExs_GET_USB2_EHCI_SB_EHCI_EOR_RUNSTOP_O()		(ioExstop.usb2EhciSb.bit.eorRunstopO)				/**< Get eorRunstopO */
#define DdExs_GET_USB2_EHCI_SB_EHCI_EHCI_USBSTS_O()			(ioExstop.usb2EhciSb.bit.ehciUsbstsO)				/**< Get ehciUsbstsO */

// usb2EhciStrap
#define DdExs_GET_USB2_EHCI_STRAP_SS_FADJ_HOST_I()			(ioExstop.usb2EhciStrap.bit.ssFadjHostI)			/**< Get ssFadjHostI */
#define DdExs_GET_USB2_EHCI_STRAP_SS_FLADJ_VAL_I()			(ioExstop.usb2EhciStrap.bit.ssFladjValI)			/**< Get ssFladjValI */

// usb2OhciIf
#define DdExs_GET_USB2_OHCI_IF_OHCI_CLKSEL_I()					(ioExstop.usb2OhciIf.bit.ohciClkselI)				/**< Get ohciClkselI */
#define DdExs_GET_USB2_OHCI_IF_UTMI_SUSPEND_O_N()		(ioExstop.usb2OhciIf.bit.utmiSuspendON)			/**< Get utmiSuspendON */
#define DdExs_GET_USB2_OHCI_IF_OHCI_GSUSPEND_O()			(ioExstop.usb2OhciIf.bit.ohciGsuspendO)			/**< Get ohciGsuspendO */
#define DdExs_GET_USB2_OHCI_IF_OHCI_RWE_O()						(ioExstop.usb2OhciIf.bit.ohciRweO)					/**< Get ohciRweO */
#define DdExs_GET_USB2_OHCI_IF_OHCI_RMTWKP_O()				(ioExstop.usb2OhciIf.bit.ohciRmtwkpO)				/**< Get ohciRmtwkpO */
#define DdExs_GET_USB2_OHCI_IF_OHCI_DRWE_O()					(ioExstop.usb2OhciIf.bit.ohciDrweO)				/**< Get ohciDrweO */
#define DdExs_GET_USB2_OHCI_IF_OHCI_CCS_O()						(ioExstop.usb2OhciIf.bit.ohciCcsO)					/**< Get ohciCcsO */
#define DdExs_GET_USB2_OHCI_IF_OHCI_SOF_O_N()					(ioExstop.usb2OhciIf.bit.ohciSofON)				/**< Get ohciSofON */
#define DdExs_GET_USB2_OHCI_IF_OHCI_BUFACC_O()				(ioExstop.usb2OhciIf.bit.ohciBufaccO)				/**< Get ohciBufaccO */

// usb2AhbSlvif
#define DdExs_GET_USB2_AHB_SLVIF_REG_RDY_O()					(ioExstop.usb2AhbSlvif.bit.regRdyO)				/**< Get regRdyO */

// usb2Lmodset
#define DdExs_GET_USB2_LMODSET_SS_ENA_INCR4_I()				(ioExstop.usb2Lmodset.bit.ssEnaIncr4I)				/**< Get ssEnaIncr4I */
#define DdExs_GET_USB2_LMODSET_SS_ENA_INCR8_I()				(ioExstop.usb2Lmodset.bit.ssEnaIncr8I)				/**< Get ssEnaIncr8I */
#define DdExs_GET_USB2_LMODSET_SS_ENA_INCR16_I()			(ioExstop.usb2Lmodset.bit.ssEnaIncr16I)			/**< Get ssEnaIncr16I */
#define DdExs_GET_USB2_LMODSET_SS_ENA_INC_AL_I()			(ioExstop.usb2Lmodset.bit.ssEnaIncAlI)			/**< Get ssEnaIncAlI */
#define DdExs_GET_USB2_LMODSET_SS_EHCI64B_EN_I()			(ioExstop.usb2Lmodset.bit.ssEhci64bEnI)			/**< Get ssEhci64bEnI */

// usb2Pmodset
#define DdExs_GET_USB2_PMODSET_RPDPEN_I()			(ioExstop.usb2Pmodset.bit.rpdpenI)					/**< Get rpdpenI */
#define DdExs_GET_USB2_PMODSET_RPDMEN_I()			(ioExstop.usb2Pmodset.bit.rpdmenI)					/**< Get rpdmenI */

// usb2HptCtl
#define DdExs_GET_USB2_HPT_CTL_USB2_EHPT()			(ioExstop.usb2HptCtl.bit.usb2Ehpt)					/**< Get usb2Ehpt */
#define DdExs_GET_USB2_HPT_CTL_USB2_OHPT()			(ioExstop.usb2HptCtl.bit.usb2Ohpt)					/**< Get usb2Ohpt */

// usb2Idvbusctl
#define DdExs_GET_USB2_IDVBUSCTL_USB2_IDPU_VAL()			(ioExstop.usb2Idvbusctl.bit.usb2IdpuVal)			/**< Get usb2IdpuVal */
#define DdExs_GET_USB2_IDVBUSCTL_USB2_IDPU_SEL()			(ioExstop.usb2Idvbusctl.bit.usb2IdpuSel)			/**< Get usb2IdpuSel */
#define DdExs_GET_USB2_IDVBUSCTL_USB2_ID_SEL()				(ioExstop.usb2Idvbusctl.bit.usb2IdSel)				/**< Get usb2IdSel */
#define DdExs_GET_USB2_IDVBUSCTL_USB2_ID_VAL()				(ioExstop.usb2Idvbusctl.bit.usb2IdVal)				/**< Get usb2IdVal */
#define DdExs_GET_USB2_IDVBUSCTL_USB2_VB_SEL()				(ioExstop.usb2Idvbusctl.bit.usb2VbSel)				/**< Get usb2VbSel */
#define DdExs_GET_USB2_IDVBUSCTL_USB2_VB_VAL()				(ioExstop.usb2Idvbusctl.bit.usb2VbVal)				/**< Get usb2VbVal */
#define DdExs_GET_USB2_IDVBUSCTL_USB2_VBDET_SEL()			(ioExstop.usb2Idvbusctl.bit.usb2VbdetSel)			/**< Get usb2VbdetSel */
#define DdExs_GET_USB2_IDVBUSCTL_USB2_VBDET_VAL()			(ioExstop.usb2Idvbusctl.bit.usb2VbdetVal)			/**< Get usb2VbdetVal */

// usb2Hdmac1
#define DdExs_GET_USB2_HDMAC1_HDMAC_BC1()						(ioExstop.usb2Hdmac1.bit.hdmacBc1)					/**< Get hdmacBc1 */
#define DdExs_GET_USB2_HDMAC1_HDMAC_BT1()						(ioExstop.usb2Hdmac1.bit.hdmacBt1)					/**< Get hdmacBt1 */
#define DdExs_GET_USB2_HDMAC1_HDMAC_MS1()					(ioExstop.usb2Hdmac1.bit.hdmacMs1)					/**< Get hdmacMs1 */

// usb2Hdmac2
#define DdExs_GET_USB2_HDMAC2_HDMAC_BC2()						(ioExstop.usb2Hdmac2.bit.hdmacBc2)					/**< Get hdmacBc2 */
#define DdExs_GET_USB2_HDMAC2_HDMAC_BT2()						(ioExstop.usb2Hdmac2.bit.hdmacBt2)					/**< Get hdmacBt2 */
#define DdExs_GET_USB2_HDMAC2_HDMAC_MS2()					(ioExstop.usb2Hdmac2.bit.hdmacMs2)					/**< Get hdmacMs2 */

// usb2Dmafsm1
#define DdExs_GET_USB2_DMAFSM1_FSMRST1()								(ioExstop.usb2Dmafsm1.bit.fsmrst1)					/**< Get fsmrst1 */
#define DdExs_GET_USB2_DMAFSM1_DMA_TRANS_STATE1()			(ioExstop.usb2Dmafsm1.bit.dmaTransState1)			/**< Get dmaTransState1 */

// usb2Dmafsm2
#define DdExs_GET_USB2_DMAFSM2_FSMRST2()								(ioExstop.usb2Dmafsm2.bit.fsmrst2)					/**< Get fsmrst2 */
#define DdExs_GET_USB2_DMAFSM2_DMA_TRANS_STATE2()			(ioExstop.usb2Dmafsm2.bit.dmaTransState2)			/**< Get dmaTransState2 */

// usb3Ckctl
#define DdExs_GET_USB3_CKCTL_ACLKEN()			(ioExstop.usb3Ckctl.bit.aclken)						/**< Get aclken */

// usb3Rctl
#define DdExs_GET_USB3_RCTL_SFTRST()				(ioExstop.usb3Rctl.bit.sftrst)						/**< Get sftrst */
#define DdExs_GET_USB3_PHY_RESET_N()				(ioExstop.usb3Rctl.bit.phyResetN)					/**< Get phyResetN */

// usb3RcvSns
#define DdExs_GET_USB3_RCV_SNS_ACJT_LEVEL()					(ioExstop.usb3RcvSns.bit.acjtLevel)					/**< Get acjtLevel */

// usb3Fsel
#define DdExs_GET_USB3_FSEL_FSEL3()										(ioExstop.usb3Fsel.bit.fsel3)							/**< Get fsel3 */
#define DdExs_GET_USB3_FSEL_MPLL_MULTIPLIER()				(ioExstop.usb3Fsel.bit.mpllMultiplier)				/**< Get mpllMultiplier */
#define DdExs_GET_USB3_FSEL_SSC_REF_CLK_SEL()				(ioExstop.usb3Fsel.bit.sscRefClkSel)				/**< Get sscRefClkSel */
#define DdExs_GET_USB3_FSEL_REF_CLKDIV2()						(ioExstop.usb3Fsel.bit.refClkdiv2)					/**< Get refClkdiv2 */

// usb3RfcCtl
#define DdExs_GET_USB3_RFC_CTL_REF_SSP_EN()					(ioExstop.usb3RfcCtl.bit.refSspEn)					/**< Get refSspEn */
#define DdExs_GET_USB3_RFC_CTL_REF_USE_PAD()				(ioExstop.usb3RfcCtl.bit.refUsePad)				/**< Get refUsePad */

// usb3HoIf
#define DdExs_GET_USB3_HO_IF_PCI_IMPLEMENT()				(ioExstop.usb3HoIf.bit.pciImplement)				/**< Get pciImplement */
#define DdExs_GET_USB3_HO_IF_HOST_MSI_ENABLE()			(ioExstop.usb3HoIf.bit.hostMsiEnable)				/**< Get hostMsiEnable */
#define DdExs_GET_USB3_HO_IF_XHC_BME()							(ioExstop.usb3HoIf.bit.xhcBme)						/**< Get xhcBme */
#define DdExs_GET_USB3_HO_IF_XHC_AC64()							(ioExstop.usb3HoIf.bit.xhcAc64)						/**< Get xhcAc64 */
#define DdExs_GET_USB3_HO_IF_HOST_SYSTEM_ERR()			(ioExstop.usb3HoIf.bit.hostSystemErr)				/**< Get hostSystemErr */

// usb3JtAdj
#define DdExs_GET_USB3_JT_ADJ_FLADJ_30MHZ_REG()			(ioExstop.usb3JtAdj.bit.fladj30mhzReg)				/**< Get fladj30mhzReg */
#define DdExs_GET_USB3_JT_ADJ_USB3_OVRCUR_EN()			(ioExstop.usb3JtAdj.bit.usb3OvrcurEn)				/**< Get usb3OvrcurEn */

// usb3Idvbusctl
#define DdExs_GET_USB3_IDVBUSCTL_USB3_IDPU_VAL()		(ioExstop.usb3Idvbusctl.bit.usb3IdpuVal)			/**< Get usb3IdpuVal */
#define DdExs_GET_USB3_IDVBUSCTL_USB3_ID_SEL()			(ioExstop.usb3Idvbusctl.bit.usb3IdSel)				/**< Get usb3IdSel */
#define DdExs_GET_USB3_IDVBUSCTL_USB3_ID_VAL()			(ioExstop.usb3Idvbusctl.bit.usb3IdVal)				/**< Get usb3IdVal */
#define DdExs_GET_USB3_IDVBUSCTL_USB3_VB_SEL()			(ioExstop.usb3Idvbusctl.bit.usb3VbSel)				/**< Get usb3VbSel */
#define DdExs_GET_USB3_IDVBUSCTL_USB3_VB_VAL()			(ioExstop.usb3Idvbusctl.bit.usb3VbVal)				/**< Get usb3VbVal */
#define DdExs_GET_USB3_IDVBUSCTL_USB3_VBDET_SEL()		(ioExstop.usb3Idvbusctl.bit.usb3VbdetSel)			/**< Get usb3VbdetSel */
#define DdExs_GET_USB3_IDVBUSCTL_USB3_VBDET_VAL()		(ioExstop.usb3Idvbusctl.bit.usb3VbdetVal)			/**< Get usb3VbdetVal */

// nfIpCtl
#define DdExs_GET_NF_IP_CTL_DSCV_INHIBIT()				(ioExstop.nfIpCtl.bit.dscvInhibit)					/**< Get dscvInhibit */
#define DdExs_GET_NF_IP_CTL_DSCV_IGNR_CRC()			(ioExstop.nfIpCtl.bit.dscvIgnrCrc)					/**< Get dscvIgnrCrc */
#define DdExs_GET_NF_IP_CTL_BOOT_EN()						(ioExstop.nfIpCtl.bit.bootEn)						/**< Get bootEn */
#define DdExs_GET_NF_IP_CTL_IDDQ_EN()						(ioExstop.nfIpCtl.bit.iddqEn)						/**< Get iddqEn */

// nfBtsqState
#define DdExs_GET_NF_BTSQ_STATE_INIT_FAIL()				(ioExstop.nfBtsqState.bit.initFail)					/**< Get initFail */
#define DdExs_GET_NF_BTSQ_STATE_BOOT_COMP()		(ioExstop.nfBtsqState.bit.bootComp)					/**< Get bootComp */
#define DdExs_GET_NF_BTSQ_STATE_BOOT_ERROR()		(ioExstop.nfBtsqState.bit.bootError)				/**< Get bootError */
#define DdExs_GET_NF_BTSQ_STATE_CTRL_BUSY()			(ioExstop.nfBtsqState.bit.ctrlBusy)					/**< Get ctrlBusy */

// nfRbValidTm
#define DdExs_GET_NF_RB_VALID_TM()				(ioExstop.nfRbValidTm.bit.rbValidTime)			/**< Get rbValidTime */
// nfPhyCtrlReg
#define DdExs_GET_NF_PHY_CTRL_REG()			(ioExstop.nfPhyCtrlReg.bit.phyCtrl)				/**< Get phyCtrl */
// nfPhyDqTim
#define DdExs_GET_NF_PHY_DQ_TIMING()		(ioExstop.nfPhyDqTim.bit.phyDqTiming)				/**< Get phyDqTiming */
// nfPhyDqsTim
#define DdExs_GET_NF_PHY_DQS_TIMING()		(ioExstop.nfPhyDqsTim.bit.phyDqsTiming)			/**< Get phyDqsTiming */
// nfPhyGtLpbk
#define DdExs_GET_NF_PHY_GT_LPBK_CTL()		(ioExstop.nfPhyGtLpbk.bit.phyGtLpbkCtl)			/**< Get phyGtLpbkCtl */
// nfPhyDllMctl
#define DdExs_GET_NF_PHY_DLL_MCTL()			(ioExstop.nfPhyDllMctl.bit.phyDllMstCtl)			/**< Get phyDllMstCtl */
// nfPhyDllSctl
#define DdExs_GET_NF_PHY_DLL_SCTL()			(ioExstop.nfPhyDllSctl.bit.phyDllSlvCtl)			/**< Get phyDllSlvCtl */

// nfBootEccCtl
#define DdExs_GET_NF_BOOT_ECC_CTL_SEC_SIZ()			(ioExstop.nfBootEccCtl.bit.bootEccSecSiz)		/**< Get bootEccSecSiz */
#define DdExs_GET_NF_BOOT_ECC_CTL_CORR_STR()		(ioExstop.nfBootEccCtl.bit.btEccCorrStr)			/**< Get btEccCorrStr */
#define DdExs_GET_NF_BOOT_ECC_CTL_EN()					(ioExstop.nfBootEccCtl.bit.bootEccEn)				/**< Get bootEccEn */
#define DdExs_GET_NF_NFWPX_CNT()								(ioExstop.nfNfwpxCnt.bit.nfwpxCnt)					/**< Get nfwpxCnt */

// intstat
#define DdExs_GET_INTSTAT_SD2_RIS()					(ioExstop.intstat.bit.intstat00)		//TODO:	__intstat00	不符合规范所以改成intstat00,记得提醒同事		/**< Get SD2 (UHS1 Wifi) rising edge detection */
#define DdExs_GET_INTSTAT_SD2_FIS()					(ioExstop.intstat.bit.intstat01)						/**< Get SD2 (UHS1 Wifi) falling edge detection */
#define DdExs_GET_INTSTAT_SD3_RIS()					(ioExstop.intstat.bit.intstat02)						/**< Get SD3 (UHS2) rising edge detection */
#define DdExs_GET_INTSTAT_SD3_FIS()					(ioExstop.intstat.bit.intstat03)						/**< Get SD3 (UHS2) falling edge detection */
#define DdExs_GET_INTSTAT_SD4_RIS()					(ioExstop.intstat.bit.intstat04)						/**< Get SD4 (UHS1 Card) rising edge detection */
#define DdExs_GET_INTSTAT_SD4_FIS()					(ioExstop.intstat.bit.intstat05)						/**< Get SD4 (UHS1 Card) falling edge detection */
#define DdExs_GET_INTSTAT_PCIe0_RIS()				(ioExstop.intstat.bit.intstat06)						/**< Get PCIe0 rising edge detection */
#define DdExs_GET_INTSTAT_PCIe0_FIS()				(ioExstop.intstat.bit.intstat07)						/**< Get PCIe0 falling edge detection */
#define DdExs_GET_INTSTAT_PCIe1_RIS()				(ioExstop.intstat.bit.intstat08)						/**< Get PCIe1 rising edge detection */
#define DdExs_GET_INTSTAT_PCIe1_FIS()				(ioExstop.intstat.bit.intstat09)						/**< Get PCIe1 falling edge detection */
#define DdExs_GET_INTSTAT_USB2VBUS_RIS()		(ioExstop.intstat.bit.intstat10)						/**< Get USB2 VBUS rising edge detection */
#define DdExs_GET_INTSTAT_USB2VBUS_FIS()		(ioExstop.intstat.bit.intstat11)						/**< Get USB2 VBUS falling edge detection */
#define DdExs_GET_INTSTAT_USB2ID_RIS()			(ioExstop.intstat.bit.intstat12)						/**< Get USB2 ID rising edge detection */
#define DdExs_GET_INTSTAT_USB2ID_FIS()			(ioExstop.intstat.bit.intstat13)						/**< Get USB2 ID falling edge detection */
#define DdExs_GET_INTSTAT_USB3VBUS_RIS()		(ioExstop.intstat.bit.intstat14)						/**< Get USB3 VBUS rising edge detection */
#define DdExs_GET_INTSTAT_USB3VBUS_FIS()		(ioExstop.intstat.bit.intstat15)						/**< Get USB3 VBUS falling edge detection */
#define DdExs_GET_INTSTAT_USB3ID_RIS()			(ioExstop.intstat.bit.intstat16)						/**< Get USB3 ID rising edge detection */
#define DdExs_GET_INTSTAT_USB3ID_FIS()			(ioExstop.intstat.bit.intstat17)						/**< Get USB3 ID falling edge detection */

typedef struct _DdExs                	DdExs;
typedef struct _DdExsPrivate 		DdExsPrivate;

struct _DdExs
{
	KObject parent;
};

KConstType 	dd_exs_get_type(void);
DdExs* 			dd_exs_get(void);

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/**
Set status of transition requests to LowPower mode of XDMAC.<br>
@param[in]  val		Setting value
					<ul><li> 0:LowPower mode request.
						<li> 1:Normal mode request.</ul>
@retval	None.
*/
void dd_exs_set_xdmac_lowpower_ctl_csysreq(DdExs *self, kulong val);

/**
Set reset control of nf_rst_n terminal.<br>
@param[in]  *val Setting value.
					<ul><li> 0:nf_rst_n terminal reset is released.
						<li> 1:nf_rst_n terminal reset is set.</ul>
@retval	None.
*/
void dd_exs_set_nf_rst_n_soft_reset(DdExs *self, kulong val);

/**
Set reset control of bch_rst_n terminal.<br>
@param[in]  *val Setting value
					<ul><li> 0:bch_rst_n terminal reset is released.
						<li> 1:bch_rst_n terminal reset is set.</ul>
@retval	None.
*/
void dd_exs_set_bch_rst_n_soft_reset(DdExs *self, kulong val);

/**
Set reset control of reg_rst_n terminal.<br>
@param[in]  *val Setting value
					<ul><li> 0:reg_rst_n terminal reset is released.
						<li> 1:reg_rst_n terminal reset is set.</ul>
@retval	None.
*/
void dd_exs_set_reg_rst_n_soft_reset(DdExs *self, kulong val);

/**
Set reset control of NETSEC macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:NETSEC macro reset is released.
						<li> 1:NETSEC macro reset is set.</ul>
@retval	None.
*/
void dd_exs_set_netsec_soft_reset(DdExs *self, kulong val);

/**
Set reset control of eMMC macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:eMMC macro reset is released.
						<li> 1:eMMC macro reset is set.</ul>
@retval	None.
*/
void dd_exs_set_emmc_soft_reset(DdExs *self, kulong val);

/**
Set reset control of RELC macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:RELC macro reset is released.
						<li> 1:RELC macro reset is set.</ul>
@retval	None.
*/
void dd_exs_set_relc_soft_reset(DdExs *self, kulong val);

/**
Set reset control of Card Debounce SD3 (UHS2).<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
					<ul><li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_sd3_cd_debounce_soft_reset(DdExs *self, kulong val);

/**
Set reset control of Card Debounce SD4 (UHS1 Card).<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_sd4_cd_debounce_soft_reset(DdExs *self, kulong val);

/**
Set reset control of Card Debounce PCIe0.<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_pcie0_cd_debounce_soft_reset(DdExs *self, kulong val);

/**
Set reset control of Card Debounce PCIe1.<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_pcie1_cd_debounce_soft_reset(DdExs *self, kulong val);

/**
Set reset control of Card Debounce USB2 VBUS.<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_usb2vbus_cd_debounce_soft_reset(DdExs *self, kulong val);

/**
Set reset control of Card Debounce USB2 ID.<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_usb2id_cd_debounce_soft_reset(DdExs *self, kulong val);

/**
Set reset control of Card Debounce USB3 VBUS.<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_usb3vbus_cd_debounce_soft_reset(DdExs *self, kulong val);

/**
Set reset control of Card Debounce USB3 ID.<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_usb3id_cd_debounce_soft_reset(DdExs *self, kulong val);

/**
Set SD3(UHS2) Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the SD3(UHS2) detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the SD3(UHS2) detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_sd3_rim(DdExs *self, kulong val);

/**
Set SD3(UHS2) Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the SD3(UHS2) detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the SD3(UHS2) detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_sd3_fim(DdExs *self, kulong val);

/**
Set SD4(UHS1 Card) Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the SD4(UHS1 Card) detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the SD4(UHS1 Card) detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_sd4_rim(DdExs *self, kulong val);

/**
Set SD4(UHS1 Card) Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the SD4(UHS1 Card) detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the SD4(UHS1 Card) detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_sd4_fim(DdExs *self, kulong val);

/**
Set PCIe0 Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the PCIe0 detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the PCIe0 detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_pcie0_rim(DdExs *self, kulong val);

/**
Set PCIe0 Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the PCIe0 detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the PCIe0 detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_pcie0_fim(DdExs *self, kulong val);

/**
Set PCIe1 Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the PCIe1 detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the PCIe1 detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_pcie1_rim(DdExs *self, kulong val);

/**
Set PCIe1 Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the PCIe1 detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the PCIe1 detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_pcie1_fim(DdExs *self, kulong val);

/**
Set USB2 VBUS Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB2 VBUS detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the USB2 VBUS detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb2vbus_rim(DdExs *self, kulong val);

/**
Set USB2 VBUS Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB2 VBUS detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the USB2 VBUS detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb2vbus_fim(DdExs *self, kulong val);

/**
Set USB2 ID Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB2 ID detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the USB2 ID detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb2id_rim(DdExs *self, kulong val);

/**
Set USB2 ID Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB2 ID detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the USB2 ID detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb2id_fim(DdExs *self, kulong val);

/**
Set USB3 VBUS Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB3 VBUS detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the USB3 VBUS detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb3vbus_rim(DdExs *self, kulong val);

/**
Set USB3 VBUS Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB3 VBUS detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the USB3 VBUS detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb3vbus_fim(DdExs *self, kulong val);

/**
Set USB3 ID Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB3 ID detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the USB3 ID detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb3id_rim(DdExs *self, kulong val);

/**
Set USB3 ID Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB3 ID detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the USB3 ID detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb3id_fim(DdExs *self, kulong val);

/**
Set SD3(UHS2) Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the SD3(UHS2) signal is turned off.
						<li> 1:The debounce of the SD3(UHS2) signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_sd3_en(DdExs *self, kulong val);

/**
Set SD4(UHS1 Card) Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the SD4(UHS1 Card) signal is turned off.
						<li> 1:The debounce of the SD4(UHS1 Card) signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_sd4_en(DdExs *self, kulong val);

/**
Set PCIe0 Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the PCIe0 signal is turned off.
						<li> 1:The debounce of the PCIe0 signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_pcie0_en(DdExs *self, kulong val);

/**
Set PCIe1 Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the PCIe1 signal is turned off.
						<li> 1:The debounce of the PCIe1 signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_pcie1_en(DdExs *self, kulong val);

/**
Set USB2 VBUS Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the USB2 VBUS signal is turned off.
						<li> 1:The debounce of the USB2 VBUS signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_usb2vbus_en(DdExs *self, kulong val);

/**
Set USB2 ID Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the USB2 ID signal is turned off.
						<li> 1:The debounce of the USB2 ID signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_usb2id_en(DdExs *self, kulong val);

/**
Set USB3 VBUS Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the USB3 VBUS signal is turned off.
						<li> 1:The debounce of the USB3 VBUS signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_usb3vbus_en(DdExs *self, kulong val);

/**
Set USB3 ID Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the USB3 ID signal is turned off.
						<li> 1:The debounce of the USB3 ID signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_usb3id_en(DdExs *self, kulong val);

/**
Set SD-Card ch3 Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_sd3detim(DdExs *self, kulong val);

/**
Set SD-Card ch4 Debounce time..<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_sd4detim(DdExs *self, kulong val);

/**
Set PCIe0 Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_pcie0detim(DdExs *self, kulong val);

/**
Set PCIe1 Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_pcie1detim(DdExs *self, kulong val);

/**
Set USB2 VBUS Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_usb2vbusdetim(DdExs *self, kulong val);

/**
Set USB2 ID Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_usb2iddetim(DdExs *self, kulong val);

/**
Set USB3 VBUS Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_usb3vbusdetim(DdExs *self, kulong val);

/**
Set USB3 ID Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_usb3iddetim(DdExs *self, kulong val);

/**
Set the mode setting of the card detection SD3(UHS2).<br>
param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the SD3(UHS2) signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the SD3(UHS2) signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_sd3_mod(DdExs *self, kulong val);

/**
Set the mode setting of the card detection SD4(UHS1 Card).<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the SD4(UHS1 Card) signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the SD4(UHS1 Card) signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_sd4_mod(DdExs *self, kulong val);

/**
Set the mode setting of the card detection PCIe0.<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the PCIe0 signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the PCIe0 signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_pcie0_mod(DdExs *self, kulong val);

/**
Set the mode setting of the card detection PCIe1.<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the PCIe1 signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the PCIe1 signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_pcie1_mod(DdExs *self, kulong val);

/**
Set the mode setting of the card detection USB2 VBUS.<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the USB2 VBUS signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the USB2 VBUS signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_usb2vbus_mod(DdExs *self, kulong val);

/**
Set the mode setting of the card detection USB2 ID.<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the USB2 ID signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the USB2 ID signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_usb2id_mod(DdExs *self, kulong val);

/**
Set the mode setting of the card detection USB3 VBUS.<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the USB3 VBUS signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the USB3 VBUS signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_usb3vbus_mod(DdExs *self, kulong val);

/**
Set the mode setting of the card detection USB3 ID.<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the USB3 ID signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the USB3 ID signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_usb3id_mod(DdExs *self, kulong val);

/**
Set the RELC expanded data read side HPROT setting(Data/Opcode).<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_set_relc_hprot_read(DdExs *self, kulong val);

/**
Set the RELC expanded data write side HPROT setting(Data/Opcode).<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_set_relc_hprot_write(DdExs *self, kulong val);

/**
Set SD2(UHS1 Wifi) macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_sd2(DdExs *self, kulong val);

/**
Set SD3(UHS2) macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_sd3(DdExs *self, kulong val);

/**
Set SD4(UHS1 Card) macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_sd4(DdExs *self, kulong val);

/**
Set Nand Flash macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_nf(DdExs *self, kulong val);

/**
Set RELC macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_relc(DdExs *self, kulong val);

/**
Set NETSEC macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_netsec(DdExs *self, kulong val);

/**
Set USB2 macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_usb2(DdExs *self, kulong val);

/**
Set USB3 macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_usb3(DdExs *self, kulong val);

/**
Set PCIE0 macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_pcie0(DdExs *self, kulong val);

#ifdef __cplusplus
}
#endif

#endif /* __DD_EXS_H__ */
