/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y36series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_36SERIES_H__
#define __CT_IM_R2Y_36SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_36SERIES                  (ct_im_r2y_36series_get_type())
#define CT_IM_R2Y_36SERIES(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y36series)) 
#define CT_IS_IM_R2Y_36SERIES(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_36SERIES)) 


typedef struct _CtImR2y36series CtImR2y36series;
typedef struct _CtImR2y36seriesPrivate CtImR2y36seriesPrivate;

struct _CtImR2y36series 
{
	KObject parent;
};


KConstType 				ct_im_r2y_36series_get_type(void);
CtImR2y36series		*ct_im_r2y_36series_new(void);

kint32 							ct_im_r2y_36series_0(CtImR2y36series *self, kuchar pipeNo);
kint32 							ct_im_r2y_36series_1(CtImR2y36series *self, kuchar pipeNo);
kint32 							ct_im_r2y_36series_2(CtImR2y36series *self, kuchar pipeNo);
kint32 							ct_im_r2y_36series_3(CtImR2y36series *self, kuchar pipeNo);
kint32 							ct_im_r2y_36series_4(CtImR2y36series *self, kuchar pipeNo);
kint32 							ct_im_r2y_36series_5(CtImR2y36series *self, kuchar pipeNo);


#endif /* __CT_IM_R2Y_36SERIES_H__ */
