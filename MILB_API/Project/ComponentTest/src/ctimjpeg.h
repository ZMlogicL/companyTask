/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImJpeg类
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#ifndef __CT_IM_JPEG_H__
#define __CT_IM_JPEG_H__

#include "./../../../fj/glib/src/gobject.h"
#include "ctimjpeg3.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_JPEG            			(ct_im_jpeg_get_type())
#define CT_IM_JPEG(obj)               			(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_JPEG, CtImJpeg))
#define CT_IM_JPEG_CALSS(klass)  			(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_JPEG, CtImJpegClass))
#define CT_IS_IM_JPEG(obj)             		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_JPEG))
#define CT_IS_IM_JPEG_CLASS(klass)   	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_JPEG))
#define CT_IM_JPEG_GET_CLASS(obj) 		(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_JPEG, CtImJpegClass))

typedef struct _CtImJpeg              	CtImJpeg;
typedef struct _CtImJpegClass       	CtImJpegClass;
typedef struct _CtImJpegPrivate    	CtImJpegPrivate;

typedef enum {
	CtImJpeg_CR_4_0     	= (gshort )0x0000,	/**< CR 4.0	*/
	CtImJpeg_CR_4_5     	= (gshort )0x0001,	/**< CR 4.5	*/
	CtImJpeg_CR_5_0     	= (gshort )0x0002,	/**< CR 5.0	*/
	CtImJpeg_CR_5_5     	= (gshort )0x0003,	/**< CR 5.5	*/
	CtImJpeg_CR_6_0    	= (gshort )0x0004,	/**< CR 6.0	*/
	CtImJpeg_CR_6_5     	= (gshort )0x0005,	/**< CR 6.5	*/
	CtImJpeg_CR_7_0     	= (gshort )0x0006,	/**< CR 7.0	*/
	CtImJpeg_CR_7_5     	= (gshort )0x0007,	/**< CR 7.5	*/
	CtImJpeg_CR_8_0      	= (gshort )0x0008,	/**< CR 8.0	*/
	CtImJpeg_CR_8_5     	= (gshort )0x0009,	/**< CR 8.5	*/
	CtImJpeg_CR_9_0     	= (gshort )0x000A,	/**< CR 9.0	*/
	CtImJpeg_CR_9_5     	= (gshort )0x000B,	/**< CR 9.5	*/
	CtImJpeg_CR_10_0   	= (gshort )0x000C,	/**< CR 10.0	*/
	CtImJpeg_CR_12_0   	= (gshort )0x000D,	/**< CR 12.0	*/
	CtImJpeg_CR_14_0   	= (gshort )0x000E,	/**< CR 14.0	*/
	CtImJpeg_CR_16_0   	= (gshort )0x000F,	/**< CR 16.0	*/
	CtImJpeg_CR_17_0  	= (gshort )0x0010,	/**< CR 17.0	*/
	CtImJpeg_CR_18_0   	= (gshort )0x0011,	/**< CR 18.0	*/
	CtImJpeg_CR_19_0    	= (gshort )0x0012,	/**< CR 19.0	*/
	CtImJpeg_CR_20_0    	= (gshort )0x0013,	/**< CR 20.0	*/
	CtImJpeg_CR_21_0     	= (gshort )0x0014,	/**< CR 21.0	*/
	CtImJpeg_CR_22_0    	= (gshort )0x0015,	/**< CR 22.0	*/
	CtImJpeg_CR_23_0    	= (gshort )0x0016,	/**< CR 23.0	*/
	CtImJpeg_CR_24_0   	= (gshort )0x0017,	/**< CR 24.0	*/
	CtImJpeg_CR_25_0   	= (gshort )0x0018,	/**< CR 25.0	*/
	CtImJpeg_CR_26_0   	= (gshort )0x0019,	/**< CR 26.0	*/
	CtImJpeg_CR_27_0   	= (gshort )0x001A,	/**< CR 27.0	*/
	CtImJpeg_CR_28_0    	= (gshort )0x001B,	/**< CR 28.0	*/
	CtImJpeg_CR_29_0  	= (gshort )0x001C,	/**< CR 29.0	*/
	CtImJpeg_CR_30_0   	= (gshort )0x001D,	/**< CR 30.0	*/
	CtImJpeg_CR_31_0   	= (gshort )0x001E,	/**< CR 31.0	*/
	CtImJpeg_CR_32_0   	= (gshort )0x001F,	/**< CR 32.0	*/
	CtImJpeg_CR_33_0   	= (gshort )0x0020,	/**< CR 33.0	*/
	CtImJpeg_CR_34_0   	= (gshort )0x0021,	/**< CR 34.0	*/
	CtImJpeg_CR_35_0   	= (gshort )0x0022,	/**< CR 35.0	*/
	CtImJpeg_CR_36_0   	= (gshort )0x0023,	/**< CR 36.0	*/
	CtImJpeg_CR_37_0   	= (gshort )0x0024,	/**< CR 37.0	*/
	CtImJpeg_CR_38_0   	= (gshort )0x0025,	/**< CR 38.0	*/
	CtImJpeg_CR_39_0  	= (gshort )0x0026,	/**< CR 39.0	*/
	CtImJpeg_CR_40_0   	= (gshort )0x0027,	/**< CR 40.0	*/
	CtImJpeg_CR_3_0     	= (gshort )0x0028,	/**< CR 3.0	*/
	CtImJpeg_CR_3_5    	= (gshort )0x0029,	/**< CR 3.5	*/
	CtImJpeg_CR_2_0  		= (gshort )0x002A,	/**< CR 2.0	*/
	CtImJpeg_CR_2_5  		= (gshort )0x002B,	/**< CR 2.5	*/
	CtImJpeg_CR_2_7  		= (gshort )0x002C	/**< CR 2.7	*/
} CtImJpegCompressionRatio;

struct _CtImJpeg
{
	GObject    parent;
	// Downsample type (Parameter of Im_JPEG_Set_Down_Sampling_Rate())
	guchar			downSpType;
	// Maximum retry count. (1~D_JPGEPC_RETRY_MAX_COUNT)
	guchar			maxRetry;
	// Shift value.
	guint32		shift;
	// Target ratio.
	guint32		ratio;
	// Target bytes.
	gulong			targetBytes;
};

struct _CtImJpegClass
{
	GObjectClass    parentClass;
};


GType     		ct_im_jpeg_get_type(void);
CtImJpeg*	ct_im_jpeg_new();

gulong 		ct_im_jpeg_special_encode(CtImJpeg *self,CtImJpeg3* jpgencParam);
gint16 			ct_im_jpeg_get_encode_quality( gushort cr );
gulong 		ct_im_jpeg_get_ycc_addr(void);
gulong 		ct_im_jpeg_get_code_addr(void);


G_END_DECLS
#endif /* __CT_IM_JPEG_H_ */

