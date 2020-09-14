/*
 * imdisp6.h
 *
 *  Created on: 2020年9月8日
 *      Author: sns
 */
#ifndef __IM_DISP6_H__
#define __IM_DISP6_H__

#include <klib.h>
#include "driver_common.h"
#include "dd_top.h"
#include "imdisp3.h"
#include "imdisp5.h"

#define IM_TYPE_DISP6				(im_disp6_get_type())
#define IM_DISP6(obj) 				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp6))
#define IM_IS_DISP6(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP6))

typedef struct   _ImDisp6 			ImDisp6;
typedef struct   _ImDisp6Private		ImDisp6Private;

struct _ImDisp6 {
	KObject parent;
};


KConstType 		im_disp6_get_type(void);
ImDisp6*	im_disp6_new(void);



 INT32 im_disp6_set_osd_display_position(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, U_IM_DISP_DSTA position);

/**
Get input start position.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[in]	bank_no			Bank No.
@param[out]	position		Input start position.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp6_get_osd_display_position(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, U_IM_DISP_DSTA* position);

/**
Set GR's horizontal rectangle to showing or hiden.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	area_enable		Enable show area.<br>
							bit d[0]:Display area 0 ~ d[9]:Display area 9<br>
							value 0:disable, 1:enable<br>
							(Two or more area can be specified by the OR value.)<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp6_set_osd_area_enable(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG area_enable);

/**
Get GR's horizontal rectangle to showing or hiden.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	area_enable		Enable show area.<br>
							bit d[0]:Display area 0 ~ d[9]:Display area 9<br>
							value 0:disable, 1:enable<br>
							(Two or more area can be specified by the OR value.)<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp6_get_osd_area_enable(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG *area_enable);

/**
Set blink method selection.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	blink			Blink method selection.<br>
							bit d[0]:Display area 0 ~ d[9]:Display area 9<br>
							value 0:not blink, 1:blink<br>
							(Two or more area can be specified by the OR value.)<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp6_set_osd_blink(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG blink);

/**
Get blink method selection.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	blink			Blink method selection.<br>
							bit d[0]:Display area 0 ~ d[9]:Display area 9<br>
							value 0:not blink, 1:blink<br>
							(Two or more area can be specified by the OR value.)<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp6_get_osd_blink(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG *blink);

/**
Set GR's blink period.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	grblink			Set data which specified by set_item.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks The item which was not specified by set_item would not be set to the register.
*/
 INT32 im_disp6_set_osd_blink_timer(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_GRBLINK grblink);

/**
Get GR's blink period.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	grblink			Get data which specified by set_item.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp6_get_osd_blink_timer(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_GRBLINK *grblink);

/**
Set GR's blink sync setting.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	grbinit			Blink sync setting.<br>
							bit d[0]:Display area 0 ~ d[9]:Display area 9<br>
							value 0:not blink sync, 1:blink sync<br>
							(Two or more area can be specified by the OR value.)<br>
@param[in]	grbitrg			Blink sync trigger.<br>
							<ul><li>@ref D_IM_DISP_BITRG_NON
								<li>@ref D_IM_DISP_BITRG_WRITE_SYNC_WAIT</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks Can not D_IM_DISP_BITRG_WRITE_SYNC_WAIT writing to Blink sync trigger in the blink sync reflect wait state.
*/
 INT32 im_disp6_set_osd_blink_sync(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG grbinit, ULONG grbitrg);

/**
Get GR's blink sync setting.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	grbinit			Blink sync setting.<br>
							bit d[0]:Display area 0 ~ d[9]:Display area 9<br>
							value 0:not blink sync, 1:blink sync<br>
							(Two or more area can be specified by the OR value.)<br>
@param[out]	grbitrg			Blink sync trigger.<br>
							<ul><li>@ref D_IM_DISP_BITRG_READ_STOP
								<li>@ref D_IM_DISP_BITRG_READ_SYNC_WAIT</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp6_get_osd_blink_sync(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG* grbinit, ULONG* grbitrg);

/**
Set resize value.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	resize			Resize value.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>GRRSZ1.hrszm / GRRSZ1.hrszn >= 0.5
				<li>GRRSZ1.hrszm / GRRSZ1.hrszn <= 8
				<li>(in the case of GRRSZ1.hrszm / GRRSZ1.hrszn = 1.0) GRRSZ1.hrszof = 0
				<li>(in the case of GRHRSZ0 = ImDisp_E_IM_DISP_RSZSL_PADDING_THINNING) GRRSZ1.hrszof = 0
				<li>GRRSZ1.hrszof < GRISIZE.IHSIZE * GRRSZ1.hrszm - (pixel count after horizontal resize -1) * GRRSZ1.hrszn
				<li>GRRSZ1.hrszof < GRRSZ1.hrszm
				<li>GRRSZ2.vrszm / GRRSZ2.vrszn >= 0.5
				<li>GRRSZ2.vrszm / GRRSZ2.vrszn <= 8
			</ul>
*/
 INT32 im_disp6_set_osd_resize(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, T_IM_DISP_RESIZE const *const resize);

/**
Get resize value.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	resize			Resize value.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp6_get_osd_resize(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, T_IM_DISP_RESIZE *const resize);

/**
Set YCbCr -> RGB matrix data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	gry2r			Matrix data.
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
 INT32 im_disp6_set_osd_matrix(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_GRY2R gry2r[D_IM_DISP_MATRIX_SIZE]);

/**
Get YCbCr -> RGB matrix data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	gry2r			Matrix data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp6_get_osd_matrix(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_GRY2R gry2r[D_IM_DISP_MATRIX_SIZE]);

/**
Set GR's Alpha.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	alpha			GR's Alpha. Value range:0~255<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp6_set_osd_alpha(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG alpha);

/**
Get GR's Alpha.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	alpha			GR's Alpha.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp6_get_osd_alpha(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG* alpha);

/**
Set Anti-gamma table.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	surface			Anti-gamma table surface.<br>
							<ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
								<li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>
@param[in]	tbl				Anti gamma table.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/
 INT32 im_disp6_set_anti_gamma_table(ImDisp6 * self, ImDispEImDispSel block, BYTE surface, T_IM_DISP_ANTI_GAMMA_TBL const *const tbl);

/**
Get Anti-gamma table.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	surface			Anti-gamma table surface.<br>
							<ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
								<li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>
@param[out]	tbl				Anti gamma table.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/
 INT32 im_disp6_get_anti_gamma_table(ImDisp6 * self, ImDispEImDispSel block, BYTE surface, T_IM_DISP_ANTI_GAMMA_TBL *const tbl);

/**
Set Gamma table (Main data input block).
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	surface			Gamma table surface.<br>
							<ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
								<li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>
@param[in]	tbl				Gamma table (Main data input block).
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/
 INT32 im_disp6_set_main_gamma_table(ImDisp6 * self, ImDispEImDispSel block, BYTE surface, T_IM_DISP_GAMMA_TBL_IN const *const tbl);

/**
Get Gamma table (Main data input block).
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	surface			Gamma table surface.<br>
							<ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
								<li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>
@param[out]	tbl				Gamma table (Main data input block).
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/
 INT32 im_disp6_get_main_gamma_table(ImDisp6 * self, ImDispEImDispSel block, BYTE surface, T_IM_DISP_GAMMA_TBL_IN *const tbl);

/**
Set Gamma table (Data output block).
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	surface			Gamma table surface.<br>
							<ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
								<li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>
@param[in]	tbl				Gamma table (Data output block).
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/
 INT32 im_disp6_set_dcore_gamma_table(ImDisp6 * self, ImDispEImDispSel block, BYTE surface, T_IM_DISP_GAMMA_TBL_OUT const *const tbl);

/**
Get Gamma table (Data output block).
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	surface			Gamma table surface.<br>
							<ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
								<li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>
@param[out]	tbl				Gamma table (Data output block).
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/
 INT32 im_disp6_get_dcore_gamma_table(ImDisp6 * self, ImDispEImDispSel block, BYTE surface, T_IM_DISP_GAMMA_TBL_OUT *const tbl);

/**
Set Luminance correct table.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	surface			Luminance correct table surface.<br>
							<ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
								<li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>
@param[in]	tbl				Luminance correct table.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/
#endif /* __IM_DISP6_H__ */
