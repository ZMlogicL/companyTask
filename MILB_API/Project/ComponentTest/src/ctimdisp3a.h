/*
 *ctimdisp3a.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP3A_H__
#define __CT_IM_DISP3A_H__

#include <glib-object.h>

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP3A					(ct_im_disp3a_get_type ())
#define CT_IM_DISP3A(widget)				(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
		CT_TYPE_IM_DISP3A, CtImDisp3a))
#define CT_IM_DISP3A_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_DISP3A, CtImDisp3aClass))
#define CT_IS_IM_DISP3A(widget)			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP3A))
#define CT_IS_IM_DISP3A_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP3A))
#define CT_IM_DISP3A_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_DISP3A, CtImDisp3aClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp3a 					CtImDisp3a;
typedef struct _CtImDisp3aClass 			CtImDisp3aClass;
typedef struct _CtImDisp3aPrivate 			CtImDisp3aPrivate;

struct _CtImDisp3a
{
	GObject parent;
	/*public*/
	CtImDisp3aPrivate *privCtImDisp3a;
};

struct _CtImDisp3aClass
{
	GObjectClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 				ct_im_disp3a_get_type(void) G_GNUC_CONST;
CtImDisp3a *	ct_im_disp3a_new(guchar *pclkCounter, guchar *hclkCounter);

#ifdef CtImDisp_CO_DEBUG_DISP
void 				ct_im_disp3a_dump_reg_p2m_pwch(CtImDisp3a *self, E_IM_DISP_WC_NUM number);
void 				ct_im_disp3a_clear_reg_lch(CtImDisp3a *self, E_IM_DISP_SEL block);
void 				ct_im_disp3a_dump_reg_grid(CtImDisp3a *self, E_IM_DISP_SEL block);
void 				ct_im_disp3a_dump_reg_trg(CtImDisp3a *self);
void 				ct_im_disp3a_dump_regiser(CtImDisp3a *self, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_SEL block);
void 				ct_im_disp3a_dump_reg_dcore_gamma(CtImDisp3a *self, E_IM_DISP_SEL block);

void 				ct_im_disp3a_output_dword_table(LLONG table[], gint32 size);
void 				ct_im_disp3a_print_ctrl_output_tbl(T_IM_DISP_CTRL_OUTPUT_TBL ctrlTbl);
void 				ct_im_disp3a_output_p2m_pwch(T_IM_DISP_CTRL_P2M *p2m, T_IM_DISP_CTRL_PWCH pwch);
void 				ct_im_disp3a_print_param_grch(T_IM_DISP_CTRL_OSD_LAYER ctrl);
void 				ct_im_disp3a_print_param_ctrl_grid(T_IM_DISP_CTRL_GRID_LAYER ctrl);
void 				ct_im_disp3a_print_param_grid(T_IM_DISP_GRID grid);
void 				ct_im_disp3a_print_param_ctrl_osd_layer(T_IM_DISP_CTRL_OSD_LAYER osd);
void 				ct_im_disp3a_output_byte_9_table(U_IM_DISP_YR_MATRIX_COEFFICIENT table[3]);
void 				ct_im_disp3a_output_ushort_32_table(volatile gushort table[32]);
void 				ct_im_disp3a_output_ushort_33_table(volatile gushort table[33]);
void 				ct_im_disp3a_output_word_table(guint32 table[], gint32 size);
void 				ct_im_disp3a_output_dcore_gamma(const T_IM_DISP_GAMMA_TBL_OUT gammaTbl);
void 				ct_im_disp3a_get_ctrl_main_layer(BYTE getDataType, E_IM_DISP_SEL block);

#endif //CtImDisp_CO_DEBUG_DISP


G_END_DECLS

#endif /* __CT_IM_DISP3A_H__ */
