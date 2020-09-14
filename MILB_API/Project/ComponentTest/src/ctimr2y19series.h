/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y19series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_19SERIES_H__
#define __CT_IM_R2Y_19SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_19SERIES                  (ct_im_r2y_19series_get_type())
#define CT_IM_R2Y_19SERIES(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y19series)) 
#define CT_IS_IM_R2Y_19SERIES(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_19SERIES)) 


typedef struct _CtImR2y19series CtImR2y19series;
typedef struct _CtImR2y19seriesPrivate CtImR2y19seriesPrivate;

struct _CtImR2y19series 
{
	KObject parent;
	ImR2yCtrl3 *imR2yCtrl3;
	ImR2yClk *imR2yClk;
	ImR2yCtrl * imR2yCtrl;
	ImR2yCtrl2 * imR2yCtrl2;
	ImR2ySet *imR2ySet;
	ImR2yEdge *imR2yEdge;
};


KConstType 				ct_im_r2y_19series_get_type(void);
CtImR2y19series		*ct_im_r2y_19series_new(void);

kint32 							ct_im_r2y_19series_0(CtImR2y19series *self, kuchar pipeNo);
kint32 							ct_im_r2y_19series_1(CtImR2y19series *self, kuchar pipeNo);
kint32 							ct_im_r2y_19series_2(CtImR2y19series *self, kuchar pipeNo);
kint32 							ct_im_r2y_19series_3(CtImR2y19series *self, kuchar pipeNo);
kint32 							ct_im_r2y_19series_4(CtImR2y19series *self, kuchar pipeNo);


#endif /* __CT_IM_R2Y_19SERIES_H__ */
