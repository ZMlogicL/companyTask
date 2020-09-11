/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro27
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsrosdc.h"
#include "ctimpro27.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro27, ct_im_pro2_7)
#define CT_IM_PRO2_7_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro27Private, CT_TYPE_IM_PRO2_7))


struct _CtImPro27Private
{
	ImproSrosdc *improSrosdc;
	ImPro27Print *imPro27Print;
	ImPro25Print *imPro25Print;
	kint32 ercd;
	E_IM_PRO_UNIT_NUM unitNo;
	kuchar ch;
};


/**********
 * IMPL
 */
static void ct_im_pro2_7_constructor(CtImPro27 *self)
{
	self->priv = CT_IM_PRO2_7_GET_PRIVATE(self);
	self->priv->improSrosdc = impro_srosdc_new();
	self->priv->imPro27Print = im_pro_2_7_print_new();
	self->priv->imPro25Print = im_pro_2_5_print_new();
	self->priv->ercd = 0;
	self->priv->unitNo = 0;
	self->priv->ch = 0;
}

static void ct_im_pro2_7_destructor(CtImPro27 *self)
{
	CtImPro27Private *priv = CT_IM_PRO2_7_GET_PRIVATE(self);

	if (priv->improSrosdc) {
		k_object_unref(priv->improSrosdc);
		priv->improSrosdc = NULL;
	}

	if (priv->imPro27Print) {
		k_object_unref(priv->imPro27Print);
		priv->imPro27Print = NULL;
	}

	if (priv->imPro25Print) {
		k_object_unref(priv->imPro25Print);
		priv->imPro25Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro2_7_0(CtImPro27* self, const kuint32 idx)
{
	EimproSdcGainTableSel sdcCtrlMax = ImproSrosdc_E_IM_PRO_SDC_GAIN_TABLE_SEL_1;
	EimproSdcGainTableSel sdcCtrlMin = ImproSrosdc_E_IM_PRO_SDC_GAIN_TABLE_SEL_0;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = E_IM_PRO_SDC_CH0; self->priv->ch < E_IM_PRO_SDC_CH1 + 1; self->priv->ch++) {//TODO
				self->priv->ercd = impro_srosdc_select_gain_table(self->priv->improSrosdc, self->priv->unitNo,
						self->priv->ch, sdcCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srosdc_select_gain_table(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_7_print_0(self->priv->imPro27Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, sdcCtrlMax);
				}

				self->priv->ercd = impro_srosdc_select_gain_table(self->priv->improSrosdc, self->priv->unitNo,
						self->priv->ch, sdcCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srosdc_select_gain_table(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_7_print_0(self->priv->imPro27Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, sdcCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_7_1(CtImPro27* self, const kuint32 idx)
{
    TimproSdcCtrlAfpb sdcCtrlMax = {
        .hPattern0[0] = 0xFFFFFFFFFFFFFFFF,
        .hPattern0[1] = 0xFFFFFFFFFFFFFFFF,
        .hPattern0[2] = 0xFFFFFFFFFFFFFFFF,
        .hPattern0[3] = 0xFFFFFFFFFFFFFFFF,
        .hPattern0[4] = 0xFFFFFFFFFFFFFFFF,
        .hPattern0[5] = 0xFFFFFFFFFFFFFFFF,
        .hPattern0[6] = 0xFFFFFFFFFFFFFFFF,
        .hPattern0[7] = 0xFFFFFFFFFFFFFFFF,
        .hPattern0[8] = 0xFFFFFFFFFFFFFFFF,
        .hPattern1[0] = 0xFFFFFFFFFFFFFFFF,
        .hPattern1[1] = 0xFFFFFFFFFFFFFFFF,
        .hPattern1[2] = 0xFFFFFFFFFFFFFFFF,
        .hPattern1[3] = 0xFFFFFFFFFFFFFFFF,
        .hPattern1[4] = 0xFFFFFFFFFFFFFFFF,
        .hPattern1[5] = 0xFFFFFFFFFFFFFFFF,
        .hPattern1[6] = 0xFFFFFFFFFFFFFFFF,
        .hPattern1[7] = 0xFFFFFFFFFFFFFFFF,
        .hPattern1[8] = 0xFFFFFFFFFFFFFFFF,
        .hPattern0ValidWidth[0] = 64,
        .hPattern0ValidWidth[1] = 64,
        .hPattern0ValidWidth[2] = 64,
        .hPattern0ValidWidth[3] = 64,
        .hPattern0ValidWidth[4] = 64,
        .hPattern0ValidWidth[5] = 64,
        .hPattern0ValidWidth[6] = 64,
        .hPattern0ValidWidth[7] = 64,
        .hPattern0ValidWidth[8] = 64,
        .hPattern1ValidWidth[0] = 64,
        .hPattern1ValidWidth[1] = 64,
        .hPattern1ValidWidth[2] = 64,
        .hPattern1ValidWidth[3] = 64,
        .hPattern1ValidWidth[4] = 64,
        .hPattern1ValidWidth[5] = 64,
        .hPattern1ValidWidth[6] = 64,
        .hPattern1ValidWidth[7] = 64,
        .hPattern1ValidWidth[8] = 64,
        .hPattern0R1ValidWidth[0] = 8191,
        .hPattern0R1ValidWidth[1] = 8191,
        .hPattern0R1ValidWidth[2] = 8191,
        .hPattern0R1ValidWidth[3] = 8191,
        .hPattern0R1ValidWidth[4] = 8191,
        .hPattern0R1ValidWidth[5] = 8191,
        .hPattern0R1ValidWidth[6] = 8191,
        .hPattern0R1ValidWidth[7] = 8191,
        .hPattern0R1ValidWidth[8] = 8191,
        .hPattern1R1ValidWidth[0] = 8191,
        .hPattern1R1ValidWidth[1] = 8191,
        .hPattern1R1ValidWidth[2] = 8191,
        .hPattern1R1ValidWidth[3] = 8191,
        .hPattern1R1ValidWidth[4] = 8191,
        .hPattern1R1ValidWidth[5] = 8191,
        .hPattern1R1ValidWidth[6] = 8191,
        .hPattern1R1ValidWidth[7] = 8191,
        .hPattern1R1ValidWidth[8] = 8191,
        .hPattern0R1InvalidWidth[0] = 8191,
        .hPattern0R1InvalidWidth[1] = 8191,
        .hPattern0R1InvalidWidth[2] = 8191,
        .hPattern0R1InvalidWidth[3] = 8191,
        .hPattern0R1InvalidWidth[4] = 8191,
        .hPattern0R1InvalidWidth[5] = 8191,
        .hPattern0R1InvalidWidth[6] = 8191,
        .hPattern0R1InvalidWidth[7] = 8191,
        .hPattern0R1InvalidWidth[8] = 8191,
        .hPattern1R1InvalidWidth[0] = 8191,
        .hPattern1R1InvalidWidth[1] = 8191,
        .hPattern1R1InvalidWidth[2] = 8191,
        .hPattern1R1InvalidWidth[3] = 8191,
        .hPattern1R1InvalidWidth[4] = 8191,
        .hPattern1R1InvalidWidth[5] = 8191,
        .hPattern1R1InvalidWidth[6] = 8191,
        .hPattern1R1InvalidWidth[7] = 8191,
        .hPattern1R1InvalidWidth[8] = 8191,
        .hPattern0R2ValidWidth[0] = 8191,
        .hPattern0R2ValidWidth[1] = 8191,
        .hPattern0R2ValidWidth[2] = 8191,
        .hPattern0R2ValidWidth[3] = 8191,
        .hPattern0R2ValidWidth[4] = 8191,
        .hPattern0R2ValidWidth[5] = 8191,
        .hPattern0R2ValidWidth[6] = 8191,
        .hPattern0R2ValidWidth[7] = 8191,
        .hPattern0R2ValidWidth[8] = 8191,
        .hPattern1R2ValidWidth[0] = 8191,
        .hPattern1R2ValidWidth[1] = 8191,
        .hPattern1R2ValidWidth[2] = 8191,
        .hPattern1R2ValidWidth[3] = 8191,
        .hPattern1R2ValidWidth[4] = 8191,
        .hPattern1R2ValidWidth[5] = 8191,
        .hPattern1R2ValidWidth[6] = 8191,
        .hPattern1R2ValidWidth[7] = 8191,
        .hPattern1R2ValidWidth[8] = 8191,
        .hPattern0R2InvalidWidth[0] = 8191,
        .hPattern0R2InvalidWidth[1] = 8191,
        .hPattern0R2InvalidWidth[2] = 8191,
        .hPattern0R2InvalidWidth[3] = 8191,
        .hPattern0R2InvalidWidth[4] = 8191,
        .hPattern0R2InvalidWidth[5] = 8191,
        .hPattern0R2InvalidWidth[6] = 8191,
        .hPattern0R2InvalidWidth[7] = 8191,
        .hPattern0R2InvalidWidth[8] = 8191,
        .hPattern1R2InvalidWidth[0] = 8191,
        .hPattern1R2InvalidWidth[1] = 8191,
        .hPattern1R2InvalidWidth[2] = 8191,
        .hPattern1R2InvalidWidth[3] = 8191,
        .hPattern1R2InvalidWidth[4] = 8191,
        .hPattern1R2InvalidWidth[5] = 8191,
        .hPattern1R2InvalidWidth[6] = 8191,
        .hPattern1R2InvalidWidth[7] = 8191,
        .hPattern1R2InvalidWidth[8] = 8191,
        .hColumnPattern0[0] = 8,
        .hColumnPattern0[1] = 8,
        .hColumnPattern0[2] = 8,
        .hColumnPattern0[3] = 8,
        .hColumnPattern0[4] = 8,
        .hColumnPattern0[5] = 8,
        .hColumnPattern0[6] = 8,
        .hColumnPattern0[7] = 8,
        .hColumnPattern0[8] = 8,
        .hColumnPattern0[9] = 8,
        .hColumnPattern0[10] = 8,
        .hColumnPattern0[11] = 8,
        .hColumnPattern0[12] = 8,
        .hColumnPattern0[13] = 8,
        .hColumnPattern0[14] = 8,
        .hColumnPattern0[15] = 8,
        .hColumnPattern0[16] = 8,
        .hColumnPattern0[17] = 8,
        .hColumnPattern0[18] = 8,
        .hColumnPattern0[19] = 8,
        .hColumnPattern0[20] = 8,
        .hColumnPattern0[21] = 8,
        .hColumnPattern0[22] = 8,
        .hColumnPattern0[23] = 8,
        .hColumnPattern0[24] = 8,
        .hColumnPattern0[25] = 8,
        .hColumnPattern0[26] = 8,
        .hColumnPattern0[27] = 8,
        .hColumnPattern0[28] = 8,
        .hColumnPattern0[29] = 8,
        .hColumnPattern0[30] = 8,
        .hColumnPattern0[31] = 8,
        .hColumnPattern0[32] = 8,
        .hColumnPattern0[33] = 8,
        .hColumnPattern0[34] = 8,
        .hColumnPattern0[35] = 8,
        .hColumnPattern0[36] = 8,
        .hColumnPattern0[37] = 8,
        .hColumnPattern0[38] = 8,
        .hColumnPattern0[39] = 8,
        .hColumnPattern0[40] = 8,
        .hColumnPattern0[41] = 8,
        .hColumnPattern0[42] = 8,
        .hColumnPattern0[43] = 8,
        .hColumnPattern0[44] = 8,
        .hColumnPattern0[45] = 8,
        .hColumnPattern0[46] = 8,
        .hColumnPattern0[47] = 8,
        .hColumnPattern0[48] = 8,
        .hColumnPattern0[49] = 8,
        .hColumnPattern0[50] = 8,
        .hColumnPattern0[51] = 8,
        .hColumnPattern0[52] = 8,
        .hColumnPattern0[53] = 8,
        .hColumnPattern0[54] = 8,
        .hColumnPattern0[55] = 8,
        .hColumnPattern0[56] = 8,
        .hColumnPattern0[57] = 8,
        .hColumnPattern0[58] = 8,
        .hColumnPattern0[59] = 8,
        .hColumnPattern0[60] = 8,
        .hColumnPattern0[61] = 8,
        .hColumnPattern0[62] = 8,
        .hColumnPattern0[63] = 8,
        .hColumnPattern1[0] = 8,
        .hColumnPattern1[1] = 8,
        .hColumnPattern1[2] = 8,
        .hColumnPattern1[3] = 8,
        .hColumnPattern1[4] = 8,
        .hColumnPattern1[5] = 8,
        .hColumnPattern1[6] = 8,
        .hColumnPattern1[7] = 8,
        .hColumnPattern1[8] = 8,
        .hColumnPattern1[9] = 8,
        .hColumnPattern1[10] = 8,
        .hColumnPattern1[11] = 8,
        .hColumnPattern1[12] = 8,
        .hColumnPattern1[13] = 8,
        .hColumnPattern1[14] = 8,
        .hColumnPattern1[15] = 8,
        .hColumnPattern1[16] = 8,
        .hColumnPattern1[17] = 8,
        .hColumnPattern1[18] = 8,
        .hColumnPattern1[19] = 8,
        .hColumnPattern1[20] = 8,
        .hColumnPattern1[21] = 8,
        .hColumnPattern1[22] = 8,
        .hColumnPattern1[23] = 8,
        .hColumnPattern1[24] = 8,
        .hColumnPattern1[25] = 8,
        .hColumnPattern1[26] = 8,
        .hColumnPattern1[27] = 8,
        .hColumnPattern1[28] = 8,
        .hColumnPattern1[29] = 8,
        .hColumnPattern1[30] = 8,
        .hColumnPattern1[31] = 8,
        .hColumnPattern1[32] = 8,
        .hColumnPattern1[33] = 8,
        .hColumnPattern1[34] = 8,
        .hColumnPattern1[35] = 8,
        .hColumnPattern1[36] = 8,
        .hColumnPattern1[37] = 8,
        .hColumnPattern1[38] = 8,
        .hColumnPattern1[39] = 8,
        .hColumnPattern1[40] = 8,
        .hColumnPattern1[41] = 8,
        .hColumnPattern1[42] = 8,
        .hColumnPattern1[43] = 8,
        .hColumnPattern1[44] = 8,
        .hColumnPattern1[45] = 8,
        .hColumnPattern1[46] = 8,
        .hColumnPattern1[47] = 8,
        .hColumnPattern1[48] = 8,
        .hColumnPattern1[49] = 8,
        .hColumnPattern1[50] = 8,
        .hColumnPattern1[51] = 8,
        .hColumnPattern1[52] = 8,
        .hColumnPattern1[53] = 8,
        .hColumnPattern1[54] = 8,
        .hColumnPattern1[55] = 8,
        .hColumnPattern1[56] = 8,
        .hColumnPattern1[57] = 8,
        .hColumnPattern1[58] = 8,
        .hColumnPattern1[59] = 8,
        .hColumnPattern1[60] = 8,
        .hColumnPattern1[61] = 8,
        .hColumnPattern1[62] = 8,
        .hColumnPattern1[63] = 8,
        .hColumnPatternValidWidth0 = 64,
        .hColumnPatternValidWidth1 = 64,
        .hColumnPattern1ValidWidth0 = 8191,
        .hColumnPattern1ValidWidth1 = 8191,
        .hColumnPattern2ValidWidth0 = 8191,
        .hColumnPattern2ValidWidth1 = 8191,
        .hColumnPattern1InvalidWidth0 = 8191,
        .hColumnPattern1InvalidWidth1 = 8191,
        .hColumnPattern2InvalidWidth0 = 8191,
        .hColumnPattern2InvalidWidth1 = 8191,
        .afpbGainCorrectionUThreshold = 4095,
        .afGainCorrectionLThreshold = 4095,
        .afpbNeighborPixelCorrectionLevel = 3,
    };

    TimproSdcCtrlAfpb sdcCtrlMin = {
        .hPattern0[0] = 0,
        .hPattern0[1] = 0,
        .hPattern0[2] = 0,
        .hPattern0[3] = 0,
        .hPattern0[4] = 0,
        .hPattern0[5] = 0,
        .hPattern0[6] = 0,
        .hPattern0[7] = 0,
        .hPattern0[8] = 0,
        .hPattern1[0] = 0,
        .hPattern1[1] = 0,
        .hPattern1[2] = 0,
        .hPattern1[3] = 0,
        .hPattern1[4] = 0,
        .hPattern1[5] = 0,
        .hPattern1[6] = 0,
        .hPattern1[7] = 0,
        .hPattern1[8] = 0,
        .hPattern0ValidWidth[0] = 0,
        .hPattern0ValidWidth[1] = 0,
        .hPattern0ValidWidth[2] = 0,
        .hPattern0ValidWidth[3] = 0,
        .hPattern0ValidWidth[4] = 0,
        .hPattern0ValidWidth[5] = 0,
        .hPattern0ValidWidth[6] = 0,
        .hPattern0ValidWidth[7] = 0,
        .hPattern0ValidWidth[8] = 0,
        .hPattern1ValidWidth[0] = 0,
        .hPattern1ValidWidth[1] = 0,
        .hPattern1ValidWidth[2] = 0,
        .hPattern1ValidWidth[3] = 0,
        .hPattern1ValidWidth[4] = 0,
        .hPattern1ValidWidth[5] = 0,
        .hPattern1ValidWidth[6] = 0,
        .hPattern1ValidWidth[7] = 0,
        .hPattern1ValidWidth[8] = 0,
        .hPattern0R1ValidWidth[0] = 0,
        .hPattern0R1ValidWidth[1] = 0,
        .hPattern0R1ValidWidth[2] = 0,
        .hPattern0R1ValidWidth[3] = 0,
        .hPattern0R1ValidWidth[4] = 0,
        .hPattern0R1ValidWidth[5] = 0,
        .hPattern0R1ValidWidth[6] = 0,
        .hPattern0R1ValidWidth[7] = 0,
        .hPattern0R1ValidWidth[8] = 0,
        .hPattern1R1ValidWidth[0] = 0,
        .hPattern1R1ValidWidth[1] = 0,
        .hPattern1R1ValidWidth[2] = 0,
        .hPattern1R1ValidWidth[3] = 0,
        .hPattern1R1ValidWidth[4] = 0,
        .hPattern1R1ValidWidth[5] = 0,
        .hPattern1R1ValidWidth[6] = 0,
        .hPattern1R1ValidWidth[7] = 0,
        .hPattern1R1ValidWidth[8] = 0,
        .hPattern0R1InvalidWidth[0] = 0,
        .hPattern0R1InvalidWidth[1] = 0,
        .hPattern0R1InvalidWidth[2] = 0,
        .hPattern0R1InvalidWidth[3] = 0,
        .hPattern0R1InvalidWidth[4] = 0,
        .hPattern0R1InvalidWidth[5] = 0,
        .hPattern0R1InvalidWidth[6] = 0,
        .hPattern0R1InvalidWidth[7] = 0,
        .hPattern0R1InvalidWidth[8] = 0,
        .hPattern1R1InvalidWidth[0] = 0,
        .hPattern1R1InvalidWidth[1] = 0,
        .hPattern1R1InvalidWidth[2] = 0,
        .hPattern1R1InvalidWidth[3] = 0,
        .hPattern1R1InvalidWidth[4] = 0,
        .hPattern1R1InvalidWidth[5] = 0,
        .hPattern1R1InvalidWidth[6] = 0,
        .hPattern1R1InvalidWidth[7] = 0,
        .hPattern1R1InvalidWidth[8] = 0,
        .hPattern0R2ValidWidth[0] = 0,
        .hPattern0R2ValidWidth[1] = 0,
        .hPattern0R2ValidWidth[2] = 0,
        .hPattern0R2ValidWidth[3] = 0,
        .hPattern0R2ValidWidth[4] = 0,
        .hPattern0R2ValidWidth[5] = 0,
        .hPattern0R2ValidWidth[6] = 0,
        .hPattern0R2ValidWidth[7] = 0,
        .hPattern0R2ValidWidth[8] = 0,
        .hPattern1R2ValidWidth[0] = 0,
        .hPattern1R2ValidWidth[1] = 0,
        .hPattern1R2ValidWidth[2] = 0,
        .hPattern1R2ValidWidth[3] = 0,
        .hPattern1R2ValidWidth[4] = 0,
        .hPattern1R2ValidWidth[5] = 0,
        .hPattern1R2ValidWidth[6] = 0,
        .hPattern1R2ValidWidth[7] = 0,
        .hPattern1R2ValidWidth[8] = 0,
        .hPattern0R2InvalidWidth[0] = 0,
        .hPattern0R2InvalidWidth[1] = 0,
        .hPattern0R2InvalidWidth[2] = 0,
        .hPattern0R2InvalidWidth[3] = 0,
        .hPattern0R2InvalidWidth[4] = 0,
        .hPattern0R2InvalidWidth[5] = 0,
        .hPattern0R2InvalidWidth[6] = 0,
        .hPattern0R2InvalidWidth[7] = 0,
        .hPattern0R2InvalidWidth[8] = 0,
        .hPattern1R2InvalidWidth[0] = 0,
        .hPattern1R2InvalidWidth[1] = 0,
        .hPattern1R2InvalidWidth[2] = 0,
        .hPattern1R2InvalidWidth[3] = 0,
        .hPattern1R2InvalidWidth[4] = 0,
        .hPattern1R2InvalidWidth[5] = 0,
        .hPattern1R2InvalidWidth[6] = 0,
        .hPattern1R2InvalidWidth[7] = 0,
        .hPattern1R2InvalidWidth[8] = 0,
        .hColumnPattern0[0] = 0,
        .hColumnPattern0[1] = 0,
        .hColumnPattern0[2] = 0,
        .hColumnPattern0[3] = 0,
        .hColumnPattern0[4] = 0,
        .hColumnPattern0[5] = 0,
        .hColumnPattern0[6] = 0,
        .hColumnPattern0[7] = 0,
        .hColumnPattern0[8] = 0,
        .hColumnPattern0[9] = 0,
        .hColumnPattern0[10] = 0,
        .hColumnPattern0[11] = 0,
        .hColumnPattern0[12] = 0,
        .hColumnPattern0[13] = 0,
        .hColumnPattern0[14] = 0,
        .hColumnPattern0[15] = 0,
        .hColumnPattern0[16] = 0,
        .hColumnPattern0[17] = 0,
        .hColumnPattern0[18] = 0,
        .hColumnPattern0[19] = 0,
        .hColumnPattern0[20] = 0,
        .hColumnPattern0[21] = 0,
        .hColumnPattern0[22] = 0,
        .hColumnPattern0[23] = 0,
        .hColumnPattern0[24] = 0,
        .hColumnPattern0[25] = 0,
        .hColumnPattern0[26] = 0,
        .hColumnPattern0[27] = 0,
        .hColumnPattern0[28] = 0,
        .hColumnPattern0[29] = 0,
        .hColumnPattern0[30] = 0,
        .hColumnPattern0[31] = 0,
        .hColumnPattern0[32] = 0,
        .hColumnPattern0[33] = 0,
        .hColumnPattern0[34] = 0,
        .hColumnPattern0[35] = 0,
        .hColumnPattern0[36] = 0,
        .hColumnPattern0[37] = 0,
        .hColumnPattern0[38] = 0,
        .hColumnPattern0[39] = 0,
        .hColumnPattern0[40] = 0,
        .hColumnPattern0[41] = 0,
        .hColumnPattern0[42] = 0,
        .hColumnPattern0[43] = 0,
        .hColumnPattern0[44] = 0,
        .hColumnPattern0[45] = 0,
        .hColumnPattern0[46] = 0,
        .hColumnPattern0[47] = 0,
        .hColumnPattern0[48] = 0,
        .hColumnPattern0[49] = 0,
        .hColumnPattern0[50] = 0,
        .hColumnPattern0[51] = 0,
        .hColumnPattern0[52] = 0,
        .hColumnPattern0[53] = 0,
        .hColumnPattern0[54] = 0,
        .hColumnPattern0[55] = 0,
        .hColumnPattern0[56] = 0,
        .hColumnPattern0[57] = 0,
        .hColumnPattern0[58] = 0,
        .hColumnPattern0[59] = 0,
        .hColumnPattern0[60] = 0,
        .hColumnPattern0[61] = 0,
        .hColumnPattern0[62] = 0,
        .hColumnPattern0[63] = 0,
        .hColumnPattern1[0] = 0,
        .hColumnPattern1[1] = 0,
        .hColumnPattern1[2] = 0,
        .hColumnPattern1[3] = 0,
        .hColumnPattern1[4] = 0,
        .hColumnPattern1[5] = 0,
        .hColumnPattern1[6] = 0,
        .hColumnPattern1[7] = 0,
        .hColumnPattern1[8] = 0,
        .hColumnPattern1[9] = 0,
        .hColumnPattern1[10] = 0,
        .hColumnPattern1[11] = 0,
        .hColumnPattern1[12] = 0,
        .hColumnPattern1[13] = 0,
        .hColumnPattern1[14] = 0,
        .hColumnPattern1[15] = 0,
        .hColumnPattern1[16] = 0,
        .hColumnPattern1[17] = 0,
        .hColumnPattern1[18] = 0,
        .hColumnPattern1[19] = 0,
        .hColumnPattern1[20] = 0,
        .hColumnPattern1[21] = 0,
        .hColumnPattern1[22] = 0,
        .hColumnPattern1[23] = 0,
        .hColumnPattern1[24] = 0,
        .hColumnPattern1[25] = 0,
        .hColumnPattern1[26] = 0,
        .hColumnPattern1[27] = 0,
        .hColumnPattern1[28] = 0,
        .hColumnPattern1[29] = 0,
        .hColumnPattern1[30] = 0,
        .hColumnPattern1[31] = 0,
        .hColumnPattern1[32] = 0,
        .hColumnPattern1[33] = 0,
        .hColumnPattern1[34] = 0,
        .hColumnPattern1[35] = 0,
        .hColumnPattern1[36] = 0,
        .hColumnPattern1[37] = 0,
        .hColumnPattern1[38] = 0,
        .hColumnPattern1[39] = 0,
        .hColumnPattern1[40] = 0,
        .hColumnPattern1[41] = 0,
        .hColumnPattern1[42] = 0,
        .hColumnPattern1[43] = 0,
        .hColumnPattern1[44] = 0,
        .hColumnPattern1[45] = 0,
        .hColumnPattern1[46] = 0,
        .hColumnPattern1[47] = 0,
        .hColumnPattern1[48] = 0,
        .hColumnPattern1[49] = 0,
        .hColumnPattern1[50] = 0,
        .hColumnPattern1[51] = 0,
        .hColumnPattern1[52] = 0,
        .hColumnPattern1[53] = 0,
        .hColumnPattern1[54] = 0,
        .hColumnPattern1[55] = 0,
        .hColumnPattern1[56] = 0,
        .hColumnPattern1[57] = 0,
        .hColumnPattern1[58] = 0,
        .hColumnPattern1[59] = 0,
        .hColumnPattern1[60] = 0,
        .hColumnPattern1[61] = 0,
        .hColumnPattern1[62] = 0,
        .hColumnPattern1[63] = 0,
        .hColumnPatternValidWidth0 = 0,
        .hColumnPatternValidWidth1 = 0,
        .hColumnPattern1ValidWidth0 = 0,
        .hColumnPattern1ValidWidth1 = 0,
        .hColumnPattern2ValidWidth0 = 0,
        .hColumnPattern2ValidWidth1 = 0,
        .hColumnPattern1InvalidWidth0 = 0,
        .hColumnPattern1InvalidWidth1 = 0,
        .hColumnPattern2InvalidWidth0 = 0,
        .hColumnPattern2InvalidWidth1 = 0,
        .afpbGainCorrectionUThreshold = 0,
        .afGainCorrectionLThreshold = 0,
        .afpbNeighborPixelCorrectionLevel = 0,
    };

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = E_IM_PRO_SDC_CH0; self->priv->ch < E_IM_PRO_SDC_CH1 + 1; self->priv->ch++) {//TODO
				self->priv->ercd = impro_srosdc_ctrl_afpb(self->priv->improSrosdc, self->priv->unitNo,
						self->priv->ch, &sdcCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srosdc_ctrl_afpb(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_7_print_1(self->priv->imPro27Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &sdcCtrlMax);
				}

				self->priv->ercd = impro_srosdc_ctrl_afpb(self->priv->improSrosdc, self->priv->unitNo,
						self->priv->ch, &sdcCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srosdc_ctrl_afpb(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_7_print_1(self->priv->imPro27Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &sdcCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_7_2(CtImPro27* self, const kuint32 idx)
{
	kint32 cmpErcd;
	kuchar tblSel;
	TimproSdcGainTable sdcCtrlMax;
	TimproSdcGainTable sdcCtrlMin;
	const T_IM_PRO_SRO_SDC_INFO* sdcInfo;//TODO

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = E_IM_PRO_SDC_CH0; self->priv->ch < E_IM_PRO_SDC_CH1 + 1; self->priv->ch++) {
				for (tblSel = ImproSrosdc_E_IM_PRO_SDC_GAIN_TABLE_SEL_0; tblSel < ImproSrosdc_E_IM_PRO_SDC_GAIN_TABLE_SEL_1 + 1;
						tblSel++) {
					memset(sdcCtrlMax.gainTable, 255, sizeof(sdcCtrlMax.gainTable));
					memset(sdcCtrlMin.gainTable, 0, sizeof(sdcCtrlMax.gainTable));

					self->priv->ercd = impro_srosdc_set_gain_table(self->priv->improSrosdc, self->priv->unitNo,
							self->priv->ch, tblSel, &sdcCtrlMax);
					im_pro_comm_get_sdc_reg_info(self->priv->improSrosdc, self->priv->unitNo, self->priv->ch,
							&sdcInfo);
					if (self->priv->ercd == DdimUserCustom_E_OK) {
						cmpErcd = memcmp((void*) &sdcInfo->tblRegPtr[tblSel].hword, sdcCtrlMax.gainTable,
								sizeof(sdcCtrlMax.gainTable));
					} else {
						cmpErcd = -1;
					}

					if (self->priv->ercd != DdimUserCustom_E_OK) {
						Ddim_Print(
								("impro_srosdc_set_gain_table(%u %u %u) max_para Error self->priv->ercd=0x%x\n",
										self->priv->unitNo, self->priv->ch, tblSel, self->priv->ercd));
					} else {
						//pgr0539
						im_pro_2_7_print_2(self->priv->imPro27Print, "max_para", self->priv->unitNo,
								self->priv->ch, tblSel, self->priv->ercd, &sdcCtrlMax, cmpErcd);
					}

					self->priv->ercd = impro_srosdc_set_gain_table(self->priv->improSrosdc, self->priv->unitNo,
							self->priv->ch, tblSel, &sdcCtrlMin);
					if (self->priv->ercd != DdimUserCustom_E_OK) {
						Ddim_Print(
								("impro_srosdc_set_gain_table(%u %u %u) min_para Error self->priv->ercd=0x%x\n",
										self->priv->unitNo, self->priv->ch, tblSel, tblSel));
					} else {
						//pgr0539
						im_pro_2_7_print_2(self->priv->imPro27Print, "min_para", self->priv->unitNo,
								self->priv->ch, tblSel, self->priv->ercd, &sdcCtrlMin, cmpErcd);
					}
                }
            }
        }
    }
}

void ct_im_pro2_7_3(CtImPro27* self, const kuint32 idx)
{
	kuchar paenTrg;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = E_IM_PRO_SDC_CH0; self->priv->ch < E_IM_PRO_SDC_CH1 + 1; self->priv->ch++) {
				for (paenTrg = 0; paenTrg < 2 + 1; paenTrg++) {
					self->priv->ercd = impro_srosdc_set_paen(self->priv->improSrosdc, self->priv->unitNo,
							self->priv->ch, paenTrg);
					im_pro_2_5_print_9(self->priv->imPro25Print, self->priv->unitNo, self->priv->ch,
							self->priv->ercd, paenTrg);
				}
            }
        }
    }
}

void ct_im_pro2_7_4(CtImPro27* self, const kuint32 idx)
{
	const TimproRdmaSdcAddr* sdcCtrl;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = E_IM_PRO_SDC_CH0; self->priv->ch < E_IM_PRO_SDC_CH1 + 1; self->priv->ch++) {
				self->priv->ercd = impro_srosdc_get_rdma_addr_sdc_cntl(self->priv->improSrosdc, self->priv->unitNo,
						self->priv->ch, &sdcCtrl);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srosdc_get_rdma_addr_sdc_cntl(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_7_print_4(self->priv->imPro27Print, "", self->priv->unitNo, self->priv->ch,
							self->priv->ercd, &sdcCtrl);
				}
			}
        }
    }
}

void ct_im_pro2_7_5(CtImPro27* self, const kuint32 idx)
{
	kuchar tblSel;
	const TimproRdmaSdcGainTblAddr* sdcCtrl;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = E_IM_PRO_SDC_CH0; self->priv->ch < E_IM_PRO_SDC_CH1 + 1; self->priv->ch++) {
				for (tblSel = ImproSrosdc_E_IM_PRO_SDC_GAIN_TABLE_SEL_0; tblSel < ImproSrosdc_E_IM_PRO_SDC_GAIN_TABLE_SEL_1 + 1;
						tblSel++) {
					self->priv->ercd = impro_srosdc_get_rdma_addr_sdc_gain_tbl(self->priv->improSrosdc,
							self->priv->unitNo, self->priv->ch, tblSel, &sdcCtrl);
					if (self->priv->ercd != DdimUserCustom_E_OK) {
						Ddim_Print(
								("impro_srosdc_get_rdma_addr_sdc_gain_tbl(%u %u %u) max_para Error self->priv->ercd=0x%x\n",
										self->priv->unitNo, self->priv->ch, tblSel, self->priv->ercd));
					} else {
						im_pro_2_7_print_5(self->priv->imPro27Print, "", self->priv->unitNo, self->priv->ch,
								tblSel, self->priv->ercd, &sdcCtrl);
					}
                }
            }
        }
    }
}
#endif  //CO_CT_IM_PRO_DISABLE

CtImPro27* ct_im_pro2_7_new(void)
{
	CtImPro27* self = k_object_new_with_private(CT_TYPE_IM_PRO2_7, sizeof(CtImPro27Private));

	return self;
}

