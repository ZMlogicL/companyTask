/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 杨文
*@brief : CtImFpt2
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_FPT2_H__
#define __CT_IM_FPT2_H__


#include <klib.h>


#define CT_TYPE_IM_FPT2                  (ct_im_fpt2_get_type())
#define CT_IM_FPT2(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImFpt2)) 
#define CT_IS_IM_FPT2(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_FPT2)) 


typedef struct _CtImFpt2 CtImFpt2;
typedef struct _CtImFpt2Private CtImFpt2Private;

struct _CtImFpt2 
{
	KObject parent;
};


KConstType ct_im_fpt2_get_type(void);
CtImFpt2* ct_im_fpt2_new(void);
CtImFpt2* ct_im_fpt2_get(void);


/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
extern INT32 ct_im_fpt2_2_1( UCHAR ch );
extern INT32 ct_im_fpt2_2_2( UCHAR ch );
extern INT32 ct_im_fpt2_2_3( UCHAR ch );
extern INT32 ct_im_fpt2_2_4( UCHAR ch );
extern INT32 ct_im_fpt2_2_5( UCHAR ch );
extern INT32 ct_im_fpt2_2_6( UCHAR ch );
extern INT32 ct_im_fpt2_2_7( UCHAR ch );
extern INT32 ct_im_fpt2_2_8( UCHAR ch );
extern INT32 ct_im_fpt2_2_9( UCHAR ch );
extern INT32 ct_im_fpt2_2_10( UCHAR ch );
extern INT32 ct_im_fpt2_2_11( UCHAR ch );
extern INT32 ct_im_fpt2_2_12( UCHAR ch );
extern INT32 ct_im_fpt2_3_1( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_2( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_3( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_4( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_5( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_6( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_7( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_8( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_9( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_10( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_11( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_12( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_13( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_14( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_15( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_16( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_17( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_18( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_19( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_20( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_21( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_22( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_23( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_24( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_25( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_26( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_27( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_28( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_29( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_30( UCHAR pipe_no );
extern INT32 ct_im_fpt2_3_31( UCHAR pipe_no );
INT32 ct_im_fpt2_run_2( UCHAR ch, const UINT32 ctNo2nd );
INT32 ct_im_fpt2_run_3( UCHAR ch, const UINT32 ctNo2nd );


#endif /* __CT_IM_FPT2_H__ */
