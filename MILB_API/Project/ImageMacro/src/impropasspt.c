/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-01
*@author              :杨金波
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/

#include<stdint.h>
#include<string.h>
#include<math.h>

#include <klib.h>
#include"impropasspt.h"
#include "im_pro_common.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImproPasspt, impro_passpt);
#define IMPRO_PASSPT_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproPassptPrivate, IMPRO_TYPE_PASSPT));


/*宏定义区域*/
/* SEN clock status ON	*/
#define ImproPaspt_SET_START_STATUS(st, ch) 	(gIM_PAS_START_Status[((st) >> 28) & 0xf]\
																						|=  (((st) & 0x0fffffff) << (ch)))
/* SEN clock status OFF	*/
#define ImproPaspt_SET_STOP_STATUS(st, ch)		(gIM_PAS_START_Status[((st) >> 28) & 0xf]\
																						&= ~(((st) & 0x0fffffff) << (ch)))
/* SPT			*/
#define	ImproPaspt_D_IM_PAS_STATUS_SPT			(0x00000000UL)&(1<<0)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/*私有结构体定义区域*/
struct _ImproPassptPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
static const TimproRdmaSptShdTblAddr S_G_IM_PRO_SPT_SHD_TBL_ADDR[D_IM_PRO_PAS_SPT_TBL_CNT] =
{
	{ 0x29814000 },
	{ 0x29814400 },
};


/*DECLS（私有函数声明区域）*/


/*
*对象初始化区域
*/
static void impro_passpt_constructor(ImproPasspt *self)
{
	ImproPassptPrivate *priv = IMPRO_PASSPT_GET_PRIVATE(self);
}

/*
*内存释放区域
*/
static void impro_passpt_destructor(ImproPasspt *self)
{
	ImproPassptPrivate *priv = IMPRO_PASSPT_GET_PRIVATE(self);
}


/*IMPL*/


/*PUBLIC*/
/**
SPT macro start
@retval		D_DDIM_OK				: Processing OK
@retval		D_IM_PRO_MACRO_BUSY_NG	: PWCH not running NG
*/
INT32 impro_passpt_start( VOID )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	ioPro.pas.spt.spttrg.bit.spttrg = D_IM_PRO_TRG_START;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	ImproPaspt_SET_START_STATUS(ImproPaspt_D_IM_PAS_STATUS_SPT, 0);

	return D_DDIM_OK;
}

/**
SPT macro stop
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: PWCH not stopped NG
*/
INT32 impro_passpt_stop( UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	if (force == 0){
		// frame stop
		ioPro.pas.spt.SPTTRG.bit.SPTTRG = D_IM_PRO_TRG_FRAME_STOP;
	}
	else{
		// force stop
		ioPro.pas.spt.SPTTRG.bit.SPTTRG = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	ImproPaspt_SET_STOP_STATUS(ImproPaspt_D_IM_PAS_STATUS_SPT, 0);

	return D_DDIM_OK;
}

/**
Setup of SPT control parameter.
@param[in]	sptCtrl : SPT Information @ref TimproSptCtrl
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_passpt_ctrl( TimproSptCtrl* sptCtrl )
{
#ifdef CO_PARAM_CHECK
	if (sptCtrl == NULL){
		Ddim_Assertion(("I:impro_passpt_ctrl error. sptCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproPasspt_D_IM_PRO_SPT_SPTBSH_MIN,
					ImproPasspt_D_IM_PRO_SPT_SPTBSH_MAX,
					sptCtrl->horizontalPixel, "impro_passpt_ctrl : horizontalPixel" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproPasspt_D_IM_PRO_SPT_SPTBSV_MIN,
					ImproPasspt_D_IM_PRO_SPT_SPTBSV_MAX,
					sptCtrl->verticalPixel, "impro_passpt_ctrl : verticalPixel" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproPasspt_D_IM_PRO_SPT_SPTBDE_MIN,
			ImproPasspt_D_IM_PRO_SPT_SPTBDE_MAX,sptCtrl->InverseExponent,
			"impro_passpt_ctrl : InverseExponent" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproPasspt_D_IM_PRO_SPT_SPTV_MIN,
			ImproPasspt_D_IM_PRO_SPT_SPTV_MAX,sptCtrl->posY, "impro_passpt_ctrl : posY" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproPasspt_D_IM_PRO_SPT_SPTH_MIN,
					ImproPasspt_D_IM_PRO_SPT_SPTH_MAX, sptCtrl->posX, "impro_passpt_ctrl : posX" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproPasspt_D_IM_PRO_SPT_SPTVBC_MIN,
					ImproPasspt_D_IM_PRO_SPT_SPTVBC_MAX, sptCtrl->vBlockSize,
					"impro_passpt_ctrl : vBlockSize" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproPasspt_D_IM_PRO_SPT_SPTHBC_MIN,
					ImproPasspt_D_IM_PRO_SPT_SPTHBC_MAX, sptCtrl->hBlockSize,
					"impro_passpt_ctrl : hBlockSize" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	ioPro.pas.spt.spttbl.bit.spttbl	= sptCtrl->tableSel;
	ioPro.pas.spt.sptbs.bit.sptbsh		= sptCtrl->horizontalPixel;
	ioPro.pas.spt.sptbs.bit.sptbsv		= sptCtrl->verticalPixel;
	ioPro.pas.spt.sptbd.bit.sptbdm		= sptCtrl->InverseBase;
	ioPro.pas.spt.sptbd.bit.sptbde		= sptCtrl->InverseExponent;
	ioPro.pas.spt.sptv.bit.sptv		= sptCtrl->posY;
	ioPro.pas.spt.spth.bit.spth		= sptCtrl->posX;
	ioPro.pas.spt.sptvbc.bit.sptvbc	= sptCtrl->vBlockSize;
	ioPro.pas.spt.spthbc.bit.spthbc	= sptCtrl->hBlockSize;
	im_pro_set_reg_signed( ioPro.pas.spt.sptclp, union IoSptclp, sptclph, sptCtrl->upperClipValue );
	im_pro_set_reg_signed( ioPro.pas.spt.sptclp, union IoSptclp, sptclpl, sptCtrl->lowerClipValue );
	im_pro_set_reg_signed( ioPro.pas.spt.sptnopv, union IoSptnopv, sptnopv, sptCtrl->correctionThroughVal );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );	// Dd_Top_Start_Clock

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of SPT.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_passpt_set_paen( UCHAR paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( ioPro.pas.spt.SPTTRG.bit.SPTTRG != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:impro_passpt_set_paen. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	ioPro.pas.spt.SPTPAEN.bit.PAEN	= paenTrg;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	return D_DDIM_OK;
}

/**
shading compensation table is registered.
@param[in]	tblSel : table select.
@param[in]	shdTbl		: Shading table info
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@note		None
*/
INT32 impro_passpt_set_table( E_IM_PRO_SPT_TBL_SEL tblSel, TimproSptTable* shdTbl )
{
	UCHAR* pDstTable;

#ifdef CO_PARAM_CHECK
	if (shdTbl == NULL){
		Ddim_Assertion(("I:impro_passpt_set_table error. sptCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( ( shdTbl->pshdTbl == NULL ) || ( shdTbl->size == 0 ) ) {
		Ddim_Assertion(("I:impro_passpt_set_table error. shdTbl->pshdTbl=%lx shdTbl->size=%u \n",
										(ULONG)shdTbl->pshdTbl, shdTbl->size));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	if( tblSel == E_IM_PRO_SPT_TBL_SEL_SPTTBL0 ) {
		pDstTable = (UCHAR*)IO_PRO_TBL.PAS_TBL.SPTTBL0.word;
	}
	else {
		pDstTable = (UCHAR*)IO_PRO_TBL.PAS_TBL.SPTTBL1.word;
	}

	// Dd_Top_Start_Clock
	im_pro_on_hclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );
	im_pro_memcpy( pDstTable, shdTbl->pshdTbl, shdTbl->size );
	// Dd_Top_Start_Clock
	im_pro_off_hclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_PAS );

	return D_DDIM_OK;
}

/**
Get the top address of the address array of FSHD control.
@param[in]		tblSel : table select.
@param[out]		addr					: Top address of the address array of FSHD Concentric Circles Correction table.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 impro_passpt_get_rdma_addr_spt_shd_tbl( E_IM_PRO_SPT_TBL_SEL tblSel, const TimproRdmaSptShdTblAddr** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:impro_passpt_get_rdma_addr_spt_shd_tbl. error. addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &S_G_IM_PRO_SPT_SHD_TBL_ADDR[tblSel];

	return D_DDIM_OK;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproPasspt类的一个实例
 *
 */
ImproPasspt* 	impro_passpt_new()
{
	ImproPasspt* self = k_object_new_with_private(IMPRO_TYPE_PASSPT,sizeof(ImproPassptPrivate));
	ImproPassptPrivate* priv = IMPRO_PASSPT_GET_PRIVATE(self);
	
	e_warning_o(self," impro_passpt_new \n");
	return self;
}
