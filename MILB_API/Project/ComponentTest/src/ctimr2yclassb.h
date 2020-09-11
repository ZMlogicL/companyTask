/*
 *
 *@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
 *@date : 2020-09-02
 *@author : THH
 *@brief : CtImR2yClassb
 *@rely : klib.h
 *@function : 按ETK规范抄写索喜源代码
 *@version : 1.0.0 能正常上屏显示图像
 *
 */

#ifndef __CT_IM_R2Y_CLASSB_H__
#define __CT_IM_R2Y_CLASSB_H__

#include <klib.h>

#define CT_TYPE_IM_R2Y_CLASSB                  (ct_im_r2y_classb_get_type())
#define CT_IM_R2Y_CLASSB(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassb)) 
#define CT_IS_IM_R2Y_CLASSB(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSB)) 

typedef struct _CtImR2yClassb CtImR2yClassb;
typedef struct _CtImR2yClassbPrivate CtImR2yClassbPrivate;

struct _CtImR2yClassb
{
	KObject parent;
	CtImR2yClassb * ctImR2yClassb;
	CtImR2yClassa * ctImR2yClassa;
	ImR2yCtrl2 *imR2yCtrl2;
	ImR2yClk *imR2yClk;
	ImR2yStat * imR2yStat;
	ImR2y * imR2y;
};

KConstType ct_im_r2y_classb_get_type(void);
CtImR2yClassb* ct_im_r2y_classb_new(void);
CtImR2yClassb* ct_im_r2y_classb_get(void);

VOID ct_im_r2y_classb_print_post_resize_edge1_reg( CtImR2yClassb * self);
VOID ct_im_classb_r2y_print_other_reg( CtImR2yClassb * self);
VOID ct_im_r2y_classb_print_fr2y_ctrl_reg( CtImR2yClassb * self);
VOID ct_im_r2y_classb_print_axi_reg( CtImR2yClassb * self);
VOID ct_im_r2y_classb_printreg( CtImR2yClassb * self);
INT32 ct_im_r2y_classb_1_1(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_2(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_3(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_4(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_5(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_6(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_7(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_8(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_9(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_10(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_11(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_12(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_13(CtImR2yClassb * self,UCHAR pipeNo);
INT32 ct_im_r2y_classb_1_14(CtImR2yClassb * self,UCHAR pipeNo);

#endif /* __CT_IM_R2Y_CLASSB_H__ */
