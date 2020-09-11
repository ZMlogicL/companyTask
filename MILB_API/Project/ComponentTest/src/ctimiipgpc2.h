/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhangxinyue
*@brief               :CtImIipGpc2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_IIP_GPC2_H_
#define __CT_IM_IIP_GPC2_H_

#include <klib.h>

#define CT_TYPE_IM_IIP_GPC2				(ct_im_iip_gpc2_get_type())
#define CT_IM_IIP_GPC2(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipGpc2)) 
#define CT_IS_IM_IIP_GPC2(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_GPC2))

typedef struct 			_CtImIipGpc2 CtImIipGpc2;
typedef struct 			_CtImIipGpc2Private CtImIipGpc2Private;

struct _CtImIipGpc2
{
	KObject parent;
};

KConstType 	ct_im_iip_gpc2_get_type(void);
CtImIipGpc2* ct_im_iip_gpc2_new(void);

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

kint32 				ct_im_iip_gpc_13_1_2(CtImIipGpc2* self);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* __CT_IM_IIP_GPC2_H_ */
