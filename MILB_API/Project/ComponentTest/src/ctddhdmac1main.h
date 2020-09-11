/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :杨升柄
*@brief               :CtDdHdmac1Main类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_HDMAC1_MAIN_H__
#define __CT_DD_HDMAC1_MAIN_H__

#include <klib.h>

#define CT_TYPE_DD_HDMAC1_MAIN					(ct_dd_hdmac1_main_get_type())
#define CT_DD_HDMAC1_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdHdmac1Main)) 
#define CT_IS_DD_HDMAC1_MAIN(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_HDMAC1_MAIN))

typedef struct 			_CtDdHdmac1Main CtDdHdmac1Main;
typedef struct 			_CtDdHdmac1MainPrivate CtDdHdmac1MainPrivate;

struct _CtDdHdmac1Main
{
	KObject parent;

};

KConstType 				ct_dd_hdmac1_main_get_type(void);
CtDdHdmac1Main* 	ct_dd_hdmac1_main_new(void);

void 							ct_dd_hdmac1_main_test(CtDdHdmac1Main* self, kint argc, kchar** argv);


#endif /* __CT_DD_HDMAC1_MAIN_H__ */
