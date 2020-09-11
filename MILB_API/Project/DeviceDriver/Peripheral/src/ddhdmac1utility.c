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


#include "peripheral.h"
#include "driver_common.h"
#include "ddhdmac1.h"
#include "ddhdmac1utility.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdHdmac1Utility, dd_hdmac1_utility);
#define DD_HDMAC1_UTILITY_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdHdmac1UtilityPrivate, DD_TYPE_HDMAC1_UTILITY))


struct _DdHdmac1UtilityPrivate
{
};


static void dd_hdmac1_utility_constructor(DdHdmac1Utility *self)
{
}

static void dd_hdmac1_utility_destructor(DdHdmac1Utility *self)
{

}

#ifdef CO_DDIM_UTILITY_USE
/**
 * @brief  HDMAC1 Copy Sync for SDRAM
 * @param  UCHAR		ch				Channel number (0 to 7)
 * @param  ULONG		srcAddr		source address
 * @param  ULONG		dstAddr		destination address
 * @param  ULONG		size			Copy size
 * @param  INT32		wait_mode		HDMAC1 end wait mode
 * @return INT32		D_DDIM_OK
 */
INT32 dd_hdmac1_utility_copy_sdram_sync(DdHdmac1Utility *self, UCHAR ch, ULONG srcAddr, ULONG dstAddr, ULONG size, UINT32 wait_mode)
{
	INT32                 ret;
	USHORT                status = 0;
	Hdmac1CtrlTrns hdmac1_ctrl_trns;
	UCHAR tmp_width;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if ((srcAddr == 0) || (dstAddr == 0)) {
		Ddim_Assertion(("HDMAC1: input param error. [addr] = 0\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if (size == 0) {
		Ddim_Assertion(("HDMAC1: input param error. [size] = 0\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if ((wait_mode != DdHdmac1_WAITMODE_CPU) && (wait_mode != DdHdmac1_WAITMODE_EVENT)) {
		Ddim_Assertion(("HDMAC1: input param error. [wait_mode] = %x\n", wait_mode));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	// Check transfer size
	if (((srcAddr & 0x03) == 0) && ((dstAddr & 0x03) == 0) && ((size & 0x03) == 0)) {
		hdmac1_ctrl_trns.size.trnsWidth = DdHdmac1_TW_WORD;
	}
	else if (((srcAddr & 0x01) == 0) && ((dstAddr & 0x01) == 0) && ((size & 0x01) == 0)) {
		hdmac1_ctrl_trns.size.trnsWidth = DdHdmac1_TW_HWORD;
	}
	else {
		hdmac1_ctrl_trns.size.trnsWidth = DdHdmac1_TW_BYTE;
	}

	// Parameter Setting
	hdmac1_ctrl_trns.mode.inputSel = DdHdmac1_IS_SOFT;
	hdmac1_ctrl_trns.mode.modeSel  = DdHdmac1_MS_BLK;
	hdmac1_ctrl_trns.mode.srcFix   = DdHdmac1_FS_INCR;
	hdmac1_ctrl_trns.mode.dstFix   = DdHdmac1_FD_INCR;
	tmp_width = 0x01 << hdmac1_ctrl_trns.size.trnsWidth;
	if (size > (tmp_width * 16)) {
		hdmac1_ctrl_trns.mode.beatType = DdHdmac1_BT_INCR16;
	}
	else {
		hdmac1_ctrl_trns.mode.beatType  = DdHdmac1_BT_NORMAL;
	}

	hdmac1_ctrl_trns.size.trnsSize = size;
	hdmac1_ctrl_trns.size.srcAddr  = srcAddr;
	hdmac1_ctrl_trns.size.dstAddr  = dstAddr;

	hdmac1_ctrl_trns.intHandler = NULL;

	ret = dd_hdmac1_open(dd_hdmac1_get(), ch, D_DDIM_WAIT_END_TIME);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("HDMAC1 Util Copy Sync. Open ERR : ret=0x%x\n", ret));
		return ret;
	}
	while (1) {
		ret = dd_hdmac1_ctrl_trns(dd_hdmac1_get(), ch, &hdmac1_ctrl_trns);
		if (ret != D_DDIM_OK) {
			Ddim_Print(("HDMAC1 Util Copy Sync. Ctrl ERR : ret=0x%x\n", ret));
			break;
		}
		ret = dd_hdmac1_start_sync(dd_hdmac1_get(), ch, &status, wait_mode);
		if (ret != D_DDIM_OK) {
			Ddim_Print(("HDMAC1 Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
		}
		break;
	}

	ret = dd_hdmac1_close(dd_hdmac1_get(), ch);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("HDMAC1 Util Copy Sync. Close ERR : ret=0x%x\n", ret));
	}

	return ret;
}

/**
 * @brief  HDMAC1 Copy Async SDRAM
 * @param  UCHAR		ch				Channel number (0 to 7)
 * @param  ULONG		srcAddr		source address
 * @param  ULONG		dstAddr		destination address
 * @param  ULONG		size			Copy size
 * @param  VP_CALLBACK	intHandler		Callback function pointer
 * @return INT32  		D_DDIM_OK
 */
INT32 dd_hdmac1_utility_copy_sdram_async(DdHdmac1Utility *self, UCHAR ch, ULONG srcAddr, ULONG dstAddr, ULONG size, VP_CALLBACK intHandler)
{
	INT32                 ret;
	Hdmac1CtrlTrns hdmac1_ctrl_trns;
	UCHAR tmp_width;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac1_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC1: input param error. [ch] = %x\n", ch));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if ((srcAddr == 0) || (dstAddr == 0)) {
		Ddim_Assertion(("HDMAC1: input param error. [addr] = 0\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
	if (size == 0) {
		Ddim_Assertion(("HDMAC1: input param error. [size] = 0\n"));
		return DdHdmac1_INPUT_PARAM_ERR;
	}
#endif

	// Check transfer size
	if (((srcAddr & 0x03) == 0) && ((dstAddr & 0x03) == 0) && ((size & 0x03) == 0)) {
		hdmac1_ctrl_trns.size.trnsWidth = DdHdmac1_TW_WORD;
	}
	else if (((srcAddr & 0x01) == 0) && ((dstAddr & 0x01) == 0) && ((size & 0x01) == 0)) {
		hdmac1_ctrl_trns.size.trnsWidth = DdHdmac1_TW_HWORD;
	}
	else {
		hdmac1_ctrl_trns.size.trnsWidth = DdHdmac1_TW_BYTE;
	}

	// Parameter Setting
	hdmac1_ctrl_trns.mode.inputSel = DdHdmac1_IS_SOFT;
	hdmac1_ctrl_trns.mode.modeSel  = DdHdmac1_MS_BLK;
	hdmac1_ctrl_trns.mode.srcFix   = DdHdmac1_FS_INCR;
	hdmac1_ctrl_trns.mode.dstFix   = DdHdmac1_FD_INCR;
	tmp_width = 0x01 << hdmac1_ctrl_trns.size.trnsWidth;
	if (size > (tmp_width * 16)) {
		hdmac1_ctrl_trns.mode.beatType = DdHdmac1_BT_INCR16;
	}
	else {
		hdmac1_ctrl_trns.mode.beatType  = DdHdmac1_BT_NORMAL;
	}

	hdmac1_ctrl_trns.size.trnsSize = size;
	hdmac1_ctrl_trns.size.srcAddr  = srcAddr;
	hdmac1_ctrl_trns.size.dstAddr  = dstAddr;

	hdmac1_ctrl_trns.intHandler = intHandler;

	ret = dd_hdmac1_ctrl_trns(dd_hdmac1_get(), ch, &hdmac1_ctrl_trns);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("HDMAC1 Util Copy Async. Ctrl ERR : ret=0x%x\n", ret));
		return ret;
	}
	ret = dd_hdmac1_start_async(dd_hdmac1_get(), ch);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("HDMAC1 Util Copy Async. Start ERR : ret=0x%x\n", ret));
		return ret;
	}
	return ret;
}

#endif

DdHdmac1Utility* dd_hdmac1_utility_new(void)
{
	DdHdmac1Utility* self = k_object_new_with_private(DD_TYPE_HDMAC1_UTILITY, sizeof(DdHdmac1UtilityPrivate));

	return self;
}
