/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 王顺
*@brief : DdNic
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/
/**
 * @file		dd_nic.c
 * @brief		NIC-400 (Network Inter Connect) driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#include "ddnic.h"
#include "ddarm.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdNic, dd_nic);

#define DD_NIC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdNicPrivate, DD_TYPE_NIC))


struct _DdNicPrivate
{

};


static kulong S_GDD_NIC_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));

/**
DECLS
*/

/**
IMPL
*/
static void dd_nic_constructor(DdNic *self)
{
//	DdNicPrivate *priv = DD_NIC_GET_PRIVATE(self);
}

static void dd_nic_destructor(DdNic *self)
{
//	DdNicPrivate *priv = DD_NIC_GET_PRIVATE(self);
}

/**
PUBLIC
*/
/**
 * @brief	Set to Slave 1 security setting register
 * @param	kulong val
 * @return	D_DDIM_OK/D_DD_NIC_INPUT_PARAM_ERROR
 */
kint32 dd_nic_set_addrctrl_security1(DdNic *self, kulong val)
{
#ifdef CO_PARAM_CHECK
	if (val > C_NIC_SECURITY1_MAX) {
		Ddim_Assertion(("NIC: input param error. [val] = %lx\n", val));
		return C_NIC_INPUT_PARAM_ERR;
	}
#endif
	DD_ARM_CRITICAL_SECTION_START(S_GDD_NIC_SPIN_LOCK);
	ioNicAddrctrl.security1.word = val;
	DD_ARM_DMB_POU();
	DD_ARM_CRITICAL_SECTION_END(S_GDD_NIC_SPIN_LOCK);
	return D_DDIM_OK;
}

/**
 * @brief	Set to ASIB Tidemark register
 * @param	kuint32 num, kulong val
 * @return	D_DDIM_OK/D_DD_NIC_INPUT_PARAM_ERROR
 */
kint32 dd_nic_set_asib_wr_tidemark(DdNic *self, kuint32 num, kulong val)
{
#ifdef CO_PARAM_CHECK
	if (num > C_NIC_NODE_NUM_MAX) {
		Ddim_Assertion(("NIC: input param error. [num] = %x\n", num));
		return C_NIC_INPUT_PARAM_ERR;
	}
	if (val > C_NIC_TIDEMARK_VAL_MAX) {
		Ddim_Assertion(("NIC: input param error. [val] = %lx\n", val));
		return C_NIC_INPUT_PARAM_ERR;
	}
#endif
	ioNicAsib[num].wrTidemark.bit.wt = val;

	return D_DDIM_OK;
}

/**
 * @brief	Set to ASIB Read Channel QoS register
 * @param	kuint32 num, kulong val
 * @return	D_DDIM_OK/D_DD_NIC_INPUT_PARAM_ERROR
 */
kint32 dd_nic_set_asib_read_qos(DdNic *self, kuint32 num, kulong val)
{
#ifdef CO_PARAM_CHECK
	if (num > C_NIC_NODE_NUM_MAX) {
		Ddim_Assertion(("NIC: input param error. [num] = %x\n", num));
		return C_NIC_INPUT_PARAM_ERR;
	}
	if (val > C_NIC_QOS_VAL_MAX) {
		Ddim_Assertion(("NIC: input param error. [val] = %lx\n", val));
		return C_NIC_INPUT_PARAM_ERR;
	}
#endif
	ioNicAsib[num].readQos.bit.rq = val;

	return D_DDIM_OK;
}

/**
 * @brief	Set to ASIB Write Channel QoS register
 * @param	kuint32 num, kulong val
 * @return	D_DDIM_OK/D_DD_NIC_INPUT_PARAM_ERROR
 */
kint32 dd_nic_set_asib_write_qos(DdNic *self, kuint32 num, kulong val)
{
#ifdef CO_PARAM_CHECK
	if (num > C_NIC_NODE_NUM_MAX) {
		Ddim_Assertion(("NIC: input param error. [num] = %x\n", num));
		return C_NIC_INPUT_PARAM_ERR;
	}
	if (val > C_NIC_QOS_VAL_MAX) {
		Ddim_Assertion(("NIC: input param error. [val] = %lx\n", val));
		return C_NIC_INPUT_PARAM_ERR;
	}
#endif

	ioNicAsib[num].writeQos.bit.wq = val;
	return D_DDIM_OK;
}

/**
 * @brief	Set to ASIB Functionality Modification register
 * @param	kuint32 num, kulong val
 * @return	D_DDIM_OK/D_DD_NIC_INPUT_PARAM_ERROR
 */
kint32 dd_nic_set_asib_func_mod(DdNic *self, kuint32 num, kulong val)
{
#ifdef CO_PARAM_CHECK
	if (num > C_NIC_NODE_NUM_MAX) {
		Ddim_Assertion(("NIC: input param error. [num] = %x\n", num));
		return C_NIC_INPUT_PARAM_ERR;
	}
	if (val > C_NIC_FM_VAL_MAX) {
		Ddim_Assertion(("NIC: input param error. [val] = %lx\n", val));
		return C_NIC_INPUT_PARAM_ERR;
	}
#endif
	ioNicAsib[num].fnMod.bit.fm = val;

	return D_DDIM_OK;
}

DdNic* dd_nic_new(void)
{
	DdNic* self = k_object_new_with_private(DD_TYPE_NIC, sizeof(DdNicPrivate));

	return self;
}
