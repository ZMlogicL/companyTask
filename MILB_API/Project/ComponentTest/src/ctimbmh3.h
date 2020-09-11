/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh3类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_BMH3_H_
#define __CT_IM_BMH3_H_

#include <klib.h>

#define CT_TYPE_IM_BMH3					(ct_im_bmh3_get_type())
#define CT_IM_BMH3(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImBmh3)) 
#define CT_IS_IM_BMH3(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_BMH3))

typedef struct 			_CtImBmh3 CtImBmh3;
typedef struct 			_CtImBmh3Private CtImBmh3Private;

struct _CtImBmh3
{
	KObject parent; 
	kuchar channelNo;
};

KConstType 	ct_im_bmh3_get_type(void);
CtImBmh3* 	ct_im_bmh3_new(void);

kint32 				ct_im_bmh3_1_34(CtImBmh3 *self);
kint32 				ct_im_bmh3_1_35(CtImBmh3 *self);
kint32 				ct_im_bmh3_1_36(CtImBmh3 *self);
kint32 				ct_im_bmh3_1_37(CtImBmh3 *self);
kint32 				ct_im_bmh3_1_38(CtImBmh3 *self);
kint32 				ct_im_bmh3_1_39(CtImBmh3 *self);

#endif /* __CT_IM_BMH3_H_ */
