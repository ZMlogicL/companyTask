/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 王顺
*@brief : DdIpcuMb
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __DD_IPCU_MB_H__
#define __DD_IPCU_MB_H__

#include <klib.h>
#include <string.h>
#include "ddarm.h"
#include "ddimusercustom.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DD_TYPE_IPCU_MB                  (dd_ipcu_mb_get_type())
#define DD_IPCU_MB(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdIpcuMb))
#define DD_IS_IPCU_MB(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DD_TYPE_IPCU_MB))

#define C_IPCU_UNIT_TOTAL_NUM			(3)									/* Total number of IPCU Unit 			*/
#define C_IPCU_UNIT_MAX						(C_IPCU_UNIT_TOTAL_NUM - 1)		/* IPCU Unit Max Value					*/
#define C_IPCU_ID_TOTAL_NUM				(16)								/* Total number of IPCU ID				*/
#define C_IPCU_ID_MAX							(C_IPCU_ID_TOTAL_NUM - 1)		/* IPCU ID Max Value 					*/


typedef struct _DdIpcuMb DdIpcuMb;
typedef struct _DdIpcuMbPrivate DdIpcuMbPrivate;

struct _DdIpcuMb
{
	KObject parent;
};


KConstType		dd_ipcu_mb_get_type(void);
DdIpcuMb*		dd_ipcu_mb_new(void);
/**
It is Interrupt Handler of IPCU request.<br>
@param [in] intCh	Interrupt CH number(0 to 15)
@remarks This API uses DDIM_User_Set_Flg ().
*/
void				dd_ipcu_int_handler_req(DdIpcuMb *self, kuint32 intCh );

/**
Get Request data to global variable.
@param [in] id		IPCU ID(0 to 17)
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@remarks	This API uses DDIM_User_Clr_Flg ().
@remarks	This API uses DDIM_User_Twai_Flg ().
*/
kint32				dd_ipcu_wait_req(DdIpcuMb *self, kulong id );

/**
Get Request data from global variable.
@param [in] id		IPCU ID(0 to 17)
@param [in]	data	Top address of request data.
@param [in]	length	Size of data.
@retval		D_DDIM_OK					: OK
@retval		C_IPCU_WAIT_TIMEOUT		: IPCU wait timeout error
*/
kint32				dd_ipcu_get_req_data(DdIpcuMb *self, kulong id, kulong *data, kuchar length );

/**
Set Request callback function.
@param [in] unit	IPCU unit(0-2)
@param [in] ch		IPCU interrupt ch(0-17)
@param [in] reqFnPtr	Callback function of Request
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_set_req_cb(DdIpcuMb *self, kulong unit, kulong ch, void (* reqFnPtr )( kuchar ));

/**
Clear Destination information indicated by IPCU ch
@param [in] id		IPCU ID(0 to 17)
@param [in] dstCh 	Request transmit destination ch(0-15)
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
 */
kint32				dd_ipcu_mb_clr_mb_dst_unit(DdIpcuMb *self, kuchar id, kulong dstCh );

/**
Get Destination information
@param [in] id		IPCU ID(0 to 17)
@param [out] dst 	Request transmit destination by bit data
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_mb_get_mb_dst_stat(DdIpcuMb * self, kuchar id, kulong * dst );

/**
Get Destination information indicated by IPCU ch
@param [in] id		IPCU ID(0 to 17)
@param [in] dstCh 	Request transmit destination ch(0-15)
@param [out] dst 	Request transmit destination by bit data
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_mb_get_mb_dst_stat_unit(DdIpcuMb * self, kuchar id, kulong dstCh, kulong * dst );

/**
Set Mask request
@param [in] id		IPCU ID(0 to 17)
@param [in] msk 	Mask request
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_mb_set_mb_msk(DdIpcuMb * self, kuchar id, kulong msk );

/**
Set Mask request indicated by IPCU ch
@param [in] id		IPCU ID(0 to 17)
@param [in] mskCh 	Request mask ch(0-15)
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
 */
kint32				dd_ipcu_mb_set_mb_msk_unit(DdIpcuMb *self, kuchar id, kulong mskCh);

/**
Clear Mask request
@param [in] id		IPCU ID(0 to 17)
@param [in] msk 	Mask request
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_mb_clr_mb_msk(DdIpcuMb * self, kuchar id, kulong msk );

/**
Clear Mask request indicated by IPCU ch
@param [in] id		IPCU ID(0 to 17)
@param [in] mskCh 	Request mask ch(0-15)
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_mb_clr_mb_msk_unit(DdIpcuMb * self, kuchar id, kulong mskCh );

/**
Get Mask request status
@param [in] id		IPCU ID(0 to 17)
@param [out] msk 	Mask request
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_mb_get_mb_msk_stat(DdIpcuMb * self, kuchar id, kulong * msk );

/**
Get Mask request indicated by IPCU ch
@param [in] id		IPCU ID(0 to 17)
@param [in] mskCh 	Request mask ch(0-15)
@param [out] msk 	Mask request
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_mb_get_mb_msk_stat_unit(DdIpcuMb * self, kuchar id, kulong mskCh, kulong * msk );

/**
Set Acknowledge
@param [in] id		IPCU ID(0 to 17)
@param [in] ack 	Acknowledge
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_mb_set_mb_ack(DdIpcuMb * self, kuchar id, kulong ack );

/**
Set Acknowledge indicated by IPCU ch
@param [in] id		IPCU ID(0 to 17)
@param [in] ackCh 	Acknowledge ch(0-15)
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
 */
kint32				dd_ipcu_mb_set_mb_ack_unit(DdIpcuMb * self, kuchar id, kulong ackCh );

/**
Clear Acknowledge indicated by IPCU ch
@param [in] id		IPCU ID(0 to 17)
@param [in] ack 	Acknowledge
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
 */
kint32				dd_ipcu_mb_clr_mb_ack(DdIpcuMb * self, kuchar id, kulong ack );

/**
Clear Acknowledge indicated by IPCU ch
@param [in] id		IPCU ID(0 to 17)
@param [in] ackCh 	Acknowledge ch(0-15)
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_mb_clr_mb_ack_unit(DdIpcuMb * self, kuchar id, kulong ackCh );

/**
Get Acknowledge status
@param [in] id		IPCU ID(0 to 17)
@param [out] ack 	Acknowledge
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_mb_get_mb_ack_stat(DdIpcuMb * self, kuchar id, kulong * ack );

/**
Get Acknowledge indicated by IPCU ch
@param [in] id		IPCU ID(0 to 17)
@param [in] ackCh 	Acknowledge ch(0-15)
@param [out] ack 	Acknowledge
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_mb_get_mb_ack_stat_unit(DdIpcuMb * self, kuchar id, kulong ackCh, kulong * ack );

/**
Get Acknowledge source information
@param [in] id		IPCU ID(0 to 17)
@param [out] ack 	Acknowledge  source
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_mb_get_mb_ack_src(DdIpcuMb * self, kuchar id, kulong * ack );

/**
Get Source information indicated by IPCU ch
@param [in] id		IPCU ID(0 to 17)
@param [in] ackCh	Interrupt ch of IPCU(0-15)
@param [out] ack  	Acknowledge source
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
@retval		C_IPCU_STATUS_ABNORMAL	: IPCU status error
*/
kint32				dd_ipcu_mb_get_mb_ack_src_unit(DdIpcuMb * self, kuchar id, kulong ackCh, kulong * ack );

/**
Get Transfer data
@param [in] id		IPCU ID(0 to 17)
@param [in] datNum	Transfer data No.
@param [out] data 	Transfer data
@retval		D_DDIM_OK					: OK
@retval		D_DD_IPCU_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32				dd_ipcu_mb_get_mb_data(DdIpcuMb * self, kuchar id, kuchar datNum, kulong * data );

#ifdef __cplusplus
}
#endif

#endif /* __DD_IPCU_MB_H__ */
