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

#ifndef _IM_CNR_AXI_H_
#define _IM_CNR_AXI_H_

#include <klib.h>
#include "driver_common.h"
#include "ddim_typedef.h"
// get register value for RDMA
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"
#include "_jdscnr_otf_reg_rw.h"
#include "imcnr.h"

#define IM_TYPE_CNR_AXI		(im_cnr_axi_get_type())
#define IM_CNR_AXI(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImCnrAxi))
#define IM_IS_CNR_AXI(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_CNR_AXI))

typedef struct 				_ImCnrAxi ImCnrAxi;
typedef struct 				_ImCnrAxiPrivate ImCnrAxiPrivate;

struct _ImCnrAxi {
	KObject parent;
};

KConstType 		    im_cnr_axi_get_type(void);
ImCnrAxi*		        im_cnr_axi_new(void);

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------- driver section ----------------------------
/**
Suppre Control set AXI bus I/F Control for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	axi_ctrl	AXI bus I/F control parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_axi_ofl_ctrl_axi(ImCnrAxi*self, UCHAR ch, const TImCnrOflAxi* const axi_ctrl );

/**
Suppre Control set AXI bus I/F Control for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	axi_ctrl	AXI bus I/F control parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_axi_otf_ctrl_axi(ImCnrAxi*self, UCHAR ch, const TImCnrOtfAxi* const axi_ctrl );

/**
Get AXI bus I/F Status for Off Line
@param [in]	ch				channel[0 - 1]
@param[out]	sts	AXI bus I/F status parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_axi_ofl_get_axi_status(ImCnrAxi*self, UCHAR ch, TImCnrOflAxiStatus* const sts );

/**
Get AXI bus I/F Status for On The Fly
@param [in]	ch				channel[0 - 1]
@param[out]	sts	AXI bus I/F status parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_axi_otf_get_axi_status(ImCnrAxi*self, UCHAR ch, TImCnrOtfAxiStatus* const sts );

/**
Set SPR setting for CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_ctrl_c	CbCr suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the Suppre for CbCr is set.
*/
INT32 im_cnr_axi_ofl_ctrl_c(ImCnrAxi*self, UCHAR ch, const TImCnrCtrlC* const cnr_ctrl_c );

/**
Set SPR setting for CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_ctrl_c	CbCr suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the Suppre for CbCr is set.
*/
INT32 im_cnr_axi_otf_ctrl_c(ImCnrAxi*self, UCHAR ch, const TImCnrCtrlC* const cnr_ctrl_c );

/**
Set SPR setting for Y for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_ctrl_y	Y suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the Suppre for Y is set.
*/
INT32 im_cnr_axi_ofl_ctrl_y(ImCnrAxi*self, UCHAR ch, const TImCnrOflCtrlY* const cnr_ctrl_y );

/**
Set CbCr setting of source for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	sprs_ctrl	Source CbCr adjustment parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the source CbCr Adjustment is set.
*/
INT32 im_cnr_axi_ofl_ctrl_sprs_cc(ImCnrAxi*self, UCHAR ch, const TImCnrCtrlCcSrcDst* const sprs_ctrl );

/**
Set CbCr setting of source for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	sprs_ctrl	Source CbCr adjustment parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the source CbCr Adjustment is set.
*/
INT32 im_cnr_axi_otf_ctrl_sprs_cc(ImCnrAxi*self, UCHAR ch, const TImCnrCtrlCcSrcDst* const sprs_ctrl );

/**
Set CbCr setting of destination for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	sprd_ctrl	Destination CbCr adjustment parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the destination CbCr Adjustment is set.
*/
INT32 im_cnr_axi_ofl_ctrl_sprd_cc(ImCnrAxi*self, UCHAR ch, const TImCnrCtrlCcSrcDst* const sprd_ctrl );

/**
Set CbCr setting of destination for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	sprd_ctrl	Destination CbCr adjustment parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the destination CbCr Adjustment is set.
*/
INT32 im_cnr_axi_otf_ctrl_sprd_cc(ImCnrAxi*self, UCHAR ch, const TImCnrCtrlCcSrcDst* const sprd_ctrl );

#endif// _IM_CNR_AXI_H_
