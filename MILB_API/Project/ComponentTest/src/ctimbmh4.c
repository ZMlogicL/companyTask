/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh4类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include <string.h>
#include <stdlib.h>
#include "im_bmh.h"
#include "dd_top.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#include "jmlbmh.h"
#include "ctimbmh.h"
#include "ctimbmh1.h"
#include "ctimbmh2.h"
#include "ctimbmh3.h"
#include "ctimbmh4.h"
#include "ctimbmh5.h"
#include "ctimbmh6.h"
#include "ctimbmh7.h"
#include "ctimbmh8.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImBmh4, ct_im_bmh4);
#define CT_IM_BMH4_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImBmh4Private,CT_TYPE_IM_BMH4))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// nothing special.

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// nothing special.

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// nothing special.

struct _CtImBmh4Private
{
	kint32 ercd;
	kuchar channelNo;
};

static void ct_im_bmh4_constructor(CtImBmh4 *self) 
{
//	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
}

static void ct_im_bmh4_destructor(CtImBmh4 *self) 
{
//	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
}

/*
 * PUBLIC
 */
kint32 ct_im_bmh4_2_1(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_1: "));

	priv->ercd = Im_BMH_Ctrl(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_1: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_2(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_2: "));

	priv->ercd = Im_BMH_Get_Ctrl(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_2: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_3(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_3: "));

	priv->ercd = Im_BMH_Set_Bmhre(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_3: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_4(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_4: "));

	priv->ercd = Im_BMH_Get_Bmhre(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_4: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_5(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_5: "));

	priv->ercd = Im_BMH_Get_Rsst(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_5: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_6(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_6: "));

	priv->ercd = Im_BMH_Set_Bmhcont(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_6: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_7(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_7: "));

	priv->ercd = Im_BMH_Get_Bmhcont(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_7: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_8(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_8: "));

	priv->ercd = Im_BMH_Set_Bmhaxi(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_8: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_9(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_9: "));

	priv->ercd = Im_BMH_Get_Bmhaxierr(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_9: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_10(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_10: "));

	priv->ercd = Im_BMH_Set_Bmhhcnt(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_10: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_11(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_11: "));

	priv->ercd = Im_BMH_Get_Bmhhcnt(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_11: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_12(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_12: "));

	priv->ercd = Im_BMH_Set_Bmhsad_wr(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_12: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_13(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_13: "));

	priv->ercd = Im_BMH_Get_Bmhsad_wr(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_13: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_14(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_14: "));

	priv->ercd = Im_BMH_Ctrl_Dma(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_14: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_15(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_15: "));

	priv->ercd = Im_BMH_Get_Ctrl_Dma(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_15: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_16(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_16: "));

	priv->ercd = Im_BMH_Set_Lut(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_16: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_17(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;
	kushort interrupt_bit = 0;
	kuchar permission_flg = 2;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_17: "));

	priv->ercd = Im_BMH_Set_Interrupt(priv->channelNo, interrupt_bit, permission_flg);
	Ddim_Print(("ct_im_bmh4_2_17: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_18(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_18: "));

	priv->ercd = Im_BMH_Set_Cur(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_18: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_19(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_19: "));

	priv->ercd = Im_BMH_Set_Ref(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_19: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_20(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_20: "));

	priv->ercd = Im_BMH_Get_Sadr_000(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_20: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_21(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_21: "));

	priv->ercd = Im_BMH_Get_Sadr_001(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_21: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_22(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_22: "));

	priv->ercd = Im_BMH_Get_Sadr_010(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_22: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_23(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_23: "));

	priv->ercd = Im_BMH_Get_Sadr_011(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_23: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_24(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_24: "));

	priv->ercd = Im_BMH_Get_Sadr_100(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_24: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_25(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_25: "));

	priv->ercd = Im_BMH_Get_Sadr_101(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_25: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_26(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_26: "));

	priv->ercd = Im_BMH_Get_Sadr_110(priv->channelNo, NULL);
	Ddim_Print(("ct_im_bmh4_2_26: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_27(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_CTRL bmh_ctrl;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_27: "));

	priv->ercd = Im_BMH_Ctrl(priv->channelNo, &bmh_ctrl);
	Ddim_Print(("ct_im_bmh4_2_27: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_28(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_CTRL bmh_ctrl;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_28: "));

	priv->ercd = Im_BMH_Get_Ctrl(priv->channelNo, &bmh_ctrl);
	Ddim_Print(("ct_im_bmh4_2_28: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_29(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_BMHRE sram;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_29: "));

	priv->ercd = Im_BMH_Set_Bmhre(priv->channelNo, &sram);
	Ddim_Print(("ct_im_bmh4_2_29: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_30(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_BMHRE sram;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_30: "));

	priv->ercd = Im_BMH_Get_Bmhre(priv->channelNo, &sram);
	Ddim_Print(("ct_im_bmh4_2_30: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_31(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_RSST rsst;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_31: "));

	priv->ercd = Im_BMH_Get_Rsst(priv->channelNo, &rsst);
	Ddim_Print(("ct_im_bmh4_2_31: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_32(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_BMHCONT cont;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_32: "));

	priv->ercd = Im_BMH_Set_Bmhcont(priv->channelNo, &cont);
	Ddim_Print(("ct_im_bmh4_2_32: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_33(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_BMHCONT cont;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_33: "));

	priv->ercd = Im_BMH_Get_Bmhcont(priv->channelNo, &cont);
	Ddim_Print(("ct_im_bmh4_2_33: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_34(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_AXI axi_ctrl;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_34: "));

	priv->ercd = Im_BMH_Set_Bmhaxi(priv->channelNo, &axi_ctrl);
	Ddim_Print(("ct_im_bmh4_2_34: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_35(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_AXI_STATUS sts;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_35: "));

	priv->ercd = Im_BMH_Get_Bmhaxierr(priv->channelNo, &sts);
	Ddim_Print(("ct_im_bmh4_2_35: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_36(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_BMHHCNT cnt;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_36: "));

	priv->ercd = Im_BMH_Set_Bmhhcnt(priv->channelNo, &cnt);
	Ddim_Print(("ct_im_bmh4_2_36: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_37(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_BMHHCNT cnt;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_37: "));

	priv->ercd = Im_BMH_Get_Bmhhcnt(priv->channelNo, &cnt);
	Ddim_Print(("ct_im_bmh4_2_37: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_38(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_BMHSAD_WR sad_wr;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_38: "));

	priv->ercd = Im_BMH_Set_Bmhsad_wr(priv->channelNo, &sad_wr);
	Ddim_Print(("ct_im_bmh4_2_38: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_39(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_BMHSAD_WR sad_wr;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_39: "));

	priv->ercd = Im_BMH_Get_Bmhsad_wr(priv->channelNo, &sad_wr);
	Ddim_Print(("ct_im_bmh4_2_39: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_40(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_CTRL_DMA bmh_ctrl_dma;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_40: "));

	priv->ercd = Im_BMH_Ctrl_Dma(priv->channelNo, &bmh_ctrl_dma);
	Ddim_Print(("ct_im_bmh4_2_40: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_41(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_CTRL_DMA bmh_ctrl_dma;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_41: "));

	priv->ercd = Im_BMH_Get_Ctrl_Dma(priv->channelNo, &bmh_ctrl_dma);
	Ddim_Print(("ct_im_bmh4_2_41: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_42(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_LUT lut_data;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_42: "));

	priv->ercd = Im_BMH_Set_Lut(priv->channelNo, &lut_data);
	Ddim_Print(("ct_im_bmh4_2_42: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_43(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	kushort interrupt_bit = 0;
	kuchar permission_flg = 0;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_43: "));

	priv->ercd = Im_BMH_Set_Interrupt(priv->channelNo, interrupt_bit, permission_flg);
	Ddim_Print(("ct_im_bmh4_2_43: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_44(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_CUR_BLOCK cur_write_data;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_44: "));

	priv->ercd = Im_BMH_Set_Cur(priv->channelNo, &cur_write_data);
	Ddim_Print(("ct_im_bmh4_2_44: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_45(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_REF_BLOCK ref_write_data;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_45: "));

	priv->ercd = Im_BMH_Set_Ref(priv->channelNo, &ref_write_data);
	Ddim_Print(("ct_im_bmh4_2_45: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_46(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_SADR_000 sadr_read_data;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_46: "));

	priv->ercd = Im_BMH_Get_Sadr_000(priv->channelNo, &sadr_read_data);
	Ddim_Print(("ct_im_bmh4_2_46: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_47(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_SADR_001 sadr_read_data;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_47: "));

	priv->ercd = Im_BMH_Get_Sadr_001(priv->channelNo, &sadr_read_data);
	Ddim_Print(("ct_im_bmh4_2_47: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_48(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_SADR_010 sadr_read_data;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_48: "));

	priv->ercd = Im_BMH_Get_Sadr_010(priv->channelNo, &sadr_read_data);
	Ddim_Print(("ct_im_bmh4_2_48: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_49(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_SADR_011 sadr_read_data;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_49: "));

	priv->ercd = Im_BMH_Get_Sadr_011(priv->channelNo, &sadr_read_data);
	Ddim_Print(("ct_im_bmh4_2_49: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_50(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_SADR_100 sadr_read_data;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_50: "));

	priv->ercd = Im_BMH_Get_Sadr_100(priv->channelNo, &sadr_read_data);
	Ddim_Print(("ct_im_bmh4_2_50: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_51(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_SADR_101 sadr_read_data;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_51: "));

	priv->ercd = Im_BMH_Get_Sadr_101(priv->channelNo, &sadr_read_data);
	Ddim_Print(("ct_im_bmh4_2_51: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

kint32 ct_im_bmh4_2_52(CtImBmh4 *self)
{
	CtImBmh4Private *priv = CT_IM_BMH4_GET_PRIVATE(self);
	priv->channelNo = 2;
	T_IM_BMH_SADR_110 sadr_read_data;

	Ddim_Print(("%s\n", "ct_im_bmh4_2_52: "));

	priv->ercd = Im_BMH_Get_Sadr_110(priv->channelNo, &sadr_read_data);
	Ddim_Print(("ct_im_bmh4_2_52: " "result = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

CtImBmh4* ct_im_bmh4_new(void) 
{
    CtImBmh4 *self = k_object_new_with_private(CT_TYPE_IM_BMH4, sizeof(CtImBmh4Private));
    return self;
}
