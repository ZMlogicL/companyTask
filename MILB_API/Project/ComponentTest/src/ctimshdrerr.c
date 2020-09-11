/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImShdrErr
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include <string.h>
#include <stdlib.h>

#include "ct_im_shdr.h"
#include "jdsshdr.h"
#include "im_shdr.h"

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif //CO_ACT_CLOCK | CO_ACT_HCLOCK | CO_ACT_PCLOCK

#include "ddim_user_custom.h"
#include "ctimshdr.h"
#include "ctimshdrerr.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImShdrErr, ct_im_shdr_err)
#define CT_IM_SHDR_ERR_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImShdrErrPrivate, CT_TYPE_IM_SHDR_ERR))


struct _CtImShdrErrPrivate
{

};


static VOID 			ctImShdrErrCtrl( VOID );
static VOID 			ctImShdrErrPre( VOID );
static VOID 			ctImShdrErrFmd( VOID );
static VOID 			ctImShdrErrPmsk( VOID );
static VOID 			ctImShdrErrSpnr( VOID );
static VOID 			ctImShdrErrMask( VOID );
static VOID 			ctImShdrErrBld( VOID );
static VOID 			ctImShdrErrPost( VOID );
static VOID 			ctImShdrErrResize( VOID );
static VOID 			ctImShdrErrSmc( VOID );
static VOID 			ctImShdrErrDgr( VOID );
static VOID 			ctImShdrErrDgg( VOID );
static VOID 			ctImShdrErrDgb( VOID );
static VOID 			ctImShdrErrDg( VOID );
static VOID 			ctImShdrErrAxi( VOID );
static VOID 			ctImShdrErrAxires( VOID );
static VOID 			ctImShdrGetAxi( VOID );


/********
 * IMPL
 */
static void ct_im_shdr_err_constructor(CtImShdrErr *self)
{
//	CtImShdrErrPrivate *priv = CT_IM_SHDR_ERR_GET_PRIVATE(self);
}

static void ct_im_shdr_err_destructor(CtImShdrErr *self)
{
//	CtImShdrErrPrivate *priv = CT_IM_SHDR_ERR_GET_PRIVATE(self);
}

static VOID ctImShdrErrCtrl( VOID )
{
	INT32			ret;
	T_IM_SHDR_CTRL	ctrl;

	ret = Im_SHDR_Ctrl_Common( NULL );
	Ddim_Print(("Im_SHDR_Ctrl_Common[ret=0x%08x]\n", ret));

	ctrl.image_set.in_bit_depth = D_IM_SHDR_INBITDEPTH_16 + 1;

	ret = Im_SHDR_Ctrl_Common( &ctrl );
	Ddim_Print(("Im_SHDR_Ctrl_Common[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Ctrl_Common( NULL );
	Ddim_Print(("Im_SHDR_Get_Ctrl_Common[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrPre( VOID )
{
	INT32			ret;
	T_IM_SHDR_PRE	pre;

	ret = Im_SHDR_Set_Pre( NULL );
	Ddim_Print(("Im_SHDR_Set_Pre[ret=0x%08x]\n", ret));

	pre.pre_mode.cus_mode = D_IM_SHDR_CUS_YCC420_PADDING + 1;
	ret = Im_SHDR_Set_Pre( &pre );
	Ddim_Print(("Im_SHDR_Set_Pre[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Pre( NULL );
	Ddim_Print(("Im_SHDR_Get_Pre[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrFmd( VOID )
{
	INT32			ret;
	T_IM_SHDR_FMD	fmd;

	ret = Im_SHDR_Set_Fmd( NULL );
	Ddim_Print(("Im_SHDR_Set_Fmd[ret=0x%08x]\n", ret));

	fmd.weight_base = D_IM_SHDR_WGHTBASE_RGB + 1;
	ret = Im_SHDR_Set_Fmd( &fmd );
	Ddim_Print(("Im_SHDR_Set_Fmd[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Fmd( NULL );
	Ddim_Print(("Im_SHDR_Get_Fmd[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrPmsk( VOID )
{
	INT32			ret;
	T_IM_SHDR_PMSK	pmsk;

	ret = Im_SHDR_Set_PreMask( NULL );
	Ddim_Print(("Im_SHDR_Set_PreMask[ret=0x%08x]\n", ret));

	pmsk.pmsk_mode = D_IM_SHDR_PMSKMD_AVE + 1;
	ret = Im_SHDR_Set_PreMask( &pmsk );
	Ddim_Print(("Im_SHDR_Set_PreMask[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_PreMask( NULL );
	Ddim_Print(("Im_SHDR_Get_PreMask[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrSpnr( VOID )
{
	INT32			ret;
	T_IM_SHDR_SPNR	spnr;

	ret = Im_SHDR_Set_Spnr( NULL );
	Ddim_Print(("Im_SHDR_Set_Spnr[ret=0x%08x]\n", ret));

	spnr.spnr_en = D_IM_SHDR_ENABLE + 1;
	ret = Im_SHDR_Set_Spnr( &spnr );
	Ddim_Print(("Im_SHDR_Set_Spnr[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Spnr( NULL );
	Ddim_Print(("Im_SHDR_Get_Spnr[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrMask( VOID )
{
	INT32			ret;

	ret = Im_SHDR_Set_Mask( NULL );
	Ddim_Print(("Im_SHDR_Set_Mask[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Mask( NULL );
	Ddim_Print(("Im_SHDR_Get_Mask[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrBld( VOID )
{
	INT32			ret;
	T_IM_SHDR_BLD	bld;

	ret = Im_SHDR_Set_Blend( NULL );
	Ddim_Print(("Im_SHDR_Set_Blend[ret=0x%08x]\n", ret));

	bld.blend_sel = D_IM_SHDR_BLDSEL_LONG_SHORT + 1;
	ret = Im_SHDR_Set_Blend( &bld );
	Ddim_Print(("Im_SHDR_Set_Blend[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Blend( NULL );
	Ddim_Print(("Im_SHDR_Get_Blend[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrPost( VOID )
{
	INT32			ret;
	T_IM_SHDR_POST	post;

	ret = Im_SHDR_Set_Post( NULL );
	Ddim_Print(("Im_SHDR_Set_Post[ret=0x%08x]\n", ret));

	post.ev_sel = D_IM_SHDR_POSTSEL1_RGB + 1;
	ret = Im_SHDR_Set_Post( &post );
	Ddim_Print(("Im_SHDR_Set_Post[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Post( NULL );
	Ddim_Print(("Im_SHDR_Get_Post[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrResize( VOID )
{
	INT32				ret;
	T_IM_SHDR_RESIZE	resize;

	ret = Im_SHDR_Set_Resize( NULL );
	Ddim_Print(("Im_SHDR_Set_Resize[ret=0x%08x]\n", ret));

	resize.chmode.a_w_en = D_IM_SHDR_ENABLE + 1;
	ret = Im_SHDR_Set_Resize( &resize );
	Ddim_Print(("Im_SHDR_Set_Resize[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Resize( NULL );
	Ddim_Print(("Im_SHDR_Get_Resize[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrSmc( VOID )
{
	INT32			ret;
	T_IM_SHDR_SMC	smc;

	ret = Im_SHDR_Set_Smc( NULL );
	Ddim_Print(("Im_SHDR_Set_Smc[ret=0x%08x]\n", ret));

	smc.mcarmd.mca_mode = D_IM_MCAMD_MAX_MIN_VECTOR + 1;
	ret = Im_SHDR_Set_Smc( &smc );
	Ddim_Print(("Im_SHDR_Set_Smc[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Smc( NULL );
	Ddim_Print(("Im_SHDR_Get_Smc[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrDgr( VOID )
{
	INT32	ret;
	USHORT	srcTbl[ D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE ];

	ret = Im_SHDR_Set_Degamma_R( NULL, 0, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE );
	Ddim_Print(("Im_SHDR_Set_Degamma_R[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Set_Degamma_R( &srcTbl[0], 1, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE );
	Ddim_Print(("Im_SHDR_Set_Degamma_R[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Degamma_R( NULL, 0, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE, D_IM_SHDR_DGTRSEL_PREFL );
	Ddim_Print(("Im_SHDR_Get_Degamma_R[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Degamma_R( &srcTbl[0], 1, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE, D_IM_SHDR_DGTRSEL_PREFL );
	Ddim_Print(("Im_SHDR_Get_Degamma_R[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrDgg( VOID )
{
	INT32	ret;
	USHORT	srcTbl[ D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE ];

	ret = Im_SHDR_Set_Degamma_G( NULL, 0, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE );
	Ddim_Print(("Im_SHDR_Set_Degamma_G[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Set_Degamma_G( &srcTbl[0], 1, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE );
	Ddim_Print(("Im_SHDR_Set_Degamma_G[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Degamma_G( NULL, 0, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE, D_IM_SHDR_DGTRSEL_PREFL );
	Ddim_Print(("Im_SHDR_Get_Degamma_G[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Degamma_G( &srcTbl[0], 1, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE, D_IM_SHDR_DGTRSEL_PREFL );
	Ddim_Print(("Im_SHDR_Get_Degamma_G[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrDgb( VOID )
{
	INT32	ret;
	USHORT	srcTbl[ D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE ];

	ret = Im_SHDR_Set_Degamma_B( NULL, 0, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE );
	Ddim_Print(("Im_SHDR_Set_Degamma_B[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Set_Degamma_B( &srcTbl[0], 1, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE );
	Ddim_Print(("Im_SHDR_Set_Degamma_B[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Degamma_B( NULL, 0, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE, D_IM_SHDR_DGTRSEL_PREFL );
	Ddim_Print(("Im_SHDR_Get_Degamma_B[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Degamma_B( &srcTbl[0], 1, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE, D_IM_SHDR_DGTRSEL_PREFL );
	Ddim_Print(("Im_SHDR_Get_Degamma_B[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrDg( VOID )
{
	INT32	ret;
	USHORT	srcTbl[ D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE ];

	ret = Im_SHDR_Set_Degamma( NULL, &srcTbl[0], &srcTbl[0], 0, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE );
	Ddim_Print(("Im_SHDR_Set_Degamma[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Set_Degamma( &srcTbl[0], &srcTbl[0], &srcTbl[0], 1, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE );
	Ddim_Print(("Im_SHDR_Set_Degamma[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Degamma( NULL, &srcTbl[0], &srcTbl[0], 0, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE, D_IM_SHDR_DGTRSEL_PREFL );
	Ddim_Print(("Im_SHDR_Get_Degamma[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Degamma( &srcTbl[0], &srcTbl[0],&srcTbl[0], 1, D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE, D_IM_SHDR_DGTRSEL_PREFL );
	Ddim_Print(("Im_SHDR_Get_Degamma[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrAxi( VOID )
{
	INT32			ret;
	T_IM_SHDR_AXI	axi;

	ret = Im_SHDR_Set_Axi( NULL );
	Ddim_Print(("Im_SHDR_Set_Axi[ret=0x%08x]\n", ret));

	axi.ax_mode.r_burst = D_IM_SHDR_BURSTLEN_256 + 1;
	ret = Im_SHDR_Set_Axi( &axi );
	Ddim_Print(("Im_SHDR_Set_Axi[ret=0x%08x]\n", ret));

	ret = Im_SHDR_Get_Axi( NULL );
	Ddim_Print(("Im_SHDR_Get_Axi[ret=0x%08x]\n", ret));
}

static VOID ctImShdrErrAxires( VOID )
{
	INT32			ret;

	ret = Im_SHDR_Get_Axi_Response( NULL );
	Ddim_Print(("Im_SHDR_Get_Axi_Response[ret=0x%08x]\n", ret));
}

static VOID ctImShdrGetAxi( VOID )
{
	INT32			ret;
	T_IM_SHDR_AXI	axi;

	ret = Im_SHDR_Get_Axi( &axi );

	Ddim_Print(("ctImShdrGetAxi[ret=0x%08x]\n", ret));
	Ddim_Print(("ax_mode.r_burst	= 0x%08x\n",	axi.ax_mode.r_burst		));
	Ddim_Print(("ax_mode.w_burst	= 0x%08x\n",	axi.ax_mode.w_burst		));
	Ddim_Print(("ax_mode.w_w_mask	= 0x%08x\n",	axi.ax_mode.w_w_mask	));
	Ddim_Print(("r_ctl.a_cahche[0]	= 0x%08x\n",	axi.r_ctl.a_cahche[0]	));
	Ddim_Print(("r_ctl.a_cahche[1]	= 0x%08x\n",	axi.r_ctl.a_cahche[1]	));
	Ddim_Print(("r_ctl.a_protect[0]	= 0x%08x\n",	axi.r_ctl.a_protect[0]	));
	Ddim_Print(("r_ctl.a_protect[1]	= 0x%08x\n",	axi.r_ctl.a_protect[1]	));
	Ddim_Print(("r_ctl.b_cahche[0]	= 0x%08x\n",	axi.r_ctl.b_cahche[0]	));
	Ddim_Print(("r_ctl.b_cahche[1]	= 0x%08x\n",	axi.r_ctl.b_cahche[1]	));
	Ddim_Print(("r_ctl.b_protect[0]	= 0x%08x\n",	axi.r_ctl.b_protect[0]	));
	Ddim_Print(("r_ctl.b_protect[1]	= 0x%08x\n",	axi.r_ctl.b_protect[1]	));
	Ddim_Print(("r_ctl.c_cahche[0]	= 0x%08x\n",	axi.r_ctl.c_cahche[0]	));
	Ddim_Print(("r_ctl.c_cahche[1]	= 0x%08x\n",	axi.r_ctl.c_cahche[1]	));
	Ddim_Print(("r_ctl.c_cahche[2]	= 0x%08x\n",	axi.r_ctl.c_cahche[2]	));
	Ddim_Print(("r_ctl.c_cahche[3]	= 0x%08x\n",	axi.r_ctl.c_cahche[3]	));
	Ddim_Print(("r_ctl.c_protect[0]	= 0x%08x\n",	axi.r_ctl.c_protect[0]	));
	Ddim_Print(("r_ctl.c_protect[1]	= 0x%08x\n",	axi.r_ctl.c_protect[1]	));
	Ddim_Print(("r_ctl.c_protect[2]	= 0x%08x\n",	axi.r_ctl.c_protect[2]	));
	Ddim_Print(("r_ctl.c_protect[3]	= 0x%08x\n",	axi.r_ctl.c_protect[3]	));
	Ddim_Print(("r_ctl.d_cahche[0]	= 0x%08x\n",	axi.r_ctl.d_cahche[0]	));
	Ddim_Print(("r_ctl.d_cahche[1]	= 0x%08x\n",	axi.r_ctl.d_cahche[1]	));
	Ddim_Print(("r_ctl.d_protect[0]	= 0x%08x\n",	axi.r_ctl.d_protect[0]	));
	Ddim_Print(("r_ctl.d_protect[1]	= 0x%08x\n",	axi.r_ctl.d_protect[1]	));
	Ddim_Print(("w_ctl.a_cahche[0]	= 0x%08x\n",	axi.w_ctl.a_cahche[0]	));
	Ddim_Print(("w_ctl.a_cahche[1]	= 0x%08x\n",	axi.w_ctl.a_cahche[1]	));
	Ddim_Print(("w_ctl.a_cahche[2]	= 0x%08x\n",	axi.w_ctl.a_cahche[2]	));
	Ddim_Print(("w_ctl.a_cahche[3]	= 0x%08x\n",	axi.w_ctl.a_cahche[3]	));
	Ddim_Print(("w_ctl.a_protect[0]	= 0x%08x\n",	axi.w_ctl.a_protect[0]	));
	Ddim_Print(("w_ctl.a_protect[1]	= 0x%08x\n",	axi.w_ctl.a_protect[1]	));
	Ddim_Print(("w_ctl.a_protect[2]	= 0x%08x\n",	axi.w_ctl.a_protect[2]	));
	Ddim_Print(("w_ctl.a_protect[3]	= 0x%08x\n",	axi.w_ctl.a_protect[3]	));
	Ddim_Print(("w_ctl.b_cahche[0]	= 0x%08x\n",	axi.w_ctl.b_cahche[0]	));
	Ddim_Print(("w_ctl.b_cahche[1]	= 0x%08x\n",	axi.w_ctl.b_cahche[1]	));
	Ddim_Print(("w_ctl.b_cahche[2]	= 0x%08x\n",	axi.w_ctl.b_cahche[2]	));
	Ddim_Print(("w_ctl.b_cahche[3]	= 0x%08x\n",	axi.w_ctl.b_cahche[3]	));
	Ddim_Print(("w_ctl.b_cahche[4]	= 0x%08x\n",	axi.w_ctl.b_cahche[4]	));
	Ddim_Print(("w_ctl.b_cahche[5]	= 0x%08x\n",	axi.w_ctl.b_cahche[5]	));
	Ddim_Print(("w_ctl.b_protect[0]	= 0x%08x\n",	axi.w_ctl.b_protect[0]	));
	Ddim_Print(("w_ctl.b_protect[1]	= 0x%08x\n",	axi.w_ctl.b_protect[1]	));
	Ddim_Print(("w_ctl.b_protect[2]	= 0x%08x\n",	axi.w_ctl.b_protect[2]	));
	Ddim_Print(("w_ctl.b_protect[3]	= 0x%08x\n",	axi.w_ctl.b_protect[3]	));
	Ddim_Print(("w_ctl.b_protect[4]	= 0x%08x\n",	axi.w_ctl.b_protect[4]	));
	Ddim_Print(("w_ctl.b_protect[5]	= 0x%08x\n",	axi.w_ctl.b_protect[5]	));
	Ddim_Print(("w_ctl.c_cahche[0]	= 0x%08x\n",	axi.w_ctl.c_cahche[0]	));
	Ddim_Print(("w_ctl.c_cahche[1]	= 0x%08x\n",	axi.w_ctl.c_cahche[1]	));
	Ddim_Print(("w_ctl.c_cahche[2]	= 0x%08x\n",	axi.w_ctl.c_cahche[2]	));
	Ddim_Print(("w_ctl.c_cahche[3]	= 0x%08x\n",	axi.w_ctl.c_cahche[3]	));
	Ddim_Print(("w_ctl.c_cahche[4]	= 0x%08x\n",	axi.w_ctl.c_cahche[4]	));
	Ddim_Print(("w_ctl.c_cahche[5]	= 0x%08x\n",	axi.w_ctl.c_cahche[5]	));
	Ddim_Print(("w_ctl.c_cahche[6]	= 0x%08x\n",	axi.w_ctl.c_cahche[6]	));
	Ddim_Print(("w_ctl.c_protect[0]	= 0x%08x\n",	axi.w_ctl.c_protect[0]	));
	Ddim_Print(("w_ctl.c_protect[1]	= 0x%08x\n",	axi.w_ctl.c_protect[1]	));
	Ddim_Print(("w_ctl.c_protect[2]	= 0x%08x\n",	axi.w_ctl.c_protect[2]	));
	Ddim_Print(("w_ctl.c_protect[3]	= 0x%08x\n",	axi.w_ctl.c_protect[3]	));
	Ddim_Print(("w_ctl.c_protect[4]	= 0x%08x\n",	axi.w_ctl.c_protect[4]	));
	Ddim_Print(("w_ctl.c_protect[5]	= 0x%08x\n",	axi.w_ctl.c_protect[5]	));
	Ddim_Print(("w_ctl.c_protect[6]	= 0x%08x\n",	axi.w_ctl.c_protect[6]	));
}


/**********
 * PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
/**
 * @brief       Command processing of SHDR.
 * @param[in]   INT32 argc
 * @param[in]   CHAR** argv
 *
 *	The meaning of parameters
 *	+----------+---------+--------+-------+-------+-----------------------------------------------------+
 *	| P1       | P2      | P4     | P5    | P6    | Meaning                                             |
 *	+----------+---------+--------+-------+-------+-----------------------------------------------------+
 *	| init     |         |        |       |       | SHDR initialize                                     |
 *	|          |         |        |       |       | Im_SHDR_Init()                                      |
 *	|----------+---------+--------+-------+-------+-----------------------------------------------------+
 *	| open     |         |        |       |       | The semaphore of SHDR is acquired                   |
 *	|          |         |        |       |       | Im_SHDR_Open()                                      |
 *	|----------+---------+--------+-------+-------+-----------------------------------------------------+
 *	| close    |         |        |       |       | The semaphore of SHDR is returned                   |
 *	|          |         |        |       |       | Im_SHDR_Close()                                     |
 *	|----------+---------+--------+-------+-------+-----------------------------------------------------+
 *	| ctrl     |         |        |       |       | SHDR parameters set                                 |
 *	|          |         |        |       |       | Im_SHDR_Ctrl_Common()                               |
 *	|----------+---------+--------+-------+-------+-----------------------------------------------------+
 *	| start    |         |        |       |       | SHDR start                                          |
 *	|          |         |        |       |       | Im_SHDR_Start()                                     |
 *	|----------+---------+--------+-------+-------+-----------------------------------------------------+
 *	| wait     |         |        |       |       | SHDR wait end                                       |
 *	|          |         |        |       |       | Im_SHDR_Wait_End()                                  |
 *	|----------+---------+--------+-------+-------+-----------------------------------------------------+
 *	| stop     |         |        |       |       | SHDR stop                                           |
 *	|          |         |        |       |       | Im_SHDR_Stop()                                      |
 *	|----------+---------+--------+-------+-------+-----------------------------------------------------+
 *	| set      | pre     |        |       |       | SHDR pre parameter set                              |
 *	|          |         |        |       |       | Im_SHDR_Set_Pre()                                   |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | fmd     |        |       |       | SHDR FMD parameter set                              |
 *	|          |         |        |       |       | Im_SHDR_Set_Fmd()                                   |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | pmsk    |        |       |       | SHDR PMSK parameter set                             |
 *	|          |         |        |       |       | Im_SHDR_Set_PreMask()                               |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | spnr    |        |       |       | SHDR SPNR parameter set                             |
 *	|          |         |        |       |       | Im_SHDR_Set_Spnr()                                  |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | mask    |        |       |       | SHDR MSK parameter set                              |
 *	|          |         |        |       |       | Im_SHDR_Set_Mask()                                  |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | blend   |        |       |       | SHDR BLD parameter set                              |
 *	|          |         |        |       |       | Im_SHDR_Set_Blend()                                 |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | post    |        |       |       | SHDR POST parameter set                             |
 *	|          |         |        |       |       | Im_SHDR_Set_Post()                                  |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | resize  |        |       |       | SHDR resize parameter set                           |
 *	|          |         |        |       |       | Im_SHDR_Set_Resize()                                |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | smc     |        |       |       | SHDR smc parameter set                              |
 *	|          |         |        |       |       | Im_SHDR_Set_Smc()                                   |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | dgr     |        |       |       | SHDR degamma R table set                            |
 *	|          |         |        |       |       | Im_SHDR_Set_Degamma_R()                             |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | dgg     |        |       |       | SHDR degamma G table set                            |
 *	|          |         |        |       |       | Im_SHDR_Set_Degamma_G()                             |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | dgb     |        |       |       | SHDR degamma B table set                            |
 *	|          |         |        |       |       | Im_SHDR_Set_Degamma_B()                             |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | dg      |        |       |       | SHDR degamma table set                              |
 *	|          |         |        |       |       | Im_SHDR_Set_Degamma()                               |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | axi     |        |       |       | SHDR AXI parameter set                              |
 *	|          |         |        |       |       | Im_SHDR_Set_Axi()                                   |
 *	|----------+---------+--------+-------+-------+-----------------------------------------------------+
 *	| get      | ctrl    |        |       |       | SHDR common parameter get                           |
 *	|          |         |        |       |       | Im_SHDR_Get_Ctrl_Common()                           |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | pre     |        |       |       | SHDR pre parameter get                              |
 *	|          |         |        |       |       | Im_SHDR_Get_Pre()                                   |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | fmd     |        |       |       | SHDR FMD parameter get                              |
 *	|          |         |        |       |       | Im_SHDR_Get_Fmd()                                   |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | pmsk    |        |       |       | SHDR PMSK parameter get                             |
 *	|          |         |        |       |       | Im_SHDR_Get_PreMask()                               |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | spnr    |        |       |       | SHDR SPNR parameter get                             |
 *	|          |         |        |       |       | Im_SHDR_Get_Spnr()                                  |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | mask    |        |       |       | SHDR MSK parameter get                              |
 *	|          |         |        |       |       | Im_SHDR_Get_Mask()                                  |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | blend   |        |       |       | SHDR BLD parameter get                              |
 *	|          |         |        |       |       | Im_SHDR_Get_Blend()                                 |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | post    |        |       |       | SHDR POST parameter get                             |
 *	|          |         |        |       |       | Im_SHDR_Get_Post()                                  |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | resize  |        |       |       | SHDR resize parameter get                           |
 *	|          |         |        |       |       | Im_SHDR_Get_Resize()                                |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | smc     |        |       |       | SHDR smc parameter get                              |
 *	|          |         |        |       |       | Im_SHDR_Get_Smc()                                   |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | dgr     |        |       |       | SHDR degamma R table get                            |
 *	|          |         |        |       |       | Im_SHDR_Get_Degamma_R()                             |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | dgg     |        |       |       | SHDR degamma G table get                            |
 *	|          |         |        |       |       | Im_SHDR_Get_Degamma_G()                             |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | dgb     |        |       |       | SHDR degamma B table get                            |
 *	|          |         |        |       |       | Im_SHDR_Get_Degamma_B()                             |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | dg      |        |       |       | SHDR degamma table get                              |
 *	|          |         |        |       |       | Im_SHDR_Get_Degamma()                               |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | axi     |        |       |       | SHDR AXI parameter get                              |
 *	|          |         |        |       |       | Im_SHDR_Get_Axi()                                   |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | axires  |        |       |       | SHDR AXI response get                               |
 *	|          |         |        |       |       | Im_SHDR_Get_Axi_Response()                          |
 *	+----------+---------+--------+-------+-------+-----------------------------------------------------+
 *	| err      | init                             | Im_SHDR_Init()                                      |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | open                             | Im_SHDR_Open()                                      |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | close                            | Im_SHDR_Close()                                     |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | ctrl                             | Im_SHDR_Ctrl_Common()                               |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Ctrl_Common()                           |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | start                            | Im_SHDR_Start()                                     |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | wait                             | Im_SHDR_Wait_End()                                  |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | stop                             | Im_SHDR_Stop()                                      |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | pre                              | Im_SHDR_Set_Pre()                                   |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Pre()                                   |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | fmd                              | Im_SHDR_Set_Fmd()                                   |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Fmd()                                   |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | pmsk                             | Im_SHDR_Set_PreMask()                               |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_PreMask()                               |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | spnr                             | Im_SHDR_Set_Spnr()                                  |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Spnr()                                  |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | mask                             | Im_SHDR_Set_Mask()                                  |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Mask()                                  |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | blend                            | Im_SHDR_Set_Blend()                                 |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Blend()                                 |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | post                             | Im_SHDR_Set_Post()                                  |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Post()                                  |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | resize                           | Im_SHDR_Set_Resize()                                |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Resizet()                               |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | smc                              | Im_SHDR_Set_Smc()                                   |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Smc()                                   |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | dgr                              | Im_SHDR_Set_Degamma_R()                             |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Degamma_R()                             |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | dgg                              | Im_SHDR_Set_Degamma_G()                             |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Degamma_G()                             |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | dgb                              | Im_SHDR_Set_Degamma_B()                             |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Degamma_B()                             |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | dg                               | Im_SHDR_Set_Degamma()                               |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Degamma()                               |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | axi                              | Im_SHDR_Set_Axi()                                   |
 *	|          |                                  +-----------------------------------------------------+
 *	|          |                                  | Im_SHDR_Get_Axi()                                   |
 *	|          +---------+--------+-------+-------+-----------------------------------------------------+
 *	|          | axires                           | Im_SHDR_Get_Axi_Response()                          |
 *	|----------+---------+--------+-------+-------+-----------------------------------------------------+
 *
 * @return      VOID
 */
VOID ct_im_shdr_err_main(CtImShdrErr* self, INT32 argc, char** argv)
{
	INT32	ret;
	UINT32	waitFactor;

	if ( strcmp(argv[1], "init") == 0 ) {
#ifdef CtImShdrTools_PC_DEBUG
		IO_SHDR.SHDRACTL1.bit.TRG = 2;
#endif
		ret = Im_SHDR_Init( FALSE );
		Ddim_Print( ("Im_SHDR_Init() ret = %d\n", ret) );
	}
	else if ( strcmp(argv[1], "open") == 0 ) {
		ret = Im_SHDR_Open( D_DDIM_USER_SEM_WAIT_FEVR );
		Ddim_Print( ("Im_SHDR_Open() ret = %d\n", ret) );
	}
	else if ( strcmp(argv[1], "close") == 0 ) {
		ret = Im_SHDR_Close();
		Ddim_Print( ("Im_SHDR_Close() ret = %d\n", ret) );
	}
	else if ( strcmp(argv[1], "ctrl") == 0 ) {
		ct_im_shdr_set_ctrl(NULL);
	}
	else if ( strcmp(argv[1], "start") == 0 ) {
#ifdef CtImShdrTools_PC_DEBUG
		IO_SHDR.SHDRACTL1.bit.TRG = 2;
#endif
		ret = Im_SHDR_Start();
		Ddim_Print( ("Im_SHDR_Start() ret = %d\n", ret) );
	}
	else if ( strcmp(argv[1], "wait") == 0 ) {
#ifdef CtImShdrTools_PC_DEBUG
		(VOID)DDIM_User_Set_Flg( FID_IM_SHDR, 1 );
#endif
		ret = Im_SHDR_Wait_End( &waitFactor, 0 );
		Ddim_Print( ("Im_SHDR_Wait_End() End ret = %d\n", ret) );

#ifdef CtImShdrTools_PC_DEBUG
		(VOID)DDIM_User_Set_Flg( FID_IM_SHDR, 2 );
#endif
		ret = Im_SHDR_Wait_End( &waitFactor, 0 );
		Ddim_Print( ("Im_SHDR_Wait_End() Stop ret = %d\n", ret) );
	}
	else if ( strcmp(argv[1], "stop") == 0 ) {
#ifdef CtImShdrTools_PC_DEBUG
		IO_SHDR.SHDRACTL1.bit.TRG = 3;
#endif
		ret = Im_SHDR_Stop();
		Ddim_Print( ("Im_SHDR_Stop() ret = %d\n", ret) );
	}
	else if ( strcmp(argv[1], "set") == 0 ) {
		if ( strcmp(argv[2], "pre") == 0 ) {
			ct_im_shdr_set_pre(NULL);
		}
		else if ( strcmp(argv[2], "fmd") == 0 ) {
			ct_im_shdr_set_fmd(NULL);
		}
		else if ( strcmp(argv[2], "pmsk") == 0 ) {
			ct_im_shdr_set_pmsk(NULL);
		}
		else if ( strcmp(argv[2], "spnr") == 0 ) {
			ct_im_shdr_set_spnr(NULL);
		}
		else if ( strcmp(argv[2], "mask") == 0 ) {
			ct_im_shdr_set_mask(NULL);
		}
		else if ( strcmp(argv[2], "blend") == 0 ) {
			ct_im_shdr_set_bld(NULL);
		}
		else if ( strcmp(argv[2], "post") == 0 ) {
			ct_im_shdr_set1_post(NULL);
		}
		else if ( strcmp(argv[2], "resize") == 0 ) {
			ct_im_shdr_set1_resize(NULL);
		}
		else if ( strcmp(argv[2], "smc") == 0 ) {
			ct_im_shdr_set1_smc(NULL);
		}
		else if ( strcmp(argv[2], "dgr") == 0 ) {
#ifdef CtImShdrTools_PC_DEBUG
			IO_SHDR.SHDRACTL1.bit.TRG = 2;
#endif
			ct_im_shdr_set1_dgr(NULL);
		}
		else if ( strcmp(argv[2], "dgg") == 0 ) {
#ifdef CtImShdrTools_PC_DEBUG
			IO_SHDR.SHDRACTL1.bit.TRG = 2;
#endif
			ct_im_shdr_set1_dgg(NULL);
		}
		else if ( strcmp(argv[2], "dgb") == 0 ) {
#ifdef CtImShdrTools_PC_DEBUG
			IO_SHDR.SHDRACTL1.bit.TRG = 2;
#endif
			ct_im_shdr_set1_dgb(NULL);
		}
		else if ( strcmp(argv[2], "dg") == 0 ) {
#ifdef CtImShdrTools_PC_DEBUG
			IO_SHDR.SHDRACTL1.bit.TRG = 2;
#endif
			ct_im_shdr_set1_dg(NULL);
		}
		else if ( strcmp(argv[2], "axi") == 0 ) {
			ct_im_shdr_set1_axi(NULL);
		}
		else {
			Ddim_Print( ("please check 2nd parameter!\n") );
			return;
		}
	}
	else if ( strcmp(argv[1], "get") == 0 ) {
		if ( strcmp(argv[2], "ctrl") == 0 ) {
			ct_im_shdr_set2_get_ctrl(NULL);
		}
		else if ( strcmp(argv[2], "pre") == 0 ) {
			ct_im_shdr_set2_get_pre(NULL);
		}
		else if ( strcmp(argv[2], "fmd") == 0 ) {
			ct_im_shdr_set2_get_fmd(NULL);
		}
		else if ( strcmp(argv[2], "pmsk") == 0 ) {
			ct_im_shdr_set2_get_pmsk(NULL);
		}
		else if ( strcmp(argv[2], "spnr") == 0 ) {
			ct_im_shdr_set2_get_spnr(NULL);
		}
		else if ( strcmp(argv[2], "mask") == 0 ) {
			ct_im_shdr_set2_get_mask(NULL);
		}
		else if ( strcmp(argv[2], "blend") == 0 ) {
			ct_im_shdr_set2_get_bld(NULL);
		}
		else if ( strcmp(argv[2], "post") == 0 ) {
			ct_im_shdr_set2_get_post(NULL);
		}
		else if ( strcmp(argv[2], "resize") == 0 ) {
			ct_im_shdr_set2_get_resize(NULL);
		}
		else if ( strcmp(argv[2], "smc") == 0 ) {
			ct_im_shdr_set2_get_smc(NULL);
		}
		else if ( strcmp(argv[2], "dgr") == 0 ) {
			ct_im_shdr_set2_get_dgr(NULL);
		}
		else if ( strcmp(argv[2], "dgg") == 0 ) {
			ct_im_shdr_set2_get_dgg(NULL);
		}
		else if ( strcmp(argv[2], "dgb") == 0 ) {
			ct_im_shdr_set2_get_dgb(NULL);
		}
		else if ( strcmp(argv[2], "dg") == 0 ) {
			ct_im_shdr_set2_get_dg(NULL);
		}
		else if ( strcmp(argv[2], "axi") == 0 ) {
			ctImShdrGetAxi();
		}
		else if ( strcmp(argv[2], "axires") == 0 ) {
			ct_im_shdr_set2_get_axires(NULL);
		}
		else {
			Ddim_Print( ("please check 2nd parameter!\n") );
			return;
		}
	}
	else if ( strcmp(argv[1], "err") == 0 ) {
		if ( strcmp(argv[2], "init") == 0 ) {
#ifdef CtImShdrTools_PC_DEBUG
			IO_SHDR.SHDRACTL1.bit.TRG = 0;
#endif
			ret = Im_SHDR_Init( FALSE );
			Ddim_Print( ("Im_SHDR_Init() ret = %d\n", ret) );
		}
		else if ( strcmp(argv[2], "open") == 0 ) {
			ret = Im_SHDR_Open( -2 );
			Ddim_Print( ("Im_SHDR_Open() ret = %d\n", ret) );
		}
		else if ( strcmp(argv[2], "close") == 0 ) {
			ret = Im_SHDR_Close();
			Ddim_Print( ("Im_SHDR_Close() ret = %d\n", ret) );
		}
		else if ( strcmp(argv[2], "ctrl") == 0 ) {
			ctImShdrErrCtrl();
		}
		else if ( strcmp(argv[2], "start") == 0 ) {
#ifdef CtImShdrTools_PC_DEBUG
			IO_SHDR.SHDRACTL1.bit.TRG = 0;
#endif
			ret = Im_SHDR_Start();
			Ddim_Print( ("Im_SHDR_Start() ret = %d\n", ret) );
		}
		else if ( strcmp(argv[2], "wait") == 0 ) {
#ifdef CtImShdrTools_PC_DEBUG
			(VOID)DDIM_User_Clr_Flg( FID_IM_SHDR, ~3 );
#endif
			ret = Im_SHDR_Wait_End( &waitFactor, 100 );
			Ddim_Print( ("Im_SHDR_Wait_End() ret = %d\n", ret) );

#ifdef CtImShdrTools_PC_DEBUG
			(VOID)DDIM_User_Set_Flg( FID_IM_SHDR, 1 );
#endif
			ret = Im_SHDR_Wait_End( NULL, 0 );
			Ddim_Print( ("Im_SHDR_Wait_End() ret = %d\n", ret) );

			ret = Im_SHDR_Wait_End( &waitFactor, -2 );
			Ddim_Print( ("Im_SHDR_Wait_End() ret = %d\n", ret) );
		}
		else if ( strcmp(argv[2], "stop") == 0 ) {
#ifdef CtImShdrTools_PC_DEBUG
			IO_SHDR.SHDRACTL1.bit.TRG = 2;
#endif
			ret = Im_SHDR_Stop();
			Ddim_Print( ("Im_SHDR_Stop() ret = %d\n", ret) );
		}
		else if ( strcmp(argv[2], "pre") == 0 ) {
			ctImShdrErrPre();
		}
		else if ( strcmp(argv[2], "fmd") == 0 ) {
			ctImShdrErrFmd();
		}
		else if ( strcmp(argv[2], "pmsk") == 0 ) {
			ctImShdrErrPmsk();
		}
		else if ( strcmp(argv[2], "spnr") == 0 ) {
			ctImShdrErrSpnr();
		}
		else if ( strcmp(argv[2], "mask") == 0 ) {
			ctImShdrErrMask();
		}
		else if ( strcmp(argv[2], "blend") == 0 ) {
			ctImShdrErrBld();
		}
		else if ( strcmp(argv[2], "post") == 0 ) {
			ctImShdrErrPost();
		}
		else if ( strcmp(argv[2], "resize") == 0 ) {
			ctImShdrErrResize();
		}
		else if ( strcmp(argv[2], "smc") == 0 ) {
			ctImShdrErrSmc();
		}
		else if ( strcmp(argv[2], "dgr") == 0 ) {
			ctImShdrErrDgr();
		}
		else if ( strcmp(argv[2], "dgg") == 0 ) {
			ctImShdrErrDgg();
		}
		else if ( strcmp(argv[2], "dgb") == 0 ) {
			ctImShdrErrDgb();
		}
		else if ( strcmp(argv[2], "dg") == 0 ) {
			ctImShdrErrDg();
		}
		else if ( strcmp(argv[2], "axi") == 0 ) {
			ctImShdrErrAxi();
		}
		else if ( strcmp(argv[2], "axires") == 0 ) {
			ctImShdrErrAxires();
		}
		else {
			Ddim_Print( ("please check 2nd parameter!\n") );
			return;
		}
	}
	// Palladium.
	else if ( strcmp(argv[1], "2") == 0 ) {

#ifdef CtImShdrTools_PC_DEBUG
		IO_SHDR.SHDRACTL1.bit.TRG = 2;
		(VOID)DDIM_User_Set_Flg( FID_IM_SHDR, 1 );
#endif

		if ( strcmp(argv[2], "1") == 0 ) {
			Ddim_Print(( "shdr test2_1 Start [3DNR w/o MC]\n" ));
			ct_im_shdr_test2_1(NULL);
			Ddim_Print(( "shdr test2_1 End\n" ));
		}
		else if ( strcmp(argv[2], "2") == 0 ) {
			Ddim_Print(( "shdr test2_2 Start [3DNR with MC]\n" ));
//			ct_im_shdr_test2_2();
			Ddim_Print(( "shdr test2_2 End\n" ));
		}
		else if ( strcmp(argv[2], "3") == 0 ) {
			Ddim_Print(( "shdr test2_3 Start [Video-HDR w/o MC]\n" ));
			ct_im_shdr_test2_3(NULL);
			Ddim_Print(( "shdr test2_3 End\n" ));
		}
		else if ( strcmp(argv[2], "4") == 0 ) {
			Ddim_Print(( "shdr test2_4 Start [Video-HDR with MC]\n" ));
//			ct_im_shdr_test2_4();
			Ddim_Print(( "shdr test2_4 End\n" ));
		}
		else if ( strcmp(argv[2], "5") == 0 ) {
			Ddim_Print(( "shdr test2_5 Start [Bypass-YCC]\n" ));
			ct_im_shdr_test2_5(NULL);
			Ddim_Print(( "shdr test2_5 End\n" ));
		}
		else if ( strcmp(argv[2], "6") == 0 ) {
			Ddim_Print(( "shdr test2_6 Start [SHDR w/o MC]\n" ));
//			ct_im_shdr_test2_6();
			Ddim_Print(( "shdr test2_6 End\n" ));
		}
		else if ( strcmp(argv[2], "7") == 0 ) {
			Ddim_Print(( "shdr test2_7 Start [SHDR with MC]\n" ));
//			ct_im_shdr_test2_7();
			Ddim_Print(( "shdr test2_7 End\n" ));
		}
		else if ( strcmp(argv[2], "8") == 0 ) {
			Ddim_Print(( "shdr test2_8 Start [MFNR w/o MC]\n" ));
//			ct_im_shdr_test2_8();
			Ddim_Print(( "shdr test2_8 End\n" ));
		}
		else if ( strcmp(argv[2], "9") == 0 ) {
			Ddim_Print(( "shdr test2_9 Start [MFNR with MC]\n" ));
//			ct_im_shdr_test2_9();
			Ddim_Print(( "shdr test2_9 End\n" ));
		}
		else if ( strcmp(argv[2], "10") == 0 ) {
			Ddim_Print(( "shdr test2_10 Start [Force stop]\n" ));
//			ct_im_shdr_test2_10();
			Ddim_Print(( "shdr test2_10 End\n" ));
		}
		else {
			Ddim_Print( ("please check 2nd parameter!\n") );
			return;
		}
	}
	else {
		Ddim_Print( ("please check 1st parameter!\n") );
	}

	return ;
}

CtImShdrErr* ct_im_shdr_err_get(void)
{
	static CtImShdrErr* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_SHDR_ERR, sizeof(CtImShdrErrPrivate));
	}

	return self;
}
