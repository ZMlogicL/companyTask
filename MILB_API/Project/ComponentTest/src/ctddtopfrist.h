/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
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

#ifndef __CT_DD_TOP_FRIST_H_
#define __CT_DD_TOP_FRIST_H_

#include "ctddtopparent.h"

#define CT_TYPE_DD_TOP_FRIST						(ct_dd_top_frist_get_type())
#define CT_DD_TOP_FRIST(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdTopFrist))
#define CT_IS_DD_TOP_FRIST(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_TOP_FRIST)) 

typedef struct 			_CtDdTopFrist CtDdTopFrist;
typedef struct 			_CtDdTopFristPrivate CtDdTopFristPrivate;

struct _CtDdTopFrist
{
	CtDdTopParent parent;
};

KConstType 							ct_dd_top_frist_get_type(void);
CtDdTopFrist* 						ct_dd_top_frist_new(void);

void 										ct_dd_top_frist_pc_test_main(CtDdTopFrist *self);

#endif /* __CT_DD_TOP_FRIST_H_ */
