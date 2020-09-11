/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :guguangjian
*@brief               :CtDdRelcMain类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_RELC_MAIN_H__
#define __CT_DD_RELC_MAIN_H__

#include <klib.h>

#define CT_TYPE_DD_RELC_MAIN					(ct_dd_relc_main_get_type())
#define CT_DD_RELC_MAIN(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdRelcMain))
#define CT_IS_DD_RELC_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_RELC_MAIN)) 

typedef struct 													_CtDdRelcMain CtDdRelcMain;
typedef struct 													_CtDdRelcMainPrivate CtDdRelcMainPrivate;

struct _CtDdRelcMain
{
	KObject parent;
};

KConstType 				ct_dd_relc_main_get_type(void);
CtDdRelcMain* 			ct_dd_relc_main_new(void);

void 							ct_dd_relc_main(CtDdRelcMain *self,kint argc, kchar** argv);

#endif /* __CT_DD_RELC_MAIN_H__ */
