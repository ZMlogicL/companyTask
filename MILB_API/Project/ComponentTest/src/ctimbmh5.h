/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh5类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_BMH5_H_
#define __CT_IM_BMH5_H_

#include <klib.h>
#include "driver_common.h"

#define CT_TYPE_IM_BMH5					(ct_im_bmh5_get_type())
#define CT_IM_BMH5(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImBmh5)) 
#define CT_IS_IM_BMH5(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_BMH5)) 

typedef struct 			_CtImBmh5 CtImBmh5;
typedef struct 			_CtImBmh5Private CtImBmh5Private;

struct _CtImBmh5
{
	KObject parent;
	kuchar channelNo;
};

KConstType	 	ct_im_bmh5_get_type(void);
CtImBmh5* 	ct_im_bmh5_new(void);

kint32 				ct_im_bmh5_3_1(CtImBmh5 *self);
kint32 				ct_im_bmh5_3_2(CtImBmh5 *self);
kint32 				ct_im_bmh5_3_3(CtImBmh5 *self);
kint32 				ct_im_bmh5_3_4(CtImBmh5 *self);
kint32 				ct_im_bmh5_3_5(CtImBmh5 *self);
kint32 				ct_im_bmh5_3_6(CtImBmh5 *self);
kint32 				ct_im_bmh5_3_7(CtImBmh5 *self);
kint32 				ct_im_bmh5_3_8(CtImBmh5 *self);
kint32 				ct_im_bmh5_3_9(CtImBmh5 *self);
kint32 				ct_im_bmh5_3_10(CtImBmh5 *self);

#endif /* __CT_IM_BMH5_H_ */
