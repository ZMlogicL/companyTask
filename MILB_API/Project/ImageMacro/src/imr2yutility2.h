/*
 * imr2yutility2.h
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

#ifndef __IM_R2Y_UTILITY2_H__
#define __IM_R2Y_UTILITY2_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_UTILITY2		(im_r2y_utility2_get_type())
#define IM_R2Y_UTILITY2(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yUtility2))
#define IM_IS_R2Y_UTILITY2(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_UTILITY2))

typedef struct 				_ImR2yUtility2 ImR2yUtility2;
typedef struct 				_ImR2yUtility2Private ImR2yUtility2Private;

struct _ImR2yUtility2 {
	KObject parent;
};

KConstType 		    		im_r2y_utility2_get_type(void);
ImR2yUtility2*		        im_r2y_utility2_new(void);

#ifdef CO_DDIM_UTILITY_USE

/**
Get the top address of the address array of EENR control.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of EENR control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_eenr_cntl(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_EENR_ADDR** addr );

/**
Get the top address of the address array of High frequency edge enhancement control.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of High frequency edge enhancement control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_eghw_cntl(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_EGHW_ADDR** addr );

/**
Get the top address of the address array of Medium frequency edge enhancement control.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Medium frequency edge enhancement control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_egmw_cntl(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_EGMW_ADDR** addr );

/**
Get the top address of the address array of Low frequency edge enhancement control.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Low frequency edge enhancement control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_eglw_cntl(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_EGLW_ADDR** addr );

/**
Get the top address of the address array of Edge dot noise correction control.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Edge dot noise correction control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_egdt_cntl(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_EGDT_ADDR** addr );

/**
Get the top address of the address array of Edge emphasis blend control.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Edge emphasis blend control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_egcmp_cntl(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_EGCMP_ADDR** addr );

/**
Get the top address of the address array of Chroma referenced edge and texture adjustment control.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Chroma referenced edge and texture adjustment control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_crv_cntl(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_CRV_ADDR** addr );

/**
Get the top address of the address array of Chroma referenced edge adjustment control.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Chroma referenced edge adjustment control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_egcrv_cntl(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_EGCRV_ADDR** addr );

/**
Get the top address of the address array of Chroma referenced luminance blend control.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Chroma referenced luminance blend control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_ybcrv_cntl(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_YBCRV_ADDR** addr );

/**
Get the top address of the address array of Color Noise Reduction(LPF) control.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Color Noise Reduction(LPF) control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_clpf_cntl(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_CLPF_ADDR** addr );

/**
Get the top address of the address array of Chroma suppress control.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Chroma suppress control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_csp_cntl(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_CSP_ADDR** addr );

/**
Get the top address of the address array of Tone control table.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Tone control table.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_tone_table(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_TONE_TBL_ADDR** addr );

/**
Get the top address of the address array of (High/Medium/Low) edge emphasis stepping table.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		tbl_index				: Selection of table<br>
										  0 : High / 1 : Medium / 2 : Low
@param[out]		addr					: Top address of the address array of High edge emphasis stepping table.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_egwton_table(ImR2yUtility2 *self, UCHAR pipe_no, UCHAR tbl_index, const T_IM_R2Y_CTRL_RDMA_EGWTON_TBL_ADDR** addr );

/**
Get the top address of the address array of Map Scale table.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		addr					: Top address of the address array of Map Scale table.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility2_get_rdma_addr_egmpscl_table(ImR2yUtility2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_RDMA_EGMPSCL_TBL_ADDR** addr );

#endif	// CO_DDIM_UTILITY_USE

#endif /* __IM_R2Y_UTILITY2_H__ */
