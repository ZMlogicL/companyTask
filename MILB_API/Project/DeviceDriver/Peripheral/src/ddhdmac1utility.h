/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月4日
 * @author            :冯黎阳
 * @brief             :
 * @rely              :klib
 * @function
 * @version
 *
 */


#ifndef __DD_HDMAC1_UTILITY_H__
#define __DD_HDMAC1_UTILITY_H__

#include "klib.h"
#include "driver_common.h"


#define DD_TYPE_HDMAC1_UTILITY				(dd_hdmac1_utility_get_type())
#define DD_HDMAC1_UTILITY(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdHdmac1Utility))
#define DD_IS_HDMAC1_UTILITY(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_HDMAC1_UTILITY))


typedef struct _DdHdmac1Utility 		DdHdmac1Utility;
typedef struct _DdHdmac1UtilityPrivate 	DdHdmac1UtilityPrivate;

struct  _DdHdmac1Utility {
	KObject parent;
};

#ifdef __cplusplus
extern "C" {
#endif

KConstType 			dd_hdmac1_utility_get_type(void);
DdHdmac1Utility* 	dd_hdmac1_utility_new(void);

#ifdef CO_DDIM_UTILITY_USE
/**
HDMAC1 forwarding between SDRAM-SDRAM.<br>
It waits until forwarding ends. (synchronization)

@param [in] ch			Channel number (0 to 7)
@param [in] srcAddr	source address
@param [in] dstAddr	destination address
@param [in] size		transfer size
@param [in] waitMode	HDMAC1 end wait mode (DdHdmac1_WAITMODE_CPU or DdHdmac1_WAITMODE_EVENT)
@retval D_DDIM_OK					OK
@retval DdHdmac1_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac1_EXC_LOCK_NG		Lock Error (System Using designated channel number)
@retval DdHdmac1_BUSY_ERR		HDMAC1 is being forwarded. 
@remarks The unit of forwarding makes a large size give priority.<br>
         <br>
         Transfer MAX size of this API as following.<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
         	BYTE transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
*/
kint32				dd_hdmac1_utility_copy_sdram_sync(DdHdmac1Utility *self, kuchar ch,
						kulong srcAddr, kulong dstAddr, kulong size, kuint32 waitMode);

/**
HDMAC1 forwarding between SDRAM-SDRAM.<br>
It doesn't wait until the forwarding completion is done. (Asynchronization)

@param [in] ch			Channel number (0 to 7)
@param [in] srcAddr	source address
@param [in] dstAddr	destination address
@param [in] size		transfer size
@param [in] *intHandler	Pointer of callback function
@retval D_DDIM_OK					OK
@retval DdHdmac1_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac1_BUSY_ERR		HDMAC1 is being forwarded. 
@remarks The unit of forwarding makes a large size give priority.<br>
         Please call dd_hdmac1_open(dd_hdmac1_get(), ) before calling this function.<br>
         Please call dd_hdmac1_close(dd_hdmac1_get(), ) when the HDMAC1 forwarding ends. <br>
         <br>
         Transfer MAX size of this API as following.<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
         	BYTE transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
*/
kint32				dd_hdmac1_utility_copy_sdram_async(DdHdmac1Utility *self, kuchar ch,
						kulong srcAddr, kulong dstAddr, kulong size, VpCallbackFunc intHandler);

#endif

#ifdef __cplusplus
}
#endif


#endif	// __DD_HDMAC1_UTILITY_H__
