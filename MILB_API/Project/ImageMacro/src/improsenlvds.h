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


#ifndef __IMPRO_SENLVDS_H__
#define __IMPRO_SENLVDS_H__


#include <klib.h>
#include "improbase.h"
#include "improsentop.h"

#define IMPRO_TYPE_SENLVDS       	(impro_senlvds_get_type())
#define IMPRO_SENLVDS(obj)       		(K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSenlvds))
#define IMPRO_IS_SENLVDS(obj)    	(K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SENLVDS))


/*宏定义区域*/
/**< Minimum setting of LHSIZE		*/
#define	ImproSenlvds_D_IM_PRO_LVDS_LHSIZE_MIN				(4)
/**< Maximum setting of LVDSINTADR	*/
#define	ImproSenlvds_D_IM_PRO_LVDS_LVDSINTADR_MAX	(8960)


/*其他结构体或类型定义区域*/


/** Sensor Mode*/
typedef enum {
	/**< 8lane/12bit */
	ImproSenlvds_E_IM_PRO_LVDS_INPUT_SERIAL = 0,
	/**< 8lane/10bit */
	ImproSenlvds_E_IM_PRO_LVDS_INPUT_PARALLEL
} EimproLvdsInput;

/** Channel number of sensor output*/
typedef enum {
	/**< 1ch output sensor */
	ImproSenlvds_E_IM_PRO_LVDS_OUT_1CH = 0,
} EimproLvdsOutCh;

/** LVDS use lane number*/
typedef enum {
	/**< 1lane	*/
	ImproSenlvds_E_IM_PRO_LVDS_LANE_1 = 1,
	/**< 2lane	*/
	ImproSenlvds_E_IM_PRO_LVDS_LANE_2,
	/**< 3lane	*/
	ImproSenlvds_E_IM_PRO_LVDS_LANE_3,
	/**< 4lane	*/
	ImproSenlvds_E_IM_PRO_LVDS_LANE_4,
	/**< 5lane	*/
	ImproSenlvds_E_IM_PRO_LVDS_LANE_5,
	/**< 6lane	*/
	ImproSenlvds_E_IM_PRO_LVDS_LANE_6,
	/**< 7lane	*/
	ImproSenlvds_E_IM_PRO_LVDS_LANE_7,
	/**< 8lane	*/
	ImproSenlvds_E_IM_PRO_LVDS_LANE_8,
	/**< 10lane	*/
	ImproSenlvds_E_IM_PRO_LVDS_LANE_10 = 10,
	/**< 12lane	*/
	ImproSenlvds_E_IM_PRO_LVDS_LANE_12 = 12,
	/**< 14lane	*/
	ImproSenlvds_E_IM_PRO_LVDS_LANE_14 = 14,
	/**< 16lane	*/
	ImproSenlvds_E_IM_PRO_LVDS_LANE_16 = 16
} EimproLvdsLane;

/** LVDS output data bit width*/
typedef enum {
	/**< RAW 16bit	*/
	ImproSenlvds_E_IM_PRO_LVDS_BIT_WIDTH_RAW_16_BIT = 0,
	/**< RAW 14bit	*/
	ImproSenlvds_E_IM_PRO_LVDS_BIT_WIDTH_RAW_14_BIT,
	/**< RAW 12bit	*/
	ImproSenlvds_E_IM_PRO_LVDS_BIT_WIDTH_RAW_12_BIT,
	/**< RAW 10bit	*/
	ImproSenlvds_E_IM_PRO_LVDS_BIT_WIDTH_RAW_10_BIT
} EimproLvdsBitWidth;

/** LVDS Output data bit shift*/
typedef enum {
	/**< bit shift none		*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_NONE = 0,
	/**< 1bit right shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_1BIT_SHIFT_R,
	/**< 2bit right shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_2BIT_SHIFT_R,
	/**< 3bit right shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_3BIT_SHIFT_R,
	/**< 4bit right shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_4BIT_SHIFT_R,
	/**< 5bit right shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_5BIT_SHIFT_R,
	/**< 6bit right shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_6BIT_SHIFT_R,
	/**< 7bit right shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_7BIT_SHIFT_R,
	/**< 8bit left shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_8BIT_SHIFT_L,
	/**< 7bit left shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_7BIT_SHIFT_L,
	/**< 6bit left shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_6BIT_SHIFT_L,
	/**< 5bit left shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_5BIT_SHIFT_L,
	/**< 4bit left shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_4BIT_SHIFT_L,
	/**< 3bit left shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_3BIT_SHIFT_L,
	/**< 2bit left shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_2BIT_SHIFT_L,
	/**< 1bit left shift	*/
	ImproSenlvds_E_IM_PRO_LVDS_SFT_1BIT_SHIFT_L
} EimproLvdsSft;

/** LVDS synchronous code detection type*/
typedef enum {
	/**< Sync code type0(SAV/EAV/SAB/EAB)	*/
	ImproSenlvds_E_IM_PRO_LVDS_SYNC_TYPE_TYPE0 = 0,
	/**< Sync code type1(SOF/SOL/EOF/EOL)	*/
	ImproSenlvds_E_IM_PRO_LVDS_SYNC_TYPE_TYPE1
} EimproLvdsSyncType;

/** LVDS Input size type*/
typedef enum {
	/**< A synchronous code is followed.	*/
	ImproSenlvds_E_IM_PRO_LVDS_INPUT_TYPE_SYNC_CODE = 0,
	/**< LHSIZE/LHSADD is followed.	*/
	ImproSenlvds_E_IM_PRO_LVDS_INPUT_TYPE_HSZIE
} EimproLvdsInputType;

/** LVDS output data bit width*/
typedef enum {
	/**< same as LDW	*/
	ImproSenlvds_E_IM_PRO_LVDS_SYNC_BIT_SAME_LDW = 0,
	/**< 16bit fix		*/
	ImproSenlvds_E_IM_PRO_LVDS_SYNC_BIT_16BIT_FIX
} EimproLvdsSyncBit;

/** LVDS Division output*/
typedef enum {
	/**< 2-point division output		*/
	ImproSenlvds_E_IM_PRO_LVDS_DIV_OUT_2 = 1,
	/**< 4-point division output		*/
	ImproSenlvds_E_IM_PRO_LVDS_DIV_OUT_4,
	/**< 8-point division output		*/
	ImproSenlvds_E_IM_PRO_LVDS_DIV_OUT_8,
} EimproLvdsDivOut;

/** LVDS Inverted output Enable/Disable*/
typedef enum {
	/**< Disable	*/
	ImproSenlvds_E_IM_PRO_LVDS_INVERTED_DIS = 0,
	/**< Enable		*/
	ImproSenlvds_E_IM_PRO_LVDS_INVERTED_EN
} EimproLvdsInverted;

/** LVDS select serial clock*/
typedef enum {
	/**< clock stop	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_STOP = 0,
	/**< SNCLK0		*/
	ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_SNCLK0,
	/**< SNCLK1		*/
	ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_SNCLK1,
	/**< SNCLK2		*/
	ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_SNCLK2,
	/**< SNCLK3		*/
	ImproSenlvds_E_IM_PRO_LVDS_SNCLK_SEL_SNCLK3
} EimproLvdsSnclkSel;

/** LVDS select serial data*/
typedef enum {
	/**< SNDATA0	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA0 = 0,
	/**< SNDATA1	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA1,
	/**< SNDATA2	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA2,
	/**< SNDATA3	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA3,
	/**< SNDATA4	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA4,
	/**< SNDATA5	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA5,
	/**< SNDATA6	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA6,
	/**< SNDATA7	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA7,
	/**< SNDATA8	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA8,
	/**< SNDATA9	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA9,
	/**< SNDATA10	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA10,
	/**< SNDATA11	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA11,
	/**< SNDATA12	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA12,
	/**< SNDATA13	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA13,
	/**< SNDATA14	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA14,
	/**< SNDATA15	*/
	ImproSenlvds_E_IM_PRO_LVDS_SNDATA_SEL_SNDATA15
} EimproLvdsSndataSel;

/** LVDS sync code lane select*/
typedef enum {
	/**< Enable select side D0 of SPx	*/
	ImproSenlvds_E_IM_PRO_LVDS_SYNC_SEL_SPX_D0 = 0,
	/**< Enable select side D1 of SPx	*/
	ImproSenlvds_E_IM_PRO_LVDS_SYNC_SEL_SPX_D1
} EimproLvdsSyncSel;

/** LVDS sort output pixel selection*/
typedef enum {
	/**< pixel position 0	*/
	ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_0 = 0,
	/**< pixel position 1	*/
	ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_1,
	/**< pixel position 2	*/
	ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_2,
	/**< pixel position 3	*/
	ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_3,
	/**< pixel position 4	*/
	ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_4,
	/**< pixel position 5	*/
	ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_5,
	/**< pixel position 6	*/
	ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_6,
	/**< pixel position 7	*/
	ImproSenlvds_E_IM_PRO_LVDS_PIXEL_POS_7
} EimproLvdsPixelPos;
/** SENCORE maximum horizontal size of RAM*/



/** LVDS Control Information*/
typedef struct {
	/**< LVDS input modetarget registor	:@@LMD */
	EimproLvdsInput								transMode;
	/**< LVDS sensor number of output channel target registor	:@@LCH */
	EimproLvdsOutCh								outputChNo;
	/**< LVDS use lane number target registor	:@@LANE */
	EimproLvdsLane									lane;
	/**< LVDS output data bit width target registor	:@@LDW */
	EimproLvdsBitWidth							dataBitWidth;
	/**< LVDS Output data bit shift target registor	:@@LSFT */
	EimproLvdsSft									lsft;
	/**< LVDS synchronous code detection type target registor	:@@SYNT */
	EimproLvdsSyncType							syncType;
	/**< LVDS Input size type. target registor	:@@SZEN */
	EimproLvdsInputType						dataInputType;
	/**< LVDS Sync code bit 16bit fix target registor	:@@SYN16 */
	EimproLvdsSyncBit							syncBitFix;
	/**< LVDS divide output for use 1ch sensor target registor	:@@DIVOT */
	EimproLvdsDivOut								divideOutput;
	/**< LVDS Inverted output for use 1ch sensor target registor	:@@LMIR */
	EimproLvdsInverted							invertedOutput;
	/**< LVDS synchronous code detection mode. target registor	:@@DOLMD */
	E_IM_PRO_LVDS_OUTPUT_MODE		outputMode;
	/**< LVDS sync code mask setting value range		:[0x00 - 0xFFFF] target registor	:@@LMSK */
	USHORT												laneMask;
	/**< LVDS select serial clock for SP0 target registor	:@@LVDSCLKS */
	EimproLvdsSnclkSel							clockSelectSp0;
	/**< LVDS select serial clock for SP1 target registor	:@@LVDSCLKS */
	EimproLvdsSnclkSel							clockSelectSp1;
	/**< LVDS select serial clock for SP2 target registor	:@@LVDSCLKS */
	EimproLvdsSnclkSel							clockSelectSp2;
	/**< LVDS select serial clock for SP3 target registor	:@@LVDSCLKS */
	EimproLvdsSnclkSel							clockSelectSp3;
	/**< LVDS select serial clock for SP4 target registor	:@@LVDSCLKS */
	EimproLvdsSnclkSel							clockSelectSp4;
	/**< LVDS select serial clock for SP5 target registor	:@@LVDSCLKS */
	EimproLvdsSnclkSel							clockSelectSp5;
	/**< LVDS select serial clock for SP6 target registor	:@@LVDSCLKS */
	EimproLvdsSnclkSel							clockSelectSp6;
	/**< LVDS select serial clock for SP7 target registor	:@@LVDSCLKS */
	EimproLvdsSnclkSel							clockSelectSp7;
	/**< LVDS select serial data for SP0 data 0 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp00;
	/**< LVDS select serial data for SP0 data 1 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp01;
	/**< LVDS select serial data for SP1 data 0 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp10;
	/**< LVDS select serial data for SP1 data 1 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp11;
	/**< LVDS select serial data for SP2 data 0 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp20;
	/**< LVDS select serial data for SP2 data 1 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp21;
	/**< LVDS select serial data for SP3 data 0 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp30;
	/**< LVDS select serial data for SP3 data 1 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp31;
	/**< LVDS select serial data for SP4 data 0 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp40;
	/**< LVDS select serial data for SP4 data 1 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp41;
	/**< LVDS select serial data for SP5 data 0 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp50;
	/**< LVDS select serial data for SP5 data 1 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp51;
	/**< LVDS select serial data for SP6 data 0 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp60;
	/**< LVDS select serial data for SP6 data 1 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp61;
	/**< LVDS select serial data for SP7 data 0 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp70;
	/**< LVDS select serial data for SP7 data 1 target registor	:@@LVDSDATS */
	EimproLvdsSndataSel						clockSelectSp71;
	/**< LVDS sync code lane select target registor	:@@SYNCSEL */
	EimproLvdsSyncSel							laneSelect;
} TimproLvdsCtrl;

/** LVDS Lane select information */
typedef struct {
	/**< LVDS output line A value range		:See @ref EimproLvdsPixelPos target registor	:@@SELA */
	EimproLvdsPixelPos		ptnA:3;
	/**< LVDS output line bb value range		:See @ref EimproLvdsPixelPos target registor	:@@SELB */
	EimproLvdsPixelPos		ptnB:3;
	/**< LVDS output line C value range		:See @ref EimproLvdsPixelPos target registor	:@@SELC */
	EimproLvdsPixelPos		ptnC:3;
	/**< LVDS output line D value range		:See @ref EimproLvdsPixelPos target registor :@@SELD */
	EimproLvdsPixelPos		ptnD:3;
	/**< LVDS output line E value range			:See @ref EimproLvdsPixelPos target registor	:@@SELE */
	EimproLvdsPixelPos		ptnE:3;
	/**< Not used */
	USHORT							dummy01:1;
	/**< LVDS output line F value range			:See @ref EimproLvdsPixelPos target registor	:@@SELF */
	EimproLvdsPixelPos		ptnF:3;
	/**< LVDS output line G value range		:See @ref EimproLvdsPixelPos target registor	:@@SELG */
	EimproLvdsPixelPos		ptnG:3;
	/**< LVDS output line H value range		:See @ref EimproLvdsPixelPos target registor	:@@SELH */
	EimproLvdsPixelPos		ptnH:3;
	/**< LVDS output line I value range			:See @ref EimproLvdsPixelPos target registor	:@@SELI */
	EimproLvdsPixelPos		ptnI:3;
	/**< LVDS output line J value range			:See @ref EimproLvdsPixelPos target registor	:@@SELJ */
	EimproLvdsPixelPos		ptnJ:3;
	/**< Not used */
	USHORT							dummy02:1;
	/**< LVDS output line K value range		:See @ref EimproLvdsPixelPos target registor	:@@SELK */
	EimproLvdsPixelPos		ptnK:3;
	/**< LVDS output line L value range			:See @ref EimproLvdsPixelPos target registor	:@@SELL */
	EimproLvdsPixelPos		ptnP:3;
	/**< LVDS output line M value range		:See @ref EimproLvdsPixelPos target registor	:@@SELM */
	EimproLvdsPixelPos		ptnM:3;
	/**< LVDS output line N value range		:See @ref EimproLvdsPixelPos target registor	:@@SELN */
	EimproLvdsPixelPos		ptnN:3;
	/**< LVDS output line O value range		:See @ref EimproLvdsPixelPos target registor	:@@SELO */
	EimproLvdsPixelPos		ptnO:3;
	/**< Not used */
	USHORT							dummy03:1;
	/**< LVDS output line P value range		:See @ref EimproLvdsPixelPos target registor	:@@SELP */
	EimproLvdsPixelPos		ptnP:3;
	/**< Not used */
	USHORT							dummy04:13;
} TimproLvdsPixelOrder;

/** LVDS Sync Code Information */
typedef struct {
	/**< Effective pixel start(SAV) value range		:[0x0000 - 0xFFFF] target registor	:@@SAV_0 - @@SAV_3 */
	USHORT				sav[4];
	/**< Effective pixel end(EAV) value range		:[0x0000 - 0xFFFF] target registor	:@@EAV_0 - @@EAV_3 */
	USHORT				eav[4];
	/**< V blank start(SAB) value range		  			:[0x0000 - 0xFFFF] target registor	:@@SAB_0 - @@SAB_3 */
	USHORT				sab[4];
	/**< V blank end(EAB) value range					:[0x0000 - 0xFFFF] target registor	:@@EAB_0 - @@EAB_3 */
	USHORT				eab[4];
} TimproLvdsSyncCode;

/** LVDS Sync Code Control */
typedef struct {
	/**< the synchronous code of LVDS. LVDS can set up to 3 groups of synchronous code and
	 * can output the data with different synchronous codes as the data of different frames separately.	*/
	TimproLvdsSyncCode				syncCode[ E_IM_PRO_LVDS_OUTPUT_MODE_MAX ];
} TimproLvdsSyncCodeCtrl;

/** LVDS Sync Code Mask Information */
typedef struct {
	/**< SAV Mask bit<br> value range		:[0x0000 - 0xFFFF] target registor	:@@MSAV_0 - @@MSAV_3 */
	USHORT					msav[4];
	/**< EAV Mask bit value range				:[0x0000 - 0xFFFF] target registor	:@@MEAV_0 - @@MEAV_3 */
	USHORT					meav[4];
	/**< SAB Mask bit value range				:[0x0000 - 0xFFFF] target registor	:@@MSAB_0 - @@MSAB_3 */
	USHORT					msab[4];
	/**< EAB Mask bit value range				:[0x0000 - 0xFFFF] target registor	:@@MEAB_0 - @@MEAB_3 */
	USHORT					meab[4];
} TimproLvdsSyncMask;

/** LVDS Sync Code Mask Control */
typedef struct {
	/**< exclude the specific bit from comparison object in the synchronous code match detection processing.	*/
	TimproLvdsSyncMask	syncMask[ E_IM_PRO_LVDS_OUTPUT_MODE_MAX ];
} TimproLvdsSyncMaskCtrl;

/** SOL/EOL detection interrupt vertical address. */
typedef struct {
	/**< SOL detection interrupt vertical address.  value range:[0 - 8960]  target registor:@@SOLVADR */
	USHORT 						solAddr;
	/**< EOL detection interrupt vertical address.  value range:[0 - 8960]  target registor:@@EOLVADR */
	USHORT 						eolAddr;
} TimproLvdsIntAddr;

/** SOL/EOL detection interrupt vertical address Control */
typedef struct {
	/**< SOL/EOL detection interrupt vertical address.	*/
	TimproLvdsIntAddr			intAddr[ E_IM_PRO_LVDS_OUTPUT_MODE_MAX ];
} TimproLvdsIntAddrCtrl;

/*类型定义区域*/
typedef struct _ImproSenlvds							ImproSenlvds;
typedef struct _ImproSenlvdsPrivate				ImproSenlvdsPrivate;


/*对象结构体区域*/
struct _ImproSenlvds
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_senlvds_get_type(void);
ImproSenlvds*		impro_senlvds_new();
/**
LVDS macro start.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Macro Start OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: LVDS has not stopped NG
*/
extern	INT32			impro_senlvds_start( E_IM_PRO_LVDS_CH ch );
/**
LVDS macro stop.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Macro Stop OK
@retval		D_IM_PRO_NG					: Macro Stop NG
*/
extern	INT32			impro_senlvds_stop( E_IM_PRO_LVDS_CH ch );
/**
The control parameter of LVDS is set.
@param[in]	ch : Channel No.
@param[in]	lvdsCtrl : LVDS control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
extern	INT32			impro_senlvds_ctrl( E_IM_PRO_LVDS_CH ch, TimproLvdsCtrl* lvdsCtrl );
/**
LVDS Input starting position setup .
@param[in]	ch : Channel No.
@param[in]	input_pos	: LVDS input position<br>
						 value range:[0 - 12288pixel](Multiples of 4)<br>
						 target registor:@@LHSADD
@param[in]	inputSize : LVDS input size<br>
						 value range:[4 - ](Multiples of 4)<br>
						 maximum size that can be set by each SENCORE block set by SENTOP.SENRAMSW.<br>
						 target registor:@@LHSIZE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
@remarks	Only in the case of @@SZEN = 1 (see impro_senlvds_ctrl), the value set up by this API is effective.
*/
extern	INT32			impro_senlvds_set_area( E_IM_PRO_LVDS_CH ch, USHORT input_pos, USHORT inputSize );
/**
LVDS output data rearrangement setup.
@param[in]	ch : Channel No.
@param[in]	lvdsOrder : LVDS pixel order information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
extern	INT32			impro_senlvds_set_pixel_order( E_IM_PRO_LVDS_CH ch, TimproLvdsPixelOrder* lvdsOrder );
/**
The sync code parameter of LVDS is set.
@param[in]	ch : Channel No.
@param[in]	syncCode : LVDS sync code information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
@code
		//sample code
		TimproLvdsSyncCode		syncCode;

		syncCode.sav[0] = 0x0FFF;
		syncCode.sav[1] = 0x0000;
		syncCode.sav[2] = 0x0000;
		syncCode.sav[3] = 0x0800;

		syncCode.eav[0] = 0x0FFF;
		syncCode.eav[1] = 0x0000;
		syncCode.eav[2] = 0x0000;
		syncCode.eav[3] = 0x09D0;

		syncCode.sab[0] = 0x0FFF;
		syncCode.sab[1] = 0x0000;
		syncCode.sab[2] = 0x0000;
		syncCode.sab[3] = 0x0AB0;

		syncCode.eab[0] = 0x0FFF;
		syncCode.eab[1] = 0x0000;
		syncCode.eab[2] = 0x0000;
		syncCode.eab[3] = 0x0B60;

		impro_senlvds_set_sync_code( &syncCode );
@endcode
*/
extern	INT32			impro_senlvds_set_sync_code( E_IM_PRO_LVDS_CH ch, TimproLvdsSyncCodeCtrl* syncCode );
/**
LVDS sync code Mask setup.
@param[in]	ch : Channel No.
@param[in]	syncMask : LVDS sync mask information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
@code
		//sample code
		TimproLvdsSyncMask		syncCode;

		syncMask.msav[0] = 0x0001;
		syncMask.msav[1] = 0x0001;
		syncMask.msav[2] = 0x0001;
		syncMask.msav[3] = 0x0001;

		syncMask.meav[0] = 0x0001;
		syncMask.meav[1] = 0x0001;
		syncMask.meav[2] = 0x0001;
		syncMask.meav[3] = 0x0001;

		syncMask.msab[0] = 0x0001;
		syncMask.msab[1] = 0x0001;
		syncMask.msab[2] = 0x0001;
		syncMask.msab[3] = 0x0001;

		syncMask.meab[0] = 0x0001;
		syncMask.meab[1] = 0x0001;
		syncMask.meab[2] = 0x0001;
		syncMask.meab[3] = 0x0001;

		impro_senlvds_set_sync_mask( &syncMask );
@endcode
*/
extern	INT32			impro_senlvds_set_sync_mask( E_IM_PRO_LVDS_CH ch, TimproLvdsSyncMaskCtrl* syncMask );
/**
LVDS Input starting position setup .
@param[in]	ch : Channel No.
@param[in]	intAddr	: SOL/EOL interrupt address information.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_senlvds_set_int_adr( E_IM_PRO_LVDS_CH ch, TimproLvdsIntAddrCtrl* intAddr );
/**
A setup of enable access to the built-in RAM of LVDS.
@param[in]	ch : Channel No.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_senlvds_set_paen( E_IM_PRO_LVDS_CH ch, UCHAR paenTrg );


#endif /* __IMPRO_SENLVDS_H__ */

