/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :杨升柄
*@brief               :CtDdIpcu类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_IPCU_H__
#define __CT_DD_IPCU_H__

#include "ddim_typedef.h"
#include <klib.h>

#define CT_TYPE_DD_IPCU					(ct_dd_ipcu_get_type())
#define CT_DD_IPCU(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdIpcu)) 
#define CT_IS_DD_IPCU(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_IPCU))

typedef struct 			_CtDdIpcu CtDdIpcu;
typedef struct 			_CtDdIpcuPrivate CtDdIpcuPrivate;

//自己结合分解的文件定义的
typedef void (* CtDdIpcuFunc)  (CtDdIpcu *self, kchar* cmd, kpointer userData);

struct _CtDdIpcu
{
	KObject parent;
	CtDdIpcuPrivate *priv;

};

KConstType 	ct_dd_ipcu_get_type(void);
CtDdIpcu* 		ct_dd_ipcu_new(void);

/*
 * 原.c的公有函数，原.h没有声明
 */
void 				ct_dd_ipcu_test_all_2(CtDdIpcu* self);
void 				ct_dd_ipcu_test_all_3(CtDdIpcu* self);
void  				ct_dd_ipcu_set_func(CtDdIpcu *self, CtDdIpcuFunc func, kpointer userData);

#endif /* __CT_DD_IPCU_H__ */
