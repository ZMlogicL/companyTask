/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :jianghaodong
*@brief               :CtImMxicMain1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MXIC_MAIN1_H_
#define __CT_IM_MXIC_MAIN1_H_

#include <klib.h>
#include "im_mxic.h"

#define CT_TYPE_IM_MXIC_MAIN1					(ct_im_mxic_main1_get_type())
#define CT_IM_MXIC_MAIN1(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImMxicMain1)) 
#define CT_IS_IM_MXIC_MAIN1(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_MXIC_MAIN1)) 

typedef struct 			_CtImMxicMain1 CtImMxicMain1;
typedef struct 			_CtImMxicMain1Private CtImMxicMain1Private;

struct _CtImMxicMain1
{
	KObject parent;

	kint32	result;
	E_IM_MXIC_UNIT							unit;
	T_IM_MXIC_W_ARBITER_ASSIGN_PORT			wSlotStatus;
	T_IM_MXIC_R_ARBITER_ASSIGN_PORT			rSlotStatus;
};

KConstType 			ct_im_mxic_main1_get_type(void);
CtImMxicMain1* 	ct_im_mxic_main1_new(void);

void 						ct_im_mxic_main1(CtImMxicMain1 *self, kint32 argc, kchar** argv);


#endif /* __CT_IM_MXIC_MAIN1_H_ */
