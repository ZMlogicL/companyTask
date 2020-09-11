/*
 * imshdr3.h
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

#ifndef __IM_SHDR3_H__
#define __IM_SHDR3_H__

#include <klib.h>
#include "driver_common.h"

#define IM_TYPE_SHDR3      (im_shdr3_get_type())
#define IM_SHDR3(obj)        (K_TYPE_CHECK_INSTANCE_CAST(obj, ImShdr3))
#define IM_IS_SHDR3(obj)  (K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_SHDR3))

/** SHDR BLD parameter */
typedef struct {
	UCHAR							blend_sel;			/**< BLDSEL  :Blend select<br>
															<ul>
																<li>@ref D_IM_SHDR_BLDSEL_SHORT_LONG
																<li>@ref D_IM_SHDR_BLDSEL_LONG_SHORT
															</ul>
														*/
	UCHAR							alpha_sel;			/**< ALPHASEL:Alpha value select<br>
															<ul>
																<li>@ref D_IM_SHDR_ALPHASEL_MERGEMASK
																<li>@ref D_IM_SHDR_ALPHASEL_FIXED
															</ul>
														*/
	UCHAR							alpha_val[ 3 ];		/**< ALPHAVAL:Alpha value Y/U/V (8bit).				*/
} T_IM_SHDR_BLD;

/** SHDR POST parameter (PSOTSFT1RND) */
typedef struct {
	UCHAR							sft1rnd_en;			/**< POSTSFT1RNDEN:Random number addition enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
} T_IM_SHDR_POST_PSOTSFT1RND;

/** SHDR POST parameter */
typedef struct {
	T_IM_SHDR_POST_PSOTSFT1RND		sft1rnd;				/**< POSTSFT1RND  :Random number addition setting.								*/
	SHORT							y2r_coef[ 9 ];			/**< POSTY2RCOEF  :Y2R color space conversion coefficient (15bit).				*/
	USHORT							y2r_clp_th_upper[ 3 ];	/**< POSTY2RCLPTHU:Y2R clip upper value R/G/B (16bit).							*/
	USHORT							y2r_clp_th_lower[ 3 ];	/**< POSTY2RCLPTHL:Y2R clip lower value R/G/B (16bit).							*/
	UCHAR							ev_sel;					/**< POSTSEL1     :EV compensation input data<br>
																	<ul>
																		<li>@ref D_IM_SHDR_POSTSEL1_Y
																		<li>@ref D_IM_SHDR_POSTSEL1_RGB
																	</ul>
															*/
	UCHAR							mulqpos;				/**< POSTMULQPOS  :EV compensation multiplication decimal point position<br>
																	<ul>
																		<li>@ref D_IM_SHDR_POSTMULQPOS_Q5
																		<li>@ref D_IM_SHDR_POSTMULQPOS_Q4
																		<li>@ref D_IM_SHDR_POSTMULQPOS_Q3
																		<li>@ref D_IM_SHDR_POSTMULQPOS_Q2
																	</ul>
															*/
	USHORT							ev_kn_boundary[ 10 ];	/**< EVKNB        :EV compensation Knee input data boundary (12bit) [0]:D.C.	*/
	USHORT							ev_kn_offset[ 10 ];		/**< EVKNOFS      :EV compensation Knee offset (14bit).							*/
	SHORT							ev_kn_slope[ 10 ];		/**< EVKNSL       :EV compensation Knee slope (15bit).							*/
	UCHAR							css_sel;				/**< POSTSEL0     :CSS input signal selection<br>
																	<ul>
																		<li>@ref D_IM_SHDR_POSTSEL0_BLEND_YCC16
																		<li>@ref D_IM_SHDR_POSTSEL0_BYPASS_YCC8
																	</ul>
															*/
	UCHAR							hdrcss_mode;			/**< HDRCSSMD     :CSS sampling mode<br>
																	<ul>
																		<li>@ref D_IM_SHDR_HDRCSSMD_YCC422_ODD
																		<li>@ref D_IM_SHDR_HDRCSSMD_YCC422_CENTER
																	</ul>
															*/
} T_IM_SHDR_POST;

/** SHDR resize parameter (Channel mode) */
typedef struct {
	UCHAR							a_w_en;				/**< A:Write enable<br>
															 If you select D_IM_SHDR_OUTCTRL_RGB on SHDROFRM(Output image control),<br>
															 you must set D_IM_SHDR_DISABLE.<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							a_drc_en;			/**< A:Data range enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							a_css_md;			/**< A:CSS mode<br>
															<ul>
																<li>@ref D_IM_SHDR_CSSMD_YCC422
																<li>@ref D_IM_SHDR_CSSMD_YCC420_ODD
																<li>@ref D_IM_SHDR_CSSMD_YCC420_CENTER
															</ul>
														*/
	UCHAR							b_w_en;				/**< B:Write enable<br>
															 If you select D_IM_SHDR_OUTCTRL_RGB on SHDROFRM(Output image control),<br>
															 you must set D_IM_SHDR_DISABLE.<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							b_rdc_md;			/**< B:Reduction mode 1<br>
															<ul>
																<li>@ref D_IM_RDCMD1_1_4
																<li>@ref D_IM_RDCMD1_1_8
																<li>@ref D_IM_RDCMD1_1_32
															</ul>
														*/
	UCHAR							b_css_md;			/**< B:CSS mode<br>
															<ul>
																<li>@ref D_IM_SHDR_CSSMD_YCC422
																<li>@ref D_IM_SHDR_CSSMD_YCC420_ODD
																<li>@ref D_IM_SHDR_CSSMD_YCC420_CENTER
															</ul>
														*/
	UCHAR							c_w_en;				/**< C:Write enable<br>
															 If you select D_IM_SHDR_OUTCTRL_RGB on SHDROFRM(Output image control),<br>
															 you must set D_IM_SHDR_DISABLE.<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							c_rsz_md;			/**< C:Resize mode<br>
															<ul>
																<li>@ref D_IM_RSZMD_ODD0
																<li>@ref D_IM_RSZMD_ODD1
																<li>@ref D_IM_RSZMD_CENTER0
																<li>@ref D_IM_RSZMD_CENTER1
															</ul>
														*/
	UCHAR							c_rdc_en;			/**< C:Reduction enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							c_rdc_md;			/**< C:Reduction mode<br>
															<ul>
																<li>@ref D_IM_RDCMD_1_2
																<li>@ref D_IM_RDCMD_1_4
																<li>@ref D_IM_RDCMD_1_8
															</ul>
														*/
	UCHAR							c_trm_en;			/**< C:Triming enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							c_drc_en;			/**< C:DRC enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							c_css_md;			/**< C:CSS mode<br>
															 If c_rdc_en = D_IM_SHDR_ENABLE, abd c_rdc_md = D_IM_RDCMD_1_8, set other than D_IM_SHDR_CSSMD_YCC420_CENTER<br>
															<ul>
																<li>@ref D_IM_SHDR_CSSMD_YCC422
																<li>@ref D_IM_SHDR_CSSMD_YCC420_ODD
																<li>@ref D_IM_SHDR_CSSMD_YCC420_CENTER
															</ul>
														*/
	UCHAR							d_w_en;				/**< D:Write enable<br>
															 If you select D_IM_SHDR_OUTCTRL_RGB on SHDROFRM(Output image control),<br>
															 you must set D_IM_SHDR_DISABLE.<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							d_rsz_md;			/**< D:Resize mode<br>
															<ul>
																<li>@ref D_IM_RSZMD_ODD0
																<li>@ref D_IM_RSZMD_ODD1
																<li>@ref D_IM_RSZMD_CENTER0
																<li>@ref D_IM_RSZMD_CENTER1
															</ul>
														*/
	UCHAR							d_rdc_en;			/**< D:Reduction enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							d_rdc_md;			/**< D:Reduction mode<br>
															<ul>
																<li>@ref D_IM_RDCMD_1_2
																<li>@ref D_IM_RDCMD_1_4
																<li>@ref D_IM_RDCMD_1_8
															</ul>
														*/
	UCHAR							d_trm_en;			/**< D:Triming enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							d_drc_en;			/**< D:DRC enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							d_css_md;			/**< D:CSS mode<br>
															 If d_rdc_en = D_IM_SHDR_ENABLE, abd d_rdc_md = D_IM_RDCMD_1_8, set other than D_IM_SHDR_CSSMD_YCC420_CENTER.
															<ul>
																<li>@ref D_IM_SHDR_CSSMD_YCC422
																<li>@ref D_IM_SHDR_CSSMD_YCC420_ODD
																<li>@ref D_IM_SHDR_CSSMD_YCC420_CENTER
															</ul>
														*/
	UCHAR							e_w_en;				/**< E:Write enable<br>
															 If you select D_IM_SHDR_OUTCTRL_RGB on SHDROFRM(Output image control),<br>
															 you must set D_IM_SHDR_DISABLE.<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							e_rsz_md;			/**< E:Resize mode<br>
															<ul>
																<li>@ref D_IM_RSZMD_ODD0
																<li>@ref D_IM_RSZMD_ODD1
																<li>@ref D_IM_RSZMD_CENTER0
																<li>@ref D_IM_RSZMD_CENTER1
															</ul>
														*/
	UCHAR							e_rdc_en;			/**< E:Reduction enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							e_rdc_md;			/**< E:Reduction mode<br>
															<ul>
																<li>@ref D_IM_RDCMD_1_2
																<li>@ref D_IM_RDCMD_1_4
																<li>@ref D_IM_RDCMD_1_8
															</ul>
														*/
	UCHAR							e_trm_en;			/**< E:Triming enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							e_css_md;			/**< E:CSS mode<br>
															 If e_rdc_en = D_IM_SHDR_ENABLE, abd e_rdc_md = D_IM_RDCMD_1_8, set other than D_IM_SHDR_CSSMD_YCC420_CENTER<br>
															<ul>
																<li>@ref D_IM_SHDR_CSSMD_YCC422
																<li>@ref D_IM_SHDR_CSSMD_YCC420_ODD
																<li>@ref D_IM_SHDR_CSSMD_YCC420_CENTER
															</ul>
														*/
	UCHAR							f_w_en;				/**< F:Write enable<br>
															 If you select D_IM_SHDR_OUTCTRL_RGB on SHDROFRM(Output image control),<br>
															 you must set D_IM_SHDR_DISABLE.<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							f_rsz_md;			/**< F:Resize mode<br>
															<ul>
																<li>@ref D_IM_RSZMD_ODD0
																<li>@ref D_IM_RSZMD_ODD1
																<li>@ref D_IM_RSZMD_CENTER0
																<li>@ref D_IM_RSZMD_CENTER1
															</ul>
														*/
	UCHAR							f_rdc_en;			/**< F:Reduction enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							f_rdc_md;			/**< F:Reduction mode<br>
															<ul>
																<li>@ref D_IM_RDCMD_1_2
																<li>@ref D_IM_RDCMD_1_4
																<li>@ref D_IM_RDCMD_1_8
															</ul>
														*/
	UCHAR							f_trm_en;			/**< F:Triming enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							f_css_md;			/**< F:CSS mode<br>
															 If f_rdc_en = D_IM_SHDR_ENABLE, abd f_rdc_md = D_IM_RDCMD_1_8, set other than D_IM_SHDR_CSSMD_YCC420_CENTER<br>
															<ul>
																<li>@ref D_IM_SHDR_CSSMD_YCC422
																<li>@ref D_IM_SHDR_CSSMD_YCC420_ODD
																<li>@ref D_IM_SHDR_CSSMD_YCC420_CENTER
															</ul>
														*/
} T_IM_SHDR_RESIZE_CHMODE;

/** SHDR resize parameter (WOUTSZ) */
typedef struct {
	USHORT							a_hsize;			/**< A:Horizontal size (14bits unit 2pixel, 512~11880).	*/
	USHORT							a_vsize;			/**< A:Vertical size   (14bits unit 8pixel, 384~8800).	*/
	USHORT							b_hsize;			/**< B:Horizontal size (14bits unit 2pixel, 16~2970).	*/
	USHORT							b_vsize;			/**< B:Vertical size   (14bits unit 2pixel, 12~2200).	*/
	USHORT							c_hsize;			/**< C:Horizontal size (14bits unit 2pixel, 32~11880).	*/
	USHORT							c_vsize;			/**< C:Vertical size   (14bits unit 2pixel, 24~8800).	*/
	USHORT							d_hsize;			/**< D:Horizontal size (14bits unit 2pixel, 32~11880).	*/
	USHORT							d_vsize;			/**< D:Vertical size   (14bits unit 2pixel, 24~8800).	*/
	USHORT							e_hsize;			/**< E:Horizontal size (14bits unit 2pixel, 32~11880).	*/
	USHORT							e_vsize;			/**< E:Vertical size   (14bits unit 2pixel, 24~8800).	*/
	USHORT							f_hsize;			/**< F:Horizontal size (14bits unit 2pixel, 32~11880).	*/
	USHORT							f_vsize;			/**< F:Vertical size   (14bits unit 2pixel, 24~8800).	*/
} T_IM_SHDR_RESIZE_WOUTSZ;

/** SHDR resize parameter (RSZHCNT) */
typedef struct {
	USHORT							c_hsta;				/**< C:Horizontal start position (14bits, 0~16383).						*/
	USHORT							c_hpit;				/**< C:Horizontal pitch size     (15bits, 16384/16384 ~ 32767/16384).	*/
	USHORT							d_hsta;				/**< D:Horizontal start position (14bits, 0~16383).						*/
	USHORT							d_hpit;				/**< D:Horizontal pitch size     (15bits, 16384/16384 ~ 32767/16384).	*/
	USHORT							e_hsta;				/**< E:Horizontal start position (14bits, 0~16383).						*/
	USHORT							e_hpit;				/**< E:Horizontal pitch size     (15bits, 16384/16384 ~ 32767/16384).	*/
	USHORT							f_hsta;				/**< F:Horizontal start position (14bits, 0~16383).						*/
	USHORT							f_hpit;				/**< F:Horizontal pitch size     (15bits, 16384/16384 ~ 32767/16384).	*/
} T_IM_SHDR_RESIZE_RSZHCNT;

/** SHDR resize parameter (RSZVCNT) */
typedef struct {
	USHORT							c_vsta;				/**< C:Vertical start position (14bits 0~16383).						*/
	USHORT							c_vpit;				/**< C:Vertical pitch size     (15bits, 16384/16384 ~ 32767/16384).		*/
	USHORT							d_vsta;				/**< D:Vertical start position (14bits 0~16383).						*/
	USHORT							d_vpit;				/**< D:Vertical pitch size     (15bits, 16384/16384 ~ 32767/16384).		*/
	USHORT							e_vsta;				/**< E:Vertical start position (14bits 0~16383).						*/
	USHORT							e_vpit;				/**< E:Vertical pitch size     (15bits, 16384/16384 ~ 32767/16384).		*/
	USHORT							f_vsta;				/**< F:Vertical start position (14bits  0~16383).						*/
	USHORT							f_vpit;				/**< F:Vertical pitch size     (15bits, 16384/16384 ~ 32767/16384).		*/
} T_IM_SHDR_RESIZE_RSZVCNT;

/** SHDR resize parameter (TRMSTA) */
typedef struct {
	USHORT							c_hsta;				/**< C:Horizontal start position (14bits unit 2pixel, 0~11846).	*/
	USHORT							c_vsta;				/**< C:Vertical start position   (15bits unit 2pixel, 0~8774).	*/
	USHORT							d_hsta;				/**< D:Horizontal start position (14bits unit 2pixel, 0~11846).	*/
	USHORT							d_vsta;				/**< D:Vertical start position   (15bits unit 2pixel, 0~8774).	*/
	USHORT							e_hsta;				/**< E:Horizontal start position (14bits unit 2pixel, 0~11846).	*/
	USHORT							e_vsta;				/**< E:Vertical start position   (15bits unit 2pixel, 0~8774).	*/
	USHORT							f_hsta;				/**< F:Horizontal start position (14bits unit 2pixel, 0~11846).	*/
	USHORT							f_vsta;				/**< F:Vertical start position   (15bits unit 2pixel, 0~8774).	*/
} T_IM_SHDR_RESIZE_TRMSTA;

/** SHDR resize parameter (DRCOFST) */
typedef struct {
	UCHAR							a_y;				/**< A:Data range compression offset Y  (5bits).	*/
	INT8							a_cb;				/**< A:Data range compression offset Cr (5bits).	*/
	INT8							a_cr;				/**< A:Data range compression offset Cb (5bits).	*/
	UCHAR							c_y;				/**< C:Data range compression offset Y  (5bits).	*/
	INT8							c_cb;				/**< C:Data range compression offset Cr (5bits).	*/
	INT8							c_cr;				/**< C:Data range compression offset Cb (5bits).	*/
	UCHAR							d_y;				/**< D:Data range compression offset Y  (5bits).	*/
	INT8							d_cb;				/**< D:Data range compression offset Cr (5bits).	*/
	INT8							d_cr;				/**< D:Data range compression offset Cb (5bits).	*/
} T_IM_SHDR_RESIZE_DRCOFST;

/** SHDR resize parameter (DRCGAIN) */
typedef struct {
	USHORT							a_y;				/**< A:Data range compression gain Y  (9bits).		*/
	UCHAR							a_cb;				/**< A:Data range compression gain Cr (8bits).		*/
	UCHAR							a_cr;				/**< A:Data range compression gain Cb (8bits).		*/
	USHORT							c_y;				/**< C:Data range compression gain Y  (9bits).		*/
	UCHAR							c_cb;				/**< C:Data range compression gain Cr (8bits).		*/
	UCHAR							c_cr;				/**< C:Data range compression gain Cb (8bits).		*/
	USHORT							d_y;				/**< D:Data range compression gain Y  (9bits).		*/
	UCHAR							d_cb;				/**< D:Data range compression gain Cr (8bits).		*/
	UCHAR							d_cr;				/**< D:Data range compression gain Cb (8bits).		*/
} T_IM_SHDR_RESIZE_DRCGAIN;

/** SHDR resize parameter (DRCCLPH) */
typedef struct {
	UCHAR							a_y;				/**< A:Data range compression clip high Y  (8bits).	*/
	INT8							a_cb;				/**< A:Data range compression clip high Cr (8bits).	*/
	INT8							a_cr;				/**< A:Data range compression clip high Cb (8bits).	*/
	UCHAR							c_y;				/**< C:Data range compression clip high Y. (8bits)	*/
	INT8							c_cb;				/**< C:Data range compression clip high Cr (8bits).	*/
	INT8							c_cr;				/**< C:Data range compression clip high Cb (8bits).	*/
	UCHAR							d_y;				/**< D:Data range compression clip high Y  (8bits).	*/
	INT8							d_cb;				/**< D:Data range compression clip high Cr (8bits).	*/
	INT8							d_cr;				/**< D:Data range compression clip high Cb (8bits).	*/
} T_IM_SHDR_RESIZE_DRCCLPH;

/** SHDR resize parameter (DRCCLPL) */
typedef struct {
	UCHAR							a_y;				/**< A:Data range compression clip low Y  (8bits).	*/
	INT8							a_cb;				/**< A:Data range compression clip low Cr (8bits).	*/
	INT8							a_cr;				/**< A:Data range compression clip low Cb (8bits).	*/
	UCHAR							c_y;				/**< C:Data range compression clip low Y  (8bits).	*/
	INT8							c_cb;				/**< C:Data range compression clip low Cr (8bits).	*/
	INT8							c_cr;				/**< C:Data range compression clip low Cb (8bits).	*/
	UCHAR							d_y;				/**< D:Data range compression clip low Y  (8bits).	*/
	INT8							d_cb;				/**< D:Data range compression clip low Cr (8bits).	*/
	INT8							d_cr;				/**< D:Data range compression clip low Cb (8bits).	*/
} T_IM_SHDR_RESIZE_DRCCLPL;


/** SHDR resize parameter */
typedef struct {
	T_IM_SHDR_RESIZE_CHMODE			chmode;				/**< CHMODE :Channel mode.							*/
	T_IM_SHDR_RESIZE_WOUTSZ			woutsz;				/**< WOUTSZ :Output image size.						*/
	T_IM_SHDR_RESIZE_RSZHCNT		rszhcnt;			/**< RSZHCNT:Bilinear interpolation (Horizontal).	*/
	T_IM_SHDR_RESIZE_RSZVCNT		rszvcnt;			/**< RSZVCNT:Bilinear interpolation (Vertical).		*/
	T_IM_SHDR_RESIZE_TRMSTA			trmsta;				/**< TRMSTA :Triming start position.				*/
	T_IM_SHDR_RESIZE_DRCOFST		drcofst;			/**< DRCOFST:Data range compression offset.			*/
	T_IM_SHDR_RESIZE_DRCGAIN		drcgain;			/**< DRCGAIN:Data range compression gain.			*/
	T_IM_SHDR_RESIZE_DRCCLPH		drcclph;			/**< DRCCLPH:Data range compression clip high.		*/
	T_IM_SHDR_RESIZE_DRCCLPL		drcclpl;			/**< DRCCLPL:Data range compression clip low.		*/
} T_IM_SHDR_RESIZE;

/** SHDR SMC parameter (MCARMD) */
typedef struct {
	UCHAR							mca_mode;			/**< Average MC mode<br>
															<ul>
																<li>@ref D_IM_MCAMD_MAX
																<li>@ref D_IM_MCAMD_NR_EFFECT
																<li>@ref D_IM_MCAMD_MAX_VECTOR
																<li>@ref D_IM_MCAMD_MAX_MIN_VECTOR
															</ul>
														*/
	UCHAR							mcr_mode;			/**< Low confidence MC mode<br>
															<ul>
																<li>@ref D_IM_MCRMD_STANDARD
																<li>@ref D_IM_MCRMD_AVERAGE
																<li>@ref D_IM_MCRMD_MC
															</ul>
														*/
} T_IM_SHDR_SMC_MCARMD;

/** SHDR SMC parameter (MCMPMD) */
typedef struct {
	UCHAR							mcmp_mode;			/**< Reliability MAP output mode<br>
															<ul>
																<li>@ref D_IM_SHDR_OFF
																<li>@ref D_IM_SHDR_ON
															</ul>
														*/
	UCHAR							mvw_en;				/**< MVW enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
} T_IM_SHDR_SMC_MCMPMD;

/** SHDR SMC parameter (MMVVAL) */
typedef struct {
	UCHAR							mmv_x;				/**< Fast determination threshold(x) (7bits, 0~64).	*/
	UCHAR							mmv_y;				/**< Fast determination threshold(y) (7bits, 0~48).	*/
} T_IM_SHDR_SMC_MMVVAL;

/** SHDR SMC parameter (MMVRCNT) */
typedef struct {
	UCHAR							mmvro_x;			/**< Reliability reduction(x) (5bits, 0~16).		*/
	UCHAR							mmvro_y;			/**< Reliability reduction(y) (5bits, 0~16).		*/
	UCHAR							mmvrk_x;			/**< Smooth coefficient(x) (3bits, 0~6).			*/
	UCHAR							mmvrk_y;			/**< Smooth coefficient(y) (3bits, 0~6).			*/
} T_IM_SHDR_SMC_MMVRCNT;

/** SHDR SMC parameter (MDBCNT) */
typedef struct {
	UCHAR							mdb_x;				/**< Reference range(x) (3bits, 0~5).				*/
	UCHAR							mdb_y;				/**< Reference range(y) (3bits, 0~3).				*/
} T_IM_SHDR_SMC_MDBCNT;

/** SHDR SMC parameter (MDBROCNT) */
typedef struct {
	UCHAR							mdbro_x;			/**< Weight of the distant area reference(x) (5bits, 0~16).	*/
	UCHAR							mdbro_y;			/**< Weight of the distant area reference(y) (5bits, 0~16).	*/
	UCHAR							mdbrk_x;			/**< Smooth coefficient(x) (3bits, 0~4).					*/
	UCHAR							mdbrk_y;			/**< Smooth coefficient(y) (3bits, 0~3).					*/
} T_IM_SHDR_SMC_MDBROCNT;

/** SHDR SMC parameter (MOLRCNT) */
typedef struct {
	UCHAR							molr_sm;			/**< Occlusion determination threshold(main) (4bits).	*/
	UCHAR							molr_ss;			/**< Occlusion determination threshold(sub) (4bits).	*/
	UCHAR							molr_o;				/**< Reliability reduction (5bits, 0~16)				*/
	UCHAR							molr_k;				/**< Smooth cofficient (2bits, 0~2).					*/
} T_IM_SHDR_SMC_MOLRCNT;

/** SHDR SMC parameter (MCPCNT) */
typedef struct {
	UCHAR							mcpx_s;				/**< Decision threshold (8bits, 0~128).		*/
	UCHAR							mcpx_o;				/**< Reliability reduction (5bits, 0~16).	*/
	UCHAR							mcpx_k;				/**< Smooth coefficient (3bits, 0~6).		*/
} T_IM_SHDR_SMC_MCPCNT;

/** SHDR SMC parameter (MMCRCNT) */
typedef struct {
	USHORT							mmcr_s;				/**< Decision threshold (10bits, 0~765).	*/
	UCHAR							mmcr_k;				/**< Smooth coefficient (3bits, 0~6).		*/
} T_IM_SHDR_SMC_MMCRCNT;

/** SHDR SMC parameter (MOLECNT) */
typedef struct {
	USHORT							mole_s;				/**< Decision threshold (10bits, 0~765).	*/
	UCHAR							mole_o;				/**< Reliability reduction (5bits, 0~16).	*/
	UCHAR							mole_k;				/**< Smooth coefficient (3bits, 0~6).		*/
} T_IM_SHDR_SMC_MOLECNT;

/** SHDR SMC parameter (MMVECNT) */
typedef struct {
	USHORT							mmve_s;				/**< Decision threshold (10bits, 0~765).	*/
	UCHAR							mmve_o;				/**< Reliability reduction (5bits, 0~16).	*/
	UCHAR							mmve_k;				/**< Smooth coefficient (3bits, 0~6).		*/
} T_IM_SHDR_SMC_MMVECNT;

/** SHDR SMC parameter (MCPXECNT) */
typedef struct {
	USHORT							mcpxe_s;			/**< Decision threshold (10bits, 0~765).	*/
	UCHAR							mcpxe_o;			/**< Reliability reduction (5bits, 0~16).	*/
	UCHAR							mcpxe_k;			/**< Smooth coefficient (3bits, 0~6).		*/
} T_IM_SHDR_SMC_MCPXECNT;

/** SHDR SMC parameter (MVLCNT) */
typedef struct {
	UCHAR							mvl_en;					/**< Vector accuracy improvement process enable<br>
																<ul>
																	<li>@ref D_IM_SHDR_DISABLE
																	<li>@ref D_IM_SHDR_ENABLE
																</ul>
															*/
	UCHAR							mvl_threshold;			/**< Reference decision threshold (7bits, 0~64).	*/
	UCHAR							mvl_count_threshold;	/**< Count threshold (7bits, 0~127)					*/
} T_IM_SHDR_SMC_MVLCNT;

/** SHDR SMC parameter */
typedef struct {
	T_IM_SHDR_SMC_MCARMD			mcarmd;				/**< MCARMD  :MC mode.							*/
	T_IM_SHDR_SMC_MCMPMD			mcmpmd;				/**< MCMPMD  :MC map output mode.				*/
	T_IM_SHDR_SMC_MMVVAL			mmvval;				/**< MMVVAL  :Fast determination threshold.		*/
	T_IM_SHDR_SMC_MMVRCNT			mmvrcnt;			/**< MMVRCNT :Reliability reduction.			*/
	T_IM_SHDR_SMC_MDBCNT			mdbcnt;				/**< MDBCNT  :Vector MAX value determination.	*/
	T_IM_SHDR_SMC_MDBROCNT			mdbrocnt;			/**< MDBROCNT:Distant area reference.			*/
	T_IM_SHDR_SMC_MOLRCNT			molrcnt;			/**< MOLRCNT :Occlusion detection.				*/
	T_IM_SHDR_SMC_MCPCNT			mcpcnt;				/**< MCPCNT  :Complex movement control.			*/
	T_IM_SHDR_SMC_MMCRCNT			mmcrcnt;			/**< MMCRCNT :Local afterimage.					*/
	T_IM_SHDR_SMC_MOLECNT			molecnt;			/**< MOLECNT :Occlusion reliability.			*/
	T_IM_SHDR_SMC_MMVECNT			mmvecnt;			/**< MMVECNT :Fast decision result.				*/
	T_IM_SHDR_SMC_MCPXECNT			mcpxecnt;			/**< MCPXECNT:Complex movement result.			*/
	T_IM_SHDR_SMC_MVLCNT			mvlcnt;				/**< MVLCNT  :Vector smoothing.					*/
} T_IM_SHDR_SMC;


typedef struct _ImShdr3  ImShdr3;
typedef struct _ImShdr3Private ImShdr3Private;

struct _ImShdr3 {
KObject parent;
};

KConstType  im_shdr3_get_type(void);
ImShdr3* im_shdr3_new(void);

INT32 Im_SHDR_Set_Blend( const T_IM_SHDR_BLD* const shdr_bld );
INT32 Im_SHDR_Get_Blend( T_IM_SHDR_BLD* const shdr_bld );
INT32 Im_SHDR_Set_Post( const T_IM_SHDR_POST* const shdr_post );
INT32 Im_SHDR_Get_Post( T_IM_SHDR_POST* const shdr_post );
INT32 Im_SHDR_Set_Resize( const T_IM_SHDR_RESIZE* const shdr_resize );
INT32 Im_SHDR_Get_Resize( T_IM_SHDR_RESIZE* const shdr_resize );
INT32 Im_SHDR_Set_Smc( const T_IM_SHDR_SMC* const shdr_smc );
INT32 Im_SHDR_Get_Smc( T_IM_SHDR_SMC* const shdr_smc );



#endif /* __IM_SHDR3_H__ */
