/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-8-5 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/


#ifndef  __IM_CNRFIVE_H__
#define __IM_CNRFIVE_H__


#include "driver_common.h"
#include "ddim_typedef.h"
// get register value for RDMA
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"
#include "_jdscnr_otf_reg_rw.h"
#include <glib-object.h>


G_BEGIN_DECLS


#define IM_TYPE_CNRFIVE							(im_cnrfive_get_type ())
#define IM_CNRFIVE(obj)								(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_CNRFIVE, ImCnrfive))
#define IM_CNRFIVE_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_CNRFIVE, ImCnrfiveClass))
#define IM_IS_CNRFIVE(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_CNRFIVE))
#define IM_IS_CNRFIVE_CLASS(klass)		    (G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_CNRFIVE))
#define IM_CNRFIVE_GET_CLASS(obj)			(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_CNRFIVE, ImCnrfiveClass))


struct 				   _ImCnrfive;
typedef struct _ImCnrfive 							ImCnrfive;
typedef struct _ImCnrfiveClass 					ImCnrfiveClass;
typedef struct _ImCnrfivePrivate 				ImCnrfivePrivate;

struct _ImCnrfive{
	GObject parent;
};

struct _ImCnrfiveClass{
	GObjectClass parentclass;
};

#ifdef __cplusplus
	extern "c1" {
#endif


GType 						im_cnrfive_get_type(void) G_GNUC_CONST;
ImCnrfive* 				im_cnrfive_new(void);

/**
Set CbCr setting of destination for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	sprdCtrl	Destination CbCr adjustment parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the destination CbCr Adjustment is set.
*/
extern	INT32 im_cnrfive_ofl_ctrl_sprd_cc(ImCnrfive *self, UCHAR ch, const ImCnrCtrlCcSrcDst* const sprdCtrl );

/**
Set CbCr setting of destination for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	sprdCtrl	Destination CbCr adjustment parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the destination CbCr Adjustment is set.
*/
extern	INT32 im_cnrfive_otf_ctrl_sprd_cc(ImCnrfive *self, UCHAR ch, const ImCnrCtrlCcSrcDst* const sprdCtrl );
/* @} */

#ifdef CO_DDIM_UTILITY_USE
/**
Set CSPR Low-CC-Y setting parameter information for C for Off Line
@param[in]	sprCsprLowCcY			C suppre Low-CC-Y parameter
@param[out]	rdmaCsprLowCcYTable	C suppre Low-CC-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_ofl_cspr_low_cc_y_table(ImCnrfive *self, const ImCnrTable* const sprCsprLowCcY,
		ImCnroneRdmaDataCsprLowCcYTbl* const rdmaCsprLowCcYTable );

/**
Set CSPR Low-CC-Y setting parameter information for C for On The Fly
@param[in]	sprCsprLowCcY			C suppre Low-CC-Y parameter
@param[out]	rdmaCsprLowCcYTable	C suppre Low-CC-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_otf_cspr_low_cc_y_table(ImCnrfive *self, const ImCnrTable* const sprCsprLowCcY,
		ImCnroneRdmaDataCsprLowCcYTbl* const rdmaCsprLowCcYTable );

/**
Set CSPR Low-CC-C setting parameter information for C for Off Line
@param[in]	sprCsprLowCcC			C suppre Low-CC-C parameter
@param[out]	rdmaCsprLowCcCTable	C suppre Low-CC-C parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_ofl_cspr_low_cc_c_table(ImCnrfive *self, const ImCnrTable* const sprCsprLowCcC,
		ImCnroneRdmaDataCsprLowCcCTbl* const rdmaCsprLowCcCTable );

/**
Set CSPR Low-CC-C setting parameter information for C for On The Fly
@param[in]	sprCsprLowCcC			C suppre Low-CC-C parameter
@param[out]	rdmaCsprLowCcCTable	C suppre Low-CC-C parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_otf_cspr_low_cc_c_table(ImCnrfive *self, const ImCnrTable* const sprCsprLowCcC,
		ImCnroneRdmaDataCsprLowCcCTbl* const rdmaCsprLowCcCTable );

/**
Set CSPR Edge setting parameter information for C for Off Line
@param[in]	sprCsprEdge			C suppre Edge parameter
@param[out]	rdmaCsprEdgeTable	C suppre Edge parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_ofl_cspr_edge_table(ImCnrfive *self, const ImCnrTable* const sprCsprEdge,
		ImCnroneRdmaDataCsprEdgeTbl* const rdmaCsprEdgeTable );

/**
Set CSPR Edge setting parameter information for C for On The Fly
@param[in]	sprCsprEdge			C suppre Edge parameter
@param[out]	rdmaCsprEdgeTable	C suppre Edge parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_otf_cspr_edge_table(ImCnrfive *self, const ImCnrTable* const sprCsprEdge,
		ImCnroneRdmaDataCsprEdgeTbl* const rdmaCsprEdgeTable );

/**
Set CSPR Hue Specified setting parameter information for C for Off Line
@param[in]	sprCsprHue			C suppre Hue Specified parameter
@param[out]	rdmaCsprHueTable		C suppre Hue Specified parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_ofl_cspr_hue_spec_table(ImCnrfive *self, const ImCnrHueSpecTable* const sprCsprHue,
		ImCnroneRdmaDataCsprHueTbl* const rdmaCsprHueTable );

/**
Set CSPR Hue Specified setting parameter information for C for On The Fly
@param[in]	sprCsprHue			C suppre Hue Specified parameter
@param[out]	rdmaCsprHueTable		C suppre Hue Specified parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_otf_cspr_hue_spec_table(ImCnrfive *self, const ImCnrHueSpecTable* const sprCsprHue,
		ImCnroneRdmaDataCsprHueTbl* const rdmaCsprHueTable );


/**
Set CSPR SPRS setting parameter information for C for Off Line
@param[in]	csprSprsCc			C suppre SPRS CC parameter
@param[out]	rdmaCsprSprsCc		C suppre SPRS CC parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_ofl_cspr_sprs_cc_table(ImCnrfive *self, const ImCnrCtrlCcSrcDst* const csprSprsCc,
		ImCnrRdmaDataSprsCcTbl* const rdmaCsprSprsCc );

/**
Set CSPR SPRS setting parameter information for C for On The Fly
@param[in]	csprSprsCc			C suppre SPRS CC parameter
@param[out]	rdmaCsprSprsCc		C suppre SPRS CC parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_otf_cspr_sprs_cc_table(ImCnrfive *self, const ImCnrCtrlCcSrcDst* const csprSprsCc,
		ImCnrRdmaDataSprsCcTbl* const rdmaCsprSprsCc );


/**
Set CSPR SPRD setting parameter information for C for Off Line
@param[in]	csprSprdCc			C suppre SPRD CC parameter
@param[out]	rdmaCsprSprdCc		C suppre SPRD CC parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_ofl_cspr_sprd_cc_table(ImCnrfive *self, const ImCnrCtrlCcSrcDst* const csprSprdCc,
		ImCnroneRdmaDataSprdCcTbl* const rdmaCsprSprdCc );

/**
Set CSPR SPRD setting parameter information for C for On The Fly
@param[in]	csprSprdCc			C suppre SPRD CC parameter
@param[out]	rdmaCsprSprdCc		C suppre SPRD CC parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_otf_cspr_sprd_cc_table(ImCnrfive *self, const ImCnrCtrlCcSrcDst* const csprSprdCc,
		ImCnroneRdmaDataSprdCcTbl* const rdmaCsprSprdCc );


/**
Set CSPR Low-Y setting parameter information for C for Off Line
@param[in]	sprCsprLowY			C suppre Low-Y parameter
@param[out]	rdmaCsprLowYTable	C suppre Low-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_ofl_cspr_low_y_table(ImCnrfive *self, const ImCnrTable* const sprCsprLowY,
		ImCnrRdmaDataCsprLowYTbl* const rdmaCsprLowYTable );

/**
Set CSPR Low-Y setting parameter information for C for On The Fly
@param[in]	sprCsprLowY			C suppre Low-Y parameter
@param[out]	rdmaCsprLowYTable	C suppre Low-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfive_set_rdmavalue_otf_cspr_low_y_table(ImCnrfive *self, const ImCnrTable* const sprCsprLowY,
		ImCnrRdmaDataCsprLowYTbl* const rdmaCsprLowYTable );


#endif



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
	ImCnrOflCtrl cnr_ctrl = {
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

		.divideTop = ImCnr_VPROCESS_NORM,		// divideTop	Virtucal process devide	@@VDIVT
		.divideBot = ImCnr_VPROCESS_NORM,		// divideBot	Virtucal process devide	@@VDIVB

		.pCallBack = NULL,							// pCallBack	callback function
		.userParam = 0,							// userParam	callback arg
	};
	ImCnrCtrlC cnr_ctrl_c = {
		.enable = ImCnr_ONOFF_ENABLE,					// enable				CbCr SPR enable @@CSPREN
		.gradationKeepEn = ImCnr_ONOFF_ENABLE,			// enable				gradation keep enable @@CGDKEN
		.midFreqNr = {									// Middle range frequency Color NR parmeter
			.enable = ImCnr_ONOFF_ENABLE,				// Middle CbCr SPR enable @@MCEN
			.hYThreshold = {								// Middle SPR Y threshold for horizontal	@@MCYTHH
				0, 0, 0, 0										// register default. Need tuning.
			},
			.vYThreshold = {								// Middle SPR Y threshold for vertical		@@MCYTHV
				0, 0, 0, 0										// register default. Need tuning.
			},
			.hCThreshold = {								// Middle SPR CbCr threshold for horizontal	@@MCCTHH
				0, 0, 0, 0										// register default. Need tuning.
			},
			.vCThreshold = {								// Middle SPR CbCr threshold for vertical	@@MCCTHV
				0, 0, 0, 0										// register default. Need tuning.
			},
			.yThresholdCor = 0,							// Middle SPR Y threshold coring	@@MCYDYMYCR
			.yThresholdGain = 0,							// register default. Need tuning.
			.yThresholdDymEn = ImCnr_ONOFF_DISABLE,	// Middle Y threshold dynamic setting enable @@MCYDYM
			.yThresholdSclEn = ImCnr_ONOFF_DISABLE,	// Middle Y threshold scale enable @@MCYSCL
			.cYThresholdSclEn = ImCnr_ONOFF_DISABLE,	// Middle CbCr threshold Y scale enable @@MCSSCL
			.cThresholdSclEn = ImCnr_ONOFF_DISABLE,	// Middle CbCr threshold scale enable @@MCCSCL
		},
		.lowFreqNr = {									// Low range frequency Color NR parmeters
			.enable = ImCnr_ONOFF_ENABLE,					// Low CbCr SPR enable @@LCEN
			.hYThreshold = {								// Low SPR Y threshold for horizontal		@@LCYTHH
				0, 0, 0, 0										// register default. Need tuning.
			},
			.vYThreshold = {								// Low SPR Y threshold for vertical			@@LCYTHV
				0, 0, 0, 0										// register default. Need tuning.
			},
			.hCThreshold = {								// Low SPR CbCr threshold for horizontal	@@LCCTHH
				0, 0, 0, 0										// register default. Need tuning.
			},
			.vCThreshold = {								// Low SPR CbCr threshold for vertical		@@LCCTHV
				0, 0, 0, 0										// register default. Need tuning.
			},
			.yThresholdCor = 0,							// Low SPR Y threshold coring	@@LCYDYMYCR
			.yThresholdGain = 0,							// register default. Need tuning.
			.yThresholdDymEn = ImCnr_ONOFF_DISABLE,	// Low Y threshold dynamic setting enable @@LCYDYM
			.yThresholdSclEn = ImCnr_ONOFF_DISABLE,	// Low Y threshold scale enable @@LCYSCL
			.cYThresholdSclEn = ImCnr_ONOFF_DISABLE,	// Low CbCr threshold Y scale enable @@LCSSCL
			.cThresholdSclEn = ImCnr_ONOFF_DISABLE,	// Low CbCr threshold scale enable @@LCCSCL
		},
	};
	ImCnrOflCtrlY cnr_ctrl_y = {
		.enable = ImCnr_ONOFF_ENABLE,					// enable				Y SPR enable @@YSPREN
		.thresholdType = ImCnr_THRES_REGISTER,			// thresholdType		threshold type for Y	@@YSPRMODE YSPRMD
		.level = ImCnr_LEVEL_LOW,						// level				filter level		@@YSPRMODE YSPRFE
		.hYThreshold = 0,									// hYThreshold		SPR Y threshold for horizontal		@@YSPRFXEYH
		.vYThreshold = 0,									// vYThreshold		SPR Y threshold for vertical		@@YSPRFXEYV
		.hCThreshold = 0,									// hCThreshold		SPR CbCr threshold for horizontal	@@YSPRFXECH
		.vCThreshold = 0,									// vCThreshold		SPR CbCr threshold for vertical		@@YSPRFXECV
		.alphaBlendRatio = 0,								// alphaBlendRatio	Alpha BLEND ratio			@@YSPRALPBD
	};



	im_ercd = im_cnrone_ofl_open( 0, 100 );	// wai_sem timeout 100 ticks
	if( im_ercd != D_DDIM_OK ) {
		return im_ercd;
	}

	// don't forget im_cnr_ofl_close() after this line

	while( 1 ) {
		im_ercd = im_cnrone_ofl_ctrl( 0, &cnr_ctrl );
		if( im_ercd != D_DDIM_OK ) {
			break;
		}

		im_ercd = im_cnrone_ofl_ctrl_c( 0, &cnr_ctrl_c );
		if( im_ercd != D_DDIM_OK ) {
			break;
		}

		im_ercd = im_cnrone_ofl_ctrl_y( 0, &cnr_ctrl_y );
		if( im_ercd != D_DDIM_OK ) {
			break;
		}

		im_ercd = im_cnrfour_ofl_start_sync( 0, 1000 );	// wait timeout 1000 ticks
		if( im_ercd != D_DDIM_OK ) {
			break;
		}

		break;
	}

	im_ercd2 = im_cnr_ofl_stop( 0 );
	if( im_ercd2 != D_DDIM_OK ) {
		im_ercd = im_ercd2;
	}

	if( im_ercd == D_DDIM_OK ) {
		im_ercd2 = im_cnr_ofl_close( 0 );
		if( im_ercd2 != D_DDIM_OK ) {
			im_ercd = im_ercd2;
		}
	}
	else {
		(VOID)im_cnr_ofl_close( 0 );
	}

	return im_ercd;
}
@endcode
@}*/


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_CNRFIVE_H__ */


