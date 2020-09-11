/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 王顺
*@brief : DdIpcu
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/
/**
 * @file		ddipcu.h
 * @brief		IPCU (Inter-Processor Communications Unit) driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
/**
@addtogroup dd_ipcu
@{
	- @ref Send_Req_Sequence
	- @ref Receive_Req_Sequence
*/


#ifndef __DD_IPCU_H__
#define __DD_IPCU_H__


#include <klib.h>
#include "arm.h"
#include "driver_common.h"
#include "ddipcumb.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DD_TYPE_IPCU                  (dd_ipcu_get_type())
#define DD_IPCU(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdIpcu))
#define DD_IS_IPCU(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DD_TYPE_IPCU))

//---------------------------- driver section ----------------------------
/* Return value of IPCU processing result */
#define C_IPCU_INPUT_PARAM_ERR				(D_DD_IPCU | D_DDIM_INPUT_PARAM_ERROR)
/**< Input parameter error				*/
#define C_IPCU_STATUS_ABNORMAL				(D_DD_IPCU | D_DDIM_STATUS_ABNORMAL)
/**< IPCU status error					*/
#define C_IPCU_MB_BUSY								(D_DD_IPCU | D_DDIM_DATA_EXIST_ERROR)
/**< IPCU Mailbox busy					*/
#define C_IPCU_WAIT_TIMEOUT						(D_DD_IPCU | D_DDIM_TIMEOUT)
/**< IPCU wait timeout error			*/
#define C_IPCU_SEM_TIMEOUT						(D_DD_IPCU | D_DDIM_SEM_TIMEOUT)
/**< Semaphore acquisition Time Out 	*/
#define C_IPCU_SEM_NG									(D_DD_IPCU | D_DDIM_SEM_NG)
/**< Semaphore acquisition NG 			*/

#define C_IPCU_MB_DATA_TOTAL_NUM			(9)
/**< Total Number of Mailbox Data 		*/
#define C_IPCU_MB_DATA_MAX						(C_IPCU_MB_DATA_TOTAL_NUM - 1)
/**< Mailbox Data Max Value 			*/
#define C_IPCU_DATA_BLK_MAX						(9)
/**< Total number of IPCU send data		*/
#define C_IPCU_SEND_DATA_MAX					(4 * C_IPCU_DATA_BLK_MAX)
/**< Total number of IPCU data size		*/
#define C_IPCU_INT_TOTAL_NUM					(16)
/**< Total number of Interrupt Channel 	*/
#define C_IPCU_INT_MAX								(C_IPCU_INT_TOTAL_NUM - 1)
/**< Interrupt Channel Max Value		*/
#define C_IPCU_MB_TOTAL_NUM					(16)
/**< Total Number of Mailboxes 			*/
#define C_IPCU_MB_MAX									(C_IPCU_MB_TOTAL_NUM - 1)
/**< Mailbox Max Value 					*/
#define C_IPCU_DATA_LENGTH						(36)
/**< IPCU send data length				*/
#define C_IPCU_STATE_NONE							(0)
/**< IPCU not used						*/
#define C_IPCU_STATE_KEEP							(1)
/**< IPCU set and not send				*/


/** IPCU Mailbox Mode */
typedef enum _DdIpcuMbMode DdIpcuMbMode;

enum _DdIpcuMbMode
{
	DdIpcu_IPCU_MB_MODE_MANUAL_1 = 0,		/**< 000b:Manual Mode 1 	*/
	DdIpcu_IPCU_MB_MODE_MANUAL_2,				/**< 001b:Manual Mode 2 	*/
	DdIpcu_IPCU_MB_MODE_AUTO_ACK_1,			/**< 010b:Auto Acknowledge Mode 1 */
	DdIpcu_IPCU_MB_MODE_AUTO_ACK_2,			/**< 011b:Auto Acknowledge Mode 2 */
	DdIpcu_IPCU_MB_MODE_AUTO_CLEAR,			/**< 100b:Auto Clear Mode 	*/
	DdIpcu_IPCU_MB_MODE_MAX
};


typedef struct _DdIpcu DdIpcu;
typedef struct _DdIpcuPrivate DdIpcuPrivate;

//结构体名字T_DD_IPCU_MNG改为DdIpcuMng，其成员名字规范，将其全部成员放入类结构体中。
struct _DdIpcu
{
	KObject parent;
	DdIpcuMbMode mode; /**< Mailbox mode
	 <ul><li>@ref DdIpcu_IPCU_MB_MODE_MANUAL_1
	 <li>@ref DdIpcu_IPCU_MB_MODE_MANUAL_2
	 <li>@ref DdIpcu_IPCU_MB_MODE_AUTO_ACK_1
	 <li>@ref DdIpcu_IPCU_MB_MODE_AUTO_ACK_2
	 <li>@ref DdIpcu_IPCU_MB_MODE_AUTO_CLEAR</ul> */
	kulong srcChNum; /**< Source ch (0 to 15)		*/
	kulong dstChBit; /**< Dest ch bit (Bit position is equal to ch No.)	*/
	kulong maskChBit; /**< Mask ch bit (Bit position is equal to ch No.)	*/
	kulong sendData[9]; /**< Send data		*/
	kulong dataSize; /**< Send data size */
//	VpCallback			ack_func;			/**< ACK function pointer */
};


KConstType		dd_ipcu_get_type(void);
DdIpcu* 			dd_ipcu_new(void);
void				dd_ipcu_memcpy_ulong(DdIpcu *self, kulong* const dst, kulong* const src, kuint32 cpSize );

/**
Execute exclusive control for designated IPCU unit and Mailbox.<br>
@param [in]	mbNum 	Mailbox No.(0 to 15)
@param [in] tmout	Time of timeout<br>
					<ul><li>Positive Value(Time of timeout)
						<li>@ref D_DDIM_USER_SEM_WAIT_POL
						<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
@param [out] id		IPCU ID(0 to 15)
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
@retval		C_IPCU_MB_BUSY			: IPCU Mailbox busy
*/
kint32				dd_ipcu_open(DdIpcu *self, kuchar mbNum, kint32 tmout, kuchar *id );

/**
Cancel exclusive control for designated IPCU unit and Mailbox.<br>
@param [in] id		IPCU ID(0 to 17)
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_close(DdIpcu *self, kuchar id );

/**
Set IPCU operation condition and callback function for designated IPCU unit and Mailbox.
@param [in] id		IPCU ID(0 to 17)
@param [in]	self	IPCU Control data. See @ref DdIpcu.
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_ctrl(kuchar id, DdIpcu const* const self );

/**
Get IPCU operation condition and callback function for designated IPCU unit and Mailbox.
@param [in]  id		IPCU ID(0 to 17)
@param [out] self	IPCU Control data. See @ref DdIpcu.
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_get_ctrl(kuchar id, DdIpcu *const self );

/**
Start sending data.
@param [in]  id		IPCU ID(0 to 17)
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@remarks	This API uses DDIM_User_Clr_Flg().
@remarks	This API uses DDIM_User_Twai_Flg().
*/
kint32				dd_ipcu_start(DdIpcu *self, kuchar id );

/**
It is Interrupt Handler of IPCU acknowledge.<br>
@param [in] intCh	Interrupt CH number(0 to 15)
@param [out] mbNum Mailbox No.(0 to 17)
*/
void				dd_ipcu_int_handler_ack(DdIpcu *self, kuint32 intCh, kulong *mbNum );


/**
Get Request data to global variable.
@param [in] mbNum	Mailbox number(0-17)
@param [in] intCh	Interrupt CH number(0 to 15)
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@remarks	This API uses DDIM_User_Set_Flg().
*/
kint32				dd_ipcu_start_ack_proc(DdIpcu *self, kulong mbNum, kulong intCh );

/**
Set Acknowledge callback function.
@param [in] id		IPCU ID(0 to 17)
@param [in] ackFnPtr	Callback function of Acknowledge
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_set_ack_cb(DdIpcu *self, kuchar id, void (* ackFnPtr )( kuchar ));

/**
Get Interrupt Status
@param [in]	unit 	Unit number(0 to 2)
@param [in] ch		IPCU Interrupt CH number(0 to 15)
@param [out] state  Interrupt Status
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_get_int_stat(DdIpcu *self, kulong unit, kulong ch, kulong* state );

/**
Get Interrupt Status indicated by Mailbox Number
@param [in]	unit 	Unit number(0 to 2)
@param [in] ch		IPCU Interrupt CH number(0 to 15)
@param [in] mbNum	Mailbox number
@param [out] state	Interrupt Status
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_get_int_stat_mb(DdIpcu *self,  kulong unit, kulong ch, kuchar mbNum, kulong *state );

/**
Get Acknowledge status
@param [in]	unit 	Unit number(0 to 2)
@param [in] ch		IPCU Interrupt CH number(0 to 15)
@param [out] ack	Acknowledge Status
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_get_mb_ack(DdIpcu *self, kulong unit, kulong ch, kulong *ack );

/**
Get Request status
@param [in]	unit 	Unit number(0 to 2)
@param [in] ch		IPCU Interrupt CH number(0 to 15)
@param [out] req	Request Status
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_get_mb_req(DdIpcu *self, kulong unit, kulong ch, kulong *req );

/**
Get Mailbox Address
@param [in]	unit 	Unit number(0 to 2)
@param [in] ch		IPCU Interrupt CH number(0 to 15)
@param [out] mba	Mailbox Address
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_get_mb_adr(DdIpcu *self,  kulong unit, kulong ch, kulong *mba );

/**
Get Source information
@param [in] id		IPCU ID(0 to 17)
@param [out] src 	Request transmit source
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_get_mb_src(DdIpcu *self, kuchar id, kulong *src );

/**
Get Source information indicated by IPCU ch
@param [in] id		IPCU ID(0 to 17)
@param [in] srcCh	Interrupt ch of IPCU(0-15)
@param [out] src 	Request transmit source
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_get_mb_src_unit(DdIpcu *self, kuchar id, kulong srcCh, kulong *src );

/**
Set Source information
@param [in] id		IPCU ID(0 to 17)
@param [in] src 	Request transmit source
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_set_mb_src(DdIpcu *self, kuchar id, kulong src );

/**
Get Mode information
@param [in] id		IPCU ID(0 to 17)
@param [out] mode 	Operation mode
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_get_mb_mode(DdIpcu *self, kuchar id, kulong *mode );

/**
Set Mode information
@param [in] id		IPCU ID(0 to 17)
@param [in] mode 	Operation mode
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_set_mb_mode(DdIpcu *self, kuchar id, DdIpcuMbMode mode );

/**
Get Send trigger
@param [in] id		IPCU ID(0 to 17)
@param [out] send 	Send trigger
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_get_mb_send(DdIpcu *self, kuchar id, kulong *send );

/**
Set Send trigger
@param [in] id		IPCU ID(0 to 17)
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_set_mb_send(DdIpcu *self, kuchar id );

/**
Set Destination information
@param [in] id		IPCU ID(0 to 17)
@param [in] dst 	Request transmit destination
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_set_mb_dst(DdIpcu *self, kuchar id, kulong dst );

/**
Set Destination information indicated by IPCU ch
@param [in] id		IPCU ID(0 to 17)
@param [in] dstCh 	Request transmit destination ch(0-15)
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_set_mb_dst_unit(DdIpcu *self, kuchar id, kulong dstCh );

/**
Clear Destination information
@param [in] id		IPCU ID(0 to 17)
@param [in] dst 	Request transmit destination by bit data
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_clr_mb_dst(DdIpcu *self, kuchar id, kulong dst );

/**
Set Transfer data
@param [in] id		IPCU ID(0 to 17)
@param [in] dat_num	Transfer data No.
@param [in] data 	Transfer data
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_mb_set_mb_data(DdIpcu *self, kuchar id, kuchar dat_num, kulong data );

/**
Get MailBox status
@param [in]	unit 		Unit number(0 to 2)
@param [out] mb_stat 	MailBox status
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_mb_get_mb_stat(DdIpcu *self, kuchar unit, kulong *mb_stat );

/**
Get Mailbox Status indicated by Mailbox Number
@param [in]	unit 	Unit number(0 to 2)
@param [in] num		Mailbox number(0 to 7)
@param [out] mb_stat MailBox status
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
 */
kint32				dd_ipcu_mb_get_mb_stat_mb(DdIpcu *self,  kuchar unit, kulong num, kulong *mb_stat );

/*@}*/

/**
@weakgroup dd_ipcu
@{
	@section Send_Req_Sequence		Sequence example of sending request and receiving acknowledge on IPCU.
	@image html IPCU_Send_Req_Receive_Ack.png
	<br>
	@section Receive_Req_Sequence		Sequence example of receiving request on IPCU.
	@image html IPCU_Receive_Req.png
	<br>
*/
/*@}*/

#ifdef __cplusplus
}
#endif

#endif	// _DD_IPCU_H_
