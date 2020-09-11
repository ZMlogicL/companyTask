/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImIipTool
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimiip.h"
#include "ctimiiptool.h"


//K_TYPE_DEFINE_WITH_PRIVATE(CtImIipTool, ct_im_iip_tool)
//#define CT_IM_IIP_TOOL_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIipToolPrivate, CT_TYPE_IM_IIP_TOOL))


struct _CtImIipToolPrivate
{

};


/********
 * IMPL
 */
//static void ct_im_iip_tool_constructor(CtImIipTool *self)
//{
//	CtImIipToolPrivate *priv = CT_IM_IIP_TOOL_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_tool_destructor(CtImIipTool *self)
//{
//	CtImIipToolPrivate *priv = CT_IM_IIP_TOOL_GET_PRIVATE(self);
//}


/**********
 * PUBLIC
 */
CtImIipTool* ct_im_iip_tool_get(void)
{
	static CtImIipTool* self = NULL;

	if (!self) {
//		self = k_object_new_with_private(CT_TYPE_IM_IIP_TOOL, sizeof(CtImIipToolPrivate));
	}

	return self;
}
