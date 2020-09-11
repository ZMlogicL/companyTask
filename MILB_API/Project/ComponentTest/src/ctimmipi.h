/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :jianghaodong
*@brief               :CtImMipi类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_MIPI_H_
#define __CT_IM_MIPI_H_

#include <klib.h>
#include "driver_common.h"

#define CT_TYPE_IM_MIPI					(ct_im_mipi_get_type())
#define CT_IM_MIPI(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImMipi)) 
#define CT_IS_IM_MIPI(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_MIPI)) 

typedef struct 			_CtImMipi CtImMipi;
typedef struct 			_CtImMipiPrivate CtImMipiPrivate;

struct _CtImMipi
{
	KObject parent;

};

KConstType 	ct_im_mipi_get_type(void);
CtImMipi* 		ct_im_mipi_new(void);

void 				ct_im_mipi_pclk_on(void);
void 				ct_im_mipi_pclk_off(void);
void 				ct_im_mipi_cb(void);

void 				ct_im_mipi_pcsim_test(CtImMipi* self);



#endif /* __CT_IM_MIPI_H_ */
