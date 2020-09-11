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
#include "ct_im_iip_utility.h"
#include "ct_im_iip.h"

// im_iip header
#include "im_iip.h"
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
	priv->paramMasterIf = D_IM_IIP_MASTER_IF0;
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

/*PUBLIC*/

// IM_IIP_Utility_AlphaBlend 14-4-1
#undef D_IM_IIP_FUNC_NAME
#define CtImIipUtility2_D_IM_IIP_FUNC_NAME "ct_im_iip_utility2_14_4_1: "
kint32 ct_im_iip_utility2_14_4_1(CtImIipUtility2 *self)
{
	CtImIipUtility2Private *priv = CT_IM_IIP_UTILITY2_GET_PRIVATE(self);
	T_IM_IIP_UTIL_ALPHABLEND iipUtilBlend = {
		.ld_unitid[0] = E_IM_IIP_UNIT_ID_LD0,
		.ld_unitid[1] = E_IM_IIP_UNIT_ID_LD1,
		.blend_unitid = E_IM_IIP_UNIT_ID_BLEND0,
		.sl_unitid = E_IM_IIP_UNIT_ID_SL3,
		.src_pixid[0] = E_IM_IIP_PIXID_0,
		.src_pixid[1] = E_IM_IIP_PIXID_1,
		.dst_pixid = E_IM_IIP_PIXID_2,
		.src[0] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = D_IM_IIP_VGA_WIDTH,			// Width
				.lines = D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = D_IM_IIP_ALPHA_TRUE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> Chunky component (offset +0).
					.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> Chunky component (offset +1).
					.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> Chunky component (offset +2).
					.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> Chunky component (offset +3).
				},
				.sign_Y_G = D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.sign_D3 = D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.line_bytes = {								// The size of byte of Global image 1 line.
					.Y_G   = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.Cb_B  = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Cr_R  = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.Y_G   = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y,
					.Cb_B  = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.Cr_R  = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C,
					.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A,
				},
				.masterIF_Y_G = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterIF_Alpha = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.src[1] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = D_IM_IIP_VGA_WIDTH,			// Width
				.lines = D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> Chunky component (offset +0).
					.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> Chunky component (offset +1).
					.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> Chunky component (offset +2).
					.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> Chunky component (offset +3).
				},
				.sign_Y_G = D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.sign_D3 = D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.line_bytes = {								// The size of byte of Global image 1 line.
					.Y_G   = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.Cb_B  = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Cr_R  = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.Y_G   = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_Y,
					.Cb_B  = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_C,
					.Cr_R  = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_C,
					.Alpha = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_A,
				},
				.masterIF_Y_G = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterIF_Alpha = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.dst = {								// Destination image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = D_IM_IIP_VGA_WIDTH,			// Width
				.lines = D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = D_IM_IIP_ALPHA_TRUE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> Chunky component (offset +0).
					.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> Chunky component (offset +1).
					.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> Chunky component (offset +2).
					.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> Chunky component (offset +3).
				},
				.sign_Y_G = D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.sign_D3 = D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.line_bytes = {								// The size of byte of Global image 1 line.
					.Y_G   = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH,
					.Cb_B  = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Cr_R  = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH,
					.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.Y_G   = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y,
					.Cb_B  = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C,
					.Cr_R  = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C,
					.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A,
				},
				.masterIF_Y_G = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterIF_Cb_B = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterIF_Cr_R = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterIF_Alpha = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.ld_cache_select[0] = E_IM_IIP_PARAM_CSEL_0,
		.ld_cache_select[1] = E_IM_IIP_PARAM_CSEL_0,
		.pix_depth = D_IM_IIP_PDEPTH_8BITS,
		.alpha_depth = E_IM_IIP_ADEPTH_8BITS,
		.alpha_subsampling = D_IM_IIP_ALPHA_NO_SUBSAMP,
		.alpha = {
			.step = E_IM_IIP_PARAM_ALPHA_STEP_8BITS,
			.sel = E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA,
			.out = E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA,
			.ALPHA_VAL[0] = 0,
			.ALPHA_VAL[1] = 0,
			.ALPHA_VAL[2] = 0,
			.ALPHA_VAL[3] = 0,
		},
	};
	kuchar paramBuffer[D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES];
	kulong paramBufferAddr = ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align
	
#if 0
//	iipUtilBlend.src[0].gbl.alpha = D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.src[1].gbl.alpha = D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.dst.gbl.alpha = D_IM_IIP_ALPHA_FALSE;
//	iipUtilBlend.alpha.sel = E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL;
	iipUtilBlend.alpha.sel = E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA;
//	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_FIXED_VAL;
//	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA;
	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_NONE;
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
	T_IM_IIP_UTIL_ALPHABLEND iipUtilBlend = {
		.ld_unitid[0] = E_IM_IIP_UNIT_ID_LD0,
		.ld_unitid[1] = E_IM_IIP_UNIT_ID_LD1,
		.blend_unitid = E_IM_IIP_UNIT_ID_BLEND0,
		.sl_unitid = E_IM_IIP_UNIT_ID_SL3,
		.src_pixid[0] = E_IM_IIP_PIXID_0,
		.src_pixid[1] = E_IM_IIP_PIXID_1,
		.dst_pixid = E_IM_IIP_PIXID_2,
		.src[0] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = D_IM_IIP_VGA_WIDTH,			// Width
				.lines = D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = D_IM_IIP_ALPHA_TRUE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frame_type = E_IM_IIP_FTYPE_CHUNKY,		// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pix_format = E_IM_IIP_PFMT_YCC444,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> Chunky component (offset +0).
					.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> Chunky component (offset +1).
					.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> Chunky component (offset +2).
					.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> Chunky component (offset +3).
				},
				.sign_Y_G = D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.sign_D3 = D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel. [2~16383]
				.line_bytes = {								// The size of byte of Global image 1 line.
					.Y_G   = D_IM_IIP_VGA_RGBA8888_GLOBAL_WIDTH,
					.Cb_B  = 0,		// dummy
					.Cr_R  = 0,		// dummy
					.Alpha = 0,		// dummy
				},
				.addr = {									// Beginning address of Global image.
					.Y_G   = D_IM_IIP_IMG_MEM_ADDR_0_RGBA8888,
					.Cb_B  = 0,		// dummy
					.Cr_R  = 0,		// dummy
					.Alpha = 0,		// dummy
				},
				.masterIF_Y_G = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterIF_Alpha = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.src[1] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = D_IM_IIP_VGA_WIDTH,			// Width
				.lines = D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = D_IM_IIP_ALPHA_TRUE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frame_type = E_IM_IIP_FTYPE_CHUNKY,		// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pix_format = E_IM_IIP_PFMT_YCC444,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> Chunky component (offset +0).
					.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> Chunky component (offset +1).
					.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> Chunky component (offset +2).
					.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> Chunky component (offset +3).
				},
				.sign_Y_G = D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.sign_D3 = D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.line_bytes = {								// The size of byte of Global image 1 line.
					.Y_G   = D_IM_IIP_VGA_RGBA8888_GLOBAL_WIDTH,
					.Cb_B  = 0,		// dummy
					.Cr_R  = 0,		// dummy
					.Alpha = 0,		// dummy
				},
				.addr = {									// Beginning address of Global image.
					.Y_G   = D_IM_IIP_IMG_MEM_ADDR_4_RGBA8888,
					.Cb_B  = 0,		// dummy
					.Cr_R  = 0,		// dummy
					.Alpha = 0,		// dummy
				},
				.masterIF_Y_G = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterIF_Alpha = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.dst = {								// Destination image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = D_IM_IIP_VGA_WIDTH,			// Width
				.lines = D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = D_IM_IIP_ALPHA_TRUE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frame_type = E_IM_IIP_FTYPE_CHUNKY,		// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pix_format = E_IM_IIP_PFMT_YCC444,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> Chunky component (offset +0).
					.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> Chunky component (offset +1).
					.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> Chunky component (offset +2).
					.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> Chunky component (offset +3).
				},
				.sign_Y_G = D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.sign_D3 = D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.line_bytes = {								// The size of byte of Global image 1 line.
					.Y_G   = D_IM_IIP_VGA_RGBA8888_GLOBAL_WIDTH,
					.Cb_B  = 0,		// dummy
					.Cr_R  = 0,		// dummy
					.Alpha = 0,		// dummy
				},
				.addr = {									// Beginning address of Global image.
					.Y_G   = D_IM_IIP_IMG_MEM_ADDR_1_RGBA8888,
					.Cb_B  = 0,		// dummy
					.Cr_R  = 0,		// dummy
					.Alpha = 0,		// dummy
				},
				.masterIF_Y_G = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterIF_Cb_B = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterIF_Cr_R = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterIF_Alpha = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.ld_cache_select[0] = E_IM_IIP_PARAM_CSEL_0,
		.ld_cache_select[1] = E_IM_IIP_PARAM_CSEL_0,
		.pix_depth = D_IM_IIP_PDEPTH_8BITS,
		.alpha_depth = E_IM_IIP_ADEPTH_8BITS,
		.alpha_subsampling = D_IM_IIP_ALPHA_NO_SUBSAMP,
		.alpha = {
			.step = E_IM_IIP_PARAM_ALPHA_STEP_8BITS,
			.sel = E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL,
			.out = E_IM_IIP_PARAM_ALPHA_OUT_P1_ALPHA,
			.ALPHA_VAL[0] = 0,
			.ALPHA_VAL[1] = 0,
			.ALPHA_VAL[2] = 0,
			.ALPHA_VAL[3] = 0,
		},
	};
	kuchar paramBuffer[D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES];
	kulong paramBufferAddr = ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align

#if 0
//	iipUtilBlend.src[0].gbl.alpha = D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.src[1].gbl.alpha = D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.dst.gbl.alpha = D_IM_IIP_ALPHA_FALSE;
//	iipUtilBlend.alpha.sel = E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL;
	iipUtilBlend.alpha.sel = E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA;
//	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_FIXED_VAL;
//	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA;
	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_NONE;
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
	T_IM_IIP_UTIL_ALPHABLEND iipUtilBlend = {
		.ld_unitid[0] = E_IM_IIP_UNIT_ID_LD0,
		.ld_unitid[1] = E_IM_IIP_UNIT_ID_LD1,
		.blend_unitid = E_IM_IIP_UNIT_ID_BLEND0,
		.sl_unitid = E_IM_IIP_UNIT_ID_SL3,
		.src_pixid[0] = E_IM_IIP_PIXID_0,
		.src_pixid[1] = E_IM_IIP_PIXID_1,
		.dst_pixid = E_IM_IIP_PIXID_2,
		.src[0] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = D_IM_IIP_VGA_WIDTH,			// Width
				.lines = D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frame_type = E_IM_IIP_FTYPE_PLANE,			// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pix_format = E_IM_IIP_PFMT_YCC444,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> Chunky component (offset +0).
					.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> Chunky component (offset +1).
					.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> Chunky component (offset +2).
					.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> Chunky component (offset +3).
				},
				.sign_Y_G = D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.sign_D3 = D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.line_bytes = {								// The size of byte of Global image 1 line.
					.Y_G   = D_IM_IIP_VGA_YCC444_U16_Y_GLOBAL_WIDTH,
					.Cb_B  = D_IM_IIP_VGA_YCC444_U16_C_GLOBAL_WIDTH,
					.Cr_R  = D_IM_IIP_VGA_YCC444_U16_C_GLOBAL_WIDTH,
					.Alpha = D_IM_IIP_VGA_YCC444_U16_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.Y_G   = D_IM_IIP_IMG_MEM_ADDR_0_YCC444_U16_Y,
					.Cb_B  = D_IM_IIP_IMG_MEM_ADDR_0_YCC444_U16_CB,
					.Cr_R  = D_IM_IIP_IMG_MEM_ADDR_0_YCC444_U16_CR,
					.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC444_U16_A,
				},
				.masterIF_Y_G = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterIF_Alpha = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.src[1] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = D_IM_IIP_VGA_WIDTH,			// Width
				.lines = D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frame_type = E_IM_IIP_FTYPE_PLANE,			// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pix_format = E_IM_IIP_PFMT_YCC444,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> Chunky component (offset +0).
					.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> Chunky component (offset +1).
					.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> Chunky component (offset +2).
					.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> Chunky component (offset +3).
				},
				.sign_Y_G = D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.sign_D3 = D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.line_bytes = {								// The size of byte of Global image 1 line.
					.Y_G   = D_IM_IIP_VGA_YCC444_U16_Y_GLOBAL_WIDTH,
					.Cb_B  = D_IM_IIP_VGA_YCC444_U16_C_GLOBAL_WIDTH,
					.Cr_R  = D_IM_IIP_VGA_YCC444_U16_C_GLOBAL_WIDTH,
					.Alpha = D_IM_IIP_VGA_YCC444_U16_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.Y_G   = D_IM_IIP_IMG_MEM_ADDR_4_YCC444_U16_Y,
					.Cb_B  = D_IM_IIP_IMG_MEM_ADDR_4_YCC444_U16_CB,
					.Cr_R  = D_IM_IIP_IMG_MEM_ADDR_4_YCC444_U16_CR,
					.Alpha = D_IM_IIP_IMG_MEM_ADDR_4_YCC444_U16_A,
				},
				.masterIF_Y_G = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterIF_Alpha = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.dst = {								// Destination image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = D_IM_IIP_VGA_WIDTH,			// Width
				.lines = D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frame_type = E_IM_IIP_FTYPE_PLANE,			// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pix_format = E_IM_IIP_PFMT_YCC444,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> Chunky component (offset +0).
					.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> Chunky component (offset +1).
					.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> Chunky component (offset +2).
					.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> Chunky component (offset +3).
				},
				.sign_Y_G = D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.sign_D3 = D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.line_bytes = {								// The size of byte of Global image 1 line.
					.Y_G   = D_IM_IIP_VGA_YCC444_U16_Y_GLOBAL_WIDTH,
					.Cb_B  = D_IM_IIP_VGA_YCC444_U16_C_GLOBAL_WIDTH,
					.Cr_R  = D_IM_IIP_VGA_YCC444_U16_C_GLOBAL_WIDTH,
					.Alpha = D_IM_IIP_VGA_YCC444_U16_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.Y_G   = D_IM_IIP_IMG_MEM_ADDR_1_YCC444_U16_Y,
					.Cb_B  = D_IM_IIP_IMG_MEM_ADDR_1_YCC444_U16_CB,
					.Cr_R  = D_IM_IIP_IMG_MEM_ADDR_1_YCC444_U16_CR,
					.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC444_U16_A,
				},
				.masterIF_Y_G = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterIF_Cb_B = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterIF_Cr_R = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterIF_Alpha = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.ld_cache_select[0] = E_IM_IIP_PARAM_CSEL_0,
		.ld_cache_select[1] = E_IM_IIP_PARAM_CSEL_0,
		.pix_depth = D_IM_IIP_PDEPTH_16BITS,
		.alpha_depth = E_IM_IIP_ADEPTH_8BITS,
		.alpha_subsampling = D_IM_IIP_ALPHA_NO_SUBSAMP,
		.alpha = {
			.step = E_IM_IIP_PARAM_ALPHA_STEP_8BITS,
			.sel = E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL,
			.out = E_IM_IIP_PARAM_ALPHA_OUT_NONE,
			.ALPHA_VAL[0] = 127,
			.ALPHA_VAL[1] = 127,
			.ALPHA_VAL[2] = 127,
			.ALPHA_VAL[3] = 127,
		},
	};
	kuchar paramBuffer[D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES];
	kulong paramBufferAddr = ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align

#if 0
	iipUtilBlend.src[0].gbl.alpha = D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.src[1].gbl.alpha = D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.dst.gbl.alpha = D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.alpha.sel = E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL;
//	iipUtilBlend.alpha.sel = E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA;
//	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_FIXED_VAL;
//	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA;
	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_NONE;
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
	T_IM_IIP_UTIL_ALPHABLEND iipUtilBlend = {
		.ld_unitid[0] = E_IM_IIP_UNIT_ID_LD0,
		.ld_unitid[1] = E_IM_IIP_UNIT_ID_LD1,
		.blend_unitid = E_IM_IIP_UNIT_ID_BLEND0,
		.sl_unitid = E_IM_IIP_UNIT_ID_SL3,
		.src_pixid[0] = E_IM_IIP_PIXID_0,
		.src_pixid[1] = E_IM_IIP_PIXID_1,
		.dst_pixid = E_IM_IIP_PIXID_2,
		.src[0] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = D_IM_IIP_VGA_WIDTH,			// Width
				.lines = D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = D_IM_IIP_ALPHA_TRUE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> Chunky component (offset +0).
					.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> Chunky component (offset +1).
					.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> Chunky component (offset +2).
					.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> Chunky component (offset +3).
				},
				.sign_Y_G = D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.sign_D3 = D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.line_bytes = {								// The size of byte of Global image 1 line.
					.Y_G   = D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH,
					.Cb_B  = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.Cr_R  = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.Alpha = D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.Y_G   = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_Y,
					.Cb_B  = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_C,
					.Cr_R  = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_C,
					.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_A,
				},
				.masterIF_Y_G = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterIF_Alpha = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.src[1] = {								// Source image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = D_IM_IIP_VGA_WIDTH,			// Width
				.lines = D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = D_IM_IIP_ALPHA_FALSE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> Chunky component (offset +0).
					.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> Chunky component (offset +1).
					.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> Chunky component (offset +2).
					.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> Chunky component (offset +3).
				},
				.sign_Y_G = D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.sign_D3 = D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.line_bytes = {								// The size of byte of Global image 1 line.
					.Y_G   = D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH,
					.Cb_B  = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.Cr_R  = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.Alpha = D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.Y_G   = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U16_Y,
					.Cb_B  = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U16_C,
					.Cr_R  = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U16_C,
					.Alpha = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U16_A,
				},
				.masterIF_Y_G = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterIF_Cb_B = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterIF_Cr_R = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterIF_Alpha = D_IM_IIP_MASTER_IF0,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.dst = {								// Destination image info.
			.rect = {								// Rectangle info. (Source image area)
				.top = 0.0,								// Vertical position of top-left pixel
				.left = 0.0,							// Horizontal position of top-left pixel
				.width = D_IM_IIP_VGA_WIDTH,			// Width
				.lines = D_IM_IIP_VGA_LINES,			// Lines
			},
			.gbl = {								// Global image info.
				.alpha = D_IM_IIP_ALPHA_TRUE,				// PIXFMTTBL.ALPHA <br><br> Whether image has alpha or not.
				.frame_type = E_IM_IIP_FTYPE_Y_PACKED_CBCR,	// PIXFMTTBL.FTYPE[2:0] <br><br> Frame format.
				.pix_format = E_IM_IIP_PFMT_YCC422,			// PIXFMTTBL.PFMT[3:0] <br><br> Pixel format.
				.chunky_color = {							// PIXFMTTBL.CHKYORDR[7:0] <br><br> Chunky component.
					.component0 = D_IM_IIP_CHUNKY_COLOR_Y0_G,// ...[1:0] <br><br> Chunky component (offset +0).
					.component1 = D_IM_IIP_CHUNKY_COLOR_CB_B,// ...[3:2] <br><br> Chunky component (offset +1).
					.component2 = D_IM_IIP_CHUNKY_COLOR_CR_R,// ...[5:4] <br><br> Chunky component (offset +2).
					.component3 = D_IM_IIP_CHUNKY_COLOR_Y1_A,// ...[7:6] <br><br> Chunky component (offset +3).
				},
				.sign_Y_G = D_IM_IIP_UNSIGNED_DATA,	// PIXFMTTBL.SGYG <br><br> Whether Y(G) image has sign bit or not.
				.sign_Cb_B = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGB <br><br> Whether Cb(B) image has sign bit or not.
				.sign_Cr_R = D_IM_IIP_UNSIGNED_DATA,// PIXFMTTBL.SGR <br><br> Whether Cr(R) image has sign bit or not.
				.sign_D3 = D_IM_IIP_UNSIGNED_DATA,	
				// PIXFMTTBL.SGA <br><br> Whether the fourth color which CSC uses has sign bit or not.
				.width = D_IM_IIP_VGA_WIDTH,// PIXFMTTBL.PICHSZ[14:0]<br><br> The number of horizontal pixel.[16~16383]
				.lines = D_IM_IIP_VGA_LINES,// PIXFMTTBL.PICVSZ[13:0]<br><br> The number of vertical pixel.[2~16383]
				.line_bytes = {								// The size of byte of Global image 1 line.
					.Y_G   = D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH,
					.Cb_B  = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.Cr_R  = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH,
					.Alpha = D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH,
				},
				.addr = {									// Beginning address of Global image.
					.Y_G   = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_Y,
					.Cb_B  = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_C,
					.Cr_R  = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_C,
					.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_A,
				},
				.masterIF_Y_G = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFYG <br><br> Whether the location of Y(G) image is master I/F 0 or 1.
				.masterIF_Cb_B = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFB <br><br> Whether the location of Cb(B) image is master I/F 0 or 1.
				.masterIF_Cr_R = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFR <br><br> Whether the location of Cr(R) image is master I/F 0 or 1.
				.masterIF_Alpha = D_IM_IIP_MASTER_IF1,		
				// PIXFMTTBL.MTIFA <br><br> Whether the location of Alpha image is master I/F 0 or 1.
			},
		},
		.ld_cache_select[0] = E_IM_IIP_PARAM_CSEL_0,
		.ld_cache_select[1] = E_IM_IIP_PARAM_CSEL_0,
		.pix_depth = D_IM_IIP_PDEPTH_16BITS,
		.alpha_depth = E_IM_IIP_ADEPTH_8BITS,
		.alpha_subsampling = D_IM_IIP_ALPHA_NO_SUBSAMP,
		.alpha = {
			.step = E_IM_IIP_PARAM_ALPHA_STEP_8BITS,
			.sel = E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA,
			.out = E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA,
			.ALPHA_VAL[0] = 0,
			.ALPHA_VAL[1] = 0,
			.ALPHA_VAL[2] = 0,
			.ALPHA_VAL[3] = 0,
		},
	};
	kuchar paramBuffer[D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES];
	kulong paramBufferAddr = ct_im_iip_roundup_8((kulong)paramBuffer);	// Convet 8bytes align

#if 0
	iipUtilBlend.src[0].gbl.alpha = D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.src[1].gbl.alpha = D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.dst.gbl.alpha = D_IM_IIP_ALPHA_FALSE;
	iipUtilBlend.alpha.sel = E_IM_IIP_PARAM_ALPHA_SEL_FIXED_VAL;
//	iipUtilBlend.alpha.sel = E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA;
//	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_FIXED_VAL;
//	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA;
	iipUtilBlend.alpha.out = E_IM_IIP_PARAM_ALPHA_OUT_NONE;
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
