/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmMap2类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#include <stdlib.h>
#include <string.h>
#include "ct_im_ltm.h"
#include "im_ltm.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif
#include "jdsltm.h"

#include "ctimltmmap1.h"
#include "ctimltmmap2.h"

G_DEFINE_TYPE(CtImLtmMap2, ct_im_ltm_map2, G_TYPE_OBJECT);

#define CT_IM_LTM_MAP_2_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_LTM_MAP_2, CtImLtmMap2Private))

struct _CtImLtmMap2Private
{
	CtImLtmMap3 *map3;
};

/*
 *DECLS
 * */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static void 	ctImLtmMapPrintRbkDirectReg( void );

static void ct_im_ltm_map2_class_init(CtImLtmMap2Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImLtmMap2Private));
}

static void ct_im_ltm_map2_init(CtImLtmMap2 *self)
{
//	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
}

/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
//	CtImLtmMap2 *self = (CtImLtmMap2*)object;
//	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_map2_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImLtmMap2 *self = (CtImLtmMap2*)object;
//	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_map2_parent_class)->finalize(object);
}

static void ctImLtmMapPrintRbkDirectReg( void )
{
	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P1.MAP.MIOCTL.bit.INSEL = 0x%x\n", IO_LTM_P1.MAP.MIOCTL.bit.INSEL ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.MAP.MIOCTL.bit.INSEL = 0x%x\n", IO_LTM_P2.MAP.MIOCTL.bit.INSEL ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
}
/*
 *PUBLIC
 * */
#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_1: "
gint32 ct_im_ltm_map2_1_1( CtImLtmMap2 *self )
{
	gint32 ercd;
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	ercd = Im_LTM_MAP_Init( priv->map3->pipeNo );

	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P1.MAP.MAPSR   = 0x%lx\n", IO_LTM_P1.MAP.MAPSR.word ));
	Ddim_Print(( "IO_LTM_P1.MAP.MSRAMEN = 0x%lx\n", IO_LTM_P1.MAP.MSRAMEN.word ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.MAP.MAPSR   = 0x%lx\n", IO_LTM_P2.MAP.MAPSR.word ));
	Ddim_Print(( "IO_LTM_P2.MAP.MSRAMEN = 0x%lx\n", IO_LTM_P2.MAP.MSRAMEN.word ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );

	return ercd;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_2: "
gint32 ct_im_ltm_map2_1_2( CtImLtmMap2 *self )
{
	guint32	loopCnt;
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	T_IM_LTM_MAP_CTRL_AXI	mapCtrlAxi[] = {
		[0] = {	// max
			.rch.cache_type = 0xF,
			.rch.protect_type = 7,
			.wch[0].cache_type = 0xF,
			.wch[0].protect_type = 7,
			.wch[1].cache_type = 0xF,
			.wch[1].protect_type = 7,
		},
		[1] = {	// min
			.rch.cache_type = 0,
			.rch.protect_type = 0,
			.wch[0].cache_type = 0,
			.wch[0].protect_type = 0,
			.wch[1].cache_type = 0,
			.wch[1].protect_type = 0,
		},
	};

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopCnt = 0; loopCnt < (sizeof(mapCtrlAxi) / sizeof(mapCtrlAxi[0])); loopCnt++ ) {
		Ddim_Print(( "** %u\n", loopCnt ));

		Im_LTM_MAP_Ctrl_Axi( priv->map3->pipeNo, &mapCtrlAxi[loopCnt] );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.MAP.MAXICTLR.bit.ARCACHE    = %u\n", IO_LTM_P1.MAP.MAXICTLR.bit.ARCACHE    ));
		Ddim_Print(( "IO_LTM_P1.MAP.MAXICTLR.bit.ARPROT     = %u\n", IO_LTM_P1.MAP.MAXICTLR.bit.ARPROT     ));
		Ddim_Print(( "IO_LTM_P1.MAP.MAXICTLW.bit.AWCACHE_YP = %u\n", IO_LTM_P1.MAP.MAXICTLW.bit.AWCACHE_YP ));
		Ddim_Print(( "IO_LTM_P1.MAP.MAXICTLW.bit.AWPROT_YP  = %u\n", IO_LTM_P1.MAP.MAXICTLW.bit.AWPROT_YP  ));
		Ddim_Print(( "IO_LTM_P1.MAP.MAXICTLW.bit.AWCACHE_YN = %u\n", IO_LTM_P1.MAP.MAXICTLW.bit.AWCACHE_YN ));
		Ddim_Print(( "IO_LTM_P1.MAP.MAXICTLW.bit.AWPROT_YN  = %u\n", IO_LTM_P1.MAP.MAXICTLW.bit.AWPROT_YN  ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.MAP.MAXICTLR.bit.ARCACHE    = %u\n", IO_LTM_P2.MAP.MAXICTLR.bit.ARCACHE    ));
		Ddim_Print(( "IO_LTM_P2.MAP.MAXICTLR.bit.ARPROT     = %u\n", IO_LTM_P2.MAP.MAXICTLR.bit.ARPROT     ));
		Ddim_Print(( "IO_LTM_P2.MAP.MAXICTLW.bit.AWCACHE_YP = %u\n", IO_LTM_P2.MAP.MAXICTLW.bit.AWCACHE_YP ));
		Ddim_Print(( "IO_LTM_P2.MAP.MAXICTLW.bit.AWPROT_YP  = %u\n", IO_LTM_P2.MAP.MAXICTLW.bit.AWPROT_YP  ));
		Ddim_Print(( "IO_LTM_P2.MAP.MAXICTLW.bit.AWCACHE_YN = %u\n", IO_LTM_P2.MAP.MAXICTLW.bit.AWCACHE_YN ));
		Ddim_Print(( "IO_LTM_P2.MAP.MAXICTLW.bit.AWPROT_YN  = %u\n", IO_LTM_P2.MAP.MAXICTLW.bit.AWPROT_YN  ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}
	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_3: "
gint32 ct_im_ltm_map2_1_3( CtImLtmMap2 *self )
{
	T_IM_LTM_MAP_AXI_RCH_STAT mapAxiReadStat;
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_DEBUG_ON_PC
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		IO_LTM_P1.MAP.MAXIRERR.bit.RRESP = 3;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		IO_LTM_P2.MAP.MAXIRERR.bit.RRESP = 3;
	}
#endif // CO_DEBUG_ON_PC
	memset( &mapAxiReadStat, '\0', sizeof(mapAxiReadStat) );
	Im_LTM_MAP_Get_AxiReadStat( priv->map3->pipeNo, &mapAxiReadStat );
	Ddim_Print(( "rch_axi_stat = %u\n", mapAxiReadStat.rch_axi_stat ));

#ifdef CO_DEBUG_ON_PC
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		IO_LTM_P1.MAP.MAXIRERR.bit.RRESP = 0;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		IO_LTM_P2.MAP.MAXIRERR.bit.RRESP = 0;
	}
#endif // CO_DEBUG_ON_PC
	memset( &mapAxiReadStat, '\0', sizeof(mapAxiReadStat) );
	Im_LTM_MAP_Get_AxiReadStat( priv->map3->pipeNo, &mapAxiReadStat );
	Ddim_Print(( "rch_axi_stat = %u\n", mapAxiReadStat.rch_axi_stat ));

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_4: "
gint32 ct_im_ltm_map2_1_4( CtImLtmMap2 *self )
{
	T_IM_LTM_MAP_AXI_WCH_STAT mapAxiWriteStat;
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_DEBUG_ON_PC
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		IO_LTM_P1.MAP.MAXIWERR.bit.WRESP_YP = 3;
		IO_LTM_P1.MAP.MAXIWERR.bit.WRESP_YN = 3;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		IO_LTM_P2.MAP.MAXIWERR.bit.WRESP_YP = 3;
		IO_LTM_P2.MAP.MAXIWERR.bit.WRESP_YN = 3;
	}
#endif // CO_DEBUG_ON_PC
	memset( &mapAxiWriteStat, '\0', sizeof(mapAxiWriteStat) );
	Im_LTM_MAP_Get_AxiWriteStat( priv->map3->pipeNo, &mapAxiWriteStat );
	Ddim_Print(( "wch_axi_stat[0] = %u\n", mapAxiWriteStat.wch_axi_stat[0] ));
	Ddim_Print(( "wch_axi_stat[1] = %u\n", mapAxiWriteStat.wch_axi_stat[1] ));

#ifdef CO_DEBUG_ON_PC
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		IO_LTM_P1.MAP.MAXIWERR.bit.WRESP_YP = 0;
		IO_LTM_P1.MAP.MAXIWERR.bit.WRESP_YN = 0;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		IO_LTM_P2.MAP.MAXIWERR.bit.WRESP_YP = 0;
		IO_LTM_P2.MAP.MAXIWERR.bit.WRESP_YN = 0;
	}
#endif // CO_DEBUG_ON_PC
	memset( &mapAxiWriteStat, '\0', sizeof(mapAxiWriteStat) );
	Im_LTM_MAP_Get_AxiWriteStat( priv->map3->pipeNo, &mapAxiWriteStat );
	Ddim_Print(( "wch_axi_stat[0] = %u\n", mapAxiWriteStat.wch_axi_stat[0] ));
	Ddim_Print(( "wch_axi_stat[1] = %u\n", mapAxiWriteStat.wch_axi_stat[1] ));

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_5: "
gint32 ct_im_ltm_map2_1_5( CtImLtmMap2 *self )
{
	T_IM_LTM_MAP_AXI_CTRL_PARAM mapAxiCtrlParam;
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTR    = 1;
		IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTWYP  = 1;
		IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTWYN  = 1;
		IO_LTM_P1.MAP.MAXIBSIZ.bit.WSTBMSKYP = 1;
		IO_LTM_P1.MAP.MAXIBSIZ.bit.WSTBMSKYN = 1;
		IO_LTM_P1.MAP.AXICHSEL.bit.AXIWSEL1  = 1;
		IO_LTM_P1.MAP.AXICHSEL.bit.AXIWSEL2  = 1;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTR    = 1;
		IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTWYP  = 1;
		IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTWYN  = 1;
		IO_LTM_P2.MAP.MAXIBSIZ.bit.WSTBMSKYP = 1;
		IO_LTM_P2.MAP.MAXIBSIZ.bit.WSTBMSKYN = 1;
		IO_LTM_P2.MAP.AXICHSEL.bit.AXIWSEL1  = 1;
		IO_LTM_P2.MAP.AXICHSEL.bit.AXIWSEL2  = 1;
	}

	memset( &mapAxiCtrlParam, '\0', sizeof(mapAxiCtrlParam) );
	Im_LTM_MAP_Get_AxiCtrlParam( priv->map3->pipeNo, &mapAxiCtrlParam );
	Ddim_Print(( "rch_burst_length    = %u\n", mapAxiCtrlParam.rch_burst_length    ));
	Ddim_Print(( "wch_burst_length_yp = %u\n", mapAxiCtrlParam.wch_burst_length_yp ));
	Ddim_Print(( "wch_burst_length_yn = %u\n", mapAxiCtrlParam.wch_burst_length_yn ));
	Ddim_Print(( "mask_write_yp       = %u\n", mapAxiCtrlParam.mask_write_yp       ));
	Ddim_Print(( "mask_write_yn       = %u\n", mapAxiCtrlParam.mask_write_yn       ));
	Ddim_Print(( "write_select_yp     = %u\n", mapAxiCtrlParam.write_select_yp     ));
	Ddim_Print(( "write_select_yn     = %u\n", mapAxiCtrlParam.write_select_yn     ));

	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTR    = 0;
		IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTWYP  = 0;
		IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTWYN  = 0;
		IO_LTM_P1.MAP.MAXIBSIZ.bit.WSTBMSKYP = 0;
		IO_LTM_P1.MAP.MAXIBSIZ.bit.WSTBMSKYN = 0;
		IO_LTM_P1.MAP.AXICHSEL.bit.AXIWSEL1  = 0;
		IO_LTM_P1.MAP.AXICHSEL.bit.AXIWSEL2  = 0;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTR    = 0;
		IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTWYP  = 0;
		IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTWYN  = 0;
		IO_LTM_P2.MAP.MAXIBSIZ.bit.WSTBMSKYP = 0;
		IO_LTM_P2.MAP.MAXIBSIZ.bit.WSTBMSKYN = 0;
		IO_LTM_P2.MAP.AXICHSEL.bit.AXIWSEL1  = 0;
		IO_LTM_P2.MAP.AXICHSEL.bit.AXIWSEL2  = 0;
	}

	memset( &mapAxiCtrlParam, '\0', sizeof(mapAxiCtrlParam) );
	Im_LTM_MAP_Get_AxiCtrlParam( priv->map3->pipeNo, &mapAxiCtrlParam );
	Ddim_Print(( "rch_burst_length    = %u\n", mapAxiCtrlParam.rch_burst_length    ));
	Ddim_Print(( "wch_burst_length_yp = %u\n", mapAxiCtrlParam.wch_burst_length_yp ));
	Ddim_Print(( "wch_burst_length_yn = %u\n", mapAxiCtrlParam.wch_burst_length_yn ));
	Ddim_Print(( "mask_write_yp       = %u\n", mapAxiCtrlParam.mask_write_yp       ));
	Ddim_Print(( "mask_write_yn       = %u\n", mapAxiCtrlParam.mask_write_yn       ));
	Ddim_Print(( "write_select_yp     = %u\n", mapAxiCtrlParam.write_select_yp     ));
	Ddim_Print(( "write_select_yn     = %u\n", mapAxiCtrlParam.write_select_yn     ));

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_6: "
gint32 ct_im_ltm_map2_1_6( CtImLtmMap2 *self )
{
	guint32	loopCnt;
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	T_IM_LTM_MAP_AXI_CTRL_PARAM	mapAxiCtrlParam[] = {
		[0] = {	// max
			.rch_burst_length = 1,
			.wch_burst_length_yp = 1,
			.wch_burst_length_yn = 1,
			.mask_write_yp = 1,
			.mask_write_yn = 1,
			.write_select_yp = 1,
			.write_select_yn = 1,
		},
		[1] = {	// min
			.rch_burst_length = 0,
			.wch_burst_length_yp = 0,
			.wch_burst_length_yn = 0,
			.mask_write_yp = 0,
			.mask_write_yn = 0,
			.write_select_yp = 0,
			.write_select_yn = 0,
		},
	};

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopCnt = 0; loopCnt < (sizeof(mapAxiCtrlParam) / sizeof(mapAxiCtrlParam[0])); loopCnt++ ) {
		Ddim_Print(( "** %u\n", loopCnt ));

		Im_LTM_MAP_Set_AxiCtrlParam( priv->map3->pipeNo, &mapAxiCtrlParam[loopCnt] );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTR    = %u\n", IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTR    ));
		Ddim_Print(( "IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTWYP  = %u\n", IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTWYP  ));
		Ddim_Print(( "IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTWYN  = %u\n", IO_LTM_P1.MAP.MAXIBSIZ.bit.BURSTWYN  ));
		Ddim_Print(( "IO_LTM_P1.MAP.MAXIBSIZ.bit.WSTBMSKYP = %u\n", IO_LTM_P1.MAP.MAXIBSIZ.bit.WSTBMSKYP ));
		Ddim_Print(( "IO_LTM_P1.MAP.MAXIBSIZ.bit.WSTBMSKYN = %u\n", IO_LTM_P1.MAP.MAXIBSIZ.bit.WSTBMSKYN ));
		Ddim_Print(( "IO_LTM_P1.MAP.AXICHSEL.bit.AXIWSEL1  = %u\n", IO_LTM_P1.MAP.AXICHSEL.bit.AXIWSEL1  ));
		Ddim_Print(( "IO_LTM_P1.MAP.AXICHSEL.bit.AXIWSEL2  = %u\n", IO_LTM_P1.MAP.AXICHSEL.bit.AXIWSEL2  ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTR    = %u\n", IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTR    ));
		Ddim_Print(( "IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTWYP  = %u\n", IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTWYP  ));
		Ddim_Print(( "IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTWYN  = %u\n", IO_LTM_P2.MAP.MAXIBSIZ.bit.BURSTWYN  ));
		Ddim_Print(( "IO_LTM_P2.MAP.MAXIBSIZ.bit.WSTBMSKYP = %u\n", IO_LTM_P2.MAP.MAXIBSIZ.bit.WSTBMSKYP ));
		Ddim_Print(( "IO_LTM_P2.MAP.MAXIBSIZ.bit.WSTBMSKYN = %u\n", IO_LTM_P2.MAP.MAXIBSIZ.bit.WSTBMSKYN ));
		Ddim_Print(( "IO_LTM_P2.MAP.AXICHSEL.bit.AXIWSEL1  = %u\n", IO_LTM_P2.MAP.AXICHSEL.bit.AXIWSEL1  ));
		Ddim_Print(( "IO_LTM_P2.MAP.AXICHSEL.bit.AXIWSEL2  = %u\n", IO_LTM_P2.MAP.AXICHSEL.bit.AXIWSEL2  ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_10: "
gint32 ct_im_ltm_map2_1_10( CtImLtmMap2 *self )
{
	guint32	loopCnt;
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	T_IM_LTM_MAP_OUTDATA_INFO	map_outdata_info[] = {
		[0] = {	// max
			.addr_yp = (gpointer)0xFFFFFFFF,
			.global_width_yp = 0xFFF8,
			.addr_yn = (gpointer)0xFFFFFFFF,
			.global_width_yn = 0xFFF8,
		},
		[1] = {	// min
			.addr_yp = (gpointer)0,
			.global_width_yp = 0,
			.addr_yn = (gpointer)0,
			.global_width_yn = 0,
		},
	};

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopCnt = 0; loopCnt < (sizeof(map_outdata_info) / sizeof(map_outdata_info[0])); loopCnt++ ) {
		Ddim_Print(( "** %u\n", loopCnt ));

		Im_LTM_MAP_Set_OutData_Info( priv->map3->pipeNo, &map_outdata_info[loopCnt] );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.MAP.MSDWADW0.bit.SDWADW0   = 0x%lx\n", IO_LTM_P1.MAP.MSDWADW0.bit.SDWADW0   ));
		Ddim_Print(( "IO_LTM_P1.MAP.MSDWDEFW0.bit.SDWDEFW0 = 0x%x\n",  IO_LTM_P1.MAP.MSDWDEFW0.bit.SDWDEFW0 ));
		Ddim_Print(( "IO_LTM_P1.MAP.MSDWADW1.bit.SDWADW1   = 0x%lx\n", IO_LTM_P1.MAP.MSDWADW1.bit.SDWADW1   ));
		Ddim_Print(( "IO_LTM_P1.MAP.MSDWDEFW1.bit.SDWDEFW1 = 0x%x\n",  IO_LTM_P1.MAP.MSDWDEFW1.bit.SDWDEFW1 ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.MAP.MSDWADW0.bit.SDWADW0   = 0x%lx\n", IO_LTM_P2.MAP.MSDWADW0.bit.SDWADW0   ));
		Ddim_Print(( "IO_LTM_P2.MAP.MSDWDEFW0.bit.SDWDEFW0 = 0x%x\n",  IO_LTM_P2.MAP.MSDWDEFW0.bit.SDWDEFW0 ));
		Ddim_Print(( "IO_LTM_P2.MAP.MSDWADW1.bit.SDWADW1   = 0x%lx\n", IO_LTM_P2.MAP.MSDWADW1.bit.SDWADW1   ));
		Ddim_Print(( "IO_LTM_P2.MAP.MSDWDEFW1.bit.SDWDEFW1 = 0x%x\n",  IO_LTM_P2.MAP.MSDWDEFW1.bit.SDWDEFW1 ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_11: "
gint32 ct_im_ltm_map2_1_11( CtImLtmMap2 *self )
{
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	Im_LTM_MAP_Ctrl_ModeRBKDirect( priv->map3->pipeNo );

	ctImLtmMapPrintRbkDirectReg();

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_12: "
gint32 ct_im_ltm_map2_1_12( CtImLtmMap2 *self )
{
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	guint32	loopCnt;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopCnt = 0; loopCnt < 2; loopCnt++ ) {
		Ddim_Print(( "** %u\n", loopCnt ));
		Im_LTM_MAP_Set_FrameStop( priv->map3->pipeNo, loopCnt );
		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.MAP.MFRSTP.bit.FRSTP = %u\n", IO_LTM_P1.MAP.MFRSTP.bit.FRSTP ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.MAP.MFRSTP.bit.FRSTP = %u\n", IO_LTM_P2.MAP.MFRSTP.bit.FRSTP ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_13: "
gint32 ct_im_ltm_map2_1_13( CtImLtmMap2 *self )
{
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	guint32	loopCnt;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopCnt = 0; loopCnt < 2; loopCnt++ ) {
		Ddim_Print(( "** %u\n", loopCnt ));
		Im_LTM_MAP_Set_ParamHold( priv->map3->pipeNo, loopCnt );
		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.MAP.MPARMSK.bit.PARMSK = %u\n", IO_LTM_P1.MAP.MPARMSK.bit.PARMSK ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.MAP.MPARMSK.bit.PARMSK = %u\n", IO_LTM_P2.MAP.MPARMSK.bit.PARMSK ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_14: "
gint32 ct_im_ltm_map2_1_14( CtImLtmMap2 *self )
{
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	gboolean busyStat = FALSE;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_DEBUG_ON_PC
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		IO_LTM_P1.MAP.MTRG.bit.TRG = 3;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		IO_LTM_P2.MAP.MTRG.bit.TRG = 3;
	}
#endif // CO_DEBUG_ON_PC
	Im_LTM_MAP_Get_MapBusy( priv->map3->pipeNo, &busyStat );
	Ddim_Print(( "busyStat = %u\n", busyStat ));

#ifdef CO_DEBUG_ON_PC
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		IO_LTM_P1.MAP.MTRG.bit.TRG = 2;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		IO_LTM_P2.MAP.MTRG.bit.TRG = 2;
	}
#endif // CO_DEBUG_ON_PC

	busyStat = FALSE;

	Im_LTM_MAP_Get_MapBusy( priv->map3->pipeNo, &busyStat );
	Ddim_Print(( "busyStat = %u\n", busyStat ));

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_15: "
gint32 ct_im_ltm_map2_1_15( CtImLtmMap2 *self )
{
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	Im_LTM_MAP_ContStart( priv->map3->pipeNo );

	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "IO_LTM_P1.MAP.MTRG.bit.TRG = %u\n", IO_LTM_P1.MAP.MTRG.bit.TRG ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.MAP.MTRG.bit.TRG = %u\n", IO_LTM_P2.MAP.MTRG.bit.TRG ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_16: "
gint32 ct_im_ltm_map2_1_16( CtImLtmMap2 *self )
{
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	guint32	loopCnt;
	T_IM_LTM_MAP_GAIN	mapWbParam[] = {
		[0] = {	// max
			.gain_r = 0x7FF,
			.gain_g = 0x7FF,
			.gain_b = 0x7FF,
			.clip_r = 0xFFF,
			.clip_g = 0xFFF,
			.clip_b = 0xFFF,
		},
		[1] = {	// min
			.gain_r = 0,
			.gain_g = 0,
			.gain_b = 0,
			.clip_r = 0,
			.clip_g = 0,
			.clip_b = 0,
		},
	};

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopCnt = 0; loopCnt < (sizeof(mapWbParam) / sizeof(mapWbParam[0])); loopCnt++ ) {
		Ddim_Print(( "** %u\n", loopCnt ));

		Im_LTM_MAP_Set_WB_Gain( priv->map3->pipeNo, &mapWbParam[loopCnt] );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.MAP.GAINR.bit.GAINR     = 0x%x\n", IO_LTM_P1.MAP.GAINR.bit.GAINR     ));
		Ddim_Print(( "IO_LTM_P1.MAP.GAING.bit.GAING     = 0x%x\n", IO_LTM_P1.MAP.GAING.bit.GAING     ));
		Ddim_Print(( "IO_LTM_P1.MAP.GAINB.bit.GAINB     = 0x%x\n", IO_LTM_P1.MAP.GAINB.bit.GAINB     ));
		Ddim_Print(( "IO_LTM_P1.MAP.GAINCPR.bit.GAINCPR = 0x%x\n", IO_LTM_P1.MAP.GAINCPR.bit.GAINCPR ));
		Ddim_Print(( "IO_LTM_P1.MAP.GAINCPG.bit.GAINCPG = 0x%x\n", IO_LTM_P1.MAP.GAINCPG.bit.GAINCPG ));
		Ddim_Print(( "IO_LTM_P1.MAP.GAINCPB.bit.GAINCPB = 0x%x\n", IO_LTM_P1.MAP.GAINCPB.bit.GAINCPB ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.MAP.GAINR.bit.GAINR     = 0x%x\n", IO_LTM_P2.MAP.GAINR.bit.GAINR     ));
		Ddim_Print(( "IO_LTM_P2.MAP.GAING.bit.GAING     = 0x%x\n", IO_LTM_P2.MAP.GAING.bit.GAING     ));
		Ddim_Print(( "IO_LTM_P2.MAP.GAINB.bit.GAINB     = 0x%x\n", IO_LTM_P2.MAP.GAINB.bit.GAINB     ));
		Ddim_Print(( "IO_LTM_P2.MAP.GAINCPR.bit.GAINCPR = 0x%x\n", IO_LTM_P2.MAP.GAINCPR.bit.GAINCPR ));
		Ddim_Print(( "IO_LTM_P2.MAP.GAINCPG.bit.GAINCPG = 0x%x\n", IO_LTM_P2.MAP.GAINCPG.bit.GAINCPG ));
		Ddim_Print(( "IO_LTM_P2.MAP.GAINCPB.bit.GAINCPB = 0x%x\n", IO_LTM_P2.MAP.GAINCPB.bit.GAINCPB ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_17: "
gint32 ct_im_ltm_map2_1_17( CtImLtmMap2 *self )
{
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	guint32	loopCnt;
	T_IM_LTM_MAP_CTRL_GENERATION_MODE	mapModeCtrl[] = {
		[0] = {	// max
			.mode0 = 1,
			.coef0 = 0xFFF,
			.mode1 = 1,
			.coef1 = 0xFFF,
			.mode2 = 1,
			.coef2 = 0xFFF,
		},
		[1] = {	// min
			.mode0 = 0,
			.coef0 = 0,
			.mode1 = 0,
			.coef1 = 0,
			.mode2 = 0,
			.coef2 = 0,
		},
	};

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopCnt = 0; loopCnt < (sizeof(mapModeCtrl) / sizeof(mapModeCtrl[0])); loopCnt++ ) {
		Ddim_Print(( "** %u\n", loopCnt ));

		Im_LTM_MAP_Ctrl_Generation_Mode( priv->map3->pipeNo, &mapModeCtrl[loopCnt] );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.MAP.PEPS0M.bit.PEPS0M     = 0x%x\n", IO_LTM_P1.MAP.PEPS0M.bit.PEPS0M     ));
		Ddim_Print(( "IO_LTM_P1.MAP.PEPS0OF.bit.PEPS0OF_3 = 0x%x\n", IO_LTM_P1.MAP.PEPS0OF.bit.PEPS0OF_3 ));
		Ddim_Print(( "IO_LTM_P1.MAP.PEPS1M.bit.PEPS1M     = 0x%x\n", IO_LTM_P1.MAP.PEPS1M.bit.PEPS1M     ));
		Ddim_Print(( "IO_LTM_P1.MAP.PEPS1OF.bit.PEPS1OF_3 = 0x%x\n", IO_LTM_P1.MAP.PEPS1OF.bit.PEPS1OF_3 ));
		Ddim_Print(( "IO_LTM_P1.MAP.PEPS2M.bit.PEPS2M     = 0x%x\n", IO_LTM_P1.MAP.PEPS2M.bit.PEPS2M     ));
		Ddim_Print(( "IO_LTM_P1.MAP.PEPS2OF.bit.PEPS2OF_3 = 0x%x\n", IO_LTM_P1.MAP.PEPS2OF.bit.PEPS2OF_3 ));
		Ddim_Print(( "IO_LTM_P1.MAP.NEPS0M.bit.NEPS0M     = 0x%x\n", IO_LTM_P1.MAP.NEPS0M.bit.NEPS0M     ));
		Ddim_Print(( "IO_LTM_P1.MAP.NEPS0OF.bit.NEPS0OF_3 = 0x%x\n", IO_LTM_P1.MAP.NEPS0OF.bit.NEPS0OF_3 ));
		Ddim_Print(( "IO_LTM_P1.MAP.NEPS1M.bit.NEPS1M     = 0x%x\n", IO_LTM_P1.MAP.NEPS1M.bit.NEPS1M     ));
		Ddim_Print(( "IO_LTM_P1.MAP.NEPS1OF.bit.NEPS1OF_3 = 0x%x\n", IO_LTM_P1.MAP.NEPS1OF.bit.NEPS1OF_3 ));
		Ddim_Print(( "IO_LTM_P1.MAP.NEPS2M.bit.NEPS2M     = 0x%x\n", IO_LTM_P1.MAP.NEPS2M.bit.NEPS2M     ));
		Ddim_Print(( "IO_LTM_P1.MAP.NEPS2OF.bit.NEPS2OF_3 = 0x%x\n", IO_LTM_P1.MAP.NEPS2OF.bit.NEPS2OF_3 ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.MAP.PEPS0M.bit.PEPS0M     = 0x%x\n", IO_LTM_P2.MAP.PEPS0M.bit.PEPS0M     ));
		Ddim_Print(( "IO_LTM_P2.MAP.PEPS0OF.bit.PEPS0OF_3 = 0x%x\n", IO_LTM_P2.MAP.PEPS0OF.bit.PEPS0OF_3 ));
		Ddim_Print(( "IO_LTM_P2.MAP.PEPS1M.bit.PEPS1M     = 0x%x\n", IO_LTM_P2.MAP.PEPS1M.bit.PEPS1M     ));
		Ddim_Print(( "IO_LTM_P2.MAP.PEPS1OF.bit.PEPS1OF_3 = 0x%x\n", IO_LTM_P2.MAP.PEPS1OF.bit.PEPS1OF_3 ));
		Ddim_Print(( "IO_LTM_P2.MAP.PEPS2M.bit.PEPS2M     = 0x%x\n", IO_LTM_P2.MAP.PEPS2M.bit.PEPS2M     ));
		Ddim_Print(( "IO_LTM_P2.MAP.PEPS2OF.bit.PEPS2OF_3 = 0x%x\n", IO_LTM_P2.MAP.PEPS2OF.bit.PEPS2OF_3 ));
		Ddim_Print(( "IO_LTM_P2.MAP.NEPS0M.bit.NEPS0M     = 0x%x\n", IO_LTM_P2.MAP.NEPS0M.bit.NEPS0M     ));
		Ddim_Print(( "IO_LTM_P2.MAP.NEPS0OF.bit.NEPS0OF_3 = 0x%x\n", IO_LTM_P2.MAP.NEPS0OF.bit.NEPS0OF_3 ));
		Ddim_Print(( "IO_LTM_P2.MAP.NEPS1M.bit.NEPS1M     = 0x%x\n", IO_LTM_P2.MAP.NEPS1M.bit.NEPS1M     ));
		Ddim_Print(( "IO_LTM_P2.MAP.NEPS1OF.bit.NEPS1OF_3 = 0x%x\n", IO_LTM_P2.MAP.NEPS1OF.bit.NEPS1OF_3 ));
		Ddim_Print(( "IO_LTM_P2.MAP.NEPS2M.bit.NEPS2M     = 0x%x\n", IO_LTM_P2.MAP.NEPS2M.bit.NEPS2M     ));
		Ddim_Print(( "IO_LTM_P2.MAP.NEPS2OF.bit.NEPS2OF_3 = 0x%x\n", IO_LTM_P2.MAP.NEPS2OF.bit.NEPS2OF_3 ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_18: "
gint32 ct_im_ltm_map2_1_18( CtImLtmMap2 *self )
{
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	T_IM_LTM_INTERNAL_PARAM mapInternalParam;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_DEBUG_ON_PC
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		IO_LTM_P1.MAP.YSHADOW.bit.YSHADOW = 0x3FFF;
		IO_LTM_P1.MAP.YHIGHLIGHT.bit.YHIGHLIGHT = 0x3FFF;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		IO_LTM_P2.MAP.YSHADOW.bit.YSHADOW = 0x3FFF;
		IO_LTM_P2.MAP.YHIGHLIGHT.bit.YHIGHLIGHT = 0x3FFF;
	}
#endif // CO_DEBUG_ON_PC
	memset( &mapInternalParam, '\0', sizeof(mapInternalParam) );
	Im_LTM_MAP_Get_Internal_Param( priv->map3->pipeNo, &mapInternalParam );
	Ddim_Print(( "yshadow    = 0x%x\n", mapInternalParam.yshadow ));
	Ddim_Print(( "yhighlight = 0x%x\n", mapInternalParam.yhighlight ));

#ifdef CO_DEBUG_ON_PC
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		IO_LTM_P1.MAP.YSHADOW.bit.YSHADOW = 0;
		IO_LTM_P1.MAP.YHIGHLIGHT.bit.YHIGHLIGHT = 0;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		IO_LTM_P2.MAP.YSHADOW.bit.YSHADOW = 0;
		IO_LTM_P2.MAP.YHIGHLIGHT.bit.YHIGHLIGHT = 0;
	}
#endif // CO_DEBUG_ON_PC
	memset( &mapInternalParam, '\0', sizeof(mapInternalParam) );
	Im_LTM_MAP_Get_Internal_Param( priv->map3->pipeNo, &mapInternalParam );
	Ddim_Print(( "yshadow    = 0x%x\n", mapInternalParam.yshadow ));
	Ddim_Print(( "yhighlight = 0x%x\n", mapInternalParam.yhighlight ));

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_19: "
gint32 ct_im_ltm_map2_1_19( CtImLtmMap2 *self )
{
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	guint32	loopCnt;
	T_IM_LTM_CTRL_YLOG	mapYlogCtrl[] = {
		[0] = {	// max
			.use_tbl = 1,
			.end_point0_tbl0 = 0x3FFF,
			.end_point0_tbl1 = 0x3FFF,
			.end_point1_tbl0 = 0x3FFF,
			.end_point1_tbl1 = 0x3FFF,
		},
		[1] = {	// min
			.use_tbl = 0,
			.end_point0_tbl0 = 0,
			.end_point0_tbl1 = 0,
			.end_point1_tbl0 = 0,
			.end_point1_tbl1 = 0,
		},
	};

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

	for( loopCnt = 0; loopCnt < (sizeof(mapYlogCtrl) / sizeof(mapYlogCtrl[0])); loopCnt++ ) {
		Ddim_Print(( "** %u\n", loopCnt ));

		Im_LTM_MAP_Ctrl_Ylog_Tbl( priv->map3->pipeNo, &mapYlogCtrl[loopCnt] );

		Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
		Ddim_Print(( "IO_LTM_P1.MAP.MYLCTL.bit.YLOGSL      = 0x%x\n", IO_LTM_P1.MAP.MYLCTL.bit.YLOGSL      ));
		Ddim_Print(( "IO_LTM_P1.MAP.MYLOG0EP0.bit.YLOG0EP0 = 0x%x\n", IO_LTM_P1.MAP.MYLOG0EP0.bit.YLOG0EP0 ));
		Ddim_Print(( "IO_LTM_P1.MAP.MYLOG0EP1.bit.YLOG0EP1 = 0x%x\n", IO_LTM_P1.MAP.MYLOG0EP1.bit.YLOG0EP1 ));
		Ddim_Print(( "IO_LTM_P1.MAP.MYLOG1EP0.bit.YLOG1EP0 = 0x%x\n", IO_LTM_P1.MAP.MYLOG1EP0.bit.YLOG1EP0 ));
		Ddim_Print(( "IO_LTM_P1.MAP.MYLOG1EP1.bit.YLOG1EP1 = 0x%x\n", IO_LTM_P1.MAP.MYLOG1EP1.bit.YLOG1EP1 ));
		Ddim_Print(( "\n" ));
		Ddim_Print(( "IO_LTM_P2.MAP.MYLCTL.bit.YLOGSL      = 0x%x\n", IO_LTM_P2.MAP.MYLCTL.bit.YLOGSL      ));
		Ddim_Print(( "IO_LTM_P2.MAP.MYLOG0EP0.bit.YLOG0EP0 = 0x%x\n", IO_LTM_P2.MAP.MYLOG0EP0.bit.YLOG0EP0 ));
		Ddim_Print(( "IO_LTM_P2.MAP.MYLOG0EP1.bit.YLOG0EP1 = 0x%x\n", IO_LTM_P2.MAP.MYLOG0EP1.bit.YLOG0EP1 ));
		Ddim_Print(( "IO_LTM_P2.MAP.MYLOG1EP0.bit.YLOG1EP0 = 0x%x\n", IO_LTM_P2.MAP.MYLOG1EP0.bit.YLOG1EP0 ));
		Ddim_Print(( "IO_LTM_P2.MAP.MYLOG1EP1.bit.YLOG1EP1 = 0x%x\n", IO_LTM_P2.MAP.MYLOG1EP1.bit.YLOG1EP1 ));
		Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
	}

	return D_DDIM_OK;
}

#undef D_IM_LTM_FUNC_NAME
#define D_IM_LTM_FUNC_NAME "ct_im_ltm_map2_1_20: "
gint32 ct_im_ltm_map2_1_20( CtImLtmMap2 *self )
{
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	guchar actTblNo;

	Ddim_Print(( "%s\n", D_IM_LTM_FUNC_NAME ));

#ifdef CO_DEBUG_ON_PC
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		IO_LTM_P1.MAP.MYLCTL.bit.YLOGSTA = 1;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		IO_LTM_P2.MAP.MYLCTL.bit.YLOGSTA = 1;
	}
#endif // CO_DEBUG_ON_PC
	Im_LTM_MAP_Get_Active_Ylog_Tbl_No( priv->map3->pipeNo, &actTblNo );
	Ddim_Print(( "actTblNo = %u\n", actTblNo ));

#ifdef CO_DEBUG_ON_PC
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1( priv->map3->pipeNo ) ){
		IO_LTM_P1.MAP.MYLCTL.bit.YLOGSTA = 0;
	}
	if( CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2( priv->map3->pipeNo ) ){
		IO_LTM_P2.MAP.MYLCTL.bit.YLOGSTA = 0;
	}
#endif // CO_DEBUG_ON_PC
	Im_LTM_MAP_Get_Active_Ylog_Tbl_No( priv->map3->pipeNo, &actTblNo );
	Ddim_Print(( "actTblNo = %u\n", actTblNo ));

	return D_DDIM_OK;
}

void ct_im_ltm_map2_set_map3(CtImLtmMap2* self, CtImLtmMap3* map3)
{
	CtImLtmMap2Private *priv = CT_IM_LTM_MAP_2_GET_PRIVATE(self);
	priv->map3 = map3;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImLtmMap2类的一个实例
 */
CtImLtmMap2* ct_im_ltm_map2_new()
{
	CtImLtmMap2 *self = g_object_new(CT_TYPE_IM_LTM_MAP_2,NULL);
	return self;
}
