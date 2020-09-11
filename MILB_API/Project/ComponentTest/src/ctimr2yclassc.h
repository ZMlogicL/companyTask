/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassc
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_CLASSC_H__
#define __CT_IM_R2Y_CLASSC_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_CLASSC                  (ct_im_r2y_classc_get_type())
#define CT_IM_R2Y_CLASSC(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yClassc)) 
#define CT_IS_IM_R2Y_CLASSC(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_CLASSC)) 


typedef struct _CtImR2yClassc CtImR2yClassc;
typedef struct _CtImR2yClasscPrivate CtImR2yClasscPrivate;

struct _CtImR2yClassc 
{
	KObject parent;
	ImR2y * imR2y;
	CtImR2y* ctImR2y;
	CtImR2yClassa * ctImR2yClassa;
	ImR2y3 *imR2y3;
	ImR2yClk*imR2yClk;
	ImR2y3 *imR2y2;
	ImR2yProc*imR2yProc;
};


KConstType ct_im_r2y_classc_get_type(void);
CtImR2yClassc* ct_im_r2y_classc_new(void);
CtImR2yClassc* ct_im_r2y_classc_get(void);


INT32 ct_im_r2y_classc_1_16( CtImR2yClassc *self,UCHAR pipeNo );
INT32 ct_im_r2y_classc_1_17( CtImR2yClassc *self,UCHAR pipeNo );
INT32 ct_im_r2y_classc_1_18( CtImR2yClassc *self,UCHAR pipeNo );
INT32 ct_im_r2y_classc_1_19( CtImR2yClassc *self,UCHAR pipeNo );
INT32 ct_im_r2y_classc_1_20( CtImR2yClassc *self,UCHAR pipeNo );
INT32 ct_im_r2y_classc_1_21( CtImR2yClassc *self,UCHAR pipeNo );
INT32 ct_im_r2y_classc_1_22( CtImR2yClassc *self,UCHAR pipeNo );
INT32 ct_im_r2y_classc_1_23( CtImR2yClassc *self,UCHAR pipeNo );
INT32 ct_im_r2y_classc_1_24( CtImR2yClassc *self,UCHAR pipeNo );



#endif /* __CT_IM_R2Y_CLASSC_H__ */
