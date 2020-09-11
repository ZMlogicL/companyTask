/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 杨文
*@brief : CtImIipCfl
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_CFL_H__
#define __CT_IM_IIP_CFL_H__


#include <klib.h>
#include "ddim_typedef.h"


#define CT_TYPE_IM_IIP_CFL                  (ct_im_iip_cfl_get_type())
#define CT_IM_IIP_CFL(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipCfl)) 
#define CT_IS_IM_IIP_CFL(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_CFL)) 


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


typedef struct _CtImIipCfl CtImIipCfl;
typedef struct _CtImIipCflPrivate CtImIipCflPrivate;

struct _CtImIipCfl 
{
	KObject parent;
};


KConstType ct_im_iip_cfl_get_type(void);
CtImIipCfl* ct_im_iip_cfl_new(void);
CtImIipCfl* ct_im_iip_cfl_get(void);


/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

// CFL Unit
extern INT32 ct_im_iip_cfl_12_1_1( VOID );
extern INT32 ct_im_iip_cfl_12_1_2( VOID );
extern INT32 ct_im_iip_cfl_run_12_1( const UINT32 ctNo3rxd );

#ifdef __cplusplus
}
#endif	// __cplusplus


#endif /* __CT_IM_IIP_CFL_H__ */
