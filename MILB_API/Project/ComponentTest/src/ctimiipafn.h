/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 杨文
*@brief : CtImIipAfn
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_AFN_H__
#define __CT_IM_IIP_AFN_H__


// CT header
#include "ct_im_iip.h"

// im_iip header
#include "im_iip.h"

// MILB register header
#include "jdsiip.h"

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

// for Memory barrier
#include "dd_arm.h"

// for memset
#include <string.h>
#include <klib.h>
#include "ddim_typedef.h"
#include "ctimiipafn1.h"


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#if 1
#include <stdio.h>
#undef CtImIipAfn_DDIM_PRINT
#define CtImIipAfn_DDIM_PRINT(arg)		{DDIM_User_Printf arg;}		/**< printf function inside DDIM */
#endif

// FRECT table size (for VGA 640x480)
#define CtImIipAfn_D_CT_IM_IIP_FRECT_TBL_X_SZ	(64)
#define CtImIipAfn_D_CT_IM_IIP_FRECT_TBL_Y_SZ	(8)
// FRECT table number (for VGA 640x480)
#define CtImIipAfn_D_CT_IM_IIP_FRECT_TBL_X_NUM	(10)		// (640 / 64)
#define CtImIipAfn_D_CT_IM_IIP_FRECT_TBL_Y_NUM	(60)		// (480 / 8)
#define CtImIipAfn_D_CT_IM_IIP_FRECT_TBL_NUM	(CtImIipAfn_D_CT_IM_IIP_FRECT_TBL_X_NUM * \
												 CtImIipAfn_D_CT_IM_IIP_FRECT_TBL_Y_NUM)

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


#define CT_TYPE_IM_IIP_AFN                  (ct_im_iip_afn_get_type())
#define CT_IM_IIP_AFN(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipAfn)) 
#define CT_IS_IM_IIP_AFN(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_AFN)) 


typedef struct _CtImIipAfn CtImIipAfn;
typedef struct _CtImIipAfnPrivate CtImIipAfnPrivate;

struct _CtImIipAfn 
{
	KObject parent;
};


KConstType ct_im_iip_afn_get_type(void);
CtImIipAfn* ct_im_iip_afn_new(void);
CtImIipAfn* ct_im_iip_afn_get(void);


/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

// AFN Unit
extern INT32 ct_im_iip_afn1_3_1_1( VOID );
extern INT32 ct_im_iip_afn1_3_1_2( VOID );
extern INT32 ct_im_iip_afn1_3_1_3( VOID );
extern INT32 ct_im_iip_afn1_run_3_1( const UINT32 ctNo3rd );

extern INT32 ct_im_iip_afn_3_2_1( VOID );
extern INT32 ct_im_iip_afn_3_2_2( VOID );
extern INT32 ct_im_iip_afn_3_2_3( VOID );
extern INT32 ct_im_iip_afn_run_3_2( const UINT32 ctNo3rd );

#ifdef __cplusplus
}
#endif	// __cplusplus


#endif /* __CT_IM_IIP_AFN_H__ */
