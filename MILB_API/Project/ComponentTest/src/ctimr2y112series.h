/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y112series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_112SERIES_H__
#define __CT_IM_R2Y_112SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_112SERIES                  (ct_im_r2y_112series_get_type())
#define CT_IM_R2Y_112SERIES(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y112series)) 
#define CT_IS_IM_R2Y_112SERIES(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_112SERIES)) 


typedef struct _CtImR2y112series CtImR2y112series;
typedef struct _CtImR2y112seriesPrivate CtImR2y112seriesPrivate;

struct _CtImR2y112series 
{
	KObject parent;
	ImR2yUtility2 *imR2yUtility2;
	ImR2yUtility3 *imR2yUtility3;
	ImR2yUtility4 *imR2yUtility4;
};


KConstType 				ct_im_r2y_112series_get_type(void);
CtImR2y112series		*ct_im_r2y_112series_new(void);

kint32 							ct_im_r2y_112series_0(CtImR2y112series *self, kuchar pipeNo);
kint32 							ct_im_r2y_112series_1(CtImR2y112series *self, kuchar pipeNo);
kint32 							ct_im_r2y_112series_2(CtImR2y112series *self, kuchar pipeNo);
kint32 							ct_im_r2y_112series_3(CtImR2y112series *self, kuchar pipeNo);
kint32 							ct_im_r2y_112series_4(CtImR2y112series *self, kuchar pipeNo);
kint32 							ct_im_r2y_112series_5(CtImR2y112series *self, kuchar pipeNo);
kint32 							ct_im_r2y_112series_6(CtImR2y112series *self, kuchar pipeNo);
kint32 							ct_im_r2y_112series_7(CtImR2y112series *self, kuchar pipeNo);
kint32 							ct_im_r2y_112series_8(CtImR2y112series *self, kuchar pipeNo);
kint32 							ct_im_r2y_112series_9(CtImR2y112series *self, kuchar pipeNo);

#endif /* __CT_IM_R2Y_112SERIES_H__ */
