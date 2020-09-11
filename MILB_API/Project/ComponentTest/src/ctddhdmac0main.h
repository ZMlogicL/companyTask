/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :杨升柄
*@brief               :CtDdHdmac0Main类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_HDMAC0_MAIN_H__
#define __CT_DD_HDMAC0_MAIN_H__

#include <klib.h>

#define CT_TYPE_DD_HDMAC0_MAIN					(ct_dd_hdmac0_main_get_type())
#define CT_DD_HDMAC0_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdHdmac0Main)) 
#define CT_IS_DD_HDMAC0_MAIN(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_HDMAC0_MAIN))

typedef struct 			_CtDdHdmac0Main CtDdHdmac0Main;
typedef struct 			_CtDdHdmac0MainPrivate CtDdHdmac0MainPrivate;

struct _CtDdHdmac0Main
{
	KObject parent;
};

KConstType 				ct_dd_hdmac0_main_get_type(void);
CtDdHdmac0Main* 	ct_dd_hdmac0_main_new(void);

void 							ct_dd_hdmac0_main_test(CtDdHdmac0Main* self, kint argc, kchar** argv);

#endif /* __CT_DD_HDMAC0_MAIN_H__ */
