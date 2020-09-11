/*
 *ctimdisp3.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-02
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP3_H__
#define __CT_IM_DISP3_H__

#include <klib.h>
//#include "im_disp.h"

#define CT_TYPE_IM_DISP3	(ct_im_disp3_get_type())
#define CT_IM_DISP3(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp3))
#define CT_IS_IM_DISP3(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP3)

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/

#define CtImDisp3_CT_IM_DISP_MAX_PARAMETER_NUM	(16)	// Maximum parameter word num
#define CtImDisp3_D_CT_IM_DISP_NO_PARA	('0')			// No any parameters
#define CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY	('1')	// Have first parameter only
#define CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY	('2')	// Have second parameter only
#define CtImDisp3_D_CT_IM_DISP_BOTH_PARA	('3')			// Have first and second parameter

#define CtImDisp3_D_CT_IM_DISP_BLOCK_NUM	(2)				// Maximum block number
#define CtImDisp3_D_CT_IM_DISP_BLOCK_0	('0')			// block 0
#define CtImDisp3_D_CT_IM_DISP_BLOCK_1	('1')			// block 1

typedef struct _CtImDisp3 CtImDisp3;
typedef struct _CtImDisp3Private		CtImDisp3Private;

struct _CtImDisp3{
	KObject parent;
	CtImDisp3Private *privCtImDisp3;
};

KConstType 		ct_im_disp3_get_type(void);
CtImDisp3 *		ct_im_disp3_new(kuchar *pclkCounter, kuchar *hclkCounter);

#ifdef CtImDisp_CO_DEBUG_DISP

void 				ct_im_disp3_dump_reg_yhelp(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_warning(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_zebra(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_matrix(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_output_size(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_clbdt(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_out_matrix(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_clip(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_face(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_osd_area_size(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_osd_area_addr(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_osd_area_adata_addr(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_osd_lfd(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_osd_adata_lfd(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_osd_pos(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_osd_blink_timer(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_osd_resize(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_osd_matrix(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_anti_gamma_table(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_main_gamma_table(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_dcore_gamma_table(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_lumi_gamma_table(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_gain_table(CtImDisp3 *self, E_IM_DISP_SEL block);
void 				ct_im_disp3_dump_reg_bb(CtImDisp3 *self);
void 				ct_im_disp3_dump_reg_reset(CtImDisp3 *self);
void 				ct_im_disp3_dump_reg_addr(CtImDisp3 *self);
void 				ct_im_disp3_dump_reg_resize(CtImDisp3 *self);
void 				ct_im_disp3_dump_reg_csc_matrix(CtImDisp3 *self, E_IM_DISP_SEL block);

void 				ct_im_disp3_pclk_counter_on(kuchar *pclkCounter);
void 				ct_im_disp3_pclk_counter_off(kuchar *pclkCounter);
void 				ct_im_disp3_hclk_counter_on(kuchar *hclkCounter);
void 				ct_im_disp3_hclk_counter_off(kuchar *hclkCounter);

void 				ct_im_disp3_print_param_resize(T_IM_DISP_RESIZE resize);
void 				ct_im_disp3_print_param_yhelp(T_IM_DISP_YHLP Yhlp);
void 				ct_im_disp3_print_param_warning(T_IM_DISP_WARNING warning);
void 				ct_im_disp3_print_param_zebra(T_IM_DISP_ZEBRA zebra);
void 				ct_im_disp3_print_param_matrix(U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE]);
void 				ct_im_disp3_print_param_clbdt(U_IM_DISP_IMAGE_COLOR* clbdt);
void 				ct_im_disp3_print_param_out_matrix(U_IM_DISP_YR_MATRIX_COEFFICIENT* matrix);
void 				ct_im_disp3_print_param_clip(T_IM_DISP_CLIP_CAL clipCal);
void 				ct_im_disp3_print_param_face(T_IM_DISP_FACE_FRAME face);
void 				ct_im_disp3_print_param_osd_area_size(U_IM_DISP_SIZE* inputSize);
void 				ct_im_disp3_print_param_osd_matrix(U_IM_DISP_GRY2R* gry2r);

void 				ct_im_disp3_int_00_cb();
void 				ct_im_disp3_int_01_cb();
void 				ct_im_disp3_int_02_cb();
void 				ct_im_disp3_int_03_cb();
void 				ct_im_disp3_int_04_cb();
void 				ct_im_disp3_int_05_cb();
void 				ct_im_disp3_int_06_cb();
void 				ct_im_disp3_int_07_cb();
void 				ct_im_disp3_int_08_cb();
void 				ct_im_disp3_int_09_cb();
void 				ct_im_disp3_int_10_cb();
void 				ct_im_disp3_int_11_cb();

#endif //CtImDisp_CO_DEBUG_DISP

#endif /* __CT_IM_DISP3_H__ */
