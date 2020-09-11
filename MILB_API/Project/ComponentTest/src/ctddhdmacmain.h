/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :杨升柄
*@brief               :CtDdHdmacMain类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_HDMAC_MAIN_H__
#define __CT_DD_HDMAC_MAIN_H__

#include <klib.h>

#define CT_TYPE_DD_HDMAC_MAIN					(ct_dd_hdmac_main_get_type())
#define CT_DD_HDMAC_MAIN(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdHdmacMain))
#define CT_IS_DD_HDMAC_MAIN(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_HDMAC_MAIN))

typedef struct 			_CtDdHdmacMain CtDdHdmacMain;
typedef struct 			_CtDdHdmacMainPrivate CtDdHdmacMainPrivate;

struct _CtDdHdmacMain
{
	KObject parent;
};

KConstType 				ct_dd_hdmac_main_get_type(void);
CtDdHdmacMain* 		ct_dd_hdmac_main_new(void);

//原来公有方法的更改
void 							ct_dd_hdmac_main_test(CtDdHdmacMain *self, kint argc, kchar** argv);

#endif /* __CT_DD_HDMAC_MAIN_H__ */
