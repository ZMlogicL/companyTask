/*
 * improb2b1.c
 *
 *  Created on: 2020年9月4日
 *      Author: sns
 */

#include "impro1.h"
#include "impro.h"
#include "im_pro_common.h"

typedef struct _ImPro1Private ImPro1Private;
 struct _ImPro1Private
{
	int a;
};

K_TYPE_DEFINE_DERIVED(ImPro1, im_pro1, sizeof(ImPro1Private),K_TYPE_OBJECT)
#define IM_PRO1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImPro1Private, IM_TYPE_PRO1))

 static volatile T_IM_PRO_B2BTOP_INFO	gIM_PRO_B2BTOP_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX] = {
 	// E_IM_PRO_UNIT_NUM_1
 	{
 		&IO_PRO.IMG_PIPE[0].B2B.B2BTOP
 	},
 	// E_IM_PRO_UNIT_NUM_2
 	{
 		&IO_PRO.IMG_PIPE[1].B2B.B2BTOP
 	},
 	// E_IM_PRO_BOTH_UNIT
 	{
 		&IO_PRO.IMG_PIPE[2].B2B.B2BTOP
 	},
 };

static void im_pro1_constructor(ImPro1 *self)
{
	//ImPro1Private *priv = IM_PRO1_GET_PRIVATE(self);
}

static void im_pro1_destructor(ImPro1 *self)
{
	//ImPro1Private *priv = IM_PRO1_GET_PRIVATE(self);
}

VOID im_pro_b2btop_init( E_IM_PRO_UNIT_NUM unit_no )
{
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	// Software release
	gIM_PRO_B2BTOP_Reg_Ptr_Tbl[unit_no].reg_ptr->SR.bit.SR = D_IM_PRO_SR_RELEASE;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock
}

INT32 im_pro_b2btop_sw_reset( E_IM_PRO_UNIT_NUM unit_no )
{
#ifdef CO_ACT_PRO_CLOCK
	if (im_pro_b2b_get_stop_all() == FALSE){	//not ALL Stopped
		Ddim_Print(("I:im_pro_b2btop_sw_reset. macro not stopped error. \n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif	/* CO_ACT_PRO_CLOCK */

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	// Software reset
	gIM_PRO_B2BTOP_Reg_Ptr_Tbl[unit_no].reg_ptr->SR.bit.SR = D_IM_PRO_SR_RESET;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_b2btop_control_clock( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_B2BTOP_CLK_TYPE clk_type, UCHAR on_off, UCHAR wait_skip )
{
	UINT32 cpu_clk_hz;
	UINT32 macro_clk_hz;
#ifdef CO_PARAM_CHECK
	if (on_off > D_IM_PRO_CLOCK_OFF){
		Ddim_Assertion(("I:im_pro_b2btop_control_clock error. on_off value over!! (%d)\n", on_off));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else {
		// DO NOTHING
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	switch( clk_type ) {
		case E_IM_PRO_B2BTOP_CLK_TYPE_B2BCLK:
			gIM_PRO_B2BTOP_Reg_Ptr_Tbl[unit_no].reg_ptr->CLKSTP.bit.PSTP1 = ( ( on_off == D_IM_PRO_CLOCK_ON ) ? D_IM_PRO_CLOCK_ON : D_IM_PRO_CLOCK_OFF );
			break;

		default:
			break;
	}
	// waiting for 5 cycle
	if( wait_skip == 0 ) {
		im_pro_get_current_clk_hz( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B, &cpu_clk_hz, &macro_clk_hz );
		im_pro_common_wait_by_clk_cycle( 5, macro_clk_hz, cpu_clk_hz );
#ifndef CO_DEBUG_ON_PC
//			__nop();
#endif
	}
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_b2btop_ctrl( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_B2BTOP_CTRL* ctrl )
{
#ifdef CO_PARAM_CHECK
	if (ctrl == NULL){
		Ddim_Assertion(("I:im_pro_b2btop_ctrl error. ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	gIM_PRO_B2BTOP_Reg_Ptr_Tbl[unit_no].reg_ptr->B2BTOPCTL1.bit.B2BISW	= ctrl->input_mode;
	gIM_PRO_B2BTOP_Reg_Ptr_Tbl[unit_no].reg_ptr->B2BTOPCTL1.bit.CAGSL	= ctrl->cag_target_sel;
	gIM_PRO_B2BTOP_Reg_Ptr_Tbl[unit_no].reg_ptr->B2BTOPCTL2.bit.ORG0	= ctrl->first_pixel[0];
	gIM_PRO_B2BTOP_Reg_Ptr_Tbl[unit_no].reg_ptr->B2BTOPCTL2.bit.ORG1	= ctrl->first_pixel[1];
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_paen( E_IM_PRO_UNIT_NUM unit_no, UCHAR paen_trg )
{
#ifdef CO_PARAM_CHECK
	if( ( paen_trg == 0 ) && ( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFTRG.bit.ELFTRG != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:im_pro_elf_set_paen. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFPAEN.bit.EPAEN = paen_trg;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_ctrl_common( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_COMMON_CTRL* elf_common_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (elf_common_ctrl == NULL){
		Ddim_Assertion(("I:im_pro_elf_ctrl_common error. elf_common_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.ELFPDD		= elf_common_ctrl->pix_padding;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.ELFRNG		= elf_common_ctrl->padding_mode;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.ELFAFS		= elf_common_ctrl->nr_select;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_ctrl( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_CTRL* elf_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (elf_ctrl == NULL){
		Ddim_Assertion(("I:im_pro_elf_ctrl error. elf_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.N1S5EN		= elf_ctrl->cmn1.n1s5_enable;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.N5S9EN		= elf_ctrl->cmn1.n5s9_enable;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.NFS9EN		= elf_ctrl->cmn1.f9_enable;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.NLA0EN		= elf_ctrl->cmn1.a0_enable;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.F5MD		= elf_ctrl->cmn1.f5_filter_mode;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.F9MD		= elf_ctrl->cmn1.f9_filter_mode;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.EFMD		= elf_ctrl->cmn1.e_filter_mode;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.LFMD		= elf_ctrl->cmn1.l_filter_mode;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFL.ELFL1.bit.ELFL1	= elf_ctrl->cmn2.elfl1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFL.ELFL1.bit.ELFL2	= elf_ctrl->cmn2.elfl2;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFL.ELFL2.bit.ELFL3	= elf_ctrl->cmn2.elfl3;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFL.ELFL2.bit.ELFL4	= elf_ctrl->cmn2.elfl4;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_noisefunc( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_NOISE_FUNC* nfunc )
{
#ifdef CO_PARAM_CHECK
	if (nfunc == NULL){
		Ddim_Assertion(("I:im_pro_elf_set_noisefunc error. nfunc=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	// Offset
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBOR.ANBOR1.bit.ANBOR_0	= nfunc[0].offset[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBOR.ANBOR1.bit.ANBOR_1	= nfunc[0].offset[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBOR.ANBOR2.bit.ANBOR_2	= nfunc[0].offset[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBOR.ANBOR2.bit.ANBOR_3	= nfunc[0].offset[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBOG.ANBOG1.bit.ANBOG_0	= nfunc[1].offset[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBOG.ANBOG1.bit.ANBOG_1	= nfunc[1].offset[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBOG.ANBOG2.bit.ANBOG_2	= nfunc[1].offset[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBOG.ANBOG2.bit.ANBOG_3	= nfunc[1].offset[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBOB.ANBOB1.bit.ANBOB_0	= nfunc[2].offset[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBOB.ANBOB1.bit.ANBOB_1	= nfunc[2].offset[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBOB.ANBOB2.bit.ANBOB_2	= nfunc[2].offset[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBOB.ANBOB2.bit.ANBOB_3	= nfunc[2].offset[ 3 ];
	// Gain
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBKR.ANBKR1.bit.ANBKR_0	= nfunc[0].gain[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBKR.ANBKR1.bit.ANBKR_1	= nfunc[0].gain[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBKR.ANBKR2.bit.ANBKR_2	= nfunc[0].gain[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBKR.ANBKR2.bit.ANBKR_3	= nfunc[0].gain[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBKG.ANBKG1.bit.ANBKG_0	= nfunc[1].gain[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBKG.ANBKG1.bit.ANBKG_1	= nfunc[1].gain[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBKG.ANBKG2.bit.ANBKG_2	= nfunc[1].gain[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBKG.ANBKG2.bit.ANBKG_3	= nfunc[1].gain[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBKB.ANBKB1.bit.ANBKB_0	= nfunc[2].gain[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBKB.ANBKB1.bit.ANBKB_1	= nfunc[2].gain[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBKB.ANBKB2.bit.ANBKB_2	= nfunc[2].gain[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBKB.ANBKB2.bit.ANBKB_3	= nfunc[2].gain[ 3 ];
	// Boundary
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBDR.ANBDR1.bit.ANBDR_0	= nfunc[0].boundary[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBDR.ANBDR1.bit.ANBDR_1	= nfunc[0].boundary[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBDR.ANBDR2.bit.ANBDR_2	= nfunc[0].boundary[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBDR.ANBDR2.bit.ANBDR_3	= nfunc[0].boundary[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBDG.ANBDG1.bit.ANBDG_0	= nfunc[1].boundary[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBDG.ANBDG1.bit.ANBDG_1	= nfunc[1].boundary[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBDG.ANBDG2.bit.ANBDG_2	= nfunc[1].boundary[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBDG.ANBDG2.bit.ANBDG_3	= nfunc[1].boundary[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBDB.ANBDB1.bit.ANBDB_0	= nfunc[2].boundary[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBDB.ANBDB1.bit.ANBDB_1	= nfunc[2].boundary[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBDB.ANBDB2.bit.ANBDB_2	= nfunc[2].boundary[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ANBDB.ANBDB2.bit.ANBDB_3	= nfunc[2].boundary[ 3 ];
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_lgt_edg_filter( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_LGT_EDG_FUNC* lgt_filter )
{
#ifdef CO_PARAM_CHECK
	if (lgt_filter == NULL){
		Ddim_Assertion(("I:im_pro_elf_set_lgt_edg_filter error. lgt_filter=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFZP.bit.ELFZP		= lgt_filter->zero_point;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.LGTW.LGTW1.bit.LGTWR	= lgt_filter->gain_r;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.LGTW.LGTW1.bit.LGTWG	= lgt_filter->gain_g;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.LGTW.LGTW2.bit.LGTWB	= lgt_filter->gain_b;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.LGT.bit.LGTR			= lgt_filter->factor_r;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.LGT.bit.LGTG			= lgt_filter->factor_g;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.LGT.bit.LGTB			= lgt_filter->factor_b;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.LGT.bit.LGTC			= lgt_filter->color_para;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.LGTE.bit.LGTER			= lgt_filter->contour_r;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.LGTE.bit.LGTEG			= lgt_filter->contour_g;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.LGTE.bit.LGTEB			= lgt_filter->contour_b;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EDG2ANBA.bit.EDG2ANBA	= lgt_filter->contour_a_1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EDGSCLA.bit.EDGSCLA	= lgt_filter->contour_a_2;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EDG2ANBB.bit.EDG2ANBB	= lgt_filter->contour_b_1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EDGSCLB.bit.EDGSCLB	= lgt_filter->contour_b_2;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EDG2ANBC.bit.EDG2ANBC	= lgt_filter->contour_c_1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EDGSCLC.bit.EDGSCLC	= lgt_filter->contour_c_2;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_area( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_AREA* elf_area )
{
#ifdef CO_PARAM_CHECK
	if (elf_area == NULL){
		Ddim_Assertion(("I:im_pro_elf_set_area error. elf_area=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_ELF_ELFGH_MIN, D_IM_PRO_ELF_ELFGH_MAX, elf_area->g_pos_x, "im_pro_elf_set_area : g_pos_x" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_ELF_ELFGV_MIN, D_IM_PRO_ELF_ELFGV_MAX, elf_area->g_pos_y, "im_pro_elf_set_area : g_pos_y" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_ELF_ELFGHW_MIN, D_IM_PRO_ELF_ELFGHW_MAX, elf_area->g_width, "im_pro_elf_set_area : g_width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_ELF_ELFGVW_MIN, D_IM_PRO_ELF_ELFGVW_MAX, elf_area->g_lines, "im_pro_elf_set_area : g_lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_ELF_ELFH_MIN, D_IM_PRO_ELF_ELFH_MAX, elf_area->pos_x, "im_pro_elf_set_area : pos_x" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_ELF_ELFV_MIN, D_IM_PRO_ELF_ELFV_MAX, elf_area->pos_y, "im_pro_elf_set_area : pos_y" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_ELF_ELFHW_MIN, D_IM_PRO_ELF_ELFHW_MAX, elf_area->width, "im_pro_elf_set_area : width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_ELF_ELFVW_MIN, D_IM_PRO_ELF_ELFVW_MAX, elf_area->lines, "im_pro_elf_set_area : lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFGWS.bit.ELFGHW	= elf_area->g_width;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFGWS.bit.ELFGVW	= elf_area->g_lines;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFGWP.bit.ELFGH	= elf_area->g_pos_x;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFGWP.bit.ELFGV	= elf_area->g_pos_y;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFWS.bit.ELFHW	= elf_area->width;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFWS.bit.ELFVW	= elf_area->lines;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFWP.bit.ELFH		= elf_area->pos_x;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFWP.bit.ELFV		= elf_area->pos_y;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_e_l_filter( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_L_E_FUNC* e_l_filter )
{
#ifdef CO_PARAM_CHECK
	if (e_l_filter == NULL){
		Ddim_Assertion(("I:im_pro_elf_set_e_l_filter error. e_l_filter=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EFTH.EFTH1.bit.EFL1TH			= e_l_filter->e_threshold_1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EFTH.EFTH1.bit.EFL2TH			= e_l_filter->e_threshold_2;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EFTH.EFTH2.bit.EFL3TH			= e_l_filter->e_threshold_3;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EFTH.EFTH2.bit.EFL4TH			= e_l_filter->e_threshold_4;
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.LFTH, union io_lfth, LFTH, e_l_filter->l_threshold );
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELCOME.bit.ELCOME1				= e_l_filter->l_contour_1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELCOME.bit.ELCOME2				= e_l_filter->l_contour_2;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELCOMEN.bit.ELCOME1N			= e_l_filter->l_cintensity_1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELCOMEN.bit.ELCOME2N			= e_l_filter->l_cintensity_2;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_f9_filter( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_f9_SAMPLING* f9_filter )
{
#ifdef CO_PARAM_CHECK
	if (f9_filter == NULL){
		Ddim_Assertion(("I:im_pro_elf_set_f9_filter error. f9_filter=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9W.FS9W1.bit.FS9WR			= f9_filter->rgb_gain.gain[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9W.FS9W1.bit.FS9WG			= f9_filter->rgb_gain.gain[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9W.FS9W2.bit.FS9WB			= f9_filter->rgb_gain.gain[2];
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9YC.FS9YC1, union io_fs9yc_1, FS9YC00, f9_filter->yc_conv_matrix[0] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9YC.FS9YC1, union io_fs9yc_1, FS9YC01, f9_filter->yc_conv_matrix[1] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9YC.FS9YC2, union io_fs9yc_2, FS9YC02, f9_filter->yc_conv_matrix[2] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9YC.FS9YC2, union io_fs9yc_2, FS9YC10, f9_filter->yc_conv_matrix[3] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9YC.FS9YC3, union io_fs9yc_3, FS9YC11, f9_filter->yc_conv_matrix[4] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9YC.FS9YC3, union io_fs9yc_3, FS9YC12, f9_filter->yc_conv_matrix[5] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9YC.FS9YC4, union io_fs9yc_4, FS9YC20, f9_filter->yc_conv_matrix[6] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9YC.FS9YC4, union io_fs9yc_4, FS9YC21, f9_filter->yc_conv_matrix[7] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9YC.FS9YC5, union io_fs9yc_5, FS9YC22, f9_filter->yc_conv_matrix[8] );

	// groupe A
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FASTR.bit.FASTR				= f9_filter->f9a_group.strength;
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.CRVAF, union io_crvaf, CRVAFX1, f9_filter->f9a_group.e_focus_coord[0] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.CRVAF, union io_crvaf, CRVAFY1, f9_filter->f9a_group.e_focus_coord[1] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.CRVAF, union io_crvaf, CRVAFX2, f9_filter->f9a_group.e_focus_coord[2] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.CRVAF, union io_crvaf, CRVAFY2, f9_filter->f9a_group.e_focus_coord[3] );
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FCRVABTOF.bit.FCRVABTOF1		= f9_filter->f9a_group.e_polygonal_line_offset1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FCRVABTGA.bit.FCRVABTGA0		= f9_filter->f9a_group.e_polygonal_line_minus_inclination[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FCRVABTGA.bit.FCRVABTGA1		= f9_filter->f9a_group.e_polygonal_line_minus_inclination[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FCRVABTBD.bit.FCRVABTBD1		= f9_filter->f9a_group.e_polygonal_line_boundary1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FCRVABTCP.bit.FCRVABTCPH		= f9_filter->f9a_group.e_upper_clip;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FCRVABTCP.bit.FCRVABTCPL		= f9_filter->f9a_group.e_lower_clip;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FYABTGA.bit.FYABTGA0			= f9_filter->f9a_group.l_polygonal_line_plus_inclination0;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FYABTGA.bit.FYABTGA1			= f9_filter->f9a_group.l_polygonal_line_minus_inclination1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FYABTBD.bit.FYABTBD0			= f9_filter->f9a_group.l_polygonal_line_boundary[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FYABTBD.bit.FYABTBD1			= f9_filter->f9a_group.l_polygonal_line_boundary[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FYABTCLP.bit.FYABTCLPH			= f9_filter->f9a_group.l_upper_clip;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FYABTCLP.bit.FYABTCLPL			= f9_filter->f9a_group.l_lower_clip;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FAEHH.bit.FAECHH				= f9_filter->f9a_group.t_f_profile_transition;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FAEHH.bit.FAETHH				= f9_filter->f9a_group.t_f_profile_threshold;

	// groupe B
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FBSTR.bit.FBSTR				= f9_filter->f9b_group.strength;
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.CRVBF, union io_crvbf, CRVBFX1, f9_filter->f9b_group.e_focus_coord[0] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.CRVBF, union io_crvbf, CRVBFY1, f9_filter->f9b_group.e_focus_coord[1] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.CRVBF, union io_crvbf, CRVBFX2, f9_filter->f9b_group.e_focus_coord[2] );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.CRVBF, union io_crvbf, CRVBFY2, f9_filter->f9b_group.e_focus_coord[3] );
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FCRVBBTOF.bit.FCRVBBTOF1		= f9_filter->f9b_group.e_polygonal_line_offset1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FCRVBBTGA.bit.FCRVBBTGA0		= f9_filter->f9b_group.e_polygonal_line_minus_inclination[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FCRVBBTGA.bit.FCRVBBTGA1		= f9_filter->f9b_group.e_polygonal_line_minus_inclination[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FCRVBBTBD.bit.FCRVBBTBD1		= f9_filter->f9b_group.e_polygonal_line_boundary1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FCRVBBTCP.bit.FCRVBBTCPL		= f9_filter->f9b_group.e_upper_clip;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FCRVBBTCP.bit.FCRVBBTCPH		= f9_filter->f9b_group.e_lower_clip;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FYBBTGA.bit.FYBBTGA0			= f9_filter->f9b_group.l_polygonal_line_plus_inclination0;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FYBBTGA.bit.FYBBTGA1			= f9_filter->f9b_group.l_polygonal_line_minus_inclination1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FYBBTBD.bit.FYBBTBD0			= f9_filter->f9b_group.l_polygonal_line_boundary[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FYBBTBD.bit.FYBBTBD1			= f9_filter->f9b_group.l_polygonal_line_boundary[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FYBBTCLP.bit.FYBBTCLPL			= f9_filter->f9b_group.l_upper_clip;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FYBBTCLP.bit.FYBBTCLPH			= f9_filter->f9b_group.l_lower_clip;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FBEHH.bit.FBECHH				= f9_filter->f9b_group.t_f_profile_transition;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FBEHH.bit.FBETHH				= f9_filter->f9b_group.t_f_profile_threshold;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_f9_rgbgain( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_f9_RGB_GAIN* rgb_gain )
{
#ifdef CO_PARAM_CHECK
	if( rgb_gain == NULL ){
		Ddim_Assertion(("I:im_pro_elf_set_f9_rgbgain error. rgb_gain=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	//Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9W.FS9W1.bit.FS9WR				= rgb_gain->gain[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9W.FS9W1.bit.FS9WG				= rgb_gain->gain[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.FS9W.FS9W2.bit.FS9WB				= rgb_gain->gain[2];
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_1s5_sampling( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_1s5_SAMPLING* s1s5_sampling )
{
#ifdef CO_PARAM_CHECK
	if (s1s5_sampling == NULL){
		Ddim_Assertion(("I:im_pro_elf_set_1s5_sampling error. s1s5_sampling=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5E.A1S5E1.bit.A1S5E1		= s1s5_sampling->s1s5_threshold[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5E.A1S5E1.bit.A1S5E2		= s1s5_sampling->s1s5_threshold[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5E.A1S5E2.bit.A1S5E3		= s1s5_sampling->s1s5_threshold[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5L1.A1S5L11.bit.A1S5L1E1N	= s1s5_sampling->s1s5_nr_l1_E13[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5L1.A1S5L11.bit.A1S5L1E2N	= s1s5_sampling->s1s5_nr_l1_E13[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5L1.A1S5L12.bit.A1S5L1E3N	= s1s5_sampling->s1s5_nr_l1_E13[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5L2.A1S5L21.bit.A1S5L2E1N	= s1s5_sampling->s1s5_nr_l2_E13[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5L2.A1S5L21.bit.A1S5L2E2N	= s1s5_sampling->s1s5_nr_l2_E13[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5L2.A1S5L22.bit.A1S5L2E3N	= s1s5_sampling->s1s5_nr_l2_E13[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5L3.A1S5L31.bit.A1S5L3E1N	= s1s5_sampling->s1s5_nr_l3_E13[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5L3.A1S5L31.bit.A1S5L3E2N	= s1s5_sampling->s1s5_nr_l3_E13[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5L3.A1S5L32.bit.A1S5L3E3N	= s1s5_sampling->s1s5_nr_l3_E13[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5L4.A1S5L41.bit.A1S5L4E1N	= s1s5_sampling->s1s5_nr_l4_E13[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5L4.A1S5L41.bit.A1S5L4E2N	= s1s5_sampling->s1s5_nr_l4_E13[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A1S5L4.A1S5L42.bit.A1S5L4E3N	= s1s5_sampling->s1s5_nr_l4_E13[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NR1S5RGB.NR1S5RGB1.bit.NR1S5R	= s1s5_sampling->s1s5_nr_adjustment[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NR1S5RGB.NR1S5RGB1.bit.NR1S5G	= s1s5_sampling->s1s5_nr_adjustment[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NR1S5RGB.NR1S5RGB2.bit.NR1S5B	= s1s5_sampling->s1s5_nr_adjustment[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NS1S5LM.bit.NS1S5LMP			= s1s5_sampling->s1s5_noise_limit_plus;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NS1S5LM.bit.NS1S5LMM			= s1s5_sampling->s1s5_noise_limit_minus;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_5s9_sampling( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_5s9_SAMPLING* s5s9_sampling )
{
#ifdef CO_PARAM_CHECK
	if (s5s9_sampling == NULL){
		Ddim_Assertion(("I:im_pro_elf_set_5s9_sampling error. s5s9_sampling=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9E.A5S9E1.bit.A5S9E1		= s5s9_sampling->s5s9_threshold[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9E.A5S9E1.bit.A5S9E2		= s5s9_sampling->s5s9_threshold[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9E.A5S9E2.bit.A5S9E3		= s5s9_sampling->s5s9_threshold[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9L1.A5S9L11.bit.A5S9L1E1N	= s5s9_sampling->s5s9_nr_l1_E13[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9L1.A5S9L11.bit.A5S9L1E2N	= s5s9_sampling->s5s9_nr_l1_E13[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9L1.A5S9L12.bit.A5S9L1E3N	= s5s9_sampling->s5s9_nr_l1_E13[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9L2.A5S9L21.bit.A5S9L2E1N	= s5s9_sampling->s5s9_nr_l2_E13[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9L2.A5S9L21.bit.A5S9L2E2N	= s5s9_sampling->s5s9_nr_l2_E13[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9L2.A5S9L22.bit.A5S9L2E3N	= s5s9_sampling->s5s9_nr_l2_E13[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9L3.A5S9L31.bit.A5S9L3E1N	= s5s9_sampling->s5s9_nr_l3_E13[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9L3.A5S9L31.bit.A5S9L3E2N	= s5s9_sampling->s5s9_nr_l3_E13[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9L3.A5S9L32.bit.A5S9L3E3N	= s5s9_sampling->s5s9_nr_l3_E13[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9L4.A5S9L41.bit.A5S9L4E1N	= s5s9_sampling->s5s9_nr_l4_E13[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9L4.A5S9L41.bit.A5S9L4E2N	= s5s9_sampling->s5s9_nr_l4_E13[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.A5S9L4.A5S9L42.bit.A5S9L4E3N	= s5s9_sampling->s5s9_nr_l4_E13[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NR5S9RGB.NR5S9RGB1.bit.NR5S9R	= s5s9_sampling->s5s9_nr_adjustment[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NR5S9RGB.NR5S9RGB1.bit.NR5S9G	= s5s9_sampling->s5s9_nr_adjustment[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NR5S9RGB.NR5S9RGB2.bit.NR5S9B	= s5s9_sampling->s5s9_nr_adjustment[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NS5S9LM.bit.NS5S9LMP			= s5s9_sampling->s5s9_noise_limit_plus;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NS5S9LM.bit.NS5S9LMM			= s5s9_sampling->s5s9_noise_limit_minus;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_noise_adj( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_Noise_Adj* noise_adj_filter )
{
#ifdef CO_PARAM_CHECK
	if (noise_adj_filter == NULL){
		Ddim_Assertion(("I:im_pro_elf_set_noise_adj error. noise_adj_filter=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFMNNRRL.bit.ELFMNNRRL1	= noise_adj_filter->nr_strength_l1[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFMNNRGL.bit.ELFMNNRGL1	= noise_adj_filter->nr_strength_l1[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFMNNRBL.bit.ELFMNNRBL1	= noise_adj_filter->nr_strength_l1[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFMNNRRL.bit.ELFMNNRRL2	= noise_adj_filter->nr_strength_l2[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFMNNRGL.bit.ELFMNNRGL2	= noise_adj_filter->nr_strength_l2[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFMNNRBL.bit.ELFMNNRBL2	= noise_adj_filter->nr_strength_l2[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFMNNRRL.bit.ELFMNNRRL3	= noise_adj_filter->nr_strength_l3[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFMNNRGL.bit.ELFMNNRGL3	= noise_adj_filter->nr_strength_l3[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFMNNRBL.bit.ELFMNNRBL3	= noise_adj_filter->nr_strength_l3[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFMNNRRL.bit.ELFMNNRRL4	= noise_adj_filter->nr_strength_l4[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFMNNRGL.bit.ELFMNNRGL4	= noise_adj_filter->nr_strength_l4[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFMNNRBL.bit.ELFMNNRBL4	= noise_adj_filter->nr_strength_l4[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFAFNR.bit.ELFAFNR		= noise_adj_filter->af_path_nr_strength;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_a0_sampling( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_a0_FILTER* a0_filter )
{
#ifdef CO_PARAM_CHECK
	if (a0_filter == NULL){
		Ddim_Assertion(("I:im_pro_elf_set_a0_sampling error. a0_filter=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZELADCMD.bit.ZELADCMD			= a0_filter->dpc_mode;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBOR.ZANBOR1.bit.ZANBOR_0	= a0_filter->nce[0].offset[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBOR.ZANBOR1.bit.ZANBOR_1	= a0_filter->nce[0].offset[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBOR.ZANBOR2.bit.ZANBOR_2	= a0_filter->nce[0].offset[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBOR.ZANBOR2.bit.ZANBOR_3	= a0_filter->nce[0].offset[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBOG.ZANBOG1.bit.ZANBOG_0	= a0_filter->nce[1].offset[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBOG.ZANBOG1.bit.ZANBOG_1	= a0_filter->nce[1].offset[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBOG.ZANBOG2.bit.ZANBOG_2	= a0_filter->nce[1].offset[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBOG.ZANBOG2.bit.ZANBOG_3	= a0_filter->nce[1].offset[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBOB.ZANBOB1.bit.ZANBOB_0	= a0_filter->nce[2].offset[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBOB.ZANBOB1.bit.ZANBOB_1	= a0_filter->nce[2].offset[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBOB.ZANBOB2.bit.ZANBOB_2	= a0_filter->nce[2].offset[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBOB.ZANBOB2.bit.ZANBOB_3	= a0_filter->nce[2].offset[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBKR.ZANBKR1.bit.ZANBKR_0	= a0_filter->nce[0].gain[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBKR.ZANBKR1.bit.ZANBKR_1	= a0_filter->nce[0].gain[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBKR.ZANBKR2.bit.ZANBKR_2	= a0_filter->nce[0].gain[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBKR.ZANBKR2.bit.ZANBKR_3	= a0_filter->nce[0].gain[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBKG.ZANBKG1.bit.ZANBKG_0	= a0_filter->nce[1].gain[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBKG.ZANBKG1.bit.ZANBKG_1	= a0_filter->nce[1].gain[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBKG.ZANBKG2.bit.ZANBKG_2	= a0_filter->nce[1].gain[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBKG.ZANBKG2.bit.ZANBKG_3	= a0_filter->nce[1].gain[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBKB.ZANBKB1.bit.ZANBKB_0	= a0_filter->nce[2].gain[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBKB.ZANBKB1.bit.ZANBKB_1	= a0_filter->nce[2].gain[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBKB.ZANBKB2.bit.ZANBKB_2	= a0_filter->nce[2].gain[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBKB.ZANBKB2.bit.ZANBKB_3	= a0_filter->nce[2].gain[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBDR.ZANBDR1.bit.ZANBDR_0	= a0_filter->nce[0].area_boundary[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBDR.ZANBDR1.bit.ZANBDR_1	= a0_filter->nce[0].area_boundary[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBDR.ZANBDR2.bit.ZANBDR_2	= a0_filter->nce[0].area_boundary[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBDR.ZANBDR2.bit.ZANBDR_3	= a0_filter->nce[0].area_boundary[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBDG.ZANBDG1.bit.ZANBDG_0	= a0_filter->nce[1].area_boundary[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBDG.ZANBDG1.bit.ZANBDG_1	= a0_filter->nce[1].area_boundary[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBDG.ZANBDG2.bit.ZANBDG_2	= a0_filter->nce[1].area_boundary[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBDG.ZANBDG2.bit.ZANBDG_3	= a0_filter->nce[1].area_boundary[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBDB.ZANBDB1.bit.ZANBDB_0	= a0_filter->nce[2].area_boundary[ 0 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBDB.ZANBDB1.bit.ZANBDB_1	= a0_filter->nce[2].area_boundary[ 1 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBDB.ZANBDB2.bit.ZANBDB_2	= a0_filter->nce[2].area_boundary[ 2 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZANBDB.ZANBDB2.bit.ZANBDB_3	= a0_filter->nce[2].area_boundary[ 3 ];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLGTW.ZLGTW1.bit.ZLGTWR		= a0_filter->lumi_rgb_gain[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLGTW.ZLGTW1.bit.ZLGTWG		= a0_filter->lumi_rgb_gain[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLGTW.ZLGTW2.bit.ZLGTWB		= a0_filter->lumi_rgb_gain[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLGT.bit.ZLGTR					= a0_filter->lumi_rgb_coeff[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLGT.bit.ZLGTG					= a0_filter->lumi_rgb_coeff[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLGT.bit.ZLGTB					= a0_filter->lumi_rgb_coeff[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLGT.bit.ZLGTC					= a0_filter->lumi_c_coeff;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLGTE.bit.ZLGTER				= a0_filter->t_weight[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLGTE.bit.ZLGTEG				= a0_filter->t_weight[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLGTE.bit.ZLGTEB				= a0_filter->t_weight[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZEDG2ANBA.bit.ZEDG2ANBA		= a0_filter->t_adj_a.coeff1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZEDGSCLA.bit.ZEDGSCLA			= a0_filter->t_adj_a.coeff2;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZEDG2ANBB.bit.ZEDG2ANBB		= a0_filter->t_adj_b.coeff1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZEDGSCLB.bit.ZEDGSCLB			= a0_filter->t_adj_b.coeff2;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNGE.ZALNGE1.bit.ZALNGE1		= a0_filter->t_long_wavelength_threshold[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNGE.ZALNGE1.bit.ZALNGE2		= a0_filter->t_long_wavelength_threshold[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNGE.ZALNGE2.bit.ZALNGE3		= a0_filter->t_long_wavelength_threshold[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNG.ZALNG1.bit.ZALNGL1E1N	= a0_filter->t_long_wavelength_nr_strength[0][0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNG.ZALNG1.bit.ZALNGL1E2N	= a0_filter->t_long_wavelength_nr_strength[0][1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNG.ZALNG2.bit.ZALNGL1E3N	= a0_filter->t_long_wavelength_nr_strength[0][2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNG.ZALNG2.bit.ZALNGL2E1N	= a0_filter->t_long_wavelength_nr_strength[1][0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNG.ZALNG3.bit.ZALNGL2E2N	= a0_filter->t_long_wavelength_nr_strength[1][1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNG.ZALNG3.bit.ZALNGL2E3N	= a0_filter->t_long_wavelength_nr_strength[1][2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNG.ZALNG4.bit.ZALNGL3E1N	= a0_filter->t_long_wavelength_nr_strength[2][0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNG.ZALNG4.bit.ZALNGL3E2N	= a0_filter->t_long_wavelength_nr_strength[2][1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNG.ZALNG5.bit.ZALNGL3E3N	= a0_filter->t_long_wavelength_nr_strength[2][2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNG.ZALNG5.bit.ZALNGL4E1N	= a0_filter->t_long_wavelength_nr_strength[3][0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNG.ZALNG6.bit.ZALNGL4E2N	= a0_filter->t_long_wavelength_nr_strength[3][1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZALNG.ZALNG6.bit.ZALNGL4E3N	= a0_filter->t_long_wavelength_nr_strength[3][2];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLFTH.bit.ZLFTH				= a0_filter->l_filter_extraction_threshold;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLCOME.bit.ZLCOME1				= a0_filter->l_app_tolerance_threshold[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLCOME.bit.ZLCOME2				= a0_filter->l_app_tolerance_threshold[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLCOMEN.bit.ZLCOME1N			= a0_filter->l_app_strength[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZLCOMEN.bit.ZLCOME2N			= a0_filter->l_app_strength[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZNSLNGLM.bit.ZNSLNGLMP			= a0_filter->long_wavelength_noise_p_limiter;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ZNSLNGLM.bit.ZNSLNGLMM			= a0_filter->long_wavelength_noise_m_limiter;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

ImPro1 *im_pro1_new(void)
{
	ImPro1* self = k_object_new(IM_TYPE_PRO1);
	return self;
}
