/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImImg类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_im_img.h
 * @brief		This is ct header for im_img.c
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_IM_IMG_H__
#define __CT_IM_IMG_H__

#include <klib.h>
#include "driver_common.h"

#define CT_TYPE_IM_IMG                  (ct_im_img_get_type())
#define CT_IM_IMG(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImImg)) 
#define CT_IS_IM_IMG(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IMG)) 

typedef struct                          _CtImImg CtImImg;
typedef struct                          _CtImImgPrivate CtImImgPrivate;

struct _CtImImg {
    KObject         parent;
    kushort         reg;
    kboolean        reg1;
    ImImgMxicmonTyp			mxicmonTyp;
	ImImgMxicmonSts			mxicmonSts;
	ImImgImgpipepswTyp		imgpipeswTyp;
	ImImgImgpipeswSel		imgpipeswSel;
	ImImgSrampdTyp			srampdTyp;
	kboolean				srampdSts;
	kuint32					argv1;
	kushort					argv2;
	kushort					argv3;
};

KConstType      ct_im_img_get_type(void);

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
void            ct_im_img_reg_print(CtImImg *self);
void            ct_im_img_1_01(CtImImg *self);
void            ct_im_img_2_01(CtImImg *self);
void            ct_im_img_2_02(CtImImg *self);
void            ct_im_img_2_03(CtImImg *self);
void            ct_im_img_2_04(CtImImg *self);
void            ct_im_img_2_05(CtImImg *self);
void            ct_im_img_2_06(CtImImg *self);
void            ct_im_img_2_07(CtImImg *self);
void            ct_im_img_2_08(CtImImg *self);
void            ct_im_img_2_09(CtImImg *self);
void            ct_im_img_2_10(CtImImg *self);
void            ct_im_img_2_11(CtImImg *self);
void            ct_im_img_2_12(CtImImg *self);
void            ct_im_img_2_13(CtImImg *self);
void            ct_im_img_2_14(CtImImg *self);
void            ct_im_img_2_15(CtImImg *self);
void            ct_im_img_2_16(CtImImg *self);
void            ct_im_img_2_17(CtImImg *self);
void            ct_im_img_2_18(CtImImg *self);
void            ct_im_img_2_19(CtImImg *self);
void            ct_im_img_2_20(CtImImg *self);
void            ct_im_img_2_21(CtImImg *self);
void            ct_im_img_2_22(CtImImg *self);
void            ct_im_img_2_23(CtImImg *self);
void            ct_im_img_2_24(CtImImg *self);
void            ct_im_img_2_25_26(CtImImg *self);
void            ct_im_img_3_01(CtImImg *self);
void            ct_im_img_3_02(CtImImg *self);
void            ct_im_img_3_03(CtImImg *self);
void            ct_im_img_3_04(CtImImg *self);
void            ct_im_img_3_05(CtImImg *self);
void            ct_im_img_3_06(CtImImg *self);
void            ct_im_img_3_07(CtImImg *self);
void            ct_im_img_3_08(CtImImg *self);
void            ct_im_img_3_09(CtImImg *self);
void            ct_im_img_4_01(CtImImg *self);
void            ct_im_img_4_02(CtImImg *self);
void            ct_im_img_4_03(CtImImg *self);
void            ct_im_img_4_04(CtImImg *self);
void            ct_im_img_4_05(CtImImg *self);
void            ct_im_img_4_06(CtImImg *self);
void            ct_im_img_4_07(CtImImg *self);
void            ct_im_img_main(CtImImg *self, kint32 argc, KType* argv);

CtImImg*        ct_im_img_new(void);

#endif /* __CT_IM_IMG_H__ */
