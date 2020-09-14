/*
 * imr2yutility3.h
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

#ifndef __IM_R2Y_UTILITY3_H__
#define __IM_R2Y_UTILITY3_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_UTILITY3		(im_r2y_utility3_get_type())
#define IM_R2Y_UTILITY3(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yUtility3))
#define IM_IS_R2Y_UTILITY3(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_UTILITY3))

typedef struct 				_ImR2yUtility3 ImR2yUtility3;
typedef struct 				_ImR2yUtility3Private ImR2yUtility3Private;

struct _ImR2yUtility3 {
	KObject parent;
};

KConstType 		    		im_r2y_utility3_get_type(void);
ImR2yUtility3*		        im_r2y_utility3_new(void);

/**
Get the top address of the address array of Gamma Table(Diff).
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		tbl_index				: Selection of setting table<br>
										  0 : RGB common / 1 : R / 2 : G / 3 : B / 4 : Yb
@param[out]		addr					: Top address of the address array of Gamma Table(Diff).
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_utility3_get_rdma_addr_gmdf_table(ImR2yUtility3 *self, kuint16 pipeNo, kuint16 tbl_index, const RdmaGmdfTblAddr** addr );


#endif /* __IM_R2Y_UTILITY3_H__ */
