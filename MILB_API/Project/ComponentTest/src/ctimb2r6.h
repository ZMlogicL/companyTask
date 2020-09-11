/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r6类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_B2R6_H_
#define __CT_IM_B2R6_H_

#include <klib.h>

#define CT_TYPE_IM_B2R6					(ct_im_b2r6_get_type())
#define CT_IM_B2R6(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImB2r6)) 
#define CT_IS_IM_B2R6(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_B2R6)) 

typedef struct 			_CtImB2r6 CtImB2r6;
typedef struct 			_CtImB2r6Private CtImB2r6Private;

struct _CtImB2r6
{
	KObject parent;
	UCHAR pipeNo;

};

KConstType ct_im_b2r6_get_type(void);
CtImB2r6* ct_im_b2r6_new(void);

 kint32 ct_im_b2r6_3_1( CtImB2r6 *self );
 kint32 ct_im_b2r6_3_2( CtImB2r6 *self );
 kint32 ct_im_b2r6_3_3( CtImB2r6 *self );
 kint32 ct_im_b2r6_3_4( CtImB2r6 *self );
 kint32 ct_im_b2r6_3_5( CtImB2r6 *self );
 kint32 ct_im_b2r6_3_6( CtImB2r6 *self );

#endif /* __CT_IM_B2R6_H_ */
