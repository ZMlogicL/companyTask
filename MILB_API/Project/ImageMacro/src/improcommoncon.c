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
#include "pwchtbl.h"
#include "improcommon.h"
#include "improcommoncon.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImProCommonCon, im_pro_common_con);
#define IM_PRO_COMMON_CON_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImProCommonConPrivate, IM_TYPE_PRO_COMMON_CON))

struct _ImProCommonConPrivate
{
	int a;
};

// OBD
static	volatile	T_IM_PRO_OBD_BUF_INFO	gIM_PRO_OBD_Buffer_Info[D_IM_PRO_SENTOP_BLOB_NUM][D_IM_PRO_SEN_OBD_CH_NUM] = {
	{
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
	},
	{
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
	},
	{
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
	},
	{
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
	},
};

// RDMA I/F
static const T_IM_PRO_RDMA_LNR_ADDR gIM_PRO_LNR_Addr[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][D_IM_PRO_SEN_LNR_CH_NUM] = {
	{
		// E_IM_PRO_BLOCK_TYPE_SEN
		{
			// E_IM_PRO_LNR_CH_0
			{
				0x2800AC10,0x2800AC14,0x2800AC18,0x2800AC1C,
				0x2800AC20,0x2800AC24,0x2800AC28,0x2800AC2C,
				0x2800AC30,0x2800AC34,0x2800AC38,0x2800AC3C,
				0x2800AC40,0x2800AC44,0x2800AC48,0x2800AC4C,
				0x2800AC50,0x2800AC54,0x2800AC58,0x2800AC5C,
				0x2800AC60,0x2800AC64,0x2800AC68,0x2800AC6C,
				0x2800AC70,0x2800AC74,0x2800AC78,0x2800AC7C,
				0x2800AC80,0x2800AC84,0x2800AC88,0x2800AC8C,
				0x2800AC90,0x2800AC94,0x2800AC98,0x2800AC9C,
				0x2800ACA0,0x2800ACA4,0x2800ACA8,0x2800ACAC,
				0x2800ACB0,0x2800ACB4,0x2800ACB8,0x2800ACBC,
				0x2800ACC0,0x2800ACC4,0x2800ACC8,0x2800ACCC,
			},
			{
				0x2800AD10,0x2800AD14,0x2800AD18,0x2800AD1C,
				0x2800AD20,0x2800AD24,0x2800AD28,0x2800AD2C,
				0x2800AD30,0x2800AD34,0x2800AD38,0x2800AD3C,
				0x2800AD40,0x2800AD44,0x2800AD48,0x2800AD4C,
				0x2800AD50,0x2800AD54,0x2800AD58,0x2800AD5C,
				0x2800AD60,0x2800AD64,0x2800AD68,0x2800AD6C,
				0x2800AD70,0x2800AD74,0x2800AD78,0x2800AD7C,
				0x2800AD80,0x2800AD84,0x2800AD88,0x2800AD8C,
				0x2800AD90,0x2800AD94,0x2800AD98,0x2800AD9C,
				0x2800ADA0,0x2800ADA4,0x2800ADA8,0x2800ADAC,
				0x2800ADB0,0x2800ADB4,0x2800ADB8,0x2800ADBC,
				0x2800ADC0,0x2800ADC4,0x2800ADC8,0x2800ADCC,
			},
			{
				0x2800AE10,0x2800AE14,0x2800AE18,0x2800AE1C,
				0x2800AE20,0x2800AE24,0x2800AE28,0x2800AE2C,
				0x2800AE30,0x2800AE34,0x2800AE38,0x2800AE3C,
				0x2800AE40,0x2800AE44,0x2800AE48,0x2800AE4C,
				0x2800AE50,0x2800AE54,0x2800AE58,0x2800AE5C,
				0x2800AE60,0x2800AE64,0x2800AE68,0x2800AE6C,
				0x2800AE70,0x2800AE74,0x2800AE78,0x2800AE7C,
				0x2800AE80,0x2800AE84,0x2800AE88,0x2800AE8C,
				0x2800AE90,0x2800AE94,0x2800AE98,0x2800AE9C,
				0x2800AEA0,0x2800AEA4,0x2800AEA8,0x2800AEAC,
				0x2800AEB0,0x2800AEB4,0x2800AEB8,0x2800AEBC,
				0x2800AEC0,0x2800AEC4,0x2800AEC8,0x2800AECC,
			},
			{
				0x2800AF10,0x2800AF14,0x2800AF18,0x2800AF1C,
				0x2800AF20,0x2800AF24,0x2800AF28,0x2800AF2C,
				0x2800AF30,0x2800AF34,0x2800AF38,0x2800AF3C,
				0x2800AF40,0x2800AF44,0x2800AF48,0x2800AF4C,
				0x2800AF50,0x2800AF54,0x2800AF58,0x2800AF5C,
				0x2800AF60,0x2800AF64,0x2800AF68,0x2800AF6C,
				0x2800AF70,0x2800AF74,0x2800AF78,0x2800AF7C,
				0x2800AF80,0x2800AF84,0x2800AF88,0x2800AF8C,
				0x2800AF90,0x2800AF94,0x2800AF98,0x2800AF9C,
				0x2800AFA0,0x2800AFA4,0x2800AFA8,0x2800AFAC,
				0x2800AFB0,0x2800AFB4,0x2800AFB8,0x2800AFBC,
				0x2800AFC0,0x2800AFC4,0x2800AFC8,0x2800AFCC,
			},
		},
		// E_IM_PRO_BLOCK_TYPE_SRO
		{{0}},
		// E_IM_PRO_BLOCK_TYPE_B2B
		{{0}},
		// E_IM_PRO_BLOCK_TYPE_STAT
		{{0}},
		// E_IM_PRO_BLOCK_TYPE_PAS
		{
			{
				0x28868210,0x28868214,0x28868218,0x2886821C,
				0x28868220,0x28868224,0x28868228,0x2886822C,
				0x28868230,0x28868234,0x28868238,0x2886823C,
				0x28868240,0x28868244,0x28868248,0x2886824C,
				0x28868250,0x28868254,0x28868258,0x2886825C,
				0x28868260,0x28868264,0x28868268,0x2886826C,
				0x28868270,0x28868274,0x28868278,0x2886827C,
				0x28868280,0x28868284,0x28868288,0x2886828C,
				0x28868290,0x28868294,0x28868298,0x2886829C,
				0x288682A0,0x288682A4,0x288682A8,0x288682AC,
				0x288682B0,0x288682B4,0x288682B8,0x288682BC,
				0x288682C0,0x288682C4,0x288682C8,0x288682CC,
			},
			{0},
			{0},
			{0},
		},
	},
	{{{0}}},
	{{{0}}},
};

static const T_IM_PRO_RDMA_PZSFT_ADDR gIM_PRO_PZSFT_Addr[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_PZSFT_CH_MAX] = {
	{
		{ 0x28409004 },
		{ 0x28409204 },
		{ 0x28409604 },
		{ 0x28409904 },
		{ 0x28410304 },
		{ 0x28410804 },
		{ 0x28410904 },
	},
	{
		{ 0x28509004 },
		{ 0x28509204 },
		{ 0x28509604 },
		{ 0x28509904 },
		{ 0x28510304 },
		{ 0x28510804 },
		{ 0x28510904 },
	},
	{
		{ 0x28609004 },
		{ 0x28609204 },
		{ 0x28609604 },
		{ 0x28609904 },
		{ 0x28610304 },
		{ 0x28610804 },
		{ 0x28610904 },
	},
};

static const T_IM_PRO_RDMA_PGAIN_ADDR gIM_PRO_PGAIN_Addr[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][D_IM_PRO_PGAIN_CNT] = {
	{
		// E_IM_PRO_BLOCK_TYPE_SEN
		{{0}},
		// E_IM_PRO_BLOCK_TYPE_SRO
		{
			{
				0x28408604,0x28408608,0x2840860C,0x28408610,
				0x28408614,0x28408618,0x2840861C,0x28408620,
				0x28408624,
			},
			{0},
			{0},
		},
		// E_IM_PRO_BLOCK_TYPE_B2B
		{
			{0},
			{
				0x28410204,0x28410208,0x2841020C,0x28410210,
				0x28410214,0x28410218,0x2841021C,0x28410220,
				0x28410224,
			},
			{
				0x28410B04,0x28410B08,0x28410B0C,0x28410B10,
				0x28410B14,0x28410B18,0x28410B1C,0x28410B20,
				0x28410B24,
			},
		},
		// E_IM_PRO_BLOCK_TYPE_STAT
		{{0}},
		// E_IM_PRO_BLOCK_TYPE_PAS
		{
			{
				0x28868304,0x28868308,0x2886830C,0x28868310,
				0x28868314,0x28868318,0x2886831C,0x28868320,
				0x28868324,
			},
			{0},
			{0},
		},
	},
	{
		// E_IM_PRO_BLOCK_TYPE_SEN
		{{0}},
		// E_IM_PRO_BLOCK_TYPE_SRO
		{
			{
				0x28508604,0x28508608,0x2850860C,0x28508610,
				0x28508614,0x28508618,0x2850861C,0x28508620,
				0x28508624,
			},
			{0},
			{0},
		},
		// E_IM_PRO_BLOCK_TYPE_B2B
		{
			{0},
			{
				0x28510204,0x28510208,0x2851020C,0x28510210,
				0x28510214,0x28510218,0x2851021C,0x28510220,
				0x28510224,
			},
			{
				0x28510B04,0x28510B08,0x28510B0C,0x28510B10,
				0x28510B14,0x28510B18,0x28510B1C,0x28510B20,
				0x28510B24,
			},
		},
		// E_IM_PRO_BLOCK_TYPE_STAT
		{{0}},
		// E_IM_PRO_BLOCK_TYPE_PAS
		{
			{0},
			{0},
			{0},
		},
	},
	{
		// E_IM_PRO_BLOCK_TYPE_SEN
		{{0}},
		// E_IM_PRO_BLOCK_TYPE_SRO
		{
			{
				0x28608604,0x28608608,0x2860860C,0x28608610,
				0x28608614,0x28608618,0x2860861C,0x28608620,
				0x28608624,
			},
			{0},
			{0},
		},
		// E_IM_PRO_BLOCK_TYPE_B2B
		{
			{0},
			{
				0x28610204,0x28610208,0x2861020C,0x28610210,
				0x28610214,0x28610218,0x2861021C,0x28610220,
				0x28610224,
			},
			{
				0x28610B04,0x28610B08,0x28610B0C,0x28610B10,
				0x28610B14,0x28610B18,0x28610B1C,0x28610B20,
				0x28610B24,
			},
		},
		// E_IM_PRO_BLOCK_TYPE_STAT
		{{0}},
		// E_IM_PRO_BLOCK_TYPE_PAS
		{
			{0},
			{0},
			{0},
		},
	},
};

static const T_IM_PRO_RDMA_P2M_KNEE_TBL_ADDR	gIM_PRO_P2M_Knee_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][E_IM_PRO_P2M_MAX] = {
	{
		{
			{ 0x29000000 },
			{ 0x29000400 },
			{ 0x29000800 },
			{ 0x29000C00 },
			{ 0x29001000 },
			{ 0x29001400 },
			{ 0x29001800 },
			{ 0x29001C00 },
		},
		{
			{ 0x29440400 },
			{ 0x29440800 },
			{ 0x29440C00 },
			{ 0x29441000 },
			{ 0x29441400 },
			{ 0x29441800 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29481000 },
			{ 0x29481400 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29814800 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
	},
	{
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29540400 },
			{ 0x29540800 },
			{ 0x29540C00 },
			{ 0x29541000 },
			{ 0x29541400 },
			{ 0x29541800 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29581000 },
			{ 0x29581400 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
	},
	{
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29640400 },
			{ 0x29640800 },
			{ 0x29640C00 },
			{ 0x29641000 },
			{ 0x29641400 },
			{ 0x29641800 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29681000 },
			{ 0x29681400 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
	},
};

static const T_IM_PRO_RDMA_M2P_DEKNEE_TBL_ADDR	gIM_PRO_M2P_Deknee_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][E_IM_PRO_M2P_MAX] = {
	{
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29441C00 },
			{ 0x29442000 },
			{ 0x29442400 },
			{ 0x29442800 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29481800 },
			{ 0x29481C00 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29814C00 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
	},
	{
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29541C00 },
			{ 0x29542000 },
			{ 0x29542400 },
			{ 0x29542800 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29581800 },
			{ 0x29581C00 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
	},
	{
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29641C00 },
			{ 0x29642000 },
			{ 0x29642400 },
			{ 0x29642800 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x29681800 },
			{ 0x29681C00 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
		{
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
			{ 0x00000000 },
		},
	},
};

static	volatile	UCHAR	gIM_PRO_PWch_AXI_Response[D_IM_PRO_PIPE_NUM][E_IM_PRO_BLOCK_TYPE_MAX][E_IM_PRO_PWCH_MAX]	= {{{0}}};
// AFPB
static	volatile	T_IM_PRO_AFPB_BUF_INFO	gIM_PRO_AFPB_Buffer_Info[D_IM_PRO_PIPE_NUM][D_IM_PRO_SROTOP_AFPB_CH_NUM];
// Buffer management
// PWCH
static	volatile	T_IM_PRO_STAT_PWCH_BUF_INFO	gIM_PRO_STAT_Buffer_Info[D_IM_PRO_STAT_AEAWB_CH_NUM + D_IM_PRO_STAT_FLCK_CH_NUM];
//static	volatile	T_IM_PRO_ADDR_MNG			gIM_PRO_PWchAddrMng[E_IM_PRO_UNIT_NUM_MAX][E_IM_PRO_BLOCK_TYPE_MAX][E_IM_PRO_PWCH_MAX] = { { { { { 0 } } } } };
static void im_pro_common_con_constructor(ImProCommonCon *self)
{
	ImProCommonConPrivate *priv = IM_PRO_COMMON_CON_GET_PRIVATE(self);
	priv-> a = 0;
}

static void im_pro_common_con_destructor(ImProCommonCon *self)
{
	ImProCommonConPrivate *priv = IM_PRO_COMMON_CON_GET_PRIVATE(self);
	priv-> a = 0;
}
VOID im_pro_comm_update_obd_result( UINT32 blob_num, UINT32 ch )
{
	gIM_PRO_OBD_Buffer_Info[blob_num][ch].data_addr = &gIM_PRO_OBD_Buffer_Info[blob_num][ch].data_table[ gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur ];

	im_pro_common_fig_im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );	// Dd_Top_Start_Clock
	gIM_PRO_OBD_Buffer_Info[blob_num][ch].data_table[ gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur ].R	= IO_PRO.SEN.OBD[blob_num][ch].OBDCORE.OBDDATAR.bit.OBDDATAR;
	gIM_PRO_OBD_Buffer_Info[blob_num][ch].data_table[ gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur ].Gr	= IO_PRO.SEN.OBD[blob_num][ch].OBDCORE.OBDDATAGR.bit.OBDDATAGR;
	gIM_PRO_OBD_Buffer_Info[blob_num][ch].data_table[ gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur ].Gb	= IO_PRO.SEN.OBD[blob_num][ch].OBDCORE.OBDDATAGB.bit.OBDDATAGB;
	gIM_PRO_OBD_Buffer_Info[blob_num][ch].data_table[ gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur ].B	= IO_PRO.SEN.OBD[blob_num][ch].OBDCORE.OBDDATAB.bit.OBDDATAB;

	gIM_PRO_OBD_Buffer_Info[blob_num][ch].cnt_addr = &gIM_PRO_OBD_Buffer_Info[blob_num][ch].cnt_table[ gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur ];

	gIM_PRO_OBD_Buffer_Info[blob_num][ch].cnt_table[ gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur ].R	= IO_PRO.SEN.OBD[blob_num][ch].OBDCORE.OBDCNTR.bit.OBDCNTR;
	gIM_PRO_OBD_Buffer_Info[blob_num][ch].cnt_table[ gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur ].Gr	= IO_PRO.SEN.OBD[blob_num][ch].OBDCORE.OBDCNTGR.bit.OBDCNTGR;
	gIM_PRO_OBD_Buffer_Info[blob_num][ch].cnt_table[ gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur ].Gb	= IO_PRO.SEN.OBD[blob_num][ch].OBDCORE.OBDCNTGB.bit.OBDCNTGB;
	gIM_PRO_OBD_Buffer_Info[blob_num][ch].cnt_table[ gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur ].B	= IO_PRO.SEN.OBD[blob_num][ch].OBDCORE.OBDCNTB.bit.OBDCNTB;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );	// Dd_Top_Stop_Clock

	gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur++;
	if (gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur > gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.max){
		// Index Reset
		gIM_PRO_OBD_Buffer_Info[blob_num][ch].addr_index.cur = 0;
	}
}

VOID im_pro_comm_get_obd_data( UINT32 blob_num, UINT32 ch, T_IM_PRO_RGB4* data )
{
#ifdef CO_PARAM_CHECK
	if( data == NULL ) {
		Ddim_Assertion(("I:im_pro_comm_get_obd_data error. ch:%d data=NULL\n", ch));
		return;
	}
#endif
	Ddim_Print(("I:im_pro_comm_get_obd_data data_addr=0x%08lx\n", (ULONG)gIM_PRO_OBD_Buffer_Info[blob_num][ch].data_addr));
	im_pro_common_fig_im_pro_memcpy(NULL,data, (void *)gIM_PRO_OBD_Buffer_Info[blob_num][ch].data_addr, sizeof(T_IM_PRO_RGB4));
}

VOID im_pro_comm_get_obd_cnt( UINT32 blob_num, UINT32 ch, T_IM_PRO_RGB4* cnt )
{
#ifdef CO_PARAM_CHECK
	if( cnt == NULL ) {
		Ddim_Assertion(("I:im_pro_comm_get_obd_cnt error. ch:%d cnt=NULL\n", ch));
		return;
	}
#endif
	im_pro_common_fig_im_pro_memcpy(NULL,cnt, (void *)gIM_PRO_OBD_Buffer_Info[blob_num][ch].cnt_addr, sizeof(T_IM_PRO_RGB4));
}

VOID im_pro_comm_update_afpb_pwch_index( E_IM_PRO_UNIT_NUM unit_no, UINT32 ch )
{
	gIM_PRO_AFPB_Buffer_Info[unit_no][ch].last_addr = gIM_PRO_AFPB_Buffer_Info[unit_no][ch].current_addr;
	gIM_PRO_AFPB_Buffer_Info[unit_no][ch].addr_index.cur++;

	if (gIM_PRO_AFPB_Buffer_Info[unit_no][ch].addr_index.cur > gIM_PRO_AFPB_Buffer_Info[unit_no][ch].addr_index.max){
		// Index Reset
		gIM_PRO_AFPB_Buffer_Info[unit_no][ch].addr_index.cur = 0;
	}
	im_pro_common_fig_im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	IO_PRO.IMG_PIPE[unit_no].SRO.PWCH[ch].PWSA.bit.PWSA = gIM_PRO_AFPB_Buffer_Info[unit_no][ch].current_addr = gIM_PRO_AFPB_Buffer_Info[unit_no][ch].addr_table[gIM_PRO_AFPB_Buffer_Info[unit_no][ch].addr_index.cur];
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
}

INT32 Im_PRO_PWch_Set_Buf_Addr( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, T_IM_PRO_PWCH_INFO* pwch_info )
{
	PwchTbl* pwchTbl=pwch_tbl_get();
	UINT32 buff;

#ifdef CO_PARAM_CHECK
	if( pwch_info == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PWch_Set_Buf_Addr. error. pwch_info=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	 paok_ind(pwch_tbl_get(),   unit_no,  block_type,  ch);
	if ( (pwch_info->buffer_num < D_IM_PRO_PWCH_BUFFER_MIN) ||
	    	  (pwch_info->buffer_num > D_IM_PRO_PWCH_BUFFER_MAX)){
		Ddim_Assertion(("I:Im_PRO_PWch_Set_Buf_Addr. buffer over\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	if( block_type == E_IM_PRO_BLOCK_TYPE_STAT ) {
		gIM_PRO_STAT_Buffer_Info[ch].addr_index.max = (UCHAR)pwch_info->buffer_num - 1;
		gIM_PRO_STAT_Buffer_Info[ch].addr_index.cur = 0;
		for (buff = 0; buff < D_IM_PRO_PWCH_BUFFER_MAX; buff ++){
			/* copy to bayer top address */
			if (buff < pwch_info->buffer_num){
				gIM_PRO_STAT_Buffer_Info[ch].addr_table[buff] = pwch_info->buff_addr[buff];
			}
			else{
				gIM_PRO_STAT_Buffer_Info[ch].addr_table[buff] = 0;
			}
		}
		gIM_PRO_STAT_Buffer_Info[ch].current_addr = pwch_info->buff_addr[0];
	}
	else {
		pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].buff_index.max = (UCHAR)pwch_info->buffer_num - 1;
		pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].buff_index.cur = 0;
		for (buff = 0; buff < D_IM_PRO_PWCH_BUFFER_MAX; buff ++){
			/* copy to bayer top address */
			if (buff < pwch_info->buffer_num){
				pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].top_addr[buff] = pwch_info->buff_addr[buff];
			}
			else{
				pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].top_addr[buff] = 0;
			}
		}

		// AFPB buffer
		if( ( (block_type == E_IM_PRO_BLOCK_TYPE_SRO) && ( ( ch >= E_IM_PRO_PWCH_2 ) && ( ch <= E_IM_PRO_PWCH_5 ) ) ) ) {
			gIM_PRO_AFPB_Buffer_Info[unit_no][ch].current_addr = pwch_info->buff_addr[0];
		}
	}

	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	paok_and(pwch_tbl_get(),   unit_no,  block_type,  ch,  pwch_info);
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );

	return D_DDIM_OK;
}

VOID im_pro_comm_update_stat_pwch_index(UINT32 ch)
{
	gIM_PRO_STAT_Buffer_Info[ch].last_addr = gIM_PRO_STAT_Buffer_Info[ch].current_addr;
	gIM_PRO_STAT_Buffer_Info[ch].addr_index.cur++;

	if (gIM_PRO_STAT_Buffer_Info[ch].addr_index.cur > gIM_PRO_STAT_Buffer_Info[ch].addr_index.max){
		// Index Reset
		gIM_PRO_STAT_Buffer_Info[ch].addr_index.cur = 0;
	}
	im_pro_common_fig_im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Start_Clock
	IO_PRO.STAT.PWCH[ch].PWSA.bit.PWSA = gIM_PRO_STAT_Buffer_Info[ch].current_addr = gIM_PRO_STAT_Buffer_Info[ch].addr_table[gIM_PRO_STAT_Buffer_Info[ch].addr_index.cur];
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );	// Dd_Top_Stop_Clock
}

ULONG im_pro_comm_get_stat_cur_data_addr( UINT32 ch )
{
	return gIM_PRO_STAT_Buffer_Info[ch].current_addr;
}

ULONG im_pro_comm_get_stat_last_data_addr( UINT32 ch )
{
	return gIM_PRO_STAT_Buffer_Info[ch].last_addr;
}

ULONG Im_PRO_PWch_Get_Buf_Data( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch )
{
	PwchTbl* pwchTbl=pwch_tbl_get();
#ifdef CO_PARAM_CHECK
	 paok_bnd(pwch_tbl_get(),   unit_no,  block_type,  ch);
#endif
	return pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].buff_last_addr;
}

//#pragma inline Im_PRO_PWch_Update_Bayer_Index
INT32 Im_PRO_PWch_Update_Buf_Index( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch )
{
	PwchTbl* pwchTbl=pwch_tbl_get();
#ifdef CO_PARAM_CHECK
	paok_cnd(pwch_tbl_get(),   unit_no,  block_type,  ch);
#endif

	// SDRAM 1Frame Set Completion Address
	pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].buff_last_addr = pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].top_addr[pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].buff_index.cur];

	// RAM Area Index Check
	if (pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].buff_index.max > 0){
		if (pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].buff_index.cur < pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].buff_index.max){
			// Bayer Address Table Index Update
			pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].buff_index.cur++;
		}
		else{
			pwchTbl->gIM_PRO_PWchAddrMng[unit_no][block_type][ch].buff_index.cur = 0;
		}
	}
	else{
		return D_DDIM_OK;
	}

	im_pro_common_fig_im_pro_on_pclk( unit_no, im_pro_convert_clk_type( block_type ) );
	// Next Field Storing Address Set
	 paok_dnd(pwch_tbl_get(),   unit_no,  block_type,  ch);
	im_pro_off_pclk( unit_no, im_pro_convert_clk_type( block_type ) );

	return D_DDIM_OK;
}

INT32 Im_PRO_Get_RdmaAddr_LNR_Cntl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_LNR_CH ch, const T_IM_PRO_RDMA_LNR_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_Get_RdmaAddr_LNR_Cntl. error. addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &(gIM_PRO_LNR_Addr[unit_no][block_type][ch]);

	return D_DDIM_OK;
}

INT32 Im_PRO_Get_RdmaAddr_PZSFT_Cntl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_PZSFT_CH ch, const T_IM_PRO_RDMA_PZSFT_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_Get_RdmaAddr_PZSFT_Cntl. error. addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &(gIM_PRO_PZSFT_Addr[unit_no][ch]);

	return D_DDIM_OK;
}

INT32 Im_PRO_Get_RdmaAddr_PGAIN_Cntl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PGAIN_SELECT select, const T_IM_PRO_RDMA_PGAIN_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_Get_RdmaAddr_PGAIN_Cntl. error. addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &(gIM_PRO_PGAIN_Addr[unit_no][block_type][select]);

	return D_DDIM_OK;
}

INT32 Im_PRO_Get_RdmaAddr_P2M_Knee_Tbl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_P2M_CH ch, const T_IM_PRO_RDMA_P2M_KNEE_TBL_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_Get_RdmaAddr_P2M_Knee_Tbl. error. addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &gIM_PRO_P2M_Knee_Reg_Ptr_Tbl[unit_no][block_type][ch];

	return D_DDIM_OK;
}

INT32 Im_PRO_Get_RdmaAddr_M2P_Deknee_Tbl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_P2M_CH ch, const T_IM_PRO_RDMA_M2P_DEKNEE_TBL_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:Im_PRO_Get_RdmaAddr_M2P_Deknee_Tbl. error. addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &gIM_PRO_M2P_Deknee_Reg_Ptr_Tbl[unit_no][block_type][ch];

	return D_DDIM_OK;
}

VOID im_pro_comm_set_pwch_axi_response( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, UCHAR axi_resp )
{
	gIM_PRO_PWch_AXI_Response[unit_no][block_type][ch] = axi_resp;
}

INT32 Im_PRO_PWch_Get_AXI_Response( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_BLOCK_TYPE block_type, E_IM_PRO_PWCH ch, UCHAR* axi_response )
{
#ifdef CO_PARAM_CHECK
	if( axi_response == NULL ) {
		Ddim_Assertion(("I:Im_PRO_PWch_Get_AXI_Response. error. axi_response=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*axi_response = gIM_PRO_PWch_AXI_Response[unit_no][block_type][ch];
	return D_DDIM_OK;
}

ImProCommonCon *im_pro_common_con_new(void)
{
	ImProCommonCon* self = k_object_new_with_private(IM_TYPE_PRO_COMMON_CON,sizeof(ImProCommonConPrivate));
	return self;
}
