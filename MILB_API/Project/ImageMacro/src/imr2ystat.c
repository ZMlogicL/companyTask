/*
 * imr2ystat.c
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
*@author              :gonghaotian
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

#include "imr2ystat.h"
#include "imr2y2.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2yStat, im_r2y_stat);
#define IM_R2Y_STAT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yStatPrivate, IM_TYPE_R2Y_STAT))


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
//#define CO_R2Y_RDMA_ON

/* debug print switch  for im_r2y.c developping/debugging person.
 * (not im_r2y user)
 */
//#define IM_R2Y_DEBUG_PRINT
//#define IM_R2Y_STATUS_PRINT



#define D_IM_R2Y_PACK10_MSB_CYCLE_PIXS	(4)


#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
// Nothing Special

/*----------------------------------------------------------------------*/
/* Structure  															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
struct _ImR2yStatPrivate
{
	int a;
};

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
// Nothing Special
#endif

/*
*DECLS
*/

// YYRA offset information

//
// Access enable register manager
//


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------


/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------


/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------

/*
*IMPL
*/
static void im_r2y_stat_constructor(ImR2yStat *self)
{
	ImR2yStatPrivate *priv = IM_R2Y_STAT_GET_PRIVATE(self);
}

static void im_r2y_stat_destructor(ImR2yStat *self)
{
	ImR2yStatPrivate *priv = IM_R2Y_STAT_GET_PRIVATE(self);
}

#ifdef IM_R2Y_STATUS_PRINT
// Calculate YYW0 output image width
static UINT32 imR2yCalcYyw0OutWidth( kuint16 pipeNo )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 refPixs;
	kuint16 reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	if( gImR2yState[pipeNo].videoPhotoMode == ImR2yUtils_MODE_SDRAM_INPUT ) {
		// Photo mode.
		in_pixs = gImIoR2yRegPtr[pipeNo]->YYR.YYRHSIZ.word;
		refPixs = gImR2yState[pipeNo].ringPixsInfo.refPixs;
	}
	else {
		// Video mode.
		in_pixs = gImR2yState[pipeNo].inputSize.imgWidth;
		refPixs = gImR2yState[pipeNo].ringPixsInfo.refPixs;
	}

	if( (gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HSTA.bit.RSZ0HSTA == 0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HPIT.bit.RSZ0HPIT == ImR2yCtrl_STA_PIT_1_0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VSTA.bit.RSZ0VSTA == 0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VPIT.bit.RSZ0VPIT == ImR2yCtrl_STA_PIT_1_0)
	 ) {
		// dot by dot output mode(not resized)
		out_pixs = ((in_pixs - refPixs) & 0x1FFE);
	}
	else {
		if( (gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HPIT.bit.RSZ0HPIT == 0) || (in_pixs == 0) ) {
			out_pixs = 0xffffffff;
		}
		else {
			// Resize 0 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.RSZ0MD == ImR2yCtrl_RSZ_BICUBIC ){
				out_pixs = ((((in_pixs - refPixs - 2) * ImR2yCtrl_STA_PIT_1_0 - gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HSTA.bit.RSZ0HSTA - 1) / gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HPIT.bit.RSZ0HPIT) + 1);
			}
			else{
				out_pixs = ((((in_pixs - refPixs - 1) * ImR2yCtrl_STA_PIT_1_0 - gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HSTA.bit.RSZ0HSTA) / gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HPIT.bit.RSZ0HPIT) + 1);
			}

			// Reduction 0 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.RDC0EN == ImR2yCtrl_ENABLE_ON ){
				switch( gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.RDC0MD ){
					case ImR2yCtrl_RDC_MODE_DIV_2:
						reduct_val = 2;
						break;
					case ImR2yCtrl_RDC_MODE_DIV_4:
						reduct_val = 4;
						break;
					case ImR2yCtrl_RDC_MODE_DIV_8:
						reduct_val = 8;
						break;
					default:
						reduct_val = 1;
						break;
				}
				out_pixs /= reduct_val;
			}

			// Edge enhancement 0 block
			out_pixs = out_pixs & 0x1FFE;

			// YC Trimming 0 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.TRM0EN == ImR2yCtrl_ENABLE_ON ){
				out_pixs = gImIoR2yRegPtr[pipeNo]->YYW.TRM0H.bit.TRM0HSIZ;
			}
		}
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return out_pixs;
}

// Calculate YYW0 output image lines
static UINT32 imR2yCalcYyw0OutLines( kuint16 pipeNo )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 refPixs;
	kuint16 reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	if( gImR2yState[pipeNo].videoPhotoMode == ImR2yUtils_MODE_SDRAM_INPUT ) {
		// Photo mode.
		in_pixs = gImIoR2yRegPtr[pipeNo]->YYR.YYRVSIZ.word;
		refPixs = gImR2yState[pipeNo].ringPixsInfo.refPixs;
	}
	else {
		// Video mode.
		in_pixs = gImR2yState[pipeNo].inputSize.imgLines;
		refPixs = gImR2yState[pipeNo].ringPixsInfo.refPixs;
	}

	if( (gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HSTA.bit.RSZ0HSTA == 0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HPIT.bit.RSZ0HPIT == ImR2yCtrl_STA_PIT_1_0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VSTA.bit.RSZ0VSTA == 0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VPIT.bit.RSZ0VPIT == ImR2yCtrl_STA_PIT_1_0)
	 ) {
		// dot by dot output mode(not resized)
		out_pixs = ((in_pixs - refPixs) & 0x1FFE);
	}
	else {
		if( (gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VPIT.bit.RSZ0VPIT == 0) || (in_pixs == 0) ) {
			out_pixs = 0xffffffff;
		}
		else {
			// Resize 0 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.RSZ0MD == ImR2yCtrl_RSZ_BICUBIC ){
				out_pixs = ((((in_pixs - refPixs - 2) * ImR2yCtrl_STA_PIT_1_0 - gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VSTA.bit.RSZ0VSTA - 1) / gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VPIT.bit.RSZ0VPIT) + 1);
			}
			else{
				out_pixs = ((((in_pixs - refPixs - 1) * ImR2yCtrl_STA_PIT_1_0 - gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VSTA.bit.RSZ0VSTA) / gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VPIT.bit.RSZ0VPIT) + 1);
			}

			// Reduction 0 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.RDC0EN == ImR2yCtrl_ENABLE_ON ){
				switch( gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.RDC0MD ){
					case ImR2yCtrl_RDC_MODE_DIV_2:
						reduct_val = 2;
						break;
					case ImR2yCtrl_RDC_MODE_DIV_4:
						reduct_val = 4;
						break;
					case ImR2yCtrl_RDC_MODE_DIV_8:
						reduct_val = 8;
						break;
					default:
						reduct_val = 1;
						break;
				}
				out_pixs /= reduct_val;
			}

			// CSS0 block
			out_pixs = out_pixs & 0x1FFE;

			// YC Trimming 0 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.TRM0EN == ImR2yCtrl_ENABLE_ON ){
				out_pixs = gImIoR2yRegPtr[pipeNo]->YYW.TRM0V.bit.TRM0VSIZ;
			}
		}
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return out_pixs;
}

// Calculate YYW0a output image width
static UINT32 imR2yCalcYyw0aOutWidth( kuint16 pipeNo )
{
	UINT32 out_pixs;
	kuint16 reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	out_pixs = imR2yCalcYyw0OutWidth( pipeNo );

	switch( gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.CH0AMD ){
		case ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_4_Y:
			reduct_val = 4;
			break;
		case ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_8_Y:
			reduct_val = 8;
			break;
		case ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_32_SP:
			reduct_val = 32;
			break;
//		case ImR2yCtrl_YYW0A_OUTPUT_MODE_STOP:
		default:
			return 0xffffffff;
	}

	if( out_pixs % reduct_val ){
		out_pixs = out_pixs / reduct_val + 1;
	}
	else{
		out_pixs = out_pixs / reduct_val;
	}
	out_pixs = ( out_pixs + 1 ) & 0x1FFE;

	return out_pixs;
}

// Calculate YYW0a output image lines
static UINT32 imR2yCalcYyw0aOutLines( kuint16 pipeNo )
{
	UINT32 out_pixs;
	kuint16 reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	out_pixs = imR2yCalcYyw0OutLines( pipeNo );

	switch( gImIoR2yRegPtr[pipeNo]->YYW.YYW0MD.bit.CH0AMD ){
		case ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_4_Y:
			reduct_val = 4;
			break;
		case ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_8_Y:
			reduct_val = 8;
			break;
		case ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_32_SP:
			reduct_val = 32;
			break;
//		case ImR2yCtrl_YYW0A_OUTPUT_MODE_STOP:
		default:
			return 0xffffffff;
	}

	if( out_pixs % reduct_val ){
		out_pixs = out_pixs / reduct_val + 1;
	}
	else{
		out_pixs = out_pixs / reduct_val;
	}
	out_pixs = ( out_pixs + 1 ) & 0x1FFE;

	return out_pixs;
}

// Calculate YYW1 output image width
static UINT32 imR2yCalcYyw1OutWidth( kuint16 pipeNo )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 refPixs;
	kuint16 reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	if( gImR2yState[pipeNo].videoPhotoMode == ImR2yUtils_MODE_SDRAM_INPUT ) {
		// Photo mode.
		in_pixs = gImIoR2yRegPtr[pipeNo]->YYR.YYRHSIZ.word;
		refPixs = gImR2yState[pipeNo].ringPixsInfo.refPixs;
	}
	else {
		// Video mode.
		in_pixs = gImR2yState[pipeNo].inputSize.imgWidth;
		refPixs = gImR2yState[pipeNo].ringPixsInfo.refPixs;
	}

	if( (gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HSTA.bit.RSZ1HSTA == 0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HPIT.bit.RSZ1HPIT == ImR2yCtrl_STA_PIT_1_0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VSTA.bit.RSZ1VSTA == 0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VPIT.bit.RSZ1VPIT == ImR2yCtrl_STA_PIT_1_0)
	 ) {
		// dot by dot output mode(not resized)
		out_pixs = ((in_pixs - refPixs) & 0x1FFE);
	}
	else {
		if( (gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HPIT.bit.RSZ1HPIT == 0) || (in_pixs == 0) ) {
			out_pixs = 0xffffffff;
		}
		else {
			// Resize 1 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.RSZ1MD == ImR2yCtrl_RSZ_BICUBIC ){
				out_pixs = ((((in_pixs - refPixs - 2) * ImR2yCtrl_STA_PIT_1_0 - gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HSTA.bit.RSZ1HSTA - 1) / gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HPIT.bit.RSZ1HPIT) + 1);
			}
			else{
				out_pixs = ((((in_pixs - refPixs - 1) * ImR2yCtrl_STA_PIT_1_0 - gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HSTA.bit.RSZ1HSTA) / gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HPIT.bit.RSZ1HPIT) + 1);
			}

			// Reduction 1 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.RDC1EN == ImR2yCtrl_ENABLE_ON ){
				switch( gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.RDC1MD ){
					case ImR2yCtrl_RDC_MODE_DIV_2:
						reduct_val = 2;
						break;
					case ImR2yCtrl_RDC_MODE_DIV_4:
						reduct_val = 4;
						break;
					case ImR2yCtrl_RDC_MODE_DIV_8:
						reduct_val = 8;
						break;
					default:
						reduct_val = 1;
						break;
				}
				out_pixs /= reduct_val;
			}

			// Edge enhancement 1 block
			out_pixs = out_pixs & 0x1FFE;

			// YC Trimming 1 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.TRM1EN == ImR2yCtrl_ENABLE_ON ){
				out_pixs = gImIoR2yRegPtr[pipeNo]->YYW.TRM1H.bit.TRM1HSIZ;
			}
		}
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return out_pixs;
}

// Calculate YYW1 output image lines
static UINT32 imR2yCalcYyw1OutLines( kuint16 pipeNo )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 refPixs;
	kuint16 reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	if( gImR2yState[pipeNo].videoPhotoMode == ImR2yUtils_MODE_SDRAM_INPUT ) {
		// Photo mode.
		in_pixs = gImIoR2yRegPtr[pipeNo]->YYR.YYRVSIZ.word;
		refPixs = gImR2yState[pipeNo].ringPixsInfo.refPixs;
	}
	else {
		// Video mode.
		in_pixs = gImR2yState[pipeNo].inputSize.imgLines;
		refPixs = gImR2yState[pipeNo].ringPixsInfo.refPixs;
	}

	if( (gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HSTA.bit.RSZ1HSTA == 0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HPIT.bit.RSZ1HPIT == ImR2yCtrl_STA_PIT_1_0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VSTA.bit.RSZ1VSTA == 0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VPIT.bit.RSZ1VPIT == ImR2yCtrl_STA_PIT_1_0)
	 ) {
		// dot by dot output mode(not resized)
		out_pixs = ((in_pixs - refPixs) & 0x1FFE);
	}
	else {
		if( (gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VPIT.bit.RSZ1VPIT == 0) || (in_pixs == 0) ) {
			out_pixs = 0xffffffff;
		}
		else {
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.RSZ1MD == ImR2yCtrl_RSZ_BICUBIC ){
				out_pixs = ((((in_pixs - refPixs - 2) * ImR2yCtrl_STA_PIT_1_0 - gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VSTA.bit.RSZ1VSTA - 1) / gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VPIT.bit.RSZ1VPIT) + 1);
			}
			else{
				out_pixs = ((((in_pixs - refPixs - 1) * ImR2yCtrl_STA_PIT_1_0 - gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VSTA.bit.RSZ1VSTA) / gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VPIT.bit.RSZ1VPIT) + 1);
			}

			// Reduction 1 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.RDC1EN == ImR2yCtrl_ENABLE_ON ){
				switch( gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.RDC1MD ){
					case ImR2yCtrl_RDC_MODE_DIV_2:
						reduct_val = 2;
						break;
					case ImR2yCtrl_RDC_MODE_DIV_4:
						reduct_val = 4;
						break;
					case ImR2yCtrl_RDC_MODE_DIV_8:
						reduct_val = 8;
						break;
					default:
						reduct_val = 1;
						break;
				}
				out_pixs /= reduct_val;
			}

			// CSS1 block
			out_pixs = out_pixs & 0x1FFE;

			// YC Trimming 1 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW1MD.bit.TRM1EN == ImR2yCtrl_ENABLE_ON ){
				out_pixs = gImIoR2yRegPtr[pipeNo]->YYW.TRM1V.bit.TRM1VSIZ;
			}
		}
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return out_pixs;
}

// Calculate YYW2 output image width
static UINT32 imR2yCalcYyw2OutWidth( kuint16 pipeNo )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 refPixs;
	kuint16 reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	if( gImR2yState[pipeNo].videoPhotoMode == ImR2yUtils_MODE_SDRAM_INPUT ) {
		// Photo mode.
		in_pixs = gImIoR2yRegPtr[pipeNo]->YYR.YYRHSIZ.word;
		refPixs = gImR2yState[pipeNo].ringPixsInfo.refPixs;
	}
	else {
		// Video mode.
		in_pixs = gImR2yState[pipeNo].inputSize.imgWidth;
		refPixs = gImR2yState[pipeNo].ringPixsInfo.refPixs;
	}

	if( (gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HSTA.bit.RSZ2HSTA == 0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HPIT.bit.RSZ2HPIT == ImR2yCtrl_STA_PIT_1_0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VSTA.bit.RSZ2VSTA == 0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VPIT.bit.RSZ2VPIT == ImR2yCtrl_STA_PIT_1_0)
	 ) {
		// dot by dot output mode(not resized)
		out_pixs = ((in_pixs - refPixs) & 0x1FFE);
	}
	else {
		if( (gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HPIT.bit.RSZ2HPIT == 0) || (in_pixs == 0) ) {
			out_pixs = 0xffffffff;
		}
		else {
			// Resize 2 block
			out_pixs = ((((in_pixs - refPixs - 1) * ImR2yCtrl_STA_PIT_1_0 - gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HSTA.bit.RSZ2HSTA) / gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HPIT.bit.RSZ2HPIT) + 1);

			// Reduction 2 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW2MD.bit.RDC2EN == ImR2yCtrl_ENABLE_ON ){
				switch( gImIoR2yRegPtr[pipeNo]->YYW.YYW2MD.bit.RDC2MD ){
					case ImR2yCtrl_RDC_MODE_DIV_2:
						reduct_val = 2;
						break;
					case ImR2yCtrl_RDC_MODE_DIV_4:
						reduct_val = 4;
						break;
					case ImR2yCtrl_RDC_MODE_DIV_8:
						reduct_val = 8;
						break;
					default:
						reduct_val = 1;
						break;
				}
				out_pixs /= reduct_val;
			}
			out_pixs = out_pixs & 0x1FFE;

			// YC Trimming 2 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW2MD.bit.TRM2EN == ImR2yCtrl_ENABLE_ON ){
				out_pixs = gImIoR2yRegPtr[pipeNo]->YYW.TRM2H.bit.TRM2HSIZ;
			}
		}
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return out_pixs;
}

// Calculate YYW2 output image lines
static UINT32 imR2yCalcYyw2OutLines( kuint16 pipeNo )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 refPixs;
	kuint16 reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	if( gImR2yState[pipeNo].videoPhotoMode == ImR2yUtils_MODE_SDRAM_INPUT ) {
		// Photo mode.
		in_pixs = gImIoR2yRegPtr[pipeNo]->YYR.YYRVSIZ.word;
		refPixs = gImR2yState[pipeNo].ringPixsInfo.refPixs;
	}
	else {
		// Video mode.
		in_pixs = gImR2yState[pipeNo].inputSize.imgLines;
		refPixs = gImR2yState[pipeNo].ringPixsInfo.refPixs;
	}

	if( (gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HSTA.bit.RSZ2HSTA == 0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HPIT.bit.RSZ2HPIT == ImR2yCtrl_STA_PIT_1_0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VSTA.bit.RSZ2VSTA == 0)
	 && (gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VPIT.bit.RSZ2VPIT == ImR2yCtrl_STA_PIT_1_0)
	 ) {
		// dot by dot output mode(not resized)
		out_pixs = ((in_pixs - refPixs) & 0x1FFE);
	}
	else {
		if( (gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VPIT.bit.RSZ2VPIT == 0) || (in_pixs == 0) ) {
			out_pixs = 0xffffffff;
		}
		else {
			// Resize 2 block
			out_pixs = ((((in_pixs - refPixs - 1) * ImR2yCtrl_STA_PIT_1_0 - gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VSTA.bit.RSZ2VSTA) / gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VPIT.bit.RSZ2VPIT) + 1);

			// Reduction 2 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW2MD.bit.RDC2EN == ImR2yCtrl_ENABLE_ON ){
				switch( gImIoR2yRegPtr[pipeNo]->YYW.YYW2MD.bit.RDC2MD ){
					case ImR2yCtrl_RDC_MODE_DIV_2:
						reduct_val = 2;
						break;
					case ImR2yCtrl_RDC_MODE_DIV_4:
						reduct_val = 4;
						break;
					case ImR2yCtrl_RDC_MODE_DIV_8:
						reduct_val = 8;
						break;
					default:
						reduct_val = 1;
						break;
				}
				out_pixs /= reduct_val;
			}

			// YC Trimming 2 block
			if( gImIoR2yRegPtr[pipeNo]->YYW.YYW2MD.bit.TRM2EN == ImR2yCtrl_ENABLE_ON ){
				out_pixs = gImIoR2yRegPtr[pipeNo]->YYW.TRM2V.bit.TRM2VSIZ;
			}
		}
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return out_pixs;
}
#endif

/*
*PUBLIC
*/
/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
void im_r2y_stat_init(ImR2yStat *self, kuint16 pipeNo, kuint16 size_coef)
{

	// Initialize of State & Handler management information
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();

	memset( (kuint16*)&(imR2yUtils->gImR2yState[pipeNo]), 0, sizeof(R2yStateMng) * size_coef );
	// initialize of Resize information
	im_r2y2_sta_manage_init(im_r2y2_new(), pipeNo, size_coef);
	// Initialize of control information
	memset( (kuint16*)&(imR2yUtils->gImR2yYyraOfsInfo[pipeNo]), 0, sizeof(R2yYyraOfsInfo) * size_coef );

}

#ifdef IM_R2Y_STATUS_PRINT
void im_r2y_stat_print_status(ImR2yStat *self)
{
	UINT32 loopcnt;
	UINT32 loopcnt2;
	UINT32 loopcnt3;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);
	volatile R2yYyraOfsInfo* gImR2yYyraOfsInfo = im_r2y_utils_get_yyra_ofs_info(imR2yUtils);

	for( loopcnt3 = 0; loopcnt3 < 2; loopcnt3++ ) {
		Ddim_Print(( "PIPE%u:\n", loopcnt3+1 ));
		Ddim_Print(( "\tOutput pixs[%u]:\n", loopcnt3 ));
		Ddim_Print(( "\t\tYYW0 x=%u, y=%u\n", imR2yCalcYyw0OutWidth(loopcnt3), imR2yCalcYyw0OutLines(loopcnt3) ));
		Ddim_Print(( "\t\tYYW0a x=%u, y=%u\n", imR2yCalcYyw0aOutWidth(loopcnt3), imR2yCalcYyw0aOutLines(loopcnt3) ));
		Ddim_Print(( "\t\tYYW1 x=%u, y=%u\n", imR2yCalcYyw1OutWidth(loopcnt3), imR2yCalcYyw1OutLines(loopcnt3) ));
		Ddim_Print(( "\t\tYYW2 x=%u, y=%u\n", imR2yCalcYyw2OutWidth(loopcnt3), imR2yCalcYyw2OutLines(loopcnt3) ));
		Ddim_Print(( "\tgIM_R2Y_State[%u]:\n", loopcnt3 ));
		Ddim_Print(( "\t\twas_started = %u\n", gImR2yState[loopcnt3].wasStarted ));
		Ddim_Print(( "\t\tvideo_photo_mode = %u\n", gImR2yState[loopcnt3].videoPhotoMode ));
		Ddim_Print(( "\t\tbusy_state = %u\n", gImR2yState[loopcnt3].busyState ));
		Ddim_Print(( "\t\tycf_bypass = %u\n", gImR2yState[loopcnt3].ycfBypass ));
		Ddim_Print(( "\t\tycf_padding = %u\n", gImR2yState[loopcnt3].ycfPadding ));
		Ddim_Print(( "\t\tmcc_select = %u\n", gImR2yState[loopcnt3].mccSelect ));
		Ddim_Print(( "\t\tmcc_bit_shift = %u\n", gImR2yState[loopcnt3].mccBitShift ));
		Ddim_Print(( "\t\tpix_avg_reduct_mode[0] = %u\n", gImR2yState[loopcnt3].pixAvgReductMode[0] ));
		Ddim_Print(( "\t\tpix_avg_reduct_mode[1] = %u\n", gImR2yState[loopcnt3].pixAvgReductMode[1] ));
		Ddim_Print(( "\t\tpix_avg_reduct_mode[2] = %u\n", gImR2yState[loopcnt3].pixAvgReductMode[2] ));
		Ddim_Print(( "\t\tpix_avg_reduct_en[0] = %u\n", gImR2yState[loopcnt3].pixAvgReductEn[0] ));
		Ddim_Print(( "\t\tpix_avg_reduct_en[1] = %u\n", gImR2yState[loopcnt3].pixAvgReductEn[1] ));
		Ddim_Print(( "\t\tpix_avg_reduct_en[2] = %u\n", gImR2yState[loopcnt3].pixAvgReductEn[2] ));
		Ddim_Print(( "\t\toutput_mode_0a = %u\n", gImR2yState[loopcnt3].outputMode0a ));
		Ddim_Print(( "\t\tint_status = %u\n", gImR2yState[loopcnt3].intStatus ));
		Ddim_Print(( "\t\tr2y_user_handler = 0x%x\n", (UINT32)gImR2yState[loopcnt3].r2yUserHandler ));
		Ddim_Print(( "\t\tuser_param = 0x%x\n", (UINT32)gImR2yState[loopcnt3].userParam ));
		Ddim_Print(( "\t\tinput_dtype = %u\n", gImR2yState[loopcnt3].inputDtype ));
		Ddim_Print(( "\t\tin_addr[0] = 0x%x\n", (UINT32)gImR2yState[loopcnt3].inAddr[ImR2yCtrl_PORT_0] ));
		Ddim_Print(( "\t\tin_addr[1] = 0x%x\n", (UINT32)gImR2yState[loopcnt3].inAddr[ImR2yCtrl_PORT_1] ));
		Ddim_Print(( "\t\tin_addr[2] = 0x%x\n", (UINT32)gImR2yState[loopcnt3].inAddr[ImR2yCtrl_PORT_2] ));
		Ddim_Print(( "\t\tinput_global = %u\n", gImR2yState[loopcnt3].inputGlobal ));
		Ddim_Print(( "\t\ttop_offset[0] = %u\n", gImR2yState[loopcnt3].topOffset[ImR2yCtrl_PORT_0] ));
		Ddim_Print(( "\t\ttop_offset[1] = %u\n", gImR2yState[loopcnt3].topOffset[ImR2yCtrl_PORT_1] ));
		Ddim_Print(( "\t\ttop_offset[2] = %u\n", gImR2yState[loopcnt3].topOffset[ImR2yCtrl_PORT_2] ));
		Ddim_Print(( "\t\tyyw_enable[0] = %u\n", gImR2yState[loopcnt3].yywEnable[ImR2yCtrl_YYW_CH_0] ));
		Ddim_Print(( "\t\tyyw_enable[1] = %u\n", gImR2yState[loopcnt3].yywEnable[ImR2yCtrl_YYW_CH_1] ));
		Ddim_Print(( "\t\tyyw_enable[2] = %u\n", gImR2yState[loopcnt3].yywEnable[ImR2yCtrl_YYW_CH_2] ));
		Ddim_Print(( "\t\tyyw_rect_valid = %u\n", gImR2yState[loopcnt3].yywRectValid ));
		Ddim_Print(( "\t\tyyw_width[0] = %u\n", gImR2yState[loopcnt3].yywWidth[ImR2yCtrl_YYW_CH_0] ));
		Ddim_Print(( "\t\tyyw_width[1] = %u\n", gImR2yState[loopcnt3].yywWidth[ImR2yCtrl_YYW_CH_1] ));
		Ddim_Print(( "\t\tyyw_width[2] = %u\n", gImR2yState[loopcnt3].yywWidth[ImR2yCtrl_YYW_CH_2] ));
		Ddim_Print(( "\t\tyyw_lines[0] = %u\n", gImR2yState[loopcnt3].yywLines[ImR2yCtrl_YYW_CH_0] ));
		Ddim_Print(( "\t\tyyw_lines[1] = %u\n", gImR2yState[loopcnt3].yywLines[ImR2yCtrl_YYW_CH_1] ));
		Ddim_Print(( "\t\tyyw_lines[2] = %u\n", gImR2yState[loopcnt3].yywLines[ImR2yCtrl_YYW_CH_2] ));
		Ddim_Print(( "\t\tring_pixs_info.padEnable = %u\n", gImR2yState[loopcnt3].ringPixsInfo.padEnable ));
		Ddim_Print(( "\t\tring_pixs_info.ringPixs = %u\n", gImR2yState[loopcnt3].ringPixsInfo.ringPixs ));
		Ddim_Print(( "\t\tring_pixs_info.padPixs = %u\n", gImR2yState[loopcnt3].ringPixsInfo.padPixs ));
		Ddim_Print(( "\t\tring_pixs_info.refPixs = %u\n", gImR2yState[loopcnt3].ringPixsInfo.refPixs ));
		Ddim_Print(( "\t\tinput_size.imgTop = %u\n", gImR2yState[loopcnt3].inputSize.imgTop ));
		Ddim_Print(( "\t\tinput_size.imgLeft = %u\n", gImR2yState[loopcnt3].inputSize.imgLeft ));
		Ddim_Print(( "\t\tinput_size.imgWidth = %u\n", gImR2yState[loopcnt3].inputSize.imgWidth ));
		Ddim_Print(( "\t\tinput_size.imgLines = %u\n", gImR2yState[loopcnt3].inputSize.imgLines ));
		Ddim_Print(( "\t\ttrim[0].trimming_enable = %u\n", gImR2yState[loopcnt3].trim[0].trimming_enable ));
		Ddim_Print(( "\t\ttrim[0].trim_window.imgTop = %u\n", gImR2yState[loopcnt3].trim[0].trim_window.imgTop ));
		Ddim_Print(( "\t\ttrim[0].trim_window.imgLeft = %u\n", gImR2yState[loopcnt3].trim[0].trim_window.imgLeft ));
		Ddim_Print(( "\t\ttrim[0].trim_window.imgWidth = %u\n", gImR2yState[loopcnt3].trim[0].trim_window.imgWidth ));
		Ddim_Print(( "\t\ttrim[0].trim_window.imgLines = %u\n", gImR2yState[loopcnt3].trim[0].trim_window.imgLines ));
		Ddim_Print(( "\t\ttrim[1].trimming_enable = %u\n", gImR2yState[loopcnt3].trim[1].trimming_enable ));
		Ddim_Print(( "\t\ttrim[1].trim_window.imgTop = %u\n", gImR2yState[loopcnt3].trim[1].trim_window.imgTop ));
		Ddim_Print(( "\t\ttrim[1].trim_window.imgLeft = %u\n", gImR2yState[loopcnt3].trim[1].trim_window.imgLeft ));
		Ddim_Print(( "\t\ttrim[1].trim_window.imgWidth = %u\n", gImR2yState[loopcnt3].trim[1].trim_window.imgWidth ));
		Ddim_Print(( "\t\ttrim[1].trim_window.imgLines = %u\n", gImR2yState[loopcnt3].trim[1].trim_window.imgLines ));
		Ddim_Print(( "\t\ttrim[2].trimming_enable = %u\n", gImR2yState[loopcnt3].trim[2].trimming_enable ));
		Ddim_Print(( "\t\ttrim[2].trim_window.imgTop = %u\n", gImR2yState[loopcnt3].trim[2].trim_window.imgTop ));
		Ddim_Print(( "\t\ttrim[2].trim_window.imgLeft = %u\n", gImR2yState[loopcnt3].trim[2].trim_window.imgLeft ));
		Ddim_Print(( "\t\ttrim[2].trim_window.imgWidth = %u\n", gImR2yState[loopcnt3].trim[2].trim_window.imgWidth ));
		Ddim_Print(( "\t\ttrim[2].trim_window.imgLines = %u\n", gImR2yState[loopcnt3].trim[2].trim_window.imgLines ));
		Ddim_Print(( "\t\ttrim_ext.trimming_enable_b = %u\n", gImR2yState[loopcnt3].trimExt.trimming_enable_b ));
		Ddim_Print(( "\t\ttrim_ext.trimming_enable_c = %u\n", gImR2yState[loopcnt3].trimExt.trimming_enable_c ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_b.imgTop = %u\n", gImR2yState[loopcnt3].trimExt.trim_window_b.imgTop ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_b.imgLeft = %u\n", gImR2yState[loopcnt3].trimExt.trim_window_b.imgLeft ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_b.imgWidth = %u\n", gImR2yState[loopcnt3].trimExt.trim_window_b.imgWidth ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_b.imgLines = %u\n", gImR2yState[loopcnt3].trimExt.trim_window_b.imgLines ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_c.imgTop = %u\n", gImR2yState[loopcnt3].trimExt.trim_window_c.imgTop ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_c.imgLeft = %u\n", gImR2yState[loopcnt3].trimExt.trim_window_c.imgLeft ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_c.imgWidth = %u\n", gImR2yState[loopcnt3].trimExt.trim_window_c.imgWidth ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_c.imgLines = %u\n", gImR2yState[loopcnt3].trimExt.trim_window_c.imgLines ));

		for( loopcnt2 = 0; loopcnt2 < ImR2yCtrl_YYW_CH_MAX; loopcnt2++ ) {
			Ddim_Print(( "\tgIM_R2Y_Out_Mng[%u]:\n", loopcnt2 ));
			im_r2y_ddim_print(im_r2y_new(),  loopcnt, loopcnt2, loopcnt3)
		}

		Ddim_Print(( "\tgIM_R2Y_yyra_ofs_info:\n" ));
		Ddim_Print(( "\t\tofs_x_pixs[%u] = %u\n", loopcnt2, gImR2yYyraOfsInfo[loopcnt3].ofsXPixs ));
		Ddim_Print(( "\t\tofs_y_pixs[%u] = %u\n", loopcnt2, gImR2yYyraOfsInfo[loopcnt3].ofsYPixs ));
		Ddim_Print(( "\t\tofs_bytes[%u] = %lu\n", loopcnt2, gImR2yYyraOfsInfo[loopcnt3].ofsBytes ));
	}
}

void im_r2y_stat_print_clock_status(ImR2yStat *self)
{
	//TODO imr2yclk.c中
	im_r2y_clk_ddim_print(im_r2y_clk_new());
	Ddim_Print(( "\n" ));
}

void im_r2y_stat_print_acc_en_status(ImR2yStat *self)
{
	UINT32 loopcnt;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  ImR2yCtrl_PIPE12 );
	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "PIPE%x\n", loopcnt+1 ));
		Ddim_Print(( "YYRAEN_RGB_DEKNEE = 0x%x\n", gImIoR2yRegPtr[loopcnt]->R2Y_CMN.RAMAEN.bit.YYRAEN_RGB_DEKNEE ));
		Ddim_Print(( "YYRAEN_YYR = 0x%x\n", gImIoR2yRegPtr[loopcnt]->R2Y_CMN.RAMAEN.bit.YYRAEN_YYR ));
		Ddim_Print(( "YW0AEN_YYW0 = 0x%x\n", gImIoR2yRegPtr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0 ));
		Ddim_Print(( "YW0AEN_YYW0_BICUBIC = 0x%x\n", gImIoR2yRegPtr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0_BICUBIC ));
		Ddim_Print(( "YW0AEN_YYW0_EDGE = 0x%x\n", gImIoR2yRegPtr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0_EDGE ));
		Ddim_Print(( "YW0AEN_YYW0A = 0x%x\n", gImIoR2yRegPtr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0A ));
		Ddim_Print(( "YW1AEN_YYW1 = 0x%x\n", gImIoR2yRegPtr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1 ));
		Ddim_Print(( "YW1AEN_YYW1_BICUBIC = 0x%x\n", gImIoR2yRegPtr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1_BICUBIC ));
		Ddim_Print(( "YW1AEN_YYW1_EDGE = 0x%x\n", gImIoR2yRegPtr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1_EDGE ));
		Ddim_Print(( "YW2AEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW2AEN ));
		Ddim_Print(( "HSTAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->R2Y_CMN.RAMAEN.bit.HSTAEN ));

		Ddim_Print(( "TCTAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->F_R2Y.BTC.TCTCTL.bit.TCTAEN ));
		Ddim_Print(( "TCHAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->F_R2Y.BTC.TCHSCTL.bit.TCHAEN ));
		Ddim_Print(( "TCAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->F_R2Y.TC.TCCTL.bit.TCAEN ));
		Ddim_Print(( "GMAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->F_R2Y.GAM.GMCTL.bit.GMAEN ));
		Ddim_Print(( "GMYAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->F_R2Y.GAM.GMCTL.bit.GMYAEN ));
		Ddim_Print(( "EHSAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->F_R2Y.EGHW.EGHWCTL.bit.EHSAEN ));
		Ddim_Print(( "EHTAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->F_R2Y.EGHW.EGHWCTL.bit.EHTAEN ));
		Ddim_Print(( "EMSAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->F_R2Y.EGMW.EGMWCTL.bit.EMSAEN ));
		Ddim_Print(( "EMTAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->F_R2Y.EGMW.EGMWCTL.bit.EMTAEN ));
		Ddim_Print(( "ELSAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->F_R2Y.EGLW.EGLWCTL.bit.ELSAEN ));
		Ddim_Print(( "ELTAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->F_R2Y.EGLW.EGLWCTL.bit.ELTAEN ));
		Ddim_Print(( "EMPAEN = 0x%x\n", gImIoR2yRegPtr[loopcnt]->F_R2Y.MAPSCL.EGMPCTL.bit.EMPAEN ));
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  ImR2yCtrl_PIPE12 );
}
#endif

ImR2yStat *im_r2y_stat_new(void)
{
	ImR2yStat* self = k_object_new_with_private(IM_TYPE_R2Y_STAT,sizeof(ImR2yStatPrivate));
	return self;
}
