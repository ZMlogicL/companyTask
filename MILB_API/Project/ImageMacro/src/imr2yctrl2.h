/*
 * imr2yctrl2.h
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
*@author              :gonghaotian
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

#ifndef __IM_R2Y_CTRL2_H__
#define __IM_R2Y_CTRL2_H__

#include <klib.h>
#include "ddim_typedef.h"

#define IM_TYPE_R2Y_CTRL2		(im_r2y_ctrl2_get_type())
#define IM_R2Y_CTRL2(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yCtrl2))
#define IM_IS_R2Y_CTRL2(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_CTRL2))

typedef struct 				_ImR2yCtrl2 ImR2yCtrl2;
typedef struct 				_ImR2yCtrl2Private ImR2yCtrl2Private;

struct _ImR2yCtrl2 {
	KObject parent;
};

/** Color control of RGB data
*/
typedef struct {
	kuint16			R;							/**< WBGAR (11bits) / WBLVR (12bits) : Control of R pixel	*/
	kuint16			G;							/**< WBGAG (11bits) / WBLVG (12bits) : Control of G pixel	*/
	kuint16			B;							/**< WBGAB (11bits) / WBLVB (12bits) : Control of B pixel	*/
} R2yRgbColor;

/** CC0 Matrix control
*/
typedef struct {
	kuint16			posiDec;					/**< CCCTL.CC0DP : CC0 matrix decimal point position (2bits)			*/
	kint16			ccMatrix[3][3];			/**< CC0K : CC-Matrix coefficient 3x3 (12bits signed)					*/
	kuint16			cybof[3];					/**< CC0YBOF : Blend luminance offset color correction (11bits)			*/
	kint16			cybga[3];					/**< CC0YBGA : Blend color correction brightness gain (9bits signed)	*/
	kuint16			cybbd[2];					/**< CC0YBBD : Boundary blend color correction brightness (12bits)		*/
	kuint16			cyc[3];						/**< CCYC : Coefficient of Yb convert (8bits)							*/
} R2yCtrlCc0;							/* CC-Matrix control	*/

/** Offset before TC data
*/
typedef struct {
	kint16			R;							/**< TCOFR : Offset R correction value before TC(10bits signed)		*/
	kint16			G;							/**< TCOFG : Offset G correction value before TC(10bits signed)		*/
	kint16			B;							/**< TCOFB : Offset B correction value before TC(10bits signed)		*/
	kint16			Yb;							/**< TCOFYB : Offset Yb correction value before TC(10bits signed)	*/
} TImR2yTcof;								/* Offset before TC data	*/

/** Luminance Evaluation before TC data
*/
typedef struct {
	kuint16			tctEnable;					/**< TCTCTL.TCTEN : Luminance evaluation acquisition enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not acquire luminance evaluation value.
													<li>@ref ImR2yCtrl_ENABLE_ON : Acquires luminance evaluation value.</ul>	*/
	kuint16			startX;					/**< TCTSTA.TCTHSTA : start X position (12bits, multiple of 2)				*/
	kuint16			startY;					/**< TCTSTA.TCTVSTA : start Y position (14bits)								*/
	kuint16			blockHsiz;					/**< TCTB.TCTBHSIZ : Horizontal size (8bits, multiple of 2, 8~128)			*/
	kuint16			blockVsiz;					/**< TCTB.TCTBVSIZ : Vertical size (8bits, 4~128)							*/
	kuint16			blockHnum;					/**< TCTB.TCTBHNUM : Block count(Horizontal) (6bits, 2~40)					*/
	kuint16			blockVnum;					/**< TCTB.TCTBVNUM : Block count(Vertical) (5bits, 2~30)					*/
} TImR2yTct;									/* Luminance Evaluation before TC data	*/

/** Rectangle of image
*/
typedef struct {
	kuint16					imgTop;								/**< Vertical start position		*/
	kuint16					imgLeft;								/**< Horizontal start position		*/
	kuint16					imgWidth;								/**< Horizontal size				*/
	kuint16					imgLines;								/**< Vertical size					*/
} TImR2yRect;								/* Rectangle control data	*/


/** histogram before TC data
*/
typedef struct {
	kuint16			histEnable;				/**< TCHSCTL.TCHSEN : Histogram acquisition enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not acquire histogram.
													<li>@ref ImR2yCtrl_ENABLE_ON : Acquires histogram.</ul>								*/
	kuint16			samplingHcyc;				/**< TCHSCTL.TCHSHCYC : Horizontal sampling interval setting (2bit)
												<ul><li>@ref ImR2yCtrl_HIST_HCYC_4
													<li>@ref ImR2yCtrl_HIST_HCYC_8
													<li>@ref ImR2yCtrl_HIST_HCYC_16</ul>													*/
	kuint16			samplingVcyc;				/**< TCHSCTL.TCHSVCYC : Vertical sampling interval setting (3bit)
												<ul><li>@ref ImR2yCtrl_HIST_VCYC_1
													<li>@ref ImR2yCtrl_HIST_VCYC_2
													<li>@ref ImR2yCtrl_HIST_VCYC_4
													<li>@ref ImR2yCtrl_HIST_VCYC_8
													<li>@ref ImR2yCtrl_HIST_VCYC_16</ul>													*/
	kuint16			histogramMode;				/**< TCHSCTL.TCHSRGBMD : RGB histogram mode (3bit)
												<ul><li>@ref ImR2yCtrl_HIST_BIT_WIDTH_7_0
													<li>@ref ImR2yCtrl_HIST_BIT_WIDTH_8_1
													<li>@ref ImR2yCtrl_HIST_BIT_WIDTH_9_2
													<li>@ref ImR2yCtrl_HIST_BIT_WIDTH_10_3
													<li>@ref ImR2yCtrl_HIST_BIT_WIDTH_11_4</ul>											*/
	kuint16			histMinusMode;			/**< TCHSCTL.TCHSMN : RGB histogram minus value mode (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not count minus value.
													<li>@ref ImR2yCtrl_ENABLE_ON : Counts minus value as pixel value equals "0".</ul>	*/
	TImR2yRect	tchsWindow;				/**< TCHSSTA.TCHSHSTA : Horizontal start position (12bits, multiple of 2)<br>
													 TCHSSTA.TCHSVSTA : Vertical start position (14bits)<br>
													 TCHSSIZ.TCHSHSIZ : Horizontal size (12bits, multiple of 2, 2~2360)<br>
													 TCHSSIZ.TCHSVSIZ : Vertical size (14bits, 1~8800)									*/
} TImR2yTchs;								/* Histogram before TC data	*/

/** Gamma correction control
*/
typedef struct {
	kuint16			gammaEnable;				/**< GMCTL.GMEN : Gamma correction enable (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Does not perform gamma correction.
													<li>@ref ImR2yCtrl_ENABLE_ON : Performs gamma correction.</ul>							*/
	kuint16			gammaMode;					/**< GMCTL.GMMD : Gamma correction mode (1bit)
												<ul><li>@ref ImR2yCtrl_GAMMA_MODE_12
													<li>@ref ImR2yCtrl_GAMMA_MODE_10</ul>													*/
	kuint16			gammaYbTblSimul;			/**< TGCTL.GAMSW : Gamma correction Yb Table simultaneous writing selection (1bit)
												<ul><li>@ref ImR2yCtrl_ENABLE_OFF : Simultaneous writing Yb table can be performed.
													<li>@ref ImR2yCtrl_ENABLE_ON : Simultaneous writing Yb table can't be performed.</ul>	*/
} ImR2yCtrlGamma;							/* Gamma correction control	*/


/** CC1 Matrix control
*/
typedef struct {
	kuint16			posiDec;					/**< CCCTL.CC1DP : CC1 matrix decimal point position (2bits)					*/
	kint16			ccMatrix[3][3];			/**< CC1K : CC-Matrix coefficient 3x3 (12bits signed)							*/
	kuint16			clipPR;					/**< CC1CLPR.CC1CLPRP : R component after CC1 positive direction clip(12bit)	*/
	kuint16			clipMR;					/**< CC1CLPR.CC1CLPRM : R component after CC1 negative direction clip(12bit)	*/
	kuint16			clipPG;					/**< CC1CLPG.CC1CLPGP : G component after CC1 positive direction clip(12bit)	*/
	kuint16			clipMG;					/**< CC1CLPG.CC1CLPGM : G component after CC1 negative direction clip(12bit)	*/
	kuint16			clipPB;					/**< CC1CLPB.CC1CLPBP : B component after CC1 positive direction clip(12bit)	*/
	kuint16			clipMB;					/**< CC1CLPB.CC1CLPBM : B component after CC1 negative direction clip(12bit)	*/
} R2yCtrlCc1;							/* CC-Matrix control	*/

/** YC Convert control
*/
typedef struct {
	kint16			ycCoeff[3][3];				/**< YC : YC convesion matrix coefficient (9bits signed)		*/
	kuint16			yBlendRatio;				/**< YBLEND.YYBLND : Luminance Y blend ratio (6bits 0 ~ 32)		*/
	kuint16			ybBlendRatio;				/**< YBLEND.YBBLND : Luminance Yb blend ratio (6bits 0 ~ 32)	*/
} R2yCtrlYcc;							/* YC convert control	*/

/** Y(Luminance) Noise Reduction control
*/
typedef struct {
	kuint16			nrMode;					/**< NRCTL.NRMD : Luminance noise reduction mode. (2bits 0~2)								*/
	kuint16			blendRatio;				/**< NRCTL.NRBLEND : Luminance blend before and after noise reduction (3bits 0~7)			*/
	kuint16			offset[4];					/**< NROF : Luminance noise reduction noise characteristic offset/LPF coefficient (10bits)	*/
	kint16			gain[4];					/**< NRGA : Luminance noise reduction noise characteristic gain (11bits signed)				*/
	kuint16			border[3];					/**< NRBD : Luminance noise reduction noise characteristic area boundary (10bits)			*/
} R2yCtrlYnr;							/* Y-Noise Reduction control	*/


KConstType 		    	im_r2y_ctrl2_get_type(void);
ImR2yCtrl2*		        im_r2y_ctrl2_new(void);

/**
WB Gain control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		rgb_color				: pointer of WB gain parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_wb_gain(ImR2yCtrl2 *self, kuint16 pipeNo, const R2yRgbColor* const rgb_color );

/**
WB Clip Level control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_rgb_color			: pointer of WB clip level parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_wb_clip_level(ImR2yCtrl2 *self, kuint16 pipeNo, const R2yRgbColor* const r2y_rgb_color );

/**
CC0 Matrix Control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_cc				: pointer of CC0 Matrix parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_cc0_matrix(ImR2yCtrl2 *self, kuint16 pipeNo, const R2yCtrlCc0* const r2y_ctrl_cc );

/**
Set CC0 Matrix coefficient
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		cc0k					: pointer of CC0 Matrix coefficient.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_cc0_matrix_coefficient(ImR2yCtrl2 *self, kuint16 pipeNo, const kint16* const cc0k );

/**
RGB Offset before TC control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_btc_offset		: pointer of BTC rgb offset control parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_before_tone_offset(ImR2yCtrl2 *self, kuint16 pipeNo, const TImR2yTcof* const r2y_ctrl_btc_offset );

/**
Luminance Evaluation before TC control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_btc_tct		: pointer of BTC tct control parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_before_tone_tct(ImR2yCtrl2 *self, kuint16 pipeNo, const TImR2yTct* const r2y_ctrl_btc_tct );

/**
Histogram before TC control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_btc_hist		: pointer of BTC histogram control parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_before_tone_tchs(ImR2yCtrl2 *self, kuint16 pipeNo, const TImR2yTchs* const r2y_ctrl_btc_hist );

/**
Set Luminance evaluation table access enable
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		tctEnable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: ImR2yCtrl_WAIT_OFF : Turn off wait. / ImR2yCtrl_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_MACRO_BUSY		: Macro busy error.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(ImR2yCtrl2 *self, kuint16 pipeNo, kuint16 tctEnable, kuint16 wait_enable );

/**
Set BTC histogram table access enable
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		histEnable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: ImR2yCtrl_WAIT_OFF : Turn off wait. / ImR2yCtrl_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_MACRO_BUSY		: Macro busy error.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(ImR2yCtrl2 *self, kuint16 pipeNo, kuint16 histEnable, kuint16 wait_enable );

/**
Gamma Correction control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_gamma			: pointer of Gamma Correction control parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_gamma(ImR2yCtrl2 *self, kuint16 pipeNo, const ImR2yCtrlGamma* const r2y_ctrl_gamma );

/**
Set Gamma table access enable
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		acc_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: ImR2yCtrl_WAIT_OFF : Turn off wait. / ImR2yCtrl_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_MACRO_BUSY		: Macro busy error.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_gamma_tbl_access_enable(ImR2yCtrl2 *self, kuint16 pipeNo, kuint16 acc_enable, kuint16 wait_enable );

/**
Set Gamma Yb table access enable
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		acc_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: ImR2yCtrl_WAIT_OFF : Turn off wait. / ImR2yCtrl_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_MACRO_BUSY		: Macro busy error.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(ImR2yCtrl2 *self, kuint16 pipeNo, kuint16 acc_enable, kuint16 wait_enable );

/** Is Gamma Control active
@param[in]		pipeNo	: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		active_status			: Gamma control status(active/inactive).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
 */
INT32 im_r2y_ctrl2_is_act_gamma(ImR2yCtrl2 *self, kuint16 pipeNo, kuint16* const active_status );

/**
CC1 Matrix Control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_cc				: pointer of CC1 Matrix parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_cc1_matrix(ImR2yCtrl2 *self, kuint16 pipeNo, const R2yCtrlCc1* const r2y_ctrl_cc );

/**
Set CC1 Matrix coefficient
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		cc1k					: pointer of CC1 Matrix coefficient.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_cc1_matrix_coefficient(ImR2yCtrl2 *self, kuint16 pipeNo, const kint16* const cc1k );

/**
YC Convert control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_ycc			: pointer of YC Convert control parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_yc_convert(ImR2yCtrl2 *self, kuint16 pipeNo, const R2yCtrlYcc* const r2y_ctrl_ycc );

/**
Y(Luminance) Noise Reduction control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_ynr			: pointer of Y Noise Reduction control parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_ynr(ImR2yCtrl2 *self, kuint16 pipeNo, const R2yCtrlYnr* const r2y_ctrl_ynr );

#endif /* __IM_R2Y_CTRL2_H__ */
