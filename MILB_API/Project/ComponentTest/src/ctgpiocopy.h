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

#ifndef __CT_GPIO_COPY_H_
#define __CT_GPIO_COPY_H_

#include <klib.h>

#define CT_TYPE_GPIO_COPY						(ct_gpio_copy_get_type())
#define CT_GPIO_COPY(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtGpioCopy))
#define CT_IS_GPIO_COPY(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_GPIO_COPY)) 

typedef struct 			_CtGpioCopy CtGpioCopy;
typedef struct 			_CtGpioCopyPrivate CtGpioCopyPrivate;

struct _CtGpioCopy
{
	KObject parent;

};

KConstType 						ct_gpio_copy_get_type(void);
CtGpioCopy* 						ct_gpio_copy_new(void);

#ifdef CtGpio_D_DD_TOP_PC_DEBUG
kint32 									ct_gpio_copy_pdr_pc(CtGpioCopy *self,E_DD_TOP_GPIO_PORT port, kuchar status);
#endif

#endif /* __CT_GPIO_COPY_H_ */
