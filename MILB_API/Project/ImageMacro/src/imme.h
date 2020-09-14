/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :唐萍萍
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

#ifndef __IM_ME_H__
#define __IM_ME_H__

#include "driver_common.h"
#include <klib.h>

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define IM_TYPE_ME		(im_me_get_type())
#define IM_ME(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImMe))
#define IM_IS_ME(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_ME))

// Result.
#define	ImMe_D_IM_ME_INPUT_PARAM_ERROR	(D_IM_ME | D_DDIM_INPUT_PARAM_ERROR)	/**< Processing result code<br> Input parameter error			(0x50000001) */
#define	ImMe_D_IM_ME_MACRO_BUSY			(D_IM_ME | D_DDIM_MACRO_BUSY_NG)		/**< Processing result code<br> Macro busy 						(0x50000005) */
#define ImMe_D_IM_ME_SEM_NG				(D_IM_ME | D_DDIM_SEM_NG)				/**< Processing result code<br> Semaphore acquisition NG		(0x50000010) */
#define	ImMe_D_IM_ME_SEM_TIMEOUT_ERR		(D_IM_ME | D_DDIM_SEM_TIMEOUT)			/**< Processing result code<br> Semaphore acquisition Time Out	(0x50000011) */
#define	ImMe_D_IM_ME_TIMEOUT				(D_IM_ME | D_DDIM_TIMEOUT)				/**< Processing result code<br> Time Out 						(0x50000013) */
#define	ImMe_D_IM_ME_AXI_ERROR			(D_IM_ME | D_DDIM_AXI_ERROR)			/**< Processing result code<br> AXI BUS error					(0x5000001A) */
#define	ImMe_D_IM_ME_NG					(D_IM_ME | D_DDIM_SYSTEM_ERROR)			/**< Processing result code<br> Processing NG					(0x50000099) */
#define	ImMe_D_IM_ME_PROCESS_END			(D_IM_ME | 0x000000FF)					/**< Processing result code<br> Process End 					(0x500000FF) */

// AXI Result.
#define ImMe_D_IM_ME_AXI_NORMAL_END					(0)			/**< Normal end.													*/
#define ImMe_D_IM_ME_AXI_ERR_CH_W_PRE				(1)			/**< The AXI error occurred by the write channel (Previous).		*/
#define ImMe_D_IM_ME_AXI_ERR_CH_W_VEC				(2)			/**< The AXI error occurred by the write channel (Vector).			*/
#define ImMe_D_IM_ME_AXI_ERR_CH_R_CUR				(3)			/**< The AXI error occurred by the read channel  (Current).			*/
#define ImMe_D_IM_ME_AXI_ERR_CH_RW					(4)			/**< The AXI error occurred by the read channel and write channel.	*/

// OFF/ON.
#define ImMe_D_IM_ME_OFF								(0)			/**< OFF.												*/
#define ImMe_D_IM_ME_ON								(1)			/**< ON.												*/

// DISABLE/ENABLE.
#define ImMe_D_IM_ME_DISABLE							(0)			/**< DISABLE.											*/
#define ImMe_D_IM_ME_ENABLE							(1)			/**< ENABLE.											*/

// Vector cancel mode.
#define ImMe_D_IM_ME_VEC_CANCEL_MODE_OFF				(0)			/**< Cancel off. (Ribery. PME Interchangeable output)	*/
#define ImMe_D_IM_ME_VEC_CANCEL_MODE_CUR1			(1)			/**< Current image.	Pixel comparison.					*/
#define ImMe_D_IM_ME_VEC_CANCEL_MODE_CUR2			(2)			/**< Current image.	Average value comparison.			*/

// Vector height size.
#define ImMe_D_IM_ME_PRE_VEC_HSIZE_512				(512)		/**<  512 byte.											*/
#define ImMe_D_IM_ME_PRE_VEC_HSIZE_1024				(1024)		/**< 1024 byte.											*/

//Interrupt mode (MEINT).
#define ImMe_D_IM_ME_INTMODE_AFTER_CYCLE				(0)			/**< After a certain cycle, interrupt issuing preparation start.	*/
#define ImMe_D_IM_ME_INTMODE_LOGICAL_OR				(1)			/**< Logical OR output.												*/

// Current image margin size.
#define ImMe_D_IM_ME_CUR_MARGIN_0					(0)			/**< 0 pixel.											*/
#define ImMe_D_IM_ME_CUR_MARGIN_4					(4)			/**< 4 pixel.											*/
#define ImMe_D_IM_ME_CUR_MARGIN_8					(8)			/**< 8 pixel.											*/

// Request arbitration method selection.
#define ImMe_D_IM_ME_ABT_FIXED						(0)			/**< Fixed priority.									*/
#define ImMe_D_IM_ME_ABT_ROUND						(1)			/**< Round robin.										*/

// MB number max.
#define ImMe_D_IM_ME_MBNUM_H_MAX						(260)		/**< 260.												*/
#define ImMe_D_IM_ME_MBNUM_V_MAX						(192)		/**< 192.												*/

// Input image mode.
#define ImMe_D_IM_ME_INPUTMODE_INTERLACE				(0)			/**< Interlace.											*/
#define ImMe_D_IM_ME_INPUTMODE_PROGRESSIVE			(1)			/**< Progressive.										*/

// Reference image Top/Bottom.
#define ImMe_D_IM_ME_REFTXB_TOP						(0)			/**< Top field.											*/
#define ImMe_D_IM_ME_REFTXB_BOTTOM					(1)			/**< Bottom field.										*/

// The limit of the use of off-screen as a reference pixel.
#define ImMe_D_IM_ME_OUTLIMIT_NOLIMIT0				(0)			/**< No limit.											*/
#define ImMe_D_IM_ME_OUTLIMIT_NOLIMIT1				(1)			/**< No limit.											*/
#define ImMe_D_IM_ME_OUTLIMIT_BOTTOM					(2)			/**< Outside of bottom image is out of reference.		*/
#define ImMe_D_IM_ME_OUTLIMIT_TOP					(3)			/**< Outside of top image is out of reference.			*/

// PME processing target number of screens.
#define ImMe_D_IM_ME_BANKNUM_1						(1)			/**< 1 (Progressive P, Interlaced P).					*/
#define ImMe_D_IM_ME_BANKNUM_2						(2)			/**< 2 (Progressive B).									*/
#define ImMe_D_IM_ME_BANKNUM_3						(3)			/**< 3.													*/
#define ImMe_D_IM_ME_BANKNUM_4						(4)			/**< 4 (Interlaced B).									*/

// Search direction.
#define ImMe_D_IM_ME_M1ORG_DIR_FWD					(0)			/**< FWD side.											*/
#define ImMe_D_IM_ME_M1ORG_DIR_BWD					(1)			/**< BWD side.											*/

// Parity.
#define ImMe_D_IM_ME_M1ORG_PARI_TOP					(0)			/**< Top.												*/
#define ImMe_D_IM_ME_M1ORG_PARI_BOTTOM				(1)			/**< Bottom.											*/

// ME1 information read mode.
#define ImMe_D_IM_ME_M1ORG_READ_FIXED				(0)			/**< Fixed 0. 											*/
#define ImMe_D_IM_ME_M1ORG_READ_SDRAM				(1)			/**< Read from SDRAM.									*/

// SAD0/1 write mode.
#define ImMe_D_IM_ME_M1ORG_SAD_SAVE					(0)			/**< Save MB_SAD0/1.									*/
#define ImMe_D_IM_ME_M1ORG_SAD_WRITE					(1)			/**< Write SAD to MB_SAD0/1.							*/
#define ImMe_D_IM_ME_M1ORG_SAD_COPY					(2)			/**< Copy MB_SAD0/1.									*/
#define ImMe_D_IM_ME_M1ORG_SAD_MIN0					(3)			/**< Write MIN(MB_SAD0, SAD) to MB_SAD0/1.				*/
#define ImMe_D_IM_ME_M1ORG_SAD_MIN1					(4)			/**< Write MIN(MB_SAD1, SAD) to MB_SAD0/1.				*/

// Vector write mode.
#define ImMe_D_IM_ME_M1ORG_VECM_WRITE0				(0)			/**< Write MB_MV0, MB_MH0								*/
#define ImMe_D_IM_ME_M1ORG_VECM_WRITE1				(1)			/**< Write MB_MV1, MB_MH1								*/

// Vector selection.
#define ImMe_D_IM_ME_M1ORG_VECS_SAVE					(0)			/**< Save MB_MV2, MB_MH2.								*/
#define ImMe_D_IM_ME_M1ORG_VECS_COPY0				(2)			/**< Copy MB_MV0, MB_MH0 to MB_MV2, MB_MH2.				*/
#define ImMe_D_IM_ME_M1ORG_VECS_COPY1				(3)			/**< Copy MB_MV1, MB_MH1 to MB_MV2, MB_MH2.				*/

// Picture type.
#define ImMe_D_IM_ME_M1ORG_PICT_P					(0)			/**< P Pic.												*/
#define ImMe_D_IM_ME_M1ORG_PICT_B					(1)			/**< B Pic.												*/
#define ImMe_D_IM_ME_M1ORG_PICT_I					(2)			/**< I Pic.												*/

// M1 correct KY/X max.
#define ImMe_D_IM_ME_M1CRCT_KY_MAX					(4)			/**< KY max.											*/
#define ImMe_D_IM_ME_M1CRCT_KX_MAX					(3)			/**< KX max.											*/

// M1 split mode.
#define ImMe_D_IM_ME_SPLITMODE_NORMAL				(0)			/**< Normal.											*/
#define ImMe_D_IM_ME_SPLITMODE_HORIZONTAL			(1)			/**< Horizontal split.									*/
#define ImMe_D_IM_ME_SPLITMODE_VERTICAL				(2)			/**< Vertical split.									*/

// PME Core mode parameter.
#define ImMe_D_IM_ME_LINEINTV_0QMB					(0)			/**< 0QMB line interval.								*/
#define ImMe_D_IM_ME_LINEINTV_1QMB					(1)			/**< 1QMB line interval.								*/
#define ImMe_D_IM_ME_LINEINTV_2QMB					(2)			/**< 2QMB line interval.								*/
#define ImMe_D_IM_ME_LINEINTV_3QMB					(3)			/**< 3QMB line interval.								*/

// Vector search limitation max.
#define	ImMe_D_IM_ME_VEC_LIMITV_MAX					(12)		/**< Horizon max.										*/
#define	ImMe_D_IM_ME_VEC_LIMITH_MAX					(16)		/**< Vertical max.										*/

// Previous image width min/max.
#define	ImMe_D_IM_ME_PRE_WIDTH_MIN					(48)		/**< Min.												*/
#define	ImMe_D_IM_ME_PRE_WIDTH_MAX					(1024)		/**< Max.												*/

// Previous image height min/max.
#define	ImMe_D_IM_ME_PRE_HEIGHT_MIN					(32)		/**< Min.												*/
#define	ImMe_D_IM_ME_PRE_HEIGHT_MAX					(752)		/**< Max.												*/

// Prefetch image width min/max.
#define	ImMe_D_IM_ME_PREF_WIDTH_MIN					(192)		/**< Min.												*/
#define	ImMe_D_IM_ME_PREF_WIDTH_MAX					(4160)		/**< Max.												*/

// Prefetch image height min/max.
#define	ImMe_D_IM_ME_PREF_HEIGHT_MIN					(128)		/**< Min.												*/
#define	ImMe_D_IM_ME_PREF_HEIGHT_MAX					(3072)		/**< Max.												*/

// Search width min/max.
#define	ImMe_D_IM_ME_SRCH_WIDTH_MIN					(40)		/**< Min.												*/
#define	ImMe_D_IM_ME_SRCH_WIDTH_MAX					(128)		/**< Max.												*/

// Search height min/max.
#define	ImMe_D_IM_ME_SRCH_HEIGHT_MIN					(8)			/**< Min.												*/
#define	ImMe_D_IM_ME_SRCH_HEIGHT_MAX					(48)		/**< Max.												*/

// Previous image shift min/max.
#define	ImMe_D_IM_ME_PRE_SHIFT_MIN					(-64)		/**< Min.												*/
#define	ImMe_D_IM_ME_PRE_SHIFT_MAX					(63)		/**< Max.												*/

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/** PP number */
typedef enum {
	ImMe_E_IM_ME_PPNUM_PPA = 0,				/**< PPA						*/
	ImMe_E_IM_ME_PPNUM_PPB,					/**< PPB						*/
	ImMe_E_IM_ME_PPNUM_PPC,					/**< PPC						*/
	ImMe_E_IM_ME_PPNUM_MAX,					/**< Maximum value				*/
} ImMe_EImMePpnum;

/** BANK number */
typedef enum {
	ImMe_E_IM_ME_BANKNUM_0 = 0,				/**< BANK 0						*/
	ImMe_E_IM_ME_BANKNUM_1,					/**< BANK 1						*/
	ImMe_E_IM_ME_BANKNUM_2,					/**< BANK 2						*/
	ImMe_E_IM_ME_BANKNUM_3,					/**< BANK 3						*/
	ImMe_E_IM_ME_BANKNUM_MAX,				/**< Maximum value				*/
} ImMe_EImMeBanknum;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/** User callback function pointer(Frame complete) */
typedef VOID (*ImMeCallback)( ULONG interrupt_flag_mask );

/** APBBRG control parameter	*/
typedef struct {
	UCHAR					ppEnable[ ImMe_E_IM_ME_PPNUM_MAX ];
														/**< PP part A/B/C core enable.
															<ul>
																<li>@ref ImMe_D_IM_ME_DISABLE
																<li>@ref ImMe_D_IM_ME_ENABLE
															</ul>
														*/
	UCHAR					intMode;					/**< Interrupt mode (MEINT).
															<ul>
																<li>@ref ImMe_D_IM_ME_INTMODE_AFTER_CYCLE
																<li>@ref ImMe_D_IM_ME_INTMODE_LOGICAL_OR
															</ul>
														*/
	USHORT					interval;					/**< Interrupt output interval (10bit).		*/
} ImMeCtrlApbbrg;

/** M1 Original image mode parameter	*/
typedef struct {
	UCHAR					direction;					/**< Search direction.
															<ul>
																<li>@ref ImMe_D_IM_ME_M1ORG_DIR_FWD
																<li>@ref ImMe_D_IM_ME_M1ORG_DIR_BWD
															</ul>
														*/
	UCHAR					parity;						/**< Parity.
															<ul>
																<li>@ref ImMe_D_IM_ME_M1ORG_PARI_TOP
																<li>@ref ImMe_D_IM_ME_M1ORG_PARI_BOTTOM
															</ul>
														*/
	UCHAR					readMode;					/**< ME1 information read mode.
															<ul>
																<li>@ref ImMe_D_IM_ME_M1ORG_READ_FIXED
																<li>@ref ImMe_D_IM_ME_M1ORG_READ_SDRAM
															</ul>
														*/
	UCHAR					sad0Mode;					/**< SAD0 write mode.
															<ul>
																<li>@ref ImMe_D_IM_ME_M1ORG_SAD_SAVE
																<li>@ref ImMe_D_IM_ME_M1ORG_SAD_WRITE
																<li>@ref ImMe_D_IM_ME_M1ORG_SAD_COPY
																<li>@ref ImMe_D_IM_ME_M1ORG_SAD_MIN0
																<li>@ref ImMe_D_IM_ME_M1ORG_SAD_MIN1
															</ul>
														*/
	UCHAR					sad1Mode;					/**< SAD1 write mode.
															<ul>
																<li>@ref ImMe_D_IM_ME_M1ORG_SAD_SAVE
																<li>@ref ImMe_D_IM_ME_M1ORG_SAD_WRITE
																<li>@ref ImMe_D_IM_ME_M1ORG_SAD_COPY
																<li>@ref ImMe_D_IM_ME_M1ORG_SAD_MIN0
																<li>@ref ImMe_D_IM_ME_M1ORG_SAD_MIN1
															</ul>
														*/
	UCHAR					vecMode;					/**< Vector write mode.
															<ul>
																<li>@ref ImMe_D_IM_ME_M1ORG_VECM_WRITE0
																<li>@ref ImMe_D_IM_ME_M1ORG_VECM_WRITE1
															</ul>
														*/
	UCHAR					vecSelect;					/**< Vector selection.
															<ul>
																<li>@ref ImMe_D_IM_ME_M1ORG_VECS_SAVE
																<li>@ref ImMe_D_IM_ME_M1ORG_VECS_COPY0
																<li>@ref ImMe_D_IM_ME_M1ORG_VECS_COPY1
															</ul>
														*/
	UCHAR					picType;					/**< Picture type.
															<ul>
																<li>@ref ImMe_D_IM_ME_M1ORG_PICT_P
																<li>@ref ImMe_D_IM_ME_M1ORG_PICT_B
																<li>@ref ImMe_D_IM_ME_M1ORG_PICT_I
															</ul>
														*/
} ImMeCtrlPmeM1org;

/** M1 Correct parameter	*/
typedef struct {
	UCHAR					frontKy;					/**< Front ky for ME1(L0 direction). (3bit 0~4)				*/
	UCHAR					backKy;					/**< Back  ky for ME1(L1 direction). (3bit 0~4)				*/
	UCHAR					frontKx;					/**< Front kx for ME1(L0 direction). (2bit 0~3)				*/
	UCHAR					backKx;					/**< Back  kx for ME1(L1 direction). (2bit 0~3)				*/
	UCHAR					mode;						/**< mode[ 0 ]:CPU specified vector base.<br>
															 mode[ 1 ]:0 vector.<br>
															 mode[ 2 ]:Lower left MB vector base.<br>
															 mode[ 3 ]:Upper left MB vector base.<br>
														*/
	UCHAR					frontH;					/**< Correction base position. (Front, horizontal, 6bit, mode[ 0 ]=1 valid only)	*/
	UCHAR					frontV;					/**< Correction base position. (Front, vertical,   5bit, mode[ 0 ]=1 valid only)	*/
	UCHAR					backH;						/**< Correction base position. (Back,  horizontal, 6bit, mode[ 0 ]=1 valid only)	*/
	UCHAR					backV;						/**< Correction base position. (Back,  vertical,   5bit, mode[ 0 ]=1 valid only)	*/
} ImMeCtrlPmeM1crct;

/** M1 MC on/off parameter	*/
typedef struct {
	USHORT					pPic;						/**< MC on/off decision threshold for P pic. (13bit).<br>
															 1. Normal.<br>
															  - Accept.
															 2. SAD of fixed 0 vector.<br>
															  - Set 0x1FFE.
															 3. SAD is 0.<br>
															  - Set 0x1FFF.
														*/
	USHORT					bPic;						/**< MC on/off decision threshold for B pic. (13bit).
															 1. Normal.<br>
															  - Accept.
															 2. SAD of fixed 0 vector.<br>
															  - Set 0x1FFE.
															 3. SAD is 0.<br>
															  - Set 0x1FFF.
														*/
} ImMeCtrlPmeM1mc;


/** M1 Split parameter	*/
typedef struct {
	UCHAR					mode;						/**< Split mode.
															<ul>
																<li>@ref ImMe_D_IM_ME_SPLITMODE_NORMAL
																<li>@ref ImMe_D_IM_ME_SPLITMODE_HORIZONTAL
																<li>@ref ImMe_D_IM_ME_SPLITMODE_VERTICAL
															</ul>
														*/
	UCHAR					thH;						/**< Threshold for horizontal split. (8bit)	*/
	UCHAR					thV;						/**< Threshold fot vertical split. (8bit)	*/
} ImMeCtrlPmeM1splt;

/** M1 Sad parameter	*/
typedef struct {
	USHORT					upper;						/**< Upper value. (12bit)	*/
	USHORT					lower;						/**< Lower value. (12bit)	*/
} ImMeCtrlPmeM1sad;

/** M1 Adjust parameter	*/
typedef struct {
	USHORT					waitCycle;					/**< Wait cycle. (15bit)	*/
	UCHAR					waitOnoff;					/**< Wait on/off.
															<ul>
																<li>@ref ImMe_D_IM_ME_OFF
																<li>@ref ImMe_D_IM_ME_ON
															</ul>
														*/
} ImMeCtrlPmeM1adjust;

/** M1 Pause parameter	*/
typedef struct {
	UCHAR					pauseLine;					/**< Pause QMB line. (0~QMB line-1, 7bit)	*/
	UCHAR					pauseOnoff;				/**< Pause on/off.
															<ul>
																<li>@ref ImMe_D_IM_ME_OFF
																<li>@ref ImMe_D_IM_ME_ON
															</ul>
														*/
} ImMeCtrlPmeM1pause;

/** M1 Limit parameter	*/
typedef struct {
	UCHAR					vPlus;						/**< Vector search limitation parameter (Vertical   plus  side. 4bit. 0~12).	*/
	UCHAR					vMinus;					/**< Vector search limitation parameter (Vertical   minus side. 4bit. 0~12).	*/
	UCHAR					hPlus;						/**< Vector search limitation parameter (Horizontal plus  side. 5bit. 0~16).	*/
	UCHAR					hMinus;					/**< Vector search limitation parameter (Horizontal minus side. 5bit. 0~16).	*/
} ImMeCtrlPmeM1limit;

/** PME Core mode parameter		*/
typedef struct {
	UCHAR					lineInterval;				/**< QME line interval.
															<ul>
																<li>@ref ImMe_D_IM_ME_LINEINTV_0QMB
																<li>@ref ImMe_D_IM_ME_LINEINTV_1QMB
																<li>@ref ImMe_D_IM_ME_LINEINTV_2QMB
																<li>@ref ImMe_D_IM_ME_LINEINTV_3QMB
															</ul>
														*/
	UCHAR					initPosY;					/**< QMB initial y position. (2bit)	*/
} ImMeCtrlPmeCoremode;

/** PME control parameter		*/
typedef struct {
	UCHAR					inputMode;					/**< Input image mode.
															<ul>
																<li>@ref ImMe_D_IM_ME_INPUTMODE_INTERLACE
																<li>@ref ImMe_D_IM_ME_INPUTMODE_PROGRESSIVE
															</ul>
														*/
	UCHAR					refTxb;					/**< Reference image Top/Bottom (if inputMode is progressive, select ImMe_D_IM_ME_REFTXB_TOP).
															<ul>
																<li>@ref ImMe_D_IM_ME_REFTXB_TOP
																<li>@ref ImMe_D_IM_ME_REFTXB_BOTTOM
															</ul>
														*/
	UCHAR					outLimit;					/**< The limit of the use of off-screen as a reference pixel.
															<ul>
																<li>@ref ImMe_D_IM_ME_OUTLIMIT_NOLIMIT0
																<li>@ref ImMe_D_IM_ME_OUTLIMIT_NOLIMIT1
																<li>@ref ImMe_D_IM_ME_OUTLIMIT_BOTTOM
																<li>@ref ImMe_D_IM_ME_OUTLIMIT_TOP
															</ul>
														*/
	UCHAR					bankNum;					/**< PME processing target number of screens.
															<ul>
																<li>@ref ImMe_D_IM_ME_BANKNUM_1
																<li>@ref ImMe_D_IM_ME_BANKNUM_2
																<li>@ref ImMe_D_IM_ME_BANKNUM_3
																<li>@ref ImMe_D_IM_ME_BANKNUM_4
															</ul>
														*/
														/**< M1 Original image mode.				*/
	ImMeCtrlPmeM1org		m1orgMode[ ImMe_E_IM_ME_BANKNUM_MAX ];
	ImMeCtrlPmeM1crct		m1correct;				/**< M1 Correct parameter.					*/
	ImMeCtrlPmeM1mc		m1mc;					/**< M1 MC on/off parameter.				*/
	ImMeCtrlPmeM1splt		m1splt;					/**< M1 Split parameter.					*/
	UCHAR						m1skip;					/**< M1 Skip parameter.
															<ul>
																<li>@ref ImMe_D_IM_ME_OFF
																<li>@ref ImMe_D_IM_ME_ON
															</ul>
														*/
	ImMeCtrlPmeM1sad		m1sad;					/**< M1 Sad parameter.						*/
	ImMeCtrlPmeM1adjust	m1adjust;				/**< M1 Adjust parameter.					*/
	ImMeCtrlPmeM1pause	m1pause;				/**< M1 Pause parameter.					*/
	ImMeCtrlPmeM1limit	m1limit;				/**< M1 Limit parameterer.					*/
	ImMeCtrlPmeCoremode	coreMode;				/**< PME Core mode parameterer.				*/
} ImMeCtrlPme;

/** Bank table parameter	*/
typedef struct {
	UCHAR					fwdPvec;					/**< Physical bank number for foward vector data read/write access. (8bit)	*/
	UCHAR					top;						/**< Physical bank number for TopField of Interlace.  (8bit)				*/
	UCHAR					fwd8pel;					/**< Physical bank number for 1/8 reference image read access. (8bit)		*/
} ImMeCtrlRmcifBnktbl;

/** AXI interface			*/
typedef struct {
	UCHAR					rCacheType;				/**< Read cache type for AXI IF (4bit)									*/
	UCHAR					rProtectType;				/**< Read protect type for AXI IF (3bit)								*/
	UCHAR					wCacheType;				/**< Write cache type for AXI IF (4bit)									*/
	UCHAR					wProtectType;				/**< Write protect type for AXI IF (3bit)								*/
} ImMeCtrlRmcifAxiif;

/** RMCIF control parameter		*/
typedef struct {
	UCHAR						pmeNum;				/**< Number of PME use. (2bit. 0~2)<br>
															pmeNum = 0 : PME 1 use.<br>
															pmeNum = 1 : PME 2 use.<br>
															pmeNum = 2 : PME 3 use.<br>
														*/
	UCHAR						abtType;				/**< Request arbitration method selection.
															<ul>
																<li>@ref ImMe_D_IM_ME_ABT_FIXED
																<li>@ref ImMe_D_IM_ME_ABT_ROUND
															</ul>
														*/
	ImMeCtrlRmcifBnktbl	bankTbl;				/* Bank table parameter.					*/
	ImMeCtrlRmcifAxiif	axiIf;					/* AXI interface.							*/
} ImMeCtrlRmcif;

/** ME control parameter */
typedef struct {
	ImMeCtrlApbbrg		apbbrg;						/**< APBBRG control parameter.				*/
	ImMeCtrlPme		pme[ ImMe_E_IM_ME_PPNUM_MAX ];	/**< PME    control parameter.				*/
	ImMeCtrlRmcif		rmcif;						/**< RMCIF  control parameter.				*/
	ImMeCallback		pCallBack;					/**< User callback function. (Frame comp)	*/
} ImMeCtrl;

/** PME start parameter */
typedef struct {
	USHORT					mbnumH;					/**< MB number (Horizontal 9bit. Max:256)	*/
	USHORT					mbnumV;					/**< MB number (Vertical   8bit. Max:144)	*/
	UCHAR					cancelMode;				/**< Vector cancel mode.
															<ul>
																<li>@ref ImMe_D_IM_ME_VEC_CANCEL_MODE_OFF
																<li>@ref ImMe_D_IM_ME_VEC_CANCEL_MODE_CUR1
																<li>@ref ImMe_D_IM_ME_VEC_CANCEL_MODE_CUR2
															</ul>
														*/
	UCHAR					cancelThresholdHi;		/**< Vector cancel comparison threshold high. (8bit)	*/
	UCHAR					cancelThresholdLo;		/**< Vector cancel comparison threshold low.  (8bit)	*/
	USHORT					vecHsize;					/**< Vector output foramt horizontal size.<br>
															 - Reduction image horizontal size <= 1024 : set  512 byte.<br>
															 - Reduction image horizontal size  > 1024 : set 1024 byte.<br>
															<ul>
																<li>@ref ImMe_D_IM_ME_PRE_VEC_HSIZE_512
																<li>@ref ImMe_D_IM_ME_PRE_VEC_HSIZE_1024
															</ul>
														*/
} ImMeStartPme;

/** RMCIF start parameter */
typedef struct {
	CHAR					preShiftX;				/**< Previous image shift X. (7bit. -64~63)								*/
	CHAR					preShiftY;				/**< Previous image shift Y. (7bit. -64~63)								*/

	USHORT					preRAddrHi;				/**< Previous image base address high[31:16]. (16bit)					*/
	USHORT					preRAddrLo;				/**< Previous image base address low [15:12].
															(16bit. Previous image base address[31:12] is 16K byte align)		*/
	USHORT					curRAddrHi;				/**< Current image base address high[31:16]. (16bit)					*/
	USHORT					curRAddrLo;				/**< Current image base address low[15:12].
															(16bit. Current image base address[31:12] is 16K byte align)		*/
	USHORT					vecWAddrHi;				/**< Vector information base address high[31:16]. (16bit)				*/
	USHORT					vecWAddrLo;				/**< Vector information base address low[15:10].
															(16bit. Vector information base address[31:10] is 1K byte align)	*/
	USHORT					preGwidth;					/**< Previous image global width. (11bit. 128 byte align)				*/
	USHORT					preWidth;					/**< Previous image width.        (11bit. 48~1024 pixel. unit 4 pixel)	*/
	USHORT					preHeight;					/**< Previous image height.       (10bit. 32~ 752 pixel. unit 4 pixel)	*/
	USHORT					curGwidth;					/**< Current  image global width. (11bit. 128 byte align)				*/
	USHORT					curMarginWidth;			/**< Current  image margin size Left/Right.
															<ul>
																<li>@ref ImMe_D_IM_ME_CUR_MARGIN_0
																<li>@ref ImMe_D_IM_ME_CUR_MARGIN_4
																<li>@ref ImMe_D_IM_ME_CUR_MARGIN_8
															</ul>
														*/
	USHORT					curMarginHeight;			/**< Current  image margin size Top/Bottom.
															<ul>
																<li>@ref ImMe_D_IM_ME_CUR_MARGIN_0
																<li>@ref ImMe_D_IM_ME_CUR_MARGIN_4
																<li>@ref ImMe_D_IM_ME_CUR_MARGIN_8
															</ul>
														*/
	USHORT					prefetchWidth;				/**< Prefetch image width. (13bit. 192~4160 pixel)<br>
															ex. prefetchWidth = ( preWidth + ( curMarginWidth * 2 ) ) * 4
														*/
	USHORT					prefetchHeight;			/**< Prefetch image height. (12bit. 128~3072 pixel)<br>
															ex. prefetchHeight = ( preHeight + ( curMarginHeight * 2 ) ) * 4
														*/
	UCHAR					searchWidth;				/**< ME1 initialize search width. ( 8bit. 40~136 pixel)<br>
															ex1. curMarginWidth = 4 or 8 : searchWidth = 136<br>
															ex2. curMarginWidth = 0      : searchWidth = 136 - 8<br>
														*/
	UCHAR					searchHeight;				/**< ME1 initialize search height.( 6bit. 8~48 pixel)<br>
															ex1. pmeNum = 2 : searchHeight = 40<br>
															ex2. pmeNum = 1 : searchHeight = 32<br>
															ex3. pmeNum = 0 : searchHeight = 24<br>
														*/
} ImMeStartRmcif;

/** ME start parameter */
typedef struct {
	ImMeStartPme		pme[ ImMe_E_IM_ME_PPNUM_MAX ];	/**< PME   start parameter.		*/
	ImMeStartRmcif		rmcif;						/**< RMCIF start parameter.		*/
} ImMeStart;

typedef struct 				_ImMe ImMe;
typedef struct 				_ImMePrivate ImMePrivate;

struct _ImMe {
	KObject parent;
};

KConstType 		    im_me_get_type(void);
ImMe*		        im_me_new(void);

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// Nothing Special.

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
// Nothing Special.

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/**
ME initialize.<br>
@retval			D_DDIM_OK					Success.
*/
extern INT32 Im_ME_Init( VOID );

/**
The semaphore of ME is acquired.<br>
@param[in]		wait_time					Time-out period.<br>
@retval			D_DDIM_OK					Success.
@retval			ImMe_D_IM_ME_INPUT_PARAM_ERROR	Parameter error.
@retval			ImMe_D_IM_ME_SEM_NG				Semaphore acquisition NG.
@remarks		This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
				This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
extern INT32 Im_ME_Open( const INT32 wait_time );

/**
The semaphore of ME is returned.<br>
@retval			D_DDIM_OK					Success.
@retval			ImMe_D_IM_ME_SEM_NG				Semaphore acquisition NG.
@remarks		This API uses DDIM_User_Sig_Sem().
*/
extern INT32 Im_ME_Close( VOID );

/**
ME control parameters set.<br>
@param[in]		me_ctrl						ME control parameters. See @ref ImMeCtrl.<br>
@retval			D_DDIM_OK					Success.
@retval			ImMe_D_IM_ME_INPUT_PARAM_ERROR	Parameter error.
@remarks		This API uses DDIM_User_Dly_Tsk().
*/
extern INT32 Im_ME_Ctrl( const ImMeCtrl* const me_ctrl );

/**
ME start.<br>
@param[in]		me_start					ME start parameters. See @ref ImMeStart.<br>
@retval			D_DDIM_OK					Success.
@retval			ImMe_D_IM_ME_INPUT_PARAM_ERROR	Parameter error.
@remarks		This API uses DDIM_User_Dly_Tsk().
@remarks		This API uses DDIM_User_Clr_Flg().
*/
extern INT32 Im_ME_Start( const ImMeStart* const me_start );

/**
ME wait end.<br>
@param[out]		p_wait_factor				Pointer of factor parameter which release wait process.
@param[in]		wait_time					Wait time [msec]. The valid range is -1, 0, ... .
											If this parameter is set to -1, driver waits permanently unless system-call sets event-flag.
@retval			D_DDIM_OK					Success.
@retval			ImMe_D_IM_ME_INPUT_PARAM_ERROR	Parameter error.
@retval			ImMe_D_IM_ME_TIMEOUT				Time out.
@retval			ImMe_D_IM_ME_AXI_ERROR			AXI BUS error.
@retval			ImMe_D_IM_ME_NG					System NG.
@remarks		This API uses DDIM_User_Clr_Flg().
@remarks		This API uses DDIM_User_Twai_Flg().
*/
extern INT32 Im_ME_Wait_End( UINT32* const p_wait_factor, const INT32 wait_time );

/**
ME interupt handler.<br>
@retval			None.
@remarks		This API uses DDIM_User_Set_Flg().
*/
extern VOID Im_ME_Int_Handler( VOID );

/*@}*/	// end of im_me

#ifdef __cplusplus
}
#endif

#endif /* __IM_ME_H__ */

/**
@weakgroup im_me
@{
	@section im_me_code Sample code
	- @ref ME_Init
	- @ref ME_Start

	<hr>

	@section ME_Init			ME init
	@code
	Im_ME_Init();													// Release software-reset

	Dd_GIC_Ctrl( E_DD_GIC_INTID_ME_INT, 1, D_DD_GIC_PRI30, 1 );		// Enable interrupt
	@endcode
	<br>
	<br>
	@section ME_Start			ME start
	@code
	ImMeCtrl	me_ctrl;
	ImMeStart	me_start;
	UINT32			wait_factor;

	Im_ME_Open( 100 );

	Im_ME_Ctrl( &me_ctrl );

	Im_ME_Start( &me_start);

	Im_ME_Wait_End( &wait_factor, 1000 );

	Im_ME_Close();
	@endcode
	<br>
	<br>
@}*/ /* end of im_me_code */
