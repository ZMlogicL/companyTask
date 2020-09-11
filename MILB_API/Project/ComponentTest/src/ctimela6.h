/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla6类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_ELA6_H_
#define __CT_IM_ELA6_H_

#include <klib.h>

#define CT_TYPE_IM_ELA6				(ct_im_ela6_get_type())
#define CT_IM_ELA6(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImEla6)) 
#define CT_IS_IM_ELA6(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_ELA6))

typedef struct 			_CtImEla6 CtImEla6;
typedef struct 			_CtImEla6Private CtImEla6Private;

struct _CtImEla6
{
	KObject parent;

};

KConstType 	ct_im_ela6_get_type(void);
CtImEla6* 		ct_im_ela6_new(void);

void 				ct_im_ela6_3_01(CtImEla6 *self);
void 				ct_im_ela6_3_02(CtImEla6 *self);
void 				ct_im_ela6_3_03(CtImEla6 *self);
void 				ct_im_ela6_3_04(CtImEla6 *self);
void 				ct_im_ela6_3_05(CtImEla6 *self);
void 				ct_im_ela6_3_06(CtImEla6 *self);
void 				ct_im_ela6_3_07(CtImEla6 *self);
void 				ct_im_ela6_3_08(CtImEla6 *self);
void 				ct_im_ela6_3_09(CtImEla6 *self);
void 				ct_im_ela6_3_10(CtImEla6 *self);
void 				ct_im_ela6_3_11(CtImEla6 *self);
void 				ct_im_ela6_3_12(CtImEla6 *self);
void 				ct_im_ela6_3_13(CtImEla6 *self);
void 				ct_im_ela6_3_14(CtImEla6 *self);
void 				ct_im_ela6_3_15(CtImEla6 *self);
void 				ct_im_ela6_3_16(CtImEla6 *self);
void 				ct_im_ela6_3_17(CtImEla6 *self);
void 				ct_im_ela6_3_18(CtImEla6 *self);
void 				ct_im_ela6_3_19(CtImEla6 *self);
void 				ct_im_ela6_3_20(CtImEla6 *self);
void 				ct_im_ela6_3_21(CtImEla6 *self);
void 				ct_im_ela6_3_22(CtImEla6 *self);
void 				ct_im_ela6_3_23(CtImEla6 *self);
void 				ct_im_ela6_3_24(CtImEla6 *self);
void 				ct_im_ela6_3_25(CtImEla6 *self);
void 				ct_im_ela6_3_26(CtImEla6 *self);
void 				ct_im_ela6_3_27(CtImEla6 *self);
void 				ct_im_ela6_3_28(CtImEla6 *self);
void 				ct_im_ela6_3_29(CtImEla6 *self);
void 				ct_im_ela6_3_30(CtImEla6 *self);
void 				ct_im_ela6_3_31(CtImEla6 *self);

#endif /* __CT_IM_ELA6_H_ */
