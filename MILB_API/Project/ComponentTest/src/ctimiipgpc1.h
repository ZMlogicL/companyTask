/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhangxinyue
*@brief               :CtImIipGpc1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_IIP_GPC1_H_
#define __CT_IM_IIP_GPC1_H_

#include <klib.h>
#include "ddim_typedef.h"

#define CT_TYPE_IM_IIP_GPC1					(ct_im_iip_gpc1_get_type())
#define CT_IM_IIP_GPC1(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipGpc1))
#define CT_IS_IM_IIP_GPC1(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_GPC1)) 

#ifndef CO_CT_IM_IIP_DISABLE
#define CtImIipGpc1_D_GPC_STEPNUM		(5)			// GeneralCalculator0(4) + Register9(1) = 5
#endif //CO_CT_IM_IIP_DISABLE

typedef struct 			_CtImIipGpc1 CtImIipGpc1;
typedef struct 			_CtImIipGpc1Private CtImIipGpc1Private;

struct _CtImIipGpc1
{
	KObject parent;
};

KConstType 		ct_im_iip_gpc1_get_type(void);
CtImIipGpc1* 	ct_im_iip_gpc1_new(void);

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

kint32 					ct_im_iip_gpc_13_1_1(CtImIipGpc1* self);
TImIipParamGpc 		ct_im_iip1_gpc_get_param_gpc_base(CtImIipGpc1 *self);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* __CT_IM_IIP_GPC1_H_ */
