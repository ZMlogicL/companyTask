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


#include "driver_common.h"
#include "ddim_typedef.h"
// get register value for RDMA
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"
#include "_jdscnr_otf_reg_rw.h"
#include <glib-object.h>


#ifndef  __IM_CNRTWO_H__
#define __IM_CNRTWO_H__


G_BEGIN_DECLS


#define IM_TYPE_CNRTWO							(im_cnrtwo_get_type ())
#define IM_CNRTWO(obj)							(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_CNRTWO, ImCnrtwo))
#define IM_CNRTWO_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_CNRTWO, ImCnrtwoClass))
#define IM_IS_CNRTWO(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_CNRTWO))
#define IM_IS_CNRTWO_CLASS(klass)		    (G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_CNRTWO))
#define IM_CNRTWO_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_CNRTWO, ImCnrtwoClass))


typedef struct _ImCnrtwo 							ImCnrtwo;
typedef struct _ImCnrtwoClass 					ImCnrtwoClass;
typedef struct _ImCnrtwoPrivate 				ImCnrtwoPrivate;

struct _ImCnrtwo{
	GObject parent;
};

struct _ImCnrtwoClass{
	GObjectClass parentclass;
};


#ifdef __cplusplus
	extern "c1" {
#endif


GType 					im_cnrtwo_get_type(void) G_GNUC_CONST;
ImCnrtwo* 			im_cnrtwo_new(void);

/**
Set SPR Y table for Middle frequency CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprMidY	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
extern	INT32 im_cnrtwo_otf_set_cspr_mid_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprMidY );

/**
Set SPR Y table for Middle frequency CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprMidC	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
extern	INT32 im_cnrtwo_ofl_set_cspr_mid_cc_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprMidC );

/**
Set SPR Y table for Middle frequency CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprMidC	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
extern	INT32 im_cnrtwo_otf_set_cspr_mid_cc_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprMidC );

/**
Set SPR CbCr table for Middle frequency CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprMidC	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR CbCr table for CbCr is set.
*/
extern	INT32 im_cnrtwo_ofl_set_cspr_mid_cc_c_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprMidC );

/**
Set SPR CbCr table for Middle frequency CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprMidC	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR CbCr table for CbCr is set.
*/
extern	INT32 im_cnrtwo_otf_set_cspr_mid_cc_c_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprMidC );

/**
Set SPR Y table for Low frequency CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprLowY	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
extern	INT32 im_cnrtwo_ofl_set_cspr_low_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprLowY );

/**
Set SPR Y table for Low frequency CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprLowY	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
extern	INT32 im_cnrtwo_otf_set_cspr_low_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprLowY );

/**
Set SPR Y table for Low frequency CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprLowC	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
extern	INT32 im_cnrtwo_ofl_set_cspr_low_cc_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprLowC );

/**
Set SPR Y table for Low frequency CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprLowC	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
extern	INT32 im_cnrtwo_otf_set_cspr_low_cc_y_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprLowC );

/**
Set SPR CbCr table for Low frequency CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprLowC	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR CbCr table for CbCr is set.
*/
extern	INT32 im_cnrtwo_ofl_set_cspr_low_cc_c_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprLowC );

/**
Set SPR CbCr table for Low frequency CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprLowC	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR CbCr table for CbCr is set.
*/
extern	INT32 im_cnrtwo_otf_set_cspr_low_cc_c_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprLowC );

/**
Set SPR Edge for CbcCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprEdge	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Edge table for CbCr is set.
*/
extern	INT32 im_cnrtwo_ofl_set_cspr_edge_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprEdge );

/**
Set SPR Edge for CbcCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprEdge	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Edge table for CbCr is set.
*/
extern	INT32 im_cnrtwo_otf_set_cspr_edge_table(ImCnrtwo *self, UCHAR ch, const ImCnrTable* const cnrCsprEdge );

/**
Set SPR Hue specified for CbcCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	sprCsprHue	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Hue specified table for CbCr is set.
*/
extern	INT32 im_cnrtwo_ofl_set_cspr_hue_specified_table(ImCnrtwo *self, UCHAR ch,
		const ImCnrHueSpecTable* const sprCsprHue );

/**
Set SPR Hue specified for CbcCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	sprCsprFue	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Hue specified table for CbCr is set.
*/
extern	INT32 im_cnrtwo_otf_set_cspr_hue_specified_table(ImCnrtwo *self, UCHAR ch,
		const ImCnrHueSpecTable* const sprCsprFue );

/**
Set CbCr setting of source for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	sprsCtrl	Source CbCr adjustment parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the source CbCr Adjustment is set.
*/
extern	INT32 im_cnrtwo_ofl_ctrl_sprs_cc(ImCnrtwo *self, UCHAR ch, const ImCnrCtrlCcSrcDst* const sprsCtrl );

/**
Set CbCr setting of source for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	sprsCtrl	Source CbCr adjustment parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the source CbCr Adjustment is set.
*/
extern	INT32 im_cnrtwo_otf_ctrl_sprs_cc(ImCnrtwo *self, UCHAR ch, const ImCnrCtrlCcSrcDst* const sprsCtrl );


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_CNRTWO_H__ */
