/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh2类
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

K_TYPE_DEFINE_WITH_PRIVATE(CtImBmh2, ct_im_bmh2);
#define CT_IM_BMH2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImBmh2Private,CT_TYPE_IM_BMH2))

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

struct _CtImBmh2Private
{
	int i;
	kint32 imErcd;
	CtImBmh1 *bmh1;
};

/*
 * DECLS
 */
static void 	ctImBmh2PrintDebugReg(void);//调用到回调方法，暂时加不了self
static void 	bmhCallbackOutputResult_cb(kulong interruptFlagMask);//回调方法，被其他文件调用

static void ct_im_bmh2_constructor(CtImBmh2 *self) 
{
	 CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	 priv->bmh1 = ct_im_bmh1_new();
}

static void ct_im_bmh2_destructor(CtImBmh2 *self) 
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	if(priv->bmh1){
	k_object_unref(priv->bmh1);
	priv->bmh1 = NULL;		
	}
}

/*
 * IMPL
 */
static void ctImBmh2PrintDebugReg(void)
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

static void bmhCallbackOutputResult_cb(kulong interruptFlagMask)
{
	Ddim_Print(("bmhCallbackOutputResult_cb interruptFlagMask = 0x%lx\n", interruptFlagMask));
	ctImBmh2PrintDebugReg();
}

/*
 * PUBLIC
 */
kint32 ct_im_bmh2_1_18(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_BMHHCNT cnt[2] = {
		{	// min
			.hcnt = 0,
			.rcnt = 0,
		},
		{	// max
			.hcnt = 0xff,
			.rcnt = 0xf,
		},
	};

	Ddim_Print(("%s\n", "ct_im_bmh2_1_18: "));

	for(loop = 0; loop < 2; loop++){
		priv->imErcd = Im_BMH_Set_Bmhhcnt(self->channelNo, &cnt[loop]);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh2_1_18: " "Set Bmhhcnt error = 0x%x\n", priv->imErcd));
		}
		ctImBmh2PrintDebugReg();
	}

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_19(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);	
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

	Ddim_Print(("%s\n", "ct_im_bmh2_1_19: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_19: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Init(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_19: " "Init error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_19: " "Set Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_19: " "Set Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
		IO_BMH[self->channelNo].BMHINTFS.bit.__BMHF = 1;
#endif //CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_19: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_19: " "Stop error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_19: " "Close error = 0x%x\n", priv->imErcd));
	}

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_20(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);

	Ddim_Print(("%s\n", "ct_im_bmh2_1_20: "));

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_20: " "Stop error = 0x%x\n", priv->imErcd));
	}

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_21(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);

	priv->imErcd = ct_im_bmh1_1_8(priv->bmh1);

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_22(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);

	Ddim_Print(("%s\n", "ct_im_bmh2_1_22: "));

	priv->imErcd = Im_BMH_Init(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_22: " "Init error = 0x%x\n", priv->imErcd));
	}

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_23(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	T_IM_BMH_BMHHCNT cnt;
	T_IM_BMH_BMHHCNT cnt_get;

	Ddim_Print(("%s\n", "ct_im_bmh2_1_23: "));

	cnt.hcnt = 1;
	cnt.rcnt = 1;
	priv->imErcd = Im_BMH_Set_Bmhhcnt(self->channelNo, &cnt);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_23: " "Set Bmhhcnt error = 0x%x\n", priv->imErcd));
	}
	priv->imErcd = Im_BMH_Get_Bmhhcnt(self->channelNo, &cnt_get);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_23: " "Set Bmhhcnt error = 0x%x\n", priv->imErcd));
	}
	Ddim_Print(("ct_im_bmh2_1_23: " "cnt_get.hcnt = 0x%x\n", cnt_get.hcnt));
	Ddim_Print(("ct_im_bmh2_1_23: " "cnt_get.rcnt = 0x%x\n", cnt_get.rcnt));

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_24(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_BMHSAD_WR sad_wr[2] = {
		{	// min
			.sad_wr = 0,
		},
		{	// max
			.sad_wr = 0x1f,
		},
	};

	Ddim_Print(("%s\n", "ct_im_bmh2_1_24: "));

	for(loop = 0; loop < 2; loop++){
		priv->imErcd = Im_BMH_Set_Bmhsad_wr(self->channelNo, &sad_wr[loop]);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh2_1_24: " "Set Bmhsad_wr error = 0x%x\n", priv->imErcd));
		}
		ctImBmh2PrintDebugReg();
	}

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_25(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	T_IM_BMH_BMHSAD_WR sad_wr;
	T_IM_BMH_BMHSAD_WR sad_wr_get;

	Ddim_Print(("%s\n", "ct_im_bmh2_1_25: "));

	sad_wr.sad_wr = 1;
	priv->imErcd = Im_BMH_Set_Bmhsad_wr(self->channelNo, &sad_wr);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_25: " "Set Bmhsad_wr error = 0x%x\n", priv->imErcd));
	}
	priv->imErcd = Im_BMH_Get_Bmhsad_wr(self->channelNo, &sad_wr_get);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_25: " "Get Bmhsad_wr error = 0x%x\n", priv->imErcd));
	}
	Ddim_Print(("ct_im_bmh2_1_25: " "sad_wr_get.sad_wr = 0x%x\n", sad_wr_get.sad_wr));

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_26(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	kuint32 loop;

	T_IM_BMH_CTRL_DMA bmh_ctrl_dma[2] = {
		{	// min
			.dmamd = 0,
			.ghsize_cur = 16,
			.ghsize_ref = 32,
			.hsize_ref = 32,
			.vsize_ref = 8,
			.curstad = 0,
			.refstad = 0,
			.sadstad = 0,
			.sadghsize = 0,
		},
		{	// max
			.dmamd = 1,
			.ghsize_cur = 0xFFF8,
			.ghsize_ref = 0xFFF8,
			.hsize_ref = 0xFFFF,
			.vsize_ref = 0xFFFF,
			.curstad = 0xFFFFFFF8,
			.refstad = 0xFFFFFFF8,
			.sadstad = 0xFFFFFFF8,
			.sadghsize = 0xFFF8,
		},
	};

	Ddim_Print(("%s\n", "ct_im_bmh2_1_26: "));

	for(loop = 0; loop < 2; loop++){
		priv->imErcd = Im_BMH_Ctrl_Dma(self->channelNo, &bmh_ctrl_dma[loop]);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh2_1_26: " "Ctrl Dma error = 0x%x\n", priv->imErcd));
		}
		ctImBmh2PrintDebugReg();
	}

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_27(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	T_IM_BMH_CTRL_DMA bmh_ctrl_dma;
	T_IM_BMH_CTRL_DMA bmh_ctrl_dma_get;

	Ddim_Print(("%s\n", "ct_im_bmh2_1_27: "));

	bmh_ctrl_dma.dmamd = 1;
	bmh_ctrl_dma.ghsize_cur = 0x10;
	bmh_ctrl_dma.ghsize_ref = 0x20;
	bmh_ctrl_dma.hsize_ref = 0x30;
	bmh_ctrl_dma.vsize_ref = 0x40;
	bmh_ctrl_dma.curstad = 0x50;
	bmh_ctrl_dma.refstad = 0x60;
	bmh_ctrl_dma.sadstad = 0x70;
	bmh_ctrl_dma.sadghsize = 0x80;
	priv->imErcd = Im_BMH_Ctrl_Dma(self->channelNo, &bmh_ctrl_dma);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_27: " "Ctrl Dma error = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = Im_BMH_Get_Ctrl_Dma(self->channelNo, &bmh_ctrl_dma_get);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_27: " "Get Ctrl_Dma error = 0x%x\n", priv->imErcd));
	}

	Ddim_Print(("ct_im_bmh2_1_27: " "bmh_ctrl_dma_get.dmamd      = 0x%lx\n", bmh_ctrl_dma_get.dmamd));
	Ddim_Print(("ct_im_bmh2_1_27: " "bmh_ctrl_dma_get.ghsize_cur = 0x%lx\n", bmh_ctrl_dma_get.ghsize_cur));
	Ddim_Print(("ct_im_bmh2_1_27: " "bmh_ctrl_dma_get.ghsize_ref = 0x%lx\n", bmh_ctrl_dma_get.ghsize_ref));
	Ddim_Print(("ct_im_bmh2_1_27: " "bmh_ctrl_dma_get.hsize_ref  = 0x%lx\n", bmh_ctrl_dma_get.hsize_ref));
	Ddim_Print(("ct_im_bmh2_1_27: " "bmh_ctrl_dma_get.vsize_ref  = 0x%lx\n", bmh_ctrl_dma_get.vsize_ref));
	Ddim_Print(("ct_im_bmh2_1_27: " "bmh_ctrl_dma_get.curstad    = 0x%lx\n", bmh_ctrl_dma_get.curstad));
	Ddim_Print(("ct_im_bmh2_1_27: " "bmh_ctrl_dma_get.refstad    = 0x%lx\n", bmh_ctrl_dma_get.refstad));
	Ddim_Print(("ct_im_bmh2_1_27: " "bmh_ctrl_dma_get.sadstad    = 0x%lx\n", bmh_ctrl_dma_get.sadstad));
	Ddim_Print(("ct_im_bmh2_1_27: " "bmh_ctrl_dma_get.sadghsize  = 0x%lx\n", bmh_ctrl_dma_get.sadghsize));

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_28(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	kulong count;
	kuint32 loop;

	T_IM_BMH_LUT lut_data;

	Ddim_Print(("%s\n", "ct_im_bmh2_1_28: "));

	for(loop = 0; loop < 3; loop++){
		Ddim_Print(("ct_im_bmh2_1_28: " "loop[%d]\n", loop));
		switch(loop){
			case 1:	// max
				for(count = 0; count < 2048; count++){
					lut_data.lut[count] = 0xFFF;
				}
				break;

			case 2:	// individual
				for(count = 0; count < 2048; count++){
					lut_data.lut[count] = count;
				}
				break;

//			case 0:	// min
			default:
				for(count = 0; count < 2048; count++){
					lut_data.lut[count] = 0;
				}
				break;
		}

		priv->imErcd = Im_BMH_Set_Lut(self->channelNo, &lut_data);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh2_1_28: " "Set Lut error = 0x%x\n", priv->imErcd));
		}
#ifdef CO_DEBUG_ON_PC
		for(count = 0; count < 1024; count++){
			Ddim_Print(("ct_im_bmh2_1_28: " "IO_BMH[%d].LUT.word[%lu] = 0x%lx\n", self->channelNo, count, IO_BMH[self->channelNo].LUT.word[count]));
		}
#endif // CO_DEBUG_ON_PC
	}

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_29(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);

	Ddim_Print(("%s\n", "ct_im_bmh2_1_29: "));

	priv->imErcd = Im_BMH_Set_Interrupt(self->channelNo, 0, 1);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_29: " "Interrupt error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	ctImBmh2PrintDebugReg();

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_30(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	kuint32 i, j;
	kuint32 waitFactor;

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
		.pCallBack = bmhCallbackOutputResult_cb,
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

	Ddim_Print(("%s\n", "ct_im_bmh2_1_30: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_30: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Init(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_30: " "Init error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_30: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Interrupt(self->channelNo, D_IM_BMH_FLG_BMH_END | D_IM_BMH_FLG_BMH_AXI_ERR, 1);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_30: " "Interrupt error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_30: " "Set Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_30: " "Set Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Start_Async(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_30: " "Start Async error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
	IO_BMH[self->channelNo].BMHINTFS.bit.__BMHF = 1;
	Im_BMH_Int_Handler(self->channelNo);
#endif //CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Wait_End(self->channelNo, &waitFactor, 1000);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_30: " "Wait End error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_30: " "Close error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_31(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	kuint32 loop1, loop2, loop3;

	T_IM_BMH_CUR_BLOCK cur_write_data;

	Ddim_Print(("%s\n", "ct_im_bmh2_1_31: "));

	for(loop1 = 0; loop1 < 3; loop1++){
		switch(loop1){
			case 1:	// max
				for(loop2 = 0; loop2 < 9; loop2++){
					for(loop3 = 0; loop3 < 256; loop3++){
						cur_write_data.cur_write_flg[loop2][loop3] = 1;
						cur_write_data.cur_data[loop2][loop3] = 0xFF;
					}
				}
				break;

			case 2:	// individual
				for(loop2 = 0; loop2 < 9; loop2++){
					for(loop3 = 0; loop3 < 256; loop3++){
						cur_write_data.cur_write_flg[loop2][loop3] = (loop3 & 1);
						cur_write_data.cur_data[loop2][loop3] = (loop3 + 2) & 0xFF;
					}
				}
				break;

//			case 0:	// min
			default:
				for(loop2 = 0; loop2 < 9; loop2++){
					for(loop3 = 0; loop3 < 256; loop3++){
						cur_write_data.cur_write_flg[loop2][loop3] = 0;
						cur_write_data.cur_data[loop2][loop3] = 0;
					}
				}
				break;
		}

		priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh2_1_31: " "Set Cur error = 0x%x\n", priv->imErcd));
			return priv->imErcd;
		}

#ifdef CO_DEBUG_ON_PC
		for(loop2 = 0; loop2 < 9; loop2++){
			for(loop3 = 0; loop3 < 64; loop3++){
				Ddim_Print(("ct_im_bmh2_1_31: " "IO_BMH[%d].CUR.word[%d][%d] = 0x%lx\n", self->channelNo, loop2, loop3, IO_BMH[self->channelNo].CUR.word[loop2][loop3]));
			}
		}
#endif // CO_DEBUG_ON_PC
	}

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_32(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	kuint32 loop1, loop2, loop3;

	T_IM_BMH_REF_BLOCK ref_write_data;

	Ddim_Print(("%s\n", "ct_im_bmh2_1_32: "));

	for(loop1 = 0; loop1 < 3; loop1++){
		switch(loop1){
			case 1:	// max
				for(loop2 = 0; loop2 < 9; loop2++){
					for(loop3 = 0; loop3 < 256; loop3++){
						ref_write_data.ref_write_flg[loop2][loop3] = 1;
						ref_write_data.ref_data[loop2][loop3] = 0xFF;
					}
				}
				break;

			case 2:	// individual
				for(loop2 = 0; loop2 < 9; loop2++){
					for(loop3 = 0; loop3 < 256; loop3++){
						ref_write_data.ref_write_flg[loop2][loop3] = (loop3 & 1);
						ref_write_data.ref_data[loop2][loop3] = (loop3 + 2) & 0xFF;
					}
				}
				break;

//			case 0:	// min
			default:
				for(loop2 = 0; loop2 < 9; loop2++){
					for(loop3 = 0; loop3 < 256; loop3++){
						ref_write_data.ref_write_flg[loop2][loop3] = 0;
						ref_write_data.ref_data[loop2][loop3] = 0;
					}
				}
				break;
		}

		priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
		if(priv->imErcd != D_DDIM_OK){
			Ddim_Print(("ct_im_bmh2_1_32: " "Set Ref error = 0x%x\n", priv->imErcd));
			return priv->imErcd;
		}

#ifdef CO_DEBUG_ON_PC
		for(loop2 = 0; loop2 < 9; loop2++){
			for(loop3 = 0; loop3 < 64; loop3++){
				Ddim_Print(("ct_im_bmh2_1_32: " "IO_BMH[%d].REF.word[%d][%d] = 0x%lx\n", self->channelNo, loop2, loop3, IO_BMH[self->channelNo].REF.word[loop2][loop3]));
			}
		}
#endif // CO_DEBUG_ON_PC
	}

	return priv->imErcd;
}

kint32 ct_im_bmh2_1_33(CtImBmh2 *self)
{
	CtImBmh2Private *priv = CT_IM_BMH2_GET_PRIVATE(self);
	kuint32 i, j;
	T_IM_BMH_SADR_000 sadr_read_data;
	kulong loop1;
	kulong loop2;

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

	Ddim_Print(("%s\n", "ct_im_bmh2_1_33: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_33: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Init(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_33: " "Init error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_33: " "Set Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_33: " "Set Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
		IO_BMH[self->channelNo].BMHINTFS.bit.__BMHF = 1;
#endif //CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_33: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
	for(loop1 = 0; loop1 < 2; loop1++){
		for(loop2 = 0; loop2 < 56; loop2++){
			IO_BMH[self->channelNo].SADR.bit000[loop1][loop2].POS_0    = loop2;
			IO_BMH[self->channelNo].SADR.bit000[loop1][loop2].SADcmp_0 = loop1;
			IO_BMH[self->channelNo].SADR.bit000[loop1][loop2].POS_1    = loop2 + 1;
			IO_BMH[self->channelNo].SADR.bit000[loop1][loop2].SADcmp_1 = loop1;
			IO_BMH[self->channelNo].SADR.bit000[loop1][loop2].POS_2    = loop2 + 2;
			IO_BMH[self->channelNo].SADR.bit000[loop1][loop2].SADcmp_2 = loop1;
			IO_BMH[self->channelNo].SADR.bit000[loop1][loop2].POS_3    = loop2 + 3;
			IO_BMH[self->channelNo].SADR.bit000[loop1][loop2].SADcmp_3 = loop1;
		}
		IO_BMH[self->channelNo].SADR.bit000[loop1][56].POS_0    = loop2;
		IO_BMH[self->channelNo].SADR.bit000[loop1][56].SADcmp_0 = loop1;
	}
#endif // CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Get_Sadr_000(self->channelNo, &sadr_read_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_33: " "Get Sadr000 error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	for(loop1 = 0; loop1 < 2; loop1++){
		for(loop2 = 0; loop2 < 228; loop2++){
			Ddim_Print(("ct_im_bmh2_1_33: " "sadr_read_data.sadcmp[%lu][%lu] = 0x%x\n",loop1,loop2, sadr_read_data.sadcmp[loop1][loop2]));
			Ddim_Print(("ct_im_bmh2_1_33: " "sadr_read_data.pos[%lu][%lu]    = 0x%x\n",loop1,loop2, sadr_read_data.pos[loop1][loop2]));
		}
	}

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_33: " "Stop error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh2_1_33: " "Close error = 0x%x\n", priv->imErcd));
	}

	return priv->imErcd;
}

CtImBmh2* ct_im_bmh2_new(void) 
{
    CtImBmh2 *self = k_object_new_with_private(CT_TYPE_IM_BMH2, sizeof(CtImBmh2Private));
    return self;
}
