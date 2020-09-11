/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r5类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_B2R5_H_
#define __CT_IM_B2R5_H_

#include <klib.h>

#define CT_TYPE_IM_B2R5					(ct_im_b2r5_get_type())
#define CT_IM_B2R5(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImB2r5)) 
#define CT_IS_IM_B2R5(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_B2R5)) 

typedef struct 			_CtImB2r5 CtImB2r5;
typedef struct 			_CtImB2r5Private CtImB2r5Private;

struct _CtImB2r5
{
	KObject parent;
	UCHAR pipeNo;

};

KConstType ct_im_b2r5_get_type(void);
CtImB2r5* ct_im_b2r5_new(void);

 kint32 ct_im_b2r5_1_46( CtImB2r5 *self );
 kint32 ct_im_b2r5_1_47( CtImB2r5 *self );
 kint32 ct_im_b2r5_1_48( CtImB2r5 *self );
 kint32 ct_im_b2r5_1_49( CtImB2r5 *self );
 kint32 ct_im_b2r5_1_50( CtImB2r5 *self );
 kint32 ct_im_b2r5_1_51( CtImB2r5 *self );
 kint32 ct_im_b2r5_1_52( CtImB2r5 *self );
 kint32 ct_im_b2r5_1_53( CtImB2r5 *self );
 kint32 ct_im_b2r5_1_54( CtImB2r5 *self );


#endif /* __CT_IM_B2R5_H_ */
