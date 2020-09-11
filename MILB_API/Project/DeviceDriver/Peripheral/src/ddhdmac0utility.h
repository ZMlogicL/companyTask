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


#ifndef __DD_HDMAC0_UTILITY_UTILITY_H__
#define __DD_HDMAC0_UTILITY_UTILITY_H__

#include "klib.h"
#include "driver_common.h"


#define DD_TYPE_HDMAC0_UTILITY				(dd_hdmac0_utility_get_type())
#define DD_HDMAC0_UTILITY(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdHdmac0Utility))
#define DD_IS_HDMAC0_UTILITY(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_HDMAC0_UTILITY))


typedef struct _DdHdmac0Utility 		DdHdmac0Utility;
typedef struct _DdHdmac0UtilityPrivate 	DdHdmac0UtilityPrivate;

struct  _DdHdmac0Utility {
	KObject parent;
};

#ifdef __cplusplus
extern "C" {
#endif


KConstType			dd_hdmac0_utility_get_type(void);
DdHdmac0Utility* 	dd_hdmac0_utility_new(void);

#ifdef CO_DDIM_UTILITY_USE

/**
HDMAC0 forwarding between SDRAM-SDRAM.<br>
It waits until forwarding ends. (synchronization)

@param [in] ch			Channel number (0 to 7)
@param [in] srcAddr	source address
@param [in] dstAddr	destination address
@param [in] size		transfer size
@param [in] wait_mode	HDMAC0 end wait mode (D_DD_HDMAC0_UTILITY_WAITMODE_CPU or D_DD_HDMAC0_UTILITY_WAITMODE_EVENT)
@retval D_DDIM_OK					OK
@retval D_DD_HDMAC0_UTILITY_INPUT_PARAM_ERR	Input Parameter Error
@retval D_DD_HDMAC0_UTILITY_EXC_LOCK_NG		Lock Error (System Using designated channel number)
@retval D_DD_HDMAC0_UTILITY_BUSY_ERR		HDMAC0 is being forwarded.
@remarks The unit of forwarding makes a large size give priority.<br>
         <br>
         Transfer MAX size of this API as following.<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
         	BYTE transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
*/
INT32				dd_hdmac0_utility_copy_sdram_sync(DdHdmac0Utility *self, UCHAR ch, ULONG srcAddr, ULONG dstAddr, ULONG size, UINT32 wait_mode);

/**
HDMAC0 forwarding between SDRAM-SDRAM.<br>
It doesn't wait until the forwarding completion is done. (Asynchronization)

@param [in] ch			Channel number (0 to 7)
@param [in] srcAddr	source address
@param [in] dstAddr	destination address
@param [in] size		transfer size
@param [in] *intHandler	Pointer of callback function
@retval D_DDIM_OK					OK
@retval D_DD_HDMAC0_UTILITY_INPUT_PARAM_ERR	Input Parameter Error
@retval D_DD_HDMAC0_UTILITY_BUSY_ERR		HDMAC0 is being forwarded.
@remarks The unit of forwarding makes a large size give priority.<br>
         Please call dd_hdmac0_open(dd_hdmac0_get(), ) before calling this function.<br>
         Please call dd_hdmac0_close(dd_hdmac0_get(), ) when the HDMAC0 forwarding ends. <br>
         <br>
         Transfer MAX size of this API as following.<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
         	BYTE transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
*/
INT32				dd_hdmac0_utility_copy_sdram_async(DdHdmac0Utility *self, UCHAR ch, ULONG srcAddr, ULONG dstAddr, ULONG size, VP_CALLBACK intHandler);

/**
It is a function to transfer the input data of Audio by using HDMAC0. 
It doesn't wait until the forwarding completion is done. (Asynchronization)

@param [in] ch			Channel number (0 to 7)
@param [in] inputSel	input select
@param [in] srcAddr	source address
@param [in] dstAddr	destination address
@param [in] size		transfer size
@param [in] *intHandler	Pointer of callback function
@retval D_DDIM_OK					OK
@retval D_DD_HDMAC0_UTILITY_INPUT_PARAM_ERR	Input Parameter Error
@retval D_DD_HDMAC0_UTILITY_BUSY_ERR		HDMAC0 is being forwarded.
@remarks The unit of forwarding makes a large size give priority.<br>
         Please call dd_hdmac0_open(dd_hdmac0_get(), ) before calling this function.<br>
         Please call dd_hdmac0_close(dd_hdmac0_get(), ) when the HDMAC0 forwarding ends.<br>
         <br>
         Transfer MAX size of this API as following.<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 256KByte.<br>
*/
INT32				dd_hdmac0_utility_input_audio_async(DdHdmac0Utility *self, UCHAR ch, UCHAR inputSel, ULONG srcAddr, ULONG dstAddr, ULONG size, VP_CALLBACK intHandler);

/**
It is a function to transfer the output data of Audio by using HDMAC0. 
It doesn't wait until the forwarding completion is done. (Asynchronization)

@param [in] ch			Channel number (0 to 7)
@param [in] inputSel	input select
@param [in] srcAddr	source address
@param [in] dstAddr	destination address
@param [in] size		transfer size
@param [in] *intHandler	Pointer of callback function
@retval D_DDIM_OK						OK
@retval D_DD_HDMAC0_UTILITY_INPUT_PARAM_ERR	Input Parameter Error
@retval D_DD_HDMAC0_UTILITY_BUSY_ERR		HDMAC0 is being forwarded.
@remarks The unit of forwarding makes a large size give priority.<br>
         Please call dd_hdmac0_open(dd_hdmac0_get(), ) before calling this function.<br>
         Please call dd_hdmac0_close(dd_hdmac0_get(), ) when the HDMAC0 forwarding ends.<br>
         <br>
         Transfer MAX size of this API as following.<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 256KByte.<br>
*/
INT32				dd_hdmac0_utility_output_audio_async(DdHdmac0Utility *self, UCHAR ch, UCHAR inputSel, ULONG srcAddr, ULONG dstAddr, ULONG size, VP_CALLBACK intHandler);

#endif

#ifdef __cplusplus
}
#endif


#endif	// __DD_HDMAC0_UTILITY_UTILITY_H__
