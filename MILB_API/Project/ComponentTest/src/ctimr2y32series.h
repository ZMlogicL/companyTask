/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y32series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_32SERIES_H__
#define __CT_IM_R2Y_32SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_32SERIES                  (ct_im_r2y_32series_get_type())
#define CT_IM_R2Y_32SERIES(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y32series)) 
#define CT_IS_IM_R2Y_32SERIES(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_32SERIES)) 


typedef struct _CtImR2y32series CtImR2y32series;
typedef struct _CtImR2y32seriesPrivate CtImR2y32seriesPrivate;

struct _CtImR2y32series 
{
	KObject parent;
	CtImR2y31series *ctImR2y31series;
	ImR2y *imR2y;
	ImR2y2 *imR2y2;
	CtImR2yClassa *ctImR2yClassa;
	CtImR2yClassb *ctImR2yClassb;
	CtImR2y *ctImR2y;
	ImR2yProc *imR2yProc;
	ImR2y3 *imR2y3;
	ImR2yStat *imR2yStat;
};


KConstType 				ct_im_r2y_32series_get_type(void);
CtImR2y32series		*ct_im_r2y_32series_new(void);


kint32 							ct_im_r2y_32series_0(CtImR2y32series *self, kuchar pipeNo);
kint32 							ct_im_r2y_32series_1(CtImR2y32series *self, kuchar pipeNo);
kint32 							ct_im_r2y_32series_2(CtImR2y32series *self, kuchar pipeNo);
kint32 							ct_im_r2y_32series_3(CtImR2y32series *self, kuchar pipeNo);
kint32 							ct_im_r2y_32series_4(CtImR2y32series *self, kuchar pipeNo);
kint32 							ct_im_r2y_32series_5(CtImR2y32series *self, kuchar pipeNo);
kint32 							ct_im_r2y_32series_6(CtImR2y32series *self, kuchar pipeNo);
kint32 							ct_im_r2y_32series_7(CtImR2y32series *self, kuchar pipeNo);
kint32 							ct_im_r2y_32series_8(CtImR2y32series *self, kuchar pipeNo);
kint32 							ct_im_r2y_32series_9(CtImR2y32series *self, kuchar pipeNo);

#endif /* __CT_IM_R2Y_32SERIES_H__ */
