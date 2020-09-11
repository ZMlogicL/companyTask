/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro16
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsencmipi.h"
#include "improsenlvds.h"
#include "ctimpro16.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro16, ct_im_pro1_6)
#define CT_IM_PRO1_6_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro16Private, CT_TYPE_IM_PRO1_6))


struct _CtImPro16Private
{
	ImproSencmipi *improSencmipi;
	ImproSenlvds *improSenlvds;
	ImPro16Print *imPro16Print;
	kint32 ercd;
};


/**********
 * IMPL
 */
static void ct_im_pro1_6_constructor(CtImPro16 *self)
{
	self->priv = CT_IM_PRO1_6_GET_PRIVATE(self);
	self->priv->improSencmipi = impro_sencmipi_new();
	self->priv->improSenlvds = impro_senlvds_new();
	self->priv->imPro16Print = im_pro_1_6_print_new();
	self->priv->ercd = 0;
}

static void ct_im_pro1_6_destructor(CtImPro16 *self)
{
	CtImPro16Private *priv = CT_IM_PRO1_6_GET_PRIVATE(self);

	if (priv->improSencmipi) {
		k_object_unref(priv->improSencmipi);
		priv->improSencmipi = NULL;
	}

	if (priv->improSenlvds) {
		k_object_unref(priv->improSenlvds);
		priv->improSenlvds = NULL;
	}

	if (priv->imPro16Print) {
		k_object_unref(priv->imPro16Print);
		priv->imPro16Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro1_6_0(CtImPro16* self, const kuint32 idx)
{
	kuchar paenTrg0;
	kuchar paenTrg1;
	kuchar ch;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sencmipi_set_pean(0) MPICPAEN0    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[0].MPICPAEN0.word, ioPro.sen.mipic[0].MPICPAEN0.word ));
//        Ddim_Print(("impro_sencmipi_set_pean(0) MPICPAEN1    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[0].MPICPAEN1.word, ioPro.sen.mipic[0].MPICPAEN1.word ));
//        Ddim_Print(("impro_sencmipi_set_pean(1) MPICPAEN0    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[1].MPICPAEN0.word, ioPro.sen.mipic[1].MPICPAEN0.word ));
//        Ddim_Print(("impro_sencmipi_set_pean(1) MPICPAEN1    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[1].MPICPAEN1.word, ioPro.sen.mipic[1].MPICPAEN1.word ));
//        Ddim_Print(("impro_sencmipi_set_pean(2) MPICPAEN0    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[2].MPICPAEN0.word, ioPro.sen.mipic[2].MPICPAEN0.word ));
//        Ddim_Print(("impro_sencmipi_set_pean(2) MPICPAEN1    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[2].MPICPAEN1.word, ioPro.sen.mipic[2].MPICPAEN1.word ));
//        Ddim_Print(("impro_sencmipi_set_pean(3) MPICPAEN0    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[3].MPICPAEN0.word, ioPro.sen.mipic[3].MPICPAEN0.word ));
//        Ddim_Print(("impro_sencmipi_set_pean(3) MPICPAEN1    (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[3].MPICPAEN1.word, ioPro.sen.mipic[3].MPICPAEN1.word ));

// enable value parameter
		ch = E_IM_PRO_CMIPI_CH3;//TODO
		paenTrg0 = 1;
		paenTrg1 = 1;
		self->priv->ercd = impro_sencmipi_set_pean(self->priv->improSencmipi, ch, paenTrg0, paenTrg1);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_set_pean() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_0(self->priv->imPro16Print, "max_para", ch, paenTrg0, paenTrg1);
		}

		// disable value parameter
		ch = E_IM_PRO_CMIPI_CH0;
		paenTrg0 = 0;
		paenTrg1 = 0;
		self->priv->ercd = impro_sencmipi_set_pean(self->priv->improSencmipi, ch, paenTrg0, paenTrg1);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_set_pean() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_0(self->priv->imPro16Print, "min_para", ch, paenTrg0, paenTrg1);
		}

		// macro running error test
		ch = E_IM_PRO_CMIPI_CH0;
		paenTrg0 = 0;
		paenTrg1 = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipic[ch].mpictrg.bit.mpictrg = D_IM_PRO_TRG_STATUS_RUNNING;
#else
		impro_sencmipi_start(self->priv->improSencmipi, ch);
#endif
		self->priv->ercd = impro_sencmipi_set_pean(self->priv->improSencmipi, ch, paenTrg0, paenTrg1);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_set_pean() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_0(self->priv->imPro16Print, "macro running error", ch, paenTrg0, paenTrg1);
		}
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipic[ch].mpictrg.bit.mpictrg = D_IM_PRO_TRG_STATUS_STOPPED;
#else
		impro_sencmipi_stop(self->priv->improSencmipi, ch, 0);
#endif
	}
}

void ct_im_pro1_6_1(CtImPro16* self, const kuint32 idx)
{
	TimproCmipiStatus status;
	E_IM_PRO_CMIPI_CH ch;//TODO

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicpvr            (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[0].mpicpvr.word        ,   ioPro.sen.mipic[0].mpicpvr.word           ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrlst        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrlst.word    ,   ioPro.sen.mipic[0].mpicprlrlst.word       ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrwecnt0     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrwecnt0.word ,   ioPro.sen.mipic[0].mpicprlrwecnt0.word    ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrwecnt1     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrwecnt1.word ,   ioPro.sen.mipic[0].mpicprlrwecnt1.word    ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrwecnt2     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrwecnt2.word ,   ioPro.sen.mipic[0].mpicprlrwecnt2.word    ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrwcnt0      (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrwcnt0.dword,   ioPro.sen.mipic[0].mpicprlrwcnt0.dword    ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrwcnt1      (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrwcnt1.dword,   ioPro.sen.mipic[0].mpicprlrwcnt1.dword    ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrwcnt2      (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrwcnt2.dword,   ioPro.sen.mipic[0].mpicprlrwcnt2.dword    ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrserrcnt0   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrserrcnt0.word,  ioPro.sen.mipic[0].mpicprlrserrcnt0.word  ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrserrcnt1   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrserrcnt1.word,  ioPro.sen.mipic[0].mpicprlrserrcnt1.word  ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrserrcnt2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrserrcnt2.word,  ioPro.sen.mipic[0].mpicprlrserrcnt2.word  ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrserrloc0   (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrserrloc0.dword,    ioPro.sen.mipic[0].mpicprlrserrloc0.dword ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrserrloc1   (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrserrloc1.dword,    ioPro.sen.mipic[0].mpicprlrserrloc1.dword ));
//        Ddim_Print(("impro_sencmipi_get_status(0) mpicprlrserrloc2   (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[0].mpicprlrserrloc2.dword,    ioPro.sen.mipic[0].mpicprlrserrloc2.dword ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicpvr            (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[1].mpicpvr.word        ,   ioPro.sen.mipic[1].mpicpvr.word           ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrlst        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrlst.word    ,   ioPro.sen.mipic[1].mpicprlrlst.word       ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrwecnt0     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrwecnt0.word ,   ioPro.sen.mipic[1].mpicprlrwecnt0.word    ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrwecnt1     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrwecnt1.word ,   ioPro.sen.mipic[1].mpicprlrwecnt1.word    ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrwecnt2     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrwecnt2.word ,   ioPro.sen.mipic[1].mpicprlrwecnt2.word    ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrwcnt0      (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrwcnt0.dword,   ioPro.sen.mipic[1].mpicprlrwcnt0.dword    ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrwcnt1      (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrwcnt1.dword,   ioPro.sen.mipic[1].mpicprlrwcnt1.dword    ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrwcnt2      (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrwcnt2.dword,   ioPro.sen.mipic[1].mpicprlrwcnt2.dword    ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrserrcnt0   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrserrcnt0.word,  ioPro.sen.mipic[1].mpicprlrserrcnt0.word  ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrserrcnt1   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrserrcnt1.word,  ioPro.sen.mipic[1].mpicprlrserrcnt1.word  ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrserrcnt2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrserrcnt2.word,  ioPro.sen.mipic[1].mpicprlrserrcnt2.word  ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrserrloc0   (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrserrloc0.dword,    ioPro.sen.mipic[1].mpicprlrserrloc0.dword ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrserrloc1   (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrserrloc1.dword,    ioPro.sen.mipic[1].mpicprlrserrloc1.dword ));
//        Ddim_Print(("impro_sencmipi_get_status(1) mpicprlrserrloc2   (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[1].mpicprlrserrloc2.dword,    ioPro.sen.mipic[1].mpicprlrserrloc2.dword ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicpvr            (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[2].mpicpvr.word        ,   ioPro.sen.mipic[2].mpicpvr.word           ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrlst        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrlst.word    ,   ioPro.sen.mipic[2].mpicprlrlst.word       ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrwecnt0     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrwecnt0.word ,   ioPro.sen.mipic[2].mpicprlrwecnt0.word    ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrwecnt1     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrwecnt1.word ,   ioPro.sen.mipic[2].mpicprlrwecnt1.word    ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrwecnt2     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrwecnt2.word ,   ioPro.sen.mipic[2].mpicprlrwecnt2.word    ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrwcnt0      (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrwcnt0.dword,   ioPro.sen.mipic[2].mpicprlrwcnt0.dword    ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrwcnt1      (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrwcnt1.dword,   ioPro.sen.mipic[2].mpicprlrwcnt1.dword    ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrwcnt2      (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrwcnt2.dword,   ioPro.sen.mipic[2].mpicprlrwcnt2.dword    ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrserrcnt0   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrserrcnt0.word,  ioPro.sen.mipic[2].mpicprlrserrcnt0.word  ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrserrcnt1   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrserrcnt1.word,  ioPro.sen.mipic[2].mpicprlrserrcnt1.word  ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrserrcnt2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrserrcnt2.word,  ioPro.sen.mipic[2].mpicprlrserrcnt2.word  ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrserrloc0   (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrserrloc0.dword,    ioPro.sen.mipic[2].mpicprlrserrloc0.dword ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrserrloc1   (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrserrloc1.dword,    ioPro.sen.mipic[2].mpicprlrserrloc1.dword ));
//        Ddim_Print(("impro_sencmipi_get_status(2) mpicprlrserrloc2   (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[2].mpicprlrserrloc2.dword,    ioPro.sen.mipic[2].mpicprlrserrloc2.dword ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicpvr            (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[3].mpicpvr.word        ,   ioPro.sen.mipic[3].mpicpvr.word           ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrlst        (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrlst.word    ,   ioPro.sen.mipic[3].mpicprlrlst.word       ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrwecnt0     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrwecnt0.word ,   ioPro.sen.mipic[3].mpicprlrwecnt0.word    ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrwecnt1     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrwecnt1.word ,   ioPro.sen.mipic[3].mpicprlrwecnt1.word    ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrwecnt2     (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrwecnt2.word ,   ioPro.sen.mipic[3].mpicprlrwecnt2.word    ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrwcnt0      (0x%08lx, %lllx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrwcnt0.dword,  ioPro.sen.mipic[3].mpicprlrwcnt0.dword    ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrwcnt1      (0x%08lx, %lllx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrwcnt1.dword,  ioPro.sen.mipic[3].mpicprlrwcnt1.dword    ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrwcnt2      (0x%08lx, %lllx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrwcnt2.dword,  ioPro.sen.mipic[3].mpicprlrwcnt2.dword    ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrserrcnt0   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrserrcnt0.word,  ioPro.sen.mipic[3].mpicprlrserrcnt0.word  ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrserrcnt1   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrserrcnt1.word,  ioPro.sen.mipic[3].mpicprlrserrcnt1.word  ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrserrcnt2   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrserrcnt2.word,  ioPro.sen.mipic[3].mpicprlrserrcnt2.word  ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrserrloc0   (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrserrloc0.dword,    ioPro.sen.mipic[3].mpicprlrserrloc0.dword ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrserrloc1   (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrserrloc1.dword,    ioPro.sen.mipic[3].mpicprlrserrloc1.dword ));
//        Ddim_Print(("impro_sencmipi_get_status(3) mpicprlrserrloc2   (0x%08lx, %llx)\n", (kulong)&ioPro.sen.mipic[3].mpicprlrserrloc2.dword,    ioPro.sen.mipic[3].mpicprlrserrloc2.dword ));

// Maximum value parameter
		ch = E_IM_PRO_CMIPI_CH3;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipic[ch].mpicpvr.bit.ssl0 = 1;
		ioPro.sen.mipic[ch].mpicpvr.bit.ssl1 = 1;
		ioPro.sen.mipic[ch].mpicpvr.bit.ssl2 = 1;
		ioPro.sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus0 = 255;
		ioPro.sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus1 = 255;
		ioPro.sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus2 = 255;
		ioPro.sen.mipic[ch].mpicprlrwecnt0.bit.cpRlrWerrcnt0 = 255;
		ioPro.sen.mipic[ch].mpicprlrwecnt1.bit.cpRlrWerrcnt1 = 255;
		ioPro.sen.mipic[ch].mpicprlrwecnt2.bit.cpRlrWerrcnt2 = 255;
		ioPro.sen.mipic[ch].mpicprlrwcnt0.bit.cpRlrWcnt0 = 0xFFFFFFFFFFFF;
		ioPro.sen.mipic[ch].mpicprlrwcnt1.bit.cpRlrWcnt1 = 0xFFFFFFFFFFFF;
		ioPro.sen.mipic[ch].mpicprlrwcnt2.bit.cpRlrWcnt2 = 0xFFFFFFFFFFFF;
		ioPro.sen.mipic[ch].mpicprlrserrcnt0.bit.cpRlrSyerrcnt0 = 255;
		ioPro.sen.mipic[ch].mpicprlrserrcnt1.bit.cpRlrSyerrcnt1 = 255;
		ioPro.sen.mipic[ch].mpicprlrserrcnt2.bit.cpRlrSyerrcnt2 = 255;
		ioPro.sen.mipic[ch].mpicprlrserrloc0.bit.cpRlrSyerrloc0 = 0xFFFFFFFFFFFF;
		ioPro.sen.mipic[ch].mpicprlrserrloc1.bit.cpRlrSyerrloc1 = 0xFFFFFFFFFFFF;
		ioPro.sen.mipic[ch].mpicprlrserrloc2.bit.cpRlrSyerrloc2 = 0xFFFFFFFFFFFF;
#endif  // CO_DEBUG_ON_PC
		self->priv->ercd = impro_sencmipi_get_status(self->priv->improSencmipi, ch, &status);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_get_status() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_1(self->priv->imPro16Print, "max_para", ch, &status);
		}

		ch = E_IM_PRO_CMIPI_CH0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.mipic[ch].mpicpvr.bit.ssl0 = 0;
		ioPro.sen.mipic[ch].mpicpvr.bit.ssl1 = 0;
		ioPro.sen.mipic[ch].mpicpvr.bit.ssl2 = 0;
		ioPro.sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus0 = 0;
		ioPro.sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus1 = 0;
		ioPro.sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus2 = 0;
		ioPro.sen.mipic[ch].mpicprlrwecnt0.bit.cpRlrWerrcnt0 = 0;
		ioPro.sen.mipic[ch].mpicprlrwecnt1.bit.cpRlrWerrcnt1 = 0;
		ioPro.sen.mipic[ch].mpicprlrwecnt2.bit.cpRlrWerrcnt2 = 0;
		ioPro.sen.mipic[ch].mpicprlrwcnt0.bit.cpRlrWcnt0 = 0;
		ioPro.sen.mipic[ch].mpicprlrwcnt1.bit.cpRlrWcnt1 = 0;
		ioPro.sen.mipic[ch].mpicprlrwcnt2.bit.cpRlrWcnt2 = 0;
		ioPro.sen.mipic[ch].mpicprlrserrcnt0.bit.cpRlrSyerrcnt0 = 0;
		ioPro.sen.mipic[ch].mpicprlrserrcnt1.bit.cpRlrSyerrcnt1 = 0;
		ioPro.sen.mipic[ch].mpicprlrserrcnt2.bit.cpRlrSyerrcnt2 = 0;
		ioPro.sen.mipic[ch].mpicprlrserrloc0.bit.cpRlrSyerrloc0 = 0;
		ioPro.sen.mipic[ch].mpicprlrserrloc1.bit.cpRlrSyerrloc1 = 0;
		ioPro.sen.mipic[ch].mpicprlrserrloc2.bit.cpRlrSyerrloc2 = 0;
#endif  // CO_DEBUG_ON_PC
		// Minimum value parameter
		self->priv->ercd = impro_sencmipi_get_status(self->priv->improSencmipi, ch, &status);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_get_status() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_1(self->priv->imPro16Print, "min_para", ch, &status);
		}

		// invalid value parameter
		ch = E_IM_PRO_CMIPI_CH0;
		self->priv->ercd = impro_sencmipi_get_status(self->priv->improSencmipi, ch, NULL);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sencmipi_get_status() invalid Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_1(self->priv->imPro16Print, "invalid", ch, &status);
		}
	}
}

void ct_im_pro1_6_2(CtImPro16* self, const kuint32 idx)
{
	kuchar ch;

	if (idx == 1) {
		// max parameter
		ch = E_IM_PRO_LVDS_CH_3;
		self->priv->ercd = impro_senlvds_start(self->priv->improSenlvds, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_start(%u) Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_6_print_2(self->priv->imPro16Print, "max_para", ch);
		}

		// min parameter
		ch = E_IM_PRO_LVDS_CH_0;
		self->priv->ercd = impro_senlvds_start(self->priv->improSenlvds, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_start(%u) Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_6_print_2(self->priv->imPro16Print, "min_para", ch);
		}
	}
}

void ct_im_pro1_6_3(CtImPro16* self, const kuint32 idx)
{
	kuchar ch;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senlvds_stop(0) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.lvds[0].lvdstrg.word,    ioPro.sen.lvds[0].lvdstrg.word));
//        Ddim_Print(("impro_senlvds_stop(1) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.lvds[1].lvdstrg.word,    ioPro.sen.lvds[1].lvdstrg.word));
//        Ddim_Print(("impro_senlvds_stop(2) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.lvds[2].lvdstrg.word,    ioPro.sen.lvds[2].lvdstrg.word));
//        Ddim_Print(("impro_senlvds_stop(3) sgtrg (0x%08lx, %lx)\n", (kulong)&ioPro.sen.lvds[3].lvdstrg.word,    ioPro.sen.lvds[3].lvdstrg.word));
		// Maximum value parameter
		ch = E_IM_PRO_LVDS_CH_3;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.lvds[ch].lvdstrg.bit.lvdstrg = 3;
#endif
		self->priv->ercd = impro_senlvds_stop(self->priv->improSenlvds, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_stop(%u) max_para Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_6_print_3(self->priv->imPro16Print, "max_para", ch);
		}

		// Minimum value parameter
		ch = E_IM_PRO_LVDS_CH_0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.lvds[ch].lvdstrg.bit.lvdstrg = 3;
#endif
		self->priv->ercd = impro_senlvds_stop(self->priv->improSenlvds, ch);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_stop(%u) min_para Error self->priv->ercd=0x%x\n", ch, self->priv->ercd));
		} else {
			im_pro_1_6_print_3(self->priv->imPro16Print, "min_para", ch);
		}
	}
}

void ct_im_pro1_6_4(CtImPro16* self, const kuint32 idx)
{
    kuchar ch;
    TimproLvdsCtrl lvdsCtrlMax = {
        .transMode = ImproSenlvds_E_IM_PRO_LVDS_INPUT_PARALLEL,
        .outputChNo = ImproSenlvds_E_IM_PRO_LVDS_OUT_1CH,
        .lane = ImproSenlvds_E_IM_PRO_LVDS_LANE_16,
        .dataBitWidth = ImproSenlvds_E_IM_PRO_LVDS_BIT_WIDTH_RAW_10_BIT,
        .lsft = ImproSenlvds_E_IM_PRO_LVDS_SFT_1BIT_SHIFT_L,
        .syncType = ImproSenlvds_E_IM_PRO_LVDS_SYNC_TYPE_TYPE1,
        .dataInputType = ImproSenlvds_E_IM_PRO_LVDS_INPUT_TYPE_HSZIE,
        .syncBitFix = ImproSenlvds_E_IM_PRO_LVDS_SYNC_BIT_16BIT_FIX,
        .divideOutput = ImproSenlvds_E_IM_PRO_LVDS_DIV_OUT_8,
        .invertedOutput = ImproSenlvds_E_IM_PRO_LVDS_INVERTED_EN,
        .outputMode = E_IM_PRO_LVDS_OUTPUT_MODE_DOL2,//TODO
        .laneMask  = 0xFFFF,
        .clockSelectSp0 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_SNCLK3,
        .clockSelectSp1 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_SNCLK3,
        .clockSelectSp2 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_SNCLK3,
        .clockSelectSp3 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_SNCLK3,
        .clockSelectSp4 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_SNCLK3,
        .clockSelectSp5 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_SNCLK3,
        .clockSelectSp6 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_SNCLK3,
        .clockSelectSp7 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_SNCLK3,
        .dataSelectSp00 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp01 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp10 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp11 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp20 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp21 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp30 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp31 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp40 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp41 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp50 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp51 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp60 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp61 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp70 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .dataSelectSp71 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15,
        .laneSelect = ImproSenlvds_E_IM_PRO_LVDS_SYNC_SEL_SPX_D1,
    };

    TimproLvdsCtrl lvdsCtrlMin = {
        .transMode = ImproSenlvds_E_IM_PRO_LVDS_INPUT_SERIAL,
        .outputChNo = ImproSenlvds_E_IM_PRO_LVDS_OUT_1CH,
        .lane = ImproSenlvds_E_IM_PRO_LVDS_LANE_1,
        .dataBitWidth = ImproSenlvds_E_IM_PRO_LVDS_BIT_WIDTH_RAW_16_BIT,
        .lsft = ImproSenlvds_E_IM_PRO_LVDS_SFT_NONE,
        .syncType = ImproSenlvds_E_IM_PRO_LVDS_SYNC_TYPE_TYPE0,
        .dataInputType = ImproSenlvds_E_IM_PRO_LVDS_INPUT_TYPE_HSZIE,
        .syncBitFix = ImproSenlvds_E_IM_PRO_LVDS_INPUT_TYPE_SYNC_CODE,
        .divideOutput = ImproSenlvds_E_IM_PRO_LVDS_DIV_OUT_2,
        .invertedOutput = ImproSenlvds_E_IM_PRO_LVDS_INVERTED_DIS,
        .outputMode = E_IM_PRO_LVDS_OUTPUT_MODE_NORNAL,//TODO
        .laneMask = 0,
        .clockSelectSp0 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_STOP,
        .clockSelectSp1 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_STOP,
        .clockSelectSp2 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_STOP,
        .clockSelectSp3 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_STOP,
        .clockSelectSp4 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_STOP,
        .clockSelectSp5 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_STOP,
        .clockSelectSp6 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_STOP,
        .clockSelectSp7 = ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_STOP,
        .dataSelectSp00 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp01 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp10 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp11 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp20 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp21 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp30 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp31 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp40 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp41 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp50 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp51 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp60 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp61 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp70 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .dataSelectSp71 = ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0,
        .laneSelect = ImproSenlvds_E_IM_PRO_LVDS_SYNC_SEL_SPX_D0,
    };

    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senlvds_ctrl(0) LVDSCTL1  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[0].LVDSCTL1.word   ,   ioPro.sen.lvds[0].LVDSCTL1.word   ));
//        Ddim_Print(("impro_senlvds_ctrl(0) LVDSCTL2  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[0].LVDSCTL2.word   ,   ioPro.sen.lvds[0].LVDSCTL2.word   ));
//        Ddim_Print(("impro_senlvds_ctrl(0) LVDSCLKS  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[0].LVDSCLKS.word   ,   ioPro.sen.lvds[0].LVDSCLKS.word   ));
//        Ddim_Print(("impro_senlvds_ctrl(0) LVDSDATS  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[0].LVDSDATS.dword  ,   ioPro.sen.lvds[0].LVDSDATS.dword  ));
//        Ddim_Print(("impro_senlvds_ctrl(0) SYNCSEL   (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[0].SYNCSEL.word    ,   ioPro.sen.lvds[0].SYNCSEL.word    ));
//        Ddim_Print(("impro_senlvds_ctrl(1) LVDSCTL1  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[1].LVDSCTL1.word   ,   ioPro.sen.lvds[1].LVDSCTL1.word   ));
//        Ddim_Print(("impro_senlvds_ctrl(1) LVDSCTL2  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[1].LVDSCTL2.word   ,   ioPro.sen.lvds[1].LVDSCTL2.word   ));
//        Ddim_Print(("impro_senlvds_ctrl(1) LVDSCLKS  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[1].LVDSCLKS.word   ,   ioPro.sen.lvds[1].LVDSCLKS.word   ));
//        Ddim_Print(("impro_senlvds_ctrl(1) LVDSDATS  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[1].LVDSDATS.dword  ,   ioPro.sen.lvds[1].LVDSDATS.dword  ));
//        Ddim_Print(("impro_senlvds_ctrl(1) SYNCSEL   (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[1].SYNCSEL.word    ,   ioPro.sen.lvds[1].SYNCSEL.word    ));
//        Ddim_Print(("impro_senlvds_ctrl(2) LVDSCTL1  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[2].LVDSCTL1.word   ,   ioPro.sen.lvds[2].LVDSCTL1.word   ));
//        Ddim_Print(("impro_senlvds_ctrl(2) LVDSCTL2  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[2].LVDSCTL2.word   ,   ioPro.sen.lvds[2].LVDSCTL2.word   ));
//        Ddim_Print(("impro_senlvds_ctrl(2) LVDSCLKS  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[2].LVDSCLKS.word   ,   ioPro.sen.lvds[2].LVDSCLKS.word   ));
//        Ddim_Print(("impro_senlvds_ctrl(2) LVDSDATS  (0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].LVDSDATS.dword  ,   ioPro.sen.lvds[2].LVDSDATS.dword  ));
//        Ddim_Print(("impro_senlvds_ctrl(2) SYNCSEL   (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[2].SYNCSEL.word    ,   ioPro.sen.lvds[2].SYNCSEL.word    ));
//        Ddim_Print(("impro_senlvds_ctrl(3) LVDSCTL1  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[3].LVDSCTL1.word   ,   ioPro.sen.lvds[3].LVDSCTL1.word   ));
//        Ddim_Print(("impro_senlvds_ctrl(3) LVDSCTL2  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[3].LVDSCTL2.word   ,   ioPro.sen.lvds[3].LVDSCTL2.word   ));
//        Ddim_Print(("impro_senlvds_ctrl(3) LVDSCLKS  (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[3].LVDSCLKS.word   ,   ioPro.sen.lvds[3].LVDSCLKS.word   ));
//        Ddim_Print(("impro_senlvds_ctrl(3) LVDSDATS  (0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].LVDSDATS.dword  ,   ioPro.sen.lvds[3].LVDSDATS.dword  ));
//        Ddim_Print(("impro_senlvds_ctrl(3) SYNCSEL   (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[3].SYNCSEL.word    ,   ioPro.sen.lvds[3].SYNCSEL.word    ));
        // Maximum value parameter
		ch = E_IM_PRO_LVDS_CH_3;
		self->priv->ercd = impro_senlvds_ctrl(self->priv->improSenlvds, ch, &lvdsCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_4(self->priv->imPro16Print, "max_para", ch, &lvdsCtrlMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_LVDS_CH_0;
		self->priv->ercd = impro_senlvds_ctrl(self->priv->improSenlvds, ch, &lvdsCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_4(self->priv->imPro16Print, "min_para", ch, &lvdsCtrlMin);
		}
    }
}

void ct_im_pro1_6_5(CtImPro16* self, const kuint32 idx)
{
	kuchar ch;
	kuint16 inputPos;
	kuint16 inputSize;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senlvds_ctrl(0) LHSADD    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[0].LHSADD.word,    ioPro.sen.lvds[0].LHSADD.word ));
//        Ddim_Print(("impro_senlvds_ctrl(0) LHSIZE    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[0].LHSIZE.word,    ioPro.sen.lvds[0].LHSIZE.word ));
//        Ddim_Print(("impro_senlvds_ctrl(1) LHSADD    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[1].LHSADD.word,    ioPro.sen.lvds[1].LHSADD.word ));
//        Ddim_Print(("impro_senlvds_ctrl(1) LHSIZE    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[1].LHSIZE.word,    ioPro.sen.lvds[1].LHSIZE.word ));
//        Ddim_Print(("impro_senlvds_ctrl(2) LHSADD    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[2].LHSADD.word,    ioPro.sen.lvds[2].LHSADD.word ));
//        Ddim_Print(("impro_senlvds_ctrl(2) LHSIZE    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[2].LHSIZE.word,    ioPro.sen.lvds[2].LHSIZE.word ));
//        Ddim_Print(("impro_senlvds_ctrl(3) LHSADD    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[3].LHSADD.word,    ioPro.sen.lvds[3].LHSADD.word ));
//        Ddim_Print(("impro_senlvds_ctrl(3) LHSIZE    (0x%08lx, %lx)\n",  (kulong)&ioPro.sen.lvds[3].LHSIZE.word,    ioPro.sen.lvds[3].LHSIZE.word ));
		// Maximum value parameter
		ch = E_IM_PRO_LVDS_CH_3;
		inputPos = 12288;
		inputSize = 11840;
		self->priv->ercd = impro_senlvds_set_area(self->priv->improSenlvds, ch, inputPos, inputSize);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_set_area() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_5(self->priv->imPro16Print, "max_para", ch, inputPos, inputSize);
		}

		// Minimum value parameter
		ch = E_IM_PRO_LVDS_CH_0;
		inputPos = 0;
		inputSize = 4;
		self->priv->ercd = impro_senlvds_set_area(self->priv->improSenlvds, ch, inputPos, inputSize);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_set_area() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_5(self->priv->imPro16Print, "min_para", ch, inputPos, inputSize);
		}
	}
}

void ct_im_pro1_6_6(CtImPro16* self, const kuint32 idx)
{
    kuchar ch;
    TimproLvdsPixelOrder lvdsOrderMax = {
        .ptnA = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnB = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnC = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnD = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnE = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnF = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnG = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnH = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnI = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnJ = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnK = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnL = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnM = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnN = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnO = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
        .ptnP = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7,
    };

    TimproLvdsPixelOrder lvdsOrderMin = {
        .ptnA = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnB = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnC = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnD = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnE = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnF = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnG = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnH = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnI = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnJ = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnK = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnL = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnM = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnN = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnO = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
        .ptnP = ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senlvds_set_pixel_order(0) LPDCHG  (0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].LPDCHG.dword,   ioPro.sen.lvds[0].LPDCHG.dword));
//        Ddim_Print(("impro_senlvds_set_pixel_order(1) LPDCHG  (0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].LPDCHG.dword,   ioPro.sen.lvds[1].LPDCHG.dword));
//        Ddim_Print(("impro_senlvds_set_pixel_order(2) LPDCHG  (0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].LPDCHG.dword,   ioPro.sen.lvds[2].LPDCHG.dword));
//        Ddim_Print(("impro_senlvds_set_pixel_order(3) LPDCHG  (0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].LPDCHG.dword,   ioPro.sen.lvds[3].LPDCHG.dword));
		// Maximum value parameter
		ch = E_IM_PRO_LVDS_CH_3;
		self->priv->ercd = impro_senlvds_set_pixel_order(self->priv->improSenlvds, ch, &lvdsOrderMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senlvds_set_pixel_order() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_6(self->priv->imPro16Print, "max_para", ch, &lvdsOrderMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_LVDS_CH_0;
		self->priv->ercd = impro_senlvds_set_pixel_order(self->priv->improSenlvds, ch, &lvdsOrderMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senlvds_set_pixel_order() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_6(self->priv->imPro16Print, "min_para", ch, &lvdsOrderMin);
		}
    }
}

void ct_im_pro1_6_7(CtImPro16* self, const kuint32 idx)
{
    kuchar ch;
    TimproLvdsSyncCodeCtrl syncCodeMax = {
        .syncCode[0].sav[0] = 0xFFFF,
        .syncCode[0].sav[1] = 0xFFFF,
        .syncCode[0].sav[2] = 0xFFFF,
        .syncCode[0].sav[3] = 0xFFFF,
        .syncCode[0].eav[0] = 0xFFFF,
        .syncCode[0].eav[1] = 0xFFFF,
        .syncCode[0].eav[2] = 0xFFFF,
        .syncCode[0].eav[3] = 0xFFFF,
        .syncCode[0].sab[0] = 0xFFFF,
        .syncCode[0].sab[1] = 0xFFFF,
        .syncCode[0].sab[2] = 0xFFFF,
        .syncCode[0].sab[3] = 0xFFFF,
        .syncCode[0].eab[0] = 0xFFFF,
        .syncCode[0].eab[1] = 0xFFFF,
        .syncCode[0].eab[2] = 0xFFFF,
        .syncCode[0].eab[3] = 0xFFFF,
        .syncCode[1].sav[0] = 0xFFFF,
        .syncCode[1].sav[1] = 0xFFFF,
        .syncCode[1].sav[2] = 0xFFFF,
        .syncCode[1].sav[3] = 0xFFFF,
        .syncCode[1].eav[0] = 0xFFFF,
        .syncCode[1].eav[1] = 0xFFFF,
        .syncCode[1].eav[2] = 0xFFFF,
        .syncCode[1].eav[3] = 0xFFFF,
        .syncCode[1].sab[0] = 0xFFFF,
        .syncCode[1].sab[1] = 0xFFFF,
        .syncCode[1].sab[2] = 0xFFFF,
        .syncCode[1].sab[3] = 0xFFFF,
        .syncCode[1].eab[0] = 0xFFFF,
        .syncCode[1].eab[1] = 0xFFFF,
        .syncCode[1].eab[2] = 0xFFFF,
        .syncCode[1].eab[3] = 0xFFFF,
        .syncCode[2].sav[0] = 0xFFFF,
        .syncCode[2].sav[1] = 0xFFFF,
        .syncCode[2].sav[2] = 0xFFFF,
        .syncCode[2].sav[3] = 0xFFFF,
        .syncCode[2].eav[0] = 0xFFFF,
        .syncCode[2].eav[1] = 0xFFFF,
        .syncCode[2].eav[2] = 0xFFFF,
        .syncCode[2].eav[3] = 0xFFFF,
        .syncCode[2].sab[0] = 0xFFFF,
        .syncCode[2].sab[1] = 0xFFFF,
        .syncCode[2].sab[2] = 0xFFFF,
        .syncCode[2].sab[3] = 0xFFFF,
        .syncCode[2].eab[0] = 0xFFFF,
        .syncCode[2].eab[1] = 0xFFFF,
        .syncCode[2].eab[2] = 0xFFFF,
        .syncCode[2].eab[3] = 0xFFFF,
    };

    TimproLvdsSyncCodeCtrl syncCodeMin = {
        .syncCode[0].sav[0] = 0,
        .syncCode[0].sav[1] = 0,
        .syncCode[0].sav[2] = 0,
        .syncCode[0].sav[3] = 0,
        .syncCode[0].eav[0] = 0,
        .syncCode[0].eav[1] = 0,
        .syncCode[0].eav[2] = 0,
        .syncCode[0].eav[3] = 0,
        .syncCode[0].sab[0] = 0,
        .syncCode[0].sab[1] = 0,
        .syncCode[0].sab[2] = 0,
        .syncCode[0].sab[3] = 0,
        .syncCode[0].eab[0] = 0,
        .syncCode[0].eab[1] = 0,
        .syncCode[0].eab[2] = 0,
        .syncCode[0].eab[3] = 0,
        .syncCode[1].sav[0] = 0,
        .syncCode[1].sav[1] = 0,
        .syncCode[1].sav[2] = 0,
        .syncCode[1].sav[3] = 0,
        .syncCode[1].eav[0] = 0,
        .syncCode[1].eav[1] = 0,
        .syncCode[1].eav[2] = 0,
        .syncCode[1].eav[3] = 0,
        .syncCode[1].sab[0] = 0,
        .syncCode[1].sab[1] = 0,
        .syncCode[1].sab[2] = 0,
        .syncCode[1].sab[3] = 0,
        .syncCode[1].eab[0] = 0,
        .syncCode[1].eab[1] = 0,
        .syncCode[1].eab[2] = 0,
        .syncCode[1].eab[3] = 0,
        .syncCode[2].sav[0] = 0,
        .syncCode[2].sav[1] = 0,
        .syncCode[2].sav[2] = 0,
        .syncCode[2].sav[3] = 0,
        .syncCode[2].eav[0] = 0,
        .syncCode[2].eav[1] = 0,
        .syncCode[2].eav[2] = 0,
        .syncCode[2].eav[3] = 0,
        .syncCode[2].sab[0] = 0,
        .syncCode[2].sab[1] = 0,
        .syncCode[2].sab[2] = 0,
        .syncCode[2].sab[3] = 0,
        .syncCode[2].eab[0] = 0,
        .syncCode[2].eab[1] = 0,
        .syncCode[2].eab[2] = 0,
        .syncCode[2].eab[3] = 0,
    };

    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) SAV01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].SAV0.SAV01.word,    ioPro.sen.lvds[0].SAV0.SAV01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) SAV02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].SAV0.SAV02.word,    ioPro.sen.lvds[0].SAV0.SAV02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) EAV01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].EAV0.EAV01.word,    ioPro.sen.lvds[0].EAV0.EAV01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) EAV02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].EAV0.EAV02.word,    ioPro.sen.lvds[0].EAV0.EAV02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) SAB01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].SAB0.SAB01.word,    ioPro.sen.lvds[0].SAB0.SAB01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) SAB02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].SAB0.SAB02.word,    ioPro.sen.lvds[0].SAB0.SAB02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) EAB01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].EAB0.EAB01.word,    ioPro.sen.lvds[0].EAB0.EAB01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) EAB02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].EAB0.EAB02.word,    ioPro.sen.lvds[0].EAB0.EAB02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) SAV11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].SAV1.SAV11.word,    ioPro.sen.lvds[0].SAV1.SAV11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) SAV12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].SAV1.SAV12.word,    ioPro.sen.lvds[0].SAV1.SAV12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) EAV11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].EAV1.EAV11.word,    ioPro.sen.lvds[0].EAV1.EAV11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) EAV12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].EAV1.EAV12.word,    ioPro.sen.lvds[0].EAV1.EAV12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) SAB11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].SAB1.SAB11.word,    ioPro.sen.lvds[0].SAB1.SAB11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) SAB12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].SAB1.SAB12.word,    ioPro.sen.lvds[0].SAB1.SAB12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) EAB11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].EAB1.EAB11.word,    ioPro.sen.lvds[0].EAB1.EAB11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) EAB12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].EAB1.EAB12.word,    ioPro.sen.lvds[0].EAB1.EAB12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) SAV21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].SAV2.SAV21.word,    ioPro.sen.lvds[0].SAV2.SAV21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) SAV22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].SAV2.SAV22.word,    ioPro.sen.lvds[0].SAV2.SAV22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) EAV21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].EAV2.EAV21.word,    ioPro.sen.lvds[0].EAV2.EAV21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) EAV22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].EAV2.EAV22.word,    ioPro.sen.lvds[0].EAV2.EAV22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) SAB21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].SAB2.SAB21.word,    ioPro.sen.lvds[0].SAB2.SAB21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) SAB22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].SAB2.SAB22.word,    ioPro.sen.lvds[0].SAB2.SAB22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) EAB21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].EAB2.EAB21.word,    ioPro.sen.lvds[0].EAB2.EAB21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(0) EAB22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].EAB2.EAB22.word,    ioPro.sen.lvds[0].EAB2.EAB22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) SAV01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].SAV0.SAV01.word,    ioPro.sen.lvds[1].SAV0.SAV01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) SAV02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].SAV0.SAV02.word,    ioPro.sen.lvds[1].SAV0.SAV02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) EAV01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].EAV0.EAV01.word,    ioPro.sen.lvds[1].EAV0.EAV01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) EAV02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].EAV0.EAV02.word,    ioPro.sen.lvds[1].EAV0.EAV02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) SAB01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].SAB0.SAB01.word,    ioPro.sen.lvds[1].SAB0.SAB01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) SAB02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].SAB0.SAB02.word,    ioPro.sen.lvds[1].SAB0.SAB02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) EAB01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].EAB0.EAB01.word,    ioPro.sen.lvds[1].EAB0.EAB01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) EAB02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].EAB0.EAB02.word,    ioPro.sen.lvds[1].EAB0.EAB02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) SAV11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].SAV1.SAV11.word,    ioPro.sen.lvds[1].SAV1.SAV11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) SAV12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].SAV1.SAV12.word,    ioPro.sen.lvds[1].SAV1.SAV12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) EAV11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].EAV1.EAV11.word,    ioPro.sen.lvds[1].EAV1.EAV11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) EAV12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].EAV1.EAV12.word,    ioPro.sen.lvds[1].EAV1.EAV12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) SAB11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].SAB1.SAB11.word,    ioPro.sen.lvds[1].SAB1.SAB11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) SAB12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].SAB1.SAB12.word,    ioPro.sen.lvds[1].SAB1.SAB12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) EAB11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].EAB1.EAB11.word,    ioPro.sen.lvds[1].EAB1.EAB11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) EAB12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].EAB1.EAB12.word,    ioPro.sen.lvds[1].EAB1.EAB12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) SAV21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].SAV2.SAV21.word,    ioPro.sen.lvds[1].SAV2.SAV21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) SAV22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].SAV2.SAV22.word,    ioPro.sen.lvds[1].SAV2.SAV22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) EAV21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].EAV2.EAV21.word,    ioPro.sen.lvds[1].EAV2.EAV21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) EAV22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].EAV2.EAV22.word,    ioPro.sen.lvds[1].EAV2.EAV22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) SAB21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].SAB2.SAB21.word,    ioPro.sen.lvds[1].SAB2.SAB21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) SAB22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].SAB2.SAB22.word,    ioPro.sen.lvds[1].SAB2.SAB22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) EAB21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].EAB2.EAB21.word,    ioPro.sen.lvds[1].EAB2.EAB21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(1) EAB22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].EAB2.EAB22.word,    ioPro.sen.lvds[1].EAB2.EAB22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) SAV01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].SAV0.SAV01.word,    ioPro.sen.lvds[2].SAV0.SAV01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) SAV02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].SAV0.SAV02.word,    ioPro.sen.lvds[2].SAV0.SAV02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) EAV01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].EAV0.EAV01.word,    ioPro.sen.lvds[2].EAV0.EAV01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) EAV02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].EAV0.EAV02.word,    ioPro.sen.lvds[2].EAV0.EAV02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) SAB01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].SAB0.SAB01.word,    ioPro.sen.lvds[2].SAB0.SAB01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) SAB02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].SAB0.SAB02.word,    ioPro.sen.lvds[2].SAB0.SAB02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) EAB01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].EAB0.EAB01.word,    ioPro.sen.lvds[2].EAB0.EAB01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) EAB02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].EAB0.EAB02.word,    ioPro.sen.lvds[2].EAB0.EAB02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) SAV11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].SAV1.SAV11.word,    ioPro.sen.lvds[2].SAV1.SAV11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) SAV12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].SAV1.SAV12.word,    ioPro.sen.lvds[2].SAV1.SAV12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) EAV11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].EAV1.EAV11.word,    ioPro.sen.lvds[2].EAV1.EAV11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) EAV12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].EAV1.EAV12.word,    ioPro.sen.lvds[2].EAV1.EAV12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) SAB11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].SAB1.SAB11.word,    ioPro.sen.lvds[2].SAB1.SAB11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) SAB12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].SAB1.SAB12.word,    ioPro.sen.lvds[2].SAB1.SAB12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) EAB11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].EAB1.EAB11.word,    ioPro.sen.lvds[2].EAB1.EAB11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) EAB12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].EAB1.EAB12.word,    ioPro.sen.lvds[2].EAB1.EAB12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) SAV21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].SAV2.SAV21.word,    ioPro.sen.lvds[2].SAV2.SAV21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) SAV22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].SAV2.SAV22.word,    ioPro.sen.lvds[2].SAV2.SAV22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) EAV21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].EAV2.EAV21.word,    ioPro.sen.lvds[2].EAV2.EAV21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) EAV22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].EAV2.EAV22.word,    ioPro.sen.lvds[2].EAV2.EAV22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) SAB21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].SAB2.SAB21.word,    ioPro.sen.lvds[2].SAB2.SAB21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) SAB22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].SAB2.SAB22.word,    ioPro.sen.lvds[2].SAB2.SAB22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) EAB21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].EAB2.EAB21.word,    ioPro.sen.lvds[2].EAB2.EAB21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(2) EAB22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].EAB2.EAB22.word,    ioPro.sen.lvds[2].EAB2.EAB22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) SAV01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].SAV0.SAV01.word,    ioPro.sen.lvds[3].SAV0.SAV01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) SAV02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].SAV0.SAV02.word,    ioPro.sen.lvds[3].SAV0.SAV02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) EAV01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].EAV0.EAV01.word,    ioPro.sen.lvds[3].EAV0.EAV01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) EAV02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].EAV0.EAV02.word,    ioPro.sen.lvds[3].EAV0.EAV02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) SAB01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].SAB0.SAB01.word,    ioPro.sen.lvds[3].SAB0.SAB01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) SAB02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].SAB0.SAB02.word,    ioPro.sen.lvds[3].SAB0.SAB02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) EAB01(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].EAB0.EAB01.word,    ioPro.sen.lvds[3].EAB0.EAB01.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) EAB02(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].EAB0.EAB02.word,    ioPro.sen.lvds[3].EAB0.EAB02.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) SAV11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].SAV1.SAV11.word,    ioPro.sen.lvds[3].SAV1.SAV11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) SAV12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].SAV1.SAV12.word,    ioPro.sen.lvds[3].SAV1.SAV12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) EAV11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].EAV1.EAV11.word,    ioPro.sen.lvds[3].EAV1.EAV11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) EAV12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].EAV1.EAV12.word,    ioPro.sen.lvds[3].EAV1.EAV12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) SAB11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].SAB1.SAB11.word,    ioPro.sen.lvds[3].SAB1.SAB11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) SAB12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].SAB1.SAB12.word,    ioPro.sen.lvds[3].SAB1.SAB12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) EAB11(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].EAB1.EAB11.word,    ioPro.sen.lvds[3].EAB1.EAB11.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) EAB12(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].EAB1.EAB12.word,    ioPro.sen.lvds[3].EAB1.EAB12.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) SAV21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].SAV2.SAV21.word,    ioPro.sen.lvds[3].SAV2.SAV21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) SAV22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].SAV2.SAV22.word,    ioPro.sen.lvds[3].SAV2.SAV22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) EAV21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].EAV2.EAV21.word,    ioPro.sen.lvds[3].EAV2.EAV21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) EAV22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].EAV2.EAV22.word,    ioPro.sen.lvds[3].EAV2.EAV22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) SAB21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].SAB2.SAB21.word,    ioPro.sen.lvds[3].SAB2.SAB21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) SAB22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].SAB2.SAB22.word,    ioPro.sen.lvds[3].SAB2.SAB22.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) EAB21(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].EAB2.EAB21.word,    ioPro.sen.lvds[3].EAB2.EAB21.word ));
//        Ddim_Print(("impro_senlvds_set_sync_code(3) EAB22(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].EAB2.EAB22.word,    ioPro.sen.lvds[3].EAB2.EAB22.word ));
        // Maximum value parameter
		ch = E_IM_PRO_LVDS_CH_3;
		self->priv->ercd = impro_senlvds_set_sync_code(self->priv->improSenlvds, ch, &syncCodeMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senlvds_set_sync_code() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_7(self->priv->imPro16Print, "max_para", ch, &syncCodeMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_LVDS_CH_0;
		self->priv->ercd = impro_senlvds_set_sync_code(self->priv->improSenlvds, ch, &syncCodeMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senlvds_set_sync_code() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_7(self->priv->imPro16Print, "min_para", ch, &syncCodeMin);
		}
    }
}

void ct_im_pro1_6_8(CtImPro16* self, const kuint32 idx)
{
    kuchar ch;
    TimproLvdsSyncMaskCtrl syncMaskMax = {
        .syncMask[0].msav[0] = 0xFFFF,
        .syncMask[0].msav[1] = 0xFFFF,
        .syncMask[0].msav[2] = 0xFFFF,
        .syncMask[0].msav[3] = 0xFFFF,
        .syncMask[0].meav[0] = 0xFFFF,
        .syncMask[0].meav[1] = 0xFFFF,
        .syncMask[0].meav[2] = 0xFFFF,
        .syncMask[0].meav[3] = 0xFFFF,
        .syncMask[0].msab[0] = 0xFFFF,
        .syncMask[0].msab[1] = 0xFFFF,
        .syncMask[0].msab[2] = 0xFFFF,
        .syncMask[0].msab[3] = 0xFFFF,
        .syncMask[0].meab[0] = 0xFFFF,
        .syncMask[0].meab[1] = 0xFFFF,
        .syncMask[0].meab[2] = 0xFFFF,
        .syncMask[0].meab[3] = 0xFFFF,
        .syncMask[1].msav[0] = 0xFFFF,
        .syncMask[1].msav[1] = 0xFFFF,
        .syncMask[1].msav[2] = 0xFFFF,
        .syncMask[1].msav[3] = 0xFFFF,
        .syncMask[1].meav[0] = 0xFFFF,
        .syncMask[1].meav[1] = 0xFFFF,
        .syncMask[1].meav[2] = 0xFFFF,
        .syncMask[1].meav[3] = 0xFFFF,
        .syncMask[1].msab[0] = 0xFFFF,
        .syncMask[1].msab[1] = 0xFFFF,
        .syncMask[1].msab[2] = 0xFFFF,
        .syncMask[1].msab[3] = 0xFFFF,
        .syncMask[1].meab[0] = 0xFFFF,
        .syncMask[1].meab[1] = 0xFFFF,
        .syncMask[1].meab[2] = 0xFFFF,
        .syncMask[1].meab[3] = 0xFFFF,
        .syncMask[2].msav[0] = 0xFFFF,
        .syncMask[2].msav[1] = 0xFFFF,
        .syncMask[2].msav[2] = 0xFFFF,
        .syncMask[2].msav[3] = 0xFFFF,
        .syncMask[2].meav[0] = 0xFFFF,
        .syncMask[2].meav[1] = 0xFFFF,
        .syncMask[2].meav[2] = 0xFFFF,
        .syncMask[2].meav[3] = 0xFFFF,
        .syncMask[2].msab[0] = 0xFFFF,
        .syncMask[2].msab[1] = 0xFFFF,
        .syncMask[2].msab[2] = 0xFFFF,
        .syncMask[2].msab[3] = 0xFFFF,
        .syncMask[2].meab[0] = 0xFFFF,
        .syncMask[2].meab[1] = 0xFFFF,
        .syncMask[2].meab[2] = 0xFFFF,
        .syncMask[2].meab[3] = 0xFFFF,
    };

    TimproLvdsSyncMaskCtrl syncMaskMin = {
        .syncMask[0].msav[0] = 0,
        .syncMask[0].msav[1] = 0,
        .syncMask[0].msav[2] = 0,
        .syncMask[0].msav[3] = 0,
        .syncMask[0].meav[0] = 0,
        .syncMask[0].meav[1] = 0,
        .syncMask[0].meav[2] = 0,
        .syncMask[0].meav[3] = 0,
        .syncMask[0].msab[0] = 0,
        .syncMask[0].msab[1] = 0,
        .syncMask[0].msab[2] = 0,
        .syncMask[0].msab[3] = 0,
        .syncMask[0].meab[0] = 0,
        .syncMask[0].meab[1] = 0,
        .syncMask[0].meab[2] = 0,
        .syncMask[0].meab[3] = 0,
        .syncMask[1].msav[0] = 0,
        .syncMask[1].msav[1] = 0,
        .syncMask[1].msav[2] = 0,
        .syncMask[1].msav[3] = 0,
        .syncMask[1].meav[0] = 0,
        .syncMask[1].meav[1] = 0,
        .syncMask[1].meav[2] = 0,
        .syncMask[1].meav[3] = 0,
        .syncMask[1].msab[0] = 0,
        .syncMask[1].msab[1] = 0,
        .syncMask[1].msab[2] = 0,
        .syncMask[1].msab[3] = 0,
        .syncMask[1].meab[0] = 0,
        .syncMask[1].meab[1] = 0,
        .syncMask[1].meab[2] = 0,
        .syncMask[1].meab[3] = 0,
        .syncMask[2].msav[0] = 0,
        .syncMask[2].msav[1] = 0,
        .syncMask[2].msav[2] = 0,
        .syncMask[2].msav[3] = 0,
        .syncMask[2].meav[0] = 0,
        .syncMask[2].meav[1] = 0,
        .syncMask[2].meav[2] = 0,
        .syncMask[2].meav[3] = 0,
        .syncMask[2].msab[0] = 0,
        .syncMask[2].msab[1] = 0,
        .syncMask[2].msab[2] = 0,
        .syncMask[2].msab[3] = 0,
        .syncMask[2].meab[0] = 0,
        .syncMask[2].meab[1] = 0,
        .syncMask[2].meab[2] = 0,
        .syncMask[2].meab[3] = 0,
    };

    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MSAV01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MSAV0.MSAV01.word,  ioPro.sen.lvds[0].MSAV0.MSAV01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MSAV02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MSAV0.MSAV02.word,  ioPro.sen.lvds[0].MSAV0.MSAV02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MEAV01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MEAV0.MEAV01.word,  ioPro.sen.lvds[0].MEAV0.MEAV01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MEAV02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MEAV0.MEAV02.word,  ioPro.sen.lvds[0].MEAV0.MEAV02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MSAB01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MSAB0.MSAB01.word,  ioPro.sen.lvds[0].MSAB0.MSAB01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MSAB02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MSAB0.MSAB02.word,  ioPro.sen.lvds[0].MSAB0.MSAB02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MEAB01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MEAB0.MEAB01.word,  ioPro.sen.lvds[0].MEAB0.MEAB01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MEAB02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MEAB0.MEAB02.word,  ioPro.sen.lvds[0].MEAB0.MEAB02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MSAV11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MSAV1.MSAV11.word,  ioPro.sen.lvds[0].MSAV1.MSAV11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MSAV12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MSAV1.MSAV12.word,  ioPro.sen.lvds[0].MSAV1.MSAV12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MEAV11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MEAV1.MEAV11.word,  ioPro.sen.lvds[0].MEAV1.MEAV11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MEAV12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MEAV1.MEAV12.word,  ioPro.sen.lvds[0].MEAV1.MEAV12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MSAB11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MSAB1.MSAB11.word,  ioPro.sen.lvds[0].MSAB1.MSAB11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MSAB12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MSAB1.MSAB12.word,  ioPro.sen.lvds[0].MSAB1.MSAB12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MEAB11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MEAB1.MEAB11.word,  ioPro.sen.lvds[0].MEAB1.MEAB11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MEAB12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MEAB1.MEAB12.word,  ioPro.sen.lvds[0].MEAB1.MEAB12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MSAV21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MSAV2.MSAV21.word,  ioPro.sen.lvds[0].MSAV2.MSAV21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MSAV22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MSAV2.MSAV22.word,  ioPro.sen.lvds[0].MSAV2.MSAV22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MEAV21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MEAV2.MEAV21.word,  ioPro.sen.lvds[0].MEAV2.MEAV21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MEAV22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MEAV2.MEAV22.word,  ioPro.sen.lvds[0].MEAV2.MEAV22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MSAB21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MSAB2.MSAB21.word,  ioPro.sen.lvds[0].MSAB2.MSAB21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MSAB22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MSAB2.MSAB22.word,  ioPro.sen.lvds[0].MSAB2.MSAB22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MEAB21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MEAB2.MEAB21.word,  ioPro.sen.lvds[0].MEAB2.MEAB21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(0) MEAB22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[0].MEAB2.MEAB22.word,  ioPro.sen.lvds[0].MEAB2.MEAB22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MSAV01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MSAV0.MSAV01.word,  ioPro.sen.lvds[1].MSAV0.MSAV01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MSAV02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MSAV0.MSAV02.word,  ioPro.sen.lvds[1].MSAV0.MSAV02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MEAV01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MEAV0.MEAV01.word,  ioPro.sen.lvds[1].MEAV0.MEAV01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MEAV02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MEAV0.MEAV02.word,  ioPro.sen.lvds[1].MEAV0.MEAV02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MSAB01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MSAB0.MSAB01.word,  ioPro.sen.lvds[1].MSAB0.MSAB01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MSAB02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MSAB0.MSAB02.word,  ioPro.sen.lvds[1].MSAB0.MSAB02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MEAB01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MEAB0.MEAB01.word,  ioPro.sen.lvds[1].MEAB0.MEAB01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MEAB02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MEAB0.MEAB02.word,  ioPro.sen.lvds[1].MEAB0.MEAB02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MSAV11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MSAV1.MSAV11.word,  ioPro.sen.lvds[1].MSAV1.MSAV11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MSAV12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MSAV1.MSAV12.word,  ioPro.sen.lvds[1].MSAV1.MSAV12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MEAV11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MEAV1.MEAV11.word,  ioPro.sen.lvds[1].MEAV1.MEAV11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MEAV12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MEAV1.MEAV12.word,  ioPro.sen.lvds[1].MEAV1.MEAV12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MSAB11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MSAB1.MSAB11.word,  ioPro.sen.lvds[1].MSAB1.MSAB11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MSAB12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MSAB1.MSAB12.word,  ioPro.sen.lvds[1].MSAB1.MSAB12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MEAB11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MEAB1.MEAB11.word,  ioPro.sen.lvds[1].MEAB1.MEAB11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MEAB12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MEAB1.MEAB12.word,  ioPro.sen.lvds[1].MEAB1.MEAB12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MSAV21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MSAV2.MSAV21.word,  ioPro.sen.lvds[1].MSAV2.MSAV21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MSAV22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MSAV2.MSAV22.word,  ioPro.sen.lvds[1].MSAV2.MSAV22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MEAV21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MEAV2.MEAV21.word,  ioPro.sen.lvds[1].MEAV2.MEAV21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MEAV22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MEAV2.MEAV22.word,  ioPro.sen.lvds[1].MEAV2.MEAV22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MSAB21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MSAB2.MSAB21.word,  ioPro.sen.lvds[1].MSAB2.MSAB21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MSAB22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MSAB2.MSAB22.word,  ioPro.sen.lvds[1].MSAB2.MSAB22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MEAB21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MEAB2.MEAB21.word,  ioPro.sen.lvds[1].MEAB2.MEAB21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(1) MEAB22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[1].MEAB2.MEAB22.word,  ioPro.sen.lvds[1].MEAB2.MEAB22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MSAV01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MSAV0.MSAV01.word,  ioPro.sen.lvds[2].MSAV0.MSAV01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MSAV02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MSAV0.MSAV02.word,  ioPro.sen.lvds[2].MSAV0.MSAV02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MEAV01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MEAV0.MEAV01.word,  ioPro.sen.lvds[2].MEAV0.MEAV01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MEAV02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MEAV0.MEAV02.word,  ioPro.sen.lvds[2].MEAV0.MEAV02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MSAB01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MSAB0.MSAB01.word,  ioPro.sen.lvds[2].MSAB0.MSAB01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MSAB02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MSAB0.MSAB02.word,  ioPro.sen.lvds[2].MSAB0.MSAB02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MEAB01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MEAB0.MEAB01.word,  ioPro.sen.lvds[2].MEAB0.MEAB01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MEAB02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MEAB0.MEAB02.word,  ioPro.sen.lvds[2].MEAB0.MEAB02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MSAV11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MSAV1.MSAV11.word,  ioPro.sen.lvds[2].MSAV1.MSAV11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MSAV12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MSAV1.MSAV12.word,  ioPro.sen.lvds[2].MSAV1.MSAV12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MEAV11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MEAV1.MEAV11.word,  ioPro.sen.lvds[2].MEAV1.MEAV11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MEAV12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MEAV1.MEAV12.word,  ioPro.sen.lvds[2].MEAV1.MEAV12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MSAB11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MSAB1.MSAB11.word,  ioPro.sen.lvds[2].MSAB1.MSAB11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MSAB12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MSAB1.MSAB12.word,  ioPro.sen.lvds[2].MSAB1.MSAB12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MEAB11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MEAB1.MEAB11.word,  ioPro.sen.lvds[2].MEAB1.MEAB11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MEAB12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MEAB1.MEAB12.word,  ioPro.sen.lvds[2].MEAB1.MEAB12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MSAV21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MSAV2.MSAV21.word,  ioPro.sen.lvds[2].MSAV2.MSAV21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MSAV22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MSAV2.MSAV22.word,  ioPro.sen.lvds[2].MSAV2.MSAV22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MEAV21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MEAV2.MEAV21.word,  ioPro.sen.lvds[2].MEAV2.MEAV21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MEAV22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MEAV2.MEAV22.word,  ioPro.sen.lvds[2].MEAV2.MEAV22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MSAB21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MSAB2.MSAB21.word,  ioPro.sen.lvds[2].MSAB2.MSAB21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MSAB22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MSAB2.MSAB22.word,  ioPro.sen.lvds[2].MSAB2.MSAB22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MEAB21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MEAB2.MEAB21.word,  ioPro.sen.lvds[2].MEAB2.MEAB21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(2) MEAB22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[2].MEAB2.MEAB22.word,  ioPro.sen.lvds[2].MEAB2.MEAB22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MSAV01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MSAV0.MSAV01.word,  ioPro.sen.lvds[3].MSAV0.MSAV01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MSAV02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MSAV0.MSAV02.word,  ioPro.sen.lvds[3].MSAV0.MSAV02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MEAV01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MEAV0.MEAV01.word,  ioPro.sen.lvds[3].MEAV0.MEAV01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MEAV02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MEAV0.MEAV02.word,  ioPro.sen.lvds[3].MEAV0.MEAV02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MSAB01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MSAB0.MSAB01.word,  ioPro.sen.lvds[3].MSAB0.MSAB01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MSAB02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MSAB0.MSAB02.word,  ioPro.sen.lvds[3].MSAB0.MSAB02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MEAB01(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MEAB0.MEAB01.word,  ioPro.sen.lvds[3].MEAB0.MEAB01.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MEAB02(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MEAB0.MEAB02.word,  ioPro.sen.lvds[3].MEAB0.MEAB02.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MSAV11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MSAV1.MSAV11.word,  ioPro.sen.lvds[3].MSAV1.MSAV11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MSAV12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MSAV1.MSAV12.word,  ioPro.sen.lvds[3].MSAV1.MSAV12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MEAV11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MEAV1.MEAV11.word,  ioPro.sen.lvds[3].MEAV1.MEAV11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MEAV12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MEAV1.MEAV12.word,  ioPro.sen.lvds[3].MEAV1.MEAV12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MSAB11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MSAB1.MSAB11.word,  ioPro.sen.lvds[3].MSAB1.MSAB11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MSAB12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MSAB1.MSAB12.word,  ioPro.sen.lvds[3].MSAB1.MSAB12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MEAB11(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MEAB1.MEAB11.word,  ioPro.sen.lvds[3].MEAB1.MEAB11.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MEAB12(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MEAB1.MEAB12.word,  ioPro.sen.lvds[3].MEAB1.MEAB12.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MSAV21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MSAV2.MSAV21.word,  ioPro.sen.lvds[3].MSAV2.MSAV21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MSAV22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MSAV2.MSAV22.word,  ioPro.sen.lvds[3].MSAV2.MSAV22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MEAV21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MEAV2.MEAV21.word,  ioPro.sen.lvds[3].MEAV2.MEAV21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MEAV22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MEAV2.MEAV22.word,  ioPro.sen.lvds[3].MEAV2.MEAV22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MSAB21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MSAB2.MSAB21.word,  ioPro.sen.lvds[3].MSAB2.MSAB21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MSAB22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MSAB2.MSAB22.word,  ioPro.sen.lvds[3].MSAB2.MSAB22.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MEAB21(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MEAB2.MEAB21.word,  ioPro.sen.lvds[3].MEAB2.MEAB21.word   ));
//        Ddim_Print(("impro_senlvds_set_sync_mask(3) MEAB22(0x%08lx, %llx)\n", (kulong)&ioPro.sen.lvds[3].MEAB2.MEAB22.word,  ioPro.sen.lvds[3].MEAB2.MEAB22.word   ));
        // Maximum value parameter
		ch = E_IM_PRO_LVDS_CH_3;
		self->priv->ercd = impro_senlvds_set_sync_mask(self->priv->improSenlvds, ch, &syncMaskMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senlvds_set_sync_mask() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_8(self->priv->imPro16Print, "max_para", ch, &syncMaskMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_LVDS_CH_0;
		self->priv->ercd = impro_senlvds_set_sync_mask(self->priv->improSenlvds, ch, &syncMaskMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senlvds_set_sync_mask() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_8(self->priv->imPro16Print, "min_para", ch, &syncMaskMin);
		}

    }
}

void ct_im_pro1_6_9(CtImPro16* self, const kuint32 idx)
{
    kuchar ch;
    TimproLvdsIntAddrCtrl intAddrMax = {
        .intAddr[0].solAddr = 8960,
        .intAddr[0].eolAddr = 8960,
        .intAddr[1].solAddr = 8960,
        .intAddr[1].eolAddr = 8960,
        .intAddr[2].solAddr = 8960,
        .intAddr[2].eolAddr = 8960,
    };

    TimproLvdsIntAddrCtrl intAddrMin = {
        .intAddr[0].solAddr = 0,
        .intAddr[0].eolAddr = 0,
        .intAddr[1].solAddr = 0,
        .intAddr[1].eolAddr = 0,
        .intAddr[2].solAddr = 0,
        .intAddr[2].eolAddr = 0,
    };

    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senlvds_set_int_adr(0) LVDSINTADR0(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].LVDSINTADR0.word,   ioPro.sen.lvds[0].LVDSINTADR0.word));
//        Ddim_Print(("impro_senlvds_set_int_adr(0) LVDSINTADR1(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].LVDSINTADR1.word,   ioPro.sen.lvds[0].LVDSINTADR1.word));
//        Ddim_Print(("impro_senlvds_set_int_adr(0) LVDSINTADR2(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[0].LVDSINTADR2.word,   ioPro.sen.lvds[0].LVDSINTADR2.word));
//        Ddim_Print(("impro_senlvds_set_int_adr(1) LVDSINTADR0(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].LVDSINTADR0.word,   ioPro.sen.lvds[1].LVDSINTADR0.word));
//        Ddim_Print(("impro_senlvds_set_int_adr(1) LVDSINTADR1(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].LVDSINTADR1.word,   ioPro.sen.lvds[1].LVDSINTADR1.word));
//        Ddim_Print(("impro_senlvds_set_int_adr(1) LVDSINTADR2(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[1].LVDSINTADR2.word,   ioPro.sen.lvds[1].LVDSINTADR2.word));
//        Ddim_Print(("impro_senlvds_set_int_adr(2) LVDSINTADR0(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].LVDSINTADR0.word,   ioPro.sen.lvds[2].LVDSINTADR0.word));
//        Ddim_Print(("impro_senlvds_set_int_adr(2) LVDSINTADR1(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].LVDSINTADR1.word,   ioPro.sen.lvds[2].LVDSINTADR1.word));
//        Ddim_Print(("impro_senlvds_set_int_adr(2) LVDSINTADR2(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[2].LVDSINTADR2.word,   ioPro.sen.lvds[2].LVDSINTADR2.word));
//        Ddim_Print(("impro_senlvds_set_int_adr(3) LVDSINTADR0(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].LVDSINTADR0.word,   ioPro.sen.lvds[3].LVDSINTADR0.word));
//        Ddim_Print(("impro_senlvds_set_int_adr(3) LVDSINTADR1(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].LVDSINTADR1.word,   ioPro.sen.lvds[3].LVDSINTADR1.word));
//        Ddim_Print(("impro_senlvds_set_int_adr(3) LVDSINTADR2(0x%08lx, %llx)\n",  (kulong)&ioPro.sen.lvds[3].LVDSINTADR2.word,   ioPro.sen.lvds[3].LVDSINTADR2.word));
        // Maximum value parameter
		ch = E_IM_PRO_LVDS_CH_3;
		self->priv->ercd = impro_senlvds_set_int_adr(self->priv->improSenlvds, ch, &intAddrMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_set_int_adr() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_9(self->priv->imPro16Print, "max_para", ch, &intAddrMax);
		}

		// Minimum value parameter
		ch = E_IM_PRO_LVDS_CH_0;
		self->priv->ercd = impro_senlvds_set_int_adr(self->priv->improSenlvds, ch, &intAddrMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senlvds_set_int_adr() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_6_print_9(self->priv->imPro16Print, "min_para", ch, &intAddrMin);
		}
    }
}
#endif //CO_CT_IM_PRO_DISABLE

CtImPro16* ct_im_pro1_6_new(void)
{
	CtImPro16* self = k_object_new_with_private(CT_TYPE_IM_PRO1_6, sizeof(CtImPro16Private));

	return self;
}

