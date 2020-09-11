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

#ifndef __CT_DD_TOP_PARENT_H_
#define __CT_DD_TOP_PARENT_H_

#include"ctddtopwrap.h"

#define CT_TYPE_DD_TOP_PARENT						(ct_dd_top_parent_get_type())
#define CT_DD_TOP_PARENT(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdTopParent))
#define CT_IS_DD_TOP_PARENT(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_TOP_PARENT)) 

typedef struct 			_CtDdTopParent CtDdTopParent;
typedef struct 			_CtDdTopParentPrivate CtDdTopParentPrivate;

struct _CtDdTopParent
{
	KObject parent;
	CtDdTopWrap* ctDdTopWrap;
};

KConstType 						ct_dd_top_parent_get_type(void);
CtDdTopParent* 				ct_dd_top_parent_new(void);

void 									ct_dd_top_parent_set_wrap(CtDdTopParent * self,CtDdTopWrap* ctDdTopWrap);
CtDdTopWrap* 					ct_dd_top_parent_get_wrap(CtDdTopParent * self);

#endif /* __CT_DD_TOP_PARENT_H_ */
