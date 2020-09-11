/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro13
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsensldiv.h"
#include "improsenobd.h"
#include "ctimpro13.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro13, ct_im_pro1_3)
#define CT_IM_PRO1_3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro13Private, CT_TYPE_IM_PRO1_3))


struct _CtImPro13Private
{
	ImproSensldiv *improSensldiv;
	ImproSenobd *improSenobd;
	ImPro13Print *imPro13Print;
	kint32 ercd;
};


/**********
 * IMPL
 */
static void ct_im_pro1_3_constructor(CtImPro13 *self)
{
	self->priv = CT_IM_PRO1_3_GET_PRIVATE(self);
	self->priv->improSensldiv = impro_sensldiv_new();
	self->priv->improSenobd = impro_senobd_new();
	self->priv->imPro13Print = im_pro_1_3_print_new();
	self->priv->ercd = 0;
}

static void ct_im_pro1_3_destructor(CtImPro13 *self)
{
	CtImPro13Private *priv = CT_IM_PRO1_3_GET_PRIVATE(self);

	if (priv->improSensldiv) {
		k_object_unref(priv->improSensldiv);
		priv->improSensldiv = NULL;
	}

	if (priv->improSenobd) {
		k_object_unref(priv->improSenobd);
		priv->improSenobd = NULL;
	}

	if (priv->imPro13Print) {
		k_object_unref(priv->imPro13Print);
		priv->imPro13Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro1_3_0(CtImPro13* self, const kuint32 idx)
{
	kuchar ch;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sensldiv_start(0) trgr  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[0].ldivtrg.word, ioPro.sen.ldiv[0].ldivtrg.word));
//        Ddim_Print(("impro_sensldiv_start(1) trgr  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[1].ldivtrg.word, ioPro.sen.ldiv[1].ldivtrg.word));
//        Ddim_Print(("impro_sensldiv_start(2) trgr  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[2].ldivtrg.word, ioPro.sen.ldiv[2].ldivtrg.word));
//        Ddim_Print(("impro_sensldiv_start(3) trgr  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[3].ldivtrg.word, ioPro.sen.ldiv[3].ldivtrg.word));
		// Maximum value parameter
		ch = E_IM_PRO_LDIV_CH_3;//TODO
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.ldiv[ch].ldivtrg.bit.ldivtrg = 2;
#endif
		self->priv->ercd = impro_sensldiv_start(self->priv->improSensldiv, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensldiv_start() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_0(self->priv->imPro13Print, "max_para", ch);
		}

		// Minimum value parameter
		ch = E_IM_PRO_LDIV_CH_0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.ldiv[ch].ldivtrg.bit.ldivtrg = 2;
#endif
		self->priv->ercd = impro_sensldiv_start(self->priv->improSensldiv, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensldiv_start() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_0(self->priv->imPro13Print, "min_para", ch);
		}
	}
}

void ct_im_pro1_3_1(CtImPro13* self, const kuint32 idx)
{
	kuchar ch;
	kuchar force = 0;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sensldiv_stop(0) trgr  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[0].ldivtrg.word, ioPro.sen.ldiv[0].ldivtrg.word));
//        Ddim_Print(("impro_sensldiv_stop(1) trgr  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[1].ldivtrg.word, ioPro.sen.ldiv[1].ldivtrg.word));
//        Ddim_Print(("impro_sensldiv_stop(2) trgr  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[2].ldivtrg.word, ioPro.sen.ldiv[2].ldivtrg.word));
//        Ddim_Print(("impro_sensldiv_stop(3) trgr  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[3].ldivtrg.word, ioPro.sen.ldiv[3].ldivtrg.word));
		// Maximum value parameter
		ch = E_IM_PRO_LDIV_CH_3;
		force = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.ldiv[ch].ldivtrg.bit.ldivtrg = 3;
#endif
		self->priv->ercd = impro_sensldiv_stop(self->priv->improSensldiv, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_stop() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_1(self->priv->imPro13Print, "max_para", ch, force);
		}

		// Minimum value parameter
		ch = E_IM_PRO_LDIV_CH_0;
		force = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.ldiv[ch].ldivtrg.bit.ldivtrg = 3;
#endif
		self->priv->ercd = impro_sensldiv_stop(self->priv->improSensldiv, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_stop() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_1(self->priv->imPro13Print, "min_para", ch, force);
		}
	}
}

void ct_im_pro1_3_2(CtImPro13* self, const kuint32 idx)
{
    kuchar ch;
    TimproLdivCtrl ldivCtrlMax = {
        .mode = ImproSensldiv_E_IM_PRO_LDIV_LDSTMD_LINESKIP,
        .ldipmd = ImproSensldiv_E_IM_PRO_LDIV_LDIPMD_8POINT_INPUT,
        .ldvdmd = ImproSensldiv_E_IM_PRO_LDIV_LDVDMD_QUARTER_SUBSAMPLING,
        .hdInsertionEn = ImproSensldiv_E_IM_PRO_LDIV_HD_INSERTION_ENABLE_EN,
        .ldmch = ImproSensldiv_E_IM_PRO_LDIV_LDMCH_4_COMBI,
        .lddivmd = ImproSensldiv_E_IM_PRO_LDIV_LDDIVMD_4RECT_OUTPUT,
        .ldopmd = ImproSensldiv_E_IM_PRO_LDIV_LDOPMD_2LINE_2OUT,
    };

    TimproLdivCtrl  ldivCtrlMin = {
        .mode = ImproSensldiv_E_IM_PRO_LDIV_LDSTMD_LINE,
        .ldipmd = ImproSensldiv_E_IM_PRO_LDIV_LDIPMD_2POINT_INPUT,
        .ldvdmd = ImproSensldiv_E_IM_PRO_LDIV_LDVDMD_NO_SUBSAMPLING,
        .hdInsertionEn = ImproSensldiv_E_IM_PRO_LDIV_HD_INSERTION_ENABLE_DIS,
        .ldmch = ImproSensldiv_E_IM_PRO_LDIV_LDMCH_NO_COMBI,
        .lddivmd = ImproSensldiv_E_IM_PRO_LDIV_LDDIVMD_SINGLE_OUTPUT,
        .ldopmd = ImproSensldiv_E_IM_PRO_LDIV_LDOPMD_2LINE_1OUT,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sensldiv_ctrl(0) LDIVCTL  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[0].LDIVCTL.word, ioPro.sen.ldiv[0].LDIVCTL.word));
//        Ddim_Print(("impro_sensldiv_ctrl(1) LDIVCTL  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[1].LDIVCTL.word, ioPro.sen.ldiv[1].LDIVCTL.word));
//        Ddim_Print(("impro_sensldiv_ctrl(2) LDIVCTL  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[2].LDIVCTL.word, ioPro.sen.ldiv[2].LDIVCTL.word));
//        Ddim_Print(("impro_sensldiv_ctrl(3) LDIVCTL  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[3].LDIVCTL.word, ioPro.sen.ldiv[3].LDIVCTL.word));
		// Maximum value parameter
		ch = E_IM_PRO_LDIV_CH_3;
		self->priv->ercd = impro_sensldiv_ctrl(self->priv->improSensldiv, ch, &ldivCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensldiv_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_2(self->priv->imPro13Print, "max_para", ch, &ldivCtrlMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_LDIV_CH_0;
		self->priv->ercd = impro_sensldiv_ctrl(self->priv->improSensldiv, ch, &ldivCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensldiv_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_2(self->priv->imPro13Print, "min_para", ch, &ldivCtrlMin);
		}
    }
}

void ct_im_pro1_3_3(CtImPro13* self, const kuint32 idx)
{
    kuchar ch;
    TimproLdivArea ldivAreaMax = {
        .inWidth = 11840,
        .outPosX[0] = 16382,
        .outPosX[1] = 16382,
        .outPosX[2] = 16382,
        .outPosX[3] = 16382,
        .outWidth[0] = 11840,
        .outWidth[1] = 11840,
        .outWidth[2] = 11840,
        .outWidth[3] = 11840,
    };

    TimproLdivArea ldivAreaMin = {
        .inWidth = 0,
        .outPosX[0] = 0,
        .outPosX[1] = 0,
        .outPosX[2] = 0,
        .outPosX[3] = 0,
        .outWidth[0] = 0,
        .outWidth[1] = 0,
        .outWidth[2] = 0,
        .outWidth[3] = 0,
    };


    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sensldiv_set_area(0) LDIVIHW   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[0].LDIVIHW.word,            ioPro.sen.ldiv[0].LDIVIHW.word            ));
//        Ddim_Print(("impro_sensldiv_set_area(0) LDIVOH1   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[0].LDIVOH.LDIVOH1.word,     ioPro.sen.ldiv[0].LDIVOH.LDIVOH1.word     ));
//        Ddim_Print(("impro_sensldiv_set_area(0) LDIVOH2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[0].LDIVOH.LDIVOH2.word,     ioPro.sen.ldiv[0].LDIVOH.LDIVOH2.word     ));
//        Ddim_Print(("impro_sensldiv_set_area(0) LDIVOHW1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[0].LDIVOHW.LDIVOHW1.word,   ioPro.sen.ldiv[0].LDIVOHW.LDIVOHW1.word   ));
//        Ddim_Print(("impro_sensldiv_set_area(0) LDIVOHW2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[0].LDIVOHW.LDIVOHW2.word,   ioPro.sen.ldiv[0].LDIVOHW.LDIVOHW2.word   ));
//        Ddim_Print(("impro_sensldiv_set_area(1) LDIVIHW   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[1].LDIVIHW.word,            ioPro.sen.ldiv[1].LDIVIHW.word            ));
//        Ddim_Print(("impro_sensldiv_set_area(1) LDIVOH1   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[1].LDIVOH.LDIVOH1.word,     ioPro.sen.ldiv[1].LDIVOH.LDIVOH1.word     ));
//        Ddim_Print(("impro_sensldiv_set_area(1) LDIVOH2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[1].LDIVOH.LDIVOH2.word,     ioPro.sen.ldiv[1].LDIVOH.LDIVOH2.word     ));
//        Ddim_Print(("impro_sensldiv_set_area(1) LDIVOHW1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[1].LDIVOHW.LDIVOHW1.word,   ioPro.sen.ldiv[1].LDIVOHW.LDIVOHW1.word   ));
//        Ddim_Print(("impro_sensldiv_set_area(1) LDIVOHW2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[1].LDIVOHW.LDIVOHW2.word,   ioPro.sen.ldiv[1].LDIVOHW.LDIVOHW2.word   ));
//        Ddim_Print(("impro_sensldiv_set_area(2) LDIVIHW   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[2].LDIVIHW.word,            ioPro.sen.ldiv[2].LDIVIHW.word            ));
//        Ddim_Print(("impro_sensldiv_set_area(2) LDIVOH1   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[2].LDIVOH.LDIVOH1.word,     ioPro.sen.ldiv[2].LDIVOH.LDIVOH1.word     ));
//        Ddim_Print(("impro_sensldiv_set_area(2) LDIVOH2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[2].LDIVOH.LDIVOH2.word,     ioPro.sen.ldiv[2].LDIVOH.LDIVOH2.word     ));
//        Ddim_Print(("impro_sensldiv_set_area(2) LDIVOHW1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[2].LDIVOHW.LDIVOHW1.word,   ioPro.sen.ldiv[2].LDIVOHW.LDIVOHW1.word   ));
//        Ddim_Print(("impro_sensldiv_set_area(2) LDIVOHW2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[2].LDIVOHW.LDIVOHW2.word,   ioPro.sen.ldiv[2].LDIVOHW.LDIVOHW2.word   ));
//        Ddim_Print(("impro_sensldiv_set_area(3) LDIVIHW   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[3].LDIVIHW.word,            ioPro.sen.ldiv[3].LDIVIHW.word            ));
//        Ddim_Print(("impro_sensldiv_set_area(3) LDIVOH1   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[3].LDIVOH.LDIVOH1.word,     ioPro.sen.ldiv[3].LDIVOH.LDIVOH1.word     ));
//        Ddim_Print(("impro_sensldiv_set_area(3) LDIVOH2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[3].LDIVOH.LDIVOH2.word,     ioPro.sen.ldiv[3].LDIVOH.LDIVOH2.word     ));
//        Ddim_Print(("impro_sensldiv_set_area(3) LDIVOHW1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[3].LDIVOHW.LDIVOHW1.word,   ioPro.sen.ldiv[3].LDIVOHW.LDIVOHW1.word   ));
//        Ddim_Print(("impro_sensldiv_set_area(3) LDIVOHW2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[3].LDIVOHW.LDIVOHW2.word,   ioPro.sen.ldiv[3].LDIVOHW.LDIVOHW2.word   ));
		// Maximum value parameter
		ch = E_IM_PRO_LDIV_CH_3;
		self->priv->ercd = impro_sensldiv_set_area(self->priv->improSensldiv, ch, &ldivAreaMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensldiv_set_area() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_3(self->priv->imPro13Print, "max_para", ch, &ldivAreaMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_LDIV_CH_0;
		self->priv->ercd = impro_sensldiv_set_area(self->priv->improSensldiv, ch, &ldivAreaMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensldiv_set_area() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_3(self->priv->imPro13Print, "min_para", ch, &ldivAreaMin);
		}
    }
}

void ct_im_pro1_3_4(CtImPro13* self, const kuint32 idx)
{
	kuchar paenTrg;
	kuchar ch;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sensldiv_set_paen(0) LDIVPAEN  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[0].LDIVPAEN,    ioPro.sen.ldiv[0].LDIVPAEN));
//        Ddim_Print(("impro_sensldiv_set_paen(1) LDIVPAEN  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[1].LDIVPAEN,    ioPro.sen.ldiv[1].LDIVPAEN));
//        Ddim_Print(("impro_sensldiv_set_paen(2) LDIVPAEN  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[2].LDIVPAEN,    ioPro.sen.ldiv[2].LDIVPAEN));
//        Ddim_Print(("impro_sensldiv_set_paen(3) LDIVPAEN  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.ldiv[3].LDIVPAEN,    ioPro.sen.ldiv[3].LDIVPAEN));

		// enable value parameter
		ch = E_IM_PRO_LDIV_CH_3;
		paenTrg = 1;
		self->priv->ercd = impro_sensldiv_set_paen(self->priv->improSensldiv, ch, paenTrg);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensldiv_set_paen() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_4(self->priv->imPro13Print, "max_para", ch, paenTrg);
		}

		// disable value parameter
		ch = E_IM_PRO_LDIV_CH_0;
		paenTrg = 0;
		self->priv->ercd = impro_sensldiv_set_paen(self->priv->improSensldiv, ch, paenTrg);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensldiv_set_paen() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_4(self->priv->imPro13Print, "min_para", ch, paenTrg);
		}

		// macro running error test
		ch = E_IM_PRO_LDIV_CH_0;
		paenTrg = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.ldiv[ch].ldivtrg.bit.ldivtrg = D_IM_PRO_TRG_STATUS_RUNNING;
#else
		impro_sensldiv_start(self->priv->improSensldiv, ch);
#endif
		self->priv->ercd = impro_sensldiv_set_paen(self->priv->improSensldiv, ch, paenTrg);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensldiv_set_paen() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_4(self->priv->imPro13Print, "macro running error", ch, paenTrg);
		}
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.ldiv[ch].ldivtrg.bit.ldivtrg = D_IM_PRO_TRG_STATUS_STOPPED;
#else
		impro_sensldiv_stop(self->priv->improSensldiv, ch, 0);
#endif
	}
}

void ct_im_pro1_3_5(CtImPro13* self, const kuint32 idx)
{
	kuchar ch;
#ifdef CO_DEBUG_ON_PC
	kuchar blockNum = 0;
	kuchar chNum = 0;
#endif

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senobd_start(0, 0) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].obdtrg.word, ioPro.sen.obd[0][0].obdtrg.word));
//        Ddim_Print(("impro_senobd_start(0, 1) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].obdtrg.word, ioPro.sen.obd[0][1].obdtrg.word));
//        Ddim_Print(("impro_senobd_start(1, 0) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].obdtrg.word, ioPro.sen.obd[1][0].obdtrg.word));
//        Ddim_Print(("impro_senobd_start(1, 1) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].obdtrg.word, ioPro.sen.obd[1][1].obdtrg.word));
//        Ddim_Print(("impro_senobd_start(2, 0) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].obdtrg.word, ioPro.sen.obd[2][0].obdtrg.word));
//        Ddim_Print(("impro_senobd_start(2, 1) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].obdtrg.word, ioPro.sen.obd[2][1].obdtrg.word));
//        Ddim_Print(("impro_senobd_start(3, 0) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].obdtrg.word, ioPro.sen.obd[3][0].obdtrg.word));
//        Ddim_Print(("impro_senobd_start(3, 1) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].obdtrg.word, ioPro.sen.obd[3][1].obdtrg.word));
		// Maximum value parameter
		ch = E_IM_PRO_OBD_CH_0_0;
#ifdef CO_DEBUG_ON_PC
		im_pro_comm_get_obd_block_ch(self->priv->improSensldiv, ch, &blockNum, &chNum);//TODO
		ioPro.sen.obd[blockNum][chNum].obdtrg.bit.obdtrg = 2;
#endif
		self->priv->ercd = impro_senobd_start(self->priv->improSenobd, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_start() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_5(self->priv->imPro13Print, "max_para", ch);
		}

		// Minimum value parameter
		ch = E_IM_PRO_OBD_CH_3_1;
#ifdef CO_DEBUG_ON_PC
		im_pro_comm_get_obd_block_ch(self->priv->improSensldiv, ch, &blockNum, &chNum);//TODO
		ioPro.sen.obd[blockNum][chNum].obdtrg.bit.obdtrg = 2;
#endif
		self->priv->ercd = impro_senobd_start(self->priv->improSenobd, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_start() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_5(self->priv->imPro13Print, "min_para", ch);
		}
	}
}

void ct_im_pro1_3_6(CtImPro13* self, const kuint32 idx)
{
	kuchar ch;
	kuchar force = 0;
#ifdef CO_DEBUG_ON_PC
	kuchar blockNum = 0;
	kuchar chNum = 0;
#endif

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senobd_stop(0, 0) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].obdtrg.word, ioPro.sen.obd[0][0].obdtrg.word));
//        Ddim_Print(("impro_senobd_stop(0, 1) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].obdtrg.word, ioPro.sen.obd[0][1].obdtrg.word));
//        Ddim_Print(("impro_senobd_stop(1, 0) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].obdtrg.word, ioPro.sen.obd[1][0].obdtrg.word));
//        Ddim_Print(("impro_senobd_stop(1, 1) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].obdtrg.word, ioPro.sen.obd[1][1].obdtrg.word));
//        Ddim_Print(("impro_senobd_stop(2, 0) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].obdtrg.word, ioPro.sen.obd[2][0].obdtrg.word));
//        Ddim_Print(("impro_senobd_stop(2, 1) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].obdtrg.word, ioPro.sen.obd[2][1].obdtrg.word));
//        Ddim_Print(("impro_senobd_stop(3, 0) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].obdtrg.word, ioPro.sen.obd[3][0].obdtrg.word));
//        Ddim_Print(("impro_senobd_stop(3, 1) obdtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].obdtrg.word, ioPro.sen.obd[3][1].obdtrg.word));
		// Maximum value parameter
		ch = E_IM_PRO_OBD_CH_3_1;
		force = 0;
#ifdef CO_DEBUG_ON_PC
		im_pro_comm_get_obd_block_ch(self->priv->improSensldiv, ch, &blockNum, &chNum);//TODO
		ioPro.sen.obd[blockNum][chNum].obdtrg.bit.obdtrg = 3;
#endif
		self->priv->ercd = impro_senobd_stop(self->priv->improSenobd, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_stop() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_6(self->priv->imPro13Print, "max_para", ch, force);
		}

		// Minimum value parameter
		ch = E_IM_PRO_OBD_CH_0_0;
		force = 1;
#ifdef CO_DEBUG_ON_PC
		im_pro_comm_get_obd_block_ch(self->priv->improSensldiv, ch, &blockNum, &chNum);
		ioPro.sen.obd[blockNum][chNum].obdtrg.bit.obdtrg = 3;
#endif
		self->priv->ercd = impro_senobd_stop(self->priv->improSenobd, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_stop() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_6(self->priv->imPro13Print, "min_para", ch, force);
		}
	}
}

void ct_im_pro1_3_7(CtImPro13* self, const kuint32 idx)
{
    kuchar ch;
    TimproObdCtrl obCtrlMax = {
        .obMinValue = 16383,
        .obMaxValue = 16383,
    };

    TimproObdCtrl obCtrlMin = {
        .obMinValue = 0,
        .obMaxValue = 0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senobd_ctrl(0, 0) OBDTHBIT    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDTHBIT.word, ioPro.sen.obd[0][0].OBDCORE.OBDTHBIT.word ));
//        Ddim_Print(("impro_senobd_ctrl(0, 1) OBDTHBIT    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDTHBIT.word, ioPro.sen.obd[0][1].OBDCORE.OBDTHBIT.word ));
//        Ddim_Print(("impro_senobd_ctrl(1, 0) OBDTHBIT    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDTHBIT.word, ioPro.sen.obd[1][0].OBDCORE.OBDTHBIT.word ));
//        Ddim_Print(("impro_senobd_ctrl(1, 1) OBDTHBIT    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDTHBIT.word, ioPro.sen.obd[1][1].OBDCORE.OBDTHBIT.word ));
//        Ddim_Print(("impro_senobd_ctrl(2, 0) OBDTHBIT    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDTHBIT.word, ioPro.sen.obd[2][0].OBDCORE.OBDTHBIT.word ));
//        Ddim_Print(("impro_senobd_ctrl(2, 1) OBDTHBIT    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDTHBIT.word, ioPro.sen.obd[2][1].OBDCORE.OBDTHBIT.word ));
//        Ddim_Print(("impro_senobd_ctrl(3, 0) OBDTHBIT    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDTHBIT.word, ioPro.sen.obd[3][0].OBDCORE.OBDTHBIT.word ));
//        Ddim_Print(("impro_senobd_ctrl(3, 1) OBDTHBIT    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDTHBIT.word, ioPro.sen.obd[3][1].OBDCORE.OBDTHBIT.word ));
		// Maximum value parameter
		ch = E_IM_PRO_OBD_CH_3_1;
		self->priv->ercd = impro_senobd_ctrl(self->priv->improSenobd, ch, &obCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_7(self->priv->imPro13Print, "max_para", ch, &obCtrlMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_OBD_CH_0_0;
		self->priv->ercd = impro_senobd_ctrl(self->priv->improSenobd, ch, &obCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_7(self->priv->imPro13Print, "min_para", ch, &obCtrlMin);
		}
    }
}

void ct_im_pro1_3_8(CtImPro13* self, const kuint32 idx)
{
    kuchar ch;
    T_IM_PRO_AREA_INFO obAreaMax = {
        .posX = 12287,
        .posY = 8191,
        .width = 12288,
        .lines = 8192,
    };

    T_IM_PRO_AREA_INFO obAreaMin = {
        .posX = 0,
        .posY = 0,
        .width = 0,
        .lines = 0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senobd_set_area(0, 0) OBDH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDH.word,     ioPro.sen.obd[0][0].OBDCORE.OBDH.word ));
//        Ddim_Print(("impro_senobd_set_area(0, 0) OBDV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDV.word,     ioPro.sen.obd[0][0].OBDCORE.OBDV.word ));
//        Ddim_Print(("impro_senobd_set_area(0, 0) OBDHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDHW.word,    ioPro.sen.obd[0][0].OBDCORE.OBDHW.word));
//        Ddim_Print(("impro_senobd_set_area(0, 0) OBDVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDVW.word,    ioPro.sen.obd[0][0].OBDCORE.OBDVW.word));
//        Ddim_Print(("impro_senobd_set_area(0, 1) OBDH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDH.word,     ioPro.sen.obd[0][1].OBDCORE.OBDH.word ));
//        Ddim_Print(("impro_senobd_set_area(0, 1) OBDV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDV.word,     ioPro.sen.obd[0][1].OBDCORE.OBDV.word ));
//        Ddim_Print(("impro_senobd_set_area(0, 1) OBDHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDHW.word,    ioPro.sen.obd[0][1].OBDCORE.OBDHW.word));
//        Ddim_Print(("impro_senobd_set_area(0, 1) OBDVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDVW.word,    ioPro.sen.obd[0][1].OBDCORE.OBDVW.word));
//        Ddim_Print(("impro_senobd_set_area(1, 0) OBDH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDH.word,     ioPro.sen.obd[1][0].OBDCORE.OBDH.word ));
//        Ddim_Print(("impro_senobd_set_area(1, 0) OBDV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDV.word,     ioPro.sen.obd[1][0].OBDCORE.OBDV.word ));
//        Ddim_Print(("impro_senobd_set_area(1, 0) OBDHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDHW.word,    ioPro.sen.obd[1][0].OBDCORE.OBDHW.word));
//        Ddim_Print(("impro_senobd_set_area(1, 0) OBDVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDVW.word,    ioPro.sen.obd[1][0].OBDCORE.OBDVW.word));
//        Ddim_Print(("impro_senobd_set_area(1, 1) OBDH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDH.word,     ioPro.sen.obd[1][1].OBDCORE.OBDH.word ));
//        Ddim_Print(("impro_senobd_set_area(1, 1) OBDV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDV.word,     ioPro.sen.obd[1][1].OBDCORE.OBDV.word ));
//        Ddim_Print(("impro_senobd_set_area(1, 1) OBDHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDHW.word,    ioPro.sen.obd[1][1].OBDCORE.OBDHW.word));
//        Ddim_Print(("impro_senobd_set_area(1, 1) OBDVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDVW.word,    ioPro.sen.obd[1][1].OBDCORE.OBDVW.word));
//        Ddim_Print(("impro_senobd_set_area(2, 0) OBDH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDH.word,     ioPro.sen.obd[2][0].OBDCORE.OBDH.word ));
//        Ddim_Print(("impro_senobd_set_area(2, 0) OBDV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDV.word,     ioPro.sen.obd[2][0].OBDCORE.OBDV.word ));
//        Ddim_Print(("impro_senobd_set_area(2, 0) OBDHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDHW.word,    ioPro.sen.obd[2][0].OBDCORE.OBDHW.word));
//        Ddim_Print(("impro_senobd_set_area(2, 0) OBDVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDVW.word,    ioPro.sen.obd[2][0].OBDCORE.OBDVW.word));
//        Ddim_Print(("impro_senobd_set_area(2, 1) OBDH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDH.word,     ioPro.sen.obd[2][1].OBDCORE.OBDH.word ));
//        Ddim_Print(("impro_senobd_set_area(2, 1) OBDV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDV.word,     ioPro.sen.obd[2][1].OBDCORE.OBDV.word ));
//        Ddim_Print(("impro_senobd_set_area(2, 1) OBDHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDHW.word,    ioPro.sen.obd[2][1].OBDCORE.OBDHW.word));
//        Ddim_Print(("impro_senobd_set_area(2, 1) OBDVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDVW.word,    ioPro.sen.obd[2][1].OBDCORE.OBDVW.word));
//        Ddim_Print(("impro_senobd_set_area(3, 0) OBDH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDH.word,     ioPro.sen.obd[3][0].OBDCORE.OBDH.word ));
//        Ddim_Print(("impro_senobd_set_area(3, 0) OBDV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDV.word,     ioPro.sen.obd[3][0].OBDCORE.OBDV.word ));
//        Ddim_Print(("impro_senobd_set_area(3, 0) OBDHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDHW.word,    ioPro.sen.obd[3][0].OBDCORE.OBDHW.word));
//        Ddim_Print(("impro_senobd_set_area(3, 0) OBDVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDVW.word,    ioPro.sen.obd[3][0].OBDCORE.OBDVW.word));
//        Ddim_Print(("impro_senobd_set_area(3, 1) OBDH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDH.word,     ioPro.sen.obd[3][1].OBDCORE.OBDH.word ));
//        Ddim_Print(("impro_senobd_set_area(3, 1) OBDV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDV.word,     ioPro.sen.obd[3][1].OBDCORE.OBDV.word ));
//        Ddim_Print(("impro_senobd_set_area(3, 1) OBDHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDHW.word,    ioPro.sen.obd[3][1].OBDCORE.OBDHW.word));
//        Ddim_Print(("impro_senobd_set_area(3, 1) OBDVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDVW.word,    ioPro.sen.obd[3][1].OBDCORE.OBDVW.word));

		// Maximum value parameter
		ch = E_IM_PRO_OBD_CH_3_1;
		self->priv->ercd = impro_senobd_set_area(self->priv->improSenobd, ch, &obAreaMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_set_area() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_8(self->priv->imPro13Print, "max_para", ch, &obAreaMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_OBD_CH_0_0;
		self->priv->ercd = impro_senobd_set_area(self->priv->improSenobd, ch, &obAreaMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_set_area() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_8(self->priv->imPro13Print, "min_para", ch, &obAreaMin);
		}
	}
}

void ct_im_pro1_3_9(CtImPro13* self, const kuint32 idx)
{
	kuchar ch;
	TimproRgb4 obcnt;
	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTR    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDCNTR.word,      ioPro.sen.obd[0][0].OBDCORE.OBDCNTR.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGR   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDCNTGR.word,     ioPro.sen.obd[0][0].OBDCORE.OBDCNTGR.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGB   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDCNTGB.word,     ioPro.sen.obd[0][0].OBDCORE.OBDCNTGB.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTB    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDCNTB.word,      ioPro.sen.obd[0][0].OBDCORE.OBDCNTB.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTR    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDCNTR.word,      ioPro.sen.obd[0][1].OBDCORE.OBDCNTR.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGR   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDCNTGR.word,     ioPro.sen.obd[0][1].OBDCORE.OBDCNTGR.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGB   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDCNTGB.word,     ioPro.sen.obd[0][1].OBDCORE.OBDCNTGB.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTB    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDCNTB.word,      ioPro.sen.obd[0][1].OBDCORE.OBDCNTB.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTR    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDCNTR.word,      ioPro.sen.obd[1][0].OBDCORE.OBDCNTR.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGR   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDCNTGR.word,     ioPro.sen.obd[1][0].OBDCORE.OBDCNTGR.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGB   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDCNTGB.word,     ioPro.sen.obd[1][0].OBDCORE.OBDCNTGB.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTB    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDCNTB.word,      ioPro.sen.obd[1][0].OBDCORE.OBDCNTB.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTR    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDCNTR.word,      ioPro.sen.obd[1][1].OBDCORE.OBDCNTR.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGR   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDCNTGR.word,     ioPro.sen.obd[1][1].OBDCORE.OBDCNTGR.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGB   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDCNTGB.word,     ioPro.sen.obd[1][1].OBDCORE.OBDCNTGB.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTB    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDCNTB.word,      ioPro.sen.obd[1][1].OBDCORE.OBDCNTB.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTR    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDCNTR.word,      ioPro.sen.obd[2][0].OBDCORE.OBDCNTR.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGR   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDCNTGR.word,     ioPro.sen.obd[2][0].OBDCORE.OBDCNTGR.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGB   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDCNTGB.word,     ioPro.sen.obd[2][0].OBDCORE.OBDCNTGB.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTB    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDCNTB.word,      ioPro.sen.obd[2][0].OBDCORE.OBDCNTB.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTR    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDCNTR.word,      ioPro.sen.obd[2][1].OBDCORE.OBDCNTR.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGR   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDCNTGR.word,     ioPro.sen.obd[2][1].OBDCORE.OBDCNTGR.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGB   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDCNTGB.word,     ioPro.sen.obd[2][1].OBDCORE.OBDCNTGB.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTB    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDCNTB.word,      ioPro.sen.obd[2][1].OBDCORE.OBDCNTB.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTR    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDCNTR.word,      ioPro.sen.obd[3][0].OBDCORE.OBDCNTR.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGR   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDCNTGR.word,     ioPro.sen.obd[3][0].OBDCORE.OBDCNTGR.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGB   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDCNTGB.word,     ioPro.sen.obd[3][0].OBDCORE.OBDCNTGB.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTB    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDCNTB.word,      ioPro.sen.obd[3][0].OBDCORE.OBDCNTB.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTR    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDCNTR.word,      ioPro.sen.obd[3][1].OBDCORE.OBDCNTR.word  ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGR   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDCNTGR.word,     ioPro.sen.obd[3][1].OBDCORE.OBDCNTGR.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTGB   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDCNTGB.word,     ioPro.sen.obd[3][1].OBDCORE.OBDCNTGB.word ));
//        Ddim_Print(("impro_senobd_get_ob_cnt(0, 0) OBDCNTB    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDCNTB.word,      ioPro.sen.obd[3][1].OBDCORE.OBDCNTB.word  ));

		// Maximum value parameter
		ch = E_IM_PRO_OBD_CH_3_1;
		self->priv->ercd = impro_senobd_get_ob_cnt(self->priv->improSenobd, ch, &obcnt);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_get_ob_cnt() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_9(self->priv->imPro13Print, "max_para", ch, &obcnt);
		}

		ch = E_IM_PRO_OBD_CH_0_0;
		// Minimum value parameter
		self->priv->ercd = impro_senobd_get_ob_cnt(self->priv->improSenobd, ch, &obcnt);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_get_ob_cnt() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_3_print_9(self->priv->imPro13Print, "min_para", ch, &obcnt);
		}
	}
}
#endif //CO_CT_IM_PRO_DISABLE

CtImPro13* ct_im_pro1_3_new(void)
{
	CtImPro13* self = k_object_new_with_private(CT_TYPE_IM_PRO1_3, sizeof(CtImPro13Private));

	return self;
}

