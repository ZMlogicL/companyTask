/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r8类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_B2R8_H_
#define __CT_IM_B2R8_H_

#include <klib.h>

#define CT_TYPE_IM_B2R8					(ct_im_b2r8_get_type())
#define CT_IM_B2R8(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImB2r8)) 
#define CT_IS_IM_B2R8(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_B2R8)) 

typedef struct 			_CtImB2r8 CtImB2r8;
typedef struct 			_CtImB2r8Private CtImB2r8Private;

struct _CtImB2r8
{
	KObject parent;
	UCHAR pipeNo;

};

KConstType ct_im_b2r8_get_type(void);
CtImB2r8* ct_im_b2r8_new(void);

 kint32 ct_im_b2r8_3_17( CtImB2r8 *self );
 kint32 ct_im_b2r8_3_18( CtImB2r8 *self );
 kint32 ct_im_b2r8_3_19( CtImB2r8 *self );
 kint32 ct_im_b2r8_3_20( CtImB2r8 *self );
 kint32 ct_im_b2r8_3_21( CtImB2r8 *self );
 kint32 ct_im_b2r8_3_22( CtImB2r8 *self );
 kint32 ct_im_b2r8_3_23( CtImB2r8 *self );
 kint32 ct_im_b2r8_3_24( CtImB2r8 *self );
 kint32 ct_im_b2r8_3_25( CtImB2r8 *self );
 kint32 ct_im_b2r8_3_26( CtImB2r8 *self );
 kint32 ct_im_b2r8_3_27( CtImB2r8 *self );


#endif /* __CT_IM_B2R8_H_ */
