/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro11
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsentop.h"
#include "improsensg.h"
#include "improsenslvs.h"
#include "ctimpro11.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro11, ct_im_pro1_1)
#define CT_IM_PRO1_1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro11Private, CT_TYPE_IM_PRO1_1))


struct _CtImPro11Private
{
	ImproSentop *improSentop;
	ImproSensg *improSensg;
	ImproSenslvs *improSenslvs;
	ImPro11Print *imPro11Print;
	kint32 ercd;
};


/**********
 * IMPL
 */
static void ct_im_pro1_1_constructor(CtImPro11 *self)
{
	self->priv = CT_IM_PRO1_1_GET_PRIVATE(self);
	self->priv->improSentop = impro_sentop_new();
	self->priv->improSensg = impro_sensg_new();
	self->priv->improSenslvs = impro_senslvs_new();
	self->priv->imPro11Print = im_pro_1_1_print_new();
	self->priv->ercd = 0;
}

static void ct_im_pro1_1_destructor(CtImPro11 *self)
{
	CtImPro11Private *priv = CT_IM_PRO1_1_GET_PRIVATE(self);

	if (priv->improSentop) {
		k_object_unref(priv->improSentop);
		priv->improSentop = NULL;
	}

	if (priv->improSensg) {
		k_object_unref(priv->improSensg);
		priv->improSensg = NULL;
	}

	if (priv->improSenslvs) {
		k_object_unref(priv->improSenslvs);
		priv->improSenslvs = NULL;
	}

	if (priv->imPro11Print) {
		k_object_unref(priv->imPro11Print);
		priv->imPro11Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro1_1_0(CtImPro11* self, const kuint32 idx)
{
    TimproSentopSgCtrl sgCtrlMax = {
        .sgIfOutputSel[0] = ImproSentop_E_IM_PRO_SENTOP_SG_IF_OUTPUT_SEL_SG3,
        .sgIfOutputSel[1] = ImproSentop_E_IM_PRO_SENTOP_SG_IF_OUTPUT_SEL_SG3,
        .sgIfOutputSel[2] = ImproSentop_E_IM_PRO_SENTOP_SG_IF_OUTPUT_SEL_SG3,
        .sgIfOutputSel[3] = ImproSentop_E_IM_PRO_SENTOP_SG_IF_OUTPUT_SEL_SG3,
    };

    TimproSentopSgCtrl sgCtrlMin = {
        .sgIfOutputSel[0] = ImproSentop_E_IM_PRO_SENTOP_SG_IF_OUTPUT_SEL_SG0,
        .sgIfOutputSel[1] = ImproSentop_E_IM_PRO_SENTOP_SG_IF_OUTPUT_SEL_SG0,
        .sgIfOutputSel[2] = ImproSentop_E_IM_PRO_SENTOP_SG_IF_OUTPUT_SEL_SG0,
        .sgIfOutputSel[3] = ImproSentop_E_IM_PRO_SENTOP_SG_IF_OUTPUT_SEL_SG0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sentop_sg_ctrl() SLVSECCTL (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.SGOUTCTL.word,    ioPro.sen.sentop.SGOUTCTL.word));
		// Maximum value parameter
		self->priv->ercd = impro_sentop_sg_ctrl(self->priv->improSentop, &sgCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_sg_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_1_print_0(self->priv->imPro11Print, "max_para", &sgCtrlMax);
		}

		// Minimum value parameter
		self->priv->ercd = impro_sentop_sg_ctrl(self->priv->improSentop, &sgCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_sg_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_1_print_0(self->priv->imPro11Print, "min_para", &sgCtrlMin);
		}
    }
}

void ct_im_pro1_1_1(CtImPro11* self, const kuint32 idx)
{
    TimproSentopCphyCtrl cphyCtrlMax = {
        .commonIfCtrl.pregcnt = 0xFF,
        .commonIfCtrl.freqcnt = 0xFF,
        .commonIfCtrl.pdccnt = 0x1,
        .commonIfCtrl.setdf = 0x1,
        .commonIfCtrl.picodetst = 0x3F,
        .commonIfCtrl.pmonsel = 0x3,
        .commonIfCtrl.dmonsel = 0x1,
        .commonIfCtrl.cntsel = 0xFF,
        .commonIfCtrl.mulgainf = 0x3,
        .commonIfCtrl.mulgainp = 0x3,
        .commonIfCtrl.cdrfunc = 0xFF,
        .cpmodeCtrl[0].zerop3uicp0 = 0x1,
        .cpmodeCtrl[0].zerop4uicp0 = 0x1,
        .cpmodeCtrl[0].zerop5uicp0 = 0x1,
        .cpmodeCtrl[0].zerop6uicp0 = 0x1,
        .cpmodeCtrl[0].detcntCp0 = 0xFF,
        .cpmodeCtrl[0].eqEnCp0 = 0x1,
        .cpmodeCtrl[0].eqSetCp0 = 0x7,
        .cpmodeCtrl[0].zerop3uicp1 = 0x1,
        .cpmodeCtrl[0].zerop4uicp1 = 0x1,
        .cpmodeCtrl[0].zerop5uicp1 = 0x1,
        .cpmodeCtrl[0].zerop6uicp1 = 0x1,
        .cpmodeCtrl[0].detcntCp1 = 0xFF,
        .cpmodeCtrl[0].eqEnCp1 = 0x1,
        .cpmodeCtrl[0].eqSetCp1 = 0x7,
        .cpmodeCtrl[0].zerop3uicp2 = 0x1,
        .cpmodeCtrl[0].zerop4uicp2 = 0x1,
        .cpmodeCtrl[0].zerop5uicp2 = 0x1,
        .cpmodeCtrl[0].zerop6uicp2 = 0x1,
        .cpmodeCtrl[0].detcntCp2 = 0xFF,
        .cpmodeCtrl[0].eqEnCp2 = 0x1,
        .cpmodeCtrl[0].eqSetCp2 = 0x7,
        .cpmodeCtrl[1].zerop3uicp0 = 0x1,
        .cpmodeCtrl[1].zerop4uicp0 = 0x1,
        .cpmodeCtrl[1].zerop5uicp0 = 0x1,
        .cpmodeCtrl[1].zerop6uicp0 = 0x1,
        .cpmodeCtrl[1].detcntCp0 = 0xFF,
        .cpmodeCtrl[1].eqEnCp0 = 0x1,
        .cpmodeCtrl[1].eqSetCp0 = 0x7,
        .cpmodeCtrl[1].zerop3uicp1 = 0x1,
        .cpmodeCtrl[1].zerop4uicp1 = 0x1,
        .cpmodeCtrl[1].zerop5uicp1 = 0x1,
        .cpmodeCtrl[1].zerop6uicp1 = 0x1,
        .cpmodeCtrl[1].detcntCp1 = 0xFF,
        .cpmodeCtrl[1].eqEnCp1 = 0x1,
        .cpmodeCtrl[1].eqSetCp1 = 0x7,
        .cpmodeCtrl[1].zerop3uicp2 = 0x1,
        .cpmodeCtrl[1].zerop4uicp2 = 0x1,
        .cpmodeCtrl[1].zerop5uicp2 = 0x1,
        .cpmodeCtrl[1].zerop6uicp2 = 0x1,
        .cpmodeCtrl[1].detcntCp2 = 0xFF,
        .cpmodeCtrl[1].eqEnCp2 = 0x1,
        .cpmodeCtrl[1].eqSetCp2 = 0x7,
        .cpmodeCtrl[2].zerop3uicp0 = 0x1,
        .cpmodeCtrl[2].zerop4uicp0 = 0x1,
        .cpmodeCtrl[2].zerop5uicp0 = 0x1,
        .cpmodeCtrl[2].zerop6uicp0 = 0x1,
        .cpmodeCtrl[2].detcntCp0 = 0xFF,
        .cpmodeCtrl[2].eqEnCp0 = 0x1,
        .cpmodeCtrl[2].eqSetCp0 = 0x7,
        .cpmodeCtrl[2].zerop3uicp1 = 0x1,
        .cpmodeCtrl[2].zerop4uicp1 = 0x1,
        .cpmodeCtrl[2].zerop5uicp1 = 0x1,
        .cpmodeCtrl[2].zerop6uicp1 = 0x1,
        .cpmodeCtrl[2].detcntCp1 = 0xFF,
        .cpmodeCtrl[2].eqEnCp1 = 0x1,
        .cpmodeCtrl[2].eqSetCp1 = 0x7,
        .cpmodeCtrl[2].zerop3uicp2 = 0x1,
        .cpmodeCtrl[2].zerop4uicp2 = 0x1,
        .cpmodeCtrl[2].zerop5uicp2 = 0x1,
        .cpmodeCtrl[2].zerop6uicp2 = 0x1,
        .cpmodeCtrl[2].detcntCp2 = 0xFF,
        .cpmodeCtrl[2].eqEnCp2 = 0x1,
        .cpmodeCtrl[2].eqSetCp2 = 0x7,
        .cpmodeCtrl[3].zerop3uicp0 = 0x1,
        .cpmodeCtrl[3].zerop4uicp0 = 0x1,
        .cpmodeCtrl[3].zerop5uicp0 = 0x1,
        .cpmodeCtrl[3].zerop6uicp0 = 0x1,
        .cpmodeCtrl[3].detcntCp0 = 0xFF,
        .cpmodeCtrl[3].eqEnCp0 = 0x1,
        .cpmodeCtrl[3].eqSetCp0 = 0x7,
        .cpmodeCtrl[3].zerop3uicp1 = 0x1,
        .cpmodeCtrl[3].zerop4uicp1 = 0x1,
        .cpmodeCtrl[3].zerop5uicp1 = 0x1,
        .cpmodeCtrl[3].zerop6uicp1 = 0x1,
        .cpmodeCtrl[3].detcntCp1 = 0xFF,
        .cpmodeCtrl[3].eqEnCp1 = 0x1,
        .cpmodeCtrl[3].eqSetCp1 = 0x7,
        .cpmodeCtrl[3].zerop3uicp2 = 0x1,
        .cpmodeCtrl[3].zerop4uicp2 = 0x1,
        .cpmodeCtrl[3].zerop5uicp2 = 0x1,
        .cpmodeCtrl[3].zerop6uicp2 = 0x1,
        .cpmodeCtrl[3].detcntCp2 = 0xFF,
        .cpmodeCtrl[3].eqEnCp2 = 0x1,
        .cpmodeCtrl[3].eqSetCp2 = 0x7,
        .delayCtrl[0].d0rxspeed = 0x7,
        .delayCtrl[0].d1rxspeed = 0x7,
        .delayCtrl[0].d2rxspeed = 0x7,
        .delayCtrl[0].d3rxspeed = 0x7,
        .delayCtrl[0].skwselCp0 = 0x3,
        .delayCtrl[0].skwselCp1 = 0x3,
        .delayCtrl[0].skwselCp2 = 0x3,
        .delayCtrl[1].d0rxspeed = 0x7,
        .delayCtrl[1].d1rxspeed = 0x7,
        .delayCtrl[1].d2rxspeed = 0x7,
        .delayCtrl[1].d3rxspeed = 0x7,
        .delayCtrl[1].skwselCp0 = 0x3,
        .delayCtrl[1].skwselCp1 = 0x3,
        .delayCtrl[1].skwselCp2 = 0x3,
        .delayCtrl[2].d0rxspeed = 0x7,
        .delayCtrl[2].d1rxspeed = 0x7,
        .delayCtrl[2].d2rxspeed = 0x7,
        .delayCtrl[2].d3rxspeed = 0x7,
        .delayCtrl[2].skwselCp0 = 0x3,
        .delayCtrl[2].skwselCp1 = 0x3,
        .delayCtrl[2].skwselCp2 = 0x3,
        .delayCtrl[3].d0rxspeed = 0x7,
        .delayCtrl[3].d1rxspeed = 0x7,
        .delayCtrl[3].d2rxspeed = 0x7,
        .delayCtrl[3].d3rxspeed = 0x7,
        .delayCtrl[3].skwselCp0 = 0x3,
        .delayCtrl[3].skwselCp1 = 0x3,
        .delayCtrl[3].skwselCp2 = 0x3,
        .desknewCtrl[0].rxspden = 0x3,
        .desknewCtrl[0].dcntnum = 0x3,
        .desknewCtrl[0].grdwidth = 0x1,
        .desknewCtrl[0].rdwait = 0x3,
        .desknewCtrl[0].vldprd = 0x3,
        .desknewCtrl[1].rxspden = 0x3,
        .desknewCtrl[1].dcntnum = 0x3,
        .desknewCtrl[1].grdwidth = 0x1,
        .desknewCtrl[1].rdwait = 0x3,
        .desknewCtrl[1].vldprd = 0x3,
        .desknewCtrl[2].rxspden = 0x3,
        .desknewCtrl[2].dcntnum = 0x3,
        .desknewCtrl[2].grdwidth = 0x1,
        .desknewCtrl[2].rdwait = 0x3,
        .desknewCtrl[2].vldprd = 0x3,
        .desknewCtrl[3].rxspden = 0x3,
        .desknewCtrl[3].dcntnum = 0x3,
        .desknewCtrl[3].grdwidth = 0x1,
        .desknewCtrl[3].rdwait = 0x3,
        .desknewCtrl[3].vldprd = 0x3,
        .pll0Ctrl.ibcnt = 0x7,
        .pll0Ctrl.ilfsel = 0x1,
        .pll0Ctrl.ioclken = 0x1,
        .pll0Ctrl.itxpclk2aen = 0x1,
    };

    TimproSentopCphyCtrl cphyCtrlMin = {
        .commonIfCtrl.pregcnt = 0,
        .commonIfCtrl.freqcnt = 0,
        .commonIfCtrl.pdccnt = 0,
        .commonIfCtrl.setdf = 0,
        .commonIfCtrl.picodetst = 0,
        .commonIfCtrl.pmonsel = 0,
        .commonIfCtrl.dmonsel = 0,
        .commonIfCtrl.cntsel = 0,
        .commonIfCtrl.mulgainf = 0,
        .commonIfCtrl.mulgainp = 0,
        .commonIfCtrl.cdrfunc = 0,
        .cpmodeCtrl[0].zerop3uicp0 = 0,
        .cpmodeCtrl[0].zerop4uicp0 = 0,
        .cpmodeCtrl[0].zerop5uicp0 = 0,
        .cpmodeCtrl[0].zerop6uicp0 = 0,
        .cpmodeCtrl[0].detcntCp0 = 0,
        .cpmodeCtrl[0].eqEnCp0 = 0,
        .cpmodeCtrl[0].eqSetCp0 = 0,
        .cpmodeCtrl[0].zerop3uicp1 = 0,
        .cpmodeCtrl[0].zerop4uicp1 = 0,
        .cpmodeCtrl[0].zerop5uicp1 = 0,
        .cpmodeCtrl[0].zerop6uicp1 = 0,
        .cpmodeCtrl[0].detcntCp1 = 0,
        .cpmodeCtrl[0].eqEnCp1 = 0,
        .cpmodeCtrl[0].eqSetCp1 = 0,
        .cpmodeCtrl[0].zerop3uicp2 = 0,
        .cpmodeCtrl[0].zerop4uicp2 = 0,
        .cpmodeCtrl[0].zerop5uicp2 = 0,
        .cpmodeCtrl[0].zerop6uicp2 = 0,
        .cpmodeCtrl[0].detcntCp2 = 0,
        .cpmodeCtrl[0].eqEnCp2 = 0,
        .cpmodeCtrl[0].eqSetCp2 = 0,
        .cpmodeCtrl[1].zerop3uicp0 = 0,
        .cpmodeCtrl[1].zerop4uicp0 = 0,
        .cpmodeCtrl[1].zerop5uicp0 = 0,
        .cpmodeCtrl[1].zerop6uicp0 = 0,
        .cpmodeCtrl[1].detcntCp0 = 0,
        .cpmodeCtrl[1].eqEnCp0 = 0,
        .cpmodeCtrl[1].eqSetCp0 = 0,
        .cpmodeCtrl[1].zerop3uicp1 = 0,
        .cpmodeCtrl[1].zerop4uicp1 = 0,
        .cpmodeCtrl[1].zerop5uicp1 = 0,
        .cpmodeCtrl[1].zerop6uicp1 = 0,
        .cpmodeCtrl[1].detcntCp1 = 0,
        .cpmodeCtrl[1].eqEnCp1 = 0,
        .cpmodeCtrl[1].eqSetCp1 = 0,
        .cpmodeCtrl[1].zerop3uicp2 = 0,
        .cpmodeCtrl[1].zerop4uicp2 = 0,
        .cpmodeCtrl[1].zerop5uicp2 = 0,
        .cpmodeCtrl[1].zerop6uicp2 = 0,
        .cpmodeCtrl[1].detcntCp2 = 0,
        .cpmodeCtrl[1].eqEnCp2 = 0,
        .cpmodeCtrl[2].zerop3uicp0 = 0,
        .cpmodeCtrl[2].zerop4uicp0 = 0,
        .cpmodeCtrl[2].zerop5uicp0 = 0,
        .cpmodeCtrl[2].zerop6uicp0 = 0,
        .cpmodeCtrl[2].detcntCp0 = 0,
        .cpmodeCtrl[2].eqEnCp0 = 0,
        .cpmodeCtrl[2].eqSetCp0 = 0,
        .cpmodeCtrl[2].zerop3uicp1 = 0,
        .cpmodeCtrl[2].zerop4uicp1 = 0,
        .cpmodeCtrl[2].zerop5uicp1 = 0,
        .cpmodeCtrl[2].zerop6uicp1 = 0,
        .cpmodeCtrl[2].detcntCp1 = 0,
        .cpmodeCtrl[2].eqEnCp1 = 0,
        .cpmodeCtrl[2].eqSetCp1 = 0,
        .cpmodeCtrl[2].zerop3uicp2 = 0,
        .cpmodeCtrl[2].zerop4uicp2 = 0,
        .cpmodeCtrl[2].zerop5uicp2 = 0,
        .cpmodeCtrl[2].zerop6uicp2 = 0,
        .cpmodeCtrl[2].detcntCp2 = 0,
        .cpmodeCtrl[2].eqEnCp2 = 0,
        .cpmodeCtrl[2].eqSetCp2 = 0,
        .cpmodeCtrl[3].zerop3uicp0 = 0,
        .cpmodeCtrl[3].zerop4uicp0 = 0,
        .cpmodeCtrl[3].zerop5uicp0 = 0,
        .cpmodeCtrl[3].zerop6uicp0 = 0,
        .cpmodeCtrl[3].detcntCp0 = 0,
        .cpmodeCtrl[3].eqEnCp0 = 0,
        .cpmodeCtrl[3].eqSetCp0 = 0,
        .cpmodeCtrl[3].zerop3uicp1 = 0,
        .cpmodeCtrl[3].zerop4uicp1 = 0,
        .cpmodeCtrl[3].zerop5uicp1 = 0,
        .cpmodeCtrl[3].zerop6uicp1 = 0,
        .cpmodeCtrl[3].detcntCp1 = 0,
        .cpmodeCtrl[3].eqEnCp1 = 0,
        .cpmodeCtrl[3].eqSetCp1 = 0,
        .cpmodeCtrl[3].zerop3uicp2 = 0,
        .cpmodeCtrl[3].zerop4uicp2 = 0,
        .cpmodeCtrl[3].zerop5uicp2 = 0,
        .cpmodeCtrl[3].zerop6uicp2 = 0,
        .cpmodeCtrl[3].detcntCp2 = 0,
        .cpmodeCtrl[3].eqEnCp2 = 0,
        .cpmodeCtrl[3].eqSetCp2 = 0,
        .delayCtrl[0].d0rxspeed = 0,
        .delayCtrl[0].d1rxspeed = 0,
        .delayCtrl[0].d2rxspeed = 0,
        .delayCtrl[0].d3rxspeed = 0,
        .delayCtrl[0].skwselCp0 = 0,
        .delayCtrl[0].skwselCp1 = 0,
        .delayCtrl[0].skwselCp2 = 0,
        .delayCtrl[1].d0rxspeed = 0,
        .delayCtrl[1].d1rxspeed = 0,
        .delayCtrl[1].d2rxspeed = 0,
        .delayCtrl[1].d3rxspeed = 0,
        .delayCtrl[1].skwselCp0 = 0,
        .delayCtrl[1].skwselCp1 = 0,
        .delayCtrl[1].skwselCp2 = 0,
        .delayCtrl[2].d0rxspeed = 0,
        .delayCtrl[2].d1rxspeed = 0,
        .delayCtrl[2].d2rxspeed = 0,
        .delayCtrl[2].d3rxspeed = 0,
        .delayCtrl[2].skwselCp0 = 0,
        .delayCtrl[2].skwselCp1 = 0,
        .delayCtrl[2].skwselCp2 = 0,
        .delayCtrl[3].d0rxspeed = 0,
        .delayCtrl[3].d1rxspeed = 0,
        .delayCtrl[3].d2rxspeed = 0,
        .delayCtrl[3].d3rxspeed = 0,
        .delayCtrl[3].skwselCp0 = 0,
        .delayCtrl[3].skwselCp1 = 0,
        .delayCtrl[3].skwselCp2 = 0,
        .desknewCtrl[0].rxspden = 0,
        .desknewCtrl[0].dcntnum = 0,
        .desknewCtrl[0].grdwidth = 0,
        .desknewCtrl[0].rdwait = 0,
        .desknewCtrl[0].vldprd = 0,
        .desknewCtrl[1].rxspden = 0,
        .desknewCtrl[1].dcntnum = 0,
        .desknewCtrl[1].grdwidth = 0,
        .desknewCtrl[1].rdwait = 0,
        .desknewCtrl[1].vldprd = 0,
        .desknewCtrl[2].rxspden = 0,
        .desknewCtrl[2].dcntnum = 0,
        .desknewCtrl[2].grdwidth = 0,
        .desknewCtrl[2].rdwait = 0,
        .desknewCtrl[2].vldprd = 0,
        .desknewCtrl[3].rxspden = 0,
        .desknewCtrl[3].dcntnum = 0,
        .desknewCtrl[3].grdwidth = 0,
        .desknewCtrl[3].rdwait = 0,
        .desknewCtrl[3].vldprd = 0,
        .pll0Ctrl.ibcnt = 0,
        .pll0Ctrl.ilfsel = 0,
        .pll0Ctrl.ioclken = 0,
        .pll0Ctrl.itxpclk2aen = 0,
    };

	if (idx == 1) {
#if 0
		Ddim_Print(("Target register address\n"));
		Ddim_Print(("impro_sentop_cphy_ctrl() phycifctl.phycifctl1 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phycifctl.phycifctl1.word, ioPro.sen.sentop.phycifctl.phycifctl1.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phycifctl.phycifctl2 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phycifctl.phycifctl2.word, ioPro.sen.sentop.phycifctl.phycifctl2.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phycifctl.phycifctl3 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phycifctl.phycifctl3.word, ioPro.sen.sentop.phycifctl.phycifctl3.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0clkctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0clkctl.word, ioPro.sen.sentop.phy0clkctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1clkctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1clkctl.word, ioPro.sen.sentop.phy1clkctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2clkctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2clkctl.word, ioPro.sen.sentop.phy2clkctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3clkctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3clkctl.word, ioPro.sen.sentop.phy3clkctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0mdctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0mdctl.word, ioPro.sen.sentop.phy0mdctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1mdctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1mdctl.word, ioPro.sen.sentop.phy1mdctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2mdctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2mdctl.word, ioPro.sen.sentop.phy2mdctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3mdctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3mdctl.word, ioPro.sen.sentop.phy3mdctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0mdcpctl.phy0mdcpctl1 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.word,
				ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.word));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0mdcpctl.phy0mdcpctl2 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.word,
				ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.word));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0mdcpctl.phy0mdcpctl3 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.word,
				ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.word));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1mdcpctl.phy1mdcpctl1 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.word,
				ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.word));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1mdcpctl.phy1mdcpctl2 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.word,
				ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.word));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1mdcpctl.phy1mdcpctl3 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.word,
				ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.word));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2mdcpctl.phy2mdcpctl1 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.word,
				ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.word));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2mdcpctl.phy2mdcpctl2 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.word,
				ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.word));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2mdcpctl.phy2mdcpctl3 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.word,
				ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.word));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3mdcpctl.phy3mdcpctl1 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.word,
				ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.word));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3mdcpctl.phy3mdcpctl2 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.word,
				ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.word));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3mdcpctl.phy3mdcpctl3 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.word,
				ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.word));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0dlctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0dlctl.word, ioPro.sen.sentop.phy0dlctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1dlctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1dlctl.word, ioPro.sen.sentop.phy1dlctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2dlctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2dlctl.word, ioPro.sen.sentop.phy2dlctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3dlctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3dlctl.word, ioPro.sen.sentop.phy3dlctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0ifctl.phy0ifctl1 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0ifctl.phy0ifctl1.word, ioPro.sen.sentop.phy0ifctl.phy0ifctl1.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0ifctl.phy0ifctl2 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0ifctl.phy0ifctl2.word, ioPro.sen.sentop.phy0ifctl.phy0ifctl2.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0ifctl.phy0ifctl3 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0ifctl.phy0ifctl3.word, ioPro.sen.sentop.phy0ifctl.phy0ifctl3.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0ifctl.phy0ifctl4 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0ifctl.phy0ifctl4.word, ioPro.sen.sentop.phy0ifctl.phy0ifctl4.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0ifctl.phy0ifctl5 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0ifctl.phy0ifctl5.word, ioPro.sen.sentop.phy0ifctl.phy0ifctl5.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0ifctl.phy0ifctl6 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0ifctl.phy0ifctl6.word, ioPro.sen.sentop.phy0ifctl.phy0ifctl6.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0ifctl.phy0ifctl7 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0ifctl.phy0ifctl7.word, ioPro.sen.sentop.phy0ifctl.phy0ifctl7.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1ifctl.phy1ifctl1 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1ifctl.phy1ifctl1.word, ioPro.sen.sentop.phy1ifctl.phy1ifctl1.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1ifctl.phy1ifctl2 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1ifctl.phy1ifctl2.word, ioPro.sen.sentop.phy1ifctl.phy1ifctl2.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1ifctl.phy1ifctl3 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1ifctl.phy1ifctl3.word, ioPro.sen.sentop.phy1ifctl.phy1ifctl3.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1ifctl.phy1ifctl4 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1ifctl.phy1ifctl4.word, ioPro.sen.sentop.phy1ifctl.phy1ifctl4.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1ifctl.phy1ifctl5 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1ifctl.phy1ifctl5.word, ioPro.sen.sentop.phy1ifctl.phy1ifctl5.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1ifctl.phy1ifctl6 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1ifctl.phy1ifctl6.word, ioPro.sen.sentop.phy1ifctl.phy1ifctl6.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1ifctl.phy1ifctl7 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1ifctl.phy1ifctl7.word, ioPro.sen.sentop.phy1ifctl.phy1ifctl7.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2ifctl.phy2ifctl1 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2ifctl.phy2ifctl1.word, ioPro.sen.sentop.phy2ifctl.phy2ifctl1.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2ifctl.phy2ifctl2 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2ifctl.phy2ifctl2.word, ioPro.sen.sentop.phy2ifctl.phy2ifctl2.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2ifctl.phy2ifctl3 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2ifctl.phy2ifctl3.word, ioPro.sen.sentop.phy2ifctl.phy2ifctl3.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2ifctl.phy2ifctl4 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2ifctl.phy2ifctl4.word, ioPro.sen.sentop.phy2ifctl.phy2ifctl4.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2ifctl.phy2ifctl5 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2ifctl.phy2ifctl5.word, ioPro.sen.sentop.phy2ifctl.phy2ifctl5.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2ifctl.phy2ifctl6 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2ifctl.phy2ifctl6.word, ioPro.sen.sentop.phy2ifctl.phy2ifctl6.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2ifctl.phy2ifctl7 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2ifctl.phy2ifctl7.word, ioPro.sen.sentop.phy2ifctl.phy2ifctl7.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3ifctl.phy3ifctl1 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3ifctl.phy3ifctl1.word, ioPro.sen.sentop.phy3ifctl.phy3ifctl1.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3ifctl.phy3ifctl2 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3ifctl.phy3ifctl2.word, ioPro.sen.sentop.phy3ifctl.phy3ifctl2.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3ifctl.phy3ifctl3 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3ifctl.phy3ifctl3.word, ioPro.sen.sentop.phy3ifctl.phy3ifctl3.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3ifctl.phy3ifctl4 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3ifctl.phy3ifctl4.word, ioPro.sen.sentop.phy3ifctl.phy3ifctl4.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3ifctl.phy3ifctl5 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3ifctl.phy3ifctl5.word, ioPro.sen.sentop.phy3ifctl.phy3ifctl5.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3ifctl.phy3ifctl6 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3ifctl.phy3ifctl6.word, ioPro.sen.sentop.phy3ifctl.phy3ifctl6.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3ifctl.phy3ifctl7 (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3ifctl.phy3ifctl7.word, ioPro.sen.sentop.phy3ifctl.phy3ifctl7.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy0dskctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy0dskctl.word, ioPro.sen.sentop.phy0dskctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy1dskctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy1dskctl.word, ioPro.sen.sentop.phy1dskctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy2dskctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy2dskctl.word, ioPro.sen.sentop.phy2dskctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() phy3dskctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.phy3dskctl.word, ioPro.sen.sentop.phy3dskctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() pll0ctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.pll0ctl.word, ioPro.sen.sentop.pll0ctl.word ));
		Ddim_Print(("impro_sentop_cphy_ctrl() biasctl (0x%08lx, %lx)\n",
				(kulong)&ioPro.sen.sentop.biasctl.word, ioPro.sen.sentop.biasctl.word ));
#endif
		// Maximum value parameter
		self->priv->ercd = impro_sentop_cphy_ctrl(self->priv->improSentop, &cphyCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_cphy_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_1_print_1(self->priv->imPro11Print, "max_para", &cphyCtrlMax);
		}

		// Minimum value parameter
		self->priv->ercd = impro_sentop_cphy_ctrl(self->priv->improSentop, &cphyCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_cphy_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_1_print_1(self->priv->imPro11Print, "min_para", &cphyCtrlMin);
		}
    }
}

void ct_im_pro1_1_2(CtImPro11* self, const kuint32 idx)
{
    TimproSentopCphyDesknewMonitor cphyMon;

    if (idx == 1) {
#if 0
        Ddim_Print(("Target register address\n"));
        Ddim_Print(("impro_sentop_cphy_get_des_knew_ctrl() phy0dskmoni1 (0x%08lx, %lx)\n",
        		(kulong)&ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.word,
        		ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.word));
        Ddim_Print(("impro_sentop_cphy_get_des_knew_ctrl() phy0dskmoni2 (0x%08lx, %lx)\n",
        		(kulong)&ioPro.sen.sentop.phy0dskmoni.phy0dskmoni2.word,
        		ioPro.sen.sentop.phy0dskmoni.phy0dskmoni2.word));
        Ddim_Print(("impro_sentop_cphy_get_des_knew_ctrl() phy1dskmoni1 (0x%08lx, %lx)\n",
        		(kulong)&ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.word,
        		ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.word));
        Ddim_Print(("impro_sentop_cphy_get_des_knew_ctrl() phy1dskmoni2 (0x%08lx, %lx)\n",
        		(kulong)&ioPro.sen.sentop.phy1dskmoni.phy1dskmoni2.word,
        		ioPro.sen.sentop.phy1dskmoni.phy1dskmoni2.word));
        Ddim_Print(("impro_sentop_cphy_get_des_knew_ctrl() phy2dskmoni1 (0x%08lx, %lx)\n",
        		(kulong)&ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.word,
        		ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.word));
        Ddim_Print(("impro_sentop_cphy_get_des_knew_ctrl() phy2dskmoni2 (0x%08lx, %lx)\n",
        		(kulong)&ioPro.sen.sentop.phy2dskmoni.phy2dskmoni2.word,
        		ioPro.sen.sentop.phy2dskmoni.phy2dskmoni2.word));
#endif
        // Maximum value parameter
#ifdef CO_DEBUG_ON_PC
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon0 = 3;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon1 = 3;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon2 = 3;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon3 = 3;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Vldwindow0 = 127;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Vldwindow1 = 127;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni2.bit.phy0Vldwindow2 = 127;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni2.bit.phy0Vldwindow3 = 127;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon0 = 3;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon1 = 3;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon2 = 3;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon3 = 3;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Vldwindow0 = 127;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Vldwindow1 = 127;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni2.bit.phy1Vldwindow2 = 127;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni2.bit.phy1Vldwindow3 = 127;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon0 = 3;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon1 = 3;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon2 = 3;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon3 = 3;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Vldwindow0 = 127;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Vldwindow1 = 127;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni2.bit.phy2Vldwindow2 = 127;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni2.bit.phy2Vldwindow3 = 127;
#endif  // CO_DEBUG_ON_PC
		self->priv->ercd = impro_sentop_cphy_get_des_knew_ctrl(self->priv->improSentop, &cphyMon);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_cphy_get_des_knew_ctrl() max_para Error self->priv->ercd=0x%x\n",
							self->priv->ercd));
		} else {
			im_pro_1_1_print_2(self->priv->imPro11Print, "max_para", &cphyMon);
		}

#ifdef CO_DEBUG_ON_PC
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon0 = 0;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon1 = 0;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon2 = 0;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon3 = 0;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Vldwindow0 = 0;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Vldwindow1 = 0;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni2.bit.phy0Vldwindow2 = 0;
        ioPro.sen.sentop.phy0dskmoni.phy0dskmoni2.bit.phy0Vldwindow3 = 0;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon0 = 0;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon1 = 0;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon2 = 0;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon3 = 0;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Vldwindow0 = 0;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Vldwindow1 = 0;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni2.bit.phy1Vldwindow2 = 0;
        ioPro.sen.sentop.phy1dskmoni.phy1dskmoni2.bit.phy1Vldwindow3 = 0;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon0 = 0;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon1 = 0;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon2 = 0;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon3 = 0;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Vldwindow0 = 0;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Vldwindow1 = 0;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni2.bit.phy2Vldwindow2 = 0;
        ioPro.sen.sentop.phy2dskmoni.phy2dskmoni2.bit.phy2Vldwindow3 = 0;
        // Minimum value parameter
        self->priv->ercd = impro_sentop_cphy_get_des_knew_ctrl(self->priv->improSentop, &cphyMon);
        if (self->priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("impro_sentop_cphy_get_des_knew_ctrl() min_para Error self->priv->ercd=0x%x\n",
            		self->priv->ercd));
        } else {
            im_pro_1_1_print_2(self->priv->imPro11Print, "min_para", &cphyMon);
        }
#endif  // CO_DEBUG_ON_PC

        // invalid value parameter
		self->priv->ercd = impro_sentop_cphy_get_des_knew_ctrl(self->priv->improSentop, NULL);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_cphy_get_des_knew_ctrl() invalid Error self->priv->ercd=0x%x\n",
							self->priv->ercd));
		} else {
			im_pro_1_1_print_2(self->priv->imPro11Print, "invalid", &cphyMon);
		}
    }
}

void ct_im_pro1_1_3(CtImPro11* self, const kuint32 idx)
{
    EimproSgCh ch = ImproSensg_E_IM_PRO_SG_CH_0;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sensg_start(0) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].sgtrg.word, ioPro.sen.sg[0].sgtrg.word));
//        Ddim_Print(("impro_sensg_start(1) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].sgtrg.word, ioPro.sen.sg[1].sgtrg.word));
//        Ddim_Print(("impro_sensg_start(2) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].sgtrg.word, ioPro.sen.sg[2].sgtrg.word));
//        Ddim_Print(("impro_sensg_start(3) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].sgtrg.word, ioPro.sen.sg[3].sgtrg.word));
		// Maximum value parameter
		ch = ImproSensg_E_IM_PRO_SG_CH_3;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sg[ch].sgtrg.bit.sgtrg = 0;
#endif
		self->priv->ercd = impro_sensg_start(self->priv->improSensg, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensg_start(%u) max_para Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_1_print_3(self->priv->imPro11Print, "max_para");
		}

		// Minimum value parameter
		ch = ImproSensg_E_IM_PRO_SG_CH_0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sg[ch].sgtrg.bit.sgtrg = 0;
#endif
		self->priv->ercd = impro_sensg_start(self->priv->improSensg, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensg_start(%u) min_para Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_1_print_3(self->priv->imPro11Print, "min_para");
		}
    }
}

void ct_im_pro1_1_4(CtImPro11* self, const kuint32 idx)
{
	EimproSgCh ch = ImproSensg_E_IM_PRO_SG_CH_0;
	kuchar force = 0;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sensg_stop(0) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].sgtrg.word,  ioPro.sen.sg[0].sgtrg.word));
//        Ddim_Print(("impro_sensg_stop(1) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].sgtrg.word,  ioPro.sen.sg[1].sgtrg.word));
//        Ddim_Print(("impro_sensg_stop(2) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].sgtrg.word,  ioPro.sen.sg[2].sgtrg.word));
//        Ddim_Print(("impro_sensg_stop(3) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].sgtrg.word,  ioPro.sen.sg[3].sgtrg.word));
		// Maximum value parameter
		ch = ImproSensg_E_IM_PRO_SG_CH_3;
		force = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sg[ch].sgtrg.bit.sgtrg = 3;
#endif
		self->priv->ercd = impro_sensg_stop(self->priv->improSensg, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sensg_stop(%u, %u) max_para Error self->priv->ercd=0x%x\n", ch, force, self->priv->ercd));
		} else {
			im_pro_1_1_print_4(self->priv->imPro11Print, "max_para", force);
		}

        // Minimum value parameter
		ch = ImproSensg_E_IM_PRO_SG_CH_0;
		force = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sg[ch].sgtrg.bit.sgtrg = 3;
#endif
		self->priv->ercd = impro_sensg_stop(self->priv->improSensg, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sensg_stop(%u, %u) min_para Error self->priv->ercd=0x%x\n", ch, force, self->priv->ercd));
		} else {
			im_pro_1_1_print_4(self->priv->imPro11Print, "min_para", force);
		}

        // Maximum value parameter
		ch = ImproSensg_E_IM_PRO_SG_CH_3;
		force = 1;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sg[ch].sgtrg.bit.sgtrg = 3;
#endif
		self->priv->ercd = impro_sensg_stop(self->priv->improSensg, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sensg_stop(%u, %u) max_para Error self->priv->ercd=0x%x\n", ch, force, self->priv->ercd));
		} else {
			im_pro_1_1_print_4(self->priv->imPro11Print, "max_para", force);
		}

		// Minimum value parameter
		ch = ImproSensg_E_IM_PRO_SG_CH_0;
		force = 1;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sg[ch].sgtrg.bit.sgtrg = 3;
#endif
		self->priv->ercd = impro_sensg_stop(self->priv->improSensg, ch, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sensg_stop(%u, %u) min_para Error self->priv->ercd=0x%x\n", ch, force, self->priv->ercd));
		} else {
			im_pro_1_1_print_4(self->priv->imPro11Print, "min_para", force);
		}
    }
}

void ct_im_pro1_1_5(CtImPro11* self, const kuint32 idx)
{
    EimproSgCh ch = ImproSensg_E_IM_PRO_SG_CH_0;
    TimproSgCtrl sgCtrlMax = {
        .vhdo = 0xFF,
        .vdot = 0xFF,
        .vdinv = 0xFFFF,
        .hdinv = 0xFF,
        .hdchg = 0xFF,
        .vddly = 0xFF,
        .vdocyc = 0xFFFFFFFF,
        .vdow = 0xFFFF,
        .hdocyc = 0xFFFF,
        .hdow = 0xFFFF,
        .hdocyc2 = 0xFFFF,
        .hdow2 = 0xFFFF,
    };

    TimproSgCtrl sgCtrlMin = {
        .vhdo = 0,
        .vdot = 0,
        .vdinv = 0,
        .hdinv = 0,
        .hdchg = 0,
        .vddly = 0,
        .vdocyc = 0,
        .vdow = 0,
        .hdocyc = 0,
        .hdow = 0,
        .hdocyc2 = 0,
        .hdow2 = 0,
    };

    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sensg_ctrl(0) sgctl1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].sgctl1.word,   ioPro.sen.sg[0].sgctl1.word   ));
//        Ddim_Print(("impro_sensg_ctrl(0) sgctl2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].sgctl2.word,   ioPro.sen.sg[0].sgctl2.word   ));
//        Ddim_Print(("impro_sensg_ctrl(0) vdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].vdocyc.word,   ioPro.sen.sg[0].vdocyc.word   ));
//        Ddim_Print(("impro_sensg_ctrl(0) vdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].vdow.word,     ioPro.sen.sg[0].vdow.word     ));
//        Ddim_Print(("impro_sensg_ctrl(0) hdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].hdocyc.word,   ioPro.sen.sg[0].hdocyc.word   ));
//        Ddim_Print(("impro_sensg_ctrl(0) hdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].hdow.word,     ioPro.sen.sg[0].hdow.word     ));
//        Ddim_Print(("impro_sensg_ctrl(0) hdocyc2 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].hdocyc2.word,  ioPro.sen.sg[0].hdocyc2.word  ));
//        Ddim_Print(("impro_sensg_ctrl(0) hdow2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].hdow2.word,    ioPro.sen.sg[0].hdow2.word    ));
//        Ddim_Print(("impro_sensg_ctrl(1) sgctl1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].sgctl1.word,   ioPro.sen.sg[1].sgctl1.word   ));
//        Ddim_Print(("impro_sensg_ctrl(1) sgctl2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].sgctl2.word,   ioPro.sen.sg[1].sgctl2.word   ));
//        Ddim_Print(("impro_sensg_ctrl(1) vdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].vdocyc.word,   ioPro.sen.sg[1].vdocyc.word   ));
//        Ddim_Print(("impro_sensg_ctrl(1) vdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].vdow.word,     ioPro.sen.sg[1].vdow.word     ));
//        Ddim_Print(("impro_sensg_ctrl(1) hdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].hdocyc.word,   ioPro.sen.sg[1].hdocyc.word   ));
//        Ddim_Print(("impro_sensg_ctrl(1) hdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].hdow.word,     ioPro.sen.sg[1].hdow.word     ));
//        Ddim_Print(("impro_sensg_ctrl(1) hdocyc2 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].hdocyc2.word,  ioPro.sen.sg[1].hdocyc2.word  ));
//        Ddim_Print(("impro_sensg_ctrl(1) hdow2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].hdow2.word,    ioPro.sen.sg[1].hdow2.word    ));
//        Ddim_Print(("impro_sensg_ctrl(2) sgctl1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].sgctl1.word,   ioPro.sen.sg[2].sgctl1.word   ));
//        Ddim_Print(("impro_sensg_ctrl(2) sgctl2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].sgctl2.word,   ioPro.sen.sg[2].sgctl2.word   ));
//        Ddim_Print(("impro_sensg_ctrl(2) vdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].vdocyc.word,   ioPro.sen.sg[2].vdocyc.word   ));
//        Ddim_Print(("impro_sensg_ctrl(2) vdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].vdow.word,     ioPro.sen.sg[2].vdow.word     ));
//        Ddim_Print(("impro_sensg_ctrl(2) hdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].hdocyc.word,   ioPro.sen.sg[2].hdocyc.word   ));
//        Ddim_Print(("impro_sensg_ctrl(2) hdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].hdow.word,     ioPro.sen.sg[2].hdow.word     ));
//        Ddim_Print(("impro_sensg_ctrl(2) hdocyc2 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].hdocyc2.word,  ioPro.sen.sg[2].hdocyc2.word  ));
//        Ddim_Print(("impro_sensg_ctrl(2) hdow2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].hdow2.word,    ioPro.sen.sg[2].hdow2.word    ));
//        Ddim_Print(("impro_sensg_ctrl(3) sgctl1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].sgctl1.word,   ioPro.sen.sg[3].sgctl1.word   ));
//        Ddim_Print(("impro_sensg_ctrl(3) sgctl2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].sgctl2.word,   ioPro.sen.sg[3].sgctl2.word   ));
//        Ddim_Print(("impro_sensg_ctrl(3) vdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].vdocyc.word,   ioPro.sen.sg[3].vdocyc.word   ));
//        Ddim_Print(("impro_sensg_ctrl(3) vdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].vdow.word,     ioPro.sen.sg[3].vdow.word     ));
//        Ddim_Print(("impro_sensg_ctrl(3) hdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].hdocyc.word,   ioPro.sen.sg[3].hdocyc.word   ));
//        Ddim_Print(("impro_sensg_ctrl(3) hdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].hdow.word,     ioPro.sen.sg[3].hdow.word     ));
//        Ddim_Print(("impro_sensg_ctrl(3) hdocyc2 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].hdocyc2.word,  ioPro.sen.sg[3].hdocyc2.word  ));
//        Ddim_Print(("impro_sensg_ctrl(3) hdow2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].hdow2.word,    ioPro.sen.sg[3].hdow2.word    ));
        // Maximum value parameter
		ch = ImproSensg_E_IM_PRO_SG_CH_3;
		self->priv->ercd = impro_sensg_ctrl(self->priv->improSensg, ch, &sgCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensg_ctrl(%u) max_para Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_1_print_5(self->priv->imPro11Print, "max_para", ch, &sgCtrlMax);
		}

		// Minimum value parameter
		ch = ImproSensg_E_IM_PRO_SG_CH_0;
		self->priv->ercd = impro_sensg_ctrl(self->priv->improSensg, ch, &sgCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sensg_ctrl(%u) min_para Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_1_print_5(self->priv->imPro11Print, "min_para", ch, &sgCtrlMin);
		}
    }
}

void ct_im_pro1_1_6(CtImPro11* self, const kuint32 idx)
{
	EimproSgCh ch = ImproSensg_E_IM_PRO_SG_CH_0;
	TimproSgCtrl sgCtrl;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sensg_get_cycle(0) sgctl1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].sgctl1.word,   ioPro.sen.sg[0].sgctl1.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(0) sgctl2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].sgctl2.word,   ioPro.sen.sg[0].sgctl2.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(0) vdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].vdocyc.word,   ioPro.sen.sg[0].vdocyc.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(0) vdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].vdow.word,     ioPro.sen.sg[0].vdow.word     ));
//        Ddim_Print(("impro_sensg_get_cycle(0) hdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].hdocyc.word,   ioPro.sen.sg[0].hdocyc.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(0) hdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].hdow.word,     ioPro.sen.sg[0].hdow.word     ));
//        Ddim_Print(("impro_sensg_get_cycle(0) hdocyc2 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].hdocyc2.word,  ioPro.sen.sg[0].hdocyc2.word  ));
//        Ddim_Print(("impro_sensg_get_cycle(0) hdow2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].hdow2.word,    ioPro.sen.sg[0].hdow2.word    ));
//        Ddim_Print(("impro_sensg_get_cycle(1) sgctl1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].sgctl1.word,   ioPro.sen.sg[1].sgctl1.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(1) sgctl2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].sgctl2.word,   ioPro.sen.sg[1].sgctl2.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(1) vdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].vdocyc.word,   ioPro.sen.sg[1].vdocyc.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(1) vdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].vdow.word,     ioPro.sen.sg[1].vdow.word     ));
//        Ddim_Print(("impro_sensg_get_cycle(1) hdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].hdocyc.word,   ioPro.sen.sg[1].hdocyc.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(1) hdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].hdow.word,     ioPro.sen.sg[1].hdow.word     ));
//        Ddim_Print(("impro_sensg_get_cycle(1) hdocyc2 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].hdocyc2.word,  ioPro.sen.sg[1].hdocyc2.word  ));
//        Ddim_Print(("impro_sensg_get_cycle(1) hdow2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].hdow2.word,    ioPro.sen.sg[1].hdow2.word    ));
//        Ddim_Print(("impro_sensg_get_cycle(2) sgctl1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].sgctl1.word,   ioPro.sen.sg[2].sgctl1.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(2) sgctl2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].sgctl2.word,   ioPro.sen.sg[2].sgctl2.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(2) vdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].vdocyc.word,   ioPro.sen.sg[2].vdocyc.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(2) vdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].vdow.word,     ioPro.sen.sg[2].vdow.word     ));
//        Ddim_Print(("impro_sensg_get_cycle(2) hdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].hdocyc.word,   ioPro.sen.sg[2].hdocyc.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(2) hdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].hdow.word,     ioPro.sen.sg[2].hdow.word     ));
//        Ddim_Print(("impro_sensg_get_cycle(2) hdocyc2 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].hdocyc2.word,  ioPro.sen.sg[2].hdocyc2.word  ));
//        Ddim_Print(("impro_sensg_get_cycle(2) hdow2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].hdow2.word,    ioPro.sen.sg[2].hdow2.word    ));
//        Ddim_Print(("impro_sensg_get_cycle(3) sgctl1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].sgctl1.word,   ioPro.sen.sg[3].sgctl1.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(3) sgctl2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].sgctl2.word,   ioPro.sen.sg[3].sgctl2.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(3) vdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].vdocyc.word,   ioPro.sen.sg[3].vdocyc.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(3) vdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].vdow.word,     ioPro.sen.sg[3].vdow.word     ));
//        Ddim_Print(("impro_sensg_get_cycle(3) hdocyc  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].hdocyc.word,   ioPro.sen.sg[3].hdocyc.word   ));
//        Ddim_Print(("impro_sensg_get_cycle(3) hdow    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].hdow.word,     ioPro.sen.sg[3].hdow.word     ));
//        Ddim_Print(("impro_sensg_get_cycle(3) hdocyc2 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].hdocyc2.word,  ioPro.sen.sg[3].hdocyc2.word  ));
//        Ddim_Print(("impro_sensg_get_cycle(3) hdow2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].hdow2.word,    ioPro.sen.sg[3].hdow2.word    ));
        // Maximum value parameter
        ch = ImproSensg_E_IM_PRO_SG_CH_3;
#ifdef CO_DEBUG_ON_PC
        ioPro.sen.sg[ch].sgctl1.bit.vhdo = 1;
        ioPro.sen.sg[ch].sgctl1.bit.vdot = 1;
        ioPro.sen.sg[ch].sgctl1.bit.vdinv = 1;
        ioPro.sen.sg[ch].sgctl1.bit.hdinv = 1;
        ioPro.sen.sg[ch].sgctl2.bit.hdchg = 1;
        ioPro.sen.sg[ch].sgctl2.bit.vddly = 0xFF;
        ioPro.sen.sg[ch].vdocyc.bit.vdocyc = 0xFFFFFF;
        ioPro.sen.sg[ch].vdow.bit.vdow = 0x1FF;
        ioPro.sen.sg[ch].hdocyc.bit.hdocyc = 0x3FFF;
        ioPro.sen.sg[ch].hdow.bit.hdow = 0x1FF;
        ioPro.sen.sg[ch].hdocyc2.bit.hdocyc2 = 0x3FFF;
        ioPro.sen.sg[ch].hdow2.bit.hdow2 = 0x1FF;
#endif  // CO_DEBUG_ON_PC
		self->priv->ercd = impro_sensg_get_cycle(self->priv->improSensg, ch, &sgCtrl);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sensg_get_cycle(%d) max_para Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_1_print_6(self->priv->imPro11Print, "max_para", ch, &sgCtrl);
		}

		ch = ImproSensg_E_IM_PRO_SG_CH_0;
#ifdef CO_DEBUG_ON_PC
        ioPro.sen.sg[ch].sgctl1.bit.vhdo = 0;
        ioPro.sen.sg[ch].sgctl1.bit.vdot = 0;
        ioPro.sen.sg[ch].sgctl1.bit.vdinv = 0;
        ioPro.sen.sg[ch].sgctl1.bit.hdinv = 0;
        ioPro.sen.sg[ch].sgctl2.bit.hdchg = 0;
        ioPro.sen.sg[ch].sgctl2.bit.vddly = 0;
        ioPro.sen.sg[ch].vdocyc.bit.vdocyc = 0;
        ioPro.sen.sg[ch].vdow.bit.vdow = 0;
        ioPro.sen.sg[ch].hdocyc.bit.hdocyc = 0;
        ioPro.sen.sg[ch].hdow.bit.hdow = 0;
        ioPro.sen.sg[ch].hdocyc2.bit.hdocyc2 = 0;
        ioPro.sen.sg[ch].hdow2.bit.hdow2 = 0;
#endif  // CO_DEBUG_ON_PC
        // Minimum value parameter
		self->priv->ercd = impro_sensg_get_cycle(self->priv->improSensg, ch, &sgCtrl);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sensg_get_cycle(%d) min_para Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_1_print_6(self->priv->imPro11Print, "min_para", ch, &sgCtrl);
		}

		// invalid value parameter
		self->priv->ercd = impro_sensg_get_cycle(self->priv->improSensg, ch, NULL);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sensg_get_cycle(%d) invalid Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_1_print_6(self->priv->imPro11Print, "invalid", ch, &sgCtrl);
		}
    }
}

void ct_im_pro1_1_7(CtImPro11* self, const kuint32 idx)
{
	EimproSgCh ch = ImproSensg_E_IM_PRO_SG_CH_0;
	TimproSgMoniInfo sgMoniInfo;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sensg_get_monitor_info(0) vdhdmon  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[0].vdhdmon.word,   ioPro.sen.sg[0].vdhdmon.word   ));
//        Ddim_Print(("impro_sensg_get_monitor_info(1) vdhdmon  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[1].vdhdmon.word,   ioPro.sen.sg[1].vdhdmon.word   ));
//        Ddim_Print(("impro_sensg_get_monitor_info(2) vdhdmon  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[2].vdhdmon.word,   ioPro.sen.sg[2].vdhdmon.word   ));
//        Ddim_Print(("impro_sensg_get_monitor_info(3) vdhdmon  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sg[3].vdhdmon.word,   ioPro.sen.sg[3].vdhdmon.word   ));
		// Maximum value parameter
		ch = ImproSensg_E_IM_PRO_SG_CH_3;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sg[ch].vdhdmon.bit.vdin = 1;
		ioPro.sen.sg[ch].vdhdmon.bit.hdin = 1;
#endif  // CO_DEBUG_ON_PC
		self->priv->ercd = impro_sensg_get_monitor_info(self->priv->improSensg, ch, &sgMoniInfo);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sensg_get_monitor_info(%d) max_para Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_1_print_7(self->priv->imPro11Print, "max_para", ch, &sgMoniInfo);
		}

        ch = ImproSensg_E_IM_PRO_SG_CH_0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.sg[ch].vdhdmon.bit.vdin = 0;
		ioPro.sen.sg[ch].vdhdmon.bit.hdin = 0;
#endif  // CO_DEBUG_ON_PC
        // Minimum value parameter
		self->priv->ercd = impro_sensg_get_monitor_info(self->priv->improSensg, ch, &sgMoniInfo);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sensg_get_monitor_info(%d) min_para Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_1_print_7(self->priv->imPro11Print, "min_para", ch, &sgMoniInfo);
		}

		// invalid value parameter
		self->priv->ercd = impro_sensg_get_monitor_info(self->priv->improSensg, ch, NULL);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sensg_get_monitor_info(%d) invalid Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_1_print_7(self->priv->imPro11Print, "invalid", ch, &sgMoniInfo);
		}
    }
}

void ct_im_pro1_1_8(CtImPro11* self, const kuint32 idx)
{
	E_IM_PRO_SLVS_STREAM_TYPE streamType = E_IM_PRO_SLVS_STREAM_TYPE_A;//TODO

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senslvs_sr() slvsec.common  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.common.sr.word,   ioPro.sen.slvsec.common.sr.word   ));
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.slvsec.common.sr.bit.upda = 0;
		ioPro.sen.slvsec.common.sr.bit.inita = 1;
		ioPro.sen.slvsec.common.sr.bit.updb = 0;
		ioPro.sen.slvsec.common.sr.bit.initb = 1;
#endif  // CO_DEBUG_ON_PC
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_A;
		self->priv->ercd = impro_senslvs_sr(self->priv->improSenslvs, streamType);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senslvs_sr(%d) min_para Error self->priv->ercd=0x%x\n", streamType, self->priv->ercd));
		} else {
			im_pro_1_1_print_8(self->priv->imPro11Print, "", streamType);
		}

#ifdef CO_DEBUG_ON_PC
		ioPro.sen.slvsec.common.sr.bit.upda = 0;
		ioPro.sen.slvsec.common.sr.bit.inita = 1;
		ioPro.sen.slvsec.common.sr.bit.updb = 0;
		ioPro.sen.slvsec.common.sr.bit.initb = 1;
#endif  // CO_DEBUG_ON_PC
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_B;
		self->priv->ercd = impro_senslvs_sr(self->priv->improSenslvs, streamType);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senslvs_sr(%d) min_para Error self->priv->ercd=0x%x\n", streamType, self->priv->ercd));
		} else {
			im_pro_1_1_print_8(self->priv->imPro11Print, "", streamType);
		}

#ifdef CO_DEBUG_ON_PC
		ioPro.sen.slvsec.common.sr.bit.upda = 0;
		ioPro.sen.slvsec.common.sr.bit.inita = 1;
		ioPro.sen.slvsec.common.sr.bit.updb = 0;
		ioPro.sen.slvsec.common.sr.bit.initb = 1;
#endif  // CO_DEBUG_ON_PC
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_BOTH;
		self->priv->ercd = impro_senslvs_sr(self->priv->improSenslvs, streamType);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senslvs_sr(%d) max_para Error self->priv->ercd=0x%x\n", streamType, self->priv->ercd));
		} else {
			im_pro_1_1_print_8(self->priv->imPro11Print, "", streamType);
		}
	}
}

void ct_im_pro1_1_9(CtImPro11* self, const kuint32 idx)
{
	E_IM_PRO_SLVS_STREAM_TYPE streamType = E_IM_PRO_SLVS_STREAM_TYPE_A;//TODO

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senslvs_update_cfg(0) slvsec.common  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.common.sr.word,   ioPro.sen.slvsec.common.sr.word   ));
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.slvsec.common.sr.bit.upda = 1;
		ioPro.sen.slvsec.common.sr.bit.inita = 0;
		ioPro.sen.slvsec.common.sr.bit.updb = 1;
		ioPro.sen.slvsec.common.sr.bit.initb = 0;
#endif  // CO_DEBUG_ON_PC
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_A;
		self->priv->ercd = impro_senslvs_update_cfg(self->priv->improSenslvs, streamType);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senslvs_update_cfg(%d) min_para Error self->priv->ercd=0x%x\n",
							streamType, self->priv->ercd));
		} else {
			im_pro_1_1_print_9(self->priv->imPro11Print, "", streamType);
		}

#ifdef CO_DEBUG_ON_PC
		ioPro.sen.slvsec.common.sr.bit.upda = 1;
		ioPro.sen.slvsec.common.sr.bit.inita = 0;
		ioPro.sen.slvsec.common.sr.bit.updb = 1;
		ioPro.sen.slvsec.common.sr.bit.initb = 0;
#endif  // CO_DEBUG_ON_PC
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_B;//TODO
		self->priv->ercd = impro_senslvs_update_cfg(self->priv->improSenslvs, streamType);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senslvs_update_cfg(%d) min_para Error self->priv->ercd=0x%x\n",
							streamType, self->priv->ercd));
		} else {
			im_pro_1_1_print_9(self->priv->imPro11Print, "", streamType);
		}

#ifdef CO_DEBUG_ON_PC
		ioPro.sen.slvsec.common.sr.bit.upda = 1;
		ioPro.sen.slvsec.common.sr.bit.inita = 0;
		ioPro.sen.slvsec.common.sr.bit.updb = 1;
		ioPro.sen.slvsec.common.sr.bit.initb = 0;
#endif  // CO_DEBUG_ON_PC
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_BOTH;//TODO
		self->priv->ercd = impro_senslvs_update_cfg(self->priv->improSenslvs, streamType);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senslvs_update_cfg(%d) max_para Error self->priv->ercd=0x%x\n",
							streamType, self->priv->ercd));
		} else {
			im_pro_1_1_print_9(self->priv->imPro11Print, "", streamType);
		}
	}
}
#endif //CO_CT_IM_PRO_DISABLE

CtImPro11* ct_im_pro1_1_new(void)
{
	CtImPro11* self = k_object_new_with_private(CT_TYPE_IM_PRO1_1, sizeof(CtImPro11Private));

	return self;
}

