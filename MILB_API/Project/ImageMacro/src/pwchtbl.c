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
#include "improcommonlist.h"
#include "im_pro.h"
#include "improcommon.h"
#include "pwchtbl.h"

K_TYPE_DEFINE_WITH_PRIVATE(PwchTbl, pwch_tbl);
#define PWCH_TBL_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), PwchTblPrivate, PWCH_TYPE_TBL))

struct _PwchTblPrivate
{
	int a;
};

static const T_IM_PRO_COMMON_PWCH_INFO	gIM_PRO_PWCH_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][E_IM_PRO_PWCH_MAX] = {
	// E_IM_PRO_UNIT_NUM_1
	{
		{	// SEN
			{ &IO_PRO.SEN.PWCH[0],				D_IM_PRO_COMMON_STATUS_SEN_PWCH0	},
			{ &IO_PRO.SEN.PWCH[1],				D_IM_PRO_COMMON_STATUS_SEN_PWCH1	},
			{ &IO_PRO.SEN.PWCH[2],				D_IM_PRO_COMMON_STATUS_SEN_PWCH2	},
			{ &IO_PRO.SEN.PWCH[3],				D_IM_PRO_COMMON_STATUS_SEN_PWCH3	},
			{ &IO_PRO.SEN.PWCH[4],				D_IM_PRO_COMMON_STATUS_SEN_PWCH4	},
			{ &IO_PRO.SEN.PWCH[5],				D_IM_PRO_COMMON_STATUS_SEN_PWCH5	},
			{ &IO_PRO.SEN.PWCH[6],				D_IM_PRO_COMMON_STATUS_SEN_PWCH6	},
			{ &IO_PRO.SEN.PWCH[7],				D_IM_PRO_COMMON_STATUS_SEN_PWCH7	},
		},
		{	// SRO
			{ &IO_PRO.IMG_PIPE[0].SRO.PWCH[0],	D_IM_PRO_COMMON_STATUS_SRO1_PWCH0	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PWCH[1],	D_IM_PRO_COMMON_STATUS_SRO1_PWCH1	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PWCH[2],	D_IM_PRO_COMMON_STATUS_SRO1_PWCH2	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PWCH[3],	D_IM_PRO_COMMON_STATUS_SRO1_PWCH3	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PWCH[4],	D_IM_PRO_COMMON_STATUS_SRO1_PWCH4	},
			{ &IO_PRO.IMG_PIPE[0].SRO.PWCH[5],	D_IM_PRO_COMMON_STATUS_SRO1_PWCH5	},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// B2B
			{ &IO_PRO.IMG_PIPE[0].B2B.PWCH[0],	D_IM_PRO_COMMON_STATUS_B2B1_PWCH0	},
			{ &IO_PRO.IMG_PIPE[0].B2B.PWCH[1],	D_IM_PRO_COMMON_STATUS_B2B1_PWCH1	},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// STAT
			{ &IO_PRO.STAT.PWCH[0],				D_IM_PRO_COMMON_STATUS_STAT_PWCH0	},
			{ &IO_PRO.STAT.PWCH[1], 			D_IM_PRO_COMMON_STATUS_STAT_PWCH1	},
			{ &IO_PRO.STAT.PWCH[2], 			D_IM_PRO_COMMON_STATUS_STAT_PWCH2	},
			{ &IO_PRO.STAT.PWCH[3], 			D_IM_PRO_COMMON_STATUS_STAT_PWCH3	},
			{ &IO_PRO.STAT.PWCH[4], 			D_IM_PRO_COMMON_STATUS_STAT_PWCH4	},
			{ &IO_PRO.STAT.PWCH[5], 			D_IM_PRO_COMMON_STATUS_STAT_PWCH5	},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// PAS
			{ &IO_PRO.PAS.PWCH0,				D_IM_PRO_COMMON_STATUS_PAS_PWCH0	},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
	},
	{
		{	// SEN
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// SRO
			{ &IO_PRO.IMG_PIPE[1].SRO.PWCH[0],	D_IM_PRO_COMMON_STATUS_SRO2_PWCH0	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PWCH[1],	D_IM_PRO_COMMON_STATUS_SRO2_PWCH1	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PWCH[2],	D_IM_PRO_COMMON_STATUS_SRO2_PWCH2	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PWCH[3],	D_IM_PRO_COMMON_STATUS_SRO2_PWCH3	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PWCH[4],	D_IM_PRO_COMMON_STATUS_SRO2_PWCH4	},
			{ &IO_PRO.IMG_PIPE[1].SRO.PWCH[5],	D_IM_PRO_COMMON_STATUS_SRO2_PWCH5	},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// B2B
			{ &IO_PRO.IMG_PIPE[1].B2B.PWCH[0],	D_IM_PRO_COMMON_STATUS_B2B2_PWCH0	},
			{ &IO_PRO.IMG_PIPE[1].B2B.PWCH[1],	D_IM_PRO_COMMON_STATUS_B2B2_PWCH1	},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// STAT
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// PAS
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
	},
	{
		{	// SEN
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// SRO
			{ &IO_PRO.IMG_PIPE[2].SRO.PWCH[0],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PWCH[1],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PWCH[2],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PWCH[3],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PWCH[4],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].SRO.PWCH[5],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// B2B
			{ &IO_PRO.IMG_PIPE[2].B2B.PWCH[0],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ &IO_PRO.IMG_PIPE[2].B2B.PWCH[1],	D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// STAT
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
		{	// PAS
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
			{ NULL, 							D_IM_PRO_COMMON_STATUS_NONE			},
		},
	},
};

static const T_IM_PRO_COMMON_M2P_INFO	gIM_PRO_M2P_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][10] = {
	// E_IM_PRO_UNIT_NUM_1
	{
		{	// SEN
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// SRO
			{ &IO_PRO.IMG_PIPE[0].SRO.M2P[0],	&IO_PRO_TBL.SRO1_TBL.M2P0DKNTBL,	D_IM_PRO_COMMON_STATUS_SRO1_M2P0,	{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH0,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].SRO.M2P[1],	&IO_PRO_TBL.SRO1_TBL.M2P1DKNTBL,	D_IM_PRO_COMMON_STATUS_SRO1_M2P1,	{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH1,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].SRO.M2P[2],	NULL,								D_IM_PRO_COMMON_STATUS_SRO1_M2P2,	{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH2,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].SRO.M2P[3],	NULL,								D_IM_PRO_COMMON_STATUS_SRO1_M2P3,	{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH3,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].SRO.M2P[4],	NULL,								D_IM_PRO_COMMON_STATUS_SRO1_M2P6,	{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH6,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].SRO.M2P[5],	NULL,								D_IM_PRO_COMMON_STATUS_SRO1_M2P7,	{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH7,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].SRO.M2P[6],	&IO_PRO_TBL.SRO1_TBL.M2P6DKNTBL,	D_IM_PRO_COMMON_STATUS_SRO1_M2P8,	{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH8,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].SRO.M2P[7],	&IO_PRO_TBL.SRO1_TBL.M2P7DKNTBL,	D_IM_PRO_COMMON_STATUS_SRO1_M2P9,	{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH9,	D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// B2B
			{ &IO_PRO.IMG_PIPE[0].B2B.M2P[0],	&IO_PRO_TBL.B2B1_TBL.M2P0DKNTBL,	D_IM_PRO_COMMON_STATUS_B2B1_M2P0,	{ D_IM_PRO_COMMON_STATUS_B2B1_PRCH0,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].B2B.M2P[1],	&IO_PRO_TBL.B2B1_TBL.M2P1DKNTBL,	D_IM_PRO_COMMON_STATUS_B2B1_M2P1,	{ D_IM_PRO_COMMON_STATUS_B2B1_PRCH1,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].B2B.M2P[2],	NULL,								D_IM_PRO_COMMON_STATUS_B2B1_M2P2,	{ D_IM_PRO_COMMON_STATUS_B2B1_PRCH2,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].B2B.M2P[3],	NULL,								D_IM_PRO_COMMON_STATUS_B2B1_M2P3,	{ D_IM_PRO_COMMON_STATUS_B2B1_PRCH3,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// STAT
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// PAS
			{ &IO_PRO.PAS.M2P0,					NULL,								D_IM_PRO_COMMON_STATUS_PAS_M2P0,	{ D_IM_PRO_COMMON_STATUS_PAS_PRCH0,		D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
	},
	{
		{	// SEN
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// SRO
			{ &IO_PRO.IMG_PIPE[1].SRO.M2P[0],	&IO_PRO_TBL.SRO2_TBL.M2P0DKNTBL,	D_IM_PRO_COMMON_STATUS_SRO2_M2P0,	{ D_IM_PRO_COMMON_STATUS_SRO2_PRCH0,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].SRO.M2P[1],	&IO_PRO_TBL.SRO2_TBL.M2P1DKNTBL,	D_IM_PRO_COMMON_STATUS_SRO2_M2P1,	{ D_IM_PRO_COMMON_STATUS_SRO2_PRCH1,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].SRO.M2P[2],	NULL,								D_IM_PRO_COMMON_STATUS_SRO2_M2P2,	{ D_IM_PRO_COMMON_STATUS_SRO2_PRCH2,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].SRO.M2P[3],	NULL,								D_IM_PRO_COMMON_STATUS_SRO2_M2P3,	{ D_IM_PRO_COMMON_STATUS_SRO2_PRCH3,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].SRO.M2P[4],	NULL,								D_IM_PRO_COMMON_STATUS_SRO2_M2P6,	{ D_IM_PRO_COMMON_STATUS_SRO2_PRCH6,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].SRO.M2P[5],	NULL,								D_IM_PRO_COMMON_STATUS_SRO2_M2P7,	{ D_IM_PRO_COMMON_STATUS_SRO2_PRCH7,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].SRO.M2P[6],	&IO_PRO_TBL.SRO2_TBL.M2P6DKNTBL,	D_IM_PRO_COMMON_STATUS_SRO2_M2P8,	{ D_IM_PRO_COMMON_STATUS_SRO2_PRCH8,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].SRO.M2P[7],	&IO_PRO_TBL.SRO2_TBL.M2P7DKNTBL,	D_IM_PRO_COMMON_STATUS_SRO2_M2P9,	{ D_IM_PRO_COMMON_STATUS_SRO2_PRCH9,	D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// B2B
			{ &IO_PRO.IMG_PIPE[1].B2B.M2P[0],	&IO_PRO_TBL.B2B2_TBL.M2P0DKNTBL,	D_IM_PRO_COMMON_STATUS_B2B2_M2P0,	{ D_IM_PRO_COMMON_STATUS_B2B2_PRCH0,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].B2B.M2P[1],	&IO_PRO_TBL.B2B2_TBL.M2P1DKNTBL,	D_IM_PRO_COMMON_STATUS_B2B2_M2P1,	{ D_IM_PRO_COMMON_STATUS_B2B2_PRCH1,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].B2B.M2P[2],	NULL,								D_IM_PRO_COMMON_STATUS_B2B2_M2P2,	{ D_IM_PRO_COMMON_STATUS_B2B2_PRCH2,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].B2B.M2P[3],	NULL,								D_IM_PRO_COMMON_STATUS_B2B2_M2P3,	{ D_IM_PRO_COMMON_STATUS_B2B2_PRCH3,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// STAT
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// PAS
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
	},
	{
		{	// SEN
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// SRO
			{ &IO_PRO.IMG_PIPE[2].SRO.M2P[0],	&IO_PRO_TBL.SRO3_TBL.M2P0DKNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH0,	D_IM_PRO_COMMON_STATUS_SRO2_PRCH0}	},
			{ &IO_PRO.IMG_PIPE[2].SRO.M2P[1],	&IO_PRO_TBL.SRO3_TBL.M2P1DKNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH1,	D_IM_PRO_COMMON_STATUS_SRO2_PRCH1}	},
			{ &IO_PRO.IMG_PIPE[2].SRO.M2P[2],	NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH2,	D_IM_PRO_COMMON_STATUS_SRO2_PRCH2}	},
			{ &IO_PRO.IMG_PIPE[2].SRO.M2P[3],	NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH3,	D_IM_PRO_COMMON_STATUS_SRO2_PRCH3}	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE		}	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE		}	},
			{ &IO_PRO.IMG_PIPE[2].SRO.M2P[4],	NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH6,	D_IM_PRO_COMMON_STATUS_SRO2_PRCH6}	},
			{ &IO_PRO.IMG_PIPE[2].SRO.M2P[5],	NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH7,	D_IM_PRO_COMMON_STATUS_SRO2_PRCH7}	},
			{ &IO_PRO.IMG_PIPE[2].SRO.M2P[6],	&IO_PRO_TBL.SRO3_TBL.M2P6DKNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH8,	D_IM_PRO_COMMON_STATUS_SRO2_PRCH8}	},
			{ &IO_PRO.IMG_PIPE[2].SRO.M2P[7],	&IO_PRO_TBL.SRO3_TBL.M2P7DKNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PRCH9,	D_IM_PRO_COMMON_STATUS_SRO2_PRCH9}	},
		},
		{	// B2B
			{ &IO_PRO.IMG_PIPE[2].B2B.M2P[0],	&IO_PRO_TBL.B2B3_TBL.M2P0DKNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_B2B1_PRCH0,	D_IM_PRO_COMMON_STATUS_B2B2_PRCH0}	},
			{ &IO_PRO.IMG_PIPE[2].B2B.M2P[1],	&IO_PRO_TBL.B2B3_TBL.M2P1DKNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_B2B1_PRCH1,	D_IM_PRO_COMMON_STATUS_B2B2_PRCH1}	},
			{ &IO_PRO.IMG_PIPE[2].B2B.M2P[2],	NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_B2B1_PRCH2,	D_IM_PRO_COMMON_STATUS_B2B2_PRCH2}	},
			{ &IO_PRO.IMG_PIPE[2].B2B.M2P[3],	NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_B2B1_PRCH3,	D_IM_PRO_COMMON_STATUS_B2B2_PRCH3}	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// STAT
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// PAS
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,								D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
	},
};

static void pwch_tbl_constructor(PwchTbl *self)
{
	PwchTblPrivate *priv = PWCH_TBL_GET_PRIVATE(self);
	priv-> a = 0;
}

static void pwch_tbl_destructor(PwchTbl *self)
{
	PwchTblPrivate *priv = PWCH_TBL_GET_PRIVATE(self);
	priv-> a = 0;
}

VOID im_pro_comm_get_m2p_reg_info( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_M2P_CH ch, const T_IM_PRO_COMMON_M2P_INFO** m2p_info )
{
	*m2p_info = &gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch];
}

INT32 Im_PRO_M2P_Ctrl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_M2P_CH ch, T_IM_PRO_M2P_CTRL* m2p_ctrl )
{
#ifdef CO_PARAM_CHECK
	if( m2p_ctrl == NULL ) {
		Ddim_Assertion(("I:Im_PRO_M2P_Ctrl. error. m2p_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_M2P_Start. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_M2P_M2PBT_MIN, D_IM_PRO_M2P_M2PBT_MAX, m2p_ctrl->valid_bit_count, "Im_PRO_M2P_Ctrl : valid_bit_count" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( E_IM_PRO_M2P_DEKNEE_DIS, ( E_IM_PRO_M2P_DEKNEE_MAX - 1 ), m2p_ctrl->deknee_enable, "Im_PRO_M2P_Ctrl : deknee_enable" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PCTL.bit.M2PTYP		= m2p_ctrl->data_type;
	if( ( ( block_type == E_IM_PRO_BLOCK_TYPE_SRO ) && ( ( ch == E_IM_PRO_M2P_2 ) || ( ch == E_IM_PRO_M2P_3 ) || ( ch == E_IM_PRO_M2P_8 ) || ( ch == E_IM_PRO_M2P_9 ) ) ) ||
		( ( block_type == E_IM_PRO_BLOCK_TYPE_B2B ) && ( ( ch == E_IM_PRO_M2P_2 ) || ( ch == E_IM_PRO_M2P_3 ) ) ) ) {
		// In the M2P Light macro configuration case, always disable deknee.
		gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PCTL.bit.MDKNMD		= E_IM_PRO_M2P_DEKNEE_DIS;
	}
	else {
		gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PCTL.bit.MDKNMD		= m2p_ctrl->deknee_enable;
	}
	gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PBSFT.bit.M2PBSFT	= m2p_ctrl->shift_bit;
	gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PBSFT.bit.M2PBMD	= m2p_ctrl->shift_sat;
	gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PBSFT.bit.M2PBLR	= m2p_ctrl->bit_shift;
	gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PBSFT.bit.M2PBT		= m2p_ctrl->valid_bit_count;
	im_pro_set_reg_signed( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2POFS, union io_m2pofs, M2POFS, m2p_ctrl->shift_value );
	im_pro_set_reg_signed( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PCLIP, union io_m2pclip, M2PCLIPLW, m2p_ctrl->lower_limit_clip_value );
	gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PCLIP.bit.M2PCLIPHI	= m2p_ctrl->upper_limit_clip_value;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

INT32 Im_PRO_M2P_Set_PAEN( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_M2P_CH ch, UCHAR paen_trg )
{
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_M2P_Start. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( ( paen_trg == 0 ) && ( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PTRG.bit.M2PTRG != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:Im_PRO_M2P_Start. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PPAEN.bit.MPPAEN = paen_trg;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

INT32 Im_PRO_M2P_Set_Table( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_M2P_CH ch, T_IM_PRO_M2P_TABLE* m2p_tbl )
{
#ifdef CO_PARAM_CHECK
	if( m2p_tbl == NULL ) {
		Ddim_Assertion(("I:Im_PRO_M2P_Set_Table. error. m2p_tbl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].dkntbl_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_M2P_Set_Table. error. unit:%d block:%d ch:%d dkntbl_ptr=NULL\n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PPAEN.bit.MPPAEN != 1 ) {
		Ddim_Assertion(("I:Im_PRO_M2P_Set_Table. built-in RAM access disabled error. MPPAEN == 0.\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PTRG.bit.M2PTRG != D_IM_PRO_TRG_STATUS_STOPPED ) {
		Ddim_Assertion(("I:Im_PRO_M2P_Set_Table. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	im_pro_common_fig_im_pro_on_hclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_fig_im_pro_memcpy( NULL,(void*)gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].dkntbl_ptr->hword, m2p_tbl->pm2p_tbl, ( m2p_tbl->size * sizeof(SHORT) ) );
	im_pro_off_hclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

INT32 Im_PRO_M2P_Stop( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_M2P_CH ch, UCHAR force )
{
	ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_M2P_Start. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	if (force == 0){
		gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PTRG.bit.M2PTRG	= D_IM_PRO_TRG_FRAME_STOP;		// stop
	}
	else{
		gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PTRG.bit.M2PTRG	= D_IM_PRO_TRG_FORCE_STOP;		// force stop
	}
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_set_stop_status( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].status, 0 );
	return D_DDIM_OK;
}

VOID im_pro_comm_get_pwch_reg_info( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, const T_IM_PRO_COMMON_PWCH_INFO** pwch_info )
{
	*pwch_info = &gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch];
}

INT32 Im_PRO_M2P_Start( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_M2P_CH ch )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_M2P_Start. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	for( UCHAR loopcnt = 0; loopcnt < D_IM_PRO_COMMON_M2P_PRE_STARTED_STATUS_MAX; loopcnt++ ) {
		if(gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].pre_started_status[loopcnt] != D_IM_PRO_COMMON_STATUS_NONE) {
			if (im_pro_common_get_start_status(gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].pre_started_status[loopcnt], 0) == FALSE){
				Ddim_Print(("I:Im_PRO_M2P_Start. macro not stopped error. Pre-Stopped Macro status:(%u) \n", gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].pre_started_status[loopcnt]));
				return D_IM_PRO_MACRO_BUSY_NG;
			}
		}
	}
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->M2PTRG.bit.M2PTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_set_start_status( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].status, 0 );
	return D_DDIM_OK;
}
INT32 paok_ind( PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch)
{
	if( gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
			Ddim_Assertion(("I:Im_PRO_PWch_Set_Buf_Addr. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
			return D_IM_PRO_INPUT_PARAM_ERROR;
		}
	return 0;
}

INT32 paok_and(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, T_IM_PRO_PWCH_INFO* pwch_info)
{
	gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWSA.bit.PWSA = pwch_info->buff_addr[0];
	return 0;
}

INT32 paok_bnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch)
{
	if( gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
			Ddim_Assertion(("I:Im_PRO_PWch_Get_Buf_Data. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
			return D_IM_PRO_INPUT_PARAM_ERROR;
		}
	return 0;
}

INT32 paok_cnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch)
{
	if( gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
			Ddim_Assertion(("I:Im_PRO_PWch_Update_Buf_Index. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
			return D_IM_PRO_INPUT_PARAM_ERROR;
		}
	return 0;
}

void paok_dnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch)
{

	gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWSA.bit.PWSA	= self->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].top_addr[self->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].buff_index.cur];
//		im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
}

INT32 paok_end(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, T_IM_PRO_PWCH_CTRL* pw_ctrl )
{
#ifdef CO_PARAM_CHECK
	if( pw_ctrl == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PWch_Ctrl. error. pw_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PWch_Ctrl. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWS.bit.PWS			= pw_ctrl->trans_to;
	gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWCHCTL.bit.PWBMD	= E_IM_PRO_PWCH_BURST_512BYTE;
	gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWCHCTL.bit.PWLV		= pw_ctrl->req_threshold;
	gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWCHCTL.bit.PWMW		= pw_ctrl->write_mask;
	gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWDW.bit.PWDW		= pw_ctrl->burst_align_size;
	gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWVFM.bit.PWVFM		= pw_ctrl->output_format;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

INT32 paok_fnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch)
{
	if( gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
			Ddim_Assertion(("I:Im_PRO_PWch_Ctrl_Axi. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
			return D_IM_PRO_INPUT_PARAM_ERROR;
		}
	return 0;
}

INT32 paok_gnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, T_IM_PRO_AXI_CTRL* axi_ctrl)
{
	gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWAXCTL.bit.AWCACHE	= axi_ctrl->cache_type;
		gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWAXCTL.bit.AWPROT	= axi_ctrl->protect_type;
	return 0;
}

INT32 paok_hnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, ULONG line_feed)
{
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PWch_Set_LineFeed. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWLSIZE.bit.PWLSIZE = line_feed;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
	return 0;
}

INT32 paok_jnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, ULONG reg_addr)
{
	if( gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == 0 ) {
					}
					else {
						reg_addr = (ULONG)gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr - im_pro_get_block_top_addr( unit_no, block_type );
						Ddim_Print(( "gIM_PRO_PWCH_Reg_Ptr_Tbl unit_no:%u block_type:%u ch:%u REL_reg_addr(0x%08lx) ABS_reg_addr(0x%08lx) status(%u)\n",
																																		unit_no,
																																		block_type,
																																		ch,
																																		reg_addr,
																																		(ULONG)gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr,
																																		gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].status
						));
					}
	return 0;
				}

INT32 paok_knd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch)
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PWch_Start. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWCHTRG.bit.PWCHTRG	= D_IM_PRO_TRG_START;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_set_start_status( gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].status, 0 );
	return D_DDIM_OK;
	return 0;
}

INT32 paok_mnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch,UCHAR force)
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PWch_Stop. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	if (force == 0){
		gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWCHTRG.bit.PWCHTRG = D_IM_PRO_TRG_FRAME_STOP;	// stop
	}
	else{
		gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PWCHTRG.bit.PWCHTRG = D_IM_PRO_TRG_FORCE_STOP;	// force stop
	}
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_set_stop_status( gIM_PRO_PWCH_Reg_Ptr_Tbl[unit_no][block_type][ch].status, 0 );
	return D_DDIM_OK;
	return 0;
}

INT32 paok_nnd(PwchTbl* self,E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, ULONG reg_addr)
{
	if( gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == 0 ) {
					}
					else {
						reg_addr = (ULONG)gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr - im_pro_get_block_top_addr( unit_no, block_type );
						Ddim_Print(( "gIM_PRO_M2P_Reg_Ptr_Tbl unit_no:%u block_type:%u ch:%u REL_reg_addr(0x%08lx) ABS_reg_addr(0x%08lx) dkntbl_ptr(0x%08lx) status(%u)\n",
																																		unit_no,
																																		block_type,
																																		ch,
																																		(ULONG)reg_addr,
																																		(ULONG)gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr,
																																		(ULONG)gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].dkntbl_ptr,
																																		gIM_PRO_M2P_Reg_Ptr_Tbl[unit_no][block_type][ch].status
						));
					}
	return 0;
}

PwchTbl* pwch_tbl_get(void)
{
	static PwchTbl* self = NULL;
	if(!self){
		self = k_object_new(PWCH_TYPE_TBL);
	}
	return self;

	}

PwchTbl *pwch_tbl_new(void)
{
	PwchTbl* self = k_object_new_with_private(PWCH_TYPE_TBL,sizeof(PwchTblPrivate));
	return self;
}
