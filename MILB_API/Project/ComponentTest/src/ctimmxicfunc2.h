/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :jianghaodong
*@brief               :CtImMxicFunc2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MXIC_FUNC2_H_
#define __CT_IM_MXIC_FUNC2_H_

#include <klib.h>
#include "driver_common.h"

#define CT_TYPE_IM_MXIC_FUNC2					(ct_im_mxic_func2_get_type())
#define CT_IM_MXIC_FUNC2(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImMxicFunc2)) 
#define CT_IS_IM_MXIC_FUNC2(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_MXIC_FUNC2)) 

typedef struct 			_CtImMxicFunc2 CtImMxicFunc2;
typedef struct 			_CtImMxicFunc2Private CtImMxicFunc2Private;

struct _CtImMxicFunc2
{
	KObject parent;
	kuchar unit;
};

KConstType 			ct_im_mxic_func2_get_type(void);
CtImMxicFunc2* 	ct_im_mxic_func2_new(void);

void 						ct_im_mxic_func2_12(CtImMxicFunc2* self);
void 						ct_im_mxic_func2_13(CtImMxicFunc2* self);
void 						ct_im_mxic_func2_14(CtImMxicFunc2* self);
void 						ct_im_mxic_func2_15(CtImMxicFunc2* self);
void 						ct_im_mxic_func2_16(CtImMxicFunc2* self);
void 						ct_im_mxic_func2_17(CtImMxicFunc2* self);
void 						ct_im_mxic_func2_19(CtImMxicFunc2* self);

#endif /* __CT_IM_MXIC_FUNC2_H_ */
