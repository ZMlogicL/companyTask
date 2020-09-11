/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-11
*@author : 陈阳
*@brief : AbsImProPrint
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "absimproprint.h"


K_TYPE_DEFINE_WITH_PRIVATE(AbsImProPrint, abs_im_pro_print)
#define ABS_IM_PRO_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), AbsImProPrintPrivate, ABS_TYPE_IM_PRO_PRINT))


struct _AbsImProPrintPrivate
{

};


static void abs_im_pro_print_constructor(AbsImProPrint *self)
{
	AbsImProPrintPrivate *priv = ABS_IM_PRO_PRINT_GET_PRIVATE(self);
	self->ioPro = &ioPro;
}

static void abs_im_pro_print_destructor(AbsImProPrint *self)
{
	AbsImProPrintPrivate *priv = ABS_IM_PRO_PRINT_GET_PRIVATE(self);
}
