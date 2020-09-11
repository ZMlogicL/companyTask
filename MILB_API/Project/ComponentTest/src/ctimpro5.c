/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈元
*@brief : CtImPro5
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impropastop.h"
#include "impropasspt.h"
#include "improsensg.h"
#include "ctimpro5.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro5, ct_im_pro5)
#define CT_IM_PRO5_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro5Private, CT_TYPE_IM_PRO5))


struct _CtImPro5Private
{
	ImproPastop *improPastop;
	ImproPasspt *improPasspt;
	ImproSensg *improSensg;
	ImPro5Print *imPro5Print;
	kint32 ercd;
};


/********
 * IMPL
 */
static void ct_im_pro5_constructor(CtImPro5 *self)
{
	CtImPro5Private *priv = CT_IM_PRO5_GET_PRIVATE(self);

	priv->improPastop = impro_pastop_new();
	priv->improPasspt = impro_passpt_new();
	priv->improSensg = impro_sensg_new();
	priv->imPro5Print = im_pro_5_print_new();
	priv->ercd = 0;
}

static void ct_im_pro5_destructor(CtImPro5 *self)
{
	CtImPro5Private *priv = CT_IM_PRO5_GET_PRIVATE(self);

	if (priv->improPastop) {
		k_object_unref(priv->improPastop);
		priv->improPastop = NULL;
	}

	if (priv->improPasspt) {
		k_object_unref(priv->improPasspt);
		priv->improPasspt = NULL;
	}

	if (priv->improSensg) {
		k_object_unref(priv->improSensg);
		priv->improSensg = NULL;
	}

	if (priv->imPro5Print) {
		k_object_unref(priv->imPro5Print);
		priv->imPro5Print = NULL;
	}
}


/********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro5_1(CtImPro5* self, const kuint32 idx)
{
	CtImPro5Private *priv = CT_IM_PRO5_GET_PRIVATE(self);

    if (idx == 1) {
        impro_pastop_init(priv->improPastop);
        Ddim_Print(("impro_pastop_init() result:sr(%u)\n", ioPro.pas.pastop.sr.bit.sr));
    }
}

void ct_im_pro5_2(CtImPro5* self, const kuint32 idx)
{
	CtImPro5Private *priv = CT_IM_PRO5_GET_PRIVATE(self);

    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_pastop_sw_reset() sr (0x%08lx, %lx)\n", (kulong)&ioPro.pas.pastop.sr.word,    ioPro.pas.pastop.sr.word  ));

        // Normal case
        priv->ercd = impro_pastop_sw_reset(priv->improPastop);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("impro_pastop_sw_reset() Error priv->ercd=0x%x\n", priv->ercd));
        } else {
            Ddim_Print(("impro_pastop_sw_reset() result:sr(%u)\n", ioPro.pas.pastop.sr.bit.sr));
        }

        // illegal case
        impro_sensg_start(priv->improSensg, ImproSensg_E_IM_PRO_SG_CH_0);

        priv->ercd = impro_pastop_sw_reset(priv->improPastop);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("impro_pastop_sw_reset() Error priv->ercd=0x%x\n", priv->ercd));
        } else {
            Ddim_Print(("impro_pastop_sw_reset() result:sr(%u)\n", ioPro.pas.pastop.sr.bit.sr));
        }
        impro_sensg_stop(priv->improSensg, ImproSensg_E_IM_PRO_SG_CH_0, 0);
    }
}

void ct_im_pro5_3(CtImPro5* self, const kuint32 idx)
{
	CtImPro5Private *priv = CT_IM_PRO5_GET_PRIVATE(self);
    EimproPastopClkType clkType;
    kuchar onOff;
    kuchar waitSkip;

    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_pastop_control_clock() clkstp1 (0x%08lx, %lx)\n", (kulong)&ioPro.pas.pastop.clkstp.word,  ioPro.pas.pastop.clkstp.word  ));

        // SENSORCLK ON
        clkType = ImproPastop_E_IM_PRO_PASTOP_CLK_TYPE_PASCLK;
        onOff = D_IM_PRO_CLOCK_ON;
        waitSkip = 0;
        priv->ercd = impro_pastop_control_clock(priv->improPastop, clkType, onOff, waitSkip);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("impro_pastop_control_clock(%u, %u, %u) Error priv->ercd=0x%x\n",
            		clkType, onOff, waitSkip, priv->ercd));
        } else {
            Ddim_Print(("impro_pastop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
            		clkType, onOff, waitSkip, ioPro.pas.pastop.clkstp.word));
        }

        // SENSORCLK OFF
        clkType = ImproPastop_E_IM_PRO_PASTOP_CLK_TYPE_PASCLK;
        onOff = D_IM_PRO_CLOCK_OFF;
        waitSkip = 0;
        priv->ercd = impro_pastop_control_clock(priv->improPastop, clkType, onOff, waitSkip);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("impro_pastop_control_clock(%u, %u, %u) Error priv->ercd=0x%x\n",
            		clkType, onOff, waitSkip, priv->ercd));
        } else {
            Ddim_Print(("impro_pastop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
            		clkType, onOff, waitSkip, ioPro.pas.pastop.clkstp.word));
        }

        // wait skip on
        clkType = ImproPastop_E_IM_PRO_PASTOP_CLK_TYPE_PASCLK;
        onOff = D_IM_PRO_CLOCK_ON;
        waitSkip = 1;
        priv->ercd = impro_pastop_control_clock(priv->improPastop, clkType, onOff, waitSkip);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("impro_pastop_control_clock(%u, %u, %u) Error priv->ercd=0x%x\n",
            		clkType, onOff, waitSkip, priv->ercd));
        } else {
            Ddim_Print(("impro_pastop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
            		clkType, onOff, waitSkip, ioPro.pas.pastop.clkstp.word));
        }

        // wait skip on
        clkType = ImproPastop_E_IM_PRO_PASTOP_CLK_TYPE_PASCLK;
        onOff = D_IM_PRO_CLOCK_OFF;
        waitSkip = 1;
        priv->ercd = impro_pastop_control_clock(priv->improPastop, clkType, onOff, waitSkip);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("impro_pastop_control_clock(%u, %u, %u) Error priv->ercd=0x%x\n",
            		clkType, onOff, waitSkip, priv->ercd));
        } else {
            Ddim_Print(("impro_pastop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
            		clkType, onOff, waitSkip, ioPro.pas.pastop.clkstp.word));
        }
    }
}

void ct_im_pro5_4(CtImPro5* self, const kuint32 idx)
{
	CtImPro5Private *priv = CT_IM_PRO5_GET_PRIVATE(self);
    TimproPastopCtrl ctrlMax = {
        .org = ImproPastop_E_IM_PRO_PASTOP_ORG_R_PDAF,
    };
    TimproPastopCtrl ctrlMin = {
        .org = ImproPastop_E_IM_PRO_PASTOP_ORG_L_PDAF,
    };

    if (idx == 1) {
        priv->ercd = impro_pastop_ctrl(priv->improPastop, &ctrlMax);
        im_pro_5_print_4(priv->imPro5Print, "max_para", priv->ercd);

        priv->ercd = impro_pastop_ctrl(priv->improPastop, &ctrlMin);
        im_pro_5_print_4(priv->imPro5Print, "min_para", priv->ercd);
    }
}

void ct_im_pro5_5(CtImPro5* self, const kuint32 idx)
{
	CtImPro5Private *priv = CT_IM_PRO5_GET_PRIVATE(self);

    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_passpt_start() spttrg (0x%08lx, %lx)\n", (kulong)&ioPro.pas.spt.spttrg.word, ioPro.pas.spt.spttrg.word ));
        // Maximum value parameter
#ifdef CO_DEBUG_ON_PC
        ioPro.pas.spt.spttrg.bit.spttrg = 0;
#endif
        priv->ercd = impro_passpt_start(priv->improPasspt);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("Im_PRO_PAS_Start() Error priv->ercd=0x%x\n", priv->ercd));
        } else {
            im_pro_5_print_5(priv->imPro5Print, priv->ercd);
        }
    }
}

void ct_im_pro5_6(CtImPro5* self, const kuint32 idx)
{
	CtImPro5Private *priv = CT_IM_PRO5_GET_PRIVATE(self);
    kuchar force;

    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_passpt_stop() spttrg (0x%08lx, %lx)\n", (kulong)&ioPro.pas.spt.spttrg.word, ioPro.pas.spt.spttrg.word  ));
        // Maximum value parameter
#ifdef CO_DEBUG_ON_PC
        ioPro.pas.spt.spttrg.bit.spttrg = 3;
#endif
        force = 0;
        priv->ercd = impro_passpt_stop(priv->improPasspt, force);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("impro_passpt_stop() Error priv->ercd=0x%x\n", priv->ercd));
        } else {
            im_pro_5_print_6(priv->imPro5Print, priv->ercd, force);
        }

        force = 1;
        priv->ercd = impro_passpt_stop(priv->improPasspt, force);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("impro_passpt_stop() Error priv->ercd=0x%x\n", priv->ercd));
        } else {
            im_pro_5_print_6(priv->imPro5Print, priv->ercd, force);
        }
    }
}

void ct_im_pro5_7(CtImPro5* self, const kuint32 idx)
{
	CtImPro5Private *priv = CT_IM_PRO5_GET_PRIVATE(self);
	TimproSptCtrl ctrlMax = {
        .tableSel = E_IM_PRO_SPT_TBL_SEL_SPTTBL1,//TODO
        .horizontalPixel = 255,
        .verticalPixel = 255,
        .inverseBase = 511,
        .inverseExponent = 14,
        .posY = 4095,
        .posX = 8191,
        .vBlockSize = 15,
        .hBlockSize = 15,
        .upperClipValue = 32767,
        .lowerClipValue = 32767,
        .correctionThroughVal = 32767,
    };
    TimproSptCtrl ctrlMin = {
        .tableSel = E_IM_PRO_SPT_TBL_SEL_SPTTBL0,
        .horizontalPixel = 2,
        .verticalPixel = 2,
        .inverseBase = 0,
        .inverseExponent = 0,
        .posY = 0,
        .posX = 0,
        .vBlockSize = 0,
        .hBlockSize = 0,
        .upperClipValue = 0,
        .lowerClipValue = 0,
        .correctionThroughVal = 0,
    };

    if (idx == 1) {
        priv->ercd = impro_passpt_ctrl(priv->improPasspt, &ctrlMax);
        im_pro_5_print_7(priv->imPro5Print, "max_para", priv->ercd, &ctrlMax);

        priv->ercd = impro_passpt_ctrl(priv->improPasspt, &ctrlMin);
        im_pro_5_print_7(priv->imPro5Print, "min_para", priv->ercd, &ctrlMin);
    }
}

void ct_im_pro5_8(CtImPro5* self, const kuint32 idx)
{
	CtImPro5Private *priv = CT_IM_PRO5_GET_PRIVATE(self);
	kuchar paenTrg;

    if (idx == 1) {
        paenTrg = 1;
        priv->ercd = impro_passpt_set_paen(priv->improPasspt, paenTrg);
        im_pro_5_print_8(priv->imPro5Print, priv->ercd, paenTrg);

        paenTrg = 0;
        priv->ercd = impro_passpt_set_paen(priv->improPasspt, paenTrg);
        im_pro_5_print_8(priv->imPro5Print, priv->ercd, paenTrg);
    }
}

void ct_im_pro5_9(CtImPro5* self, const kuint32 idx)
{
	CtImPro5Private *priv = CT_IM_PRO5_GET_PRIVATE(self);
	kint32 cmpErcd;
	TimproSptTable shdTbl;
	kint16 sptShd[257];
	kuchar tblSel;
	kuchar* regTblAddr;

	shdTbl.pshdTbl = sptShd;
	shdTbl.size = sizeof(sptShd);

    if (idx == 1) {
        for (tblSel = E_IM_PRO_SPT_TBL_SEL_SPTTBL0; tblSel < E_IM_PRO_SPT_TBL_SEL_SPTTBL1 + 1; tblSel++) {//TODO
            if (tblSel == E_IM_PRO_SPT_TBL_SEL_SPTTBL0) {
                regTblAddr = (kuchar*)ioProTbl.pasTbl.spttbl0.word;
            } else {
                regTblAddr = (kuchar*)ioProTbl.pasTbl.spttbl1.word;
            }
            shdTbl.size = 256;
            memset(sptShd, 0xFFFF, sizeof(sptShd));
            priv->ercd = impro_passpt_set_table(priv->improPasspt, tblSel, &shdTbl);
            if (priv->ercd == DdimUserCustom_E_OK) {
                cmpErcd = memcmp(regTblAddr, sptShd, shdTbl.size * sizeof(kint16));
            } else {
                cmpErcd = -1;
            }
            //pgr0539
            im_pro_5_print_9(priv->imPro5Print, "max_para", priv->ercd, cmpErcd);

            memset(sptShd, 0, sizeof(sptShd));
            priv->ercd = impro_passpt_set_table(priv->improPasspt, tblSel, &shdTbl);
            if (priv->ercd == DdimUserCustom_E_OK) {
                cmpErcd = memcmp(regTblAddr, sptShd, shdTbl.size * sizeof(kint16));
            } else {
                cmpErcd = -1;
            }
            //pgr0539
            im_pro_5_print_9(priv->imPro5Print, "min_para", priv->ercd, cmpErcd);
        }
    }
}

void ct_im_pro5_10(CtImPro5* self, const kuint32 idx)
{
	CtImPro5Private *priv = CT_IM_PRO5_GET_PRIVATE(self);
	const TimproRdmaSptShdTblAddr* addr;
	kuchar tblSel;

    if (idx == 1) {
        for (tblSel = E_IM_PRO_SPT_TBL_SEL_SPTTBL0; tblSel < E_IM_PRO_SPT_TBL_SEL_SPTTBL1 + 1; tblSel++) {
            priv->ercd = impro_passpt_get_rdma_addr_spt_shd_tbl(priv->improPasspt, tblSel, &addr);
            im_pro_5_1print_0(priv->imPro5Print, priv->ercd, tblSel, &addr);
        }
    }
}
#endif

CtImPro5* ct_im_pro5_new(void)
{
	CtImPro5* self = k_object_new_with_private(CT_TYPE_IM_PRO5, sizeof(CtImPro5Private));

	return self;
}


