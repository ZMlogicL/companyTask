/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :jianghaodong
*@brief               :CtImRbkRun2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_RBK_RUN2_H_
#define __CT_IM_RBK_RUN2_H_

#include <klib.h>
#include "im_ltm.h"
#include "ctimrbkrun1.h"

#define CT_TYPE_IM_RBK_RUN2					(ct_im_rbk_run2_get_type())
#define CT_IM_RBK_RUN2(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImRbkRun2)) 
#define CT_IS_IM_RBK_RUN2(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_RBK_RUN2)) 

typedef struct 			_CtImRbkRun2 CtImRbkRun2;
typedef struct 			_CtImRbkRun2Private CtImRbkRun2Private;

struct _CtImRbkRun2
{
	KObject parent;
};

KConstType 		ct_im_rbk_run2_get_type(void);
CtImRbkRun2* 	ct_im_rbk_run2_new(void);

kint32 					ct_im_rbk_run2_rbk_2_1(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_2_2(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_2_3(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_2_4(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_2_5(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_2_6(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_2_7(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_2_8(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_2_9(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_2_10(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_2_11(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_2_12(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_2_13(CtImRbkRun2* self);

kint32 					ct_im_rbk_run2_rbk_3_11(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_3_12(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_3_13(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_3_14(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_3_15(CtImRbkRun2* self);
kint32 					ct_im_rbk_run2_rbk_3_16(CtImRbkRun2* self);

T_IM_LTM_RBK_CTRL_SRO_DIRECT *
							ct_im_rbk_run2_get_gct_im_ltm_rbk_ctrl_sro_direct_base(CtImRbkRun2* self);
void 					ct_im_rbk_run2_set_var1(CtImRbkRun2* self, CtImRbkRun1* var1);


#endif /* __CT_IM_RBK_RUN2_H_ */
