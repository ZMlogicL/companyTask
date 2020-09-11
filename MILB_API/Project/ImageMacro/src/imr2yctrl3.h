/*
 * imr2yctrl3.h
 *
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

#ifndef __IM_R2Y_CTRL3_H__
#define __IM_R2Y_CTRL3_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_CTRL3		(im_r2y_ctrl3_get_type())
#define IM_R2Y_CTRL3(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yCtrl3))
#define IM_IS_R2Y_CTRL3(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_CTRL3))

typedef struct 				_ImR2yCtrl3 ImR2yCtrl3;
typedef struct 				_ImR2yCtrl3Private ImR2yCtrl3Private;

struct _ImR2yCtrl3 {
	KObject parent;
};

KConstType 		    im_r2y_ctrl3_get_type(void);
ImR2yCtrl3*		        im_r2y_ctrl3_new(void);

INT32 im_r2y_ctrl3_copy_reg_to_sdram_ushort(ImR2yCtrl3 *self, USHORT* const sdram_addr, const volatile USHORT* const reg_addr, const UINT32 array_num );

/**
Map scale control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_mapscl			: pointer of Map scale control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl3_map_scl(ImR2yCtrl3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_MAPSCL* const r2y_ctrl_mapscl );

/**
Set Map scale table access enable
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		acc_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: D_IM_R2Y_WAIT_OFF : Turn off wait. / D_IM_R2Y_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl3_set_map_scl_tbl_access_enable(ImR2yCtrl3 *self, UCHAR pipe_no, UCHAR acc_enable, UCHAR wait_enable );

/**
Chroma referenced edge and texture adjustment control
@param[in]		pipe_no									: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_c_ref_edge_texture_adj_common	: pointer of Chroma referenced edge and texture adjustment control parameters.
@retval			D_DDIM_OK								: success.
@retval			D_IM_R2Y_PARAM_ERROR					: parameter error.
*/
INT32 im_r2y_ctrl3_cref_edge_texture_adj_common(ImR2yCtrl3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_C_REF_EDGE_TEXTURE_ADJ_COMMON* const r2y_ctrl_c_ref_edge_texture_adj_common );

/**
Chroma referenced edge adjustment control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_c_ref_edge_adj	: pointer of Chroma referenced edge adjustment control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl3_cref_edge_adj(ImR2yCtrl3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_C_REF_EDGE_ADJ* const r2y_ctrl_c_ref_edge_adj );

/**
Chroma referenced luminance blend control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_c_ref_yb_blend	: pointer of Chroma referenced edge adjustment control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl3_cref_yb_blend(ImR2yCtrl3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_C_REF_YB_BLEND* const r2y_ctrl_c_ref_yb_blend );

/**
Color Noise Reduction(LPF) control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_clpf			: pointer of Color Noise Reduction control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl3_color_nr(ImR2yCtrl3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_CLPF* const r2y_ctrl_clpf );

/**
Chroma suppress control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_cs				: pointer of Chroma suppress control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl3_chroma_suppress(ImR2yCtrl3 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_CS* const r2y_ctrl_cs );

/**
Set Tone control table
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		src_tbl					: Pointer of Table data (Type of USHORT, Maximum array number is D_IM_R2Y_TABLE_MAX_TONE)
@param[in]		write_ofs_num			: write offset num of table constituent(USHORT data num, must set multiple of 2).
@param[in]		array_num				: num of table constituent(USHORT data num, must set multiple of 2).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl3_set_tone_control_table(ImR2yCtrl3 *self, UCHAR pipe_no, const USHORT* const src_tbl, USHORT write_ofs_num, USHORT array_num );

/**
Get Tone control Table
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2).
@param[out]		dst_tbl					: Pointer of Table data (Type of USHORT, Maximum array number is D_IM_R2Y_TABLE_MAX_TONE)
@param[in]		read_ofs_num			: read offset num of table constituent(USHORT data num, must set multiple of 2).
@param[in]		array_num				: table size(USHORT data num, must set multiple of 2)
@retval			D_DDIM_OK				: success
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl3_get_tone_control_table(ImR2yCtrl3 *self, UCHAR pipe_no, USHORT* const dst_tbl, USHORT read_ofs_num, USHORT array_num );

/**
Get Luminance evaluation
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2).
@param[out]		dst_addr				: Luminance evaluation value return buffer address. Array number is D_IM_R2Y_TABLE_MAX_TCT.
@param[in]		array_num				: table size.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro is running. Can not get Luminance evaluation value.
*/
INT32 im_r2y_ctrl3_get_luminance_evaluation_before_tone(ImR2yCtrl3 *self, UCHAR pipe_no, UINT32* const dst_addr, USHORT array_num );

/**
Get BTC Histogram
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2).
@param[in]		data_type				: Data type(R/G/B/Y).
@param[out]		overflow_flg			: Histogram overflow flag before TC data.
@param[out]		dst_addr				: Histogram value return buffer address. Array number is D_IM_R2Y_TABLE_MAX_BTC_HISTOGRAM_Y/D_IM_R2Y_TABLE_MAX_BTC_HISTOGRAM_RGB.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro is running. Can not get histogram.
*/
INT32 im_r2y_ctrl3_get_histogram_before_tone(ImR2yCtrl3 *self, UCHAR pipe_no, E_R2Y_BTC_HIST_RGBTBL data_type, T_IM_R2Y_TCHS_FLG* const overflow_flg, USHORT* const dst_addr );

#endif /* __IM_R2Y_CTRL3_H__ */
