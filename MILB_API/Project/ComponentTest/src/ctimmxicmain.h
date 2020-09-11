/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :jianghaodong
*@brief               :CtImMxicMain类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MXIC_MAIN_H_
#define __CT_IM_MXIC_MAIN_H_

#include <klib.h>
#include "driver_common.h"

#define CT_TYPE_IM_MXIC_MAIN					(ct_im_mxic_main_get_type())
#define CT_IM_MXIC_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImMxicMain)) 
#define CT_IS_IM_MXIC_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_MXIC_MAIN)) 

typedef struct 			_CtImMxicMain CtImMxicMain;
typedef struct 			_CtImMxicMainPrivate CtImMxicMainPrivate;

struct _CtImMxicMain
{
	KObject parent;

};

KConstType ct_im_mxic_main_get_type(void);
CtImMxicMain* ct_im_mxic_main_new(void);

void Ct_Im_MXIC_Main(kint32 argc, kchar** argv);
//void ct_im_mxic_main_main(kint32 argc, kchar** argv);

#endif /* __CT_IM_MXIC_MAIN_H_ */
