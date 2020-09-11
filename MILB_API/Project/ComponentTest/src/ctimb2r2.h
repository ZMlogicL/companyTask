/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_B2R2_H_
#define __CT_IM_B2R2_H_

#include <klib.h>

#define CT_TYPE_IM_B2R2					(ct_im_b2r2_get_type())
#define CT_IM_B2R2(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImB2r2)) 
#define CT_IS_IM_B2R2(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_B2R2)) 

typedef struct 			_CtImB2r2 CtImB2r2;
typedef struct 			_CtImB2r2Private CtImB2r2Private;

struct _CtImB2r2
{
	KObject parent;
	UCHAR pipeNo;

};

KConstType ct_im_b2r2_get_type(void);
CtImB2r2* ct_im_b2r2_new(void);

 kint32 ct_im_b2r2_1_1( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_2( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_3( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_4( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_5( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_6( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_7( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_8( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_9( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_10( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_11( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_12( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_13( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_14( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_15( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_16( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_17( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_18( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_19( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_20( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_21( CtImB2r2 *self );
 kint32 ct_im_b2r2_1_22( CtImB2r2 *self );

#endif /* __CT_IM_B2R2_H_ */
