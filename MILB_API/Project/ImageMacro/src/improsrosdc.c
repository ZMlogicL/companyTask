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
#include"improsrosdc.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSrosdc, impro_srosdc);
#define IMPRO_SROSDC_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSrosdcPrivate, IMPRO_TYPE_SROSDC));


/*宏定义区域*/
/* SDC0				*/
#define	ImproSrosdc_D_IM_SRO1_STATUS_SDC0		((0x00000000UL)&(1<< 5))
/* SDC1				*/
#define	ImproSrosdc_D_IM_SRO1_STATUS_SDC1		((0x00000000UL)&(1<< 6))
/* SDC0				*/
#define	ImproSrosdc_D_IM_SRO2_STATUS_SDC0		((0x10000000UL)&(1<< 5))
/* SDC1				*/
#define	ImproSrosdc_D_IM_SRO2_STATUS_SDC1		((0x10000000UL)&(1<< 6))
/* Image Pipe1&2 SDC0	*/
#define	ImproSrosdc_D_IM_SRO_STATUS_SDC0_BOTH	( ImproSrosdc_D_IM_SRO1_STATUS_SDC0\
																								| ImproSrosdc_D_IM_SRO2_STATUS_SDC0	)
/* Image Pipe1&2 SDC1	*/
#define	ImproSrosdc_D_IM_SRO_STATUS_SDC1_BOTH	( ImproSrosdc_D_IM_SRO1_STATUS_SDC1\
																								| ImproSrosdc_D_IM_SRO2_STATUS_SDC1	)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSrosdcPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
static const TimproRdmaSdcAddr S_G_IM_PRO_SDC_ADDR[ImproBase_E_IM_PRO_UNIT_NUM_MAX][ImproSrosdc_D_IM_PRO_SRO_SDC_CH_NUM] = {
	{
		{
			0x28408808,0x28408814,0x28408880,0x28408884,
			0x28408888,0x2840888C,0x28408890,0x28408894,
			0x28408898,0x2840889C,0x284088A0,0x284088A4,
			0x284088A8,0x284088AC,0x284088B0,0x284088B4,
			0x284088B8,0x284088BC,0x284088C0,0x284088C4,
			0x28408900,0x28408904,0x28408908,0x2840890C,
			0x28408910,0x28408914,0x28408918,0x2840891C,
			0x28408920,0x28408924,0x28408928,0x2840892C,
			0x28408930,0x28408934,0x28408938,0x2840893C,
			0x28408940,0x28408944,0x28408980,0x28408984,
			0x28408988,0x28408990,0x28408994,0x28408998,
			0x284089A0,0x284089A4,0x284089A8,0x284089AC,
			0x284089B0,0x284089C0,0x284089C4,0x284089C8,
			0x284089CC,0x284089D0,0x284089E0,0x284089E4,
			0x284089E8,0x284089EC,0x284089F0,0x28408A00,
			0x28408A04,0x28408A08,0x28408A0C,0x28408A10,
			0x28408A20,0x28408A24,0x28408A28,0x28408A2C,
			0x28408A30,0x28408A40,0x28408A44,0x28408A48,
			0x28408A4C,0x28408A50,0x28408A60,0x28408A64,
			0x28408A68,0x28408A6C,0x28408A70,0x28408A80,
			0x28408A84,0x28408A88,0x28408A8C,0x28408A90,
			0x28408AC0,0x28408AC4,0x28408AC8,0x28408ACC,
			0x28408AD0,0x28408AD4,0x28408AD8,0x28408ADC,
			0x28408AE0,0x28408AE4,0x28408AE8,0x28408AEC,
			0x28408AF0,0x28408AF4,0x28408AF8,0x28408AFC,
			0x28408B00,0x28408B04,0x28408B08,0x28408B0C,
			0x28408B10,0x28408B14,0x28408B18,0x28408B1C,
			0x28408B20,0x28408B24,0x28408B28,0x28408B2C,
			0x28408B30,0x28408B34,0x28408B38,0x28408B3C,
			0x28408B40,0x28408B44,0x28408B48,0x28408B4C,
			0x28408B50,0x28408B54,0x28408B58,0x28408B5C,
			0x28408B60,0x28408B64,0x28408B9C,0x28408BA0,
		},
		{
			0x2840C808,0x2840C814,0x2840C880,0x2840C884,
			0x2840C888,0x2840C88C,0x2840C890,0x2840C894,
			0x2840C898,0x2840C89C,0x2840C8A0,0x2840C8A4,
			0x2840C8A8,0x2840C8AC,0x2840C8B0,0x2840C8B4,
			0x2840C8B8,0x2840C8BC,0x2840C8C0,0x2840C8C4,
			0x2840C900,0x2840C904,0x2840C908,0x2840C90C,
			0x2840C910,0x2840C914,0x2840C918,0x2840C91C,
			0x2840C920,0x2840C924,0x2840C928,0x2840C92C,
			0x2840C930,0x2840C934,0x2840C938,0x2840C93C,
			0x2840C940,0x2840C944,0x2840C980,0x2840C984,
			0x2840C988,0x2840C990,0x2840C994,0x2840C998,
			0x2840C9A0,0x2840C9A4,0x2840C9A8,0x2840C9AC,
			0x2840C9B0,0x2840C9C0,0x2840C9C4,0x2840C9C8,
			0x2840C9CC,0x2840C9D0,0x2840C9E0,0x2840C9E4,
			0x2840C9E8,0x2840C9EC,0x2840C9F0,0x2840CA00,
			0x2840CA04,0x2840CA08,0x2840CA0C,0x2840CA10,
			0x2840CA20,0x2840CA24,0x2840CA28,0x2840CA2C,
			0x2840CA30,0x2840CA40,0x2840CA44,0x2840CA48,
			0x2840CA4C,0x2840CA50,0x2840CA60,0x2840CA64,
			0x2840CA68,0x2840CA6C,0x2840CA70,0x2840CA80,
			0x2840CA84,0x2840CA88,0x2840CA8C,0x2840CA90,
			0x2840CAC0,0x2840CAC4,0x2840CAC8,0x2840CACC,
			0x2840CAD0,0x2840CAD4,0x2840CAD8,0x2840CADC,
			0x2840CAE0,0x2840CAE4,0x2840CAE8,0x2840CAEC,
			0x2840CAF0,0x2840CAF4,0x2840CAF8,0x2840CAFC,
			0x2840CB00,0x2840CB04,0x2840CB08,0x2840CB0C,
			0x2840CB10,0x2840CB14,0x2840CB18,0x2840CB1C,
			0x2840CB20,0x2840CB24,0x2840CB28,0x2840CB2C,
			0x2840CB30,0x2840CB34,0x2840CB38,0x2840CB3C,
			0x2840CB40,0x2840CB44,0x2840CB48,0x2840CB4C,
			0x2840CB50,0x2840CB54,0x2840CB58,0x2840CB5C,
			0x2840CB60,0x2840CB64,0x2840CB9C,0x2840CBA0,
		},
	},
	{
		{
			0x28508808,0x28508814,0x28508880,0x28508884,
			0x28508888,0x2850888C,0x28508890,0x28508894,
			0x28508898,0x2850889C,0x285088A0,0x285088A4,
			0x285088A8,0x285088AC,0x285088B0,0x285088B4,
			0x285088B8,0x285088BC,0x285088C0,0x285088C4,
			0x28508900,0x28508904,0x28508908,0x2850890C,
			0x28508910,0x28508914,0x28508918,0x2850891C,
			0x28508920,0x28508924,0x28508928,0x2850892C,
			0x28508930,0x28508934,0x28508938,0x2850893C,
			0x28508940,0x28508944,0x28508980,0x28508984,
			0x28508988,0x28508990,0x28508994,0x28508998,
			0x285089A0,0x285089A4,0x285089A8,0x285089AC,
			0x285089B0,0x285089C0,0x285089C4,0x285089C8,
			0x285089CC,0x285089D0,0x285089E0,0x285089E4,
			0x285089E8,0x285089EC,0x285089F0,0x28508A00,
			0x28508A04,0x28508A08,0x28508A0C,0x28508A10,
			0x28508A20,0x28508A24,0x28508A28,0x28508A2C,
			0x28508A30,0x28508A40,0x28508A44,0x28508A48,
			0x28508A4C,0x28508A50,0x28508A60,0x28508A64,
			0x28508A68,0x28508A6C,0x28508A70,0x28508A80,
			0x28508A84,0x28508A88,0x28508A8C,0x28508A90,
			0x28508AC0,0x28508AC4,0x28508AC8,0x28508ACC,
			0x28508AD0,0x28508AD4,0x28508AD8,0x28508ADC,
			0x28508AE0,0x28508AE4,0x28508AE8,0x28508AEC,
			0x28508AF0,0x28508AF4,0x28508AF8,0x28508AFC,
			0x28508B00,0x28508B04,0x28508B08,0x28508B0C,
			0x28508B10,0x28508B14,0x28508B18,0x28508B1C,
			0x28508B20,0x28508B24,0x28508B28,0x28508B2C,
			0x28508B30,0x28508B34,0x28508B38,0x28508B3C,
			0x28508B40,0x28508B44,0x28508B48,0x28508B4C,
			0x28508B50,0x28508B54,0x28508B58,0x28508B5C,
			0x28508B60,0x28508B64,0x28508B9C,0x28508BA0,
		},
		{
			0x2850C808,0x2850C814,0x2850C880,0x2850C884,
			0x2850C888,0x2850C88C,0x2850C890,0x2850C894,
			0x2850C898,0x2850C89C,0x2850C8A0,0x2850C8A4,
			0x2850C8A8,0x2850C8AC,0x2850C8B0,0x2850C8B4,
			0x2850C8B8,0x2850C8BC,0x2850C8C0,0x2850C8C4,
			0x2850C900,0x2850C904,0x2850C908,0x2850C90C,
			0x2850C910,0x2850C914,0x2850C918,0x2850C91C,
			0x2850C920,0x2850C924,0x2850C928,0x2850C92C,
			0x2850C930,0x2850C934,0x2850C938,0x2850C93C,
			0x2850C940,0x2850C944,0x2850C980,0x2850C984,
			0x2850C988,0x2850C990,0x2850C994,0x2850C998,
			0x2850C9A0,0x2850C9A4,0x2850C9A8,0x2850C9AC,
			0x2850C9B0,0x2850C9C0,0x2850C9C4,0x2850C9C8,
			0x2850C9CC,0x2850C9D0,0x2850C9E0,0x2850C9E4,
			0x2850C9E8,0x2850C9EC,0x2850C9F0,0x2850CA00,
			0x2850CA04,0x2850CA08,0x2850CA0C,0x2850CA10,
			0x2850CA20,0x2850CA24,0x2850CA28,0x2850CA2C,
			0x2850CA30,0x2850CA40,0x2850CA44,0x2850CA48,
			0x2850CA4C,0x2850CA50,0x2850CA60,0x2850CA64,
			0x2850CA68,0x2850CA6C,0x2850CA70,0x2850CA80,
			0x2850CA84,0x2850CA88,0x2850CA8C,0x2850CA90,
			0x2850CAC0,0x2850CAC4,0x2850CAC8,0x2850CACC,
			0x2850CAD0,0x2850CAD4,0x2850CAD8,0x2850CADC,
			0x2850CAE0,0x2850CAE4,0x2850CAE8,0x2850CAEC,
			0x2850CAF0,0x2850CAF4,0x2850CAF8,0x2850CAFC,
			0x2850CB00,0x2850CB04,0x2850CB08,0x2850CB0C,
			0x2850CB10,0x2850CB14,0x2850CB18,0x2850CB1C,
			0x2850CB20,0x2850CB24,0x2850CB28,0x2850CB2C,
			0x2850CB30,0x2850CB34,0x2850CB38,0x2850CB3C,
			0x2850CB40,0x2850CB44,0x2850CB48,0x2850CB4C,
			0x2850CB50,0x2850CB54,0x2850CB58,0x2850CB5C,
			0x2850CB60,0x2850CB64,0x2850CB9C,0x2850CBA0,
		},
	},
	{
		{
			0x28608808,0x28608814,0x28608880,0x28608884,
			0x28608888,0x2860888C,0x28608890,0x28608894,
			0x28608898,0x2860889C,0x286088A0,0x286088A4,
			0x286088A8,0x286088AC,0x286088B0,0x286088B4,
			0x286088B8,0x286088BC,0x286088C0,0x286088C4,
			0x28608900,0x28608904,0x28608908,0x2860890C,
			0x28608910,0x28608914,0x28608918,0x2860891C,
			0x28608920,0x28608924,0x28608928,0x2860892C,
			0x28608930,0x28608934,0x28608938,0x2860893C,
			0x28608940,0x28608944,0x28608980,0x28608984,
			0x28608988,0x28608990,0x28608994,0x28608998,
			0x286089A0,0x286089A4,0x286089A8,0x286089AC,
			0x286089B0,0x286089C0,0x286089C4,0x286089C8,
			0x286089CC,0x286089D0,0x286089E0,0x286089E4,
			0x286089E8,0x286089EC,0x286089F0,0x28608A00,
			0x28608A04,0x28608A08,0x28608A0C,0x28608A10,
			0x28608A20,0x28608A24,0x28608A28,0x28608A2C,
			0x28608A30,0x28608A40,0x28608A44,0x28608A48,
			0x28608A4C,0x28608A50,0x28608A60,0x28608A64,
			0x28608A68,0x28608A6C,0x28608A70,0x28608A80,
			0x28608A84,0x28608A88,0x28608A8C,0x28608A90,
			0x28608AC0,0x28608AC4,0x28608AC8,0x28608ACC,
			0x28608AD0,0x28608AD4,0x28608AD8,0x28608ADC,
			0x28608AE0,0x28608AE4,0x28608AE8,0x28608AEC,
			0x28608AF0,0x28608AF4,0x28608AF8,0x28608AFC,
			0x28608B00,0x28608B04,0x28608B08,0x28608B0C,
			0x28608B10,0x28608B14,0x28608B18,0x28608B1C,
			0x28608B20,0x28608B24,0x28608B28,0x28608B2C,
			0x28608B30,0x28608B34,0x28608B38,0x28608B3C,
			0x28608B40,0x28608B44,0x28608B48,0x28608B4C,
			0x28608B50,0x28608B54,0x28608B58,0x28608B5C,
			0x28608B60,0x28608B64,0x28608B9C,0x28608BA0,
		},
		{
			0x2860C808,0x2860C814,0x2860C880,0x2860C884,
			0x2860C888,0x2860C88C,0x2860C890,0x2860C894,
			0x2860C898,0x2860C89C,0x2860C8A0,0x2860C8A4,
			0x2860C8A8,0x2860C8AC,0x2860C8B0,0x2860C8B4,
			0x2860C8B8,0x2860C8BC,0x2860C8C0,0x2860C8C4,
			0x2860C900,0x2860C904,0x2860C908,0x2860C90C,
			0x2860C910,0x2860C914,0x2860C918,0x2860C91C,
			0x2860C920,0x2860C924,0x2860C928,0x2860C92C,
			0x2860C930,0x2860C934,0x2860C938,0x2860C93C,
			0x2860C940,0x2860C944,0x2860C980,0x2860C984,
			0x2860C988,0x2860C990,0x2860C994,0x2860C998,
			0x2860C9A0,0x2860C9A4,0x2860C9A8,0x2860C9AC,
			0x2860C9B0,0x2860C9C0,0x2860C9C4,0x2860C9C8,
			0x2860C9CC,0x2860C9D0,0x2860C9E0,0x2860C9E4,
			0x2860C9E8,0x2860C9EC,0x2860C9F0,0x2860CA00,
			0x2860CA04,0x2860CA08,0x2860CA0C,0x2860CA10,
			0x2860CA20,0x2860CA24,0x2860CA28,0x2860CA2C,
			0x2860CA30,0x2860CA40,0x2860CA44,0x2860CA48,
			0x2860CA4C,0x2860CA50,0x2860CA60,0x2860CA64,
			0x2860CA68,0x2860CA6C,0x2860CA70,0x2860CA80,
			0x2860CA84,0x2860CA88,0x2860CA8C,0x2860CA90,
			0x2860CAC0,0x2860CAC4,0x2860CAC8,0x2860CACC,
			0x2860CAD0,0x2860CAD4,0x2860CAD8,0x2860CADC,
			0x2860CAE0,0x2860CAE4,0x2860CAE8,0x2860CAEC,
			0x2860CAF0,0x2860CAF4,0x2860CAF8,0x2860CAFC,
			0x2860CB00,0x2860CB04,0x2860CB08,0x2860CB0C,
			0x2860CB10,0x2860CB14,0x2860CB18,0x2860CB1C,
			0x2860CB20,0x2860CB24,0x2860CB28,0x2860CB2C,
			0x2860CB30,0x2860CB34,0x2860CB38,0x2860CB3C,
			0x2860CB40,0x2860CB44,0x2860CB48,0x2860CB4C,
			0x2860CB50,0x2860CB54,0x2860CB58,0x2860CB5C,
			0x2860CB60,0x2860CB64,0x2860CB9C,0x2860CBA0,
		},
	},
};

static const TimproRdmaSdcGainTblAddr gIM_PRO_SDC_Gain_Tbl_Addr[ImproBase_E_IM_PRO_UNIT_NUM_MAX]
                                                                			[ImproSrosdc_D_IM_PRO_SRO_SDC_CH_NUM][D_IM_PRO_SRO_SDC_TBL_CNT] = {
	{
		{
			{ 0x29440000 },
			{ 0x29440100 },
		},
		{
			{ 0x29440200},
			{ 0x29440300},
		},
	},
	{
		{
			{ 0x29540000 },
			{ 0x29540100 },
		},
		{
			{ 0x29540200},
			{ 0x29540300},
		},
	},
	{
		{
			{ 0x29640000 },
			{ 0x29640100 },
		},
		{
			{ 0x29640200},
			{ 0x29640300},
		},
	},
};

static const T_IM_PRO_SRO_SDC_INFO	S_G_IM_PRO_SDC_STATUS_TBL[ImproBase_E_IM_PRO_UNIT_NUM_MAX]
                                  	                          	  	  	  [ImproSrosdc_D_IM_PRO_SRO_SDC_CH_NUM] = {
	// ImproBase_E_IM_PRO_UNIT_NUM_1
	{
		{ &IO_PRO_TBL.SRO1_TBL.SDCGD[0][0],	ImproSrosdc_D_IM_SRO1_STATUS_SDC0	},
		{ &IO_PRO_TBL.SRO1_TBL.SDCGD[1][0],	ImproSrosdc_D_IM_SRO1_STATUS_SDC1	},
	},
	// ImproBase_E_IM_PRO_UNIT_NUM_2
	{
		{ &IO_PRO_TBL.SRO2_TBL.SDCGD[0][0],	ImproSrosdc_D_IM_SRO2_STATUS_SDC0	},
		{ &IO_PRO_TBL.SRO2_TBL.SDCGD[1][0],	ImproSrosdc_D_IM_SRO2_STATUS_SDC1	},
	},
	// ImproBase_E_IM_PRO_BOTH_UNIT
	{
		{ &IO_PRO_TBL.SRO3_TBL.SDCGD[0][0],	ImproSrosdc_D_IM_SRO_STATUS_SDC0_BOTH	},
		{ &IO_PRO_TBL.SRO3_TBL.SDCGD[1][0],	ImproSrosdc_D_IM_SRO_STATUS_SDC1_BOTH	},
	},
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_srosdc_constructor(ImproSrosdc *self)
{
	ImproSrosdcPrivate *priv = IMPRO_SROSDC_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_srosdc_destructor(ImproSrosdc *self)
{
	ImproSrosdcPrivate *priv = IMPRO_SROSDC_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/

VOID impro_srosdc_comm_get_sdc_reg_info( E_IM_PRO_UNIT_NUM unitNo, EimproSdcCh ch, const T_IM_PRO_SRO_SDC_INFO** sdcInfo )
{
	*sdcInfo = &S_G_IM_PRO_SDC_STATUS_TBL[unitNo][ch];
}

/**
Compensation mode start
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@retval		D_DDIM_OK					: Processing OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: PRCH not running NG
*/
INT32 impro_srosdc_start( E_IM_PRO_UNIT_NUM unitNo, EimproSdcCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdctrg.bit.sdctrg = D_IM_PRO_TRG_START;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_START_STATUS(S_G_IM_PRO_SDC_STATUS_TBL[unitNo][ch].status, 0);

	return D_DDIM_OK;
}

/**
Compensation mode stop
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Processing OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: PRCH not stopped NG
*/
INT32 impro_srosdc_stop( E_IM_PRO_UNIT_NUM unitNo, EimproSdcCh ch, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	if(force == 0) {
		// stop
		ioPro.imgPipe[unitNo].sro.sdc[ch].sdctrg.bit.sdctrg = D_IM_PRO_TRG_FRAME_STOP;
	}
	else {
		// force stop
		ioPro.imgPipe[unitNo].sro.sdc[ch].sdctrg.bit.sdctrg = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_STOP_STATUS(S_G_IM_PRO_SDC_STATUS_TBL[unitNo][ch].status, 0);

	return D_DDIM_OK;
}

/**
SDC control setup
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@param[in]	sdcCtrl : SDC control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srosdc_ctrl( E_IM_PRO_UNIT_NUM unitNo, EimproSdcCh ch, TimproSdcCtrl* sdcCtrl )
{
#ifdef CO_PARAM_CHECK
	if (sdcCtrl == NULL){
		Ddim_Assertion(("I:impro_srosdc_ctrl error. sdcCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcctl.bit.sdcmd		= sdcCtrl->sdcMode;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcctl.bit.sdcpto		= sdcCtrl->afpbOutputPtn;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcctl.bit.sdcmono		= sdcCtrl->monochromeMode;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcctl.bit.sdcpdafen	= sdcCtrl->afpbEnabled;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Select SDC gain table.
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@param[in]	tblSel : SDC gain table select.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srosdc_select_gain_table( E_IM_PRO_UNIT_NUM unitNo, EimproSdcCh ch, EimproSdcGainTableSel tblSel )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcsgd.bit.sdcsgd	= tblSel;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
set SDC gain table.
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@param[in]	sdcAfpbCtrl : SDC AFPB control information.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srosdc_ctrl_afpb( E_IM_PRO_UNIT_NUM unitNo, EimproSdcCh ch, TimproSdcCtrlAfpb* sdcAfpbCtrl )
{
#ifdef CO_PARAM_CHECK
	if (sdcAfpbCtrl == NULL){
		Ddim_Assertion(("I:impro_srosdc_ctrl_afpb error. sdcAfpbCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	for(UINT32 i = 0; i < 9; i++) {
		if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPHW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPHW_MAX,
				sdcAfpbCtrl->hPattern0ValidWidth[i], "impro_srosdc_ctrl_afpb : hPattern0ValidWidth" ) == FALSE ) {
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
		if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPHW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPHW_MAX,
				sdcAfpbCtrl->hPattern1ValidWidth[i], "impro_srosdc_ctrl_afpb : hPattern1ValidWidth" ) == FALSE ) {
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
		if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPxHW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPxHW_MAX,
				sdcAfpbCtrl->hPattern0R1ValidWidth[i], "impro_srosdc_ctrl_afpb : hPattern0R1ValidWidth" ) == FALSE ) {
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
		if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPxHW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPxHW_MAX,
				sdcAfpbCtrl->hPattern1R1ValidWidth[i], "impro_srosdc_ctrl_afpb : hPattern1R1ValidWidth" ) == FALSE ) {
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
		if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPxHW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPxHW_MAX,
				sdcAfpbCtrl->hPattern0R2ValidWidth[i], "impro_srosdc_ctrl_afpb : hPattern0R2ValidWidth" ) == FALSE ) {
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
		if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPxHW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPxHW_MAX,
				sdcAfpbCtrl->hPattern1R2ValidWidth[i], "impro_srosdc_ctrl_afpb : hPattern1R2ValidWidth" ) == FALSE ) {
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
		if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCNxHW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCNxHW_MAX,
				sdcAfpbCtrl->hPattern0R1InvalidWidth[i], "impro_srosdc_ctrl_afpb : hPattern0R1InvalidWidth" ) == FALSE ) {
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
		if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCNxHW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCNxHW_MAX,
				sdcAfpbCtrl->hPattern1R1InvalidWidth[i], "impro_srosdc_ctrl_afpb : hPattern1R1InvalidWidth" ) == FALSE ) {
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
		if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCNxHW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCNxHW_MAX,
				sdcAfpbCtrl->hPattern0R2InvalidWidth[i], "impro_srosdc_ctrl_afpb : hPattern0R2InvalidWidth" ) == FALSE ) {
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
		if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCNxHW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCNxHW_MAX,
				sdcAfpbCtrl->hPattern1R2InvalidWidth[i], "impro_srosdc_ctrl_afpb : hPattern1R2InvalidWidth" ) == FALSE ) {
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
	};
	for(UINT32 i = 0; i < 64; i++) {
		if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPC_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPC_MAX,
				sdcAfpbCtrl->hColumnPattern0[i], "impro_srosdc_ctrl_afpb : hColumnPattern0" ) == FALSE ) {
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
		if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPC_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPC_MAX,
				sdcAfpbCtrl->hColumnPattern1[i], "impro_srosdc_ctrl_afpb : hColumnPattern1" ) == FALSE ) {
			return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
		}
	};
	if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPCW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPCW_MAX,
			sdcAfpbCtrl->hColumnPatternValidWidth0, "impro_srosdc_ctrl_afpb : hColumnPatternValidWidth0" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPCW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPCW_MAX,
			sdcAfpbCtrl->hColumnPatternValidWidth1, "impro_srosdc_ctrl_afpb : hColumnPatternValidWidth1" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPxCW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPxCW_MAX,
			sdcAfpbCtrl->hColumnPattern1ValidWidth0, "impro_srosdc_ctrl_afpb : hColumnPattern1ValidWidth0" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPxCW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPxCW_MAX,
			sdcAfpbCtrl->hColumnPattern1ValidWidth1, "impro_srosdc_ctrl_afpb : hColumnPattern1ValidWidth1" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPxCW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPxCW_MAX,
			sdcAfpbCtrl->hColumnPattern2ValidWidth0, "impro_srosdc_ctrl_afpb : hColumnPattern2ValidWidth0" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCPxCW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPxCW_MAX,
			sdcAfpbCtrl->hColumnPattern2ValidWidth1, "impro_srosdc_ctrl_afpb : hColumnPattern2ValidWidth1" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCNxCW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCPxCW_MAX,
			sdcAfpbCtrl->hColumnPattern1InvalidWidth0, "impro_srosdc_ctrl_afpb : hColumnPattern1InvalidWidth0" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCNxCW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCNxCW_MAX,
			sdcAfpbCtrl->hColumnPattern1InvalidWidth1, "impro_srosdc_ctrl_afpb : hColumnPattern1InvalidWidth1" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCN2CW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCN2CW_MAX,
			sdcAfpbCtrl->hColumnPattern2InvalidWidth0, "impro_srosdc_ctrl_afpb : hColumnPattern2InvalidWidth0" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCN2CW_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCN2CW_MAX,
			sdcAfpbCtrl->hColumnPattern2InvalidWidth1, "impro_srosdc_ctrl_afpb : hColumnPattern2InvalidWidth1" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( im_pro_check_val_range( ImproSrosdc_D_IM_PRO_SDC_SDCNMAX_MIN, ImproSrosdc_D_IM_PRO_SDC_SDCNMAX_MAX,
			sdcAfpbCtrl->afpbNeighborPixelCorrectionLevel, "impro_srosdc_ctrl_afpb : afpbNeighborPixelCorrectionLevel" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph01.bit.sdcph00		= sdcAfpbCtrl->hPattern0[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph02.bit.sdcph01		= sdcAfpbCtrl->hPattern0[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph03.bit.sdcph02		= sdcAfpbCtrl->hPattern0[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph04.bit.sdcph03		= sdcAfpbCtrl->hPattern0[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph05.bit.sdcph04		= sdcAfpbCtrl->hPattern0[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph06.bit.sdcph05		= sdcAfpbCtrl->hPattern0[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph07.bit.sdcph06		= sdcAfpbCtrl->hPattern0[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph08.bit.sdcph07		= sdcAfpbCtrl->hPattern0[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph09.bit.sdcph08		= sdcAfpbCtrl->hPattern0[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph11.bit.sdcph10		= sdcAfpbCtrl->hPattern1[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph12.bit.sdcph11		= sdcAfpbCtrl->hPattern1[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph13.bit.sdcph12		= sdcAfpbCtrl->hPattern1[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph14.bit.sdcph13		= sdcAfpbCtrl->hPattern1[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph15.bit.sdcph14		= sdcAfpbCtrl->hPattern1[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph16.bit.sdcph15		= sdcAfpbCtrl->hPattern1[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph17.bit.sdcph16		= sdcAfpbCtrl->hPattern1[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph18.bit.sdcph17		= sdcAfpbCtrl->hPattern1[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph19.bit.sdcph18		= sdcAfpbCtrl->hPattern1[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw0.sdcphw01.bit.sdcphw00		= sdcAfpbCtrl->hPattern0ValidWidth[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw0.sdcphw01.bit.sdcphw01		= sdcAfpbCtrl->hPattern0ValidWidth[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw0.sdcphw01.bit.sdcphw02		= sdcAfpbCtrl->hPattern0ValidWidth[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw0.sdcphw01.bit.sdcphw03		= sdcAfpbCtrl->hPattern0ValidWidth[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw0.sdcphw02.bit.sdcphw04		= sdcAfpbCtrl->hPattern0ValidWidth[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw0.sdcphw02.bit.sdcphw05		= sdcAfpbCtrl->hPattern0ValidWidth[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw0.sdcphw02.bit.sdcphw06		= sdcAfpbCtrl->hPattern0ValidWidth[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw0.sdcphw02.bit.sdcphw07		= sdcAfpbCtrl->hPattern0ValidWidth[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw0.sdcphw03.bit.sdcphw08		= sdcAfpbCtrl->hPattern0ValidWidth[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw1.sdcphw11.bit.sdcphw10		= sdcAfpbCtrl->hPattern1ValidWidth[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw1.sdcphw11.bit.sdcphw11		= sdcAfpbCtrl->hPattern1ValidWidth[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw1.sdcphw11.bit.sdcphw12		= sdcAfpbCtrl->hPattern1ValidWidth[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw1.sdcphw11.bit.sdcphw13		= sdcAfpbCtrl->hPattern1ValidWidth[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw1.sdcphw12.bit.sdcphw14		= sdcAfpbCtrl->hPattern1ValidWidth[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw1.sdcphw12.bit.sdcphw15		= sdcAfpbCtrl->hPattern1ValidWidth[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw1.sdcphw12.bit.sdcphw16		= sdcAfpbCtrl->hPattern1ValidWidth[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw1.sdcphw12.bit.sdcphw17		= sdcAfpbCtrl->hPattern1ValidWidth[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcphw1.sdcphw13.bit.sdcphw18		= sdcAfpbCtrl->hPattern1ValidWidth[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw01.bit.sdcp1hw00	= sdcAfpbCtrl->hPattern0R1ValidWidth[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw01.bit.sdcp1hw01	= sdcAfpbCtrl->hPattern0R1ValidWidth[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw02.bit.sdcp1hw02	= sdcAfpbCtrl->hPattern0R1ValidWidth[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw02.bit.sdcp1hw03	= sdcAfpbCtrl->hPattern0R1ValidWidth[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw03.bit.sdcp1hw04	= sdcAfpbCtrl->hPattern0R1ValidWidth[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw03.bit.sdcp1hw05	= sdcAfpbCtrl->hPattern0R1ValidWidth[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw04.bit.sdcp1hw06	= sdcAfpbCtrl->hPattern0R1ValidWidth[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw04.bit.sdcp1hw07	= sdcAfpbCtrl->hPattern0R1ValidWidth[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw05.bit.sdcp1hw08	= sdcAfpbCtrl->hPattern0R1ValidWidth[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw11.bit.sdcp1hw10	= sdcAfpbCtrl->hPattern1R1ValidWidth[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw11.bit.sdcp1hw11	= sdcAfpbCtrl->hPattern1R1ValidWidth[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw12.bit.sdcp1hw12	= sdcAfpbCtrl->hPattern1R1ValidWidth[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw12.bit.sdcp1hw13	= sdcAfpbCtrl->hPattern1R1ValidWidth[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw13.bit.sdcp1hw14	= sdcAfpbCtrl->hPattern1R1ValidWidth[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw13.bit.sdcp1hw15	= sdcAfpbCtrl->hPattern1R1ValidWidth[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw14.bit.sdcp1hw16	= sdcAfpbCtrl->hPattern1R1ValidWidth[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw14.bit.sdcp1hw17	= sdcAfpbCtrl->hPattern1R1ValidWidth[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw15.bit.sdcp1hw18	= sdcAfpbCtrl->hPattern1R1ValidWidth[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw01.bit.sdcn1hw00	= sdcAfpbCtrl->hPattern0R1InvalidWidth[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw01.bit.sdcn1hw01	= sdcAfpbCtrl->hPattern0R1InvalidWidth[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw02.bit.sdcn1hw02	= sdcAfpbCtrl->hPattern0R1InvalidWidth[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw02.bit.sdcn1hw03	= sdcAfpbCtrl->hPattern0R1InvalidWidth[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw03.bit.sdcn1hw04	= sdcAfpbCtrl->hPattern0R1InvalidWidth[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw03.bit.sdcn1hw05	= sdcAfpbCtrl->hPattern0R1InvalidWidth[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw04.bit.sdcn1hw06	= sdcAfpbCtrl->hPattern0R1InvalidWidth[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw04.bit.sdcn1hw07	= sdcAfpbCtrl->hPattern0R1InvalidWidth[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw05.bit.sdcn1hw08	= sdcAfpbCtrl->hPattern0R1InvalidWidth[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw11.bit.sdcn1hw10	= sdcAfpbCtrl->hPattern1R1InvalidWidth[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw11.bit.sdcn1hw11	= sdcAfpbCtrl->hPattern1R1InvalidWidth[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw12.bit.sdcn1hw12	= sdcAfpbCtrl->hPattern1R1InvalidWidth[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw12.bit.sdcn1hw13	= sdcAfpbCtrl->hPattern1R1InvalidWidth[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw13.bit.sdcn1hw14	= sdcAfpbCtrl->hPattern1R1InvalidWidth[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw13.bit.sdcn1hw15	= sdcAfpbCtrl->hPattern1R1InvalidWidth[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw14.bit.sdcn1hw16	= sdcAfpbCtrl->hPattern1R1InvalidWidth[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw14.bit.sdcn1hw17	= sdcAfpbCtrl->hPattern1R1InvalidWidth[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw15.bit.sdcn1hw18	= sdcAfpbCtrl->hPattern1R1InvalidWidth[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw01.bit.sdcp2hw00	= sdcAfpbCtrl->hPattern0R2ValidWidth[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw01.bit.sdcp2hw01	= sdcAfpbCtrl->hPattern0R2ValidWidth[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw02.bit.sdcp2hw02	= sdcAfpbCtrl->hPattern0R2ValidWidth[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw02.bit.sdcp2hw03	= sdcAfpbCtrl->hPattern0R2ValidWidth[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw03.bit.sdcp2hw04	= sdcAfpbCtrl->hPattern0R2ValidWidth[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw03.bit.sdcp2hw05	= sdcAfpbCtrl->hPattern0R2ValidWidth[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw04.bit.sdcp2hw06	= sdcAfpbCtrl->hPattern0R2ValidWidth[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw04.bit.sdcp2hw07	= sdcAfpbCtrl->hPattern0R2ValidWidth[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw05.bit.sdcp2hw08	= sdcAfpbCtrl->hPattern0R2ValidWidth[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw11.bit.sdcp2hw10	= sdcAfpbCtrl->hPattern1R2ValidWidth[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw11.bit.sdcp2hw11	= sdcAfpbCtrl->hPattern1R2ValidWidth[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw12.bit.sdcp2hw12	= sdcAfpbCtrl->hPattern1R2ValidWidth[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw12.bit.sdcp2hw13	= sdcAfpbCtrl->hPattern1R2ValidWidth[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw13.bit.sdcp2hw14	= sdcAfpbCtrl->hPattern1R2ValidWidth[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw13.bit.sdcp2hw15	= sdcAfpbCtrl->hPattern1R2ValidWidth[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw14.bit.sdcp2hw16	= sdcAfpbCtrl->hPattern1R2ValidWidth[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw14.bit.sdcp2hw17	= sdcAfpbCtrl->hPattern1R2ValidWidth[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw15.bit.sdcp2hw18	= sdcAfpbCtrl->hPattern1R2ValidWidth[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw01.bit.sdcn2hw00	= sdcAfpbCtrl->hPattern0R2InvalidWidth[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw01.bit.sdcn2hw01	= sdcAfpbCtrl->hPattern0R2InvalidWidth[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw02.bit.sdcn2hw02	= sdcAfpbCtrl->hPattern0R2InvalidWidth[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw02.bit.sdcn2hw03	= sdcAfpbCtrl->hPattern0R2InvalidWidth[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw03.bit.sdcn2hw04	= sdcAfpbCtrl->hPattern0R2InvalidWidth[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw03.bit.sdcn2hw05	= sdcAfpbCtrl->hPattern0R2InvalidWidth[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw04.bit.sdcn2hw06	= sdcAfpbCtrl->hPattern0R2InvalidWidth[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw04.bit.sdcn2hw07	= sdcAfpbCtrl->hPattern0R2InvalidWidth[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw05.bit.sdcn2hw08	= sdcAfpbCtrl->hPattern0R2InvalidWidth[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw11.bit.sdcn2hw10	= sdcAfpbCtrl->hPattern1R2InvalidWidth[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw11.bit.sdcn2hw11	= sdcAfpbCtrl->hPattern1R2InvalidWidth[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw12.bit.sdcn2hw12	= sdcAfpbCtrl->hPattern1R2InvalidWidth[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw12.bit.sdcn2hw13	= sdcAfpbCtrl->hPattern1R2InvalidWidth[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw13.bit.sdcn2hw14	= sdcAfpbCtrl->hPattern1R2InvalidWidth[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw13.bit.sdcn2hw15	= sdcAfpbCtrl->hPattern1R2InvalidWidth[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw14.bit.sdcn2hw16	= sdcAfpbCtrl->hPattern1R2InvalidWidth[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw14.bit.sdcn2hw17	= sdcAfpbCtrl->hPattern1R2InvalidWidth[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw15.bit.sdcn2hw18	= sdcAfpbCtrl->hPattern1R2InvalidWidth[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.bit.sdcpc00		= sdcAfpbCtrl->hColumnPattern0[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.bit.sdcpc01		= sdcAfpbCtrl->hColumnPattern0[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.bit.sdcpc02		= sdcAfpbCtrl->hColumnPattern0[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.bit.sdcpc03		= sdcAfpbCtrl->hColumnPattern0[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.bit.sdcpc04		= sdcAfpbCtrl->hColumnPattern0[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.bit.sdcpc05		= sdcAfpbCtrl->hColumnPattern0[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.bit.sdcpc06		= sdcAfpbCtrl->hColumnPattern0[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.bit.sdcpc07		= sdcAfpbCtrl->hColumnPattern0[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.bit.sdcpc08		= sdcAfpbCtrl->hColumnPattern0[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.bit.sdcpc09		= sdcAfpbCtrl->hColumnPattern0[9];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.bit.sdcpc010		= sdcAfpbCtrl->hColumnPattern0[10];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.bit.sdcpc011		= sdcAfpbCtrl->hColumnPattern0[11];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.bit.sdcpc012		= sdcAfpbCtrl->hColumnPattern0[12];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.bit.sdcpc013		= sdcAfpbCtrl->hColumnPattern0[13];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.bit.sdcpc014		= sdcAfpbCtrl->hColumnPattern0[14];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.bit.sdcpc015		= sdcAfpbCtrl->hColumnPattern0[15];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.bit.sdcpc016		= sdcAfpbCtrl->hColumnPattern0[16];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.bit.sdcpc017		= sdcAfpbCtrl->hColumnPattern0[17];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.bit.sdcpc018		= sdcAfpbCtrl->hColumnPattern0[18];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.bit.sdcpc019		= sdcAfpbCtrl->hColumnPattern0[19];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.bit.sdcpc020		= sdcAfpbCtrl->hColumnPattern0[20];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.bit.sdcpc021		= sdcAfpbCtrl->hColumnPattern0[21];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.bit.sdcpc022		= sdcAfpbCtrl->hColumnPattern0[22];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.bit.sdcpc023		= sdcAfpbCtrl->hColumnPattern0[23];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.bit.sdcpc024		= sdcAfpbCtrl->hColumnPattern0[24];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.bit.sdcpc025		= sdcAfpbCtrl->hColumnPattern0[25];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.bit.sdcpc026		= sdcAfpbCtrl->hColumnPattern0[26];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.bit.sdcpc027		= sdcAfpbCtrl->hColumnPattern0[27];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.bit.sdcpc028		= sdcAfpbCtrl->hColumnPattern0[28];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.bit.sdcpc029		= sdcAfpbCtrl->hColumnPattern0[29];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.bit.sdcpc030		= sdcAfpbCtrl->hColumnPattern0[30];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.bit.sdcpc031		= sdcAfpbCtrl->hColumnPattern0[31];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.bit.sdcpc032		= sdcAfpbCtrl->hColumnPattern0[32];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.bit.sdcpc033		= sdcAfpbCtrl->hColumnPattern0[33];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.bit.sdcpc034		= sdcAfpbCtrl->hColumnPattern0[34];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.bit.sdcpc035		= sdcAfpbCtrl->hColumnPattern0[35];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.bit.sdcpc036		= sdcAfpbCtrl->hColumnPattern0[36];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.bit.sdcpc037		= sdcAfpbCtrl->hColumnPattern0[37];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.bit.sdcpc038		= sdcAfpbCtrl->hColumnPattern0[38];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.bit.sdcpc039		= sdcAfpbCtrl->hColumnPattern0[39];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.bit.sdcpc040		= sdcAfpbCtrl->hColumnPattern0[40];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.bit.sdcpc041		= sdcAfpbCtrl->hColumnPattern0[41];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.bit.sdcpc042		= sdcAfpbCtrl->hColumnPattern0[42];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.bit.sdcpc043		= sdcAfpbCtrl->hColumnPattern0[43];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.bit.sdcpc044		= sdcAfpbCtrl->hColumnPattern0[44];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.bit.sdcpc045		= sdcAfpbCtrl->hColumnPattern0[45];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.bit.sdcpc046		= sdcAfpbCtrl->hColumnPattern0[46];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.bit.sdcpc047		= sdcAfpbCtrl->hColumnPattern0[47];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.bit.sdcpc048		= sdcAfpbCtrl->hColumnPattern0[48];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.bit.sdcpc049		= sdcAfpbCtrl->hColumnPattern0[49];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.bit.sdcpc050		= sdcAfpbCtrl->hColumnPattern0[50];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.bit.sdcpc051		= sdcAfpbCtrl->hColumnPattern0[51];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.bit.sdcpc052		= sdcAfpbCtrl->hColumnPattern0[52];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.bit.sdcpc053		= sdcAfpbCtrl->hColumnPattern0[53];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.bit.sdcpc054		= sdcAfpbCtrl->hColumnPattern0[54];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.bit.sdcpc055		= sdcAfpbCtrl->hColumnPattern0[55];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.bit.sdcpc056		= sdcAfpbCtrl->hColumnPattern0[56];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.bit.sdcpc057		= sdcAfpbCtrl->hColumnPattern0[57];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.bit.sdcpc058		= sdcAfpbCtrl->hColumnPattern0[58];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.bit.sdcpc059		= sdcAfpbCtrl->hColumnPattern0[59];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.bit.sdcpc060		= sdcAfpbCtrl->hColumnPattern0[60];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.bit.sdcpc061		= sdcAfpbCtrl->hColumnPattern0[61];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.bit.sdcpc062		= sdcAfpbCtrl->hColumnPattern0[62];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.bit.sdcpc063		= sdcAfpbCtrl->hColumnPattern0[63];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.bit.sdcpc10		= sdcAfpbCtrl->hColumnPattern1[0];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.bit.sdcpc11		= sdcAfpbCtrl->hColumnPattern1[1];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.bit.sdcpc12		= sdcAfpbCtrl->hColumnPattern1[2];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.bit.sdcpc13		= sdcAfpbCtrl->hColumnPattern1[3];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.bit.sdcpc14		= sdcAfpbCtrl->hColumnPattern1[4];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.bit.sdcpc15		= sdcAfpbCtrl->hColumnPattern1[5];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.bit.sdcpc16		= sdcAfpbCtrl->hColumnPattern1[6];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.bit.sdcpc17		= sdcAfpbCtrl->hColumnPattern1[7];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.bit.sdcpc18		= sdcAfpbCtrl->hColumnPattern1[8];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.bit.sdcpc19		= sdcAfpbCtrl->hColumnPattern1[9];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.bit.sdcpc110		= sdcAfpbCtrl->hColumnPattern1[10];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.bit.sdcpc111		= sdcAfpbCtrl->hColumnPattern1[11];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.bit.sdcpc112		= sdcAfpbCtrl->hColumnPattern1[12];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.bit.sdcpc113		= sdcAfpbCtrl->hColumnPattern1[13];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.bit.sdcpc114		= sdcAfpbCtrl->hColumnPattern1[14];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.bit.sdcpc115		= sdcAfpbCtrl->hColumnPattern1[15];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.bit.sdcpc116		= sdcAfpbCtrl->hColumnPattern1[16];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.bit.sdcpc117		= sdcAfpbCtrl->hColumnPattern1[17];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.bit.sdcpc118		= sdcAfpbCtrl->hColumnPattern1[18];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.bit.sdcpc119		= sdcAfpbCtrl->hColumnPattern1[19];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.bit.sdcpc120		= sdcAfpbCtrl->hColumnPattern1[20];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.bit.sdcpc121		= sdcAfpbCtrl->hColumnPattern1[21];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.bit.sdcpc122		= sdcAfpbCtrl->hColumnPattern1[22];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.bit.sdcpc123		= sdcAfpbCtrl->hColumnPattern1[23];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.bit.sdcpc124		= sdcAfpbCtrl->hColumnPattern1[24];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.bit.sdcpc125		= sdcAfpbCtrl->hColumnPattern1[25];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.bit.sdcpc126		= sdcAfpbCtrl->hColumnPattern1[26];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.bit.sdcpc127		= sdcAfpbCtrl->hColumnPattern1[27];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.bit.sdcpc128		= sdcAfpbCtrl->hColumnPattern1[28];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.bit.sdcpc129		= sdcAfpbCtrl->hColumnPattern1[29];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.bit.sdcpc130		= sdcAfpbCtrl->hColumnPattern1[30];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.bit.sdcpc131		= sdcAfpbCtrl->hColumnPattern1[31];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.bit.sdcpc132		= sdcAfpbCtrl->hColumnPattern1[32];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.bit.sdcpc133		= sdcAfpbCtrl->hColumnPattern1[33];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.bit.sdcpc134		= sdcAfpbCtrl->hColumnPattern1[34];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.bit.sdcpc135		= sdcAfpbCtrl->hColumnPattern1[35];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.bit.sdcpc136		= sdcAfpbCtrl->hColumnPattern1[36];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.bit.sdcpc137		= sdcAfpbCtrl->hColumnPattern1[37];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.bit.sdcpc138		= sdcAfpbCtrl->hColumnPattern1[38];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.bit.sdcpc139		= sdcAfpbCtrl->hColumnPattern1[39];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.bit.sdcpc140		= sdcAfpbCtrl->hColumnPattern1[40];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.bit.sdcpc141		= sdcAfpbCtrl->hColumnPattern1[41];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.bit.sdcpc142		= sdcAfpbCtrl->hColumnPattern1[42];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.bit.sdcpc143		= sdcAfpbCtrl->hColumnPattern1[43];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.bit.sdcpc144		= sdcAfpbCtrl->hColumnPattern1[44];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.bit.sdcpc145		= sdcAfpbCtrl->hColumnPattern1[45];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.bit.sdcpc146		= sdcAfpbCtrl->hColumnPattern1[46];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.bit.sdcpc147		= sdcAfpbCtrl->hColumnPattern1[47];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.bit.sdcpc148		= sdcAfpbCtrl->hColumnPattern1[48];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.bit.sdcpc149		= sdcAfpbCtrl->hColumnPattern1[49];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.bit.sdcpc150		= sdcAfpbCtrl->hColumnPattern1[50];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.bit.sdcpc151		= sdcAfpbCtrl->hColumnPattern1[51];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.bit.sdcpc152		= sdcAfpbCtrl->hColumnPattern1[52];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.bit.sdcpc153		= sdcAfpbCtrl->hColumnPattern1[53];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.bit.sdcpc154		= sdcAfpbCtrl->hColumnPattern1[54];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.bit.sdcpc155		= sdcAfpbCtrl->hColumnPattern1[55];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.bit.sdcpc156		= sdcAfpbCtrl->hColumnPattern1[56];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.bit.sdcpc157		= sdcAfpbCtrl->hColumnPattern1[57];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.bit.sdcpc158		= sdcAfpbCtrl->hColumnPattern1[58];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.bit.sdcpc159		= sdcAfpbCtrl->hColumnPattern1[59];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.bit.sdcpc160		= sdcAfpbCtrl->hColumnPattern1[60];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.bit.sdcpc161		= sdcAfpbCtrl->hColumnPattern1[61];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.bit.sdcpc162		= sdcAfpbCtrl->hColumnPattern1[62];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.bit.sdcpc163		= sdcAfpbCtrl->hColumnPattern1[63];
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpcw0.bit.sdcpcw0				= sdcAfpbCtrl->hColumnPatternValidWidth0;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcpcw1.bit.sdcpcw1				= sdcAfpbCtrl->hColumnPatternValidWidth1;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1cw0.bit.sdcp1cw0				= sdcAfpbCtrl->hColumnPattern1ValidWidth0;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp1cw1.bit.sdcp1cw1				= sdcAfpbCtrl->hColumnPattern1ValidWidth1;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2cw0.bit.sdcp2cw0				= sdcAfpbCtrl->hColumnPattern2ValidWidth0;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcp2cw1.bit.sdcp2cw1				= sdcAfpbCtrl->hColumnPattern2ValidWidth1;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1cw0.bit.sdcn1cw0				= sdcAfpbCtrl->hColumnPattern1InvalidWidth0;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn1cw1.bit.sdcn1cw1				= sdcAfpbCtrl->hColumnPattern1InvalidWidth1;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2cw0.bit.sdcn2cw0				= sdcAfpbCtrl->hColumnPattern2InvalidWidth0;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcn2cw1.bit.sdcn2cw1				= sdcAfpbCtrl->hColumnPattern2InvalidWidth1;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcgmaxmin.bit.sdcgmax				= sdcAfpbCtrl->afpbGainCorrectionUThreshold;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcgmaxmin.bit.sdcgmin				= sdcAfpbCtrl->afpbGainCorrectionIThreshold;
	ioPro.imgPipe[unitNo].sro.sdc[ch].sdcnmax.bit.sdcnmax				= sdcAfpbCtrl->afpbNeighborPixelCorrectionLevel;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
set SDC gain table.
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@param[in]	tblSel : SDC gain table select.
@param[in]	gainTable : SDC gain table information.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srosdc_set_gain_table( E_IM_PRO_UNIT_NUM unitNo, EimproSdcCh ch, EimproSdcGainTableSel tblSel,
				TimproSdcGainTable* gainTable )
{
#ifdef CO_PARAM_CHECK
	if (gainTable == NULL){
		Ddim_Assertion(("I:impro_srosdc_set_gain_table error. gainTable=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( ( ioPro.imgPipe[unitNo].sro.sdc[ch].sdctrg.bit.sdctrg != D_IM_PRO_TRG_STATUS_STOPPED )
			&& ( ioPro.imgPipe[unitNo].sro.sdc[ch].SDCSGD.bit.SDCSGD == tblSel ) ) {
		Ddim_Assertion(("I:impro_srosdc_set_gain_table error. macro has not stopped, "
				"and RAM table that referrenced from SDC can not overwrite until macro stopping.\n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_hclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	for( INT32 i = 0; i < ImproSrosdc_D_IM_PRO_SDC_GAIN_TBL_NUM; i++ ) {
		S_G_IM_PRO_SDC_STATUS_TBL[unitNo][ch].tbl_reg_ptr[tblSel].bit[i].SDCGD	= gainTable->gainTable[i];
	}
	// Dd_Top_Stop_Clock
	im_pro_off_hclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of SDC.
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srosdc_set_paen( E_IM_PRO_UNIT_NUM unitNo, EimproSdcCh ch, UCHAR paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( ioPro.imgPipe[unitNo].sro.sdc[ch].sdctrg.bit.sdctrg != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:impro_sensldiv_set_paen. macro has not stopped error.\n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.sdc[ch].SDCPAEN.bit.SDCPAEN = paenTrg;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Get the top address of the address array of SDC control.
@param[in]		unitNo : Unit number.
@param[in]		ch : Channel No
@param[out]		addr					: Top address of the address array of SDC control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 impro_srosdc_get_rdma_addr_sdc_cntl( E_IM_PRO_UNIT_NUM unitNo, EimproSdcCh ch,
				const TimproRdmaSdcAddr** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:impro_srosdc_get_rdma_addr_sdc_cntl. error. addr=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &S_G_IM_PRO_SDC_ADDR[unitNo][ch];

	return D_DDIM_OK;
}


INT32 impro_srosdc_get_rdma_addr_sdc_gain_tbl( E_IM_PRO_UNIT_NUM unitNo, EimproSdcCh ch,
				EimproSdcGainTableSel tblSel, const TimproRdmaSdcGainTblAddr** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:impro_srosdc_get_rdma_addr_sdc_gain_tbl. error. addr=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &gIM_PRO_SDC_Gain_Tbl_Addr[unitNo][ch][tblSel];

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSrosdc类的一个实例
 *
 */
ImproSrosdc* 	impro_srosdc_new()
{
	ImproSrosdc* self = k_object_new_with_private(IMPRO_TYPE_SROSDC,sizeof(ImproSrosdcPrivate));
	ImproSrosdcPrivate* priv = IMPRO_SROSDC_GET_PRIVATE(self);
	
	e_warning_o(self," impro_srosdc_new \n");
	return self;
}
