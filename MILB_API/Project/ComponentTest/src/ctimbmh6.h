/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh6类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_BMH6_H_
#define __CT_IM_BMH6_H_

#include <klib.h>

#define CT_TYPE_IM_BMH6					(ct_im_bmh6_get_type())
#define CT_IM_BMH6(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImBmh6)) 
#define CT_IS_IM_BMH6(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_BMH6)) 

typedef struct 			_CtImBmh6 CtImBmh6;
typedef struct 			_CtImBmh6Private CtImBmh6Private;

struct _CtImBmh6
{
	KObject parent;
	kuchar channelNo;
};

KConstType 	ct_im_bmh6_get_type(void);
CtImBmh6* 	ct_im_bmh6_new(void);

kint32 				ct_im_bmh6_3_11(CtImBmh6 *self);
kint32 				ct_im_bmh6_3_12(CtImBmh6 *self);
kint32 				ct_im_bmh6_3_13(CtImBmh6 *self);
kint32 				ct_im_bmh6_3_14(CtImBmh6 *self);
kint32 				ct_im_bmh6_3_15(CtImBmh6 *self);
kint32 				ct_im_bmh6_3_16(CtImBmh6 *self);
kint32 				ct_im_bmh6_3_17(CtImBmh6 *self);
kint32 				ct_im_bmh6_3_18(CtImBmh6 *self);
kint32 				ct_im_bmh6_3_19(CtImBmh6 *self);
kint32 				ct_im_bmh6_3_20(CtImBmh6 *self);
kint32 				ct_im_bmh6_3_21(CtImBmh6 *self);
kint32 				ct_im_bmh6_3_22(CtImBmh6 *self);

#endif /* __CT_IM_BMH6_H_ */
