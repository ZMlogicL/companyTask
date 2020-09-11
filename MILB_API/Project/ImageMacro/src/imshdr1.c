/*
 * imshdr1.c
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

#include "imshdr1.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImShdr1, im_shdr1);
#define IM_SHDR1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImShdr1Private, IM_TYPE_SHDR1))

struct _ImShdr1Private
{
	int a;
};


static void im_shdr1_constructor(ImShdr1 *self)
{
//	ImShdr1Private *priv = IM_SHDR1_GET_PRIVATE(self);
}

static void im_shdr1_destructor(ImShdr1 *self)
{
//	ImShdr1Private *priv = IM_SHDR1_GET_PRIVATE(self);
}

/*
PUBLIC
 */

INT32 Im_SHDR_Set_Pre(  const T_IM_SHDR_PRE* const shdr_pre )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_pre == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_Pre() error. shdr_pre = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_pre->pre_mode.cus_mode > D_IM_SHDR_CUS_YCC420_PADDING ) {
		Ddim_Assertion(("Im_SHDR_Set_Pre() error. cus_mode is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_pre->pre_mode.degamma_mode > D_IM_SHDR_DEGAMMA_BITEXP ) {
		Ddim_Assertion(("Im_SHDR_Set_Pre() error. degamma_mode is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// PREMD.
	IO_SHDR.PREMD.bit.CUSMD	= shdr_pre->pre_mode.cus_mode;
	IO_SHDR.PREMD.bit.DGMD	= shdr_pre->pre_mode.degamma_mode;

	// Y2RCOEF.
	im_shdr_set_reg_signed_a( IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_0, shdr_pre->y2r_coef[ 0 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_1, shdr_pre->y2r_coef[ 1 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_2, shdr_pre->y2r_coef[ 2 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_3, shdr_pre->y2r_coef[ 3 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_4, shdr_pre->y2r_coef[ 4 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_5, shdr_pre->y2r_coef[ 5 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_6, shdr_pre->y2r_coef[ 6 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_7, shdr_pre->y2r_coef[ 7 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_8, shdr_pre->y2r_coef[ 8 ] );

	// PREY2RCLPUL0.
	IO_SHDR.PREY2RCLPUL0.bit.PREY2RCLPUL0_0	= shdr_pre->y2r_clp.upper_long0[ 0 ];
	IO_SHDR.PREY2RCLPUL0.bit.PREY2RCLPUL0_1	= shdr_pre->y2r_clp.upper_long0[ 1 ];
	IO_SHDR.PREY2RCLPUL0.bit.PREY2RCLPUL0_2	= shdr_pre->y2r_clp.upper_long0[ 2 ];

	// PREY2RCLPLL0.
	IO_SHDR.PREY2RCLPLL0.bit.PREY2RCLPLL0_0	= shdr_pre->y2r_clp.lower_long0[ 0 ];
	IO_SHDR.PREY2RCLPLL0.bit.PREY2RCLPLL0_1	= shdr_pre->y2r_clp.lower_long0[ 1 ];
	IO_SHDR.PREY2RCLPLL0.bit.PREY2RCLPLL0_2	= shdr_pre->y2r_clp.lower_long0[ 2 ];

	// PREY2RCLPUS.
	IO_SHDR.PREY2RCLPUS.bit.PREY2RCLPUS_0	= shdr_pre->y2r_clp.upper_short[ 0 ];
	IO_SHDR.PREY2RCLPUS.bit.PREY2RCLPUS_1	= shdr_pre->y2r_clp.upper_short[ 1 ];
	IO_SHDR.PREY2RCLPUS.bit.PREY2RCLPUS_2	= shdr_pre->y2r_clp.upper_short[ 2 ];

	// PREY2RCLPLS.
	IO_SHDR.PREY2RCLPLS.bit.PREY2RCLPLS_0	= shdr_pre->y2r_clp.lower_short[ 0 ];
	IO_SHDR.PREY2RCLPLS.bit.PREY2RCLPLS_1	= shdr_pre->y2r_clp.lower_short[ 1 ];
	IO_SHDR.PREY2RCLPLS.bit.PREY2RCLPLS_2	= shdr_pre->y2r_clp.lower_short[ 2 ];

	// R2YCOEF.
	im_shdr_set_reg_signed_a( IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_0, shdr_pre->r2y_coef[ 0 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_1, shdr_pre->r2y_coef[ 1 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_2, shdr_pre->r2y_coef[ 2 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_3, shdr_pre->r2y_coef[ 3 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_4, shdr_pre->r2y_coef[ 4 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_5, shdr_pre->r2y_coef[ 5 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_6, shdr_pre->r2y_coef[ 6 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_7, shdr_pre->r2y_coef[ 7 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_8, shdr_pre->r2y_coef[ 8 ] );

	// PRER2YCLPUL.
	IO_SHDR.PRER2YCLPUL.bit.PRER2YCLPUL_0	= shdr_pre->r2y_clp.upper_long_y;
	im_shdr_set_reg_signed_a( IO_SHDR.PRER2YCLPUL, union io_shdr_prer2yclpul, PRER2YCLPUL_1, shdr_pre->r2y_clp.upper_long_c[ 0 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.PRER2YCLPUL, union io_shdr_prer2yclpul, PRER2YCLPUL_2, shdr_pre->r2y_clp.upper_long_c[ 1 ] );

	// PRER2YCLPLL.
	IO_SHDR.PRER2YCLPLL.bit.PRER2YCLPLL_0	= shdr_pre->r2y_clp.lower_long_y;
	im_shdr_set_reg_signed_a( IO_SHDR.PRER2YCLPLL, union io_shdr_prer2yclpll, PRER2YCLPLL_1, shdr_pre->r2y_clp.lower_long_c[ 0 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.PRER2YCLPLL, union io_shdr_prer2yclpll, PRER2YCLPLL_2, shdr_pre->r2y_clp.lower_long_c[ 1 ] );

	// PRER2YCLPUS.
	IO_SHDR.PRER2YCLPUS.bit.PRER2YCLPUS_0	= shdr_pre->r2y_clp.upper_short_y;
	im_shdr_set_reg_signed_a( IO_SHDR.PRER2YCLPUS, union io_shdr_prer2yclpus, PRER2YCLPUS_1, shdr_pre->r2y_clp.upper_short_c[ 0 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.PRER2YCLPUS, union io_shdr_prer2yclpus, PRER2YCLPUS_2, shdr_pre->r2y_clp.upper_short_c[ 1 ] );

	// PRER2YCLPLS.
	IO_SHDR.PRER2YCLPLS.bit.PRER2YCLPLS_0	= shdr_pre->r2y_clp.lower_short_y;
	im_shdr_set_reg_signed_a( IO_SHDR.PRER2YCLPLS, union io_shdr_prer2yclpls, PRER2YCLPLS_1, shdr_pre->r2y_clp.lower_short_c[ 0 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.PRER2YCLPLS, union io_shdr_prer2yclpls, PRER2YCLPLS_2, shdr_pre->r2y_clp.lower_short_c[ 1 ] );

	// SKNOFS.
	IO_SHDR.SKNOFS.bit.SKNOFS_0	= shdr_pre->short_knee.offset[ 0 ];
	IO_SHDR.SKNOFS.bit.SKNOFS_1	= shdr_pre->short_knee.offset[ 1 ];
	IO_SHDR.SKNOFS.bit.SKNOFS_2	= shdr_pre->short_knee.offset[ 2 ];

	// SKNSL.
	IO_SHDR.SKNSL.bit.SKNSL_0	= shdr_pre->short_knee.slope[ 0 ];
	IO_SHDR.SKNSL.bit.SKNSL_1	= shdr_pre->short_knee.slope[ 1 ];
	IO_SHDR.SKNSL.bit.SKNSL_2	= shdr_pre->short_knee.slope[ 2 ];

	// SKNB1/2.
	IO_SHDR.SKNB1.bit.SKNB		= shdr_pre->short_knee.boundary[ 0 ];
	IO_SHDR.SKNB2.bit.SKNB		= shdr_pre->short_knee.boundary[ 1 ];

	// LKNOFS.
	IO_SHDR.LKNOFS.bit.LKNOFS_0	= shdr_pre->long_knee.offset[ 0 ];
	IO_SHDR.LKNOFS.bit.LKNOFS_1	= shdr_pre->long_knee.offset[ 1 ];
	IO_SHDR.LKNOFS.bit.LKNOFS_2	= shdr_pre->long_knee.offset[ 2 ];

	// LKNSL.
	IO_SHDR.LKNSL.bit.LKNSL_0	= shdr_pre->long_knee.slope[ 0 ];
	IO_SHDR.LKNSL.bit.LKNSL_1	= shdr_pre->long_knee.slope[ 1 ];
	IO_SHDR.LKNSL.bit.LKNSL_2	= shdr_pre->long_knee.slope[ 2 ];

	// LKNB1/2.
	IO_SHDR.LKNB1.bit.LKNB		= shdr_pre->long_knee.boundary[ 0 ];
	IO_SHDR.LKNB2.bit.LKNB		= shdr_pre->long_knee.boundary[ 1 ];

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}


INT32 Im_SHDR_Get_Pre( T_IM_SHDR_PRE* const shdr_pre )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_pre == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Pre() error. shdr_pre = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// PREMD.
	shdr_pre->pre_mode.cus_mode			= IO_SHDR.PREMD.bit.CUSMD;
	shdr_pre->pre_mode.degamma_mode		= IO_SHDR.PREMD.bit.DGMD;

	// Y2RCOEF.
	im_shdr_get_reg_signed_a( shdr_pre->y2r_coef[ 0 ], IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_0 );
	im_shdr_get_reg_signed_a( shdr_pre->y2r_coef[ 1 ], IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_1 );
	im_shdr_get_reg_signed_a( shdr_pre->y2r_coef[ 2 ], IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_2 );
	im_shdr_get_reg_signed_a( shdr_pre->y2r_coef[ 3 ], IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_3 );
	im_shdr_get_reg_signed_a( shdr_pre->y2r_coef[ 4 ], IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_4 );
	im_shdr_get_reg_signed_a( shdr_pre->y2r_coef[ 5 ], IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_5 );
	im_shdr_get_reg_signed_a( shdr_pre->y2r_coef[ 6 ], IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_6 );
	im_shdr_get_reg_signed_a( shdr_pre->y2r_coef[ 7 ], IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_7 );
	im_shdr_get_reg_signed_a( shdr_pre->y2r_coef[ 8 ], IO_SHDR.Y2RCOEF, union io_shdr_y2rcoef, Y2RCOEF_8 );

	// PREY2RCLPUL0.
	shdr_pre->y2r_clp.upper_long0[ 0 ]	= IO_SHDR.PREY2RCLPUL0.bit.PREY2RCLPUL0_0;
	shdr_pre->y2r_clp.upper_long0[ 1 ]	= IO_SHDR.PREY2RCLPUL0.bit.PREY2RCLPUL0_1;
	shdr_pre->y2r_clp.upper_long0[ 2 ]	= IO_SHDR.PREY2RCLPUL0.bit.PREY2RCLPUL0_2;

	// PREY2RCLPLL0.
	shdr_pre->y2r_clp.lower_long0[ 0 ]	= IO_SHDR.PREY2RCLPLL0.bit.PREY2RCLPLL0_0;
	shdr_pre->y2r_clp.lower_long0[ 1 ]	= IO_SHDR.PREY2RCLPLL0.bit.PREY2RCLPLL0_1;
	shdr_pre->y2r_clp.lower_long0[ 2 ]	= IO_SHDR.PREY2RCLPLL0.bit.PREY2RCLPLL0_2;

	// PREY2RCLPUS.
	shdr_pre->y2r_clp.upper_short[ 0 ]	= IO_SHDR.PREY2RCLPUS.bit.PREY2RCLPUS_0;
	shdr_pre->y2r_clp.upper_short[ 1 ]	= IO_SHDR.PREY2RCLPUS.bit.PREY2RCLPUS_1;
	shdr_pre->y2r_clp.upper_short[ 2 ]	= IO_SHDR.PREY2RCLPUS.bit.PREY2RCLPUS_2;

	// PREY2RCLPLS.
	shdr_pre->y2r_clp.lower_short[ 0 ]	= IO_SHDR.PREY2RCLPLS.bit.PREY2RCLPLS_0;
	shdr_pre->y2r_clp.lower_short[ 1 ]	= IO_SHDR.PREY2RCLPLS.bit.PREY2RCLPLS_1;
	shdr_pre->y2r_clp.lower_short[ 2 ]	= IO_SHDR.PREY2RCLPLS.bit.PREY2RCLPLS_2;

	// R2YCOEF.
	im_shdr_get_reg_signed_a( shdr_pre->r2y_coef[ 0 ], IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_0 );
	im_shdr_get_reg_signed_a( shdr_pre->r2y_coef[ 1 ], IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_1 );
	im_shdr_get_reg_signed_a( shdr_pre->r2y_coef[ 2 ], IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_2 );
	im_shdr_get_reg_signed_a( shdr_pre->r2y_coef[ 3 ], IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_3 );
	im_shdr_get_reg_signed_a( shdr_pre->r2y_coef[ 4 ], IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_4 );
	im_shdr_get_reg_signed_a( shdr_pre->r2y_coef[ 5 ], IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_5 );
	im_shdr_get_reg_signed_a( shdr_pre->r2y_coef[ 6 ], IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_6 );
	im_shdr_get_reg_signed_a( shdr_pre->r2y_coef[ 7 ], IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_7 );
	im_shdr_get_reg_signed_a( shdr_pre->r2y_coef[ 8 ], IO_SHDR.R2YCOEF, union io_shdr_r2ycoef, R2YCOEF_8 );

	// PRER2YCLPUL.
	shdr_pre->r2y_clp.upper_long_y		= IO_SHDR.PRER2YCLPUL.bit.PRER2YCLPUL_0;
	im_shdr_get_reg_signed_a( shdr_pre->r2y_clp.upper_long_c[ 0 ], IO_SHDR.PRER2YCLPUL, union io_shdr_prer2yclpul, PRER2YCLPUL_1 );
	im_shdr_get_reg_signed_a( shdr_pre->r2y_clp.upper_long_c[ 1 ], IO_SHDR.PRER2YCLPUL, union io_shdr_prer2yclpul, PRER2YCLPUL_2 );

	// PRER2YCLPLL.
	shdr_pre->r2y_clp.lower_long_y		= IO_SHDR.PRER2YCLPLL.bit.PRER2YCLPLL_0;
	im_shdr_get_reg_signed_a( shdr_pre->r2y_clp.lower_long_c[ 0 ], IO_SHDR.PRER2YCLPLL, union io_shdr_prer2yclpll, PRER2YCLPLL_1 );
	im_shdr_get_reg_signed_a( shdr_pre->r2y_clp.lower_long_c[ 1 ], IO_SHDR.PRER2YCLPLL, union io_shdr_prer2yclpll, PRER2YCLPLL_2 );

	// PRER2YCLPUS.
	shdr_pre->r2y_clp.upper_short_y		= IO_SHDR.PRER2YCLPUS.bit.PRER2YCLPUS_0;
	im_shdr_get_reg_signed_a( shdr_pre->r2y_clp.upper_short_c[ 0 ], IO_SHDR.PRER2YCLPUS, union io_shdr_prer2yclpus, PRER2YCLPUS_1 );
	im_shdr_get_reg_signed_a( shdr_pre->r2y_clp.upper_short_c[ 1 ], IO_SHDR.PRER2YCLPUS, union io_shdr_prer2yclpus, PRER2YCLPUS_2 );

	// PRER2YCLPLS.
	shdr_pre->r2y_clp.lower_short_y		= IO_SHDR.PRER2YCLPLS.bit.PRER2YCLPLS_0;
	im_shdr_get_reg_signed_a( shdr_pre->r2y_clp.lower_short_c[ 0 ], IO_SHDR.PRER2YCLPLS, union io_shdr_prer2yclpls, PRER2YCLPLS_1 );
	im_shdr_get_reg_signed_a( shdr_pre->r2y_clp.lower_short_c[ 1 ], IO_SHDR.PRER2YCLPLS, union io_shdr_prer2yclpls, PRER2YCLPLS_2 );

	// SKNOFS.
	shdr_pre->short_knee.offset[ 0 ]	= IO_SHDR.SKNOFS.bit.SKNOFS_0;
	shdr_pre->short_knee.offset[ 1 ]	= IO_SHDR.SKNOFS.bit.SKNOFS_1;
	shdr_pre->short_knee.offset[ 2 ]	= IO_SHDR.SKNOFS.bit.SKNOFS_2;

	// SKNSL.
	shdr_pre->short_knee.slope[ 0 ]		= IO_SHDR.SKNSL.bit.SKNSL_0;
	shdr_pre->short_knee.slope[ 1 ]		= IO_SHDR.SKNSL.bit.SKNSL_1;
	shdr_pre->short_knee.slope[ 2 ]		= IO_SHDR.SKNSL.bit.SKNSL_2;

	// SKNB1/2.
	shdr_pre->short_knee.boundary[ 0 ]	= IO_SHDR.SKNB1.bit.SKNB;
	shdr_pre->short_knee.boundary[ 1 ]	= IO_SHDR.SKNB2.bit.SKNB;

	// LKNOFS.
	shdr_pre->long_knee.offset[ 0 ]		= IO_SHDR.LKNOFS.bit.LKNOFS_0;
	shdr_pre->long_knee.offset[ 1 ]		= IO_SHDR.LKNOFS.bit.LKNOFS_1;
	shdr_pre->long_knee.offset[ 2 ]		= IO_SHDR.LKNOFS.bit.LKNOFS_2;

	// LKNSL.
	shdr_pre->long_knee.slope[ 0 ]		= IO_SHDR.LKNSL.bit.LKNSL_0;
	shdr_pre->long_knee.slope[ 1 ]		= IO_SHDR.LKNSL.bit.LKNSL_1;
	shdr_pre->long_knee.slope[ 2 ]		= IO_SHDR.LKNSL.bit.LKNSL_2;

	// LKNB1/2.
	shdr_pre->long_knee.boundary[ 0 ]	= IO_SHDR.LKNB1.bit.LKNB;
	shdr_pre->long_knee.boundary[ 1 ]	= IO_SHDR.LKNB2.bit.LKNB;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Set_Fmd( const T_IM_SHDR_FMD* const shdr_fmd )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_fmd == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_Fmd() error. shdr_fmd = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_fmd->weight_base > D_IM_SHDR_WGHTBASE_RGB ) {
		Ddim_Assertion(("Im_SHDR_Set_Fmd() error. weight_base is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_fmd->exp77_mode > D_IM_SHDR_EXP77MD_PERIMAXVAL ) {
		Ddim_Assertion(("Im_SHDR_Set_Fmd() error. exp77_mode is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_fmd->fmd_sel > D_IM_SHDR_FMDSEL_REDUCTION ) {
		Ddim_Assertion(("Im_SHDR_Set_Fmd() error. fmd_sel is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// EPBD.
	IO_SHDR.EPBD.bit.EPBD_1			= shdr_fmd->ep_boundary[ 1 ];
	IO_SHDR.EPBD.bit.EPBD_2			= shdr_fmd->ep_boundary[ 2 ];
	IO_SHDR.EPBD.bit.EPBD_3			= shdr_fmd->ep_boundary[ 3 ];

	// EPOF.
	IO_SHDR.EPOF.bit.EPOF_0			= shdr_fmd->ep_offset[ 0 ];
	IO_SHDR.EPOF.bit.EPOF_1			= shdr_fmd->ep_offset[ 1 ];
	IO_SHDR.EPOF.bit.EPOF_2			= shdr_fmd->ep_offset[ 2 ];
	IO_SHDR.EPOF.bit.EPOF_3			= shdr_fmd->ep_offset[ 3 ];

	// EPBLD.
	IO_SHDR.EPBLD.bit.EPBLD			= shdr_fmd->ep_blend;

	// FDWEIGHT.
	IO_SHDR.FDWEIGHT.bit.FDWEIGHT	= shdr_fmd->fd_weight;

	// MVCNT.
	IO_SHDR.MVCNT.bit.MVBD			= shdr_fmd->mvcnt.bounds;
	IO_SHDR.MVCNT.bit.MVTH			= shdr_fmd->mvcnt.threshold;
	im_shdr_set_reg_signed( IO_SHDR.MVCNT, union io_shdr_mvcnt, MVGR, shdr_fmd->mvcnt.gr );

	// BLDROFS.
	IO_SHDR.BLDROFS.bit.BLDROFS_0	= shdr_fmd->bldr_offset[ 0 ];
	IO_SHDR.BLDROFS.bit.BLDROFS_1	= shdr_fmd->bldr_offset[ 1 ];
	IO_SHDR.BLDROFS.bit.BLDROFS_2	= shdr_fmd->bldr_offset[ 2 ];
	IO_SHDR.BLDROFS.bit.BLDROFS_3	= shdr_fmd->bldr_offset[ 3 ];
	IO_SHDR.BLDROFS.bit.BLDROFS_4	= shdr_fmd->bldr_offset[ 4 ];

	// BLDRSL.
	IO_SHDR.BLDRSL.bit.BLDRSL_0		= shdr_fmd->bldr_slope[ 0 ];
	IO_SHDR.BLDRSL.bit.BLDRSL_1		= shdr_fmd->bldr_slope[ 1 ];
	IO_SHDR.BLDRSL.bit.BLDRSL_2		= shdr_fmd->bldr_slope[ 2 ];
	IO_SHDR.BLDRSL.bit.BLDRSL_3		= shdr_fmd->bldr_slope[ 3 ];
	IO_SHDR.BLDRSL.bit.BLDRSL_4		= shdr_fmd->bldr_slope[ 4 ];

	// BLDRB.
	IO_SHDR.BLDRB.bit.BLDRB_1		= shdr_fmd->bldr_boundary[ 1 ];
	IO_SHDR.BLDRB.bit.BLDRB_2		= shdr_fmd->bldr_boundary[ 2 ];
	IO_SHDR.BLDRB.bit.BLDRB_3		= shdr_fmd->bldr_boundary[ 3 ];
	IO_SHDR.BLDRB.bit.BLDRB_4		= shdr_fmd->bldr_boundary[ 4 ];

	// WGHTR2YCOEF.
	im_shdr_set_reg_signed_a( IO_SHDR.WGHTR2YCOEF, union io_shdr_wghtr2ycoef, WGHTR2YCOEF_0, shdr_fmd->weight_r2y_coef[ 0 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.WGHTR2YCOEF, union io_shdr_wghtr2ycoef, WGHTR2YCOEF_1, shdr_fmd->weight_r2y_coef[ 1 ] );
	im_shdr_set_reg_signed_a( IO_SHDR.WGHTR2YCOEF, union io_shdr_wghtr2ycoef, WGHTR2YCOEF_2, shdr_fmd->weight_r2y_coef[ 2 ] );

	// WGHTR2YCLP.
	IO_SHDR.WGHTR2YCLP.bit.WGHTR2YCLPU	= shdr_fmd->weight_r2y_clp.upper;
	IO_SHDR.WGHTR2YCLP.bit.WGHTR2YCLPL	= shdr_fmd->weight_r2y_clp.lower;

	// WGHTBASE.
	IO_SHDR.WGHTBASE.bit.WGHTBASE		= shdr_fmd->weight_base;

	// WGHTROFS.
	IO_SHDR.WGHTROFS.bit.WGHTROFS_0		= shdr_fmd->weight_offset[ 0 ][ 0 ];
	IO_SHDR.WGHTROFS.bit.WGHTROFS_1		= shdr_fmd->weight_offset[ 0 ][ 1 ];
	IO_SHDR.WGHTROFS.bit.WGHTROFS_2		= shdr_fmd->weight_offset[ 0 ][ 2 ];
	IO_SHDR.WGHTROFS.bit.WGHTROFS_3		= shdr_fmd->weight_offset[ 0 ][ 3 ];
	IO_SHDR.WGHTROFS.bit.WGHTROFS_4		= shdr_fmd->weight_offset[ 0 ][ 4 ];

	// WGHTGOFS.
	IO_SHDR.WGHTGOFS.bit.WGHTGOFS_0		= shdr_fmd->weight_offset[ 1 ][ 0 ];
	IO_SHDR.WGHTGOFS.bit.WGHTGOFS_1		= shdr_fmd->weight_offset[ 1 ][ 1 ];
	IO_SHDR.WGHTGOFS.bit.WGHTGOFS_2		= shdr_fmd->weight_offset[ 1 ][ 2 ];
	IO_SHDR.WGHTGOFS.bit.WGHTGOFS_3		= shdr_fmd->weight_offset[ 1 ][ 3 ];
	IO_SHDR.WGHTGOFS.bit.WGHTGOFS_4		= shdr_fmd->weight_offset[ 1 ][ 4 ];

	// WGHTBOFS.
	IO_SHDR.WGHTBOFS.bit.WGHTBOFS_0		= shdr_fmd->weight_offset[ 2 ][ 0 ];
	IO_SHDR.WGHTBOFS.bit.WGHTBOFS_1		= shdr_fmd->weight_offset[ 2 ][ 1 ];
	IO_SHDR.WGHTBOFS.bit.WGHTBOFS_2		= shdr_fmd->weight_offset[ 2 ][ 2 ];
	IO_SHDR.WGHTBOFS.bit.WGHTBOFS_3		= shdr_fmd->weight_offset[ 2 ][ 3 ];
	IO_SHDR.WGHTBOFS.bit.WGHTBOFS_4		= shdr_fmd->weight_offset[ 2 ][ 4 ];

	// WGHTRSL.
	IO_SHDR.WGHTRSL.bit.WGHTRSL_0		= shdr_fmd->weight_slope[ 0 ][ 0 ];
	IO_SHDR.WGHTRSL.bit.WGHTRSL_1		= shdr_fmd->weight_slope[ 0 ][ 1 ];
	IO_SHDR.WGHTRSL.bit.WGHTRSL_2		= shdr_fmd->weight_slope[ 0 ][ 2 ];
	IO_SHDR.WGHTRSL.bit.WGHTRSL_3		= shdr_fmd->weight_slope[ 0 ][ 3 ];
	IO_SHDR.WGHTRSL.bit.WGHTRSL_4		= shdr_fmd->weight_slope[ 0 ][ 4 ];

	// WGHTGSL.
	IO_SHDR.WGHTGSL.bit.WGHTGSL_0		= shdr_fmd->weight_slope[ 1 ][ 0 ];
	IO_SHDR.WGHTGSL.bit.WGHTGSL_1		= shdr_fmd->weight_slope[ 1 ][ 1 ];
	IO_SHDR.WGHTGSL.bit.WGHTGSL_2		= shdr_fmd->weight_slope[ 1 ][ 2 ];
	IO_SHDR.WGHTGSL.bit.WGHTGSL_3		= shdr_fmd->weight_slope[ 1 ][ 3 ];
	IO_SHDR.WGHTGSL.bit.WGHTGSL_4		= shdr_fmd->weight_slope[ 1 ][ 4 ];

	// WGHTBSL.
	IO_SHDR.WGHTBSL.bit.WGHTBSL_0		= shdr_fmd->weight_slope[ 2 ][ 0 ];
	IO_SHDR.WGHTBSL.bit.WGHTBSL_1		= shdr_fmd->weight_slope[ 2 ][ 1 ];
	IO_SHDR.WGHTBSL.bit.WGHTBSL_2		= shdr_fmd->weight_slope[ 2 ][ 2 ];
	IO_SHDR.WGHTBSL.bit.WGHTBSL_3		= shdr_fmd->weight_slope[ 2 ][ 3 ];
	IO_SHDR.WGHTBSL.bit.WGHTBSL_4		= shdr_fmd->weight_slope[ 2 ][ 4 ];

	// WGHTRB.
	IO_SHDR.WGHTRB.bit.WGHTRB_1			= shdr_fmd->weight_boundary[ 0 ][ 1 ];
	IO_SHDR.WGHTRB.bit.WGHTRB_2			= shdr_fmd->weight_boundary[ 0 ][ 2 ];
	IO_SHDR.WGHTRB.bit.WGHTRB_3			= shdr_fmd->weight_boundary[ 0 ][ 3 ];
	IO_SHDR.WGHTRB.bit.WGHTRB_4			= shdr_fmd->weight_boundary[ 0 ][ 4 ];

	// WGHTGB.
	IO_SHDR.WGHTGB.bit.WGHTGB_1			= shdr_fmd->weight_boundary[ 1 ][ 1 ];
	IO_SHDR.WGHTGB.bit.WGHTGB_2			= shdr_fmd->weight_boundary[ 1 ][ 2 ];
	IO_SHDR.WGHTGB.bit.WGHTGB_3			= shdr_fmd->weight_boundary[ 1 ][ 3 ];
	IO_SHDR.WGHTGB.bit.WGHTGB_4			= shdr_fmd->weight_boundary[ 1 ][ 4 ];

	// WGHTBB.
	IO_SHDR.WGHTBB.bit.WGHTBB_1			= shdr_fmd->weight_boundary[ 2 ][ 1 ];
	IO_SHDR.WGHTBB.bit.WGHTBB_2			= shdr_fmd->weight_boundary[ 2 ][ 2 ];
	IO_SHDR.WGHTBB.bit.WGHTBB_3			= shdr_fmd->weight_boundary[ 2 ][ 3 ];
	IO_SHDR.WGHTBB.bit.WGHTBB_4			= shdr_fmd->weight_boundary[ 2 ][ 4 ];

	// ISOTH.
	IO_SHDR.ISOTH.bit.ISOTH2			= shdr_fmd->iso_threshold;

	// ISOCOEF.
	IO_SHDR.ISOCOEF.bit.ISO2K0			= shdr_fmd->iso_coef[ 0 ];
	IO_SHDR.ISOCOEF.bit.ISO2K1			= shdr_fmd->iso_coef[ 1 ];
	IO_SHDR.ISOCOEF.bit.ISO2K2			= shdr_fmd->iso_coef[ 2 ];
	IO_SHDR.ISOCOEF.bit.ISO2K3			= shdr_fmd->iso_coef[ 3 ];
	IO_SHDR.ISOCOEF.bit.ISO2K4			= shdr_fmd->iso_coef[ 4 ];
	IO_SHDR.ISOCOEF.bit.ISO2K5			= shdr_fmd->iso_coef[ 5 ];

	// SATTH.
	IO_SHDR.SATTH.bit.SATTH				= shdr_fmd->sat_threshold;

	// EXP77MD.
	IO_SHDR.EXP77MD.bit.EXP77MD			= shdr_fmd->exp77_mode;

	// EXP77MD.
	IO_SHDR.FMDSEL.bit.FMDSEL			= shdr_fmd->fmd_sel;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}


INT32 Im_SHDR_Get_Fmd( T_IM_SHDR_FMD* const shdr_fmd )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_fmd == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Fmd() error. shdr_fmd = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// EPBD.
	shdr_fmd->ep_boundary[ 1 ]		= IO_SHDR.EPBD.bit.EPBD_1;
	shdr_fmd->ep_boundary[ 2 ]		= IO_SHDR.EPBD.bit.EPBD_2;
	shdr_fmd->ep_boundary[ 3 ]		= IO_SHDR.EPBD.bit.EPBD_3;

	// EPOF.
	shdr_fmd->ep_offset[ 0 ]		= IO_SHDR.EPOF.bit.EPOF_0;
	shdr_fmd->ep_offset[ 1 ]		= IO_SHDR.EPOF.bit.EPOF_1;
	shdr_fmd->ep_offset[ 2 ]		= IO_SHDR.EPOF.bit.EPOF_2;
	shdr_fmd->ep_offset[ 3 ]		= IO_SHDR.EPOF.bit.EPOF_3;

	// EPBLD.
	shdr_fmd->ep_blend				= IO_SHDR.EPBLD.bit.EPBLD;

	// FDWEIGHT.
	shdr_fmd->fd_weight				= IO_SHDR.FDWEIGHT.bit.FDWEIGHT;

	// MVCNT.
	shdr_fmd->mvcnt.bounds			= IO_SHDR.MVCNT.bit.MVBD;
	shdr_fmd->mvcnt.threshold		= IO_SHDR.MVCNT.bit.MVTH;
	im_shdr_get_reg_signed( shdr_fmd->mvcnt.gr, IO_SHDR.MVCNT, union io_shdr_mvcnt, MVGR );

	// BLDROFS.
	shdr_fmd->bldr_offset[ 0 ]		= IO_SHDR.BLDROFS.bit.BLDROFS_0;
	shdr_fmd->bldr_offset[ 1 ]		= IO_SHDR.BLDROFS.bit.BLDROFS_1;
	shdr_fmd->bldr_offset[ 2 ]		= IO_SHDR.BLDROFS.bit.BLDROFS_2;
	shdr_fmd->bldr_offset[ 3 ]		= IO_SHDR.BLDROFS.bit.BLDROFS_3;
	shdr_fmd->bldr_offset[ 4 ]		= IO_SHDR.BLDROFS.bit.BLDROFS_4;

	// BLDRSL.
	shdr_fmd->bldr_slope[ 0 ]		= IO_SHDR.BLDRSL.bit.BLDRSL_0;
	shdr_fmd->bldr_slope[ 1 ]		= IO_SHDR.BLDRSL.bit.BLDRSL_1;
	shdr_fmd->bldr_slope[ 2 ]		= IO_SHDR.BLDRSL.bit.BLDRSL_2;
	shdr_fmd->bldr_slope[ 3 ]		= IO_SHDR.BLDRSL.bit.BLDRSL_3;
	shdr_fmd->bldr_slope[ 4 ]		= IO_SHDR.BLDRSL.bit.BLDRSL_4;

	// BLDRB.
	shdr_fmd->bldr_boundary[ 1 ]	= IO_SHDR.BLDRB.bit.BLDRB_1;
	shdr_fmd->bldr_boundary[ 2 ]	= IO_SHDR.BLDRB.bit.BLDRB_2;
	shdr_fmd->bldr_boundary[ 3 ]	= IO_SHDR.BLDRB.bit.BLDRB_3;
	shdr_fmd->bldr_boundary[ 4 ]	= IO_SHDR.BLDRB.bit.BLDRB_4;

	// WGHTR2YCOEF.
	im_shdr_get_reg_signed_a( shdr_fmd->weight_r2y_coef[ 0 ], IO_SHDR.WGHTR2YCOEF, union io_shdr_wghtr2ycoef, WGHTR2YCOEF_0 );
	im_shdr_get_reg_signed_a( shdr_fmd->weight_r2y_coef[ 1 ], IO_SHDR.WGHTR2YCOEF, union io_shdr_wghtr2ycoef, WGHTR2YCOEF_1 );
	im_shdr_get_reg_signed_a( shdr_fmd->weight_r2y_coef[ 2 ], IO_SHDR.WGHTR2YCOEF, union io_shdr_wghtr2ycoef, WGHTR2YCOEF_2 );

	// WGHTR2YCLP.
	shdr_fmd->weight_r2y_clp.upper	= IO_SHDR.WGHTR2YCLP.bit.WGHTR2YCLPU;
	shdr_fmd->weight_r2y_clp.lower	= IO_SHDR.WGHTR2YCLP.bit.WGHTR2YCLPL;

	// WGHTBASE.
	shdr_fmd->weight_base			= IO_SHDR.WGHTBASE.bit.WGHTBASE;

	// WGHTROFS.
	shdr_fmd->weight_offset[ 0 ][ 0 ]	= IO_SHDR.WGHTROFS.bit.WGHTROFS_0;
	shdr_fmd->weight_offset[ 0 ][ 1 ]	= IO_SHDR.WGHTROFS.bit.WGHTROFS_1;
	shdr_fmd->weight_offset[ 0 ][ 2 ]	= IO_SHDR.WGHTROFS.bit.WGHTROFS_2;
	shdr_fmd->weight_offset[ 0 ][ 3 ]	= IO_SHDR.WGHTROFS.bit.WGHTROFS_3;
	shdr_fmd->weight_offset[ 0 ][ 4 ]	= IO_SHDR.WGHTROFS.bit.WGHTROFS_4;

	// WGHTGOFS.
	shdr_fmd->weight_offset[ 1 ][ 0 ]	= IO_SHDR.WGHTGOFS.bit.WGHTGOFS_0;
	shdr_fmd->weight_offset[ 1 ][ 1 ]	= IO_SHDR.WGHTGOFS.bit.WGHTGOFS_1;
	shdr_fmd->weight_offset[ 1 ][ 2 ]	= IO_SHDR.WGHTGOFS.bit.WGHTGOFS_2;
	shdr_fmd->weight_offset[ 1 ][ 3 ]	= IO_SHDR.WGHTGOFS.bit.WGHTGOFS_3;
	shdr_fmd->weight_offset[ 1 ][ 4 ]	= IO_SHDR.WGHTGOFS.bit.WGHTGOFS_4;

	// WGHTBOFS.
	shdr_fmd->weight_offset[ 2 ][ 0 ]	= IO_SHDR.WGHTBOFS.bit.WGHTBOFS_0;
	shdr_fmd->weight_offset[ 2 ][ 1 ]	= IO_SHDR.WGHTBOFS.bit.WGHTBOFS_1;
	shdr_fmd->weight_offset[ 2 ][ 2 ]	= IO_SHDR.WGHTBOFS.bit.WGHTBOFS_2;
	shdr_fmd->weight_offset[ 2 ][ 3 ]	= IO_SHDR.WGHTBOFS.bit.WGHTBOFS_3;
	shdr_fmd->weight_offset[ 2 ][ 4 ]	= IO_SHDR.WGHTBOFS.bit.WGHTBOFS_4;

	// WGHTRSL.
	shdr_fmd->weight_slope[ 0 ][ 0 ]	= IO_SHDR.WGHTRSL.bit.WGHTRSL_0;
	shdr_fmd->weight_slope[ 0 ][ 1 ]	= IO_SHDR.WGHTRSL.bit.WGHTRSL_1;
	shdr_fmd->weight_slope[ 0 ][ 2 ]	= IO_SHDR.WGHTRSL.bit.WGHTRSL_2;
	shdr_fmd->weight_slope[ 0 ][ 3 ]	= IO_SHDR.WGHTRSL.bit.WGHTRSL_3;
	shdr_fmd->weight_slope[ 0 ][ 4 ]	= IO_SHDR.WGHTRSL.bit.WGHTRSL_4;

	// WGHTGSL.
	shdr_fmd->weight_slope[ 1 ][ 0 ]	= IO_SHDR.WGHTGSL.bit.WGHTGSL_0;
	shdr_fmd->weight_slope[ 1 ][ 1 ]	= IO_SHDR.WGHTGSL.bit.WGHTGSL_1;
	shdr_fmd->weight_slope[ 1 ][ 2 ]	= IO_SHDR.WGHTGSL.bit.WGHTGSL_2;
	shdr_fmd->weight_slope[ 1 ][ 3 ]	= IO_SHDR.WGHTGSL.bit.WGHTGSL_3;
	shdr_fmd->weight_slope[ 1 ][ 4 ]	= IO_SHDR.WGHTGSL.bit.WGHTGSL_4;

	// WGHTBSL.
	shdr_fmd->weight_slope[ 2 ][ 0 ]	= IO_SHDR.WGHTBSL.bit.WGHTBSL_0;
	shdr_fmd->weight_slope[ 2 ][ 1 ]	= IO_SHDR.WGHTBSL.bit.WGHTBSL_1;
	shdr_fmd->weight_slope[ 2 ][ 2 ]	= IO_SHDR.WGHTBSL.bit.WGHTBSL_2;
	shdr_fmd->weight_slope[ 2 ][ 3 ]	= IO_SHDR.WGHTBSL.bit.WGHTBSL_3;
	shdr_fmd->weight_slope[ 2 ][ 4 ]	= IO_SHDR.WGHTBSL.bit.WGHTBSL_4;

	// WGHTRB.
	shdr_fmd->weight_boundary[ 0 ][ 1 ]	= IO_SHDR.WGHTRB.bit.WGHTRB_1;
	shdr_fmd->weight_boundary[ 0 ][ 2 ]	= IO_SHDR.WGHTRB.bit.WGHTRB_2;
	shdr_fmd->weight_boundary[ 0 ][ 3 ]	= IO_SHDR.WGHTRB.bit.WGHTRB_3;
	shdr_fmd->weight_boundary[ 0 ][ 4 ]	= IO_SHDR.WGHTRB.bit.WGHTRB_4;

	// WGHTGB.
	shdr_fmd->weight_boundary[ 1 ][ 1 ]	= IO_SHDR.WGHTGB.bit.WGHTGB_1;
	shdr_fmd->weight_boundary[ 1 ][ 2 ]	= IO_SHDR.WGHTGB.bit.WGHTGB_2;
	shdr_fmd->weight_boundary[ 1 ][ 3 ]	= IO_SHDR.WGHTGB.bit.WGHTGB_3;
	shdr_fmd->weight_boundary[ 1 ][ 4 ]	= IO_SHDR.WGHTGB.bit.WGHTGB_4;

	// WGHTBB.
	shdr_fmd->weight_boundary[ 2 ][ 1 ]	= IO_SHDR.WGHTBB.bit.WGHTBB_1;
	shdr_fmd->weight_boundary[ 2 ][ 2 ]	= IO_SHDR.WGHTBB.bit.WGHTBB_2;
	shdr_fmd->weight_boundary[ 2 ][ 3 ]	= IO_SHDR.WGHTBB.bit.WGHTBB_3;
	shdr_fmd->weight_boundary[ 2 ][ 4 ]	= IO_SHDR.WGHTBB.bit.WGHTBB_4;

	// ISOTH.
	shdr_fmd->iso_threshold				= IO_SHDR.ISOTH.bit.ISOTH2;

	// ISOCOEF.
	shdr_fmd->iso_coef[ 0 ]				= IO_SHDR.ISOCOEF.bit.ISO2K0;
	shdr_fmd->iso_coef[ 1 ]				= IO_SHDR.ISOCOEF.bit.ISO2K1;
	shdr_fmd->iso_coef[ 2 ]				= IO_SHDR.ISOCOEF.bit.ISO2K2;
	shdr_fmd->iso_coef[ 3 ]				= IO_SHDR.ISOCOEF.bit.ISO2K3;
	shdr_fmd->iso_coef[ 4 ]				= IO_SHDR.ISOCOEF.bit.ISO2K4;
	shdr_fmd->iso_coef[ 5 ]				= IO_SHDR.ISOCOEF.bit.ISO2K5;

	// SATTH.
	shdr_fmd->sat_threshold				= IO_SHDR.SATTH.bit.SATTH;

	// EXP77MD.
	shdr_fmd->exp77_mode				= IO_SHDR.EXP77MD.bit.EXP77MD;

	// EXP77MD.
	shdr_fmd->fmd_sel					= IO_SHDR.FMDSEL.bit.FMDSEL;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Set_PreMask( const T_IM_SHDR_PMSK* const shdr_pmsk )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_pmsk == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_PreMask() error. shdr_pmsk = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_pmsk->pmsk_mode > D_IM_SHDR_PMSKMD_AVE ) {
		Ddim_Assertion(("Im_SHDR_Set_PreMask() error. pmsk_mode is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// TLUT.
	IO_SHDR.TLUT.bit.TLUT_0		= shdr_pmsk->tlut[ 0 ];
	IO_SHDR.TLUT.bit.TLUT_1		= shdr_pmsk->tlut[ 1 ];
	IO_SHDR.TLUT.bit.TLUT_2		= shdr_pmsk->tlut[ 2 ];
	IO_SHDR.TLUT.bit.TLUT_3		= shdr_pmsk->tlut[ 3 ];
	IO_SHDR.TLUT.bit.TLUT_4		= shdr_pmsk->tlut[ 4 ];
	IO_SHDR.TLUT.bit.TLUT_5		= shdr_pmsk->tlut[ 5 ];
	IO_SHDR.TLUT.bit.TLUT_6		= shdr_pmsk->tlut[ 6 ];
	IO_SHDR.TLUT.bit.TLUT_7		= shdr_pmsk->tlut[ 7 ];
	IO_SHDR.TLUT.bit.TLUT_8		= shdr_pmsk->tlut[ 8 ];
	IO_SHDR.TLUT.bit.TLUT_9		= shdr_pmsk->tlut[ 9 ];
	IO_SHDR.TLUT.bit.TLUT_10	= shdr_pmsk->tlut[ 10 ];
	IO_SHDR.TLUT.bit.TLUT_11	= shdr_pmsk->tlut[ 11 ];
	IO_SHDR.TLUT.bit.TLUT_12	= shdr_pmsk->tlut[ 12 ];
	IO_SHDR.TLUT.bit.TLUT_13	= shdr_pmsk->tlut[ 13 ];
	IO_SHDR.TLUT.bit.TLUT_14	= shdr_pmsk->tlut[ 14 ];
	IO_SHDR.TLUT.bit.TLUT_15	= shdr_pmsk->tlut[ 15 ];
	IO_SHDR.TLUT.bit.TLUT_16	= shdr_pmsk->tlut[ 16 ];

	// PMSKMD.
	IO_SHDR.PMSKMD.bit.PMSKMD	= shdr_pmsk->pmsk_mode;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Get_PreMask( T_IM_SHDR_PMSK* const shdr_pmsk )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_pmsk == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_PreMask() error. shdr_pmsk = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// TLUT.
	shdr_pmsk->tlut[ 0 ]	= IO_SHDR.TLUT.bit.TLUT_0;
	shdr_pmsk->tlut[ 1 ]	= IO_SHDR.TLUT.bit.TLUT_1;
	shdr_pmsk->tlut[ 2 ]	= IO_SHDR.TLUT.bit.TLUT_2;
	shdr_pmsk->tlut[ 3 ]	= IO_SHDR.TLUT.bit.TLUT_3;
	shdr_pmsk->tlut[ 4 ]	= IO_SHDR.TLUT.bit.TLUT_4;
	shdr_pmsk->tlut[ 5 ]	= IO_SHDR.TLUT.bit.TLUT_5;
	shdr_pmsk->tlut[ 6 ]	= IO_SHDR.TLUT.bit.TLUT_6;
	shdr_pmsk->tlut[ 7 ]	= IO_SHDR.TLUT.bit.TLUT_7;
	shdr_pmsk->tlut[ 8 ]	= IO_SHDR.TLUT.bit.TLUT_8;
	shdr_pmsk->tlut[ 9 ]	= IO_SHDR.TLUT.bit.TLUT_9;
	shdr_pmsk->tlut[ 10 ]	= IO_SHDR.TLUT.bit.TLUT_10;
	shdr_pmsk->tlut[ 11 ]	= IO_SHDR.TLUT.bit.TLUT_11;
	shdr_pmsk->tlut[ 12 ]	= IO_SHDR.TLUT.bit.TLUT_12;
	shdr_pmsk->tlut[ 13 ]	= IO_SHDR.TLUT.bit.TLUT_13;
	shdr_pmsk->tlut[ 14 ]	= IO_SHDR.TLUT.bit.TLUT_14;
	shdr_pmsk->tlut[ 15 ]	= IO_SHDR.TLUT.bit.TLUT_15;
	shdr_pmsk->tlut[ 16 ]	= IO_SHDR.TLUT.bit.TLUT_16;

	// PMSKMD.
	shdr_pmsk->pmsk_mode	= IO_SHDR.PMSKMD.bit.PMSKMD;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Set_Spnr( const T_IM_SHDR_SPNR* const shdr_spnr )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_spnr == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_Spnr() error. shdr_spnr = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_spnr->spnr_en > D_IM_SHDR_ENABLE ) {
		Ddim_Assertion(("Im_SHDR_Set_Spnr() error. spnr_en is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// SPNR.
	IO_SHDR.SPNREN.bit.SPNREN	= shdr_spnr->spnr_en;

	// SPEBD.
	IO_SHDR.SPEBD.bit.SPEBD_1	= shdr_spnr->spe_boundary[ 1 ];
	IO_SHDR.SPEBD.bit.SPEBD_2	= shdr_spnr->spe_boundary[ 2 ];
	IO_SHDR.SPEBD.bit.SPEBD_3	= shdr_spnr->spe_boundary[ 3 ];

	// SPEOF.
	IO_SHDR.SPEOF.bit.SPEOF_0	= shdr_spnr->spe_offset[ 0 ];
	IO_SHDR.SPEOF.bit.SPEOF_1	= shdr_spnr->spe_offset[ 1 ];
	IO_SHDR.SPEOF.bit.SPEOF_2	= shdr_spnr->spe_offset[ 2 ];
	IO_SHDR.SPEOF.bit.SPEOF_3	= shdr_spnr->spe_offset[ 3 ];

	// SPEBLD.
	IO_SHDR.SPEBLD.bit.SPEBLD	= shdr_spnr->spe_blend;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Get_Spnr( T_IM_SHDR_SPNR* const shdr_spnr )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_spnr == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Spnr() error. shdr_spnr = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// SPNR.
	shdr_spnr->spnr_en				= IO_SHDR.SPNREN.bit.SPNREN;

	// SPEBD.
	shdr_spnr->spe_boundary[ 1 ]	= IO_SHDR.SPEBD.bit.SPEBD_1;
	shdr_spnr->spe_boundary[ 2 ]	= IO_SHDR.SPEBD.bit.SPEBD_2;
	shdr_spnr->spe_boundary[ 3 ]	= IO_SHDR.SPEBD.bit.SPEBD_3;

	// SPEOF.
	shdr_spnr->spe_offset[ 0 ]		= IO_SHDR.SPEOF.bit.SPEOF_0;
	shdr_spnr->spe_offset[ 1 ]		= IO_SHDR.SPEOF.bit.SPEOF_1;
	shdr_spnr->spe_offset[ 2 ]		= IO_SHDR.SPEOF.bit.SPEOF_2;
	shdr_spnr->spe_offset[ 3 ]		= IO_SHDR.SPEOF.bit.SPEOF_3;

	// SPEBLD.
	shdr_spnr->spe_blend			= IO_SHDR.SPEBLD.bit.SPEBLD;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Set_Mask( const T_IM_SHDR_MSK* const shdr_msk )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_msk == NULL ) {
		Ddim_Assertion(("Im_SHDR_Set_Mask() error. shdr_msk = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
	if ( shdr_msk->msk_mode > D_IM_SHDR_MSKMD_MSKONLY ) {
		Ddim_Assertion(("Im_SHDR_Set_Mask() error. msk_mode is invalid\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// MSKY2RCLPUL.
	IO_SHDR.MSKY2RCLPUL.bit.MSKY2RCLPUL_0	= shdr_msk->y2r_clp_upper_long[ 0 ];
	IO_SHDR.MSKY2RCLPUL.bit.MSKY2RCLPUL_1	= shdr_msk->y2r_clp_upper_long[ 1 ];
	IO_SHDR.MSKY2RCLPUL.bit.MSKY2RCLPUL_2	= shdr_msk->y2r_clp_upper_long[ 2 ];

	// MSKY2RCLPLL.
	IO_SHDR.MSKY2RCLPLL.bit.MSKY2RCLPLL_0	= shdr_msk->y2r_clp_lower_long[ 0 ];
	IO_SHDR.MSKY2RCLPLL.bit.MSKY2RCLPLL_1	= shdr_msk->y2r_clp_lower_long[ 1 ];
	IO_SHDR.MSKY2RCLPLL.bit.MSKY2RCLPLL_2	= shdr_msk->y2r_clp_lower_long[ 2 ];

	// MSKY2RCLPUS.
	IO_SHDR.MSKY2RCLPUS.bit.MSKY2RCLPUS_0	= shdr_msk->y2r_clp_upper_short[ 0 ];
	IO_SHDR.MSKY2RCLPUS.bit.MSKY2RCLPUS_1	= shdr_msk->y2r_clp_upper_short[ 1 ];
	IO_SHDR.MSKY2RCLPUS.bit.MSKY2RCLPUS_2	= shdr_msk->y2r_clp_upper_short[ 2 ];

	// MSKY2RCLPLS.
	IO_SHDR.MSKY2RCLPLS.bit.MSKY2RCLPLS_0	= shdr_msk->y2r_clp_lower_short[ 0 ];
	IO_SHDR.MSKY2RCLPLS.bit.MSKY2RCLPLS_1	= shdr_msk->y2r_clp_lower_short[ 1 ];
	IO_SHDR.MSKY2RCLPLS.bit.MSKY2RCLPLS_2	= shdr_msk->y2r_clp_lower_short[ 2 ];

	// ALPHA.
	IO_SHDR.ALPHA.bit.ALPHA					= shdr_msk->alpha;

	// LPFC.
	IO_SHDR.LPFC.bit.LPFC_0_0				= shdr_msk->lpfc[ 0 ][ 0 ];
	IO_SHDR.LPFC.bit.LPFC_0_1				= shdr_msk->lpfc[ 0 ][ 1 ];
	IO_SHDR.LPFC.bit.LPFC_0_2				= shdr_msk->lpfc[ 0 ][ 2 ];
	IO_SHDR.LPFC.bit.LPFC_1_0				= shdr_msk->lpfc[ 1 ][ 0 ];
	IO_SHDR.LPFC.bit.LPFC_1_1				= shdr_msk->lpfc[ 1 ][ 1 ];
	IO_SHDR.LPFC.bit.LPFC_1_2				= shdr_msk->lpfc[ 1 ][ 2 ];
	IO_SHDR.LPFC.bit.LPFC_2_0				= shdr_msk->lpfc[ 2 ][ 0 ];
	IO_SHDR.LPFC.bit.LPFC_2_1				= shdr_msk->lpfc[ 2 ][ 1 ];
	IO_SHDR.LPFC.bit.LPFC_2_2				= shdr_msk->lpfc[ 2 ][ 2 ];

	// BLDOFS.
	IO_SHDR.BLDOFS.bit.BLDOFS_0				= shdr_msk->blend_offset[ 0 ];
	IO_SHDR.BLDOFS.bit.BLDOFS_1				= shdr_msk->blend_offset[ 1 ];
	IO_SHDR.BLDOFS.bit.BLDOFS_2				= shdr_msk->blend_offset[ 2 ];
	IO_SHDR.BLDOFS.bit.BLDOFS_3				= shdr_msk->blend_offset[ 3 ];
	IO_SHDR.BLDOFS.bit.BLDOFS_4				= shdr_msk->blend_offset[ 4 ];
	IO_SHDR.BLDOFS.bit.BLDOFS_5				= shdr_msk->blend_offset[ 5 ];
	IO_SHDR.BLDOFS.bit.BLDOFS_6				= shdr_msk->blend_offset[ 6 ];

	// BLDSL.
	IO_SHDR.BLDSL.bit.BLDSL_0				= shdr_msk->blend_slope[ 0 ];
	IO_SHDR.BLDSL.bit.BLDSL_1				= shdr_msk->blend_slope[ 1 ];
	IO_SHDR.BLDSL.bit.BLDSL_2				= shdr_msk->blend_slope[ 2 ];
	IO_SHDR.BLDSL.bit.BLDSL_3				= shdr_msk->blend_slope[ 3 ];
	IO_SHDR.BLDSL.bit.BLDSL_4				= shdr_msk->blend_slope[ 4 ];
	IO_SHDR.BLDSL.bit.BLDSL_5				= shdr_msk->blend_slope[ 5 ];
	IO_SHDR.BLDSL.bit.BLDSL_6				= shdr_msk->blend_slope[ 6 ];

	// BLDB.
	IO_SHDR.BLDB.bit.BLDB_1					= shdr_msk->blend_boundary[ 1 ];
	IO_SHDR.BLDB.bit.BLDB_2					= shdr_msk->blend_boundary[ 2 ];
	IO_SHDR.BLDB.bit.BLDB_3					= shdr_msk->blend_boundary[ 3 ];
	IO_SHDR.BLDB.bit.BLDB_4					= shdr_msk->blend_boundary[ 4 ];
	IO_SHDR.BLDB.bit.BLDB_5					= shdr_msk->blend_boundary[ 5 ];
	IO_SHDR.BLDB.bit.BLDB_6					= shdr_msk->blend_boundary[ 6 ];

	// NORMGAIN.
	IO_SHDR.NORMGAIN.bit.NORMGAIN_0			= shdr_msk->norm_gain[ 0 ];
	IO_SHDR.NORMGAIN.bit.NORMGAIN_1			= shdr_msk->norm_gain[ 1 ];
	IO_SHDR.NORMGAIN.bit.NORMGAIN_2			= shdr_msk->norm_gain[ 2 ];

	// NORMOFS.
	IO_SHDR.NORMOFS.bit.NORMOFS_0			= shdr_msk->norm_offset[ 0 ];
	IO_SHDR.NORMOFS.bit.NORMOFS_1			= shdr_msk->norm_offset[ 1 ];
	IO_SHDR.NORMOFS.bit.NORMOFS_2			= shdr_msk->norm_offset[ 2 ];

	// MSKMD.
	IO_SHDR.MSKMD.bit.MSKMD					= shdr_msk->msk_mode;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}

INT32 Im_SHDR_Get_Mask( T_IM_SHDR_MSK* const shdr_msk )
{
#ifdef CO_PARAM_CHECK
	if ( shdr_msk == NULL ) {
		Ddim_Assertion(("Im_SHDR_Get_Mask() error. shdr_msk = NULL\n"));
		return D_IM_SHDR_INPUT_PARAM_ERROR;
	}
#endif

	im_shdr_on_pclk();
	im_shdr_dsb();

	// MSKY2RCLPUL.
	shdr_msk->y2r_clp_upper_long[ 0 ]	= IO_SHDR.MSKY2RCLPUL.bit.MSKY2RCLPUL_0;
	shdr_msk->y2r_clp_upper_long[ 1 ]	= IO_SHDR.MSKY2RCLPUL.bit.MSKY2RCLPUL_1;
	shdr_msk->y2r_clp_upper_long[ 2 ]	= IO_SHDR.MSKY2RCLPUL.bit.MSKY2RCLPUL_2;

	// MSKY2RCLPLL.
	shdr_msk->y2r_clp_lower_long[ 0 ]	= IO_SHDR.MSKY2RCLPLL.bit.MSKY2RCLPLL_0;
	shdr_msk->y2r_clp_lower_long[ 1 ]	= IO_SHDR.MSKY2RCLPLL.bit.MSKY2RCLPLL_1;
	shdr_msk->y2r_clp_lower_long[ 2 ]	= IO_SHDR.MSKY2RCLPLL.bit.MSKY2RCLPLL_2;

	// MSKY2RCLPUS.
	shdr_msk->y2r_clp_upper_short[ 0 ]	= IO_SHDR.MSKY2RCLPUS.bit.MSKY2RCLPUS_0;
	shdr_msk->y2r_clp_upper_short[ 1 ]	= IO_SHDR.MSKY2RCLPUS.bit.MSKY2RCLPUS_1;
	shdr_msk->y2r_clp_upper_short[ 2 ]	= IO_SHDR.MSKY2RCLPUS.bit.MSKY2RCLPUS_2;

	// MSKY2RCLPLS.
	shdr_msk->y2r_clp_lower_short[ 0 ]	= IO_SHDR.MSKY2RCLPLS.bit.MSKY2RCLPLS_0;
	shdr_msk->y2r_clp_lower_short[ 1 ]	= IO_SHDR.MSKY2RCLPLS.bit.MSKY2RCLPLS_1;
	shdr_msk->y2r_clp_lower_short[ 2 ]	= IO_SHDR.MSKY2RCLPLS.bit.MSKY2RCLPLS_2;

	// ALPHA.
	shdr_msk->alpha						= IO_SHDR.ALPHA.bit.ALPHA;

	// LPFC.
	shdr_msk->lpfc[ 0 ][ 0 ]			= IO_SHDR.LPFC.bit.LPFC_0_0;
	shdr_msk->lpfc[ 0 ][ 1 ]			= IO_SHDR.LPFC.bit.LPFC_0_1;
	shdr_msk->lpfc[ 0 ][ 2 ]			= IO_SHDR.LPFC.bit.LPFC_0_2;
	shdr_msk->lpfc[ 1 ][ 0 ]			= IO_SHDR.LPFC.bit.LPFC_1_0;
	shdr_msk->lpfc[ 1 ][ 1 ]			= IO_SHDR.LPFC.bit.LPFC_1_1;
	shdr_msk->lpfc[ 1 ][ 2 ]			= IO_SHDR.LPFC.bit.LPFC_1_2;
	shdr_msk->lpfc[ 2 ][ 0 ]			= IO_SHDR.LPFC.bit.LPFC_2_0;
	shdr_msk->lpfc[ 2 ][ 1 ]			= IO_SHDR.LPFC.bit.LPFC_2_1;
	shdr_msk->lpfc[ 2 ][ 2 ]			= IO_SHDR.LPFC.bit.LPFC_2_2;

	// BLDOFS.
	shdr_msk->blend_offset[ 0 ]			= IO_SHDR.BLDOFS.bit.BLDOFS_0;
	shdr_msk->blend_offset[ 1 ]			= IO_SHDR.BLDOFS.bit.BLDOFS_1;
	shdr_msk->blend_offset[ 2 ]			= IO_SHDR.BLDOFS.bit.BLDOFS_2;
	shdr_msk->blend_offset[ 3 ]			= IO_SHDR.BLDOFS.bit.BLDOFS_3;
	shdr_msk->blend_offset[ 4 ]			= IO_SHDR.BLDOFS.bit.BLDOFS_4;
	shdr_msk->blend_offset[ 5 ]			= IO_SHDR.BLDOFS.bit.BLDOFS_5;
	shdr_msk->blend_offset[ 6 ]			= IO_SHDR.BLDOFS.bit.BLDOFS_6;

	// BLDSL.
	shdr_msk->blend_slope[ 0 ]			= IO_SHDR.BLDSL.bit.BLDSL_0;
	shdr_msk->blend_slope[ 1 ]			= IO_SHDR.BLDSL.bit.BLDSL_1;
	shdr_msk->blend_slope[ 2 ]			= IO_SHDR.BLDSL.bit.BLDSL_2;
	shdr_msk->blend_slope[ 3 ]			= IO_SHDR.BLDSL.bit.BLDSL_3;
	shdr_msk->blend_slope[ 4 ]			= IO_SHDR.BLDSL.bit.BLDSL_4;
	shdr_msk->blend_slope[ 5 ]			= IO_SHDR.BLDSL.bit.BLDSL_5;
	shdr_msk->blend_slope[ 6 ]			= IO_SHDR.BLDSL.bit.BLDSL_6;

	// BLDB.
	shdr_msk->blend_boundary[ 1 ]		= IO_SHDR.BLDB.bit.BLDB_1;
	shdr_msk->blend_boundary[ 2 ]		= IO_SHDR.BLDB.bit.BLDB_2;
	shdr_msk->blend_boundary[ 3 ]		= IO_SHDR.BLDB.bit.BLDB_3;
	shdr_msk->blend_boundary[ 4 ]		= IO_SHDR.BLDB.bit.BLDB_4;
	shdr_msk->blend_boundary[ 5 ]		= IO_SHDR.BLDB.bit.BLDB_5;
	shdr_msk->blend_boundary[ 6 ]		= IO_SHDR.BLDB.bit.BLDB_6;

	// NORMGAIN.
	shdr_msk->norm_gain[ 0 ]			= IO_SHDR.NORMGAIN.bit.NORMGAIN_0;
	shdr_msk->norm_gain[ 1 ]			= IO_SHDR.NORMGAIN.bit.NORMGAIN_1;
	shdr_msk->norm_gain[ 2 ]			= IO_SHDR.NORMGAIN.bit.NORMGAIN_2;

	// NORMOFS.
	shdr_msk->norm_offset[ 0 ]			= IO_SHDR.NORMOFS.bit.NORMOFS_0;
	shdr_msk->norm_offset[ 1 ]			= IO_SHDR.NORMOFS.bit.NORMOFS_1;
	shdr_msk->norm_offset[ 2 ]			= IO_SHDR.NORMOFS.bit.NORMOFS_2;

	// MSKMD.
	shdr_msk->msk_mode					= IO_SHDR.MSKMD.bit.MSKMD;

	im_shdr_off_pclk();
	im_shdr_dsb();

	return D_DDIM_OK;
}


ImShdr1 *im_shdr1_new(void)
{
	ImShdr1* self = k_object_new_with_private(IM_TYPE_SHDR1,sizeof(ImShdr1Private));
	return self;
}


