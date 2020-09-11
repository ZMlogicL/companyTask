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

#ifndef __CT_DD_TOP_WRAP_H_
#define __CT_DD_TOP_WRAP_H_

#include <klib.h>
#include<ddim_typedef.h>

#define CT_TYPE_DD_TOP_WRAP					(ct_dd_top_wrap_get_type())
#define CT_DD_TOP_WRAP(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdTopWrap))
#define CT_IS_DD_TOP_WRAP(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_TOP_WRAP)) 

typedef struct 			_CtDdTopWrap CtDdTopWrap;
typedef struct 			_CtDdTopWrapPrivate CtDdTopWrapPrivate;

struct _CtDdTopWrap
{
	KObject parent;
};

KConstType 				ct_dd_top_wrap_get_type(void);
CtDdTopWrap* 			ct_dd_top_wrap_new(void);

void 							ct_dd_top_wrap_pctest(CtDdTopWrap *self,kchar *cmd);

#endif /* __CT_DD_TOP_WRAP_H_ */
