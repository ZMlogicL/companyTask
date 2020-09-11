/*
 * imr2yset.h
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
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

#ifndef __IM_R2Y_SET_H__
#define __IM_R2Y_SET_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_SET		(im_r2y_set_get_type())
#define IM_R2Y_SET(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2ySet))
#define IM_IS_R2Y_SET(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_SET))

typedef struct 				_ImR2ySet ImR2ySet;
typedef struct 				_ImR2ySetPrivate ImR2ySetPrivate;

struct _ImR2ySet {
	KObject parent;
};

KConstType 		    im_r2y_set_get_type(void);
ImR2ySet*		        im_r2y_set_new(void);

/**
Set Gamma Table
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		tbl_index				: Selection of setting table<br>
										  0 : RGB common / 1 : R / 2 : G / 3 : B / 4 : Yb
@param[in]		src_full_tbl			: Pointer of diff Table data array (Type of USHORT, array number is D_IM_R2Y_TABLE_MAX_GAMMA)
@param[in]		src_diff_tbl			: Pointer of full Table data array (Type of ULLONG, array number is D_IM_R2Y_TABLE_MAX_GAMMA)
@retval			D_DDIM_OK				: success
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro is running. Do not update Gamma table.
*/
INT32 im_r2y_set_gamma_table(ImR2ySet *self, UCHAR pipe_no, UCHAR tbl_index, const USHORT* const src_full_tbl, const ULLONG* const src_diff_tbl );

/**
Set High Edge enhancement scaling Table
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		src_tbl					: Pointer of Table data (Type of USHORT, Maximum array number is D_IM_R2Y_TABLE_MAX_EDGE_SCALE_HI)
@param[in]		write_ofs_num			: write offset num of table constituent(USHORT data num, must set multiple of 2).
@param[in]		array_num				: num of table constituent(USHORT data num, must set multiple of 2).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro is running. Do not update High Edge enhancement table.
*/
INT32 im_r2y_set_high_edge_scale_table(ImR2ySet *self, UCHAR pipe_no, const UCHAR* const src_tbl, USHORT write_ofs_num, USHORT array_num );

/**
Set High Edge enhancement stepping Table
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		src_tbl					: Pointer of Table data (Type of USHORT, Maximum array number is D_IM_R2Y_TABLE_MAX_EDGE_TC_HI)
@param[in]		write_ofs_num			: write offset num of table constituent(USHORT data num, must set multiple of 2).
@param[in]		array_num				: num of table constituent(USHORT data num, must set multiple of 2).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter errore.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro is running. Do not update High Edge enhancement table.
*/
INT32 im_r2y_set_high_edge_step_table(ImR2ySet *self, UCHAR pipe_no, const USHORT* const src_tbl, USHORT write_ofs_num, USHORT array_num );

/**
Set Medium Edge enhancement scaling Table
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		src_tbl					: Pointer of Table data (Type of USHORT, Maximum array number is D_IM_R2Y_TABLE_MAX_EDGE_SCALE_HI)
@param[in]		write_ofs_num			: write offset num of table constituent(USHORT data num, must set multiple of 2).
@param[in]		array_num				: num of table constituent(USHORT data num, must set multiple of 2).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro is running. Do not update Medium Edge enhancement table.
*/
INT32 im_r2y_set_medium_edge_scale_table(ImR2ySet *self, UCHAR pipe_no, const UCHAR* const src_tbl, USHORT write_ofs_num, USHORT array_num );

/**
Set Medium Edge enhancement stepping Table
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		src_tbl					: Pointer of Table data (Type of USHORT, Maximum array number is D_IM_R2Y_TABLE_MAX_EDGE_TC_HI)
@param[in]		write_ofs_num			: write offset num of table constituent(USHORT data num, must set multiple of 2).
@param[in]		array_num				: num of table constituent(USHORT data num, must set multiple of 2).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter errore.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro is running. Do not update Medium Edge enhancement table.
*/
INT32 im_r2y_set_medium_edge_step_table(ImR2ySet *self, UCHAR pipe_no, const USHORT* const src_tbl, USHORT write_ofs_num, USHORT array_num );

/**
Set Low Edge enhancement scaling Table
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		src_tbl					: Pointer of Table data (Type of USHORT, Maximum array number is D_IM_R2Y_TABLE_MAX_EDGE_SCALE_LO)
@param[in]		write_ofs_num			: write offset num of table constituent(USHORT data num, must set multiple of 2).
@param[in]		array_num				: num of table constituent(USHORT data num, must set multiple of 2).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter errore.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro is running. Do not update Low Edge enhancement table.
*/
INT32 im_r2y_set_low_edge_scale_table(ImR2ySet *self, UCHAR pipe_no, const UCHAR* const src_tbl, USHORT write_ofs_num, USHORT array_num );

/**
Set Low Edge enhancement stepping Table
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		src_tbl					: Pointer of Table data (Type of USHORT, Maximum array number is D_IM_R2Y_TABLE_MAX_EDGE_TC_LO)
@param[in]		write_ofs_num			: write offset num of table constituent(USHORT data num, must set multiple of 2).
@param[in]		array_num				: num of table constituent(USHORT data num, must set multiple of 2).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro is running. Do not update Low Edge enhancement table.
*/
INT32 im_r2y_set_low_edge_step_table(ImR2ySet *self, UCHAR pipe_no, const USHORT* const src_tbl, USHORT write_ofs_num, USHORT array_num );

/**
Set Map Scale Table
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		src_tbl					: Pointer of Table data (Type of USHORT, Maximum array number is D_IM_R2Y_TABLE_MAX_MAPSCL)
@param[in]		write_ofs_num			: write offset num of table constituent(USHORT data num, must set multiple of 2).
@param[in]		array_num				: num of table constituent(USHORT data num, must set multiple of 2).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro is running. Do not update Low Edge enhancement table.
*/
INT32 im_r2y_set_map_scl_table(ImR2ySet *self, UCHAR pipe_no, const USHORT* const src_tbl, USHORT write_ofs_num, USHORT array_num );

#endif /* __IM_R2Y_SET_H__ */
