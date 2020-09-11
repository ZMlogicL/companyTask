/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImJpeg3类
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
#include "ctimjpeg4.h"
#include "ctimjpeg5.h"
#include "ctimjpeg6.h"
#include "ctimjpeg3.h"

G_DEFINE_TYPE(CtImJpeg3, ct_im_jpeg3, G_TYPE_OBJECT);

#define CT_IM_JPEG_3_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_JPEG_3, CtImJpeg3Private))

struct _CtImJpeg3Private {
	CtImJpeg 	*jpeg;
	CtImJpeg1 	*jpeg1;
	CtImJpeg5 	*jpeg5;
	CtImJpeg6 	*jpeg6;
};
// PBUF(AXI) controll.
static const TImJpegAxiCtrl CtImJpeg3_GCT_IM_JPEG_PBUF_CTRL = {
		.endian = ImJpegCommon_E_IM_JPEG_ENDIAN_LITTLE,
		.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8,
		.cacheType = ImJpegCommon_D_IM_JPEG_NON_CACHE_NON_BUF,
		.protType = ImJpegCommon_D_IM_JPEG_D_SEC_NORMAL_ACCESS,
		.err_state = 0,
};
// JBUF(AXI) controll.
static const TImJpegAxiCtrl CtImJpeg3_GCT_IM_JPEG_JBUF_CTRL = {
		.endian = ImJpegCommon_E_IM_JPEG_ENDIAN_LITTLE,
		.issueTranNum = ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8,
		.cacheType = ImJpegCommon_D_IM_JPEG_NON_CACHE_NON_BUF,
		.protType = ImJpegCommon_D_IM_JPEG_D_SEC_NORMAL_ACCESS,
		.err_state = 0,
};
/*
 *DECLS
 * */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static void 	ct_im_jpeg111(void);
static void 	ct_im_jpeg121(void);
static void 	ct_im_jpeg122(void);
static void 	ct_im_jpeg152(void);

static void ct_im_jpeg3_class_init(CtImJpeg3Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImJpeg3Private));
}

static void ct_im_jpeg3_init(CtImJpeg3 *self)
{
	CtImJpeg3Private *priv = CT_IM_JPEG_3_GET_PRIVATE(self);
	priv->jpeg1=NULL;
	priv->jpeg=ct_im_jpeg_new();
	priv->jpeg5=ct_im_jpeg5_new();
	priv->jpeg6=ct_im_jpeg6_new();
}

/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
//	CtImJpeg3 *self = (CtImJpeg3*)object;
//	CtImJpeg3Private *priv = CT_IM_JPEG_3_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg3_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	CtImJpeg3 *self = (CtImJpeg3*)object;
	CtImJpeg3Private *priv = CT_IM_JPEG_3_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg3_parent_class)->finalize(object);

	if(priv->jpeg)
	{
		g_object_unref(priv->jpeg);
		priv->jpeg=NULL;
	}
	if(priv->jpeg5)
	{
		g_object_unref(priv->jpeg5);
		priv->jpeg5=NULL;
	}
	if(priv->jpeg6)
	{
		g_object_unref(priv->jpeg6);
		priv->jpeg6=NULL;
	}
}

static void ct_im_jpeg111(void)
{
#ifdef CO_DEBUG_ON_PC
	IO_JPG7.JSTATE.bit.JALLRSTP = 1;
#endif	// CO_DEBUG_ON_PC

	Im_JPEG_Init();

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("IO_JPG7.JPCMD.bit.JRESET=%d\n", IO_JPG7.JPCMD.bit.JRESET));
#endif	// CO_DEBUG_ON_PC
	return;
}

static void ct_im_jpeg121(void)
{
	gint32 ret;
	ret = Im_JPEG_Open(D_DDIM_WAIT_END_TIME);
	Ddim_Print(("Im_JPEG_Open ret=0x%X\n", ret));
	return;
}

static void ct_im_jpeg122(void)
{
	gint32 ret;

	ret = Im_JPEG_Open(D_DDIM_WAIT_END_TIME);
	Ddim_Print(("Im_JPEG_Open ret=0x%X\n", ret));

	ret = Im_JPEG_Close();
	Ddim_Print(("Im_JPEG_Close ret=0x%X\n", ret));

	return;
}

static void ct_im_jpeg152(void)
{
	gint32 ret;
	EImJpegAxiSt status;

	ret = Im_JPEG_Open(D_DDIM_WAIT_END_TIME);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("Im_JPEG_Open error ret=0x%X\n", ret));
		return;
	}

#ifdef CO_DEBUG_ON_PC
	IO_JPG7.JSTATE.bit.JALLACTP = 1;
	IO_JPG7.JSTATE.bit.JPBACTP = 1;
#endif	// CO_DEBUG_ON_PC

	ret = Im_JPEG_Get_Axi_State(&status);
	Ddim_Print(("Im_JPEG_Get_Axi_State ret=0x%X\n", ret));
	Ddim_Print(("status=0x%X\n", status));

	CtImJpeg1 *self1=ct_im_jpeg1_new();

	ct_im_jpeg1_start_hclock(self1);
	Ddim_Print(("IO_JPG7.JPSTATUS.bit.JPSTATUS=0x%X\n", IO_JPG7.JPSTATUS.bit.JPSTATUS));
	ct_im_jpeg1_stop_hclock(self1);

	ret = Im_JPEG_Close();
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("Im_JPEG_Close error ret=0x%X\n", ret));
		return;
	}

	return;
}
/*
 *PUBLIC
 * */
void ct_Im_jpeg3_run1(CtImJpeg3 *self,gint32 ctParam1, gint32 ctParam2)
{
	CtImJpeg3Private *priv = CT_IM_JPEG_3_GET_PRIVATE(self);
#ifdef CO_DEBUG_ON_PC
	memset((kushort*)&IO_JPG7, 0, sizeof(IO_JPG7));
#endif	// CO_DEBUG_ON_PC

	if (ctParam1 != 1 && ctParam1 != 6) {

#ifdef CO_DEBUG_ON_PC
		IO_JPG7.JSTATE.bit.JALLRSTP = 0;
#endif	// CO_DEBUG_ON_PC

		Ddim_Print(("*** Jpeg begin Im_Jpeg_Init\n"));
		Im_JPEG_Init();
		Ddim_Print(("*** Jpeg end Im_Jpeg_Init\n"));
	}

	switch (ctParam1) {
		case 1:
			if (ctParam2 == 1) {
				Ddim_Print(("TEST 1_1_1 Start\n"));
				ct_im_jpeg111();
				Ddim_Print(("TEST 1_1_1 End\n"));
			}
			else {
				Ddim_Print(("input parameter error\n"));
			}
			break;
		case 2:
			if (ctParam2 == 1) {
				Ddim_Print(("TEST 1_2_1 Start\n"));
				ct_im_jpeg121();
				Ddim_Print(("TEST 1_2_1 End\n"));
			}
			else if (ctParam2 == 2) {
				Ddim_Print(("TEST 1_2_2 Start\n"));
				ct_im_jpeg122();
				Ddim_Print(("TEST 1_2_2 End\n"));
			}
			else {
				Ddim_Print(("input parameter error\n"));
			}
			break;

		case 3:
			switch (ctParam2) {
				case 1:
					Ddim_Print(("TEST 1_3_1 Start\n"));
					ct_im_jpeg5_1_3_1(priv->jpeg5);
					Ddim_Print(("TEST 1_3_1 End\n"));
					break;
				case 2:
					Ddim_Print(("TEST 1_3_2 Start\n"));
					ct_im_jpeg5_1_3_2(priv->jpeg5);
					Ddim_Print(("TEST 1_3_2 End\n"));
					break;
				case 3:
					Ddim_Print(("TEST 1_3_3 Start\n"));
					ct_im_jpeg5_1_3_3(priv->jpeg5);
					Ddim_Print(("TEST 1_3_3 End\n"));
					break;
				case 4:
					Ddim_Print(("TEST 1_3_4 Start\n"));
					ct_im_jpeg5_1_3_4(priv->jpeg5);
					Ddim_Print(("TEST 1_3_4 End\n"));
					break;
				case 5:
					Ddim_Print(("TEST 1_3_5 Start\n"));
					ct_im_jpeg6_1_3_5(priv->jpeg6);
					Ddim_Print(("TEST 1_3_5 End\n"));
					break;
				case 6:
					Ddim_Print(("TEST 1_3_6 Start\n"));
					ct_im_jpeg6_1_3_6(priv->jpeg6);
					Ddim_Print(("TEST 1_3_6 End\n"));
					break;
				case 7:
					Ddim_Print(("TEST 1_3_7 Start\n"));
					ct_im_jpeg6_1_3_7(priv->jpeg6);
					Ddim_Print(("TEST 1_3_7 End\n"));
					break;
				case 8:
					Ddim_Print(("TEST 1_3_8 Start\n"));
					ct_im_jpeg6_1_3_8(priv->jpeg6);
					Ddim_Print(("TEST 1_3_8 End\n"));
					break;
				case 9:
					Ddim_Print(("TEST 1_3_9 Start\n"));
					ct_im_jpeg6_1_3_9(priv->jpeg6);
					Ddim_Print(("TEST 1_3_9 End\n"));
					break;
				case 10:
					Ddim_Print(("TEST 1_3_10 Start\n"));
					ct_im_jpeg6_1_3_10(priv->jpeg6);
					Ddim_Print(("TEST 1_3_10 End\n"));
					break;
				case 11:
					Ddim_Print(("TEST 1_3_11 Start\n"));
					ct_im_jpeg6_1_3_11(priv->jpeg6);
					Ddim_Print(("TEST 1_3_11 End\n"));
					break;
				case 12:
					Ddim_Print(("TEST 1_3_12 Start\n"));
					ct_im_jpeg6_1_3_12(priv->jpeg6);
					Ddim_Print(("TEST 1_3_12 End\n"));
					break;
				case 13:
					Ddim_Print(("TEST 1_3_13 Start\n"));
					ct_im_jpeg6_1_3_13(priv->jpeg6);
					Ddim_Print(("TEST 1_3_13 End\n"));
					break;
				case 14:
					Ddim_Print(("TEST 1_3_14 Start\n"));
					ct_im_jpeg6_1_3_14(priv->jpeg6);
					Ddim_Print(("TEST 1_3_14 End\n"));
					break;
				case 15:
					Ddim_Print(("TEST 1_3_15 Start\n"));
					ct_im_jpeg6_1_3_15(priv->jpeg6);
					Ddim_Print(("TEST 1_3_15 End\n"));
					break;
				case 16:
					Ddim_Print(("TEST 1_3_16 Start\n"));
					ct_im_jpeg6_1_3_16(priv->jpeg6);
					Ddim_Print(("TEST 1_3_16 End\n"));
					break;
				case 17:
					Ddim_Print(("TEST 1_3_17 Start\n"));
					ct_im_jpeg6_1_3_17(priv->jpeg6);
					Ddim_Print(("TEST 1_3_17 End\n"));
					break;
				case 18:
					Ddim_Print(("TEST 1_3_18 Start\n"));
					ct_im_jpeg6_1_3_18(priv->jpeg6);
					Ddim_Print(("TEST 1_3_18 End\n"));
					break;
				case 19:
					Ddim_Print(("TEST 1_3_19 Start\n"));
					ct_im_jpeg6_1_3_19(priv->jpeg6);
					Ddim_Print(("TEST 1_3_19 End\n"));
					break;
				case 20:
					Ddim_Print(("TEST 1_3_20 Start\n"));
					ct_im_jpeg6_1_3_20(priv->jpeg6);
					Ddim_Print(("TEST 1_3_20 End\n"));
					break;
				case 21:
					Ddim_Print(("TEST 1_3_21 Start\n"));
					ct_im_jpeg6_1_3_21(priv->jpeg6);
					Ddim_Print(("TEST 1_3_21 End\n"));
					break;
				default:
					Ddim_Print(("input parameter error\n"));
					break;
			}
			break;

		case 4:
			switch (ctParam2) {
				case 1:
					Ddim_Print(("TEST 1_4_1 empty number\n"));
					break;
				case 2:
					Ddim_Print(("TEST 1_4_2 Start\n"));
					ct_im_jpeg5_1_4_2(priv->jpeg5);
					Ddim_Print(("TEST 1_4_2 End\n"));
					break;
				case 3:
					Ddim_Print(("TEST 1_4_3 Start\n"));
					ct_im_jpeg5_1_4_3(priv->jpeg5);
					Ddim_Print(("TEST 1_4_3 End\n"));
					break;
				case 4:
					Ddim_Print(("TEST 1_4_4 Start\n"));
					ct_im_jpeg5_1_4_4(priv->jpeg5);
					Ddim_Print(("TEST 1_4_4 End\n"));
					break;
				case 5:
					Ddim_Print(("TEST 1_4_5 Start\n"));
					ct_im_jpeg5_1_4_5(priv->jpeg5);
					Ddim_Print(("TEST 1_4_5 End\n"));
					break;
				case 6:
					Ddim_Print(("TEST 1_4_6 Start\n"));
					ct_im_jpeg5_1_4_6(priv->jpeg5);
					Ddim_Print(("TEST 1_4_6 End\n"));
					break;
				case 7:
					Ddim_Print(("TEST 1_4_7 Start\n"));
					ct_im_jpeg5_1_4_7(priv->jpeg5);
					Ddim_Print(("TEST 1_4_7 End\n"));
					break;
				case 8:
					Ddim_Print(("TEST 1_4_8 Start\n"));
					ct_im_jpeg5_1_4_8(priv->jpeg5);
					Ddim_Print(("TEST 1_4_8 End\n"));
					break;
				case 9:
					Ddim_Print(("TEST 1_4_9 Start\n"));
					ct_im_jpeg5_1_4_9(priv->jpeg5);
					Ddim_Print(("TEST 1_4_9 End\n"));
					break;
				case 10:
					Ddim_Print(("TEST 1_4_10 Start\n"));
					ct_im_jpeg5_1_4_10(priv->jpeg5);
					Ddim_Print(("TEST 1_4_10 End\n"));
					break;
				case 11:
					Ddim_Print(("TEST 1_4_11 Start\n"));
					ct_im_jpeg5_1_4_11(priv->jpeg5);
					Ddim_Print(("TEST 1_4_11 End\n"));
					break;
				case 12:
					Ddim_Print(("TEST 1_4_12 empty number\n"));
					break;
				case 13:
					Ddim_Print(("TEST 1_4_13 Start\n"));
					ct_im_jpeg5_1_4_13(priv->jpeg5);
					Ddim_Print(("TEST 1_4_13 End\n"));
					break;
				case 14:
					Ddim_Print(("TEST 1_4_14 Start\n"));
					ct_im_jpeg5_1_4_14(priv->jpeg5);
					Ddim_Print(("TEST 1_4_14 End\n"));
					break;
				default:
					Ddim_Print(("input parameter error\n"));
					break;
			}
			break;

		case 5:
			if (ctParam2 == 1) {
				Ddim_Print(("TEST 1_5_1 Start\n"));
				ct_im_jpeg6_1_5_1(priv->jpeg6);
				Ddim_Print(("TEST 1_5_1 End\n"));
			}
			else if (ctParam2 == 2) {
				Ddim_Print(("TEST 1_5_2 Start\n"));
				ct_im_jpeg152();
				Ddim_Print(("TEST 1_5_2 End\n"));
			}
			else {
				Ddim_Print(("input parameter error\n"));
			}
			break;

		case 6:	// Special

			Ddim_Print(("TEST 6 Start\n"));

//			memset(&jpgencParam, 0, sizeof(T_CT_IM_JPG_SPENC_PARAM));

			self->jpegEncTbl.yccSmpl			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;
			self->jpegEncTbl.memFormat	= ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE_DOT;
			self->jpegEncTbl.skipMkFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
			self->jpegEncTbl.driMkNum	= 0;
			self->jpegEncTbl.exifFmtFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
			self->jpegEncTbl.pintLine			= 0;
			self->jpegEncTbl.pintSect			= 0;
			self->jpegEncTbl.pbufCtrl			= CtImJpeg3_GCT_IM_JPEG_PBUF_CTRL;
			self->jpegEncTbl.jbufCtrl			= CtImJpeg3_GCT_IM_JPEG_JBUF_CTRL;
			self->jpegEncTbl.bitDepth		= ImJpegCommon_E_IM_JPEG_BIT_DEPTH_8BIT;
			self->jpegEncTbl.pburstLength	= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
			self->jpegEncTbl.jburstLength	= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
			self->jpegEncTbl.width				= CtImJpeg3_D_CT_JPEG_SIZE_16M_H;
			self->jpegEncTbl.lines				= CtImJpeg3_D_CT_JPEG_SIZE_16M_V;
			// Y Component parameter
			self->jpegEncTbl.component[0].quantTblNo  = 0;	// Select Qunatization table No. for Y
			self->jpegEncTbl.component[0].hufDcTblNo = 0;	// Select DC Huffman table No. for Y
			self->jpegEncTbl.component[0].hufAcTblNo = 0;	// Select AC Huffman table No. for Y
			// Cb Component parameter
			self->jpegEncTbl.component[1].quantTblNo  = 1;	// Select Qunatization table No. for Cb
			self->jpegEncTbl.component[1].hufDcTblNo = 1;	// Select DC Huffman table No. for Cb
			self->jpegEncTbl.component[1].hufAcTblNo = 1;	// Select AC Huffman table No. for Cb
			// Cr Component parameter
			self->jpegEncTbl.component[2].quantTblNo  = 1;	// Select Qunatization table No. for Cr
			self->jpegEncTbl.component[2].hufDcTblNo = 1;	// Select DC Huffman table No. for Cr
			self->jpegEncTbl.component[2].hufAcTblNo = 1;	// Select AC Huffman table No. for Cr

			// Address
			self->jpegEncFrameTbl.yccAddr.y		= CtImJpeg5_D_CT_JPEG_YCC_ADDR;
			self->jpegEncFrameTbl.yccAddr.c		= CtImJpeg5_D_CT_JPEG_YCC_ADDR + \
					(self->jpegEncTbl.width * self->jpegEncTbl.lines);
			self->jpegEncFrameTbl.codeAddr		= CtImJpeg5_D_CT_JPEG_CODE_ADDR;
			// Size
			self->jpegEncFrameTbl.globalYWidth		= CtImJpeg3_D_CT_JPEG_SIZE_16M_H;
			self->jpegEncFrameTbl.globalCWidth		= CtImJpeg3_D_CT_JPEG_SIZE_16M_H;
			self->jpegEncFrameTbl.codeCountFlg	= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;	// dummy value
			self->jpegEncFrameTbl.codeOverCountFlg	= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
			self->limitSize		= ((CtImJpeg3_D_CT_JPEG_SIZE_16M_H + 16) * CtImJpeg3_D_CT_JPEG_SIZE_16M_V) / 2.6;
			self->mode			= CtImJpeg3_T_CT_IM_JPG_SPENC_MODE_CAPTURE;

			// Quality
			self->quality							= ct_im_jpeg_get_encode_quality(CtImJpeg_CR_4_0);


			ct_im_jpeg1_set2(priv->jpeg1,ct_im_jpeg_special_encode(priv->jpeg,self));
			ct_im_jpeg1_set3(priv->jpeg1,ct_im_jpeg1_get2(priv->jpeg1));

			Ddim_Print(("JPEG encode size [0x%lX]\n",ct_im_jpeg1_get2(priv->jpeg1)));
			Ddim_Print(("TEST 6 End\n"));

			break;

		default:
			Ddim_Print(("input parameter error\n"));
			break;

			if(self){
			g_object_unref(self);
			self=NULL;
			}
	}

	return;
}

void ct_im_jpeg3_set1(CtImJpeg3 *self,CtImJpeg1 *outputBytes)
{
	CtImJpeg3Private *priv = CT_IM_JPEG_3_GET_PRIVATE(self);
	priv->jpeg1=outputBytes;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImJpeg3类的一个实例
 */
CtImJpeg3* ct_im_jpeg3_new()
{
	CtImJpeg3 *self = g_object_new(CT_TYPE_IM_JPEG_3,NULL);
	return self;
}
