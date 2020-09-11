/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_BMH1_H_
#define __CT_IM_BMH1_H_

#include <klib.h>
#include "driver_common.h"

#define CT_TYPE_IM_BMH1					(ct_im_bmh1_get_type())
#define CT_IM_BMH1(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImBmh1)) 
#define CT_IS_IM_BMH1(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_BMH1))

typedef struct 			_CtImBmh1 CtImBmh1;
typedef struct 			_CtImBmh1Private CtImBmh1Private;

struct _CtImBmh1
{
	KObject parent;
	kuchar channelNo;
};

KConstType 	ct_im_bmh1_get_type(void);
CtImBmh1* 	ct_im_bmh1_new(void);

kint32 				ct_im_bmh1_1_1(CtImBmh1 *self);
kint32	 			ct_im_bmh1_1_2(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_3(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_4(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_5(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_6(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_7(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_8(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_9(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_10(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_11(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_12(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_13(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_14(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_15(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_16(CtImBmh1 *self);
kint32 				ct_im_bmh1_1_17(CtImBmh1 *self);

#endif /* __CT_IM_BMH1_H_ */
