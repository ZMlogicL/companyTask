/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImJpeg1类
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/

#include <string.h>
#include <stdlib.h>
#include "ddtopone.h"
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
#include "ctimjpeg5.h"
#include "ctimjpeg1.h"

G_DEFINE_TYPE(CtImJpeg1, ct_im_jpeg1, G_TYPE_OBJECT);

#define CT_IM_JPEG_1_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_JPEG_1, CtImJpeg1Private))

#define  CO_CT_IM_JPEG_REG_DUMP	// Debug dump option.
#ifdef 	CO_ACT_HCLOCK
#define  CtImJpeg1_CO_ACT_JPEG_HCLOCK
#endif
#if 1
#ifndef CO_ACT_HCLOCK
#define CtImJpeg1_CO_ACT_JPEG_HCLOCK
#endif
#endif
#define CtImJpeg1_D_CT_JPEG_HCLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP3())
#define CtImJpeg1_D_CT_JPEG_HCLK_BIT					DdTopone_JPGAH_BIT
// #define CO_DEBUG_ON_PC
// #define CO_DEBUG_MEASURE_MS

struct _CtImJpeg1Private
{
#ifdef CtImJpeg1_CO_ACT_JPEG_HCLOCK
	guchar 	gCtIMJpgHclkCtrlCnt;
#endif
	gulong		gJpegEncodeSize;
	gulong		gJpegOutputBytes;
	guchar		gJpegAXIErr;
};

static guchar								S_GJPEG_ENC_END_FLG=0;
static TImJpegEncMng 	S_GJPEG_ENC_MNG;

static TImJpegQuatTbl S_G_JPEG_QTBL = {
	{
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
		0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
		0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
		0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
		0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
		0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
		0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0xFF
	}
};

static TImJpegQuatTbl S_G_JPEG_QTBL2 = {
	{
		0x40, 0x3F, 0x3E, 0x3D, 0x3C, 0x3B, 0x3A, 0x39,
		0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31,
		0x30, 0x2F, 0x2E, 0x2D, 0x2C, 0x2B, 0x2A, 0x29,
		0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21,
		0x20, 0x1F, 0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19,
		0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11,
		0x10, 0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09,
		0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01
	}
};
/*
 *DECLS
 * */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
#if 0
#ifndef CO_DEBUG_MEASURE_MS
static gulong 	ctJpegGetTimeUs(void);
#else
static gulong ctJpegGetTimeMs(void);
#endif
#endif
#ifdef CO_PT_ENABLE
static void 	ctJpegEncodePalladiumIn(const TImJpegEncMng* const encMng,
						const TImJpegEncFrameMng* const encFrmMng, const CtImJpeg6* const encParam);
#endif

static void ct_im_jpeg1_class_init(CtImJpeg1Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImJpeg1Private));
}

static void ct_im_jpeg1_init(CtImJpeg1 *self)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	priv->gCtIMJpgHclkCtrlCnt=0;
	priv->gJpegEncodeSize=0;
	priv->gJpegOutputBytes= 0ul;
	priv->gJpegAXIErr=0;
}
/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
//	CtImJpeg1 *self = (CtImJpeg1*)object;
//	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg1_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImJpeg1 *self = (CtImJpeg1*)object;
//	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg1_parent_class)->finalize(object);
}

#if 0	// measure_time disable.
#ifndef CO_DEBUG_MEASURE_MS
static gulong ctJpegGetTimeUs(void)
{
	guint64 periClk;
	guint64 gtimerCounter;

	periClk = Dd_Top_Get_PERICLK();
	Dd_GTMR_Get_Counter(&gtimerCounter);

	return (gulong)(((gtimerCounter * 1000) / (periClk / 100000)) / 100);
}
#else
static gulong ctJpegGetTimeMs(void)
{
	return ctJpegGetTimeUs() / 1000;
}
#endif
#endif
// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
static void ctJpegEncodePalladiumIn(const TImJpegEncMng* const encMng,
		const TImJpegEncFrameMng* const encFrmMng, const CtImJpeg6* const encParam)
{
	gulong inDataSizY;
	gulong inDataSizC;

	// Calc Y bytes.
	inDataSizY = ((gulong)encFrmMng->globalYWidth) * encParam->gYLines;

	switch(encMng->yccSmpl) {
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC444:	// FALLTHROUGH
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422:
			inDataSizC = ((gulong)encFrmMng->globalCWidth) * encParam->gYLines;
			break;
//		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420:
		default:
			inDataSizC = ((gulong)encFrmMng->globalCWidth) * (encParam->gYLines /2);
			break;
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400:
			inDataSizC = 0ul;
	}
	if(encMng->memFormat == ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE) {
		inDataSizC *= 2;
	}


	Ddim_Print(("%s(): Palladium_Set_In_Localstack(0x%lx, %lu)\n", __func__,
						((gulong)encFrmMng->yccAddr.y), inDataSizY + inDataSizC));
	Palladium_Set_In_Localstack(((gulong)encFrmMng->yccAddr.y), inDataSizY + inDataSizC);
}
#endif
/*
 *PUBLIC
 * */
#if 0	// measure_time disable.
gint32 ct_im_jpeg1_measure_time_start(void)
{
	DDIM_USER_SYSTIM sysTime;

#ifndef CO_DEBUG_MEASURE_MS
	sysTime = ctJpegGetTimeUs();
#else
	sysTime = ctJpegGetTimeMs();
#endif
	gJpeg_Measure_Time = sysTime;
	return 0;
}

gint32 ct_im_jpeg1_measure_time_print(void)
{
	DDIM_USER_SYSTIM sysTime;
	DDIM_USER_SYSTIM mTime;

#ifndef CO_DEBUG_MEASURE_MS
	sysTime = ctJpegGetTimeUs();
	mTime = sysTime - gJpeg_Measure_Time;
	Ddim_Print(("***** Measure Time = %d(us) *****\n", (gulong)mTime));
#else
	sysTime = ctJpegGetTimeMs();
	mTime = sysTime - gJpeg_Measure_Time;
	Ddim_Print(("***** Measure Time = %d(ms) *****\n", (gulong)mTime));
#endif

	return 0;
}
#endif	// measure_time disable.
//变公有
void ct_im_jpeg1_start_hclock(CtImJpeg1 *self)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
#ifdef CtImJpeg1_CO_ACT_JPEG_HCLOCK
	DDIM_User_AhbReg_SpinLock();
	Dd_Top_Start_Clock((guchar*)&priv->gCtIMJpgHclkCtrlCnt, CtImJpeg1_D_CT_JPEG_HCLK_REG_ADDR, ~CtImJpeg1_D_CT_JPEG_HCLK_BIT);
#endif // CtImJpeg1_CO_ACT_JPEG_HCLOCK
}
//变公有
void ct_im_jpeg1_stop_hclock(CtImJpeg1 *self)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
#ifdef CtImJpeg1_CO_ACT_JPEG_HCLOCK
	Dd_Top_Stop_Clock((guchar*)&priv->gCtIMJpgHclkCtrlCnt, CtImJpeg1_D_CT_JPEG_HCLK_REG_ADDR, CtImJpeg1_D_CT_JPEG_HCLK_BIT);
	DDIM_User_AhbReg_SpinUnLock();
#endif
}
//变公有
void ct_im_jpeg1_ctrl_print(CtImJpeg1EPrintCtrl ptn, void* ctrl)
{
#if 0
	T_IM_JPEG_DEC_MNG decMng;
	T_IM_JPEG_DEC_FRAME_MNG decFrmMng;
	TImJpegEncMng encMng;
	TImJpegEncFrameMng encFrmMng;

	switch(ptn) {
		case CtImJpeg1_E_PRINT_CTRL_ENC_BASE:
			memcpy(&encMng, ctrl, sizeof(TImJpegEncMng));
			Ddim_Print(("Print Enc Base Setting start ------------- \n"));
			Ddim_Print(("encMng.yccSmpl                   =[0x%X]\n", encMng.yccSmpl));
			Ddim_Print(("encMng.memFormat                 =[0x%X]\n", encMng.memFormat));
			Ddim_Print(("encMng.width                      =[%d]\n", encMng.width));
			Ddim_Print(("encMng.lines                      =[%d]\n", encMng.lines));
			Ddim_Print(("encMng.component[0].quantTblNo  =[0x%X]\n", encMng.component[0].quantTblNo));
			Ddim_Print(("encMng.component[0].hufDcTblNo =[0x%X]\n", encMng.component[0].hufDcTblNo));
			Ddim_Print(("encMng.component[0].hufAcTblNo =[0x%X]\n", encMng.component[0].hufAcTblNo));
			Ddim_Print(("encMng.component[1].quantTblNo  =[0x%X]\n", encMng.component[1].quantTblNo));
			Ddim_Print(("encMng.component[1].hufDcTblNo =[0x%X]\n", encMng.component[1].hufDcTblNo));
			Ddim_Print(("encMng.component[1].hufAcTblNo =[0x%X]\n", encMng.component[1].hufAcTblNo));
			Ddim_Print(("encMng.component[2].quantTblNo  =[0x%X]\n", encMng.component[2].quantTblNo));
			Ddim_Print(("encMng.component[2].hufDcTblNo =[0x%X]\n", encMng.component[2].hufDcTblNo));
			Ddim_Print(("encMng.component[2].hufAcTblNo =[0x%X]\n", encMng.component[2].hufAcTblNo));
			Ddim_Print(("encMng.skipMkFlg                =[0x%X]\n", encMng.skipMkFlg));
			Ddim_Print(("encMng.driMkNum                 =[0x%X]\n", encMng.driMkNum));
			Ddim_Print(("encMng.exifFmtFlg               =[0x%X]\n", encMng.exifFmtFlg));
			Ddim_Print(("encMng.pintLine                  =[0x%X]\n", encMng.pintLine));
			Ddim_Print(("encMng.pintSect                  =[0x%lX]\n", encMng.pintSect));
			Ddim_Print(("encMng.pbufCtrl.endian           =[0x%X]\n", encMng.pbufCtrl.endian));
			Ddim_Print(("encMng.pbufCtrl.issueTranNum   =[0x%X]\n", encMng.pbufCtrl.issueTranNum));
			Ddim_Print(("encMng.pbufCtrl.cacheType       =[0x%X]\n", encMng.pbufCtrl.cacheType));
			Ddim_Print(("encMng.pbufCtrl.protType        =[0x%X]\n", encMng.pbufCtrl.protType));
			Ddim_Print(("encMng.jbufCtrl.endian           =[0x%X]\n", encMng.jbufCtrl.endian));
			Ddim_Print(("encMng.jbufCtrl.issueTranNum   =[0x%X]\n", encMng.jbufCtrl.issueTranNum));
			Ddim_Print(("encMng.jbufCtrl.cacheType       =[0x%X]\n", encMng.jbufCtrl.cacheType));
			Ddim_Print(("encMng.jbufCtrl.protType        =[0x%X]\n", encMng.jbufCtrl.protType));
			Ddim_Print(("encMng.jburstLength              =[0x%X]\n", encMng.jburstLength));
			Ddim_Print(("encMng.pburstLength              =[0x%X]\n", encMng.pburstLength));
			Ddim_Print(("Print Enc Base Setting end ------------- \n"));
			break;
		case CtImJpeg1_E_PRINT_CTRL_ENC_FRAME:
			memcpy(&encFrmMng, ctrl, sizeof(TImJpegEncFrameMng));
			Ddim_Print(("Print Enc Frame Setting start ------------- \n"));
			Ddim_Print(("encFrmMng.globalYWidth =[%ld]\n", encFrmMng.globalYWidth));
			Ddim_Print(("encFrmMng.globalCWidth =[%ld]\n", encFrmMng.globalCWidth));
			Ddim_Print(("encFrmMng.yccAddr.y     =[0x%08lX]\n", encFrmMng.yccAddr.y));
			Ddim_Print(("encFrmMng.yccAddr.c     =[0x%08lX]\n", encFrmMng.yccAddr.c));
			Ddim_Print(("encFrmMng.codeAddr      =[0x%08lX]\n", encFrmMng.codeAddr));
			Ddim_Print(("encFrmMng.codeCountFlg =[0x%X]\n", encFrmMng.codeCountFlg));
#ifdef CO_DEBUG_ON_PC
			Ddim_Print(("encFrmMng.limitSize     =[%I64X]\n", encFrmMng.limitSize));
#else
			Ddim_Print(("encFrmMng.limitSize     =[0x%llX]\n", encFrmMng.limitSize));
#endif	// CO_DEBUG_ON_PC
			Ddim_Print(("Print Enc Frame Setting end------------- \n"));
			break;
		case CtImJpeg1_E_PRINT_CTRL_DEC_BASE:
			memcpy(&decMng, ctrl, sizeof(T_IM_JPEG_DEC_MNG));
			Ddim_Print(("Print Dec Base Setting start ------------- \n"));
			Ddim_Print(("decMng.smpl_type                =[0x%X]\n", decMng.smpl_type));
			Ddim_Print(("decMng.memFormat               =[0x%X]\n", decMng.memFormat));
			Ddim_Print(("decMng.ext_mode                 =[0x%X]\n", decMng.ext_mode));
			Ddim_Print(("decMng.skipMkFlg              =[0x%X]\n", decMng.skipMkFlg));
			Ddim_Print(("decMng.pintLine                =[0x%X]\n", decMng.pintLine));
			Ddim_Print(("decMng.pintSect                =[0x%lX]\n", decMng.pintSect));
			Ddim_Print(("decMng.corr_mode                =[0x%X]\n", decMng.corr_mode));
			Ddim_Print(("decMng.color_band.y_band        =[0x%X]\n", decMng.color_band.y_band));
			Ddim_Print(("decMng.color_band.cb_band       =[0x%X]\n", decMng.color_band.cb_band));
			Ddim_Print(("decMng.color_band.cr_band       =[0x%X]\n", decMng.color_band.cr_band));
			Ddim_Print(("decMng.pbufCtrl.endian         =[0x%X]\n", decMng.pbufCtrl.endian));
			Ddim_Print(("decMng.pbufCtrl.issueTranNum =[0x%X]\n", decMng.pbufCtrl.issueTranNum));
			Ddim_Print(("decMng.pbufCtrl.cacheType     =[0x%X]\n", decMng.pbufCtrl.cacheType));
			Ddim_Print(("decMng.pbufCtrl.protType      =[0x%X]\n", decMng.pbufCtrl.protType));
			Ddim_Print(("decMng.jbufCtrl.endian         =[0x%X]\n", decMng.jbufCtrl.endian));
			Ddim_Print(("decMng.jbufCtrl.issueTranNum =[0x%X]\n", decMng.jbufCtrl.issueTranNum));
			Ddim_Print(("decMng.jbufCtrl.cacheType     =[0x%X]\n", decMng.jbufCtrl.cacheType));
			Ddim_Print(("decMng.jbufCtrl.protType      =[0x%X]\n", decMng.jbufCtrl.protType));
			Ddim_Print(("decMng.jburstLength            =[0x%X]\n", decMng.jburstLength));
			Ddim_Print(("decMng.pburstLength            =[0x%X]\n", decMng.pburstLength));
			Ddim_Print(("Print Dec Base Setting end ------------- \n"));
			break;
		case CtImJpeg1_E_PRINT_CTRL_DEC_FRAME:
			memcpy(&decFrmMng, ctrl, sizeof(T_IM_JPEG_DEC_FRAME_MNG));
			Ddim_Print(("Print Dec Frame Setting start ------------- \n"));
			Ddim_Print(("decFrmMng.globalYWidth  =[%ld]\n", decFrmMng.globalYWidth));
			Ddim_Print(("decFrmMng.globalCWidth  =[%ld]\n", decFrmMng.globalCWidth));
			Ddim_Print(("decFrmMng.cutout_flg	     =[0x%X]\n", decFrmMng.cutout_flg	));
			Ddim_Print(("decFrmMng.cutout_width    =[%d]\n", decFrmMng.cutout_width));
			Ddim_Print(("decFrmMng.cutout_lines    =[%d]\n", decFrmMng.cutout_lines));
			Ddim_Print(("decFrmMng.cutout_offset_h =[%d]\n", decFrmMng.cutout_offset_h));
			Ddim_Print(("decFrmMng.cutout_offset_v =[%d]\n", decFrmMng.cutout_offset_v));
			Ddim_Print(("decFrmMng.yccAddr.y      =[0x%08lX]\n", decFrmMng.yccAddr.y));
			Ddim_Print(("decFrmMng.yccAddr.c      =[0x%08lX]\n", decFrmMng.yccAddr.c));
			Ddim_Print(("decFrmMng.codeAddr       =[0x%08lX]\n", decFrmMng.codeAddr));
#ifdef CO_DEBUG_ON_PC
			Ddim_Print(("decFrmMng.codeSize   =[%I64X]\n", decFrmMng.codeSize));
#else
			Ddim_Print(("decFrmMng.codeSize   =[0x%llX]\n", decFrmMng.codeSize));
#endif
			Ddim_Print(("Print Dec Frame Setting end ------------- \n"));
			break;
		default:
			break;
	}
#endif
}
//变公有
void ct_im_jpeg1_encode_cb(TImJpegEncMng* pJpgEncMng)
{
	Ddim_Print(("***** Encode Callback function *****\n"));
	memcpy(&S_GJPEG_ENC_MNG, pJpgEncMng, sizeof(TImJpegEncMng));
	S_GJPEG_ENC_END_FLG = 1;
//	ct_im_jpeg1_measure_time_print();
	Ddim_Print(("***** Process Result = 0x%lX *****\n", (gulong)(pJpgEncMng->result)));
	Ddim_Print(("***** Code Size      = 0x%lX *****\n", (gulong)(pJpgEncMng->codeSize)));
	return;
}

#ifdef CO_DEBUG_ON_PC
//变公有
void ct_im_jpeg1_encode_int_handler(guchar ptn)
{
	IO_JPG7.JSTATE.bit.JALLRSTP = 1;
	switch(ptn) {
		case 1:
		// Normal
			IO_JPG7.JINT.word		= 0x0C00C000;
			IO_JPG7.JPINTSTA.word	= 0x80000000;
			IO_JPG7.JPBYTCNT.word	= 0x005DC900;
			break;

		case 2:
		// Pause
			IO_JPG7.JINT.word		= 0x80001000;
			IO_JPG7.JPINTSTA.word	= 0x00000000;
			IO_JPG7.JPBYTCNT.word	= 0xFFFFFFFF;
			break;

		case 3:
		// Quant update
			IO_JPG7.JINT.word		= 0x0C000000;
			IO_JPG7.JPINTSTA.word	= 0x00000010;
			IO_JPG7.JPBYTCNT.word	= 0xFFFFFFFF;
			break;
		case 4:
		// JPBINT
			IO_JPG7.JINT.word		= 0x20400000;
			IO_JPG7.JPINTSTA.word	= 0x00000000;
			break;

		case 5:
		// JJBINT
			IO_JPG7.JINT.word		= 0x20200000;
			IO_JPG7.JPINTSTA.word	= 0x00000000;
			break;

		default:

			break;

	}
	IO_JPG7.JPSTATUS.bit.JPSTATUS = 1;
	Im_JPEG_Int_Handler();
	return;
}
#endif	// CO_DEBUG_ON_PC
//变公有
void ct_im_jpeg1_stop(void)
{
#ifdef CO_DEBUG_ON_PC
	IO_JPG7.JSTATE.bit.JALLRSTP = 1;
#endif	// CO_DEBUG_ON_PC
	Im_JPEG_Stop();
	return;
}
//变公有
// ### REMOVE_RELEASE END
void ct_im_jpeg1_encode(CtImJpeg1 *self,CtImJpeg6* encParam, guchar setQualv)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	TImJpegEncMng encMng;
	TImJpegEncFrameMng encFrmMng;
	gint32 ret = 0;
//	E_IM_JPEG_AXI_ST		buf_status;
	gint32	i;
	gint32		roopCnt;
	gulonglong	pauseSize;
	gulong		sectorCnt;
	gushort	errRatio;
	TImJpegEncMng outEncMng;
	TImJpegEncFrameMng outEncFrmMng;
	TImJpegQuatTblPack quantTblPack;
// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	gulong	codeAddr;
#endif
// ### REMOVE_RELEASE END

	memset(&encMng, 0, sizeof(TImJpegEncMng));
	memset(&encFrmMng, 0, sizeof(TImJpegEncFrameMng));
	memset(&outEncMng, 0, sizeof(TImJpegEncMng));
	memset(&outEncFrmMng, 0, sizeof(TImJpegEncFrameMng));

	// Base
	switch(encParam->format) {
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

	encMng.width = encParam->hSize;
	encMng.lines = encParam->vSize;

	encMng.component[0].quantTblNo  	= 0;	// Y
	encMng.component[0].hufDcTblNo 	= 0;	// Y
	encMng.component[0].hufAcTblNo 	= 0;	// Y
	encMng.component[1].quantTblNo  	= 1;	// CB
	encMng.component[1].hufDcTblNo 	= 1;	// CB
	encMng.component[1].hufAcTblNo 	= 1;	// CB
	encMng.component[2].quantTblNo  	= 1;	// CR
	encMng.component[2].hufDcTblNo 	= 1;	// CR
	encMng.component[2].hufAcTblNo 	= 1;	// CR

	encMng.skipMkFlg = encParam->skipMkFlg;

	if (encParam->dri) {
		encMng.driMkNum = 0x10;
	}
	else {
		encMng.driMkNum = 0;
	}

	encMng.exifFmtFlg				= ImJpegCommon_D_IM_JPEG_ENABLE_ON;
	encMng.pintLine					= 0;
	encMng.pintSect					= 0;
	encMng.pbufCtrl.endian		= ImJpegCommon_E_IM_JPEG_ENDIAN_LITTLE;
	encMng.pbufCtrl.issueTranNum	= ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
	encMng.pbufCtrl.cacheType			= ImJpegCommon_D_IM_JPEG_NON_CACHE_NON_BUF;
	encMng.pbufCtrl.protType				= ImJpegCommon_D_IM_JPEG_D_SEC_NORMAL_ACCESS;
	encMng.jbufCtrl.endian					= ImJpegCommon_E_IM_JPEG_ENDIAN_LITTLE;
	encMng.jbufCtrl.issueTranNum		= ImJpegCommon_E_IM_JPEG_ISSUE_TRAN_8;
	encMng.jbufCtrl.cacheType				= ImJpegCommon_D_IM_JPEG_NON_CACHE_NON_BUF;
	encMng.jbufCtrl.protType				= ImJpegCommon_D_IM_JPEG_D_SEC_NORMAL_ACCESS;
	encMng.jburstLength						= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
	encMng.pburstLength						= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;

	if (encParam->sync) {
		encMng.pcallback = NULL;
	}
	else {
		encMng.pcallback = (VP_CALLBACK)ct_im_jpeg1_encode_cb;
	}

	// Frame
	encFrmMng.globalYWidth = encParam->gYWidth;

	// Y addr
	encFrmMng.yccAddr.y = CtImJpeg5_D_CT_JPEG_YCC_ADDR;

	encFrmMng.globalCWidth = encParam->gCWidth;
	// Cb addr
	encFrmMng.yccAddr.c = CtImJpeg5_D_CT_JPEG_YCC_ADDR + (encParam->gYWidth * encParam->gYLines);

	// Code addr
	if(priv->gJpegAXIErr) {
		encFrmMng.codeAddr		= CtImJpeg1_D_CT_JPEG_CODE_ADDR_ERR;
	}
	else {
		encFrmMng.codeAddr		= CtImJpeg5_D_CT_JPEG_CODE_ADDR;
	}
	encFrmMng.codeCountFlg	= encParam->countFlg;

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ctJpegEncodePalladiumIn(&encMng, &encFrmMng, encParam);
	codeAddr = encFrmMng.codeAddr;
#endif

// ### REMOVE_RELEASE END
//	ct_im_jpeg1_measure_time_start();

	ret = Im_JPEG_Open(100);
	Ddim_Print(("Im_JPEG_Open ret=0x%X\n", ret));
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		return;
	}

	if (setQualv) {
		ret = Im_JPEG_Set_Quality(51200, 0);
		Ddim_Print(("Im_JPEG_Set_Quality ret=0x%X\n", ret));
		if (ret != ImJpegCommon_D_IM_JPEG_OK) {
			Im_JPEG_Close();
			return;
		}
	}
	else {
#if 1
		quantTblPack.quantization_tbl_0 = &S_G_JPEG_QTBL;
		quantTblPack.quantization_tbl_1 = &S_G_JPEG_QTBL;
		quantTblPack.quantization_tbl_2 = &S_G_JPEG_QTBL;
		quantTblPack.quantization_tbl_3 = &S_G_JPEG_QTBL;
#else
		quantTblPack.quantization_tbl_0 = NULL;
		quantTblPack.quantization_tbl_1 = NULL;
		quantTblPack.quantization_tbl_2 = NULL;
		quantTblPack.quantization_tbl_3 = NULL;
#endif
		Im_JPEG_Set_QTbl(&quantTblPack, 0);
		Ddim_Print(("Im_JPEG_Set_QTbl ret=0x%X\n", ret));
		if (ret != ImJpegCommon_D_IM_JPEG_OK) {
			Im_JPEG_Close();
			return;
		}
	}

	ret = Im_JPEG_Ctrl_Enc(&encMng);
	Ddim_Print(("Im_JPEG_Ctrl_Enc ret=0x%X\n", ret));
	// Ctrl Print
	ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_ENC_BASE, (void*)&encMng);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Im_JPEG_Close();
		return;
	}

	if (!encParam->pauseFlg) {

		// limit size
		encFrmMng.limitSize		= encParam->limitSize;

		if (encParam->countFlg ) {
			errRatio = Im_JPEG_Set_Down_Sampling_Rate(encParam->dspRate);
			Ddim_Print(("Im_JPEG_Set_Down_Sampling_Rate errRatio=0x%X\n", errRatio));
			roopCnt = 0;
		}
		else if (encParam->quantupFlg) {

			if (setQualv) {
				// For next frame
				ret = Im_JPEG_Set_Quality(0x40, 1);
				Ddim_Print(("Im_JPEG_Set_Quality ret=0x%X\n", ret));
				if (ret != ImJpegCommon_D_IM_JPEG_OK) {
					Im_JPEG_Close();
					return;
				}
			}
			else {
				quantTblPack.quantization_tbl_0 = &S_G_JPEG_QTBL2;
				quantTblPack.quantization_tbl_1 = &S_G_JPEG_QTBL2;
				quantTblPack.quantization_tbl_2 = &S_G_JPEG_QTBL2;
				quantTblPack.quantization_tbl_3 = &S_G_JPEG_QTBL2;

				Im_JPEG_Set_QTbl(&quantTblPack, 1);
				Ddim_Print(("Im_JPEG_Set_QTbl ret=0x%X\n", ret));
				if (ret != ImJpegCommon_D_IM_JPEG_OK) {
					Im_JPEG_Close();
					return;
				}
			}
			roopCnt = 1;
		}
		else {
			roopCnt = 0;
		}

		for (i=0; i<=roopCnt; i++) {
			ret = Im_JPEG_Ctrl_Enc_Frame(&encFrmMng);
			Ddim_Print(("Im_JPEG_Ctrl_Enc_Frame ret=0x%X\n", ret));
			// Ctrl Print
			ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_ENC_FRAME, (void*)&encFrmMng);
			if (ret != ImJpegCommon_D_IM_JPEG_OK) {
				Im_JPEG_Close();
				return;
			}

			Ddim_Print(("Im_JPEG_Get_Ctrl_Enc\n"));
			Im_JPEG_Get_Ctrl_Enc(&outEncMng);
			ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_ENC_BASE, (void*)&outEncMng);
			Ddim_Print(("Im_JPEG_Get_Ctrl_Enc_Frame\n"));
			Im_JPEG_Get_Ctrl_Enc_Frame(&outEncFrmMng);
			ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_ENC_FRAME, (void*)&outEncFrmMng);

			Ddim_Print(("Im_JPEG_Start_Enc\n"));
			ret = Im_JPEG_Start_Enc();
			Ddim_Print(("Im_JPEG_Start_Enc ret=0x%X\n", ret));
			if (ret != ImJpegCommon_D_IM_JPEG_OK) {
				Im_JPEG_Close();
				return;
			}

#ifdef CO_CT_IM_JPEG_REG_DUMP
			ct_im_jpeg1_start_hclock(self);
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
			Ddim_Print(("IO_JPG7.JJBSTA  		=0x%lX\n", IO_JPG7.JJBSTA.word));
			Ddim_Print(("IO_JPG7.JPBSTA   		=0x%lX\n", IO_JPG7.JPBSTA.word));
			Ddim_Print(("IO_JPG7.JPMODE   	=0x%lX\n", IO_JPG7.JPMODE.word));
			Ddim_Print(("IO_JPG7.JIMGAY.bit.JIMGAY   		=0x%lX\n", IO_JPG7.JIMGAY.bit.JIMGAY));
			Ddim_Print(("IO_JPG7.JIMGACB.bit.JIMGACB 	=0x%lX\n", IO_JPG7.JIMGACB.bit.JIMGACB));
			Ddim_Print(("IO_JPG7.JCODA.bit.JCODA     		=0x%lX\n", IO_JPG7.JCODA.bit.JCODA));

			ct_im_jpeg1_stop_hclock(self);
#endif

/*
			while(1) {
				Im_JPEG_Get_Axi_State(&buf_status);
				Ddim_Print(("Im_JPEG_Get_Axi_State status=0x%X\n", buf_status));
				if (buf_status == E_IM_JPEG_AXI_ST_ACTIVE_BOTH) {
					break;
				}
#ifdef CO_DEBUG_ON_PC
				IO_JPG7.JSTATE.bit.JALLACTP = 1;
				IO_JPG7.JSTATE.bit.JJBACTP = 1;
				IO_JPG7.JSTATE.bit.JPBACTP = 1;
#endif	// CO_DEBUG_ON_PC
			}
*/
			if (roopCnt != 0) {
				encFrmMng.codeAddr		= 0x52000000;
				// For next frame
				ret = Im_JPEG_Ctrl_Enc_Frame(&encFrmMng);
				Ddim_Print(("Im_JPEG_Ctrl_Enc_Frame ret=0x%X\n", ret));
				// Ctrl Print
				ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_ENC_FRAME, (void*)&encFrmMng);
				if (ret != ImJpegCommon_D_IM_JPEG_OK) {
					Im_JPEG_Close();
					return;
				}
			}

			if (encParam->sync) {
#ifdef CO_DEBUG_ON_PC
				ct_im_jpeg1_encode_int_handler(1);
#endif	// CO_DEBUG_ON_PC
				Ddim_Print(("Im_JPEG_Wait_End_Enc\n"));
				ret = Im_JPEG_Wait_End_Enc(&encMng, D_DDIM_WAIT_END_TIME);

				Ddim_Print(("Im_JPEG_Wait_End_Enc ret=0x%X\n", ret));
				memcpy(&S_GJPEG_ENC_MNG, &encMng, sizeof(TImJpegEncMng));

				if (ret != ImJpegCommon_D_IM_JPEG_OK) {
					ct_im_jpeg1_stop();
					Im_JPEG_Close();
					Ddim_Print(("***** Encode Error result=[0x%X] *****\n", S_GJPEG_ENC_MNG.result));
					return;
				}
			}
			else {
#ifdef CO_DEBUG_ON_PC
				ct_im_jpeg1_encode_int_handler(1);
#endif	// CO_DEBUG_ON_PC

				while (!S_GJPEG_ENC_END_FLG) {
					DDIM_User_Dly_Tsk(1);
				}

				Ddim_Print(("***** Callback Wait End *****\n"));

				S_GJPEG_ENC_END_FLG = 0;

				if ((S_GJPEG_ENC_MNG.result & ImJpegCommon_D_IM_JPEG_PROC_END) != ImJpegCommon_D_IM_JPEG_PROC_END) {
					Ddim_Print(("***** Encode Error result=[0x%X] *****\n", S_GJPEG_ENC_MNG.result));
					ct_im_jpeg1_stop();
					Ddim_Print(("***** close *****\n"));
					Im_JPEG_Close();
					return;
				}
			}

			priv->gJpegEncodeSize = (S_GJPEG_ENC_MNG.codeSize << (encParam->dspRate * 2));
			priv->gJpegOutputBytes = priv->gJpegEncodeSize;

//			ct_im_jpeg1_measure_time_print();
			Ddim_Print(("***** Encode %d result                  =[0x%X] *****\n", i, S_GJPEG_ENC_MNG.result));
			Ddim_Print(("***** Encode %d S_GJPEG_ENC_MNG.codeSize =[0x%lX] *****\n", i, S_GJPEG_ENC_MNG.codeSize));
			Ddim_Print(("***** Encode %d priv->gJpegEncodeSize       =[0x%lX] *****\n", i, priv->gJpegEncodeSize));
		}
	}
	else {
	// pause

		// limit size
		pauseSize = encParam->limitSize / 2;
		sectorCnt = (gulong)(pauseSize / 512);
		encFrmMng.limitSize = pauseSize;

		for (i=0; i<=1; i++) {

			if (i == 0) {

				ret = Im_JPEG_Ctrl_Enc_Frame(&encFrmMng);
				Ddim_Print(("Im_JPEG_Ctrl_Enc_Frame ret=0x%X\n", ret));
				ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_ENC_FRAME, (void*)&encFrmMng);
				if (ret != ImJpegCommon_D_IM_JPEG_OK) {
					Im_JPEG_Close();
					return;
				}

				Im_JPEG_Get_Ctrl_Enc(&outEncMng);
				ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_ENC_BASE, (void*)&outEncMng);
				Im_JPEG_Get_Ctrl_Enc_Frame(&outEncFrmMng);
				ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_ENC_FRAME, (void*)&outEncFrmMng);

				Ddim_Print(("Im_JPEG_Start_Enc\n"));
				ret = Im_JPEG_Start_Enc();
				Ddim_Print(("Im_JPEG_Start_Enc ret=0x%X\n", ret));
				if (ret != ImJpegCommon_D_IM_JPEG_OK) {
					Im_JPEG_Close();
					return;
				}

				ct_im_jpeg1_start_hclock(self);
				Ddim_Print(("IO_JPG7.JINTEN =0x%lX\n", IO_JPG7.JINTEN.word));
				Ddim_Print(("IO_JPG7.JPSTATUS.bit.JPSTATUS =0x%X\n", IO_JPG7.JPSTATUS.bit.JPSTATUS));
				Ddim_Print(("IO_JPG7.JPCMD  =0x%lX\n", IO_JPG7.JPCMD.word));
				Ddim_Print(("IO_JPG7.JICTL  =0x%lX\n", IO_JPG7.JICTL.word));
				Ddim_Print(("IO_JPG7.JCCTL  =0x%lX\n", IO_JPG7.JCCTL.word));
				ct_im_jpeg1_stop_hclock(self);

			}
			else {
				// none limit
				encFrmMng.limitSize = 0;
				encFrmMng.codeAddr = CtImJpeg5_D_CT_JPEG_CODE_ADDR + (sectorCnt * 512);

				ret = Im_JPEG_Restart_Enc(&encFrmMng);
				Ddim_Print(("Im_JPEG_Restart_Enc ret=0x%X\n", ret));
				ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_ENC_FRAME, (void*)&encFrmMng);
				if (ret != ImJpegCommon_D_IM_JPEG_OK) {
					Im_JPEG_Close();
					return;
				}
			}

			if (encParam->sync) {
#ifdef CO_DEBUG_ON_PC
				if (i == 0) {
					ct_im_jpeg1_encode_int_handler(2);
				}
				else {
					ct_im_jpeg1_encode_int_handler(1);
				}
#endif	// CO_DEBUG_ON_PC
				ret = Im_JPEG_Wait_End_Enc(&encMng, D_DDIM_WAIT_END_TIME);

				Ddim_Print(("Im_JPEG_Wait_End_Enc ret=0x%X\n", ret));
				memcpy(&S_GJPEG_ENC_MNG, &encMng, sizeof(TImJpegEncMng));

				if (ret != ImJpegCommon_D_IM_JPEG_OK) {
					if (i == 0 && ret == ImJpegCommon_D_IM_JPEG_ENCODE_PAUSE) {
						Ddim_Print(("Encode Pause\n"));
#ifdef CO_DEBUG_ON_PC
						IO_JPG7.JCCTL.bit.JCTRG = 2;
#endif	// CO_DEBUG_ON_PC
					}
					else {
						ct_im_jpeg1_stop();
						Im_JPEG_Close();
						Ddim_Print(("Encode Error result=0x%X\n", S_GJPEG_ENC_MNG.result));
						return;
					}
				}
			}
			else {
#ifdef CO_DEBUG_ON_PC
				if (i == 0) {
					ct_im_jpeg1_encode_int_handler(2);
				}
				else {
					ct_im_jpeg1_encode_int_handler(1);
				}
#endif	// CO_DEBUG_ON_PC
				while (!S_GJPEG_ENC_END_FLG) {
					;
				}
				S_GJPEG_ENC_END_FLG = 0;

				if ((S_GJPEG_ENC_MNG.result & ImJpegCommon_D_IM_JPEG_PROC_END) != ImJpegCommon_D_IM_JPEG_PROC_END) {
					if (i == 0 && ret == ImJpegCommon_D_IM_JPEG_ENCODE_PAUSE) {
						Ddim_Print(("Encode Pause\n"));
					}
					else {
						ct_im_jpeg1_stop();
						Im_JPEG_Close();
						Ddim_Print(("***** Encode Error result=[0x%X] *****\n", S_GJPEG_ENC_MNG.result));
						return;
					}
				}
			}

			Ddim_Print(("***** Encode %d result                 =[0x%X] *****\n", i, S_GJPEG_ENC_MNG.result));
			Ddim_Print(("***** Encode %d S_GJPEG_ENC_MNG.codeSize=[0x%lX] *****\n", i, S_GJPEG_ENC_MNG.codeSize));
		}

		priv->gJpegEncodeSize = S_GJPEG_ENC_MNG.codeSize;
		priv->gJpegOutputBytes = priv->gJpegEncodeSize;

		Ddim_Print(("***** Encode priv->gJpegEncodeSize=[0x%lX] *****\n", priv->gJpegEncodeSize));
	}
// ### REMOVE_RELEASE BEGIN

#ifdef CO_PT_ENABLE
	if(priv->gJpegEncodeSize != 0) {
		Ddim_Print(("%s() Palladium_Set_Out_Localstack(0x%lx, %lu)\n", __func__, codeAddr, priv->gJpegEncodeSize));
		Palladium_Set_Out_Localstack(codeAddr, priv->gJpegEncodeSize);
	}
#endif
// ### REMOVE_RELEASE END

	ret = Im_JPEG_Close();
	Ddim_Print(("Im_JPEG_Close ret=0x%X\n", ret));
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		return;
	}

	return;
}

// for palladium
gulong ct_im_jpeg_get_enc_size(CtImJpeg1 *self)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	return priv->gJpegEncodeSize;
}

gulong ct_im_jpeg_get_output_bytes(CtImJpeg1 *self)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	return priv->gJpegOutputBytes;
}

guchar ct_im_jpeg1_get1(CtImJpeg1 *self)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	return priv->gCtIMJpgHclkCtrlCnt;
}

gulong ct_im_jpeg1_get2(CtImJpeg1 *self)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	return priv->gJpegEncodeSize;
}

void ct_im_jpeg1_set2(CtImJpeg1 *self,gulong Encode_Size)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	priv->gJpegEncodeSize=Encode_Size;
}

gulong ct_im_jpeg1_get3(CtImJpeg1 *self)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	return priv->gJpegOutputBytes;
}

void ct_im_jpeg1_set3(CtImJpeg1 *self,gulong outputBytes)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	priv->gJpegOutputBytes=outputBytes;
}

guchar ct_im_jpeg1_get4(CtImJpeg1 *self)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	return priv->gJpegAXIErr;
}

void ct_im_jpeg1_set4(CtImJpeg1 *self,gulong gJpegAXIErr)
{
	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	priv->gJpegAXIErr=gJpegAXIErr;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImJpeg1类的一个实例
 */
CtImJpeg1* ct_im_jpeg1_new()
{
	CtImJpeg1 *self = g_object_new(CT_TYPE_IM_JPEG_1,NULL);
//	CtImJpeg1Private *priv = CT_IM_JPEG_1_GET_PRIVATE(self);
	return self;
}
