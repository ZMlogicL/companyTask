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

#ifndef __CT_IM_JPEG_5_H__
#define __CT_IM_JPEG_5_H__

#include "./../../../fj/glib/src/gobject.h"
#include "ctimjpeg3.h"
#include "ctimjpeg6.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_JPEG_5              			(ct_im_jpeg5_get_type())
#define CT_IM_JPEG_5(obj)             				(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_JPEG_5, CtImJpeg5))
#define CT_IM_JPEG_5_CALSS(klass)      	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_JPEG_5, CtImJpeg5Class))
#define CT_IS_IM_JPEG_5(obj)                  	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_JPEG_5))
#define CT_IS_IM_JPEG_5_CLASS(klass)     	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_JPEG_5))
#define CT_IM_JPEG_5_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_JPEG_5, CtImJpeg5Class))

#define CtImJpeg5_D_CT_JPEG_SIZE_3M_LIMIT		(0)
#define CtImJpeg5_D_CT_JPEG_YCC_ADDR				(0xB8000000)	// YCC address (edit to Y address)
#define CtImJpeg5_D_CT_JPEG_CODE_ADDR			(0xB0000000)	// JPEG code address
#define CtImJpeg5_D_CT_JPEG_SIZE_VGA_H			(640)
#define CtImJpeg5_D_CT_JPEG_SIZE_VGA_V			(480)
#define CtImJpeg5_D_CT_JPEG_SIZE_3M_H				(2048)
#define CtImJpeg5_D_CT_JPEG_SIZE_3M_V				(1536)
#define CtImJpeg5_D_CT_JPEG_CODE_SIZE_16M	(0x99DE60)		// (edit with test JPEG file)
#define CtImJpeg5_D_CT_JPEG_CODE_SIZE_16M_GRAY	(0x2FA350)	// (edit with test JPEG file)
#define CtImJpeg5_D_CT_JPEG_SIZE_16M_LIMIT	(0)
#define CtImJpeg5_D_CT_JPEG_LIMIT_MAX			(0)
#define CtImJpeg5_D_CT_JPEG_LIMIT_SIZE		\
		(CtImJpeg3_D_CT_JPEG_SIZE_16M_H * CtImJpeg3_D_CT_JPEG_SIZE_16M_V)
#define CtImJpeg5_D_CT_JPEG_TEST_SIZE_H				CtImJpeg3_D_CT_JPEG_SIZE_16M_H
#define CtImJpeg5_D_CT_JPEG_TEST_SIZE_V				CtImJpeg3_D_CT_JPEG_SIZE_16M_V
#define CtImJpeg5_D_CT_JPEG_TEST_CODE				CtImJpeg5_D_CT_JPEG_CODE_SIZE_16M
#define CtImJpeg5_D_CT_JPEG_TEST_CODE_GRAY		CtImJpeg5_D_CT_JPEG_CODE_SIZE_16M_GRAY
#define CtImJpeg5_D_CT_JPEG_TEST_SIZE_LIMIT		CtImJpeg5_D_CT_JPEG_SIZE_16M_LIMIT


typedef struct _CtImJpeg5              	CtImJpeg5;
typedef struct _CtImJpeg5Class    	CtImJpeg5Class;
typedef struct _CtImJpeg5Private  	CtImJpeg5Private;


struct _CtImJpeg5
{
	GObject    parent;
	guchar			sync;
	CtImJpeg6ECtTJpegFormat		format;
	gulong			gYWidth;
	gulong			gYLines;
	gulong			gCWidth;
	gushort		hSize;
	gushort		vSize;
	guchar			cutOutFlg;
	gushort		cutHSize;
	gushort		cutVSize;
	gulonglong		limitSize;
	EimgResizeExt		ext;
	guchar			corrFlg;
	guchar			pauseFlg;
};

struct _CtImJpeg5Class
{
	GObjectClass    parentClass;
};


GType     		  	ct_im_jpeg5_get_type(void);
CtImJpeg5*     ct_im_jpeg5_new();

void ct_im_jpeg5_1_3_1(CtImJpeg5 *self);
void ct_im_jpeg5_1_3_2( CtImJpeg5 *self);
void ct_im_jpeg5_1_3_3(CtImJpeg5 *self);
void ct_im_jpeg5_1_3_4(CtImJpeg5 *self);
void ct_im_jpeg5_1_4_14(CtImJpeg5 *self);
void ct_im_jpeg5_1_4_2(CtImJpeg5 *self);
void ct_im_jpeg5_1_4_3(CtImJpeg5 *self);
void ct_im_jpeg5_1_4_4(CtImJpeg5 *self);
void ct_im_jpeg5_1_4_5(CtImJpeg5 *self);
void ct_im_jpeg5_1_4_6(CtImJpeg5 *self);
void ct_im_jpeg5_1_4_7(CtImJpeg5 *self);
void ct_im_jpeg5_1_4_8(CtImJpeg5 *self);
void ct_im_jpeg5_1_4_9(CtImJpeg5 *self);
void ct_im_jpeg5_1_4_10(CtImJpeg5 *self);
void ct_im_jpeg5_1_4_11(CtImJpeg5 *self);
void ct_im_jpeg5_1_4_13(CtImJpeg5 *self);
void ct_im_jpeg5_2_3_1(CtImJpeg5 *self);
void ct_im_jpeg5_2_3_2(CtImJpeg5 *self);


G_END_DECLS
#endif /* __CT_IM_JPEG_5_H_ */

