/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈元
*@brief : CtImRawTest2
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_RAW_TEST2_H__
#define __CT_IM_RAW_TEST2_H__


#include <klib.h>
#include "driver_common.h"


#define CT_TYPE_IM_RAW_TEST2                  (ct_im_raw_test2_get_type())
#define CT_IM_RAW_TEST2(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImRawTest2))
#define CT_IS_IM_RAW_TEST2(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_RAW_TEST2))


typedef struct _CtImRawTest2 CtImRawTest2;
typedef struct _CtImRawTest2Private CtImRawTest2Private;


typedef struct {
	kuint32 test2Val1;
	kuint32 test2Val2;
	kuint32 test2Val3;
	kuint32 test2Val4;
	kuint32 test2Val5;
	kuint32 test2Val6;
	kuint32 test2Val7;
	kuint32 test2Val8;
}Test2Val;

struct _CtImRawTest2
{
	KObject parent;
};


KConstType ct_im_raw_test2_get_type(void);
CtImRawTest2* ct_im_raw_test2_new(void);

kint32 ct_im_raw_test2_0(CtImRawTest2* self);
kint32 ct_im_raw_test2_1(CtImRawTest2* self);
kint32 ct_im_raw_test2_2(CtImRawTest2* self, kint32 testType);
kint32 ct_im_raw_test2_3(CtImRawTest2* self);
kint32 ct_im_raw_test2_4(CtImRawTest2* self);
kint32 ct_im_raw_test2_5(CtImRawTest2* self);
kint32 ct_im_raw_test2_6(CtImRawTest2* self);
kint32 ct_im_raw_test2_7(CtImRawTest2* self);
kint32 ct_im_raw_test2_8(CtImRawTest2* self);
kint32 ct_im_raw_test2_9(CtImRawTest2* self);
kint32 ct_im_raw_test2_10(CtImRawTest2* self);
kint32 ct_im_raw_test2_11(CtImRawTest2* self);
kint32 ct_im_raw_test2_12(CtImRawTest2* self);
kint32 ct_im_raw_test2_14(CtImRawTest2* self, Test2Val test2Val);

#endif /* __CT_IM_RAW_TEST2_H__ */
