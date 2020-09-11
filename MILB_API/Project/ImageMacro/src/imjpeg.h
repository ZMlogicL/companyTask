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


#ifndef __IM_JPEG_H__
#define __IM_JPEG_H__


#include <klib.h>
#include "driver_common.h"
#include "imjpegcommon.h"


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_JPEG					(im_jpeg_get_type())
#define IM_JPEG	(obj)					(K_TYPE_CHECK_INSTANCE_CAST(obj, ImJpeg))
#define IM_IS_JPEG(obj)				(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_JPEG))


typedef struct _ImJpeg 					ImJpeg;
typedef struct _ImJpegPrivate 	ImJpegPrivate;


struct _ImJpeg
{
	KObject parent;
};


KConstType 		    im_jpeg_get_type(void);
ImJpeg*		        	im_jpeg_new(void);
void 						im_jpeg_on_clk(ImJpeg*self);
void 						im_jpeg_off_clk(ImJpeg*self);
void 						im_jpeg_on_hclk(ImJpeg*self);
void 						im_jpeg_off_hclk(ImJpeg*self);
void 						im_jpeg_on_iclk( ImJpeg*self );
void	 					im_jpeg_off_iclk( ImJpeg*self );
void 						im_jpeg_reset( ImJpeg*self );
void 						im_jpeg_set_quant_tbl(ImJpeg*self, TimgQuatTblPack* pQuantTbl );
void 						im_jpeg_set_next_quant_tbl(ImJpeg*self, TimgQuatTblPack* pQuantTbl );
void 						im_jpeg_sub_int_handler_enc_core_qtwint(ImJpeg*self, kint32* result );
void 						im_jpeg_sub_int_handler_enc_core_end(ImJpeg*self, kint32* result );
void 						im_jpeg_sub_int_handler_dec_core_errint(ImJpeg*self, kint32* result );
kint32 						im_jpeg_sub_int_handler_dec_core_regrdint(ImJpeg*self, kint32* result );
void 						im_jpeg_sub_int_handler_dec_core_end(ImJpeg*self, kint32* result );
void 						im_jpeg_sub_int_handler_dec_core_segint(ImJpeg*self, kint32* result );
void 						im_jpeg_sub_int_handler_dec_core_mkint(ImJpeg*self, kint32* result );


#ifdef __cplusplus
}
#endif


#endif /* __IM_JPEG_H__ */
/*@}*/
/**
@weakgroup im_jpeg
@{
<hr>
@section JPEG_DECODE	Sample code for jpeg decode.
@code
// SAMPLE CODE //
kint32 jpeg_decode_sample()
{
	kint32					ret = 0;
	kint32					result = 0;
	TimgDecMng		jpgmng;
	TimgDecFrameMng	jpg_frm_mng;

	memset( &jpgmng, 0, sizeof(TimgDecMng) );
	memset( &jpg_frm_mng, 0, sizeof(TimgDecFrameMng) );

	jpgmng.extMode				= ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	jpgmng.corrMode			= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	jpgmng.skipMkFlg			= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	jpgmng.smplType			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;
	jpgmng.pcallback			= NULL;

	jpg_frm_mng.globalYWidth	= 4000;
	jpg_frm_mng.globalCWidth	= 2000;
	jpg_frm_mng.cutoutFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	jpg_frm_mng.yccAddr.y		= 0x83000000;	// Y
	jpg_frm_mng.yccAddr.c		= 0x83200000;	// C
	jpg_frm_mng.codeAddr		= 0x81000000;
	jpg_frm_mng.codeSize		= 0;

	ret = im_jpeg_open( D_DDIM_SEM_WAIT_FEVR );
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_open error! ercd = %d\n", ret));
		return ret;
	}

	ret = im_jpeg_ctrl_dec(&jpgmng);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		im_jpeg_close(NULL);
		Ddim_Print(("im_jpeg_ctrl_dec error! ercd = %d\n", ret));
		return ret;
	}

	ret = im_jpeg_ctrl_dec_frame(&jpg_frm_mng);
	if (ret == ImJpegCommon_D_IM_JPEG_OK) {
		im_jpeg_close(NULL);
		Ddim_Print(("im_jpeg_ctrl_dec_frame error! ercd = %d\n", ret));
		return ret;
	}

	ret = im_jpeg_start_dec(NULL);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		im_jpeg_close(NULL);
		Ddim_Print(("im_jpeg_start_dec error! ercd = %d\n", ret));
		return ret;
	}

	ret = im_jpeg_wait_end_dec(&jpgmng, D_DDIM_WAIT_END_TIME);
	if (ret == ImJpegCommon_D_IM_JPEG_OK) {
		if ( ret == D_IM_JPEG_AXI_ERROR ) {
			Ddim_Print(("im_jpeg_wait_end_dec AXI error! ercd = %d\n", ret));
		}
		else if ( ret == ImJpegCommon_D_IM_JPEG_DECODE_PAUSE ) {
			Ddim_Print(("im_jpeg_wait_end_dec Code size over error! ercd = %d\n", ret));
		}
		else {
			Ddim_Print(("im_jpeg_wait_end_dec Decode error! ercd = %d\n", ret));
		}
		im_jpeg_stop();
	}

	// JPEG Close
	ret = im_jpeg_close(NULL);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_close error! ercd = %d\n", result));
	}

	return ret;
}
@endcode

@section JPEG_ENCODE	Sample code for jpeg encode.
@code
// SAMPLE CODE //
kint32 jpeg_encode_sample()
{
	kint32					ret = 0;
	TimgEncMng		jpg_mng;
	TimgEncFrameMng	jpg_frm_mng;

	memset( &jpg_mng, 0, sizeof(TimgEncMng));
	memset( &jpg_frm_mng, 0, sizeof(TimgEncFrameMng));

	// set encode param
	jpg_mng.yccSmpl			= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;
	jpg_mng.width				= 4000;
	jpg_mng.lines				= 3000;
	jpg_mng.skipMkFlg			= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	jpg_mng.driMkNum			= 0;
	jpg_mng.exifFmtFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_ON;
	jpg_mng.pintLine			= 0;
	jpg_mng.pintSect			= 0;
	jpg_mng.jburstLength		= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;
	jpg_mng.pburstLength		= ImJpegCommon_E_IM_JPEG_BURST_INCR_8;

	// Y Component parameter
	jpg_mng.component[0].quantTblNo  = 0;	// Select Qunatization table No. for Y
	jpg_mng.component[0].hufDcTblNo = 0;	// Select DC Huffman table No. for Y
	jpg_mng.component[0].hufAcTblNo = 0;	// Select AC Huffman table No. for Y
	// Cb Component parameter
	jpg_mng.component[1].quantTblNo  = 1;	// Select Qunatization table No. for Cb
	jpg_mng.component[1].hufDcTblNo = 1;	// Select DC Huffman table No. for Cb
	jpg_mng.component[1].hufAcTblNo = 1;	// Select AC Huffman table No. for Cb
	// Cr Component parameter
	jpg_mng.component[2].quantTblNo  = 1;	// Select Qunatization table No. for Cr
	jpg_mng.component[2].hufDcTblNo = 1;	// Select DC Huffman table No. for Cr
	jpg_mng.component[2].hufAcTblNo = 1;	// Select AC Huffman table No. for Cr

	jpg_frm_mng.globalYWidth		= 4000;
	jpg_frm_mng.globalCWidth		= 2000;
	jpg_frm_mng.yccAddr.y			= 0x83000000;
	jpg_frm_mng.yccAddr.c			= 0x83200000;
	jpg_frm_mng.codeAddr			= 0x81000000;
	jpg_frm_mng.codeCountFlg		= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	jpg_frm_mng.codeOverCountFlg	= ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	jpg_frm_mng.limitSize			= 0x20000;

	ret = im_jpeg_open( D_DDIM_SEM_WAIT_FEVR );
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_open error! ercd = %d\n", ret));
		return ret;
	}

	// set quantization table of the default.
	im_jpeg_set_qtbl(NULL, NULL, 0 );

	// set base configuration for encode
	ret = im_jpeg_ctrl_enc(&jpg_mng);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		im_jpeg_close(NULL);
		Ddim_Print(("im_jpeg_ctrl_enc error! ercd = %d\n", ret));
		return ret;
	}

	// set frame configuration for encode
	ret = im_jpeg_ctrl_enc_frame(&jpg_frm_mng);
	if (ret == ImJpegCommon_D_IM_JPEG_OK) {
		im_jpeg_close(NULL);
		Ddim_Print(("im_jpeg_ctrl_enc_frame error! ercd = %d\n", ret));
		return ret;
	}

	// encode start
	ret = im_jpeg_start_enc();
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		im_jpeg_close(NULL);
		Ddim_Print(("im_jpeg_start_enc error! ercd = %d\n", ret));
		return ret;
	}

	// wait the process end
	ret = im_jpeg_wait_end_enc(&jpg_mng, D_DDIM_WAIT_END_TIME);
	if (ret == ImJpegCommon_D_IM_JPEG_OK) {
		if ( ret == D_IM_JPEG_AXI_ERROR ) {
			Ddim_Print(("im_jpeg_wait_end_enc AXI error! ercd = %d\n", ret));
		}
		else if ( ret == ImJpegCommon_D_IM_JPEG_ENCODE_PAUSE ) {
			Ddim_Print(("im_jpeg_wait_end_enc Code size over error! ercd = %d\n", ret));
		}
		else {
			Ddim_Print(("im_jpeg_wait_end_enc Encode error! ercd = %d\n", ret));
		}
		im_jpeg_stop();
	}

	ret = im_jpeg_close(NULL);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_close error! ercd = %d\n", ret));
		return ret;
	}

	return ImJpegCommon_D_IM_JPEG_OK;
}
@endcode

@section JPEG_DECODE_UTIL	Sample code for jpeg decode(util).
@code
// SAMPLE CODE //
kint32 jpeg_simplicity_decode_sample()
{
	kint32					result;
	TimgDecInput		inputParam;
	TimgDecOutput	outputParam;

	memset( &inputParam, 0, sizeof(TimgDecInput) );
	memset( &outputParam, 0, sizeof(TimgDecOutput) );

	// set jpeg addr
	inputParam.globalYWidth	= 3648;
	inputParam.globalCWidth	= (3648 >> 1);
	inputParam.codeAddr		= 0x83000000;
	inputParam.smplType		= ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422;

	// set output(Y,Cb,Cr) addr
	inputParam.dstYccAddr.y  = 0x81000000;
	inputParam.dstYccAddr.c	= inputParam.dstYccAddr.y + (3648 * 2736);

	// set code size
	inputParam.codeSize		= 0;	// no limit

	// decode start
	result = im_jpeg_decode_sync(&inputParam, &outputParam);
	if(result != ImJpegCommon_D_IM_JPEG_OK) {

		// Analysis of the "outputParam.errCode"

		// Error processing
		Ddim_Print(("im_jpeg_decode_sync error! ercd = %d\n", result));
		return result;
	}
	return ImJpegCommon_D_IM_JPEG_OK;
}
@endcode

@}*/

/*	@}*/
/*@}*/
