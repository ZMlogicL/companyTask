/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y34series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_34SERIES_H__
#define __CT_IM_R2Y_34SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_34SERIES                  (ct_im_r2y_34series_get_type())
#define CT_IM_R2Y_34SERIES(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y34series)) 
#define CT_IS_IM_R2Y_34SERIES(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_34SERIES)) 


typedef struct _CtImR2y34series CtImR2y34series;
typedef struct _CtImR2y34seriesPrivate CtImR2y34seriesPrivate;

struct _CtImR2y34series 
{
	KObject parent;
	CtImR2yClassa *ctImR2yClassa;
	ImR2y *imR2y;
	ImR2y3 *imR2y3;
	ImR2y2 *imR2y2;
	CtImR2y *ctImR2y;
	ImR2yProc *imR2yProc;
	CtImR2yClassb *ctImR2yClassb;
	ImR2yStat *imR2yStat;
	CtImR2y3series *ctImR2y3series;
};


KConstType 				ct_im_r2y_34series_get_type(void);
CtImR2y34series		*ct_im_r2y_34series_new(void);

kint32 							ct_im_r2y_34series_0(CtImR2y34series *self, kuchar pipeNo);
kint32 							ct_im_r2y_34series_1(CtImR2y34series *self, kuchar pipeNo);
kint32 							ct_im_r2y_34series_2(CtImR2y34series *self, kuchar pipeNo);
kint32 							ct_im_r2y_34series_3(CtImR2y34series *self, kuchar pipeNo);
kint32 							ct_im_r2y_34series_4(CtImR2y34series *self, kuchar pipeNo);
kint32 							ct_im_r2y_34series_5(CtImR2y34series *self, kuchar pipeNo);
kint32 							ct_im_r2y_34series_6(CtImR2y34series *self, kuchar pipeNo);
kint32 							ct_im_r2y_34series_7(CtImR2y34series *self, kuchar pipeNo);
kint32 							ct_im_r2y_34series_8(CtImR2y34series *self, kuchar pipeNo);
kint32 							ct_im_r2y_34series_9(CtImR2y34series *self, kuchar pipeNo);


#endif /* __CT_IM_R2Y_34SERIES_H__ */
