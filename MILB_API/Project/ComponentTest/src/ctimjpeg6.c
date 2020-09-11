/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImJpeg6类
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
#include "ctimjpeg6.h"

G_DEFINE_TYPE(CtImJpeg6, ct_im_jpeg6, G_TYPE_OBJECT);

#define CT_IM_JPEG_6_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_JPEG_6, CtImJpeg6Private))

struct _CtImJpeg6Private
{
	CtImJpeg1 *jpeg1;
};
/*
 *DECLS
 * */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static void 	ctJpegEncodeForceStop(CtImJpeg6* self);

static void ct_im_jpeg6_class_init(CtImJpeg6Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImJpeg6Private));
}

static void ct_im_jpeg6_init(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);
	priv->jpeg1	=ct_im_jpeg1_new();
}
/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
	CtImJpeg6 *self = (CtImJpeg6*)object;
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg6_parent_class)->dispose(object);
	if(priv->jpeg1)
	{
		g_object_unref(priv->jpeg1);
		priv->jpeg1=NULL;
	}
}

static void finalize_od(GObject *object)
{
//	CtImJpeg6 *self = (CtImJpeg6*)object;
//	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg6_parent_class)->finalize(object);
}

static void ctJpegEncodeForceStop(CtImJpeg6* self)
{
	TImJpegEncMng encMng;
	TImJpegEncFrameMng encFrmMng;
	gint32 ret = 0;
	EImJpegAxiSt	bufStatus;

	memset(&encMng, 0, sizeof(TImJpegEncMng));
	memset(&encFrmMng, 0, sizeof(TImJpegEncFrameMng));

	// Base
	switch(self->format) {
		case CtImJpeg6_E_CT_JPEG_FORMAT_444P:
		case CtImJpeg6_E_CT_JPEG_FORMAT_RGBP:
			encMng.yccSmpl			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC444;
			encMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE;
			break;
		case CtImJpeg6_E_CT_JPEG_FORMAT_422P:
			encMng.yccSmpl			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;
			encMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE;
			break;
		case CtImJpeg6_E_CT_JPEG_FORMAT_422PD:
			encMng.yccSmpl			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;
			encMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE_DOT;
			break;
		case CtImJpeg6_E_CT_JPEG_FORMAT_420P:
			encMng.yccSmpl			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420;
			encMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE;
			break;
		case CtImJpeg6_E_CT_JPEG_FORMAT_420PD:
			encMng.yccSmpl			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420;
			encMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE_DOT;
			break;
		case CtImJpeg6_E_CT_JPEG_FORMAT_400P:
			encMng.yccSmpl			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400;
			encMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE;
			break;
		default:
			Ddim_Print(("input parameter error\n"));
			return;
	}

	encMng.width = self->hSize;
	encMng.lines = self->vSize;

	encMng.component[0].quantTblNo  = 0;	// Y
	encMng.component[0].hufDcTblNo = 0;	// Y
	encMng.component[0].hufAcTblNo = 0;	// Y
	encMng.component[1].quantTblNo  = 1;	// CB
	encMng.component[1].hufDcTblNo = 1;	// CB
	encMng.component[1].hufAcTblNo = 1;	// CB
	encMng.component[2].quantTblNo  = 1;	// CR
	encMng.component[2].hufDcTblNo = 1;	// CR
	encMng.component[2].hufAcTblNo = 1;	// CR

	encMng.skipMkFlg = ImJpegCommon_D_IM_JPEG_ENABLE_OFF;

	if (self->dri) {
		encMng.driMkNum = 0x10;
	}
	else {
		encMng.driMkNum = 0;
	}

	encMng.exifFmtFlg						= ImJpegCommon_D_IM_JPEG_ENABLE_ON;
	encMng.pintLine							= 0;
	encMng.pintSect							= 0;
	encMng.pbufCtrl.endian				= ImJpegCommon_E_IM_JPEG_ENDIAN_LITTLE;
	encMng.pbufCtrl.issueTranNum= ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
	encMng.pbufCtrl.cacheType		= ImJpegCommon_D_IM_JPEG_NON_CACHE_NON_BUF;
	encMng.pbufCtrl.protType			= ImJpegCommon_D_IM_JPEG_D_SEC_NORMAL_ACCESS;
	encMng.jbufCtrl.endian				= ImJpegCommon_E_IM_JPEG_ENDIAN_LITTLE;
	encMng.jbufCtrl.issueTranNum	= ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
	encMng.jbufCtrl.cacheType			= ImJpegCommon_D_IM_JPEG_NON_CACHE_NON_BUF;
	encMng.jbufCtrl.protType			= ImJpegCommon_D_IM_JPEG_D_SEC_NORMAL_ACCESS;
	encMng.jburstLength					= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
	encMng.pburstLength					= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;

	if (self->sync) {
		encMng.pcallback = NULL;
	}
	else {
		encMng.pcallback = (VP_CALLBACK)ct_im_jpeg1_encode_cb;
	}

	// Frame
	encFrmMng.globalYWidth = self->gYWidth;
	encFrmMng.globalCWidth = self->gCWidth;

	// Y addr
	encFrmMng.yccAddr.y = CtImJpeg5_D_CT_JPEG_YCC_ADDR;

	if (encMng.yccSmpl != ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400) {

		// Cb addr
		encFrmMng.yccAddr.c = CtImJpeg5_D_CT_JPEG_YCC_ADDR + (self->gYWidth * self->gYLines);
	}

	// Code addr
	encFrmMng.codeAddr		= CtImJpeg5_D_CT_JPEG_CODE_ADDR;
	encFrmMng.codeCountFlg	= self->countFlg;

	ret = Im_JPEG_Open(D_DDIM_WAIT_END_TIME);
	Ddim_Print(("Im_JPEG_Open ret=0x%X\n", ret));
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		return;
	}

	Im_JPEG_Set_Quality(1024, 0);

	ret = Im_JPEG_Ctrl_Enc(&encMng);
	Ddim_Print(("Im_JPEG_Ctrl_Enc ret=0x%X\n", ret));
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Im_JPEG_Close();
		return;
	}

	// limit size
	encFrmMng.limitSize		= self->limitSize;

	ret = Im_JPEG_Ctrl_Enc_Frame(&encFrmMng);
	Ddim_Print(("Im_JPEG_Ctrl_Enc_Frame ret=0x%X\n", ret));
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Im_JPEG_Close();
		return;
	}

	Ddim_Print(("Im_JPEG_Start_Enc\n"));
	ret = Im_JPEG_Start_Enc();
	Ddim_Print(("Im_JPEG_Start_Enc ret=0x%X\n", ret));
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Im_JPEG_Close();
		return;
	}

	while(1) {
		Im_JPEG_Get_Axi_State(&bufStatus);
		if (bufStatus == ImJpegCommon_E_IM_JPEG_AXI_ST_ACTIVE_BOTH) {
			break;
		}
#ifdef CO_DEBUG_ON_PC
		IO_JPG7.JSTATE.bit.JALLACTP = 1;
		IO_JPG7.JSTATE.bit.JJBACTP = 1;
		IO_JPG7.JSTATE.bit.JPBACTP = 1;
#endif	// CO_DEBUG_ON_PC
	}

	// Force stop
	ct_im_jpeg1_stop();

	Im_JPEG_Get_Axi_State(&bufStatus);
	Ddim_Print(("Im_JPEG_Get_Axi_State status=0x%X\n", bufStatus));

	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	ct_im_jpeg1_start_hclock(priv->jpeg1);
	Ddim_Print(("IO_JPG7.JPSTATUS.bit.JPSTATUS=0x%X\n", IO_JPG7.JPSTATUS.bit.JPSTATUS));
	ct_im_jpeg1_stop_hclock(priv->jpeg1);

	ret = Im_JPEG_Close();
	Ddim_Print(("Im_JPEG_Close ret=0x%X\n", ret));
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		return;
	}

	return;
}
/*
 *PUBLIC
 * */

void ct_im_jpeg6_1_3_5(CtImJpeg6 *self)
{
	TImJpegEncMng jpegMng;
	gushort retRatio;
	gint32 ret;

	jpegMng.yccSmpl			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;
	jpegMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE_DOT;
	jpegMng.width				= 4608;
	jpegMng.lines					= 3456;
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
	jpegMng.pbufCtrl.cacheType	= 0;
	jpegMng.pbufCtrl.protType		= 0;
	jpegMng.jbufCtrl.endian			= ImJpegCommon_E_IM_JPEG_ENDIAN_LITTLE;
	jpegMng.jbufCtrl.issueTranNum	= ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
	jpegMng.jbufCtrl.cacheType= 0;
	jpegMng.jbufCtrl.protType	= 0;
	jpegMng.jburstLength			= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
	jpegMng.pburstLength			= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
	jpegMng.codeSize					= 0;
	jpegMng.result						= 0;
	jpegMng.pcallback 				= (VP_CALLBACK)ct_im_jpeg1_encode_cb;

	ret = Im_JPEG_Open(D_DDIM_WAIT_END_TIME);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("Im_JPEG_Open error ret=0x%X\n", ret));
		return;
	}

	Im_JPEG_Ctrl_Enc(&jpegMng);

	retRatio = Im_JPEG_Set_Down_Sampling_Rate(ImJpegCommon_D_IM_JPEG_DOWNSP_1_2);
	Ddim_Print(("Im_JPEG_Set_Down_Sampling_Rate=0x%X\n", retRatio));

	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

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

	return;
}

void ct_im_jpeg6_1_3_6(CtImJpeg6 *self)
{
	TImJpegEncMng jpegMng;
	gushort retRatio;
	gint32 ret;

	jpegMng.yccSmpl			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;
	jpegMng.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE;
	jpegMng.width				= 4616;
	jpegMng.lines					= 3464;
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
	jpegMng.codeSize								= 0;
	jpegMng.result									= 0;
	jpegMng.pcallback								= (VP_CALLBACK)ct_im_jpeg4_decode_cb;

	ret = Im_JPEG_Open(D_DDIM_WAIT_END_TIME);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("Im_JPEG_Open error ret=0x%X\n", ret));
		return;
	}

	Im_JPEG_Ctrl_Enc(&jpegMng);

	retRatio = Im_JPEG_Set_Down_Sampling_Rate(ImJpegCommon_D_IM_JPEG_DOWNSP_1_2);
	Ddim_Print(("Im_JPEG_Set_Down_Sampling_Rate=0x%X\n", retRatio));

	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

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

	return;
}

void ct_im_jpeg6_1_3_7(CtImJpeg6 *self)
{
	TImJpegEncMng inJpegMng;
	TImJpegEncMng outJpegMng;
	TImJpegEncFrameMng inJpegFrmMng;
	TImJpegEncFrameMng outJpegFrmMng;
	gint32 ret;

	memset(&inJpegMng, 0, sizeof(TImJpegEncMng));
	memset(&outJpegMng, 0, sizeof(TImJpegEncMng));
	memset(&inJpegFrmMng, 0, sizeof(TImJpegEncFrameMng));
	memset(&outJpegFrmMng, 0, sizeof(TImJpegEncFrameMng));

	inJpegMng.yccSmpl					=ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400;
	inJpegMng.memFormat			=ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE_DOT;
	inJpegMng.width						=0xFFFF;
	inJpegMng.lines							=0xFFFF;
	inJpegMng.component[0].quantTblNo	=0;
	inJpegMng.component[0].hufDcTblNo	=0;
	inJpegMng.component[0].hufAcTblNo	=0;
	inJpegMng.component[1].quantTblNo	=1;
	inJpegMng.component[1].hufDcTblNo	=1;
	inJpegMng.component[1].hufAcTblNo	=1;
	inJpegMng.component[2].quantTblNo	=2;
	inJpegMng.component[2].hufDcTblNo	=0;
	inJpegMng.component[2].hufAcTblNo	=1;
	inJpegMng.skipMkFlg				=ImJpegCommon_D_IM_JPEG_ENABLE_ON;
	inJpegMng.driMkNum				=0xFFFF;
	inJpegMng.exifFmtFlg				=ImJpegCommon_D_IM_JPEG_ENABLE_ON;
	inJpegMng.pintLine					=0xFFFF;
	inJpegMng.pintSect					=0xFFFFFFFF;
	inJpegMng.pbufCtrl.endian		=ImJpegCommon_E_IM_JPEG_ENDIAN_BIG;
	inJpegMng.pbufCtrl.issueTranNum	=ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
	inJpegMng.pbufCtrl.cacheType			=ImJpegCommon_D_IM_JPEG_ON_CACHE_RW_WRITE_BACK;
	inJpegMng.pbufCtrl.protType				=ImJpegCommon_D_IM_JPEG_I_NSEC_PRIVILEGED_ACCESS;
	inJpegMng.jbufCtrl.endian					=ImJpegCommon_E_IM_JPEG_ENDIAN_BIG;
	inJpegMng.jbufCtrl.issueTranNum		=ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
	inJpegMng.jbufCtrl.cacheType			=ImJpegCommon_D_IM_JPEG_ON_CACHE_RW_WRITE_BACK;
	inJpegMng.jbufCtrl.protType				=ImJpegCommon_D_IM_JPEG_I_NSEC_PRIVILEGED_ACCESS;
	inJpegMng.jburstLength						=ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
	inJpegMng.pburstLength						=ImJpegCommon_E_IM_JPEG_BURST_INCR_16;
	inJpegMng.codeSize								=0;
	inJpegMng.result									=0;
	inJpegMng.pcallback								=NULL;

	inJpegFrmMng.globalYWidth	= 0xFFFFF;
	inJpegFrmMng.globalCWidth	= 0xFFFFF;
	inJpegFrmMng.yccAddr.y			= 0xFFFFFFFF;
	inJpegFrmMng.yccAddr.c			= 0xFFFFFFFF;
	inJpegFrmMng.codeAddr			= 0xFFFFFFFF;
	inJpegFrmMng.codeCountFlg	= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	inJpegFrmMng.limitSize			= 0x1FFFFFFFC00;

	ret = Im_JPEG_Open(D_DDIM_WAIT_END_TIME);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("Im_JPEG_Open error ret=0x%X\n", ret));
		return;
	}

	ret = Im_JPEG_Ctrl_Enc(&inJpegMng);
	Ddim_Print(("Im_JPEG_Ctrl_Enc ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = Im_JPEG_Ctrl_Enc_Frame(&inJpegFrmMng);
	Ddim_Print(("Im_JPEG_Ctrl_Enc_Frame ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	ct_im_jpeg1_start_hclock(priv->jpeg1);
	Ddim_Print(("IO_JPG7.JPMODE.bit.S_ENDIAN    =0x%X\n", IO_JPG7.JPMODE.bit.S_ENDIAN));
	Ddim_Print(("IO_JPG7.JPMODE.bit.P_ENDIAN    =0x%X\n", IO_JPG7.JPMODE.bit.P_ENDIAN));
	Ddim_Print(("IO_JPG7.JPMODE.bit.DISPOSAL    =0x%X\n", IO_JPG7.JPMODE.bit.DISPOSAL));
	Ddim_Print(("IO_JPG7.JPMODE.bit.MMODE       =0x%X\n", IO_JPG7.JPMODE.bit.MMODE));
	Ddim_Print(("IO_JPG7.JPQTABLE.bit.QT0L      =0x%X\n", IO_JPG7.JPQTABLE.bit.QT0L));
	Ddim_Print(("IO_JPG7.JPQTABLE.bit.QT0U      =0x%X\n", IO_JPG7.JPQTABLE.bit.QT0U));
	Ddim_Print(("IO_JPG7.JPQTABLE.bit.QT1L      =0x%X\n", IO_JPG7.JPQTABLE.bit.QT1L));
	Ddim_Print(("IO_JPG7.JPQTABLE.bit.QT1U      =0x%X\n", IO_JPG7.JPQTABLE.bit.QT1U));
	Ddim_Print(("IO_JPG7.JPQTABLE.bit.QT2L      =0x%X\n", IO_JPG7.JPQTABLE.bit.QT2L));
	Ddim_Print(("IO_JPG7.JPQTABLE.bit.QT2U      =0x%X\n", IO_JPG7.JPQTABLE.bit.QT2U));
	Ddim_Print(("IO_JPG7.JPHTABLE.bit.HT0DC     =0x%X\n", IO_JPG7.JPHTABLE.bit.HT0DC));
	Ddim_Print(("IO_JPG7.JPHTABLE.bit.HT0AC     =0x%X\n", IO_JPG7.JPHTABLE.bit.HT0AC));
	Ddim_Print(("IO_JPG7.JPHTABLE.bit.HT1DC     =0x%X\n", IO_JPG7.JPHTABLE.bit.HT1DC));
	Ddim_Print(("IO_JPG7.JPHTABLE.bit.HT1AC     =0x%X\n", IO_JPG7.JPHTABLE.bit.HT1AC));
	Ddim_Print(("IO_JPG7.JPHTABLE.bit.HT2DC     =0x%X\n", IO_JPG7.JPHTABLE.bit.HT2DC));
	Ddim_Print(("IO_JPG7.JPHTABLE.bit.HT2AC     =0x%X\n", IO_JPG7.JPHTABLE.bit.HT2AC));
	Ddim_Print(("IO_JPG7.JPDRISET.word          =0x%lX\n", IO_JPG7.JPDRISET.word));
	Ddim_Print(("IO_JPG7.JPWIDTH.word           =0x%lX\n", IO_JPG7.JPWIDTH.word));
	Ddim_Print(("IO_JPG7.JPHEIGHT.word          =0x%lX\n", IO_JPG7.JPHEIGHT.word));
	Ddim_Print(("IO_JPG7.JPFORMAT.bit.CODECNT   =0x%X\n", IO_JPG7.JPFORMAT.bit.CODECNT));
	Ddim_Print(("IO_JPG7.JPFORMAT.bit.MKSKIP    =0x%X\n", IO_JPG7.JPFORMAT.bit.MKSKIP));
	Ddim_Print(("IO_JPG7.JPFORMAT.bit.EXIFMOD   =0x%X\n", IO_JPG7.JPFORMAT.bit.EXIFMOD));
	Ddim_Print(("IO_JPG7.JMODE.bit.JCSCCCEN     =0x%X\n", IO_JPG7.JMODE.bit.JCSCCCEN));
	Ddim_Print(("IO_JPG7.JMODE.bit.JPBDEXT      =0x%X\n", IO_JPG7.JMODE.bit.JPBDEXT));
	Ddim_Print(("IO_JPG7.JMODE.bit.JMEMFORM     =0x%X\n", IO_JPG7.JMODE.bit.JMEMFORM));
	Ddim_Print(("IO_JPG7.JMODE.bit.JPBENDIAN    =0x%X\n", IO_JPG7.JMODE.bit.JPBENDIAN));
	Ddim_Print(("IO_JPG7.JMODE.bit.JJBENDIAN    =0x%X\n", IO_JPG7.JMODE.bit.JJBENDIAN));
	Ddim_Print(("IO_JPG7.JPBSTA.bit.JPISSUESET  =0x%X\n", IO_JPG7.JPBSTA.bit.JPISSUESET));
	Ddim_Print(("IO_JPG7.JPBSTA.bit.JPACACHE    =0x%X\n", IO_JPG7.JPBSTA.bit.JPACACHE));
	Ddim_Print(("IO_JPG7.JPBSTA.bit.JPAPROT     =0x%X\n", IO_JPG7.JPBSTA.bit.JPAPROT));
	Ddim_Print(("IO_JPG7.JJBSTA.bit.JJISSUESET  =0x%X\n", IO_JPG7.JJBSTA.bit.JJISSUESET));
	Ddim_Print(("IO_JPG7.JJBSTA.bit.JJACACHE    =0x%X\n", IO_JPG7.JJBSTA.bit.JJACACHE));
	Ddim_Print(("IO_JPG7.JJBSTA.bit.JJAPROT     =0x%X\n", IO_JPG7.JJBSTA.bit.JJAPROT));
	Ddim_Print(("IO_JPG7.JCCTL.bit.JCRP         =0x%X\n", IO_JPG7.JCCTL.bit.JCRP));
	Ddim_Print(("IO_JPG7.JICTL.bit.JIRP         =0x%X\n", IO_JPG7.JICTL.bit.JIRP));
	Ddim_Print(("IO_JPG7.JINTEN.bit.JLINEEN     =0x%X\n", IO_JPG7.JINTEN.bit.JLINEEN));
	Ddim_Print(("IO_JPG7.JLINEVAL.word          =0x%lX\n", IO_JPG7.JLINEVAL.word));
	Ddim_Print(("IO_JPG7.JINTEN.bit.JSECTEN     =0x%X\n", IO_JPG7.JINTEN.bit.JSECTEN));
	Ddim_Print(("IO_JPG7.JSECTVAL.word          =0x%lX\n", IO_JPG7.JSECTVAL.word));
	Ddim_Print(("\n"));

	Ddim_Print(("IO_JPG7.JIMGYGH.bit.JIMGYGH    =0x%X\n", IO_JPG7.JIMGYGH.bit.JIMGYGH));
	Ddim_Print(("IO_JPG7.JIMGCGH.bit.JIMGCGH    =0x%X\n", IO_JPG7.JIMGCGH.bit.JIMGCGH));
	Ddim_Print(("IO_JPG7.JIMGSH.bit.JIMGSH      =0x%X\n", IO_JPG7.JIMGSH.bit.JIMGSH));
	Ddim_Print(("IO_JPG7.JIMGSV.bit.JIMGSV      =0x%X\n", IO_JPG7.JIMGSV.bit.JIMGSV));
	Ddim_Print(("IO_JPG7.JIMGAY.bit.JIMGAY      =0x%lX\n", IO_JPG7.JIMGAY.bit.JIMGAY));
	Ddim_Print(("IO_JPG7.JIMGACB.bit.JIMGACB    =0x%lX\n", IO_JPG7.JIMGACB.bit.JIMGACB));
	Ddim_Print(("IO_JPG7.JCCTL.bit.JCC          =0x%X\n", IO_JPG7.JCCTL.bit.JCC));
	Ddim_Print(("IO_JPG7.JCODA.bit.JCODA        =0x%lX\n", IO_JPG7.JCODA.bit.JCODA));
	Ddim_Print(("IO_JPG7.JCODSV                 =0x%lX\n", IO_JPG7.JCODSV.word));
	Ddim_Print(("\n"));
	ct_im_jpeg1_stop_hclock(priv->jpeg1);

	ret = Im_JPEG_Get_Ctrl_Enc(&outJpegMng);
	Ddim_Print(("Im_JPEG_Get_Ctrl_Enc ret=0x%X\n", ret));

	Ddim_Print(("outJpegMng.yccSmpl=0x%X\n", outJpegMng.yccSmpl));
	Ddim_Print(("outJpegMng.component[0].quantTblNo   =0x%X\n", outJpegMng.component[0].quantTblNo));
	Ddim_Print(("outJpegMng.component[1].quantTblNo   =0x%X\n", outJpegMng.component[1].quantTblNo));
	Ddim_Print(("outJpegMng.component[2].quantTblNo   =0x%X\n", outJpegMng.component[2].quantTblNo));
	Ddim_Print(("outJpegMng.component[0].hufDcTblNo  =0x%X\n", outJpegMng.component[0].hufDcTblNo));
	Ddim_Print(("outJpegMng.component[0].hufAcTblNo  =0x%X\n", outJpegMng.component[0].hufAcTblNo));
	Ddim_Print(("outJpegMng.component[1].hufDcTblNo  =0x%X\n", outJpegMng.component[1].hufDcTblNo));
	Ddim_Print(("outJpegMng.component[1].hufAcTblNo  =0x%X\n", outJpegMng.component[1].hufAcTblNo));
	Ddim_Print(("outJpegMng.component[2].hufDcTblNo  =0x%X\n", outJpegMng.component[2].hufDcTblNo));
	Ddim_Print(("outJpegMng.component[2].hufAcTblNo  =0x%X\n", outJpegMng.component[2].hufAcTblNo));
	Ddim_Print(("outJpegMng.driMkNum                  		=0x%X\n", outJpegMng.driMkNum));
	Ddim_Print(("outJpegMng.width                       			=0x%X\n", outJpegMng.width));
	Ddim_Print(("outJpegMng.lines                      		 		=0x%X\n", outJpegMng.lines));
	Ddim_Print(("outJpegMng.skipMkFlg                 		=0x%X\n", outJpegMng.skipMkFlg));
	Ddim_Print(("outJpegMng.exifFmtFlg                			=0x%X\n", outJpegMng.exifFmtFlg));
	Ddim_Print(("outJpegMng.memFormat                  		=0x%X\n", outJpegMng.memFormat));
	Ddim_Print(("outJpegMng.pbufCtrl.endian            		=0x%X\n", outJpegMng.pbufCtrl.endian));
	Ddim_Print(("outJpegMng.jbufCtrl.endian            		=0x%X\n", outJpegMng.jbufCtrl.endian));
	Ddim_Print(("outJpegMng.pbufCtrl.issueTranNum 	=0x%X\n", outJpegMng.pbufCtrl.issueTranNum));
	Ddim_Print(("outJpegMng.pbufCtrl.cacheType        	=0x%X\n", outJpegMng.pbufCtrl.cacheType));
	Ddim_Print(("outJpegMng.pbufCtrl.protType         	=0x%X\n", outJpegMng.pbufCtrl.protType));
	Ddim_Print(("outJpegMng.jbufCtrl.issueTranNum    =0x%X\n", outJpegMng.jbufCtrl.issueTranNum));
	Ddim_Print(("outJpegMng.jbufCtrl.cacheType        	=0x%X\n", outJpegMng.jbufCtrl.cacheType));
	Ddim_Print(("outJpegMng.jbufCtrl.protType         		=0x%X\n", outJpegMng.jbufCtrl.protType));
	Ddim_Print(("outJpegMng.jburstLength               		=0x%X\n", outJpegMng.jburstLength));
	Ddim_Print(("outJpegMng.pburstLength              	 	=0x%X\n", outJpegMng.pburstLength));
	Ddim_Print(("outJpegMng.bitDepth                   			=0x%X\n", outJpegMng.bitDepth));
	Ddim_Print(("outJpegMng.pintLine                   			=0x%X\n", outJpegMng.pintLine));
	Ddim_Print(("outJpegMng.pintSect                   			=0x%lX\n", outJpegMng.pintSect));
	Ddim_Print(("\n"));

	ret = Im_JPEG_Get_Ctrl_Enc_Frame(&outJpegFrmMng);
	Ddim_Print(("Im_JPEG_Get_Ctrl_Enc_Frame ret=0x%X\n", ret));

	Ddim_Print(("outJpegFrmMng.globalYWidth     =0x%lX\n", outJpegFrmMng.globalYWidth));
	Ddim_Print(("outJpegFrmMng.globalCWidth     =0x%lX\n", outJpegFrmMng.globalCWidth));
	Ddim_Print(("outJpegFrmMng.yccAddr.y           	=0x%lX\n", outJpegFrmMng.yccAddr.y));
	Ddim_Print(("outJpegFrmMng.yccAddr.c          	=0x%lX\n", outJpegFrmMng.yccAddr.c));
	Ddim_Print(("outJpegFrmMng.codeCountFlg   	=0x%X\n", outJpegFrmMng.codeCountFlg));
	Ddim_Print(("outJpegFrmMng.codeAddr            =0x%lX\n", outJpegFrmMng.codeAddr));
#if defined(CO_DEBUG_ON_PC) && defined(__MINGW32__)
	Ddim_Print(("outJpegFrmMng.limitSize              =%I64X\n", outJpegFrmMng.limitSize));
#else
	Ddim_Print(("outJpegFrmMng.limitSize              =%llX\n", outJpegFrmMng.limitSize));
#endif	// CO_DEBUG_ON_PC
	Ddim_Print(("\n"));

	ret = Im_JPEG_Close();
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("Im_JPEG_Close error ret=0x%X\n", ret));
		return;
	}

	return;
}

void ct_im_jpeg6_1_3_8(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_444P;
	self->gYWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg			= 0;
	self->countFlg			= 0;
	self->quantupFlg	= 0;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_9(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_422P;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= (gulong)(CtImJpeg5_D_CT_JPEG_TEST_SIZE_H / 2);
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg		= 0;
	self->countFlg		= 0;
	self->quantupFlg	= 0;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_10(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg		= 0;
	self->countFlg		= 0;
	self->quantupFlg	= 0;
	self->skipMkFlg	= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_11(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_422P;
	self->gYWidth		= (gulong)((CtImJpeg5_D_CT_JPEG_TEST_SIZE_H << 1) << 4);
	self->gYLines			= 0;
	self->gCWidth		= 0;
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg		= 0;
	self->countFlg		= 0;
	self->quantupFlg	= 0;
	self->skipMkFlg	= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_12(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_420P;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= (gulong)(CtImJpeg5_D_CT_JPEG_TEST_SIZE_H / 2);
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg		= 0;
	self->countFlg		= 0;
	self->quantupFlg	= 0;
	self->skipMkFlg	= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_13(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 0;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_420PD;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg		= 0;
	self->countFlg		= 0;
	self->quantupFlg	= 0;
	self->skipMkFlg	= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_14(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 0;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_400P;
	self->gYWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth			= 0;
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg			= 0;
	self->countFlg			= 0;
	self->quantupFlg	= 0;
	self->skipMkFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_15(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_RGBP;
	self->gYWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize		= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg		= 0;
	self->countFlg		= 0;
	self->quantupFlg	= 0;
	self->skipMkFlg	= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_16(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
	self->gYWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg			= 0;
	self->countFlg			= 0;
	self->quantupFlg	= 0;
	self->skipMkFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 0;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_17(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_420PD;
	self->gYWidth			= CtImJpeg5_D_CT_JPEG_SIZE_3M_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_SIZE_3M_V;
	self->gCWidth			= CtImJpeg5_D_CT_JPEG_SIZE_3M_H;
	self->hSize				= CtImJpeg5_D_CT_JPEG_SIZE_VGA_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_SIZE_VGA_V;
	self->limitSize			= CtImJpeg6_D_CT_JPEG_SIZE_VGA_LIMIT;
	self->pauseFlg			= 0;
	self->countFlg			= 0;
	self->quantupFlg	= 0;
	self->skipMkFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 0;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_18(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
	self->gYWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg			= 0;
	self->countFlg			= 0;
	self->quantupFlg	= 1;
	self->skipMkFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_19(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
	self->gYWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg			= 0;
	self->countFlg			= 1;
	self->quantupFlg	= 0;
	self->skipMkFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_1_2;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_20(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
	self->gYWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize			= CtImJpeg5_D_CT_JPEG_TEST_CODE;
	self->pauseFlg			= 1;
	self->countFlg			= 0;
	self->quantupFlg	= 0;
	self->skipMkFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	return;
}

void ct_im_jpeg6_1_3_21(CtImJpeg6 *self)
{
	CtImJpeg6Private *priv = CT_IM_JPEG_6_GET_PRIVATE(self);

	gulong	sectCnt;
	gushort	lineCnt;

	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
	self->gYWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg			= 0;
	self->countFlg			= 0;
	self->quantupFlg	= 0;
	self->skipMkFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ct_im_jpeg1_encode(priv->jpeg1,self, 1);

	lineCnt = Im_JPEG_Get_Line_Cnt();
	Ddim_Print(("Im_JPEG_Get_Line_Cnt ret=0x%X\n", lineCnt));

	sectCnt = Im_JPEG_Get_Sect_Cnt();
	Ddim_Print(("Im_JPEG_Get_Sect_Cnt ret=0x%lX\n", sectCnt));

	return;
}

void ct_im_jpeg6_1_5_1(CtImJpeg6 *self)
{
	self->sync				= 1;
	self->format			= CtImJpeg6_E_CT_JPEG_FORMAT_422PD;
	self->gYWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->gYLines			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->gCWidth			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->hSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_H;
	self->vSize				= CtImJpeg5_D_CT_JPEG_TEST_SIZE_V;
	self->limitSize			= CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT;
	self->pauseFlg			= 0;
	self->countFlg			= 0;
	self->quantupFlg	= 0;
	self->skipMkFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	self->dri					= 1;
	self->dspRate			= ImJpegCommon_D_IM_JPEG_DOWNSP_NONE;

	ctJpegEncodeForceStop(self);

	return;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImJpeg6类的一个实例
 */
CtImJpeg6* ct_im_jpeg6_new()
{
	CtImJpeg6 *self = g_object_new(CT_TYPE_IM_JPEG_6,NULL);
	return self;
}
