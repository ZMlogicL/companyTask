/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr14类
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
#include "ctimcnr14.h"

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr14, ct_im_cnr14, G_TYPE_OBJECT); 
#define CT_IM_CNR14_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR14, CtImCnr14Private))

struct _CtImCnr14Private
{
};

static void ct_im_cnr14_constructor(CtImCnr14 *self) 
{
//	CtImCnr14Private *priv = CT_IM_CNR14_GET_PRIVATE(self);
}

static void ct_im_cnr14_destructor(CtImCnr14 *self) 
{
//	CtImCnr14Private *priv = CT_IM_CNR14_GET_PRIVATE(self);
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_1: "
INT32 ct_im_cnr_otf_4_1(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Ctrl(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_2: "
INT32 ct_im_cnr_otf_4_2(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Ctrl_Axi(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_3: "
INT32 ct_im_cnr_otf_4_3(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Get_AXI_Status(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_4: "
INT32 ct_im_cnr_otf_4_4(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Ctrl_C(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_5: "
INT32 ct_im_cnr_otf_4_5(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Set_CSPR_Mid_Y_Table(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_6: "
INT32 ct_im_cnr_otf_4_6(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Set_CSPR_Mid_CC_Y_Table(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_7: "
INT32 ct_im_cnr_otf_4_7(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Set_CSPR_Mid_CC_C_Table(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_8: "
INT32 ct_im_cnr_otf_4_8(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Set_CSPR_Low_Y_Table(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_9: "
INT32 ct_im_cnr_otf_4_9(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Set_CSPR_Low_CC_Y_Table(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_10: "
INT32 ct_im_cnr_otf_4_10(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Set_CSPR_Low_CC_C_Table(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_11: "
INT32 ct_im_cnr_otf_4_11(CtImCnr14 *self)
{
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Wait_End(0, NULL, 0);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_12: "
INT32 ct_im_cnr_otf_4_12(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Ctrl_SPRS_CC(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_13: "
INT32 ct_im_cnr_otf_4_13(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Ctrl_SPRD_CC(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_14: "
INT32 ct_im_cnr_otf_4_14(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Get_Latest_OutAddr(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_otf_4_15: "
INT32 ct_im_cnr_otf_4_15(CtImCnr14 *self)
{
	UCHAR ch = self->ch14;
	INT32 ercd;

	Ddim_Print(("%s\n", D_IM_CNR_FUNC_NAME));

	ercd = Im_CNR_OTF_Set_OutAddr_Info(ch, NULL);
	Ddim_Print((D_IM_CNR_FUNC_NAME "result = 0x%x\n", ercd));

	return D_DDIM_OK;
}

INT32 ct_im_cnr_run_4(CtImCnr14 *self, const UINT32 ctNo2nd)
{
	Ddim_Print(("ct_im_cnr_run_4 ctNo2nd = 0x%x ctNo3rd = 0x%x\n", ctNo2nd, self->ch14));
	switch(ctNo2nd) {
		// Test-4-1
		case 1:
			return ct_im_cnr_otf_4_1(self);

		// Test-4-2
		case 2:
			return ct_im_cnr_otf_4_2(self);

		// Test-4-3
		case 3:
			return ct_im_cnr_otf_4_3(self);

		// Test-4-4
		case 4:
			return ct_im_cnr_otf_4_4(self);

		// Test-4-5
		case 5:
			return ct_im_cnr_otf_4_5(self);

		// Test-4-6
		case 6:
			return ct_im_cnr_otf_4_6(self);

		// Test-4-7
		case 7:
			return ct_im_cnr_otf_4_7(self);

		// Test-4-8
		case 8:
			return ct_im_cnr_otf_4_8(self);

		// Test-4-9
		case 9:
			return ct_im_cnr_otf_4_9(self);

		// Test-4-10
		case 10:
			return ct_im_cnr_otf_4_10(self);

		// Test-4-11
		case 11:
			return ct_im_cnr_otf_4_11(self);

		// Test-4-12
		case 12:
			return ct_im_cnr_otf_4_12(self);

		// Test-4-13
		case 13:
			return ct_im_cnr_otf_4_13(self);

		// Test-4-14
		case 14:
			return ct_im_cnr_otf_4_14(self);

		// Test-4-15
		case 15:
			return ct_im_cnr_otf_4_15(self);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

CtImCnr14* ct_im_cnr14_new(void) 
{
    CtImCnr14 *self = g_object_new(CT_TYPE_IM_CNR14, NULL);
    return self;
}
