/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : maoguangkun
*@brief : CtImShdr
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_SHDR_H__
#define __CT_IM_SHDR_H__


#include <klib.h>

#include "shdrtest21.h"
#include "driver_common.h"


#define CT_TYPE_IM_SHDR                  (ct_im_shdr_get_type())
#define CT_IM_SHDR(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImShdr)) 
#define CT_IS_IM_SHDR(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_SHDR)) 

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define CtImShdr_CT_IM_SHDR_ROUNDUP_16( val )			((((val) +15) /16) *16)
#define CtImShdr_CT_IM_SHDR_ROUNDUP_32( val )			((((val) +31) /32) *32)
#define CtImShdr_CT_IM_SHDR_ROUNDUP_128( val )			((((val) +127) /128) *128)
#define CtImShdr_CT_IM_SHDR_ROUNDUP_256( val )			((((val) +255) /256) *256)
#define CtImShdr_CT_IM_SHDR_ROUNDUP_16K( val )			((((val) +16383) /16384) *16384)
#define CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_WIDTH( width ) \
	                                         (CtImShdr_CT_IM_SHDR_ROUNDUP_256((width)))
#define CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_LINES( lines ) \
	                                         (CtImShdr_CT_IM_SHDR_ROUNDUP_32((lines)))

#define CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_WIDTH_YCC_4K2K_REF		(3840)
#define CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_LINES_YCC_4K2K_REF		(2160)
#define CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_WIDTH_YCC_4K2K_STD		(3840 + 32 * 2)
#define CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_LINES_YCC_4K2K_STD		(2160 + 32 * 2)

#define CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_HEVC				(3840)		// [A]HEVC   4K2K
#define CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_HEVC				(2160)		// [A]HEVC   4K2K
#define CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_MEIN				(960)		// [B]ME input
#define CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_MEIN				(540)		// [B]ME input
#define CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_RIB_FHD			(1920)		// [C]Ribery FHD
#define CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_RIB_FHD			(1080)		// [C]Ribery FHD
#define CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_RIB_HD				(1280)		// [D]Ribery HD
#define CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_RIB_HD				(720)		// [D]Ribery HD
#define CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_DISP_HDMI			(1280)		// [E]DISP   HDMI
#define CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_DISP_HDMI			(720)		// [E]DISP   HDMI
#define CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_DISP_LCD			(640)		// [F]DISP   LCD
#define CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_DISP_LCD			(360)		// [F]DISP   LCD

#define CtImShdr_D_IM_SHDR_IMG_MEM_IN0_ADDR_TOP					(gctImShdrInAddr[ 0 ])
#define CtImShdr_D_IM_SHDR_IMG_MEM_IN1_ADDR_TOP					(gctImShdrInAddr[ 1 ])
#define CtImShdr_D_IM_SHDR_IMG_MEM_IN2_ADDR_TOP					(gctImShdrInAddr[ 2 ])
#define CtImShdr_D_IM_SHDR_IMG_MEM_IN3_ADDR_TOP					(gctImShdrInAddr[ 3 ])
#define CtImShdr_D_IM_SHDR_IMG_MEM_IN4_ADDR_TOP					(gctImShdrInAddr[ 4 ])

#define CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_TOP \
	                                        (CtImShdr_D_IM_SHDR_IMG_MEM_IN0_ADDR_TOP)
#define CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_STD_ADDR_TOP \
	                                        (CtImShdr_D_IM_SHDR_IMG_MEM_IN1_ADDR_TOP)

#define CtImShdr_D_IM_SHDR_IMG_MEM_4K2K_YCC_REF_U8_BYTES \
	                                        (CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_WIDTH_YCC_4K2K_REF * \
	                                        CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_LINES_YCC_4K2K_REF * 3 / 2)
#define CtImShdr_D_IM_SHDR_IMG_MEM_4K2K_YCC_STD_U8_BYTES \
	                                        (CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_WIDTH_YCC_4K2K_STD * \
	                                        CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_LINES_YCC_4K2K_STD * 3 / 2)

#define CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_Y \
                                           (CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_TOP)
#define CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_C \
	                                       (CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_REF_ADDR_Y + \
	                                       (CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_WIDTH_YCC_4K2K_REF * \
	                                       CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_LINES_YCC_4K2K_REF ) )
#define CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_STD_ADDR_Y \
	                                       (CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_STD_ADDR_TOP)
#define CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_STD_ADDR_C	 \
											(CtImShdr_D_IM_SHDR_IMG_MEM_IN_YCC_STD_ADDR_Y + \
											(CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_WIDTH_YCC_4K2K_STD * \
											CtImShdr_D_IM_SHDR_SRC_IMG_PIXS_LINES_YCC_4K2K_STD ) )

#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT0_ADDR_TOP			(gctImShdrOutAddr[ 0 ])
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT1_ADDR_TOP			(gctImShdrOutAddr[ 1 ])
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT2_ADDR_TOP			(gctImShdrOutAddr[ 2 ])
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT3_ADDR_TOP			(gctImShdrOutAddr[ 3 ])
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT4_ADDR_TOP			(gctImShdrOutAddr[ 4 ])
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT5_ADDR_TOP			(gctImShdrOutAddr[ 5 ])

#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_TOP \
	                                       (CtImShdr_D_IM_SHDR_IMG_MEM_OUT0_ADDR_TOP)
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_TOP \
	                                       (CtImShdr_D_IM_SHDR_IMG_MEM_OUT1_ADDR_TOP)
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_TOP	 \
	                                       (CtImShdr_D_IM_SHDR_IMG_MEM_OUT2_ADDR_TOP)
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_TOP \
	                                       (CtImShdr_D_IM_SHDR_IMG_MEM_OUT3_ADDR_TOP)
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_TOP \
                                           (CtImShdr_D_IM_SHDR_IMG_MEM_OUT4_ADDR_TOP)
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_TOP \
	                                       (CtImShdr_D_IM_SHDR_IMG_MEM_OUT5_ADDR_TOP)

#define CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_Y_GLOBAL_WIDTH \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_WIDTH(CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_HEVC))
#define CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_C_GLOBAL_WIDTH \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_WIDTH(CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_Y_GLOBAL_WIDTH))
#define CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_Y_GLOBAL_LINES \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_LINES( CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_HEVC ))
#define CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_C_GLOBAL_LINES \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_LINES( CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_HEVC /2 ))
#define CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_BYTES \
	           ( CtImShdr_CT_IM_SHDR_ROUNDUP_16K(CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_Y_GLOBAL_WIDTH * \
	        	CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_Y_GLOBAL_LINES) \
				+ CtImShdr_CT_IM_SHDR_ROUNDUP_16K(CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_C_GLOBAL_WIDTH * \
				CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_C_GLOBAL_LINES) )
#define CtImShdr_D_IM_SHDR_IMG_MEM_MEIN_YCC_U8_BYTES \
	            (CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_MEIN * CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_MEIN)

#define CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_Y_GLOBAL_WIDTH \
	            (CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_WIDTH(CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_RIB_FHD))
#define CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_C_GLOBAL_WIDTH \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_WIDTH(CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_Y_GLOBAL_WIDTH))
#define CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_Y_GLOBAL_LINES \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_LINES( CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_RIB_FHD ))
#define CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_C_GLOBAL_LINES \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_LINES( CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_RIB_FHD /2 ))
#define CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_BYTES \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_16K(CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_Y_GLOBAL_WIDTH * \
	           CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_Y_GLOBAL_LINES) \
				+ CtImShdr_CT_IM_SHDR_ROUNDUP_16K(CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_C_GLOBAL_WIDTH * \
				CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_C_GLOBAL_LINES) )
#define CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_Y_GLOBAL_WIDTH \
	            (CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_WIDTH(CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_RIB_HD))
#define CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_C_GLOBAL_WIDTH \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_WIDTH(CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_Y_GLOBAL_WIDTH))
#define CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_Y_GLOBAL_LINES \
	            (CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_LINES( CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_RIB_HD ))
#define CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_C_GLOBAL_LINES \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_RIBERY_LINES( CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_RIB_HD /2 ))
#define CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_BYTES \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_16K(CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_Y_GLOBAL_WIDTH * \
	           CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_Y_GLOBAL_LINES) \
				+ CtImShdr_CT_IM_SHDR_ROUNDUP_16K(CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_C_GLOBAL_WIDTH * \
				CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_C_GLOBAL_LINES) )
#define CtImShdr_D_IM_SHDR_IMG_MEM_DISP_HDMI_YCC_U8_BYTES \
	            (CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_DISP_HDMI * \
	            CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_DISP_HDMI * 3 / 2)

#define CtImShdr_D_IM_SHDR_IMG_MEM_DISP_LCD_YCC_U8_BYTES \
	           (CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_DISP_LCD  * \
	           CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_DISP_LCD  * 3 / 2)

#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_Y \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_16K(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_TOP))
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_C \
	           (CtImShdr_D_IM_SHDR_IMG_MEM_OUT_HEVC_ADDR_Y + \
	           CtImShdr_CT_IM_SHDR_ROUNDUP_16K( CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_Y_GLOBAL_WIDTH * \
	           CtImShdr_D_IM_SHDR_IMG_MEM_HEVC_U8_Y_GLOBAL_LINES ) )
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_Y \
	           (CtImShdr_D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_TOP)
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_C \
	           (CtImShdr_D_IM_SHDR_IMG_MEM_OUT_MEIN_ADDR_Y + \
	           (CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_MEIN      * \
	           CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_MEIN      ) )
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_Y \
	           (CtImShdr_CT_IM_SHDR_ROUNDUP_16K(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_TOP))
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_C \
	            (CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_FHD_ADDR_Y + \
	            CtImShdr_CT_IM_SHDR_ROUNDUP_16K( CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_Y_GLOBAL_WIDTH * \
	            CtImShdr_D_IM_SHDR_IMG_MEM_RIB_FHD_U8_Y_GLOBAL_LINES ) )
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_Y \
	            (CtImShdr_CT_IM_SHDR_ROUNDUP_16K(CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_TOP))
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_C \
	           (CtImShdr_D_IM_SHDR_IMG_MEM_OUT_RIB_HD_ADDR_Y + \
	           CtImShdr_CT_IM_SHDR_ROUNDUP_16K( CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_Y_GLOBAL_WIDTH * \
	           CtImShdr_D_IM_SHDR_IMG_MEM_RIB_HD_U8_Y_GLOBAL_LINES ) )
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_Y \
	           (CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_TOP)
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_C \
	           (CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_HDMI_ADDR_Y + \
	           (CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_DISP_HDMI * \
	           CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_DISP_HDMI ) )
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_Y \
	           (CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_TOP)
#define CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_C \
	           (CtImShdr_D_IM_SHDR_IMG_MEM_OUT_DISP_LCD_ADDR_Y  + \
	           (CtImShdr_D_IM_SHDR_DST_IMG_PIXS_WIDTH_DISP_LCD  * \
	           CtImShdr_D_IM_SHDR_DST_IMG_PIXS_LINES_DISP_LCD  ) )


typedef struct _CtImShdr CtImShdr;
typedef struct _CtImShdrPrivate CtImShdrPrivate;


struct _CtImShdr
{
	KObject parent;
};


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */
/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
extern ULONG gctImShdrInAddr[ 5 ];
extern ULONG gctImShdrOutAddr[ 6 ];
/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/


KConstType 			ct_im_shdr_get_type(void);
CtImShdr* 				ct_im_shdr_get(void);

#endif /* __CT_IM_SHDR_H__ */
