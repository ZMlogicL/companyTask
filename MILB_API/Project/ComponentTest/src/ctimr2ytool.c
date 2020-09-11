/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yTool
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yTool, ct_im_r2y_tool)
#define CT_IM_R2Y_TOOL_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yToolPrivate, CT_TYPE_IM_R2Y_TOOL))


struct _CtImR2yToolPrivate
{

};


static void ct_im_r2y_tool_constructor(CtImR2yTool *self)
{
//	CtImR2yToolPrivate *priv = CT_IM_R2Y_TOOL_GET_PRIVATE(self);
}

static void ct_im_r2y_tool_destructor(CtImR2yTool *self)
{
//	CtImR2yToolPrivate *priv = CT_IM_R2Y_TOOL_GET_PRIVATE(self);
}


CtImR2yTool* ct_im_r2y_tool_new(void)
{
	CtImR2yTool* self = k_object_new_with_private(CT_TYPE_IM_R2Y_TOOL, sizeof(CtImR2yToolPrivate));

	return self;
}

CtImR2yTool* ct_im_r2y_tool_get(void)
{
	static CtImR2yTool* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_R2Y_TOOL, sizeof(CtImR2yToolPrivate));
	}

	return self;
}
