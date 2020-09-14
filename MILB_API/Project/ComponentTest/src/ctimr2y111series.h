/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y111series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_111SERIES_H__
#define __CT_IM_R2Y_111SERIES_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_111SERIES                  (ct_im_r2y_111series_get_type())
#define CT_IM_R2Y_111SERIES(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2y111series)) 
#define CT_IS_IM_R2Y_111SERIES(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_111SERIES)) 


typedef struct _CtImR2y111series CtImR2y111series;
typedef struct _CtImR2y111seriesPrivate CtImR2y111seriesPrivate;

struct _CtImR2y111series 
{
	KObject parent;
	ImR2yUtility *imR2yUtility;
	ImR2yUtility2 *imR2yUtility2;
};


KConstType 					ct_im_r2y_111series_get_type(void);
CtImR2y111series			*ct_im_r2y_111series_new(void);

kint32 								ct_im_r2y_111series_0(CtImR2y111series *self, kuchar pipeNo);
kint32 								ct_im_r2y_111series_1(CtImR2y111series *self, kuchar pipeNo);
kint32 								ct_im_r2y_111series_2(CtImR2y111series *self, kuchar pipeNo);
kint32 								ct_im_r2y_111series_3(CtImR2y111series *self, kuchar pipeNo);
kint32 								ct_im_r2y_111series_4(CtImR2y111series *self, kuchar pipeNo);
kint32 								ct_im_r2y_111series_5(CtImR2y111series *self, kuchar pipeNo);
kint32 								ct_im_r2y_111series_6(CtImR2y111series *self, kuchar pipeNo);
kint32 								ct_im_r2y_111series_7(CtImR2y111series *self, kuchar pipeNo);
kint32 								ct_im_r2y_111series_8(CtImR2y111series *self, kuchar pipeNo);
kint32 								ct_im_r2y_111series_9(CtImR2y111series *self, kuchar pipeNo);


#endif /* __CT_IM_R2Y_111SERIES_H__ */
