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
*2、将dd_gpv.h里有关T_DD_GPV_CTRL_M结构体调用的方法移到这里
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __DD_GPV_MASTER_H__
#define __DD_GPV_MASTER_H__

#include <klib.h>
#include "driver_common.h"
#include "exstop.h"
#include "ddgpv.h"

#define DD_TYPE_GPV_MASTER     (dd_gpv_master_get_type())
#define DD_GPV_MASTER(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, DdGpvMaster))
#define DD_IS_GPV_MASTER(obj)  (K_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_GPV_MASTER))

typedef struct _DdGpvMaster                DdGpvMaster;
typedef struct _DdGpvMasterPrivate 	DdGpvMasterPrivate;

/*----------------------------------------------------------------------*/
/* Structure  															*/
/*----------------------------------------------------------------------*/
///** Control information (Master)*/
//typedef struct {
//	unsigned long		FMIB;			/**< Base_(0008h - 000Bh) fn_mod_iss_bm */
//	unsigned long		FM2;			/**< Base_(0024h - 0027h) fn_mod2 */
//	unsigned long		FML;			/**< Base_(002Ch - 002Fh) fn_mod_lb */
//	unsigned long		WT;				/**< Base_(0040h - 0043h) wr_tidemark */
//	unsigned long		AC;				/**< Base_(0044h - 0047h) ahb_cntl */
//	unsigned long		FM;				/**< Base_(0108h - 010Bh) fn_mod */
//} T_DD_GPV_CTRL_M;

struct _DdGpvMaster
{
	KObject parent;

	/** Control information (Master)*/
	unsigned long		masterFMIB;			/**< Base_(0008h - 000Bh) fn_mod_iss_bm */
	unsigned long		masterFM2;			/**< Base_(0024h - 0027h) fn_mod2 */
	unsigned long		masterFML;			/**< Base_(002Ch - 002Fh) fn_mod_lb */
	unsigned long		masterWT;				/**< Base_(0040h - 0043h) wr_tidemark */
	unsigned long		masterAC;				/**< Base_(0044h - 0047h) ahb_cntl */
	unsigned long		masterFM;
};

KConstType 			dd_gpv_master_get_type(void);
DdGpvMaster* 	dd_gpv_master_new(void);

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/**
M_Usb3_r_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_m_usb3_r_ib(DdGpvMaster *const self);

/**
M_Emmc_r_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_m_emmc_r_ib(DdGpvMaster *const self);

/**
M_Uhs2_r_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_m_uhs2_r_ib(DdGpvMaster *const self);

/**
M_Mxic1_m_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_m_mxic1_m_ib(DdGpvMaster *const self);

/**
M_Mxic2_m_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_m_mxic2_m_ib(DdGpvMaster *const self);

/**
M_Xdmac_r_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_m_xdmac_r_ib(DdGpvMaster *const self);

/**
M_Nf_r_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_m_nf_r_ib(DdGpvMaster *const self);

/**
M_Pcie0_r_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_m_pcie0_r_ib(DdGpvMaster *const self);

/**
M_Pcie1_r_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_m_pcie1_r_ib(DdGpvMaster *const self);

/**
M_NicPeriAHB_m_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_m_nic_peri_ahb_m_ib(DdGpvMaster *const self);

/**
M_NicBmAHB1_r_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_m_nic_bm_ahb1_r_ib(DdGpvMaster *const self);

/**
NsecX2P_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_nsec_x2p_ib(DdGpvMaster *const self);

/**
ToprX2P_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_topr_x2p_ib(DdGpvMaster *const self);

/**
M_NicBmAHB2_r_ib register Value is gotten
@param [out]	*gpv_ctrl_m				: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_get_m_nic_bm_ahb2_r_ib(DdGpvMaster *const self);

/**
Set to M_Usb3_r_ib register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_m_usb3_r_ib(DdGpvMaster const *const self);

/**
Set to M_Emmc_r_ib register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_m_emmc_r_ib(DdGpvMaster const *const self);

/**
Set to M_Uhs2_r_ib register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_m_uhs2_r_ib(DdGpvMaster const *const self);

/**
Set to M_Mxic1_m_ib register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_m_mxic1_m_ib(DdGpvMaster const *const self);

/**
Set to M_Mxic2_m_ib register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_m_mxic2_m_ib(DdGpvMaster const *const self);

/**
Set to M_Xdmac_r_ib register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_m_xdmac_r_ib(DdGpvMaster const *const self);

/**
Set to M_Nf_r_ib register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_m_nf_r_ib(DdGpvMaster const *const self);

/**
Set to M_Pcie0_r_ib register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_m_pcie0_r_ib(DdGpvMaster const *const self);

/**
Set to M_Pcie1_r_ib register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_m_pcie1_r_ib(DdGpvMaster const *const self);

/**
Set to M_NicPeriAHB_m_ib register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_m_nic_peri_ahb_m_ib(DdGpvMaster const *const self);

/**
Set to M_NicBmAHB1_r_ib register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_m_nic_bm_ahb1_r_ib(DdGpvMaster const *const self);

/**
Set to NsecX2P_ib FMIB register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_nsec_x2p_ib(DdGpvMaster const *const self);

/**
Set to ToprX2P_ib FMIB register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_topr_x2p_ib(DdGpvMaster const *const self);

/**
Set to M_NicBmAHB2_r_ib FMIB register.
@param [in]	*gpv_ctrl_m					: Gpv Control Information (Master)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_m_nic_bm_ahb2_r_ib(DdGpvMaster const *const self);

/**
Set to S_Uhs1AHB_m FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_s_uhs1_ahb_m_fm(DdGpvMaster *self, kulong val);

/**
Set to S_RelcwAHB_m FMA register.
@param [in]	val							: FMA (0 to @ref DdGpv_FMA_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_s_relcw_ahb_m_fma(DdGpvMaster *self, kulong val);

/**
Set to S_RelcwAHB_m FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_s_relcw_ahb_m_fm(DdGpvMaster *self, kulong val);

/**
Set to S_BmNicAHB_m FMA register.
@param [in]	val							: FMA (0 to @ref DdGpv_FMA_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_s_bm_nic_ahb_m_fma(DdGpvMaster *self, kulong val);

/**
Set to S_BmNicAHB_m FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_s_bm_nic_ahb_m_fm(DdGpvMaster *self, kulong val);

/**
Set to S_Usb2AHB_ehci FMA register.
@param [in]	val							: FMA (0 to @ref DdGpv_FMA_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_s_usb2_ahb_ehci_fma(DdGpvMaster *self, kulong val);

/**
Set to S_Usb2AHB_ehci FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_s_usb2_ahb_ehci_fm(DdGpvMaster *self, kulong val);

/**
Set to S_Usb2AHB_ohci FMA register.
@param [in]	val							: FMA (0 to @ref DdGpv_FMA_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_s_usb2_ahb_ohci_fma(DdGpvMaster *self, kulong val);

/**
Set to S_Usb2AHB_ohci FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_master_set_s_usb2_ahb_ohci_fm(DdGpvMaster *self, kulong val);

#ifdef __cplusplus
}
#endif

#endif /* __DD_GPV_MASTER_H__ */
