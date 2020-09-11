/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :
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

#ifndef __IM_IIP_DEFINE_H__
#define __IM_IIP_DEFINE_H__

#include "driver_common.h"

#include "ddim_typedef.h"
#include <klib.h>
#include"imiipstruct.h"

#define CO_IM_IIP_ENABLE_UTILITY	/**< If this definition is valid, Im_IIP_Util_xxx functions are valid. */

#define IM_TYPE_IIP_DEFINE		(im_iip_define_get_type())
#define IM_IIP_DEFINE(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImIipDefine))
#define IM_IS_IIP_DEFINE(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IIP_DEFINE))

#ifdef CO_DEBUG_PRINT_XX_YYY
#define CO_DEBUG_PRINT_IM_IIP	/**< DEBUG */
#endif

#define	D_IM_IIP_OK									(D_DDIM_OK)								/**< Normal end                      (0) */
#define	D_IM_IIP_INVALID_ARG_ERR					(D_IM_IIP | D_DDIM_INPUT_PARAM_ERROR)	/**< Invalid argument error (0x0C000001) */
#define	D_IM_IIP_TIMEOUT_ERR						(D_IM_IIP | D_DDIM_TIMEOUT)				/**< Wait timeout error     (0x0C000013) */
#define	D_IM_IIP_SYSTEMCALL_ERR						(D_IM_IIP | D_DDIM_SYSTEM_ERROR)		/**< System call error      (0x0C000099) */
#define	D_IM_IIP_ERR								(D_IM_IIP | 0x100)						/**< Other error            (0x0C000100) */
#define	D_IM_IIP_ABORT_FAILED_ERR					(D_IM_IIP | 0x101)						/**< Abort failed error     (0x0C000101) */

/** @} */	// name

#define	D_IM_IIP_RUNNING			(3)
#define D_IM_IIP_PIXID_MAXNUM						(12)	/**< PIXID number */

#define D_IM_IIP_ENABLE_OFF							(0)		/**< The function is disable */
#define D_IM_IIP_ENABLE_ON							(1)		/**< The function is enable */

#define D_IM_IIP_STOP								(0)		/**< Stop IIP */
#define D_IM_IIP_ABORT								(1)		/**< Abort IIP */

// PLDUNIT BitMask
#define D_IM_IIP_PARAM_PLDUNIT_NONE			(0ULL)			/**< None			*/
#define D_IM_IIP_PARAM_PLDUNIT_LD0			(1ULL << 0)		/**< Loader 0		*/
#define D_IM_IIP_PARAM_PLDUNIT_LD1			(1ULL << 1)		/**< Loader 1		*/
#define D_IM_IIP_PARAM_PLDUNIT_LD2			(1ULL << 2)		/**< Loader 2		*/
#define D_IM_IIP_PARAM_PLDUNIT_LD3			(1ULL << 3)		/**< Loader 3		*/
#define D_IM_IIP_PARAM_PLDUNIT_FLT			(1ULL << 4)		/**< FLT			*/
#define D_IM_IIP_PARAM_PLDUNIT_AFN0			(1ULL << 5)		/**< AFN 0			*/
#define D_IM_IIP_PARAM_PLDUNIT_AFN1			(1ULL << 6)		/**< AFN 1			*/
#define D_IM_IIP_PARAM_PLDUNIT_AFN2			(1ULL << 7)		/**< AFN 2			*/
#define D_IM_IIP_PARAM_PLDUNIT_FRECT0		(1ULL << 8)		/**< FRECT 0		*/
#define D_IM_IIP_PARAM_PLDUNIT_MON			(1ULL << 9)		/**< Monitor		*/
#define D_IM_IIP_PARAM_PLDUNIT_SL0			(1ULL << 10)	/**< Store 0		*/
#define D_IM_IIP_PARAM_PLDUNIT_SL1			(1ULL << 11)	/**< Store 1		*/
#define D_IM_IIP_PARAM_PLDUNIT_SL2			(1ULL << 12)	/**< Store 2		*/
#define D_IM_IIP_PARAM_PLDUNIT_SL3			(1ULL << 13)	/**< Store 3		*/
#define D_IM_IIP_PARAM_PLDUNIT_SL4			(1ULL << 14)	/**< Store 4		*/
#define D_IM_IIP_PARAM_PLDUNIT_SL5			(1ULL << 15)	/**< Store 5		*/
#define D_IM_IIP_PARAM_PLDUNIT_CSC0			(1ULL << 16)	/**< CSC 0			*/
#define D_IM_IIP_PARAM_PLDUNIT_CSC1			(1ULL << 17)	/**< CSC 1			*/
#define D_IM_IIP_PARAM_PLDUNIT_LUT			(1ULL << 18)	/**< LUT			*/
#define D_IM_IIP_PARAM_PLDUNIT_GPC			(1ULL << 19)	/**< GPC			*/
#define D_IM_IIP_PARAM_PLDUNIT_BLEND0		(1ULL << 20)	/**< Blend 0		*/
#define D_IM_IIP_PARAM_PLDUNIT_BLEND1		(1ULL << 21)	/**< Blend 1		*/
#define D_IM_IIP_PARAM_PLDUNIT_FRECT1		(1ULL << 22)	/**< FRECT 1		*/
#define D_IM_IIP_PARAM_PLDUNIT_CFL0			(1ULL << 23)	/**< Cache Flow 0	*/
#define D_IM_IIP_PARAM_PLDUNIT_CSC2			(1ULL << 27)	/**< CSC 2			*/
#define D_IM_IIP_PARAM_PLDUNIT_CSC3			(1ULL << 28)	/**< CSC 3			*/
#define D_IM_IIP_PARAM_PLDUNIT_SL6			(1ULL << 29)	/**< Store 6		*/
#define D_IM_IIP_PARAM_PLDUNIT_SL7			(1ULL << 30)	/**< Store 7		*/
#define D_IM_IIP_PARAM_PLDUNIT_SL8			(1ULL << 31)	/**< Store 8		*/
#define D_IM_IIP_PARAM_PLDUNIT_LD4			(1ULL << 32)	/**< Loader 4		*/
#define D_IM_IIP_PARAM_PLDUNIT_LD5			(1ULL << 33)	/**< Loader 5		*/
#define D_IM_IIP_PARAM_PLDUNIT_LD6			(1ULL << 34)	/**< Loader 6		*/
#define D_IM_IIP_PARAM_PLDUNIT_LD7			(1ULL << 35)	/**< Loader 7		*/
#define D_IM_IIP_PARAM_PLDUNIT_AFN3			(1ULL << 36)	/**< AFN 3			*/
#define D_IM_IIP_PARAM_PLDUNIT_MFT			(1ULL << 37)	/**< MFT			*/

// UNITINFTBL.SWTRG
#define D_IM_IIP_SWTRG_OFF							(0)		/**< Don't care unit	*/
#define D_IM_IIP_SWTRG_ON							(1)		/**< Start unit */

// UNITINFTBL.HWEN
#define	D_IM_IIP_HW_CTRL_SWTRG						(0)		/**< SWTRG control	 */
#define	D_IM_IIP_HW_CTRL_AUTO						(1)		/**< HW auto control */

// UNITINFTBL.CHAIN
#define	D_IM_IIP_PLDUNIT_CHAIN_DISABLE				(0)		/**< PLDUNIT do not chain operation */
#define	D_IM_IIP_PLDUNIT_CHAIN_ENABLE				(1)		/**< PLDUNIT do chain operation */

// PIXFMTTBL.PDEPTH
#define	D_IM_IIP_PDEPTH_8BITS						(0)		/**< 8bits			*/
#define	D_IM_IIP_PDEPTH_12BITS						(1)		/**< 12bits-packed	*/
#define	D_IM_IIP_PDEPTH_16BITS						(2)		/**< 16bits(14bits)	*/

// PIXFMTTBL.CHKYORDR
#define	D_IM_IIP_CHUNKY_COLOR_Y0_G					(0)		/**< YO(G)	   */
#define	D_IM_IIP_CHUNKY_COLOR_CB_B					(1)		/**< Cb(B)	   */
#define	D_IM_IIP_CHUNKY_COLOR_CR_R					(2)		/**< Cr(R)	   */
#define	D_IM_IIP_CHUNKY_COLOR_Y1_A					(3)		/**< Y1(Alpha) */

// PIXFMTTBL.SGYG, SGB, SGR, SGA
#define	D_IM_IIP_UNSIGNED_DATA						(0)		/**< Unsigned data */
#define	D_IM_IIP_SIGNED_DATA						(1)		/**< Signed data   */

// PIXFMTTBL.ALPHA
#define	D_IM_IIP_ALPHA_FALSE						(0)		/**< Image without alpha */
#define	D_IM_IIP_ALPHA_TRUE							(1)		/**< Image with alpha	 */

// PIXFMTTBL.ASUBSPL
#define	D_IM_IIP_ALPHA_NO_SUBSAMP					(0)		/**< No subsampling							*/
#define	D_IM_IIP_ALPHA_H_SUBSAMP					(1)		/**< Horizontal subsampling					*/
#define	D_IM_IIP_ALPHA_HV_SUBSAMP					(2)		/**< Horizontal and Vertical subsampling	*/

// PIXFMTTBL.MTIFYG, MTIFB, MTIFR, MTIFA (for SL2/SL5 only)
#define	D_IM_IIP_MASTER_IF0							(1)		/**< Master I/F 0 */
#define	D_IM_IIP_MASTER_IF1							(0)		/**< Master I/F 1 */
#define	D_IM_IIP_MASTER_IF2							(0)		/**< Master I/F 2 */

// PIXFMTTBL.OARBHV
#define	D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE			(0)		/**< Fixed value */
#define	D_IM_IIP_OUTSIDE_IMG_EDGE					(1)		/**< Image edge value (value of pixels on top, bottom, left and right lines) */

#if 0	// B2Y Link not support
// IZACTL1.LKEN
#define	D_IM_IIP_LINK_B2Y_OFF						(0)		/**< Disable linkage between B2Y to IIP.	*/
#define	D_IM_IIP_LINK_B2Y_ON						(1)		/**< Enable linkage between B2Y to IIP.	*/
#endif	// B2Y Link not support

#define	D_IM_IIP_INT_FACTOR_IZAEND					(1<<0)	/**< IZAFLG interrupt factor ID (0x0000001) */
#define	D_IM_IIP_INT_FACTOR_AXIERR					(1<<1)	/**< AXEFLG interrupt factor ID (0x0000002) */
#define	D_IM_IIP_INT_FACTOR_SL0END					(1<<2)	/**< SL0FF interrupt factor ID  (0x0000004) */
#define	D_IM_IIP_INT_FACTOR_SL1END					(1<<3)	/**< SL1FF interrupt factor ID  (0x0000008) */
#define	D_IM_IIP_INT_FACTOR_SL2END					(1<<4)	/**< SL2FF interrupt factor ID  (0x0000010) */
#define	D_IM_IIP_INT_FACTOR_SL3END					(1<<5)	/**< SL3FF interrupt factor ID  (0x0000020) */
#define	D_IM_IIP_INT_FACTOR_SL4END					(1<<6)	/**< SL4FF interrupt factor ID  (0x0000040) */
#define	D_IM_IIP_INT_FACTOR_SL5END					(1<<7)	/**< SL5FF interrupt factor ID  (0x0000080) */
#define	D_IM_IIP_INT_FACTOR_SL6END					(1<<8)	/**< SL6FF interrupt factor ID  (0x0000100) */
#define	D_IM_IIP_INT_FACTOR_SL7END					(1<<9)	/**< SL7FF interrupt factor ID  (0x0000200) */
#define	D_IM_IIP_INT_FACTOR_SL8END					(1<<10)	/**< SL8FF interrupt factor ID  (0x0000400) */
#define	D_IM_IIP_INT_FACTOR_SL0_LINEEND				(1<<11)	/**< SL0MF interrupt factor ID  (0x0000800) */
#define	D_IM_IIP_INT_FACTOR_SL1_LINEEND				(1<<12)	/**< SL1MF interrupt factor ID  (0x0001000) */
#define	D_IM_IIP_INT_FACTOR_SL2_LINEEND				(1<<13)	/**< SL2MF interrupt factor ID  (0x0002000) */
#define	D_IM_IIP_INT_FACTOR_SL3_LINEEND				(1<<14)	/**< SL3MF interrupt factor ID  (0x0004000) */
#define	D_IM_IIP_INT_FACTOR_SL4_LINEEND				(1<<15)	/**< SL4MF interrupt factor ID  (0x0008000) */
#define	D_IM_IIP_INT_FACTOR_SL5_LINEEND				(1<<16)	/**< SL5MF interrupt factor ID  (0x0010000) */
#define	D_IM_IIP_INT_FACTOR_SL6_LINEEND				(1<<17)	/**< SL6MF interrupt factor ID  (0x0020000) */
#define	D_IM_IIP_INT_FACTOR_SL7_LINEEND				(1<<18)	/**< SL7MF interrupt factor ID  (0x0040000) */
#define	D_IM_IIP_INT_FACTOR_SL8_LINEEND				(1<<19)	/**< SL8MF interrupt factor ID  (0x0080000) */

// PDCCTL.FLHALL
#define	D_IM_IIP_NON_FLUSH_IMGCACHE_START			(0)		/**< Non flush cache data when IIP begins to run.	*/
#define	D_IM_IIP_FLUSH_IMGCACHE_START				(1)		/**< Flush cache data when IIP begins to run.		*/

// PDCCTL.EXBIT
#define	D_IM_IIP_EXTBIT_LOWER_ALIGNED				(0)		/**< Store data on lower bit. */
#define	D_IM_IIP_EXTBIT_UPPER_ALIGNED				(1)		/**< Store data on upper bit. */

// SLAXICTl.SL0PKG, SL1PKG, SL2PKG, SL3PKG, SL4PKG, SL5PKG, SL6PKG, SL7PKG, SL8PKG
#define	D_IM_IIP_NON_BURST							(0)		/**< Non burst transfer. */
#define	D_IM_IIP_BURST_MAX_2LINES					(1)		/**< Up to 2lines burst transfer. */
#define	D_IM_IIP_BURST_MAX_4LINES					(2)		/**< Up to 4lines burst transfer. */
#define	D_IM_IIP_BURST_OVER_4LINES					(3)		/**< Over 4lines burst transfer. */

#define D_IM_IIP_AND_WAIT							(0)		/**< AND WAIT */
#define D_IM_IIP_OR_WAIT							(1)		/**< OR WAIT  */

#define D_IM_IIP_HIST_MAXCOUNTS						(256)	/**< Array counts of Histgram buffer */
#define D_IM_IIP_HIST_MAXBYTES						(D_IM_IIP_HIST_MAXCOUNTS * sizeof(ULONG))	/**< Byte number of Histgram buffer */

#define D_IM_IIP_LUT_MAXNUM							(1024)	/**< Array number of LUTRAM */

#define Im_IIP_Set_PLDUNIT( pldunit_reg, pldunit_val )	( \
		pldunit_reg.bit.PLDUNIT_SL_LO = Im_IIP_Get_PLDUNIT_Lo( pldunit_val ), \
		pldunit_reg.bit.PLDUNIT_SL_HI = Im_IIP_Get_PLDUNIT_Hi( pldunit_val ) \
		)

/** Get Lower 32bit of PLDUNIT value. */
#define Im_IIP_Get_PLDUNIT_Lo( pldunit_val )	( (ULONG)((pldunit_val) & 0xFFFFFFFFULL) )

/** Get Upper 32bit of PLDUNIT value. */
#define Im_IIP_Get_PLDUNIT_Hi( pldunit_val )	( (ULONG)(((pldunit_val) & 0xFFFFFFFF00000000ULL) >> 32) )

/** Get PLDUNIT 64bit value from register parameter. */
#define Im_IIP_Get_Reg_PLDUNIT64( pldunit_reg )	( \
		((ULLONG)pldunit_reg.bit.PLDUNIT_LO) & (((ULLONG)pldunit_reg.bit.PLDUNIT_HI) << 32) \
	)

#define	D_IM_IIP_IZAFLG_BIT			(1<<0)
#define	D_IM_IIP_AXEFLG_BIT			(1<<2)

#define	D_IM_IIP_SL0FEN_BIT			D_IM_IIP_SL0FF_BIT
#define	D_IM_IIP_SL0FF_BIT			(1<<0)

#define	D_IM_IIP_SL1FF_BIT			(1<<1)
#define	D_IM_IIP_SL2FF_BIT			(1<<2)
#define	D_IM_IIP_SL3FF_BIT			(1<<3)
#define	D_IM_IIP_SL4FF_BIT			(1<<4)
#define	D_IM_IIP_SL5FF_BIT			(1<<5)
#define	D_IM_IIP_SL6FF_BIT			(1<<6)
#define	D_IM_IIP_SL7FF_BIT			(1<<7)
#define	D_IM_IIP_SL8FF_BIT			(1<<8)
#define	D_IM_IIP_SL0MF_BIT			(1<<16)
#define	D_IM_IIP_SL1MF_BIT			(1<<17)
#define	D_IM_IIP_SL2MF_BIT			(1<<18)
#define	D_IM_IIP_SL3MF_BIT			(1<<19)
#define	D_IM_IIP_SL4MF_BIT			(1<<20)
#define	D_IM_IIP_SL5MF_BIT			(1<<21)
#define	D_IM_IIP_SL6MF_BIT			(1<<22)
#define	D_IM_IIP_SL7MF_BIT			(1<<23)
#define	D_IM_IIP_SL8MF_BIT			(1<<24)
#define	D_IM_IIP_REAF0F_BIT			(1<<0)
#define	D_IM_IIP_REAF1F_BIT			(1<<1)
#define	D_IM_IIP_REAF2F_BIT			(1<<2)
#define	D_IM_IIP_REAF3F_BIT			(1<<3)
#define	D_IM_IIP_REFR0F_BIT			(1<<4)
#define	D_IM_IIP_REFR1F_BIT			(1<<5)
#define	D_IM_IIP_REFLTF_BIT			(1<<6)

// INTEN0, INTEN1, INTEN2 Register bits
#define	D_IM_IIP_IZAEN_BIT			D_IM_IIP_IZAFLG_BIT
#define	D_IM_IIP_AXEEN_BIT			D_IM_IIP_AXEFLG_BIT

#define	D_IM_IIP_SL1FEN_BIT			D_IM_IIP_SL1FF_BIT
#define	D_IM_IIP_SL2FEN_BIT			D_IM_IIP_SL2FF_BIT
#define	D_IM_IIP_SL3FEN_BIT			D_IM_IIP_SL3FF_BIT
#define	D_IM_IIP_SL4FEN_BIT			D_IM_IIP_SL4FF_BIT
#define	D_IM_IIP_SL5FEN_BIT			D_IM_IIP_SL5FF_BIT
#define	D_IM_IIP_SL6FEN_BIT			D_IM_IIP_SL6FF_BIT
#define	D_IM_IIP_SL7FEN_BIT			D_IM_IIP_SL7FF_BIT
#define	D_IM_IIP_SL8FEN_BIT			D_IM_IIP_SL8FF_BIT
#define	D_IM_IIP_SL0MEN_BIT			D_IM_IIP_SL0MF_BIT
#define	D_IM_IIP_SL1MEN_BIT			D_IM_IIP_SL1MF_BIT
#define	D_IM_IIP_SL2MEN_BIT			D_IM_IIP_SL2MF_BIT
#define	D_IM_IIP_SL3MEN_BIT			D_IM_IIP_SL3MF_BIT
#define	D_IM_IIP_SL4MEN_BIT			D_IM_IIP_SL4MF_BIT
#define	D_IM_IIP_SL5MEN_BIT			D_IM_IIP_SL5MF_BIT
#define	D_IM_IIP_SL6MEN_BIT			D_IM_IIP_SL6MF_BIT
#define	D_IM_IIP_SL7MEN_BIT			D_IM_IIP_SL7MF_BIT
#define	D_IM_IIP_SL8MEN_BIT			D_IM_IIP_SL8MF_BIT
#define	D_IM_IIP_REAF0E_BIT			D_IM_IIP_REAF0F_BIT
#define	D_IM_IIP_REAF1E_BIT			D_IM_IIP_REAF1F_BIT
#define	D_IM_IIP_REAF2E_BIT			D_IM_IIP_REAF2F_BIT
#define	D_IM_IIP_REAF3E_BIT			D_IM_IIP_REAF3F_BIT
#define	D_IM_IIP_REFR0E_BIT			D_IM_IIP_REFR0F_BIT
#define	D_IM_IIP_REFR1E_BIT			D_IM_IIP_REFR1F_BIT
#define	D_IM_IIP_REFLTE_BIT			D_IM_IIP_REFLTF_BIT

#define	D_IM_IIP_TRUE		(1)
#define	D_IM_IIP_FALSE		(0)
#define im_iip_roundup_8(val)			(((UINT32)(val) + 7) & 0xFFFFFFF8)
#define im_iip_get_fixed_point(val)		( (INT32)((DOUBLE)(val) * D_IM_IIP_PARAM_AFN_VAL_1_0) )
#define im_iip_util_conv_unitid_to_pldunit(unit_id)		(1ULL << (unit_id))

#define	D_IM_IIP_UTIL_ORIGIN					(0x00)
#define	D_IM_IIP_UTIL_TOPRIGHT					(0x01)
#define	D_IM_IIP_UTIL_BOTTOMLEFT				(0x02)
#define	D_IM_IIP_UTIL_BOTTOMRIGHT				(0x03)
#define	D_IM_IIP_UNITPARAM_BASEADDR		(0x10000)
#define	D_IM_IIP_UNITPARAM_SIZE_ERROR	(0x000)

#define D_IM_IIP_NUM_CPU_CORES			(4)
#define D_IM_IIP_RECURSIVE_COUNT_MAX	(0xFFFFFFFF)
#define D_IM_IIP_SRAM_WAIT_USEC			(1)

#define	D_IM_IIP_STOPPED			(2)

#define im_iip_wait_usec( usec )				Dd_ARM_Wait_ns( (usec) * 1000 )
#define Im_IIP_Dsb()	Dd_ARM_Dsb_Pou()
#define	D_IM_IIP_FLG_USED_BIT_PATTERN		(0x7FFFFFF)
#define	D_IM_IIP_SWTRG_STOPPED		(2)
#define D_IM_IIP_TRIG_STOP_CHK_RETRY_COUNT	(1000)
typedef struct 				_ImIipDefine ImIipDefine;
typedef struct 				_ImIipDefinePrivate ImIipDefinePrivate;
// HISTGRAM
#define D_IM_IIP_NUM_HISTGRAM		(256)
#define D_IM_IIP_HISTGRAM_BYTES		(D_IM_IIP_NUM_HISTGRAM *4)

// Maximum value
#define	D_IM_IIP_MAX_PIXID			(12)
#define D_IM_IIP_MAX_LUTRAM_TYPE	(6)			// A~F
#define D_IM_IIP_MAX_LUTRAM_RESOL	(1024)		// 0~1023

#define im_iip_get_reg_signed_a( val, reg, type, member )		{ \
			type work = { .word[0] = 0UL }; \
			work.bit.member = -1L; \
			if( ((work.bit.member) == 0xFFFFFFFFUL) || ((reg.bit.member) <= ((work.bit.member) /2)) ) { \
				(val) = reg.bit.member; \
			} \
			else { \
				(val) = -(work.bit.member - reg.bit.member +1); \
			} \
			im_iip_check_reg_type( (reg), work ); /* The structure type matching check. */ \
		}

#ifdef CO_IIP_DEBUG_PRINT_FUNC
#define Im_IIP_Print_Pcdbg	Ddim_Print
#else
#define Im_IIP_Print_Pcdbg(dmy)
#endif

#ifdef CO_IIP_REG_TYPE_CHECK
#define im_iip_check_reg_type( dst, src )	(dst) = (src);
#else
#define im_iip_check_reg_type( dst, src )
#endif

#define im_xxx_get_reg_signed( val, reg, type, member )		{ \
			type work = { .word = 0UL }; \
			work.bit.member = -1L; \
			if( ((work.bit.member) == 0xFFFFFFFFUL) || ((reg.bit.member) <= ((work.bit.member) /2)) ) { \
				(val) = reg.bit.member; \
			} \
			else { \
				(val) = -(work.bit.member - reg.bit.member +1); \
			} \
			im_iip_check_reg_type( (reg), work ); /* The structure type matching check. */ \
		}

// Set signed Bit field value from signed variable.
#define im_iip_set_reg_signed_a( reg, type, member, val )		\
		{ \
			type work = { .word[0] = 0UL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			im_iip_check_reg_type( work, (reg) );	/* The structure type matching check. */ \
		}

// Unit Parameter [debug function]
#define	D_IM_IIP_UNITPARAM_SIZE_LD		(0x040)
#define	D_IM_IIP_UNITPARAM_SIZE_CFL		(0x020)
#define	D_IM_IIP_UNITPARAM_SIZE_GPC		(0x01C)
#define	D_IM_IIP_UNITPARAM_SIZE_CSC		(0x060)
#define	D_IM_IIP_UNITPARAM_SIZE_AFN		(0x070)
#define	D_IM_IIP_UNITPARAM_SIZE_FRECT	(0x070)
#define	D_IM_IIP_UNITPARAM_SIZE_MON		(0x060)
#define	D_IM_IIP_UNITPARAM_SIZE_BLEND	(0x0DC)
#define	D_IM_IIP_UNITPARAM_SIZE_SL		(0x3A0)
#define	D_IM_IIP_UNITPARAM_SIZE_LUT		(0x0E0)

#define	D_IM_IIP_UNITPARAM_SIZE_MFT		(0x020)

#define	D_IM_IIP_UNITPARAM_SIZE_FLT		(0x240)

// IZACTL1.bit.TRG
#define	D_IM_IIP_STOP				(0)
#define	D_IM_IIP_START				(1)

// UNITINFTBL0.bit.SWTRG
#define	D_IM_IIP_SWTRG_START		(1)

#define	D_IM_IIP_SWTRG_RUNNING		(3)

#define Im_IIP_Dmb()	Dd_ARM_Dmb_Pou()

typedef struct {
	E_IM_IIP_UNIT_ID	unit_id;
	const CHAR*			unit_name;
} T_IM_IIP_DUMP_UNIT_NAME;

typedef struct {
	ULONG				flg_bitmask;		// Bitmask of INTIZ0/INTIZ1/INTIZ2.
	ULONG				ena_bitmask;		// Bitmask of INTEN0/INTEN1/INTEN2.
	ULONG				int_fact;			// Interrupt factor bitmask. (parameter "interrupt_bitmask" of Im_IIP_Set_Interrupt() and Im_IIP_Set_IntHandler())
	ULLONG				unitid_bitmask;		// PLDUNIT bitmask. (D_IM_IIP_PARAM_PLDUNIT_xxx)
	T_IM_IIP_CALLBACK	callback_func;		// Software trigger's Callback function.
} T_IM_IIP_INTFLG_TBL;

typedef union {
	ULLONG	bit64;
	struct {
		ULONG	lower;
		ULONG	upper;
	}bit32;
	struct {
		DDIM_USER_FLGPTN	lower;
		DDIM_USER_FLGPTN	upper;
	}flgptn;
} U_IM_IIP_64BIT_MASK;

// parameter structure of im_iip_calc_timeout()
typedef struct {
	DDIM_USER_TMO		last_wait_time;		// "wait_time" for next OS serivce call (ex. DDIM_User_Twai_Flg()).
	DDIM_USER_TMO		wait_time;			// "wait_time" parameter of MILB_API functions.
	DDIM_USER_SYSTIM	start_time;			// System time when start MILB_API functions.
	DDIM_USER_SYSTIM	cur_time;			// Now System time.
} T_IM_IIP_TIMEOUT;

typedef struct {
	ULLONG				unit_bitmask;						// Using unit bitmask. (parameter "unitid_bitmask" of Im_IIP_Open_SWTRG())
	ULONG				pixfmttbl_bitmask;					// Using PIXFMTTBL bitmask. (parameter "pixid_bitmask" of Im_IIP_Open_SWTRG())
	ULONG				res_bitmask;						// Using resource bitmask. (parameter "open_res_bitmask" of Im_IIP_Open_SWTRG())
	UINT32				cache_users[D_IM_IIP_CACHE_MAXNUM];	// Using users count of Image Cache.
} T_IM_IIP_SWTRG_MNG;

struct _ImIipDefine {
	KObject parent;

   T_IM_IIP_CALLBACK  gimIipCallback;
};

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

KConstType 		    	im_iip_define_get_type(void);
ImIipDefine*		       			 	im_iip_define_get(void);
ImIipDefine*		       			 	im_iip_define_new(void);

extern INT32 Im_IIP_Init( VOID );
extern INT32 Im_IIP_Init_Unit( const E_IM_IIP_UNIT_ID unit_id );
extern INT32 Im_IIP_Open( const INT32 wait_time );
extern INT32 Im_IIP_Close( VOID );
extern INT32 Im_IIP_Ctrl_PIXFMTTBL( const UINT32 pixid, const T_IM_IIP_PIXFMTTBL* const tbl );
extern INT32 Im_IIP_Ctrl_UNITINFTBL( const T_IM_IIP_UNITINFTBL* const tbl );
extern INT32 Im_IIP_Ctrl_LUT( const T_IM_IIP_LUT* const lut );
extern INT32 Im_IIP_Open_SWTRG( const ULLONG unitid_bitmask64, const UINT32 pixid_bitmask, const UINT32 open_res_bitmask, const INT32 wait_time );
extern INT32 Im_IIP_Close_SWTRG( const ULLONG unitid_bitmask64, const UINT32 pixid_bitmask, const UINT32 open_res_bitmask );
extern INT32 Im_IIP_Ctrl_SWTRG_Unit( const E_IM_IIP_UNIT_ID unit_id, const T_IM_IIP_UNIT_CFG* const p_unitcfg );
extern INT32 Im_IIP_Ctrl_AXI( const E_IM_IIP_AXI_ID axi_id, const T_IM_IIP_CTRL_AXI* const cfg );
extern INT32 Im_IIP_Ctrl_AXI_ALL( const T_IM_IIP_CTRL_AXI_ALL* const cfg );
extern INT32 Im_IIP_Ctrl_Base( const T_IM_IIP_CTRL_BASE* const cfg );
extern INT32 Im_IIP_Set_Interrupt( const ULONG interrupt_bitmask, const UCHAR permission_flg );
extern INT32 Im_IIP_Set_SLIntLines( const ULONG interrupt_bitmask, const UINT32 trans_lines );
extern INT32 Im_IIP_Update_PADRS( const E_IM_IIP_UNIT_ID unit_id, const ULONG unit_param_addr );
extern INT32 Im_IIP_Start( VOID );
extern INT32 Im_IIP_LinkStart_SWTRG( const E_IM_IIP_UNIT_ID unit_id, const INT32 swtrg, const UINT32 link_onoff );
extern INT32 Im_IIP_Start_SWTRG( const E_IM_IIP_UNIT_ID unit_id, const INT32 swtrg );
extern INT32 Im_IIP_Stop( const UINT32 stop_type );
extern INT32 Im_IIP_Wait_End( UINT32* const p_wait_factor, const UINT32 wait_factor, const UINT32 wait_mode, const INT32 wait_time );
extern INT32 Im_IIP_Int_Handler( VOID );
extern INT32 Im_IIP_Clear_HISTGRAM( const UINT32 histgram_a_clr_flag, const UINT32 histgram_b_clr_flag, const UINT32 histgram_c_clr_flag, const UINT32 histgram_d_clr_flag );
extern INT32 Im_IIP_Get_HISTGRAM( ULONG* const buffer_histgram_a, ULONG* const buffer_histgram_b, ULONG* const buffer_histgram_c, ULONG* const buffer_histgram_d );
extern INT32 Im_IIP_Get_HISTMAX( UCHAR* const histmax_a, UCHAR* const histmax_b, UCHAR* const histmax_c, UCHAR* const histmax_d );
extern INT32 Im_IIP_Get_MAXMON( T_IM_IIP_MAXMON* const mon );
extern INT32 Im_IIP_Get_MINMON( T_IM_IIP_MINMON* const mon );
extern INT32 Im_IIP_Get_ADDMON( T_IM_IIP_ADDMON* const mon );
extern INT32 Im_IIP_Get_ImgCache_Access_Info( const E_IM_IIP_CACHE_CH cache_ch, T_IM_IIP_ACCESS_INFO* const info );
extern INT32 Im_IIP_Get_AXI_Status( T_IM_IIP_AXI_STATUS* const sts );
extern INT32 Im_IIP_Get_SL_Status( UINT32* const sl_status );
extern INT32 Im_IIP_Get_UNIT_PARAM( const E_IM_IIP_UNIT_ID unit_id, ULONG* const p_param_buffer, UINT32* const size );
extern INT32 Im_IIP_Set_AccessEnable( const UINT32 res_bitmask, const UCHAR permission_flg );

//私有函数变成公有函数被调用
INT32 Im_IIP_Set_IntHandler( const ULONG interrupt_bitmask, const T_IM_IIP_CALLBACK int_handler );
UINT32 im_iip_irq_disable( void );
void im_iip_irq_enable( UINT32 irq_mask );
INT32 im_iip_util_resizerotate_main( T_IM_IIP_UTIL_PARAM_RESIZE_ROTATE* const rr_param, const T_IM_IIP_UTIL_RR* const cfg );
INT32 im_iip_check_wait_time( const INT32 wait_time );
INT32 im_iip_util_csc_main( T_IM_IIP_UTIL_PARAM_CSC* const csc_param, const T_IM_IIP_UTIL_CSC* const cfg, const INT32 wait_time );
INT32 im_iip_util_lut_main( T_IM_IIP_UTIL_PARAM_LUT* const lut_param, const T_IM_IIP_UTIL_LUT* const cfg );
INT32 im_iip_util_alpha_main( T_IM_IIP_UTIL_PARAM_ALPHA* const alp_param, const T_IM_IIP_UTIL_ALPHABLEND* const cfg );
VOID im_iip_get_unit_param_size( UINT32* const size, const E_IM_IIP_UNIT_ID unit_id );
VOID im_iip_On_Iipclk( VOID );
VOID im_iip_On_Iclk( VOID );
VOID im_iip_get_regword( ULONG* dst, const volatile ULONG* src, const UINT32 bytes );
VOID im_iip_Off_Iclk( VOID );
VOID im_iip_Off_Iipclk( VOID );
VOID im_iip_clear_hwen_all( VOID );
VOID im_iip_set_acesen0_reg( volatile T_IM_IIP_SWTRG_MNG* const swtrg_mng );
volatile struct io_iip_uinftbl* im_iip_get_unitinftbl_regaddr( const E_IM_IIP_UNIT_ID unit_id );
VOID im_iip_set_UNITINFTBL_SL( const T_IM_IIP_UNIT_CFG* const sl_cfg, volatile struct io_iip_uinftbl* const pUNITINFTBL );
VOID im_iip_set_UNITINFTBL( const T_IM_IIP_UNIT_CFG* const cfg, volatile struct io_iip_uinftbl* const pUNITINFTBL );
VOID im_iip_fill_word( volatile ULONG* dst, const UINT32 start_pos, const UINT32 num, const ULONG fill_value );
VOID im_iip_copy_short_to_word( volatile ULONG* dst, const USHORT* src, const UINT32 bytes );
VOID im_iip_update_pixfmttbl( const UINT32 pixid );
VOID im_iip_wait_pftflg( VOID );
INT32 im_iip_hunt_unit_and_pix( const U_IM_IIP_64BIT_MASK unitid_bitmask, const UINT32 pixid_bitmask, const UINT32 other_bitmask, const UINT32 cache_bitmask );
INT32 im_iip_twai_pol_sem( const DDIM_USER_ID semid, const DDIM_USER_TMO tmout );
INT32 im_iip_calc_timeout( T_IM_IIP_TIMEOUT* const tmout );
VOID im_iip_Off_izarac_caxrac( VOID );
INT32 im_iip_twai_pol_flg( const DDIM_USER_ID flagid, const DDIM_USER_FLGPTN waiptn, const DDIM_USER_MODE wfmode, DDIM_USER_FLGPTN* const p_flgptn, const DDIM_USER_TMO tmout );
VOID im_iip_On_izarac_caxrac( VOID );

VOID im_iip_set_pixfmttbl_param( T_IM_IIP_PIXFMTTBL* const pixfmttbl,
									    const T_IM_IIP_UTIL_IMG_GBL* const gbl,
									    const UINT32 pix_depth,
									    const T_IM_IIP_UTIL_ALPHA_INFO* const alpha );

ULONG im_iip_util_conv_pixid( const E_IM_IIP_PIXID pixid );
VOID im_iip_set_phvsz_1d_sl( T_IM_IIP_UTIL_PHVSZ* const phvsz,
								    const T_IM_IIP_UTIL_IMG_INT* const dst );
VOID im_iip_set_unitinftbl_param( T_IM_IIP_UNIT_CFG* const unitinftbl_param, const E_IM_IIP_UNIT_ID id, const VOID* const addr, const ULLONG unitid_bitmask );

ULONG im_iip_util_conv_portid( const E_IM_IIP_UNIT_ID unitid );
VOID im_iip_set_sl_unit_param( T_IM_IIP_PARAM_STS* const sl,
									  const T_IM_IIP_UTIL_PHVSZ* const phvsz,
									  const T_IM_IIP_UTIL_RECT_INT* const dst_rect,
									  const T_IM_IIP_UTIL_IMG_GBL* const dst_gbl,
									  const UINT32 pix_depth );
VOID im_iip_set_1d_unit_param( T_IM_IIP_PARAM_1DL* const p1D,
									  const T_IM_IIP_UTIL_PHVSZ* const phvsz,
									  const T_IM_IIP_UTIL_IMG_INT* const src,
									  const UINT32 pix_depth,
									  const E_IM_IIP_PARAM_CSEL cache_select );

INT32 im_iip_util_exec_rotate( T_IM_IIP_UTIL_PARAM_RESIZE_ROTATE* const rr_param, const T_IM_IIP_UTIL_RR* const cfg );
INT32 im_iip_util_exec_csc( T_IM_IIP_UTIL_PARAM_CSC* const csc_param, const T_IM_IIP_UTIL_CSC* const cfg );

VOID im_iip_util_set_lut_unit_param( T_IM_IIP_PARAM_LUT* const lut,
									   const T_IM_IIP_UTIL_LUT* const cfg );

ULONG im_iip_util_conv_portid_1( const E_IM_IIP_UNIT_ID unitid );
VOID im_iip_set_axi_param( const E_IM_IIP_UNIT_ID unitid, E_IM_IIP_AXI_ID* const axi_id, T_IM_IIP_CTRL_AXI* const axi_cfg, const UCHAR master_IF );

E_IM_IIP_PARAM_PF_PDIST im_iip_get_PF_PDIST( const UINT32 pix_depth,
												    const E_IM_IIP_FTYPE frame_type,
												    const E_IM_IIP_PFMT pix_format,
												    const UINT32 alpha );
INT32 im_iip_unset_interrupt( const U_IM_IIP_64BIT_MASK unitid_bitmask, const UCHAR cause );
//————————————————————————————————————————————————

#define im_iip_get_gim_iip(self)          ((self->gimIipCallback))
#define im_iip_set_gim_iip(self,g)        {self->gimIipCallback = g;}

#if 0	// B2Y Link not support

extern INT32 Im_IIP_Set_B2YLinkEnable( const UCHAR b2y_link );

#endif	// B2Y Link not support

extern INT32 Im_IIP_Get_Genline( T_IM_IIP_GENLINE* const genline );
extern INT32 Im_IIP_Get_Debug_Monitor( T_IM_IIP_DEBUG_MONITOR* const monitor_val );
extern INT32 Im_IIP_Start_DumpUnitReg( const E_IM_IIP_UNIT_ID unit_id );
extern INT32 Im_IIP_Start_DumpUnitReg_ByName( const CHAR* const unit_name );
extern INT32 Im_IIP_Stop_DumpUnitReg( VOID );
#ifdef __cplusplus
}
#endif	// __cplusplus

#ifdef CO_IM_IIP_ENABLE_UTILITY

#include "im_iip_param.h"

#define D_IM_IIP_UTIL_RR_BUF_BYTES				(268 +8)	/**< Buffer bytes of IM_IIP_Utility_ResizeRotate() */
#define D_IM_IIP_UTIL_CSC_BUF_BYTES				(280 +8)	/**< Buffer bytes of IM_IIP_Utility_CSC() */
#define D_IM_IIP_UTIL_LUT_BUF_BYTES				(408 +8)	/**< Buffer bytes of IM_IIP_Utility_LUT() */
#define D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES		(352 +8)	/**< Buffer bytes of IM_IIP_Utility_AlphaBlend() */

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

extern INT32 IM_IIP_Utility_ResizeRotate( const T_IM_IIP_UTIL_RR* const cfg0,
										  const T_IM_IIP_UTIL_RR* const cfg1,
										  const UCHAR param_master_IF,
										  const ULONG param_buffer_addr,
										  const INT32 wait_time );

extern INT32 IM_IIP_Utility_CSC( const T_IM_IIP_UTIL_CSC* const cfg0,
								 const T_IM_IIP_UTIL_CSC* const cfg1,
								 const UCHAR param_master_IF,
								 const ULONG param_buffer_addr,
								 const INT32 wait_time );

extern INT32 IM_IIP_Utility_LUT( const T_IM_IIP_UTIL_LUT* const cfg,
								 const UCHAR param_master_IF,
								 const ULONG param_buffer_addr,
								 const INT32 wait_time );

extern INT32 IM_IIP_Utility_AlphaBlend( const T_IM_IIP_UTIL_ALPHABLEND* cfg,
										const UCHAR param_master_IF,
										const ULONG param_buffer_addr,
										const INT32 wait_time );


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// CO_IM_IIP_ENABLE_UTILITY

#endif /* __IM_IIP_DEFINE_H__ */
