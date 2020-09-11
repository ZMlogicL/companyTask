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

#ifndef  __DD_TOP_H__
#define __DD_TOP_H__

/**
@addtogroup lsi_top
@{
*/

#include "ddim_typedef.h"
#include "driver_common.h"
#include "kchiptop3.h"
#include "dd_arm.h"
#include "ddtopone.h"
#include "ddtopthree.h"
#include "ddtoptwo.h"
#include "ddtopfour.h"
#include <glib-object.h>


G_BEGIN_DECLS


#define DD_TYPE_TOP								(dd_top_get_type ())
#define DD_TOP(obj)								(G_TYPE_CHECK_INSTANCE_CAST ((obj), DD_TYPE_TOP, DdTop))
#define DD_TOP_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST((klass), DD_TYPE_TOP, DdTopClass))
#define DD_IS_TOP(obj)							(G_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_TOP))
#define DD_IS_TOP_CLASS(klass)		 	(G_TYPE_CHECK_CLASS_TYPE ((klass), DD_TYPE_TOP))
#define DD_TOP_GET_CLASS(obj)			(G_TYPE_INSTANCE_GET_CLASS ((obj), DD_TYPE_TOP, DdTopClass))


typedef struct 	_DdTop 					DdTop;
typedef struct 	_DdTopClass 			DdTopClass;
typedef struct 	_DdTopPrivate 		DdTopPrivate;

struct _DdTop{
	GObject parent;
};

struct _DdTopClass{
	GObjectClass parentclass;
};

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/** GPIO port name */
typedef enum {
	DdTop_GPIO_P60	= 0,			/**< GPIO port P60 */
	DdTop_GPIO_P61,				/**< GPIO port P61 */
	DdTop_GPIO_P62,				/**< GPIO port P62 */
	DdTop_GPIO_P63,				/**< GPIO port P63 */
	DdTop_GPIO_P64,				/**< GPIO port P64 */
	DdTop_GPIO_P65,				/**< GPIO port P65 */
	DdTop_GPIO_P66,				/**< GPIO port P66 */
	DdTop_GPIO_P67,				/**< GPIO port P67 */
	DdTop_GPIO_P70,				/**< GPIO port P70 */
	DdTop_GPIO_P71,				/**< GPIO port P71 */
	DdTop_GPIO_P72,				/**< GPIO port P72 */
	DdTop_GPIO_P73,				/**< GPIO port P73 */
	DdTop_GPIO_P74,				/**< GPIO port P74 */
	DdTop_GPIO_P75,				/**< GPIO port P75 */
	DdTop_GPIO_P76,				/**< GPIO port P76 */
	DdTop_GPIO_P77,				/**< GPIO port P77 */
	DdTop_GPIO_P80,				/**< GPIO port P80 */
	DdTop_GPIO_P81,				/**< GPIO port P81 */
	DdTop_GPIO_P82,				/**< GPIO port P82 */
	DdTop_GPIO_P83,				/**< GPIO port P83 */
	DdTop_GPIO_P84,				/**< GPIO port P84 */
	DdTop_GPIO_P85,				/**< GPIO port P85 */
	DdTop_GPIO_P86,				/**< GPIO port P86 */
	DdTop_GPIO_P87,				/**< GPIO port P87 */
	DdTop_GPIO_P90,				/**< GPIO port P90 */
	DdTop_GPIO_P91,				/**< GPIO port P91 */
	DdTop_GPIO_P92,				/**< GPIO port P92 */
	DdTop_GPIO_P93,				/**< GPIO port P93 */
	DdTop_GPIO_PA0,				/**< GPIO port PA0 */
	DdTop_GPIO_PA1,				/**< GPIO port PA1 */
	DdTop_GPIO_PA2,				/**< GPIO port PA2 */
	DdTop_GPIO_PA3,				/**< GPIO port PA3 */
	DdTop_GPIO_PA4,				/**< GPIO port PA4 */
	DdTop_GPIO_PA5,				/**< GPIO port PA5 */
	DdTop_GPIO_PA6,				/**< GPIO port PA6 */
	DdTop_GPIO_PA7,				/**< GPIO port PB7 */
	DdTop_GPIO_PB0,				/**< GPIO port PB0 */
	DdTop_GPIO_PB1,				/**< GPIO port PB1 */
	DdTop_GPIO_PB2,				/**< GPIO port PB2 */
	DdTop_GPIO_PB3,				/**< GPIO port PB3 */
	DdTop_GPIO_PB4,				/**< GPIO port PB4 */
	DdTop_GPIO_PC0L,				/**< GPIO port PC0L */
	DdTop_GPIO_PC1L,				/**< GPIO port PC1L */
	DdTop_GPIO_PC2L,				/**< GPIO port PC2L */
	DdTop_GPIO_PC3L,				/**< GPIO port PC3L */
	DdTop_GPIO_PC4L,				/**< GPIO port PC4L */
	DdTop_GPIO_PC5L,				/**< GPIO port PC5L */
	DdTop_GPIO_PD0,				/**< GPIO port PD0 */
	DdTop_GPIO_PD1,				/**< GPIO port PD1 */
	DdTop_GPIO_PD2,				/**< GPIO port PD2 */
	DdTop_GPIO_PD3,				/**< GPIO port PD3 */
	DdTop_GPIO_PD4,				/**< GPIO port PD4 */
	DdTop_GPIO_PD5,				/**< GPIO port PD5 */
	DdTop_GPIO_PD6,				/**< GPIO port PD6 */
	DdTop_GPIO_PE0,				/**< GPIO port PE0 */
	DdTop_GPIO_PE1,				/**< GPIO port PE1 */
	DdTop_GPIO_PE2,				/**< GPIO port PE2 */
	DdTop_GPIO_PE3,				/**< GPIO port PE3 */
	DdTop_GPIO_PE4,				/**< GPIO port PE4 */
	DdTop_GPIO_PE5,				/**< GPIO port PE5 */
	DdTop_GPIO_PF0,				/**< GPIO port PF0 */
	DdTop_GPIO_PF1,				/**< GPIO port PF1 */
	DdTop_GPIO_PF2,				/**< GPIO port PF2 */
	DdTop_GPIO_PF3,				/**< GPIO port PF3 */
	DdTop_GPIO_PF4,				/**< GPIO port PF4 */
	DdTop_GPIO_PG0,				/**< GPIO port PG0 */
	DdTop_GPIO_PG1,				/**< GPIO port PG1 */
	DdTop_GPIO_PG2,				/**< GPIO port PG2 */
	DdTop_GPIO_PG3,				/**< GPIO port PG3 */
	DdTop_GPIO_PG4,				/**< GPIO port PG4 */
	DdTop_GPIO_PG5,				/**< GPIO port PG5 */
	DdTop_GPIO_PG6,				/**< GPIO port PG6 */
	DdTop_GPIO_PG7,				/**< GPIO port PG7 */
	DdTop_GPIO_PH0,				/**< GPIO port PH0 */
	DdTop_GPIO_PH1,				/**< GPIO port PH1 */
	DdTop_GPIO_PH2,				/**< GPIO port PH2 */
	DdTop_GPIO_PH3,				/**< GPIO port PH3 */
	DdTop_GPIO_PW0,				/**< GPIO port PW0 */
	DdTop_GPIO_PW1,				/**< GPIO port PW1 */
	DdTop_GPIO_PW2,				/**< GPIO port PW2 */
	DdTop_GPIO_PW3,				/**< GPIO port PW3 */
	DdTop_GPIO_PW4,				/**< GPIO port PW4 */
	DdTop_GPIO_PW5,				/**< GPIO port PW5 */
	DdTop_GPIO_PW6,				/**< GPIO port PW6 */
	DdTop_GPIO_PW7,				/**< GPIO port PW7 */
	DdTop_GPIO_PJ0,				/**< GPIO port PJ0 */
	DdTop_GPIO_PJ1,				/**< GPIO port PJ1 */
	DdTop_GPIO_PJ2,				/**< GPIO port PJ2 */
	DdTop_GPIO_PJ3,				/**< GPIO port PJ3 */
	DdTop_GPIO_PJ4,				/**< GPIO port PJ4 */
	DdTop_GPIO_PJ5,				/**< GPIO port PJ5 */
	DdTop_GPIO_PJ6,				/**< GPIO port PJ6 */
	DdTop_GPIO_PJ7,				/**< GPIO port PJ7 */
	DdTop_GPIO_PK0,				/**< GPIO port PK0 */
	DdTop_GPIO_PK1,				/**< GPIO port PK1 */
	DdTop_GPIO_PK2,				/**< GPIO port PK2 */
	DdTop_GPIO_PK3,				/**< GPIO port PK3 */
	DdTop_GPIO_PK4,				/**< GPIO port PK4 */
	DdTop_GPIO_PK5,				/**< GPIO port PK5 */
	DdTop_GPIO_PK6,				/**< GPIO port PK6 */
	DdTop_GPIO_PK7,				/**< GPIO port PK7 */
	DdTop_GPIO_PL0,				/**< GPIO port PL0 */
	DdTop_GPIO_PL1,				/**< GPIO port PL1 */
	DdTop_GPIO_PL2,				/**< GPIO port PL2 */
	DdTop_GPIO_PL3,				/**< GPIO port PL3 */
	DdTop_GPIO_PL4,				/**< GPIO port PL4 */
	DdTop_GPIO_PL5,				/**< GPIO port PL5 */
	DdTop_GPIO_PM0,				/**< GPIO port PM0 */
	DdTop_GPIO_PM1,				/**< GPIO port PM1 */
	DdTop_GPIO_PM2,				/**< GPIO port PM2 */
	DdTop_GPIO_PM3,				/**< GPIO port PM3 */
	DdTop_GPIO_PM4,				/**< GPIO port PM4 */
	DdTop_GPIO_PN0,				/**< GPIO port PN0 */
	DdTop_GPIO_PN1,				/**< GPIO port PN1 */
	DdTop_GPIO_PN2,				/**< GPIO port PN2 */
	DdTop_GPIO_PN3,				/**< GPIO port PN3 */
	DdTop_GPIO_PN4,				/**< GPIO port PN4 */
	DdTop_GPIO_PY0,				/**< GPIO port PY0 */
	DdTop_GPIO_PY1,				/**< GPIO port PY1 */
	DdTop_GPIO_PY2,				/**< GPIO port PY2 */
	DdTop_GPIO_PY3,				/**< GPIO port PY3 */
	DdTop_GPIO_PY4,				/**< GPIO port PY4 */
	DdTop_GPIO_PY5,				/**< GPIO port PY5 */
	DdTop_GPIO_PY6,				/**< GPIO port PY6 */
	DdTop_GPIO_PY7,				/**< GPIO port PY7 */
	DdTop_GPIO_PP0,				/**< GPIO port PP0 */
	DdTop_GPIO_PP1,				/**< GPIO port PP1 */
	DdTop_GPIO_PP2,				/**< GPIO port PP2 */
	DdTop_GPIO_PP3,				/**< GPIO port PP3 */
	DdTop_GPIO_PORT_MAX			/**< GPIO port maximum value */
} DdTop_GPIO_PORT;

#if 1    // special key control
/** GPIO CM0 port name */
typedef enum {
	DdTop_GPIO_CM0_P00	= 0,	/**< GPIO CM0 port P00 */
	DdTop_GPIO_CM0_P01,			/**< GPIO CM0 port P01 */
	DdTop_GPIO_CM0_P02,			/**< GPIO CM0 port P02 */
	DdTop_GPIO_CM0_P03,			/**< GPIO CM0 port P03 */
	DdTop_GPIO_CM0_P04,			/**< GPIO CM0 port P04 */
	DdTop_GPIO_CM0_P05,			/**< GPIO CM0 port P05 */
	DdTop_GPIO_CM0_P06,			/**< GPIO CM0 port P06 */
	DdTop_GPIO_CM0_P07,			/**< GPIO CM0 port P07 */
	DdTop_GPIO_CM0_P10,			/**< GPIO CM0 port P10 */
	DdTop_GPIO_CM0_P11,			/**< GPIO CM0 port P11 */
	DdTop_GPIO_CM0_P12,			/**< GPIO CM0 port P12 */
	DdTop_GPIO_CM0_P13,			/**< GPIO CM0 port P13 */
	DdTop_GPIO_CM0_P14,			/**< GPIO CM0 port P14 */
	DdTop_GPIO_CM0_P15,			/**< GPIO CM0 port P15 */
	DdTop_GPIO_CM0_P16,			/**< GPIO CM0 port P16 */
	DdTop_GPIO_CM0_P17,			/**< GPIO CM0 port P17 */
	DdTop_GPIO_CM0_P20,			/**< GPIO CM0 port P20 */
	DdTop_GPIO_CM0_P21,			/**< GPIO CM0 port P21 */
	DdTop_GPIO_CM0_P22,			/**< GPIO CM0 port P22 */
	DdTop_GPIO_CM0_P23,			/**< GPIO CM0 port P23 */
	DdTop_GPIO_CM0_P24,			/**< GPIO CM0 port P24 */
	DdTop_GPIO_CM0_P25,			/**< GPIO CM0 port P25 */
	DdTop_GPIO_CM0_P26,			/**< GPIO CM0 port P26 */
	DdTop_GPIO_CM0_P27,			/**< GPIO CM0 port P27 */
	DdTop_GPIO_CM0_P30,			/**< GPIO CM0 port P30 */
	DdTop_GPIO_CM0_P31,			/**< GPIO CM0 port P31 */
	DdTop_GPIO_CM0_P32,			/**< GPIO CM0 port P32 */
	DdTop_GPIO_CM0_P33,			/**< GPIO CM0 port P33 */
	DdTop_GPIO_CM0_P34,			/**< GPIO CM0 port P34 */
	DdTop_GPIO_CM0_P35,			/**< GPIO CM0 port P35 */
	DdTop_GPIO_CM0_P36,			/**< GPIO CM0 port P36 */
	DdTop_GPIO_CM0_P37,			/**< GPIO CM0 port P37 */
	DdTop_GPIO_CM0_P44,			/**< GPIO CM0 port P44 */
	DdTop_GPIO_CM0_P45,			/**< GPIO CM0 port P45 */
	DdTop_GPIO_CM0_P46,			/**< GPIO CM0 port P46 */
	DdTop_GPIO_CM0_PORT_MAX		/**< GPIO CM0 port maximum value */
} DdTop_GPIO_CM0_PORT;
#endif

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
//@cond
extern ULONG gDD_Top_Spin_Lock __attribute__((section(".LOCK_SECTION"), aligned(64)));
//@endcond

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/

								/**< Set Cortex-A7 MPCore CPU3 Reset Clear */


/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

GType 								dd_top_get_type(void) G_GNUC_CONST;
DdTop* 							dd_top_new(void);

/**
Get Frequency of eMMC clock
@retval	Hz
*/
ULONG dd_topone_get_emmcclk(VOID);

/**
Get Frequency of NAND Flash clock
@retval	Hz
*/
ULONG dd_topone_get_nfclk(VOID);

/**
Get Frequency of UHS2 clock
@retval	Hz
*/
ULONG dd_topone_get_uhs2clk(VOID);

/**
Get Frequency of UHS1 ch2 clock
@retval	Hz
*/
ULONG dd_topone_get_uhs1clk2(VOID);

/**
Get Frequency of UHS1 ch1 clock
@retval	Hz
*/
ULONG dd_topone_get_uhs1clk1(VOID);

/**
Get Frequency of UHS1 ch0 clock
@retval	Hz
*/
ULONG dd_topone_get_uhs1clk0(VOID);

/**
Get Frequency of Cortex-A7 MPCore Peri clock
@retval	Hz
*/
ULONG dd_topone_get_rclk(VOID);

/**
Get Frequency of RAW clock
@retval	Hz
*/
ULONG dd_topone_get_rawclk(VOID);

/**
Get Frequency of DISP HIF clock
@retval	Hz
*/
ULONG dd_topone_get_hifclk(VOID);

/**
Get Frequency of DISP MIF clock
@retval	Hz
*/
ULONG dd_topone_get_mifclk(VOID);

/**
Get Frequency of IPU system clock
@retval	Hz
*/
ULONG dd_topone_get_ipuclk(VOID);

/**
Get Frequency of IPU TME clock
@retval	Hz
*/
ULONG dd_topone_get_iputmeclk(VOID);

/**
Get Frequency of GPU clock
@retval	Hz
*/
ULONG dd_topone_get_gpuclk(VOID);

/**
Get Frequency of JPEG clock
@retval	Hz
*/
ULONG DdTopone_Get_JPEGCLK(VOID);

/**
Get Frequency of ELA clock
@retval	Hz
*/
ULONG dd_topone_get_elaclk(VOID);

/**
Get Frequency of SENSOR clock
@retval	Hz
*/
ULONG dd_topone_get_senclk(VOID);

/**
Get Frequency of SENSOR clock
@retval	Hz
*/
ULONG dd_topone_get_senmskclk(VOID);

/**
Get Frequency of IIP clock
@retval	Hz
*/
ULONG dd_topone_get_iipclk(VOID);

/**
Get Frequency of STAT clock
@retval	Hz
*/
ULONG dd_topone_get_pasclk(VOID);

/**
Get Frequency of HEVC IPP clock
@retval	Hz
*/
ULONG dd_topone_get_ippclk(VOID);

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
/**
Get Frequency of HEVC PXF clock
@retval	Hz
*/
ULONG dd_topone_get_pxfclk(VOID);
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**
Get Frequency of HEVC ENC clock
@retval	Hz
*/
ULONG dd_topone_get_hevencclk(VOID);
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

/**
Get Frequency of HEVC VDF clock
@retval	Hz
*/
ULONG dd_topone_get_vdfclk(VOID);

/**
Get Frequency of SRO pipe1 input2 clock
@retval	Hz
*/
ULONG dd_topone_get_sro1clk_2(VOID);

/**
Get Frequency of R2Y pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_r2y1clk(VOID);

/**
Get Frequency of LTM pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_ltm1clk(VOID);

/**
Get Frequency of B2R pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_b2r1clk(VOID);

/**
Get Frequency of CNR pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_cnr1clk(VOID);

/**
Get Frequency of SRO pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_sro1clk(VOID);

/**
Get Frequency of B2B pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_b2b1clk(VOID);

/**
Get Frequency of LTMRBK pipe1 clock
@retval	Hz
*/
ULONG dd_topone_get_ltmrbk1clk(VOID);

/**
Get Frequency of SRO pipe2 input2 clock
@retval	Hz
*/
ULONG dd_topone_get_sro2clk_2(VOID);

/**
Get Frequency of R2Y pipe2 clock
@retval	Hz
*/
ULONG dd_topone_get_r2y2clk(VOID);

/**
Get Frequency of LTM pipe2 clock
@retval	Hz
*/
ULONG dd_top_get_ltm2clk(VOID);

/**
Get Frequency of B2R pipe2 clock
@retval	Hz
*/
ULONG dd_top_get_b2r2clk(VOID);

/**
Get Frequency of CNR pipe2 clock
@retval	Hz
*/
ULONG dd_top_get_cnr2clk(VOID);

/**
Get Frequency of SRO pipe2 clock
@retval	Hz
*/
ULONG dd_top_get_sro2clk(VOID);

/**
Get Frequency of B2B pipe2 clock
@retval	Hz
*/
ULONG dd_top_get_b2b2clk(VOID);

/**
Get Frequency of LTMRBK pipe2 clock
@retval	Hz
*/
ULONG dd_top_get_ltmrbk2clk(VOID);

/**
Get Frequency of APCLK clock
@retval	Hz
*/
ULONG dd_top_get_apclk(VOID);

/**
Get Frequency of Audio clock
@retval	Hz
*/
ULONG dd_top_get_auclk(VOID);

/**
Get Frequency of SPI clock
@retval	Hz
*/
ULONG dd_top_get_spiclk(VOID);

/**
Get Frequency of DSP clock
@retval	Hz
*/
ULONG dd_toptwo_get_dspclk(VOID);

/**
Get Frequency of AXI bus clock
@retval	Hz
*/
ULONG dd_toptwo_get_aclk(VOID);

/**
Get Frequency of AXI bus EXS clock
@retval	Hz
*/
ULONG dd_toptwo_get_aclkexs(VOID);

/**
Get Frequency of AHB bus BMH clock
@retval	Hz
*/
ULONG dd_toptwo_get_hclkbmh(VOID);

/**
Get Frequency of AHB bus clock
@retval	Hz
*/
ULONG dd_toptwo_get_hclk(VOID);

/**
Get Frequency of APB bus clock
@retval	Hz
*/
ULONG dd_toptwo_get_pclk(VOID);

/**
Get Frequency of MXI bus 400 clock
@retval	Hz
*/
ULONG dd_toptwo_get_mclk400(VOID);

/**
Get Frequency of MXI bus 200 clock
@retval	Hz
*/
ULONG dd_toptwo_get_mclk200(VOID);

/**
Get Frequency of AXI bus 400 clock
@retval	Hz
*/
ULONG dd_toptwo_get_aclk400(VOID);

/**
Get Frequency of RIBERY clock
@retval	Hz
*/
ULONG dd_topthree_get_ribclk(VOID);

/**
Get Frequency of NF Bch clock
@retval	Hz
*/
ULONG dd_topthree_get_nfbchclk(VOID);

/**
Get Frequency of ME clock
@retval	Hz
*/
ULONG dd_topthree_get_meclk(VOID);

/**
Get Frequency of FPT1 clock
@retval	Hz
*/
ULONG dd_topthree_get_fpt1clk(VOID);

/**
Get Frequency of FPT0 clock
@retval	Hz
*/
ULONG dd_topthree_get_fpt0clk(VOID);

/**
Get Frequency of 3DNR clock
@retval	Hz
*/
ULONG dd_toptwo_get_shdrclk(VOID);

/**
Get Frequency of GYRO clock
@retval	Hz
*/
ULONG dd_topthree_get_gyroclk(VOID);

/**
Get Frequency of AXI bus 300 clock
@retval	Hz
*/
ULONG dd_topthree_get_aclk300(VOID);


/**
Control Clock Stop to start clock.<br>
@param[in,out]	counter		address of Garding counter
@param[in,out]	reg_addr	address of clock stop register
@param[in]		val			setting value
@remarks Set 1 to XXXSTOPC register internally.<br><br>
		*(reg_addr + DdTopone_CLKSTOPC_OFFSET) |= ~val
*/
VOID dd_topthree_start_clock(DdTopthree *self, UCHAR* counter, volatile unsigned long* reg_addr, unsigned long val );

/**
Control Clock Stop to stop clock.
@param[in,out]	counter		address of Garding counter
@param[in,out]	reg_addr	address of clock stop register
@param[in]		val			setting value
@remarks Set 1 to XXXSTOPS register internally.<br><br>
		*(reg_addr + DdTopone_CLKSTOPS_OFFSET) |= val
*/
VOID dd_topthree_stop_clock(DdTopthree *self, UCHAR* counter, volatile unsigned long* reg_addr, unsigned long val );

/**
Start PLL00.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll00(VOID);

/**
Stop PLL00.
*/
VOID dd_topthree_stop_pll00(VOID);

/**
Start PLL01.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll01(VOID);

/**
Stop PLL01.
*/
VOID dd_topthree_stop_pll01(VOID);

/**
Start PLL02.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll02(VOID);

/**
Stop PLL02.
*/
VOID dd_topthree_stop_pll02(VOID);

/**
Start PLL03.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll03(VOID);

/**
Stop PLL03.
*/
VOID dd_topthree_stop_pll03(VOID);

/**
Start PLL04.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll04(VOID);

/**
Stop PLL04.
*/
VOID dd_topthree_stop_pll04(VOID);

/**
Start PLL05.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll05(VOID);

/**
Stop PLL05.
*/
VOID dd_topthree_stop_pll05(VOID);

/**
Start PLL05A.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll05a(VOID);

/**
Stop PLL05A.
*/
VOID dd_topthree_stop_pll05a(VOID);

/**
Start PLL06.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll06(VOID);

/**
Stop PLL06.
*/
VOID dd_topthree_stop_pll06(VOID);

/**
Start PLL07.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll07(VOID);

/**
Stop PLL07.
*/
VOID dd_topthree_stop_pll07(VOID);

/**
Start PLL08.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll08(VOID);

/**
Stop PLL08.
*/
VOID dd_topthree_stop_pll08(VOID);

/**
Start PLL10.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll10(VOID);

/**
Stop PLL10.
*/
VOID dd_topthree_stop_pll10(VOID);

/**
Start PLL10A.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll10a(VOID);

/**
Stop PLL100A.
*/
VOID dd_topthree_stop_pll10a(VOID);

/**
Start PLL11.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_pll11(VOID);

/**
Stop PLL11.
*/
VOID dd_topthree_stop_pll11(VOID);

/**
Start DDR 00 PLL.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_ddr_pll00(VOID);

/**
Stop DDR PLL00.
*/
VOID dd_topthree_stop_ddr_pll00(VOID);

/**
Start DDR PLL01.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_ddr_pll01(VOID);

/**
Stop DDR PLL01.
*/
VOID dd_topthree_stop_ddr_pll01(VOID);

/**
Start DDR PLL02.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_ddr_pll02(VOID);

/**
Stop DDR PLL02.
*/
VOID dd_topthree_stop_ddr_pll02(VOID);

/**
Start DDR PLL10.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_ddr_pll10(VOID);

/**
Stop DDR PLL10.
*/
VOID dd_topthree_stop_ddr_pll10(VOID);

/**
Start DDR PLL11.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_ddr_pll11(VOID);

/**
Stop DDR PLL11.
*/
VOID dd_topthree_stop_ddr_pll11(VOID);

/**
Start DDR PLL12.
@retval	D_DD_OK						Success
@retval	DdTopone_STATUS_ABNORMAL	Fail - output condition
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 dd_topthree_start_ddr_pll12(VOID);

/**
Stop DDR PLL12.
*/
VOID dd_topthree_stop_ddr_pll12(VOID);


/**
Set parameters for Audio PLL.
@param [in]	clock		select clock
@param [in]	select[]	ch0-ch3 select Audio Clock(Internal clock or External clock)<br>
						<ul><li>select[0]:Audio ch0 Clock
							<li>select[1]:Audio ch1 Clock
							<li>select[2]:Audio ch2 Clock
							<li>select[3]:Audio Ethernet Clock</ul>
@param [in]	pll_select	Audio PLL select
*/
VOID DdTopone_Set_Aud_Pll(UCHAR clock, UCHAR const *const select, UCHAR pll_select);

/**
Get Frequency of Audio PLL.
@retval	Hz
*/
ULONG DdTopone_Get_Aud_Pll(VOID);

/**
Set the functionality of a selectable GPIO port.<br>
It is set to the EPCR(External Port Control Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [in]  function	Function type.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_FUNC_GPIO
							  <li>1:@ref DdToptwo_GPIO_FUNC_HWMODE
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Input parameter error.
*/
INT32 dd_topfour_set_gpio_function(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR function );

/**
Get the functionality of a selectable GPIO port.<br>
It is get from the EPCR(External Port Control Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [out] function	Function type.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_FUNC_GPIO
							  <li>1:@ref DdToptwo_GPIO_FUNC_HWMODE
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Input parameter error.
*/
INT32 dd_topfour_get_gpio_function(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR* function );

/**
Set the direction of a selectable GPIO port.<br>
It is set to the DDR(Data Direction Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [in]  direction	Direction type.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_DIR_IN
							  <li>1:@ref DdToptwo_GPIO_DIR_OUT
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_topthree_set_gpio_direction(DdTopthree *self, DdTop_GPIO_PORT port, UCHAR direction );

/**
Get the direction of a selectable GPIO port.<br>
It is get from the DDR(Data Direction Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [out] direction	Direction type.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_DIR_IN
							  <li>1:@ref DdToptwo_GPIO_DIR_OUT
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_topfour_get_gpio_direction(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR* direction );

/**
Set the state of a selectable GPIO port.<br>
It is set to the PDR(Port Data Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [in]  status		Port status.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_STATUS_LOW
							  <li>1:@ref DdToptwo_GPIO_STATUS_HIGH
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_toptwo_set_gpio_status(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR status );

/**
Get the state of a selectable GPIO port.<br>
It is get from the PDR(Port Data Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [out] status		Port status.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_STATUS_LOW
							  <li>1:@ref DdToptwo_GPIO_STATUS_HIGH
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_topfour_get_gpio_status(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR* status );

#if 1    // special key control
INT32 dd_toptwo_set_gpio_cm0_function(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR function );
INT32 dd_toptwo_get_gpio_cm0_function(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR* function );
INT32 dd_toptwo_set_gpio_cm0_direction(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR direction );
INT32 dd_toptwo_get_gpio_cm0_direction(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR* direction );
INT32 dd_toptwo_set_gpio_cm0_pull_up_down_enable(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR enable );
INT32 dd_toptwo_get_gpio_cm0_pull_up_down_enable(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR* enable );
INT32 dd_toptwo_set_gpio_cm0_pull_up_down_ctrl(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR control );
INT32 dd_toptwo_get_gpio_cm0_pull_up_down_ctrl(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR* control );
INT32 dd_toptwo_set_gpio_cm0_status(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR status );
/**
Get the state of a selectable GPIO CM0 port.<br>
It is get from the PDR(Port Data Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_CM0_PORT
@param [out] status		Port status.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_STATUS_LOW
							  <li>1:@ref DdToptwo_GPIO_STATUS_HIGH
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_toptwo_get_gpio_cm0_status(DdToptwo *self, DdTop_GPIO_CM0_PORT port, UCHAR* status );
#endif

/**
Set the Pull-up/down enable state of a selectable GPIO port.<br>
It is set to the PUDER(Pull-up/down Enable Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [in]  enable		Pull-up/down enable state.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_PUD_OFF
							  <li>1:@ref DdToptwo_GPIO_PUD_ON
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_top_set_gpio_pull_up_down_enable(DdTop *self, DdTop_GPIO_PORT port, UCHAR enable );

/**
Get the Pull-up/down enable state of a selectable GPIO port.<br>
It is get from the PUDER(Pull-up/down Enable Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [out] enable		Pull-up/down enable state.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_PUD_OFF
							  <li>1:@ref DdToptwo_GPIO_PUD_ON
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_top_get_gpio_pull_up_down_enable(DdTop *self, DdTop_GPIO_PORT port, UCHAR* enable );

/**
Set the Pull-up/down state of a selectable GPIO port.<br>
It is set to the PUDCR(Pull-up/down Control Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [in]  control	Pull-up/down state.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_PUD_DOWN
							  <li>1:@ref DdToptwo_GPIO_PUD_UP
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_top_set_gpio_pull_up_down_ctrl(DdTop *self, DdTop_GPIO_PORT port, UCHAR control );

/**
Get the Pull-up/down state of a selectable GPIO port.<br>
It is get from the PUDCR(Pull-up/down Control Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [out] control	Pull-up/down state.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_PUD_DOWN
							  <li>1:@ref DdToptwo_GPIO_PUD_UP
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_top_get_gpio_pull_up_down_ctrl( DdTop *selfm, DdTop_GPIO_PORT port, UCHAR* control );

#ifdef __cplusplus
}
#endif

/*@}*/
G_END_DECLS

#endif /* __DD_TOP_H__ */
