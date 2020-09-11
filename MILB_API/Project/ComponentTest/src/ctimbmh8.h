/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh8类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_BMH8_H_
#define __CT_IM_BMH8_H_

#include <klib.h>

#define CT_TYPE_IM_BMH8					(ct_im_bmh8_get_type())
#define CT_IM_BMH8(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImBmh8)) 
#define CT_IS_IM_BMH8(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_BMH8)) 

typedef struct 			_CtImBmh8 CtImBmh8;
typedef struct 			_CtImBmh8Private CtImBmh8Private;

struct _CtImBmh8
{
	KObject 		parent;
	kuchar 		channelNo;
};

KConstType 	ct_im_bmh8_get_type(void);
CtImBmh8* 	ct_im_bmh8_new(void);

kint32 				ct_im_bmh8_3_32(CtImBmh8 *self);
kint32 				ct_im_bmh8_3_33(CtImBmh8 *self);
kint32 				ct_im_bmh8_3_34(CtImBmh8 *self);
kint32 				ct_im_bmh8_3_35(CtImBmh8 *self);
kint32 				ct_im_bmh8_3_36(CtImBmh8 *self);
kint32 				ct_im_bmh8_3_37(CtImBmh8 *self);

#endif /* __CT_IM_BMH8_H_ */
