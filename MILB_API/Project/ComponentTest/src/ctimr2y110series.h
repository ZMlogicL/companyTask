/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y110series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_110SERIES_H__
#define __CT_IM_R2Y_110SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_110SERIES                  (ct_im_r2y_110series_get_type())
#define CT_IM_R2Y_110SERIES(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y110series)) 
#define CT_IS_IM_R2Y_110SERIES(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_110SERIES)) 


typedef struct _CtImR2y110series CtImR2y110series;
typedef struct _CtImR2y110seriesPrivate CtImR2y110seriesPrivate;

struct _CtImR2y110series 
{
	KObject parent;
	ImR2ySet *imR2ySet;
	ImR2yClk *imR2yClk;
	ImR2yCtrl3 *imR2yCtrl3;
	ImR2yUtility *imR2yUtility;
};


KConstType 					ct_im_r2y_110series_get_type(void);
CtImR2y110series			*ct_im_r2y_110series_new(void);

kint32 								ct_im_r2y_110series_0(CtImR2y110series *self, kuchar pipeNo);
kint32 								ct_im_r2y_110series_1(CtImR2y110series *self, kuchar pipeNo);
kint32 								ct_im_r2y_110series_2(CtImR2y110series *self, kuchar pipeNo);
kint32 								ct_im_r2y_110series_3(CtImR2y110series *self, kuchar pipeNo);
kint32 								ct_im_r2y_110series_4(CtImR2y110series *self, kuchar pipeNo);
kint32 								ct_im_r2y_110series_5(CtImR2y110series *self, kuchar pipeNo);
kint32 								ct_im_r2y_110series_6(CtImR2y110series *self, kuchar pipeNo);
kint32 								ct_im_r2y_110series_7(CtImR2y110series *self, kuchar pipeNo);
kint32 								ct_im_r2y_110series_8(CtImR2y110series *self, kuchar pipeNo);
kint32 								ct_im_r2y_110series_9(CtImR2y110series *self, kuchar pipeNo);


#endif /* __CT_IM_R2Y_110SERIES_H__ */
