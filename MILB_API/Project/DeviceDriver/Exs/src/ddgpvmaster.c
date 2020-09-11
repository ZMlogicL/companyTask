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
*2、将dd_gpv.c里有关T_DD_GPV_CTRL_M结构体调用的方法移到这里
*@version
*1.0.0 2020年06月开始开发
*/

#include "dd_arm.h"
#include "ddgpvmaster.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdGpvMaster, dd_gpv_master);
#define DD_GPV_MASTER_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), DdGpvMasterPrivate, DD_TYPE_GPV_MASTER))

struct _DdGpvMasterPrivate
{
    int a;
};

static void dd_gpv_master_constructor(DdGpvMaster *self)
{
	DdGpvMasterPrivate *priv = DD_GPV_MASTER_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_gpv_master_destructor(DdGpvMaster *self)
{

}

/*----------------------------------------------------------------------*/
/* PUBLIC(公有函数接口实现)														*/
/*----------------------------------------------------------------------*/
/**
 * @brief	M_Usb3_r_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_m_usb3_r_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_M_Usb3_r_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.mUsb3RIb.fmib;
	self->masterFM2 = ioGpv.mUsb3RIb.fm2;
	self->masterFM = ioGpv.mUsb3RIb.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Emmc_r_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_m_emmc_r_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_M_Emmc_r_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.mEmmcRIb.fmib;
	self->masterFM2 = ioGpv.mEmmcRIb.fm2;
	self->masterFML = ioGpv.mEmmcRIb.fml;
	self->masterFM = ioGpv.mEmmcRIb.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Uhs2_r_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_m_uhs2_r_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_M_Uhs2_r_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.mUhs2RIb.fmib;
	self->masterFM2 = ioGpv.mUhs2RIb.fm2;
	self->masterFML = ioGpv.mUhs2RIb.fml;
	self->masterFM = ioGpv.mUhs2RIb.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Mxic1_m_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_m_mxic1_m_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_M_Mxic1_m_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.mMxic1MIb.fmib;
	self->masterWT = ioGpv.mMxic1MIb.wt;
	self->masterFM = ioGpv.mMxic1MIb.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Mxic2_m_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_m_mxic2_m_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_M_Mxic2_m_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.mMxic2MIb.fmib;
	self->masterWT = ioGpv.mMxic2MIb.wt;
	self->masterFM = ioGpv.mMxic2MIb.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Xdmac_r_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_m_xdmac_r_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_M_Xdmac_r_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.mXdmacRIb.fmib;
	self->masterFM2 = ioGpv.mXdmacRIb.fm2;
	self->masterFM = ioGpv.mXdmacRIb.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Nf_r_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_m_nf_r_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_M_Nf_r_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.mNfRIb.fmib;
	self->masterFM2 = ioGpv.mNfRIb.fm2;
	self->masterFML = ioGpv.mNfRIb.fml;
	self->masterFM = ioGpv.mNfRIb.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Pcie0_r_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_m_pcie0_r_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_M_Pcie0_r_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.mPcie0RIb.fmib;
	self->masterFM2 = ioGpv.mPcie0RIb.fm2;
	self->masterFML = ioGpv.mPcie0RIb.fml;
	self->masterFM = ioGpv.mPcie0RIb.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Pcie1_r_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_m_pcie1_r_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_M_Pcie1_r_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.mPcie1RIb.fmib;
	self->masterFM2 = ioGpv.mPcie1RIb.fm2;
	self->masterFML = ioGpv.mPcie1RIb.fml;
	self->masterFM = ioGpv.mPcie1RIb.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicPeriAHB_m_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_m_nic_peri_ahb_m_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_M_NicPeriAHB_m_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.mNicPeriAhbMIb.fmib;
	self->masterFM2 = ioGpv.mNicPeriAhbMIb.fm2;
	self->masterAC = ioGpv.mNicPeriAhbMIb.ac;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicPeriAHB_m_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_m_nic_bm_ahb1_r_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_M_NicBmAHB1_r_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.mNicBmAhb1RIb.fmib;
	self->masterAC = ioGpv.mNicBmAhb1RIb.ac;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	NsecX2P_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_nsec_x2p_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL)
	{
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_NsecX2P_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.nsecX2pIb.fmib;
	self->masterFM2 = ioGpv.nsecX2pIb.fm2;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	ToprX2P_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_topr_x2p_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL)
	{
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_ToprX2P_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.toprX2pIb.fmib;
	self->masterFM2 = ioGpv.toprX2pIb.fm2;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicBmAHB2_r_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_get_m_nic_bm_ahb2_r_ib(DdGpvMaster *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL)
	{
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_M_NicBmAHB2_r_ib: input param error. [gpv_ctrl_m] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->masterFMIB = ioGpv.mNicBmAhb2RIb.fmib;
	self->masterFM2 = ioGpv.mNicBmAhb2RIb.fm2;
	self->masterAC = ioGpv.mNicBmAhb2RIb.ac;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Usb3_r_ib register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_m_usb3_r_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm2] = 0x%lx\n", self->masterFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFML > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fml] = 0x%lx\n", self->masterFML));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm] = 0x%lx\n", self->masterFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mUsb3RIb.fmib = self->masterFMIB;
	ioGpv.mUsb3RIb.fm2 = self->masterFM2;
	ioGpv.mUsb3RIb.fm = self->masterFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Emmc_r_ib register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_m_emmc_r_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm2] = 0x%lx\n", self->masterFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFML > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fml] = 0x%lx\n", self->masterFML));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm] = 0x%lx\n", self->masterFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mEmmcRIb.fmib = self->masterFMIB;
	ioGpv.mEmmcRIb.fm2 = self->masterFM2;
	ioGpv.mEmmcRIb.fml = self->masterFML;
	ioGpv.mEmmcRIb.fm = self->masterFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Uhs2_r_ib register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_m_uhs2_r_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm2] = 0x%lx\n", self->masterFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFML > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fml] = 0x%lx\n", self->masterFML));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm] = 0x%lx\n", self->masterFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mUhs2RIb.fmib = self->masterFMIB;
	ioGpv.mUhs2RIb.fm2 = self->masterFM2;
	ioGpv.mUhs2RIb.fml = self->masterFML;
	ioGpv.mUhs2RIb.fm = self->masterFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Mxic1_m_ib FMIB register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_m_mxic1_m_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterWT > DdGpv_WT_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.wt] = 0x%lx\n", self->masterWT));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm] = 0x%lx\n", self->masterFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mMxic1MIb.fmib = self->masterFMIB;
	ioGpv.mMxic1MIb.wt = self->masterWT;
	ioGpv.mMxic1MIb.fm = self->masterFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Mxic2_m_ib register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_m_mxic2_m_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterWT > DdGpv_WT_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.wt] = 0x%lx\n", self->masterWT));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm] = 0x%lx\n", self->masterFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mMxic2MIb.fmib = self->masterFMIB;
	ioGpv.mMxic2MIb.wt = self->masterWT;
	ioGpv.mMxic2MIb.fm = self->masterFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Xdmac_r_ib register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_m_xdmac_r_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", self->masterFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", self->masterFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mXdmacRIb.fmib = self->masterFMIB;
	ioGpv.mXdmacRIb.fm2 = self->masterFM2;
	ioGpv.mXdmacRIb.fm = self->masterFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Nf_r_ib register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_m_nf_r_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm2] = 0x%lx\n", self->masterFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFML > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fml] = 0x%lx\n", self->masterFML));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm] = 0x%lx\n", self->masterFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNfRIb.fmib = self->masterFMIB;
	ioGpv.mNfRIb.fm2 = self->masterFM2;
	ioGpv.mNfRIb.fml = self->masterFML;
	ioGpv.mNfRIb.fm = self->masterFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Pcie0_r_ib register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_m_pcie0_r_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm2] = 0x%lx\n", self->masterFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFML > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fml] = 0x%lx\n", self->masterFML));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm] = 0x%lx\n", self->masterFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mPcie0RIb.fmib = self->masterFMIB;
	ioGpv.mPcie0RIb.fm2 = self->masterFM2;
	ioGpv.mPcie0RIb.fml = self->masterFML;
	ioGpv.mPcie0RIb.fm = self->masterFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Pcie1_r_ib register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_m_pcie1_r_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm2] = 0x%lx\n", self->masterFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFML > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fml] = 0x%lx\n", self->masterFML));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm] = 0x%lx\n", self->masterFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mPcie1RIb.fmib = self->masterFMIB;
	ioGpv.mPcie1RIb.fm2 = self->masterFM2;
	ioGpv.mPcie1RIb.fml = self->masterFML;
	ioGpv.mPcie1RIb.fm = self->masterFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicPeriAHB_m_ib register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_m_nic_peri_ahb_m_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm2] = 0x%lx\n", self->masterFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterAC > DdGpv_AC_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.ac] = 0x%lx\n", self->masterAC));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNicPeriAhbMIb.fmib = self->masterFMIB;
	ioGpv.mNicPeriAhbMIb.fm2 = self->masterFM2;
	ioGpv.mNicPeriAhbMIb.ac = self->masterAC;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicBmAHB1_r_ib register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_m_nic_bm_ahb1_r_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterAC > DdGpv_AC_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.ac] = 0x%lx\n", self->masterAC));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNicBmAhb1RIb.fmib = self->masterFMIB;
	ioGpv.mNicBmAhb1RIb.ac = self->masterAC;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	NsecX2P_ib register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_nsec_x2p_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm2] = 0x%lx\n", self->masterFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.nsecX2pIb.fmib = self->masterFMIB;
	ioGpv.nsecX2pIb.fm2 = self->masterFM2;
	return DriverCommon_DDIM_OK;
}

/**
 * @brief	ToprX2P_ib register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_topr_x2p_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm2] = 0x%lx\n", self->masterFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.toprX2pIb.fmib = self->masterFMIB;
	ioGpv.toprX2pIb.fm2 = self->masterFM2;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicBmAHB2_r_ib register.
 * @param	T_DD_GPV_CTRL_M* gpv_ctrl_m
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_m_nic_bm_ahb2_r_ib(DdGpvMaster const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->masterFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fmib] = 0x%lx\n", self->masterFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.fm2] = 0x%lx\n", self->masterFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->masterAC > DdGpv_AC_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_m.ac] = 0x%lx\n", self->masterAC));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNicBmAhb2RIb.fmib = self->masterFMIB;
	ioGpv.mNicBmAhb2RIb.fm2 = self->masterFM2;
	ioGpv.mNicBmAhb2RIb.ac = self->masterAC;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Uhs1AHB_m FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_s_uhs1_ahb_m_fm(DdGpvMaster *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sUhs1AhbM.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_RelcwAHB_m FMA register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_s_relcw_ahb_m_fma(DdGpvMaster *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sRelcwAhbM.fma = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_RelcwAHB_m FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_s_relcw_ahb_m_fm(DdGpvMaster *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sRelcwAhbM.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_BmNicAHB_m FMA register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_s_bm_nic_ahb_m_fma(DdGpvMaster *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sBmNicAhbM.fma = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_BmNicAHB_m FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_s_bm_nic_ahb_m_fm(DdGpvMaster *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sBmNicAhbM.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Usb2AHB_ehci FMA register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_s_usb2_ahb_ehci_fma(DdGpvMaster *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sUsb2AhbEhci.fma = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Usb2AHB_ehci FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_s_usb2_ahb_ehci_fm(DdGpvMaster *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sUsb2AhbEhci.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Usb2AHB_ohci FMA register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_s_usb2_ahb_ohci_fma(DdGpvMaster *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sUsb2AhbOhci.fma = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Usb2AHB_ohci FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_master_set_s_usb2_ahb_ohci_fm(DdGpvMaster *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sUsb2AhbOhci.fm = val;

	return DriverCommon_DDIM_OK;
}

DdGpvMaster* dd_gpv_master_new(void)
{
	DdGpvMaster* self = k_object_new_with_private(DD_TYPE_GPV_MASTER, sizeof(DdGpvMasterPrivate));
	return self;
}
