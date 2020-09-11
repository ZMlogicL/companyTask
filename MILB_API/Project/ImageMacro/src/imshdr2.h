/*
 * imshdr2.h
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

#ifndef __IM_SHDR2_H__
#define __IM_SHDR2_H__

#include <klib.h>
#include "driver_common.h"

#define IM_TYPE_SHDR2      (im_shdr2_get_type())
#define IM_SHDR2(obj)        (K_TYPE_CHECK_INSTANCE_CAST(obj, ImShdr2))
#define IM_IS_SHDR2(obj)  (K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_SHDR2))

/** User callback function pointer(Frame complete) */
typedef VOID (*T_IM_SHDR_CALLBACK)( ULONG interrupt_flag_mask );

/** User callback function pointer(Line complete) */
typedef VOID (*T_IM_SHDR_LINEINT_CALLBACK)( ULONG interrupt_flag_mask );

/** SHDR image setting parameter */
typedef struct {
	UCHAR							in_bit_depth;		/**< SHDRIFRM:Input image bit depth<br>
															<ul>
																<li>@ref D_IM_SHDR_INBITDEPTH_8
																<li>@ref D_IM_SHDR_INBITDEPTH_16
															</ul>
														*/
	UCHAR							in_c_fmt;			/**< SHDRIFRM:Input CbCr image format<br>
															 If you use 16bit image, you must set D_IM_SHDR_INCFMT_422SP.<br>
															<ul>
																<li>@ref D_IM_SHDR_INCFMT_420SP
																<li>@ref D_IM_SHDR_INCFMT_422SP
															</ul>
														*/
	UCHAR							in_edge_cpy;		/**< SHDRIFRM:Input image edge copy<br>
															 If you select D_IM_SHDR_SHDRIN_SMCOUT_REF on BRSEL(SHDR input select),<br>
															 you must set D_IM_SHDR_OFF.<br>
															<ul>
																<li>@ref D_IM_SHDR_OFF
																<li>@ref D_IM_SHDR_ON
															</ul>
														*/
	UCHAR							in_edge_cut;		/**< SHDRIFRM:Input image edge cut<br>
															 If you use a 1/32 reduct image, you must set D_IM_SHDR_OFF.<br>
															 Other than Bypass mode, you must set a value same as in_edge_cpy.<br>
															<ul>
																<li>@ref D_IM_SHDR_OFF
																<li>@ref D_IM_SHDR_ON
															</ul>
														*/
	UCHAR							out_ctrl;			/**< SHDROFRM:Output image control<br>
															<ul>
																<li>@ref D_IM_SHDR_OUTCTRL_YCC
																<li>@ref D_IM_SHDR_OUTCTRL_RGB
															</ul>
														*/
	UCHAR							out_sel;			/**< SHDROFRM:Output image select<br>
															 You must set a value same as SHDROFRM(Output image control).<br>
															<ul>
																<li>@ref D_IM_SHDR_OUTSEL_YCC_16
																<li>@ref D_IM_SHDR_OUTSEL_RGB_16
															</ul>
														*/
	UCHAR							out_sel_en;			/**< SHDROFRM:Output image select enable<br>
															<ul>
																<li>@ref D_IM_SHDR_OFF
																<li>@ref D_IM_SHDR_ON
															</ul>
														*/
} T_IM_SHDR_CTRL_IMAGE_SET;

/** SHDR image mode parameter.
*/
typedef struct {
	USHORT							exp_mag;			/**< EXMAG :Exposure magnification (14bits, Unit 1/256, 1~16383).	*/
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	UCHAR							fil_margin;			/**< MRGN  :Filter margin<br>
															If you use a 1/32 reduct image, you must set D_IM_SHDR_FLITER_MARGIN_96.<br>
															<ul>
																<li>@ref D_IM_SHDR_FLITER_MARGIN_16
																<li>@ref D_IM_SHDR_FLITER_MARGIN_32
																<li>@ref D_IM_SHDR_FLITER_MARGIN_96
															</ul>
														*/
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	UCHAR							fil_margin;			/**< MRGN  :Filter margin<br>
															<ul>
																<li>@ref D_IM_SHDR_FLITER_MARGIN_16
																<li>@ref D_IM_SHDR_FLITER_MARGIN_32
															</ul>
														*/
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	INT8							rexp_mag_shift;		/**< REMVAL.REMSFT:Reciprocal of the exposure magnification shift (4bits, -8~5).					*/
	ULONG							rexp_mag;			/**< REMVAL.REXMAG:Reciprocal of the exposure magnification(significant digits) (17bits 0~65536).	*/
	SHORT							shift_x;			/**< SHIFT.SHIFTX :Alignment shift X (13bits, Unit 2pixel, -4096~4094).<br>
															 If you select D_IM_SHDR_OFF on in_edge_cpy, you must set 0.
														*/
	SHORT							shift_y;			/**< SHIFT.SHIFTY :Alignment shift Y (13bits, Unit 2pixel, -4096~4094).<br>
															 If you select D_IM_SHDR_OFF on in_edge_cpy, you must set 0.
														*/
	UCHAR							fmd_en;				/**< FLWCNT.FMDEN :FMC enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							bypass_en;			/**< FLWCNT.BPEN  :Bypass enable<br>
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							smc_in;				/**< FLWCNT.SMCIN :SMC input select<br>
															<ul>
																<li>@ref D_IM_SHDR_SMCIN_STN_REF
																<li>@ref D_IM_SHDR_SMCIN_EXT_STN
																<li>@ref D_IM_SHDR_SMCIN_EXT_REF
															</ul>
														*/
	UCHAR							shdr_in;			/**< FLWCNT.BRSEL :SHDR input select<br>
															<ul>
																<li>@ref D_IM_SHDR_SHDRIN_STN_REF
																<li>@ref D_IM_SHDR_SHDRIN_STN_SMCOUT
																<li>@ref D_IM_SHDR_SHDRIN_SMCOUT_REF
															</ul>
														*/
	UCHAR							tile_size;			/**< TMODE:Tile size select<br>
															<ul>
																<li>@ref D_IM_SHDR_TILESIZE_1024x1024
																<li>@ref D_IM_SHDR_TILESIZE_1024x512
															</ul>
														*/
} T_IM_SHDR_CTRL_IMAGE_MODE;

/** SHDR SDRAM parameter (SDRR_ADDR) */
typedef struct {
	ULONG							a_y;				/**< A:Reference image Y (32bits, unit byte).			*/
	ULONG							a_c;				/**< A:Reference image C (32bits, unit byte).			*/
	ULONG							b_y;				/**< B:SMC merge image Y (32bits, unit byte).			*/
	ULONG							b_c;				/**< B:SMC merge image C (32bits, unit byte).			*/
	ULONG							c_y;				/**< C:Long exp reduct image Y (32bits, unit byte).		*/
	ULONG							c_c;				/**< C:Long exp reduct image C (32bits, unit byte).		*/
	ULONG							d_y;				/**< D:Short exp reduct image Y (32bits, unit byte).	*/
	ULONG							d_c;				/**< D:Short exp reduct image C (32bits, unit byte).	*/
	ULONG							e_y;				/**< E:Reserve.											*/
	ULONG							e_c;				/**< E:Reserve.											*/
	ULONG							f;					/**< F:Reserve.											*/
} T_IM_SHDR_CTRL_SDRAM_ADDR_R;

/** SHDR SDRAM parameter (SDRR_GHSIZE) */
typedef struct {
	USHORT							a_y;				/**< A:Reference image Y (16bits unit 8byte, 8~FFF8h).			*/
	USHORT							a_c;				/**< A:Reference image C (16bits unit 8byte, 8~FFF8h).			*/
	USHORT							b_y;				/**< B:SMC merge image Y (16bits unit 8byte, 8~FFF8h).			*/
	USHORT							b_c;				/**< B:SMC merge image C (16bits unit 8byte, 8~FFF8h).			*/
	USHORT							c_y;				/**< C:Long exp reduct image Y (16bits unit 8byte, 8~FFF8h).	*/
	USHORT							c_c;				/**< C:Long exp reduct image C (16bits unit 8byte, 8~FFF8h).	*/
	USHORT							d_y;				/**< D:Short exp reduct image Y (16bits unit 8byte, 8~FFF8h).	*/
	USHORT							d_c;				/**< D:Short exp reduct image C (16bits unit 8byte, 8~FFF8h).	*/
	USHORT							e_y;				/**< E:Reserve.													*/
	USHORT							e_c;				/**< E:Reserve.													*/
	USHORT							f;					/**< F:Reserve.													*/
} T_IM_SHDR_CTRL_SDRAM_GHSIZE_R;

/** SHDR SDRAM parameter (SDRR_HSIZE) */
typedef struct {
	USHORT							a;					/**< A:Rference image (14bits unit 2pixel, Full image:128~11992, Reduct image:4~376).			*/
	USHORT							b;					/**< B:SMC merge image (14bits unit 2pixel, Full image:128~11992, Reduct image:4~376).			*/
	USHORT							c;					/**< C:Long exp reduct image (14bits unit 2pixel, Full image:128~11992, Reduct image:4~376).	*/
	USHORT							d;					/**< D:Short exp reduct image (14bits unit 2pixel, Full image:128~11992, Reduct image:4~376).	*/
	USHORT							e;					/**< E:same A.																					*/
} T_IM_SHDR_CTRL_SDRAM_HSIZE_R;

/** SHDR SDRAM parameter (SDRR_VSIZE) */
typedef struct {
	USHORT							a;					/**< A:Reference image (14bits unit 2pixel, Full image:72~8992, Reduct image:4~282).			*/
	USHORT							b;					/**< B:SMC merge image (14bits unit 2pixel, Full image:72~8992, Reduct image:4~282).			*/
	USHORT							c;					/**< C:Long exp reduct image (14bits unit 2pixel, Full image:72~8992, Reduct image:4~282).		*/
	USHORT							d;					/**< D:Short exp reduct image (14bits unit 2pixel, Full image:72~8992, Reduct image:4~282).		*/
	USHORT							e;					/**< E:same A.																					*/
} T_IM_SHDR_CTRL_SDRAM_VSIZE_R;

/** SHDR SDRAM parameter (SDRR_VFM) */
typedef struct {
	UCHAR							a;					/**< A:Reference image<br>
															<ul>
																<li>@ref D_IM_SHDR_VFMT_RASTER
																<li>@ref D_IM_SHDR_VFMT_VIDEO
															</ul>
														*/
} T_IM_SHDR_CTRL_SDRAM_VFM_R;

/** SHDR SDRAM parameter (SDWR_ADDR) */
typedef struct {
	ULONG							b_y;				/**< B:1/32 reduction image Y (32bits, unit 8byte).			*/
	ULONG							b_c;				/**< B:1/32 reduction image C (32bits, unit 8byte).			*/
	ULONG							e_y;				/**< E:Resize image #5 Y (32bits, unit 8byte).				*/
	ULONG							e_c;				/**< E:Resize image #5 C (32bits, unit 8byte).				*/
	ULONG							f_y;				/**< F:Resize image #6 Y (32bits, unit 8byte).				*/
	ULONG							f_c;				/**< F:Resize image #6 C (32bits, unit 8byte).				*/
	ULONG							g_r_y;				/**< G:SHDR output image R/Y (32bits, unit 8byte).			*/
	ULONG							g_g_c;				/**< G:SHDR output image G/C (32bits, unit 8byte).			*/
	ULONG							g_b;				/**< G:SHDR output image B (32bits, unit 8byte).			*/
	ULONG							h_x;				/**< H:Output motion vector image X (32bits, unit 8byte).	*/
	ULONG							h_y;				/**< H:Output motion vector image Y (32bits, unit 8byte).	*/
	ULONG							i;					/**< I:Reserve.												*/
} T_IM_SHDR_CTRL_SDRAM_ADDR_W;

/** SHDR SDRAM parameter (SDWR_GHSIZE) */
typedef struct {
	USHORT							b_y;				/**< B:1/32 reduction image Y (16bits, unit 8byte).			*/
	USHORT							b_c;				/**< B:1/32 reduction image C (16bits, unit 8byte).			*/
	USHORT							e_y;				/**< E:Resize image #5 Y (16bits, unit 8byte).				*/
	USHORT							e_c;				/**< E:Resize image #5 C (16bits, unit 8byte).				*/
	USHORT							f_y;				/**< F:Resize image #6 Y (16bits, unit 8byte).				*/
	USHORT							f_c;				/**< F:Resize image #6 C (16bits, unit 8byte).				*/
	USHORT							g_r_y;				/**< G:SHDR output image R/Y (16bits, unit 8byte).			*/
	USHORT							g_g_c;				/**< G:SHDR output image G/C (16bits, unit 8byte).			*/
	USHORT							g_b;				/**< G:SHDR output image B (16bits, unit 8byte).			*/
	USHORT							h_x;				/**< H:Output motion vector image X (16bits, unit 8byte).	*/
	USHORT							h_y;				/**< H:Output motion vector image Y (16bits, unit 8byte).	*/
	USHORT							i;					/**< I:Reserve.												*/
} T_IM_SHDR_CTRL_SDRAM_GHSIZE_W;

/** SHDR SDRAM parameter (SDWR_VFM) */
typedef struct {
	UCHAR							a;					/**< A:RBK0 output image<br>
															<ul>
																<li>@ref D_IM_SHDR_VFMT_COMPIP_VIDEO
																<li>@ref D_IM_SHDR_VFMT_COMPIP_RASTER
															</ul>
														*/
	UCHAR							b;					/**< B:RBK1 output image(1/32 reduction image).<br>
															<ul>
																<li>@ref D_IM_SHDR_VFMT_RASTER
																<li>@ref D_IM_SHDR_VFMT_VIDEO
															</ul>
														*/
} T_IM_SHDR_CTRL_SDRAM_VFM_W;

/** SHDR SDRAM parameter (SDWR_BA) */
typedef struct {
	ULONG							a_y;				/**< A:RBK0 output image Y (32bits, unit 16Kbyte).		*/
	ULONG							a_c;				/**< A:RBK0 output image C (32bits, unit 16Kbyte).		*/
	ULONG							c_y;				/**< C:RBK2 output image Y (32bits, unit 16Kbyte).		*/
	ULONG							c_c;				/**< C:RBK2 output image C (32bits, unit 16Kbyte).		*/
	ULONG							d_y;				/**< D:RBK3 output image Y (32bits, unit 16Kbyte).		*/
	ULONG							d_c;				/**< D:RBK3 output image C (32bits, unit 16Kbyte).		*/
} T_IM_SHDR_CTRL_SDRAM_BADDR_W;

/** SHDR SDRAM parameter (SDWR_FW) */
typedef struct {
	USHORT							a;					/**< A:RBK0 output image (16bits, unit 256byte).		*/
	USHORT							c;					/**< C:RBK2 output image (16bits, unit 256byte).		*/
	USHORT							d;					/**< D:RBK3 output image (16bits, unit 256byte).		*/
} T_IM_SHDR_CTRL_SDRAM_HSIZE_W;

/** SHDR SDRAM parameter */
typedef struct {
	T_IM_SHDR_CTRL_SDRAM_ADDR_R		r_addr;				/**< SDRR_ADDR  :Read address.<br>
															[Ycc image]16bit image : Multiple of 4. 8bit image : Multiple of 2.<br>
															[Vector image]Multiple of 2.<br>
														*/
	T_IM_SHDR_CTRL_SDRAM_GHSIZE_R	r_ghsize;			/**< SDRR_GHSIZE:Read global horizontal size.	*/
	T_IM_SHDR_CTRL_SDRAM_HSIZE_R	r_hsize;			/**< SDRR_HSIZE :Read horizontal size.			*/
	T_IM_SHDR_CTRL_SDRAM_VSIZE_R	r_vsize;			/**< SDRR_VSIZE :Read vertical size.			*/
	T_IM_SHDR_CTRL_SDRAM_VFM_R		r_vfm;				/**< SDRR_VFM   :Read video format.				*/
	T_IM_SHDR_CTRL_SDRAM_ADDR_W		w_addr;				/**< SDRW_ADDR  :Write address.					*/
	T_IM_SHDR_CTRL_SDRAM_GHSIZE_W	w_ghsize;			/**< SDRW_GHSIZE:Write global horizontal size.	*/
	T_IM_SHDR_CTRL_SDRAM_VFM_W		w_vfm;				/**< SDRW_VFM   :Write video format.			*/
	T_IM_SHDR_CTRL_SDRAM_BADDR_W	w_baddr;			/**< SDRW_BA    :Write base address.			*/
	T_IM_SHDR_CTRL_SDRAM_HSIZE_W	w_hsize;			/**< SDRW_FW    :Write horizontal size.			*/
} T_IM_SHDR_CTRL_SDRAM;

/** SHDR COMPIP parameter */
typedef struct {
	UCHAR							mode;				/**< Compression/Decompression mode.
															<ul>
																<li>@ref D_IM_SHDR_COMP_MODE_LOSSY
																<li>@ref D_IM_SHDR_COMP_MODE_LOSSLESS
															</ul>
														*/
	UCHAR							mc_mode;			/**< MC mode.
															<ul>
																<li>@ref D_IM_SHDR_COMP_MC_UNUSED
																<li>@ref D_IM_SHDR_COMP_MC_USED
															</ul>
														*/
	UCHAR							comp_incfmt;		/**< CbCr format at COMP side.
															If you use r/w_bypass_mode = D_IM_SHDR_DISABLE,<br>
															select D_IM_SHDR_COMP_INCFMT_YUV420.
															<ul>
																<li>@ref D_IM_SHDR_COMP_INCFMT_YUV420
																<li>@ref D_IM_SHDR_COMP_INCFMT_YUV422
															</ul>
														*/
	UCHAR							r_bypass_mode;		/**< Read bypass mode.
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							w_bypass_mode;		/**< Write bypass mode.
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							r_img_axi_size;		/**< axi size unit of image data transfer(read).
															<ul>
																<li>@ref D_IM_SHDR_COMP_AXI_512
																<li>@ref D_IM_SHDR_COMP_AXI_256
															</ul>
														*/
	UCHAR							r_comp_axi_size;	/**< axi size unit of compression information(read).
															<ul>
																<li>@ref D_IM_SHDR_COMP_AXI_512
																<li>@ref D_IM_SHDR_COMP_AXI_256
															</ul>
														*/
	UCHAR							w_img_axi_size;		/**< axi size unit of image data transfer(write).
															 axi size unit of compression information(write) is 256byte fixation.
															<ul>
																<li>@ref D_IM_SHDR_COMP_AXI_512
																<li>@ref D_IM_SHDR_COMP_AXI_256
															</ul>
														*/
	USHORT							lint_no;			/**< Tile vertical number that an line interrupt generates. */
	UCHAR							lint_mask;			/**< Line interrupt mask setting.
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul>
														*/
	UCHAR							lint_sts;			/**< Line interrupt status.
															-- Case of read --
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE
															</ul><br>
															-- Case of write --
															<ul>
																<li>@ref D_IM_SHDR_DISABLE
																<li>@ref D_IM_SHDR_ENABLE (Line interrupt clear)
															</ul>
														*/
	ULONG							w_addr_y;			/**< Write address(Y) of compression information.<br>
															 You do not use it with the BYPASS mode.
														*/
	ULONG							w_addr_c;			/**< Write address(C) of compression information.<br>
															 You do not use it with the BYPASS mode.
														*/
	ULONG							r_addr_y;			/**< Read address(Y) of compression information.<br>
															 You do not use it with the BYPASS mode.
														*/
	ULONG							r_addr_c;			/**< Read address(C) of compression information.<br>
															 You do not use it with the BYPASS mode.
														*/
} T_IM_SHDR_CTRL_COMPIP;

/** SHDR control parameter */
typedef struct {
	T_IM_SHDR_CTRL_IMAGE_SET		image_set;			/**< Image setting parameter.				*/
	T_IM_SHDR_CTRL_IMAGE_MODE		image_mode;			/**< Image mode parameter.					*/
	T_IM_SHDR_CTRL_SDRAM			sdram;				/**< SDRAM parameter.						*/
	T_IM_SHDR_CTRL_COMPIP			compip;				/**< COMPIP parameter.						*/
	T_IM_SHDR_CALLBACK				pCallBack;			/**< User callback function(Frame comp).	*/
	T_IM_SHDR_LINEINT_CALLBACK		pLineInt_CallBack;	/**< User callback function(Line int).		*/
} T_IM_SHDR_CTRL;

typedef struct _ImShdr2  ImShdr2;
typedef struct _ImShdr2Private ImShdr2Private;

struct _ImShdr2 {
KObject parent;
UCHAR				gImShdrOutCtrl;
};

KConstType  im_shdr2_get_type(void);
ImShdr2* im_shdr2_get(void);

INT32 Im_SHDR_Ctrl_Common( const T_IM_SHDR_CTRL* const shdr_ctrl );
INT32 Im_SHDR_Get_Ctrl_Common( T_IM_SHDR_CTRL* const shdr_ctrl );
INT32 Im_SHDR_Wait_End( UINT32* const p_wait_factor, const INT32 wait_time );
VOID Im_SHDR_Int_Handler( VOID );
VOID Im_SHDR_Line_Int_Handler( VOID );

#define im_shdr2_get_gIM_SHDR_Out_Ctrl(self)        (&(self->gImShdrOutCtrl))

#endif /* __IM_SHDR2_H__ */
