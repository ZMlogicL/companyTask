/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
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

#ifndef __CT_DD_COES3_HELP_H_
#define __CT_DD_COES3_HELP_H_

#include <klib.h>

#define CT_TYPE_DD_COES3_HELP						(ct_dd_coes3_help_get_type())
#define CT_DD_COES3_HELP(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdCoes3Help))
#define CT_IS_DD_COES3_HELP(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_COES3_HELP)) 

typedef struct 			_CtDdCoes3Help CtDdCoes3Help;
typedef struct 			_CtDdCoes3HelpPrivate CtDdCoes3HelpPrivate;

struct _CtDdCoes3Help
{
	KObject parent;

};

KConstType 					ct_dd_coes3_help_get_type(void);
CtDdCoes3Help* 			ct_dd_coes3_help_new(void);

CtDdCoes3Help*			ct_dd_coes3_help_new(void);

#endif /* __CT_DD_COES3_HELP_H_ */
