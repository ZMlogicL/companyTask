/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈元
*@brief : CtImRawTest1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include <stdlib.h>
#include <string.h>

#include "jdsraw.h"
#include "imraw.h"
//#include "ct_im_raw.h"
#include "driver_common.h"
#include "ctimrawconfig.h"
#include "ctimrawvarify.h"
#include "imraw.h"
#include "ddimusercustom.h"
#include "ctimrawtest1.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImRawTest1, ct_im_raw_test1)
#define CT_IM_RAW_TEST1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImRawTest1Private, CT_TYPE_IM_RAW_TEST1))


struct _CtImRawTest1Private
{
	CtImRawVarify 	*ctImRawVarify;
	CtImRawConfig 	*ctImRawConfig;
	ImRaw 				*imRaw;
	DdimUserCustom *ddimUserCustom;
	kint32					retval;
	kint32					ret;
	kuint32				condition;
	kuint32 				byte;
	kuchar					tmpFid;
};


/********
 * IMPL
 */
static void ct_im_raw_test1_constructor(CtImRawTest1 *self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	priv->ctImRawVarify = ct_im_raw_varify_new();
	priv->ctImRawConfig = ct_im_raw_config_new();
	priv->imRaw = im_raw_new();
	priv->ddimUserCustom = ddim_user_custom_new();
}

static void ct_im_raw_test1_destructor(CtImRawTest1 *self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	if (priv->ctImRawVarify) {
		k_object_unref(priv->ctImRawVarify);
		priv->ctImRawVarify = NULL;
	}

	if (priv->ctImRawConfig) {
		k_object_unref(priv->ctImRawConfig);
		priv->ctImRawConfig = NULL;
	}

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
// Open(pol_sem)
kint32 ct_im_raw_test1_0(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	Ddim_Print(("raw test1_0 porocess 1\n"));
	priv->retval = im_raw_open(priv->imRaw, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_0 porocess 2\n"));
	priv->retval = im_raw_close(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Open/Close(twai_sem)
kint32 ct_im_raw_test1_1(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	Ddim_Print(("raw test1_1 porocess 1\n"));
	priv->retval = im_raw_open(priv->imRaw, 100);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_1 porocess 2\n"));
	priv->retval = im_raw_close(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return CtImRawConfig_OK;
}

// Open(parameter error)
kint32 ct_im_raw_test1_2(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	Ddim_Print(("raw test1_2 porocess 1\n"));
	priv->retval = im_raw_open(priv->imRaw, -2);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Ctrl_CodeTbl(normal end)
kint32 ct_im_raw_test1_3(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Ctrl_CodeTbl(parameter error)
kint32 ct_im_raw_test1_4(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, NULL,
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig), 3);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Ctrl_CodeTbl(macro busy)
kint32 ct_im_raw_test1_5(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	ioRaw.rctl1.bit.rtrg = 1;
#ifdef CO_DEBUG_ON_PC
	ioRaw.rctl1.bit.rtrg = 3;
#endif

	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Ctrl_Enc(normal end)
kint32 ct_im_raw_test1_6(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	priv->retval = im_raw_ctrl_enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Ctrl_Enc(parameter error)
kint32 ct_im_raw_test1_7(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	priv->retval = im_raw_ctrl_enc(priv->imRaw, NULL, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Ctrl_Enc(macro busy)
kint32 ct_im_raw_test1_8(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	ioRaw.rctl1.bit.rtrg = 1;
#ifdef CO_DEBUG_ON_PC
	ioRaw.rctl1.bit.rtrg = 3;
#endif

	priv->retval = im_raw_ctrl_enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Ctrl_Dec(normal end)
kint32 ct_im_raw_test1_9(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	priv->retval = im_raw_ctrl_dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Ctrl_Dec(parameter error)
kint32 ct_im_raw_test1_10(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	priv->retval = im_raw_ctrl_dec(priv->imRaw, NULL);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Ctrl_Dec(macro busy)
kint32 ct_im_raw_test1_11(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	ioRaw.rctl1.bit.rtrg = 1;
#ifdef CO_DEBUG_ON_PC
	ioRaw.rctl1.bit.rtrg = 3;
#endif

	priv->retval = im_raw_ctrl_dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Start(normal end)
kint32 ct_im_raw_test1_12(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	Ddim_Print(("raw test1_12 porocess 1\n"));
	priv->retval = im_raw_open(priv->imRaw, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_12 porocess 2\n"));
	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_12 porocess 3\n"));
	priv->retval = im_raw_ctrl_enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_12 porocess 4\n"));
	priv->retval = im_raw_start(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

#ifdef CO_DEBUG_ON_PC
	// normal end
	DDIM_User_Set_Flg(priv->ddimUserCustom, FID_IM_RAW, 0x00000001);
#endif

	Ddim_Print(("raw test1_12 porocess 5\n"));
	priv->retval = im_raw_wait_end_enc(priv->imRaw, &priv->condition, &priv->byte, 1000);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if(priv->ret != CtImRawConfig_OK){
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_12 porocess 6\n"));
	priv->retval = im_raw_close(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Start(system error)
kint32 ct_im_raw_test1_13(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	Ddim_Print(("raw test1_13 porocess 1\n"));
	priv->retval = im_raw_open(priv->imRaw, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_13 porocess 2\n"));
	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_13 porocess 3\n"));
	priv->retval = im_raw_ctrl_enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	priv->tmpFid = FID_IM_RAW;
	FID_IM_RAW = 0xFF;

	Ddim_Print(("raw test1_13 porocess 4\n"));
	priv->retval = im_raw_start(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	FID_IM_RAW = priv->tmpFid;

#if 0	// because not start
	Ddim_Print(("raw test1_13 porocess 5\n"));
	priv->retval = im_raw_wait_end_enc(priv->imRaw, &priv->condition, &priv->byte, 1000);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}
#endif	// because not start

	Ddim_Print(("raw test1_13 porocess 6\n"));
	priv->retval = im_raw_close(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Start(macro busy)
kint32 ct_im_raw_test1_14(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	Ddim_Print(("raw test1_14 porocess 1\n"));
	priv->retval = im_raw_open(priv->imRaw, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_14 porocess 2\n"));
	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_14 porocess 3\n"));
	priv->retval = im_raw_ctrl_enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_14 porocess 4\n"));
	priv->retval = im_raw_start(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

#ifdef CO_DEBUG_ON_PC
	ioRaw.rctl1.bit.rtrg = 3;
#endif

	Ddim_Print(("raw test1_14 porocess 5\n"));
	// im_raw_start() retry
	priv->retval = im_raw_start(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

#ifdef CO_DEBUG_ON_PC
	// normal end
	DDIM_User_Set_Flg(priv->ddimUserCustom, FID_IM_RAW, 0x00000001);
#endif

	Ddim_Print(("raw test1_14 porocess 6\n"));
	priv->retval = im_raw_wait_end_enc(priv->imRaw, &priv->condition, &priv->byte, 1000);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_14 porocess 7\n"));
	priv->retval = im_raw_close(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Wait_End_Enc(normal end)
kint32 ct_im_raw_test1_15(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	Ddim_Print(("raw test1_15 porocess 1\n"));
	priv->retval = im_raw_open(priv->imRaw, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_15 porocess 2\n"));
	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_15 porocess 3\n"));
	priv->retval = im_raw_ctrl_enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_15 porocess 4\n"));
	priv->retval = im_raw_start(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

#ifdef CO_DEBUG_ON_PC
	// normal end
	DDIM_User_Set_Flg(priv->ddimUserCustom, FID_IM_RAW, 0x00000001);
#endif

	Ddim_Print(("raw test1_15 porocess 5\n"));
	priv->retval = im_raw_wait_end_enc(priv->imRaw, &priv->condition, &priv->byte, 1000);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_15 porocess 6\n"));
	priv->retval = im_raw_close(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Wait_End_Enc(parameter error)
kint32 ct_im_raw_test1_16(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	priv->retval = im_raw_wait_end_enc(priv->imRaw, NULL, &priv->byte, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	priv->retval = im_raw_wait_end_enc(priv->imRaw, &priv->condition, NULL, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	priv->retval = im_raw_wait_end_enc(priv->imRaw, &priv->condition, &priv->byte, -3);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Wait_End_Enc(system error)
kint32 ct_im_raw_test1_17(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	Ddim_Print(("raw test1_17 porocess 1\n"));
	priv->retval = im_raw_open(priv->imRaw, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_17 porocess 2\n"));
	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_17 porocess 3\n"));
	priv->retval = im_raw_ctrl_enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_17 porocess 4\n"));
	priv->retval = im_raw_start(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	priv->tmpFid = FID_IM_RAW;
	FID_IM_RAW = 0xFF;

	Ddim_Print(("raw test1_17 porocess 5\n"));
	priv->retval = im_raw_wait_end_enc(priv->imRaw, &priv->condition, &priv->byte, 1000);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	FID_IM_RAW = priv->tmpFid;

	Ddim_Print(("raw test1_17 porocess 6\n"));
	priv->retval = im_raw_close(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Wait_End_Enc(R_AXI error)
kint32 ct_im_raw_test1_18(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	DDIM_User_Set_Flg(priv->ddimUserCustom, FID_IM_RAW, 0x00000004);
	Ddim_Print(("Set_Flg : R_AXI_ERR\n"));

	priv->retval = im_raw_wait_end_enc(priv->imRaw, &priv->condition, &priv->byte, 1000);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Wait_End_Enc(RW_AXI error)
kint32 ct_im_raw_test1_19(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	DDIM_User_Set_Flg(priv->ddimUserCustom, FID_IM_RAW, 0x00000008);
	Ddim_Print(("Set_Flg : W_AXI_ERR\n"));

	priv->retval = im_raw_wait_end_enc(priv->imRaw, &priv->condition, &priv->byte, 1000);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}


// Wait_End_Enc(force stop)
kint32 ct_im_raw_test1_20(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	Ddim_Print(("raw test1_20 porocess 1\n"));
	priv->retval = im_raw_open(priv->imRaw, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_20 porocess 2\n"));
	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_20 porocess 3\n"));
	priv->retval = im_raw_ctrl_enc(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig), 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_20 porocess 4\n"));
	priv->retval = im_raw_start(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

#ifdef CO_DEBUG_ON_PC
	ioRaw.rctl1.bit.rtrg = 3;
#endif

	Ddim_Print(("raw test1_20 porocess 5\n"));
	priv->retval = im_raw_stop(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_20 porocess 6\n"));
	priv->retval = im_raw_close(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Wait_End_Dec(normal end)
kint32 ct_im_raw_test1_21(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	Ddim_Print(("raw test1_21 porocess 1\n"));
	priv->retval = im_raw_open(priv->imRaw, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_21 porocess 2\n"));
	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_21 porocess 3\n"));
	priv->retval = im_raw_ctrl_dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_21 porocess 4\n"));
	priv->retval = im_raw_start(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

#ifdef CO_DEBUG_ON_PC
	// normal end
	DDIM_User_Set_Flg(priv->ddimUserCustom, FID_IM_RAW, 0x00000001);
#endif

	Ddim_Print(("raw test1_21 porocess 5\n"));
	priv->retval = im_raw_wait_end_dec(priv->imRaw, &priv->condition, 1000);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_21 porocess 6\n"));
	priv->retval = im_raw_close(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Wait_End_Dec(parameter error)
kint32 ct_im_raw_test1_22(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	priv->retval = im_raw_wait_end_dec(priv->imRaw, NULL, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	priv->retval = im_raw_wait_end_dec(priv->imRaw, &priv->condition, -100);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Wait_End_Dec(system error)
kint32 ct_im_raw_test1_23(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	Ddim_Print(("raw test1_23 porocess 1\n"));
	priv->retval = im_raw_open(priv->imRaw, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_23 porocess 2\n"));
	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_23 porocess 3\n"));
	priv->retval = im_raw_ctrl_dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_23 porocess 4\n"));
	priv->retval = im_raw_start(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	priv->tmpFid = FID_IM_RAW;
	FID_IM_RAW = 0xFF;

	Ddim_Print(("raw test1_23 porocess 5\n"));
	priv->retval = im_raw_wait_end_dec(priv->imRaw, &priv->condition, 1000);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	FID_IM_RAW = priv->tmpFid;

	Ddim_Print(("raw test1_23 porocess 6\n"));
	priv->retval = im_raw_close(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Wait_End_Dec(R_AXI error)
kint32 ct_im_raw_test1_24(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	ddim_user_custom_set_flg(priv->ddimUserCustom, FID_IM_RAW, 0x00000004);
	Ddim_Print(("Set_Flg : R_AXI_ERR\n"));

	priv->retval = im_raw_wait_end_dec(priv->imRaw, &priv->condition, 1000);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Wait_End_Dec(W_AXI error)
kint32 ct_im_raw_test1_25(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	ddim_user_custom_set_flg(priv->ddimUserCustom, FID_IM_RAW, 0x00000008);
	Ddim_Print(("Set_Flg : W_AXI_ERR\n"));

	priv->retval = im_raw_wait_end_dec(priv->imRaw, &priv->condition, 1000);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Wait_End_Dec(force stop)
kint32 ct_im_raw_test1_26(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	Ddim_Print(("raw test1_26 porocess 1\n"));
	priv->retval = im_raw_open(priv->imRaw, 0);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_26 porocess 2\n"));
	priv->retval = im_raw_ctrl_code_tbl(priv->imRaw, &ct_im_raw_config_get_code_tbl(priv->ctImRawConfig),
			ct_im_raw_config_get_raw_param(priv->ctImRawConfig).dataFormat);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_26 porocess 3\n"));
	priv->retval = im_raw_ctrl_dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_26 porocess 4\n"));
	priv->retval = im_raw_start(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

#ifdef CO_DEBUG_ON_PC
	ioRaw.rctl1.bit.rtrg = 3;
#endif

	Ddim_Print(("raw test1_26 porocess 5\n"));
	priv->retval = im_raw_stop(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("raw test1_26 porocess 6\n"));
	priv->retval = im_raw_close(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);

	return priv->ret;
}

// Stop(system error)
kint32 ct_im_raw_test1_28(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	priv->tmpFid = FID_IM_RAW;
	FID_IM_RAW = 0xFF;

#ifdef CO_DEBUG_ON_PC
	ioRaw.rctl1.bit.rtrg = 3;
#endif

	priv->retval = im_raw_stop(priv->imRaw);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	FID_IM_RAW = priv->tmpFid;

	return CtImRawConfig_OK;
}

// Get_AXI_Status(normal end)
kint32 ct_im_raw_test1_30(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);
	T_IM_RAW_AXI_STATUS	axiState;

	priv->retval = im_raw_get_axi_status(priv->imRaw, &axiState);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	Ddim_Print(("AXI state\n"));
	Ddim_Print(("Read ch  response state : %d\n", axiState.rChResp));
	Ddim_Print(("Write ch response state : %d\n", axiState.wChResp));

	return CtImRawConfig_OK;
}

// Get_AXI_Status(parameter error)
kint32 ct_im_raw_test1_31(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	priv->retval = im_raw_get_axi_status(priv->imRaw, NULL);
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_NG) {
		// NG is correct
		return CtImRawConfig_NG;
	}

	return CtImRawConfig_OK;
}

// Int_Handler(normal end)
kint32 ct_im_raw_test1_32(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	// set decode for callback setting
	priv->retval = im_raw_ctrl_dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	ioRaw.rintf.bit.__RF	= 1;
	ioRaw.rinte.bit.re = 1;

	Im_RAW_Int_Handler(priv->imRaw);
	Ddim_Print(("check : Int_Handler called\n"));

	return CtImRawConfig_OK;
}

// Int_Handler(R_AXI error)
kint32 ct_im_raw_test1_33(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	// set decode for callback setting
	priv->retval = im_raw_ctrl_dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	ioRaw.rintf.bit.__RAXERF = 1;
	ioRaw.rinte.bit.raxere = 1;

	Im_RAW_Int_Handler(priv->imRaw);
	Ddim_Print(("check : Int_Handler called\n"));

	return CtImRawConfig_OK;
}

// Int_Handler(W_AXI error)
kint32 ct_im_raw_test1_34(CtImRawTest1* self)
{
	CtImRawTest1Private *priv = CT_IM_RAW_TEST1_GET_PRIVATE(self);

	// set decode for callback setting
	priv->retval = im_raw_ctrl_dec(priv->imRaw, &ct_im_raw_config_get_raw_param(priv->ctImRawConfig));
	priv->ret = ct_im_raw_varify_check_retval(priv->ctImRawVarify, priv->retval, D_IM_RAW_RETVAL_OK);
	if (priv->ret != CtImRawConfig_OK) {
		return CtImRawConfig_NG;
	}

	ioRaw.rintf.bit.__WAXERF = 1;
	ioRaw.rinte.bit.waxere = 1;

	Im_RAW_Int_Handler(priv->imRaw);
	Ddim_Print(("check : Int_Handler called\n"));

	return CtImRawConfig_OK;
}

CtImRawTest1* ct_im_raw_test1_new(void)
{
	CtImRawTest1* self = k_object_new_with_private(CT_TYPE_IM_RAW_TEST1, sizeof(CtImRawTest1Private));

	return self;
}

