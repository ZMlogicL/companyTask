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

#include "ddhdmac0.h"
#include "ddhdmac0utility.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdHdmac0Utility, dd_hdmac0_utility);
#define DD_HDMAC0_UTILITY_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdHdmac0UtilityPrivate, DD_TYPE_HDMAC0_UTILITY))


struct _DdHdmac0UtilityPrivate
{
};


static void dd_hdmac0_utility_constructor(DdHdmac0Utility *self)
{
}

static void dd_hdmac0_utility_destructor(DdHdmac0Utility *self)
{

}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
/**
 * @brief  HDMAC0 Copy Sync for SDRAM
 * @param  UCHAR		ch				Channel number (0 to 7)
 * @param  ULONG		srcAddr		source address
 * @param  ULONG		dstAddr		destination address
 * @param  ULONG		size			Copy size
 * @param  INT32		wait_mode		HDMAC0 end wait mode
 * @return INT32		D_DDIM_OK
 */
INT32 dd_hdmac0_utility_copy_sdram_sync(DdHdmac0Utility *self, UCHAR ch, ULONG srcAddr, ULONG dstAddr, ULONG size, UINT32 wait_mode)
{
	INT32                 ret;
	USHORT                status = 0;
	Hdmac0CtrlTrns hdmac0_ctrl_trns;
	UCHAR tmp_width;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if ((srcAddr == 0) || (dstAddr == 0)) {
		Ddim_Assertion(("HDMAC0: input param error. [addr] = 0\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (size == 0) {
		Ddim_Assertion(("HDMAC0: input param error. [size] = 0\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if ((wait_mode != DdHdmac0_WAITMODE_CPU) && (wait_mode != DdHdmac0_WAITMODE_EVENT)) {
		Ddim_Assertion(("HDMAC0: input param error. [wait_mode] = %x\n", wait_mode));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// Check transfer size
	if (((srcAddr & 0x03) == 0) && ((dstAddr & 0x03) == 0) && ((size & 0x03) == 0)) {
		hdmac0_ctrl_trns.size.trnsWidth = DdHdmac0_TW_WORD;
	}
	else if (((srcAddr & 0x01) == 0) && ((dstAddr & 0x01) == 0) && ((size & 0x01) == 0)) {
		hdmac0_ctrl_trns.size.trnsWidth = DdHdmac0_TW_HWORD;
	}
	else {
		hdmac0_ctrl_trns.size.trnsWidth = DdHdmac0_TW_BYTE;
	}

	// Parameter Setting
	hdmac0_ctrl_trns.mode.inputSel = DdHdmac0_IS_SOFT;
	hdmac0_ctrl_trns.mode.modeSel  = DdHdmac0_MS_BLK;
	hdmac0_ctrl_trns.mode.srcFix   = DdHdmac0_FS_INCR;
	hdmac0_ctrl_trns.mode.dstFix   = DdHdmac0_FD_INCR;
	tmp_width = 0x01 << hdmac0_ctrl_trns.size.trnsWidth;
	if (size > (tmp_width * 16)) {
		hdmac0_ctrl_trns.mode.beatType = DdHdmac0_BT_INCR16;
	}
	else {
		hdmac0_ctrl_trns.mode.beatType  = DdHdmac0_BT_NORMAL;
	}

	hdmac0_ctrl_trns.size.trnsSize = size;
	hdmac0_ctrl_trns.size.srcAddr  = srcAddr;
	hdmac0_ctrl_trns.size.dstAddr  = dstAddr;

	hdmac0_ctrl_trns.intHandler = NULL;

	ret = dd_hdmac0_open(dd_hdmac0_get(), ch, D_DDIM_WAIT_END_TIME);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("HDMAC0 Util Copy Sync. Open ERR : ret=0x%x\n", ret));
		return ret;
	}
	while (1) {
		ret = dd_hdmac0_ctrl_trns(dd_hdmac0_get(), ch, &hdmac0_ctrl_trns);
		if (ret != D_DDIM_OK) {
			Ddim_Print(("HDMAC0 Util Copy Sync. Ctrl ERR : ret=0x%x\n", ret));
			break;
		}
		ret = dd_hdmac0_start_sync(dd_hdmac0_get(), ch, &status, wait_mode);
		if (ret != D_DDIM_OK) {
			Ddim_Print(("HDMAC0 Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
		}
		break;
	}

	ret = dd_hdmac0_close(dd_hdmac0_get(), ch);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("HDMAC0 Util Copy Sync. Close ERR : ret=0x%x\n", ret));
	}

	return ret;
}

/**
 * @brief  HDMAC0 Copy Async SDRAM
 * @param  UCHAR		ch				Channel number (0 to 7)
 * @param  ULONG		srcAddr		source address
 * @param  ULONG		dstAddr		destination address
 * @param  ULONG		size			Copy size
 * @param  VP_CALLBACK	intHandler		Callback function pointer
 * @return INT32  		D_DDIM_OK
 */
INT32 dd_hdmac0_utility_copy_sdram_async(DdHdmac0Utility *self, UCHAR ch, ULONG srcAddr, ULONG dstAddr, ULONG size, VP_CALLBACK intHandler)
{
	INT32                 ret;
	Hdmac0CtrlTrns hdmac0_ctrl_trns;
	UCHAR tmp_width;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if ((srcAddr == 0) || (dstAddr == 0)) {
		Ddim_Assertion(("HDMAC0: input param error. [addr] = 0\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (size == 0) {
		Ddim_Assertion(("HDMAC0: input param error. [size] = 0\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// Check transfer size
	if (((srcAddr & 0x03) == 0) && ((dstAddr & 0x03) == 0) && ((size & 0x03) == 0)) {
		hdmac0_ctrl_trns.size.trnsWidth = DdHdmac0_TW_WORD;
	}
	else if (((srcAddr & 0x01) == 0) && ((dstAddr & 0x01) == 0) && ((size & 0x01) == 0)) {
		hdmac0_ctrl_trns.size.trnsWidth = DdHdmac0_TW_HWORD;
	}
	else {
		hdmac0_ctrl_trns.size.trnsWidth = DdHdmac0_TW_BYTE;
	}

	// Parameter Setting
	hdmac0_ctrl_trns.mode.inputSel = DdHdmac0_IS_SOFT;
	hdmac0_ctrl_trns.mode.modeSel  = DdHdmac0_MS_BLK;
	hdmac0_ctrl_trns.mode.srcFix   = DdHdmac0_FS_INCR;
	hdmac0_ctrl_trns.mode.dstFix   = DdHdmac0_FD_INCR;
	tmp_width = 0x01 << hdmac0_ctrl_trns.size.trnsWidth;
	if (size > (tmp_width * 16)) {
		hdmac0_ctrl_trns.mode.beatType = DdHdmac0_BT_INCR16;
	}
	else {
		hdmac0_ctrl_trns.mode.beatType  = DdHdmac0_BT_NORMAL;
	}

	hdmac0_ctrl_trns.size.trnsSize = size;
	hdmac0_ctrl_trns.size.srcAddr  = srcAddr;
	hdmac0_ctrl_trns.size.dstAddr  = dstAddr;

	hdmac0_ctrl_trns.intHandler = intHandler;

	ret = dd_hdmac0_ctrl_trns(dd_hdmac0_get(), ch, &hdmac0_ctrl_trns);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("HDMAC0 Util Copy Async. Ctrl ERR : ret=0x%x\n", ret));
		return ret;
	}
	ret = dd_hdmac0_start_async(dd_hdmac0_get(), ch);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("HDMAC0 Util Copy Async. Start ERR : ret=0x%x\n", ret));
		return ret;
	}
	return ret;
}

/**
 * @brief  HDMAC0 Copy Async for Audio (Audio Input)
 * @param  UCHAR		ch				Channel number (0 to 7)
 * @param  UCHAR		inputSel		input select
 * @param  ULONG		srcAddr		source address
 * @param  ULONG		dstAddr		destination address
 * @param  ULONG		size			transfer size
 * @param  VP_CALLBACK	intHandler		Callback function pointer
 * @return INT32		D_DDIM_OK
 */
INT32 dd_hdmac0_utility_input_audio_async(DdHdmac0Utility *self, UCHAR ch, UCHAR inputSel, ULONG srcAddr, ULONG dstAddr, ULONG size, VP_CALLBACK intHandler)
{
	INT32                 ret;
	Hdmac0CtrlTrns hdmac0_ctrl_trns;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if ((srcAddr == 0) || (dstAddr == 0)) {
		Ddim_Assertion(("HDMAC0: input param error. [addr] = 0\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (size == 0) {
		Ddim_Assertion(("HDMAC0: input param error. [size] = 0\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// Set register values to the table.
	hdmac0_ctrl_trns.mode.inputSel = inputSel;
	hdmac0_ctrl_trns.mode.modeSel  = DdHdmac0_MS_DEMAND;
	hdmac0_ctrl_trns.mode.srcFix   = DdHdmac0_FS_FIX;
	hdmac0_ctrl_trns.mode.dstFix   = DdHdmac0_FD_INCR;
	hdmac0_ctrl_trns.mode.beatType = DdHdmac0_BT_NORMAL;

	hdmac0_ctrl_trns.size.trnsWidth = DdHdmac0_TW_WORD;
	hdmac0_ctrl_trns.size.trnsSize  = size;
	hdmac0_ctrl_trns.size.srcAddr   = srcAddr;
	hdmac0_ctrl_trns.size.dstAddr   = dstAddr;

	hdmac0_ctrl_trns.intHandler     = intHandler;

	ret = dd_hdmac0_ctrl_trns(dd_hdmac0_get(), ch, &hdmac0_ctrl_trns);
	if (ret == D_DDIM_OK) {
		ret = dd_hdmac0_start_async(dd_hdmac0_get(), ch);
	}

	return ret;
}

/**
 * @brief  HDMAC0 Copy Async for Audio (Audio Output)
 * @param  UCHAR		ch				DMA Channel number (0 to 7)
 * @param  UCHAR		inputSel		input select
 * @param  ULONG		srcAddr		source address
 * @param  ULONG		dstAddr		destination address
 * @param  ULONG		size			transfer size
 * @param  VP_CALLBACK	intHandler		Callback function pointer
 * @return INT32		D_DDIM_OK
 */
INT32 dd_hdmac0_utility_output_audio_async(DdHdmac0Utility *self, UCHAR ch, UCHAR inputSel, ULONG srcAddr, ULONG dstAddr, ULONG size, VP_CALLBACK intHandler)
{
	INT32                 ret;
	Hdmac0CtrlTrns hdmac0_ctrl_trns;

#ifdef CO_PARAM_CHECK
	if (ch >= DdHdmac0_CH_NUM_MAX) {
		Ddim_Assertion(("HDMAC0: input param error. [ch] = %x\n", ch));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if ((srcAddr == 0) || (dstAddr == 0)) {
		Ddim_Assertion(("HDMAC0: input param error. [addr] = 0\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
	if (size == 0) {
		Ddim_Assertion(("HDMAC0: input param error. [size] = 0\n"));
		return DdHdmac0_INPUT_PARAM_ERR;
	}
#endif

	// Set register values to the table.
	hdmac0_ctrl_trns.mode.inputSel = inputSel;
	hdmac0_ctrl_trns.mode.modeSel  = DdHdmac0_MS_DEMAND;
	hdmac0_ctrl_trns.mode.srcFix   = DdHdmac0_FS_INCR;
	hdmac0_ctrl_trns.mode.dstFix   = DdHdmac0_FD_FIX;
	hdmac0_ctrl_trns.mode.beatType = DdHdmac0_BT_NORMAL;

	hdmac0_ctrl_trns.size.trnsWidth = DdHdmac0_TW_WORD;
	hdmac0_ctrl_trns.size.trnsSize  = size;
	hdmac0_ctrl_trns.size.srcAddr   = srcAddr;
	hdmac0_ctrl_trns.size.dstAddr   = dstAddr;

	hdmac0_ctrl_trns.intHandler     = intHandler;

	ret = dd_hdmac0_ctrl_trns(dd_hdmac0_get(), ch, &hdmac0_ctrl_trns);
	if (ret == D_DDIM_OK) {
		ret = dd_hdmac0_start_async(dd_hdmac0_get(), ch);
	}

	return ret;
}

#endif

DdHdmac0Utility* dd_hdmac0_utility_new(void)
{
	DdHdmac0Utility* self = k_object_new_with_private(DD_TYPE_HDMAC0_UTILITY, sizeof(DdHdmac0UtilityPrivate));

	return self;
}
