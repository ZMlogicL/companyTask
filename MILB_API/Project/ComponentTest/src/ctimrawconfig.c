/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈元
*@brief : CtImRawConfig
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimrawconfig.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImRawConfig, ct_im_raw_config)
#define CT_IM_RAW_CONFIG_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImRawConfigPrivate, CT_TYPE_IM_RAW_CONFIG))


struct _CtImRawConfigPrivate
{
	T_IM_RAW_CTRL_CODE_TBL codeTbl;
	T_IM_RAW_CTRL_PARAM rawParam;
	kuchar userLut[256];
	kuint32 encByte;
};


/********
 * DECLS
 */
static void sampleRaw_cb(kuint32 cond);


/********
 * IMPN
 */
static void ct_im_raw_config_constructor(CtImRawConfig *self)
{
//	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_GET_PRIVATE(self);
}

static void ct_im_raw_config_destructor(CtImRawConfig *self)
{
//	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_GET_PRIVATE(self);
}

// callback
static void sampleRaw_cb(kuint32 cond)
{
	Ddim_Print(("Int : cond = %d\n", cond));
}


/********
 * PUBLIC
 */
T_IM_RAW_CTRL_CODE_TBL ct_im_raw_config_get_code_tbl(CtImRawConfig *self)
{
	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_GET_PRIVATE(self);

	return priv->codeTbl;
}

T_IM_RAW_CTRL_PARAM	ct_im_raw_config_get_raw_param(CtImRawConfig *self)
{
	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_GET_PRIVATE(self);

	return priv->rawParam;
}

kuchar	ct_im_raw_config_get_user_lut(CtImRawConfig *self)
{
	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_GET_PRIVATE(self);

	return priv->userLut;
}

kuint32 ct_im_raw_config_get_enc_byte(CtImRawConfig *self)
{
	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_GET_PRIVATE(self);

	return priv->encByte;
}

// User setting Huffman table
void ct_im_raw_config_set_huff_tbl(CtImRawConfig* self)
{
	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_PRIVATE(self);

	priv->codeTbl.code[0] = 0xD000;
	priv->codeTbl.code[1] = 0xD800;
	priv->codeTbl.code[2] = 0xF000;
	priv->codeTbl.code[3] = 0xC000;
	priv->codeTbl.code[4] = 0x0000;
	priv->codeTbl.code[5] = 0x8000;
	priv->codeTbl.code[6] = 0x4000;
	priv->codeTbl.code[7] = 0x2000;
	priv->codeTbl.code[8] = 0xE000;
	priv->codeTbl.code[9] = 0xD400;
	priv->codeTbl.code[10] = 0xD600;
	priv->codeTbl.code[11] = 0xD700;
	priv->codeTbl.code[12] = 0xD780;
	priv->codeTbl.code[13] = 0xD7E0;
	priv->codeTbl.code[14] = 0xD7C0;

	priv->codeTbl.codeLength[0] = 6;
	priv->codeTbl.codeLength[1] = 5;
	priv->codeTbl.codeLength[2] = 4;
	priv->codeTbl.codeLength[3] = 4;
	priv->codeTbl.codeLength[4] = 3;
	priv->codeTbl.codeLength[5] = 2;
	priv->codeTbl.codeLength[6] = 2;
	priv->codeTbl.codeLength[7] = 3;
	priv->codeTbl.codeLength[8] = 4;
	priv->codeTbl.codeLength[9] = 7;
	priv->codeTbl.codeLength[10] = 8;
	priv->codeTbl.codeLength[11] = 9;
	priv->codeTbl.codeLength[12] = 10;
	priv->codeTbl.codeLength[13] = 11;
	priv->codeTbl.codeLength[14] = 11;
}

// init global param
void ct_im_raw_config_init_param(CtImRawConfig* self)
{
	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_PRIVATE(self);

	// init rawParam
	priv->rawParam.srcAddr = CtImRaw_ORG_ADDR;
	priv->rawParam.dstAddr = CtImRaw_ENC_ADDR;
	priv->rawParam.diffFixedValue = 0;
	priv->rawParam.byteStuffing = D_IM_RAW_OFF;
	priv->rawParam.dataFormat = D_IM_RAW_RFMT_14_OR_16_BIT;
	priv->rawParam.callback = sampleRaw_cb;
	priv->rawParam.mcuSize = D_IM_RAW_DEFFC_MCU_2x2;
	priv->rawParam.bitSelect = D_IM_RAW_BITSEL_EXCEPT_16_BIT;
	priv->rawParam.width = 0;
	priv->rawParam.lines = 0;
	priv->rawParam.diffMode = D_IM_RAW_DEFOP_DIFF_PREV_VALUE;
	priv->rawParam.lut = NULL;
	priv->rawParam.dataSize = 0;
	// mraxctl
	priv->rawParam.axiParam.rCacheType = D_IM_RAW_ON_CACHE_RW_WRITE_BACK;
	// mraxctl
	priv->rawParam.axiParam.rProtectionType = D_IM_RAW_D_SEC_NORMAL_ACCESS;
	// mwaxctl
	priv->rawParam.axiParam.wCacheType = D_IM_RAW_ON_CACHE_RW_WRITE_BACK;
	// mwaxctl
	priv->rawParam.axiParam.wProtectionType = D_IM_RAW_D_SEC_NORMAL_ACCESS;
	// init codeTbl.code
	priv->codeTbl.code[0] = 0x6000;
	priv->codeTbl.code[1] = 0x7000;
	priv->codeTbl.code[2] = 0x0000;
	priv->codeTbl.code[3] = 0x2000;
	priv->codeTbl.code[4] = 0x4000;
	priv->codeTbl.code[5] = 0x8000;
	priv->codeTbl.code[6] = 0x9000;
	priv->codeTbl.code[7] = 0xA000;
	priv->codeTbl.code[8] = 0xB000;
	priv->codeTbl.code[9] = 0xC000;
	priv->codeTbl.code[10] = 0xD000;
	priv->codeTbl.code[11] = 0xE000;
	priv->codeTbl.code[12] = 0xE800;
	priv->codeTbl.code[13] = 0xF000;
	priv->codeTbl.code[14] = 0xF800;
	// init codeTbl.codeLength
	priv->codeTbl.codeLength[0] = 4;
	priv->codeTbl.codeLength[1] = 4;
	priv->codeTbl.codeLength[2] = 3;
	priv->codeTbl.codeLength[3] = 3;
	priv->codeTbl.codeLength[4] = 3;
	priv->codeTbl.codeLength[5] = 4;
	priv->codeTbl.codeLength[6] = 4;
	priv->codeTbl.codeLength[7] = 4;
	priv->codeTbl.codeLength[8] = 4;
	priv->codeTbl.codeLength[9] = 4;
	priv->codeTbl.codeLength[10] = 4;
	priv->codeTbl.codeLength[11] = 5;
	priv->codeTbl.codeLength[12] = 5;
	priv->codeTbl.codeLength[13] = 5;
	priv->codeTbl.codeLength[14] = 5;
}

// setup invalid code
void ct_im_raw_config_invalid_code(CtImRawConfig* self)
{
	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_PRIVATE(self);

	priv->codeTbl.code[0] = 0xFFFC;
	priv->codeTbl.code[1] = 0xFFFC;
	priv->codeTbl.code[2] = 0xFFFC;
	priv->codeTbl.code[3] = 0xFFFC;
	priv->codeTbl.code[4] = 0xFFFC;
	priv->codeTbl.code[5] = 0xFFFC;
	priv->codeTbl.code[6] = 0xFFFC;
	priv->codeTbl.code[7] = 0xFFFC;
	priv->codeTbl.code[8] = 0xFFFC;
	priv->codeTbl.code[9] = 0xFFFC;
	priv->codeTbl.code[10] = 0xFFFC;
	priv->codeTbl.code[11] = 0xFFFC;
	priv->codeTbl.code[12] = 0xFFFC;
	priv->codeTbl.code[13] = 0xFFFC;
	priv->codeTbl.code[14] = 0xFFFC;

	priv->codeTbl.codeLength[0] = 14;
	priv->codeTbl.codeLength[1] = 14;
	priv->codeTbl.codeLength[2] = 14;
	priv->codeTbl.codeLength[3] = 14;
	priv->codeTbl.codeLength[4] = 14;
	priv->codeTbl.codeLength[5] = 14;
	priv->codeTbl.codeLength[6] = 14;
	priv->codeTbl.codeLength[7] = 14;
	priv->codeTbl.codeLength[8] = 14;
	priv->codeTbl.codeLength[9] = 14;
	priv->codeTbl.codeLength[10] = 14;
	priv->codeTbl.codeLength[11] = 14;
	priv->codeTbl.codeLength[12] = 14;
	priv->codeTbl.codeLength[13] = 14;
	priv->codeTbl.codeLength[14] = 14;
}

// setup 8bit code table
void ct_im_raw_config_8bit_code_table(CtImRawConfig* self)
{
	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_PRIVATE(self);

	priv->codeTbl.code[0] = 0x6000;
	priv->codeTbl.code[1] = 0x4000;
	priv->codeTbl.code[2] = 0x0000;
	priv->codeTbl.code[3] = 0x8000;
	priv->codeTbl.code[4] = 0xc000;
	priv->codeTbl.code[5] = 0x2000;
	priv->codeTbl.code[6] = 0x3000;
	priv->codeTbl.code[7] = 0x3800;
	priv->codeTbl.code[8] = 0x3c00;
	priv->codeTbl.code[9] = 0x3ec0;
	priv->codeTbl.code[10] = 0x3e80;
	priv->codeTbl.code[11] = 0x3e40;
	priv->codeTbl.code[12] = 0x3e00;
	priv->codeTbl.code[13] = 0x3f80;
	priv->codeTbl.code[14] = 0x3f00;

	priv->codeTbl.codeLength[0] = 3;
	priv->codeTbl.codeLength[1] = 3;
	priv->codeTbl.codeLength[2] = 3;
	priv->codeTbl.codeLength[3] = 2;
	priv->codeTbl.codeLength[4] = 2;
	priv->codeTbl.codeLength[5] = 4;
	priv->codeTbl.codeLength[6] = 5;
	priv->codeTbl.codeLength[7] = 6;
	priv->codeTbl.codeLength[8] = 7;
	priv->codeTbl.codeLength[9] = 10;
	priv->codeTbl.codeLength[10] = 10;
	priv->codeTbl.codeLength[11] = 10;
	priv->codeTbl.codeLength[12] = 10;
	priv->codeTbl.codeLength[13] = 9;
	priv->codeTbl.codeLength[14] = 9;
}

// setup User lut
void ct_im_raw_config_setup_user_lut0(CtImRawConfig* self)
{
	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_PRIVATE(self);
	kint32 i;

	for (i = 0; i < 256; i++) {
		priv->userLut[i] = 255 - i;
	}
}

// setup User lut
void ct_im_raw_config_setup_user_lut1(CtImRawConfig* self)
{
	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_PRIVATE(self);
	kint32 i;

	for (i = 0; i < 256; i++) {
		priv->userLut[i] = i;
	}
}

// verify 8bit data
kint32 ct_im_raw_config_verify_data_lut(CtImRawConfig* self, kuchar* addr1, kuchar* addr2, kuint32 byte)
{
	CtImRawConfigPrivate *priv = CT_IM_RAW_CONFIG_PRIVATE(self);
	kint32 i;

	for (i = 0; i < byte; i++) {
		if ((priv->userLut[*addr1]) != (*addr2)){
			return CtImRawConfig_NG;
		}
		addr1++;
		addr2++;
	}

	return CtImRawConfig_OK;
}

CtImRawConfig* ct_im_raw_config_new(void)
{
	CtImRawConfig* self = k_object_new_with_private(CT_TYPE_IM_RAW_CONFIG, sizeof(CtImRawConfigPrivate));

	return self;
}
