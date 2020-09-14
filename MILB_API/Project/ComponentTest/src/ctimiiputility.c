/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipUtility类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_im_iip_utility.c
 * @brief		IIP Utility ct code
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

// CT header
#include "ctimiip.h"

// im_iip header
#include "imiipdefine.h"
#include "imiipstruct.h"
#include "imiipparamenum.h"
#include "ctimiiputility.h"

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#include <stdio.h>
#endif
#endif //CO_CT_IM_IIP_DISABLE

K_TYPE_DEFINE_WITH_PRIVATE(CtImIipUtility, ct_im_iip_utility);
#define CT_IM_IIP_UTILITY_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImIipUtilityPrivate,CT_TYPE_IM_IIP_UTILITY))

struct _CtImIipUtilityPrivate {
    CtImIipUtility *ciIipUtility;
	kint32			ercd;
	kuchar 			paramMasterIf;
	kint32 			waitTime;
};

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#define CtImIipUtility_DDIM_PRINT(arg)		{DDIM_User_Printf arg;}		/**< printf function inside DDIM */
#endif

static void ct_im_iip_utility_constructor(CtImIipUtility *self) 
{
	CtImIipUtilityPrivate *priv = CT_IM_IIP_UTILITY_GET_PRIVATE(self);
	priv->ciIipUtility 			= ct_im_iip_utility_new();
	priv->paramMasterIf 		= ImIipDefine_D_IM_IIP_MASTER_IF0;
	priv->waitTime 				= 60;
}

static void ct_im_iip_utility_destructor(CtImIipUtility *self)
{
	CtImIipUtilityPrivate *priv = CT_IM_IIP_UTILITY_GET_PRIVATE(self);
	if(priv->ciIipUtility){
		k_object_unref(priv->ciIipUtility);
	}
	priv->ciIipUtility = NULL;
}
/*
 *PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/

// Im_IIP_Utility_ResizeRotate 14-1-1
#undef D_IM_IIP_FUNC_NAME
#define CtImIipUtility_D_IM_IIP_FUNC_NAME "ct_im_iip_utility_14_1_1: "
kint32 ct_im_iip_utility_14_1_1(CtImIipUtility *self)
{
	CtImIipUtilityPrivate *priv = CT_IM_IIP_UTILITY_GET_PRIVATE(self);
	
	TImIipUtilRr iipUtilRr0 = {
		.afnUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_AFN1,		// UNITID of AFN
		.slUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL3,			// UNITID of SL
		.srcPixid = ImIipStruct_E_IM_IIP_PIXID_1,				// Source image PIXID
		.dstPixid = ImIipStruct_E_IM_IIP_PIXID_2,				// Destination image PIXID
		.src = {									// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> ... (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> ... (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> ... (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> ... (offset +3).
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,				
				// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_LINES,
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH,			// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A,	// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.dst = {								// Destination image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = 320,							// Width
				.lines = 240,							// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC420,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br>Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0]<br><br>...(offset+0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2]<br><br>...(offset+1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4]<br><br>...(offset+2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6]<br><br>...(offset+3).
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = 320,	// PIXFMTTBL.PICHSZ[14:0]	<br><br> The number of horizontal pixel. [16~16383]
				.lines = 240,	// PIXFMTTBL.PICVSZ[13:0]	<br><br> The number of vertical pixel. [2~16383]
				.lineBytes = {						// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,			// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A,	// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.afnCacheSelect = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,	// AFN cache select.
		.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_8BITS,			// PIXFMTTBL.PDEPTH[2:0] <br><br> Depth of pixel.
		.rotation = ImIipStruct_E_IM_IIP_UTIL_ROTATE_000,		// Angle of rotation
		.resizeMode = ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR,// Resize mode
	};

	TImIipUtilRr iipUtilRr1 = {
		.afnUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_AFN0,		// UNITID of AFN
		.slUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL2,			// UNITID of SL
		.srcPixid = ImIipStruct_E_IM_IIP_PIXID_4,				// Source image PIXID
		.dstPixid = ImIipStruct_E_IM_IIP_PIXID_5,				// Destination image PIXID
		.src = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br>Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> ...(offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> ...(offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> ...(offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> ...(offset +3).
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,
				// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_LINES,
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH,			// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A,	// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.dst = {								// Destination image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_LINES,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_WIDTH,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> ... (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> ... (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> ... (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> ... (offset +3).
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_LINES,
				// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_WIDTH,
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG   = 480,
					.cbB  = 480,
					.crR  = 480,
					.Alpha = 480,			// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_2_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_2_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_2_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_2_YCC422_U8_A,	// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.afnCacheSelect = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,	// AFN cache select.
		.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_8BITS,			// PIXFMTTBL.PDEPTH[2:0] <br><br> Depth of pixel.
		.rotation = ImIipStruct_E_IM_IIP_UTIL_ROTATE_090,		// Angle of rotation
		.resizeMode = ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR,// Resize mode
	};
	kuchar paramBuffer[ImIipDefine_D_IM_IIP_UTIL_RR_BUF_BYTES *2];
	kulong paramBufferAddr = CtImIip_ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align
	
	CtImIipUtility_DDIM_PRINT((CtImIipUtility_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = IM_IIP_Utility_ResizeRotate(&iipUtilRr0, &iipUtilRr1, priv->paramMasterIf,
										paramBufferAddr, priv->waitTime);
	CtImIipUtility_DDIM_PRINT((CtImIipUtility_D_IM_IIP_FUNC_NAME "result = 0x%x.\n", priv->ercd));

	return D_DDIM_OK;
}


// Im_IIP_Utility_ResizeRotate 14-1-2
#undef CtImIipUtility_D_IM_IIP_FUNC_NAME
#define CtImIipUtility_D_IM_IIP_FUNC_NAME "ct_im_iip_utility_14_1_2: "
kint32 ct_im_iip_utility_14_1_2(CtImIipUtility *self)
{
	CtImIipUtilityPrivate *priv = CT_IM_IIP_UTILITY_GET_PRIVATE(self);

	TImIipUtilRr iipUtilRr0 = {
		.afnUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_AFN0,		// UNITID of AFN
		.slUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL2,			// UNITID of SL
		.srcPixid = ImIipStruct_E_IM_IIP_PIXID_4,				// Source image PIXID
		.dstPixid = ImIipStruct_E_IM_IIP_PIXID_5,				// Destination image PIXID
		.src = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> ... (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> ... (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> ... (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> ... (offset +3).
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,
				// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_LINES,
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH,			// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A,	// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.dst = {								// Destination image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_LINES,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_WIDTH,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> ... (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> ... (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> ... (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> ... (offset +3).
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_LINES,
				// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_WIDTH,
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG   = 480,
					.cbB  = 480,
					.crR  = 480,
					.Alpha = 480,			// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A,	// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.afnCacheSelect = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,	// AFN cache select.
		.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_8BITS,			// PIXFMTTBL.PDEPTH[2:0] <br><br> Depth of pixel.
		.rotation = ImIipStruct_E_IM_IIP_UTIL_ROTATE_270,		// Angle of rotation
		.resizeMode = ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR,// Resize mode
	};

	TImIipUtilRr iipUtilRr1 = {
		.afnUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_AFN1,		// UNITID of AFN
		.slUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL3,			// UNITID of SL
		.srcPixid = ImIipStruct_E_IM_IIP_PIXID_1,				// Source image PIXID
		.dstPixid = ImIipStruct_E_IM_IIP_PIXID_2,				// Destination image PIXID
		.src = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> ... (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> ... (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> ... (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> ... (offset +3).
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,
				// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_LINES,
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH,			// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A,	// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.dst = {								// Destination image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> ... (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> ... (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> ... (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> ... (offset +3).
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,
				// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_LINES,
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,			// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_2_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_2_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_2_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_2_YCC422_U8_A,	// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.afnCacheSelect = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,	// AFN cache select.
		.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_8BITS,			// PIXFMTTBL.PDEPTH[2:0] <br><br> Depth of pixel.
		.rotation = ImIipStruct_E_IM_IIP_UTIL_ROTATE_180,		// Angle of rotation
		.resizeMode = ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR,// Resize mode
	};
	kuchar paramBuffer[ImIipDefine_D_IM_IIP_UTIL_RR_BUF_BYTES *2];
	kulong paramBufferAddr = CtImIip_ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align

	CtImIipUtility_DDIM_PRINT((CtImIipUtility_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = IM_IIP_Utility_ResizeRotate(&iipUtilRr0, &iipUtilRr1, priv->paramMasterIf,
										paramBufferAddr, priv->waitTime);
	CtImIipUtility_DDIM_PRINT((CtImIipUtility_D_IM_IIP_FUNC_NAME "result = 0x%x.\n", priv->ercd));

	return D_DDIM_OK;
}


// Im_IIP_Utility_ResizeRotate 14-1-3
#undef CtImIipUtility_D_IM_IIP_FUNC_NAME
#define CtImIipUtility_D_IM_IIP_FUNC_NAME "ct_im_iip_utility_14_1_3: "
kint32 ct_im_iip_utility_14_1_3(CtImIipUtility *self)
{
	CtImIipUtilityPrivate *priv = CT_IM_IIP_UTILITY_GET_PRIVATE(self);

	TImIipUtilRr iipUtilRr0 = {
		.afnUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_AFN0,		// UNITID of AFN
		.slUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL2,			// UNITID of SL
		.srcPixid = ImIipStruct_E_IM_IIP_PIXID_4,				// Source image PIXID
		.dstPixid = ImIipStruct_E_IM_IIP_PIXID_5,				// Destination image PIXID
		.src = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> ... (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> ... (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> ... (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> ... (offset +3).
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,
				// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_LINES,
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH,			// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A,	// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.dst = {								// Destination image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_HD_4_3_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_HD_4_3_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0]<br><br>Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,//...[1:0]<br><br>Chunky component(offset+0)
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,//...[3:2]<br><br>Chunky component(offset+1)
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,//...[5:4]<br><br>Chunky component(offset+2)
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,//...[7:6]<br><br>Chunky component(offset+3)
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_HD_4_3_WIDTH,
				// PIXFMTTBL.PICHSZ[14:0]<br><br>number of horizontal pixel.[16~16383]
				.lines = CtImIip_D_IM_IIP_HD_4_3_LINES,
				// PIXFMTTBL.PICVSZ[13:0]<br><br>The number of vertical pixel.[2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_HD_4_3_YCC422_U8_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_HD_4_3_YCC422_U8_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_HD_4_3_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_HD_4_3_YCC422_U8_A_GLOBAL_WIDTH,			// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_HD_4_3_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_HD_4_3_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_HD_4_3_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_HD_4_3_YCC422_U8_A,	// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.afnCacheSelect = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,	// AFN cache select.
		.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_8BITS,			// PIXFMTTBL.PDEPTH[2:0] <br><br> Depth of pixel.
		.rotation = ImIipStruct_E_IM_IIP_UTIL_ROTATE_000,		// Angle of rotation
		.resizeMode = ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR,// Resize mode
	};
	kuchar paramBuffer[ImIipDefine_D_IM_IIP_UTIL_RR_BUF_BYTES];
	kulong paramBufferAddr = CtImIip_ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align

	CtImIipUtility_DDIM_PRINT((CtImIipUtility_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = IM_IIP_Utility_ResizeRotate(&iipUtilRr0, NULL, priv->paramMasterIf,
										paramBufferAddr, priv->waitTime);
	CtImIipUtility_DDIM_PRINT((CtImIipUtility_D_IM_IIP_FUNC_NAME "result = 0x%x.\n", priv->ercd));

	return D_DDIM_OK;
}


// Im_IIP_Utility_ResizeRotate 14-1-4
#undef CtImIipUtility_D_IM_IIP_FUNC_NAME
#define CtImIipUtility_D_IM_IIP_FUNC_NAME "ct_im_iip_utility_14_1_4: "
kint32 ct_im_iip_utility_14_1_4(CtImIipUtility *self)
{
	CtImIipUtilityPrivate *priv = CT_IM_IIP_UTILITY_GET_PRIVATE(self);

	TImIipUtilRr iipUtilRr0 = {
		.afnUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_AFN1,		// UNITID of AFN
		.slUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL3,			// UNITID of SL
		.srcPixid = ImIipStruct_E_IM_IIP_PIXID_1,				// Source image PIXID
		.dstPixid = ImIipStruct_E_IM_IIP_PIXID_2,				// Destination image PIXID
		.src = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> ... (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> ... (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> ... (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> ... (offset +3).
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,
				// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_LINES,
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG    = CtImIip_D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH,
					.cbB   = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.crR   = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH,			// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_A,	// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.dst = {								// Destination image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> ... (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> ... (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> ... (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> ... (offset +3).
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,			
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,
				// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_LINES,
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH,			// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG    = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_Y,
					.cbB   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_C,
					.crR   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_A,	// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.afnCacheSelect = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,	// AFN cache select.
		.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_16BITS,		// PIXFMTTBL.PDEPTH[2:0] <br><br> Depth of pixel.
		.rotation = ImIipStruct_E_IM_IIP_UTIL_ROTATE_000,		// Angle of rotation
		.resizeMode = ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR,// Resize mode
	};
	kuchar paramBuffer[ImIipDefine_D_IM_IIP_UTIL_RR_BUF_BYTES];
	kulong paramBufferAddr = CtImIip_ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align

	CtImIipUtility_DDIM_PRINT((CtImIipUtility_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = IM_IIP_Utility_ResizeRotate(&iipUtilRr0, NULL, priv->paramMasterIf,
										paramBufferAddr, priv->waitTime);
	CtImIipUtility_DDIM_PRINT((CtImIipUtility_D_IM_IIP_FUNC_NAME "result = 0x%x.\n", priv->ercd));

	return D_DDIM_OK;
}


// Im_IIP_Utility_ResizeRotate 14-1-5
#undef CtImIipUtility_D_IM_IIP_FUNC_NAME
#define CtImIipUtility_D_IM_IIP_FUNC_NAME "ct_im_iip_utility_14_1_5: "
kint32 ct_im_iip_utility_14_1_5(CtImIipUtility *self)
{
	CtImIipUtilityPrivate *priv = CT_IM_IIP_UTILITY_GET_PRIVATE(self);

	TImIipUtilRr iipUtilRr0 = {
		.afnUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_AFN1,		// UNITID of AFN
		.slUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL3,			// UNITID of SL
		.srcPixid = ImIipStruct_E_IM_IIP_PIXID_1,				// Source image PIXID
		.dstPixid = ImIipStruct_E_IM_IIP_PIXID_2,				// Destination image PIXID
		.src = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH /2,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_CHUNKY,		// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_CBCR,		// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[1:0] <br><br> ... (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[3:2] <br><br> ... (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,	// dummy
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,	// dummy
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_WIDTH /2,
				//PIXFMTTBL.PICHSZ[14:0]<br><br>The number of horizontal pixel.[16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_LINES,   
				// PIXFMTTBL.PICVSZ[13:0]<br><br>The number of vertical pixel. [2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG   = 0,						// dummy
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH *2,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH *2,
					.Alpha = 0,						// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = (kulong)NULL,			// dummy
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.Alpha = (kulong)NULL,			// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.dst = {								// Destination image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH /4,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES /2,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,	// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_CHUNKY,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_CBCR,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[1:0] <br><br> ... (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[3:2] <br><br> ... (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,	// dummy
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,	// dummy
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,
				// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_WIDTH /4,
				// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel. [16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_LINES /2,
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.lineBytes = {								// The size of byte of Global image 1 line.
					.yG   = 0,						// dummy
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH *2,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH *2,
					.Alpha = 0,						// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = (kulong)NULL,			// dummy
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C,
					.Alpha = (kulong)NULL,			// dummy
				},
				.masterifYG = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterifCbB = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterifCrR = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterifAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.afnCacheSelect = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,	// AFN cache select.
		.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_8BITS,			// PIXFMTTBL.PDEPTH[2:0] <br><br> Depth of pixel.
		.rotation = ImIipStruct_E_IM_IIP_UTIL_ROTATE_000,		// Angle of rotation
		.resizeMode = ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR,// Resize mode
	};
	kuchar paramBuffer[ImIipDefine_D_IM_IIP_UTIL_RR_BUF_BYTES];
	kulong paramBufferAddr = CtImIip_ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align

	CtImIipUtility_DDIM_PRINT((CtImIipUtility_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = IM_IIP_Utility_ResizeRotate(&iipUtilRr0, NULL, priv->paramMasterIf, 
										paramBufferAddr, priv->waitTime);
	CtImIipUtility_DDIM_PRINT((CtImIipUtility_D_IM_IIP_FUNC_NAME "result = 0x%x.\n", priv->ercd));

	return D_DDIM_OK;
}


// Im_IIP_Utility_ResizeRotate 14-1-X
kint32 ct_im_iip_utility_run_14_1(CtImIipUtility *self, const kuint32 ctNo3rd)
{
	CtImIipUtilityPrivate *priv = CT_IM_IIP_UTILITY_GET_PRIVATE(self);

	switch(ctNo3rd) {
		// Test-14-1-1
		case 1:
			return ct_im_iip_utility_14_1_1(priv->ciIipUtility);

		// Test-14-1-2
		case 2:
			return ct_im_iip_utility_14_1_2(priv->ciIipUtility);

		// Test-14-1-3
		case 3:
			return ct_im_iip_utility_14_1_3(priv->ciIipUtility);

		// Test-14-1-4
		case 4:
			return ct_im_iip_utility_14_1_4(priv->ciIipUtility);

		// Test-14-1-5
		case 5:
			return ct_im_iip_utility_14_1_5(priv->ciIipUtility);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

#endif //CO_CT_IM_IIP_DISABLE

CtImIipUtility *ct_im_iip_utility_new(void)
{
    CtImIipUtility *self = k_object_new_with_private(CT_TYPE_IM_IIP_UTILITY, sizeof(CtImIipUtilityPrivate));
    return self;
}