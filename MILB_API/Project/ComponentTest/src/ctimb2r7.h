/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r7类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_B2R7_H_
#define __CT_IM_B2R7_H_

#include <klib.h>

#define CT_TYPE_IM_B2R7					(ct_im_b2r7_get_type())
#define CT_IM_B2R7(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImB2r7)) 
#define CT_IS_IM_B2R7(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_B2R7)) 

typedef struct 			_CtImB2r7 CtImB2r7;
typedef struct 			_CtImB2r7Private CtImB2r7Private;

struct _CtImB2r7
{
	KObject parent;
	UCHAR pipeNo;
};

KConstType ct_im_b2r7_get_type(void);
CtImB2r7* ct_im_b2r7_new(void);

 kint32 ct_im_b2r7_3_7( CtImB2r7 *self );
 kint32 ct_im_b2r7_3_8( CtImB2r7 *self );
 kint32 ct_im_b2r7_3_9( CtImB2r7 *self );
 kint32 ct_im_b2r7_3_10( CtImB2r7 *self );
 kint32 ct_im_b2r7_3_11( CtImB2r7 *self );

#endif /* __CT_IM_B2R7_H_ */
