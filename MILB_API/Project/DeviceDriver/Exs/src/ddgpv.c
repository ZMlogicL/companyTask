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
*2、将dd_gpv.c更名为ddgpv.c,并将dd_gpv.c中所有的定义放在这里
*@version
*1.0.0 2020年06月开始开发
*/

#include "ddarm.h"
#include "ddgpv.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdGpv, dd_gpv);
#define DD_GPV_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), DdGpvPrivate, DD_TYPE_GPV))

struct _DdGpvPrivate
{
    volatile kuint32 gRemap;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static kulong S_DD_GPV_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));

static void dd_gpv_constructor(DdGpv *self)
{
	DdGpvPrivate *priv = DD_GPV_GET_PRIVATE(self);
    priv->gRemap = 0;
}

static void dd_gpv_destructor(DdGpv *self)
{

}

/*----------------------------------------------------------------------*/
/* PUBLIC(公有函数接口实现)									*/
/*----------------------------------------------------------------------*/
/**
 * @brief	Get to REMAP register.
 * @return	Remap value
 */
kuint32 dd_gpv_get_arc_remap(DdGpv *self)
{
	DdGpvPrivate *priv = DD_GPV_GET_PRIVATE(self);
	return priv->gRemap;
}

/**
 * @brief	Set to REMAP register.
 * @param	kulong val, kuint32 set
 * @return	DriverCommon_DDIM_OK/D_DD_GPV_INPUT_PARAM_ERROR
 */
kint32 dd_gpv_set_arc_remap(DdGpv *self, kulong val, kuint32 set)
{
	DdGpvPrivate *priv = DD_GPV_GET_PRIVATE(self);
#ifdef DriverCommon_CO_PARAM_CHECK
	if(val > DdGpv_REMAP_VAL_MAX){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [val] = 0x%lx\n", val)); //TODO:原型Ddim_Assertion定义在driver_common.h中
		return DdGpv_INPUT_PARAM_ERR;
	}
	if(set > 1){
		DriverCommon_DDIM_ASSERTION(("GPV: input param error. [set] = %d\n", set));
		return DdGpv_INPUT_PARAM_ERR;
	}
#endif
	DD_ARM_CRITICAL_SECTION_START(S_DD_GPV_SPIN_LOCK);//TODO:定义在dd_arm.h中原型DD_ARM_CRITICAL_SECTION_START(s)

	if(set){
		priv->gRemap |= val;
		ioGpv.remap.word = priv->gRemap;
	}else{
		priv->gRemap &= ~val;
		ioGpv.remap.word = priv->gRemap;
	}

	DD_ARM_DMB_POU();//TODO:定义在dd_arm.h中原型Dd_ARM_Dmb_Pou()
	DD_ARM_CRITICAL_SECTION_END(S_DD_GPV_SPIN_LOCK);

	return DriverCommon_DDIM_OK;//TODO:原型D_DDIM_OK定义在driver_common.h中
}


DdGpv* dd_gpv_get(void)
{
	static DdGpv *ddGpv = NULL;
	if(!ddGpv){
		ddGpv = k_object_new_with_private(DD_TYPE_GPV,sizeof(DdGpvPrivate));
	}
    return ddGpv;
}
