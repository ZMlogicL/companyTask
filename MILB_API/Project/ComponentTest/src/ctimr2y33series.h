/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y33series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_33SERIES_H__
#define __CT_IM_R2Y_33SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_33SERIES                  (ct_im_r2y_33series_get_type())
#define CT_IM_R2Y_33SERIES(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y33series)) 
#define CT_IS_IM_R2Y_33SERIES(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_33SERIES)) 


typedef struct _CtImR2y33series CtImR2y33series;
typedef struct _CtImR2y33seriesPrivate CtImR2y33seriesPrivate;

struct _CtImR2y33series 
{
	KObject parent;
	ImR2y *imR2y;
	ImR2y2 *imR2y2;
	CtImR2yClassa *ctImR2yClassa;
	CtImR2y *ctImR2y;
	ImR2yProc *imR2yProc;
	CtImR2yClassb *ctImR2yClassb;
	ImR2y3 *imR2y3;
};


KConstType 				ct_im_r2y_33series_get_type(void);
CtImR2y33series		*ct_im_r2y_33series_new(void);

kint32 							ct_im_r2y_33series_0(CtImR2y33series *self, kuchar pipeNo);
kint32 							ct_im_r2y_33series_1(CtImR2y33series *self, kuchar pipeNo);
kint32 							ct_im_r2y_33series_2(CtImR2y33series *self, kuchar pipeNo);
kint32 							ct_im_r2y_33series_3(CtImR2y33series *self, kuchar pipeNo);
kint32 							ct_im_r2y_33series_4(CtImR2y33series *self, kuchar pipeNo);


#endif /* __CT_IM_R2Y_33SERIES_H__ */
