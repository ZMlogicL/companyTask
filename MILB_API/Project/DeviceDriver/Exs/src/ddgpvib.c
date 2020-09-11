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
*2、将dd_gpv.c里有关T_DD_GPV_CTRL_IB结构体调用的方法移到这里
*@version
*1.0.0 2020年06月开始开发
*/

#include "ddarm.h"
#include "ddgpvib.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdGpvIb, dd_gpv_ib);
#define DD_GPV_IB_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), DdGpvIbPrivate, DD_TYPE_GPV_IB))

struct _DdGpvIbPrivate
{
    int a;
};

static void dd_gpv_ib_constructor(DdGpvIb *self)
{
	DdGpvIbPrivate *priv = DD_GPV_IB_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_gpv_ib_destructor(DdGpvIb *self)
{

}

/*----------------------------------------------------------------------*/
/* PUBLIC(公有函数接口实现)									*/
/*----------------------------------------------------------------------*/
/**
 * @brief	IB8 register values are acquired.
 * @param	T_DD_GPV_CTRL_IB* gpv_ctrl_ib
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_get_ib8(DdGpvIb*const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK//TODO:driver_common.h中的定义(搜索/**< Compile Option of Parametre Check. */)
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_IB8: input param error. [gpv_ctrl_ib] NULL\n"));//driver_common.h中的定义(搜索/**< printf function inside DDIM */)
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->ibFMIB = ioGpv.ib8.fmib;
	self->ibFM2 = ioGpv.ib8.fm2;
	self->ibWT = ioGpv.ib8.wt;
	self->ibFM = ioGpv.ib8.fm;

	return DriverCommon_DDIM_OK;//driver_common.h中的定义
}

/**
 * @brief	IB13 register values are acquired.
 * @param	T_DD_GPV_CTRL_IB* gpv_ctrl_ib
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_get_ib13(DdGpvIb*const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_IB13: input param error. [gpv_ctrl_ib] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->ibFMIB = ioGpv.ib13.fmib;
	self->ibFM2 = ioGpv.ib13.fm2;
	self->ibFML = ioGpv.ib13.fml;
	self->ibFM = ioGpv.ib13.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB12 register values are acquired.
 * @param	T_DD_GPV_CTRL_IB* gpv_ctrl_ib
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_get_ib12(DdGpvIb*const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_IB12: input param error. [gpv_ctrl_ib] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->ibFMIB = ioGpv.ib12.fmib;
	self->ibFM2 = ioGpv.ib12.fm2;
	self->ibFM = ioGpv.ib12.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB9 register values are acquired.
 * @param	T_DD_GPV_CTRL_IB* gpv_ctrl_ib
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_get_ib9(DdGpvIb*const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK//TODO:定义在driver_common.h中
	if(self == NULL) {
		DriverCommon_DDIM_ASSERTION(("Dd_GPV_Get_IB9: input param error. [gpv_ctrl_ib] NULL\n"));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	// Register value acquisition
	self->ibFMIB = ioGpv.ib9.fmib;
	self->ibFM2 = ioGpv.ib9.fm2;
	self->ibWT = ioGpv.ib9.wt;
	self->ibFM = ioGpv.ib9.fm;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB8 register.
 * @param	T_DD_GPV_CTRL_IB* gpv_ctrl_ib
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib8(DdGpvIb const*const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->ibFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fmib] = 0x%lx\n", self->ibFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->ibFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fm2] = 0x%lx\n", self->ibFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->ibWT > DdGpv_WT_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.wt] = 0x%lx\n", self->ibWT));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->ibFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fm] = 0x%lx\n", self->ibFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib8.fmib = self->ibFMIB;
	ioGpv.ib8.fm2 = self->ibFM2;
	ioGpv.ib8.wt = self->ibWT;
	ioGpv.ib8.fm = self->ibFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB13 register.
 * @param	T_DD_GPV_CTRL_IB* gpv_ctrl_ib
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib13(DdGpvIb const*const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->ibFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fmib] = 0x%lx\n", self->ibFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->ibFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fm2] = 0x%lx\n", self->ibFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->ibFML > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fml] = 0x%lx\n", self->ibFML));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->ibFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fm] = 0x%lx\n", self->ibFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib13.fmib = self->ibFMIB;
	ioGpv.ib13.fm2 = self->ibFM2;
	ioGpv.ib13.fml = self->ibFML;
	ioGpv.ib13.fm = self->ibFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB12 register.
 * @param	T_DD_GPV_CTRL_IB* gpv_ctrl_ib
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib12(DdGpvIb const*const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->ibFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fmib] = 0x%lx\n", self->ibFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->ibFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fm2] = 0x%lx\n", self->ibFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->ibFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fm] = 0x%lx\n", self->ibFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib12.fmib = self->ibFMIB;
	ioGpv.ib12.fm2 = self->ibFM2;
	ioGpv.ib12.fm = self->ibFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB9 register.
 * @param	T_DD_GPV_CTRL_IB* gpv_ctrl_ib
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib9(DdGpvIb const *const self)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(self->ibFMIB > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fmib] = 0x%lx\n", self->ibFMIB));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->ibFM2 > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fm2] = 0x%lx\n", self->ibFM2));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->ibWT > DdGpv_WT_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.wt] = 0x%lx\n", self->ibWT));
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(self->ibFM > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [gpv_ctrl_ib.fm] = 0x%lx\n", self->ibFM));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib9.fmib = self->ibFMIB;
	ioGpv.ib9.fm2 = self->ibFM2;
	ioGpv.ib9.wt = self->ibWT;
	ioGpv.ib9.fm = self->ibFM;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB8 FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib8_fmib(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib8.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB8 FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib8_fm2(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib8.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB8 WT register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib8_wt(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_WT_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib8.wt = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB8 FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib8_fm(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib8.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB13 FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib13_fmib(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib13.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB13 FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib13_fm2(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib13.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB13 FML register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib13_fml(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FML_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib13.fml = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB13 FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib13_fm(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib13.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB12 FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib12_fmib(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib12.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB12 FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib12_fm2(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib12.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB12 FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib12_fm(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib12.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB9 FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib9_fmib(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib9.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB9 FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib9_fm2(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib9.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB9 WT register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib9_wt(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_WT_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib9.wt = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	IB9 FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_ib9_fm(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.ib9.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Netsec2_m FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_s_netsec2_m_fm(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sNetsec2M.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Uhs2AHB_m FMA register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_s_uhs2_ahb_m_fma(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sUhs2AhbM.fma = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Uhs2AHB_m FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_s_uhs2_ahb_m_fm(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sUhs2AhbM.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_RelcrAHB_m FMA register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_s_relcr_ahb_m_fma(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sRelcrAhbM.fma = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_RelcrAHB_m FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_s_relcr_ahb_m_fm(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sRelcrAhbM.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Uhs1AHB_m FMA register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_s_uhs1_ahb_m_fma(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sUhs1AhbM.fma = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicBmAHB1_r_ib AC register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_m_nic_bm_ahb1_r_ac(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_AC_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNicBmAhb1RIb.ac = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	NsecX2P_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_nsec_x2p_ib_fmib(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.nsecX2pIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	NsecX2P_ib FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_nsec_x2p_ib_fm2(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.nsecX2pIb.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	ToprX2P_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_topr_x2p_ib_fmib(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.toprX2pIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	ToprX2P_ib FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_topr_x2p_ib_fm2(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.toprX2pIb.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicBmAHB2_r_ib FMIB register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_m_nic_bm_ahb2_r_ib_fmib(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMIB_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNicBmAhb2RIb.fmib = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicBmAHB2_r_ib FM2 register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_m_nic_bm_ahb2_r_ib_fm2(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM2_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNicBmAhb2RIb.fm2 = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	M_NicBmAHB2_r_ib AC register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_m_nic_bm_ahb2_r_ac(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_AC_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.mNicBmAhb2RIb.ac = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Main_rm_ib FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_s_main_rm_ib_fm(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sMainRmIb.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Xdmac_m_ib FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_s_xdmac_m_ib_fm(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sXdmacMIb.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_Netsec_m FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_s_netsec_m_fm(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sNetsecM.fm = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_WifiAHB_m_ib FMA register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_s_wifiahb_m_fma(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FMA_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sWifiAhbMIb.fma = val;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief	S_WifiAHB_m_ib FM register.
 * @param	kulong val
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_ib_set_s_wifiahb_m_ib_fm(DdGpvIb *self, kulong val)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_FM_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	ioGpv.sWifiAhbMIb.fm = val;

	return DriverCommon_DDIM_OK;
}

DdGpvIb* dd_gpv_ib_new(void)
{
	DdGpvIb* self = k_object_new_with_private(DD_TYPE_GPV_IB, sizeof(DdGpvIbPrivate));
	return self;
}
