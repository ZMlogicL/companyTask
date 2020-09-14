/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImJpeg5类
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

#include "ctimjpeg.h"
#include "ctimjpeg1.h"
#include "ctimjpeg2.h"
#include "ctimjpeg3.h"
#include "ctimjpeg4.h"
#include "ctimjpeg6.h"
#include "ctimjpeg5.h"

G_DEFINE_TYPE(CtImJpeg5, ct_im_jpeg5, G_TYPE_OBJECT);

#define CT_IM_JPEG_5_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_JPEG_5, CtImJpeg5Private))

struct _CtImJpeg5Private
{
	CtImJpeg1 *jpeg1;
	CtImJpeg2 *jpeg2;
	CtImJpeg4 *jpeg4;
};

static TimgQuatTbl S_G_JPEG_QTBL_Y = {
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
static TimgQuatTbl S_G_JPEG_QTBL_C = {
	{	0x11, 0x12, 0x18, 0x2F, 0x63, 0x63, 0x63, 0x63,
		0x12, 0x15, 0x1A, 0x42, 0x63, 0x63, 0x63, 0x63,
		0x18, 0x1A, 0x38, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x2F, 0x42, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63	}
};
/*
 *DECLS
 * */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static void 	ctImJpegSetQtbl(CtImJpeg5 *self,guchar next);
static void 	ctImJpegSetQuality(CtImJpeg5 *self,guchar next);
#ifdef CO_PT_ENABLE
static void 	ctJpegDecodeSyncPalladiumIn(const TimgDecInput* const input, const gulong lines);
static void 	ctJpegDecodeSyncPalladiumOut(const TimgDecInput* const input,
						const TimgDecOutput* const output);
#endif

static void ct_im_jpeg5_class_init(CtImJpeg5Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImJpeg5Private));
}

static void ct_im_jpeg5_init(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);
	priv->jpeg1=ct_im_jpeg1_new();
	priv->jpeg2=NULL;
	priv->jpeg4=ct_im_jpeg4_new();
}
/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
	CtImJpeg5 *self = (CtImJpeg5*)object;
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg5_parent_class)->dispose(object);

	if(priv->jpeg1){
		g_object_unref(priv->jpeg1);
		priv->jpeg1=NULL;
	}

	if(priv->jpeg4){
			g_object_unref(priv->jpeg4);
			priv->jpeg4=NULL;
		}
}

static void finalize_od(GObject *object)
{
//	CtImJpeg5 *self = (CtImJpeg5*)object;
//	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg5_parent_class)->finalize(object);
}

// ### REMOVE_RELEASE END
static void ctImJpegSetQtbl(CtImJpeg5 *self,guchar next)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);
	TimgQuatTblPack quantTblPack;
	gint32 i;

#if 1
	quantTblPack.quantizationTbl0 = &S_G_JPEG_QTBL_Y;
	quantTblPack.quantizationTbl1 = &S_G_JPEG_QTBL_C;
	quantTblPack.quantizationTbl2 = &S_G_JPEG_QTBL_Y;
	quantTblPack.quantizationTbl3 = &S_G_JPEG_QTBL_C;
#else
	quantTblPack.quantizationTbl0 = NULL;
	quantTblPack.quantizationTbl1 = NULL;
	quantTblPack.quantizationTbl2 = NULL;
	quantTblPack.quantizationTbl3 = NULL;
#endif

	im_jpeg_set_qtbl(&quantTblPack, next);

	if (!next) {
		ct_im_jpeg1_start_hclock(priv->jpeg1);
		for (i=0; i < 16; i++) {
			Ddim_Print(("IO_JPG7.JPQT0[%d]=0x%lX\n", i, IO_JPG7.JPQT0.word[i]));
		}
		for (i=0; i < 16; i++) {
			Ddim_Print(("IO_JPG7.JPQT1[%d]=0x%lX\n", i, IO_JPG7.JPQT1.word[i]));
		}
		for (i=0; i < 16; i++) {
			Ddim_Print(("IO_JPG7.JPQT2[%d]=0x%lX\n", i, IO_JPG7.JPQT2.word[i]));
		}
		for (i=0; i < 16; i++) {
			Ddim_Print(("IO_JPG7.JPQT3[%d]=0x%lX\n", i, IO_JPG7.JPQT3.word[i]));
		}
		ct_im_jpeg1_stop_hclock(priv->jpeg1);
	}
}

static void ctImJpegSetQuality(CtImJpeg5 *self,guchar next)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);
	gint32 i;

	im_jpeg_set_quality(0, next);

	ct_im_jpeg1_start_hclock(priv->jpeg1);
		for (i=0; i < 16; i++) {
			Ddim_Print(("IO_JPG7.JPQT0[%d]=0x%lX\n", i, IO_JPG7.JPQT0.word[i]));
		}
		for (i=0; i < 16; i++) {
			Ddim_Print(("IO_JPG7.JPQT1[%d]=0x%lX\n", i, IO_JPG7.JPQT1.word[i]));
		}
		for (i=0; i < 16; i++) {
			Ddim_Print(("IO_JPG7.JPQT2[%d]=0x%lX\n", i, IO_JPG7.JPQT2.word[i]));
		}
		for (i=0; i < 16; i++) {
			Ddim_Print(("IO_JPG7.JPQT3[%d]=0x%lX\n", i, IO_JPG7.JPQT3.word[i]));
		}
	ct_im_jpeg1_stop_hclock(priv->jpeg1);
}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
static void ctJpegDecodeSyncPalladiumIn(const TimgDecInput* const input, const gulong lines)
{
	gulong inDataSizY;
	gulong inDataSizC;

	// Calc Y bytes.
	inDataSizY = ((gulong)input->globalYWidth) * lines;

	switch(input->smplType) {
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC444:	// FALLTHROUGH
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422:
			inDataSizC = ((gulong)input->globalCWidth) * lines;
			break;
//		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420:
		default:
			inDataSizC = ((gulong)input->globalCWidth) * (lines /2);
			break;
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400:
			inDataSizC = 0ul;
	}
	if(input->memFormat == ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE) {
		inDataSizC *= 2;
	}


	Ddim_Print(("%s(): Palladium_Set_In_Localstack(0x%lx, %lu)\n", __func__,
							((gulong)input->codeAddr), inDataSizY + inDataSizC));
	Palladium_Set_In_Localstack(((gulong)input->codeAddr), inDataSizY + inDataSizC);//NO
}

static void ctJpegDecodeSyncPalladiumOut(const TimgDecInput* const input,
									const TimgDecOutput* const output)
{
	gulong outDataSizY;
	gulong outDataSizC;

	// Calc Y bytes.
	outDataSizY = ((gulong)input->globalYWidth) * output->orgLines;

	switch(input->smplType) {
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC444:	// FALLTHROUGH
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422:
			outDataSizC = ((gulong)input->globalCWidth) * output->orgLines;
			break;
//		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420:
		default:
			outDataSizC = ((gulong)input->globalCWidth) * (output->orgLines /2);
			break;
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400:
			outDataSizC = 0ul;
	}
	if(input->memFormat == ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE) {
		outDataSizC *= 2;
	}


	Ddim_Print(("%s(): Palladium_Set_Out_Localstack(0x%lx, %lu)\n", __func__,
							((gulong)input->dstYccAddr.y), outDataSizY + outDataSizC));
	Palladium_Set_Out_Localstack(((gulong)input->dstYccAddr.y), outDataSizY + outDataSizC);//NO
}
#endif
/*
 *PUBLIC
 * */
void ct_im_jpeg5_1_3_1(CtImJpeg5 *self)
{
	gint32 ret;
	ret = im_jpeg_open(D_DDIM_WAIT_END_TIME);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_open error ret=0x%X\n", ret));
		return;
	}

	ctImJpegSetQtbl(self,0);

	ret = im_jpeg_close();
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_close error ret=0x%X\n", ret));
		return;
	}
	return;
}

void ct_im_jpeg5_1_3_2(CtImJpeg5 *self)
{
	gint32 ret;
	ret = im_jpeg_open(D_DDIM_WAIT_END_TIME);//NO
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_open error ret=0x%X\n", ret));
		return;
	}

	ctImJpegSetQtbl(self,1);

	ret = im_jpeg_close();
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_close error ret=0x%X\n", ret));
		return;
	}
	return;
}

void ct_im_jpeg5_1_3_3(CtImJpeg5 *self)
{
	gint32 ret;
	ret = im_jpeg_open(D_DDIM_WAIT_END_TIME);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_open error ret=0x%X\n", ret));
		return;
	}

	ctImJpegSetQuality(self,0);

	ret = im_jpeg_close();
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_close error ret=0x%X\n", ret));
		return;
	}
	return;
}

void ct_im_jpeg5_1_3_4(CtImJpeg5 *self)
{
	gint32 ret;
	ret = im_jpeg_open(D_DDIM_WAIT_END_TIME);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_open error ret=0x%X\n", ret));
		return;
	}

	ctImJpegSetQuality(self,1);

	ret = im_jpeg_close();
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_close error ret=0x%X\n", ret));
		return;
	}
	return;
}

void ct_im_jpeg5_1_4_14(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);
	TimgDecInput		input;
	TimgDecOutput	output;
	gint32	ret;

	memset(&input, 0, sizeof(TimgDecInput));
	memset(&output, 0, sizeof(TimgDecOutput));

	input.globalYWidth	= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	input.globalCWidth	= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	input.memFormat		= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE_DOT;
	input.smplType			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;
	input.codeSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	input.codeAddr			= CtImJpeg5_D_CT_JPEG_CODE_ADDR;
	input.dstYccAddr.y	= CtImJpeg5_D_CT_JPEG_YCC_ADDR;
	input.dstYccAddr.c	= CtImJpeg5_D_CT_JPEG_YCC_ADDR + \
			(CtImJpeg5_D_CT_JPEG_TEST_SIZE_H * CtImJpeg5_D_CT_JPEG_TEST_SIZE_V);

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ctJpegDecodeSyncPalladiumIn(&input, CtImJpeg5_D_CT_JPEG_TEST_SIZE_V);
	IO_JPG7.JPWIDTH.bit.JPWIDTH		= input.globalYWidth;
	IO_JPG7.JPHEIGHT.bit.JPHEIGHT	= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
#endif

// ### REMOVE_RELEASE END
	ret = Im_JPEG_Decode_Sync(&input, &output);
	Ddim_Print(("Im_JPEG_Decode_Sync ret=0x%X\n", ret));

	Ddim_Print(("output.smplType =0x%X\n", output.smplType));
	Ddim_Print(("output.orgWidth =0x%X\n", output.orgWidth));
	Ddim_Print(("output.orgLines =0x%X\n", output.orgLines));
	Ddim_Print(("output.errCode  =0x%X\n", output.errCode));


	ct_im_jpeg2_set_ycc_out_bytes(priv->jpeg2,output.smplType, input.memFormat, input.globalYWidth,
				input.globalCWidth, output.orgLines);

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	if(ret == ImJpegCommon_D_IM_JPEG_OK) {
		ctJpegDecodeSyncPalladiumOut(&input, &output);
	}
#endif

// ### REMOVE_RELEASE END
	return;
}

void ct_im_jpeg5_1_4_2(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);
	TimgDecMng inJpegMng;
	TimgDecMng outJpegMng;
	TimgDecFrameMng inJpegFrmMng;
	TimgDecFrameMng outJpegFrmMng;
	gint32 ret;

	memset(&inJpegMng, 0, sizeof(TimgDecMng));
	memset(&outJpegMng, 0, sizeof(TimgDecMng));
	memset(&inJpegFrmMng, 0, sizeof(TimgDecFrameMng));
	memset(&outJpegFrmMng, 0, sizeof(TimgDecFrameMng));

	inJpegMng.memFormat						=ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE_DOT;
	inJpegMng.extMode								=ImJpegCommon_E_IM_JPEG_RESIZE_EXT_BAND;
	inJpegMng.corrMode							=ImJpegCommon_D_IM_JPEG_ENABLE_ON;
	inJpegMng.skipMkFlg							=ImJpegCommon_D_IM_JPEG_ENABLE_ON;
	inJpegMng.pintLine								=0xFFFF;
	inJpegMng.pintSect								=0x11111111;
	inJpegMng.colorBand.yBand				=0xFF;
	inJpegMng.colorBand.cbBand			=0x11;
	inJpegMng.colorBand.crBand			=0x22;
	inJpegMng.pbufCtrl.endian					=ImJpegCommon_E_IM_JPEG_ENDIAN_BIG;
	inJpegMng.pbufCtrl.issueTranNum	=ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
	inJpegMng.pbufCtrl.cacheType			=ImJpegCommon_D_IM_JPEG_ON_CACHE_RW_WRITE_BACK;
	inJpegMng.pbufCtrl.protType				=ImJpegCommon_D_IM_JPEG_I_NSEC_PRIVILEGED_ACCESS;
	inJpegMng.jbufCtrl.endian					=ImJpegCommon_E_IM_JPEG_ENDIAN_BIG;
	inJpegMng.jbufCtrl.issueTranNum		=ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
	inJpegMng.jbufCtrl.cacheType			=ImJpegCommon_D_IM_JPEG_ON_CACHE_RW_WRITE_BACK;
	inJpegMng.jbufCtrl.protType				=ImJpegCommon_D_IM_JPEG_I_NSEC_PRIVILEGED_ACCESS;
	inJpegMng.jburstLength						=ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
	inJpegMng.pburstLength						=ImJpegCommon_E_IM_JPEG_BURST_INCR_16;
	inJpegMng.smplType								=ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;
	inJpegMng.orgWidth								=0;
	inJpegMng.orgLines								=0;
	inJpegMng.result									=0;
	inJpegMng.errCode								=0;
	inJpegMng.pcallback								=NULL;

	inJpegFrmMng.globalYWidth	= 0xFFFFF;
	inJpegFrmMng.globalCWidth	= 0x99999;
	inJpegFrmMng.cutoutFlg			= ImJpegCommon_D_IM_JPEG_ENABLE_ON;
	inJpegFrmMng.cutoutWidth		= 0xFFFF;
	inJpegFrmMng.cutoutLines		= 0x0001;
	inJpegFrmMng.cutoutOffsetH	= 0x1234;
	inJpegFrmMng.cutoutOffsetV	= 0x4321;
	inJpegFrmMng.yccAddr.y			= 0xFFFFFFFF;
	inJpegFrmMng.yccAddr.c			= 0x00000001;
	inJpegFrmMng.codeAddr			= 0x22222222;
	inJpegFrmMng.codeSize			= 0x1FFFFFFFC00;

	ret = im_jpeg_open(D_DDIM_WAIT_END_TIME);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_open error ret=0x%X\n", ret));
		return;
	}

	ret = im_jpeg_ctrl_dec(&inJpegMng);
	Ddim_Print(("im_jpeg_ctrl_dec ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_ctrl_dec_frame(&inJpegFrmMng);
	Ddim_Print(("im_jpeg_ctrl_dec_frame ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ct_im_jpeg1_start_hclock(priv->jpeg1);
	Ddim_Print(("IO_JPG7.JPMODE.bit.S_ENDIAN       	=0x%X\n", IO_JPG7.JPMODE.bit.S_ENDIAN));
	Ddim_Print(("IO_JPG7.JPMODE.bit.P_ENDIAN      	 =0x%X\n", IO_JPG7.JPMODE.bit.P_ENDIAN));
	Ddim_Print(("IO_JPG7.JPMODE.bit.DISPOSAL       	=0x%X\n", IO_JPG7.JPMODE.bit.DISPOSAL));
	Ddim_Print(("IO_JPG7.JPMODE.bit.MMODE          	=0x%X\n", IO_JPG7.JPMODE.bit.MMODE));
	Ddim_Print(("IO_JPG7.JPFORMAT.bit.CODECNT 		=0x%X\n", IO_JPG7.JPFORMAT.bit.CODECNT));
	Ddim_Print(("IO_JPG7.JPFORMAT.bit.MKSKIP       	=0x%X\n", IO_JPG7.JPFORMAT.bit.MKSKIP));
	Ddim_Print(("IO_JPG7.JPFORMAT.bit.EXIFMOD    	=0x%X\n", IO_JPG7.JPFORMAT.bit.EXIFMOD));
	Ddim_Print(("IO_JPG7.JPWIDTH.bit.JPWIDTH       		=%d\n", IO_JPG7.JPWIDTH.bit.JPWIDTH));
	Ddim_Print(("IO_JPG7.JPHEIGHT.bit.JPHEIGHT     	=%d\n", IO_JPG7.JPHEIGHT.bit.JPHEIGHT));
	Ddim_Print(("IO_JPG7.JMODE.bit.JPBDEXT         		=0x%X\n", IO_JPG7.JMODE.bit.JPBDEXT));
	Ddim_Print(("IO_JPG7.JMODE.bit.JMEMFORM        	=0x%X\n", IO_JPG7.JMODE.bit.JMEMFORM));
	Ddim_Print(("IO_JPG7.JMODE.bit.JPBENDIAN       	=0x%X\n", IO_JPG7.JMODE.bit.JPBENDIAN));
	Ddim_Print(("IO_JPG7.JMODE.bit.JJBENDIAN       	=0x%X\n", IO_JPG7.JMODE.bit.JJBENDIAN));
	Ddim_Print(("IO_JPG7.JPBSTA.bit.JPISSUESET     		=0x%X\n", IO_JPG7.JPBSTA.bit.JPISSUESET));
	Ddim_Print(("IO_JPG7.JPBSTA.bit.JPACACHE       		=0x%X\n", IO_JPG7.JPBSTA.bit.JPACACHE));
	Ddim_Print(("IO_JPG7.JPBSTA.bit.JPAPROT        		=0x%X\n", IO_JPG7.JPBSTA.bit.JPAPROT));
	Ddim_Print(("IO_JPG7.JJBSTA.bit.JJISSUESET     		=0x%X\n", IO_JPG7.JJBSTA.bit.JJISSUESET));
	Ddim_Print(("IO_JPG7.JJBSTA.bit.JJACACHE       		=0x%X\n", IO_JPG7.JJBSTA.bit.JJACACHE));
	Ddim_Print(("IO_JPG7.JJBSTA.bit.JJAPROT        			=0x%X\n", IO_JPG7.JJBSTA.bit.JJAPROT));
	Ddim_Print(("IO_JPG7.JCCTL.bit.JCRP            			=0x%X\n", IO_JPG7.JCCTL.bit.JCRP));
	Ddim_Print(("IO_JPG7.JICTL.bit.JIRP            				=0x%X\n", IO_JPG7.JICTL.bit.JIRP));
	Ddim_Print(("IO_JPG7.JINTEN.bit.JLINEEN        		=0x%X\n", IO_JPG7.JINTEN.bit.JLINEEN));
	Ddim_Print(("IO_JPG7.JLINEVAL.word             			=0x%lX\n", IO_JPG7.JLINEVAL.word));
	Ddim_Print(("IO_JPG7.JINTEN.bit.JSECTEN        		=0x%X\n", IO_JPG7.JINTEN.bit.JSECTEN));
	Ddim_Print(("IO_JPG7.JSECTVAL.word             			=0x%lX\n", IO_JPG7.JSECTVAL.word));
	Ddim_Print(("IO_JPG7.JBANDCOLOR.bit.JBANDY     =0x%X\n", IO_JPG7.JBANDCOLOR.bit.JBANDY));
	Ddim_Print(("IO_JPG7.JBANDCOLOR.bit.JBANDCB	=0x%X\n", IO_JPG7.JBANDCOLOR.bit.JBANDCB));
	Ddim_Print(("IO_JPG7.JBANDCOLOR.bit.JBANDCR  =0x%X\n", IO_JPG7.JBANDCOLOR.bit.JBANDCR));
	Ddim_Print(("\n"));

	Ddim_Print(("IO_JPG7.JICTL.bit.JIXP            		=0x%X\n", IO_JPG7.JICTL.bit.JIXP));
	Ddim_Print(("IO_JPG7.JCCTL.bit.JCC             		=0x%X\n", IO_JPG7.JCCTL.bit.JCC));
	Ddim_Print(("IO_JPG7.JIMGAY.bit.JIMGAY       	=0x%lX\n", IO_JPG7.JIMGAY.bit.JIMGAY));
	Ddim_Print(("IO_JPG7.JIMGACB.bit.JIMGACB 	=0x%lX\n", IO_JPG7.JIMGACB.bit.JIMGACB));
	Ddim_Print(("IO_JPG7.JCODA.bit.JCODA           =0x%lX\n", IO_JPG7.JCODA.bit.JCODA));
	Ddim_Print(("IO_JPG7.JCODSV.word               	=0x%lX\n", IO_JPG7.JCODSV.word));
	Ddim_Print(("\n"));
	ct_im_jpeg1_stop_hclock(priv->jpeg1);

	ret = Im_JPEG_Get_Ctrl_Dec(&outJpegMng);
	Ddim_Print(("Im_JPEG_Get_Ctrl_Dec ret=0x%X\n", ret));

	Ddim_Print(("outJpegMng.skipMkFlg              			=0x%X\n", outJpegMng.skipMkFlg));
	Ddim_Print(("outJpegMng.memFormat               		=0x%X\n", outJpegMng.memFormat));
	Ddim_Print(("outJpegMng.extMode                 			=0x%X\n", outJpegMng.extMode));
	Ddim_Print(("outJpegMng.corrMode                			=0x%X\n", outJpegMng.corrMode));
	Ddim_Print(("outJpegMng.colorBand.yBand        		=0x%X\n", outJpegMng.colorBand.yBand));
	Ddim_Print(("outJpegMng.colorBand.cbBand       	=0x%X\n", outJpegMng.colorBand.cbBand));
	Ddim_Print(("outJpegMng.colorBand.crBand       	=0x%X\n", outJpegMng.colorBand.crBand));
	Ddim_Print(("outJpegMng.pbufCtrl.endian         		=0x%X\n", outJpegMng.pbufCtrl.endian));
	Ddim_Print(("outJpegMng.jbufCtrl.endian         			=0x%X\n", outJpegMng.jbufCtrl.endian));
	Ddim_Print(("outJpegMng.pbufCtrl.issueTranNum 	=0x%X\n", outJpegMng.pbufCtrl.issueTranNum));
	Ddim_Print(("outJpegMng.pbufCtrl.cacheType     		=0x%X\n", outJpegMng.pbufCtrl.cacheType));
	Ddim_Print(("outJpegMng.pbufCtrl.protType      		=0x%X\n", outJpegMng.pbufCtrl.protType));
	Ddim_Print(("outJpegMng.jbufCtrl.issueTranNum 	=0x%X\n", outJpegMng.jbufCtrl.issueTranNum));
	Ddim_Print(("outJpegMng.jbufCtrl.cacheType     		=0x%X\n", outJpegMng.jbufCtrl.cacheType));
	Ddim_Print(("outJpegMng.jbufCtrl.protType      		=0x%X\n", outJpegMng.jbufCtrl.protType));
	Ddim_Print(("outJpegMng.jburstLength            			=0x%X\n", outJpegMng.jburstLength));
	Ddim_Print(("outJpegMng.pburstLength            			=0x%X\n", outJpegMng.pburstLength));
	Ddim_Print(("outJpegMng.pintLine                				=0x%X\n", outJpegMng.pintLine));
	Ddim_Print(("outJpegMng.pintSect                				=0x%lX\n", outJpegMng.pintSect));
	Ddim_Print(("\n"));

	ret = im_jpeg_get_ctrl_dec_frame(&outJpegFrmMng);
	Ddim_Print(("im_jpeg_get_ctrl_dec_frame ret=0x%X\n", ret));

	Ddim_Print(("outJpegFrmMng.yccAddr.y          =0x%lX\n", outJpegFrmMng.yccAddr.y));
	Ddim_Print(("outJpegFrmMng.yccAddr.c          =0x%lX\n", outJpegFrmMng.yccAddr.c));
	Ddim_Print(("outJpegFrmMng.codeAddr           =0x%lX\n", outJpegFrmMng.codeAddr));
#if defined(CO_DEBUG_ON_PC) && defined(__MINGW__)
	Ddim_Print(("outJpegFrmMng.codeSize           =0x%I64X\n", outJpegFrmMng.codeSize));
#else
	Ddim_Print(("outJpegFrmMng.codeSize           =0x%llX\n", outJpegFrmMng.codeSize));
#endif	// CO_DEBUG_ON_PC
	Ddim_Print(("\n"));

	ret = im_jpeg_close();
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_close error ret=0x%X\n", ret));
		return;
	}

	return;
}

void ct_im_jpeg5_1_4_3(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);

	self->sync			= 1;
	self->format		= CtImJpeg6_E_CT_JPEG_FORMAT_444P;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->cutOutFlg	= 0;
	self->cutHSize		= 0;
	self->cutVSize		= 0;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	self->corrFlg		= 0;
	self->pauseFlg		= 0;

	ct_im_jpeg4_decode(priv->jpeg4,self);

	return;
}

void ct_im_jpeg5_1_4_4(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);

	self->sync			= 1;
	self->format		= CtImJpeg6_E_CT_JPEG_FORMAT_422P;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= (gulong)(CtImJpeg5_D_CT_JPEG_TEST_SIZE_H / 2);
	self->hSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->cutOutFlg	= 0;
	self->cutHSize		= 0;
	self->cutVSize		= 0;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	self->corrFlg		= 0;
	self->pauseFlg		= 0;

	ct_im_jpeg4_decode(priv->jpeg4,self);

	return;
}

void ct_im_jpeg5_1_4_5(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);

	self->sync			= 1;
	self->format		= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->cutOutFlg	= 0;
	self->cutHSize		= 0;
	self->cutVSize		= 0;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	self->corrFlg		= 0;
	self->pauseFlg		= 0;

	ct_im_jpeg4_decode(priv->jpeg4,self);

	return;
}

void ct_im_jpeg5_1_4_6(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);

	self->sync			= 0;
	self->format		= CtImJpeg6_E_CT_JPEG_FORMAT_420P;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= (gulong)(CtImJpeg5_D_CT_JPEG_TEST_SIZE_H / 2);
	self->hSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->cutOutFlg	= 0;
	self->cutHSize		= 0;
	self->cutVSize		= 0;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	self->corrFlg		= 0;
	self->pauseFlg		= 0;

	ct_im_jpeg4_decode(priv->jpeg4,self);

	return;
}

void ct_im_jpeg5_1_4_7(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);

	self->sync			= 0;
	self->format		= CtImJpeg6_E_CT_JPEG_FORMAT_420PD;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->cutOutFlg	= 0;
	self->cutHSize		= 0;
	self->cutVSize		= 0;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	self->corrFlg		= 0;
	self->pauseFlg		= 0;

	ct_im_jpeg4_decode(priv->jpeg4,self);

	return;
}

void ct_im_jpeg5_1_4_8(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);

	self->sync			= 1;
	self->format		= CtImJpeg6_E_CT_JPEG_FORMAT_400P;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= 0;
	self->hSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->cutOutFlg	= 0;
	self->cutHSize		= 0;
	self->cutVSize		= 0;
	self->limitSize		= 0;
	self->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	self->corrFlg		= 0;
	self->pauseFlg		= 0;

	ct_im_jpeg4_decode(priv->jpeg4,self);

	return;
}

void ct_im_jpeg5_1_4_9(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);

	self->sync			= 1;
	self->format		= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->cutOutFlg	= 0;
	self->cutHSize		= 0;
	self->cutVSize		= 0;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	self->corrFlg		= 1;
	self->pauseFlg		= 0;

	ct_im_jpeg4_decode(priv->jpeg4,self);

	return;
}

void ct_im_jpeg5_1_4_10(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);

	self->sync			= 1;
	self->format		= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_SIZE_VGA_H;
	self->gYLines		= CtImJpeg5_D_CT_JPEG_SIZE_VGA_V;
	self->gCWidth		= CtImJpeg5_D_CT_JPEG_SIZE_VGA_H;
	self->hSize			= CtImJpeg5_D_CT_JPEG_SIZE_3M_H;
	self->vSize			= CtImJpeg5_D_CT_JPEG_SIZE_3M_V;
	self->cutOutFlg	= 1;
	self->cutHSize		= CtImJpeg5_D_CT_JPEG_SIZE_VGA_H;
	self->cutVSize		= CtImJpeg5_D_CT_JPEG_SIZE_VGA_V;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_SIZE_3M_LIMIT;
	self->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	self->corrFlg		= 0;
	self->pauseFlg		= 0;

	ct_im_jpeg4_decode(priv->jpeg4,self);

	return;
}

void ct_im_jpeg5_1_4_11(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);

	self->sync			= 1;
	self->format		= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->cutOutFlg	= 0;
	self->cutHSize		= 0;
	self->cutVSize		= 0;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_CODE;
	self->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	self->corrFlg		= 0;
	self->pauseFlg		= 1;

	ct_im_jpeg4_decode(priv->jpeg4,self);

	return;
}

void ct_im_jpeg5_1_4_13(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);

	gulong	sectCnt;
	gushort	lineCnt;

	self->sync			= 1;
	self->format		= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->cutOutFlg	= 0;
	self->cutHSize		= 0;
	self->cutVSize		= 0;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	self->corrFlg		= 0;
	self->pauseFlg		= 0;

	ct_im_jpeg4_decode(priv->jpeg4,self);

	lineCnt = im_jpeg_get_line_cnt();
	Ddim_Print(("im_jpeg_get_line_cnt ret=0x%X\n", lineCnt));

	sectCnt = im_jpeg_get_sect_cnt();
	Ddim_Print(("im_jpeg_get_sect_cnt ret=0x%lX\n", sectCnt));

	return;
}

void ct_im_jpeg5_2_3_1(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);

	self->sync			= 1;
	self->format		= CtImJpeg6_E_CT_JPEG_FORMAT_420PD;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->cutOutFlg	= 0;
	self->cutHSize		= 0;
	self->cutVSize		= 0;
	// Input jpeg file compression ratio 200% are supposed.
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H * CtImJpeg5_D_CT_JPEG_TEST_SIZE_V * 2;
	self->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	self->corrFlg		= 0;
	self->pauseFlg		= 0;

	ct_im_jpeg4_decode(priv->jpeg4,self);

	return;
}

void ct_im_jpeg5_2_3_2(CtImJpeg5 *self)
{
	CtImJpeg5Private *priv = CT_IM_JPEG_5_GET_PRIVATE(self);

	self->sync			= 1;
	self->format		= CtImJpeg6_E_CT_JPEG_FORMAT_420PD;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_SIZE_3M_H;
	self->gYLines		= CtImJpeg5_D_CT_JPEG_SIZE_3M_V;
	self->gCWidth		= CtImJpeg5_D_CT_JPEG_SIZE_3M_H;
	self->hSize			= CtImJpeg5_D_CT_JPEG_SIZE_3M_H;
	self->vSize			= CtImJpeg5_D_CT_JPEG_SIZE_3M_V;
	self->cutOutFlg	= 1;
	self->cutHSize		= CtImJpeg5_D_CT_JPEG_SIZE_VGA_H;
	self->cutVSize		= CtImJpeg5_D_CT_JPEG_SIZE_VGA_V;
	// Input jpeg file compression ratio 200% are supposed.
	self->limitSize	= CtImJpeg5_D_CT_JPEG_SIZE_3M_H * CtImJpeg5_D_CT_JPEG_SIZE_3M_V * 2;
	self->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	self->corrFlg		= 0;
	self->pauseFlg	= 0;

	ct_im_jpeg4_decode(priv->jpeg4,self);

	return;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImJpeg5类的一个实例
 */
CtImJpeg5* ct_im_jpeg5_new()
{
	CtImJpeg5 *self = g_object_new(CT_TYPE_IM_JPEG_5,NULL);
	return self;
}
