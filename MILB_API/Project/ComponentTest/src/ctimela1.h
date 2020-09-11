/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_ELA1_H_
#define __CT_IM_ELA1_H_

#include <klib.h>
#include "driver_common.h"

#define CT_TYPE_IM_ELA1				(ct_im_ela1_get_type())
#define CT_IM_ELA1(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImEla1)) 
#define CT_IS_IM_ELA1(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_ELA1))

typedef struct 			_CtImEla1 CtImEla1;
typedef struct 			_CtImEla1Private CtImEla1Private;

struct _CtImEla1
{
	KObject parent;
};

KConstType		ct_im_ela1_get_type(void);
CtImEla1* 		ct_im_ela1_new(void);

void 				ct_im_ela1_1_04(CtImEla1 *self);
void 				ct_im_ela1_1_05(CtImEla1 *self);
void 				ct_im_ela1_1_06(CtImEla1 *self);
void 				ct_im_ela1_1_07(CtImEla1 *self);
void 				ct_im_ela1_1_08(CtImEla1 *self);
void 				ct_im_ela1_1_09(CtImEla1 *self);
void 				ct_im_ela1_1_10(CtImEla1 *self);
void 				ct_im_ela1_1_11(CtImEla1 *self);

#endif /* __CT_IM_ELA1_H_ */
