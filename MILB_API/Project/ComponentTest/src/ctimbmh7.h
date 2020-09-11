/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh7类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_BMH7_H_
#define __CT_IM_BMH7_H_

#include <klib.h>

#define CT_TYPE_IM_BMH7					(ct_im_bmh7_get_type())
#define CT_IM_BMH7(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImBmh7)) 
#define CT_IS_IM_BMH7(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_BMH7)) 

typedef struct 			_CtImBmh7 CtImBmh7;
typedef struct 			_CtImBmh7Private CtImBmh7Private;

struct _CtImBmh7
{
	KObject parent;
	kuchar channelNo;
};

KConstType 	ct_im_bmh7_get_type(void);
CtImBmh7* 	ct_im_bmh7_new(void);

kint32 				ct_im_bmh7_3_23(CtImBmh7 *self);
kint32 				ct_im_bmh7_3_24(CtImBmh7 *self);
kint32 				ct_im_bmh7_3_25(CtImBmh7 *self);
kint32 				ct_im_bmh7_3_26(CtImBmh7 *self);
kint32 				ct_im_bmh7_3_27(CtImBmh7 *self);
kint32 				ct_im_bmh7_3_28(CtImBmh7 *self);
kint32 				ct_im_bmh7_3_29(CtImBmh7 *self);
kint32 				ct_im_bmh7_3_30(CtImBmh7 *self);
kint32 				ct_im_bmh7_3_31(CtImBmh7 *self);

#endif /* __CT_IM_BMH7_H_ */
