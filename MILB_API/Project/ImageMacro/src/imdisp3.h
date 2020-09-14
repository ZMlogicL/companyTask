/*
 * imdisp3.h
 *
 *  Created on: 2020年9月8日
 *      Author: sns
 */
#ifndef __IM_DISP3_H__
#define __IM_DISP3_H__

#include <klib.h>
#include "driver_common.h"
#include "dd_top.h"
#include "imdisp1.h"
#include "imdisp8.h"

#define IM_TYPE_DISP3				(im_disp3_get_type())
#define IM_DISP3(obj) 				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp3))
#define IM_IS_DISP3(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP3))

typedef struct   _ImDisp3 			ImDisp3;
typedef struct   _ImDisp3Private		ImDisp3Private;

struct _ImDisp3 {
	KObject parent;
};


KConstType 		im_disp3_get_type(void);
ImDisp3*	im_disp3_new(void);

/**	TBLASET register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	GMTAEN	:1;	/**< GMTAEN: Gamma correction access enable.<br>
								 <ul><li>@ref E_IM_DISP_CORRECT_PROC_DISABLE
									 <li>@ref E_IM_DISP_CORRECT_PROC_ENABLE</ul>				*/
		ULONG	gmen	:1;	/**< gmen: Gamma correction enable.<br>
								 <ul><li>@ref E_IM_DISP_CORRECT_PROC_DISABLE
									 <li>@ref E_IM_DISP_CORRECT_PROC_ENABLE</ul>				*/
		ULONG	gmtsl	:1;	/**< gmtsl: Gamma correction table surface.<br>
								 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
									 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>					*/
		ULONG			:5;	/**< Reserve														*/
		ULONG	YSATTA	:1;	/**< YSATTA: Luminance and chroma correction access enable.<br>
								 <ul><li>@ref E_IM_DISP_CORRECT_PROC_DISABLE
									 <li>@ref E_IM_DISP_CORRECT_PROC_ENABLE</ul>				*/
		ULONG	YSATEN	:1;	/**< YSATEN: Luminance and chroma correction enable.<br>
								 <ul><li>@ref E_IM_DISP_CORRECT_PROC_DISABLE
									 <li>@ref E_IM_DISP_CORRECT_PROC_ENABLE</ul>				*/
		ULONG	YSATSL	:1;	/**< YSATSL: Luminance and chroma correction table surface.<br>
								 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
									 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>					*/
		ULONG			:5;	/**< Reserve														*/
		ULONG	gmtmn	:1;	/**< gmtmn: Gamma correction table monitor.<br>
								 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
									 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>					*/
		ULONG			:7;	/**< Reserve														*/
		ULONG	YSATMN	:1;	/**< YSATMN:  Luminance and chroma correction table monitor.<br>
								 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
									 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>					*/
		ULONG			:7;	/**< Reserve														*/
	} bit;	/**< Bit field */
} U_IM_DISP_TBLASET;

/** LYHLPCTL Register - yhlpmd (YHLP mode) */
typedef enum {
	E_IM_DISP_YHLPMD_HORIZONTAL_SPACE_FILTER	= 0,	/**< LYHLPCTL.yhlpmd Register<br> Horizontal space filter	*/
	E_IM_DISP_YHLPMD_OUTLINE_ENHANCEMENT		= 1,	/**< LYHLPCTL.yhlpmd Register<br> Outline enhancement		*/
	E_IM_DISP_YHLPMD_OUTLINE_COLOR				= 2		/**< LYHLPCTL.yhlpmd Register<br> Outline color				*/
} E_IM_DISP_YHLPMD;

/** GRAREN Register - AREN (Display area enable setting)<br>
 GRBSL  Register - BSL (Display area blink setting)*/
typedef enum {
	E_IM_DISP_AREA_0   = 0x0001,	/**< GRAREN.AREN, GRBSL.BSL Register<br> Display area 0	*/
	E_IM_DISP_AREA_1   = 0x0002,	/**< GRAREN.AREN, GRBSL.BSL Register<br> Display area 1	*/
	E_IM_DISP_AREA_2   = 0x0004,	/**< GRAREN.AREN, GRBSL.BSL Register<br> Display area 2	*/
	E_IM_DISP_AREA_3   = 0x0008,	/**< GRAREN.AREN, GRBSL.BSL Register<br> Display area 3	*/
	E_IM_DISP_AREA_4   = 0x0010,	/**< GRAREN.AREN, GRBSL.BSL Register<br> Display area 4	*/
	E_IM_DISP_AREA_5   = 0x0020,	/**< GRAREN.AREN, GRBSL.BSL Register<br> Display area 5	*/
	E_IM_DISP_AREA_6   = 0x0040,	/**< GRAREN.AREN, GRBSL.BSL Register<br> Display area 6	*/
	E_IM_DISP_AREA_7   = 0x0080,	/**< GRAREN.AREN, GRBSL.BSL Register<br> Display area 7	*/
	E_IM_DISP_AREA_8   = 0x0100,	/**< GRAREN.AREN, GRBSL.BSL Register<br> Display area 8	*/
	E_IM_DISP_AREA_9   = 0x0200		/**< GRAREN.AREN, GRBSL.BSL Register<br> Display area 9	*/
} E_IM_DISP_AREA;

/** P2MCTL Register - PKNEMD (KNEE compression mode) */
typedef enum {
	E_IM_DISP_PKNEMD_NOT	= 0,	/**< not KNEE compression processing.				*/
	E_IM_DISP_PKNEMD_12_8,			/**< KNEE compression processing(12bit to 8bit).	*/
	E_IM_DISP_PKNEMD_12_10			/**< KNEE compression processing(12bit to 10bit).	*/
} E_IM_DISP_PKNEMD;

/** Setting of table access enable and processing enable. */
typedef struct {
	ImDispEImDispTableAccess	access;		/**< Table access enable.<br>
				 							 <ul><li>@ref ImDisp_E_IM_DISP_TABLE_ACCESS_DISABLE
												 <li>@ref ImDisp_E_IM_DISP_TABLE_ACCESS_ENABLE</ul>	*/
	E_IM_DISP_CORRECT_PROC	proc;		/**< Processing enable.<br>
				 							 <ul><li>@ref E_IM_DISP_CORRECT_PROC_DISABLE
												 <li>@ref E_IM_DISP_CORRECT_PROC_ENABLE</ul>	*/
	BYTE					surface;	/**< Table surface.<br>
											 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
												 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>		*/
} T_IM_DISP_TBL_ACCESS_SET;


/** Setting of resize value. */
typedef struct {
	ImDispEImDispRszsl		rsz0;		/**< Resize method<br>
										 <ul><li>@ref ImDisp_E_IM_DISP_RSZSL_PADDING_THINNING
											 <li>@ref ImDisp_E_IM_DISP_RSZSL_BILINEAR</ul>		*/
	ImDispUImDispRsz1		rsz1;		/**< Resize data 1 (Horizontal)						*/
	ImDispUImDispRsz2		rsz2;		/**< Resize data 2 (Vertical)						*/
	ImDispUImDispRsz3		rsz3;		/**< Resize data 3 (chrominance start position)		*/
} T_IM_DISP_RESIZE;

 INT32 im_disp3_set_parameter_reflect_timing(ImDisp3 * self, ImDispEImDispSel block, ImDispEImDispRpgtmg timing);

/**
Get parameter reflect timing.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	timing			Register parameter reflect timing.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
								<li>@ref ImDisp_E_IM_DISP_RPGTMG_VSYNC_VSYNC</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_parameter_reflect_timing(ImDisp3 * self, ImDispEImDispSel block, ImDispEImDispRpgtmg *timing);

/**
Set input data transfer.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	lidt			Input data forwarding setting register.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_set_input_data_transfer(ImDisp3 * self, ImDispEImDispSel block, ImDispUImDispLidt lidt);

/**
Get input data transfer.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	lidt			Input data forwarding setting register.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_input_data_transfer(ImDisp3 * self, ImDispEImDispSel block, ImDispUImDispLidt *lidt);

/**
Set input data size of MAIN.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	input_size		width and height of input data buffer.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>LISIZE.IHSIZE >= 128
				<li>LISIZE.IHSIZE is a multiple of 2
				<li>LDSTA.DSH + LISIZE.IHSIZE * (LRSZ1.hrszm / LRSZ1.hrszn) <= OHSIZE
				<li>LISIZE.IVSIZE >= 16
				<li>LISIZE.IVSIZE is a multiple of 2
				<li>LDSTA.DSV + LISIZE.IVSIZE * (LRSZ2.vrszm / LRSZ2.vrszn) <= OVSIZE
			</ul>
*/
 INT32 im_disp3_set_input_size(ImDisp3 * self, ImDispEImDispSel block, U_IM_DISP_SIZE input_size);

/**
Get input data size of MAIN.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	input_size		Width and height of input data buffer.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_input_size(ImDisp3 * self, ImDispEImDispSel block, U_IM_DISP_SIZE *input_size);

/**
Connect MAIN input data address with the bank index.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	bank_no			Bank No.<br>
							<ul><li>@ref E_IM_DISP_BANK_00
								<li>@ref E_IM_DISP_BANK_01
								<li>@ref E_IM_DISP_BANK_10
								<li>@ref E_IM_DISP_BANK_11</ul>
@param[in]	address			Data address.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>(in case of bit depth is 8-bit) LYSA and LCSA are 2-byte unit.<br>
				<li>(in case of bit depth is 12-bit) LYSA and LCSA are 3-byte unit.<br>
				<li>(in case of bit depth is 16-bit) LYSA and LCSA are 4-byte unit.<br>
			</ul>
*/
 INT32 im_disp3_set_addr(ImDisp3 * self, ImDispEImDispSel block, E_IM_DISP_BANK bank_no, T_IM_DISP_IMAGE_ADDR const *const address);

/**
Get MAIN input data address of the bank index specified.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	bank_no			Bank No.<br>
							<ul><li>@ref E_IM_DISP_BANK_00
								<li>@ref E_IM_DISP_BANK_01
								<li>@ref E_IM_DISP_BANK_10
								<li>@ref E_IM_DISP_BANK_11</ul>
@param[out]	address			Data address.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_addr(ImDisp3 * self, ImDispEImDispSel block, E_IM_DISP_BANK bank_no, T_IM_DISP_IMAGE_ADDR *const address);

/**
Set the global size.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	y_hga			Global width of Y.<br>
@param[in]	c_hga			Global width of CbCr.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>LYHGA > 0
				<li>LCHGA > 0
				<li>(in case of bit depth is 8-bit) LYHGA and LCHGA are 2-byte unit.<br>
				<li>(in case of bit depth is 12-bit) LYHGA and LCHGA are 3-byte unit.<br>
				<li>(in case of bit depth is 16-bit) LYHGA and LCHGA are 4-byte unit.<br>
			</ul>
*/
 INT32 im_disp3_set_lfd(ImDisp3 * self, ImDispEImDispSel block, ULONG y_hga, ULONG c_hga);

/**
Get the global size.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	y_hga			Global width of Y.<br>
@param[out]	c_hga			Global width of CbCr.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_lfd(ImDisp3 * self, ImDispEImDispSel block, ULONG* y_hga, ULONG* c_hga);

/**
Set main bank No. to show.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	bank_no			Bank No.<br>
							<ul><li>@ref E_IM_DISP_BANK_00
								<li>@ref E_IM_DISP_BANK_01
								<li>@ref E_IM_DISP_BANK_10
								<li>@ref E_IM_DISP_BANK_11</ul>
*/
 VOID im_disp3_set_main_bank(ImDisp3 * self, ImDispEImDispSel block, E_IM_DISP_BANK bank_no);

/**
Get main bank No. to show or showing.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	bank_no			Bank No.<br>
							<ul><li>@ref E_IM_DISP_BANK_00
								<li>@ref E_IM_DISP_BANK_01
								<li>@ref E_IM_DISP_BANK_10
								<li>@ref E_IM_DISP_BANK_11</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_main_bank(ImDisp3 * self, ImDispEImDispSel block, E_IM_DISP_BANK *bank_no);

/**
Get main bank No. to showing.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	bank_no			Bank No.<br>
							<ul><li>@ref E_IM_DISP_BANK_00
								<li>@ref E_IM_DISP_BANK_01
								<li>@ref E_IM_DISP_BANK_10
								<li>@ref E_IM_DISP_BANK_11</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_main_bank_monitor(ImDisp3 * self, ImDispEImDispSel block, E_IM_DISP_BANK *bank_no);

/**
Set resize value.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	resize			Resize value.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>LRSZ1.hrszm / LRSZ1.hrszn >= 0.5
				<li>LRSZ1.hrszm / LRSZ1.hrszn <= 8
				<li>(in the case of LRSZ1.hrszm / LRSZ1.hrszn = 1.0) LRSZ1.hrszof = 0
				<li>(in the case of LHRSZ0 = ImDisp_E_IM_DISP_RSZSL_PADDING_THINNING) LRSZ1.hrszof = 0
				<li>LRSZ1.hrszof < LISIZE.IHSIZE * LRSZ1.hrszm - (OHSIZE - 1) * LRSZ1.hrszn
				<li>LRSZ1.hrszof < LRSZ1.hrszm
				<li>LRSZ2.vrszm / LRSZ2.vrszn >= 0.5
				<li>LRSZ2.vrszm / LRSZ2.vrszn <= 8
			</ul>
*/
 INT32 im_disp3_set_resize(ImDisp3 * self, ImDispEImDispSel block, T_IM_DISP_RESIZE const *const resize);

/**
Get resize value.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	resize			Resize value.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_resize(ImDisp3 * self, ImDispEImDispSel block, T_IM_DISP_RESIZE *const resize);

/**
Set YHLP data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	yhlp			YHLP data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_set_yhlp(ImDisp3 * self, ImDispEImDispSel block, T_IM_DISP_YHLP const *const yhlp);

/**
Get YHLP data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	yhlp			YHLP data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_yhlp(ImDisp3 * self, ImDispEImDispSel block, T_IM_DISP_YHLP *const yhlp);

/**
Set warning processing data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	warning			Warning processing data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>LYW0TH.YW0THH >= LYW0TH.YW0THL
				<li>LYW1TH.YW1THH >= LYW1TH.YW1THL
				<li>If LYWCTL.ywsl=0 or 1(Brightness warning),<br>
					don't set to 2 and 3 in LYW0ST.YW0MD/LYW1ST.YW1MD.
			</ul>
*/
 INT32 im_disp3_set_warning(ImDisp3 * self, ImDispEImDispSel block, T_IM_DISP_WARNING const *const warning);

/**
Get warning processing data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	warning			Warning processing data
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_warning(ImDisp3 * self, ImDispEImDispSel block, T_IM_DISP_WARNING *const warning);

/**
Set blink timer control data.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	lbltmr			Blinking timer.
*/
 VOID im_disp3_set_blink_timer(ImDisp3 * self, ImDispEImDispSel block, ImDispUImDispLbltmr lbltmr);

/**
Get blink timer control data.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	lbltmr			Blinking timer.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_blink_timer(ImDisp3 * self, ImDispEImDispSel block, ImDispUImDispLbltmr *lbltmr);


/**
Set zebra warning data.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	zebra			Zebra warning data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>LZBWID.zbhh >= 2
				<li>LZBWID.zbhl >= 2
			</ul>
*/
 INT32 im_disp3_set_zebra(ImDisp3 * self, ImDispEImDispSel block, T_IM_DISP_ZEBRA const *const zebra);

/**
Get zebra warning data.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	zebra			Zebra warning data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_zebra(ImDisp3 * self, ImDispEImDispSel block, T_IM_DISP_ZEBRA *const zebra);

/**
Set YCbCr -> RGB matrix.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	matrix			Matrix data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>Value range of COEFFICIENT0 is -128~127.<br>
					The matrix coefficient value is COEFFICIENT0/64.<br>
				<li>Value range of COEFFICIENT1 is -128~127.<br>
					The matrix coefficient value is COEFFICIENT1/64.<br>
				<li>Value range of COEFFICIENT2 is -128~127.<br>
					The matrix coefficient value is COEFFICIENT2/64.<br>
			</ul>
*/
 INT32 im_disp3_set_matrix(ImDisp3 * self, ImDispEImDispSel block, const U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE]);

/**
Get YCbCr -> RGB matrix.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	matrix			Matrix data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_matrix(ImDisp3 * self, ImDispEImDispSel block, U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE]);

/**
Set gamma correct enable.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param [in] set_item		Correct selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA
								<li>@ref ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_IN
								<li>@ref ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_OUT
								<li>@ref ImDisp_E_IM_DISP_CORRECT_SELECT_LUMINANCE
								<li>@ref ImDisp_E_IM_DISP_CORRECT_SELECT_CHROMA</ul>
@param [in] correct			Correction table and correction enable.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_set_gamma_enable(ImDisp3 * self, ImDispEImDispSel block, ImDispEImDispCorrectSelect set_item, T_IM_DISP_TBL_ACCESS_SET const *const correct);

/**
Get gamma correct enable.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	lch_ltblaset	Table RAM access setting (Main data input block).
@param[out]	dcore_tblaset	Table RAM access setting (Data output block).
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_gamma_enable(ImDisp3 * self, ImDispEImDispSel block, ImDispUImDispLtblaset *lch_ltblaset, U_IM_DISP_TBLASET *dcore_tblaset);

/**
Set gamma correct mode.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	lgmmd			Gamma correct mode.
*/
 VOID im_disp3_set_gamma_mode(ImDisp3 * self, ImDispEImDispSel block, U_IM_DISP_LGMMD lgmmd);

/**
Get gamma correct mode.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	lgmmd			Gamma correct mode.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_gamma_mode(ImDisp3 * self, ImDispEImDispSel block, U_IM_DISP_LGMMD* lgmmd);

/**
Set Alpha value.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	lalp			Alpha value.
*/
 VOID im_disp3_set_alpha_value(ImDisp3 * self, ImDispEImDispSel block, U_IM_DISP_LALP lalp);

/**
Get Alpha value.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	lalp			Alpha value.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_alpha_value(ImDisp3 * self, ImDispEImDispSel block, U_IM_DISP_LALP *lalp);

/**
Set display position.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	position		Display position.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>LDSTA.DSH is a multiple of 2
				<li>LDSTA.DSV is a multiple of 2
			</ul>
*/
 INT32 im_disp3_set_display_position(ImDisp3 * self, ImDispEImDispSel block, U_IM_DISP_DSTA position);

/**
Get display position.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	position		Display position.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_display_position(ImDisp3 * self, ImDispEImDispSel block, U_IM_DISP_DSTA *position);

/**
Set reverse display setting.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	reverse			Reverse display selection.<br>
*/
 VOID im_disp3_set_reverse_display(ImDisp3 * self, ImDispEImDispSel block, U_IM_DISP_LREVDISP reverse);

/**
Get reverse display setting.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	reverse			Reverse display selection.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp3_get_reverse_display(ImDisp3 * self, ImDispEImDispSel block, U_IM_DISP_LREVDISP *reverse);

/**
Set display interface selection.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	ifs				Display I/F Selection .<br>
							<ul><li>@ref D_IM_DISP_IFS_NONE
								<li>@ref D_IM_DISP_IFS_LCD
								<li>@ref D_IM_DISP_IFS_HDMI
								<li>@ref D_IM_DISP_IFS_MIPI</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_STATUS_ABNORMAL		Can not set because RESET.SR was not set to 1.
@remarks	The data output unit needs to be in a reset state.
*/
#endif /* __IM_DISP3_H__ */
