/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y31series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_31SERIES_H__
#define __CT_IM_R2Y_31SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_31SERIES                  (ct_im_r2y_31series_get_type())
#define CT_IM_R2Y_31SERIES(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y31series)) 
#define CT_IS_IM_R2Y_31SERIES(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_31SERIES)) 


typedef struct _CtImR2y31series CtImR2y31series;
typedef struct _CtImR2y31seriesPrivate CtImR2y31seriesPrivate;

struct _CtImR2y31series 
{
	KObject parent;
	ImR2y *imR2y;
	ImR2y2 *imR2y2;
	CtImR2yClassa *ctImR2yClassa;
	CtImR2y *ctImR2y;
	ImR2yStat *imR2yStat;
	ImR2yProc *imR2yProc;
	CtImR2yClassb *ctImR2yClassb;
	CtImR2y31series *ctImR2y31series;
	ImR2y3 *imR2y3;
};


KConstType 					ct_im_r2y_31series_get_type(void);
CtImR2y31series			*ct_im_r2y_31series_new(void);

kint32 								ct_im_r2y_31series_0(CtImR2y31series *self, kuchar pipeNo);
kint32 								ct_im_r2y_31series_1(CtImR2y31series *self, kuchar pipeNo);
kint32	 							ct_im_r2y_31series_2(CtImR2y31series *self, kuchar pipeNo);
kint32 								ct_im_r2y_31series_3(CtImR2y31series *self, kuchar pipeNo);
kint32 								ct_im_r2y_31series_4(CtImR2y31series *self, kuchar pipeNo);
kint32 								ct_im_r2y_31series_5(CtImR2y31series *self, kuchar pipeNo);
kint32 								ct_im_r2y_31series_6(CtImR2y31series *self, kuchar pipeNo);
kint32 								ct_im_r2y_31series_7(CtImR2y31series *self, kuchar pipeNo);
kint32 								ct_im_r2y_31series_8(CtImR2y31series *self, kuchar pipeNo);
kint32 								ct_im_r2y_31series_9(CtImR2y31series *self, kuchar pipeNo);

#endif /* __CT_IM_R2Y_31SERIES_H__ */
