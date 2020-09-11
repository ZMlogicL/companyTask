/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2yRun3
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_RUN3_H__
#define __CT_IM_R2Y_RUN3_H__


#include <klib.h>


#define CT_TYPE_IM_R2Y_RUN3                  (ct_im_r2y_run3_get_type())
#define CT_IM_R2Y_RUN3(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yRun3)) 
#define CT_IS_IM_R2Y_RUN3(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_RUN3)) 


typedef struct _CtImR2yRun3 CtImR2yRun3;
typedef struct _CtImR2yRun3Private CtImR2yRun3Private;

struct _CtImR2yRun3 
{
	KObject parent;
};


KConstType 			ct_im_r2y_run3_get_type(void);
CtImR2yRun3			*ct_im_r2y_run3_new(void);

kint32 						ct_im_r2y_run3_3(CtImR2yRun3 *self, kuchar pipeNo, const kuint32 ctNo3rd);
void 							ct_im_r2y_run3_run(CtImR2yRun3 *self, const kuint32 ctIdx1st, const kuint32 ctIdx2nd,
									const kuint32 ctIdx3rd);
void 							ct_im_r2y_run3_main(CtImR2yRun3 *self, kint32 argc, kchar** argv);


#endif /* __CT_IM_R2Y_RUN3_H__ */
