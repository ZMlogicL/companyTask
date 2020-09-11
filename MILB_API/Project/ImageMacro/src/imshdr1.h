/*
 * imshdr1.h
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

#ifndef __IM_SHDR1_H__
#define __IM_SHDR1_H__

#include <klib.h>
#include "driver_common.h"

#define IM_TYPE_SHDR1      (im_shdr1_get_type())
#define IM_SHDR1(obj)        (K_TYPE_CHECK_INSTANCE_CAST(obj, ImShdr1))
#define IM_IS_SHDR1(obj)  (K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_SHDR1))

/** SHDR PRE parameter (PREMD) */
typedef struct {
	UCHAR							cus_mode;			/**< Chroma up sampling mode<br>
															<ul>
																<li>@ref D_IM_SHDR_CUS_YCC422_BILINEAR_A
																<li>@ref D_IM_SHDR_CUS_YCC422_BILINEAR_B
																<li>@ref D_IM_SHDR_CUS_YCC422_PADDING
																<li>@ref D_IM_SHDR_CUS_YCC420_BILINEAR_A
																<li>@ref D_IM_SHDR_CUS_YCC420_BILINEAR_B
																<li>@ref D_IM_SHDR_CUS_YCC420_PADDING
															</ul>
														*/
	UCHAR							degamma_mode;		/**< Degamma mode<br>
															<ul>
																<li>@ref D_IM_SHDR_DEGAMMA_LUT
																<li>@ref D_IM_SHDR_DEGAMMA_BITEXP
															</ul>
														*/

} T_IM_SHDR_PRE_PREMD;

/** SHDR PRE parameter (PREY2RCLP) */
typedef struct {
	USHORT							upper_long0[ 3 ];	/**< Upper value R/G/B (long exposure - full image) (16bit).	*/
	USHORT							lower_long0[ 3 ];	/**< Lower value R/G/B (long exposure - full image) (16bit).	*/
	UCHAR							upper_short[ 3 ];	/**< Upper value R/G/B (shrt exposure) (8bit).					*/
	UCHAR							lower_short[ 3 ];	/**< Upper value R/G/B (shrt exposure) (8bit).					*/
} T_IM_SHDR_PRE_PREY2RCLP;

/** SHDR PRE parameter (PRER2YCLP) */
typedef struct {
	USHORT							upper_long_y;		/**< Upper value Y (long exposure) (16bit).			*/
	SHORT							upper_long_c[ 2 ];	/**< Upper value Cb/Cr (long exposure) (16bit).		*/
	USHORT							lower_long_y;		/**< Lower value Y (long exposure) (16bit).			*/
	SHORT							lower_long_c[ 2 ];	/**< Lower value Cb/Cr (long exposure) (16bit).		*/
	USHORT							upper_short_y;		/**< Upper value Y (short exposure) (12bit).		*/
	SHORT							upper_short_c[ 2 ];	/**< Upper value Cb/Cr (short exposure) (12bit).	*/
	USHORT							lower_short_y;		/**< Lower value Y (short exposure) (12bit).		*/
	SHORT							lower_short_c[ 2 ];	/**< Lower value Cb/Cr (short exposure) (12bit).	*/
} T_IM_SHDR_PRE_PRER2YCLP;

/** SHDR PRE parameter (SKN/LKN) */
typedef struct {
	UCHAR							offset[ 3 ];		/**< Offset (8bits).								*/
	UCHAR							slope[ 3 ];			/**< Slope (8bits).									*/
	USHORT							boundary[ 2 ];		/**< Boundary:boundary[0] =< boundary[1] (10bits).	*/
} T_IM_SHDR_PRE_KN;

/** SHDR PRE parameter */
typedef struct {
	T_IM_SHDR_PRE_PREMD				pre_mode;			/**< PREMD    :Chroma Up Sampling/Degamma mode.							*/
	SHORT							y2r_coef[ 9 ];		/**< Y2RCOEF  :Y2R color space conversion coefficient.					*/
	T_IM_SHDR_PRE_PREY2RCLP			y2r_clp;			/**< PREY2RCLP:Y2R conversion clip.										*/
	SHORT							r2y_coef[ 9 ];		/**< R2YCOEF  :R2Y color space conversion coefficient.					*/
	T_IM_SHDR_PRE_PRER2YCLP			r2y_clp;			/**< PRER2YCLP:R2Y conversion clip.										*/
	T_IM_SHDR_PRE_KN				short_knee;			/**< SKN      :Knee setting(Short exposure image).						*/
	T_IM_SHDR_PRE_KN				long_knee;			/**< LKN      :Knee setting(Long exposure image).						*/
} T_IM_SHDR_PRE;


/** SHDR FMD parameter (MVCNT) */
typedef struct {
	UCHAR							bounds;				/**< Bounds (8bit).					*/
	UCHAR							threshold;			/**< Threshold (8bit).				*/
	SHORT							gr;					/**< gr (13bit)						*/
} T_IM_SHDR_FMD_MVCNT;

/** SHDR FMD parameter (WGHTR2YCLP) */
typedef struct {
	UCHAR							upper;				/**< Upper value (8bit).			*/
	UCHAR							lower;				/**< Lower value (8bit).			*/
} T_IM_SHDR_FMD_WGHTR2YCLP;

/** SHDR FMD parameter (PRETH) */
typedef struct {
	UCHAR							md;					/**< Reduced image comparison judgment threshold (8bit).	*/
	UCHAR							y;					/**< Brightness reference threshold (8bit).					*/
} T_IM_SHDR_FMD_PRETH;

/** SHDR FMD parameter (SSMRGCNT) */
typedef struct {
	UCHAR							mode;				/**< Reduction image merge mode<br>
															<ul>
																<li>@ref D_IM_SHDR_OFF
																<li>@ref D_IM_SHDR_ON (use prohibition)
															</ul>
														*/
	UCHAR							threshold;			/**< Reduction image threshold (8bit).	*/
	UCHAR							value;				/**< Reduction image value (8bit).		*/
} T_IM_SHDR_FMD_SSMRGCNT;

/** SHDR FMD parameter */
typedef struct {
	UCHAR							ep_boundary[ 4 ];			/**< EPBD    :Epsilon boundary (8bit) [0]:D.C.				*/
	UCHAR							ep_offset[ 4 ];				/**< EPOF    :Epsilon offset (8bit).						*/
	UCHAR							ep_blend;					/**< EPBLD   :Epsilon blend ratio (3bit).					*/
	UCHAR							fd_weight;					/**< FDWEIGHT:Frame difference weight (5bit).				*/
	T_IM_SHDR_FMD_MVCNT				mvcnt;						/**< MVCNT   :.												*/
	UCHAR							bldr_offset[ 5 ];			/**< BLDROFS :Blend ratio offset (8bit).					*/
	USHORT							bldr_slope[ 5 ];			/**< BLDRSL  :Blend ratio slope (12bit).					*/
	UCHAR							bldr_boundary[ 5 ];			/**< BLDRB   :Blend ratio boundary (8bit) [0]:D.C.			*/
	SHORT							weight_r2y_coef[ 3 ];		/**< WGHTR2YCOEF:Weight R2Y coefficient (15bit).			*/
	T_IM_SHDR_FMD_WGHTR2YCLP		weight_r2y_clp;				/**< WGHTR2YCLP :Weight R2Y clip.							*/
	UCHAR							weight_base;				/**< WGHTBASE   :Weight base<br>
																	<ul>
																		<li>@ref D_IM_SHDR_WGHTBASE_Y
																		<li>@ref D_IM_SHDR_WGHTBASE_RGB
																	</ul>
																*/
	USHORT							weight_offset[ 3 ][ 5 ];	/**< WGHT R/G/B OFS:Weight offset RGB (12bit).				*/
	USHORT							weight_slope[ 3 ][ 5 ];		/**< WGHT R/G/B SL :Weight slope RGB (12bit).				*/
	UCHAR							weight_boundary[ 3 ][ 5 ];	/**< WGHT R/G/B B  :Weight boundary RGB (8bit) [0]:D.C.		*/
	USHORT							iso_threshold;				/**< ISOTH   :Isolated point threshold (9bit).				*/
	UCHAR							iso_coef[ 6 ];				/**< ISOCOEF :Isolated point coefficient (2/2/2/5/5/8 bit).	*/
	UCHAR							sat_threshold;				/**< SATTH   :Saturation threshold (8bit).					*/
	UCHAR							exp77_mode;					/**< EXP77MD :Expansion process mode<br>
																	<ul>
																		<li>@ref D_IM_SHDR_EXP77MD_COEFSUMDIV
																		<li>@ref D_IM_SHDR_EXP77MD_PERIMAXVAL
																	</ul>
																*/
	UCHAR							fmd_sel;					/**< FMDSEL  :FMD output image select<br>
																	<ul>
																		<li>@ref D_IM_SHDR_FMDSEL_EXPANSION
																		<li>@ref D_IM_SHDR_FMDSEL_REDUCTION
																	</ul>
																*/
} T_IM_SHDR_FMD;

/** SHDR PMSK parameter */
typedef struct {
	UCHAR							tlut[ 17 ];			/**< TLUT  :Reliability map conversion LUT (8bit).	*/
	UCHAR							pmsk_mode;			/**< PMSKMD:Pre mask mode<br>
															<ul>
																<li>@ref D_IM_SHDR_PMSKMD_MAX
																<li>@ref D_IM_SHDR_PMSKMD_AVE
															</ul>
														*/
} T_IM_SHDR_PMSK;

/** SHDR SPNR parameter */
typedef struct {
	UCHAR							spnr_en;			/**< SPNREN:SPNR process enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							spe_blend;			/**< SPEBLD:SPE blend ratio (3bit).			*/
	USHORT							spe_boundary[ 4 ];	/**< SPEBD :SPE boundary (12bit) [0]:D.C.	*/
	USHORT							spe_offset[ 4 ];	/**< SPEOF :SPE offset (12bit).				*/
} T_IM_SHDR_SPNR;

/** SHDR MSK parameter */
typedef struct {
	USHORT							y2r_clp_upper_long[ 3 ];	/**< MSKY2RCLPUL:Y2R conversion clip upper R/G/B (long exp) (12bit).	*/
	USHORT							y2r_clp_lower_long[ 3 ];	/**< MSKY2RCLPLL:Y2R conversion clip lower R/G/B (long exp) (12bit).	*/
	USHORT							y2r_clp_upper_short[ 3 ];	/**< MSKY2RCLPUS:Y2R conversion clip upper R/G/B (short exp) (12bit).	*/
	USHORT							y2r_clp_lower_short[ 3 ];	/**< MSKY2RCLPLS:Y2R conversion clip lower R/G/B (short exp) (12bit).	*/
	UCHAR							alpha;						/**< ALPHA      :Average processing weight (6bit) 63=100% short exp.	*/
	UCHAR							lpfc[ 3 ][ 3 ];				/**< LPFC       :Low-pass filter coefficient (8bit).					*/
	UCHAR							blend_offset[ 7 ];			/**< BLDOFS     :Blend offset (8bit).									*/
	USHORT							blend_slope[ 7 ];			/**< BLDSL      :Blend slope (16bit).									*/
	USHORT							blend_boundary[ 7 ];		/**< BLDB       :Blend boundary (12bit) [0]:D.C.<br>
																				 blend_boundary[1] =< [2] =< [3] =< [4] =< [5] =< [6]<br>
																*/
	UCHAR							norm_gain[ 3 ];				/**< NORMGAIN   :Normalization gain R/G/B (8bit).						*/
	UCHAR							norm_offset[ 3 ];			/**< NORMOFS    :Normalization offset R/G/B (8bit).						*/
	UCHAR							msk_mode;					/**< MSKMD      :Mask merge mode<br>
																	<ul>
																		<li>@ref D_IM_SHDR_MSKMD_SHORT
																		<li>@ref D_IM_SHDR_MSKMD_LONG
																		<li>@ref D_IM_SHDR_MSKMD_MSKONLY
																	</ul>
																*/
} T_IM_SHDR_MSK;


typedef struct _ImShdr1  ImShdr1;
typedef struct _ImShdr1Private ImShdr1Private;

struct _ImShdr1 {
KObject parent;
};

KConstType  im_shdr1_get_type(void);
ImShdr1* im_shdr1_new(void);

INT32 Im_SHDR_Set_Pre( const T_IM_SHDR_PRE*  const shdr_pre );
INT32 Im_SHDR_Get_Pre( T_IM_SHDR_PRE* const shdr_pre );
INT32 Im_SHDR_Set_Fmd( const T_IM_SHDR_FMD* const shdr_fmd );
INT32 Im_SHDR_Get_Fmd( T_IM_SHDR_FMD* const shdr_fmd );
INT32 Im_SHDR_Set_PreMask( const T_IM_SHDR_PMSK* const shdr_pmsk );
INT32 Im_SHDR_Get_PreMask( T_IM_SHDR_PMSK* const shdr_pmsk );
INT32 Im_SHDR_Set_Spnr( const T_IM_SHDR_SPNR* const shdr_spnr );
INT32 Im_SHDR_Get_Spnr( T_IM_SHDR_SPNR* const shdr_spnr );
INT32 Im_SHDR_Set_Mask( const T_IM_SHDR_MSK* const shdr_msk );
INT32 Im_SHDR_Get_Mask( T_IM_SHDR_MSK* const shdr_msk );



#endif /* __IM_SHDR1_H__ */
