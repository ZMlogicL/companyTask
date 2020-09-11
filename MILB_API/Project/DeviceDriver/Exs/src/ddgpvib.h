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
*2、将dd_gpv.h里有关T_DD_GPV_CTRL_IB结构体调用的方法移到这里
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __DD_GPV_IB_H__
#define __DD_GPV_IB_H__

#include <klib.h>
#include "driver_common.h"
#include "exstop.h"
#include "ddgpv.h"

#define DD_TYPE_GPV_IB     (dd_gpv_ib_get_type())
#define DD_GPV_IB(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, DdGpvIb))
#define DD_IS_GPV_IB(obj)  (K_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_GPV_IB))

typedef struct _DdGpvIb                	DdGpvIb;
typedef struct _DdGpvIbPrivate 	DdGpvIbPrivate;

/** Control information (IB)*/
//typedef struct {
//	unsigned long		FMIB;			/**< Base_(0008h - 000Bh) fn_mod_iss_bm */
//	unsigned long		FM2;			/**< Base_(0024h - 0027h) fn_mod2 */
//	unsigned long		FML;			/**< Base_(002Ch - 002Fh) fn_mod_lb */
//	unsigned long		WT;				/**< Base_(0040h - 0043h) wr_tidemark */
//	unsigned long		FM;				/**< Base_(0108h - 010Bh) fn_mod */
//} T_DD_GPV_CTRL_IB;//这个结构体移到了类中

struct _DdGpvIb
{
	KObject 					parent;

	/** Control information (IB)*/
	unsigned long		ibFMIB;			/**< Base_(0008h - 000Bh) fn_mod_iss_bm */
	unsigned long		ibFM2;			/**< Base_(0024h - 0027h) fn_mod2 */
	unsigned long		ibFML;			/**< Base_(002Ch - 002Fh) fn_mod_lb */
	unsigned long		ibWT;				/**< Base_(0040h - 0043h) wr_tidemark */
	unsigned long		ibFM;				/**< Base_(0108h - 010Bh) fn_mod */
};

KConstType 	dd_gpv_ib_get_type(void);
DdGpvIb* 		dd_gpv_ib_new(void);

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/**
IB8 register Value is gotten
@param [out]	*gpv_ctrl_ib			: Gpv Control Information (IB)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_get_ib8(DdGpvIb *const self);

/**
IB13 register Value is gotten
@param [out]	*gpv_ctrl_ib			: Gpv Control Information (IB)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_get_ib13(DdGpvIb *const self);

/**
IB12 register Value is gotten
@param [out]	*gpv_ctrl_ib			: Gpv Control Information (IB)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_get_ib12(DdGpvIb *const self);

/**
IB9 register Value is gotten
@param [out]	*gpv_ctrl_ib			: Gpv Control Information (IB)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_get_ib9(DdGpvIb *const self);

/**
Set to IB8 register.
@param [in]	*gpv_ctrl_ib				: Gpv Control Information (IB)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib8(DdGpvIb const *const self);

/**
Set to IB13 register.
@param [in]	*gpv_ctrl_ib				: Gpv Control Information (IB)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib13(DdGpvIb const *const self);

/**
Set to IB12 register.
@param [in]	*gpv_ctrl_ib				: Gpv Control Information (IB)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib12(DdGpvIb const *const self);

/**
Set to IB9 register.
@param [in]	*gpv_ctrl_ib				: Gpv Control Information (IB)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib9(DdGpvIb const *const self);

/**
Set to IB8 FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib8_fmib(DdGpvIb *self, kulong val);

/**
Set to IB8 FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib8_fm2(DdGpvIb *self, kulong val);

/**
Set to IB8 WT register.
@param [in]	val							: WT (0 to @ref DdGpv_WT_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib8_wt(DdGpvIb *self, kulong val);

/**
Set to IB8 FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib8_fm(DdGpvIb *self, kulong val);

/**
Set to IB13 FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib13_fmib(DdGpvIb *self, kulong val);

/**
Set to IB13 FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib13_fm2(DdGpvIb *self, kulong val);

/**
Set to IB13 FML register.
@param [in]	val							: FML (0 to @ref DdGpv_FML_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib13_fml(DdGpvIb *self, kulong val);

/**
Set to IB13 FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib13_fm(DdGpvIb *self, kulong val);

/**
Set to IB12 FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib12_fmib(DdGpvIb *self, kulong val);

/**
Set to IB12 FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib12_fm2(DdGpvIb *self, kulong val);

/**
Set to IB12 FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib12_fm(DdGpvIb *self, kulong val);

/**
Set to IB9 FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib9_fmib(DdGpvIb *self, kulong val);

/**
Set to IB9 FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib9_fm2(DdGpvIb *self, kulong val);

/**
Set to IB9 WT register.
@param [in]	val							: WT (0 to @ref DdGpv_WT_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib9_wt(DdGpvIb *self, kulong val);

/**
Set to IB9 FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_ib9_fm(DdGpvIb *self, kulong val);

/**
Set to S_Netsec2_m FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_s_netsec2_m_fm(DdGpvIb *self, kulong val);

/**
Set to S_Uhs2AHB_m FMA register.
@param [in]	val							: FMA (0 to @ref DdGpv_FMA_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_s_uhs2_ahb_m_fma(DdGpvIb *self, kulong val);

/**
Set to S_Uhs2AHB_m FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_s_uhs2_ahb_m_fm(DdGpvIb *self, kulong val);

/**
Set to S_RelcrAHB_m FMA register.
@param [in]	val							: FMA (0 to @ref DdGpv_FMA_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_s_relcr_ahb_m_fma(DdGpvIb *self, kulong val);

/**
Set to S_RelcrAHB_m FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_s_relcr_ahb_m_fm(DdGpvIb *self, kulong val);

/**
Set to S_Uhs1AHB_m FMA register.
@param [in]	val							: FMA (0 to @ref DdGpv_FMA_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_s_uhs1_ahb_m_fma(DdGpvIb *self, kulong val);

/**
Set to M_NicBmAHB1_r_ib AC register.
@param [in]	val							: AC (0 to @ref DdGpv_AC_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_m_nic_bm_ahb1_r_ac(DdGpvIb *self, kulong val);

/**
Set to NsecX2P_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_nsec_x2p_ib_fmib(DdGpvIb *self, kulong val);

/**
Set to NsecX2P_ib FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_nsec_x2p_ib_fm2(DdGpvIb *self, kulong val);

/**
Set to ToprX2P_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_topr_x2p_ib_fmib(DdGpvIb *self, kulong val);

/**
Set to ToprX2P_ib FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_topr_x2p_ib_fm2(DdGpvIb *self, kulong val);

/**
Set to M_NicBmAHB2_r_ib FMIB register.
@param [in]	val							: FMIB (0 to @ref DdGpv_FMIB_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_m_nic_bm_ahb2_r_ib_fmib(DdGpvIb *self, kulong val);

/**
Set to M_NicBmAHB2_r_ib FM2 register.
@param [in]	val							: FM2 (0 to @ref DdGpv_FM2_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_m_nic_bm_ahb2_r_ib_fm2(DdGpvIb *self, kulong val);

/**
Set to M_NicBmAHB2_r_ib AC register.
@param [in]	val							: AC (0 to @ref DdGpv_AC_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_m_nic_bm_ahb2_r_ac(DdGpvIb *self, kulong val);

/**
Set to S_Main_rm_ib FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_s_main_rm_ib_fm(DdGpvIb *self, kulong val);

/**
Set to S_Xdmac_m_ib FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_s_xdmac_m_ib_fm(DdGpvIb *self, kulong val);

/**
Set to S_Netsec_m FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_s_netsec_m_fm(DdGpvIb *self, kulong val);

/**
Set to S_WifiAHB_m_ib FMA register.
@param [in]	val							: FMA (0 to @ref DdGpv_FMA_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_s_wifiahb_m_fma(DdGpvIb *self, kulong val);

/**
Set to S_WifiAHB_m_ib FM register.
@param [in]	val							: FM (0 to @ref DdGpv_FM_VAL_MAX)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdGpv_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 dd_gpv_ib_set_s_wifiahb_m_ib_fm(DdGpvIb *self, kulong val);

#ifdef __cplusplus
}
#endif

#endif /* __DD_GPV_IB_H__ */
