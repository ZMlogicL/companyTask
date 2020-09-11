/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 梁正明
*@brief : CtImR2y18series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_18SERIES_H__
#define __CT_IM_R2Y_18SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_18SERIES                  (ct_im_r2y_18series_get_type())
#define CT_IM_R2Y_18SERIES(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y18series)) 
#define CT_IS_IM_R2Y_18SERIES(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_18SERIES)) 


typedef struct _CtImR2y18series CtImR2y18series;
typedef struct _CtImR2y18seriesPrivate CtImR2y18seriesPrivate;

struct _CtImR2y18series 
{
	KObject parent;
	ImR2yEdge *imR2yEdge;
	ImR2yClk * imR2yClk;
	ImR2yStat *imR2yStat;
	ImR2yCtrl3 *imR2yCtrl3;
};


KConstType 			ct_im_r2y_18series_get_type(void);
CtImR2y18series	*ct_im_r2y_18series_new(void);

kint32 						ct_im_r2y_18series_0(CtImR2y18series *self, kuchar pipeNo);
kint32 						ct_im_r2y_18series_1(CtImR2y18series *self, kuchar pipeNo);
kint32 						ct_im_r2y_18series_2(CtImR2y18series *self, kuchar pipeNo);
kint32 						ct_im_r2y_18series_3(CtImR2y18series *self, kuchar pipeNo);
kint32 						ct_im_r2y_18series_4(CtImR2y18series *self, kuchar pipeNo);
kint32 						ct_im_r2y_18series_5(CtImR2y18series *self, kuchar pipeNo);


#endif /* __CT_IM_R2Y_18SERIES_H__ */
