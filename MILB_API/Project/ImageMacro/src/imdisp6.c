/*
 * imdisp6.c
 *
 *  Created on: 2020年8月8日
 *      Author: sns
 */
#include "imdisp.h"
#include "imdisp6.h"

#include "jdsdisp3a.h"

#include "dd_arm.h"
#include "ddim_user_custom.h"
#include <stddef.h>
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImDisp6, im_disp6)
#define IM_DISP6_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp6Private,IM_TYPE_DISP6))


struct _ImDisp6Private
{
	int a;
};

static void im_disp6_constructor(ImDisp6 *self)
{
//	ImDisp6Private *priv = IM_DISP6_GET_PRIVATE(self);
}

static void im_disp6_destructor(ImDisp6 *self)
{
//	ImDisp6Private *priv = IM_DISP6_GET_PRIVATE(self);
}


/* Set input start position.
*/
INT32 im_disp6_set_osd_display_position(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, U_IM_DISP_DSTA position)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp6_set_osd_display_position: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bank_no >= ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT) {
		Ddim_Print(("E:im_disp6_set_osd_display_position: bank_no parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_grdsta(position) != D_DDIM_OK) {
		Ddim_Print(("E:im_disp6_set_osd_display_position: GRDSTA parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// Set GRDSTA
			IO_DISP.MAIN[block].GRCH[loop].GRDSTA[bank_no].word = position.word;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get input start position.
*/
INT32 im_disp6_get_osd_display_position(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, U_IM_DISP_DSTA* position)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (position == NULL) {
		Ddim_Print(("E:im_disp6_get_osd_display_position: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bank_no >= ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT) {
		Ddim_Print(("E:im_disp6_get_osd_display_position: bank_no parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp6_get_osd_display_position: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set layer index
	if (layer == E_IM_DISP_SEL_LAYER_OSD_0) {
		layer_index = 0;
	}
	else {
		layer_index = 1;
	}

	// Get GRDSTA
	position->word = IO_DISP.MAIN[block].GRCH[layer_index].GRDSTA[bank_no].word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set GR's horizontal rectangle to showing or hiden.
*/
INT32 im_disp6_set_osd_area_enable(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG area_enable)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp6_set_osd_area_enable: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// Set GRAREN
			IO_DISP.MAIN[block].GRCH[loop].GRAREN.word = area_enable;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get GR's horizontal rectangle to showing or hiden.
*/
INT32 im_disp6_get_osd_area_enable(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG *area_enable)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (area_enable == NULL) {
		Ddim_Print(("E:im_disp6_get_osd_area_enable: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp6_get_osd_area_enable: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set layer index
	if (layer == E_IM_DISP_SEL_LAYER_OSD_0) {
		layer_index = 0;
	}
	else {
		layer_index = 1;
	}

	// Get GRAREN
	*area_enable = IO_DISP.MAIN[block].GRCH[layer_index].GRAREN.bit.AREN;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set blink method selection.
*/
INT32 im_disp6_set_osd_blink(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG blink)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp6_set_osd_blink: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// Set GRBSL
			IO_DISP.MAIN[block].GRCH[loop].GRBSL.word = blink;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get blink method selection.
*/
INT32 im_disp6_get_osd_blink(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG *blink)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (blink == NULL) {
		Ddim_Print(("E:im_disp6_get_osd_blink: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp6_get_osd_blink: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set layer index
	if (layer == E_IM_DISP_SEL_LAYER_OSD_0) {
		layer_index = 0;
	}
	else {
		layer_index = 1;
	}

	// Get GRBSL
	*blink = IO_DISP.MAIN[block].GRCH[layer_index].GRBSL.bit.BSL;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set GR's blink period.
*/
INT32 im_disp6_set_osd_blink_timer(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_GRBLINK grblink)
{
	INT32 layer_index;
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp6_set_osd_blink_timer: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (layer_index = 0; layer_index < 2; layer_index++) {
		if ((layer & osd_layer_id[layer_index]) == osd_layer_id[layer_index]) {
			// Set GRBLINK
			for(loop = D_IM_DISP_GRBLINK_SIZE - 1; loop >= 0; loop--) {
				IO_DISP.MAIN[block].GRCH[layer_index].GRBLINK.word[loop] = grblink.word[loop];
			}
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get GR's blink period.
*/
INT32 im_disp6_get_osd_blink_timer(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_GRBLINK *grblink)
{
	INT32 layer_index;
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (grblink == NULL) {
		Ddim_Print(("E:im_disp6_get_osd_blink_timer: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp6_get_osd_blink_timer: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set layer index
	if (layer == E_IM_DISP_SEL_LAYER_OSD_0) {
		layer_index = 0;
	}
	else {
		layer_index = 1;
	}

	// Get GRBLINK
	for(loop = D_IM_DISP_GRBLINK_SIZE - 1; loop >= 0; loop--) {
		grblink->word[loop] = IO_DISP.MAIN[block].GRCH[layer_index].GRBLINK.word[loop];
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set GR's blink sync.
*/
INT32 im_disp6_set_osd_blink_sync(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG grbinit, ULONG grbitrg)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp6_set_osd_blink_sync: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (grbinit > 0x03FF) {
		Ddim_Print(("E:im_disp6_set_osd_blink_sync: parameter error (GRBINIT)\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((grbitrg != D_IM_DISP_BITRG_NON) &&
		(grbitrg != D_IM_DISP_BITRG_WRITE_SYNC_WAIT) &&
		(grbitrg != D_IM_DISP_BITRG_READ_STOP) &&
		(grbitrg != D_IM_DISP_BITRG_READ_SYNC_WAIT)) {
		Ddim_Print(("E:im_disp6_set_osd_blink_sync: parameter error (GRBITRG)\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (layer_index = 0; layer_index < 2; layer_index++) {
		if ((layer & osd_layer_id[layer_index]) == osd_layer_id[layer_index]) {
			// Set GRBINIT
			IO_DISP.MAIN[block].GRCH[layer_index].GRBINIT.bit.BINIT = grbinit;

			// Set GRBITRG
			if ((grbitrg == D_IM_DISP_BITRG_WRITE_SYNC_WAIT) &&
				(IO_DISP.MAIN[block].GRCH[layer_index].GRBITRG.bit.BITRG != D_IM_DISP_BITRG_READ_SYNC_WAIT))
			{
				IO_DISP.MAIN[block].GRCH[layer_index].GRBITRG.bit.BITRG = grbitrg;
			}
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get GR's blink sync.
*/
INT32 im_disp6_get_osd_blink_sync(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG* grbinit, ULONG* grbitrg)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((grbinit == NULL) || (grbitrg == NULL)) {
		Ddim_Print(("E:im_disp6_get_osd_blink_sync: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp6_get_osd_blink_sync: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set layer index
	if (layer == E_IM_DISP_SEL_LAYER_OSD_0) {
		layer_index = 0;
	}
	else {
		layer_index = 1;
	}
	// Get GRBINIT/GRBITRG
	*grbinit = IO_DISP.MAIN[block].GRCH[layer_index].GRBINIT.bit.BINIT;
	*grbitrg = IO_DISP.MAIN[block].GRCH[layer_index].GRBITRG.bit.BITRG;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set resize value.
*/
INT32 im_disp6_set_osd_resize(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, T_IM_DISP_RESIZE const *const resize)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (resize == NULL) {
		Ddim_Print(("E:im_disp6_set_osd_resize: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp6_set_osd_resize: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_resize(resize->rsz0, resize->rsz1, resize->rsz2, resize->rsz3) != D_DDIM_OK){
		Ddim_Print(("E:im_disp6_set_osd_resize: GRHRSZ0/GRHRSZ1/GRVRSZ parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// Set GRRSZ0/GRRSZ1/GRRSZ2/GRRSZ3
			IO_DISP.MAIN[block].GRCH[loop].GRRSZ0.word = resize->rsz0;
			IO_DISP.MAIN[block].GRCH[loop].GRRSZ1.word = resize->rsz1.word;
			IO_DISP.MAIN[block].GRCH[loop].GRRSZ2.word = resize->rsz2.word;
			IO_DISP.MAIN[block].GRCH[loop].GRRSZ3.word = resize->rsz3.word;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get resize value.
*/
INT32 im_disp6_get_osd_resize(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, T_IM_DISP_RESIZE *const resize)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (resize == NULL) {
		Ddim_Print(("E:im_disp6_get_osd_resize: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp6_get_osd_resize: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set layer index
	if (layer == E_IM_DISP_SEL_LAYER_OSD_0) {
		layer_index = 0;
	}
	else {
		layer_index = 1;
	}

	// Get GRRSZ0/GRRSZ1/GRRSZ2/GRRSZ3
	resize->rsz0 = (ImDispEImDispRszsl)IO_DISP.MAIN[block].GRCH[layer_index].GRRSZ0.bit.RSZSL;
	resize->rsz1.word = IO_DISP.MAIN[block].GRCH[layer_index].GRRSZ1.word;
	resize->rsz2.word = IO_DISP.MAIN[block].GRCH[layer_index].GRRSZ2.word;
	resize->rsz3.word = IO_DISP.MAIN[block].GRCH[layer_index].GRRSZ3.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set YCbCr -> RGB matrix data.
*/
INT32 im_disp6_set_osd_matrix(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_GRY2R gry2r[D_IM_DISP_MATRIX_SIZE])
{
	INT32 loop1;
	INT32 loop2;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (gry2r == NULL) {
		Ddim_Print(("E:im_disp6_set_osd_matrix: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp6_set_osd_matrix: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop1 = 0; loop1 < 2; loop1++) {
		if ((layer & osd_layer_id[loop1]) == osd_layer_id[loop1]) {
			// Set GRY2R0~2
			for (loop2 = D_IM_DISP_MATRIX_SIZE - 1; loop2 >= 0; loop2--) {
				IO_DISP.MAIN[block].GRCH[loop1].GRY2R[loop2].word = gry2r[loop2].word;
			}
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get YCbCr -> RGB matrix data.
*/
INT32 im_disp6_get_osd_matrix(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_GRY2R gry2r[D_IM_DISP_MATRIX_SIZE])
{
	INT32 layer_index;
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (gry2r == NULL) {
		Ddim_Print(("E:im_disp6_get_osd_matrix: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp6_get_osd_matrix: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set layer index
	if (layer == E_IM_DISP_SEL_LAYER_OSD_0) {
		layer_index = 0;
	}
	else {
		layer_index = 1;
	}

	// Set GRY2R0~2
	for (loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
		gry2r[loop].word = IO_DISP.MAIN[block].GRCH[layer_index].GRY2R[loop].word;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set GR's Alpha.
*/
INT32 im_disp6_set_osd_alpha(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG alpha)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp6_set_osd_alpha: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// Set GRALP
			IO_DISP.MAIN[block].GRCH[loop].GRALP.word = alpha;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get GR's Alpha.
*/
INT32 im_disp6_get_osd_alpha(ImDisp6 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ULONG* alpha)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (alpha == NULL) {
		Ddim_Print(("E:im_disp6_get_osd_alpha: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp6_get_osd_alpha: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set layer index
	if (layer == E_IM_DISP_SEL_LAYER_OSD_0) {
		layer_index = 0;
	}
	else {
		layer_index = 1;
	}

	// Get GRALP
	*alpha = IO_DISP.MAIN[block].GRCH[layer_index].GRALP.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set Anti-gamma table.
*/
INT32 im_disp6_set_anti_gamma_table(ImDisp6 * self, ImDispEImDispSel block, BYTE surface, T_IM_DISP_ANTI_GAMMA_TBL const *const tbl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (tbl == NULL) {
 		Ddim_Print(("E:im_disp6_set_anti_gamma_table: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((surface != D_IM_DISP_TABLE_SURFACE_A) &&
		(surface != D_IM_DISP_TABLE_SURFACE_B)) {
		Ddim_Print(("E:im_disp6_set_anti_gamma_table: Paramter check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// check trigger.
	if ((IO_DISP.MAIN[block].LCH.LTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		(IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtsl != surface)) {
		// Main data input block is stopped, or specified surface is unused.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());

		// check table surface.
		if (surface == D_IM_DISP_TABLE_SURFACE_A) {
			// Set Anti gamma table (surface A)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.IGTBLA)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		}
		else {
			// Set Anti gamma table (surface B)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.IGTBLB)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		}

		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	else {
		Ddim_Print(("E:im_disp6_set_anti_gamma_table: Main layer busy and specified surface is being used\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}

	im_disp_pclk_off(im_disp_new());

	return  ret;
}

/* Get Anti-gamma table.
*/
INT32 im_disp6_get_anti_gamma_table(ImDisp6 * self, ImDispEImDispSel block, BYTE surface, T_IM_DISP_ANTI_GAMMA_TBL *const tbl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (tbl == NULL) {
		Ddim_Print(("E:im_disp6_get_anti_gamma_table: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((surface != D_IM_DISP_TABLE_SURFACE_A) &&
		(surface != D_IM_DISP_TABLE_SURFACE_B)) {
		Ddim_Print(("E:im_disp6_get_anti_gamma_table: Paramter check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// check trigger.
	if ((IO_DISP.MAIN[block].LCH.LTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		(IO_DISP.MAIN[block].LCH.LTBLASET.bit.igtsl != surface)) {
		// Main data input block is stopped, or specified surface is unused.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());

		// check table surface.
		if (surface == D_IM_DISP_TABLE_SURFACE_A) {
			// Get Anti gamma table (surface A)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.IGTBLA)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		}
		else {
			// Get Anti gamma table (surface B)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.IGTBLB)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		}

		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	else {
		Ddim_Print(("E:im_disp6_get_anti_gamma_table: Main layer busy and specified surface is being used\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set Gamma table (Main data input block).
*/
INT32 im_disp6_set_main_gamma_table(ImDisp6 * self, ImDispEImDispSel block, BYTE surface, T_IM_DISP_GAMMA_TBL_IN const *const tbl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (tbl == NULL) {
		Ddim_Print(("E:im_disp6_set_main_gamma_table: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((surface != D_IM_DISP_TABLE_SURFACE_A) &&
		(surface != D_IM_DISP_TABLE_SURFACE_B)) {
		Ddim_Print(("E:im_disp6_set_main_gamma_table: Paramter check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// check trigger.
	if ((IO_DISP.MAIN[block].LCH.LTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		(IO_DISP.MAIN[block].LCH.LTBLASET.bit.gmtsl != surface)) {
		// Main data input block is stopped, or specified surface is unused.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());

		// check table surface.
		if (surface == D_IM_DISP_TABLE_SURFACE_A) {
			// Set Gamma table (Main data input block, surface A)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.GTBLA)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_IN, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		}
		else {
			// Set Gamma table (Main data input block, surface B)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.GTBLB)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_IN, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		}
		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	else {
		Ddim_Print(("E:im_disp6_set_main_gamma_table: Main layer busy and specified surface is being used\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}

	im_disp_pclk_off(im_disp_new());

	return  ret;
}

/* Get Gamma table (Main data input block).
*/
INT32 im_disp6_get_main_gamma_table(ImDisp6 * self, ImDispEImDispSel block, BYTE surface, T_IM_DISP_GAMMA_TBL_IN *const tbl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (tbl == NULL) {
		Ddim_Print(("E:im_disp6_get_main_gamma_table: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((surface != D_IM_DISP_TABLE_SURFACE_A) &&
		(surface != D_IM_DISP_TABLE_SURFACE_B)) {
		Ddim_Print(("E:im_disp6_get_main_gamma_table: Paramter check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// check trigger.
	if ((IO_DISP.MAIN[block].LCH.LTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		(IO_DISP.MAIN[block].LCH.LTBLASET.bit.gmtsl != surface)) {
		// Main data input block is stopped, or specified surface is unused.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());

		// check table surface.
		if (surface == D_IM_DISP_TABLE_SURFACE_A) {
			// Get Gamma table (Main data input block, surface A)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.GTBLA)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_IN, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		}
		else {
			// Get Gamma table (Main data input block, surface B)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].LCH.GTBLB)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_IN, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		}

		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	else {
		Ddim_Print(("E:im_disp6_get_main_gamma_table: Main layer busy and specified surface is being used\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}

	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set Gamma table (Data output block).
*/
INT32 im_disp6_set_dcore_gamma_table(ImDisp6 * self, ImDispEImDispSel block, BYTE surface, T_IM_DISP_GAMMA_TBL_OUT const *const tbl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (tbl == NULL) {
		Ddim_Print(("E:im_disp6_set_dcore_gamma_table: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((surface != D_IM_DISP_TABLE_SURFACE_A) &&
		(surface != D_IM_DISP_TABLE_SURFACE_B)) {
		Ddim_Print(("E:im_disp6_set_dcore_gamma_table: Paramter check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// check trigger.
	if ((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		(IO_DISP.MAIN[block].DCORE.TBLASET.bit.gmtsl != surface)) {
		// Data output block is stopped, or or specified surface is unused.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());

		// check table surface.
		if (surface == D_IM_DISP_TABLE_SURFACE_A) {
			// Set Gamma table (Data output block, surface A)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.GTBLA)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_OUT, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		}
		else {
			// Set Gamma table (Data output block, surface B)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.GTBLB)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_OUT, ImDisp_E_IM_DISP_ACCESS_GAMMA_SET);
		}

		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	else {
		Ddim_Print(("E:im_disp6_set_dcore_gamma_table: Output layer busy and specified surface is being used\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}

	im_disp_pclk_off(im_disp_new());

	return  ret;
}

/* Get Gamma table (Data output block).
*/
INT32 im_disp6_get_dcore_gamma_table(ImDisp6 * self, ImDispEImDispSel block, BYTE surface, T_IM_DISP_GAMMA_TBL_OUT *const tbl)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (tbl == NULL) {
		Ddim_Print(("E:im_disp6_get_dcore_gamma_table: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}

	if ((surface != D_IM_DISP_TABLE_SURFACE_A) &&
		(surface != D_IM_DISP_TABLE_SURFACE_B)) {
		Ddim_Print(("E:im_disp6_get_dcore_gamma_table: Paramter check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());

	// check trigger.
	if ((IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
		(IO_DISP.MAIN[block].DCORE.TBLASET.bit.gmtsl != surface)) {
		// Data output block is stopped, or or specified surface is unused.

		DDIM_User_AhbReg_SpinLock();
		im_disp_hclk_on(im_disp_new());

		// check table surface.
		if (surface == D_IM_DISP_TABLE_SURFACE_A) {
			// Get Gamma table (Data output block, surface A)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.GTBLA)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_OUT, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		}
		else {
			// Get Gamma table (Data output block, surface B)
			im_disp_access_gamma_table(im_disp_new(),(BYTE*)(tbl), (BYTE*)(&(IO_DISP_TBL.MAIN[block].DCORE.GTBLB)),
										ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_OUT, ImDisp_E_IM_DISP_ACCESS_GAMMA_GET);
		}

		im_disp_hclk_off(im_disp_new());
		DDIM_User_AhbReg_SpinUnLock();
	}
	else {
		Ddim_Print(("E:im_disp6_get_dcore_gamma_table: Output layer busy and specified surface is being used\n"));
		ret = D_IM_DISP_MACRO_BUSY_NG;
	}

	im_disp_pclk_off(im_disp_new());

	return ret;
}

ImDisp6 *im_disp6_new(void)
{
	ImDisp6* self = k_object_new_with_private(IM_TYPE_DISP6,sizeof(ImDisp6Private));
	return self;
}
