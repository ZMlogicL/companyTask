/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla3类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_ELA3_H_
#define __CT_IM_ELA3_H_

#include <klib.h>

#define CT_TYPE_IM_ELA3				(ct_im_ela3_get_type())
#define CT_IM_ELA3(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImEla3)) 
#define CT_IS_IM_ELA3(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_ELA3))

typedef struct 			_CtImEla3 CtImEla3;
typedef struct 			_CtImEla3Private CtImEla3Private;

struct _CtImEla3
{
	KObject parent;

};

KConstType 	ct_im_ela3_get_type(void);
CtImEla3* 		ct_im_ela3_new(void);

void 				ct_im_ela3_2_01(CtImEla3 *self);
void 				ct_im_ela3_2_02(CtImEla3 *self);
void 				ct_im_ela3_2_03(CtImEla3 *self);
void 				ct_im_ela3_2_04(CtImEla3 *self);
void 				ct_im_ela3_2_05(CtImEla3 *self);
void 				ct_im_ela3_2_06(CtImEla3 *self);
void 				ct_im_ela3_2_07(CtImEla3 *self);
void 				ct_im_ela3_2_08(CtImEla3 *self);
void 				ct_im_ela3_2_08_a(CtImEla3 *self);

#endif /* __CT_IM_ELA3_H_ */
