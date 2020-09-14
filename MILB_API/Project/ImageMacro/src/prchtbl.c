/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author             chenling
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/
#include "im_pro.h"
#include "improcommon.h"
#include "prchtbl.h"
#include"improcommonlist.h"
K_TYPE_DEFINE_WITH_PRIVATE(PrchTbl, prch_tbl);
#define PRCH_TBL_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), PrchTblPrivate, PRCH_TYPE_TBL))

struct _PrchTblPrivate
{
	int a;
};
static	volatile	UCHAR	gIM_PRO_PRch_AXI_Response[D_IM_PRO_PIPE_NUM][E_IM_PRO_BLOCK_TYPE_MAX][E_IM_PRO_PWCH_MAX]	= {{{0}}};
static const T_IM_PRO_COMMON_LNR_INFO	gIM_PRO_LNR_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][D_IM_PRO_SEN_LNR_CH_NUM] = {
	// E_IM_PRO_UNIT_NUM_1
	{
		{	// SEN
			{ &IO_PRO.SEN.LNR[0],	D_IM_PRO_COMMON_STATUS_SEN_LNR0	},
			{ &IO_PRO.SEN.LNR[1],	D_IM_PRO_COMMON_STATUS_SEN_LNR1	},
			{ &IO_PRO.SEN.LNR[2],	D_IM_PRO_COMMON_STATUS_SEN_LNR2	},
			{ &IO_PRO.SEN.LNR[3],	D_IM_PRO_COMMON_STATUS_SEN_LNR3	},
		},
		{	// SRO
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
		{	// B2B
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
		{	// STAT
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
		{	// PAS
			{ &IO_PRO.PAS.LNR,	D_IM_PRO_COMMON_STATUS_PAS_LNR	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
	},
	{
		{	// SEN
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
		{	// SRO
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
		{	// B2B
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
		{	// STAT
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
		{	// PAS
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
	},
	{
		{	// SEN
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
		{	// SRO
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
		{	// B2B
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
		{	// STAT
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
		{	// PAS
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
			{ NULL,					D_IM_PRO_COMMON_STATUS_NONE	},
		},
	},
};
static const T_IM_PRO_COMMON_PRCH_INFO	gIM_PRO_PRCH_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][10] = {
	// E_IM_PRO_UNIT_NUM_1
	{
		{	// SEN
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// SRO
			{ &IO_PRO.IMG_PIPE[0].SRO.PRCH[0],	D_IM_PRO_COMMON_STATUS_SRO1_PRCH0	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PRCH[1],	D_IM_PRO_COMMON_STATUS_SRO1_PRCH1	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PRCH[2],	D_IM_PRO_COMMON_STATUS_SRO1_PRCH2	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PRCH[3],	D_IM_PRO_COMMON_STATUS_SRO1_PRCH3	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PRCH[4],	D_IM_PRO_COMMON_STATUS_SRO1_PRCH4	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PRCH[5],	D_IM_PRO_COMMON_STATUS_SRO1_PRCH5	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PRCH[6],	D_IM_PRO_COMMON_STATUS_SRO1_PRCH6	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PRCH[7],	D_IM_PRO_COMMON_STATUS_SRO1_PRCH7	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PRCH[8],	D_IM_PRO_COMMON_STATUS_SRO1_PRCH8	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PRCH[9],	D_IM_PRO_COMMON_STATUS_SRO1_PRCH9	},
		},
		{	// B2B
			{ &IO_PRO.IMG_PIPE[0].B2B.PRCH[0],	D_IM_PRO_COMMON_STATUS_B2B1_PRCH0	},
			{ &IO_PRO.IMG_PIPE[0].B2B.PRCH[1],	D_IM_PRO_COMMON_STATUS_B2B1_PRCH1	},
			{ &IO_PRO.IMG_PIPE[0].B2B.PRCH[2],	D_IM_PRO_COMMON_STATUS_B2B1_PRCH2	},
			{ &IO_PRO.IMG_PIPE[0].B2B.PRCH[3],	D_IM_PRO_COMMON_STATUS_B2B1_PRCH3	},
			{ &IO_PRO.IMG_PIPE[0].B2B.PRCH[4],	D_IM_PRO_COMMON_STATUS_B2B1_PRCH4	},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// STAT
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// PAS
			{ &IO_PRO.PAS.PRCH0,				D_IM_PRO_COMMON_STATUS_PAS_PRCH0	},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
	},
	{
		{	// SEN
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// SRO
			{ &IO_PRO.IMG_PIPE[1].SRO.PRCH[0],	D_IM_PRO_COMMON_STATUS_SRO2_PRCH0	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PRCH[1],	D_IM_PRO_COMMON_STATUS_SRO2_PRCH1	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PRCH[2],	D_IM_PRO_COMMON_STATUS_SRO2_PRCH2	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PRCH[3],	D_IM_PRO_COMMON_STATUS_SRO2_PRCH3	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PRCH[4],	D_IM_PRO_COMMON_STATUS_SRO2_PRCH4	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PRCH[5],	D_IM_PRO_COMMON_STATUS_SRO2_PRCH5	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PRCH[6],	D_IM_PRO_COMMON_STATUS_SRO2_PRCH6	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PRCH[7],	D_IM_PRO_COMMON_STATUS_SRO2_PRCH7	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PRCH[8],	D_IM_PRO_COMMON_STATUS_SRO2_PRCH8	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PRCH[9],	D_IM_PRO_COMMON_STATUS_SRO2_PRCH9	},
		},
		{	// B2B
			{ &IO_PRO.IMG_PIPE[1].B2B.PRCH[0],	D_IM_PRO_COMMON_STATUS_B2B2_PRCH0	},
			{ &IO_PRO.IMG_PIPE[1].B2B.PRCH[1],	D_IM_PRO_COMMON_STATUS_B2B2_PRCH1	},
			{ &IO_PRO.IMG_PIPE[1].B2B.PRCH[2],	D_IM_PRO_COMMON_STATUS_B2B2_PRCH2	},
			{ &IO_PRO.IMG_PIPE[1].B2B.PRCH[3],	D_IM_PRO_COMMON_STATUS_B2B2_PRCH3	},
			{ &IO_PRO.IMG_PIPE[1].B2B.PRCH[4],	D_IM_PRO_COMMON_STATUS_B2B2_PRCH4	},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// STAT
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// PAS
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
	},
	{
		{	// SEN
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// SRO
			{ &IO_PRO.IMG_PIPE[2].SRO.PRCH[0],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PRCH[1],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PRCH[2],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PRCH[3],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PRCH[4],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PRCH[5],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PRCH[6],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PRCH[7],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PRCH[8],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PRCH[9],	D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// B2B
			{ &IO_PRO.IMG_PIPE[2].B2B.PRCH[0],	D_IM_PRO_COMMON_STATUS_B2B2_PRCH0	},
			{ &IO_PRO.IMG_PIPE[2].B2B.PRCH[1],	D_IM_PRO_COMMON_STATUS_B2B2_PRCH1	},
			{ &IO_PRO.IMG_PIPE[2].B2B.PRCH[2],	D_IM_PRO_COMMON_STATUS_B2B2_PRCH2	},
			{ &IO_PRO.IMG_PIPE[2].B2B.PRCH[3],	D_IM_PRO_COMMON_STATUS_B2B2_PRCH3	},
			{ &IO_PRO.IMG_PIPE[2].B2B.PRCH[4],	D_IM_PRO_COMMON_STATUS_B2B2_PRCH4	},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// STAT
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// PAS
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
	},
};
static void prch_tbl_constructor(PrchTbl *self)
{
	PrchTblPrivate *priv = PRCH_TBL_GET_PRIVATE(self);
	priv-> a = 0;
}

static void prch_tbl_destructor(PrchTbl *self)
{
	PrchTblPrivate *priv = PRCH_TBL_GET_PRIVATE(self);
	priv-> a = 0;
}
INT32 Im_PRO_PRch_Get_AXI_Response( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PRCH ch, UCHAR* axi_response )
{
#ifdef CO_PARAM_CHECK
	if( axi_response == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Get_AXI_Response. error. axi_response=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Get_AXI_Response. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*axi_response = gIM_PRO_PRch_AXI_Response[unit_no][block_type][ch];

	return D_DDIM_OK;
}

VOID im_pro_comm_set_prch_axi_response( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, UCHAR axi_resp )
{
	gIM_PRO_PRch_AXI_Response[unit_no][block_type][ch] = axi_resp;
}

INT32 Im_PRO_PRch_Start( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PRCH ch )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Start. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PRCHTRG.bit.PRCHTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_set_start_status( gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].status, 0 );
	return D_DDIM_OK;
}

INT32 Im_PRO_PRch_Stop( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PRCH ch, UCHAR force )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Stop. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	if (force == 0){
		gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PRCHTRG.bit.PRCHTRG = D_IM_PRO_TRG_FRAME_STOP;	// stop
	}
	else{
		gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PRCHTRG.bit.PRCHTRG = D_IM_PRO_TRG_FORCE_STOP;	// force stop
	}
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_set_stop_status( gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].status, 0 );
	return D_DDIM_OK;
}

VOID im_pro_comm_get_prch_reg_info( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PRCH ch, const T_IM_PRO_COMMON_PRCH_INFO** prch_info )
{
	*prch_info = &gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch];
}

INT32 Im_PRO_PRch_Set_Area( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PRCH ch, T_IM_PRO_PRCH_AREA* pr_area )
{
#ifdef CO_PARAM_CHECK
	if( pr_area == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Set_Area. error. pr_area=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Set_Area. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PRLSIZE.bit.PRLSIZE	= pr_area->global_width;
	gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PRHSIZE.bit.PRHSIZE	= pr_area->width;
	gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PRVSIZE.bit.PRVSIZE	= pr_area->height;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

INT32 Im_PRO_PRch_Ctrl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PRCH ch, T_IM_PRO_PRCH_CTRL* pr_ctrl )
{
#ifdef CO_PARAM_CHECK
	if( pr_ctrl == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Ctrl. error. pr_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Ctrl. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PRCHCTL.bit.PRBMD	= pr_ctrl->trans_mode;
	gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PRCHCTL.bit.PRLV		= pr_ctrl->req_threshold;
	gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PRCHRS.bit.PRS		= pr_ctrl->trans_to;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

INT32 Im_PRO_PRch_Ctrl_Axi( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PRCH ch, T_IM_PRO_AXI_CTRL* axi_ctrl )
{
#ifdef CO_PARAM_CHECK
	if( axi_ctrl == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Ctrl_Axi. error. axi_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Ctrl_Axi. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if ( axi_ctrl->cache_type > D_IM_PRO_PRCH_ARCACHE_MAX ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Ctrl_Axi. error. PWch cache type value over (%d)\n", axi_ctrl->cache_type));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if ( axi_ctrl->protect_type > D_IM_PRO_PRCH_ARPROT_MAX ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Ctrl_Axi. error. PWch protect type value over (%d)\n", axi_ctrl->protect_type));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PRAXCTL.bit.ARCACHE	= axi_ctrl->cache_type;
	gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PRAXCTL.bit.ARPROT	= axi_ctrl->protect_type;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

INT32 Im_PRO_PRch_Set_Addr( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PRCH ch, ULONG pr_addr )
{
#ifdef CO_PARAM_CHECK
	if( pr_addr == 0 ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Set_Addr. error. pr_addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PRch_Set_Addr. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PRSA.bit.PRSA	= pr_addr;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

INT32 Im_PRO_LNR_Start( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_LNR_CH ch )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_LNR_Start. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRTRG.bit.LNRTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );

	im_pro_common_set_start_status( gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].status, 0 );

	return D_DDIM_OK;
}

INT32 Im_PRO_LNR_Stop( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_LNR_CH ch, UCHAR force )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_LNR_Stop. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	if (force == 0){
		gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRTRG.bit.LNRTRG = D_IM_PRO_TRG_FRAME_STOP;		// stop
	}
	else{
		gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRTRG.bit.LNRTRG = D_IM_PRO_TRG_FORCE_STOP;		// force stop
	}
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );

	im_pro_common_set_stop_status( gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].status, 0 );

	return D_DDIM_OK;
}

INT32 Im_PRO_LNR_Ctrl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_LNR_CH ch, T_IM_PRO_LNR_CTRL* lnr_ctrl )
{
#ifdef CO_PARAM_CHECK
	if( lnr_ctrl == NULL ) {
		Ddim_Assertion(("I:Im_PRO_LNR_Ctrl. error. lnr_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_LNR_Stop. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBR.LNRBR1.bit.LNRBR_1			= lnr_ctrl->lnr_br[0];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBR.LNRBR1.bit.LNRBR_2			= lnr_ctrl->lnr_br[1];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBR.LNRBR2.bit.LNRBR_3			= lnr_ctrl->lnr_br[2];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBR.LNRBR2.bit.LNRBR_4			= lnr_ctrl->lnr_br[3];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBR.LNRBR3.bit.LNRBR_5			= lnr_ctrl->lnr_br[4];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBR.LNRBR3.bit.LNRBR_6			= lnr_ctrl->lnr_br[5];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBR.LNRBR4.bit.LNRBR_7			= lnr_ctrl->lnr_br[6];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCR.LNRINCR1.bit.LNRINCR_0	= lnr_ctrl->lnr_incr[0];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCR.LNRINCR1.bit.LNRINCR_1	= lnr_ctrl->lnr_incr[1];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCR.LNRINCR2.bit.LNRINCR_2	= lnr_ctrl->lnr_incr[2];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCR.LNRINCR2.bit.LNRINCR_3	= lnr_ctrl->lnr_incr[3];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCR.LNRINCR3.bit.LNRINCR_4	= lnr_ctrl->lnr_incr[4];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCR.LNRINCR3.bit.LNRINCR_5	= lnr_ctrl->lnr_incr[5];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCR.LNRINCR4.bit.LNRINCR_6	= lnr_ctrl->lnr_incr[6];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCR.LNRINCR4.bit.LNRINCR_7	= lnr_ctrl->lnr_incr[7];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSR.LNROFSR1.bit.LNROFSR_0	= lnr_ctrl->lnr_ofsr[0];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSR.LNROFSR1.bit.LNROFSR_1	= lnr_ctrl->lnr_ofsr[1];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSR.LNROFSR2.bit.LNROFSR_2	= lnr_ctrl->lnr_ofsr[2];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSR.LNROFSR2.bit.LNROFSR_3	= lnr_ctrl->lnr_ofsr[3];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSR.LNROFSR3.bit.LNROFSR_4	= lnr_ctrl->lnr_ofsr[4];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSR.LNROFSR3.bit.LNROFSR_5	= lnr_ctrl->lnr_ofsr[5];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSR.LNROFSR4.bit.LNROFSR_6	= lnr_ctrl->lnr_ofsr[6];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSR.LNROFSR4.bit.LNROFSR_7	= lnr_ctrl->lnr_ofsr[7];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGR.LNRBGR1.bit.LNRBGR_1		= lnr_ctrl->lnr_bgr[0];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGR.LNRBGR1.bit.LNRBGR_2		= lnr_ctrl->lnr_bgr[1];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGR.LNRBGR2.bit.LNRBGR_3		= lnr_ctrl->lnr_bgr[2];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGR.LNRBGR2.bit.LNRBGR_4		= lnr_ctrl->lnr_bgr[3];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGR.LNRBGR3.bit.LNRBGR_5		= lnr_ctrl->lnr_bgr[4];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGR.LNRBGR3.bit.LNRBGR_6		= lnr_ctrl->lnr_bgr[5];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGR.LNRBGR4.bit.LNRBGR_7		= lnr_ctrl->lnr_bgr[6];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGR.LNRINCGR1.bit.LNRINCGR_0	= lnr_ctrl->lnr_incgr[0];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGR.LNRINCGR1.bit.LNRINCGR_1	= lnr_ctrl->lnr_incgr[1];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGR.LNRINCGR2.bit.LNRINCGR_2	= lnr_ctrl->lnr_incgr[2];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGR.LNRINCGR2.bit.LNRINCGR_3	= lnr_ctrl->lnr_incgr[3];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGR.LNRINCGR3.bit.LNRINCGR_4	= lnr_ctrl->lnr_incgr[4];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGR.LNRINCGR3.bit.LNRINCGR_5	= lnr_ctrl->lnr_incgr[5];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGR.LNRINCGR4.bit.LNRINCGR_6	= lnr_ctrl->lnr_incgr[6];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGR.LNRINCGR4.bit.LNRINCGR_7	= lnr_ctrl->lnr_incgr[7];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGR.LNROFSGR1.bit.LNROFSGR_0	= lnr_ctrl->lnr_ofsgr[0];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGR.LNROFSGR1.bit.LNROFSGR_1	= lnr_ctrl->lnr_ofsgr[1];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGR.LNROFSGR2.bit.LNROFSGR_2	= lnr_ctrl->lnr_ofsgr[2];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGR.LNROFSGR2.bit.LNROFSGR_3	= lnr_ctrl->lnr_ofsgr[3];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGR.LNROFSGR3.bit.LNROFSGR_4	= lnr_ctrl->lnr_ofsgr[4];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGR.LNROFSGR3.bit.LNROFSGR_5	= lnr_ctrl->lnr_ofsgr[5];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGR.LNROFSGR4.bit.LNROFSGR_6	= lnr_ctrl->lnr_ofsgr[6];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGR.LNROFSGR4.bit.LNROFSGR_7	= lnr_ctrl->lnr_ofsgr[7];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGB.LNRBGB1.bit.LNRBGB_1		= lnr_ctrl->lnr_bgb[0];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGB.LNRBGB1.bit.LNRBGB_2		= lnr_ctrl->lnr_bgb[1];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGB.LNRBGB2.bit.LNRBGB_3		= lnr_ctrl->lnr_bgb[2];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGB.LNRBGB2.bit.LNRBGB_4		= lnr_ctrl->lnr_bgb[3];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGB.LNRBGB3.bit.LNRBGB_5		= lnr_ctrl->lnr_bgb[4];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGB.LNRBGB3.bit.LNRBGB_6		= lnr_ctrl->lnr_bgb[5];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBGB.LNRBGB4.bit.LNRBGB_7		= lnr_ctrl->lnr_bgb[6];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGB.LNRINCGB1.bit.LNRINCGB_0	= lnr_ctrl->lnr_incgb[0];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGB.LNRINCGB1.bit.LNRINCGB_1	= lnr_ctrl->lnr_incgb[1];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGB.LNRINCGB2.bit.LNRINCGB_2	= lnr_ctrl->lnr_incgb[2];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGB.LNRINCGB2.bit.LNRINCGB_3	= lnr_ctrl->lnr_incgb[3];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGB.LNRINCGB3.bit.LNRINCGB_4	= lnr_ctrl->lnr_incgb[4];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGB.LNRINCGB3.bit.LNRINCGB_5	= lnr_ctrl->lnr_incgb[5];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGB.LNRINCGB4.bit.LNRINCGB_6	= lnr_ctrl->lnr_incgb[6];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCGB.LNRINCGB4.bit.LNRINCGB_7	= lnr_ctrl->lnr_incgb[7];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGB.LNROFSGB1.bit.LNROFSGB_0	= lnr_ctrl->lnr_ofsgb[0];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGB.LNROFSGB1.bit.LNROFSGB_1	= lnr_ctrl->lnr_ofsgb[1];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGB.LNROFSGB2.bit.LNROFSGB_2	= lnr_ctrl->lnr_ofsgb[2];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGB.LNROFSGB2.bit.LNROFSGB_3	= lnr_ctrl->lnr_ofsgb[3];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGB.LNROFSGB3.bit.LNROFSGB_4	= lnr_ctrl->lnr_ofsgb[4];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGB.LNROFSGB3.bit.LNROFSGB_5	= lnr_ctrl->lnr_ofsgb[5];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGB.LNROFSGB4.bit.LNROFSGB_6	= lnr_ctrl->lnr_ofsgb[6];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSGB.LNROFSGB4.bit.LNROFSGB_7	= lnr_ctrl->lnr_ofsgb[7];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBB.LNRBB1.bit.LNRBB_1			= lnr_ctrl->lnr_bb[0];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBB.LNRBB1.bit.LNRBB_2			= lnr_ctrl->lnr_bb[1];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBB.LNRBB2.bit.LNRBB_3			= lnr_ctrl->lnr_bb[2];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBB.LNRBB2.bit.LNRBB_4			= lnr_ctrl->lnr_bb[3];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBB.LNRBB3.bit.LNRBB_5			= lnr_ctrl->lnr_bb[4];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBB.LNRBB3.bit.LNRBB_6			= lnr_ctrl->lnr_bb[5];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRBB.LNRBB4.bit.LNRBB_7			= lnr_ctrl->lnr_bb[6];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCB.LNRINCB1.bit.LNRINCB_0	= lnr_ctrl->lnr_incb[0];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCB.LNRINCB1.bit.LNRINCB_1	= lnr_ctrl->lnr_incb[1];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCB.LNRINCB2.bit.LNRINCB_2	= lnr_ctrl->lnr_incb[2];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCB.LNRINCB2.bit.LNRINCB_3	= lnr_ctrl->lnr_incb[3];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCB.LNRINCB3.bit.LNRINCB_4	= lnr_ctrl->lnr_incb[4];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCB.LNRINCB3.bit.LNRINCB_5	= lnr_ctrl->lnr_incb[5];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCB.LNRINCB4.bit.LNRINCB_6	= lnr_ctrl->lnr_incb[6];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNRINCB.LNRINCB4.bit.LNRINCB_7	= lnr_ctrl->lnr_incb[7];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSB.LNROFSB1.bit.LNROFSB_0	= lnr_ctrl->lnr_ofsb[0];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSB.LNROFSB1.bit.LNROFSB_1	= lnr_ctrl->lnr_ofsb[1];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSB.LNROFSB2.bit.LNROFSB_2	= lnr_ctrl->lnr_ofsb[2];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSB.LNROFSB2.bit.LNROFSB_3	= lnr_ctrl->lnr_ofsb[3];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSB.LNROFSB3.bit.LNROFSB_4	= lnr_ctrl->lnr_ofsb[4];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSB.LNROFSB3.bit.LNROFSB_5	= lnr_ctrl->lnr_ofsb[5];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSB.LNROFSB4.bit.LNROFSB_6	= lnr_ctrl->lnr_ofsb[6];
	gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->LNROFSB.LNROFSB4.bit.LNROFSB_7	= lnr_ctrl->lnr_ofsb[7];
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

VOID im_pro_comm_get_lnr_reg_info( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_LNR_CH ch, const T_IM_PRO_COMMON_LNR_INFO** lnr_info )
{
	*lnr_info = &gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch];
}

INT32 paek_and(PrchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,ULONG reg_addr)
{
	if( gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == 0 ) {
					}
					else {
						reg_addr = (ULONG)gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr - im_pro_get_block_top_addr( unit_no, block_type );
						Ddim_Print(( "gIM_PRO_PRCH_Reg_Ptr_Tbl unit_no:%u block_type:%u ch:%u REL_reg_addr(0x%08lx) ABS_reg_addr(0x%08lx) status(%u)\n",
																																		unit_no,
																																		block_type,
																																		ch,
																																		(ULONG)reg_addr,
																																		(ULONG)gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr,
																																		gIM_PRO_PRCH_Reg_Ptr_Tbl[unit_no][block_type][ch].status
						));
					}
	return 0;
}

INT32 paek_bnd(PrchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,ULONG reg_addr)
{
	if( gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == 0 ) {
						reg_addr = 0;
					}
					else {
						reg_addr = (ULONG)gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr - im_pro_get_block_top_addr( unit_no, block_type );
						Ddim_Print(( "gIM_PRO_LNR_Reg_Ptr_Tbl unit_no:%u block_type:%u ch:%u REL_reg_addr(0x%08lx) ABS_reg_addr(0x%08lx) status(%u)\n",
																																		unit_no,
																																		block_type,
																																		ch,
																																		(ULONG)reg_addr,
																																		(ULONG)gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr,
																																		gIM_PRO_LNR_Reg_Ptr_Tbl[unit_no][block_type][ch].status
						));
					}
	return 0;
}

PrchTbl* prch_tbl_get(void)
{
	static PrchTbl* self = NULL;
	if(!self){
		self = k_object_new(PRCH_TYPE_TBL);
	}
	return self;
}

PrchTbl *prch_tbl_new(void)
{
	PrchTbl* self = k_object_new_with_private(PRCH_TYPE_TBL,sizeof(PrchTblPrivate));
	return self;
}
