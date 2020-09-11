/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 杨文
*@brief : CtImFpt1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_FPT1_H__
#define __CT_IM_FPT1_H__


#include <klib.h>


#define CT_TYPE_IM_FPT1                  (ct_im_fpt1_get_type())
#define CT_IM_FPT1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImFpt1)) 
#define CT_IS_IM_FPT1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_FPT1)) 


typedef struct _CtImFpt1 CtImFpt1;
typedef struct _CtImFpt1Private CtImFpt1Private;

struct _CtImFpt1 
{
	KObject parent;
};


KConstType ct_im_fpt1_get_type(void);
CtImFpt1* ct_im_fpt1_new(void);
CtImFpt1* ct_im_fpt1_get(void);


/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
extern INT32 ct_im_fpt1_1_1( UCHAR ch );
extern INT32 ct_im_fpt1_1_2( UCHAR ch );
extern INT32 ct_im_fpt1_1_3( UCHAR ch );
extern INT32 ct_im_fpt1_1_4( UCHAR ch );
extern INT32 ct_im_fpt1_1_5( UCHAR ch );
extern INT32 ct_im_fpt1_1_6( UCHAR ch );
extern INT32 ct_im_fpt1_1_7( UCHAR ch );
extern INT32 ct_im_fpt1_1_8( UCHAR ch );
extern INT32 ct_im_fpt1_1_9( UCHAR ch );
extern INT32 ct_im_fpt1_1_10( UCHAR ch );
extern INT32 ct_im_fpt1_1_11( UCHAR ch );
extern INT32 ct_im_fpt1_1_12( UCHAR ch );
INT32 ct_im_fpt1_run_1( UCHAR ch, const UINT32 ctNo2nd );


#endif /* __CT_IM_FPT1_H__ */
