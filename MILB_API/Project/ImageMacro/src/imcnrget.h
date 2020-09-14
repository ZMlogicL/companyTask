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
INT32 im_cnr_get_rdma_addr_ofl_ctrl_c(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCtrlC** const cnr_ctrl_c, ULONG* const size );

/**
Get SPR setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	cnr_ctrl_c		Top address of the address array of C suppre parameter
@param[out]	size			Size of the address array of C suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_ctrl_c(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCtrlC** const cnr_ctrl_c, ULONG* const size );

/**
Get SPR setting address information for Y for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	cnr_ctrl_y		Top address of the address array of Y suppre parameter
@param[out]	size			Size of the address array of Y suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_ctrl_y(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrOflCtrlY** const cnr_ctrl_y, ULONG* const size );

/**
Get SPR table setting address information for Y for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	cnr_yspr_tbl	Top address of the address array of Y suppre table parameter
@param[out]	size			Size of the address array of Y suppre table parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_yspr_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrOflYsprTbl** const cnr_yspr_tbl, ULONG* const size );

/**
Get CSPR Mid-Y setting address information for C for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	cspr_mid_y_tbl	Top address of the address array of C suppre Middle-Y parameter
@param[out]	size			Size of the address array of C suppre Middle-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_mid_y_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprMidYTbl** const cspr_mid_y_tbl, ULONG* const size );

/**
Get CSPR Mid-Y setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	cspr_mid_y_tbl	Top address of the address array of C suppre Middle-Y parameter
@param[out]	size			Size of the address array of C suppre Middle-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_mid_y_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprMidYTbl** const cspr_mid_y_tbl, ULONG* const size );

/**
Get CSPR Mid-CC-Y setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_mid_cc_y_tbl	Top address of the address array of C suppre Middle-CC-Y parameter
@param[out]	size				Size of the address array of C suppre Middle-CC-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_mid_cc_y_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprMidCcYTbl** const cspr_mid_cc_y_tbl, ULONG* const size );

/**
Get CSPR Mid-CC-Y setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_mid_cc_y_tbl	Top address of the address array of C suppre Middle-CC-Y parameter
@param[out]	size				Size of the address array of C suppre Middle-CC-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_mid_cc_y_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprMidCcYTbl** const cspr_mid_cc_y_tbl, ULONG* const size );

/**
Get CSPR Mid-CC-C setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_mid_cc_c_tbl	Top address of the address array of C suppre Middle-CC-C parameter
@param[out]	size				Size of the address array of C suppre Middle-CC-C parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_mid_cc_c_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprMidCcCTbl** const cspr_mid_cc_c_tbl, ULONG* const size );

/**
Get CSPR Mid-CC-C setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_mid_cc_c_tbl	Top address of the address array of C suppre Middle-CC-C parameter
@param[out]	size				Size of the address array of C suppre Middle-CC-C parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_mid_cc_c_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprMidCcCTbl** const cspr_mid_cc_c_tbl, ULONG* const size );

/**
Get CSPR Low-Y setting address information for C for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	cspr_low_y_tbl	Top address of the address array of C suppre Low-Y parameter
@param[out]	size			Size of the address array of C suppre Low-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_low_y_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprLowYTbl** const cspr_low_y_tbl, ULONG* const size );

/**
Get CSPR Low-Y setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	cspr_low_y_tbl	Top address of the address array of C suppre Low-Y parameter
@param[out]	size			Size of the address array of C suppre Low-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_low_y_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprLowYTbl** const cspr_low_y_tbl, ULONG* const size );

/**
Get CSPR Low-CC-Y setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_low_cc_y_tbl	Top address of the address array of C suppre Low-CC-Y parameter
@param[out]	size				Size of the address array of C suppre Low-CC-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_low_cc_y_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprLowCcYTbl** const cspr_low_cc_y_tbl, ULONG* const size );

/**
Get CSPR Low-CC-Y setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_low_cc_y_tbl	Top address of the address array of C suppre Low-CC-Y parameter
@param[out]	size				Size of the address array of C suppre Low-CC-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_low_cc_y_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprLowCcYTbl** const cspr_low_cc_y_tbl, ULONG* const size );

/**
Get CSPR Low-CC-C setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_low_cc_c_tbl	Top address of the address array of C suppre Low-CC-C parameter
@param[out]	size				Size of the address array of C suppre Low-CC-C parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_low_cc_c_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprLowCcCTbl** const cspr_low_cc_c_tbl, ULONG* const size );

/**
Get CSPR Low-CC-C setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_low_cc_c_tbl	Top address of the address array of C suppre Low-CC-C parameter
@param[out]	size				Size of the address array of C suppre Low-CC-C parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_low_cc_c_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprLowCcCTbl** const cspr_low_cc_c_tbl, ULONG* const size );

/**
Get CSPR Edge setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_edge_tbl		Top address of the address array of C suppre Edge parameter
@param[out]	size				Size of the address array of C suppre Edge parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_edge_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprEdgeTbl** const cspr_edge_tbl, ULONG* const size );

/**
Get CSPR Edge setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	cspr_edge_tbl	Top address of the address array of C suppre Edge parameter
@param[out]	size			Size of the address array of C suppre Edge parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_edge_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprEdgeTbl** const cspr_edge_tbl, ULONG* const size );

/**
Get CSPR Hue Specified setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_hue_tbl		Top address of the address array of C suppre Hue Specified parameter
@param[out]	size				Size of the address array of C suppre Hue Specified parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_hue_spec_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprHueTbl** const cspr_hue_tbl, ULONG* const size );

/**
Get CSPR Hue Specified setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	cspr_hue_tbl	Top address of the address array of C suppre Hue Specified parameter
@param[out]	size			Size of the address array of C suppre Hue Specified parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_hue_spec_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrCsprHueTbl** const cspr_hue_tbl, ULONG* const size );

/**
Get CSPR sprs setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_sprs_cc_tbl	Top address of the address array of C suppre sprs CC parameter
@param[out]	size				Size of the address array of C suppre sprs CC parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_sprs_cc_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrSprsCcTbl** const cspr_sprs_cc_tbl, ULONG* const size );

/**
Get CSPR sprs setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_sprs_cc_tbl	Top address of the address array of C suppre sprs CC parameter
@param[out]	size				Size of the address array of C suppre sprs CC parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_sprs_cc_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrSprsCcTbl** const cspr_sprs_cc_tbl, ULONG* const size );

/**
Get CSPR sprd setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_sprd_cc_tbl	Top address of the address array of C suppre sprd CC parameter
@param[out]	size				Size of the address array of C suppre sprd CC parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_ofl_cspr_sprd_cc_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrSprdCcTbl** const cspr_sprd_cc_tbl, ULONG* const size );

/**
Get CSPR sprd setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	cspr_sprd_cc_tbl	Top address of the address array of C suppre sprd CC parameter
@param[out]	size				Size of the address array of C suppre sprd CC parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_get_rdma_addr_otf_cspr_sprd_cc_table(ImCnrGet*self, UCHAR ch, const TImCnrRdmaAddrSprdCcTbl** const cspr_sprd_cc_tbl, ULONG* const size );

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
	TImCnrOflCtrl cnr_ctrl = {
		.mode = E_IM_CNR_YCC_MODE_YCC422,			// mode			SPR YCC mode	@@YUV_MODE

		.width = 4000,								// width		SPR valid data width	@@HSIZE
		.lines = 3000,								// lines		SPR valid data lines	@@VSIZE

		.rYWidth = 4000,							// rYWidth	Y width for read	@@RYDEF
		.rYAddr = 0x42000000,						// rYAddr		Y address for read	@@RYTA

		.rCWidth = 4000 /2,						// rCWidth	CbCr width for read	@@RCDEF
		.rCbAddr = 0x43000000,					// rCbAddr	Cb address for read	@@RCBTA
		.rCrAddr = 0x44000000,					// rCrAddr	Cr address for read	@@RCRTA

		.wYWidth = 4000,							// wYWidth	Y width for write	@@WYDEF
		.wYAddr = 0x45000000,						// wYAddr		Y address for write	@@WYTA

		.wCWidth = 4000 /2,						// wCWidth	CbCr width for write	@@WCDEF
		.wCbAddr = 0x46000000,					// wCbAddr	Cb address for write	@@WCBTA
		.wCrAddr = 0x47000000,					// wCrAddr	Cr address for write	@@WCRTA

		.workAddr = 0x48000000,					// workAddr	Address fir work area	@@TMPTA

		.divideTop = ImCnr_E_IM_CNR_VPROCESS_NORM,		// divideTop	Virtucal process devide	@@VDIVT
		.divideBot = ImCnr_E_IM_CNR_VPROCESS_NORM,		// divideBot	Virtucal process devide	@@VDIVB

		.pCallBack = NULL,							// pCallBack	callback function
		.userParam = 0,							// userParam	callback arg
	};
	TImCnrCtrlC cnr_ctrl_c = {
		.enable = ImCnr_E_IM_CNR_ONOFF_ENABLE,					// enable				CbCr SPR enable @@csprEn
		.gradationKeepEn = ImCnr_E_IM_CNR_ONOFF_ENABLE,			// enable				gradation keep enable @@cgdkEn
		.midFreqNr = {									// Middle range frequency Color NR parmeter
			.enable = ImCnr_E_IM_CNR_ONOFF_ENABLE,				// Middle CbCr SPR enable @@mcEn
			.hYThreshold = {								// Middle SPR Y threshold for horizontal	@@mcYthh
				0, 0, 0, 0										// register default. Need tuning.
			},
			.vYThreshold = {								// Middle SPR Y threshold for vertical		@@mcYthv
				0, 0, 0, 0										// register default. Need tuning.
			},
			.hCThreshold = {								// Middle SPR CbCr threshold for horizontal	@@mcCthh
				0, 0, 0, 0										// register default. Need tuning.
			},
			.vCThreshold = {								// Middle SPR CbCr threshold for vertical	@@mcCthv
				0, 0, 0, 0										// register default. Need tuning.
			},
			.yThresholdCor = 0,							// Middle SPR Y threshold coring	@@MCYDYMYCR
			.yThresholdGain = 0,							// register default. Need tuning.
			.yThresholdDymEn = ImCnr_E_IM_CNR_ONOFF_DISABLE,	// Middle Y threshold dynamic setting enable @@mcYdym
			.yThresholdSclEn = ImCnr_E_IM_CNR_ONOFF_DISABLE,	// Middle Y threshold scale enable @@mcYscl
			.cYThresholdSclEn = ImCnr_E_IM_CNR_ONOFF_DISABLE,	// Middle CbCr threshold Y scale enable @@mcSscl
			.cThresholdSclEn = ImCnr_E_IM_CNR_ONOFF_DISABLE,	// Middle CbCr threshold scale enable @@mcCscl
		},
		.lowFreqNr = {									// Low range frequency Color NR parmeters
			.enable = ImCnr_E_IM_CNR_ONOFF_ENABLE,					// Low CbCr SPR enable @@lcEn
			.hYThreshold = {								// Low SPR Y threshold for horizontal		@@lcYthh
				0, 0, 0, 0										// register default. Need tuning.
			},
			.vYThreshold = {								// Low SPR Y threshold for vertical			@@lcYthv
				0, 0, 0, 0										// register default. Need tuning.
			},
			.hCThreshold = {								// Low SPR CbCr threshold for horizontal	@@lcCthh
				0, 0, 0, 0										// register default. Need tuning.
			},
			.vCThreshold = {								// Low SPR CbCr threshold for vertical		@@lcCthv
				0, 0, 0, 0										// register default. Need tuning.
			},
			.yThresholdCor = 0,							// Low SPR Y threshold coring	@@LCYDYMYCR
			.yThresholdGain = 0,							// register default. Need tuning.
			.yThresholdDymEn = ImCnr_E_IM_CNR_ONOFF_DISABLE,	// Low Y threshold dynamic setting enable @@lcYdym
			.yThresholdSclEn = ImCnr_E_IM_CNR_ONOFF_DISABLE,	// Low Y threshold scale enable @@lcYscl
			.cYThresholdSclEn = ImCnr_E_IM_CNR_ONOFF_DISABLE,	// Low CbCr threshold Y scale enable @@lcSscl
			.cThresholdSclEn = ImCnr_E_IM_CNR_ONOFF_DISABLE,	// Low CbCr threshold scale enable @@lcCscl
		},
	};
	TImCnrOflCtrlY cnr_ctrl_y = {
		.enable = ImCnr_E_IM_CNR_ONOFF_ENABLE,					// enable				Y SPR enable @@ysprEn
		.thresholdType = ImCnr_E_IM_CNR_THRES_REGISTER,			// thresholdType		threshold type for Y	@@ysprMode YSPRMD
		.level = ImCnr_E_IM_CNR_LEVEL_LOW,						// level				filter level		@@ysprMode YSPRFE
		.hYThreshold = 0,									// hYThreshold		SPR Y threshold for horizontal		@@YSPRFXEYH
		.vYThreshold = 0,									// vYThreshold		SPR Y threshold for vertical		@@YSPRFXEYV
		.hCThreshold = 0,									// hCThreshold		SPR CbCr threshold for horizontal	@@YSPRFXECH
		.vCThreshold = 0,									// vCThreshold		SPR CbCr threshold for vertical		@@YSPRFXECV
		.alphaBlendRatio = 0,								// alphaBlendRatio	Alpha blend ratio			@@ysprAlpbd
	};



	im_ercd = im_cnr_ofl_open(im_cnr_new(), 0, 100 );	// wai_sem timeout 100 ticks
	if( im_ercd != D_DDIM_OK ) {
		return im_ercd;
	}

	// don't forget im_cnr_ofl_close() after this line

	while( 1 ) {
		im_ercd = im_cnr_init_ofl_ctrl(im_cnr_init_new(), 0, &cnr_ctrl );
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

		im_ercd = im_cnr_ofl_start_sync( 0, 1000 );	// wait timeout 1000 ticks
		if( im_ercd != D_DDIM_OK ) {
			break;
		}

		break;
	}

	im_ercd2 = im_cnr_ofl_stop(im_cnr_new(), 0 );
	if( im_ercd2 != D_DDIM_OK ) {
		im_ercd = im_ercd2;
	}

	if( im_ercd == D_DDIM_OK ) {
		im_ercd2 = im_cnr_ofl_close(im_cnr_new(), 0 );
		if( im_ercd2 != D_DDIM_OK ) {
			im_ercd = im_ercd2;
		}
	}
	else {
		(VOID)im_cnr_ofl_close(im_cnr_new(), 0 );
	}

	return im_ercd;
}
@endcode
@}*/
