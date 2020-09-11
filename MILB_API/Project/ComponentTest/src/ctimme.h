/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __CT_IM_ME_H__
#define __CT_IM_ME_H__

#include "driver_common.h"
#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_ME            	(ct_im_me_get_type())
#define CT_IM_ME(obj)            	(G_TYPE_CHECK_INSTANCE_CAST(obj,CtImMe))
#define CT_IM_ME_CLASS(kclass)   	(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_ME, CtImMeClass))
#define CT_IS_IM_ME(obj)         	(G_TYPE_CHECK_INSTANCE_TYPE(obj,CT_TYPE_IM_ME))
#define CT_IS_IM_ME_CLASS(kclass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_ME))
#define CT_IM_ME_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_ME, CtImMeClass))

#define CtImMe_D_IM_ME_SRC_IMG_PIXS_WIDTH_YCC_4K2K_REF		(3840)
#define CtImMe_D_IM_ME_SRC_IMG_PIXS_LINES_YCC_4K2K_REF		(2160)
#define CtImMe_D_IM_ME_SRC_IMG_PIXS_WIDTH_YCC_4K2K_STD		(3840 + 32 * 2)
#define CtImMe_D_IM_ME_SRC_IMG_PIXS_LINES_YCC_4K2K_STD		(2160 + 32 * 2)

#define CtImMe_D_IM_ME_DST_IMG_PIXS_WIDTH_HEVC				(3840)		// [A]HEVC   4K2K
#define CtImMe_D_IM_ME_DST_IMG_PIXS_LINES_HEVC				(2160)		// [A]HEVC   4K2K

#define CtImMe_D_IM_ME_IMG_MEM_IN0_ADDR_TOP				(0x48000000)
#define CtImMe_D_IM_ME_IMG_MEM_IN1_ADDR_TOP				(0x49000000)

#define CtImMe_D_IM_ME_IMG_MEM_OUT0_ADDR_TOP				(0x4A000000)
#define CtImMe_D_IM_ME_IMG_MEM_OUT_HEVC_ADDR_TOP		(CtImMe_D_IM_ME_IMG_MEM_OUT0_ADDR_TOP)
#define CtImMe_D_IM_ME_IMG_MEM_IN_YCC_REF_ADDR_TOP		(CtImMe_D_IM_ME_IMG_MEM_IN0_ADDR_TOP)
#define CtImMe_D_IM_ME_IMG_MEM_IN_YCC_STD_ADDR_TOP		(CtImMe_D_IM_ME_IMG_MEM_IN1_ADDR_TOP)

#define CtImMe_D_IM_ME_IMG_MEM_IN_YCC_REF_ADDR_Y		(CtImMe_D_IM_ME_IMG_MEM_IN_YCC_REF_ADDR_TOP)
#define CtImMe_D_IM_ME_IMG_MEM_IN_YCC_REF_ADDR_C		(CtImMe_D_IM_ME_IMG_MEM_IN_YCC_REF_ADDR_Y + \
														(CtImMe_D_IM_ME_SRC_IMG_PIXS_WIDTH_YCC_4K2K_REF * \
														CtImMe_D_IM_ME_SRC_IMG_PIXS_LINES_YCC_4K2K_REF))

#define CtImMe_D_IM_ME_IMG_MEM_IN_YCC_STD_ADDR_Y		(CtImMe_D_IM_ME_IMG_MEM_IN_YCC_STD_ADDR_TOP)
#define CtImMe_D_IM_ME_IMG_MEM_IN_YCC_STD_ADDR_C		(CtImMe_D_IM_ME_IMG_MEM_IN_YCC_STD_ADDR_Y + \
															(CtImMe_D_IM_ME_SRC_IMG_PIXS_WIDTH_YCC_4K2K_STD * \
															CtImMe_D_IM_ME_SRC_IMG_PIXS_LINES_YCC_4K2K_STD))
#define CtImMe_D_IM_ME_IMG_MEM_HEVC_U8_Y_GLOBAL_LINES	\
			(ct_im_me_roundup_ribery_lines(CtImMe_D_IM_ME_DST_IMG_PIXS_LINES_HEVC))
													
#define CtImMe_D_IM_ME_IMG_MEM_HEVC_U8_Y_GLOBAL_WIDTH	\
			(ct_im_me_roundup_ribery_width(CtImMe_D_IM_ME_DST_IMG_PIXS_WIDTH_HEVC))

#define CtImMe_D_IM_ME_IMG_MEM_HEVC_U8_C_GLOBAL_WIDTH \
			(ct_im_me_roundup_ribery_width(CtImMe_D_IM_ME_IMG_MEM_HEVC_U8_Y_GLOBAL_WIDTH))

#define CtImMe_D_IM_ME_IMG_MEM_HEVC_U8_C_GLOBAL_LINES \
			(ct_im_me_roundup_ribery_lines(CtImMe_D_IM_ME_DST_IMG_PIXS_LINES_HEVC /2))

#define CtImMe_D_IM_ME_IMG_MEM_4K2K_YCC_REF_U8_BYTES	\
			(CtImMe_D_IM_ME_SRC_IMG_PIXS_WIDTH_YCC_4K2K_REF * \
			CtImMe_D_IM_ME_SRC_IMG_PIXS_LINES_YCC_4K2K_REF * 3 / 2)
			
#define CtImMe_D_IM_ME_IMG_MEM_4K2K_YCC_STD_U8_BYTES	\
			(CtImMe_D_IM_ME_SRC_IMG_PIXS_WIDTH_YCC_4K2K_STD * \
			CtImMe_D_IM_ME_SRC_IMG_PIXS_LINES_YCC_4K2K_STD * 3 / 2)

#define CtImMe_D_IM_ME_IMG_MEM_HEVC_U8_BYTES			\
			(ct_im_me_roundup_16k(CtImMe_D_IM_ME_IMG_MEM_HEVC_U8_Y_GLOBAL_WIDTH * \
			CtImMe_D_IM_ME_IMG_MEM_HEVC_U8_Y_GLOBAL_LINES) +\
			ct_im_me_roundup_16k(CtImMe_D_IM_ME_IMG_MEM_HEVC_U8_C_GLOBAL_WIDTH * \
			CtImMe_D_IM_ME_IMG_MEM_HEVC_U8_C_GLOBAL_LINES))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define ct_im_me_roundup_16(val)					((((val) +15) /16) *16)
#define ct_im_me_roundup_32(val)					((((val) +31) /32) *32)
#define ct_im_me_roundup_128(val)					((((val) +127) /128) *128)
#define ct_im_me_roundup_256(val)					((((val) +255) /256) *256)
#define ct_im_me_roundup_16k(val)					((((val) +16383) /16384) *16384)
#define ct_im_me_roundup_ribery_width(width)		(ct_im_me_roundup_256((width)))
#define ct_im_me_roundup_ribery_lines(lines)		(ct_im_me_roundup_32((lines)))


typedef struct     _CtImMe 			CtImMe;
typedef struct	   _CtImMePrivate 	CtImMePrivate;
typedef struct     _CtImMeClass   	CtImMeClass;

struct _CtImMe {
	GObject parent;
};

struct _CtImMeClass {
	GObjectClass parentclass;
}

GType 			ct_im_me_get_type(void) G_GNUC_CONST;
CtImMe* 		ct_im_me_new(void);

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
void ct_im_me_main(int argc, char** argv);

G_END_DECLS
#endif /* __CT_IM_ME_H__ */
