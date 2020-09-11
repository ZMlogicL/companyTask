/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :jianghaodong
*@brief               :CtImRbkRun3类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_RBK_RUN3_H_
#define __CT_IM_RBK_RUN3_H_

#include <klib.h>
#include "im_ltm.h"
#include "ctimrbkrun1.h"

#define CT_TYPE_IM_RBK_RUN3					(ct_im_rbk_run3_get_type())
#define CT_IM_RBK_RUN3(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImRbkRun3)) 
#define CT_IS_IM_RBK_RUN3(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_RBK_RUN3)) 

typedef struct 			_CtImRbkRun3 CtImRbkRun3;
typedef struct 			_CtImRbkRun3Private CtImRbkRun3Private;

struct _CtImRbkRun3
{
	KObject parent;
};

KConstType 		ct_im_rbk_run3_get_type(void);
CtImRbkRun3* 	ct_im_rbk_run3_new(void);

kint32 					ct_im_rbk_run3_3_1(CtImRbkRun3* self);
kint32 					ct_im_rbk_run3_3_2(CtImRbkRun3* self);
kint32 					ct_im_rbk_run3_3_3(CtImRbkRun3* self);
kint32 					ct_im_rbk_run3_3_4(CtImRbkRun3* self);
kint32 					ct_im_rbk_run3_3_5(CtImRbkRun3* self);
kint32 					ct_im_rbk_run3_3_6(CtImRbkRun3* self);
kint32 					ct_im_rbk_run3_3_7(CtImRbkRun3* self);
kint32 					ct_im_rbk_run3_3_8(CtImRbkRun3* self);
kint32 					ct_im_rbk_run3_3_9(CtImRbkRun3* self);
kint32 					ct_im_rbk_run3_3_10(CtImRbkRun3* self);
kint32 					ct_im_rbk_run3_3_18(CtImRbkRun3* self);

T_IM_LTM_RBK_CTRL_SDRAM_INPUT *
							ct_im_rbk_run3_get_gct_im_ltm_rbk_ctrl_sdram_in_base(CtImRbkRun3* self);
T_IM_LTM_RBK_OUTDATA_INFO *
							ct_im_rbk_run3_get_gct_im_ltm_rbk_outdata_base(CtImRbkRun3* self);
void 					ct_im_rbk_run3_set_var1(CtImRbkRun3* self, CtImRbkRun1* var1);


#endif /* __CT_IM_RBK_RUN3_H_ */
