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
#	define ImIipStruct_CO_ACT_IIPCLK
#endif
#if defined(CO_ACT_ICLOCK) || defined(CO_ACT_IMAGE_ICLOCK)
#	define ImIipStruct_CO_ACT_IIP_ICLK
#endif
#if defined(CO_ACT_HCLOCK) || defined(CO_ACT_IMAGE_HCLOCK)
#	define ImIipStruct_CO_ACT_IIP_HCLK
#endif
#if defined(CO_ACT_PCLOCK) || defined(CO_ACT_IMAGE_PCLOCK)
#	define ImIipStruct_CO_ACT_IIP_PCLK
#endif
#endif

// Debug option
#ifdef CO_IIP_DEBUG
#	ifndef ImIipStruct_CO_PARAM_CHECK
#		define ImIipStruct_CO_PARAM_CHECK
#	endif
#	ifndef CO_IIP_DEBUG_CLK_DISABLE
#		ifndef ImIipStruct_CO_ACT_IIPCLK
#			define ImIipStruct_CO_ACT_IIPCLK
#		endif
#		ifndef ImIipStruct_CO_ACT_IIP_HCLK
#			define ImIipStruct_CO_ACT_IIP_HCLK
#		endif
#		ifndef ImIipStruct_CO_ACT_IIP_PCLK
#			define ImIipStruct_CO_ACT_IIP_PCLK
#		endif
#	endif
#endif

#define ImIipStruct_D_IM_IIP_UNIT_LD_MAXNUM						(8)		/**< Loader Unit number */
#define ImIipStruct_D_IM_IIP_UNIT_AFN_MAXNUM					(4)		/**< AFN Unit number */
#define ImIipStruct_D_IM_IIP_UNIT_FRECT_MAXNUM					(2)		/**< FRECT Unit number */
#define ImIipStruct_D_IM_IIP_UNIT_SL_MAXNUM						(9)		/**< SL Unit number */
#define ImIipStruct_D_IM_IIP_UNIT_CSC_MAXNUM					(4)		/**< CSC Unit number */
#define ImIipStruct_D_IM_IIP_UNIT_CFL_MAXNUM					(1)		/**< CFC Unit number */
#define ImIipStruct_D_IM_IIP_UNIT_BLEND_MAXNUM					(2)		/**< BLEND Unit number */
#define ImIipStruct_D_IM_IIP_CACHE_MAXNUM						(3)		/**< Cache number */

typedef struct 				_ImIipStruct ImIipStruct;
typedef struct 				_ImIipStructPrivate ImIipStructPrivate;

typedef enum {
	ImIipStruct_E_IM_IIP_CACHE_CH_0 = 0,			/**< Cache channel 0 */
	ImIipStruct_E_IM_IIP_CACHE_CH_1,				/**< Cache channel 1 */
	ImIipStruct_E_IM_IIP_CACHE_CH_2,				/**< Cache channel 2 */
	ImIipStruct_E_IM_IIP_CACHE_CH_MAX				/**< Cache channel Maximum number */
} EImIipCacheCh;

/** PIXFMTTBL FTYPE[2:0] bits */
typedef enum {
	ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR = 0,	/**< Planar format of Y and Chunky format of CbCr */
	ImIipStruct_E_IM_IIP_FTYPE_CHUNKY = 1,			/**< Chunky format of RGB/YCbCr or<br> Chunky format of CbCr without Y */
	ImIipStruct_E_IM_IIP_FTYPE_PLANE = 2			/**< Planar format of YCbCr/GBR or<br> Planar format of CbCr without Y */
} EImIipFtype;

/** PIXFMTTBL PFMT[3:0] bits */
typedef enum {
	ImIipStruct_E_IM_IIP_PFMT_YCC422	  = 0,		/**< YCbCr422				*/
	ImIipStruct_E_IM_IIP_PFMT_YCC444	  = 1,		/**< YCbCr444(RGB)			*/
	ImIipStruct_E_IM_IIP_PFMT_YCC420	  = 2,		/**< YCbCr420				*/
	ImIipStruct_E_IM_IIP_PFMT_BAYER		  = 3,		/**< Bayer					*/
	ImIipStruct_E_IM_IIP_PFMT_CBCR		  = 4,		/**< CbCr without Y			*/
	ImIipStruct_E_IM_IIP_PFMT_VIDEO		  = 5,		/**< Video format (JMILH264_6 uses it) */
	ImIipStruct_E_IM_IIP_PFMT_PLANE		  = 6,		/**< Plane					*/
	ImIipStruct_E_IM_IIP_PFMT_RGB565	  = 7,		/**< RGB565					*/
	ImIipStruct_E_IM_IIP_PFMT_RGBA5551	  = 8,		/**< RGBA5551				*/
	ImIipStruct_E_IM_IIP_PFMT_RGBA4444	  = 9		/**< RGBA4444				*/
} EImIipPfmt;

/** PIXFMTTBL ADEPTH[2:0] bits */
typedef enum {
	ImIipStruct_E_IM_IIP_ADEPTH_8BITS  = 0,			/**< 8bit			*/
	ImIipStruct_E_IM_IIP_ADEPTH_4BITS  = 3			/**< 4bit			*/
} EImIipAdepth;

/** UNIT ID (same as PLDUNIT BitNo) */
typedef enum {
	ImIipStruct_E_IM_IIP_UNIT_ID_TOP = 0,			/**< Minimum value of enum	*/
	ImIipStruct_E_IM_IIP_UNIT_ID_LD0 = 0,			/**< Loader 0				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_LD1 = 1,			/**< Loader 1				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_LD2 = 2,			/**< Loader 2				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_LD3 = 3,			/**< Loader 3				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_FLT = 4,			/**< FLT					*/
	ImIipStruct_E_IM_IIP_UNIT_ID_AFN0 = 5,			/**< Affine 0				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_AFN1 = 6,			/**< Affine 1				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_AFN2 = 7,			/**< Affine 2				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_FRECT0 = 8,		/**< FRECT 0				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_MON = 9,			/**< Monitor				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_SL0 = 10,			/**< Store 0				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_SL1 = 11,			/**< Store 1				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_SL2 = 12,			/**< Store 2				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_SL3 = 13,			/**< Store 3				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_SL4 = 14,			/**< Store 4				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_SL5 = 15,			/**< Store 5				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_CSC0 = 16,			/**< CSC 0					*/
	ImIipStruct_E_IM_IIP_UNIT_ID_CSC1 = 17,			/**< CSC 1					*/
	ImIipStruct_E_IM_IIP_UNIT_ID_LUT = 18,			/**< LUT					*/
	ImIipStruct_E_IM_IIP_UNIT_ID_GPC = 19,			/**< GPC					*/
	ImIipStruct_E_IM_IIP_UNIT_ID_BLEND0 = 20,		/**< Blend 0				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_BLEND1 = 21,		/**< Blend 1				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_FRECT1 = 22,		/**< FRECT 1				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_CFL0 = 23,			/**< Cache Flow 0			*/
	ImIipStruct_E_IM_IIP_UNIT_ID_CSC2 = 27,			/**< CSC 2					*/
	ImIipStruct_E_IM_IIP_UNIT_ID_CSC3 = 28,			/**< CSC 3					*/
	ImIipStruct_E_IM_IIP_UNIT_ID_SL6 = 29,			/**< Store 6				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_SL7 = 30,			/**< Store 7				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_SL8 = 31,			/**< Store 8				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_LD4 = 32,			/**< Loader 4				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_LD5 = 33,			/**< Loader 5				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_LD6 = 34,			/**< Loader 6				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_LD7 = 35,			/**< Loader 7				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_AFN3 = 36,			/**< Affine 3				*/
	ImIipStruct_E_IM_IIP_UNIT_ID_MFT = 37,			/**< MFT					*/
	ImIipStruct_E_IM_IIP_UNIT_ID_MAX = 38,			/**< Maximum value of enum	*/
} EImIipUnitId;

/** PIXFMTTBL ID BitMask */
typedef enum {
	ImIipStruct_E_IM_IIP_PIXID_0 = 1 << 0,				/**< PIXFMTTBL No.0			*/
	ImIipStruct_E_IM_IIP_PIXID_1 = 1 << 1,				/**< PIXFMTTBL No.1			*/
	ImIipStruct_E_IM_IIP_PIXID_2 = 1 << 2,				/**< PIXFMTTBL No.2			*/
	ImIipStruct_E_IM_IIP_PIXID_3 = 1 << 3,				/**< PIXFMTTBL No.3			*/
	ImIipStruct_E_IM_IIP_PIXID_4 = 1 << 4,				/**< PIXFMTTBL No.4			*/
	ImIipStruct_E_IM_IIP_PIXID_5 = 1 << 5,				/**< PIXFMTTBL No.5			*/
	ImIipStruct_E_IM_IIP_PIXID_6 = 1 << 6,				/**< PIXFMTTBL No.6			*/
	ImIipStruct_E_IM_IIP_PIXID_7 = 1 << 7,				/**< PIXFMTTBL No.7			*/
	ImIipStruct_E_IM_IIP_PIXID_8 = 1 << 8,				/**< PIXFMTTBL No.8			*/
	ImIipStruct_E_IM_IIP_PIXID_9 = 1 << 9,				/**< PIXFMTTBL No.9			*/
	ImIipStruct_E_IM_IIP_PIXID_10 = 1 << 10,			/**< PIXFMTTBL No.10		*/
	ImIipStruct_E_IM_IIP_PIXID_11 = 1 << 11,			/**< PIXFMTTBL No.11		*/
	ImIipStruct_E_IM_IIP_PIXID_INVALID = 1 << 16,		/**< Invalid value. (Driver internal use only)		*/
} EImIipPixid;

/** AXI ID */
typedef enum {
	ImIipStruct_E_IM_IIP_AXI_ID_TOP = 0,								/**< Top value of this enum. */
	ImIipStruct_E_IM_IIP_AXI_ID_CACHE0 = 0,								/**< Read cache 0 */
	ImIipStruct_E_IM_IIP_AXI_ID_CACHE1,									/**< Read cache 1 */
	ImIipStruct_E_IM_IIP_AXI_ID_CACHE2,									/**< Read cache 2 */
	ImIipStruct_E_IM_IIP_AXI_ID_DP,										/**< Dispatch sequencer */
	ImIipStruct_E_IM_IIP_AXI_ID_AFN0,									/**< Affine 0 */
	ImIipStruct_E_IM_IIP_AXI_ID_AFN1,									/**< Affine 1 */
	ImIipStruct_E_IM_IIP_AXI_ID_AFN2,									/**< Affine 2 */
	ImIipStruct_E_IM_IIP_AXI_ID_AFN3,									/**< Affine 3 */
	ImIipStruct_E_IM_IIP_AXI_ID_FRECT0,									/**< FRECT 0 */
	ImIipStruct_E_IM_IIP_AXI_ID_FRECT1,									/**< FRECT 1 */
	ImIipStruct_E_IM_IIP_AXI_ID_GPC,									/**< GPC */
	ImIipStruct_E_IM_IIP_AXI_ID_SL0,									/**< Store 0 */
	ImIipStruct_E_IM_IIP_AXI_ID_SL1,									/**< Store 1 */
	ImIipStruct_E_IM_IIP_AXI_ID_SL2,									/**< Store 2 */
	ImIipStruct_E_IM_IIP_AXI_ID_SL3,									/**< Store 3 */
	ImIipStruct_E_IM_IIP_AXI_ID_SL4,									/**< Store 4 */
	ImIipStruct_E_IM_IIP_AXI_ID_SL5,									/**< Store 5 */
	ImIipStruct_E_IM_IIP_AXI_ID_SL6,									/**< Store 6 */
	ImIipStruct_E_IM_IIP_AXI_ID_SL7,									/**< Store 7 */
	ImIipStruct_E_IM_IIP_AXI_ID_SL8,									/**< Store 8 */
	ImIipStruct_E_IM_IIP_AXI_ID_MAX										/**< Maximum value of this enum. */
} EImIipAxiId;

/** LUTRAM type */
typedef enum {
	ImIipStruct_E_IM_IIP_LUTRAM_TYPE_A = 0,			/**< LUTRAM A */
	ImIipStruct_E_IM_IIP_LUTRAM_TYPE_B,				/**< LUTRAM B */
	ImIipStruct_E_IM_IIP_LUTRAM_TYPE_C,				/**< LUTRAM C */
	ImIipStruct_E_IM_IIP_LUTRAM_TYPE_D,				/**< LUTRAM D */
	ImIipStruct_E_IM_IIP_LUTRAM_TYPE_E,				/**< LUTRAM E */
	ImIipStruct_E_IM_IIP_LUTRAM_TYPE_F,				/**< LUTRAM F */
	ImIipStruct_E_IM_IIP_LUTRAM_TYPE_MAX,			/**< Maximum value of this enum. */
} EImIipLutramType;

/** Resource BitMask */
typedef enum {
	ImIipStruct_E_IM_IIP_OPEN_RES_NONE     = 0,					/**< None */
	ImIipStruct_E_IM_IIP_OPEN_RES_LUT_A    = (1 << 0),			/**< LUT A */
	ImIipStruct_E_IM_IIP_OPEN_RES_LUT_B    = (1 << 1),			/**< LUT B */
	ImIipStruct_E_IM_IIP_OPEN_RES_LUT_C    = (1 << 2),			/**< LUT C */
	ImIipStruct_E_IM_IIP_OPEN_RES_LUT_D    = (1 << 3),			/**< LUT D */
	ImIipStruct_E_IM_IIP_OPEN_RES_LUT_E    = (1 << 4),			/**< LUT E */
	ImIipStruct_E_IM_IIP_OPEN_RES_LUT_F    = (1 << 5),			/**< LUT F */
	ImIipStruct_E_IM_IIP_OPEN_RES_HIST_0   = (1 << 6),			/**< Histogram 0 */
	ImIipStruct_E_IM_IIP_OPEN_RES_HIST_1   = (1 << 7),			/**< Histogram 1 */
	ImIipStruct_E_IM_IIP_OPEN_RES_HIST_2   = (1 << 8),			/**< Histogram 2 */
	ImIipStruct_E_IM_IIP_OPEN_RES_HIST_3   = (1 << 9),			/**< Histogram 3 */
	ImIipStruct_E_IM_IIP_OPEN_RES_CACHE0   = (1 << 10),			/**< Image Cache 0 */
	ImIipStruct_E_IM_IIP_OPEN_RES_CACHE1   = (1 << 11),			/**< Image Cache 1 */
	ImIipStruct_E_IM_IIP_OPEN_RES_CACHE2   = (1 << 12),			/**< Image Cache 2 */
	ImIipStruct_E_IM_IIP_OPEN_RES_BICUBIC0 = (1 << 13),			/**< Bi-Cubic calculator 0 */
	ImIipStruct_E_IM_IIP_OPEN_RES_BICUBIC1 = (1 << 14),			/**< Bi-Cubic calculator 1 */
} EImIipOpenRes;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
typedef VOID (*T_IM_IIP_CALLBACK)( ULONG interrupt_flag_mask );	/**< Callback function pointer	*/

/** Chunky component structure */
typedef struct {
	UCHAR	component0;		/**< PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
								 <ul>
									 <li>@ref D_IM_IIP_CHUNKY_COLOR_Y0_G	[PIXFMTTBL.CHKYORDR[1:0]=00b]
									 <li>@ref ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B	[PIXFMTTBL.CHKYORDR[1:0]=01b]
									 <li>@ref D_IM_IIP_CHUNKY_COLOR_CR_R	[PIXFMTTBL.CHKYORDR[1:0]=10b]
									 <li>@ref ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A	[PIXFMTTBL.CHKYORDR[1:0]=11b]
								 </ul> */
	UCHAR	component1;		/**< PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1). Setting value is same as component0. */
	UCHAR	component2;		/**< PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2). Setting value is same as component0. */
	UCHAR	component3;		/**< PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3). Setting value is same as component0. */
} TImIipChunky;

/** The size of byte of Global image 1 line. */
typedef struct {
	LONG	yG;			/**< PIXFMTTBL.GHSZYG[17:0] <br><br>
								 The size of byte of Global Y(G) image 1 line.
								 Should be aligned on 8.
							 */
	LONG	cbB;			/**< PIXFMTTBL.GHSZB[17:0] <br><br>
								 The size of byte of Global Cb(B) image 1 line.
								 Should be aligned on 8.
							 */
	LONG	crR;			/**< PIXFMTTBL.GHSZR[17:0] <br><br>
								 The size of byte of Global Cr(R) image 1 line.
								 Should be aligned on 8.
							 */
	LONG	Alpha;			/**< PIXFMTTBL.GHSZA[17:0] <br><br>
								 The size of byte of Global Alpha image 1 line.
								 Should be aligned on 8.
							 */
} TImIipLineBytes;

/** The beginning address of Global image. */
typedef struct {
	ULONG	yG;			/**< PIXFMTTBL.ADRSYG[31:0] <br><br>
								 Beginning address of Global Y(G) image.
								 Should be aligned on 8.
							 */
	ULONG	cbB;			/**< PIXFMTTBL.ADRSB[31:0] <br><br>
								 Beginning address of Global Cb(B) image.
								 Should be aligned on 8.
							 */
	ULONG	crR;			/**< PIXFMTTBL.ADRSR[31:0] <br><br>
								 Beginning address of Global Cr(R) image.
								 Should be aligned on 8.
							 */
	ULONG	Alpha;			/**< PIXFMTTBL.ADRSA[31:0] <br><br>
								 Beginning address of Global Alpha image.
								 Should be aligned on 8.
							 */
} TImIipImgAddr;

/** im_iip_ctrl_pixfmttbl() parameter structure */
typedef struct {
	UINT32				pixDepth;				/**< PIXFMTTBL.PDEPTH[2:0] <br><br> Depth of pixel.
													 <ul>
														 <li>@ref D_IM_IIP_PDEPTH_8BITS	 [PIXFMTTBL.PDEPTH[2:0] = 000b]
														 <li>@ref ImIipDefine_D_IM_IIP_PDEPTH_12BITS [PIXFMTTBL.PDEPTH[2:0] = 001b]
														 <li>@ref ImIipDefine_D_IM_IIP_PDEPTH_16BITS [PIXFMTTBL.PDEPTH[2:0] = 010b]
													 </ul> */
	UINT32				alpha;					/**< PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
													 <ul>
														 <li>@ref ImIipDefine_D_IM_IIP_ALPHA_FALSE	[PIXFMTTBL.ALPHA = 0b]
														 <li>@ref ImIipDefine_D_IM_IIP_ALPHA_TRUE	[PIXFMTTBL.ALPHA = 1b]
													 </ul> */
	EImIipFtype		frameType;				/**< PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
													 <ul>
														 <li>@ref ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR	[PIXFMTTBL.FTYPE[2:0] = 000b]
														 <li>@ref ImIipStruct_E_IM_IIP_FTYPE_CHUNKY			[PIXFMTTBL.FTYPE[2:0] = 001b]
														 <li>@ref ImIipStruct_E_IM_IIP_FTYPE_PLANE			[PIXFMTTBL.FTYPE[2:0] = 010b]
													 </ul> */
	EImIipPfmt		pixFormat;				/**< PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
													 <ul>
														 <li>@ref ImIipStruct_E_IM_IIP_PFMT_YCC422		[PIXFMTTBL.PFMT[3:0] = 0000b]
														 <li>@ref ImIipStruct_E_IM_IIP_PFMT_YCC444		[PIXFMTTBL.PFMT[3:0] = 0001b]
														 <li>@ref ImIipStruct_E_IM_IIP_PFMT_YCC420		[PIXFMTTBL.PFMT[3:0] = 0010b]
														 <li>@ref ImIipStruct_E_IM_IIP_PFMT_BAYER		[PIXFMTTBL.PFMT[3:0] = 0011b]
														 <li>@ref ImIipStruct_E_IM_IIP_PFMT_CBCR		[PIXFMTTBL.PFMT[3:0] = 0100b]
														 <li>@ref ImIipStruct_E_IM_IIP_PFMT_VIDEO		[PIXFMTTBL.PFMT[3:0] = 0101b]
														 <li>@ref ImIipStruct_E_IM_IIP_PFMT_PLANE		[PIXFMTTBL.PFMT[3:0] = 0110b]
														 <li>@ref ImIipStruct_E_IM_IIP_PFMT_RGB565		[PIXFMTTBL.PFMT[3:0] = 0111b]
														 <li>@ref ImIipStruct_E_IM_IIP_PFMT_RGBA5551	[PIXFMTTBL.PFMT[3:0] = 1000b]
														 <li>@ref ImIipStruct_E_IM_IIP_PFMT_RGBA4444	[PIXFMTTBL.PFMT[3:0] = 1001b]
													 </ul> */
	EImIipAdepth		alphaDepth;			/**< PIXFMTTBL.ADEPTH[2:0] <br><br> Depth of alpha.
													 <ul>
														 <li>@ref ImIipStruct_E_IM_IIP_ADEPTH_8BITS		[PIXFMTTBL.ADEPTH[2:0] = 000b]
														 <li>@ref ImIipStruct_E_IM_IIP_ADEPTH_4BITS		[PIXFMTTBL.ADEPTH[2:0] = 011b]
													 </ul> */
	TImIipChunky		chunkyColor;			/**< PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component. */

	UCHAR				signYG;				/**< PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
													 <ul>
														 <li>@ref ImIipDefine_D_IM_IIP_UNSIGNED_DATA	[PIXFMTTBL.SGYG = 0b]
														 <li>@ref ImIipDefine_D_IM_IIP_SIGNED_DATA		[PIXFMTTBL.SGYG = 1b]
													 </ul> */
	UCHAR				signCbB;				/**< PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
													 <ul>
														 <li>@ref ImIipDefine_D_IM_IIP_UNSIGNED_DATA	[PIXFMTTBL.SGB = 0b]
														 <li>@ref ImIipDefine_D_IM_IIP_SIGNED_DATA		[PIXFMTTBL.SGB = 1b]
													 </ul> */
	UCHAR				signCrR;				/**< PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
													 <ul>
														 <li>@ref ImIipDefine_D_IM_IIP_UNSIGNED_DATA	[PIXFMTTBL.SGR = 0b]
														 <li>@ref ImIipDefine_D_IM_IIP_SIGNED_DATA		[PIXFMTTBL.SGR = 1b]
													 </ul> */
	UCHAR				signD3;				/**< PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
													 <ul>
														 <li>@ref ImIipDefine_D_IM_IIP_UNSIGNED_DATA	[PIXFMTTBL.SGA = 0b]
														 <li>@ref ImIipDefine_D_IM_IIP_SIGNED_DATA		[PIXFMTTBL.SGA = 1b]
													 </ul> */

	UCHAR				masterifYG;			/**< PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) output image is master I/F 0, 1 or 2.
													 <TABLE>
														<TR><TH>Store Unit No.</TH><TH>Valid parameter</TH></TR>
														<TR><TH>SL0</TH><TH>D.C.<BR>Fixed value ImIipDefine_D_IM_IIP_MASTER_IF0 by hardware.</TH></TR>
														<TR><TH>SL1</TH><TH>D.C.<BR>Fixed value ImIipDefine_D_IM_IIP_MASTER_IF1 by hardware.</TH></TR>
														<TR><TH>SL2</TH><TH>ImIipDefine_D_IM_IIP_MASTER_IF0 = not supported<BR>ImIipDefine_D_IM_IIP_MASTER_IF1 = 1<BR>D_IM_IIP_MASTER_IF2 = 2</TH></TR>
														<TR><TH>SL3</TH><TH>D.C.<BR>Fixed value ImIipDefine_D_IM_IIP_MASTER_IF0 by hardware.</TH></TR>
														<TR><TH>SL4</TH><TH>D.C.<BR>Fixed value ImIipDefine_D_IM_IIP_MASTER_IF1 by hardware.</TH></TR>
														<TR><TH>SL5</TH><TH>ImIipDefine_D_IM_IIP_MASTER_IF0 = 0<BR>ImIipDefine_D_IM_IIP_MASTER_IF1 = not supported<BR>D_IM_IIP_MASTER_IF2 = 2</TH></TR>
														<TR><TH>SL6</TH><TH>D.C.<BR>Fixed value ImIipDefine_D_IM_IIP_MASTER_IF0 by hardware.</TH></TR>
														<TR><TH>SL7</TH><TH>D.C.<BR>Fixed value ImIipDefine_D_IM_IIP_MASTER_IF1 by hardware.</TH></TR>
														<TR><TH>SL8</TH><TH>D.C.<BR>Fixed value D_IM_IIP_MASTER_IF2 by hardware.</TH></TR>
													 </TABLE>
													 <ul>
														 <li>@ref ImIipDefine_D_IM_IIP_MASTER_IF0	[PIXFMTTBL.MTIFYG = 1b]
														 <li>@ref ImIipDefine_D_IM_IIP_MASTER_IF1	[PIXFMTTBL.MTIFYG = 0b]
														 <li>@ref D_IM_IIP_MASTER_IF2	[PIXFMTTBL.MTIFYG = 0b]
													 </ul> */
	UCHAR				masterifCbB;			/**< PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) output image is master I/F 0, 1 or 2.
													 Please refrer @ref masterifYG.
													 */
	UCHAR				masterifCrR;			/**< PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) output image is master I/F 0, 1 or 2.
													 Please refrer @ref masterifYG.
													 */
	UCHAR				masterifAlpha;			/**< PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha output image is master I/F 0, 1 or 2
													 Please refrer @ref masterifYG.
													 */
	UINT32				alphaSubsampling;		/**< PIXFMTTBL.ASUBSPL[1:0] <br><br> Control Alpha subsampling.
													 <ul>
														 <li>@ref ImIipDefine_D_IM_IIP_ALPHA_NO_SUBSAMP	[PIXFMTTBL.ASUBSPL[1:0] = 00b]
														 <li>@ref ImIipDefine_D_IM_IIP_ALPHA_H_SUBSAMP	[PIXFMTTBL.ASUBSPL[1:0] = 01b]
														 <li>@ref ImIipDefine_D_IM_IIP_ALPHA_HV_SUBSAMP	[PIXFMTTBL.ASUBSPL[1:0] = 10b]
													 </ul> */
	UINT32				pixOutsideImg;		/**< PIXFMTTBL.OARBHV <br><br> Control pixel value outside image.
													 <ul>
														 <li>@ref ImIipDefine_D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE	[PIXFMTTBL.OARBHV = 0b]
														 <li>@ref ImIipDefine_D_IM_IIP_OUTSIDE_IMG_EDGE			[PIXFMTTBL.OARBHV = 1b]
													 </ul> */
	USHORT				yGValOutsideImg;	/**< PIXFMTTBL.OARVALYG[15:0] <br><br> pixel value outside Y(G) image.
												   This parameter is valid
												   only when TImIipPixfmttbl::pixOutsideImg is set to ImIipDefine_D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE.*/
	USHORT				cbBValOutsideImg;	/**< PIXFMTTBL.OARVALB[15:0] <br><br> pixel value outside Cb(B) image.
												   This parameter is valid
												   only when TImIipPixfmttbl::pixOutsideImg is set to ImIipDefine_D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE.*/
	USHORT				crRValOutsideImg;	/**< PIXFMTTBL.OARVALR[15:0] <br><br> pixel value outside Cr(R) image.
												   This parameter is valid
												   only when TImIipPixfmttbl::pixOutsideImg is set to ImIipDefine_D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE.*/
	USHORT				alphaValOutsideImg;	/**< PIXFMTTBL.OARVALA[15:0] <br><br> pixel value outside Alpha image.
												   This parameter is valid
												   only when TImIipPixfmttbl::pixOutsideImg is set to ImIipDefine_D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE.*/
	USHORT				width;					/**< PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383] */
	USHORT				lines;					/**< PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383] */

	TImIipLineBytes	lineBytes;				/**< The size of byte of Global image 1 line. */
	TImIipImgAddr	addr;					/**< Beginning address of Global image. */
} TImIipPixfmttbl;

/** UNITINFTBL structure */
typedef struct {
	UCHAR	unitCtrl;			/**< UNITINFTBL.HWEN <br><br> Control unit.
													 <ul>
														 <li>@ref ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG	[UNITINFTBL.HWEN = 0b]
														 <li>@ref ImIipDefine_D_IM_IIP_HW_CTRL_AUTO		[UNITINFTBL.HWEN = 1b]
													 </ul> */
	UCHAR	chainEnable;		/**< UNITINFTBL.CHAIN <br><br> Chain control.
													 <ul>
														 <li>@ref ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE	[UNITINFTBL.CHAIN = 0b]
														 <li>@ref ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_ENABLE		[UNITINFTBL.CHAIN = 1b]
													 </ul> */
	ULONG	unitParamAddr;	/**< UNITINFTBL.PADRS[31:0] <br><br> Beginning address of unit parameter. Should be aligned on 8. */
	ULLONG	loadUnitParamFlag;
} TImIipUnitCfg;

/** im_iip_ctrl_unitinftbl() parameter structure */
typedef struct {
	TImIipUnitCfg*	pLD[ImIipStruct_D_IM_IIP_UNIT_LD_MAXNUM];	/**< Pointer of Loader UNITINFTBL parameters.
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
	TImIipUnitCfg*	pFLT;		/**< Pointer of FLT UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b. */
	TImIipUnitCfg*	pAFN[ImIipStruct_D_IM_IIP_UNIT_AFN_MAXNUM];	/**< Pointer of Affine UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 <ul>
											<li>pAFN[0]	Affine 0
											<li>pAFN[1]	Affine 1
											<li>pAFN[2]	Affine 2
											<li>pAFN[3]	Affine 3
										 </ul> */
	TImIipUnitCfg*	pFRECT[ImIipStruct_D_IM_IIP_UNIT_FRECT_MAXNUM];	/**< Pointer of FRECT UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 <ul>
											<li>pFRECT[0]	FRECT 0
											<li>pFRECT[1]	FRECT 1
										 </ul> */
	TImIipUnitCfg*	pMON;		/**< Pointer of Monitor UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b. */
	TImIipUnitCfg*	pSL[ImIipStruct_D_IM_IIP_UNIT_SL_MAXNUM];	/**< Pointer of Store UNITINFTBL parameters.
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
	TImIipUnitCfg*	pCSC[ImIipStruct_D_IM_IIP_UNIT_CSC_MAXNUM];	/**< Pointer of CSC UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 <ul>
											<li>pCSC[0]	CSC 0
											<li>pCSC[1]	CSC 1
											<li>pCSC[2]	CSC 2
											<li>pCSC[3]	CSC 3
										 </ul> */
	TImIipUnitCfg*	pLUT;		/**< Pointer of LUT UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b. */
	TImIipUnitCfg*	pGPC;		/**< Pointer of GPC UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b. */
	TImIipUnitCfg*	pBLEND[ImIipStruct_D_IM_IIP_UNIT_BLEND_MAXNUM];	/**< Pointer of Blend UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 <ul>
											<li>pBLEND[0]	Blend 0
											<li>pBLEND[1]	Blend 1
										 </ul> */
	TImIipUnitCfg*	pCFL;	/**< Pointer of Cache Flow UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 */
	TImIipUnitCfg*	pMFT;	/**< Pointer of MFT UNITINFTBL parameters.
										 If it is set to NULL, the unit's UNITINFTBL.HWEN is set to 0b.
										 */
} TImIipUnitinftbl;

/** im_iip_ctrl_lut() parameter structure */
typedef struct {
	UINT32					bufferBytes;	/**< The bytes of user LUT buffer "bufferAddr". Should be align on 2. */
	const USHORT*			bufferAddr;	/**< Beginning address of user LUT buffer. */
	EImIipLutramType	lutramType;	/**< Beginning position of written LUTRAM. */
} TImIipLut;

/** im_iip_sub_ctrl_axi() parameter structure */
typedef struct {
	UINT32	transReqCtrl;
	UINT32	cacheType;
	UINT32	protectionType;
} TIMIipCtrlAxi;

/** im_iip_sub_ctrl_axi_all() parameter structure */
typedef struct {
	TIMIipCtrlAxi*		imgcache0;	/**< Pointer of AXI control parameters for Image data cache0. */
	TIMIipCtrlAxi*		imgcache1;	/**< Pointer of AXI control parameters for Image data cache1. */
	TIMIipCtrlAxi*		imgcache2;	/**< Pointer of AXI control parameters for Image data cache3. */
	TIMIipCtrlAxi*		dp;			/**< Pointer of AXI control parameters for Dispatch sequencer. */
	TIMIipCtrlAxi*		afn0;		/**< Pointer of AXI control parameters for Affine 0. */
	TIMIipCtrlAxi*		afn1;		/**< Pointer of AXI control parameters for Affine 1. */
	TIMIipCtrlAxi*		afn2;		/**< Pointer of AXI control parameters for Affine 2. */
	TIMIipCtrlAxi*		afn3;		/**< Pointer of AXI control parameters for Affine 3. */
	TIMIipCtrlAxi*		frect0;		/**< Pointer of AXI control parameters for FRECT 0. */
	TIMIipCtrlAxi*		frect1;		/**< Pointer of AXI control parameters for FRECT 1. */
	TIMIipCtrlAxi*		gpc;		/**< Pointer of AXI control parameters for GPC. */
	TIMIipCtrlAxi*		sl0;		/**< Pointer of AXI control parameters for Store 0. */
	TIMIipCtrlAxi*		sl1;		/**< Pointer of AXI control parameters for Store 1. */
	TIMIipCtrlAxi*		sl2;		/**< Pointer of AXI control parameters for Store 2. */
	TIMIipCtrlAxi*		sl3;		/**< Pointer of AXI control parameters for Store 3. */
	TIMIipCtrlAxi*		sl4;		/**< Pointer of AXI control parameters for Store 4. */
	TIMIipCtrlAxi*		sl5;		/**< Pointer of AXI control parameters for Store 5. */
	TIMIipCtrlAxi*		sl6;		/**< Pointer of AXI control parameters for Store 6. */
	TIMIipCtrlAxi*		sl7;		/**< Pointer of AXI control parameters for Store 7. */
	TIMIipCtrlAxi*		sl8;		/**< Pointer of AXI control parameters for Store 8. */
} TIMIipCtrlAxiAll;

/** im_iip_struct_ctrl_base() parameter structure */
typedef struct {
#if 0	// B2Y Link not support
	UINT32		b2yLink;
#endif	// B2Y Link not support
	UINT32		enableInterruptFlag;
	UINT32		sl0InterruptLines;
	UINT32		sl1InterruptLines;
	UINT32		sl2InterruptLines;
	UINT32		sl3InterruptLines;
	UINT32		sl4InterruptLines;
	UINT32		sl5InterruptLines;
	UINT32		sl6InterruptLines;
	UINT32		sl7InterruptLines;
	UINT32		sl8InterruptLines;
	T_IM_IIP_CALLBACK		intHandler;
	UINT32		cacheFlushCtrl[ImIipStruct_D_IM_IIP_CACHE_MAXNUM];	/**< PDCCTL[n].FLHALL <br><br> Control flush cache.
												 <ul>
													 <li>@ref ImIipDefine_D_IM_IIP_NON_FLUSH_IMGCACHE_START	[PDCCTL.FLHALL = 0b]
													 <li>@ref D_IM_IIP_FLUSH_IMGCACHE_START		[PDCCTL.FLHALL = 1b]
												 </ul> */
	UINT32		extBitCtrlLess8Bits[ImIipStruct_D_IM_IIP_CACHE_MAXNUM];	/**< PDCCTL[n].EXTBIT <br><br> bit extenstion.
												 <ul>
													 <li>@ref D_IM_IIP_EXTBIT_LOWER_ALIGNED		[PDCCTL.EXTBIT = 0b]
													 <li>@ref ImIipDefine_D_IM_IIP_EXTBIT_UPPER_ALIGNED		[PDCCTL.EXTBIT = 1b]
												 </ul> */
} TImIipCtrlBase;

/** Im_IIP_Get_MAXMON() and Im_IIP_Get_MINMON() parameter structure */
typedef struct {
	USHORT	posX;		/**< MAXMON.HPOINTMAX_0/1/2/3[13:0], MINMON.HPOINTMIN_0/1/2/3[13:0] and ADDMON.HPOINTADD_0/1/2/3[13:0] */
	USHORT	posY;		/**< MAXMON.VPOINTMAX_0/1/2/3[13:0], MINMON.VPOINTMIN_0/1/2/3[13:0] and ADDMON.VPOINTADD_0/1/2/3[13:0] */
	INT32	value;		/**< MAXMON.MAXVAL_0/1/2/3[14:0], MINMON.MINVAL_0/1/2/3[14:0] and ADDMON.ADDVAL_0/1/2/3[31:0] */
} TImIipMon;

/** Im_IIP_Get_MAXMON() parameter structure */
typedef struct {
	TImIipMon	max[4];			/**< The result of maximum value monitor.
										 <ul>
											 <li>max[0]	D0 component
											 <li>max[1]	D1 component
											 <li>max[2]	D2 component
											 <li>max[3]	D3 component
										 </ul> */
} TImIipMaxmon;

/** Im_IIP_Get_MINMON() parameter structure */
typedef struct {
	TImIipMon	min[4];			/**< The result of minimum value monitor.
										 <ul>
											 <li>min[0]	D0 component
											 <li>min[1]	D1 component
											 <li>min[2]	D2 component
											 <li>min[3]	D3 component
										 </ul> */
} TImIipMinmon;

/** Im_IIP_Get_ADDMON() parameter structure */
typedef struct {
	TImIipMon	add[4];			/**< The result of cumulo-addition monitor.
										 <ul>
											 <li>add[0]	D0 component
											 <li>add[1]	D1 component
											 <li>add[2]	D2 component
											 <li>add[3]	D3 component
										 </ul> */
} TImIipAddmon;

/** Im_IIP_Get_ImgCache_Access_Info() parameter structure */
typedef struct {
	ULONG	realAccessCounter;	/**< PDCRAC.PDCRAC[31:0]	*/
	ULONG	realMissCounter;		/**< PDCRMC.PDCRMC[31:0]	*/
} TImIipAccessInfo;

/** Im_IIP_Get_AXI_Status() parameter structure */
typedef struct {
	ULONG	readChannelStatus;	/**< AXRSTS	register */
	ULONG	writeChannelStatus;	/**< AXWSTS register */
} TImIipAxiStatus;

/** im_iip_static_get_genline() parameter structure */
typedef struct {
	USHORT	b2yOutlineno;									/**< Generated lines of B2Y macro @@GENLINE.b2yOutlineno */
	USHORT	afnOutlineno[ImIipStruct_D_IM_IIP_UNIT_AFN_MAXNUM];		/**< Generated lines of AFN0~2 unit @@GENLINE.AFNn_OUTLINENO (n=0~3) */
	USHORT	frectOutlineno[ImIipStruct_D_IM_IIP_UNIT_FRECT_MAXNUM];	/**< Generated lines of FRECT0~1 unit @@GENLINE.FRn_OUTLINENO (n=0~1)*/
	USHORT	ldOutlineno[ImIipStruct_D_IM_IIP_UNIT_LD_MAXNUM];			/**< Generated lines of LD0~7 unit @@GENLINE.LDn_OUTLINENO (n=0~7) */
	USHORT	fltOutlineno;									/**< Generated lines of FLT unit @@GENLINE.fltOutlineno */
} TImIipGenline;

/** im_iip_static_get_debug_monitor() parameter structure */
typedef struct {
	ULLONG		dataOutPort;								/**< DTOUT_MON register value. */
	ULLONG		waitingPort;								/**< WAIT_MON register value. */
	USHORT		imgcacheDataOut[ImIipStruct_D_IM_IIP_CACHE_MAXNUM];	/**< PDC_DTOUT_MON register value. */
	USHORT		imgcacheReady[ImIipStruct_D_IM_IIP_CACHE_MAXNUM];		/**< PDC_RDY_MON register value. */
} TImIipDebugMonitor;

typedef struct {
	EImIipAdepth		alphaDepth;			// PIXFMTTBL.ADEPTH
	UINT32				alphaSubsampling;		// PIXFMTTBL.ASUBSPL
} TImIipUtilAlphaInfo;

// PHSZ, PVSZ parameter for Loader and STS Unit.
typedef struct {
	UINT32	PHSZ0;
	UINT32	PHSZ1;
	UINT32	PVSZ0;
	UINT32	PVSZ1;
} TImIipUtilPhvsz;

// Parameter of Im_IIP_Open_SWTRG().
typedef struct {
	ULLONG						unitidBitmask;
	UINT32						pixidBitmask;
	UINT32						openResBitmask;
} TImIipUtilParamOpen;

// Parameter of Im_IIP_Open_SWTRG(), Im_IIP_Set_Interrupt() and Im_IIP_Wait_End()>
typedef struct {
	UINT32						intFact;	// Parameter "interrupt_bitmask" of Im_IIP_Set_Interrupt() and Parameter "wait_factor" of Im_IIP_Wait_End()
	INT32						waitTime;	// Parameter "waitTime" of Im_IIP_Open_SWTRG() and Parameter "waitTime" of Im_IIP_Wait_End()
} TImIipUtilParamWait;

typedef struct {
	TImIipUtilParamOpen	openParam;
	TImIipUtilParamWait	waitParam;
	ULONG						paramBufferAddr;
	UCHAR						paramMasterIf;
	TImIipPixfmttbl			pixfmttbl[2];
	UINT32						pixid[2];
	TImIipUnitCfg			unitCfgAfn;
	TImIipUnitCfg			unitCfgSl;
	EImIipAxiId				axiIdAfn;
	EImIipAxiId				axiIdSl;
	TIMIipCtrlAxi			axiCfgAfn;
	TIMIipCtrlAxi			axiCfgSl;

	T_IM_IIP_PARAM_STS*			pParamSl;
	T_IM_IIP_PARAM_AFN*			pParamAfn;
	T_IM_IIP_PARAM_AFN_OPCOL_0*	pAfnStructParam;
} TImIipUtilParamResizeRotate;

// Internal parameter of IM_IIP_Utility_CSC()
typedef struct {
	TImIipUtilParamOpen	openParam;
	TImIipUtilParamWait	waitParam;
	ULONG						paramBufferAddr;
	UCHAR						paramMasterIf;
	TImIipPixfmttbl			pixfmttbl[2];
	UINT32						pixid[2];
	TImIipUnitCfg			unitCfg1D;
	TImIipUnitCfg			unitCfgCsc;
	TImIipUnitCfg			unitCfgSl;
	EImIipAxiId				axiIdLd;
	EImIipAxiId				axiIdSl;
	TIMIipCtrlAxi			axiCfg1D;
	TIMIipCtrlAxi			axiCfgSl;

	T_IM_IIP_PARAM_1DL*			pParam1D;
	T_IM_IIP_PARAM_CSC*			pParamCsc;
	T_IM_IIP_PARAM_STS*			pParamSl;
} TImIipUtilParamCsc;

// Internal parameter of IM_IIP_Utility_LUT()
typedef struct {
	TImIipUtilParamOpen	openParam;
	TImIipUtilParamWait	waitParam;
	ULONG						paramBufferAddr;
	UCHAR						paramMasterIf;
	TImIipPixfmttbl			pixfmttbl[2];
	UINT32						pixid[2];
	TImIipUnitCfg			unitCfg1D;
	TImIipUnitCfg			unitCfgLut;
	TImIipUnitCfg			unitCfgSl;
	EImIipAxiId				axiIdLd;
	EImIipAxiId				axiIdSl;
	TIMIipCtrlAxi			axiCfg1D;
	TIMIipCtrlAxi			axiCfgSl;

	T_IM_IIP_PARAM_1DL*			pParam1D;
	T_IM_IIP_PARAM_LUT*			pParamLut;
	T_IM_IIP_PARAM_STS*			pParamSl;
} TImIipUtilParamLut;

typedef struct {
	TImIipUtilParamOpen	openParam;
	TImIipUtilParamWait	waitParam;
	ULONG						paramBufferAddr;
	UCHAR						paramMasterIf;
	TImIipPixfmttbl			pixfmttbl[3];
	UINT32						pixid[3];
	TImIipUnitCfg			unitCfg1D[2];
	TImIipUnitCfg			unitCfgAlp;
	TImIipUnitCfg			unitCfgSl;
	EImIipAxiId				axiIdLd[2];
	EImIipAxiId				axiIdSl;
	TIMIipCtrlAxi			axiCfg1D[2];
	TIMIipCtrlAxi			axiCfgSl;

	T_IM_IIP_PARAM_1DL*			pParam1D[2];
	T_IM_IIP_PARAM_BLEND*		pParamAlp;
	T_IM_IIP_PARAM_STS*			pParamSl;
} TImIipUtilParamAlpha;

typedef enum {
	ImIipStruct_E_IM_IIP_UTIL_ROTATE_000 = 0,	/**< 0 */
	ImIipStruct_E_IM_IIP_UTIL_ROTATE_090 = 1,	/**< 90 */
	ImIipStruct_E_IM_IIP_UTIL_ROTATE_180 = 2,	/**< 180 */
	ImIipStruct_E_IM_IIP_UTIL_ROTATE_270 = 3,	/**< 270 */
	ImIipStruct_E_IM_IIP_UTIL_ROTATE_MAX = 4,	/**< Maximum value */
} EImIipUtilRotate;

/** Resize mode (Interpolation mode) */
typedef enum {
	ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_NEAREST = E_IM_IIP_PARAM_ITMD_NEAREST,	/**< Nearest */
	ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR = E_IM_IIP_PARAM_ITMD_BI_LINEAR,	/**< Bi-linear */
	ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BICUBIC = E_IM_IIP_PARAM_ITMD_BI_CUBIC	/**< Bi-cubic */
} EImIipUtilResizwMode;

/** Flip status */
typedef enum {
	ImIipStruct_E_IM_IIP_UTIL_FLIP_OFF = 0,			/**< Off */
	ImIipStruct_E_IM_IIP_UTIL_FLIP_MIRROR,			/**< Mirror */
	ImIipStruct_E_IM_IIP_UTIL_FLIP_REVERSE,			/**< Reverse */
	ImIipStruct_E_IM_IIP_UTIL_FLIP_MIR_AND_REV,		/**< Mirror and Reverse */
	ImIipStruct_E_IM_IIP_UTIL_FLIP_MAX,				/**< Maximum value */
} EImIipUtilFlip;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/** Rectangle (Source image area) */
typedef struct {
	DOUBLE	top;		/**< Vertical position of top-left pixel */
	DOUBLE	left;		/**< Horizontal position of top-left pixel */
	USHORT	width;		/**< Width */
	USHORT	lines;		/**< Lines */
} TImIipUtilRect;

/** Rectangle (Source image area) */
typedef struct {
	USHORT	top;		/**< Vertical position of top-left pixel */
	USHORT	left;		/**< Horizontal position of top-left pixel */
	USHORT	width;		/**< Width */
	USHORT	lines;		/**< Lines */
} TImIipUtilRectInt;

/** Global Image info. */
typedef struct {
	UINT32				alpha;
	EImIipFtype		frameType;
	EImIipPfmt		pixFormat;
	TImIipChunky		chunkyColor;			/**< PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component. */
	UCHAR				signYG;
	UCHAR				signCbB;
	UCHAR				signCrR;
	UCHAR				signD3;
	USHORT				width;					/**< PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383] */
	USHORT				lines;					/**< PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]	*/
	TImIipLineBytes	lineBytes;				/**< The size of byte of Global image 1 line. */
	TImIipImgAddr	addr;					/**< Beginning address of Global image. */
	UCHAR				masterifYG;
	UCHAR				masterifCbB;
	UCHAR				masterifCrR;
	UCHAR				masterifAlpha;
} TImIipUtilImgGbl;

/** Image info. */
typedef struct {
	TImIipUtilRect			rect;	/**< Rectangle info. (Source image area) */
	TImIipUtilImgGbl		gbl;	/**< Global image info. */
} TImIipUtilImg;

/** Image info. */
typedef struct {
	TImIipUtilRectInt		rect;	/**< Rectangle info. (Source image area) */
	TImIipUtilImgGbl		gbl;	/**< Global image info. */
} TImIipUtilImgInt;

/** Alpha unit info. */
typedef struct {
	E_IM_IIP_PARAM_ALPHA_STEP	step;			/**< Bit depth of alpha */
	E_IM_IIP_PARAM_ALPHA_SEL	sel;			/**< Select alpha value which IIP uses */
	E_IM_IIP_PARAM_ALPHA_OUT	out;			/**< Select alpha value which IIP outputs */
	USHORT						alphaVal[4];	/**< Fixed alpha value.
													 This parameter is valid
													 only when TImIipUtilAlpha::sel is E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL. */
} TImIipUtilAlpha;

/** Parameter of IM_IIP_Utility_ResizeRotate */
typedef struct {
	EImIipUnitId			afnUnitid;			/**< UNITID of AFN */
	EImIipUnitId			slUnitid;			/**< UNITID of SL */
	EImIipPixid				srcPixid;			/**< Source image PIXID */
	EImIipPixid				dstPixid;			/**< Destination image PIXID */
	E_IM_IIP_PARAM_SCUB			biCubicUnitid;	/**< BI-Cubic Unit ID */
	TImIipUtilImg			src;				/**< Source image info. */
	TImIipUtilImgInt		dst;				/**< Destination image info. */
	E_IM_IIP_PARAM_CSEL			afnCacheSelect;	/**< AFN cache select. */
	UINT32						pixDepth;

	EImIipUtilRotate		rotation;			/**< Angle of rotation */
	EImIipUtilFlip			flip;				/**< flip state */
	EImIipUtilResizwMode	resizeMode;		/**< Resize mode */
} TImIipUtilRr;

/** Parameter of IM_IIP_Utility_CSC */
typedef struct {
	EImIipUnitId			ldUnitid;			/**< UNITID of Loader */
	EImIipUnitId			cscUnitid;			/**< UNITID of CSC */
	EImIipUnitId			slUnitid;			/**< UNITID of SL */
	EImIipPixid				srcPixid;			/**< Source image PIXID */
	EImIipPixid				dstPixid;			/**< Destination image PIXID */
	TImIipUtilImgInt		src;				/**< Source image info. */
	TImIipUtilImgInt		dst;				/**< Destination image info. */
	E_IM_IIP_PARAM_CSEL			ldCacheSelect;	/**< Loader cache select. */
	UINT32						pixDepth;
	EImIipAdepth				alphaDepth;
	UINT32						alphaSubsampling;

	SHORT						csck[4][4];			/**< CSCK register */
	ULONG						csckModeSel;		/**< MDSEL register */
	E_IM_IIP_PARAM_ALPSEL		alphaInSel;		/**< ALPSEL register */
	E_IM_IIP_PARAM_ALOSEL		alphaOutSel;		/**< ALOSEL register */
	UINT32						alphaVal;			/**< ALPVAL register.
														 This parameter is valid only when
														 TImIipUtilCsc::alpha_sel is E_IM_IIP_PARAM_ALPSEL_ALPVAL_REG. */
	BYTE						slSftval;				/**< SL unit's SFTVAL */


} TImIipUtilCsc;

/** LUTRAM info. */
typedef struct {
	UINT32	bufferBytes[ImIipStruct_E_IM_IIP_LUTRAM_TYPE_MAX];
	const USHORT*	bufferAddr[ImIipStruct_E_IM_IIP_LUTRAM_TYPE_MAX];
} TImIipLutram;

/** Parameter of IM_IIP_Utility_LUT */
typedef struct {
	EImIipUnitId			ldUnitid;			/**< UNITID of Loader */
	EImIipUnitId			lutUnitid;			/**< UNITID of LUT */
	EImIipUnitId			slUnitid;			/**< UNITID of SL */
	EImIipPixid				srcPixid;			/**< Source image PIXID */
	EImIipPixid				dstPixid;			/**< Destination image PIXID */
	TImIipUtilImgInt		src;				/**< Source image info. */
	TImIipUtilImgInt		dst;				/**< Destination image info. */
	E_IM_IIP_PARAM_CSEL			ldCacheSelect;	/**< Loader cache select. */
	UINT32						pixDepth;
	EImIipAdepth				alphaDepth;		/**< PIXFMTTBL.ADEPTH[2:0] <br><br> Depth of alpha.
													 <ul>
														 <li>@ref ImIipStruct_E_IM_IIP_ADEPTH_8BITS		[PIXFMTTBL.ADEPTH[2:0] = 000b]
														 <li>@ref ImIipStruct_E_IM_IIP_ADEPTH_4BITS		[PIXFMTTBL.ADEPTH[2:0] = 011b]
													 </ul> */
	UINT32						alphaSubsampling;

	UINT32						lutPixDepth[4];
	UINT32						splbit[4];
	TImIipLutram				lutram;				/**< Parameters of LUTRAM */
} TImIipUtilLut;

/** Parameter of IM_IIP_Utility_AlphaBlend */
typedef struct {
	EImIipUnitId			ldUnitid[2];		/**< UNITID of Loader */
	EImIipUnitId			blendUnitid;		/**< UNITID of Alpha */
	EImIipUnitId			slUnitid;			/**< UNITID of SL */
	EImIipPixid				srcPixid[2];		/**< Source image PIXID */
	EImIipPixid				dstPixid;			/**< Destination image PIXID */
	TImIipUtilImgInt		src[2];				/**< Source image info. */
	TImIipUtilImgInt		dst;				/**< Destination image info. */
	E_IM_IIP_PARAM_CSEL			ldCacheSelect[2];	/**< Loader cache select. */
	UINT32						pixDepth;
	EImIipAdepth				alphaDepth;
	UINT32						alphaSubsampling;

	TImIipUtilAlpha			alpha;				/**< Parameter of Alpha blend */
} TImIipUtilAlphablend;

struct _ImIipStruct {
	KObject parent;
};

KConstType 		   				 	im_iip_struct_get_type(void);
ImIipStruct*		        			im_iip_struct_get(void);

extern VOID 							Im_IIP_On_Hclk( VOID );
extern VOID 							Im_IIP_Off_Hclk( VOID );
extern VOID 							Im_IIP_On_Pclk( VOID );
extern VOID 							Im_IIP_Off_Pclk( VOID );

#endif /* __IM_IIP_STRUCT_H__ */
