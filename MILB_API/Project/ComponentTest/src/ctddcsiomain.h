/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :杨升柄
*@brief               :CtDdCsioMain类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_CSIO_MAIN_H__
#define __CT_DD_CSIO_MAIN_H__

#include <klib.h>

#define CT_TYPE_DD_CSIO_MAIN					(ct_dd_csio_main_get_type())
#define CT_DD_CSIO_MAIN(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdCsioMain))
#define CT_IS_DD_CSIO_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_CSIO_MAIN)) 

typedef struct 			_CtDdCsioMain CtDdCsioMain;
typedef struct 			_CtDdCsioMainPrivate CtDdCsioMainPrivate;

struct _CtDdCsioMain
{
	KObject parent;
	CtDdCsioMainPrivate* priv;
};

KConstType 		ct_dd_csio_main_get_type(void);
CtDdCsioMain* 	ct_dd_csio_main_new(void);

void 					ct_dd_csio_main_test(CtDdCsioMain* self, kint argc, kchar** argv );

#endif /* __CT_DD_CSIO_MAIN_H__ */
