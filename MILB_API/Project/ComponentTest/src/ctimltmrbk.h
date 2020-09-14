/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImLtmRbk类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_LTM_RBK_H_
#define __CT_IM_LTM_RBK_H_

#include "./../../../fj/glib/src/gobject.h"


G_BEGIN_DECLS

#define CT_TYPE_IM_LTM_RBK					(ct_im_ltm_rbk_get_type())
#define CT_IM_LTM_RBK(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImLtmRbk)) 
#define CT_IM_LTM_RBK_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_LTM_RBK, CtImLtmRbkClass)) 
#define CT_IS_IM_LTM_RBK(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_LTM_RBK)) 
#define CT_IS_IM_LTM_RBK_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_LTM_RBK)) 
#define CT_IM_LTM_RBK_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_LTM_RBK, CtImLtmRbkClass)) 


typedef struct 			_CtImLtmRbk CtImLtmRbk;
typedef struct 			_CtImLtmRbkClass CtImLtmRbkClass;
typedef struct 			_CtImLtmRbkPrivate CtImLtmRbkPrivate;

struct _CtImLtmRbk
{
	GObject parent;
};

struct _CtImLtmRbkClass
{
	GObjectClass parentclass;
};


GType ct_im_ltm_rbk_get_type(void);
CtImLtmRbk *ct_im_ltm_rbk_new(void);

void 				ct_im_ltm_rbk_print_ctrl_common_reg(void);
void 				ct_im_ltm_rbk_print_ctrl_sdram_input_reg(void);
void 				ct_im_ltm_rbk_print_sro_direct_reg(void);
void 				ct_im_ltm_rbk_print_all_reg(void);
void 				ct_im_ltm_rbk_set_sro(E_IM_PRO_UNIT_NUM unitNo, guchar testPtn);
void 				ct_im_ltm_rbk_start_sro(E_IM_PRO_UNIT_NUM unitNo);
void 				ct_im_ltm_rbk_waitend_stop_sro(E_IM_PRO_UNIT_NUM unitNo);

void 				CT_Im_LTM_RBK_Run(CtImLtmRbk *self, const guint32 ctIdx1st, const guint32 ctIdx2nd, const guint32 ctIdx3rd);
//void 				ct_im_ltm_rbk_run( CtImLtmRbk* self, const guint32 ct_idx_1st, const guint32 ct_idx_2nd, const guint32 ct_idx_3rd );

void 				ct_im_ltm_rbk_main(CtImLtmRbk* self, gint32 argc, gchar** argv);

G_END_DECLS

#endif /* __CT_IM_LTM_RBK_H_ */
