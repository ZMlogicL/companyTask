/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : maoguangkun
*@brief : CtImShdrTools
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimshdr.h"
#include "shdrtest21.h"
#include "ctimshdrtools.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImShdrTools, ct_im_shdr_tools)
#define CT_IM_SHDR_TOOLS_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImShdrToolsPrivate, CT_TYPE_IM_SHDR_TOOLS))


struct _CtImShdrToolsPrivate
{

};


/********
 * IMPL
 */
static void ct_im_shdr_tools_constructor(CtImShdrTools *self)
{
//	CtImShdrToolsPrivate *priv = CT_IM_SHDR_TOOLS_GET_PRIVATE(self);
}

static void ct_im_shdr_tools_destructor(CtImShdrTools *self)
{
//	CtImShdrToolsPrivate *priv = CT_IM_SHDR_TOOLS_GET_PRIVATE(self);
}


/**********
 * PUBLIC
 */
CtImShdrTools* ct_im_shdr_tools_get(void)
{
	static CtImShdrTools* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_SHDR_TOOLS, sizeof(CtImShdrToolsPrivate));
	}

	return self;
}
