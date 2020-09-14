/*
 *
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-08
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/


#include <string.h>
#include "imjpeg.h"
#include "ddtop.h"
#include "ddimusercustom.h"
#include "jdsjp7.h"
#include "jdsimg.h"
#include "imjpegshare.h"


G_DEFINE_TYPE(ImJpegShare, im_jpeg_share, G_TYPE_OBJECT);
#define IM_JPEG_SHARE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_JPEG_SHARE, ImJpegSharePrivate));


struct _ImJpegSharePrivate
{
	gint a;
};


/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// quantization table for the next frame
static volatile guchar S_GIM_JPEG_UPDATE_QUANT_FLG = 0;

// counter
static volatile gushort S_GIM_JPEG_LINE_CNT = 0;
static volatile gulong S_GIM_JPEG_SECT_CNT = 0;

// encode setting table
static TimgEncMng S_GIM_JPEG_ENC_MNG;
static TimgEncFrameMng S_GIM_JPEG_ENC_FRAME_MNG;

// decode setting table
static TimgDecMng S_GIM_JPEG_DEC_MNG;
static TimgDecFrameMng S_GIM_JPEG_DEC_FRAME_MNG;
static gint32 S_GIM_JPEG_RESULT_JUDGE = 0;
/**
 *DECLS
 */
static void 		dispose_od(GObject *object);
static void 		finalize_od(GObject *object);
/**
 *IMPL
 */
static void 		im_jpeg_share_class_init(ImJpegShareClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_aim_private(klass, sizeof(ImJpegSharePrivate));
}

static void 		im_jpeg_share_init(ImJpegShare *self)
{
	ImJpegSharePrivate *priv = IM_JPEG_SHARE_GET_PRIVATE(self);
	self->ddimUserCustom = ddim_user_custom_new();
}

static void 		dispose_od(GObject *object)
{
	ImJpegSharePrivate *priv = IM_JPEG_SHARE_GET_PRIVATE(object);
	ImJpegCommon *self = im_jpeg_common_new();
	if(self->ddimUserCustom){
		g_object_unref(self->ddimUserCustom);
		self->ddimUserCustom = NULL;
	}
	G_OBJECT_CLASS(im_jpeg_share_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	ImJpegSharePrivate *priv = IM_JPEG_SHARE_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_jpeg_share_parent_class) -> dispose(object);
}
/**
 * PUBLIC
 */
/**
 * @brief		Frame configuration of the JPEG encoding process
 * @param[in]	TimgEncFrameMng*	pJpgEncFrmMng	: Pointer to JPEG Encode frame management table
 * @param[out]	None
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_PARAM_ERROR
 */
gint32 im_jpeg_ctrl_enc_frame(ImJpegShare*self, TimgEncFrameMng* pJpgEncFrmMng )
{
#ifdef CO_PARAM_CHECK
	if (pJpgEncFrmMng == NULL) {
		Ddim_Assertion(("im_jpeg_ctrl_enc_frame(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	// Set Jpeg frame management table to a global table
	S_GIM_JPEG_ENC_FRAME_MNG = *pJpgEncFrmMng;

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);
	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// JIMGYGH
	ioJpg7.jimgygh.bit.jimgygh = pJpgEncFrmMng->globalYWidth;
	// JIMGCGH
	ioJpg7.jimgcgh.bit.jimgcgh = pJpgEncFrmMng->globalCWidth;
	// JIMGSH
	ioJpg7.jimgsh.bit.jimgsh = S_GIM_JPEG_ENC_MNG.width;
	// JIMGSV
	ioJpg7.jimgsv.bit.jimgsv = S_GIM_JPEG_ENC_MNG.lines;
	// JIMGAY
	ioJpg7.jimgay.bit.jimgay = pJpgEncFrmMng->yccAddr.y;
	// JIMGACB
	ioJpg7.jimgacb.bit.jimgacb = pJpgEncFrmMng->yccAddr.c;
	// JCC (pass-1 mode)
	ioJpg7.jcctl.bit.jcc = pJpgEncFrmMng->codeCountFlg;
	// JCPS
	ioJpg7.jcctl.bit.jcps = pJpgEncFrmMng->codeOverCountFlg;
	// JCODA
	ioJpg7.jcoda.bit.jcoda = pJpgEncFrmMng->codeAddr;
	// JCODSV
	if (pJpgEncFrmMng->limitSize == 0 || pJpgEncFrmMng->codeCountFlg) {
		ioJpg7.jcodsv.word = 0;
	}
	else if (pJpgEncFrmMng->limitSize < ImJpegCommon_D_IM_JPEG_SECT_CNT) {
		ioJpg7.jcodsv.word = 1;
		Ddim_Print(("I:im_jpeg_ctrl_enc_frame() Warning : Limit size changed to 512 bytes.\n"));
	}
	else {
		ioJpg7.jcodsv.word = (gulong) (pJpgEncFrmMng->limitSize / ImJpegCommon_D_IM_JPEG_SECT_CNT);
	}

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);

	return ImJpegCommon_D_IM_JPEG_OK;
}

/**
 * @brief		get the base settings for Jpeg encode.
 * @param[in]	None
 * @param[out]	TimgEncMng* pJpgEncMng
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_PARAM_ERROR
 */
gint32	im_jpeg_get_ctrl_enc(ImJpegShare*self, TimgEncMng* pJpgEncMng )
{
#ifdef CO_PARAM_CHECK
	if (pJpgEncMng == NULL) {
		Ddim_Assertion(("im_jpeg_get_ctrl_enc(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);

	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// sampling type
	pJpgEncMng->yccSmpl = (EimgSmplType) ioJpg7.jpmode.bit.mmode;

	// JPQTABLE
	pJpgEncMng->component[0].quantTblNo = (ioJpg7.jpqtable.bit.qt0u << 1) | ioJpg7.jpqtable.bit.qt0l;
	pJpgEncMng->component[1].quantTblNo = (ioJpg7.jpqtable.bit.qt1u << 1) | ioJpg7.jpqtable.bit.qt1l;
	pJpgEncMng->component[2].quantTblNo = (ioJpg7.jpqtable.bit.qt2u << 1) | ioJpg7.jpqtable.bit.qt2l;
	// JPHTABLE
	pJpgEncMng->component[0].hufDcTblNo = ioJpg7.jphtable.bit.ht0dc;
	pJpgEncMng->component[0].hufAcTblNo = ioJpg7.jphtable.bit.ht0ac;
	pJpgEncMng->component[1].hufDcTblNo = ioJpg7.jphtable.bit.ht1dc;
	pJpgEncMng->component[1].hufAcTblNo = ioJpg7.jphtable.bit.ht1ac;
	pJpgEncMng->component[2].hufDcTblNo = ioJpg7.jphtable.bit.ht2dc;
	pJpgEncMng->component[2].hufAcTblNo = ioJpg7.jphtable.bit.ht2ac;
	// JPDRISET
	pJpgEncMng->driMkNum = ioJpg7.jpdriset.bit.jpdriset;
	// JPWIDTH
	pJpgEncMng->width = ioJpg7.jpwidth.bit.jpwidth;
	// JPHEIGHT
	pJpgEncMng->lines = ioJpg7.jpheight.bit.jpheight;
	// JPFORMAT
	pJpgEncMng->skipMkFlg = ioJpg7.jpformat.bit.mkskip;
	pJpgEncMng->exifFmtFlg = ioJpg7.jpformat.bit.exifmod;
	// JMODE
	pJpgEncMng->pbufCtrl.endian = (EimgEndian) ioJpg7.jmode.bit.jpbendian;
	pJpgEncMng->jbufCtrl.endian = (EimgEndian) ioJpg7.jmode.bit.jjbendian;
	pJpgEncMng->burstAlignment = (EimgBurstAl) ioJpg7.jmode.bit.jburstAlOn;
	// JPBSTA
	switch ((guchar) ioJpg7.jpbsta.bit.jpissueset) {
		case 0x01:
			pJpgEncMng->pbufCtrl.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_2;
			break;
		case 0x02:
			pJpgEncMng->pbufCtrl.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_4;
			break;
		default:
			pJpgEncMng->pbufCtrl.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
			break;
	}
	pJpgEncMng->pbufCtrl.cacheType = ioJpg7.jpbsta.bit.jpacache;
	pJpgEncMng->pbufCtrl.protType = ioJpg7.jpbsta.bit.jpaprot;
	// JJBSTA
	switch ((guchar) ioJpg7.jjbsta.bit.jjissueset) {
		case 0x01:
			pJpgEncMng->jbufCtrl.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_2;
			break;
		case 0x02:
			pJpgEncMng->jbufCtrl.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_4;
			break;
		default:
			pJpgEncMng->jbufCtrl.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
			break;
	}
	pJpgEncMng->jbufCtrl.cacheType = ioJpg7.jjbsta.bit.jjacache;
	pJpgEncMng->jbufCtrl.protType = ioJpg7.jjbsta.bit.japrot;

	// jcctl
	if ((guchar) ioJpg7.jcctl.bit.jcrp == 0x2) {
		pJpgEncMng->jburstLength = ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
	}
	else {
		pJpgEncMng->jburstLength = ImJpegCommon_E_IM_JPEG_BURST_INCR_16;
	}
	// JICTL
	if ((guchar) ioJpg7.jictl.bit.jirp == 0x2) {
		pJpgEncMng->pburstLength = ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
	}
	else {
		pJpgEncMng->pburstLength = ImJpegCommon_E_IM_JPEG_BURST_INCR_16;
	}
	pJpgEncMng->bitDepth = ioJpg7.jictl.bit.b12m;

	// Periodic interrupt setting
	// line unit
	pJpgEncMng->pintLine = ioJpg7.jlineval.bit.jlineval;

	// sector unit
	pJpgEncMng->pintSect = ioJpg7.jsectval.bit.jsectval;

	// iipset
	pJpgEncMng->portMode = (EimgIipPortMode) ioJpg7.iipset.bit.portMode;
	pJpgEncMng->ringOn = ioJpg7.iipset.bit.ringOn;
	pJpgEncMng->blockSize = (EimgIipBlock) ioJpg7.iipset.bit.blkSize;
	pJpgEncMng->ringSize = ioJpg7.iipset.bit.ringSize;

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);

	return ImJpegCommon_D_IM_JPEG_OK;
}


/**
 * @brief		Get the frame settings for Jpeg encode.
 * @param[in]	None
 * @param[out]	TimgEncFrameMng* pJpgEncFrmMng
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_PARAM_ERROR
 */
gint32	im_jpeg_get_ctrl_enc_frame(ImJpegShare*self, TimgEncFrameMng* pJpgEncFrmMng )
{
#ifdef CO_PARAM_CHECK
	if (pJpgEncFrmMng == NULL) {
		Ddim_Assertion(("im_jpeg_get_ctrl_enc_frame(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);

	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// JIMGYGH
	pJpgEncFrmMng->globalYWidth = ioJpg7.jimgygh.bit.jimgygh;
	// JIMGCGH
	pJpgEncFrmMng->globalCWidth = ioJpg7.jimgcgh.bit.jimgcgh;

	// JIMGAY
	pJpgEncFrmMng->yccAddr.y = ioJpg7.jimgay.bit.jimgay;
	// JIMGACB
	pJpgEncFrmMng->yccAddr.c = ioJpg7.jimgacb.bit.jimgacb;
	// JCC (pass-1 mode)
	pJpgEncFrmMng->codeCountFlg = ioJpg7.jcctl.bit.jcc;
	// JCPS
	pJpgEncFrmMng->codeOverCountFlg = ioJpg7.jcctl.bit.jcps;
	// JCODA
	pJpgEncFrmMng->codeAddr = ioJpg7.jcoda.bit.jcoda;

	// JCODSV
	pJpgEncFrmMng->limitSize = ((ioJpg7.jcodsv.word) * (kulonglong) ImJpegCommon_D_IM_JPEG_SECT_CNT);

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);

	return ImJpegCommon_D_IM_JPEG_OK;
}


/**
 * @brief		JPEG Encoding process asynchronous.
 * @param[in]	None
 * @param[out]	None
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_RUNNING_NG / ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR
 */
gint32 im_jpeg_start_enc( ImJpegShare*self )
{
	DdimUserCustom_ER ercd;

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);
	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// F_JPEG7 macro In-use check
	if (ioJpg7.jpstatus.bit.jpstatus != 0) {

		// HCLK off
		im_jpeg_off_hclk(NULL);
		ImJpegCommon_IM_JPEG_DSB();
		ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);

		// macro running
		return ImJpegCommon_D_IM_JPEG_RUNNING_NG;
	}

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);

	// Initialize
	// Size of JPEG Compressed data
	S_GIM_JPEG_ENC_MNG.codeSize = 0;
	// Processing result
	S_GIM_JPEG_ENC_MNG.result = 0;
	S_GIM_JPEG_RESULT_JUDGE = 0;
	S_GIM_JPEG_LINE_CNT = 0;
	S_GIM_JPEG_SECT_CNT = 0;

	ercd = DDIM_User_Clr_Flg( FID_IM_JPEG, ~ImJpegCommon_D_IM_JPEG_FLG_WAIT_END);
	if ( DdimUserCustom_E_OK != ercd) {
		return ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR;
	}

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);

	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// interrupt setting
	ioJpg7.jinten.word |= 0xC4D000;

	if (S_GIM_JPEG_UPDATE_QUANT_FLG) {
		// Set quant table for the next frame -> enable
		ioJpg7.jpintset.bit.qtwset = 1;
	}
	else {
		ioJpg7.jpintset.bit.qtwset = 0;
	}

	// CORE start
	ioJpg7.jpcmd.bit.jstart = 1;
	// PBUF start
	ioJpg7.jictl.bit.jitrg = 1;
	// JBUF start
	ioJpg7.jcctl.bit.jctrg = 1;
	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);

	return ImJpegCommon_D_IM_JPEG_OK;
}

/**
 * @brief		Waiting to be processed JPEG encoding.
 * @param[out]	TimgEncMng*			pJpgEncMng		:Result of the JPEG encoding process
 * @param[in]	gint32						timeOut			:Time-out period
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_PARAM_ERROR /
 * ImJpegCommon_D_IM_JPEG_TIMEOUT / ImJpegCommon_D_IM_JPEG_ENCODE_ERR / ImJpegCommon_D_IM_JPEG_AXI_ERR
 */
gint32 im_jpeg_wait_end_enc(ImJpegShare*self, TimgEncMng* pJpgEncMng, gint32 timeOut )
{
	DdimUserCustom_FLGPTN flgptn = 0;
	DdimUserCustom_ER ercd;
	gint32 ret;

#ifdef CO_PARAM_CHECK
	if (pJpgEncMng == NULL) {
		Ddim_Assertion(("im_jpeg_wait_end_enc(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
	if (timeOut < D_DDIM_WAIT_END_FOREVER) {
		Ddim_Assertion(("im_jpeg_wait_end_enc(): input param error. timeOut = %x\n", timeOut));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	ercd = ddim_user_custom_twai_flg(self->ddimUserCustom, FID_IM_JPEG, ImJpegCommon_D_IM_JPEG_FLG_WAIT_END, DdimUserCustom_TWF_ORW, &flgptn, timeOut);

	// Set Result
	pJpgEncMng->codeSize = S_GIM_JPEG_ENC_MNG.codeSize;
	pJpgEncMng->result = S_GIM_JPEG_ENC_MNG.result;

	if (ercd != DdimUserCustom_E_OK) {
		ret = ImJpegCommon_D_IM_JPEG_TIMEOUT;
	}
	else {
		// judge the process result
		if (((pJpgEncMng->result & ImJpegCommon_D_IM_JPEG_JJBINT) == ImJpegCommon_D_IM_JPEG_JJBINT)
			|| ((pJpgEncMng->result & ImJpegCommon_D_IM_JPEG_JPBINT) == ImJpegCommon_D_IM_JPEG_JPBINT)) {
			// bus error
			ret = ImJpegCommon_D_IM_JPEG_AXI_ERR;
		}
		else if ((pJpgEncMng->result & (ImJpegCommon_D_IM_JPEG_JCLRFMER | ImJpegCommon_D_IM_JPEG_ERR)) != 0) {
			ret = ImJpegCommon_D_IM_JPEG_ENCODE_ERR;
		}
		else if ((pJpgEncMng->result & ImJpegCommon_D_IM_JPEG_PAUSE) == ImJpegCommon_D_IM_JPEG_PAUSE) {
			// pausing end or code size over
			ret = ImJpegCommon_D_IM_JPEG_ENCODE_PAUSE;
		}
		else {
			// encode process finished
			ret = ImJpegCommon_D_IM_JPEG_OK;
		}
	}

	return ret;
}

/**
 * @brief		JPEG encode restart.(Restart from the state is paused encoding)
 * @param[in]	TimgEncFrameMng*	pJpgEncFrmMng	: Pointer to JPEG Encode frame management table
 * @param[out]	None
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_RUNNING_NG /
 *  ImJpegCommon_D_IM_JPEG_PARAM_ERROR / ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR
 */
gint32 im_jpeg_restart_enc(ImJpegShare*self, TimgEncFrameMng* pJpgEncFrmMng )
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if (pJpgEncFrmMng == NULL) {
		Ddim_Assertion(("im_jpeg_restart_enc(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);

	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	if (ioJpg7.jictl.bit.jitrg != 2) {
		// HCLK off
		im_jpeg_off_hclk(NULL);
		ImJpegCommon_IM_JPEG_DSB();
		ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);
		// Coding not stopped
		return ImJpegCommon_D_IM_JPEG_RUNNING_NG;
	}

	// Initialize result
	// Processing result
	S_GIM_JPEG_ENC_MNG.result = 0;
	S_GIM_JPEG_RESULT_JUDGE = 0;

	// Set destination addr
	ioJpg7.jcoda.bit.jcoda = pJpgEncFrmMng->codeAddr;

	if (pJpgEncFrmMng->limitSize == 0) {
		ioJpg7.jinten.bit.jcpfen = 0;
		ioJpg7.jcodsv.word = 0;
	}
	else {
		ioJpg7.jinten.bit.jcpfen = 1;
		ioJpg7.jcodsv.word = (gulong) (pJpgEncFrmMng->limitSize / ImJpegCommon_D_IM_JPEG_SECT_CNT);
	}
	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);

	ercd = ddim_user_custom_clr_flg(self->ddimUserCustom, FID_IM_JPEG, ~ImJpegCommon_D_IM_JPEG_FLG_WAIT_END);
	if ( DdimUserCustom_E_OK != ercd) {
		return ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR;
	}

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);

	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// JBUF restart
	ioJpg7.jcctl.bit.jctrg = 1;

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);

	return ImJpegCommon_D_IM_JPEG_OK;
}

/**
 * @brief		Configuration of the JPEG decoding process for marker skip mode
 * @param[in]	None
 * @param[out]	None
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_RUNNING_NG
 */
gint32 im_jpeg_set_skip_marker_dec( ImJpegShare*self )
{
	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);

	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// F_JPEG7 macro In-use check
	if (ioJpg7.jpstatus.bit.jpstatus != 0) {
		// HCLK off
		im_jpeg_off_hclk(NULL);
		ImJpegCommon_IM_JPEG_DSB();
		ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);
		// macro running
		return ImJpegCommon_D_IM_JPEG_RUNNING_NG;
	}
	// Marker Skip Mode ON
	ioJpg7.jpformat.bit.mkskip = 1;
	// JPINTSET
	ioJpg7.jpintset.word = 0;

	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);

	return ImJpegCommon_D_IM_JPEG_OK;
}

/**
 * @brief		Base configuration of the JPEG decoding process
 * @param[in]	TimgDecMng*	pJpgDecMng	:Pointer to JPEG decode base management table
 * @param[out]	None
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_RUNNING_NG / ImJpegCommon_D_IM_JPEG_PARAM_ERROR
 */
gint32 im_jpeg_ctrl_dec(ImJpegShare*self, TimgDecMng* pJpgDecMng )
{
#ifdef CO_PARAM_CHECK
	if (pJpgDecMng == NULL) {
		Ddim_Assertion(("im_jpeg_ctrl_dec(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// F_JPEG7 macro In-use check
	if (ioJpg7.jpstatus.bit.jpstatus != 0) {
		im_jpeg_off_hclk(NULL);
		ImJpegCommon_IM_JPEG_DSB();
		ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);
		// macro running
		return ImJpegCommon_D_IM_JPEG_RUNNING_NG;
	}

	// soft reset
	im_jpeg_reset(NULL);
	// Set Jpeg base management table to a global table
	S_GIM_JPEG_DEC_MNG = *pJpgDecMng;

	// JPMODE
	// MMODE:000/S_ENDIAN:1/P_ENDIAN:1/DISPOSAL:1
	ioJpg7.jpmode.word = 0x38;
	// JPFORMAT
	ioJpg7.jpformat.bit.exifmod = 0;
	ioJpg7.jpformat.bit.mkskip = pJpgDecMng->skipMkFlg;
	// JMODE
	ioJpg7.jmode.bit.jmemform = pJpgDecMng->memFormat;
	ioJpg7.jmode.bit.jpbdext = pJpgDecMng->extMode;
	ioJpg7.jmode.bit.jpbendian = pJpgDecMng->pbufCtrl.endian;
	ioJpg7.jmode.bit.jjbendian = pJpgDecMng->jbufCtrl.endian;
	ioJpg7.jmode.bit.jburstAlOn = pJpgDecMng->burstAlignment;
	// JPBSTA
	switch (pJpgDecMng->pbufCtrl.issueTranNum) {
		case ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_2:
			ioJpg7.jpbsta.bit.jpissueset = 0x1;
			break;
		case ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_4:
			ioJpg7.jpbsta.bit.jpissueset = 0x2;
			break;
		default:
			ioJpg7.jpbsta.bit.jpissueset = 0x3;
			break;
	}
	ioJpg7.jpbsta.bit.jpacache = pJpgDecMng->pbufCtrl.cacheType;
	ioJpg7.jpbsta.bit.jpaprot = pJpgDecMng->pbufCtrl.protType;
	// JJBSTA
	switch (pJpgDecMng->jbufCtrl.issueTranNum) {
		case ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_2:
			ioJpg7.jjbsta.bit.jjissueset = 0x1;
			break;
		case ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_4:
			ioJpg7.jjbsta.bit.jjissueset = 0x2;
			break;
		default:
			ioJpg7.jjbsta.bit.jjissueset = 0x3;
			break;
	}
	ioJpg7.jjbsta.bit.jjacache = pJpgDecMng->jbufCtrl.cacheType;
	ioJpg7.jjbsta.bit.japrot = pJpgDecMng->jbufCtrl.protType;
	// Periodic interrupt setting
	// line unit
	if (pJpgDecMng->pintLine != 0) {
		ioJpg7.jinten.bit.jlineen = 1;
		ioJpg7.jlineval.bit.jlineval = pJpgDecMng->pintLine;
	}
	else {
		ioJpg7.jinten.bit.jlineen = 0;
		ioJpg7.jlineval.bit.jlineval = 0;
	}
	// sector unit
	if (pJpgDecMng->pintSect != 0) {
		ioJpg7.jinten.bit.jsecten = 1;
		ioJpg7.jsectval.bit.jsectval = pJpgDecMng->pintSect;
	}
	else {
		ioJpg7.jinten.bit.jsecten = 0;
		ioJpg7.jsectval.bit.jsectval = 0;
	}
	// JBANDCOLOR
	ioJpg7.jbandcolor.bit.jbandy = pJpgDecMng->colorBand.yBand;
	ioJpg7.jbandcolor.bit.jbandcb = pJpgDecMng->colorBand.cbBand;
	ioJpg7.jbandcolor.bit.jbandcr = pJpgDecMng->colorBand.crBand;
	// jcctl
	if (pJpgDecMng->jburstLength == ImJpegCommon_E_IM_JPEG_BURST_INCR_8) {
		ioJpg7.jcctl.bit.jcrp = 0x2;
	}
	else {
		ioJpg7.jcctl.bit.jcrp = 0x3;
	}
	// JICTL
	if (pJpgDecMng->pburstLength == ImJpegCommon_E_IM_JPEG_BURST_INCR_8) {
		ioJpg7.jictl.bit.jirp = 0x2;
	}
	else {
		ioJpg7.jictl.bit.jirp = 0x3;
	}
	ioJpg7.jictl.bit.b12m = ImJpegCommon_E_IM_JPEG_BIT_DEPTH_8BIT;
	// JPINTSET
	if (pJpgDecMng->corrMode) {
		ioJpg7.jpintset.word = 0x40F;
	}
	else {
		ioJpg7.jpintset.word = 0x30F;
	}

	// iipset
	ioJpg7.iipset.bit.portMode = pJpgDecMng->portMode;
	ioJpg7.iipset.bit.ringOn = pJpgDecMng->ringOn;
	ioJpg7.iipset.bit.blkSize = pJpgDecMng->blockSize;
	ioJpg7.iipset.bit.ringSize = pJpgDecMng->ringSize;

	// SRAM power down control.
	ioImg.srampd.bit.jpegpd = 0x1;

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);
	// SRAM power down control wait time.
	DD_ARM_WAIT_NS(1000);

	return ImJpegCommon_D_IM_JPEG_OK;
}

/**
 * @brief		Frame configuration of the JPEG decoding process
 * @param[in]	TimgDecFrameMng*	pJpgDecFrmMng	:Pointer to JPEG Decode frame management table
 * @param[out]	None
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_PARAM_ERROR
 */
gint32 im_jpeg_ctrl_dec_frame(ImJpegShare*self,  TimgDecFrameMng* pJpgDecFrmMng )
{
#ifdef CO_PARAM_CHECK
	if (pJpgDecFrmMng == NULL) {
		Ddim_Assertion(("im_jpeg_ctrl_dec_frame(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	// Set Jpeg frame management table to a global table
	S_GIM_JPEG_DEC_FRAME_MNG = *pJpgDecFrmMng;

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// jictl
	ioJpg7.jictl.bit.jixp = 0;
	// jcctl
	ioJpg7.jcctl.bit.jcc = 0;
	ioJpg7.jcctl.bit.jcps = 0;
	// jimgay
	ioJpg7.jimgay.bit.jimgay = pJpgDecFrmMng->yccAddr.y;
	// jimgacb
	ioJpg7.jimgacb.bit.jimgacb = pJpgDecFrmMng->yccAddr.c;
	// jcoda
	ioJpg7.jcoda.bit.jcoda = pJpgDecFrmMng->codeAddr;
	// jcodsv
	if (pJpgDecFrmMng->codeSize == 0) {
		ioJpg7.jcodsv.word = 0;
	}
	else {
		ioJpg7.jcodsv.word = (gulong) (pJpgDecFrmMng->codeSize / ImJpegCommon_D_IM_JPEG_SECT_CNT) + 1;
	}

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);

	return ImJpegCommon_D_IM_JPEG_OK;
}

/**
 * @brief		Get the base settings for Jpeg decode.
 * @param[in]	None
 * @param[out]	TimgDecMng*	pJpgDecMng	:Pointer to JPEG Decode base management table
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_PARAM_ERROR
 */
gint32	im_jpeg_get_ctrl_dec(ImJpegShare*self, TimgDecMng* pJpgDecMng )
{
#ifdef CO_PARAM_CHECK
	if (pJpgDecMng == NULL) {
		Ddim_Assertion(("im_jpeg_get_ctrl_dec(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);
	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// JPFORMAT
	pJpgDecMng->skipMkFlg = ioJpg7.jpformat.bit.mkskip;
	// JMODE
	pJpgDecMng->extMode = (EimgResizeExt) ioJpg7.jmode.bit.jpbdext;
	pJpgDecMng->pbufCtrl.endian = (EimgEndian) ioJpg7.jmode.bit.jpbendian;
	pJpgDecMng->jbufCtrl.endian = (EimgEndian) ioJpg7.jmode.bit.jjbendian;
	pJpgDecMng->burstAlignment = (EimgBurstAl) ioJpg7.jmode.bit.jburstAlOn;
	// JPBSTA
	switch ((guchar) ioJpg7.jpbsta.bit.jpissueset) {
		case 0x01:
			pJpgDecMng->pbufCtrl.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_2;
			break;
		case 0x02:
			pJpgDecMng->pbufCtrl.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_4;
			break;
		default:
			pJpgDecMng->pbufCtrl.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
			break;
	}
	pJpgDecMng->pbufCtrl.cacheType = ioJpg7.jpbsta.bit.jpacache;
	pJpgDecMng->pbufCtrl.protType = ioJpg7.jpbsta.bit.jpaprot;
	// JJBSTA
	switch ((guchar) ioJpg7.jjbsta.bit.jjissueset) {
		case 0x01:
			pJpgDecMng->jbufCtrl.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_2;
			break;
		case 0x02:
			pJpgDecMng->jbufCtrl.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_4;
			break;
		default:
			pJpgDecMng->jbufCtrl.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
			break;
	}
	pJpgDecMng->jbufCtrl.cacheType = ioJpg7.jjbsta.bit.jjacache;
	pJpgDecMng->jbufCtrl.protType = ioJpg7.jjbsta.bit.japrot;
	// Periodic interrupt setting
	// line unit
	pJpgDecMng->pintLine = ioJpg7.jlineval.bit.jlineval;

	// sector unit
	pJpgDecMng->pintSect = ioJpg7.jsectval.bit.jsectval;

	// JBANDCOLOR
	pJpgDecMng->colorBand.yBand = ioJpg7.jbandcolor.bit.jbandy;
	pJpgDecMng->colorBand.cbBand = ioJpg7.jbandcolor.bit.jbandcb;
	pJpgDecMng->colorBand.crBand = ioJpg7.jbandcolor.bit.jbandcr;

	// jcctl
	if (ioJpg7.jcctl.bit.jcrp == 0x2) {
		pJpgDecMng->jburstLength = ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
	}
	else {
		pJpgDecMng->jburstLength = ImJpegCommon_E_IM_JPEG_BURST_INCR_16;
	}
	// jictl
	if (ioJpg7.jictl.bit.jirp == 0x2) {
		pJpgDecMng->pburstLength = ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
	}
	else {
		pJpgDecMng->pburstLength = ImJpegCommon_E_IM_JPEG_BURST_INCR_16;
	}
	// JPINTSET
	pJpgDecMng->corrMode = ioJpg7.jpintset.bit.corset;

	// iipset
	pJpgDecMng->portMode = (EimgIipPortMode) ioJpg7.iipset.bit.portMode;
	pJpgDecMng->ringOn = ioJpg7.iipset.bit.ringOn;
	pJpgDecMng->blockSize = (EimgIipBlock) ioJpg7.iipset.bit.blkSize;
	pJpgDecMng->ringSize = ioJpg7.iipset.bit.ringSize;
	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);

	return ImJpegCommon_D_IM_JPEG_OK;
}

ImJpegShare* 		im_jpeg_share_new(void)
{
	ImJpegShare *self = g_object_new(IM_TYPE_JPEG_SHARE, NULL);
	return self;
}
