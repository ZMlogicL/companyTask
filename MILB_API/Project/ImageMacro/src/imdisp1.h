/*
 * imdisp1.h
 *
 *  Created on: 2020年9月8日
 *      Author: sns
 */#ifndef __IM_DISP1_H__
#define __IM_DISP1_H__

#include <klib.h>
#include "driver_common.h"
#include "dd_top.h"
#include "imdisp8.h"

#define IM_TYPE_DISP1				(im_disp1_get_type())
#define IM_DISP1(obj) 				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp1))
#define IM_IS_DISP1(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP1))

typedef struct   _ImDisp1 			ImDisp1;
typedef struct   _ImDisp1Private		ImDisp1Private;

struct _ImDisp1 {
	KObject parent;
	ImDisp0 * imDisp0;
};


KConstType 		im_disp1_get_type(void);
ImDisp1*	im_disp1_new(void);

#define im_disp_set_reg_signed( reg, type, member, val )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			im_disp_check_reg_type( work, (reg) );	/* The structure type matching check. */ \
		}

#define im_disp_get_reg_signed( val, reg, type, member )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = -1L; \
			if( ((work.bit.member) == 0xFFFFFFFFUL) || ((reg.bit.member) <= ((work.bit.member) /2)) ) { \
				(val) = reg.bit.member; \
			} \
			else { \
				(val) = -(work.bit.member - reg.bit.member +1); \
			} \
			im_disp_check_reg_type( (reg), work );	/* The structure type matching check. */ \
		}
//#define IM_DISP_REG_TYPE_CHECK
// The structure type matching check.
#ifdef IM_DISP_REG_TYPE_CHECK
#define im_disp_check_reg_type( dst, src )	(dst) = (src);
#else
#define im_disp_check_reg_type( dst, src )
#endif

#define im_disp_set_reg_signed_a( reg, type, member, val )		\
		{ \
			type work = { .word[0] = 0xFFFFFFFFUL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			im_disp_check_reg_type( work, (reg) );	/* The structure type matching check. */ \
		}

// Startup status of P2M/PWCH
typedef enum {
	E_IM_DISP_P2M_PWCH_TRG_WRITE_STOP = 0x00000000,		// Set TRG to off by frame stop
	E_IM_DISP_P2M_PWCH_TRG_WRITE_START,					// Set TRG to on
	E_IM_DISP_P2M_PWCH_TRG_READ_NO_ACT,					// TRG is not on, or set to off at once
	E_IM_DISP_P2M_PWCH_TRG_READ_ACT						// TRG is on
} E_IM_DISP_P2M_PWCH_TRG;

//---------------------- driver  section -------------------------------
/**
Initialize DISP macro to clear soft-reset bit.
*/
 VOID im_disp1_init(ImDisp1 * self);

/**
Set control data of main data input block.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param [in] ctrl_trg_limit	Setting of main data input block.<br>
							It is not possible to rewrite it while main data input block is operating.<br>
@param[in]	ctrl			Setting of main data input block.<br>
							It is possible to rewrite it while main data input block is operating.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
@remarks	If NULL is specified for the argument, the setting of the item can be skipped.<br>
			It is necessary to fulfill the following conditions. <br>
			<ul><li>LISIZE.IHSIZE >= 128
				<li>LISIZE.IHSIZE is a multiple of 2
				<li>LDSTA.DSH + LISIZE.IHSIZE * (LRSZ1.hrszm / LRSZ1.hrszn) <= OHSIZE
				<li>LISIZE.IVSIZE >= 16
				<li>LISIZE.IVSIZE is a multiple of 2
				<li>LDSTA.DSV + LISIZE.IVSIZE * (LRSZ2.vrszm / LRSZ2.vrszn) <= OVSIZE
				<li>LYHGA > 0
				<li>LCHGA > 0
				<li>LRSZ1.hrszm / LRSZ1.hrszn >= 0.5
				<li>LRSZ1.hrszm / LRSZ1.hrszn <= 8
				<li>(in the case of LRSZ1.hrszm / LRSZ1.hrszn = 1.0) LRSZ1.hrszof = 0
				<li>(in the case of LHRSZ0 = ImDisp_E_IM_DISP_RSZSL_PADDING_THINNING) LRSZ1.hrszof = 0
				<li>LRSZ1.hrszof < LISIZE.IHSIZE * LRSZ1.hrszm - (OHSIZE - 1) * LRSZ1.hrszn
				<li>LRSZ1.hrszof < LRSZ1.hrszm
				<li>LRSZ2.vrszm / LRSZ2.vrszn >= 0.5
				<li>LRSZ2.vrszm / LRSZ2.vrszn <= 8
				<li>LYWTH.ywthh > LYWTH.ywthl
				<li>LDSTA.DSH is a multiple of 2
				<li>LDSTA.DSV is a multiple of 2
				<li>LTCCTL.TCRES < 3
				<li>(in the case of LTCCTL.TCRES = 1 and LTCCTL.TCBLEN = 0) LTCCTL.TCTBL < 2
				<li>(in the case of LTCCTL.TCRES = 2 and LTCCTL.TCBLEN = 1) LTCCTL.TCTBL < 2
			</ul>
*/
 INT32 im_disp1_ctrl_main_layer(ImDisp1 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT const *const ctrl_trg_limit, T_IM_DISP_CTRL_MAIN_LAYER const *const ctrl);

/**
Get control data of main data input block.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out] ctrl_trg_limit	Setting of main data input block.<br>
							It is not possible to rewrite it while main data input block is operating.<br>
@param[out]	ctrl			Setting of main data input block.<br>
							It is possible to rewrite it while main data input block is operating.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks If NULL is specified for the argument, the acquisition of the item can be skipped.<br>
*/
 INT32 im_disp1_get_ctrl_main_layer(ImDisp1 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT *const ctrl_trg_limit, T_IM_DISP_CTRL_MAIN_LAYER *const ctrl);

/**
Set control data of data output block.<br>
@param[in]	block				Common block selection.<br>
								<ul><li>@ref ImDisp_E_IM_DISP_HDMI
									<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	ctrl_trg_limit		Setting of data output block.<br>
								It is not possible to rewrite it while data output block is operating.<br>
@param[in]	ctrl				Setting of data output block.<br>
								It is possible to rewrite it while data output block is operating.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy.
@remarks	If NULL is specified for the argument, the setting of the item can be skipped.<br>
			It is necessary to fulfill the following conditions. <br>
			<ul><li>(in the case of IFS = D_IM_DISP_IFS_LCD) TOCTL.CON = D_IM_DISP_CON_EXTERNAL
				<li>(in the case of IFS = D_IM_DISP_IFS_HDMI) POLSEL.VEPS = D_IM_DISP_POLARITY_POSITIVE
				<li>(in the case of TSL = D_IM_DISP_TSL_PROGRESSIVE) VCYC.VCYC1 >= VBLK.VBLK1 + OVSIZE + 1
				<li>(in the case of TSL = D_IM_DISP_TSL_PROGRESSIVE) VCYC.VCYC2 >= VBLK.VBLK2 + OVSIZE + 1
				<li>(in the case of TSL = D_IM_DISP_TSL_INTERLACE) VCYC.VCYC1 >= VBLK.VBLK1 + (OVSIZE / 2) + 1
				<li>(in the case of TSL = D_IM_DISP_TSL_INTERLACE) VCYC.VCYC2 >= VBLK.VBLK2 + (OVSIZE / 2) + 1
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_RGB888_24BIT) HCYC >= HBLK + OHSIZE + 8
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_RGB888_24BIT) HCYC >= OHSIZE + 28
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_RGB888_8BIT_1) HCYC >= HBLK + OHSIZE + 8
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_RGB888_8BIT_1) HCYC >= OHSIZE + 28
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_RGB888_8BIT_2) HCYC >= HBLK + (OHSIZE * 3) + 8
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_RGB888_8BIT_2) HCYC >= (OHSIZE * 3) + 28
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_RGB888_8BIT_3) HCYC >= HBLK + (OHSIZE * 2) + 8
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_RGB888_8BIT_3) HCYC >= (OHSIZE * 2) + 28
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_YCC422_8BIT) HCYC >= HBLK + (OHSIZE * 2) + 8
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_YCC422_8BIT) HCYC >= (OHSIZE * 2) + 28
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_YCC422_16BIT) HCYC >= HBLK + OHSIZE + 8
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_YCC422_16BIT) HCYC >= OHSIZE + 28
				<li>OVPW.OVPW > 0
				<li>HPW > 0
				<li>VBLK.VBLK1 > 0
				<li>VBLK.VBLK2 > 0
				<li>(in the case of HDLY = 0) HBLK >= 16
				<li>(in the case of HDLY > 0) HBLK >= 8
				<li>VDLY <= (HCYC / 2) - 1
				<li>HDLY <= HBLK - 8
				<li>OVSIZE < 8192
				<li>(in the case of TSL = D_IM_DISP_TSL_INTERLACE then OVSIZE is a multiple of 2
				<li>OHSIZE >= 256
				<li>(in the case of IFS = D_IM_DISP_IFS_LCD) OHSIZE <= 1024
				<li>(in the case of IFS = D_IM_DISP_IFS_HDMI) OHSIZE <= 1920
				<li>(in the case of IFS = D_IM_DISP_IFS_HDMI) VRFCTL.VEPS = D_IM_DISP_POLARITY_POSITIVE
				<li>(in the case of IFS = D_IM_DISP_IFS_LCD) DOMD.MODE = 0x00 or 0x04 or 0x05 or 0x06 or 0x40 or 0x41
				<li>(in the case of IFS = D_IM_DISP_IFS_HDMI) DOMD.MODE = 0x41
				<li>CLBHSIZE * 16 >= OHSIZE
				<li>BLDCTL.BLD1, BLDCTL.BLD2, BLDCTL.BLD3 and BLDCTL.BLD4 do not overlap
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_RGB888_24BIT) DOCTL1.ODO1 = 0
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_RGB888_24BIT) DOCTL1.ODO2 = 0
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_RGB888_24BIT) DOCTL1.ODE1 = 0
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_RGB888_24BIT) DOCTL1.ODE2 = 0
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_YCC422_8BIT) DOCTL2.CLVS = 0
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_YCC422_8BIT) DOCTL2.CAVES = 0
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_YCC422_16BIT) DOCTL2.CLVS = 0
				<li>(in the case of DOMD.MODE = D_IM_DISP_MODE_YCC422_16BIT) DOCTL2.CAVES = 0
				<li>FFDSTA.FFDSH is a multiple of 2
				<li>FFDSTA.FFDSV is a multiple of 2
				<li>FFSIZE.FFHSZ is a multiple of 2
				<li>FFSIZE.FFHSZ >= 8
				<li>FFSIZE.FFVSZ is a multiple of 2
				<li>FFSIZE.FFVSZ >= 8
				<li>FFWIDTH.FFHWID is a multiple of 2
				<li>FFWIDTH.FFHWID >= 2
				<li>FFWIDTH.FFVWID is a multiple of 2
				<li>FFWIDTH.FFVWID >= 2
			</ul>
*/
 INT32 im_disp1_ctrl_output(ImDisp1 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT const *const ctrl_trg_limit, T_IM_DISP_CTRL_OUTPUT const *const ctrl);

/**
Get control data of data output block.<br>
@param[in]	block				Common block selection.<br>
								<ul><li>@ref ImDisp_E_IM_DISP_HDMI
									<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	ctrl_trg_limit		Setting of data output block.<br>
								It is not possible to rewrite it while data output block is operating.<br>
@param[out]	ctrl				Setting of data output block.<br>
								It is possible to rewrite it while data output block is operating.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks If NULL is specified for the argument, the acquisition of the item can be skipped.<br>
*/
 INT32 im_disp1_get_ctrl_output(ImDisp1 * self,ImDispEImDispSel block, T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT *const ctrl_trg_limit, T_IM_DISP_CTRL_OUTPUT *const ctrl);

/**
Set control data of Grid in common block.<br>
@param[in]	block				Common block selection.<br>
								<ul><li>@ref ImDisp_E_IM_DISP_HDMI
									<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	ctrl				Setting of grid data.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	If NULL is specified for the argument, the acquisition of the item can be skipped.<br>
			It is necessary to fulfill the following conditions. <br>
			<ul><li>GHDSTA.DSH is a multiple of 2
				<li>GHDSTA.DSV is a multiple of 2
				<li>GVDSTA.DSH is a multiple of 2
				<li>GVDSTA.DSV is a multiple of 2
				<li>GLENGTH.GHLEN is a multiple of 2
				<li>GLENGTH.GHLEN >= 8
				<li>GLENGTH.GVLEN is a multiple of 2
				<li>GLENGTH.GVLEN >= 8
				<li>GWIDTH.GHWID is a multiple of 2
				<li>GWIDTH.GHWID >= 2
				<li>GWIDTH.GVWID is a multiple of 2
				<li>GWIDTH.GVWID >= 2
				<li>GITVL.GHITV is a multiple of 2
				<li>GITVL.GHITV >= GWIDTH.GHWID + 2
				<li>GITVL.GVITV is a multiple of 2
				<li>GITVL.GVITV >= GWIDTH.GVWID + 2
			</ul>
*/
 INT32 im_disp1_ctrl_grid_layer(ImDisp1 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_GRID_LAYER const *const ctrl);

/**
Get control data of Grid in common block.<br>
@param[in]	block				Common block selection.<br>
								<ul><li>@ref ImDisp_E_IM_DISP_HDMI
									<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[out]	ctrl				Setting of grid data.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks If NULL is specified for the argument, the acquisition of the item can be skipped.<br>
*/
 INT32 im_disp1_get_ctrl_grid_layer(ImDisp1 * self, ImDispEImDispSel block, T_IM_DISP_CTRL_GRID_LAYER *const ctrl);

/**
Set control data of OSD data input block.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[in]	grrpgctl		Register paramter taking control register.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
								<li>@ref ImDisp_E_IM_DISP_RPGTMG_VSYNC_VSYNC</ul>
@param[in]	ctrl			Setting of OSD data input block.<br>
							It is possible to rewrite it while OSD data input block is operating.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy.
@remarks	If NULL is specified for the argument, the setting of the item can be skipped.<br>
			It is necessary to fulfill the following conditions. <br>
			<ul><li>GRIDT.ifmt <= @ref D_IM_DISP_GRIDT_IFMT_RGBA5551
				<li>GRTISIZE.TIHSIZE is a multiple of 2
				<li>GRTISIZE.TIHSIZE >= 8
				<li>GRDSTA.DSH + GRTISIZE.TIHSIZE * (GRRSZ1.hrszm / GRRSZ1.hrszn) <= OHSIZE
				<li>GRTISIZE.TIVSIZE is a multiple of 2
				<li>GRTISIZE.TIVSIZE >= 8
				<li>GRDSTA.DSV + GRTISIZE.TIVSIZE * (GRRSZ2.vrszm / GRRSZ2.vrszn) <= OVSIZE
				<li>GRTDSTA.DSH is a multiple of 2
				<li>GRTDSTA.DSV is a multiple of 2
				<li>GRIPO.IPO1, GRIPO.IPO2, GRIPO.IPO3 and GRIPO.IPO4 do not overlap
				<li>GRISIZE.IHSIZE is a multiple of 4
				<li>GRISIZE.IHSIZE >= 8
				<li>GRISIZE.IVSIZE is a multiple of 2
				<li>GRISIZE.IVSIZE >= 8
				<li>GRDSTA.DSH + GRISIZE.IHSIZE <= GRTISIZE.TIHSIZE
				<li>GRDSTA.DSV + GRISIZE.IVSIZE <= GRTISIZE.TIVSIZE
				<li>GRSA0 is a multiple of 8
				<li>GRSA is a multiple of 8
				<li>GRHGA > 0
				<li>GRHGA <= 0xFFF8
				<li>GRHGA is a multiple of 8
				<li>GRDSTA.DSH is a multiple of 2
				<li>GRDSTA.DSV is a multiple of 2
				<li>GRDSTA.DSH_0 <= DSH_1 <= DSH_2 ... <= DSH_9 (in order of bank_no)
				<li>(in case of same DSH) GRDSTA.DSV_0 <= DSV_1 <= DSV_2 ... <= DSV_9
				<li>GRRSZ1.hrszm / GRRSZ1.hrszn >= 0.5
				<li>GRRSZ1.hrszm / GRRSZ1.hrszn <= 8
				<li>(in the case of GRRSZ1.hrszm / GRRSZ1.hrszn = 1.0) GRRSZ1.hrszof = 0
				<li>(in the case of GRRSZ0 = ImDisp_E_IM_DISP_RSZSL_PADDING_THINNING) GRRSZ1.hrszof = 0
				<li>GRRSZ1.hrszof < GRISIZE.IHSIZE * GRRSZ1.hrszm - (pixel count after horizontal resize -1) * GRRSZ1.hrszn
				<li>GRRSZ1.hrszof < GRRSZ1.hrszm
				<li>GRRSZ2.vrszm / GRRSZ2.vrszn >= 0.5
				<li>GRRSZ2.vrszm / GRRSZ2.vrszn <= 8
				<li>GRTCCTL.TCRES < 3
				<li>(in the case of GRTCCTL.TCRES = 1 and GRTCCTL.TCBLEN = 0) GRTCCTL.TCTBL < 2
				<li>(in the case of GRTCCTL.TCRES = 2 and GRTCCTL.TCBLEN = 1) GRTCCTL.TCTBL < 2
			</ul>
*/
 INT32 im_disp1_ctrl_osd_layer(ImDisp1 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ImDispEImDispRpgtmg* grrpgctl, T_IM_DISP_CTRL_OSD_LAYER const *const ctrl);

/**
Get control data of OSD layer in common block.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	grrpgctl		Register paramter taking control register.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
								<li>@ref ImDisp_E_IM_DISP_RPGTMG_VSYNC_VSYNC</ul>
@param[out]	ctrl			Setting of OSD data input block.<br>
							It is possible to rewrite it while OSD layer in common block is operating.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks If NULL is specified for the argument, the acquisition of the item can be skipped.<br>
*/
 INT32 im_disp1_get_ctrl_osd_layer(ImDisp1 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ImDispEImDispRpgtmg* grrpgctl, T_IM_DISP_CTRL_OSD_LAYER *const ctrl);

/**
Set Gamma table of main data input block.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	ctrl_tbl		Table setting data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks If NULL is specified for the argument, the acquisition of the item can be skipped.<br>
*/
#endif /* __IM_DISP1_H__ */
