/*
 * imdisp5.c
 *
 *  Created on: 2020年8月8日
 *      Author: sns
 */
#include "imdisp.h"
#include "imdisp5.h"

#include "jdsdisp3a.h"

#include "dd_arm.h"
#include "ddim_user_custom.h"
#include <stddef.h>
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImDisp5, im_disp5)
#define IM_DISP5_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp5Private,IM_TYPE_DISP5))


struct _ImDisp5Private
{
	int a;
};

static void im_disp5_constructor(ImDisp5 *self)
{
//	ImDisp5Private *priv = IM_DISP5_GET_PRIVATE(self);
}

static void im_disp5_destructor(ImDisp5 *self)
{
//	ImDisp5Private *priv = IM_DISP5_GET_PRIVATE(self);
}


/* Set face frame data.
*/
INT32 im_disp5_set_face_frame(ImDisp5 * self, ImDispEImDispSel block, UINT32 frame_count, T_IM_DISP_FACE_FRAME const *const face)
{
	INT32 ret = D_DDIM_OK;
	INT32 loop;

#ifdef CO_PARAM_CHECK
	if (face == NULL) {
		Ddim_Print(("E:im_disp5_set_face_frame: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (frame_count > D_IM_DISP_FACE_FRAME_COUNT) {
		Ddim_Print(("E:im_disp5_set_face_frame: frame_count parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	for(loop = frame_count - 1; loop >= 0 ; loop--) {
		if (im_disp_param_check_face_frame(&(face->param[loop])) != D_DDIM_OK) {
			Ddim_Print(("E:im_disp5_set_face_frame: FFDSTA/FFSIZE/FFWIDTH parameter error\n"));
			return D_IM_DISP_INPUT_PARAM_ERROR;
		}
	}
	if (im_disp_param_check_top_face(face->msff) != D_DDIM_OK) {
		Ddim_Print(("E:im_disp5_set_face_frame: FFDISPEN.MSFF parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set FFDSTA/FFSIZE/FFWIDTH/FFCLR
	for(loop = frame_count - 1; loop >= 0 ; loop--) {
		IO_DISP.MAIN[block].DCORE.FFDSTA[loop].word = face->param[loop].ffdsta.word;
		IO_DISP.MAIN[block].DCORE.FFSIZE[loop].word = face->param[loop].ffsize.word;
		IO_DISP.MAIN[block].DCORE.FFWIDTH[loop].word = face->param[loop].ffwidth.word;
		IO_DISP.MAIN[block].DCORE.FFCLR[loop].word = face->param[loop].ffclr.word;
	}
	// Set FFDISPEN/FFDO
	IO_DISP.MAIN[block].DCORE.FFDISPEN.bit.FFDEN = face->ffden;
	IO_DISP.MAIN[block].DCORE.FFDO.bit.MSFF = face->msff;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get face frame data.
*/
INT32 im_disp5_get_face_frame(ImDisp5 * self, ImDispEImDispSel block, T_IM_DISP_FACE_FRAME *const face)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (face == NULL) {
		Ddim_Print(("E:im_disp5_get_face_frame: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get FFDSTA/FFSIZE/FFWIDTH/FFCLR/FFDISPEN
	for (loop = D_IM_DISP_FACE_FRAME_COUNT - 1; loop >= 0; loop--) {
		face->param[loop].ffdsta.word = IO_DISP.MAIN[block].DCORE.FFDSTA[loop].word;
		face->param[loop].ffsize.word = IO_DISP.MAIN[block].DCORE.FFSIZE[loop].word;
		face->param[loop].ffwidth.word = IO_DISP.MAIN[block].DCORE.FFWIDTH[loop].word;
		face->param[loop].ffclr.word = IO_DISP.MAIN[block].DCORE.FFCLR[loop].word;
	}
	// Get FFDISPEN/FFDO
	face->ffden = IO_DISP.MAIN[block].DCORE.FFDISPEN.bit.FFDEN;
	face->msff = IO_DISP.MAIN[block].DCORE.FFDO.bit.MSFF;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set face frame display enable.
*/
INT32 im_disp5_set_face_frame_enable(ImDisp5 * self, ImDispEImDispSel block, UINT64 ffden, BYTE msff)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (im_disp_param_check_top_face(msff) != D_DDIM_OK) {
		Ddim_Print(("E:im_disp5_set_face_frame_enable: FFDISPEN.MSFF parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set FFDISPEN.FFDEN
	IO_DISP.MAIN[block].DCORE.FFDISPEN.bit.FFDEN = ffden;
	// Set FFDO.MSFF
	IO_DISP.MAIN[block].DCORE.FFDO.bit.MSFF = msff;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get face frame display enable.
*/
INT32 im_disp5_get_face_frame_enable(ImDisp5 * self, ImDispEImDispSel block, UINT64 *ffden, BYTE *msff)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((ffden == NULL) || (msff == NULL)) {
		Ddim_Print(("E:im_disp5_get_face_frame_enable: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get FFDISPEN.FFDEN
	*ffden = IO_DISP.MAIN[block].DCORE.FFDISPEN.bit.FFDEN;
	// Get FFDO.MSFF
	*msff = IO_DISP.MAIN[block].DCORE.FFDO.bit.MSFF;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set parameter reflect timing of a OSD layer.
*/
INT32 im_disp5_set_osd_parameter_reflect_timing(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ImDispEImDispRpgtmg timing)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp5_set_osd_parameter_reflect_timing: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// check trigger
			if (IO_DISP.MAIN[block].GRCH[loop].GRTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) {
				// Set GRRPGCTL
				IO_DISP.MAIN[block].GRCH[loop].GRRPGCTL.bit.RPGTMG = timing;
			}
			else {
				Ddim_Print(("E:im_disp5_set_osd_parameter_reflect_timing: OSD-%d layer busy\n", loop));
				ret = D_IM_DISP_MACRO_BUSY_NG;
			}
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get parameter reflect timing of a OSD layer.
*/
INT32 im_disp5_get_osd_parameter_reflect_timing(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ImDispEImDispRpgtmg *timing)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (timing == NULL) {
		Ddim_Print(("E:im_disp5_get_osd_parameter_reflect_timing: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_get_osd_parameter_reflect_timing: layer parameter error\n"));
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

	// Get RPGTMG
	*timing = (ImDispEImDispRpgtmg)IO_DISP.MAIN[block].GRCH[layer_index].GRRPGCTL.bit.RPGTMG;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set input data transfer of a OSD layer.
*/
INT32 im_disp5_set_osd_input_data_transfer(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_GRIDT gridt)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp5_set_osd_input_data_transfer: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_gridt(gridt) != D_DDIM_OK){
		Ddim_Print(("E:im_disp5_set_osd_input_data_transfer: GRIDT parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// Set GRIDT
			IO_DISP.MAIN[block].GRCH[loop].GRIDT.word = gridt.word;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get input data transfer of a OSD layer.
*/
INT32 im_disp5_get_osd_input_data_transfer(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_GRIDT *gridt)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (gridt == NULL) {
		Ddim_Print(("E:im_disp5_get_osd_input_data_transfer: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_get_osd_input_data_transfer: layer parameter error\n"));
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

	// Get GRIDT
	gridt->word = IO_DISP.MAIN[block].GRCH[layer_index].GRIDT.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set OSD data territory size.
*/
INT32 im_disp5_set_osd_territory_size(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_SIZE territory_size)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp5_set_osd_territory_size: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_grtisize(territory_size) != D_DDIM_OK){
		Ddim_Print(("E:im_disp5_set_osd_territory_size: GRTISIZE parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// Set GRTISIZE
			IO_DISP.MAIN[block].GRCH[loop].GRTISIZE.word = territory_size.word;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get OSD data territory size.
*/
INT32 im_disp5_get_osd_territory_size(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_SIZE *territory_size)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (territory_size == NULL) {
		Ddim_Print(("E:im_disp5_get_osd_territory_size: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_get_osd_territory_size: layer parameter error\n"));
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

	// Get GRTISIZE
	territory_size->word = IO_DISP.MAIN[block].GRCH[layer_index].GRTISIZE.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set display position for OSD.
*/
INT32 im_disp5_set_osd_territory_position(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_DSTA position)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp5_set_osd_territory_position: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_grtdsta(position) != D_DDIM_OK){
		Ddim_Print(("E:im_disp5_get_osd_territory_position: GRTDSTA parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// Set GRTDSTA
			IO_DISP.MAIN[block].GRCH[loop].GRTDSTA.word = position.word;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get display position for OSD.
*/
INT32 im_disp5_get_osd_territory_position(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_DSTA* position)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (position == NULL) {
		Ddim_Print(("E:im_disp5_get_osd_territory_position: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_get_osd_territory_position: layer parameter error\n"));
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

	// Get GRTDSTA
	position->word = IO_DISP.MAIN[block].GRCH[layer_index].GRTDSTA.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set input data's order.
*/
INT32 im_disp5_set_osd_ipo(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer,  U_IM_DISP_GRIPO ipo)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_set_osd_ipo: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_gripo(ipo) != D_DDIM_OK){
		Ddim_Print(("E:im_disp5_set_osd_ipo: GRIPO parameter error\n"));
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

	// Set GRIPO
	IO_DISP.MAIN[block].GRCH[layer_index].GRIPO.word = ipo.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get input data's order.
*/
INT32 im_disp5_get_osd_ipo(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer,  U_IM_DISP_GRIPO* ipo)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ipo == NULL) {
		Ddim_Print(("E:im_disp5_get_osd_ipo: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_get_osd_ipo: layer parameter error\n"));
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

	// Get GRIPO
	ipo->word = IO_DISP.MAIN[block].GRCH[layer_index].GRIPO.word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set input data area to access.
*/
INT32 im_disp5_set_osd_area0_switch(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ImDispEImDispInputDataArea area)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp5_set_osd_area0_switch: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// Set GRSCCTL.IDSET
			IO_DISP.MAIN[block].GRCH[loop].GRSCCTL.bit.IDSET = area;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get input data area to access.
*/
INT32 im_disp5_get_osd_area0_switch(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ImDispEImDispInputDataArea *area)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (area == NULL) {
		Ddim_Print(("E:im_disp5_get_osd_area0_switch: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_get_osd_area0_switch: layer parameter error\n"));
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

	// Get GRSCCTL.IDSET
	*area = (ImDispEImDispInputDataArea)IO_DISP.MAIN[block].GRCH[layer_index].GRSCCTL.bit.IDSET;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get input data area inder processing.
*/
INT32 im_disp5_get_osd_area0_monitor(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, ImDispEImDispInputDataArea *area)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (area == NULL) {
		Ddim_Print(("E:im_disp5_get_osd_area0_monitor: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_get_osd_area0_monitor: layer parameter error\n"));
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

	// Get GRSCCTL.IDM
	*area = (ImDispEImDispInputDataArea)IO_DISP.MAIN[block].GRCH[layer_index].GRSCCTL.bit.IDM;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set input data size of OSD.
*/
INT32 im_disp5_set_osd_area_size(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer,
								U_IM_DISP_SIZE input_size[ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT],
								UINT32 input_size_count)
{
	INT32 loop1;
	INT32 loop2;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (input_size == NULL) {
		 Ddim_Print(("E:im_disp5_set_osd_area_size: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp5_set_osd_area_size: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (input_size_count > ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT) {
		Ddim_Print(("E:im_disp5_set_osd_area_size: input_size_count parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_grisize(input_size, input_size_count) != D_DDIM_OK) {
		Ddim_Print(("E:im_disp5_set_osd_area_size: input_size parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop1 = 0; loop1 < 2; loop1++) {
		if ((layer & osd_layer_id[loop1]) == osd_layer_id[loop1]) {
			// Set GRISIZE
			for (loop2 = 0; loop2 <input_size_count; loop2++) {
				IO_DISP.MAIN[block].GRCH[loop1].GRISIZE[loop2].word = input_size[loop2].word;
			}
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get input data size of OSD.
*/
INT32 im_disp5_get_osd_area_size(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_SIZE input_size[ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT])
{
	INT32 layer_index;
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (input_size == NULL) {
		Ddim_Print(("E:im_disp5_get_osd_area_size: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_get_osd_area_size: layer parameter error\n"));
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

	// Get GRISIZE
	for (loop = ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT - 1; loop >= 0; loop--) {
		input_size[loop].word = IO_DISP.MAIN[block].GRCH[layer_index].GRISIZE[loop].word;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Connect OSD input data address with the bank index.
*/
INT32 im_disp5_set_osd_area_addr(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_OSD_SA_BANK_NO bank_no, ULONG address)
{
	INT32 index;
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp5_set_osd_area_addr: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_grsa(address) != D_DDIM_OK){
		Ddim_Print(("E:im_disp5_set_osd_area_addr: GRSA0/GRSA parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			if (bank_no < E_IM_DISP_OSD_SA_BANK_NO_1) {
				// Set GRSA0
				IO_DISP.MAIN[block].GRCH[loop].GRSA0[bank_no].word = address;
			}
			else {
				index = bank_no - E_IM_DISP_OSD_SA_BANK_NO_1;
				// Set GRSA
				IO_DISP.MAIN[block].GRCH[loop].GRSA[index].word = address;
			}
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get OSD input data address of the bank index specified.
*/
INT32 im_disp5_get_osd_area_addr(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_OSD_SA_BANK_NO bank_no, ULONG *address)
{
	INT32 layer_index;
	INT32 index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (address == NULL) {
		Ddim_Print(("E:im_disp5_get_osd_area_addr: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_get_osd_area_addr: layer parameter error\n"));
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

	// Get GRIDT
	if (bank_no < E_IM_DISP_OSD_SA_BANK_NO_1) {
		// GRSA0
		*address = IO_DISP.MAIN[block].GRCH[layer_index].GRSA0[bank_no].word;
	}
	else {
		index = bank_no - E_IM_DISP_OSD_SA_BANK_NO_1;
		// GRSA
		*address = IO_DISP.MAIN[block].GRCH[layer_index].GRSA[index].word;
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Connect OSD input A data address with the bank index.
*/
INT32 im_disp5_set_osd_area_adata_addr(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, ULONG address)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp5_set_osd_area_adata_addr: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bank_no >= ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT) {
		Ddim_Print(("E:im_disp5_set_osd_area_adata_addr: bank_no parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_grsa(address) != D_DDIM_OK){
		Ddim_Print(("E:im_disp5_set_osd_area_adata_addr: GRASA parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// Set GRASA
			IO_DISP.MAIN[block].GRCH[loop].GRASA[bank_no].word = address;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get OSD input A data address of the bank index specified.
*/
INT32 im_disp5_get_osd_area_adata_addr(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, ULONG *address)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (address == NULL) {
		Ddim_Print(("E:im_disp5_get_osd_area_adata_addr: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bank_no >= ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT) {
		Ddim_Print(("E:im_disp5_get_osd_area_adata_addr: bank_no parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_get_osd_area_adata_addr: layer parameter error\n"));
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

	// Get GRASA
	*address = IO_DISP.MAIN[block].GRCH[layer_index].GRASA[bank_no].word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set the horizontal global area width.
*/
INT32 im_disp5_set_osd_lfd(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, ULONG width)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp5_set_osd_lfd: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bank_no >= ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT) {
		Ddim_Print(("E:im_disp5_set_osd_lfd: bank_no parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_grhga(width) != D_DDIM_OK) {
		Ddim_Print(("E:im_disp5_set_osd_lfd: GRHGA parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// Set GRHGA
			IO_DISP.MAIN[block].GRCH[loop].GRHGA[bank_no].word = width;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get the horizontal global area width.
*/
INT32 im_disp5_get_osd_lfd(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, ULONG *width)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (width == NULL) {
		Ddim_Print(("E:im_disp5_get_osd_lfd: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bank_no >= ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT) {
		Ddim_Print(("E:im_disp5_get_osd_lfd: bank_no parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_get_osd_lfd: layer parameter error\n"));
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

	// Get GRHGA
	*width = IO_DISP.MAIN[block].GRCH[layer_index].GRHGA[bank_no].word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Set the A data horizontal global area width.
*/
INT32 im_disp5_set_osd_adata_lfd(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, ULONG width)
{
	INT32 loop;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if ((layer & E_IM_DISP_SEL_LAYER_OSD_ALL) == E_IM_DISP_SEL_LAYER_NONE) {
		Ddim_Print(("E:im_disp5_set_osd_adata_lfd: layer parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bank_no >= ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT) {
		Ddim_Print(("E:im_disp5_set_osd_adata_lfd: bank_no parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (im_disp_param_check_grhga(width) != D_DDIM_OK) {
		Ddim_Print(("E:im_disp5_set_osd_adata_lfd: GRAHGA parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	for (loop = 0; loop < 2; loop++) {
		if ((layer & osd_layer_id[loop]) == osd_layer_id[loop]) {
			// Set GRAHGA
			IO_DISP.MAIN[block].GRCH[loop].GRAHGA[bank_no].word = width;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get the A data horizontal global area width.
*/
INT32 im_disp5_get_osd_adata_lfd(ImDisp5 * self, ImDispEImDispSel block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, ULONG *width)
{
	INT32 layer_index;
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (width == NULL) {
		Ddim_Print(("E:im_disp5_get_osd_adata_lfd: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if (bank_no >= ImDisp_D_IM_DISP_OSD_DISPLAY_AREA_COUNT) {
		Ddim_Print(("E:im_disp5_get_osd_adata_lfd: bank_no parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((layer != E_IM_DISP_SEL_LAYER_OSD_0) && (layer != E_IM_DISP_SEL_LAYER_OSD_1)) {
		Ddim_Print(("E:im_disp5_get_osd_adata_lfd: layer parameter error\n"));
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

	// Get GRAHGA
	*width = IO_DISP.MAIN[block].GRCH[layer_index].GRAHGA[bank_no].word;
	im_disp_pclk_off(im_disp_new());

	return ret;
}

ImDisp5 *im_disp5_new(void)
{
	ImDisp5* self = k_object_new_with_private(IM_TYPE_DISP5,sizeof(ImDisp5Private));
	return self;
}
