/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 杨文
*@brief : CtImFpt3
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_FPT3_H__
#define __CT_IM_FPT3_H__


#include <klib.h>


#define CT_TYPE_IM_FPT3                  (ct_im_fpt3_get_type())
#define CT_IM_FPT3(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImFpt3)) 
#define CT_IS_IM_FPT3(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_FPT3)) 


typedef struct _CtImFpt3 CtImFpt3;
typedef struct _CtImFpt3Private CtImFpt3Private;

struct _CtImFpt3 
{
	KObject parent;
};


KConstType ct_im_fpt3_get_type(void);
CtImFpt3* ct_im_fpt3_new(void);
CtImFpt3* ct_im_fpt3_get(void);


/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
extern INT32 ct_im_fpt3_4_1( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_2( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_3( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_4( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_5( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_6( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_7( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_8( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_9( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_10( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_11( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_12( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_13( UCHAR pipe_no );
extern INT32 ct_im_fpt3_4_14( UCHAR pipe_no );
INT32 ct_im_fpt3_run_4( UCHAR ch, const UINT32 ctNo2nd );


#endif /* __CT_IM_FPT3_H__ */
