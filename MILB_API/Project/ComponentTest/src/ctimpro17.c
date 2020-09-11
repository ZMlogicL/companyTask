/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro17
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsenlvds.h"
#include "improsentop.h"
#include "ctimpro17.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro17, ct_im_pro1_7)
#define CT_IM_PRO1_7_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro17Private, CT_TYPE_IM_PRO1_7))


struct _CtImPro17Private
{
	ImproSenlvds *improSenlvds;
	ImproSentop *improSentop;
	ImPro17Print *imPro17Print;
	kint32 ercd;
};


/**********
 * IMPL
 */
static void ct_im_pro1_7_constructor(CtImPro17 *self)
{
	self->priv = CT_IM_PRO1_7_GET_PRIVATE(self);
	self->priv->improSenlvds = impro_senlvds_new();
	self->priv->improSentop = impro_sentop_new();
	self->priv->imPro17Print = im_pro_1_7_print_new();
	self->priv->ercd = 0;
}

static void ct_im_pro1_7_destructor(CtImPro17 *self)
{
	CtImPro17Private *priv = CT_IM_PRO1_7_GET_PRIVATE(self);

	if (priv->improSenlvds) {
		k_object_unref(priv->improSenlvds);
		priv->improSenlvds = NULL;
	}

	if (priv->improSentop) {
		k_object_unref(priv->improSentop);
		priv->improSentop = NULL;
	}

	if (priv->imPro17Print) {
		k_object_unref(priv->imPro17Print);
		priv->imPro17Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro1_7_0(CtImPro17* self, const kuint32 idx)
{
	kuchar paenTrg;
	kuchar ch;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senlvds_set_paen(0) LVDSPAEN  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.lvds[0].LVDSPAEN,    ioPro.sen.lvds[0].LVDSPAEN));
//        Ddim_Print(("impro_senlvds_set_paen(1) LVDSPAEN  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.lvds[1].LVDSPAEN,    ioPro.sen.lvds[1].LVDSPAEN));
//        Ddim_Print(("impro_senlvds_set_paen(2) LVDSPAEN  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.lvds[2].LVDSPAEN,    ioPro.sen.lvds[2].LVDSPAEN));
//        Ddim_Print(("impro_senlvds_set_paen(3) LVDSPAEN  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.lvds[3].LVDSPAEN,    ioPro.sen.lvds[3].LVDSPAEN));

// enable value parameter
		ch = E_IM_PRO_LVDS_CH_3;
		paenTrg = 1;
		self->priv->ercd = impro_senlvds_set_paen(self->priv->improSenlvds, ch, paenTrg);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_set_paen() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_7_print_0(self->priv->imPro17Print, "max_para", ch, paenTrg);
		}

		// disable value parameter
		ch = E_IM_PRO_LVDS_CH_0;
		paenTrg = 0;
		self->priv->ercd = impro_senlvds_set_paen(self->priv->improSenlvds, ch, paenTrg);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_set_paen() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_7_print_0(self->priv->imPro17Print, "min_para", ch, paenTrg);
		}

		// macro running error test
		ch = E_IM_PRO_LVDS_CH_0;
		paenTrg = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.lvds[ch].lvdstrg.bit.lvdstrg = D_IM_PRO_TRG_STATUS_RUNNING;
#else
		impro_senlvds_start(self->priv->improSenlvds, ch);
#endif
		self->priv->ercd = impro_senlvds_set_paen(self->priv->improSenlvds, ch, paenTrg);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_set_paen() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_7_print_0(self->priv->imPro17Print, "macro running error", ch, paenTrg);
		}
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.lvds[ch].lvdstrg.bit.lvdstrg = D_IM_PRO_TRG_STATUS_STOPPED;
#else
		impro_senlvds_stop(self->priv->improSenlvds, ch);
#endif
	}
}

void ct_im_pro1_7_1(CtImPro17* self, const kuint32 idx)
{
	T_IM_PRO_SENTOP_CPHY_DELAYLINE_MONITOR status;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sentop_cphy_get_delay_line_monitor() phy0dlmoni1    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.phy0dlmoni.phy0dlmoni1.word,  ioPro.sen.sentop.phy0dlmoni.phy0dlmoni1.word));
//        Ddim_Print(("impro_sentop_cphy_get_delay_line_monitor() phy0dlmoni2    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.phy0dlmoni.phy0dlmoni2.word,  ioPro.sen.sentop.phy0dlmoni.phy0dlmoni2.word));
//        Ddim_Print(("impro_sentop_cphy_get_delay_line_monitor() phy0dlmoni3    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.phy0dlmoni.phy0dlmoni3.word,  ioPro.sen.sentop.phy0dlmoni.phy0dlmoni3.word));
//        Ddim_Print(("impro_sentop_cphy_get_delay_line_monitor() phy1dlmoni1    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.phy1dlmoni.phy1dlmoni1.word,  ioPro.sen.sentop.phy1dlmoni.phy1dlmoni1.word));
//        Ddim_Print(("impro_sentop_cphy_get_delay_line_monitor() phy1dlmoni2    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.phy1dlmoni.phy1dlmoni2.word,  ioPro.sen.sentop.phy1dlmoni.phy1dlmoni2.word));
//        Ddim_Print(("impro_sentop_cphy_get_delay_line_monitor() phy1dlmoni3    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.phy1dlmoni.phy1dlmoni3.word,  ioPro.sen.sentop.phy1dlmoni.phy1dlmoni3.word));
//        Ddim_Print(("impro_sentop_cphy_get_delay_line_monitor() phy2dlmoni1    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.phy2dlmoni.phy2dlmoni1.word,  ioPro.sen.sentop.phy2dlmoni.phy2dlmoni1.word));
//        Ddim_Print(("impro_sentop_cphy_get_delay_line_monitor() phy2dlmoni2    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.phy2dlmoni.phy2dlmoni2.word,  ioPro.sen.sentop.phy2dlmoni.phy2dlmoni2.word));
//        Ddim_Print(("impro_sentop_cphy_get_delay_line_monitor() phy2dlmoni3    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.phy2dlmoni.phy2dlmoni3.word,  ioPro.sen.sentop.phy2dlmoni.phy2dlmoni3.word));
//        Ddim_Print(("impro_sentop_cphy_get_delay_line_monitor() phy3dlmoni1    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.phy3dlmoni.phy3dlmoni1.word,  ioPro.sen.sentop.phy3dlmoni.phy3dlmoni1.word));
//        Ddim_Print(("impro_sentop_cphy_get_delay_line_monitor() phy3dlmoni2    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.phy3dlmoni.phy3dlmoni2.word,  ioPro.sen.sentop.phy3dlmoni.phy3dlmoni2.word));
//        Ddim_Print(("impro_sentop_cphy_get_delay_line_monitor() phy3dlmoni3    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.phy3dlmoni.phy3dlmoni3.word,  ioPro.sen.sentop.phy3dlmoni.phy3dlmoni3.word));

// Maximum value parameter
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sentop.phy0dlmoni.phy0dlmoni1.bit.phy0CodeCp0 = 1;
		ioPro.sen.sentop.phy0dlmoni.phy0dlmoni2.bit.phy0CodeCp1 = 1;
		ioPro.sen.sentop.phy0dlmoni.phy0dlmoni3.bit.phy0CodeCp2 = 1;
		ioPro.sen.sentop.phy1dlmoni.phy1dlmoni1.bit.phy1CodeCp0 = 0x3FFFF;
		ioPro.sen.sentop.phy1dlmoni.phy1dlmoni2.bit.phy1CodeCp1 = 0x3FFFF;
		ioPro.sen.sentop.phy1dlmoni.phy1dlmoni3.bit.phy1CodeCp2 = 0x3FFFF;
		ioPro.sen.sentop.phy2dlmoni.phy2dlmoni1.bit.phy2CodeCp0 = 0x3FFFF;
		ioPro.sen.sentop.phy2dlmoni.phy2dlmoni2.bit.phy2CodeCp1 = 0x3FFFF;
		ioPro.sen.sentop.phy2dlmoni.phy2dlmoni3.bit.phy2CodeCp2 = 0x3FFFF;
		ioPro.sen.sentop.phy3dlmoni.phy3dlmoni1.bit.phy3CodeCp0 = 0x3FFFF;
		ioPro.sen.sentop.phy3dlmoni.phy3dlmoni2.bit.phy3CodeCp1 = 0x3FFFF;
		ioPro.sen.sentop.phy3dlmoni.phy3dlmoni3.bit.phy3CodeCp2 = 0x3FFFF;
#endif  // CO_DEBUG_ON_PC
		self->priv->ercd = impro_sentop_cphy_get_delay_line_monitor(self->priv->improSentop, &status);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_cphy_get_delay_line_monitor() max_para Error self->priv->ercd=0x%x\n",
							self->priv->ercd));
		} else {
			im_pro_1_7_print_1(self->priv->imPro17Print, "max_para", &status);
		}

#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sentop.phy0dlmoni.phy0dlmoni1.bit.phy0CodeCp0 = 0;
		ioPro.sen.sentop.phy0dlmoni.phy0dlmoni2.bit.phy0CodeCp1 = 0;
		ioPro.sen.sentop.phy0dlmoni.phy0dlmoni3.bit.phy0CodeCp2 = 0;
		ioPro.sen.sentop.phy1dlmoni.phy1dlmoni1.bit.phy1CodeCp0 = 0;
		ioPro.sen.sentop.phy1dlmoni.phy1dlmoni2.bit.phy1CodeCp1 = 0;
		ioPro.sen.sentop.phy1dlmoni.phy1dlmoni3.bit.phy1CodeCp2 = 0;
		ioPro.sen.sentop.phy2dlmoni.phy2dlmoni1.bit.phy2CodeCp0 = 0;
		ioPro.sen.sentop.phy2dlmoni.phy2dlmoni2.bit.phy2CodeCp1 = 0;
		ioPro.sen.sentop.phy2dlmoni.phy2dlmoni3.bit.phy2CodeCp2 = 0;
		ioPro.sen.sentop.phy3dlmoni.phy3dlmoni1.bit.phy3CodeCp0 = 0;
		ioPro.sen.sentop.phy3dlmoni.phy3dlmoni2.bit.phy3CodeCp1 = 0;
		ioPro.sen.sentop.phy3dlmoni.phy3dlmoni3.bit.phy3CodeCp2 = 0;
#endif  // CO_DEBUG_ON_PC
		// Minimum value parameter
		self->priv->ercd = impro_sentop_cphy_get_delay_line_monitor(self->priv->improSentop, &status);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_cphy_get_delay_line_monitor() min_para Error self->priv->ercd=0x%x\n",
							self->priv->ercd));
		} else {
			im_pro_1_7_print_1(self->priv->imPro17Print, "min_para", &status);
		}

		// invalid value parameter
		self->priv->ercd = impro_sentop_cphy_get_delay_line_monitor(self->priv->improSentop, NULL);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_cphy_get_delay_line_monitor() invalid Error self->priv->ercd=0x%x\n",
							self->priv->ercd));
		} else {
			im_pro_1_7_print_1(self->priv->imPro17Print, "invalid", &status);
		}
	}
}

void ct_im_pro1_7_2(CtImPro17* self, const kuint32 idx)
{
	TimproSentopCphyCommonIfMonitor status;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sentop_cphy_get_common_if_monitor(0) phycmoni1 (0x%08lx, %llx)\n", (kulong)&ioPro.sen.sentop.phycmoni.phycmoni1.dword,    ioPro.sen.sentop.phycmoni.phycmoni1.dword));
//        Ddim_Print(("impro_sentop_cphy_get_common_if_monitor(0) phycmoni2 (0x%08lx, %llx)\n", (kulong)&ioPro.sen.sentop.phycmoni.phycmoni2.dword,    ioPro.sen.sentop.phycmoni.phycmoni2.dword));
//        Ddim_Print(("impro_sentop_cphy_get_common_if_monitor(0) phycmoni3 (0x%08lx, %llx)\n", (kulong)&ioPro.sen.sentop.phycmoni.phycmoni3.dword,    ioPro.sen.sentop.phycmoni.phycmoni3.dword));
//        Ddim_Print(("impro_sentop_cphy_get_common_if_monitor(0) phycmoni4 (0x%08lx, %llx)\n", (kulong)&ioPro.sen.sentop.phycmoni.phycmoni4.dword,    ioPro.sen.sentop.phycmoni.phycmoni4.dword));

// Maximum value parameter
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sentop.phycmoni.phycmoni1.bit.phy0Cdrmon = 0xFFFFFFFFFFFFFFFF;
		ioPro.sen.sentop.phycmoni.phycmoni2.bit.phy1Cdrmon = 0xFFFFFFFFFFFFFFFF;
		ioPro.sen.sentop.phycmoni.phycmoni3.bit.phy2Cdrmon = 0xFFFFFFFFFFFFFFFF;
		ioPro.sen.sentop.phycmoni.phycmoni4.bit.phy3Cdrmon = 0xFFFFFFFFFFFFFFFF;
#endif  // CO_DEBUG_ON_PC
		self->priv->ercd = impro_sentop_cphy_get_common_if_monitor(self->priv->improSentop, &status);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_cphy_get_common_if_monitor() max_para Error self->priv->ercd=0x%x\n",
							self->priv->ercd));
		} else {
			im_pro_1_7_print_2(self->priv->imPro17Print, "max_para", &status);
		}

#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sentop.phycmoni.phycmoni1.bit.phy0Cdrmon = 0;
		ioPro.sen.sentop.phycmoni.phycmoni2.bit.phy1Cdrmon = 0;
		ioPro.sen.sentop.phycmoni.phycmoni3.bit.phy2Cdrmon = 0;
		ioPro.sen.sentop.phycmoni.phycmoni4.bit.phy3Cdrmon = 0;
#endif  // CO_DEBUG_ON_PC
		// Minimum value parameter
		self->priv->ercd = impro_sentop_cphy_get_common_if_monitor(self->priv->improSentop, &status);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_cphy_get_common_if_monitor() min_para Error self->priv->ercd=0x%x\n",
							self->priv->ercd));
		} else {
			im_pro_1_7_print_2(self->priv->imPro17Print, "min_para", &status);
		}

		// invalid value parameter
		self->priv->ercd = impro_sentop_cphy_get_common_if_monitor(self->priv->improSentop, NULL);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_cphy_get_common_if_monitor() invalid Error self->priv->ercd=0x%x\n",
							self->priv->ercd));
		} else {
			im_pro_1_7_print_2(self->priv->imPro17Print, "invalid", &status);
		}
	}
}
#endif //CO_CT_IM_PRO_DISABLE

CtImPro17* ct_im_pro1_7_new(void)
{
	CtImPro17* self = k_object_new_with_private(CT_TYPE_IM_PRO1_7, sizeof(CtImPro17Private));

	return self;
}

