/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh1类
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

K_TYPE_DEFINE_WITH_PRIVATE(CtImBmh1, ct_im_bmh1);
#define CT_IM_BMH1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImBmh1Private,CT_TYPE_IM_BMH1))

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

struct _CtImBmh1Private
{
	kint32 imErcd;
	kuchar loopcnt;

	// Im_BMH *ib = im_bmh_new();
};

/*
 * DECLS
 */
static void ctImBmh1PrintDebugReg(CtImBmh1 *self);
static void ctImBmh1Callback_cb(kulong interruptFlagMask);//回调方法被其他文件调用

static void ct_im_bmh1_constructor(CtImBmh1 *self) 
{
//	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
}

static void ct_im_bmh1_destructor(CtImBmh1 *self) 
{
//	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
}

/*
 * IMPL
 */
static void ctImBmh1PrintDebugReg(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	for(priv->loopcnt = 0; priv->loopcnt < 2; priv->loopcnt++){
		Ddim_Print(("IO_BMH[%d]\n",                  priv->loopcnt));
		Ddim_Print(("\tBMHSR-SR             = 0x%x\n",  IO_BMH[priv->loopcnt].BMHSR.bit.SR));
		Ddim_Print(("\tBMHTRG-BMHTRG        = 0x%x\n",  IO_BMH[priv->loopcnt].BMHTRG.bit.BMHTRG));
		Ddim_Print(("\tBMHRE-BMHRE          = 0x%x\n",  IO_BMH[priv->loopcnt].BMHRE.bit.BMHRE));
		Ddim_Print(("\tBMHCONT-CONT         = 0x%x\n",  IO_BMH[priv->loopcnt].BMHCONT.bit.CONT));
		Ddim_Print(("\tBMHINTFS-__RSST      = 0x%x\n",  IO_BMH[priv->loopcnt].BMHINTFS.bit.__RSST));
		Ddim_Print(("\tBMHINTFS-__AXIF      = 0x%x\n",  IO_BMH[priv->loopcnt].BMHINTFS.bit.__AXIF));
		Ddim_Print(("\tBMHINTFS-__BMHF      = 0x%x\n",  IO_BMH[priv->loopcnt].BMHINTFS.bit.__BMHF));
		Ddim_Print(("\tBMHINTE-AXIE         = 0x%x\n",  IO_BMH[priv->loopcnt].BMHINTE.bit.AXIE));
		Ddim_Print(("\tBMHINTE-BMHE         = 0x%x\n",  IO_BMH[priv->loopcnt].BMHINTE.bit.BMHE));
		Ddim_Print(("\tBMHMD-MODE           = 0x%x\n",  IO_BMH[priv->loopcnt].BMHMD.bit.MODE));
		Ddim_Print(("\tBMHMD-OFFMD          = 0x%x\n",  IO_BMH[priv->loopcnt].BMHMD.bit.OFFMD));
		Ddim_Print(("\tBMHMD-LUTMD          = 0x%x\n",  IO_BMH[priv->loopcnt].BMHMD.bit.LUTMD));
		Ddim_Print(("\tBMHMD-OUTMD          = 0x%x\n",  IO_BMH[priv->loopcnt].BMHMD.bit.OUTMD));
		Ddim_Print(("\tBMHMD-PSHIFT         = 0x%x\n",  IO_BMH[priv->loopcnt].BMHMD.bit.PSHIFT));
		Ddim_Print(("\tBMHMD-RBS            = 0x%x\n",  IO_BMH[priv->loopcnt].BMHMD.bit.RBS));
		Ddim_Print(("\tBMHMD-LSELCNT        = 0x%x\n",  IO_BMH[priv->loopcnt].BMHMD.bit.LSELCNT));
		Ddim_Print(("\tBMHPRM-SADLV         = 0x%x\n",  IO_BMH[priv->loopcnt].BMHPRM.bit.SADLV));
		Ddim_Print(("\tBMHPRM-POFFSET       = 0x%x\n",  IO_BMH[priv->loopcnt].BMHPRM.bit.POFFSET));
		Ddim_Print(("\tBMHHCNT-RCNT         = 0x%x\n",  IO_BMH[priv->loopcnt].BMHHCNT.bit.RCNT));
		Ddim_Print(("\tBMHHCNT-HCNT         = 0x%x\n",  IO_BMH[priv->loopcnt].BMHHCNT.bit.HCNT));
		Ddim_Print(("\tBMHSAD_WR-SAD_WR     = 0x%x\n",  IO_BMH[priv->loopcnt].BMHSAD_WR.bit.SAD_WR));
		Ddim_Print(("\tBMHDMA-DMAMD         = 0x%x\n",  IO_BMH[priv->loopcnt].BMHDMA.bit.DMAMD));
		Ddim_Print(("\tBMHGHSIZE-GHSIZE_REF = 0x%x\n",  IO_BMH[priv->loopcnt].BMHGHSIZE.bit.GHSIZE_REF));
		Ddim_Print(("\tBMHGHSIZE-GHSIZE_CUR = 0x%x\n",  IO_BMH[priv->loopcnt].BMHGHSIZE.bit.GHSIZE_CUR));
		Ddim_Print(("\tBMHHSIZE-HSIZE_REF   = 0x%x\n",  IO_BMH[priv->loopcnt].BMHHSIZE.bit.HSIZE_REF));
		Ddim_Print(("\tBMHVSIZE-VSIZE_REF   = 0x%x\n",  IO_BMH[priv->loopcnt].BMHVSIZE.bit.VSIZE_REF));
		Ddim_Print(("\tBMHCURAD-CURSTAD     = 0x%lx\n", IO_BMH[priv->loopcnt].BMHCURAD.bit.CURSTAD));
		Ddim_Print(("\tBMHREFAD-REFSTAD     = 0x%lx\n", IO_BMH[priv->loopcnt].BMHREFAD.bit.REFSTAD));
		Ddim_Print(("\tBMHSADAD-SADSTAD     = 0x%lx\n", IO_BMH[priv->loopcnt].BMHSADAD.bit.SADSTAD));
		Ddim_Print(("\tBMHSADGH-SADGHSIZE   = 0x%x\n",  IO_BMH[priv->loopcnt].BMHSADGH.bit.SADGHSIZE));
		Ddim_Print(("\tBMHAXICTRL-ARCACHE   = 0x%x\n",  IO_BMH[priv->loopcnt].BMHAXICTRL.bit.ARCACHE));
		Ddim_Print(("\tBMHAXICTRL-ARPROT    = 0x%x\n",  IO_BMH[priv->loopcnt].BMHAXICTRL.bit.ARPROT));
		Ddim_Print(("\tBMHAXICTRL-AWCACHE   = 0x%x\n",  IO_BMH[priv->loopcnt].BMHAXICTRL.bit.AWCACHE));
		Ddim_Print(("\tBMHAXICTRL-AWPROT    = 0x%x\n",  IO_BMH[priv->loopcnt].BMHAXICTRL.bit.AWPROT));
		Ddim_Print(("\tBMHAXIERR-RRESP      = 0x%x\n",  IO_BMH[priv->loopcnt].BMHAXIERR.bit.RRESP));
		Ddim_Print(("\tBMHAXIERR-WRESP      = 0x%x\n",  IO_BMH[priv->loopcnt].BMHAXIERR.bit.WRESP));
		Ddim_Print(("\n"));
	}
}

void ctImBmh1Callback_cb(kulong interruptFlagMask)
{
	Ddim_Print(("ctImBmh1Callback_cb interruptFlagMask = 0x%lx\n", interruptFlagMask));
}

/*
 * PUBLIC
 */
kint32 ct_im_bmh1_1_1(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);

	Ddim_Print(("%s\n", "ct_im_bmh1_1_1: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_1: " "Open0 error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);
	if(priv->imErcd != D_IM_BMH_SEM_TIMEOUT_ERR){
		Ddim_Print(("ct_im_bmh1_1_1: " "Open1 error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_1: " "Close error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_2(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);	
	DDIM_USER_ID sidBack;

	Ddim_Print(("%s\n", "ct_im_bmh1_1_2: "));

	sidBack = SID_IM_BMH(self->channelNo);
	SID_IM_BMH(self->channelNo) = 0xfff;

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_2: " "Open error = 0x%x\n", priv->imErcd));
		SID_IM_BMH(self->channelNo) = sidBack;
		return priv->imErcd;
	}

	SID_IM_BMH(self->channelNo) = sidBack;

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_3(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	kuint32 i, j;

	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 32; j++){
			cur_write_data.cur_write_flg[i][j] = 1;
			cur_write_data.cur_data[i][j] = j + 2;
			ref_write_data.ref_write_flg[i][j] = 1;
			ref_write_data.ref_data[i][j] = j;
		}
	}

	Ddim_Print(("%s\n", "ct_im_bmh1_1_3: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_3: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_3: " "Set Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_3: " "Set Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 10);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_3: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_3: " "Close error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_4(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	kuint32 waitFactor;
	kuint32 i, j;
	T_IM_BMH_CTRL bmh_ctrl = {
		.lselcnt = 0,
		.rbs = 0,
		.pshift = 0,
		.outmd = 0,
		.lutmd = 0,
		.offmd = 0,
		.mode = 1,
		.poffset = 0,
		.sadlv = 0,
		.pCallBack = ctImBmh1Callback_cb,
	};
	T_IM_BMH_BMHHCNT cnt = {
		.hcnt = 0,
		.rcnt = 0,
	};

	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 256; j++){
			cur_write_data.cur_write_flg[i][j] = 1;
			cur_write_data.cur_data[i][j] = j;
			ref_write_data.ref_write_flg[i][j] = 1;
			ref_write_data.ref_data[i][j] = j / 2;
		}
	}

	Ddim_Print(("%s\n", "ct_im_bmh1_1_4: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_4: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Init(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_4: " "Init error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_4: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Interrupt(self->channelNo, D_IM_BMH_FLG_BMH_END | D_IM_BMH_FLG_BMH_AXI_ERR, 1);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_4: " "Interrupt error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Bmhhcnt(self->channelNo, &cnt);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_4: " "Set Bmhhcnt error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_4: " "Set Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_4: " "Set Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Async(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_4: " "Start Async error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
	IO_BMH[self->channelNo].BMHINTFS.bit.__BMHF = 1;
	Im_BMH_Int_Handler(self->channelNo);
#endif //CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Wait_End(self->channelNo, &waitFactor, 1000);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_4: " "Wait End error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_4: " "Close error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_5(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
#ifdef CO_DEBUG_ON_PC
	kuint32 waitFactor;
#endif //CO_DEBUG_ON_PC

	Ddim_Print(("%s\n", "ct_im_bmh1_1_5: "));

#ifdef CO_DEBUG_ON_PC
	priv->imErcd = Im_BMH_Open(self->channelNo, 100);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_5: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Async(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_5: " "Start Async error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Wait_End(self->channelNo, &waitFactor, 10);
	if(priv->imErcd != D_IM_BMH_SEM_TIMEOUT_ERR){
		Ddim_Print(("ct_im_bmh1_1_5: " "Wait End error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_5: " "Close error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}
#else //!CO_DEBUG_ON_PC
	Ddim_Print(("%s: Only debug on PC\n", "ct_im_bmh1_1_5: "));
	priv->imErcd = D_DDIM_SYSTEM_ERROR;
#endif //!CO_DEBUG_ON_PC

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_6(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	kuint32 waitFactor;
	DDIM_USER_ID fid_back;

	Ddim_Print(("%s\n", "ct_im_bmh1_1_6: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_6: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Async(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_6: " "Start Async error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	fid_back = FID_IM_BMH;
	FID_IM_BMH = 0xfff;
	priv->imErcd = Im_BMH_Wait_End(self->channelNo, &waitFactor, 10);
	if(priv->imErcd != D_IM_BMH_SEM_NG){
		Ddim_Print(("ct_im_bmh1_1_6: " "Wait End error = 0x%x\n", priv->imErcd));
		FID_IM_BMH = fid_back;
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	FID_IM_BMH = fid_back;

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_6: " "Close error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_7(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	DDIM_USER_ID sidBack;

	Ddim_Print(("%s\n", "ct_im_bmh1_1_7: "));

	sidBack = SID_IM_BMH(self->channelNo);
	SID_IM_BMH(self->channelNo) = 0xfff;

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_IM_BMH_SEM_NG){
		Ddim_Print(("ct_im_bmh1_1_7: " "Close error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	SID_IM_BMH(self->channelNo) = sidBack;

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_8(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	Ddim_Print(("%s\n", "ct_im_bmh1_1_8: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_8: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_8: " "Close error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_9(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl[2] = {
		{	// min
			.lselcnt = 0,
			.rbs = 0,
			.pshift = 0,
			.outmd = 0,
			.lutmd = 0,
			.offmd = 0,
			.mode = 1,
			.poffset = 0,
			.sadlv = 0,
			.pCallBack = NULL,
		},
		{	// max
			.lselcnt = 8,
			.rbs = 7,
			.pshift = 4,
			.outmd = 6,
			.lutmd = 1,
			.offmd = 1,
			.mode = 15,
			.poffset = 0xFF,
			.sadlv = 0xFFFF,
			.pCallBack = NULL,
		},
	};

	Ddim_Print(("%s\n", "ct_im_bmh1_1_9: "));

	for(loop = 0; loop < 2; loop++){
		priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl[loop]);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_9: " "Ctrl error = 0x%x\n", priv->imErcd));
			return priv->imErcd;
		}
		ctImBmh1PrintDebugReg(self);
	}

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_10(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);

	T_IM_BMH_CTRL bmh_ctrl = {
		.lselcnt = 2,
		.rbs = 3,
		.pshift = 4,
		.outmd = 5,
		.lutmd = 1,
		.offmd = 1,
		.mode = 15,
		.poffset = 63,
		.sadlv = 0x7FFF,
		.pCallBack = ctImBmh1Callback_cb,
	};
	T_IM_BMH_CTRL bmh_ctrl_get;

	Ddim_Print(("%s\n", "ct_im_bmh1_1_10: "));

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_10: " "Im_BMH_Ctrl error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Get_Ctrl(self->channelNo, &bmh_ctrl_get);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_10: " "Im_BMH_Get_Ctrl error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}
	ctImBmh1PrintDebugReg(self);
	Ddim_Print(("ct_im_bmh1_1_10: " "bmh_ctrl_get.lselcnt   = 0x%x\n",  bmh_ctrl_get.lselcnt));
	Ddim_Print(("ct_im_bmh1_1_10: " "bmh_ctrl_get.rbs       = 0x%x\n",  bmh_ctrl_get.rbs));
	Ddim_Print(("ct_im_bmh1_1_10: " "bmh_ctrl_get.pshift    = 0x%x\n",  bmh_ctrl_get.pshift));
	Ddim_Print(("ct_im_bmh1_1_10: " "bmh_ctrl_get.outmd     = 0x%x\n",  bmh_ctrl_get.outmd));
	Ddim_Print(("ct_im_bmh1_1_10: " "bmh_ctrl_get.lutmd     = 0x%x\n",  bmh_ctrl_get.lutmd));
	Ddim_Print(("ct_im_bmh1_1_10: " "bmh_ctrl_get.offmd     = 0x%x\n",  bmh_ctrl_get.offmd));
	Ddim_Print(("ct_im_bmh1_1_10: " "bmh_ctrl_get.mode      = 0x%x\n",  bmh_ctrl_get.mode));
	Ddim_Print(("ct_im_bmh1_1_10: " "bmh_ctrl_get.poffset   = 0x%lx\n", bmh_ctrl_get.poffset));
	Ddim_Print(("ct_im_bmh1_1_10: " "bmh_ctrl_get.sadlv     = 0x%lx\n", bmh_ctrl_get.sadlv));
	Ddim_Print(("ct_im_bmh1_1_10: " "bmh_ctrl_get.pCallBack = 0x%p\n",  bmh_ctrl_get.pCallBack));

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_11(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_BMHRE sram;

	Ddim_Print(("%s\n", "ct_im_bmh1_1_11: "));

	for(loop = 0; loop < 2; loop++){
		sram.bmhre = loop;
		priv->imErcd = Im_BMH_Set_Bmhre(self->channelNo, &sram);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_11: " "Set Bmhre error = 0x%x\n", priv->imErcd));
			return priv->imErcd;
		}
		ctImBmh1PrintDebugReg(self);
	}

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_12(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	T_IM_BMH_BMHRE sram;
	T_IM_BMH_BMHRE sram_get;

	Ddim_Print(("%s\n", "ct_im_bmh1_1_12: "));

	sram.bmhre = 1;
	priv->imErcd = Im_BMH_Set_Bmhre(self->channelNo, &sram);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_12: " "Set Bmhre error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}
	priv->imErcd = Im_BMH_Get_Bmhre(self->channelNo, &sram_get);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_12: " "Get Bmhre error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}
	Ddim_Print(("ct_im_bmh1_1_12: " "sram_get.bmhre = 0x%x\n", sram_get.bmhre));

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_13(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	kuint32 loop;
	kuint32 waitFactor;
	kuint32 i, j;
	T_IM_BMH_CTRL bmh_ctrl = {
		.lselcnt = 0,
		.rbs = 0,
		.pshift = 0,
		.outmd = 0,
		.lutmd = 0,
		.offmd = 0,
		.mode = 1,
		.poffset = 0,
		.sadlv = 0,
		.pCallBack = ctImBmh1Callback_cb,
	};
	T_IM_BMH_RSST rsst;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 256; j++){
			cur_write_data.cur_write_flg[i][j] = 1;
			cur_write_data.cur_data[i][j] = j;
			ref_write_data.ref_write_flg[i][j] = 1;
			ref_write_data.ref_data[i][j] = j / 2;
		}
	}

	Ddim_Print(("%s\n", "ct_im_bmh1_1_13: "));

	for(loop = 0; loop < 2; loop++){
		Ddim_Print(("ct_im_bmh1_1_13: " "loop[%d]\n", loop));
		priv->imErcd = Im_BMH_Open(self->channelNo, 100);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_13: " "Open error = 0x%x\n", priv->imErcd));
			return priv->imErcd;
		}

		priv->imErcd = Im_BMH_Init(self->channelNo);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_13: " "Init error = 0x%x\n", priv->imErcd));
			Im_BMH_Close(self->channelNo);
			return priv->imErcd;
		}

		priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_13: " "Ctrl error = 0x%x\n", priv->imErcd));
			Im_BMH_Close(self->channelNo);
			return priv->imErcd;
		}

		priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_13: " "Set Cur error = 0x%x\n", priv->imErcd));
			Im_BMH_Close(self->channelNo);
			return priv->imErcd;
		}

		priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_13: " "Set Ref error = 0x%x\n", priv->imErcd));
			Im_BMH_Close(self->channelNo);
			return priv->imErcd;
		}

		priv->imErcd = Im_BMH_Start_Async(self->channelNo);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_13: " "Start Async error = 0x%x\n", priv->imErcd));
			Im_BMH_Close(self->channelNo);
			return priv->imErcd;
		}

#ifdef CO_DEBUG_ON_PC
		IO_BMH[self->channelNo].BMHINTFS.bit.__BMHF = 1;
		IO_BMH[self->channelNo].BMHINTFS.bit.__RSST = (IO_BMH[self->channelNo].BMHINTFS.bit.__RSST + 1) & 1;
		Im_BMH_Int_Handler(self->channelNo);
#endif //CO_DEBUG_ON_PC

		priv->imErcd = Im_BMH_Wait_End(self->channelNo, &waitFactor, 1000);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_13: " "Wait End error = 0x%x\n", priv->imErcd));
			Im_BMH_Close(self->channelNo);
			return priv->imErcd;
		}

		priv->imErcd = Im_BMH_Get_Rsst(self->channelNo, &rsst);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_13: " "Get Rsst error = 0x%x\n", priv->imErcd));
			Im_BMH_Close(self->channelNo);
			return priv->imErcd;
		}
		Ddim_Print(("rsst.rsst = %u\n", rsst.rsst));

		priv->imErcd = Im_BMH_Close(self->channelNo);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_13: " "Close error = 0x%x\n", priv->imErcd));
			return priv->imErcd;
		}
	}

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_14(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_BMHCONT cont;

	Ddim_Print(("%s\n", "ct_im_bmh1_1_14: "));

	for(loop = 0; loop < 2; loop++){
		Ddim_Print(("ct_im_bmh1_1_14: " "loop[%d]\n", loop));
		cont.cont = loop;
		priv->imErcd = Im_BMH_Set_Bmhcont(self->channelNo, &cont);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_14: " "Set Bmhcont error = 0x%x\n", priv->imErcd));
			return priv->imErcd;
		}

		ctImBmh1PrintDebugReg(self);
	}

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_15(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);

	T_IM_BMH_BMHCONT cont;
	T_IM_BMH_BMHCONT cont_get;

	Ddim_Print(("%s\n", "ct_im_bmh1_1_15: "));

	cont.cont = 1;
	priv->imErcd = Im_BMH_Set_Bmhcont(self->channelNo, &cont);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_15: " "Set Bmhcont error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Get_Bmhcont(self->channelNo, &cont_get);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_15: " "Get Bmhcont error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}
	Ddim_Print(("ct_im_bmh1_1_15: " "cont_get.cont = 0x%x\n", cont_get.cont));

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_16(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_AXI axi_ctrl[2] = {
		{	// min
			.read_cache_type = 0,
			.read_protection_type = 0,
			.write_cache_type = 0,
			.write_protection_type = 0,
		},
		{	// max
			.read_cache_type = 0xf,
			.read_protection_type = 0x7,
			.write_cache_type = 0xf,
			.write_protection_type = 0x7,
		},
	};

	Ddim_Print(("%s\n", "ct_im_bmh1_1_16: "));

	for(loop = 0; loop < 2; loop++){
		Ddim_Print(("ct_im_bmh1_1_16: " "loop[%d]\n", loop));
		priv->imErcd = Im_BMH_Set_Bmhaxi(self->channelNo, &axi_ctrl[loop]);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh1_1_16: " "Set Bmhaxi error = 0x%x\n", priv->imErcd));
			return priv->imErcd;
		}
		ctImBmh1PrintDebugReg(self);
	}

	return priv->imErcd;
}

kint32 ct_im_bmh1_1_17(CtImBmh1 *self)
{
	CtImBmh1Private *priv = CT_IM_BMH1_GET_PRIVATE(self);
	T_IM_BMH_AXI_STATUS sts;

	Ddim_Print(("%s\n", "ct_im_bmh1_1_17: "));

#ifdef CO_DEBUG_ON_PC
	IO_BMH[self->channelNo].BMHAXIERR.bit.WRESP = 1;
	IO_BMH[self->channelNo].BMHAXIERR.bit.RRESP = 1;
#endif // CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Get_Bmhaxierr(self->channelNo, &sts);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh1_1_17: " "Get Bmhaxierr error = 0x%x\n", priv->imErcd));
	}
	Ddim_Print(("ct_im_bmh1_1_17: " "sts.read_channel_response  = 0x%x\n", sts.read_channel_response));
	Ddim_Print(("ct_im_bmh1_1_17: " "sts.write_channel_response = 0x%x\n", sts.write_channel_response));

	return priv->imErcd;
}

/*
 * 此函数用于创建对象
 * @     
 * @return:
 */
CtImBmh1* ct_im_bmh1_new(void) 
{
    CtImBmh1 *self = k_object_new_with_private(CT_TYPE_IM_BMH1, sizeof(CtImBmh1Private));
    return self;
}
