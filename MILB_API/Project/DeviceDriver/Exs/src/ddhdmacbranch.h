/*
* @上海网用软件有限公司
*
* Date        : 2020-9-4
*
* Author    : zhou hong
*
* Version   :0.0.0
*
* Description :功能描述
*/

#ifndef __DD_HDMAC_BRANCH_H__
#define __DD_HDMAC_BRANCH_H__

#include <klib.h>
#include "driver_common.h"
#include "ddhdmac.h"

#define DD_TYPE_HDMAC_BRANCH     (dd_hdmac_branch_get_type())
#define DD_HDMAC_BRANCH(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, DdHdmacBranch))
#define DD_IS_HDMAC_BRANCH(obj)  (K_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_HDMAC_BRANCH))

typedef struct _DdHdmacBranch                	DdHdmacBranch;
typedef struct _DdHdmacBranchPrivate 		DdHdmacBranchPrivate;

struct _DdHdmacBranch
{
	KObject parent;
};

KConstType 				dd_hdmac_branch_get_type(void);
DdHdmacBranch* 	dd_hdmac_branch_new(void);

/**
The operation of HDMAC of specified ch is stopped.

@param [in] ch				Channel number (0 to 3)
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	dd_hdmac_branch_stop(DdHdmacBranch *self, kuchar ch);

/**
The operation of HDMAC of specified ch is paused.

@param [in] ch				Channel number (0 to 3)
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	dd_hdmac_branch_pause(DdHdmacBranch *self, kuchar ch);

/**
The status bit of the dmacb register is cleared.

@param [in] ch				Channel number (0 to 3)
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	dd_hdmac_branch_clear_status(DdHdmacBranch *self, kuchar ch);

/**
The content of the dmacb register is acquired.

@param [in] ch				Channel number (0 to 3)
@param [out] *status		Channel Status Register pointer
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	dd_hdmac_branch_get_status(DdHdmacBranch *self, kuchar ch, kushort *const status);

/**
The operation of HDMAC of specified ch is resumed.

@param [in] ch				Channel number (0 to 3)
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
@remarks	This API uses ddim_user_custom_clr_flg(priv->ddimUserCustom,).
*/
kint32	dd_hdmac_branch_resume(DdHdmacBranch *self, kuchar ch);

/**
The value of the source address (dmacsa) of the specified channel is acquired.

@param [in] ch				Channel number (0 to 3)
@retval src_addr					source address of the specified channel
*/
kulong	dd_hdmac_branch_get_src_addr(DdHdmacBranch *self, kuchar ch);

/**
The value of the destination address (dmacda) of the specified channel is acquired.

@param [in] ch				Channel number (0 to 3)
@retval dst_addr					Destination address of the specified channel
*/
kulong	dd_hdmac_branch_get_dst_addr(DdHdmacBranch *self, kuchar ch);

/**
Source Protection code is set.

@param [in] ch					Channel number (0 to 3)
@param [in] protect_code		Source Protection Code (4'b0000 to 4'b1111)<br>
								AHB HPROT[3:0] value.<br>
								[0] = 0:Opcode fetch, 1:Data access (Not effect)<br>
								[1] = 0:User mode access, 1:Supervisor mode access (Not effect)<br>
								[2] = 0:Nonbufferable access, 1:Bufferable access (Not effect)<br>
								[3] = 0:Noncachable access, 1:Cachable access<br>
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	dd_hdmac_branch_set_source_protect(DdHdmacBranch *self, kuchar ch, kuchar protect_code);

/**
Destination Protection code is set.

@param [in] ch					Channel number (0 to 3)
@param [in] protect_code		Destination Protection Code (4'b0000 to 4'b1111)<br>
								AHB HPROT[3:0] value.<br>
								[0] = 0:Opcode fetch, 1:Data access (Not effect)<br>
								[1] = 0:User mode access, 1:Supervisor mode access (Not effect)<br>
								[2] = 0:Nonbufferable access, 1:Bufferable access (Not effect)<br>
								[3] = 0:Noncachable access, 1:Cachable access<br>
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	dd_hdmac_branch_set_destination_protect(DdHdmacBranch *self, kuchar ch, kuchar protect_code);

/**
Arbitration mode is set.

@param [in] arbitration		Arbitration mode. (0 or 1)
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
@remarks There is an influence in all channels when setting it because it is a common register to all channels.
*/
kint32	dd_hdmac_branch_set_arbitration(DdHdmacBranch *self, kuchar arbitration);

/**
Arbitration mode is read.

@param [out] *arbitration		Arbitration mode.
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	dd_hdmac_branch_get_arbitration(DdHdmacBranch *self, kuchar *const arbitration);

/**
Arbitration mode is returned to an initial value.

@remarks There is an influence in all channels when setting it because it is a common register to all channels.
*/
void	dd_hdmac_branch_clear_arbitration(DdHdmacBranch *self);

/**
The operation of All HDMAC channel is stopped.
*/
void	dd_hdmac_branch_stop_all_ch(DdHdmacBranch *self);

/**
The operation of All HDMAC channel is resumed.
*/
void	dd_hdmac_branch_resume_all_ch(DdHdmacBranch *self);

/**
It is API that returns the value set to the register of TW.

@param [in] src_addr			soruce address
@param [in] dst_addr			destination address
@param [in] total_size			total size
@retval TW value set to register of TW
@remarks Total MAX size of this API as following.<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
         	kuchar transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
*/
kuchar	dd_hdmac_branch_get_trns_width(DdHdmacBranch *self, kulong src_addr, kulong dst_addr, kulong total_size);

#endif /* __DD_HDMAC_BRANCH_H__ */
