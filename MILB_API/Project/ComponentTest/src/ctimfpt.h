/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 杨文
*@brief : CtImFpt
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_FPT_H__
#define __CT_IM_FPT_H__

// #include "ct_im_fpt.h"
#include "im_fpt.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#include "jdsfpt.h"
#include <stdlib.h>
#include <string.h>
#include <klib.h>
#include "ctimfpt1.h"
#include "ctimfpt2.h"
#include "ctimfpt3.h"


#define CT_TYPE_IM_FPT                  (ct_im_fpt_get_type())
#define CT_IM_FPT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImFpt)) 
#define CT_IS_IM_FPT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_FPT)) 


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// nothing special.


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// nothing special.


/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// nothing special.


/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
#ifdef D_IM_FPT_DEBUG_ON_PC
extern volatile UCHAR gIM_FPT_macro_fake_finish[2];
#endif

#ifdef CO_MSG_PRINT_ON
#define CtImFpt_D_IM_FPT_RESULT(statement)		result = statement
#else
#define CtImFpt_D_IM_FPT_RESULT
#endif


/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef IM_FPT_STATUS_PRINT
extern VOID Im_FPT_Print_Status( VOID );
#endif


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
// nothing special.


#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif



typedef struct _CtImFpt CtImFpt;
typedef struct _CtImFptPrivate CtImFptPrivate;

struct _CtImFpt 
{
	KObject parent;
};


KConstType ct_im_fpt_get_type(void);
CtImFpt* ct_im_fpt_new(void);
CtImFpt* ct_im_fpt_get(void);


/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
extern VOID ct_im_fpt_run( const UINT32 ct_idx_1st, const UINT32 ct_idx_2nd, const UINT32 ct_idx_3rd );
extern VOID ct_im_fpt_main( INT32 argc, CHAR** argv );
VOID ct_im_fpt_handler( UINT32 result, UCHAR ch );
VOID ct_im_fpt_on_pclk( UCHAR ch );
VOID ct_im_fpt_off_pclk( UCHAR ch );
VOID ct_im_fpt_on_hclk( UCHAR ch );
VOID ct_im_fpt_off_hclk( UCHAR ch );
VOID ct_im_fpt_print_mode0_reg( UCHAR ch );
VOID ct_im_fpt_print_mode1_reg( UCHAR ch );
VOID ct_im_fpt_print_mode2_reg( UCHAR ch );
VOID ct_im_fpt_print_mode3_reg( UCHAR ch );
VOID ct_im_fpt_print_all_reg( UCHAR ch );

#endif /* __CT_IM_FPT_H__ */
