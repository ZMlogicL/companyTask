/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r3类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_B2R3_H_
#define __CT_IM_B2R3_H_

#include <klib.h>

#define CT_TYPE_IM_B2R3					(ct_im_b2r3_get_type())
#define CT_IM_B2R3(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImB2r3)) 
#define CT_IS_IM_B2R3(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_B2R3)) 

typedef struct 			_CtImB2r3 CtImB2r3;
typedef struct 			_CtImB2r3Private CtImB2r3Private;

struct _CtImB2r3
{
	KObject parent;
	UCHAR pipeNo;

};

KConstType ct_im_b2r3_get_type(void);
CtImB2r3* ct_im_b2r3_new(void);

 kint32 ct_im_b2r3_1_23( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_24( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_25( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_26( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_27( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_28( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_29( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_30( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_31( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_32( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_33( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_34( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_35( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_36( CtImB2r3 *self );
 kint32 ct_im_b2r3_1_37( CtImB2r3 *self );

#endif /* __CT_IM_B2R3_H_ */
