/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro15
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsendmipi.h"
#include "improsencmipi.h"
#include "ctimpro15.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro15, ct_im_pro1_5)
#define CT_IM_PRO1_5_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro15Private, CT_TYPE_IM_PRO1_5))


struct _CtImPro15Private
{
	ImproSendmipi *improSendmipi;
	ImproSencmipi *improSencmipi;
	ImPro15Print *imPro15Print;
	kint32 ercd;
};


/**********
 * IMPL
 */
static void ct_im_pro1_5_constructor(CtImPro15 *self)
{
	self->priv = CT_IM_PRO1_5_GET_PRIVATE(self);
	self->priv->improSendmipi = impro_sendmipi_new();
	self->priv->improSencmipi = impro_sencmipi_new();
	self->priv->imPro15Print = im_pro_1_5_print_new();
	self->priv->ercd = 0;
}

static void ct_im_pro1_5_destructor(CtImPro15 *self)
{
	CtImPro15Private *priv = CT_IM_PRO1_5_GET_PRIVATE(self);

	if (priv->improSendmipi) {
		k_object_unref(priv->improSendmipi);
		priv->improSendmipi = NULL;
	}

	if (priv->improSencmipi) {
		k_object_unref(priv->improSencmipi);
		priv->improSencmipi = NULL;
	}

	if (priv->imPro15Print) {
		k_object_unref(priv->imPro15Print);
		priv->imPro15Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro1_5_0(CtImPro15* self, const kuint32 idx)
{
	kuchar ch;

	if (idx == 1) {
		// max parameter
		ch = E_IM_PRO_DMIPI_CH3;//TODO
		self->priv->ercd = impro_sendmipi_start(self->priv->improSendmipi, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_start() Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_0(self->priv->imPro15Print, "max_para", ch);
		}

		// min parameter
		ch = E_IM_PRO_DMIPI_CH0;
		self->priv->ercd = impro_sendmipi_start(self->priv->improSendmipi, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_start() Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_0(self->priv->imPro15Print, "min_para", ch);
		}
	}
}

void ct_im_pro1_5_1(CtImPro15* self, const kuint32 idx)
{
	kuchar ch;
	kuchar force = 0;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sendmipi_stop(0) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[0].mpitrg.word,   ioPro.sen.mipid[0].mpitrg.word));
//        Ddim_Print(("impro_sendmipi_stop(1) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[1].mpitrg.word,   ioPro.sen.mipid[1].mpitrg.word));
//        Ddim_Print(("impro_sendmipi_stop(2) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[2].mpitrg.word,   ioPro.sen.mipid[2].mpitrg.word));
//        Ddim_Print(("impro_sendmipi_stop(3) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[3].mpitrg.word,   ioPro.sen.mipid[3].mpitrg.word));
		// Maximum value parameter
		ch = E_IM_PRO_DMIPI_CH3;
		force = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sg[ch].sgtrg.bit.sgtrg = 3;
#endif
		self->priv->ercd = impro_sendmipi_stop(self->priv->improSendmipi, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sendmipi_stop(%u, %u) max_para Error self->priv->ercd=0x%x\n", ch, force, self->priv->ercd));
		} else {
			im_pro_1_5_print_1(self->priv->imPro15Print, "max_para", ch, force);
		}

		// Minimum value parameter
		ch = E_IM_PRO_DMIPI_CH0;
		force = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipid[ch].mpitrg.bit.mpitrg = 3;
#endif
		self->priv->ercd = impro_sendmipi_stop(self->priv->improSendmipi, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sendmipi_stop(%u, %u) min_para Error self->priv->ercd=0x%x\n", ch, force, self->priv->ercd));
		} else {
			im_pro_1_5_print_1(self->priv->imPro15Print, "min_para", ch, force);
		}

		// Maximum value parameter
		ch = E_IM_PRO_DMIPI_CH3;
		force = 1;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipid[ch].mpitrg.bit.mpitrg = 3;
#endif
		self->priv->ercd = impro_sendmipi_stop(self->priv->improSendmipi, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sendmipi_stop(%u, %u) max_para Error self->priv->ercd=0x%x\n", ch, force, self->priv->ercd));
		} else {
			im_pro_1_5_print_1(self->priv->imPro15Print, "max_para", ch, force);
		}

		// Minimum value parameter
		ch = E_IM_PRO_DMIPI_CH0;
		force = 1;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipid[ch].mpitrg.bit.mpitrg = 3;
#endif
		self->priv->ercd = impro_sendmipi_stop(self->priv->improSendmipi, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sendmipi_stop(%u, %u) min_para Error self->priv->ercd=0x%x\n", ch, force, self->priv->ercd));
		} else {
			im_pro_1_5_print_1(self->priv->imPro15Print, "min_para", ch, force);
		}
	}
}

void ct_im_pro1_5_2(CtImPro15* self, const kuint32 idx)
{
    kuchar ch;
    TimproDmipiCtrl dmipiCtrlMax = {
        .laneSel = ImproSencmipi_E_IM_PRO_CMIPI_LANE_4,
        .inputDataMode[0] = ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_USER_DEF,
        .outputDataMode[0] = ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_8POINT,
        .vcModeSel[0] = ImproSencmipi_E_IM_PRO_CMIPI_VC_INVALID,
        .outputDtSel[0] = ImproSencmipi_E_IM_PRO_CMIPI_DT_OUT_EN,
        .outputDtSetting[0] = 63,
        .inputDataMode[1] = ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_USER_DEF,
        .outputDataMode[1] = ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_8POINT,
        .vcModeSel[1] = ImproSencmipi_E_IM_PRO_CMIPI_VC_INVALID,
        .outputDtSel[1] = ImproSencmipi_E_IM_PRO_CMIPI_DT_OUT_EN,
        .outputDtSetting[1] = 63,
        .phyCtrl.rxsmt_c_val = 0x7,
        .phyCtrl.rxsmt_d_val = 0xE,
        .phyCtrl.rxsyncmode = E_IM_PRO_DMIPI_RXSYNCMODE_1BIT_DISCREPANCY,//TODO
        .outCycle[0] = ImproSendmipi_E_IM_PRO_DMIPI_SEL_CYCLE_2,
        .outCycle[1] = ImproSendmipi_E_IM_PRO_DMIPI_SEL_CYCLE_2,
        .phyCtrl.rxenable = ImproSendmipi_E_IM_PRO_DMIPI_RXENABLE_OUT1,
    };

    TimproDmipiCtrl dmipiCtrlMin = {
        .laneSel = ImproSencmipi_E_IM_PRO_CMIPI_LANE_1,
        .inputDataMode[0] = ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_8BIT,
        .outputDataMode[0] = ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_NO_OUTPUT,
        .vcModeSel[0] = ImproSencmipi_E_IM_PRO_CMIPI_VC_0,
        .outputDtSel[0] = ImproSencmipi_E_IM_PRO_CMIPI_DT_OUT_DIS,
        .outputDtSetting[0] = 0,
        .inputDataMode[1] = ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_8BIT,
        .outputDataMode[1] = ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_NO_OUTPUT,
        .vcModeSel[1] = ImproSencmipi_E_IM_PRO_CMIPI_VC_0,
        .outputDtSel[1] = ImproSencmipi_E_IM_PRO_CMIPI_DT_OUT_DIS,
        .outputDtSetting[1] = 0,
        .phyCtrl.rxsmt_c_val = 0x7,
        .phyCtrl.rxsmt_d_val = 0xE,
        .phyCtrl.rxsyncmode = E_IM_PRO_DMIPI_RXSYNCMODE_PERFECTLY_MATCHED,//TODO
        .outCycle[0] = ImproSendmipi_E_IM_PRO_DMIPI_SEL_CYCLE_0,
        .outCycle[1] = ImproSendmipi_E_IM_PRO_DMIPI_SEL_CYCLE_0,
        .phyCtrl.rxenable = ImproSendmipi_E_IM_PRO_DMIPI_RXENABLE_ALL_OUT0,
    };

    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sendmipi_ctrl(0) MPILMODE     (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[0].MPILMODE.word  ,       ioPro.sen.mipid[0].MPILMODE.word  ));
//        Ddim_Print(("impro_sendmipi_ctrl(0) MPIIOMD0     (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[0].MPIIOMD0.word  ,       ioPro.sen.mipid[0].MPIIOMD0.word  ));
//        Ddim_Print(("impro_sendmipi_ctrl(0) MPIIOMD1     (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[0].MPIIOMD1.word  ,       ioPro.sen.mipid[0].MPIIOMD1.word  ));
//        Ddim_Print(("impro_sendmipi_ctrl(0) MPIDPI       (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[0].MPIDPI.word    ,       ioPro.sen.mipid[0].MPIDPI.word    ));
//        Ddim_Print(("impro_sendmipi_ctrl(0) MPIHDPDSEL   (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[0].MPIHDPDSEL.word,       ioPro.sen.mipid[0].MPIHDPDSEL.word));
//        Ddim_Print(("impro_sendmipi_ctrl(0) MPIDPI       (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[0].MPIDPI.word    ,       ioPro.sen.mipid[0].MPIDPI.word    ));
//
//        Ddim_Print(("impro_sendmipi_ctrl(1) MPILMODE     (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[1].MPILMODE.word  ,       ioPro.sen.mipid[1].MPILMODE.word  ));
//        Ddim_Print(("impro_sendmipi_ctrl(1) MPIIOMD0     (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[1].MPIIOMD0.word  ,       ioPro.sen.mipid[1].MPIIOMD0.word  ));
//        Ddim_Print(("impro_sendmipi_ctrl(1) MPIIOMD1     (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[1].MPIIOMD1.word  ,       ioPro.sen.mipid[1].MPIIOMD1.word  ));
//        Ddim_Print(("impro_sendmipi_ctrl(1) MPIDPI       (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[1].MPIDPI.word    ,       ioPro.sen.mipid[1].MPIDPI.word    ));
//        Ddim_Print(("impro_sendmipi_ctrl(1) MPIHDPDSEL   (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[1].MPIHDPDSEL.word,       ioPro.sen.mipid[1].MPIHDPDSEL.word));
//        Ddim_Print(("impro_sendmipi_ctrl(1) MPIDPI       (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[1].MPIDPI.word    ,       ioPro.sen.mipid[1].MPIDPI.word    ));
//
//        Ddim_Print(("impro_sendmipi_ctrl(2) MPILMODE     (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[2].MPILMODE.word  ,       ioPro.sen.mipid[2].MPILMODE.word  ));
//        Ddim_Print(("impro_sendmipi_ctrl(2) MPIIOMD0     (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[2].MPIIOMD0.word  ,       ioPro.sen.mipid[2].MPIIOMD0.word  ));
//        Ddim_Print(("impro_sendmipi_ctrl(2) MPIIOMD1     (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[2].MPIIOMD1.word  ,       ioPro.sen.mipid[2].MPIIOMD1.word  ));
//        Ddim_Print(("impro_sendmipi_ctrl(2) MPIDPI       (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[2].MPIDPI.word    ,       ioPro.sen.mipid[2].MPIDPI.word    ));
//        Ddim_Print(("impro_sendmipi_ctrl(2) MPIHDPDSEL   (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[2].MPIHDPDSEL.word,       ioPro.sen.mipid[2].MPIHDPDSEL.word));
//        Ddim_Print(("impro_sendmipi_ctrl(2) MPIDPI       (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[2].MPIDPI.word    ,       ioPro.sen.mipid[2].MPIDPI.word    ));
//
//        Ddim_Print(("impro_sendmipi_ctrl(3) MPILMODE     (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[3].MPILMODE.word  ,       ioPro.sen.mipid[3].MPILMODE.word  ));
//        Ddim_Print(("impro_sendmipi_ctrl(3) MPIIOMD0     (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[3].MPIIOMD0.word  ,       ioPro.sen.mipid[3].MPIIOMD0.word  ));
//        Ddim_Print(("impro_sendmipi_ctrl(3) MPIIOMD1     (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[3].MPIIOMD1.word  ,       ioPro.sen.mipid[3].MPIIOMD1.word  ));
//        Ddim_Print(("impro_sendmipi_ctrl(3) MPIDPI       (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[3].MPIDPI.word    ,       ioPro.sen.mipid[3].MPIDPI.word    ));
//        Ddim_Print(("impro_sendmipi_ctrl(3) MPIHDPDSEL   (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[3].MPIHDPDSEL.word,       ioPro.sen.mipid[3].MPIHDPDSEL.word));
//        Ddim_Print(("impro_sendmipi_ctrl(3) MPIDPI       (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipid[3].MPIDPI.word    ,       ioPro.sen.mipid[3].MPIDPI.word    ));
        // Maximum value parameter
		ch = E_IM_PRO_DMIPI_CH3;
		self->priv->ercd = impro_sendmipi_ctrl(self->priv->improSendmipi, ch, &dmipiCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_2(self->priv->imPro15Print, "max_para", ch, &dmipiCtrlMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_DMIPI_CH0;
		self->priv->ercd = impro_sendmipi_ctrl(self->priv->improSendmipi, ch, &dmipiCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_2(self->priv->imPro15Print, "min_para", ch, &dmipiCtrlMin);
        }
    }
}

void ct_im_pro1_5_3(CtImPro15* self, const kuint32 idx)
{
	kuchar paenTrg0;
	kuchar paenTrg1;
	kuchar ch;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sendmipi_set_paen(0) MPIPAEN0 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[0].MPIPAEN0.word,  ioPro.sen.mipid[0].MPIPAEN0.word  ));
//        Ddim_Print(("impro_sendmipi_set_paen(0) MPIPAEN1 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[0].MPIPAEN1.word,  ioPro.sen.mipid[0].MPIPAEN1.word  ));
//        Ddim_Print(("impro_sendmipi_set_paen(1) MPIPAEN0 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[1].MPIPAEN0.word,  ioPro.sen.mipid[1].MPIPAEN0.word  ));
//        Ddim_Print(("impro_sendmipi_set_paen(1) MPIPAEN1 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[1].MPIPAEN1.word,  ioPro.sen.mipid[1].MPIPAEN1.word  ));
//        Ddim_Print(("impro_sendmipi_set_paen(2) MPIPAEN0 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[2].MPIPAEN0.word,  ioPro.sen.mipid[2].MPIPAEN0.word  ));
//        Ddim_Print(("impro_sendmipi_set_paen(2) MPIPAEN1 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[2].MPIPAEN1.word,  ioPro.sen.mipid[2].MPIPAEN1.word  ));
//        Ddim_Print(("impro_sendmipi_set_paen(3) MPIPAEN0 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[3].MPIPAEN0.word,  ioPro.sen.mipid[3].MPIPAEN0.word  ));
//        Ddim_Print(("impro_sendmipi_set_paen(3) MPIPAEN1 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[3].MPIPAEN1.word,  ioPro.sen.mipid[3].MPIPAEN1.word  ));

		// enable value parameter
		ch = E_IM_PRO_DMIPI_CH3;
		paenTrg0 = 1;
		paenTrg1 = 1;
		self->priv->ercd = impro_sendmipi_set_paen(self->priv->improSendmipi, ch, paenTrg0, paenTrg1);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_set_paen() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_3(self->priv->imPro15Print, "max_para", ch, paenTrg0, paenTrg1);
		}

		// disable value parameter
		ch = E_IM_PRO_DMIPI_CH0;
		paenTrg0 = 0;
		paenTrg1 = 0;
		self->priv->ercd = impro_sendmipi_set_paen(self->priv->improSendmipi, ch, paenTrg0, paenTrg1);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_set_paen() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_3(self->priv->imPro15Print, "min_para", ch, paenTrg0, paenTrg1);
		}

		// macro running error test
		ch = E_IM_PRO_DMIPI_CH0;
		paenTrg0 = 0;
		paenTrg1 = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipid[ch].mpitrg.bit.mpitrg = D_IM_PRO_TRG_STATUS_RUNNING;
#else
		impro_sensldiv_start(self->priv->improSendmipi, ch);
#endif
		self->priv->ercd = impro_sendmipi_set_paen(self->priv->improSendmipi, ch, paenTrg0, paenTrg1);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_set_paen() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_3(self->priv->imPro15Print, "macro running error", ch, paenTrg0, paenTrg1);
		}
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipid[ch].mpitrg.bit.mpitrg = D_IM_PRO_TRG_STATUS_STOPPED;
#else
		impro_sendmipi_stop(self->priv->improSendmipi, ch, 0);
#endif
	}
}

void ct_im_pro1_5_4(CtImPro15* self, const kuint32 idx)
{
	TimproDmipiStatus status;
	E_IM_PRO_DMIPI_CH ch;//TODO

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sendmipi_get_status(0) mpidpvr.   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[0].mpidpvr.word,   ioPro.sen.mipid[0].mpidpvr.word   ));
//        Ddim_Print(("impro_sendmipi_get_status(0) mpiscs     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[0].mpiscs.word,    ioPro.sen.mipid[0].mpiscs.word    ));
//        Ddim_Print(("impro_sendmipi_get_status(1) mpidpvr.   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[1].mpidpvr.word,   ioPro.sen.mipid[1].mpidpvr.word   ));
//        Ddim_Print(("impro_sendmipi_get_status(1) mpiscs     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[1].mpiscs.word,    ioPro.sen.mipid[1].mpiscs.word    ));
//        Ddim_Print(("impro_sendmipi_get_status(2) mpidpvr.   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[2].mpidpvr.word,   ioPro.sen.mipid[2].mpidpvr.word   ));
//        Ddim_Print(("impro_sendmipi_get_status(2) mpiscs     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[2].mpiscs.word,    ioPro.sen.mipid[2].mpiscs.word    ));
//        Ddim_Print(("impro_sendmipi_get_status(3) mpidpvr.   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[3].mpidpvr.word,   ioPro.sen.mipid[3].mpidpvr.word   ));
//        Ddim_Print(("impro_sendmipi_get_status(3) mpiscs     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipid[3].mpiscs.word,    ioPro.sen.mipid[3].mpiscs.word    ));

		// Maximum value parameter
		ch = E_IM_PRO_DMIPI_CH3;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipid[ch].mpidpvr.word = 0xF8000000;
		ioPro.sen.mipid[ch].mpiscs.word = 0xF0000000;
#endif  // CO_DEBUG_ON_PC
		self->priv->ercd = impro_sendmipi_get_status(self->priv->improSendmipi, ch, &status);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_get_status() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_4(self->priv->imPro15Print, "max_para", ch, &status);
		}

		ch = E_IM_PRO_DMIPI_CH0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipid[ch].mpidpvr.word = 0;
		ioPro.sen.mipid[ch].mpiscs.word = 0;
#endif  // CO_DEBUG_ON_PC
		// Minimum value parameter
		self->priv->ercd = impro_sendmipi_get_status(self->priv->improSendmipi, ch, &status);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_get_status() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_4(self->priv->imPro15Print, "min_para", ch, &status);
		}

		// invalid value parameter
		ch = E_IM_PRO_DMIPI_CH0;
		self->priv->ercd = impro_sendmipi_get_status(self->priv->improSendmipi, ch, NULL);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sendmipi_get_status() invalid Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_4(self->priv->imPro15Print, "invalid", ch, &status);
		}

	}
}

void ct_im_pro1_5_5(CtImPro15* self, const kuint32 idx)
{
	kuchar ch;

	if (idx == 1) {
		// max parameter
		ch = E_IM_PRO_CMIPI_CH3;
		self->priv->ercd = impro_sencmipi_init(self->priv->improSencmipi, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_init(%u) Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_5_print_5(self->priv->imPro15Print, "max_para", ch);
		}

		// min parameter
		ch = E_IM_PRO_CMIPI_CH0;
		self->priv->ercd = impro_sencmipi_init(self->priv->improSencmipi, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_init(%u) Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_5_print_5(self->priv->imPro15Print, "min_para", ch);
		}
	}
}

void ct_im_pro1_5_6(CtImPro15* self, const kuint32 idx)
{
	kuchar ch;

	if (idx == 1) {
		// max parameter
		ch = E_IM_PRO_CMIPI_CH3;//TODO
		self->priv->ercd = impro_sencmipi_sr(self->priv->improSencmipi, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_sr(%u) Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_5_print_6(self->priv->imPro15Print, "max_para", ch);
		}

		// min parameter
		ch = E_IM_PRO_CMIPI_CH0;
		self->priv->ercd = impro_sencmipi_sr(self->priv->improSencmipi, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_sr(%u) Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_5_print_6(self->priv->imPro15Print, "min_para", ch);
		}
	}
}

void ct_im_pro1_5_7(CtImPro15* self, const kuint32 idx)
{
	kuchar ch;

	if (idx == 1) {
		// max parameter
		ch = E_IM_PRO_CMIPI_CH3;
		self->priv->ercd = impro_sencmipi_start(self->priv->improSencmipi, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_start() Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_7(self->priv->imPro15Print, "max_para", ch);
		}

		// min parameter
		ch = E_IM_PRO_CMIPI_CH0;
		self->priv->ercd = impro_sencmipi_start(self->priv->improSencmipi, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_start() Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_7(self->priv->imPro15Print, "min_para", ch);
		}
	}
}

void ct_im_pro1_5_8(CtImPro15* self, const kuint32 idx)
{
	kuchar ch;
	kuchar force = 0;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sencmipi_stop(0) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[0].mpictrg.word,  ioPro.sen.mipic[0].mpictrg.word   ));
//        Ddim_Print(("impro_sencmipi_stop(1) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[1].mpictrg.word,  ioPro.sen.mipic[1].mpictrg.word   ));
//        Ddim_Print(("impro_sencmipi_stop(2) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[2].mpictrg.word,  ioPro.sen.mipic[2].mpictrg.word   ));
//        Ddim_Print(("impro_sencmipi_stop(3) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[3].mpictrg.word,  ioPro.sen.mipic[3].mpictrg.word   ));
		// Maximum value parameter
		ch = E_IM_PRO_CMIPI_CH3;
		force = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sg[ch].sgtrg.bit.sgtrg = 3;
#endif
		self->priv->ercd = impro_sencmipi_stop(self->priv->improSencmipi, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sencmipi_stop(%u, %u) max_para Error self->priv->ercd=0x%x\n", ch, force, self->priv->ercd));
		} else {
			im_pro_1_5_print_8(self->priv->imPro15Print, "max_para", ch, force);
		}

		// Minimum value parameter
		ch = E_IM_PRO_CMIPI_CH0;
		force = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipic[ch].mpictrg.bit.mpictrg = 3;
#endif
		self->priv->ercd = impro_sencmipi_stop(self->priv->improSencmipi, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sencmipi_stop(%u, %u) min_para Error self->priv->ercd=0x%x\n", ch, force, self->priv->ercd));
		} else {
			im_pro_1_5_print_8(self->priv->imPro15Print, "min_para", ch, force);
		}

		// Maximum value parameter
		ch = E_IM_PRO_CMIPI_CH3;
		force = 1;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipic[ch].mpictrg.bit.mpictrg = 3;
#endif
		self->priv->ercd = impro_sencmipi_stop(self->priv->improSencmipi, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sencmipi_stop(%u, %u) max_para Error self->priv->ercd=0x%x\n", ch, force, self->priv->ercd));
		} else {
			im_pro_1_5_print_8(self->priv->imPro15Print, "max_para", ch, force);
		}

		// Minimum value parameter
		ch = E_IM_PRO_CMIPI_CH0;
		force = 1;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipic[ch].mpictrg.bit.mpictrg = 3;
#endif
		self->priv->ercd = impro_sencmipi_stop(self->priv->improSencmipi, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sencmipi_stop(%u, %u) min_para Error self->priv->ercd=0x%x\n", ch, force, self->priv->ercd));
		} else {
			im_pro_1_5_print_8(self->priv->imPro15Print, "min_para", ch, force);
		}
	}
}

void ct_im_pro1_5_9(CtImPro15* self, const kuint32 idx)
{
    kuchar ch;
    TimproCmipiCtrl cmipiCtrlMax = {
        .laneSel = ImproSencmipi_E_IM_PRO_CMIPI_LANE_4,
        .inputDataMode[0] = ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_USER_DEF,
        .outputDataMode[0] = ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_8POINT,
        .vcModeSel[0] = ImproSencmipi_E_IM_PRO_CMIPI_VC_INVALID,
        .outputDtSel[0] = ImproSencmipi_E_IM_PRO_CMIPI_DT_OUT_EN,
        .outputDtSetting[0] = 63,
        .inputDataMode[1] = ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_USER_DEF,
        .outputDataMode[1] = ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_8POINT,
        .vcModeSel[1] = ImproSencmipi_E_IM_PRO_CMIPI_VC_INVALID,
        .outputDtSel[1] = ImproSencmipi_E_IM_PRO_CMIPI_DT_OUT_EN,
        .outputDtSetting[1] = 63,
        .outCycle[0] = ImproSencmipi_E_IM_PRO_CMIPI_SEL_CYCLE_2,
        .outCycle[1] = ImproSencmipi_E_IM_PRO_CMIPI_SEL_CYCLE_2,
        .phyCtrl.hsSettlecnt = 15,
        .phyCtrl.hsStopcnt = 31,
        .phyCtrl.hsSyncmode = 1,
        .phyCtrl.rlrLconfig = 255,
        .phyCtrl.rlrTpsel = 255,
        .phyCtrl.rlrPrbssp = 255,
        .phyCtrl.tgrProgseq = 0x20000000000,
        .phyCtrl.forcerxmode2 = 1,
        .phyCtrl.forcerxmode1 = 1,
        .phyCtrl.forcerxmode0 = 1,
    };

    TimproCmipiCtrl cmipiCtrlMin = {
        .laneSel = ImproSencmipi_E_IM_PRO_CMIPI_LANE_1,
        .inputDataMode[0] = ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_8BIT,
        .outputDataMode[0] = ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_NO_OUTPUT,
        .vcModeSel[0] = ImproSencmipi_E_IM_PRO_CMIPI_VC_0,
        .outputDtSel[0] = ImproSencmipi_E_IM_PRO_CMIPI_DT_OUT_DIS,
        .outputDtSetting[0] = 0,
        .inputDataMode[1] = ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_8BIT,
        .outputDataMode[1] = ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_NO_OUTPUT,
        .vcModeSel[1] = ImproSencmipi_E_IM_PRO_CMIPI_VC_0,
        .outputDtSel[1] = ImproSencmipi_E_IM_PRO_CMIPI_DT_OUT_DIS,
        .outputDtSetting[1] = 0,
        .outCycle[0] = ImproSencmipi_E_IM_PRO_CMIPI_SEL_CYCLE_0,
        .outCycle[1] = ImproSencmipi_E_IM_PRO_CMIPI_SEL_CYCLE_0,
        .phyCtrl.hsSettlecnt = 0,
        .phyCtrl.hsStopcnt = 0,
        .phyCtrl.hsSyncmode = 0,
        .phyCtrl.rlrLconfig = 0,
        .phyCtrl.rlrTpsel = 0,
        .phyCtrl.rlrPrbssp = 0,
        .phyCtrl.tgrProgseq = 0,
        .phyCtrl.forcerxmode2 = 0,
        .phyCtrl.forcerxmode1 = 0,
        .phyCtrl.forcerxmode0 = 0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sencmipi_ctrl(0) MPICLMODE        (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.mipic[0].MPICLMODE.word ,       ioPro.sen.mipic[0].MPICLMODE.word ));
		// Maximum value parameter
		ch = E_IM_PRO_CMIPI_CH3;
		self->priv->ercd = impro_sencmipi_ctrl(self->priv->improSencmipi, ch, &cmipiCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_9(self->priv->imPro15Print, "max_para", ch, &cmipiCtrlMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_CMIPI_CH0;
		self->priv->ercd = impro_sencmipi_ctrl(self->priv->improSencmipi, ch, &cmipiCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_5_print_9(self->priv->imPro15Print, "min_para", ch, &cmipiCtrlMin);
		}
    }
}
#endif //CO_CT_IM_PRO_DISABLE

CtImPro15* ct_im_pro1_5_new(void)
{
	CtImPro15* self = k_object_new_with_private(CT_TYPE_IM_PRO1_5, sizeof(CtImPro15Private));

	return self;
}

