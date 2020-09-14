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
*2、将dd_xdmac.h中最后两个关于拷贝的公有方法移到这里
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __DD_XDMAC_COPY_SDRAM_H__
#define __DD_XDMAC_COPY_SDRAM_H__

#include <klib.h>
#include "driver_common.h"
#include "ddxdmac.h"

#define DD_TYPE_XDMAC_COPY_SDRAM     (dd_xdmac_copy_sdram_get_type())
#define DD_XDMAC_COPY_SDRAM(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, DdXdmacCopySdram))
#define DD_IS_XDMAC_COPY_SDRAM(obj)  (K_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_XDMAC_COPY_SDRAM))

typedef struct _DdXdmacCopySdram                DdXdmacCopySdram;
typedef struct _DdXdmacCopySdramPrivate DdXdmacCopySdramPrivate;

struct _DdXdmacCopySdram
{
	KObject parent;
};

KConstType dd_xdmac_copy_sdram_get_type(void);
DdXdmacCopySdram* dd_xdmac_copy_sdram_new(void);



#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
/** @name Utility Functions
@{*/
/**
DMA forwarding between SDRAM-SDRAM.<br>
It waits until forwarding ends. (synchronization)
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@param [in]	src_addr					: Source address
@param [in]	dst_addr					: Destination address
@param [in]	size						: Transfer size
@param [in]	waitMode					: DMA end wait mode
										<ul>
										<li>@ref DdXdmac_WAITMODE_CPU
										<li>@ref DdXdmac_WAITMODE_EVENT
										</ul>
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR		: Input Parameter Error
@retval	DdXdmac_EXC_LOCK_NG			: Lock Error (System Using designated channel number)
@retval	DdXdmac_BUSY_ERR				: DMA is being forwarded.
@remarks	The unit of forwarding makes a large size give priority.<br>
			Transfer MAX size of this API as following.
			<ul>
			<li>WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.
			<li>HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.
			<li>kuchar transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.
			</ul>
*/
extern	kint32	dd_xdmac_copy_sdram_sync(DdXdmacCopySdram *self, kuchar ch,\
		kulong srcAddr, kulong dstAddr, kulong size, kuint32 waitMode);

/**
DMA forwarding between SDRAM-SDRAM.<br>
It doesn't wait until the forwarding completion is done. (Asynchronization)
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@param [in]	src_addr					: Source address
@param [in]	dst_addr					: Destination address
@param [in]	size						: Transfer size
@param [in]	intHandler					: Pointer of callback function
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR		: Input Parameter Error
@retval	DdXdmac_BUSY_ERR				: DMA is being forwarded
@remarks	The unit of forwarding makes a large size give priority.<br>
			Please call Dd_XDMAC_Open() before calling this function.<br>
			Please call dd_xdmac_close() when the DMA forwarding ends.<br>
			Transfer MAX size of this API as following.<br>
			<ul>
			<li>WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
			<li>HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
			<li>kuchar transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
			</ul>
*/
extern	kint32	dd_xdmac_copy_sdram_async(DdXdmacCopySdram *self, kuchar ch,\
		kulong srcAddr, kulong dstAddr, kulong size, VpCallback intHandler);
/*@}*/
#endif

#ifdef __cplusplus
}
#endif


#endif /* __DD_XDMAC_COPY_SDRAM_H__ */
