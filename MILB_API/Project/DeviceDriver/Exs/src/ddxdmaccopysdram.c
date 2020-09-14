/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
*@author              :周洪
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、XDMA driver
*2、将dd_xdmac.c中最后两个关于拷贝的公有方法移到这里
*@version
*1.0.0 2020年06月开始开发
*/

#include "ddarm.h"
#include "arm.h"
//#include "dd_exs.h"
#include "ddexs.h"
#include "ddexsbranch.h"
#include "ddxdmaccopysdram.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdXdmacCopySdram, dd_xdmac_copy_sdram);
#define DD_XDMAC_COPY_SDRAM_GET_PRIVATE(o)\
	(K_OBJECT_GET_PRIVATE ((o), DdXdmacCopySdramPrivate, DD_TYPE_XDMAC_COPY_SDRAM))

struct _DdXdmacCopySdramPrivate
{
    int a;
    DdXdmac *ddXdmac;
};

static void dd_xdmac_copy_sdram_constructor(DdXdmacCopySdram *self)
{
	DdXdmacCopySdramPrivate *priv = DD_XDMAC_COPY_SDRAM_GET_PRIVATE(self);
    priv->a = 0;
    priv->ddXdmac = dd_xdmac_get();
}

static void dd_xdmac_copy_sdram_destructor(DdXdmacCopySdram *self)
{
	DdXdmacCopySdramPrivate *priv = DD_XDMAC_COPY_SDRAM_GET_PRIVATE(self);
    if(priv->ddXdmac){
        k_object_unref(priv->ddXdmac);
        priv->ddXdmac = NULL;
    }
}

/*----------------------------------------------------------------------*/
/* PUBLIC(公有函数接口实现)									*/
/*----------------------------------------------------------------------*/
#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
/**
 * @brief  DMA Copy Sync for SDRAM
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  kulong		srcAddr		source address
 * @param  kulong		dstAddr		destination address
 * @param  kulong		size			Copy size
 * @param  kint32		waitMode		DMA end wait mode
 * @return kint32		DriverCommon_DDIM_OK
 */
kint32 dd_xdmac_copy_sdram_sync(DdXdmacCopySdram *self, kuchar ch, kulong srcAddr,\
		kulong dstAddr, kulong size, kuint32 waitMode)
{
	DdXdmacCopySdramPrivate *priv = DD_XDMAC_COPY_SDRAM_GET_PRIVATE(self);
	kint32              				ret;
	kushort             				status = 0;
	TDdXdmacCtrl 				dmaCtrlTrns;
	TDdXdmacCommon 	dmaCommon;

#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if((srcAddr == 0) || (dstAddr == 0)){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [addr] = 0\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(size == 0){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [size] = 0\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if((waitMode != DdXdmac_WAITMODE_CPU) && (waitMode != DdXdmac_WAITMODE_EVENT)){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [waitMode] = %x\n", waitMode));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif
	// Check transfer size
	if(((srcAddr & 0x07) == 0) && ((dstAddr & 0x07) == 0) && ((size & 0x07) == 0)){
		dmaCtrlTrns.configOne.bit.sBS = DdXdmac_XDSAC_SBS_DOUBLEWORD;
		dmaCtrlTrns.configOne.bit.dBS = DdXdmac_XDDAC_DBS_DOUBLEWORD;
	}
	else if(((srcAddr & 0x03) == 0) && ((dstAddr & 0x03) == 0) && ((size & 0x03) == 0)){
		dmaCtrlTrns.configOne.bit.sBS = DdXdmac_XDSAC_SBS_WORD;
		dmaCtrlTrns.configOne.bit.dBS = DdXdmac_XDDAC_DBS_WORD;
	}
	else if(((srcAddr & 0x01) == 0) && ((dstAddr & 0x01) == 0) && ((size & 0x01) == 0)){
		dmaCtrlTrns.configOne.bit.sBS = DdXdmac_XDSAC_SBS_HALFWORD;
		dmaCtrlTrns.configOne.bit.dBS = DdXdmac_XDDAC_DBS_HALFWORD;
	}
	else{
		dmaCtrlTrns.configOne.bit.sBS = DdXdmac_XDSAC_SBS_BYTE;
		dmaCtrlTrns.configOne.bit.dBS = DdXdmac_XDDAC_DBS_BYTE;
	}

	// Parameter Setting
	dmaCtrlTrns.trnsSize = size;
	dmaCtrlTrns.srcAddr = srcAddr;
	dmaCtrlTrns.dstAddr = dstAddr;
	dmaCtrlTrns.intHandler = NULL;

	dmaCtrlTrns.configOne.bit.sRL = DdXdmac_XDSAC_SRL_DISABLE;
	dmaCtrlTrns.configOne.bit.sAF = DdXdmac_XDSAC_SAF_NOTFIX;
	dmaCtrlTrns.configOne.bit.sBL = DdXdmac_XDSAC_SBL_LENGTH_16;
	dmaCtrlTrns.configOne.bit.dRL = DdXdmac_XDDAC_DRL_DISABLE;
	dmaCtrlTrns.configOne.bit.dAF = DdXdmac_XDDAC_DAF_NOTFIX;
	dmaCtrlTrns.configOne.bit.dBL = DdXdmac_XDDAC_DBL_LENGTH_16;

	if(waitMode == DdXdmac_WAITMODE_EVENT){
		dmaCtrlTrns.configOne.bit.tI = DdXdmac_XDDES_TI_ENABLE;
		dmaCtrlTrns.configOne.bit.eI = DdXdmac_XDDES_EI_ENABLE;
	}
	else{
		dmaCtrlTrns.configOne.bit.tI = DdXdmac_XDDES_TI_DISABLE;
		dmaCtrlTrns.configOne.bit.eI = DdXdmac_XDDES_EI_DISABLE;
	}

	dmaCtrlTrns.configOne.bit.aT = DdXdmac_XDDES_AT_SOURCE;
	dmaCtrlTrns.configOne.bit.bR = DdXdmac_XDDES_BR_DISABLE;
	dmaCtrlTrns.configOne.bit.bT = DdXdmac_XDDES_BT_ENABLE;
	dmaCtrlTrns.configOne.bit.sA = DdXdmac_XDDES_SA_ENABLE;
	dmaCtrlTrns.configOne.bit.tF = DdXdmac_XDDES_TF_SOFT;
	dmaCtrlTrns.configOne.bit.sE = DdXdmac_XDDES_SE_ENABLE;
	dmaCtrlTrns.configTwo.bit.dCN = DdXdmac_XDDCC_DCN_INVALID;
	dmaCtrlTrns.configTwo.bit.dCA = 0;

	dmaCommon.commonConfig.bit.xE = DdXdmac_XDACS_XE_ENABLE;
	dmaCommon.commonConfig.bit.cP = DdXdmac_XDACS_CP_FIXED;

	ret = dd_xdmac_open(priv->ddXdmac, ch, DriverCommon_DDIM_WAIT_END_TIME);
	if(ret != DriverCommon_DDIM_OK){
		DriverCommon_DDIM_PRINT(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
		return ret;
	}

	ret = dd_xdmac_ctrl_common(priv->ddXdmac, &dmaCommon);
	if(ret != DriverCommon_DDIM_OK){
		DriverCommon_DDIM_PRINT(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
		return ret;
	}

	while(1){
		ret = dd_xdmac_ctrl_trns(priv->ddXdmac, ch, &dmaCtrlTrns);
		if(ret != DriverCommon_DDIM_OK){
			DriverCommon_DDIM_PRINT(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
			break;
		}
		ret = dd_xdmac_start_sync(priv->ddXdmac, ch, &status, waitMode);
		if(ret != DriverCommon_DDIM_OK){
			DriverCommon_DDIM_PRINT(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
		}
		break;
	}

	ret = dd_xdmac_close(priv->ddXdmac, ch);
	if(ret != DriverCommon_DDIM_OK){
		DriverCommon_DDIM_PRINT(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
	}

	return ret;
}

/**
 * @brief  DMA Copy Async SDRAM
 * @param  kuchar		ch				Channel number (0 to 3)
 * @param  kulong		srcAddr		source address
 * @param  kulong		dstAddr		destination address
 * @param  kulong		size			Copy size
 * @param  VpCallback	intHandler		Callback function pointer
 * @return kint32  		DriverCommon_DDIM_OK
 */
kint32 dd_xdmac_copy_sdram_async(DdXdmacCopySdram *self, kuchar ch, kulong srcAddr,\
		kulong dstAddr, kulong size, VpCallback intHandler)
{
	DdXdmacCopySdramPrivate *priv = DD_XDMAC_COPY_SDRAM_GET_PRIVATE(self);
	kint32             			 	ret;
	TDdXdmacCtrl 				dmaCtrlTrns;
	TDdXdmacCommon 	dmaCommon;

#ifdef DriverCommon_CO_PARAM_CHECK
	if(ch >= DdXdmac_CH_NUM_MAX){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [ch] = %x\n", ch));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if((srcAddr == 0) || (dstAddr == 0)){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [addr] = 0\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
	if(size == 0){
		DriverCommon_DDIM_ASSERTION(("XDMAC: input param error. [size] = 0\n"));
		return DdXdmac_INPUT_PARAM_ERR;
	}
#endif
	// Check transfer size
	if(((srcAddr & 0x07) == 0) && ((dstAddr & 0x07) == 0) && ((size & 0x07) == 0)){
		dmaCtrlTrns.configOne.bit.sBS = DdXdmac_XDSAC_SBS_DOUBLEWORD;
		dmaCtrlTrns.configOne.bit.dBS = DdXdmac_XDDAC_DBS_DOUBLEWORD;
	}
	else if(((srcAddr & 0x03) == 0) && ((dstAddr & 0x03) == 0) && ((size & 0x03) == 0)){
		dmaCtrlTrns.configOne.bit.sBS = DdXdmac_XDSAC_SBS_WORD;
		dmaCtrlTrns.configOne.bit.dBS = DdXdmac_XDDAC_DBS_WORD;
	}
	else if(((srcAddr & 0x01) == 0) && ((dstAddr & 0x01) == 0) && ((size & 0x01) == 0)){
		dmaCtrlTrns.configOne.bit.sBS = DdXdmac_XDSAC_SBS_HALFWORD;
		dmaCtrlTrns.configOne.bit.dBS = DdXdmac_XDDAC_DBS_HALFWORD;
	}
	else{
		dmaCtrlTrns.configOne.bit.sBS = DdXdmac_XDSAC_SBS_BYTE;
		dmaCtrlTrns.configOne.bit.dBS = DdXdmac_XDDAC_DBS_BYTE;
	}

	// Parameter Setting
	dmaCtrlTrns.trnsSize = size;
	dmaCtrlTrns.srcAddr = srcAddr;
	dmaCtrlTrns.dstAddr = dstAddr;
	dmaCtrlTrns.intHandler = intHandler;

	dmaCtrlTrns.configOne.bit.sRL = DdXdmac_XDSAC_SRL_DISABLE;
	dmaCtrlTrns.configOne.bit.sAF = DdXdmac_XDSAC_SAF_NOTFIX;
	dmaCtrlTrns.configOne.bit.sBL = DdXdmac_XDSAC_SBL_LENGTH_16;
	dmaCtrlTrns.configOne.bit.dRL = DdXdmac_XDDAC_DRL_DISABLE;
	dmaCtrlTrns.configOne.bit.dAF = DdXdmac_XDDAC_DAF_NOTFIX;
	dmaCtrlTrns.configOne.bit.dBL = DdXdmac_XDDAC_DBL_LENGTH_16;

	dmaCtrlTrns.configOne.bit.tI = DdXdmac_XDDES_TI_ENABLE;
	dmaCtrlTrns.configOne.bit.eI = DdXdmac_XDDES_EI_ENABLE;

	dmaCtrlTrns.configOne.bit.aT = DdXdmac_XDDES_AT_SOURCE;
	dmaCtrlTrns.configOne.bit.bR = DdXdmac_XDDES_BR_DISABLE;
	dmaCtrlTrns.configOne.bit.bT = DdXdmac_XDDES_BT_ENABLE;
	dmaCtrlTrns.configOne.bit.sA = DdXdmac_XDDES_SA_ENABLE;
	dmaCtrlTrns.configOne.bit.tF = DdXdmac_XDDES_TF_SOFT;
	dmaCtrlTrns.configOne.bit.sE = DdXdmac_XDDES_SE_ENABLE;
	dmaCtrlTrns.configTwo.bit.dCN = DdXdmac_XDDCC_DCN_INVALID;
	dmaCtrlTrns.configTwo.bit.dCA = 0;

	dmaCommon.commonConfig.bit.xE = DdXdmac_XDACS_XE_ENABLE;
	dmaCommon.commonConfig.bit.cP = DdXdmac_XDACS_CP_FIXED;

	ret = dd_xdmac_ctrl_common(priv->ddXdmac, &dmaCommon);
	if(ret != DriverCommon_DDIM_OK){
		DriverCommon_DDIM_PRINT(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
		return ret;
	}

	ret = dd_xdmac_ctrl_trns(priv->ddXdmac, ch, &dmaCtrlTrns);
	if(ret != DriverCommon_DDIM_OK){
		DriverCommon_DDIM_PRINT(("DMA Util Copy Async. Ctrl ERR : ret=0x%x\n", ret));
		return ret;
	}

	ret = dd_xdmac_start_async(priv->ddXdmac, ch);
	if(ret != DriverCommon_DDIM_OK){
		DriverCommon_DDIM_PRINT(("DMA Util Copy Async. Start ERR : ret=0x%x\n", ret));
		return ret;
	}

	return ret;
}
#endif	// CO_DDIM_UTILITY_USE

DdXdmacCopySdram* dd_xdmac_copy_sdram_new(void)
{
	DdXdmacCopySdram* self = k_object_new_with_private(DD_TYPE_XDMAC_COPY_SDRAM, sizeof(DdXdmacCopySdramPrivate));
	return self;
}
