/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh3类
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

K_TYPE_DEFINE_WITH_PRIVATE(CtImBmh3, ct_im_bmh3);
#define CT_IM_BMH3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImBmh3Private,CT_TYPE_IM_BMH3))

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

struct _CtImBmh3Private
{
	kint32 imErcd;
};

/*
 * DECLS
 */
static void ctImBmh3Callback_cb(kulong interruptFlagMask);//回调方法被其他文件调用

static void ct_im_bmh3_constructor(CtImBmh3 *self) 
{
// CtImBmh3Private *priv = CT_IM_BMH3_GET_PRIVATE(self);
}

static void ct_im_bmh3_destructor(CtImBmh3 *self) 
{
//	CtImBmh3Private *priv = CT_IM_BMH3_GET_PRIVATE(self);
}

/*
 * IMPL
 */
static void ctImBmh3Callback_cb(kulong interruptFlagMask)
{
	Ddim_Print(("ctImBmh3Callback_cb interruptFlagMask = 0x%lx\n", interruptFlagMask));
}

/*
 * PUBLIC
 */
kint32 ct_im_bmh3_1_34(CtImBmh3 *self)
{
	CtImBmh3Private *priv = CT_IM_BMH3_GET_PRIVATE(self);
	kuint32 i, j;

	T_IM_BMH_CTRL bmh_ctrl = {
		.lselcnt = 0,
		.rbs = 0,
		.pshift = 0,
		.outmd = 1,
		.lutmd = 0,
		.offmd = 0,
		.mode = 1,
		.poffset = 0,
		.sadlv = 0,
		.pCallBack = ctImBmh3Callback_cb,
	};
	T_IM_BMH_SADR_001 sadr_read_data;
	kulong loop1;

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

	Ddim_Print(("%s\n", "ct_im_bmh3_1_34: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_34: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Init(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_34: " "Init error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_34: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_34: " "Set Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_34: " "Set Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
		IO_BMH[self->channelNo].BMHINTFS.bit.__BMHF = 1;
#endif //CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_34: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
	for(loop1 = 0; loop1 < 225; loop1++){
		IO_BMH[self->channelNo].SADR.bit001[loop1].SADmin = loop1;
		IO_BMH[self->channelNo].SADR.bit001[loop1].POS    = (loop1 & 0x7F);
		IO_BMH[self->channelNo].SADR.bit001[loop1].SADcmp = (loop1 & 1);
	}
#endif // CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Get_Sadr_001(self->channelNo, &sadr_read_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_34: " "Get Sadr001 error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	for(loop1 = 0; loop1 < 225; loop1++){
		Ddim_Print(("ct_im_bmh3_1_34: " "sadr_read_data.sadcmp[%lu] = 0x%x\n",loop1, sadr_read_data.sadcmp[loop1]));
		Ddim_Print(("ct_im_bmh3_1_34: " "sadr_read_data.pos[%lu]    = 0x%x\n",loop1, sadr_read_data.pos[loop1]));
		Ddim_Print(("ct_im_bmh3_1_34: " "sadr_read_data.sadmin[%lu] = 0x%x\n",loop1, sadr_read_data.sadmin[loop1]));
	}

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_34: " "Stop error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_34: " "Close error = 0x%x\n", priv->imErcd));
	}

	return priv->imErcd;
}

kint32 ct_im_bmh3_1_35(CtImBmh3 *self)
{
	CtImBmh3Private *priv = CT_IM_BMH3_GET_PRIVATE(self);
	kuint32 i, j;

	T_IM_BMH_CTRL bmh_ctrl = {
		.lselcnt = 0,
		.rbs = 0,
		.pshift = 0,
		.outmd = 2,
		.lutmd = 0,
		.offmd = 0,
		.mode = 1,
		.poffset = 0,
		.sadlv = 0,
		.pCallBack = ctImBmh3Callback_cb,
	};
	T_IM_BMH_SADR_010 sadr_read_data;
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

	Ddim_Print(("%s\n", "ct_im_bmh3_1_35: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_35: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Init(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_35: " "Init error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_35: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_35: " "Set Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_35: " "Set Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
		IO_BMH[self->channelNo].BMHINTFS.bit.__BMHF = 1;
#endif //CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_35: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
	for(loop1 = 0; loop1 < 2; loop1++){
		for(loop2 = 0; loop2 < 112; loop2++){
			IO_BMH[self->channelNo].SADR.bit010[loop1][loop2].POS_fraction_0 = ((0xFF - loop2) & 0x3F);
			IO_BMH[self->channelNo].SADR.bit010[loop1][loop2].POS_Integer_0  = loop2 + 1;
			IO_BMH[self->channelNo].SADR.bit010[loop1][loop2].SADcmp_0       = loop1;
			IO_BMH[self->channelNo].SADR.bit010[loop1][loop2].POS_fraction_1 = ((0xFE - loop2) & 0x3F);
			IO_BMH[self->channelNo].SADR.bit010[loop1][loop2].POS_Integer_1  = loop2 + 2;
			IO_BMH[self->channelNo].SADR.bit010[loop1][loop2].SADcmp_1       = loop1;
		}
		IO_BMH[self->channelNo].SADR.bit010[loop1][112].POS_fraction_0 = ((0xFF - loop2) & 0x3F);
		IO_BMH[self->channelNo].SADR.bit010[loop1][112].POS_Integer_0  = loop2 + 1;
		IO_BMH[self->channelNo].SADR.bit010[loop1][112].SADcmp_0       = loop1;
	}
#endif // CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Get_Sadr_010(self->channelNo, &sadr_read_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_35: " "Get Sadr010 error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
	}

	for(loop1 = 0; loop1 < 2; loop1++){
		for(loop2 = 0; loop2 < 226; loop2++){
			Ddim_Print(("ct_im_bmh3_1_35: " "sadr_read_data.sadcmp[%lu][%lu]       = 0x%x\n",loop1,loop2, sadr_read_data.sadcmp[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_35: " "sadr_read_data.pos_integer[%lu][%lu]  = 0x%x\n",loop1,loop2, sadr_read_data.pos_integer[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_35: " "sadr_read_data.pos_fraction[%lu][%lu] = 0x%x\n",loop1,loop2, sadr_read_data.pos_fraction[loop1][loop2]));
		}
	}

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_35: " "Stop error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_35: " "Close error = 0x%x\n", priv->imErcd));
	}

	return priv->imErcd;
}

kint32 ct_im_bmh3_1_36(CtImBmh3 *self)
{
	CtImBmh3Private *priv = CT_IM_BMH3_GET_PRIVATE(self);
	kuint32 i, j;

	T_IM_BMH_CTRL bmh_ctrl = {
		.lselcnt = 0,
		.rbs = 0,
		.pshift = 0,
		.outmd = 3,
		.lutmd = 0,
		.offmd = 0,
		.mode = 1,
		.poffset = 0,
		.sadlv = 0,
		.pCallBack = ctImBmh3Callback_cb,
	};
	T_IM_BMH_SADR_011 sadr_read_data;
	kulong loop1;

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

	Ddim_Print(("%s\n", "ct_im_bmh3_1_36: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_36: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Init(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_36: " "Init error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_36: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_36: " "Set Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_36: " "Set Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
		IO_BMH[self->channelNo].BMHINTFS.bit.__BMHF = 1;
#endif //CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_36: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
	for(loop1 = 0; loop1 < 225; loop1++){
		IO_BMH[self->channelNo].SADR.bit011[loop1].SADmin       = loop1;
		IO_BMH[self->channelNo].SADR.bit011[loop1].POS_fraction = ((0xFF - loop1) & 0x3F);
		IO_BMH[self->channelNo].SADR.bit011[loop1].POS_Integer  = (loop1 & 0x7F);
		IO_BMH[self->channelNo].SADR.bit011[loop1].SADcmp       = (loop1 & 1);
	}
#endif // CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Get_Sadr_011(self->channelNo, &sadr_read_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_36: " "Im_BMH_Get_Sadr_011 error = 0x%x\n", priv->imErcd));
	}

	for(loop1 = 0; loop1 < 225; loop1++){
		Ddim_Print(("ct_im_bmh3_1_36: " "sadr_read_data.sadcmp[%lu]       = 0x%x\n",loop1, sadr_read_data.sadcmp[loop1]));
		Ddim_Print(("ct_im_bmh3_1_36: " "sadr_read_data.pos_integer[%lu]  = 0x%x\n",loop1, sadr_read_data.pos_integer[loop1]));
		Ddim_Print(("ct_im_bmh3_1_36: " "sadr_read_data.pos_fraction[%lu] = 0x%x\n",loop1, sadr_read_data.pos_fraction[loop1]));
		Ddim_Print(("ct_im_bmh3_1_36: " "sadr_read_data.sadmin[%lu]       = 0x%x\n",loop1, sadr_read_data.sadmin[loop1]));
	}

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_36: " "Stop error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_36: " "Close error = 0x%x\n", priv->imErcd));
	}

	return priv->imErcd;
}

kint32 ct_im_bmh3_1_37(CtImBmh3 *self)
{
	CtImBmh3Private *priv = CT_IM_BMH3_GET_PRIVATE(self);
	kuint32 i, j;

	T_IM_BMH_CTRL bmh_ctrl = {
		.lselcnt = 0,
		.rbs = 0,
		.pshift = 0,
		.outmd = 4,
		.lutmd = 0,
		.offmd = 0,
		.mode = 1,
		.poffset = 0,
		.sadlv = 0,
		.pCallBack = ctImBmh3Callback_cb,
	};
	T_IM_BMH_SADR_100 sadr_read_data;
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

	Ddim_Print(("%s\n", "ct_im_bmh3_1_37: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_37: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Init(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_37: " "Init error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_37: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_37: " "Set Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_37: " "Set Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
		IO_BMH[self->channelNo].BMHINTFS.bit.__BMHF = 1;
#endif //CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_37: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
	for(loop1 = 0; loop1 < 2; loop1++){
		for(loop2 = 0; loop2 < 112; loop2++){
			IO_BMH[self->channelNo].SADR.bit100[loop1][loop2].SADmin       = loop2;
			IO_BMH[self->channelNo].SADR.bit100[loop1][loop2].POS_fraction = ((0xFF - loop2) & 0x3F);
			IO_BMH[self->channelNo].SADR.bit100[loop1][loop2].POS_Integer  = loop2 + 1;
			IO_BMH[self->channelNo].SADR.bit100[loop1][loop2].SADcmp       = loop1;
		}
	}
#endif // CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Get_Sadr_100(self->channelNo, &sadr_read_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_37: " "Get Sadr100 error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
	}

	for(loop1 = 0; loop1 < 2; loop1++){
		for(loop2 = 0; loop2 < 112; loop2++){
			Ddim_Print(("ct_im_bmh3_1_37: " "sadr_read_data.sadcmp[%lu][%lu]       = 0x%x\n",loop1,loop2, sadr_read_data.sadcmp[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_37: " "sadr_read_data.pos_integer[%lu][%lu]  = 0x%x\n",loop1,loop2, sadr_read_data.pos_integer[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_37: " "sadr_read_data.pos_fraction[%lu][%lu] = 0x%x\n",loop1,loop2, sadr_read_data.pos_fraction[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_37: " "sadr_read_data.sadmin[%lu][%lu]       = 0x%x\n",loop1,loop2, sadr_read_data.sadmin[loop1][loop2]));
		}
	}

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_37: " "Stop error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_37: " "Close error = 0x%x\n", priv->imErcd));
	}

	return priv->imErcd;
}

kint32 ct_im_bmh3_1_38(CtImBmh3 *self)
{
	CtImBmh3Private *priv = CT_IM_BMH3_GET_PRIVATE(self);
	kuint32 i, j;

	T_IM_BMH_CTRL bmh_ctrl = {
		.lselcnt = 0,
		.rbs = 0,
		.pshift = 0,
		.outmd = 5,
		.lutmd = 0,
		.offmd = 0,
		.mode = 1,
		.poffset = 0,
		.sadlv = 0,
		.pCallBack = ctImBmh3Callback_cb,
	};
	T_IM_BMH_SADR_101 sadr_read_data;
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

	Ddim_Print(("%s\n", "ct_im_bmh3_1_38: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_38: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Init(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_38: " "Init error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_38: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_38: " "Set Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_38: " "Set Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
		IO_BMH[self->channelNo].BMHINTFS.bit.__BMHF = 1;
#endif //CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_38: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
	for(loop1 = 0; loop1 < 2; loop1++){
		for(loop2 = 0; loop2 < 56; loop2++){
			IO_BMH[self->channelNo].SADR.bit101[loop1][loop2].SADmin       = loop2;
			IO_BMH[self->channelNo].SADR.bit101[loop1][loop2].POS_fraction = 0x3F - loop2;
			IO_BMH[self->channelNo].SADR.bit101[loop1][loop2].POS_Integer  = loop2 + 1;
			IO_BMH[self->channelNo].SADR.bit101[loop1][loop2].SADcmp       = loop1;
			IO_BMH[self->channelNo].SADR.bit101[loop1][loop2].CUR_MIN      = loop2 + 2;
			IO_BMH[self->channelNo].SADR.bit101[loop1][loop2].CUR_MAX      = loop2 + 3;
			IO_BMH[self->channelNo].SADR.bit101[loop1][loop2].Deviation    = loop2 + 4;
			IO_BMH[self->channelNo].SADR.bit101[loop1][loop2].Weight       = loop2 + 5;
		}
	}
#endif // CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Get_Sadr_101(self->channelNo, &sadr_read_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_38: " "Im_BMH_Get_Sadr_101 error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
	}

	for(loop1 = 0; loop1 < 2; loop1++){
		for(loop2 = 0; loop2 < 56; loop2++){
			Ddim_Print(("ct_im_bmh3_1_38: " "sadr_read_data.sadcmp[%lu][%lu]       = 0x%x\n",loop1,loop2, sadr_read_data.sadcmp[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_38: " "sadr_read_data.pos_integer[%lu][%lu]  = 0x%x\n",loop1,loop2, sadr_read_data.pos_integer[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_38: " "sadr_read_data.pos_fraction[%lu][%lu] = 0x%x\n",loop1,loop2, sadr_read_data.pos_fraction[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_38: " "sadr_read_data.sadmin[%lu][%lu]       = 0x%x\n",loop1,loop2, sadr_read_data.sadmin[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_38: " "sadr_read_data.weight[%lu][%lu]       = 0x%x\n",loop1,loop2, sadr_read_data.weight[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_38: " "sadr_read_data.deviation[%lu][%lu]    = 0x%x\n",loop1,loop2, sadr_read_data.deviation[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_38: " "sadr_read_data.cur_max[%lu][%lu]      = 0x%x\n",loop1,loop2, sadr_read_data.cur_max[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_38: " "sadr_read_data.cur_min[%lu][%lu]      = 0x%x\n",loop1,loop2, sadr_read_data.cur_min[loop1][loop2]));
		}
	}

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_38: " "Stop error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_38: " "Close error = 0x%x\n", priv->imErcd));
	}

	return priv->imErcd;
}

kint32 ct_im_bmh3_1_39(CtImBmh3 *self)
{
	CtImBmh3Private *priv = CT_IM_BMH3_GET_PRIVATE(self);
	kuint32 i, j;

	T_IM_BMH_CTRL bmh_ctrl = {
		.lselcnt = 0,
		.rbs = 0,
		.pshift = 0,
		.outmd = 6,
		.lutmd = 0,
		.offmd = 0,
		.mode = 1,
		.poffset = 0,
		.sadlv = 0,
		.pCallBack = ctImBmh3Callback_cb,
	};
	T_IM_BMH_SADR_110 sadr_read_data;
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

	Ddim_Print(("%s\n", "ct_im_bmh3_1_39: "));

	priv->imErcd = Im_BMH_Open(self->channelNo, 100);	// wai_sem timeout 100 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_39: " "Open error = 0x%x\n", priv->imErcd));
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Init(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_39: " "Init error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Ctrl(self->channelNo, &bmh_ctrl);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_39: " "Ctrl error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Cur(self->channelNo, &cur_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_39: " "Set Cur error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

	priv->imErcd = Im_BMH_Set_Ref(self->channelNo, &ref_write_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_39: " "Set Ref error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
		IO_BMH[self->channelNo].BMHINTFS.bit.__BMHF = 1;
#endif //CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Start_Sync(self->channelNo, 1000);	// wait timeout 1000 ticks
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_39: " "Start Sync error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
		return priv->imErcd;
	}

#ifdef CO_DEBUG_ON_PC
	for(loop1 = 0; loop1 < 2; loop1++){
		for(loop2 = 0; loop2 < 28; loop2++){
			IO_BMH[self->channelNo].SADR.bit110[loop1][loop2].SADmin        = loop2;
			IO_BMH[self->channelNo].SADR.bit110[loop1][loop2].POS           = loop2 + 1;
			IO_BMH[self->channelNo].SADR.bit110[loop1][loop2].SADcmp        = loop1;
			IO_BMH[self->channelNo].SADR.bit110[loop1][loop2].SADmin1after  = loop2 + 2;
			IO_BMH[self->channelNo].SADR.bit110[loop1][loop2].SADmin1before = loop2 + 3;
			IO_BMH[self->channelNo].SADR.bit110[loop1][loop2].SADmin2after  = loop2 + 4;
			IO_BMH[self->channelNo].SADR.bit110[loop1][loop2].SADmin2before = loop2 + 5;
			IO_BMH[self->channelNo].SADR.bit110[loop1][loop2].CUR_MIN       = loop2 + 6;
			IO_BMH[self->channelNo].SADR.bit110[loop1][loop2].CUR_MAX       = loop2 + 7;
			IO_BMH[self->channelNo].SADR.bit110[loop1][loop2].Deviation     = loop2 + 8;
			IO_BMH[self->channelNo].SADR.bit110[loop1][loop2].Weight        = loop2 + 9;
		}
	}
#endif // CO_DEBUG_ON_PC

	priv->imErcd = Im_BMH_Get_Sadr_110(self->channelNo, &sadr_read_data);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_39: " "Im_BMH_Get_Sadr_110 error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
	}

	for(loop1 = 0; loop1 < 2; loop1++){
		for(loop2 = 0; loop2 < 28; loop2++){
			Ddim_Print(("ct_im_bmh3_1_39: " "sadr_read_data.sadcmp[%lu][%lu]        = 0x%x\n",loop1,loop2, sadr_read_data.sadcmp[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_39: " "sadr_read_data.pos[%lu][%lu]           = 0x%x\n",loop1,loop2, sadr_read_data.pos[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_39: " "sadr_read_data.sadmin[%lu][%lu]        = 0x%x\n",loop1,loop2, sadr_read_data.sadmin[loop1][loop2]));

			Ddim_Print(("ct_im_bmh3_1_39: " "sadr_read_data.sadmin1before[%lu][%lu] = 0x%x\n",loop1,loop2, sadr_read_data.sadmin1before[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_39: " "sadr_read_data.sadmin1after[%lu][%lu]  = 0x%x\n",loop1,loop2, sadr_read_data.sadmin1after[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_39: " "sadr_read_data.sadmin2before[%lu][%lu] = 0x%x\n",loop1,loop2, sadr_read_data.sadmin2before[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_39: " "sadr_read_data.sadmin2after[%lu][%lu]  = 0x%x\n",loop1,loop2, sadr_read_data.sadmin2after[loop1][loop2]));

			Ddim_Print(("ct_im_bmh3_1_39: " "sadr_read_data.weight[%lu][%lu]        = 0x%x\n",loop1,loop2, sadr_read_data.weight[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_39: " "sadr_read_data.deviation[%lu][%lu]     = 0x%x\n",loop1,loop2, sadr_read_data.deviation[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_39: " "sadr_read_data.cur_max[%lu][%lu]       = 0x%x\n",loop1,loop2, sadr_read_data.cur_max[loop1][loop2]));
			Ddim_Print(("ct_im_bmh3_1_39: " "sadr_read_data.cur_min[%lu][%lu]       = 0x%x\n",loop1,loop2, sadr_read_data.cur_min[loop1][loop2]));
		}
	}

	priv->imErcd = Im_BMH_Stop(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_39: " "Stop error = 0x%x\n", priv->imErcd));
		Im_BMH_Close(self->channelNo);
	}

	priv->imErcd = Im_BMH_Close(self->channelNo);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("ct_im_bmh3_1_39: " "Close error = 0x%x\n", priv->imErcd));
	}

	return priv->imErcd;
}

CtImBmh3* ct_im_bmh3_new(void) 
{
    CtImBmh3 *self = k_object_new_with_private(CT_TYPE_IM_BMH3, sizeof(CtImBmh3Private));
    return self;
}
