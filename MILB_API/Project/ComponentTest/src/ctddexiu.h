/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-05
*@author              :jianghaodong
*@brief               :CtDdExiu类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_EXIU_H_
#define __CT_DD_EXIU_H_

#include <klib.h>
#include "ddim_typedef.h"

#define CT_TYPE_DD_EXIU					(ct_dd_exiu_get_type())
#define CT_DD_EXIU(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdExiu)) 
#define CT_IS_DD_EXIU(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_EXIU)) 

typedef struct 			_CtDdExiu CtDdExiu;
typedef struct 			_CtDdExiuPrivate CtDdExiuPrivate;

struct _CtDdExiu
{
	KObject parent;

};

KConstType 		ct_dd_exiu_get_type(void);
CtDdExiu* 			ct_dd_exiu_new(void);

void 					Ct_Dd_EXIU_Main(kint argc, kchar** argv);
//void 					ct_dd_exiu_main_main(int argc, char** argv);


#endif /* __CT_DD_EXIU_H_ */
