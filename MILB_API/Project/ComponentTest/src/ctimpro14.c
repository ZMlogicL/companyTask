/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro14
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsenobd.h"
#include "improsenobt.h"
#include "improsendmipi.h"
#include "ctimpro14.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro14, ct_im_pro1_4)
#define CT_IM_PRO1_4_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro14Private, CT_TYPE_IM_PRO1_4))


struct _CtImPro14Private
{
	ImproSenobd *improSenobd;
	ImproSenobt *improSenobt;
	ImproSendmipi *improSendmipi;
	ImPro14Print *imPro14Print;
	kint32 ercd;
};


/**********
 * IMPL
 */
static void ct_im_pro1_4_constructor(CtImPro14 *self)
{
	self->priv = CT_IM_PRO1_4_GET_PRIVATE(self);
	self->priv->improSenobd = impro_senobd_new();
	self->priv->improSenobt = impro_senobt_new();
	self->priv->improSendmipi = impro_sendmipi_new();
	self->priv->imPro14Print = im_pro_1_4_print_new();
	self->priv->ercd = 0;
}

static void ct_im_pro1_4_destructor(CtImPro14 *self)
{
	CtImPro14Private *priv = CT_IM_PRO1_4_GET_PRIVATE(self);

	if (priv->improSenobd) {
		k_object_unref(priv->improSenobd);
		priv->improSenobd = NULL;
	}

	if (priv->improSenobt) {
		k_object_unref(priv->improSenobt);
		priv->improSenobt = NULL;
	}

	if (priv->improSendmipi) {
		k_object_unref(priv->improSendmipi);
		priv->improSendmipi = NULL;
	}

	if (priv->imPro14Print) {
		k_object_unref(priv->imPro14Print);
		priv->imPro14Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro1_4_0(CtImPro14* self, const kuint32 idx)
{
	kuchar ch;
	TimproRgb4 obcnt;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDDATAR.word,     ioPro.sen.obd[0][0].OBDCORE.OBDDATAR.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDDATAGR.word,    ioPro.sen.obd[0][0].OBDCORE.OBDDATAGR.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDDATAGB.word,    ioPro.sen.obd[0][0].OBDCORE.OBDDATAGB.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][0].OBDCORE.OBDDATAB.word,     ioPro.sen.obd[0][0].OBDCORE.OBDDATAB.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDDATAR.word,     ioPro.sen.obd[0][1].OBDCORE.OBDDATAR.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDDATAGR.word,    ioPro.sen.obd[0][1].OBDCORE.OBDDATAGR.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDDATAGB.word,    ioPro.sen.obd[0][1].OBDCORE.OBDDATAGB.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[0][1].OBDCORE.OBDDATAB.word,     ioPro.sen.obd[0][1].OBDCORE.OBDDATAB.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDDATAR.word,     ioPro.sen.obd[1][0].OBDCORE.OBDDATAR.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDDATAGR.word,    ioPro.sen.obd[1][0].OBDCORE.OBDDATAGR.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDDATAGB.word,    ioPro.sen.obd[1][0].OBDCORE.OBDDATAGB.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][0].OBDCORE.OBDDATAB.word,     ioPro.sen.obd[1][0].OBDCORE.OBDDATAB.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDDATAR.word,     ioPro.sen.obd[1][1].OBDCORE.OBDDATAR.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDDATAGR.word,    ioPro.sen.obd[1][1].OBDCORE.OBDDATAGR.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDDATAGB.word,    ioPro.sen.obd[1][1].OBDCORE.OBDDATAGB.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[1][1].OBDCORE.OBDDATAB.word,     ioPro.sen.obd[1][1].OBDCORE.OBDDATAB.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDDATAR.word,     ioPro.sen.obd[2][0].OBDCORE.OBDDATAR.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDDATAGR.word,    ioPro.sen.obd[2][0].OBDCORE.OBDDATAGR.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDDATAGB.word,    ioPro.sen.obd[2][0].OBDCORE.OBDDATAGB.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][0].OBDCORE.OBDDATAB.word,     ioPro.sen.obd[2][0].OBDCORE.OBDDATAB.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDDATAR.word,     ioPro.sen.obd[2][1].OBDCORE.OBDDATAR.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDDATAGR.word,    ioPro.sen.obd[2][1].OBDCORE.OBDDATAGR.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDDATAGB.word,    ioPro.sen.obd[2][1].OBDCORE.OBDDATAGB.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[2][1].OBDCORE.OBDDATAB.word,     ioPro.sen.obd[2][1].OBDCORE.OBDDATAB.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDDATAR.word,     ioPro.sen.obd[3][0].OBDCORE.OBDDATAR.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDDATAGR.word,    ioPro.sen.obd[3][0].OBDCORE.OBDDATAGR.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDDATAGB.word,    ioPro.sen.obd[3][0].OBDCORE.OBDDATAGB.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][0].OBDCORE.OBDDATAB.word,     ioPro.sen.obd[3][0].OBDCORE.OBDDATAB.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDDATAR.word,     ioPro.sen.obd[3][1].OBDCORE.OBDDATAR.word ));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDDATAGR.word,    ioPro.sen.obd[3][1].OBDCORE.OBDDATAGR.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDDATAGB.word,    ioPro.sen.obd[3][1].OBDCORE.OBDDATAGB.word));
//        Ddim_Print(("impro_senobd_get_ob_data(0, 0) OBDDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obd[3][1].OBDCORE.OBDDATAB.word,     ioPro.sen.obd[3][1].OBDCORE.OBDDATAB.word ));

// Maximum value parameter
		ch = E_IM_PRO_OBD_CH_3_1;
		self->priv->ercd = impro_senobd_get_ob_data(self->priv->improSenobd, ch, &obcnt);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_get_ob_data() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_0(self->priv->imPro14Print, "max_para", ch, &obcnt);
		}

		ch = E_IM_PRO_OBD_CH_0_0;
		// Minimum value parameter
		self->priv->ercd = impro_senobd_get_ob_data(self->priv->improSenobd, ch, &obcnt);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_get_ob_data() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_0(self->priv->imPro14Print, "min_para", ch, &obcnt);
		}

		// invalid value parameter
		self->priv->ercd = impro_senobd_get_ob_data(self->priv->improSenobd, ch, NULL);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobd_get_ob_data() invalid Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_0(self->priv->imPro14Print, "invalid", ch, &obcnt);
		}
	}
}

void ct_im_pro1_4_1(CtImPro14* self, const kuint32 idx)
{
	kuchar ch;
#ifdef CO_DEBUG_ON_PC
	kuchar blockNum = 0;
	kuchar chNum = 0;
#endif

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senobt_start(0, 0) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].obttrg.word, ioPro.sen.obt[0][0].obttrg.word));
//        Ddim_Print(("impro_senobt_start(0, 1) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].obttrg.word, ioPro.sen.obt[0][1].obttrg.word));
//        Ddim_Print(("impro_senobt_start(1, 0) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].obttrg.word, ioPro.sen.obt[1][0].obttrg.word));
//        Ddim_Print(("impro_senobt_start(1, 1) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].obttrg.word, ioPro.sen.obt[1][1].obttrg.word));
//        Ddim_Print(("impro_senobt_start(2, 0) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].obttrg.word, ioPro.sen.obt[2][0].obttrg.word));
//        Ddim_Print(("impro_senobt_start(2, 1) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].obttrg.word, ioPro.sen.obt[2][1].obttrg.word));
//        Ddim_Print(("impro_senobt_start(3, 0) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].obttrg.word, ioPro.sen.obt[3][0].obttrg.word));
//        Ddim_Print(("impro_senobt_start(3, 1) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].obttrg.word, ioPro.sen.obt[3][1].obttrg.word));
		// Maximum value parameter
		ch = E_IM_PRO_OBT_CH_0_0;
#ifdef CO_DEBUG_ON_PC
//		im_pro_comm_get_obt_block_ch(self->priv->improSenobd, ch, &blockNum, &chNum);//TODO
		ioPro.sen.obt[blockNum][chNum].obttrg.bit.obttrg = 2;
#endif
		self->priv->ercd = impro_senobt_start(self->priv->improSenobt, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobt_start() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_1(self->priv->imPro14Print, "max_para", ch);
		}

		// Minimum value parameter
		ch = E_IM_PRO_OBT_CH_3_1;
#ifdef CO_DEBUG_ON_PC
		im_pro_comm_get_obt_block_ch(self->priv->improSenobd, ch, &blockNum, &chNum);
		ioPro.sen.obt[blockNum][chNum].obttrg.bit.obttrg = 2;
#endif
		self->priv->ercd = impro_senobt_start(self->priv->improSenobt, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobt_start() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_1(self->priv->imPro14Print, "min_para", ch);
		}
	}
}

void ct_im_pro1_4_2(CtImPro14* self, const kuint32 idx)
{
	kuchar ch;
	kuchar force = 0;
#ifdef CO_DEBUG_ON_PC
	kuchar blockNum = 0;
	kuchar chNum = 0;
#endif

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senobt_stop(0, 0) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].obttrg.word, ioPro.sen.obt[0][0].obttrg.word));
//        Ddim_Print(("impro_senobt_stop(0, 1) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].obttrg.word, ioPro.sen.obt[0][1].obttrg.word));
//        Ddim_Print(("impro_senobt_stop(1, 0) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].obttrg.word, ioPro.sen.obt[1][0].obttrg.word));
//        Ddim_Print(("impro_senobt_stop(1, 1) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].obttrg.word, ioPro.sen.obt[1][1].obttrg.word));
//        Ddim_Print(("impro_senobt_stop(2, 0) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].obttrg.word, ioPro.sen.obt[2][0].obttrg.word));
//        Ddim_Print(("impro_senobt_stop(2, 1) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].obttrg.word, ioPro.sen.obt[2][1].obttrg.word));
//        Ddim_Print(("impro_senobt_stop(3, 0) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].obttrg.word, ioPro.sen.obt[3][0].obttrg.word));
//        Ddim_Print(("impro_senobt_stop(3, 1) obttrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].obttrg.word, ioPro.sen.obt[3][1].obttrg.word));
		// Maximum value parameter
		ch = E_IM_PRO_OBT_CH_3_1;
		force = 0;
#ifdef CO_DEBUG_ON_PC
		im_pro_comm_get_obt_block_ch(self->priv->improSenobd, ch, &blockNum, &chNum);//TODO
		ioPro.sen.obt[blockNum][chNum].obttrg.bit.obttrg = 3;
#endif
		self->priv->ercd = impro_senobt_stop(self->priv->improSenobt, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobt_stop() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_2(self->priv->imPro14Print, "max_para", ch, force);
		}

		// Minimum value parameter
		ch = E_IM_PRO_OBT_CH_0_0;
		force = 1;
#ifdef CO_DEBUG_ON_PC
		im_pro_comm_get_obt_block_ch(self->priv->improSenobd, ch, &blockNum, &chNum);
		ioPro.sen.obt[blockNum][chNum].obttrg.bit.obttrg = 3;
#endif
		self->priv->ercd = impro_senobt_stop(self->priv->improSenobt, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobt_stop() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_2(self->priv->imPro14Print, "min_para", ch, force);
		}
	}
}

void ct_im_pro1_4_3(CtImPro14* self, const kuint32 idx)
{
    kuchar ch;
    TimproObtCtrl obCtrlMax = {
        .obtEnable = ImproSenobt_E_IM_PRO_OBT_EN,
        .mode = ImproSenobt_E_IM_PRO_OBT_MODE_COLOR,
        .sel = ImproSenobt_E_IM_PRO_OBT_SELECT_EVALUATION,
        .intercommEnable = ImproSenobt_E_IM_PRO_OBT_INTERCOMM_EN,
        .obMinValue = 16383,
        .obMaxValue = 16383,
    };

    TimproObtCtrl obCtrlMin = {
        .obtEnable = ImproSenobt_E_IM_PRO_OBT_DIS,
        .mode = ImproSenobt_E_IM_PRO_OBT_MODE_ALL,
        .sel = ImproSenobt_E_IM_PRO_OBT_SELECT_FIX,
        .intercommEnable   = ImproSenobt_E_IM_PRO_OBT_INTERCOMM_DIS,
        .obMinValue = 0,
        .obMaxValue = 0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senobt_ctrl(0, 0) OBTCTL      (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTCTL.word,      ioPro.sen.obt[0][0].OBTCORE.OBTCTL.word   ));
//        Ddim_Print(("impro_senobt_ctrl(0, 0) OBTTHBIT    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTTHBIT.word,    ioPro.sen.obt[0][0].OBTCORE.OBTTHBIT.word ));
//        Ddim_Print(("impro_senobt_ctrl(0, 1) OBTCTL      (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTCTL.word,      ioPro.sen.obt[0][1].OBTCORE.OBTCTL.word   ));
//        Ddim_Print(("impro_senobt_ctrl(0, 1) OBTTHBIT    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTTHBIT.word,    ioPro.sen.obt[0][1].OBTCORE.OBTTHBIT.word ));
//        Ddim_Print(("impro_senobt_ctrl(1, 0) OBTCTL      (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTCTL.word,      ioPro.sen.obt[1][0].OBTCORE.OBTCTL.word   ));
//        Ddim_Print(("impro_senobt_ctrl(1, 0) OBTTHBIT    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTTHBIT.word,    ioPro.sen.obt[1][0].OBTCORE.OBTTHBIT.word ));
//        Ddim_Print(("impro_senobt_ctrl(1, 1) OBTCTL      (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTCTL.word,      ioPro.sen.obt[1][1].OBTCORE.OBTCTL.word   ));
//        Ddim_Print(("impro_senobt_ctrl(1, 1) OBTTHBIT    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTTHBIT.word,    ioPro.sen.obt[1][1].OBTCORE.OBTTHBIT.word ));
//        Ddim_Print(("impro_senobt_ctrl(2, 0) OBTCTL      (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTCTL.word,      ioPro.sen.obt[2][0].OBTCORE.OBTCTL.word   ));
//        Ddim_Print(("impro_senobt_ctrl(2, 0) OBTTHBIT    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTTHBIT.word,    ioPro.sen.obt[2][0].OBTCORE.OBTTHBIT.word ));
//        Ddim_Print(("impro_senobt_ctrl(2, 1) OBTCTL      (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTCTL.word,      ioPro.sen.obt[2][1].OBTCORE.OBTCTL.word   ));
//        Ddim_Print(("impro_senobt_ctrl(2, 1) OBTTHBIT    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTTHBIT.word,    ioPro.sen.obt[2][1].OBTCORE.OBTTHBIT.word ));
//        Ddim_Print(("impro_senobt_ctrl(3, 0) OBTCTL      (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTCTL.word,      ioPro.sen.obt[3][0].OBTCORE.OBTCTL.word   ));
//        Ddim_Print(("impro_senobt_ctrl(3, 0) OBTTHBIT    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTTHBIT.word,    ioPro.sen.obt[3][0].OBTCORE.OBTTHBIT.word ));
//        Ddim_Print(("impro_senobt_ctrl(3, 1) OBTCTL      (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTCTL.word,      ioPro.sen.obt[3][1].OBTCORE.OBTCTL.word   ));
//        Ddim_Print(("impro_senobt_ctrl(3, 1) OBTTHBIT    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTTHBIT.word,    ioPro.sen.obt[3][1].OBTCORE.OBTTHBIT.word ));
		// Maximum value parameter
		ch = E_IM_PRO_OBT_CH_3_1;
		self->priv->ercd = impro_senobt_ctrl(self->priv->improSenobt, ch, &obCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobt_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_3(self->priv->imPro14Print, "max_para", ch, &obCtrlMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_OBT_CH_0_0;
		self->priv->ercd = impro_senobt_ctrl(self->priv->improSenobt, ch, &obCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobt_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_3(self->priv->imPro14Print, "min_para", ch, &obCtrlMin);
		}
    }
}

void ct_im_pro1_4_4(CtImPro14* self, const kuint32 idx)
{
    kuchar ch;
    T_IM_PRO_AREA_INFO obAreaMax = {
        .posX = 12287,
        .posY = 8191,
        .width = 12288,
        .lines = 127,
    };

    T_IM_PRO_AREA_INFO obAreaMin = {
        .posX = 0,
        .posY = 0,
        .width = 0,
        .lines = 0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senobt_set_area(0, 0) OBTH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTH.word,     ioPro.sen.obt[0][0].OBTCORE.OBTH.word ));
//        Ddim_Print(("impro_senobt_set_area(0, 0) OBTV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTV.word,     ioPro.sen.obt[0][0].OBTCORE.OBTV.word ));
//        Ddim_Print(("impro_senobt_set_area(0, 0) OBTHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTHW.word,    ioPro.sen.obt[0][0].OBTCORE.OBTHW.word));
//        Ddim_Print(("impro_senobt_set_area(0, 0) OBTVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTVW.word,    ioPro.sen.obt[0][0].OBTCORE.OBTVW.word));
//        Ddim_Print(("impro_senobt_set_area(0, 1) OBTH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTH.word,     ioPro.sen.obt[0][1].OBTCORE.OBTH.word ));
//        Ddim_Print(("impro_senobt_set_area(0, 1) OBTV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTV.word,     ioPro.sen.obt[0][1].OBTCORE.OBTV.word ));
//        Ddim_Print(("impro_senobt_set_area(0, 1) OBTHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTHW.word,    ioPro.sen.obt[0][1].OBTCORE.OBTHW.word));
//        Ddim_Print(("impro_senobt_set_area(0, 1) OBTVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTVW.word,    ioPro.sen.obt[0][1].OBTCORE.OBTVW.word));
//        Ddim_Print(("impro_senobt_set_area(1, 0) OBTH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTH.word,     ioPro.sen.obt[1][0].OBTCORE.OBTH.word ));
//        Ddim_Print(("impro_senobt_set_area(1, 0) OBTV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTV.word,     ioPro.sen.obt[1][0].OBTCORE.OBTV.word ));
//        Ddim_Print(("impro_senobt_set_area(1, 0) OBTHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTHW.word,    ioPro.sen.obt[1][0].OBTCORE.OBTHW.word));
//        Ddim_Print(("impro_senobt_set_area(1, 0) OBTVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTVW.word,    ioPro.sen.obt[1][0].OBTCORE.OBTVW.word));
//        Ddim_Print(("impro_senobt_set_area(1, 1) OBTH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTH.word,     ioPro.sen.obt[1][1].OBTCORE.OBTH.word ));
//        Ddim_Print(("impro_senobt_set_area(1, 1) OBTV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTV.word,     ioPro.sen.obt[1][1].OBTCORE.OBTV.word ));
//        Ddim_Print(("impro_senobt_set_area(1, 1) OBTHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTHW.word,    ioPro.sen.obt[1][1].OBTCORE.OBTHW.word));
//        Ddim_Print(("impro_senobt_set_area(1, 1) OBTVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTVW.word,    ioPro.sen.obt[1][1].OBTCORE.OBTVW.word));
//        Ddim_Print(("impro_senobt_set_area(2, 0) OBTH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTH.word,     ioPro.sen.obt[2][0].OBTCORE.OBTH.word ));
//        Ddim_Print(("impro_senobt_set_area(2, 0) OBTV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTV.word,     ioPro.sen.obt[2][0].OBTCORE.OBTV.word ));
//        Ddim_Print(("impro_senobt_set_area(2, 0) OBTHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTHW.word,    ioPro.sen.obt[2][0].OBTCORE.OBTHW.word));
//        Ddim_Print(("impro_senobt_set_area(2, 0) OBTVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTVW.word,    ioPro.sen.obt[2][0].OBTCORE.OBTVW.word));
//        Ddim_Print(("impro_senobt_set_area(2, 1) OBTH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTH.word,     ioPro.sen.obt[2][1].OBTCORE.OBTH.word ));
//        Ddim_Print(("impro_senobt_set_area(2, 1) OBTV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTV.word,     ioPro.sen.obt[2][1].OBTCORE.OBTV.word ));
//        Ddim_Print(("impro_senobt_set_area(2, 1) OBTHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTHW.word,    ioPro.sen.obt[2][1].OBTCORE.OBTHW.word));
//        Ddim_Print(("impro_senobt_set_area(2, 1) OBTVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTVW.word,    ioPro.sen.obt[2][1].OBTCORE.OBTVW.word));
//        Ddim_Print(("impro_senobt_set_area(3, 0) OBTH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTH.word,     ioPro.sen.obt[3][0].OBTCORE.OBTH.word ));
//        Ddim_Print(("impro_senobt_set_area(3, 0) OBTV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTV.word,     ioPro.sen.obt[3][0].OBTCORE.OBTV.word ));
//        Ddim_Print(("impro_senobt_set_area(3, 0) OBTHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTHW.word,    ioPro.sen.obt[3][0].OBTCORE.OBTHW.word));
//        Ddim_Print(("impro_senobt_set_area(3, 0) OBTVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTVW.word,    ioPro.sen.obt[3][0].OBTCORE.OBTVW.word));
//        Ddim_Print(("impro_senobt_set_area(3, 1) OBTH        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTH.word,     ioPro.sen.obt[3][1].OBTCORE.OBTH.word ));
//        Ddim_Print(("impro_senobt_set_area(3, 1) OBTV        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTV.word,     ioPro.sen.obt[3][1].OBTCORE.OBTV.word ));
//        Ddim_Print(("impro_senobt_set_area(3, 1) OBTHW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTHW.word,    ioPro.sen.obt[3][1].OBTCORE.OBTHW.word));
//        Ddim_Print(("impro_senobt_set_area(3, 1) OBTVW       (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTVW.word,    ioPro.sen.obt[3][1].OBTCORE.OBTVW.word));

		// Maximum value parameter
		ch = E_IM_PRO_OBT_CH_3_1;
		self->priv->ercd = impro_senobt_set_area(self->priv->improSenobt, ch, &obAreaMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobt_set_area() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_4(self->priv->imPro14Print, "max_para", ch, &obAreaMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_OBT_CH_0_0;
		self->priv->ercd = impro_senobt_set_area(self->priv->improSenobt, ch, &obAreaMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobt_set_area() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_4(self->priv->imPro14Print, "min_para", ch, &obAreaMin);
		}
    }
}

void ct_im_pro1_4_5(CtImPro14* self, const kuint32 idx)
{
    kuchar ch;
    T_IM_PRO_RGB2 offsetMax = {//TODO
        .R = 16383,
        .Gr = 16383,
        .Gb = 16383,
        .B = 16383,
    };

    T_IM_PRO_RGB2 offsetMin = {
        .R= -16384,
        .Gr = -16384,
        .Gb = -16384,
        .B = -16384,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senobt_set_area(0, 0) OBTOFSR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTOFSR.word,  ioPro.sen.obt[0][0].OBTCORE.OBTOFSR.word));
//        Ddim_Print(("impro_senobt_set_area(0, 0) OBTOFSGR(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTOFSGR.word, ioPro.sen.obt[0][0].OBTCORE.OBTOFSGR.word));
//        Ddim_Print(("impro_senobt_set_area(0, 0) OBTOFSGB(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTOFSGB.word, ioPro.sen.obt[0][0].OBTCORE.OBTOFSGB.word));
//        Ddim_Print(("impro_senobt_set_area(0, 0) OBTOFSB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTOFSB.word,  ioPro.sen.obt[0][0].OBTCORE.OBTOFSB.word));
//        Ddim_Print(("impro_senobt_set_area(0, 1) OBTOFSR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTOFSR.word,  ioPro.sen.obt[0][1].OBTCORE.OBTOFSR.word));
//        Ddim_Print(("impro_senobt_set_area(0, 1) OBTOFSGR(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTOFSGR.word, ioPro.sen.obt[0][1].OBTCORE.OBTOFSGR.word));
//        Ddim_Print(("impro_senobt_set_area(0, 1) OBTOFSGB(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTOFSGB.word, ioPro.sen.obt[0][1].OBTCORE.OBTOFSGB.word));
//        Ddim_Print(("impro_senobt_set_area(0, 1) OBTOFSB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTOFSB.word,  ioPro.sen.obt[0][1].OBTCORE.OBTOFSB.word));
//        Ddim_Print(("impro_senobt_set_area(1, 0) OBTOFSR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTOFSR.word,  ioPro.sen.obt[1][0].OBTCORE.OBTOFSR.word));
//        Ddim_Print(("impro_senobt_set_area(1, 0) OBTOFSGR(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTOFSGR.word, ioPro.sen.obt[1][0].OBTCORE.OBTOFSGR.word));
//        Ddim_Print(("impro_senobt_set_area(1, 0) OBTOFSGB(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTOFSGB.word, ioPro.sen.obt[1][0].OBTCORE.OBTOFSGB.word));
//        Ddim_Print(("impro_senobt_set_area(1, 0) OBTOFSB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTOFSB.word,  ioPro.sen.obt[1][0].OBTCORE.OBTOFSB.word));
//        Ddim_Print(("impro_senobt_set_area(1, 1) OBTOFSR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTOFSR.word,  ioPro.sen.obt[1][1].OBTCORE.OBTOFSR.word));
//        Ddim_Print(("impro_senobt_set_area(1, 1) OBTOFSGR(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTOFSGR.word, ioPro.sen.obt[1][1].OBTCORE.OBTOFSGR.word));
//        Ddim_Print(("impro_senobt_set_area(1, 1) OBTOFSGB(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTOFSGB.word, ioPro.sen.obt[1][1].OBTCORE.OBTOFSGB.word));
//        Ddim_Print(("impro_senobt_set_area(1, 1) OBTOFSB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTOFSB.word,  ioPro.sen.obt[1][1].OBTCORE.OBTOFSB.word));
//        Ddim_Print(("impro_senobt_set_area(2, 0) OBTOFSR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTOFSR.word,  ioPro.sen.obt[2][0].OBTCORE.OBTOFSR.word));
//        Ddim_Print(("impro_senobt_set_area(2, 0) OBTOFSGR(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTOFSGR.word, ioPro.sen.obt[2][0].OBTCORE.OBTOFSGR.word));
//        Ddim_Print(("impro_senobt_set_area(2, 0) OBTOFSGB(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTOFSGB.word, ioPro.sen.obt[2][0].OBTCORE.OBTOFSGB.word));
//        Ddim_Print(("impro_senobt_set_area(2, 0) OBTOFSB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTOFSB.word,  ioPro.sen.obt[2][0].OBTCORE.OBTOFSB.word));
//        Ddim_Print(("impro_senobt_set_area(2, 1) OBTOFSR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTOFSR.word,  ioPro.sen.obt[2][1].OBTCORE.OBTOFSR.word));
//        Ddim_Print(("impro_senobt_set_area(2, 1) OBTOFSGR(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTOFSGR.word, ioPro.sen.obt[2][1].OBTCORE.OBTOFSGR.word));
//        Ddim_Print(("impro_senobt_set_area(2, 1) OBTOFSGB(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTOFSGB.word, ioPro.sen.obt[2][1].OBTCORE.OBTOFSGB.word));
//        Ddim_Print(("impro_senobt_set_area(2, 1) OBTOFSB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTOFSB.word,  ioPro.sen.obt[2][1].OBTCORE.OBTOFSB.word));
//        Ddim_Print(("impro_senobt_set_area(3, 0) OBTOFSR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTOFSR.word,  ioPro.sen.obt[3][0].OBTCORE.OBTOFSR.word));
//        Ddim_Print(("impro_senobt_set_area(3, 0) OBTOFSGR(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTOFSGR.word, ioPro.sen.obt[3][0].OBTCORE.OBTOFSGR.word));
//        Ddim_Print(("impro_senobt_set_area(3, 0) OBTOFSGB(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTOFSGB.word, ioPro.sen.obt[3][0].OBTCORE.OBTOFSGB.word));
//        Ddim_Print(("impro_senobt_set_area(3, 0) OBTOFSB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTOFSB.word,  ioPro.sen.obt[3][0].OBTCORE.OBTOFSB.word));
//        Ddim_Print(("impro_senobt_set_area(3, 1) OBTOFSR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTOFSR.word,  ioPro.sen.obt[3][1].OBTCORE.OBTOFSR.word));
//        Ddim_Print(("impro_senobt_set_area(3, 1) OBTOFSGR(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTOFSGR.word, ioPro.sen.obt[3][1].OBTCORE.OBTOFSGR.word));
//        Ddim_Print(("impro_senobt_set_area(3, 1) OBTOFSGB(0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTOFSGB.word, ioPro.sen.obt[3][1].OBTCORE.OBTOFSGB.word));
//        Ddim_Print(("impro_senobt_set_area(3, 1) OBTOFSB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTOFSB.word,  ioPro.sen.obt[3][1].OBTCORE.OBTOFSB.word));

		// Maximum value parameter
		ch = E_IM_PRO_OBT_CH_3_1;
		self->priv->ercd = impro_senobt_set_offset(self->priv->improSenobt, ch, &offsetMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobt_set_offset() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_5(self->priv->imPro14Print, "max_para", ch, &offsetMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_OBT_CH_0_0;
		self->priv->ercd = impro_senobt_set_offset(self->priv->improSenobt, ch, &offsetMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobt_set_offset() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_5(self->priv->imPro14Print, "min_para", ch, &offsetMin);
		}
	}
}

void ct_im_pro1_4_6(CtImPro14* self, const kuint32 idx) {
	kuchar ch;
	T_IM_PRO_RGB2 obcnt;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTDATAR.word,     ioPro.sen.obt[0][0].OBTCORE.OBTDATAR.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTDATAGR.word,    ioPro.sen.obt[0][0].OBTCORE.OBTDATAGR.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTDATAGB.word,    ioPro.sen.obt[0][0].OBTCORE.OBTDATAGB.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][0].OBTCORE.OBTDATAB.word,     ioPro.sen.obt[0][0].OBTCORE.OBTDATAB.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTDATAR.word,     ioPro.sen.obt[0][1].OBTCORE.OBTDATAR.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTDATAGR.word,    ioPro.sen.obt[0][1].OBTCORE.OBTDATAGR.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTDATAGB.word,    ioPro.sen.obt[0][1].OBTCORE.OBTDATAGB.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[0][1].OBTCORE.OBTDATAB.word,     ioPro.sen.obt[0][1].OBTCORE.OBTDATAB.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTDATAR.word,     ioPro.sen.obt[1][0].OBTCORE.OBTDATAR.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTDATAGR.word,    ioPro.sen.obt[1][0].OBTCORE.OBTDATAGR.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTDATAGB.word,    ioPro.sen.obt[1][0].OBTCORE.OBTDATAGB.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][0].OBTCORE.OBTDATAB.word,     ioPro.sen.obt[1][0].OBTCORE.OBTDATAB.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTDATAR.word,     ioPro.sen.obt[1][1].OBTCORE.OBTDATAR.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTDATAGR.word,    ioPro.sen.obt[1][1].OBTCORE.OBTDATAGR.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTDATAGB.word,    ioPro.sen.obt[1][1].OBTCORE.OBTDATAGB.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[1][1].OBTCORE.OBTDATAB.word,     ioPro.sen.obt[1][1].OBTCORE.OBTDATAB.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTDATAR.word,     ioPro.sen.obt[2][0].OBTCORE.OBTDATAR.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTDATAGR.word,    ioPro.sen.obt[2][0].OBTCORE.OBTDATAGR.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTDATAGB.word,    ioPro.sen.obt[2][0].OBTCORE.OBTDATAGB.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][0].OBTCORE.OBTDATAB.word,     ioPro.sen.obt[2][0].OBTCORE.OBTDATAB.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTDATAR.word,     ioPro.sen.obt[2][1].OBTCORE.OBTDATAR.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTDATAGR.word,    ioPro.sen.obt[2][1].OBTCORE.OBTDATAGR.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTDATAGB.word,    ioPro.sen.obt[2][1].OBTCORE.OBTDATAGB.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[2][1].OBTCORE.OBTDATAB.word,     ioPro.sen.obt[2][1].OBTCORE.OBTDATAB.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTDATAR.word,     ioPro.sen.obt[3][0].OBTCORE.OBTDATAR.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTDATAGR.word,    ioPro.sen.obt[3][0].OBTCORE.OBTDATAGR.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTDATAGB.word,    ioPro.sen.obt[3][0].OBTCORE.OBTDATAGB.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][0].OBTCORE.OBTDATAB.word,     ioPro.sen.obt[3][0].OBTCORE.OBTDATAB.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAR  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTDATAR.word,     ioPro.sen.obt[3][1].OBTCORE.OBTDATAR.word ));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGR (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTDATAGR.word,    ioPro.sen.obt[3][1].OBTCORE.OBTDATAGR.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAGB (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTDATAGB.word,    ioPro.sen.obt[3][1].OBTCORE.OBTDATAGB.word));
//        Ddim_Print(("Im_PRO_OBT_Get_OBTata(0, 0) OBTDATAB  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.obt[3][1].OBTCORE.OBTDATAB.word,     ioPro.sen.obt[3][1].OBTCORE.OBTDATAB.word ));

		// Maximum value parameter
		ch = E_IM_PRO_OBT_CH_3_1;
		self->priv->ercd = impro_senobt_set_obt_data(self->priv->improSenobt, ch, &obcnt);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("Im_PRO_OBT_Get_OBTata() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_6(self->priv->imPro14Print, "max_para", ch, &obcnt);
		}

		ch = E_IM_PRO_OBT_CH_0_0;
		// Minimum value parameter
		self->priv->ercd = impro_senobt_set_obt_data(self->priv->improSenobt, ch, &obcnt);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("Im_PRO_OBT_Get_OBTata() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_6(self->priv->imPro14Print, "min_para", ch, &obcnt);
		}

		// invalid value parameter
		self->priv->ercd = impro_senobt_set_obt_data(self->priv->improSenobt, ch, NULL);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("Im_PRO_OBT_Get_OBTata() invalid Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_6(self->priv->imPro14Print, "invalid", ch, &obcnt);
		}
    }
}

void ct_im_pro1_4_7(CtImPro14* self, const kuint32 idx)
{
	E_IM_PRO_OBT_CH ch;//TODO
	const TimproRdmaObtAddr* addr;

	if (idx == 1) {
		// max parameter
		ch = E_IM_PRO_OBT_CH_3_1;//TODO
		self->priv->ercd = impro_senobt_get_rdma_addr_obt_cntl(self->priv->improSenobt, ch, &addr);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobt_get_rdma_addr_obt_cntl() Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_7(self->priv->imPro14Print, "max_para", ch, &addr);
		}

		// min parameter
		ch = E_IM_PRO_OBT_CH_0_0;
		self->priv->ercd = impro_senobt_get_rdma_addr_obt_cntl(self->priv->improSenobt, ch, &addr);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senobt_get_rdma_addr_obt_cntl() Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_7(self->priv->imPro14Print, "min_para", ch, &addr);
		}

		// invalid value parameter
		self->priv->ercd = impro_senobt_set_obt_data(self->priv->improSenobt, ch, NULL);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senobt_get_rdma_addr_obt_cntl() invalid Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_4_print_7(self->priv->imPro14Print, "invalid", ch, &addr);
		}

	}
}

void ct_im_pro1_4_8(CtImPro14* self, const kuint32 idx)
{
	kuchar ch;

	if (idx == 1) {
		// max parameter
		ch = E_IM_PRO_DMIPI_CH3;
		self->priv->ercd = impro_sendmipi_init(self->priv->improSendmipi, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_init(%u) Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_4_print_8(self->priv->imPro14Print, "max_para", ch);
		}

		// min parameter
		ch = E_IM_PRO_DMIPI_CH0;
		self->priv->ercd = impro_sendmipi_init(self->priv->improSendmipi, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_init(%u) Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_4_print_8(self->priv->imPro14Print, "min_para", ch);
		}
	}
}

void ct_im_pro1_4_9(CtImPro14* self, const kuint32 idx)
{
	kuchar ch;

	if (idx == 1) {
		// max parameter
		ch = E_IM_PRO_DMIPI_CH3;
		self->priv->ercd = impro_sendmipi_sr(self->priv->improSendmipi, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_sr(%u) Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_4_print_9(self->priv->imPro14Print, "max_para", ch);
		}

		// min parameter
		ch = E_IM_PRO_DMIPI_CH0;
		self->priv->ercd = impro_sendmipi_sr(self->priv->improSendmipi, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_sr(%u) Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_4_print_9(self->priv->imPro14Print, "min_para", ch);
		}
	}
}
#endif //CO_CT_IM_PRO_DISABLE

CtImPro14* ct_im_pro1_4_new(void)
{
	CtImPro14* self = k_object_new_with_private(CT_TYPE_IM_PRO1_4, sizeof(CtImPro14Private));

	return self;
}

