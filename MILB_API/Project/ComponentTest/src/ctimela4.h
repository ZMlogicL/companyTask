/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla4类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_ELA4_H_
#define __CT_IM_ELA4_H_

#include <klib.h>

#define CT_TYPE_IM_ELA4				(ct_im_ela4_get_type())
#define CT_IM_ELA4(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImEla4)) 
#define CT_IS_IM_ELA4(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_ELA4))

typedef struct 			_CtImEla4 CtImEla4;
typedef struct 			_CtImEla4Private CtImEla4Private;

struct _CtImEla4
{
	KObject parent;
};

KConstType ct_im_ela4_get_type(void);
CtImEla4* 	ct_im_ela4_new(void);

void 			ct_im_ela4_2_09(CtImEla4 *self);
void 			ct_im_ela4_2_10(CtImEla4 *self);
void 			ct_im_ela4_2_11(CtImEla4 *self);
void 			ct_im_ela4_2_12(CtImEla4 *self);
void 			ct_im_ela4_2_13(CtImEla4 *self);
void 			ct_im_ela4_2_14(CtImEla4 *self);
void 			ct_im_ela4_2_15(CtImEla4 *self);
void 			ct_im_ela4_2_16(CtImEla4 *self);

#endif /* __CT_IM_ELA4_H_ */
