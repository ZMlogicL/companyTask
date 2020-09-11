/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmLtm3类
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#include <stdlib.h>
#include <string.h>
#include "ct_im_b2r.h"
#include "ct_im_ltm.h"
#include "im_b2r.h"
#include "im_ltm.h"
#include "im_r2y.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif
#include "jdsimg.h"
#include "jdsltm.h"

#include "ctimltmltm.h"
#include "ctimltmltm3.h"

G_DEFINE_TYPE(CtImLtmLtm3, ct_im_ltm_ltm3, G_TYPE_OBJECT);

#define CT_IM_LTM_LTM3_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_LTM_LTM_3, CtImLtmLtm3Private))

struct _CtImLtmLtm3Private
{
	CtImLtmLtm4 *ltm43;
};
/*
 *DECLS
 * */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);


static void ct_im_ltm_ltm3_class_init(CtImLtmLtm3Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImLtmLtm3Private));
}

static void ct_im_ltm_ltm3_init(CtImLtmLtm3 *self)
{
//	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
}
/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
//	CtImLtmLtm3 *self = (CtImLtmLtm3*)object;
//	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_ltm3_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImLtmLtm3 *self = (CtImLtmLtm3*)object;
//	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_ltm3_parent_class)->finalize(object);
}
/*
 *PUBLIC
 * */
#ifdef IM_LTM_STATUS_PRINT
extern void Im_LTM_LTM_Print_Status(void);
#endif

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_1: "
gint32 ct_im_ltm_ltm3_1_1(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	gint32 ercd;

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	ercd = Im_LTM_LTM_Init(priv->ltm43->pipeNo);

	Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P1.LTM.LTMSR   = 0x%lx\n", IO_LTM_P1.LTM.LTMSR.word));
	Ddim_Print(("IO_LTM_P1.LTM.LSRAMEN = 0x%lx\n", IO_LTM_P1.LTM.LSRAMEN.word));
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P2.LTM.LTMSR   = 0x%lx\n", IO_LTM_P2.LTM.LTMSR.word));
	Ddim_Print(("IO_LTM_P2.LTM.LSRAMEN = 0x%lx\n", IO_LTM_P2.LTM.LSRAMEN.word));
	Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);

	return ercd;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_2: "
gint32 ct_im_ltm_ltm3_1_2(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	guint32					loopCnt;
	T_IM_LTM_LTM_CTRL_AXI	ltmCtrlAxi[] =
	{
		[0] =
		{	// max
			.rch_rgb[0].cache_type = 0xF,
			.rch_rgb[0].protect_type = 7,
			.rch_rgb[1].cache_type = 0xF,
			.rch_rgb[1].protect_type = 7,
			.rch_rgb[2].cache_type = 0xF,
			.rch_rgb[2].protect_type = 7,
			.rch_y[0].cache_type = 0xF,
			.rch_y[0].protect_type = 7,
			.rch_y[1].cache_type = 0xF,
			.rch_y[1].protect_type = 7,
			.wch[0].cache_type = 0xF,
			.wch[0].protect_type = 7,
			.wch[1].cache_type = 0xF,
			.wch[1].protect_type = 7,
			.wch[2].cache_type = 0xF,
			.wch[2].protect_type = 7,
		},
		[1] =
		{	// min
			.rch_rgb[0].cache_type = 0,
			.rch_rgb[0].protect_type = 0,
			.rch_rgb[1].cache_type = 0,
			.rch_rgb[1].protect_type = 0,
			.rch_rgb[2].cache_type = 0,
			.rch_rgb[2].protect_type = 0,
			.rch_y[0].cache_type = 0,
			.rch_y[0].protect_type = 0,
			.rch_y[1].cache_type = 0,
			.rch_y[1].protect_type = 0,
			.wch[0].cache_type = 0,
			.wch[0].protect_type = 0,
			.wch[1].cache_type = 0,
			.wch[1].protect_type = 0,
			.wch[2].cache_type = 0,
			.wch[2].protect_type = 0,
		},
	};

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < (sizeof(ltmCtrlAxi) / sizeof(ltmCtrlAxi[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Ctrl_Axi(priv->ltm43->pipeNo, &ltmCtrlAxi[loopCnt]);

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLR1.bit.ARCACHE_R  = %u\n", IO_LTM_P1.LTM.LAXICTLR1.bit.ARCACHE_R));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLR1.bit.ARPROT_R   = %u\n", IO_LTM_P1.LTM.LAXICTLR1.bit.ARPROT_R));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLR1.bit.ARCACHE_G  = %u\n", IO_LTM_P1.LTM.LAXICTLR1.bit.ARCACHE_G));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLR1.bit.ARPROT_G   = %u\n", IO_LTM_P1.LTM.LAXICTLR1.bit.ARPROT_G));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLR1.bit.ARCACHE_B  = %u\n", IO_LTM_P1.LTM.LAXICTLR1.bit.ARCACHE_B));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLR1.bit.ARPROT_B   = %u\n", IO_LTM_P1.LTM.LAXICTLR1.bit.ARPROT_B));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLR2.bit.ARCACHE_YP = %u\n", IO_LTM_P1.LTM.LAXICTLR2.bit.ARCACHE_YP));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLR2.bit.ARPROT_YP  = %u\n", IO_LTM_P1.LTM.LAXICTLR2.bit.ARPROT_YP));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLR2.bit.ARCACHE_YN = %u\n", IO_LTM_P1.LTM.LAXICTLR2.bit.ARCACHE_YN));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLR2.bit.ARPROT_YN  = %u\n", IO_LTM_P1.LTM.LAXICTLR2.bit.ARPROT_YN));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLW.bit.AWCACHE_R   = %u\n", IO_LTM_P1.LTM.LAXICTLW.bit.AWCACHE_R));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLW.bit.AWPROT_R    = %u\n", IO_LTM_P1.LTM.LAXICTLW.bit.AWPROT_R));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLW.bit.AWCACHE_G   = %u\n", IO_LTM_P1.LTM.LAXICTLW.bit.AWCACHE_G));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLW.bit.AWPROT_G    = %u\n", IO_LTM_P1.LTM.LAXICTLW.bit.AWPROT_G));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLW.bit.AWCACHE_B   = %u\n", IO_LTM_P1.LTM.LAXICTLW.bit.AWCACHE_B));
		Ddim_Print(("IO_LTM_P1.LTM.LAXICTLW.bit.AWPROT_B    = %u\n", IO_LTM_P1.LTM.LAXICTLW.bit.AWPROT_B));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLR1.bit.ARCACHE_R  = %u\n", IO_LTM_P2.LTM.LAXICTLR1.bit.ARCACHE_R));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLR1.bit.ARPROT_R   = %u\n", IO_LTM_P2.LTM.LAXICTLR1.bit.ARPROT_R));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLR1.bit.ARCACHE_G  = %u\n", IO_LTM_P2.LTM.LAXICTLR1.bit.ARCACHE_G));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLR1.bit.ARPROT_G   = %u\n", IO_LTM_P2.LTM.LAXICTLR1.bit.ARPROT_G));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLR1.bit.ARCACHE_B  = %u\n", IO_LTM_P2.LTM.LAXICTLR1.bit.ARCACHE_B));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLR1.bit.ARPROT_B   = %u\n", IO_LTM_P2.LTM.LAXICTLR1.bit.ARPROT_B));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLR2.bit.ARCACHE_YP = %u\n", IO_LTM_P2.LTM.LAXICTLR2.bit.ARCACHE_YP));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLR2.bit.ARPROT_YP  = %u\n", IO_LTM_P2.LTM.LAXICTLR2.bit.ARPROT_YP));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLR2.bit.ARCACHE_YN = %u\n", IO_LTM_P2.LTM.LAXICTLR2.bit.ARCACHE_YN));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLR2.bit.ARPROT_YN  = %u\n", IO_LTM_P2.LTM.LAXICTLR2.bit.ARPROT_YN));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLW.bit.AWCACHE_R   = %u\n", IO_LTM_P2.LTM.LAXICTLW.bit.AWCACHE_R));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLW.bit.AWPROT_R    = %u\n", IO_LTM_P2.LTM.LAXICTLW.bit.AWPROT_R));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLW.bit.AWCACHE_G   = %u\n", IO_LTM_P2.LTM.LAXICTLW.bit.AWCACHE_G));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLW.bit.AWPROT_G    = %u\n", IO_LTM_P2.LTM.LAXICTLW.bit.AWPROT_G));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLW.bit.AWCACHE_B   = %u\n", IO_LTM_P2.LTM.LAXICTLW.bit.AWCACHE_B));
		Ddim_Print(("IO_LTM_P2.LTM.LAXICTLW.bit.AWPROT_B    = %u\n", IO_LTM_P2.LTM.LAXICTLW.bit.AWPROT_B));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_3: "
gint32 ct_im_ltm_ltm3_1_3(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	T_IM_LTM_LTM_AXI_RCH_STAT ltmAxiReadStat;

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

#ifdef CO_DEBUG_ON_PC
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm43->pipeNo)){
		IO_LTM_P1.LTM.LAXIRERR.bit.RRESP_R  = 3;
		IO_LTM_P1.LTM.LAXIRERR.bit.RRESP_G  = 3;
		IO_LTM_P1.LTM.LAXIRERR.bit.RRESP_B  = 3;
		IO_LTM_P1.LTM.LAXIRERR.bit.RRESP_YP = 3;
		IO_LTM_P1.LTM.LAXIRERR.bit.RRESP_YN = 3;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm43->pipeNo)){
		IO_LTM_P2.LTM.LAXIRERR.bit.RRESP_R  = 3;
		IO_LTM_P2.LTM.LAXIRERR.bit.RRESP_G  = 3;
		IO_LTM_P2.LTM.LAXIRERR.bit.RRESP_B  = 3;
		IO_LTM_P2.LTM.LAXIRERR.bit.RRESP_YP = 3;
		IO_LTM_P2.LTM.LAXIRERR.bit.RRESP_YN = 3;
	}
#endif // CO_DEBUG_ON_PC
	memset(&ltmAxiReadStat, '\0', sizeof(ltmAxiReadStat));
	Im_LTM_LTM_Get_AxiReadStat(priv->ltm43->pipeNo, &ltmAxiReadStat);
	Ddim_Print(("rch_rgb_axi_stat[0] = %u\n", ltmAxiReadStat.rch_rgb_axi_stat[0]));
	Ddim_Print(("rch_rgb_axi_stat[1] = %u\n", ltmAxiReadStat.rch_rgb_axi_stat[1]));
	Ddim_Print(("rch_rgb_axi_stat[2] = %u\n", ltmAxiReadStat.rch_rgb_axi_stat[2]));
	Ddim_Print(("rch_y_axi_stat[0]   = %u\n", ltmAxiReadStat.rch_y_axi_stat[0]));
	Ddim_Print(("rch_y_axi_stat[1]   = %u\n", ltmAxiReadStat.rch_y_axi_stat[1]));

#ifdef CO_DEBUG_ON_PC
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm43->pipeNo)){
		IO_LTM_P1.LTM.LAXIRERR.bit.RRESP_R  = 0;
		IO_LTM_P1.LTM.LAXIRERR.bit.RRESP_G  = 0;
		IO_LTM_P1.LTM.LAXIRERR.bit.RRESP_B  = 0;
		IO_LTM_P1.LTM.LAXIRERR.bit.RRESP_YP = 0;
		IO_LTM_P1.LTM.LAXIRERR.bit.RRESP_YN = 0;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm43->pipeNo)){
		IO_LTM_P2.LTM.LAXIRERR.bit.RRESP_R  = 0;
		IO_LTM_P2.LTM.LAXIRERR.bit.RRESP_G  = 0;
		IO_LTM_P2.LTM.LAXIRERR.bit.RRESP_B  = 0;
		IO_LTM_P2.LTM.LAXIRERR.bit.RRESP_YP = 0;
		IO_LTM_P2.LTM.LAXIRERR.bit.RRESP_YN = 0;
	}
#endif // CO_DEBUG_ON_PC
	memset(&ltmAxiReadStat, '\0', sizeof(ltmAxiReadStat));
	Im_LTM_LTM_Get_AxiReadStat(priv->ltm43->pipeNo, &ltmAxiReadStat);
	Ddim_Print(("rch_rgb_axi_stat[0] = %u\n", ltmAxiReadStat.rch_rgb_axi_stat[0]));
	Ddim_Print(("rch_rgb_axi_stat[1] = %u\n", ltmAxiReadStat.rch_rgb_axi_stat[1]));
	Ddim_Print(("rch_rgb_axi_stat[2] = %u\n", ltmAxiReadStat.rch_rgb_axi_stat[2]));
	Ddim_Print(("rch_y_axi_stat[0]   = %u\n", ltmAxiReadStat.rch_y_axi_stat[0]));
	Ddim_Print(("rch_y_axi_stat[1]   = %u\n", ltmAxiReadStat.rch_y_axi_stat[1]));

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_4: "
gint32 ct_im_ltm_ltm3_1_4(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	T_IM_LTM_LTM_AXI_WCH_STAT ltmAxiWriteStat;

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

#ifdef CO_DEBUG_ON_PC
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm43->pipeNo)){
		IO_LTM_P1.LTM.LAXIWERR.bit.WRESP_R = 3;
		IO_LTM_P1.LTM.LAXIWERR.bit.WRESP_G = 3;
		IO_LTM_P1.LTM.LAXIWERR.bit.WRESP_B = 3;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm43->pipeNo)){
		IO_LTM_P2.LTM.LAXIWERR.bit.WRESP_R = 3;
		IO_LTM_P2.LTM.LAXIWERR.bit.WRESP_G = 3;
		IO_LTM_P2.LTM.LAXIWERR.bit.WRESP_B = 3;
	}
#endif // CO_DEBUG_ON_PC
	memset(&ltmAxiWriteStat, '\0', sizeof(ltmAxiWriteStat));
	Im_LTM_LTM_Get_AxiWriteStat(priv->ltm43->pipeNo, &ltmAxiWriteStat);
	Ddim_Print(("wch_axi_stat[0] = %u\n", ltmAxiWriteStat.wch_axi_stat[0]));
	Ddim_Print(("wch_axi_stat[1] = %u\n", ltmAxiWriteStat.wch_axi_stat[1]));
	Ddim_Print(("wch_axi_stat[2] = %u\n", ltmAxiWriteStat.wch_axi_stat[2]));

#ifdef CO_DEBUG_ON_PC
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm43->pipeNo)){
		IO_LTM_P1.LTM.LAXIWERR.bit.WRESP_R = 0;
		IO_LTM_P1.LTM.LAXIWERR.bit.WRESP_G = 0;
		IO_LTM_P1.LTM.LAXIWERR.bit.WRESP_B = 0;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm43->pipeNo)){
		IO_LTM_P2.LTM.LAXIWERR.bit.WRESP_R = 0;
		IO_LTM_P2.LTM.LAXIWERR.bit.WRESP_G = 0;
		IO_LTM_P2.LTM.LAXIWERR.bit.WRESP_B = 0;
	}
#endif // CO_DEBUG_ON_PC
	memset(&ltmAxiWriteStat, '\0', sizeof(ltmAxiWriteStat));
	Im_LTM_LTM_Get_AxiWriteStat(priv->ltm43->pipeNo, &ltmAxiWriteStat);
	Ddim_Print(("wch_axi_stat[0] = %u\n", ltmAxiWriteStat.wch_axi_stat[0]));
	Ddim_Print(("wch_axi_stat[1] = %u\n", ltmAxiWriteStat.wch_axi_stat[1]));
	Ddim_Print(("wch_axi_stat[2] = %u\n", ltmAxiWriteStat.wch_axi_stat[2]));

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_5: "
gint32 ct_im_ltm_ltm3_1_5(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	T_IM_LTM_LTM_AXI_CTRL_PARAM ltmAxiCtrlParam;

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm43->pipeNo)){
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRR  = 1;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRG  = 1;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRB  = 1;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRYP = 1;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRYN = 1;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWR  = 1;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWG  = 1;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWB  = 1;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKR = 1;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKG = 1;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKB = 1;
		IO_LTM_P1.LTM.AXIRSEL.bit.AXIRSEL1  = 1;
		IO_LTM_P1.LTM.AXIRSEL.bit.AXIRSEL2  = 1;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm43->pipeNo)){
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRR  = 1;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRG  = 1;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRB  = 1;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRYP = 1;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRYN = 1;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWR  = 1;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWG  = 1;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWB  = 1;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKR = 1;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKG = 1;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKB = 1;
		IO_LTM_P2.LTM.AXIRSEL.bit.AXIRSEL1  = 1;
		IO_LTM_P2.LTM.AXIRSEL.bit.AXIRSEL2  = 1;
	}
	memset(&ltmAxiCtrlParam, '\0', sizeof(ltmAxiCtrlParam));
	Im_LTM_LTM_Get_AxiCtrlParam(priv->ltm43->pipeNo, &ltmAxiCtrlParam);
	Ddim_Print(("rch_burst_length_r  = %u\n", ltmAxiCtrlParam.rch_burst_length_r));
	Ddim_Print(("rch_burst_length_g  = %u\n", ltmAxiCtrlParam.rch_burst_length_g));
	Ddim_Print(("rch_burst_length_b  = %u\n", ltmAxiCtrlParam.rch_burst_length_b));
	Ddim_Print(("rch_burst_length_yp = %u\n", ltmAxiCtrlParam.rch_burst_length_yp));
	Ddim_Print(("rch_burst_length_yn = %u\n", ltmAxiCtrlParam.rch_burst_length_yn));
	Ddim_Print(("wch_burst_length_r  = %u\n", ltmAxiCtrlParam.wch_burst_length_r));
	Ddim_Print(("wch_burst_length_g  = %u\n", ltmAxiCtrlParam.wch_burst_length_g));
	Ddim_Print(("wch_burst_length_b  = %u\n", ltmAxiCtrlParam.wch_burst_length_b));
	Ddim_Print(("mask_write_r        = %u\n", ltmAxiCtrlParam.mask_write_r));
	Ddim_Print(("mask_write_g        = %u\n", ltmAxiCtrlParam.mask_write_g));
	Ddim_Print(("mask_write_b        = %u\n", ltmAxiCtrlParam.mask_write_b));
	Ddim_Print(("read_select_yp      = %u\n", ltmAxiCtrlParam.read_select_yp));
	Ddim_Print(("read_select_yn      = %u\n", ltmAxiCtrlParam.read_select_yn));

	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm43->pipeNo)){
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRR  = 0;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRG  = 0;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRB  = 0;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRYP = 0;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRYN = 0;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWR  = 0;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWG  = 0;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWB  = 0;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKR = 0;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKG = 0;
		IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKB = 0;
		IO_LTM_P1.LTM.AXIRSEL.bit.AXIRSEL1  = 0;
		IO_LTM_P1.LTM.AXIRSEL.bit.AXIRSEL2  = 0;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm43->pipeNo)){
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRR  = 0;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRG  = 0;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRB  = 0;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRYP = 0;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRYN = 0;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWR  = 0;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWG  = 0;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWB  = 0;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKR = 0;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKG = 0;
		IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKB = 0;
		IO_LTM_P2.LTM.AXIRSEL.bit.AXIRSEL1  = 0;
		IO_LTM_P2.LTM.AXIRSEL.bit.AXIRSEL2  = 0;
	}
	memset(&ltmAxiCtrlParam, '\0', sizeof(ltmAxiCtrlParam));
	Im_LTM_LTM_Get_AxiCtrlParam(priv->ltm43->pipeNo, &ltmAxiCtrlParam);
	Ddim_Print(("rch_burst_length_r  = %u\n", ltmAxiCtrlParam.rch_burst_length_r));
	Ddim_Print(("rch_burst_length_g  = %u\n", ltmAxiCtrlParam.rch_burst_length_g));
	Ddim_Print(("rch_burst_length_b  = %u\n", ltmAxiCtrlParam.rch_burst_length_b));
	Ddim_Print(("rch_burst_length_yp = %u\n", ltmAxiCtrlParam.rch_burst_length_yp));
	Ddim_Print(("rch_burst_length_yn = %u\n", ltmAxiCtrlParam.rch_burst_length_yn));
	Ddim_Print(("wch_burst_length_r  = %u\n", ltmAxiCtrlParam.wch_burst_length_r));
	Ddim_Print(("wch_burst_length_g  = %u\n", ltmAxiCtrlParam.wch_burst_length_g));
	Ddim_Print(("wch_burst_length_b  = %u\n", ltmAxiCtrlParam.wch_burst_length_b));
	Ddim_Print(("mask_write_r        = %u\n", ltmAxiCtrlParam.mask_write_r));
	Ddim_Print(("mask_write_g        = %u\n", ltmAxiCtrlParam.mask_write_g));
	Ddim_Print(("mask_write_b        = %u\n", ltmAxiCtrlParam.mask_write_b));
	Ddim_Print(("read_select_yp      = %u\n", ltmAxiCtrlParam.read_select_yp));
	Ddim_Print(("read_select_yn      = %u\n", ltmAxiCtrlParam.read_select_yn));

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_6: "
gint32 ct_im_ltm_ltm3_1_6(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	guint32						loopCnt;
	T_IM_LTM_LTM_AXI_CTRL_PARAM	ltmAxiCtrlParam[] =
	{
		[0] =
		{	// max
			.rch_burst_length_r = 1,
			.rch_burst_length_g = 1,
			.rch_burst_length_b = 1,
			.rch_burst_length_yp = 1,
			.rch_burst_length_yn = 1,
			.wch_burst_length_r = 1,
			.wch_burst_length_g = 1,
			.wch_burst_length_b = 1,
			.mask_write_r = 1,
			.mask_write_g = 1,
			.mask_write_b = 1,
			.read_select_yp = 1,
			.read_select_yn = 1,
		},
		[1] =
		{	// min
			.rch_burst_length_r = 0,
			.rch_burst_length_g = 0,
			.rch_burst_length_b = 0,
			.rch_burst_length_yp = 0,
			.rch_burst_length_yn = 0,
			.wch_burst_length_r = 0,
			.wch_burst_length_g = 0,
			.wch_burst_length_b = 0,
			.mask_write_r = 0,
			.mask_write_g = 0,
			.mask_write_b = 0,
			.read_select_yp = 0,
			.read_select_yn = 0,
		},
	};

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < (sizeof(ltmAxiCtrlParam) / sizeof(ltmAxiCtrlParam[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Set_AxiCtrlParam(priv->ltm43->pipeNo, &ltmAxiCtrlParam[loopCnt]);

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRR  = %u\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRR));
		Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRG  = %u\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRG));
		Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRB  = %u\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRB));
		Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRYP = %u\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRYP));
		Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRYN = %u\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTRYN));
		Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWR  = %u\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWR));
		Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWG  = %u\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWG));
		Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWB  = %u\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.BURSTWB));
		Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKR = %u\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKR));
		Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKG = %u\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKG));
		Ddim_Print(("IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKB = %u\n", IO_LTM_P1.LTM.LAXIBSIZ.bit.WSTBMSKB));
		Ddim_Print(("IO_LTM_P1.LTM.AXIRSEL.bit.AXIRSEL1  = %u\n", IO_LTM_P1.LTM.AXIRSEL.bit.AXIRSEL1));
		Ddim_Print(("IO_LTM_P1.LTM.AXIRSEL.bit.AXIRSEL2  = %u\n", IO_LTM_P1.LTM.AXIRSEL.bit.AXIRSEL2));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRR  = %u\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRR));
		Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRG  = %u\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRG));
		Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRB  = %u\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRB));
		Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRYP = %u\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRYP));
		Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRYN = %u\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTRYN));
		Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWR  = %u\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWR));
		Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWG  = %u\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWG));
		Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWB  = %u\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.BURSTWB));
		Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKR = %u\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKR));
		Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKG = %u\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKG));
		Ddim_Print(("IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKB = %u\n", IO_LTM_P2.LTM.LAXIBSIZ.bit.WSTBMSKB));
		Ddim_Print(("IO_LTM_P2.LTM.AXIRSEL.bit.AXIRSEL1  = %u\n", IO_LTM_P2.LTM.AXIRSEL.bit.AXIRSEL1));
		Ddim_Print(("IO_LTM_P2.LTM.AXIRSEL.bit.AXIRSEL2  = %u\n", IO_LTM_P2.LTM.AXIRSEL.bit.AXIRSEL2));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_11: "
gint32 ct_im_ltm_ltm3_1_11(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	guint32						loopCnt;
	T_IM_LTM_LTM_OUTDATA_INFO	ltmOutdataInfo[] =
	{
		[0] =
		{	// max
			.addr[0] = (gpointer)0xFFFFFFFE,
			.addr[1] = (gpointer)0xFFFFFFFE,
			.addr[2] = (gpointer)0xFFFFFFFE,
			.global_width[0] = 0xFFF8,
			.global_width[1] = 0xFFF8,
			.global_width[2] = 0xFFF8,
		},
		[1] =
		{	// min
			.addr[0] = (gpointer)0,
			.addr[1] = (gpointer)0,
			.addr[2] = (gpointer)0,
			.global_width[0] = 0,
			.global_width[1] = 0,
			.global_width[2] = 0,
		},
	};

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < (sizeof(ltmOutdataInfo) / sizeof(ltmOutdataInfo[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Set_OutData_Info(priv->ltm43->pipeNo, &ltmOutdataInfo[loopCnt]);

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.LSDWADR.bit.SDWADR   = 0x%lx\n", IO_LTM_P1.LTM.LSDWADR.bit.SDWADR));
		Ddim_Print(("IO_LTM_P1.LTM.LSDWDEFR.bit.SDWDEFR = 0x%x\n",  IO_LTM_P1.LTM.LSDWDEFR.bit.SDWDEFR));
		Ddim_Print(("IO_LTM_P1.LTM.LSDWADG.bit.SDWADG   = 0x%lx\n", IO_LTM_P1.LTM.LSDWADG.bit.SDWADG));
		Ddim_Print(("IO_LTM_P1.LTM.LSDWDEFG.bit.SDWDEFG = 0x%x\n",  IO_LTM_P1.LTM.LSDWDEFG.bit.SDWDEFG));
		Ddim_Print(("IO_LTM_P1.LTM.LSDWADB.bit.SDWADB   = 0x%lx\n", IO_LTM_P1.LTM.LSDWADB.bit.SDWADB));
		Ddim_Print(("IO_LTM_P1.LTM.LSDWDEFB.bit.SDWDEFB = 0x%x\n",  IO_LTM_P1.LTM.LSDWDEFB.bit.SDWDEFB));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.LSDWADR.bit.SDWADR   = 0x%lx\n", IO_LTM_P2.LTM.LSDWADR.bit.SDWADR));
		Ddim_Print(("IO_LTM_P2.LTM.LSDWDEFR.bit.SDWDEFR = 0x%x\n",  IO_LTM_P2.LTM.LSDWDEFR.bit.SDWDEFR));
		Ddim_Print(("IO_LTM_P2.LTM.LSDWADG.bit.SDWADG   = 0x%lx\n", IO_LTM_P2.LTM.LSDWADG.bit.SDWADG));
		Ddim_Print(("IO_LTM_P2.LTM.LSDWDEFG.bit.SDWDEFG = 0x%x\n",  IO_LTM_P2.LTM.LSDWDEFG.bit.SDWDEFG));
		Ddim_Print(("IO_LTM_P2.LTM.LSDWADB.bit.SDWADB   = 0x%lx\n", IO_LTM_P2.LTM.LSDWADB.bit.SDWADB));
		Ddim_Print(("IO_LTM_P2.LTM.LSDWDEFB.bit.SDWDEFB = 0x%x\n",  IO_LTM_P2.LTM.LSDWDEFB.bit.SDWDEFB));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_14: "
gint32 ct_im_ltm_ltm3_1_14(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	guint32	loopCnt;
	T_IM_LTM_LTM_MAP_RESIZE_PITCH ltmResizePitch[] =
	{
		[0] =
		{	// max
			.hsta = 0xFFFFFF,
			.hpit = 0x7FFF,
			.vsta = 0xFFFFFF,
			.vpit = 0x7FFF,
		},
		[1] =
		{	// min
			.hsta = -0x1000000,
			.hpit = 0,
			.vsta = -0x1000000,
			.vpit = 0,
		},
	};

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < 2; loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Set_MapImage_Resize_Pitch(priv->ltm43->pipeNo, &ltmResizePitch[loopCnt]);

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.LHSTA.bit.HSTA = 0x%x\n", IO_LTM_P1.LTM.LHSTA.bit.HSTA));
		Ddim_Print(("IO_LTM_P1.LTM.LHPIT.bit.HPIT = 0x%x\n", IO_LTM_P1.LTM.LHPIT.bit.HPIT));
		Ddim_Print(("IO_LTM_P1.LTM.LVSTA.bit.VSTA = 0x%x\n", IO_LTM_P1.LTM.LVSTA.bit.VSTA));
		Ddim_Print(("IO_LTM_P1.LTM.LVPIT.bit.VPIT = 0x%x\n", IO_LTM_P1.LTM.LVPIT.bit.VPIT));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.LHSTA.bit.HSTA = 0x%x\n", IO_LTM_P2.LTM.LHSTA.bit.HSTA));
		Ddim_Print(("IO_LTM_P2.LTM.LHPIT.bit.HPIT = 0x%x\n", IO_LTM_P2.LTM.LHPIT.bit.HPIT));
		Ddim_Print(("IO_LTM_P2.LTM.LVSTA.bit.VSTA = 0x%x\n", IO_LTM_P2.LTM.LVSTA.bit.VSTA));
		Ddim_Print(("IO_LTM_P2.LTM.LVPIT.bit.VPIT = 0x%x\n", IO_LTM_P2.LTM.LVPIT.bit.VPIT));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_15: "
gint32 ct_im_ltm_ltm3_1_15(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	guint32	loopCnt;

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < 2; loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Set_FrameStop(priv->ltm43->pipeNo, loopCnt);

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.LFRSTP.bit.FRSTP = %u\n", IO_LTM_P1.LTM.LFRSTP.bit.FRSTP));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.LFRSTP.bit.FRSTP = %u\n", IO_LTM_P2.LTM.LFRSTP.bit.FRSTP));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_16: "
gint32 ct_im_ltm_ltm3_1_16(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	guint32	loopCnt;

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < 2; loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Set_ParamHold(priv->ltm43->pipeNo, loopCnt);

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.LPARMSK.bit.PARMSK = %u\n", IO_LTM_P1.LTM.LPARMSK.bit.PARMSK));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.LPARMSK.bit.PARMSK = %u\n", IO_LTM_P2.LTM.LPARMSK.bit.PARMSK));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_17: "
gint32 ct_im_ltm_ltm3_1_17(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	gboolean busyStat = FALSE;

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

#ifdef CO_DEBUG_ON_PC
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm43->pipeNo)){
		IO_LTM_P1.LTM.LTRG.bit.TRG = 3;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm43->pipeNo)){
		IO_LTM_P2.LTM.LTRG.bit.TRG = 3;
	}
#endif // CO_DEBUG_ON_PC
	Im_LTM_LTM_Get_LtmBusy(priv->ltm43->pipeNo, &busyStat);
	Ddim_Print(("busyStat = %u\n", busyStat));

#ifdef CO_DEBUG_ON_PC
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO1(priv->ltm43->pipeNo)){
		IO_LTM_P1.LTM.LTRG.bit.TRG = 2;
	}
	if(CtImLtmLtm_CHECK_TARGET_PIPE_NO2(priv->ltm43->pipeNo)){
		IO_LTM_P2.LTM.LTRG.bit.TRG = 2;
	}
#endif // CO_DEBUG_ON_PC

	busyStat = FALSE;

	Im_LTM_LTM_Get_LtmBusy(priv->ltm43->pipeNo, &busyStat);
	Ddim_Print(("busyStat = %u\n", busyStat));

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_18: "
gint32 ct_im_ltm_ltm3_1_18(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	Im_LTM_LTM_ContStart(priv->ltm43->pipeNo);

	Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
	Ddim_Print(("IO_LTM_P1.LTM.LTRG.bit.TRG = %u\n", IO_LTM_P1.LTM.LTRG.bit.TRG));
	Ddim_Print(("\n"));
	Ddim_Print(("IO_LTM_P2.LTM.LTRG.bit.TRG = %u\n", IO_LTM_P2.LTM.LTRG.bit.TRG));
	Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_19: "
gint32 ct_im_ltm_ltm3_1_19(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	guint32	loopCnt;
	T_IM_LTM_LTM_CTRL_HF_STRENGTH	ltmHfCtrl[] =
	{
		[0] =
		{	// max
			.strength = 0x1000,
		},
		[1] =
		{	// min
			.strength = 0,
		},
	};

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < (sizeof(ltmHfCtrl) / sizeof(ltmHfCtrl[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Set_High_Frequency_Strength(priv->ltm43->pipeNo, &ltmHfCtrl[loopCnt]);

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.NLVTHOF7.bit.NLVTHOF_7 = 0x%x\n", IO_LTM_P1.LTM.NLVTHOF7.bit.NLVTHOF_7));
		Ddim_Print(("IO_LTM_P1.LTM.PLVTHOF7.bit.PLVTHOF_7 = 0x%x\n", IO_LTM_P1.LTM.PLVTHOF7.bit.PLVTHOF_7));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.NLVTHOF7.bit.NLVTHOF_7 = 0x%x\n", IO_LTM_P2.LTM.NLVTHOF7.bit.NLVTHOF_7));
		Ddim_Print(("IO_LTM_P2.LTM.PLVTHOF7.bit.PLVTHOF_7 = 0x%x\n", IO_LTM_P2.LTM.PLVTHOF7.bit.PLVTHOF_7));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_20: "
gint32 ct_im_ltm_ltm3_1_20(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	guint32	loopCnt;
	T_IM_LTM_INTERNAL_PARAM	ltmInternalParam[] =
	{
		[0] =
		{	// max
			.yshadow = 0x3FFF,
			.yhighlight = 0x3FFF,
		},
		[1] =
		{	// min
			.yshadow = 0,
			.yhighlight = 0,
		},
	};

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < (sizeof(ltmInternalParam) / sizeof(ltmInternalParam[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Set_Internal_Param(priv->ltm43->pipeNo, &ltmInternalParam[loopCnt]);

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.LYSHADOW.bit.YSHADOW       = 0x%x\n", IO_LTM_P1.LTM.LYSHADOW.bit.YSHADOW));
		Ddim_Print(("IO_LTM_P1.LTM.LYHIGHLIGHT.bit.YHIGHLIGHT = 0x%x\n", IO_LTM_P1.LTM.LYHIGHLIGHT.bit.YHIGHLIGHT));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.LYSHADOW.bit.YSHADOW       = 0x%x\n", IO_LTM_P2.LTM.LYSHADOW.bit.YSHADOW));
		Ddim_Print(("IO_LTM_P2.LTM.LYHIGHLIGHT.bit.YHIGHLIGHT = 0x%x\n", IO_LTM_P2.LTM.LYHIGHLIGHT.bit.YHIGHLIGHT));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_21: "
gint32 ct_im_ltm_ltm3_1_21(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	guint32					loopCnt;
	T_IM_LTM_LTM_CTRL_BLEND	ltmCtrlBlend[] =
	{
		[0] =
		{	// max
			.ratio = 8,
			.offset =
			{
					4096,   4096,   4096,   4096,   4096,   4096,   4096,   4096
			},
			.gain   =
			{
					0x3FFF, 0x3FFF, 0x3FFF, 0x3FFF, 0x3FFF, 0x3FFF, 0x3FFF, 0x3FFF
			},
			.border =
			{
					0xFFF,  0xFFF,  0xFFF,  0xFFF,  0xFFF,  0xFFF,  0xFFF,  0xFFF
			},
			.mode = 1,
		},
		[1] =
		{	// min
			.ratio = 0,
			.offset =
			{
					0, 0, 0, 0, 0, 0, 0, 0
			},
			.gain   =
			{
					-0x4000, -0x4000, -0x4000, -0x4000, -0x4000, -0x4000, -0x4000, -0x4000
			},
			.border =
			{
					0, 0, 0, 0, 0, 0, 0, 0
			},
			.mode = 0,
		},
	};

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < (sizeof(ltmCtrlBlend) / sizeof(ltmCtrlBlend[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Ctrl_Blend(priv->ltm43->pipeNo, &ltmCtrlBlend[loopCnt]);

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.BLDYRT.bit.BLDYRT        = 0x%x\n", IO_LTM_P1.LTM.BLDYRT.bit.BLDYRT));
		Ddim_Print(("IO_LTM_P1.LTM.BLDOF.BLDOF1.bit.BLDOF_0 = 0x%x\n", IO_LTM_P1.LTM.BLDOF.BLDOF1.bit.BLDOF_0));
		Ddim_Print(("IO_LTM_P1.LTM.BLDOF.BLDOF1.bit.BLDOF_1 = 0x%x\n", IO_LTM_P1.LTM.BLDOF.BLDOF1.bit.BLDOF_1));
		Ddim_Print(("IO_LTM_P1.LTM.BLDOF.BLDOF2.bit.BLDOF_2 = 0x%x\n", IO_LTM_P1.LTM.BLDOF.BLDOF2.bit.BLDOF_2));
		Ddim_Print(("IO_LTM_P1.LTM.BLDOF.BLDOF2.bit.BLDOF_3 = 0x%x\n", IO_LTM_P1.LTM.BLDOF.BLDOF2.bit.BLDOF_3));
		Ddim_Print(("IO_LTM_P1.LTM.BLDOF.BLDOF3.bit.BLDOF_4 = 0x%x\n", IO_LTM_P1.LTM.BLDOF.BLDOF3.bit.BLDOF_4));
		Ddim_Print(("IO_LTM_P1.LTM.BLDOF.BLDOF3.bit.BLDOF_5 = 0x%x\n", IO_LTM_P1.LTM.BLDOF.BLDOF3.bit.BLDOF_5));
		Ddim_Print(("IO_LTM_P1.LTM.BLDOF.BLDOF4.bit.BLDOF_6 = 0x%x\n", IO_LTM_P1.LTM.BLDOF.BLDOF4.bit.BLDOF_6));
		Ddim_Print(("IO_LTM_P1.LTM.BLDOF.BLDOF4.bit.BLDOF_7 = 0x%x\n", IO_LTM_P1.LTM.BLDOF.BLDOF4.bit.BLDOF_7));
		Ddim_Print(("IO_LTM_P1.LTM.BLDGA.BLDGA1.bit.BLDGA_0 = 0x%x\n", IO_LTM_P1.LTM.BLDGA.BLDGA1.bit.BLDGA_0));
		Ddim_Print(("IO_LTM_P1.LTM.BLDGA.BLDGA1.bit.BLDGA_1 = 0x%x\n", IO_LTM_P1.LTM.BLDGA.BLDGA1.bit.BLDGA_1));
		Ddim_Print(("IO_LTM_P1.LTM.BLDGA.BLDGA2.bit.BLDGA_2 = 0x%x\n", IO_LTM_P1.LTM.BLDGA.BLDGA2.bit.BLDGA_2));
		Ddim_Print(("IO_LTM_P1.LTM.BLDGA.BLDGA2.bit.BLDGA_3 = 0x%x\n", IO_LTM_P1.LTM.BLDGA.BLDGA2.bit.BLDGA_3));
		Ddim_Print(("IO_LTM_P1.LTM.BLDGA.BLDGA3.bit.BLDGA_4 = 0x%x\n", IO_LTM_P1.LTM.BLDGA.BLDGA3.bit.BLDGA_4));
		Ddim_Print(("IO_LTM_P1.LTM.BLDGA.BLDGA3.bit.BLDGA_5 = 0x%x\n", IO_LTM_P1.LTM.BLDGA.BLDGA3.bit.BLDGA_5));
		Ddim_Print(("IO_LTM_P1.LTM.BLDGA.BLDGA4.bit.BLDGA_6 = 0x%x\n", IO_LTM_P1.LTM.BLDGA.BLDGA4.bit.BLDGA_6));
		Ddim_Print(("IO_LTM_P1.LTM.BLDGA.BLDGA4.bit.BLDGA_7 = 0x%x\n", IO_LTM_P1.LTM.BLDGA.BLDGA4.bit.BLDGA_7));
		Ddim_Print(("IO_LTM_P1.LTM.BLDBD.BLDBD1.bit.BLDBD_0 = 0x%x\n", IO_LTM_P1.LTM.BLDBD.BLDBD1.bit.BLDBD_0));
		Ddim_Print(("IO_LTM_P1.LTM.BLDBD.BLDBD1.bit.BLDBD_1 = 0x%x\n", IO_LTM_P1.LTM.BLDBD.BLDBD1.bit.BLDBD_1));
		Ddim_Print(("IO_LTM_P1.LTM.BLDBD.BLDBD2.bit.BLDBD_2 = 0x%x\n", IO_LTM_P1.LTM.BLDBD.BLDBD2.bit.BLDBD_2));
		Ddim_Print(("IO_LTM_P1.LTM.BLDBD.BLDBD2.bit.BLDBD_3 = 0x%x\n", IO_LTM_P1.LTM.BLDBD.BLDBD2.bit.BLDBD_3));
		Ddim_Print(("IO_LTM_P1.LTM.BLDBD.BLDBD3.bit.BLDBD_4 = 0x%x\n", IO_LTM_P1.LTM.BLDBD.BLDBD3.bit.BLDBD_4));
		Ddim_Print(("IO_LTM_P1.LTM.BLDBD.BLDBD3.bit.BLDBD_5 = 0x%x\n", IO_LTM_P1.LTM.BLDBD.BLDBD3.bit.BLDBD_5));
		Ddim_Print(("IO_LTM_P1.LTM.BLDBD.BLDBD4.bit.BLDBD_6 = 0x%x\n", IO_LTM_P1.LTM.BLDBD.BLDBD4.bit.BLDBD_6));
		Ddim_Print(("IO_LTM_P1.LTM.BLDBD.BLDBD4.bit.BLDBD_7 = 0x%x\n", IO_LTM_P1.LTM.BLDBD.BLDBD4.bit.BLDBD_7));
		Ddim_Print(("IO_LTM_P1.LTM.LTMMD.bit.LTMMD          = 0x%x\n", IO_LTM_P1.LTM.LTMMD.bit.LTMMD));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.BLDYRT.bit.BLDYRT        = 0x%x\n", IO_LTM_P2.LTM.BLDYRT.bit.BLDYRT));
		Ddim_Print(("IO_LTM_P2.LTM.BLDOF.BLDOF1.bit.BLDOF_0 = 0x%x\n", IO_LTM_P2.LTM.BLDOF.BLDOF1.bit.BLDOF_0));
		Ddim_Print(("IO_LTM_P2.LTM.BLDOF.BLDOF1.bit.BLDOF_1 = 0x%x\n", IO_LTM_P2.LTM.BLDOF.BLDOF1.bit.BLDOF_1));
		Ddim_Print(("IO_LTM_P2.LTM.BLDOF.BLDOF2.bit.BLDOF_2 = 0x%x\n", IO_LTM_P2.LTM.BLDOF.BLDOF2.bit.BLDOF_2));
		Ddim_Print(("IO_LTM_P2.LTM.BLDOF.BLDOF2.bit.BLDOF_3 = 0x%x\n", IO_LTM_P2.LTM.BLDOF.BLDOF2.bit.BLDOF_3));
		Ddim_Print(("IO_LTM_P2.LTM.BLDOF.BLDOF3.bit.BLDOF_4 = 0x%x\n", IO_LTM_P2.LTM.BLDOF.BLDOF3.bit.BLDOF_4));
		Ddim_Print(("IO_LTM_P2.LTM.BLDOF.BLDOF3.bit.BLDOF_5 = 0x%x\n", IO_LTM_P2.LTM.BLDOF.BLDOF3.bit.BLDOF_5));
		Ddim_Print(("IO_LTM_P2.LTM.BLDOF.BLDOF4.bit.BLDOF_6 = 0x%x\n", IO_LTM_P2.LTM.BLDOF.BLDOF4.bit.BLDOF_6));
		Ddim_Print(("IO_LTM_P2.LTM.BLDOF.BLDOF4.bit.BLDOF_7 = 0x%x\n", IO_LTM_P2.LTM.BLDOF.BLDOF4.bit.BLDOF_7));
		Ddim_Print(("IO_LTM_P2.LTM.BLDGA.BLDGA1.bit.BLDGA_0 = 0x%x\n", IO_LTM_P2.LTM.BLDGA.BLDGA1.bit.BLDGA_0));
		Ddim_Print(("IO_LTM_P2.LTM.BLDGA.BLDGA1.bit.BLDGA_1 = 0x%x\n", IO_LTM_P2.LTM.BLDGA.BLDGA1.bit.BLDGA_1));
		Ddim_Print(("IO_LTM_P2.LTM.BLDGA.BLDGA2.bit.BLDGA_2 = 0x%x\n", IO_LTM_P2.LTM.BLDGA.BLDGA2.bit.BLDGA_2));
		Ddim_Print(("IO_LTM_P2.LTM.BLDGA.BLDGA2.bit.BLDGA_3 = 0x%x\n", IO_LTM_P2.LTM.BLDGA.BLDGA2.bit.BLDGA_3));
		Ddim_Print(("IO_LTM_P2.LTM.BLDGA.BLDGA3.bit.BLDGA_4 = 0x%x\n", IO_LTM_P2.LTM.BLDGA.BLDGA3.bit.BLDGA_4));
		Ddim_Print(("IO_LTM_P2.LTM.BLDGA.BLDGA3.bit.BLDGA_5 = 0x%x\n", IO_LTM_P2.LTM.BLDGA.BLDGA3.bit.BLDGA_5));
		Ddim_Print(("IO_LTM_P2.LTM.BLDGA.BLDGA4.bit.BLDGA_6 = 0x%x\n", IO_LTM_P2.LTM.BLDGA.BLDGA4.bit.BLDGA_6));
		Ddim_Print(("IO_LTM_P2.LTM.BLDGA.BLDGA4.bit.BLDGA_7 = 0x%x\n", IO_LTM_P2.LTM.BLDGA.BLDGA4.bit.BLDGA_7));
		Ddim_Print(("IO_LTM_P2.LTM.BLDBD.BLDBD1.bit.BLDBD_0 = 0x%x\n", IO_LTM_P2.LTM.BLDBD.BLDBD1.bit.BLDBD_0));
		Ddim_Print(("IO_LTM_P2.LTM.BLDBD.BLDBD1.bit.BLDBD_1 = 0x%x\n", IO_LTM_P2.LTM.BLDBD.BLDBD1.bit.BLDBD_1));
		Ddim_Print(("IO_LTM_P2.LTM.BLDBD.BLDBD2.bit.BLDBD_2 = 0x%x\n", IO_LTM_P2.LTM.BLDBD.BLDBD2.bit.BLDBD_2));
		Ddim_Print(("IO_LTM_P2.LTM.BLDBD.BLDBD2.bit.BLDBD_3 = 0x%x\n", IO_LTM_P2.LTM.BLDBD.BLDBD2.bit.BLDBD_3));
		Ddim_Print(("IO_LTM_P2.LTM.BLDBD.BLDBD3.bit.BLDBD_4 = 0x%x\n", IO_LTM_P2.LTM.BLDBD.BLDBD3.bit.BLDBD_4));
		Ddim_Print(("IO_LTM_P2.LTM.BLDBD.BLDBD3.bit.BLDBD_5 = 0x%x\n", IO_LTM_P2.LTM.BLDBD.BLDBD3.bit.BLDBD_5));
		Ddim_Print(("IO_LTM_P2.LTM.BLDBD.BLDBD4.bit.BLDBD_6 = 0x%x\n", IO_LTM_P2.LTM.BLDBD.BLDBD4.bit.BLDBD_6));
		Ddim_Print(("IO_LTM_P2.LTM.BLDBD.BLDBD4.bit.BLDBD_7 = 0x%x\n", IO_LTM_P2.LTM.BLDBD.BLDBD4.bit.BLDBD_7));
		Ddim_Print(("IO_LTM_P2.LTM.LTMMD.bit.LTMMD          = 0x%x\n", IO_LTM_P2.LTM.LTMMD.bit.LTMMD));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	return D_DDIM_OK;
}

#undef CtImLtmLtm3_D_IM_LTM_FUNC_NAME
#define CtImLtmLtm3_D_IM_LTM_FUNC_NAME "ct_im_ltm_ltm3_1_22: "
gint32 ct_im_ltm_ltm3_1_22(CtImLtmLtm3 *self)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	guint32	loopCnt;
	T_IM_LTM_LTM_CTRL_CHROMA	ltmCtrlChroma[] =
	{
		[0] =
		{	// max
			.offset =
			{
					4096,  4096,  4096,  4096,  4096,  4096,  4096,  4096
			},
			.gain   =
			{
					0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF
			},
			.border =
			{
					0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF
			},
		},
		[1] =
		{	// min
			.offset =
			{
					0, 0, 0, 0, 0, 0, 0, 0
			},
			.gain   =
			{
					-0x1000, -0x1000, -0x1000, -0x1000, -0x1000, -0x1000, -0x1000, -0x1000
			},
			.border =
			{
					0, 0, 0, 0, 0, 0, 0
			},
		},
	};

	Ddim_Print(("%s\n", CtImLtmLtm3_D_IM_LTM_FUNC_NAME));

	for(loopCnt = 0; loopCnt < (sizeof(ltmCtrlChroma) / sizeof(ltmCtrlChroma[0])); loopCnt++) {
		Ddim_Print(("** %u\n", loopCnt));

		Im_LTM_LTM_Ctrl_Chroma_Correction_Strength(priv->ltm43->pipeNo, &ltmCtrlChroma[loopCnt]);

		Im_LTM_On_Pclk(D_IM_LTM_PIPE12);
		Ddim_Print(("IO_LTM_P1.LTM.CGOF.CGOF1.bit.CGOF_0 = 0x%x\n", IO_LTM_P1.LTM.CGOF.CGOF1.bit.CGOF_0));
		Ddim_Print(("IO_LTM_P1.LTM.CGOF.CGOF1.bit.CGOF_1 = 0x%x\n", IO_LTM_P1.LTM.CGOF.CGOF1.bit.CGOF_1));
		Ddim_Print(("IO_LTM_P1.LTM.CGOF.CGOF2.bit.CGOF_2 = 0x%x\n", IO_LTM_P1.LTM.CGOF.CGOF2.bit.CGOF_2));
		Ddim_Print(("IO_LTM_P1.LTM.CGOF.CGOF2.bit.CGOF_3 = 0x%x\n", IO_LTM_P1.LTM.CGOF.CGOF2.bit.CGOF_3));
		Ddim_Print(("IO_LTM_P1.LTM.CGOF.CGOF3.bit.CGOF_4 = 0x%x\n", IO_LTM_P1.LTM.CGOF.CGOF3.bit.CGOF_4));
		Ddim_Print(("IO_LTM_P1.LTM.CGOF.CGOF3.bit.CGOF_5 = 0x%x\n", IO_LTM_P1.LTM.CGOF.CGOF3.bit.CGOF_5));
		Ddim_Print(("IO_LTM_P1.LTM.CGOF.CGOF4.bit.CGOF_6 = 0x%x\n", IO_LTM_P1.LTM.CGOF.CGOF4.bit.CGOF_6));
		Ddim_Print(("IO_LTM_P1.LTM.CGOF.CGOF4.bit.CGOF_7 = 0x%x\n", IO_LTM_P1.LTM.CGOF.CGOF4.bit.CGOF_7));
		Ddim_Print(("IO_LTM_P1.LTM.CGGA.CGGA1.bit.CGGA_0 = 0x%x\n", IO_LTM_P1.LTM.CGGA.CGGA1.bit.CGGA_0));
		Ddim_Print(("IO_LTM_P1.LTM.CGGA.CGGA1.bit.CGGA_1 = 0x%x\n", IO_LTM_P1.LTM.CGGA.CGGA1.bit.CGGA_1));
		Ddim_Print(("IO_LTM_P1.LTM.CGGA.CGGA2.bit.CGGA_2 = 0x%x\n", IO_LTM_P1.LTM.CGGA.CGGA2.bit.CGGA_2));
		Ddim_Print(("IO_LTM_P1.LTM.CGGA.CGGA2.bit.CGGA_3 = 0x%x\n", IO_LTM_P1.LTM.CGGA.CGGA2.bit.CGGA_3));
		Ddim_Print(("IO_LTM_P1.LTM.CGGA.CGGA3.bit.CGGA_4 = 0x%x\n", IO_LTM_P1.LTM.CGGA.CGGA3.bit.CGGA_4));
		Ddim_Print(("IO_LTM_P1.LTM.CGGA.CGGA3.bit.CGGA_5 = 0x%x\n", IO_LTM_P1.LTM.CGGA.CGGA3.bit.CGGA_5));
		Ddim_Print(("IO_LTM_P1.LTM.CGGA.CGGA4.bit.CGGA_6 = 0x%x\n", IO_LTM_P1.LTM.CGGA.CGGA4.bit.CGGA_6));
		Ddim_Print(("IO_LTM_P1.LTM.CGGA.CGGA4.bit.CGGA_7 = 0x%x\n", IO_LTM_P1.LTM.CGGA.CGGA4.bit.CGGA_7));
		Ddim_Print(("IO_LTM_P1.LTM.CGBD.CGBD1.bit.CGBD_1 = 0x%x\n", IO_LTM_P1.LTM.CGBD.CGBD1.bit.CGBD_1));
		Ddim_Print(("IO_LTM_P1.LTM.CGBD.CGBD2.bit.CGBD_2 = 0x%x\n", IO_LTM_P1.LTM.CGBD.CGBD2.bit.CGBD_2));
		Ddim_Print(("IO_LTM_P1.LTM.CGBD.CGBD2.bit.CGBD_3 = 0x%x\n", IO_LTM_P1.LTM.CGBD.CGBD2.bit.CGBD_3));
		Ddim_Print(("IO_LTM_P1.LTM.CGBD.CGBD3.bit.CGBD_4 = 0x%x\n", IO_LTM_P1.LTM.CGBD.CGBD3.bit.CGBD_4));
		Ddim_Print(("IO_LTM_P1.LTM.CGBD.CGBD3.bit.CGBD_5 = 0x%x\n", IO_LTM_P1.LTM.CGBD.CGBD3.bit.CGBD_5));
		Ddim_Print(("IO_LTM_P1.LTM.CGBD.CGBD4.bit.CGBD_6 = 0x%x\n", IO_LTM_P1.LTM.CGBD.CGBD4.bit.CGBD_6));
		Ddim_Print(("IO_LTM_P1.LTM.CGBD.CGBD4.bit.CGBD_7 = 0x%x\n", IO_LTM_P1.LTM.CGBD.CGBD4.bit.CGBD_7));
		Ddim_Print(("\n"));
		Ddim_Print(("IO_LTM_P2.LTM.CGOF.CGOF1.bit.CGOF_0 = 0x%x\n", IO_LTM_P2.LTM.CGOF.CGOF1.bit.CGOF_0));
		Ddim_Print(("IO_LTM_P2.LTM.CGOF.CGOF1.bit.CGOF_1 = 0x%x\n", IO_LTM_P2.LTM.CGOF.CGOF1.bit.CGOF_1));
		Ddim_Print(("IO_LTM_P2.LTM.CGOF.CGOF2.bit.CGOF_2 = 0x%x\n", IO_LTM_P2.LTM.CGOF.CGOF2.bit.CGOF_2));
		Ddim_Print(("IO_LTM_P2.LTM.CGOF.CGOF2.bit.CGOF_3 = 0x%x\n", IO_LTM_P2.LTM.CGOF.CGOF2.bit.CGOF_3));
		Ddim_Print(("IO_LTM_P2.LTM.CGOF.CGOF3.bit.CGOF_4 = 0x%x\n", IO_LTM_P2.LTM.CGOF.CGOF3.bit.CGOF_4));
		Ddim_Print(("IO_LTM_P2.LTM.CGOF.CGOF3.bit.CGOF_5 = 0x%x\n", IO_LTM_P2.LTM.CGOF.CGOF3.bit.CGOF_5));
		Ddim_Print(("IO_LTM_P2.LTM.CGOF.CGOF4.bit.CGOF_6 = 0x%x\n", IO_LTM_P2.LTM.CGOF.CGOF4.bit.CGOF_6));
		Ddim_Print(("IO_LTM_P2.LTM.CGOF.CGOF4.bit.CGOF_7 = 0x%x\n", IO_LTM_P2.LTM.CGOF.CGOF4.bit.CGOF_7));
		Ddim_Print(("IO_LTM_P2.LTM.CGGA.CGGA1.bit.CGGA_0 = 0x%x\n", IO_LTM_P2.LTM.CGGA.CGGA1.bit.CGGA_0));
		Ddim_Print(("IO_LTM_P2.LTM.CGGA.CGGA1.bit.CGGA_1 = 0x%x\n", IO_LTM_P2.LTM.CGGA.CGGA1.bit.CGGA_1));
		Ddim_Print(("IO_LTM_P2.LTM.CGGA.CGGA2.bit.CGGA_2 = 0x%x\n", IO_LTM_P2.LTM.CGGA.CGGA2.bit.CGGA_2));
		Ddim_Print(("IO_LTM_P2.LTM.CGGA.CGGA2.bit.CGGA_3 = 0x%x\n", IO_LTM_P2.LTM.CGGA.CGGA2.bit.CGGA_3));
		Ddim_Print(("IO_LTM_P2.LTM.CGGA.CGGA3.bit.CGGA_4 = 0x%x\n", IO_LTM_P2.LTM.CGGA.CGGA3.bit.CGGA_4));
		Ddim_Print(("IO_LTM_P2.LTM.CGGA.CGGA3.bit.CGGA_5 = 0x%x\n", IO_LTM_P2.LTM.CGGA.CGGA3.bit.CGGA_5));
		Ddim_Print(("IO_LTM_P2.LTM.CGGA.CGGA4.bit.CGGA_6 = 0x%x\n", IO_LTM_P2.LTM.CGGA.CGGA4.bit.CGGA_6));
		Ddim_Print(("IO_LTM_P2.LTM.CGGA.CGGA4.bit.CGGA_7 = 0x%x\n", IO_LTM_P2.LTM.CGGA.CGGA4.bit.CGGA_7));
		Ddim_Print(("IO_LTM_P2.LTM.CGBD.CGBD1.bit.CGBD_1 = 0x%x\n", IO_LTM_P2.LTM.CGBD.CGBD1.bit.CGBD_1));
		Ddim_Print(("IO_LTM_P2.LTM.CGBD.CGBD2.bit.CGBD_2 = 0x%x\n", IO_LTM_P2.LTM.CGBD.CGBD2.bit.CGBD_2));
		Ddim_Print(("IO_LTM_P2.LTM.CGBD.CGBD2.bit.CGBD_3 = 0x%x\n", IO_LTM_P2.LTM.CGBD.CGBD2.bit.CGBD_3));
		Ddim_Print(("IO_LTM_P2.LTM.CGBD.CGBD3.bit.CGBD_4 = 0x%x\n", IO_LTM_P2.LTM.CGBD.CGBD3.bit.CGBD_4));
		Ddim_Print(("IO_LTM_P2.LTM.CGBD.CGBD3.bit.CGBD_5 = 0x%x\n", IO_LTM_P2.LTM.CGBD.CGBD3.bit.CGBD_5));
		Ddim_Print(("IO_LTM_P2.LTM.CGBD.CGBD4.bit.CGBD_6 = 0x%x\n", IO_LTM_P2.LTM.CGBD.CGBD4.bit.CGBD_6));
		Ddim_Print(("IO_LTM_P2.LTM.CGBD.CGBD4.bit.CGBD_7 = 0x%x\n", IO_LTM_P2.LTM.CGBD.CGBD4.bit.CGBD_7));
		Im_LTM_Off_Pclk(D_IM_LTM_PIPE12);
	}

	return D_DDIM_OK;
}

void ct_im_ltm_ltm3_set_ltm4(CtImLtmLtm3 *self,CtImLtmLtm4 *ltm4)
{
	CtImLtmLtm3Private *priv = CT_IM_LTM_LTM3_GET_PRIVATE(self);
	priv->ltm43=ltm4;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImLtmLtm3类的一个实例
 */
CtImLtmLtm3* ct_im_ltm_ltm3_new()
{
	CtImLtmLtm3 *self = g_object_new(CT_TYPE_IM_LTM_LTM_3,NULL);
	return self;
}
