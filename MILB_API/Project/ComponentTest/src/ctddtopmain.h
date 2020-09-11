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

#ifndef __CT_DD_TOP_MAIN_H_
#define __CT_DD_TOP_MAIN_H_

#include <klib.h>

#define CT_TYPE_DD_TOP_MAIN						(ct_dd_top_main_get_type())
#define CT_DD_TOP_MAIN(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdTopMain))
#define CT_IS_DD_TOP_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_TOP_MAIN)) 

typedef struct 			_CtDdTopMain CtDdTopMain;
typedef struct 			_CtDdTopMainPrivate CtDdTopMainPrivate;

struct _CtDdTopMain
{
	KObject parent;

};

KConstType 						ct_dd_top_main_get_type(void);
CtDdTopMain* 					ct_dd_top_main_new(void);

void 									ct_dd_top_main(CtDdTopMain* self,kint argc, kchar **argv);

#endif /* __CT_DD_TOP_MAIN_H_ */
