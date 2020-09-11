/*
*@Copyright (C) 2020-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*2、
*2、
*@version
*2.0.0 2020年06月开始开发
*/

#ifndef __IM_IIP_STRUCT_H__
#define __IM_IIP_STRUCT_H__

#include "driver_common.h"

#include "ddim_typedef.h"
#include <klib.h>

#include <klib.h>

#include "im_iip_param.h"

 #include"imiipdefine.h"

#define IM_TYPE_IIP_STRUCT		(im_iip_struct_get_type())
#define IM_IIP_STRUCT(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipStruct))
#define IM_IS_IIP_STRUCT(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_STRUCT))

#ifndef CO_IIP_DEBUG_CLK_DISABLE
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_IMAGE_CLOCK)
#	define CO_ACT_IIPCLK
#endif
#if defined(CO_ACT_ICLOCK) || defined(CO_ACT_IMAGE_ICLOCK)
#	define CO_ACT_IIP_ICLK
#endif
#if defined(CO_ACT_HCLOCK) || defined(CO_ACT_IMAGE_HCLOCK)
#	define CO_ACT_IIP_HCLK
#endif
#if defined(CO_ACT_PCLOCK) || defined(CO_ACT_IMAGE_PCLOCK)
#	define CO_ACT_IIP_PCLK
#endif
#endif

// Debug option
#ifdef CO_IIP_DEBUG
#	ifndef CO_PARAM_CHECK
#		define CO_PARAM_CHECK
#	endif
#	ifndef CO_IIP_DEBUG_CLK_DISABLE
#		ifndef CO_ACT_IIPCLK
#			define CO_ACT_IIPCLK
#		endif
#		ifndef CO_ACT_IIP_HCLK
#			define CO_ACT_IIP_HCLK
#		endif
#		ifndef CO_ACT_IIP_PCLK
#			define CO_ACT_IIP_PCLK
#		endif
#	endif
#endif

#define D_IM_IIP_UNIT_LD_MAXNUM						(8)		/**< Loader Unit number */
#define D_IM_IIP_UNIT_AFN_MAXNUM					(4)		/**< AFN Unit number */
#define D_IM_IIP_UNIT_FRECT_MAXNUM					(2)		/**< FRECT Unit number */
#define D_IM_IIP_UNIT_SL_MAXNUM						(9)		/**< SL Unit number */
#define D_IM_IIP_UNIT_CSC_MAXNUM					(4)		/**< CSC Unit number */
#define D_IM_IIP_UNIT_CFL_MAXNUM					(1)		/**< CFC Unit number */
#define D_IM_IIP_UNIT_BLEND_MAXNUM					(2)		/**< BLEND Unit number */
#define D_IM_IIP_CACHE_MAXNUM						(3)		/**< Cache number */

typedef struct 				_ImIipStruct ImIipStruct;
typedef struct 				_ImIipStructPrivate ImIipStructPrivate;

typedef enum {
	E_IM_IIP_CACHE_CH_0 = 0,			/**< Cache channel 0 */
	E_IM_IIP_CACHE_CH_1,				/**< Cache channel 1 */
	E_IM_IIP_CACHE_CH_2,				/**< Cache channel 2 */
	E_IM_IIP_CACHE_CH_MAX				/**< Cache channel Maximum number */
} E_IM_IIP_CACHE_CH;

/** PIXFMTTBL FTYPE[2:0] bits */
typedef enum {
	E_IM_IIP_FTYPE_Y_PACKED_CBCR = 0,	/**< Planar format of Y and Chunky format of CbCr */
	E_IM_IIP_FTYPE_CHUNKY = 1,			/**< Chunky format of RGB/YCbCr or<br> Chunky format of CbCr without Y */
	E_IM_IIP_FTYPE_PLANE = 2			/**< Planar format of YCbCr/GBR or<br> Planar format of CbCr without Y */
} E_IM_IIP_FTYPE;

/** PIXFMTTBL PFMT[3:0] bits */
typedef enum {
	E_IM_IIP_PFMT_YCC422	  = 0,		/**< YCbCr422				*/
	E_IM_IIP_PFMT_YCC444	  = 1,		/**< YCbCr444(RGB)			*/
	E_IM_IIP_PFMT_YCC420	  = 2,		/**< YCbCr420				*/
	E_IM_IIP_PFMT_BAYER		  = 3,		/**< Bayer					*/
	E_IM_IIP_PFMT_CBCR		  = 4,		/**< CbCr without Y			*/
	E_IM_IIP_PFMT_VIDEO		  = 5,		/**< Video format (JMILH264_6 uses it) */
	E_IM_IIP_PFMT_PLANE		  = 6,		/**< Plane					*/
	E_IM_IIP_PFMT_RGB565	  = 7,		/**< RGB565					*/
	E_IM_IIP_PFMT_RGBA5551	  = 8,		/**< RGBA5551				*/
	E_IM_IIP_PFMT_RGBA4444	  = 9		/**< RGBA4444				*/
} E_IM_IIP_PFMT;

/** PIXFMTTBL ADEPTH[2:0] bits */
typedef enum {
	E_IM_IIP_ADEPTH_8BITS  = 0,			/**< 8bit			*/
	E_IM_IIP_ADEPTH_4BITS  = 3			/**< 4bit			*/
} E_IM_IIP_ADEPTH;

/** UNIT ID (same as PLDUNIT BitNo) */
typedef enum {
	E_IM_IIP_UNIT_ID_TOP = 0,			/**< Minimum value of enum	*/
	E_IM_IIP_UNIT_ID_LD0 = 0,			/**< Loader 0				*/
	E_IM_IIP_UNIT_ID_LD1 = 1,			/**< Loader 1				*/
	E_IM_IIP_UNIT_ID_LD2 = 2,			/**< Loader 2				*/
	E_IM_IIP_UNIT_ID_LD3 = 3,			/**< Loader 3				*/
	E_IM_IIP_UNIT_ID_FLT = 4,			/**< FLT					*/
	E_IM_IIP_UNIT_ID_AFN0 = 5,			/**< Affine 0				*/
	E_IM_IIP_UNIT_ID_AFN1 = 6,			/**< Affine 1				*/
	E_IM_IIP_UNIT_ID_AFN2 = 7,			/**< Affine 2				*/
	E_IM_IIP_UNIT_ID_FRECT0 = 8,		/**< FRECT 0				*/
	E_IM_IIP_UNIT_ID_MON = 9,			/**< Monitor				*/
	E_IM_IIP_UNIT_ID_SL0 = 10,			/**< Store 0				*/
	E_IM_IIP_UNIT_ID_SL1 = 11,			/**< Store 1				*/
	E_IM_IIP_UNIT_ID_SL2 = 12,			/**< Store 2				*/
	E_IM_IIP_UNIT_ID_SL3 = 13,			/**< Store 3				*/
	E_IM_IIP_UNIT_ID_SL4 = 14,			/**< Store 4				*/
	E_IM_IIP_UNIT_ID_SL5 = 15,			/**< Store 5				*/
	E_IM_IIP_UNIT_ID_CSC0 = 16,			/**< CSC 0					*/
	E_IM_IIP_UNIT_ID_CSC1 = 17,			/**< CSC 1					*/
	E_IM_IIP_UNIT_ID_LUT = 18,			/**< LUT					*/
	E_IM_IIP_UNIT_ID_GPC = 19,			/**< GPC					*/
	E_IM_IIP_UNIT_ID_BLEND0 = 20,		/**< Blend 0				*/
	E_IM_IIP_UNIT_ID_BLEND1 = 21,		/**< Blend 1				*/
	E_IM_IIP_UNIT_ID_FRECT1 = 22,		/**< FRECT 1				*/
	E_IM_IIP_UNIT_ID_CFL0 = 23,			/**< Cache Flow 0			*/
	E_IM_IIP_UNIT_ID_CSC2 = 27,			/**< CSC 2					*/
	E_IM_IIP_UNIT_ID_CSC3 = 28,			/**< CSC 3					*/
	E_IM_IIP_UNIT_ID_SL6 = 29,			/**< Store 6				*/
	E_IM_IIP_UNIT_ID_SL7 = 30,			/**< Store 7				*/
	E_IM_IIP_UNIT_ID_SL8 = 31,			/**< Store 8				*/
	E_IM_IIP_UNIT_ID_LD4 = 32,			/**< Loader 4				*/
	E_IM_IIP_UNIT_ID_LD5 = 33,			/**< Loader 5				*/
	E_IM_IIP_UNIT_ID_LD6 = 34,			/**< Loader 6				*/
	E_IM_IIP_UNIT_ID_LD7 = 35,			/**< Loader 7				*/
	E_IM_IIP_UNIT_ID_AFN3 = 36,			/**< Affine 3				*/
	E_IM_IIP_UNIT_ID_MFT = 37,			/**< MFT					*/
	E_IM_IIP_UNIT_ID_MAX = 38,			/**< Maximum value of enum	*/
} E_IM_IIP_UNIT_ID;

/** PIXFMTTBL ID BitMask */
typedef enum {
	E_IM_IIP_PIXID_0 = 1 << 0,				/**< PIXFMTTBL No.0			*/
	E_IM_IIP_PIXID_1 = 1 << 1,				/**< PIXFMTTBL No.1			*/
	E_IM_IIP_PIXID_2 = 1 << 2,				/**< PIXFMTTBL No.2			*/
	E_IM_IIP_PIXID_3 = 1 << 3,				/**< PIXFMTTBL No.3			*/
	E_IM_IIP_PIXID_4 = 1 << 4,				/**< PIXFMTTBL No.4			*/
	E_IM_IIP_PIXID_5 = 1 << 5,				/**< PIXFMTTBL No.5			*/
	E_IM_IIP_PIXID_6 = 1 << 6,				/**< PIXFMTTBL No.6			*/
	E_IM_IIP_PIXID_7 = 1 << 7,				/**< PIXFMTTBL No.7			*/
	E_IM_IIP_PIXID_8 = 1 << 8,				/**< PIXFMTTBL No.8			*/
	E_IM_IIP_PIXID_9 = 1 << 9,				/**< PIXFMTTBL No.9			*/
	E_IM_IIP_PIXID_10 = 1 << 10,			/**< PIXFMTTBL No.10		*/
	E_IM_IIP_PIXID_11 = 1 << 11,			/**< PIXFMTTBL No.11		*/
	E_IM_IIP_PIXID_INVALID = 1 << 16,		/**< Invalid value. (Driver internal use only)		*/
} E_IM_IIP_PIXID;

/** AXI ID */
typedef enum {
	E_IM_IIP_AXI_ID_TOP = 0,								/**< Top value of this enum. */
	E_IM_IIP_AXI_ID_CACHE0 = 0,								/**< Read cache 0 */
	E_IM_IIP_AXI_ID_CACHE1,									/**< Read cache 1 */
	E_IM_IIP_AXI_ID_CACHE2,									/**< Read cache 2 */
	E_IM_IIP_AXI_ID_DP,										/**< Dispatch sequencer */
	E_IM_IIP_AXI_ID_AFN0,									/**< Affine 0 */
	E_IM_IIP_AXI_ID_AFN1,									/**< Affine 1 */
	E_IM_IIP_AXI_ID_AFN2,									/**< Affine 2 */
	E_IM_IIP_AXI_ID_AFN3,									/**< Affine 3 */
	E_IM_IIP_AXI_ID_FRECT0,									/**< FRECT 0 */
	E_IM_IIP_AXI_ID_FRECT1,									/**< FRECT 1 */
	E_IM_IIP_AXI_ID_GPC,									/**< GPC */
	E_IM_IIP_AXI_ID_SL0,									/**< Store 0 */
	E_IM_IIP_AXI_ID_SL1,									/**< Store 1 */
	E_IM_IIP_AXI_ID_SL2,									/**< Store 2 */
	E_IM_IIP_AXI_ID_SL3,									/**< Store 3 */
	E_IM_IIP_AXI_ID_SL4,									/**< Store 4 */
	E_IM_IIP_AXI_ID_SL5,									/**< Store 5 */
	E_IM_IIP_AXI_ID_SL6,									/**< Store 6 */
	E_IM_IIP_AXI_ID_SL7,									/**< Store 7 */
	E_IM_IIP_AXI_ID_SL8,									/**< Store 8 */
	E_IM_IIP_AXI_ID_MAX										/**< Maximum value of this enum. */
} E_IM_IIP_AXI_ID;

/** LUTRAM type */
typedef enum {
	E_IM_IIP_LUTRAM_TYPE_A = 0,			/**< LUTRAM A */
	E_IM_IIP_LUTRAM_TYPE_B,				/**< LUTRAM B */
	E_IM_IIP_LUTRAM_TYPE_C,				/**< LUTRAM C */
	E_IM_IIP_LUTRAM_TYPE_D,				/**< LUTRAM D */
	E_IM_IIP_LUTRAM_TYPE_E,				/**< LUTRAM E */
	E_IM_IIP_LUTRAM_TYPE_F,				/**< LUTRAM F */
	E_IM_IIP_LUTRAM_TYPE_MAX,			/**< Maximum value of this enum. */
} E_IM_IIP_LUTRAM_TYPE;

/** Resource BitMask */
typedef enum {
	E_IM_IIP_OPEN_RES_NONE     = 0,					/**< None */
	E_IM_IIP_OPEN_RES_LUT_A    = (1 << 0),			/**< LUT A */
	E_IM_IIP_OPEN_RES_LUT_B    = (1 << 1),			/**< LUT B */
	E_IM_IIP_OPEN_RES_LUT_C    = (1 << 2),			/**< LUT C */
	E_IM_IIP_OPEN_RES_LUT_D    = (1 << 3),			/**< LUT D */
	E_IM_IIP_OPEN_RES_LUT_E    = (1 << 4),			/**< LUT E */
	E_IM_IIP_OPEN_RES_LUT_F    = (1 << 5),			/**< LUT F */
	E_IM_IIP_OPEN_RES_HIST_0   = (1 << 6),			/**< Histogram 0 */
	E_IM_IIP_OPEN_RES_HIST_1   = (1 << 7),			/**< Histogram 1 */
	E_IM_IIP_OPEN_RES_HIST_2   = (1 << 8),			/**< Histogram 2 */
	E_IM_IIP_OPEN_RES_HIST_3   = (1 << 9),			/**< Histogram 3 */
	E_IM_IIP_OPEN_RES_CACHE0   = (1 << 10),			/**< Image Cache 0 */
	E_IM_IIP_OPEN_RES_CACHE1   = (1 << 11),			/**< Image Cache 1 */
	E_IM_IIP_OPEN_RES_CACHE2   = (1 << 12),			/**< Image Cache 2 */
	E_IM_IIP_OPEN_RES_BICUBIC0 = (1 << 13),			/**< Bi-Cubic calculator 0 */
	E_IM_IIP_OPEN_RES_BICUBIC1 = (1 << 14),			/**< Bi-Cubic calculator 1 */
} E_IM_IIP_OPEN_RES;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
typedef VOID (*T_IM_IIP_CALLBACK)( ULONG interrupt_flag_mask );	/**< Callback function pointer	*/

/** Chunky component structure */
typedef struct {
	UCHAR	component0;		/**< PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
								 <ul>
									 <li>@ref D_IM_IIP_CHUNKY_COLOR_Y0_G	[PIXFMTTBL.CHKYORDR[1:0]=00b]
									 <li>@ref D_IM_IIP_CHUNKY_COLOR_CB_B	[PIXFMTTBL.CHKYORDR[1:0]=01b]
									 <li>@ref D_IM_IIP_CHUNKY_COLOR_CR_R	[PIXFMTTBL.CHKYORDR[1:0]=10b]
									 <li>@ref D_IM_IIP_CHUNKY_COLOR_Y1_A	[PIXFMTTBL.CHKYORDR[1:0]=11b]
								 </ul> */
	UCHAR	component1;		/**< PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1). Setting value is same as component0. */
	UCHAR	component2;		/**< PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2). Setting value is same as component0. */
	UCHAR	component3;		/**< PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3). Setting value is same as component0. */
} T_IM_IIP_CHUNKY;

/** The size of byte of Global image 1 line. */
typedef struct {
	LONG	Y_G;			/**< PIXFMTTBL.GHSZYG[17:0] <br><br>
								 The size of byte of Global Y(G) image 1 line.
								 Should be aligned on 8.
							 */
	LONG	Cb_B;			/**< PIXFMTTBL.GHSZB[17:0] <br><br>
								 The size of byte of Global Cb(B) image 1 line.
								 Should be aligned on 8.
							 */
	LONG	Cr_R;			/**< PIXFMTTBL.GHSZR[17:0] <br><br>
								 The size of byte of Global Cr(R) image 1 line.
								 Should be aligned on 8.
							 */
	LONG	Alpha;			/**< PIXFMTTBL.GHSZA[17:0] <br><br>
								 The size of byte of Global Alpha image 1 line.
								 Should be aligned on 8.
							 */
} T_IM_IIP_LINE_BYTES;

/** The beginning address of Global image. */
typedef struct {
	ULONG	Y_G;			/**< PIXFMTTBL.ADRSYG[31:0] <br><br>
								 Beginning address of Global Y(G) image.
								 Should be aligned on 8.
							 */
	ULONG	Cb_B;			/**< PIXFMTTBL.ADRSB[31:0] <br><br>
								 Beginning address of Global Cb(B) image.
								 Should be aligned on 8.
							 */
	ULONG	Cr_R;			/**< PIXFMTTBL.ADRSR[31:0] <br><br>
								 Beginning address of Global Cr(R) image.
								 Should be aligned on 8.
							 */
	ULONG	Alpha;			/**< PIXFMTTBL.ADRSA[31:0] <br><br>
								 Beginning address of Global Alpha image.
								 Should be aligned on 8.
							 */
} T_IM_IIP_IMG_ADDR;

/** Im_IIP_Ctrl_PIXFMTTBL() parameter structure */
typedef struct {
	UINT32				pix_depth;				/**< PIXFMTTBL.PDEPTH[2:0] <br><br> Depth of pixel.
													 <ul>
														 <li>@ref D_IM_IIP_PDEPTH_8BITS	 [PIXFMTTBL.PDEPTH[2:0] = 000b]
														 <li>@ref D_IM_IIP_PDEPTH_12BITS [PIXFMTTBL.PDEPTH[2:0] = 001b]
														 <li>@ref D_IM_IIP_PDEPTH_16BITS [PIXFMTTBL.PDEPTH[2:0] = 010b]
													 </ul> */
	UINT32				alpha;					/**< PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
													 <ul>
														 <li>@ref D_IM_IIP_ALPHA_FALSE	[PIXFMTTBL.ALPHA = 0b]
														 <li>@ref D_IM_IIP_ALPHA_TRUE	[PIXFMTTBL.ALPHA = 1b]
													 </ul> */
	E_IM_IIP_FTYPE		frame_type;				/**< PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
													 <ul>
														 <li>@ref E_IM_IIP_FTYPE_Y_PACKED_CBCR	[PIXFMTTBL.FTYPE[2:0] = 000b]
														 <li>@ref E_IM_IIP_FTYPE_CHUNKY			[PIXFMTTBL.FTYPE[2:0] = 001b]
														 <li>@ref E_IM_IIP_FTYPE_PLANE			[PIXFMTTBL.FTYPE[2:0] = 010b]
													 </ul> */
	E_IM_IIP_PFMT		pix_format;				/**< PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
													 <ul>
														 <li>@ref E_IM_IIP_PFMT_YCC422		[PIXFMTTBL.PFMT[3:0] = 0000b]
														 <li>@ref E_IM_IIP_PFMT_YCC444		[PIXFMTTBL.PFMT[3:0] = 0001b]
														 <li>@ref E_IM_IIP_PFMT_YCC420		[PIXFMTTBL.PFMT[3:0] = 0010b]
														 <li>@ref E_IM_IIP_PFMT_BAYER		[PIXFMTTBL.PFMT[3:0] = 0011b]
														 <li>@ref E_IM_IIP_PFMT_CBCR		[PIXFMTTBL.PFMT[3:0] = 0100b]
														 <li>@ref E_IM_IIP_PFMT_VIDEO		[PIXFMTTBL.PFMT[3:0] = 0101b]
														 <li>@ref E_IM_IIP_PFMT_PLANE		[PIXFMTTBL.PFMT[3:0] = 0110b]
														 <li>@ref E_IM_IIP_PFMT_RGB565		[PIXFMTTBL.PFMT[3:0] = 0111b]
														 <li>@ref E_IM_IIP_PFMT_RGBA5551	[PIXFMTTBL.PFMT[3:0] = 1000b]
														 <li>@ref E_IM_IIP_PFMT_RGBA4444	[PIXFMTTBL.PFMT[3:0] = 1001b]
													 </ul> */
	E_IM_IIP_ADEPTH		alpha_depth;			/**< PIXFMTTBL.ADEPTH[2:0] <br><br> Depth of alpha.
													 <ul>
														 <li>@ref E_IM_IIP_ADEPTH_8BITS		[PIXFMTTBL.ADEPTH[2:0] = 000b]
														 <li>@ref E_IM_IIP_ADEPTH_4BITS		[PIXFMTTBL.ADEPTH[2:0] = 011b]
													 </ul> */
	T_IM_IIP_CHUNKY		chunky_color;			/**< PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component. */

	UCHAR				sign_Y_G;				/**< PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
													 <ul>
														 <li>@ref D_IM_IIP_UNSIGNED_DATA	[PIXFMTTBL.SGYG = 0b]
														 <li>@ref D_IM_IIP_SIGNED_DATA		[PIXFMTTBL.SGYG = 1b]
													 </ul> */
	UCHAR				sign_Cb_B;				/**< PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
													 <ul>
														 <li>@ref D_IM_IIP_UNSIGNED_DATA	[PIXFMTTBL.SGB = 0b]
														 <li>@ref D_IM_IIP_SIGNED_DATA		[PIXFMTTBL.SGB = 1b]
													 </ul> */
	UCHAR				sign_Cr_R;				/**< PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
													 <ul>
														 <li>@ref D_IM_IIP_UNSIGNED_DATA	[PIXFMTTBL.SGR = 0b]
														 <li>@ref D_IM_IIP_SIGNED_DATA		[PIXFMTTBL.SGR = 1b]
													 </ul> */
	UCHAR				sign_D3;				/**< PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
													 <ul>
														 <li>@ref D_IM_IIP_UNSIGNED_DATA	[PIXFMTTBL.SGA = 0b]
														 <li>@ref D_IM_IIP_SIGNED_DATA		[PIXFMTTBL.SGA = 1b]
													 </ul> */

	UCHAR				masterIF_Y_G;			/**< PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) output image is master I/F 0, 1 or 2.
													 <TABLE>
														<TR><TH>Store Unit No.</TH><TH>Valid parameter</TH></TR>
														<TR><TH>SL0</TH><TH>D.C.<BR>Fixed value D_IM_IIP_MASTER_IF0 by hardware.</TH></TR>
														<TR><TH>SL1</TH><TH>D.C.<BR>Fixed value D_IM_IIP_MASTER_IF1 by hardware.</TH></TR>
														<TR><TH>SL2</TH><TH>D_IM_IIP_MASTER_IF0 = not supported<BR>D_IM_IIP_MASTER_IF1 = 1<BR>D_IM_IIP_MASTER_IF2 = 2</TH></TR>
														<TR><TH>SL3</TH><TH>D.C.<BR>Fixed value D_IM_IIP_MASTER_IF0 by hardware.</TH></TR>
														<TR><TH>SL4</TH><TH>D.C.<BR>Fixed value D_IM_IIP_MASTER_IF1 by hardware.</TH></TR>
														<TR><TH>SL5</TH><TH>D_IM_IIP_MASTER_IF0 = 0<BR>D_IM_IIP_MASTER_IF1 = not supported<BR>D_IM_IIP_MASTER_IF2 = 2</TH></TR>
														<TR><TH>SL6</TH><TH>D.C.<BR>Fixed value D_IM_IIP_MASTER_IF0 by hardware.</TH></TR>
														<TR><TH>SL7</TH><TH>D.C.<BR>Fixed value D_IM_IIP_MASTER_IF1 by hardware.</TH></TR>
														<TR><TH>SL8</TH><TH>D.C.<BR>Fixed value D_IM_IIP_MASTER_IF2 by hardware.</TH></TR>
													 </TABLE>
													 <ul>
														 <li>@ref D_IM_IIP_MASTER_IF0	[PIXFMTTBL.MTIFYG = 1b]
														 <li>@ref D_IM_IIP_MASTER_IF1	[PIXFMTTBL.MTIFYG = 0b]
														 <li>@ref D_IM_IIP_MASTER_IF2	[PIXFMTTBL.MTIFYG = 0b]
													 </ul> */
	UCHAR				masterIF_Cb_B;			/**< PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) output image is master I/F 0, 1 or 2.
													 Please refrer @ref masterIF_Y_G.
													 */
	UCHAR				masterIF_Cr_R;			/**< PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) output image is master I/F 0, 1 or 2.
													 Please refrer @ref masterIF_Y_G.
													 */
	UCHAR				masterIF_Alpha;			/**< PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha output image is master I/F 0, 1 or 2
													 Please refrer @ref masterIF_Y_G.
													 */
	UINT32				alpha_subsampling;		/**< PIXFMTTBL.ASUBSPL[1:0] <br><br> Control Alpha subsampling.
													 <ul>
														 <li>@ref D_IM_IIP_ALPHA_NO_SUBSAMP	[PIXFMTTBL.ASUBSPL[1:0] = 00b]
														 <li>@ref D_IM_IIP_ALPHA_H_SUBSAMP	[PIXFMTTBL.ASUBSPL[1:0] = 01b]
														 <li>@ref D_IM_IIP_ALPHA_HV_SUBSAMP	[PIXFMTTBL.ASUBSPL[1:0] = 10b]
													 </ul> */
	UINT32				pix_outside_img;		/**< PIXFMTTBL.OARBHV <br><br> Control pixel value outside image.
													 <ul>
														 <li>@ref D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE	[PIXFMTTBL.OARBHV = 0b]
														 <li>@ref D_IM_IIP_OUTSIDE_IMG_EDGE			[PIXFMTTBL.OARBHV = 1b]
													 </ul> */
	USHORT				Y_G_val_outside_img;	/**< PIXFMTTBL.OARVALYG[15:0] <br><br> pixel value outside Y(G) image.
												   This parameter is valid
												   only when T_IM_IIP_PIXFMTTBL::pix_outside_img is set to D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE.*/
	USHORT				Cb_B_val_outside_img;	/**< PIXFMTTBL.OARVALB[15:0] <br><br> pixel value outside Cb(B) image.
												   This parameter is valid
												   only when T_IM_IIP_PIXFMTTBL::pix_outside_img is set to D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE.*/
	USHORT				Cr_R_val_outside_img;	/**< PIXFMTTBL.OARVALR[15:0] <br><br> pixel value outside Cr(R) image.
												   This parameter is valid
												   only when T_IM_IIP_PIXFMTTBL::pix_outside_img is set to D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE.*/
	USHORT				Alpha_val_outside_img;	/**< PIXFMTTBL.OARVALA[15:0] <br><br> pixel value outside Alpha image.
												   This parameter is valid
												   only when T_IM_IIP_PIXFMTTBL::pix_outside_img is set to D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE.*/
	USHORT				width;					/**< PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383] */
	USHORT				lines;					/**< PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383] */

	T_IM_IIP_LINE_BYTES	line_bytes;				/**< The size of byte of Global image 1 line. */
	T_IM_IIP_IMG_ADDR	addr;					/**< Beginning address of Global image. */
} T_IM_IIP_PIXFMTTBL;

/** UNITINFTBL structure */
typedef struct {
	UCHAR	unit_ctrl;			/**< UNITINFTBL.HWEN <br><br> Control unit.
													 <ul>
														 <li>@ref D_IM_IIP_HW_CTRL_SWTRG	[UNITINFTBL.HWEN = 0b]
														 <li>@ref D_IM_IIP_HW_CTRL_AUTO		[UNITINFTBL.HWEN = 1b]
													 </ul> */
	UCHAR	chain_enable;		/**< UNITINFTBL.CHAIN <br><br> Chain control.
													 <ul>
														 <li>@ref D_IM_IIP_PLDUNIT_CHAIN_DISABLE	[UNITINFTBL.CHAIN = 0b]
														 <li>@ref D_IM_IIP_PLDUNIT_CHAIN_ENABLE		[UNITINFTBL.CHAIN = 1b]
													 </ul> */
	ULONG	unit_param_addr;	/**< UNITINFTBL.PADRS[31:0] <br><br> Beginning address of unit parameter. Should be aligned on 8. */
	ULLONG	load_unit_param_flag;
} T_IM_IIP_UNIT_CFG;

/** Im_IIP_Ctrl_UNITINFTBL() parameter structure */
typedef struct {
	T_IM_IIP_UNIT_CFG*	pLD[D_IM_IIP_UNIT_LD_MAXNUM];	/**< Pointer of Loader UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 <ul>
											<li>pLD[0]	Loader 0
											<li>pLD[1]	Loader 1
											<li>pLD[2]	Loader 2
											<li>pLD[3]	Loader 3
											<li>pLD[4]	Loader 4
											<li>pLD[5]	Loader 5
											<li>pLD[6]	Loader 6
											<li>pLD[7]	Loader 7
										 </ul> */
	T_IM_IIP_UNIT_CFG*	pFLT;		/**< Pointer of FLT UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b. */
	T_IM_IIP_UNIT_CFG*	pAFN[D_IM_IIP_UNIT_AFN_MAXNUM];	/**< Pointer of Affine UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 <ul>
											<li>pAFN[0]	Affine 0
											<li>pAFN[1]	Affine 1
											<li>pAFN[2]	Affine 2
											<li>pAFN[3]	Affine 3
										 </ul> */
	T_IM_IIP_UNIT_CFG*	pFRECT[D_IM_IIP_UNIT_FRECT_MAXNUM];	/**< Pointer of FRECT UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 <ul>
											<li>pFRECT[0]	FRECT 0
											<li>pFRECT[1]	FRECT 1
										 </ul> */
	T_IM_IIP_UNIT_CFG*	pMON;		/**< Pointer of Monitor UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b. */
	T_IM_IIP_UNIT_CFG*	pSL[D_IM_IIP_UNIT_SL_MAXNUM];	/**< Pointer of Store UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 <ul>
											<li>pSL[0]	Store 0
											<li>pSL[1]	Store 1
											<li>pSL[2]	Store 2
											<li>pSL[3]	Store 3
											<li>pSL[4]	Store 4
											<li>pSL[5]	Store 5
											<li>pSL[6]	Store 6
											<li>pSL[7]	Store 7
											<li>pSL[8]	Store 8
										 </ul> */
	T_IM_IIP_UNIT_CFG*	pCSC[D_IM_IIP_UNIT_CSC_MAXNUM];	/**< Pointer of CSC UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 <ul>
											<li>pCSC[0]	CSC 0
											<li>pCSC[1]	CSC 1
											<li>pCSC[2]	CSC 2
											<li>pCSC[3]	CSC 3
										 </ul> */
	T_IM_IIP_UNIT_CFG*	pLUT;		/**< Pointer of LUT UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b. */
	T_IM_IIP_UNIT_CFG*	pGPC;		/**< Pointer of GPC UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b. */
	T_IM_IIP_UNIT_CFG*	pBLEND[D_IM_IIP_UNIT_BLEND_MAXNUM];	/**< Pointer of Blend UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 <ul>
											<li>pBLEND[0]	Blend 0
											<li>pBLEND[1]	Blend 1
										 </ul> */
	T_IM_IIP_UNIT_CFG*	pCFL;	/**< Pointer of Cache Flow UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 */
	T_IM_IIP_UNIT_CFG*	pMFT;	/**< Pointer of MFT UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 */
} T_IM_IIP_UNITINFTBL;

/** Im_IIP_Ctrl_LUT() parameter structure */
typedef struct {
	UINT32					buffer_bytes;	/**< The bytes of user LUT buffer "buffer_addr". Should be align on 2. */
	const USHORT*			buffer_addr;	/**< Beginning address of user LUT buffer. */
	E_IM_IIP_LUTRAM_TYPE	lutram_type;	/**< Beginning position of written LUTRAM. */
} T_IM_IIP_LUT;

/** Im_IIP_Ctrl_AXI() parameter structure */
typedef struct {
	UINT32	trans_req_ctrl;
	UINT32	cache_type;
	UINT32	protection_type;
} T_IM_IIP_CTRL_AXI;

/** Im_IIP_Ctrl_AXI_ALL() parameter structure */
typedef struct {
	T_IM_IIP_CTRL_AXI*		imgcache0;	/**< Pointer of AXI control parameters for Image data cache0. */
	T_IM_IIP_CTRL_AXI*		imgcache1;	/**< Pointer of AXI control parameters for Image data cache1. */
	T_IM_IIP_CTRL_AXI*		imgcache2;	/**< Pointer of AXI control parameters for Image data cache3. */
	T_IM_IIP_CTRL_AXI*		dp;			/**< Pointer of AXI control parameters for Dispatch sequencer. */
	T_IM_IIP_CTRL_AXI*		afn0;		/**< Pointer of AXI control parameters for Affine 0. */
	T_IM_IIP_CTRL_AXI*		afn1;		/**< Pointer of AXI control parameters for Affine 1. */
	T_IM_IIP_CTRL_AXI*		afn2;		/**< Pointer of AXI control parameters for Affine 2. */
	T_IM_IIP_CTRL_AXI*		afn3;		/**< Pointer of AXI control parameters for Affine 3. */
	T_IM_IIP_CTRL_AXI*		frect0;		/**< Pointer of AXI control parameters for FRECT 0. */
	T_IM_IIP_CTRL_AXI*		frect1;		/**< Pointer of AXI control parameters for FRECT 1. */
	T_IM_IIP_CTRL_AXI*		gpc;		/**< Pointer of AXI control parameters for GPC. */
	T_IM_IIP_CTRL_AXI*		sl0;		/**< Pointer of AXI control parameters for Store 0. */
	T_IM_IIP_CTRL_AXI*		sl1;		/**< Pointer of AXI control parameters for Store 1. */
	T_IM_IIP_CTRL_AXI*		sl2;		/**< Pointer of AXI control parameters for Store 2. */
	T_IM_IIP_CTRL_AXI*		sl3;		/**< Pointer of AXI control parameters for Store 3. */
	T_IM_IIP_CTRL_AXI*		sl4;		/**< Pointer of AXI control parameters for Store 4. */
	T_IM_IIP_CTRL_AXI*		sl5;		/**< Pointer of AXI control parameters for Store 5. */
	T_IM_IIP_CTRL_AXI*		sl6;		/**< Pointer of AXI control parameters for Store 6. */
	T_IM_IIP_CTRL_AXI*		sl7;		/**< Pointer of AXI control parameters for Store 7. */
	T_IM_IIP_CTRL_AXI*		sl8;		/**< Pointer of AXI control parameters for Store 8. */
} T_IM_IIP_CTRL_AXI_ALL;

/** Im_IIP_Ctrl_Base() parameter structure */
typedef struct {
#if 0	// B2Y Link not support
	UINT32		b2y_link;
#endif	// B2Y Link not support
	UINT32		enable_interrupt_flag;
	UINT32		sl0_interrupt_lines;
	UINT32		sl1_interrupt_lines;
	UINT32		sl2_interrupt_lines;
	UINT32		sl3_interrupt_lines;
	UINT32		sl4_interrupt_lines;
	UINT32		sl5_interrupt_lines;
	UINT32		sl6_interrupt_lines;
	UINT32		sl7_interrupt_lines;
	UINT32		sl8_interrupt_lines;
	T_IM_IIP_CALLBACK		int_handler;
	UINT32		cache_flush_ctrl[D_IM_IIP_CACHE_MAXNUM];	/**< PDCCTL[n].FLHALL <br><br> Control flush cache.
												 <ul>
													 <li>@ref D_IM_IIP_NON_FLUSH_IMGCACHE_START	[PDCCTL.FLHALL = 0b]
													 <li>@ref D_IM_IIP_FLUSH_IMGCACHE_START		[PDCCTL.FLHALL = 1b]
												 </ul> */
	UINT32		ext_bit_ctrl_less_8bits[D_IM_IIP_CACHE_MAXNUM];	/**< PDCCTL[n].EXTBIT <br><br> bit extenstion.
												 <ul>
													 <li>@ref D_IM_IIP_EXTBIT_LOWER_ALIGNED		[PDCCTL.EXTBIT = 0b]
													 <li>@ref D_IM_IIP_EXTBIT_UPPER_ALIGNED		[PDCCTL.EXTBIT = 1b]
												 </ul> */
} T_IM_IIP_CTRL_BASE;

/** Im_IIP_Get_MAXMON() and Im_IIP_Get_MINMON() parameter structure */
typedef struct {
	USHORT	pos_x;		/**< MAXMON.HPOINTMAX_0/1/2/3[13:0], MINMON.HPOINTMIN_0/1/2/3[13:0] and ADDMON.HPOINTADD_0/1/2/3[13:0] */
	USHORT	pos_y;		/**< MAXMON.VPOINTMAX_0/1/2/3[13:0], MINMON.VPOINTMIN_0/1/2/3[13:0] and ADDMON.VPOINTADD_0/1/2/3[13:0] */
	INT32	value;		/**< MAXMON.MAXVAL_0/1/2/3[14:0], MINMON.MINVAL_0/1/2/3[14:0] and ADDMON.ADDVAL_0/1/2/3[31:0] */
} T_IM_IIP_MON;

/** Im_IIP_Get_MAXMON() parameter structure */
typedef struct {
	T_IM_IIP_MON	max[4];			/**< The result of maximum value monitor.
										 <ul>
											 <li>max[0]	D0 component
											 <li>max[1]	D1 component
											 <li>max[2]	D2 component
											 <li>max[3]	D3 component
										 </ul> */
} T_IM_IIP_MAXMON;

/** Im_IIP_Get_MINMON() parameter structure */
typedef struct {
	T_IM_IIP_MON	min[4];			/**< The result of minimum value monitor.
										 <ul>
											 <li>min[0]	D0 component
											 <li>min[1]	D1 component
											 <li>min[2]	D2 component
											 <li>min[3]	D3 component
										 </ul> */
} T_IM_IIP_MINMON;

/** Im_IIP_Get_ADDMON() parameter structure */
typedef struct {
	T_IM_IIP_MON	add[4];			/**< The result of cumulo-addition monitor.
										 <ul>
											 <li>add[0]	D0 component
											 <li>add[1]	D1 component
											 <li>add[2]	D2 component
											 <li>add[3]	D3 component
										 </ul> */
} T_IM_IIP_ADDMON;

/** Im_IIP_Get_ImgCache_Access_Info() parameter structure */
typedef struct {
	ULONG	real_access_counter;	/**< PDCRAC.PDCRAC[31:0]	*/
	ULONG	real_miss_counter;		/**< PDCRMC.PDCRMC[31:0]	*/
} T_IM_IIP_ACCESS_INFO;

/** Im_IIP_Get_AXI_Status() parameter structure */
typedef struct {
	ULONG	read_channel_status;	/**< AXRSTS	register */
	ULONG	write_channel_status;	/**< AXWSTS register */
} T_IM_IIP_AXI_STATUS;

/** Im_IIP_Get_Genline() parameter structure */
typedef struct {
	USHORT	b2y_outlineno;									/**< Generated lines of B2Y macro @@GENLINE.B2Y_OUTLINENO */
	USHORT	afn_outlineno[D_IM_IIP_UNIT_AFN_MAXNUM];		/**< Generated lines of AFN0~2 unit @@GENLINE.AFNn_OUTLINENO (n=0~3) */
	USHORT	frect_outlineno[D_IM_IIP_UNIT_FRECT_MAXNUM];	/**< Generated lines of FRECT0~1 unit @@GENLINE.FRn_OUTLINENO (n=0~1)*/
	USHORT	ld_outlineno[D_IM_IIP_UNIT_LD_MAXNUM];			/**< Generated lines of LD0~7 unit @@GENLINE.LDn_OUTLINENO (n=0~7) */
	USHORT	flt_outlineno;									/**< Generated lines of FLT unit @@GENLINE.FLT_OUTLINENO */
} T_IM_IIP_GENLINE;

/** Im_IIP_Get_Debug_Monitor() parameter structure */
typedef struct {
	ULLONG		data_out_port;								/**< DTOUT_MON register value. */
	ULLONG		waiting_port;								/**< WAIT_MON register value. */
	USHORT		imgcache_data_out[D_IM_IIP_CACHE_MAXNUM];	/**< PDC_DTOUT_MON register value. */
	USHORT		imgcache_ready[D_IM_IIP_CACHE_MAXNUM];		/**< PDC_RDY_MON register value. */
} T_IM_IIP_DEBUG_MONITOR;

typedef struct {
	E_IM_IIP_ADEPTH		alpha_depth;			// PIXFMTTBL.ADEPTH
	UINT32				alpha_subsampling;		// PIXFMTTBL.ASUBSPL
} T_IM_IIP_UTIL_ALPHA_INFO;

// PHSZ, PVSZ parameter for Loader and STS Unit.
typedef struct {
	UINT32	PHSZ0;
	UINT32	PHSZ1;
	UINT32	PVSZ0;
	UINT32	PVSZ1;
} T_IM_IIP_UTIL_PHVSZ;

// Parameter of Im_IIP_Open_SWTRG().
typedef struct {
	ULLONG						unitid_bitmask;
	UINT32						pixid_bitmask;
	UINT32						open_res_bitmask;
} T_IM_IIP_UTIL_PARAM_OPEN;

// Parameter of Im_IIP_Open_SWTRG(), Im_IIP_Set_Interrupt() and Im_IIP_Wait_End()>
typedef struct {
	UINT32						int_fact;	// Parameter "interrupt_bitmask" of Im_IIP_Set_Interrupt() and Parameter "wait_factor" of Im_IIP_Wait_End()
	INT32						wait_time;	// Parameter "wait_time" of Im_IIP_Open_SWTRG() and Parameter "wait_time" of Im_IIP_Wait_End()
} T_IM_IIP_UTIL_PARAM_WAIT;


typedef struct {
	T_IM_IIP_UTIL_PARAM_OPEN	open_param;
	T_IM_IIP_UTIL_PARAM_WAIT	wait_param;
	ULONG						param_buffer_addr;
	UCHAR						param_master_IF;
	T_IM_IIP_PIXFMTTBL			pixfmttbl[2];
	UINT32						pixid[2];
	T_IM_IIP_UNIT_CFG			unit_cfg_afn;
	T_IM_IIP_UNIT_CFG			unit_cfg_sl;
	E_IM_IIP_AXI_ID				axi_id_afn;
	E_IM_IIP_AXI_ID				axi_id_sl;
	T_IM_IIP_CTRL_AXI			axi_cfg_afn;
	T_IM_IIP_CTRL_AXI			axi_cfg_sl;

	T_IM_IIP_PARAM_STS*			p_param_sl;
	T_IM_IIP_PARAM_AFN*			p_param_afn;
	T_IM_IIP_PARAM_AFN_OPCOL_0*	p_afn_struct_param;
} T_IM_IIP_UTIL_PARAM_RESIZE_ROTATE;

// Internal parameter of IM_IIP_Utility_CSC()
typedef struct {
	T_IM_IIP_UTIL_PARAM_OPEN	open_param;
	T_IM_IIP_UTIL_PARAM_WAIT	wait_param;
	ULONG						param_buffer_addr;
	UCHAR						param_master_IF;
	T_IM_IIP_PIXFMTTBL			pixfmttbl[2];
	UINT32						pixid[2];
	T_IM_IIP_UNIT_CFG			unit_cfg_1d;
	T_IM_IIP_UNIT_CFG			unit_cfg_csc;
	T_IM_IIP_UNIT_CFG			unit_cfg_sl;
	E_IM_IIP_AXI_ID				axi_id_ld;
	E_IM_IIP_AXI_ID				axi_id_sl;
	T_IM_IIP_CTRL_AXI			axi_cfg_1d;
	T_IM_IIP_CTRL_AXI			axi_cfg_sl;

	T_IM_IIP_PARAM_1DL*			p_param_1d;
	T_IM_IIP_PARAM_CSC*			p_param_csc;
	T_IM_IIP_PARAM_STS*			p_param_sl;
} T_IM_IIP_UTIL_PARAM_CSC;

// Internal parameter of IM_IIP_Utility_LUT()
typedef struct {
	T_IM_IIP_UTIL_PARAM_OPEN	open_param;
	T_IM_IIP_UTIL_PARAM_WAIT	wait_param;
	ULONG						param_buffer_addr;
	UCHAR						param_master_IF;
	T_IM_IIP_PIXFMTTBL			pixfmttbl[2];
	UINT32						pixid[2];
	T_IM_IIP_UNIT_CFG			unit_cfg_1d;
	T_IM_IIP_UNIT_CFG			unit_cfg_lut;
	T_IM_IIP_UNIT_CFG			unit_cfg_sl;
	E_IM_IIP_AXI_ID				axi_id_ld;
	E_IM_IIP_AXI_ID				axi_id_sl;
	T_IM_IIP_CTRL_AXI			axi_cfg_1d;
	T_IM_IIP_CTRL_AXI			axi_cfg_sl;

	T_IM_IIP_PARAM_1DL*			p_param_1d;
	T_IM_IIP_PARAM_LUT*			p_param_lut;
	T_IM_IIP_PARAM_STS*			p_param_sl;
} T_IM_IIP_UTIL_PARAM_LUT;

typedef struct {
	T_IM_IIP_UTIL_PARAM_OPEN	open_param;
	T_IM_IIP_UTIL_PARAM_WAIT	wait_param;
	ULONG						param_buffer_addr;
	UCHAR						param_master_IF;
	T_IM_IIP_PIXFMTTBL			pixfmttbl[3];
	UINT32						pixid[3];
	T_IM_IIP_UNIT_CFG			unit_cfg_1d[2];
	T_IM_IIP_UNIT_CFG			unit_cfg_alp;
	T_IM_IIP_UNIT_CFG			unit_cfg_sl;
	E_IM_IIP_AXI_ID				axi_id_ld[2];
	E_IM_IIP_AXI_ID				axi_id_sl;
	T_IM_IIP_CTRL_AXI			axi_cfg_1d[2];
	T_IM_IIP_CTRL_AXI			axi_cfg_sl;

	T_IM_IIP_PARAM_1DL*			p_param_1d[2];
	T_IM_IIP_PARAM_BLEND*		p_param_alp;
	T_IM_IIP_PARAM_STS*			p_param_sl;
} T_IM_IIP_UTIL_PARAM_ALPHA;

typedef enum {
	E_IM_IIP_UTIL_ROTATE_000 = 0,	/**< 0 */
	E_IM_IIP_UTIL_ROTATE_090 = 1,	/**< 90 */
	E_IM_IIP_UTIL_ROTATE_180 = 2,	/**< 180 */
	E_IM_IIP_UTIL_ROTATE_270 = 3,	/**< 270 */
	E_IM_IIP_UTIL_ROTATE_MAX = 4,	/**< Maximum value */
} E_IM_IIP_UTIL_ROTATE;

/** Resize mode (Interpolation mode) */
typedef enum {
	E_IM_IIP_UTIL_RESIZE_MODE_NEAREST = E_IM_IIP_PARAM_ITMD_NEAREST,	/**< Nearest */
	E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR = E_IM_IIP_PARAM_ITMD_BI_LINEAR,	/**< Bi-linear */
	E_IM_IIP_UTIL_RESIZE_MODE_BICUBIC = E_IM_IIP_PARAM_ITMD_BI_CUBIC	/**< Bi-cubic */
} E_IM_IIP_UTIL_RESIZE_MODE;

/** Flip status */
typedef enum {
	E_IM_IIP_UTIL_FLIP_OFF = 0,			/**< Off */
	E_IM_IIP_UTIL_FLIP_MIRROR,			/**< Mirror */
	E_IM_IIP_UTIL_FLIP_REVERSE,			/**< Reverse */
	E_IM_IIP_UTIL_FLIP_MIR_AND_REV,		/**< Mirror and Reverse */
	E_IM_IIP_UTIL_FLIP_MAX,				/**< Maximum value */
} E_IM_IIP_UTIL_FLIP;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/** Rectangle (Source image area) */
typedef struct {
	DOUBLE	top;		/**< Vertical position of top-left pixel */
	DOUBLE	left;		/**< Horizontal position of top-left pixel */
	USHORT	width;		/**< Width */
	USHORT	lines;		/**< Lines */
} T_IM_IIP_UTIL_RECT;

/** Rectangle (Source image area) */
typedef struct {
	USHORT	top;		/**< Vertical position of top-left pixel */
	USHORT	left;		/**< Horizontal position of top-left pixel */
	USHORT	width;		/**< Width */
	USHORT	lines;		/**< Lines */
} T_IM_IIP_UTIL_RECT_INT;

/** Global Image info. */
typedef struct {
	UINT32				alpha;
	E_IM_IIP_FTYPE		frame_type;
	E_IM_IIP_PFMT		pix_format;
	T_IM_IIP_CHUNKY		chunky_color;			/**< PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component. */
	UCHAR				sign_Y_G;
	UCHAR				sign_Cb_B;
	UCHAR				sign_Cr_R;
	UCHAR				sign_D3;
	USHORT				width;					/**< PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383] */
	USHORT				lines;					/**< PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]	*/
	T_IM_IIP_LINE_BYTES	line_bytes;				/**< The size of byte of Global image 1 line. */
	T_IM_IIP_IMG_ADDR	addr;					/**< Beginning address of Global image. */
	UCHAR				masterIF_Y_G;
	UCHAR				masterIF_Cb_B;
	UCHAR				masterIF_Cr_R;
	UCHAR				masterIF_Alpha;
} T_IM_IIP_UTIL_IMG_GBL;

/** Image info. */
typedef struct {
	T_IM_IIP_UTIL_RECT			rect;	/**< Rectangle info. (Source image area) */
	T_IM_IIP_UTIL_IMG_GBL		gbl;	/**< Global image info. */
} T_IM_IIP_UTIL_IMG;

/** Image info. */
typedef struct {
	T_IM_IIP_UTIL_RECT_INT		rect;	/**< Rectangle info. (Source image area) */
	T_IM_IIP_UTIL_IMG_GBL		gbl;	/**< Global image info. */
} T_IM_IIP_UTIL_IMG_INT;

/** Alpha unit info. */
typedef struct {
	E_IM_IIP_PARAM_ALPHA_STEP	step;			/**< Bit depth of alpha */
	E_IM_IIP_PARAM_ALPHA_SEL	sel;			/**< Select alpha value which IIP uses */
	E_IM_IIP_PARAM_ALPHA_OUT	out;			/**< Select alpha value which IIP outputs */
	USHORT						ALPHA_VAL[4];	/**< Fixed alpha value.
													 This parameter is valid
													 only when T_IM_IIP_UTIL_ALPHA::sel is E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL. */
} T_IM_IIP_UTIL_ALPHA;

/** Parameter of IM_IIP_Utility_ResizeRotate */
typedef struct {
	E_IM_IIP_UNIT_ID			afn_unitid;			/**< UNITID of AFN */
	E_IM_IIP_UNIT_ID			sl_unitid;			/**< UNITID of SL */
	E_IM_IIP_PIXID				src_pixid;			/**< Source image PIXID */
	E_IM_IIP_PIXID				dst_pixid;			/**< Destination image PIXID */
	E_IM_IIP_PARAM_SCUB			bi_cubic_unitid;	/**< BI-Cubic Unit ID */
	T_IM_IIP_UTIL_IMG			src;				/**< Source image info. */
	T_IM_IIP_UTIL_IMG_INT		dst;				/**< Destination image info. */
	E_IM_IIP_PARAM_CSEL			afn_cache_select;	/**< AFN cache select. */
	UINT32						pix_depth;

	E_IM_IIP_UTIL_ROTATE		rotation;			/**< Angle of rotation */
	E_IM_IIP_UTIL_FLIP			flip;				/**< flip state */
	E_IM_IIP_UTIL_RESIZE_MODE	resize_mode;		/**< Resize mode */
} T_IM_IIP_UTIL_RR;

/** Parameter of IM_IIP_Utility_CSC */
typedef struct {
	E_IM_IIP_UNIT_ID			ld_unitid;			/**< UNITID of Loader */
	E_IM_IIP_UNIT_ID			csc_unitid;			/**< UNITID of CSC */
	E_IM_IIP_UNIT_ID			sl_unitid;			/**< UNITID of SL */
	E_IM_IIP_PIXID				src_pixid;			/**< Source image PIXID */
	E_IM_IIP_PIXID				dst_pixid;			/**< Destination image PIXID */
	T_IM_IIP_UTIL_IMG_INT		src;				/**< Source image info. */
	T_IM_IIP_UTIL_IMG_INT		dst;				/**< Destination image info. */
	E_IM_IIP_PARAM_CSEL			ld_cache_select;	/**< Loader cache select. */
	UINT32						pix_depth;
	E_IM_IIP_ADEPTH				alpha_depth;
	UINT32						alpha_subsampling;

	SHORT						csck[4][4];			/**< CSCK register */
	ULONG						csck_mode_sel;		/**< MDSEL register */
	E_IM_IIP_PARAM_ALPSEL		alpha_in_sel;		/**< ALPSEL register */
	E_IM_IIP_PARAM_ALOSEL		alpha_out_sel;		/**< ALOSEL register */
	UINT32						alpha_val;			/**< ALPVAL register.
														 This parameter is valid only when
														 T_IM_IIP_UTIL_CSC::alpha_sel is E_IM_IIP_PARAM_ALPSEL_ALPVAL_REG. */
	BYTE						sl_sftval;				/**< SL unit's SFTVAL */


} T_IM_IIP_UTIL_CSC;

/** LUTRAM info. */
typedef struct {
	UINT32	buffer_bytes[E_IM_IIP_LUTRAM_TYPE_MAX];
	const USHORT*	buffer_addr[E_IM_IIP_LUTRAM_TYPE_MAX];
} T_IM_IIP_LUTRAM;

/** Parameter of IM_IIP_Utility_LUT */
typedef struct {
	E_IM_IIP_UNIT_ID			ld_unitid;			/**< UNITID of Loader */
	E_IM_IIP_UNIT_ID			lut_unitid;			/**< UNITID of LUT */
	E_IM_IIP_UNIT_ID			sl_unitid;			/**< UNITID of SL */
	E_IM_IIP_PIXID				src_pixid;			/**< Source image PIXID */
	E_IM_IIP_PIXID				dst_pixid;			/**< Destination image PIXID */
	T_IM_IIP_UTIL_IMG_INT		src;				/**< Source image info. */
	T_IM_IIP_UTIL_IMG_INT		dst;				/**< Destination image info. */
	E_IM_IIP_PARAM_CSEL			ld_cache_select;	/**< Loader cache select. */
	UINT32						pix_depth;
	E_IM_IIP_ADEPTH				alpha_depth;		/**< PIXFMTTBL.ADEPTH[2:0] <br><br> Depth of alpha.
													 <ul>
														 <li>@ref E_IM_IIP_ADEPTH_8BITS		[PIXFMTTBL.ADEPTH[2:0] = 000b]
														 <li>@ref E_IM_IIP_ADEPTH_4BITS		[PIXFMTTBL.ADEPTH[2:0] = 011b]
													 </ul> */
	UINT32						alpha_subsampling;

	UINT32						lut_pix_depth[4];
	UINT32						splbit[4];
	T_IM_IIP_LUTRAM				lutram;				/**< Parameters of LUTRAM */
} T_IM_IIP_UTIL_LUT;

/** Parameter of IM_IIP_Utility_AlphaBlend */
typedef struct {
	E_IM_IIP_UNIT_ID			ld_unitid[2];		/**< UNITID of Loader */
	E_IM_IIP_UNIT_ID			blend_unitid;		/**< UNITID of Alpha */
	E_IM_IIP_UNIT_ID			sl_unitid;			/**< UNITID of SL */
	E_IM_IIP_PIXID				src_pixid[2];		/**< Source image PIXID */
	E_IM_IIP_PIXID				dst_pixid;			/**< Destination image PIXID */
	T_IM_IIP_UTIL_IMG_INT		src[2];				/**< Source image info. */
	T_IM_IIP_UTIL_IMG_INT		dst;				/**< Destination image info. */
	E_IM_IIP_PARAM_CSEL			ld_cache_select[2];	/**< Loader cache select. */
	UINT32						pix_depth;
	E_IM_IIP_ADEPTH				alpha_depth;
	UINT32						alpha_subsampling;

	T_IM_IIP_UTIL_ALPHA			alpha;				/**< Parameter of Alpha blend */
} T_IM_IIP_UTIL_ALPHABLEND;

struct _ImIipStruct {
	KObject parent;
};

KConstType 		    im_iip_struct_get_type(void);
ImIipStruct*		        		im_iip_struct_get(void);

extern VOID Im_IIP_On_Hclk( VOID );
extern VOID Im_IIP_Off_Hclk( VOID );
extern VOID Im_IIP_On_Pclk( VOID );
extern VOID Im_IIP_Off_Pclk( VOID );

#endif /* __IM_IIP_STRUCT_H__ */
