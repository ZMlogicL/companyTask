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
#include "pkchtbl.h"
#include"improcommonlist.h"
K_TYPE_DEFINE_WITH_PRIVATE(PkchTbl, pkch_tbl);
#define PKCH_TBL_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), PkchTblPrivate, PKCH_TYPE_TBL))

static	volatile	T_IM_PRO_MONI_RESULT	gIM_PRO_MONI_Buffer_Info[D_IM_PRO_PIPE_NUM][E_IM_PRO_BLOCK_TYPE_MAX][D_IM_PRO_SEN_MONI_CH_NUM];
static E_IM_PRO_BLOCK_TYPE im_pro_convert_pzsft_type( E_IM_PRO_PZSFT_CH ch );

static const T_IM_PRO_COMMON_MONI_INFO	gIM_PRO_MONI_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][E_IM_PRO_MONI_CH_3 + 1] = {
	// E_IM_PRO_UNIT_NUM_1
	{
		{	// SEN
			{ &IO_PRO.SEN.MONI[0],				D_IM_PRO_COMMON_STATUS_SEN_MONI0	},
			{ &IO_PRO.SEN.MONI[1],				D_IM_PRO_COMMON_STATUS_SEN_MONI1	},
			{ &IO_PRO.SEN.MONI[2],				D_IM_PRO_COMMON_STATUS_SEN_MONI2	},
			{ &IO_PRO.SEN.MONI[3],				D_IM_PRO_COMMON_STATUS_SEN_MONI3	},
		},

		{	// SRO
			{ &IO_PRO.IMG_PIPE[0].SRO.MONI0,	D_IM_PRO_COMMON_STATUS_SRO1_MONI	},
// --- REMOVE_BUZ BEGIN
#ifdef CO_USE_BUZ
			{ &IO_PRO.IMG_PIPE[0].SRO.MONI1,	D_IM_PRO_COMMON_STATUS_SRO1_MONI1	},
#endif
// --- REMOVE_BUZ END
// --- REMOVE_BUZ BEGIN
#ifndef CO_USE_BUZ
// --- REMOVE_BUZ END
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
// --- REMOVE_BUZ BEGIN
#endif
// --- REMOVE_BUZ END
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},

		{	// B2B
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
		},

		{	// PAS
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
	},
	// E_IM_PRO_UNIT_NUM_2
	{
		{	// SEN
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},

		{	// SRO
			{ &IO_PRO.IMG_PIPE[1].SRO.MONI0,	D_IM_PRO_COMMON_STATUS_SRO2_MONI	},
// --- REMOVE_BUZ BEGIN
#ifdef CO_USE_BUZ
			{ &IO_PRO.IMG_PIPE[1].SRO.MONI1,	D_IM_PRO_COMMON_STATUS_SRO1_MONI1	},
#endif
// --- REMOVE_BUZ END
// --- REMOVE_BUZ BEGIN
#ifndef CO_USE_BUZ
// --- REMOVE_BUZ END
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
// --- REMOVE_BUZ BEGIN
#endif
// --- REMOVE_BUZ END
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},

		{	// B2B
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
		},

		{	// PAS
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
	},
	// E_IM_PRO_BOTH_UNIT
	{
		{	// SEN
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},

		{	// SRO
			{ &IO_PRO.IMG_PIPE[2].SRO.MONI0,	D_IM_PRO_COMMON_STATUS_NONE	},
// --- REMOVE_BUZ BEGIN
#ifdef CO_USE_BUZ
			{ &IO_PRO.IMG_PIPE[2].SRO.MONI1,	D_IM_PRO_COMMON_STATUS_SRO1_MONI1	},
#endif
// --- REMOVE_BUZ END
// --- REMOVE_BUZ BEGIN
#ifndef CO_USE_BUZ
// --- REMOVE_BUZ END
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
// --- REMOVE_BUZ BEGIN
#endif
// --- REMOVE_BUZ END
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},

		{	// B2B
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
		},

		{	// PAS
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE			},
		},
	},
};

static const T_IM_PRO_COMMON_PG_INFO	gIM_PRO_PG_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX] = {
	// E_IM_PRO_UNIT_NUM_1
	{
		{ NULL,							D_IM_PRO_COMMON_STATUS_NONE,	{	D_IM_PRO_COMMON_STATUS_NONE }	},										// SEN
		{ &IO_PRO.IMG_PIPE[0].SRO.PG,	D_IM_PRO_COMMON_STATUS_SRO1_PG,	{	D_IM_PRO_COMMON_STATUS_SRO1_PRCH0,	D_IM_PRO_COMMON_STATUS_SRO1_PRCH1,
																			D_IM_PRO_COMMON_STATUS_SRO1_M2P0,	D_IM_PRO_COMMON_STATUS_SRO1_M2P1,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE }	},	// SRO
		{ &IO_PRO.IMG_PIPE[0].B2B.PG,	D_IM_PRO_COMMON_STATUS_B2B1_PG,	{	D_IM_PRO_COMMON_STATUS_SRO1_PRCH0,	D_IM_PRO_COMMON_STATUS_SRO1_PRCH1,
																			D_IM_PRO_COMMON_STATUS_B2B1_M2P0,	D_IM_PRO_COMMON_STATUS_B2B1_M2P1,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE }	},	// B2B
		{ NULL,							D_IM_PRO_COMMON_STATUS_NONE,	{	D_IM_PRO_COMMON_STATUS_NONE }	},										// STAT
		{ &IO_PRO.PAS.PG,				D_IM_PRO_COMMON_STATUS_PAS_PG,	{	D_IM_PRO_COMMON_STATUS_PAS_PRCH0,	D_IM_PRO_COMMON_STATUS_PAS_M2P0,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE }	},	// PAS
	},
	// E_IM_PRO_UNIT_NUM_2
	{
		{ NULL,							D_IM_PRO_COMMON_STATUS_NONE,	{	D_IM_PRO_COMMON_STATUS_NONE }	},										// SEN
		{ &IO_PRO.IMG_PIPE[1].SRO.PG,	D_IM_PRO_COMMON_STATUS_SRO2_PG,	{	D_IM_PRO_COMMON_STATUS_SRO2_PRCH0,	D_IM_PRO_COMMON_STATUS_SRO2_PRCH1,
																			D_IM_PRO_COMMON_STATUS_SRO2_M2P0,	D_IM_PRO_COMMON_STATUS_SRO2_M2P1,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE }	},	// SRO
		{ &IO_PRO.IMG_PIPE[1].B2B.PG,	D_IM_PRO_COMMON_STATUS_B2B2_PG,	{	D_IM_PRO_COMMON_STATUS_SRO2_PRCH0,	D_IM_PRO_COMMON_STATUS_SRO2_PRCH1,
																			D_IM_PRO_COMMON_STATUS_B2B2_M2P0,	D_IM_PRO_COMMON_STATUS_B2B2_M2P1,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE }	},	// B2B
		{ NULL,							D_IM_PRO_COMMON_STATUS_NONE,	{	D_IM_PRO_COMMON_STATUS_NONE }	},										// STAT
		{ NULL,							D_IM_PRO_COMMON_STATUS_NONE,	{	D_IM_PRO_COMMON_STATUS_NONE }	},										// PAS
	},
	// E_IM_PRO_BOTH_UNIT
	{
		{ NULL,							D_IM_PRO_COMMON_STATUS_NONE,	{	D_IM_PRO_COMMON_STATUS_NONE }	},										// SEN
		{ &IO_PRO.IMG_PIPE[2].SRO.PG,	D_IM_PRO_COMMON_STATUS_NONE,	{	D_IM_PRO_COMMON_STATUS_SRO1_PRCH0,	D_IM_PRO_COMMON_STATUS_SRO1_PRCH1,
																			D_IM_PRO_COMMON_STATUS_SRO1_M2P0,	D_IM_PRO_COMMON_STATUS_SRO1_M2P1,
																			D_IM_PRO_COMMON_STATUS_SRO2_PRCH0,	D_IM_PRO_COMMON_STATUS_SRO2_PRCH1,
																			D_IM_PRO_COMMON_STATUS_SRO2_M2P0,	D_IM_PRO_COMMON_STATUS_SRO2_M2P1}},	// SRO
		{ &IO_PRO.IMG_PIPE[2].B2B.PG,	D_IM_PRO_COMMON_STATUS_NONE,	{	D_IM_PRO_COMMON_STATUS_B2B1_PRCH0,	D_IM_PRO_COMMON_STATUS_B2B1_PRCH1,
																			D_IM_PRO_COMMON_STATUS_B2B1_M2P0,	D_IM_PRO_COMMON_STATUS_B2B1_M2P1,
																			D_IM_PRO_COMMON_STATUS_B2B2_PRCH0,	D_IM_PRO_COMMON_STATUS_B2B2_PRCH1,
																			D_IM_PRO_COMMON_STATUS_B2B2_M2P0,	D_IM_PRO_COMMON_STATUS_B2B2_M2P1}},	// B2B
		{ NULL,							D_IM_PRO_COMMON_STATUS_NONE,	{	D_IM_PRO_COMMON_STATUS_NONE }	},										// STAT
		{ NULL,							D_IM_PRO_COMMON_STATUS_NONE,	{	D_IM_PRO_COMMON_STATUS_NONE }	},										// PAS
	},
};

static  const T_IM_PRO_COMMON_PGAIN_INFO	gIM_PRO_PGAIN_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][D_IM_PRO_PGAIN_CNT] = {
	// E_IM_PRO_UNIT_NUM_1
	{
		{	// SEN
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
		},

		{	// SRO
			{ &IO_PRO.IMG_PIPE[0].SRO.PGAIN0,	D_IM_PRO_COMMON_STATUS_SRO1_PGAIN },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
		},

		{	// B2B
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ &IO_PRO.IMG_PIPE[0].B2B.PGAIN1,	D_IM_PRO_COMMON_STATUS_B2B1_PGAIN1 },
			{ &IO_PRO.IMG_PIPE[0].B2B.PGAIN2,	D_IM_PRO_COMMON_STATUS_B2B1_PGAIN2 },
		},

		{	// STAT
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
		},

		{	// PAS
			{ &IO_PRO.PAS.PGAIN,				D_IM_PRO_COMMON_STATUS_PAS_PGAIN },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
		},
	},
	// E_IM_PRO_UNIT_NUM_2
	{
		{	// SEN
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
		},

		{	// SRO
			{ &IO_PRO.IMG_PIPE[1].SRO.PGAIN0,	D_IM_PRO_COMMON_STATUS_SRO2_PGAIN },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
		},

		{	// B2B
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ &IO_PRO.IMG_PIPE[1].B2B.PGAIN1,	D_IM_PRO_COMMON_STATUS_B2B2_PGAIN1 },
			{ &IO_PRO.IMG_PIPE[1].B2B.PGAIN2,	D_IM_PRO_COMMON_STATUS_B2B2_PGAIN2 },
		},

		{	// STAT
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
		},

		{	// PAS
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
		},
	},
	// E_IM_PRO_BOTH_UNIT
	{
		{	// SEN
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
		},

		{	// SRO
			{ &IO_PRO.IMG_PIPE[2].SRO.PGAIN0,	D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
		},

		{	// B2B
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ &IO_PRO.IMG_PIPE[2].B2B.PGAIN1,	D_IM_PRO_COMMON_STATUS_NONE },
			{ &IO_PRO.IMG_PIPE[2].B2B.PGAIN2,	D_IM_PRO_COMMON_STATUS_NONE },
		},

		{	// STAT
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
		},

		{	// PAS
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
			{ NULL,								D_IM_PRO_COMMON_STATUS_NONE },
		},
	},
};

static const T_IM_PRO_COMMON_PZSFT_INFO	gIM_PRO_PZSFT_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_PZSFT_CH_MAX] = {
	// E_IM_PRO_UNIT_NUM_1
	{
		{ &IO_PRO.IMG_PIPE[0].SRO.PZSFTB1,	D_IM_PRO_COMMON_STATUS_SRO1_PZSFTB1		},
		{ &IO_PRO.IMG_PIPE[0].SRO.PZSFTB2,	D_IM_PRO_COMMON_STATUS_SRO1_PZSFTB2		},
		{ &IO_PRO.IMG_PIPE[0].SRO.PZSFTC1,	D_IM_PRO_COMMON_STATUS_SRO1_PZSFTC1		},
		{ &IO_PRO.IMG_PIPE[0].SRO.PZSFTC2,	D_IM_PRO_COMMON_STATUS_SRO1_PZSFTC2		},
		{ &IO_PRO.IMG_PIPE[0].B2B.PZSFTA1,	D_IM_PRO_COMMON_STATUS_B2B1_PZSFTA1		},
		{ &IO_PRO.IMG_PIPE[0].B2B.PZSFTA2,	D_IM_PRO_COMMON_STATUS_B2B1_PZSFTA2		},
		{ &IO_PRO.IMG_PIPE[0].B2B.PZSFTA2A,	D_IM_PRO_COMMON_STATUS_B2B1_PZSFTA2A	},
	},
	// E_IM_PRO_UNIT_NUM_2
	{
		{ &IO_PRO.IMG_PIPE[1].SRO.PZSFTB1,	D_IM_PRO_COMMON_STATUS_SRO2_PZSFTB1		},
		{ &IO_PRO.IMG_PIPE[1].SRO.PZSFTB2,  D_IM_PRO_COMMON_STATUS_SRO2_PZSFTB2		},
		{ &IO_PRO.IMG_PIPE[1].SRO.PZSFTC1,  D_IM_PRO_COMMON_STATUS_SRO2_PZSFTC1		},
		{ &IO_PRO.IMG_PIPE[1].SRO.PZSFTC2,  D_IM_PRO_COMMON_STATUS_SRO2_PZSFTC2		},
		{ &IO_PRO.IMG_PIPE[1].B2B.PZSFTA1,	D_IM_PRO_COMMON_STATUS_B2B2_PZSFTA1		},
		{ &IO_PRO.IMG_PIPE[1].B2B.PZSFTA2,	D_IM_PRO_COMMON_STATUS_B2B2_PZSFTA2		},
		{ &IO_PRO.IMG_PIPE[1].B2B.PZSFTA2A,	D_IM_PRO_COMMON_STATUS_B2B2_PZSFTA2A	},
	},
	// E_IM_PRO_BOTH_UNIT
	{
		{ &IO_PRO.IMG_PIPE[2].SRO.PZSFTB1,	D_IM_PRO_COMMON_STATUS_NONE				},
		{ &IO_PRO.IMG_PIPE[2].SRO.PZSFTB2,	D_IM_PRO_COMMON_STATUS_NONE				},
		{ &IO_PRO.IMG_PIPE[2].SRO.PZSFTC1,	D_IM_PRO_COMMON_STATUS_NONE				},
		{ &IO_PRO.IMG_PIPE[2].SRO.PZSFTC2,	D_IM_PRO_COMMON_STATUS_NONE				},
		{ &IO_PRO.IMG_PIPE[2].B2B.PZSFTA1,	D_IM_PRO_COMMON_STATUS_NONE				},
		{ &IO_PRO.IMG_PIPE[2].B2B.PZSFTA2,	D_IM_PRO_COMMON_STATUS_NONE				},
		{ &IO_PRO.IMG_PIPE[2].B2B.PZSFTA2A,	D_IM_PRO_COMMON_STATUS_NONE				},
	},
};

struct _PkchTblPrivate
{
	int a;
};


static void pkch_tbl_constructor(PkchTbl *self)
{
	PkchTblPrivate *priv = PKCH_TBL_GET_PRIVATE(self);
	priv-> a = 0;
}

static void pkch_tbl_destructor(PkchTbl *self)
{
	PkchTblPrivate *priv = PKCH_TBL_GET_PRIVATE(self);
	priv-> a = 0;
}

static E_IM_PRO_BLOCK_TYPE im_pro_convert_pzsft_type( E_IM_PRO_PZSFT_CH ch )
{
	E_IM_PRO_CLK_BLOCK_TYPE type;

	switch( ch ) {
		case E_IM_PRO_PZSFT_CH_B1:
		case E_IM_PRO_PZSFT_CH_B2:
		case E_IM_PRO_PZSFT_CH_C1:
		case E_IM_PRO_PZSFT_CH_C2:
			type = E_IM_PRO_BLOCK_TYPE_SRO;
			break;

		//case E_IM_PRO_PZSFT_CH_A1,
		//case E_IM_PRO_PZSFT_CH_A2,
		//case E_IM_PRO_PZSFT_CH_A2A
		default:
			type = E_IM_PRO_BLOCK_TYPE_B2B;
			break;
	}
	return type;
}

INT32 Im_PRO_MONI_Ctrl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_MONI_CH ch, T_IM_PRO_MONI_CTRL* moni_ctrl )
{
#ifdef CO_PARAM_CHECK
	if( moni_ctrl == NULL ) {
		Ddim_Assertion(("I:Im_PRO_MONI_Ctrl. error. moni_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_MONI_Ctrl. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONICTL.bit.MONIMD				= moni_ctrl->monitor_mode;
	gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIHDEXP.bit.MONIHDEXP			= moni_ctrl->hd_cnt_expect_val;
	gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIEPFEXP.bit.MONIEPFEXP		= moni_ctrl->valid_pixel_expect_cnt_in_1frame;
	gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIBLLMINEXP.bit.MONIBLLMINEXP	= moni_ctrl->lower_limit_except_h_blank;
	gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIBLLMAXEXP.bit.MONIBLLMAXEXP	= moni_ctrl->upper_limit_except_h_blank;
	gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIADHD.bit.MONIADHD			= moni_ctrl->additional_hd_cnt;
	gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIADHW.bit.MONIADHW			= moni_ctrl->additional_hd_gap_cnt;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

VOID im_pro_comm_get_moni_reg_info( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_MONI_CH ch, const T_IM_PRO_COMMON_MONI_INFO** moni_info )
{
#ifdef CO_PARAM_CHECK
	if( moni_info == NULL ) {
		Ddim_Assertion(("I:im_pro_comm_get_moni_reg_info error. ch:%d moni_info=NULL\n", ch));
		return;
	}
#endif
	*moni_info = &gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch];
}

INT32 Im_PRO_MONI_Start( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_MONI_CH ch )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_MONI_Start. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONITRG.bit.MONITRG	= D_IM_PRO_TRG_START;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_set_start_status( gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].status, 0 );
	return D_DDIM_OK;
}

INT32 Im_PRO_MONI_Stop( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_MONI_CH ch, UCHAR force )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_MONI_Stop. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	if (force == 0){
		gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONITRG.bit.MONITRG = D_IM_PRO_TRG_FRAME_STOP;	// frame stop
	}
	else{
		gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONITRG.bit.MONITRG = D_IM_PRO_TRG_FORCE_STOP;	// force stop
	}
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_set_stop_status( gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].status, 0 );
	return D_DDIM_OK;
}

VOID im_pro_comm_update_moni_result( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_MONI_CH ch )
{
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].vd_cnt					= gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIVD.bit.MONIVD;
	gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].hd_cnt					= gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIHD.bit.MONIHD;
	gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].pixel_cnt_in_1frame		= gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIEPF.bit.MONIEPF;
	gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].min_val_h_valid_pixel_cnt	= gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIEPLMIN.bit.MONIEPLMIN;
	gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].max_val_h_valid_pixel_cnt	= gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIEPLMAX.bit.MONIEPLMAX;
	gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].intra_frame_blank_cycle	= gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIBLF.bit.MONIBLF;
	gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].min_val_h_blank_cycle		= gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIBLLMIN.bit.MONIBLLMIN;
	gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].max_val_h_blank_cycle		= gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->MONIBLLMAX.bit.MONIBLLMAX;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
}

INT32 Im_PRO_MONI_Get_Monitor_Count( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_MONI_CH ch, T_IM_PRO_MONI_RESULT* moni_result )
{
#ifdef CO_PARAM_CHECK
	if( moni_result == NULL ) {
		Ddim_Assertion(("I:Im_PRO_MONI_Get_Monitor_Count. error. moni_result=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_MONI_Get_Monitor_Count. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	moni_result->vd_cnt						= gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].vd_cnt;
	moni_result->hd_cnt						= gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].hd_cnt;
	moni_result->pixel_cnt_in_1frame		= gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].pixel_cnt_in_1frame;
	moni_result->min_val_h_valid_pixel_cnt	= gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].min_val_h_valid_pixel_cnt;
	moni_result->max_val_h_valid_pixel_cnt	= gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].max_val_h_valid_pixel_cnt;
	moni_result->intra_frame_blank_cycle	= gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].intra_frame_blank_cycle;
	moni_result->min_val_h_blank_cycle		= gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].min_val_h_blank_cycle;
	moni_result->max_val_h_blank_cycle		= gIM_PRO_MONI_Buffer_Info[unit_no][block_type][ch].max_val_h_blank_cycle;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );

	return D_DDIM_OK;
}

INT32 Im_PRO_PG_Start( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PG_Start. invalid ch parameters. unit:%d block:%d \n", unit_no, block_type));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	for( UCHAR loopcnt = 0; loopcnt < D_IM_PRO_COMMON_PG_PRE_STARTED_STATUS_MAX; loopcnt++ ) {
		if(gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].pre_started_status[loopcnt] != D_IM_PRO_COMMON_STATUS_NONE) {
			if (im_pro_common_get_start_status(gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].pre_started_status[loopcnt], 0) == FALSE){
				Ddim_Print(("I:Im_PRO_PG_Start. macro not running error. Pre-Started Macro status:(%u) \n", gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].pre_started_status[loopcnt]));
				return D_IM_PRO_MACRO_BUSY_NG;
			}
		}
	}

	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr->PGTRG.bit.PGTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );

	im_pro_common_set_start_status( gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].status, 0 );

	return D_DDIM_OK;
}

INT32 Im_PRO_PG_Stop( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PG_Stop. invalid ch parameters. unit:%d block:%d \n", unit_no, block_type));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	for( UCHAR loopcnt = 0; loopcnt < D_IM_PRO_COMMON_PG_PRE_STARTED_STATUS_MAX; loopcnt++ ) {
		if(gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].pre_started_status[loopcnt] != D_IM_PRO_COMMON_STATUS_NONE) {
			if (im_pro_common_get_start_status(gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].pre_started_status[loopcnt], 0) != FALSE){
				Ddim_Print(("I:Im_PRO_PG_Stop. macro not stopped error. Pre-Stopped Macro status:(%u) \n", gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].pre_started_status[loopcnt]));
				return D_IM_PRO_MACRO_BUSY_NG;
			}
		}
	}
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr->PGTRG.bit.PGTRG = D_IM_PRO_TRG_FRAME_STOP;	// frame stop
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_set_stop_status( gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].status, 0 );
	return D_DDIM_OK;
}

INT32 Im_PRO_PG_Ctrl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, T_IM_PRO_PG_CTRL* pg_ctrl)
{
#ifdef CO_PARAM_CHECK
	if( pg_ctrl == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PG_Ctrl. error. pg_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PG_Ctrl. invalid ch parameters. unit:%d block:%d \n", unit_no, block_type));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_PG_PGHW_MIN, D_IM_PRO_PG_PGHW_MAX, pg_ctrl->input_img_width, "Im_PRO_PG_Ctrl : input_img_width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_PG_PGVW_MIN, D_IM_PRO_PG_PGVW_MAX, pg_ctrl->input_img_lines, "Im_PRO_PG_Ctrl : input_img_lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_PG_PGVBLNK_MIN, D_IM_PRO_PG_PGVBLNK_MAX, pg_ctrl->vertical_blanking, "Im_PRO_PG_Ctrl : vertical_blanking" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_PG_PGHBLNK_MIN, D_IM_PRO_PG_PGHBLNK_MAX, pg_ctrl->horizontal_blanking, "Im_PRO_PG_Ctrl : horizontal_blanking" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_PG_PGVHBLNK_MIN, D_IM_PRO_PG_PGVHBLNK_MAX, pg_ctrl->start_blanking, "Im_PRO_PG_Ctrl : start_blanking" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr->PGCTL.bit.PGMD				= pg_ctrl->mode;
	gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr->PGVW.bit.PGVW				= pg_ctrl->input_img_lines;
	gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr->PGHW.bit.PGHW				= pg_ctrl->input_img_width;
	gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr->PGVBLNK.bit.PGVBLNK		= pg_ctrl->vertical_blanking;
	gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr->PGHBLNK.bit.PGHBLNK		= pg_ctrl->horizontal_blanking;
	gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr->PGVDHDBLNK.bit.PGVHBLNK	= pg_ctrl->start_blanking;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

VOID im_pro_comm_get_pg_reg_info( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, const T_IM_PRO_COMMON_PG_INFO** pg_info )
{
	*pg_info = &gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type];
}

INT32 Im_PRO_PGAIN_Start( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PGAIN_SELECT select )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PGAIN_Start. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, select));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr->PGAINTRG.bit.PGAINTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );

	im_pro_common_set_start_status( gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].status, 0 );

	return D_DDIM_OK;
}

INT32 Im_PRO_PGAIN_Stop( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PGAIN_SELECT select, UCHAR force )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PGAIN_Stop. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, select));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	if (force == 0){
		gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr->PGAINTRG.bit.PGAINTRG = D_IM_PRO_TRG_FRAME_STOP;	// frame stop
	}
	else{
		gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr->PGAINTRG.bit.PGAINTRG = D_IM_PRO_TRG_FORCE_STOP;	// force stop
	}
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );

	im_pro_common_set_stop_status( gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].status, 0 );

	return D_DDIM_OK;
}

INT32 Im_PRO_PGAIN_Ctrl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PGAIN_SELECT select, T_IM_PRO_PGAIN_CTRL* pgain_ctrl )
{
#ifdef CO_PARAM_CHECK
	if( pgain_ctrl == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PGAIN_Ctrl. error. pgain_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PGAIN_Ctrl. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, select));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr->PGAINR.bit.PGAINR	= pgain_ctrl->R;
	gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr->PGAINGR.bit.PGAINGR	= pgain_ctrl->Gr;
	gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr->PGAINGB.bit.PGAINGB	= pgain_ctrl->Gb;
	gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr->PGAINB.bit.PGAINB	= pgain_ctrl->B;
	im_pro_set_reg_signed( gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr->POFSR, union io_pofsr, POFSR, pgain_ctrl->R_offset );
	im_pro_set_reg_signed( gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr->POFSGR, union io_pofsgr, POFSGR, pgain_ctrl->Gr_offset );
	im_pro_set_reg_signed( gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr->POFSGB, union io_pofsgb, POFSGB, pgain_ctrl->Gb_offset );
	im_pro_set_reg_signed( gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr->POFSB, union io_pofsb, POFSB, pgain_ctrl->B_offset );
	gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][select].reg_ptr->PGAINDP.bit.PGAINDP	= pgain_ctrl->decimal_point_position;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

VOID im_pro_comm_get_pgain_reg_info( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PGAIN_SELECT ch, const T_IM_PRO_COMMON_PGAIN_INFO** pgain_info )
{
	*pgain_info = &gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][ch];
}

INT32 Im_PRO_PZSFT_Start( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_PZSFT_CH ch )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PZSFT_Start. invalid ch parameters. unit:%d ch:%d \n", unit_no, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_common_fig_im_pro_on_pclk( unit_no,  im_pro_convert_clk_type(im_pro_convert_pzsft_type( ch )) );
	gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][ch].reg_ptr->PZSFTTRG.bit.PZSFTTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type(im_pro_convert_pzsft_type( ch )) );

	im_pro_common_set_start_status( gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][ch].status, 0 );

	return D_DDIM_OK;
}

INT32 Im_PRO_PZSFT_Stop( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_PZSFT_CH ch, UCHAR force )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PZSFT_Stop. invalid ch parameters. unit:%d ch:%d \n", unit_no, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type(im_pro_convert_pzsft_type( ch )) );
	if (force == 0){
		gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][ch].reg_ptr->PZSFTTRG.bit.PZSFTTRG = D_IM_PRO_TRG_FRAME_STOP;	// frame stop
	}
	else{
		gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][ch].reg_ptr->PZSFTTRG.bit.PZSFTTRG = D_IM_PRO_TRG_FORCE_STOP;	// force stop
	}
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type(im_pro_convert_pzsft_type( ch )) );

	im_pro_common_set_stop_status( gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][ch].status, 0 );

	return D_DDIM_OK;
}

INT32 Im_PRO_PZSFT_Ctrl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_PZSFT_CH ch, T_IM_PRO_PZSFT_CTRL* pzsft_ctrl )
{
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PZSFT_Ctrl. invalid ch parameters. unit:%d ch:%d \n", unit_no, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type(im_pro_convert_pzsft_type( ch )) );
	im_pro_set_reg_signed( gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][ch].reg_ptr->PZOFST, union io_pzofst, PZOFST, pzsft_ctrl->offset_shift );
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type(im_pro_convert_pzsft_type( ch )) );

	return D_DDIM_OK;
}

VOID im_pro_comm_get_pzsft_reg_info( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_PZSFT_CH ch, const T_IM_PRO_COMMON_PZSFT_INFO** pzsft_info )
{
	*pzsft_info = &gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][ch];
}

INT32 paek_cnd(PkchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,ULONG reg_addr)
{
	if( gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == 0 ) {
					}
					else {
						reg_addr = (ULONG)gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr - im_pro_get_block_top_addr( unit_no, block_type );
						Ddim_Print(( "gIM_PRO_MONI_Reg_Ptr_Tbl unit_no:%u block_type:%u ch:%u REL_reg_addr(0x%08lx) ABS_reg_addr(0x%08lx) status(%u)\n",
																																		unit_no,
																																		block_type,
																																		ch,
																																		(ULONG)reg_addr,
																																		(ULONG)gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr,
																																		gIM_PRO_MONI_Reg_Ptr_Tbl[unit_no][block_type][ch].status
						));
					}
	return 0;
}

INT32 paek_dnd(PkchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,ULONG reg_addr)
{
	if( gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr == 0 ) {
					}
					else {
						reg_addr = (ULONG)gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr - im_pro_get_block_top_addr( unit_no, block_type );
						Ddim_Print(( "gIM_PRO_PG_Reg_Ptr_Tbl unit_no:%u block_type:%u REL_reg_addr(0x%08lx) ABS_reg_addr(0x%08lx) status(%u)\n",
																																		unit_no,
																																		block_type,
																																		(ULONG)reg_addr,
																																		(ULONG)gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr,
																																		gIM_PRO_PG_Reg_Ptr_Tbl[unit_no][block_type].status
						));
					}
	return 0;
}

INT32 paek_end(PkchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,ULONG reg_addr)
{
	if( gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == 0 ) {
					}
					else {
						reg_addr = (ULONG)gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr - im_pro_get_block_top_addr( unit_no, block_type );
						Ddim_Print(( "gIM_PRO_PGAIN_Reg_Ptr_Tbl unit_no:%u block_type:%u ch:%u REL_reg_addr(0x%08lx) ABS_reg_addr(0x%08lx) status(%u)\n",
																																		unit_no,
																																		block_type,
																																		ch,
																																		(ULONG)reg_addr,
																																		(ULONG)gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr,
																																		gIM_PRO_PGAIN_Reg_Ptr_Tbl[unit_no][block_type][ch].status
						));
					}
	return 0;
}

INT32 paek_fnd(PkchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,ULONG reg_addr)
{
	if( gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr == 0 ) {
					}
					else {
						reg_addr = (ULONG)gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr - im_pro_get_block_top_addr( unit_no, block_type );
						Ddim_Print(( "gIM_PRO_PZSFT_Reg_Ptr_Tbl unit_no:%u block_type:%u REL_reg_addr(0x%08lx) ABS_reg_addr(0x%08lx) status(%u)\n",
																																		unit_no,
																																		block_type,
																																		(ULONG)reg_addr,
																																		(ULONG)gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][block_type].reg_ptr,
																																		gIM_PRO_PZSFT_Reg_Ptr_Tbl[unit_no][block_type].status
						));
					}
	return 0;
}

PkchTbl* pkch_tbl_get(void)
{
	static PkchTbl* self = NULL;
	if(!self){
		self = k_object_new(PKCH_TYPE_TBL);
	}
	return self;
}
PkchTbl *pkch_tbl_new(void)
{
	PkchTbl* self = k_object_new_with_private(PKCH_TYPE_TBL,sizeof(PkchTblPrivate));
	return self;
}
