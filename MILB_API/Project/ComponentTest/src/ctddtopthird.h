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

#ifndef __CT_DD_TOP_THIRD_H_
#define __CT_DD_TOP_THIRD_H_

#include "ctddtopparent.h"

#define CT_TYPE_DD_TOP_THIRD					(ct_dd_top_third_get_type())
#define CT_DD_TOP_THIRD(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdTopThird))
#define CT_IS_DD_TOP_THIRD(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_TOP_THIRD)) 

typedef struct 			_CtDdTopThird CtDdTopThird;
typedef struct 			_CtDdTopThirdPrivate CtDdTopThirdPrivate;

struct _CtDdTopThird
{
	CtDdTopParent parent;

};

KConstType 							ct_dd_top_third_get_type(void);
CtDdTopThird* 						ct_dd_top_third_new(void);

void 										ct_dd_top_third_set_seq_no(CtDdTopThird *self,kint32 seqNo);
kint32 										ct_dd_top_third_get_seq_no(CtDdTopThird *self);
void 										ct_dd_top_third_pc_test_main(CtDdTopThird *self);

#endif /* __CT_DD_TOP_THIRD_H_ */
