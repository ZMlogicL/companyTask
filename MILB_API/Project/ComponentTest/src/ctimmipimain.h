/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :jianghaodong
*@brief               :CtImMipiMain类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MIPI_MAIN_H_
#define __CT_IM_MIPI_MAIN_H_

#include <klib.h>
#include "driver_common.h"

#define CT_TYPE_IM_MIPI_MAIN					(ct_im_mipi_main_get_type())
#define CT_IM_MIPI_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImMipiMain)) 
#define CT_IS_IM_MIPI_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_MIPI_MAIN)) 

typedef struct 			_CtImMipiMain CtImMipiMain;
typedef struct 			_CtImMipiMainPrivate CtImMipiMainPrivate;

struct _CtImMipiMain
{
	KObject parent;

};

KConstType 		ct_im_mipi_main_get_type(void);
CtImMipiMain* 	ct_im_mipi_main_new(void);

void 					Ct_Im_Mipi_Main(kint32 argc, kchar** argv);
//void 					ct_im_mipi_main_main(CtImMipiMain* self,int argc, char** argv);

#endif /* __CT_IM_MIPI_MAIN_H_ */
