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
#include "imjpegcommon.h"


G_DEFINE_TYPE(ImJpegCommon, im_jpeg_common, G_TYPE_OBJECT);
#define IM_JPEG_COMMON_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_JPEG_COMMON, ImJpegCommonPrivate));


struct _ImJpegCommonPrivate
{
	gint a;
};


/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// quantization table for the next frame
static TimgQuatTblPack S_GIM_JPEG_NEXT_FRAME_QUANT_TBL;
static volatile guchar S_GIM_JPEG_UPDATE_QUANT_FLG = 0;

static TimgQuatTbl S_GIM_JPEG_QUANT_TBL_0;
static TimgQuatTbl S_GIM_JPEG_QUANT_TBL_1;
static TimgQuatTbl S_GIM_JPEG_QUANT_TBL_2;
static TimgQuatTbl S_GIM_JPEG_QUANT_TBL_3;

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

/********************************************************/
/* Default Quantization Table							*/
/********************************************************/
// for Y
static const TimgQuatTbl S_GDEFAULT_QUANTIZE_TBL_LUMA = {
	{	0x10, 0x0B, 0x0A, 0x10, 0x18, 0x28, 0x33, 0x3D,
		0x0C, 0x0C, 0x0E, 0x13, 0x1A, 0x3A, 0x3C, 0x37,
		0x0E, 0x0D, 0x10, 0x18, 0x28, 0x39, 0x45, 0x38,
		0x0E, 0x11, 0x16, 0x1D, 0x33, 0x57, 0x50, 0x3E,
		0x12, 0x16, 0x25, 0x38, 0x44, 0x6D, 0x67, 0x4D,
		0x18, 0x23, 0x37, 0x40, 0x51, 0x68, 0x71, 0x5C,
		0x31, 0x40, 0x4E, 0x57, 0x67, 0x79, 0x78, 0x65,
		0x48, 0x5C, 0x5F, 0x62, 0x70, 0x64, 0x67, 0x63	}
};

// for Cb/Cr
static const TimgQuatTbl S_GDEFAULT_QUANTIZE_TBL_CHROMA = {
	{	0x11, 0x12, 0x18, 0x2F, 0x63, 0x63, 0x63, 0x63,
		0x12, 0x15, 0x1A, 0x42, 0x63, 0x63, 0x63, 0x63,
		0x18, 0x1A, 0x38, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x2F, 0x42, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63	}
};
/**
 *DECLS
 */
static void 		dispose_od(GObject *object);
static void 		finalize_od(GObject *object);
/**
 *IMPL
 */
static void 		im_jpeg_common_class_init(ImJpegCommonClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_aim_private(klass, sizeof(ImJpegCommonPrivate));
}

static void 		im_jpeg_common_init(ImJpegCommon *self)
{
	ImJpegCommonPrivate *priv = IM_JPEG_COMMON_GET_PRIVATE(self);
	self->ddimUserCustom = ddim_user_custom_new();
}

static void 		dispose_od(GObject *object)
{
	ImJpegCommonPrivate *priv = IM_JPEG_COMMON_GET_PRIVATE(object);
	ImJpegCommon *self = im_jpeg_common_new();
	if(self->ddimUserCustom){
		g_object_unref(self->ddimUserCustom);
		self->ddimUserCustom = NULL;
	}
	G_OBJECT_CLASS(im_jpeg_common_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	ImJpegCommonPrivate *priv = IM_JPEG_COMMON_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_jpeg_common_parent_class) -> dispose(object);
}

/**
 * PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
/**
 * @brief		Initialization of the JPEG macro.
 * @param[in]	None
 * @param[out]	None
 * @return		None
 */
void im_jpeg_init( ImJpegCommon*self )
{
	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);
	im_jpeg_on_clk(NULL);
	im_jpeg_on_iclk(NULL);
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	im_jpeg_reset(NULL);
	im_jpeg_off_hclk(NULL);
	im_jpeg_off_iclk(NULL);
	im_jpeg_off_clk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);
}

/**
 * @brief		The semaphore of JPEG is acquired
 * @param[in]	gint32	tmout	:Timeout time ( -1:Forever, 0:Polling, Other(ms))
 * @param[out]	None
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_SEM_TIMEOUT /
 * ImJpegCommon_D_IM_JPEG_SEM_NG / ImJpegCommon_D_IM_JPEG_PARAM_ERROR
 */
gint32 im_jpeg_open(ImJpegCommon*self, gint32 tmout )
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if (tmout < DdimUserCustom_SEM_WAIT_FEVR) {
		Ddim_Assertion(("I:im_jpeg_open: input param error. tmout = %x\n", tmout));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif

	if ( DdimUserCustom_SEM_WAIT_POL == tmout) {
		// pol_sem()
		ercd = ddim_user_custom_pol_sem(self->ddimUserCustom,  SID_IM_JPEG);
	}
	else {
		// twai_sem()
		ercd = ddim_user_custom_twai_sem(self->ddimUserCustom,  SID_IM_JPEG, (DdimUserCustom_TMO) tmout);
	}

	if ( DdimUserCustom_E_OK != ercd) {
		if ( DdimUserCustom_E_TMOUT == ercd) {
			Ddim_Print(("I:im_jpeg_open() Error : Semaphore Get Time Out. ercd = %d\n", ercd));
			return ImJpegCommon_D_IM_JPEG_SEM_TIMEOUT;
		}

		Ddim_Print(("I:im_jpeg_open() Error : Semaphore Get Error. ercd = %d\n", ercd));
		return ImJpegCommon_D_IM_JPEG_SEM_NG;
	}

	// CLK on
	im_jpeg_on_clk(NULL);
	// ICLK on
	im_jpeg_on_iclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// Initialize
	memset(&S_GIM_JPEG_ENC_MNG, 0, sizeof(TimgEncMng));
	memset(&S_GIM_JPEG_ENC_FRAME_MNG, 0, sizeof(TimgEncFrameMng));
	memset(&S_GIM_JPEG_DEC_MNG, 0, sizeof(TimgDecMng));
	memset(&S_GIM_JPEG_DEC_FRAME_MNG, 0, sizeof(TimgDecFrameMng));
	memset(&S_GIM_JPEG_NEXT_FRAME_QUANT_TBL, 0, sizeof(TimgQuatTblPack));

	return ImJpegCommon_D_IM_JPEG_OK;
}

/**
 * @brief		The semaphore of JPEG is returned
 * @param[in]	None
 * @param[out]	None
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_SEM_NG
 */
gint32 im_jpeg_close( ImJpegCommon*self )
{
	DdimUserCustom_ER ercd;

	// ICLK off
	im_jpeg_off_iclk(NULL);
	// CLK off
	im_jpeg_off_clk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	S_GIM_JPEG_UPDATE_QUANT_FLG = 0;

	ercd = ddim_user_custom_sig_sem(self->ddimUserCustom,  SID_IM_JPEG);
	if (ercd != DdimUserCustom_E_OK) {
		Ddim_Print(("I:im_jpeg_close() Error : ercd = %d\n", ercd));
		return ImJpegCommon_D_IM_JPEG_SEM_NG;
	}

	return ImJpegCommon_D_IM_JPEG_OK;
}

/**
 * @brief		Set quantization table
 * @param[in]	TimgQuatTblPack*	pQuantTbl		: Pointer to quantization table
 * @param[in]	guchar						nextFrmFlg	: Flag to determine whether a quantization table for the next frame
 * @param[out]	None
 * @return 		None
 * @note		"pQuantTbl" is NULL, use the default table.
 */
void im_jpeg_set_qtbl(ImJpegCommon*self, TimgQuatTblPack* pQuantTbl, guchar nextFrmFlg )
{
	// Set flag for next frame
	S_GIM_JPEG_UPDATE_QUANT_FLG = nextFrmFlg;

	if (nextFrmFlg) {
		// For next frame
		im_jpeg_set_next_quant_tbl(NULL, pQuantTbl);
	}
	else {
		// Set quantization table
		ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);
		im_jpeg_set_quant_tbl(NULL, pQuantTbl);
		ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);
	}

	return;
}

/**
 * @brief		Set the quantization table value by considering the quality value.
 * @param[in]	gint32	quaValue		: Quality value ( format: S7.10 )
 * @param[in]	guchar	nextFrmFlg	: Flag to determine whether a quantization table for the next frame
 * @param[out]	None
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_PARAM_ERROR
 */
gint32 im_jpeg_set_quality(ImJpegCommon*self, gint32 quaValue, guchar nextFrmFlg )
{
	gint32 i, index;
	guchar lumaArray[64];
	guchar chroArray[64];
	gint32 lumaBuf;
	gint32 chroBuf;

	// parameter check
#ifdef CO_PARAM_CHECK
	// check for S7.10 format (18bits length)
	if ((guint32) quaValue >= (1 << 17)) {
		Ddim_Assertion(("im_jpeg_set_quality(): Quality value error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (quaValue == 0) {
		// DC component
		lumaArray[0] = S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[0];
		chroArray[0] = S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[0];
		// AC component = 1
		for (i = 1; i < 64; i++) {
			lumaArray[i] = 1;
			chroArray[i] = 1;
		}
	}
	else {
		// DC/AC component
		for (i = 0; i < 64; i++) {
			lumaBuf = (((((gint32) (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[i])) << 11) / quaValue) + 1) >> 1;
			chroBuf = (((((gint32) (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[i])) << 11) / quaValue) + 1) >> 1;
			lumaArray[i] = (guchar) ImJpegCommon_IM_JPEG_LIMIT(lumaBuf, 1, 255);
			chroArray[i] = (guchar) ImJpegCommon_IM_JPEG_LIMIT(chroBuf, 1, 255);
		}
	}

	// Set flag for next frame
	S_GIM_JPEG_UPDATE_QUANT_FLG = nextFrmFlg;

	if (nextFrmFlg) {
		// Set Next Quantization table
		// Quantization table No.0 for Y
		for (i = 0; i < 64; i++) {
			S_GIM_JPEG_QUANT_TBL_0.quantValue[i] = lumaArray[i];
		}
		// Quantization table No.1 for Cb/Cr
		for (i = 0; i < 64; i++) {
			S_GIM_JPEG_QUANT_TBL_1.quantValue[i] = chroArray[i];
		}
		// Quantization table No.2 for Y
		for (i = 0; i < 64; i++) {
			S_GIM_JPEG_QUANT_TBL_2.quantValue[i] = lumaArray[i];
		}
		// Quantization table No.3 for Cb/Cr
		for (i = 0; i < 64; i++) {
			S_GIM_JPEG_QUANT_TBL_3.quantValue[i] = chroArray[i];
		}
		// Set table pack
		S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl0 = &S_GIM_JPEG_QUANT_TBL_0;
		S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl1 = &S_GIM_JPEG_QUANT_TBL_1;
		S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl2 = &S_GIM_JPEG_QUANT_TBL_2;
		S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl3 = &S_GIM_JPEG_QUANT_TBL_3;

#ifdef CO_IM_JPEG_DEBUG
		guchar i;
		for ( i=0; i < 64; i++ ) {
			Ddim_Print(("S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl0.quantValue[%d]=0x%X\n", i,
				S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl0->quantValue[i]));
		}
		for ( i=0; i < 64; i++ ) {
			Ddim_Print(("S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl1.quantValue[%d]=0x%X\n", i,
				S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl1->quantValue[i]));
		}
		for ( i=0; i < 64; i++ ) {
			Ddim_Print(("S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl2.quantValue[%d]=0x%X\n", i,
				S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl2->quantValue[i]));
		}
		for ( i=0; i < 64; i++ ) {
			Ddim_Print(("S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl3.quantValue[%d]=0x%X\n", i,
				S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl3->quantValue[i]));
		}
#endif

	}
	else {
		ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);

		// HCLK on
		im_jpeg_on_hclk(NULL);
		ImJpegCommon_IM_JPEG_DSB();

		// QTTBL SRAM power down off.
		ioImg.srampd.bit.jpegpd &= ~0x8;

		ImJpegCommon_IM_JPEG_DSB();

		// QTTBL SRAM power down control wait time.
		DD_ARM_WAIT_NS(1000);

		// Set Quantization table
		// Quantization table No.0 for Y
		for (i = 0, index = 0; i < 16; i++) {
			ioJpg7.jpqt0.word[i] = ((lumaArray[index] << 24) | (lumaArray[index + 1] << 16) | (lumaArray[index + 2] << 8) | (lumaArray[index + 3]));
			index = index + 4;
		}
		// Quantization table No.1 for Cb/Cr
		for (i = 0, index = 0; i < 16; i++) {
			ioJpg7.jpqt1.word[i] = ((chroArray[index] << 24) | (chroArray[index + 1] << 16) | (chroArray[index + 2] << 8) | (chroArray[index + 3]));
			index = index + 4;
		}
		// Quantization table No.2 for Y
		for (i = 0, index = 0; i < 16; i++) {
			ioJpg7.jpqt2.word[i] = ((lumaArray[index] << 24) | (lumaArray[index + 1] << 16) | (lumaArray[index + 2] << 8) | (lumaArray[index + 3]));
			index = index + 4;
		}
		// Quantization table No.3 for Cb/Cr
		for (i = 0, index = 0; i < 16; i++) {
			ioJpg7.jpqt3.word[i] = ((chroArray[index] << 24) | (chroArray[index + 1] << 16) | (chroArray[index + 2] << 8) | (chroArray[index + 3]));
			index = index + 4;
		}

#ifdef CO_IM_JPEG_DEBUG
		static gint32 zeroCnt=0;
		gulong value;
		for ( i = 0; i < 16; i++ ) {
			value = ioJpg7.jpqt0.word[i];
			if ( (value & 0xFF000000) == 0 ) {
				zeroCnt++;
			}
			if ( (value & 0x00FF0000) == 0 ) {
				zeroCnt++;
			}
			if ( (value & 0x0000FF00) == 0 ) {
				zeroCnt++;
			}
			if ( (value & 0x000000FF) == 0 ) {
				zeroCnt++;
			}
		}

		for ( i = 0; i < 16; i++ ) {
			value = ioJpg7.jpqt1.word[i];
			if ( (value & 0xFF000000) == 0 ) {
				zeroCnt++;
			}
			if ( (value & 0x00FF0000) == 0 ) {
				zeroCnt++;
			}
			if ( (value & 0x0000FF00) == 0 ) {
				zeroCnt++;
			}
			if ( (value & 0x000000FF) == 0 ) {
				zeroCnt++;
			}
		}

		for ( i = 0; i < 16; i++ ) {
			value = ioJpg7.jpqt2.word[i];
			if ( (value & 0xFF000000) == 0 ) {
				zeroCnt++;
			}
			if ( (value & 0x00FF0000) == 0 ) {
				zeroCnt++;
			}
			if ( (value & 0x0000FF00) == 0 ) {
				zeroCnt++;
			}
			if ( (value & 0x000000FF) == 0 ) {
				zeroCnt++;
			}
		}

		for ( i = 0; i < 16; i++ ) {
			value = ioJpg7.jpqt3.word[i];
			if ( (value & 0xFF000000) == 0 ) {
				zeroCnt++;
			}
			if ( (value & 0x00FF0000) == 0 ) {
				zeroCnt++;
			}
			if ( (value & 0x0000FF00) == 0 ) {
				zeroCnt++;
			}
			if ( (value & 0x000000FF) == 0 ) {
				zeroCnt++;
			}
		}
		if ( zeroCnt != 0 ) {
			while(1) {
				;
			}
		}
#endif
		// HCLK off
		im_jpeg_off_hclk(NULL);
		ImJpegCommon_IM_JPEG_DSB();

		ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);
	}

	return ImJpegCommon_D_IM_JPEG_OK;
}

/**
 * @brief		Setting the block downsampling (for Pass-1 mode)
 * @param[in]	guchar downspType : downsampling type  (0:1/1, 1:1/2, 2:1/4, 3:1/8)
 * @param[out]	None
 * @return		gushort	: Proportion of remainder after adjusting for size when decimated. (format: 8.8)
 */
gushort im_jpeg_set_down_sampling_rate(ImJpegCommon*self, guchar downspType )
{
	gushort dspHSize;
	gushort dspVSize;
	kdouble orgSize;
	kdouble mcrSize;
	gushort errRatio = 0;
	guint32 roundH;
	guint32 roundV;

#ifdef CO_PARAM_CHECK
	if (downspType > 3) {
		Ddim_Assertion(("I:Im_JPEG_Set_Enc_Decim. decim_type unknown ratio error\n"));
		return 0;
	}
#endif

	// Base alignment value
	switch (S_GIM_JPEG_ENC_MNG.yccSmpl) {
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420:
			roundH = 2;
			roundV = 2;
			break;
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422:
			roundH = 2;
			roundV = 1;
			break;
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC444:
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400:
			roundH = 1;
			roundV = 1;
			break;
		default:
			Ddim_Print(("im_jpeg_set_down_sampling_rate sampling type error!\n"));
			return 0;
	}

	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);
	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	// Set the down sampling rate
	ioJpg7.jictl.bit.jixp = downspType;

	// original size
	orgSize = ((kdouble) S_GIM_JPEG_ENC_MNG.width * S_GIM_JPEG_ENC_MNG.lines);

	// alignment value
	if (downspType != ImJpegCommon_D_IM_JPEG_DOWNSP_NONE) {
		if (downspType == ImJpegCommon_D_IM_JPEG_DOWNSP_1_2) {
			roundH *= 16;
		}
		else {
			roundH *= 8;
		}
		roundV *= 8;
	}

	// Horizon
	// adjust align
	dspHSize = (gushort) (roundH * (gushort) ((S_GIM_JPEG_ENC_MNG.width / (0x1 << downspType)) / roundH));
	S_GIM_JPEG_ENC_MNG.width = (dspHSize << downspType);
	ioJpg7.jimgsh.bit.jimgsh = S_GIM_JPEG_ENC_MNG.width;
	ioJpg7.jpwidth.bit.jpwidth = dspHSize;

	// Vertical
	// adjust align
	dspVSize = (gushort) (roundV * (gushort) (S_GIM_JPEG_ENC_MNG.lines / (0x1 << downspType) / roundV));
	S_GIM_JPEG_ENC_MNG.lines = (dspVSize << downspType);
	ioJpg7.jimgsv.bit.jimgsv = S_GIM_JPEG_ENC_MNG.lines;
	ioJpg7.jpheight.bit.jpheight = dspVSize;

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);

	// Ask the error ratio
	mcrSize = ((kdouble) S_GIM_JPEG_ENC_MNG.width * S_GIM_JPEG_ENC_MNG.lines);
	errRatio = (gushort) ((orgSize / mcrSize) * 256);

	return errRatio;
}

/**
 * @brief		Base configuration of the JPEG encoding process
 * @param[in]	TimgEncMng*	pJpgEncMng	: Pointer to JPEG Encode base management table
 * @param[out]	None
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_RUNNING_NG / ImJpegCommon_D_IM_JPEG_PARAM_ERROR
 */
gint32 im_jpeg_ctrl_enc(ImJpegCommon*self, TimgEncMng* pJpgEncMng )
{
#ifdef CO_PARAM_CHECK
	if (pJpgEncMng == NULL) {
		Ddim_Assertion(("im_jpeg_ctrl_enc(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

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

	// Set Jpeg base management table to a global table
	S_GIM_JPEG_ENC_MNG = *pJpgEncMng;

	// JPMODE
	// S_ENDIAN:1/P_ENDIAN:1/DISPOSAL:0
	ioJpg7.jpmode.word = 0x30;
	// sampling type
	ioJpg7.jpmode.bit.mmode = pJpgEncMng->yccSmpl;

	// JPQTABLE
	ioJpg7.jpqtable.bit.qt0l = pJpgEncMng->component[0].quantTblNo & 0x01;
	ioJpg7.jpqtable.bit.qt0u = (pJpgEncMng->component[0].quantTblNo >> 1) & 0x01;
	ioJpg7.jpqtable.bit.qt1l = pJpgEncMng->component[1].quantTblNo & 0x01;
	ioJpg7.jpqtable.bit.qt1u = (pJpgEncMng->component[1].quantTblNo >> 1) & 0x01;
	ioJpg7.jpqtable.bit.qt2l = pJpgEncMng->component[2].quantTblNo & 0x01;
	ioJpg7.jpqtable.bit.qt2u = (pJpgEncMng->component[2].quantTblNo >> 1) & 0x01;

	// jphtable
	ioJpg7.jphtable.bit.ht0dc = pJpgEncMng->component[0].hufDcTblNo;
	ioJpg7.jphtable.bit.ht0ac = pJpgEncMng->component[0].hufAcTblNo;
	ioJpg7.jphtable.bit.ht1dc = pJpgEncMng->component[1].hufDcTblNo;
	ioJpg7.jphtable.bit.ht1ac = pJpgEncMng->component[1].hufAcTblNo;
	ioJpg7.jphtable.bit.ht2dc = pJpgEncMng->component[2].hufDcTblNo;
	ioJpg7.jphtable.bit.ht2ac = pJpgEncMng->component[2].hufAcTblNo;

	// jpdriset
	ioJpg7.jpdriset.bit.jpdriset = pJpgEncMng->driMkNum;
	// jpwidth
	ioJpg7.jpwidth.bit.jpwidth = pJpgEncMng->width;
	// jpheight
	ioJpg7.jpheight.bit.jpheight = pJpgEncMng->lines;
	// jimgshdg
	// Fixed value
	ioJpg7.jimgshdg.bit.jimgshdg = 0;

	// JPFORMAT
	// Fixed value
	ioJpg7.jpformat.bit.codecnt = 0;
	ioJpg7.jpformat.bit.mkskip = pJpgEncMng->skipMkFlg;
	ioJpg7.jpformat.bit.exifmod = pJpgEncMng->exifFmtFlg;
	// jmode
	// CSC Off
	ioJpg7.jmode.bit.jcscccen = 0;
	// Not use Ext mode
	ioJpg7.jmode.bit.jpbdext = 0;
	ioJpg7.jmode.bit.jmemform = (guchar) pJpgEncMng->memFormat;
	ioJpg7.jmode.bit.jpbendian = pJpgEncMng->pbufCtrl.endian;
	ioJpg7.jmode.bit.jjbendian = pJpgEncMng->jbufCtrl.endian;
	ioJpg7.jmode.bit.jburstAlOn = pJpgEncMng->burstAlignment;
	// JPBSTA
	switch (pJpgEncMng->pbufCtrl.issueTranNum) {
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
	ioJpg7.jpbsta.bit.jpacache = pJpgEncMng->pbufCtrl.cacheType;
	ioJpg7.jpbsta.bit.jpaprot = pJpgEncMng->pbufCtrl.protType;
	// JJBSTA
	switch (pJpgEncMng->jbufCtrl.issueTranNum) {
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
	ioJpg7.jjbsta.bit.jjacache = pJpgEncMng->jbufCtrl.cacheType;
	ioJpg7.jjbsta.bit.japrot = pJpgEncMng->jbufCtrl.protType;

	// JCCTL
	if (pJpgEncMng->jburstLength == ImJpegCommon_E_IM_JPEG_BURST_INCR_8) {
		ioJpg7.jcctl.bit.jcrp = 0x2;
	}
	else {
		ioJpg7.jcctl.bit.jcrp = 0x3;
	}
	// JICTL
	ioJpg7.jictl.bit.jixp = 0;

	if (pJpgEncMng->pburstLength == ImJpegCommon_E_IM_JPEG_BURST_INCR_8) {
		ioJpg7.jictl.bit.jirp = 0x2;
	}
	else {
		ioJpg7.jictl.bit.jirp = 0x3;
	}
	ioJpg7.jictl.bit.b12m = pJpgEncMng->bitDepth;

	// Periodic interrupt setting
	// line unit
	if (pJpgEncMng->pintLine != 0) {
		ioJpg7.jinten.bit.jlineen = 1;
		ioJpg7.jlineval.bit.jlineval = pJpgEncMng->pintLine;
	}
	else {
		ioJpg7.jinten.bit.jlineen = 0;
		ioJpg7.jlineval.bit.jlineval = 0;
	}
	// sector unit
	if (pJpgEncMng->pintSect != 0) {
		ioJpg7.jinten.bit.jsecten = 1;
		ioJpg7.jsectval.bit.jsectval = pJpgEncMng->pintSect;
	}
	else {
		ioJpg7.jinten.bit.jsecten = 0;
		ioJpg7.jsectval.bit.jsectval = 0;
	}

	// IIPSET
	ioJpg7.iipset.bit.portMode = pJpgEncMng->portMode;
	ioJpg7.iipset.bit.ringOn = pJpgEncMng->ringOn;
	ioJpg7.iipset.bit.blkSize = pJpgEncMng->blockSize;
	ioJpg7.iipset.bit.ringSize = pJpgEncMng->ringSize;

	// SRAM power down control
	if (pJpgEncMng->yccSmpl == ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400) {
		ioImg.srampd.bit.jpegpd = 0x7;
	}
	else {
		ioImg.srampd.bit.jpegpd = 0x5;
	}

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);
	// SRAM power down control wait time.
	DD_ARM_WAIT_NS(1000);
	return ImJpegCommon_D_IM_JPEG_OK;
}



/**
 * @brief		Get the frame settings for Jpeg decode.
 * @param[in]	None
 * @param[out]	TimgDecFrameMng*	pJpgDecFrmMng	:Pointer to JPEG Decode frame management table
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_PARAM_ERROR
 */
gint32	im_jpeg_get_ctrl_dec_frame(ImJpegCommon*self, TimgDecFrameMng* pJpgDecFrmMng )
{
#ifdef CO_PARAM_CHECK
	if (pJpgDecFrmMng == NULL) {
		Ddim_Assertion(("im_jpeg_get_ctrl_dec_frame(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK
	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);
	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	// JIMGAY
	pJpgDecFrmMng->yccAddr.y = ioJpg7.jimgay.bit.jimgay;
	// JIMGACB
	pJpgDecFrmMng->yccAddr.c = ioJpg7.jimgacb.bit.jimgacb;
	// JCODA
	pJpgDecFrmMng->codeAddr = ioJpg7.jcoda.bit.jcoda;
	// JCODSV
	pJpgDecFrmMng->codeSize = ((ioJpg7.jcodsv.word) * (kulonglong) ImJpegCommon_D_IM_JPEG_SECT_CNT);
	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);
	return ImJpegCommon_D_IM_JPEG_OK;
}

/**
 * @brief		JPEG Decoding process asynchronous.
 * @param[in]	None
 * @param[out]	None
 * @return		gint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_RUNNING_NG / ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR
 */
gint32 im_jpeg_start_dec( ImJpegCommon*self )
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
	// Decompression Error Code
	S_GIM_JPEG_DEC_MNG.errCode = 0;
	// Processing result
	S_GIM_JPEG_DEC_MNG.result = 0;
	S_GIM_JPEG_RESULT_JUDGE = 0;
	S_GIM_JPEG_LINE_CNT = 0;
	S_GIM_JPEG_SECT_CNT = 0;
	ercd = ddim_user_custom_clr_flg(self->ddimUserCustom,  FID_IM_JPEG, ~ImJpegCommon_D_IM_JPEG_FLG_WAIT_END);
	if ( DdimUserCustom_E_OK != ercd) {
		return ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR;
	}
	ddim_user_custom_ahb_reg_spin_lock(self->ddimUserCustom);
	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	// interrupt setting
	ioJpg7.jinten.word |= 0xC4D000;
	// JBUF start
	ioJpg7.jcctl.bit.jctrg = 1;
	// CORE start
	ioJpg7.jpcmd.bit.jstart = 1;
	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	ddim_user_custom_ahb_reg_spin_un_lock(self->ddimUserCustom);
	return ImJpegCommon_D_IM_JPEG_OK;
}

ImJpegCommon* 		im_jpeg_common_new(void)
{
	ImJpegCommon *self = g_object_new(IM_TYPE_JPEG_COMMON, NULL);
	return self;
}
