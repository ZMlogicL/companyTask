/**
 * @file		ct_im_iip_gpc.h
 * @brief		This is ct header for im_iip_gpc.c.
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef _CT_IM_IIP_GPC_H_
#define _CT_IM_IIP_GPC_H_

#include <klib.h>
#include "ddim_typedef.h"

#define CT_TYPE_IM_IIP_GPC					(ct_im_iip_gpc_get_type())
#define CT_IM_IIP_GPC(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipGpc)) 
#define CT_IS_IM_IIP_GPC(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_GPC))

typedef struct 			_CtImIipGpc CtImIipGpc;
typedef struct 			_CtImIipGpcPrivate CtImIipGpcPrivate;

struct _CtImIipGpc
{
	KObject parent;
};

KConstType 	ct_im_iip_gpc_get_type(void);
CtImIipGpc* 	ct_im_iip_gpc_new(void);

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

// GPC Unit
kint32 				ct_im_iip_13_1_3(CtImIipGpc *self);
kint32 				ct_im_iip_13_1_4(CtImIipGpc *self);
kint32 				ct_im_iip_13_1_5(CtImIipGpc *self);
kint32 				ct_im_iip_13_1_6(CtImIipGpc *self);
kint32 				ct_im_iip_13_1_7(CtImIipGpc *self);
kint32 				ct_im_iip_13_1_8(CtImIipGpc *self);
kint32 				ct_im_iip_gpc_run_13_1(CtImIipGpc *self, const kuint32 ct_no_3rd);

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif	// _CT_IM_IIP_GPC_H_

