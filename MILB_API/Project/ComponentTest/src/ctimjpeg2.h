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
*1.0.0
*/

#ifndef __CT_IM_JPEG_2_H__
#define __CT_IM_JPEG_2_H__

#include "./../../../fj/glib/src/gobject.h"
#include "imjpegcommon.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_JPEG_2                   		(ct_im_jpeg2_get_type())
#define CT_IM_JPEG_2(obj)               			(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_JPEG_2, CtImJpeg2))
#define CT_IM_JPEG_2_CALSS(klass)        	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_JPEG_2, CtImJpeg2Class))
#define CT_IS_IM_JPEG_2(obj)                     (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_JPEG_2))
#define CT_IS_IM_JPEG_2_CLASS(klass)    	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_JPEG_2))
#define CT_IM_JPEG_2_GET_CLASS(obj)    	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_JPEG_2, CtImJpeg2Class))

#define CtImJpeg2_D_CT_JPEG_CODE_ADDR2		(0xB4000000)	// JPEG code address
#define CtImJpeg2_D_CT_JPEG_YCC_ADDR_ERR		(0xC1000000)	// YCC address (edit to Y address)
#define CtImJpeg2_D_CT_JPEG_CODE_SIZE_VGA	(0x0001733B)	// (edit with test JPEG file)
#define CtImJpeg2_D_CT_JPEG_CODE_SIZE_3M		(0x197A90)		// (edit with test JPEG file)
#define CtImJpeg2_D_CT_JPEG_SIZE_12M_H			(4000)
#define CtImJpeg2_D_CT_JPEG_SIZE_12M_V			(3000)
#define CtImJpeg2_D_CT_JPEG_CODE_SIZE_12M				(0x4632A0)
#define CtImJpeg2_D_CT_JPEG_CODE_SIZE_12M_GRAY		(0x2FA350)
#define CtImJpeg2_D_CT_JPEG_SIZE_12M_LIMIT				(0)

typedef struct _CtImJpeg2                  	CtImJpeg2;
typedef struct _CtImJpeg2Class        	CtImJpeg2Class;
typedef struct _CtImJpeg2Private     	CtImJpeg2Private;


struct _CtImJpeg2
{
	GObject    parent;
};

struct _CtImJpeg2Class
{
	GObjectClass    parentClass;
};


GType     		  	ct_im_jpeg2_get_type(void);
CtImJpeg2*     ct_im_jpeg2_new();

void 	ct_im_jpeg2_set_ycc_out_bytes(CtImJpeg2 *self,const EimgSmplType smplType,
			const EimgMemForm memFormat,
			const gulong globalYWidth, const gulong globalCWidth, const gulong lines);
void 	ct_im_jpeg2_main(CtImJpeg2 *self,gint32 argc, gchar** argv);


G_END_DECLS
#endif /* __CT_IM_JPEG_2_H_ */

