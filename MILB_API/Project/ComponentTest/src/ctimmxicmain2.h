/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :jianghaodong
*@brief               :CtImMxicMain2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MXIC_MAIN2_H_
#define __CT_IM_MXIC_MAIN2_H_

#include <klib.h>
#include "ctimmxicmain1.h"

#define CT_TYPE_IM_MXIC_MAIN2					(ct_im_mxic_main2_get_type())
#define CT_IM_MXIC_MAIN2(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImMxicMain2)) 
#define CT_IS_IM_MXIC_MAIN2(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_MXIC_MAIN2)) 

typedef struct 			_CtImMxicMain2 CtImMxicMain2;
typedef struct 			_CtImMxicMain2Private CtImMxicMain2Private;

struct _CtImMxicMain2
{
	KObject parent;
	CtImMxicMain1* ctImMxicMain1;
};

KConstType 			ct_im_mxic_main2_get_type(void);
CtImMxicMain2* 	ct_im_mxic_main2_new(void);

void 						ct_im_mxic_main2(CtImMxicMain2 *self, kint32 argc, kchar** argv);


#endif /* __CT_IM_MXIC_MAIN2_H_ */
