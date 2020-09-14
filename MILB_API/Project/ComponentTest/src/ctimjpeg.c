/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImJpeg类
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#include <string.h>
#include <stdlib.h>
#include "ddtop.h"
#include "driver_common.h"
#include "imjpegcommon.h"
#include "ddimusercustom.h"
// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#include "palladium_test_common.h"
#endif
// ### REMOVE_RELEASE END
#include "jdsjp7.h"

#include "ctimjpeg1.h"
#include "ctimjpeg3.h"
#include "ctimjpeg5.h"
#include "ctimjpeg.h"

G_DEFINE_TYPE(CtImJpeg, ct_im_jpeg, G_TYPE_OBJECT);

#define CT_IM_JPEG_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_JPEG, CtImJpegPrivate))

#define CtImJpeg_D_CT_IM_JPG_SPENC_RETRY_MAX_COUNT		(30)
#define CtImJpeg_M_MIN(val1, val2)			(((val1) < (val2))?(val1):(val2))
#define CtImJpeg_D_CT_IM_JPG_SPENC_MULTI_ON

struct _CtImJpegPrivate
{
	CtImJpeg *jpge1;
};

static guint16 S_GCT_IM_JPEG_CR;
/*
 *DECLS
 * */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static gulong 	ctImJpegCalcTargetSize(guint16 width, guint16 lines, CtImJpeg3TCtImJpgSpencMode mode);
static void 	ctImJpegSpecialSetTuningParam(CtImJpeg* self,CtImJpeg3* jpgencParam);
static gint32 	ctImJpegSpecialRunEncode(CtImJpeg* self, CtImJpeg3* jpgencParam,
			 	 	 	guint32 quality, guint16* errRatio);
static void 	ctImJpegSpecialInitParam(CtImJpeg* self, CtImJpeg3* jpgencParam,guchar* realenc);
static gint32 	ctImJpegSpecialInitMacro(CtImJpeg* self, CtImJpeg3* jpgencParam);
static gint32 	ctImJpegSpecialEncodePass1(CtImJpeg* self, CtImJpeg3* jpgencParam,guint32* quality);
static gint32 	ctImJpegSpecialEncodeReal(CtImJpeg* self, CtImJpeg3* jpgencParam,guint32* quality);

static void ct_im_jpeg_class_init(CtImJpegClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImJpegPrivate));
}

static void ct_im_jpeg_init(CtImJpeg *self)
{
	CtImJpegPrivate *priv = CT_IM_JPEG_GET_PRIVATE(self);
	priv->jpge1=ct_im_jpeg1_new();
}
/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
	CtImJpeg *self = (CtImJpeg*)object;
	CtImJpegPrivate *priv = CT_IM_JPEG_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg_parent_class)->dispose(object);

	if(priv->jpge1){
		g_object_unref(priv->jpge1);
		priv->jpge1=NULL;
	}

}

static void finalize_od(GObject *object)
{
//	CtImJpeg *self = (CtImJpeg*)object;
//	CtImJpegPrivate *priv = CT_IM_JPEG_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg_parent_class)->finalize(object);
}

static gulong ctImJpegCalcTargetSize(guint16 width, guint16 lines, CtImJpeg3TCtImJpgSpencMode mode)
{
	gulong result;
	guint16 cr;

	result= width * lines * 2;
	cr = S_GCT_IM_JPEG_CR;

	if (width == 160) {
		if ((cr >= 40) || (cr == 0)) {
			cr = 1;		// Max 4_5
		}else if (cr > 19) {
			cr = 19;	// min 20_0
		}
	}else{
		if ((mode == CtImJpeg3_T_CT_IM_JPG_SPENC_MODE_CAPTURE) || (mode == CtImJpeg3_T_CT_IM_JPG_SPENC_MODE_PLAY)) {
			if (cr >= 41) {
				cr = 0;		// Max 4_0
			}
		}
	}

	// cr to div value
	switch (cr) {
		case CtImJpeg_CR_4_0:
		case CtImJpeg_CR_5_0:
		case CtImJpeg_CR_6_0:
		case CtImJpeg_CR_7_0:
		case CtImJpeg_CR_8_0:
		case CtImJpeg_CR_9_0:
		case CtImJpeg_CR_10_0:
			result /= (gulong)cr / 2 + 4;
			break;
		case CtImJpeg_CR_4_5:
		case CtImJpeg_CR_5_5:
		case CtImJpeg_CR_6_5:
		case CtImJpeg_CR_7_5:
		case CtImJpeg_CR_8_5:
		case CtImJpeg_CR_9_5:
			result /= ((gdouble)cr + 8) / 2;
			break;
		case CtImJpeg_CR_12_0:
			result /= 12;
			break;
		case CtImJpeg_CR_14_0:
			result /= 14;
			break;
		case CtImJpeg_CR_16_0:
		case CtImJpeg_CR_17_0:
		case CtImJpeg_CR_18_0:
		case CtImJpeg_CR_19_0:
		case CtImJpeg_CR_20_0:
		case CtImJpeg_CR_21_0:
		case CtImJpeg_CR_22_0:
		case CtImJpeg_CR_23_0:
		case CtImJpeg_CR_24_0:
		case CtImJpeg_CR_25_0:
		case CtImJpeg_CR_26_0:
		case CtImJpeg_CR_27_0:
		case CtImJpeg_CR_28_0:
		case CtImJpeg_CR_29_0:
		case CtImJpeg_CR_30_0:
		case CtImJpeg_CR_31_0:
		case CtImJpeg_CR_32_0:
		case CtImJpeg_CR_33_0:
		case CtImJpeg_CR_34_0:
		case CtImJpeg_CR_35_0:
		case CtImJpeg_CR_36_0:
		case CtImJpeg_CR_37_0:
		case CtImJpeg_CR_38_0:
		case CtImJpeg_CR_39_0:
		case CtImJpeg_CR_40_0:
			result /= (gulong)cr + 1;
			break;
		case CtImJpeg_CR_3_0:
			result /= 3;
			break;
		case CtImJpeg_CR_3_5:
			result /= (gdouble)7 / 2;
			break;
		case CtImJpeg_CR_2_0:
			result /= 2;
			break;
		case CtImJpeg_CR_2_5:
			result /= (gdouble)5 / 2;
			break;
		case CtImJpeg_CR_2_7:
			result /= (gdouble)27 / 10;
			break;
		default:
			break;
	}
	return result;
}

static void ctImJpegSpecialSetTuningParam(CtImJpeg* self,CtImJpeg3* jpgencParam)
{
	guint32 pixs;

	pixs = jpgencParam->jpegEncTbl.width * jpgencParam->jpegEncTbl.lines;

	self->ratio = 0x00007999;
	self->maxRetry = 30;

	if(pixs <= (160 * 120)) {
		// ThumbNail
		self->shift = 0;
		self->downSpType = ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;
	}else if(pixs <= (640 *480)) {
		// Main VGA
		self->shift = 5;
		self->downSpType = ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;
	}else if(pixs <= (1700 * (1700 *3 /4))) {
		// Main 2M
		self->downSpType = ImJpegCommon_D_IM_JPEG_DOWNSP_1_2;
		self->shift = 10;
	}else {
		self->downSpType = ImJpegCommon_D_IM_JPEG_DOWNSP_1_8;
		self->shift = 10;
	}

	self->targetBytes = ctImJpegCalcTargetSize(jpgencParam->jpegEncTbl.width,
						jpgencParam->jpegEncTbl.lines, jpgencParam->mode);
}

static gint32 ctImJpegSpecialRunEncode(CtImJpeg* self, CtImJpeg3* jpgencParam,
			 guint32 quality, guint16* errRatio)
{
	CtImJpegPrivate *priv = CT_IM_JPEG_GET_PRIVATE(self);
	gint32 ret;

	ret = im_jpeg_set_quality(quality, 0);
	if(ret != ImJpegCommon_D_IM_JPEG_OK) {
		return ret;
	}
	ret = im_jpeg_get_ctrl_enc_frame(&jpgencParam->jpegEncFrameTbl);
	if(ret != ImJpegCommon_D_IM_JPEG_OK) {
		return ret;
	}
	*errRatio = im_jpeg_set_down_sampling_rate(self->downSpType);
	ret = im_jpeg_start_enc();
	if(ret != ImJpegCommon_D_IM_JPEG_OK) {
		return ret;
	}
	ct_im_jpeg1_start_hclock(priv->jpge1);
	Ddim_Print(("IO_JPG7.JINTEN   	=0x%lX\n", IO_JPG7.JINTEN.word));
	Ddim_Print(("IO_JPG7.JPSTATUS.bit.JPSTATUS =0x%X\n", IO_JPG7.JPSTATUS.bit.JPSTATUS));
	Ddim_Print(("IO_JPG7.JPCMD    	=0x%lX\n", IO_JPG7.JPCMD.word));
	Ddim_Print(("IO_JPG7.JPWIDTH  	=0x%lX\n", IO_JPG7.JPWIDTH.word));
	Ddim_Print(("IO_JPG7.JPHEIGHT 	=0x%lX\n", IO_JPG7.JPHEIGHT.word));
	Ddim_Print(("IO_JPG7.JIMGYGH  	=0x%lX\n", IO_JPG7.JIMGYGH.word));
	Ddim_Print(("IO_JPG7.JIMGCGH  	=0x%lX\n", IO_JPG7.JIMGCGH.word));
	Ddim_Print(("IO_JPG7.JIMGSH   	=0x%lX\n", IO_JPG7.JIMGSH.word));
	Ddim_Print(("IO_JPG7.JIMGSV   	=0x%lX\n", IO_JPG7.JIMGSV.word));
	Ddim_Print(("IO_JPG7.JIMGSHDG =0x%lX\n", IO_JPG7.JIMGSHDG.word));
	Ddim_Print(("IO_JPG7.JPFORMAT =0x%lX\n", IO_JPG7.JPFORMAT.word));
	Ddim_Print(("IO_JPG7.JMODE    	=0x%lX\n", IO_JPG7.JMODE.word));
	Ddim_Print(("IO_JPG7.JCCTL    		=0x%lX\n", IO_JPG7.JCCTL.word));
	Ddim_Print(("IO_JPG7.JICTL    		=0x%lX\n", IO_JPG7.JICTL.word));
	Ddim_Print(("IO_JPG7.JJBSTA  	 	=0x%lX\n", IO_JPG7.JJBSTA.word));
	Ddim_Print(("IO_JPG7.JPBSTA   		=0x%lX\n", IO_JPG7.JPBSTA.word));
	Ddim_Print(("IO_JPG7.JPMODE  	=0x%lX\n", IO_JPG7.JPMODE.word));
	ct_im_jpeg1_stop_hclock(priv->jpge1);


#ifdef CO_DEBUG_ON_PC
	ct_im_jpeg1_encode_int_handler(1);
#endif	// CO_DEBUG_ON_PC

	ret = im_jpeg_wait_end_enc(&jpgencParam->jpegEncTbl, 1000);
	Ddim_Print(("I:im_jpeg_wait_end_enc ret=%d\n", ret));
	if(ret != ImJpegCommon_D_IM_JPEG_OK) {
		if(ret != ImJpegCommon_D_IM_JPEG_ENCODE_PAUSE) {
			Ddim_Print(("E:jpeg encode error ret=%d\n", ret));
			jpgencParam->jpegEncTbl.codeSize = 0;
			return ret;
		}
	}
	if((jpgencParam->jpegEncTbl.codeSize < jpgencParam->limitSize) && (ret == ImJpegCommon_D_IM_JPEG_OK)) {
		return ImJpegCommon_D_IM_JPEG_OK;
	}else {
		return ImJpegCommon_D_IM_JPEG_ENCODE_PAUSE;
	}
}

static void ctImJpegSpecialInitParam(CtImJpeg* self, CtImJpeg3* jpgencParam,guchar* realenc)
{
	//---- Set downsp_typeation Ratio & Target Size ----
	ctImJpegSpecialSetTuningParam(self, jpgencParam);

	self->maxRetry = CtImJpeg_M_MIN(self->maxRetry, CtImJpeg_D_CT_IM_JPG_SPENC_RETRY_MAX_COUNT);

	jpgencParam->jpegEncFrameTbl.limitSize = jpgencParam->limitSize;

	//---- Set SDRAM Limit ----
	Ddim_Print(("TargetSize=%lu\n", self->targetBytes));
	Ddim_Print(("limit Size=%lu\n", jpgencParam->limitSize));

	if(self->targetBytes > jpgencParam->limitSize) {
		self->targetBytes = jpgencParam->limitSize;
	}

	Ddim_Print(("==== Target(limited)=%lu ====\n", self->targetBytes));

	self->targetBytes >>= self->shift;
	self->targetBytes = (self->targetBytes * self->ratio) / 0x8000;

	Ddim_Print(("==== Target * %.2f ====\n", (((gfloat)self->ratio) / 0x8000)));
	Ddim_Print(("==== TargetSize=%lu ====\n", self->targetBytes));

	//---- JPEG fixed Size ----
#ifdef CtImJpeg_D_CT_IM_JPG_SPENC_MULTI_ON
	if(self->downSpType == ImJpegCommon_D_IM_JPEG_DOWNSP_NONE) {
		jpgencParam->jpegEncFrameTbl.codeCountFlg = ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
		*realenc = 0;
	}else {
		// Pass_1
		jpgencParam->jpegEncFrameTbl.codeCountFlg = ImJpegCommon_D_IM_JPEG_ENABLE_ON;
		*realenc = 1;
	}
#else
	jpgencParam->jpegEncFrameTbl.codeCountFlg = ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	*realenc = 0;
#endif
}

static gint32 ctImJpegSpecialInitMacro(CtImJpeg* self, CtImJpeg3* jpgencParam)
{
	gint32 ret;

#ifdef CO_DEBUG_ON_PC
	IO_JPG7.JSTATE.bit.JALLRSTP = 0;
#endif

	im_jpeg_init();
	im_jpeg_set_qtbl(NULL, 0);
	ret = im_jpeg_ctrl_enc(&jpgencParam->jpegEncTbl);
	if(ret != ImJpegCommon_D_IM_JPEG_OK) {
		return ret;
	}
	ret = im_jpeg_get_ctrl_enc_frame(&jpgencParam->jpegEncFrameTbl);
	if(ret != ImJpegCommon_D_IM_JPEG_OK) {
		return ret;
	}
	im_jpeg_set_down_sampling_rate(self->downSpType);

	return ImJpegCommon_D_IM_JPEG_OK;
}

static gint32 ctImJpegSpecialEncodePass1(CtImJpeg* self, CtImJpeg3* jpgencParam,guint32* quality)
{
	guchar 	flgHretry = 0;
	guchar 	retryCnt;
	guint32	quality0 = 0;
	guint32	quality1 = 0;
	guint32	qualityBest = 0;
	guint16	errRatio;
	gint32		size0 = 0;
	gint32		size1 = 0;
	gint32		sizeDiffBest = 0x00FFFFFF;
	gint32		jpegSizeTry[CtImJpeg_D_CT_IM_JPG_SPENC_RETRY_MAX_COUNT];
	gint32		ret;

	for(retryCnt = 0; retryCnt < self->maxRetry; retryCnt++) {
		if(0 == retryCnt) {
			quality0 = *quality = 0x40;
		}else if(1 == retryCnt) {
			quality1 = *quality = 50<<10;
		}
		//---- try ---
		ret = ctImJpegSpecialRunEncode(self, jpgencParam, *quality, &errRatio);
		if((ret != ImJpegCommon_D_IM_JPEG_ENCODE_PAUSE) && (ret != ImJpegCommon_D_IM_JPEG_OK)) {
			// Encode error
			return ret;
		}

		jpegSizeTry[retryCnt] = (jpgencParam->jpegEncTbl.codeSize >> (self->shift - (self->downSpType * 2)));
		Ddim_Print(("errRatio [0x%X] :\n", errRatio));
		if(errRatio != 0x100) {
			jpegSizeTry[retryCnt] = (jpegSizeTry[retryCnt] * errRatio) >> 8;
		}
		Ddim_Print(("Count [%2u] : quality=%2d.%d  size=%4u [%lu] /tgtsize=%4lu\n",
				retryCnt, (*quality) >> 10, (*quality) & 0x3FF, jpegSizeTry[retryCnt], \
				jpgencParam->jpegEncTbl.codeSize, self->targetBytes));


		//==== Check CodeSize ====
		//---- 1st ,2nd ----
		if(0 == retryCnt) {
			if(self->targetBytes < jpegSizeTry[retryCnt]) {
				Ddim_Print(("Abort0 : Lowest SF\n"));
				break;
			}
			size0 = jpegSizeTry[retryCnt];
		}else if(1 == retryCnt) {
			if (self->targetBytes > jpegSizeTry[retryCnt]) {
				if(flgHretry != 0) {
					Ddim_Print(("Abort1 : High Side SF\n"));
					break;
				}else {
					*quality = 70 << 10;
					flgHretry++;
				}
			}else {
				size1 = jpegSizeTry[retryCnt];
				*quality = ((self->targetBytes - size0) * (quality1 - quality0)) / (size1 - size0) + quality0;
			}
		}else {
			//---- save the best value ----
			if(self->targetBytes > jpegSizeTry[retryCnt]) {
				Ddim_Print(("---> Update1\n"));
				if(sizeDiffBest > self->targetBytes - jpegSizeTry[retryCnt]) {
					sizeDiffBest = self->targetBytes - jpegSizeTry[retryCnt];
					qualityBest = *quality;
					Ddim_Print(("---> Update2 Best quality!!\n"));
				}
			}
			if(self->targetBytes > jpegSizeTry[retryCnt]) {
				quality0 = *quality;
				size0 = jpegSizeTry[retryCnt];
			}else {
				quality1 = *quality;
				size1 = jpegSizeTry[retryCnt];
			}
			//---- OK : Size （Code size is target in - 0%～+1.56%
			if((jpegSizeTry[retryCnt] >= self->targetBytes) &&
				// tgt+1.56%
				(jpegSizeTry[retryCnt] < (self->targetBytes + (self->targetBytes >> 6)))) {
				Ddim_Print(("OK : JPEG Size in Target Range!!\n"));
				break;
			}
			//---- white---
			if(retryCnt > 0) {
				// -0.78%
				if((jpegSizeTry[retryCnt-1] - (jpegSizeTry[retryCnt-1] >> 7) < jpegSizeTry[retryCnt]) &&
					// +0.78%
					(jpegSizeTry[retryCnt-1] + (jpegSizeTry[retryCnt-1] >> 7) > jpegSizeTry[retryCnt])) {
					if(jpegSizeTry[retryCnt] < self->targetBytes) {
						Ddim_Print(("Abort2 : Saturation1 Lower Size [like White Image]\n"));
						break;
					}
				}
				if(jpegSizeTry[retryCnt-1] == jpegSizeTry[retryCnt]) {
					if(jpegSizeTry[retryCnt] < self->targetBytes) {
						Ddim_Print(("Abort3 : Saturation2\n"));
						break;
					}
				}
			}
			//---- Zero Div ----
			if(size1 == size0) {
				Ddim_Print(("Abort4 : Zero Div\n"));
				break;
			}

			//---- calc quarity ----
			*quality = ((self->targetBytes - size0) * (quality1 - quality0)) / (size1 - size0) + quality0;

			//---- HOKEN ----
			if(retryCnt >= (self->maxRetry -2)) {
				if(qualityBest != 0) {
					*quality = qualityBest;
					Ddim_Print(("**** HOKEN quality BEST ****\n"));
					break;
				}else if(jpegSizeTry[retryCnt] < self->targetBytes) {
					Ddim_Print(("**** HOKEN break ****\n"));
					break;
				}else {
					*quality = 10;
					Ddim_Print(("**** HOKEN Force set High-CompRatio ****\n"));
				}
			}
		}
	}
	return ImJpegCommon_D_IM_JPEG_OK;
}

static gint32 ctImJpegSpecialEncodeReal(CtImJpeg* self, CtImJpeg3* jpgencParam,guint32* quality)
{
	guint16	errRatio;
	gint32		ret;

	Ddim_Print(("**** Real Encode ****\n"));

	jpgencParam->jpegEncFrameTbl.codeCountFlg = ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->downSpType = ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	while(1) {
		ret = ctImJpegSpecialRunEncode(self, jpgencParam, *quality, &errRatio);

		Ddim_Print(("**** MainEnc : quality=%2u.%u  size=%4lu [%lu] /tgtsize=%4lu ****\n", (*quality) >> 10,
				(*quality) & 0x3FF, (jpgencParam->jpegEncTbl.codeSize >> self->shift),
						jpgencParam->jpegEncTbl.codeSize, self->targetBytes));

		if(ret == ImJpegCommon_D_IM_JPEG_OK) {
			// Encode success
			return ret;
		}
		if(ret != ImJpegCommon_D_IM_JPEG_ENCODE_PAUSE) {
			jpgencParam->jpegEncTbl.codeSize = 0;
			// Encode error
			return ret;
		}

		// Code size over
		*quality -= (1<<10);

		Ddim_Print(("RETRY at MainEncode!!\n"));
	}
}
/*
 *PUBLIC
 * */
gint16 ct_im_jpeg_get_encode_quality(gushort cr)
{
	S_GCT_IM_JPEG_CR = cr;
	gint16 quality = 1;

	switch (cr) {
		case CtImJpeg_CR_2_0:
		case CtImJpeg_CR_2_5:
		case CtImJpeg_CR_2_7:
		case CtImJpeg_CR_3_0:
		case CtImJpeg_CR_3_5:
		case CtImJpeg_CR_4_0:
		case CtImJpeg_CR_4_5:
			quality = 40;
			break;
		case CtImJpeg_CR_5_0:
		case CtImJpeg_CR_5_5:
		case CtImJpeg_CR_6_0:
		case CtImJpeg_CR_6_5:
			break;
		case CtImJpeg_CR_7_0:
			quality = 8;
			break;
		case CtImJpeg_CR_7_5:
			break;
		case CtImJpeg_CR_8_0:
			quality = 7;
			break;
		case CtImJpeg_CR_8_5:
		case CtImJpeg_CR_9_0:
		case CtImJpeg_CR_9_5:
			break;
		case CtImJpeg_CR_10_0:
			quality = 3;
			break;
		case CtImJpeg_CR_12_0:
			break;
		case CtImJpeg_CR_14_0:
			quality = 2;
			break;
		case CtImJpeg_CR_16_0:
		case CtImJpeg_CR_17_0:
		case CtImJpeg_CR_18_0:
			break;
		case CtImJpeg_CR_19_0:
			quality = 1;
			break;
		case CtImJpeg_CR_20_0:
		case CtImJpeg_CR_21_0:
		case CtImJpeg_CR_22_0:
		case CtImJpeg_CR_23_0:
		case CtImJpeg_CR_24_0:
		case CtImJpeg_CR_25_0:
		case CtImJpeg_CR_26_0:
		case CtImJpeg_CR_27_0:
		case CtImJpeg_CR_28_0:
		case CtImJpeg_CR_29_0:
		case CtImJpeg_CR_30_0:
		case CtImJpeg_CR_31_0:
		case CtImJpeg_CR_32_0:
		case CtImJpeg_CR_33_0:
		case CtImJpeg_CR_34_0:
		case CtImJpeg_CR_35_0:
		case CtImJpeg_CR_36_0:
		case CtImJpeg_CR_37_0:
		case CtImJpeg_CR_38_0:
		case CtImJpeg_CR_39_0:
		case CtImJpeg_CR_40_0:
			break;
		default :
			break;
	}
	return quality;
}

// Capture_Jpeg_Encode
gulong ct_im_jpeg_special_encode(CtImJpeg *self,CtImJpeg3* jpgencParam)
{
	self->downSpType = ImJpegCommon_D_IM_JPEG_DOWNSP_1_8;
	self->maxRetry = CtImJpeg_D_CT_IM_JPG_SPENC_RETRY_MAX_COUNT;
	self->shift = 10;
	self->ratio = 0x00007999;					// 0x8000 => 1.0
	guchar		realenc = 0;
	guint32	quality = 0;
	gint32		ret;
	gulong		jpegSize = 0;

	// parameter initialize
	ctImJpegSpecialInitParam(self, jpgencParam, &realenc);

	//---- JPEG Open ----
	ret = im_jpeg_open(1000);
	if(ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("E:jpeg encode open error ret=%d\n", ret));
		return 0;
	}

	while(1) {	// for Error return
		ret = ctImJpegSpecialInitMacro(self , jpgencParam);
		if (ret != D_DDIM_OK) {
			Ddim_Print(("E:jpeg encode set error width=%d, line=%d, ret=%d\n",
					jpgencParam->jpegEncTbl.width, jpgencParam->jpegEncTbl.lines, ret));
			jpegSize = 0UL;
			break;
		}

		//==== Retry Loop ====
		ret = ctImJpegSpecialEncodePass1(self, jpgencParam, &quality);
		if(ret != ImJpegCommon_D_IM_JPEG_OK) {
			jpegSize = 0UL;
			break;
		}

		// ==== JPEG Encode ====
		if((self->downSpType != ImJpegCommon_D_IM_JPEG_DOWNSP_NONE) || (realenc == 1)) {
			ret = ctImJpegSpecialEncodeReal(self, jpgencParam, &quality);
			if(ret != ImJpegCommon_D_IM_JPEG_OK) {
				jpegSize = 0UL;
				break;
			}
		}

		//---- return val ----
		jpgencParam->quality = (guint16)(quality >> 10);		// return 10bit
		jpegSize = jpgencParam->jpegEncTbl.codeSize;

		break;
	}

	ret = im_jpeg_close();
	if(ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("E:jpeg encode close error ret=%d\n", ret));
		jpegSize = 0UL;
	}

	Ddim_Print(("#### Return : size=%lu  quality=%u ####\n", jpegSize, jpgencParam->quality));

	return jpegSize;
}

gulong ct_im_jpeg_get_ycc_addr(void)
{
	return CtImJpeg5_D_CT_JPEG_YCC_ADDR;
}

gulong ct_im_jpeg_get_code_addr(void)
{
	return CtImJpeg5_D_CT_JPEG_CODE_ADDR;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImJpeg类的一个实例
 */
CtImJpeg* ct_im_jpeg_new()
{
	CtImJpeg *self = g_object_new(CT_TYPE_IM_JPEG,NULL);
	return self;
}
