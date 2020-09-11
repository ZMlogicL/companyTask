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
 * @file		ct_im_img.c
 * @brief		This is ct code for im_img.c
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include "jdsimg.h"
#include "imimg.h"
#include "stdlib.h"
#include "string.h"
#include "driver_common.h"
#include "ctimimg.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImImg, ct_im_img);
#define CT_IM_IMG_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImImgPrivate,CT_TYPE_IM_IMG))

struct _CtImImgPrivate {
	CtImImg *ciImg;
	ImImg 	*imImg;
};

static void ct_im_img_constructor(CtImImg *self) 
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	priv->ciImg = ct_im_img_new();
	priv->imImg = im_img_new();
}

static void ct_im_img_destructor(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	if(priv->ciImg) {
		k_object_unref(priv->ciImg);
	}
	priv->ciImg = NULL;

	if(priv->imImg){
		k_object_unref(priv->imImg);
	}
	priv->imImg = NULL;
}

/*PUBLIC*/

void ct_im_img_reg_print(CtImImg *self)
{
	Ddim_Print(("---------------------------------\n"));
	Ddim_Print(("  Display MXICMON Register Value\n"));
	Ddim_Print(("---------------------------------\n"));
	Ddim_Print(("MXICMON.VDEN      = %d\n", ioImg.mxicmon.bit.vden));
	Ddim_Print(("MXICMON.HDEN      = %d\n", ioImg.mxicmon.bit.hden));
	Ddim_Print(("MXICMON.SENEN     = %d\n", ioImg.mxicmon.bit.senen));
	Ddim_Print(("MXICMON.SRO1EN    = %d\n", ioImg.mxicmon.bit.sro1en));
	Ddim_Print(("MXICMON.SRO2EN    = %d\n", ioImg.mxicmon.bit.sro2en));
	Ddim_Print(("MXICMON.B2B1EN    = %d\n", ioImg.mxicmon.bit.b2b1en));
	Ddim_Print(("MXICMON.B2B2EN    = %d\n", ioImg.mxicmon.bit.b2b2en));
	Ddim_Print(("MXICMON.YO1EN     = %d\n", ioImg.mxicmon.bit.yo1en));
	Ddim_Print(("MXICMON.YO2EN     = %d\n", ioImg.mxicmon.bit.yo2en));
	Ddim_Print(("MXICMON.STATEN    = %d\n", ioImg.mxicmon.bit.staten));
	Ddim_Print(("MXICMON.PASEN     = %d\n", ioImg.mxicmon.bit.pasen));
	Ddim_Print(("MXICMON.DEN       = %d\n", ioImg.mxicmon.bit.den));
	Ddim_Print(("------------------------------------\n"));
	Ddim_Print(("  Display IMGPIPEPSW Register Value\n"));
	Ddim_Print(("------------------------------------\n"));
	Ddim_Print(("IMGPIPEPSW.R2YSEL = %d\n", ioImg.imgpipepsw.bit.r2ysel));
	Ddim_Print(("IMGPIPEPSW.B2RCNC = %d\n", ioImg.imgpipepsw.bit.b2rcnc));
	Ddim_Print(("------------------------------------\n"));
	Ddim_Print(("  Display SRAMPD Register Value\n"));
	Ddim_Print(("------------------------------------\n"));
	Ddim_Print(("SRAMPD.JPEGPD = %d\n", ioImg.srampd.bit.jpegpd));
	Ddim_Print(("\n"));
}

void ct_im_img_1_01(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_init(priv->imImg);

	Ddim_Print(("ct_im_img_1_01\n"));
	ct_im_img_reg_print(priv->ciImg);
}

void ct_im_img_2_01(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_VDEN, ImImg_MXICMON_DISABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_VDEN);

	Ddim_Print(("ct_im_img_2_01\n"));
	Ddim_Print(("MXICMON.VDEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_02(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_VDEN, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_VDEN);

	Ddim_Print(("ct_im_img_2_02\n"));
	Ddim_Print(("MXICMON.VDEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_03(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_HDEN, ImImg_MXICMON_DISABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_HDEN);

	Ddim_Print(("ct_im_img_2_03\n"));
	Ddim_Print(("MXICMON.HDEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_04(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_HDEN, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_HDEN);

	Ddim_Print(("ct_im_img_2_04\n"));
	Ddim_Print(("MXICMON.HDEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_05(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_SENEN, ImImg_MXICMON_DISABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_SENEN);

	Ddim_Print(("ct_im_img_2_05\n"));
	Ddim_Print(("MXICMON.SEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_06(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_SENEN, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_SENEN);

	Ddim_Print(("ct_im_img_2_06\n"));
	Ddim_Print(("MXICMON.SEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_07(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_SRO1EN, ImImg_MXICMON_DISABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_SRO1EN);

	Ddim_Print(("ct_im_img_2_07\n"));
	Ddim_Print(("MXICMON.SRO1EN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_08(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_SRO1EN, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_SRO1EN);

	Ddim_Print(("ct_im_img_2_08\n"));
	Ddim_Print(("MXICMON.SRO1EN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_09(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_SRO2EN, ImImg_MXICMON_DISABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_SRO2EN);

	Ddim_Print(("ct_im_img_2_09\n"));
	Ddim_Print(("MXICMON.SRO2EN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_10(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_SRO2EN, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_SRO2EN);

	Ddim_Print(("ct_im_img_2_10\n"));
	Ddim_Print(("MXICMON.SRO2EN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_11(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_B2B1EN, ImImg_MXICMON_DISABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_B2B1EN);

	Ddim_Print(("ct_im_img_2_11\n"));
	Ddim_Print(("MXICMON.B2B1EN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_12(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_B2B1EN, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_B2B1EN);

	Ddim_Print(("ct_im_img_2_12\n"));
	Ddim_Print(("MXICMON.B2B1EN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_13(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_B2B2EN, ImImg_MXICMON_DISABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_B2B2EN);

	Ddim_Print(("ct_im_img_2_13\n"));
	Ddim_Print(("MXICMON.B2B2EN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_14(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_B2B2EN, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_B2B2EN);

	Ddim_Print(("ct_im_img_2_14\n"));
	Ddim_Print(("MXICMON.B2B2EN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_15(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_YO1EN, ImImg_MXICMON_DISABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_YO1EN);

	Ddim_Print(("ct_im_img_2_15\n"));
	Ddim_Print(("MXICMON.Y01EN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_16(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_YO1EN, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_YO1EN);

	Ddim_Print(("ct_im_img_2_16\n"));
	Ddim_Print(("MXICMON.Y01EN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_17(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_YO2EN, ImImg_MXICMON_DISABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_YO2EN);

	Ddim_Print(("ct_im_img_2_17\n"));
	Ddim_Print(("MXICMON.Y02EN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_18(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_YO2EN, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_YO2EN);

	Ddim_Print(("ct_im_img_2_18\n"));
	Ddim_Print(("MXICMON.Y02EN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_19(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_STATEN, ImImg_MXICMON_DISABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_STATEN);

	Ddim_Print(("ct_im_img_2_19\n"));
	Ddim_Print(("MXICMON.STATEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_20(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_STATEN, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_STATEN);

	Ddim_Print(("ct_im_img_2_20\n"));
	Ddim_Print(("MXICMON.STATEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_21(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_PASEN, ImImg_MXICMON_DISABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_PASEN);

	Ddim_Print(("ct_im_img_2_21\n"));
	Ddim_Print(("MXICMON.PASEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_22(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_PASEN, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_PASEN);

	Ddim_Print(("ct_im_img_2_22\n"));
	Ddim_Print(("MXICMON.PASEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_23(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_DEN, ImImg_MXICMON_DISABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_DEN);

	Ddim_Print(("ct_im_img_2_23\n"));
	Ddim_Print(("MXICMON.DEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_24(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_DEN, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_DEN);

	Ddim_Print(("ct_im_img_2_24\n"));
	Ddim_Print(("MXICMON.DEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_2_25_26(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_mxicmon(priv->imImg, (ImImgMxicmonTyp)12, ImImg_MXICMON_ENABLE);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_DEN);

	Ddim_Print(("ct_im_img_2_25\n"));
	Ddim_Print(("MXICMON.DEN = %d\n", self->reg));
	Ddim_Print(("\n"));

	im_img_set_mxicmon(priv->imImg, ImImg_MXICMON_DEN, (ImImgMxicmonSts)2);
	self->reg = im_img_get_mxicmon(priv->imImg, ImImg_MXICMON_DEN);

	Ddim_Print(("ct_im_img_2_26\n"));
	Ddim_Print(("MXICMON.DEN = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_3_01(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_R2YSEL, ImImg_IMGPIPEPSW_B2R);
	self->reg = im_img_get_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_R2YSEL);

	Ddim_Print(("ct_im_img_3_01\n"));
	Ddim_Print(("IMGPIPEPSW.R2YSEL = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_3_02(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_R2YSEL, ImImg_IMGPIPEPSW_LTM);
	self->reg = im_img_get_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_R2YSEL);

	Ddim_Print(("ct_im_img_3_02\n"));
	Ddim_Print(("IMGPIPEPSW.R2YSEL = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_3_03(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_R2YSEL, ImImg_IMGPIPEPSW_NONE);
	self->reg = im_img_get_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_R2YSEL);

	Ddim_Print(("ct_im_img_3_03\n"));
	Ddim_Print(("IMGPIPEPSW.R2YSEL = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_3_04(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_R2YSEL, (ImImgImgpipeswSel)3);
	self->reg = im_img_get_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_R2YSEL);

	Ddim_Print(("ct_im_img_3_04\n"));
	Ddim_Print(("IMGPIPEPSW.R2YSEL = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_3_05(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_B2RCNC, ImImg_IMGPIPEPSW_B2R);
	self->reg = im_img_get_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_B2RCNC);

	Ddim_Print(("ct_im_img_3_05\n"));
	Ddim_Print(("IMGPIPEPSW.B2RCNC = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_3_06(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_B2RCNC, ImImg_IMGPIPEPSW_LTM);
	self->reg = im_img_get_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_B2RCNC);

	Ddim_Print(("ct_im_img_3_06\n"));
	Ddim_Print(("IMGPIPEPSW.B2RCNC = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_3_07(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_B2RCNC, ImImg_IMGPIPEPSW_NONE);
	self->reg = im_img_get_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_B2RCNC);

	Ddim_Print(("ct_im_img_3_07\n"));
	Ddim_Print(("IMGPIPEPSW.B2RCNC = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_3_08(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_B2RCNC, (ImImgImgpipeswSel)3);
	self->reg = im_img_get_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_B2RCNC);

	Ddim_Print(("ct_im_img_3_08\n"));
	Ddim_Print(("IMGPIPEPSW.B2RCNC = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_3_09(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_imgpipepsw(priv->imImg, (ImImgImgpipepswTyp)2, ImImg_IMGPIPEPSW_NONE);
	self->reg = im_img_get_imgpipepsw(priv->imImg, ImImg_IMGPIPEPSW_B2RCNC);

	Ddim_Print(("ct_im_img_3_09\n"));
	Ddim_Print(("IMGPIPEPSW.B2RCNC = %d\n", self->reg));
	Ddim_Print(("\n"));
}

void ct_im_img_4_01(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_srampd(priv->imImg, ImImg_SRAMPD_Y01, TRUE);
	self->reg1 = im_img_get_srampd(priv->imImg, ImImg_SRAMPD_Y01);

	Ddim_Print(("ct_im_img_4_01\n"));
	Ddim_Print(("SRAMPD.JPEGPD(Y01) = %d\n", self->reg1));
	Ddim_Print(("\n"));
}

void ct_im_img_4_02(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_srampd(priv->imImg, ImImg_SRAMPD_Y01, FALSE);
	self->reg1 = im_img_get_srampd(priv->imImg, ImImg_SRAMPD_Y01);

	Ddim_Print(("ct_im_img_4_02\n"));
	Ddim_Print(("SRAMPD.JPEGPD(Y01) = %d\n", self->reg1));
	Ddim_Print(("\n"));
}

void ct_im_img_4_03(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_srampd(priv->imImg, ImImg_SRAMPD_Y23, TRUE);
	self->reg1 = im_img_get_srampd(priv->imImg, ImImg_SRAMPD_Y23);

	Ddim_Print(("ct_im_img_4_03\n"));
	Ddim_Print(("SRAMPD.JPEGPD(Y23) = %d\n", self->reg1));
	Ddim_Print(("\n"));
}

void ct_im_img_4_04(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_srampd(priv->imImg, ImImg_SRAMPD_Y23, FALSE);
	self->reg1 = im_img_get_srampd(priv->imImg, ImImg_SRAMPD_Y23);

	Ddim_Print(("ct_im_img_4_04\n"));
	Ddim_Print(("SRAMPD.JPEGPD(Y23) = %d\n", self->reg1));
	Ddim_Print(("\n"));
}

void ct_im_img_4_05(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_srampd(priv->imImg, ImImg_SRAMPD_C, TRUE);
	self->reg1 = im_img_get_srampd(priv->imImg, ImImg_SRAMPD_C);

	Ddim_Print(("ct_im_img_4_05\n"));
	Ddim_Print(("SRAMPD.JPEGPD(C) = %d\n", self->reg1));
	Ddim_Print(("\n"));
}

void ct_im_img_4_06(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_srampd(priv->imImg, ImImg_SRAMPD_C, FALSE);
	self->reg1 = im_img_get_srampd(priv->imImg, ImImg_SRAMPD_C);

	Ddim_Print(("ct_im_img_4_06\n"));
	Ddim_Print(("SRAMPD.JPEGPD(C) = %d\n", self->reg1));
	Ddim_Print(("\n"));
}

void ct_im_img_4_07(CtImImg *self)
{
	CtImImgPrivate *priv = CT_IM_IMG_GET_PRIVATE(self);
	im_img_set_srampd((priv->imImg, ImImgSrampdTyp)3, FALSE);
	self->reg1 = im_img_get_srampd(priv->imImg, ImImg_SRAMPD_C);

	Ddim_Print(("ct_im_img_4_07\n"));
	Ddim_Print(("SRAMPD.JPEGPD(C) = %d\n", self->reg1));
	Ddim_Print(("\n"));
}

void ct_im_img_main(CtImImg *self, kint32 argc, KType* argv)
{
	CtImImgPrivate 			*priv = CT_IM_IMG_GET_PRIVATE(self);
	
	if(argc < 4) {
		Ddim_Print(("ct_im_img_main: parameter error.\n"));
		return;
	}

	Ddim_Print(("img command execute\n"));

	self->argv1 = (kuint32)atoi((KConstType)argv[1]);
	self->argv2 = (kushort)atoi((KConstType)argv[2]);
	self->argv3 = (kushort)atoi((KConstType)argv[3]);

	switch (self->argv1) {
		case 1:	/* initialize */
			if (self->argv2 == 1) {
				ct_im_img_1_01(priv->ciImg);
			}
			else if (self->argv2 == 2) {
				ct_im_img_reg_print(priv->ciImg);
			}
			else {
				Ddim_Print(("input parameter error\n"));
			}
			break;

		case 2:	/* MXICMON Register Set */
			/* ----------------------------------------------
				<MXICMON Type>
					MXICMON.VDEN	: 0
					MXICMON.HDEN	: 1
					MXICMON.SENEN	: 2
					MXICMON.SRO1EN	: 3
					MXICMON.SRO2EN	: 4
					MXICMON.B2B1EN	: 5
					MXICMON.B2B2EN	: 6
					MXICMON.YO1EN	: 7
					MXICMON.YO2EN	: 8
					MXICMON.STATEN	: 9
					MXICMON.PASEN	: 10
					MXICMON.DEN		: 11
			------------------------------------------------
				<enable/disable status>
					Disable			: 0
					Enable			: 1
			------------------------------------------------
			*/

			self->mxicmonTyp = (ImImgMxicmonTyp)self->argv2;
			self->mxicmonSts = (ImImgMxicmonSts)self->argv3;

			switch (self->mxicmonTyp) {
				case ImImg_MXICMON_VDEN:
					if (self->mxicmonSts == ImImg_MXICMON_DISABLE) {
						ct_im_img_2_01(priv->ciImg);
					}
					else {
						ct_im_img_2_02(priv->ciImg);
					}
					break;
				case ImImg_MXICMON_HDEN:
					if (self->mxicmonSts == ImImg_MXICMON_DISABLE) {
						ct_im_img_2_03(priv->ciImg);
					}
					else {
						ct_im_img_2_04(priv->ciImg);
					}
					break;
				case ImImg_MXICMON_SENEN:
					if (self->mxicmonSts == ImImg_MXICMON_DISABLE) {
						ct_im_img_2_05(priv->ciImg);
					}
					else {
						ct_im_img_2_06(priv->ciImg);
					}
					break;
				case ImImg_MXICMON_SRO1EN:
					if (self->mxicmonSts == ImImg_MXICMON_DISABLE) {
						ct_im_img_2_07(priv->ciImg);
					}
					else {
						ct_im_img_2_08(priv->ciImg);
					}
					break;
				case ImImg_MXICMON_SRO2EN:
					if (self->mxicmonSts == ImImg_MXICMON_DISABLE) {
						ct_im_img_2_09(priv->ciImg);
					}
					else {
						ct_im_img_2_10(priv->ciImg);
					}
					break;
				case ImImg_MXICMON_B2B1EN:
					if (self->mxicmonSts == ImImg_MXICMON_DISABLE) {
						ct_im_img_2_11(priv->ciImg);
					}
					else {
						ct_im_img_2_12(priv->ciImg);
					}
					break;
				case ImImg_MXICMON_B2B2EN:
					if (self->mxicmonSts == ImImg_MXICMON_DISABLE) {
						ct_im_img_2_13(priv->ciImg);
					}
					else {
						ct_im_img_2_14(priv->ciImg);
					}
					break;
				case ImImg_MXICMON_YO1EN:
					if (self->mxicmonSts == ImImg_MXICMON_DISABLE) {
						ct_im_img_2_15(priv->ciImg);
					}
					else {
						ct_im_img_2_16(priv->ciImg);
					}
					break;
				case ImImg_MXICMON_YO2EN:
					if (self->mxicmonSts == ImImg_MXICMON_DISABLE) {
						ct_im_img_2_17(priv->ciImg);
					}
					else {
						ct_im_img_2_18(priv->ciImg);
					}
					break;
				case ImImg_MXICMON_STATEN:
					if (self->mxicmonSts == ImImg_MXICMON_DISABLE) {
						ct_im_img_2_19(priv->ciImg);
					}
					else {
						ct_im_img_2_20(priv->ciImg);
					}
					break;
				case ImImg_MXICMON_PASEN:
					if (self->mxicmonSts == ImImg_MXICMON_DISABLE) {
						ct_im_img_2_21(priv->ciImg);
					}
					else {
						ct_im_img_2_22(priv->ciImg);
					}
					break;
				case ImImg_MXICMON_DEN:
					if (self->mxicmonSts == ImImg_MXICMON_DISABLE) {
						ct_im_img_2_23(priv->ciImg);
					}
					else {
						ct_im_img_2_24(priv->ciImg);
					}
					break;
				default :
					ct_im_img_2_25_26(priv->ciImg);
					break;
			}
			break;

		case 3:	/* IMGPIPEPSW Register Set. */
			/* ----------------------------------------------
				<IMGPIPEPSW Type>
					IMGPIPEPSW.R2YSEL	: 0
				<Status>
					R2Y input B2R		: 0
					R2Y input LTM		: 1
					R2Y input None		: 2

				<IMGPIPEPSW Type>
					IMGPIPEPSW.B2RCNC	: 1
				<Status>
					B2R connection None	: 0
					B2R connection LTM	: 1
					B2R connection None	: 2
			------------------------------------------------
			*/

			self->imgpipeswTyp = (ImImgImgpipepswTyp)self->argv2;
			self->imgpipeswSel = (ImImgImgpipeswSel)self->argv3;

			switch (self->imgpipeswTyp) {
				case ImImg_IMGPIPEPSW_R2YSEL:
					if (self->imgpipeswSel == ImImg_IMGPIPEPSW_B2R) {
						ct_im_img_3_01(priv->ciImg);
					}
					else if (self->imgpipeswSel == ImImg_IMGPIPEPSW_LTM) {
						ct_im_img_3_02(priv->ciImg);
					}
					else if (self->imgpipeswSel == ImImg_IMGPIPEPSW_NONE) {
						ct_im_img_3_03(priv->ciImg);
					}
					else {
						ct_im_img_3_04(priv->ciImg);
					}
					break;
				case ImImg_IMGPIPEPSW_B2RCNC:
					if (self->imgpipeswSel == ImImg_IMGPIPEPSW_B2R) {
						ct_im_img_3_05(priv->ciImg);
					}
					else if (self->imgpipeswSel == ImImg_IMGPIPEPSW_LTM) {
						ct_im_img_3_06(priv->ciImg);
					}
					else if (self->imgpipeswSel == ImImg_IMGPIPEPSW_NONE) {
						ct_im_img_3_07(priv->ciImg);
					}
					else {
						ct_im_img_3_08(priv->ciImg);
					}
					break;
				default:
					ct_im_img_3_09(priv->ciImg);
					break;
			}
			break;

		case 4:	/* SRAMPD Register Set */
			/* ----------------------------------------------
				<SRAMPD Type>
					ImImg_SRAMPD_Y01	: 0
					ImImg_SRAMPD_Y23	: 1
					ImImg_SRAMPD_C	: 2
			------------------------------------------------
				<SRAMPD status>
					Power down off	: 0
					Power down on	: 1
			------------------------------------------------
			*/

			self->srampdTyp = (ImImgSrampdTyp)self->argv2;
			self->srampdSts = (kboolean)self->argv3;

			switch (self->srampdTyp) {
				case ImImg_SRAMPD_Y01:
					if (self->srampdSts) {
						ct_im_img_4_01(priv->ciImg);
					}
					else {
						ct_im_img_4_02(priv->ciImg);
					}
					break;
				case ImImg_SRAMPD_Y23:
					if (self->srampdSts) {
						ct_im_img_4_03(priv->ciImg);
					}
					else {
						ct_im_img_4_04(priv->ciImg);
					}
					break;
				case ImImg_SRAMPD_C:
					if (self->srampdSts) {
						ct_im_img_4_05(priv->ciImg);
					}
					else {
						ct_im_img_4_06(priv->ciImg);
					}
					break;
				default:
					ct_im_img_4_07(priv->ciImg);
					break;
			}
			break;

		default:
			/* Nothing special */
			break;
	}

	Ddim_Print(("img command complete\n"));
	return;
}

CtImImg *ct_im_img_new(void)
{
    CtImImg *self = k_object_new_with_private(CT_TYPE_IM_IMG, sizeof(CtImImgPrivate));
    return self;
}
