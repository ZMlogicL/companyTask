/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 杨文
*@brief : CtImIipCsc
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_CSC_H__
#define __CT_IM_IIP_CSC_H__


#include <klib.h>
#include "ddim_typedef.h"


#define CT_TYPE_IM_IIP_CSC                  (ct_im_iip_csc_get_type())
#define CT_IM_IIP_CSC(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipCsc)) 
#define CT_IS_IM_IIP_CSC(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_CSC)) 


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


typedef struct _CtImIipCsc CtImIipCsc;
typedef struct _CtImIipCscPrivate CtImIipCscPrivate;

struct _CtImIipCsc 
{
	KObject parent;
};


KConstType ct_im_iip_csc_get_type(void);
CtImIipCsc* ct_im_iip_csc_new(void);
CtImIipCsc* ct_im_iip_csc_get(void);


/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

// CSC Unit
extern INT32 ct_im_iip_csc_7_1_1( VOID );
extern INT32 ct_im_iip_csc_7_1_2( VOID );
extern INT32 ct_im_iip_csc_run_7_1( const UINT32 ctNo3rd );

#ifdef __cplusplus
}
#endif	// __cplusplus


#endif /* __CT_IM_IIP_CSC_H__ */
