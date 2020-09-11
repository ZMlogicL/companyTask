/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassa
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_CLASSA_H__
#define __CT_IM_R2Y_CLASSA_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_CLASSA                  (ct_im_r2y_classa_get_type())
#define CT_IM_R2Y_CLASSA(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassa)) 
#define CT_IS_IM_R2Y_CLASSA(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSA)) 


typedef struct _CtImR2yClassa CtImR2yClassa;
typedef struct _CtImR2yClassaPrivate CtImR2yClassaPrivate;

struct _CtImR2yClassa 
{
	KObject parent;
	CtImR2yClassa * ctImR2yClassa;
	ImR2yCtrl2 *imR2yCtrl2;
	ImR2yClk *imR2yClk;
};


KConstType ct_im_r2y_classa_get_type(void);
CtImR2yClassa* ct_im_r2y_classa_new(void);
CtImR2yClassa* ct_im_r2y_classa_get(void);

VOID ct_im_r2y_classa_b2r_int_handler( UINT32* result, UINT32 userParam );
VOID ct_im_r2y_classa_set_b2r(CtImR2yClassa*self, UCHAR pipeNo );
VOID ct_im_r2y_classa_start_b2r( CtImR2yClassa*self,UCHAR pipeNo );
VOID ct_im_r2y_classa_wait_b2r( CtImR2yClassa*self,UCHAR pipeNo );
VOID ct_im_r2y_classa_waitend_stop_b2r( CtImR2yClassa*self,UCHAR pipeNo );
VOID ct_im_r2y_calssa_ltm_int_handler( UINT32* result, UINT32 userParam );
VOID ct_im_r2y_classa_set_ltm( CtImR2yClassa*self,UCHAR pipeNo );
VOID ct_im_r2y_classa_start_ltm( CtImR2yClassa*self,UCHAR pipeNo );
VOID ct_im_r2y_classa_wait_ltm(CtImR2yClassa*self, UCHAR pipeNo );
VOID ct_im_r2y_classa_waitend_stop_ltm( CtImR2yClassa*self,UCHAR pipeNo );
VOID ct_im_r2y_classa_set_wb_gain_rgb( CtImR2yClassa*self,UCHAR pipeNo );
VOID ct_im_r2y_classa_print_r2y_common_reg( CtImR2yClassa*self );
VOID ct_im_r2y_classa_print_r2y_yyr_reg( CtImR2yClassa*self );
VOID ct_im_r2y_classa_print_r2y_yyw_reg( CtImR2yClassa*self );
VOID ct_im_r2y_classa_print_r2y_ctrl_reg( CtImR2yClassa*self );
VOID ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa CtImR2yClassa*self );
VOID ct_im_r2y_classa_print_r2y_ctrl_modedirect_reg(self->ctImR2yClassa CtImR2yClassa*self );
VOID ct_im_r2y_classa_print_resize_rect_reg( CtImR2yClassa*self );
VOID ct_im_r2y_classa_print_trimming_reg( CtImR2yClassa*self );
VOID ct_im_r2y_classa_print_color_extract_reg( CtImR2yClassa*self );
VOID ct_im_r2y_classa_print_chroma_scale_reg( CtImR2yClassa*self );
VOID ct_im_r2y_classa_print_hue_scale_reg( CtImR2yClassa*self );
VOID ct_im_r2y_classa_print_hist_reg( CtImR2yClassa*self );
VOID ct_im_r2y_classa_print_post_resize_edge0_reg( CtImR2yClassa*self );




#endif /* __CT_IM_R2Y_CLASSA_H__ */
