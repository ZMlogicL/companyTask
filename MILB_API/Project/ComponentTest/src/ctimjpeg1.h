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

#ifndef __CT_IM_JPEG_1_H__
#define __CT_IM_JPEG_1_H__

#include "./../../../fj/glib/src/gobject.h"
#include "ctimjpeg2.h"
#include "ctimjpeg6.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_JPEG_1      					(ct_im_jpeg1_get_type())
#define CT_IM_JPEG_1(obj)     						(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_JPEG_1, CtImJpeg1))
#define CT_IM_JPEG_1_CALSS(klass)   			(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_JPEG_1, CtImJpeg1Class))
#define CT_IS_IM_JPEG_1(obj)              		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_JPEG_1))
#define CT_IS_IM_JPEG_1_CLASS(klass)  		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_JPEG_1))
#define CT_IM_JPEG_1_GET_CLASS(obj)  	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_JPEG_1, CtImJpeg1Class))

#define CtImJpeg1_D_CT_JPEG_CODE_ADDR_ERR			(0xC3000000)	// JPEG code address

typedef struct _CtImJpeg1        		CtImJpeg1;
typedef struct _CtImJpeg1Class      CtImJpeg1Class;
typedef struct _CtImJpeg1Private 	CtImJpeg1Private;

typedef enum {
	CtImJpeg1_E_PRINT_CTRL_ENC_BASE	= 0,
	CtImJpeg1_E_PRINT_CTRL_ENC_FRAME,
	CtImJpeg1_E_PRINT_CTRL_DEC_BASE,
	CtImJpeg1_E_PRINT_CTRL_DEC_FRAME
} CtImJpeg1EPrintCtrl;

struct _CtImJpeg1
{
	GObject    parent;
};

struct _CtImJpeg1Class
{
	GObjectClass    parentClass;
};


GType     		  ct_im_jpeg1_get_type(void);
CtImJpeg1*     ct_im_jpeg1_new();

/**********私有变公有区域***********/
void ct_im_jpeg1_start_hclock(CtImJpeg1 *self);
void ct_im_jpeg1_stop_hclock(CtImJpeg1 *self);
void ct_im_jpeg1_ctrl_print(CtImJpeg1EPrintCtrl ptn, gpointer ctrl);
void ct_im_jpeg1_stop(void);
void ct_im_jpeg1_encode_cb(TImJpegEncMng* pjpgEncMng);
void ct_im_jpeg1_encode(CtImJpeg1 *self,CtImJpeg6* encParam, guchar setQualv);
#ifdef CO_DEBUG_ON_PC
void ct_im_jpeg1_encode_int_handler(guchar ptn);
#endif
/*********************************/
#if 0	// measure_time disable.
kint32 	ct_im_jpeg1_measure_time_start(void);
kint32 	ct_im_jpeg1_measure_time_print(void);
#endif
guchar ct_im_jpeg1_get1(CtImJpeg1 *self);
gulong ct_im_jpeg1_get2(CtImJpeg1 *self);
gulong ct_im_jpeg_get_enc_size(CtImJpeg1 *self);
gulong ct_im_jpeg_get_output_bytes(CtImJpeg1 *self);
gulong ct_im_jpeg1_get3(CtImJpeg1 *self);
guchar ct_im_jpeg1_get4(CtImJpeg1 *self);
void 	ct_im_jpeg1_set2(CtImJpeg1 *self,gulong Encode_Size);
void	ct_im_jpeg1_set3(CtImJpeg1 *self,gulong outputBytes);
void 	ct_im_jpeg1_set4(CtImJpeg1 *self,gulong gJpeg_AXI_Err);


G_END_DECLS
#endif /* __CT_IM_JPEG_1_H_ */

