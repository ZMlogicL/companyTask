/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
*@author              :董如利
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#include "ctddtopparent.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdTopParent, ct_dd_top_parent);
#define CT_DD_TOP_PARENT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdTopParentPrivate,CT_TYPE_DD_TOP_PARENT))

struct _CtDdTopParentPrivate
{
	kint a;
};
/****************
* DECLS
*/
static void 		ct_dd_top_parent_constructor(CtDdTopParent *self);
static void 		ct_dd_top_parent_destructor(CtDdTopParent *self);
/****************
* IMPL
*/
static void ct_dd_top_parent_constructor(CtDdTopParent *self) 
{
//	CtDdTopParentPrivate *priv = CT_DD_TOP_PARENT_GET_PRIVATE(self);
    self->ctDdTopWrap = ct_dd_top_wrap_new();
}

static void ct_dd_top_parent_destructor(CtDdTopParent *self) 
{
//	CtDdTopParentPrivate *priv = CT_DD_TOP_PARENT_GET_PRIVATE(self);
    k_object_unref(self->ctDdTopWrap);
}
/****************
* PUBLIC
*/
void ct_dd_top_parent_set_wrap(CtDdTopParent * self,CtDdTopWrap* ctDdTopWrap)
{
    self->ctDdTopWrap = ctDdTopWrap;
}

CtDdTopWrap* ct_dd_top_parent_get_wrap(CtDdTopParent * self)
{
    return self->ctDdTopWrap;
}

CtDdTopParent* ct_dd_top_parent_new(void) 
{
    CtDdTopParent *self = k_object_new_with_private(CT_TYPE_DD_TOP_PARENT, sizeof(CtDdTopParentPrivate));
    return self;
}
