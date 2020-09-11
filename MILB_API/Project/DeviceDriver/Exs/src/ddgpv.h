/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :周洪
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、GPV (Global Programmers View) driver
*2、将dd_gpv.h更名为ddgpv.h
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __DD_GPV_H__
#define __DD_GPV_H__

#include <klib.h>
#include "driver_common.h"
#include "exstop.h"

#define DD_TYPE_GPV     (dd_gpv_get_type())
#define DD_GPV(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, DdGpv))
#define DD_IS_GPV(obj)  (K_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_GPV))
/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Return value of GPV processing result
#define	DdGpv_INPUT_PARAM_ERR		(D_DD_GPV | D_DDIM_INPUT_PARAM_ERROR)		/**< Input Parameter Error */
//在3个拆出中都有用到

// Max value of REMAP
#define DdGpv_REMAP_VAL_MAX			(255)

//未用
// Number of REMAP register
#define DdGpv_REMAP_NANDFLASH							(0x01)										/**< REMAP NANDFLASH Register Number */
#define DdGpv_REMAP_SD1										(0x02)										/**< REMAP SD1(eMMC) Register Number */
#define DdGpv_REMAP_SD3										(0x04)										/**< REMAP SD3(UHS2) Register Number */
#define DdGpv_REMAP_PCIE										(0x08)										/**< REMAP PCIe0/PCIe1 Register Number */
#define DdGpv_REMAP_USB3										(0x10)										/**< REMAP USB3.0 Register Number */
#define DdGpv_REMAP_SD_RELC_HDMAC_USB2		(0x20)										/**< REMAP SD2(UHS1 Wifi)/SD4(UHS1 Card)/SD3(UHS1)/RELC/HDMAC/USB2 Register Number */
#define DdGpv_REMAP_NETSEC									(0x40)										/**< REMAP NETSEC Register Number */

								/**< Remap Max Value */
//以下在3个拆出中都有用到
#define DdGpv_FMIB_VAL_MAX			(3)											/**< FMIB Max Value */
#define DdGpv_FM2_VAL_MAX				(1)											/**< FM2 Max Value */
#define DdGpv_FMA_VAL_MAX			(3)											/**< FMA Max Value */
#define DdGpv_FML_VAL_MAX				(3)											/**< FML Max Value */
#define DdGpv_WT_VAL_MAX				(8)											/**< WT Max Value */
#define DdGpv_AC_VAL_MAX				(3)											/**< AC Max Value */
#define DdGpv_FM_VAL_MAX				(3)											/**< FM Max Value */

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
/* M_Usb3_r_ib Registers */
#define DdGpv_GET_M_USB3_R_IB_FMIB()			(ioGpv.mUsb3RIb.fmib)			/**< Get M_Usb3_r_ib fn_mod_iss_bm */
#define DdGpv_GET_M_USB3_R_IB_FM2()				(ioGpv.mUsb3RIb.fm2)			/**< Get M_Usb3_r_ib fn_mod2 */
#define DdGpv_GET_M_USB3_R_IB_FM()				(ioGpv.mUsb3RIb.fm)			/**< Get M_Usb3_r_ib fn_mod */

/* M_Emmc_r_ib Registers */
#define DdGpv_GET_M_EMMC_R_IB_FMIB()			(ioGpv.mEmmcRIb.fmib)			/**< Get M_Emmc_r_ib fn_mod_iss_bm */
#define DdGpv_GET_M_EMMC_R_IB_FM2()			(ioGpv.mEmmcRIb.fm2)			/**< Get M_Emmc_r_ib fn_mod2 */
#define DdGpv_GET_M_EMMC_R_IB_FML()			(ioGpv.mEmmcRIb.fml)			/**< Get M_Emmc_r_ib fn_mod_lb */
#define DdGpv_GET_M_EMMC_R_IB_FM()				(ioGpv.mEmmcRIb.fm)			/**< Get M_Emmc_r_ib fn_mod */

/* M_Uhs2_r_ib Registers */
#define DdGpv_GET_M_UHS2_R_IB_FMIB()			(ioGpv.mUhs2RIb.fmib)			/**< Get M_Uhs2_r_ib fn_mod_iss_bm */
#define DdGpv_GET_M_UHS2_R_IB_FM2()				(ioGpv.mUhs2RIb.fm2)			/**< Get M_Uhs2_r_ib fn_mod2 */
#define DdGpv_GET_M_UHS2_R_IB_FML()				(ioGpv.mUhs2RIb.fml)			/**< Get M_Uhs2_r_ib fn_mod_lb */
#define DdGpv_GET_M_UHS2_R_IB_FM()				(ioGpv.mUhs2RIb.fm)			/**< Get M_Uhs2_r_ib fn_mod */

/* M_Mxic1_m_ib Registers */
#define DdGpv_GET_M_MXIC1_M_IB_FMIB()			(ioGpv.mMxic1MIb.fmib)			/**< Get M_Mxic1_m_ib fn_mod_iss_bm */
#define DdGpv_GET_M_MXIC1_M_IB_WT()				(ioGpv.mMxic1MIb.wt)			/**< Get M_Mxic1_m_ib wr_tidemark */
#define DdGpv_GET_M_MXIC1_M_IB_FM()				(ioGpv.mMxic1MIb.fm)			/**< Get M_Mxic1_m_ib fn_mod */

/* M_Mxic2_m_ib Registers */
#define DdGpv_GET_M_MXIC2_M_IB_FMIB()			(ioGpv.mMxic2MIb.fmib)			/**< Get M_Mxic2_m_ib fn_mod_iss_bm */
#define DdGpv_GET_M_MXIC2_M_IB_WT()				(ioGpv.mMxic2MIb.wt)			/**< Get M_Mxic2_m_ib wr_tidemark */
#define DdGpv_GET_M_MXIC2_M_IB_FM()				(ioGpv.mMxic2MIb.fm)			/**< Get M_Mxic2_m_ib fn_mod */

/* M_Xdmac_r_ib Registers */
#define DdGpv_GET_M_XDMAC_R_IB_FMIB()		(ioGpv.mXdmacRIb.fmib)			/**< Get M_Xdmac_r_ib fn_mod_iss_bm */
#define DdGpv_GET_M_XDMAC_R_IB_FM2()			(ioGpv.mXdmacRIb.fm2)			/**< Get M_Xdmac_r_ib fn_mod2 */
#define DdGpv_GET_M_XDMAC_R_IB_FM()			(ioGpv.mXdmacRIb.fm)			/**< Get M_Xdmac_r_ib fn_mod */

/* M_Nf_r_ib Registers */
#define DdGpv_GET_M_NF_R_IB_FMIB()				(ioGpv.mNfRIb.fmib)			/**< Get M_Nf_r_ib fn_mod_iss_bm */
#define DdGpv_GET_M_NF_R_IB_FM2()				(ioGpv.mNfRIb.fm2)				/**< Get M_Nf_r_ib fn_mod2 */
#define DdGpv_GET_M_NF_R_IB_FML()				(ioGpv.mNfRIb.fml)				/**< Get M_Nf_r_ib fn_mod_lb */
#define DdGpv_GET_M_NF_R_IB_FM()				(ioGpv.mNfRIb.fm)				/**< Get M_Nf_r_ib fn_mod */

/* M_Pcie0_r_ib Registers */
#define DdGpv_GET_M_PCIE0_R_IB_FMIB()		(ioGpv.mPcie0RIb.fmib)			/**< Get M_Pcie0_r_ib fn_mod_iss_bm */
#define DdGpv_GET_M_PCIE0_R_IB_FM2()			(ioGpv.mPcie0RIb.fm2)			/**< Get M_Pcie0_r_ib fn_mod2 */
#define DdGpv_GET_M_PCIE0_R_IB_FML()			(ioGpv.mPcie0RIb.fml)			/**< Get M_Pcie0_r_ib fn_mod_lb */
#define DdGpv_GET_M_PCIE0_R_IB_FM()			(ioGpv.mPcie0RIb.fm)			/**< Get M_Pcie0_r_ib fn_mod */

/* M_Pcie1_r_ib Registers */
#define DdGpv_GET_M_PCIE1_R_IB_FMIB()		(ioGpv.mPcie1RIb.fmib)			/**< Get M_Pcie1_r_ib fn_mod_iss_bm */
#define DdGpv_GET_M_PCIE1_R_IB_FM2()			(ioGpv.mPcie1RIb.fm2)			/**< Get M_Pcie1_r_ib fn_mod2 */
#define DdGpv_GET_M_PCIE1_R_IB_FML()			(ioGpv.mPcie1RIb.fml)			/**< Get M_Pcie1_r_ib fn_mod_lb */
#define DdGpv_GET_M_PCIE1_R_IB_FM()			(ioGpv.mPcie1RIb.fm)			/**< Get M_Pcie1_r_ib fn_mod */

/* M_NicPeriAHB_m_ib Registers */
#define DdGpv_GET_M_NICPERIAHB_M_IB_FMIB()		(ioGpv.mNicPeriAhbMIb.fmib)	/**< Get M_NicPeriAHB_m_ib fn_mod_iss_bm */
#define DdGpv_GET_M_NICPERIAHB_M_IB_FM2()		(ioGpv.mNicPeriAhbMIb.fm2)		/**< Get M_NicPeriAHB_m_ib fn_mod2 */
#define DdGpv_GET_M_NICPERIAHB_M_AC()				(ioGpv.mNicPeriAhbMIb.ac)		/**< Get M_NicPeriAHB_m_ib ahb_cntl */

/* M_NicBmAHB1_r_ib Registers */
#define DdGpv_GET_M_NICBMAHB1_R_IB_FMIB()		(ioGpv.mNicBmAhb1RIb.fmib)		/**< Get M_NicBmAHB1_r_ib fn_mod_iss_bm */
#define DdGpv_GET_M_NICBMAHB1_R_AC()					(ioGpv.mNicBmAhb1RIb.ac)		/**< Get M_NicBmAHB1_r_ib ahb_cntl */

/* NsecX2P_ib Registers */
#define DdGpv_GET_NSECX2P_IB_FMIB()				(ioGpv.nsecX2pIb.fmib)			/**< Get NsecX2P_ib fn_mod_iss_bm */
#define DdGpv_GET_NSECX2P_IB_FM2()				(ioGpv.nsecX2pIb.fm2)			/**< Get NsecX2P_ib fn_mod2 */

/* ToprX2P_ib Registers */
#define DdGpv_GET_TOPRX2P_IB_FMIB()				(ioGpv.toprX2pIb.fmib)			/**< Get ToprX2P_ib fn_mod_iss_bm */
#define DdGpv_GET_TOPRX2P_IB_FM2()				(ioGpv.toprX2pIb.fm2)			/**< Get ToprX2P_ib fn_mod2 */

/* M_NicBmAHB2_r_ib Registers */
#define DdGpv_GET_M_NICBMAHB2_R_IB_FMIB()		(ioGpv.mNicBmAhb2RIb.fmib)		/**< Get M_NicBmAHB2_r_ib fn_mod_iss_bm */
#define DdGpv_GET_M_NICBMAHB2_R_IB_FM2()			(ioGpv.mNicBmAhb2RIb.fm2)		/**< Get M_NicBmAHB2_r_ib fn_mod2 */
#define DdGpv_GET_M_NICBMAHB2_R_AC()					(ioGpv.mNicBmAhb2RIb.ac)		/**< Get M_NicBmAHB2_r_ib ahb_cntl */

/* S_Main_rm_ib Registers */
#define DdGpv_GET_S_MAIN_RM_IB_FM()			(ioGpv.sMainRmIb.fm)			/**< Get S_Main_rm_ib fn_mod */

/* S_Xdmac_m_ib Registers */
#define DdGpv_GET_S_XDMAC_M_IB_FM()			(ioGpv.sXdmacMIb.fm)			/**< Get S_Xdmac_m_ib fn_mod */

/* S_Netsec_m Registers */
#define DdGpv_GET_S_NETSEC_M_FM()				(ioGpv.sNetsecM.fm)			/**< Get S_Netsec_m fn_mod */

/* S_WifiAHB_m_ib Registers */
#define DdGpv_GET_S_WIFIAHB_M_FMA()			(ioGpv.sWifiAhbMIb.fma)		/**< Get S_WifiAHB_m_ib fn_mod_ahb */
#define DdGpv_GET_S_WIFIAHB_M_IB_FM()		(ioGpv.sWifiAhbMIb.fm)			/**< Get S_WifiAHB_m_ib fn_mod */

/* S_Uhs2AHB_m Registers */
#define DdGpv_GET_S_UHS2AHB_M_FMA()		(ioGpv.sUhs2AhbM.fma)			/**< Get S_Uhs2AHB_m fn_mod_ahb */
#define DdGpv_GET_S_UHS2AHB_M_FM()			(ioGpv.sUhs2AhbM.fm)			/**< Get S_Uhs2AHB_m fn_mod */

/* S_RelcrAHB_m Registers */
#define DdGpv_GET_S_RELCRAHB_M_FMA()		(ioGpv.sRelcrAhbM.fma)			/**< Get S_RelcrAHB_m fn_mod_ahb */
#define DdGpv_GET_S_RELCRAHB_M_FM()		(ioGpv.sRelcrAhbM.fm)			/**< Get S_RelcrAHB_m fn_mod */

/* S_Uhs1AHB_m Registers */
#define DdGpv_GET_S_UHS1AHB_M_FMA()		(ioGpv.sUhs1AhbM.fma)			/**< Get S_Uhs1AHB_m fn_mod_ahb */
#define DdGpv_GET_S_UHS1AHB_M_FM()			(ioGpv.sUhs1AhbM.fm)			/**< Get S_Uhs1AHB_m fn_mod */

/* S_RelcwAHB_m Registers */
#define DdGpv_GET_S_RELCWAHB_M_FMA()		(ioGpv.sRelcwAhbM.fma)			/**< Get S_RelcwAHB_m fn_mod_ahb */
#define DdGpv_GET_S_RELCWAHB_M_FM()		(ioGpv.sRelcwAhbM.fm)			/**< Get S_RelcwAHB_m fn_mod */

/* S_BmNicAHB_m Registers */
#define DdGpv_GET_S_BMNICAHB_M_FMA()		(ioGpv.sBmNicAhbM.fma)			/**< Get S_BmNicAHB_m fn_mod_ahb */
#define DdGpv_GET_S_BMNICAHB_M_FM()		(ioGpv.sBmNicAhbM.fm)			/**< Get S_BmNicAHB_m fn_mod */

/* S_Usb2AHB_ehci Registers */
#define DdGpv_GET_S_USB2AHB_EHCI_FMA()		(ioGpv.sUsb2AhbEhci.fma)		/**< Get S_Usb2AHB_ehci fn_mod_ahb */
#define DdGpv_GET_S_USB2AHB_EHCI_FM()			(ioGpv.sUsb2AhbEhci.fm)		/**< Get S_Usb2AHB_ehci fn_mod */

/* S_Usb2AHB_ohci Registers */
#define DdGpv_GET_S_USB2AHB_OHCI_FMA()		(ioGpv.sUsb2AhbOhci.fma)		/**< Get S_Usb2AHB_ohci fn_mod_ahb */
#define DdGpv_GET_S_USB2AHB_OHCI_FM()		(ioGpv.sUsb2AhbOhci.fm)		/**< Get S_Usb2AHB_ohci fn_mod */

/* S_Netsec2_m Registers */
#define DdGpv_GET_S_NETSEC2_M_FM()				(ioGpv.sNetsec2M.fm)			/**< Get S_Netsec2_m fn_mod */

/* IB8 Registers */
#define DdGpv_GET_IB8_FMIB()					(ioGpv.ib8.fmib)				/**< Get IB8 fn_mod_iss_bm */
#define DdGpv_GET_IB8_FM2()					(ioGpv.ib8.fm2)				/**< Get IB8 fn_mod2 */
#define DdGpv_GET_IB8_WT()						(ioGpv.ib8.wt)					/**< Get IB8 wr_tidemark */
#define DdGpv_GET_IB8_FM()						(ioGpv.ib8.fm)					/**< Get IB8 fn_mod */

/* IB13 Registers */
#define DdGpv_GET_IB13_FMIB()				(ioGpv.ib13.fmib)				/**< Get IB13 fn_mod_iss_bm */
#define DdGpv_GET_IB13_FM2()					(ioGpv.ib13.fm2)				/**< Get IB13 fn_mod2 */
#define DdGpv_GET_IB13_FML()					(ioGpv.ib13.fml)				/**< Get IB13 fn_mod_lb */
#define DdGpv_GET_IB13_FM()					(ioGpv.ib13.fm)				/**< Get IB13 fn_mod */

/* IB12 Registers */
#define DdGpv_GET_IB12_FMIB()				(ioGpv.ib12.fmib)				/**< Get IB12 fn_mod_iss_bm */
#define DdGpv_GET_IB12_FM2()					(ioGpv.ib12.fm2)				/**< Get IB12 fn_mod2 */
#define DdGpv_GET_IB12_FM()					(ioGpv.ib12.fm)				/**< Get IB12 fn_mod */

/* IB9 Registers */
#define DdGpv_GET_IB9_FMIB()					(ioGpv.ib9.fmib)				/**< Get IB9 fn_mod_iss_bm */
#define DdGpv_GET_IB9_FM2()					(ioGpv.ib9.fm2)				/**< Get IB9 fn_mod2 */
#define DdGpv_GET_IB9_WT()						(ioGpv.ib9.wt)					/**< Get IB9 wr_tidemark */
#define DdGpv_GET_IB9_FM()						(ioGpv.ib9.fm)					/**< Get IB9 fn_mod */

typedef struct _DdGpv                	DdGpv;
typedef struct _DdGpvPrivate 	DdGpvPrivate;

struct _DdGpv
{
	KObject parent;
};

KConstType 	dd_gpv_get_type(void);
DdGpv* 			dd_gpv_get(void);

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/**
Get to REMAP register.
@retval	gRemap							: REMAP state (0 to @ref D_DD_GPV_REMAP_VAL_MAX)
*/
kuint32 	dd_gpv_get_arc_remap(DdGpv *self);

/**
Set to REMAP register.
@param [in]	val							: REMAP state (0 to @ref D_DD_GPV_REMAP_VAL_MAX)
@param [in]	set							: Set Flag (0 or 1)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 		dd_gpv_set_arc_remap(DdGpv *self, kulong val, kuint32 set);//这

#ifdef __cplusplus
}
#endif

#endif /* __DD_GPV_H__ */
