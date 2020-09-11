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

#ifndef __CT_IM_JPEG_6_H__
#define __CT_IM_JPEG_6_H__

#include "./../../../fj/glib/src/gobject.h"
#include "driver_common.h"
#include "imjpegcommon.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_JPEG_6                 		(ct_im_jpeg6_get_type())
#define CT_IM_JPEG_6(obj)                 			(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_JPEG_6, CtImJpeg6))
#define CT_IM_JPEG_6_CALSS(klass)    		(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_JPEG_6, CtImJpeg6Class))
#define CT_IS_IM_JPEG_6(obj)           			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_JPEG_6))
#define CT_IS_IM_JPEG_6_CLASS(klass) 		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_JPEG_6))
#define CT_IM_JPEG_6_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_JPEG_6, CtImJpeg6Class))

#define CtImJpeg6_D_CT_JPEG_SIZE_VGA_LIMIT	(0)

typedef struct _CtImJpeg6              		CtImJpeg6;
typedef struct _CtImJpeg6Class       	CtImJpeg6Class;
typedef struct _CtImJpeg6Private    	CtImJpeg6Private;

typedef enum {
	// 444 plane
	CtImJpeg6_E_CT_JPEG_FORMAT_444P	= 0,
	// 422 plane
	CtImJpeg6_E_CT_JPEG_FORMAT_422P,
	// 422 plane & dot
	CtImJpeg6_E_CT_JPEG_FORMAT_422PD,
	// 400 plane
	CtImJpeg6_E_CT_JPEG_FORMAT_420P,
	// 400 plane & dot
	CtImJpeg6_E_CT_JPEG_FORMAT_420PD,
	// 400 plane
	CtImJpeg6_E_CT_JPEG_FORMAT_400P,
	// RGB
	CtImJpeg6_E_CT_JPEG_FORMAT_RGBP
} CtImJpeg6ECtTJpegFormat;

struct _CtImJpeg6
{
	GObject    parent;
	guchar		sync;
	CtImJpeg6ECtTJpegFormat	format;
	gulong		gYWidth;
	gulong		gYLines;
	gulong		gCWidth;
	gushort	hSize;
	gushort	vSize;
	gulonglong	limitSize;
	guchar		pauseFlg;
	guchar		countFlg;
	guchar		quantupFlg;
	guchar		skipMkFlg;
	guchar		dri;
	guchar		dspRate;
};

struct _CtImJpeg6Class
{
	GObjectClass    parentClass;
};


GType     		  	ct_im_jpeg6_get_type(void);
CtImJpeg6*		ct_im_jpeg6_new();

void ct_im_jpeg6_1_3_5(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_6(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_7(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_8(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_9(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_10(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_11(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_12(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_13(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_14(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_15(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_16(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_17(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_18(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_19(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_20(CtImJpeg6 *self);
void ct_im_jpeg6_1_3_21(CtImJpeg6 *self);
void ct_im_jpeg6_1_5_1(CtImJpeg6 *self);


G_END_DECLS
#endif /* __CT_IM_JPEG_6_H_ */

