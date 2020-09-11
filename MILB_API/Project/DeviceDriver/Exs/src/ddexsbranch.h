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
*2、将dd_exs.h里将后面的个共有方法放在这里,将前面部分定义放在这里(前20个定义在ddexsbranch.c中有用到其他的宏和定义均在别的类里用
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __DD_EXS_BRANCH_H__
#define __DD_EXS_BRANCH_H__

#include <klib.h>
#include "ddim_typedef.h"
#include "driver_common.h"
#include "ddarm.h"
#include "ddexs.h"
#include "ddexsbranch.h"
#include "exstop.h"

#define DD_TYPE_EXS_BRANCH     (dd_exs_branch_get_type())
#define DD_EXS_BRANCH(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, DdExsBranch))
#define DD_IS_EXS_BRANCH(obj)  (K_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_EXS_BRANCH))

/**
// Error Code
*/
// CD INT STATUS
#define DdExsBranch_USB3ID_FIS_BIT			(1 << 17)	/**< Bit Location of intstat[17] on intstat */
#define DdExsBranch_USB3ID_RIS_BIT			(1 << 16)	/**< Bit Location of intstat[16] on intstat */
#define DdExsBranch_USB3VBUS_FIS_BIT		(1 << 15)	/**< Bit Location of intstat[15] on intstat */
#define DdExsBranch_USB3VBUS_RIS_BIT		(1 << 14)	/**< Bit Location of intstat[14] on intstat */
#define DdExsBranch_USB2ID_FIS_BIT			(1 << 13)	/**< Bit Location of intstat[13] on intstat */
#define DdExsBranch_USB2ID_RIS_BIT			(1 << 12)	/**< Bit Location of intstat[12] on intstat */
#define DdExsBranch_USB2VBUS_FIS_BIT		(1 << 11)	/**< Bit Location of intstat[11] on intstat */
#define DdExsBranch_USB2VBUS_RIS_BIT		(1 << 10)	/**< Bit Location of intstat[10] on intstat */
#define DdExsBranch_PCIE1_FIS_BIT				(1 << 9)	/**< Bit Location of intstat[9] on intstat */
#define DdExsBranch_PCIE1_RIS_BIT				(1 << 8)	/**< Bit Location of intstat[8] on intstat */
#define DdExsBranch_PCIE0_FIS_BIT				(1 << 7)	/**< Bit Location of intstat[7] on intstat */
#define DdExsBranch_PCIE0_RIS_BIT				(1 << 6)	/**< Bit Location of intstat[6] on intstat */
#define DdExsBranch_SD4_FIS_BIT					(1 << 5)	/**< Bit Location of intstat[5] on intstat */
#define DdExsBranch_SD4_RIS_BIT				(1 << 4)	/**< Bit Location of intstat[4] on intstat */
#define DdExsBranch_SD3_FIS_BIT					(1 << 3)	/**< Bit Location of intstat[3] on intstat */
#define DdExsBranch_SD3_RIS_BIT				(1 << 2)	/**< Bit Location of intstat[2] on intstat */
#define DdExsBranch_SD2_FIS_BIT					(1 << 1)	/**< Bit Location of intstat[1] on intstat */
#define DdExsBranch_SD2_RIS_BIT				(1 << 0)	/**< Bit Location of intstat[0] on intstat */

// CD INT MASK
#define DdExsBranch_USB3ID_FIM_BIT			(1 << 17)	/**< Bit Location of intMsk[17] on intMsk */
#define DdExsBranch_USB3ID_RIM_BIT		(1 << 16)	/**< Bit Location of intMsk[16] on intMsk */
#define DdExsBranch_USB3VBUS_FIM_BIT	(1 << 15)	/**< Bit Location of intMsk[15] on intMsk */
#define DdExsBranch_USB3VBUS_RIM_BIT	(1 << 14)	/**< Bit Location of intMsk[14] on intMsk */
#define DdExsBranch_USB2ID_FIM_BIT			(1 << 13)	/**< Bit Location of intMsk[13] on intMsk */
#define DdExsBranch_USB2ID_RIM_BIT		(1 << 12)	/**< Bit Location of intMsk[12] on intMsk */
#define DdExsBranch_USB2VBUS_FIM_BIT	(1 << 11)	/**< Bit Location of intMsk[11] on intMsk */
#define DdExsBranch_USB2VBUS_RIM_BIT	(1 << 10)	/**< Bit Location of intMsk[10] on intMsk */
#define DdExsBranch_PCIE1_FIM_BIT			(1 << 9)	/**< Bit Location of intMsk[9] on intMsk */
#define DdExsBranch_PCIE1_RIM_BIT			(1 << 8)	/**< Bit Location of intMsk[8] on intMsk */
#define DdExsBranch_PCIE0_FIM_BIT			(1 << 7)	/**< Bit Location of intMsk[7] on intMsk */
#define DdExsBranch_PCIE0_RIM_BIT			(1 << 6)	/**< Bit Location of intMsk[6] on intMsk */
#define DdExsBranch_SD4_FIM_BIT				(1 << 5)	/**< Bit Location of intMsk[5] on intMsk */
#define DdExsBranch_SD4_RIM_BIT				(1 << 4)	/**< Bit Location of intMsk[4] on intMsk */
#define DdExsBranch_SD3_FIM_BIT				(1 << 3)	/**< Bit Location of intMsk[3] on intMsk */
#define DdExsBranch_SD3_RIM_BIT				(1 << 2)	/**< Bit Location of intMsk[2] on intMsk */
#define DdExsBranch_INTMSK_01_BIT			(1 << 1)	/**< Bit Location of intMsk[1] on intMsk  (Reserved) */
#define DdExsBranch_INTMSK_00_BIT			(1 << 0)	/**< Bit Location of intMsk[0] on intMsk  (Reserved) */

// CD INT MONITOR
#define DdExsBranch_USB3ID_SIGMON2_BIT			(1 << 24)	/**< Bit Location of SIGMON2[8] on sigmon */
#define DdExsBranch_USB3VBUS_SIGMON2_BIT		(1 << 23)	/**< Bit Location of SIGMON2[7] on sigmon */
#define DdExsBranch_USB2ID_SIGMON2_BIT			(1 << 22)	/**< Bit Location of SIGMON2[6] on sigmon */
#define DdExsBranch_USB2VBUS_SIGMON2_BIT		(1 << 21)	/**< Bit Location of SIGMON2[5] on sigmon */
#define DdExsBranch_PCIE1_SIGMON2_BIT				(1 << 20)	/**< Bit Location of SIGMON2[4] on sigmon */
#define DdExsBranch_PCIE0_SIGMON2_BIT				(1 << 19)	/**< Bit Location of SIGMON2[3] on sigmon */
#define DdExsBranch_SD4_SIGMON2_BIT				(1 << 18)	/**< Bit Location of SIGMON2[2] on sigmon */
#define DdExsBranch_SD3_SIGMON2_BIT				(1 << 17)	/**< Bit Location of SIGMON2[1] on sigmon */
#define DdExsBranch_SIGMON2_00_BIT					(1 << 16)	/**< Bit Location of SIGMON2[0] on sigmon  (Reserved) */
#define DdExsBranch_USB3ID_SIGMON_BIT			(1 << 08)	/**< Bit Location of sigmon[8] on sigmon */
#define DdExsBranch_USB3VBUS_SIGMON_BIT		(1 << 07)	/**< Bit Location of sigmon[7] on sigmon */
#define DdExsBranch_USB2ID_SIGMON_BIT			(1 << 06)	/**< Bit Location of sigmon[6] on sigmon */
#define DdExsBranch_USB2VBUS_SIGMON_BIT		(1 << 05)	/**< Bit Location of sigmon[5] on sigmon */
#define DdExsBranch_PCIE1_SIGMON_BIT				(1 << 04)	/**< Bit Location of sigmon[4] on sigmon */
#define DdExsBranch_PCIE0_SIGMON_BIT				(1 << 03)	/**< Bit Location of sigmon[3] on sigmon */
#define DdExsBranch_SD4_SIGMON_BIT					(1 << 02)	/**< Bit Location of sigmon[2] on sigmon */
#define DdExsBranch_SD3_SIGMON_BIT					(1 << 01)	/**< Bit Location of sigmon[1] on sigmon */
#define DdExsBranch_SIGMON_00_BIT						(1 << 00)	/**< Bit Location of sigmon[0] on sigmon  (Reserved) */
#define DdExsBranch_SET_0										(0)			/**< SET_0 */
#define DdExsBranch_SET_1										(1)			/**< SET_1 */

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
// xdmacLpctrl
#define DdExsBranch_GET_XDMAC_LOWPOWER_CTL_CSYSREQ()			(ioExstop.xdmacLpctrl.bit.csysReq)						/**< Get status of transition requests to LowPower mode of XDMAC<br>
																													Values:
																													<ul><li>0:LowPower mode request
																													<li>1:Normal mode request </ul> */

#define DdExsBranch_GET_XDMAC_LOWPOWER_CTL_CSYSACK()				(ioExstop.xdmacLpctrl.bit.csysAck)						/**< Get acknowledge LowPower mode transition of XDMAC<br>
																													Values:
																													<ul><li>0:LowPower mode enabled
																													<li>1:Normal mode enabled</ul> */

#define DdExsBranch_GET_XDMAC_LOWPOWER_CTL_CACTIVE()				(ioExstop.xdmacLpctrl.bit.cActive)						/**< Get the state of the internal clock XDMAC<br>
																													Values:
																													<ul><li>0:The bus clock not request
																													<li>1:The bus clock request</ul> */

// softreset
#define DdExsBranch_GET_NF_RST_N_SOFT_RESET()				(ioExstop.softreset.bit.nfRstn	)						/**< Get status of reset control of nf_rst_n terminal<br>
																													Values:
																													<ul><li>0:nf_rst_n terminal reset is released
																													<li>1:nf_rst_n terminal reset is set</ul> */

#define DdExsBranch_GET_BCH_RST_N_SOFT_RESET()			(ioExstop.softreset.bit.nfRstnBch)						/**< Get status of reset control of bch_rst_n terminal<br>
																													Values:
																													<ul><li>0:bch_rst_n terminal reset is released
																													<li>1:bch_rst_n terminal reset is set</ul> */

#define DdExsBranch_GET_REG_RST_N_SOFT_RESET()			(ioExstop.softreset.bit.nfRstnReg)						/**< Get status of reset control of reg_rst_n terminal<br>
																													Values:
																													<ul><li>0:reg_rst_n terminal reset is released
																													<li>1:reg_rst_n terminal reset is set</ul> */

#define DdExsBranch_GET_NETSEC_SOFT_RESET()					(ioExstop.softreset.bit.netsecRst)						/**< Get status of reset control of NETSEC macro<br>
																													Values:
																													<ul><li>0:NETSEC macro reset is released
																													<li>1:NETSEC macro reset is set</ul> */

#define DdExsBranch_GET_EMMC_SOFT_RESET()						(ioExstop.softreset.bit.emcRst)						/**< Get status of reset control of eMMC macro<br>
																													Values:
																													<ul><li>0:eMMC macro reset is released
																													<li>1:eMMC macro reset is set</ul> */

#define DdExsBranch_GET_RELC_SOFT_RESET()						(ioExstop.softreset.bit.relcRst)						/**< Get status of reset control of RELC macro<br>
																													Values:
																													<ul><li>0:RELC macro reset is released
																													<li>1:RELC macro reset is set</ul> */

// softreset2
#define DdExsBranch_GET_SD3_CD_DEBOUNCE_SOFT_RESET()					(ioExstop.softreset2.bit.debrstxSd3)					/**< Get status of reset control of Card Debounce SD3 (UHS2)<br>
																													Values:
																													<ul><li>0:Card Debounce reset is released
																													<li>1:Card Debounce reset is set</ul> */

#define DdExsBranch_GET_SD4_CD_DEBOUNCE_SOFT_RESET()					(ioExstop.softreset2.bit.debrstxSd4)					/**< Get status of reset control of Card Debounce SD4 (UHS1 Card)<br>
																													Values:
																													<ul><li>0:Card Debounce reset is released
																													<li>1:Card Debounce reset is set</ul> */

#define DdExsBranch_GET_PCIE0_CD_DEBOUNCE_SOFT_RESET()				(ioExstop.softreset2.bit.debrstxPcie0)				/**< Get status of reset control of Card Debounce PCIe0<br>
																													Values:
																													<ul><li>0:Card Debounce reset is released
																													<li>1:Card Debounce reset is set</ul> */

#define DdExsBranch_GET_PCIE1_CD_DEBOUNCE_SOFT_RESET()				(ioExstop.softreset2.bit.debrstxPcie1)				/**< Get status of reset control of Card Debounce PCIe1<br>
																													Values:
																													<ul><li>0:Card Debounce reset is released
																													<li>1:Card Debounce reset is set</ul> */

#define DdExsBranch_GET_USB2VBUS_CD_DEBOUNCE_SOFT_RESET()		(ioExstop.softreset2.bit.debrstxUsb2Vbus)				/**< Get status of reset control of Card Debounce USB2 VBUS<br>
																													Values:
																													<ul><li>0:Card Debounce reset is released
																													<li>1:Card Debounce reset is set</ul> */

#define DdExsBranch_GET_USB2ID_CD_DEBOUNCE_SOFT_RESET()				(ioExstop.softreset2.bit.debrstxUsb2Id)				/**< Get status of reset control of Card Debounce USB2 ID<br>
																													Values:
																													<ul><li>0:Card Debounce reset is released
																													<li>1:Card Debounce reset is set</ul> */

#define DdExsBranch_GET_USB3VBUS_CD_DEBOUNCE_SOFT_RESET()		(ioExstop.softreset2.bit.debrstxUsb3Vbus)				/**< Get status of reset control of Card Debounce USB3 VBUS<br>
																													Values:
																													<ul><li>0:Card Debounce reset is released
																													<li>1:Card Debounce reset is set</ul> */

#define DdExsBranch_GET_USB3ID_CD_DEBOUNCE_SOFT_RESET()				(ioExstop.softreset2.bit.debrstxUsb3Id)				/**< Get status of reset control of Card Debounce USB3 ID<br>
																													Values:
																													<ul><li>0:Card Debounce reset is released
																													<li>1:Card Debounce reset is set</ul> */

// intMsk
#define DdExsBranch_GET_INTMSK_SD3_RIM()					(ioExstop.intMsk.bit.intMsk02)							/**< Get SD3(UHS2) Detect INT Mask(Rising Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the SD3(UHS2) detection rising edge detection factor is output
																													<li>1:The interrupt signal by the SD3(UHS2) detection rising edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_SD3_FIM()					(ioExstop.intMsk.bit.intMsk03)							/**< Get SD3(UHS2) Detect INT Mask(Falling Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the SD3(UHS2) detection falling edge detection factor is output
																													<li>1:The interrupt signal by the SD3(UHS2) detection falling edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_SD4_RIM()					(ioExstop.intMsk.bit.intMsk04)							/**< Get SD4(UHS1 Card) Detect INT Mask(Rising Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the SD4(UHS1 Card) detection rising edge detection factor is output
																													<li>1:The interrupt signal by the SD4(UHS1 Card) detection rising edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_SD4_FIM()					(ioExstop.intMsk.bit.intMsk05)							/**< Get SD4(UHS1 Card) Detect INT Mask(Falling Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the SD4(UHS1 Card) detection falling edge detection factor is output
																													<li>1:The interrupt signal by the SD4(UHS1 Card) detection falling edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_PCIE0_RIM()				(ioExstop.intMsk.bit.intMsk06)							/**< Get PCIe0 Detect INT Mask(Rising Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the PCIe0 detection rising edge detection factor is output
																													<li>1:The interrupt signal by the PCIe0 detection rising edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_PCIE0_FIM()				(ioExstop.intMsk.bit.intMsk07)							/**< Get PCIe0 Detect INT Mask(Falling Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the PCIe0 detection falling edge detection factor is output
																													<li>1:The interrupt signal by the PCIe0 detection falling edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_PCIE1_RIM()				(ioExstop.intMsk.bit.intMsk08)							/**< Get PCIe1 Detect INT Mask(Rising Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the PCIe1 detection rising edge detection factor is output
																													<li>1:The interrupt signal by the PCIe1 detection rising edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_PCIE1_FIM()				(ioExstop.intMsk.bit.intMsk09)							/**< Get PCIe1 Detect INT Mask(Falling Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the PCIe1 detection falling edge detection factor is output
																													<li>1:The interrupt signal by the PCIe1 detection falling edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_USB2VBUS_RIM()		(ioExstop.intMsk.bit.intMsk10)							/**< Get USB2 VBUS Detect INT Mask(Rising Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the USB2 VBUS detection rising edge detection factor is output
																													<li>1:The interrupt signal by the USB2 VBUS detection rising edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_USB2VBUS_FIM()		(ioExstop.intMsk.bit.intMsk11)							/**< Get USB2 VBUS Detect INT Mask(Falling Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the USB2 VBUS detection falling edge detection factor is output
																													<li>1:The interrupt signal by the USB2 VBUS detection falling edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_USB2ID_RIM()				(ioExstop.intMsk.bit.intMsk12)							/**< Get USB2 ID Detect INT Mask(Rising Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the USB2 ID detection rising edge detection factor is output
																													<li>1:The interrupt signal by the USB2 ID detection rising edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_USB2ID_FIM()				(ioExstop.intMsk.bit.intMsk13)							/**< Get USB2 ID Detect INT Mask(Falling Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the USB2 ID detection falling edge detection factor is output
																													<li>1:The interrupt signal by the USB2 ID detection falling edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_USB3VBUS_RIM()		(ioExstop.intMsk.bit.intMsk14)							/**< Get USB3 VBUS Detect INT Mask(Rising Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the USB3 VBUS detection rising edge detection factor is output
																													<li>1:The interrupt signal by the USB3 VBUS detection rising edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_USB3VBUS_FIM()		(ioExstop.intMsk.bit.intMsk15)							/**< Get USB3 VBUS Detect INT Mask(Falling Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the USB3 VBUS detection falling edge detection factor is output
																													<li>1:The interrupt signal by the USB3 VBUS detection falling edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_USB3ID_RIM()				(ioExstop.intMsk.bit.intMsk16)							/**< Get USB3 ID Detect INT Mask(Rising Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the USB3 ID detection rising edge detection factor is output
																													<li>1:The interrupt signal by the USB3 ID detection rising edge detection factor is mask</ul> */

#define DdExsBranch_GET_INTMSK_USB3ID_FIM()				(ioExstop.intMsk.bit.intMsk17)							/**< Get USB3 ID Detect INT Mask(Falling Edge)<br>
																													Values:
																													<ul><li>0:The interrupt signal by the USB3 ID detection falling edge detection factor factor is output
																													<li>1:The interrupt signal by the USB3 ID detection falling edge detection factor is mask</ul> */

// sigmon
#define DdExsBranch_GET_SIGMON_SD3_CD()					(ioExstop.sigmon.bit.sigmonSd3)						/**< Get SD3(UHS2) Detect Monitor for after the debounce */
#define DdExsBranch_GET_SIGMON_SD4_CD()					(ioExstop.sigmon.bit.sigmonSd4)						/**< Get SD4(UHS1 Card) Detect Monitor for after the debounce */
#define DdExsBranch_GET_SIGMON_PCIE0_CD()					(ioExstop.sigmon.bit.sigmonPcie0)						/**< Get PCIE0 Detect Monitor for after the debounce */
#define DdExsBranch_GET_SIGMON_PCIE1_CD()					(ioExstop.sigmon.bit.sigmonPcie1)						/**< Get PCIE1 Detect Monitor for after the debounce */
#define DdExsBranch_GET_SIGMON_USB2VBUS_CD()		(ioExstop.sigmon.bit.sigmonUsb2Vbus)					/**< Get USB2 VBUS Detect Monitor for after the debounce */
#define DdExsBranch_GET_SIGMON_USB2ID_CD()				(ioExstop.sigmon.bit.sigmonUsb2Id)					/**< Get USB2 ID Detect Monitor for after the debounce */
#define DdExsBranch_GET_SIGMON_USB3VBUS_CD()		(ioExstop.sigmon.bit.sigmonUsb3Vbus)					/**< Get USB3 VBUS Detect Monitor for after the debounce */
#define DdExsBranch_GET_SIGMON_USB3ID_CD()				(ioExstop.sigmon.bit.sigmonUsb3Id)					/**< Get USB3 ID Detect Monitor for after the debounce */
#define DdExsBranch_GET_SIGMON2_SD3_CD()					(ioExstop.sigmon.bit.sigmon2Sd3)						/**< Get SD3(UHS2) Detect Monitor for chip terminal status */
#define DdExsBranch_GET_SIGMON2_SD4_CD()					(ioExstop.sigmon.bit.sigmon2Sd4)						/**< Get SD4(UHS1 Card) Detect Monitor for chip terminal status */
#define DdExsBranch_GET_SIGMON2_PCIE0_CD()				(ioExstop.sigmon.bit.sigmon2Pcie0)					/**< Get PCIE0 Detect Monitor for chip terminal status */
#define DdExsBranch_GET_SIGMON2_PCIE1_CD()				(ioExstop.sigmon.bit.sigmon2Pcie1)					/**< Get PCIE1 Detect Monitor for chip terminal status */
#define DdExsBranch_GET_SIGMON2_USB2VBUS_CD()		(ioExstop.sigmon.bit.sigmon2Usb2Vbus)					/**< Get USB2 VBUS Detect Monitor for chip terminal status */
#define DdExsBranch_GET_SIGMON2_USB2ID_CD()			(ioExstop.sigmon.bit.sigmon2Usb2Id)					/**< Get USB2 ID Detect Monitor for chip terminal status */
#define DdExsBranch_GET_SIGMON2_USB3VBUS_CD()		(ioExstop.sigmon.bit.sigmon2Usb3Vbus)					/**< Get USB3 VBUS Detect Monitor for chip terminal status */
#define DdExsBranch_GET_SIGMON2_USB3ID_CD()			(ioExstop.sigmon.bit.sigmon2Usb3Id)					/**< Get USB3 ID Detect Monitor for chip terminal status */

// deben
#define DdExsBranch_GET_DEBEN_SD3_EN()							(ioExstop.deben.bit.debenSd3)							/**< Get SD3(UHS2) Debounce ON/OFF<br>
																													Values:
																													<ul><li>0:The debounce of the SD3(UHS2) signal is turned off
																													<li>1:The debounce of the SD3(UHS2) signal is turned on</ul> */

#define DdExsBranch_GET_DEBEN_SD4_EN()							(ioExstop.deben.bit.debenSd4)							/**< Get SD4(UHS1 Card) Debounce ON/OFF<br>
																													Values:
																													<ul><li>0:The debounce of the SD4(UHS1 Card) signal is turned off
																													<li>1:The debounce of the SD4(UHS1 Card) signal is turned on</ul> */

#define DdExsBranch_GET_DEBEN_PCIE0_EN()						(ioExstop.deben.bit.debenPcie0)						/**< Get PCIe0 Debounce ON/OFF<br>
																													Values:
																													<ul><li>0:The debounce of the PCIe0 signal is turned off
																													<li>1:The debounce of the PCIe0 signal is turned on</ul> */

#define DdExsBranch_GET_DEBEN_PCIE1_EN()						(ioExstop.deben.bit.debenPcie1)						/**< Get PCIe1 Debounce ON/OFF<br>
																													Values:
																													<ul><li>0:The debounce of the PCIe1 signal is turned off
																													<li>1:The debounce of the PCIe1 signal is turned on</ul> */

#define DdExsBranch_GET_DEBEN_USB2VBUS_EN()				(ioExstop.deben.bit.debenUsb2Vbus)					/**< Get USB2 VBUS Debounce ON/OFF<br>
																													Values:
																													<ul><li>0:The debounce of the USB2 VBUS signal is turned off
																													<li>1:The debounce of the USB2 VBUS signal is turned on</ul> */

#define DdExsBranch_GET_DEBEN_USB2ID_EN()						(ioExstop.deben.bit.debenUsb2Id)						/**< Get USB2 ID Debounce ON/OFF<br>
																													Values:
																													<ul><li>0:The debounce of the USB2 ID signal is turned off
																													<li>1:The debounce of the USB2 ID signal is turned on</ul> */

#define DdExsBranch_GET_DEBEN_USB3VBUS_EN()				(ioExstop.deben.bit.debenUsb3Vbus)					/**< Get USB3 VBUS Debounce ON/OFF<br>
																													Values:
																													<ul><li>0:The debounce of the USB3 VBUS signal is turned off
																													<li>1:The debounce of the USB3 VBUS signal is turned on</ul> */

#define DdExsBranch_GET_DEBEN_USB3ID_EN()						(ioExstop.deben.bit.debenUsb3Id)						/**< Get USB3 ID Debounce ON/OFF<br>
																													Values:
																													<ul><li>0:The debounce of the USB3 ID signal is turned off
																													<li>1:The debounce of the USB3 ID signal is turned on</ul> */

#define DdExsBranch_GET_DEBEN_SD3DETIM()						(ioExstop.deben.bit.sd3Detim)							/**< Get SD-Card ch3 Debounce time<br>
																													Values:
																													<ul><li>00:APBCLK 131072 cycles
																													<li>01:APBCLK 65536 cycles (131072 cycles /2)
																													<li>10:APBCLK 262144 cycles (131072 cycles *2)
																													<li>11:APBCLK 524288 cycles (131072 cycles *4)</ul> */

#define DdExsBranch_GET_DEBEN_SD4DETIM()						(ioExstop.deben.bit.sd4Detim)							/**< Get SD-Card ch4 Debounce time<br>
																													Values:
																													<ul><li>00:APBCLK 131072 cycles
																													<li>01:APBCLK 65536 cycles (131072 cycles /2)
																													<li>10:APBCLK 262144 cycles (131072 cycles *2)
																													<li>11:APBCLK 524288 cycles (131072 cycles *4)</ul> */

#define DdExsBranch_GET_DEBEN_PCIE0DETIM()					(ioExstop.deben.bit.pcie0Detim)						/**< Get PCIe0 Debounce time<br>
																													Values:
																													<ul><li>00:APBCLK 131072 cycles
																													<li>01:APBCLK 65536 cycles (131072 cycles /2)
																													<li>10:APBCLK 262144 cycles (131072 cycles *2)
																													<li>11:APBCLK 524288 cycles (131072 cycles *4)</ul> */

#define DdExsBranch_GET_DEBEN_PCIE1DETIM()					(ioExstop.deben.bit.pcie1Detim)						/**< Get PCIe1 Debounce time<br>
																													Values:
																													<ul><li>00:APBCLK 131072 cycles
																													<li>01:APBCLK 65536 cycles (131072 cycles /2)
																													<li>10:APBCLK 262144 cycles (131072 cycles *2)
																													<li>11:APBCLK 524288 cycles (131072 cycles *4)</ul> */

#define DdExsBranch_GET_DEBEN_USB2VBUSDETIM()			(ioExstop.deben.bit.usb2VbusDetim)						/**< Get USB2 VBUS Debounce time<br>
																													Values:
																													<ul><li>00:APBCLK 131072 cycles
																													<li>01:APBCLK 65536 cycles (131072 cycles /2)
																													<li>10:APBCLK 262144 cycles (131072 cycles *2)
																													<li>11:APBCLK 524288 cycles (131072 cycles *4)</ul> */

#define DdExsBranch_GET_DEBEN_USB2IDDETIM()				(ioExstop.deben.bit.usb2IdDetim)						/**< Get USB2 ID Debounce time<br>
																													Values:
																													<ul><li>00:APBCLK 131072 cycles
																													<li>01:APBCLK 65536 cycles (131072 cycles /2)
																													<li>10:APBCLK 262144 cycles (131072 cycles *2)
																													<li>11:APBCLK 524288 cycles (131072 cycles *4)</ul> */

#define DdExsBranch_GET_DEBEN_USB3VBUSDETIM()			(ioExstop.deben.bit.usb3VbusDetim)						/**< Get USB3 VBUS Debounce time<br>
																													Values:
																													<ul><li>00:APBCLK 131072 cycles
																													<li>01:APBCLK 65536 cycles (131072 cycles /2)
																													<li>10:APBCLK 262144 cycles (131072 cycles *2)
																													<li>11:APBCLK 524288 cycles (131072 cycles *4)</ul> */

#define DdExsBranch_GET_DEBEN_USB3IDDETIM()				(ioExstop.deben.bit.usb3IdDetim)						/**< Get USB3 ID Debounce time<br>
																													Values:
																													<ul><li>00:APBCLK 131072 cycles
																													<li>01:APBCLK 65536 cycles (131072 cycles /2)
																													<li>10:APBCLK 262144 cycles (131072 cycles *2)
																													<li>11:APBCLK 524288 cycles (131072 cycles *4)</ul> */

// cdinsmdctl
#define DdExsBranch_GET_CDINS_SD3_MOD()						(ioExstop.cdinsmdctl.bit.cdimodSd3)					/**< Get the mode setting of the card detection SD3(UHS2)<br>
																													Values:
																													<ul><li>0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the SD3(UHS2) signal
																													<li>1:After exiting reset at debounce circuit, generates an interrupt by the state of the SD3(UHS2) signal</ul> */

#define DdExsBranch_GET_CDINS_SD4_MOD()						(ioExstop.cdinsmdctl.bit.cdimodSd4)					/**< Get the mode setting of the card detection SD4(UHS1 Card)<br>
																													Values:
																													<ul><li>0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the SD4(UHS1 Card) signal
																													<li>1:After exiting reset at debounce circuit, generates an interrupt by the state of the SD4(UHS1 Card) signal</ul> */

#define DdExsBranch_GET_CDINS_PCIE0_MOD()						(ioExstop.cdinsmdctl.bit.cdimodPcie0)					/**< Get the mode setting of the card detection PCIe0<br>
																													Values:
																													<ul><li>0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the PCIe0 signal
																													<li>1:After exiting reset at debounce circuit, generates an interrupt by the state of the PCIe0 signal</ul> */

#define DdExsBranch_GET_CDINS_PCIE1_MOD()						(ioExstop.cdinsmdctl.bit.cdimodPcie1)					/**< Get the mode setting of the card detection PCIe1<br>
																													Values:
																													<ul><li>0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the PCIe1 signal
																													<li>1:After exiting reset at debounce circuit, generates an interrupt by the state of the PCIe1 signal</ul> */

#define DdExsBranch_GET_CDINS_USB2VBUS_MOD()			(ioExstop.cdinsmdctl.bit.cdimodUsb2Vbus)				/**< Get the mode setting of the card detection USB2 VBUS<br>
																													Values:
																													<ul><li>0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the USB2 VBUS signal
																													<li>1:After exiting reset at debounce circuit, generates an interrupt by the state of the USB2 VBUS signal</ul> */

#define DdExsBranch_GET_CDINS_USB2ID_MOD()					(ioExstop.cdinsmdctl.bit.cdimodUsb2Id)				/**< Get the mode setting of the card detection USB2 ID<br>
																													Values:
																													<ul><li>0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the USB2 ID signal
																													<li>1:After exiting reset at debounce circuit, generates an interrupt by the state of the USB2 ID signal</ul> */

#define DdExsBranch_GET_CDINS_USB3VBUS_MOD()			(ioExstop.cdinsmdctl.bit.cdimodUsb3Vbus)				/**< Get the mode setting of the card detection USB3 VBUS<br>
																													Values:
																													<ul><li>0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the USB3 VBUS signal
																													<li>1:After exiting reset at debounce circuit, generates an interrupt by the state of the USB3 VBUS signal</ul> */

#define DdExsBranch_GET_CDINS_USB3ID_MOD()					(ioExstop.cdinsmdctl.bit.cdimodUsb3Id)				/**< Get the mode setting of the card detection USB3 ID<br>
																													Values:
																													<ul><li>0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the USB3 ID signal
																													<li>1:After exiting reset at debounce circuit, generates an interrupt by the state of the USB3 ID signal</ul> */

// rlcHptCtl
#define DdExsBranch_GET_RELC_HPROT_Read()						(ioExstop.rlcHptCtl.bit.reRHpt)						/**< Get the RELC expanded data read side HPROT setting(Data/Opcode) */
#define DdExsBranch_GET_RELC_HPROT_Write()						(ioExstop.rlcHptCtl.bit.reWHpt)						/**< Get the RELC expanded data write side HPROT setting(Data/Opcode) */

typedef struct _DdExsBranch                DdExsBranch;
typedef struct _DdExsBranchPrivate DdExsBranchPrivate;

struct _DdExsBranch
{
	KObject parent;
};

KConstType 			dd_exs_branch_get_type(void);
DdExsBranch* 		dd_exs_branch_get(void);

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif


/**
Set usb2IdpuSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_idpu_sel(DdExsBranch *self, kulong val);

/**
Set usb2IdSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_id_sel(DdExsBranch *self, kulong val);

/**
Set usb2IdVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_id_val(DdExsBranch *self, kulong val);

/**
Set usb2VbSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_vb_sel(DdExsBranch *self, kulong val);

/**
Set usb2VbVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_vb_val(DdExsBranch *self, kulong val);

/**
Set usb2VbdetSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_vbdet_sel(DdExsBranch *self, kulong val);

/**
Set usb2VbdetVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_idvbusctl_usb2_vbdet_val(DdExsBranch *self, kulong val);

/**
Set hdmacBc1.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_hdmac1_hdmac_bc1(DdExsBranch *self, kulong val);

/**
Set hdmacBt1.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_hdmac1_hdmac_bt1(DdExsBranch *self, kulong val);

/**
Set hdmacMs1.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_hdmac1_hdmac_ms1(DdExsBranch *self, kulong val);

/**
Set hdmacBc2.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_hdmac2_hdmac_bc2(DdExsBranch *self, kulong val);

/**
Set hdmacBt2.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_hdmac2_hdmac_bt2(DdExsBranch *self, kulong val);

/**
Set hdmacMs2.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_hdmac2_hdmac_ms2(DdExsBranch *self, kulong val);

/**
Set fsmrst1.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_dmafsm1_fsmrst1(DdExsBranch *self, kulong val);

/**
Set fsmrst2.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb2_dmafsm2_fsmrst2(DdExsBranch *self, kulong val);

/**
Set aclken.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_ckctl_aclken(DdExsBranch *self, kulong val);

/**
Set sftrst.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_rctl_sftrst(DdExsBranch *self, kulong val);

/**
Set phyResetN.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_rctl_phy_reset_n(DdExsBranch *self, kulong val);

/**
Set acjtLevel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_rcv_sns_acjt_level(DdExsBranch *self, kulong val);

/**
Set fsel3.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_fsel_fsel3(DdExsBranch *self, kulong val);

/**
Set mpllMultiplier.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_fsel_mpll_multiplier(DdExsBranch *self, kulong val);

/**
Set sscRefClkSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_fsel_ssc_ref_clk_sel(DdExsBranch *self, kulong val);

/**
Set refClkdiv2.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_fsel_ref_clkdiv2(DdExsBranch *self, kulong val);

/**
Set refSspEn.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_rfc_ctl_ref_ssp_en(DdExsBranch *self, kulong val);

/**
Set refUsePad.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_rfc_ctl_ref_use_pad(DdExsBranch *self, kulong val);

/**
Set pciImplement.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_ho_if_pci_implement(DdExsBranch *self, kulong val);

/**
Set hostMsiEnable.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_ho_if_host_msi_enable(DdExsBranch *self, kulong val);

/**
Set xhcBme.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_ho_if_xhc_bme(DdExsBranch *self, kulong val);

/**
Set xhcAc64.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_ho_if_xhc_ac64(DdExsBranch *self, kulong val);

/**
Set fladj30mhzReg.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_jt_adj_fladj_30mhz_reg(DdExsBranch *self, kulong val);

/**
Set usb3OvrcurEn.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_jt_adj_usb3_ovrcur_en(DdExsBranch *self, kulong val);

/**
Set usb3IdpuVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_idpu_val(DdExsBranch *self, kulong val);

/**
Set usb3IdSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_id_sel(DdExsBranch *self, kulong val);

/**
Set usb3IdVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_id_val(DdExsBranch *self, kulong val);

/**
Set usb3VbSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_vb_sel(DdExsBranch *self, kulong val);

/**
Set usb3VbVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_vb_val(DdExsBranch *self, kulong val);

/**
Set usb3VbdetSel.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_vbdet_sel(DdExsBranch *self, kulong val);

/**
Set usb3VbdetVal.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_usb3_idvbusctl_usb3_vbdet_val(DdExsBranch *self, kulong val);

/**
Set dscvInhibit.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_ip_ctl_dscv_inhibit(DdExsBranch *self, kulong val);

/**
Set dscvIgnrCrc.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_ip_ctl_dscv_ignr_crc(DdExsBranch *self, kulong val);

/**
Set bootEn.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_ip_ctl_boot_en(DdExsBranch *self, kulong val);

/**
Set iddqEn.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_ip_ctl_iddq_en(DdExsBranch *self, kulong val);

/**
Set rbValidTime.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_rb_valid_tm(DdExsBranch *self, kulong val);

/**
Set phyCtrl.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_phy_ctrl_reg(DdExsBranch *self, kulong val);

/**
Set PHY_DQ_TIMENG.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_phy_dq_timing(DdExsBranch *self, kulong val);

/**
Set phyDqsTiming.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_phy_dqs_timing(DdExsBranch *self, kulong val);

/**
Set phyGtLpbkCtl.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_phy_gt_lpbk_ctl(DdExsBranch *self, kulong val);

/**
Set phyDllMstCtl.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_phy_dll_mctl(DdExsBranch *self, kulong val);

/**
Set phyDllSlvCtl.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_phy_dll_sctl(DdExsBranch *self, kulong val);

/**
Set bootEccSecSiz.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_boot_ecc_ctl_sec_siz(DdExsBranch *self, kulong val);

/**
Set btEccCorrStr.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_boot_ecc_ctl_corr_str(DdExsBranch *self, kulong val);

/**
Set bootEccEn.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_boot_ecc_ctl_en(DdExsBranch *self, kulong val);

/**
Set nfwpxCnt.<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_branch_set_nf_nfwpx_cnt(DdExsBranch *self, kulong val);

/**
The status of intstat of SD2_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_sd2_ris(DdExsBranch *self);

/**
The status of intstat of SD2_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_sd2_fis(DdExsBranch *self);

/**
The status of intstat of SD3_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_sd3_ris(DdExsBranch *self);

/**
The status of intstat of SD3_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_sd3_fis(DdExsBranch *self);

/**
The status of intstat of SD4_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_sd4_ris(DdExsBranch *self);

/**
The status of intstat of SD4_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_sd4_fis(DdExsBranch *self);

/**
The status of intstat of PCIe0_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_pcie0_ris(DdExsBranch *self);

/**
The status of intstat of PCIe0_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_pcie0_fis(DdExsBranch *self);

/**
The status of intstat of PCIe1_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_pcie1_ris(DdExsBranch *self);

/**
The status of intstat of PCIe1_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_pcie1_fis(DdExsBranch *self);

/**
The status of intstat of USB2VBUS_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb2vbus_ris(DdExsBranch *self);

/**
The status of intstat of USB2VBUS_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb2vbus_fis(DdExsBranch *self);

/**
The status of intstat of USB2ID_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb2id_ris(DdExsBranch *self);

/**
The status of intstat of USB2ID_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb2id_fis(DdExsBranch *self);

/**
The status of intstat of USB3VBUS_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb3vbus_ris(DdExsBranch *self);

/**
The status of intstat of USB3VBUS_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb3vbus_fis(DdExsBranch *self);

/**
The status of intstat of USB3ID_RIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb3id_ris(DdExsBranch *self);

/**
The status of intstat of USB3ID_FIS is cleared.<br>
@retval	None.
*/
void dd_exs_branch_clear_intstat_usb3id_fis(DdExsBranch *self);

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
void dd_exs_branch_int_handler(kulong *val);

#ifdef __cplusplus
}
#endif

#endif /* __DD_EXS_BRANCH_H__ */
