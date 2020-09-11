/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla5类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_ELA5_H_
#define __CT_IM_ELA5_H_

#include <klib.h>

#define CT_TYPE_IM_ELA5				(ct_im_ela5_get_type())
#define CT_IM_ELA5(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImEla5)) 
#define CT_IS_IM_ELA5(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_ELA5))

typedef struct 			_CtImEla5 CtImEla5;
typedef struct 			_CtImEla5Private CtImEla5Private;

struct _CtImEla5
{
	KObject parent;

};

KConstType 	ct_im_ela5_get_type(void);
CtImEla5* 		ct_im_ela5_new(void);

void 				ct_im_ela5_2_17(CtImEla5 *self);
void 				ct_im_ela5_2_18(CtImEla5 *self);
void 				ct_im_ela5_2_19(CtImEla5 *self);
void 				ct_im_ela5_2_20(CtImEla5 *self);
void 				ct_im_ela5_2_21(CtImEla5 *self);
void 				ct_im_ela5_2_22(CtImEla5 *self);
void 				ct_im_ela5_2_23(CtImEla5 *self);
void 				ct_im_ela5_2_24(CtImEla5 *self);

#endif /* __CT_IM_ELA5_H_ */
