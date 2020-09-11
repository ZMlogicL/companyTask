/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
*@author              :李昕
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

#ifndef _IM_CNR_GET_H_
#define _IM_CNR_GET_H_

#include <klib.h>
#include "driver_common.h"
#include "ddim_typedef.h"
// get register value for RDMA
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"
#include "_jdscnr_otf_reg_rw.h"
#include "imcnr.h"
#include "imcnrset.h"

#define IM_TYPE_CNR_GET		(im_cnr_get_get_type())
#define IM_CNR_GET(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImCnrGet))
#define IM_IS_CNR_GET(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_CNR_GET))

typedef struct 				_ImCnrGet ImCnrGet;
typedef struct 				_ImCnrGetPrivate ImCnrGetPrivate;

struct _ImCnrGet {
	KObject parent;
};

KConstType 		    im_cnr_get_get_type(void);
ImCnrGet*		        im_cnr_get_new(void);

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------- driver section ----------------------------
#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
//------------ for RDMA ----------------
/**
Get SPR setting address information for C for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	cnr_ctrl_c		Top address of the address array of C suppre parameter
@param[out]	size			Size of the address array of C suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_ctrl_c(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CTRL_C** const cnr_ctrl_c, ULONG* const size );

/**
Get SPR setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	cnr_ctrl_c		Top address of the address array of C suppre parameter
@param[out]	size			Size of the address array of C suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_ctrl_c(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CTRL_C** const cnr_ctrl_c, ULONG* const size );

/**
Get SPR setting address information for Y for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	cnr_ctrl_y		Top address of the address array of Y suppre parameter
@param[out]	size			Size of the address array of Y suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_ctrl_y(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_OFL_CTRL_Y** const cnr_ctrl_y, ULONG* const size );

/**
Get SPR table setting address information for Y for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	cnr_yspr_tbl	Top address of the address array of Y suppre table parameter
@param[out]	size			Size of the address array of Y suppre table parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_yspr_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_OFL_YSPR_TBL** const cnr_yspr_tbl, ULONG* const size );

/**
Get CSPR Mid-Y setting address information for C for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	cspr_mid_y_tbl	Top address of the address array of C suppre Middle-Y parameter
@param[out]	size			Size of the address array of C suppre Middle-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_mid_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL** const cspr_mid_y_tbl, ULONG* const size );

/**
Get CSPR Mid-Y setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	cspr_mid_y_tbl	Top address of the address array of C suppre Middle-Y parameter
@param[out]	size			Size of the address array of C suppre Middle-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_mid_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL** const cspr_mid_y_tbl, ULONG* const size );

/**
Get CSPR Mid-CC-Y setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_mid_cc_y_tbl	Top address of the address array of C suppre Middle-CC-Y parameter
@param[out]	size				Size of the address array of C suppre Middle-CC-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_mid_cc_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL** const cspr_mid_cc_y_tbl, ULONG* const size );

/**
Get CSPR Mid-CC-Y setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_mid_cc_y_tbl	Top address of the address array of C suppre Middle-CC-Y parameter
@param[out]	size				Size of the address array of C suppre Middle-CC-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_mid_cc_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL** const cspr_mid_cc_y_tbl, ULONG* const size );

/**
Get CSPR Mid-CC-C setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_mid_cc_c_tbl	Top address of the address array of C suppre Middle-CC-C parameter
@param[out]	size				Size of the address array of C suppre Middle-CC-C parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_mid_cc_c_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL** const cspr_mid_cc_c_tbl, ULONG* const size );

/**
Get CSPR Mid-CC-C setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_mid_cc_c_tbl	Top address of the address array of C suppre Middle-CC-C parameter
@param[out]	size				Size of the address array of C suppre Middle-CC-C parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_mid_cc_c_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL** const cspr_mid_cc_c_tbl, ULONG* const size );

/**
Get CSPR Low-Y setting address information for C for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	cspr_low_y_tbl	Top address of the address array of C suppre Low-Y parameter
@param[out]	size			Size of the address array of C suppre Low-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_low_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL** const cspr_low_y_tbl, ULONG* const size );

/**
Get CSPR Low-Y setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	cspr_low_y_tbl	Top address of the address array of C suppre Low-Y parameter
@param[out]	size			Size of the address array of C suppre Low-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_low_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL** const cspr_low_y_tbl, ULONG* const size );

/**
Get CSPR Low-CC-Y setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_low_cc_y_tbl	Top address of the address array of C suppre Low-CC-Y parameter
@param[out]	size				Size of the address array of C suppre Low-CC-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_low_cc_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL** const cspr_low_cc_y_tbl, ULONG* const size );

/**
Get CSPR Low-CC-Y setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_low_cc_y_tbl	Top address of the address array of C suppre Low-CC-Y parameter
@param[out]	size				Size of the address array of C suppre Low-CC-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_low_cc_y_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL** const cspr_low_cc_y_tbl, ULONG* const size );

/**
Get CSPR Low-CC-C setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_low_cc_c_tbl	Top address of the address array of C suppre Low-CC-C parameter
@param[out]	size				Size of the address array of C suppre Low-CC-C parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_low_cc_c_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL** const cspr_low_cc_c_tbl, ULONG* const size );

/**
Get CSPR Low-CC-C setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_low_cc_c_tbl	Top address of the address array of C suppre Low-CC-C parameter
@param[out]	size				Size of the address array of C suppre Low-CC-C parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_low_cc_c_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL** const cspr_low_cc_c_tbl, ULONG* const size );

/**
Get CSPR Edge setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_edge_tbl		Top address of the address array of C suppre Edge parameter
@param[out]	size				Size of the address array of C suppre Edge parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_edge_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL** const cspr_edge_tbl, ULONG* const size );

/**
Get CSPR Edge setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	cspr_edge_tbl	Top address of the address array of C suppre Edge parameter
@param[out]	size			Size of the address array of C suppre Edge parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_edge_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL** const cspr_edge_tbl, ULONG* const size );

/**
Get CSPR Hue Specified setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_hue_tbl		Top address of the address array of C suppre Hue Specified parameter
@param[out]	size				Size of the address array of C suppre Hue Specified parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_hue_spec_table( UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL** const cspr_hue_tbl, ULONG* const size );

/**
Get CSPR Hue Specified setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	cspr_hue_tbl	Top address of the address array of C suppre Hue Specified parameter
@param[out]	size			Size of the address array of C suppre Hue Specified parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_hue_spec_table(ImCnrGet*self, UCHAR ch, const T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL** const cspr_hue_tbl, ULONG* const size );

/**
Get CSPR SPRS setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_sprs_cc_tbl	Top address of the address array of C suppre SPRS CC parameter
@param[out]	size				Size of the address array of C suppre SPRS CC parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_sprs_cc_table( UCHAR ch, const T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL** const cspr_sprs_cc_tbl, ULONG* const size );

/**
Get CSPR SPRS setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_sprs_cc_tbl	Top address of the address array of C suppre SPRS CC parameter
@param[out]	size				Size of the address array of C suppre SPRS CC parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_sprs_cc_table( UCHAR ch, const T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL** const cspr_sprs_cc_tbl, ULONG* const size );

/**
Get CSPR SPRD setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_sprd_cc_tbl	Top address of the address array of C suppre SPRD CC parameter
@param[out]	size				Size of the address array of C suppre SPRD CC parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_sprd_cc_table( UCHAR ch, const T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL** const cspr_sprd_cc_tbl, ULONG* const size );

/**
Get CSPR SPRD setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_sprd_cc_tbl	Top address of the address array of C suppre SPRD CC parameter
@param[out]	size				Size of the address array of C suppre SPRD CC parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_sprd_cc_table( UCHAR ch, const T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL** const cspr_sprd_cc_tbl, ULONG* const size );

#endif

#ifdef __cplusplus
}
#endif

#endif//_IM_CNR_GET_H_

/**
@weakgroup im_cnr
@{

<hr>

@section im_cnr_sample	Sample code
@code
// SAMPLE CODE //
#include "imcnr.h"

INT32 sample_cnr( VOID )
{
	INT32 im_ercd;
	INT32 im_ercd2;
	T_IM_CNR_OFL_CTRL cnr_ctrl = {
		.mode = E_IM_CNR_YCC_MODE_YCC422,			// mode			SPR YCC mode	@@YUV_MODE

		.width = 4000,								// width		SPR valid data width	@@HSIZE
		.lines = 3000,								// lines		SPR valid data lines	@@VSIZE

		.r_y_width = 4000,							// r_y_width	Y width for read	@@RYDEF
		.r_y_addr = 0x42000000,						// r_y_addr		Y address for read	@@RYTA

		.r_c_width = 4000 /2,						// r_c_width	CbCr width for read	@@RCDEF
		.r_cb_addr = 0x43000000,					// r_cb_addr	Cb address for read	@@RCBTA
		.r_cr_addr = 0x44000000,					// r_cr_addr	Cr address for read	@@RCRTA

		.w_y_width = 4000,							// w_y_width	Y width for write	@@WYDEF
		.w_y_addr = 0x45000000,						// w_y_addr		Y address for write	@@WYTA

		.w_c_width = 4000 /2,						// w_c_width	CbCr width for write	@@WCDEF
		.w_cb_addr = 0x46000000,					// w_cb_addr	Cb address for write	@@WCBTA
		.w_cr_addr = 0x47000000,					// w_cr_addr	Cr address for write	@@WCRTA

		.work_addr = 0x48000000,					// work_addr	Address fir work area	@@TMPTA

		.divide_top = E_IM_CNR_VPROCESS_NORM,		// divide_top	Virtucal process devide	@@VDIVT
		.divide_bot = E_IM_CNR_VPROCESS_NORM,		// divide_bot	Virtucal process devide	@@VDIVB

		.pCallBack = NULL,							// pCallBack	callback function
		.user_param = 0,							// user_param	callback arg
	};
	T_IM_CNR_CTRL_C cnr_ctrl_c = {
		.enable = E_IM_CNR_ONOFF_ENABLE,					// enable				CbCr SPR enable @@CSPREN
		.gradation_keep_en = E_IM_CNR_ONOFF_ENABLE,			// enable				gradation keep enable @@CGDKEN
		.mid_freq_nr = {									// Middle range frequency Color NR parmeter
			.enable = E_IM_CNR_ONOFF_ENABLE,				// Middle CbCr SPR enable @@MCEN
			.h_y_threshold = {								// Middle SPR Y threshold for horizontal	@@MCYTHH
				0, 0, 0, 0										// register default. Need tuning.
			},
			.v_y_threshold = {								// Middle SPR Y threshold for vertical		@@MCYTHV
				0, 0, 0, 0										// register default. Need tuning.
			},
			.h_c_threshold = {								// Middle SPR CbCr threshold for horizontal	@@MCCTHH
				0, 0, 0, 0										// register default. Need tuning.
			},
			.v_c_threshold = {								// Middle SPR CbCr threshold for vertical	@@MCCTHV
				0, 0, 0, 0										// register default. Need tuning.
			},
			.y_threshold_cor = 0,							// Middle SPR Y threshold coring	@@MCYDYMYCR
			.y_threshold_gain = 0,							// register default. Need tuning.
			.y_threshold_dym_en = E_IM_CNR_ONOFF_DISABLE,	// Middle Y threshold dynamic setting enable @@MCYDYM
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,	// Middle Y threshold scale enable @@MCYSCL
			.c_y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,	// Middle CbCr threshold Y scale enable @@MCSSCL
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,	// Middle CbCr threshold scale enable @@MCCSCL
		},
		.low_freq_nr = {									// Low range frequency Color NR parmeters
			.enable = E_IM_CNR_ONOFF_ENABLE,					// Low CbCr SPR enable @@LCEN
			.h_y_threshold = {								// Low SPR Y threshold for horizontal		@@LCYTHH
				0, 0, 0, 0										// register default. Need tuning.
			},
			.v_y_threshold = {								// Low SPR Y threshold for vertical			@@LCYTHV
				0, 0, 0, 0										// register default. Need tuning.
			},
			.h_c_threshold = {								// Low SPR CbCr threshold for horizontal	@@LCCTHH
				0, 0, 0, 0										// register default. Need tuning.
			},
			.v_c_threshold = {								// Low SPR CbCr threshold for vertical		@@LCCTHV
				0, 0, 0, 0										// register default. Need tuning.
			},
			.y_threshold_cor = 0,							// Low SPR Y threshold coring	@@LCYDYMYCR
			.y_threshold_gain = 0,							// register default. Need tuning.
			.y_threshold_dym_en = E_IM_CNR_ONOFF_DISABLE,	// Low Y threshold dynamic setting enable @@LCYDYM
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,	// Low Y threshold scale enable @@LCYSCL
			.c_y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,	// Low CbCr threshold Y scale enable @@LCSSCL
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,	// Low CbCr threshold scale enable @@LCCSCL
		},
	};
	T_IM_CNR_OFL_CTRL_Y cnr_ctrl_y = {
		.enable = E_IM_CNR_ONOFF_ENABLE,					// enable				Y SPR enable @@YSPREN
		.threshold_type = E_IM_CNR_THRES_REGISTER,			// threshold_type		threshold type for Y	@@YSPRMODE YSPRMD
		.level = E_IM_CNR_LEVEL_LOW,						// level				filter level		@@YSPRMODE YSPRFE
		.h_y_threshold = 0,									// h_y_threshold		SPR Y threshold for horizontal		@@YSPRFXEYH
		.v_y_threshold = 0,									// v_y_threshold		SPR Y threshold for vertical		@@YSPRFXEYV
		.h_c_threshold = 0,									// h_c_threshold		SPR CbCr threshold for horizontal	@@YSPRFXECH
		.v_c_threshold = 0,									// v_c_threshold		SPR CbCr threshold for vertical		@@YSPRFXECV
		.alpha_blend_ratio = 0,								// alpha_blend_ratio	Alpha blend ratio			@@YSPRALPBD
	};



	im_ercd = Im_CNR_OFL_Open( 0, 100 );	// wai_sem timeout 100 ticks
	if( im_ercd != D_DDIM_OK ) {
		return im_ercd;
	}

	// don't forget Im_CNR_OFL_Close() after this line

	while( 1 ) {
		im_ercd = Im_CNR_OFL_Ctrl( 0, &cnr_ctrl );
		if( im_ercd != D_DDIM_OK ) {
			break;
		}

		im_ercd = im_cnr_axi_ofl_ctrl_c(NULL, 0, &cnr_ctrl_c );
		if( im_ercd != D_DDIM_OK ) {
			break;
		}

		im_ercd = im_cnr_axi_ofl_ctrl_y(NULL, 0, &cnr_ctrl_y );
		if( im_ercd != D_DDIM_OK ) {
			break;
		}

		im_ercd = Im_CNR_OFL_Start_Sync( 0, 1000 );	// wait timeout 1000 ticks
		if( im_ercd != D_DDIM_OK ) {
			break;
		}

		break;
	}

	im_ercd2 = Im_CNR_OFL_Stop( 0 );
	if( im_ercd2 != D_DDIM_OK ) {
		im_ercd = im_ercd2;
	}

	if( im_ercd == D_DDIM_OK ) {
		im_ercd2 = Im_CNR_OFL_Close( 0 );
		if( im_ercd2 != D_DDIM_OK ) {
			im_ercd = im_ercd2;
		}
	}
	else {
		(VOID)Im_CNR_OFL_Close( 0 );
	}

	return im_ercd;
}
@endcode
@}*/
