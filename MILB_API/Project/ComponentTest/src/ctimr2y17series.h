/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y17series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_17SERIES_H__
#define __CT_IM_R2Y_17SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_17SERIES                 (ct_im_r2y_17series_get_type())
#define CT_IM_R2Y_17SERIES(obj)                   (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y17series))
#define CT_IS_IM_R2Y_17SERIES(obj)              (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_17SERIES))


typedef struct _CtImR2y17series CtImR2y17series;
typedef struct _CtImR2y17seriesPrivate CtImR2y17seriesPrivate;

struct _CtImR2y17series 
{
	KObject parent;
	ImR2yStat *imR2yStat;
	ImR2yEdge *imR2yEdge;
	ImR2yClk *imR2yClk;
};


KConstType 				ct_im_r2y_17series_get_type(void);
CtImR2y17series		*ct_im_r2y_17series_new(void);

kint32 							ct_im_r2y_17series_4(CtImR2y17series *self, kuchar pipeNo);
kint32 							ct_im_r2y_17series_5(CtImR2y17series *self, kuchar pipeNo);
kint32 							ct_im_r2y_17series_6(CtImR2y17series *self, kuchar pipeNo);
kint32 							ct_im_r2y_17series_7(CtImR2y17series *self, kuchar pipeNo);
kint32 							ct_im_r2y_17series_8(CtImR2y17series *self, kuchar pipeNo);
kint32 							ct_im_r2y_17series_9(CtImR2y17series *self, kuchar pipeNo);


#endif /* __CT_IM_R2Y_17SERIES_H__ */
