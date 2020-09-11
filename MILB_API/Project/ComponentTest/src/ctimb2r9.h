/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r9类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_B2R9_H_
#define __CT_IM_B2R9_H_

#include <klib.h>

#define CT_TYPE_IM_B2R9					(ct_im_b2r9_get_type())
#define CT_IM_B2R9(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImB2r9)) 
#define CT_IS_IM_B2R9(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_B2R9)) 

typedef struct 			_CtImB2r9 CtImB2r9;
typedef struct 			_CtImB2r9Private CtImB2r9Private;

struct _CtImB2r9
{
	KObject parent;
	UCHAR pipeNo;

};

KConstType ct_im_b2r9_get_type(void);
CtImB2r9* ct_im_b2r9_new(void);

 kint32 ct_im_b2r9_3_28( CtImB2r9 *self );
 kint32 ct_im_b2r9_3_29( CtImB2r9 *self );
 kint32 ct_im_b2r9_3_30( CtImB2r9 *self );
 kint32 ct_im_b2r9_3_31( CtImB2r9 *self );
 kint32 ct_im_b2r9_3_32( CtImB2r9 *self );
 kint32 ct_im_b2r9_3_33( CtImB2r9 *self );
 kint32 ct_im_b2r9_3_34( CtImB2r9 *self );
 kint32 ct_im_b2r9_3_35( CtImB2r9 *self );

#endif /* __CT_IM_B2R9_H_ */
