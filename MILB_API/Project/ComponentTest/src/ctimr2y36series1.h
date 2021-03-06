/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y36series1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_36SERIES1_H__
#define __CT_IM_R2Y_36SERIES1_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_36SERIES1                  (ct_im_r2y_36series1_get_type())
#define CT_IM_R2Y_36SERIES1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y36series1)) 
#define CT_IS_IM_R2Y_36SERIES1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_36SERIES1)) 


typedef struct _CtImR2y36series1 CtImR2y36series1;
typedef struct _CtImR2y36series1Private CtImR2y36series1Private;

struct _CtImR2y36series1 
{
	KObject parent;
	ImR2y *imR2y;
	ImR2y2 *imR2y2;
	ImR2y3 *imR2y3;
	CtImR2yClassa *ctImR2yClassa;
	CtImR2y *ctImR2y;
	ImR2yProc *imR2yProc;
	CtImR2yClassb *ctImR2yClassb;
	ImR2yStat *imR2yStat;
};


KConstType 					ct_im_r2y_36series1_get_type(void);
CtImR2y36series1			*ct_im_r2y_36series1_new(void);

kint32 								ct_im_r2y_36series1_6(CtImR2y36series1 *self, kuchar pipeNo);
kint32 								ct_im_r2y_36series1_7(CtImR2y36series1 *self, kuchar pipeNo);
kint32 								ct_im_r2y_36series1_8(CtImR2y36series1 *self, kuchar pipeNo);
kint32 								ct_im_r2y_36series1_9(CtImR2y36series1 *self, kuchar pipeNo);


#endif /* __CT_IM_R2Y_36SERIES1_H__ */
