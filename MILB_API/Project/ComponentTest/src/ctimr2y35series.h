/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y35series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_35SERIES_H__
#define __CT_IM_R2Y_35SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_35SERIES                  (ct_im_r2y_35series_get_type())
#define CT_IM_R2Y_35SERIES(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y35series)) 
#define CT_IS_IM_R2Y_35SERIES(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_35SERIES)) 


typedef struct _CtImR2y35series CtImR2y35series;
typedef struct _CtImR2y35seriesPrivate CtImR2y35seriesPrivate;

struct _CtImR2y35series 
{
	KObject parent;
	ImR2y *imR2y;
	ImR2y2 *imR2y2;
	CtImR2yClassa *ctImR2yClassa;
	CtImR2y *ctImR2y;
	ImR2yProc *imR2yProc;
	CtImR2yClassb *ctImR2yClassb;
	CtImR2y35series *ctImR2y35series;
	CtImR2y3series *ctImR2y3series;
	CtImR2y31series *ctImR2y31series;
};


KConstType 				ct_im_r2y_35series_get_type(void);
CtImR2y35series		*ct_im_r2y_35series_new(void);

kint32 							ct_im_r2y_35series_0(CtImR2y35series *self, kuchar pipeNo);
kint32 							ct_im_r2y_35series_1(CtImR2y35series *self, kuchar pipeNo);
kint32 							ct_im_r2y_35series_2(CtImR2y35series *self, kuchar pipeNo);
kint32 							ct_im_r2y_35series_3(CtImR2y35series *self, kuchar pipeNo);
kint32 							ct_im_r2y_35series_4(CtImR2y35series *self, kuchar pipeNo);
kint32 							ct_im_r2y_35series_5(CtImR2y35series *self, kuchar pipeNo);
kint32 							ct_im_r2y_35series_6(CtImR2y35series *self, kuchar pipeNo);
kint32 							ct_im_r2y_35series_7(CtImR2y35series *self, kuchar pipeNo);
kint32 							ct_im_r2y_35series_8(CtImR2y35series *self, kuchar pipeNo);
kint32 							ct_im_r2y_35series_9(CtImR2y35series *self, kuchar pkuchar);


#endif /* __CT_IM_R2Y_35SERIES_H__ */
