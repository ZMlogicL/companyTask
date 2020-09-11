/*
 * imshdr.h
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :卢樊
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、interrupt setting process api
*2、
*@version:        1.0.0
*/

#ifndef __IM_SHDR_H__
#define __IM_SHDR_H__

#include <klib.h>
#include "driver_common.h"

#define IM_TYPE_SHDR      (im_shdr_get_type())
#define IM_SHDR(obj)        (K_TYPE_CHECK_INSTANCE_CAST(obj, ImShdr))
#define IM_IS_SHDR(obj)  (K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_SHDR))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//#define CO_SHDR_REG_TYPE_CHECK
//#define CO_SHDR_DEBUG_PRINT		// Debug.

// Data Synchronization Barrier.
#define im_shdr_dsb()						Dd_ARM_Dsb_Pou()

// Wait usec.
#define im_shdr_wait_usec( usec )			Dd_ARM_Wait_ns( ( usec * 1000 ) )

// The structure type matching check.
#ifdef CO_SHDR_REG_TYPE_CHECK
#define im_shdr_check_reg_type( dst, src )	( dst ) = ( src );
#else
#define im_shdr_check_reg_type( dst, src )
#endif

// Set signed register.
#define im_shdr_set_reg_signed( reg, type, member, val )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			im_shdr_check_reg_type( work, (reg) ); \
		}

// Set signed register (multi array).
#define im_shdr_set_reg_signed_a( reg, type, member, val )		\
		{ \
			type work = { .word[0] = 0xFFFFFFFFUL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			im_shdr_check_reg_type( work, (reg) ); \
		}

// Get signed register.
#define im_shdr_get_reg_signed( val, reg, type, member )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = -1L; \
			if( ((work.bit.member) == 0xFFFFFFFFUL) || ((reg.bit.member) <= ((work.bit.member) /2)) ) { \
				(val) = reg.bit.member; \
			} \
			else { \
				(val) = -(work.bit.member - reg.bit.member +1); \
			} \
			im_shdr_check_reg_type( (reg), work );	/* The structure type matching check. */ \
		}

// Get signed register (multi array).
#define im_shdr_get_reg_signed_a( val, reg, type, member )		\
		{ \
			type work = { .word[0] = 0UL }; \
			work.bit.member = -1L; \
			if( ((work.bit.member) == 0xFFFFFFFFUL) || ((reg.bit.member) <= ((work.bit.member) /2)) ) { \
				(val) = reg.bit.member; \
			} \
			else { \
				(val) = -(work.bit.member - reg.bit.member +1); \
			} \
			im_shdr_check_reg_type( (reg), work );	/* The structure type matching check. */ \
		}

#ifdef CO_PARAM_CHECK
#define im_shdr_check_wait_time( wait_time )	(( wait_time >= D_DDIM_USER_SEM_WAIT_FEVR ) ? TRUE : FALSE)
#endif	// CO_PARAM_CHECK

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_IMAGE_CLOCK)
#define	CO_ACT_SHDR_CLOCK
#endif

#if defined(CO_ACT_ICLOCK) || defined(CO_ACT_IMAGE_ICLOCK)
#define	CO_ACT_SHDR_ICLOCK
#endif

#if defined(CO_ACT_HCLOCK) || defined(CO_ACT_IMAGE_HCLOCK)
#define	CO_ACT_SHDR_HCLOCK
#endif

#if defined(CO_ACT_PCLOCK) || defined(CO_ACT_IMAGE_PCLOCK)
#define	CO_ACT_SHDR_PCLOCK
#endif

// Software reset.
#define	D_IM_SHDR_SR_RELEASE			(0)				// Software reset release.
#define	D_IM_SHDR_SR_RESET				(1)				// Software reset state.

// SRAM enable.
#define	D_IM_SHDR_SRAM_DISABLE			(0)				// SRAM disable.
#define	D_IM_SHDR_SRAM_ENABLE			(1)				// SRAM enable.

// Macro stat/stop trigger.
#define	D_IM_SHDR_TRG_STOP				(0)				// W:Stop.
#define	D_IM_SHDR_TRG_START				(1)				// W:Start.
#define	D_IM_SHDR_TRG_STATUS_STOP		(2)				// R:Stop status.
#define	D_IM_SHDR_TRG_STATUS_START		(3)				// R:Start status.

// SDHRINT1 register.
#define D_IM_SHDR_INTF_AXWEFLG			(0x0020)		// __AXWEFLG.
#define D_IM_SHDR_INTF_AXREFLG			(0x0010)		// __AXREFLG.
#define D_IM_SHDR_INTF_SHDRFLG			(0x0001)		// __SHDRFLG.

// Wait time.
#define D_IM_SHDR_SRAM_WAIT_USEC		(1)				// SRAM access wait time.
#define D_IM_SHDR_WAIT_END_TIME			(100)			// SHDR wait end time.

// Interrupt flag.
#define D_IM_SHDR_FLG_END				(0x00000001)	// End.
#define D_IM_SHDR_FLG_STOP				(0x00000002)	// Stop.



/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Result.
#define	D_IM_SHDR_INPUT_PARAM_ERROR			(D_IM_SHDR | D_DDIM_INPUT_PARAM_ERROR)	/**< Processing result code<br> Input parameter error			(0x0E000001) */
#define	D_IM_SHDR_MACRO_BUSY				(D_IM_SHDR | D_DDIM_MACRO_BUSY_NG)		/**< Processing result code<br> Macro busy 						(0x0E000005) */
#define D_IM_SHDR_SEM_NG					(D_IM_SHDR | D_DDIM_SEM_NG)				/**< Processing result code<br> Semaphore acquisition NG		(0x0E000010) */
#define	D_IM_SHDR_SEM_TIMEOUT_ERR			(D_IM_SHDR | D_DDIM_SEM_TIMEOUT)		/**< Processing result code<br> Semaphore acquisition Time Out	(0x0E000011) */
#define	D_IM_SHDR_TIMEOUT					(D_IM_SHDR | D_DDIM_TIMEOUT)			/**< Processing result code<br> Time Out 						(0x0E000013) */
#define	D_IM_SHDR_AXI_ERROR					(D_IM_SHDR | D_DDIM_AXI_ERROR)			/**< Processing result code<br> AXI BUS error					(0x0E00001A) */
#define	D_IM_SHDR_NG						(D_IM_SHDR | D_DDIM_SYSTEM_ERROR)		/**< Processing result code<br> Processing NG					(0x0E000099) */
#define	D_IM_SHDR_PROCESS_END				(D_IM_SHDR | 0x000000FF)				/**< Processing result code<br> Process End 					(0x0E0000FF) */

// AXI.
#define	D_IM_SHDR_AXI_READ_CH_DATA_MAX		(4)			/**< The maximum values of AXI read channel data.					*/
#define	D_IM_SHDR_AXI_WRITE_CH_DATA_MAX		(7)			/**< The maximum values of AXI write channel data.					*/

#define D_IM_SHDR_NORMAL_END				(0x00)		/**< Normal end.													*/
#define D_IM_SHDR_AXI_ERR_CH_W				(0x01)		/**< The AXI error occurred by the write channel.					*/
#define D_IM_SHDR_AXI_ERR_CH_R				(0x02)		/**< The AXI error occurred by the read channel.					*/
#define D_IM_SHDR_AXI_ERR_CH_RW				(0x03)		/**< The AXI error occurred by the read channel and write channel.	*/

// Degamma table.
#define D_IM_SHDR_TABLE_MAX_DEGAMMA_TABLE	(256)		/**< The maximum values of degamma table.	*/

// OFF/ON.
#define D_IM_SHDR_OFF						(0)			/**< OFF.									*/
#define D_IM_SHDR_ON						(1)			/**< ON.									*/

// DISABLE/ENABLE.
#define D_IM_SHDR_DISABLE					(0)			/**< DISABLE.								*/
#define D_IM_SHDR_ENABLE					(1)			/**< ENABLE.								*/

// Chroma up sampling mode.
#define D_IM_SHDR_CUS_YCC422_BILINEAR_A		(0)			/**< YCC422 bilinear mode A.				*/
#define D_IM_SHDR_CUS_YCC422_BILINEAR_B		(1)			/**< YCC422 bilinear mode B.				*/
#define D_IM_SHDR_CUS_YCC422_PADDING		(2)			/**< YCC422 padding mode.					*/
#define D_IM_SHDR_CUS_YCC420_BILINEAR_A		(3)			/**< YCC420 bilinear mode A.				*/
#define D_IM_SHDR_CUS_YCC420_BILINEAR_B		(4)			/**< YCC420 bilinear mode B.				*/
#define D_IM_SHDR_CUS_YCC420_PADDING		(5)			/**< YCC420 padding mode.					*/

// Chroma up sampling mode.
#define D_IM_SHDR_DEGAMMA_LUT				(0)			/**< Degamma(LUT).							*/
#define D_IM_SHDR_DEGAMMA_BITEXP			(1)			/**< Bit expansion.							*/

// Input image bit depth.
#define D_IM_SHDR_INBITDEPTH_8				(0)			/**< 8 bit.									*/
#define D_IM_SHDR_INBITDEPTH_16				(1)			/**< 16 bit.								*/

// Input CbCr image format.
#define D_IM_SHDR_INCFMT_420SP				(0)			/**< 420 semi-planar.						*/
#define D_IM_SHDR_INCFMT_422SP				(1)			/**< 422 semi-planar.						*/

// Output image control.
#define D_IM_SHDR_OUTCTRL_YCC				(0)			/**< YCC output path.						*/
#define D_IM_SHDR_OUTCTRL_RGB				(1)			/**< RGB output path.						*/

// Output image select.
#define D_IM_SHDR_OUTSEL_YCC_16				(0)			/**< YCC 16 bit image.						*/
#define D_IM_SHDR_OUTSEL_RGB_16				(1)			/**< RGB 16 bit image.						*/

// Filter margin.
#define D_IM_SHDR_FLITER_MARGIN_16			(16)		/**< 16.									*/
#define D_IM_SHDR_FLITER_MARGIN_32			(32)		/**< 32.									*/
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
#define D_IM_SHDR_FLITER_MARGIN_96			(96)		/**< 96.									*/
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// SMC input select.
#define D_IM_SHDR_SMCIN_STN_REF				(0)			/**< SMC input standard image  : Standard image<br>
															 SMC input reference image : Reference image<br>
														*/
#define D_IM_SHDR_SMCIN_EXT_STN				(1)			/**< SMC input standard image  : Extra image<br>
															 SMC input reference image : Standard image<br>
														*/
#define D_IM_SHDR_SMCIN_EXT_REF				(2)			/**< SMC input standard image  : Extra image<br>
															 SMC input reference image : Reference image<br>
														*/
// SHDR input select.
#define D_IM_SHDR_SHDRIN_STN_REF			(0)			/**< SHDR input standard image  : Standard image<br>
															 SHDR input reference image : Reference image<br>
														*/
#define D_IM_SHDR_SHDRIN_STN_SMCOUT			(1)			/**< SHDR input standard image  : Standard image<br>
															 SHDR input reference image : SMC output image<br>
														*/
#define D_IM_SHDR_SHDRIN_SMCOUT_REF			(2)			/**< SHDR input standard image  : SMC output image<br>
															 SHDR input reference image : Reference image<br>
														*/

// Tile size select.
#define D_IM_SHDR_TILESIZE_1024x1024		(0)			/**< Horizontal:1024 x Vertical:1024.		*/
#define D_IM_SHDR_TILESIZE_1024x512			(1)			/**< Horizontal:1024 x Vertical: 512.		*/

// Video format.
#define D_IM_SHDR_VFMT_RASTER				(0)			/**< Raster format.							*/
#define D_IM_SHDR_VFMT_VIDEO				(1)			/**< Video	format.							*/

// Video format(COMPIP WFID=A0/A1).
#define D_IM_SHDR_VFMT_COMPIP_VIDEO			(0)			/**< Video	format.							*/
#define D_IM_SHDR_VFMT_COMPIP_RASTER		(1)			/**< Raster format.							*/

// Weight base.
#define D_IM_SHDR_WGHTBASE_Y				(0)			/**< Y.										*/
#define D_IM_SHDR_WGHTBASE_RGB				(1)			/**< RGB.									*/

// Expansion process mode.
#define D_IM_SHDR_EXP77MD_COEFSUMDIV		(0)			/**< Coefficient sum division.				*/
#define D_IM_SHDR_EXP77MD_PERIMAXVAL		(1)			/**< Peripheral pixel maximum value.		*/

// FMD output image select.
#define D_IM_SHDR_FMDSEL_EXPANSION			(0)			/**< Expansion process image.				*/
#define D_IM_SHDR_FMDSEL_REDUCTION			(1)			/**< Reduction result merge image.			*/

// Pre mask mode.
#define D_IM_SHDR_PMSKMD_MAX				(0)			/**< Max value output.						*/
#define D_IM_SHDR_PMSKMD_AVE				(1)			/**< Average value output.					*/

// Mask merge mode.
#define D_IM_SHDR_MSKMD_SHORT				(0)			/**< Short exposure.						*/
#define D_IM_SHDR_MSKMD_LONG				(1)			/**< Long exposure.							*/
#define D_IM_SHDR_MSKMD_MSKONLY				(2)			/**< Motion mask only.						*/

// Blend select.
#define D_IM_SHDR_BLDSEL_SHORT_LONG			(0)			/**< Base   image : short exposure<br>
															 Target image : long  exposure<br>
														*/
#define D_IM_SHDR_BLDSEL_LONG_SHORT			(1)			/**< Base   image : long  exposure<br>
															 Target image : short exposure<br>
														*/

// Alpha value select.
#define D_IM_SHDR_ALPHASEL_DEVIATION		(0)			/**< Deviation + Margin condition.			*/
#define D_IM_SHDR_ALPHASEL_FIXED			(1)			/**< Fixed value (register setting).		*/
#define D_IM_SHDR_ALPHASEL_MERGEMASK		(2)			/**< Merge mask value.						*/

// EV compensation input data.
#define D_IM_SHDR_POSTSEL1_Y				(0)			/**< Y (BlendY12).							*/
#define D_IM_SHDR_POSTSEL1_RGB				(1)			/**< RGB max value (BlendRgbMax12).			*/

// EV compensation multiplication decimal point position.
#define D_IM_SHDR_POSTMULQPOS_Q5			(0)			/**< Q5.9  (Decimal part 9bit).				*/
#define D_IM_SHDR_POSTMULQPOS_Q4			(1)			/**< Q4.10 (Decimal part 10bit).			*/
#define D_IM_SHDR_POSTMULQPOS_Q3			(2)			/**< Q3.11 (Decimal part 11bit).			*/
#define D_IM_SHDR_POSTMULQPOS_Q2			(3)			/**< Q2.12 (Decimal part 12bit).			*/

// CSS input signal selection.
#define D_IM_SHDR_POSTSEL0_BLEND_YCC16		(0)			/**< BlendYcc16.							*/
#define D_IM_SHDR_POSTSEL0_BYPASS_YCC8		(1)			/**< BypassYcc8.							*/

// CSS sampling mode.
#define D_IM_SHDR_HDRCSSMD_YCC422_ODD		(0)			/**< YCC422 image output (odd sampling).	*/
#define D_IM_SHDR_HDRCSSMD_YCC422_CENTER	(1)			/**< YCC422 image output (center sampling).	*/

// Resize mode.
#define D_IM_RSZMD_ODD0						(0)			/**< Odd    -> Odd.							*/
#define D_IM_RSZMD_ODD1						(1)			/**< Odd    -> Center.						*/
#define D_IM_RSZMD_CENTER0					(2)			/**< Center -> Odd.							*/
#define D_IM_RSZMD_CENTER1					(3)			/**< Center -> Center.						*/

// Reduction mode 1.
#define D_IM_RDCMD1_1_4						(1)			/**< 1/4  reduction (output format : Y).		*/
#define D_IM_RDCMD1_1_8						(2)			/**< 1/8  reduction (output format : Y).		*/
#define D_IM_RDCMD1_1_32					(3)			/**< 1/32 reduction (output format : YCC422).	*/

// Reduction mode.
#define D_IM_RDCMD_1_2						(0)			/**< 1/2 reduction.							*/
#define D_IM_RDCMD_1_4						(1)			/**< 1/4 reduction.							*/
#define D_IM_RDCMD_1_8						(2)			/**< 1/8 reduction.							*/

// CSS mode.
#define D_IM_SHDR_CSSMD_YCC422				(0)			/**< YCC422.								*/
#define D_IM_SHDR_CSSMD_YCC420_ODD			(1)			/**< YCC420 odd.							*/
#define D_IM_SHDR_CSSMD_YCC420_CENTER		(2)			/**< YCC420 center.							*/

// Average MC mode.
#define D_IM_MCAMD_MAX						(0)			/**< Determining the maximum value of the error.									*/
#define D_IM_MCAMD_NR_EFFECT				(1)			/**< In the low confidence, output MC result of priority NR effect(Recommendation).	*/
#define D_IM_MCAMD_MAX_VECTOR				(2)			/**< Determining the maximum value of the error(overlapping vector).				*/
#define D_IM_MCAMD_MAX_MIN_VECTOR			(3)			/**< Determining the maximum - minimum value of the error(overlapping vector).		*/

// Low confidence MC mode.
#define D_IM_MCRMD_STANDARD					(0)			/**< The standard image output.				*/
#define D_IM_MCRMD_AVERAGE					(1)			/**< Average MC output(4 vector).			*/
#define D_IM_MCRMD_MC						(2)			/**< MC implementation.						*/

// Transfer burst length.
#define D_IM_SHDR_BURSTLEN_512				(0)			/**< 512byte.								*/
#define D_IM_SHDR_BURSTLEN_256				(1)			/**< 256byte.								*/

// Write with mask.
#define D_IM_SHDR_WWMASK_ON					(0)			/**< ON.									*/
#define D_IM_SHDR_WWMASK_OFF				(1)			/**< OFF.									*/

// Degamma table read selector.
#define D_IM_SHDR_DGTRSEL_PREFL				(2)			/**< PREF long exp 1/32 reduction image.			*/
#define D_IM_SHDR_DGTRSEL_PREFS				(3)			/**< PREF short exp 1/32 reduction image.			*/
#define D_IM_SHDR_DGTRSEL_PREMBL_EVEN		(4)			/**< PREMB long exp full size image (even pixel).	*/
#define D_IM_SHDR_DGTRSEL_PREMBL_ODD		(5)			/**< PREMB long exp full size image (odd pixel).	*/
#define D_IM_SHDR_DGTRSEL_PREMBS_EVEN		(6)			/**< PREMB short exp full size image (even pixel).	*/
#define D_IM_SHDR_DGTRSEL_PREMBS_ODD		(7)			/**< PREMB short exp full size image (odd pixel).	*/

// Compression/Decompression mode.
#define D_IM_SHDR_COMP_MODE_LOSSY			(0)			/**< Lossy mode.							*/
#define D_IM_SHDR_COMP_MODE_LOSSLESS		(1)			/**< Lossless mode.							*/

// MC mode.
#define D_IM_SHDR_COMP_MC_UNUSED			(0)			/**< MC mode unused.						*/
#define D_IM_SHDR_COMP_MC_USED				(1)			/**< MC mode used.							*/

// CbCr format at COMP side.
#define D_IM_SHDR_COMP_INCFMT_YUV420		(0)			/**< YUV420.								*/
#define D_IM_SHDR_COMP_INCFMT_YUV422		(1)			/**< YUV422.								*/

// Axi size unit.
#define D_IM_SHDR_COMP_AXI_512				(0)			/**< 512 byte.								*/
#define D_IM_SHDR_COMP_AXI_256				(1)			/**< 256 byte.								*/


/** SHDR AXI parameter (AXMD) */
typedef struct {
	UCHAR							r_burst;			/**< Transfer burst length (read ch)<br>
															<ul>
																<li>@ref D_IM_SHDR_BURSTLEN_512
																<li>@ref D_IM_SHDR_BURSTLEN_256
															</ul>
														*/
	UCHAR							w_burst;			/**< Transfer burst length (write ch)<br>
															<ul>
																<li>@ref D_IM_SHDR_BURSTLEN_512
																<li>@ref D_IM_SHDR_BURSTLEN_256
															</ul>
														*/
	UCHAR							w_w_mask;			/**< Write with mask<br>
															<ul>
																<li>@ref D_IM_SHDR_WWMASK_ON
																<li>@ref D_IM_SHDR_WWMASK_OFF
															</ul>
														*/
} T_IM_SHDR_AXI_AXMD;

/** SHDR AXI parameter (AXICTLAR) */
typedef struct {
	UCHAR							a_cahche[ 2 ];		/**< A:Cache type   (4bits).					*/
	UCHAR							a_protect[ 2 ];		/**< A:Protect type (3bits).					*/
	UCHAR							b_cahche[ 2 ];		/**< B:Cache type   (4bits).					*/
	UCHAR							b_protect[ 2 ];		/**< B:Protect type (3bits).					*/
	UCHAR							c_cahche[ 4 ];		/**< C:Cache type   (4bits).					*/
	UCHAR							c_protect[ 4 ];		/**< C:Protect type (3bits).					*/
	UCHAR							d_cahche[ 2 ];		/**< D:Cache type   (4bits).					*/
	UCHAR							d_protect[ 2 ];		/**< D:Protect type (3bits).					*/
} T_IM_SHDR_AXI_CTLR;

/** SHDR AXI parameter (AXICTLAW) */
typedef struct {
	UCHAR							a_cahche[ 4 ];		/**< A:Cache type   (4bits).					*/
	UCHAR							a_protect[ 4 ];		/**< A:Protect type (3bits).					*/
	UCHAR							b_cahche[ 6 ];		/**< B:Cache type   (4bits).					*/
	UCHAR							b_protect[ 6 ];		/**< B:Protect type (3bits).					*/
	UCHAR							c_cahche[ 7 ];		/**< C:Cache type   (4bits).					*/
	UCHAR							c_protect[ 7 ];		/**< C:Protect type (3bits).					*/
} T_IM_SHDR_AXI_CTLW;


typedef struct {
	T_IM_SHDR_AXI_AXMD				ax_mode;			/**< AXMD    :AXI transfer mode.				*/
	T_IM_SHDR_AXI_CTLR				r_ctl;				/**< AXICTLAR:AXI read control.					*/
	T_IM_SHDR_AXI_CTLW				w_ctl;				/**< AXICTLAW:AXI write control.				*/
} T_IM_SHDR_AXI;

/** AXI response */
typedef struct {
	UCHAR							r_resp_a[ D_IM_SHDR_AXI_READ_CH_DATA_MAX ];		/**< RRESPA:Read channel response.	*/
	UCHAR							r_resp_b[ D_IM_SHDR_AXI_READ_CH_DATA_MAX ];		/**< RRESPB:Read channel response.	*/
	UCHAR							r_resp_c[ D_IM_SHDR_AXI_READ_CH_DATA_MAX ];		/**< RRESPC:Read channel response.	*/
	UCHAR							r_resp_d[ D_IM_SHDR_AXI_READ_CH_DATA_MAX ];		/**< RRESPD:Read channel response.	*/
	UCHAR							w_resp_a[ D_IM_SHDR_AXI_WRITE_CH_DATA_MAX ];	/**< BRESPA:Write channel response.	*/
	UCHAR							w_resp_b[ D_IM_SHDR_AXI_WRITE_CH_DATA_MAX ];	/**< BRESPB:Write channel response.	*/
	UCHAR							w_resp_c[ D_IM_SHDR_AXI_WRITE_CH_DATA_MAX ];	/**< BRESPC:Write channel response.	*/
} T_IM_SHDR_AXI_RESP;

typedef struct _ImShdr  ImShdr;
typedef struct _ImShdrPrivate ImShdrPrivate;

struct _ImShdr {
KObject parent;
};

KConstType  im_shdr_get_type(void);
ImShdr* im_shdr_new(void);

VOID im_shdr_off_clk( VOID );
VOID im_shdr_off_xclk( VOID );
VOID im_shdr_on_pclk( VOID );
VOID im_shdr_off_pclk( VOID );
INT32 Im_SHDR_Init( BOOL force_flg );
INT32 Im_SHDR_Open( const INT32 wait_time );
INT32 Im_SHDR_Close( VOID );
INT32 Im_SHDR_Set_Degamma_R( const USHORT* const src_tbl, const USHORT write_ofs_num, const USHORT array_num );
INT32 Im_SHDR_Set_Degamma_G( const USHORT* const src_tbl, const USHORT write_ofs_num, const USHORT array_num );
INT32 Im_SHDR_Set_Degamma_B( const USHORT* const src_tbl, const USHORT write_ofs_num, const USHORT array_num );
INT32 Im_SHDR_Set_Degamma( const USHORT* const src_tbl_r, const USHORT* const src_tbl_g, const USHORT* const src_tbl_b, const USHORT write_ofs_num, const USHORT array_num );
INT32 Im_SHDR_Get_Degamma_R( USHORT* const dst_tbl, const USHORT read_ofs_num, const USHORT array_num, const UCHAR read_sel );
INT32 Im_SHDR_Get_Degamma_G( USHORT* const dst_tbl, const USHORT read_ofs_num, const USHORT array_num, const UCHAR read_sel );
INT32 Im_SHDR_Get_Degamma_B( USHORT* const dst_tbl, const USHORT read_ofs_num, const USHORT array_num, const UCHAR read_sel );
INT32 Im_SHDR_Get_Degamma( USHORT* const dst_tbl_r, USHORT* const dst_tbl_g, USHORT* const dst_tbl_b, const USHORT read_ofs_num, const USHORT array_num, const UCHAR read_sel );
INT32 Im_SHDR_Set_Axi( const T_IM_SHDR_AXI* const shdr_axi );
INT32 Im_SHDR_Get_Axi( T_IM_SHDR_AXI* const shdr_axi );
INT32 Im_SHDR_Get_Axi_Response( T_IM_SHDR_AXI_RESP* const axi_resp );
INT32 Im_SHDR_Start( VOID );
INT32 Im_SHDR_Stop( VOID );


#endif /* __IM_SHDR_H__ */
