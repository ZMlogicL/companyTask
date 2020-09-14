/*
 * imr2yutility4.h
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

#ifndef __IM_R2Y_UTILITY4_H__
#define __IM_R2Y_UTILITY4_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_UTILITY4			(im_r2y_utility4_get_type())
#define IM_R2Y_UTILITY4(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yUtility4))
#define IM_IS_R2Y_UTILITY4(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_UTILITY4))

typedef struct 				_ImR2yUtility4 ImR2yUtility4;
typedef struct 				_ImR2yUtility4Private ImR2yUtility4Private;

struct _ImR2yUtility4 {
	KObject parent;
};

KConstType 		    		im_r2y_utility4_get_type(void);
ImR2yUtility4*		        im_r2y_utility4_new(void);


#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
INT32 im_r2y_utility4_get_rdmaaddr_gmdf_table(ImR2yUtility4 *self, kuint16 pipeNo, const RdmaGmdfTblAddr** addr );

/**
Get the top address of the address array of Gamma Table(Full).
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		tbl_index				: Selection of table<br>
										  0 : RGB common / 1 : R / 2 : G / 3 : B / 4 : Yb
@param[out]		addr					: Top address of the address array of Gamma Table(Full).
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility4_get_rdma_addr_gmfl_table(ImR2yUtility4 *self, kuint16 pipeNo, kuint16 tbl_index, const RdmaGmflTblAddr** addr );

/**
Get the top address of the address array of (High/Medium/Low) edge emphasis scaling table.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		tbl_index				: Selection of table<br>
										  0 : High / 1 : Medium / 2 : Low
@param[out]		addr					: Top address of the address array of High edge emphasis scaling table.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility4_get_rdma_addr_egwscl_table(ImR2yUtility4 *self, kuint16 pipeNo, kuint16 tbl_index, const RdmaEgwsclTblAddr** addr );
#endif	// CO_DDIM_UTILITY_USE

#endif /* __IM_R2Y_UTILITY4_H__ */
