/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImLtmRbk类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "ct_im_ltm.h"

#include "im_ltm.h"
#include "im_pro.h"
#include "im_pro_common.h"

#include "driver_common.h"
#include "ddim_user_custom.h"
//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
//#endif

#include "jdsltm.h"

#include <stdlib.h>
#include <string.h>

#include "ctimrbkrun1.h"
#include "ctimrbkrun2.h"
#include "ctimrbkrun3.h"
#include "ctimltmrbk.h"


G_DEFINE_TYPE(CtImLtmRbk, ct_im_ltm_rbk, G_TYPE_OBJECT);
#define CT_IM_LTM_RBK_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_LTM_RBK, CtImLtmRbkPrivate))

/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
#ifdef CO_MSG_PRINT_ON
#define CtImLtmRbk_D_IM_LTM_RESULT(statement)		result = statement
#else
#define CtImLtmRbk_D_IM_LTM_RESULT
#endif

struct _CtImLtmRbkPrivate
{
	CtImRbkRun1 *runself1;
	CtImRbkRun2 *runself2;
	CtImRbkRun3 *runself3;
};

static volatile BOOL S_GCT_IM_LTM_RBK_SRO_VD_FLG = FALSE;

/*
*DECLS
*/
static void 		dispose_od(GObject *object);
static void 		finalize_od(GObject *object);
static void 		ctImLtmRbkSroPrchIntHandler(T_CALLBACK_ID* cbId, gulong result, gulong userParam);
static void 		ctImLtmRbkSroVdIntHandler(T_CALLBACK_ID* cbId, gulong result, gulong userParam);
static void 		ctImLtmRbkWaitVdSro(void);
static gint32 		ctImLtmRbkRun1(CtImLtmRbk *self, const guint32 ctNo2nd);
static gint32 		ctImLtmRbkRun2(CtImLtmRbk *self, const guint32 ctNo2nd);
static gint32 		ctImLtmRbkRun3(CtImLtmRbk *self, const guint32 ctNo2nd);

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef IM_LTM_STATUS_PRINT
extern void Im_LTM_RBK_Print_Status( void );
#endif
/*
*IMPL
*/

static void ct_im_ltm_rbk_class_init(CtImLtmRbkClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImLtmRbkPrivate));
}

static void ct_im_ltm_rbk_init(CtImLtmRbk *self)
{
	CtImLtmRbkPrivate *priv = CT_IM_LTM_RBK_GET_PRIVATE(self);
	priv->runself1 = ct_im_rbk_run1_new();
	priv->runself2 = ct_im_rbk_run2_new();
	priv->runself3 = ct_im_rbk_run3_new();
}

static void dispose_od(GObject *object)
{
//	CtImLtmRbk *self = (CtImLtmRbk*)object;
//	CtImLtmRbkPrivate *priv = CT_IM_LTM_RBK_GET_PRIVATE(self);
}

static void finalize_od(GObject *object)
{
	CtImLtmRbk *self = (CtImLtmRbk*)object;
	CtImLtmRbkPrivate *priv = CT_IM_LTM_RBK_GET_PRIVATE(self);
	if(priv->runself1!=NULL){
		g_object_unref(priv->runself1);
		priv->runself1=NULL;
	}
	if(priv->runself2!=NULL){
		g_object_unref(priv->runself2);
		priv->runself2=NULL;
	}
	if(priv->runself3!=NULL){
		g_object_unref(priv->runself3);
		priv->runself3=NULL;
	}
	G_OBJECT_CLASS(ct_im_ltm_rbk_parent_class)->finalize(object);
}

static void ctImLtmRbkSroPrchIntHandler( T_CALLBACK_ID* cbId, gulong result, gulong userParam )
{
	Ddim_Print(( "PRch Int %u, %u, %u %lx, %lx\n", cbId->unit_no, cbId->block_type, cbId->channel,
			result, userParam ));
}

static void ctImLtmRbkSroVdIntHandler( T_CALLBACK_ID* cbId, gulong result, gulong userParam )
{
	Ddim_Print(( "VD Int %u, %u, %u %lx, %lx\n", cbId->unit_no, cbId->block_type, cbId->channel,
			result, userParam ));
	S_GCT_IM_LTM_RBK_SRO_VD_FLG = TRUE;
}

static void ctImLtmRbkWaitVdSro( void )
{
	guint32 loopcnt;
#ifdef CO_DEBUG_ON_PC
	T_CALLBACK_ID cbId = {
		.unit_no	= 0,
		.block_type	= 0,
		.channel	= 0,
	};
#endif

	for( loopcnt = 0; S_GCT_IM_LTM_RBK_SRO_VD_FLG == FALSE; loopcnt++ ) {
		if( loopcnt >= 10 ) {
			Ddim_Print(( "SRO wait end timeout.\n" ));
			break;
		}

		DDIM_User_Dly_Tsk( 1 );
#ifdef CO_DEBUG_ON_PC
		ctImLtmRbkSroVdIntHandler( &cbId, 0, 0 );
#endif
	}

	S_GCT_IM_LTM_RBK_SRO_VD_FLG = FALSE;
}

static gint32 ctImLtmRbkRun1(CtImLtmRbk *self, const guint32 ctNo2nd)
{
	CtImLtmRbkPrivate *priv = CT_IM_LTM_RBK_GET_PRIVATE(self);

	switch( ctNo2nd ) {
		// Test-1-1-1
		case 1:
			return ct_im_rbk_run1_rbk_1_1(priv->runself1);

		// Test-1-1-2
		case 2:
			return ct_im_rbk_run1_rbk_1_2(priv->runself1);

		// Test-1-1-3
		case 3:
			return ct_im_rbk_run1_rbk_1_3(priv->runself1);

		// Test-1-1-4
		case 4:
			return ct_im_rbk_run1_rbk_1_4(priv->runself1);

		// Test-1-1-5
		case 5:
			return ct_im_rbk_run1_rbk_1_5(priv->runself1);

		// Test-1-1-6
		case 6:
			return ct_im_rbk_run1_rbk_1_6(priv->runself1);

		// Test-1-1-7
		case 7:
			return ct_im_rbk_run1_rbk_1_7(priv->runself1);

		// Test-1-1-8
		case 8:
			return ct_im_rbk_run1_rbk_1_8(priv->runself1);

		// Test-1-1-9
		case 9:
			return ct_im_rbk_run1_rbk_1_9(priv->runself1);

		// Test-1-1-10
		case 10:
			return ct_im_rbk_run1_rbk_1_10(priv->runself1);

		// Test-1-1-11
		case 11:
			return ct_im_rbk_run1_rbk_1_11(priv->runself1);

		// Test-1-1-12
		case 12:
			return ct_im_rbk_run1_rbk_1_12(priv->runself1);

		// Test-1-1-13
		case 13:
			return ct_im_rbk_run1_rbk_1_13(priv->runself1);

		// Test-1-1-14
		case 14:
			return ct_im_rbk_run1_rbk_1_14(priv->runself1);

		// Test-1-1-15
		case 15:
			return ct_im_rbk_run1_rbk_1_15(priv->runself1);

		// Test-1-1-16
		case 16:
			return ct_im_rbk_run1_rbk_1_16(priv->runself1);

		// Test-1-1-17
		case 17:
			return ct_im_rbk_run1_rbk_1_17(priv->runself1);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;

}

static gint32 ctImLtmRbkRun2(CtImLtmRbk *self, const guint32 ctNo2nd)
{
	CtImLtmRbkPrivate *priv = CT_IM_LTM_RBK_GET_PRIVATE(self);

	switch( ctNo2nd ) {
		// Test-1-2-1
		case 1:
			return ct_im_rbk_run2_rbk_2_1(priv->runself2);

		// Test-1-2-2
		case 2:
			return ct_im_rbk_run2_rbk_2_2(priv->runself2);

		// Test-1-2-3
		case 3:
			return ct_im_rbk_run2_rbk_2_3(priv->runself2);

		// Test-1-2-4
		case 4:
			return ct_im_rbk_run2_rbk_2_4(priv->runself2);

		// Test-1-2-5
		case 5:
			return ct_im_rbk_run2_rbk_2_5(priv->runself2);

		// Test-1-2-6
		case 6:
			return ct_im_rbk_run2_rbk_2_6(priv->runself2);

		// Test-1-2-7
		case 7:
			return ct_im_rbk_run2_rbk_2_7(priv->runself2);

		// Test-1-2-8
		case 8:
			return ct_im_rbk_run2_rbk_2_8(priv->runself2);

		// Test-1-2-9
		case 9:
			return ct_im_rbk_run2_rbk_2_9(priv->runself2);

		// Test-1-2-10
		case 10:
			return ct_im_rbk_run2_rbk_2_10(priv->runself2);

		// Test-1-2-11
		case 11:
			return ct_im_rbk_run2_rbk_2_11(priv->runself2);

		// Test-1-2-12
		case 12:
			return ct_im_rbk_run2_rbk_2_12(priv->runself2);

		// Test-1-2-13
		case 13:
			return ct_im_rbk_run2_rbk_2_13(priv->runself2);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

static gint32 ctImLtmRbkRun3(CtImLtmRbk *self, const guint32 ctNo2nd)
{
	CtImLtmRbkPrivate *priv = CT_IM_LTM_RBK_GET_PRIVATE(self);

	switch( ctNo2nd ) {
		// Test-1-3-1
		case 1:
			return ct_im_rbk_run3_3_1(priv->runself3);

		// Test-1-3-2
		case 2:
			return ct_im_rbk_run3_3_2(priv->runself3);

		// Test-1-3-3
		case 3:
			return ct_im_rbk_run3_3_3(priv->runself3);

		// Test-1-3-4
		case 4:
			return ct_im_rbk_run3_3_4(priv->runself3);

		// Test-1-3-5
		case 5:
			return ct_im_rbk_run3_3_5(priv->runself3);

		// Test-1-3-6
		case 6:
			return ct_im_rbk_run3_3_6(priv->runself3);

		// Test-1-3-7
		case 7:
			return ct_im_rbk_run3_3_7(priv->runself3);

		// Test-1-3-8
		case 8:
			return ct_im_rbk_run3_3_8(priv->runself3);

		// Test-1-3-9
		case 9:
			return ct_im_rbk_run3_3_9(priv->runself3);

		// Test-1-3-10
		case 10:
			return ct_im_rbk_run3_3_10(priv->runself3);

		// Test-1-3-11
		case 11:
			return ct_im_rbk_run2_rbk_3_11(priv->runself2);

		// Test-1-3-12
		case 12:
			return ct_im_rbk_run2_rbk_3_12(priv->runself2);

		// Test-1-3-13
		case 13:
			return ct_im_rbk_run2_rbk_3_13(priv->runself2);

		// Test-1-3-14
		case 14:
			return ct_im_rbk_run2_rbk_3_14(priv->runself2);

		// Test-1-3-15
		case 15:
			return ct_im_rbk_run2_rbk_3_15(priv->runself2);

		// Test-1-3-16
		case 16:
			return ct_im_rbk_run2_rbk_3_16(priv->runself2);

		// Test-1-3-18
		case 18:
			return ct_im_rbk_run3_3_18(priv->runself3);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;

}
/*
*PUBLIC
*/
void ct_im_ltm_rbk_print_ctrl_common_reg( void )
{
	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P1.RBK.RLINTLV.bit.LINTLV   = 0x%x\n", IO_LTM_P1.RBK.RLINTLV.bit.LINTLV   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTW  = 0x%x\n", IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTW  ));
	Ddim_Print(( "IO_LTM_P1.RBK.RAXIBSIZ.bit.WSTBMSK = 0x%x\n", IO_LTM_P1.RBK.RAXIBSIZ.bit.WSTBMSK ));
	Ddim_Print(( "IO_LTM_P1.RBK.RIOCTL.bit.OUTSEL    = 0x%x\n", IO_LTM_P1.RBK.RIOCTL.bit.OUTSEL    ));
	Ddim_Print(( "IO_LTM_P1.RBK.RIOCTL.bit.W0DTYP    = 0x%x\n", IO_LTM_P1.RBK.RIOCTL.bit.W0DTYP    ));
	Ddim_Print(( "IO_LTM_P1.RBK.RDCMD.bit.RDCEN      = 0x%x\n", IO_LTM_P1.RBK.RDCMD.bit.RDCEN      ));
	Ddim_Print(( "IO_LTM_P1.RBK.RDCMD.bit.RDCMD      = 0x%x\n", IO_LTM_P1.RBK.RDCMD.bit.RDCMD      ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.RBK.RLINTLV.bit.LINTLV   = 0x%x\n", IO_LTM_P2.RBK.RLINTLV.bit.LINTLV   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTW  = 0x%x\n", IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTW  ));
	Ddim_Print(( "IO_LTM_P2.RBK.RAXIBSIZ.bit.WSTBMSK = 0x%x\n", IO_LTM_P2.RBK.RAXIBSIZ.bit.WSTBMSK ));
	Ddim_Print(( "IO_LTM_P2.RBK.RIOCTL.bit.OUTSEL    = 0x%x\n", IO_LTM_P2.RBK.RIOCTL.bit.OUTSEL    ));
	Ddim_Print(( "IO_LTM_P2.RBK.RIOCTL.bit.W0DTYP    = 0x%x\n", IO_LTM_P2.RBK.RIOCTL.bit.W0DTYP    ));
	Ddim_Print(( "IO_LTM_P2.RBK.RDCMD.bit.RDCEN      = 0x%x\n", IO_LTM_P2.RBK.RDCMD.bit.RDCEN      ));
	Ddim_Print(( "IO_LTM_P2.RBK.RDCMD.bit.RDCMD      = 0x%x\n", IO_LTM_P2.RBK.RDCMD.bit.RDCMD      ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
}

void ct_im_ltm_rbk_print_ctrl_sdram_input_reg( void )
{
	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRR = 0x%x\n", IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRR ));
	Ddim_Print(( "IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRG = 0x%x\n", IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRG ));
	Ddim_Print(( "IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRB = 0x%x\n", IO_LTM_P1.RBK.RAXIBSIZ.bit.BURSTRB ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDRDEF.bit.SDRDEF   = 0x%x\n", IO_LTM_P1.RBK.RSDRDEF.bit.SDRDEF   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDRHSZ.bit.SDRHSZ   = 0x%x\n", IO_LTM_P1.RBK.RSDRHSZ.bit.SDRHSZ   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDRVSZ.bit.SDRVSZ   = 0x%x\n", IO_LTM_P1.RBK.RSDRVSZ.bit.SDRVSZ   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RIOCTL.bit.INSEL     = 0x%x\n", IO_LTM_P1.RBK.RIOCTL.bit.INSEL     ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSFEN.bit.RSFEN      = 0x%x\n", IO_LTM_P1.RBK.RSFEN.bit.RSFEN      ));
	Ddim_Print(( "IO_LTM_P1.RBK.HVEN.bit.HVEN        = 0x%x\n", IO_LTM_P1.RBK.HVEN.bit.HVEN        ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRR = 0x%x\n", IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRR ));
	Ddim_Print(( "IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRG = 0x%x\n", IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRG ));
	Ddim_Print(( "IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRB = 0x%x\n", IO_LTM_P2.RBK.RAXIBSIZ.bit.BURSTRB ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDRDEF.bit.SDRDEF   = 0x%x\n", IO_LTM_P2.RBK.RSDRDEF.bit.SDRDEF   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDRHSZ.bit.SDRHSZ   = 0x%x\n", IO_LTM_P2.RBK.RSDRHSZ.bit.SDRHSZ   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDRVSZ.bit.SDRVSZ   = 0x%x\n", IO_LTM_P2.RBK.RSDRVSZ.bit.SDRVSZ   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RIOCTL.bit.INSEL     = 0x%x\n", IO_LTM_P2.RBK.RIOCTL.bit.INSEL     ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSFEN.bit.RSFEN      = 0x%x\n", IO_LTM_P2.RBK.RSFEN.bit.RSFEN      ));
	Ddim_Print(( "IO_LTM_P2.RBK.HVEN.bit.HVEN        = 0x%x\n", IO_LTM_P2.RBK.HVEN.bit.HVEN        ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
}

void ct_im_ltm_rbk_print_sro_direct_reg( void )
{
	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P1.RBK.RIOCTL.bit.INSEL    = 0x%x\n", IO_LTM_P1.RBK.RIOCTL.bit.INSEL    ));
	Ddim_Print(( "IO_LTM_P1.RBK.RIOCTL.bit.BAYER0   = 0x%x\n", IO_LTM_P1.RBK.RIOCTL.bit.BAYER0   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RIOCTL.bit.BAYER1   = 0x%x\n", IO_LTM_P1.RBK.RIOCTL.bit.BAYER1   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RIOCTL.bit.SROMD    = 0x%x\n", IO_LTM_P1.RBK.RIOCTL.bit.SROMD    ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSFEN.bit.RSFEN0    = 0x%x\n", IO_LTM_P1.RBK.RSFEN.bit.RSFEN0    ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSFEN.bit.RSFEN1    = 0x%x\n", IO_LTM_P1.RBK.RSFEN.bit.RSFEN1    ));
	Ddim_Print(( "IO_LTM_P1.RBK.HVEN.bit.HVEN       = 0x%x\n", IO_LTM_P1.RBK.HVEN.bit.HVEN       ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTHSTA0.bit.BTHSTA0 = 0x%x\n", IO_LTM_P1.RBK.BTHSTA0.bit.BTHSTA0 ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTVSTA0.bit.BTVSTA0 = 0x%x\n", IO_LTM_P1.RBK.BTVSTA0.bit.BTVSTA0 ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTHSIZ0.bit.BTHSIZ0 = 0x%x\n", IO_LTM_P1.RBK.BTHSIZ0.bit.BTHSIZ0 ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTVSIZ0.bit.BTVSIZ0 = 0x%x\n", IO_LTM_P1.RBK.BTVSIZ0.bit.BTVSIZ0 ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTHSTA1.bit.BTHSTA1 = 0x%x\n", IO_LTM_P1.RBK.BTHSTA1.bit.BTHSTA1 ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTVSTA1.bit.BTVSTA1 = 0x%x\n", IO_LTM_P1.RBK.BTVSTA1.bit.BTVSTA1 ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTHSIZ1.bit.BTHSIZ1 = 0x%x\n", IO_LTM_P1.RBK.BTHSIZ1.bit.BTHSIZ1 ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTVSIZ1.bit.BTVSIZ1 = 0x%x\n", IO_LTM_P1.RBK.BTVSIZ1.bit.BTVSIZ1 ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.RBK.RIOCTL.bit.INSEL    = 0x%x\n", IO_LTM_P2.RBK.RIOCTL.bit.INSEL    ));
	Ddim_Print(( "IO_LTM_P2.RBK.RIOCTL.bit.BAYER0   = 0x%x\n", IO_LTM_P2.RBK.RIOCTL.bit.BAYER0   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RIOCTL.bit.BAYER1   = 0x%x\n", IO_LTM_P2.RBK.RIOCTL.bit.BAYER1   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RIOCTL.bit.SROMD    = 0x%x\n", IO_LTM_P2.RBK.RIOCTL.bit.SROMD    ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSFEN.bit.RSFEN0    = 0x%x\n", IO_LTM_P2.RBK.RSFEN.bit.RSFEN0    ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSFEN.bit.RSFEN1    = 0x%x\n", IO_LTM_P2.RBK.RSFEN.bit.RSFEN1    ));
	Ddim_Print(( "IO_LTM_P2.RBK.HVEN.bit.HVEN       = 0x%x\n", IO_LTM_P2.RBK.HVEN.bit.HVEN       ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTHSTA0.bit.BTHSTA0 = 0x%x\n", IO_LTM_P2.RBK.BTHSTA0.bit.BTHSTA0 ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTVSTA0.bit.BTVSTA0 = 0x%x\n", IO_LTM_P2.RBK.BTVSTA0.bit.BTVSTA0 ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTHSIZ0.bit.BTHSIZ0 = 0x%x\n", IO_LTM_P2.RBK.BTHSIZ0.bit.BTHSIZ0 ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTVSIZ0.bit.BTVSIZ0 = 0x%x\n", IO_LTM_P2.RBK.BTVSIZ0.bit.BTVSIZ0 ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTHSTA1.bit.BTHSTA1 = 0x%x\n", IO_LTM_P2.RBK.BTHSTA1.bit.BTHSTA1 ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTVSTA1.bit.BTVSTA1 = 0x%x\n", IO_LTM_P2.RBK.BTVSTA1.bit.BTVSTA1 ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTHSIZ1.bit.BTHSIZ1 = 0x%x\n", IO_LTM_P2.RBK.BTHSIZ1.bit.BTHSIZ1 ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTVSIZ1.bit.BTVSIZ1 = 0x%x\n", IO_LTM_P2.RBK.BTVSIZ1.bit.BTVSIZ1 ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
}

void ct_im_ltm_rbk_print_all_reg( void )
{
	Im_LTM_On_Pclk( D_IM_LTM_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P1.RBK.RBKSR     = 0x%lx\n", IO_LTM_P1.RBK.RBKSR.word     ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSRAMEN   = 0x%lx\n", IO_LTM_P1.RBK.RSRAMEN.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RTRG      = 0x%lx\n", IO_LTM_P1.RBK.RTRG.word      ));
	Ddim_Print(( "IO_LTM_P1.RBK.RFRSTP    = 0x%lx\n", IO_LTM_P1.RBK.RFRSTP.word    ));
	Ddim_Print(( "IO_LTM_P1.RBK.RPARMSK   = 0x%lx\n", IO_LTM_P1.RBK.RPARMSK.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RINT0     = 0x%lx\n", IO_LTM_P1.RBK.RINT0.word     ));
	Ddim_Print(( "IO_LTM_P1.RBK.RINT1     = 0x%lx\n", IO_LTM_P1.RBK.RINT1.word     ));
	Ddim_Print(( "IO_LTM_P1.RBK.RLINTLV   = 0x%lx\n", IO_LTM_P1.RBK.RLINTLV.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RAXICTLR1 = 0x%lx\n", IO_LTM_P1.RBK.RAXICTLR1.word ));
	Ddim_Print(( "IO_LTM_P1.RBK.RAXIRERR  = 0x%lx\n", IO_LTM_P1.RBK.RAXIRERR.word  ));
	Ddim_Print(( "IO_LTM_P1.RBK.RAXICTLW1 = 0x%lx\n", IO_LTM_P1.RBK.RAXICTLW1.word ));
	Ddim_Print(( "IO_LTM_P1.RBK.RAXIWERR  = 0x%lx\n", IO_LTM_P1.RBK.RAXIWERR.word  ));
	Ddim_Print(( "IO_LTM_P1.RBK.RAXIBSIZ  = 0x%lx\n", IO_LTM_P1.RBK.RAXIBSIZ.word  ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDRHSZ   = 0x%lx\n", IO_LTM_P1.RBK.RSDRHSZ.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDRDEF   = 0x%lx\n", IO_LTM_P1.RBK.RSDRDEF.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDRVSZ   = 0x%lx\n", IO_LTM_P1.RBK.RSDRVSZ.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDRADR   = 0x%lx\n", IO_LTM_P1.RBK.RSDRADR.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDRADG   = 0x%lx\n", IO_LTM_P1.RBK.RSDRADG.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDRADB   = 0x%lx\n", IO_LTM_P1.RBK.RSDRADB.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDWAD    = 0x%lx\n", IO_LTM_P1.RBK.RSDWAD.word    ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSDWDEF   = 0x%lx\n", IO_LTM_P1.RBK.RSDWDEF.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RIOCTL    = 0x%lx\n", IO_LTM_P1.RBK.RIOCTL.word    ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTHSTA0   = 0x%lx\n", IO_LTM_P1.RBK.BTHSTA0.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTVSTA0   = 0x%lx\n", IO_LTM_P1.RBK.BTVSTA0.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTHSIZ0   = 0x%lx\n", IO_LTM_P1.RBK.BTHSIZ0.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTVSIZ0   = 0x%lx\n", IO_LTM_P1.RBK.BTVSIZ0.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTHSTA1   = 0x%lx\n", IO_LTM_P1.RBK.BTHSTA1.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTVSTA1   = 0x%lx\n", IO_LTM_P1.RBK.BTVSTA1.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTHSIZ1   = 0x%lx\n", IO_LTM_P1.RBK.BTHSIZ1.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.BTVSIZ1   = 0x%lx\n", IO_LTM_P1.RBK.BTVSIZ1.word   ));
	Ddim_Print(( "IO_LTM_P1.RBK.RSFEN     = 0x%lx\n", IO_LTM_P1.RBK.RSFEN.word     ));
	Ddim_Print(( "IO_LTM_P1.RBK.HVEN      = 0x%lx\n", IO_LTM_P1.RBK.HVEN.word      ));
	Ddim_Print(( "IO_LTM_P1.RBK.RHSTA     = 0x%lx\n", IO_LTM_P1.RBK.RHSTA.word     ));
	Ddim_Print(( "IO_LTM_P1.RBK.RHPIT     = 0x%lx\n", IO_LTM_P1.RBK.RHPIT.word     ));
	Ddim_Print(( "IO_LTM_P1.RBK.RVSTA     = 0x%lx\n", IO_LTM_P1.RBK.RVSTA.word     ));
	Ddim_Print(( "IO_LTM_P1.RBK.RVPIT     = 0x%lx\n", IO_LTM_P1.RBK.RVPIT.word     ));
	Ddim_Print(( "IO_LTM_P1.RBK.RDCMD     = 0x%lx\n", IO_LTM_P1.RBK.RDCMD.word     ));
	Ddim_Print(( "IO_LTM_P1.RBK.RTEN      = 0x%lx\n", IO_LTM_P1.RBK.RTEN.word      ));
	Ddim_Print(( "IO_LTM_P1.RBK.RTHSTA    = 0x%lx\n", IO_LTM_P1.RBK.RTHSTA.word    ));
	Ddim_Print(( "IO_LTM_P1.RBK.RTVSTA    = 0x%lx\n", IO_LTM_P1.RBK.RTVSTA.word    ));
	Ddim_Print(( "IO_LTM_P1.RBK.RTHSIZ    = 0x%lx\n", IO_LTM_P1.RBK.RTHSIZ.word    ));
	Ddim_Print(( "IO_LTM_P1.RBK.RTVSIZ    = 0x%lx\n", IO_LTM_P1.RBK.RTVSIZ.word    ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( "IO_LTM_P2.RBK.RBKSR     = 0x%lx\n", IO_LTM_P2.RBK.RBKSR.word     ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSRAMEN   = 0x%lx\n", IO_LTM_P2.RBK.RSRAMEN.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RTRG      = 0x%lx\n", IO_LTM_P2.RBK.RTRG.word      ));
	Ddim_Print(( "IO_LTM_P2.RBK.RFRSTP    = 0x%lx\n", IO_LTM_P2.RBK.RFRSTP.word    ));
	Ddim_Print(( "IO_LTM_P2.RBK.RPARMSK   = 0x%lx\n", IO_LTM_P2.RBK.RPARMSK.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RINT0     = 0x%lx\n", IO_LTM_P2.RBK.RINT0.word     ));
	Ddim_Print(( "IO_LTM_P2.RBK.RINT1     = 0x%lx\n", IO_LTM_P2.RBK.RINT1.word     ));
	Ddim_Print(( "IO_LTM_P2.RBK.RLINTLV   = 0x%lx\n", IO_LTM_P2.RBK.RLINTLV.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RAXICTLR1 = 0x%lx\n", IO_LTM_P2.RBK.RAXICTLR1.word ));
	Ddim_Print(( "IO_LTM_P2.RBK.RAXIRERR  = 0x%lx\n", IO_LTM_P2.RBK.RAXIRERR.word  ));
	Ddim_Print(( "IO_LTM_P2.RBK.RAXICTLW1 = 0x%lx\n", IO_LTM_P2.RBK.RAXICTLW1.word ));
	Ddim_Print(( "IO_LTM_P2.RBK.RAXIWERR  = 0x%lx\n", IO_LTM_P2.RBK.RAXIWERR.word  ));
	Ddim_Print(( "IO_LTM_P2.RBK.RAXIBSIZ  = 0x%lx\n", IO_LTM_P2.RBK.RAXIBSIZ.word  ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDRHSZ   = 0x%lx\n", IO_LTM_P2.RBK.RSDRHSZ.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDRDEF   = 0x%lx\n", IO_LTM_P2.RBK.RSDRDEF.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDRVSZ   = 0x%lx\n", IO_LTM_P2.RBK.RSDRVSZ.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDRADR   = 0x%lx\n", IO_LTM_P2.RBK.RSDRADR.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDRADG   = 0x%lx\n", IO_LTM_P2.RBK.RSDRADG.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDRADB   = 0x%lx\n", IO_LTM_P2.RBK.RSDRADB.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDWAD    = 0x%lx\n", IO_LTM_P2.RBK.RSDWAD.word    ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSDWDEF   = 0x%lx\n", IO_LTM_P2.RBK.RSDWDEF.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RIOCTL    = 0x%lx\n", IO_LTM_P2.RBK.RIOCTL.word    ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTHSTA0   = 0x%lx\n", IO_LTM_P2.RBK.BTHSTA0.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTVSTA0   = 0x%lx\n", IO_LTM_P2.RBK.BTVSTA0.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTHSIZ0   = 0x%lx\n", IO_LTM_P2.RBK.BTHSIZ0.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTVSIZ0   = 0x%lx\n", IO_LTM_P2.RBK.BTVSIZ0.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTHSTA1   = 0x%lx\n", IO_LTM_P2.RBK.BTHSTA1.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTVSTA1   = 0x%lx\n", IO_LTM_P2.RBK.BTVSTA1.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTHSIZ1   = 0x%lx\n", IO_LTM_P2.RBK.BTHSIZ1.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.BTVSIZ1   = 0x%lx\n", IO_LTM_P2.RBK.BTVSIZ1.word   ));
	Ddim_Print(( "IO_LTM_P2.RBK.RSFEN     = 0x%lx\n", IO_LTM_P2.RBK.RSFEN.word     ));
	Ddim_Print(( "IO_LTM_P2.RBK.HVEN      = 0x%lx\n", IO_LTM_P2.RBK.HVEN.word      ));
	Ddim_Print(( "IO_LTM_P2.RBK.RHSTA     = 0x%lx\n", IO_LTM_P2.RBK.RHSTA.word     ));
	Ddim_Print(( "IO_LTM_P2.RBK.RHPIT     = 0x%lx\n", IO_LTM_P2.RBK.RHPIT.word     ));
	Ddim_Print(( "IO_LTM_P2.RBK.RVSTA     = 0x%lx\n", IO_LTM_P2.RBK.RVSTA.word     ));
	Ddim_Print(( "IO_LTM_P2.RBK.RVPIT     = 0x%lx\n", IO_LTM_P2.RBK.RVPIT.word     ));
	Ddim_Print(( "IO_LTM_P2.RBK.RDCMD     = 0x%lx\n", IO_LTM_P2.RBK.RDCMD.word     ));
	Ddim_Print(( "IO_LTM_P2.RBK.RTEN      = 0x%lx\n", IO_LTM_P2.RBK.RTEN.word      ));
	Ddim_Print(( "IO_LTM_P2.RBK.RTHSTA    = 0x%lx\n", IO_LTM_P2.RBK.RTHSTA.word    ));
	Ddim_Print(( "IO_LTM_P2.RBK.RTVSTA    = 0x%lx\n", IO_LTM_P2.RBK.RTVSTA.word    ));
	Ddim_Print(( "IO_LTM_P2.RBK.RTHSIZ    = 0x%lx\n", IO_LTM_P2.RBK.RTHSIZ.word    ));
	Ddim_Print(( "IO_LTM_P2.RBK.RTVSIZ    = 0x%lx\n", IO_LTM_P2.RBK.RTVSIZ.word    ));
	Im_LTM_Off_Pclk( D_IM_LTM_PIPE12 );
}

void ct_im_ltm_rbk_set_sro(E_IM_PRO_UNIT_NUM unitNo, guchar testPtn)
{
	T_IM_PRO_SROTOP_CTRL		sroCtrl;
	T_IM_PRO_PG_CTRL			pgCtrl;
	T_IM_PRO_M2P_CTRL			m2pCtrl;
	T_IM_PRO_PRCH_CTRL			prCtrl;
	T_IM_PRO_PRCH_AREA			prArea = {
		.width = 1280 * 1.5,				// bytes
		.height = 960 / 2,
		.global_width = 1280 * 2 * 1.5,	// 12bit pack, Interlace
	};
	T_IM_PRO_INT_SROTOP_CTRL	intCtrl;
	T_IM_PRO_CALLBACK_CFG		callbackCfg;

	if( testPtn == 1 ){
		prArea.width  = 4680 * 3 / 2;
		prArea.height = 3500 / 2;
		prArea.global_width = 4680 * 2 * 3 / 2;
	}

	Im_PRO_SROTOP_Init( unitNo );

//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Dd_Top_Set_CLKSTOP10_SRO1CK( 1 );
	Dd_Top_Set_CLKSTOP12_SRO2CK( 1 );
	Dd_Top_Set_CLKSEL5_SRO1CLK( 0 );		// 300MHz
	Dd_Top_Set_CLKSEL7_SRO2CLK( 0 );		// 300MHz
	Dd_Top_Set_CLKSTOP10_SRO1CK( 0 );
	Dd_Top_Set_CLKSTOP12_SRO2CK( 0 );

	Ddim_Print(( "SRO1 CLK %u\n", Dd_Top_Get_CLKSEL5_SRO1CLK() ));
	Ddim_Print(( "SRO2 CLK %u\n", Dd_Top_Get_CLKSEL7_SRO2CLK() ));

	Dd_Top_Set_CLKSTOP10_LTMRBK1CK( 1 );
	Dd_Top_Set_CLKSTOP12_LTMRBK2CK( 1 );
	Dd_Top_Set_CLKSEL5_LTMRBK1CLK( 8 );		// SRO1CLK
	Dd_Top_Set_CLKSEL7_LTMRBK2CLK( 8 );		// SRO2CLK
	Dd_Top_Set_CLKSTOP12_LTMRBK2CK( 0 );
	Dd_Top_Set_CLKSTOP10_LTMRBK1CK( 0 );
//#endif

	Im_PRO_SROTOP_Control_Clock( unitNo, E_IM_PRO_SROTOP_CLK_TYPE_SROCLK, D_IM_PRO_CLOCK_ON, 1 );

	// B2BTOP(and PAT) settings
	sroCtrl.input_mode				= E_IM_PRO_SROTOP_INPUT_MODE_REINPUT;
	sroCtrl.sro_mode_sel			= E_IM_PRO_SROTOP_MODE0;
	sroCtrl.cag_target_sel			= E_IM_PRO_SROTOP_CAG_TARGET_BLOCK_SRO;
	sroCtrl.bay_out_path_sel		= E_IM_PRO_SROTOP_PATH_SEL_BAY_OUT_WITHOUT_BR;
	sroCtrl.b2b_connect_path_sel	= E_IM_PRO_SROTOP_PATH_SEL_B2B_CONN_WITHOUT_BR;
	sroCtrl.ltm_connect_path_sel	= E_IM_PRO_SROTOP_PATH_SEL_LTM_CONN_WITHOUT_BR;
	sroCtrl.first_pixel[0]			= E_IM_PRO_ORG_R;
	sroCtrl.first_pixel[1]			= E_IM_PRO_ORG_GB;
	Im_PRO_SROTOP_Ctrl( unitNo, &sroCtrl );

	// PG settings
	pgCtrl.mode				= E_IM_PRO_PG_MODE_2LINE;
	if( unitNo == E_IM_PRO_BOTH_UNIT ){
		pgCtrl.input_img_width		= D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH / 2;
	}
	else{
		pgCtrl.input_img_width		= D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH;
	}
	pgCtrl.input_img_lines		= D_IM_LTM_RBK_SRC_IMG_PIXS_LINES / 2;
	if( testPtn == 1 ){
		if( unitNo == E_IM_PRO_BOTH_UNIT ){
			pgCtrl.input_img_width		= 4680 / 2;
		}
		else{
			pgCtrl.input_img_width		= 4680;
		}
		pgCtrl.input_img_lines		= 3500 / 2;
	}
	pgCtrl.vertical_blanking	= 200;		// branking line after image
	pgCtrl.horizontal_blanking	= 1000;		// branking line after image
	pgCtrl.start_blanking		= 100;		// branking line before image
	Im_PRO_PG_Ctrl( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, &pgCtrl );

	// M2P settings
	m2pCtrl.data_type				= E_IM_PRO_M2P_DATA_TYPE_12BIT;
	m2pCtrl.deknee_enable			= E_IM_PRO_M2P_DEKNEE_DIS;
	m2pCtrl.shift_bit				= E_IM_PRO_M2P_SHIFT_0BIT;
	m2pCtrl.shift_sat				= E_IM_PRO_M2P_SAT_NOCOMP;
	m2pCtrl.bit_shift				= E_IM_PRO_M2P_BIT_SHIFT_L;
	m2pCtrl.valid_bit_count		= 8;	// dummy
	m2pCtrl.shift_value			= 0;
	m2pCtrl.upper_limit_clip_value	= 0xFFFF;
	m2pCtrl.lower_limit_clip_value	= 0;
	Im_PRO_M2P_Ctrl( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_M2P_0, &m2pCtrl );
	Im_PRO_M2P_Ctrl( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_M2P_1, &m2pCtrl );

	// PRch settings
	prCtrl.trans_mode		= E_IM_PRO_PRCH_BURST_512BYTE;
	prCtrl.req_threshold	= E_IM_PRO_PRCH_CNT_NOLIMIT;
	prCtrl.trans_to		= E_IM_PRO_PRCH_TRANS_IO_0;
	Im_PRO_PRch_Ctrl( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_0, &prCtrl );
	Im_PRO_PRch_Ctrl( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_1, &prCtrl );

	if( unitNo == E_IM_PRO_BOTH_UNIT ){
		prArea.width /= 2;
	}

	if( unitNo == E_IM_PRO_BOTH_UNIT ){
		Im_PRO_PRch_Set_Addr( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_0,
				D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP );
		Im_PRO_PRch_Set_Addr( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_1,
				D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP + prArea.global_width / 2 );
		Im_PRO_PRch_Set_Addr( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_0,
				D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP + prArea.width );
		Im_PRO_PRch_Set_Addr( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_1,
				D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP + prArea.width + prArea.global_width / 2 );
	}
	else{
		Im_PRO_PRch_Set_Addr( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_0,
				D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP );
		Im_PRO_PRch_Set_Addr( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_1,
				D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP + prArea.global_width / 2 );
	}

	Im_PRO_PRch_Set_Area( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_0, &prArea );
	Im_PRO_PRch_Set_Area( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_1, &prArea );

	intCtrl.int_mode						= E_IM_PRO_INT_INTMD_OR;
	intCtrl.vd_enable[0].interrupt_bit		= D_IM_PRO_SROTOP_INT_VDE0;
	intCtrl.vd_enable[0].permission_flg	= 1;
	intCtrl.hd_enable[0].interrupt_bit		= 0;
	intCtrl.hd_enable[0].permission_flg	= 0;
	intCtrl.vd_enable[1].interrupt_bit		= D_IM_PRO_SROTOP_INT_VDE1;
	intCtrl.vd_enable[1].permission_flg	= 1;
	intCtrl.hd_enable[1].interrupt_bit		= 0;
	intCtrl.hd_enable[1].permission_flg	= 0;
	Im_PRO_SROTOP_Interrupt_Ctrl( unitNo, &intCtrl );

	callbackCfg.inthandler	= ctImLtmRbkSroVdIntHandler;
	callbackCfg.user_param	= 0;
	Im_PRO_SROTOP_Pipe_Set_VD_Int_Handler( E_IM_PRO_UNIT_NUM_1, &callbackCfg );

	callbackCfg.inthandler	= ctImLtmRbkSroPrchIntHandler;
	callbackCfg.user_param	= 0;
	Im_PRO_PRch_Set_Int_Handler( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_0, &callbackCfg );
	Im_PRO_PRch_Set_Int_Handler( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_1, &callbackCfg );

}

void ct_im_ltm_rbk_start_sro(E_IM_PRO_UNIT_NUM unitNo)
{
	S_GCT_IM_LTM_RBK_SRO_VD_FLG = FALSE;

	Im_PRO_PRch_Start( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_0 );
	Im_PRO_PRch_Start( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_1 );
	Im_PRO_M2P_Set_PAEN( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_M2P_0, E_IM_PRO_M2P_PAEN_EN );
	Im_PRO_M2P_Set_PAEN( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_M2P_1, E_IM_PRO_M2P_PAEN_EN );
	Im_PRO_M2P_Start( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_M2P_0 );
	Im_PRO_M2P_Start( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_M2P_1 );

	Im_PRO_PG_Start( unitNo, E_IM_PRO_BLOCK_TYPE_SRO );
}

void ct_im_ltm_rbk_waitend_stop_sro(E_IM_PRO_UNIT_NUM unitNo)
{
	ctImLtmRbkWaitVdSro();

	Im_PRO_PWch_Stop( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PWCH_0, 0 );
	Im_PRO_P2M_Stop( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_P2M_CH0, 0 );
	Im_PRO_PWch_Stop( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PWCH_1, 0 );
	Im_PRO_P2M_Stop( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_P2M_CH1, 0 );

	Im_PRO_PRch_Stop( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_0, 0 );
	Im_PRO_M2P_Stop( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_M2P_0, 0 );
	Im_PRO_PRch_Stop( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_PRCH_1, 0 );
	Im_PRO_M2P_Stop( unitNo, E_IM_PRO_BLOCK_TYPE_SRO, E_IM_PRO_M2P_1, 0 );

	ctImLtmRbkWaitVdSro();

	Im_PRO_PG_Stop( unitNo, E_IM_PRO_BLOCK_TYPE_SRO );
}

void CT_Im_LTM_RBK_Run(CtImLtmRbk *self, const guint32 ctIdx1st, const guint32 ctIdx2nd, const guint32 ctIdx3rd)
{
	CtImLtmRbkPrivate *priv = CT_IM_LTM_RBK_GET_PRIVATE(self);

	ct_im_rbk_run2_set_var1(priv->runself2,priv->runself1);
	ct_im_rbk_run3_set_var1(priv->runself3,priv->runself1);

#ifdef CO_MSG_PRINT_ON
	gint32 result = D_DDIM_INPUT_PARAM_ERROR;
#endif
	static BOOL isInit = 0;
	guchar loopCnt;

	Ddim_Print(( "CT_Im_LTM_RBK_Run( %u, %u, %u ) Begin\n", ctIdx1st, ctIdx2nd, ctIdx3rd ));

	if( isInit == 0 ) {
#ifdef CO_DEBUG_ON_PC
		memset( (void*)&IO_LTM_P1.RBK, '\0', sizeof(IO_LTM_P1.RBK) );
		memset( (void*)&IO_LTM_P2.RBK, '\0', sizeof(IO_LTM_P2.RBK) );
		IO_LTM_P1.RBK.RTRG.word = 2;
		IO_LTM_P2.RBK.RTRG.word = 2;
#endif // CO_DEBUG_ON_PC
		if( !((ctIdx1st == 1) && (ctIdx2nd == 1)) ) {
			Ddim_Print(( "Im_LTM_RBK_Init() Begin\n" ));
			Im_LTM_RBK_Init( D_IM_LTM_PIPE12 );
			Ddim_Print(( "Im_LTM_RBK_Init() End\n" ));
			isInit = 1;
		}
	}
	Dd_Top_Set_CLKSTOP10_LTMRBK1CK( 1 );
	Dd_Top_Set_CLKSTOP12_LTMRBK2CK( 1 );
	Dd_Top_Set_CLKSEL5_LTMRBK1CLK( 0 );		// 300MHz
	Dd_Top_Set_CLKSEL7_LTMRBK2CLK( 0 );		// 300MHz
	Dd_Top_Set_CLKSTOP12_LTMRBK2CK( 0 );
	Dd_Top_Set_CLKSTOP10_LTMRBK1CK( 0 );

	if( ctIdx1st != 3 ){
		for( loopCnt = 0; loopCnt <= 1; loopCnt++ ){
			ct_im_rbk_run1_set_pipe_no(priv->runself1,loopCnt);
			switch( ctIdx1st ) {
				case 1:
					CtImLtmRbk_D_IM_LTM_RESULT( ctImLtmRbkRun1(priv->runself1, ctIdx2nd ) );
					break;

				case 2:
					CtImLtmRbk_D_IM_LTM_RESULT( ctImLtmRbkRun2( priv->runself2, ctIdx2nd ) );
					break;

				default:
					Ddim_Print(( "Error: Unknown command.\n" ));
					break;
			}

#ifdef CO_MSG_PRINT_ON
			Ddim_Print(( "result = 0x%x\n", result ));
#endif
			Ddim_Print(( "CT_Im_LTM_RBK_Run( %u, %u, %u) End\n", ctIdx1st, ctIdx2nd, loopCnt ));
		}
	}
	else{
		ct_im_rbk_run1_set_pipe_no(priv->runself1,ctIdx3rd);

		CtImLtmRbk_D_IM_LTM_RESULT( ctImLtmRbkRun3( priv->runself3, ctIdx2nd ) );

#ifdef CO_MSG_PRINT_ON
		Ddim_Print(( "result = 0x%x\n", result ));
#endif
		Ddim_Print(( "CT_Im_LTM_RBK_Run( %u, %u, %u) End\n", ctIdx1st, ctIdx2nd, ctIdx3rd ));
	}

	return;
}

// for Debug console interface
void ct_im_ltm_rbk_main(CtImLtmRbk* self, gint32 argc, gchar** argv)
{
	if( argc < 3 ) {
		Ddim_Print(( "ct_im_ltm_rbk_main: parameter error.\n" ));
		return;
	}

	CT_Im_LTM_RBK_Run(self, (guint32)atoi((const char*)argv[1]),
					   (guint32)atoi((const char*)argv[2]),
					   (guint32)atoi((const char*)argv[3]) );
}

CtImLtmRbk *ct_im_ltm_rbk_new(void) 
{
    CtImLtmRbk *self = g_object_new(CT_TYPE_IM_LTM_RBK, NULL);
    return self;
}
