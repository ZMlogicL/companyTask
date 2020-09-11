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
static UINT32 imR2yCalcYyw0OutWidth( UCHAR pipe_no )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 ref_pixs;
	UCHAR reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	if( gIM_R2Y_State[pipe_no].video_photo_mode == D_IM_R2Y_MODE_SDRAM_INPUT ) {
		// Photo mode.
		in_pixs = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRHSIZ.word;
		ref_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	}
	else {
		// Video mode.
		in_pixs = gIM_R2Y_State[pipe_no].input_size.img_width;
		ref_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	}

	if( (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HSTA.bit.RSZ0HSTA == 0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HPIT.bit.RSZ0HPIT == D_IM_R2Y_STA_PIT_1_0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VSTA.bit.RSZ0VSTA == 0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VPIT.bit.RSZ0VPIT == D_IM_R2Y_STA_PIT_1_0)
	 ) {
		// dot by dot output mode(not resized)
		out_pixs = ((in_pixs - ref_pixs) & 0x1FFE);
	}
	else {
		if( (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HPIT.bit.RSZ0HPIT == 0) || (in_pixs == 0) ) {
			out_pixs = 0xffffffff;
		}
		else {
			// Resize 0 block
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.RSZ0MD == D_IM_R2Y_RSZ_BICUBIC ){
				out_pixs = ((((in_pixs - ref_pixs - 2) * D_IM_R2Y_STA_PIT_1_0 - gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HSTA.bit.RSZ0HSTA - 1) / gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HPIT.bit.RSZ0HPIT) + 1);
			}
			else{
				out_pixs = ((((in_pixs - ref_pixs - 1) * D_IM_R2Y_STA_PIT_1_0 - gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HSTA.bit.RSZ0HSTA) / gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HPIT.bit.RSZ0HPIT) + 1);
			}

			// Reduction 0 block
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.RDC0EN == D_IM_R2Y_ENABLE_ON ){
				switch( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.RDC0MD ){
					case D_IM_R2Y_RDC_MODE_DIV_2:
						reduct_val = 2;
						break;
					case D_IM_R2Y_RDC_MODE_DIV_4:
						reduct_val = 4;
						break;
					case D_IM_R2Y_RDC_MODE_DIV_8:
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
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.TRM0EN == D_IM_R2Y_ENABLE_ON ){
				out_pixs = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM0H.bit.TRM0HSIZ;
			}
		}
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return out_pixs;
}

// Calculate YYW0 output image lines
static UINT32 imR2yCalcYyw0OutLines( UCHAR pipe_no )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 ref_pixs;
	UCHAR reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	if( gIM_R2Y_State[pipe_no].video_photo_mode == D_IM_R2Y_MODE_SDRAM_INPUT ) {
		// Photo mode.
		in_pixs = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRVSIZ.word;
		ref_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	}
	else {
		// Video mode.
		in_pixs = gIM_R2Y_State[pipe_no].input_size.img_lines;
		ref_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	}

	if( (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HSTA.bit.RSZ0HSTA == 0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HPIT.bit.RSZ0HPIT == D_IM_R2Y_STA_PIT_1_0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VSTA.bit.RSZ0VSTA == 0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VPIT.bit.RSZ0VPIT == D_IM_R2Y_STA_PIT_1_0)
	 ) {
		// dot by dot output mode(not resized)
		out_pixs = ((in_pixs - ref_pixs) & 0x1FFE);
	}
	else {
		if( (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VPIT.bit.RSZ0VPIT == 0) || (in_pixs == 0) ) {
			out_pixs = 0xffffffff;
		}
		else {
			// Resize 0 block
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.RSZ0MD == D_IM_R2Y_RSZ_BICUBIC ){
				out_pixs = ((((in_pixs - ref_pixs - 2) * D_IM_R2Y_STA_PIT_1_0 - gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VSTA.bit.RSZ0VSTA - 1) / gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VPIT.bit.RSZ0VPIT) + 1);
			}
			else{
				out_pixs = ((((in_pixs - ref_pixs - 1) * D_IM_R2Y_STA_PIT_1_0 - gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VSTA.bit.RSZ0VSTA) / gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VPIT.bit.RSZ0VPIT) + 1);
			}

			// Reduction 0 block
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.RDC0EN == D_IM_R2Y_ENABLE_ON ){
				switch( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.RDC0MD ){
					case D_IM_R2Y_RDC_MODE_DIV_2:
						reduct_val = 2;
						break;
					case D_IM_R2Y_RDC_MODE_DIV_4:
						reduct_val = 4;
						break;
					case D_IM_R2Y_RDC_MODE_DIV_8:
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
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.TRM0EN == D_IM_R2Y_ENABLE_ON ){
				out_pixs = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM0V.bit.TRM0VSIZ;
			}
		}
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return out_pixs;
}

// Calculate YYW0a output image width
static UINT32 imR2yCalcYyw0aOutWidth( UCHAR pipe_no )
{
	UINT32 out_pixs;
	UCHAR reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	out_pixs = imR2yCalcYyw0OutWidth( pipe_no );

	switch( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.CH0AMD ){
		case D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_4_Y:
			reduct_val = 4;
			break;
		case D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_8_Y:
			reduct_val = 8;
			break;
		case D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_32_SP:
			reduct_val = 32;
			break;
//		case D_IM_R2Y_YYW0A_OUTPUT_MODE_STOP:
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
static UINT32 imR2yCalcYyw0aOutLines( UCHAR pipe_no )
{
	UINT32 out_pixs;
	UCHAR reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	out_pixs = imR2yCalcYyw0OutLines( pipe_no );

	switch( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0MD.bit.CH0AMD ){
		case D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_4_Y:
			reduct_val = 4;
			break;
		case D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_8_Y:
			reduct_val = 8;
			break;
		case D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_32_SP:
			reduct_val = 32;
			break;
//		case D_IM_R2Y_YYW0A_OUTPUT_MODE_STOP:
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
static UINT32 imR2yCalcYyw1OutWidth( UCHAR pipe_no )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 ref_pixs;
	UCHAR reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	if( gIM_R2Y_State[pipe_no].video_photo_mode == D_IM_R2Y_MODE_SDRAM_INPUT ) {
		// Photo mode.
		in_pixs = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRHSIZ.word;
		ref_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	}
	else {
		// Video mode.
		in_pixs = gIM_R2Y_State[pipe_no].input_size.img_width;
		ref_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	}

	if( (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HSTA.bit.RSZ1HSTA == 0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HPIT.bit.RSZ1HPIT == D_IM_R2Y_STA_PIT_1_0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VSTA.bit.RSZ1VSTA == 0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VPIT.bit.RSZ1VPIT == D_IM_R2Y_STA_PIT_1_0)
	 ) {
		// dot by dot output mode(not resized)
		out_pixs = ((in_pixs - ref_pixs) & 0x1FFE);
	}
	else {
		if( (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HPIT.bit.RSZ1HPIT == 0) || (in_pixs == 0) ) {
			out_pixs = 0xffffffff;
		}
		else {
			// Resize 1 block
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.RSZ1MD == D_IM_R2Y_RSZ_BICUBIC ){
				out_pixs = ((((in_pixs - ref_pixs - 2) * D_IM_R2Y_STA_PIT_1_0 - gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HSTA.bit.RSZ1HSTA - 1) / gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HPIT.bit.RSZ1HPIT) + 1);
			}
			else{
				out_pixs = ((((in_pixs - ref_pixs - 1) * D_IM_R2Y_STA_PIT_1_0 - gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HSTA.bit.RSZ1HSTA) / gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HPIT.bit.RSZ1HPIT) + 1);
			}

			// Reduction 1 block
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.RDC1EN == D_IM_R2Y_ENABLE_ON ){
				switch( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.RDC1MD ){
					case D_IM_R2Y_RDC_MODE_DIV_2:
						reduct_val = 2;
						break;
					case D_IM_R2Y_RDC_MODE_DIV_4:
						reduct_val = 4;
						break;
					case D_IM_R2Y_RDC_MODE_DIV_8:
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
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.TRM1EN == D_IM_R2Y_ENABLE_ON ){
				out_pixs = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM1H.bit.TRM1HSIZ;
			}
		}
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return out_pixs;
}

// Calculate YYW1 output image lines
static UINT32 imR2yCalcYyw1OutLines( UCHAR pipe_no )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 ref_pixs;
	UCHAR reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	if( gIM_R2Y_State[pipe_no].video_photo_mode == D_IM_R2Y_MODE_SDRAM_INPUT ) {
		// Photo mode.
		in_pixs = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRVSIZ.word;
		ref_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	}
	else {
		// Video mode.
		in_pixs = gIM_R2Y_State[pipe_no].input_size.img_lines;
		ref_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	}

	if( (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HSTA.bit.RSZ1HSTA == 0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HPIT.bit.RSZ1HPIT == D_IM_R2Y_STA_PIT_1_0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VSTA.bit.RSZ1VSTA == 0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VPIT.bit.RSZ1VPIT == D_IM_R2Y_STA_PIT_1_0)
	 ) {
		// dot by dot output mode(not resized)
		out_pixs = ((in_pixs - ref_pixs) & 0x1FFE);
	}
	else {
		if( (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VPIT.bit.RSZ1VPIT == 0) || (in_pixs == 0) ) {
			out_pixs = 0xffffffff;
		}
		else {
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.RSZ1MD == D_IM_R2Y_RSZ_BICUBIC ){
				out_pixs = ((((in_pixs - ref_pixs - 2) * D_IM_R2Y_STA_PIT_1_0 - gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VSTA.bit.RSZ1VSTA - 1) / gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VPIT.bit.RSZ1VPIT) + 1);
			}
			else{
				out_pixs = ((((in_pixs - ref_pixs - 1) * D_IM_R2Y_STA_PIT_1_0 - gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VSTA.bit.RSZ1VSTA) / gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VPIT.bit.RSZ1VPIT) + 1);
			}

			// Reduction 1 block
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.RDC1EN == D_IM_R2Y_ENABLE_ON ){
				switch( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.RDC1MD ){
					case D_IM_R2Y_RDC_MODE_DIV_2:
						reduct_val = 2;
						break;
					case D_IM_R2Y_RDC_MODE_DIV_4:
						reduct_val = 4;
						break;
					case D_IM_R2Y_RDC_MODE_DIV_8:
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
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1MD.bit.TRM1EN == D_IM_R2Y_ENABLE_ON ){
				out_pixs = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM1V.bit.TRM1VSIZ;
			}
		}
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return out_pixs;
}

// Calculate YYW2 output image width
static UINT32 imR2yCalcYyw2OutWidth( UCHAR pipe_no )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 ref_pixs;
	UCHAR reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	if( gIM_R2Y_State[pipe_no].video_photo_mode == D_IM_R2Y_MODE_SDRAM_INPUT ) {
		// Photo mode.
		in_pixs = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRHSIZ.word;
		ref_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	}
	else {
		// Video mode.
		in_pixs = gIM_R2Y_State[pipe_no].input_size.img_width;
		ref_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	}

	if( (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HSTA.bit.RSZ2HSTA == 0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HPIT.bit.RSZ2HPIT == D_IM_R2Y_STA_PIT_1_0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VSTA.bit.RSZ2VSTA == 0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VPIT.bit.RSZ2VPIT == D_IM_R2Y_STA_PIT_1_0)
	 ) {
		// dot by dot output mode(not resized)
		out_pixs = ((in_pixs - ref_pixs) & 0x1FFE);
	}
	else {
		if( (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HPIT.bit.RSZ2HPIT == 0) || (in_pixs == 0) ) {
			out_pixs = 0xffffffff;
		}
		else {
			// Resize 2 block
			out_pixs = ((((in_pixs - ref_pixs - 1) * D_IM_R2Y_STA_PIT_1_0 - gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HSTA.bit.RSZ2HSTA) / gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HPIT.bit.RSZ2HPIT) + 1);

			// Reduction 2 block
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2MD.bit.RDC2EN == D_IM_R2Y_ENABLE_ON ){
				switch( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2MD.bit.RDC2MD ){
					case D_IM_R2Y_RDC_MODE_DIV_2:
						reduct_val = 2;
						break;
					case D_IM_R2Y_RDC_MODE_DIV_4:
						reduct_val = 4;
						break;
					case D_IM_R2Y_RDC_MODE_DIV_8:
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
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2MD.bit.TRM2EN == D_IM_R2Y_ENABLE_ON ){
				out_pixs = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM2H.bit.TRM2HSIZ;
			}
		}
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return out_pixs;
}

// Calculate YYW2 output image lines
static UINT32 imR2yCalcYyw2OutLines( UCHAR pipe_no )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 ref_pixs;
	UCHAR reduct_val;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	if( gIM_R2Y_State[pipe_no].video_photo_mode == D_IM_R2Y_MODE_SDRAM_INPUT ) {
		// Photo mode.
		in_pixs = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRVSIZ.word;
		ref_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	}
	else {
		// Video mode.
		in_pixs = gIM_R2Y_State[pipe_no].input_size.img_lines;
		ref_pixs = gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	}

	if( (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HSTA.bit.RSZ2HSTA == 0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HPIT.bit.RSZ2HPIT == D_IM_R2Y_STA_PIT_1_0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VSTA.bit.RSZ2VSTA == 0)
	 && (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VPIT.bit.RSZ2VPIT == D_IM_R2Y_STA_PIT_1_0)
	 ) {
		// dot by dot output mode(not resized)
		out_pixs = ((in_pixs - ref_pixs) & 0x1FFE);
	}
	else {
		if( (gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VPIT.bit.RSZ2VPIT == 0) || (in_pixs == 0) ) {
			out_pixs = 0xffffffff;
		}
		else {
			// Resize 2 block
			out_pixs = ((((in_pixs - ref_pixs - 1) * D_IM_R2Y_STA_PIT_1_0 - gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VSTA.bit.RSZ2VSTA) / gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VPIT.bit.RSZ2VPIT) + 1);

			// Reduction 2 block
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2MD.bit.RDC2EN == D_IM_R2Y_ENABLE_ON ){
				switch( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2MD.bit.RDC2MD ){
					case D_IM_R2Y_RDC_MODE_DIV_2:
						reduct_val = 2;
						break;
					case D_IM_R2Y_RDC_MODE_DIV_4:
						reduct_val = 4;
						break;
					case D_IM_R2Y_RDC_MODE_DIV_8:
						reduct_val = 8;
						break;
					default:
						reduct_val = 1;
						break;
				}
				out_pixs /= reduct_val;
			}

			// YC Trimming 2 block
			if( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2MD.bit.TRM2EN == D_IM_R2Y_ENABLE_ON ){
				out_pixs = gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.TRM2V.bit.TRM2VSIZ;
			}
		}
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

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
void im_r2y_stat_init(ImR2yStat *self, UCHAR pipe_no, UCHAR size_coef)
{

	// Initialize of State & Handler management information
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();

	memset( (USHORT*)&(imR2yUtils->gIM_R2Y_State[pipe_no]), 0, sizeof(T_IM_R2Y_STATE_MNG) * size_coef );
	// initialize of Resize information
	im_r2y2_sta_manage_init(im_r2y2_new(), pipe_no, size_coef);
	// Initialize of control information
	memset( (USHORT*)&(imR2yUtils->gIM_R2Y_yyra_ofs_info[pipe_no]), 0, sizeof(T_IM_R2Y_YYRA_OFS_INFO) * size_coef );

}

#ifdef IM_R2Y_STATUS_PRINT
VOID im_r2y_stat_print_status(ImR2yStat *self)
{
	UINT32 loopcnt;
	UINT32 loopcnt2;
	UINT32 loopcnt3;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);
	volatile T_IM_R2Y_YYRA_OFS_INFO* gIM_R2Y_yyra_ofs_info = im_r2y_utils_get_yyra_ofs_info(imR2yUtils);

	for( loopcnt3 = 0; loopcnt3 < 2; loopcnt3++ ) {
		Ddim_Print(( "PIPE%u:\n", loopcnt3+1 ));
		Ddim_Print(( "\tOutput pixs[%u]:\n", loopcnt3 ));
		Ddim_Print(( "\t\tYYW0 x=%u, y=%u\n", imR2yCalcYyw0OutWidth(loopcnt3), imR2yCalcYyw0OutLines(loopcnt3) ));
		Ddim_Print(( "\t\tYYW0a x=%u, y=%u\n", imR2yCalcYyw0aOutWidth(loopcnt3), imR2yCalcYyw0aOutLines(loopcnt3) ));
		Ddim_Print(( "\t\tYYW1 x=%u, y=%u\n", imR2yCalcYyw1OutWidth(loopcnt3), imR2yCalcYyw1OutLines(loopcnt3) ));
		Ddim_Print(( "\t\tYYW2 x=%u, y=%u\n", imR2yCalcYyw2OutWidth(loopcnt3), imR2yCalcYyw2OutLines(loopcnt3) ));
		Ddim_Print(( "\tgIM_R2Y_State[%u]:\n", loopcnt3 ));
		Ddim_Print(( "\t\twas_started = %u\n", gIM_R2Y_State[loopcnt3].was_started ));
		Ddim_Print(( "\t\tvideo_photo_mode = %u\n", gIM_R2Y_State[loopcnt3].video_photo_mode ));
		Ddim_Print(( "\t\tbusy_state = %u\n", gIM_R2Y_State[loopcnt3].busy_state ));
		Ddim_Print(( "\t\tycf_bypass = %u\n", gIM_R2Y_State[loopcnt3].ycf_bypass ));
		Ddim_Print(( "\t\tycf_padding = %u\n", gIM_R2Y_State[loopcnt3].ycf_padding ));
		Ddim_Print(( "\t\tmcc_select = %u\n", gIM_R2Y_State[loopcnt3].mcc_select ));
		Ddim_Print(( "\t\tmcc_bit_shift = %u\n", gIM_R2Y_State[loopcnt3].mcc_bit_shift ));
		Ddim_Print(( "\t\tpix_avg_reduct_mode[0] = %u\n", gIM_R2Y_State[loopcnt3].pix_avg_reduct_mode[0] ));
		Ddim_Print(( "\t\tpix_avg_reduct_mode[1] = %u\n", gIM_R2Y_State[loopcnt3].pix_avg_reduct_mode[1] ));
		Ddim_Print(( "\t\tpix_avg_reduct_mode[2] = %u\n", gIM_R2Y_State[loopcnt3].pix_avg_reduct_mode[2] ));
		Ddim_Print(( "\t\tpix_avg_reduct_en[0] = %u\n", gIM_R2Y_State[loopcnt3].pix_avg_reduct_en[0] ));
		Ddim_Print(( "\t\tpix_avg_reduct_en[1] = %u\n", gIM_R2Y_State[loopcnt3].pix_avg_reduct_en[1] ));
		Ddim_Print(( "\t\tpix_avg_reduct_en[2] = %u\n", gIM_R2Y_State[loopcnt3].pix_avg_reduct_en[2] ));
		Ddim_Print(( "\t\toutput_mode_0a = %u\n", gIM_R2Y_State[loopcnt3].output_mode_0a ));
		Ddim_Print(( "\t\tint_status = %u\n", gIM_R2Y_State[loopcnt3].int_status ));
		Ddim_Print(( "\t\tr2y_user_handler = 0x%x\n", (UINT32)gIM_R2Y_State[loopcnt3].r2y_user_handler ));
		Ddim_Print(( "\t\tuser_param = 0x%x\n", (UINT32)gIM_R2Y_State[loopcnt3].user_param ));
		Ddim_Print(( "\t\tinput_dtype = %u\n", gIM_R2Y_State[loopcnt3].input_dtype ));
		Ddim_Print(( "\t\tin_addr[0] = 0x%x\n", (UINT32)gIM_R2Y_State[loopcnt3].in_addr[D_IM_R2Y_PORT_0] ));
		Ddim_Print(( "\t\tin_addr[1] = 0x%x\n", (UINT32)gIM_R2Y_State[loopcnt3].in_addr[D_IM_R2Y_PORT_1] ));
		Ddim_Print(( "\t\tin_addr[2] = 0x%x\n", (UINT32)gIM_R2Y_State[loopcnt3].in_addr[D_IM_R2Y_PORT_2] ));
		Ddim_Print(( "\t\tinput_global = %u\n", gIM_R2Y_State[loopcnt3].input_global ));
		Ddim_Print(( "\t\ttop_offset[0] = %u\n", gIM_R2Y_State[loopcnt3].top_offset[D_IM_R2Y_PORT_0] ));
		Ddim_Print(( "\t\ttop_offset[1] = %u\n", gIM_R2Y_State[loopcnt3].top_offset[D_IM_R2Y_PORT_1] ));
		Ddim_Print(( "\t\ttop_offset[2] = %u\n", gIM_R2Y_State[loopcnt3].top_offset[D_IM_R2Y_PORT_2] ));
		Ddim_Print(( "\t\tyyw_enable[0] = %u\n", gIM_R2Y_State[loopcnt3].yyw_enable[D_IM_R2Y_YYW_CH_0] ));
		Ddim_Print(( "\t\tyyw_enable[1] = %u\n", gIM_R2Y_State[loopcnt3].yyw_enable[D_IM_R2Y_YYW_CH_1] ));
		Ddim_Print(( "\t\tyyw_enable[2] = %u\n", gIM_R2Y_State[loopcnt3].yyw_enable[D_IM_R2Y_YYW_CH_2] ));
		Ddim_Print(( "\t\tyyw_rect_valid = %u\n", gIM_R2Y_State[loopcnt3].yyw_rect_valid ));
		Ddim_Print(( "\t\tyyw_width[0] = %u\n", gIM_R2Y_State[loopcnt3].yyw_width[D_IM_R2Y_YYW_CH_0] ));
		Ddim_Print(( "\t\tyyw_width[1] = %u\n", gIM_R2Y_State[loopcnt3].yyw_width[D_IM_R2Y_YYW_CH_1] ));
		Ddim_Print(( "\t\tyyw_width[2] = %u\n", gIM_R2Y_State[loopcnt3].yyw_width[D_IM_R2Y_YYW_CH_2] ));
		Ddim_Print(( "\t\tyyw_lines[0] = %u\n", gIM_R2Y_State[loopcnt3].yyw_lines[D_IM_R2Y_YYW_CH_0] ));
		Ddim_Print(( "\t\tyyw_lines[1] = %u\n", gIM_R2Y_State[loopcnt3].yyw_lines[D_IM_R2Y_YYW_CH_1] ));
		Ddim_Print(( "\t\tyyw_lines[2] = %u\n", gIM_R2Y_State[loopcnt3].yyw_lines[D_IM_R2Y_YYW_CH_2] ));
		Ddim_Print(( "\t\tring_pixs_info.pad_enable = %u\n", gIM_R2Y_State[loopcnt3].ring_pixs_info.pad_enable ));
		Ddim_Print(( "\t\tring_pixs_info.ring_pixs = %u\n", gIM_R2Y_State[loopcnt3].ring_pixs_info.ring_pixs ));
		Ddim_Print(( "\t\tring_pixs_info.pad_pixs = %u\n", gIM_R2Y_State[loopcnt3].ring_pixs_info.pad_pixs ));
		Ddim_Print(( "\t\tring_pixs_info.ref_pixs = %u\n", gIM_R2Y_State[loopcnt3].ring_pixs_info.ref_pixs ));
		Ddim_Print(( "\t\tinput_size.img_top = %u\n", gIM_R2Y_State[loopcnt3].input_size.img_top ));
		Ddim_Print(( "\t\tinput_size.img_left = %u\n", gIM_R2Y_State[loopcnt3].input_size.img_left ));
		Ddim_Print(( "\t\tinput_size.img_width = %u\n", gIM_R2Y_State[loopcnt3].input_size.img_width ));
		Ddim_Print(( "\t\tinput_size.img_lines = %u\n", gIM_R2Y_State[loopcnt3].input_size.img_lines ));
		Ddim_Print(( "\t\ttrim[0].trimming_enable = %u\n", gIM_R2Y_State[loopcnt3].trim[0].trimming_enable ));
		Ddim_Print(( "\t\ttrim[0].trim_window.img_top = %u\n", gIM_R2Y_State[loopcnt3].trim[0].trim_window.img_top ));
		Ddim_Print(( "\t\ttrim[0].trim_window.img_left = %u\n", gIM_R2Y_State[loopcnt3].trim[0].trim_window.img_left ));
		Ddim_Print(( "\t\ttrim[0].trim_window.img_width = %u\n", gIM_R2Y_State[loopcnt3].trim[0].trim_window.img_width ));
		Ddim_Print(( "\t\ttrim[0].trim_window.img_lines = %u\n", gIM_R2Y_State[loopcnt3].trim[0].trim_window.img_lines ));
		Ddim_Print(( "\t\ttrim[1].trimming_enable = %u\n", gIM_R2Y_State[loopcnt3].trim[1].trimming_enable ));
		Ddim_Print(( "\t\ttrim[1].trim_window.img_top = %u\n", gIM_R2Y_State[loopcnt3].trim[1].trim_window.img_top ));
		Ddim_Print(( "\t\ttrim[1].trim_window.img_left = %u\n", gIM_R2Y_State[loopcnt3].trim[1].trim_window.img_left ));
		Ddim_Print(( "\t\ttrim[1].trim_window.img_width = %u\n", gIM_R2Y_State[loopcnt3].trim[1].trim_window.img_width ));
		Ddim_Print(( "\t\ttrim[1].trim_window.img_lines = %u\n", gIM_R2Y_State[loopcnt3].trim[1].trim_window.img_lines ));
		Ddim_Print(( "\t\ttrim[2].trimming_enable = %u\n", gIM_R2Y_State[loopcnt3].trim[2].trimming_enable ));
		Ddim_Print(( "\t\ttrim[2].trim_window.img_top = %u\n", gIM_R2Y_State[loopcnt3].trim[2].trim_window.img_top ));
		Ddim_Print(( "\t\ttrim[2].trim_window.img_left = %u\n", gIM_R2Y_State[loopcnt3].trim[2].trim_window.img_left ));
		Ddim_Print(( "\t\ttrim[2].trim_window.img_width = %u\n", gIM_R2Y_State[loopcnt3].trim[2].trim_window.img_width ));
		Ddim_Print(( "\t\ttrim[2].trim_window.img_lines = %u\n", gIM_R2Y_State[loopcnt3].trim[2].trim_window.img_lines ));
		Ddim_Print(( "\t\ttrim_ext.trimming_enable_b = %u\n", gIM_R2Y_State[loopcnt3].trim_ext.trimming_enable_b ));
		Ddim_Print(( "\t\ttrim_ext.trimming_enable_c = %u\n", gIM_R2Y_State[loopcnt3].trim_ext.trimming_enable_c ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_b.img_top = %u\n", gIM_R2Y_State[loopcnt3].trim_ext.trim_window_b.img_top ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_b.img_left = %u\n", gIM_R2Y_State[loopcnt3].trim_ext.trim_window_b.img_left ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_b.img_width = %u\n", gIM_R2Y_State[loopcnt3].trim_ext.trim_window_b.img_width ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_b.img_lines = %u\n", gIM_R2Y_State[loopcnt3].trim_ext.trim_window_b.img_lines ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_c.img_top = %u\n", gIM_R2Y_State[loopcnt3].trim_ext.trim_window_c.img_top ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_c.img_left = %u\n", gIM_R2Y_State[loopcnt3].trim_ext.trim_window_c.img_left ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_c.img_width = %u\n", gIM_R2Y_State[loopcnt3].trim_ext.trim_window_c.img_width ));
		Ddim_Print(( "\t\ttrim_ext.trim_window_c.img_lines = %u\n", gIM_R2Y_State[loopcnt3].trim_ext.trim_window_c.img_lines ));

		for( loopcnt2 = 0; loopcnt2 < D_IM_R2Y_YYW_CH_MAX; loopcnt2++ ) {
			Ddim_Print(( "\tgIM_R2Y_Out_Mng[%u]:\n", loopcnt2 ));
			im_r2y_ddim_print(im_r2y_new(),  loopcnt, loopcnt2, loopcnt3)
		}

		Ddim_Print(( "\tgIM_R2Y_yyra_ofs_info:\n" ));
		Ddim_Print(( "\t\tofs_x_pixs[%u] = %u\n", loopcnt2, gIM_R2Y_yyra_ofs_info[loopcnt3].ofs_x_pixs ));
		Ddim_Print(( "\t\tofs_y_pixs[%u] = %u\n", loopcnt2, gIM_R2Y_yyra_ofs_info[loopcnt3].ofs_y_pixs ));
		Ddim_Print(( "\t\tofs_bytes[%u] = %lu\n", loopcnt2, gIM_R2Y_yyra_ofs_info[loopcnt3].ofs_bytes ));
	}
}

VOID im_r2y_stat_print_clock_status(ImR2yStat *self)
{
	//TODO imr2yclk.c中
	im_r2y_clk_ddim_print(im_r2y_clk_new());
	Ddim_Print(( "\n" ));
}

VOID im_r2y_stat_print_acc_en_status(ImR2yStat *self)
{
	UINT32 loopcnt;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  D_IM_R2Y_PIPE12 );
	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "PIPE%x\n", loopcnt+1 ));
		Ddim_Print(( "YYRAEN_RGB_DEKNEE = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->R2Y_CMN.RAMAEN.bit.YYRAEN_RGB_DEKNEE ));
		Ddim_Print(( "YYRAEN_YYR = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->R2Y_CMN.RAMAEN.bit.YYRAEN_YYR ));
		Ddim_Print(( "YW0AEN_YYW0 = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0 ));
		Ddim_Print(( "YW0AEN_YYW0_BICUBIC = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0_BICUBIC ));
		Ddim_Print(( "YW0AEN_YYW0_EDGE = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0_EDGE ));
		Ddim_Print(( "YW0AEN_YYW0A = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW0AEN_YYW0A ));
		Ddim_Print(( "YW1AEN_YYW1 = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1 ));
		Ddim_Print(( "YW1AEN_YYW1_BICUBIC = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1_BICUBIC ));
		Ddim_Print(( "YW1AEN_YYW1_EDGE = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW1AEN_YYW1_EDGE ));
		Ddim_Print(( "YW2AEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->R2Y_CMN.RAMAEN.bit.YW2AEN ));
		Ddim_Print(( "HSTAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->R2Y_CMN.RAMAEN.bit.HSTAEN ));

		Ddim_Print(( "TCTAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->F_R2Y.BTC.TCTCTL.bit.TCTAEN ));
		Ddim_Print(( "TCHAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->F_R2Y.BTC.TCHSCTL.bit.TCHAEN ));
		Ddim_Print(( "TCAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->F_R2Y.TC.TCCTL.bit.TCAEN ));
		Ddim_Print(( "GMAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->F_R2Y.GAM.GMCTL.bit.GMAEN ));
		Ddim_Print(( "GMYAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->F_R2Y.GAM.GMCTL.bit.GMYAEN ));
		Ddim_Print(( "EHSAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->F_R2Y.EGHW.EGHWCTL.bit.EHSAEN ));
		Ddim_Print(( "EHTAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->F_R2Y.EGHW.EGHWCTL.bit.EHTAEN ));
		Ddim_Print(( "EMSAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->F_R2Y.EGMW.EGMWCTL.bit.EMSAEN ));
		Ddim_Print(( "EMTAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->F_R2Y.EGMW.EGMWCTL.bit.EMTAEN ));
		Ddim_Print(( "ELSAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->F_R2Y.EGLW.EGLWCTL.bit.ELSAEN ));
		Ddim_Print(( "ELTAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->F_R2Y.EGLW.EGLWCTL.bit.ELTAEN ));
		Ddim_Print(( "EMPAEN = 0x%x\n", gIM_Io_R2y_Reg_Ptr[loopcnt]->F_R2Y.MAPSCL.EGMPCTL.bit.EMPAEN ));
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  D_IM_R2Y_PIPE12 );
}
#endif

ImR2yStat *im_r2y_stat_new(void)
{
	ImR2yStat* self = k_object_new_with_private(IM_TYPE_R2Y_STAT,sizeof(ImR2yStatPrivate));
	return self;
}
