/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh8类
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
#include "ctimbmh.h"
#include "im_bmh.h"
#include "dd_top.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#include "jmlbmh.h"
#include "ctimbmh1.h"
#include "ctimbmh2.h"
#include "ctimbmh3.h"
#include "ctimbmh4.h"
#include "ctimbmh5.h"
#include "ctimbmh6.h"
#include "ctimbmh7.h"
#include "ctimbmh8.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImBmh8, ct_im_bmh8);
#define CT_IM_BMH8_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImBmh8Private,CT_TYPE_IM_BMH8))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define CtImBmh8_D_IM_BMH_TEST_IMG_HSIZE		(320)
#define CtImBmh8_D_IM_BMH_TEST_IMG_VSIZE		(240)
#define CtImBmh8_D_IM_BMH_TEST_RESULT_OUT_ADDR	(0x7E000000)

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// nothing special.

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// nothing special.

struct _CtImBmh8Private
{
	kint32 imErcd;
	CtImBmh* bmh;	
};

/*
 * DECLS
 */
static void bmhCallbackOutputResult_cb(kulong interruptFlagMask);
static void ctImBmhPrintDebugReg(void);

static void ct_im_bmh8_constructor(CtImBmh8 *self) 
{
	CtImBmh8Private *priv = CT_IM_BMH8_GET_PRIVATE(self);
	priv->bmh = ct_im_bmh_new();	
}

static void ct_im_bmh8_destructor(CtImBmh8 *self) 
{
	CtImBmh8Private *priv = CT_IM_BMH8_GET_PRIVATE(self);
	
	if(priv->bmh){
		k_object_unref(priv->bmh);
		priv->bmh = NULL;
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

static T_IM_BMH_CTRL gctImBmhCtrl = {
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
kint32 ct_im_bmh8_3_32(CtImBmh8 *self)
{
	CtImBmh8Private *priv = CT_IM_BMH8_GET_PRIVATE(self);
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

	bmh_ctrl.mode = 11;

	Ddim_Print(("%s\n", "ct_im_bmh8_3_32: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_32: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_32: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_32: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_32: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_32: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_32: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_32: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh8_3_33(CtImBmh8 *self)
{
	CtImBmh8Private *priv = CT_IM_BMH8_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;
	T_IM_BMH_BMHCONT cont;

	// top line
	memcpy(cur_write_data.cur_data[0], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
	memcpy(ref_write_data.ref_data[0], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
	memset(cur_write_data.cur_write_flg[0], 1, 256);
	memset(ref_write_data.ref_write_flg[0], 1, 256);

	// 2~8 line(last 16pix)
	for(loop = 1; loop < 8; loop++){
		memcpy(&cur_write_data.cur_data[loop][256 - 16], (kpointer)(CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR + CtImBmh8_D_IM_BMH_TEST_IMG_HSIZE * loop - 16), 16);
		memcpy(&ref_write_data.ref_data[loop][256 - 16], (kpointer)(CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR + CtImBmh8_D_IM_BMH_TEST_IMG_HSIZE * loop - 16), 16);
		memset(&cur_write_data.cur_write_flg[loop][256 - 16], 1, 16);
		memset(&ref_write_data.ref_write_flg[loop][256 - 16], 1, 16);
	}

	bmh_ctrl.mode = 7;

	Ddim_Print(("%s\n", "ct_im_bmh8_3_33: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_33: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_33: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_33: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_33: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_33: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	memcpy(&cur_write_data.cur_data[8][256 - 16], (kpointer)(CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR + CtImBmh8_D_IM_BMH_TEST_IMG_HSIZE * 8 - 16), 16);
	memcpy(&ref_write_data.ref_data[8][256 - 16], (kpointer)(CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR + CtImBmh8_D_IM_BMH_TEST_IMG_HSIZE * 8 - 16), 16);
	memset(&cur_write_data.cur_write_flg[8][256 - 16], 1, 16);
	memset(&ref_write_data.ref_write_flg[8][256 - 16], 1, 16);

	cont.cont = 1;
	priv->imErcd = Im_BMH_Set_Bmhcont(self->channelNo, &cont);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_33: " "Set Bmhcont error = 0x%x\n", priv->imErcd));
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_33: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_33: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh8_3_34(CtImBmh8 *self)
{
	CtImBmh8Private *priv = CT_IM_BMH8_GET_PRIVATE(self);
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

	bmh_ctrl.sadlv = 0xFFFF;

	Ddim_Print(("%s\n", "ct_im_bmh8_3_34: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_34: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_34: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_34: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_34: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_34: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_34: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_34: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh8_3_35(CtImBmh8 *self)
{
	CtImBmh8Private *priv = CT_IM_BMH8_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;
	T_IM_BMH_BMHHCNT cnt;

	for(loop = 0; loop < 8; loop++){
		memcpy(cur_write_data.cur_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
		memcpy(ref_write_data.ref_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
		memset(cur_write_data.cur_write_flg[loop], 1, 256);
		memset(ref_write_data.ref_write_flg[loop], 1, 256);
	}

	bmh_ctrl.sadlv = 0xFFFF;
	cnt.hcnt = 10;

	Ddim_Print(("%s\n", "ct_im_bmh8_3_35: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_35: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_35: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Bmhhcnt(self->channelNo, &cnt);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_35: " "Set Bmhhcnt error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_35: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_35: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_35: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_35: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_35: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh8_3_36(CtImBmh8 *self)
{
	CtImBmh8Private *priv = CT_IM_BMH8_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CUR_BLOCK cur_write_data;
	T_IM_BMH_REF_BLOCK ref_write_data;
	T_IM_BMH_BMHHCNT cnt;

	for(loop = 0; loop < 8; loop++){
		memcpy(cur_write_data.cur_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR, 256);
		memcpy(ref_write_data.ref_data[loop], (kpointer)CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR, 256);
		memset(cur_write_data.cur_write_flg[loop], 1, 256);
		memset(ref_write_data.ref_write_flg[loop], 1, 256);
	}

	bmh_ctrl.rbs = 3;
	bmh_ctrl.sadlv = 0xFFFF;
	cnt.hcnt = 200;

	Ddim_Print(("%s\n", "ct_im_bmh8_3_36: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_36: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_36: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Bmhhcnt(self->channelNo, &cnt);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_36: " "Set Bmhhcnt error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_36: " "Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_36: " "Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_36: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_36: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_36: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

kint32 ct_im_bmh8_3_37(CtImBmh8 *self)
{
	CtImBmh8Private *priv = CT_IM_BMH8_GET_PRIVATE(self);

	T_IM_BMH_CTRL bmh_ctrl = gctImBmhCtrl;
	T_IM_BMH_CTRL_DMA bmh_dma_ctrl;

	bmh_dma_ctrl.dmamd = 1;
	bmh_dma_ctrl.ghsize_cur = CtImBmh8_D_IM_BMH_TEST_IMG_HSIZE;
	bmh_dma_ctrl.ghsize_ref = CtImBmh8_D_IM_BMH_TEST_IMG_HSIZE;
	bmh_dma_ctrl.hsize_ref = CtImBmh8_D_IM_BMH_TEST_IMG_HSIZE;
	bmh_dma_ctrl.vsize_ref = CtImBmh8_D_IM_BMH_TEST_IMG_VSIZE;
	bmh_dma_ctrl.curstad = CtImBmh_D_IM_BMH_TEST_CUR_IMG_ADDR;
	bmh_dma_ctrl.refstad = CtImBmh_D_IM_BMH_TEST_REF_IMG_ADDR;
	bmh_dma_ctrl.sadstad = CtImBmh8_D_IM_BMH_TEST_RESULT_OUT_ADDR;
	bmh_dma_ctrl.sadghsize = 0x400;

	Ddim_Print(("%s\n", "ct_im_bmh8_3_37: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_37: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	Im_BMH_Init(self->channelNo);
	// don't forget Im_BMH_Close() after this line

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_37: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Ctrl_Dma(self->channelNo, &bmh_dma_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_37: " "Ctrl Dma error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_37: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Stop(self->channelNo);
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	ct_im_bmh_print_debug_sadr(priv->bmh);

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_37: " "Stop error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh8_3_37: " "Close error = 0x%x\n", priv->imErcd));
	}
	return priv->imErcd;
}

CtImBmh8* ct_im_bmh8_new(void) 
{
    CtImBmh8 *self = k_object_new_with_private(CT_TYPE_IM_BMH8, sizeof(CtImBmh8Private));
    return self;
}
