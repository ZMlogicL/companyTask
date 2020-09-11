/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :jianghaodong
*@brief               :CtImRbkRun1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_RBK_RUN1_H_
#define __CT_IM_RBK_RUN1_H_

#include <klib.h>
#include "im_ltm.h"

#define CT_TYPE_IM_RBK_RUN1					(ct_im_rbk_run1_get_type())
#define CT_IM_RBK_RUN1(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImRbkRun1)) 
#define CT_IS_IM_RBK_RUN1(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_RBK_RUN1)) 

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define ct_im_ltm_rbk_check_target_pipe_no_1(a)		(((a)+1) & (D_IM_LTM_PIPE1+1))
#define ct_im_ltm_rbk_check_target_pipe_no_2(a)		(((a)+1) & (D_IM_LTM_PIPE2+1))


typedef struct 			_CtImRbkRun1 CtImRbkRun1;
typedef struct 			_CtImRbkRun1Private CtImRbkRun1Private;

struct _CtImRbkRun1
{
	KObject parent;
	kuchar pipeNo;
};

KConstType 			ct_im_rbk_run1_get_type(void);
CtImRbkRun1* 		ct_im_rbk_run1_new(void);

kint32 						ct_im_rbk_run1_rbk_1_1(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_2(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_3(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_4(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_5(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_6(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_7(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_8(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_9(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_10(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_11(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_12(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_13(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_14(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_15(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_16(CtImRbkRun1* self);
kint32 						ct_im_rbk_run1_rbk_1_17(CtImRbkRun1* self);

T_IM_LTM_RBK_CTRL_COMMON *
								ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(CtImRbkRun1* self);
void 						ct_im_rbk_run1_set_pipe_no(CtImRbkRun1* self, kuchar pipeNo);
kuchar 					ct_im_rbk_run1_get_pipe_no(CtImRbkRun1* self);


#endif /* __CT_IM_RBK_RUN1_H_ */
