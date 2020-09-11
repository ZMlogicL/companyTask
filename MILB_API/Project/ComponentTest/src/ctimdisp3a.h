/*
 *ctimdisp3a.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP3A_H__
#define __CT_IM_DISP3A_H__

#include <klib.h>

#define CT_TYPE_IM_DISP3A	(ct_im_disp3a_get_type())
#define CT_IM_DISP3A(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp3a))
#define CT_IS_IM_DISP3A(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP3A)

typedef struct _CtImDisp3a CtImDisp3a;
typedef struct _CtImDisp3aPrivate		CtImDisp3aPrivate;

struct _CtImDisp3a{
	KObject parent;
	CtImDisp3aPrivate *privCtImDisp3a;
};

KConstType 		ct_im_disp3a_get_type(void);
CtImDisp3a *	ct_im_disp3a_new(kuchar *pclkCounter, kuchar *hclkCounter);

#ifdef CtImDisp_CO_DEBUG_DISP
void 				ct_im_disp3a_dump_reg_p2m_pwch(CtImDisp3a *self, E_IM_DISP_WC_NUM number);
void 				ct_im_disp3a_clear_reg_lch(CtImDisp3a *self, E_IM_DISP_SEL block);
void 				ct_im_disp3a_dump_reg_grid(CtImDisp3a *self, E_IM_DISP_SEL block);
void 				ct_im_disp3a_dump_reg_trg(CtImDisp3a *self);
void 				ct_im_disp3a_dump_regiser(CtImDisp3a *self, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_SEL block);
void 				ct_im_disp3a_dump_reg_dcore_gamma(CtImDisp3a *self, E_IM_DISP_SEL block);

void 				ct_im_disp3a_output_dword_table(LLONG table[], kint32 size);
void 				ct_im_disp3a_print_ctrl_output_tbl(T_IM_DISP_CTRL_OUTPUT_TBL ctrlTbl);
void 				ct_im_disp3a_output_p2m_pwch(T_IM_DISP_CTRL_P2M *p2m, T_IM_DISP_CTRL_PWCH pwch);
void 				ct_im_disp3a_print_param_grch(T_IM_DISP_CTRL_OSD_LAYER ctrl);
void 				ct_im_disp3a_print_param_ctrl_grid(T_IM_DISP_CTRL_GRID_LAYER ctrl);
void 				ct_im_disp3a_print_param_grid(T_IM_DISP_GRID grid);
void 				ct_im_disp3a_print_param_ctrl_osd_layer(T_IM_DISP_CTRL_OSD_LAYER osd);
void 				ct_im_disp3a_output_byte_9_table(U_IM_DISP_YR_MATRIX_COEFFICIENT table[3]);
void 				ct_im_disp3a_output_ushort_32_table(volatile kushort table[32]);
void 				ct_im_disp3a_output_ushort_33_table(volatile kushort table[33]);
void 				ct_im_disp3a_output_word_table(kuint32 table[], kint32 size);
void 				ct_im_disp3a_output_dcore_gamma(const T_IM_DISP_GAMMA_TBL_OUT gammaTbl);
void 				ct_im_disp3a_get_ctrl_main_layer(BYTE getDataType, E_IM_DISP_SEL block);

#endif //CtImDisp_CO_DEBUG_DISP

#endif /* __CT_IM_DISP3A_H__ */
