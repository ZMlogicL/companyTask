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
#define  	/**< DEBUG */
#endif

#define	ImIipDefine_D_IM_IIP_OK									(D_DDIM_OK)								/**< Normal end                      (0) */
#define	ImIipDefine_D_IM_IIP_INVALID_ARG_ERR					(D_IM_IIP | D_DDIM_INPUT_PARAM_ERROR)	/**< Invalid argument error (0x0C000001) */
#define	ImIipDefine_D_IM_IIP_TIMEOUT_ERR						(D_IM_IIP | D_DDIM_TIMEOUT)				/**< Wait timeout error     (0x0C000013) */
#define	ImIipDefine_D_IM_IIP_SYSTEMCALL_ERR						(D_IM_IIP | D_DDIM_SYSTEM_ERROR)		/**< System call error      (0x0C000099) */
#define	ImIipDefine_D_IM_IIP_ERR								(D_IM_IIP | 0x100)						/**< Other error            (0x0C000100) */
#define	ImIipDefine_D_IM_IIP_ABORT_FAILED_ERR					(D_IM_IIP | 0x101)						/**< Abort failed error     (0x0C000101) */

/** @} */	// name

#define	ImIipDefine_D_IM_IIP_RUNNING			(3)
#define ImIipDefine_D_IM_IIP_PIXID_MAXNUM						(12)	/**< PIXID number */

#define ImIipDefine_D_IM_IIP_ENABLE_OFF							(0)		/**< The function is disable */
#define ImIipDefine_D_IM_IIP_ENABLE_ON							(1)		/**< The function is enable */

#define ImIipDefine_D_IM_IIP_STOP								(0)		/**< Stop IIP */
#define ImIipDefine_D_IM_IIP_ABORT								(1)		/**< Abort IIP */

// PLDUNIT BitMask
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_NONE			(0ULL)			/**< None			*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD0			(1ULL << 0)		/**< Loader 0		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD1			(1ULL << 1)		/**< Loader 1		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD2			(1ULL << 2)		/**< Loader 2		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD3			(1ULL << 3)		/**< Loader 3		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_FLT			(1ULL << 4)		/**< FLT			*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_AFN0			(1ULL << 5)		/**< AFN 0			*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_AFN1			(1ULL << 6)		/**< AFN 1			*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_AFN2			(1ULL << 7)		/**< AFN 2			*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_FRECT0		(1ULL << 8)		/**< FRECT 0		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_MON			(1ULL << 9)		/**< Monitor		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL0			(1ULL << 10)	/**< Store 0		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL1			(1ULL << 11)	/**< Store 1		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL2			(1ULL << 12)	/**< Store 2		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL3			(1ULL << 13)	/**< Store 3		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL4			(1ULL << 14)	/**< Store 4		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL5			(1ULL << 15)	/**< Store 5		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_CSC0			(1ULL << 16)	/**< CSC 0			*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_CSC1			(1ULL << 17)	/**< CSC 1			*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LUT			(1ULL << 18)	/**< LUT			*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_GPC			(1ULL << 19)	/**< GPC			*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_BLEND0		(1ULL << 20)	/**< Blend 0		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_BLEND1		(1ULL << 21)	/**< Blend 1		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_FRECT1		(1ULL << 22)	/**< FRECT 1		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_CFL0			(1ULL << 23)	/**< Cache Flow 0	*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_CSC2			(1ULL << 27)	/**< CSC 2			*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_CSC3			(1ULL << 28)	/**< CSC 3			*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL6			(1ULL << 29)	/**< Store 6		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL7			(1ULL << 30)	/**< Store 7		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL8			(1ULL << 31)	/**< Store 8		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD4			(1ULL << 32)	/**< Loader 4		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD5			(1ULL << 33)	/**< Loader 5		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD6			(1ULL << 34)	/**< Loader 6		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD7			(1ULL << 35)	/**< Loader 7		*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_AFN3			(1ULL << 36)	/**< AFN 3			*/
#define ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_MFT			(1ULL << 37)	/**< MFT			*/

// UNITINFTBL.SWTRG
#define ImIipDefine_D_IM_IIP_SWTRG_OFF							(0)		/**< Don't care unit	*/
#define ImIipDefine_D_IM_IIP_SWTRG_ON							(1)		/**< Start unit */

// UNITINFTBL.HWEN
#define	ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG						(0)		/**< SWTRG control	 */
#define	ImIipDefine_D_IM_IIP_HW_CTRL_AUTO						(1)		/**< HW auto control */

// UNITINFTBL.CHAIN
#define	ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE				(0)		/**< PLDUNIT do not chain operation */
#define	ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_ENABLE				(1)		/**< PLDUNIT do chain operation */

// PIXFMTTBL.PDEPTH
#define	ImIipDefine_D_IM_IIP_PDEPTH_8BITS						(0)		/**< 8bits			*/
#define	ImIipDefine_D_IM_IIP_PDEPTH_12BITS						(1)		/**< 12bits-packed	*/
#define	ImIipDefine_D_IM_IIP_PDEPTH_16BITS						(2)		/**< 16bits(14bits)	*/

// PIXFMTTBL.CHKYORDR
#define	ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y0_G					(0)		/**< YO(G)	   */
#define	ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CB_B					(1)		/**< Cb(B)	   */
#define	ImIipDefine_D_IM_IIP_CHUNKY_COLOR_CR_R					(2)		/**< Cr(R)	   */
#define	ImIipDefine_D_IM_IIP_CHUNKY_COLOR_Y1_A					(3)		/**< Y1(Alpha) */

// PIXFMTTBL.SGYG, SGB, SGR, SGA
#define	ImIipDefine_D_IM_IIP_UNSIGNED_DATA						(0)		/**< Unsigned data */
#define	ImIipDefine_D_IM_IIP_SIGNED_DATA						(1)		/**< Signed data   */

// PIXFMTTBL.ALPHA
#define	ImIipDefine_D_IM_IIP_ALPHA_FALSE						(0)		/**< Image without alpha */
#define	ImIipDefine_D_IM_IIP_ALPHA_TRUE							(1)		/**< Image with alpha	 */

// PIXFMTTBL.ASUBSPL
#define	ImIipDefine_D_IM_IIP_ALPHA_NO_SUBSAMP					(0)		/**< No subsampling							*/
#define	ImIipDefine_D_IM_IIP_ALPHA_H_SUBSAMP					(1)		/**< Horizontal subsampling					*/
#define	ImIipDefine_D_IM_IIP_ALPHA_HV_SUBSAMP					(2)		/**< Horizontal and Vertical subsampling	*/

// PIXFMTTBL.MTIFYG, MTIFB, MTIFR, MTIFA (for SL2/SL5 only)
#define	ImIipDefine_D_IM_IIP_MASTER_IF0							(1)		/**< Master I/F 0 */
#define	ImIipDefine_D_IM_IIP_MASTER_IF1							(0)		/**< Master I/F 1 */
#define	ImIipDefine_D_IM_IIP_MASTER_IF2							(0)		/**< Master I/F 2 */

// PIXFMTTBL.OARBHV
#define	ImIipDefine_D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE			(0)		/**< Fixed value */
#define	ImIipDefine_D_IM_IIP_OUTSIDE_IMG_EDGE					(1)		/**< Image edge value (value of pixels on top, bottom, left and right lines) */

#if 0	// B2Y Link not support
// IZACTL1.LKEN
#define	ImIipDefine_D_IM_IIP_LINK_B2Y_OFF						(0)		/**< Disable linkage between B2Y to IIP.	*/
#define	ImIipDefine_D_IM_IIP_LINK_B2Y_ON						(1)		/**< Enable linkage between B2Y to IIP.	*/
#endif	// B2Y Link not support

#define	ImIipDefine_D_IM_IIP_INT_FACTOR_IZAEND					(1<<0)	/**< IZAFLG interrupt factor ID (0x0000001) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_AXIERR					(1<<1)	/**< AXEFLG interrupt factor ID (0x0000002) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL0END					(1<<2)	/**< SL0FF interrupt factor ID  (0x0000004) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL1END					(1<<3)	/**< SL1FF interrupt factor ID  (0x0000008) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL2END					(1<<4)	/**< SL2FF interrupt factor ID  (0x0000010) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL3END					(1<<5)	/**< SL3FF interrupt factor ID  (0x0000020) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL4END					(1<<6)	/**< SL4FF interrupt factor ID  (0x0000040) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL5END					(1<<7)	/**< SL5FF interrupt factor ID  (0x0000080) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL6END					(1<<8)	/**< SL6FF interrupt factor ID  (0x0000100) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL7END					(1<<9)	/**< SL7FF interrupt factor ID  (0x0000200) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL8END					(1<<10)	/**< SL8FF interrupt factor ID  (0x0000400) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL0_LINEEND				(1<<11)	/**< SL0MF interrupt factor ID  (0x0000800) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL1_LINEEND				(1<<12)	/**< SL1MF interrupt factor ID  (0x0001000) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL2_LINEEND				(1<<13)	/**< SL2MF interrupt factor ID  (0x0002000) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL3_LINEEND				(1<<14)	/**< SL3MF interrupt factor ID  (0x0004000) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL4_LINEEND				(1<<15)	/**< SL4MF interrupt factor ID  (0x0008000) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL5_LINEEND				(1<<16)	/**< SL5MF interrupt factor ID  (0x0010000) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL6_LINEEND				(1<<17)	/**< SL6MF interrupt factor ID  (0x0020000) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL7_LINEEND				(1<<18)	/**< SL7MF interrupt factor ID  (0x0040000) */
#define	ImIipDefine_D_IM_IIP_INT_FACTOR_SL8_LINEEND				(1<<19)	/**< SL8MF interrupt factor ID  (0x0080000) */

// PDCCTL.FLHALL
#define	ImIipDefine_D_IM_IIP_NON_FLUSH_IMGCACHE_START			(0)		/**< Non flush cache data when IIP begins to run.	*/
#define	ImIipDefine_D_IM_IIP_FLUSH_IMGCACHE_START				(1)		/**< Flush cache data when IIP begins to run.		*/

// PDCCTL.EXBIT
#define	ImIipDefine_D_IM_IIP_EXTBIT_LOWER_ALIGNED				(0)		/**< Store data on lower bit. */
#define	ImIipDefine_D_IM_IIP_EXTBIT_UPPER_ALIGNED				(1)		/**< Store data on upper bit. */

// SLAXICTl.SL0PKG, SL1PKG, SL2PKG, SL3PKG, SL4PKG, SL5PKG, SL6PKG, SL7PKG, SL8PKG
#define	ImIipDefine_D_IM_IIP_NON_BURST							(0)		/**< Non burst transfer. */
#define	ImIipDefine_D_IM_IIP_BURST_MAX_2LINES					(1)		/**< Up to 2lines burst transfer. */
#define	ImIipDefine_D_IM_IIP_BURST_MAX_4LINES					(2)		/**< Up to 4lines burst transfer. */
#define	ImIipDefine_D_IM_IIP_BURST_OVER_4LINES					(3)		/**< Over 4lines burst transfer. */

#define ImIipDefine_D_IM_IIP_AND_WAIT							(0)		/**< AND WAIT */
#define ImIipDefine_D_IM_IIP_OR_WAIT							(1)		/**< OR WAIT  */

#define ImIipDefine_D_IM_IIP_HIST_MAXCOUNTS						(256)	/**< Array counts of Histgram buffer */
#define ImIipDefine_D_IM_IIP_HIST_MAXBYTES						(ImIipDefine_D_IM_IIP_HIST_MAXCOUNTS * sizeof(ULONG))	/**< Byte number of Histgram buffer */

#define ImIipDefine_D_IM_IIP_LUT_MAXNUM							(1024)	/**< Array number of LUTRAM */

#define ImIipDefine_Im_IIP_SET_PLDUNIT( pldunit_reg, pldunit_val )	( \
		pldunit_reg.bit.PLDUNIT_SL_LO = ImIipDefine_Im_IIP_GET_PLDUNIT_LO( pldunit_val ), \
		pldunit_reg.bit.PLDUNIT_SL_HI = ImIipDefine_Im_IIP_GET_PLDUNIT_HI( pldunit_val ) \
		)

/** Get Lower 32bit of PLDUNIT value. */
#define ImIipDefine_Im_IIP_GET_PLDUNIT_LO( pldunit_val )	( (ULONG)((pldunit_val) & 0xFFFFFFFFULL) )

/** Get Upper 32bit of PLDUNIT value. */
#define ImIipDefine_Im_IIP_GET_PLDUNIT_HI( pldunit_val )	( (ULONG)(((pldunit_val) & 0xFFFFFFFF00000000ULL) >> 32) )

/** Get PLDUNIT 64bit value from register parameter. */
#define ImIipDefine_Im_IIP_GET_REG_PLDUNIT64( pldunit_reg )	( \
		((ULLONG)pldunit_reg.bit.PLDUNIT_LO) & (((ULLONG)pldunit_reg.bit.PLDUNIT_HI) << 32) \
	)

#define	ImIipDefine_D_IM_IIP_IZAFLG_BIT			(1<<0)
#define	ImIipDefine_D_IM_IIP_AXEFLG_BIT			(1<<2)

#define	ImIipDefine_D_IM_IIP_SL0FEN_BIT			ImIipDefine_D_IM_IIP_SL0FF_BIT
#define	ImIipDefine_D_IM_IIP_SL0FF_BIT			(1<<0)

#define	ImIipDefine_D_IM_IIP_SL1FF_BIT			(1<<1)
#define	ImIipDefine_D_IM_IIP_SL2FF_BIT			(1<<2)
#define	ImIipDefine_D_IM_IIP_SL3FF_BIT			(1<<3)
#define	ImIipDefine_D_IM_IIP_SL4FF_BIT			(1<<4)
#define	ImIipDefine_D_IM_IIP_SL5FF_BIT			(1<<5)
#define	ImIipDefine_D_IM_IIP_SL6FF_BIT			(1<<6)
#define	ImIipDefine_D_IM_IIP_SL7FF_BIT			(1<<7)
#define	ImIipDefine_D_IM_IIP_SL8FF_BIT			(1<<8)
#define	ImIipDefine_D_IM_IIP_SL0MF_BIT			(1<<16)
#define	ImIipDefine_D_IM_IIP_SL1MF_BIT			(1<<17)
#define	ImIipDefine_D_IM_IIP_SL2MF_BIT			(1<<18)
#define	ImIipDefine_D_IM_IIP_SL3MF_BIT			(1<<19)
#define	ImIipDefine_D_IM_IIP_SL4MF_BIT			(1<<20)
#define	ImIipDefine_D_IM_IIP_SL5MF_BIT			(1<<21)
#define	ImIipDefine_D_IM_IIP_SL6MF_BIT			(1<<22)
#define	ImIipDefine_D_IM_IIP_SL7MF_BIT			(1<<23)
#define	ImIipDefine_D_IM_IIP_SL8MF_BIT			(1<<24)
#define	ImIipDefine_D_IM_IIP_REAF0F_BIT			(1<<0)
#define	ImIipDefine_D_IM_IIP_REAF1F_BIT			(1<<1)
#define	ImIipDefine_D_IM_IIP_REAF2F_BIT			(1<<2)
#define	ImIipDefine_D_IM_IIP_REAF3F_BIT			(1<<3)
#define	ImIipDefine_D_IM_IIP_REFR0F_BIT			(1<<4)
#define	ImIipDefine_D_IM_IIP_REFR1F_BIT			(1<<5)
#define	ImIipDefine_D_IM_IIP_REFLTF_BIT			(1<<6)

// INTEN0, INTEN1, INTEN2 Register bits
#define	ImIipDefine_D_IM_IIP_IZAEN_BIT			ImIipDefine_D_IM_IIP_IZAFLG_BIT
#define	ImIipDefine_D_IM_IIP_AXEEN_BIT			ImIipDefine_D_IM_IIP_AXEFLG_BIT

#define	ImIipDefine_D_IM_IIP_SL1FEN_BIT			ImIipDefine_D_IM_IIP_SL1FF_BIT
#define	ImIipDefine_D_IM_IIP_SL2FEN_BIT			ImIipDefine_D_IM_IIP_SL2FF_BIT
#define	ImIipDefine_D_IM_IIP_SL3FEN_BIT			ImIipDefine_D_IM_IIP_SL3FF_BIT
#define	ImIipDefine_D_IM_IIP_SL4FEN_BIT			ImIipDefine_D_IM_IIP_SL4FF_BIT
#define	ImIipDefine_D_IM_IIP_SL5FEN_BIT			ImIipDefine_D_IM_IIP_SL5FF_BIT
#define	ImIipDefine_D_IM_IIP_SL6FEN_BIT			ImIipDefine_D_IM_IIP_SL6FF_BIT
#define	ImIipDefine_D_IM_IIP_SL7FEN_BIT			ImIipDefine_D_IM_IIP_SL7FF_BIT
#define	ImIipDefine_D_IM_IIP_SL8FEN_BIT			ImIipDefine_D_IM_IIP_SL8FF_BIT
#define	ImIipDefine_D_IM_IIP_SL0MEN_BIT			ImIipDefine_D_IM_IIP_SL0MF_BIT
#define	ImIipDefine_D_IM_IIP_SL1MEN_BIT			ImIipDefine_D_IM_IIP_SL1MF_BIT
#define	ImIipDefine_D_IM_IIP_SL2MEN_BIT			ImIipDefine_D_IM_IIP_SL2MF_BIT
#define	ImIipDefine_D_IM_IIP_SL3MEN_BIT			ImIipDefine_D_IM_IIP_SL3MF_BIT
#define	ImIipDefine_D_IM_IIP_SL4MEN_BIT			ImIipDefine_D_IM_IIP_SL4MF_BIT
#define	ImIipDefine_D_IM_IIP_SL5MEN_BIT			ImIipDefine_D_IM_IIP_SL5MF_BIT
#define	ImIipDefine_D_IM_IIP_SL6MEN_BIT			ImIipDefine_D_IM_IIP_SL6MF_BIT
#define	ImIipDefine_D_IM_IIP_SL7MEN_BIT			ImIipDefine_D_IM_IIP_SL7MF_BIT
#define	ImIipDefine_D_IM_IIP_SL8MEN_BIT			ImIipDefine_D_IM_IIP_SL8MF_BIT
#define	ImIipDefine_D_IM_IIP_REAF0E_BIT			ImIipDefine_D_IM_IIP_REAF0F_BIT
#define	ImIipDefine_D_IM_IIP_REAF1E_BIT			ImIipDefine_D_IM_IIP_REAF1F_BIT
#define	ImIipDefine_D_IM_IIP_REAF2E_BIT			ImIipDefine_D_IM_IIP_REAF2F_BIT
#define	ImIipDefine_D_IM_IIP_REAF3E_BIT			ImIipDefine_D_IM_IIP_REAF3F_BIT
#define	ImIipDefine_D_IM_IIP_REFR0E_BIT			ImIipDefine_D_IM_IIP_REFR0F_BIT
#define	ImIipDefine_D_IM_IIP_REFR1E_BIT			ImIipDefine_D_IM_IIP_REFR1F_BIT
#define	ImIipDefine_D_IM_IIP_REFLTE_BIT			ImIipDefine_D_IM_IIP_REFLTF_BIT

#define	ImIipDefine_D_IM_IIP_TRUE		(1)
#define	ImIipDefine_D_IM_IIP_FALSE		(0)
#define ImIipDefine_IM_IIP_ROUNDUN_8(val)			(((UINT32)(val) + 7) & 0xFFFFFFF8)
#define ImIipDefine_IM_IIP_FIXED_POINT(val)		( (INT32)((DOUBLE)(val) * D_IM_IIP_PARAM_AFN_VAL_1_0) )
#define ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(unitId)		(1ULL << (unitId))

#define	ImIipDefine_D_IM_IIP_UTIL_ORIGIN					(0x00)
#define	ImIipDefine_D_IM_IIP_UTIL_TOPRIGHT					(0x01)
#define	ImIipDefine_D_IM_IIP_UTIL_BOTTOMLEFT				(0x02)
#define	ImIipDefine_D_IM_IIP_UTIL_BOTTOMRIGHT				(0x03)
#define	ImIipDefine_D_IM_IIP_UNITPARAM_BASEADDR		(0x10000)
#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_ERROR	(0x000)

#define ImIipDefine_D_IM_IIP_NUM_CPU_CORES			(4)
#define ImIipDefine_D_IM_IIP_RECURSIVE_COUNT_MAX	(0xFFFFFFFF)
#define ImIipDefine_D_IM_IIP_SRAM_WAIT_USEC			(1)

#define	ImIipDefine_D_IM_IIP_STOPPED			(2)

#define ImIipDefine_IM_IIP_WAIT_USEC( usec )				Dd_ARM_Wait_ns( (usec) * 1000 )
#define ImIipDefine_IM_IIP_DSB()	Dd_ARM_Dsb_Pou()
#define	ImIipDefine_D_IM_IIP_FLG_USED_BIT_PATTERN		(0x7FFFFFF)
#define	ImIipDefine_D_IM_IIP_SWTRG_STOPPED		(2)
#define ImIipDefine_D_IM_IIP_TRIG_STOP_CHK_RETRY_COUNT	(1000)

// HISTGRAM
#define ImIipDefine_D_IM_IIP_NUM_HISTGRAM		(256)
#define ImIipDefine_D_IM_IIP_HISTGRAM_BYTES		(ImIipDefine_D_IM_IIP_NUM_HISTGRAM *4)

// Maximum value
#define	ImIipDefine_D_IM_IIP_MAX_PIXID			(12)
#define ImIipDefine_D_IM_IIP_MAX_LUTRAM_TYPE	(6)			// A~F
#define ImIipDefine_D_IM_IIP_MAX_LUTRAM_RESOL	(1024)		// 0~1023

#define ImIipDefine_IM_IIP_GET_REG_SIGNED_A( val, reg, type, member )		{ \
			type work = { .word[0] = 0UL }; \
			work.bit.member = -1L; \
			if( ((work.bit.member) == 0xFFFFFFFFUL) || ((reg.bit.member) <= ((work.bit.member) /2)) ) { \
				(val) = reg.bit.member; \
			} \
			else { \
				(val) = -(work.bit.member - reg.bit.member +1); \
			} \
			ImIipDefine_IM_IIP_CHECK_REG_TYPE( (reg), work ); /* The structure type matching check. */ \
		}

#ifdef CO_IIP_DEBUG_PRINT_FUNC
#define ImIipDefine_IM_IIP_PRINT_PCDBG	Ddim_Print
#else
#define ImIipDefine_IM_IIP_PRINT_PCDBG(dmy)
#endif

#ifdef CO_IIP_REG_TYPE_CHECK
#define ImIipDefine_IM_IIP_CHECK_REG_TYPE( dst, src )	(dst) = (src);
#else
#define ImIipDefine_IM_IIP_CHECK_REG_TYPE( dst, src )
#endif

#define ImIipDefine_IM_XXX_GET_REG_SIGNED( val, reg, type, member )		{ \
			type work = { .word = 0UL }; \
			work.bit.member = -1L; \
			if( ((work.bit.member) == 0xFFFFFFFFUL) || ((reg.bit.member) <= ((work.bit.member) /2)) ) { \
				(val) = reg.bit.member; \
			} \
			else { \
				(val) = -(work.bit.member - reg.bit.member +1); \
			} \
			ImIipDefine_IM_IIP_CHECK_REG_TYPE( (reg), work ); /* The structure type matching check. */ \
		}

// Set signed Bit field value from signed variable.
#define ImIipDefine_IM_IIP_SET_REG_SIGNED_A( reg, type, member, val )		\
		{ \
			type work = { .word[0] = 0UL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			ImIipDefine_IM_IIP_CHECK_REG_TYPE( work, (reg) );	/* The structure type matching check. */ \
		}

// Unit Parameter [debug function]
#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_LD		(0x040)
#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_CFL		(0x020)
#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_GPC		(0x01C)
#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_CSC		(0x060)
#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_AFN		(0x070)
#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_FRECT	(0x070)
#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_MON		(0x060)
#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_BLEND	(0x0DC)
#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_SL		(0x3A0)
#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_LUT		(0x0E0)

#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_MFT		(0x020)

#define	ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_FLT		(0x240)

// IZACTL1.bit.TRG
#define	ImIipDefine_D_IM_IIP_STOP				(0)
#define	ImIipDefine_D_IM_IIP_START				(1)

// UNITINFTBL0.bit.SWTRG
#define	ImIipDefine_D_IM_IIP_SWTRG_START		(1)

#define	ImIipDefine_D_IM_IIP_SWTRG_RUNNING		(3)

#define ImIipDefine_IM_IIP_DMD()	Dd_ARM_Dmb_Pou()

typedef struct 				_ImIipDefine ImIipDefine;
typedef struct 				_ImIipDefinePrivate ImIipDefinePrivate;

typedef struct {
	EImIipUnitId	unitId;
	const CHAR*			unitName;
} TImIipDumpUnitName;

typedef struct {
	ULONG				flgBitmask;		// Bitmask of INTIZ0/INTIZ1/INTIZ2.
	ULONG				enaBitmask;		// Bitmask of INTEN0/INTEN1/INTEN2.
	ULONG				intFact;			// Interrupt factor bitmask. (parameter "interrupt_bitmask" of Im_IIP_Set_Interrupt() and im_iip_counter_set_inthandler())
	ULLONG				unitidBitmask;		// PLDUNIT bitmask. (D_IM_IIP_PARAM_PLDUNIT_xxx)
	T_IM_IIP_CALLBACK	callbackFunc;		// Software trigger's Callback function.
} TImIipIntflgTbl;

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
} UImIip64BitMask;

// parameter structure of im_iip_static_calc_timeout()
typedef struct {
	DDIM_USER_TMO		lastWaitTime;		// "waitTime" for next OS serivce call (ex. DDIM_User_Twai_Flg()).
	DDIM_USER_TMO		waitTime;			// "waitTime" parameter of MILB_API functions.
	DDIM_USER_SYSTIM	startTime;			// System time when start MILB_API functions.
	DDIM_USER_SYSTIM	curTime;			// Now System time.
} TImIipTimeout;

typedef struct {
	ULLONG				unitBitmask;						// Using unit bitmask. (parameter "unitidBitmask" of Im_IIP_Open_SWTRG())
	ULONG				pixfmttbl_bitmask;					// Using PIXFMTTBL bitmask. (parameter "pixidBitmask" of Im_IIP_Open_SWTRG())
	ULONG				resBitmask;						// Using resource bitmask. (parameter "openResBitmask" of Im_IIP_Open_SWTRG())
	UINT32				cacheUsers[ImIipStruct_D_IM_IIP_CACHE_MAXNUM];	// Using users count of Image Cache.
} TImIipSwtrgMng;

struct _ImIipDefine {
	KObject parent;

   T_IM_IIP_CALLBACK  gimIipCallback;
};

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

KConstType 		    				im_iip_define_get_type(void);
ImIipDefine*		       			 	im_iip_define_get(void);
ImIipDefine*		       			 	im_iip_define_new(void);

INT32 										im_iip_struct_init( VOID );
INT32 										im_iip_struct_init_unit( const EImIipUnitId unitId );
INT32 										im_iip_struct_open( const INT32 waitTime );
INT32 										im_iip_struct_close( VOID );
INT32 										im_iip_struct_ctrl_base( const TImIipCtrlBase* const cfg );
INT32 										im_iip_sub_ctrl_axi( const EImIipAxiId axi_id, const TIMIipCtrlAxi* const cfg );
INT32 										im_iip_sub_ctrl_axi_all( const TIMIipCtrlAxiAll* const cfg );
INT32 										im_iip_sub_update_padrs( const EImIipUnitId unitId, const ULONG unitParamAddr );
INT32 										im_iip_sub_start( VOID );
INT32 										im_iip_main_stop( const UINT32 stop_type );
INT32 										im_iip_main_get_sl_status( UINT32* const sl_status );
INT32 										im_iip_static_get_unit_param( const EImIipUnitId unitId, ULONG* const p_param_buffer, UINT32* const size );
INT32 										im_iip_set_static_accessenable( const UINT32 resBitmask, const UCHAR permission_flg );
INT32 										im_iip_counter_set_inthandler( const ULONG interrupt_bitmask, const T_IM_IIP_CALLBACK intHandler );
//静态变量库调用函数
INT32 										Im_IIP_LinkStart_SWTRG( const EImIipUnitId unitId, const INT32 swtrg, const UINT32 link_onoff );
INT32 										Im_IIP_Start_SWTRG( const EImIipUnitId unitId, const INT32 swtrg );
extern INT32 						Im_IIP_Set_Interrupt( const ULONG interrupt_bitmask, const UCHAR permission_flg );
extern INT32 						Im_IIP_Set_SLIntLines( const ULONG interrupt_bitmask, const UINT32 trans_lines );
extern INT32 						Im_IIP_Ctrl_PIXFMTTBL( const UINT32 pixid, const TImIipPixfmttbl* const tbl );
extern INT32 						Im_IIP_Ctrl_UNITINFTBL( const TImIipUnitinftbl* const tbl );
extern INT32 						Im_IIP_Ctrl_LUT( const TImIipLut* const lut );
extern INT32 						Im_IIP_Open_SWTRG( const ULLONG unitid_bitmask64, const UINT32 pixidBitmask, const UINT32 openResBitmask, const INT32 waitTime );
extern INT32 						Im_IIP_Close_SWTRG( const ULLONG unitid_bitmask64, const UINT32 pixidBitmask, const UINT32 openResBitmask );
extern INT32 						Im_IIP_Ctrl_SWTRG_Unit( const EImIipUnitId unitId, const TImIipUnitCfg* const p_unitcfg );
extern INT32 						Im_IIP_Wait_End( UINT32* const p_wait_factor, const UINT32 wait_factor, const UINT32 wait_mode, const INT32 waitTime );
extern INT32 						Im_IIP_Int_Handler( VOID );
extern INT32 						Im_IIP_Clear_HISTGRAM( const UINT32 histgram_a_clr_flag, const UINT32 histgram_b_clr_flag, const UINT32 histgram_c_clr_flag, const UINT32 histgram_d_clr_flag );
extern INT32 						Im_IIP_Get_HISTGRAM( ULONG* const buffer_histgram_a, ULONG* const buffer_histgram_b, ULONG* const buffer_histgram_c, ULONG* const buffer_histgram_d );
extern INT32	 					Im_IIP_Get_HISTMAX( UCHAR* const histmax_a, UCHAR* const histmax_b, UCHAR* const histmax_c, UCHAR* const histmax_d );
extern INT32 						Im_IIP_Get_MAXMON( TImIipMaxmon* const mon );
extern INT32 						Im_IIP_Get_MINMON( TImIipMinmon* const mon );
extern INT32 						Im_IIP_Get_ADDMON( TImIipAddmon* const mon );
extern INT32 						Im_IIP_Get_ImgCache_Access_Info( const EImIipCacheCh cache_ch, TImIipAccessInfo* const info );
extern INT32 						Im_IIP_Get_AXI_Status( TImIipAxiStatus* const sts );

//私有函数变成公有函数被调用

UINT32	 									im_iip_static_irq_disable( void );
void 											im_iip_static_irq_enable( ImIipDefine* self, UINT32 irq_mask );
INT32 										im_iip_define_util_resizerotate_main( TImIipUtilParamResizeRotate* const rr_param, const TImIipUtilRr* const cfg );
INT32 										im_iip_counter_check_wait_time(ImIipDefine* self, const INT32 waitTime );
INT32 										im_iip_define_util_csc_main( TImIipUtilParamCsc* const csc_param, const TImIipUtilCsc* const cfg, const INT32 waitTime );
INT32										im_iip_new_util_lut_main( TImIipUtilParamLut* const lut_param, const TImIipUtilLut* const cfg );
INT32 										im_iip_new_util_alpha_main( TImIipUtilParamAlpha* const alp_param, const TImIipUtilAlphablend* const cfg );
VOID 											im_iip_sub_get_unit_param_size(ImIipDefine* self, UINT32* const size, const EImIipUnitId unitId );
VOID											im_iip_counter_on_lipclk( ImIipDefine* self );
VOID 											im_iip_struct_on_lclk( ImIipDefine* self );
VOID 											im_iip_sub_get_regword(  ImIipDefine* self,ULONG* dst, const volatile ULONG* src, const UINT32 bytes );
VOID 											im_iip_struct_off_iclk(  ImIipDefine* self );

VOID 											im_iip_counter_off_lipclk(  ImIipDefine* self  );
VOID 											im_iip_sub_clear_hwen_all( ImIipDefine* self );
VOID 											im_iip_counter_set_acesen0_reg(ImIipDefine* self, volatile TImIipSwtrgMng* const swtrg_mng );
VOID 											im_iip_static_set_unitinftbl_sl(  ImIipDefine* self,const TImIipUnitCfg* const sl_cfg, volatile struct io_iip_uinftbl* const pUNITINFTBL );
VOID 											im_iip_couter_set_unitinftbl( ImIipDefine* self,const TImIipUnitCfg* const cfg, volatile struct io_iip_uinftbl* const pUNITINFTBL );
VOID 											im_iip_sub_fill_word(  ImIipDefine* self,volatile ULONG* dst, const UINT32 start_pos, const UINT32 num, const ULONG fill_value );
VOID 											im_iip_sub_copy_short_to_word( ImIipDefine* self, volatile ULONG* dst, const USHORT* src, const UINT32 bytes );
VOID 											im_iip_counter_update_pixfmttbl( ImIipDefine* self,const UINT32 pixid );
VOID 											im_iip_counter_wait_pftflg(  ImIipDefine* self );
INT32 										im_iip_counter_hunt_unit_and_pix( const UImIip64BitMask unitidBitmask, const UINT32 pixidBitmask, const UINT32 other_bitmask, const UINT32 cache_bitmask );
INT32 										im_iip_counter_twai_pol_sem( const DDIM_USER_ID semid, const DDIM_USER_TMO tmout );
INT32	 									im_iip_static_calc_timeout( TImIipTimeout* const tmout );
VOID 											im_iip_counter_off_izarac_caxrac(  ImIipDefine* self );
INT32 										im_iip_static_twai_pol_flg( const DDIM_USER_ID flagid, const DDIM_USER_FLGPTN waiptn, const DDIM_USER_MODE wfmode, DDIM_USER_FLGPTN* const p_flgptn, const DDIM_USER_TMO tmout );
VOID 											im_iip_counter_on_izarac_caxrac( ImIipDefine* self );

VOID											im_iip_sub_set_pixfmttbl_param( ImIipDefine* self,TImIipPixfmttbl* const pixfmttbl,
									    const TImIipUtilImgGbl* const gbl,
									    const UINT32 pixDepth,
									    const TImIipUtilAlphaInfo* const alpha );

ULONG 									im_iip_sub_util_conv_pixid( const EImIipPixid pixid );
VOID 											im_iip_sub_set_phvsz_1d_sl( ImIipDefine* self,TImIipUtilPhvsz* const phvsz,
								    const TImIipUtilImgInt* const dst );
VOID 											im_iip_sub_set_unitinftbl_param( ImIipDefine* self,TImIipUnitCfg* const unitinftbl_param, const EImIipUnitId id, const VOID* const addr, const ULLONG unitidBitmask );

ULONG 									im_iip_sub_util_conv_portid( const EImIipUnitId unitid );
VOID 											im_iip_define_set_sl_unit_param( ImIipDefine* self,T_IM_IIP_PARAM_STS* const sl,
									  const TImIipUtilPhvsz* const phvsz,
									  const TImIipUtilRectInt* const dst_rect,
									  const TImIipUtilImgGbl* const dst_gbl,
									  const UINT32 pixDepth );
VOID 											im_iip_define_set_1d_unit_param(  ImIipDefine* self,T_IM_IIP_PARAM_1DL* const p1D,
									  const TImIipUtilPhvsz* const phvsz,
									  const TImIipUtilImgInt* const src,
									  const UINT32 pixDepth,
									  const E_IM_IIP_PARAM_CSEL cache_select );

INT32 										im_iip_new_util_exec_rotate( TImIipUtilParamResizeRotate* const rr_param, const TImIipUtilRr* const cfg );
INT32 										im_iip_new_util_exec_csc( TImIipUtilParamCsc* const csc_param, const TImIipUtilCsc* const cfg );

VOID 											im_iip_new_util_set_lut_unit_param( ImIipDefine* self,T_IM_IIP_PARAM_LUT* const lut,
									   const TImIipUtilLut* const cfg );

ULONG	 									im_iip_new_util_conv_portid_1( const EImIipUnitId unitid );
VOID 											im_iip_new_set_axi_param(  ImIipDefine* self,const EImIipUnitId unitid, EImIipAxiId* const axi_id, TIMIipCtrlAxi* const axi_cfg, const UCHAR master_IF );


INT32 										im_iip_counter_unset_interrupt( const UImIip64BitMask unitidBitmask, const UCHAR cause );

volatile struct io_iip_uinftbl* im_iip_sun_get_unitinftbl_regaddr( const EImIipUnitId unitId );
E_IM_IIP_PARAM_PF_PDIST	 	im_iip_sub_get_pf_pdist( const UINT32 pixDepth,
												    const EImIipFtype frameType,
												    const EImIipPfmt pixFormat,
												    const UINT32 alpha );
//————————————————————————————————————————————————

#define im_iip_get_gim_iip(self)          ((self->gimIipCallback))
#define im_iip_set_gim_iip(self,g)        {self->gimIipCallback = g;}

#if 0	// B2Y Link not support

extern INT32 Im_IIP_Set_B2YLinkEnable( const UCHAR b2yLink );

#endif	// B2Y Link not support

INT32 im_iip_static_get_genline( TImIipGenline* const genline );
INT32 im_iip_static_get_debug_monitor( TImIipDebugMonitor* const monitor_val );
INT32 im_iip_static_start_dumpunitreg( const EImIipUnitId unitId );
INT32 im_iip_static_dumpunitreg_byname( const CHAR* const unitName );
INT32 im_iip_static_stop_dumpunitreg( VOID );

#ifdef __cplusplus
}
#endif	// __cplusplus

#ifdef CO_IM_IIP_ENABLE_UTILITY

#include "im_iip_param.h"

#define ImIipDefine_D_IM_IIP_UTIL_RR_BUF_BYTES				(268 +8)	/**< Buffer bytes of IM_IIP_Utility_ResizeRotate() */
#define ImIipDefine_D_IM_IIP_UTIL_CSC_BUF_BYTES				(280 +8)	/**< Buffer bytes of IM_IIP_Utility_CSC() */
#define ImIipDefine_D_IM_IIP_UTIL_LUT_BUF_BYTES				(408 +8)	/**< Buffer bytes of IM_IIP_Utility_LUT() */
#define ImIipDefine_D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES		(352 +8)	/**< Buffer bytes of IM_IIP_Utility_AlphaBlend() */

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

extern INT32 IM_IIP_Utility_ResizeRotate( const TImIipUtilRr* const cfg0,
										  const TImIipUtilRr* const cfg1,
										  const UCHAR paramMasterIf,
										  const ULONG paramBufferAddr,
										  const INT32 waitTime );

extern INT32 IM_IIP_Utility_CSC( const TImIipUtilCsc* const cfg0,
								 const TImIipUtilCsc* const cfg1,
								 const UCHAR paramMasterIf,
								 const ULONG paramBufferAddr,
								 const INT32 waitTime );

extern INT32 IM_IIP_Utility_LUT( const TImIipUtilLut* const cfg,
								 const UCHAR paramMasterIf,
								 const ULONG paramBufferAddr,
								 const INT32 waitTime );

extern INT32 IM_IIP_Utility_AlphaBlend( const TImIipUtilAlphablend* cfg,
										const UCHAR paramMasterIf,
										const ULONG paramBufferAddr,
										const INT32 waitTime );


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// CO_IM_IIP_ENABLE_UTILITY

#endif /* __IM_IIP_DEFINE_H__ */
