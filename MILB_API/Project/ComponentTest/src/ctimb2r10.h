/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-08
*@author              :liudong
*@brief               :CtImB2r10类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_B2R10_H_
#define __CT_IM_B2R10_H_

#include <klib.h>

#define CT_TYPE_IM_B2R10					(ct_im_b2r10_get_type())
#define CT_IM_B2R10(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImB2r10)) 
#define CT_IS_IM_B2R10(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_B2R10)) 

typedef struct 			_CtImB2r10 CtImB2r10;
typedef struct 			_CtImB2r10Private CtImB2r10Private;

struct _CtImB2r10
{
	KObject parent;
	UCHAR pipeNo;

};

KConstType ct_im_b2r10_get_type(void);
CtImB2r10* ct_im_b2r10_new(void);


 kint32 ct_im_b2r10_2_1( CtImB2r10 *self );
 kint32 ct_im_b2r10_2_2( CtImB2r10 *self );

#endif /* __CT_IM_B2R10_H_ */
