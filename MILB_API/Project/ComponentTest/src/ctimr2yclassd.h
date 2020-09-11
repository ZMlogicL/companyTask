/*
 *
 *@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
 *@date : 2020-09-02
 *@author : THH
 *@brief : CtImR2yClassd
 *@rely : klib.h
 *@function : 按ETK规范抄写索喜源代码
 *@version : 1.0.0 能正常上屏显示图像
 *
 */

#ifndef __CT_IM_R2Y_CLASSD_H__
#define __CT_IM_R2Y_CLASSD_H__

#include <klib.h>

#define CT_TYPE_IM_R2Y_CLASSD                  (ct_im_r2y_classd_get_type())
#define CT_IM_R2Y_CLASSD(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassd)) 
#define CT_IS_IM_R2Y_CLASSD(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSD)) 

typedef struct _CtImR2yClassd CtImR2yClassd;
typedef struct _CtImR2yClassdPrivate CtImR2yClassdPrivate;

struct _CtImR2yClassd
{
	KObject parent;
	ImR2y * imR2y;
	ImR2yClk*imR2yClk;
	ImR2y3 *imR2y2;
	CtImR2yClassa * ctImR2yClassa;
	ImR2yStat*imR2yStat;
	CtImR2y*ctImR2y;
	ImR2yProc*imR2yProc;
	ImR2y3 *imR2y3;
};

KConstType ct_im_r2y_classd_get_type(void);
CtImR2yClassd* ct_im_r2y_classd_new(void);
CtImR2yClassd* ct_im_r2y_classd_get(void);

INT32 ct_im_r2y_classd_1_15(CtImR2yClassd*self,UCHAR pipeNo);
INT32 ct_im_r2y_classd_1_25(CtImR2yClassd*self,UCHAR pipeNo);
INT32 ct_im_r2y_classd_1_26(CtImR2yClassd*self,UCHAR pipeNo);
INT32 ct_im_r2y_classd_1_27(CtImR2yClassd*self,UCHAR pipeNo);
INT32 ct_im_r2y_classd_1_28(CtImR2yClassd*self,UCHAR pipeNo);
INT32 ct_im_r2y_classd_1_29(CtImR2yClassd*self,UCHAR pipeNo);
INT32 ct_im_r2y_classd_1_30(CtImR2yClassd*self,UCHAR pipeNo);
INT32 ct_im_r2y_classd_1_31(CtImR2yClassd*self,UCHAR pipeNo);
INT32 ct_im_r2y_classd_1_32(CtImR2yClassd*self,UCHAR pipeNo);
INT32 ct_im_r2y_classd_1_33(CtImR2yClassd*self,UCHAR pipeNo);
INT32 ct_im_r2y_classd_1_34(CtImR2yClassd*self,UCHAR pipeNo);
INT32 ct_im_r2y_classd_1_35(CtImR2yClassd*self,UCHAR pipeNo);
INT32 ct_im_r2y_classd_1_36(CtImR2yClassd*self,UCHAR pipeNo);

#endif /* __CT_IM_R2Y_CLASSD_H__ */
