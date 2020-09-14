/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y2series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_2SERIES_H__
#define __CT_IM_R2Y_2SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_2SERIES                  (ct_im_r2y_2series_get_type())
#define CT_IM_R2Y_2SERIES(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y2series)) 
#define CT_IS_IM_R2Y_2SERIES(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_2SERIES)) 


typedef struct _CtImR2y2series CtImR2y2series;
typedef struct _CtImR2y2seriesPrivate CtImR2y2seriesPrivate;

struct _CtImR2y2series 
{
	KObject parent;
	ImR2y *imR2y;
	ImR2y2 *imR2y2;
	ImR2yStat *imR2yStat;
	ImR2yProc *imR2yProc;
	ImR2y3 *imR2y3;
	CtImR2y2series *ctImR2y2series;
};


KConstType 				ct_im_r2y_2series_get_type(void);
CtImR2y2series			*ct_im_r2y_2series_new(void);

kint32 							ct_im_r2y_2series_1(CtImR2y2series *self, kuchar pipeNo);
kint32 							ct_im_r2y_2series_2(CtImR2y2series *self, kuchar pipeNo);
kint32 							ct_im_r2y_2series_run_2(CtImR2y2series *self, kuchar pipeNo, const kuint32 ctNo3rd);


#endif /* __CT_IM_R2Y_2SERIES_H__ */
