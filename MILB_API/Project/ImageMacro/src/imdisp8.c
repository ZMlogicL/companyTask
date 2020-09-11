/*
 * imdisp8.c
 *
 *  Created on: 2020年8月8日
 *      Author: sns
 */
#include "imdisp.h"
#include "imdisp3.h"
#include "imdisp4.h"
#include "imdisp6.h"
#include "imdisp8.h"
#include "jdsdisp3a.h"
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include <stddef.h>
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImDisp8, im_disp8)
#define IM_DISP8_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp8Private,IM_TYPE_DISP8))

struct _ImDisp8Private{
	int a;
};

static void im_disp8_constructor(ImDisp8 *self){
}

static void im_disp8_destructor(ImDisp8 *self){
}

#ifdef CO_PARAM_CHECK
/**
Check input data transfer parameter.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	lidt			Input data forwarding setting register.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp_param_check_lidt(E_IM_DISP_SEL block, U_IM_DISP_LIDT lidt)
{
	INT32 ret = D_DDIM_OK;

	if (block == E_IM_DISP_HDMI) {
		// HDMI.
		if ((lidt.bit.IFMT != D_IM_DISP_LIDT_IFMT_YCC422_RP_8BIT) &&
			(lidt.bit.IFMT != D_IM_DISP_LIDT_IFMT_YCC422_RP_12BIT_PACK) &&
			(lidt.bit.IFMT != D_IM_DISP_LIDT_IFMT_YCC422_RP_10BIT_PACK) &&
			(lidt.bit.IFMT != D_IM_DISP_LIDT_IFMT_YCC420_RP_8BIT) &&
			(lidt.bit.IFMT != D_IM_DISP_LIDT_IFMT_YCC420_RP_10BIT_PACK) &&
			(lidt.bit.IFMT != D_IM_DISP_LIDT_IFMT_GENERAL_10BIT) &&
			(lidt.bit.IFMT != D_IM_DISP_LIDT_IFMT_GENERAL_10BITx2)) {
			Im_DISP_Check_Point(("CP:im_disp_param_check_lidt() 1\n"));
			ret = D_IM_DISP_INPUT_PARAM_ERROR;
		}
	}
	else {
		// LCD/MIPI.
		if ((lidt.bit.IFMT != D_IM_DISP_LIDT_IFMT_YCC422_RP_8BIT) &&
			(lidt.bit.IFMT != D_IM_DISP_LIDT_IFMT_YCC420_RP_8BIT)) {
			Im_DISP_Check_Point(("CP:im_disp_param_check_lidt() 2\n"));
			ret = D_IM_DISP_INPUT_PARAM_ERROR;
		}
	}
	return ret;
}

/**
Check LISIZE parameter.
@param[in]	lisize			width and height of input data buffer.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp_param_check_lisize(U_IM_DISP_SIZE lisize)
{
	INT32 ret = D_DDIM_OK;

	if (lisize.size.width < 128) {
		Im_DISP_Check_Point(("CP:im_disp_param_check_lisize() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((lisize.size.width & 0x00000001) != 0) {
		Im_DISP_Check_Point(("CP:im_disp_param_check_lisize() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (lisize.size.lines < 16) {
		Im_DISP_Check_Point(("CP:im_disp_param_check_lisize() 3\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((lisize.size.lines & 0x00000001) != 0) {
		Im_DISP_Check_Point(("CP:im_disp_param_check_lisize() 4\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check LDSTA parameter.
@param[in]	ldsta			Display position.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp_param_check_ldsta(U_IM_DISP_DSTA ldsta)
{
	INT32 ret = D_DDIM_OK;

	if ((ldsta.bit.DSH & 0x00000001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_ldsta() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((ldsta.bit.DSV & 0x00000001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_ldsta() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check global size parameter.
@param[in]	y_hga			Global width of Y.<br>
							Value range:2~65535<br>
							Bit depth=8bit -> 2-byte unit<br>
							Bit depth=12bit -> 3-byte unit<br>
							Bit depth=16bit -> 4-byte unit<br>
@param[in]	c_hga			Global width of CbCr.<br>
							Value range:2~65535<br>
							Bit depth=8bit -> 2-byte unit<br>
							Bit depth=12bit -> 3-byte unit<br>
							Bit depth=16bit -> 4-byte unit<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp_param_check_lfd(ULONG y_hga, ULONG c_hga)
{
	INT32 ret = D_DDIM_OK;

	if (y_hga == 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_lfd() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((y_hga & 0x00000001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_lfd() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (c_hga == 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_lfd() 3\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((c_hga & 0x00000001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_lfd() 4\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check resize value parameter.
@param[in]	rsz0			Resize method<br>
							 <ul><li>@ref E_IM_DISP_RSZSL_PADDING_THINNING
								 <li>@ref E_IM_DISP_RSZSL_BILINEAR</ul>
@param[in]	rsz1			Resize data for horizontal.
@param[in]	rsz2			Resize data for vertical.
@param[in]	rsz3			Chrominance start position adjustment.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_resize(E_IM_DISP_RSZSL rsz0, U_IM_DISP_RSZ1 rsz1, U_IM_DISP_RSZ2 rsz2, U_IM_DISP_RSZ3 rsz3)
{
	INT32 ret = D_DDIM_OK;

	if ((double)rsz1.bit.HRSZM / rsz1.bit.HRSZN < 0.5){
		Im_DISP_Check_Point(("CP:im_disp_param_check_resize() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((double)rsz1.bit.HRSZM / rsz1.bit.HRSZN > 8.0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_resize() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((rsz0 == E_IM_DISP_RSZSL_PADDING_THINNING) && (rsz1.bit.HRSZOF != 0)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_resize() 3\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((double)rsz1.bit.HRSZM / rsz1.bit.HRSZN == 1.0) && (rsz1.bit.HRSZOF != 0)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_resize() 4\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (rsz1.bit.HRSZOF >= rsz1.bit.HRSZM){
		Im_DISP_Check_Point(("CP:im_disp_param_check_resize() 5\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((double)rsz2.bit.VRSZM / rsz2.bit.VRSZN < 0.5){
		Im_DISP_Check_Point(("CP:im_disp_param_check_resize() 6\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((double)rsz2.bit.VRSZM / rsz2.bit.VRSZN > 8){
		Im_DISP_Check_Point(("CP:im_disp_param_check_resize() 7\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((rsz0 == E_IM_DISP_RSZSL_PADDING_THINNING) && (rsz2.bit.VRSZOF != 0)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_resize() 8\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((double)rsz2.bit.VRSZM / rsz2.bit.VRSZN == 1.0) && (rsz2.bit.VRSZOF != 0)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_resize() 9\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (rsz2.bit.VRSZOF >= rsz2.bit.VRSZM){
		Im_DISP_Check_Point(("CP:im_disp_param_check_resize() 10\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((rsz0 == E_IM_DISP_RSZSL_PADDING_THINNING) && (rsz3.bit.HCSTA != 0)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_resize() 11\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((rsz0 == E_IM_DISP_RSZSL_PADDING_THINNING) && (rsz3.bit.VCSTA != 0)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_resize() 12\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check warning parameter.
@param[in]	warning			Warning processing data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_warning(T_IM_DISP_WARNING const *const warning)
{
	INT32 ret = D_DDIM_OK;

	if (warning->lyw0th.bit.YWTHH < warning->lyw0th.bit.YWTHL) {
		Im_DISP_Check_Point(("CP:im_disp_param_check_warning() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (warning->lyw1th.bit.YWTHH < warning->lyw1th.bit.YWTHL) {
		Im_DISP_Check_Point(("CP:im_disp_param_check_warning() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((warning->lywctl.bit.YWSL == E_IM_DISP_YWSL_BRIGHTNESS_SPECIFIED_COLOR) ||
		(warning->lywctl.bit.YWSL == E_IM_DISP_YWSL_BRIGHTNESS_ZEBRA)) {

		if ((warning->lyw0st == E_IM_DISP_YWMD_G) || (warning->lyw0st == E_IM_DISP_YWMD_B)) {
			Im_DISP_Check_Point(("CP:im_disp_param_check_warning() 3\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if ((warning->lyw1st == E_IM_DISP_YWMD_G) || (warning->lyw1st == E_IM_DISP_YWMD_B)) {
			Im_DISP_Check_Point(("CP:im_disp_param_check_warning() 4\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
	}
	if ((warning->lbost != D_IM_DISP_BOMD_MASTER) && (warning->lbost != D_IM_DISP_BOMD_SLAVE)) {
		Im_DISP_Check_Point(("CP:im_disp_param_check_warning() 5\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check blend order parameter.
@param[in]	bldctl			Blend order data.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_blend(U_IM_DISP_BLDCTL bldctl)
{
	INT32 ret = D_DDIM_OK;

	if (bldctl.bit.BLD1 == bldctl.bit.BLD2){
		Im_DISP_Check_Point(("CP:im_disp_param_check_blend() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bldctl.bit.BLD1 == bldctl.bit.BLD3){
		Im_DISP_Check_Point(("CP:im_disp_param_check_blend() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bldctl.bit.BLD1 == bldctl.bit.BLD4){
		Im_DISP_Check_Point(("CP:im_disp_param_check_blend() 3\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bldctl.bit.BLD2 == bldctl.bit.BLD3){
		Im_DISP_Check_Point(("CP:im_disp_param_check_blend() 4\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bldctl.bit.BLD2 == bldctl.bit.BLD4){
		Im_DISP_Check_Point(("CP:im_disp_param_check_blend() 5\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bldctl.bit.BLD3 == bldctl.bit.BLD4){
		Im_DISP_Check_Point(("CP:im_disp_param_check_blend() 6\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check grid parameter.
@param[in]	grid			Grid data.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_grid(T_IM_DISP_GRID const *const grid)
{
	INT32 ret = D_DDIM_OK;

	if ((grid->ghdsta.bit.DSH & 0x0001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grid() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((grid->ghdsta.bit.DSV & 0x0001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grid() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((grid->gvdsta.bit.DSH & 0x0001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grid() 3\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((grid->gvdsta.bit.DSV & 0x0001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grid() 4\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((grid->glength.bit.GHLEN & 0x0001) != 0) || (grid->glength.bit.GHLEN < 8)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grid() 5\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((grid->glength.bit.GVLEN & 0x0001) != 0) || (grid->glength.bit.GVLEN < 8)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grid() 6\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((grid->gwidth.bit.GHWID & 0x01) != 0) || (grid->gwidth.bit.GHWID < 2)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grid() 7\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((grid->gwidth.bit.GVWID & 0x01) != 0) || (grid->gwidth.bit.GVWID < 2)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grid() 8\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((grid->gitvl.bit.GHITV & 0x0001) != 0) || (grid->gitvl.bit.GHITV < grid->gwidth.bit.GHWID + 2)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grid() 9\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((grid->gitvl.bit.GVITV & 0x0001) != 0) || (grid->gitvl.bit.GVITV < grid->gwidth.bit.GVWID + 2)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grid() 10\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check face frame parameter.
@param[in]	face			Face frame data parameter.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp_param_check_face_frame(T_IM_DISP_FACE_FRAME_PARAM const *const face)
{
	INT32 ret = D_DDIM_OK;

	if ((face->ffdsta.bit.DSH & 0x0001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_face_frame() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((face->ffdsta.bit.DSV & 0x0001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_face_frame() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((face->ffsize.bit.FFHSZ & 0x0001) != 0) || (face->ffsize.bit.FFHSZ < 8)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_face_frame() 3\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((face->ffsize.bit.FFVSZ & 0x0001) != 0) || (face->ffsize.bit.FFVSZ < 8)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_face_frame() 4\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((face->ffwidth.bit.FFHWID & 0x0001) != 0) || (face->ffwidth.bit.FFHWID < 2)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_face_frame() 5\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((face->ffwidth.bit.FFVWID & 0x0001) != 0) || (face->ffwidth.bit.FFVWID < 2)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_face_frame() 6\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check top face frame parameter.
@param[in]	msff			FFDISPEN.MSFF: Top face frame setting register.<br>
							Value range:0~15 (face frame 0 ~ face frame 15)
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
 INT32 im_disp_param_check_top_face(BYTE msff)
{
	INT32 ret = D_DDIM_OK;

	if (msff >= D_IM_DISP_FACE_FRAME_COUNT) {
		Im_DISP_Check_Point(("CP:im_disp_param_check_top_face() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check input data transfer of a OSD layer parameter.
@param[in]	gridt			Input data forwarding setting register.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_gridt(U_IM_DISP_GRIDT gridt)
{
	INT32 ret = D_DDIM_OK;

	if (gridt.bit.IFMT > D_IM_DISP_GRIDT_IFMT_YCC422_A8){
		Im_DISP_Check_Point(("CP:im_disp_param_check_gridt() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check OSD data territory size parameter.
@param[in]	grtisize	Width and height of OSD data territory.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_grtisize(U_IM_DISP_SIZE grtisize)
{
	INT32 ret = D_DDIM_OK;

	if (((grtisize.size.width & 0x0001) != 0) || (grtisize.size.width < 8)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grtisize() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (((grtisize.size.lines & 0x0001) != 0) || (grtisize.size.lines < 8)){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grtisize() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check display position for OSD parameter.
@param[in]	grtdsta		Display position.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_grtdsta(U_IM_DISP_DSTA grtdsta)
{
	INT32 ret = D_DDIM_OK;

	if ((grtdsta.bit.DSH & 0x0001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grtdsta() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((grtdsta.bit.DSV & 0x0001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grtdsta() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check input data's parameter.
@param[in]	ipo				Input data order.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_gripo(U_IM_DISP_GRIPO ipo)
{
	INT32 ret = D_DDIM_OK;

	if (ipo.bit.IPO1 == ipo.bit.IPO2){
		Im_DISP_Check_Point(("CP:im_disp_param_check_gripo() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (ipo.bit.IPO1 == ipo.bit.IPO3){
		Im_DISP_Check_Point(("CP:im_disp_param_check_gripo() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (ipo.bit.IPO1 == ipo.bit.IPO4){
		Im_DISP_Check_Point(("CP:im_disp_param_check_gripo() 3\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (ipo.bit.IPO2 == ipo.bit.IPO3){
		Im_DISP_Check_Point(("CP:im_disp_param_check_gripo() 4\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (ipo.bit.IPO2 == ipo.bit.IPO4){
		Im_DISP_Check_Point(("CP:im_disp_param_check_gripo() 5\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (ipo.bit.IPO3 == ipo.bit.IPO4){
		Im_DISP_Check_Point(("CP:im_disp_param_check_gripo() 6\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check input data size of OSD parameter.
@param[in]	grisize				Width and height of input data buffer.<br>
@param[in]	input_size_count	input_size's number.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_grisize(const U_IM_DISP_SIZE grisize[], UINT32 input_size_count)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

	for(loop = input_size_count - 1; loop >= 0; loop--) {
		if (((grisize[loop].size.width & 0x0003) != 0) || (grisize[loop].size.width < 8)){
			Im_DISP_Check_Point(("CP:im_disp_param_check_grisize() 1 (area=%d)\n", loop));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (((grisize[loop].size.lines & 0x0001) != 0) || (grisize[loop].size.lines < 8)){
			Im_DISP_Check_Point(("CP:im_disp_param_check_grisize() 2 (area=%d)\n", loop));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
	}
	return ret;
}

/**
Check OSD input data address parameter.
@param[in]	address			OSD start address.<br>
							Value range:0x00000000~0xFFFFFFFF (8-bytel unit)<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_grsa(ULONG address)
{
	INT32 ret = D_DDIM_OK;

	if ((address & 0x00000007) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grsa() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check horizontal global area width parameter.
@param[in]	grhga			Horizontal global area width.<br>
							Value range:8~65528 (8-bytel unit)<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_grhga(ULONG grhga)
{
	INT32 ret = D_DDIM_OK;

	if (grhga == 0) {
		Im_DISP_Check_Point(("CP:im_disp_param_check_grhga() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (grhga > 0xFFF8) {
		Im_DISP_Check_Point(("CP:im_disp_param_check_grhga() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((grhga & 0x00000007) != 0) {
		Im_DISP_Check_Point(("CP:im_disp_param_check_grhga() 3\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check input start position parameter.
@param[in]	position		Input start position.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_grdsta(U_IM_DISP_DSTA grdsta)
{
	INT32 ret = D_DDIM_OK;

	if ((grdsta.bit.DSH & 0x0001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grdsta() 1\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((grdsta.bit.DSV & 0x0001) != 0){
		Im_DISP_Check_Point(("CP:im_disp_param_check_grdsta() 2\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	return ret;
}

/**
Check control output parameter.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	ctrl			Setting of main data input block.<br>
							It is possible to rewrite it while main data input block is operating.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_ctrl_main_layer(E_IM_DISP_SEL block, T_IM_DISP_CTRL_MAIN_LAYER const *const ctrl)
{
	INT32 ret = D_DDIM_OK;

	if(ctrl != NULL){
		if (im_disp_param_check_lidt(block, ctrl->lidt) != D_DDIM_OK) {
			Ddim_Print(("E:Im_DISP_Ctrl_Main_Layer: LIDT parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (im_disp_param_check_lisize(ctrl->lisize) != D_DDIM_OK) {
			Ddim_Print(("E:Im_DISP_Ctrl_Main_Layer: LISIZE parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (im_disp_param_check_ldsta(ctrl->ldsta) != D_DDIM_OK){
			Ddim_Print(("E:Im_DISP_Ctrl_Main_Layer: LDSTA parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (im_disp_param_check_lfd(ctrl->y_hga, ctrl->c_hga) != D_DDIM_OK){
			Ddim_Print(("E:Im_DISP_Ctrl_Main_Layer: LYHGA/LCHGA parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (im_disp_param_check_resize(ctrl->lrsz0, ctrl->lrsz1, ctrl->lrsz2, ctrl->lrsz3) != D_DDIM_OK){
			Ddim_Print(("E:Im_DISP_Ctrl_Main_Layer: LHRSZ0/LHRSZ1/LVRSZ parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (im_disp_param_check_warning(&(ctrl->warning)) != D_DDIM_OK) {
			Ddim_Print(("E:Im_DISP_Ctrl_Main_Layer: LYWTH parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
	}
	return ret;
}

/**
Check control output parameter.
@param[in]	block				Common block selection.<br>
								<ul><li>@ref E_IM_DISP_HDMI
									<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	ctrl_trg_limit		Setting of data output block.<br>
								It is not possible to rewrite it while data output block is operating.<br>
@param[in]	ctrl				Setting of data output block.<br>
								It is possible to rewrite it while data output block is operating.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
INT32 im_disp_param_check_ctrl_output(E_IM_DISP_SEL block, T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT const *const ctrl_trg_limit, T_IM_DISP_CTRL_OUTPUT const *const ctrl)
{
	INT32 ret = D_DDIM_OK;
#if 0	// skip for HDMI
	ULONG	cycle;
#endif
	INT32	loop;
	ULONG	ohsize, ovsize, mode;
	ULONG	con, ifs, veps, vens;

	im_disp_pclk_on(im_disp_new());
	ohsize = IO_DISP.MAIN[block].DCORE.OHSIZE.word;
	ovsize = IO_DISP.MAIN[block].DCORE.OVSIZE.word;
	mode = IO_DISP.MAIN[block].DCORE.DOMD.bit.MODE;
	con  = IO_DISP.MAIN[block].DCORE.TOCTL.bit.CON;
	ifs  = IO_DISP.MAIN[block].DCORE.IFS.bit.IFS;
	veps = IO_DISP.MAIN[block].DCORE.POLSEL.bit.VEPS;
	vens = IO_DISP.MAIN[block].DCORE.VRFCTL.bit.VENS;
	im_disp_pclk_off(im_disp_new());
	if(ctrl_trg_limit != NULL){
		if (ctrl_trg_limit->tsl == D_IM_DISP_TSL_PROGRESSIVE){
#if 0	// skip for AUO LCD
			if (ctrl_trg_limit->vcyc.bit.VCYC1 < ctrl_trg_limit->vblk.bit.VBLK1 + ctrl_trg_limit->ovsize + 1){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 1\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: VCYC1 parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
			if (ctrl_trg_limit->vcyc.bit.VCYC2 < ctrl_trg_limit->vblk.bit.VBLK2 + ctrl_trg_limit->ovsize + 1){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 2\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: VCYC2 parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
#endif
		}
		else{
#if 0	// skip for HDMI
			if (ctrl_trg_limit->vcyc.bit.VCYC1 < ctrl_trg_limit->vblk.bit.VBLK1 + (ctrl_trg_limit->ovsize / 2) + 1){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 3\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: VCYC1 parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
			if (ctrl_trg_limit->vcyc.bit.VCYC2 < ctrl_trg_limit->vblk.bit.VBLK2 + (ctrl_trg_limit->ovsize / 2) + 1){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 4\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: VCYC2 parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
#endif
		}
		switch(ctrl_trg_limit->domd.bit.MODE){
			case D_IM_DISP_MODE_RGB888_8BIT_2:
#if 0	// skip for HDMI
				cycle = ctrl_trg_limit->ohsize * 3;
#endif
				break;
			case D_IM_DISP_MODE_RGB888_8BIT_3:
			case D_IM_DISP_MODE_YCC422_8BIT:
#if 0	// skip for HDMI
				cycle = ctrl_trg_limit->ohsize * 2;
#endif
				break;
			case D_IM_DISP_MODE_YCC420_24BIT:
			case D_IM_DISP_MODE_YCC420_30BIT:
#if 0	// skip for HDMI
				cycle = ctrl_trg_limit->ohsize / 2;
#endif
				break;
			case D_IM_DISP_MODE_RGB888_24BIT:
			case D_IM_DISP_MODE_RGB888_30BIT:
			case D_IM_DISP_MODE_RGB888_36BIT:
			case D_IM_DISP_MODE_RGB888_8BIT_1:
			case D_IM_DISP_MODE_RGB565_16BIT:
			case D_IM_DISP_MODE_RGB666_18BIT:
			case D_IM_DISP_MODE_YCC422_16BIT:
			case D_IM_DISP_MODE_YCC444_24BIT:
			case D_IM_DISP_MODE_YCC422_20BIT:
			case D_IM_DISP_MODE_YCC422_24BIT:
			case D_IM_DISP_MODE_DEEP_YCC444_30BIT:
			case D_IM_DISP_MODE_DEEP_YCC444_36BIT:
			case D_IM_DISP_MODE_GENERAL_10BIT_1:
			case D_IM_DISP_MODE_GENERAL_10BIT_2:
#if 0	// skip for HDMI
				cycle = ctrl_trg_limit->ohsize;
#endif
				break;
			default:
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 5\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: DOMD parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
		}
#if 0	// skip for HDMI
		if (ctrl_trg_limit->hcyc < ctrl_trg_limit->hblk + cycle + 8){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 6\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: HCYC parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
#endif
#if 0	// skip for HDMI
		if (ctrl_trg_limit->ovpw.bit.OVPW == 0){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 8\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: OVPW parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (ctrl_trg_limit->hpw == 0){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 9\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: HPW parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if ((ctrl_trg_limit->vblk.bit.VBLK1 == 0) || (ctrl_trg_limit->vblk.bit.VBLK2 == 0)){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 10\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: VBLK parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
#endif
		if (ctrl_trg_limit->hdly == 0){
#if 0	// skip for CASIO LCD
			if ((ctrl_trg_limit->hblk < 16)){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 11\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: HBLK parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
#endif
		}
		else{
			if ((ctrl_trg_limit->hblk < 8)){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 12\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: HBLK parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
		}
		if (ctrl_trg_limit->vdly > (ctrl_trg_limit->hcyc / 2 - 1)){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 13\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: VDLY parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (ctrl_trg_limit->hdly > (ctrl_trg_limit->hblk - 8)){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 14\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: HDLY parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if ((ctrl_trg_limit->tsl == D_IM_DISP_TSL_INTERLACE) && ((ctrl_trg_limit->ovsize & 0x00000001) != 0)){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 15\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: OVSIZE parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (ctrl_trg_limit->ohsize < 0x00000100){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 16\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: OHSIZE parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if ((ctrl_trg_limit->domd.bit.MODE == D_IM_DISP_MODE_YCC420_24BIT) ||
			(ctrl_trg_limit->domd.bit.MODE == D_IM_DISP_MODE_YCC420_30BIT)) {
			if ((ctrl_trg_limit->ovsize & 0x00000001) != 0){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 17\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: OVSIZE parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
			if ((ctrl_trg_limit->ohsize & 0x00000001) != 0){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 18\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: OHSIZE parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
		}
		ohsize = ctrl_trg_limit->ohsize;
		ovsize = ctrl_trg_limit->ovsize;
		mode = ctrl_trg_limit->domd.bit.MODE;
		con  = ctrl_trg_limit->toctl.bit.CON;
		veps = ctrl_trg_limit->polsel.bit.VEPS;
		vens = ctrl_trg_limit->vrfctl;
	}
	if(ctrl != NULL){
		if (ctrl->clbhsize * 16 < ohsize) {
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 19\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: CLBHSIZE parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (im_disp_param_check_blend(ctrl->bldctl) != D_DDIM_OK) {
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 20\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: BLDCTL parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (mode != D_IM_DISP_MODE_RGB888_24BIT){
			if (ctrl->doctl1.bit.ODO1 == D_IM_DISP_ENABLE_ON){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 21\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: DOCTL1 parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
			if (ctrl->doctl1.bit.ODO2 == D_IM_DISP_ENABLE_ON){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 22\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: DOCTL1 parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
			if (ctrl->doctl1.bit.ODE1 == D_IM_DISP_ENABLE_ON){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 23\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: DOCTL1 parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
			if (ctrl->doctl1.bit.ODE2 == D_IM_DISP_ENABLE_ON){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 24\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: DOCTL1 parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
		}
		if ((mode != D_IM_DISP_MODE_YCC422_8BIT) &&
			(mode != D_IM_DISP_MODE_YCC422_16BIT) &&
			(mode != D_IM_DISP_MODE_YCC444_24BIT) &&
			(mode != D_IM_DISP_MODE_YCC422_20BIT) &&
			(mode != D_IM_DISP_MODE_YCC422_24BIT) &&
			(mode != D_IM_DISP_MODE_DEEP_YCC444_30BIT) &&
			(mode != D_IM_DISP_MODE_DEEP_YCC444_36BIT) &&
			(mode != D_IM_DISP_MODE_DUAL_YCC444_12BIT) &&
			(mode != D_IM_DISP_MODE_YCC420_24BIT) &&
			(mode != D_IM_DISP_MODE_YCC420_30BIT)){
			if (ctrl->doctl2.bit.CLVS != D_IM_DISP_CLVS_NORMAL){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 25\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: DOCTL2 parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
		}
		if ((mode != D_IM_DISP_MODE_YCC422_8BIT) &&
			(mode != D_IM_DISP_MODE_YCC422_16BIT) &&
			(mode != D_IM_DISP_MODE_YCC422_20BIT) &&
			(mode != D_IM_DISP_MODE_YCC422_24BIT) &&
			(mode != D_IM_DISP_MODE_YCC420_24BIT) &&
			(mode != D_IM_DISP_MODE_YCC420_30BIT)){
			if (ctrl->doctl2.bit.CTOH != D_IM_DISP_CTOH_LEFT){
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 26\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: DOCTL2 parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
		}
		for(loop = D_IM_DISP_FACE_FRAME_COUNT - 1; loop >= 0 ; loop--) {
			if (im_disp_param_check_face_frame(&(ctrl->face.param[loop])) != D_DDIM_OK) {
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 27\n"));
				Ddim_Print(("E:im_disp1_ctrl_output: FFDSTA/FFSIZE/FFWIDTH parameter error\n"));
				return D_IM_DISP_INPUT_PARAM_ERROR;
			}
		}
		if (im_disp_param_check_top_face(ctrl->face.msff) != D_DDIM_OK) {
				Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() 28\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: FFDISPEN.MSFF parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
	}
	if(ifs == D_IM_DISP_IFS_HDMI){
		if ((mode != D_IM_DISP_MODE_RGB888_24BIT) &&
			(mode != D_IM_DISP_MODE_RGB888_30BIT) &&
			(mode != D_IM_DISP_MODE_RGB888_36BIT) &&
			(mode != D_IM_DISP_MODE_YCC422_16BIT) &&
			(mode != D_IM_DISP_MODE_YCC444_24BIT) &&
			(mode != D_IM_DISP_MODE_YCC422_20BIT) &&
			(mode != D_IM_DISP_MODE_YCC422_24BIT) &&
			(mode != D_IM_DISP_MODE_DEEP_YCC444_30BIT) &&
			(mode != D_IM_DISP_MODE_DEEP_YCC444_36BIT) &&
			(mode != D_IM_DISP_MODE_YCC420_24BIT) &&
			(mode != D_IM_DISP_MODE_YCC420_30BIT) &&
			(mode != D_IM_DISP_MODE_GENERAL_10BIT_1) &&
			(mode != D_IM_DISP_MODE_GENERAL_10BIT_2)){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : HDMI 1\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: DOMD parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (veps != D_IM_DISP_POLARITY_POSITIVE){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : HDMI 2\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: POLSEL parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (vens != D_IM_DISP_VENS_H_ENABLE){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : HDMI 3\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: VRFCTL parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (ovsize > 0x2000){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : HDMI 4\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: OVSIZE parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (ohsize > 0x1000){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : HDMI 5\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: OHSIZE parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (con != D_IM_DISP_CON_INTERNAL){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : HDMI 6\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: TOCTL parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
	}
	else if(ifs == D_IM_DISP_IFS_LCD){
		if ((mode != D_IM_DISP_MODE_RGB888_24BIT) &&
			(mode != D_IM_DISP_MODE_RGB888_8BIT_1) &&
			(mode != D_IM_DISP_MODE_RGB888_8BIT_2) &&
			(mode != D_IM_DISP_MODE_RGB888_8BIT_3) &&
			(mode != D_IM_DISP_MODE_RGB565_16BIT) &&
			(mode != D_IM_DISP_MODE_RGB666_18BIT) &&
			(mode != D_IM_DISP_MODE_YCC422_8BIT) &&
			(mode != D_IM_DISP_MODE_YCC422_16BIT)){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : LCD 1\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: DOMD parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (con != D_IM_DISP_CON_EXTERNAL){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : LCD 2\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: TOCTL parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (ovsize > 0x2000){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : LCD 3\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: OVSIZE parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (ohsize > 0x780){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : LCD 4\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: OHSIZE parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (ctrl->doctl2.bit.CTOV != D_IM_DISP_CTOV_TOP){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : LCD 5\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: DOCTL2.CTOV parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
	}
	else if(ifs == D_IM_DISP_IFS_MIPI){
		if ((mode != D_IM_DISP_MODE_RGB888_24BIT) &&
			(mode != D_IM_DISP_MODE_RGB565_16BIT) &&
			(mode != D_IM_DISP_MODE_RGB666_18BIT)){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : MIPI 1\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: DOMD parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (con != D_IM_DISP_CON_INTERNAL){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : MIPI 2\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: TOCTL parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (ovsize > 0x2000){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : MIPI 3\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: OVSIZE parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (ohsize > 0x780){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : MIPI 4\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: OHSIZE parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
		if (ctrl->doctl2.bit.CTOV != D_IM_DISP_CTOV_TOP){
			Im_DISP_Check_Point(("CP:im_disp_param_check_ctrl_output() : MIPI 5\n"));
			Ddim_Print(("E:im_disp1_ctrl_output: DOCTL2.CTOV parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
	}
	return ret;
}
#endif // CO_PARAM_CHECK

ImDisp8 *im_disp8_new(void)
{
	ImDisp8* self = k_object_new_with_private(IM_TYPE_DISP8,sizeof(ImDisp8Private));
	return self;
}
