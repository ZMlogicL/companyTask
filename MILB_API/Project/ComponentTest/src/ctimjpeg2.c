/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImJpeg2类
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
#include "ctimjpeg4.h"
#include "ctimjpeg2.h"

G_DEFINE_TYPE(CtImJpeg2, ct_im_jpeg2, G_TYPE_OBJECT);

#define CT_IM_JPEG_2_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_JPEG_2, CtImJpeg2Private))

#ifdef CO_ACT_CLOCK
#define CtImJpeg2_CO_ACT_JPEG_CLOCK
#endif //CO_ACT_CLOCK
#ifdef CO_ACT_HCLOCK
#define CtImJpeg2_CO_ACT_JPEG_HCLOCK
#endif //CO_ACT_HCLOCK
#ifdef CO_ACT_ICLOCK
#define CtImJpeg2_CO_ACT_JPEG_ICLOCK
#endif //CO_ACT_ICLOCK

#if 1	// Clock control force ON.
#ifndef CO_ACT_CLOCK
#define CtImJpeg2_CO_ACT_JPEG_CLOCK
#endif //CO_ACT_CLOCK
#ifndef CO_ACT_HCLOCK
#define CtImJpeg2_CO_ACT_JPEG_HCLOCK
#endif //CO_ACT_HCLOCK
#ifndef CO_ACT_ICLOCK
#define CtImJpeg2_CO_ACT_JPEG_ICLOCK
#endif //CO_ACT_ICLOCK
#endif

struct _CtImJpeg2Private
{
	CtImJpeg1 *jpeg1;
	CtImJpeg3 *jpeg3;
	CtImJpeg4 *jpeg4;
};

#ifdef CtImJpeg2_CO_ACT_JPEG_CLOCK
static guchar S_GCT_IM_JPG_CLK_CTRL_CNT= 0;
#endif
#ifdef CtImJpeg2_CO_ACT_JPEG_ICLOCK
static guchar S_GCT_IM_JPG_ICLK_CTRL_CNT = 0;
#endif
/*
 *DECLS
 * */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static void 	ctJpegDecodeMkSkip(CtImJpeg2 *self,CtImJpeg5* decParam);

static void ct_im_jpeg2_class_init(CtImJpeg2Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImJpeg2Private));
}

static void ct_im_jpeg2_init(CtImJpeg2 *self)
{
	CtImJpeg2Private *priv = CT_IM_JPEG_2_GET_PRIVATE(self);
	priv->jpeg1=ct_im_jpeg1_new();
	priv->jpeg3=ct_im_jpeg3_new();
	priv->jpeg4=ct_im_jpeg4_new();
}

/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
//	CtImJpeg2 *self = (CtImJpeg2*)object;
//	CtImJpeg2Private *priv = CT_IM_JPEG_2_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg2_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	CtImJpeg2 *self = (CtImJpeg2*)object;
	CtImJpeg2Private *priv = CT_IM_JPEG_2_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg2_parent_class)->finalize(object);

	if(priv->jpeg1)
	{
		g_object_unref(priv->jpeg1);
		priv->jpeg1=NULL;
	}
	if(priv->jpeg3)
		{
			g_object_unref(priv->jpeg3);
			priv->jpeg3=NULL;
		}
	if(priv->jpeg4)
		{
			g_object_unref(priv->jpeg4);
			priv->jpeg4=NULL;
		}
}

static void ctJpegDecodeMkSkip(CtImJpeg2 *self,CtImJpeg5* decParam)
{
	CtImJpeg2Private *priv = CT_IM_JPEG_2_GET_PRIVATE(self);
	TImJpegDecMng decMng;
	TImJpegDecFrameMng decFrmMng;
	gint32	ret=0;
	gint32	i;

	memset(&decMng, 0, sizeof(TImJpegDecMng));
	memset(&decFrmMng, 0, sizeof(TImJpegDecFrameMng));

	switch(decParam->format) {
		case CtImJpeg6_E_CT_JPEG_FORMAT_444P:
		case CtImJpeg6_E_CT_JPEG_FORMAT_RGBP:
			decMng.smplType			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC444;
			decMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE;
			break;
		case CtImJpeg6_E_CT_JPEG_FORMAT_422P:
			decMng.smplType			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;
			decMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE;
			break;
		case CtImJpeg6_E_CT_JPEG_FORMAT_422PD:
			decMng.smplType			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;
			decMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE_DOT;
			break;
		case CtImJpeg6_E_CT_JPEG_FORMAT_420P:
			decMng.smplType			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420;
			decMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE;
			break;
		case CtImJpeg6_E_CT_JPEG_FORMAT_420PD:
			decMng.smplType			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420;
			decMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE_DOT;
			break;
		case CtImJpeg6_E_CT_JPEG_FORMAT_400P:
			decMng.smplType			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400;
			decMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE;
			break;
		default:
			Ddim_Print(("input parameter error\n"));
			return;
	}

	decMng.ext_mode 		= decParam->ext;
	decMng.skipMkFlg	= 0;
	decMng.pintLine		= 0;
	decMng.pintSect		= 0;
	decMng.corr_mode	= decParam->corrFlg;

	decMng.color_band.y_band		= 0x01;
	decMng.color_band.cb_band	= 0x01;
	decMng.color_band.cr_band		= 0x01;

	decMng.pbufCtrl.endian					= ImJpegCommon_E_IM_JPEG_ENDIAN_LITTLE;
	decMng.pbufCtrl.issueTranNum	= ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
	decMng.pbufCtrl.cacheType			= ImJpegCommon_D_IM_JPEG_NON_CACHE_NON_BUF;
	decMng.pbufCtrl.protType				= ImJpegCommon_D_IM_JPEG_D_SEC_NORMAL_ACCESS;
	decMng.jbufCtrl.endian					= ImJpegCommon_E_IM_JPEG_ENDIAN_LITTLE;
	decMng.jbufCtrl.issueTranNum		= ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
	decMng.jbufCtrl.cacheType				= ImJpegCommon_D_IM_JPEG_NON_CACHE_NON_BUF;
	decMng.jbufCtrl.protType				= ImJpegCommon_D_IM_JPEG_D_SEC_NORMAL_ACCESS;
	decMng.jburstLength						= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
	decMng.pburstLength						= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;

	if (decParam->sync) {
		decMng.pcallback = NULL;
	}
	else {
		decMng.pcallback = (VP_CALLBACK)ct_im_jpeg4_decode_cb;
	}

	// Frame memory
	// Y
	decFrmMng.globalYWidth = decParam->gYWidth;

	if (decParam->cutOutFlg) {
		decFrmMng.cutout_flg		= ImJpegCommon_D_IM_JPEG_ENABLE_ON;
		decFrmMng.cutout_width	= decParam->cutHSize;
		decFrmMng.cutout_lines	= decParam->cutVSize;
		decFrmMng.cutout_offset_h = ((decParam->hSize - decParam->cutHSize) / 2);
		decFrmMng.cutout_offset_v = ((decParam->vSize - decParam->cutVSize) / 2);

		if ((decFrmMng.cutout_offset_h & 0xF) != 0) {
			decFrmMng.cutout_offset_h = ((decFrmMng.cutout_offset_h >> 4) << 4) + 16;
		}
		if ((decFrmMng.cutout_offset_v & 0xF) != 0) {
			decFrmMng.cutout_offset_v = ((decFrmMng.cutout_offset_v >> 4) << 4) + 16;
		}

		if(ct_im_jpeg1_get4(priv->jpeg1)) {
			decFrmMng.yccAddr.y		= CtImJpeg2_D_CT_JPEG_YCC_ADDR_ERR;
		}
		else {
			decFrmMng.yccAddr.y		= CtImJpeg5_D_CT_JPEG_YCC_ADDR;
		}

		// CbCr
		decFrmMng.globalCWidth = decParam->gCWidth;
		decFrmMng.yccAddr.c	= CtImJpeg5_D_CT_JPEG_YCC_ADDR + (decParam->gYWidth * decParam->gYLines);
	}
	else {
		decFrmMng.cutout_flg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
		decFrmMng.cutout_width	= 0;
		decFrmMng.cutout_lines	= 0;
		decFrmMng.cutout_offset_h	= 0;
		decFrmMng.cutout_offset_v	= 0;

		if(ct_im_jpeg1_get4(priv->jpeg1)) {
			decFrmMng.yccAddr.y		= CtImJpeg2_D_CT_JPEG_YCC_ADDR_ERR;
		}
		else {
			decFrmMng.yccAddr.y		= CtImJpeg5_D_CT_JPEG_YCC_ADDR;
		}

		// CbCr
		decFrmMng.globalCWidth = decParam->gCWidth;
		decFrmMng.yccAddr.c	= CtImJpeg5_D_CT_JPEG_YCC_ADDR + (decParam->gYWidth * decParam->gYLines);
	}
	decFrmMng.codeAddr = CtImJpeg5_D_CT_JPEG_CODE_ADDR;

//	ct_im_jpeg1_measure_time_start();

	ret = Im_JPEG_Open(D_DDIM_WAIT_END_TIME);
	Ddim_Print(("Im_JPEG_Open ret=0x%X\n", ret));
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		return;
	}

	for(i=0; i < 10; i++) {
		if (i == 0) {
			ret = Im_JPEG_Ctrl_Dec(&decMng);
			Ddim_Print(("Im_JPEG_Ctrl_Dec ret=0x%X\n", ret));
			ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_DEC_BASE, (gpointer)&decMng);
		}
		else {
			ret = Im_JPEG_Set_Skip_Marker_Dec();
			// target address change
			decFrmMng.codeAddr = CtImJpeg2_D_CT_JPEG_CODE_ADDR2;
		}
		if (ret != ImJpegCommon_D_IM_JPEG_OK) {
			Im_JPEG_Close();
			return;
		}

		// limit size
		decFrmMng.codeSize		= decParam->limitSize;
		ret = Im_JPEG_Ctrl_Dec_Frame(&decFrmMng);
		Ddim_Print(("Im_JPEG_Ctrl_Dec_Frame ret=0x%X\n", ret));
		// Ctrl Print
		ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_DEC_FRAME, (gpointer)&decFrmMng);
		if (ret != ImJpegCommon_D_IM_JPEG_OK) {
			Im_JPEG_Close();
			return;
		}

		if (i == 0) {
			ret = Im_JPEG_Start_Dec();
			Ddim_Print(("Im_JPEG_Start_Dec ret=0x%X\n", ret));
		}
		else {
			ret = Im_JPEG_Start_Skip_Marker_Dec();
			Ddim_Print(("Im_JPEG_Start_Skip_Marker_Dec ret=0x%X\n", ret));
#if 0	// error root
			ret = Im_JPEG_Start_Skip_Marker_Dec();
			Ddim_Print(("Im_JPEG_Start_Skip_Marker_Dec ret=0x%X\n", ret));
#endif
		}
		if (ret != ImJpegCommon_D_IM_JPEG_OK) {
			ct_im_jpeg1_stop();
			Im_JPEG_Close();
			return;
		}
		ret = Im_JPEG_Wait_End_Dec(&decMng, 5000);
		Ddim_Print(("Im_JPEG_Wait_End_Dec ret=0x%X\n", ret));

		memcpy(ct_im_jpeg4_get1(priv->jpeg4), &decMng, sizeof(TImJpegDecMng));

		if (ret != ImJpegCommon_D_IM_JPEG_OK) {
			ct_im_jpeg1_stop();
			Im_JPEG_Close();
			Ddim_Print(("***** Decode Error result=[0x%X] *****\n", ct_im_jpeg4_get1(priv->jpeg4)->result));
			Ddim_Print(("***** Decode Error Code=[0x%X] *****\n", ct_im_jpeg4_get1(priv->jpeg4)->errCode));
			Ddim_Print(("***** Decode Sampling type[%d] *****\n", ct_im_jpeg4_get1(priv->jpeg4)->smplType));
			return;
		}
//		ct_im_jpeg1_measure_time_print();
		Ddim_Print(("***** Decode result=[0x%X] *****\n", ct_im_jpeg4_get1(priv->jpeg4)->result));
		Ddim_Print(("***** Decode Sampling type[%d] *****\n", ct_im_jpeg4_get1(priv->jpeg4)->smplType));
		Ddim_Print(("***** Decode Width[%d], Height[%d] *****\n",
				ct_im_jpeg4_get1(priv->jpeg4)->orgWidth, ct_im_jpeg4_get1(priv->jpeg4)->orgLines));
	}

	ret = Im_JPEG_Close();
	Ddim_Print(("Im_JPEG_Close ret=0x%X\n", ret));
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		return;
	}

	ct_im_jpeg2_set_ycc_out_bytes(self,decMng.smplType, decMng.memFormat, decFrmMng.globalYWidth,
				decFrmMng.globalCWidth, ct_im_jpeg4_get1(priv->jpeg4)->orgLines);
}
/*
 *PUBLIC
 * */
void ct_im_jpeg2_set_ycc_out_bytes(CtImJpeg2 *self,const EImJpegSmplType smplType,
			const EImJpegMemForm memFormat,
			const gulong globalYWidth, const gulong globalCWidth, const gulong lines)
{
	CtImJpeg2Private *priv = CT_IM_JPEG_2_GET_PRIVATE(self);
	gulong outDataSizY;
	gulong outDataSizC;

	// Calc Y bytes.
	outDataSizY = globalYWidth * lines;

	switch(smplType) {
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC444:	// FALLTHROUGH
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422:
			outDataSizC = globalCWidth * lines;
			break;
//		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420:
		default:
			outDataSizC = globalCWidth * (lines /2);
			break;
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400:
			outDataSizC = 0ul;
	}
	if(memFormat == ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE) {
		outDataSizC *= 2;
	}

	ct_im_jpeg1_set3(priv->jpeg1,outDataSizY + outDataSizC);
}

/**
 * @brief  Command main function for JPEG test.
 * @param  gint32 argc	:The number of parameters
 *		   CGAR** argv	:The value of parameters
 * @return void
 */
void ct_im_jpeg2_main(CtImJpeg2 *self,gint32 argc, gchar** argv)
{
	CtImJpeg2Private *priv = CT_IM_JPEG_2_GET_PRIVATE(self);
	ct_im_jpeg3_set1(priv->jpeg3,priv->jpeg1);
	gint32	ctParam1 = 0;
	gint32	ctParam2 = 0;
	gint32	ctParam3 = 0;
	gint32	ctParam4 = 0;
	gint32	ctParam5 = 0;
	gint32	ctParam6 = 0;

	if (argc > 8) {
		Ddim_Print(("input parameter error. argc=%d\n", argc));
		return;
	}

	if(argc >= 2) {
		ctParam1 = atoi((const gchar *)argv[1]);
	}
	if(argc >= 3) {
		ctParam2 = atoi((const gchar *)argv[2]);
	}
	if(argc >= 4) {
		ctParam3 = atoi((const gchar *)argv[3]);
	}
	if(argc >= 5) {
		ctParam4 = atoi((const gchar *)argv[4]);
	}

	ct_im_jpeg1_set4(priv->jpeg1,0);
	ct_im_jpeg1_set3(priv->jpeg1,0);

	if (ctParam1 == 1) {
		ct_Im_jpeg3_run1(priv->jpeg3,ctParam2, ctParam3);
	}
	else if (ctParam1 == 2) {
		ct_im_jpeg4_run2(priv->jpeg4,ctParam2, ctParam3);
	}
	else if (ctParam1 == 3) {
	// Encode
		CtImJpeg6 *encParam=ct_im_jpeg6_new();

		encParam->sync				= 1;
		encParam->gYWidth		= ctParam3;
		encParam->gYLines		= ctParam4;
		encParam->hSize			= ctParam3;
		encParam->vSize			= ctParam4;
		// AXI_Err happen
		ct_im_jpeg1_set4(priv->jpeg1,atoi((const gchar *)argv[5]));
		// Quality value use or Qtable set
		ctParam5	 			= atoi((const gchar *)argv[6]);
		// skip marker mode use
		ctParam6	 			= atoi((const gchar *)argv[7]);

		if (ctParam2 == 0) {
			encParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_444P;
			encParam->gCWidth	= (gulong)ctParam3;
		}
		else if(ctParam2 == 1) {
			encParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_422P;
			encParam->gCWidth	= (gulong)(ctParam3 >> 1);
		}
		else if(ctParam2 == 2) {
			encParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
			encParam->gCWidth	= (gulong)ctParam3;
		}
		else if(ctParam2 == 3) {
			encParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_420P;
			encParam->gCWidth	= (gulong)(ctParam3 >> 1);
		}
		else if(ctParam2 == 4) {
			encParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_420PD;
			encParam->gCWidth	= (gulong)ctParam3;
		}
		else if(ctParam2 == 5) {
			encParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_400P;
			encParam->gCWidth	= 0;
		}
		else {
			Ddim_Print(("input parameter error. argc=%d\n", argc));

			if(encParam){
				g_object_unref(encParam);
				encParam=NULL;
			}

			return;
		}

		encParam->limitSize		= 0;
		encParam->pauseFlg		= 0;
		encParam->countFlg		= 0;
		encParam->quantupFlg	= 0;
		encParam->dri				= 0;
		encParam->dspRate		= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;
		encParam->skipMkFlg	= ctParam6;

		Im_JPEG_Init();

		ct_im_jpeg1_encode(priv->jpeg1,encParam, ctParam5);

		if(encParam){
			g_object_unref(encParam);
			encParam=NULL;
		}
	}
	else if (ctParam1 == 4) {
	// Decode
		CtImJpeg5 *decParam=ct_im_jpeg5_new();

//		memset((void *)0x49000000 ,0, 0x10000000);

//		Im_JPEG_Init();

		decParam->sync				= 1;
		decParam->gYWidth		= ctParam3;
		decParam->gYLines		= ctParam4;
		decParam->hSize			= ctParam3;
		decParam->vSize			= ctParam4;
		// AXI_Err happen
		ct_im_jpeg1_set4(priv->jpeg1,atoi((const gchar *)argv[5]));
		// skip marker mode use
		ctParam5				= atoi((const gchar *)argv[6]);

		if (ctParam2 == 0) {
			decParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_444P;
			decParam->gCWidth	= (gulong)ctParam3;
		}
		else if(ctParam2 == 1) {
			decParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_422P;
			decParam->gCWidth	= (gulong)(ctParam3 >> 1);
		}
		else if(ctParam2 == 2) {
			decParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
			decParam->gCWidth	= (gulong)ctParam3;
		}
		else if(ctParam2 == 3) {
			decParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_420P;
			decParam->gCWidth	= (gulong)(ctParam3 >> 1);
		}
		else if(ctParam2 == 4) {
			decParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_420PD;
			decParam->gCWidth	= (gulong)ctParam3;
		}
		else if(ctParam2 == 5) {
			decParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_400P;
			decParam->gCWidth	= 0;
		}
		else {
			Ddim_Print(("input parameter error. argc=%d\n", argc));

			if(decParam){
				g_object_unref(decParam);
				decParam=NULL;
			}

			return;
		}

		decParam->cutOutFlg	= 0;
		decParam->cutHSize		= 0;
		decParam->cutVSize		= 0;
		decParam->limitSize		= 0;
		decParam->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
		decParam->corrFlg			= 1;
		decParam->pauseFlg		= 0;

		if (ctParam5 > 0) {
		// marker skip mode test
			ctJpegDecodeMkSkip(self,decParam);
		}
		else {
		// normal test
			ct_im_jpeg4_decode(priv->jpeg4,decParam);
		}

		if(decParam){
			g_object_unref(decParam);
			decParam=NULL;
		}
	}
	else if (ctParam1 == 5) {
	// cont Decode
		CtImJpeg5 *decParam=ct_im_jpeg5_new();
		gint32 i;
		gint32 cntMax = 1;

		decParam->sync				= 1;
		decParam->gYWidth		= ctParam3;
		decParam->gYLines		= ctParam4;
		decParam->hSize			= ctParam3;
		decParam->vSize			= ctParam4;
		ct_im_jpeg1_set4(priv->jpeg1,atoi((const gchar *)argv[5]));
		cntMax = atoi((const gchar *)argv[6]);

		if (ctParam2 == 0) {
			decParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_444P;
			decParam->gCWidth	= (gulong)ctParam3;
		}
		else if(ctParam2 == 1) {
			decParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_422P;
			decParam->gCWidth	= (gulong)(ctParam3 >> 1);
		}
		else if(ctParam2 == 2) {
			decParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
			decParam->gCWidth	= (gulong)ctParam3;
		}
		else if(ctParam2 == 3) {
			decParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_420P;
			decParam->gCWidth	= (gulong)(ctParam3 >> 1);
		}
		else if(ctParam2 == 4) {
			decParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_420PD;
			decParam->gCWidth	= (gulong)ctParam3;
		}
		else if(ctParam2 == 5) {
			decParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_400P;
			decParam->gCWidth	= 0;
		}
		else {
			Ddim_Print(("input parameter error. argc=%d\n", argc));

			if(decParam){
				g_object_unref(decParam);
				decParam=NULL;
			}

			return;
		}

		decParam->cutOutFlg	= 0;
		decParam->cutHSize		= 0;
		decParam->cutVSize		= 0;
		decParam->limitSize		= 0;
		decParam->ext				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_BAND;
		decParam->corrFlg			= 1;
		decParam->pauseFlg		= 0;

		for(i=0; i < cntMax; i++) {
//			Im_JPEG_Init();
			ct_im_jpeg4_decode(priv->jpeg4,decParam);
		}

		if(decParam){
			g_object_unref(decParam);
			decParam=NULL;
		}
	}
	else if (ctParam1 == 6) {

		TImJpegEncMng jpegMng;
		gushort retRatio;
		gint32 ret;
		UINT32 dsp;

		if (ctParam2 == 0) {
			jpegMng.yccSmpl	= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420;
		}
		else if(ctParam2 == 1) {
			jpegMng.yccSmpl	= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;
		}
		else if(ctParam2 == 2) {
			jpegMng.yccSmpl	= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC444;
		}
		else if(ctParam2 == 3) {
			jpegMng.yccSmpl	= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400;
		}
		else {
			Ddim_Print(("input parameter error. argc=%d\n", argc));
			return;
		}

		if (ctParam3 == 0) {
			jpegMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE;
		}
		else if(ctParam3 == 1) {
			jpegMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE_DOT;
		}
		else {
			Ddim_Print(("input parameter error. argc=%d\n", argc));
			return;
		}

		if (ctParam4 == 0) {
			dsp	= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;
		}
		else if(ctParam4 == 1) {
			dsp	= ImJpegCommon_D_IM_JPEG_DOWNSP_1_2;
		}
		else if(ctParam4 == 2) {
			dsp	= ImJpegCommon_D_IM_JPEG_DOWNSP_1_4;
		}
		else if(ctParam4 == 3) {
			dsp	= ImJpegCommon_D_IM_JPEG_DOWNSP_1_8;
		}
		else {
			Ddim_Print(("input parameter error. argc=%d\n", argc));
			return;
		}

		jpegMng.width						= 0xFFFF;
		jpegMng.lines							= 0xFFFF;
		jpegMng.component[0].quantTblNo	= 0;
		jpegMng.component[0].hufDcTblNo	= 0;
		jpegMng.component[0].hufAcTblNo	= 0;
		jpegMng.component[1].quantTblNo	= 1;
		jpegMng.component[1].hufDcTblNo	= 1;
		jpegMng.component[1].hufAcTblNo	= 1;
		jpegMng.component[2].quantTblNo	= 2;
		jpegMng.component[2].hufDcTblNo	= 1;
		jpegMng.component[2].hufAcTblNo	= 1;
		jpegMng.skipMkFlg				= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
		jpegMng.driMkNum			= 8;
		jpegMng.exifFmtFlg				= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
		jpegMng.pintLine					= 0;
		jpegMng.pintSect					= 0;
		jpegMng.pbufCtrl.endian		= ImJpegCommon_E_IM_JPEG_ENDIAN_LITTLE;
		jpegMng.pbufCtrl.issueTranNum	= ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
		jpegMng.pbufCtrl.cacheType			= 0;
		jpegMng.pbufCtrl.protType				= 0;
		jpegMng.jbufCtrl.endian					= ImJpegCommon_E_IM_JPEG_ENDIAN_LITTLE;
		jpegMng.jbufCtrl.issueTranNum	= ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
		jpegMng.jbufCtrl.cacheType			= 0;
		jpegMng.jbufCtrl.protType				= 0;
		jpegMng.jburstLength						= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
		jpegMng.pburstLength						= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
		jpegMng.bitDepth								= ImJpegCommon_E_IM_JPEG_BIT_DEPTH_8BIT;
		jpegMng.codeSize								= 0;
		jpegMng.result									= 0;
		jpegMng.pcallback 							= (VP_CALLBACK)ct_im_jpeg1_encode_cb;

		ret = Im_JPEG_Open(D_DDIM_WAIT_END_TIME);
		if (ret != ImJpegCommon_D_IM_JPEG_OK) {
			Ddim_Print(("Im_JPEG_Open error ret=0x%X\n", ret));
			return;
		}

		Im_JPEG_Ctrl_Enc(&jpegMng);

		retRatio = Im_JPEG_Set_Down_Sampling_Rate(dsp);
		Ddim_Print(("Im_JPEG_Set_Down_Sampling_Rate=0x%X\n", retRatio));

		ct_im_jpeg1_start_hclock(priv->jpeg1);
		Ddim_Print(("IO_JPG7.JICTL.bit.JIXP=0x%X\n", IO_JPG7.JICTL.bit.JIXP));
		Ddim_Print(("IO_JPG7.JIMGSH.bit.JIMGSH=%d\n", IO_JPG7.JIMGSH.bit.JIMGSH));
		Ddim_Print(("IO_JPG7.JPWIDTH.bit.JPWIDTH=%d\n", IO_JPG7.JPWIDTH.bit.JPWIDTH));
		Ddim_Print(("IO_JPG7.JIMGSV.bit.JIMGSV=%d\n", IO_JPG7.JIMGSV.bit.JIMGSV));
		Ddim_Print(("IO_JPG7.JPHEIGHT.bit.JPHEIGHT=%d\n", IO_JPG7.JPHEIGHT.bit.JPHEIGHT));
		ct_im_jpeg1_stop_hclock(priv->jpeg1);

		ret = Im_JPEG_Close();
		if (ret != ImJpegCommon_D_IM_JPEG_OK) {
			Ddim_Print(("Im_JPEG_Close error ret=0x%X\n", ret));
			return;
		}
	}
	else if (ctParam1 == 7) {
	// Encode
		CtImJpeg6 *encParam=ct_im_jpeg6_new();
		gint32	i;

		encParam->sync				= 1;
		encParam->gYWidth		= ctParam3;
		encParam->gYLines		= ctParam4;
		encParam->hSize			= ctParam3;
		encParam->vSize			= ctParam4;
		// AXI_Err happen
		ct_im_jpeg1_set4(priv->jpeg1,atoi((const gchar *)argv[5]));
		// Quality value use or Qtable set
		ctParam5	 			= atoi((const gchar *)argv[6]);
		// skip marker mode use
		ctParam6	 			= atoi((const gchar *)argv[7]);

		if (ctParam2 == 0) {
			encParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_444P;
			encParam->gCWidth	= (gulong)ctParam3;
		}
		else if(ctParam2 == 1) {
			encParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_422P;
			encParam->gCWidth	= (gulong)(ctParam3 >> 1);
		}
		else if(ctParam2 == 2) {
			encParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
			encParam->gCWidth	= (gulong)ctParam3;
		}
		else if(ctParam2 == 3) {
			encParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_420P;
			encParam->gCWidth	= (gulong)(ctParam3 >> 1);
		}
		else if(ctParam2 == 4) {
			encParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_420PD;
			encParam->gCWidth	= (gulong)ctParam3;
		}
		else if(ctParam2 == 5) {
			encParam->format	= CtImJpeg6_E_CT_JPEG_FORMAT_400P;
			encParam->gCWidth	= 0;
		}
		else {
			Ddim_Print(("input parameter error. argc=%d\n", argc));

			if(encParam){
				g_object_unref(encParam);
				encParam=NULL;
			}

			return;
		}

		encParam->limitSize			= 0;
		encParam->pauseFlg			= 0;
		encParam->countFlg			= 0;
		encParam->quantupFlg		= 0;
		encParam->dri					= 0;
		encParam->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;
		encParam->skipMkFlg		= ctParam6;

		Im_JPEG_Init();

		for (i=0; i<1000; i++) {
			ct_im_jpeg1_encode(priv->jpeg1,encParam, ctParam5);
		}

		if(encParam){
			g_object_unref(encParam);
			encParam=NULL;
		}
	}
	else if (ctParam1 == 8) {
		ct_Im_jpeg3_run1(priv->jpeg3,1, 1);
		ct_Im_jpeg3_run1(priv->jpeg3,2, 1);
		ct_Im_jpeg3_run1(priv->jpeg3,2, 2);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 1);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 2);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 3);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 4);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 5);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 6);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 7);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 8);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 9);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 10);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 11);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 12);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 13);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 14);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 15);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 16);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 17);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 18);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 19);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 20);
		ct_Im_jpeg3_run1(priv->jpeg3,3, 21);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 1);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 2);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 3);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 4);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 5);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 6);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 7);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 8);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 9);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 10);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 11);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 12);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 13);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 14);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 15);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 16);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 17);
		ct_Im_jpeg3_run1(priv->jpeg3,4, 18);
		ct_Im_jpeg3_run1(priv->jpeg3,5, 1);
		ct_Im_jpeg3_run1(priv->jpeg3,5, 2);

		// Special Encode for HIIRE
		ct_Im_jpeg3_run1(priv->jpeg3,6, 1);

		ct_im_jpeg4_run2(priv->jpeg4,1, 1);
		ct_im_jpeg4_run2(priv->jpeg4,2, 1);
		ct_im_jpeg4_run2(priv->jpeg4,3, 1);
		ct_im_jpeg4_run2(priv->jpeg4,3, 2);
		ct_im_jpeg4_run2(priv->jpeg4,4, 1);	// Int_Handler PC check
		ct_im_jpeg4_run2(priv->jpeg4,4, 2);	// Int_Handler PC check
		ct_im_jpeg4_run2(priv->jpeg4,4, 3);	// Int_Handler PC check
		ct_im_jpeg4_run2(priv->jpeg4,4, 4);	// Int_Handler PC check
		ct_im_jpeg4_run2(priv->jpeg4,4, 5);	// Int_Handler PC check
		ct_im_jpeg4_run2(priv->jpeg4,4, 6);	// Int_Handler PC check
		ct_im_jpeg4_run2(priv->jpeg4,4, 7);	// Int_Handler PC check
		ct_im_jpeg4_run2(priv->jpeg4,4, 8);	// Int_Handler PC check
		ct_im_jpeg4_run2(priv->jpeg4,4, 9);	// Int_Handler PC check
		ct_im_jpeg4_run2(priv->jpeg4,4, 10);	// Int_Handler PC check
		ct_im_jpeg4_run2(priv->jpeg4,4, 11);	// Int_Handler PC check
		ct_im_jpeg4_run2(priv->jpeg4,4, 12);	// Int_Handler PC check
		ct_im_jpeg4_run2(priv->jpeg4,4, 13);	// Int_Handler PC check
	}
	else {
		Ddim_Print(("input parameter error\n"));
	}

#ifdef CtImJpeg2_CO_ACT_JPEG_CLOCK
	if (S_GCT_IM_JPG_CLK_CTRL_CNT != 0) {
		Ddim_Print(("Jpeg clock Error S_GCT_IM_JPG_CLK_CTRL_CNT=%d\n", S_GCT_IM_JPG_CLK_CTRL_CNT));
	}
	else {
		Ddim_Print(("Jpeg clock OK\n"));
	}
#endif

#ifdef CtImJpeg2_CO_ACT_JPEG_HCLOCK
	if (ct_im_jpeg1_get1(priv->jpeg1) != 0) {
		Ddim_Print(("Jpeg Hclock Error ct_im_jpeg1_get1(priv->jpeg1)=%d\n",ct_im_jpeg1_get1(priv->jpeg1)));
	}
	else {
		Ddim_Print(("Jpeg Hclock OK\n"));
	}
#endif

#ifdef CtImJpeg2_CO_ACT_JPEG_ICLOCK
	if (S_GCT_IM_JPG_ICLK_CTRL_CNT != 0) {
		Ddim_Print(("Jpeg Iclock Error S_GCT_IM_JPG_ICLK_CTRL_CNT=%d\n", S_GCT_IM_JPG_ICLK_CTRL_CNT));
	}
	else {
		Ddim_Print(("Jpeg Iclock OK\n"));
	}
#endif

	return;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImJpeg2类的一个实例
 */
CtImJpeg2* ct_im_jpeg2_new()
{
	CtImJpeg2 *self = g_object_new(CT_TYPE_IM_JPEG_2,NULL);
//	CtImJpeg2Private *priv = CT_IM_JPEG_2_GET_PRIVATE(self);
	return self;
}
