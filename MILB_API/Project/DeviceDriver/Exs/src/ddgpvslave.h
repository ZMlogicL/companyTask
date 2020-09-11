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
*2、将dd_gpv.h里有关T_DD_GPV_CTRL_S结构体调用的方法移到这里
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __DD_GPV_SLAVE_H__
#define __DD_GPV_SLAVE_H__

#include <klib.h>
#include "driver_common.h"
#include "exstop.h"
#include "ddgpv.h"

#define DD_TYPE_GPV_SLAVE     (dd_gpv_slave_get_type())
#define DD_GPV_SLAVE(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, DdGpvSlave))
#define DD_IS_GPV_SLAVE(obj)  (K_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_GPV_SLAVE))

typedef struct _DdGpvSlave                	DdGpvSlave;
typedef struct _DdGpvSlavePrivate 		DdGpvSlavePrivate;

/*----------------------------------------------------------------------*/
/* Structure  															*/
/*----------------------------------------------------------------------*/
///** Control information (Slave)*/
//typedef struct {
//	unsigned long		FMA;			/**< Base_(0028h - 002Bh) fn_mod_ahb */
//	unsigned long		FM;				/**< Base_(0108h - 010Bh) fn_mod */
//} T_DD_GPV_CTRL_S;

struct _DdGpvSlave
{
	KObject parent;

	/** Control information (Slave)*/
	unsigned long		slaveFMA;			/**< Base_(0028h - 002Bh) fn_mod_ahb */
	unsigned long		slaveFM;
};

KConstType 		dd_gpv_slave_get_type(void);
DdGpvSlave* 	dd_gpv_slave_new(void);

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/**
S_WifiAHB_m_ib register Value is gotten
@param [out]	*gpv_ctrl_s				: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_get_s_wifiahb_m_ib(DdGpvSlave* const self);

/**
S_Uhs2AHB_m register Value is gotten
@param [out]	*gpv_ctrl_s				: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_get_s_uhs2_ahb_m(DdGpvSlave *self);

/**
S_RelcrAHB_m register Value is gotten
@param [out]	*gpv_ctrl_s				: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_get_s_relcr_ahb_m(DdGpvSlave *self);

/**
S_Uhs1AHB_m register Value is gotten
@param [out]	*gpv_ctrl_s				: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_get_s_uhs1_ahb_m(DdGpvSlave *self);

/**
S_RelcwAHB_m register Value is gotten
@param [out]	*gpv_ctrl_s				: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_get_s_relcw_ahb_m(DdGpvSlave *self);

/**
S_BmNicAHB_m register Value is gotten
@param [out]	*gpv_ctrl_s				: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_get_s_bm_nic_ahb_m(DdGpvSlave *self);

/**
S_Usb2AHB_ehci register Value is gotten
@param [out]	*gpv_ctrl_s				: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_get_s_usb2_ahb_ehci(DdGpvSlave *self);

/**
S_Usb2AHB_ohci register Value is gotten
@param [out]	*gpv_ctrl_s				: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_get_s_usb2_ahb_ohci(DdGpvSlave *self);

/**
Set to S_WifiAHB_m_ib register.
@param [in]	*gpv_ctrl_s					: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_s_wifiahb_m_ib(DdGpvSlave const *self);

/**
Set to S_Uhs2AHB_m register.
@param [in]	*gpv_ctrl_s					: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_s_uhs2_ahb_m(DdGpvSlave const *self);

/**
Set to S_RelcrAHB_m register.
@param [in]	*gpv_ctrl_s					: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_s_relcr_ahb_m(DdGpvSlave const *self);

/**
Set to S_Uhs1AHB_m register.
@param [in]	*gpv_ctrl_s					: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_s_uhs1_ahb_m(DdGpvSlave const *self);

/**
Set to S_RelcwAHB_m register.
@param [in]	*gpv_ctrl_s					: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_s_relcw_ahb_m(DdGpvSlave const *self);

/**
Set to S_BmNicAHB_m register.
@param [in]	*gpv_ctrl_s					: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_s_bm_nic_ahb_m(DdGpvSlave const *self);

/**
Set to S_Usb2AHB_ehci register.
@param [in]	*gpv_ctrl_s					: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_s_usb2_ahb_ehci(DdGpvSlave const *self);

/**
Set to S_Usb2AHB_ohci register.
@param [in]	*gpv_ctrl_s					: Gpv Control Information (Slave)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_s_usb2_ahb_ohci(DdGpvSlave const *self);

/**
Set to M_Usb3_r_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_usb3_r_ib_fmib(DdGpvSlave *self, kulong val);

/**
Set to M_Usb3_r_ib FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_usb3_r_ib_fm2(DdGpvSlave *self, kulong val);

/**
Set to M_Usb3_r_ib FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_usb3_r_ib_fm(DdGpvSlave *self, kulong val);

/**
Set to M_Emmc_r_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_emmc_r_ib_fmib(DdGpvSlave *self, kulong val);

/**
Set to M_Emmc_r_ib FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_emmc_r_ib_fm2(DdGpvSlave *self, kulong val);

/**
Set to M_Emmc_r_ib FML register.
@param [in]	val							: FML (0 to @ref DdGpv_FML_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_emmc_r_ib_fml(DdGpvSlave *self, kulong val);

/**
Set to M_Emmc_r_ib FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_emmc_r_ib_fm(DdGpvSlave *self, kulong val);

/**
Set to M_Uhs2_r_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_uhs2_r_ib_fmib(DdGpvSlave *self, kulong val);

/**
Set to M_Uhs2_r_ib FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_uhs2_r_ib_fm2(DdGpvSlave *self, kulong val);

/**
Set to M_Uhs2_r_ib FML register.
@param [in]	val							: FML (0 to @ref DdGpv_FML_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_uhs2_r_ib_fml(DdGpvSlave *self, kulong val);

/**
Set to M_Uhs2_r_ib FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_uhs2_r_ib_fm(DdGpvSlave *self, kulong val);

/**
Set to M_Mxic1_m_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_mxic1_m_ib_fmib(DdGpvSlave *self, kulong val);

/**
Set to M_Mxic1_m_ib WT register.
@param [in]	val							: WT (0 to @ref DdGpv_WT_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_mxic1_m_ib_wt(DdGpvSlave *self, kulong val);

/**
Set to M_Mxic1_m_ib FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_mxic1_m_ib_fm(DdGpvSlave *self, kulong val);

/**
Set to M_Mxic2_m_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_mxic2_m_ib_fmib(DdGpvSlave *self, kulong val);

/**
Set to M_Mxic2_m_ib WT register.
@param [in]	val							: WT (0 to @ref DdGpv_WT_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_mxic2_m_ib_wt(DdGpvSlave *self, kulong val);

/**
Set to M_Mxic2_m_ib FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_mxic2_m_ib_fm(DdGpvSlave *self, kulong val);

/**
Set to M_Xdmac_r_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_xdmac_r_ib_fmib(DdGpvSlave *self, kulong val);

/**
Set to M_Xdmac_r_ib FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_xdmac_r_ib_fm2(DdGpvSlave *self, kulong val);

/**
Set to M_Xdmac_r_ib FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_xdmac_r_ib_fm(DdGpvSlave *self, kulong val);

/**
Set to M_Nf_r_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_nf_r_ib_fmib(DdGpvSlave *self, kulong val);

/**
Set to M_Nf_r_ib FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_nf_r_ib_fm2(DdGpvSlave *self, kulong val);

/**
Set to M_Nf_r_ib FML register.
@param [in]	val							: FML (0 to @ref DdGpv_FML_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_nf_r_ib_fml(DdGpvSlave *self, kulong val);

/**
Set to M_Nf_r_ib FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_nf_r_ib_fm(DdGpvSlave *self, kulong val);

/**
Set to M_Pcie0_r_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_pcie0_r_ib_fmib(DdGpvSlave *self, kulong val);

/**
Set to M_Pcie0_r_ib FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_pcie0_r_ib_fm2(DdGpvSlave *self, kulong val);

/**
Set to M_Pcie0_r_ib FML register.
@param [in]	val							: FML (0 to @ref DdGpv_FML_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_pcie0_r_ib_fml(DdGpvSlave *self, kulong val);

/**
Set to M_Pcie0_r_ib FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_pcie0_r_ib_fm(DdGpvSlave *self, kulong val);

/**
Set to M_Pcie1_r_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_pcie1_r_ib_fmib(DdGpvSlave *self, kulong val);

/**
Set to M_Pcie1_r_ib FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_pcie1_r_ib_fm2(DdGpvSlave *self, kulong val);

/**
Set to M_Pcie1_r_ib FML register.
@param [in]	val							: FML (0 to @ref DdGpv_FML_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_pcie1_r_ib_fml(DdGpvSlave *self, kulong val);

/**
Set to M_Pcie1_r_ib FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_pcie1_r_ib_fm(DdGpvSlave *self, kulong val);

/**
Set to M_NicPeriAHB_m_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_nic_peri_ahb_m_ib_fmib(DdGpvSlave *self, kulong val);

/**
Set to M_NicPeriAHB_m_ib FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_nic_peri_ahb_m_ib_fm2(DdGpvSlave *self, kulong val);

/**
Set to M_NicPeriAHB_m_ib AC register.
@param [in]	val							: AC (0 to @ref DdGpv_AC_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_nic_peri_ahb_m_ac(DdGpvSlave *self, kulong val);

/**
Set to M_NicBmAHB1_r_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_slave_set_m_nic_bm_ahb1_r_ib_fmib(DdGpvSlave *self, kulong val);

#ifdef __cplusplus
}
#endif

#endif /* __DD_GPV_SLAVE_H__ */
