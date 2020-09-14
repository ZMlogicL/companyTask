/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro70
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro70.h"
#include "impro7print.h"
#include "improdebug.h"
#include "improcallback.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImpro70, ct_impro_7_0)
#define CT_IMPRO_7_0_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro70Private, CT_TYPE_IMPRO_7_0))


struct _CtImpro70Private
{

};


/**
 *IMPL
 */
static void ct_impro_7_0_constructor(CtImpro70 *self)
{
	CtImpro70Private *priv = CT_IMPRO_7_0_GET_PRIVATE(self);
}

static void ct_impro_7_0_destructor(CtImpro70 *self)
{
	CtImpro70Private *priv = CT_IMPRO_7_0_GET_PRIVATE(self);
}


/**
 *PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_0_1(CtImpro70* self, const kuint32 idx)
{
}

void ct_im_pro_7_0_2(CtImpro70* self, const kuint32 idx)
{
}

void ct_im_pro_7_0_3(CtImpro70* self, const kuint32 idx)
{
}

void ct_im_pro_7_0_4(CtImpro70* self, const kuint32 idx)
{
}

void ct_im_pro_7_0_5(CtImpro70* self, const kuint32 idx)
{
}

void ct_im_pro_7_0_6(CtImpro70* self, const kuint32 idx)
{
}

void ct_im_pro_7_0_7(CtImpro70* self, const kuint32 idx)
{
}

void ct_im_pro_7_0_8(CtImpro70* self, const kuint32 idx)
{
}

void ct_im_pro_7_0_9(CtImpro70* self, const kuint32 idx)
{
}
#endif

CtImpro70* ct_impro_7_0_new(void)
{
	CtImpro70* self = k_object_new_with_private(CT_TYPE_IMPRO_7_0, sizeof(CtImpro70Private));

	return self;
}

CtImpro70* ct_impro_7_0_get(void)
{
	static CtImpro70* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_7_0, sizeof(CtImpro70Private));
	}

	return self;
}
