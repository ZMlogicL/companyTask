/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 陈元
*@brief : CtImRawVarify
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimrawconfig.h"
#include "ctimrawvarify.h"
#include "imraw.h"
#include "ddimusercustom.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImRawVarify, ct_im_raw_varify)
#define CT_IM_RAW_VARIFY_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImRawVarifyPrivate, CT_TYPE_IM_RAW_VARIFY))


struct _CtImRawVarifyPrivate
{
	kint32	ret;
	ImRaw *imRaw;
	DdimUserCustom *ddimUserCustom;
};


/********
 * IMPL
 */
static void ct_im_raw_varify_constructor(CtImRawVarify *self)
{
	CtImRawVarifyPrivate *priv = CT_IM_RAW_VARIFY_GET_PRIVATE(self);

	priv->imRaw = im_raw_new();
	priv->ddimUserCustom = ddim_user_custom_new();
}

static void ct_im_raw_varify_destructor(CtImRawVarify *self)
{
	CtImRawVarifyPrivate *priv = CT_IM_RAW_VARIFY_GET_PRIVATE(self);

	if (priv->imRaw) {
		k_object_unref(priv->imRaw);
		priv->imRaw = NULL;
	}

	if (priv->ddimUserCustom) {
		k_object_unref(priv->ddimUserCustom);
		priv->ddimUserCustom = NULL;
	}
}


/********
 * PUBLIC
 */
kint32 ct_im_raw_varify_check_retval(CtImRawVarify* self, kint32 retval, kint32 correct)
{
	CtImRawVarifyPrivate *priv = CT_IM_RAW_VARIFY_GET_PRIVATE(self);

	if (retval != correct) {
		Ddim_Print(("Return Value Error !!!!!,  retval = 0x%x\n", retval));
		priv->ret = CtImRawConfig_NG;
	} else
	{
//		Ddim_Print(("Return Value OK\n"));
		priv->ret = CtImRawConfig_OK;
	}

	return priv->ret;
}

void ct_im_raw_varify_ret_print(CtImRawVarify* self, kint32 retVal)
{
	if (retVal) {
		Ddim_Print(("Return Value Error\n"));
	}
}

#if 0
#ifndef CO_DEBUG_ON_PC
// Clear
void ct_im_raw_config_clear(CtImRawVarify* self)
{
	kint32 i;
	kint32 byte = 64*1024*1024;
	volatile kuint32 *ptr;

	byte = 64*1024*1024;

	ptr = (volatile kuint32*)CtImRaw_ORG_ADDR;
	for (i = 0; i < byte; i+=4) {
		*ptr++ = 0;
	}

	ptr = (kuint32*)CtImRaw_ENC_ADDR;
	for (i = 0; i < byte; i+=4) {
		*ptr++ = 0;
	}

	ptr = (kuint32*)CtImRaw_DEC_ADDR;
	for (i = 0; i < byte; i+=4) {
		*ptr++ = 0;
	}
}
#endif	// CO_DEBUG_ON_PC
#endif

// Dump register
void ct_im_raw_varify_dump_reg(CtImRawVarify* self)
{
	CtImRawVarifyPrivate *priv = CT_IM_RAW_VARIFY_GET_PRIVATE(self);
	kint32 i;
	volatile kuint32 *pLut = (volatile kuint32*)&ioRaw.lut.lut1.word;
	volatile kuint32 temp;

	im_raw_on_pclk(priv->imRaw);

	Ddim_Print(("rctl0 = 0x%8lx\n", ioRaw.rctl0.word));
	Ddim_Print(("rctl1 = 0x%8lx\n", ioRaw.rctl1.word));
	Ddim_Print(("rinte = 0x%8lx\n", ioRaw.rinte.word));
	Ddim_Print(("rintf = 0x%8lx\n", ioRaw.rintf.word));
	Ddim_Print(("cond = 0x%8lx\n", ioRaw.cond.word));
	Ddim_Print(("hsize = 0x%8lx\n", ioRaw.hsize.word));
	Ddim_Print(("vsize = 0x%8lx\n", ioRaw.vsize.word));
	Ddim_Print(("dsize = 0x%8lx\n", ioRaw.dsize.word));
	Ddim_Print(("msa = 0x%8lx\n", ioRaw.msa.word));
	Ddim_Print(("mda = 0x%8lx\n", ioRaw.mda.word));
	Ddim_Print(("definit = 0x%8lx\n", ioRaw.definit.word));
	Ddim_Print(("clmt = 0x%8lx\n", ioRaw.clmt.word));
	Ddim_Print(("ccnt = 0x%8lx\n", ioRaw.ccnt.word));
	Ddim_Print(("mwaxctl = 0x%8lx\n", ioRaw.mraxctl.word));
	Ddim_Print(("mwaxctl = 0x%8lx\n", ioRaw.mwaxctl.word));
	Ddim_Print(("mraxsts = 0x%8lx\n", ioRaw.mraxsts.word));
	Ddim_Print(("mwaxsts = 0x%8lx\n", ioRaw.mwaxsts.word));

	Ddim_Print(("code0 = 0x%04X\n", ioRaw.code.code1.bit.code0));
	Ddim_Print(("code1 = 0x%04X\n", ioRaw.code.code1.bit.code1));
	Ddim_Print(("code2 = 0x%04X\n", ioRaw.code.code2.bit.code2));
	Ddim_Print(("code3 = 0x%04X\n", ioRaw.code.code2.bit.code3));
	Ddim_Print(("code4 = 0x%04X\n", ioRaw.code.code3.bit.code4));
	Ddim_Print(("code5 = 0x%04X\n", ioRaw.code.code3.bit.code5));
	Ddim_Print(("code6 = 0x%04X\n", ioRaw.code.code4.bit.code6));
	Ddim_Print(("code7 = 0x%04X\n", ioRaw.code.code4.bit.code7));
	Ddim_Print(("code8 = 0x%04X\n", ioRaw.code.code5.bit.code8));
	Ddim_Print(("code9 = 0x%04X\n", ioRaw.code.code5.bit.code9));
	Ddim_Print(("codea = 0x%04X\n", ioRaw.code.code6.bit.codea));
	Ddim_Print(("codeb = 0x%04X\n", ioRaw.code.code6.bit.codeb));
	Ddim_Print(("codec = 0x%04X\n", ioRaw.code.code7.bit.codec));
	Ddim_Print(("coded = 0x%04X\n", ioRaw.code.code7.bit.coded));
	Ddim_Print(("codee = 0x%04X\n", ioRaw.code.code8.bit.codee));

	Ddim_Print(("len0 = 0x%04X\n", ioRaw.len.len1.bit.len0));
	Ddim_Print(("len1 = 0x%04X\n", ioRaw.len.len1.bit.len1));
	Ddim_Print(("len2 = 0x%04X\n", ioRaw.len.len2.bit.len2));
	Ddim_Print(("len3 = 0x%04X\n", ioRaw.len.len2.bit.len3));
	Ddim_Print(("len4 = 0x%04X\n", ioRaw.len.len3.bit.len4));
	Ddim_Print(("len5 = 0x%04X\n", ioRaw.len.len3.bit.len5));
	Ddim_Print(("len6 = 0x%04X\n", ioRaw.len.len4.bit.len6));
	Ddim_Print(("len7 = 0x%04X\n", ioRaw.len.len4.bit.len7));
	Ddim_Print(("len8 = 0x%04X\n", ioRaw.len.len5.bit.len8));
	Ddim_Print(("len9 = 0x%04X\n", ioRaw.len.len5.bit.len9));
	Ddim_Print(("lena = 0x%04X\n", ioRaw.len.len6.bit.lena));
	Ddim_Print(("lenb = 0x%04X\n", ioRaw.len.len6.bit.lenb));
	Ddim_Print(("lenc = 0x%04X\n", ioRaw.len.len7.bit.lenc));
	Ddim_Print(("lend = 0x%04X\n", ioRaw.len.len7.bit.lend));
	Ddim_Print(("lene = 0x%04X\n", ioRaw.len.len8.bit.lene));

	Ddim_Print(("clmt = 0x%08lX\n", ioRaw.clmt.word));
	Ddim_Print(("ccnt = 0x%08lX\n", ioRaw.ccnt.word));

	Ddim_Print(("lut ADDR = 0x%08X\n", (kuint32)pLut));

	for (i = 0; i < 256; i+=4) {
		temp = *pLut++;
		Ddim_Print(("0x%08X ", (kuint32)temp));
		Ddim_Print(("lut[%3d-%3d] | 0x%2X | 0x%2X | 0x%2X | 0x%2X |\n", i, (i+3),
					(kuchar)(temp >> 0), (kuchar)(temp >> 8),
					(kuchar)(temp >> 16), (kuchar)(temp >> 24)));
	}

	im_raw_off_pclk(priv->imRaw);
}

// print out enc
void ct_im_raw_varify_enc_result(CtImRawVarify* self, EncResult encResult)
{
	if ((encResult.retval == D_IM_RAW_RETVAL_OK) && (encResult.cond == D_IM_RAW_COND_OK)) {
		if (encResult.bitMode == 0) {
			Ddim_Print(("Org data = %ld byte\n", (kulong)((kulong)encResult.width * 2 * (kulong)encResult.lines)));
		} else {
			Ddim_Print(("Org data = %ld byte\n", (kulong)((kulong)encResult.width * 1.5 * (kulong)encResult.lines)));
		}
		Ddim_Print(("Enc data = %d byte\n", encResult.byte));
	}
}

// verify raw
kint32 ct_im_raw_varify_raw(CtImRawVarify* self, RawData rawData)
{
	kint32 i;
	kuint16 mask = (rawData.bitsel == D_IM_RAW_BITSEL_EXCEPT_16_BIT) ? 0x3FFF : 0xFFFC;

	for (i = 0; i < rawData.byte; i+=2) {
		if ((mask & (*rawData.addr1)) != (mask & (*rawData.addr2))) {
			return CtImRawConfig_NG;
		}
		rawData.addr1++;
		rawData.addr2++;
	}

	return CtImRawConfig_OK;
}

kint32 ct_im_raw_varify_raw_12bit_pack(CtImRawVarify* self, kuint16* addr1, kuchar* addr2, kuint32 byte)
{
	kint32 i;
	kuchar tmp1;
	kuchar tmp2;
	kuint16 decVal;
	kuint16 orgVal;

	for (i = 0; i < byte; i += 3) {
		orgVal = (*addr1);
		tmp1 = ((*(addr2 + 1)) & 0x0F);
		tmp2 = (*addr2);
		decVal = (kuint16) tmp2 + ((kuint16) tmp1 << 8);

		if ((0x3FFF & orgVal) != (0x3FFF & decVal)) {
			Ddim_Print(("Org = %d, Dec = %d\n", orgVal, decVal));
			return CtImRawConfig_NG;
		}

		orgVal = (*(addr1 + 1));
		tmp1 = ((*(addr2 + 1)) >> 4);
		tmp2 = (*(addr2 + 2));
		decVal = ((kuint16) tmp2 << 4) + (kuint16) tmp1;

		if((0x3FFF & orgVal) != (0x3FFF & decVal)){
			Ddim_Print(("Org = %d, Dec = %d\n", orgVal, decVal));
			return CtImRawConfig_NG;
		}

		addr1 += 2;		// +2 Byte
		 addr2 += 3;		// +3 Byte
	}

	return CtImRawConfig_OK;
}

// verify 8bit data with lut
kint32 ct_im_raw_varify_data(CtImRawVarify* self, kuchar* addr1, kuchar* addr2, kuint32 byte)
{
	kint32 i;

	for (i = 0; i < byte; i++) {
		if ((*addr1) != (*addr2)) {
			return CtImRawConfig_NG;
		}
		addr1++;
		addr2++;
	}

	return CtImRawConfig_OK;
}

/*----------------------------------------------------------------------*/
/* Test code	     													*/
/*----------------------------------------------------------------------*/
// Init
kint32 ct_im_raw_varify_test_init(CtImRawVarify* self)
{
	CtImRawVarifyPrivate *priv = CT_IM_RAW_VARIFY_GET_PRIVATE(self);
	kint32 retval;

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_PCLOCK)
	Dd_Top_Set_CLKSTOP7_RAWCK(0);
	Dd_Top_Set_CLKSTOP7_RAWAX(0);
	Dd_Top_Set_CLKSTOP7_RAWAP(0);
#endif

	ddim_user_custom_dly_tsk(priv->ddimUserCustom, 1);

	ioRaw.rctl0.word = 1;	// Reset

	ddim_user_custom_dly_tsk(priv->ddimUserCustom, 1);

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_PCLOCK)
	Dd_Top_Set_CLKSTOP7_RAWAP(1);//TODO
	Dd_Top_Set_CLKSTOP7_RAWAX(1);
	Dd_Top_Set_CLKSTOP7_RAWCK(1);
#endif

#ifdef CO_DEBUG_ON_PC
	ioRaw.rctl1.bit.rtrg = 2;
#endif	//CO_DEBUG_ON_PC

	retval = im_raw_init(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(self, retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		Ddim_Print(("Im_RAW_Init() Error !!!!!,  retval = 0x%x\n", retval));
		return CtImRawConfig_NG;
	}

	// Dd_GIC_Ctrl(E_DD_GIC_INTID_RAW_INT, 1, D_DD_GIC_PRI30, 0);

	return CtImRawConfig_OK;
}

CtImRawVarify* ct_im_raw_varify_new(void)
{
	CtImRawVarify* self = k_object_new_with_private(CT_TYPE_IM_RAW_VARIFY, sizeof(CtImRawVarifyPrivate));

	return self;
}

