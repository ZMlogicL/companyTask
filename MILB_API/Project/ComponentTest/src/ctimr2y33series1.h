/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y33series1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_33SERIES1_H__
#define __CT_IM_R2Y_33SERIES1_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_33SERIES1                  (ct_im_r2y_33series1_get_type())
#define CT_IM_R2Y_33SERIES1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y33series1)) 
#define CT_IS_IM_R2Y_33SERIES1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_33SERIES1)) 


typedef struct _CtImR2y33series1 CtImR2y33series1;
typedef struct _CtImR2y33series1Private CtImR2y33series1Private;

struct _CtImR2y33series1 
{
	KObject parent;
};


KConstType 						ct_im_r2y_33series1_get_type(void);
CtImR2y33series1				*ct_im_r2y_33series1_new(void);

kint32 									ct_im_r2y_33series1_5(CtImR2y33series1 *self, kuchar pipeNo);
kint32 									ct_im_r2y_33series1_6(CtImR2y33series1 *self, kuchar pipeNo);
kint32 									ct_im_r2y_33series1_7(CtImR2y33series1 *self, kuchar pipeNo);
kint32 									ct_im_r2y_33series1_8(CtImR2y33series1 *self, kuchar pipeNo);
kint32 									ct_im_r2y_33series1_9(CtImR2y33series1 *self, kuchar pipeNo);


#endif /* __CT_IM_R2Y_33SERIES1_H__ */
