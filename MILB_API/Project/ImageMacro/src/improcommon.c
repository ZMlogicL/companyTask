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
#include "jdspro.h"
#include "im_pro.h"
#include "dd_top.h"
#include "improcommon.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImProCommom, im_pro_commom);
#define IM_PRO_COMMON_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImProCommomPrivate, IM_TYPE_PRO_COMMON))

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_IMAGE_CLOCK)
#define	CO_ACT_PRO_CLOCK
#endif
#if defined(CO_ACT_PCLOCK) || defined(CO_ACT_IMAGE_PCLOCK)
#define	CO_ACT_PRO_PCLOCK
#endif
#if defined(CO_ACT_HCLOCK) || defined(CO_ACT_IMAGE_HCLOCK)
#define	CO_ACT_PRO_HCLOCK
#endif
#if defined(CO_ACT_ICLOCK) || defined(CO_ACT_IMAGE_ICLOCK)
#define	CO_ACT_PRO_ICLOCK
#endif

#define CO_USE_BUZ

#ifdef CO_ACT_PRO_CLOCK
#define D_IM_PRO_SEN_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP1())

#define D_IM_PRO_SEN_CLK_REG_BIT	(D_DD_TOP_SENCK_BIT)
#endif

#ifdef CO_ACT_PRO_PCLOCK
#define D_IM_PRO_SEN_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP1())

#define D_IM_PRO_SEN_PCLK_REG_BIT	(D_DD_TOP_SENAP_BIT)
#endif

#ifdef CO_ACT_PRO_HCLOCK
#define D_IM_PRO_SEN_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP1())

#define D_IM_PRO_SEN_HCLK_REG_BIT	(D_DD_TOP_SENAH_BIT)
#endif

#ifdef CO_ACT_PRO_ICLOCK
#define D_IM_PRO_SEN_XCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP1())

#define D_IM_PRO_SEN_XCLK_REG_BIT	(D_DD_TOP_SENAX_BIT)
#endif

#ifdef CO_ACT_PRO_CLOCK
#define D_IM_PRO_SRO1_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())
#define D_IM_PRO_SRO1_CLK2_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())

#define D_IM_PRO_SRO1_CLK_REG_BIT	(D_DD_TOP_SRO1CK_BIT)
#define D_IM_PRO_SRO1_CLK2_REG_BIT	(D_DD_TOP_SRO1CK_2_BIT)
#endif

#ifdef CO_ACT_PRO_PCLOCK
#define D_IM_PRO_SRO1_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())

#define D_IM_PRO_SRO1_PCLK_REG_BIT	(D_DD_TOP_SRO1AP_BIT)
#endif

#ifdef CO_ACT_PRO_HCLOCK
#define D_IM_PRO_SRO1_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())

#define D_IM_PRO_SRO1_HCLK_REG_BIT	(D_DD_TOP_SRO1AH_BIT)
#endif

#ifdef CO_ACT_PRO_ICLOCK
#define D_IM_PRO_SRO1_XCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())

#define D_IM_PRO_SRO1_XCLK_REG_BIT	(D_DD_TOP_SRO1AX_BIT)
#endif

#ifdef CO_ACT_PRO_CLOCK
#define D_IM_PRO_SRO2_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())
#define D_IM_PRO_SRO2_CLK2_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())

#define D_IM_PRO_SRO2_CLK_REG_BIT	(D_DD_TOP_SRO2CK_BIT)
#define D_IM_PRO_SRO2_CLK2_REG_BIT	(D_DD_TOP_SRO2CK_2_BIT)
#endif

#ifdef CO_ACT_PRO_PCLOCK
#define D_IM_PRO_SRO2_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())

#define D_IM_PRO_SRO2_PCLK_REG_BIT	(D_DD_TOP_SRO2AP_BIT)
#endif

#ifdef CO_ACT_PRO_HCLOCK
#define D_IM_PRO_SRO2_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())

#define D_IM_PRO_SRO2_HCLK_REG_BIT	(D_DD_TOP_SRO2AH_BIT)
#endif

#ifdef CO_ACT_PRO_ICLOCK
#define D_IM_PRO_SRO2_XCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())

#define D_IM_PRO_SRO2_XCLK_REG_BIT	(D_DD_TOP_SRO2AX_BIT)
#endif

#ifdef CO_ACT_PRO_CLOCK
#define D_IM_PRO_B2B1_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())

#define D_IM_PRO_B2B1_CLK_REG_BIT	(D_DD_TOP_B2B1CK_BIT)
#endif

#ifdef CO_ACT_PRO_PCLOCK
#define D_IM_PRO_B2B1_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())

#define D_IM_PRO_B2B1_PCLK_REG_BIT	(D_DD_TOP_B2B1AP_BIT)
#endif

#ifdef CO_ACT_PRO_HCLOCK
#define D_IM_PRO_B2B1_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())

#define D_IM_PRO_B2B1_HCLK_REG_BIT	(D_DD_TOP_B2B1AH_BIT)
#endif

#ifdef CO_ACT_PRO_ICLOCK
#define D_IM_PRO_B2B1_XCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())

#define D_IM_PRO_B2B1_XCLK_REG_BIT	(D_DD_TOP_B2B1AX_BIT)
#endif

#ifdef CO_ACT_PRO_CLOCK
#define D_IM_PRO_B2B2_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())

#define D_IM_PRO_B2B2_CLK_REG_BIT	(D_DD_TOP_B2B2CK_BIT)
#endif

#ifdef CO_ACT_PRO_PCLOCK
#define D_IM_PRO_B2B2_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())

#define D_IM_PRO_B2B2_PCLK_REG_BIT	(D_DD_TOP_B2B2AP_BIT)
#endif

#ifdef CO_ACT_PRO_HCLOCK
#define D_IM_PRO_B2B2_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())

#define D_IM_PRO_B2B2_HCLK_REG_BIT	(D_DD_TOP_B2B2AH_BIT)
#endif

#ifdef CO_ACT_PRO_ICLOCK
#define D_IM_PRO_B2B2_XCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())

#define D_IM_PRO_B2B2_XCLK_REG_BIT	(D_DD_TOP_B2B2AX_BIT)
#endif

#ifdef CO_ACT_PRO_PCLOCK
#define D_IM_PRO_STAT_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP14())

#define D_IM_PRO_STAT_PCLK_REG_BIT	(D_DD_TOP_STATAP_BIT)
#endif

#ifdef CO_ACT_PRO_HCLOCK
#define D_IM_PRO_STAT_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP14())

#define D_IM_PRO_STAT_HCLK_REG_BIT	(D_DD_TOP_STATAH_BIT)
#endif

#ifdef CO_ACT_PRO_ICLOCK
#define D_IM_PRO_STAT_XCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP14())

#define D_IM_PRO_STAT_XCLK_REG_BIT	(D_DD_TOP_STATAX_BIT)
#endif

#ifdef CO_ACT_PRO_CLOCK
#define D_IM_PRO_PAS_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP14())

#define D_IM_PRO_PAS_CLK_REG_BIT	(D_DD_TOP_PASCK_BIT)
#endif

#ifdef CO_ACT_PRO_PCLOCK
#define D_IM_PRO_PAS_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP14())

#define D_IM_PRO_PAS_PCLK_REG_BIT	(D_DD_TOP_STATAP_BIT)	// share with STAT
#endif

#ifdef CO_ACT_PRO_HCLOCK
#define D_IM_PRO_PAS_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP14())

#define D_IM_PRO_PAS_HCLK_REG_BIT	(D_DD_TOP_STATAH_BIT)	// share with STAT
#endif

#ifdef CO_ACT_PRO_ICLOCK
#define D_IM_PRO_PAS_XCLK_REG_ADDR	(&IO_CHIPTOP.CLKSTOP_D.word)

#define D_IM_PRO_PAS_XCLK_REG_BIT	(D_DD_TOP_STATAX_BIT)	// share with STAT
#endif

typedef struct {
	ULONG							lock;
	ULONG							dummy[ ( 64 / 4 ) - 1 ];
} T_IM_PRO_SPIN_LOCK_VAR;

struct _ImProCommomPrivate
{
	int a;
};

static	volatile	T_IM_PRO_SPIN_LOCK_VAR gIM_PRO_Spin_Lock[E_IM_PRO_BOTH_UNIT][E_IM_PRO_CLK_BLOCK_TYPE_MAX] __attribute__((section(".LOCK_SECTION"), aligned(64)));
#ifdef CO_ACT_PRO_CLOCK
static	volatile	UCHAR	gIM_SEN_CLK_Ctrl_Cnt = 0;
static	volatile	UCHAR	gIM_SRO_CLK_Ctrl_Cnt[2] = { 0 };
static	volatile	UCHAR	gIM_SRO2_CLK_Ctrl_Cnt[2] = { 0 };
static	volatile	UCHAR	gIM_B2B_CLK_Ctrl_Cnt[2] = { 0 };
static	volatile	UCHAR	gIM_PAS_CLK_Ctrl_Cnt = 0;
static	volatile	UCHAR	gIM_STAT_CLK_Ctrl_Cnt = 0;

static	volatile	T_IM_PRO_CLK_REG_INFO gIM_Drive_Clk_Info[ E_IM_PRO_BOTH_UNIT ][ E_IM_PRO_CLK_BLOCK_TYPE_MAX ] = {
	{
		{	D_IM_PRO_SEN_CLK_REG_ADDR,		D_IM_PRO_SEN_CLK_REG_BIT,	&gIM_SEN_CLK_Ctrl_Cnt		},	// SEN
		{	D_IM_PRO_SRO1_CLK_REG_ADDR,		D_IM_PRO_SRO1_CLK_REG_BIT,	&gIM_SRO_CLK_Ctrl_Cnt[0]	},	// SRO
		{	D_IM_PRO_SRO1_CLK2_REG_ADDR,	D_IM_PRO_SRO1_CLK2_REG_BIT,	&gIM_SRO2_CLK_Ctrl_Cnt[0]	},	// SRO2
		{	D_IM_PRO_B2B1_CLK_REG_ADDR,		D_IM_PRO_B2B1_CLK_REG_BIT,	&gIM_B2B_CLK_Ctrl_Cnt[0]	},	// B2B
		{	0,								0,							0							},	// STAT
		{	0,								0,							0							},	// PAS
	},
	{
		{	0,								0,							0							},	// SEN
		{	D_IM_PRO_SRO2_CLK_REG_ADDR,		D_IM_PRO_SRO2_CLK_REG_BIT,	&gIM_SRO_CLK_Ctrl_Cnt[1]	},	// SRO
		{	D_IM_PRO_SRO2_CLK2_REG_ADDR,	D_IM_PRO_SRO2_CLK2_REG_BIT,	&gIM_SRO2_CLK_Ctrl_Cnt[1]	},	// SRO2
		{	D_IM_PRO_B2B2_CLK_REG_ADDR,		D_IM_PRO_B2B2_CLK_REG_BIT,	&gIM_B2B_CLK_Ctrl_Cnt[1]	},	// B2B
		{	0,								0,							0							},	// STAT
		{	0,								0,							0							},	// PAS
	},
};
#endif
#ifdef CO_ACT_PRO_PCLOCK
static	volatile	UCHAR	gIM_SEN_PCLK_Ctrl_Cnt = 0;
static	volatile	UCHAR	gIM_SRO_PCLK_Ctrl_Cnt[2] = { 0 };
static	volatile	UCHAR	gIM_B2B_PCLK_Ctrl_Cnt[2] = { 0 };
static	volatile	UCHAR	gIM_PAS_PCLK_Ctrl_Cnt = 0;
static	volatile	UCHAR	gIM_STAT_PCLK_Ctrl_Cnt = 0;
static	volatile	T_IM_PRO_CLK_REG_INFO gIM_Pclk_Info[ E_IM_PRO_BOTH_UNIT ][ E_IM_PRO_CLK_BLOCK_TYPE_MAX ] = {
	{
		{	D_IM_PRO_SEN_PCLK_REG_ADDR,		D_IM_PRO_SEN_PCLK_REG_BIT,		&gIM_SEN_PCLK_Ctrl_Cnt		},	// SEN
		{	D_IM_PRO_SRO1_PCLK_REG_ADDR,	D_IM_PRO_SRO1_PCLK_REG_BIT,		&gIM_SRO_PCLK_Ctrl_Cnt[0]	},	// SRO
		{	0,								0,								0							},	// SRO2
		{	D_IM_PRO_B2B1_PCLK_REG_ADDR,	D_IM_PRO_B2B1_PCLK_REG_BIT,		&gIM_B2B_PCLK_Ctrl_Cnt[0]	},	// B2B
		{	D_IM_PRO_STAT_PCLK_REG_ADDR,	D_IM_PRO_STAT_PCLK_REG_BIT,		&gIM_STAT_PCLK_Ctrl_Cnt		},	// STAT
		{	D_IM_PRO_STAT_PCLK_REG_ADDR,	D_IM_PRO_STAT_PCLK_REG_BIT,		&gIM_STAT_PCLK_Ctrl_Cnt		},	// PAS (shared /w STAT)
	},
	{
		{	0,								0,								0							},	// SEN
		{	D_IM_PRO_SRO2_PCLK_REG_ADDR,	D_IM_PRO_SRO2_PCLK_REG_BIT,		&gIM_SRO_PCLK_Ctrl_Cnt[1]	},	// SRO
		{	0,								0,								0							},	// SRO2
		{	D_IM_PRO_B2B2_PCLK_REG_ADDR,	D_IM_PRO_B2B2_PCLK_REG_BIT,		&gIM_B2B_PCLK_Ctrl_Cnt[1]	},	// B2B
		{	0,								0,								0							},	// STAT
		{	0,								0,								0							},	// PAS
	},
};
#endif
#ifdef CO_ACT_PRO_HCLOCK
static	volatile	UCHAR	gIM_SEN_HCLK_Ctrl_Cnt = 0;
static	volatile	UCHAR	gIM_SRO_HCLK_Ctrl_Cnt[2] = { 0 };
static	volatile	UCHAR	gIM_B2B_HCLK_Ctrl_Cnt[2] = { 0 };
static	volatile	UCHAR	gIM_PAS_HCLK_Ctrl_Cnt = 0;
static	volatile	UCHAR	gIM_STAT_HCLK_Ctrl_Cnt = 0;
static	volatile	T_IM_PRO_CLK_REG_INFO gIM_Hclk_Info[ E_IM_PRO_BOTH_UNIT ][ E_IM_PRO_CLK_BLOCK_TYPE_MAX ] = {
	{
		{	D_IM_PRO_SEN_HCLK_REG_ADDR,		D_IM_PRO_SEN_HCLK_REG_BIT,		&gIM_SEN_HCLK_Ctrl_Cnt		},	// SEN
		{	D_IM_PRO_SRO1_HCLK_REG_ADDR,	D_IM_PRO_SRO1_HCLK_REG_BIT,		&gIM_SRO_HCLK_Ctrl_Cnt[0]	},	// SRO
		{	0,								0,								0							},	// SRO2
		{	D_IM_PRO_B2B1_HCLK_REG_ADDR,	D_IM_PRO_B2B1_HCLK_REG_BIT,		&gIM_B2B_HCLK_Ctrl_Cnt[0]	},	// B2B
		{	D_IM_PRO_STAT_HCLK_REG_ADDR,	D_IM_PRO_STAT_HCLK_REG_BIT,		&gIM_STAT_HCLK_Ctrl_Cnt		},	// STAT
		{	D_IM_PRO_STAT_HCLK_REG_ADDR,	D_IM_PRO_STAT_HCLK_REG_BIT,		&gIM_STAT_HCLK_Ctrl_Cnt		},	// PAS (shared /w STAT)
	},
	{
		{	0,								0,								0							},	// SEN
		{	D_IM_PRO_SRO2_HCLK_REG_ADDR,	D_IM_PRO_SRO2_HCLK_REG_BIT,		&gIM_SRO_HCLK_Ctrl_Cnt[1]	},	// SRO
		{	0,								0,								0							},	// SRO2
		{	D_IM_PRO_B2B2_HCLK_REG_ADDR,	D_IM_PRO_B2B2_HCLK_REG_BIT,		&gIM_B2B_HCLK_Ctrl_Cnt[1]	},	// B2B
		{	0,								0,								0							},	// STAT
		{	0,								0,								0							},	// PAS
	},
};
#endif
#ifdef CO_ACT_PRO_ICLOCK
static	volatile	UCHAR	gIM_SEN_XCLK_Ctrl_Cnt = 0;
static	volatile	UCHAR	gIM_SRO_XCLK_Ctrl_Cnt[2] = { 0 };
static	volatile	UCHAR	gIM_B2B_XCLK_Ctrl_Cnt[2] = { 0 };
static	volatile	UCHAR	gIM_PAS_XCLK_Ctrl_Cnt = 0;
static	volatile	UCHAR	gIM_STAT_XCLK_Ctrl_Cnt = 0;
static	volatile	T_IM_PRO_CLK_REG_INFO gIM_Xclk_Info[ E_IM_PRO_BOTH_UNIT ][ E_IM_PRO_CLK_BLOCK_TYPE_MAX ] = {
	{
		{	D_IM_PRO_SEN_XCLK_REG_ADDR,		D_IM_PRO_SEN_XCLK_REG_BIT,		&gIM_SEN_XCLK_Ctrl_Cnt		},	// SEN
		{	D_IM_PRO_SRO1_XCLK_REG_ADDR,	D_IM_PRO_SRO1_XCLK_REG_BIT,		&gIM_SRO_XCLK_Ctrl_Cnt[0]	},	// SRO
		{	0,								0,								0							},	// SRO2
		{	D_IM_PRO_B2B1_XCLK_REG_ADDR,	D_IM_PRO_B2B1_XCLK_REG_BIT,		&gIM_B2B_XCLK_Ctrl_Cnt[0]	},	// B2B
		{	D_IM_PRO_STAT_XCLK_REG_ADDR,	D_IM_PRO_STAT_XCLK_REG_BIT,		&gIM_STAT_XCLK_Ctrl_Cnt		},	// STAT
		{	D_IM_PRO_STAT_XCLK_REG_ADDR,	D_IM_PRO_STAT_XCLK_REG_BIT,		&gIM_STAT_XCLK_Ctrl_Cnt		},	// PAS (shared /w STAT)
	},
	{
		{	0,								0,								0							},	// SEN
		{	D_IM_PRO_SRO2_XCLK_REG_ADDR,	D_IM_PRO_SRO2_XCLK_REG_BIT,		&gIM_SRO_XCLK_Ctrl_Cnt[1]	},	// SRO
		{	0,								0,								0							},	// SRO2
		{	D_IM_PRO_B2B2_XCLK_REG_ADDR,	D_IM_PRO_B2B2_XCLK_REG_BIT,		&gIM_B2B_XCLK_Ctrl_Cnt[1]	},	// B2B
		{	0,								0,								0							},	// STAT
		{	0,								0,								0							},	// PAS
	},
};
#endif

static void im_pro_commom_constructor(ImProCommom *self)
{
	ImProCommomPrivate *priv = IM_PRO_COMMON_GET_PRIVATE(self);
	priv-> a = 0;
}

static void im_pro_commom_destructor(ImProCommom *self)
{
	ImProCommomPrivate *priv = IM_PRO_COMMON_GET_PRIVATE(self);
	priv-> a = 0;
}

#ifdef CO_PRO_DEBUG_PRINT_FUNC
VOID Im_PRO_Print_ClockStatus( VOID )
{
#ifdef CO_ACT_PRO_CLOCK
	Ddim_Print(( ">>>>PRO CoreClock Unit1 Status\n" ));
	if( gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr != NULL ){
		Ddim_Print(( "SEN :reg %lu status %u\n",	(*(ULONG*)gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr & gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_bit),
													*gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_ctrl_cnt ));
	}
	if( gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr != NULL ){
		Ddim_Print(( "SRO :reg %lu status %u\n",	(*(ULONG*)gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr & gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_bit),
													*gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_ctrl_cnt ));
	}
	if( gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr != NULL ){
		Ddim_Print(( "SRO2:reg %lu status %u\n",	(*(ULONG*)gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr & gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_bit),
													*gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_ctrl_cnt ));
	}
	if( gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr != NULL ){
		Ddim_Print(( "B2B :reg %lu status %u\n",	(*(ULONG*)gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr & gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_bit),
													*gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_ctrl_cnt ));
	}
	if( gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr != NULL ){
		Ddim_Print(( "STAT:reg %lu status %u\n",	(*(ULONG*)gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr & gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_bit),
													*gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_ctrl_cnt ));
	}
	if( gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr != NULL ){
		Ddim_Print(( "PAS :reg %lu status %u\n",	(*(ULONG*)gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr & gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_bit),
													*gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_ctrl_cnt ));
	}
	Ddim_Print(( ">>>>PRO CoreClock Unit2 Status\n" ));
	if( gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr != NULL ){
		Ddim_Print(( "SEN :reg %lu status %u\n",	(*(ULONG*)gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr & gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_bit),
													*gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_ctrl_cnt ));
	}
	if( gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr != NULL ){
		Ddim_Print(( "SRO :reg %lu status %u\n",	(*(ULONG*)gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr & gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_bit),
													*gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_ctrl_cnt ));
	}
	if( gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr != NULL ){
		Ddim_Print(( "SRO2:reg %lu status %u\n",	(*(ULONG*)gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr & gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_bit),
													*gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_ctrl_cnt ));
	}
	if( gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr != NULL ){
		Ddim_Print(( "B2B :reg %lu status %u\n",	(*(ULONG*)gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr & gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_bit),
													*gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_ctrl_cnt ));
	}
	if( gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr != NULL ){
		Ddim_Print(( "STAT:reg %lu status %u\n",	(*(ULONG*)gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr & gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_bit),
													*gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_ctrl_cnt ));
	}
	if( gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr != NULL ){
		Ddim_Print(( "PAS :reg %lu status %u\n",	(*(ULONG*)gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr & gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_bit),
													*gIM_Drive_Clk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_ctrl_cnt ));
	}
#endif	// CO_ACT_PRO_CLOCK

#ifdef CO_ACT_PRO_PCLOCK
	Ddim_Print(( ">>>>PRO APB BusClock Unit1 Status\n" ));
	if( gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr != NULL ){
		Ddim_Print(( "SEN :reg %lu status %u\n",	(*(ULONG*)gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr & gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_bit),
													*gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_ctrl_cnt ));
	}
	if( gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr != NULL ){
		Ddim_Print(( "SRO :reg %lu status %u\n",	(*(ULONG*)gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr & gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_bit),
													*gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_ctrl_cnt ));
	}
	if( gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr != NULL ){
		Ddim_Print(( "SRO2:reg %lu status %u\n",	(*(ULONG*)gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr & gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_bit),
													*gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_ctrl_cnt ));
	}
	if( gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr != NULL ){
		Ddim_Print(( "B2B :reg %lu status %u\n",	(*(ULONG*)gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr & gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_bit),
													*gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_ctrl_cnt ));
	}
	if( gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr != NULL ){
		Ddim_Print(( "STAT:reg %lu status %u\n",	(*(ULONG*)gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr & gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_bit),
													*gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_ctrl_cnt ));
	}
	if( gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr != NULL ){
		Ddim_Print(( "PAS :reg %lu status %u\n",	(*(ULONG*)gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr & gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_bit),
													*gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_ctrl_cnt ));
	}
	Ddim_Print(( ">>>>PRO APB BusClock Unit2 Status\n" ));
	if( gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr != NULL ){
		Ddim_Print(( "SEN :reg %lu status %u\n",	(*(ULONG*)gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr & gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_bit),
													*gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_ctrl_cnt ));
	}
	if( gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr != NULL ){
		Ddim_Print(( "SRO :reg %lu status %u\n",	(*(ULONG*)gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr & gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_bit),
													*gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_ctrl_cnt ));
	}
	if( gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr != NULL ){
		Ddim_Print(( "SRO2:reg %lu status %u\n",	(*(ULONG*)gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr & gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_bit),
													*gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_ctrl_cnt ));
	}
	if( gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr != NULL ){
		Ddim_Print(( "B2B :reg %lu status %u\n",	(*(ULONG*)gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr & gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_bit),
													*gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_ctrl_cnt ));
	}
	if( gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr != NULL ){
		Ddim_Print(( "STAT:reg %lu status %u\n",	(*(ULONG*)gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr & gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_bit),
													*gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_ctrl_cnt ));
	}
	if( gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr != NULL ){
		Ddim_Print(( "PAS :reg %lu status %u\n",	(*(ULONG*)gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr & gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_bit),
													*gIM_Pclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_ctrl_cnt ));
	}
#endif	// CO_ACT_PRO_PCLOCK

#ifdef CO_ACT_PRO_HCLOCK
	Ddim_Print(( ">>>>PRO AHB BusClock Unit1 Status\n" ));
	if( gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr != NULL ){
		Ddim_Print(( "SEN :reg %lu status %u\n",	(*(ULONG*)gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr & gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_bit),
													*gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_ctrl_cnt ));
	}
	if( gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr != NULL ){
		Ddim_Print(( "SRO :reg %lu status %u\n",	(*(ULONG*)gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr & gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_bit),
													*gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_ctrl_cnt ));
	}
	if( gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr != NULL ){
		Ddim_Print(( "SRO2:reg %lu status %u\n",	(*(ULONG*)gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr & gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_bit),
													*gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_ctrl_cnt ));
	}
	if( gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr != NULL ){
		Ddim_Print(( "B2B :reg %lu status %u\n",	(*(ULONG*)gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr & gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_bit),
													*gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_ctrl_cnt ));
	}
	if( gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr != NULL ){
		Ddim_Print(( "STAT:reg %lu status %u\n",	(*(ULONG*)gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr & gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_bit),
													*gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_ctrl_cnt ));
	}
	if( gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr != NULL ){
		Ddim_Print(( "PAS :reg %lu status %u\n",	(*(ULONG*)gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr & gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_bit),
													*gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_ctrl_cnt ));
	}
	Ddim_Print(( ">>>>PRO AHB BusClock Unit2 Status\n" ));
	if( gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr != NULL ){
		Ddim_Print(( "SEN :reg %lu status %u\n",	(*(ULONG*)gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr & gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_bit),
													*gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_ctrl_cnt ));
	}
	if( gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr != NULL ){
		Ddim_Print(( "SRO :reg %lu status %u\n",	(*(ULONG*)gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr & gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_bit),
													*gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_ctrl_cnt ));
	}
	if( gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr != NULL ){
		Ddim_Print(( "SRO2:reg %lu status %u\n",	(*(ULONG*)gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr & gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_bit),
													*gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_ctrl_cnt ));
	}
	if( gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr != NULL ){
		Ddim_Print(( "B2B :reg %lu status %u\n",	(*(ULONG*)gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr & gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_bit),
													*gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_ctrl_cnt ));
	}
	if( gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr != NULL ){
		Ddim_Print(( "STAT:reg %lu status %u\n",	(*(ULONG*)gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr & gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_bit),
													*gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_ctrl_cnt ));
	}
	if( gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr != NULL ){
		Ddim_Print(( "PAS :reg %lu status %u\n",	(*(ULONG*)gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr & gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_bit),
													*gIM_Hclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_ctrl_cnt ));
	}
#endif	// CO_ACT_PRO_HCLOCK

#ifdef CO_ACT_PRO_ICLOCK
	Ddim_Print(( ">>>>PRO AXI BusClock Unit1 Status\n" ));
	if( gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr != NULL ){
		Ddim_Print(( "SEN :reg %lu status %u\n",	(*(ULONG*)gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr & gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_bit),
													*gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_ctrl_cnt ));
	}
	if( gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr != NULL ){
		Ddim_Print(( "SRO :reg %lu status %u\n",	(*(ULONG*)gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr & gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_bit),
													*gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_ctrl_cnt ));
	}
	if( gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr != NULL ){
		Ddim_Print(( "SRO2:reg %lu status %u\n",	(*(ULONG*)gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr & gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_bit),
													*gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_ctrl_cnt ));
	}
	if( gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr != NULL ){
		Ddim_Print(( "B2B :reg %lu status %u\n",	(*(ULONG*)gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr & gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_bit),
													*gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_ctrl_cnt ));
	}
	if( gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr != NULL ){
		Ddim_Print(( "STAT:reg %lu status %u\n",	(*(ULONG*)gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr & gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_bit),
													*gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_ctrl_cnt ));
	}
	if( gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr != NULL ){
		Ddim_Print(( "PAS :reg %lu status %u\n",	(*(ULONG*)gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr & gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_bit),
													*gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_1][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_ctrl_cnt ));
	}
	Ddim_Print(( ">>>>PRO AXI BusClock Unit2 Status\n" ));
	if( gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr != NULL ){
		Ddim_Print(( "SEN :reg %lu status %u\n",	(*(ULONG*)gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_addr & gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_bit),
													*gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SEN].reg_ctrl_cnt ));
	}
	if( gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr != NULL ){
		Ddim_Print(( "SRO :reg %lu status %u\n",	(*(ULONG*)gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_addr & gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_bit),
													*gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO].reg_ctrl_cnt ));
	}
	if( gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr != NULL ){
		Ddim_Print(( "SRO2:reg %lu status %u\n",	(*(ULONG*)gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_addr & gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_bit),
													*gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_SRO2].reg_ctrl_cnt ));
	}
	if( gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr != NULL ){
		Ddim_Print(( "B2B :reg %lu status %u\n",	(*(ULONG*)gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_addr & gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_bit),
													*gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_B2B].reg_ctrl_cnt ));
	}
	if( gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr != NULL ){
		Ddim_Print(( "STAT:reg %lu status %u\n",	(*(ULONG*)gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_addr & gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_bit),
													*gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_STAT].reg_ctrl_cnt ));
	}
	if( gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr != NULL ){
		Ddim_Print(( "PAS :reg %lu status %u\n",	(*(ULONG*)gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_addr & gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_bit),
													*gIM_Xclk_Info[E_IM_PRO_UNIT_NUM_2][E_IM_PRO_CLK_BLOCK_TYPE_PAS].reg_ctrl_cnt ));
	}
#endif	// CO_ACT_PRO_ICLOCK
}

#endif	// CO_PRO_DEBUG_PRINT_FUNC

ImProCommom *im_pro_commom_new(void)
{
	ImProCommom* self = k_object_new_with_private(IM_TYPE_PRO_COMMON,sizeof(ImProCommomPrivate));
	return self;
}








