/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r4类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_B2R4_H_
#define __CT_IM_B2R4_H_

#include <klib.h>

#define CT_TYPE_IM_B2R4					(ct_im_b2r4_get_type())
#define CT_IM_B2R4(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImB2r4)) 
#define CT_IS_IM_B2R4(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_B2R4)) 

typedef struct 			_CtImB2r4 CtImB2r4;
typedef struct 			_CtImB2r4Private CtImB2r4Private;

struct _CtImB2r4
{
	KObject parent;
	UCHAR pipeNo;

};

KConstType ct_im_b2r4_get_type(void);
CtImB2r4* ct_im_b2r4_new(void);

 kint32 ct_im_b2r4_1_38( CtImB2r4 *self );
 kint32 ct_im_b2r4_1_39( CtImB2r4 *self );
 kint32 ct_im_b2r4_1_40( CtImB2r4 *self );
 kint32 ct_im_b2r4_1_41( CtImB2r4 *self );
 kint32 ct_im_b2r4_1_42( CtImB2r4 *self );
 kint32 ct_im_b2r4_1_43( CtImB2r4 *self );
 kint32 ct_im_b2r4_1_44( CtImB2r4 *self );
 kint32 ct_im_b2r4_1_45( CtImB2r4 *self );

#endif /* __CT_IM_B2R4_H_ */
