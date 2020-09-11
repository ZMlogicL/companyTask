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

#ifndef _IM_CNR_CSPR_H_
#define _IM_CNR_CSPR_H_

#include <klib.h>
#include "driver_common.h"
#include "ddim_typedef.h"
// get register value for RDMA
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"
#include "_jdscnr_otf_reg_rw.h"
#include "imcnr.h"

#define IM_TYPE_CNR_CSPR		(im_cnr_cspr_get_type())
#define IM_CNR_CSPR(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImCnrCspr))
#define IM_IS_CNR_CSPR(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_CNR_CSPR))

typedef struct 				_ImCnrCspr ImCnrCspr;
typedef struct 				_ImCnrCsprPrivate ImCnrCsprPrivate;

struct _ImCnrCspr {
	KObject parent;
};

KConstType 		    im_cnr_cspr_get_type(void);
ImCnrCspr*		        im_cnr_cspr_new(void);

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------- driver section ----------------------------
/**
Set SPR table for Y for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_yspr	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre YSPR table for Y is set.
*/
INT32 im_cnr_cspr_ofl_set_yspr_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_yspr );

/**
Set SPR Y table for Middle frequency CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_mid_y	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
INT32 im_cnr_cspr_ofl_set_cspr_mid_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_mid_y );

/**
Set SPR Y table for Middle frequency CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_mid_y	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
INT32 im_cnr_cspr_otf_set_cspr_mid_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_mid_y );

/**
Set SPR Y table for Middle frequency CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_mid_c	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
INT32 im_cnr_cspr_ofl_set_cspr_mid_cc_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_mid_c );

/**
Set SPR Y table for Middle frequency CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_mid_c	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
INT32 im_cnr_cspr_otf_set_cspr_mid_cc_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_mid_c );
/**
Set SPR CbCr table for Middle frequency CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_mid_c	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR CbCr table for CbCr is set.
*/
INT32 im_cnr_cspr_ofl_set_cspr_mid_cc_c_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_mid_c );

/**
Set SPR CbCr table for Middle frequency CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_mid_c	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR CbCr table for CbCr is set.
*/
INT32 im_cnr_cspr_otf_set_cspr_mid_cc_c_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_mid_c );

/**
Set SPR Y table for Low frequency CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_low_y	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
INT32 im_cnr_cspr_ofl_set_cspr_low_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_low_y );

/**
Set SPR Y table for Low frequency CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_low_y	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
INT32 im_cnr_cspr_otf_set_cspr_low_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_low_y );

/**
Set SPR Y table for Low frequency CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_low_c	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
INT32 im_cnr_cspr_ofl_set_cspr_low_cc_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_low_c );

/**
Set SPR Y table for Low frequency CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_low_c	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
INT32 im_cnr_cspr_otf_set_cspr_low_cc_y_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_low_c );

/**
Set SPR CbCr table for Low frequency CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_low_c	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR CbCr table for CbCr is set.
*/
INT32 im_cnr_cspr_ofl_set_cspr_low_cc_c_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_low_c );

/**
Set SPR CbCr table for Low frequency CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_low_c	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR CbCr table for CbCr is set.
*/
INT32 im_cnr_cspr_otf_set_cspr_low_cc_c_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_low_c );

/**
Set SPR Edge for CbcCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_edge	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Edge table for CbCr is set.
*/
INT32 im_cnr_cspr_ofl_set_cspr_edge_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_edge );

/**
Set SPR Edge for CbcCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnr_cspr_edge	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Edge table for CbCr is set.
*/
INT32 im_cnr_cspr_otf_set_cspr_edge_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_TABLE* const cnr_cspr_edge );

/**
Set SPR Hue specified for CbcCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	spr_cspr_hue	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Hue specified table for CbCr is set.
*/
INT32 im_cnr_cspr_ofl_set_cspr_hue_specified_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_HUE_SPEC_TABLE* const spr_cspr_hue );

/**
Set SPR Hue specified for CbcCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	spr_cspr_fue	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Hue specified table for CbCr is set.
*/
INT32 im_cnr_cspr_otf_set_cspr_hue_specified_table(ImCnrCspr*self, UCHAR ch, const T_IM_CNR_HUE_SPEC_TABLE* const spr_cspr_fue );

#endif// _IM_CNR_CSPR_H_
