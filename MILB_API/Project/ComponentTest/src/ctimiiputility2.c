/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipUtility2类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
#include "ctimiip.h"

// im_iip header
#include "imiipdefine.h"
#include "imiipstruct.h"
#include "imiipparamenum.h"
#include "ctimiiputility2.h"
#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#include <stdio.h>
#endif
#endif //CO_CT_IM_IIP_DISABLE

K_TYPE_DEFINE_WITH_PRIVATE(CtImIipUtility2, ct_im_iip_utility2);
#define CT_IM_IIP_UTILITY2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImIipUtility2Private,CT_TYPE_IM_IIP_UTILITY2))

struct _CtImIipUtility2Private {
    CtImIipUtility2 *	ciIipUtility2;
	kint32				ercd;
	kuchar 				paramMasterIf;
	kint32 				waitTime;
};

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#undef Ddim_Print
#define CtImIipUtility2_DDIM_PRINT(arg)		{DDIM_User_Printf arg;}		/**< printf function inside DDIM */
#endif

static void ct_im_iip_utility2_constructor(CtImIipUtility2 *self) 
{
	CtImIipUtility2Private *priv = CT_IM_IIP_UTILITY2_GET_PRIVATE(self);
	priv->ciIipUtility2 = ct_im_iip_utility2_new();
	priv->paramMasterIf = ImIipDefine_D_IM_IIP_MASTER_IF0;
	priv->waitTime = 30;
}

static void ct_im_iip_utility2_destructor(CtImIipUtility2 *self)
{
	CtImIipUtility2Private *priv = CT_IM_IIP_UTILITY2_GET_PRIVATE(self);
	if(priv->ciIipUtility2){
		k_object_unref(priv->ciIipUtility2);
	}
	priv->ciIipUtility2 = NULL;
}
/*
 *PUBLIC
 */
// IM_IIP_Utility_AlphaBlend 14-4-1
#undef D_IM_IIP_FUNC_NAME
#define CtImIipUtility2_D_IM_IIP_FUNC_NAME "ct_im_iip_utility2_14_4_1: "
kint32 ct_im_iip_utility2_14_4_1(CtImIipUtility2 *self)
{
	CtImIipUtility2Private *priv = CT_IM_IIP_UTILITY2_GET_PRIVATE(self);
	TImIipUtilAlphablend iipUtilBlend = {
		.ldUnitid[0] = ImIipStruct_E_IM_IIP_UNIT_ID_LD0,
		.ldUnitid[1] = ImIipStruct_E_IM_IIP_UNIT_ID_LD1,
		.blendUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_BLEND0,
		.slUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL3,
		.srcPixid[0] = ImIipStruct_E_IM_IIP_PIXID_0,
		.srcPixid[1] = ImIipStruct_E_IM_IIP_PIXID_1,
		.dstPixid = ImIipStruct_E_IM_IIP_PIXID_2,
		.src[0] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE,				
				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,
					// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,
					// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,
					// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,
					// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
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
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.lineyBtes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A,
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
		.src[1] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,				
				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,
					// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,
					// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,
					// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,
					// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
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
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.lineyBtes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_A,
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
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE,				
				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,
					// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,
					// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,
					// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,
					// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
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
				.lineyBtes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A,
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
		.ldCacheSelect[0] = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,
		.ldCacheSelect[1] = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,
		.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_8BITS,
		.alphaDepth = ImIipStruct_E_IM_IIP_ADEPTH_8BITS,
		.alphaSubsampling = ImIipDefine_D_IM_IIP_ALPHA_NO_SUBSAMP,
		.alpha = {
			.step = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_STEP_8BITS,
			.sel = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA,
			.out = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA,
			.alphaVal[0] = 0,
			.alphaVal[1] = 0,
			.alphaVal[2] = 0,
			.alphaVal[3] = 0,
		},
	};
	kuchar paramBuffer[ImIipDefine_D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES];
	kulong paramBufferAddr = CtImIip_ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align
	
#if 0
//	iipUtilBlend.src[0].gbl.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.src[1].gbl.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.dst.gbl.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
//	iipUtilBlend.alpha.sel = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL;
	iipUtilBlend.alpha.sel = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA;
//	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_FIXED_VAL;
//	iipUtilBlend.alpha.out = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA;
	iipUtilBlend.alpha.out = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_NONE;
#endif

	CtImIipUtility2_DDIM_PRINT((CtImIipUtility2_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = IM_IIP_Utility_AlphaBlend(&iipUtilBlend, priv->paramMasterIf,
										paramBufferAddr, priv->waitTime);
	CtImIipUtility2_DDIM_PRINT((CtImIipUtility2_D_IM_IIP_FUNC_NAME "result = 0x%x.\n", priv->ercd));

	return D_DDIM_OK;
}


// IM_IIP_Utility_AlphaBlend 14-4-2
#undef CtImIipUtility2_D_IM_IIP_FUNC_NAME
#define CtImIipUtility2_D_IM_IIP_FUNC_NAME "ct_im_iip_utility2_14_4_2: "
kint32 ct_im_iip_utility2_14_4_2(CtImIipUtility2 *self)
{
	CtImIipUtility2Private *priv = CT_IM_IIP_UTILITY2_GET_PRIVATE(self);
	TImIipUtilAlphablend iipUtilBlend = {
		.ldUnitid[0] = ImIipStruct_E_IM_IIP_UNIT_ID_LD0,
		.ldUnitid[1] = ImIipStruct_E_IM_IIP_UNIT_ID_LD1,
		.blendUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_BLEND0,
		.slUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL3,
		.srcPixid[0] = ImIipStruct_E_IM_IIP_PIXID_0,
		.srcPixid[1] = ImIipStruct_E_IM_IIP_PIXID_1,
		.dstPixid = ImIipStruct_E_IM_IIP_PIXID_2,
		.src[0] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE,				
				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_CHUNKY,		// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC444,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
				},
				.signYG = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.signCbB = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.signCrR = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.signD3 = ImIipDefine_D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = CtImIip_D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.lineyBtes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_RGBA8888_GLOBAL_WIDTH,
					.cbB  = 0,		// dummy
					.crR  = 0,		// dummy
					.Alpha = 0,		// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_RGBA8888,
					.cbB  = 0,		// dummy
					.crR  = 0,		// dummy
					.Alpha = 0,		// dummy
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
		.src[1] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE,				
				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_CHUNKY,		// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC444,		// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,
					// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,
					// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,
					// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,
					// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
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
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.lineyBtes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_RGBA8888_GLOBAL_WIDTH,
					.cbB  = 0,		// dummy
					.crR  = 0,		// dummy
					.Alpha = 0,		// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_RGBA8888,
					.cbB  = 0,		// dummy
					.crR  = 0,		// dummy
					.Alpha = 0,		// dummy
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
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE,				
				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_CHUNKY,		// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC444,		// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,
					// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,
					// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,
					// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,
					// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
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
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.lineyBtes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_RGBA8888_GLOBAL_WIDTH,
					.cbB  = 0,		// dummy
					.crR  = 0,		// dummy
					.Alpha = 0,		// dummy
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_RGBA8888,
					.cbB  = 0,		// dummy
					.crR  = 0,		// dummy
					.Alpha = 0,		// dummy
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
		.ldCacheSelect[0] = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,
		.ldCacheSelect[1] = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,
		.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_8BITS,
		.alphaDepth = ImIipStruct_E_IM_IIP_ADEPTH_8BITS,
		.alphaSubsampling = ImIipDefine_D_IM_IIP_ALPHA_NO_SUBSAMP,
		.alpha = {
			.step = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_STEP_8BITS,
			.sel = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL,
			.out = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_P1_ALPHA,
			.alphaVal[0] = 0,
			.alphaVal[1] = 0,
			.alphaVal[2] = 0,
			.alphaVal[3] = 0,
		},
	};
	kuchar paramBuffer[ImIipDefine_D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES];
	kulong paramBufferAddr = CtImIip_ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align

#if 0
//	iipUtilBlend.src[0].gbl.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.src[1].gbl.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.dst.gbl.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
//	iipUtilBlend.alpha.sel = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL;
	iipUtilBlend.alpha.sel = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA;
//	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_FIXED_VAL;
//	iipUtilBlend.alpha.out = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA;
	iipUtilBlend.alpha.out = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_NONE;
#endif

	CtImIipUtility2_DDIM_PRINT((CtImIipUtility2_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = IM_IIP_Utility_AlphaBlend(&iipUtilBlend, priv->paramMasterIf,
										paramBufferAddr, priv->waitTime);
	CtImIipUtility2_DDIM_PRINT((CtImIipUtility2_D_IM_IIP_FUNC_NAME "result = 0x%x.\n", priv->ercd));

	return D_DDIM_OK;
}


// IM_IIP_Utility_AlphaBlend 14-4-3
#undef CtImIipUtility2_D_IM_IIP_FUNC_NAME
#define CtImIipUtility2_D_IM_IIP_FUNC_NAME "ct_im_iip_utility2_14_4_3: "
kint32 ct_im_iip_utility2_14_4_3(CtImIipUtility2 *self)
{
	CtImIipUtility2Private *priv = CT_IM_IIP_UTILITY2_GET_PRIVATE(self);
	TImIipUtilAlphablend iipUtilBlend = {
		.ldUnitid[0] = ImIipStruct_E_IM_IIP_UNIT_ID_LD0,
		.ldUnitid[1] = ImIipStruct_E_IM_IIP_UNIT_ID_LD1,
		.blendUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_BLEND0,
		.slUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL3,
		.srcPixid[0] = ImIipStruct_E_IM_IIP_PIXID_0,
		.srcPixid[1] = ImIipStruct_E_IM_IIP_PIXID_1,
		.dstPixid = ImIipStruct_E_IM_IIP_PIXID_2,
		.src[0] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,				
				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_PLANE,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC444,	// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,
					// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,
					// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,
					// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,
					// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
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
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.lineyBtes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC444_U16_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC444_U16_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC444_U16_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC444_U16_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC444_U16_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC444_U16_CB,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC444_U16_CR,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC444_U16_A,
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
		.src[1] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,				
				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_PLANE,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC444,	// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,
					// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,
					// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,
					// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,
					// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
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
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.lineyBtes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC444_U16_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC444_U16_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC444_U16_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC444_U16_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC444_U16_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC444_U16_CB,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC444_U16_CR,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC444_U16_A,
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
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,				
				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_PLANE,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC444,	// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,
					// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,
					// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,
					// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,
					// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
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
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.lineyBtes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC444_U16_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC444_U16_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC444_U16_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC444_U16_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC444_U16_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC444_U16_CB,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC444_U16_CR,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC444_U16_A,
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
		.ldCacheSelect[0] = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,
		.ldCacheSelect[1] = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,
		.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_16BITS,
		.alphaDepth = ImIipStruct_E_IM_IIP_ADEPTH_8BITS,
		.alphaSubsampling = ImIipDefine_D_IM_IIP_ALPHA_NO_SUBSAMP,
		.alpha = {
			.step = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_STEP_8BITS,
			.sel = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL,
			.out = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_NONE,
			.alphaVal[0] = 127,
			.alphaVal[1] = 127,
			.alphaVal[2] = 127,
			.alphaVal[3] = 127,
		},
	};
	kuchar paramBuffer[ImIipDefine_D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES];
	kulong paramBufferAddr = CtImIip_ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align

#if 0
	iipUtilBlend.src[0].gbl.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.src[1].gbl.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.dst.gbl.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.alpha.sel = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL;
//	iipUtilBlend.alpha.sel = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA;
//	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_FIXED_VAL;
//	iipUtilBlend.alpha.out = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA;
	iipUtilBlend.alpha.out = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_NONE;
#endif

	CtImIipUtility2_DDIM_PRINT((CtImIipUtility2_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = IM_IIP_Utility_AlphaBlend(&iipUtilBlend, priv->paramMasterIf,
										paramBufferAddr, priv->waitTime);
	CtImIipUtility2_DDIM_PRINT((CtImIipUtility2_D_IM_IIP_FUNC_NAME "result = 0x%x.\n", priv->ercd));

	return D_DDIM_OK;
}


// IM_IIP_Utility_AlphaBlend 14-4-4
#undef CtImIipUtility2_D_IM_IIP_FUNC_NAME
#define CtImIipUtility2_D_IM_IIP_FUNC_NAME "ct_im_iip_utility2_14_4_4: "
kint32 ct_im_iip_utility2_14_4_4(CtImIipUtility2 *self)
{
	CtImIipUtility2Private *priv = CT_IM_IIP_UTILITY2_GET_PRIVATE(self);
	TImIipUtilAlphablend iipUtilBlend = {
		.ldUnitid[0] = ImIipStruct_E_IM_IIP_UNIT_ID_LD0,
		.ldUnitid[1] = ImIipStruct_E_IM_IIP_UNIT_ID_LD1,
		.blendUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_BLEND0,
		.slUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL3,
		.srcPixid[0] = ImIipStruct_E_IM_IIP_PIXID_0,
		.srcPixid[1] = ImIipStruct_E_IM_IIP_PIXID_1,
		.dstPixid = ImIipStruct_E_IM_IIP_PIXID_2,
		.src[0] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE,				
				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,
					// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,
					// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,
					// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,
					// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
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
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.lineyBtes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_A,
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
		.src[1] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = CtImIip_D_IM_IIP_VGA_WIDTH,			// Width
				.lines = CtImIip_D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE,				
				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,
					// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,
					// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,
					// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,
					// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
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
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.lineyBtes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U16_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U16_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U16_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U16_A,
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
				.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE,				
				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frameType = ImIipStruct_E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pixFormat = ImIipStruct_E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunkyColor = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G,
					// PIXFMTTBL.CHKYORDR[1:0] <br><br> Chunky component (offset +0).
					.component1 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B,
					// PIXFMTTBL.CHKYORDR[3:2] <br><br> Chunky component (offset +1).
					.component2 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R,
					// PIXFMTTBL.CHKYORDR[5:4] <br><br> Chunky component (offset +2).
					.component3 = ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A,
					// PIXFMTTBL.CHKYORDR[7:6] <br><br> Chunky component (offset +3).
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
				// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.lineyBtes = {								// The size of byte of Global image 1 line.
					.yG   = CtImIip_D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH,
					.cbB  = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.crR  = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.yG   = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_Y,
					.cbB  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_C,
					.crR  = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_C,
					.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_A,
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
		.ldCacheSelect[0] = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,
		.ldCacheSelect[1] = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_0,
		.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_16BITS,
		.alphaDepth = ImIipStruct_E_IM_IIP_ADEPTH_8BITS,
		.alphaSubsampling = ImIipDefine_D_IM_IIP_ALPHA_NO_SUBSAMP,
		.alpha = {
			.step = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_STEP_8BITS,
			.sel = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA,
			.out = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA,
			.alphaVal[0] = 0,
			.alphaVal[1] = 0,
			.alphaVal[2] = 0,
			.alphaVal[3] = 0,
		},
	};
	kuchar paramBuffer[ImIipDefine_D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES];
	kulong paramBufferAddr = CtImIip_ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align

#if 0
	iipUtilBlend.src[0].gbl.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.src[1].gbl.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.dst.gbl.alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.alpha.sel = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL;
//	iipUtilBlend.alpha.sel = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA;
//	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_FIXED_VAL;
//	iipUtilBlend.alpha.out = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA;
	iipUtilBlend.alpha.out = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_NONE;
#endif

	CtImIipUtility2_DDIM_PRINT((CtImIipUtility2_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = IM_IIP_Utility_AlphaBlend(&iipUtilBlend, priv->paramMasterIf,
										paramBufferAddr, priv->waitTime);
	CtImIipUtility2_DDIM_PRINT((CtImIipUtility2_D_IM_IIP_FUNC_NAME "result = 0x%x.\n", priv->ercd));

	return D_DDIM_OK;
}


// IM_IIP_Utility_AlphaBlend 14-4-X
kint32 ct_im_iip_utility2_run_14_4(CtImIipUtility2 *self, const kuint32 ctNo3rd)
{
	CtImIipUtility2Private *priv = CT_IM_IIP_UTILITY2_GET_PRIVATE(self);
	switch(ctNo3rd) {
		// Test-14-4-1
		case 1:
			return ct_im_iip_utility2_14_4_1(priv->ciIipUtility2);

		// Test-14-4-2
		case 2:
			return ct_im_iip_utility2_14_4_2(priv->ciIipUtility2);

		// Test-14-4-3
		case 3:
			return ct_im_iip_utility2_14_4_3(priv->ciIipUtility2);

		// Test-14-4-4
		case 4:
			return ct_im_iip_utility2_14_4_4(priv->ciIipUtility2);

		default:
			CtImIipUtility2_DDIM_PRINT(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

#endif //CO_CT_IM_IIP_DISABLE

CtImIipUtility2 *ct_im_iip_utility2_new(void)
{
    CtImIipUtility2 *self = k_object_new_with_private(CT_TYPE_IM_IIP_UTILITY2, sizeof(CtImIipUtility2Private));
    return self;
}
