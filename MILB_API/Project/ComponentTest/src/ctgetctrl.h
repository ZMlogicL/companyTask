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

#ifndef __CT_GET_CTRL_H_
#define __CT_GET_CTRL_H_

#include <klib.h>

#define CT_TYPE_GET_CTRL						(ct_get_ctrl_get_type())
#define CT_GET_CTRL(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtGetCtrl))
#define CT_IS_GET_CTRL(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_GET_CTRL)) 

typedef struct 			_CtGetCtrl CtGetCtrl;
typedef struct 			_CtGetCtrlPrivate CtGetCtrlPrivate;

struct _CtGetCtrl
{
	KObject parent;
};

KConstType 						ct_get_ctrl_get_type(void);
CtGetCtrl* 							ct_get_ctrl_new(void);

void 									ct_get_ctrl_set_vaule(CtGetCtrl *self,kchar* vaule);
void 									ct_get_ctrl(CtGetCtrl *self);

#endif /* __CT_GET_CTRL_H_ */
