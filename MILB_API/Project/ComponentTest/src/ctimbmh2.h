/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_BMH2_H_
#define __CT_IM_BMH2_H_

#include <klib.h>

#define CT_TYPE_IM_BMH2					(ct_im_bmh2_get_type())
#define CT_IM_BMH2(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImBmh2)) 
#define CT_IS_IM_BMH2(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_BMH2))

typedef struct 			_CtImBmh2 CtImBmh2;
typedef struct 			_CtImBmh2Private CtImBmh2Private;

struct _CtImBmh2
{
	KObject parent;
	kuchar channelNo;
};

KConstType 		ct_im_bmh2_get_type(void);
CtImBmh2* 		ct_im_bmh2_new(void);

kint32 					ct_im_bmh2_1_18(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_19(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_20(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_21(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_22(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_23(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_24(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_25(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_26(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_27(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_28(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_29(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_30(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_31(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_32(CtImBmh2 *self);
kint32 					ct_im_bmh2_1_33(CtImBmh2 *self);


#endif /* __CT_IM_BMH2_H_ */
