/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh6类
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

K_TYPE_DEFINE_WITH_PRIVATE(CtImBmh6, ct_im_bmh6);
#define CT_IM_BMH6_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImBmh6Private,CT_TYPE_IM_BMH6))

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

struct _CtImBmh6Private
{
	kint32 imErcd;	
	CtImBmh* bmh;
	CtImBmh5 *bmh5;
};

/*
 * DECLS
 */
static void bmhCallbackOutputResult_cb(kulong interruptFlagMask);
static void ctImBmhPrintDebugReg(void);

static void ct_im_bmh6_constructor(CtImBmh6 *self) 
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);
	priv->bmh = ct_im_bmh_new();
	priv->bmh5 = ct_im_bmh5_new();
}

static void ct_im_bmh6_destructor(CtImBmh6 *self) 
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);
	if(priv->bmh){
		k_object_unref(priv->bmh);
		priv->bmh = NULL;
	}	
	if(priv->bmh5){
		k_object_unref(priv->bmh5);
		priv->bmh5 = NULL;
	}
}

/*
 * IMPL
 */
static void bmhCallbackOutputResult_cb(kulong interruptFlagMask)
{
	Ddim_Print(("bmhCallbackOutputResult_cb interruptFlagMask = 0x%lx\n", interruptFlagMask));
	ctImBmhPrintDebugReg();
}

static void ctImBmhPrintDebugReg(void)
{
	kuchar loopcnt;
	for(loopcnt = 0; loopcnt < 2; loopcnt++){
		Ddim_Print(("IO_BMH[%d]\n",                  loopcnt));
		Ddim_Print(("\tBMHSR-SR             = 0x%x\n",  IO_BMH[loopcnt].BMHSR.bit.SR));
		Ddim_Print(("\tBMHTRG-BMHTRG        = 0x%x\n",  IO_BMH[loopcnt].BMHTRG.bit.BMHTRG));
		Ddim_Print(("\tBMHRE-BMHRE          = 0x%x\n",  IO_BMH[loopcnt].BMHRE.bit.BMHRE));
		Ddim_Print(("\tBMHCONT-CONT         = 0x%x\n",  IO_BMH[loopcnt].BMHCONT.bit.CONT));
		Ddim_Print(("\tBMHINTFS-__RSST      = 0x%x\n",  IO_BMH[loopcnt].BMHINTFS.bit.__RSST));
		Ddim_Print(("\tBMHINTFS-__AXIF      = 0x%x\n",  IO_BMH[loopcnt].BMHINTFS.bit.__AXIF));
		Ddim_Print(("\tBMHINTFS-__BMHF      = 0x%x\n",  IO_BMH[loopcnt].BMHINTFS.bit.__BMHF));
		Ddim_Print(("\tBMHINTE-AXIE         = 0x%x\n",  IO_BMH[loopcnt].BMHINTE.bit.AXIE));
		Ddim_Print(("\tBMHINTE-BMHE         = 0x%x\n",  IO_BMH[loopcnt].BMHINTE.bit.BMHE));
		Ddim_Print(("\tBMHMD-MODE           = 0x%x\n",  IO_BMH[loopcnt].BMHMD.bit.MODE));
		Ddim_Print(("\tBMHMD-OFFMD          = 0x%x\n",  IO_BMH[loopcnt].BMHMD.bit.OFFMD));
		Ddim_Print(("\tBMHMD-LUTMD          = 0x%x\n",  IO_BMH[loopcnt].BMHMD.bit.LUTMD));
		Ddim_Print(("\tBMHMD-OUTMD          = 0x%x\n",  IO_BMH[loopcnt].BMHMD.bit.OUTMD));
		Ddim_Print(("\tBMHMD-PSHIFT         = 0x%x\n",  IO_BMH[loopcnt].BMHMD.bit.PSHIFT));
		Ddim_Print(("\tBMHMD-RBS            = 0x%x\n",  IO_BMH[loopcnt].BMHMD.bit.RBS));
		Ddim_Print(("\tBMHMD-LSELCNT        = 0x%x\n",  IO_BMH[loopcnt].BMHMD.bit.LSELCNT));
		Ddim_Print(("\tBMHPRM-SADLV         = 0x%x\n",  IO_BMH[loopcnt].BMHPRM.bit.SADLV));
		Ddim_Print(("\tBMHPRM-POFFSET       = 0x%x\n",  IO_BMH[loopcnt].BMHPRM.bit.POFFSET));
		Ddim_Print(("\tBMHHCNT-RCNT         = 0x%x\n",  IO_BMH[loopcnt].BMHHCNT.bit.RCNT));
		Ddim_Print(("\tBMHHCNT-HCNT         = 0x%x\n",  IO_BMH[loopcnt].BMHHCNT.bit.HCNT));
		Ddim_Print(("\tBMHSAD_WR-SAD_WR     = 0x%x\n",  IO_BMH[loopcnt].BMHSAD_WR.bit.SAD_WR));
		Ddim_Print(("\tBMHDMA-DMAMD         = 0x%x\n",  IO_BMH[loopcnt].BMHDMA.bit.DMAMD));
		Ddim_Print(("\tBMHGHSIZE-GHSIZE_REF = 0x%x\n",  IO_BMH[loopcnt].BMHGHSIZE.bit.GHSIZE_REF));
		Ddim_Print(("\tBMHGHSIZE-GHSIZE_CUR = 0x%x\n",  IO_BMH[loopcnt].BMHGHSIZE.bit.GHSIZE_CUR));
		Ddim_Print(("\tBMHHSIZE-HSIZE_REF   = 0x%x\n",  IO_BMH[loopcnt].BMHHSIZE.bit.HSIZE_REF));
		Ddim_Print(("\tBMHVSIZE-VSIZE_REF   = 0x%x\n",  IO_BMH[loopcnt].BMHVSIZE.bit.VSIZE_REF));
		Ddim_Print(("\tBMHCURAD-CURSTAD     = 0x%lx\n", IO_BMH[loopcnt].BMHCURAD.bit.CURSTAD));
		Ddim_Print(("\tBMHREFAD-REFSTAD     = 0x%lx\n", IO_BMH[loopcnt].BMHREFAD.bit.REFSTAD));
		Ddim_Print(("\tBMHSADAD-SADSTAD     = 0x%lx\n", IO_BMH[loopcnt].BMHSADAD.bit.SADSTAD));
		Ddim_Print(("\tBMHSADGH-SADGHSIZE   = 0x%x\n",  IO_BMH[loopcnt].BMHSADGH.bit.SADGHSIZE));
		Ddim_Print(("\tBMHAXICTRL-ARCACHE   = 0x%x\n",  IO_BMH[loopcnt].BMHAXICTRL.bit.ARCACHE));
		Ddim_Print(("\tBMHAXICTRL-ARPROT    = 0x%x\n",  IO_BMH[loopcnt].BMHAXICTRL.bit.ARPROT));
		Ddim_Print(("\tBMHAXICTRL-AWCACHE   = 0x%x\n",  IO_BMH[loopcnt].BMHAXICTRL.bit.AWCACHE));
		Ddim_Print(("\tBMHAXICTRL-AWPROT    = 0x%x\n",  IO_BMH[loopcnt].BMHAXICTRL.bit.AWPROT));
		Ddim_Print(("\tBMHAXIERR-RRESP      = 0x%x\n",  IO_BMH[loopcnt].BMHAXIERR.bit.RRESP));
		Ddim_Print(("\tBMHAXIERR-WRESP      = 0x%x\n",  IO_BMH[loopcnt].BMHAXIERR.bit.WRESP));
		Ddim_Print(("\n"));
	}
}

static T_IM_BMH_CTRL gctImBmhCtrl = {//TODO:尝试修改
	.lselcnt = 0,
	.rbs = 0,
	.pshift = 0,
	.outmd = 0,
	.lutmd = 0,
	.offmd = 0,
	.mode = 1,
	.poffset = 0,
	.sadlv = 0,
	.pCallBack = bmhCallbackOutputResult_cb,
};

/*
 * PUBLIC
 */
kint32 ct_im_bmh6_3_11(CtImBmh6 *self)
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;

	for(loop = 0; loop < 8; loop++){
		memcpy(cur_write_data.cur_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
		memcpy(ref_write_data.ref_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
		memset(cur_write_data.cur_write_flg[loop], 1, 256);
		memset(ref_write_data.ref_write_flg[loop], 1, 256);
	}

	bmh_ctrl.rbs = 2;

	Ddim_Print(("%s\n", "ct_im_bmh6_3_11: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_11: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_11: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_11: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_11: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_11: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_11: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_11: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh6_3_12(CtImBmh6 *self)
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;

	for(loop = 0; loop < 8; loop++){
		memcpy(cur_write_data.cur_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
		memcpy(ref_write_data.ref_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
		memset(cur_write_data.cur_write_flg[loop], 1, 256);
		memset(ref_write_data.ref_write_flg[loop], 1, 256);
	}

	bmh_ctrl.rbs = 3;

	Ddim_Print(("%s\n", "ct_im_bmh6_3_12: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_12: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_12: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_12: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_12: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_12: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_12: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_12: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh6_3_13(CtImBmh6 *self)
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;

	for(loop = 0; loop < 8; loop++){
		memcpy(cur_write_data.cur_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
		memcpy(ref_write_data.ref_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
		memset(cur_write_data.cur_write_flg[loop], 1, 256);
		memset(ref_write_data.ref_write_flg[loop], 1, 256);
	}

	bmh_ctrl.rbs = 4;

	Ddim_Print(("%s\n", "ct_im_bmh6_3_13: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_13: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_13: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_13: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_13: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_13: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_13: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_13: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh6_3_14(CtImBmh6 *self)
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;

	for(loop = 0; loop < 8; loop++){
		memcpy(cur_write_data.cur_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
		memcpy(ref_write_data.ref_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
		memset(cur_write_data.cur_write_flg[loop], 1, 256);
		memset(ref_write_data.ref_write_flg[loop], 1, 256);
	}

	bmh_ctrl.rbs = 5;

	Ddim_Print(("%s\n", "ct_im_bmh6_3_14: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_14: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_14: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_14: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_14: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_14: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_14: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_14: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh6_3_15(CtImBmh6 *self)
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;

	for(loop = 0; loop < 8; loop++){
		memcpy(cur_write_data.cur_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
		memcpy(ref_write_data.ref_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
		memset(cur_write_data.cur_write_flg[loop], 1, 256);
		memset(ref_write_data.ref_write_flg[loop], 1, 256);
	}

	bmh_ctrl.rbs = 6;

	Ddim_Print(("%s\n", "ct_im_bmh6_3_15: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_15: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_15: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_15: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_15: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_15: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_15: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_15: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh6_3_16(CtImBmh6 *self)
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);

	priv->imErcd = ct_im_bmh5_3_1(priv->bmh5);

	return priv->imErcd;
}

kint32 ct_im_bmh6_3_17(CtImBmh6 *self)
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;

	for(loop = 0; loop < 8; loop++){
		memcpy(cur_write_data.cur_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
		memcpy(ref_write_data.ref_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
		memset(cur_write_data.cur_write_flg[loop], 1, 256);
		memset(ref_write_data.ref_write_flg[loop], 1, 256);
	}

	bmh_ctrl.pshift = 1;

	Ddim_Print(("%s\n", "ct_im_bmh6_3_17: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_17: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_17: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_17: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_17: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_17: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_17: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_17: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh6_3_18(CtImBmh6 *self)
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;

	for(loop = 0; loop < 8; loop++){
		memcpy(cur_write_data.cur_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
		memcpy(ref_write_data.ref_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
		memset(cur_write_data.cur_write_flg[loop], 1, 256);
		memset(ref_write_data.ref_write_flg[loop], 1, 256);
	}

	bmh_ctrl.pshift = 2;

	Ddim_Print(("%s\n", "ct_im_bmh6_3_18: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_18: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_18: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_18: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_18: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_18: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_18: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_18: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh6_3_19(CtImBmh6 *self)
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;

	for(loop = 0; loop < 8; loop++){
		memcpy(cur_write_data.cur_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
		memcpy(ref_write_data.ref_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
		memset(cur_write_data.cur_write_flg[loop], 1, 256);
		memset(ref_write_data.ref_write_flg[loop], 1, 256);
	}

	bmh_ctrl.pshift = 3;

	Ddim_Print(("%s\n", "ct_im_bmh6_3_19: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_19: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_19: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_19: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_19: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_19: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_19: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_19: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh6_3_20(CtImBmh6 *self)
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;

	for(loop = 0; loop < 8; loop++){
		memcpy(cur_write_data.cur_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
		memcpy(ref_write_data.ref_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
		memset(cur_write_data.cur_write_flg[loop], 1, 256);
		memset(ref_write_data.ref_write_flg[loop], 1, 256);
	}

	bmh_ctrl.pshift = 4;

	Ddim_Print(("%s\n", "ct_im_bmh6_3_20: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_20: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_20: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_20: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_20: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_20: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_20: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_20: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh6_3_21(CtImBmh6 *self)
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);

	priv->imErcd = ct_im_bmh5_3_1(priv->bmh5);

	return priv->imErcd;
}

kint32 ct_im_bmh6_3_22(CtImBmh6 *self)
{
	CtImBmh6Private *priv = CT_IM_BMH6_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;

	for(loop = 0; loop < 8; loop++){
		memcpy(cur_write_data.cur_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
		memcpy(ref_write_data.ref_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
		memset(cur_write_data.cur_write_flg[loop], 1, 256);
		memset(ref_write_data.ref_write_flg[loop], 1, 256);
	}

	bmh_ctrl.outmd = 1;

	Ddim_Print(("%s\n", "ct_im_bmh6_3_22: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_22: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_22: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_22: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_22: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_22: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_22: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh6_3_22: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

CtImBmh6* ct_im_bmh6_new(void) 
{
    CtImBmh6 *self = k_object_new_with_private(CT_TYPE_IM_BMH6, sizeof(CtImBmh6Private));
    return self;
}
