/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr6类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/
#include "im_cnr.h"
#include "dd_top.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#include "im_rdma.h"
#include "jdscnr.h"
#include "ctimcnr.h"
#include "ctimcnr1.h"
#include "ctimcnr6.h"

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr6, ct_im_cnr6, G_TYPE_OBJECT); 
#define CT_IM_CNR6_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR6, CtImCnr6Private))

struct _CtImCnr6Private
{

};

static void ct_im_cnr6_constructor(CtImCnr6 *self) 
{
//	CtImCnr6Private *priv = CT_IM_CNR6_GET_PRIVATE(self);
}

static void ct_im_cnr6_destructor(CtImCnr6 *self) 
{
//	CtImCnr6Private *priv = CT_IM_CNR6_GET_PRIVATE(self);
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_1: "
INT32 ct_im_cnr_ofl_2_1(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Ctrl(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_2: "
INT32 ct_im_cnr_ofl_2_2(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Ctrl_Axi(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_3: "
INT32 ct_im_cnr_ofl_2_3(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Get_AXI_Status(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_4: "
INT32 ct_im_cnr_ofl_2_4(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Ctrl_C(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_5: "
INT32 ct_im_cnr_ofl_2_5(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Ctrl_Y(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_6: "
INT32 ct_im_cnr_ofl_2_6(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Set_CSPR_Mid_Y_Table(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "CT_IM_CNR_OFL_2_7: "
INT32 CT_IM_CNR_OFL_2_7(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Set_CSPR_Mid_CC_Y_Table(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_8: "
INT32 ct_im_cnr_ofl_2_8(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Set_CSPR_Mid_CC_C_Table(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_9: "
INT32 ct_im_cnr_ofl_2_9(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Set_CSPR_Low_Y_Table(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_10: "
INT32 ct_im_cnr_ofl_2_10(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Set_CSPR_Low_CC_Y_Table(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "CT_IM_CNR_OFL_2_11: "
INT32 CT_IM_CNR_OFL_2_11(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Set_CSPR_Low_CC_C_Table(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_12: "
INT32 ct_im_cnr_ofl_2_12(CtImCnr6 *self)
{
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Set_YSPR_Table(0, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_13: "
INT32 ct_im_cnr_ofl_2_13(CtImCnr6 *self)
{
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Wait_End(0, NULL, 0);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_14: "
INT32 ct_im_cnr_ofl_2_14(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Ctrl_SPRS_CC(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}


#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_ofl_2_15: "
INT32 ct_im_cnr_ofl_2_15(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Ctrl_SPRD_CC(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_1: "
INT32 ct_im_cnr_otf_3_1(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 imErcd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_IM_CNR_SEM_TIMEOUT_ERR) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", imErcd));
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_2: "
INT32 ct_im_cnr_otf_3_2(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 imErcd;
	DDIM_USER_ID sidBack;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	sidBack = SID_IM_CNR_OTF(ch);
	SID_IM_CNR_OTF(ch) = 0xfff;

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_IM_CNR_SEM_NG) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		Im_CNR_OTF_Close(ch);
		return imErcd;
	}

	SID_IM_CNR_OTF(ch) = sidBack;

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_3: "
INT32 ct_im_cnr_otf_3_3(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 imErcd;
	T_IM_CNR_OTF_CTRL sprCtrl = {
		.mode = E_IM_CNR_OTF_YCC_MODE_YCC422_SIMPLE,

		.width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = CtImCnr_D_IM_CNR_TEST_V_PIXS,

		.w_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,

		.divide_left = E_IM_CNR_VPROCESS_NORM,
		.divide_right = E_IM_CNR_VPROCESS_NORM,

		.w_offset_x = 1000,

		.pCallBack = NULL,
		.user_param = 0,
	};
	T_IM_CNR_OTF_OUTADDR_INFO addrInfo = {
		.use_bank_num = 1,
		.w_c_addr[0] = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR,
	};
	T_IM_CNR_CTRL_C sprCtrlC = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
		.low_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Ctrl(ch, &sprCtrl);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Set_OutAddr_Info(ch, &addrInfo);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Set OutAddrInfo error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Ctrl_C(ch, &sprCtrlC);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_C error = 0x%x\n", imErcd));
		return imErcd;
	}

#ifdef CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE
	CtImCnr1 *ctim1 = ct_im_cnr1_new();
	ctim1->ch1 = ch;
	ct_im_cnr_set_im_r2y_set(ctim1);
	ct_im_cnr_set_im_r2y_start(ctim1);
	k_object_unref(ctim1);
#endif

	imErcd = Im_CNR_OTF_Start_Sync(ch, 10);
	if(imErcd != D_IM_CNR_SEM_TIMEOUT_ERR) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start Sync error = 0x%x\n", imErcd));
		Im_CNR_OTF_Close(ch);
		return imErcd;
	}

#ifdef CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE
	ct_im_cnr_set_im_r2y_stop(ch);
#endif

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_4: "
INT32 ct_im_cnr_otf_3_4(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 imErcd;
	UINT32 waitFactor;
#ifdef CO_DEBUG_ON_PC
	INT32 roop_count;
	ULONG out_addr;
#endif //CO_DEBUG_ON_PC
	T_IM_CNR_OTF_CTRL sprCtrl = {
		.mode = E_IM_CNR_OTF_YCC_MODE_YCC422_SIMPLE,

		.width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = CtImCnr_D_IM_CNR_TEST_V_PIXS,

		.w_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,

		.divide_left = E_IM_CNR_VPROCESS_NORM,
		.divide_right = E_IM_CNR_VPROCESS_NORM,

		.w_offset_x = 1000,

		.pCallBack = NULL,
		.user_param = 0,
	};
	T_IM_CNR_OTF_OUTADDR_INFO addrInfo = {
		.use_bank_num = 4,
		.w_c_addr[0] = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR,
		.w_c_addr[1] = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR + 0x1000,
		.w_c_addr[2] = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR + 0x2000,
		.w_c_addr[3] = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR + 0x3000,
	};
	T_IM_CNR_CTRL_C sprCtrlC = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
		.low_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}
	Im_CNR_OTF_Init(ch);


	imErcd = Im_CNR_OTF_Ctrl(ch, &sprCtrl);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Set_OutAddr_Info(ch, &addrInfo);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Set OutAddrInfo error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Ctrl_C(ch, &sprCtrlC);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_C error = 0x%x\n", imErcd));
		return imErcd;
	}

	Ddim_Print(("[Before Start]ch0 SPRACS = %u\n", io_cnr(D_IM_CNR_CH_0)->OTF_REG_RW.ACESEN.bit.SPRACS));
	Ddim_Print(("[Before Start]ch1 SPRACS = %u\n", io_cnr(D_IM_CNR_CH_1)->OTF_REG_RW.ACESEN.bit.SPRACS));

	imErcd = Im_CNR_OTF_Start_Async(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start Async error = 0x%x\n", imErcd));
		return imErcd;
	}

	Ddim_Print(("[After Start]ch0 SPRACS = %u\n", io_cnr(D_IM_CNR_CH_0)->OTF_REG_RW.ACESEN.bit.SPRACS));
	Ddim_Print(("[After Start]ch1 SPRACS = %u\n", io_cnr(D_IM_CNR_CH_1)->OTF_REG_RW.ACESEN.bit.SPRACS));

#ifdef CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE
	ct_im_cnr_set_im_r2y_set(ch);
	ct_im_cnr_set_im_r2y_start(ch);
#endif

#ifdef CO_DEBUG_ON_PC
	if(ch == D_IM_CNR_CH_2){
		io_cnr(D_IM_CNR_CH_0)->OTF_REG_RW.SPRICF.bit.__SPDF = 1;
		io_cnr(D_IM_CNR_CH_1)->OTF_REG_RW.SPRICF.bit.__SPDF = 1;
		Im_CNR0_Int_Handler();
		Im_CNR1_Int_Handler();
	}
	else{
		io_cnr(ch)->OTF_REG_RW.SPRICF.bit.__SPDF = 1;
		if(ch == D_IM_CNR_CH_0){
			Im_CNR0_Int_Handler();
		}
		else{
			Im_CNR1_Int_Handler();
		}
	}
#endif //CO_DEBUG_ON_PC

	imErcd = Im_CNR_OTF_Wait_End(ch, &waitFactor, 1000);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Wait End error = 0x%x\n", imErcd));
		return imErcd;
	}

#ifdef CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE
	ct_im_cnr_set_im_r2y_stop(ch);
#endif

#ifdef CO_DEBUG_ON_PC
	// check output address update
	for(roop_count=0; roop_count<12; roop_count++){
		if(ch == D_IM_CNR_CH_2){
			Im_CNR_OTF_Get_Latest_OutAddr(D_IM_CNR_CH_0, &out_addr);
			Ddim_Print(("Im_CNR_OTF_Get_Latest_OutAddr() = ch=0, 0x%lx\n", out_addr));
			Im_CNR_OTF_Get_Latest_OutAddr(D_IM_CNR_CH_1, &out_addr);
			Ddim_Print(("Im_CNR_OTF_Get_Latest_OutAddr() = ch=1, 0x%lx\n", out_addr));

			io_cnr(D_IM_CNR_CH_0)->OTF_REG_RW.SPRICF.bit.__SPDF = 1;
			io_cnr(D_IM_CNR_CH_1)->OTF_REG_RW.SPRICF.bit.__SPDF = 1;
			Im_CNR0_Int_Handler();
			Im_CNR1_Int_Handler();
		}
		else{
			Im_CNR_OTF_Get_Latest_OutAddr(ch, &out_addr);
			Ddim_Print(("Im_CNR_OTF_Get_Latest_OutAddr() = ch=%d, 0x%lx\n", ch, out_addr));

			io_cnr(ch)->OTF_REG_RW.SPRICF.bit.__SPDF = 1;
			if(ch == D_IM_CNR_CH_0){
				Im_CNR0_Int_Handler();
			}
			else{
				Im_CNR1_Int_Handler();
			}
		}
	}
#endif //CO_DEBUG_ON_PC


	Ddim_Print(("[After Stop]ch0 SPRACS = %u\n", io_cnr(D_IM_CNR_CH_0)->OTF_REG_RW.ACESEN.bit.SPRACS));
	Ddim_Print(("[After Stop]ch1 SPRACS = %u\n", io_cnr(D_IM_CNR_CH_1)->OTF_REG_RW.ACESEN.bit.SPRACS));

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_5: "
INT32 ct_im_cnr_otf_3_5(CtImCnr6 *self)
{

	INT32 imErcd;
#ifdef CO_DEBUG_ON_PC
	UINT32 waitFactor;
#endif //CO_DEBUG_ON_PC

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

#ifdef CO_DEBUG_ON_PC
	UCHAR ch = self->ch6;
	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Start_Async(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start Async error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Wait_End(ch, &waitFactor, 10);
	if(imErcd != D_IM_CNR_SEM_TIMEOUT_ERR) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Wait End error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}
#else //!CO_DEBUG_ON_PC
	Ddim_Print(("%s: Only debug on PC\n", D_IM_CNR_FUNC_NAME));
	imErcd = D_DDIM_SYSTEM_ERROR;
#endif //!CO_DEBUG_ON_PC

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_6: "
INT32 ct_im_cnr_otf_3_6(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 imErcd;
	UINT32 waitFactor;
	DDIM_USER_ID fidBack;
	T_IM_CNR_OTF_CTRL sprCtrl = {
		.mode = E_IM_CNR_OTF_YCC_MODE_YCC422_SIMPLE,

		.width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = CtImCnr_D_IM_CNR_TEST_V_PIXS,

		.w_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,

		.divide_left = E_IM_CNR_VPROCESS_NORM,
		.divide_right = E_IM_CNR_VPROCESS_NORM,

		.w_offset_x = 1000,

		.pCallBack = NULL,
		.user_param = 0,
	};
	T_IM_CNR_OTF_OUTADDR_INFO addrInfo = {
		.use_bank_num = 1,
		.w_c_addr[0] = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR,
	};
	T_IM_CNR_CTRL_C sprCtrlC = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
		.low_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
	};

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}


	imErcd = Im_CNR_OTF_Ctrl(ch, &sprCtrl);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Set_OutAddr_Info(ch, &addrInfo);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Set OutAddrInfo error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Ctrl_C(ch, &sprCtrlC);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_C error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Start_Async(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start Async error = 0x%x\n", imErcd));
		return imErcd;
	}

	fidBack = FID_IM_CNR;
	FID_IM_CNR = 0xfff;
	imErcd = Im_CNR_OTF_Wait_End(ch, &waitFactor, 10);
	if(imErcd != D_IM_CNR_SEM_NG) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Wait End error = 0x%x\n", imErcd));
		return imErcd;
	}

	FID_IM_CNR = fidBack;

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_7: "
INT32 ct_im_cnr_otf_3_7(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 imErcd;
	DDIM_USER_ID sidBack;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	sidBack = SID_IM_CNR_OTF(ch);
	SID_IM_CNR_OTF(ch) = 0xfff;

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_IM_CNR_SEM_NG) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	SID_IM_CNR_OTF(ch) = sidBack;

	return imErcd;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_3_8: "
INT32 ct_im_cnr_otf_3_8(CtImCnr6 *self)
{
	UCHAR ch = self->ch6;
	INT32 imErcd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	imErcd = Im_CNR_OTF_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
		return imErcd;
	}

	return imErcd;
}

INT32 ct_im_cnr_run_2(CtImCnr6 *self, const UINT32 ctNo2nd)
{
	
	Ddim_Print(("ct_im_cnr_run_2 ctNo2nd = 0x%x ctNo3rd = 0x%x\n", ctNo2nd, self->ch6));
	switch(ctNo2nd) {
		// Test-2-1
		case 1:
			return ct_im_cnr_ofl_2_1(self);

		// Test-2-2
		case 2:
			return ct_im_cnr_ofl_2_2(self);

		// Test-2-3
		case 3:
			return ct_im_cnr_ofl_2_3(self);

		// Test-2-4
		case 4:
			return ct_im_cnr_ofl_2_4(self);

		// Test-2-5
		case 5:
			return ct_im_cnr_ofl_2_5(self);

		// Test-2-6
		case 6:
			return ct_im_cnr_ofl_2_6(self);

		// Test-2-7
		case 7:
			return CT_IM_CNR_OFL_2_7(self);

		// Test-2-8
		case 8:
			return ct_im_cnr_ofl_2_8(self);

		// Test-2-9
		case 9:
			return ct_im_cnr_ofl_2_9(self);

		// Test-2-10
		case 10:
			return ct_im_cnr_ofl_2_10(self);

		// Test-2-11
		case 11:
			return CT_IM_CNR_OFL_2_11(self);

		// Test-2-12
		case 12:
			return ct_im_cnr_ofl_2_12(self);

		// Test-2-13
		case 13:
			return ct_im_cnr_ofl_2_13(self);

		// Test-2-14
		case 14:
			return ct_im_cnr_ofl_2_14(self);

		// Test-2-15
		case 15:
			return ct_im_cnr_ofl_2_15(self);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

CtImCnr6* ct_im_cnr6_new(void) 
{
    CtImCnr6 *self = g_object_new(CT_TYPE_IM_CNR6, NULL);
    return self;
}
