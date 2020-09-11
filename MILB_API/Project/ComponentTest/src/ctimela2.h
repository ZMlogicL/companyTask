/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_ELA2_H_
#define __CT_IM_ELA2_H_

#include <klib.h>
#include "driver_common.h"

#define CT_TYPE_IM_ELA2				(ct_im_ela2_get_type())
#define CT_IM_ELA2(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImEla2)) 
#define CT_IS_IM_ELA2(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_ELA2))

typedef struct 			_CtImEla2 CtImEla2;
typedef struct 			_CtImEla2Private CtImEla2Private;

struct _CtImEla2
{
	KObject parent;

};

KConstType 	ct_im_ela2_get_type(void);
CtImEla2* 		ct_im_ela2_new(void);

void 				ct_im_ela2_1_12(CtImEla2 *self);
void 				ct_im_ela2_1_13(CtImEla2 *self);
void 				ct_im_ela2_1_14(CtImEla2 *self);
void 				ct_im_ela2_1_15(CtImEla2 *self);
void 				ct_im_ela2_1_16(CtImEla2 *self);
void 				ct_im_ela2_1_17(CtImEla2 *self);
void 				ct_im_ela2_1_18(CtImEla2 *self);
void 				ct_im_ela2_1_19(CtImEla2 *self);
void 				ct_im_ela2_1_20(CtImEla2 *self);
void 				ct_im_ela2_1_21(CtImEla2 *self);
void 				ct_im_ela2_1_22(CtImEla2 *self);
void 				ct_im_ela2_1_23(CtImEla2 *self);
void 				ct_im_ela2_1_24(CtImEla2 *self);
void 				ct_im_ela2_1_25(CtImEla2 *self);

#endif /* __CT_IM_ELA2_H_ */
