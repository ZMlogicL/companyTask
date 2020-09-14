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

#ifndef __CT_IM_JPEG_4_H__
#define __CT_IM_JPEG_4_H__

#include "ctimjpeg5.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_JPEG_4            			(ct_im_jpeg4_get_type())
#define CT_IM_JPEG_4(obj)                  		(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_JPEG_4, CtImJpeg4))
#define CT_IM_JPEG_4_CALSS(klass)      		(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_JPEG_4, CtImJpeg4Class))
#define CT_IS_IM_JPEG_4(obj)             		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_JPEG_4))
#define CT_IS_IM_JPEG_4_CLASS(klass)   	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_JPEG_4))
#define CT_IM_JPEG_4_GET_CLASS(obj) 		(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_JPEG_4, CtImJpeg4Class))


typedef struct _CtImJpeg4            		CtImJpeg4;
typedef struct _CtImJpeg4Class      	 	CtImJpeg4Class;
typedef struct _CtImJpeg4Private 		CtImJpeg4Private;


struct _CtImJpeg4
{
	GObject    parent;
};

struct _CtImJpeg4Class
{
	GObjectClass    parentClass;
};


GType     		  	ct_im_jpeg4_get_type(void);
CtImJpeg4*		ct_im_jpeg4_new();

void ct_im_jpeg4_run2(CtImJpeg4 *self,gint32 ctParam1, gint32 ctParam2);
void ct_im_jpeg4_decode_cb(TimgDecMng* pJpgDecMng);
void ct_im_jpeg4_decode(CtImJpeg4 *self,CtImJpeg5* decParam);
TimgDecMng *ct_im_jpeg4_get1(CtImJpeg4 *self);


G_END_DECLS
#endif /* __CT_IM_JPEG_4_H_ */

