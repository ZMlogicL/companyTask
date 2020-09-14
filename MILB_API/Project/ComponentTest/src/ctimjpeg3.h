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

#ifndef __CT_IM_JPEG_3_H__
#define __CT_IM_JPEG_3_H__

#include "./../../../fj/glib/src/gobject.h"
#include "ctimjpeg1.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_JPEG_3                          	(ct_im_jpeg3_get_type())
#define CT_IM_JPEG_3(obj)                     			(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_JPEG_3, CtImJpeg3))
#define CT_IM_JPEG_3_CALSS(klass)        		(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_JPEG_3, CtImJpeg3Class))
#define CT_IS_IM_JPEG_3(obj)                      	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_JPEG_3))
#define CT_IS_IM_JPEG_3_CLASS(klass)        	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_JPEG_3))
#define CT_IM_JPEG_3_GET_CLASS(obj)       	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_JPEG_3, CtImJpeg3Class))

#define CtImJpeg3_D_CT_JPEG_SIZE_16M_H			(4608)
#define CtImJpeg3_D_CT_JPEG_SIZE_16M_V			(3456)

typedef struct _CtImJpeg3                          		CtImJpeg3;
typedef struct _CtImJpeg3Class                    	CtImJpeg3Class;
typedef struct _CtImJpeg3Private                  	CtImJpeg3Private;

typedef enum {
	CtImJpeg3_T_CT_IM_JPG_SPENC_MODE_CAPTURE = 0,
	CtImJpeg3_T_CT_IM_JPG_SPENC_MODE_PLAY,
	CtImJpeg3_T_CT_IM_JPG_SPENC_MODE_MOVIE,
	CtImJpeg3_T_CT_IM_JPG_SPENC_MODE_MAX,
} CtImJpeg3TCtImJpgSpencMode;

struct _CtImJpeg3
{
	GObject    parent;
    // Parameter of Im_JPEG_Ctrl_Enc().
	TimgEncMng				jpegEncTbl;
	// Parameter of Im_JPEG_Ctrl_Enc_Frame().
	TimgEncFrameMng	jpegEncFrameTbl;
	// Encode mode (parameter of Jpgepc_Wrap_Set_Tuning_Param()).
	CtImJpeg3TCtImJpgSpencMode		mode;
	// Maximum bytes of JPEG code.
	gulong			limitSize;
	// Quality value of JPEG code when encode is successful. (In/Out)
	gushort		quality;
};

struct _CtImJpeg3Class
{
	GObjectClass    parentClass;
};


GType     		  	ct_im_jpeg3_get_type(void);
CtImJpeg3*  	ct_im_jpeg3_new();

void ct_Im_jpeg3_run1(CtImJpeg3 *self,gint32 ctParam1, gint32 ctParam2);
void ct_im_jpeg3_set1(CtImJpeg3 *self,CtImJpeg1 *outputBytes);


G_END_DECLS
#endif /* __CT_IM_JPEG_3_H_ */

