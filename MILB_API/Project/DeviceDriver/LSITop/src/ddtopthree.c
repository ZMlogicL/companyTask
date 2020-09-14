/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-9-7 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/


#include <stdio.h>
#include "dd_arm.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#if 1    // special key control
#include "pmc.h"
#include <string.h>
#endif
#include "ddtopthree.h"


G_DEFINE_TYPE(DdTopthree, dd_topthree, G_TYPE_OBJECT);
#define DD_TOPTHREE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), DD_TYPE_TOPTHREE, DdTopthreePrivate));


struct _DdTopthreePrivate{

};


/*DECLS*/
static void 					dispose_od(GObject  *object);
static void 					finalize_od(GObject  *object);


/*IMPL*/
static void dd_topthree_class_init(DdTopthreeClass *klass)
{
	g_type_class_add_private(klass, sizeof(DdTopthreePrivate));
}

static void dd_topthree_init(DdTopthree *self)
{
	DdTopthreePrivate *priv = DD_TOPTHREE_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	DdTopthreePrivate *self = DD_TOPTHREE_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	DdTopthreePrivate *self = DD_TOPTHREE_GET_PRIVATE(object);
}

/**
Start PLL00.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll00(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL00ST() != 0 || DdTopone_Get_PLLCNT2_PL00SEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL00ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL00SEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL00.
*/
VOID dd_topthree_stop_pll00(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL00SEL(0);
	DdTopone_Set_PLLCNT1_PL00ST(0);
	Dd_ARM_Dsb_Pou();

}

/**
Start PLL01.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll01(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL01ST() != 0 || DdTopone_Get_PLLCNT2_PL01SEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL01ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL01SEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL01.
*/
VOID dd_topthree_stop_pll01(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL01SEL(0);
	DdTopone_Set_PLLCNT1_PL01ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start PLL02.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll02(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL02ST() != 0 || DdTopone_Get_PLLCNT2_PL02SEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL02ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL02SEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL02.
*/
VOID dd_topthree_stop_pll02(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL02SEL(0);
	DdTopone_Set_PLLCNT1_PL02ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start PLL03.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll03(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL03ST() != 0 || DdTopone_Get_PLLCNT2_PL03SEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL03ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL03SEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL03.
*/
VOID dd_topthree_stop_pll03(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL03SEL(0);
	DdTopone_Set_PLLCNT1_PL03ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start PLL04.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll04(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL04ST() != 0 || DdTopone_Get_PLLCNT2_PL04SEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL04ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL04SEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL04.
*/
VOID dd_topthree_stop_pll04(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL04SEL(0);
	DdTopone_Set_PLLCNT1_PL04ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start PLL05.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll05(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL05ST() != 0 || DdTopone_Get_PLLCNT2_PL05SEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL05ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL05SEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL05.
*/
VOID dd_topthree_stop_pll05(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL05SEL(0);
	DdTopone_Set_PLLCNT1_PL05ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start PLL05A.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll05a(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL05AST() != 0 || DdTopone_Get_PLLCNT1_PL05ST() != 1 || DdTopone_Get_PLLCNT2_PL05ASEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL05AST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL05ASEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL05A.
*/
VOID dd_topthree_stop_pll05a(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL05ASEL(0);
	DdTopone_Set_PLLCNT1_PL05AST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start PLL06.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll06(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL06ST() != 0 || DdTopone_Get_PLLCNT2_PL06SEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL06ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL06SEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL06.
*/
VOID dd_topthree_stop_pll06(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL06SEL(0);
	DdTopone_Set_PLLCNT1_PL06ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start PLL07.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll07(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL07ST() != 0 || DdTopone_Get_PLLCNT2_PL07SEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL07ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL07SEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL07.
*/
VOID dd_topthree_stop_pll07(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL07SEL(0);
	DdTopone_Set_PLLCNT1_PL07ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start PLL08.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll08(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL08ST() != 0 || DdTopone_Get_PLLCNT2_PL08SEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL08ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL08SEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL08.
*/
VOID dd_topthree_stop_pll08(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL08SEL(0);
	DdTopone_Set_PLLCNT1_PL08ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start PLL10.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll10(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL10ST() != 0 || DdTopone_Get_PLLCNT2_PL10SEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL10ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL10SEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL10.
*/
VOID dd_topthree_stop_pll10(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL10SEL(0);
	DdTopone_Set_PLLCNT1_PL10ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start PLL10A.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll10a(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL10AST() != 0 || DdTopone_Get_PLLCNT1_PL10ST() != 1 || DdTopone_Get_PLLCNT2_PL10ASEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL10AST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL10ASEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL100A.
*/
VOID dd_topthree_stop_pll10a(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL10ASEL(0);
	DdTopone_Set_PLLCNT1_PL10AST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start PLL11.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_pll11(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_PL11ST() != 0 || DdTopone_Get_PLLCNT2_PL11SEL() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_PL11ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	DdTopone_Set_PLLCNT2_PL11SEL(1);
	Dd_ARM_Dsb_Pou();

	return(D_DDIM_OK);
}

/**
Stop PLL11.
*/
VOID dd_topthree_stop_pll11(DdTopthree *self)
{
	DdTopone_Set_PLLCNT2_PL11SEL(0);
	DdTopone_Set_PLLCNT1_PL11ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start DDR 00 PLL.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_ddr_pll00(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_DPL00ST() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_DPL00ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	return(D_DDIM_OK);
}

/**
Stop DDR PLL00.
*/
VOID dd_topthree_stop_ddr_pll00(DdTopthree *self)
{
	DdTopone_Set_PLLCNT1_DPL00ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start DDR PLL01.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_ddr_pll01(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_DPL01ST() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_DPL01ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	return(D_DDIM_OK);
}

/**
Stop DDR PLL01.
*/
VOID dd_topthree_stop_ddr_pll01(DdTopthree *self)
{
	DdTopone_Set_PLLCNT1_DPL01ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start DDR PLL02.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_ddr_pll02(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_DPL02ST() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_DPL02ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	return(D_DDIM_OK);
}

/**
Stop DDR PLL02.
*/
VOID dd_topthree_stop_ddr_pll02(DdTopthree *self)
{
	DdTopone_Set_PLLCNT1_DPL02ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start DDR PLL10.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_ddr_pll10(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_DPL10ST() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_DPL10ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	return(D_DDIM_OK);
}

/**
Stop DDR PLL10.
*/
VOID dd_topthree_stop_ddr_pll10(DdTopthree *self)
{
	DdTopone_Set_PLLCNT1_DPL10ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start DDR PLL11.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_ddr_pll11(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_DPL11ST() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_DPL11ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	return(D_DDIM_OK);
}

/**
Stop DDR PLL11.
*/
VOID dd_topthree_stop_ddr_pll11(DdTopthree *self)
{
	DdTopone_Set_PLLCNT1_DPL11ST(0);
	Dd_ARM_Dsb_Pou();
}

/**
Start DDR PLL12.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
*/
INT32 dd_topthree_start_ddr_pll12(DdTopthree *self)
{
	if (DdTopone_Get_PLLCNT1_DPL12ST() != 0) {
		return(DdTopone_STATUS_ABNORMAL);
	}

	DdTopone_Set_PLLCNT1_DPL12ST(1);
	Dd_ARM_Dsb_Pou();

	DDIM_User_Dly_Tsk(1);

	return(D_DDIM_OK);
}

/**
Stop DDR PLL12.
*/
VOID dd_topthree_stop_ddr_pll12(DdTopthree *self)
{
	DdTopone_Set_PLLCNT1_DPL12ST(0);
	Dd_ARM_Dsb_Pou();
}


/**
Control Clock Stop to start clock.<br>
@param[in,out]	counter		address of Garding counter
@param[in,out]	regAddr	address of clock stop register
@param[in]		val			setting value
@remarks Set 1 to XXXSTOPC register internally.<br><br>
		*regAddr |= ~val
*/
VOID dd_topthree_start_clock(DdTopthree *self, UCHAR* counter, volatile unsigned long* regAddr, unsigned long val )
{
	static ULONG critseq __attribute__((section(".LOCK_SECTION"), aligned(64)));
	unsigned long reg = *regAddr;

	Dd_ARM_Critical_Section_Start( critseq );
	(*counter)++;
	if ( 1 == (*counter) ) {
		reg &= ~(~val | (~val << 1));
		reg += (~val << 1);
		*regAddr = reg;
	}
	Dd_ARM_Critical_Section_End( critseq );
}

/**
Control Clock Stop to stop clock.
@param[in,out]	counter		address of Garding counter
@param[in,out]	regAddr	address of clock stop register
@param[in]		val			setting value
@remarks Set 1 to XXXSTOPS register internally.<br><br>
		*regAddr |= val
*/
VOID dd_topthree_stop_clock(DdTopthree *self, UCHAR* counter, volatile unsigned long* regAddr, unsigned long val )
{
	static ULONG critseq __attribute__((section(".LOCK_SECTION"), aligned(64)));

	Dd_ARM_Critical_Section_Start( critseq );
	if ( 0 < (*counter) ) {
		(*counter)--;
	}
	if ( 0 == (*counter) ) {
		*regAddr = ((*regAddr & ~(val | (val << 1))) + (val | (val << 1))) | val;
	}
	Dd_ARM_Critical_Section_End( critseq );
}

/**
Get Frequency of RIBERY clock
@retval	Hz
*/
ULONG dd_topthree_get_ribclk(DdTopthree *self)
{
	// 0:466.666MHz(=1400MHz/3)
	// 1:350MHz(=1400MHz/4)
	// 2:233.333MHz(=1400MHz/6)
	// 3:116.666MHz(=1400MHz/12)
	// 4:58.333MHz(=1400MHz/24)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 255};
	static const UCHAR S_DIVID[] = {3, 4, 6, 12, 24};
	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL12_RIBCLK() == S_ID[i]) {
			clock = (DdTopone_1400_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}


/**
Get Frequency of NFBCHCLK clock
@retval	Hz
*/
ULONG dd_topthree_get_nfbchclk(DdTopthree *self)
{
	// 0:200MHz(=1600MHz/8)
	// 1:100MHz(=1600MHz/16)
	static const UCHAR S_DIVID[] = {8, 16};

	return (DdTopone_1600_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL12_NFBCHCLK()]);
}

/**
Get Frequency of MECLK clock
@retval	Hz
*/
ULONG dd_topthree_get_meclk(DdTopthree *self)
{
	// 0: 466.666MHz(=1400MHz/3)
	// 1: 233.333MHz(=1400MHz/6)
	// 2: 116.666MHz(=1400MHz/12)
	// 3: 58.333MHz(=1400MHz/24)
	static const UCHAR S_DIVID[] = {3, 6, 12, 24};

	return (DdTopone_1400_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL12_MECLK()]);
}

/**
Get Frequency of FPT1 clock
@retval	Hz
*/
ULONG dd_topthree_get_fpt1clk(DdTopthree *self)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 5, 6, 255};
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};
	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL12_FPT1CLK() == S_ID[i]) {
			clock = (DdTopone_1200_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of FPT0 clock
@retval	Hz
*/
ULONG dd_topthree_get_fpt0clk(DdTopthree *self)
{
	// 0: 300MHz(=1200MHz/4)
	// 1: 200MHz(=1200MHz/6)
	// 2: 150MHz(=1200MHz/8)
	// 3: 100MHz(=1200MHz/12)
	// 4: 75MHz(=1200MHz/16)
	// 5: 60MHz(=1200MHz/20)
	// 6: 50MHz(=1200MHz/24)
	static const UCHAR S_ID[] = {0, 1, 2, 3, 4, 5, 6, 255};
	static const UCHAR S_DIVID[] = {4, 6, 8, 12, 16, 20, 24};
	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL12_FPT0CLK() == S_ID[i]) {
			clock = (DdTopone_1200_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of GYRO clock
@retval	Hz
*/
ULONG dd_topthree_get_gyroclk(DdTopthree *self)
{
	// 0:100MHz(=1600MHz/16)
	// 1:32MHz(=1600MHz/50)
	// 2:2MHz(=1600MHz/800)
	static const ULONG S_ID[] = {0, 1, 2, 255};
	static const ULONG S_DIVID[] = {16, 50, 800};
	int i;
	ULONG clock = 0;

	for (i = 0; S_ID[i] != 255; i ++) {
		if (DdTopone_Get_CLKSEL12_GYROCLK() == S_ID[i]) {
			clock = (DdTopone_1600_PLL_OUT / S_DIVID[i]);
			break;
		}
	}

	return clock;
}

/**
Get Frequency of AXI bus 300 clock
@retval	Hz
*/
ULONG dd_topthree_get_aclk300(DdTopthree *self)
{
	// 0:300MHz(=1200MHz/4)
	// 1:200MHz(=1200MHz/6)
	static const UCHAR S_DIVID[] = {4, 6};


	return (DdTopone_1200_PLL_OUT / S_DIVID[DdTopone_Get_CLKSEL12_ACLK300()]);
}

INT32 dd_topthree_set_gpio_direction(DdTopthree *self, DdTop_GPIO_PORT port, UCHAR direction )
{
#ifdef DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL
	INT32 s;
#endif // DdToptwo_CO_ACT_GPIO_CLOCK_CONTROL

#ifdef CO_PARAM_CHECK
	if( port >= DdTop_GPIO_PORT_MAX ) {
		Ddim_Assertion(("dd_topthree_set_gpio_direction() error. port parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
	if( direction > DdToptwo_GPIO_DIR_OUT ) {
		Ddim_Assertion(("dd_topthree_set_gpio_direction() error. direction parameters is abnormal.\n"));
		return DdTopone_INPUT_PARAM_ERROR;
	}
#endif

	DdToptwo_START_GPIO_CLK_WITH_CS();

	switch( port ) {
		case DdTop_GPIO_P60: IO_CHIPTOP.DDR.bit.P60 = direction; break;
		case DdTop_GPIO_P61: IO_CHIPTOP.DDR.bit.P61 = direction; break;
		case DdTop_GPIO_P62: IO_CHIPTOP.DDR.bit.P62 = direction; break;
		case DdTop_GPIO_P63: IO_CHIPTOP.DDR.bit.P63 = direction; break;
		case DdTop_GPIO_P64: IO_CHIPTOP.DDR.bit.P64 = direction; break;
		case DdTop_GPIO_P65: IO_CHIPTOP.DDR.bit.P65 = direction; break;
		case DdTop_GPIO_P66: IO_CHIPTOP.DDR.bit.P66 = direction; break;
		case DdTop_GPIO_P67: IO_CHIPTOP.DDR.bit.P67 = direction; break;
		case DdTop_GPIO_P70: IO_CHIPTOP.DDR.bit.P70 = direction; break;
		case DdTop_GPIO_P71: IO_CHIPTOP.DDR.bit.P71 = direction; break;
		case DdTop_GPIO_P72: IO_CHIPTOP.DDR.bit.P72 = direction; break;
		case DdTop_GPIO_P73: IO_CHIPTOP.DDR.bit.P73 = direction; break;
		case DdTop_GPIO_P74: IO_CHIPTOP.DDR.bit.P74 = direction; break;
		case DdTop_GPIO_P75: IO_CHIPTOP.DDR.bit.P75 = direction; break;
		case DdTop_GPIO_P76: IO_CHIPTOP.DDR.bit.P76 = direction; break;
		case DdTop_GPIO_P77: IO_CHIPTOP.DDR.bit.P77 = direction; break;
		case DdTop_GPIO_P80: IO_CHIPTOP.DDR.bit.P80 = direction; break;
		case DdTop_GPIO_P81: IO_CHIPTOP.DDR.bit.P81 = direction; break;
		case DdTop_GPIO_P82: IO_CHIPTOP.DDR.bit.P82 = direction; break;
		case DdTop_GPIO_P83: IO_CHIPTOP.DDR.bit.P83 = direction; break;
		case DdTop_GPIO_P84: IO_CHIPTOP.DDR.bit.P84 = direction; break;
		case DdTop_GPIO_P85: IO_CHIPTOP.DDR.bit.P85 = direction; break;
		case DdTop_GPIO_P86: IO_CHIPTOP.DDR.bit.P86 = direction; break;
		case DdTop_GPIO_P87: IO_CHIPTOP.DDR.bit.P87 = direction; break;
		case DdTop_GPIO_P90: IO_CHIPTOP.DDR.bit.P90 = direction; break;
		case DdTop_GPIO_P91: IO_CHIPTOP.DDR.bit.P91 = direction; break;
		case DdTop_GPIO_P92: IO_CHIPTOP.DDR.bit.P92 = direction; break;
		case DdTop_GPIO_P93: IO_CHIPTOP.DDR.bit.P93 = direction; break;
		case DdTop_GPIO_PA0: IO_CHIPTOP.DDR.bit.PA0 = direction; break;
		case DdTop_GPIO_PA1: IO_CHIPTOP.DDR.bit.PA1 = direction; break;
		case DdTop_GPIO_PA2: IO_CHIPTOP.DDR.bit.PA2 = direction; break;
		case DdTop_GPIO_PA3: IO_CHIPTOP.DDR.bit.PA3 = direction; break;
		case DdTop_GPIO_PA4: IO_CHIPTOP.DDR.bit.PA4 = direction; break;
		case DdTop_GPIO_PA5: IO_CHIPTOP.DDR.bit.PA5 = direction; break;
		case DdTop_GPIO_PA6: IO_CHIPTOP.DDR.bit.PA6 = direction; break;
		case DdTop_GPIO_PA7: IO_CHIPTOP.DDR.bit.PA7 = direction; break;
		case DdTop_GPIO_PB0: IO_CHIPTOP.DDR.bit.PB0 = direction; break;
		case DdTop_GPIO_PB1: IO_CHIPTOP.DDR.bit.PB1 = direction; break;
		case DdTop_GPIO_PB2: IO_CHIPTOP.DDR.bit.PB2 = direction; break;
		case DdTop_GPIO_PB3: IO_CHIPTOP.DDR.bit.PB3 = direction; break;
		case DdTop_GPIO_PB4: IO_CHIPTOP.DDR.bit.PB4 = direction; break;
		case DdTop_GPIO_PC0L: IO_CHIPTOP.DDR.bit.PC0 = direction; break;
		case DdTop_GPIO_PC1L: IO_CHIPTOP.DDR.bit.PC1 = direction; break;
		case DdTop_GPIO_PC2L: IO_CHIPTOP.DDR.bit.PC2 = direction; break;
		case DdTop_GPIO_PC3L: IO_CHIPTOP.DDR.bit.PC3 = direction; break;
		case DdTop_GPIO_PC4L: IO_CHIPTOP.DDR.bit.PC4 = direction; break;
		case DdTop_GPIO_PC5L: IO_CHIPTOP.DDR.bit.PC5 = direction; break;
		case DdTop_GPIO_PD0: IO_CHIPTOP.DDR.bit.PD0 = direction; break;
		case DdTop_GPIO_PD1: IO_CHIPTOP.DDR.bit.PD1 = direction; break;
		case DdTop_GPIO_PD2: IO_CHIPTOP.DDR.bit.PD2 = direction; break;
		case DdTop_GPIO_PD3: IO_CHIPTOP.DDR.bit.PD3 = direction; break;
		case DdTop_GPIO_PD4: IO_CHIPTOP.DDR.bit.PD4 = direction; break;
		case DdTop_GPIO_PD5: IO_CHIPTOP.DDR.bit.PD5 = direction; break;
		case DdTop_GPIO_PD6: IO_CHIPTOP.DDR.bit.PD6 = direction; break;
		case DdTop_GPIO_PE0: IO_CHIPTOP.DDR.bit.PE0 = direction; break;
		case DdTop_GPIO_PE1: IO_CHIPTOP.DDR.bit.PE1 = direction; break;
		case DdTop_GPIO_PE2: IO_CHIPTOP.DDR.bit.PE2 = direction; break;
		case DdTop_GPIO_PE3: IO_CHIPTOP.DDR.bit.PE3 = direction; break;
		case DdTop_GPIO_PE4: IO_CHIPTOP.DDR.bit.PE4 = direction; break;
		case DdTop_GPIO_PE5: IO_CHIPTOP.DDR.bit.PE5 = direction; break;
		case DdTop_GPIO_PF0: IO_CHIPTOP.DDR.bit.PF0 = direction; break;
		case DdTop_GPIO_PF1: IO_CHIPTOP.DDR.bit.PF1 = direction; break;
		case DdTop_GPIO_PF2: IO_CHIPTOP.DDR.bit.PF2 = direction; break;
		case DdTop_GPIO_PF3: IO_CHIPTOP.DDR.bit.PF3 = direction; break;
		case DdTop_GPIO_PF4: IO_CHIPTOP.DDR.bit.PF4 = direction; break;
		case DdTop_GPIO_PG0: IO_CHIPTOP.DDR.bit.PG0 = direction; break;
		case DdTop_GPIO_PG1: IO_CHIPTOP.DDR.bit.PG1 = direction; break;
		case DdTop_GPIO_PG2: IO_CHIPTOP.DDR.bit.PG2 = direction; break;
		case DdTop_GPIO_PG3: IO_CHIPTOP.DDR.bit.PG3 = direction; break;
		case DdTop_GPIO_PG4: IO_CHIPTOP.DDR.bit.PG4 = direction; break;
		case DdTop_GPIO_PG5: IO_CHIPTOP.DDR.bit.PG5 = direction; break;
		case DdTop_GPIO_PG6: IO_CHIPTOP.DDR.bit.PG6 = direction; break;
		case DdTop_GPIO_PG7: IO_CHIPTOP.DDR.bit.PG7 = direction; break;
		case DdTop_GPIO_PH0: IO_CHIPTOP.DDR.bit.PH0 = direction; break;
		case DdTop_GPIO_PH1: IO_CHIPTOP.DDR.bit.PH1 = direction; break;
		case DdTop_GPIO_PH2: IO_CHIPTOP.DDR.bit.PH2 = direction; break;
		case DdTop_GPIO_PH3: IO_CHIPTOP.DDR.bit.PH3 = direction; break;
		case DdTop_GPIO_PW0: IO_CHIPTOP.DDR.bit.PW0 = direction; break;
		case DdTop_GPIO_PW1: IO_CHIPTOP.DDR.bit.PW1 = direction; break;
		case DdTop_GPIO_PW2: IO_CHIPTOP.DDR.bit.PW2 = direction; break;
		case DdTop_GPIO_PW3: IO_CHIPTOP.DDR.bit.PW3 = direction; break;
		case DdTop_GPIO_PW4: IO_CHIPTOP.DDR.bit.PW4 = direction; break;
		case DdTop_GPIO_PW5: IO_CHIPTOP.DDR.bit.PW5 = direction; break;
		case DdTop_GPIO_PW6: IO_CHIPTOP.DDR.bit.PW6 = direction; break;
		case DdTop_GPIO_PW7: IO_CHIPTOP.DDR.bit.PW7 = direction; break;
		case DdTop_GPIO_PJ0: IO_CHIPTOP.DDR.bit.PJ0 = direction; break;
		case DdTop_GPIO_PJ1: IO_CHIPTOP.DDR.bit.PJ1 = direction; break;
		case DdTop_GPIO_PJ2: IO_CHIPTOP.DDR.bit.PJ2 = direction; break;
		case DdTop_GPIO_PJ3: IO_CHIPTOP.DDR.bit.PJ3 = direction; break;
		case DdTop_GPIO_PJ4: IO_CHIPTOP.DDR.bit.PJ4 = direction; break;
		case DdTop_GPIO_PJ5: IO_CHIPTOP.DDR.bit.PJ5 = direction; break;
		case DdTop_GPIO_PJ6: IO_CHIPTOP.DDR.bit.PJ6 = direction; break;
		case DdTop_GPIO_PJ7: IO_CHIPTOP.DDR.bit.PJ7 = direction; break;
		case DdTop_GPIO_PK0: IO_CHIPTOP.DDR.bit.PK0 = direction; break;
		case DdTop_GPIO_PK1: IO_CHIPTOP.DDR.bit.PK1 = direction; break;
		case DdTop_GPIO_PK2: IO_CHIPTOP.DDR.bit.PK2 = direction; break;
		case DdTop_GPIO_PK3: IO_CHIPTOP.DDR.bit.PK3 = direction; break;
		case DdTop_GPIO_PK4: IO_CHIPTOP.DDR.bit.PK4 = direction; break;
		case DdTop_GPIO_PK5: IO_CHIPTOP.DDR.bit.PK5 = direction; break;
		case DdTop_GPIO_PK6: IO_CHIPTOP.DDR.bit.PK6 = direction; break;
		case DdTop_GPIO_PK7: IO_CHIPTOP.DDR.bit.PK7 = direction; break;
		case DdTop_GPIO_PL0: IO_CHIPTOP.DDR.bit.PL0 = direction; break;
		case DdTop_GPIO_PL1: IO_CHIPTOP.DDR.bit.PL1 = direction; break;
		case DdTop_GPIO_PL2: IO_CHIPTOP.DDR.bit.PL2 = direction; break;
		case DdTop_GPIO_PL3: IO_CHIPTOP.DDR.bit.PL3 = direction; break;
		case DdTop_GPIO_PL4: IO_CHIPTOP.DDR.bit.PL4 = direction; break;
		case DdTop_GPIO_PL5: IO_CHIPTOP.DDR.bit.PL5 = direction; break;
		case DdTop_GPIO_PM0: IO_CHIPTOP.DDR.bit.PM0 = direction; break;
		case DdTop_GPIO_PM1: IO_CHIPTOP.DDR.bit.PM1 = direction; break;
		case DdTop_GPIO_PM2: IO_CHIPTOP.DDR.bit.PM2 = direction; break;
		case DdTop_GPIO_PM3: IO_CHIPTOP.DDR.bit.PM3 = direction; break;
		case DdTop_GPIO_PM4: IO_CHIPTOP.DDR.bit.PM4 = direction; break;
		case DdTop_GPIO_PN0: IO_CHIPTOP.DDR.bit.PN0 = direction; break;
		case DdTop_GPIO_PN1: IO_CHIPTOP.DDR.bit.PN1 = direction; break;
		case DdTop_GPIO_PN2: IO_CHIPTOP.DDR.bit.PN2 = direction; break;
		case DdTop_GPIO_PN3: IO_CHIPTOP.DDR.bit.PN3 = direction; break;
		case DdTop_GPIO_PN4: IO_CHIPTOP.DDR.bit.PN4 = direction; break;
		case DdTop_GPIO_PY0: IO_CHIPTOP.DDR.bit.PY0 = direction; break;
		case DdTop_GPIO_PY1: IO_CHIPTOP.DDR.bit.PY1 = direction; break;
		case DdTop_GPIO_PY2: IO_CHIPTOP.DDR.bit.PY2 = direction; break;
		case DdTop_GPIO_PY3: IO_CHIPTOP.DDR.bit.PY3 = direction; break;
		case DdTop_GPIO_PY4: IO_CHIPTOP.DDR.bit.PY4 = direction; break;
		case DdTop_GPIO_PY5: IO_CHIPTOP.DDR.bit.PY5 = direction; break;
		case DdTop_GPIO_PY6: IO_CHIPTOP.DDR.bit.PY6 = direction; break;
		case DdTop_GPIO_PY7: IO_CHIPTOP.DDR.bit.PY7 = direction; break;
		case DdTop_GPIO_PP0: IO_CHIPTOP.DDR.bit.PP0 = direction; break;
		case DdTop_GPIO_PP1: IO_CHIPTOP.DDR.bit.PP1 = direction; break;
		case DdTop_GPIO_PP2: IO_CHIPTOP.DDR.bit.PP2 = direction; break;
		case DdTop_GPIO_PP3: IO_CHIPTOP.DDR.bit.PP3 = direction; break;
		default:
			DdToptwo_STOP_GPIO_CLK_WITH_CS();
			Ddim_Print(("dd_topthree_set_gpio_direction() error. port not exist.\n"));
			return DdTopone_INPUT_PARAM_ERROR;
	}

	Dd_ARM_Dsb_Pou();
	DdToptwo_STOP_GPIO_CLK_WITH_CS();

	return D_DDIM_OK;
}


DdTopthree* dd_topthree_new(void)
{
	DdTopthree *self = g_object_new(DD_TYPE_TOPTHREE, NULL);
	return self;
}
