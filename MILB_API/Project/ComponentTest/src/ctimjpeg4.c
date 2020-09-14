/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImJpeg4类
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
#include "ctimjpeg4.h"

G_DEFINE_TYPE(CtImJpeg4, ct_im_jpeg4, G_TYPE_OBJECT);

#define CT_IM_JPEG_4_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_JPEG_4, CtImJpeg4Private))

struct _CtImJpeg4Private
{
	TimgDecMng 	*gJpegDecMng;
	CtImJpeg1 *jpeg1;
	CtImJpeg2 *jpeg2;
	CtImJpeg5 *jpeg5;
};

static guchar	S_GJPEG_DEC_END_FLG=0;
/*
 *DECLS
 * */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static void 	ctImJpeg211(void);
static void 	ctImJpeg221(void);
static void 	ctImJpegCheckHandler(gint32 ptn);
#ifdef CO_PT_ENABLE
static void 	ctJpegDecodePalladiumIn(const TimgDecMng* const decMng,
						const TimgDecFrameMng* const decFrmMng, const CtImJpeg5* const decParam);
static void 	ctJpegDecodePalladiumOut(const TimgDecMng* const decMng,
						const TimgDecFrameMng* const decFrmMng, const CtImJpeg5* const decParam);
#endif
#ifdef CO_DEBUG_ON_PC
static void 	ctJpegDecodeIntHandler(guchar ptn);
#endif


static void ct_im_jpeg4_class_init(CtImJpeg4Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImJpeg4Private));
}

static void ct_im_jpeg4_init(CtImJpeg4 *self)
{
	CtImJpeg4Private *priv = CT_IM_JPEG_4_GET_PRIVATE(self);
	priv->gJpegDecMng=NULL;
	priv->jpeg1=NULL;
	priv->jpeg2=ct_im_jpeg2_new();
	priv->jpeg5=ct_im_jpeg5_new();
}

/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
		CtImJpeg4 *self = (CtImJpeg4*)object;
		CtImJpeg4Private *priv = CT_IM_JPEG_4_GET_PRIVATE(self);
		G_OBJECT_CLASS(ct_im_jpeg4_parent_class)->dispose(object);

		if(priv->jpeg2){
			g_object_unref(priv->jpeg2);
			priv->jpeg2=NULL;
		}

		if(priv->jpeg5){
			g_object_unref(priv->jpeg5);
			priv->jpeg5=NULL;
		}
}

static void finalize_od(GObject *object)
{
//	CtImJpeg4 *self = (CtImJpeg4*)object;
//	CtImJpeg4Private *priv = CT_IM_JPEG_4_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_jpeg4_parent_class)->finalize(object);
}

static void ctImJpeg211(void)
{
	gint32 ret;
	ret = im_jpeg_open(100);
	Ddim_Print(("im_jpeg_open ret=0x%X\n", ret));

	ret = im_jpeg_open(20);
	Ddim_Print(("im_jpeg_open ret=0x%X\n", ret));

	return;
}

static void ctImJpeg221(void)
{
	gint32 ret;

	ret = im_jpeg_open(-2);
	Ddim_Print(("im_jpeg_open ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_set_quality(0x40000, 0);
	Ddim_Print(("im_jpeg_set_quality ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_set_down_sampling_rate(4);
	Ddim_Print(("im_jpeg_set_down_sampling_rate ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_ctrl_enc(NULL);
	Ddim_Print(("im_jpeg_ctrl_enc ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_get_ctrl_enc_frame(NULL);
	Ddim_Print(("im_jpeg_get_ctrl_enc_frame ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_get_ctrl_enc(NULL);
	Ddim_Print(("im_jpeg_get_ctrl_enc ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_get_ctrl_enc_frame(NULL);
	Ddim_Print(("im_jpeg_get_ctrl_enc_frame ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_wait_end_enc(NULL , 100);
	Ddim_Print(("im_jpeg_wait_end_enc ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_restart_enc(NULL);
	Ddim_Print(("im_jpeg_restart_enc ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_ctrl_dec(NULL);
	Ddim_Print(("im_jpeg_ctrl_dec ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_ctrl_dec_frame(NULL);
	Ddim_Print(("im_jpeg_ctrl_dec_frame ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = Im_JPEG_Get_Ctrl_Dec(NULL);
	Ddim_Print(("Im_JPEG_Get_Ctrl_Dec ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_get_ctrl_dec_frame(NULL);
	Ddim_Print(("im_jpeg_get_ctrl_dec_frame ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_wait_end_dec(NULL , 100);
	Ddim_Print(("im_jpeg_wait_end_dec ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_get_axi_state(NULL);
	Ddim_Print(("im_jpeg_get_axi_state ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = im_jpeg_restart_dec(NULL);
	Ddim_Print(("im_jpeg_restart_dec ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	ret = Im_JPEG_Decode_Sync(NULL, NULL);
	Ddim_Print(("Im_JPEG_Decode_Sync ret=0x%X\n", ret));
	Ddim_Print(("\n"));

	return;
}

static void ctImJpegCheckHandler(gint32 ptn)
{
	IO_JPG7.JSTATE.bit.JALLRSTP = 1;
	IO_JPG7.JINTEN.word = 0xFFFFFFFF;

//	IO_JPG7.JPMODE.bit.DISPOSAL = 0;
	IO_JPG7.JPMODE.bit.DISPOSAL = 1;

	switch (ptn) {
		case 1:
		//	JCLRFMER
			IO_JPG7.JINT.word				= 0x20040000;
			IO_JPG7.JPINTSTA.word		= 0x00000000;
			break;
		case 2:
		//	JJBINT
			IO_JPG7.JJBSTA.bit.JJRES 	= 0x2;
			IO_JPG7.JINT.word				= 0x20400000;
			IO_JPG7.JPINTSTA.word		= 0x00000000;
			break;
		case 3:
		//	JPBINT
			IO_JPG7.JPBSTA.bit.JPRES 	= 0x3;
			IO_JPG7.JINT.word				= 0x20800000;
			IO_JPG7.JPINTSTA.word		= 0x00000000;
			break;
		case 4:
		//	JLINEINT
			IO_JPG7.JINT.word			= 0x20000;
			IO_JPG7.JPINTSTA.word	= 0x00000000;
			break;
		case 5:
		//	JSECTINT
			IO_JPG7.JINT.word			= 0x10000;
			IO_JPG7.JPINTSTA.word	= 0x00000000;
			break;
		case 6:
		//	ERR_FLG
			IO_JPG7.JINT.word			= 0x09000000;
			IO_JPG7.JPINTSTA.word	= 0x00000400;
			break;
		case 7:
		//	SIZERR
			IO_JPG7.JINT.word			= 0x09000000;
			IO_JPG7.JPINTSTA.word	= 0x00000200;
			break;
		case 8:
		//	RSTERR
			IO_JPG7.JINT.word			= 0x09000000;
			IO_JPG7.JPINTSTA.word	= 0x00000100;
			break;
		case 9:
		//	UMKINFO
			IO_JPG7.JPSUSPEND.bit.JPSUSPEND = 1;
			IO_JPG7.JINT.word			= 0x8000000;
			IO_JPG7.JPINTSTA.word	= 0x00000004;
			break;
		case 10:
		//	COMMKONFO
			IO_JPG7.JPSUSPEND.bit.JPSUSPEND = 1;
			IO_JPG7.JINT.word			= 0x8000000;
			IO_JPG7.JPINTSTA.word	= 0x00000002;
			break;
		case 11:
		//	APPINFO
			IO_JPG7.JPSUSPEND.bit.JPSUSPEND = 1;
			IO_JPG7.JINT.word			= 0x8000000;
			IO_JPG7.JPINTSTA.word	= 0x00000001;
			break;
		case 12:
		//	COREND
			IO_JPG7.JINT.word				= 0x08000000;
			IO_JPG7.JPINTSTA.word		= 0x40000000;
			IO_JPG7.JPCORSTA.word	= 0x00000003;
			break;
		case 13:
		// Normal
			IO_JPG7.JINT.word				= 0x0C00C000;
			IO_JPG7.JPINTSTA.word		= 0x80000000;
			IO_JPG7.JPBYTCNT.word	= 0xFFFFFFFF;
			break;
		default:
			Ddim_Print(("input parameter error\n"));
			return;
	}

	IO_JPG7.JPSTATUS.bit.JPSTATUS = 1;

	im_jpeg_int_handler();

	Ddim_Print(("IO_JPG7.JINT     = [0x%lX]\n", IO_JPG7.JINT.word));
	Ddim_Print(("IO_JPG7.JPINTSTA = [0x%lX]\n", IO_JPG7.JPINTSTA.word));
	Ddim_Print(("IO_JPG7.JPSUSPEND = [0x%X]\n", IO_JPG7.JPSUSPEND.bit.JPSUSPEND));

	return;
}
// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
static void ctJpegDecodePalladiumIn(const TimgDecMng* const decMng,
		const TimgDecFrameMng* const decFrmMng, const CtImJpeg5* const decParam)
{
	gulong inDataSizY;	// Maximum data bytes of Y. (Compression ratio=x1.0)
	gulong inDataSizC;	// Maximum data bytes of C. (Compression ratio=x1.0)

	// Calc Y bytes.
	inDataSizY = ((gulong)decFrmMng->globalYWidth) * decParam->gYLines;

	switch(decMng->smplType) {
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC444:	// FALLTHROUGH
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422:
			inDataSizC = ((gulong)decFrmMng->globalCWidth) * decParam->gYLines;
			break;
//		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420:
		default:
			inDataSizC = ((gulong)decFrmMng->globalCWidth) * (decParam->gYLines /2);
			break;
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400:
			inDataSizC = 0ul;
	}
	if(decMng->memFormat == ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE) {
		inDataSizC *= 2;
	}


	Ddim_Print(("%s() Palladium_Set_In_Localstack(0x%lx, %lu)\n", __func__,
			((gulong)decFrmMng->codeAddr), inDataSizY + inDataSizC));
	Palladium_Set_In_Localstack(((gulong)decFrmMng->codeAddr), inDataSizY + inDataSizC);
	Palladium_Set_Out_Localstack(((gulong)decFrmMng->codeAddr), inDataSizY + inDataSizC);	// for Input file check.
}

static void ctJpegDecodePalladiumOut(const TimgDecMng* const decMng,
		const TimgDecFrameMng* const decFrmMng, const CtImJpeg5* const decParam)
{
	gulong outDataSizY;
	gulong outDataSizC;

	// Calc Y bytes.
	outDataSizY = ((gulong)decFrmMng->globalYWidth) * decParam->gYLines;

	switch(decMng->smplType) {
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC444:	// FALLTHROUGH
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422:
			outDataSizC = ((gulong)decFrmMng->globalCWidth) * decParam->gYLines;
			break;
//		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420:
		default:
			outDataSizC = ((gulong)decFrmMng->globalCWidth) * (decParam->gYLines /2);
			break;
		case ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC400:
			outDataSizC = 0ul;
	}
	if(decMng->memFormat == ImJpegCommon_E_IM_JPEG_MEM_FORM_PLANE) {
		outDataSizC *= 2;
	}


	Ddim_Print(("%s() Palladium_Set_Out_Localstack(0x%lx, %lu)\n", __func__, ((gulong)decFrmMng->yccAddr.y),
			outDataSizY + outDataSizC));
	Palladium_Set_Out_Localstack(((gulong)decFrmMng->yccAddr.y), outDataSizY + outDataSizC);
}
#endif

#ifdef CO_DEBUG_ON_PC
static void ctJpegDecodeIntHandler(guchar ptn)
{
	IO_JPG7.JSTATE.bit.JALLRSTP = 1;

	switch(ptn) {
		case 1:
		// Normal
			IO_JPG7.JINT.word			= 0x0A000000;
			IO_JPG7.JPINTSTA.word	= 0x00000008;
			IO_JPG7.JPSUSPEND.bit.JPSUSPEND = 1;

			im_jpeg_int_handler();
			// JIF
			IO_JPG7.JINT.word		= 0x8000;
			im_jpeg_int_handler();
			// JCF
			IO_JPG7.JINT.word		= 0x4000;
			im_jpeg_int_handler();

			IO_JPG7.JINT.word		= 0x0C000000;
			IO_JPG7.JPINTSTA.word	= 0x80000000;
			break;

		case 2:
		// Pause 1
			IO_JPG7.JINT.word		= 0x0A000000;
			IO_JPG7.JPINTSTA.word	= 0x00000008;
			IO_JPG7.JPSUSPEND.bit.JPSUSPEND = 1;

			im_jpeg_int_handler();

			IO_JPG7.JINT.word		= 0x00001000;
			IO_JPG7.JPINTSTA.word	= 0x00000000;
			break;

		case 3:
		// Pause 2
			IO_JPG7.JINT.word		= 0x8000;
			im_jpeg_int_handler();

			IO_JPG7.JINT.word		= 0x4000;
			im_jpeg_int_handler();

			IO_JPG7.JINT.word		= 0x0C000000;
			IO_JPG7.JPINTSTA.word	= 0x80000000;
			break;

		default:

			break;

	}
	IO_JPG7.JPSTATUS.bit.JPSTATUS = 1;
	im_jpeg_int_handler();
	return;
}
#endif
/*
 *PUBLIC
 * */
void ct_im_jpeg4_run2(CtImJpeg4 *self,gint32 ctParam1, gint32 ctParam2)
{
	CtImJpeg4Private *priv = CT_IM_JPEG_4_GET_PRIVATE(self);
	Ddim_Print(("*** Jpeg begin Im_Jpeg_Init\n"));
	im_jpeg_init();
	Ddim_Print(("*** Jpeg end Im_Jpeg_Init\n"));

	switch (ctParam1) {
		case 1:
			if (ctParam2 == 1) {
				Ddim_Print(("TEST 2_1_1 Start\n"));
				ctImJpeg211();
				Ddim_Print(("TEST 2_1_1 End\n"));
			}
			else {
				Ddim_Print(("input parameter error\n"));
			}
			break;
		case 2:
			if (ctParam2 == 1) {
				Ddim_Print(("TEST 2_2_1 Start\n"));
				ctImJpeg221();
				Ddim_Print(("TEST 2_2_1 End\n"));
			}
			else {
				Ddim_Print(("input parameter error\n"));
			}
			break;
		case 3:
			if (ctParam2 == 1) {
				Ddim_Print(("TEST 2_3_1 Start\n"));
				ct_im_jpeg5_2_3_1(priv->jpeg5);
				Ddim_Print(("TEST 2_3_1 End\n"));
			}
			else if (ctParam2 == 2) {
				Ddim_Print(("TEST 2_3_2 Start\n"));
				ct_im_jpeg5_2_3_2(priv->jpeg5);
				Ddim_Print(("TEST 2_3_2 End\n"));
			}
			else {
				Ddim_Print(("input parameter error\n"));
			}
			break;
		case 4:
			if (ctParam2 <= 12) {
				Ddim_Print(("TEST 2_4_1 Start\n"));
				ctImJpegCheckHandler(ctParam2);
				Ddim_Print(("TEST 2_4_1 End\n"));
			}
			else {
				Ddim_Print(("input parameter error\n"));
			}
			break;
		default:
			Ddim_Print(("input parameter error\n"));
			break;
	}
}
//变公有
void ct_im_jpeg4_decode_cb(TimgDecMng* pJpgDecMng)
{
	CtImJpeg4 *self=ct_im_jpeg4_new();
	CtImJpeg4Private *priv = CT_IM_JPEG_4_GET_PRIVATE(self);
	Ddim_Print(("***** Decode Callback function *****\n"));
	memcpy(&priv->gJpegDecMng, pJpgDecMng, sizeof(TimgDecMng));
	S_GJPEG_DEC_END_FLG = 1;
//	ct_im_jpeg1_measure_time_print();
	return;
}
//变公有
// ### REMOVE_RELEASE END
void ct_im_jpeg4_decode(CtImJpeg4 *self,CtImJpeg5* decParam)
{
	CtImJpeg4Private *priv = CT_IM_JPEG_4_GET_PRIVATE(self);
	TimgDecMng decMng;
	TimgDecFrameMng decFrmMng;
	gint32		ret=0;
	gulonglong	pauseSize;
	gulong		sectorCnt;
	gint32		i;

	memset(&decMng, 0, sizeof(TimgDecMng));
	memset(&decFrmMng, 0, sizeof(TimgDecFrameMng));

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

	decMng.extMode 		= decParam->ext;
	decMng.skipMkFlg	= 0;
	decMng.pintLine		= 0;
	decMng.pintSect		= 0;
	decMng.corrMode	= decParam->corrFlg;

	decMng.colorBand.yBand		= 0x01;
	decMng.colorBand.cbBand	= 0x01;
	decMng.colorBand.crBand		= 0x01;

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
		decMng.pcallback = (VpCallback)ct_im_jpeg4_decode_cb;
	}

	// Frame memory
	// Y
	decFrmMng.globalYWidth = decParam->gYWidth;

	if (decParam->cutOutFlg) {
		decFrmMng.cutoutFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_ON;
		decFrmMng.cutoutWidth	= decParam->cutHSize;
		decFrmMng.cutoutLines	= decParam->cutVSize;
		decFrmMng.cutoutOffsetH = ((decParam->hSize - decParam->cutHSize) / 2);
		decFrmMng.cutoutOffsetV = ((decParam->vSize - decParam->cutVSize) / 2);

		if ((decFrmMng.cutoutOffsetH & 0xF) != 0) {
			decFrmMng.cutoutOffsetH = ((decFrmMng.cutoutOffsetH >> 4) << 4) + 16;
		}
		if ((decFrmMng.cutoutOffsetV & 0xF) != 0) {
			decFrmMng.cutoutOffsetV = ((decFrmMng.cutoutOffsetV >> 4) << 4) + 16;
		}

		if(ct_im_jpeg1_get4(priv->jpeg1)) {
			decFrmMng.yccAddr.y		= CtImJpeg2_D_CT_JPEG_YCC_ADDR_ERR;
		}
		else {
			decFrmMng.yccAddr.y		= CtImJpeg5_D_CT_JPEG_YCC_ADDR;
		}

		// CbCr
		decFrmMng.globalCWidth = decParam->gCWidth;
		decFrmMng.yccAddr.c		= CtImJpeg5_D_CT_JPEG_YCC_ADDR + (decParam->gYWidth * decParam->gYLines);
	}
	else {
		decFrmMng.cutoutFlg			= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
		decFrmMng.cutoutWidth		= 0;
		decFrmMng.cutoutLines		= 0;
		decFrmMng.cutoutOffsetH	= 0;
		decFrmMng.cutoutOffsetV	= 0;

		if(ct_im_jpeg1_get4(priv->jpeg1)) {
			decFrmMng.yccAddr.y		= CtImJpeg2_D_CT_JPEG_YCC_ADDR_ERR;
		}
		else {
			decFrmMng.yccAddr.y		= CtImJpeg5_D_CT_JPEG_YCC_ADDR;
		}

		// CbCr
		decFrmMng.globalCWidth = decParam->gCWidth;
		decFrmMng.yccAddr.c		= CtImJpeg5_D_CT_JPEG_YCC_ADDR + (decParam->gYWidth * decParam->gYLines);
	}
	decFrmMng.codeAddr			= CtImJpeg5_D_CT_JPEG_CODE_ADDR;

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ctJpegDecodePalladiumIn(&decMng, &decFrmMng, decParam);
#endif

// ### REMOVE_RELEASE END
//	ct_im_jpeg1_measure_time_start();

	ret = im_jpeg_open(D_DDIM_WAIT_END_TIME);
	Ddim_Print(("im_jpeg_open ret=0x%X\n", ret));
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		return;
	}

	ret = im_jpeg_ctrl_dec(&decMng);
	Ddim_Print(("im_jpeg_ctrl_dec ret=0x%X\n", ret));
	ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_DEC_BASE, (gpointer)&decMng);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		im_jpeg_close();
		return;
	}

	if (!decParam->pauseFlg) {

		// limit size
		decFrmMng.codeSize		= decParam->limitSize;

		ret = im_jpeg_ctrl_dec_frame(&decFrmMng);
		Ddim_Print(("im_jpeg_ctrl_dec_frame ret=0x%X\n", ret));
		// Ctrl Print
		ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_DEC_FRAME, (gpointer)&decFrmMng);
		if (ret != ImJpegCommon_D_IM_JPEG_OK) {
			im_jpeg_close();
			return;
		}

		ret = im_jpeg_start_dec();
		Ddim_Print(("im_jpeg_start_dec ret=0x%X\n", ret));
		if (ret != ImJpegCommon_D_IM_JPEG_OK) {
			im_jpeg_close();
			return;
		}

		if (decParam->sync) {
#ifdef CO_DEBUG_ON_PC
			IO_JPG7.JPWIDTH.bit.JPWIDTH		= decParam->hSize;
			IO_JPG7.JPHEIGHT.bit.JPHEIGHT	= decParam->vSize;
			IO_JPG7.JPMODE.bit.MMODE		= (guchar)decMng.smplType;

			ctJpegDecodeIntHandler(1);

#endif	// CO_DEBUG_ON_PC

			ret = im_jpeg_wait_end_dec(&decMng, 5000);
			Ddim_Print(("im_jpeg_wait_end_dec ret=0x%X\n", ret));

			memcpy(&priv->gJpegDecMng, &decMng, sizeof(TimgDecMng));

			if (ret != ImJpegCommon_D_IM_JPEG_OK) {
				ct_im_jpeg1_stop();
				im_jpeg_close();
				Ddim_Print(("***** Decode Error result=[0x%X] *****\n", priv->gJpegDecMng->result));
				Ddim_Print(("***** Decode Error Code=[0x%X] *****\n", priv->gJpegDecMng->errCode));
				Ddim_Print(("***** Decode Sampling type[%d] *****\n", priv->gJpegDecMng->smplType));
				return;
			}

		}
		else {
#ifdef CO_DEBUG_ON_PC
			IO_JPG7.JPWIDTH.bit.JPWIDTH		= decParam->hSize;
			IO_JPG7.JPHEIGHT.bit.JPHEIGHT	= decParam->vSize;
			IO_JPG7.JPMODE.bit.MMODE		= (guchar)decMng.smplType;

			ctJpegDecodeIntHandler(1);

#endif	// CO_DEBUG_ON_PC

			while (!S_GJPEG_DEC_END_FLG) {
				DDIM_User_Dly_Tsk(1);
			}
			S_GJPEG_DEC_END_FLG = 0;

			if ((priv->gJpegDecMng->result & ImJpegCommon_D_IM_JPEG_PROC_END) != ImJpegCommon_D_IM_JPEG_PROC_END){
					ct_im_jpeg1_stop();
					im_jpeg_close();
					Ddim_Print(("***** Decode Error result=[0x%X] *****\n", priv->gJpegDecMng->result));
					Ddim_Print(("***** Decode Error Code=[0x%X] *****\n", priv->gJpegDecMng->errCode));
					Ddim_Print(("***** Decode Sampling type[%d] *****\n", priv->gJpegDecMng->smplType));
					return;
			}
		}

//		ct_im_jpeg1_measure_time_print();
		Ddim_Print(("***** Decode result=[0x%X] *****\n", priv->gJpegDecMng->result));
		Ddim_Print(("***** Decode Sampling type[%d] *****\n", priv->gJpegDecMng->smplType));
		Ddim_Print(("***** Decode Width[%d], Height[%d] *****\n", priv->gJpegDecMng->orgWidth, priv->gJpegDecMng->orgLines));

	}else {
		pauseSize = decParam->limitSize / 2;
		sectorCnt = (gulong)(pauseSize / 512) + 1;
		decFrmMng.codeSize = pauseSize;

		Ddim_Print(("***** pauseSize=[0x%llX] *****\n", pauseSize));

		for (i=0; i <= 1; i++) {

			if (i == 1) {
				// none limit
				decFrmMng.codeSize = 0;
				decFrmMng.codeAddr = CtImJpeg5_D_CT_JPEG_CODE_ADDR + (sectorCnt * 512);

#ifdef CO_DEBUG_ON_PC
				IO_JPG7.JCCTL.bit.JCTRG = 2;
#endif	// CO_DEBUG_ON_PC
				ret = im_jpeg_restart_dec(&decFrmMng);
				Ddim_Print(("im_jpeg_restart_dec ret=0x%X\n", ret));
				ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_DEC_FRAME, (gpointer)&decFrmMng);
				if (ret != ImJpegCommon_D_IM_JPEG_OK) {
					ct_im_jpeg1_stop();
					im_jpeg_close();
					return;
				}
			}else {
				ret = im_jpeg_ctrl_dec_frame(&decFrmMng);
				Ddim_Print(("im_jpeg_ctrl_dec_frame ret=0x%X\n", ret));
				ct_im_jpeg1_ctrl_print(CtImJpeg1_E_PRINT_CTRL_DEC_FRAME, (gpointer)&decFrmMng);
				if (ret != ImJpegCommon_D_IM_JPEG_OK) {
					im_jpeg_close();
					return;
				}

				ret = im_jpeg_start_dec();
				Ddim_Print(("im_jpeg_start_dec ret=0x%X\n", ret));
				if (ret != ImJpegCommon_D_IM_JPEG_OK) {
					im_jpeg_close();
					return;
				}
			}

			if (decParam->sync) {

#ifdef CO_DEBUG_ON_PC
				if (i == 0) {
					IO_JPG7.JPWIDTH.bit.JPWIDTH		= decParam->hSize;
					IO_JPG7.JPHEIGHT.bit.JPHEIGHT	= decParam->vSize;
					IO_JPG7.JPMODE.bit.MMODE		= (guchar)decMng.smplType;

					ctJpegDecodeIntHandler(2);

					Ddim_Print(("IO_JPG7.JPWIDTH.bit.JPWIDTH   =%d\n", IO_JPG7.JPWIDTH.bit.JPWIDTH));
					Ddim_Print(("IO_JPG7.JPHEIGHT.bit.JPHEIGHT =%d\n", IO_JPG7.JPHEIGHT.bit.JPHEIGHT));
					Ddim_Print(("IO_JPG7.JIMGSH.bit.JIMGSH     =%d\n", IO_JPG7.JIMGSH.bit.JIMGSH));
					Ddim_Print(("IO_JPG7.JIMGSV.bit.JIMGSV     =%d\n", IO_JPG7.JIMGSV.bit.JIMGSV));
					Ddim_Print(("IO_JPG7.JIMGSHDG.bit.JIMGSHDG =%d\n", IO_JPG7.JIMGSHDG.bit.JIMGSHDG));
					Ddim_Print(("IO_JPG7.JHOFFSET.bit.JHOFFSET =%d\n", IO_JPG7.JHOFFSET.bit.JHOFFSET));
					Ddim_Print(("IO_JPG7.JVOFFSET.bit.JVOFFSET =%d\n", IO_JPG7.JVOFFSET.bit.JVOFFSET));
				}else {
					ctJpegDecodeIntHandler(3);
				}
#endif	// CO_DEBUG_ON_PC
				ret = im_jpeg_wait_end_dec(&decMng, D_DDIM_WAIT_END_TIME);
				Ddim_Print(("im_jpeg_wait_end_dec ret=0x%X\n", ret));

				memcpy(&priv->gJpegDecMng, &decMng, sizeof(TimgDecMng));

				if (ret != ImJpegCommon_D_IM_JPEG_OK) {
					if (i == 0 && ret == ImJpegCommon_D_IM_JPEG_DECODE_PAUSE) {
						Ddim_Print(("Decode Pause \n"));
					}else {
						ct_im_jpeg1_stop();
						im_jpeg_close();
						Ddim_Print(("***** Decode Error result=[0x%X] *****\n", priv->gJpegDecMng->result));
						Ddim_Print(("***** Decode Error Code=[0x%X] *****\n", priv->gJpegDecMng->errCode));
						Ddim_Print(("***** Decode Sampling type[%d] *****\n", priv->gJpegDecMng->smplType));
						return;
					}
				}
			}else {

#ifdef CO_DEBUG_ON_PC
				if (i == 0) {
					IO_JPG7.JPWIDTH.bit.JPWIDTH		= decParam->hSize;
					IO_JPG7.JPHEIGHT.bit.JPHEIGHT	= decParam->vSize;
					IO_JPG7.JPMODE.bit.MMODE			= (guchar)decMng.smplType;

					ctJpegDecodeIntHandler(2);

					Ddim_Print(("IO_JPG7.JPWIDTH.bit.JPWIDTH=%d\n", IO_JPG7.JPWIDTH.bit.JPWIDTH));
					Ddim_Print(("IO_JPG7.JPHEIGHT.bit.JPHEIGHT=%d\n", IO_JPG7.JPHEIGHT.bit.JPHEIGHT));
					Ddim_Print(("IO_JPG7.JIMGSH.bit.JIMGSH=%d\n", IO_JPG7.JIMGSH.bit.JIMGSH));
					Ddim_Print(("IO_JPG7.JIMGSV.bit.JIMGSV=%d\n", IO_JPG7.JIMGSV.bit.JIMGSV));
					Ddim_Print(("IO_JPG7.JIMGSHDG.bit.JIMGSHDG=%d\n", IO_JPG7.JIMGSHDG.bit.JIMGSHDG));
					Ddim_Print(("IO_JPG7.JHOFFSET.bit.JHOFFSET=%d\n", IO_JPG7.JHOFFSET.bit.JHOFFSET));
					Ddim_Print(("IO_JPG7.JVOFFSET.bit.JVOFFSET=%d\n", IO_JPG7.JVOFFSET.bit.JVOFFSET));
				}else {
					ctJpegDecodeIntHandler(3);
				}
#endif	// CO_DEBUG_ON_PC
				while (!S_GJPEG_DEC_END_FLG) {
					DDIM_User_Dly_Tsk(1);
				}
				S_GJPEG_DEC_END_FLG = 0;

				if ((priv->gJpegDecMng->result & ImJpegCommon_D_IM_JPEG_PROC_END) != ImJpegCommon_D_IM_JPEG_PROC_END){
					if (i == 0 && (priv->gJpegDecMng->result & ImJpegCommon_D_IM_JPEG_PAUSE) \
							== ImJpegCommon_D_IM_JPEG_PAUSE) {
						Ddim_Print(("Decode Pause\n"));
					}else {
						ct_im_jpeg1_stop();
						im_jpeg_close();
						Ddim_Print(("***** Decode Error result=[0x%X] *****\n", priv->gJpegDecMng->result));
						Ddim_Print(("***** Decode Error Code=[0x%X] *****\n", priv->gJpegDecMng->errCode));
						Ddim_Print(("***** Decode Sampling type[%d] *****\n", priv->gJpegDecMng->smplType));
						return;
					}
				}
			}
		}

		Ddim_Print(("***** Decode result=[0x%X] *****\n", priv->gJpegDecMng->result));
		Ddim_Print(("***** Decode Sampling type[%d] *****\n", priv->gJpegDecMng->smplType));
		Ddim_Print(("***** Decode Width[%d], Height[%d] *****\n",
				priv->gJpegDecMng->orgWidth, priv->gJpegDecMng->orgLines));

	}
	ct_im_jpeg2_set_ycc_out_bytes(priv->jpeg2,decMng.smplType, decMng.memFormat, decFrmMng.globalYWidth,
			decFrmMng.globalCWidth, priv->gJpegDecMng->orgLines);

// ### REMOVE_RELEASE BEGIN

#ifdef CO_PT_ENABLE
	ctJpegDecodePalladiumOut(&decMng, &decFrmMng, decParam);
#endif
// ### REMOVE_RELEASE END
	ret = im_jpeg_close();
	Ddim_Print(("im_jpeg_close ret=0x%X\n", ret));
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		return;
	}
}

TimgDecMng *ct_im_jpeg4_get1(CtImJpeg4 *self)
{
	CtImJpeg4Private *priv = CT_IM_JPEG_4_GET_PRIVATE(self);
	return priv->gJpegDecMng;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImJpeg4类的一个实例
 */
CtImJpeg4* ct_im_jpeg4_new()
{
	CtImJpeg4 *self = g_object_new(CT_TYPE_IM_JPEG_4,NULL);
	return self;
}
