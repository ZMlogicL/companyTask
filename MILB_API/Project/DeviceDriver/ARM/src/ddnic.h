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
 * @file		ddnic.h
 * @brief		NIC-400 (Network Inter Connect) driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

/**
@addtogroup dd_nic
@{
	- @ref dd_nic_sample_section1
*/


#ifndef __DD_NIC_H__
#define __DD_NIC_H__


#include <klib.h>
#include "driver_common.h"
#include "arm.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DD_TYPE_NIC                  (dd_nic_get_type())
#define DD_NIC(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdNic))
#define DD_IS_NIC(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DD_TYPE_NIC))

// Return value of NIC processing result
#define	C_NIC_INPUT_PARAM_ERR		(D_DD_NIC | D_DDIM_INPUT_PARAM_ERROR)
/**< Input Parameter Error */

// Max value of SECURITY1
#define C_NIC_SECURITY1_MAX			(65535)
/**< Security1 Max Value */

// Max number of ASIB node
#define C_NIC_NODE_NUM_MAX		(6)
/**< Node Max Number */

// Max value of Tidemark
#define C_NIC_TIDEMARK_VAL_MAX	(15)
/**< Tidemark Max Value */

// Max value of QoS
#define C_NIC_QOS_VAL_MAX				(15)
/**< Qos Max Value */

// Max value of Func Mod
#define C_NIC_FM_VAL_MAX				(1)
/**< Func Mod Max Value */

#define DdNic_GET_ASIB_WR_TIDEMARK(num)		(IO_NIC_ASIB[num].WR_TIDEMARK.bit.WT)
/**< Get Tidemark (num: 0 to @ref C_NIC_NODE_NUM_MAX) */
#define DdNic_GET_ASIB_READ_QOS(num)			(IO_NIC_ASIB[num].READ_QOS.bit.RQ)
/**< Get Read channel QoS (num: 0 to @ref C_NIC_NODE_NUM_MAX) */
#define DdNic_GET_ASIB_WRITE_QOS(num)			(IO_NIC_ASIB[num].WRITE_QOS.bit.WQ)
/**< Get Write channel QoS (num: 0 to @ref C_NIC_NODE_NUM_MAX) */
#define DdNic_GET_ASIB_FUNC_MOD(num)			(IO_NIC_ASIB[num].FN_MOD.bit.FM)
/**< Get Functionality Modification (num: 0 to @ref C_NIC_NODE_NUM_MAX) */


typedef struct _DdNic DdNic;
typedef struct _DdNicPrivate DdNicPrivate;

struct _DdNic
{
	KObject parent;
};


KConstType		dd_nic_get_type(void);
DdNic*			dd_nic_new(void);
/**
 Set to Slave 1 security setting register
 @param [in]	val							: Security 1 State ( 0 to @ref C_NIC_SECURITY1_MAX )
 1bit( 0:Secure 1:Non-Secure )
 @retval	D_DDIM_OK						: Normal end
 @retval	C_NIC_INPUT_PARAM_ERR		: Input Parameter Error
 */
kint32			dd_nic_set_addrctrl_security1(DdNic *self, kulong val);

/**
 Set to ASIB Tidemark register
 @param [in]	num							: ASIB Interface ID ( 0 to @ref C_NIC_NODE_NUM_MAX )
 @param [in]	val							: Tidemark ( 0 to @ref C_NIC_TIDEMARK_VAL_MAX )
 @retval	D_DDIM_OK						: Normal end
 @retval	C_NIC_INPUT_PARAM_ERR		: Input Parameter Error
 */
kint32			dd_nic_set_asib_wr_tidemark(DdNic *self, kuint32 num, kulong val);

/**
 Set to ASIB Read Channel QoS register
 @param [in]	num							: ASIB Interface ID ( 0 to @ref C_NIC_NODE_NUM_MAX )
 @param [in]	val							: Read Channel QoS ( 0 to @ref C_NIC_QOS_VAL_MAX )
 @retval	D_DDIM_OK						: Normal end
 @retval	C_NIC_INPUT_PARAM_ERR		: Input Parameter Error
 */
kint32			dd_nic_set_asib_read_qos(DdNic *self, kuint32 num, kulong val);

/**
 Set to ASIB Write Channel QoS register

 @param [in]	num							: ASIB Interface ID ( 0 to @ref C_NIC_NODE_NUM_MAX )
 @param [in]	val							: Write Channel QoS ( 0 to @ref C_NIC_QOS_VAL_MAX )
 @retval	D_DDIM_OK						: Normal end
 @retval	C_NIC_INPUT_PARAM_ERR		: Input Parameter Error
 */
kint32			dd_nic_set_asib_write_qos(DdNic *self, kuint32 num, kulong val);

/**
 Set to ASIB Functionality Modification register

 @param [in]	num							: ASIB Interface ID ( 0 to @ref C_NIC_NODE_NUM_MAX )
 @param [in]	val							: Issuing functionality modification
 <ul>
 <li>0:Read
 <li>1:Write
 </ul>
 @retval	D_DDIM_OK						: Normal end
 @retval	C_NIC_INPUT_PARAM_ERR		: Input Parameter Error
 */
kint32			dd_nic_set_asib_func_mod(DdNic *self, kuint32 num, kulong val);

/*@}*/

/**
 @weakgroup dd_nic
 @{
 @section dd_nic_sample_section1		Sample of "ASIB Functionality Modification"
 using dd_nic_set_asib_func_mod function.
 @code
 //
 // it prepares set the block write issuing capability to one outstanding transaction.
 //
 dd_nic_set_asib_func_mod(NULL,  0, 1 );
 //
 // After this, write issuing.
 //
 @endcode
 @}*/

#ifdef __cplusplus
}
#endif

#endif /* __DD_NIC_H__ */
