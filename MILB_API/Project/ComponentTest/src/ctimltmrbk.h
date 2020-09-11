/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
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

#include <klib.h>

#define CT_TYPE_IM_LTM_RBK					(ct_im_ltm_rbk_get_type())
#define CT_IM_LTM_RBK(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImLtmRbk)) 
#define CT_IS_IM_LTM_RBK(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_LTM_RBK)) 


typedef struct 			_CtImLtmRbk CtImLtmRbk;
typedef struct 			_CtImLtmRbkPrivate CtImLtmRbkPrivate;

struct _CtImLtmRbk
{
	KObject parent;

};

KConstType 	ct_im_ltm_rbk_get_type(void);
CtImLtmRbk* 	ct_im_ltm_rbk_new(void);

void 				ct_im_ltm_rbk_print_ctrl_common_reg(void);
void 				ct_im_ltm_rbk_print_ctrl_sdram_input_reg(void);
void 				ct_im_ltm_rbk_print_sro_direct_reg(void);
void 				ct_im_ltm_rbk_print_all_reg(void);
void 				ct_im_ltm_rbk_set_sro(E_IM_PRO_UNIT_NUM unitNo, kuchar testPtn);
void 				ct_im_ltm_rbk_start_sro(E_IM_PRO_UNIT_NUM unitNo);
void 				ct_im_ltm_rbk_waitend_stop_sro(E_IM_PRO_UNIT_NUM unitNo);

void 				CT_Im_LTM_RBK_Run(const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd);
//void 				ct_im_ltm_rbk_run( CtImLtmRbk* self, const kuint32 ct_idx_1st, const kuint32 ct_idx_2nd, const kuint32 ct_idx_3rd );

void 				CT_Im_LTM_RBK_Main(kint32 argc, kchar** argv);
//void 				ct_im_ltm_rbk_main( CtImLtmRbk* self, kint32 argc, kchar** argv );


#endif /* __CT_IM_LTM_RBK_H_ */
