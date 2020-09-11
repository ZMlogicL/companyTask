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


#ifndef __IMPRO_SROSDC_H__
#define __IMPRO_SROSDC_H__


#include <klib.h>
#include "improbase.h"
#include "improsrotop.h"

#define IMPRO_TYPE_SROSDC        (impro_srosdc_get_type())
#define IMPRO_SROSDC(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSrosdc))
#define IMPRO_IS_SROSDC(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SROSDC))


/*宏定义区域*/
	/**< Number of SRO SDC		*/
#define ImproSrosdc_D_IM_PRO_SRO_SDC_CH_NUM			(E_IM_PRO_SDC_CH1 + 1)

/** @addtogroup im_pro_sro_sdc SDC
@{
*/
/**< Minimum setting of SDCPHW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCPHW_MIN			(0)
/**< Maximum setting of SDCPHW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCPHW_MAX			(64)
/**< Minimum setting of SDCPxHW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCPxHW_MIN		(0)
/**< Maximum setting of SDCPxHW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCPxHW_MAX		(8191)
/**< Minimum setting of SDCNxHW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCNxHW_MIN		(0)
/**< Maximum setting of SDCNxHW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCNxHW_MAX		(8191)
/**< Minimum setting of SDCPC	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCPC_MIN			(0)
/**< Maximum setting of SDCPC	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCPC_MAX			(8)
/**< Minimum setting of SDCPCW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCPCW_MIN			(0)
/**< Maximum setting of SDCPCW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCPCW_MAX			(64)
/**< Minimum setting of SDCPxCW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCPxCW_MIN		(0)
/**< Maximum setting of SDCPxCW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCPxCW_MAX		(8191)
/**< Minimum setting of SDCNxCW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCNxCW_MIN		(0)
/**< Maximum setting of SDCNxCW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCNxCW_MAX		(8191)
/**< Minimum setting of SDCN2CW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCN2CW_MIN		(1)
/**< Maximum setting of SDCN2CW	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCN2CW_MAX		(8191)
/**< Minimum setting of SDCNMAX	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCNMAX_MIN		(0)
/**< Maximum setting of SDCNMAX	*/
#define	ImproSrosdc_D_IM_PRO_SDC_SDCNMAX_MAX		(3)
/*	@}*/	// im_pro_sro_sdc
/** @addtogroup im_pro_sro_sdc SDC
@{
*/
/**< index Number of SDC gain table.	*/
#define	ImproSrosdc_D_IM_PRO_SDC_GAIN_TBL_NUM		(128)
/*	@}*/	// im_pro_sro_sdc


/*其他结构体或类型定义区域*/
/** SDC Gain Table Select.
*/
typedef enum {
	/**< Gain coefficient table RAM0 (SDCGDTBL0) is selected.	*/
	ImproSrosdc_E_IM_PRO_SDC_GAIN_TABLE_SEL_0 = 0,
	/**< Gain coefficient table RAM1 (SDCGDTBL1) is selected.	*/
	ImproSrosdc_E_IM_PRO_SDC_GAIN_TABLE_SEL_1,
} EimproSdcGainTableSel;

/** Defect correction mode select
*/
typedef enum {
	/**< Static defect correction */
	ImproSrosdc_E_IM_PRO_SDC_MODE_SDC = 0,
	/**< Static defect correction + Gain correction  */
	ImproSrosdc_E_IM_PRO_SDC_MODE_SDC_GAIN,
	/**< DPC macro cooperative defect correction + Phase difference AF pixel output */
	ImproSrosdc_E_IM_PRO_SDC_MODE_COOP_DPC_AFPB,
	/**< DPC macro cooperative defect correction + Phase difference AF pixel output + Gain correction1 */
	ImproSrosdc_E_IM_PRO_SDC_MODE_COOP_DPC_AFPB_GAIN1,
	/**< DPC macro cooperative defect correction + Phase difference AF pixel output + Gain correction2 */
	ImproSrosdc_E_IM_PRO_SDC_MODE_COOP_DPC_AFPB_GAIN2,
} EimproSdcMode;

/** Phase difference AF pixel pattern output setting.
*/
typedef enum {
	/**< (Phase difference AF pixel pattern output + Static defect correction) processing
	 *  or static defect correction only.	*/
	ImproSrosdc_E_IM_PRO_SDC_AFPB_OUTPUT_PTN_ALL_OR_SDC_ONLY = 0,
	/**< Phase difference AF pixel pattern output only.  */
	ImproSrosdc_E_IM_PRO_SDC_AFPB_OUTPUT_PTN_AFOB_ONLY,
} EimproSdcAfpbOutputPtn;

/** Defect correction monochrome mode select.
*/
typedef enum {
	/**< Static defect correction Bayer correction mode.	*/
	ImproSrosdc_E_IM_PRO_SDC_MONOCHROME_MODE_BAYER_CORRECTION = 0,
	/**< Static defect correction  monochrome correction mode.	*/
	ImproSrosdc_E_IM_PRO_SDC_MONOCHROME_MODE_MONOCHROME_CORRECTION,
} EimproSdcMonochromeMode;

/** Phase difference AF pixel pattern output enable.
*/
typedef enum {
	/**< Phase difference AF pixel pattern output is OFF.	*/
	ImproSrosdc_E_IM_PRO_SDC_AFPB_DIS = 0,
	/**< Phase difference AF pixel pattern output is ON.	*/
	ImproSrosdc_E_IM_PRO_SDC_AFPB_EN,
} EimproSdcAfpbEnable;


/** RDMA I/F SDC register address information
*/
typedef struct {
	/**< 2840_(8808 - 880Bh) */
	ULONG	sdcctl;
	/**< 2840_(8814 - 8817h) */
	ULONG	sdcsgd;
	/**< 2840_(8880 - 8883h) */
	ULONG	sdcph01_0;
	/**< 2840_(8884 - 8887h) */
	ULONG	sdcph01_1;
	/**< 2840_(8888 - 888Bh) */
	ULONG	sdcph02_0;
	/**< 2840_(888C - 888Fh) */
	ULONG	sdcph02_1;
	/**< 2840_(8890 - 8893h) */
	ULONG	sdcph03_0;
	/**< 2840_(8894 - 8897h) */
	ULONG	sdcph03_1;
	/**< 2840_(8898 - 889Bh) */
	ULONG	sdcph04_0;
	/**< 2840_(889C - 889Fh) */
	ULONG	sdcph04_1;
	/**< 2840_(88A0 - 88A3h) */
	ULONG	sdcph05_0;
	/**< 2840_(88A4 - 88A7h) */
	ULONG	sdcph05_1;
	/**< 2840_(88A8 - 88ABh) */
	ULONG	sdcph06_0;
	/**< 2840_(88AC - 88AFh) */
	ULONG	sdcph06_1;
	/**< 2840_(88B0 - 88B3h) */
	ULONG	sdcph07_0;
	/**< 2840_(88B4 - 88B7h) */
	ULONG	sdcph07_1;
	/**< 2840_(88B8 - 88BBh) */
	ULONG	sdcph08_0;
	/**< 2840_(88BC - 88BFh) */
	ULONG	sdcph08_1;
	/**< 2840_(88C0 - 88C3h) */
	ULONG	sdcph09_0;
	/**< 2840_(88C4 - 88C7h) */
	ULONG	sdcph09_1;
	/**< 2840_(8900 - 8903h) */
	ULONG	sdcph11_0;
	/**< 2840_(8904 - 8907h) */
	ULONG	sdcph11_1;
	/**< 2840_(8908 - 890Bh) */
	ULONG	sdcph12_0;
	/**< 2840_(890C - 890Fh) */
	ULONG	sdcph12_1;
	/**< 2840_(8910 - 8913h) */
	ULONG	sdcph13_0;
	/**< 2840_(8914 - 8917h) */
	ULONG	sdcph13_1;
	/**< 2840_(8918 - 891Bh) */
	ULONG	sdcph14_0;
	/**< 2840_(891C - 891Fh) */
	ULONG	sdcph14_1;
	/**< 2840_(8920 - 8923h) */
	ULONG	sdcph15_0;
	/**< 2840_(8924 - 8927h) */
	ULONG	sdcph15_1;
	/**< 2840_(8928 - 892Bh) */
	ULONG	sdcph16_0;
	/**< 2840_(892C - 892Fh) */
	ULONG	sdcph16_1;
	/**< 2840_(8930 - 8933h) */
	ULONG	sdcph17_0;
	/**< 2840_(8934 - 8937h) */
	ULONG	sdcph17_1;
	/**< 2840_(8938 - 893Bh) */
	ULONG	sdcph18_0;
	/**< 2840_(893C - 893Fh) */
	ULONG	sdcph18_1;
	/**< 2840_(8940 - 8943h) */
	ULONG	sdcph19_0;
	/**< 2840_(8944 - 8947h) */
	ULONG	sdcph19_1;
	/**< 2840_(8980 - 8983h) */
	ULONG	sdcphw01;
	/**< 2840_(8984 - 8987h) */
	ULONG	sdcphw02;
	/**< 2840_(8988 - 898Bh) */
	ULONG	sdcphw03;
	/**< 2840_(8990 - 8993h) */
	ULONG	sdcphw10;
	/**< 2840_(8994 - 8997h) */
	ULONG	sdcphw11;
	/**< 2840_(8998 - 899Bh) */
	ULONG	sdcphw12;
	/**< 2840_(89A0 - 89A3h) */
	ULONG	sdcp1hw01;
	/**< 2840_(89A4 - 89A7h) */
	ULONG	sdcp1hw02;
	/**< 2840_(89A8 - 89ABh) */
	ULONG	sdcp1hw03;
	/**< 2840_(89AC - 89AFh) */
	ULONG	sdcp1hw04;
	/**< 2840_(89B0 - 89B3h) */
	ULONG	sdcp1hw05;
	/**< 2840_(89C0 - 89C3h) */
	ULONG	sdcp1hw11;
	/**< 2840_(89C4 - 89C7h) */
	ULONG	sdcp1hw12;
	/**< 2840_(89C8 - 89CBh) */
	ULONG	sdcp1hw13;
	/**< 2840_(89CC - 89CFh) */
	ULONG	sdcp1hw14;
	/**< 2840_(89D0 - 89D3h) */
	ULONG	sdcp1hw15;
	/**< 2840_(89E0 - 89E3h) */
	ULONG	sdcn1hw01;
	/**< 2840_(89E4 - 89E7h) */
	ULONG	sdcn1hw02;
	/**< 2840_(89E8 - 89EBh) */
	ULONG	sdcn1hw03;
	/**< 2840_(89EC - 89EFh) */
	ULONG	sdcn1hw04;
	/**< 2840_(89F0 - 89F3h) */
	ULONG	sdcn1hw05;
	/**< 2840_(8A00 - 8A03h) */
	ULONG	sdcn1hw11;
	/**< 2840_(8A04 - 8A07h) */
	ULONG	sdcn1hw12;
	/**< 2840_(8A08 - 8A0Bh) */
	ULONG	sdcn1hw13;
	/**< 2840_(8A0C - 8A0Fh) */
	ULONG	sdcn1hw14;
	/**< 2840_(8A10 - 8A13h) */
	ULONG	sdcn1hw15;
	/**< 2840_(8A20 - 8A23h) */
	ULONG	sdcp2hw01;
	/**< 2840_(8A24 - 8A27h) */
	ULONG	sdcp2hw02;
	/**< 2840_(8A28 - 8A2Bh) */
	ULONG	sdcp2hw03;
	/**< 2840_(8A2C - 8A2Fh) */
	ULONG	sdcp2hw04;
	/**< 2840_(8A30 - 8A33h) */
	ULONG	sdcp2hw05;
	/**< 2840_(8A40 - 8A43h) */
	ULONG	sdcp2hw11;
	/**< 2840_(8A44 - 8A47h) */
	ULONG	sdcp2hw12;
	/**< 2840_(8A48 - 8A4Bh) */
	ULONG	sdcp2hw13;
	/**< 2840_(8A4C - 8A4Fh) */
	ULONG	sdcp2hw14;
	/**< 2840_(8A50 - 8A53h) */
	ULONG	sdcp2hw15;
	/**< 2840_(8A60 - 8A63h) */
	ULONG	sdcn2hw01;
	/**< 2840_(8A64 - 8A67h) */
	ULONG	sdcn2hw02;
	/**< 2840_(8A68 - 8A6Bh) */
	ULONG	sdcn2hw03;
	/**< 2840_(8A6C - 8A6Fh) */
	ULONG	sdcn2hw04;
	/**< 2840_(8A70 - 8A73h) */
	ULONG	sdcn2hw05;
	/**< 2840_(8A80 - 8A83h) */
	ULONG	sdcn2hw11;
	/**< 2840_(8A84 - 8A87h) */
	ULONG	sdcn2hw12;
	/**< 2840_(8A88 - 8A8Bh) */
	ULONG	sdcn2hw13;
	/**< 2840_(8A8C - 8A8Fh) */
	ULONG	sdcn2hw14;
	/**< 2840_(8A90 - 8A93h) */
	ULONG	sdcn2hw15;
	/**< 2840_(8AC0 - 8AC3h) */
	ULONG	sdcpc01;
	/**< 2840_(8AC4 - 8AC7h) */
	ULONG	sdcpc02;
	/**< 2840_(8AC8 - 8ACBh) */
	ULONG	sdcpc03;
	/**< 2840_(8ACC - 8ACFh) */
	ULONG	sdcpc04;
	/**< 2840_(8AD0 - 8AD3h) */
	ULONG	sdcpc05;
	/**< 2840_(8AD4 - 8AD7h) */
	ULONG	sdcpc06;
	/**< 2840_(8AD8 - 8ADBh) */
	ULONG	sdcpc07;
	/**< 2840_(8ADC - 8ADFh) */
	ULONG	sdcpc08;
	/**< 2840_(8AE0 - 8AE3h) */
	ULONG	sdcpc09;
	/**< 2840_(8AE4 - 8AE7h) */
	ULONG	sdcpc010;
	/**< 2840_(8AE8 - 8AEBh) */
	ULONG	sdcpc011;
	/**< 2840_(8AEC - 8AEFh) */
	ULONG	sdcpc012;
	/**< 2840_(8AF0 - 8AF3h) */
	ULONG	sdcpc013;
	/**< 2840_(8AF4 - 8AF7h) */
	ULONG	sdcpc014;
	/**< 2840_(8AF8 - 8AFBh) */
	ULONG	sdcpc015;
	/**< 2840_(8AFC - 8AFFh) */
	ULONG	sdcpc016;
	/**< 2840_(8B00 - 8B03h) */
	ULONG	sdcpc11;
	/**< 2840_(8B04 - 8B07h) */
	ULONG	sdcpc12;
	/**< 2840_(8B08 - 8B0Bh) */
	ULONG	sdcpc13;
	/**< 2840_(8B0C - 8B0Fh) */
	ULONG	sdcpc14;
	/**< 2840_(8B10 - 8B13h) */
	ULONG	sdcpc15;
	/**< 2840_(8B14 - 8B17h) */
	ULONG	sdcpc16;
	/**< 2840_(8B18 - 8B1Bh) */
	ULONG	sdcpc17;
	/**< 2840_(8B1C - 8B1Fh) */
	ULONG	sdcpc18;
	/**< 2840_(8B20 - 8B23h) */
	ULONG	sdcpc19;
	/**< 2840_(8B24 - 8B27h) */
	ULONG	sdcpc110;
	/**< 2840_(8B28 - 8B2Bh) */
	ULONG	sdcpc111;
	/**< 2840_(8B2C - 8B2Fh) */
	ULONG	sdcpc112;
	/**< 2840_(8B30 - 8B33h) */
	ULONG	sdcpc113;
	/**< 2840_(8B34 - 8B37h) */
	ULONG	sdcpc114;
	/**< 2840_(8B38 - 8B3Bh) */
	ULONG	sdcpc115;
	/**< 2840_(8B3C - 8B3Fh) */
	ULONG	sdcpc116;
	/**< 2840_(8B40 - 8B43h) */
	ULONG	sdcpcw0;
	/**< 2840_(8B44 - 8B47h) */
	ULONG	sdcpcw1;
	/**< 2840_(8B48 - 8B4Bh) */
	ULONG	sdcp1cw0;
	/**< 2840_(8B4C - 8B4Fh) */
	ULONG	sdcp1cw1;
	/**< 2840_(8B50 - 8B53h) */
	ULONG	sdcn1cw0;
	/**< 2840_(8B54 - 8B57h) */
	ULONG	sdcn1cw1;
	/**< 2840_(8B58 - 8B5Bh) */
	ULONG	sdcp2cw0;
	/**< 2840_(8B5C - 8B5Fh) */
	ULONG	sdcp2cw1;
	/**< 2840_(8B60 - 8B63h) */
	ULONG	sdcn2cw0;
	/**< 2840_(8B64 - 8B67h) */
	ULONG	sdcn2cw1;
	/**< 2840_(8B9C - 8B9Fh) */
	ULONG	sdcgmaxmin;
	/**< 2840_(8BA0 - 8BA3h) */
	ULONG	sdcnmax;
} TimproRdmaSdcAddr;

/** SDC Control information
*/
typedef struct {
	/**< Defect correction mode select. target registor	:@@SDCMD	*/
	EimproSdcMode					sdcMode;
	/**< Phase difference AF pixel pattern output setting. target registor	:@@SDCPTO	*/
	EimproSdcAfpbOutputPtn		afpbOutputPtn;
	/**< Defect correction monochrome mode select. target registor	:@@SDCMONO	*/
	EimproSdcMonochromeMode		monochromeMode;
	/**< Phase difference AF pixel pattern output enable. target registor	:@@SDCPDAFEN	*/
	EimproSdcAfpbEnable			afpbEnabled;
} TimproSdcCtrl;

/** SDC AFPB Control information
*/
typedef struct {
	/**< horizontal pattern0  of AF generation pattern in units of 1 pixel. value range
	 * 	:[0 - 0xFFFF_FFFF_FFFF_FFFF] target registor	:@@SDCPH0[0]~0[8] */
	ULLONG						hPattern0[9];
	/**< horizontal pattern1  of AF generation pattern in units of 1 pixel. value range
	 * 	:[0 - 0xFFFF_FFFF_FFFF_FFFF] target registor	:@@SDCPH1[0]~1[8] */
	ULLONG						hPattern1[9];
	/**< horizontal pattern0 valid width of the phase difference AF pixel information
	 * generation pattern in units of 1 pixel. value range
	 * 	:[0 - 64] target registor	:@@SDCPHW0[0]~0[8] */
	UCHAR						hPattern0ValidWidth[9];
	/**< horizontal pattern1 valid width of the phase difference AF pixel information
	 *  generation pattern in units of 1 pixel. value range
	 *  	:[0 - 64] target registor	:@@SDCPHW1[0]~1[8] */
	UCHAR						hPattern1ValidWidth[9];
	/**< horizontal pattern0 repetition1 valid width of the phase difference AF pixel
	 *  information generation pattern in units of 1 pixel. value range
	 *  		:[0 - 8191] target registor	:@@SDCP1HW0[0]~0[8] */
	USHORT						hPattern0R1ValidWidth[9];
	/**< horizontal pattern1 repetition1 valid width of the phase difference AF pixel
	 * information generation pattern in units of 1 pixel. value range
	 * :[0 - 8191] target registor	:@@SDCP1HW1[0]~1[8] */
	USHORT						hPattern1R1ValidWidth[9];
	/**< horizontal pattern0 repetition1 invalid width of the phase difference AF
	 * pixel information generation pattern in units of 1 pixel. value range
	 * 		:[0 - 8191] target registor	:@@SDCN1HW0[0]~0[8] */
	USHORT						hPattern0R1InvalidWidth[9];
	/**< horizontal pattern1 repetition1 invalid width of the phase difference AF
	 *  pixel information generation pattern in units of 1 pixel. value range
	 *  		:[0 - 8191] target registor	:@@SDCN1HW1[0]~1[8] */
	USHORT						hPattern1R1InvalidWidth[9];
	/**< horizontal pattern0 repetition2 valid width of the phase difference AF
	 * pixel information generation pattern in units of 1 pixel. value range
	 * 	:[0 - 8191] target registor	:@@SDCP2HW0[0]~0[8] */
	USHORT						hPattern0R2ValidWidth[9];
	/**< horizontal pattern1 repetition2 valid width of the phase difference AF
	 *  pixel information generation pattern in units of 1 pixel. value range
	 *  	:[0 - 8191] target registor	:@@SDCP2HW1[0]~1[8] */
	USHORT						hPattern1R2ValidWidth[9];
	/**< horizontal pattern0 repetition2 invalid width of the phase difference AF
	 *  pixel information generation pattern in units of 1 pixel. value range
	 *  		:[0 - 8191] target registor	:@@SDCP2HW0[0]~0[8] */
	USHORT						hPattern0R2InvalidWidth[9];
	/**< horizontal pattern1 repetition2 invalid width of the phase difference AF
	 * pixel information generation pattern in units of 1 pixel. value range
	 * 	:[0 - 8191] target registor	:@@SDCP2HW1[0]~1[8] */
	USHORT						hPattern1R2InvalidWidth[9];
	/**< column pattern0 of the horizontal pattern of the phase difference AF
	 * pixel information generation pattern. value range
	 * 	:[0 - 8] target registor	:@@SDCPC0[0]~0[63] */
	UCHAR						hColumnPattern0[64];
	/**< column pattern1 of the horizontal pattern of the phase difference AF
	 *  pixel information generation pattern. value range
	 *  	:[0 - 8] target registor	:@@SDCPC1[0]~1[63] */
	UCHAR						hColumnPattern1[64];
	/**< column pattern valid width0 of the horizontal pattern of the phase difference AF
	 *  pixel information generation pattern. value range
	 *  		:[0 - 64] target registor	:@@SDCPCW0 */
	UCHAR						hColumnPatternValidWidth0;
	/**< column pattern valid width1 of the horizontal pattern of the phase difference AF
	 * pixel information generation pattern. value range
	 * 	:[0 - 64] target registor	:@@SDCPCW1 */
	UCHAR						hColumnPatternValidWidth1;
	/**< column pattern1 valid width0 of the horizontal pattern of the phase difference AF
	 *  pixel information generation pattern in units of 1 column. value range
	 *  		:[0 - 8191] target registor	:@@SDCP1CW0 */
	USHORT						hColumnPattern1ValidWidth0;
	/**< column pattern1 valid width1 of the horizontal pattern of the phase difference AF
	 *  pixel information generation pattern in units of 1 column. value range
	 *  	:[0 - 8191] target registor	:@@SDCP1CW1 */
	USHORT						hColumnPattern1ValidWidth1;
	/**< column pattern1 invalid width0 of the horizontal pattern of the phase difference AF
	 *  pixel information generation pattern in units of 1 column. value range
	 *  		:[0 - 8191] target registor	:@@SDCN1CW0 */
	USHORT						hColumnPattern1InvalidWidth0;
	/**< column pattern1 invalid width1 of the horizontal pattern of the phase difference AF
	 *  pixel information generation pattern in units of 1 column.value range
	 *  	:[0 - 8191] target registor	:@@SDCN1CW1 */
	USHORT						hColumnPattern1InvalidWidth1;
	/**< column pattern2 valid width0 of the horizontal pattern of the phase difference AF
	 *  pixel information generation pattern in units of 1 column. value range
	 *  	:[0 - 8191] target registor	:@@SDCP2CW0 */
	USHORT						hColumnPattern2ValidWidth0;
	/**< column pattern2 valid width1 of the horizontal pattern of the phase difference AF
	 *  pixel information generation pattern in units of 1 column. value range
	 *  	:[0 - 8191] target registor	:@@SDCP2CW1 */
	USHORT						hColumnPattern2ValidWidth1;
	/**< column pattern2 invalid width0 of the horizontal pattern of the phase difference AF
	 *  pixel information generation pattern in units of 1 column. value range
	 *  	:[0 - 8191] target registor	:@@SDCN2CW0 */
	USHORT						hColumnPattern2InvalidWidth0;
	/**< column pattern2 invalid width1 of the horizontal pattern of the phase difference AF
	 *  pixel information generation pattern in units of 1 column. value range
	 *  	:[0 - 8191] target registor	:@@SDCN2CW1 */
	USHORT						hColumnPattern2InvalidWidth1;
	/**< judgment threshold (upper-limit) of the values used in the gain correction when
	 *  performing the surrounding pixel gain correction of the phase difference AF
	 *   pixel. value range		:[0 - 4095] target registor	:@@SDCGMAX */
	USHORT						afpbGainCorrectionUThreshold;
	/**< judgment threshold (lower-limit) of the values used in the gain correction when
	 *  performing the surrounding pixel gain correction of the phase difference AF
	 *   pixel. value range		:[0 - 4095] target registor	:@@SDCGMIN */
	USHORT						afpbGainCorrectionIThreshold;
	/**< When the number of the phase difference AF pixels of neighboring pixels on the
	 * top, bottom, left and right side is equal to or larger than (SDCNMAX+1),
	 * the static defective pixel correction is performed. value range
	 * 		:[0 - 3] target registor	:@@SDCNMAX */
	UCHAR						afpbNeighborPixelCorrectionLevel;
} TimproSdcCtrlAfpb;

/** SDC gain table information
*/
typedef struct {
	/**< Coefficients for gain correction. value range
	 * 	:[0 - 255(7.96875)] target registor	:@@SDC0GD1/2	*/
	USHORT	gainTable[ImproSrosdc_D_IM_PRO_SDC_GAIN_TBL_NUM];
} TimproSdcGainTable;

/** RDMA I/F SDC gain coefficient table register address information
*/
typedef struct {
	/**< gain coefficient table register address */
	ULONG	sdcgd;
} TimproRdmaSdcGainTblAddr;

/*类型定义区域*/
typedef struct _ImproSrosdc							ImproSrosdc;
typedef struct _ImproSrosdcPrivate				ImproSrosdcPrivate;


/*对象结构体区域*/
struct _ImproSrosdc
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_srosdc_get_type(void);
ImproSrosdc*			impro_srosdc_new();
extern	VOID			impro_srosdc_comm_get_sdc_reg_info( E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch,
									const T_IM_PRO_SRO_SDC_INFO** sdcInfo );
/**
Compensation mode start
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@retval		D_DDIM_OK					: Processing OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: PRCH not running NG
*/
extern	INT32			impro_srosdc_start( E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch );
/**
Compensation mode stop
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Processing OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: PRCH not stopped NG
*/
extern	INT32			impro_srosdc_stop( E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, UCHAR force );
/**
SDC control setup
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@param[in]	sdcCtrl : SDC control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srosdc_ctrl( E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, TimproSdcCtrl* sdcCtrl );
/**
Select SDC gain table.
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@param[in]	tblSel : SDC gain table select.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srosdc_select_gain_table( E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, EimproSdcGainTableSel tblSel );
/**
set SDC gain table.
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@param[in]	sdcAfpbCtrl : SDC AFPB control information.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srosdc_ctrl_afpb( E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, TimproSdcCtrlAfpb* sdcAfpbCtrl );
/**
set SDC gain table.
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@param[in]	tblSel : SDC gain table select.
@param[in]	gainTable : SDC gain table information.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srosdc_set_gain_table( E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, EimproSdcGainTableSel tblSel, TimproSdcGainTable* gainTable );
/**
A setup of enable access to the built-in RAM of SDC.
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_srosdc_set_paen( E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, UCHAR paenTrg );
/**
Get the top address of the address array of SDC control.
@param[in]		unitNo : Unit number.
@param[in]		ch : Channel No
@param[out]		addr					: Top address of the address array of SDC control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
extern	INT32			impro_srosdc_get_rdma_addr_sdc_cntl( E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, const TimproRdmaSdcAddr** addr );
/**
Get the top address of the address array of SDC gain table.
@param[in]		unitNo : Unit number.
@param[in]		ch : Channel No
@param[in]		tblSel : SDC gain table select.
@param[out]		addr					: Top address of the address array of SDC gain table.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
extern	INT32			impro_srosdc_get_rdma_addr_sdc_gain_tbl( E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, EimproSdcGainTableSel tblSel, const TimproRdmaSdcGainTblAddr** addr );



#endif /* __IMPRO_SROSDC_H__ */

