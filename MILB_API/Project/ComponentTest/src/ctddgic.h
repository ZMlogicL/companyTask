/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-05
*@author              :jianghaodong
*@brief               :CtDdGic类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_GIC_H_
#define __CT_DD_GIC_H_

#include <klib.h>
#include "ddim_typedef.h"

#define CT_TYPE_DD_GIC					(ct_dd_gic_get_type())
#define CT_DD_GIC(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdGic)) 
#define CT_IS_DD_GIC(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_GIC)) 

typedef struct 			_CtDdGic CtDdGic;
typedef struct 			_CtDdGicPrivate CtDdGicPrivate;

struct _CtDdGic
{
	KObject parent;

};

KConstType		 	ct_dd_gic_get_type(void);
CtDdGic*			 	ct_dd_gic_new(void);

void 					ct_dd_gic_main_main(CtDdGic* self, kint argc, kchar** argv);
//void 					ct_dd_gic_main_main(CtDdGic* self,int argc, char** argv);


#endif /* __CT_DD_GIC_H_ */
