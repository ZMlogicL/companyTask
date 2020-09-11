/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 杨文
*@brief : CtImIipBlend
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_BLEND_H__
#define __CT_IM_IIP_BLEND_H__


#include <klib.h>
#include "ddim_typedef.h"


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */


/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */


/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */


#define CT_TYPE_IM_IIP_BLEND                  (ct_im_iip_blend_get_type())
#define CT_IM_IIP_BLEND(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipBlend)) 
#define CT_IS_IM_IIP_BLEND(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_BLEND)) 


typedef struct _CtImIipBlend CtImIipBlend;
typedef struct _CtImIipBlendPrivate CtImIipBlendPrivate;

struct _CtImIipBlend 
{
	KObject parent;
};


KConstType ct_im_iip_blend_get_type(void);
CtImIipBlend* ct_im_iip_blend_new(void);
CtImIipBlend* ct_im_iip_blend_get(void);


/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

// BLEND Unit
extern INT32 ct_im_iip_blend_6_1_1( VOID );
extern INT32 ct_im_iip_blend_6_2_1( VOID );
extern INT32 ct_im_iip_blend_run_6_1( const UINT32 ct_no_3rd );
extern INT32 ct_im_iip_blend_run_6_2( const UINT32 ct_no_3rd );

#ifdef __cplusplus
}
#endif	// __cplusplus


#endif /* __CT_IM_IIP_BLEND_H__ */
