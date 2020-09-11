/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈元
*@brief : CtImRawTest2
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include <stdlib.h>
#include <string.h>

#include "jdsraw.h"
#include "im_raw.h"
#include "driver_common.h"
#include "ctimrawconfig.h"
#include "ctimrawvarify.h"
#include "imraw.h"
#include "ddimusercustom.h"
#include "ctimrawtest2.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImRawTest2, ct_im_raw_test2)
#define CT_IM_RAW_TEST2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImRawTest2Private, CT_TYPE_IM_RAW_TEST2))


struct _CtImRawTest2Private
{
	CtImRawVarify 	*ctImRawVarify;
	CtImRawConfig 	*ctImRawConfig;
	ImRaw 				*imRaw;
	DdimUserCustom *ddimUserCustom;
	kint32 					retval;
	kuint32				condition;
	kuint32 				byte;
	T_IM_RAW_AXI_STATUS	axiState;
	EncResult encResult;
	RawData rawData;
};


/********
 * IMPL
 */
static void ct_im_raw_test2_constructor(CtImRawTest2 *self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);

	priv->ctImRawVarify = ct_im_raw_varify_new();
	priv->ctImRawConfig = ct_im_raw_config_new();
	priv->imRaw = im_raw_new();
	priv->ddimUserCustom = ddim_user_custom_new();
}

static void ct_im_raw_test2_destructor(CtImRawTest2 *self)
{
//	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);
}


/********
 * PUBLIC
 */
// Abnormal argument test
kint32 ct_im_raw_test2_0(CtImRawTest2* self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);
	T_IM_RAW_CTRL_CODE_TBL 	tbl;

	Ddim_Print(("raw param error check. 11test all OK?\n"));
	priv->retval = Im_RAW_Open(priv->imRaw, -2);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, (kint32)D_IM_RAW_RETVAL_PARAM_ERROR);

	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, NULL, D_IM_RAW_RFMT_14_OR_16_BIT);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_PARAM_ERROR);

	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &tbl, 10);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_PARAM_ERROR);

	priv->retval = Im_RAW_Ctrl_Enc(priv->imRaw, NULL, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_PARAM_ERROR);

	priv->retval = Im_RAW_Ctrl_Dec(priv->imRaw, NULL);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_PARAM_ERROR);

	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, NULL, &priv->byte, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_PARAM_ERROR);

	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, NULL, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_PARAM_ERROR);

	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, &priv->byte, -3);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_PARAM_ERROR);

	priv->retval = Im_RAW_Wait_End_Dec(priv->imRaw, NULL, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_PARAM_ERROR);

	priv->retval = Im_RAW_Wait_End_Dec(priv->imRaw, &priv->condition, -100);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_PARAM_ERROR);

	priv->retval = Im_RAW_Get_AXI_Status(priv->imRaw, NULL);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_PARAM_ERROR);

	return CtImRawConfig_OK;
}

kint32 ct_im_raw_test2_1(CtImRawTest2* self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);

	return ct_im_raw_varify_test_init(priv->ctImRawVarify);
}

// 14 bit RAW
kint32 ct_im_raw_test2_2(CtImRawTest2* self, kint32 testType)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ORG_ADDR;

	if (testType == 1) {
		// Can't Access Address
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = 0x00000000;
	} else
	{
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_ENC_ADDR;
	}
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_14_OR_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).mcuSize = D_IM_RAW_DEFFC_MCU_2x2;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_EXCEPT_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width = CtImRawConfig_WIDTH;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines = CtImRawConfig_LINES;

	Ddim_Print(("raw test2_2 porocess 1\n"));
	priv->retval = Im_RAW_Open(priv->imRaw, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_2 porocess 2\n"));
	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_2 porocess 3\n"));
	priv->retval = Im_RAW_Ctrl_Enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_2 porocess 4\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_2 porocess 5\n"));
	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, &priv->byte, 1000);

	ct_im_raw_config_get_enc_byte(priv->ctImRawConfig) = priv->byte;

	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	priv->encResult.retval = priv->retval;
	priv->encResult.cond = priv->condition;
	priv->encResult.byte = priv->byte;
	priv->encResult.width = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width;
	priv->encResult.lines = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines;
	priv->encResult.bitMode = 0;
	ct_im_raw_varify_enc_result(priv->ctImRawVarify, priv->encResult);

	priv->retval = Im_RAW_Get_AXI_Status(priv->imRaw, &priv->axiState);
	Ddim_Print(("AXI state\n"));
	Ddim_Print(("Read ch  response state : %d\n", priv->axiState.rChResp));
	Ddim_Print(("Write ch response state : %d\n", priv->axiState.wChResp));

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_DEC_ADDR;

	Ddim_Print(("raw test2_2 porocess 6\n"));
	priv->retval = Im_RAW_Ctrl_Dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_2 porocess 7\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_2 porocess 8\n"));
	priv->retval = Im_RAW_Wait_End_Dec(priv->imRaw, &priv->condition, 1000);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	priv->rawData.addr1 = (kuint16*)CtImRaw_DEC_ADDR;
	priv->rawData.addr2 = (kuint16*)CtImRaw_ORG_ADDR;
	priv->rawData.byte = (ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width * 2 *
	           ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines);
	priv->rawData.bitsel = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect;
	priv->retval = ct_im_raw_varify_raw(priv->ctImRawVarify, priv->rawData);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, CtImRawConfig_OK);

	Ddim_Print(("raw test2_2 porocess 9\n"));
	priv->retval = Im_RAW_Close(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_2 porocess 10\n"));

	return CtImRawConfig_OK;
}

// 16 bit RAW
kint32 ct_im_raw_test2_3(CtImRawTest2* self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ORG_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_14_OR_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).mcuSize = D_IM_RAW_DEFFC_MCU_2x2;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width = CtImRawConfig_WIDTH;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines = CtImRawConfig_LINES;

	Ddim_Print(("raw test2_3 porocess 1\n"));
	priv->retval = Im_RAW_Open(priv->imRaw, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_3 porocess 2\n"));

	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_3 porocess 3\n"));
	priv->retval = Im_RAW_Ctrl_Enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_3 porocess 4\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_3 porocess 5\n"));
	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, &priv->byte, 1000);

	ct_im_raw_config_get_enc_byte(priv->ctImRawConfig) = priv->byte;

	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	priv->encResult.retval = priv->retval;
	priv->encResult.cond = priv->condition;
	priv->encResult.byte = priv->byte;
	priv->encResult.width = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width;
	priv->encResult.lines = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines;
	priv->encResult.bitMode = 0;
	ct_im_raw_varify_enc_result(priv->ctImRawVarify, priv->encResult);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_DEC_ADDR;
	// 16 bit decode
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_16_BIT;

	Ddim_Print(("raw test2_3 porocess 6\n"));
	priv->retval = Im_RAW_Ctrl_Dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_3 porocess 7\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_3 porocess 8\n"));
	priv->retval = Im_RAW_Wait_End_Dec(priv->imRaw, &priv->condition, 1000);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	priv->rawData.addr1 = (kuint16*)CtImRaw_ORG_ADDR;
	priv->rawData.addr2 = (kuint16*)CtImRaw_DEC_ADDR;
	priv->rawData.byte = (ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width * 2 *
		          ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines);
	priv->rawData.bitsel = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect;
	priv->retval = ct_im_raw_varify_raw(priv->ctImRawVarify, priv->rawData);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, CtImRawConfig_OK);

	Ddim_Print(("raw test2_3 porocess 9\n"));
	priv->retval = Im_RAW_Close(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_3 porocess 10\n"));

	return CtImRawConfig_OK;
}

// 8 bit data w/o lut
kint32 ct_im_raw_test2_4(CtImRawTest2* self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);

	ct_im_raw_config_8bit_code_table(priv->ctImRawConfig);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ORG_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_8_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).diffMode = D_IM_RAW_DEFOP_DIFF_PREV_VALUE;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lut = NULL;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataSize = CtImRawConfig_8_WIDTH * CtImRawConfig_8_LINES;

	Ddim_Print(("raw test2_4 porocess 1\n"));
	priv->retval = Im_RAW_Open(priv->imRaw, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_4 porocess 2\n"));
	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_4 porocess 3\n"));
	priv->retval = Im_RAW_Ctrl_Enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_4 porocess 4\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_4 porocess 5\n"));
	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, &priv->byte, 1000);

	ct_im_raw_config_get_enc_byte(priv->ctImRawConfig) = priv->byte;

	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	priv->encResult.retval = priv->retval;
	priv->encResult.cond = priv->condition;
	priv->encResult.byte = priv->byte;
	priv->encResult.width = CtImRawConfig_8_WIDTH;
	priv->encResult.lines = CtImRawConfig_8_LINES;
	priv->encResult.bitMode = 0;
	ct_im_raw_varify_enc_result(priv->ctImRawVarify, priv->encResult);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_DEC_ADDR;

	Ddim_Print(("raw test2_4 porocess 6\n"));
	priv->retval = Im_RAW_Ctrl_Dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_4 porocess 7\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_4 porocess 8\n"));
	priv->retval = Im_RAW_Wait_End_Dec(priv->imRaw, &priv->condition, 1000);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	priv->retval = ct_im_raw_varify_data((kuchar*)CtImRaw_DEC_ADDR, (kuchar*)CtImRaw_ORG_ADDR,
						            ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataSize);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, CtImRawConfig_OK);

	Ddim_Print(("raw test2_4 porocess 9\n"));
	priv->retval = Im_RAW_Close(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_4 porocess 10\n"));

	return CtImRawConfig_OK;
}

// 8 bit data with lut
kint32 ct_im_raw_test2_5(CtImRawTest2* self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);

	ct_im_raw_config_8bit_code_table(priv->ctImRawConfig);

	// lut
	ct_im_raw_config_setup_user_lut0(priv->ctImRawConfig);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ORG_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_8_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).diffMode = D_IM_RAW_DEFOP_DIFF_PREV_VALUE;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lut = ct_im_raw_config_get_user_lut(priv->ctImRawConfig );
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataSize = CtImRawConfig_8_WIDTH * CtImRawConfig_8_LINES;

	Ddim_Print(("raw test2_5 porocess 1\n"));
	priv->retval = Im_RAW_Open(priv->imRaw, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_5 porocess 2\n"));
	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_5 porocess 3\n"));
	priv->retval = Im_RAW_Ctrl_Enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_5 porocess 4\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_5 porocess 5\n"));
	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, &priv->byte, 1000);

	ct_im_raw_config_get_enc_byte(priv->ctImRawConfig) = priv->byte;

	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	priv->encResult.retval = priv->retval;
	priv->encResult.cond = priv->condition;
	priv->encResult.byte = priv->byte;
	priv->encResult.width = CtImRawConfig_8_WIDTH;
	priv->encResult.lines = CtImRawConfig_8_LINES;
	priv->encResult.bitMode = 0;
	ct_im_raw_varify_enc_result(priv->ctImRawVarify, priv->encResult);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_DEC_ADDR;

	// lut
	ct_im_raw_config_setup_user_lut1(priv->ctImRawConfig);

	Ddim_Print(("raw test2_5 porocess 6\n"));
	priv->retval = Im_RAW_Ctrl_Dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_5 porocess 7\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_5 porocess 8\n"));
	priv->retval = Im_RAW_Wait_End_Dec(priv->imRaw, &priv->condition, 1000);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	// lut
	ct_im_raw_config_setup_user_lut0(priv->ctImRawConfig);

	priv->retval = ct_im_raw_config_verify_data_lut(priv->ctImRawConfig, (kuchar*)CtImRaw_ORG_ADDR,
			(kuchar*)CtImRaw_DEC_ADDR, ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataSize);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, CtImRawConfig_OK);

	Ddim_Print(("raw test2_5 porocess 9\n"));
	priv->retval = Im_RAW_Close(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_5 porocess 10\n"));

	return CtImRawConfig_OK;
}

// Force Stop
// Init at running
// Ctrl at running
// Start at running
kint32 ct_im_raw_test2_6(CtImRawTest2* self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ORG_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_14_OR_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).mcuSize = D_IM_RAW_DEFFC_MCU_2x2;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_EXCEPT_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width = CtImRawConfig_WIDTH;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines = CtImRawConfig_LINES;

	priv->retval = Im_RAW_Open(priv->imRaw, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Ctrl_Enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);


	Ddim_Print(("raw encode force stop test\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Stop(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, &priv->byte, 1000);

	ct_im_raw_config_get_enc_byte(priv->ctImRawConfig) = priv->byte;

	Ddim_Print(("encode force stop OK?\n"));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_FORCE_STOP);

	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw encode macro busy error test\n"));
	Ddim_Print(("4test macro busy OK?\n"));
	priv->retval = Im_RAW_Init(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_MACRO_BUSY);
	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_MACRO_BUSY);
	priv->retval = Im_RAW_Ctrl_Enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_MACRO_BUSY);
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_MACRO_BUSY);

	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, &priv->byte, 1000);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	Ddim_Print(("encode result\n"));
	priv->encResult.retval = priv->retval;
	priv->encResult.cond = priv->condition;
	priv->encResult.byte = priv->byte;
	priv->encResult.width = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width;
	priv->encResult.lines = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines;
	priv->encResult.bitMode = 0;
	ct_im_raw_varify_enc_result(priv->ctImRawVarify, priv->encResult);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_DEC_ADDR;

	priv->retval = Im_RAW_Ctrl_Dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Stop(priv->imRaw);
	Ddim_Print(("raw decode force stop test\n"));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Wait_End_Dec(priv->imRaw, &priv->condition, 1000);
	Ddim_Print(("decode force stop OK?\n"));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_FORCE_STOP);

	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw encode macro busy error test\n"));
	Ddim_Print(("4test macro busy OK?\n"));
	priv->retval = Im_RAW_Init(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_MACRO_BUSY);
	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_MACRO_BUSY);
	priv->retval = Im_RAW_Ctrl_Dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_MACRO_BUSY);
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_MACRO_BUSY);

	priv->retval = Im_RAW_Wait_End_Dec(priv->imRaw, &priv->condition, 1000);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	priv->retval = Im_RAW_Close(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return CtImRawConfig_OK;
}

// cLMT
kint32 ct_im_raw_test2_7(CtImRawTest2* self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);
	kuint32 	cLMT = 1024;

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ORG_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_14_OR_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).mcuSize = D_IM_RAW_DEFFC_MCU_2x2;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_EXCEPT_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width = CtImRawConfig_WIDTH;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines = CtImRawConfig_LINES;

	priv->retval = Im_RAW_Open(priv->imRaw, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Ctrl_Enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), cLMT);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, &priv->byte, 1000);

	ct_im_raw_config_get_enc_byte(priv->ctImRawConfig) = priv->byte;

	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	Ddim_Print(("encode limit over test OK?\n"));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_ENC_LIMIT_OVER);

	priv->retval = Im_RAW_Close(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return CtImRawConfig_OK;
}

// Decode error (decode error)
kint32 ct_im_raw_test2_8(CtImRawTest2* self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);

	// Modify code table
	ct_im_raw_config_get_code_tbl(priv->ctImRawConfig).code[3]  = 0x2000;
	ct_im_raw_config_get_code_tbl(priv->ctImRawConfig).code[4]  = 0x2000;
	ct_im_raw_config_get_code_tbl(priv->ctImRawConfig).codeLength[3]  = 3;
	ct_im_raw_config_get_code_tbl(priv->ctImRawConfig).codeLength[4]  = 3;

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ORG_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_14_OR_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).mcuSize = D_IM_RAW_DEFFC_MCU_2x2;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_EXCEPT_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width = CtImRawConfig_WIDTH;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines = CtImRawConfig_LINES;

	Ddim_Print(("encode process\n"));
	priv->retval = Im_RAW_Open(priv->imRaw, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Ctrl_Enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, &priv->byte, 1000);

	ct_im_raw_config_get_enc_byte(priv->ctImRawConfig) = priv->byte;

	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	priv->encResult.retval = priv->retval;
	priv->encResult.cond = priv->condition;
	priv->encResult.byte = priv->byte;
	priv->encResult.width = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width;
	priv->encResult.lines = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines;
	priv->encResult.bitMode = 0;
	ct_im_raw_varify_enc_result(priv->ctImRawVarify, priv->encResult);

	Ddim_Print(("decode process\n"));

	// Modify code table
	ct_im_raw_config_get_code_tbl(priv->ctImRawConfig).code[3] = 0x2000;
	ct_im_raw_config_get_code_tbl(priv->ctImRawConfig).code[4] = 0x2000;
	ct_im_raw_config_get_code_tbl(priv->ctImRawConfig).codeLength[3]  = 3;
	ct_im_raw_config_get_code_tbl(priv->ctImRawConfig).codeLength[4]  = 3;
	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_DEC_ADDR;

	priv->retval = Im_RAW_Ctrl_Dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("decode error test\n"));
	priv->retval = Im_RAW_Wait_End_Dec(priv->imRaw, &priv->condition, 1000);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	Ddim_Print(("decode error OK?\n"));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_DEC_ERROR);

	priv->retval = Im_RAW_Close(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return CtImRawConfig_OK;
}

// Decode error (undef code)
kint32 ct_im_raw_test2_9(CtImRawTest2* self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ORG_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_14_OR_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).mcuSize = D_IM_RAW_DEFFC_MCU_2x2;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_EXCEPT_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width = CtImRawConfig_WIDTH;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines = CtImRawConfig_LINES;

	Ddim_Print(("encode process\n"));
	priv->retval = Im_RAW_Open(priv->imRaw, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Ctrl_Enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, &priv->byte, 1000);

	ct_im_raw_config_get_enc_byte(priv->ctImRawConfig) = priv->byte;

	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	priv->encResult.retval = priv->retval;
	priv->encResult.cond = priv->condition;
	priv->encResult.byte = priv->byte;
	priv->encResult.width = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width;
	priv->encResult.lines = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines;
	priv->encResult.bitMode = 0;
	ct_im_raw_varify_enc_result(priv->ctImRawVarify, priv->encResult);


	Ddim_Print(("decode process\n"));

	// Modify code table
	ct_im_raw_config_invalid_code(priv->ctImRawConfig);
	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_DEC_ADDR;

	priv->retval = Im_RAW_Ctrl_Dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("decode error(undef code) test\n"));
	priv->retval = Im_RAW_Wait_End_Dec(priv->imRaw, &priv->condition, 1000);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	Ddim_Print(("decode error(undef code) OK?\n"));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_DEC_UNDEF_CODE);

	priv->retval = Im_RAW_Close(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return CtImRawConfig_OK;
}

// Semaphone
kint32 ct_im_raw_test2_10(CtImRawTest2* self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);

	priv->retval = Im_RAW_Open(priv->imRaw, 0);
	Ddim_Print(("raw open 1\n"));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Open(priv->imRaw, 1);
	Ddim_Print(("raw open error OK?\n"));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_SYSTEM_ERROR);

	priv->retval = Im_RAW_Close(priv->imRaw);
	Ddim_Print(("raw close 1\n"));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Close(priv->imRaw);
	Ddim_Print(("raw close error OK?\n"));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_SYSTEM_ERROR);

	return CtImRawConfig_OK;
}

// 12 bit pack RAW
kint32 ct_im_raw_test2_11(CtImRawTest2* self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ORG_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_14_OR_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).mcuSize = D_IM_RAW_DEFFC_MCU_2x2;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_EXCEPT_16_BIT;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width = CtImRawConfig_WIDTH;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines = CtImRawConfig_LINES;

	Ddim_Print(("raw test2_11 porocess 1\n"));
	priv->retval = Im_RAW_Open(priv->imRaw, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_11 porocess 2\n"));
	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_11 porocess 3\n"));
	priv->retval = Im_RAW_Ctrl_Enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_11 porocess 4\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_11 porocess 5\n"));
	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, &priv->byte, 1000);

	ct_im_raw_config_get_enc_byte(priv->ctImRawConfig) = priv->byte;

	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	priv->encResult.retval = priv->retval;
	priv->encResult.cond = priv->condition;
	priv->encResult.byte = priv->byte;
	priv->encResult.width = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width;
	priv->encResult.lines = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines;
	priv->encResult.bitMode = 1;
	ct_im_raw_varify_enc_result(priv->ctImRawVarify, priv->encResult);

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_DEC_ADDR;
	// 12bit pack decode
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_12_BIT_PACK;


	Ddim_Print(("raw test2_11 porocess 6\n"));
	priv->retval = Im_RAW_Ctrl_Dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_11 porocess 7\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_11 porocess 8\n"));
	priv->retval = Im_RAW_Wait_End_Dec(priv->imRaw, &priv->condition, 1000);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	priv->retval = ct_im_raw_varify_raw_12bit_pack(priv->ctImRawVarify, (kuint16*)CtImRaw_ORG_ADDR,
			(BYTE*)CtImRaw_DEC_ADDR,
			(ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width *
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines * 1.5));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, CtImRawConfig_OK);

	Ddim_Print(("raw test2_11 porocess 9\n"));
	priv->retval = Im_RAW_Close(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_11 porocess 10\n"));

	return CtImRawConfig_OK;
}

// Int_Handler Test(PC Only)
kint32 ct_im_raw_test2_12(CtImRawTest2* self)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);

	Im_RAW_Int_Handler(priv->imRaw);

	return CtImRawConfig_OK;
}

// change Huffman Table
kint32 ct_im_raw_test2_14(CtImRawTest2* self, Test2Val test2Val)
{
	CtImRawTest2Private *priv = CT_IM_RAW_TEST2_GET_PRIVATE(self);
	kint32	decType;

	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ORG_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_ENC_ADDR;

	// Encode Format
	if (test2Val.test2Val1 == 0) {
		// 14bit Format
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_14_OR_16_BIT;
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_EXCEPT_16_BIT;
		Ddim_Print(("Encode Format : 14bit Select\n"));
	} else if (test2Val.test2Val1 == 1) {
		// 12bit Format
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_12_BIT_PACK;
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_EXCEPT_16_BIT;
		Ddim_Print(("Encode Format : 12bit pack Select\n"));
	} else if (test2Val.test2Val1 == 2) {
		// 16bit Format
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_14_OR_16_BIT;
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_16_BIT;
		Ddim_Print(("Encode Format : 16bit Select\n"));
	} else {
		Ddim_Print(("Encode Format select error 0:14bit 1:12bit 2:16bit\n"));
		return CtImRawConfig_NG;
	}

	// Decode Format
	if (test2Val.test2Val2 == 0){
		// 14bit Format
		decType = 0;
		Ddim_Print(("Decode Format : 14bit Select\n"));
	} else if (test2Val.test2Val2 == 1) {
		// 12bit Format
		decType = 1;
		Ddim_Print(("Decode Format : 12bit pack Select\n"));
	} else if (test2Val.test2Val2 == 2){
		// 16bit Format
		decType = 2;
		Ddim_Print(("Decode Format : 16bit Select\n"));
	} else {
		Ddim_Print(("Decode Format select error 0:14bit 1:12bit 2:16bit\n"));
		return CtImRawConfig_NG;
	}

	// Width
	if (test2Val.test2Val3 % 32 != 0) {
		Ddim_Print(("Width error   not 32 priv->byte align\n"));
		return CtImRawConfig_NG;
	}
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width = test2Val.test2Val3;

	// Line
	if (test2Val.test2Val4 % 2 != 0) {
		Ddim_Print(("Line error   not 2 priv->byte align\n"));
		return CtImRawConfig_NG;
	}
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines = test2Val.test2Val4;

	// MCU
	if (test2Val.test2Val5 == 0) {
		// MCU 2x2
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).mcuSize = D_IM_RAW_DEFFC_MCU_2x2;
	} else if (test2Val.test2Val5 == 1) {
		// MCU 2x1
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).mcuSize = D_IM_RAW_DEFFC_MCU_2x1;
	} else {
		Ddim_Print(("MCU select error   0:MCU 2x2 1:MCU 2x1\n"));
		return CtImRawConfig_NG;
	}

	// Byte stuff
	if (test2Val.test2Val6 == 0){
		// Byte stuff OFF
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).byteStuffing = D_IM_RAW_OFF;
	} else if (test2Val.test2Val6 == 1){
		// Byte stuff ON
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).byteStuffing = D_IM_RAW_ON;
	} else {
		Ddim_Print(("Byte stuff select error    0:OFF 1:ON\n"));
		return CtImRawConfig_NG;
	}

	// definit
	if (test2Val.test2Val7 > 16383) {
		// definit
		Ddim_Print(("definit error   diffFixedValue 0 to 16383\n"));
		return CtImRawConfig_NG;
	} else {
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).diffFixedValue = test2Val.test2Val7;
	}

	// Huff Tbl
	if (test2Val.test2Val8 == 0) {
		// Default Huffman Table
		Ddim_Print(("Select Default huffman table\n"));
	} else if (test2Val.test2Val8 == 1){
		// User custom Table
		ct_im_raw_config_set_huff_tbl(priv->ctImRawConfig);
		Ddim_Print(("Select User set huffman table\n"));
	} else {
		Ddim_Print(("Huffman table select error    0:Default 1:User Setting\n"));
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test2_14 porocess 1\n"));
	priv->retval = Im_RAW_Open(priv->imRaw, 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_14 porocess 2\n"));
	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_14 porocess 3\n"));
	priv->retval = Im_RAW_Ctrl_Enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_14 porocess 4\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_14 porocess 5\n"));
	priv->retval = Im_RAW_Wait_End_Enc(priv->imRaw, &priv->condition, &priv->byte, 1000);

	ct_im_raw_config_get_enc_byte(priv->ctImRawConfig) = priv->byte;

	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	if (ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat == D_IM_RAW_RFMT_12_BIT_PACK) {
		priv->encResult.retval = priv->retval;
		priv->encResult.cond = priv->condition;
		priv->encResult.byte = priv->byte;
		priv->encResult.width = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width;
		priv->encResult.lines = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines;
		priv->encResult.bitMode = 1;
		ct_im_raw_varify_enc_result(priv->ctImRawVarify, priv->encResult);
	} else {
		priv->encResult.retval = priv->retval;
		priv->encResult.cond = priv->condition;
		priv->encResult.byte = priv->byte;
		priv->encResult.width = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).width;
		priv->encResult.lines = ct_im_raw_config_get_raw_param(priv->ctImRawConfig).lines;
		priv->encResult.bitMode = 0;
		ct_im_raw_varify_enc_result(priv->ctImRawVarify, priv->encResult);
	}
	priv->retval = Im_RAW_Get_AXI_Status(priv->imRaw, &priv->axiState);
	Ddim_Print(("AXI state\n"));
	Ddim_Print(("Read ch  response state : %d\n", priv->axiState.rChResp));
	Ddim_Print(("Write ch response state : %d\n", priv->axiState.wChResp));

	// Modify ct_im_raw_config_get_raw_param(priv->ctImRawConfig)
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).srcAddr = CtImRaw_ENC_ADDR;
	ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dstAddr = CtImRaw_DEC_ADDR;

	if (decType == 0) {
		// 14bit Format
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_14_OR_16_BIT;
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_EXCEPT_16_BIT;
	} else if (decType == 1) {
		// 12bit Format
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_12_BIT_PACK;
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_EXCEPT_16_BIT;
	} else {
		// 16bit Format
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat = D_IM_RAW_RFMT_14_OR_16_BIT;
		ct_im_raw_config_get_raw_param(priv->ctImRawConfig).bitSelect = D_IM_RAW_BITSEL_16_BIT;
	}

	Ddim_Print(("raw test2_14 porocess 6\n"));
	priv->retval = Im_RAW_Ctrl_CodeTbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	priv->retval = Im_RAW_Ctrl_Dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_14 porocess 7\n"));
	priv->retval = Im_RAW_Start(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_14 porocess 8\n"));
	priv->retval = Im_RAW_Wait_End_Dec(priv->imRaw, &priv->condition, 1000);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->condition, D_IM_RAW_COND_OK);

	Ddim_Print(("raw test2_14 porocess 9\n"));
	priv->retval = Im_RAW_Close(priv->imRaw);
	ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	Ddim_Print(("raw test2_14 porocess 10\n"));

	return CtImRawConfig_OK;
}

CtImRawTest2* ct_im_raw_test2_new(void)
{
	CtImRawTest2* self = k_object_new_with_private(CT_TYPE_IM_RAW_TEST2, sizeof(CtImRawTest2Private));

	return self;
}
