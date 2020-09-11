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
*2、将dd_gpv.c里有关T_DD_GPV_CTRL_S结构体调用的方法移到这里
*@version
*1.0.0 2020年06月开始开发
*/

#include "dd_arm.h"
#include "ddgpvslave.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdGpvSlave, dd_gpv_slave);
#define DD_GPV_SLAVE_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), DdGpvSlavePrivate, DD_TYPE_GPV_SLAVE))

struct _DdGpvSlavePrivate
{
    int a;
};

static void dd_gpv_slave_constructor(DdGpvSlave *self)
{
	DdGpvSlavePrivate *priv = DD_GPV_SLAVE_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_gpv_slave_destructor(DdGpvSlave *self)
{

}

/*----------------------------------------------------------------------*/
/* PUBLIC(公有函数接口实现)														*/
/*----------------------------------------------------------------------*/
/**
 * @brief	S_WifiAHB_m_ib register values are acquired.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_get_s_wifiahb_m_ib(DdGpvSlave *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_S_WifiAHB_m_ib: input param error. [gpv_ctrl_s] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->slaveFMA = ioGpv.sWifiAhbMIb.fma;
	self->slaveFM = ioGpv.sWifiAhbMIb.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Uhs2AHB_m register values are acquired.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_get_s_uhs2_ahb_m(DdGpvSlave *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_S_Uhs2AHB_m: input param error. [gpv_ctrl_s] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->slaveFMA = ioGpv.sUhs2AhbM.fma;
	self->slaveFM = ioGpv.sUhs2AhbM.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_RelcrAHB_m register values are acquired.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_get_s_relcr_ahb_m(DdGpvSlave *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_S_RelcrAHB_m: input param error. [gpv_ctrl_s] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->slaveFMA = ioGpv.sRelcrAhbM.fma;
	self->slaveFM = ioGpv.sRelcrAhbM.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Uhs1AHB_m register values are acquired.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_get_s_uhs1_ahb_m(DdGpvSlave *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_S_Uhs1AHB_m: input param error. [gpv_ctrl_s] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->slaveFMA = ioGpv.sUhs1AhbM.fma;
	self->slaveFM = ioGpv.sUhs1AhbM.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_RelcwAHB_m register values are acquired.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_get_s_relcw_ahb_m(DdGpvSlave *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_S_RelcwAHB_m: input param error. [gpv_ctrl_s] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->slaveFMA = ioGpv.sRelcwAhbM.fma;
	self->slaveFM = ioGpv.sRelcwAhbM.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_BmNicAHB_m register values are acquired.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_get_s_bm_nic_ahb_m(DdGpvSlave *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_S_BmNicAHB_m: input param error. [gpv_ctrl_s] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->slaveFMA = ioGpv.sBmNicAhbM.fma;
	self->slaveFM = ioGpv.sBmNicAhbM.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Usb2AHB_ehci register values are acquired.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_get_s_usb2_ahb_ehci(DdGpvSlave *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_S_Usb2AHB_ehci: input param error. [gpv_ctrl_s] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->slaveFMA = ioGpv.sUsb2AhbEhci.fma;
	self->slaveFM = ioGpv.sUsb2AhbEhci.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Usb2AHB_ohci register values are acquired.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_get_s_usb2_ahb_ohci(DdGpvSlave *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_S_Usb2AHB_ohci: input param error. [gpv_ctrl_s] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->slaveFMA = ioGpv.sUsb2AhbOhci.fma;
	self->slaveFM = ioGpv.sUsb2AhbOhci.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_WifiAHB_m_ib register.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_s_wifiahb_m_ib(DdGpvSlave const *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->slaveFMA > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fma] = 0x%lx\n", self->slaveFMA));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->slaveFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fm] = 0x%lx\n", self->slaveFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sWifiAhbMIb.fma = self->slaveFMA;
	ioGpv.sWifiAhbMIb.fm = self->slaveFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Uhs2AHB_m register.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_s_uhs2_ahb_m(DdGpvSlave const *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->slaveFMA > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", self->slaveFMA));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->slaveFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", self->slaveFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sUhs2AhbM.fma = self->slaveFMA;
	ioGpv.sUhs2AhbM.fm = self->slaveFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_RelcrAHB_m register.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_s_relcr_ahb_m(DdGpvSlave const *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->slaveFMA > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fma] = 0x%lx\n", self->slaveFMA));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->slaveFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fm] = 0x%lx\n", self->slaveFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sRelcrAhbM.fma = self->slaveFMA;
	ioGpv.sRelcrAhbM.fm = self->slaveFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Uhs1AHB_m register.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_s_uhs1_ahb_m(DdGpvSlave const *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->slaveFMA > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fma] = 0x%lx\n", self->slaveFMA));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->slaveFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fm] = 0x%lx\n", self->slaveFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sUhs1AhbM.fma = self->slaveFMA;
	ioGpv.sUhs1AhbM.fm = self->slaveFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_RelcwAHB_m register.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_s_relcw_ahb_m(DdGpvSlave const *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->slaveFMA > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fma] = 0x%lx\n", self->slaveFMA));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->slaveFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fm] = 0x%lx\n", self->slaveFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sRelcwAhbM.fma = self->slaveFMA;
	ioGpv.sRelcwAhbM.fm = self->slaveFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_BmNicAHB_m register.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_s_bm_nic_ahb_m(DdGpvSlave const *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->slaveFMA > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fma] = 0x%lx\n", self->slaveFMA));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->slaveFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fm] = 0x%lx\n", self->slaveFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sBmNicAhbM.fma = self->slaveFMA;
	ioGpv.sBmNicAhbM.fm = self->slaveFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Usb2AHB_ehci register.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_s_usb2_ahb_ehci(DdGpvSlave const *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->slaveFMA > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fma] = 0x%lx\n", self->slaveFMA));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->slaveFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fm] = 0x%lx\n", self->slaveFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sUsb2AhbEhci.fma = self->slaveFMA;
	ioGpv.sUsb2AhbEhci.fm = self->slaveFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Usb2AHB_ohci register.
 * @param	T_DD_GPV_CTRL_S* gpv_ctrl_s
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_s_usb2_ahb_ohci(DdGpvSlave const *self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->slaveFMA > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fma] = 0x%lx\n", self->slaveFMA));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->slaveFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_s.fm] = 0x%lx\n", self->slaveFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sUsb2AhbOhci.fma = self->slaveFMA;
	ioGpv.sUsb2AhbOhci.fm = self->slaveFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Usb3_r_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_usb3_r_ib_fmib(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mUsb3RIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Usb3_r_ib FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_usb3_r_ib_fm2(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mUsb3RIb.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Usb3_r_ib FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_usb3_r_ib_fm(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mUsb3RIb.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Emmc_r_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_emmc_r_ib_fmib(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mEmmcRIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Emmc_r_ib FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_emmc_r_ib_fm2(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mEmmcRIb.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Emmc_r_ib FML register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_emmc_r_ib_fml(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mEmmcRIb.fml = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Emmc_r_ib FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_emmc_r_ib_fm(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mEmmcRIb.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Uhs2_r_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_uhs2_r_ib_fmib(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mUhs2RIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Uhs2_r_ib FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_uhs2_r_ib_fm2(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mUhs2RIb.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Uhs2_r_ib FML register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_uhs2_r_ib_fml(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mUhs2RIb.fml = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Uhs2_r_ib FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_uhs2_r_ib_fm(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mUhs2RIb.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Mxic1_m_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_mxic1_m_ib_fmib(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mMxic1MIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Mxic1_m_ib WT register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_mxic1_m_ib_wt(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_WT_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mMxic1MIb.wt = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Mxic1_m_ib FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_mxic1_m_ib_fm(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mMxic1MIb.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Mxic2_m_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_mxic2_m_ib_fmib(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mMxic2MIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Mxic2_m_ib WT register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_mxic2_m_ib_wt(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_WT_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mMxic2MIb.wt = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Mxic2_m_ib FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_mxic2_m_ib_fm(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mMxic2MIb.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Xdmac_r_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_xdmac_r_ib_fmib(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mXdmacRIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Xdmac_r_ib FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_xdmac_r_ib_fm2(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mXdmacRIb.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Xdmac_r_ib FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_xdmac_r_ib_fm(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mXdmacRIb.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Nf_r_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_nf_r_ib_fmib(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNfRIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Nf_r_ib FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_nf_r_ib_fm2(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNfRIb.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Nf_r_ib FML register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_nf_r_ib_fml(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNfRIb.fml = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Nf_r_ib FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_nf_r_ib_fm(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNfRIb.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Pcie0_r_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_pcie0_r_ib_fmib(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mPcie0RIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Pcie0_r_ib FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_pcie0_r_ib_fm2(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mPcie0RIb.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Pcie0_r_ib FML register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_pcie0_r_ib_fml(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mPcie0RIb.fml = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Pcie0_r_ib FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_pcie0_r_ib_fm(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mPcie0RIb.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Pcie1_r_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_pcie1_r_ib_fmib(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mPcie1RIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Pcie1_r_ib FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_pcie1_r_ib_fm2(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mPcie1RIb.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Pcie1_r_ib FML register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_pcie1_r_ib_fml(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mPcie1RIb.fml = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_Pcie1_r_ib FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_pcie1_r_ib_fm(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mPcie1RIb.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicPeriAHB_m_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_nic_peri_ahb_m_ib_fmib(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNicPeriAhbMIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicPeriAHB_m_ib FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_nic_peri_ahb_m_ib_fm2(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNicPeriAhbMIb.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicPeriAHB_m_ib AC register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_nic_peri_ahb_m_ac(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_AC_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNicPeriAhbMIb.ac = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicBmAHB1_r_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_slave_set_m_nic_bm_ahb1_r_ib_fmib(DdGpvSlave *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNicBmAhb1RIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

DdGpvSlave* dd_gpv_slave_new(void)
{
	DdGpvSlave* self = k_object_new_with_private(DD_TYPE_GPV_SLAVE, sizeof(DdGpvSlavePrivate));
	return self;
}
