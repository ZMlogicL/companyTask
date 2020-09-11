/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr12类
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
#include "ctimcnr12.h"

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr12, ct_im_cnr12, G_TYPE_OBJECT); 
#define CT_IM_CNR12_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR12, CtImCnr12Private))

struct _CtImCnr12Private
{

};

static void ct_im_cnr12_constructor(CtImCnr12 *self) 
{
//	CtImCnr12Private *priv = CT_IM_CNR12_GET_PRIVATE(self);
}

static void ct_im_cnr12_destructor(CtImCnr12 *self) 
{
//	CtImCnr12Private *priv = CT_IM_CNR12_GET_PRIVATE(self);
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_5_1: "
INT32 ct_im_cnr_5_1(CtImCnr12 *self)
{
	UCHAR ch = self->ch1;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OFL_Init(ch);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_5_2: "
INT32 ct_im_cnr_5_2(CtImCnr12 *self)
{
	UCHAR ch = self->ch1;
	INT32 imErcd;
	T_IM_CNR_OFL_CTRL sprCtrl = {
		.mode = E_IM_CNR_OFL_YCC_MODE_YCC422_SIMPLE,

		.width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = CtImCnr_D_IM_CNR_TEST_V_PIXS,

		.r_y_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.r_y_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_Y_ADDR,

		.r_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.r_cb_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_CB_ADDR,
		.r_cr_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_CR_ADDR,

		.w_y_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.w_y_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_Y_ADDR,

		.w_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.w_cb_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR,
		.w_cr_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_CR_ADDR,

		.work_addr = CtImCnr_D_IM_CNR_TEST_IMG_TMP_ADDR,

		.divide_top = E_IM_CNR_VPROCESS_NORM,
		.divide_bot = E_IM_CNR_VPROCESS_NORM,

		.pCallBack = NULL,
		.user_param = 0,
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
	T_IM_CNR_OFL_CTRL_Y sprCtrlY = {
		.enable = E_IM_CNR_ONOFF_DISABLE,
		.threshold_type = E_IM_CNR_THRES_REGISTER,
		.level = E_IM_CNR_LEVEL_HIGH,
		.h_y_threshold = 0xFF,
		.v_y_threshold = 0xFF,
		.h_c_threshold = 0xFF,
		.v_c_threshold = 0xFF,
		.alpha_blend_ratio = 0x1F,
	};

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl(ch, &sprCtrl);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl_C(ch, &sprCtrlC);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_C error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl_Y(ch, &sprCtrlY);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_Y error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Start_Sync(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start error = 0x%x\n", imErcd));
	}

	imErcd = Im_CNR_OFL_Stop(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Stop error = 0x%x\n", imErcd));
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_5_3: "
INT32 ct_im_cnr_5_3(CtImCnr12 *self)
{
	UCHAR ch = self->ch1;
	INT32 imErcd;
	T_IM_CNR_OFL_CTRL sprCtrl = {
		.mode = E_IM_CNR_OFL_YCC_MODE_YCC422,

		.width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = CtImCnr_D_IM_CNR_TEST_V_PIXS,

		.r_y_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.r_y_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_Y_ADDR,

		.r_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.r_cb_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_CB_ADDR,
		.r_cr_addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_CR_ADDR,

		.w_y_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.w_y_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_Y_ADDR,

		.w_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.w_cb_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR,
		.w_cr_addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_CR_ADDR,

		.work_addr = CtImCnr_D_IM_CNR_TEST_IMG_TMP_ADDR,

		.divide_top = E_IM_CNR_VPROCESS_NORM,
		.divide_bot = E_IM_CNR_VPROCESS_NORM,

		.pCallBack = NULL,
		.user_param = 0,
	};
	T_IM_CNR_CTRL_C sprCtrlC = {
		.enable = E_IM_CNR_ONOFF_DISABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_DISABLE,
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
			.enable = E_IM_CNR_ONOFF_DISABLE,
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
	T_IM_CNR_OFL_CTRL_Y sprCtrlY = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.threshold_type = E_IM_CNR_THRES_REGISTER,
		.level = E_IM_CNR_LEVEL_HIGH,
		.h_y_threshold = 0xFF,
		.v_y_threshold = 0xFF,
		.h_c_threshold = 0xFF,
		.v_c_threshold = 0xFF,
		.alpha_blend_ratio = 0,
	};

	imErcd = Im_CNR_OFL_Open(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Open error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl(ch, &sprCtrl);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl_C(ch, &sprCtrlC);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_C error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Ctrl_Y(ch, &sprCtrlY);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Ctrl_Y error = 0x%x\n", imErcd));
		return imErcd;
	}

	imErcd = Im_CNR_OFL_Start_Sync(ch, 100);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start error = 0x%x\n", imErcd));
	}

	imErcd = Im_CNR_OFL_Stop(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Stop error = 0x%x\n", imErcd));
	}

	imErcd = Im_CNR_OFL_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_5_4: "
INT32 ct_im_cnr_5_4(CtImCnr12 *self)
{
	self->ch1 = 1;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));
	ercd = ct_im_cnr_5_1(self);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_5_5: "
INT32 ct_im_cnr_5_5(CtImCnr12 *self)
{
	self->ch1 = 1;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));
	ercd = ct_im_cnr_5_2(self);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_5_6: "
INT32 ct_im_cnr_5_6(CtImCnr12 *self)
{
	self->ch1 = 1;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));
	ercd = ct_im_cnr_5_3(self);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_5_7: "
INT32 ct_im_cnr_5_7(CtImCnr12 *self)
{
	UCHAR ch = self->ch1;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Init(ch);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_5_8: "
INT32 ct_im_cnr_5_8(CtImCnr12 *self)
{
	UCHAR ch = self->ch1;
	INT32 imErcd;
	UINT32 waitFactor;
	T_IM_CNR_OTF_CTRL sprCtrl = {
		.mode = E_IM_CNR_OTF_YCC_MODE_YCC422_SIMPLE,

		.width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = CtImCnr_D_IM_CNR_TEST_V_PIXS,

		.w_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,

		.divide_left = E_IM_CNR_VPROCESS_NORM,
		.divide_right = E_IM_CNR_VPROCESS_NORM,

		.pCallBack = NULL,
		.user_param = 0,
	};
	T_IM_CNR_OTF_OUTADDR_INFO addrInfo = {
		.use_bank_num= 1,
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
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start error = 0x%x\n", imErcd));
	}

#ifdef CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE
	CtImCnr1 *ctim1 = ct_im_cnr1_new();
	ctim1->ch1 = ch;
	imErcd = ct_im_cnr_set_im_r2y_set(ctim1);
	k_object_unref(ctim1);

	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "ct_im_cnr_set_im_r2y_set error = 0x%x\n", imErcd));
		return imErcd;
	}
	imErcd = ct_im_cnr_set_im_r2y_start(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "ct_im_cnr_set_im_r2y_start error = 0x%x\n", imErcd));
		return imErcd;
	}
#endif	// CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE

	imErcd = Im_CNR_OTF_Wait_End(ch, &waitFactor, 1000);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Wait End error = 0x%x\n", imErcd));
	}

	imErcd = Im_CNR_OTF_Stop(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Stop error = 0x%x\n", imErcd));
	}

#ifdef CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE
	imErcd = ct_im_cnr_set_im_r2y_stop(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "ct_im_cnr_set_im_r2y_stop error = 0x%x\n", imErcd));
		return imErcd;
	}
#endif	// CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_5_9: "
INT32 ct_im_cnr_5_9(CtImCnr12 *self)
{
	UCHAR ch = self->ch1;
	INT32 imErcd;
	UINT32 waitFactor;
	T_IM_CNR_OTF_CTRL sprCtrl = {
		.mode = E_IM_CNR_OTF_YCC_MODE_YCC422_SIMPLE,

		.width = CtImCnr_D_IM_CNR_TEST_H_PIXS,
		.lines = CtImCnr_D_IM_CNR_TEST_V_PIXS,

		.w_c_width = CtImCnr_D_IM_CNR_TEST_H_PIXS,

		.divide_left = E_IM_CNR_VPROCESS_NORM,
		.divide_right = E_IM_CNR_VPROCESS_NORM,

		.pCallBack = NULL,
		.user_param = 0,
	};
	T_IM_CNR_OTF_OUTADDR_INFO addrInfo = {
		.use_bank_num= 1,
		.w_c_addr[0] = CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR,
	};
	T_IM_CNR_CTRL_C sprCtrlC = {
		.enable = E_IM_CNR_ONOFF_DISABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_DISABLE,
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
			.enable = E_IM_CNR_ONOFF_DISABLE,
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
		Ddim_Print((D_IM_CNR_FUNC_NAME "Start error = 0x%x\n", imErcd));
	}

#ifdef CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE
	CtImCnr1 *ctim1 = ct_im_cnr1_new();
	ctim1->ch1 = ch;
	imErcd = ct_im_cnr_set_im_r2y_set(ctim1);
	k_object_unref(ctim1);
	
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "ct_im_cnr_set_im_r2y_set error = 0x%x\n", imErcd));
		return imErcd;
	}
	imErcd = ct_im_cnr_set_im_r2y_start(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "ct_im_cnr_set_im_r2y_start error = 0x%x\n", imErcd));
		return imErcd;
	}
#endif	// CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE

	imErcd = Im_CNR_OTF_Wait_End(ch, &waitFactor, 1000);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Wait End error = 0x%x\n", imErcd));
	}

	imErcd = Im_CNR_OTF_Stop(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Stop error = 0x%x\n", imErcd));
	}

#ifdef CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE
	imErcd = ct_im_cnr_set_im_r2y_stop(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "ct_im_cnr_set_im_r2y_stop error = 0x%x\n", imErcd));
		return imErcd;
	}
#endif	// CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE

	imErcd = Im_CNR_OTF_Close(ch);
	if(imErcd != D_DDIM_OK) {
		Ddim_Print((D_IM_CNR_FUNC_NAME "Close error = 0x%x\n", imErcd));
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_5_10: "
INT32 ct_im_cnr_5_10(CtImCnr12 *self)
{
	self->ch1 = 1;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));
	ercd = ct_im_cnr_5_7(self);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_5_11: "
INT32 ct_im_cnr_5_11(CtImCnr12 *self)
{
	self->ch1 = 1;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));
	ercd = ct_im_cnr_5_8(self);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_5_12: "
INT32 ct_im_cnr_5_12(CtImCnr12 *self)
{
	self->ch1 = 1;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));
	ercd = ct_im_cnr_5_9(self);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

INT32 ct_im_cnr_run_5(CtImCnr12 *self, const UINT32 ct_no_2nd)
{
	
	self->ch1 = 0;

	Ddim_Print(("ct_im_cnr_run_5 ct_no_2nd = 0x%x\n", ct_no_2nd));
	switch(ct_no_2nd) {
		// Test-5-1
		case 1:
			return ct_im_cnr_5_1(self);

		// Test-5-2
		case 2:
			return ct_im_cnr_5_2(self);

		// Test-5-3
		case 3:
			return ct_im_cnr_5_3(self);

		// Test-5-4
		case 4:
			return ct_im_cnr_5_4(self);

		// Test-5-5
		case 5:
			return ct_im_cnr_5_5(self);

		// Test-5-6
		case 6:
			return ct_im_cnr_5_6(self);

		// Test-5-7
		case 7:
			return ct_im_cnr_5_7(self);

		// Test-5-8
		case 8:
			return ct_im_cnr_5_8(self);

		// Test-5-9
		case 9:
			return ct_im_cnr_5_9(self);

		// Test-5-10
		case 10:
			return ct_im_cnr_5_10(self);

		// Test-5-11
		case 11:
			return ct_im_cnr_5_11(self);

		// Test-5-12
		case 12:
			return ct_im_cnr_5_12(self);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

CtImCnr12* ct_im_cnr12_new(void) 
{
    CtImCnr12 *self = g_object_new(CT_TYPE_IM_CNR12, NULL);
    return self;
}
