/*
 * imr2yutility.h
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
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

#ifndef __IM_R2Y_UTILITY_H__
#define __IM_R2Y_UTILITY_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_UTILITY			(im_r2y_utility_get_type())
#define IM_R2Y_UTILITY(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yUtility))
#define IM_IS_R2Y_UTILITY(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_UTILITY))

typedef struct 				_ImR2yUtility ImR2yUtility;
typedef struct 				_ImR2yUtilityPrivate ImR2yUtilityPrivate;

struct _ImR2yUtility {
	KObject parent;
};

KConstType 		    		im_r2y_utility_get_type(void);
ImR2yUtility*		        im_r2y_utility_new(void);

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
/**
Get the top address of the address array of Post-resize edge enhancement0 control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Post-resize edge enhancement0 control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_ee0_cntl(ImR2yUtility *self, kuint16 pipeNo, const CtrlRdmaEe0Addr** addr );

/**
Get the top address of the address array of Post-resize edge enhancement1 control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Post-resize edge enhancement1 control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_ee1_cntl(ImR2yUtility *self, kuint16 pipeNo, const CtrlRdmaEe1Addr** addr );

/**
Get the top address of the address array of Deknee table.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		tbl_type				: Table type (R, G, B).
@param[out]		addr					: Top address of the address array of Deknee table.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_deknee_table(ImR2yUtility *self, kuint16 pipeNo, ER2yDknRgbtbl tbl_type, const RdmaDekneeTblAddr** addr );

/**
Get the top address of the address array of Offset control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Offset control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_offset_cntl(ImR2yUtility *self, kuint16 pipeNo, const T_IM_R2Y_CTRL_RDMA_OFST_ADDR** addr );

/**
Get the top address of the address array of WB clip control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of WB clip control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_wb_clip_cntl(ImR2yUtility *self, kuint16 pipeNo, const RdmaWbClipAddr** addr );

/**
Get the top address of the address array of CC0 matrix control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of CC0 matrix control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_cc0_matrix_cntl(ImR2yUtility *self, kuint16 pipeNo, const CtrlRdmaCc0Addr** addr );

/**
Get the top address of the address array of CC0 matrix coefficient control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of CC0 matrix coefficient control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_cc0_matrix_coefficient_cntl(ImR2yUtility *self, kuint16 pipeNo, const RdmaCc0CoefAddr** addr );

/**
Get the top address of the address array of Multi Axis control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Multi Axis control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_multi_axis_cntl(ImR2yUtility *self, kuint16 pipeNo, const CtrlRdmaMcycAddr** addr );

/**
Get the top address of the address array of RGB Offset before TC control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of RGB Offset before TC control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_before_tone_offset_cntl(ImR2yUtility *self, kuint16 pipeNo, const RdmaBtcTcofAddr** addr );

/**
Get the top address of the address array of Luminance Evaluation before TC control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Luminance Evaluation before TC control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_before_tone_tct_cntl(ImR2yUtility *self, kuint16 pipeNo, const RdmaBtcTctAddr** addr );

/**
Get the top address of the address array of Histogram before TC control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Histogram before TC control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_before_tone_tchs_cntl(ImR2yUtility *self, kuint16 pipeNo, const RdmaBtcTchsAddr** addr );

/**
Get the top address of the address array of Tone control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Tone control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_tone_cntl(ImR2yUtility *self, kuint16 pipeNo, const CtrlRdmaToneAddr** addr );

/**
Get the top address of the address array of Gamma control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Gamma control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_gamma_cntl(ImR2yUtility *self, kuint16 pipeNo, const CtrlRdmaGammaAddr** addr );

/**
Get the top address of the address array of CC1 matrix control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of CC1 matrix control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_cc1_matrix_cntl(ImR2yUtility *self, kuint16 pipeNo, const CtrlRdmaCc1Addr** addr );

/**
Get the top address of the address array of CC1 matrix coefficient control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of CC1 matrix coefficient control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_cc1_matrix_coefficient_cntl(ImR2yUtility *self, kuint16 pipeNo, const RdmaCc1CoefAddr** addr );

/**
Get the top address of the address array of YCC control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of YCC control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_ycc_cntl(ImR2yUtility *self, kuint16 pipeNo, const CtrlRdmaYccAddr** addr );

/**
Get the top address of the address array of YNR control.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of YNR control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility_get_rdma_addr_ynr_cntl(ImR2yUtility *self, kuint16 pipeNo, const CtrlRdmaYnrAddr** addr );

#endif	// CO_DDIM_UTILITY_USE

#endif /* __IM_R2Y_UTILITY_H__ */
