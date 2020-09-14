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
#include "dd_top.h"
#include "prchtbl.h"
#include "pkchtbl.h"
#include "pwchtbl.h"
#include "improcommon.h"
#include "improcommonfig.h"
#include "improcommonlist.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImProCommonList, im_pro_pommon_list);

struct _ImProCommonListPrivate
{
	int a;
};
volatile	ULONG	gIM_PRO_COMMON_START_Status[6] = {0x00000000};
static const T_IM_PRO_CH_COMBI	gIM_SEN_OBD_Ch_Convert_Tbl[ E_IM_PRO_OBD_CH_3_1 + 1 ] = {
	{ 0, 0 },
	{ 0, 1 },
	{ 1, 0 },
	{ 1, 1 },
	{ 2, 0 },
	{ 2, 1 },
	{ 3, 0 },
	{ 3, 1 },
};

static const T_IM_PRO_CH_COMBI	gIM_SEN_OBT_Ch_Convert_Tbl[ D_IM_PRO_SEN_OBT_CNT ] = {
	{ 0, 0 },
	{ 0, 1 },
	{ 1, 0 },
	{ 1, 1 },
	{ 2, 0 },
	{ 2, 1 },
	{ 3, 0 },
	{ 3, 1 },
};

static const E_IM_PRO_OBD_CH	gIM_SEN_OBD_Ch_RevConvert_Tbl[ D_IM_PRO_SEN_SENCORE_NUM ][ D_IM_PRO_SEN_OBD_CH_NUM ] = {
	{ E_IM_PRO_OBD_CH_0_0,	E_IM_PRO_OBD_CH_0_1	},
	{ E_IM_PRO_OBD_CH_1_0,	E_IM_PRO_OBD_CH_1_1	},
	{ E_IM_PRO_OBD_CH_2_0,	E_IM_PRO_OBD_CH_2_1	},
	{ E_IM_PRO_OBD_CH_3_0,	E_IM_PRO_OBD_CH_3_1	},
};

static const E_IM_PRO_OBT_CH	gIM_SEN_OBT_Ch_RevConvert_Tbl[ D_IM_PRO_SEN_SENCORE_NUM ][ D_IM_PRO_SEN_OBT_CH_NUM ] = {
	{ E_IM_PRO_OBT_CH_0_0,	E_IM_PRO_OBT_CH_0_1	},
	{ E_IM_PRO_OBT_CH_1_0,	E_IM_PRO_OBT_CH_1_1	},
	{ E_IM_PRO_OBT_CH_2_0,	E_IM_PRO_OBT_CH_2_1	},
	{ E_IM_PRO_OBT_CH_3_0,	E_IM_PRO_OBT_CH_3_1	},
};

static const T_IM_PRO_COMMON_P2M_INFO	gIM_PRO_P2M_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][E_IM_PRO_P2M_MAX] = {
	// E_IM_PRO_UNIT_NUM_1
	{
		{	// SEN
			{ &IO_PRO.SEN.P2M[0],				&IO_PRO_TBL.SEN_TBL.P2M0KNTBL,	D_IM_PRO_COMMON_STATUS_SEN_P2M0,	{ D_IM_PRO_COMMON_STATUS_SEN_PWCH0,		D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.SEN.P2M[1],				&IO_PRO_TBL.SEN_TBL.P2M1KNTBL,	D_IM_PRO_COMMON_STATUS_SEN_P2M1,	{ D_IM_PRO_COMMON_STATUS_SEN_PWCH1,		D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.SEN.P2M[2],				&IO_PRO_TBL.SEN_TBL.P2M2KNTBL,	D_IM_PRO_COMMON_STATUS_SEN_P2M2,	{ D_IM_PRO_COMMON_STATUS_SEN_PWCH2,		D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.SEN.P2M[3],				&IO_PRO_TBL.SEN_TBL.P2M3KNTBL,	D_IM_PRO_COMMON_STATUS_SEN_P2M3,	{ D_IM_PRO_COMMON_STATUS_SEN_PWCH3,		D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.SEN.P2M[4],				&IO_PRO_TBL.SEN_TBL.P2M4KNTBL,	D_IM_PRO_COMMON_STATUS_SEN_P2M4,	{ D_IM_PRO_COMMON_STATUS_SEN_PWCH4,		D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.SEN.P2M[5],				&IO_PRO_TBL.SEN_TBL.P2M5KNTBL,	D_IM_PRO_COMMON_STATUS_SEN_P2M5,	{ D_IM_PRO_COMMON_STATUS_SEN_PWCH5,		D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.SEN.P2M[6],				&IO_PRO_TBL.SEN_TBL.P2M6KNTBL,	D_IM_PRO_COMMON_STATUS_SEN_P2M6,	{ D_IM_PRO_COMMON_STATUS_SEN_PWCH6,		D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.SEN.P2M[7],				&IO_PRO_TBL.SEN_TBL.P2M7KNTBL,	D_IM_PRO_COMMON_STATUS_SEN_P2M7,	{ D_IM_PRO_COMMON_STATUS_SEN_PWCH7,		D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// SRO
			{ &IO_PRO.IMG_PIPE[0].SRO.P2M[0],	&IO_PRO_TBL.SRO1_TBL.P2M0KNTBL,	D_IM_PRO_COMMON_STATUS_SRO1_P2M0,	{ D_IM_PRO_COMMON_STATUS_SRO1_PWCH0,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].SRO.P2M[1],	&IO_PRO_TBL.SRO1_TBL.P2M1KNTBL,	D_IM_PRO_COMMON_STATUS_SRO1_P2M1,	{ D_IM_PRO_COMMON_STATUS_SRO1_PWCH1,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].SRO.P2M[2],	&IO_PRO_TBL.SRO1_TBL.P2M2KNTBL,	D_IM_PRO_COMMON_STATUS_SRO1_P2M2,	{ D_IM_PRO_COMMON_STATUS_SRO1_PWCH2,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].SRO.P2M[3],	&IO_PRO_TBL.SRO1_TBL.P2M3KNTBL,	D_IM_PRO_COMMON_STATUS_SRO1_P2M3,	{ D_IM_PRO_COMMON_STATUS_SRO1_PWCH3,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].SRO.P2M[4],	&IO_PRO_TBL.SRO1_TBL.P2M4KNTBL,	D_IM_PRO_COMMON_STATUS_SRO1_P2M4,	{ D_IM_PRO_COMMON_STATUS_SRO1_PWCH4,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].SRO.P2M[5],	&IO_PRO_TBL.SRO1_TBL.P2M5KNTBL,	D_IM_PRO_COMMON_STATUS_SRO1_P2M5,	{ D_IM_PRO_COMMON_STATUS_SRO1_PWCH5,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// B2B
			{ &IO_PRO.IMG_PIPE[0].B2B.P2M[0],	&IO_PRO_TBL.B2B1_TBL.P2M0KNTBL,	D_IM_PRO_COMMON_STATUS_B2B1_P2M0,	{ D_IM_PRO_COMMON_STATUS_B2B1_PWCH0,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[0].B2B.P2M[1],	&IO_PRO_TBL.B2B1_TBL.P2M1KNTBL,	D_IM_PRO_COMMON_STATUS_B2B1_P2M1,	{ D_IM_PRO_COMMON_STATUS_B2B1_PWCH1,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// STAT
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// PAS
			{ &IO_PRO.PAS.P2M0,					&IO_PRO_TBL.PAS_TBL.P2M0KNTBL,	D_IM_PRO_COMMON_STATUS_PAS_P2M0,	{ D_IM_PRO_COMMON_STATUS_PAS_PWCH0,		D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
	},
	{
		{	// SEN
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// SRO
			{ &IO_PRO.IMG_PIPE[1].SRO.P2M[0],	&IO_PRO_TBL.SRO2_TBL.P2M0KNTBL,	D_IM_PRO_COMMON_STATUS_SRO2_P2M0,	{ D_IM_PRO_COMMON_STATUS_SRO2_PWCH0,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].SRO.P2M[1],	&IO_PRO_TBL.SRO2_TBL.P2M1KNTBL,	D_IM_PRO_COMMON_STATUS_SRO2_P2M1,	{ D_IM_PRO_COMMON_STATUS_SRO2_PWCH1,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].SRO.P2M[2],	&IO_PRO_TBL.SRO2_TBL.P2M2KNTBL,	D_IM_PRO_COMMON_STATUS_SRO2_P2M2,	{ D_IM_PRO_COMMON_STATUS_SRO2_PWCH2,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].SRO.P2M[3],	&IO_PRO_TBL.SRO2_TBL.P2M3KNTBL,	D_IM_PRO_COMMON_STATUS_SRO2_P2M3,	{ D_IM_PRO_COMMON_STATUS_SRO2_PWCH3,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].SRO.P2M[4],	&IO_PRO_TBL.SRO2_TBL.P2M4KNTBL,	D_IM_PRO_COMMON_STATUS_SRO2_P2M4,	{ D_IM_PRO_COMMON_STATUS_SRO2_PWCH4,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].SRO.P2M[5],	&IO_PRO_TBL.SRO2_TBL.P2M5KNTBL,	D_IM_PRO_COMMON_STATUS_SRO2_P2M5,	{ D_IM_PRO_COMMON_STATUS_SRO2_PWCH5,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// B2B
			{ &IO_PRO.IMG_PIPE[1].B2B.P2M[0],	&IO_PRO_TBL.B2B2_TBL.P2M0KNTBL,	D_IM_PRO_COMMON_STATUS_B2B2_P2M0,	{ D_IM_PRO_COMMON_STATUS_B2B2_PWCH0,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ &IO_PRO.IMG_PIPE[1].B2B.P2M[1],	&IO_PRO_TBL.B2B2_TBL.P2M1KNTBL,	D_IM_PRO_COMMON_STATUS_B2B2_P2M1,	{ D_IM_PRO_COMMON_STATUS_B2B2_PWCH1,	D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// STAT
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	//PAS
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
		},
	},
	{
		{	//SEN
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE}	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// SRO
			{ &IO_PRO.IMG_PIPE[2].SRO.P2M[0],	&IO_PRO_TBL.SRO3_TBL.P2M0KNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PWCH0,	D_IM_PRO_COMMON_STATUS_SRO2_PWCH0 }	},
			{ &IO_PRO.IMG_PIPE[2].SRO.P2M[1],	&IO_PRO_TBL.SRO3_TBL.P2M1KNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PWCH1,	D_IM_PRO_COMMON_STATUS_SRO2_PWCH1 }	},
			{ &IO_PRO.IMG_PIPE[2].SRO.P2M[2],	&IO_PRO_TBL.SRO3_TBL.P2M2KNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PWCH2,	D_IM_PRO_COMMON_STATUS_SRO2_PWCH2 }	},
			{ &IO_PRO.IMG_PIPE[2].SRO.P2M[3],	&IO_PRO_TBL.SRO3_TBL.P2M3KNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PWCH3,	D_IM_PRO_COMMON_STATUS_SRO2_PWCH3 }	},
			{ &IO_PRO.IMG_PIPE[2].SRO.P2M[4],	&IO_PRO_TBL.SRO3_TBL.P2M4KNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PWCH4,	D_IM_PRO_COMMON_STATUS_SRO2_PWCH4 }	},
			{ &IO_PRO.IMG_PIPE[2].SRO.P2M[5],	&IO_PRO_TBL.SRO3_TBL.P2M5KNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_SRO1_PWCH5,	D_IM_PRO_COMMON_STATUS_SRO2_PWCH5 }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE		  }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE		  }	},
		},
		{	// B2B
			{ &IO_PRO.IMG_PIPE[2].B2B.P2M[0],	&IO_PRO_TBL.B2B3_TBL.P2M0KNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_B2B1_PWCH0,	D_IM_PRO_COMMON_STATUS_B2B2_PWCH0 }	},
			{ &IO_PRO.IMG_PIPE[2].B2B.P2M[1],	&IO_PRO_TBL.B2B3_TBL.P2M1KNTBL,	D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_B2B1_PWCH1,	D_IM_PRO_COMMON_STATUS_B2B2_PWCH1 }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// STAT
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
		{	// PAS
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
			{ NULL,								NULL,							D_IM_PRO_COMMON_STATUS_NONE,		{ D_IM_PRO_COMMON_STATUS_NONE,			D_IM_PRO_COMMON_STATUS_NONE }	},
		},
	},
};

static void im_pro_pommon_list_constructor(ImProCommonList *self)
{
	ImProCommonListPrivate *priv = IM_PRO_COMMON_LIST_GET_PRIVATE(self);
	priv-> a = 0;
}

static void im_pro_pommon_list_destructor(ImProCommonList *self)
{
	ImProCommonListPrivate *priv = IM_PRO_COMMON_LIST_GET_PRIVATE(self);
	priv-> a = 0;
}

VOID im_pro_comm_get_obd_block_ch( E_IM_PRO_OBD_CH ch, UCHAR* block_num, UCHAR* ch_num )
{
#ifdef CO_PARAM_CHECK
	if( block_num == NULL ) {
		Ddim_Assertion(("I:im_pro_comm_get_obd_block_ch error. ch:%d block_num=NULL\n", ch));
		return;
	}
	if( ch_num == NULL ) {
		Ddim_Assertion(("I:im_pro_comm_get_obd_block_ch error. ch:%d ch_num=NULL\n", ch));
		return;
	}
#endif
	*block_num	= gIM_SEN_OBD_Ch_Convert_Tbl[ch].block_num;
	*ch_num		= gIM_SEN_OBD_Ch_Convert_Tbl[ch].ch_num;
}

VOID im_pro_comm_get_obt_block_ch( E_IM_PRO_OBT_CH ch, UCHAR* block_num, UCHAR* ch_num )
{
#ifdef CO_PARAM_CHECK
	if( block_num == NULL ) {
		Ddim_Assertion(("I:im_pro_comm_get_obt_block_ch error. ch:%d block_num=NULL\n", ch));
		return;
	}
	if( ch_num == NULL ) {
		Ddim_Assertion(("I:im_pro_comm_get_obt_block_ch error. ch:%d ch_num=NULL\n", ch));
		return;
	}
#endif
	*block_num	= gIM_SEN_OBT_Ch_Convert_Tbl[ch].block_num;
	*ch_num		= gIM_SEN_OBT_Ch_Convert_Tbl[ch].ch_num;
}

VOID im_pro_comm_get_obd_ch( UCHAR block_num, UCHAR ch_num, E_IM_PRO_OBD_CH* ch )
{
#ifdef CO_PARAM_CHECK
	if( block_num >= D_IM_PRO_SEN_SENCORE_NUM ) {
		Ddim_Assertion(("I:im_pro_comm_get_obd_ch error. block_num(%u) > D_IM_PRO_SEN_SENCORE_NUM(%u)\n", block_num, D_IM_PRO_SEN_SENCORE_NUM));
		return ;
	}
	if( ch_num >= D_IM_PRO_SEN_OBD_CH_NUM ) {
		Ddim_Assertion(("I:im_pro_comm_get_obd_ch error. ch_num(%u) > D_IM_PRO_SEN_OBD_CH_NUM(%u)\n", ch_num, D_IM_PRO_SEN_OBD_CH_NUM));
		return;
	}
#endif
	*ch	= gIM_SEN_OBD_Ch_RevConvert_Tbl[block_num][ch_num];
}

VOID im_pro_comm_get_obt_ch( UCHAR block_num, UCHAR ch_num, E_IM_PRO_OBT_CH* ch )
{
#ifdef CO_PARAM_CHECK
	if( block_num >= D_IM_PRO_SEN_SENCORE_NUM ) {
		Ddim_Assertion(("I:im_pro_comm_get_obt_ch error. block_num(%u) > D_IM_PRO_SEN_SENCORE_NUM(%u)\n", block_num, D_IM_PRO_SEN_SENCORE_NUM));
		return;
	}
	if( ch_num >= D_IM_PRO_SEN_OBT_CH_NUM ) {
		Ddim_Assertion(("I:im_pro_comm_get_obt_ch error. ch_num(%u) > D_IM_PRO_SEN_SENCORE_NUM(%u)\n", ch_num, D_IM_PRO_SEN_OBT_CH_NUM));
		return;
	}
#endif
	*ch	= gIM_SEN_OBT_Ch_RevConvert_Tbl[block_num][ch_num];
}

VOID im_pro_comm_get_p2m_reg_info( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_P2M_CH ch, const T_IM_PRO_COMMON_P2M_INFO** p2m_info )
{
	*p2m_info = &gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch];
}

INT32 Im_PRO_P2M_Start( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_P2M_CH ch )
{
	ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_P2M_Start. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	for( UCHAR loopcnt = 0; loopcnt < D_IM_PRO_COMMON_P2M_PRE_STARTED_STATUS_MAX; loopcnt++ ) {
		if(gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].pre_started_status[loopcnt] != D_IM_PRO_COMMON_STATUS_NONE) {
			if (im_pro_common_get_start_status(gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].pre_started_status[loopcnt], 0) == FALSE){
				Ddim_Print(("I:Im_PRO_P2M_Start. macro not stopped error. Pre-Stopped Macro status:(%u) \n", gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].pre_started_status[loopcnt]));
				return D_IM_PRO_MACRO_BUSY_NG;
			}
		}
	}
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2MTRG.bit.P2MTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_set_start_status( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].status, 0 );
	return D_DDIM_OK;
}

INT32 Im_PRO_P2M_Stop( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_P2M_CH ch, UCHAR force )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_P2M_Stop. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	if (force == 0){
		gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2MTRG.bit.P2MTRG = D_IM_PRO_TRG_FRAME_STOP;	// frame stop
	}
	else{
		for( UCHAR loopcnt = 0; loopcnt < D_IM_PRO_COMMON_P2M_PRE_STARTED_STATUS_MAX; loopcnt++ ) {
			if(gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].pre_started_status[loopcnt] != D_IM_PRO_COMMON_STATUS_NONE) {
				if (im_pro_common_get_start_status(gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].pre_started_status[loopcnt], 0) == TRUE){
					Ddim_Print(("I:Im_PRO_P2M_Stop. macro not stopped error. Pre-Stopped Macro status:(%u) \n", gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].pre_started_status[loopcnt]));
					return D_IM_PRO_MACRO_BUSY_NG;
				}
			}
		}
		gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2MTRG.bit.P2MTRG = D_IM_PRO_TRG_FORCE_STOP;	// force stop
	}
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_set_stop_status( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].status, 0 );
	return D_DDIM_OK;
}

INT32 Im_PRO_P2M_Ctrl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_P2M_CH ch, T_IM_PRO_P2M_CTRL* p2m_ctrl )
{
#ifdef CO_PARAM_CHECK
	if( p2m_ctrl == NULL ) {
		Ddim_Assertion(("I:Im_PRO_P2M_Ctrl error. p2m_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_P2M_Ctrl. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_P2M_PBSFT_MIN, D_IM_PRO_P2M_PBSFT_MAX, p2m_ctrl->shift_bit, "Im_PRO_P2M_Ctrl : shift_bit" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_P2M_PTRMV_MIN, D_IM_PRO_P2M_PTRMV_MAX, p2m_ctrl->start_y, "Im_PRO_P2M_Ctrl : start_y" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_P2M_PTRMH_MIN, D_IM_PRO_P2M_PTRMH_MAX, p2m_ctrl->start_x, "Im_PRO_P2M_Ctrl : start_x" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2MCTL.bit.PKNEMD			= p2m_ctrl->knee_enable;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2MCTL.bit.PLPF			= p2m_ctrl->lpf_mode;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2MCTL.bit.P2MTYP			= p2m_ctrl->rec_mode;
	im_pro_set_reg_signed( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2MOFS, union io_p2mofs, P2MOFS, p2m_ctrl->shift_value );
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PBSFT.bit.PBSFT			= p2m_ctrl->shift_bit;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PCLPH.bit.PCLPH			= p2m_ctrl->clip_value;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PTRMV.bit.PTRMV			= p2m_ctrl->start_y;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PTRMH.bit.PTRMH			= p2m_ctrl->start_x;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PTRMVW.bit.PTRMVW			= p2m_ctrl->height;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PTRMHW.bit.PTRMHW			= p2m_ctrl->width;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PTRMXVCYC.bit.PTRMXVCYC	= p2m_ctrl->vertical_thin;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PTRMXHCYC.bit.PTRMXHCYC	= p2m_ctrl->horizon_thin;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PTRMXVEN.bit.PTRMXVEN		= p2m_ctrl->sample_line;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->PTRMXHEN.bit.PTRMXHEN		= p2m_ctrl->sample_width;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2MMIR.bit.P2MMIR			= p2m_ctrl->enable_mirror;
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2M2PMD.bit.P2M2PMD		= p2m_ctrl->input_mode;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

INT32 Im_PRO_P2M_Set_PAEN( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_P2M_CH ch, UCHAR paen_trg )
{
#ifdef CO_PARAM_CHECK
	if( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_P2M_Set_PAEN. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( ( paen_trg == 0 ) && ( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2MTRG.bit.P2MTRG != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:Im_PRO_P2M_Set_PAEN. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2MPAEN.bit.PAEN = paen_trg;
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

INT32 Im_PRO_P2M_Set_Table( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_P2M_CH ch, T_IM_PRO_P2M_TABLE* p2m_tbl )
{
#ifdef CO_PARAM_CHECK
	if( p2m_tbl == NULL ) {
		Ddim_Assertion(("I:Im_PRO_P2M_Set_Table. error. m2p_tbl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_P2M_Set_PAEN. invalid ch parameters. unit:%d block:%d ch:%d \n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].kntbl_ptr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_P2M_Set_Table. error. unit:%d block:%d ch:%d kntbl_ptr=NULL\n", unit_no, block_type, ch));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2MPAEN.bit.PAEN != 1 ) {
		Ddim_Assertion(("I:Im_PRO_P2M_Set_Table. built-in RAM access disabled error. P2MPAEN == 0.\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr->P2MTRG.bit.P2MTRG != D_IM_PRO_TRG_STATUS_STOPPED ) {
		Ddim_Assertion(("I:Im_PRO_P2M_Set_Table. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	im_pro_common_fig_im_pro_on_hclk( unit_no, im_pro_convert_clk_type( block_type ) );
	im_pro_common_fig_im_pro_memcpy( NULL,(void*)gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].kntbl_ptr->hword, p2m_tbl->pp2m_tbl, ( p2m_tbl->size * sizeof(USHORT) ) );
	im_pro_off_hclk( unit_no, im_pro_convert_clk_type( block_type ) );
	return D_DDIM_OK;
}

VOID im_pro_management_info_print( VOID )
{
	E_IM_PRO_UNIT_NUM unit_no;
	E_IM_PRO_BLOCK_TYPE block_type;
	UCHAR ch = 0;
	ULONG reg_addr = 0;
	Ddim_Print(( ">>>>PRO driver Clock Management Information\n"));
#ifdef CO_ACT_PRO_CLOCK
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT; unit_no++ ) {
		for( ch = E_IM_PRO_CLK_BLOCK_TYPE_SEN; ch < E_IM_PRO_CLK_BLOCK_TYPE_MAX; ch++ ) {
			Ddim_Print(( "gIM_Drive_Clk_Info unit_no:%u clk_block_type:%u reg_addr(0x%08lx) reg_bit(%u) reg_ctrl_cnt(0x%08lx)\n",
																																unit_no,
																																ch,
																																(ULONG)gIM_Drive_Clk_Info[unit_no][ch].reg_addr,
																																gIM_Drive_Clk_Info[unit_no][ch].reg_bit,
																																(ULONG)gIM_Drive_Clk_Info[unit_no][ch].reg_ctrl_cnt
			));
		}
	}
#endif	// CO_ACT_PRO_CLOCK

#ifdef CO_ACT_PRO_PCLOCK
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT; unit_no++ ) {
		for( ch = E_IM_PRO_CLK_BLOCK_TYPE_SEN; ch < E_IM_PRO_CLK_BLOCK_TYPE_MAX; ch++ ) {
			Ddim_Print(( "gIM_Pclk_Info unit_no:%u clk_block_type:%u reg_addr(0x%08lx) reg_bit(%u) reg_ctrl_cnt(0x%08lx)\n",
																																unit_no,
																																ch,
																																(ULONG)gIM_Pclk_Info[unit_no][ch].reg_addr,
																																gIM_Pclk_Info[unit_no][ch].reg_bit,
																																(ULONG)gIM_Pclk_Info[unit_no][ch].reg_ctrl_cnt
			));
		}
	}
#endif	// CO_ACT_PRO_PCLOCK

#ifdef CO_ACT_PRO_HCLOCK
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT; unit_no++ ) {
		for( ch = E_IM_PRO_CLK_BLOCK_TYPE_SEN; ch < E_IM_PRO_CLK_BLOCK_TYPE_MAX; ch++ ) {
			Ddim_Print(( "gIM_Hclk_Info unit_no:%u clk_block_type:%u reg_addr(0x%08lx) reg_bit(%u) reg_ctrl_cnt(0x%08lx)\n",
																																unit_no,
																																ch,
																																(ULONG)gIM_Hclk_Info[unit_no][ch].reg_addr,
																																gIM_Hclk_Info[unit_no][ch].reg_bit,
																																(ULONG)gIM_Hclk_Info[unit_no][ch].reg_ctrl_cnt
			));
		}
	}
#endif	// CO_ACT_PRO_HCLOCK

#ifdef CO_ACT_PRO_ICLOCK
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT; unit_no++ ) {
		for( ch = E_IM_PRO_CLK_BLOCK_TYPE_SEN; ch < E_IM_PRO_CLK_BLOCK_TYPE_MAX; ch++ ) {
			Ddim_Print(( "gIM_Xclk_Info unit_no:%u clk_block_type:%u reg_addr(0x%08lx) reg_bit(%u) reg_ctrl_cnt(0x%08lx)\n",
																																unit_no,
																																ch,
																																(ULONG)gIM_Xclk_Info[unit_no][ch].reg_addr,
																																gIM_Xclk_Info[unit_no][ch].reg_bit,
																																(ULONG)gIM_Xclk_Info[unit_no][ch].reg_ctrl_cnt
			));
		}
	}
#endif	// CO_ACT_PRO_ICLOCK
	Ddim_Print(( ">>>>PRO driver each block Register TOP address Information\n"));
	Ddim_Print(( "SEN  unit_no:%u REL_reg_addr(0x%08x) ABS_reg_addr(0x%08x) \n",	E_IM_PRO_UNIT_NUM_1,
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN ) - (UINT32)&IO_PRO,
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN )));
	Ddim_Print(( "SRO  unit_no:%u REL_reg_addr(0x%08x) ABS_reg_addr(0x%08x) \n",	E_IM_PRO_UNIT_NUM_1,
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SRO ) - (UINT32)&IO_PRO.IMG_PIPE[E_IM_PRO_UNIT_NUM_1],
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SRO )));
	Ddim_Print(( "B2B  unit_no:%u REL_reg_addr(0x%08x) ABS_reg_addr(0x%08x) \n",	E_IM_PRO_UNIT_NUM_1,
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_B2B ) - (UINT32)&IO_PRO.IMG_PIPE[E_IM_PRO_UNIT_NUM_1],
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_B2B )));
	Ddim_Print(( "SRO  unit_no:%u REL_reg_addr(0x%08x) ABS_reg_addr(0x%08x) \n",	E_IM_PRO_UNIT_NUM_2,
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_BLOCK_TYPE_SRO ) - (UINT32)&IO_PRO.IMG_PIPE[E_IM_PRO_UNIT_NUM_2],
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_BLOCK_TYPE_SRO )));
	Ddim_Print(( "B2B  unit_no:%u REL_reg_addr(0x%08x) ABS_reg_addr(0x%08x) \n",	E_IM_PRO_UNIT_NUM_2,
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_BLOCK_TYPE_B2B ) - (UINT32)&IO_PRO.IMG_PIPE[E_IM_PRO_UNIT_NUM_2],
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_2, E_IM_PRO_BLOCK_TYPE_B2B )));
	Ddim_Print(( "SRO  unit_no:%u REL_reg_addr(0x%08x) ABS_reg_addr(0x%08x) \n",	E_IM_PRO_BOTH_UNIT,
																				im_pro_get_block_top_addr( E_IM_PRO_BOTH_UNIT, E_IM_PRO_BLOCK_TYPE_SRO ) - (UINT32)&IO_PRO.IMG_PIPE[E_IM_PRO_BOTH_UNIT],
																				im_pro_get_block_top_addr( E_IM_PRO_BOTH_UNIT, E_IM_PRO_BLOCK_TYPE_SRO )));
	Ddim_Print(( "B2B  unit_no:%u REL_reg_addr(0x%08x) ABS_reg_addr(0x%08x) \n",	E_IM_PRO_BOTH_UNIT,
																				im_pro_get_block_top_addr( E_IM_PRO_BOTH_UNIT, E_IM_PRO_BLOCK_TYPE_B2B ) - (UINT32)&IO_PRO.IMG_PIPE[E_IM_PRO_BOTH_UNIT],
																				im_pro_get_block_top_addr( E_IM_PRO_BOTH_UNIT, E_IM_PRO_BLOCK_TYPE_B2B )));
	Ddim_Print(( "STAT unit_no:%u REL_reg_addr(0x%08x) ABS_reg_addr(0x%08x) \n",	E_IM_PRO_UNIT_NUM_1,
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_STAT ) - (UINT32)IO_PRO.dmy_28800000_2885FFFF,
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_STAT )));
	Ddim_Print(( "PAS  unit_no:%u REL_reg_addr(0x%08x) ABS_reg_addr(0x%08x) \n",	E_IM_PRO_UNIT_NUM_1,
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_PAS ) - (UINT32)IO_PRO.dmy_28800000_2885FFFF,
																				im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_PAS )));
	Ddim_Print(( ">>>>PRO driver P2M Register address Management Information\n"));
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT + 1; unit_no++ ) {
		for( block_type = E_IM_PRO_BLOCK_TYPE_SEN; block_type < E_IM_PRO_BLOCK_TYPE_MAX; block_type++ ) {
			for( ch = 0; ch < E_IM_PRO_P2M_MAX; ch++ ) {
				if( gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr == 0 ) {
				}
				else {
					reg_addr = (ULONG)gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr - im_pro_get_block_top_addr( unit_no, block_type );
					Ddim_Print(( "gIM_PRO_P2M_Reg_Ptr_Tbl unit_no:%u block_type:%u ch:%u REL_reg_addr(0x%08lx) ABS_reg_addr(0x%08lx) kntbl_ptr(0x%08lx) status(%u)\n",
																																	unit_no,
																																	block_type,
																																	ch,
																																	(ULONG)reg_addr,
																																	(ULONG)gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].reg_ptr,
																																	(ULONG)gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].kntbl_ptr,
																																	gIM_PRO_P2M_Reg_Ptr_Tbl[unit_no][block_type][ch].status
					));
				}
			}
		}
	}
	Ddim_Print(( ">>>>PRO driver PWCH Register address Management Information\n"));
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT + 1; unit_no++ ) {
		for( block_type = E_IM_PRO_BLOCK_TYPE_SEN; block_type < E_IM_PRO_BLOCK_TYPE_MAX; block_type++ ) {
			for( ch = 0; ch < E_IM_PRO_PWCH_MAX; ch++ ) {
				paok_jnd(pwch_tbl_get(),   unit_no,  block_type,  ch,reg_addr);
			}
		}
	}
	Ddim_Print(( ">>>>PRO driver M2P Register address Management Information\n"));
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT + 1; unit_no++ ) {
		for( block_type = E_IM_PRO_BLOCK_TYPE_SEN; block_type < E_IM_PRO_BLOCK_TYPE_MAX; block_type++ ) {
			for( ch = 0; ch < 10; ch++ ) {
				paok_nnd(pwch_tbl_get(),   unit_no,  block_type,  ch,reg_addr);
			}
		}
	}
	Ddim_Print(( ">>>>PRO driver PRCH Register address Management Information\n"));
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT + 1; unit_no++ ) {
		for( block_type = E_IM_PRO_BLOCK_TYPE_SEN; block_type < E_IM_PRO_BLOCK_TYPE_MAX; block_type++ ) {
			for( ch = 0; ch < 10; ch++ ) {
				 paek_cnd(pkch_tbl_get(),   unit_no,  block_type,  ch, reg_addr);
			}
		}
	}
	Ddim_Print(( ">>>>PRO driver LNR Register address Management Information\n"));
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT + 1; unit_no++ ) {
		for( block_type = E_IM_PRO_BLOCK_TYPE_SEN; block_type < E_IM_PRO_BLOCK_TYPE_MAX; block_type++ ) {
			for( ch = 0; ch < D_IM_PRO_SEN_LNR_CH_NUM; ch++ ) {
				paek_bnd(prch_tbl_get(),   unit_no,  block_type,  ch, reg_addr);
			}
		}
	}
	Ddim_Print(( ">>>>PRO driver MONI Register address Management Information\n"));
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT + 1; unit_no++ ) {
		for( block_type = E_IM_PRO_BLOCK_TYPE_SEN; block_type < E_IM_PRO_BLOCK_TYPE_MAX; block_type++ ) {
			for( ch = 0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++ ) {
				 paek_cnd(pkch_tbl_get(),   unit_no,  block_type,  ch,reg_addr);
			}
		}
	}
	Ddim_Print(( ">>>>PRO driver PG Register address Management Information\n"));
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT + 1; unit_no++ ) {
		for( block_type = E_IM_PRO_BLOCK_TYPE_SEN; block_type < E_IM_PRO_BLOCK_TYPE_MAX; block_type++ ) {
			for( ch = 0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++ ) {
				 paek_dnd(pkch_tbl_get(),   unit_no,  block_type,  ch,reg_addr);
			}
		}
	}
	Ddim_Print(( ">>>>PRO driver PGAIN Register address Management Information\n"));
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT + 1; unit_no++ ) {
		for( block_type = E_IM_PRO_BLOCK_TYPE_SEN; block_type < E_IM_PRO_BLOCK_TYPE_MAX; block_type++ ) {
			for( ch = 0; ch < D_IM_PRO_PGAIN_CNT; ch++ ) {
				 paek_end(pkch_tbl_get(),   unit_no,  block_type,  ch,reg_addr);
			}
		}
	}
	Ddim_Print(( ">>>>PRO driver PZSFT Register address Management Information\n"));
	for( unit_no = E_IM_PRO_UNIT_NUM_1; unit_no < E_IM_PRO_BOTH_UNIT + 1; unit_no++ ) {
		for( block_type = E_IM_PRO_BLOCK_TYPE_SEN; block_type < E_IM_PRO_BLOCK_TYPE_MAX; block_type++ ) {
			for( ch = 0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++ ) {
				paek_fnd(pkch_tbl_get(),   unit_no,  block_type,  ch,reg_addr);
			}
		}
	}
}

INT32 Im_PRO_PWch_Start( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch )
{
	 paok_knd(pwch_tbl_get(),   unit_no,  block_type,  ch);
	 return 0;
}

INT32 Im_PRO_PWch_Stop( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, UCHAR force )
{
	 paok_mnd(pwch_tbl_get(),   unit_no,  block_type,  ch,force);
		 return 0;
}

E_IM_PRO_CLK_BLOCK_TYPE im_pro_convert_clk_type( E_IM_PRO_BLOCK_TYPE block_type )
{
	E_IM_PRO_CLK_BLOCK_TYPE ret_type;
	switch( block_type ) {
		case E_IM_PRO_BLOCK_TYPE_SEN:
			ret_type = E_IM_PRO_CLK_BLOCK_TYPE_SEN;
			break;
		case E_IM_PRO_BLOCK_TYPE_SRO:
			ret_type = E_IM_PRO_CLK_BLOCK_TYPE_SRO;
			break;
		case E_IM_PRO_BLOCK_TYPE_B2B:
			ret_type = E_IM_PRO_CLK_BLOCK_TYPE_B2B;
			break;
		case E_IM_PRO_BLOCK_TYPE_STAT:
			ret_type = E_IM_PRO_CLK_BLOCK_TYPE_STAT;
			break;
		//case E_IM_PRO_BLOCK_TYPE_PAS:
		default:
			ret_type = E_IM_PRO_CLK_BLOCK_TYPE_PAS;
			break;
	}
	return ret_type;
}

VOID Im_PRO_On_Pclk( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type )
{
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
}

VOID Im_PRO_On_Hclk( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type )
{
	im_pro_common_fig_im_pro_on_hclk( unit_no, im_pro_convert_clk_type( block_type ) );
}

VOID Im_PRO_Off_Pclk( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type )
{
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
}

VOID Im_PRO_Off_Hclk( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type )
{
	im_pro_off_hclk( unit_no, im_pro_convert_clk_type( block_type ) );
}

INT32 Im_PRO_PWch_Ctrl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, T_IM_PRO_PWCH_CTRL* pw_ctrl )
{
	 paok_end(pwch_tbl_get(),   unit_no,  block_type,  ch, pw_ctrl);
	 return 0;
}

INT32 Im_PRO_PWch_Ctrl_Axi( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, T_IM_PRO_AXI_CTRL* axi_ctrl )
{
#ifdef CO_PARAM_CHECK
	if( axi_ctrl == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PWch_Ctrl_Axi. error. axi_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	 paok_fnd(pwch_tbl_get(),   unit_no,  block_type,  ch);
	if ( axi_ctrl->cache_type > D_IM_PRO_PWCH_AWCACHE_MAX ) {
		Ddim_Assertion(("I:Im_PRO_PWch_Ctrl_Axi. error. PWch cache type value over (%d)\n", axi_ctrl->cache_type));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if ( axi_ctrl->protect_type > D_IM_PRO_PWCH_AWPROT_MAX ) {
		Ddim_Assertion(("I:Im_PRO_PWch_Ctrl_Axi. error. PWch protect type value over (%d)\n", axi_ctrl->protect_type));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	 paok_gnd(pwch_tbl_get(),   unit_no,  block_type,  ch,axi_ctrl);
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );

	return D_DDIM_OK;
}

INT32 Im_PRO_PWch_Set_LineFeed( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, ULONG line_feed )
{
	 paok_hnd(pwch_tbl_get(),   unit_no,  block_type,  ch,line_feed);
	 return 0;
}

UINT32 im_pro_get_sro_clk_hz( E_IM_PRO_UNIT_NUM unit_no )
{
	UINT32 macro_clk_sel = 0;
	UINT32 macro_clk_hz = 0;
	macro_clk_sel = ( unit_no == E_IM_PRO_UNIT_NUM_1 ) ? Dd_Top_Get_CLKSEL5_SRO1CLK() : Dd_Top_Get_CLKSEL7_SRO2CLK();
	if( macro_clk_sel == SROCLK_300MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_300MHZ;
	}
	else if( macro_clk_sel == SROCLK_200MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_200MHZ;
	}
	else if( macro_clk_sel == SROCLK_150MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_150MHZ;
	}
	else if( macro_clk_sel == SROCLK_100MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_100MHZ;
	}
	else if( macro_clk_sel == SROCLK_75MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_75MHZ;
	}
	else if( macro_clk_sel == SROCLK_60MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_60MHZ;
	}
	else if( macro_clk_sel == SROCLK_50MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_50MHZ;
	}
	else {
	}
	return macro_clk_hz;
}

UINT32 im_pro_get_b2b_clk_hz( E_IM_PRO_UNIT_NUM unit_no )
{
	UINT32 macro_clk_sel = 0;
	UINT32 macro_clk_hz = 0;
	macro_clk_sel = ( unit_no == E_IM_PRO_UNIT_NUM_1 ) ? Dd_Top_Get_CLKSEL5_B2B1CLK() : Dd_Top_Get_CLKSEL7_B2B2CLK();
	if( macro_clk_sel == B2BCLK_300MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_300MHZ;
	}
	else if( macro_clk_sel == B2BCLK_200MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_200MHZ;
	}
	else if( macro_clk_sel == B2BCLK_150MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_150MHZ;
	}
	else if( macro_clk_sel == B2BCLK_100MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_100MHZ;
	}
	else if( macro_clk_sel == B2BCLK_75MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_75MHZ;
	}
	else if( macro_clk_sel == B2BCLK_60MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_60MHZ;
	}
	else if( macro_clk_sel == B2BCLK_50MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_50MHZ;
	}
	else if( macro_clk_sel == B2BCLK_SRO1CLK ) {
		macro_clk_hz = im_pro_get_sro_clk_hz( unit_no );
	}
	else if( macro_clk_sel == B2BCLK_SRO1CLK_2 ) {
		macro_clk_hz = im_pro_get_sro2_clk_hz( unit_no );
	}
	return macro_clk_hz;
}

BOOL im_pro_check_val_range(ULONG min, ULONG max, ULONG val, char* func_name )
{
	if( ( val < min ) || ( val > max )) {
		Ddim_Assertion(("I:%s. value range error!! limit value:%lu-%lu (%lu)\n",func_name, min, max ,val ));
		return FALSE;
	}
	else {
		return TRUE;
	}
}

VOID Im_PRO_Get_Current_Clk_Hz( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_CLK_BLOCK_TYPE block_type, UINT32* macro_clk_hz )
{
	UINT32 cpu_clk_hz = 0;	// dummy
	im_pro_get_current_clk_hz( unit_no, block_type, &cpu_clk_hz, macro_clk_hz );
}

UINT32 im_pro_get_block_top_addr( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type )
{
	UINT32 abs_block_top_reg_addr = 0;
	switch( block_type ) {
		case E_IM_PRO_BLOCK_TYPE_SEN:
			abs_block_top_reg_addr = (UINT32)&IO_PRO.SEN;
			break;
		case E_IM_PRO_BLOCK_TYPE_SRO:
			abs_block_top_reg_addr = (UINT32)&IO_PRO.IMG_PIPE[unit_no].SRO;
			break;
		case E_IM_PRO_BLOCK_TYPE_B2B:
			abs_block_top_reg_addr = (UINT32)&IO_PRO.IMG_PIPE[unit_no].B2B;
			break;
		case E_IM_PRO_BLOCK_TYPE_STAT:
			abs_block_top_reg_addr = (UINT32)&IO_PRO.STAT;
			break;
		case E_IM_PRO_BLOCK_TYPE_PAS:
			abs_block_top_reg_addr = (UINT32)&IO_PRO.PAS;
			break;
		default:
			abs_block_top_reg_addr = 0;
			break;
	}
	return abs_block_top_reg_addr;
}

UINT32 im_pro_get_sro2_clk_hz( E_IM_PRO_UNIT_NUM unit_no )
{
	UINT32 macro_clk_sel = 0;
	UINT32 macro_clk_hz = 0;
	macro_clk_sel = ( unit_no == E_IM_PRO_UNIT_NUM_1 ) ? Dd_Top_Get_CLKSEL4_SRO1CLK_2() : Dd_Top_Get_CLKSEL6_SRO2CLK_2();
	if( macro_clk_sel == SRO2CLK_300MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_300MHZ;
	}
	else if( macro_clk_sel == SRO2CLK_200MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_200MHZ;
	}
	else if( macro_clk_sel == SRO2CLK_150MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_150MHZ;
	}
	else if( macro_clk_sel == SRO2CLK_100MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_100MHZ;
	}
	else if( macro_clk_sel == SRO2CLK_75MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_75MHZ;
	}
	else if( macro_clk_sel == SRO2CLK_60MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_60MHZ;
	}
	else if( macro_clk_sel == SRO2CLK_50MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_50MHZ;
	}
	else {
	}
	return macro_clk_hz;
}

ImProCommonList* im_pro_common_list_get(void)
{
	static ImProCommonList* self = NULL;
	if(!self){
		self = k_object_new(IM_TYPE_PRO_COMMON_LIST);
	}
	return self;

	}

ImProCommonList *im_pro_pommon_list_new(void)
{
	ImProCommonList* self = k_object_new_with_private(IM_TYPE_PRO_COMMON_LIST,sizeof(ImProCommonListPrivate));
	return self;
}
