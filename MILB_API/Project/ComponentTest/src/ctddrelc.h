/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :guguangjian
*@brief               :CtDdRelc类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_RELC_H__
#define __CT_DD_RELC_H__

#include <klib.h>

#define CT_TYPE_DD_RELC					(ct_dd_relc_get_type())
#define CT_DD_RELC(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdRelc)) 
#define CT_IS_DD_RELC(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_RELC))

typedef struct 										_CtDdRelc CtDdRelc;
typedef struct 										_CtDdRelcPrivate CtDdRelcPrivate;

struct _CtDdRelc
{
	KObject parent;
};

KConstType 				ct_dd_relc_get_type(void);
CtDdRelc* 					ct_dd_relc_new(void);

void 							ct_dd_relc_cmd_cb(kuint32 int_factor);
void 							ct_dd_relc_register_dump(void);
void 							ct_dd_relc_ps_sim(CtDdRelc *self);

#endif /* __CT_DD_RELC_H__ */
