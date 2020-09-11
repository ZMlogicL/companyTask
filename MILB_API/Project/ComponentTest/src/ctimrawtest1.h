/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈元
*@brief : CtImRawTest1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_RAW_TEST1_H__
#define __CT_IM_RAW_TEST1_H__


#include <klib.h>
#include "driver_common.h"


#define CT_TYPE_IM_RAW_TEST1                  (ct_im_raw_test1_get_type())
#define CT_IM_RAW_TEST1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImRawTest1))
#define CT_IS_IM_RAW_TEST1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_RAW_TEST1))


typedef struct _CtImRawTest1 CtImRawTest1;
typedef struct _CtImRawTest1Private CtImRawTest1Private;


struct _CtImRawTest1
{
	KObject parent;
};


KConstType 			ct_im_raw_test1_get_type(void);
CtImRawTest1* 	ct_im_raw_test1_new(void);

kint32 					ct_im_raw_test1_0(CtImRawTest1* self);
kint32 					ct_im_raw_test1_1(CtImRawTest1* self);
kint32 					ct_im_raw_test1_2(CtImRawTest1* self);
kint32 					ct_im_raw_test1_3(CtImRawTest1* self);
kint32 					ct_im_raw_test1_4(CtImRawTest1* self);
kint32 					ct_im_raw_test1_5(CtImRawTest1* self);
kint32 					ct_im_raw_test1_6(CtImRawTest1* self);
kint32 					ct_im_raw_test1_7(CtImRawTest1* self);
kint32 					ct_im_raw_test1_8(CtImRawTest1* self);
kint32 					ct_im_raw_test1_9(CtImRawTest1* self);
kint32 					ct_im_raw_test1_10(CtImRawTest1* self);
kint32 					ct_im_raw_test1_11(CtImRawTest1* self);
kint32 					ct_im_raw_test1_12(CtImRawTest1* self);
kint32 					ct_im_raw_test1_13(CtImRawTest1* self);
kint32 					ct_im_raw_test1_14(CtImRawTest1* self);
kint32 					ct_im_raw_test1_15(CtImRawTest1* self);
kint32 					ct_im_raw_test1_16(CtImRawTest1* self);
kint32 					ct_im_raw_test1_17(CtImRawTest1* self);
kint32 					ct_im_raw_test1_18(CtImRawTest1* self);
kint32 					ct_im_raw_test1_19(CtImRawTest1* self);
kint32 					ct_im_raw_test1_20(CtImRawTest1* self);
kint32 					ct_im_raw_test1_21(CtImRawTest1* self);
kint32 					ct_im_raw_test1_22(CtImRawTest1* self);
kint32 					ct_im_raw_test1_23(CtImRawTest1* self);
kint32 					ct_im_raw_test1_24(CtImRawTest1* self);
kint32 					ct_im_raw_test1_25(CtImRawTest1* self);
kint32 					ct_im_raw_test1_26(CtImRawTest1* self);
kint32 					ct_im_raw_test1_28(CtImRawTest1* self);
kint32 					ct_im_raw_test1_30(CtImRawTest1* self);
kint32 					ct_im_raw_test1_31(CtImRawTest1* self);
kint32 					ct_im_raw_test1_32(CtImRawTest1* self);
kint32 					ct_im_raw_test1_33(CtImRawTest1* self);
kint32 					ct_im_raw_test1_34(CtImRawTest1* self);

#endif /* __CT_IM_RAW_TEST1_H__ */
