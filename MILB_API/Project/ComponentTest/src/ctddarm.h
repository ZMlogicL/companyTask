/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :jianghaodong
*@brief               :CtDdArm类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_ARM_H_
#define __CT_DD_ARM_H_

#include <klib.h>
#include "ddim_typedef.h"

#define CT_TYPE_DD_ARM					(ct_dd_arm_get_type())
#define CT_DD_ARM(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdArm)) 
#define CT_IS_DD_ARM(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_ARM)) 

typedef struct 			_CtDdArm CtDdArm;
typedef struct 			_CtDdArmPrivate CtDdArmPrivate;

struct _CtDdArm
{
	KObject parent;

};

KConstType 		ct_dd_arm_get_type(void);
CtDdArm* 			ct_dd_arm_new(void);

void 					ct_dd_arm_main_main(CtDdArm* self, kint argc, kchar** argv);

#endif /* __CT_DD_ARM_H_ */
