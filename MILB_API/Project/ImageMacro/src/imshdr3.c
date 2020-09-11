/*
 * imshdr3.c
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

#include "jdsshdr.h"
#include "dd_top.h"
#include "ddim_user_custom.h"
#include "imshdr.h"
#include "imshdr2.h"
#include "imshdr3.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImShdr3, im_shdr3);
#define IM_SHDR3_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImShdr3Private, IM_TYPE_SHDR3))

struct _ImShdr3Private
{
	int a;
};


static void im_shdr3_constructor(ImShdr3 *self)
{
//	ImShdr3Private *priv = IM_SHDR3_GET_PRIVATE(self);
}

static void im_shdr3_destructor(ImShdr3 *self)
{
//	ImShdr3Private *priv = IM_SHDR3_GET_PRIVATE(self);
}

/*
PUBLIC
 */

INT32 Im_SHDR_Set_Blend( const T_IM_SHDR_BLD* const shdr_bld )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_bld == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_Blend() error. shdr_bld = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_bld->blend_sel > D_IM_SHDR_BLDSEL_LONG_SHORT ) {
		Ddim_Assertion(("Im_SHDR_Set_Blend() error. blend_sel is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_bld->alpha_sel > D_IM_SHDR_ALPHASEL_MERGEMASK ) {
		Ddim_Assertion(("Im_SHDR_Set_Blend() error. alpha_sel is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// BLDSEL.
	IO_SHDR.BLDSEL.bit.BLDSEL		= shdr_bld->blend_sel;

	// ALPHASEL.
	IO_SHDR.ALPHASEL.bit.ALPHASEL	= shdr_bld->alpha_sel;

	// ALPHAVAL.
	IO_SHDR.ALPHAVAL.bit.ALPHAVALY	= shdr_bld->alpha_val[ 0 ];
	IO_SHDR.ALPHAVAL.bit.ALPHAVALU	= shdr_bld->alpha_val[ 1 ];
	IO_SHDR.ALPHAVAL.bit.ALPHAVALV	= shdr_bld->alpha_val[ 2 ];

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Get_Blend( T_IM_SHDR_BLD* const shdr_bld )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_bld == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Blend() error. shdr_bld = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// BLDSEL.
	shdr_bld->blend_sel			= IO_SHDR.BLDSEL.bit.BLDSEL;

	// ALPHASEL.
	shdr_bld->alpha_sel			= IO_SHDR.ALPHASEL.bit.ALPHASEL;

	// ALPHAVAL.
	shdr_bld->alpha_val[ 0 ]	= IO_SHDR.ALPHAVAL.bit.ALPHAVALY;
	shdr_bld->alpha_val[ 1 ]	= IO_SHDR.ALPHAVAL.bit.ALPHAVALU;
	shdr_bld->alpha_val[ 2 ]	= IO_SHDR.ALPHAVAL.bit.ALPHAVALV;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Set_Post( const T_IM_SHDR_POST* const shdr_post )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_post == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_Post() error. shdr_post = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_post->ev_sel > D_IM_SHDR_POSTSEL1_RGB ) {
		Ddim_Assertion(("Im_SHDR_Set_Post() error. ev_sel is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_post->mulqpos > D_IM_SHDR_POSTMULQPOS_Q2 ) {
		Ddim_Assertion(("Im_SHDR_Set_Post() error. mulqpos is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_post->css_sel > D_IM_SHDR_POSTSEL0_BYPASS_YCC8 ) {
		Ddim_Assertion(("Im_SHDR_Set_Post() error. css_sel is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_post->hdrcss_mode > D_IM_SHDR_HDRCSSMD_YCC422_CENTER ) {
		Ddim_Assertion(("Im_SHDR_Set_Post() error. hdrcss_mode is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// POSTSFT1RND.
	IO_SHDR.POSTSFT1RND.bit.POSTSFT1RNDEN		= shdr_post->sft1rnd.sft1rnd_en;

	// POSTY2RCOEF.
	im_shdr_set_reg_signed_a( IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_0, shdr_post->y2r_coef[ 0 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_1, shdr_post->y2r_coef[ 1 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_2, shdr_post->y2r_coef[ 2 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_3, shdr_post->y2r_coef[ 3 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_4, shdr_post->y2r_coef[ 4 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_5, shdr_post->y2r_coef[ 5 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_6, shdr_post->y2r_coef[ 6 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_7, shdr_post->y2r_coef[ 7 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_8, shdr_post->y2r_coef[ 8 ] );

	// POSTY2RCLPTHU.
	IO_SHDR.POSTY2RCLPTHU.bit.POSTY2RCLPTHU_0	= shdr_post->y2r_clp_th_upper[ 0 ];
	IO_SHDR.POSTY2RCLPTHU.bit.POSTY2RCLPTHU_1	= shdr_post->y2r_clp_th_upper[ 1 ];
	IO_SHDR.POSTY2RCLPTHU.bit.POSTY2RCLPTHU_2	= shdr_post->y2r_clp_th_upper[ 2 ];

	// POSTY2RCLPTHL.
	IO_SHDR.POSTY2RCLPTHL.bit.POSTY2RCLPTHL_0	= shdr_post->y2r_clp_th_lower[ 0 ];
	IO_SHDR.POSTY2RCLPTHL.bit.POSTY2RCLPTHL_1	= shdr_post->y2r_clp_th_lower[ 1 ];
	IO_SHDR.POSTY2RCLPTHL.bit.POSTY2RCLPTHL_2	= shdr_post->y2r_clp_th_lower[ 2 ];

	// POSTSEL1.
	IO_SHDR.POSTSEL1.bit.POSTSEL1				= shdr_post->ev_sel;

	// POSTMULQPOS.
	IO_SHDR.POSTMULQPOS.bit.POSTMULQPOS			= shdr_post->mulqpos;

	// EVKNB.
	IO_SHDR.EVKNB.bit.EVKNB_1					= shdr_post->ev_kn_boundary[ 1 ];
	IO_SHDR.EVKNB.bit.EVKNB_2					= shdr_post->ev_kn_boundary[ 2 ];
	IO_SHDR.EVKNB.bit.EVKNB_3					= shdr_post->ev_kn_boundary[ 3 ];
	IO_SHDR.EVKNB.bit.EVKNB_4					= shdr_post->ev_kn_boundary[ 4 ];
	IO_SHDR.EVKNB.bit.EVKNB_5					= shdr_post->ev_kn_boundary[ 5 ];
	IO_SHDR.EVKNB.bit.EVKNB_6					= shdr_post->ev_kn_boundary[ 6 ];
	IO_SHDR.EVKNB.bit.EVKNB_7					= shdr_post->ev_kn_boundary[ 7 ];
	IO_SHDR.EVKNB.bit.EVKNB_8					= shdr_post->ev_kn_boundary[ 8 ];
	IO_SHDR.EVKNB.bit.EVKNB_9					= shdr_post->ev_kn_boundary[ 9 ];

	// EVKNOFS.
	IO_SHDR.EVKNOFS.bit.EVKNOFS_0				= shdr_post->ev_kn_offset[ 0 ];
	IO_SHDR.EVKNOFS.bit.EVKNOFS_1				= shdr_post->ev_kn_offset[ 1 ];
	IO_SHDR.EVKNOFS.bit.EVKNOFS_2				= shdr_post->ev_kn_offset[ 2 ];
	IO_SHDR.EVKNOFS.bit.EVKNOFS_3				= shdr_post->ev_kn_offset[ 3 ];
	IO_SHDR.EVKNOFS.bit.EVKNOFS_4				= shdr_post->ev_kn_offset[ 4 ];
	IO_SHDR.EVKNOFS.bit.EVKNOFS_5				= shdr_post->ev_kn_offset[ 5 ];
	IO_SHDR.EVKNOFS.bit.EVKNOFS_6				= shdr_post->ev_kn_offset[ 6 ];
	IO_SHDR.EVKNOFS.bit.EVKNOFS_7				= shdr_post->ev_kn_offset[ 7 ];
	IO_SHDR.EVKNOFS.bit.EVKNOFS_8				= shdr_post->ev_kn_offset[ 8 ];
	IO_SHDR.EVKNOFS.bit.EVKNOFS_9				= shdr_post->ev_kn_offset[ 9 ];

	// EVKNSL.
	im_shdr_set_reg_signed_a( IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_0, shdr_post->ev_kn_slope[ 0 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_1, shdr_post->ev_kn_slope[ 1 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_2, shdr_post->ev_kn_slope[ 2 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_3, shdr_post->ev_kn_slope[ 3 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_4, shdr_post->ev_kn_slope[ 4 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_5, shdr_post->ev_kn_slope[ 5 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_6, shdr_post->ev_kn_slope[ 6 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_7, shdr_post->ev_kn_slope[ 7 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_8, shdr_post->ev_kn_slope[ 8 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_9, shdr_post->ev_kn_slope[ 9 ] );

	// POSTSEL0.
	IO_SHDR.POSTSEL0.bit.POSTSEL0				= shdr_post->css_sel;

	// HDRCSSMD.
	IO_SHDR.HDRCSSMD.bit.HDRCSSMD				= shdr_post->hdrcss_mode;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Get_Post( T_IM_SHDR_POST* const shdr_post )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_post == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Post() error. shdr_post = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// POSTSFT1RND.
	shdr_post->sft1rnd.sft1rnd_en	= IO_SHDR.POSTSFT1RND.bit.POSTSFT1RNDEN;

	// POSTY2RCOEF.
	im_shdr_get_reg_signed_a( shdr_post->y2r_coef[ 0 ], IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_0 );
	im_shdr_get_reg_signed_a( shdr_post->y2r_coef[ 1 ], IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_1 );
	im_shdr_get_reg_signed_a( shdr_post->y2r_coef[ 2 ], IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_2 );
	im_shdr_get_reg_signed_a( shdr_post->y2r_coef[ 3 ], IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_3 );
	im_shdr_get_reg_signed_a( shdr_post->y2r_coef[ 4 ], IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_4 );
	im_shdr_get_reg_signed_a( shdr_post->y2r_coef[ 5 ], IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_5 );
	im_shdr_get_reg_signed_a( shdr_post->y2r_coef[ 6 ], IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_6 );
	im_shdr_get_reg_signed_a( shdr_post->y2r_coef[ 7 ], IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_7 );
	im_shdr_get_reg_signed_a( shdr_post->y2r_coef[ 8 ], IO_SHDR.POSTY2RCOEF, union io_shdr_posty2rcoef, POSTY2RCOEF_8 );

	// POSTY2RCLPTHU.
	shdr_post->y2r_clp_th_upper[ 0 ]	= IO_SHDR.POSTY2RCLPTHU.bit.POSTY2RCLPTHU_0;
	shdr_post->y2r_clp_th_upper[ 1 ]	= IO_SHDR.POSTY2RCLPTHU.bit.POSTY2RCLPTHU_1;
	shdr_post->y2r_clp_th_upper[ 2 ]	= IO_SHDR.POSTY2RCLPTHU.bit.POSTY2RCLPTHU_2;

	// POSTY2RCLPTHL.
	shdr_post->y2r_clp_th_lower[ 0 ]	= IO_SHDR.POSTY2RCLPTHL.bit.POSTY2RCLPTHL_0;
	shdr_post->y2r_clp_th_lower[ 1 ]	= IO_SHDR.POSTY2RCLPTHL.bit.POSTY2RCLPTHL_1;
	shdr_post->y2r_clp_th_lower[ 2 ]	= IO_SHDR.POSTY2RCLPTHL.bit.POSTY2RCLPTHL_2;

	// POSTSEL1.
	shdr_post->ev_sel					= IO_SHDR.POSTSEL1.bit.POSTSEL1;

	// POSTMULQPOS.
	shdr_post->mulqpos					= IO_SHDR.POSTMULQPOS.bit.POSTMULQPOS;

	// EVKNB.
	shdr_post->ev_kn_boundary[ 1 ]		= IO_SHDR.EVKNB.bit.EVKNB_1;
	shdr_post->ev_kn_boundary[ 2 ]		= IO_SHDR.EVKNB.bit.EVKNB_2;
	shdr_post->ev_kn_boundary[ 3 ]		= IO_SHDR.EVKNB.bit.EVKNB_3;
	shdr_post->ev_kn_boundary[ 4 ]		= IO_SHDR.EVKNB.bit.EVKNB_4;
	shdr_post->ev_kn_boundary[ 5 ]		= IO_SHDR.EVKNB.bit.EVKNB_5;
	shdr_post->ev_kn_boundary[ 6 ]		= IO_SHDR.EVKNB.bit.EVKNB_6;
	shdr_post->ev_kn_boundary[ 7 ]		= IO_SHDR.EVKNB.bit.EVKNB_7;
	shdr_post->ev_kn_boundary[ 8 ]		= IO_SHDR.EVKNB.bit.EVKNB_8;
	shdr_post->ev_kn_boundary[ 9 ]		= IO_SHDR.EVKNB.bit.EVKNB_9;

	// EVKNOFS.
	shdr_post->ev_kn_offset[ 0 ]		= IO_SHDR.EVKNOFS.bit.EVKNOFS_0;
	shdr_post->ev_kn_offset[ 1 ]		= IO_SHDR.EVKNOFS.bit.EVKNOFS_1;
	shdr_post->ev_kn_offset[ 2 ]		= IO_SHDR.EVKNOFS.bit.EVKNOFS_2;
	shdr_post->ev_kn_offset[ 3 ]		= IO_SHDR.EVKNOFS.bit.EVKNOFS_3;
	shdr_post->ev_kn_offset[ 4 ]		= IO_SHDR.EVKNOFS.bit.EVKNOFS_4;
	shdr_post->ev_kn_offset[ 5 ]		= IO_SHDR.EVKNOFS.bit.EVKNOFS_5;
	shdr_post->ev_kn_offset[ 6 ]		= IO_SHDR.EVKNOFS.bit.EVKNOFS_6;
	shdr_post->ev_kn_offset[ 7 ]		= IO_SHDR.EVKNOFS.bit.EVKNOFS_7;
	shdr_post->ev_kn_offset[ 8 ]		= IO_SHDR.EVKNOFS.bit.EVKNOFS_8;
	shdr_post->ev_kn_offset[ 9 ]		= IO_SHDR.EVKNOFS.bit.EVKNOFS_9;

	// EVKNSL.
	im_shdr_get_reg_signed_a( shdr_post->ev_kn_slope[ 0 ], IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_0 );
	im_shdr_get_reg_signed_a( shdr_post->ev_kn_slope[ 1 ], IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_1 );
	im_shdr_get_reg_signed_a( shdr_post->ev_kn_slope[ 2 ], IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_2 );
	im_shdr_get_reg_signed_a( shdr_post->ev_kn_slope[ 3 ], IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_3 );
	im_shdr_get_reg_signed_a( shdr_post->ev_kn_slope[ 4 ], IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_4 );
	im_shdr_get_reg_signed_a( shdr_post->ev_kn_slope[ 5 ], IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_5 );
	im_shdr_get_reg_signed_a( shdr_post->ev_kn_slope[ 6 ], IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_6 );
	im_shdr_get_reg_signed_a( shdr_post->ev_kn_slope[ 7 ], IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_7 );
	im_shdr_get_reg_signed_a( shdr_post->ev_kn_slope[ 8 ], IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_8 );
	im_shdr_get_reg_signed_a( shdr_post->ev_kn_slope[ 9 ], IO_SHDR.EVKNSL, union io_shdr_evknsl, EVKNSL_9 );

	// POSTSEL0.
	shdr_post->css_sel					= IO_SHDR.POSTSEL0.bit.POSTSEL0;

	// HDRCSSMD.
	shdr_post->hdrcss_mode				= IO_SHDR.HDRCSSMD.bit.HDRCSSMD;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Set_Resize( const T_IM_SHDR_RESIZE* const shdr_resize )
{
	ImShdr2* imShdr2 = im_shdr2_get();
	UCHAR		*gImShdrOutCtrl = im_shdr2_get_gIM_SHDR_Out_Ctrl(imShdr2);

#ifdef CO_PARAM_CHECK
	if ( shdr_resize == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_Resize() error. shdr_resize = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( shdr_resize->chmode.a_w_en > D_IM_SHDR_ENABLE ) ||
		 ( shdr_resize->chmode.b_w_en > D_IM_SHDR_ENABLE ) ||
		 ( shdr_resize->chmode.c_w_en > D_IM_SHDR_ENABLE ) ||
		 ( shdr_resize->chmode.d_w_en > D_IM_SHDR_ENABLE ) ||
		 ( shdr_resize->chmode.e_w_en > D_IM_SHDR_ENABLE ) ||
		 ( shdr_resize->chmode.f_w_en > D_IM_SHDR_ENABLE ) ) {
		Ddim_Assertion(("Im_SHDR_Set_Resize() error. x_w_en is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( shdr_resize->chmode.a_drc_en > D_IM_SHDR_ENABLE ) ||
		 ( shdr_resize->chmode.c_drc_en > D_IM_SHDR_ENABLE ) ||
		 ( shdr_resize->chmode.d_drc_en > D_IM_SHDR_ENABLE ) ) {
		Ddim_Assertion(("Im_SHDR_Set_Resize() error. x_drc_en is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( shdr_resize->chmode.a_css_md > D_IM_SHDR_CSSMD_YCC420_CENTER ) ||
		 ( shdr_resize->chmode.b_css_md > D_IM_SHDR_CSSMD_YCC420_CENTER ) ||
		 ( shdr_resize->chmode.c_css_md > D_IM_SHDR_CSSMD_YCC420_CENTER ) ||
		 ( shdr_resize->chmode.d_css_md > D_IM_SHDR_CSSMD_YCC420_CENTER ) ||
		 ( shdr_resize->chmode.e_css_md > D_IM_SHDR_CSSMD_YCC420_CENTER ) ||
		 ( shdr_resize->chmode.f_css_md > D_IM_SHDR_CSSMD_YCC420_CENTER ) ) {
		Ddim_Assertion(("Im_SHDR_Set_Resize() error. x_css_md is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( shdr_resize->chmode.b_rdc_md > D_IM_RDCMD1_1_32 ) ||
		 ( shdr_resize->chmode.c_rdc_md > D_IM_RDCMD1_1_32 ) ||
		 ( shdr_resize->chmode.d_rdc_md > D_IM_RDCMD1_1_32 ) ||
		 ( shdr_resize->chmode.e_rdc_md > D_IM_RDCMD1_1_32 ) ||
		 ( shdr_resize->chmode.f_rdc_md > D_IM_RDCMD1_1_32 ) ) {
		Ddim_Assertion(("Im_SHDR_Set_Resize() error. x_rdc_md is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( shdr_resize->chmode.c_rsz_md > D_IM_RSZMD_CENTER1 ) ||
		 ( shdr_resize->chmode.d_rsz_md > D_IM_RSZMD_CENTER1 ) ||
		 ( shdr_resize->chmode.e_rsz_md > D_IM_RSZMD_CENTER1 ) ||
		 ( shdr_resize->chmode.f_rsz_md > D_IM_RSZMD_CENTER1 ) ) {
		Ddim_Assertion(("Im_SHDR_Set_Resize() error. x_rsz_md is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( ( shdr_resize->chmode.c_trm_en > D_IM_SHDR_ENABLE ) ||
		 ( shdr_resize->chmode.d_trm_en > D_IM_SHDR_ENABLE ) ||
		 ( shdr_resize->chmode.e_trm_en > D_IM_SHDR_ENABLE ) ||
		 ( shdr_resize->chmode.f_trm_en > D_IM_SHDR_ENABLE ) ) {
		Ddim_Assertion(("Im_SHDR_Set_Resize() error. x_trm_en is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	// limitation check 1.
	if ( ( *gImShdrOutCtrl == D_IM_SHDR_OUTCTRL_RGB ) &&
		 ( ( shdr_resize->chmode.a_w_en == D_IM_SHDR_ENABLE ) ||
		   ( shdr_resize->chmode.b_w_en == D_IM_SHDR_ENABLE ) ||
		   ( shdr_resize->chmode.c_w_en == D_IM_SHDR_ENABLE ) ||
		   ( shdr_resize->chmode.d_w_en == D_IM_SHDR_ENABLE ) ||
		   ( shdr_resize->chmode.e_w_en == D_IM_SHDR_ENABLE ) ||
		   ( shdr_resize->chmode.f_w_en == D_IM_SHDR_ENABLE ) ) ) {
		Ddim_Print(("Im_SHDR_Set_Resize() : limitation check 1 NG\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}

	im_shdr_on_pclk();
	im_shdr_dsb();

	// CHMODE.
	IO_SHDR.CH0MODE.bit.WEN0		= shdr_resize->chmode.a_w_en;
	IO_SHDR.CH0MODE.bit.DRCEN0		= shdr_resize->chmode.a_drc_en;
	IO_SHDR.CH0MODE.bit.CSSMD0		= shdr_resize->chmode.a_css_md;
	IO_SHDR.CH1MODE.bit.WEN1		= shdr_resize->chmode.b_w_en;
	IO_SHDR.CH1MODE.bit.RDCMD1		= shdr_resize->chmode.b_rdc_md;
	IO_SHDR.CH1MODE.bit.CSSMD1		= shdr_resize->chmode.b_css_md;
	IO_SHDR.CH2MODE.bit.WEN2		= shdr_resize->chmode.c_w_en;
	IO_SHDR.CH2MODE.bit.RSZMD2		= shdr_resize->chmode.c_rsz_md;
	IO_SHDR.CH2MODE.bit.RDCEN2		= shdr_resize->chmode.c_rdc_en;
	IO_SHDR.CH2MODE.bit.RDCMD2		= shdr_resize->chmode.c_rdc_md;
	IO_SHDR.CH2MODE.bit.TRMEN2		= shdr_resize->chmode.c_trm_en;
	IO_SHDR.CH2MODE.bit.DRCEN2		= shdr_resize->chmode.c_drc_en;
	IO_SHDR.CH2MODE.bit.CSSMD2		= shdr_resize->chmode.c_css_md;
	IO_SHDR.CH3MODE.bit.WEN3		= shdr_resize->chmode.d_w_en;
	IO_SHDR.CH3MODE.bit.RSZMD3		= shdr_resize->chmode.d_rsz_md;
	IO_SHDR.CH3MODE.bit.RDCEN3		= shdr_resize->chmode.d_rdc_en;
	IO_SHDR.CH3MODE.bit.RDCMD3		= shdr_resize->chmode.d_rdc_md;
	IO_SHDR.CH3MODE.bit.TRMEN3		= shdr_resize->chmode.d_trm_en;
	IO_SHDR.CH3MODE.bit.DRCEN3		= shdr_resize->chmode.d_drc_en;
	IO_SHDR.CH3MODE.bit.CSSMD3		= shdr_resize->chmode.d_css_md;
	IO_SHDR.CH4MODE.bit.WEN4		= shdr_resize->chmode.e_w_en;
	IO_SHDR.CH4MODE.bit.RSZMD4		= shdr_resize->chmode.e_rsz_md;
	IO_SHDR.CH4MODE.bit.RDCEN4		= shdr_resize->chmode.e_rdc_en;
	IO_SHDR.CH4MODE.bit.RDCMD4		= shdr_resize->chmode.e_rdc_md;
	IO_SHDR.CH4MODE.bit.TRMEN4		= shdr_resize->chmode.e_trm_en;
	IO_SHDR.CH4MODE.bit.CSSMD4		= shdr_resize->chmode.e_css_md;
	IO_SHDR.CH5MODE.bit.WEN5		= shdr_resize->chmode.f_w_en;
	IO_SHDR.CH5MODE.bit.RSZMD5		= shdr_resize->chmode.f_rsz_md;
	IO_SHDR.CH5MODE.bit.RDCEN5		= shdr_resize->chmode.f_rdc_en;
	IO_SHDR.CH5MODE.bit.RDCMD5		= shdr_resize->chmode.f_rdc_md;
	IO_SHDR.CH5MODE.bit.TRMEN5		= shdr_resize->chmode.f_trm_en;
	IO_SHDR.CH5MODE.bit.CSSMD5		= shdr_resize->chmode.f_css_md;

	// WOUTSZ.
	IO_SHDR.WOUTSZ.bit.WOUTHSZ_0	= shdr_resize->woutsz.a_hsize;
	IO_SHDR.WOUTSZ.bit.WOUTVSZ_0	= shdr_resize->woutsz.a_vsize;
	IO_SHDR.WOUTSZ.bit.WOUTHSZ_1	= shdr_resize->woutsz.b_hsize;
	IO_SHDR.WOUTSZ.bit.WOUTVSZ_1	= shdr_resize->woutsz.b_vsize;
	IO_SHDR.WOUTSZ.bit.WOUTHSZ_2	= shdr_resize->woutsz.c_hsize;
	IO_SHDR.WOUTSZ.bit.WOUTVSZ_2	= shdr_resize->woutsz.c_vsize;
	IO_SHDR.WOUTSZ.bit.WOUTHSZ_3	= shdr_resize->woutsz.d_hsize;
	IO_SHDR.WOUTSZ.bit.WOUTVSZ_3	= shdr_resize->woutsz.d_vsize;
	IO_SHDR.WOUTSZ.bit.WOUTHSZ_4	= shdr_resize->woutsz.e_hsize;
	IO_SHDR.WOUTSZ.bit.WOUTVSZ_4	= shdr_resize->woutsz.e_vsize;
	IO_SHDR.WOUTSZ.bit.WOUTHSZ_5	= shdr_resize->woutsz.f_hsize;
	IO_SHDR.WOUTSZ.bit.WOUTVSZ_5	= shdr_resize->woutsz.f_vsize;

	// RSZHCNT.
	IO_SHDR.RSZHCNT_2.bit.RSZHSTA	= shdr_resize->rszhcnt.c_hsta;
	IO_SHDR.RSZHCNT_2.bit.RSZHPIT	= shdr_resize->rszhcnt.c_hpit;
	IO_SHDR.RSZHCNT_3.bit.RSZHSTA	= shdr_resize->rszhcnt.d_hsta;
	IO_SHDR.RSZHCNT_3.bit.RSZHPIT	= shdr_resize->rszhcnt.d_hpit;
	IO_SHDR.RSZHCNT_4.bit.RSZHSTA	= shdr_resize->rszhcnt.e_hsta;
	IO_SHDR.RSZHCNT_4.bit.RSZHPIT	= shdr_resize->rszhcnt.e_hpit;
	IO_SHDR.RSZHCNT_5.bit.RSZHSTA	= shdr_resize->rszhcnt.f_hsta;
	IO_SHDR.RSZHCNT_5.bit.RSZHPIT	= shdr_resize->rszhcnt.f_hpit;

	// RSZVCNT.
	IO_SHDR.RSZVCNT_2.bit.RSZVSTA	= shdr_resize->rszvcnt.c_vsta;
	IO_SHDR.RSZVCNT_2.bit.RSZVPIT	= shdr_resize->rszvcnt.c_vpit;
	IO_SHDR.RSZVCNT_3.bit.RSZVSTA	= shdr_resize->rszvcnt.d_vsta;
	IO_SHDR.RSZVCNT_3.bit.RSZVPIT	= shdr_resize->rszvcnt.d_vpit;
	IO_SHDR.RSZVCNT_4.bit.RSZVSTA	= shdr_resize->rszvcnt.e_vsta;
	IO_SHDR.RSZVCNT_4.bit.RSZVPIT	= shdr_resize->rszvcnt.e_vpit;
	IO_SHDR.RSZVCNT_5.bit.RSZVSTA	= shdr_resize->rszvcnt.f_vsta;
	IO_SHDR.RSZVCNT_5.bit.RSZVPIT	= shdr_resize->rszvcnt.f_vpit;

	// TRMSTA.
	IO_SHDR.TRMSTA_2.bit.TRMHSTA	= shdr_resize->trmsta.c_hsta;
	IO_SHDR.TRMSTA_2.bit.TRMVSTA	= shdr_resize->trmsta.c_vsta;
	IO_SHDR.TRMSTA_3.bit.TRMHSTA	= shdr_resize->trmsta.d_hsta;
	IO_SHDR.TRMSTA_3.bit.TRMVSTA	= shdr_resize->trmsta.d_vsta;
	IO_SHDR.TRMSTA_4.bit.TRMHSTA	= shdr_resize->trmsta.e_hsta;
	IO_SHDR.TRMSTA_4.bit.TRMVSTA	= shdr_resize->trmsta.e_vsta;
	IO_SHDR.TRMSTA_5.bit.TRMHSTA	= shdr_resize->trmsta.f_hsta;
	IO_SHDR.TRMSTA_5.bit.TRMVSTA	= shdr_resize->trmsta.f_vsta;

	// DRCOFST.
	IO_SHDR.DRCOFST_0.bit.DRCYOFST	= shdr_resize->drcofst.a_y;
	im_shdr_set_reg_signed( IO_SHDR.DRCOFST_0, union io_shdr_drcofst, DRCCBOFST, shdr_resize->drcofst.a_cb );
	im_shdr_set_reg_signed( IO_SHDR.DRCOFST_0, union io_shdr_drcofst, DRCCROFST, shdr_resize->drcofst.a_cr );

	IO_SHDR.DRCOFST_2.bit.DRCYOFST	= shdr_resize->drcofst.c_y;
	im_shdr_set_reg_signed( IO_SHDR.DRCOFST_2, union io_shdr_drcofst, DRCCBOFST, shdr_resize->drcofst.c_cb );
	im_shdr_set_reg_signed( IO_SHDR.DRCOFST_2, union io_shdr_drcofst, DRCCROFST, shdr_resize->drcofst.c_cr );

	IO_SHDR.DRCOFST_3.bit.DRCYOFST	= shdr_resize->drcofst.d_y;
	im_shdr_set_reg_signed( IO_SHDR.DRCOFST_3, union io_shdr_drcofst, DRCCBOFST, shdr_resize->drcofst.d_cb );
	im_shdr_set_reg_signed( IO_SHDR.DRCOFST_3, union io_shdr_drcofst, DRCCROFST, shdr_resize->drcofst.d_cr );

	// DRCGAIN.
	IO_SHDR.DRCGAIN_0.bit.DRCYGAIN	= shdr_resize->drcgain.a_y;
	IO_SHDR.DRCGAIN_0.bit.DRCCBGAIN	= shdr_resize->drcgain.a_cb;
	IO_SHDR.DRCGAIN_0.bit.DRCCRGAIN	= shdr_resize->drcgain.a_cr;
	IO_SHDR.DRCGAIN_2.bit.DRCYGAIN	= shdr_resize->drcgain.c_y;
	IO_SHDR.DRCGAIN_2.bit.DRCCBGAIN	= shdr_resize->drcgain.c_cb;
	IO_SHDR.DRCGAIN_2.bit.DRCCRGAIN	= shdr_resize->drcgain.c_cr;
	IO_SHDR.DRCGAIN_3.bit.DRCYGAIN	= shdr_resize->drcgain.d_y;
	IO_SHDR.DRCGAIN_3.bit.DRCCBGAIN	= shdr_resize->drcgain.d_cb;
	IO_SHDR.DRCGAIN_3.bit.DRCCRGAIN	= shdr_resize->drcgain.d_cr;

	// DRCCLPH.
	IO_SHDR.DRCCLPH_0.bit.DRCYCLPH	= shdr_resize->drcclph.a_y;
	im_shdr_set_reg_signed( IO_SHDR.DRCCLPH_0, union io_shdr_drcclph, DRCCBCLPH, shdr_resize->drcclph.a_cb );
	im_shdr_set_reg_signed( IO_SHDR.DRCCLPH_0, union io_shdr_drcclph, DRCCRCLPH, shdr_resize->drcclph.a_cr );

	IO_SHDR.DRCCLPH_2.bit.DRCYCLPH	= shdr_resize->drcclph.c_y;
	im_shdr_set_reg_signed( IO_SHDR.DRCCLPH_2, union io_shdr_drcclph, DRCCBCLPH, shdr_resize->drcclph.c_cb );
	im_shdr_set_reg_signed( IO_SHDR.DRCCLPH_2, union io_shdr_drcclph, DRCCRCLPH, shdr_resize->drcclph.c_cr );

	IO_SHDR.DRCCLPH_3.bit.DRCYCLPH	= shdr_resize->drcclph.d_y;
	im_shdr_set_reg_signed( IO_SHDR.DRCCLPH_3, union io_shdr_drcclph, DRCCBCLPH, shdr_resize->drcclph.d_cb );
	im_shdr_set_reg_signed( IO_SHDR.DRCCLPH_3, union io_shdr_drcclph, DRCCRCLPH, shdr_resize->drcclph.d_cr );

	// DRCCLPL.
	IO_SHDR.DRCCLPL_0.bit.DRCYCLPL	= shdr_resize->drcclpl.a_y;
	im_shdr_set_reg_signed( IO_SHDR.DRCCLPL_0, union io_shdr_drcclpl, DRCCBCLPL, shdr_resize->drcclpl.a_cb );
	im_shdr_set_reg_signed( IO_SHDR.DRCCLPL_0, union io_shdr_drcclpl, DRCCRCLPL, shdr_resize->drcclpl.a_cr );

	IO_SHDR.DRCCLPL_2.bit.DRCYCLPL	= shdr_resize->drcclpl.c_y;
	im_shdr_set_reg_signed( IO_SHDR.DRCCLPL_2, union io_shdr_drcclpl, DRCCBCLPL, shdr_resize->drcclpl.c_cb );
	im_shdr_set_reg_signed( IO_SHDR.DRCCLPL_2, union io_shdr_drcclpl, DRCCRCLPL, shdr_resize->drcclpl.c_cr );

	IO_SHDR.DRCCLPL_3.bit.DRCYCLPL	= shdr_resize->drcclpl.d_y;
	im_shdr_set_reg_signed( IO_SHDR.DRCCLPL_3, union io_shdr_drcclpl, DRCCBCLPL, shdr_resize->drcclpl.d_cb );
	im_shdr_set_reg_signed( IO_SHDR.DRCCLPL_3, union io_shdr_drcclpl, DRCCRCLPL, shdr_resize->drcclpl.d_cr );

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Get_Resize( T_IM_SHDR_RESIZE* const shdr_resize )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_resize == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Resize() error. shdr_resize = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// CHMODE.
	shdr_resize->chmode.a_w_en		= IO_SHDR.CH0MODE.bit.WEN0;
	shdr_resize->chmode.a_drc_en	= IO_SHDR.CH0MODE.bit.DRCEN0;
	shdr_resize->chmode.a_css_md	= IO_SHDR.CH0MODE.bit.CSSMD0;
	shdr_resize->chmode.b_w_en		= IO_SHDR.CH1MODE.bit.WEN1;
	shdr_resize->chmode.b_rdc_md	= IO_SHDR.CH1MODE.bit.RDCMD1;
	shdr_resize->chmode.b_css_md	= IO_SHDR.CH1MODE.bit.CSSMD1;
	shdr_resize->chmode.c_w_en		= IO_SHDR.CH2MODE.bit.WEN2;
	shdr_resize->chmode.c_rsz_md	= IO_SHDR.CH2MODE.bit.RSZMD2;
	shdr_resize->chmode.c_rdc_en	= IO_SHDR.CH2MODE.bit.RDCEN2;
	shdr_resize->chmode.c_rdc_md	= IO_SHDR.CH2MODE.bit.RDCMD2;
	shdr_resize->chmode.c_trm_en	= IO_SHDR.CH2MODE.bit.TRMEN2;
	shdr_resize->chmode.c_drc_en	= IO_SHDR.CH2MODE.bit.DRCEN2;
	shdr_resize->chmode.c_css_md	= IO_SHDR.CH2MODE.bit.CSSMD2;
	shdr_resize->chmode.d_w_en		= IO_SHDR.CH3MODE.bit.WEN3;
	shdr_resize->chmode.d_rsz_md	= IO_SHDR.CH3MODE.bit.RSZMD3;
	shdr_resize->chmode.d_rdc_en	= IO_SHDR.CH3MODE.bit.RDCEN3;
	shdr_resize->chmode.d_rdc_md	= IO_SHDR.CH3MODE.bit.RDCMD3;
	shdr_resize->chmode.d_trm_en	= IO_SHDR.CH3MODE.bit.TRMEN3;
	shdr_resize->chmode.d_drc_en	= IO_SHDR.CH3MODE.bit.DRCEN3;
	shdr_resize->chmode.d_css_md	= IO_SHDR.CH3MODE.bit.CSSMD3;
	shdr_resize->chmode.e_w_en		= IO_SHDR.CH4MODE.bit.WEN4;
	shdr_resize->chmode.e_rsz_md	= IO_SHDR.CH4MODE.bit.RSZMD4;
	shdr_resize->chmode.e_rdc_en	= IO_SHDR.CH4MODE.bit.RDCEN4;
	shdr_resize->chmode.e_rdc_md	= IO_SHDR.CH4MODE.bit.RDCMD4;
	shdr_resize->chmode.e_trm_en	= IO_SHDR.CH4MODE.bit.TRMEN4;
	shdr_resize->chmode.e_css_md	= IO_SHDR.CH4MODE.bit.CSSMD4;
	shdr_resize->chmode.f_w_en		= IO_SHDR.CH5MODE.bit.WEN5;
	shdr_resize->chmode.f_rsz_md	= IO_SHDR.CH5MODE.bit.RSZMD5;
	shdr_resize->chmode.f_rdc_en	= IO_SHDR.CH5MODE.bit.RDCEN5;
	shdr_resize->chmode.f_rdc_md	= IO_SHDR.CH5MODE.bit.RDCMD5;
	shdr_resize->chmode.f_trm_en	= IO_SHDR.CH5MODE.bit.TRMEN5;
	shdr_resize->chmode.f_css_md	= IO_SHDR.CH5MODE.bit.CSSMD5;

	// WOUTSZ.
	shdr_resize->woutsz.a_hsize		= IO_SHDR.WOUTSZ.bit.WOUTHSZ_0;
	shdr_resize->woutsz.a_vsize		= IO_SHDR.WOUTSZ.bit.WOUTVSZ_0;
	shdr_resize->woutsz.b_hsize		= IO_SHDR.WOUTSZ.bit.WOUTHSZ_1;
	shdr_resize->woutsz.b_vsize		= IO_SHDR.WOUTSZ.bit.WOUTVSZ_1;
	shdr_resize->woutsz.c_hsize		= IO_SHDR.WOUTSZ.bit.WOUTHSZ_2;
	shdr_resize->woutsz.c_vsize		= IO_SHDR.WOUTSZ.bit.WOUTVSZ_2;
	shdr_resize->woutsz.d_hsize		= IO_SHDR.WOUTSZ.bit.WOUTHSZ_3;
	shdr_resize->woutsz.d_vsize		= IO_SHDR.WOUTSZ.bit.WOUTVSZ_3;
	shdr_resize->woutsz.e_hsize		= IO_SHDR.WOUTSZ.bit.WOUTHSZ_4;
	shdr_resize->woutsz.e_vsize		= IO_SHDR.WOUTSZ.bit.WOUTVSZ_4;
	shdr_resize->woutsz.f_hsize		= IO_SHDR.WOUTSZ.bit.WOUTHSZ_5;
	shdr_resize->woutsz.f_vsize		= IO_SHDR.WOUTSZ.bit.WOUTVSZ_5;

	// RSZHCNT.
	shdr_resize->rszhcnt.c_hsta		= IO_SHDR.RSZHCNT_2.bit.RSZHSTA;
	shdr_resize->rszhcnt.c_hpit		= IO_SHDR.RSZHCNT_2.bit.RSZHPIT;
	shdr_resize->rszhcnt.d_hsta		= IO_SHDR.RSZHCNT_3.bit.RSZHSTA;
	shdr_resize->rszhcnt.d_hpit		= IO_SHDR.RSZHCNT_3.bit.RSZHPIT;
	shdr_resize->rszhcnt.e_hsta		= IO_SHDR.RSZHCNT_4.bit.RSZHSTA;
	shdr_resize->rszhcnt.e_hpit		= IO_SHDR.RSZHCNT_4.bit.RSZHPIT;
	shdr_resize->rszhcnt.f_hsta		= IO_SHDR.RSZHCNT_5.bit.RSZHSTA;
	shdr_resize->rszhcnt.f_hpit		= IO_SHDR.RSZHCNT_5.bit.RSZHPIT;

	// RSZVCNT.
	shdr_resize->rszvcnt.c_vsta		= IO_SHDR.RSZVCNT_2.bit.RSZVSTA;
	shdr_resize->rszvcnt.c_vpit		= IO_SHDR.RSZVCNT_2.bit.RSZVPIT;
	shdr_resize->rszvcnt.d_vsta		= IO_SHDR.RSZVCNT_3.bit.RSZVSTA;
	shdr_resize->rszvcnt.d_vpit		= IO_SHDR.RSZVCNT_3.bit.RSZVPIT;
	shdr_resize->rszvcnt.e_vsta		= IO_SHDR.RSZVCNT_4.bit.RSZVSTA;
	shdr_resize->rszvcnt.e_vpit		= IO_SHDR.RSZVCNT_4.bit.RSZVPIT;
	shdr_resize->rszvcnt.f_vsta		= IO_SHDR.RSZVCNT_5.bit.RSZVSTA;
	shdr_resize->rszvcnt.f_vpit		= IO_SHDR.RSZVCNT_5.bit.RSZVPIT;

	// TRMSTA.
	shdr_resize->trmsta.c_hsta		= IO_SHDR.TRMSTA_2.bit.TRMHSTA;
	shdr_resize->trmsta.c_vsta		= IO_SHDR.TRMSTA_2.bit.TRMVSTA;
	shdr_resize->trmsta.d_hsta		= IO_SHDR.TRMSTA_3.bit.TRMHSTA;
	shdr_resize->trmsta.d_vsta		= IO_SHDR.TRMSTA_3.bit.TRMVSTA;
	shdr_resize->trmsta.e_hsta		= IO_SHDR.TRMSTA_4.bit.TRMHSTA;
	shdr_resize->trmsta.e_vsta		= IO_SHDR.TRMSTA_4.bit.TRMVSTA;
	shdr_resize->trmsta.f_hsta		= IO_SHDR.TRMSTA_5.bit.TRMHSTA;
	shdr_resize->trmsta.f_vsta		= IO_SHDR.TRMSTA_5.bit.TRMVSTA;

	// DRCOFST.
	shdr_resize->drcofst.a_y		= IO_SHDR.DRCOFST_0.bit.DRCYOFST;
	im_shdr_get_reg_signed( shdr_resize->drcofst.a_cb, IO_SHDR.DRCOFST_0, union io_shdr_drcofst, DRCCBOFST );
	im_shdr_get_reg_signed( shdr_resize->drcofst.a_cr, IO_SHDR.DRCOFST_0, union io_shdr_drcofst, DRCCROFST );

	shdr_resize->drcofst.c_y		= IO_SHDR.DRCOFST_2.bit.DRCYOFST;
	im_shdr_get_reg_signed( shdr_resize->drcofst.c_cb, IO_SHDR.DRCOFST_2, union io_shdr_drcofst, DRCCBOFST );
	im_shdr_get_reg_signed( shdr_resize->drcofst.c_cr, IO_SHDR.DRCOFST_2, union io_shdr_drcofst, DRCCROFST );

	shdr_resize->drcofst.d_y		= IO_SHDR.DRCOFST_3.bit.DRCYOFST;
	im_shdr_get_reg_signed( shdr_resize->drcofst.d_cb, IO_SHDR.DRCOFST_3, union io_shdr_drcofst, DRCCBOFST );
	im_shdr_get_reg_signed( shdr_resize->drcofst.d_cr, IO_SHDR.DRCOFST_3, union io_shdr_drcofst, DRCCROFST );

	// DRCGAIN.
	shdr_resize->drcgain.a_y		= IO_SHDR.DRCGAIN_0.bit.DRCYGAIN;
	shdr_resize->drcgain.a_cb		= IO_SHDR.DRCGAIN_0.bit.DRCCBGAIN;
	shdr_resize->drcgain.a_cr		= IO_SHDR.DRCGAIN_0.bit.DRCCRGAIN;
	shdr_resize->drcgain.c_y		= IO_SHDR.DRCGAIN_2.bit.DRCYGAIN;
	shdr_resize->drcgain.c_cb		= IO_SHDR.DRCGAIN_2.bit.DRCCBGAIN;
	shdr_resize->drcgain.c_cr		= IO_SHDR.DRCGAIN_2.bit.DRCCRGAIN;
	shdr_resize->drcgain.d_y		= IO_SHDR.DRCGAIN_3.bit.DRCYGAIN;
	shdr_resize->drcgain.d_cb		= IO_SHDR.DRCGAIN_3.bit.DRCCBGAIN;
	shdr_resize->drcgain.d_cr		= IO_SHDR.DRCGAIN_3.bit.DRCCRGAIN;

	// DRCCLPH.
	shdr_resize->drcclph.a_y		= IO_SHDR.DRCCLPH_0.bit.DRCYCLPH;
	im_shdr_get_reg_signed( shdr_resize->drcclph.a_cb, IO_SHDR.DRCCLPH_0, union io_shdr_drcclph, DRCCBCLPH );
	im_shdr_get_reg_signed( shdr_resize->drcclph.a_cr, IO_SHDR.DRCCLPH_0, union io_shdr_drcclph, DRCCRCLPH );

	shdr_resize->drcclph.c_y		= IO_SHDR.DRCCLPH_2.bit.DRCYCLPH;
	im_shdr_get_reg_signed( shdr_resize->drcclph.c_cb, IO_SHDR.DRCCLPH_2, union io_shdr_drcclph, DRCCBCLPH );
	im_shdr_get_reg_signed( shdr_resize->drcclph.c_cr, IO_SHDR.DRCCLPH_2, union io_shdr_drcclph, DRCCRCLPH );

	shdr_resize->drcclph.d_y		= IO_SHDR.DRCCLPH_3.bit.DRCYCLPH;
	im_shdr_get_reg_signed( shdr_resize->drcclph.d_cb, IO_SHDR.DRCCLPH_3, union io_shdr_drcclph, DRCCBCLPH );
	im_shdr_get_reg_signed( shdr_resize->drcclph.d_cr, IO_SHDR.DRCCLPH_3, union io_shdr_drcclph, DRCCRCLPH );

	// DRCCLPL.
	shdr_resize->drcclpl.a_y		= IO_SHDR.DRCCLPL_0.bit.DRCYCLPL;
	im_shdr_get_reg_signed( shdr_resize->drcclpl.a_cb, IO_SHDR.DRCCLPL_0, union io_shdr_drcclpl, DRCCBCLPL );
	im_shdr_get_reg_signed( shdr_resize->drcclpl.a_cr, IO_SHDR.DRCCLPL_0, union io_shdr_drcclpl, DRCCRCLPL );

	shdr_resize->drcclpl.c_y		= IO_SHDR.DRCCLPL_2.bit.DRCYCLPL;
	im_shdr_get_reg_signed( shdr_resize->drcclpl.c_cb, IO_SHDR.DRCCLPL_2, union io_shdr_drcclpl, DRCCBCLPL );
	im_shdr_get_reg_signed( shdr_resize->drcclpl.c_cr, IO_SHDR.DRCCLPL_2, union io_shdr_drcclpl, DRCCRCLPL );

	shdr_resize->drcclpl.d_y		= IO_SHDR.DRCCLPL_3.bit.DRCYCLPL;
	im_shdr_get_reg_signed( shdr_resize->drcclpl.d_cb, IO_SHDR.DRCCLPL_3, union io_shdr_drcclpl, DRCCBCLPL );
	im_shdr_get_reg_signed( shdr_resize->drcclpl.d_cr, IO_SHDR.DRCCLPL_3, union io_shdr_drcclpl, DRCCRCLPL );

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Set_Smc( const T_IM_SHDR_SMC* const shdr_smc )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_smc == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_Smc() error. shdr_smc = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_smc->mcarmd.mca_mode > D_IM_MCAMD_MAX_MIN_VECTOR ) {
		Ddim_Assertion(("Im_SHDR_Set_Smc() error. shdr_smc->mcarmd.mca_mode is ivalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_smc->mcarmd.mcr_mode > D_IM_MCRMD_MC ) {
		Ddim_Assertion(("Im_SHDR_Set_Smc() error. shdr_smc->mcarmd.mcr_mode is ivalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_smc->mcmpmd.mcmp_mode > D_IM_SHDR_ON ) {
		Ddim_Assertion(("Im_SHDR_Set_Smc() error. shdr_smc->mcmpmd.mcmp_mode is ivalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_smc->mcmpmd.mvw_en > D_IM_SHDR_ENABLE ) {
		Ddim_Assertion(("Im_SHDR_Set_Smc() error. shdr_smc->mcmpmd.mvw_en is ivalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_smc->mvlcnt.mvl_en > D_IM_SHDR_ENABLE ) {
		Ddim_Assertion(("Im_SHDR_Set_Smc() error. shdr_smc->mvlcnt.mvl_en is ivalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// MCAMD.
	IO_SHDR.MCARMD.bit.MCAMD	= shdr_smc->mcarmd.mca_mode;
	IO_SHDR.MCARMD.bit.MCRMD	= shdr_smc->mcarmd.mcr_mode;

	// MCMPMD.
	IO_SHDR.MCMPMD.bit.MCMPMD	= shdr_smc->mcmpmd.mcmp_mode;
	IO_SHDR.MCMPMD.bit.MVWEN	= shdr_smc->mcmpmd.mvw_en;

	// MMVVAL.
	IO_SHDR.MMVVAL.bit.MMVX		= shdr_smc->mmvval.mmv_x;
	IO_SHDR.MMVVAL.bit.MMVY		= shdr_smc->mmvval.mmv_y;

	// MMVRCNT.
	IO_SHDR.MMVRCNT.bit.MMVROX	= shdr_smc->mmvrcnt.mmvro_x;
	IO_SHDR.MMVRCNT.bit.MMVROY	= shdr_smc->mmvrcnt.mmvro_y;
	IO_SHDR.MMVRCNT.bit.MMVRKX	= shdr_smc->mmvrcnt.mmvrk_x;
	IO_SHDR.MMVRCNT.bit.MMVRKY	= shdr_smc->mmvrcnt.mmvrk_y;

	// MDBCNT.
	IO_SHDR.MDBCNT.bit.MDBX		= shdr_smc->mdbcnt.mdb_x;
	IO_SHDR.MDBCNT.bit.MDBY		= shdr_smc->mdbcnt.mdb_y;

	// MDBROCNT.
	IO_SHDR.MDBROCNT.bit.MDBROX	= shdr_smc->mdbrocnt.mdbro_x;
	IO_SHDR.MDBROCNT.bit.MDBROY	= shdr_smc->mdbrocnt.mdbro_y;
	IO_SHDR.MDBROCNT.bit.MDBRKX	= shdr_smc->mdbrocnt.mdbrk_x;
	IO_SHDR.MDBROCNT.bit.MDBRKY	= shdr_smc->mdbrocnt.mdbrk_y;

	// MOLRCNT.
	IO_SHDR.MOLRCNT.bit.MOLRSM	= shdr_smc->molrcnt.molr_sm;
	IO_SHDR.MOLRCNT.bit.MOLRSS	= shdr_smc->molrcnt.molr_ss;
	IO_SHDR.MOLRCNT.bit.MOLRO	= shdr_smc->molrcnt.molr_o;
	IO_SHDR.MOLRCNT.bit.MOLRK	= shdr_smc->molrcnt.molr_k;

	// MCPCNT.
	IO_SHDR.MCPCNT.bit.MCPXS	= shdr_smc->mcpcnt.mcpx_s;
	IO_SHDR.MCPCNT.bit.MCPXO	= shdr_smc->mcpcnt.mcpx_o;
	IO_SHDR.MCPCNT.bit.MCPXK	= shdr_smc->mcpcnt.mcpx_k;

	// MMCRCNT.
	IO_SHDR.MMCRCNT.bit.MMCRS	= shdr_smc->mmcrcnt.mmcr_s;
	IO_SHDR.MMCRCNT.bit.MMCRK	= shdr_smc->mmcrcnt.mmcr_k;

	// MOLECNT.
	IO_SHDR.MOLECNT.bit.MOLES	= shdr_smc->molecnt.mole_s;
	IO_SHDR.MOLECNT.bit.MOLEO	= shdr_smc->molecnt.mole_o;
	IO_SHDR.MOLECNT.bit.MOLEK	= shdr_smc->molecnt.mole_k;

	// MMVECNT.
	IO_SHDR.MMVECNT.bit.MMVES	= shdr_smc->mmvecnt.mmve_s;
	IO_SHDR.MMVECNT.bit.MMVEO	= shdr_smc->mmvecnt.mmve_o;
	IO_SHDR.MMVECNT.bit.MMVEK	= shdr_smc->mmvecnt.mmve_k;

	// MCPXECNT.
	IO_SHDR.MCPXECNT.bit.MCPXES	= shdr_smc->mcpxecnt.mcpxe_s;
	IO_SHDR.MCPXECNT.bit.MCPXEO	= shdr_smc->mcpxecnt.mcpxe_o;
	IO_SHDR.MCPXECNT.bit.MCPXEK	= shdr_smc->mcpxecnt.mcpxe_k;

	// MVLCNT.
	IO_SHDR.MVLCNT.bit.MVLEN	= shdr_smc->mvlcnt.mvl_en;
	IO_SHDR.MVLCNT.bit.MVLTH	= shdr_smc->mvlcnt.mvl_threshold;
	IO_SHDR.MVLCNT.bit.MVLCTH	= shdr_smc->mvlcnt.mvl_count_threshold;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Get_Smc( T_IM_SHDR_SMC* const shdr_smc )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_smc == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Smc() error. shdr_smc = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// MCAMD.
	shdr_smc->mcarmd.mca_mode		= IO_SHDR.MCARMD.bit.MCAMD;
	shdr_smc->mcarmd.mcr_mode		= IO_SHDR.MCARMD.bit.MCRMD;

	// MCMPMD.
	shdr_smc->mcmpmd.mcmp_mode		= IO_SHDR.MCMPMD.bit.MCMPMD;
	shdr_smc->mcmpmd.mvw_en			= IO_SHDR.MCMPMD.bit.MVWEN;

	// MMVVAL.
	shdr_smc->mmvval.mmv_x			= IO_SHDR.MMVVAL.bit.MMVX;
	shdr_smc->mmvval.mmv_y			= IO_SHDR.MMVVAL.bit.MMVY;

	// MMVRCNT.
	shdr_smc->mmvrcnt.mmvro_x		= IO_SHDR.MMVRCNT.bit.MMVROX;
	shdr_smc->mmvrcnt.mmvro_y		= IO_SHDR.MMVRCNT.bit.MMVROY;
	shdr_smc->mmvrcnt.mmvrk_x		= IO_SHDR.MMVRCNT.bit.MMVRKX;
	shdr_smc->mmvrcnt.mmvrk_y		= IO_SHDR.MMVRCNT.bit.MMVRKY;

	// MDBCNT.
	shdr_smc->mdbcnt.mdb_x			= IO_SHDR.MDBCNT.bit.MDBX;
	shdr_smc->mdbcnt.mdb_y			= IO_SHDR.MDBCNT.bit.MDBY;

	// MDBROCNT.
	shdr_smc->mdbrocnt.mdbro_x		= IO_SHDR.MDBROCNT.bit.MDBROX;
	shdr_smc->mdbrocnt.mdbro_y		= IO_SHDR.MDBROCNT.bit.MDBROY;
	shdr_smc->mdbrocnt.mdbrk_x		= IO_SHDR.MDBROCNT.bit.MDBRKX;
	shdr_smc->mdbrocnt.mdbrk_y		= IO_SHDR.MDBROCNT.bit.MDBRKY;

	// MOLRCNT.
	shdr_smc->molrcnt.molr_sm		= IO_SHDR.MOLRCNT.bit.MOLRSM;
	shdr_smc->molrcnt.molr_ss		= IO_SHDR.MOLRCNT.bit.MOLRSS;
	shdr_smc->molrcnt.molr_o		= IO_SHDR.MOLRCNT.bit.MOLRO;
	shdr_smc->molrcnt.molr_k		= IO_SHDR.MOLRCNT.bit.MOLRK;

	// MCPCNT.
	shdr_smc->mcpcnt.mcpx_s			= IO_SHDR.MCPCNT.bit.MCPXS;
	shdr_smc->mcpcnt.mcpx_o			= IO_SHDR.MCPCNT.bit.MCPXO;
	shdr_smc->mcpcnt.mcpx_k			= IO_SHDR.MCPCNT.bit.MCPXK;

	// MMCRCNT.
	shdr_smc->mmcrcnt.mmcr_s		= IO_SHDR.MMCRCNT.bit.MMCRS;
	shdr_smc->mmcrcnt.mmcr_k		= IO_SHDR.MMCRCNT.bit.MMCRK;

	// MOLECNT.
	shdr_smc->molecnt.mole_s		= IO_SHDR.MOLECNT.bit.MOLES;
	shdr_smc->molecnt.mole_o		= IO_SHDR.MOLECNT.bit.MOLEO;
	shdr_smc->molecnt.mole_k		= IO_SHDR.MOLECNT.bit.MOLEK;

	// MMVECNT.
	shdr_smc->mmvecnt.mmve_s		= IO_SHDR.MMVECNT.bit.MMVES;
	shdr_smc->mmvecnt.mmve_o		= IO_SHDR.MMVECNT.bit.MMVEO;
	shdr_smc->mmvecnt.mmve_k		= IO_SHDR.MMVECNT.bit.MMVEK;

	// MCPXECNT.
	shdr_smc->mcpxecnt.mcpxe_s		= IO_SHDR.MCPXECNT.bit.MCPXES;
	shdr_smc->mcpxecnt.mcpxe_o		= IO_SHDR.MCPXECNT.bit.MCPXEO;
	shdr_smc->mcpxecnt.mcpxe_k		= IO_SHDR.MCPXECNT.bit.MCPXEK;

	// MVLCNT.
	shdr_smc->mvlcnt.mvl_en					= IO_SHDR.MVLCNT.bit.MVLEN;
	shdr_smc->mvlcnt.mvl_threshold			= IO_SHDR.MVLCNT.bit.MVLTH;
	shdr_smc->mvlcnt.mvl_count_threshold	= IO_SHDR.MVLCNT.bit.MVLCTH;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}


ImShdr3 *im_shdr3_new(void)
{
	ImShdr3* self = k_object_new_with_private(IM_TYPE_SHDR3,sizeof(ImShdr3Private));
	return self;
}


