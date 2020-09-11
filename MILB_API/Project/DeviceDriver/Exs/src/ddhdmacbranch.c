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

#include "peripheral.h"
#include "driver_common.h"
#include "ddimusercustom.h"
#include "ddarm.h"
#include "ddhdmacbranch.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdHdmacBranch, dd_hdmac_branch);
#define DD_HDMAC_BRANCH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), DdHdmacBranchPrivate, DD_TYPE_HDMAC_BRANCH))

struct _DdHdmacBranchPrivate
{
    int a;
    DdimUserCustom			*ddimUserCustom;
   //TODO: ddim_user_custom.c类中
};

static void dd_hdmac_branch_constructor(DdHdmacBranch *self)
{
	DdHdmacBranchPrivate *priv = DD_HDMAC_BRANCH_GET_PRIVATE(self);
    priv->a = 0;
    priv->ddimUserCustom = ddim_user_custom_get();
}

static void dd_hdmac_branch_destructor(DdHdmacBranch *self)
{
	DdHdmacBranchPrivate *priv = DD_HDMAC_BRANCH_GET_PRIVATE(self);
    if(priv->ddimUserCustom){
        k_object_unref(priv->ddimUserCustom);
        priv->ddimUserCustom = NULL;
    }
}

/*----------------------------------------------------------------------*/
/* PUBLIC(公有函数接口实现)									*/
/*----------------------------------------------------------------------*/
/**
 * @brief  The operation of HDMAC of specified ch is stopped.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32	DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_branch_stop(DdHdmacBranch *self, kuchar ch)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	ioHdmac.dmac[ch].dmaca.word &= 0x7FFFFFFF;
	DD_ARM_DSB_POU();

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC of specified ch is stopped.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32	DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_branch_pause(DdHdmacBranch *self, kuchar ch)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	ioHdmac.dmac[ch].dmaca.bit.pb = 1;
	DD_ARM_DSB_POU();

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  The status of HDMAC of specified ch is cleared.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32				DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_branch_clear_status(DdHdmacBranch *self, kuchar ch)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	ioHdmac.dmac[ch].dmacb.bit.ss = 0;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  The error status of HDMAC of specified ch is cleared.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32				DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_branch_get_status(DdHdmacBranch *self, kuchar ch, kushort *const status)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
	if (status == NULL) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [*status] NULL\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	*status = ioHdmac.dmac[ch].dmacb.bit.ss;
	return DriverCommon_DDIM_OK;
}

/**
 * @brief  The operation of HDMAC of specified ch is resumed.
 * @param  kuchar	ch			Channel number (0 to 3)
 * @return kint32	DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_branch_resume(DdHdmacBranch *self, kuchar ch)
{
	DdHdmacBranchPrivate *priv = DD_HDMAC_BRANCH_GET_PRIVATE(self);
#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	switch (ch) {
		case 0:
			ddim_user_custom_clr_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, ~DdHdmac_FLG_CH0);
			break;

		case 1:
			ddim_user_custom_clr_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, ~DdHdmac_FLG_CH1);
			break;

		case 2:
			ddim_user_custom_clr_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, ~DdHdmac_FLG_CH2);
			break;

		case 3:
			ddim_user_custom_clr_flg(priv->ddimUserCustom, DdimUserCustom_FID_DD_HDMAC, ~DdHdmac_FLG_CH3);
			break;

		default:
			break;
	}

	ioHdmac.dmac[ch].dmaca.bit.pb = 0;
	ioHdmac.dmac[ch].dmaca.bit.eb = 1;			// HDMAC Start
	DD_ARM_DSB_POU();

	return DriverCommon_DDIM_OK;
}

/**
The value of the source address (dmacsa) of the specified channel is acquired.

@param [in] ch				Channel number (0 to 3)
@retval src_addr					source address of the specified channel
*/
kulong dd_hdmac_branch_get_src_addr(DdHdmacBranch *self, kuchar ch)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	return ioHdmac.dmac[ch].dmacsa;
}

/**
The value of the destination address (dmacda) of the specified channel is acquired.

@param [in] ch				Channel number (0 to 3)
@retval dst_addr					Destination address of the specified channel
*/
kulong dd_hdmac_branch_get_dst_addr(DdHdmacBranch *self, kuchar ch)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	return ioHdmac.dmac[ch].dmacda;
}

/**
Source Protection code is set.

@param [in] ch					Channel number (0 to 3)
@param [in] protect_code		Protection Code
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32 dd_hdmac_branch_set_source_protect(DdHdmacBranch *self, kuchar ch, kuchar protect_code)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	ioHdmac.dmac[ch].dmacb.bit.sp = protect_code;
	return DriverCommon_DDIM_OK;
}

/**
Destination Protection code is set.

@param [in] ch					Channel number (0 to 3)
@param [in] protect_code		Protection Code
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32 dd_hdmac_branch_set_destination_protect(DdHdmacBranch *self, kuchar ch, kuchar protect_code)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (ch >= DdHdmac_CH_NUM_MAX) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [ch] = %x\n", ch));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	ioHdmac.dmac[ch].dmacb.bit.dp = protect_code;
	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Arbitration level and HDMAC forwarding control interrupt level of all channels are set.
 * @param  T_DD_HDMAC_ARBITRATION*	arbitration
 * @return kint32				DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_branch_set_arbitration(DdHdmacBranch *self, kuchar arbitration)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if ((arbitration != DdHdmac_ARB_FIX) && (arbitration != DdHdmac_ARB_ROTATE)) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [arbitration] = %x\n", arbitration));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	// Arbitration type is set
	ioHdmac.dmacr.bit.pr = arbitration;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Arbitration level and HDMAC forwarding control interrupt level of all channels are read.
 * @param  T_DD_HDMAC_ARBITRATION*	arbitration
 * @return kint32				DriverCommon_DDIM_OK / DdHdmac_INPUT_PARAM_ERR
 */
kint32 dd_hdmac_branch_get_arbitration(DdHdmacBranch *self, kuchar *const arbitration)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (arbitration == NULL) {
		DriverCommon_DDIM_ASSERTION(("HDMAC: input param error. [*arbitration] NULL\n"));
		return DdHdmac_INPUT_PARAM_ERR;
	}
#endif

	// Arbitration type is set
	*arbitration = ioHdmac.dmacr.bit.pr;

	return DriverCommon_DDIM_OK;
}

/**
 * @brief  Arbitration level and HDMAC forwarding control interrupt level of all channels are returned to an initial value.
 * @param  void
 * @return void
 */
void dd_hdmac_branch_clear_arbitration(DdHdmacBranch *self)
{
	// Arbitration type is set
	ioHdmac.dmacr.bit.pr = 0;
}

/**
The operation of All HDMAC channel is stopped.
*/
void dd_hdmac_branch_stop_all_ch(DdHdmacBranch *self)
{
	// HDMAC Halt
	ioHdmac.dmacr.bit.dh = 1;
}

/**
The operation of All HDMAC channel is resumed.
*/
void dd_hdmac_branch_resume_all_ch(DdHdmacBranch *self)
{
	// HDMAC resume
	ioHdmac.dmacr.bit.dh = 0;
}

/**
It is API that returns the value set to the register of TW.

@param [in] src_addr			soruce address
@param [in] dst_addr			destination address
@param [in] total_size			total size
@retval TW value set to register of TW
*/
kuchar dd_hdmac_branch_get_trns_width(DdHdmacBranch *self, kulong src_addr, kulong dst_addr, kulong total_size)
{
	kuchar trns_width;

	// Check transfer size
	if (((src_addr & 0x03) == 0) && ((dst_addr & 0x03) == 0) && ((total_size & 0x03) == 0)) {
		trns_width = DdHdmac_TW_WORD;
	}
	else if (((src_addr & 0x01) == 0) && ((dst_addr & 0x01) == 0) && ((total_size & 0x01) == 0)) {
		trns_width = DdHdmac_TW_HWORD;
	}
	else {
		trns_width = DdHdmac_TW_BYTE;
	}

	return trns_width;
}

DdHdmacBranch* dd_hdmac_branch_new(void)
{
	DdHdmacBranch* self = k_object_new_with_private(DD_TYPE_HDMAC_BRANCH, sizeof(DdHdmacBranchPrivate));
	return self;
}
