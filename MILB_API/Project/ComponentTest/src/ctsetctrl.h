/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
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

#ifndef __CT_SET_CTRL_H_
#define __CT_SET_CTRL_H_

#include "ctddparameter.h"

#define CT_TYPE_SET_CTRL						(ct_set_ctrl_get_type())
#define CT_SET_CTRL(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtSetCtrl))
#define CT_IS_SET_CTRL(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_SET_CTRL)) 

typedef struct 			_CtSetCtrl CtSetCtrl;
typedef struct 			_CtSetCtrlPrivate CtSetCtrlPrivate;

struct _CtSetCtrl
{
	CtDdParameter parent;
};

KConstType 			ct_set_ctrl_get_type(void);
CtSetCtrl* 				ct_set_ctrl_new(void);

void 						ct_set_ctrl(CtSetCtrl *self);

#endif /* __CT_SET_CTRL_H_ */
