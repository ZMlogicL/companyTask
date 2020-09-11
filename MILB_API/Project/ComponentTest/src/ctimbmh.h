/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_BMH_H_
#define __CT_IM_BMH_H_

#include <klib.h>
#include "driver_common.h"

#define CT_TYPE_IM_BMH					(ct_im_bmh_get_type())
#define CT_IM_BMH(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImBmh))
#define CT_IS_IM_BMH(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_BMH))

#define CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR	(0x7C000000)
#define CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR	(0x7D000000)

typedef struct 			_CtImBmh CtImBmh;
typedef struct 			_CtImBmhPrivate CtImBmhPrivate;

struct _CtImBmh
{
	KObject parent;
};

KConstType 	ct_im_bmh_get_type(void);
CtImBmh* 		ct_im_bmh_new(void);

void 				ct_im_bmh_print_debug_sadr(CtImBmh *self);
void 				ct_im_bmh_run(CtImBmh *self);
void 				ct_im_bmh_main(CtImBmh *self, kint32 argc, kchar** argv);

#endif /* __CT_IM_BMH_H_ */
